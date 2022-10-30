/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/6/6.
//
#include <algorithm>

#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
  for (size_t i = 0; i < select_stmts_.size(); i++) {
    delete select_stmts_[i];
    select_stmts_[i] = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas, bool is_agg)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
    // 如果是agg就用第一列来代替*
    if (is_agg) {
      break;
    }
  }
}

RC SelectStmt::create(Db *db, const Selects &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relation_num; i++) {
    const char *table_name = select_sql.relations[i];
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table*>(table_name, table));
  }
  // 反转tables
  std::reverse(tables.begin(), tables.end());

  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  std::vector<RelAttr> rel_attrs;
  bool is_field = false; 
  bool is_agg = false;
  
  for (int i = select_sql.attr_num - 1; i >= 0; i--) {
    // RelAttr包含聚合函数的处理
    const RelAttr &relation_attr = select_sql.attributes[i];

    // 1. 先判断是否为字段和聚合函数混合
    if (relation_attr.agg_func != AggFunc::NONE) {
      is_agg = true;
    } else {
      is_field = true;
    }

    if (is_agg && is_field) {
      return RC::SCHEMA_FIELD_MISSING;
    }

    // 2. 检查字段是否有效
    if (common::is_blank(relation_attr.relation_name) && 0 == strcmp(relation_attr.attribute_name, "*")) {
      for (Table *table : tables) {
        wildcard_fields(table, query_fields, is_agg);
      }
    } else if (!common::is_blank(relation_attr.relation_name)) { // TODO
      const char *table_name = relation_attr.relation_name;
      const char *field_name = relation_attr.attribute_name;
      // field_name == nullptr 只可能使RelAttr中聚合参数为整型数字
      // 这里就随便选择一个字段进行统计s
      if (field_name == nullptr) {
        wildcard_fields(tables[0], query_fields, is_agg);
        continue;
      }
      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          wildcard_fields(table, query_fields, is_agg);
        }
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          wildcard_fields(table, query_fields, is_agg);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

        query_fields.push_back(Field(table, field_meta));
        }
      }
    } else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name);
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta));

    }
    // 2. 对聚合函数的处理
    if (is_agg) {
      // 2.1 *只能出现在COUNT中
      if (0 == strcmp(relation_attr.attribute_name, "*") && relation_attr.agg_func != AggFunc::COUNT) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      rel_attrs.emplace_back(relation_attr);
    }
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (!tables.empty()) {
    default_table = tables[0];
  }
  std::vector<SelectStmt *> sub_select_stmt;
  for (size_t i=0; i<select_sql.condition_num; i++) {
    RC rc = RC::SUCCESS;
    if (select_sql.conditions[i].left_is_attr == 0 && select_sql.conditions[i].left_value.type == AttrType::SELECTS) {
      Selects select = *(Selects *)select_sql.conditions[i].left_value.data;
      // 将父查询中的涉及到的表 添加到 子查询中
      for (size_t i = 0; i < select_sql.relation_num; i++) {
        select.relations[select.relation_num] = select_sql.relations[i];
        select.alias[select.relation_num++] = select_sql.alias[i];
      } 
      Stmt *sub_stmt = nullptr;
      rc = SelectStmt::create(db, select, sub_stmt);
      SelectStmt *select_stmt = static_cast<SelectStmt *>(sub_stmt);
      sub_select_stmt.emplace_back(select_stmt);
    } 
    if (select_sql.conditions[i].right_is_attr == 0 && select_sql.conditions[i].right_value.type == AttrType::SELECTS) {
      Selects select = *(Selects *)select_sql.conditions[i].right_value.data;
      // 将父查询中的涉及到的表 添加到 子查询中
      for (size_t i = 0; i < select_sql.relation_num; i++) {
        select.relations[select.relation_num] = select_sql.relations[i];
        select.alias[select.relation_num++] = select_sql.alias[i];
      }  
      Stmt *sub_stmt = nullptr;
      rc = SelectStmt::create(db, select, sub_stmt); 
      SelectStmt *select_stmt = static_cast<SelectStmt *>(sub_stmt);
      sub_select_stmt.emplace_back(select_stmt);
    }
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, default_table, &table_map,
           select_sql.conditions, select_sql.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  std::reverse(rel_attrs.begin(), rel_attrs.end());
  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->rel_attrs_.swap(rel_attrs); 
  select_stmt->select_stmts_.swap(sub_select_stmt);
  select_stmt->filter_stmt_ = filter_stmt;
  stmt = select_stmt;
  return RC::SUCCESS;
}
