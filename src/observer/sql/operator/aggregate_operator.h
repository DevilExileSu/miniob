#pragma once

#include <cmath>

#include "sql/operator/operator.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/parser/parse_defs.h"
#include "util/comparator.h"
#include "util/util.h"


class AggregateStat {

public:
  void add_tuple(TupleCell &cell) {
    // 获取cell的数据
    char *data = const_cast<char *>(cell.data());
    // 按照data的数据类型相应的转换，这里为了统计，全部转换为浮点型
    if (data_type_ == AttrType::UNDEFINED) {
      data_type_ = cell.attr_type();
    }

    float data_f = 0.0;
    switch (data_type_) {
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

    ++count_;
    sum_ += data_f;
  }

  std::string max() { 
    switch (data_type_) {
      case INTS:
        return int2string(*(int *)max_);
      case CHARS: 
        return std::string(max_);
      case FLOATS:
        return double2string(*(float *)max_);
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
      default:
        return std::string("error");
    } 
  }
  float sum() { return sum_; }
  float avg() { return sum_ / count_; }
  int count() { return count_; }



private:
  AttrType data_type_ = AttrType::UNDEFINED;
  char *min_ = nullptr;
  char *max_ = nullptr;
  int count_ = 0;
  float sum_ = .0;
};

class AggregateOperator : public Operator
{
public:
  AggregateOperator(const std::vector<RelAttr> &rel_attrs, const std::vector<Field> &fields)
    : rel_attrs_(rel_attrs), query_fields_(fields)
  {
    AggregateStat stat;
    for (int i=0; i<rel_attrs.size(); i++) {
      stat_.emplace_back(stat);
    }
  }

  virtual ~AggregateOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  // 调用current_tuple时，直接传递ProjectOperator当前的tuple
  Tuple * current_tuple() override;

  void print_header(std::ostream &os);
  void to_string(std::ostream &os);


private:
  // 多少个聚合函数
  const std::vector<RelAttr> rel_attrs_;
  const std::vector<Field> query_fields_;
  std::vector<AggregateStat> stat_;
};