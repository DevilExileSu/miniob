#include "sql/operator/aggregate_operator.h"
#include "common/log/log.h"
#include "storage/record/record.h"
#include "storage/common/table.h"
#include "util/util.h"


RC AggregateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("Aggregate operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC AggregateOperator::next()
{
    RC rc = children_[0]->next();
    if (RC::SUCCESS != rc) {
        return rc;
    }
    if (!rel_attrs_.empty()) {
        Tuple *tuple = children_[0]->current_tuple();
        if (tuple == nullptr) {
            return RC::INTERNAL;
        }
        for (int i = 0; i < rel_attrs_.size(); i++) {
            if (rel_attrs_[i].attribute_name == nullptr) {
                continue;
            }
            TupleCell cell;
            tuple->find_cell(query_fields_[rel_attrs_.size() - i - 1], cell);
            stat_[i].add_tuple(cell);
        }
    }
    return rc;
}

RC AggregateOperator::close()
{
    children_[0]->close();
    return RC::SUCCESS;
}

Tuple *AggregateOperator::current_tuple()
{
    return children_[0]->current_tuple();
   
}

void AggregateOperator::print_header(std::ostream &os) {
    for (int i=0; i < rel_attrs_.size(); i++) {
        if (i != 0) {
            os << " | ";
        }
        switch (rel_attrs_[i].agg_func) {
            case MAX: {
                os << "max(";
                break;
            }
            case MIN: {
                os << "min(";
                break;
            }
            case AVG: {
                os << "avg(";
                break;
            }
            case COUNT: {
                os << "count(" ;
                break;
            }
            case SUM: {
                os<< "sum(";
                break; 
            }
            default: {
                os << "error()";
                break;             
            }
        }
        if (rel_attrs_[i].attribute_name == nullptr) {
            os << rel_attrs_[i].num << ")";
            continue;
        }
        os << rel_attrs_[i].attribute_name << ")";
    }
    os << '\n';
}

void AggregateOperator::to_string(std::ostream &os) {
    for (int i=0; i<rel_attrs_.size(); i++) {
        if (i != 0) {
            os << " | ";
        }
        if (rel_attrs_[i].attribute_name == nullptr) {
            os << rel_attrs_[i].num;
            continue;
        }
        if (stat_[i].is_null() && rel_attrs_[i].agg_func != AggFunc::COUNT) {
            os << "NULL";
            continue;
        }
        switch (rel_attrs_[i].agg_func) {
            case MAX: {
                os << stat_[i].max();
                break;
            }
            case MIN: {
                os << stat_[i].min();
                break;
            }
            case AVG: {
                os << double2string(stat_[i].avg());
                break;
            }
            case COUNT: {
                if (0 == strcmp(rel_attrs_[i].attribute_name, "*")) {
                    os << stat_[i].count();
                } else {
                    os << stat_[i].not_null_count();
                }
                break;
            }
            case SUM: {
                os << double2string(stat_[i].sum());
                break; 
            }
            default: {
                os << "x";
                break;             
            }
        }
    }
}