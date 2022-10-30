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

#include "rc.h"
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
#include "common/lang/string.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "sql/executor/execute_stage.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
		      const Condition *conditions, int condition_num,
		      FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit(db, default_table, tables, conditions[i], filter_unit, tmp_stmt);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    // tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
		       const RelAttr &attr, Table *&table, const FieldMeta *&field, CompOp comp)
{
  if (common::is_blank(attr.relation_name)) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(std::string(attr.relation_name));
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name);
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  if (common::is_blank(attr.attribute_name) && (comp == CompOp::EXISTS_OP || comp == CompOp::NOT_EXISTS_OP)) {
    field = table->table_meta().field(0);
  } else {
    field = table->table_meta().field(attr.attribute_name);
  }
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name);
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
				  const Condition &condition, FilterUnit *&filter_unit, FilterStmt *tmp_stmt)
{
  RC rc = RC::SUCCESS;
  
  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  Expression *left = nullptr;
  Expression *right = nullptr;
  Value *condition_value = nullptr;
  FieldMeta *condition_field = nullptr;
  Table *left_table = nullptr;
  Table *right_table = nullptr;
  if (condition.left_is_attr != 0) {
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.left_attr, left_table, field, comp);  
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    left = new FieldExpr(left_table, field);
    condition_field = const_cast<FieldMeta *>(field);
  } else {
    condition_value = const_cast<Value *>(&condition.left_value);
    left = new ValueExpr(condition.left_value);
  }

  if (condition.right_is_attr) {
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.right_attr, right_table, field, comp);  
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      delete left;
      return rc;
    }
    right = new FieldExpr(right_table, field);
    condition_field = const_cast<FieldMeta *>(field);
  } else {
    condition_value = const_cast<Value *>(&condition.right_value);
    right = new ValueExpr(condition.right_value);
  }

  filter_unit = new FilterUnit;
  filter_unit->set_comp(comp);
  filter_unit->set_left(left);
  filter_unit->set_right(right);
  
  // 检查两个类型是否能够比较
  // 日期类型不匹配不进行比较，其他类型不同，可以通过隐式转换来进行比较
  if (condition_value != nullptr 
      && condition_field != nullptr 
      && condition_value->type != condition_field->type() 
      && condition_field->type() == AttrType::DATES && condition_value->type != AttrType::NULL_) {

    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  if (condition_value != nullptr && condition_value->type == AttrType::SELECTS) {
    tmp_stmt->sub_select_units_.emplace_back(filter_unit);
  }

  auto add_filter_unit = [&](std::string table_name) {
    auto iter = tmp_stmt->single_filter_units_.find(table_name);
    if (iter != tmp_stmt->single_filter_units_.end()) {
        iter->second.emplace_back(filter_unit);
    } else {
      std::vector<FilterUnit *> tmp;
      tmp.emplace_back(filter_unit);
      tmp_stmt->single_filter_units_.insert(std::make_pair(table_name, tmp));
    }
  };

  if (left_table != nullptr && right_table != nullptr) {
    if (left_table == right_table) {
      std::string table_name = std::string(left_table->name());
      add_filter_unit(table_name);
    } else {
      tmp_stmt->filter_units_.emplace_back(filter_unit);
    }
  } else if (left_table != nullptr) {
    std::string table_name = std::string(left_table->name());
    add_filter_unit(table_name);
  } else if (right_table != nullptr) {
    std::string table_name = std::string(right_table->name());
    add_filter_unit(table_name);
  } else {
    std::string table_name = std::string(default_table->name());
    add_filter_unit(table_name);
  } 

  return rc;
}

