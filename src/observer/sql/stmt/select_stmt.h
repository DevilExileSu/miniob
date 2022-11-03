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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>
#include <unordered_map>
#include "rc.h"
#include "sql/stmt/stmt.h"
#include "storage/common/field.h"
#include "sql/expr/expression.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

typedef struct {
  Stmt *select;
  bool is_left_value;
  bool has_joint;
  Table *joint_table;
} SubSelectStmt;

class SelectStmt : public Stmt
{
public:

  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }
public:
  static RC create(Db *db, const Selects &select_sql, Stmt *&stmt);
  static RC create_sub_select(Db *db, std::unordered_map<std::string, Table *> &table_map, const Selects &select_sql, Stmt *&stmt, bool &has_joint, Table *&joint_table, std::unordered_map<std::string, std::string> &alias2table);
  static RC create_sub_select(Db *db, std::unordered_map<std::string, Table *> &table_map, const Selects &select_sql, Stmt *&stmt);

public:
  const std::vector<Table *> &tables() const { return tables_; }
  std::vector<Field> &query_fields() { return query_fields_; }
  std::vector<RelAttr> &rel_attrs() { return rel_attrs_; }
  // const std::vector<SelectStmt *> &sub_select_stmts() const { return select_stmts_; }
  const std::vector<SubSelectStmt> &sub_select_stmts() const { return sub_select_stmts_; }
  FilterStmt *filter_stmt() const { return filter_stmt_; }
  bool is_agg() { return !rel_attrs_.empty(); }
  bool is_single_field(){ return query_fields_.size() == 1; }
  bool is_and() { return is_and_; }

  std::vector<std::pair<bool, int>> &fields_or_expr()  { return fields_or_expr_; }
  std::vector<TreeExpr *> &query_expr() { return query_expr_; }
  

private:
  std::vector<Field> query_fields_;
  std::vector<Table *> tables_;
  std::vector<RelAttr> rel_attrs_;
  FilterStmt *filter_stmt_ = nullptr;
  std::vector<SubSelectStmt> sub_select_stmts_;
  // true表示存在query_fields_中，false表示存在query_expr_
  std::vector<std::pair<bool, int>> fields_or_expr_;
  std::vector<TreeExpr *> query_expr_;
  bool is_and_ = true;
};