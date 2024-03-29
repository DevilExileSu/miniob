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
// Created by WangYunlai on 2022/07/01.
//

#pragma once

#include "sql/operator/operator.h"
#include "sql/parser/parse_defs.h"
#include "rc.h"

class ProjectOperator : public Operator
{
public:
  ProjectOperator()
  {}
  
  ProjectOperator(std::vector<Field> &group_fields) : group_fields_(group_fields)
  {}

  virtual ~ProjectOperator() = default;

  void add_projection(const Table *table, const Field *field);

  RC open() override;
  RC next() override;
  RC close() override;

  int tuple_cell_num() const
  {
    return tuple_.cell_num();
  }

  Operator *get_child() {
    return children_[0];
  }
  Value get_result(Field field) override{
    return children_[0]->get_result(field);
  }
  OperatorType type() override {
    return OperatorType::OTHER;
  }
  RC tuple_cell_spec_at(int index, const TupleCellSpec *&spec) const;
  std::unordered_map<std::string, std::vector<std::shared_ptr<Tuple>>> &group_tuples() {
    return group_tuples_;
  }
  Tuple * current_tuple() override;

private:
  ProjectTuple tuple_;
    // 处理group by
  std::unordered_map<std::string, std::vector<std::shared_ptr<Tuple>>> group_tuples_;
  std::vector<Field> group_fields_;
};
