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


#line 152 "yacc_sql.tab.c"

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
  YYSYMBOL_LIKE = 59,                      /* LIKE  */
  YYSYMBOL_EQ = 60,                        /* EQ  */
  YYSYMBOL_LT = 61,                        /* LT  */
  YYSYMBOL_GT = 62,                        /* GT  */
  YYSYMBOL_LE = 63,                        /* LE  */
  YYSYMBOL_GE = 64,                        /* GE  */
  YYSYMBOL_NE = 65,                        /* NE  */
  YYSYMBOL_NUMBER = 66,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 67,                     /* FLOAT  */
  YYSYMBOL_DATE = 68,                      /* DATE  */
  YYSYMBOL_TEXT = 69,                      /* TEXT  */
  YYSYMBOL_ID = 70,                        /* ID  */
  YYSYMBOL_PATH = 71,                      /* PATH  */
  YYSYMBOL_SSS = 72,                       /* SSS  */
  YYSYMBOL_STAR = 73,                      /* STAR  */
  YYSYMBOL_STRING_V = 74,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 75,                  /* $accept  */
  YYSYMBOL_commands = 76,                  /* commands  */
  YYSYMBOL_command = 77,                   /* command  */
  YYSYMBOL_exit = 78,                      /* exit  */
  YYSYMBOL_help = 79,                      /* help  */
  YYSYMBOL_sync = 80,                      /* sync  */
  YYSYMBOL_begin = 81,                     /* begin  */
  YYSYMBOL_commit = 82,                    /* commit  */
  YYSYMBOL_rollback = 83,                  /* rollback  */
  YYSYMBOL_drop_table = 84,                /* drop_table  */
  YYSYMBOL_show_tables = 85,               /* show_tables  */
  YYSYMBOL_desc_table = 86,                /* desc_table  */
  YYSYMBOL_create_index = 87,              /* create_index  */
  YYSYMBOL_attr_name_list = 88,            /* attr_name_list  */
  YYSYMBOL_attr_name = 89,                 /* attr_name  */
  YYSYMBOL_drop_index = 90,                /* drop_index  */
  YYSYMBOL_show_index = 91,                /* show_index  */
  YYSYMBOL_create_table = 92,              /* create_table  */
  YYSYMBOL_attr_def_list = 93,             /* attr_def_list  */
  YYSYMBOL_attr_def = 94,                  /* attr_def  */
  YYSYMBOL_nullable = 95,                  /* nullable  */
  YYSYMBOL_number = 96,                    /* number  */
  YYSYMBOL_type = 97,                      /* type  */
  YYSYMBOL_ID_get = 98,                    /* ID_get  */
  YYSYMBOL_insert = 99,                    /* insert  */
  YYSYMBOL_tuple_list = 100,               /* tuple_list  */
  YYSYMBOL_tuple = 101,                    /* tuple  */
  YYSYMBOL_value_list = 102,               /* value_list  */
  YYSYMBOL_value = 103,                    /* value  */
  YYSYMBOL_value_with_neg = 104,           /* value_with_neg  */
  YYSYMBOL_delete = 105,                   /* delete  */
  YYSYMBOL_updates = 106,                  /* updates  */
  YYSYMBOL_modify_list = 107,              /* modify_list  */
  YYSYMBOL_modify_expr = 108,              /* modify_expr  */
  YYSYMBOL_exp = 109,                      /* exp  */
  YYSYMBOL_select_begin = 110,             /* select_begin  */
  YYSYMBOL_select_clause = 111,            /* select_clause  */
  YYSYMBOL_select = 112,                   /* select  */
  YYSYMBOL_join_list = 113,                /* join_list  */
  YYSYMBOL_agg_func = 114,                 /* agg_func  */
  YYSYMBOL_agg = 115,                      /* agg  */
  YYSYMBOL_select_attr = 116,              /* select_attr  */
  YYSYMBOL_attr_list = 117,                /* attr_list  */
  YYSYMBOL_alias_ID = 118,                 /* alias_ID  */
  YYSYMBOL_rel_list = 119,                 /* rel_list  */
  YYSYMBOL_where = 120,                    /* where  */
  YYSYMBOL_condition_list = 121,           /* condition_list  */
  YYSYMBOL_condition = 122,                /* condition  */
  YYSYMBOL_comOp = 123,                    /* comOp  */
  YYSYMBOL_load_data = 124                 /* load_data  */
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
#define YYLAST   386

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  137
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  297

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   329


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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   192,   192,   194,   198,   199,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   220,   225,   230,   236,   242,   248,   254,   260,
     266,   273,   279,   288,   289,   294,   299,   307,   314,   323,
     325,   329,   340,   354,   355,   356,   360,   363,   364,   365,
     366,   367,   370,   379,   397,   398,   404,   410,   412,   417,
     420,   423,   432,   436,   442,   444,   447,   452,   473,   483,
     484,   490,   493,   498,   509,   510,   511,   517,   518,   519,
     525,   528,   534,   541,   553,   565,   572,   585,   618,   655,
     662,   663,   670,   671,   672,   673,   674,   679,   685,   691,
     697,   703,   708,   714,   726,   732,   734,   744,   745,   746,
     749,   751,   755,   757,   763,   765,   769,   776,   784,   802,
     813,   824,   837,   851,   852,   853,   854,   855,   856,   857,
     858,   859,   860,   861,   862,   863,   864,   868
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
  "DATA", "INFILE", "MAX_T", "MIN_T", "COUNT_T", "AVG_T", "SUM_T", "LIKE",
  "EQ", "LT", "GT", "LE", "GE", "NE", "NUMBER", "FLOAT", "DATE", "TEXT",
  "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index",
  "attr_name_list", "attr_name", "drop_index", "show_index",
  "create_table", "attr_def_list", "attr_def", "nullable", "number",
  "type", "ID_get", "insert", "tuple_list", "tuple", "value_list", "value",
  "value_with_neg", "delete", "updates", "modify_list", "modify_expr",
  "exp", "select_begin", "select_clause", "select", "join_list",
  "agg_func", "agg", "select_attr", "attr_list", "alias_ID", "rel_list",
  "where", "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-235)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -235,   319,  -235,   132,    32,  -235,   -53,    92,    25,    21,
      34,   -38,    73,    80,    89,    93,    99,     7,  -235,  -235,
    -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,  -235,  -235,  -235,  -235,   169,   106,  -235,  -235,    20,
      57,   121,    63,    64,   144,   145,    97,  -235,    81,    82,
     108,  -235,  -235,  -235,  -235,  -235,   100,   169,   169,  -235,
    -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,     8,  -235,
     -16,  -235,    12,   138,  -235,   118,  -235,   140,   114,    94,
     156,   181,  -235,  -235,   119,   154,   153,   125,   124,     1,
      -4,   -23,   127,  -235,  -235,  -235,   169,   169,   169,   169,
     169,  -235,    11,   128,   129,   131,   158,  -235,  -235,   201,
     186,   115,   202,   147,   190,   172,  -235,   -16,   -16,  -235,
      12,    -4,    -4,  -235,  -235,   -16,   192,    69,    87,   -16,
    -235,   193,    91,   194,   148,  -235,    77,   195,    58,  -235,
     168,    -6,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
     313,    70,   204,  -235,   254,   125,   153,   211,  -235,  -235,
    -235,  -235,   -16,   -16,   149,   152,   -16,   159,    22,   129,
     210,  -235,  -235,  -235,  -235,  -235,    -2,   160,   215,    56,
    -235,   214,   186,   235,   222,  -235,  -235,  -235,  -235,   189,
     115,   115,  -235,   238,   238,  -235,  -235,   190,   246,   180,
    -235,  -235,   236,   242,  -235,   245,   182,   203,   153,   193,
     261,   207,  -235,   239,  -235,  -235,   250,   160,  -235,  -235,
      77,   256,   195,  -235,   303,    58,   -15,    70,    70,   257,
     258,  -235,  -235,   274,   -16,   -16,   -16,   -16,   209,  -235,
    -235,  -235,  -235,   262,  -235,   160,   263,   250,   214,  -235,
    -235,   234,   264,   266,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,  -235,   267,   -16,   -14,   250,   279,   269,  -235,    58,
     -15,   200,  -235,  -235,   249,  -235,  -235,  -235,   291,   277,
     214,   115,  -235,  -235,   278,    70,  -235,   248,   253,   153,
     228,  -235,   255,   115,    70,   248,  -235
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
      92,    93,    94,    95,    96,    59,    60,    61,   107,    62,
     107,    80,   105,     0,    85,     0,    89,     0,     0,     0,
       0,     0,    30,    29,     0,     0,   112,     0,     0,     0,
      76,     0,     0,   108,    81,    83,     0,     0,     0,     0,
       0,   104,     0,     0,     0,     0,     0,    28,    36,     0,
       0,     0,     0,     0,    69,     0,    79,   107,   107,   109,
     105,    74,    75,    78,    77,   107,     0,     0,     0,   107,
      52,    39,     0,     0,     0,    37,     0,    54,     0,   131,
     135,     0,   133,   129,   123,   124,   125,   126,   127,   128,
       0,   114,     0,    67,     0,     0,   112,     0,    82,    84,
     106,   103,   107,   107,     0,     0,   107,     0,   110,     0,
       0,    47,    48,    49,    50,    51,    43,     0,     0,     0,
      64,    57,     0,     0,     0,   136,   132,   134,   130,     0,
       0,     0,   113,     0,     0,    71,    73,    69,     0,     0,
     100,    98,     0,     0,    97,     0,     0,     0,   112,    39,
       0,     0,    44,     0,    42,    35,    33,     0,    65,    66,
       0,     0,    54,    53,     0,     0,   117,   114,   114,     0,
       0,    70,    68,     0,   107,   107,   107,   107,     0,    87,
      40,    38,    46,     0,    45,     0,     0,    33,    57,    56,
      55,     0,    80,     0,   115,   116,   121,    72,   137,   102,
      99,   101,   110,   107,    43,    33,     0,     0,    58,     0,
     119,     0,   120,   111,     0,    41,    34,    31,     0,     0,
      57,     0,    32,   122,     0,   114,   118,    90,     0,   112,
       0,    88,     0,     0,   114,    90,    91
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,  -235,  -235,  -213,  -201,  -235,  -235,  -235,    96,   146,
      49,  -235,  -235,  -235,  -235,    95,   134,  -234,  -134,  -147,
    -235,  -235,   117,   163,   -35,  -235,  -127,  -235,    30,  -235,
     173,  -235,   208,   -69,    83,  -153,  -215,  -186,  -144,  -235
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   246,   216,    29,    30,    31,   170,   131,
     214,   243,   176,   132,    32,   183,   137,   221,    71,   181,
      33,    34,   156,   114,   150,    35,    36,    37,   289,    73,
      74,    75,   101,    94,   208,   112,   192,   151,   152,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    95,   180,   198,   227,   228,   189,   195,    97,    98,
      99,   184,   254,   255,   268,   211,   247,    44,   212,   116,
     180,    99,    89,    90,    97,    98,    99,    92,    47,   125,
     212,    96,    50,   213,   267,    97,    98,    99,    42,   186,
      43,   206,   187,    91,   265,   213,   284,   117,   158,   159,
     118,    92,   276,   188,    93,   239,   161,    48,   100,    56,
     168,   120,   121,   122,   123,   124,   229,   230,     5,   100,
     287,   207,    49,   248,   100,    57,    51,   126,    93,   295,
     251,   127,    58,    52,   128,   100,   180,   163,   164,    59,
      77,   252,    53,   200,   201,   285,    54,   204,   253,    45,
      46,   179,    55,    89,   165,   166,   167,   294,    59,    76,
     190,   191,    60,    61,    62,    63,    64,   171,   172,   173,
     174,   175,   218,   219,    65,    66,    67,    78,    68,    79,
      69,    70,   138,    80,    81,    84,   291,   280,    39,    58,
      40,    41,   279,    65,    66,    67,    59,    82,    83,    69,
      87,    85,    86,    88,   226,   102,   103,   104,   105,   107,
     139,   140,   141,   142,   106,   259,   260,   261,   262,    60,
      61,    62,    63,    64,   143,   144,   145,   146,   147,   148,
     149,    65,    66,    67,   108,    68,    57,    69,    70,   109,
      89,   110,   111,    58,   274,   113,   115,   119,   129,   130,
      59,   133,   134,   136,   135,   153,   225,   154,   157,   155,
     162,   177,   169,    58,   182,   185,   270,   199,   178,   202,
      59,   193,   203,    60,    61,    62,    63,    64,   210,   205,
     215,    59,   217,   220,    89,    65,    66,    67,   223,    68,
     224,    69,    70,    60,    61,    62,    63,    64,     5,   232,
     233,   269,   237,   238,   234,    65,    66,    67,    58,    68,
     235,    69,    70,   236,   241,    59,    65,    66,    67,   245,
     244,   194,    69,   242,   249,   256,   257,   258,   179,   263,
     264,   266,   277,   271,   272,    59,   206,   278,    60,    61,
      62,    63,    64,   281,   282,   283,   286,   288,   292,   293,
      65,    66,    67,   290,    68,   240,    69,    70,    60,    61,
      62,    63,    64,   275,   231,   209,   222,   250,   197,     2,
      65,    66,    67,     3,     4,   296,    69,   196,   160,     5,
       6,     7,     8,     9,    10,    11,    97,    98,    99,    12,
      13,    14,     0,     0,     0,   273,     0,     0,   139,   140,
     141,   142,    15,    16,     0,     0,     0,     0,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,     0,
      17,     0,   143,   144,   145,   146,   147,   148,   149,     0,
       0,     0,     0,     0,     0,     0,   100
};

static const yytype_int16 yycheck[] =
{
      35,    70,   136,   156,   190,   191,   150,   154,    23,    24,
      25,   138,   227,   228,   248,    17,   217,    70,    32,    18,
     154,    25,    57,    58,    23,    24,    25,    43,     3,    18,
      32,    19,    70,    47,   247,    23,    24,    25,     6,    45,
       8,    19,    48,    35,   245,    47,   280,    70,   117,   118,
      73,    43,   265,    59,    70,   208,   125,    36,    73,    52,
     129,    96,    97,    98,    99,   100,   193,   194,    10,    73,
     285,    49,    38,   220,    73,    17,     3,    66,    70,   294,
     224,    70,    24,     3,    73,    73,   220,    18,    19,    31,
      70,   225,     3,   162,   163,   281,     3,   166,   225,     7,
       8,    24,     3,   138,    35,    18,    19,   293,    31,     3,
      40,    41,    54,    55,    56,    57,    58,    26,    27,    28,
      29,    30,    66,    67,    66,    67,    68,    70,    70,     8,
      72,    73,    17,    70,    70,    38,   289,   271,     6,    24,
       8,     9,   269,    66,    67,    68,    31,     3,     3,    72,
      42,    70,    70,    53,   189,    17,    38,    17,    44,     3,
      45,    46,    47,    48,    70,   234,   235,   236,   237,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,     3,    70,    17,    72,    73,    70,
     225,    37,    39,    24,   263,    70,    72,    70,    70,    70,
      31,    70,    44,    17,     3,     3,    17,    60,    36,    19,
      18,    17,    19,    24,    19,    47,   251,     6,    70,    70,
      31,    17,    70,    54,    55,    56,    57,    58,    18,    70,
      70,    31,    17,    19,   269,    66,    67,    68,     3,    70,
      18,    72,    73,    54,    55,    56,    57,    58,    10,     3,
      70,    17,    70,    50,    18,    66,    67,    68,    24,    70,
      18,    72,    73,    18,     3,    31,    66,    67,    68,    19,
      31,    17,    72,    66,    18,    18,    18,     3,    24,    70,
      18,    18,     3,    19,    18,    31,    19,    18,    54,    55,
      56,    57,    58,    44,     3,    18,    18,    49,    70,    44,
      66,    67,    68,    50,    70,   209,    72,    73,    54,    55,
      56,    57,    58,   264,   197,   169,   182,   222,   155,     0,
      66,    67,    68,     4,     5,   295,    72,   154,   120,    10,
      11,    12,    13,    14,    15,    16,    23,    24,    25,    20,
      21,    22,    -1,    -1,    -1,   262,    -1,    -1,    45,    46,
      47,    48,    33,    34,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    59,    60,    61,    62,    63,    64,    65,    -1,
      51,    -1,    59,    60,    61,    62,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    76,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    33,    34,    51,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    90,
      91,    92,    99,   105,   106,   110,   111,   112,   124,     6,
       8,     9,     6,     8,    70,     7,     8,     3,    36,    38,
      70,     3,     3,     3,     3,     3,    52,    17,    24,    31,
      54,    55,    56,    57,    58,    66,    67,    68,    70,    72,
      73,   103,   109,   114,   115,   116,     3,    70,    70,     8,
      70,    70,     3,     3,    38,    70,    70,    42,    53,   109,
     109,    35,    43,    70,   118,   118,    19,    23,    24,    25,
      73,   117,    17,    38,    17,    44,    70,     3,     3,    70,
      37,    39,   120,    70,   108,    72,    18,    70,    73,    70,
     109,   109,   109,   109,   109,    18,    66,    70,    73,    70,
      70,    94,    98,    70,    44,     3,    17,   101,    17,    45,
      46,    47,    48,    59,    60,    61,    62,    63,    64,    65,
     109,   122,   123,     3,    60,    19,   107,    36,   118,   118,
     117,   118,    18,    18,    19,    35,    18,    19,   118,    19,
      93,    26,    27,    28,    29,    30,    97,    17,    70,    24,
     103,   104,    19,   100,   111,    47,    45,    48,    59,   123,
      40,    41,   121,    17,    17,   104,   115,   108,   120,     6,
     118,   118,    70,    70,   118,    70,    19,    49,   119,    94,
      18,    17,    32,    47,    95,    70,    89,    17,    66,    67,
      19,   102,   101,     3,    18,    17,   109,   122,   122,   111,
     111,   107,     3,    70,    18,    18,    18,    70,    50,   120,
      93,     3,    66,    96,    31,    19,    88,    89,   104,    18,
     100,   123,   103,   111,   121,   121,    18,    18,     3,   118,
     118,   118,   118,    70,    18,    89,    18,    88,   102,    17,
     109,    19,    18,   119,   118,    95,    88,     3,    18,   111,
     103,    44,     3,    18,   102,   122,    18,   121,    49,   113,
      50,   120,    70,    44,   122,   121,   113
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    75,    76,    76,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    87,    88,    88,    89,    90,    91,    92,    93,
      93,    94,    94,    95,    95,    95,    96,    97,    97,    97,
      97,    97,    98,    99,   100,   100,   101,   102,   102,   103,
     103,   103,   103,   103,   104,   104,   104,   105,   106,   107,
     107,   108,   108,   108,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   110,   111,   111,   112,
     113,   113,   114,   114,   114,   114,   114,   115,   115,   115,
     115,   115,   115,   115,   116,   117,   117,   118,   118,   118,
     119,   119,   120,   120,   121,   121,   121,   122,   122,   122,
     122,   122,   122,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   124
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
       1,     2,     4,     2,     4,     1,     1,     7,    14,     2,
       0,     7,     1,     1,     1,     1,     1,     5,     5,     7,
       5,     7,     7,     4,     2,     0,     3,     0,     1,     2,
       0,     4,     0,     3,     0,     3,     3,     3,     8,     5,
       5,     4,     7,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     2,     1,     2,     8
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
#line 220 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1493 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 225 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1501 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 230 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1509 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 236 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1517 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 242 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1525 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 248 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1533 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 254 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1542 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 260 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1550 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 266 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1559 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON  */
#line 274 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			
		}
#line 1569 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON  */
#line 280 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $8);
		}
#line 1579 "yacc_sql.tab.c"
    break;

  case 34: /* attr_name_list: COMMA attr_name attr_name_list  */
#line 289 "yacc_sql.y"
                                         {

	}
#line 1587 "yacc_sql.tab.c"
    break;

  case 35: /* attr_name: ID  */
#line 294 "yacc_sql.y"
              {
	create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $2);
}
#line 1596 "yacc_sql.tab.c"
    break;

  case 36: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 300 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1605 "yacc_sql.tab.c"
    break;

  case 37: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 307 "yacc_sql.y"
                                    {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1614 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 315 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1626 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 325 "yacc_sql.y"
                                   {    }
#line 1632 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE nullable  */
#line 330 "yacc_sql.y"
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
#line 1647 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type nullable  */
#line 341 "yacc_sql.y"
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
#line 1662 "yacc_sql.tab.c"
    break;

  case 43: /* nullable: %empty  */
#line 354 "yacc_sql.y"
        { (yyval.number)=0; }
#line 1668 "yacc_sql.tab.c"
    break;

  case 44: /* nullable: NULLABLE  */
#line 355 "yacc_sql.y"
                   { (yyval.number)=1; }
#line 1674 "yacc_sql.tab.c"
    break;

  case 45: /* nullable: NOT NULL_T  */
#line 356 "yacc_sql.y"
                     { (yyval.number)=2; }
#line 1680 "yacc_sql.tab.c"
    break;

  case 46: /* number: NUMBER  */
#line 360 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1686 "yacc_sql.tab.c"
    break;

  case 47: /* type: INT_T  */
#line 363 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1692 "yacc_sql.tab.c"
    break;

  case 48: /* type: STRING_T  */
#line 364 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1698 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 365 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1704 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 366 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1710 "yacc_sql.tab.c"
    break;

  case 51: /* type: TEXT_T  */
#line 367 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1716 "yacc_sql.tab.c"
    break;

  case 52: /* ID_get: ID  */
#line 371 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1725 "yacc_sql.tab.c"
    break;

  case 53: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 380 "yacc_sql.y"
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
#line 1745 "yacc_sql.tab.c"
    break;

  case 55: /* tuple_list: COMMA tuple tuple_list  */
#line 398 "yacc_sql.y"
                                 {
	}
#line 1752 "yacc_sql.tab.c"
    break;

  case 56: /* tuple: LBRACE value_with_neg value_list RBRACE  */
#line 404 "yacc_sql.y"
                                                {
		insert_init(&CONTEXT->insert_list[CONTEXT->insert_num++], CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1761 "yacc_sql.tab.c"
    break;

  case 58: /* value_list: COMMA value_with_neg value_list  */
#line 412 "yacc_sql.y"
                                       { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1769 "yacc_sql.tab.c"
    break;

  case 59: /* value: NUMBER  */
#line 417 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1777 "yacc_sql.tab.c"
    break;

  case 60: /* value: FLOAT  */
#line 420 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1785 "yacc_sql.tab.c"
    break;

  case 61: /* value: DATE  */
#line 423 "yacc_sql.y"
             {
		(yyvsp[0].string) = substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);
		int res = value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		if (res != 0) {
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			yyresult = 2;
			goto yyreturnlab;
		}
	}
#line 1799 "yacc_sql.tab.c"
    break;

  case 62: /* value: SSS  */
#line 432 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1808 "yacc_sql.tab.c"
    break;

  case 63: /* value: NULL_T  */
#line 436 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1816 "yacc_sql.tab.c"
    break;

  case 64: /* value_with_neg: value  */
#line 442 "yacc_sql.y"
              {
	}
#line 1823 "yacc_sql.tab.c"
    break;

  case 65: /* value_with_neg: SUB_T NUMBER  */
#line 444 "yacc_sql.y"
                       {
		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number) * -1);
	}
#line 1831 "yacc_sql.tab.c"
    break;

  case 66: /* value_with_neg: SUB_T FLOAT  */
#line 447 "yacc_sql.y"
                      {
		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats) * -1.0);
	}
#line 1839 "yacc_sql.tab.c"
    break;

  case 67: /* delete: DELETE FROM ID where SEMICOLON  */
#line 453 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1851 "yacc_sql.tab.c"
    break;

  case 68: /* updates: UPDATE ID SET modify_expr modify_list where SEMICOLON  */
#line 473 "yacc_sql.y"
                                                              {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		updates_select_init(&CONTEXT->ssql->sstr.updates, (yyvsp[-5].string), CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
		CONTEXT->select_num = 0;
		CONTEXT->attr_num = 0;
		CONTEXT->expression_attr_num = 0;
	}
#line 1864 "yacc_sql.tab.c"
    break;

  case 70: /* modify_list: COMMA modify_expr modify_list  */
#line 484 "yacc_sql.y"
                                        {

	}
#line 1872 "yacc_sql.tab.c"
    break;

  case 71: /* modify_expr: ID EQ value_with_neg  */
#line 490 "yacc_sql.y"
                             {
		updates_append_value(&CONTEXT->ssql->sstr.updates, &CONTEXT->values[CONTEXT->value_length - 1], (yyvsp[-2].string));
	}
#line 1880 "yacc_sql.tab.c"
    break;

  case 72: /* modify_expr: ID EQ LBRACE select_clause RBRACE  */
#line 493 "yacc_sql.y"
                                           {
		Value value;
		value_init_select(&value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, (yyvsp[-4].string));
	}
#line 1890 "yacc_sql.tab.c"
    break;

  case 73: /* modify_expr: ID EQ agg  */
#line 498 "yacc_sql.y"
                    {
		Value value;
		// value_init_agg(&value, &CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]-1]);
		// CONTEXT->select_attr_num[CONTEXT->select_num]--;
		value_init_agg(&value, &CONTEXT->attrs[--CONTEXT->expression_attr_num]);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, (yyvsp[-2].string));
	}
#line 1902 "yacc_sql.tab.c"
    break;

  case 74: /* exp: exp ADD_T exp  */
#line 509 "yacc_sql.y"
                      { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, ADD); }
#line 1908 "yacc_sql.tab.c"
    break;

  case 75: /* exp: exp SUB_T exp  */
#line 510 "yacc_sql.y"
                        { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, SUB); }
#line 1914 "yacc_sql.tab.c"
    break;

  case 76: /* exp: SUB_T exp  */
#line 511 "yacc_sql.y"
                    {
		// Value left_value;
		// value_init_integer(&left_value, 0);
		// Exp *left_exp = create_expression(NULL, NULL, &left_value, NULL, VAL);
		(yyval.exp1) = create_expression(NULL, (yyvsp[0].exp1), NULL, NULL, SUB);
	}
#line 1925 "yacc_sql.tab.c"
    break;

  case 77: /* exp: exp STAR exp  */
#line 517 "yacc_sql.y"
                       { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, MUL); }
#line 1931 "yacc_sql.tab.c"
    break;

  case 78: /* exp: exp DIV_T exp  */
#line 518 "yacc_sql.y"
                        { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, DIV); }
#line 1937 "yacc_sql.tab.c"
    break;

  case 79: /* exp: LBRACE exp RBRACE  */
#line 519 "yacc_sql.y"
                            { 
		Exp *exp = (yyvsp[-1].exp1);
		++exp->lbrace;
		++exp->rbrace;
		(yyval.exp1) = exp; 
	}
#line 1948 "yacc_sql.tab.c"
    break;

  case 80: /* exp: value  */
#line 525 "yacc_sql.y"
                { 
		(yyval.exp1) = create_expression(NULL, NULL, &CONTEXT->values[CONTEXT->value_length - 1], NULL, VAL); 
	}
#line 1956 "yacc_sql.tab.c"
    break;

  case 81: /* exp: ID alias_ID  */
#line 528 "yacc_sql.y"
                      { 
		RelAttr attr;
		relation_attr_init_with_alias(&attr, NULL, (yyvsp[-1].string), (yyvsp[0].string));
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
#line 1967 "yacc_sql.tab.c"
    break;

  case 82: /* exp: ID DOT ID alias_ID  */
#line 534 "yacc_sql.y"
                             {
		RelAttr attr;
		
		relation_attr_init_with_alias(&attr, (yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[0].string));
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
#line 1979 "yacc_sql.tab.c"
    break;

  case 83: /* exp: STAR alias_ID  */
#line 541 "yacc_sql.y"
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
#line 1996 "yacc_sql.tab.c"
    break;

  case 84: /* exp: ID DOT STAR alias_ID  */
#line 553 "yacc_sql.y"
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
#line 2013 "yacc_sql.tab.c"
    break;

  case 85: /* exp: agg  */
#line 565 "yacc_sql.y"
              {
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &CONTEXT->attrs[CONTEXT->expression_attr_num - 1], ATTR);
	}
#line 2021 "yacc_sql.tab.c"
    break;

  case 86: /* select_begin: SELECT  */
#line 572 "yacc_sql.y"
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
#line 2037 "yacc_sql.tab.c"
    break;

  case 87: /* select_clause: select_begin select_attr FROM ID alias_ID rel_list where  */
#line 585 "yacc_sql.y"
                                                                 {
		// 当进入该语句中时，depth一定是>=1的，不用担心越界问题
		// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
		// selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], $4);
		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-3].string), (yyvsp[-2].string));

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
#line 2075 "yacc_sql.tab.c"
    break;

  case 88: /* select_clause: select_begin select_attr FROM ID alias_ID INNER JOIN ID alias_ID ON condition condition_list join_list where  */
#line 618 "yacc_sql.y"
                                                                                                                       {
		// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;

		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-6].string), (yyvsp[-5].string));
		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-10].string), (yyvsp[-9].string));

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
#line 2114 "yacc_sql.tab.c"
    break;

  case 89: /* select: select_clause SEMICOLON  */
#line 655 "yacc_sql.y"
                            {
		// 这里说明select是主语句
		CONTEXT->ssql->flag=SCF_SELECT;//"select";
		CONTEXT->ssql->sstr.selection = CONTEXT->selections[CONTEXT->select_num-1];
	}
#line 2124 "yacc_sql.tab.c"
    break;

  case 91: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 664 "yacc_sql.y"
        {
		selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-4].string));
	}
#line 2132 "yacc_sql.tab.c"
    break;

  case 92: /* agg_func: MAX_T  */
#line 670 "yacc_sql.y"
              { (yyval.number)=MAX; }
#line 2138 "yacc_sql.tab.c"
    break;

  case 93: /* agg_func: MIN_T  */
#line 671 "yacc_sql.y"
                { (yyval.number)=MIN; }
#line 2144 "yacc_sql.tab.c"
    break;

  case 94: /* agg_func: COUNT_T  */
#line 672 "yacc_sql.y"
                  { (yyval.number)=COUNT; }
#line 2150 "yacc_sql.tab.c"
    break;

  case 95: /* agg_func: AVG_T  */
#line 673 "yacc_sql.y"
                { (yyval.number)=AVG; }
#line 2156 "yacc_sql.tab.c"
    break;

  case 96: /* agg_func: SUM_T  */
#line 674 "yacc_sql.y"
                { (yyval.number)=SUM; }
#line 2162 "yacc_sql.tab.c"
    break;

  case 97: /* agg: agg_func LBRACE STAR RBRACE alias_ID  */
#line 679 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, "*", (yyvsp[-4].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2173 "yacc_sql.tab.c"
    break;

  case 98: /* agg: agg_func LBRACE ID RBRACE alias_ID  */
#line 685 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2184 "yacc_sql.tab.c"
    break;

  case 99: /* agg: agg_func LBRACE ID DOT ID RBRACE alias_ID  */
#line 691 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-6].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2195 "yacc_sql.tab.c"
    break;

  case 100: /* agg: agg_func LBRACE NUMBER RBRACE alias_ID  */
#line 697 "yacc_sql.y"
                                                 {
		RelAttr attr;
		relation_attr_init_with_agg_num(&attr, (yyvsp[-4].number), (yyvsp[-2].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2206 "yacc_sql.tab.c"
    break;

  case 101: /* agg: agg_func LBRACE STAR COMMA ID RBRACE alias_ID  */
#line 703 "yacc_sql.y"
                                                        {
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2216 "yacc_sql.tab.c"
    break;

  case 102: /* agg: agg_func LBRACE ID COMMA ID RBRACE alias_ID  */
#line 708 "yacc_sql.y"
                                                      {
		// 错误类型
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2227 "yacc_sql.tab.c"
    break;

  case 103: /* agg: agg_func LBRACE RBRACE alias_ID  */
#line 714 "yacc_sql.y"
                                          {
		// 错误类型
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2238 "yacc_sql.tab.c"
    break;

  case 104: /* select_attr: exp attr_list  */
#line 726 "yacc_sql.y"
                      {
		CONTEXT->expressions[CONTEXT->expr_num++] = (yyvsp[-1].exp1);
		CONTEXT->attr_num = CONTEXT->expression_attr_num;
	}
#line 2247 "yacc_sql.tab.c"
    break;

  case 106: /* attr_list: COMMA exp attr_list  */
#line 734 "yacc_sql.y"
                              {
		CONTEXT->expressions[CONTEXT->expr_num++] = (yyvsp[-1].exp1);
		// 因为现在条件语句中的RelAttr也会占用全局的attrs
		// 需要进行一下区别，attr_num只记录
		CONTEXT->attr_num = CONTEXT->expression_attr_num;
	}
#line 2258 "yacc_sql.tab.c"
    break;

  case 107: /* alias_ID: %empty  */
#line 744 "yacc_sql.y"
        { (yyval.string) = NULL; }
#line 2264 "yacc_sql.tab.c"
    break;

  case 108: /* alias_ID: ID  */
#line 745 "yacc_sql.y"
             { (yyval.string) = (yyvsp[0].string); }
#line 2270 "yacc_sql.tab.c"
    break;

  case 109: /* alias_ID: AS ID  */
#line 746 "yacc_sql.y"
                { (yyval.string) = (yyvsp[0].string); }
#line 2276 "yacc_sql.tab.c"
    break;

  case 111: /* rel_list: COMMA ID alias_ID rel_list  */
#line 751 "yacc_sql.y"
                                 {	
		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-2].string), (yyvsp[-1].string));
	}
#line 2284 "yacc_sql.tab.c"
    break;

  case 113: /* where: WHERE condition condition_list  */
#line 757 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
	}
#line 2292 "yacc_sql.tab.c"
    break;

  case 115: /* condition_list: AND condition condition_list  */
#line 765 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		CONTEXT->selections[CONTEXT->select_num].is_and = 1; 
	}
#line 2301 "yacc_sql.tab.c"
    break;

  case 116: /* condition_list: OR condition condition_list  */
#line 769 "yacc_sql.y"
                                      {
		CONTEXT->selections[CONTEXT->select_num].is_and = 0;
	}
#line 2309 "yacc_sql.tab.c"
    break;

  case 117: /* condition: exp comOp exp  */
#line 776 "yacc_sql.y"
                      {
		Exp *left_exp = (yyvsp[-2].exp1);
		Exp *right_exp = (yyvsp[0].exp1);
		Condition condition;
		condition_init_with_exp(&condition, (yyvsp[-1].number), left_exp, right_exp);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
#line 2322 "yacc_sql.tab.c"
    break;

  case 118: /* condition: exp comOp LBRACE value COMMA value value_list RBRACE  */
#line 784 "yacc_sql.y"
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
#line 2345 "yacc_sql.tab.c"
    break;

  case 119: /* condition: LBRACE select_clause RBRACE comOp exp  */
#line 802 "yacc_sql.y"
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
#line 2361 "yacc_sql.tab.c"
    break;

  case 120: /* condition: exp comOp LBRACE select_clause RBRACE  */
#line 813 "yacc_sql.y"
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
#line 2377 "yacc_sql.tab.c"
    break;

  case 121: /* condition: comOp LBRACE select_clause RBRACE  */
#line 824 "yacc_sql.y"
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
#line 2395 "yacc_sql.tab.c"
    break;

  case 122: /* condition: LBRACE select_clause RBRACE comOp LBRACE select_clause RBRACE  */
#line 837 "yacc_sql.y"
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
#line 2411 "yacc_sql.tab.c"
    break;

  case 123: /* comOp: EQ  */
#line 851 "yacc_sql.y"
             { (yyval.number) = EQUAL_TO; }
#line 2417 "yacc_sql.tab.c"
    break;

  case 124: /* comOp: LT  */
#line 852 "yacc_sql.y"
         { (yyval.number) = LESS_THAN; }
#line 2423 "yacc_sql.tab.c"
    break;

  case 125: /* comOp: GT  */
#line 853 "yacc_sql.y"
         { (yyval.number) = GREAT_THAN; }
#line 2429 "yacc_sql.tab.c"
    break;

  case 126: /* comOp: LE  */
#line 854 "yacc_sql.y"
         { (yyval.number) = LESS_EQUAL; }
#line 2435 "yacc_sql.tab.c"
    break;

  case 127: /* comOp: GE  */
#line 855 "yacc_sql.y"
         { (yyval.number) = GREAT_EQUAL; }
#line 2441 "yacc_sql.tab.c"
    break;

  case 128: /* comOp: NE  */
#line 856 "yacc_sql.y"
         { (yyval.number) = NOT_EQUAL; }
#line 2447 "yacc_sql.tab.c"
    break;

  case 129: /* comOp: LIKE  */
#line 857 "yacc_sql.y"
               { (yyval.number) = LIKE_MATCH; }
#line 2453 "yacc_sql.tab.c"
    break;

  case 130: /* comOp: NOT LIKE  */
#line 858 "yacc_sql.y"
                   { (yyval.number) = NOT_LIKE; }
#line 2459 "yacc_sql.tab.c"
    break;

  case 131: /* comOp: IN  */
#line 859 "yacc_sql.y"
             { (yyval.number) = IN_OP; }
#line 2465 "yacc_sql.tab.c"
    break;

  case 132: /* comOp: NOT IN  */
#line 860 "yacc_sql.y"
                 { (yyval.number) = NOT_IN_OP; }
#line 2471 "yacc_sql.tab.c"
    break;

  case 133: /* comOp: EXIST  */
#line 861 "yacc_sql.y"
                { (yyval.number) =EXISTS_OP; }
#line 2477 "yacc_sql.tab.c"
    break;

  case 134: /* comOp: NOT EXIST  */
#line 862 "yacc_sql.y"
                    { (yyval.number) = NOT_EXISTS_OP; }
#line 2483 "yacc_sql.tab.c"
    break;

  case 135: /* comOp: IS  */
#line 863 "yacc_sql.y"
             { (yyval.number) = IS_OP; }
#line 2489 "yacc_sql.tab.c"
    break;

  case 136: /* comOp: IS NOT  */
#line 864 "yacc_sql.y"
                 { (yyval.number) = IS_NOT_OP; }
#line 2495 "yacc_sql.tab.c"
    break;

  case 137: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 869 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2504 "yacc_sql.tab.c"
    break;


#line 2508 "yacc_sql.tab.c"

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

#line 874 "yacc_sql.y"

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
