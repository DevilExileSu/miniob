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
// Created by Wangyunlai on 2022/5/22.
//
#include <cmath>
#include <unordered_map>

#include "common/log/log.h"
#include "common/lang/defer.h"
#include "sql/operator/table_scan_operator.h"
#include "sql/operator/index_scan_operator.h"
#include "sql/operator/predicate_operator.h"
#include "sql/operator/delete_operator.h"
#include "sql/operator/update_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/operator/cross_product_operator.h"
#include "sql/operator/aggregate_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/common/field_meta.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "util/util.h"
#include "sql/executor/execute_stage.h"

UpdateStmt::UpdateStmt(Table *table, FilterStmt *filter_stmt, std::vector<const Value *> &&values, std::vector<const FieldMeta *> &&field_meta)
  : table_(table), filter_stmt_(filter_stmt), values_(values), field_meta_(field_meta)
{}

UpdateStmt::~UpdateStmt() {
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}


RC UpdateStmt::create(Db *db, const Updatess &update, Stmt *&stmt)
{
  // TODO
  const char *table_name = update.relation_name;
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db = %p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  // 2. 检查表中是否存在属性
  const TableMeta &table_meta = table->table_meta();
  std::vector<const FieldMeta *> field_metas;
  std::vector<const Value *> values;

  bool has_text = false;
  RC rc = RC::SUCCESS;
  for (size_t i=0; i < update.attr_num; i++) {
    const FieldMeta *field_meta = table_meta.field(update.attribute_names[i]);
    if (nullptr == field_meta) {
      LOG_WARN("Invalid value attribute_name: %s", update.attribute_names[i]);
      return RC::SCHEMA_FIELD_MISSING;
    }

    Value *value = const_cast<Value *>(&update.values[i]);

    if (value == nullptr) {
      LOG_WARN("parse error");
      return RC::GENERIC_ERROR;
    }
    
    // 如果value是SELECTS类型
    // 1. 创建SelectStmt
    if (value->type == AttrType::SELECTS) {
      // 1.1 构造SelectStmt
      Selects select = *(Selects *)value->data;
      Stmt *stmt = nullptr;
      SelectStmt::create(db, select, stmt);
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      // 如果字段不止一个
      if (!select_stmt->is_single_field()) {
        return RC::GENERIC_ERROR;
      }
      // 1.2 创建执行器
      FilterStmt *filter_stmt = select_stmt->filter_stmt();
      std::vector<FilterUnit *> single_filter_units;
      std::vector<Operator *> scan_oper_list;
      std::vector<PredicateOperator *> pred_oper_list;
      std::vector<CrossProductOperator *> cross_oper_list;

      for (auto table: select_stmt->tables()) {
        filter_stmt->single_filter_units(table->name(), single_filter_units);

        Operator *scan_oper = try_to_create_index_scan_operator(single_filter_units);
        if (nullptr == scan_oper) {
          scan_oper = new TableScanOperator(table);
        }
        PredicateOperator *pred_oper = new PredicateOperator(single_filter_units);
        pred_oper->add_child(scan_oper);
        pred_oper_list.push_back(pred_oper);
        single_filter_units.clear();
      }

      for (int i=1; i<pred_oper_list.size() ; i++) {
        CrossProductOperator *cross_oper = new CrossProductOperator(filter_stmt->filter_units());
        if (i == 1) {
          cross_oper->add_child(pred_oper_list[0]);
        } else {
          cross_oper->add_child(cross_oper_list.back());
        }
        cross_oper->add_child(pred_oper_list[i]);
        cross_oper_list.emplace_back(cross_oper);
      }

      DEFER([&]() { 
        for (int i=0; i<scan_oper_list.size(); i++) {
          delete scan_oper_list[i]; 
        }
        for (int i=0; i<pred_oper_list.size(); i++) {
          delete pred_oper_list[i];
        }
        for (int i=0; i<cross_oper_list.size(); i++) {
          delete cross_oper_list[i];
        }
      });

      ProjectOperator project_oper;
      if (!cross_oper_list.empty()) {
        // 多表
        project_oper.add_child(cross_oper_list.back());
      } else {
        // 单表
        project_oper.add_child(pred_oper_list[0]);
      }
      for (const Field &field : select_stmt->query_fields()) {
        project_oper.add_projection(field.table(), field.meta());
      }

      if (select_stmt->is_agg()) {
        AggregateOperator agg_oper(select_stmt->rel_attrs(), select_stmt->query_fields());
        agg_oper.add_child(&project_oper);
        agg_oper.open();
        std::stringstream ss;
        while ((rc = agg_oper.next()) == RC::SUCCESS) {
        }
        // 返回聚合结果
        agg_oper.to_string(ss);
        if (rc != RC::RECORD_EOF) {
          LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
          agg_oper.close();
        } else {
          rc = agg_oper.close();
        }
        value_destroy(value);
        value_init_string(value, ss.str().c_str());
      } else {
        Tuple *tuple = nullptr;
        project_oper.open();
        while ((rc = project_oper.next()) == RC::SUCCESS) {
          // 返回结果不止一行
          if (tuple != nullptr) {
            rc = RC::INTERNAL;
          }
          tuple = project_oper.current_tuple();
          if (nullptr == tuple) {
            rc = RC::INTERNAL;
            break;
          }
        }
        TupleCell cell;
        // 只有一个字段
        std::stringstream ss;
        tuple->cell_at(0, cell);
        cell.to_string(ss);
        value_destroy(value);
        value_init_string(value, ss.str().c_str());
      }
    } else if (value->type == AttrType::AGGFUNC) {
      // 2. 如果value是AGGFUNC类型
      // 构建select
      Selects select;
      select.attr_num = 1;
      RelAttr attr = *(RelAttr *)value->data;
      select.attributes[0] = attr;
      select.condition_num = update.condition_num;
      for (int i=0; i<update.condition_num; i++) {
        select.conditions[i] = update.conditions[i];
      }
      select.relation_num = 1;
      select.relations[0] = update.relation_name;
      Stmt *stmt = nullptr;
      SelectStmt::create(db, select, stmt);
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);

      // 1.2 创建执行器
      FilterStmt *filter_stmt = select_stmt->filter_stmt();
      std::vector<FilterUnit *> single_filter_units;
      std::vector<Operator *> scan_oper_list;
      std::vector<PredicateOperator *> pred_oper_list;

      for (auto table: select_stmt->tables()) {
        filter_stmt->single_filter_units(table->name(), single_filter_units);

        Operator *scan_oper = try_to_create_index_scan_operator(single_filter_units);
        if (nullptr == scan_oper) {
          scan_oper = new TableScanOperator(table);
        }
        PredicateOperator *pred_oper = new PredicateOperator(single_filter_units);
        pred_oper->add_child(scan_oper);
        pred_oper_list.push_back(pred_oper);
        single_filter_units.clear();
      }

      DEFER([&]() { 
        for (int i=0; i<scan_oper_list.size(); i++) {
          delete scan_oper_list[i]; 
        }
        for (int i=0; i<pred_oper_list.size(); i++) {
          delete pred_oper_list[i];
        }
      });

      ProjectOperator project_oper;
      project_oper.add_child(pred_oper_list[0]);

      for (const Field &field : select_stmt->query_fields()) {
        project_oper.add_projection(field.table(), field.meta());
      }

      AggregateOperator agg_oper(select_stmt->rel_attrs(), select_stmt->query_fields());
      agg_oper.add_child(&project_oper);
      agg_oper.open();
      std::stringstream ss;
      while ((rc = agg_oper.next()) == RC::SUCCESS) {
      }
      // 返回聚合结果
      agg_oper.to_string(ss);
      if (rc != RC::RECORD_EOF) {
        LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
        agg_oper.close();
      } else {
        rc = agg_oper.close();
      }
      value_destroy(value);
      value_init_string(value, ss.str().c_str());

    }
    rc = convert(field_meta, value, has_text);
    
    field_metas.emplace_back(field_meta);
    values.emplace_back(value);
  }

    // TODO(Vanish): unique-index: 检查是否满足unique, 如果存在text类型直接跳过
  if (!has_text) {
    if ((rc = table->check_unique(field_metas, values, update.conditions, update.condition_num)) != RC::SUCCESS) {
      return rc; 
    }
  }


  // 构建 filterstmt 用于传递给 predict operator， 谓词算子
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  rc = FilterStmt::create(db, table, &table_map, update.conditions, update.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  stmt = new UpdateStmt(table, filter_stmt, std::move(values), std::move(field_metas));
  return rc;
}
