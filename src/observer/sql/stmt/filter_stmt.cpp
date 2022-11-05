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
#include <stack>

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
  // alias 这里attr.relation_name可能是表的别名
  // tables包含表别名对应的表，并且是距离当前查询层最近的表
  // 如果考虑内外层的关联查询这里需要修改逻辑
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
  //  alias 这里attr.attribute_name可能是列别名，实际题目不考察，就不用处理
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


 RC FilterStmt::expresion_tree_generate(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
                          TreeExpr *&root_expr, Exp *exp, Table *&table, bool &is_multi_table, bool &is_agg,
                          std::vector<RelAttr> *rel_attrs, std::vector<Field> *query_fields) {


  bool has_agg = false;
  bool has_field = false;
  // 实际上，表达式树中 如果 不包含ATTR类型的Exp，可以先计算出来，不用在后面每次进行运算调用
  // 只复制节点类型，这里就是只复制节点类型，标记符号
  TreeExpr *root = new TreeExpr(exp);
  RC rc = RC::SUCCESS;
  std::stack<std::pair<Exp *, Expression *>> exp_stack;
  exp_stack.push(std::make_pair(exp, root));

  while (!exp_stack.empty()) {
    auto cur = exp_stack.top();
    exp_stack.pop();
    // 表明该节点是一个运算符
    TreeExpr *cur_parent = static_cast<TreeExpr *>(cur.second);
    Exp *left_exp = cur.first->left_expr;
    Exp *right_exp = cur.first->right_expr;
    if (left_exp != nullptr) {
      // 是个符号
      if (left_exp->expr_type != NodeType::ATTR && left_exp->expr_type != NodeType::VAL) {
        TreeExpr *left_path = new TreeExpr(left_exp);
        cur_parent->set_left(left_path);
        // 并压入栈中
        exp_stack.push(std::make_pair(left_exp, left_path));
      } else if (left_exp->expr_type == NodeType::VAL){
        // 如果是数值节点
        ValueExpr *left_leaf = new ValueExpr(*left_exp->value);
        cur_parent->set_left(left_leaf);
      } else if (left_exp->expr_type == NodeType::ATTR) {
        // 如果是字段节点
        // 判断是否是聚合函数
        RelAttr *attr = left_exp->attr;
        if (attr->agg_func != AggFunc::NONE) {
          has_agg = true;
          if (0 == strcmp(attr->attribute_name, "*") && attr->agg_func != AggFunc::COUNT) {
            return RC::SCHEMA_FIELD_MISSING;
          }
          if (rel_attrs != nullptr) {
            rel_attrs->emplace_back(*attr);
          }
        } else {
          has_field = true;
        }
        if (has_agg && has_field) {
          return RC::INVALID_ARGUMENT;
        }

        Table *left_table = nullptr;
        const FieldMeta *field = nullptr;
        rc = get_table_and_field(db, default_table, tables, *attr, left_table, field, CompOp::NO_OP);
        if (query_fields != nullptr) {
          query_fields->emplace_back(Field(left_table, field));
        }
        if (rc != RC::SUCCESS) {
          return rc;
        }
        if (table != nullptr && table != left_table) {
          is_multi_table = true;
        } else {
          table = left_table;
        }
        FieldExpr *left_leaf = new FieldExpr(left_table, field, attr->agg_func);
        cur_parent->set_left(left_leaf);
      }
    }

    if (right_exp != nullptr) {
      if (right_exp->expr_type != NodeType::ATTR && right_exp->expr_type != NodeType::VAL) {
        TreeExpr *right_path = new TreeExpr(right_exp);
        cur_parent->set_right(right_path);
        exp_stack.push(std::make_pair(right_exp, right_path));
      } else if (right_exp->expr_type == NodeType::VAL) {
        ValueExpr *right_leaf = new ValueExpr(*right_exp->value);
        cur_parent->set_right(right_leaf);
      } else if (right_exp->expr_type == NodeType::ATTR) {
        Table *right_table = nullptr;
        RelAttr *attr = right_exp->attr;
        if (attr->agg_func != AggFunc::NONE) {
          has_agg = true;
          // 2.1 *只能出现在COUNT中
          if (0 == strcmp(attr->attribute_name, "*") && attr->agg_func != AggFunc::COUNT) {
            return RC::SCHEMA_FIELD_MISSING;
          }
          if (rel_attrs != nullptr) {
            rel_attrs->emplace_back(*attr);
          }
        } else {
          has_field = true;
        }
        if (has_agg && has_field) {
          return RC::INVALID_ARGUMENT;
        }
        const FieldMeta *field = nullptr;
        rc = get_table_and_field(db, default_table, tables, *attr, right_table, field, CompOp::NO_OP);
        if (query_fields != nullptr) {
          query_fields->emplace_back(Field(right_table, field));
        }
        if (rc != RC::SUCCESS) {
          return rc;
        }
        if (table != nullptr && table != right_table) {
          is_multi_table = true;
        } else {
          table = right_table;
        }
        FieldExpr *right_leaf = new FieldExpr(right_table, field, attr->agg_func);
        cur_parent->set_right(right_leaf);
      }
    }
  }
  is_agg = has_agg;
  root_expr = root;
  return rc;
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
  Value *left_condition_value = nullptr;
  Value *right_condition_value = nullptr;
  FieldMeta *condition_field = nullptr;
  Table *left_table = nullptr;
  Table *right_table = nullptr;
  bool is_multi_table = false;


  if (condition.left_is_attr == 1 || comp == CompOp::EXISTS_OP || comp == CompOp::NOT_EXISTS_OP) {
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.left_attr, left_table, field, comp);  
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FieldExpr *field_expr = new FieldExpr(left_table, field);
    field_expr->set_func(condition.left_attr.func);
    left = field_expr;
    condition_field = const_cast<FieldMeta *>(field);
  } else if (condition.left_is_attr == 0){
    left_condition_value = const_cast<Value *>(&condition.left_value);
    condition_value = const_cast<Value *>(&condition.left_value);
    left = new ValueExpr(condition.left_value);
  } else {
    TreeExpr *root_expr = nullptr;
    bool is_agg = false;
    rc = expresion_tree_generate(db, default_table, tables, root_expr, condition.left_expr, left_table, is_multi_table, is_agg);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    left = root_expr;
  }

  if (condition.right_is_attr == 1) {
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.right_attr, right_table, field, comp);  
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      delete left;
      return rc;
    }
    FieldExpr *field_expr = new FieldExpr(right_table, field);
    field_expr->set_func(condition.right_attr.func);
    right = field_expr;
    condition_field = const_cast<FieldMeta *>(field);
  } else if (condition.right_is_attr == 0) {
    right_condition_value = const_cast<Value *>(&condition.right_value);
    condition_value = const_cast<Value *>(&condition.right_value);
    right = new ValueExpr(condition.right_value);
  } else {
    TreeExpr *root_expr = nullptr;
    bool is_agg = false;
    rc = expresion_tree_generate(db, default_table, tables, root_expr, condition.right_expr, right_table, is_multi_table, is_agg);
    if (rc != RC::SUCCESS) {
      delete left;
      return rc;
    }
    right = root_expr;
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

  bool is_sub_select_units = false;
  if (left_condition_value != nullptr && left_condition_value->type == AttrType::SELECTS) {
    tmp_stmt->sub_select_units_.emplace_back(filter_unit);
    is_sub_select_units = true;
  }

  if (right_condition_value != nullptr && right_condition_value->type == AttrType::SELECTS) {
    tmp_stmt->sub_select_units_.emplace_back(filter_unit);
    is_sub_select_units = true;
  }
  
  if (is_sub_select_units) {
    return rc;
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

  // 判断是否为多表过滤条件
  if (left_table != nullptr && right_table != nullptr) {
    // 左右使用两个表相同，并且is_multi_table = false
    if (left_table == right_table && !is_multi_table) {
      std::string table_name = std::string(left_table->name());
      add_filter_unit(table_name);
    } else {
      tmp_stmt->filter_units_.emplace_back(filter_unit);
    }
  } else if (left_table != nullptr && !is_multi_table) {
    std::string table_name = std::string(left_table->name());
    add_filter_unit(table_name);
  } else if (right_table != nullptr && !is_multi_table) {
    std::string table_name = std::string(right_table->name());
    add_filter_unit(table_name);
  } else if (!is_multi_table){
    std::string table_name = std::string(default_table->name());
    add_filter_unit(table_name);
  } else if (is_multi_table) {
    tmp_stmt->filter_units_.emplace_back(filter_unit);
  }

  return rc;
}

