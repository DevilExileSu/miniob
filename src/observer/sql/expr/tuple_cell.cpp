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
// Created by WangYunlai on 2022/07/05.
//
#include "sql/expr/tuple_cell.h"
#include "storage/common/field.h"
#include "common/log/log.h"
#include "util/comparator.h"
#include "util/util.h"

RC TupleCell::to_string_with_func(std::ostream &os, RelAttr func_attr) const {
  if (func_attr.func == LENGTH) {
    if (attr_type_ != CHARS) {
      return RC::INVALID_ARGUMENT;
    }
    os << strlen(data_);
  } else if(func_attr.func == ROUND) {
    if (attr_type_ != FLOATS) {
      return RC::INVALID_ARGUMENT;
    }
    int acc = 0;
    if (func_attr.is_has_second_value) {
      acc = *(int *)func_attr.second_value.data;
    }
    os << double2string(round_(*(float *)data_, acc));
  } else if (func_attr.func == DATE_FORMAT) {
    if (attr_type_ != DATES || func_attr.is_has_second_value == 0) {
      return RC::INVALID_ARGUMENT;
    }
    date_format(os, *(int *)data_, (char *)func_attr.second_value.data);
  } else {
    return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}


void TupleCell::to_string(std::ostream &os) const
{
  switch (attr_type_) {
  case INTS: {
    os << *(int *)data_;
  } break;
  case FLOATS: {
    float v = *(float *)data_;
    os << double2string(v);
  } break;
  case TEXTS: {
    for (int i = 0; i < length_; i++) {
      if (data_[i] == '\0') {
        break;
      }
      os << data_[i];
    }
  } break;
  case CHARS: {
    for (int i = 0; i < length_; i++) {
      if (data_[i] == '\0') {
        break;
      }
      os << data_[i];
    }
  } break;
  case DATES: {
    int value = *(int *)data_;
    char buf[16] = {0};
    sprintf(buf, "%04d-%02d-%02d", value/10000, (value%10000)/100, value%100);
    os << buf;
  }break;
  case NULL_: {
    os << "NULL";
  } break;
  default: {
    LOG_WARN("unsupported attr type: %d", attr_type_);
  } break;
  }
}

int TupleCell::compare(const TupleCell &other) const
{
  if (this->attr_type_ == NULL_ || other.attr_type_ == NULL_) {
    return -1;
  }
  // 对select显示结果排序时可能需要进行修改
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
    case INTS: return compare_int(this->data_, other.data_);
    case FLOATS: return compare_float(this->data_, other.data_);
    case CHARS: return compare_string(this->data_, this->length_, other.data_, other.length_);
    case DATES: return compare_int(this->data_, other.data_);
    default: {
      LOG_WARN("unsupported type: %d", this->attr_type_);
    }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = *(int *)data_;
    return compare_float(&this_data, other.data_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = *(int *)other.data_;
    return compare_float(data_, &other_data);
  } else if (this->attr_type_ == INTS && other.attr_type_ == CHARS) {
    // INT和CHAR比较时都转换为浮点数进行比较
    float other_data = atof(other.data_);
    float this_data = *(int *)this->data_;
    return compare_float(&this_data, &other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == INTS) {
    float other_data = *(int *)other.data_;
    float this_data = atof(this->data_);
    return compare_float(&this_data, &other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS) {
    float this_data = atof(this->data_);
    return compare_float(&this_data, other.data_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {
    float other_data = atof(other.data_);
    return compare_float(this->data_, &other_data);
  }
  LOG_WARN("not supported");
  return -1; // TODO return rc?
}
