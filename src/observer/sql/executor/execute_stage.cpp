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
// Created by Meiyi & Longda on 2021/4/13.
//

#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <algorithm>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/lang/defer.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "sql/expr/tuple.h"
#include "sql/operator/table_scan_operator.h"
#include "sql/operator/index_scan_operator.h"
#include "sql/operator/predicate_operator.h"
#include "sql/operator/delete_operator.h"
#include "sql/operator/update_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/operator/cross_product_operator.h"
#include "sql/operator/aggregate_operator.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/table.h"
#include "storage/common/field.h"
#include "storage/index/index.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"
#include "storage/clog/clog.h"

using namespace common;

// RC create_selection_executor(
//    Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag)
{}

//! Destructor
ExecuteStage::~ExecuteStage()
{}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag)
{
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties()
{
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize()
{
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup()
{
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event)
{
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context)
{
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event)
{
  SQLStageEvent *sql_event = static_cast<SQLStageEvent *>(event);
  SessionEvent *session_event = sql_event->session_event();
  Stmt *stmt = sql_event->stmt();
  Session *session = session_event->session();
  Query *sql = sql_event->query();

  if (stmt != nullptr) {
    switch (stmt->type()) {
      case StmtType::SELECT: {
        do_select(sql_event);
      } break;
      case StmtType::INSERT: {
        do_insert(sql_event);
      } break;
      case StmtType::UPDATE: {
        do_update(sql_event);
      } break;
      case StmtType::DELETE: {
        do_delete(sql_event);
      } break;
      default: {
        LOG_WARN("should not happen. please implenment");
      } break;
    }
  } else {
    switch (sql->flag) {
    case SCF_HELP: {
      do_help(sql_event);
    } break;
    case SCF_CREATE_TABLE: {
      do_create_table(sql_event);
    } break;
    case SCF_CREATE_INDEX: {
      do_create_index(sql_event);
    } break;
    case SCF_SHOW_TABLES: {
      do_show_tables(sql_event);
    } break;
    case SCF_DESC_TABLE: {
      do_desc_table(sql_event);
    } break;

    case SCF_DROP_TABLE: {
      do_drop_table(sql_event);
    } break; 
    
    case SCF_DROP_INDEX: {
      // do nothing
      const char *response = "Unsupported\n";
      session_event->set_response(response);
    } break;
    case SCF_SHOW_INDEX: {
      do_show_index(sql_event);
    } break; 
    case SCF_LOAD_DATA: {
      default_storage_stage_->handle_event(event);
    } break;
    case SCF_SYNC: {
      /*
      RC rc = DefaultHandler::get_default().sync();
      session_event->set_response(strrc(rc));
      */
    } break;
    case SCF_BEGIN: {
      do_begin(sql_event);
      /*
      session_event->set_response("SUCCESS\n");
      */
    } break;
    case SCF_COMMIT: {
      do_commit(sql_event);
      /*
      Trx *trx = session->current_trx();
      RC rc = trx->commit();
      session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      */
    } break;
    case SCF_CLOG_SYNC: {
      do_clog_sync(sql_event);
    }
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
    } break;
    case SCF_EXIT: {
      // do nothing
      const char *response = "Unsupported\n";
      session_event->set_response(response);
    } break;
    default: {
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right)
{
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

void print_tuple_header(std::ostream &os, const ProjectOperator &oper, bool is_multi_table, 
                        std::vector<TreeExpr *> &query_expr, std::vector<std::pair<int, int>> &fields_or_expr)
{
  // const int cell_num = oper.tuple_cell_num();
  const TupleCellSpec *cell_spec = nullptr;
  for (size_t i=0; i < fields_or_expr.size(); i++) {
    if (i != 0) {
      os << " | ";
    }
    if (fields_or_expr[i].first == 0) {
      oper.tuple_cell_spec_at(fields_or_expr[i].second, cell_spec);
      if (is_multi_table && cell_spec->table_name()) {
        os << cell_spec->table_name() << ".";
      }
      if (cell_spec->alias()) {
        os << cell_spec->alias();
      }
    } else if (fields_or_expr[i].first == 1){
      query_expr[fields_or_expr[i].second]->to_string(os, is_multi_table);
    }
  }
  if (fields_or_expr.size() > 0) {
    os << '\n';
  }
}

void tuple_to_string(std::ostream &os, const Tuple &tuple, std::vector<TreeExpr *> &query_expr, std::vector<std::pair<int, int>> &fields_or_expr)
{
  TupleCell cell;
  RC rc = RC::SUCCESS;
  bool first_field = true;

  for (size_t i=0; i < fields_or_expr.size(); i++) {
    if (!first_field) {
      os << " | ";
    } else {
      first_field = false;
    }
    if (fields_or_expr[i].first == 0) {
      rc = tuple.cell_at(fields_or_expr[i].second, cell);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to fetch field of cell. index=%d, rc=%s", i, strrc(rc));
        break;
      }
    } else if (fields_or_expr[i].first == 1){
      rc = query_expr[fields_or_expr[i].second]->get_value(tuple, cell);
      if (rc != RC::SUCCESS) {
        break;
      }
    }
    cell.to_string(os);
  }
}

IndexScanOperator *try_to_create_index_scan_operator(std::vector<FilterUnit *> &filter_units)
{
  // const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  if (filter_units.empty()) {
    return nullptr;
  }

  // 在所有过滤条件中，找到字段与值做比较的条件，然后判断字段是否可以使用索引
  // 如果是多列索引，这里的处理需要更复杂。
  // 这里的查找规则是比较简单的，就是尽量找到使用相等比较的索引
  // 如果没有就找范围比较的，但是直接排除不等比较的索引查询. (你知道为什么?)
  const FilterUnit *better_filter = nullptr;

  for (const FilterUnit *filter_unit : filter_units) {
    if (filter_unit->comp() == NOT_EQUAL) {
      continue;
    }

    Expression *left = filter_unit->left();
    Expression *right = filter_unit->right();
    
    if (left->type() == ExprType::VALUE && right->type() == ExprType::VALUE) {
      return nullptr;
    }

    // 如果含有表达式先不使用索引，但其实可以修改一下，适配表达式？
    if (left->type() == ExprType::TREE || right->type() == ExprType::TREE) {
      return nullptr;
    }
    if (left->type() == ExprType::FIELD && right->type() == ExprType::VALUE) {
    } else if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
      std::swap(left, right);
    }
    FieldExpr &left_field_expr = *(FieldExpr *)left;
    const Field &field = left_field_expr.field();
    const Table *table = field.table();
    Index *index = table->find_index_by_field(field.field_name());
    if (index != nullptr) {
      if (better_filter == nullptr) {
        better_filter = filter_unit;
      } else if (filter_unit->comp() == EQUAL_TO) {
        better_filter = filter_unit;
        break;
      }
    }
  }

  if (better_filter == nullptr) {
    return nullptr;
  }

  Expression *left = better_filter->left();
  Expression *right = better_filter->right();
  CompOp comp = better_filter->comp();
  if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
    std::swap(left, right);
    switch (comp) {
    case EQUAL_TO:    { comp = EQUAL_TO; }    break;
    case LESS_EQUAL:  { comp = GREAT_THAN; }  break;
    case NOT_EQUAL:   { comp = NOT_EQUAL; }   break;
    case LESS_THAN:   { comp = GREAT_EQUAL; } break;
    case GREAT_EQUAL: { comp = LESS_THAN; }   break;
    case GREAT_THAN:  { comp = LESS_EQUAL; }  break;
    case LIKE_MATCH:  { comp = LIKE_MATCH; }  break;
    case NOT_LIKE:    { comp = NOT_LIKE; }    break;
    case IN_OP:          { comp = IN_OP; }          break;
    case NOT_IN_OP:      { comp = NOT_IN_OP; }      break;
    default: {
    	LOG_WARN("should not happen");
    }
    }
  }

  FieldExpr &left_field_expr = *(FieldExpr *)left;
  const Field &field = left_field_expr.field();
  const Table *table = field.table();
  Index *index = table->find_index_by_field(field.field_name());
  assert(index != nullptr);

  ValueExpr &right_value_expr = *(ValueExpr *)right;
  TupleCell value;
  right_value_expr.get_tuple_cell(value);

  const TupleCell *left_cell = nullptr;
  const TupleCell *right_cell = nullptr;
  bool left_inclusive = false;
  bool right_inclusive = false;

  switch (comp) {
  case EQUAL_TO: {
    left_cell = &value;
    right_cell = &value;
    left_inclusive = true;
    right_inclusive = true;
  } break;

  case LESS_EQUAL: {
    left_cell = nullptr;
    left_inclusive = false;
    right_cell = &value;
    right_inclusive = true;
  } break;

  case LESS_THAN: {
    left_cell = nullptr;
    left_inclusive = false;
    right_cell = &value;
    right_inclusive = false;
  } break;

  case GREAT_EQUAL: {
    left_cell = &value;
    left_inclusive = true;
    right_cell = nullptr;
    right_inclusive = false;
  } break;

  case GREAT_THAN: {
    left_cell = &value;
    left_inclusive = false;
    right_cell = nullptr;
    right_inclusive = false;
  } break;
  case LIKE_MATCH: {
    left_cell = &value;
    right_cell = &value;
    left_inclusive = true;
    right_inclusive = true;
  } break;
  case NOT_LIKE: {
    left_cell = &value;
    right_cell = &value;
    left_inclusive = true;
    right_inclusive = true;
  } break;
  case IN_OP: {

  } break;
  case NOT_IN_OP: {

  } break;
  default: {
    LOG_WARN("should not happen. comp=%d", comp);
  } break;
  }

  IndexScanOperator *oper = new IndexScanOperator(table, index,
       left_cell, left_inclusive, right_cell, right_inclusive);

  LOG_INFO("use index for scan: %s in table %s", index->index_meta().name(), table->name());
  return oper;
}

// 子查询先执行完毕后，更新filter_stmt->sub_select_units中对应的TupleCell
RC do_sub_select(SubSelectStmt sub_select_stmt, FilterUnit *filter_unit, 
                 std::unordered_map<size_t, std::vector<FilterUnit *>> &sub_query_filter, Operator *&oper) {
  RC rc = RC::SUCCESS;
  SelectStmt *select_stmt = static_cast<SelectStmt *>(sub_select_stmt.select);
  bool is_and = select_stmt->is_and();
  FilterStmt *filter_stmt = select_stmt->filter_stmt();
  std::vector<FilterUnit *> single_filter_units;
  std::vector<Operator *> scan_oper_list;
  std::vector<PredicateOperator *> pred_oper_list;
  std::vector<CrossProductOperator *> cross_oper_list;
  std::vector<std::pair<Operator *, FilterUnit *>> sub_oper_list;
  std::vector<SubSelectStmt> sub_query_select;

  for (size_t i=0; i < select_stmt->sub_select_stmts().size(); i++) {
    SubSelectStmt sub_select_stmt_i = select_stmt->sub_select_stmts()[i];
    FilterUnit *sub_filter_unit = filter_stmt->sub_select_units()[i];
    Operator *sub_oper =  nullptr;

    CompOp comp = sub_filter_unit->comp();
    bool not_exists_op = (comp != EXISTS_OP && comp != NOT_EXISTS_OP);

    rc = do_sub_select(sub_select_stmt_i, sub_filter_unit, sub_query_filter, sub_oper);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    // 没有和外层查询进行关联，并且没有重复添加 将sub_filter_unit加回去，
    // 这里的sub_filter_unit已经是子查询执行完毕后的结果
    // 不考虑 exists
    if ((!sub_select_stmt_i.has_joint 
        || (!sub_select_stmt_i.has_joint && i >= 1 && sub_filter_unit != filter_stmt->sub_select_units()[i-1]))
        || !not_exists_op) {
      if (not_exists_op) {
        filter_stmt->add_single_filter_unit(sub_select_stmt_i.joint_table->name(), sub_filter_unit);
      } else {
        filter_stmt->add_filter_unit(sub_filter_unit);
      }
    } else if (sub_select_stmt_i.has_joint && sub_oper != nullptr) {
      sub_oper_list.emplace_back(std::make_pair(sub_oper, sub_filter_unit));
      sub_query_select.emplace_back(sub_select_stmt_i);
    }
  }

  CompOp comp = filter_unit->comp();
  bool not_exists_op = (comp != EXISTS_OP && comp != NOT_EXISTS_OP);
  // 从联表条件中去掉和父查询关联的条件
  auto composite_filter_units = const_cast<std::vector<FilterUnit *> *>(&filter_stmt->filter_units());
  for (auto iter = composite_filter_units->begin(); iter < composite_filter_units->end(); ++iter) {
    size_t table_ptr = reinterpret_cast<size_t>(sub_select_stmt.joint_table);
    auto table_name = (*iter)->get_table_name();
    if (0 == strcmp(sub_select_stmt.joint_table->name(), table_name.first) && not_exists_op) {
      sub_query_filter[table_ptr].emplace_back(*iter);
      filter_stmt->add_single_filter_unit(table_name.second, *iter);
      composite_filter_units->erase(iter);
    } else if (0 == strcmp(sub_select_stmt.joint_table->name(), table_name.second) && not_exists_op) {
      sub_query_filter[table_ptr].emplace_back(*iter);
      filter_stmt->add_single_filter_unit(table_name.first, *iter);
      composite_filter_units->erase(iter);
    }
  }
  
  

  for (auto table: select_stmt->tables()) {
    size_t table_ptr = reinterpret_cast<size_t>(table);
    // 如果是和外层查询相关联的表，跳过，对应的值通过外层查询修改Expression来实现。
    if (sub_select_stmt.has_joint && sub_select_stmt.joint_table == table && not_exists_op) {
      continue;
    }
    
    // 查找sub_query_filter中是否含有关联当前table的子查询FilterUnit
    // 判断表是否有相关联的内层查询
    auto iter = sub_query_filter.find(table_ptr);
    filter_stmt->single_filter_units(table->name(), single_filter_units);

    Operator *scan_oper = new TableScanOperator(table);
    PredicateOperator *pred_oper = nullptr;
    if (iter == sub_query_filter.end()) {
      pred_oper = new PredicateOperator(single_filter_units, is_and);
    } else {
      pred_oper = new PredicateOperator(table->name(), single_filter_units, iter->second, is_and);
    }
    pred_oper->add_child(scan_oper);
    pred_oper_list.push_back(pred_oper);
    single_filter_units.clear();
  }

  for (size_t i=1; i<pred_oper_list.size() ; i++) {
    CrossProductOperator *cross_oper = new CrossProductOperator(*composite_filter_units, is_and);
    if (i == 1) {
      cross_oper->add_child(pred_oper_list[0]);
    } else {
      cross_oper->add_child(cross_oper_list.back());
    }
    cross_oper->add_child(pred_oper_list[i]);
    cross_oper_list.emplace_back(cross_oper);
  }

  for (size_t i=0; i < sub_oper_list.size(); i++) {

    CrossProductOperator *cross_oper = new CrossProductOperator(true, sub_oper_list[i].second, sub_query_select[i], is_and);
    if (cross_oper_list.empty()) {
      cross_oper->add_child(pred_oper_list[0]);
    } else {
      cross_oper->add_child(cross_oper_list.back());
    }
    cross_oper->add_child(sub_oper_list[i].first);
    cross_oper_list.emplace_back(cross_oper);
  }



  ProjectOperator *project_oper = new ProjectOperator();
  if (!cross_oper_list.empty()) {
    // 多表
    project_oper->add_child(cross_oper_list.back());
  } else {
    // 单表
    project_oper->add_child(pred_oper_list[0]);
  }

  for (const Field &field : select_stmt->query_fields()) {
    project_oper->add_projection(field.table(), &field);
  }
  
  Expression *expr = nullptr;
  Expression *field_expr = nullptr;
  if (sub_select_stmt.is_left_value) {
    expr = filter_unit->left();
    field_expr = filter_unit->right();
  } else {
    expr = filter_unit->right();
    field_expr = filter_unit->left();
  }
  
  bool in_or_exists = (comp == CompOp::IN_OP 
                       || comp == CompOp::NOT_IN_OP 
                       || comp == CompOp::EXISTS_OP 
                       || comp == CompOp::NOT_EXISTS_OP);
  if (select_stmt->is_agg()) {
    if (in_or_exists) {
      return RC::GENERIC_ERROR;
    }
    AggregateOperator *agg_oper = new AggregateOperator(select_stmt->rel_attrs(), select_stmt->query_fields());
    agg_oper->add_child(project_oper);

    // 如果与外层查询相关联，
    if (sub_select_stmt.has_joint && comp != CompOp::EXISTS_OP && comp != CompOp::NOT_EXISTS_OP) {
      oper = agg_oper; 
      return RC::SUCCESS;
    }

    rc = agg_oper->open();
    while ((rc = agg_oper->next()) == RC::SUCCESS) {
    }

    if (rc != RC::RECORD_EOF && rc != RC::SUCCESS) {
      return rc;
    } else {
      rc = agg_oper->close();
    }

    Value res = agg_oper->get_result(select_stmt->query_fields()[0]);
    Expression *new_expr = new ValueExpr(res);
    if (sub_select_stmt.is_left_value) {
      filter_unit->set_left(new_expr);
    } else {
      filter_unit->set_right(new_expr);
    }
    delete expr;
    return RC::SUCCESS;
  }

  if (comp != CompOp::EXISTS_OP 
                      && comp != CompOp::NOT_EXISTS_OP
                      && select_stmt->query_fields().size() > 1) {

    return RC::GENERIC_ERROR;
  }

  // 如果与外层查询相关联，
  if (sub_select_stmt.has_joint && comp != CompOp::EXISTS_OP && comp != CompOp::NOT_EXISTS_OP) {
    oper = project_oper; 
    return RC::SUCCESS;
  }

  project_oper->open();
  while ((rc = project_oper->next()) == RC::SUCCESS) {
  }
  if (rc != RC::RECORD_EOF && rc != RC::SUCCESS) {
    return rc;
  }
  
  Field field;
  if (comp != CompOp::EXISTS_OP && comp != CompOp::NOT_EXISTS_OP) {
    field = select_stmt->query_fields()[0];
  } else {
    field = ((FieldExpr *)field_expr)->field();
  }
  Value res = project_oper->get_result(field);
  if (res.type == AttrType::SETS && !in_or_exists) {
    return RC::GENERIC_ERROR;
  }
  Expression *new_expr = new ValueExpr(res);
  if (sub_select_stmt.is_left_value) {
    filter_unit->set_left(new_expr);
  } else {
    filter_unit->set_right(new_expr);
  }
  delete expr;
  return RC::SUCCESS;
}


RC do_func_select(SessionEvent *session_event, std::vector<RelAttr> &func_attrs) {
  RC rc = RC::SUCCESS;
  std::stringstream ss;
  bool first = true;
  for (auto func_attr : func_attrs) {
    if (func_attr.is_value != 1) {
      return RC::INVALID_ARGUMENT;
    }
    if (!first) {
      ss << " | ";
    } else {
      first = false;
    }
    if (func_attr.alias != nullptr) {
      ss << func_attr.alias;
    } else {
      if (func_attr.is_value)
      ss << func_to_string(func_attr.func) << "(";
      if (func_attr.value.type == CHARS) {
        ss << "\'"; 
        value_to_string(ss, &func_attr.value);
        ss << "\'";
      } else {
        value_to_string(ss, &func_attr.value);
      }
      if (func_attr.is_has_second_value) {
        ss << ",";
        value_to_string(ss, &func_attr.second_value);
      }
      ss << ")";
    }
  }
  ss << std::endl;
  first = true;
  for (auto func_attr : func_attrs) {
    if (!first) {
      ss << " | ";
    } else {
      first = false;
    }
    switch (func_attr.func) {
      case LENGTH: {
        ss << strlen((char *)func_attr.value.data);
      } break;
      case ROUND: {
        if (func_attr.value.type != FLOATS) {
          return RC::INVALID_ARGUMENT;
        }
        int acc = 0;
        if (func_attr.is_has_second_value) {
          acc = *(int *)func_attr.second_value.data;
        }
        ss << round_( *(float *)func_attr.value.data, acc);
      } break;
      default:
        return RC::INVALID_ARGUMENT;
    }
  }
  ss << std::endl;
  session_event->set_response(ss.str());
  return rc;
}

RC print_query_head_with_func(std::ostream &os, std::vector<std::pair<int, int>> &fields_or_expr, 
                    const ProjectOperator &oper,  std::vector<RelAttr> func_attrs, 
                    bool is_multi_table) {

  const TupleCellSpec *cell_spec = nullptr;
  for (size_t i=0; i < fields_or_expr.size(); i++) {
    if (i != 0) {
      os << " | ";
    }
    if (fields_or_expr[i].first == 0) {
      oper.tuple_cell_spec_at(fields_or_expr[i].second, cell_spec);
      if (is_multi_table && cell_spec->table_name()) {
        os << cell_spec->table_name() << ".";
      }
      if (cell_spec->alias()) {
        os << cell_spec->alias();
      } 
    } else if (fields_or_expr[i].first == 2) {
      if (func_attrs[fields_or_expr[i].second].alias == nullptr) {
        os << func_to_string(func_attrs[fields_or_expr[i].second].func) << "(";
        if (is_multi_table) {
          os << func_attrs[fields_or_expr[i].second].relation_name << "."; 
        } else {
          os << func_attrs[fields_or_expr[i].second].attribute_name;
        } 
        if (func_attrs[fields_or_expr[i].second].is_has_second_value) {
          os << ",";
          value_to_string(os, &func_attrs[fields_or_expr[i].second].second_value);
        } 
        os << ")";
      } else {
        os << func_attrs[fields_or_expr[i].second].alias; 
      }
    }                   
  }
  return RC::SUCCESS;
}

RC ExecuteStage::do_select(SQLStageEvent *sql_event)
{
  SelectStmt *select_stmt = (SelectStmt *)(sql_event->stmt());
  SessionEvent *session_event = sql_event->session_event();
  RC rc = RC::SUCCESS;
  bool is_and = select_stmt->is_and();
  FilterStmt *filter_stmt = select_stmt->filter_stmt();
  std::vector<FilterUnit *> single_filter_units;
  std::vector<Operator *> scan_oper_list;
  std::vector<PredicateOperator *> pred_oper_list;
  std::vector<CrossProductOperator *> cross_oper_list;
  std::vector<std::pair<Operator *, FilterUnit *>> sub_oper_list;
  std::vector<SubSelectStmt> sub_query_select;
  
  std::unordered_map<size_t, std::vector<FilterUnit *>> sub_query_filter;
  if (select_stmt->is_func()) {
    rc = do_func_select(session_event, select_stmt->func_attrs());
    if (rc != RC::SUCCESS) {
      session_event->set_response("FAILURE\n");
      return rc;
    } 
    return rc;
  }


  for (size_t i=0; i < select_stmt->sub_select_stmts().size(); i++) {
    SubSelectStmt sub_select_stmt = select_stmt->sub_select_stmts()[i];
    FilterUnit *sub_filter_unit = filter_stmt->sub_select_units()[i];
    Operator *sub_oper =  nullptr;
    CompOp comp = sub_filter_unit->comp();
    bool not_exists_op = (comp != EXISTS_OP && comp != NOT_EXISTS_OP);

    rc = do_sub_select(sub_select_stmt, sub_filter_unit, sub_query_filter, sub_oper);
    if (rc != RC::SUCCESS) {
      session_event->set_response("FAILURE\n");
      return rc;
    }

    // 没有和外层查询进行关联, 将sub_filter_unit加回去，这里的sub_filter_unit已经是子查询执行完毕后的结果
    if ((!sub_select_stmt.has_joint 
        || (!sub_select_stmt.has_joint && i >= 1 && sub_filter_unit != filter_stmt->sub_select_units()[i-1]))
        || !not_exists_op) {

      filter_stmt->add_single_filter_unit(select_stmt->tables()[0]->name(), sub_filter_unit);
    
    } else if (sub_select_stmt.has_joint && sub_oper != nullptr) {
      sub_oper_list.emplace_back(std::make_pair(sub_oper, sub_filter_unit));
      sub_query_select.emplace_back(sub_select_stmt);
    }
  }

  for (auto table: select_stmt->tables()) {
    size_t table_ptr = reinterpret_cast<size_t>(table);
    filter_stmt->single_filter_units(table->name(), single_filter_units);

    Operator *scan_oper = try_to_create_index_scan_operator(single_filter_units);
    if (nullptr == scan_oper) {
      scan_oper = new TableScanOperator(table);
    }

    // 查找sub_query_filter中是否含有关联当前table的子查询FilterUnit
    // 判断表是否有相关联的内层查询
    auto iter = sub_query_filter.find(table_ptr);
    filter_stmt->single_filter_units(table->name(), single_filter_units);
    
    PredicateOperator *pred_oper = nullptr;
    if (iter == sub_query_filter.end()) {
      pred_oper = new PredicateOperator(single_filter_units, is_and);
    } else {
      pred_oper = new PredicateOperator(table->name(), single_filter_units, iter->second, is_and);
    }
    pred_oper->add_child(scan_oper);
    pred_oper_list.push_back(pred_oper);
    single_filter_units.clear();
  }

  for (int i=1; i<pred_oper_list.size() ; i++) {
    CrossProductOperator *cross_oper = new CrossProductOperator(filter_stmt->filter_units(), is_and);
    if (i == 1) {
      cross_oper->add_child(pred_oper_list[0]);
    } else {
      cross_oper->add_child(cross_oper_list.back());
    }
    cross_oper->add_child(pred_oper_list[i]);
    cross_oper_list.emplace_back(cross_oper);
  }

  for (size_t i=0; i < sub_oper_list.size(); i++) {
    CrossProductOperator *cross_oper = new CrossProductOperator(true, sub_oper_list[i].second, sub_query_select[i], is_and);
    if (cross_oper_list.empty()) {
      cross_oper->add_child(pred_oper_list[0]);
    } else {
      cross_oper->add_child(cross_oper_list.back());
    }
    cross_oper->add_child(sub_oper_list[i].first);
    cross_oper_list.emplace_back(cross_oper);
  }

  DEFER([&]() { 
    for (int i=0; i<scan_oper_list.size(); i++) {
      delete scan_oper_list[i]; 
    }
    for (int i=0; i<pred_oper_list.size(); i++) {
      delete pred_oper_list[i];
    }
    for (int i=0; i<cross_oper_list.size(); i++) {
      delete cross_oper_list[i];
    }
  });

  ProjectOperator project_oper(select_stmt->group_fields());
  if (!cross_oper_list.empty()) {
    // 多表
    project_oper.add_child(cross_oper_list.back());
  } else {
    // 单表
    project_oper.add_child(pred_oper_list[0]);
  }
  
  for (const Field &field : select_stmt->query_fields()) {
    project_oper.add_projection(field.table(), &field);
  }
  
  // 含有groupby的select输出
  if (!select_stmt->group_fields().empty()) {
    rc = project_oper.open();
    if (rc != RC::SUCCESS) {
      session_event->set_response("FAILURE\n");
      return rc;
    }
    while ((rc = project_oper.next()) == RC::SUCCESS) {
    }
    if (rc != RC::RECORD_EOF && rc != RC::SUCCESS) {
      LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
      session_event->set_response("FAILURE\n");
      return rc;
    } else {
      rc = project_oper.close();
    }
    auto group_fields = select_stmt->group_fields();
    // 有多少组就有多少行，就有多少个AggregateStat
    auto rel_attrs = select_stmt->rel_attrs();
    auto query_fields = select_stmt->query_fields();
    auto query_fields_with_agg = select_stmt->query_fields_with_agg();
    auto fields_or_expr = select_stmt->fields_or_expr();
    AggregateOperator agg_oper(rel_attrs, query_fields_with_agg);

    std::stringstream ss;
    for (size_t i=0; i<fields_or_expr.size(); i++) {
      if (i != 0) {
        ss << " | ";
      }
      if (fields_or_expr[i].first == 0) {
        if (!cross_oper_list.empty()) {
          ss << query_fields[fields_or_expr[i].second].table_name() << '.';
        }
        ss << query_fields[fields_or_expr[i].second].field_name();
      } else if (fields_or_expr[i].first == -1) {
        agg_oper.print_header_at(ss, fields_or_expr[i].second, !cross_oper_list.empty());
      }
    }
    ss << std::endl;
    for (auto group_tuple : project_oper.group_tuples()) {
      agg_oper.reset();
      std::vector<AggregateStat> stats(rel_attrs.size());
      for (auto tuple: group_tuple.second) {
        agg_oper.add_tuple(tuple.get());
      }
      if (select_stmt->has_having() && !agg_oper.do_prdicate(select_stmt->having())) {
        continue;
      }
      for (size_t i=0; i<fields_or_expr.size(); i++) {
        if (i != 0) {
          ss << " | ";
        }
        if (fields_or_expr[i].first == 0) {
          TupleCell cell;
          group_tuple.second[0]->find_cell(query_fields[fields_or_expr[i].second], cell);
          cell.to_string(ss);
        } else if (fields_or_expr[i].first == -1) {
          agg_oper.to_string_at(ss, fields_or_expr[i].second);
        }
      }
      ss << std::endl;
    }
    session_event->set_response(ss.str());
    return rc;
  }

  // 含有聚合函数的select输出
  if (select_stmt->is_agg()) {
    AggregateOperator agg_oper(select_stmt->rel_attrs(), select_stmt->query_fields());
    agg_oper.add_child(&project_oper);
    agg_oper.open();
    while ((rc = agg_oper.next()) == RC::SUCCESS) {
    }
    if (rc != RC::RECORD_EOF && rc != RC::SUCCESS) {
      LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
      session_event->set_response("FAILURE\n");
      return rc;
    } else {
      rc = agg_oper.close();
    }
    std::stringstream ss;
    // 如果是聚合，那么
    auto fields_or_expr = select_stmt->fields_or_expr();
    auto query_expr = select_stmt->query_expr();
    for (size_t i = 0; i < fields_or_expr.size(); i++) {
        if (i != 0) {
          ss << " | ";
        }
        if (fields_or_expr[i].first == 0) {
          agg_oper.print_header_at(ss, fields_or_expr[i].second);
        } else if (fields_or_expr[i].first == 1){
          query_expr[fields_or_expr[i].second]->to_string(ss, false);
        }
    }
    ss << std::endl;
    auto tuple = agg_oper.get_result_tuple();
    for (size_t i=0; i<fields_or_expr.size(); i++) {
      if (i != 0) {
        ss << " | ";
      }
      if (fields_or_expr[i].first == 0) {
        agg_oper.to_string_at(ss, fields_or_expr[i].second);
      } else if (fields_or_expr[i].first == 1) {
        TupleCell cell;
        query_expr[fields_or_expr[i].second]->get_value(tuple, cell);
        cell.to_string(ss);
      }

    }
    // agg_oper.to_string(ss);
    ss << std::endl;
    if (rc != RC::RECORD_EOF && rc != RC::SUCCESS) {
      LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
      session_event->set_response("FAILURE\n");
      return rc;
    } else {
      rc = agg_oper.close();
    }
    session_event->set_response(ss.str());
    return rc;
  }

  rc = project_oper.open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open operator");
    return rc;
  }

  std::stringstream ss;
  // 含有函数的select输出
  if (!select_stmt->func_attrs().empty()) {
    auto query_fields = select_stmt->query_fields();
    auto func_fields = select_stmt->query_func_fields();
    auto fields_or_expr = select_stmt->fields_or_expr();
    auto func_attrs = select_stmt->func_attrs();
    print_query_head_with_func(ss, select_stmt->fields_or_expr(), project_oper, select_stmt->func_attrs(), !cross_oper_list.empty());
    ss << std::endl;
    while ((rc = project_oper.next()) == RC::SUCCESS) {
      // get current record
      // write to response
      Tuple *tuple = project_oper.current_tuple();
      for (size_t i=0; i < fields_or_expr.size(); i++) {
        if (i != 0) {
          ss << " | ";
        }
        TupleCell cell;
        if (fields_or_expr[i].first == 0) {
          rc = tuple->find_cell(query_fields[fields_or_expr[i].second], cell);
          if (rc != RC::SUCCESS) {
            session_event->set_response("FAILURE\n");
            return rc;
          }
          cell.to_string(ss);
        } else if (fields_or_expr[i].first == 2) {
          rc = tuple->find_cell(func_fields[fields_or_expr[i].second], cell);
          if (rc != RC::SUCCESS) {
            session_event->set_response("FAILURE\n");
            return rc;
          }
          rc = cell.to_string_with_func(ss, func_attrs[fields_or_expr[i].second]);
          if (rc != RC::SUCCESS) {
            session_event->set_response("FAILURE\n");
            return rc;
          }
        }
      }
      ss << std::endl;
    }
    session_event->set_response(ss.str());
    return rc;
  }

  // 含有orderby和普通的select的输出
  print_tuple_header(ss, project_oper, select_stmt->tables().size() > 1, select_stmt->query_expr(), select_stmt->fields_or_expr());
  
  if (select_stmt->has_order()) {
    while ((rc = project_oper.next()) == RC::SUCCESS) {

    }
    if (rc != RC::RECORD_EOF && rc != RC::SUCCESS) {
      LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
      session_event->set_response("FAILURE\n");
      return rc;
    } else {
      rc = project_oper.close();
    }
    Operator *child_oper = project_oper.get_child();
    if (child_oper->type() == OperatorType::CROSS_PRODUCT) {
      auto cross_oper = static_cast<CrossProductOperator *>(child_oper);
      auto tuple_set = cross_oper->tuple_set();
      std::sort(tuple_set.begin(), tuple_set.end(), [&](CompositeTuple &tuple1, CompositeTuple &tuple2) {
        TupleComparetor comparetor = select_stmt->comparetor();
        return comparetor(&tuple1, &tuple2);
      });
      for (size_t i = 0; i < tuple_set.size(); i++) {
        bool first = true;
        for (const Field &field : select_stmt->query_fields()) {
          TupleCell cell;
          tuple_set[i].find_cell(field, cell);
          if (!first) {
            ss << " | ";
          } else {
            first = false;
          }
          cell.to_string(ss);
        }
        ss << std::endl;
      }
    } else if (child_oper->type() == OperatorType::PREDICATE){
      auto pred_oper = static_cast<PredicateOperator *>(child_oper);
      auto tuple_set = pred_oper->tuple_set();
      std::sort(tuple_set.begin(), tuple_set.end(), [&](RowTuple &tuple1, RowTuple &tuple2) {
        TupleComparetor comparetor = select_stmt->comparetor();
        return comparetor(&tuple1, &tuple2);
      });
      for (size_t i = 0; i < tuple_set.size(); i++) {
        bool first = true;
        for (const Field &field : select_stmt->query_fields()) {
          TupleCell cell;
          tuple_set[i].find_cell(field, cell);
          if (!first) {
            ss << " | ";
          } else {
            first = false;
          }
          cell.to_string(ss);
        }
        ss << std::endl;
      }
    }
    session_event->set_response(ss.str());
    return rc;
  } 


  while ((rc = project_oper.next()) == RC::SUCCESS) {
    // get current record
    // write to response
    Tuple *tuple = project_oper.current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc=%s", strrc(rc));
      break;
    }
    tuple_to_string(ss, *tuple, select_stmt->query_expr(), select_stmt->fields_or_expr());
    ss << std::endl;
  }
  
  if (rc != RC::RECORD_EOF && rc != RC::SUCCESS) {
    LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
    session_event->set_response("FAILURE\n");
    return rc;
  } else {
    rc = project_oper.close();
  }

  session_event->set_response(ss.str());
  return rc;
}

RC ExecuteStage::do_help(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  const char *response = "show tables;\n"
                         "desc `table name`;\n"
                         "create table `table name` (`column name` `column type`, ...);\n"
                         "create index `index name` on `table` (`column`);\n"
                         "insert into `table` values(`value1`,`value2`);\n"
                         "update `table` set column=value [where `column`=`value`];\n"
                         "delete from `table` [where `column`=`value`];\n"
                         "select [ * | `columns` ] from `table`;\n";
  session_event->set_response(response);
  return RC::SUCCESS;
}

RC ExecuteStage::do_create_table(SQLStageEvent *sql_event)
{
  const CreateTable &create_table = sql_event->query()->sstr.create_table;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  RC rc = db->create_table(create_table.relation_name, create_table.attribute_count, create_table.attributes);
  if (rc == RC::SUCCESS) {
    session_event->set_response("SUCCESS\n");
  } else {
    session_event->set_response("FAILURE\n");
  }
  return rc;
}

RC ExecuteStage::do_drop_table(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  const DropTable &drop_table = sql_event->query()->sstr.drop_table;
  RC rc = db->drop_table(drop_table.relation_name);
  if (rc == RC::SUCCESS) {
    session_event->set_response("SUCCESS\n");
  } else {
    session_event->set_response("FAILURE\n");
  }
  return rc;
}

RC ExecuteStage::do_create_index(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  CreateIndex &create_index = sql_event->query()->sstr.create_index;
  Table *table = db->find_table(create_index.relation_name);
  if (nullptr == table) {
    session_event->set_response("FAILURE\n");
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  RC rc = table->create_index(nullptr, create_index.index_name, (const char **)create_index.attribute_name, create_index.attr_num, create_index.is_unique);
  sql_event->session_event()->set_response(rc == RC::SUCCESS ? "SUCCESS\n" : "FAILURE\n");
  return rc;
}

RC ExecuteStage::do_show_index(SQLStageEvent *sql_event) {
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  const ShowIndex &show_index = sql_event->query()->sstr.show_index;
  Table *table = db->find_table(show_index.relation_name);
  if (nullptr == table) {
    session_event->set_response("FAILURE\n");
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  std::stringstream ss;
  RC rc = table->show_index(ss);
  sql_event->session_event()->set_response(rc == RC::SUCCESS ? ss.str().c_str() : "FAILURE\n");
  return rc;
}

RC ExecuteStage::do_show_tables(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  std::vector<std::string> all_tables;
  db->all_tables(all_tables);
  if (all_tables.empty()) {
    session_event->set_response("No table\n");
  } else {
    std::stringstream ss;
    for (const auto &table : all_tables) {
      ss << table << std::endl;
    }
    session_event->set_response(ss.str().c_str());
  }
  return RC::SUCCESS;
}

RC ExecuteStage::do_desc_table(SQLStageEvent *sql_event)
{
  Query *query = sql_event->query();
  Db *db = sql_event->session_event()->session()->get_current_db();
  const char *table_name = query->sstr.desc_table.relation_name;
  Table *table = db->find_table(table_name);
  std::stringstream ss;
  if (table != nullptr) {
    table->table_meta().desc(ss);
  } else {
    ss << "No such table: " << table_name << std::endl;
  }
  sql_event->session_event()->set_response(ss.str().c_str());
  return RC::SUCCESS;
}

RC ExecuteStage::do_insert(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  InsertStmt *insert_stmt = (InsertStmt *)stmt;
  Table *table = insert_stmt->table();
  std::vector<const Value *> values_list = insert_stmt->values();
  std::vector<int> values_amount_list = insert_stmt->value_amount();
  RC rc = RC::SUCCESS;

  for (size_t i = 0; i < values_list.size(); i++) {
    rc = table->insert_record(trx, values_amount_list[i], values_list[i]);
    if (rc == RC::SUCCESS) {
      if (!session->is_trx_multi_operation_mode()) {
        CLogRecord *clog_record = nullptr;
        rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
        if (rc != RC::SUCCESS || clog_record == nullptr) {
          session_event->set_response("FAILURE\n");
          return rc;
        }

        rc = clog_manager->clog_append_record(clog_record);
        if (rc != RC::SUCCESS) {
          session_event->set_response("FAILURE\n");
          return rc;
        }

        trx->next_current_id();
        session_event->set_response("SUCCESS\n");
      } else {
        session_event->set_response("SUCCESS\n");
      }
    } else {
      session_event->set_response("FAILURE\n");
    }
  }

  return rc;
}

RC ExecuteStage::do_update(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  UpdateStmt *update_stmt = (UpdateStmt *)stmt;
  Table *table = update_stmt->table();
  TableScanOperator scan_oper(table);
  std::vector<FilterUnit *> filter_units;
  update_stmt->filter_stmt()->single_filter_units(table->name(), filter_units);
  PredicateOperator pred_oper(filter_units);
  pred_oper.add_child(&scan_oper);
  UpdateOperator update_oper(update_stmt, trx);
  update_oper.add_child(&pred_oper);

  RC rc = update_oper.open();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc;
      }
      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    }
  }
  return rc;
}

RC ExecuteStage::do_delete(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  DeleteStmt *delete_stmt = (DeleteStmt *)stmt;
  Table *table = delete_stmt->table();
  TableScanOperator scan_oper(table);
  std::vector<FilterUnit *> filter_units;
  delete_stmt->filter_stmt()->single_filter_units(table->name(), filter_units);
  PredicateOperator pred_oper(filter_units);
  pred_oper.add_child(&scan_oper);
  DeleteOperator delete_oper(delete_stmt, trx);
  delete_oper.add_child(&pred_oper);

  RC rc = delete_oper.open();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    }
  }
  return rc;
}

RC ExecuteStage::do_begin(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  session->set_trx_multi_operation_mode(true);

  CLogRecord *clog_record = nullptr;
  rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_BEGIN, trx->get_current_id(), clog_record);
  if (rc != RC::SUCCESS || clog_record == nullptr) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  rc = clog_manager->clog_append_record(clog_record);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  return rc;
}

RC ExecuteStage::do_commit(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  session->set_trx_multi_operation_mode(false);

  CLogRecord *clog_record = nullptr;
  rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
  if (rc != RC::SUCCESS || clog_record == nullptr) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  rc = clog_manager->clog_append_record(clog_record);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  trx->next_current_id();

  return rc;
}

RC ExecuteStage::do_clog_sync(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  CLogManager *clog_manager = db->get_clog_manager();

  rc = clog_manager->clog_sync();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  return rc;
}
