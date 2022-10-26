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

#include "common/log/log.h"
#include "sql/operator/predicate_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/field.h"
#include "util/util.h"

RC PredicateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open();
}

RC PredicateOperator::next()
{
  RC rc = RC::SUCCESS;
  Operator *oper = children_[0];
  
  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    if (do_predicate(static_cast<RowTuple &>(*tuple))) {
      return rc;
    }
  }
  return rc;
}

RC PredicateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple * PredicateOperator::current_tuple()
{
  return children_[0]->current_tuple();
}

bool PredicateOperator::do_predicate(RowTuple &tuple)
{
  if (filter_units_.empty()) {
    return true;
  }
  
  for (const FilterUnit *filter_unit : filter_units_) {
    Expression *left_expr = filter_unit->left();
    Expression *right_expr = filter_unit->right();
    CompOp comp = filter_unit->comp();
    TupleCell left_cell;
    TupleCell right_cell;
    left_expr->get_value(tuple, left_cell);
    right_expr->get_value(tuple, right_cell);

    const int compare = left_cell.compare(right_cell);
    bool filter_result = false;
    bool has_null = left_cell.attr_type() == AttrType::NULL_ || right_cell.attr_type() == AttrType::NULL_;
    switch (comp) {
    case EQUAL_TO: {
      filter_result = (0 == compare && !has_null) ; 
    } break;
    case LESS_EQUAL: {
      filter_result = (compare <= 0 && !has_null); 
    } break;
    case NOT_EQUAL: {
      filter_result = (compare != 0 && !has_null);
    } break;
    case LESS_THAN: {
      filter_result = (compare < 0 && !has_null);
    } break;
    case GREAT_EQUAL: {
      filter_result = (compare >= 0 && !has_null);
    } break;
    case GREAT_THAN: {
      filter_result = (compare > 0 && !has_null);
    } break;
    case LIKE_MATCH: {
      filter_result = (like_match(left_cell.data(), right_cell.data()) && !has_null);
    } break;
    case NOT_LIKE: {
      filter_result = (!like_match(left_cell.data(), right_cell.data()) && !has_null);
    } break;
    case IN_OP: {
      filter_result = false;
    } break;
    case NOT_IN_OP: {
      filter_result = false;
    } break;
    case IS_OP: {
      filter_result = (left_cell.attr_type() == AttrType::NULL_ && right_cell.attr_type() == AttrType::NULL_);
    } break;
    case IS_NOT_OP: {
      filter_result = (left_cell.attr_type() != AttrType::NULL_ || right_cell.attr_type() != AttrType::NULL_);
    } break;
    case EXISTS_OP: {
      filter_result = false;
    } break;
    case NOT_EXISTS_OP: {
      filter_result = false;
    } break;
    default: {
      LOG_WARN("invalid compare type: %d", comp);
    } break;
    }
    if (!filter_result) {
      return false;
    }
  }
  return true;
}

// int PredicateOperator::tuple_cell_num() const
// {
//   return children_[0]->tuple_cell_num();
// }
// RC PredicateOperator::tuple_cell_spec_at(int index, TupleCellSpec &spec) const
// {
//   return children_[0]->tuple_cell_spec_at(index, spec);
// }
