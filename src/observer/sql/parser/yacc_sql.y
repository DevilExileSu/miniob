
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  
  // 属性列表 
  RelAttr attrs[MAX_NUM];
  size_t attr_num;

  // 一条insert插入多条数据
  size_t insert_num;
  Insert insert_list[MAX_NUM];

  // 作为其他语句子语句的select语句
  size_t select_num;
  Selects selections[MAX_NUM];
  size_t depth;

  size_t expr_num;
  Exp *expressions[MAX_NUM];
  
  size_t expression_attr_num;
  
  // order_by和group_by、having不考虑子查询
  size_t order_num;
  OrderBy order_by[MAX_NUM];

  size_t group_num;
  RelAttr group_by;

  size_t having_num;
  RelAttr having_attrs;
  // size_t 
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  size_t cursor_attr[MAX_NUM];
  size_t cursor_cond[MAX_NUM];
  size_t cursor_value[MAX_NUM];
  size_t cursor_exp[MAX_NUM];
  CompOp comp;
	char id[MAX_NUM];
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.insert_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
		UNIQUE
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
		ADD_T
		SUB_T
		DIV_T
        INT_T
        STRING_T
        FLOAT_T
		DATE_T
		TEXT_T
		NULL_T
		NULLABLE
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
		OR
        SET
		AS
        ON
		IN
		IS
		NOT
		EXIST
		INNER
		JOIN
        LOAD
        DATA
        INFILE
		MAX_T
		MIN_T
		COUNT_T
		AVG_T
		SUM_T
		ASC
		ORDER
		GROUP
		BY
		HAVING
		LENGTH_T
		ROUND_T
		DATE_FORMAT_T
		LIKE
        EQ
        LT
        GT
        LE
        GE
        NE
		

%union {
  struct _Attr *attr1;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
  char *position;
  struct _Exp *exp1;
}

// 定义优先级
%left ADD_T SUB_T
%left STAR DIV_T

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> DATE
%token <string> TEXT
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V
//非终结符

%type <number> func;
%type <attr1> func_with_param;
%type <number> agg_func;
%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <attr1> agg;
%type <number> number;
%type <number> nullable;
%type <number> comOp;
%type <string> alias_ID;
%type <exp1> exp;
%type <number> order;

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	// | update
	| updates
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index	
	| drop_index
	| show_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5, 0);
			
		}
    | CREATE UNIQUE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6, 1);
			// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $8);
		}
    ;


attr_name_list:
	| COMMA attr_name attr_name_list {

	}
	;

attr_name: ID {
	create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $1);
	// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $2);
}
drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;

show_index:
	SHOW INDEX FROM ID SEMICOLON{
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, $4);
		}
	;
	
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE nullable 
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4, $6);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
    |ID_get type nullable
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, $3);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
    ;

nullable:
	{ $$=0; }
	| NULLABLE { $$=1; }
	| NOT NULL_T { $$=2; }
	;

number:
		NUMBER {$$ = $1;}
		;
type:
	INT_T { $$=INTS; }
       | STRING_T { $$=CHARS; }
       | FLOAT_T { $$=FLOATS; }
	   | DATE_T { $$=DATES; }
	   | TEXT_T { $$=TEXTS; }
       ;
ID_get:
	ID 
	{
		char *temp=$1; 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;

	
insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES tuple tuple_list SEMICOLON 
		{
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->insert_list, CONTEXT->insert_num);
      //临时变量清零
      CONTEXT->value_length=0;
	  CONTEXT->insert_num=0;
	  memset(CONTEXT->insert_list, 0, sizeof(CONTEXT->insert_list));
    }
	

tuple_list: 
	| COMMA tuple tuple_list {
	}
	;


tuple: 
	LBRACE value_with_neg value_list RBRACE {
		insert_init(&CONTEXT->insert_list[CONTEXT->insert_num++], CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
	;

value_list:
    /* empty */
    | COMMA value_with_neg value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
    ;
value:
    NUMBER{	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |FLOAT{
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
	|DATE{
		$1 = substr($1, 1, strlen($1)-2);
		int res = value_init_date(&CONTEXT->values[CONTEXT->value_length++], $1);
		if (res != 0) {
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			yyresult = 2;
			goto yyreturnlab;
		}
	}
    |SSS {
			$1 = substr($1,1,strlen($1)-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
	|NULL_T {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
    ;

value_with_neg:
	value {
	}
	| SUB_T NUMBER {
		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $2 * -1);
	}
	| SUB_T FLOAT {
		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $2 * -1.0);
	}

delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
    ;
// update:			/*  update 语句的语法解析树*/
//     UPDATE ID SET ID EQ value where SEMICOLON
// 		{
// 			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
// 			Value *value = &CONTEXT->values[0];
// 			updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value, 
// 					CONTEXT->conditions, CONTEXT->condition_length);
// 			CONTEXT->condition_length = 0;
// 		}
//     ;

updates:
	UPDATE ID SET modify_expr modify_list where SEMICOLON {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		updates_select_init(&CONTEXT->ssql->sstr.updates, $2, CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
		CONTEXT->select_num = 0;
		CONTEXT->attr_num = 0;
		CONTEXT->expression_attr_num = 0;
	}
	; 

modify_list:
	| COMMA modify_expr modify_list {

	}
	;

modify_expr: 
	ID EQ value_with_neg {
		updates_append_value(&CONTEXT->ssql->sstr.updates, &CONTEXT->values[CONTEXT->value_length - 1], $1);
	}
	| ID EQ LBRACE select_clause RBRACE{
		Value value;
		value_init_select(&value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, $1);
	}
	| ID EQ agg {
		Value value;
		// value_init_agg(&value, &CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]-1]);
		// CONTEXT->select_attr_num[CONTEXT->select_num]--;
		value_init_agg(&value, &CONTEXT->attrs[--CONTEXT->expression_attr_num]);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, $1);
	}
	;


exp: 
	exp ADD_T exp { $$ = create_expression($1, $3, NULL, NULL, ADD); }
	| exp SUB_T exp { $$ = create_expression($1, $3, NULL, NULL, SUB); }
	| SUB_T exp {
		// Value left_value;
		// value_init_integer(&left_value, 0);
		// Exp *left_exp = create_expression(NULL, NULL, &left_value, NULL, VAL);
		$$ = create_expression(NULL, $2, NULL, NULL, SUB);
	}
	| exp STAR exp { $$ = create_expression($1, $3, NULL, NULL, MUL); }
	| exp DIV_T exp { $$ = create_expression($1, $3, NULL, NULL, DIV); }
	| LBRACE exp RBRACE { 
		Exp *exp = $2;
		++exp->lbrace;
		++exp->rbrace;
		$$ = exp; 
	}
	| value { 
		$$ = create_expression(NULL, NULL, &CONTEXT->values[CONTEXT->value_length - 1], NULL, VAL); 
	}
	| ID alias_ID { 
		RelAttr attr;
		relation_attr_init_with_alias(&attr, NULL, $1, $2);
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		$$ = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
	| ID DOT ID alias_ID {
		RelAttr attr;
		
		relation_attr_init_with_alias(&attr, $1, $3, $4);
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		$$ = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
	| STAR alias_ID {
		if ($2 != NULL) {
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			yyresult = 2;
			goto yyreturnlab;
		}
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		$$ = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
	| ID DOT STAR alias_ID {
		if ($4 != NULL) {
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			yyresult = 2;
			goto yyreturnlab;
		}
		RelAttr attr;
		relation_attr_init(&attr, $1, "*");
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		$$ = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
	| agg {
		$$ = create_expression(NULL, NULL, NULL, &CONTEXT->attrs[CONTEXT->expression_attr_num - 1], ATTR);
	}
	| func_with_param {
		$$ = create_expression(NULL, NULL, NULL, &CONTEXT->attrs[CONTEXT->expression_attr_num - 1], ATTR);
	}
	;


select_begin:
	SELECT {
		// 记录当前深度select的状态
		CONTEXT->cursor_attr[CONTEXT->depth] = CONTEXT->attr_num;
		CONTEXT->cursor_cond[CONTEXT->depth] = CONTEXT->condition_length;
		CONTEXT->cursor_value[CONTEXT->depth] = CONTEXT->value_length;
		CONTEXT->cursor_exp[CONTEXT->depth] = CONTEXT->expr_num;
		// 这里如果是子查询，说明条件语句执行完毕，将expression_attr_num重设为CONTEXT->attr_num;
		// 去掉条件语句中创建的Attr
		CONTEXT->expression_attr_num = CONTEXT->attr_num;
		++CONTEXT->depth;
	}
	;
select_clause: 
	select_begin select_attr FROM ID alias_ID rel_list where group_by order_by {
		// 当进入该语句中时，depth一定是>=1的，不用担心越界问题
		// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
		// selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], $4);
		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], $4, $5);

		selects_append_conditions(&CONTEXT->selections[CONTEXT->select_num],
		 						  CONTEXT->conditions, 
								  CONTEXT->cursor_cond[CONTEXT->depth - 1],
								  CONTEXT->condition_length - CONTEXT->cursor_cond[CONTEXT->depth - 1]);

		selects_append_attribute_list(&CONTEXT->selections[CONTEXT->select_num], 
									  CONTEXT->attrs,
									  CONTEXT->cursor_attr[CONTEXT->depth - 1],
									  CONTEXT->attr_num - CONTEXT->cursor_attr[CONTEXT->depth - 1]);

		selects_append_expressions(&CONTEXT->selections[CONTEXT->select_num], 
									  CONTEXT->expressions,
									  CONTEXT->cursor_exp[CONTEXT->depth - 1],
									  CONTEXT->expr_num - CONTEXT->cursor_exp[CONTEXT->depth - 1]);

		// 状态复原
		--CONTEXT->depth;
		CONTEXT->attr_num = CONTEXT->cursor_attr[CONTEXT->depth];
		CONTEXT->condition_length = CONTEXT->cursor_cond[CONTEXT->depth];
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth];
		CONTEXT->expr_num = CONTEXT->cursor_exp[CONTEXT->depth];
		CONTEXT->expression_attr_num = CONTEXT->attr_num;
		// 临时变量清零
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		++CONTEXT->select_num;
	}
	| select_begin select_attr FROM ID alias_ID INNER JOIN ID alias_ID ON condition condition_list join_list where group_by order_by {
		// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;

		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], $8, $9);
		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], $4, $5);

		selects_append_conditions(&CONTEXT->selections[CONTEXT->select_num],
		 						  CONTEXT->conditions, 
								  CONTEXT->cursor_cond[CONTEXT->depth - 1],
								  CONTEXT->condition_length - CONTEXT->cursor_cond[CONTEXT->depth - 1]);

		selects_append_attribute_list(&CONTEXT->selections[CONTEXT->select_num], 
									  CONTEXT->attrs,
									  CONTEXT->cursor_attr[CONTEXT->depth - 1],
									  CONTEXT->attr_num - CONTEXT->cursor_attr[CONTEXT->depth - 1]);

		selects_append_expressions(&CONTEXT->selections[CONTEXT->select_num], 
									  CONTEXT->expressions,
									  CONTEXT->cursor_exp[CONTEXT->depth - 1],
									  CONTEXT->expr_num - CONTEXT->cursor_exp[CONTEXT->depth - 1]);

		CONTEXT->selections[CONTEXT->select_num].is_and = 1;
		// 状态复原
		--CONTEXT->depth;
		CONTEXT->attr_num = CONTEXT->cursor_attr[CONTEXT->depth];
		CONTEXT->condition_length = CONTEXT->cursor_cond[CONTEXT->depth];
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth];
		CONTEXT->expr_num = CONTEXT->cursor_exp[CONTEXT->depth];
		CONTEXT->expression_attr_num = CONTEXT->attr_num;
		// 临时变量清零
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		++CONTEXT->select_num;
	}
	| select_begin select_attr {
		selects_append_attribute_list(&CONTEXT->selections[CONTEXT->select_num], 
									  CONTEXT->attrs,
									  CONTEXT->cursor_attr[CONTEXT->depth - 1],
									  CONTEXT->attr_num - CONTEXT->cursor_attr[CONTEXT->depth - 1]);

		selects_append_expressions(&CONTEXT->selections[CONTEXT->select_num], 
									  CONTEXT->expressions,
									  CONTEXT->cursor_exp[CONTEXT->depth - 1],
									  CONTEXT->expr_num - CONTEXT->cursor_exp[CONTEXT->depth - 1]);

		CONTEXT->selections[CONTEXT->select_num].is_func = 1;

		// 状态复原
		--CONTEXT->depth;
		CONTEXT->attr_num = CONTEXT->cursor_attr[CONTEXT->depth];
		CONTEXT->condition_length = CONTEXT->cursor_cond[CONTEXT->depth];
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth];
		CONTEXT->expr_num = CONTEXT->cursor_exp[CONTEXT->depth];
		CONTEXT->expression_attr_num = CONTEXT->attr_num;
		// 临时变量清零
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		++CONTEXT->select_num;
	}
	;

select:				/*  select 语句的语法解析树*/
    select_clause SEMICOLON {
		// 这里说明select是主语句
		CONTEXT->ssql->flag=SCF_SELECT;//"select";
		CONTEXT->ssql->sstr.selection = CONTEXT->selections[CONTEXT->select_num-1];
	}
	;


order_by:
	/* empty */
	| ORDER BY order_item order_item_list {
		
	}
	;

order_item_list:
	/* empty */
	| COMMA order_item order_item_list {}
	; 

order_item:
	ID order {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		OrderBy order_by; 
		order_by_init(&order_by, &attr, $2);
		selects_append_order_by(&CONTEXT->selections[CONTEXT->select_num], &order_by);
	}
	| ID DOT ID order {
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		OrderBy order_by;
		order_by_init(&order_by, &attr, $4);
		selects_append_order_by(&CONTEXT->selections[CONTEXT->select_num], &order_by);
	}
	;
order: 
	{ $$ = 0; }
	| ASC { $$ = 0; }
	| DESC { $$ = 1; }


group_by: 
	| GROUP BY group_item group_item_list having {
	}
	;

group_item_list:
	/* empty */
	| COMMA group_item group_item_list {}
	; 

group_item: 
	ID {
		RelAttr attr;	
		relation_attr_init(&attr, NULL, $1);
		selects_append_group_by(&CONTEXT->selections[CONTEXT->select_num], &attr);
	}
	| ID DOT ID {
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		selects_append_group_by(&CONTEXT->selections[CONTEXT->select_num], &attr);
	}
	;
having: 
	| HAVING agg_func LBRACE STAR RBRACE comOp value_with_neg {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, "*", $2, NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], $6, 0);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	} 
	| HAVING agg_func LBRACE ID RBRACE comOp value_with_neg {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, $4, $2, NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], $6, 0);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
	| HAVING agg_func LBRACE ID DOT ID RBRACE comOp value_with_neg {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, $4, $6, $2, NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], $8, 0);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
	| HAVING value_with_neg comOp agg_func LBRACE STAR RBRACE  {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, "*", $4, NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], $3, 1);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
	| HAVING value_with_neg comOp agg_func LBRACE ID RBRACE {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, $6, $4, NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], $3, 1);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
	| HAVING value_with_neg comOp agg_func LBRACE ID DOT ID RBRACE {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, $6, $8, $4, NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], $3, 1);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}

join_list:
	| INNER JOIN ID ON condition condition_list join_list
	{
		selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], $3);
	}
	;

agg_func:
	MAX_T { $$=MAX; }
	| MIN_T { $$=MIN; }
	| COUNT_T { $$=COUNT; }
	| AVG_T { $$=AVG; }
	| SUM_T { $$=SUM; }
	;

func:
	LENGTH_T { $$=LENGTH; }
	| ROUND_T { $$=ROUND; }
	| DATE_FORMAT_T { $$=DATE_FORMAT; }
	;

func_with_param:
	func LBRACE ID RBRACE alias_ID {
		RelAttr attr;
		relation_attr_init_with_func(&attr, NULL, $3, $1, $5);
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	  }
	| func LBRACE ID DOT ID RBRACE alias_ID {
		RelAttr attr;
		relation_attr_init_with_func(&attr, $3, $5, $1, $7);
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
	| func LBRACE value_with_neg RBRACE alias_ID {
		RelAttr attr;
		relation_attr_init_with_func_value(&attr, $1, &CONTEXT->values[CONTEXT->value_length - 1], NULL, $5);
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
	| func LBRACE value_with_neg COMMA value_with_neg RBRACE alias_ID {
		RelAttr attr;
		relation_attr_init_with_func_value(&attr, $1, &CONTEXT->values[CONTEXT->value_length - 2], &CONTEXT->values[CONTEXT->value_length - 1], $7);
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
	| func LBRACE ID COMMA value_with_neg RBRACE alias_ID {
		RelAttr attr;
		relation_attr_init_with_func(&attr, NULL, $3, $1, $7);
		relation_attr_init_with_func_append_value(&attr, &CONTEXT->values[CONTEXT->value_length - 1]);
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
	| func LBRACE ID DOT ID COMMA value_with_neg RBRACE alias_ID {
		RelAttr attr;
		relation_attr_init_with_func(&attr, $3, $5, $1, $9);
		relation_attr_init_with_func_append_value(&attr, &CONTEXT->values[CONTEXT->value_length - 1]);
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
	| func LBRACE ID COMMA value_with_neg COMMA value_with_neg RBRACE alias_ID {
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	} 
	| func LBRACE ID DOT ID COMMA value_with_neg COMMA value_with_neg RBRACE alias_ID {
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
	| func func LBRACE value_with_neg COMMA value_with_neg COMMA value_with_neg RBRACE alias_ID {
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
	;


agg:
 	agg_func LBRACE STAR RBRACE alias_ID {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, "*", $1, $5);
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
	| agg_func LBRACE ID RBRACE alias_ID {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, $3, $1, $5);
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
	| agg_func LBRACE ID DOT ID RBRACE alias_ID {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, $3, $5, $1, $7);
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
	| agg_func LBRACE NUMBER RBRACE alias_ID {
		RelAttr attr;
		relation_attr_init_with_agg_num(&attr, $1, $3, $5);
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
	| agg_func LBRACE STAR COMMA ID RBRACE alias_ID {
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
	| agg_func LBRACE ID COMMA ID RBRACE alias_ID {
		// 错误类型
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
	| agg_func LBRACE RBRACE alias_ID {
		// 错误类型
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
	;

// 原先这里是匹配attr_list规则之后再去执行{}内的内容，导致全局的CONTEXT->attrs是逆序存放的
// 这就导致实际添加到select中的RelAttr也是逆序的
// 现在使用exp代替之后，我们会按照顺序的进行添加，因此，在执行selects的create时，不需要逆序遍历
select_attr:
	exp attr_list {
		CONTEXT->expressions[CONTEXT->expr_num++] = $1;
		CONTEXT->attr_num = CONTEXT->expression_attr_num;
	}
    ;

attr_list:
    /* empty */
	| COMMA exp attr_list {
		CONTEXT->expressions[CONTEXT->expr_num++] = $2;
		// 因为现在条件语句中的RelAttr也会占用全局的attrs
		// 需要进行一下区别，attr_num只记录
		CONTEXT->attr_num = CONTEXT->expression_attr_num;
	}
  	;

alias_ID: 
	/* empty */
	{ $$ = NULL; }
	| ID { $$ = $1; }
	| AS ID { $$ = $2; }
	;

rel_list:
    /* empty */
    | COMMA ID alias_ID rel_list {	
		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], $2, $3);
	}
    ;
where:
    /* empty */ 
    | WHERE condition condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
	}
    ;


condition_list:
    /* empty */
    | AND condition condition_list {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		CONTEXT->selections[CONTEXT->select_num].is_and = 1; 
	}
	| OR condition condition_list {
		CONTEXT->selections[CONTEXT->select_num].is_and = 0;
	}
    ;


condition:
	exp comOp exp {
		Exp *left_exp = $1;
		Exp *right_exp = $3;
		Condition condition;
		condition_init_with_exp(&condition, $2, left_exp, right_exp);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
	| exp comOp LBRACE value_with_neg COMMA value_with_neg value_list RBRACE {
		// comOp只能是in/not in, exists/not exists
		// 同除了包含LBRACE value value_list RBRACE的条件语句，comOp都只能是非in/not in, exists/not exists
		// RelAttr left_attr;
		// relation_attr_init(&left_attr, NULL, $1);
		Exp *left_exp  = $1;
		Value right_value;
		value_init_set(&right_value, CONTEXT->values, CONTEXT->cursor_value[CONTEXT->depth], CONTEXT->value_length - CONTEXT->cursor_value[CONTEXT->depth]);
		Exp *right_exp = create_expression(NULL, NULL, &right_value, NULL, VAL);

		Condition condition;

		condition_init_with_exp(&condition, $2, left_exp, right_exp);
		// condition_init(&condition, $2, 1, &left_attr, NULL, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		/// 复原同一深度的cursor_value[]，防止和同一深度其他的SETS类型value冲突
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
	| LBRACE select_clause RBRACE comOp exp {
		Value left_value;
		value_init_select(&left_value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		
		Condition condition;
		Exp *left_exp = create_expression(NULL, NULL, &left_value, NULL, VAL);
		Exp *right_exp = $5;
		condition_init_with_exp(&condition, $4, left_exp, right_exp);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
	| exp comOp LBRACE select_clause RBRACE {
		Value right_value;
		value_init_select(&right_value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		
		Condition condition;
		Exp *left_exp = $1;
		Exp *right_exp = create_expression(NULL, NULL, &right_value, NULL, VAL);
		condition_init_with_exp(&condition, $2, left_exp, right_exp);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
	| comOp LBRACE select_clause RBRACE {
		if ($1 != EXISTS_OP && $1 != NOT_EXISTS_OP) {
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			yyresult = 2;
			goto yyreturnlab;
		}
		Value right_value;
		value_init_select(&right_value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		Condition condition;
		condition_init(&condition, $1, -1, NULL, NULL, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
	| LBRACE select_clause RBRACE comOp LBRACE select_clause RBRACE {
		Value left_value;
		value_init_select(&left_value, &CONTEXT->selections[CONTEXT->select_num - 2]);
		Value right_value;
		value_init_select(&right_value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		Condition condition;

		condition_init(&condition, $4, 0, NULL, &left_value, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
    ;

comOp:
  	  EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
	| LIKE { $$ = LIKE_MATCH; }
	| NOT LIKE { $$ = NOT_LIKE; }
	| IN { $$ = IN_OP; }
	| NOT IN { $$ = NOT_IN_OP; }
	| EXIST { $$ =EXISTS_OP; }
	| NOT EXIST { $$ = NOT_EXISTS_OP; }
	| IS { $$ = IS_OP; }
	| IS NOT { $$ = IS_NOT_OP; }
    ;

load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
