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

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/operator/project_operator.h"
#include "storage/record/record.h"
#include "storage/common/table.h"

RC ProjectOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("project operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ProjectOperator::next()
{
  RC rc = children_[0]->next();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  Tuple *tuple = children_[0]->current_tuple();
  std::stringstream key_ss;
  for (auto group_field : group_fields_) {
    TupleCell cell; 
    tuple->find_cell(group_field, cell);
    // 同一字段类型一定相同，除了NULL_
    key_ss << group_field.table_name() << " " 
      << group_field.field_name() << " ";
    if (cell.attr_type() != NULL_) {
      key_ss << cell.data() << " ";
    } else {
      // 如果数值为NULL就先放进去一个NULL
      key_ss << "NULL_ ";
    }
  }
  if (tuple->type() == TupleType::ROW) {
    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record *new_record = new Record(row_tuple->record());
    row_tuple->set_record(new_record);
    group_tuples_[key_ss.str()].emplace_back(std::make_shared<RowTuple>(*row_tuple));
  } else if (tuple->type() == TupleType::COMPOSITE) {
    CompositeTuple *comp_tuple = static_cast<CompositeTuple *>(tuple);
    group_tuples_[key_ss.str()].emplace_back(std::make_shared<CompositeTuple>(*comp_tuple));
  }
  return rc;
}

RC ProjectOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}
Tuple *ProjectOperator::current_tuple()
{
  tuple_.set_tuple(children_[0]->current_tuple());
  return &tuple_;
}

void ProjectOperator::add_projection(const Table *table, const Field *field)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(new FieldExpr(table, field->meta()));
  // alias: 如果field_meta没有别名，才会使用field_meta->name()
  // 只有当列的别名为空时，才会设置表名
  if (common::is_blank(field->alias())) {
    // alias: 如果table没有别名，才会使用table->name()
    // 因为别名只在一次查询中有效，因此，添加完毕spec之后，清空table的别名，清空fileld_meta的别名
    // 在子查询中，后面也会调用该方法能够对其别名进行清空
    if (common::is_blank(field->table_name_alias())) {
      spec->set_table_name(table->name());
    } else {
      spec->set_table_name(field->table_name_alias());
    }
    spec->set_alias(field->meta()->name());
  } else {
    // 如果列别名为空，不添加table的名称
    spec->set_alias(field->alias());
  }
  tuple_.add_cell_spec(spec);
}

RC ProjectOperator::tuple_cell_spec_at(int index, const TupleCellSpec *&spec) const
{
  return tuple_.cell_spec_at(index, spec);
}
