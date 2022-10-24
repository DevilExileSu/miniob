#include "common/log/log.h"
#include "sql/operator/cross_product_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/field.h"
#include "util/util.h"

RC CrossProductOperator::open() {
  if (children_.size() != 2) {
    LOG_WARN("cross product operator must has two child");
    return RC::INTERNAL;
  }
  RC rc = children_[1]->open();
  while (RC::SUCCESS == (rc = children_[1]->next())) {
    Tuple *right_tuple = children_[1]->current_tuple();
    if (right_table_name_ == nullptr) {
      RowTuple *row_tuple = static_cast<RowTuple *>(right_tuple);
      right_table_name_ = row_tuple->table_name();
    }
    buffer_tuple_.emplace_back(right_tuple);
  }

  children_[1]->close();
  return children_[0]->open();
}

RC CrossProductOperator::close()
{
  for(int i=0; i<children_.size(); i++) {
    children_[i]->close();
  }
  return RC::SUCCESS;
}

RC CrossProductOperator::next()
{
  RC rc = RC::SUCCESS;
  Operator *left_oper = children_[0];
  // 初始化 left_oper的current_tuple
  if (left_cursor_ == 0) {
    if ((rc = left_oper->next()) != RC::SUCCESS) {
      return rc;
    }
    ++left_cursor_;
  }

  Tuple *left_tuple = left_oper->current_tuple();
  if (nullptr == left_tuple) {
    rc = RC::INTERNAL;
    LOG_WARN("failed to get tuple from operator");
    return rc;
  }

  // 右表为空
  if (buffer_tuple_.empty()) {
    rc = RC::INTERNAL;
    return rc;
  }

  CompositeTuple composite_tuple;
  composite_tuple.set_tuple(left_tuple);


  if (right_cursor_ == 0 || right_cursor_ == buffer_tuple_.size()) {
    if (right_cursor_ == buffer_tuple_.size()) {
      right_cursor_ = 0;
      children_[1]->close();
      ++left_cursor_;
      // 左表也已经遍历完毕
      if ((rc = left_oper->next()) != RC::SUCCESS) {
        return rc;
      }
      children_[1]->open();
      composite_tuple.clear_tuple();
      composite_tuple.set_tuple(left_oper->current_tuple());
    } else {
      if ((rc = children_[1]->open()) != RC::SUCCESS) {
        return rc;
      }
    }
  }

  while (RC::SUCCESS == (rc = children_[1]->next())) {
    Tuple *right_tuple = children_[1]->current_tuple();
    ++right_cursor_;
    composite_tuple.add_tuple(right_table_name_, right_tuple);

    if (do_predicate(composite_tuple)) {
        tuple_ = composite_tuple;
        return rc;
    }

    if (right_cursor_ == buffer_tuple_.size()) {
      right_cursor_ = 0;
      children_[1]->close();
      ++left_cursor_;
      // 左表也已经遍历完毕
      if ((rc = left_oper->next()) != RC::SUCCESS) {
        return rc;
      }
      children_[1]->open();
      composite_tuple.clear_tuple();
      composite_tuple.set_tuple(left_oper->current_tuple());
    }
  }


  // 暂时不能使用缓存
  // while (right_cursor_ < buffer_tuple_.size()) {
  //   // 确保right_tuple一定是RowTuple
  //   Tuple *right_tuple = buffer_tuple_[right_cursor_];
  //   ++right_cursor_;
  //   composite_tuple.add_tuple(right_table_name_, right_tuple);

  //   if (do_predicate(composite_tuple)) {
  //       tuple_ = composite_tuple;
  //       return rc;
  //   }

  //   // 如果没有满足条件的，但是此时右表遍历完毕
  //   if (right_cursor_ == buffer_tuple_.size()) {
  //     right_cursor_ = 0;
  //     ++left_cursor_;
  //     // 左表也已经遍历完毕
  //     if ((rc = left_oper->next()) != RC::SUCCESS) {
  //       return rc;
  //     }
  //     composite_tuple.clear_tuple();
  //     composite_tuple.set_tuple(left_oper->current_tuple());
  //   }
  // }

  // 右表遍历完毕，初始化cursor
  right_cursor_ = 0; 
  children_[1]->close();
  // 左边也已经遍历完毕
  if ((rc = left_oper->next()) != RC::SUCCESS) {
    return rc;
  }
  return rc;
}

bool CrossProductOperator::do_predicate(CompositeTuple &tuple)
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

    RC left_rc = left_expr->get_value(tuple, left_cell);
    RC right_rc = right_expr->get_value(tuple, right_cell);

    // 表明该过滤条件中包含左、右Operator中不存在的table，直接跳过
    if (left_rc != RC::SUCCESS || right_rc != RC::SUCCESS) {
        continue;
    }

    const int compare = left_cell.compare(right_cell);
    bool filter_result = false;

    switch (comp) {
    case EQUAL_TO: {
      filter_result = (0 == compare); 
    } break;
    case LESS_EQUAL: {
      filter_result = (compare <= 0); 
    } break;
    case NOT_EQUAL: {
      filter_result = (compare != 0);
    } break;
    case LESS_THAN: {
      filter_result = (compare < 0);
    } break;
    case GREAT_EQUAL: {
      filter_result = (compare >= 0);
    } break;
    case GREAT_THAN: {
      filter_result = (compare > 0);
    } break;
    case LIKE_MATCH: {
      filter_result = like_match(left_cell.data(), right_cell.data());
    } break;
    case NOT_LIKE: {
      filter_result = !like_match(left_cell.data(), right_cell.data());
    } break;
    case IN_OP: {
      filter_result = false;
    } break;
    case NOT_IN_OP: {
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


Tuple *CrossProductOperator::current_tuple()
{
  return &tuple_;
}