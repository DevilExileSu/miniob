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
  YYSYMBOL_LIKE = 64,                      /* LIKE  */
  YYSYMBOL_EQ = 65,                        /* EQ  */
  YYSYMBOL_LT = 66,                        /* LT  */
  YYSYMBOL_GT = 67,                        /* GT  */
  YYSYMBOL_LE = 68,                        /* LE  */
  YYSYMBOL_GE = 69,                        /* GE  */
  YYSYMBOL_NE = 70,                        /* NE  */
  YYSYMBOL_NUMBER = 71,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 72,                     /* FLOAT  */
  YYSYMBOL_DATE = 73,                      /* DATE  */
  YYSYMBOL_TEXT = 74,                      /* TEXT  */
  YYSYMBOL_ID = 75,                        /* ID  */
  YYSYMBOL_PATH = 76,                      /* PATH  */
  YYSYMBOL_SSS = 77,                       /* SSS  */
  YYSYMBOL_STAR = 78,                      /* STAR  */
  YYSYMBOL_STRING_V = 79,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 80,                  /* $accept  */
  YYSYMBOL_commands = 81,                  /* commands  */
  YYSYMBOL_command = 82,                   /* command  */
  YYSYMBOL_exit = 83,                      /* exit  */
  YYSYMBOL_help = 84,                      /* help  */
  YYSYMBOL_sync = 85,                      /* sync  */
  YYSYMBOL_begin = 86,                     /* begin  */
  YYSYMBOL_commit = 87,                    /* commit  */
  YYSYMBOL_rollback = 88,                  /* rollback  */
  YYSYMBOL_drop_table = 89,                /* drop_table  */
  YYSYMBOL_show_tables = 90,               /* show_tables  */
  YYSYMBOL_desc_table = 91,                /* desc_table  */
  YYSYMBOL_create_index = 92,              /* create_index  */
  YYSYMBOL_attr_name_list = 93,            /* attr_name_list  */
  YYSYMBOL_attr_name = 94,                 /* attr_name  */
  YYSYMBOL_drop_index = 95,                /* drop_index  */
  YYSYMBOL_show_index = 96,                /* show_index  */
  YYSYMBOL_create_table = 97,              /* create_table  */
  YYSYMBOL_attr_def_list = 98,             /* attr_def_list  */
  YYSYMBOL_attr_def = 99,                  /* attr_def  */
  YYSYMBOL_nullable = 100,                 /* nullable  */
  YYSYMBOL_number = 101,                   /* number  */
  YYSYMBOL_type = 102,                     /* type  */
  YYSYMBOL_ID_get = 103,                   /* ID_get  */
  YYSYMBOL_insert = 104,                   /* insert  */
  YYSYMBOL_tuple_list = 105,               /* tuple_list  */
  YYSYMBOL_tuple = 106,                    /* tuple  */
  YYSYMBOL_value_list = 107,               /* value_list  */
  YYSYMBOL_value = 108,                    /* value  */
  YYSYMBOL_value_with_neg = 109,           /* value_with_neg  */
  YYSYMBOL_delete = 110,                   /* delete  */
  YYSYMBOL_updates = 111,                  /* updates  */
  YYSYMBOL_modify_list = 112,              /* modify_list  */
  YYSYMBOL_modify_expr = 113,              /* modify_expr  */
  YYSYMBOL_exp = 114,                      /* exp  */
  YYSYMBOL_select_begin = 115,             /* select_begin  */
  YYSYMBOL_select_clause = 116,            /* select_clause  */
  YYSYMBOL_select = 117,                   /* select  */
  YYSYMBOL_order_by = 118,                 /* order_by  */
  YYSYMBOL_order_item_list = 119,          /* order_item_list  */
  YYSYMBOL_order_item = 120,               /* order_item  */
  YYSYMBOL_order = 121,                    /* order  */
  YYSYMBOL_group_by = 122,                 /* group_by  */
  YYSYMBOL_group_item_list = 123,          /* group_item_list  */
  YYSYMBOL_group_item = 124,               /* group_item  */
  YYSYMBOL_having = 125,                   /* having  */
  YYSYMBOL_join_list = 126,                /* join_list  */
  YYSYMBOL_agg_func = 127,                 /* agg_func  */
  YYSYMBOL_agg = 128,                      /* agg  */
  YYSYMBOL_select_attr = 129,              /* select_attr  */
  YYSYMBOL_attr_list = 130,                /* attr_list  */
  YYSYMBOL_alias_ID = 131,                 /* alias_ID  */
  YYSYMBOL_rel_list = 132,                 /* rel_list  */
  YYSYMBOL_where = 133,                    /* where  */
  YYSYMBOL_condition_list = 134,           /* condition_list  */
  YYSYMBOL_condition = 135,                /* condition  */
  YYSYMBOL_comOp = 136,                    /* comOp  */
  YYSYMBOL_load_data = 137                 /* load_data  */
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
#define YYLAST   438

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  159
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  353

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   334


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
      75,    76,    77,    78,    79
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   207,   207,   209,   213,   214,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   235,   240,   245,   251,   257,   263,   269,   275,
     281,   288,   294,   303,   304,   309,   314,   322,   329,   338,
     340,   344,   355,   369,   370,   371,   375,   378,   379,   380,
     381,   382,   385,   394,   412,   413,   419,   425,   427,   432,
     435,   438,   447,   451,   457,   459,   462,   467,   488,   498,
     499,   505,   508,   513,   524,   525,   526,   532,   533,   534,
     540,   543,   549,   556,   568,   580,   587,   600,   633,   670,
     678,   680,   685,   687,   691,   698,   707,   708,   709,   712,
     713,   717,   719,   723,   728,   734,   735,   742,   749,   756,
     763,   770,   778,   779,   786,   787,   788,   789,   790,   795,
     801,   807,   813,   819,   824,   830,   842,   848,   850,   860,
     861,   862,   865,   867,   871,   873,   879,   881,   885,   892,
     900,   918,   929,   940,   953,   967,   968,   969,   970,   971,
     972,   973,   974,   975,   976,   977,   978,   979,   980,   984
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
  "ORDER", "GROUP", "BY", "HAVING", "LIKE", "EQ", "LT", "GT", "LE", "GE",
  "NE", "NUMBER", "FLOAT", "DATE", "TEXT", "ID", "PATH", "SSS", "STAR",
  "STRING_V", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "attr_name_list", "attr_name", "drop_index",
  "show_index", "create_table", "attr_def_list", "attr_def", "nullable",
  "number", "type", "ID_get", "insert", "tuple_list", "tuple",
  "value_list", "value", "value_with_neg", "delete", "updates",
  "modify_list", "modify_expr", "exp", "select_begin", "select_clause",
  "select", "order_by", "order_item_list", "order_item", "order",
  "group_by", "group_item_list", "group_item", "having", "join_list",
  "agg_func", "agg", "select_attr", "attr_list", "alias_ID", "rel_list",
  "where", "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-266)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -266,   355,  -266,    38,   101,  -266,   -30,    33,    86,    60,
      63,    69,   105,   118,   146,   147,   149,   104,  -266,  -266,
    -266,  -266,  -266,  -266,  -266,  -266,  -266,  -266,  -266,  -266,
    -266,  -266,  -266,  -266,  -266,   240,   150,  -266,  -266,    82,
      84,   152,    99,   100,   173,   174,   145,  -266,   109,   114,
     160,  -266,  -266,  -266,  -266,  -266,   151,   240,   240,  -266,
    -266,  -266,  -266,  -266,  -266,  -266,  -266,  -266,   -22,  -266,
     -25,  -266,     1,   189,  -266,   170,  -266,   192,   166,   137,
     208,   210,  -266,  -266,   142,   181,   180,   148,   144,    -9,
      -8,   -39,   157,  -266,  -266,  -266,   240,   240,   240,   240,
     240,  -266,    17,   158,   159,   167,   178,  -266,  -266,   222,
     207,   183,   223,   162,   216,   226,  -266,   -25,   -25,  -266,
       1,    -8,    -8,  -266,  -266,   -25,   225,    87,    98,   -25,
    -266,   244,   136,   242,   195,  -266,    27,   254,    56,  -266,
     227,    94,  -266,  -266,  -266,  -266,  -266,  -266,  -266,  -266,
     221,    95,   258,  -266,   124,   148,   180,   270,  -266,  -266,
    -266,  -266,   -25,   -25,   202,   203,   -25,   205,    23,   159,
     263,  -266,  -266,  -266,  -266,  -266,    20,   209,   265,    75,
    -266,   264,   207,   289,   283,  -266,  -266,  -266,  -266,   248,
     183,   183,  -266,   298,   298,  -266,  -266,   216,   307,   239,
    -266,  -266,   304,   306,  -266,   309,   253,   279,   180,   244,
     332,   266,  -266,   305,  -266,  -266,   319,   209,  -266,  -266,
      27,   326,   254,  -266,   333,    56,     5,    95,    95,   327,
     328,  -266,  -266,   347,   -25,   -25,   -25,   -25,   277,   300,
    -266,  -266,  -266,   345,  -266,   209,   346,   319,   264,  -266,
    -266,   276,   353,   356,  -266,  -266,  -266,  -266,  -266,  -266,
    -266,  -266,   354,   -25,   320,   323,    46,   319,   381,   367,
    -266,    56,     5,    53,  -266,  -266,   342,   312,   329,  -266,
    -266,  -266,  -266,   387,   374,   264,   183,   358,   375,   321,
    -266,  -266,   377,    95,   330,   312,   341,    -3,   388,  -266,
     359,  -266,   375,   285,  -266,  -266,   334,  -266,  -266,   321,
    -266,   360,   180,  -266,   333,   394,    22,   388,   337,   300,
     115,    19,  -266,  -266,   369,   323,   397,    13,   398,   183,
    -266,    65,   333,   340,   333,    95,    97,   399,    27,   400,
      27,   359,  -266,   344,  -266,  -266,   333,  -266,  -266,   402,
      27,  -266,  -266
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    86,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     0,     0,     4,    19,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,    25,    26,    27,    23,    22,     0,     0,     0,    63,
     114,   115,   116,   117,   118,    59,    60,    61,   129,    62,
     129,    80,   127,     0,    85,     0,    89,     0,     0,     0,
       0,     0,    30,    29,     0,     0,   134,     0,     0,     0,
      76,     0,     0,   130,    81,    83,     0,     0,     0,     0,
       0,   126,     0,     0,     0,     0,     0,    28,    36,     0,
       0,     0,     0,     0,    69,     0,    79,   129,   129,   131,
     127,    74,    75,    78,    77,   129,     0,     0,     0,   129,
      52,    39,     0,     0,     0,    37,     0,    54,     0,   153,
     157,     0,   155,   151,   145,   146,   147,   148,   149,   150,
       0,   136,     0,    67,     0,     0,   134,     0,    82,    84,
     128,   125,   129,   129,     0,     0,   129,     0,   132,     0,
       0,    47,    48,    49,    50,    51,    43,     0,     0,     0,
      64,    57,     0,     0,     0,   158,   154,   156,   152,     0,
       0,     0,   135,     0,     0,    71,    73,    69,     0,     0,
     122,   120,     0,     0,   119,     0,     0,     0,   134,    39,
       0,     0,    44,     0,    42,    35,    33,     0,    65,    66,
       0,     0,    54,    53,     0,     0,   139,   136,   136,     0,
       0,    70,    68,     0,   129,   129,   129,   129,     0,    99,
      40,    38,    46,     0,    45,     0,     0,    33,    57,    56,
      55,     0,    80,     0,   137,   138,   143,    72,   159,   124,
     121,   123,   132,   129,     0,    90,    43,    33,     0,     0,
      58,     0,   141,     0,   142,   133,     0,     0,     0,    87,
      41,    34,    31,     0,     0,    57,     0,   103,   101,     0,
      32,   144,     0,   136,     0,     0,   105,    96,    92,   140,
     112,   104,   101,     0,   100,    98,     0,    97,    94,     0,
      91,     0,   134,   102,     0,     0,    96,    92,     0,    99,
       0,     0,    95,    93,     0,    90,     0,     0,     0,     0,
      88,     0,     0,     0,     0,   136,     0,     0,     0,     0,
       0,   112,   110,     0,   109,   107,     0,   106,   113,     0,
       0,   111,   108
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -266,  -266,  -266,  -266,  -266,  -266,  -266,  -266,  -266,  -266,
    -266,  -266,  -266,  -213,  -174,  -266,  -266,  -266,   212,   255,
     156,  -266,  -266,  -266,  -266,   201,   243,  -236,  -135,  -152,
    -266,  -266,   229,   272,   -35,  -266,  -134,  -266,   103,   112,
     121,   116,   117,   129,   138,  -266,    93,  -265,   281,  -266,
     317,   -43,   176,  -151,  -217,  -184,  -147,  -266
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   246,   216,    29,    30,    31,   170,   131,
     214,   243,   176,   132,    32,   183,   137,   221,    71,   181,
      33,    34,   156,   114,   150,    35,    36,    37,   279,   310,
     298,   308,   265,   296,   288,   304,   312,    73,    74,    75,
     101,    94,   208,   112,   192,   151,   152,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,   180,   195,   189,   184,   198,   227,   228,   305,   116,
     254,   255,   270,    91,    97,    98,    99,    99,    92,   180,
      96,    92,    89,    90,    97,    98,    99,    95,    97,    98,
      99,   332,   306,   305,   269,   125,   117,   211,   315,   118,
      45,    46,   206,   247,    39,    44,    40,    41,   333,   292,
      93,   179,   212,    93,   281,   326,   307,   239,    59,   229,
     230,   120,   121,   122,   123,   124,     5,   213,   248,   100,
     100,   267,   207,    57,   158,   159,   300,   251,   212,   100,
      58,   307,   161,   100,    59,   180,   168,    59,   126,    47,
     252,   253,   127,   213,   327,   128,    48,   328,    65,    66,
      67,    49,   293,    89,    69,   163,   164,    42,    51,    43,
      60,    61,    62,    63,    64,   342,   166,   167,   341,   200,
     201,    52,   165,   204,    65,    66,    67,    65,    66,    67,
      69,    68,   343,    69,    70,   190,   191,   284,   285,   186,
     336,   194,   187,   337,    50,   335,   218,   219,   179,    53,
      54,   314,    55,    76,   226,    59,    56,    77,   188,    78,
      79,   319,   171,   172,   173,   174,   175,   320,   180,    60,
      61,    62,    63,    64,    80,    81,    82,    83,    60,    61,
      62,    63,    64,    84,    85,   338,   345,   340,   347,    86,
      89,   259,   260,   261,   262,    65,    66,    67,   352,   350,
     138,    69,    87,   180,    88,   180,   102,    58,   103,   104,
     105,   107,   106,   108,    59,   180,   272,   109,   110,   111,
     276,   115,   134,   113,   136,   135,   153,   154,   139,   140,
     141,   142,   119,   129,   130,   155,    89,    60,    61,    62,
      63,    64,   133,   162,    97,    98,    99,   143,   144,   145,
     146,   147,   148,   149,    65,    66,    67,    57,    68,   177,
      69,    70,   157,   169,    58,   225,   139,   140,   141,   142,
     178,    59,    58,   182,   185,   193,   199,   202,   203,    59,
     205,   210,   217,   220,   215,   143,   144,   145,   146,   147,
     148,   149,   223,   271,    60,    61,    62,    63,    64,   100,
      58,   224,    60,    61,    62,    63,    64,    59,     5,   179,
     232,    65,    66,    67,   233,    68,    59,    69,    70,    65,
      66,    67,   234,    68,   235,    69,    70,   236,   237,   238,
      60,    61,    62,    63,    64,   241,   244,   242,   245,    60,
      61,    62,    63,    64,   249,   256,   257,    65,    66,    67,
     258,    68,   263,    69,    70,     2,    65,    66,    67,     3,
       4,   264,    69,   266,   268,     5,     6,     7,     8,     9,
      10,    11,   273,   206,   274,    12,    13,    14,   139,   140,
     141,   142,   277,   278,   282,   283,   286,   287,    15,    16,
     290,   289,   291,   294,   295,   299,   297,   143,   144,   145,
     146,   147,   148,   149,   303,   301,    17,   309,   311,   316,
     318,   321,   324,   329,   331,   339,   334,   344,   346,   349,
     351,   240,   280,   250,   209,   222,   231,   197,   330,   323,
     317,   313,   322,   302,   348,   196,   325,   160,   275
};

static const yytype_int16 yycheck[] =
{
      35,   136,   154,   150,   138,   156,   190,   191,    11,    18,
     227,   228,   248,    35,    23,    24,    25,    25,    43,   154,
      19,    43,    57,    58,    23,    24,    25,    70,    23,    24,
      25,    18,    35,    11,   247,    18,    75,    17,   303,    78,
       7,     8,    19,   217,     6,    75,     8,     9,    35,   285,
      75,    24,    32,    75,   267,   320,    59,   208,    31,   193,
     194,    96,    97,    98,    99,   100,    10,    47,   220,    78,
      78,   245,    49,    17,   117,   118,   293,   224,    32,    78,
      24,    59,   125,    78,    31,   220,   129,    31,    71,     3,
     225,   225,    75,    47,    75,    78,    36,    78,    71,    72,
      73,    38,   286,   138,    77,    18,    19,     6,     3,     8,
      54,    55,    56,    57,    58,    18,    18,    19,   335,   162,
     163,     3,    35,   166,    71,    72,    73,    71,    72,    73,
      77,    75,    35,    77,    78,    40,    41,   271,   273,    45,
      75,    17,    48,    78,    75,   329,    71,    72,    24,     3,
       3,   303,     3,     3,   189,    31,    52,    75,    64,    75,
       8,   312,    26,    27,    28,    29,    30,   314,   303,    54,
      55,    56,    57,    58,    75,    75,     3,     3,    54,    55,
      56,    57,    58,    38,    75,   332,   338,   334,   340,    75,
     225,   234,   235,   236,   237,    71,    72,    73,   350,   346,
      17,    77,    42,   338,    53,   340,    17,    24,    38,    17,
      44,     3,    75,     3,    31,   350,   251,    75,    37,    39,
     263,    77,    44,    75,    17,     3,     3,    65,    45,    46,
      47,    48,    75,    75,    75,    19,   271,    54,    55,    56,
      57,    58,    75,    18,    23,    24,    25,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    17,    75,    17,
      77,    78,    36,    19,    24,    17,    45,    46,    47,    48,
      75,    31,    24,    19,    47,    17,     6,    75,    75,    31,
      75,    18,    17,    19,    75,    64,    65,    66,    67,    68,
      69,    70,     3,    17,    54,    55,    56,    57,    58,    78,
      24,    18,    54,    55,    56,    57,    58,    31,    10,    24,
       3,    71,    72,    73,    75,    75,    31,    77,    78,    71,
      72,    73,    18,    75,    18,    77,    78,    18,    75,    50,
      54,    55,    56,    57,    58,     3,    31,    71,    19,    54,
      55,    56,    57,    58,    18,    18,    18,    71,    72,    73,
       3,    75,    75,    77,    78,     0,    71,    72,    73,     4,
       5,    61,    77,    18,    18,    10,    11,    12,    13,    14,
      15,    16,    19,    19,    18,    20,    21,    22,    45,    46,
      47,    48,    62,    60,     3,    18,    44,    75,    33,    34,
       3,    62,    18,    35,    19,    18,    75,    64,    65,    66,
      67,    68,    69,    70,    63,    75,    51,    19,    49,    75,
      50,    17,    75,    44,    17,    75,    18,    18,    18,    75,
      18,   209,   266,   222,   169,   182,   197,   155,   325,   317,
     309,   302,   316,   295,   341,   154,   319,   120,   262
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    81,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    33,    34,    51,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    95,
      96,    97,   104,   110,   111,   115,   116,   117,   137,     6,
       8,     9,     6,     8,    75,     7,     8,     3,    36,    38,
      75,     3,     3,     3,     3,     3,    52,    17,    24,    31,
      54,    55,    56,    57,    58,    71,    72,    73,    75,    77,
      78,   108,   114,   127,   128,   129,     3,    75,    75,     8,
      75,    75,     3,     3,    38,    75,    75,    42,    53,   114,
     114,    35,    43,    75,   131,   131,    19,    23,    24,    25,
      78,   130,    17,    38,    17,    44,    75,     3,     3,    75,
      37,    39,   133,    75,   113,    77,    18,    75,    78,    75,
     114,   114,   114,   114,   114,    18,    71,    75,    78,    75,
      75,    99,   103,    75,    44,     3,    17,   106,    17,    45,
      46,    47,    48,    64,    65,    66,    67,    68,    69,    70,
     114,   135,   136,     3,    65,    19,   112,    36,   131,   131,
     130,   131,    18,    18,    19,    35,    18,    19,   131,    19,
      98,    26,    27,    28,    29,    30,   102,    17,    75,    24,
     108,   109,    19,   105,   116,    47,    45,    48,    64,   136,
      40,    41,   134,    17,    17,   109,   128,   113,   133,     6,
     131,   131,    75,    75,   131,    75,    19,    49,   132,    99,
      18,    17,    32,    47,   100,    75,    94,    17,    71,    72,
      19,   107,   106,     3,    18,    17,   114,   135,   135,   116,
     116,   112,     3,    75,    18,    18,    18,    75,    50,   133,
      98,     3,    71,   101,    31,    19,    93,    94,   109,    18,
     105,   136,   108,   116,   134,   134,    18,    18,     3,   131,
     131,   131,   131,    75,    61,   122,    18,    94,    18,    93,
     107,    17,   114,    19,    18,   132,   131,    62,    60,   118,
     100,    93,     3,    18,   116,   108,    44,    75,   124,    62,
       3,    18,   107,   135,    35,    19,   123,    75,   120,    18,
     134,    75,   124,    63,   125,    11,    35,    59,   121,    19,
     119,    49,   126,   123,   109,   127,    75,   120,    50,   133,
     136,    17,   121,   119,    75,   122,   127,    75,    78,    44,
     118,    17,    18,    35,    18,   135,    75,    78,   136,    75,
     136,   134,    18,    35,    18,   109,    18,   109,   126,    75,
     136,    18,   109
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    81,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    92,    93,    93,    94,    95,    96,    97,    98,
      98,    99,    99,   100,   100,   100,   101,   102,   102,   102,
     102,   102,   103,   104,   105,   105,   106,   107,   107,   108,
     108,   108,   108,   108,   109,   109,   109,   110,   111,   112,
     112,   113,   113,   113,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   115,   116,   116,   117,
     118,   118,   119,   119,   120,   120,   121,   121,   121,   122,
     122,   123,   123,   124,   124,   125,   125,   125,   125,   125,
     125,   125,   126,   126,   127,   127,   127,   127,   127,   128,
     128,   128,   128,   128,   128,   128,   129,   130,   130,   131,
     131,   131,   132,   132,   133,   133,   134,   134,   134,   135,
     135,   135,   135,   135,   135,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   137
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
       1,     2,     4,     2,     4,     1,     1,     9,    16,     2,
       0,     4,     0,     3,     2,     4,     0,     1,     1,     0,
       5,     0,     3,     1,     3,     0,     7,     7,     9,     7,
       7,     9,     0,     7,     1,     1,     1,     1,     1,     5,
       5,     7,     5,     7,     7,     4,     2,     0,     3,     0,
       1,     2,     0,     4,     0,     3,     0,     3,     3,     3,
       8,     5,     5,     4,     7,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     2,     1,     2,     8
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
#line 235 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1554 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 240 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1562 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 245 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1570 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 251 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1578 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 257 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1586 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 263 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1594 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 269 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1603 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 275 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1611 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 281 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1620 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON  */
#line 289 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			
		}
#line 1630 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON  */
#line 295 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $8);
		}
#line 1640 "yacc_sql.tab.c"
    break;

  case 34: /* attr_name_list: COMMA attr_name attr_name_list  */
#line 304 "yacc_sql.y"
                                         {

	}
#line 1648 "yacc_sql.tab.c"
    break;

  case 35: /* attr_name: ID  */
#line 309 "yacc_sql.y"
              {
	create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $2);
}
#line 1657 "yacc_sql.tab.c"
    break;

  case 36: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 315 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1666 "yacc_sql.tab.c"
    break;

  case 37: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 322 "yacc_sql.y"
                                    {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1675 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 330 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1687 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 340 "yacc_sql.y"
                                   {    }
#line 1693 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE nullable  */
#line 345 "yacc_sql.y"
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
#line 1708 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type nullable  */
#line 356 "yacc_sql.y"
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
#line 1723 "yacc_sql.tab.c"
    break;

  case 43: /* nullable: %empty  */
#line 369 "yacc_sql.y"
        { (yyval.number)=0; }
#line 1729 "yacc_sql.tab.c"
    break;

  case 44: /* nullable: NULLABLE  */
#line 370 "yacc_sql.y"
                   { (yyval.number)=1; }
#line 1735 "yacc_sql.tab.c"
    break;

  case 45: /* nullable: NOT NULL_T  */
#line 371 "yacc_sql.y"
                     { (yyval.number)=2; }
#line 1741 "yacc_sql.tab.c"
    break;

  case 46: /* number: NUMBER  */
#line 375 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1747 "yacc_sql.tab.c"
    break;

  case 47: /* type: INT_T  */
#line 378 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1753 "yacc_sql.tab.c"
    break;

  case 48: /* type: STRING_T  */
#line 379 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1759 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 380 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1765 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 381 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1771 "yacc_sql.tab.c"
    break;

  case 51: /* type: TEXT_T  */
#line 382 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1777 "yacc_sql.tab.c"
    break;

  case 52: /* ID_get: ID  */
#line 386 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1786 "yacc_sql.tab.c"
    break;

  case 53: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 395 "yacc_sql.y"
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
#line 1806 "yacc_sql.tab.c"
    break;

  case 55: /* tuple_list: COMMA tuple tuple_list  */
#line 413 "yacc_sql.y"
                                 {
	}
#line 1813 "yacc_sql.tab.c"
    break;

  case 56: /* tuple: LBRACE value_with_neg value_list RBRACE  */
#line 419 "yacc_sql.y"
                                                {
		insert_init(&CONTEXT->insert_list[CONTEXT->insert_num++], CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1822 "yacc_sql.tab.c"
    break;

  case 58: /* value_list: COMMA value_with_neg value_list  */
#line 427 "yacc_sql.y"
                                       { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1830 "yacc_sql.tab.c"
    break;

  case 59: /* value: NUMBER  */
#line 432 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1838 "yacc_sql.tab.c"
    break;

  case 60: /* value: FLOAT  */
#line 435 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1846 "yacc_sql.tab.c"
    break;

  case 61: /* value: DATE  */
#line 438 "yacc_sql.y"
             {
		(yyvsp[0].string) = substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);
		int res = value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		if (res != 0) {
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			yyresult = 2;
			goto yyreturnlab;
		}
	}
#line 1860 "yacc_sql.tab.c"
    break;

  case 62: /* value: SSS  */
#line 447 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1869 "yacc_sql.tab.c"
    break;

  case 63: /* value: NULL_T  */
#line 451 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1877 "yacc_sql.tab.c"
    break;

  case 64: /* value_with_neg: value  */
#line 457 "yacc_sql.y"
              {
	}
#line 1884 "yacc_sql.tab.c"
    break;

  case 65: /* value_with_neg: SUB_T NUMBER  */
#line 459 "yacc_sql.y"
                       {
		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number) * -1);
	}
#line 1892 "yacc_sql.tab.c"
    break;

  case 66: /* value_with_neg: SUB_T FLOAT  */
#line 462 "yacc_sql.y"
                      {
		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats) * -1.0);
	}
#line 1900 "yacc_sql.tab.c"
    break;

  case 67: /* delete: DELETE FROM ID where SEMICOLON  */
#line 468 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1912 "yacc_sql.tab.c"
    break;

  case 68: /* updates: UPDATE ID SET modify_expr modify_list where SEMICOLON  */
#line 488 "yacc_sql.y"
                                                              {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		updates_select_init(&CONTEXT->ssql->sstr.updates, (yyvsp[-5].string), CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
		CONTEXT->select_num = 0;
		CONTEXT->attr_num = 0;
		CONTEXT->expression_attr_num = 0;
	}
#line 1925 "yacc_sql.tab.c"
    break;

  case 70: /* modify_list: COMMA modify_expr modify_list  */
#line 499 "yacc_sql.y"
                                        {

	}
#line 1933 "yacc_sql.tab.c"
    break;

  case 71: /* modify_expr: ID EQ value_with_neg  */
#line 505 "yacc_sql.y"
                             {
		updates_append_value(&CONTEXT->ssql->sstr.updates, &CONTEXT->values[CONTEXT->value_length - 1], (yyvsp[-2].string));
	}
#line 1941 "yacc_sql.tab.c"
    break;

  case 72: /* modify_expr: ID EQ LBRACE select_clause RBRACE  */
#line 508 "yacc_sql.y"
                                           {
		Value value;
		value_init_select(&value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, (yyvsp[-4].string));
	}
#line 1951 "yacc_sql.tab.c"
    break;

  case 73: /* modify_expr: ID EQ agg  */
#line 513 "yacc_sql.y"
                    {
		Value value;
		// value_init_agg(&value, &CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]-1]);
		// CONTEXT->select_attr_num[CONTEXT->select_num]--;
		value_init_agg(&value, &CONTEXT->attrs[--CONTEXT->expression_attr_num]);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, (yyvsp[-2].string));
	}
#line 1963 "yacc_sql.tab.c"
    break;

  case 74: /* exp: exp ADD_T exp  */
#line 524 "yacc_sql.y"
                      { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, ADD); }
#line 1969 "yacc_sql.tab.c"
    break;

  case 75: /* exp: exp SUB_T exp  */
#line 525 "yacc_sql.y"
                        { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, SUB); }
#line 1975 "yacc_sql.tab.c"
    break;

  case 76: /* exp: SUB_T exp  */
#line 526 "yacc_sql.y"
                    {
		// Value left_value;
		// value_init_integer(&left_value, 0);
		// Exp *left_exp = create_expression(NULL, NULL, &left_value, NULL, VAL);
		(yyval.exp1) = create_expression(NULL, (yyvsp[0].exp1), NULL, NULL, SUB);
	}
#line 1986 "yacc_sql.tab.c"
    break;

  case 77: /* exp: exp STAR exp  */
#line 532 "yacc_sql.y"
                       { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, MUL); }
#line 1992 "yacc_sql.tab.c"
    break;

  case 78: /* exp: exp DIV_T exp  */
#line 533 "yacc_sql.y"
                        { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, DIV); }
#line 1998 "yacc_sql.tab.c"
    break;

  case 79: /* exp: LBRACE exp RBRACE  */
#line 534 "yacc_sql.y"
                            { 
		Exp *exp = (yyvsp[-1].exp1);
		++exp->lbrace;
		++exp->rbrace;
		(yyval.exp1) = exp; 
	}
#line 2009 "yacc_sql.tab.c"
    break;

  case 80: /* exp: value  */
#line 540 "yacc_sql.y"
                { 
		(yyval.exp1) = create_expression(NULL, NULL, &CONTEXT->values[CONTEXT->value_length - 1], NULL, VAL); 
	}
#line 2017 "yacc_sql.tab.c"
    break;

  case 81: /* exp: ID alias_ID  */
#line 543 "yacc_sql.y"
                      { 
		RelAttr attr;
		relation_attr_init_with_alias(&attr, NULL, (yyvsp[-1].string), (yyvsp[0].string));
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
#line 2028 "yacc_sql.tab.c"
    break;

  case 82: /* exp: ID DOT ID alias_ID  */
#line 549 "yacc_sql.y"
                             {
		RelAttr attr;
		
		relation_attr_init_with_alias(&attr, (yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[0].string));
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
#line 2040 "yacc_sql.tab.c"
    break;

  case 83: /* exp: STAR alias_ID  */
#line 556 "yacc_sql.y"
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
#line 2057 "yacc_sql.tab.c"
    break;

  case 84: /* exp: ID DOT STAR alias_ID  */
#line 568 "yacc_sql.y"
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
#line 2074 "yacc_sql.tab.c"
    break;

  case 85: /* exp: agg  */
#line 580 "yacc_sql.y"
              {
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &CONTEXT->attrs[CONTEXT->expression_attr_num - 1], ATTR);
	}
#line 2082 "yacc_sql.tab.c"
    break;

  case 86: /* select_begin: SELECT  */
#line 587 "yacc_sql.y"
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
#line 2098 "yacc_sql.tab.c"
    break;

  case 87: /* select_clause: select_begin select_attr FROM ID alias_ID rel_list where group_by order_by  */
#line 600 "yacc_sql.y"
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
#line 2136 "yacc_sql.tab.c"
    break;

  case 88: /* select_clause: select_begin select_attr FROM ID alias_ID INNER JOIN ID alias_ID ON condition condition_list join_list where group_by order_by  */
#line 633 "yacc_sql.y"
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
#line 2175 "yacc_sql.tab.c"
    break;

  case 89: /* select: select_clause SEMICOLON  */
#line 670 "yacc_sql.y"
                            {
		// 这里说明select是主语句
		CONTEXT->ssql->flag=SCF_SELECT;//"select";
		CONTEXT->ssql->sstr.selection = CONTEXT->selections[CONTEXT->select_num-1];
	}
#line 2185 "yacc_sql.tab.c"
    break;

  case 91: /* order_by: ORDER BY order_item order_item_list  */
#line 680 "yacc_sql.y"
                                              {
		
	}
#line 2193 "yacc_sql.tab.c"
    break;

  case 93: /* order_item_list: COMMA order_item order_item_list  */
#line 687 "yacc_sql.y"
                                           {}
#line 2199 "yacc_sql.tab.c"
    break;

  case 94: /* order_item: ID order  */
#line 691 "yacc_sql.y"
                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		OrderBy order_by; 
		order_by_init(&order_by, &attr, (yyvsp[0].number));
		selects_append_order_by(&CONTEXT->selections[CONTEXT->select_num], &order_by);
	}
#line 2211 "yacc_sql.tab.c"
    break;

  case 95: /* order_item: ID DOT ID order  */
#line 698 "yacc_sql.y"
                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		OrderBy order_by;
		order_by_init(&order_by, &attr, (yyvsp[0].number));
		selects_append_order_by(&CONTEXT->selections[CONTEXT->select_num], &order_by);
	}
#line 2223 "yacc_sql.tab.c"
    break;

  case 96: /* order: %empty  */
#line 707 "yacc_sql.y"
        { (yyval.number) = 0; }
#line 2229 "yacc_sql.tab.c"
    break;

  case 97: /* order: ASC  */
#line 708 "yacc_sql.y"
              { (yyval.number) = 0; }
#line 2235 "yacc_sql.tab.c"
    break;

  case 98: /* order: DESC  */
#line 709 "yacc_sql.y"
               { (yyval.number) = 1; }
#line 2241 "yacc_sql.tab.c"
    break;

  case 100: /* group_by: GROUP BY group_item group_item_list having  */
#line 713 "yacc_sql.y"
                                                     {
	}
#line 2248 "yacc_sql.tab.c"
    break;

  case 102: /* group_item_list: COMMA group_item group_item_list  */
#line 719 "yacc_sql.y"
                                           {}
#line 2254 "yacc_sql.tab.c"
    break;

  case 103: /* group_item: ID  */
#line 723 "yacc_sql.y"
           {
		RelAttr attr;	
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		selects_append_group_by(&CONTEXT->selections[CONTEXT->select_num], &attr);
	}
#line 2264 "yacc_sql.tab.c"
    break;

  case 104: /* group_item: ID DOT ID  */
#line 728 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		selects_append_group_by(&CONTEXT->selections[CONTEXT->select_num], &attr);
	}
#line 2274 "yacc_sql.tab.c"
    break;

  case 106: /* having: HAVING agg_func LBRACE STAR RBRACE comOp value_with_neg  */
#line 735 "yacc_sql.y"
                                                                  {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, "*", (yyvsp[-5].number), NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], (yyvsp[-1].number), 0);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
#line 2286 "yacc_sql.tab.c"
    break;

  case 107: /* having: HAVING agg_func LBRACE ID RBRACE comOp value_with_neg  */
#line 742 "yacc_sql.y"
                                                                {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, (yyvsp[-3].string), (yyvsp[-5].number), NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], (yyvsp[-1].number), 0);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
#line 2298 "yacc_sql.tab.c"
    break;

  case 108: /* having: HAVING agg_func LBRACE ID DOT ID RBRACE comOp value_with_neg  */
#line 749 "yacc_sql.y"
                                                                       {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, (yyvsp[-5].string), (yyvsp[-3].string), (yyvsp[-7].number), NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], (yyvsp[-1].number), 0);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
#line 2310 "yacc_sql.tab.c"
    break;

  case 109: /* having: HAVING value_with_neg comOp agg_func LBRACE STAR RBRACE  */
#line 756 "yacc_sql.y"
                                                                   {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, "*", (yyvsp[-3].number), NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], (yyvsp[-4].number), 1);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
#line 2322 "yacc_sql.tab.c"
    break;

  case 110: /* having: HAVING value_with_neg comOp agg_func LBRACE ID RBRACE  */
#line 763 "yacc_sql.y"
                                                                {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, (yyvsp[-1].string), (yyvsp[-3].number), NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], (yyvsp[-4].number), 1);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
#line 2334 "yacc_sql.tab.c"
    break;

  case 111: /* having: HAVING value_with_neg comOp agg_func LBRACE ID DOT ID RBRACE  */
#line 770 "yacc_sql.y"
                                                                       {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, (yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[-5].number), NULL);
		Having having;
		having_init(&having, &attr, &CONTEXT->values[CONTEXT->value_length-1], (yyvsp[-6].number), 1);
		selects_append_having(&CONTEXT->selections[CONTEXT->select_num], &having);
	}
#line 2346 "yacc_sql.tab.c"
    break;

  case 113: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 780 "yacc_sql.y"
        {
		selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-4].string));
	}
#line 2354 "yacc_sql.tab.c"
    break;

  case 114: /* agg_func: MAX_T  */
#line 786 "yacc_sql.y"
              { (yyval.number)=MAX; }
#line 2360 "yacc_sql.tab.c"
    break;

  case 115: /* agg_func: MIN_T  */
#line 787 "yacc_sql.y"
                { (yyval.number)=MIN; }
#line 2366 "yacc_sql.tab.c"
    break;

  case 116: /* agg_func: COUNT_T  */
#line 788 "yacc_sql.y"
                  { (yyval.number)=COUNT; }
#line 2372 "yacc_sql.tab.c"
    break;

  case 117: /* agg_func: AVG_T  */
#line 789 "yacc_sql.y"
                { (yyval.number)=AVG; }
#line 2378 "yacc_sql.tab.c"
    break;

  case 118: /* agg_func: SUM_T  */
#line 790 "yacc_sql.y"
                { (yyval.number)=SUM; }
#line 2384 "yacc_sql.tab.c"
    break;

  case 119: /* agg: agg_func LBRACE STAR RBRACE alias_ID  */
#line 795 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, "*", (yyvsp[-4].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2395 "yacc_sql.tab.c"
    break;

  case 120: /* agg: agg_func LBRACE ID RBRACE alias_ID  */
#line 801 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2406 "yacc_sql.tab.c"
    break;

  case 121: /* agg: agg_func LBRACE ID DOT ID RBRACE alias_ID  */
#line 807 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-6].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2417 "yacc_sql.tab.c"
    break;

  case 122: /* agg: agg_func LBRACE NUMBER RBRACE alias_ID  */
#line 813 "yacc_sql.y"
                                                 {
		RelAttr attr;
		relation_attr_init_with_agg_num(&attr, (yyvsp[-4].number), (yyvsp[-2].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2428 "yacc_sql.tab.c"
    break;

  case 123: /* agg: agg_func LBRACE STAR COMMA ID RBRACE alias_ID  */
#line 819 "yacc_sql.y"
                                                        {
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2438 "yacc_sql.tab.c"
    break;

  case 124: /* agg: agg_func LBRACE ID COMMA ID RBRACE alias_ID  */
#line 824 "yacc_sql.y"
                                                      {
		// 错误类型
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2449 "yacc_sql.tab.c"
    break;

  case 125: /* agg: agg_func LBRACE RBRACE alias_ID  */
#line 830 "yacc_sql.y"
                                          {
		// 错误类型
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2460 "yacc_sql.tab.c"
    break;

  case 126: /* select_attr: exp attr_list  */
#line 842 "yacc_sql.y"
                      {
		CONTEXT->expressions[CONTEXT->expr_num++] = (yyvsp[-1].exp1);
		CONTEXT->attr_num = CONTEXT->expression_attr_num;
	}
#line 2469 "yacc_sql.tab.c"
    break;

  case 128: /* attr_list: COMMA exp attr_list  */
#line 850 "yacc_sql.y"
                              {
		CONTEXT->expressions[CONTEXT->expr_num++] = (yyvsp[-1].exp1);
		// 因为现在条件语句中的RelAttr也会占用全局的attrs
		// 需要进行一下区别，attr_num只记录
		CONTEXT->attr_num = CONTEXT->expression_attr_num;
	}
#line 2480 "yacc_sql.tab.c"
    break;

  case 129: /* alias_ID: %empty  */
#line 860 "yacc_sql.y"
        { (yyval.string) = NULL; }
#line 2486 "yacc_sql.tab.c"
    break;

  case 130: /* alias_ID: ID  */
#line 861 "yacc_sql.y"
             { (yyval.string) = (yyvsp[0].string); }
#line 2492 "yacc_sql.tab.c"
    break;

  case 131: /* alias_ID: AS ID  */
#line 862 "yacc_sql.y"
                { (yyval.string) = (yyvsp[0].string); }
#line 2498 "yacc_sql.tab.c"
    break;

  case 133: /* rel_list: COMMA ID alias_ID rel_list  */
#line 867 "yacc_sql.y"
                                 {	
		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-2].string), (yyvsp[-1].string));
	}
#line 2506 "yacc_sql.tab.c"
    break;

  case 135: /* where: WHERE condition condition_list  */
#line 873 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
	}
#line 2514 "yacc_sql.tab.c"
    break;

  case 137: /* condition_list: AND condition condition_list  */
#line 881 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		CONTEXT->selections[CONTEXT->select_num].is_and = 1; 
	}
#line 2523 "yacc_sql.tab.c"
    break;

  case 138: /* condition_list: OR condition condition_list  */
#line 885 "yacc_sql.y"
                                      {
		CONTEXT->selections[CONTEXT->select_num].is_and = 0;
	}
#line 2531 "yacc_sql.tab.c"
    break;

  case 139: /* condition: exp comOp exp  */
#line 892 "yacc_sql.y"
                      {
		Exp *left_exp = (yyvsp[-2].exp1);
		Exp *right_exp = (yyvsp[0].exp1);
		Condition condition;
		condition_init_with_exp(&condition, (yyvsp[-1].number), left_exp, right_exp);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
#line 2544 "yacc_sql.tab.c"
    break;

  case 140: /* condition: exp comOp LBRACE value COMMA value value_list RBRACE  */
#line 900 "yacc_sql.y"
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
#line 2567 "yacc_sql.tab.c"
    break;

  case 141: /* condition: LBRACE select_clause RBRACE comOp exp  */
#line 918 "yacc_sql.y"
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
#line 2583 "yacc_sql.tab.c"
    break;

  case 142: /* condition: exp comOp LBRACE select_clause RBRACE  */
#line 929 "yacc_sql.y"
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
#line 2599 "yacc_sql.tab.c"
    break;

  case 143: /* condition: comOp LBRACE select_clause RBRACE  */
#line 940 "yacc_sql.y"
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
#line 2617 "yacc_sql.tab.c"
    break;

  case 144: /* condition: LBRACE select_clause RBRACE comOp LBRACE select_clause RBRACE  */
#line 953 "yacc_sql.y"
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
#line 2633 "yacc_sql.tab.c"
    break;

  case 145: /* comOp: EQ  */
#line 967 "yacc_sql.y"
             { (yyval.number) = EQUAL_TO; }
#line 2639 "yacc_sql.tab.c"
    break;

  case 146: /* comOp: LT  */
#line 968 "yacc_sql.y"
         { (yyval.number) = LESS_THAN; }
#line 2645 "yacc_sql.tab.c"
    break;

  case 147: /* comOp: GT  */
#line 969 "yacc_sql.y"
         { (yyval.number) = GREAT_THAN; }
#line 2651 "yacc_sql.tab.c"
    break;

  case 148: /* comOp: LE  */
#line 970 "yacc_sql.y"
         { (yyval.number) = LESS_EQUAL; }
#line 2657 "yacc_sql.tab.c"
    break;

  case 149: /* comOp: GE  */
#line 971 "yacc_sql.y"
         { (yyval.number) = GREAT_EQUAL; }
#line 2663 "yacc_sql.tab.c"
    break;

  case 150: /* comOp: NE  */
#line 972 "yacc_sql.y"
         { (yyval.number) = NOT_EQUAL; }
#line 2669 "yacc_sql.tab.c"
    break;

  case 151: /* comOp: LIKE  */
#line 973 "yacc_sql.y"
               { (yyval.number) = LIKE_MATCH; }
#line 2675 "yacc_sql.tab.c"
    break;

  case 152: /* comOp: NOT LIKE  */
#line 974 "yacc_sql.y"
                   { (yyval.number) = NOT_LIKE; }
#line 2681 "yacc_sql.tab.c"
    break;

  case 153: /* comOp: IN  */
#line 975 "yacc_sql.y"
             { (yyval.number) = IN_OP; }
#line 2687 "yacc_sql.tab.c"
    break;

  case 154: /* comOp: NOT IN  */
#line 976 "yacc_sql.y"
                 { (yyval.number) = NOT_IN_OP; }
#line 2693 "yacc_sql.tab.c"
    break;

  case 155: /* comOp: EXIST  */
#line 977 "yacc_sql.y"
                { (yyval.number) =EXISTS_OP; }
#line 2699 "yacc_sql.tab.c"
    break;

  case 156: /* comOp: NOT EXIST  */
#line 978 "yacc_sql.y"
                    { (yyval.number) = NOT_EXISTS_OP; }
#line 2705 "yacc_sql.tab.c"
    break;

  case 157: /* comOp: IS  */
#line 979 "yacc_sql.y"
             { (yyval.number) = IS_OP; }
#line 2711 "yacc_sql.tab.c"
    break;

  case 158: /* comOp: IS NOT  */
#line 980 "yacc_sql.y"
                 { (yyval.number) = IS_NOT_OP; }
#line 2717 "yacc_sql.tab.c"
    break;

  case 159: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 985 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2726 "yacc_sql.tab.c"
    break;


#line 2730 "yacc_sql.tab.c"

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

#line 990 "yacc_sql.y"

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
