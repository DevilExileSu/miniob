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
  YYSYMBOL_INT_T = 23,                     /* INT_T  */
  YYSYMBOL_STRING_T = 24,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 25,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 26,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 27,                    /* TEXT_T  */
  YYSYMBOL_NULL_T = 28,                    /* NULL_T  */
  YYSYMBOL_NULLABLE = 29,                  /* NULLABLE  */
  YYSYMBOL_HELP = 30,                      /* HELP  */
  YYSYMBOL_EXIT = 31,                      /* EXIT  */
  YYSYMBOL_DOT = 32,                       /* DOT  */
  YYSYMBOL_INTO = 33,                      /* INTO  */
  YYSYMBOL_VALUES = 34,                    /* VALUES  */
  YYSYMBOL_FROM = 35,                      /* FROM  */
  YYSYMBOL_WHERE = 36,                     /* WHERE  */
  YYSYMBOL_AND = 37,                       /* AND  */
  YYSYMBOL_OR = 38,                        /* OR  */
  YYSYMBOL_SET = 39,                       /* SET  */
  YYSYMBOL_AS = 40,                        /* AS  */
  YYSYMBOL_ON = 41,                        /* ON  */
  YYSYMBOL_IN = 42,                        /* IN  */
  YYSYMBOL_IS = 43,                        /* IS  */
  YYSYMBOL_NOT = 44,                       /* NOT  */
  YYSYMBOL_EXIST = 45,                     /* EXIST  */
  YYSYMBOL_INNER = 46,                     /* INNER  */
  YYSYMBOL_JOIN = 47,                      /* JOIN  */
  YYSYMBOL_LOAD = 48,                      /* LOAD  */
  YYSYMBOL_DATA = 49,                      /* DATA  */
  YYSYMBOL_INFILE = 50,                    /* INFILE  */
  YYSYMBOL_MAX_T = 51,                     /* MAX_T  */
  YYSYMBOL_MIN_T = 52,                     /* MIN_T  */
  YYSYMBOL_COUNT_T = 53,                   /* COUNT_T  */
  YYSYMBOL_AVG_T = 54,                     /* AVG_T  */
  YYSYMBOL_SUM_T = 55,                     /* SUM_T  */
  YYSYMBOL_LIKE = 56,                      /* LIKE  */
  YYSYMBOL_EQ = 57,                        /* EQ  */
  YYSYMBOL_LT = 58,                        /* LT  */
  YYSYMBOL_GT = 59,                        /* GT  */
  YYSYMBOL_LE = 60,                        /* LE  */
  YYSYMBOL_GE = 61,                        /* GE  */
  YYSYMBOL_NE = 62,                        /* NE  */
  YYSYMBOL_ADD_T = 63,                     /* ADD_T  */
  YYSYMBOL_SUB_T = 64,                     /* SUB_T  */
  YYSYMBOL_DIV_T = 65,                     /* DIV_T  */
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
  YYSYMBOL_delete = 104,                   /* delete  */
  YYSYMBOL_updates = 105,                  /* updates  */
  YYSYMBOL_modify_list = 106,              /* modify_list  */
  YYSYMBOL_modify_expr = 107,              /* modify_expr  */
  YYSYMBOL_exp = 108,                      /* exp  */
  YYSYMBOL_select_begin = 109,             /* select_begin  */
  YYSYMBOL_select_clause = 110,            /* select_clause  */
  YYSYMBOL_select = 111,                   /* select  */
  YYSYMBOL_join_list = 112,                /* join_list  */
  YYSYMBOL_agg_func = 113,                 /* agg_func  */
  YYSYMBOL_agg = 114,                      /* agg  */
  YYSYMBOL_select_attr = 115,              /* select_attr  */
  YYSYMBOL_attr_list = 116,                /* attr_list  */
  YYSYMBOL_alias_ID = 117,                 /* alias_ID  */
  YYSYMBOL_rel_list = 118,                 /* rel_list  */
  YYSYMBOL_where = 119,                    /* where  */
  YYSYMBOL_condition_list = 120,           /* condition_list  */
  YYSYMBOL_conjunction = 121,              /* conjunction  */
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
#define YYLAST   368

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  133
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  285

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
       0,   191,   191,   193,   197,   198,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   219,   224,   229,   235,   241,   247,   253,   259,
     265,   272,   278,   287,   288,   293,   298,   306,   313,   322,
     324,   328,   339,   353,   354,   355,   359,   362,   363,   364,
     365,   366,   369,   378,   396,   397,   403,   409,   411,   416,
     419,   422,   431,   435,   441,   462,   472,   473,   479,   482,
     487,   498,   499,   500,   501,   502,   503,   506,   512,   519,
     531,   543,   550,   563,   596,   633,   640,   641,   648,   649,
     650,   651,   652,   657,   663,   669,   675,   681,   686,   692,
     701,   707,   709,   719,   720,   721,   724,   726,   730,   732,
     738,   740,   747,   748,   752,   760,   771,   782,   795,   809,
     810,   811,   812,   813,   814,   815,   816,   817,   818,   819,
     820,   821,   822,   826
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
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "TEXT_T", "NULL_T", "NULLABLE", "HELP", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "OR", "SET", "AS", "ON",
  "IN", "IS", "NOT", "EXIST", "INNER", "JOIN", "LOAD", "DATA", "INFILE",
  "MAX_T", "MIN_T", "COUNT_T", "AVG_T", "SUM_T", "LIKE", "EQ", "LT", "GT",
  "LE", "GE", "NE", "ADD_T", "SUB_T", "DIV_T", "NUMBER", "FLOAT", "DATE",
  "TEXT", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index",
  "attr_name_list", "attr_name", "drop_index", "show_index",
  "create_table", "attr_def_list", "attr_def", "nullable", "number",
  "type", "ID_get", "insert", "tuple_list", "tuple", "value_list", "value",
  "delete", "updates", "modify_list", "modify_expr", "exp", "select_begin",
  "select_clause", "select", "join_list", "agg_func", "agg", "select_attr",
  "attr_list", "alias_ID", "rel_list", "where", "condition_list",
  "conjunction", "condition", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-229)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -229,   299,  -229,   100,    47,  -229,   -52,    85,    21,    -3,
       0,   -30,    40,    51,    75,    77,    79,    20,  -229,  -229,
    -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,
    -229,  -229,  -229,  -229,  -229,    90,    84,  -229,  -229,    28,
      30,   102,    46,    55,   114,   126,    99,  -229,    61,    65,
      98,  -229,  -229,  -229,  -229,  -229,    88,    90,  -229,  -229,
    -229,  -229,  -229,  -229,  -229,  -229,  -229,   -26,  -229,   -32,
    -229,     8,   122,  -229,   105,  -229,   129,   106,    81,   146,
     149,  -229,  -229,    83,   121,   125,    94,    93,   -15,   -45,
      97,  -229,  -229,  -229,    90,    90,    90,    90,    90,  -229,
      13,   107,   108,   109,   127,  -229,  -229,   163,   164,   131,
     192,   123,   181,   169,  -229,   -32,   -32,  -229,     8,   -31,
     -31,  -229,  -229,   -32,   188,     1,    78,   -32,  -229,   189,
      96,   190,   139,  -229,   -21,   193,    60,  -229,   167,   -19,
    -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,   280,    66,
     196,  -229,   234,    94,   125,   208,  -229,  -229,  -229,  -229,
     -32,   -32,   145,   147,   -32,   148,    -7,   108,   198,  -229,
    -229,  -229,  -229,  -229,    -8,   150,   202,   204,   164,   218,
     206,  -229,  -229,  -229,  -229,   177,  -229,  -229,  -229,   131,
     215,   215,  -229,  -229,   181,   223,   157,  -229,  -229,   216,
     217,  -229,   219,   168,   194,   125,   189,   236,   174,  -229,
     214,  -229,  -229,   229,   150,   -21,   235,   193,  -229,   306,
      60,    26,    66,   237,   243,  -229,  -229,   249,   -32,   -32,
     -32,   -32,   184,  -229,  -229,  -229,  -229,   245,  -229,   150,
     246,   229,   204,  -229,  -229,   205,   247,  -229,  -229,  -229,
    -229,  -229,  -229,  -229,   248,   -32,   -12,   229,   263,   250,
    -229,    60,    26,  -229,  -229,   228,  -229,  -229,  -229,   267,
     256,   131,  -229,  -229,    66,   230,   232,   125,   210,  -229,
     240,   131,    66,   230,  -229
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    82,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     0,     0,     4,    19,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,    25,    26,    27,    23,    22,     0,     0,    63,    88,
      89,    90,    91,    92,    59,    60,    61,   103,    62,   103,
      76,   101,     0,    81,     0,    85,     0,     0,     0,     0,
       0,    30,    29,     0,     0,   108,     0,     0,     0,     0,
       0,   104,    77,    79,     0,     0,     0,     0,     0,   100,
       0,     0,     0,     0,     0,    28,    36,     0,     0,     0,
       0,     0,    66,     0,    75,   103,   103,   105,   101,    71,
      72,    74,    73,   103,     0,     0,     0,   103,    52,    39,
       0,     0,     0,    37,     0,    54,     0,   127,   131,     0,
     129,   125,   119,   120,   121,   122,   123,   124,     0,   110,
       0,    64,     0,     0,   108,     0,    78,    80,   102,    99,
     103,   103,     0,     0,   103,     0,   106,     0,     0,    47,
      48,    49,    50,    51,    43,     0,     0,    57,     0,     0,
       0,   132,   128,   130,   126,     0,   112,   113,   109,     0,
       0,     0,    68,    70,    66,     0,     0,    96,    94,     0,
       0,    93,     0,     0,     0,   108,    39,     0,     0,    44,
       0,    42,    35,    33,     0,     0,     0,    54,    53,     0,
       0,   114,   110,     0,     0,    67,    65,     0,   103,   103,
     103,   103,     0,    83,    40,    38,    46,     0,    45,     0,
       0,    33,    57,    56,    55,     0,     0,   111,   117,    69,
     133,    98,    95,    97,   106,   103,    43,    33,     0,     0,
      58,     0,   115,   116,   107,     0,    41,    34,    31,     0,
       0,     0,    32,   118,   110,    86,     0,   108,     0,    84,
       0,     0,   110,    86,    87
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,
    -229,  -229,  -229,  -228,  -198,  -229,  -229,  -229,    76,   116,
      34,  -229,  -229,  -229,  -229,    67,   113,    50,  -130,  -229,
    -229,   101,   140,   -35,  -229,  -125,  -229,    11,  -229,   144,
    -229,   179,   -59,    44,  -153,  -207,  -229,  -187,  -143,  -229
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   240,   213,    29,    30,    31,   168,   129,
     211,   237,   174,   130,    32,   179,   135,   216,    70,    33,
      34,   154,   112,    88,    35,    36,    37,   277,    72,    73,
      74,    99,    92,   205,   110,   188,   189,   149,   150,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,   195,   222,   114,   177,   185,    89,    58,    90,   208,
      93,   180,   203,   259,    90,   247,   241,   209,    44,   161,
     162,   209,   192,   182,    47,   115,   183,    94,   116,   267,
      48,   123,   210,   163,    97,    49,   210,   184,    91,   204,
      50,   257,    98,    51,    91,    64,    65,    66,    95,    96,
      97,    68,   233,    42,    52,    43,   156,   157,    98,   118,
     119,   120,   121,   122,   159,   223,   224,   275,   166,    56,
       5,    95,    96,    97,   148,   283,   245,    57,    53,   124,
      54,    98,    55,   125,   274,   242,   126,    75,    58,    95,
      96,    97,    45,    46,   282,   246,   164,   165,    76,    98,
      77,   197,   198,   186,   187,   201,    39,    57,    40,    41,
      78,    59,    60,    61,    62,    63,    79,    81,    58,   169,
     170,   171,   172,   173,   279,    80,    64,    65,    66,    82,
      67,    84,    68,    69,    83,    85,   270,    86,    87,   100,
     101,    59,    60,    61,    62,    63,   102,   103,   136,   105,
     221,   104,   106,   107,   148,   108,    64,    65,    66,    58,
      67,   109,    68,    69,   111,   113,   133,   117,   132,   251,
     252,   253,   254,   137,   138,   139,   140,   127,   128,   131,
     152,   134,    59,    60,    61,    62,    63,   141,   142,   143,
     144,   145,   146,   147,   220,   151,   265,    64,    65,    66,
     153,    67,   155,    68,    69,    58,   160,   175,   167,   176,
     262,   181,   178,   190,   196,   199,   207,   200,   202,   214,
     212,   218,   261,   215,   219,     5,   226,   227,    59,    60,
      61,    62,    63,    58,   228,   229,   148,   230,   231,   235,
     236,   232,   238,    64,    65,    66,   148,    67,   239,    68,
      69,   191,   250,   243,   255,   248,    59,    60,    61,    62,
      63,   249,    58,   256,   258,   263,   268,   203,   269,   271,
     272,    64,    65,    66,   273,    67,   276,    68,    69,   278,
     280,   281,   234,   206,   244,    59,    60,    61,    62,    63,
     266,   217,   260,   194,   284,   225,   193,   158,   264,     2,
      64,    65,    66,     3,     4,     0,    68,     0,     0,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,    12,
      13,    14,   137,   138,   139,   140,     0,     0,     0,    15,
      16,     0,     0,     0,     0,     0,   141,   142,   143,   144,
     145,   146,   147,    95,    96,    97,     0,    17,   137,   138,
     139,   140,     0,    98,     0,     0,     0,     0,     0,     0,
       0,     0,   141,   142,   143,   144,   145,   146,   147
};

static const yytype_int16 yycheck[] =
{
      35,   154,   189,    18,   134,   148,    32,    28,    40,    17,
      69,   136,    19,   241,    40,   222,   214,    29,    70,    18,
      19,    29,   152,    42,     3,    70,    45,    19,    73,   257,
      33,    18,    44,    32,    65,    35,    44,    56,    70,    46,
      70,   239,    73,     3,    70,    66,    67,    68,    63,    64,
      65,    72,   205,     6,     3,     8,   115,   116,    73,    94,
      95,    96,    97,    98,   123,   190,   191,   274,   127,    49,
      10,    63,    64,    65,   109,   282,   219,    17,     3,    66,
       3,    73,     3,    70,   271,   215,    73,     3,    28,    63,
      64,    65,     7,     8,   281,   220,    18,    19,    70,    73,
      70,   160,   161,    37,    38,   164,     6,    17,     8,     9,
       8,    51,    52,    53,    54,    55,    70,     3,    28,    23,
      24,    25,    26,    27,   277,    70,    66,    67,    68,     3,
      70,    70,    72,    73,    35,    70,   261,    39,    50,    17,
      35,    51,    52,    53,    54,    55,    17,    41,    17,     3,
     185,    70,     3,    70,   189,    34,    66,    67,    68,    28,
      70,    36,    72,    73,    70,    72,     3,    70,    41,   228,
     229,   230,   231,    42,    43,    44,    45,    70,    70,    70,
      57,    17,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    17,     3,   255,    66,    67,    68,
      19,    70,    33,    72,    73,    28,    18,    17,    19,    70,
     245,    44,    19,    17,     6,    70,    18,    70,    70,    17,
      70,     3,    17,    19,    18,    10,     3,    70,    51,    52,
      53,    54,    55,    28,    18,    18,   271,    18,    70,     3,
      66,    47,    28,    66,    67,    68,   281,    70,    19,    72,
      73,    17,     3,    18,    70,    18,    51,    52,    53,    54,
      55,    18,    28,    18,    18,    18,     3,    19,    18,    41,
       3,    66,    67,    68,    18,    70,    46,    72,    73,    47,
      70,    41,   206,   167,   217,    51,    52,    53,    54,    55,
     256,   178,   242,   153,   283,   194,   152,   118,   254,     0,
      66,    67,    68,     4,     5,    -1,    72,    -1,    -1,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    -1,    20,
      21,    22,    42,    43,    44,    45,    -1,    -1,    -1,    30,
      31,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    -1,    48,    42,    43,
      44,    45,    -1,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    62
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    76,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    30,    31,    48,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    90,
      91,    92,    99,   104,   105,   109,   110,   111,   124,     6,
       8,     9,     6,     8,    70,     7,     8,     3,    33,    35,
      70,     3,     3,     3,     3,     3,    49,    17,    28,    51,
      52,    53,    54,    55,    66,    67,    68,    70,    72,    73,
     103,   108,   113,   114,   115,     3,    70,    70,     8,    70,
      70,     3,     3,    35,    70,    70,    39,    50,   108,    32,
      40,    70,   117,   117,    19,    63,    64,    65,    73,   116,
      17,    35,    17,    41,    70,     3,     3,    70,    34,    36,
     119,    70,   107,    72,    18,    70,    73,    70,   108,   108,
     108,   108,   108,    18,    66,    70,    73,    70,    70,    94,
      98,    70,    41,     3,    17,   101,    17,    42,    43,    44,
      45,    56,    57,    58,    59,    60,    61,    62,   108,   122,
     123,     3,    57,    19,   106,    33,   117,   117,   116,   117,
      18,    18,    19,    32,    18,    19,   117,    19,    93,    23,
      24,    25,    26,    27,    97,    17,    70,   103,    19,   100,
     110,    44,    42,    45,    56,   123,    37,    38,   120,   121,
      17,    17,   103,   114,   107,   119,     6,   117,   117,    70,
      70,   117,    70,    19,    46,   118,    94,    18,    17,    29,
      44,    95,    70,    89,    17,    19,   102,   101,     3,    18,
      17,   108,   122,   110,   110,   106,     3,    70,    18,    18,
      18,    70,    47,   119,    93,     3,    66,    96,    28,    19,
      88,    89,   103,    18,   100,   123,   110,   120,    18,    18,
       3,   117,   117,   117,   117,    70,    18,    89,    18,    88,
     102,    17,   108,    18,   118,   117,    95,    88,     3,    18,
     110,    41,     3,    18,   122,   120,    46,   112,    47,   119,
      70,    41,   122,   120,   112
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
     103,   103,   103,   103,   104,   105,   106,   106,   107,   107,
     107,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   109,   110,   110,   111,   112,   112,   113,   113,
     113,   113,   113,   114,   114,   114,   114,   114,   114,   114,
     115,   116,   116,   117,   117,   117,   118,   118,   119,   119,
     120,   120,   121,   121,   122,   122,   122,   122,   122,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   124
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
       1,     1,     1,     1,     5,     7,     0,     3,     3,     5,
       3,     3,     3,     3,     3,     3,     1,     2,     4,     2,
       4,     1,     1,     7,    14,     2,     0,     7,     1,     1,
       1,     1,     1,     5,     5,     7,     5,     7,     7,     4,
       2,     0,     3,     0,     1,     2,     0,     4,     0,     3,
       0,     3,     1,     1,     3,     5,     5,     4,     7,     1,
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
#line 219 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1486 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 224 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1494 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 229 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1502 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 235 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1510 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 241 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1518 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 247 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1526 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 253 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1535 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 259 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1543 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 265 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1552 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON  */
#line 273 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			
		}
#line 1562 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON  */
#line 279 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $8);
		}
#line 1572 "yacc_sql.tab.c"
    break;

  case 34: /* attr_name_list: COMMA attr_name attr_name_list  */
#line 288 "yacc_sql.y"
                                         {

	}
#line 1580 "yacc_sql.tab.c"
    break;

  case 35: /* attr_name: ID  */
#line 293 "yacc_sql.y"
              {
	create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $2);
}
#line 1589 "yacc_sql.tab.c"
    break;

  case 36: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 299 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1598 "yacc_sql.tab.c"
    break;

  case 37: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 306 "yacc_sql.y"
                                    {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1607 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 314 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1619 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 324 "yacc_sql.y"
                                   {    }
#line 1625 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE nullable  */
#line 329 "yacc_sql.y"
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
#line 1640 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type nullable  */
#line 340 "yacc_sql.y"
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
#line 1655 "yacc_sql.tab.c"
    break;

  case 43: /* nullable: %empty  */
#line 353 "yacc_sql.y"
        { (yyval.number)=0; }
#line 1661 "yacc_sql.tab.c"
    break;

  case 44: /* nullable: NULLABLE  */
#line 354 "yacc_sql.y"
                   { (yyval.number)=1; }
#line 1667 "yacc_sql.tab.c"
    break;

  case 45: /* nullable: NOT NULL_T  */
#line 355 "yacc_sql.y"
                     { (yyval.number)=2; }
#line 1673 "yacc_sql.tab.c"
    break;

  case 46: /* number: NUMBER  */
#line 359 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1679 "yacc_sql.tab.c"
    break;

  case 47: /* type: INT_T  */
#line 362 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1685 "yacc_sql.tab.c"
    break;

  case 48: /* type: STRING_T  */
#line 363 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1691 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 364 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1697 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 365 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1703 "yacc_sql.tab.c"
    break;

  case 51: /* type: TEXT_T  */
#line 366 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1709 "yacc_sql.tab.c"
    break;

  case 52: /* ID_get: ID  */
#line 370 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1718 "yacc_sql.tab.c"
    break;

  case 53: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 379 "yacc_sql.y"
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
#line 1738 "yacc_sql.tab.c"
    break;

  case 55: /* tuple_list: COMMA tuple tuple_list  */
#line 397 "yacc_sql.y"
                                 {
	}
#line 1745 "yacc_sql.tab.c"
    break;

  case 56: /* tuple: LBRACE value value_list RBRACE  */
#line 403 "yacc_sql.y"
                                       {
		insert_init(&CONTEXT->insert_list[CONTEXT->insert_num++], CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1754 "yacc_sql.tab.c"
    break;

  case 58: /* value_list: COMMA value value_list  */
#line 411 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1762 "yacc_sql.tab.c"
    break;

  case 59: /* value: NUMBER  */
#line 416 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1770 "yacc_sql.tab.c"
    break;

  case 60: /* value: FLOAT  */
#line 419 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1778 "yacc_sql.tab.c"
    break;

  case 61: /* value: DATE  */
#line 422 "yacc_sql.y"
             {
		(yyvsp[0].string) = substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);
		int res = value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		if (res != 0) {
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			yyresult = 2;
			goto yyreturnlab;
		}
	}
#line 1792 "yacc_sql.tab.c"
    break;

  case 62: /* value: SSS  */
#line 431 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1801 "yacc_sql.tab.c"
    break;

  case 63: /* value: NULL_T  */
#line 435 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1809 "yacc_sql.tab.c"
    break;

  case 64: /* delete: DELETE FROM ID where SEMICOLON  */
#line 442 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1821 "yacc_sql.tab.c"
    break;

  case 65: /* updates: UPDATE ID SET modify_expr modify_list where SEMICOLON  */
#line 462 "yacc_sql.y"
                                                              {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		updates_select_init(&CONTEXT->ssql->sstr.updates, (yyvsp[-5].string), CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
		CONTEXT->select_num = 0;
		CONTEXT->attr_num = 0;
		CONTEXT->expression_attr_num = 0;
	}
#line 1834 "yacc_sql.tab.c"
    break;

  case 67: /* modify_list: COMMA modify_expr modify_list  */
#line 473 "yacc_sql.y"
                                        {

	}
#line 1842 "yacc_sql.tab.c"
    break;

  case 68: /* modify_expr: ID EQ value  */
#line 479 "yacc_sql.y"
                    {
		updates_append_value(&CONTEXT->ssql->sstr.updates, &CONTEXT->values[CONTEXT->value_length - 1], (yyvsp[-2].string));
	}
#line 1850 "yacc_sql.tab.c"
    break;

  case 69: /* modify_expr: ID EQ LBRACE select_clause RBRACE  */
#line 482 "yacc_sql.y"
                                           {
		Value value;
		value_init_select(&value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, (yyvsp[-4].string));
	}
#line 1860 "yacc_sql.tab.c"
    break;

  case 70: /* modify_expr: ID EQ agg  */
#line 487 "yacc_sql.y"
                    {
		Value value;
		// value_init_agg(&value, &CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]-1]);
		// CONTEXT->select_attr_num[CONTEXT->select_num]--;
		value_init_agg(&value, &CONTEXT->attrs[--CONTEXT->expression_attr_num]);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, (yyvsp[-2].string));
	}
#line 1872 "yacc_sql.tab.c"
    break;

  case 71: /* exp: exp ADD_T exp  */
#line 498 "yacc_sql.y"
                      { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, ADD); }
#line 1878 "yacc_sql.tab.c"
    break;

  case 72: /* exp: exp SUB_T exp  */
#line 499 "yacc_sql.y"
                        { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, SUB); }
#line 1884 "yacc_sql.tab.c"
    break;

  case 73: /* exp: exp STAR exp  */
#line 500 "yacc_sql.y"
                       { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, MUL); }
#line 1890 "yacc_sql.tab.c"
    break;

  case 74: /* exp: exp DIV_T exp  */
#line 501 "yacc_sql.y"
                        { (yyval.exp1) = create_expression((yyvsp[-2].exp1), (yyvsp[0].exp1), NULL, NULL, DIV); }
#line 1896 "yacc_sql.tab.c"
    break;

  case 75: /* exp: LBRACE exp RBRACE  */
#line 502 "yacc_sql.y"
                            { (yyval.exp1) = (yyvsp[-1].exp1); }
#line 1902 "yacc_sql.tab.c"
    break;

  case 76: /* exp: value  */
#line 503 "yacc_sql.y"
                { 
		(yyval.exp1) = create_expression(NULL, NULL, &CONTEXT->values[CONTEXT->value_length - 1], NULL, VAL); 
	}
#line 1910 "yacc_sql.tab.c"
    break;

  case 77: /* exp: ID alias_ID  */
#line 506 "yacc_sql.y"
                      { 
		RelAttr attr;
		relation_attr_init_with_alias(&attr, NULL, (yyvsp[-1].string), (yyvsp[0].string));
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
#line 1921 "yacc_sql.tab.c"
    break;

  case 78: /* exp: ID DOT ID alias_ID  */
#line 512 "yacc_sql.y"
                             {
		RelAttr attr;
		
		relation_attr_init_with_alias(&attr, (yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[0].string));
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &attr, ATTR);
	}
#line 1933 "yacc_sql.tab.c"
    break;

  case 79: /* exp: STAR alias_ID  */
#line 519 "yacc_sql.y"
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
#line 1950 "yacc_sql.tab.c"
    break;

  case 80: /* exp: ID DOT STAR alias_ID  */
#line 531 "yacc_sql.y"
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
#line 1967 "yacc_sql.tab.c"
    break;

  case 81: /* exp: agg  */
#line 543 "yacc_sql.y"
              {
		(yyval.exp1) = create_expression(NULL, NULL, NULL, &CONTEXT->attrs[CONTEXT->expression_attr_num - 1], ATTR);
	}
#line 1975 "yacc_sql.tab.c"
    break;

  case 82: /* select_begin: SELECT  */
#line 550 "yacc_sql.y"
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
#line 1991 "yacc_sql.tab.c"
    break;

  case 83: /* select_clause: select_begin select_attr FROM ID alias_ID rel_list where  */
#line 563 "yacc_sql.y"
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
#line 2029 "yacc_sql.tab.c"
    break;

  case 84: /* select_clause: select_begin select_attr FROM ID alias_ID INNER JOIN ID alias_ID ON condition condition_list join_list where  */
#line 596 "yacc_sql.y"
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
#line 2068 "yacc_sql.tab.c"
    break;

  case 85: /* select: select_clause SEMICOLON  */
#line 633 "yacc_sql.y"
                            {
		// 这里说明select是主语句
		CONTEXT->ssql->flag=SCF_SELECT;//"select";
		CONTEXT->ssql->sstr.selection = CONTEXT->selections[CONTEXT->select_num-1];
	}
#line 2078 "yacc_sql.tab.c"
    break;

  case 87: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 642 "yacc_sql.y"
        {
		selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-4].string));
	}
#line 2086 "yacc_sql.tab.c"
    break;

  case 88: /* agg_func: MAX_T  */
#line 648 "yacc_sql.y"
              { (yyval.number)=MAX; }
#line 2092 "yacc_sql.tab.c"
    break;

  case 89: /* agg_func: MIN_T  */
#line 649 "yacc_sql.y"
                { (yyval.number)=MIN; }
#line 2098 "yacc_sql.tab.c"
    break;

  case 90: /* agg_func: COUNT_T  */
#line 650 "yacc_sql.y"
                  { (yyval.number)=COUNT; }
#line 2104 "yacc_sql.tab.c"
    break;

  case 91: /* agg_func: AVG_T  */
#line 651 "yacc_sql.y"
                { (yyval.number)=AVG; }
#line 2110 "yacc_sql.tab.c"
    break;

  case 92: /* agg_func: SUM_T  */
#line 652 "yacc_sql.y"
                { (yyval.number)=SUM; }
#line 2116 "yacc_sql.tab.c"
    break;

  case 93: /* agg: agg_func LBRACE STAR RBRACE alias_ID  */
#line 657 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, "*", (yyvsp[-4].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2127 "yacc_sql.tab.c"
    break;

  case 94: /* agg: agg_func LBRACE ID RBRACE alias_ID  */
#line 663 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2138 "yacc_sql.tab.c"
    break;

  case 95: /* agg: agg_func LBRACE ID DOT ID RBRACE alias_ID  */
#line 669 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-6].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2149 "yacc_sql.tab.c"
    break;

  case 96: /* agg: agg_func LBRACE NUMBER RBRACE alias_ID  */
#line 675 "yacc_sql.y"
                                                 {
		RelAttr attr;
		relation_attr_init_with_agg_num(&attr, (yyvsp[-4].number), (yyvsp[-2].number), (yyvsp[0].string));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->expression_attr_num++] = attr;
	}
#line 2160 "yacc_sql.tab.c"
    break;

  case 97: /* agg: agg_func LBRACE STAR COMMA ID RBRACE alias_ID  */
#line 681 "yacc_sql.y"
                                                        {
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2170 "yacc_sql.tab.c"
    break;

  case 98: /* agg: agg_func LBRACE ID COMMA ID RBRACE alias_ID  */
#line 686 "yacc_sql.y"
                                                      {
		// 错误类型
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2181 "yacc_sql.tab.c"
    break;

  case 99: /* agg: agg_func LBRACE RBRACE alias_ID  */
#line 692 "yacc_sql.y"
                                          {
		// 错误类型
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturnlab;
	}
#line 2192 "yacc_sql.tab.c"
    break;

  case 100: /* select_attr: exp attr_list  */
#line 701 "yacc_sql.y"
                      {
		CONTEXT->expressions[CONTEXT->expr_num++] = (yyvsp[-1].exp1);
		CONTEXT->attr_num = CONTEXT->expression_attr_num;
	}
#line 2201 "yacc_sql.tab.c"
    break;

  case 102: /* attr_list: COMMA exp attr_list  */
#line 709 "yacc_sql.y"
                              {
		CONTEXT->expressions[CONTEXT->expr_num++] = (yyvsp[-1].exp1);
		// 因为现在条件语句中的RelAttr也会占用全局的attrs
		// 需要进行一下区别，attr_num只记录
		CONTEXT->attr_num = CONTEXT->expression_attr_num;
	}
#line 2212 "yacc_sql.tab.c"
    break;

  case 103: /* alias_ID: %empty  */
#line 719 "yacc_sql.y"
        { (yyval.string) = NULL; }
#line 2218 "yacc_sql.tab.c"
    break;

  case 104: /* alias_ID: ID  */
#line 720 "yacc_sql.y"
             { (yyval.string) = (yyvsp[0].string); }
#line 2224 "yacc_sql.tab.c"
    break;

  case 105: /* alias_ID: AS ID  */
#line 721 "yacc_sql.y"
                { (yyval.string) = (yyvsp[0].string); }
#line 2230 "yacc_sql.tab.c"
    break;

  case 107: /* rel_list: COMMA ID alias_ID rel_list  */
#line 726 "yacc_sql.y"
                                 {	
		selects_append_relation_with_alias(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-2].string), (yyvsp[-1].string));
	}
#line 2238 "yacc_sql.tab.c"
    break;

  case 109: /* where: WHERE condition condition_list  */
#line 732 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
	}
#line 2246 "yacc_sql.tab.c"
    break;

  case 111: /* condition_list: conjunction condition condition_list  */
#line 740 "yacc_sql.y"
                                           {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		
	}
#line 2255 "yacc_sql.tab.c"
    break;

  case 112: /* conjunction: AND  */
#line 747 "yacc_sql.y"
            { CONTEXT->selections[CONTEXT->select_num].is_and = 1; }
#line 2261 "yacc_sql.tab.c"
    break;

  case 113: /* conjunction: OR  */
#line 748 "yacc_sql.y"
              { CONTEXT->selections[CONTEXT->select_num].is_and = 0; }
#line 2267 "yacc_sql.tab.c"
    break;

  case 114: /* condition: exp comOp exp  */
#line 752 "yacc_sql.y"
                      {
		Exp *left_exp = (yyvsp[-2].exp1);
		Exp *right_exp = (yyvsp[0].exp1);
		Condition condition;
		condition_init_with_exp(&condition, (yyvsp[-1].number), left_exp, right_exp);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
#line 2280 "yacc_sql.tab.c"
    break;

  case 115: /* condition: LBRACE select_clause RBRACE comOp exp  */
#line 760 "yacc_sql.y"
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
#line 2296 "yacc_sql.tab.c"
    break;

  case 116: /* condition: exp comOp LBRACE select_clause RBRACE  */
#line 771 "yacc_sql.y"
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
#line 2312 "yacc_sql.tab.c"
    break;

  case 117: /* condition: comOp LBRACE select_clause RBRACE  */
#line 782 "yacc_sql.y"
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
#line 2330 "yacc_sql.tab.c"
    break;

  case 118: /* condition: LBRACE select_clause RBRACE comOp LBRACE select_clause RBRACE  */
#line 795 "yacc_sql.y"
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
#line 2346 "yacc_sql.tab.c"
    break;

  case 119: /* comOp: EQ  */
#line 809 "yacc_sql.y"
             { (yyval.number) = EQUAL_TO; }
#line 2352 "yacc_sql.tab.c"
    break;

  case 120: /* comOp: LT  */
#line 810 "yacc_sql.y"
         { (yyval.number) = LESS_THAN; }
#line 2358 "yacc_sql.tab.c"
    break;

  case 121: /* comOp: GT  */
#line 811 "yacc_sql.y"
         { (yyval.number) = GREAT_THAN; }
#line 2364 "yacc_sql.tab.c"
    break;

  case 122: /* comOp: LE  */
#line 812 "yacc_sql.y"
         { (yyval.number) = LESS_EQUAL; }
#line 2370 "yacc_sql.tab.c"
    break;

  case 123: /* comOp: GE  */
#line 813 "yacc_sql.y"
         { (yyval.number) = GREAT_EQUAL; }
#line 2376 "yacc_sql.tab.c"
    break;

  case 124: /* comOp: NE  */
#line 814 "yacc_sql.y"
         { (yyval.number) = NOT_EQUAL; }
#line 2382 "yacc_sql.tab.c"
    break;

  case 125: /* comOp: LIKE  */
#line 815 "yacc_sql.y"
               { (yyval.number) = LIKE_MATCH; }
#line 2388 "yacc_sql.tab.c"
    break;

  case 126: /* comOp: NOT LIKE  */
#line 816 "yacc_sql.y"
                   { (yyval.number) = NOT_LIKE; }
#line 2394 "yacc_sql.tab.c"
    break;

  case 127: /* comOp: IN  */
#line 817 "yacc_sql.y"
             { (yyval.number) = IN_OP; }
#line 2400 "yacc_sql.tab.c"
    break;

  case 128: /* comOp: NOT IN  */
#line 818 "yacc_sql.y"
                 { (yyval.number) = NOT_IN_OP; }
#line 2406 "yacc_sql.tab.c"
    break;

  case 129: /* comOp: EXIST  */
#line 819 "yacc_sql.y"
                { (yyval.number) =EXISTS_OP; }
#line 2412 "yacc_sql.tab.c"
    break;

  case 130: /* comOp: NOT EXIST  */
#line 820 "yacc_sql.y"
                    { (yyval.number) = NOT_EXISTS_OP; }
#line 2418 "yacc_sql.tab.c"
    break;

  case 131: /* comOp: IS  */
#line 821 "yacc_sql.y"
             { (yyval.number) = IS_OP; }
#line 2424 "yacc_sql.tab.c"
    break;

  case 132: /* comOp: IS NOT  */
#line 822 "yacc_sql.y"
                 { (yyval.number) = IS_NOT_OP; }
#line 2430 "yacc_sql.tab.c"
    break;

  case 133: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 827 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2439 "yacc_sql.tab.c"
    break;


#line 2443 "yacc_sql.tab.c"

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

#line 832 "yacc_sql.y"

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
