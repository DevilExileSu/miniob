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

#pragma once

#include <string.h>
#include "storage/common/field.h"
#include "sql/parser/parse_defs.h"
#include "sql/expr/tuple_cell.h"
#include "util/util.h"

class Tuple;

enum class ExprType {
  NONE,
  FIELD,
  VALUE,
  TREE,
};

class Expression
{
public: 
  Expression() = default;
  virtual ~Expression() = default;
  
  virtual RC get_value(const Tuple &tuple, TupleCell &cell) const = 0;
  virtual ExprType type() const = 0;
};

// 需要对聚合进行额外的处理
// 如果是对字段进行聚合处理
// 需要获取tuple中对应的AggFunc结果
class FieldExpr : public Expression
{
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field)
  {}
  FieldExpr(const Table *table, const FieldMeta *field, AggFunc agg_func) : field_(table, field), agg_func_(agg_func)
  {}
  virtual ~FieldExpr() = default;

  ExprType type() const override
  {
    return ExprType::FIELD;
  }

  Field &field()
  {
    return field_;
  }

  const Field &field() const
  {
    return field_;
  }

  const char *table_name() const
  {
    return field_.table_name();
  }

  const char *field_name() const
  {
    return field_.field_name();
  }

  const AggFunc agg_func() const {
    return agg_func_;
  }
  
  const Func func() const {
    return func_;
  }
  
  void set_func(Func func) {
    func_ = func;
  }
  void set_acc(int acc) {
    acc_ = acc;
  }
  
  RC get_value(const Tuple &tuple, TupleCell &cell) const override;
private:
  Field field_;
  AggFunc agg_func_ = AggFunc::NONE;
  Func func_ = Func::NONE_;
  int acc_ = 0;
};

class ValueExpr : public Expression
{
public:
  ValueExpr() = default;
  ValueExpr(TupleCell &&cell): tuple_cell_(cell) 
  {}
  ValueExpr(const Value &value) : tuple_cell_(value.type, (char *)value.data)
  {
    if (value.type == CHARS) {
      tuple_cell_.set_length(strlen((const char *)value.data));
    }
    if (value.type == SETS || value.type == TUPLESET) {
      tuple_cell_.set_length(value.set_size);
    }
  }

  virtual ~ValueExpr() = default;

  RC get_value(const Tuple &tuple, TupleCell &cell) const override;
  ExprType type() const override
  {
    return ExprType::VALUE;
  }

  void get_tuple_cell(TupleCell &cell) const {
    cell = tuple_cell_;
  }

private:
  TupleCell tuple_cell_;
};



// 除了叶子节点只存储运算符，叶子节点存放FieldExpr或ValueExpr
class TreeExpr : public Expression
{
public:
  TreeExpr() = default;
  TreeExpr(Exp *exp) {
    expr_type_ = exp->expr_type;
    lbrace_ = exp->lbrace;
    rbrace_ = exp->rbrace;
  }

  virtual  ~TreeExpr() = default;

  ExprType type() const override 
  {
    return ExprType::TREE;
  }

  RC get_value(const Tuple &tuple, TupleCell &cell) const override;

  void set_left(Expression *left) {
    left_ = left;
  }

  void set_right(Expression *right) {
    right_ = right;
  }

  // 后序遍历输出原表达式
  void to_string(std::ostream &os, bool is_multi_table) {
    for (int i=0; i<lbrace_; i++) {
      os << '(';
    }
    // 不考虑别名
    if (left_ != nullptr && left_->type() == ExprType::FIELD) {
      FieldExpr *field = static_cast<FieldExpr *>(left_);
      switch (field->agg_func()) {
      case MAX: {
        os << "max(";
      } break;
      case MIN: {
        os << "min(";
      } break;
      case AVG: {
        os << "avg(";
      } break;
      case COUNT: {
        os << "count(" ;
      } break; 
      case SUM: { 
        os<< "sum(";
      } break; 
      default:
        break;
      }
      if (is_multi_table) {
        os << field->table_name() << '.';
      }
      os << field->field_name();
      if (field->agg_func() != AggFunc::NONE) {
        os << ')';
      }
    } else if (left_ != nullptr && left_->type() == ExprType::VALUE) {
      ValueExpr *value = static_cast<ValueExpr *>(left_);
      TupleCell cell;
      value->get_tuple_cell(cell);
      cell.to_string(os);
    } else if (left_ != nullptr){
      TreeExpr *tree = static_cast<TreeExpr *>(left_);
      tree->to_string(os, is_multi_table);
    }

    switch (expr_type_)
    {
    case ADD: {
      os << '+';
    } break;
    case SUB: {
      os << '-';
    } break;
    case DIV: {
      os << '/';
    } break;
    case MUL: {
      os << "*";
    }
    default:
      break;
    }

    if (right_->type() == ExprType::FIELD) {

      FieldExpr *field = static_cast<FieldExpr *>(right_);
      switch (field->agg_func()) {
      case MAX: {
        os << "max(";
      } break;
      case MIN: {
        os << "min(";
      } break;
      case AVG: {
        os << "avg(";
      } break;
      case COUNT: {
        os << "count(" ;
      } break; 
      case SUM: { 
        os<< "sum(";
      } break; 
      default:
        break;
      }
      if (is_multi_table) {
        os << field->table_name() << '.';
      }
      os << field->field_name();
      if (field->agg_func() != AggFunc::NONE) {
        os << ')';
      }
    } else if (right_->type() == ExprType::VALUE) {
      ValueExpr *value = static_cast<ValueExpr *>(right_);
      TupleCell cell;
      value->get_tuple_cell(cell);
      cell.to_string(os);
    } else {
      TreeExpr *tree = static_cast<TreeExpr *>(right_);
      tree->to_string(os, is_multi_table);
    }
    
    for (int i=0; i<rbrace_; i++) {
      os << ')';
    }
  }

private:
  Expression *left_ = nullptr;
  Expression *right_ = nullptr;
  int lbrace_ = 0;
  int rbrace_ = 0;
  NodeType expr_type_;
};
