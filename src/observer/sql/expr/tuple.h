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
// Created by Wangyunlai on 2021/5/14.
//

#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

#include "common/log/log.h"
#include "sql/parser/parse.h"
#include "sql/expr/tuple_cell.h"
#include "sql/expr/expression.h"
#include "storage/record/record.h"
#include "util/util.h"

class Table;
class AggregateStat;

enum class TupleType {
  ROW,
  COMPOSITE,
  PROJECT,
  CUSTOMIZE,
};

class TupleCellSpec
{
public:
  TupleCellSpec() = default;
  TupleCellSpec(Expression *expr) : expression_(expr)
  {}
  TupleCellSpec(const TupleCellSpec& spec){
    alias_=spec.alias_;
    //拷贝函数 要创建新的表达式指针
    if(spec.expression()){
      if(spec.expression()->type()==ExprType::FIELD){
        this->expression_=std::unique_ptr<Expression>(new FieldExpr(*(FieldExpr*)spec.expression()));
      }else if(spec.expression()->type()==ExprType::VALUE){
        this->expression_=std::unique_ptr<Expression>(new ValueExpr(*(ValueExpr*)spec.expression()));
      }
    }
  }
  TupleCellSpec& operator=(const TupleCellSpec &spec)
	{
    alias_=spec.alias_;
    if(spec.expression()){
      if(spec.expression()->type()==ExprType::FIELD){
        this->expression_=std::unique_ptr<Expression>(new FieldExpr(*(FieldExpr*)spec.expression()));
      }else if(spec.expression()->type()==ExprType::VALUE){
        this->expression_=std::unique_ptr<Expression>(new ValueExpr(*(ValueExpr*)spec.expression()));
      }
    }
		return *this;
	}

  ~TupleCellSpec()
  {

  }
  void set_table_name(const char *table_name) {
    this->table_name_ = table_name;
  }
  void set_alias(const char *alias)
  {
    this->alias_ = alias;
  }
  const char *alias() const
  {
    return alias_;
  }
  const char *table_name() const {
    return table_name_;
  }

  Expression *expression() const
  {
    return expression_.get();
  }

private:
  const char *alias_ = nullptr;
  const char *table_name_ = nullptr;
  std::unique_ptr<Expression> expression_;
};

class Tuple
{
public:
  Tuple() = default;
  virtual ~Tuple() = default;

  virtual TupleType type() const = 0;
  virtual int cell_num() const = 0; 
  virtual RC  cell_at(int index, TupleCell &cell) const = 0;
  virtual RC  find_cell(const Field &field, TupleCell &cell) const = 0;

  virtual RC  cell_spec_at(int index, const TupleCellSpec *&spec) const = 0;
};

class RowTuple : public Tuple
{
public:
  RowTuple() = default;
  RowTuple(const RowTuple &tuple) {
    this->record_ = tuple.record_;
    this->table_ = tuple.table_;
    this->speces_ = tuple.speces_;
  }
  RowTuple& operator=(const RowTuple &tuple) {
    this->record_ = tuple.record_;
    this->table_ = tuple.table_;
    this->speces_ = tuple.speces_;
    return *this;
  }
  virtual ~RowTuple()
  {
    // for (TupleCellSpec *spec : speces_) {
    //   delete spec;
    // }
    // speces_.clear();
  }
  
  void set_record(Record *record)
  {
    this->record_ = record;
  }
  const char *table_name() {
    if (table_ == nullptr) {
      return nullptr;
    }
    return table_->name();
  }
  void set_schema(const Table *table, const std::vector<FieldMeta> *fields)
  {
    table_ = table;
    this->speces_.reserve(fields->size());
    for (const FieldMeta &field : *fields) {
      speces_.push_back(new TupleCellSpec(new FieldExpr(table, &field)));
    }
  }

  TupleType type() const override {
    return TupleType::ROW;
  }

  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    const TupleCellSpec *spec = speces_[index];
    FieldExpr *field_expr = (FieldExpr *)spec->expression();
    const FieldMeta *field_meta = field_expr->field().meta();
    int bitmap = *(int *)(this->record_->data() + table_->table_meta().bitmap_offset());
    // 1. 先判断该字段对应的值是否为NULL
    bool is_null = 1 & (bitmap >> field_meta->index());
    if (is_null) {
      cell.set_type(AttrType::NULL_);
      return RC::SUCCESS;
    }
    // 2. 将data替换为`NULL`
    cell.set_type(field_meta->type());
    if (field_meta->type() == AttrType::TEXTS) {
      table_->get_text_data(record_, field_meta, (char *)text_data);
      cell.set_data(text_data);
      cell.set_length(strlen(text_data));
    } else {
      cell.set_data(this->record_->data() + field_meta->offset());
      cell.set_length(field_meta->len());
    }
    return RC::SUCCESS;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    const char *table_name = field.table_name();
    if (0 != strcmp(table_name, table_->name())) {
      return RC::NOTFOUND;
    }

    const char *field_name = field.field_name();
    for (size_t i = 0; i < speces_.size(); ++i) {
      const FieldExpr * field_expr = (const FieldExpr *)speces_[i]->expression();
      const Field &field = field_expr->field();
      if (0 == strcmp(field_name, field.field_name())) {
	      return cell_at(i, cell);
      }
    }
    return RC::NOTFOUND;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

  Record &record()
  {
    return *record_;
  }

  const Record &record() const
  {
    return *record_;
  }
private:
  Record *record_ = nullptr;
  const Table *table_ = nullptr;
  std::vector<TupleCellSpec *> speces_;
  char text_data[4097] = {0};
};


class CompositeTuple : public Tuple
{
public:
  CompositeTuple() = default;

  CompositeTuple(const CompositeTuple &tuple) {
    this->tuples_ = tuple.tuples_;
    this->speces_ = tuple.speces_;
  }
  CompositeTuple& operator=(const CompositeTuple &tuple) {
    this->tuples_ = tuple.tuples_;
    this->speces_ = tuple.speces_;
    return *this;
  }

  virtual ~CompositeTuple()
  {
    tuples_.clear();
    speces_.clear();
  }

  TupleType type() const override {
    return TupleType::COMPOSITE;
  }

  int cell_num() const override {
    return speces_.size();
  }
  
  void clear_tuple() {
    tuples_.clear();
  }

  // 这样做是为了使children既可以是CrossProductOperator也可以是predicate

  void add_tuple(Tuple *tuple) {
    // assert(tuple->type() == TupleType::ROW);
    if (tuple->type() == TupleType::COMPOSITE) {
      CompositeTuple *comp_tuple = static_cast<CompositeTuple *>(tuple);
      
      tuples_.insert(tuples_.end(), comp_tuple->tuples_.begin(), comp_tuple->tuples_.end());
    } else if (tuple->type() == TupleType::ROW) {
      // RowTuple 
      RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
      Record *new_record = new Record(row_tuple->record());
      row_tuple->set_record(new_record);
      std::shared_ptr<RowTuple> new_row_tuple = std::make_shared<RowTuple>(*row_tuple);
      tuples_.emplace_back(new_row_tuple);
    }
    
  }

  void remove_tuple() {
    tuples_.pop_back();
  }
  // 在调用ProjectTuple的set_tuple方法时，
  // 每次获取一个CompositeTuple时，都需要调用该方法
  void set_speces(std::vector<TupleCellSpec *> &speces) {
	  speces_ = speces;
  }

  // 1. 获取index对应的TupleCellSpec, 获取其FieldExpr的Field信息
  // 2. 调用子tuple的find_cell方法，获取TupleCell结果
  RC cell_at(int index, TupleCell &cell) const override {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    TupleCellSpec *spec = speces_[index];
    FieldExpr *field_expr = (FieldExpr *)spec->expression();
    Field field = field_expr->field();
    // 直接调用find_cell方法
    return find_cell(field, cell);
  }

  // 1. 通过Field获取对应的表，在通过表获取对应的子Tuple
  // 2. 调用子tuple的find_cell方法，获取TupleCell结果
  RC find_cell(const Field &field, TupleCell &cell) const override {
    // 获取表名
    RC rc = SUCCESS;
    for (auto tuple: tuples_) {
      if (RC::SUCCESS == (rc = tuple->find_cell(field, cell))) {
        return rc;
      }
    }
    return RC::NOTFOUND;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }
  
    
private:
  std::vector<std::shared_ptr<RowTuple>> tuples_;
  std::vector<TupleCellSpec *> speces_;
};

class ProjectTuple : public Tuple
{
public:
  ProjectTuple() = default;
  virtual ~ProjectTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_tuple(Tuple *tuple)
  {
    if (tuple->type() == TupleType::COMPOSITE) {
      CompositeTuple *comp_tuple = static_cast<CompositeTuple *>(tuple);
      comp_tuple->set_speces(speces_);
    }
    this->tuple_ = tuple;
  }

  void add_cell_spec(TupleCellSpec *spec)
  {
    speces_.push_back(spec);
  }

  TupleType type() const override {
    return TupleType::PROJECT;
  }

  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::GENERIC_ERROR;
    }
    if (tuple_ == nullptr) {
      return RC::GENERIC_ERROR;
    }

    const TupleCellSpec *spec = speces_[index];
    return spec->expression()->get_value(*tuple_, cell);
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    return tuple_->find_cell(field, cell);
  }
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }
private:
  std::vector<TupleCellSpec *> speces_;
  Tuple *tuple_ = nullptr;
};



class CustomizeTuple : public Tuple
{
public:
  CustomizeTuple() = default;

  CustomizeTuple(const std::vector<AggregateStat> &stat, const std::vector<Field> &fields) : fields_(fields), stat_(stat) {}


  virtual ~CustomizeTuple()
  {
  }

  TupleType type() const override {
    return TupleType::CUSTOMIZE;
  }

  int cell_num() const override {
    return fields_.size();
  }

  RC find_cell(const Field &field, TupleCell &cell, AggFunc agg_func) {
    for (int i=0; i<fields_.size(); i++) {
      if ( (0 == strcmp(field.field_name(), fields_[i].field_name())) ) {
        switch (agg_func) {
          case AVG: {
            cell.set_type(AttrType::FLOATS);
            float *avg = (float *)malloc(sizeof(float));
            *avg = stat_[i].avg();
            cell.set_data((char *)avg);
            return RC::SUCCESS;
          } break;
          case COUNT: {
            cell.set_type(AttrType::INTS);
            int *count = (int *)malloc(sizeof(int));
            *count = stat_[i].not_null_count();
            cell.set_data((char *)count);
            return RC::SUCCESS;
          } break;
          case MAX: {
            cell.set_type(AttrType::CHARS);
            std::string max = stat_[i].max();
            char *c_max = (char *)malloc(max.size());
            memcpy(c_max, max.c_str(), max.size());
            cell.set_data(c_max);
            return RC::SUCCESS;
          } break;
          case MIN: {
            cell.set_type(AttrType::CHARS);
            std::string min = stat_[i].min();
            char *c_min = (char *)malloc(min.size());
            memcpy(c_min, min.c_str(), min.size());
            cell.set_data(c_min);
            return RC::SUCCESS;
          } break;
          case SUM: {
            cell.set_type(AttrType::FLOATS);
            float *sum = (float *)malloc(sizeof(float));
            *sum = stat_[i].sum();
            cell.set_data((char *)sum);
            return RC::SUCCESS;
          } break;
          default: {
            cell.set_type(AttrType::NULL_);
            return RC::SUCCESS;
          } break;
        }
      }
    }
    return RC::SUCCESS;
  }

  RC cell_at(int index, TupleCell &cell) const override {
    // if (index >= values_.size()) {
    //   return RC::INVALID_ARGUMENT;
    // }
    // // return find_cell(field, cell);
    // cell.set_type(values_[index].type);
    // cell.set_data((char *)values_[index].data);
    return RC::INVALID_ARGUMENT;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override {
    return RC::INVALID_ARGUMENT;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    return RC::INVALID_ARGUMENT;
  }

private:
  std::vector<Field> fields_;
  std::vector<AggregateStat> stat_;
};

typedef struct TupleComparetor {
  
  bool operator() (Tuple *tuple1, Tuple *tuple2) {
    for (size_t i=0; i<fields_.size(); i++) {
      TupleCell cell1, cell2;
      tuple1->find_cell(fields_[i], cell1);
      tuple2->find_cell(fields_[i], cell2);
      
      size_t field_ptr = reinterpret_cast<size_t>(fields_[i].meta());
      // 默认是升序
      bool order = true;
      auto iter = fields_order_.find(field_ptr);
      if (iter != fields_order_.end()) {
        order = fields_order_[field_ptr];
      }
      if (cell1.attr_type() == NULL_ && cell2.attr_type() != NULL_){
        return order;
      } else if (cell1.attr_type() != NULL_ && cell2.attr_type() == NULL_) {
        return !order;
      } else if (cell1.attr_type() == NULL_ && cell2.attr_type() == NULL_) {
        continue;
      } else {
        int compare = cell1.compare(cell2);
        if (compare == 0) {
          continue;
        } else {
          if (order) {
            return compare < 0;
          } else {
            return compare > 0;
          }
        }
      }
    }
    return true;
  }

  std::vector<Field> fields_;
  std::unordered_map<size_t, bool> fields_order_;
} TupleComparetor;