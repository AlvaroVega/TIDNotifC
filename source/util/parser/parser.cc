
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.yy"


/*
 *  File name: parser.yy
 *  File type: Bison source file.
 *  Date : December 2005
 *  Author: David Alonso <dalonso@gsyc.escet.urjc.es>
 */

/*
 * Copyright (C) 2006 Telefonica I+D S.A.
 *
 * This source file is a property of Telefonica I+D. You can not
 * use it for any purpose unless you have an explicit authorization
 * by its owner.
 */

/*
 * Revision historial:
 *   - 04/07/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * 'yyerror()' subroutine calls to 'TIDParser::free_tmp_nodes()'.
 *       * Temporarily stored nodes are now saved in 
 *         'TIDParser::tmp_node_stack' stack object instead of using
 *         'TIDParser::tmp_nodes' linked list to avoid multiple sides memory
 *         deallocation.
 *   - 04/19/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * TK_VALUE renamed to TK_DOLLAR.
 *       * Added a new rule to match runtime variables.
 *       * yyterminate() function is not valid in Bison.
 *         YYERROR is used instead.
 */

/* Base node type. */
#include "EvaluableNode.h"

/* Inmediate value node types include. */
#include "BooleanValueNode.h"
#include "LongValueNode.h"
#include "DoubleValueNode.h"
#include "StringValueNode.h"

/* Other value nodes include. */
#include "IdentifierValueNode.h"
#include "StringArrayValueNode.h"

/* Complex expression nodes include. */
#include "UnaryExprNode.h"
#include "BinaryExprNode.h"

#include "TIDConstraint.h"
#include "StructFieldNamePath.h"
#include "StructFieldPosPath.h"
#include "ArrayPath.h"
#include "VoidPath.h"
#include "UnionIntSwitchPath.h"
#include "UnionStringSwitchPath.h"
#include "UnionDefaultSwitchPath.h"

/* Caller static class include. */
#include "TIDParser.h"

/* Runtime variable table include. */
#include "RuntimeVariableTable.h"

#include "Debugger.h"

#include <typeinfo>

void yyerror(char *);
int yylex(void);

using namespace TIDNotif::util::parser;

#define YYSTYPE TIDNotif::util::parser::EvaluableNode*



/* Line 189 of yacc.c  */
#line 151 "parser.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_EXIST = 258,
     TK_DEFAULT = 259,
     TK_TILDE_ACCENT = 260,
     TK_IN = 261,
     TK_EQ = 262,
     TK_DIF = 263,
     TK_LESS = 264,
     TK_LESSEQ = 265,
     TK_GREAT = 266,
     TK_GREATEQ = 267,
     TK_MUL = 268,
     TK_DIV = 269,
     TK_MOD = 270,
     TK_ADD = 271,
     TK_MINUS = 272,
     TK_NOT = 273,
     TK_AND = 274,
     TK_OR = 275,
     TK_COMMA = 276,
     TK_BOOL = 277,
     TK_STRING = 278,
     TK_DOT = 279,
     TK_DOLLAR = 280,
     TK__LENGTH = 281,
     TK__D = 282,
     TK__TYPE_ID = 283,
     TK__REPOS_ID = 284,
     TK_OPENPAR = 285,
     TK_CLOSEPAR = 286,
     TK_OPENBRA = 287,
     TK_CLOSEBRA = 288,
     TK_IDENT = 289,
     TK_DOUBLE = 290,
     TK_LONG = 291,
     TK_INDEX = 292
   };
#endif
/* Tokens.  */
#define TK_EXIST 258
#define TK_DEFAULT 259
#define TK_TILDE_ACCENT 260
#define TK_IN 261
#define TK_EQ 262
#define TK_DIF 263
#define TK_LESS 264
#define TK_LESSEQ 265
#define TK_GREAT 266
#define TK_GREATEQ 267
#define TK_MUL 268
#define TK_DIV 269
#define TK_MOD 270
#define TK_ADD 271
#define TK_MINUS 272
#define TK_NOT 273
#define TK_AND 274
#define TK_OR 275
#define TK_COMMA 276
#define TK_BOOL 277
#define TK_STRING 278
#define TK_DOT 279
#define TK_DOLLAR 280
#define TK__LENGTH 281
#define TK__D 282
#define TK__TYPE_ID 283
#define TK__REPOS_ID 284
#define TK_OPENPAR 285
#define TK_CLOSEPAR 286
#define TK_OPENBRA 287
#define TK_CLOSEBRA 288
#define TK_IDENT 289
#define TK_DOUBLE 290
#define TK_LONG 291
#define TK_INDEX 292




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 267 "parser.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  38
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   110

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNRULES -- Number of states.  */
#define YYNSTATES  110

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    10,    14,    16,    20,
      22,    26,    30,    34,    38,    42,    46,    48,    52,    54,
      59,    65,    69,    71,    75,    79,    81,    85,    89,    91,
      94,    96,   100,   103,   105,   107,   110,   112,   115,   117,
     119,   123,   126,   130,   131,   134,   136,   138,   141,   142,
     145,   147,   149,   152,   154,   156,   158,   160,   162,   164,
     169,   174,   177,   182,   183,   185,   188,   191,   193,   197
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    -1,    41,    -1,    42,    -1,
      42,    20,    43,    -1,    43,    -1,    43,    19,    44,    -1,
      44,    -1,    45,     7,    45,    -1,    45,     8,    45,    -1,
      45,     9,    45,    -1,    45,    10,    45,    -1,    45,    11,
      45,    -1,    45,    12,    45,    -1,    45,    -1,    46,     6,
      34,    -1,    46,    -1,    46,     6,    25,    51,    -1,    46,
       6,    30,    59,    31,    -1,    47,     5,    47,    -1,    47,
      -1,    47,    16,    48,    -1,    47,    17,    48,    -1,    48,
      -1,    48,    13,    49,    -1,    48,    14,    49,    -1,    49,
      -1,    18,    50,    -1,    50,    -1,    30,    42,    31,    -1,
       3,    34,    -1,    34,    -1,    35,    -1,    17,    35,    -1,
      36,    -1,    17,    36,    -1,    23,    -1,    22,    -1,     3,
      25,    51,    -1,    25,    51,    -1,     4,    25,    51,    -1,
      -1,    24,    53,    -1,    54,    -1,    55,    -1,    34,    52,
      -1,    -1,    24,    53,    -1,    54,    -1,    55,    -1,    34,
      52,    -1,    56,    -1,    57,    -1,    26,    -1,    27,    -1,
      28,    -1,    29,    -1,    32,    36,    33,    52,    -1,    30,
      34,    31,    52,    -1,    36,    52,    -1,    30,    58,    31,
      52,    -1,    -1,    36,    -1,    17,    36,    -1,    16,    36,
      -1,    23,    -1,    23,    21,    59,    -1,    23,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   135,   135,   151,   158,   168,   178,   192,   202,   217,
     227,   241,   255,   269,   284,   298,   313,   323,   333,   342,
     357,   375,   390,   401,   415,   429,   439,   453,   467,   477,
     490,   500,   508,   521,   529,   537,   546,   554,   563,   571,
     579,   593,   601,   617,   629,   637,   645,   653,   674,   686,
     694,   702,   712,   732,   740,   748,   760,   772,   784,   798,
     820,   830,   852,   907,   914,   922,   931,   939,   949,   964
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_EXIST", "TK_DEFAULT",
  "TK_TILDE_ACCENT", "TK_IN", "TK_EQ", "TK_DIF", "TK_LESS", "TK_LESSEQ",
  "TK_GREAT", "TK_GREATEQ", "TK_MUL", "TK_DIV", "TK_MOD", "TK_ADD",
  "TK_MINUS", "TK_NOT", "TK_AND", "TK_OR", "TK_COMMA", "TK_BOOL",
  "TK_STRING", "TK_DOT", "TK_DOLLAR", "TK__LENGTH", "TK__D", "TK__TYPE_ID",
  "TK__REPOS_ID", "TK_OPENPAR", "TK_CLOSEPAR", "TK_OPENBRA", "TK_CLOSEBRA",
  "TK_IDENT", "TK_DOUBLE", "TK_LONG", "TK_INDEX", "$accept", "start",
  "constraint", "bool", "bool_or", "bool_and", "bool_compare", "expr_in",
  "expr_twiddle", "expr", "term", "factor_not", "factor", "Component",
  "CompExt", "CompDot", "CompArray", "CompAssoc", "CompPos", "UnionPos",
  "UnionVal", "LiteralArray", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    42,    42,    43,    43,
      44,    44,    44,    44,    44,    44,    44,    45,    45,    45,
      45,    46,    46,    47,    47,    47,    48,    48,    48,    49,
      49,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    51,    51,    51,    51,    51,    52,    52,
      52,    52,    53,    53,    53,    53,    53,    53,    53,    54,
      55,    56,    57,    58,    58,    58,    58,    58,    59,    59
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     1,     3,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     1,     4,
       5,     3,     1,     3,     3,     1,     3,     3,     1,     2,
       1,     3,     2,     1,     1,     2,     1,     2,     1,     1,
       3,     2,     3,     0,     2,     1,     1,     2,     0,     2,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     4,
       4,     2,     4,     0,     1,     2,     2,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     0,     0,    39,    38,    43,     0,    33,
      34,    36,     0,     2,     4,     5,     7,     9,    16,    18,
      22,    25,    28,    30,    43,    32,    43,    35,    37,    29,
       0,     0,     0,    48,    41,    45,    46,     0,     1,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,    42,    55,    56,    57,    58,    63,
      48,    48,    44,    53,    54,     0,     0,     0,    47,    50,
      51,    31,     6,     8,    10,    11,    12,    13,    14,    15,
      43,     0,    17,    21,    23,    24,    26,    27,     0,     0,
      67,    64,     0,    52,    61,    48,    48,    49,    19,    69,
       0,    66,    65,    48,    60,    59,     0,    20,    62,    68
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    34,    68,    62,    69,    70,    63,    64,
      92,   100
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -56
static const yytype_int8 yypact[] =
{
       8,   -10,   -16,    10,    32,   -56,   -56,    29,     8,   -56,
     -56,   -56,    13,   -56,   -56,   -17,    -3,   -56,    79,    26,
       5,    15,   -56,   -56,    29,   -56,    29,   -56,   -56,   -56,
      49,    35,     1,    40,   -56,   -56,   -56,     3,   -56,     8,
       8,     8,     8,     8,     8,     8,     8,    22,     8,     8,
       8,     8,     8,   -56,   -56,   -56,   -56,   -56,   -56,    -9,
      40,    40,   -56,   -56,   -56,    53,     6,    49,   -56,   -56,
     -56,   -56,    -3,   -56,   -56,   -56,   -56,   -56,   -56,   -56,
      29,    37,   -56,    34,    15,    15,   -56,   -56,    46,    64,
     -56,   -56,    70,   -56,   -56,    40,    40,   -56,   -56,    44,
      71,   -56,   -56,    40,   -56,   -56,    37,   -56,   -56,   -56
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -56,   -56,   -56,   -56,    63,    65,    66,    51,   -56,    55,
      31,    47,   101,   -22,   -55,    41,    -7,    -6,   -56,   -56,
     -56,     4
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      35,    36,    53,    39,    54,    93,    94,    88,    89,    26,
      48,     1,     2,    38,    90,    24,    40,    35,    36,    35,
      36,    49,    50,    39,    25,     3,     4,    91,    51,    52,
       5,     6,    47,     7,    71,     1,     2,    66,     8,    96,
     104,   105,     9,    10,    11,    27,    28,    80,   108,     3,
      49,    50,    81,    30,     5,     6,    82,     7,    98,    31,
      99,    32,     8,    33,    67,   106,     9,    10,    11,    65,
      31,    37,    32,    35,    36,    55,    56,    57,    58,    59,
      84,    85,   101,    60,    95,    61,    41,    42,    43,    44,
      45,    46,    74,    75,    76,    77,    78,    79,    86,    87,
     102,   103,   107,    83,    72,    29,    73,     0,    97,     0,
     109
};

static const yytype_int8 yycheck[] =
{
       7,     7,    24,    20,    26,    60,    61,    16,    17,    25,
       5,     3,     4,     0,    23,    25,    19,    24,    24,    26,
      26,    16,    17,    20,    34,    17,    18,    36,    13,    14,
      22,    23,     6,    25,    31,     3,     4,    36,    30,    33,
      95,    96,    34,    35,    36,    35,    36,    25,   103,    17,
      16,    17,    30,    24,    22,    23,    34,    25,    80,    30,
      23,    32,    30,    34,    24,    21,    34,    35,    36,    34,
      30,     8,    32,    80,    80,    26,    27,    28,    29,    30,
      49,    50,    36,    34,    31,    36,     7,     8,     9,    10,
      11,    12,    41,    42,    43,    44,    45,    46,    51,    52,
      36,    31,    31,    48,    39,     4,    40,    -1,    67,    -1,
     106
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    17,    18,    22,    23,    25,    30,    34,
      35,    36,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    25,    34,    25,    35,    36,    50,
      24,    30,    32,    34,    51,    54,    55,    42,     0,    20,
      19,     7,     8,     9,    10,    11,    12,     6,     5,    16,
      17,    13,    14,    51,    51,    26,    27,    28,    29,    30,
      34,    36,    53,    56,    57,    34,    36,    24,    52,    54,
      55,    31,    43,    44,    45,    45,    45,    45,    45,    45,
      25,    30,    34,    47,    48,    48,    49,    49,    16,    17,
      23,    36,    58,    52,    52,    31,    33,    53,    51,    23,
      59,    36,    36,    31,    52,    52,    21,    31,    52,    59
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 136 "parser.yy"
    {
              TIDParser::tmp_constraint = new TIDConstraint;
              #ifdef DEBUG_ENABLED
              Debugger::register_malloc(TIDParser::tmp_constraint);
              #endif
              TIDParser::tmp_constraint->addRoot((yyvsp[(1) - (1)]));
              TIDParser::clear_tmp_node_stack();
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"start ::= constraint\"", 0);
              #endif
            }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 151 "parser.yy"
    {
              (yyval) = NULL;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"constraint ::= <lambda>\"", 0);
              #endif
            }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 159 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"constraint ::= bool\"", 0);
              #endif
            }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 169 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool ::= bool_or\"", 0);
              #endif
            }
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 179 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), BinaryExprNode::OR_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_or ::= bool_or TK_OR bool_and\"", 0);
              #endif
            }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 193 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_or ::= bool_and\"", 0);
              #endif
            }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 203 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), BinaryExprNode::AND_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
               Debugger::send_message(90,
                "Reducing rule \"bool_and ::= bool_and TK_AND bool_compare\"", 
                0);
              #endif
           }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 218 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_and ::= bool_compare\"", 0);
              #endif
            }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 228 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), BinaryExprNode::EQUAL_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in TK_EQ expr_in\"", 0);
              #endif
            }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 242 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), BinaryExprNode::NOT_EQUAL_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in TK_DIF expr_in\"", 0);
              #endif
            }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 256 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), BinaryExprNode::LESS_THAN_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in TK_LESS expr_in\"", 0);
              #endif
            }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 270 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 
                BinaryExprNode::LESS_OR_EQUAL_THAN_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in TK_LESSEQ expr_in\"", 0);
              #endif
            }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 285 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), BinaryExprNode::GREATER_THAN_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in TK_GREAT expr_in\"", 0);
              #endif
            }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 299 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 
              	BinaryExprNode::GREATER_OR_EQUAL_THAN_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in TK_GREATEQ expr_in\"", 0);
              #endif
            }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 314 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in\"", 0);
              #endif
            }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 324 "parser.yy"
    {
              /* It's not considered by the grammar but TID considers it */
              (yyval) = NULL;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr_in ::= expr_twiddle TK_IN TK_IDENT\"", 
                0);
              #endif
            }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 334 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr_in ::= expr_twiddle\"", 
                0);
               #endif
            }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 343 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)]), BinaryExprNode::IN_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr_in ::= expr_twiddle TK_IN TK_DOLLAR Component\"", 
                0);
              #endif
            }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 358 "parser.yy"
    {
              /* It's not considered by the grammar but TID considers it */
              (yyval) = new BinaryExprNode((yyvsp[(1) - (5)]), (yyvsp[(4) - (5)]), BinaryExprNode::IN_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr_in ::= expr_twiddle TK_IN TK_OPENPAR LiteralArray TK_CLOSEPAR\"", 
                0);
              #endif
            }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 376 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), BinaryExprNode::TILDE_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr_twiddle ::= expr TK_TILDE_ACCENT expr\"", 
                0);
              #endif
            }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 391 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr_twiddle ::= expr\"", 
                0);
              #endif
            }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 402 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), BinaryExprNode::ADD_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr ::= expr TK_ADD term\"", 0);
              #endif
            }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 416 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), BinaryExprNode::SUB_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr ::= expr TK_MINUS term\"", 0);
              #endif
            }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 430 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr ::= term\"", 0);
              #endif
            }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 440 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), BinaryExprNode::MUL_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
        	    #ifdef DEBUG_ENABLED
          	  Debugger::send_message(90,
            	  "Reducing rule \"term ::= term TK_MUL factor_not\"", 0);
              #endif
            }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 454 "parser.yy"
    {
              (yyval) = new BinaryExprNode((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), BinaryExprNode::DIV_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"term ::= term TK_DIV factor_not\"", 0);
              #endif
            }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 468 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"term ::= factor_not\"", 0);
              #endif
            }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 478 "parser.yy"
    {
              (yyval) = new UnaryExprNode((yyvsp[(2) - (2)]), UnaryExprNode::NOT_OP);
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor_not ::= TK_NOT factor\"", 0);
              #endif
            }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 491 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor_not ::= factor\"", 0);
              #endif
            }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 501 "parser.yy"
    {
              (yyval) = (yyvsp[(2) - (3)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_OPENPAR bool_or TK_CLOSEPAR\"", 0);
              #endif
            }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 509 "parser.yy"
    {
              (yyval) = new UnaryExprNode((yyvsp[(2) - (2)]), UnaryExprNode::EXIST_OP);
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_EXIST TK_IDENT\"", 0);
              #endif
            }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 522 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_IDENT\"", 0);
              #endif
            }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 530 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_DOUBLE\"", 0);
              #endif
            }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 538 "parser.yy"
    {
              dynamic_cast<DoubleValueNode*>((yyvsp[(2) - (2)]))->invert();
              (yyval) = (yyvsp[(2) - (2)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_MINUS TK_DOUBLE\"", 0);
              #endif
            }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 547 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_LONG\"", 0);
              #endif
            }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 555 "parser.yy"
    {
              dynamic_cast<LongValueNode*>((yyvsp[(2) - (2)]))->invert_sign();
              (yyval) = (yyvsp[(2) - (2)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_MINUS TK_LONG\"", 0);
              #endif
            }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 564 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_STRING\"", 0);
              #endif
            }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 572 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_BOOL\"", 0);
              #endif
            }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 580 "parser.yy"
    {

              (yyval) = new UnaryExprNode((yyvsp[(3) - (3)]), UnaryExprNode::EXIST_OP);
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_EXIST TK_DOLLAR Component\"", 0);
              #endif
            }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 594 "parser.yy"
    {
              (yyval) = (yyvsp[(2) - (2)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_DOLLAR Component\"", 0);
              #endif
            }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 602 "parser.yy"
    {
              (yyval) = new UnaryExprNode((yyvsp[(3) - (3)]), UnaryExprNode::DEFAULT_OP);
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_DEFAULT TK_DOLLAR Component\"", 0);
              #endif
            }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 617 "parser.yy"
    {
              /* No component */
              (yyval) = new VoidPath;
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"Component ::= <lambda>\"", 0);
              #endif
            }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 630 "parser.yy"
    {
              (yyval) = (yyvsp[(2) - (2)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"Component ::= TK_DOT CompDot\"", 0);
              #endif
            }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 638 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"Component ::= CompArray\"", 0);
              #endif
            }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 646 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"Component ::= CompAssoc\"", 0);
              #endif
            }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 654 "parser.yy"
    {
              try
              {
                (yyval) = RuntimeVariableTable::get_evaluable_value(
                  *dynamic_cast<IdentifierValueNode*>((yyvsp[(1) - (2)])));
              }
              catch (...)
              {
                yyerror("unknow runtime variable");
                YYERROR;
              }
              TIDParser::push_tmp_node((yyval));
              #ifdef DEBUG_ENABLED
              Debugger::register_free((yyvsp[(1) - (2)]));
              #endif
              delete (yyvsp[(1) - (2)]);
            }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 674 "parser.yy"
    {
              /* No component */
              (yyval) = new VoidPath;
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"Component ::= <lambda>\"", 0);
              #endif
            }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 687 "parser.yy"
    {
              (yyval) = (yyvsp[(2) - (2)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompExt ::= TK_DOT CompDot\"", 0);
              #endif
            }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 695 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompExt ::= CompArray\"", 0);
              #endif
            }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 703 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompExt ::= CompAssoc\"", 0);
              #endif
            }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 713 "parser.yy"
    {
              (yyval) = new StructFieldNamePath(
                dynamic_cast<SequencePath*>((yyvsp[(2) - (2)])),
                dynamic_cast<IdentifierValueNode*>((yyvsp[(1) - (2)]))->get_name().c_str());
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
						  #ifdef DEBUG_ENABLED
							Debugger::register_free((yyvsp[(1) - (2)]));
  						#endif
              delete (yyvsp[(1) - (2)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= TK_IDENT CompExt\"", 0);
              #endif
            }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 733 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= CompPos\"", 0);
              #endif
            }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 741 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= UnionPos\"", 0);
              #endif
            }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 749 "parser.yy"
    {
              (yyval) = new StructFieldNamePath(NULL, "_length");
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= TK__LENGTH\"", 0);
              #endif
            }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 761 "parser.yy"
    {
              (yyval) = new StructFieldNamePath(NULL, "_d");
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= TK__D\"", 0);
              #endif
            }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 773 "parser.yy"
    {
              (yyval) = new StructFieldNamePath(NULL, "_type_id");
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= TK__TYPE_ID\"", 0);
              #endif
            }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 785 "parser.yy"
    {
              (yyval) = new StructFieldNamePath(NULL, "_repos_id");
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= TK__REPOS_ID\"", 0);
              #endif
            }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 799 "parser.yy"
    {
              (yyval) = new ArrayPath(
                dynamic_cast<SequencePath*>((yyvsp[(4) - (4)])),
                dynamic_cast<LongValueNode*>((yyvsp[(2) - (4)]))->get_value());
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
						  #ifdef DEBUG_ENABLED
							Debugger::register_free((yyvsp[(2) - (4)]));
  						#endif
              delete (yyvsp[(2) - (4)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompArray ::= TK_OPENBRA TK_LONG TK_CLOSEBRA CompExt\"", 0);
              #endif
            }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 821 "parser.yy"
    {
              (yyval) = NULL;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompAssoc ::= TK_OPENPAR TK_IDENT TK_CLOSEPAR CompExt\"", 0);
              #endif
            }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 831 "parser.yy"
    {
              (yyval) = new StructFieldPosPath(
                dynamic_cast<SequencePath*>((yyvsp[(2) - (2)])),
                dynamic_cast<LongValueNode*>((yyvsp[(1) - (2)]))->get_value());
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
						  #ifdef DEBUG_ENABLED
							Debugger::register_free((yyvsp[(1) - (2)]));
  						#endif
              delete (yyvsp[(1) - (2)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompPos ::= TK_LONG CompExt\"", 0);
              #endif
            }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 853 "parser.yy"
    {
              if (!(yyvsp[(2) - (4)]))
              {
                (yyval) = new UnionDefaultSwitchPath(
                  dynamic_cast<SequencePath*>((yyvsp[(4) - (4)])));
                TIDParser::pop_tmp_node();
                TIDParser::push_tmp_node((yyval));
							  #ifdef DEBUG_ENABLED
								Debugger::register_malloc((yyval));
  							#endif
              }
              else if (typeid(*(yyvsp[(2) - (4)])) == typeid(LongValueNode))
              {
                (yyval) = new UnionIntSwitchPath(
                  dynamic_cast<SequencePath*>((yyvsp[(4) - (4)])),
                  dynamic_cast<LongValueNode*>((yyvsp[(2) - (4)]))->get_value());
                TIDParser::pop_tmp_node();
                TIDParser::pop_tmp_node();
                TIDParser::push_tmp_node((yyval));
							  #ifdef DEBUG_ENABLED
								Debugger::register_malloc((yyval));
  							#endif
							  #ifdef DEBUG_ENABLED
								Debugger::register_free((yyvsp[(2) - (4)]));
  							#endif
                delete (yyvsp[(2) - (4)]);
              }
              else if (typeid(*(yyvsp[(2) - (4)])) == typeid(StringValueNode))
              {
                (yyval) = new UnionStringSwitchPath(
                  dynamic_cast<SequencePath*>((yyvsp[(4) - (4)])),
                  dynamic_cast<StringValueNode*>((yyvsp[(2) - (4)]))->get_value());
                TIDParser::pop_tmp_node();
                TIDParser::pop_tmp_node();
                TIDParser::push_tmp_node((yyval));
							  #ifdef DEBUG_ENABLED
								Debugger::register_malloc((yyval));
  							#endif
							  #ifdef DEBUG_ENABLED
								Debugger::register_free((yyvsp[(2) - (4)]));
  							#endif
                delete (yyvsp[(2) - (4)]);
              }
              else
                throw CORBA::INTERNAL(
                  "Unexpected semantic value in grammar");
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"UnionPos ::= TK_OPENPAR UnionVal TK_CLOSEPAR CompExt\"", 0);
              #endif
            }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 907 "parser.yy"
    {
              (yyval) = NULL;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"UnionVal ::= <lambda>\"", 0);
              #endif
            }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 915 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"UnionVal ::= TK_LONG\"", 0);
              #endif
            }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 923 "parser.yy"
    {
              dynamic_cast<LongValueNode*>((yyvsp[(2) - (2)]))->invert_sign();
              (yyval) = (yyvsp[(2) - (2)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"UnionVal ::= TK_MINUS TK_LONG\"", 0);
              #endif
            }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 932 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (2)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"UnionVal ::= TK_ADD TK_LONG\"", 0);
              #endif
            }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 940 "parser.yy"
    {
              (yyval) = (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"UnionVal ::= TK_STRING\"", 0);
              #endif
            }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 950 "parser.yy"
    {
            	(yyval) = (yyvsp[(3) - (3)]);
            	dynamic_cast<StringArrayValueNode*>((yyval))->add_member(
                dynamic_cast<StringValueNode*>((yyvsp[(1) - (3)]))->get_value().data());
              /* String stored at $1 is not needed anymore. */
						  #ifdef DEBUG_ENABLED
							Debugger::register_free((yyvsp[(1) - (3)]));
  						#endif
              delete (yyvsp[(1) - (3)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"LiteralArray ::= TK_STRING TK_COMMA LiteralArray\"", 0);
              #endif
            }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 965 "parser.yy"
    {
              (yyval) = new StringArrayValueNode(
                dynamic_cast<StringValueNode*>((yyvsp[(1) - (1)]))->get_value().data());
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node((yyval));
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc((yyval));
  						#endif
              /* String stored at $1 is not needed anymore. */
						  #ifdef DEBUG_ENABLED
							Debugger::register_free((yyvsp[(1) - (1)]));
  						#endif
              delete (yyvsp[(1) - (1)]);
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"LiteralArray ::= TK_STRING\"", 0);
              #endif
            }
    break;



/* Line 1455 of yacc.c  */
#line 2707 "parser.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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
		      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 985 "parser.yy"


void yyerror(char* msg)
{
  #ifdef DEBUG_ENABLED
  Debugger::send_message(90, "Syntax error in constraint:", 0);
  Debugger::send_message(90, msg, 0);
  #endif

  /* Free allocated memory. */
  TIDParser::free_tmp_node_stack();

  /* Destroy parsed tree. */
  if (TIDParser::tmp_constraint)
  {
    #ifdef DEBUG_ENABLED
    Debugger::register_free(TIDParser::tmp_constraint);
    #endif
    delete TIDParser::tmp_constraint;
  }
}

