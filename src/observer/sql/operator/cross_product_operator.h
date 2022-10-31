#pragma once

#include "sql/operator/operator.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/parser/parse_defs.h"
#include "util/util.h"

class FilterUnit;

class CrossProductOperator : public Operator
{
public:
  CrossProductOperator(const std::vector<FilterUnit *> &filter_units)
    : filter_units_(filter_units)
  {}

  virtual ~CrossProductOperator() = default;
  RC open() override;
  RC next() override;
  RC close() override;

  // 这里的current_tuple是一个CompositeTuple
  Tuple * current_tuple() override;

  Value get_result(Field field) override {
    Value value;
    if (tuple_set_.size() == 0) {
      value_init_null(&value);
      return value;
    }

    if (tuple_set_.size() == 1) {
      TupleCell cell;
      tuple_set_[0].find_cell(field, cell);
      value_init_from_cell(cell, &value);
      return value;
    }

    Value values[tuple_set_.size()];
    for (size_t i=0; i<tuple_set_.size(); i++) {
      TupleCell cell;
      tuple_set_[i].find_cell(field, cell);
      value_init_from_cell(cell, &values[i]);
    }
    value_init_set(&value, values, 0, tuple_set_.size());
    return value;
  }

private:
  bool do_predicate(CompositeTuple &tuple);
private:
  const std::vector<FilterUnit *> filter_units_;
  std::vector<Tuple *> buffer_tuple_;
  std::vector<CompositeTuple> tuple_set_;
  CompositeTuple tuple_;
  int right_cursor_ = 0;        // 记录上次遍历到的buffer_tuple_的游标
  int left_cursor_ = 0;
};
