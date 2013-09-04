
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

extern YYSTYPE yylval;


