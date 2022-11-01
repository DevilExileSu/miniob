#include "common/log/log.h"
#include "sql/operator/cross_product_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/common/field.h"
#include "util/util.h"

RC CrossProductOperator::open() {
  if (children_.size() != 2) {
    LOG_WARN("cross product operator must has two child");
    return RC::INTERNAL;
  }
  tuple_set_.clear();
  if (!is_sub_query_) { 
    RC rc = children_[1]->open();
    if (rc != SUCCESS) {
      return rc;
    }
    while (RC::SUCCESS == (rc = children_[1]->next())) {
      Tuple *right_tuple = children_[1]->current_tuple();
      buffer_tuple_.emplace_back(right_tuple);
    }
    children_[1]->close();
  }
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

  if (is_sub_query_) {
    return do_sub_query();
  }

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
  
  if (buffer_tuple_.empty()) {
    rc = RC::RECORD_EOF;
    return rc;
  }

  CompositeTuple composite_tuple;
  composite_tuple.add_tuple(left_tuple);
  
  if (right_cursor_ == 0 || right_cursor_ == buffer_tuple_.size()) {
    if (right_cursor_ == buffer_tuple_.size()) {
      right_cursor_ = 0;
      children_[1]->close();
      ++left_cursor_;
      // 左表也已经遍历完毕
      if ((rc = left_oper->next()) != RC::SUCCESS) {
        return rc;
      }
      rc = children_[1]->open();
      if (rc != RC::SUCCESS && rc != RC::RECORD_EOF) {
        return rc;
      }
      composite_tuple.clear_tuple();
      composite_tuple.add_tuple(left_oper->current_tuple());
    } else {
      if ((rc = children_[1]->open()) != RC::SUCCESS) {
        return rc;
      }
    }
  }

  while (RC::SUCCESS == (rc = children_[1]->next())) {
    Tuple *right_tuple = children_[1]->current_tuple();
    ++right_cursor_;

    composite_tuple.add_tuple(right_tuple);
    
    if (do_predicate(composite_tuple)) {
        tuple_ = composite_tuple;
        tuple_set_.push_back(composite_tuple);
        return rc;
    }
    composite_tuple.remove_tuple();
    if (right_cursor_ == buffer_tuple_.size()) {
      right_cursor_ = 0;
      children_[1]->close();
      ++left_cursor_;
      // 左表也已经遍历完毕
      if ((rc = left_oper->next()) != RC::SUCCESS) {
        return rc;
      }
      rc = children_[1]->open();
      if (rc != RC::SUCCESS) {
        return rc;
      }
      composite_tuple.clear_tuple();
      composite_tuple.add_tuple(left_oper->current_tuple());
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

RC CrossProductOperator::do_sub_query() {
  Operator *left_oper = children_[0];
  // 初始化 left_oper的current_tuple
  RC rc = RC::SUCCESS;
  // 在调用left_oper返回结果时，就已经对内层查询中涉及外层查询的 Expression进行了修改
  while ((rc = left_oper->next()) == RC::SUCCESS) {
    Operator *right_oper = children_[1];
    rc = right_oper->open();
    if (rc != RC::SUCCESS && rc != RC::RECORD_EOF) {
      return rc;
    }
    // 等待子查询执行完毕
    while ((rc = right_oper->next()) == RC::SUCCESS) {
    }

    if (rc != RC::RECORD_EOF) {
      return rc;
    }

    CompOp comp = sub_query_unit_->comp();
    bool in_or_exists = (comp == CompOp::IN_OP 
                      || comp == CompOp::NOT_IN_OP 
                      || comp == CompOp::EXISTS_OP 
                      || comp == CompOp::NOT_EXISTS_OP);
    
    // 获取子查询执行结果，修改sub_query_unit_对应的Expression，并进行predicate
    SelectStmt *select_stmt = static_cast<SelectStmt *>(sub_select_.select);
    Value res = right_oper->get_result(select_stmt->query_fields()[0]);

    if (res.type == AttrType::SETS && !in_or_exists) {
      return RC::GENERIC_ERROR;
    }

    Expression *new_expr = new ValueExpr(res);
    Expression *expr = nullptr;
    Expression *field_expr = nullptr;
    if (sub_select_.is_left_value) {
      expr = sub_query_unit_->left();
      field_expr = sub_query_unit_->right();
    } else {
      expr = sub_query_unit_->right();
      field_expr = sub_query_unit_->left();
    }
    if (sub_select_.is_left_value) {
      sub_query_unit_->set_left(new_expr);
    } else {
      sub_query_unit_->set_right(new_expr);
    }
    delete expr;
    Tuple *left_tuple = left_oper->current_tuple();
    CompositeTuple composite_tuple;
    composite_tuple.add_tuple(left_tuple);
    if (do_sub_prdicate(composite_tuple)) {
      tuple_ = composite_tuple;
      tuple_set_.push_back(composite_tuple);
      return RC::SUCCESS;
    }
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
      // filter_result = false;
      filter_result = (0 == compare);
    } break;
    case NOT_IN_OP: {
      filter_result = (0 != compare);
    } break;
    default: {
      LOG_WARN("invalid compare type: %d", comp);
    } break;
    }
    if (!filter_result && is_and_) {
      return false;
    } else if (!filter_result && !is_and_) {
      continue;
    } else if (filter_result && is_and_) {
      continue;
    } else if (filter_result && !is_and_) {
      return true;
    }
  }
  return is_and_;
}


Tuple *CrossProductOperator::current_tuple()
{
  return &tuple_;
}


bool CrossProductOperator::do_sub_prdicate(CompositeTuple &tuple) {
  const FilterUnit *filter_unit = sub_query_unit_;
  Expression *left_expr = filter_unit->left();
  Expression *right_expr = filter_unit->right();
  CompOp comp = filter_unit->comp();
  TupleCell left_cell;
  TupleCell right_cell;
  left_expr->get_value(tuple, left_cell);
  right_expr->get_value(tuple, right_cell);


  const int compare = left_cell.compare(right_cell);
  bool filter_result = false;
  bool has_null = left_cell.attr_type() == AttrType::NULL_ || right_cell.attr_type() == AttrType::NULL_;
  

  switch (comp) {
  case EQUAL_TO: {
    filter_result = (0 == compare && !has_null) ; 
  } break;
  case LESS_EQUAL: {
    filter_result = (compare <= 0 && !has_null); 
  } break;
  case NOT_EQUAL: {
    filter_result = (compare != 0 && !has_null);
  } break;
  case LESS_THAN: {
    filter_result = (compare < 0 && !has_null);
  } break;
  case GREAT_EQUAL: {
    filter_result = (compare >= 0 && !has_null);
  } break;
  case GREAT_THAN: {
    filter_result = (compare > 0 && !has_null);
  } break;
  case LIKE_MATCH: {
    filter_result = (like_match(left_cell.data(), right_cell.data()) && !has_null);
  } break;
  case NOT_LIKE: {
    filter_result = (!like_match(left_cell.data(), right_cell.data()) && !has_null);
  } break;
  case EXISTS_OP:
  case IN_OP: {
    char *left_data = nullptr;
    char *right_data = nullptr;
    int set_len = 0;
    int data_len = 0;
    if (left_cell.attr_type() == AttrType::SETS) {
      right_data = left_cell.raw_data();
      left_data = right_cell.raw_data();
      data_len = right_cell.length();
      set_len = left_cell.length();
    } else if (right_cell.attr_type() == AttrType::SETS){
      right_data = right_cell.raw_data();
      left_data = left_cell.raw_data();
      data_len = left_cell.length();
      set_len = right_cell.length();
    } else {
      filter_result = (compare == 0 && has_null);
      break;
    }
    RC rc = RC::SUCCESS;
    bool has_text = false;
    for (int i=0; i < set_len; i++) {
      Value *value = (Value *)(right_data + i * sizeof(Value));
      if (value->type == AttrType::NULL_) {
        filter_result = false;
        break;
      }
      rc = convert(left_cell.attr_type(), value, has_text);
      if (rc != RC::SUCCESS) {
        filter_result = false;
        break;
      }
      if (0 == memcmp(left_data, value->data, data_len)) {
        filter_result = true;
        break; 
      }
    }
  } break;
  case NOT_EXISTS_OP:
  case NOT_IN_OP: {
    char *left_data = nullptr;
    char *right_data = nullptr;
    int set_len = 0;
    int data_len = 0;
    if (left_cell.attr_type() == AttrType::SETS) {
      right_data = left_cell.raw_data();
      left_data = right_cell.raw_data();
      data_len = right_cell.length();
      set_len = left_cell.length();
    } else if (right_cell.attr_type() == AttrType::SETS){
      right_data = right_cell.raw_data();
      left_data = left_cell.raw_data();
      data_len = left_cell.length();
      set_len = right_cell.length();
    } else {
      filter_result = (compare != 0);
      break;
    }
    RC rc = RC::SUCCESS;
    filter_result = !has_null;
    bool has_text = false;
    for (int i=0; i<set_len; i++) {
      Value *value = (Value *)(right_data + i * sizeof(Value));
      if (value->type == AttrType::NULL_) {
        filter_result = false;
        break;
      }
      rc = convert(left_cell.attr_type(), value, has_text);
      if (rc != RC::SUCCESS) {
        filter_result = false;
        break;
      }
      if (0 == memcmp(left_data, value->data, data_len)) {
        filter_result = false;
        break;
      }
    }
  } break;
  case IS_OP: {
    filter_result = (left_cell.attr_type() == AttrType::NULL_ && right_cell.attr_type() == AttrType::NULL_);
  } break;
  case IS_NOT_OP: {
    filter_result = (left_cell.attr_type() != AttrType::NULL_ || right_cell.attr_type() != AttrType::NULL_);
  } break;
  default: {
    LOG_WARN("invalid compare type: %d", comp);
  } break;
  }

  return filter_result;
}