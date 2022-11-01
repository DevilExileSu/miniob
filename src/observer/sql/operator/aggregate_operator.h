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

  Value get_result(Field field) override{
    Value res;
    // 作为子查询的返回结果，只可能返回一列，所以没有问题
    if (rel_attrs_.size() > 1 || is_null(0)) {
      value_init_null(&res);
      return res;
    } 
    switch (rel_attrs_[0].agg_func) {
      case MAX: {
        value_init_string(&res, stat_[0].max().c_str());
      } break;
      case MIN: {
        value_init_string(&res, stat_[0].min().c_str());
      } break;
      case AVG: {
        value_init_float(&res, stat_[0].avg());
      } break;
      case COUNT: {
        if (0 == strcmp(rel_attrs_[0].attribute_name, "*")) {
          value_init_integer(&res, stat_[0].count());
        } else {
          value_init_integer(&res, stat_[0].not_null_count());
        }
      } break;
      case SUM: {
        value_init_float(&res, stat_[0].sum());
      } break; 
      default: {
        value_init_null(&res);
      } break;
    }
    return res; 
  }

  Tuple * current_tuple() override {
    return nullptr;
  }

  void print_header(std::ostream &os);
  void to_string(std::ostream &os);
  bool is_null(int index) { return stat_[index].is_null() && rel_attrs_[index].agg_func != AggFunc::COUNT; }

private:
  // 多少个聚合函数
  const std::vector<RelAttr> rel_attrs_;
  const std::vector<Field> query_fields_;
  std::vector<AggregateStat> stat_;
};