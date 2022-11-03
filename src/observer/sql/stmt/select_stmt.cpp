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
  for (size_t i = 0; i < sub_select_stmts_.size(); i++) {
    delete sub_select_stmts_[i].select;
    sub_select_stmts_[i].select = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas, bool is_agg, std::unordered_map<std::string, std::string> &table_alias)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    Field field(table, table_meta.field(i));
    field.set_alias(nullptr, table_alias[table->name()].c_str());
    field_metas.push_back(field);
    // 如果是agg就用第一列来代替*
    if (is_agg) {
      break;
    }
  }
}

RC SelectStmt::create_sub_select(Db *db, std::unordered_map<std::string, Table *> &table_map, const Selects &select_sql, Stmt *&stmt, bool &has_joint, Table *&joint_table, std::unordered_map<std::string, std::string> &alias2table) {
  
  std::vector<Table *> tables; 
  std::unordered_map<std::string, std::string> table_alias;
  for (size_t i = 0; i < select_sql.relation_num; i++) {
    const char *table_name = select_sql.relations[i];
    if (nullptr == table_name) {
      return RC::INVALID_ARGUMENT;
    }
    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    tables.push_back(table);
    

    
    table_map.insert(std::make_pair(table_name, table));
    // (alias): 同层不能有重复别名
    // (alias): 将表的别名也加入table_map中
    // 不考虑外层查询和内层查询的关联查询
    if (select_sql.alias[i] != nullptr) {
      auto iter = alias2table.find(select_sql.alias[i]);
      if (iter != alias2table.end()) {
        return INVALID_ARGUMENT;
      }
      alias2table.insert(std::make_pair(select_sql.alias[i], table->name()));
      table_map.insert(std::make_pair(select_sql.alias[i], table));
      table_alias.insert(std::make_pair(table->name(), select_sql.alias[i]));
    }
  }

  std::vector<Field> query_fields;
  std::vector<RelAttr> rel_attrs;
  bool is_field = false;
  bool is_agg = false;


  for (int i = 0; i < select_sql.attr_num; i++) {
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
        wildcard_fields(table, query_fields, is_agg, table_alias);
      }
    } else if (!common::is_blank(relation_attr.relation_name)) {  // TODO
      // alias: 如果含有列别名需要进行额外的处理，给Field添加alias字段？
      const char *table_name = relation_attr.relation_name;
      const char *field_name = relation_attr.attribute_name;
      // field_name == nullptr 只可能使RelAttr中聚合参数为整型数字
      // 这里就随便选择一个字段进行统计
      if (field_name == nullptr) {
        wildcard_fields(tables[0], query_fields, is_agg, table_alias);
        continue;
      }
      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          wildcard_fields(table, query_fields, is_agg, table_alias);
        }
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          wildcard_fields(table, query_fields, is_agg, table_alias);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            return RC::SCHEMA_FIELD_MISSING;
          }
          
          Field field(table, field_meta);
          field.set_alias(relation_attr.alias, table_alias[table->name()].c_str());
          query_fields.push_back(field);
        }
      }
    } else {
      if (tables.size() != 1) {
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name);
      if (nullptr == field_meta) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      Field field(table, field_meta);
      field.set_alias(relation_attr.alias, table_alias[table->name()].c_str());
      query_fields.push_back(field);
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
  Table *default_table = nullptr;
  if (!tables.empty()) {
    default_table = tables[0];
  }

  joint_table = nullptr;
  auto add_relation = [&](const char *relation_name) -> RC {
    auto iter = table_map.find(relation_name);
    if (iter == table_map.end()) {
      return RC::INVALID_ARGUMENT; 
    }
    bool has_relation = false;
    for (int i=0; i<select_sql.relation_num; i++) {
      if (0 == strcmp(select_sql.relations[i], relation_name)) {
        // joint_table = iter->second;
        has_relation = true;
        break;
      }
    }
    if (!has_relation) {
      tables.emplace_back(iter->second);
      has_joint = true;
      joint_table = iter->second;
    }
    return RC::SUCCESS;
  }; 

  std::vector<SubSelectStmt> sub_select_stmt;
  std::unordered_map<std::string, std::string> sub_alias2table;
  for (size_t i = 0; i < select_sql.condition_num; i++) {
    RC rc = RC::SUCCESS;
    if (select_sql.conditions[i].left_is_attr == 1 && select_sql.conditions[i].left_attr.relation_name != nullptr) {
      rc = add_relation(select_sql.conditions[i].left_attr.relation_name);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
    if (select_sql.conditions[i].right_is_attr == 1 && select_sql.conditions[i].right_attr.relation_name != nullptr) {
      rc = add_relation(select_sql.conditions[i].right_attr.relation_name);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
    if (select_sql.conditions[i].left_is_attr == 0 && select_sql.conditions[i].left_value.type == AttrType::SELECTS) {
      Selects select = *(Selects *)select_sql.conditions[i].left_value.data;
      Stmt *sub_stmt = nullptr;
      Table *sub_joint_table = nullptr;
      rc = SelectStmt::create_sub_select(db, table_map, select, sub_stmt, has_joint, sub_joint_table, sub_alias2table);
      if (joint_table == nullptr && sub_joint_table != nullptr) {
        joint_table = sub_joint_table;
      }
      if (!has_joint && sub_joint_table == nullptr) {
        sub_joint_table = default_table;
      }
      SelectStmt *select_stmt = static_cast<SelectStmt *>(sub_stmt);
      SubSelectStmt sub_select;
      sub_select.has_joint = has_joint;
      sub_select.is_left_value = true;
      sub_select.select = select_stmt;
      sub_select.joint_table = sub_joint_table;
      sub_select_stmt.emplace_back(sub_select);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }

    if (select_sql.conditions[i].right_is_attr == 0 && select_sql.conditions[i].right_value.type == AttrType::SELECTS) {
      Selects select = *(Selects *)select_sql.conditions[i].right_value.data;
      Stmt *sub_stmt = nullptr;
      Table *sub_joint_table = nullptr;
      rc = SelectStmt::create_sub_select(db, table_map, select, sub_stmt, has_joint, sub_joint_table, sub_alias2table);
      if (joint_table == nullptr && sub_joint_table != nullptr) {
        joint_table = sub_joint_table;
      }
      if (!has_joint && sub_joint_table == nullptr) {
        sub_joint_table = default_table;
      }
      SelectStmt *select_stmt = static_cast<SelectStmt *>(sub_stmt);
      SubSelectStmt sub_select;
      sub_select.has_joint = has_joint;
      sub_select.is_left_value = false;
      sub_select.select = select_stmt;
      sub_select.joint_table = sub_joint_table;
      sub_select_stmt.emplace_back(sub_select);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc =
      FilterStmt::create(db, default_table, &table_map, select_sql.conditions, select_sql.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // std::reverse(rel_attrs.begin(), rel_attrs.end());
  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->rel_attrs_.swap(rel_attrs);
  select_stmt->sub_select_stmts_.swap(sub_select_stmt);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->is_and_ = select_sql.is_and;
  stmt = select_stmt;
  return RC::SUCCESS;
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
  std::unordered_map<std::string, std::string> table_alias;
  std::unordered_map<std::string, std::string> alias2table;
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
    table_map.insert(std::make_pair(table_name, table));
    // (alias): 同层不能有重复别名
    // (alias): 将表的别名也加入table_map中
    if (select_sql.alias[i] != nullptr) {
      auto iter = alias2table.find(select_sql.alias[i]);
      if (iter != alias2table.end()) {
        return INVALID_ARGUMENT;
      }
      alias2table.insert(std::make_pair(select_sql.alias[i], table->name()));
      table_map.insert(std::make_pair(select_sql.alias[i], table));
      table_alias.insert(std::make_pair(table->name(), select_sql.alias[i]));
    }

  }
  // 反转tables
  std::reverse(tables.begin(), tables.end());
  std::vector<std::pair<bool, int>> fields_or_expr;
  std::vector<TreeExpr *> query_expr;

  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  std::vector<RelAttr> rel_attrs;
  bool is_field = false;
  bool is_agg = false;
  
  Table *default_table = nullptr;
  if (!tables.empty()) {
    default_table = tables[0];
  }

  // expression: 
  for (int i = select_sql.expr_num - 1; i >= 0 ; i--) {
    // 如果当前的表达式类型为Attr
    if (select_sql.exp[i]->expr_type == NodeType::ATTR) {
      // RelAttr包含聚合函数的处理
      const RelAttr &relation_attr = *select_sql.exp[i]->attr;

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
          int cur = query_fields.size();
          wildcard_fields(table, query_fields, is_agg, table_alias);
          for (int i=cur; i<query_fields.size(); i++) {
            fields_or_expr.emplace_back(std::make_pair(true, i));
          }
          if (is_agg) {
            break;
          }
        }
      } else if (!common::is_blank(relation_attr.relation_name)) {  // TODO
        const char *table_name = relation_attr.relation_name;
        const char *field_name = relation_attr.attribute_name;
        // field_name == nullptr 只可能使RelAttr中聚合参数为整型数字
        // 这里就随便选择一个字段进行统计s
        // TODO(vanish): alias: 如果含有列别名需要进行额外的处理，给Field添加alias字段？ 
        if (field_name == nullptr) {
          int cur = query_fields.size();
          wildcard_fields(tables[0], query_fields, is_agg, table_alias);
          for (int i=cur; i<query_fields.size(); i++) {
            fields_or_expr.emplace_back(std::make_pair(true, i));
          }
          continue;
        }
        if (0 == strcmp(table_name, "*")) {
          if (0 != strcmp(field_name, "*")) {
            LOG_WARN("invalid field name while table is *. attr=%s", field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          for (Table *table : tables) {
            int cur = query_fields.size();
            wildcard_fields(table, query_fields, is_agg, table_alias);
            for (int i=cur; i<query_fields.size(); i++) {
              fields_or_expr.emplace_back(std::make_pair(true, i));
            }
            if (is_agg) {
              break;
            }
          }
        } else {
          auto iter = table_map.find(table_name);
          if (iter == table_map.end()) {
            LOG_WARN("no such table in from list: %s", table_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          Table *table = iter->second;
          if (0 == strcmp(field_name, "*")) {
            int cur = query_fields.size();
            wildcard_fields(table, query_fields, is_agg, table_alias);
            for (int i=cur; i<query_fields.size(); i++) {
              fields_or_expr.emplace_back(std::make_pair(true, i));
            }
          } else {
            const FieldMeta *field_meta = table->table_meta().field(field_name);
            if (nullptr == field_meta) {
              LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
              return RC::SCHEMA_FIELD_MISSING;
            }
  
                  
            Field field(table, field_meta);
            field.set_alias(relation_attr.alias, table_alias[table->name()].c_str());
            fields_or_expr.emplace_back(std::make_pair(true, query_fields.size()));
            query_fields.push_back(field);
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

        Field field(table, field_meta);
        field.set_alias(relation_attr.alias, table_alias[table->name()].c_str());
        fields_or_expr.emplace_back(std::make_pair(true, query_fields.size()));
        query_fields.push_back(field);
      }
      // 2. 对聚合函数的处理
      if (is_agg) {
        // 2.1 *只能出现在COUNT中
        if (0 == strcmp(relation_attr.attribute_name, "*") && relation_attr.agg_func != AggFunc::COUNT) {
          return RC::SCHEMA_FIELD_MISSING;
        }
        rel_attrs.emplace_back(relation_attr);
      }
    } else if (select_sql.exp[i]->expr_type != NodeType::VAL) {
      TreeExpr *expr = nullptr; 
      Table *table = nullptr;
      bool is_multi_table = false;
      // 生成TreeExpr
      FilterStmt::expresion_tree_generate(db, default_table, &table_map, expr, select_sql.exp[i], table, is_multi_table, is_agg, &rel_attrs, &query_fields);
      if (is_agg && is_field) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      fields_or_expr.emplace_back(std::make_pair(false, query_expr.size()));
      query_expr.emplace_back(expr);
    } else {
      return RC::INVALID_ARGUMENT;
    }
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  std::vector<SubSelectStmt> sub_select_stmt;
  std::unordered_map<std::string, std::string> sub_alias2table;
  for (size_t i = 0; i < select_sql.condition_num; i++) {
    RC rc = RC::SUCCESS;
    if (select_sql.conditions[i].left_is_attr == 0 && select_sql.conditions[i].left_value.type == AttrType::SELECTS) {
      Selects select = *(Selects *)select_sql.conditions[i].left_value.data;
      Stmt *sub_stmt = nullptr;
      bool has_joint = false;
      Table *sub_joint_table = nullptr;
      rc = SelectStmt::create_sub_select(db, table_map, select, sub_stmt, has_joint, sub_joint_table, sub_alias2table);
      if (!has_joint && sub_joint_table == nullptr) {
        sub_joint_table = default_table;
      }
      SelectStmt *select_stmt = static_cast<SelectStmt *>(sub_stmt);
      SubSelectStmt sub_select;
      sub_select.has_joint = has_joint;
      sub_select.is_left_value = true;
      sub_select.select = select_stmt;
      sub_select.joint_table = sub_joint_table;
      sub_select_stmt.emplace_back(sub_select);
    }
    if (select_sql.conditions[i].right_is_attr == 0 && select_sql.conditions[i].right_value.type == AttrType::SELECTS) {
      Selects select = *(Selects *)select_sql.conditions[i].right_value.data;
      Stmt *sub_stmt = nullptr;
      bool has_joint = false;
      Table *sub_joint_table = nullptr;
      rc = SelectStmt::create_sub_select(db, table_map, select, sub_stmt, has_joint, sub_joint_table, sub_alias2table);
      if (!has_joint && sub_joint_table == nullptr) {
        sub_joint_table = default_table;
      }
      SelectStmt *select_stmt = static_cast<SelectStmt *>(sub_stmt);
      SubSelectStmt sub_select;
      sub_select.has_joint = has_joint;
      sub_select.is_left_value = false;
      sub_select.select = select_stmt;
      sub_select.joint_table = sub_joint_table;
      sub_select_stmt.emplace_back(sub_select);
    }
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc =
      FilterStmt::create(db, default_table, &table_map, select_sql.conditions, select_sql.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // std::reverse(rel_attrs.begin(), rel_attrs.end());
  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->rel_attrs_.swap(rel_attrs);
  select_stmt->sub_select_stmts_.swap(sub_select_stmt);
  select_stmt->query_expr_.swap(query_expr);
  select_stmt->fields_or_expr_.swap(fields_or_expr);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->is_and_ = select_sql.is_and;
  stmt = select_stmt;
  return RC::SUCCESS;
}
