/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 161 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_UNIQUE = 9,                     /* UNIQUE  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_UPDATE = 16,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 20,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 21,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 22,              /* TRX_ROLLBACK  */
  YYSYMBOL_ADD_T = 23,                     /* ADD_T  */
  YYSYMBOL_SUB_T = 24,                     /* SUB_T  */
  YYSYMBOL_DIV_T = 25,                     /* DIV_T  */
  YYSYMBOL_INT_T = 26,                     /* INT_T  */
  YYSYMBOL_STRING_T = 27,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 28,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 29,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 30,                    /* TEXT_T  */
  YYSYMBOL_NULL_T = 31,                    /* NULL_T  */
  YYSYMBOL_NULLABLE = 32,                  /* NULLABLE  */
  YYSYMBOL_HELP = 33,                      /* HELP  */
  YYSYMBOL_EXIT = 34,                      /* EXIT  */
  YYSYMBOL_DOT = 35,                       /* DOT  */
  YYSYMBOL_INTO = 36,                      /* INTO  */
  YYSYMBOL_VALUES = 37,                    /* VALUES  */
  YYSYMBOL_FROM = 38,                      /* FROM  */
  YYSYMBOL_WHERE = 39,                     /* WHERE  */
  YYSYMBOL_AND = 40,                       /* AND  */
  YYSYMBOL_OR = 41,                        /* OR  */
  YYSYMBOL_SET = 42,                       /* SET  */
  YYSYMBOL_AS = 43,                        /* AS  */
  YYSYMBOL_ON = 44,                        /* ON  */
  YYSYMBOL_IN = 45,                        /* IN  */
  YYSYMBOL_IS = 46,                        /* IS  */
  YYSYMBOL_NOT = 47,                       /* NOT  */
  YYSYMBOL_EXIST = 48,                     /* EXIST  */
  YYSYMBOL_INNER = 49,                     /* INNER  */
  YYSYMBOL_JOIN = 50,                      /* JOIN  */
  YYSYMBOL_LOAD = 51,                      /* LOAD  */
  YYSYMBOL_DATA = 52,                      /* DATA  */
  YYSYMBOL_INFILE = 53,                    /* INFILE  */
  YYSYMBOL_MAX_T = 54,                     /* MAX_T  */
  YYSYMBOL_MIN_T = 55,                     /* MIN_T  */
  YYSYMBOL_COUNT_T = 56,                   /* COUNT_T  */
  YYSYMBOL_AVG_T = 57,                     /* AVG_T  */
  YYSYMBOL_SUM_T = 58,                     /* SUM_T  */
  YYSYMBOL_ASC = 59,                       /* ASC  */
  YYSYMBOL_ORDER = 60,                     /* ORDER  */
  YYSYMBOL_GROUP = 61,                     /* GROUP  */
  YYSYMBOL_BY = 62,                        /* BY  */
  YYSYMBOL_HAVING = 63,                    /* HAVING  */
  YYSYMBOL_LENGTH_T = 64,                  /* LENGTH_T  */
  YYSYMBOL_ROUND_T = 65,                   /* ROUND_T  */
  YYSYMBOL_DATE_FORMAT_T = 66,             /* DATE_FORMAT_T  */
  YYSYMBOL_LIKE = 67,                      /* LIKE  */
  YYSYMBOL_EQ = 68,                        /* EQ  */
  YYSYMBOL_LT = 69,                        /* LT  */
  YYSYMBOL_GT = 70,                        /* GT  */
  YYSYMBOL_LE = 71,                        /* LE  */
  YYSYMBOL_GE = 72,                        /* GE  */
  YYSYMBOL_NE = 73,                        /* NE  */
  YYSYMBOL_NUMBER = 74,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 75,                     /* FLOAT  */
  YYSYMBOL_DATE = 76,                      /* DATE  */
  YYSYMBOL_TEXT = 77,                      /* TEXT  */
  YYSYMBOL_ID = 78,                        /* ID  */
  YYSYMBOL_PATH = 79,                      /* PATH  */
  YYSYMBOL_SSS = 80,                       /* SSS  */
  YYSYMBOL_STAR = 81,                      /* STAR  */
  YYSYMBOL_STRING_V = 82,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 83,                  /* $accept  */
  YYSYMBOL_commands = 84,                  /* commands  */
  YYSYMBOL_command = 85,                   /* command  */
  YYSYMBOL_exit = 86,                      /* exit  */
  YYSYMBOL_help = 87,                      /* help  */
  YYSYMBOL_sync = 88,                      /* sync  */
  YYSYMBOL_begin = 89,                     /* begin  */
  YYSYMBOL_commit = 90,                    /* commit  */
  YYSYMBOL_rollback = 91,                  /* rollback  */
  YYSYMBOL_drop_table = 92,                /* drop_table  */
  YYSYMBOL_show_tables = 93,               /* show_tables  */
  YYSYMBOL_desc_table = 94,                /* desc_table  */
  YYSYMBOL_create_index = 95,              /* create_index  */
  YYSYMBOL_attr_name_list = 96,            /* attr_name_list  */
  YYSYMBOL_attr_name = 97,                 /* attr_name  */
  YYSYMBOL_drop_index = 98,                /* drop_index  */
  YYSYMBOL_show_index = 99,                /* show_index  */
  YYSYMBOL_create_table = 100,             /* create_table  */
  YYSYMBOL_attr_def_list = 101,            /* attr_def_list  */
  YYSYMBOL_attr_def = 102,                 /* attr_def  */
  YYSYMBOL_nullable = 103,                 /* nullable  */
  YYSYMBOL_number = 104,                   /* number  */
  YYSYMBOL_type = 105,                     /* type  */
  YYSYMBOL_ID_get = 106,                   /* ID_get  */
  YYSYMBOL_insert = 107,                   /* insert  */
  YYSYMBOL_tuple_list = 108,               /* tuple_list  */
  YYSYMBOL_tuple = 109,                    /* tuple  */
  YYSYMBOL_value_list = 110,               /* value_list  */
  YYSYMBOL_value = 111,                    /* value  */
  YYSYMBOL_value_with_neg = 112,           /* value_with_neg  */
  YYSYMBOL_delete = 113,                   /* delete  */
  YYSYMBOL_updates = 114,                  /* updates  */
  YYSYMBOL_modify_list = 115,              /* modify_list  */
  YYSYMBOL_modify_expr = 116,              /* modify_expr  */
  YYSYMBOL_exp = 117,                      /* exp  */
  YYSYMBOL_select_begin = 118,             /* select_begin  */
  YYSYMBOL_select_clause = 119,            /* select_clause  */
  YYSYMBOL_select = 120,                   /* select  */
  YYSYMBOL_order_by = 121,                 /* order_by  */
  YYSYMBOL_order_item_list = 122,          /* order_item_list  */
  YYSYMBOL_order_item = 123,               /* order_item  */
  YYSYMBOL_order = 124,                    /* order  */
  YYSYMBOL_group_by = 125,                 /* group_by  */
  YYSYMBOL_group_item_list = 126,          /* group_item_list  */
  YYSYMBOL_group_item = 127,               /* group_item  */
  YYSYMBOL_having = 128,                   /* having  */
  YYSYMBOL_join_list = 129,                /* join_list  */
  YYSYMBOL_agg_func = 130,                 /* agg_func  */
  YYSYMBOL_func = 131,                     /* func  */
  YYSYMBOL_func_with_param = 132,          /* func_with_param  */
  YYSYMBOL_agg = 133,                      /* agg  */
  YYSYMBOL_select_attr = 134,              /* select_attr  */
  YYSYMBOL_attr_list = 135,                /* attr_list  */
  YYSYMBOL_alias_ID = 136,                 /* alias_ID  */
  YYSYMBOL_rel_list = 137,                 /* rel_list  */
  YYSYMBOL_where = 138,                    /* where  */
  YYSYMBOL_condition_list = 139,           /* condition_list  */
  YYSYMBOL_condition = 140,                /* condition  */
  YYSYMBOL_comOp = 141,                    /* comOp  */
  YYSYMBOL_load_data = 142                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   637

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  173
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  402

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   337


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   212,   212,   214,   218,   219,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   240,   245,   250,   256,   262,   268,   274,   280,
     286,   293,   299,   308,   309,   314,   319,   327,   334,   343,
     345,   349,   360,   374,   375,   376,   380,   383,   384,   385,
     386,   387,   390,   399,   417,   418,   424,   430,   432,   437,
     440,   443,   452,   456,   462,   464,   467,   472,   493,   503,
     504,   510,   513,   518,   529,   530,   531,   537,   538,   539,
     545,   548,   554,   561,   573,   585,   588,   595,   608,   641,
     675,   703,   711,   713,   718,   720,   724,   731,   740,   741,
     742,   745,   746,   750,   752,   756,   761,   767,   768,   775,
     782,   789,   796,   803,   811,   812,   819,   820,   821,   822,
     823,   827,   828,   829,   833,   838,   843,   848,   853,   859,
     865,   870,   875,   884,   890,   896,   902,   908,   913,   919,
     931,   937,   939,   949,   950,   951,   954,   956,   960,   962,
     968,   970,   974,   981,   989,  1007,  1018,  1029,  1042,  1056,
    1057,  1058,  1059,  1060,  1061,  1062,  1063,  1064,  1065,  1066,
    1067,  1068,  1069,  1073
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "UNIQUE", "SELECT", "DESC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "ADD_T", "SUB_T", "DIV_T",
  "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "TEXT_T", "NULL_T", "NULLABLE",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "OR",
  "SET", "AS", "ON", "IN", "IS", "NOT", "EXIST", "INNER", "JOIN", "LOAD",
  "DATA", "INFILE", "MAX_T", "MIN_T", "COUNT_T", "AVG_T", "SUM_T", "ASC",
  "ORDER", "GROUP", "BY", "HAVING", "LENGTH_T", "ROUND_T", "DATE_FORMAT_T",
  "LIKE", "EQ", "LT", "GT", "LE", "GE", "NE", "NUMBER", "FLOAT", "DATE",
  "TEXT", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index",
  "attr_name_list", "attr_name", "drop_index", "show_index",
  "create_table", "attr_def_list", "attr_def", "nullable", "number",
  "type", "ID_get", "insert", "tuple_list", "tuple", "value_list", "value",
  "value_with_neg", "delete", "updates", "modify_list", "modify_expr",
  "exp", "select_begin", "select_clause", "select", "order_by",
  "order_item_list", "order_item", "order", "group_by", "group_item_list",
  "group_item", "having", "join_list", "agg_func", "func",
  "func_with_param", "agg", "select_attr", "attr_list", "alias_ID",
  "rel_list", "where", "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-326)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-67)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -326,   339,  -326,   155,    99,  -326,   -61,   119,    40,    13,
      42,    18,    86,   115,   117,   120,   138,   101,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,   417,   152,  -326,  -326,    80,
      92,   170,    94,   106,   195,   203,   180,  -326,   142,   149,
     183,  -326,  -326,  -326,  -326,  -326,   175,   417,   417,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,    19,  -326,   -33,  -326,    11,   212,    29,  -326,  -326,
     199,  -326,   221,   196,   161,   238,   239,  -326,  -326,   165,
     210,   209,   171,   172,    -4,    -7,   -39,   173,  -326,  -326,
    -326,   417,   417,   417,   417,   417,  -326,    10,    91,   233,
     176,   181,   182,   211,  -326,  -326,   250,   241,   357,   253,
     194,   244,   228,  -326,   -33,   -33,  -326,    11,    -7,    -7,
    -326,  -326,   -33,   247,   141,   127,    63,   167,  -326,   132,
     -15,   -33,  -326,   255,   164,   249,   191,  -326,   -15,   257,
     251,  -326,   223,    58,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,   556,   147,   260,  -326,   125,   171,   209,   272,
    -326,  -326,  -326,  -326,   -33,   -33,   202,   205,   -33,   206,
    -326,  -326,   -33,   -15,   207,   -33,   -15,   267,     3,   181,
     269,  -326,  -326,  -326,  -326,  -326,     9,   214,   271,   274,
     241,   287,   276,  -326,  -326,  -326,  -326,   445,   357,   357,
    -326,   285,   285,  -326,  -326,   244,   293,   220,  -326,  -326,
     281,   282,  -326,   283,  -326,   178,   190,  -326,   292,   -15,
     225,   261,   209,   255,   309,   245,  -326,   289,  -326,  -326,
     294,   214,   -15,   300,   257,  -326,   541,   311,   -17,   147,
     147,   304,   305,  -326,  -326,   321,   -33,   -33,   -33,   -33,
     -15,   -33,   -15,   -33,   314,   -33,   252,   273,  -326,  -326,
    -326,   318,  -326,   214,   319,   294,   274,  -326,  -326,   491,
     519,   322,   326,   320,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,   328,  -326,   192,  -326,   -15,   329,   -33,
     278,   296,     6,   294,   344,   340,  -326,   251,   -17,   338,
     343,   -15,  -326,   -33,   -33,   -15,   345,  -326,   327,   286,
     308,  -326,  -326,  -326,  -326,   375,   361,   274,  -326,  -326,
     362,   -33,   357,   347,   364,   306,  -326,  -326,   376,   -33,
    -326,   147,   315,   286,   332,    89,   377,  -326,  -326,   348,
    -326,   364,    55,  -326,  -326,   323,  -326,  -326,   306,  -326,
     349,   209,  -326,   541,   381,    26,   377,   330,   273,   177,
     -30,  -326,  -326,   356,   296,   389,    15,   391,   357,  -326,
      36,   541,   341,   541,   147,    84,   392,   -15,   398,   -15,
     348,  -326,   342,  -326,  -326,   541,  -326,  -326,   399,   -15,
    -326,  -326
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    87,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     0,     0,     4,    19,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,    25,    26,    27,    23,    22,     0,     0,     0,    63,
     116,   117,   118,   119,   120,   121,   122,   123,    59,    60,
      61,   143,    62,   143,    80,   141,     0,     0,    86,    85,
      90,    91,     0,     0,     0,     0,     0,    30,    29,     0,
       0,   148,     0,     0,     0,    76,     0,     0,   144,    81,
      83,     0,     0,     0,     0,     0,   140,     0,     0,     0,
       0,     0,     0,     0,    28,    36,     0,     0,     0,     0,
       0,    69,     0,    79,   143,   143,   145,   141,    74,    75,
      78,    77,   143,     0,     0,     0,     0,     0,    64,     0,
       0,   143,    52,    39,     0,     0,     0,    37,     0,    54,
       0,   167,   171,     0,   169,   165,   159,   160,   161,   162,
     163,   164,     0,   150,     0,    67,     0,     0,   148,     0,
      82,    84,   142,   139,   143,   143,     0,     0,   143,     0,
      65,    66,   143,     0,     0,   143,     0,     0,   146,     0,
       0,    47,    48,    49,    50,    51,    43,     0,     0,    57,
       0,     0,     0,   172,   168,   170,   166,     0,     0,     0,
     149,     0,     0,    71,    73,    69,     0,     0,   136,   134,
       0,     0,   133,     0,   124,     0,     0,   126,     0,     0,
       0,     0,   148,    39,     0,     0,    44,     0,    42,    35,
      33,     0,     0,     0,    54,    53,     0,     0,   153,   150,
     150,     0,     0,    70,    68,     0,   143,   143,   143,   143,
       0,   143,     0,   143,     0,   143,     0,   101,    40,    38,
      46,     0,    45,     0,     0,    33,    57,    56,    55,     0,
       0,    80,     0,     0,   151,   152,   157,    72,   173,   138,
     135,   137,   128,     0,   125,     0,   127,     0,   146,   143,
       0,    92,    43,    33,     0,     0,    58,     0,   155,    59,
      60,     0,   156,   143,   143,     0,     0,   147,     0,     0,
       0,    88,    41,    34,    31,     0,     0,    57,   130,   129,
       0,   143,     0,   105,   103,     0,    32,   158,     0,   143,
     132,   150,     0,     0,   107,    98,    94,   154,   131,   114,
     106,   103,     0,   102,   100,     0,    99,    96,     0,    93,
       0,   148,   104,     0,     0,    98,    94,     0,   101,     0,
       0,    97,    95,     0,    92,     0,     0,     0,     0,    89,
       0,     0,     0,     0,   150,     0,     0,     0,     0,     0,
     114,   112,     0,   111,   109,     0,   108,   115,     0,     0,
     113,   110
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -246,  -226,  -326,  -326,  -326,   174,   229,
     134,  -326,  -326,  -326,  -326,   198,   240,  -251,  -108,   -85,
    -326,  -326,   224,   277,   -34,  -326,  -139,  -326,    69,    79,
      88,    82,    81,   100,   107,  -326,    62,  -325,   378,  -326,
     288,  -326,   331,   -42,   158,  -166,  -237,  -204,  -159,  -326
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   274,   240,    29,    30,    31,   190,   143,
     238,   271,   196,   144,    32,   201,   149,   243,    74,   139,
      33,    34,   168,   121,   162,    35,    36,    37,   321,   359,
     346,   357,   301,   344,   334,   353,   361,    76,    77,    78,
      79,    80,   106,    99,   232,   119,   210,   163,   164,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     138,    75,   216,   207,   249,   250,   102,   103,   104,   136,
      97,   202,   284,   285,   123,   275,    59,    44,   104,   102,
     103,   104,   230,    94,    95,   306,   235,   364,   132,   305,
     101,   100,   138,   381,   102,   103,   104,   354,   236,   124,
     138,   236,   125,    47,   375,    98,   108,   303,   376,    48,
     382,   377,   231,   237,    96,   187,   237,   323,   138,    68,
      69,    70,    97,   199,   105,    72,   267,   127,   128,   129,
     130,   131,   251,   252,   105,   138,   338,   105,   138,   136,
      49,   213,   170,   171,   133,   356,    59,   279,   134,    51,
     173,   135,   105,    65,    66,    67,    50,    98,   225,   188,
     354,   228,   391,   204,   349,    42,   205,    43,   283,    60,
      61,    62,    63,    64,   385,   136,    94,   386,    52,   392,
      53,   138,    59,    54,   355,   206,    45,    46,   341,    68,
      69,    70,   218,   219,   138,    72,   222,   180,   181,   281,
     224,    55,   212,   227,   264,   178,   179,   390,   356,   136,
     185,   186,   138,    56,   138,    81,    59,   276,    82,   175,
     176,    39,   282,    40,    41,    68,    69,    70,   326,   137,
      83,    72,    85,   248,   384,   293,   177,   295,    84,    60,
      61,    62,    63,    64,    86,   182,   183,   208,   209,   138,
     191,   192,   193,   194,   195,   368,   259,   260,    87,    68,
      69,    70,   184,   138,   369,    72,    88,   138,   261,   262,
     314,   315,   316,    94,   289,   290,   291,   292,    89,   294,
      90,   296,   387,   298,   389,    92,   327,    91,    93,   107,
     330,    60,    61,    62,    63,    64,   399,   110,   111,   113,
     112,   114,   115,   116,   138,   308,    95,   117,   118,   120,
     140,   126,   122,   147,   141,   146,   165,   318,   148,   142,
     145,     5,   166,   167,   169,   174,   197,   363,    57,   198,
     203,   328,   329,    94,   189,    58,   200,   211,   217,   138,
     220,   138,    59,   221,   223,   226,   229,   234,   241,   340,
     245,   138,   239,   242,   246,     5,   254,   348,   255,   256,
     257,   258,   394,   265,   396,    60,    61,    62,    63,    64,
     263,   266,   269,   273,   401,    65,    66,    67,   277,   270,
     272,     5,   286,   287,   288,    68,    69,    70,    57,    71,
     299,    72,    73,   297,   300,   280,   302,   304,   312,     2,
     319,   -64,    59,     3,     4,   311,   313,   324,   230,     5,
       6,     7,     8,     9,    10,    11,   320,   -65,   325,    12,
      13,    14,   -66,   331,   333,    60,    61,    62,    63,    64,
     335,   332,    15,    16,   150,    65,    66,    67,   336,   337,
     339,    58,   342,   343,   345,    68,    69,    70,    59,    71,
      17,    72,    73,   350,   347,   352,   358,   360,   370,   367,
     378,   365,   151,   152,   153,   154,   380,   268,   373,   383,
     393,    60,    61,    62,    63,    64,   395,   400,   233,   388,
     398,    65,    66,    67,   155,   156,   157,   158,   159,   160,
     161,    68,    69,    70,    57,    71,   322,    72,    73,   253,
     244,    58,   278,   379,   215,   372,   366,   371,    59,   374,
     351,   362,   397,     0,   214,   109,   317,     0,   172,     0,
       0,     0,   247,     0,     0,     0,     0,     0,     0,    58,
       0,    60,    61,    62,    63,    64,    59,     0,     0,     0,
       0,    65,    66,    67,     0,     0,     0,     0,     0,     0,
       0,    68,    69,    70,     0,    71,     0,    72,    73,    60,
      61,    62,    63,    64,     0,     0,     0,     0,   307,    65,
      66,    67,     0,     0,     0,    58,     0,     0,     0,    68,
      69,    70,    59,    71,     0,    72,    73,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,     0,     0,     0,
       0,     0,     0,    58,     0,    60,    61,    62,    63,    64,
      59,     0,     0,     0,     0,    65,    66,    67,     0,     0,
       0,     0,     0,     0,     0,    68,    69,    70,     0,    71,
       0,    72,    73,    60,    61,    62,    63,    64,     0,   102,
     103,   104,     0,    65,    66,    67,   151,   152,   153,   154,
       0,     0,     0,   309,   310,    70,     0,    71,     0,    72,
      73,   151,   152,   153,   154,     0,     0,     0,   155,   156,
     157,   158,   159,   160,   161,     0,     0,     0,     0,     0,
       0,     0,     0,   155,   156,   157,   158,   159,   160,   161,
       0,     0,     0,     0,     0,     0,     0,   105
};

static const yytype_int16 yycheck[] =
{
     108,    35,   168,   162,   208,   209,    23,    24,    25,    24,
      43,   150,   249,   250,    18,   241,    31,    78,    25,    23,
      24,    25,    19,    57,    58,   276,    17,   352,    18,   275,
      19,    73,   140,    18,    23,    24,    25,    11,    32,    78,
     148,    32,    81,     3,   369,    78,    17,   273,    78,    36,
      35,    81,    49,    47,    35,   140,    47,   303,   166,    74,
      75,    76,    43,   148,    81,    80,   232,   101,   102,   103,
     104,   105,   211,   212,    81,   183,   327,    81,   186,    24,
      38,   166,   124,   125,    74,    59,    31,   246,    78,     3,
     132,    81,    81,    64,    65,    66,    78,    78,   183,   141,
      11,   186,    18,    45,   341,     6,    48,     8,   247,    54,
      55,    56,    57,    58,    78,    24,   150,    81,     3,    35,
       3,   229,    31,     3,    35,    67,     7,     8,   332,    74,
      75,    76,   174,   175,   242,    80,   178,    74,    75,   247,
     182,     3,    17,   185,   229,    18,    19,   384,    59,    24,
      18,    19,   260,    52,   262,     3,    31,   242,    78,    18,
      19,     6,   247,     8,     9,    74,    75,    76,   307,    78,
      78,    80,    78,   207,   378,   260,    35,   262,     8,    54,
      55,    56,    57,    58,    78,    18,    19,    40,    41,   297,
      26,    27,    28,    29,    30,   361,    18,    19,     3,    74,
      75,    76,    35,   311,   363,    80,     3,   315,    18,    19,
      18,    19,   297,   247,   256,   257,   258,   259,    38,   261,
      78,   263,   381,   265,   383,    42,   311,    78,    53,    17,
     315,    54,    55,    56,    57,    58,   395,    38,    17,    78,
      44,     3,     3,    78,   352,   279,   280,    37,    39,    78,
      17,    78,    80,     3,    78,    44,     3,   299,    17,    78,
      78,    10,    68,    19,    36,    18,    17,   352,    17,    78,
      47,   313,   314,   307,    19,    24,    19,    17,     6,   387,
      78,   389,    31,    78,    78,    78,    19,    18,    17,   331,
       3,   399,    78,    19,    18,    10,     3,   339,    78,    18,
      18,    18,   387,    78,   389,    54,    55,    56,    57,    58,
      18,    50,     3,    19,   399,    64,    65,    66,    18,    74,
      31,    10,    18,    18,     3,    74,    75,    76,    17,    78,
      78,    80,    81,    19,    61,    24,    18,    18,    18,     0,
      62,    19,    31,     4,     5,    19,    18,     3,    19,    10,
      11,    12,    13,    14,    15,    16,    60,    19,    18,    20,
      21,    22,    19,    18,    78,    54,    55,    56,    57,    58,
      62,    44,    33,    34,    17,    64,    65,    66,     3,    18,
      18,    24,    35,    19,    78,    74,    75,    76,    31,    78,
      51,    80,    81,    78,    18,    63,    19,    49,    17,    50,
      44,    78,    45,    46,    47,    48,    17,   233,    78,    18,
      18,    54,    55,    56,    57,    58,    18,    18,   189,    78,
      78,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    17,    78,   302,    80,    81,   215,
     200,    24,   244,   374,   167,   366,   358,   365,    31,   368,
     343,   351,   390,    -1,   166,    77,   298,    -1,   127,    -1,
      -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    54,    55,    56,    57,    58,    31,    -1,    -1,    -1,
      -1,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    75,    76,    -1,    78,    -1,    80,    81,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    17,    64,
      65,    66,    -1,    -1,    -1,    24,    -1,    -1,    -1,    74,
      75,    76,    31,    78,    -1,    80,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    54,    55,    56,    57,    58,
      31,    -1,    -1,    -1,    -1,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,    78,
      -1,    80,    81,    54,    55,    56,    57,    58,    -1,    23,
      24,    25,    -1,    64,    65,    66,    45,    46,    47,    48,
      -1,    -1,    -1,    74,    75,    76,    -1,    78,    -1,    80,
      81,    45,    46,    47,    48,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    84,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    33,    34,    51,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    98,
      99,   100,   107,   113,   114,   118,   119,   120,   142,     6,
       8,     9,     6,     8,    78,     7,     8,     3,    36,    38,
      78,     3,     3,     3,     3,     3,    52,    17,    24,    31,
      54,    55,    56,    57,    58,    64,    65,    66,    74,    75,
      76,    78,    80,    81,   111,   117,   130,   131,   132,   133,
     134,     3,    78,    78,     8,    78,    78,     3,     3,    38,
      78,    78,    42,    53,   117,   117,    35,    43,    78,   136,
     136,    19,    23,    24,    25,    81,   135,    17,    17,   131,
      38,    17,    44,    78,     3,     3,    78,    37,    39,   138,
      78,   116,    80,    18,    78,    81,    78,   117,   117,   117,
     117,   117,    18,    74,    78,    81,    24,    78,   111,   112,
      17,    78,    78,   102,   106,    78,    44,     3,    17,   109,
      17,    45,    46,    47,    48,    67,    68,    69,    70,    71,
      72,    73,   117,   140,   141,     3,    68,    19,   115,    36,
     136,   136,   135,   136,    18,    18,    19,    35,    18,    19,
      74,    75,    18,    19,    35,    18,    19,   112,   136,    19,
     101,    26,    27,    28,    29,    30,   105,    17,    78,   112,
      19,   108,   119,    47,    45,    48,    67,   141,    40,    41,
     139,    17,    17,   112,   133,   116,   138,     6,   136,   136,
      78,    78,   136,    78,   136,   112,    78,   136,   112,    19,
      19,    49,   137,   102,    18,    17,    32,    47,   103,    78,
      97,    17,    19,   110,   109,     3,    18,    17,   117,   140,
     140,   119,   119,   115,     3,    78,    18,    18,    18,    18,
      19,    18,    19,    18,   112,    78,    50,   138,   101,     3,
      74,   104,    31,    19,    96,    97,   112,    18,   108,   141,
      24,   111,   112,   119,   139,   139,    18,    18,     3,   136,
     136,   136,   136,   112,   136,   112,   136,    19,   136,    78,
      61,   125,    18,    97,    18,    96,   110,    17,   117,    74,
      75,    19,    18,    18,    18,    19,   112,   137,   136,    62,
      60,   121,   103,    96,     3,    18,   119,   112,   136,   136,
     112,    18,    44,    78,   127,    62,     3,    18,   110,    18,
     136,   140,    35,    19,   126,    78,   123,    18,   136,   139,
      78,   127,    63,   128,    11,    35,    59,   124,    19,   122,
      49,   129,   126,   112,   130,    78,   123,    50,   138,   141,
      17,   124,   122,    78,   125,   130,    78,    81,    44,   121,
      17,    18,    35,    18,   140,    78,    81,   141,    78,   141,
     139,    18,    35,    18,   112,    18,   112,   129,    78,   141,
      18,   112
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    83,    84,    84,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    95,    96,    96,    97,    98,    99,   100,   101,
     101,   102,   102,   103,   103,   103,   104,   105,   105,   105,
     105,   105,   106,   107,   108,   108,   109,   110,   110,   111,
     111,   111,   111,   111,   112,   112,   112,   113,   114,   115,
     115,   116,   116,   116,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   118,   119,   119,
     119,   120,   121,   121,   122,   122,   123,   123,   124,   124,
     124,   125,   125,   126,   126,   127,   127,   128,   128,   128,
     128,   128,   128,   128,   129,   129,   130,   130,   130,   130,
     130,   131,   131,   131,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   133,   133,   133,   133,   133,   133,   133,
     134,   135,   135,   136,   136,   136,   137,   137,   138,   138,
     139,   139,   139,   140,   140,   140,   140,   140,   140,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   142
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,    10,    11,     0,     3,     1,     4,     5,     8,     0,
       3,     6,     3,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     7,     0,     3,     4,     0,     3,     1,
       1,     1,     1,     1,     1,     2,     2,     5,     7,     0,
       3,     3,     5,     3,     3,     3,     2,     3,     3,     3,
       1,     2,     4,     2,     4,     1,     1,     1,     9,    16,
       2,     2,     0,     4,     0,     3,     2,     4,     0,     1,
       1,     0,     5,     0,     3,     1,     3,     0,     7,     7,
       9,     7,     7,     9,     0,     7,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     7,     5,     7,     7,     9,
       9,    11,    10,     5,     5,     7,     5,     7,     7,     4,
       2,     0,     3,     0,     1,     2,     0,     4,     0,     3,
       0,     3,     3,     3,     8,     5,     5,     4,     7,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       2,     1,     2,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 22: /* exit: EXIT SEMICOLON  */
#line 240 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1621 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 245 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1629 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 250 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1637 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 256 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1645 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 262 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1653 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 268 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1661 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 274 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1670 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 280 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1678 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 286 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1687 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON  */
#line 294 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			
		}
#line 1697 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON  */
#line 300 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $8);
		}
#line 1707 "yacc_sql.tab.c"
    break;

  case 34: /* attr_name_list: COMMA attr_name attr_name_list  */
#line 309 "yacc_sql.y"
                                         {

	}
#line 1715 "yacc_sql.tab.c"
    break;

  case 35: /* attr_name: ID  */
#line 314 "yacc_sql.y"
              {
	create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $2);
}
#line 1724 "yacc_sql.tab.c"
    break;

  case 36: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 320 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1733 "yacc_sql.tab.c"
    break;

  case 37: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 327 "yacc_sql.y"
                                    {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1742 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 335 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1754 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 345 "yacc_sql.y"
                                   {    }
#line 1760 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE nullable  */
#line 350 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number), (yyvsp[0].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1775 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type nullable  */
#line 361 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, (yyvsp[0].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1790 "yacc_sql.tab.c"
    break;

  case 43: /* nullable: %empty  */
#line 374 "yacc_sql.y"
        { (yyval.number)=0; }
#line 1796 "yacc_sql.tab.c"
    break;

  case 44: /* nullable: NULLABLE  */
#line 375 "yacc_sql.y"
                   { (yyval.number)=1; }
#line 1802 "yacc_sql.tab.c"
    break;

  case 45: /* nullable: NOT NULL_T  */
#line 376 "yacc_sql.y"
                     { (yyval.number)=2; }
#line 1808 "yacc_sql.tab.c"
    break;

  case 46: /* number: NUMBER  */
#line 380 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1814 "yacc_sql.tab.c"
    break;

  case 47: /* type: INT_T  */
#line 383 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1820 "yacc_sql.tab.c"
    break;

  case 48: /* type: STRING_T  */
#line 384 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1826 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 385 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1832 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 386 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1838 "yacc_sql.tab.c"
    break;

  case 51: /* type: TEXT_T  */
#line 387 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1844 "yacc_sql.tab.c"
    break;

  case 52: /* ID_get: ID  */
#line 391 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1853 "yacc_sql.tab.c"
    break;

  case 53: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 400 "yacc_sql.y"
                {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string), CONTEXT->insert_list, CONTEXT->insert_num);
      //临时变量清零
      CONTEXT->value_length=0;
	  CONTEXT->insert_num=0;
	  memset(CONTEXT->insert_list, 0, sizeof(CONTEXT->insert_list));
    }
#line 1873 "yacc_sql.tab.c"
    break;

  case 55: /* tuple_list: COMMA tuple tuple_list  */
#line 418 "yacc_sql.y"
                                 {
	}
#line 1880 "yacc_sql.tab.c"
    break;

  case 56: /* tuple: LBRACE value_with_neg value_list RBRACE  */
#line 424 "yacc_sql.y"
                                                {
		insert_init(&CONTEXT->insert_list[CONTEXT->insert_num++], CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1889 "yacc_sql.tab.c"
    break;

  case 58: /* value_list: COMMA value_with_neg value_list  */
#line 432 "yacc_sql.y"
                                       { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1897 "yacc_sql.tab.c"
    break;

  case 59: /* value: NUMBER  */
#line 437 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1905 "yacc_sql.tab.c"
    break;

  case 60: /* value: FLOAT  */
#line 440 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1913 "yacc_sql.tab.c"
    break;

  case 61: /* value: DATE  */
#line 443 "yacc_sql.y"
             {
		(yyvsp[0].string) = substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);
		int res = value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		if (res != 0) {
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			yyresult = 2;
			goto yyreturnlab;
		}
	}
#line 1927 "yacc_sql.tab.c"
    break;

  case 62: /* value: SSS  */
#line 452 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1936 "yacc_sql.tab.c"
    break;

  case 63: /* value: NULL_T  */
#line 456 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1944 "yacc_sql.tab.c"
    break;

  case 64: /* value_with_neg: value  */
#line 462 "yacc_sql.y"
              {
	}
#line 1951 "yacc_sql.tab.c"
    break;

  case 65: /* value_with_neg: SUB_T NUMBER  */
#line 464 "yacc_sql.y"
                       {
		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number) * -1);
	}
#line 1959 "yacc_sql.tab.c"
    break;

  case 66: /* value_with_neg: SUB_T FLOAT  */
#line 467 "yacc_sql.y"
                      {
		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats) * -1.0);
	}
#line 1967 "yacc_sql.tab.c"
    break;

  case 67: /* delete: DELETE FROM ID where SEMICOLON  */
#line 473 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1979 "yacc_sql.tab.c"
    break;

  case 68: /* updates: UPDATE ID SET modify_expr modify_list where SEMICOLON  */
#line 493 "yacc_sql.y"
                                                              {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		updates_select_init(&CONTEXT->ssql->sstr.updates, (yyvsp[-5].string), CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
		CONTEXT->select_num = 0;
		CONTEXT->attr_num = 0;
		CONTEXT->expression_attr_num = 0;
	}
#line 1992 "yacc_sql.tab.c"
    break;

  case 70: /* modify_list: COMMA modify_expr modify_list  */
#line 504 "yacc_sql.y"
                                        {

	}
#line 2000 "yacc_sql.tab.c"
    break;

  case 71: /* modify_expr: ID EQ value_with_neg  */
#line 510 "yacc_sql.y"
                             {
		updates_append_value(&CONTEXT->ssql->sstr.updates, &CONTEXT->values[CONTEXT->value_length - 1], (yyvsp[-2].string));
	}
#line 2008 "yacc_sql.tab.c"
    break;

  case 72: /* modify_expr: ID EQ LBRACE select_clause RBRACE  */
#line 513 "yacc_sql.y"
                                           {
		Value value;
		value_init_select(&value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, (yyvsp[-4].string));
	}
#line 2018 "yacc_sql.tab.c"
    break;

  case 73: /* modify_expr: ID EQ agg  */
#line 518 "yacc_sql.y"
                    {
		Value value;
		// value_init_agg(&value, &CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]-1]);
		// CONTEXT->select_attr_num[CONTEXT->select_num]--;
		value_init_agg(&value, &CONTEXT->attrs[--CONTEXT->expression_attr_num]);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, (yyvsp[-2].string));
	}
#line 2030 "yacc_sql.tab.c"
    break;

  case 74: /* exp: exp ADD_T exp  */
#line 529 "yacc_sql.y"
                      { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, ADD); }
#line 2036 "yacc_sql.tab.c"
    break;

  case 75: /* exp: exp SUB_T exp  */
#line 530 "yacc_sql.y"
                        { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, SUB); }
#line 2042 "yacc_sql.tab.c"
    break;

  case 76: /* exp: SUB_T exp  */
#line 531 "yacc_sql.y"
                    {
		// Value left_value;
		// value_init_integer(&left_value, 0);
		// Exp *left_exp = create_expression(NULL, NULL, &left_value, NULL, VAL);
		(yyval.exp1) = create_expression(NULL, (yyvsp[0].exp1), NULL, NULL, SUB);
	}
#line 2053 "yacc_sql.tab.c"
    break;

  case 77: /* exp: exp STAR exp  */
#line 537 "yacc_sql.y"
                       { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, MUL); }
#line 2059 "yacc_sql.tab.c"
    break;

  case 78: /* exp: exp DIV_T exp  */
#line 538 "yacc_sql.y"
                        { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, DIV); }
#line 2065 "yacc_sql.tab.c"
    break;

  case 79: /* exp: LBRACE exp RBRACE  */
#line 539 "yacc_sql.y"
                            { 
		Exp *exp = (yyvsp[-1].exp1);
		++exp->lbrace;
		++exp->rbrace;
		(yyval.exp1) = exp; 
	}
#line 2076 "yacc_sql.tab.c"
    break;

  case 80: /* exp: value  */
#line 545 "yacc_sql.y"
                { 
		(yyval.exp1) = create_expression(NULL, NULL, &CONTEXT->values[CONTEXT->value_length - 1], NULL, VAL); 
	}
#line 2084 "yacc_sql.tab.c"
    break;

  case 81: /* exp: ID alias_ID  */
#line 548 "yacc_sql.y"
                      { 
		RelAttr attr;
		relation_attr_init_with_alias(&attr, NULL, (yyvsp[-1].string), (yyvsp[0].string));
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
#line 2095 "yacc_sql.tab.c"
    break;

  case 82: /* exp: ID DOT ID alias_ID  */
#line 554 "yacc_sql.y"
                             {
		RelAttr attr;
		
		relation_attr_init_with_alias(&attr, (yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[0].string));
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
#line 2107 "yacc_sql.tab.c"
    break;

  case 83: /* exp: STAR alias_ID  */
#line 561 "yacc_sql.y"
                        {
		if ((yyvsp[0].string) != NULL) {
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			yyresult = 2;
			goto yyreturnlab;
		}
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
#line 2124 "yacc_sql.tab.c"
    break;

  case 84: /* exp: ID DOT STAR alias_ID  */
#line 573 "yacc_sql.y"
                               {
		if ((yyvsp[0].string) != NULL) {
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			yyresult = 2;
			goto yyreturnlab;
		}
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), "*");
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
#line 2141 "yacc_sql.tab.c"
    break;

  case 85: /* exp: agg  */
#line 585 "yacc_sql.y"
              {
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &CONTEXT->attrs[CONTEXT->expression_attr_num - 1], ATTR);
	}
#line 2149 "yacc_sql.tab.c"
    break;

  case 86: /* exp: func_with_param  */
#line 588 "yacc_sql.y"
                          {
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &CONTEXT->attrs[CONTEXT->expression_attr_num - 1], ATTR);
	}
#line 2157 "yacc_sql.tab.c"
    break;

  case 87: /* select_begin: SELECT  */
#line 595 "yacc_sql.y"
               {
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
#line 2173 "yacc_sql.tab.c"
    break;

  case 88: /* select_clause: select_begin select_attr FROM ID alias_ID rel_list where group_by order_by  */
#line 608 "yacc_sql.y"
                                                                                   {
		// 当进入该语句中时，depth一定是>=1的，不用担心越界问题
		// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
		// selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], $4);
		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-5].string), (yyvsp[-4].string));

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
#line 2211 "yacc_sql.tab.c"
    break;

  case 89: /* select_clause: select_begin select_attr FROM ID alias_ID INNER JOIN ID alias_ID ON condition condition_list join_list where group_by order_by  */
#line 641 "yacc_sql.y"
                                                                                                                                         {
		// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;

		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-8].string), (yyvsp[-7].string));
		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-12].string), (yyvsp[-11].string));

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
#line 2250 "yacc_sql.tab.c"
    break;

  case 90: /* select_clause: select_begin select_attr  */
#line 675 "yacc_sql.y"
                                   {
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
#line 2280 "yacc_sql.tab.c"
    break;

  case 91: /* select: select_clause SEMICOLON  */
#line 703 "yacc_sql.y"
                            {
		// 这里说明select是主语句
		CONTEXT->ssql->flag=SCF_SELECT;//"select";
		CONTEXT->ssql->sstr.selection = CONTEXT->selections[CONTEXT->select_num-1];
	}
#line 2290 "yacc_sql.tab.c"
    break;

  case 93: /* order_by: ORDER BY order_item order_item_list  */
#line 713 "yacc_sql.y"
                                              {
		
	}
#line 2298 "yacc_sql.tab.c"
    break;

  case 95: /* order_item_list: COMMA order_item order_item_list  */
#line 720 "yacc_sql.y"
                                           {}
#line 2304 "yacc_sql.tab.c"
    break;

  case 96: /* order_item: ID order  */
#line 724 "yacc_sql.y"
                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		OrderBy order_by; 
		order_by_init(&order_by, &attr, (yyvsp[0].number));
		selects_append_order_by(&CONTEXT->selections[CONTEXT->select_num], &order_by);
	}
#line 2316 "yacc_sql.tab.c"
    break;

  case 97: /* order_item: ID DOT ID order  */
#line 731 "yacc_sql.y"
                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		OrderBy order_by;
		order_by_init(&order_by, &attr, (yyvsp[0].number));
		selects_append_order_by(&CONTEXT->selections[CONTEXT->select_num], &order_by);
	}
#line 2328 "yacc_sql.tab.c"
    break;

  case 98: /* order: %empty  */
#line 740 "yacc_sql.y"
        { (yyval.number) = 0; }
#line 2334 "yacc_sql.tab.c"
    break;

  case 99: /* order: ASC  */
#line 741 "yacc_sql.y"
              { (yyval.number) = 0; }
#line 2340 "yacc_sql.tab.c"
    break;

  case 100: /* order: DESC  */
#line 742 "yacc_sql.y"
               { (yyval.number) = 1; }
#line 2346 "yacc_sql.tab.c"
    break;

  case 102: /* group_by: GROUP BY group_item group_item_list having  */
#line 746 "yacc_sql.y"
                                                     {
	}
#line 2353 "yacc_sql.tab.c"
    break;

  case 104: /* group_item_list: COMMA group_item group_item_list  */
#line 752 "yacc_sql.y"
                                           {}
#line 2359 "yacc_sql.tab.c"
    break;

  case 105: /* group_item: ID  */
#line 756 "yacc_sql.y"
           {
		RelAttr attr;	
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		selects_append_group_by(&CONTEXT->selections[CONTEXT->select_num], &attr);
	}
#line 2369 "yacc_sql.tab.c"
    break;

  case 106: /* group_item: ID DOT ID  */
#line 761 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		selects_append_group_by(&CONTEXT->selections[CONTEXT->select_num], &attr);
	}
#line 2379 "yacc_sql.tab.c"
    break;

  case 108: /* having: HAVING agg_func LBRACE STAR RBRACE comOp value_with_neg  */
#line 768 "yacc_sql.y"
                                                                  {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, "*", (yyvsp[-5].number), NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], (yyvsp[-1].number), 0);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
#line 2391 "yacc_sql.tab.c"
    break;

  case 109: /* having: HAVING agg_func LBRACE ID RBRACE comOp value_with_neg  */
#line 775 "yacc_sql.y"
                                                                {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, (yyvsp[-3].string), (yyvsp[-5].number), NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], (yyvsp[-1].number), 0);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
#line 2403 "yacc_sql.tab.c"
    break;

  case 110: /* having: HAVING agg_func LBRACE ID DOT ID RBRACE comOp value_with_neg  */
#line 782 "yacc_sql.y"
                                                                       {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, (yyvsp[-5].string), (yyvsp[-3].string), (yyvsp[-7].number), NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], (yyvsp[-1].number), 0);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
#line 2415 "yacc_sql.tab.c"
    break;

  case 111: /* having: HAVING value_with_neg comOp agg_func LBRACE STAR RBRACE  */
#line 789 "yacc_sql.y"
                                                                   {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, "*", (yyvsp[-3].number), NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], (yyvsp[-4].number), 1);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
#line 2427 "yacc_sql.tab.c"
    break;

  case 112: /* having: HAVING value_with_neg comOp agg_func LBRACE ID RBRACE  */
#line 796 "yacc_sql.y"
                                                                {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, (yyvsp[-1].string), (yyvsp[-3].number), NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], (yyvsp[-4].number), 1);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
#line 2439 "yacc_sql.tab.c"
    break;

  case 113: /* having: HAVING value_with_neg comOp agg_func LBRACE ID DOT ID RBRACE  */
#line 803 "yacc_sql.y"
                                                                       {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, (yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[-5].number), NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], (yyvsp[-6].number), 1);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
#line 2451 "yacc_sql.tab.c"
    break;

  case 115: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 813 "yacc_sql.y"
        {
		selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-4].string));
	}
#line 2459 "yacc_sql.tab.c"
    break;

  case 116: /* agg_func: MAX_T  */
#line 819 "yacc_sql.y"
              { (yyval.number)=MAX; }
#line 2465 "yacc_sql.tab.c"
    break;

  case 117: /* agg_func: MIN_T  */
#line 820 "yacc_sql.y"
                { (yyval.number)=MIN; }
#line 2471 "yacc_sql.tab.c"
    break;

  case 118: /* agg_func: COUNT_T  */
#line 821 "yacc_sql.y"
                  { (yyval.number)=COUNT; }
#line 2477 "yacc_sql.tab.c"
    break;

  case 119: /* agg_func: AVG_T  */
#line 822 "yacc_sql.y"
                { (yyval.number)=AVG; }
#line 2483 "yacc_sql.tab.c"
    break;

  case 120: /* agg_func: SUM_T  */
#line 823 "yacc_sql.y"
                { (yyval.number)=SUM; }
#line 2489 "yacc_sql.tab.c"
    break;

  case 121: /* func: LENGTH_T  */
#line 827 "yacc_sql.y"
                 { (yyval.number)=LENGTH; }
#line 2495 "yacc_sql.tab.c"
    break;

  case 122: /* func: ROUND_T  */
#line 828 "yacc_sql.y"
                  { (yyval.number)=ROUND; }
#line 2501 "yacc_sql.tab.c"
    break;

  case 123: /* func: DATE_FORMAT_T  */
#line 829 "yacc_sql.y"
                        { (yyval.number)=DATE_FORMAT; }
#line 2507 "yacc_sql.tab.c"
    break;

  case 124: /* func_with_param: func LBRACE ID RBRACE alias_ID  */
#line 833 "yacc_sql.y"
                                       {
		RelAttr attr;
		relation_attr_init_with_func(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].number), (yyvsp[0].string));
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	  }
#line 2517 "yacc_sql.tab.c"
    break;

  case 125: /* func_with_param: func LBRACE ID DOT ID RBRACE alias_ID  */
#line 838 "yacc_sql.y"
                                                {
		RelAttr attr;
		relation_attr_init_with_func(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-6].number), (yyvsp[0].string));
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2527 "yacc_sql.tab.c"
    break;

  case 126: /* func_with_param: func LBRACE value_with_neg RBRACE alias_ID  */
#line 843 "yacc_sql.y"
                                                     {
		RelAttr attr;
		relation_attr_init_with_func_value(&attr, (yyvsp[-4].number), &CONTEXT->values[CONTEXT->value_length - 1], NULL, (yyvsp[0].string));
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2537 "yacc_sql.tab.c"
    break;

  case 127: /* func_with_param: func LBRACE value_with_neg COMMA value_with_neg RBRACE alias_ID  */
#line 848 "yacc_sql.y"
                                                                          {
		RelAttr attr;
		relation_attr_init_with_func_value(&attr, (yyvsp[-6].number), &CONTEXT->values[CONTEXT->value_length - 2], &CONTEXT->values[CONTEXT->value_length - 1], (yyvsp[0].string));
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2547 "yacc_sql.tab.c"
    break;

  case 128: /* func_with_param: func LBRACE ID COMMA value_with_neg RBRACE alias_ID  */
#line 853 "yacc_sql.y"
                                                              {
		RelAttr attr;
		relation_attr_init_with_func(&attr, NULL, (yyvsp[-4].string), (yyvsp[-6].number), (yyvsp[0].string));
		relation_attr_init_with_func_append_value(&attr, &CONTEXT->values[CONTEXT->value_length - 1]);
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2558 "yacc_sql.tab.c"
    break;

  case 129: /* func_with_param: func LBRACE ID DOT ID COMMA value_with_neg RBRACE alias_ID  */
#line 859 "yacc_sql.y"
                                                                     {
		RelAttr attr;
		relation_attr_init_with_func(&attr, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-8].number), (yyvsp[0].string));
		relation_attr_init_with_func_append_value(&attr, &CONTEXT->values[CONTEXT->value_length - 1]);
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2569 "yacc_sql.tab.c"
    break;

  case 130: /* func_with_param: func LBRACE ID COMMA value_with_neg COMMA value_with_neg RBRACE alias_ID  */
#line 865 "yacc_sql.y"
                                                                                   {
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2579 "yacc_sql.tab.c"
    break;

  case 131: /* func_with_param: func LBRACE ID DOT ID COMMA value_with_neg COMMA value_with_neg RBRACE alias_ID  */
#line 870 "yacc_sql.y"
                                                                                          {
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2589 "yacc_sql.tab.c"
    break;

  case 132: /* func_with_param: func func LBRACE value_with_neg COMMA value_with_neg COMMA value_with_neg RBRACE alias_ID  */
#line 875 "yacc_sql.y"
                                                                                                    {
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2599 "yacc_sql.tab.c"
    break;

  case 133: /* agg: agg_func LBRACE STAR RBRACE alias_ID  */
#line 884 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, "*", (yyvsp[-4].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2610 "yacc_sql.tab.c"
    break;

  case 134: /* agg: agg_func LBRACE ID RBRACE alias_ID  */
#line 890 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2621 "yacc_sql.tab.c"
    break;

  case 135: /* agg: agg_func LBRACE ID DOT ID RBRACE alias_ID  */
#line 896 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-6].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2632 "yacc_sql.tab.c"
    break;

  case 136: /* agg: agg_func LBRACE NUMBER RBRACE alias_ID  */
#line 902 "yacc_sql.y"
                                                 {
		RelAttr attr;
		relation_attr_init_with_agg_num(&attr, (yyvsp[-4].number), (yyvsp[-2].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2643 "yacc_sql.tab.c"
    break;

  case 137: /* agg: agg_func LBRACE STAR COMMA ID RBRACE alias_ID  */
#line 908 "yacc_sql.y"
                                                        {
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2653 "yacc_sql.tab.c"
    break;

  case 138: /* agg: agg_func LBRACE ID COMMA ID RBRACE alias_ID  */
#line 913 "yacc_sql.y"
                                                      {
		// 错误类型
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2664 "yacc_sql.tab.c"
    break;

  case 139: /* agg: agg_func LBRACE RBRACE alias_ID  */
#line 919 "yacc_sql.y"
                                          {
		// 错误类型
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2675 "yacc_sql.tab.c"
    break;

  case 140: /* select_attr: exp attr_list  */
#line 931 "yacc_sql.y"
                      {
		CONTEXT->expressions[CONTEXT->expr_num++] = (yyvsp[-1].exp1);
		CONTEXT->attr_num = CONTEXT->expression_attr_num;
	}
#line 2684 "yacc_sql.tab.c"
    break;

  case 142: /* attr_list: COMMA exp attr_list  */
#line 939 "yacc_sql.y"
                              {
		CONTEXT->expressions[CONTEXT->expr_num++] = (yyvsp[-1].exp1);
		// 因为现在条件语句中的RelAttr也会占用全局的attrs
		// 需要进行一下区别，attr_num只记录
		CONTEXT->attr_num = CONTEXT->expression_attr_num;
	}
#line 2695 "yacc_sql.tab.c"
    break;

  case 143: /* alias_ID: %empty  */
#line 949 "yacc_sql.y"
        { (yyval.string) = NULL; }
#line 2701 "yacc_sql.tab.c"
    break;

  case 144: /* alias_ID: ID  */
#line 950 "yacc_sql.y"
             { (yyval.string) = (yyvsp[0].string); }
#line 2707 "yacc_sql.tab.c"
    break;

  case 145: /* alias_ID: AS ID  */
#line 951 "yacc_sql.y"
                { (yyval.string) = (yyvsp[0].string); }
#line 2713 "yacc_sql.tab.c"
    break;

  case 147: /* rel_list: COMMA ID alias_ID rel_list  */
#line 956 "yacc_sql.y"
                                 {	
		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-2].string), (yyvsp[-1].string));
	}
#line 2721 "yacc_sql.tab.c"
    break;

  case 149: /* where: WHERE condition condition_list  */
#line 962 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
	}
#line 2729 "yacc_sql.tab.c"
    break;

  case 151: /* condition_list: AND condition condition_list  */
#line 970 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		CONTEXT->selections[CONTEXT->select_num].is_and = 1; 
	}
#line 2738 "yacc_sql.tab.c"
    break;

  case 152: /* condition_list: OR condition condition_list  */
#line 974 "yacc_sql.y"
                                      {
		CONTEXT->selections[CONTEXT->select_num].is_and = 0;
	}
#line 2746 "yacc_sql.tab.c"
    break;

  case 153: /* condition: exp comOp exp  */
#line 981 "yacc_sql.y"
                      {
		Exp *left_exp = (yyvsp[-2].exp1);
		Exp *right_exp = (yyvsp[0].exp1);
		Condition condition;
		condition_init_with_exp(&condition, (yyvsp[-1].number), left_exp, right_exp);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
#line 2759 "yacc_sql.tab.c"
    break;

  case 154: /* condition: exp comOp LBRACE value_with_neg COMMA value_with_neg value_list RBRACE  */
#line 989 "yacc_sql.y"
                                                                                 {
		// comOp只能是in/not in, exists/not exists
		// 同除了包含LBRACE value value_list RBRACE的条件语句，comOp都只能是非in/not in, exists/not exists
		// RelAttr left_attr;
		// relation_attr_init(&left_attr, NULL, $1);
		Exp *left_exp  = (yyvsp[-7].exp1);
		Value right_value;
		value_init_set(&right_value, CONTEXT->values, CONTEXT->cursor_value[CONTEXT->depth], CONTEXT->value_length - CONTEXT->cursor_value[CONTEXT->depth]);
		Exp *right_exp = create_expression(NULL, NULL, &right_value, NULL, VAL);

		Condition condition;

		condition_init_with_exp(&condition, (yyvsp[-6].number), left_exp, right_exp);
		// condition_init(&condition, $2, 1, &left_attr, NULL, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		/// 复原同一深度的cursor_value[]，防止和同一深度其他的SETS类型value冲突
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
#line 2782 "yacc_sql.tab.c"
    break;

  case 155: /* condition: LBRACE select_clause RBRACE comOp exp  */
#line 1007 "yacc_sql.y"
                                                {
		Value left_value;
		value_init_select(&left_value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		
		Condition condition;
		Exp *left_exp = create_expression(NULL, NULL, &left_value, NULL, VAL);
		Exp *right_exp = (yyvsp[0].exp1);
		condition_init_with_exp(&condition, (yyvsp[-1].number), left_exp, right_exp);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
#line 2798 "yacc_sql.tab.c"
    break;

  case 156: /* condition: exp comOp LBRACE select_clause RBRACE  */
#line 1018 "yacc_sql.y"
                                                {
		Value right_value;
		value_init_select(&right_value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		
		Condition condition;
		Exp *left_exp = (yyvsp[-4].exp1);
		Exp *right_exp = create_expression(NULL, NULL, &right_value, NULL, VAL);
		condition_init_with_exp(&condition, (yyvsp[-3].number), left_exp, right_exp);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
#line 2814 "yacc_sql.tab.c"
    break;

  case 157: /* condition: comOp LBRACE select_clause RBRACE  */
#line 1029 "yacc_sql.y"
                                            {
		if ((yyvsp[-3].number) != EXISTS_OP && (yyvsp[-3].number) != NOT_EXISTS_OP) {
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			yyresult = 2;
			goto yyreturnlab;
		}
		Value right_value;
		value_init_select(&right_value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		Condition condition;
		condition_init(&condition, (yyvsp[-3].number), -1, NULL, NULL, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
#line 2832 "yacc_sql.tab.c"
    break;

  case 158: /* condition: LBRACE select_clause RBRACE comOp LBRACE select_clause RBRACE  */
#line 1042 "yacc_sql.y"
                                                                        {
		Value left_value;
		value_init_select(&left_value, &CONTEXT->selections[CONTEXT->select_num - 2]);
		Value right_value;
		value_init_select(&right_value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		Condition condition;

		condition_init(&condition, (yyvsp[-3].number), 0, NULL, &left_value, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
#line 2848 "yacc_sql.tab.c"
    break;

  case 159: /* comOp: EQ  */
#line 1056 "yacc_sql.y"
             { (yyval.number) = EQUAL_TO; }
#line 2854 "yacc_sql.tab.c"
    break;

  case 160: /* comOp: LT  */
#line 1057 "yacc_sql.y"
         { (yyval.number) = LESS_THAN; }
#line 2860 "yacc_sql.tab.c"
    break;

  case 161: /* comOp: GT  */
#line 1058 "yacc_sql.y"
         { (yyval.number) = GREAT_THAN; }
#line 2866 "yacc_sql.tab.c"
    break;

  case 162: /* comOp: LE  */
#line 1059 "yacc_sql.y"
         { (yyval.number) = LESS_EQUAL; }
#line 2872 "yacc_sql.tab.c"
    break;

  case 163: /* comOp: GE  */
#line 1060 "yacc_sql.y"
         { (yyval.number) = GREAT_EQUAL; }
#line 2878 "yacc_sql.tab.c"
    break;

  case 164: /* comOp: NE  */
#line 1061 "yacc_sql.y"
         { (yyval.number) = NOT_EQUAL; }
#line 2884 "yacc_sql.tab.c"
    break;

  case 165: /* comOp: LIKE  */
#line 1062 "yacc_sql.y"
               { (yyval.number) = LIKE_MATCH; }
#line 2890 "yacc_sql.tab.c"
    break;

  case 166: /* comOp: NOT LIKE  */
#line 1063 "yacc_sql.y"
                   { (yyval.number) = NOT_LIKE; }
#line 2896 "yacc_sql.tab.c"
    break;

  case 167: /* comOp: IN  */
#line 1064 "yacc_sql.y"
             { (yyval.number) = IN_OP; }
#line 2902 "yacc_sql.tab.c"
    break;

  case 168: /* comOp: NOT IN  */
#line 1065 "yacc_sql.y"
                 { (yyval.number) = NOT_IN_OP; }
#line 2908 "yacc_sql.tab.c"
    break;

  case 169: /* comOp: EXIST  */
#line 1066 "yacc_sql.y"
                { (yyval.number) =EXISTS_OP; }
#line 2914 "yacc_sql.tab.c"
    break;

  case 170: /* comOp: NOT EXIST  */
#line 1067 "yacc_sql.y"
                    { (yyval.number) = NOT_EXISTS_OP; }
#line 2920 "yacc_sql.tab.c"
    break;

  case 171: /* comOp: IS  */
#line 1068 "yacc_sql.y"
             { (yyval.number) = IS_OP; }
#line 2926 "yacc_sql.tab.c"
    break;

  case 172: /* comOp: IS NOT  */
#line 1069 "yacc_sql.y"
                 { (yyval.number) = IS_NOT_OP; }
#line 2932 "yacc_sql.tab.c"
    break;

  case 173: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1074 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2941 "yacc_sql.tab.c"
    break;


#line 2945 "yacc_sql.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1079 "yacc_sql.y"

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
