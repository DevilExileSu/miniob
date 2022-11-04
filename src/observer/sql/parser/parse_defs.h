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

#ifndef __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
#define __OBSERVER_SQL_PARSER_PARSE_DEFS_H__

#include <stddef.h>

#define MAX_NUM 20
#define MAX_REL_NAME 20
#define MAX_ATTR_NAME 20
#define MAX_ERROR_MESSAGE 20
#define MAX_DATA 50


typedef enum {
  ADD,
  SUB,
  MUL,
  DIV,
  VAL,
  ATTR,
  NO_EXP,
} NodeType;

typedef enum {
  NONE,
  MAX,
  MIN,
  COUNT,
  AVG,
  SUM,
} AggFunc;


//属性结构体
typedef struct _Attr {
  char *relation_name;   // relation name (may be NULL) 表名
  char *attribute_name;  // attribute name              属性名
  char *alias;           // alias name                  别名
  AggFunc agg_func; 
  int is_num;
  int num;
} RelAttr;

typedef enum {
  EQUAL_TO,     //"="     0
  LESS_EQUAL,   //"<="    1
  NOT_EQUAL,    //"<>"    2
  LESS_THAN,    //"<"     3
  GREAT_EQUAL,  //">="    4
  GREAT_THAN,   //">"     5
  LIKE_MATCH,   // like   6
  NOT_LIKE,     // not like  
  IN_OP,        // in 
  NOT_IN_OP,    // not in
  IS_OP,        // is
  IS_NOT_OP,    // is not
  EXISTS_OP,    // exist
  NOT_EXISTS_OP,// not exist
  NO_OP
} CompOp;

//属性值类型
typedef enum
{
  UNDEFINED,
  CHARS,
  INTS,
  FLOATS,
  DATES,
  TEXTS,
  NULL_,   // 可能参与比较放在TEXTS的后边，下面两个是不参与比较的
  SETS,
  TUPLESET,
  AGGFUNC,
  SELECTS,
} AttrType;

//属性值
typedef struct _Value {
  AttrType type;  // type of value
  void *data;     // value
  int set_size;
} Value;


typedef struct _Exp{
  NodeType expr_type;
  Value *value;
  RelAttr *attr;
  // 用来打印表达式
  int lbrace;
  int rbrace;
  struct _Exp *left_expr;
  struct _Exp *right_expr;

}Exp;

typedef struct _Condition {

  Exp *left_expr;
  Exp *right_expr;
  int left_is_attr;    // TRUE if left-hand side is an attribute
                       // 1时，操作符左边是属性名，0时，是属性值
  Value left_value;    // left-hand side value if left_is_attr = FALSE
  RelAttr left_attr;   // left-hand side attribute
  CompOp comp;         // comparison operator
  int right_is_attr;   // TRUE if right-hand side is an attribute
                       // 1时，操作符右边是属性名，0时，是属性值
  RelAttr right_attr;  // right-hand side attribute if right_is_attr = TRUE 右边的属性
  Value right_value;   // right-hand side value if right_is_attr = FALSE
  
} Condition;

typedef struct _OrderBy {
  RelAttr attr;
  int order;    // 0是asc，1是desc
} OrderBy;


typedef struct _Having {
  RelAttr attr;
  CompOp comp;
  Value value;
} Having;                

// struct of select
typedef struct {
  size_t expr_num;
  Exp *exp[MAX_NUM];
  size_t attr_num;                // Length of attrs in Select clause
  RelAttr attributes[MAX_NUM];    // attrs in Select clause
  size_t relation_num;            // Length of relations in Fro clause
  char *relations[MAX_NUM];       // relations in From clause
  char *alias[MAX_NUM];
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
  size_t order_num;
  OrderBy order_bys[MAX_NUM];
  size_t group_num;
  RelAttr group_bys[MAX_NUM];     
  Having having;
  int has_having;
  int is_and;                     // 条件语句是and还是or
} Selects;


typedef struct {
  size_t value_num;       // Length of values
  Value values[MAX_NUM];  // values to insert
} Insert;

// struct of insert
typedef struct {
  char *relation_name;    // Relation to insert into
  size_t insert_num;       
  Insert inserts[MAX_NUM];  
} Inserts;

// struct of delete
typedef struct {
  char *relation_name;            // Relation to delete from
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Deletes;

// struct of update
typedef struct {
  char *relation_name;            // Relation to update
  char *attribute_name;           // Attribute to update
  Value value;                    // update value
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Updates;

// struct of updates
typedef struct {
  size_t attr_num;
  Value values[MAX_NUM];
  char *attribute_names[MAX_NUM];
  char *relation_name;
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Updatess;

typedef struct {
  char *name;     // Attribute name
  AttrType type;  // Type of attribute
  size_t length;  // Length of attribute
  int nullable;
} AttrInfo;

// struct of craete_table
typedef struct {
  char *relation_name;           // Relation name
  size_t attribute_count;        // Length of attribute
  AttrInfo attributes[MAX_NUM];  // attributes
} CreateTable;

// struct of drop_table
typedef struct {
  char *relation_name;  // Relation name
} DropTable;

// struct of create_index
typedef struct {
  char *index_name;      // Index name
  char *relation_name;   // Relation name
  size_t attr_num;
  int is_unique;
  char *attribute_name[MAX_NUM];  // Attribute name
} CreateIndex;

// struct of  drop_index
typedef struct {
  const char *index_name;  // Index name
} DropIndex;

typedef struct {
  char *relation_name;  // Relation name
} ShowIndex;

typedef struct {
  const char *relation_name;
} DescTable;

typedef struct {
  const char *relation_name;
  const char *file_name;
} LoadData;

union Queries {
  Selects selection;
  Inserts insertion;
  Deletes deletion;
  Updates update;
  Updatess updates;
  CreateTable create_table;
  DropTable drop_table;
  CreateIndex create_index;
  DropIndex drop_index;
  DescTable desc_table;
  LoadData load_data;
  ShowIndex show_index;
  char *errors;
};

// 修改yacc中相关数字编码为宏定义
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT,
  SCF_INVALID_DATE,
  SCF_SHOW_INDEX,
};
// struct of flag and sql_struct
typedef struct Query {
  enum SqlCommandFlag flag;
  union Queries sstr;
} Query;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name);
void relation_attr_init_with_alias(RelAttr *relation_attr, const char *relation_name, const char *attribute_name, const char *alias_name);
void relation_attr_destroy(RelAttr *relation_attr);
void relation_attr_init_with_agg(RelAttr *relation_attr, const char *relation_name, const char *attribute_name, AggFunc agg, const char *alias_name);
void relation_attr_init_with_agg_num(RelAttr *relation_attr, AggFunc agg, int num, const char *alias_name);

void value_init_integer(Value *value, int v);
void value_init_float(Value *value, float v);
void value_init_string(Value *value, const char *v);
int to_date(const char *v);
int value_init_date(Value *value, const char *v);
void value_init_agg(Value *value, RelAttr *v);
void value_init_select(Value *value, Selects *v);
void value_init_null(Value *value);
void value_init_set(Value *value, Value values[], int begin, int set_size);

void order_by_init(OrderBy *order_by, RelAttr *relation, int order);
void order_by_destroy(OrderBy *order_by);

void switch_comp_op(CompOp *comop);
void having_init(Having *having, RelAttr *attr, Value *value, CompOp comp, int swap);
// +、-、*、\、创建(left_expr, right_expr, NULL, NULL, ('+', '-', '*', '\'))
// 叶子节点只能是Value或者RelAttr，Value创建(NULL, NULL, Value, NULL, VAL)，RelAttr创建(NULL, NULL, RelAttr, NULl, RelAttr)
Exp *create_expression(Exp *left_expr, Exp *right_expr, Value *value, RelAttr *relation_attr, NodeType node_type);
// TODO: 释放Exp *
void expression_destroy(Exp *exp);

void value_destroy(Value *value);

void condition_init(Condition *condition, CompOp comp, int left_is_attr, RelAttr *left_attr, Value *left_value,
    int right_is_attr, RelAttr *right_attr, Value *right_value);
void condition_destroy(Condition *condition);
// 给Condition添加Exp
void condition_init_with_exp(Condition *condition, CompOp comp, Exp *left_expr, Exp *right_expr);

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, int nullable);
void attr_info_destroy(AttrInfo *attr_info);

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr);
void selects_append_attribute_list(Selects *selects, RelAttr attr_list[], size_t begin, size_t attr_num);
void selects_append_relation(Selects *selects, const char *relation_name);
void selects_append_relation_with_alias(Selects *selects, const char *relation_name, const char *alias_name);
void selects_append_conditions(Selects *selects, Condition conditions[], size_t begin, size_t condition_num);
void selects_append_expressions(Selects *selects, Exp *expression[], size_t begin, size_t expr_num);
void selects_append_group_by(Selects *selects, RelAttr *group_by);
void selects_append_order_by(Selects *selects, OrderBy *order_by);
void selects_append_having(Selects *selects, Having *having);
void selects_destroy(Selects *selects);


void insert_init(Insert *insert, Value values[], size_t value_num);
void insert_destroy(Insert *insert);
void inserts_init(Inserts *inserts, const char *relation_name, Insert insert_list[], size_t insert_num);
void inserts_destroy(Inserts *inserts);

void deletes_init_relation(Deletes *deletes, const char *relation_name);
void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num);
void deletes_destroy(Deletes *deletes);

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, Value *value,
    Condition conditions[], size_t condition_num);
void updates_destroy(Updates *updates);
void updates_select_init(Updatess *updates, const char *relation_name, Condition conditions[], size_t condition_num);
void updates_append_value(Updatess *updates, Value *value, const char *attribute_name);
void updates_select_destroy(Updatess *updates);

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info);
void create_table_init_name(CreateTable *create_table, const char *relation_name);
void create_table_destroy(CreateTable *create_table);

void drop_table_init(DropTable *drop_table, const char *relation_name);
void drop_table_destroy(DropTable *drop_table);

void create_index_init(
    CreateIndex *create_index, const char *index_name, const char *relation_name, int is_unique);
void create_index_append_attribute_name(CreateIndex *create_index, const char *attr_name);
void create_index_destroy(CreateIndex *create_index);

void drop_index_init(DropIndex *drop_index, const char *index_name);
void drop_index_destroy(DropIndex *drop_index);

void show_index_init(ShowIndex *show_index, const char *relation_name);
void show_index_destroy(ShowIndex *show_index);

void desc_table_init(DescTable *desc_table, const char *relation_name);
void desc_table_destroy(DescTable *desc_table);

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name);
void load_data_destroy(LoadData *load_data);

void query_init(Query *query);
Query *query_create();  // create and init
void query_reset(Query *query);
void query_destroy(Query *query);  // reset and delete

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
