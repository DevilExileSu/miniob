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
  for (size_t i=0; i<stat_.size(); i++) {
    stat_[i].reset();
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  return rc;
}

RC AggregateOperator::next()
{
  RC rc = RC::SUCCESS;
  while (RC::SUCCESS == (rc = children_[0]->next())) {
    Tuple *tuple = children_[0]->current_tuple();
    if (tuple == nullptr) {
        return RC::INTERNAL;
    }
    for (int i=0; i< rel_attrs_.size(); i++) {
        if (rel_attrs_[i].attribute_name == nullptr) {
            continue;
        }
        TupleCell cell;
        tuple->find_cell(query_fields_[i], cell);
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

void AggregateOperator::print_header_at(std::ostream &os, int i, bool is_multi_table) {
    if (rel_attrs_[i].alias == nullptr) {
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
        } else {
            if (is_multi_table) {
                os << rel_attrs_[i].relation_name << ".";
            }
            os << rel_attrs_[i].attribute_name << ")";
        }
    } else {
        os << rel_attrs_[i].alias;
    }
}

void AggregateOperator::print_header(std::ostream &os) {
    for (int i=0; i < rel_attrs_.size(); i++) {
        if (i != 0) {
            os << " | ";
        }
        if (rel_attrs_[i].alias == nullptr) {
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
        } else {
            os << rel_attrs_[i].alias;
        }
    }
    os << '\n';
}

void AggregateOperator::to_string_at(std::ostream &os, int i) {
        if (rel_attrs_[i].attribute_name == nullptr) {
            os << rel_attrs_[i].num;
            return;
        }
        if (stat_[i].is_null() && rel_attrs_[i].agg_func != AggFunc::COUNT) {
            os << "NULL";
            return;
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


bool AggregateOperator::do_prdicate(HavingCondition &having) {
    AggFunc agg_func = having.agg_func;
    CustomizeTuple tuple = get_result_tuple();
    TupleCell cell1;
    tuple.find_cell(having.field, cell1, agg_func);
    TupleCell cell2 = having.value_cell;
    bool has_null = (cell1.attr_type() == NULL_);
    int compare = cell1.compare(cell2);
    switch (having.comp) {
        case EQUAL_TO: {
            return (0 == compare && !has_null) ; 
        } 
        case LESS_EQUAL: {
            return (compare <= 0 && !has_null); 
        }
        case NOT_EQUAL: {
            return (compare != 0 && !has_null);
        }
        case LESS_THAN: {
            return (compare < 0 && !has_null);
        }
        case GREAT_EQUAL: {
            return (compare >= 0 && !has_null);
        }
        case GREAT_THAN: {
            return (compare > 0 && !has_null);
        }
        default:
            return false;
    }

}
