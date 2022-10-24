/* A Bison parser, made by GNU Bison 3.7.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.1"

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
  // 为了和主语句区分
//   size_t select_attr_num[MAX_NUM];
//   RelAttr select_attrs[MAX_NUM][MAX_NUM];
//   size_t select_cond_num[MAX_NUM];
//   Condition conditions[MAX_NUM][MAX_NUM];


  // size_t 
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  size_t cursor;
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


#line 149 "yacc_sql.tab.c"

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
  YYSYMBOL_SET = 38,                       /* SET  */
  YYSYMBOL_ON = 39,                        /* ON  */
  YYSYMBOL_IN = 40,                        /* IN  */
  YYSYMBOL_NOT = 41,                       /* NOT  */
  YYSYMBOL_EXIST = 42,                     /* EXIST  */
  YYSYMBOL_INNER = 43,                     /* INNER  */
  YYSYMBOL_JOIN = 44,                      /* JOIN  */
  YYSYMBOL_LOAD = 45,                      /* LOAD  */
  YYSYMBOL_DATA = 46,                      /* DATA  */
  YYSYMBOL_INFILE = 47,                    /* INFILE  */
  YYSYMBOL_MAX_T = 48,                     /* MAX_T  */
  YYSYMBOL_MIN_T = 49,                     /* MIN_T  */
  YYSYMBOL_COUNT_T = 50,                   /* COUNT_T  */
  YYSYMBOL_AVG_T = 51,                     /* AVG_T  */
  YYSYMBOL_SUM_T = 52,                     /* SUM_T  */
  YYSYMBOL_LIKE = 53,                      /* LIKE  */
  YYSYMBOL_EQ = 54,                        /* EQ  */
  YYSYMBOL_LT = 55,                        /* LT  */
  YYSYMBOL_GT = 56,                        /* GT  */
  YYSYMBOL_LE = 57,                        /* LE  */
  YYSYMBOL_GE = 58,                        /* GE  */
  YYSYMBOL_NE = 59,                        /* NE  */
  YYSYMBOL_NUMBER = 60,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 61,                     /* FLOAT  */
  YYSYMBOL_DATE = 62,                      /* DATE  */
  YYSYMBOL_TEXT = 63,                      /* TEXT  */
  YYSYMBOL_ID = 64,                        /* ID  */
  YYSYMBOL_PATH = 65,                      /* PATH  */
  YYSYMBOL_SSS = 66,                       /* SSS  */
  YYSYMBOL_STAR = 67,                      /* STAR  */
  YYSYMBOL_STRING_V = 68,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 69,                  /* $accept  */
  YYSYMBOL_commands = 70,                  /* commands  */
  YYSYMBOL_command = 71,                   /* command  */
  YYSYMBOL_exit = 72,                      /* exit  */
  YYSYMBOL_help = 73,                      /* help  */
  YYSYMBOL_sync = 74,                      /* sync  */
  YYSYMBOL_begin = 75,                     /* begin  */
  YYSYMBOL_commit = 76,                    /* commit  */
  YYSYMBOL_rollback = 77,                  /* rollback  */
  YYSYMBOL_drop_table = 78,                /* drop_table  */
  YYSYMBOL_show_tables = 79,               /* show_tables  */
  YYSYMBOL_desc_table = 80,                /* desc_table  */
  YYSYMBOL_create_index = 81,              /* create_index  */
  YYSYMBOL_attr_name_list = 82,            /* attr_name_list  */
  YYSYMBOL_attr_name = 83,                 /* attr_name  */
  YYSYMBOL_drop_index = 84,                /* drop_index  */
  YYSYMBOL_show_index = 85,                /* show_index  */
  YYSYMBOL_create_table = 86,              /* create_table  */
  YYSYMBOL_attr_def_list = 87,             /* attr_def_list  */
  YYSYMBOL_attr_def = 88,                  /* attr_def  */
  YYSYMBOL_number = 89,                    /* number  */
  YYSYMBOL_type = 90,                      /* type  */
  YYSYMBOL_ID_get = 91,                    /* ID_get  */
  YYSYMBOL_insert = 92,                    /* insert  */
  YYSYMBOL_tuple_list = 93,                /* tuple_list  */
  YYSYMBOL_tuple = 94,                     /* tuple  */
  YYSYMBOL_value_list = 95,                /* value_list  */
  YYSYMBOL_value = 96,                     /* value  */
  YYSYMBOL_delete = 97,                    /* delete  */
  YYSYMBOL_updates = 98,                   /* updates  */
  YYSYMBOL_modify_list = 99,               /* modify_list  */
  YYSYMBOL_modify_expr = 100,              /* modify_expr  */
  YYSYMBOL_select_clause = 101,            /* select_clause  */
  YYSYMBOL_select = 102,                   /* select  */
  YYSYMBOL_join_list = 103,                /* join_list  */
  YYSYMBOL_agg_func = 104,                 /* agg_func  */
  YYSYMBOL_agg = 105,                      /* agg  */
  YYSYMBOL_select_attr = 106,              /* select_attr  */
  YYSYMBOL_attr_list = 107,                /* attr_list  */
  YYSYMBOL_rel_list = 108,                 /* rel_list  */
  YYSYMBOL_where = 109,                    /* where  */
  YYSYMBOL_condition_list = 110,           /* condition_list  */
  YYSYMBOL_condition = 111,                /* condition  */
  YYSYMBOL_comOp = 112,                    /* comOp  */
  YYSYMBOL_load_data = 113                 /* load_data  */
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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYLAST   238

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  240

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   323


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
      65,    66,    67,    68
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   173,   173,   175,   179,   180,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   201,   206,   211,   217,   223,   229,   235,   241,
     247,   254,   260,   269,   270,   275,   280,   288,   295,   304,
     306,   310,   321,   334,   337,   338,   339,   340,   341,   344,
     353,   371,   372,   378,   384,   386,   391,   394,   397,   406,
     413,   434,   441,   442,   448,   451,   456,   467,   490,   516,
     523,   524,   531,   532,   533,   534,   535,   540,   546,   552,
     558,   567,   573,   579,   585,   590,   592,   600,   608,   613,
     615,   619,   621,   625,   627,   632,   652,   672,   692,   714,
     735,   756,   778,   779,   780,   781,   782,   783,   784,   785,
     786,   787,   792
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
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "IN",
  "NOT", "EXIST", "INNER", "JOIN", "LOAD", "DATA", "INFILE", "MAX_T",
  "MIN_T", "COUNT_T", "AVG_T", "SUM_T", "LIKE", "EQ", "LT", "GT", "LE",
  "GE", "NE", "NUMBER", "FLOAT", "DATE", "TEXT", "ID", "PATH", "SSS",
  "STAR", "STRING_V", "$accept", "commands", "command", "exit", "help",
  "sync", "begin", "commit", "rollback", "drop_table", "show_tables",
  "desc_table", "create_index", "attr_name_list", "attr_name",
  "drop_index", "show_index", "create_table", "attr_def_list", "attr_def",
  "number", "type", "ID_get", "insert", "tuple_list", "tuple",
  "value_list", "value", "delete", "updates", "modify_list", "modify_expr",
  "select_clause", "select", "join_list", "agg_func", "agg", "select_attr",
  "attr_list", "rel_list", "where", "condition_list", "condition", "comOp",
  "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
#endif

#define YYPACT_NINF (-187)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -187,    68,  -187,   102,    88,     7,   -44,   141,    20,    36,
      35,    12,    92,    97,   103,   118,   122,    81,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -187,  -187,   129,  -187,  -187,    70,    75,
     133,    86,    87,  -187,  -187,  -187,  -187,  -187,   -10,   134,
     135,  -187,   119,   152,   153,   123,  -187,    93,    95,   124,
    -187,  -187,  -187,  -187,  -187,   113,  -187,   144,   125,    99,
     162,   163,   -33,   104,  -187,  -187,     0,   105,  -187,  -187,
     106,   137,   131,   108,   107,   110,   111,   138,  -187,  -187,
      34,   134,   134,   158,     3,   160,    -9,   176,   164,    43,
     177,   128,   165,   150,  -187,   166,   120,   169,   126,   127,
    -187,  -187,  -187,  -187,  -187,   130,  -187,   132,   143,   131,
    -187,    25,   170,  -187,  -187,  -187,    61,  -187,   -29,   151,
    -187,   -12,   108,   131,   186,   110,   175,  -187,  -187,  -187,
    -187,  -187,   178,   136,   180,   134,   181,   179,   139,  -187,
     182,   164,   199,   140,  -187,    22,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,    62,    69,    43,  -187,   195,  -187,  -187,
     165,   203,   145,   166,   204,   148,  -187,   191,   136,  -187,
    -187,  -187,   172,    25,   194,   170,  -187,   -29,  -187,  -187,
    -187,  -187,   183,  -187,   151,   196,  -187,  -187,   210,  -187,
    -187,  -187,   198,   136,   200,   191,    43,   182,  -187,  -187,
      76,   155,  -187,  -187,  -187,  -187,   191,   214,   202,   151,
    -187,   189,  -187,  -187,  -187,  -187,   219,   184,   159,  -187,
     185,   131,  -187,   161,  -187,   187,    43,   151,   184,  -187
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     0,     4,    19,     0,     0,
       0,     0,     0,    72,    73,    74,    75,    76,    85,    85,
       0,    84,     0,     0,     0,     0,    24,     0,     0,     0,
      25,    26,    27,    23,    22,     0,    69,     0,     0,     0,
       0,     0,     0,     0,    82,    81,     0,     0,    30,    29,
       0,     0,    91,     0,     0,     0,     0,     0,    28,    36,
      85,    85,    85,     0,     0,     0,    89,     0,     0,     0,
       0,     0,    62,     0,    49,    39,     0,     0,     0,     0,
      86,    88,    83,    80,    78,     0,    77,     0,     0,    91,
      37,     0,    51,    56,    57,    58,     0,    59,     0,    93,
      60,     0,     0,    91,     0,     0,     0,    44,    45,    46,
      47,    48,    42,     0,     0,    85,     0,    89,     0,    67,
      54,     0,     0,     0,   110,     0,   108,   102,   103,   104,
     105,   106,   107,     0,     0,     0,    92,     0,    64,    66,
      62,     0,     0,    39,     0,     0,    35,    33,     0,    87,
      79,    90,     0,     0,     0,    51,    50,     0,   111,   109,
      97,    95,    98,    96,    93,     0,    63,    61,     0,    40,
      38,    43,     0,     0,     0,    33,     0,    54,    53,    52,
       0,     0,    94,    65,   112,    41,    33,     0,     0,    93,
      55,     0,    99,   100,    34,    31,     0,    70,     0,    32,
       0,    91,   101,     0,    68,     0,     0,    93,    70,    71
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,  -187,
    -187,  -187,  -187,  -164,  -171,  -187,  -187,  -187,    51,    96,
    -187,  -187,  -187,  -187,    45,    77,    26,  -118,  -187,  -187,
      64,   100,    71,  -187,    -3,  -187,   -70,  -187,   -48,    89,
    -119,  -186,  -159,  -124,  -187
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   204,   177,    29,    30,    31,   136,   105,
     202,   142,   106,    32,   152,   122,   184,   128,    33,    34,
     133,   102,    35,    36,   231,    50,    51,    52,    74,   119,
     100,   166,   129,   163,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     149,    75,    91,   150,   164,   167,   194,   205,   212,    72,
     117,   154,   155,   168,   171,    43,    44,    45,    46,    47,
      53,   114,    73,    56,   156,   157,   158,   159,   160,   161,
     162,    90,   216,   227,   118,   115,    43,    44,    45,    46,
      47,   218,   110,   111,   112,   191,   193,   219,   123,   124,
     125,   238,   224,    72,   127,    43,    44,    45,    46,    47,
      93,   169,   188,   210,    94,   207,   109,    95,     2,    57,
      58,    48,     3,     4,    49,   189,    59,   237,     5,     6,
       7,     8,     9,    10,    11,   123,   124,   125,    12,    13,
      14,   127,   222,   153,    41,    60,    42,   179,    15,    16,
      61,   154,   155,   123,   124,   125,    62,   126,    38,   127,
      39,    40,   234,    17,   156,   157,   158,   159,   160,   161,
     162,    63,   123,   124,   125,    64,   190,    65,   127,   123,
     124,   125,    66,   192,    67,   127,   123,   124,   125,    68,
     221,    69,   127,   137,   138,   139,   140,   141,    54,    55,
      70,    71,    76,    72,    77,    78,    79,    81,    80,    82,
      84,    85,    83,    87,    86,    88,    89,    99,    92,    96,
      97,    98,   101,   103,   104,   107,   113,   108,   116,   120,
     130,   121,   131,   134,   132,   135,   143,   148,   165,   151,
     144,   145,   172,   174,   146,   175,   147,   178,   117,   180,
     176,   183,   186,   182,   187,     5,   197,   200,   201,   198,
     203,   206,   208,   214,   213,   211,   215,   225,   217,   223,
     226,   228,   229,   232,   199,   235,   236,   230,   185,   233,
     209,   173,   170,   220,   196,   239,   181,     0,   195
};

static const yytype_int16 yycheck[] =
{
     119,    49,    72,   121,   128,    17,   165,   178,   194,    19,
      19,    40,    41,   131,   133,    48,    49,    50,    51,    52,
      64,    18,    32,     3,    53,    54,    55,    56,    57,    58,
      59,    64,   203,   219,    43,    32,    48,    49,    50,    51,
      52,   205,    90,    91,    92,   163,   164,   206,    60,    61,
      62,   237,   216,    19,    66,    48,    49,    50,    51,    52,
      60,   131,    40,   187,    64,   183,    32,    67,     0,    33,
      35,    64,     4,     5,    67,    53,    64,   236,    10,    11,
      12,    13,    14,    15,    16,    60,    61,    62,    20,    21,
      22,    66,   210,    32,     6,     3,     8,   145,    30,    31,
       3,    40,    41,    60,    61,    62,     3,    64,     6,    66,
       8,     9,   231,    45,    53,    54,    55,    56,    57,    58,
      59,     3,    60,    61,    62,     3,    64,    46,    66,    60,
      61,    62,     3,    64,    64,    66,    60,    61,    62,    64,
      64,     8,    66,    23,    24,    25,    26,    27,     7,     8,
      64,    64,    17,    19,    35,     3,     3,    64,    35,    64,
      47,    17,    38,    64,    39,     3,     3,    36,    64,    64,
      64,    34,    64,    66,    64,    64,    18,    39,    18,     3,
       3,    17,    54,    33,    19,    19,    17,    44,    37,    19,
      64,    64,     6,    18,    64,    17,    64,    17,    19,    18,
      64,    19,     3,    64,    64,    10,     3,     3,    60,    64,
      19,    39,    18,     3,    18,    32,    18,     3,    18,    64,
      18,    32,     3,    64,   173,    64,    39,    43,   151,    44,
     185,   135,   132,   207,   170,   238,   147,    -1,   167
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    70,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    30,    31,    45,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    84,
      85,    86,    92,    97,    98,   101,   102,   113,     6,     8,
       9,     6,     8,    48,    49,    50,    51,    52,    64,    67,
     104,   105,   106,    64,     7,     8,     3,    33,    35,    64,
       3,     3,     3,     3,     3,    46,     3,    64,    64,     8,
      64,    64,    19,    32,   107,   107,    17,    35,     3,     3,
      35,    64,    64,    38,    47,    17,    39,    64,     3,     3,
      64,   105,    64,    60,    64,    67,    64,    64,    34,    36,
     109,    64,   100,    66,    64,    88,    91,    64,    39,    32,
     107,   107,   107,    18,    18,    32,    18,    19,    43,   108,
       3,    17,    94,    60,    61,    62,    64,    66,    96,   111,
       3,    54,    19,    99,    33,    19,    87,    23,    24,    25,
      26,    27,    90,    17,    64,    64,    64,    64,    44,   109,
      96,    19,    93,    32,    40,    41,    53,    54,    55,    56,
      57,    58,    59,   112,   112,    37,   110,    17,    96,   105,
     100,   109,     6,    88,    18,    17,    64,    83,    17,   107,
      18,   108,    64,    19,    95,    94,     3,    64,    40,    53,
      64,    96,    64,    96,   111,   101,    99,     3,    64,    87,
       3,    60,    89,    19,    82,    83,    39,    96,    18,    93,
     112,    32,   110,    18,     3,    18,    83,    18,    82,   111,
      95,    64,    96,    64,    82,     3,    18,   110,    32,     3,
      43,   103,    64,    44,   109,    64,    39,   111,   110,   103
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    81,    82,    82,    83,    84,    85,    86,    87,
      87,    88,    88,    89,    90,    90,    90,    90,    90,    91,
      92,    93,    93,    94,    95,    95,    96,    96,    96,    96,
      97,    98,    99,    99,   100,   100,   100,   101,   101,   102,
     103,   103,   104,   104,   104,   104,   104,   105,   105,   105,
     105,   106,   106,   106,   106,   107,   107,   107,   107,   108,
     108,   109,   109,   110,   110,   111,   111,   111,   111,   111,
     111,   111,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   113
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,    10,    11,     0,     3,     1,     4,     5,     8,     0,
       3,     5,     2,     1,     1,     1,     1,     1,     1,     1,
       7,     0,     3,     4,     0,     3,     1,     1,     1,     1,
       5,     7,     0,     3,     3,     5,     3,     6,    12,     2,
       0,     7,     1,     1,     1,     1,     1,     4,     4,     6,
       4,     2,     2,     4,     1,     0,     3,     5,     3,     0,
       3,     0,     3,     0,     3,     3,     3,     3,     3,     5,
       5,     7,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
#line 201 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1425 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 206 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1433 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 211 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1441 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 217 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1449 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 223 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1457 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 229 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1465 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 235 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1474 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 241 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1482 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 247 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1491 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON  */
#line 255 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			
		}
#line 1501 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON  */
#line 261 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $8);
		}
#line 1511 "yacc_sql.tab.c"
    break;

  case 34: /* attr_name_list: COMMA attr_name attr_name_list  */
#line 270 "yacc_sql.y"
                                         {

	}
#line 1519 "yacc_sql.tab.c"
    break;

  case 35: /* attr_name: ID  */
#line 275 "yacc_sql.y"
              {
	create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $2);
}
#line 1528 "yacc_sql.tab.c"
    break;

  case 36: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 281 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1537 "yacc_sql.tab.c"
    break;

  case 37: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 288 "yacc_sql.y"
                                    {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1546 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 296 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1558 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 306 "yacc_sql.y"
                                   {    }
#line 1564 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 311 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1579 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type  */
#line 322 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1594 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 334 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1600 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 337 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1606 "yacc_sql.tab.c"
    break;

  case 45: /* type: STRING_T  */
#line 338 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1612 "yacc_sql.tab.c"
    break;

  case 46: /* type: FLOAT_T  */
#line 339 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1618 "yacc_sql.tab.c"
    break;

  case 47: /* type: DATE_T  */
#line 340 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1624 "yacc_sql.tab.c"
    break;

  case 48: /* type: TEXT_T  */
#line 341 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1630 "yacc_sql.tab.c"
    break;

  case 49: /* ID_get: ID  */
#line 345 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1639 "yacc_sql.tab.c"
    break;

  case 50: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 354 "yacc_sql.y"
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
#line 1659 "yacc_sql.tab.c"
    break;

  case 52: /* tuple_list: COMMA tuple tuple_list  */
#line 372 "yacc_sql.y"
                                 {
	}
#line 1666 "yacc_sql.tab.c"
    break;

  case 53: /* tuple: LBRACE value value_list RBRACE  */
#line 378 "yacc_sql.y"
                                       {
		insert_init(&CONTEXT->insert_list[CONTEXT->insert_num++], CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1675 "yacc_sql.tab.c"
    break;

  case 55: /* value_list: COMMA value value_list  */
#line 386 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1683 "yacc_sql.tab.c"
    break;

  case 56: /* value: NUMBER  */
#line 391 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1691 "yacc_sql.tab.c"
    break;

  case 57: /* value: FLOAT  */
#line 394 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1699 "yacc_sql.tab.c"
    break;

  case 58: /* value: DATE  */
#line 397 "yacc_sql.y"
             {
		(yyvsp[0].string) = substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);
		int res = value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		if (res != 0) {
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			yyresult = 2;
			goto yyreturn;
		}
	}
#line 1713 "yacc_sql.tab.c"
    break;

  case 59: /* value: SSS  */
#line 406 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1722 "yacc_sql.tab.c"
    break;

  case 60: /* delete: DELETE FROM ID where SEMICOLON  */
#line 414 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1734 "yacc_sql.tab.c"
    break;

  case 61: /* updates: UPDATE ID SET modify_expr modify_list where SEMICOLON  */
#line 434 "yacc_sql.y"
                                                              {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		updates_select_init(&CONTEXT->ssql->sstr.updates, (yyvsp[-5].string), CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
	}
#line 1744 "yacc_sql.tab.c"
    break;

  case 63: /* modify_list: COMMA modify_expr modify_list  */
#line 442 "yacc_sql.y"
                                        {

	}
#line 1752 "yacc_sql.tab.c"
    break;

  case 64: /* modify_expr: ID EQ value  */
#line 448 "yacc_sql.y"
                    {
		updates_append_value(&CONTEXT->ssql->sstr.updates, &CONTEXT->values[CONTEXT->value_length - 1], (yyvsp[-2].string));
	}
#line 1760 "yacc_sql.tab.c"
    break;

  case 65: /* modify_expr: ID EQ LBRACE select_clause RBRACE  */
#line 451 "yacc_sql.y"
                                           {
		Value value;
		value_init_select(&value, &CONTEXT->ssql->sstr.selection);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, (yyvsp[-4].string));
	}
#line 1770 "yacc_sql.tab.c"
    break;

  case 66: /* modify_expr: ID EQ agg  */
#line 456 "yacc_sql.y"
                    {
		Value value;
		// value_init_agg(&value, &CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]-1]);
		// CONTEXT->select_attr_num[CONTEXT->select_num]--;
		value_init_agg(&value, &CONTEXT->attrs[--CONTEXT->attr_num]);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, (yyvsp[-2].string));
	}
#line 1782 "yacc_sql.tab.c"
    break;

  case 67: /* select_clause: SELECT select_attr FROM ID rel_list where  */
#line 467 "yacc_sql.y"
                                                  {
		// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
		selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-2].string));

		selects_append_conditions(&CONTEXT->selections[CONTEXT->select_num], CONTEXT->conditions, CONTEXT->condition_length);
		selects_append_attribute_list(&CONTEXT->selections[CONTEXT->select_num], 
									  &CONTEXT->attrs,
									  CONTEXT->attr_num);
									//   CONTEXT->select_attrs[CONTEXT->select_num], 
									//   CONTEXT->select_attr_num[CONTEXT->select_num]);

		

		// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;
		//临时变量清零
		CONTEXT->condition_length=0;
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		CONTEXT->value_length = 0;
		CONTEXT->attr_num = 0;
		// CONTEXT->select_attr_num[CONTEXT->select_num] = 0;
		++CONTEXT->select_num;
	}
#line 1810 "yacc_sql.tab.c"
    break;

  case 68: /* select_clause: SELECT select_attr FROM ID INNER JOIN ID ON condition condition_list join_list where  */
#line 490 "yacc_sql.y"
                                                                                               {
		// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
		selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-5].string));
		selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-8].string));

		selects_append_conditions(&CONTEXT->selections[CONTEXT->select_num], CONTEXT->conditions, CONTEXT->condition_length);

		selects_append_attribute_list(&CONTEXT->selections[CONTEXT->select_num], 
									  &CONTEXT->attrs,
									  CONTEXT->attr_num);
									//   CONTEXT->select_attrs[CONTEXT->select_num], 
									//   CONTEXT->select_attr_num[CONTEXT->select_num]);
		// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

		//临时变量清零
		CONTEXT->condition_length=0;
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		CONTEXT->value_length = 0;
		CONTEXT->attr_num = 0;
		// CONTEXT->select_attr_num[CONTEXT->select_num] = 0;
		++CONTEXT->select_num;
	}
#line 1838 "yacc_sql.tab.c"
    break;

  case 69: /* select: select_clause SEMICOLON  */
#line 516 "yacc_sql.y"
                            {
		// 这里说明select是主语句
		CONTEXT->ssql->flag=SCF_SELECT;//"select";
		CONTEXT->ssql->sstr.selection = CONTEXT->selections[CONTEXT->select_num-1];
	}
#line 1848 "yacc_sql.tab.c"
    break;

  case 71: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 525 "yacc_sql.y"
        {
		selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-4].string));
	}
#line 1856 "yacc_sql.tab.c"
    break;

  case 72: /* agg_func: MAX_T  */
#line 531 "yacc_sql.y"
              { (yyval.number)=MAX; }
#line 1862 "yacc_sql.tab.c"
    break;

  case 73: /* agg_func: MIN_T  */
#line 532 "yacc_sql.y"
                { (yyval.number)=SUM; }
#line 1868 "yacc_sql.tab.c"
    break;

  case 74: /* agg_func: COUNT_T  */
#line 533 "yacc_sql.y"
                  { (yyval.number)=COUNT; }
#line 1874 "yacc_sql.tab.c"
    break;

  case 75: /* agg_func: AVG_T  */
#line 534 "yacc_sql.y"
                { (yyval.number)=AVG; }
#line 1880 "yacc_sql.tab.c"
    break;

  case 76: /* agg_func: SUM_T  */
#line 535 "yacc_sql.y"
                { (yyval.number)=SUM; }
#line 1886 "yacc_sql.tab.c"
    break;

  case 77: /* agg: agg_func LBRACE STAR RBRACE  */
#line 540 "yacc_sql.y"
                                    {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, "*", (yyvsp[-3].number));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->attr_num++] = attr;
	}
#line 1897 "yacc_sql.tab.c"
    break;

  case 78: /* agg: agg_func LBRACE ID RBRACE  */
#line 546 "yacc_sql.y"
                                    {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, (yyvsp[-1].string), (yyvsp[-3].number));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->attr_num++] = attr;
	}
#line 1908 "yacc_sql.tab.c"
    break;

  case 79: /* agg: agg_func LBRACE ID DOT ID RBRACE  */
#line 552 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, (yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[-5].number));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->attr_num++] = attr;
	}
#line 1919 "yacc_sql.tab.c"
    break;

  case 80: /* agg: agg_func LBRACE NUMBER RBRACE  */
#line 558 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init_with_agg_num(&attr, (yyvsp[-3].number), (yyvsp[-1].number));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->attr_num++] = attr;
	}
#line 1930 "yacc_sql.tab.c"
    break;

  case 81: /* select_attr: STAR attr_list  */
#line 567 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
			CONTEXT->attrs[CONTEXT->attr_num++] = attr;
		}
#line 1941 "yacc_sql.tab.c"
    break;

  case 82: /* select_attr: ID attr_list  */
#line 573 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
			CONTEXT->attrs[CONTEXT->attr_num++] = attr;
		}
#line 1952 "yacc_sql.tab.c"
    break;

  case 83: /* select_attr: ID DOT ID attr_list  */
#line 579 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
			CONTEXT->attrs[CONTEXT->attr_num++] = attr;
		}
#line 1963 "yacc_sql.tab.c"
    break;

  case 84: /* select_attr: agg  */
#line 585 "yacc_sql.y"
              {

	}
#line 1971 "yacc_sql.tab.c"
    break;

  case 86: /* attr_list: COMMA ID attr_list  */
#line 592 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
			CONTEXT->attrs[CONTEXT->attr_num++] = attr;
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1984 "yacc_sql.tab.c"
    break;

  case 87: /* attr_list: COMMA ID DOT ID attr_list  */
#line 600 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
			CONTEXT->attrs[CONTEXT->attr_num++] = attr;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1997 "yacc_sql.tab.c"
    break;

  case 88: /* attr_list: COMMA agg attr_list  */
#line 608 "yacc_sql.y"
                              {

	}
#line 2005 "yacc_sql.tab.c"
    break;

  case 90: /* rel_list: COMMA ID rel_list  */
#line 615 "yacc_sql.y"
                        {	
		selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-1].string));
	}
#line 2013 "yacc_sql.tab.c"
    break;

  case 92: /* where: WHERE condition condition_list  */
#line 621 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2021 "yacc_sql.tab.c"
    break;

  case 94: /* condition_list: AND condition condition_list  */
#line 627 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2029 "yacc_sql.tab.c"
    break;

  case 95: /* condition: ID comOp value  */
#line 633 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2053 "yacc_sql.tab.c"
    break;

  case 96: /* condition: value comOp value  */
#line 653 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2077 "yacc_sql.tab.c"
    break;

  case 97: /* condition: ID comOp ID  */
#line 673 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2101 "yacc_sql.tab.c"
    break;

  case 98: /* condition: value comOp ID  */
#line 693 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 2127 "yacc_sql.tab.c"
    break;

  case 99: /* condition: ID DOT ID comOp value  */
#line 715 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 2152 "yacc_sql.tab.c"
    break;

  case 100: /* condition: value comOp ID DOT ID  */
#line 736 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 2177 "yacc_sql.tab.c"
    break;

  case 101: /* condition: ID DOT ID comOp ID DOT ID  */
#line 757 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2200 "yacc_sql.tab.c"
    break;

  case 102: /* comOp: EQ  */
#line 778 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2206 "yacc_sql.tab.c"
    break;

  case 103: /* comOp: LT  */
#line 779 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2212 "yacc_sql.tab.c"
    break;

  case 104: /* comOp: GT  */
#line 780 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2218 "yacc_sql.tab.c"
    break;

  case 105: /* comOp: LE  */
#line 781 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2224 "yacc_sql.tab.c"
    break;

  case 106: /* comOp: GE  */
#line 782 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2230 "yacc_sql.tab.c"
    break;

  case 107: /* comOp: NE  */
#line 783 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2236 "yacc_sql.tab.c"
    break;

  case 108: /* comOp: LIKE  */
#line 784 "yacc_sql.y"
               { CONTEXT->comp = LIKE_MATCH; }
#line 2242 "yacc_sql.tab.c"
    break;

  case 109: /* comOp: NOT LIKE  */
#line 785 "yacc_sql.y"
                   { CONTEXT->comp = NOT_LIKE; }
#line 2248 "yacc_sql.tab.c"
    break;

  case 110: /* comOp: IN  */
#line 786 "yacc_sql.y"
             { CONTEXT->comp = IN_OP; }
#line 2254 "yacc_sql.tab.c"
    break;

  case 111: /* comOp: NOT IN  */
#line 787 "yacc_sql.y"
                 { CONTEXT->comp = NOT_IN_OP; }
#line 2260 "yacc_sql.tab.c"
    break;

  case 112: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 793 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2269 "yacc_sql.tab.c"
    break;


#line 2273 "yacc_sql.tab.c"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

#line 798 "yacc_sql.y"

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
