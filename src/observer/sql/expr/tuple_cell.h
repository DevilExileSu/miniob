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
// Created by WangYunlai on 2022/6/7.
//

#pragma once

#include <iostream>
#include "storage/common/table.h"
#include "storage/common/field_meta.h"

class TupleCell
{
public: 
  TupleCell() = default;
  
  TupleCell(FieldMeta *meta, char *data)
    : TupleCell(meta->type(), data)
  {}
  TupleCell(AttrType attr_type, char *data)
    : attr_type_(attr_type), data_(data)
  {}

  void set_type(AttrType type) { this->attr_type_ = type; }
  void set_length(int length) { this->length_ = length; }
  void set_data(char *data) { this->data_ = data; }
  void set_data(const char *data) { this->set_data(const_cast<char *>(data)); }

  void to_string(std::ostream &os) const;

  int compare(const TupleCell &other) const;

  const char *data() const
  {
    return data_;
  }

  char *raw_data() const {
    return data_;
  }

  int length() const { return length_; }

  AttrType attr_type() const
  {
    return attr_type_;
  }

  TupleCell operator+(const TupleCell &cell) const {
    TupleCell res_cell;
    res_cell.attr_type_ = NULL_;
    if (this->attr_type_ == NULL_ || cell.attr_type_ == NULL_) {
      return res_cell;
    }
    if (this->attr_type_ == cell.attr_type_) {
      switch (this->attr_type_) {
      case INTS:  {
        int *res = (int *)malloc(sizeof(int));
        *res = *(int *)this->data_ + *(int *)cell.data_;
        res_cell.attr_type_ = INTS;
        res_cell.set_data((char *)res);
      } break;
      case FLOATS: {
        float *res = (float *)malloc(sizeof(float));
        *res = *(float *)this->data_ + *(float *)cell.data_;
        res_cell.attr_type_ = FLOATS;
        res_cell.set_data((char *)res);
      } break;
      case CHARS: {
        float *res = (float *)malloc(sizeof(float));
        *res = atof(this->data_) + atof(cell.data_);
        res_cell.attr_type_ = FLOATS;
        res_cell.set_data((char *)res);
      } break;
      default: 
        break;
      }
    } else if(attr_type_ == INTS && cell.attr_type_ == FLOATS) {
      float *res = (float *)malloc(sizeof(float));
      int this_data = *(int *)this->data_;
      float other_data = *(float *)cell.data_;
      *res = this_data + other_data;
      res_cell.attr_type_ = FLOATS;
      res_cell.set_data((char *)res);
    } else if (attr_type_ == FLOATS && cell.attr_type_ == INTS) {
      float *res = (float *)malloc(sizeof(float));
      float this_data = *(float *)this->data_;
      int other_data = *(int *)cell.data_;
      *res = this_data + other_data;
      res_cell.attr_type_ = FLOATS;
      res_cell.set_data((char *)res);
    } else if ((attr_type_ == INTS || attr_type_ == FLOATS) && cell.attr_type_ == CHARS) {
      float *res = (float *)malloc(sizeof(float));
      *res = *(float *)this->data_ + atof(cell.data_);
      res_cell.attr_type_ = FLOATS;
      res_cell.set_data((char *)res);
    } else if (attr_type_ == CHARS && (cell.attr_type_ == INTS || cell.attr_type_ == FLOATS)) {
       float *res = (float *)malloc(sizeof(float));
      *res = atof(this->data_) + *(float *)cell.data_;
      res_cell.attr_type_ = FLOATS;
      res_cell.set_data((char *)res);
    }
    return res_cell;
  }

  TupleCell operator-(const TupleCell &cell) const {
    TupleCell res_cell;
    res_cell.attr_type_ = NULL_;

    if (this->attr_type_ == NULL_ || cell.attr_type_ == NULL_) {
      return res_cell;
    }
    if (this->attr_type_ == cell.attr_type_) {
      switch (this->attr_type_) {
      case INTS:  {
        int *res = (int *)malloc(sizeof(int));
        *res = *(int *)this->data_ - *(int *)cell.data_;
        res_cell.attr_type_ = INTS;
        res_cell.set_data((char *)res);
      } break;
      case FLOATS: {
        float *res = (float *)malloc(sizeof(float));
        *res = *(float *)this->data_ - *(float *)cell.data_;
        res_cell.attr_type_ = FLOATS;
        res_cell.set_data((char *)res);
      } break;
      case CHARS: {
        float *res = (float *)malloc(sizeof(float));
        *res = atof(this->data_) - atof(cell.data_);
        res_cell.attr_type_ = FLOATS;
        res_cell.set_data((char *)res);
      } break; 
      default:
        break;
      }
    } else if(attr_type_ == INTS && cell.attr_type_ == FLOATS) {
      float *res = (float *)malloc(sizeof(float));
      int this_data = *(int *)this->data_;
      float other_data = *(float *)cell.data_;
      *res = this_data - other_data;
      res_cell.attr_type_ = FLOATS;
      res_cell.set_data((char *)res);
    } else if (attr_type_ == FLOATS && cell.attr_type_ == INTS) {
      float *res = (float *)malloc(sizeof(float));
      float this_data = *(float *)this->data_;
      int other_data = *(int *)cell.data_;
      *res = this_data - other_data;
      res_cell.attr_type_ = FLOATS;
      res_cell.set_data((char *)res);
    } else if ((attr_type_ == INTS || attr_type_ == FLOATS) && cell.attr_type_ == CHARS) {
      float *res = (float *)malloc(sizeof(float));
      *res = *(float *)this->data_ - atof(cell.data_);
      res_cell.attr_type_ = FLOATS;
      res_cell.set_data((char *)res);
    } else if (attr_type_ == CHARS && (attr_type_ == INTS || attr_type_ == FLOATS)) {
       float *res = (float *)malloc(sizeof(float));
      *res = atof(this->data_) - *(float *)cell.data_;
      res_cell.attr_type_ = FLOATS;
      res_cell.set_data((char *)res);
    }
    return res_cell;
  }

  TupleCell operator/(const TupleCell &cell) const {
    TupleCell res_cell;
    res_cell.attr_type_ = NULL_;
    if (this->attr_type_ == NULL_ || cell.attr_type_ == NULL_) {
      return res_cell;
    }
    const double epsilon = 1E-6;

    if (this->attr_type_ == cell.attr_type_) {
      switch (this->attr_type_) {
      case INTS:  {
        float *res = (float *)malloc(sizeof(int));
        int this_data = *(int *)this->data_;
        int other_data = *(int *)cell.data_;
        if (other_data != 0) {
          *res = this_data / (other_data + .0);
          res_cell.attr_type_ = FLOATS;
          res_cell.set_data((char *)res);
        }
      } break;
      case FLOATS: {
        float *res = (float *)malloc(sizeof(float));
        float this_data = *(float *)this->data_;
        float other_data = *(float *)cell.data_;
        if (other_data > epsilon) {
          *res = this_data / other_data;
          res_cell.attr_type_ = FLOATS;
          res_cell.set_data((char *)res);
        } 
      } break;
      case CHARS: {
        float *res = (float *)malloc(sizeof(float));
        float this_data = atof(this->data_);
        float other_data = atof(cell.data_);
        if (other_data > epsilon) {
          *res = this_data / other_data;
          res_cell.attr_type_ = FLOATS;
          res_cell.set_data((char *)res);
        }
      } break;
      default:
        break;
      }
    } else if(attr_type_ == INTS && cell.attr_type_ == FLOATS) {
      float *res = (float *)malloc(sizeof(float));
      int this_data = *(int *)this->data_;
      float other_data = *(float *)cell.data_;
      if (other_data > epsilon) {
        *res = this_data / other_data;
        res_cell.attr_type_ = FLOATS;
        res_cell.set_data((char *)res);
      }
    } else if (attr_type_ == FLOATS && cell.attr_type_ == INTS) {
      float *res = (float *)malloc(sizeof(float));
      float this_data = *(float *)this->data_;
      int other_data = *(int *)cell.data_;
      if (other_data != 0) {
        *res = this_data / other_data;
        res_cell.attr_type_ = FLOATS;
        res_cell.set_data((char *)res);
      }
    } else if ((attr_type_ == INTS || attr_type_ == FLOATS) && cell.attr_type_ == CHARS) {
      float *res = (float *)malloc(sizeof(float));
      float this_data = *(float *)this->data_;
      float other_data = atof(cell.data_);
      if (other_data > epsilon) {
        *res = this_data / other_data;
        res_cell.attr_type_ = FLOATS;
        res_cell.set_data((char *)res);
      }
    } else if (attr_type_ == CHARS && (cell.attr_type_ == INTS || cell.attr_type_ == FLOATS)) {
      float *res = (float *)malloc(sizeof(float));
      float this_data = atof(this->data_);
      float other_data = *(float *)cell.data_;
      if (other_data > epsilon) {
        *res = this_data / other_data;
        res_cell.attr_type_ = FLOATS;
        res_cell.set_data((char *)res);
      }
    }
    return res_cell;
  }

  TupleCell operator*(const TupleCell &cell) const {
    TupleCell res_cell;
    res_cell.attr_type_ = NULL_;
    if (this->attr_type_ == NULL_ || cell.attr_type_ == NULL_) {
      return res_cell;
    }
    if (this->attr_type_ == cell.attr_type_) {
      switch (this->attr_type_) {
      case INTS:  {
        int *res = (int *)malloc(sizeof(int));
        *res = *(int *)this->data_ * *(int *)cell.data_;
        res_cell.attr_type_ = INTS;
        res_cell.set_data((char *)res);
      } break;
      case FLOATS: {
        float *res = (float *)malloc(sizeof(float));
        *res = *(float *)this->data_ * *(float *)cell.data_;
        res_cell.attr_type_ = FLOATS;
        res_cell.set_data((char *)res);
      } break;
      case CHARS: {
        float *res = (float *)malloc(sizeof(float));
        *res = atof(this->data_) * atof(cell.data_);
        res_cell.attr_type_ = FLOATS;
        res_cell.set_data((char *)res);
      } break; 
      default: 
        break;
      }
    } else if(attr_type_ == INTS && cell.attr_type_ == FLOATS) {
      float *res = (float *)malloc(sizeof(float));
      int this_data = *(int *)this->data_;
      float other_data = *(float *)cell.data_;
      *res = this_data * other_data;
      res_cell.attr_type_ = FLOATS;
      res_cell.set_data((char *)res);
    } else if (attr_type_ == FLOATS && cell.attr_type_ == INTS) {
      float *res = (float *)malloc(sizeof(float));
      float this_data = *(float *)this->data_;
      int other_data = *(int *)cell.data_;
      *res = this_data * other_data;
      res_cell.attr_type_ = FLOATS;
      res_cell.set_data((char *)res);
    } else if ((attr_type_ == INTS || attr_type_ == FLOATS) && cell.attr_type_ == CHARS) {
      float *res = (float *)malloc(sizeof(float));
      float this_data = *(float *)this->data_;
      float other_data = atof(cell.data_);
      *res =  this_data * other_data;
      res_cell.attr_type_ = FLOATS;
      res_cell.set_data((char *)res);
    } else if (attr_type_ == CHARS && (cell.attr_type_ == INTS || cell.attr_type_ == FLOATS)) {
      float *res = (float *)malloc(sizeof(float));
      float this_data = atof(this->data_);
      float other_data = *(float *)cell.data_;
      *res =  this_data * other_data;
      res_cell.attr_type_ = FLOATS;
      res_cell.set_data((char *)res);
    } 
    return res_cell;
  }

private:
  AttrType attr_type_ = UNDEFINED;
  int length_ = -1;
  char *data_ = nullptr; // real data. no need to move to field_meta.offset
};
