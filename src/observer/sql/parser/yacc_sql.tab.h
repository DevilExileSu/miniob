/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    UNIQUE = 264,                  /* UNIQUE  */
    SELECT = 265,                  /* SELECT  */
    DESC = 266,                    /* DESC  */
    SHOW = 267,                    /* SHOW  */
    SYNC = 268,                    /* SYNC  */
    INSERT = 269,                  /* INSERT  */
    DELETE = 270,                  /* DELETE  */
    UPDATE = 271,                  /* UPDATE  */
    LBRACE = 272,                  /* LBRACE  */
    RBRACE = 273,                  /* RBRACE  */
    COMMA = 274,                   /* COMMA  */
    TRX_BEGIN = 275,               /* TRX_BEGIN  */
    TRX_COMMIT = 276,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 277,            /* TRX_ROLLBACK  */
    ADD_T = 278,                   /* ADD_T  */
    SUB_T = 279,                   /* SUB_T  */
    DIV_T = 280,                   /* DIV_T  */
    INT_T = 281,                   /* INT_T  */
    STRING_T = 282,                /* STRING_T  */
    FLOAT_T = 283,                 /* FLOAT_T  */
    DATE_T = 284,                  /* DATE_T  */
    TEXT_T = 285,                  /* TEXT_T  */
    NULL_T = 286,                  /* NULL_T  */
    NULLABLE = 287,                /* NULLABLE  */
    HELP = 288,                    /* HELP  */
    EXIT = 289,                    /* EXIT  */
    DOT = 290,                     /* DOT  */
    INTO = 291,                    /* INTO  */
    VALUES = 292,                  /* VALUES  */
    FROM = 293,                    /* FROM  */
    WHERE = 294,                   /* WHERE  */
    AND = 295,                     /* AND  */
    OR = 296,                      /* OR  */
    SET = 297,                     /* SET  */
    AS = 298,                      /* AS  */
    ON = 299,                      /* ON  */
    IN = 300,                      /* IN  */
    IS = 301,                      /* IS  */
    NOT = 302,                     /* NOT  */
    EXIST = 303,                   /* EXIST  */
    INNER = 304,                   /* INNER  */
    JOIN = 305,                    /* JOIN  */
    LOAD = 306,                    /* LOAD  */
    DATA = 307,                    /* DATA  */
    INFILE = 308,                  /* INFILE  */
    MAX_T = 309,                   /* MAX_T  */
    MIN_T = 310,                   /* MIN_T  */
    COUNT_T = 311,                 /* COUNT_T  */
    AVG_T = 312,                   /* AVG_T  */
    SUM_T = 313,                   /* SUM_T  */
    ASC = 314,                     /* ASC  */
    ORDER = 315,                   /* ORDER  */
    GROUP = 316,                   /* GROUP  */
    BY = 317,                      /* BY  */
    HAVING = 318,                  /* HAVING  */
    LENGTH_T = 319,                /* LENGTH_T  */
    ROUND_T = 320,                 /* ROUND_T  */
    DATE_FORMAT_T = 321,           /* DATE_FORMAT_T  */
    LIKE = 322,                    /* LIKE  */
    EQ = 323,                      /* EQ  */
    LT = 324,                      /* LT  */
    GT = 325,                      /* GT  */
    LE = 326,                      /* LE  */
    GE = 327,                      /* GE  */
    NE = 328,                      /* NE  */
    NUMBER = 329,                  /* NUMBER  */
    FLOAT = 330,                   /* FLOAT  */
    DATE = 331,                    /* DATE  */
    TEXT = 332,                    /* TEXT  */
    ID = 333,                      /* ID  */
    PATH = 334,                    /* PATH  */
    SSS = 335,                     /* SSS  */
    STAR = 336,                    /* STAR  */
    STRING_V = 337                 /* STRING_V  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 170 "yacc_sql.y"

  struct _Attr *attr1;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
  char *position;
  struct _Exp *exp1;

#line 157 "yacc_sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (void *scanner);


#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
