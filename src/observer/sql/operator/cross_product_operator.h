#pragma once

#include "sql/operator/operator.h"
#include "sql/stmt/filter_stmt.h"

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

private:
  bool do_predicate(CompositeTuple &tuple);
private:
  const std::vector<FilterUnit *> filter_units_;
  std::vector<Tuple *> buffer_tuple_;
  CompositeTuple tuple_;
  const char *right_table_name_ = nullptr;
  int right_cursor_ = 0;        // 记录上次遍历到的buffer_tuple_的游标
  int left_cursor_ = 0;
};
