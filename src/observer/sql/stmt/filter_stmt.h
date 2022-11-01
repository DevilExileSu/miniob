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

#pragma once

#include <vector>
#include <unordered_map>
#include "rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"

class Db;
class Table;
class FieldMeta;

class FilterUnit
{
public:
  FilterUnit() = default;
  ~FilterUnit()
  {
    if (left_) {
      delete left_;
      left_ = nullptr;
    }
    if (right_) {
      delete right_;
      right_ = nullptr;
    }
  }
  
  void set_comp(CompOp comp) {
    comp_ = comp;
  }

  CompOp comp() const {
    return comp_;
  }

  void set_left(Expression *expr)
  {
    left_ = expr;
  }
  void set_right(Expression *expr)
  {
    right_ = expr;
  }
  Expression *left() const
  {
    return left_;
  }
  Expression *right() const
  {
    return right_;
  }

  std::pair<const char*, const char*> get_table_name() {
    const char *left_table = nullptr;
    const char *right_table = nullptr;
    if (left_ != nullptr && left_->type() == ExprType::FIELD) {
      left_table = static_cast<FieldExpr *>(left_)->table_name();
    }
    if (right_ != nullptr && right_->type() == ExprType::FIELD) {
      right_table = static_cast<FieldExpr *>(right_)->table_name();
    }
    return std::make_pair(left_table, right_table);
  } 

private:
  CompOp comp_ = NO_OP;
  Expression *left_ = nullptr;
  Expression *right_ = nullptr;
};

class FilterStmt 
{
public:

  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  const std::vector<FilterUnit *> &filter_units() const
  {
    return filter_units_;
  }

  void single_filter_units(const char *table_name, std::vector<FilterUnit *> &single_filter_units) const 
  { 
    auto iter = single_filter_units_.find(std::string(table_name));
    if (iter != single_filter_units_.end()) {
        single_filter_units = iter->second;
    }
  }

  const std::unordered_map<std::string, std::vector<FilterUnit *>> &get_single_filter_units() const {
    return single_filter_units_;
  }

  void add_single_filter_unit(const char *table_name, FilterUnit *filter_unit) {
    single_filter_units_[std::string(table_name)].emplace_back(filter_unit);
  }

  void add_filter_unit(FilterUnit *filter_unit) {
    filter_units_.emplace_back(filter_unit);
  }

  const std::vector<FilterUnit *> &sub_select_units() const
  {
    return sub_select_units_;
  }

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
			const Condition *conditions, int condition_num,
			FilterStmt *&stmt);

  static RC create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
			       const Condition &condition, FilterUnit *&filter_unit, FilterStmt *tmp_stmt);

private:
  std::unordered_map<std::string, std::vector<FilterUnit *>> single_filter_units_;
  std::vector<FilterUnit *> filter_units_; // 默认当前都是AND关系
  std::vector<FilterUnit *> sub_select_units_;
};
