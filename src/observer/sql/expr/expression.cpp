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
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/tuple.h"


RC FieldExpr::get_value(const Tuple &tuple, TupleCell &cell) const
{
  if (tuple.type() == TupleType::CUSTOMIZE) {
    CustomizeTuple *c_tuple = (CustomizeTuple *)(&tuple); 
    return c_tuple->find_cell(field_, cell, agg_func_);
  }
  if (func_ != NONE_ && func_ == LENGTH) {
    TupleCell tmp_cell;
    RC rc = tuple.find_cell(field_, tmp_cell);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    if (tmp_cell.attr_type() != CHARS) {
      return RC::INVALID_ARGUMENT;
    }
    cell.set_type(CHARS);
    const char *len = int2string(strlen(tmp_cell.data())).c_str();
    cell.set_data(len);
    return RC::SUCCESS;
    // cell.set_length(strlen(len));
  } else if (func_ != NONE_ && func_ != LENGTH) {
    return RC::INVALID_ARGUMENT;
  }
  return tuple.find_cell(field_, cell);
}

RC ValueExpr::get_value(const Tuple &tuple, TupleCell &cell) const
{
  cell = tuple_cell_;
  return RC::SUCCESS;
}


RC TreeExpr::get_value(const Tuple &tuple, TupleCell &cell) const 
{
  // 获取左右两边的TupleCell
  TupleCell left_cell;
  TupleCell right_cell;
  // 因为SUB exp的情况，左子节点可能为空
  if (left_ != nullptr) {
    left_->get_value(tuple, left_cell);
  }
  right_->get_value(tuple, right_cell);

  // 重载TupleCell的运算符
  switch (expr_type_)
  {
  case ADD: {
    cell = left_cell + right_cell;
  } break;
  case SUB: {
    if (left_ != nullptr) {
      cell = left_cell - right_cell;
    } else {
      int zero = 0;
      TupleCell zero_cell(FLOATS, (char *)&zero);
      cell = zero_cell - right_cell;
    }
  } break;
  case MUL: {
    cell = left_cell * right_cell;
  } break;
  case DIV: {
    cell = left_cell / right_cell;
  } break;
  default: {
    cell = left_cell;
  } break;
  }
  return RC::SUCCESS;
}