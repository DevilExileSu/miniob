#pragma once

#include <cmath>

#include "sql/operator/operator.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/parser/parse_defs.h"
#include "util/comparator.h"
#include "util/util.h"


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

  Value get_result(Field field) override {
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
  void print_header_at(std::ostream &os, int i);
  void to_string(std::ostream &os);
  void to_string_at(std::ostream &os, int i);
  bool is_null(int index) { return stat_[index].is_null() && rel_attrs_[index].agg_func != AggFunc::COUNT; }
  CustomizeTuple get_result_tuple() {
    CustomizeTuple tuple(stat_, query_fields_);
    return tuple;
  }
private:
  // 多少个聚合函数
  const std::vector<RelAttr> rel_attrs_;
  const std::vector<Field> query_fields_;
  std::vector<AggregateStat> stat_;
};