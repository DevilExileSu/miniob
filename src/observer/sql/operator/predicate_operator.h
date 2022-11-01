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
// Created by WangYunlai on 2022/6/27.
//

#pragma once

#include "sql/operator/operator.h"
#include "sql/parser/parse_defs.h"
#include "util/util.h"

class FilterUnit;

/**
 * PredicateOperator 用于单个表中的记录过滤
 * 如果是多个表数据过滤，比如join条件的过滤，需要设计新的predicate或者扩展:w
 */
class PredicateOperator : public Operator
{
public:

  PredicateOperator(std::vector<FilterUnit *> &filter_units, bool is_and = true)
    : filter_units_(filter_units), is_and_(is_and)
  {}

  PredicateOperator(const char *table_name, std::vector<FilterUnit *> &filter_units, std::vector<FilterUnit *> &sub_query_units, bool is_and = true)
    : filter_units_(filter_units), sub_query_units_(sub_query_units), table_name_(table_name), is_and_(is_and)
  {}

  virtual ~PredicateOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  Value get_result(Field field) override {
    Value value;
    if (tuple_set_.size() == 0) {
      value_init_null(&value);
      value.type = AttrType::SETS;
      return value;
    }

    // if (tuple_set_.size() == 1) {
    //   TupleCell cell;
    //   tuple_set_[0].find_cell(field, cell);
    //   value_init_from_cell(cell, &value);
    //   return value;
    // }

    Value values[tuple_set_.size()];
    for (size_t i=0; i<tuple_set_.size(); i++) {
      TupleCell cell;
      tuple_set_[i].find_cell(field, cell);
      value_init_from_cell(cell, &values[i]);
    }
    value_init_set(&value, values, 0, tuple_set_.size());
    return value;
  }

  Tuple * current_tuple() override;
  //int tuple_cell_num() const override;
  //RC tuple_cell_spec_at(int index, TupleCellSpec &spec) const override;
private:
  bool do_predicate(RowTuple &tuple);

  RC modify_sub_query_units(Tuple *tuple);

private:
  std::vector<FilterUnit *> filter_units_;
  std::vector<RowTuple> tuple_set_;
  // 需要修改子查询中的FilterUnit
  std::vector<FilterUnit *> sub_query_units_;
  // 用来找到FilterUnit中对应的Expression
  const char *table_name_;
  bool is_left_ = false;
  bool is_right_ = false;
  Field left_field_;
  Field right_field_;
  bool is_and_ = true;
};
