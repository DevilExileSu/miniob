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
  size_t depth;
  // 为了和主语句区分
//   size_t select_attr_num[MAX_NUM];
//   RelAttr select_attrs[MAX_NUM][MAX_NUM];
//   size_t select_cond_num[MAX_NUM];
//   Condition conditions[MAX_NUM][MAX_NUM];


  // size_t 
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  size_t cursor_attr[MAX_NUM];
  size_t cursor_cond[MAX_NUM];
  size_t cursor_value[MAX_NUM];
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
  YYSYMBOL_NUMBER = 63,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 64,                     /* FLOAT  */
  YYSYMBOL_DATE = 65,                      /* DATE  */
  YYSYMBOL_TEXT = 66,                      /* TEXT  */
  YYSYMBOL_ID = 67,                        /* ID  */
  YYSYMBOL_PATH = 68,                      /* PATH  */
  YYSYMBOL_SSS = 69,                       /* SSS  */
  YYSYMBOL_STAR = 70,                      /* STAR  */
  YYSYMBOL_STRING_V = 71,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 72,                  /* $accept  */
  YYSYMBOL_commands = 73,                  /* commands  */
  YYSYMBOL_command = 74,                   /* command  */
  YYSYMBOL_exit = 75,                      /* exit  */
  YYSYMBOL_help = 76,                      /* help  */
  YYSYMBOL_sync = 77,                      /* sync  */
  YYSYMBOL_begin = 78,                     /* begin  */
  YYSYMBOL_commit = 79,                    /* commit  */
  YYSYMBOL_rollback = 80,                  /* rollback  */
  YYSYMBOL_drop_table = 81,                /* drop_table  */
  YYSYMBOL_show_tables = 82,               /* show_tables  */
  YYSYMBOL_desc_table = 83,                /* desc_table  */
  YYSYMBOL_create_index = 84,              /* create_index  */
  YYSYMBOL_attr_name_list = 85,            /* attr_name_list  */
  YYSYMBOL_attr_name = 86,                 /* attr_name  */
  YYSYMBOL_drop_index = 87,                /* drop_index  */
  YYSYMBOL_show_index = 88,                /* show_index  */
  YYSYMBOL_create_table = 89,              /* create_table  */
  YYSYMBOL_attr_def_list = 90,             /* attr_def_list  */
  YYSYMBOL_attr_def = 91,                  /* attr_def  */
  YYSYMBOL_nullable = 92,                  /* nullable  */
  YYSYMBOL_number = 93,                    /* number  */
  YYSYMBOL_type = 94,                      /* type  */
  YYSYMBOL_ID_get = 95,                    /* ID_get  */
  YYSYMBOL_insert = 96,                    /* insert  */
  YYSYMBOL_tuple_list = 97,                /* tuple_list  */
  YYSYMBOL_tuple = 98,                     /* tuple  */
  YYSYMBOL_value_list = 99,                /* value_list  */
  YYSYMBOL_value = 100,                    /* value  */
  YYSYMBOL_delete = 101,                   /* delete  */
  YYSYMBOL_updates = 102,                  /* updates  */
  YYSYMBOL_modify_list = 103,              /* modify_list  */
  YYSYMBOL_modify_expr = 104,              /* modify_expr  */
  YYSYMBOL_select_begin = 105,             /* select_begin  */
  YYSYMBOL_select_clause = 106,            /* select_clause  */
  YYSYMBOL_select = 107,                   /* select  */
  YYSYMBOL_join_list = 108,                /* join_list  */
  YYSYMBOL_agg_func = 109,                 /* agg_func  */
  YYSYMBOL_agg = 110,                      /* agg  */
  YYSYMBOL_select_attr = 111,              /* select_attr  */
  YYSYMBOL_attr_list = 112,                /* attr_list  */
  YYSYMBOL_alias_ID = 113,                 /* alias_ID  */
  YYSYMBOL_rel_list = 114,                 /* rel_list  */
  YYSYMBOL_where = 115,                    /* where  */
  YYSYMBOL_condition_list = 116,           /* condition_list  */
  YYSYMBOL_condition = 117,                /* condition  */
  YYSYMBOL_comOp = 118,                    /* comOp  */
  YYSYMBOL_load_data = 119                 /* load_data  */
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
#define YYLAST   297

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  132
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  285

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   326


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
      65,    66,    67,    68,    69,    70,    71
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   180,   180,   182,   186,   187,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   208,   213,   218,   224,   230,   236,   242,   248,
     254,   261,   267,   276,   277,   282,   287,   295,   302,   311,
     313,   317,   328,   342,   343,   344,   348,   351,   352,   353,
     354,   355,   358,   367,   385,   386,   392,   398,   400,   405,
     408,   411,   420,   424,   430,   451,   460,   461,   467,   470,
     475,   485,   494,   522,   551,   558,   559,   566,   567,   568,
     569,   570,   575,   581,   587,   593,   599,   604,   610,   619,
     625,   631,   637,   643,   645,   653,   661,   668,   669,   670,
     673,   675,   679,   681,   685,   687,   690,   695,   715,   735,
     755,   776,   796,   817,   836,   850,   861,   874,   888,   889,
     890,   891,   892,   893,   894,   895,   896,   897,   898,   899,
     900,   901,   905
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
  "LE", "GE", "NE", "NUMBER", "FLOAT", "DATE", "TEXT", "ID", "PATH", "SSS",
  "STAR", "STRING_V", "$accept", "commands", "command", "exit", "help",
  "sync", "begin", "commit", "rollback", "drop_table", "show_tables",
  "desc_table", "create_index", "attr_name_list", "attr_name",
  "drop_index", "show_index", "create_table", "attr_def_list", "attr_def",
  "nullable", "number", "type", "ID_get", "insert", "tuple_list", "tuple",
  "value_list", "value", "delete", "updates", "modify_list", "modify_expr",
  "select_begin", "select_clause", "select", "join_list", "agg_func",
  "agg", "select_attr", "attr_list", "alias_ID", "rel_list", "where",
  "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326
};
#endif

#define YYPACT_NINF (-209)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -209,   121,  -209,   106,    18,  -209,   -46,    53,    27,    -5,
      -3,   -24,    69,    82,    88,    90,    93,    55,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,   147,   119,  -209,  -209,    35,
      63,   131,    77,    78,   143,   145,   114,  -209,    83,    86,
     115,  -209,  -209,  -209,  -209,  -209,   108,  -209,  -209,  -209,
    -209,  -209,   -20,   146,   149,   -23,   132,  -209,   157,   134,
     109,   178,   180,  -209,  -209,   142,   176,   177,   148,   151,
     154,   161,  -209,   146,   152,  -209,    13,   146,   162,   163,
     164,   171,  -209,  -209,   213,   201,    25,   229,   179,   214,
     202,   -23,  -209,  -209,   -18,   -23,  -209,   216,    49,   110,
    -209,   -23,  -209,   218,   200,   221,   172,  -209,    99,   222,
    -209,  -209,  -209,  -209,   128,  -209,   135,    73,  -209,    54,
     148,   177,   234,   146,   175,   146,   146,  -209,  -209,   181,
     182,  -209,   183,    -1,   163,   225,  -209,  -209,  -209,  -209,
    -209,     6,   184,   227,   226,   201,   243,   185,  -209,   203,
     166,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,    10,
      92,    25,    25,  -209,   244,  -209,  -209,   214,   250,   188,
    -209,   -23,  -209,  -209,   238,   239,   240,   192,   215,   177,
     218,   257,   198,  -209,   235,  -209,  -209,   245,   184,    99,
     247,   222,  -209,   135,  -209,  -209,  -209,  -209,     1,  -209,
    -209,   236,  -209,    73,    73,   248,  -209,  -209,   264,   146,
    -209,  -209,  -209,   251,   204,  -209,  -209,  -209,  -209,   254,
    -209,   184,   255,   245,   226,  -209,  -209,    34,   226,   256,
     208,  -209,  -209,  -209,  -209,  -209,  -209,   -23,   -10,   245,
     266,   258,  -209,     1,   246,  -209,   259,  -209,  -209,   241,
    -209,  -209,  -209,   276,   226,   262,   217,  -209,    25,  -209,
     263,  -209,  -209,    73,  -209,   237,   242,   177,   219,  -209,
     249,    25,    73,   237,  -209
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    71,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     0,     0,     4,    19,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,    25,    26,    27,    23,    22,     0,    77,    78,    79,
      80,    81,    97,    93,     0,    97,     0,    74,     0,     0,
       0,     0,     0,    30,    29,     0,     0,   102,     0,     0,
       0,     0,    98,    93,     0,    89,     0,    93,     0,     0,
       0,     0,    28,    36,     0,     0,     0,     0,     0,    66,
       0,    97,    99,    90,    97,    97,    88,     0,     0,     0,
      92,    97,    52,    39,     0,     0,     0,    37,     0,    54,
      63,    59,    60,    61,     0,    62,     0,   104,    64,     0,
       0,   102,     0,    93,     0,    93,    93,    85,    83,     0,
       0,    82,     0,   100,     0,     0,    47,    48,    49,    50,
      51,    43,     0,     0,    57,     0,     0,     0,   126,   130,
       0,   128,   124,   118,   119,   120,   121,   122,   123,     0,
       0,     0,     0,   103,     0,    68,    70,    66,     0,     0,
      91,    97,    94,    96,     0,     0,     0,     0,     0,   102,
      39,     0,     0,    44,     0,    42,    35,    33,     0,     0,
       0,    54,    53,     0,   131,   127,   129,   125,     0,   109,
     107,   110,   108,   104,   104,     0,    67,    65,     0,    93,
      87,    84,    86,   100,     0,    72,    40,    38,    46,     0,
      45,     0,     0,    33,    57,    56,    55,     0,    57,     0,
       0,   105,   106,    69,   132,    95,   101,    97,    43,    33,
       0,     0,    58,     0,     0,   111,     0,   116,   112,     0,
      41,    34,    31,     0,    57,     0,     0,   114,     0,    32,
       0,   117,   113,   104,   115,    75,     0,   102,     0,    73,
       0,     0,   104,    75,    76
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,
    -209,  -209,  -209,  -208,  -183,  -209,  -209,  -209,    95,   144,
      39,  -209,  -209,  -209,  -209,    91,   136,  -201,  -113,  -209,
    -209,   116,   165,  -209,  -166,  -209,    11,  -209,   -71,  -209,
     -81,   -65,    74,  -130,  -204,  -168,  -119,  -209
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   232,   197,    29,    30,    31,   145,   113,
     195,   229,   151,   114,    32,   156,   119,   200,   126,    33,
      34,   131,    99,    35,    36,    37,   277,    64,    65,    66,
      85,    83,   189,    97,   173,   127,   169,    38
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      87,   178,   103,   213,   214,   154,   110,   170,   215,   241,
     242,     5,    80,   105,   134,   233,   175,    81,   187,   193,
      81,    44,    81,   192,    42,   251,    43,   208,    48,   120,
      47,   106,    49,   252,   194,   193,   133,   256,   120,   135,
     136,   261,   239,    50,    82,   188,   143,    82,   249,    82,
     194,   253,   180,   120,   182,   183,   210,   212,   176,   225,
      45,    46,   120,   270,   121,   122,   123,   138,   139,   275,
     125,   174,    51,   121,   122,   123,   107,   209,   283,   125,
     108,   140,   120,   109,   237,    52,   234,   265,   121,   122,
     123,    53,   124,    54,   125,   238,    55,   121,   122,   123,
     273,   254,    68,   125,    56,    57,    58,    59,    60,    61,
     171,   172,    39,   282,    40,    41,   219,   121,   122,   123,
     120,     2,    67,   125,   255,     3,     4,   120,   141,   142,
      69,     5,     6,     7,     8,     9,    10,    11,   245,    70,
     264,    12,    13,    14,    71,    72,    73,   279,    74,    75,
      76,    15,    16,    77,    78,   121,   122,   123,    79,   211,
     157,   125,   121,   122,   123,    84,    86,    88,   125,    17,
     158,   159,   160,   161,    89,    90,    91,   158,   159,   160,
     161,    92,   259,    93,   162,   163,   164,   165,   166,   167,
     168,   162,   163,   164,   165,   166,   167,   168,    57,    58,
      59,    60,    61,    57,    58,    59,    60,    61,   205,    94,
      95,   206,   116,    96,    62,    98,   117,    63,   118,   104,
     100,   101,   207,   146,   147,   148,   149,   150,   102,   111,
     112,   115,   128,   130,   137,   132,   129,   144,   152,   153,
     179,   155,   181,   191,   198,   199,   202,   204,   184,   185,
     186,   196,   203,   217,     5,   218,   220,   221,   222,   223,
     227,   228,   224,   230,   231,   235,   243,   244,   240,   262,
     187,   247,   248,   250,   257,   258,   263,   267,   266,   269,
     271,   274,   268,   276,   272,   226,   280,   260,   190,   278,
     281,   201,   236,   216,   284,   177,     0,   246
};

static const yytype_int16 yycheck[] =
{
      65,   131,    83,   171,   172,   118,    87,   126,   174,   213,
     214,    10,    32,    84,    32,   198,   129,    40,    19,    29,
      40,    67,    40,    17,     6,   233,     8,    17,    33,    28,
       3,    18,    35,   234,    44,    29,   101,   238,    28,   104,
     105,   249,   208,    67,    67,    46,   111,    67,   231,    67,
      44,    17,   133,    28,   135,   136,   169,   170,   129,   189,
       7,     8,    28,   264,    63,    64,    65,    18,    19,   273,
      69,    17,     3,    63,    64,    65,    63,    67,   282,    69,
      67,    32,    28,    70,   203,     3,   199,   253,    63,    64,
      65,     3,    67,     3,    69,   208,     3,    63,    64,    65,
     268,    67,    67,    69,    49,    51,    52,    53,    54,    55,
      37,    38,     6,   281,     8,     9,   181,    63,    64,    65,
      28,     0,     3,    69,   237,     4,     5,    28,    18,    19,
      67,    10,    11,    12,    13,    14,    15,    16,   219,     8,
     253,    20,    21,    22,    67,    67,     3,   277,     3,    35,
      67,    30,    31,    67,    39,    63,    64,    65,    50,    67,
      32,    69,    63,    64,    65,    19,    17,    35,    69,    48,
      42,    43,    44,    45,    17,    41,    67,    42,    43,    44,
      45,     3,   247,     3,    56,    57,    58,    59,    60,    61,
      62,    56,    57,    58,    59,    60,    61,    62,    51,    52,
      53,    54,    55,    51,    52,    53,    54,    55,    42,    67,
      34,    45,    41,    36,    67,    67,     3,    70,    17,    67,
      69,    67,    56,    23,    24,    25,    26,    27,    67,    67,
      67,    67,     3,    19,    18,    33,    57,    19,    17,    67,
       6,    19,    67,    18,    17,    19,     3,    44,    67,    67,
      67,    67,    67,     3,    10,    67,    18,    18,    18,    67,
       3,    63,    47,    28,    19,    18,    18,     3,    32,     3,
      19,    67,    18,    18,    18,    67,    18,    18,    32,     3,
      18,    18,    41,    46,    67,   190,    67,   248,   144,    47,
      41,   155,   201,   177,   283,   130,    -1,   223
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    73,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    30,    31,    48,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    87,
      88,    89,    96,   101,   102,   105,   106,   107,   119,     6,
       8,     9,     6,     8,    67,     7,     8,     3,    33,    35,
      67,     3,     3,     3,     3,     3,    49,    51,    52,    53,
      54,    55,    67,    70,   109,   110,   111,     3,    67,    67,
       8,    67,    67,     3,     3,    35,    67,    67,    39,    50,
      32,    40,    67,   113,    19,   112,    17,   113,    35,    17,
      41,    67,     3,     3,    67,    34,    36,   115,    67,   104,
      69,    67,    67,   112,    67,   110,    18,    63,    67,    70,
     112,    67,    67,    91,    95,    67,    41,     3,    17,    98,
      28,    63,    64,    65,    67,    69,   100,   117,     3,    57,
      19,   103,    33,   113,    32,   113,   113,    18,    18,    19,
      32,    18,    19,   113,    19,    90,    23,    24,    25,    26,
      27,    94,    17,    67,   100,    19,    97,    32,    42,    43,
      44,    45,    56,    57,    58,    59,    60,    61,    62,   118,
     118,    37,    38,   116,    17,   100,   110,   104,   115,     6,
     112,    67,   112,   112,    67,    67,    67,    19,    46,   114,
      91,    18,    17,    29,    44,    92,    67,    86,    17,    19,
      99,    98,     3,    67,    44,    42,    45,    56,    17,    67,
     100,    67,   100,   117,   117,   106,   103,     3,    67,   113,
      18,    18,    18,    67,    47,   115,    90,     3,    63,    93,
      28,    19,    85,    86,   100,    18,    97,   118,   100,   106,
      32,   116,   116,    18,     3,   112,   114,    67,    18,    86,
      18,    85,    99,    17,    67,   100,    99,    18,    67,   113,
      92,    85,     3,    18,   100,   106,    32,    18,    41,     3,
      99,    18,    67,   117,    18,   116,    46,   108,    47,   115,
      67,    41,   117,   116,   108
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    72,    73,    73,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    84,    85,    85,    86,    87,    88,    89,    90,
      90,    91,    91,    92,    92,    92,    93,    94,    94,    94,
      94,    94,    95,    96,    97,    97,    98,    99,    99,   100,
     100,   100,   100,   100,   101,   102,   103,   103,   104,   104,
     104,   105,   106,   106,   107,   108,   108,   109,   109,   109,
     109,   109,   110,   110,   110,   110,   110,   110,   110,   111,
     111,   111,   111,   112,   112,   112,   112,   113,   113,   113,
     114,   114,   115,   115,   116,   116,   116,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   119
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,    10,    11,     0,     3,     1,     4,     5,     8,     0,
       3,     6,     3,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     7,     0,     3,     4,     0,     3,     1,
       1,     1,     1,     1,     5,     7,     0,     3,     3,     5,
       3,     1,     7,    14,     2,     0,     7,     1,     1,     1,
       1,     1,     4,     4,     6,     4,     6,     6,     3,     2,
       3,     5,     3,     0,     4,     6,     4,     0,     1,     2,
       0,     3,     0,     3,     0,     3,     3,     3,     3,     3,
       3,     5,     5,     7,     6,     8,     5,     7,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     1,     2,
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
#line 208 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1468 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 213 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1476 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 218 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1484 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 224 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1492 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 230 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1500 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 236 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1508 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 242 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1517 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 248 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1525 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 254 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1534 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON  */
#line 262 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			
		}
#line 1544 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE attr_name attr_name_list RBRACE SEMICOLON  */
#line 268 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $8);
		}
#line 1554 "yacc_sql.tab.c"
    break;

  case 34: /* attr_name_list: COMMA attr_name attr_name_list  */
#line 277 "yacc_sql.y"
                                         {

	}
#line 1562 "yacc_sql.tab.c"
    break;

  case 35: /* attr_name: ID  */
#line 282 "yacc_sql.y"
              {
	create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	// create_index_append_attribute_name(&CONTEXT->ssql->sstr.create_index, $2);
}
#line 1571 "yacc_sql.tab.c"
    break;

  case 36: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 288 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1580 "yacc_sql.tab.c"
    break;

  case 37: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 295 "yacc_sql.y"
                                    {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1589 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 303 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1601 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 313 "yacc_sql.y"
                                   {    }
#line 1607 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE nullable  */
#line 318 "yacc_sql.y"
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
#line 1622 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type nullable  */
#line 329 "yacc_sql.y"
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
#line 1637 "yacc_sql.tab.c"
    break;

  case 43: /* nullable: %empty  */
#line 342 "yacc_sql.y"
        { (yyval.number)=0; }
#line 1643 "yacc_sql.tab.c"
    break;

  case 44: /* nullable: NULLABLE  */
#line 343 "yacc_sql.y"
                   { (yyval.number)=1; }
#line 1649 "yacc_sql.tab.c"
    break;

  case 45: /* nullable: NOT NULL_T  */
#line 344 "yacc_sql.y"
                     { (yyval.number)=2; }
#line 1655 "yacc_sql.tab.c"
    break;

  case 46: /* number: NUMBER  */
#line 348 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1661 "yacc_sql.tab.c"
    break;

  case 47: /* type: INT_T  */
#line 351 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1667 "yacc_sql.tab.c"
    break;

  case 48: /* type: STRING_T  */
#line 352 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1673 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 353 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1679 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 354 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1685 "yacc_sql.tab.c"
    break;

  case 51: /* type: TEXT_T  */
#line 355 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1691 "yacc_sql.tab.c"
    break;

  case 52: /* ID_get: ID  */
#line 359 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1700 "yacc_sql.tab.c"
    break;

  case 53: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 368 "yacc_sql.y"
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
#line 1720 "yacc_sql.tab.c"
    break;

  case 55: /* tuple_list: COMMA tuple tuple_list  */
#line 386 "yacc_sql.y"
                                 {
	}
#line 1727 "yacc_sql.tab.c"
    break;

  case 56: /* tuple: LBRACE value value_list RBRACE  */
#line 392 "yacc_sql.y"
                                       {
		insert_init(&CONTEXT->insert_list[CONTEXT->insert_num++], CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1736 "yacc_sql.tab.c"
    break;

  case 58: /* value_list: COMMA value value_list  */
#line 400 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1744 "yacc_sql.tab.c"
    break;

  case 59: /* value: NUMBER  */
#line 405 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1752 "yacc_sql.tab.c"
    break;

  case 60: /* value: FLOAT  */
#line 408 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1760 "yacc_sql.tab.c"
    break;

  case 61: /* value: DATE  */
#line 411 "yacc_sql.y"
             {
		(yyvsp[0].string) = substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);
		int res = value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		if (res != 0) {
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			yyresult = 2;
			goto yyreturn;
		}
	}
#line 1774 "yacc_sql.tab.c"
    break;

  case 62: /* value: SSS  */
#line 420 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1783 "yacc_sql.tab.c"
    break;

  case 63: /* value: NULL_T  */
#line 424 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1791 "yacc_sql.tab.c"
    break;

  case 64: /* delete: DELETE FROM ID where SEMICOLON  */
#line 431 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1803 "yacc_sql.tab.c"
    break;

  case 65: /* updates: UPDATE ID SET modify_expr modify_list where SEMICOLON  */
#line 451 "yacc_sql.y"
                                                              {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		updates_select_init(&CONTEXT->ssql->sstr.updates, (yyvsp[-5].string), CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
		CONTEXT->select_num = 0;
		CONTEXT->attr_num = 0;
	}
#line 1815 "yacc_sql.tab.c"
    break;

  case 67: /* modify_list: COMMA modify_expr modify_list  */
#line 461 "yacc_sql.y"
                                        {

	}
#line 1823 "yacc_sql.tab.c"
    break;

  case 68: /* modify_expr: ID EQ value  */
#line 467 "yacc_sql.y"
                    {
		updates_append_value(&CONTEXT->ssql->sstr.updates, &CONTEXT->values[CONTEXT->value_length - 1], (yyvsp[-2].string));
	}
#line 1831 "yacc_sql.tab.c"
    break;

  case 69: /* modify_expr: ID EQ LBRACE select_clause RBRACE  */
#line 470 "yacc_sql.y"
                                           {
		Value value;
		value_init_select(&value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, (yyvsp[-4].string));
	}
#line 1841 "yacc_sql.tab.c"
    break;

  case 70: /* modify_expr: ID EQ agg  */
#line 475 "yacc_sql.y"
                    {
		Value value;
		// value_init_agg(&value, &CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]-1]);
		// CONTEXT->select_attr_num[CONTEXT->select_num]--;
		value_init_agg(&value, &CONTEXT->attrs[--CONTEXT->attr_num]);
		updates_append_value(&CONTEXT->ssql->sstr.updates, &value, (yyvsp[-2].string));
	}
#line 1853 "yacc_sql.tab.c"
    break;

  case 71: /* select_begin: SELECT  */
#line 485 "yacc_sql.y"
               {
		// 记录当前深度select的状态
		CONTEXT->cursor_attr[CONTEXT->depth] = CONTEXT->attr_num;
		CONTEXT->cursor_cond[CONTEXT->depth] = CONTEXT->condition_length;
		CONTEXT->cursor_value[CONTEXT->depth] = CONTEXT->value_length;
		++CONTEXT->depth;
	}
#line 1865 "yacc_sql.tab.c"
    break;

  case 72: /* select_clause: select_begin select_attr FROM ID alias_ID rel_list where  */
#line 494 "yacc_sql.y"
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


		// 状态复原
		--CONTEXT->depth;
		CONTEXT->attr_num = CONTEXT->cursor_attr[CONTEXT->depth];
		CONTEXT->condition_length = CONTEXT->cursor_cond[CONTEXT->depth];
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth];

		// 临时变量清零
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		++CONTEXT->select_num;
	}
#line 1898 "yacc_sql.tab.c"
    break;

  case 73: /* select_clause: select_begin select_attr FROM ID alias_ID INNER JOIN ID alias_ID ON condition condition_list join_list where  */
#line 522 "yacc_sql.y"
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

		// 状态复原
		--CONTEXT->depth;
		CONTEXT->attr_num = CONTEXT->cursor_attr[CONTEXT->depth];
		CONTEXT->condition_length = CONTEXT->cursor_cond[CONTEXT->depth];
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth];
		++CONTEXT->depth;
		// 临时变量清零
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		++CONTEXT->select_num;
	}
#line 1929 "yacc_sql.tab.c"
    break;

  case 74: /* select: select_clause SEMICOLON  */
#line 551 "yacc_sql.y"
                            {
		// 这里说明select是主语句
		CONTEXT->ssql->flag=SCF_SELECT;//"select";
		CONTEXT->ssql->sstr.selection = CONTEXT->selections[CONTEXT->select_num-1];
	}
#line 1939 "yacc_sql.tab.c"
    break;

  case 76: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 560 "yacc_sql.y"
        {
		selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-4].string));
	}
#line 1947 "yacc_sql.tab.c"
    break;

  case 77: /* agg_func: MAX_T  */
#line 566 "yacc_sql.y"
              { (yyval.number)=MAX; }
#line 1953 "yacc_sql.tab.c"
    break;

  case 78: /* agg_func: MIN_T  */
#line 567 "yacc_sql.y"
                { (yyval.number)=MIN; }
#line 1959 "yacc_sql.tab.c"
    break;

  case 79: /* agg_func: COUNT_T  */
#line 568 "yacc_sql.y"
                  { (yyval.number)=COUNT; }
#line 1965 "yacc_sql.tab.c"
    break;

  case 80: /* agg_func: AVG_T  */
#line 569 "yacc_sql.y"
                { (yyval.number)=AVG; }
#line 1971 "yacc_sql.tab.c"
    break;

  case 81: /* agg_func: SUM_T  */
#line 570 "yacc_sql.y"
                { (yyval.number)=SUM; }
#line 1977 "yacc_sql.tab.c"
    break;

  case 82: /* agg: agg_func LBRACE STAR RBRACE  */
#line 575 "yacc_sql.y"
                                    {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, "*", (yyvsp[-3].number));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->attr_num++] = attr;
	}
#line 1988 "yacc_sql.tab.c"
    break;

  case 83: /* agg: agg_func LBRACE ID RBRACE  */
#line 581 "yacc_sql.y"
                                    {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, NULL, (yyvsp[-1].string), (yyvsp[-3].number));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->attr_num++] = attr;
	}
#line 1999 "yacc_sql.tab.c"
    break;

  case 84: /* agg: agg_func LBRACE ID DOT ID RBRACE  */
#line 587 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init_with_agg(&attr, (yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[-5].number));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->attr_num++] = attr;
	}
#line 2010 "yacc_sql.tab.c"
    break;

  case 85: /* agg: agg_func LBRACE NUMBER RBRACE  */
#line 593 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init_with_agg_num(&attr, (yyvsp[-3].number), (yyvsp[-1].number));
		// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
		CONTEXT->attrs[CONTEXT->attr_num++] = attr;
	}
#line 2021 "yacc_sql.tab.c"
    break;

  case 86: /* agg: agg_func LBRACE STAR COMMA ID RBRACE  */
#line 599 "yacc_sql.y"
                                               {
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturn;
	}
#line 2031 "yacc_sql.tab.c"
    break;

  case 87: /* agg: agg_func LBRACE ID COMMA ID RBRACE  */
#line 604 "yacc_sql.y"
                                             {
		// 错误类型
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturn;
	}
#line 2042 "yacc_sql.tab.c"
    break;

  case 88: /* agg: agg_func LBRACE RBRACE  */
#line 610 "yacc_sql.y"
                                 {
		// 错误类型
		CONTEXT->ssql->flag = SCF_INVALID_DATE;
		yyresult = 2;
		goto yyreturn;
	}
#line 2053 "yacc_sql.tab.c"
    break;

  case 89: /* select_attr: STAR attr_list  */
#line 619 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
			CONTEXT->attrs[CONTEXT->attr_num++] = attr;
		}
#line 2064 "yacc_sql.tab.c"
    break;

  case 90: /* select_attr: ID alias_ID attr_list  */
#line 625 "yacc_sql.y"
                            {
			RelAttr attr;
			relation_attr_init_with_alias(&attr, NULL, (yyvsp[-2].string), (yyvsp[-1].string));
			// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
			CONTEXT->attrs[CONTEXT->attr_num++] = attr;
		}
#line 2075 "yacc_sql.tab.c"
    break;

  case 91: /* select_attr: ID DOT ID alias_ID attr_list  */
#line 631 "yacc_sql.y"
                                       {
			RelAttr attr;
			relation_attr_init_with_alias(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-1].string));
			// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
			CONTEXT->attrs[CONTEXT->attr_num++] = attr;
		}
#line 2086 "yacc_sql.tab.c"
    break;

  case 92: /* select_attr: agg alias_ID attr_list  */
#line 637 "yacc_sql.y"
                                 {
		// agg 先初始化RelAttr之后，再进入该判断逻辑
		CONTEXT->attrs[CONTEXT->attr_num-1].alias = (yyvsp[-1].string);
	}
#line 2095 "yacc_sql.tab.c"
    break;

  case 94: /* attr_list: COMMA ID alias_ID attr_list  */
#line 645 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init_with_alias(&attr, NULL, (yyvsp[-2].string), (yyvsp[-1].string));
			// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
			CONTEXT->attrs[CONTEXT->attr_num++] = attr;
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2108 "yacc_sql.tab.c"
    break;

  case 95: /* attr_list: COMMA ID DOT ID alias_ID attr_list  */
#line 653 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init_with_alias(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-1].string));
			// CONTEXT->select_attrs[CONTEXT->select_num][CONTEXT->select_attr_num[CONTEXT->select_num]++] = attr;
			CONTEXT->attrs[CONTEXT->attr_num++] = attr;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2121 "yacc_sql.tab.c"
    break;

  case 96: /* attr_list: COMMA agg alias_ID attr_list  */
#line 661 "yacc_sql.y"
                                       {
		CONTEXT->attrs[CONTEXT->attr_num-1].alias = (yyvsp[-1].string);
	}
#line 2129 "yacc_sql.tab.c"
    break;

  case 97: /* alias_ID: %empty  */
#line 668 "yacc_sql.y"
        { (yyval.string) = NULL; }
#line 2135 "yacc_sql.tab.c"
    break;

  case 98: /* alias_ID: ID  */
#line 669 "yacc_sql.y"
             { (yyval.string) = (yyvsp[0].string); }
#line 2141 "yacc_sql.tab.c"
    break;

  case 99: /* alias_ID: AS ID  */
#line 670 "yacc_sql.y"
                { (yyval.string)=(yyvsp[0].string); }
#line 2147 "yacc_sql.tab.c"
    break;

  case 101: /* rel_list: COMMA ID rel_list  */
#line 675 "yacc_sql.y"
                        {	
		selects_append_relation(&CONTEXT->selections[CONTEXT->select_num], (yyvsp[-1].string));
	}
#line 2155 "yacc_sql.tab.c"
    break;

  case 103: /* where: WHERE condition condition_list  */
#line 681 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
	}
#line 2163 "yacc_sql.tab.c"
    break;

  case 105: /* condition_list: AND condition condition_list  */
#line 687 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
	}
#line 2171 "yacc_sql.tab.c"
    break;

  case 106: /* condition_list: OR condition condition_list  */
#line 690 "yacc_sql.y"
                                      {

	}
#line 2179 "yacc_sql.tab.c"
    break;

  case 107: /* condition: ID comOp value  */
#line 696 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

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
#line 2203 "yacc_sql.tab.c"
    break;

  case 108: /* condition: value comOp value  */
#line 716 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			CONTEXT->value_length -= 2;
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
#line 2227 "yacc_sql.tab.c"
    break;

  case 109: /* condition: ID comOp ID  */
#line 736 "yacc_sql.y"
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
#line 2251 "yacc_sql.tab.c"
    break;

  case 110: /* condition: value comOp ID  */
#line 756 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[--CONTEXT->value_length];
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
#line 2276 "yacc_sql.tab.c"
    break;

  case 111: /* condition: ID DOT ID comOp value  */
#line 777 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[--CONTEXT->value_length];

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
#line 2300 "yacc_sql.tab.c"
    break;

  case 112: /* condition: value comOp ID DOT ID  */
#line 797 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[--CONTEXT->value_length];

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
#line 2325 "yacc_sql.tab.c"
    break;

  case 113: /* condition: ID DOT ID comOp ID DOT ID  */
#line 818 "yacc_sql.y"
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
#line 2348 "yacc_sql.tab.c"
    break;

  case 114: /* condition: ID comOp LBRACE value value_list RBRACE  */
#line 836 "yacc_sql.y"
                                                  {
		// comOp只能是in/not in, exists/not exists
		// 同除了包含LBRACE value value_list RBRACE的条件语句，comOp都只能是非in/not in, exists/not exists
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-5].string));
		Value right_value;
		value_init_set(&right_value, CONTEXT->values, CONTEXT->cursor_value[CONTEXT->depth], CONTEXT->value_length - CONTEXT->cursor_value[CONTEXT->depth]);
		Condition condition;

		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		/// 复原同一深度的cursor_value[]，防止和同一深度其他的SETS类型value冲突
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
#line 2367 "yacc_sql.tab.c"
    break;

  case 115: /* condition: ID DOT ID comOp LBRACE value value_list RBRACE  */
#line 850 "yacc_sql.y"
                                                         {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-7].string));
		Value right_value;
		value_init_set(&right_value, CONTEXT->values, CONTEXT->cursor_value[CONTEXT->depth], CONTEXT->value_length - CONTEXT->cursor_value[CONTEXT->depth]);
		Condition condition;

		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
#line 2383 "yacc_sql.tab.c"
    break;

  case 116: /* condition: ID comOp LBRACE select_clause RBRACE  */
#line 862 "yacc_sql.y"
        {

		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-4].string));
		Value right_value;
		value_init_select(&right_value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		Condition condition;

		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
#line 2400 "yacc_sql.tab.c"
    break;

  case 117: /* condition: ID DOT ID comOp LBRACE select_clause RBRACE  */
#line 874 "yacc_sql.y"
                                                      {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
		Value right_value;
		value_init_select(&right_value, &CONTEXT->selections[CONTEXT->select_num - 1]);
		Condition condition;

		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		CONTEXT->value_length = CONTEXT->cursor_value[CONTEXT->depth - 1];
	}
#line 2416 "yacc_sql.tab.c"
    break;

  case 118: /* comOp: EQ  */
#line 888 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2422 "yacc_sql.tab.c"
    break;

  case 119: /* comOp: LT  */
#line 889 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2428 "yacc_sql.tab.c"
    break;

  case 120: /* comOp: GT  */
#line 890 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2434 "yacc_sql.tab.c"
    break;

  case 121: /* comOp: LE  */
#line 891 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2440 "yacc_sql.tab.c"
    break;

  case 122: /* comOp: GE  */
#line 892 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2446 "yacc_sql.tab.c"
    break;

  case 123: /* comOp: NE  */
#line 893 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2452 "yacc_sql.tab.c"
    break;

  case 124: /* comOp: LIKE  */
#line 894 "yacc_sql.y"
               { CONTEXT->comp = LIKE_MATCH; }
#line 2458 "yacc_sql.tab.c"
    break;

  case 125: /* comOp: NOT LIKE  */
#line 895 "yacc_sql.y"
                   { CONTEXT->comp = NOT_LIKE; }
#line 2464 "yacc_sql.tab.c"
    break;

  case 126: /* comOp: IN  */
#line 896 "yacc_sql.y"
             { CONTEXT->comp = IN_OP; }
#line 2470 "yacc_sql.tab.c"
    break;

  case 127: /* comOp: NOT IN  */
#line 897 "yacc_sql.y"
                 { CONTEXT->comp = NOT_IN_OP; }
#line 2476 "yacc_sql.tab.c"
    break;

  case 128: /* comOp: EXIST  */
#line 898 "yacc_sql.y"
                { CONTEXT->comp =EXISTS_OP; }
#line 2482 "yacc_sql.tab.c"
    break;

  case 129: /* comOp: NOT EXIST  */
#line 899 "yacc_sql.y"
                    { CONTEXT->comp = NOT_EXISTS_OP; }
#line 2488 "yacc_sql.tab.c"
    break;

  case 130: /* comOp: IS  */
#line 900 "yacc_sql.y"
             { CONTEXT->comp = IS_OP; }
#line 2494 "yacc_sql.tab.c"
    break;

  case 131: /* comOp: IS NOT  */
#line 901 "yacc_sql.y"
                 { CONTEXT->comp = IS_NOT_OP; }
#line 2500 "yacc_sql.tab.c"
    break;

  case 132: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 906 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2509 "yacc_sql.tab.c"
    break;


#line 2513 "yacc_sql.tab.c"

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

#line 911 "yacc_sql.y"

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
