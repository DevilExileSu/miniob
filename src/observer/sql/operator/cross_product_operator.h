#pragma once

#include "sql/operator/operator.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/parser/parse_defs.h"

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
    Value values[tuple_set_.size()];
    bool has_null = false; 
    for (size_t i=0; i<tuple_set_.size(); i++) {
      TupleCell cell;
      tuple_set_[i].find_cell(field, cell);
      values[i].data = (TupleCell *)malloc(sizeof(TupleCell));
      if (cell.attr_type() == AttrType::NULL_) {
        has_null = true;
      }
      values[i].type = cell.attr_type();
      memcpy(values[i].data, &cell, sizeof(TupleCell));
    }
    value_init_set(&value, values, 0, tuple_set_.size());
    if (has_null) {
      value.type = AttrType::NULL_;
    } else {
      value.type = AttrType::TUPLESET;
    }
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
