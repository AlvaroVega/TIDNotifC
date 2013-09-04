
%{

/*
 *  File name: scanner.ll
 *  File type: Flex source file.
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
 *       * Each node created in heap is inserted in 'TIDParser::tmp_nodes'.
 *       * Long and double value overflow and underflow control.
 *       * Temporarily stored nodes are now saved in 
 *         'TIDParser::tmp_node_stack' stack object instead of using
 *         'TIDParser::tmp_nodes' linked list to avoid multiple sides memory
 *         deallocation.
 *   - 04/10/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * In number scanning, errno must be set to 0 before function
 *         strto{d|l} is called to detect error correctly.
 *   - 04/17/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Double token pattern changed to disallow a heading dollar or letter.
 *   - 04/19/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * TK_VALUE renamed to TK_DOLLAR.
 *   - 30/01/2009 by Alvaro Vega Garcia <avega at tid dot es>
 *       * Added errno header inclusion
 */

#define DEBUGGING

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/* Parser static class include. */
#include "TIDParser.h"

/* Base node class. */
#include "EvaluableNode.h"

/* Inmediate value node types include. */
#include "BooleanValueNode.h"
#include "LongValueNode.h"
#include "DoubleValueNode.h"
#include "StringValueNode.h"

/* Other value nodes. */
#include "IdentifierValueNode.h"

#include "Debugger.h"

#define YYSTYPE TIDNotif::util::parser::EvaluableNode*

#include "parser.h"


void yyerror(char *);
%}

%%

"exist" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_EXISTS", 
    0);
  #endif

  return TK_EXIST;
}

"default" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_DEFAULT", 
    0);
  #endif

  return TK_DEFAULT;
}

"~" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_TILDE_ACCENT", 
    0);
  #endif

  return TK_TILDE_ACCENT;
}

"in" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_IN", 
    0);
  #endif

  return TK_IN;
}

"==" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_EQ", 
    0);
  #endif

  return TK_EQ;
}

"!=" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_DIF", 
    0);
  #endif

  return TK_DIF;
}

"<" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_LESS", 
    0);
  #endif

  return TK_LESS;
}

"<=" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_LESSEQ", 
    0);
  #endif

  return TK_LESSEQ;
}

">" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_GREAT", 
    0);
  #endif

  return TK_GREAT;
}

">=" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_GREATEQ", 
    0);
  #endif

  return TK_GREATEQ;
}

"*" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_MUL", 
    0);
  #endif

  return TK_MUL;
}

"/" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_DIV", 
    0);
  #endif

  return TK_DIV;
}

"%" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_MOD", 
    0);
  #endif

  return TK_MOD;
}

"+" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_ADD", 
    0);
  #endif

  return TK_ADD;
}

"-" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_MINUS", 
    0);
  #endif

  return TK_MINUS;
}

"," {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_COMMA", 
    0);
  #endif

  return TK_COMMA;
}

"not" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_NOT", 
    0);
  #endif

  return TK_NOT;
}

"and" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_AND", 
    0);
  #endif

  return TK_AND;
}

"or" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_OR", 
    0);
  #endif

  return TK_OR;
}

"TRUE" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_BOOL; value: TRUE", 
    0);
  #endif

  yylval = new TIDNotif::util::parser::BooleanValueNode(true);
  TIDNotif::util::parser::TIDParser::push_tmp_node(yylval);
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::register_malloc(yylval);
  #endif
  return TK_BOOL;
}

"FALSE" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_BOOL; value: false", 
    0);
  #endif

  yylval = new TIDNotif::util::parser::BooleanValueNode(false);
  TIDNotif::util::parser::TIDParser::push_tmp_node(yylval);
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::register_malloc(yylval);
  #endif
  return TK_BOOL;
}



"'"[^'\n]*[\'\n] {
  /*
    TODO_MORFEO: special characters like \ and ' are a problem. 
    Example: 'I have a \'car\' ' so the string is: I have a 'car'
  */

  yytext[yyleng-1] = '\0';
  yylval = new TIDNotif::util::parser::StringValueNode(yytext+1);
  TIDNotif::util::parser::TIDParser::push_tmp_node(yylval);
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::register_malloc(yylval);
  #endif

  #ifdef DEBUG_ENABLED
  char b[255];
  sprintf(b, "Token scanned: TK_STRING; value: %s",
          yytext+1);
  TIDNotif::util::parser::Debugger::send_message(100, b, 0);
  #endif

  return TK_STRING;
}

"." {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_DOT", 
    0);
  #endif

  return TK_DOT;
}

"$" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_DOLLAR", 
    0);
  #endif

  return TK_DOLLAR;
}

"_length" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK__LENGTH", 
    0);
  #endif

  return TK__LENGTH;
}

"_d" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK__D", 
    0);
  #endif

  return TK__D;
}

"_type_id" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK__TYPE_ID", 
    0);
  #endif

  return TK__TYPE_ID;
}

"_repos_id" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK__REPOS_ID", 
    0);
  #endif

  return TK__REPOS_ID;
}

"(" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_OPENPAR", 
    0);
  #endif

  return TK_OPENPAR;
}

")" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_CLOSEPAR", 
    0);
  #endif

  return TK_CLOSEPAR;
}

"[" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_OPENBRA", 
    0);
  #endif

  return TK_OPENBRA;
}

"]" {
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::send_message(
    100, 
    "Token scanned: TK_CLOSEBRA", 
    0);
  #endif

  return TK_CLOSEBRA;
}


[\\]?[a-zA-Z][a-zA-Z0-9_]* {
  #ifdef DEBUG_ENABLED
  char b[255];
  sprintf(b, "Token scanned: TK_IDENT; value: %s",
          yytext);
  TIDNotif::util::parser::Debugger::send_message(100, b, 0);
  #endif

  yylval = new TIDNotif::util::parser::IdentifierValueNode(yytext);
  TIDNotif::util::parser::TIDParser::push_tmp_node(yylval);

  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::register_malloc(yylval);
  #endif

  return TK_IDENT;
}

[^\$A-Za-z][0-9]*"."[0-9]*([eE][+-][0-9]+)? {
  double val;

  errno = 0;
  val = strtod(yytext, NULL);
  if (errno == ERANGE)
  {
    yyerror("range overflow in double literal");
    yyterminate();
  }

  #ifdef DEBUG_ENABLED
  char b[255];
  sprintf(b, "Token scanned: TK_DOUBLE; value: %f", val);
  TIDNotif::util::parser::Debugger::send_message(100, b, 0);
  #endif

  yylval = new TIDNotif::util::parser::DoubleValueNode(val);
  TIDNotif::util::parser::TIDParser::push_tmp_node(yylval);

  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::register_malloc(yylval);
  #endif

  return TK_DOUBLE;
}

[0-9]+ {
  long val;

  errno = 0;
  val = strtol(yytext, NULL, 10);
  if (errno == ERANGE)
  {
    yyerror("range overflow in long literal");
    yyterminate();
  }

  #ifdef DEBUG_ENABLED
  char b[255];
  sprintf(b, "Token scanned: TK_LONG; value: %d", val);
  TIDNotif::util::parser::Debugger::send_message(100, b, 0);
  #endif

  yylval = new TIDNotif::util::parser::LongValueNode(val);
  TIDNotif::util::parser::TIDParser::push_tmp_node(yylval);
  #ifdef DEBUG_ENABLED
  TIDNotif::util::parser::Debugger::register_malloc(yylval);
  #endif
  return TK_LONG;
}

[\t ]+ {
}




%%
int 
yywrap(void)
{
  return 1;
}
