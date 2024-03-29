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
// Created by Meiyi 
//

#include <mutex>
#include "sql/parser/parse.h"
#include "rc.h"
#include "common/log/log.h"

RC parse(char *st, Query *sqln);

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name)
{
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->alias = nullptr;
  relation_attr->attribute_name = strdup(attribute_name);
  relation_attr->agg_func = AggFunc::NONE;
  relation_attr->func = NONE_;
  relation_attr->is_num = 0;
  relation_attr->is_value = 0;
  relation_attr->is_has_second_value = 0;
}


void relation_attr_init_with_alias(RelAttr *relation_attr, const char *relation_name, const char *attribute_name, const char *alias_name)
{
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  if (alias_name != nullptr) {
    relation_attr->alias = strdup(alias_name);
  } else {
    relation_attr->alias = nullptr;
  }
  relation_attr->attribute_name =  strdup(attribute_name);
  relation_attr->agg_func = AggFunc::NONE;
  relation_attr->func = NONE_;
  relation_attr->is_num = 0;
  relation_attr->is_value = 0;
  relation_attr->is_has_second_value = 0;
}


void relation_attr_init_with_func(
    RelAttr *relation_attr, const char *relation_name, const char *attribute_name, Func func, const char *alias)
{
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
  relation_attr->func = func;
  relation_attr->is_num = 0;
  relation_attr->is_value = 0;
  relation_attr->is_has_second_value = 0;
  if (alias != nullptr) {
    relation_attr->alias = strdup(alias);
  } else {
    relation_attr->alias = nullptr;
  }
}

void relation_attr_init_with_func_value(RelAttr *relation_attr, Func func, Value *value, Value *second_value, const char *alias) {
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
  relation_attr->func = func;
  relation_attr->is_num = 0;
  relation_attr->is_value = 1;
  relation_attr->value = *value;
  if (second_value != nullptr) {
    relation_attr->second_value = *second_value;
    relation_attr->is_has_second_value = 1;
  } else {
    relation_attr->is_has_second_value = 0;
  }
  if (alias != nullptr) {
    relation_attr->alias = strdup(alias);
  } else {
    relation_attr->alias = nullptr;
  }
}

void relation_attr_init_with_func_append_value(RelAttr *relation_attr, Value *value) {
  relation_attr->is_has_second_value = 1;
  relation_attr->second_value = *value; 
}

void relation_attr_destroy(RelAttr *relation_attr)
{
  if (relation_attr->relation_name != nullptr) {
    free(relation_attr->relation_name);
  } 
  if (relation_attr->attribute_name != nullptr) {
    free(relation_attr->attribute_name);
  }
  if (relation_attr->alias != nullptr) {
    free(relation_attr->alias);
  }
  if (relation_attr->is_value) {
    value_destroy(&relation_attr->value);
  } 
  if (relation_attr->is_has_second_value) {
    value_destroy(&relation_attr->second_value);
  }
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
  relation_attr->alias = nullptr;
  relation_attr->func = NONE_;
  relation_attr->is_value = 0;
  relation_attr->is_has_second_value = 0;
  relation_attr->is_num = 0;
}

void relation_attr_init_with_agg(RelAttr *relation_attr, const char *relation_name,
                                  const char *attribute_name, AggFunc agg, const char *alias_name) 
{
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  if (alias_name != nullptr) {
    relation_attr->alias = strdup(alias_name);
  } else {
    relation_attr->alias = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
  relation_attr->agg_func = agg;
  relation_attr->is_num = 0;
  relation_attr->func = NONE_;
  relation_attr->is_value = 0;
  relation_attr->is_has_second_value = 0;
}
void relation_attr_init_with_agg_num(RelAttr *relation_attr, AggFunc agg, int num, const char *alias_name) {
  if (alias_name != nullptr) {
    relation_attr->alias = strdup(alias_name);
  } else {
    relation_attr->alias = nullptr;
  }
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
  relation_attr->agg_func = agg;
  relation_attr->is_num = 1;
  relation_attr->num = num;
  relation_attr->func = NONE_;
  relation_attr->is_value = 0;
  relation_attr->is_has_second_value = 0;
}

static int8_t day_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30 ,31, 30, 31};

int check_date(int y, int m, int d) {
  bool is_leapyear = ((y % 4 == 0) && (y % 100 != 0)) || (y%400 == 0);
  int date = y * 10000 + m * 100 + d;
  if (m < 1 || m > 12) {
    return -1;
  }

  if (m == 2 && d == 29 && is_leapyear) {
    return date; 
  }

  if (d > day_month[m] || d < 1) {
    return -1;
  }
  return date;
}

void value_init_integer(Value *value, int v)
{
  value->type = INTS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
  value->set_size = sizeof(v);
}
void value_init_float(Value *value, float v)
{
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
  value->set_size = sizeof(v);
}
void value_init_string(Value *value, const char *v)
{
  value->type = CHARS;
  value->data = strdup(v);
  value->set_size = strlen(v) + 1;
}

int to_date(const char *v) {
  int y = 0, m = 0, d = 0;
  sscanf(v, "%d-%d-%d", &y, &m, &d);
  return check_date(y, m, d);
}

int value_init_date(Value *value, const char *v) {
  value->type = DATES; 
  int date = to_date(v);
  if (date == -1) {
    value_init_string(value, v);
    return -1;
  }
  int *p_date = (int *)malloc(sizeof(int));
  *p_date = date;
  value->data = p_date;
  value->set_size = strlen(v) + 1;
  return 0;
}

void value_destroy(Value *value)
{
  if (value->type == UNDEFINED && value->data == nullptr) {
    return;
  }
  value->type = UNDEFINED;
  free(value->data);
  value->data = nullptr;
  value->set_size = 0;
}

void value_init_agg(Value *value, RelAttr *v) {
  value->type = AGGFUNC;
  value->data = malloc(sizeof(RelAttr));
  memcpy(value->data, v, sizeof(RelAttr));
  value->set_size = 0;
}
void value_init_select(Value *value, Selects *v) {
  value->type = SELECTS;
  value->data = malloc(sizeof(Selects));
  memcpy(value->data, v, sizeof(Selects));
  value->set_size = 0;
}
void value_init_null(Value *value) {
  value->type = NULL_;
  value->data = nullptr;
  value->set_size = 0;
}

void value_init_set(Value *value, Value values[], int begin, int set_size) {

  value->type = SETS;
  value->data = malloc(set_size * sizeof(Value));
  memcpy(value->data, values + begin, set_size * sizeof(Value));
  value->set_size = set_size;
}

void order_by_init(OrderBy *order_by, RelAttr *relation, int order) {
   // 0是asc，1是desc
   order_by->order = order;
   order_by->attr = *relation;
}


void order_by_destroy(OrderBy *order_by) {
  order_by->order = 0;
}

void switch_comp_op(CompOp *comp) {
    switch (*comp) {
    case EQUAL_TO:    { *comp = EQUAL_TO; }    break;
    case LESS_EQUAL:  { *comp = GREAT_EQUAL; }  break;
    case NOT_EQUAL:   { *comp = NOT_EQUAL; }   break;
    case LESS_THAN:   { *comp = GREAT_THAN; } break;
    case GREAT_EQUAL: { *comp = LESS_EQUAL; }   break;
    case GREAT_THAN:  { *comp = LESS_THAN; }  break;
    default: break;
    }
}


void having_init(Having *having, RelAttr *attr, Value *value, CompOp comp, int swap) {
  having->attr = *attr;
  having->value = *value;
  if (swap == 1) {
    switch_comp_op(&comp);
  }
  having->comp = comp;
}

void having_destroy(Having *having) {
  relation_attr_destroy(&having->attr);
  value_destroy(&having->value);
}

void condition_init(Condition *condition, CompOp comp, int left_is_attr, RelAttr *left_attr, Value *left_value,
    int right_is_attr, RelAttr *right_attr, Value *right_value)
{
  condition->comp = comp;
  condition->left_is_attr = left_is_attr;
  if (left_is_attr == 1) {
    condition->left_attr = *left_attr;
  } else if (left_is_attr == 0){
    condition->left_value = *left_value;
  }

  condition->right_is_attr = right_is_attr;
  if (right_is_attr) {
    condition->right_attr = *right_attr;
  } else {
    condition->right_value = *right_value;
  }
  condition->left_expr = nullptr;
  condition->right_expr = nullptr;
}
void condition_destroy(Condition *condition)
{
  if (condition->left_is_attr == 1) {
    relation_attr_destroy(&condition->left_attr);
  } else if (condition->left_is_attr == 0){
    value_destroy(&condition->left_value);
  }
  if (condition->right_is_attr == 1) {
    relation_attr_destroy(&condition->right_attr);
  } else if (condition->right_is_attr == 0){
    value_destroy(&condition->right_value);
  }
  if (condition->left_is_attr == -1 && condition->left_expr != nullptr) {
    expression_destroy(condition->left_expr);
  }
  if (condition->right_is_attr == -1 && condition->right_expr != nullptr) {
    expression_destroy(condition->right_expr);
  }
}

void condition_init_with_exp(Condition *condition, CompOp comp, Exp *left_expr, Exp *right_expr) {
  condition->comp = comp;

  // 如果表达式为叶子节点，即Value或RelAttr
  if (left_expr->expr_type == NodeType::VAL) {
    condition->left_value = *left_expr->value;
    condition->left_is_attr = 0;
    condition->left_attr.is_value = 0;
    condition->left_attr.is_has_second_value = 0;
    condition->left_attr.func = NONE_;
  } else if (left_expr->expr_type == NodeType::ATTR) {
    condition->left_attr = *left_expr->attr; 
    condition->left_is_attr = 1;
  } else {
    condition->left_expr = left_expr;
    condition->left_is_attr = -1;
    condition->left_attr.is_value = 0;
    condition->left_attr.is_has_second_value = 0;
    condition->left_attr.func = NONE_;
  }

  if (right_expr->expr_type == NodeType::VAL) {
    condition->right_value = *right_expr->value;
    condition->right_is_attr = 0;
    condition->right_attr.is_value = 0;
    condition->right_attr.is_has_second_value = 0;
    condition->right_attr.func = NONE_;
  } else if (right_expr->expr_type == NodeType::ATTR) {
    condition->right_attr = *right_expr->attr;
    condition->right_is_attr = 1;
  } else {
    condition->right_expr = right_expr;
    condition->right_is_attr = -1;
    condition->right_attr.is_value = 0;
    condition->right_attr.is_has_second_value = 0;
    condition->right_attr.func = NONE_;
  }
}

Exp *create_expression(Exp *left_expr, Exp *right_expr, Value *value, RelAttr *relation_attr, NodeType node_type) {
  Exp *exp = (Exp *)malloc(sizeof(Exp));
  exp->expr_type = node_type;


  if (value != nullptr) {
    exp->value = (Value *)malloc(sizeof(Value));
    *exp->value = *value;
  } else {
    exp->value = nullptr;
  }
  if (relation_attr != nullptr) {
    exp->attr = (RelAttr *)malloc(sizeof(RelAttr));
    *exp->attr = *relation_attr;
  } else {
    exp->attr = nullptr;
  }
  
  if (right_expr != nullptr) {
    exp->right_expr = right_expr;
  } else {
    exp->right_expr = nullptr;
  }

  if (left_expr != nullptr) {
    exp->left_expr = left_expr;
  } else {
    exp->left_expr = nullptr;
  }
  exp->lbrace = 0;
  exp->rbrace = 0; 
  return exp;
}

// 在条件语句中出现的attribute_name，但是select中没有出现
// 可能导致内存没有回收，value也是一样
void expression_destroy(Exp *exp)
{
  if (exp->expr_type == NO_EXP) {
    return;
  }
  
  if (exp->expr_type == VAL) {
    value_destroy(exp->value);
    exp->left_expr = nullptr;
    exp->right_expr = nullptr;
    return;
  }
  exp->expr_type = NO_EXP;
  if (exp->left_expr != nullptr) {
    expression_destroy(exp->left_expr);
    exp->left_expr = nullptr;
  }

  if (exp->right_expr != nullptr) {
    expression_destroy(exp->right_expr);
    exp->right_expr = nullptr;
  }
}
void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, int nullable)
{
  attr_info->name = strdup(name);
  attr_info->type = type;
  attr_info->length = length;
  attr_info->nullable = nullable;
}
void attr_info_destroy(AttrInfo *attr_info)
{
  if (attr_info->name != nullptr) {
    free(attr_info->name);
  }
  attr_info->name = nullptr;
}

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr)
{
  selects->attributes[selects->attr_num++] = *rel_attr;
}
void selects_append_relation(Selects *selects, const char *relation_name)
{
  selects->alias[selects->relation_num] = nullptr;
  selects->relations[selects->relation_num++] = strdup(relation_name);
}

void selects_append_relation_with_alias(Selects *selects, const char *relation_name, const char *alias_name) {
  if (alias_name != nullptr) {
    selects->alias[selects->relation_num] = strdup(alias_name);
  } else {
    selects->alias[selects->relation_num] = nullptr; 
  }
  selects->relations[selects->relation_num++] = strdup(relation_name);
}


// 主要是针对聚合函数的表达式计算
// 不考虑别名
void selects_append_expressions(Selects *selects, Exp *expression[], size_t begin, size_t expr_num) {
  assert(expr_num <= sizeof(selects->exp) / sizeof(expression[0]));
  for (size_t i=0; i < expr_num; i++ ){
    selects->exp[i] = expression[i+begin];
  }
  selects->expr_num = expr_num;
}

void selects_append_attribute_list(Selects *selects, RelAttr attr_list[], size_t begin, size_t attr_num) {
  assert(attr_num <= sizeof(selects->attributes) / sizeof(attr_list[0]));
  for (size_t i = 0; i < attr_num; i++) {
    selects->attributes[i] = attr_list[i + begin];
  }
  selects->attr_num = attr_num;
}

void selects_append_conditions(Selects *selects, Condition conditions[], size_t begin, size_t condition_num)
{
  assert(condition_num <= sizeof(selects->conditions) / sizeof(selects->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    selects->conditions[i] = conditions[i + begin];
    if (selects->conditions[i].left_is_attr && selects->conditions[i].left_attr.relation_name == nullptr) {
      selects->conditions[i].left_attr.relation_name = strdup(selects->relations[0]);
    } 
    if (selects->conditions[i].right_is_attr && selects->conditions[i].right_attr.relation_name == nullptr) {
      selects->conditions[i].right_attr.relation_name = strdup(selects->relations[0]);
    }
  }
  selects->condition_num = condition_num;
}

void selects_append_order_by(Selects *selects, OrderBy *order_by) {
  selects->order_bys[selects->order_num++] = *order_by;
}


void selects_append_group_by(Selects *selects, RelAttr *attr) {
  selects->group_bys[selects->group_num++] = *attr;
}


void selects_append_having(Selects *selects, Having *having) {
  selects->having = *having;
  selects->has_having = 1;
}

void selects_destroy(Selects *selects)
{
  for (size_t i = 0; i < selects->attr_num; i++) {
    relation_attr_destroy(&selects->attributes[i]);
  }
  selects->attr_num = 0;

  for (size_t i = 0; i < selects->relation_num; i++) {
    free(selects->relations[i]);
    free(selects->alias[i]);
    selects->relations[i] = NULL;
  }
  selects->relation_num = 0;

  for (size_t i = 0; i < selects->condition_num; i++) {
    condition_destroy(&selects->conditions[i]);
  }
  selects->expr_num = 0;

  for (size_t i=0; i<selects->expr_num; i++) {
    expression_destroy(selects->exp[i]);
  }
  selects->condition_num = 0;

  for (size_t i=0; i<selects->order_num; i++) {
    order_by_destroy(&selects->order_bys[i]);
  }
  selects->order_num = 0;
  for (size_t i=0; i<selects->group_num; i++) {
    relation_attr_destroy(&selects->group_bys[i]);
  }
  selects->group_num = 0;
}

void insert_init(Insert *insert, Value values[], size_t value_num) {
  assert(value_num <= sizeof(insert->values) / sizeof(insert->values[0]));
  memcpy(insert->values, values, sizeof(Value) * value_num);
  insert->value_num = value_num;
}

void insert_destroy(Insert *insert) {
  for (size_t i = 0; i < insert->value_num; i++) {
    value_destroy(&insert->values[i]);
  }
  insert->value_num = 0;
}

void inserts_init(Inserts *inserts, const char *relation_name, Insert insert_list[], size_t insert_num)
{
  assert(insert_num <= sizeof(inserts->inserts) / sizeof(inserts->inserts[0]));

  inserts->relation_name = strdup(relation_name);
  for (size_t i = 0; i < insert_num; i++) {
    inserts->inserts[i] = insert_list[i];
  }
  inserts->insert_num = insert_num;
}
void inserts_destroy(Inserts *inserts)
{
  for (size_t i=0; i<inserts->insert_num; i++) {
    insert_destroy(&inserts->inserts[i]);
  }
  free(inserts->relation_name);
  inserts->relation_name = nullptr;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name)
{
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(deletes->conditions) / sizeof(deletes->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    deletes->conditions[i] = conditions[i];
  }
  deletes->condition_num = condition_num;
}
void deletes_destroy(Deletes *deletes)
{
  for (size_t i = 0; i < deletes->condition_num; i++) {
    condition_destroy(&deletes->conditions[i]);
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, Value *value,
    Condition conditions[], size_t condition_num)
{
  updates->relation_name = strdup(relation_name);
  updates->attribute_name = strdup(attribute_name);
  updates->value = *value;

  assert(condition_num <= sizeof(updates->conditions) / sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}

void updates_destroy(Updates *updates)
{
  free(updates->relation_name);
  free(updates->attribute_name);
  updates->relation_name = nullptr;
  updates->attribute_name = nullptr;

  value_destroy(&updates->value);

  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
}

void updates_select_init(Updatess *updates, const char *relation_name, Condition conditions[], size_t condition_num) {
  updates->relation_name = strdup(relation_name);
  assert(condition_num <= sizeof(updates->conditions) / sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}

void updates_append_value(Updatess *updates, Value *value, const char *attribute_name) {
  updates->attribute_names[updates->attr_num] = strdup(attribute_name);
  updates->values[updates->attr_num] = *value;
  updates->attr_num++;
}

void updates_select_destroy(Updatess *updates) {
  free(updates->relation_name);
  updates->relation_name = nullptr;
  for (size_t i = 0; i < updates->attr_num; i++) {
    free(updates->attribute_names[i]);
    updates->attribute_names[i] = nullptr;
    value_destroy(&updates->values[i]);
  }
  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
  updates->attr_num = 0;
}


void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info)
{
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}

void create_table_init_name(CreateTable *create_table, const char *relation_name)
{
  create_table->relation_name = strdup(relation_name);
}

void create_table_destroy(CreateTable *create_table)
{
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name)
{
  drop_table->relation_name = strdup(relation_name);
}

void drop_table_destroy(DropTable *drop_table)
{
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

void create_index_append_attribute_name(CreateIndex *create_index, const char *attr_name) {
  create_index->attribute_name[create_index->attr_num] = strdup(attr_name);
  ++create_index->attr_num;
}

void create_index_init(
    CreateIndex *create_index, const char *index_name, const char *relation_name, int is_unique)
{
  create_index->index_name = strdup(index_name);
  create_index->relation_name = strdup(relation_name);
  create_index->is_unique = is_unique;
}

void create_index_destroy(CreateIndex *create_index)
{
  free(create_index->index_name);
  free(create_index->relation_name);
  for (size_t i = 0; i < create_index->attr_num; i++) {
    free(create_index->attribute_name[i]);
  }
  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;
  create_index->attr_num = 0;
}

void drop_index_init(DropIndex *drop_index, const char *index_name)
{
  drop_index->index_name = strdup(index_name);
}

void drop_index_destroy(DropIndex *drop_index)
{
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void show_index_init(ShowIndex *show_index, const char *relation_name) {
  show_index->relation_name = strdup(relation_name);
}

void show_index_destroy(ShowIndex *show_index) {
  free((char *)show_index->relation_name);
  show_index->relation_name = nullptr;
}

void desc_table_init(DescTable *desc_table, const char *relation_name)
{
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table)
{
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name)
{
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void load_data_destroy(LoadData *load_data)
{
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

void query_init(Query *query)
{
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create()
{
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

void query_reset(Query *query)
{
  switch (query->flag) {
    case SCF_SELECT: {
      selects_destroy(&query->sstr.selection);
    } break;
    case SCF_INSERT: {
      inserts_destroy(&query->sstr.insertion);
    } break;
    case SCF_DELETE: {
      deletes_destroy(&query->sstr.deletion);
    } break;
    case SCF_UPDATE: {
      updates_select_destroy(&query->sstr.updates);
    } break;
    case SCF_CREATE_TABLE: {
      create_table_destroy(&query->sstr.create_table);
    } break;
    case SCF_DROP_TABLE: {
      drop_table_destroy(&query->sstr.drop_table);
    } break;
    case SCF_CREATE_INDEX: {
      create_index_destroy(&query->sstr.create_index);
    } break;
    case SCF_DROP_INDEX: {
      drop_index_destroy(&query->sstr.drop_index);
    } break;
    case SCF_SHOW_INDEX: {
      show_index_destroy(&query->sstr.show_index);
    } break;
    case SCF_SYNC: {

    } break;
    case SCF_SHOW_TABLES:
      break;

    case SCF_DESC_TABLE: {
      desc_table_destroy(&query->sstr.desc_table);
    } break;

    case SCF_LOAD_DATA: {
      load_data_destroy(&query->sstr.load_data);
    } break;
    case SCF_CLOG_SYNC:
    case SCF_BEGIN:
    case SCF_COMMIT:
    case SCF_ROLLBACK:
    case SCF_HELP:
    case SCF_EXIT:
    case SCF_ERROR:
    case SCF_INVALID_DATE:
      break;
  }
}

void query_destroy(Query *query)
{
  query_reset(query);
  free(query);
}
#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern "C" int sql_parse(const char *st, Query *sqls);

RC parse(const char *st, Query *sqln)
{

  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else if (sqln->flag == SCF_INVALID_DATE)
    return FORMAT;
  else
    return SUCCESS;
}