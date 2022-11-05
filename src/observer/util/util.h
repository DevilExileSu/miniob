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
// Created by wangyunlai on 2022/9/28
//

#pragma once

#include <string>
#include <ctime>

#include "rc.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/field_meta.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "sql/expr/expression.h"
#include "util/comparator.h"



std::string double2string(double v);

std::string int2string(int v);

std::string float2string(float v);

int string2int(char *v);

float string2float(char *v);

int check_prefix(char *v);

bool like_match(const char *a, const char *b);

RC convert(const FieldMeta *field_meta, Value *value, bool &has_text);

RC convert(AttrType type, Value *value, bool &has_text);

void value_init_from_cell(TupleCell cell, Value *value);



class AggregateStat {

public:
  void add_tuple(TupleCell &cell) {
    // 获取cell的数据
    char *data = const_cast<char *>(cell.data());
    AttrType data_type = cell.attr_type();
    // 按照data的数据类型相应的转换，这里为了统计，全部转换为浮点型
    if (data_type_ == AttrType::UNDEFINED || data_type_ == AttrType::NULL_) {
      data_type_ = data_type;
    }

    float data_f = 0.0;
    switch (data_type) {
      case NULL_: {
        break;
      }
      case DATES:
      case INTS: {
        data_f = *(int *)data;
        if (min_ == nullptr || compare_int(data, min_) < 0) {
          min_ = data;
        }
        if (max_ == nullptr || compare_int(data, max_) > 0) {
          max_ = data;
        }
        break;
      }
      case CHARS: {
        data_f = atof(data);
        if (min_ == nullptr || compare_string(data, strlen(data), min_, strlen(min_)) < 0) {
          min_ = data;
        }
        if (max_ == nullptr || compare_string(data, strlen(data), max_, strlen(max_)) > 0) {
          max_ = data;
        }
        break;
      }
      case FLOATS: {
        data_f = *(float *) data;
        if (min_ == nullptr || compare_float(data, min_) < 0) {
          min_ = data;
        }
        if (max_ == nullptr || compare_float(data, max_) > 0) {
          max_ = data;
        }
        break;
      }
      default:
        break;
    }
    if (data_type != AttrType::NULL_) {
      ++not_null_count_;
      sum_ += data_f;
    }
    ++count_;
  }

  std::string max() { 
    switch (data_type_) {
      case INTS:
        return int2string(*(int *)max_);
      case CHARS: 
        return std::string(max_);
      case FLOATS:
        return double2string(*(float *)max_);
      case DATES: {
        int value = *(int *)max_;
        char buf[16] = {0};
        sprintf(buf, "%04d-%02d-%02d", value/10000, (value%10000)/100, value%100);
        return std::string(buf);
      }
      default:
        return std::string("error");
    }
  }
  std::string min() {     
    switch (data_type_) {
      case INTS:
        return int2string(*(int *)min_);
      case CHARS: 
        return std::string(min_);
      case FLOATS:
        return double2string(*(float *)min_);
      case DATES: {
        int value = *(int *)min_;
        char buf[16] = {0};
        sprintf(buf, "%04d-%02d-%02d", value/10000, (value%10000)/100, value%100);
        return std::string(buf);
      }
      default:
        return std::string("error");
    }
  }
  float sum() { return sum_; }
  float avg() { return sum_ / not_null_count_; }
  int count() { return count_; }
  int not_null_count() { return not_null_count_; }
  bool is_null() { return not_null_count_ == 0; }

  void reset() {
    data_type_ = AttrType::UNDEFINED;
    min_ = nullptr;
    max_ = nullptr;
    count_ = 0;
    not_null_count_ = 0;
    sum_ = .0;
  }

private:
  AttrType data_type_ = AttrType::UNDEFINED;
  char *min_ = nullptr;
  char *max_ = nullptr;
  int count_ = 0;
  int not_null_count_ = 0;
  float sum_ = .0;
};

float round_(float v, int accuracy);
std::string func_to_string(Func func);
void value_to_string(std::ostream &os, Value *value);
void date_format(std::ostream &os, int date, const char *format);