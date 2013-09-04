%{

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

%}

%token TK_EXIST;
%token TK_DEFAULT;
%token TK_TILDE_ACCENT;
%token TK_IN;
%token TK_EQ;
%token TK_DIF;
%token TK_LESS;
%token TK_LESSEQ;
%token TK_GREAT;
%token TK_GREATEQ;
%token TK_MUL;
%token TK_DIV;
%token TK_MOD;
%token TK_ADD;
%token TK_MINUS;
%token TK_NOT;
%token TK_AND;
%token TK_OR;
%token TK_COMMA;
%token TK_BOOL;
%token TK_STRING;
%token TK_DOT;
%token TK_DOLLAR;
%token TK__LENGTH;
%token TK__D;
%token TK__TYPE_ID;
%token TK__REPOS_ID;
%token TK_OPENPAR;
%token TK_CLOSEPAR;
%token TK_OPENBRA;
%token TK_CLOSEBRA;
%token TK_IDENT;
%token TK_DOUBLE;
%token TK_LONG;
%token TK_INDEX;


/*
%type constraint bool bool_or bool_and bool_compare
     expr_in expr_twiddle expr term factor_not factor 
     Component CompExt CompDot CompArray CompAssoc CompPos UnionPos UnionVal LiteralArray
*/

%left TK_OR
%left TK_AND
%left TK_EQ TK_DIF TK_LESS TK_LESSEQ TK_GREAT TK_GREATEQ
%left TK_IN
%left TK_TILDE_ACCENT
%left TK_ADD TK_MINUS
%left TK_MUL TK_DIV
%left TK_NOT
%left TK_OPENPAR TK_CLOSEPAR TK_EXIST TK_DEFAULT
%left TK_DOT


%%

start       : constraint
            {
              TIDParser::tmp_constraint = new TIDConstraint;
              #ifdef DEBUG_ENABLED
              Debugger::register_malloc(TIDParser::tmp_constraint);
              #endif
              TIDParser::tmp_constraint->addRoot($1);
              TIDParser::clear_tmp_node_stack();
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"start ::= constraint\"", 0);
              #endif
            }
            ;

constraint  : /* empty */
            {
              $$ = NULL;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"constraint ::= <lambda>\"", 0);
              #endif
            }
            | bool
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"constraint ::= bool\"", 0);
              #endif
            }
            ;

bool        : bool_or
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool ::= bool_or\"", 0);
              #endif
            }
            ;

bool_or     : bool_or TK_OR bool_and
            {
              $$ = new BinaryExprNode($1, $3, BinaryExprNode::OR_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_or ::= bool_or TK_OR bool_and\"", 0);
              #endif
            }
            | bool_and
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_or ::= bool_and\"", 0);
              #endif
            }
            ;

bool_and    : bool_and TK_AND bool_compare
            {
              $$ = new BinaryExprNode($1, $3, BinaryExprNode::AND_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
               Debugger::send_message(90,
                "Reducing rule \"bool_and ::= bool_and TK_AND bool_compare\"", 
                0);
              #endif
           }
            | bool_compare
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_and ::= bool_compare\"", 0);
              #endif
            }
            ;

bool_compare: expr_in TK_EQ expr_in
            {
              $$ = new BinaryExprNode($1, $3, BinaryExprNode::EQUAL_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in TK_EQ expr_in\"", 0);
              #endif
            }
            | expr_in TK_DIF expr_in
            {
              $$ = new BinaryExprNode($1, $3, BinaryExprNode::NOT_EQUAL_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in TK_DIF expr_in\"", 0);
              #endif
            }
            | expr_in TK_LESS expr_in
            {
              $$ = new BinaryExprNode($1, $3, BinaryExprNode::LESS_THAN_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in TK_LESS expr_in\"", 0);
              #endif
            }
            | expr_in TK_LESSEQ expr_in
            {
              $$ = new BinaryExprNode($1, $3, 
                BinaryExprNode::LESS_OR_EQUAL_THAN_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in TK_LESSEQ expr_in\"", 0);
              #endif
            }
            | expr_in TK_GREAT expr_in
            {
              $$ = new BinaryExprNode($1, $3, BinaryExprNode::GREATER_THAN_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in TK_GREAT expr_in\"", 0);
              #endif
            }
            | expr_in TK_GREATEQ expr_in
            {
              $$ = new BinaryExprNode($1, $3, 
              	BinaryExprNode::GREATER_OR_EQUAL_THAN_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in TK_GREATEQ expr_in\"", 0);
              #endif
            }
            | expr_in
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"bool_compare ::= expr_in\"", 0);
              #endif
            }
            ;

expr_in     : expr_twiddle TK_IN TK_IDENT
            {
              /* It's not considered by the grammar but TID considers it */
              $$ = NULL;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr_in ::= expr_twiddle TK_IN TK_IDENT\"", 
                0);
              #endif
            }
            | expr_twiddle
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr_in ::= expr_twiddle\"", 
                0);
               #endif
            }
            | expr_twiddle TK_IN TK_DOLLAR Component
            {
              $$ = new BinaryExprNode($1, $4, BinaryExprNode::IN_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr_in ::= expr_twiddle TK_IN TK_DOLLAR Component\"", 
                0);
              #endif
            }
            | expr_twiddle TK_IN TK_OPENPAR LiteralArray TK_CLOSEPAR
            {
              /* It's not considered by the grammar but TID considers it */
              $$ = new BinaryExprNode($1, $4, BinaryExprNode::IN_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr_in ::= expr_twiddle TK_IN TK_OPENPAR LiteralArray TK_CLOSEPAR\"", 
                0);
              #endif
            }
            ;

expr_twiddle: expr TK_TILDE_ACCENT expr
            {
              $$ = new BinaryExprNode($1, $3, BinaryExprNode::TILDE_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr_twiddle ::= expr TK_TILDE_ACCENT expr\"", 
                0);
              #endif
            }
            | expr
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr_twiddle ::= expr\"", 
                0);
              #endif
            }
            ;

expr        : expr TK_ADD term
            {
              $$ = new BinaryExprNode($1, $3, BinaryExprNode::ADD_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr ::= expr TK_ADD term\"", 0);
              #endif
            }
            | expr TK_MINUS term
            {
              $$ = new BinaryExprNode($1, $3, BinaryExprNode::SUB_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr ::= expr TK_MINUS term\"", 0);
              #endif
            }
            | term
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"expr ::= term\"", 0);
              #endif
            }
            ;

term        : term TK_MUL factor_not
            {
              $$ = new BinaryExprNode($1, $3, BinaryExprNode::MUL_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
        	    #ifdef DEBUG_ENABLED
          	  Debugger::send_message(90,
            	  "Reducing rule \"term ::= term TK_MUL factor_not\"", 0);
              #endif
            }
            | term TK_DIV factor_not
            {
              $$ = new BinaryExprNode($1, $3, BinaryExprNode::DIV_OP);
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"term ::= term TK_DIV factor_not\"", 0);
              #endif
            }
            | factor_not
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"term ::= factor_not\"", 0);
              #endif
            }
            ;

factor_not  : TK_NOT factor
            {
              $$ = new UnaryExprNode($2, UnaryExprNode::NOT_OP);
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor_not ::= TK_NOT factor\"", 0);
              #endif
            }
            | factor
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor_not ::= factor\"", 0);
              #endif
            }
            ;

factor      : TK_OPENPAR bool_or TK_CLOSEPAR 
            {
              $$ = $2;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_OPENPAR bool_or TK_CLOSEPAR\"", 0);
              #endif
            }
            | TK_EXIST TK_IDENT
            {
              $$ = new UnaryExprNode($2, UnaryExprNode::EXIST_OP);
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_EXIST TK_IDENT\"", 0);
              #endif
            }
            | TK_IDENT
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_IDENT\"", 0);
              #endif
            }
            | TK_DOUBLE
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_DOUBLE\"", 0);
              #endif
            }
            | TK_MINUS TK_DOUBLE
            {
              dynamic_cast<DoubleValueNode*>($2)->invert();
              $$ = $2;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_MINUS TK_DOUBLE\"", 0);
              #endif
            }
            | TK_LONG
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_LONG\"", 0);
              #endif
            }
            | TK_MINUS TK_LONG
            {
              dynamic_cast<LongValueNode*>($2)->invert_sign();
              $$ = $2;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_MINUS TK_LONG\"", 0);
              #endif
            }
            | TK_STRING
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_STRING\"", 0);
              #endif
            }
            | TK_BOOL
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_BOOL\"", 0);
              #endif
            }
            | TK_EXIST TK_DOLLAR Component
            {

              $$ = new UnaryExprNode($3, UnaryExprNode::EXIST_OP);
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_EXIST TK_DOLLAR Component\"", 0);
              #endif
            }
            | TK_DOLLAR Component
            {
              $$ = $2;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_DOLLAR Component\"", 0);
              #endif
            }
            | TK_DEFAULT TK_DOLLAR Component
            {
              $$ = new UnaryExprNode($3, UnaryExprNode::DEFAULT_OP);
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"factor ::= TK_DEFAULT TK_DOLLAR Component\"", 0);
              #endif
            }
            ;

Component   : /* Empty. */
            {
              /* No component */
              $$ = new VoidPath;
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"Component ::= <lambda>\"", 0);
              #endif
            }
            | TK_DOT CompDot
            {
              $$ = $2;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"Component ::= TK_DOT CompDot\"", 0);
              #endif
            }
            | CompArray
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"Component ::= CompArray\"", 0);
              #endif
            }
            | CompAssoc
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"Component ::= CompAssoc\"", 0);
              #endif
            }
            | TK_IDENT CompExt
            {
              try
              {
                $$ = RuntimeVariableTable::get_evaluable_value(
                  *dynamic_cast<IdentifierValueNode*>($1));
              }
              catch (...)
              {
                yyerror("unknow runtime variable");
                YYERROR;
              }
              TIDParser::push_tmp_node($$);
              #ifdef DEBUG_ENABLED
              Debugger::register_free($1);
              #endif
              delete $1;
            }
            ;

CompExt     : /* Empty. */
            {
              /* No component */
              $$ = new VoidPath;
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"Component ::= <lambda>\"", 0);
              #endif
            }
            | TK_DOT CompDot
            {
              $$ = $2;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompExt ::= TK_DOT CompDot\"", 0);
              #endif
            }
            | CompArray
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompExt ::= CompArray\"", 0);
              #endif
            }
            | CompAssoc
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompExt ::= CompAssoc\"", 0);
              #endif
            }
            ;

CompDot     : TK_IDENT CompExt
            {
              $$ = new StructFieldNamePath(
                dynamic_cast<SequencePath*>($2),
                dynamic_cast<IdentifierValueNode*>($1)->get_name().c_str());
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
						  #ifdef DEBUG_ENABLED
							Debugger::register_free($1);
  						#endif
              delete $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= TK_IDENT CompExt\"", 0);
              #endif
            }
            | CompPos
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= CompPos\"", 0);
              #endif
            }
            | UnionPos
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= UnionPos\"", 0);
              #endif
            }
            | TK__LENGTH
            {
              $$ = new StructFieldNamePath(NULL, "_length");
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= TK__LENGTH\"", 0);
              #endif
            }
            | TK__D
            {
              $$ = new StructFieldNamePath(NULL, "_d");
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= TK__D\"", 0);
              #endif
            }
            | TK__TYPE_ID
            {
              $$ = new StructFieldNamePath(NULL, "_type_id");
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= TK__TYPE_ID\"", 0);
              #endif
            }
            | TK__REPOS_ID
            {
              $$ = new StructFieldNamePath(NULL, "_repos_id");
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompDot ::= TK__REPOS_ID\"", 0);
              #endif
            }
            ;

CompArray   : TK_OPENBRA TK_LONG TK_CLOSEBRA CompExt
            {
              $$ = new ArrayPath(
                dynamic_cast<SequencePath*>($4),
                dynamic_cast<LongValueNode*>($2)->get_value());
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
						  #ifdef DEBUG_ENABLED
							Debugger::register_free($2);
  						#endif
              delete $2;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompArray ::= TK_OPENBRA TK_LONG TK_CLOSEBRA CompExt\"", 0);
              #endif
            }
            ;

CompAssoc   : TK_OPENPAR TK_IDENT TK_CLOSEPAR CompExt
            {
              $$ = NULL;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompAssoc ::= TK_OPENPAR TK_IDENT TK_CLOSEPAR CompExt\"", 0);
              #endif
            }
            ;

CompPos     : TK_LONG CompExt
            {
              $$ = new StructFieldPosPath(
                dynamic_cast<SequencePath*>($2),
                dynamic_cast<LongValueNode*>($1)->get_value());
              TIDParser::pop_tmp_node();
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
						  #ifdef DEBUG_ENABLED
							Debugger::register_free($1);
  						#endif
              delete $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"CompPos ::= TK_LONG CompExt\"", 0);
              #endif
            }
            ;

UnionPos    : TK_OPENPAR UnionVal TK_CLOSEPAR CompExt
            {
              if (!$2)
              {
                $$ = new UnionDefaultSwitchPath(
                  dynamic_cast<SequencePath*>($4));
                TIDParser::pop_tmp_node();
                TIDParser::push_tmp_node($$);
							  #ifdef DEBUG_ENABLED
								Debugger::register_malloc($$);
  							#endif
              }
              else if (typeid(*$2) == typeid(LongValueNode))
              {
                $$ = new UnionIntSwitchPath(
                  dynamic_cast<SequencePath*>($4),
                  dynamic_cast<LongValueNode*>($2)->get_value());
                TIDParser::pop_tmp_node();
                TIDParser::pop_tmp_node();
                TIDParser::push_tmp_node($$);
							  #ifdef DEBUG_ENABLED
								Debugger::register_malloc($$);
  							#endif
							  #ifdef DEBUG_ENABLED
								Debugger::register_free($2);
  							#endif
                delete $2;
              }
              else if (typeid(*$2) == typeid(StringValueNode))
              {
                $$ = new UnionStringSwitchPath(
                  dynamic_cast<SequencePath*>($4),
                  dynamic_cast<StringValueNode*>($2)->get_value());
                TIDParser::pop_tmp_node();
                TIDParser::pop_tmp_node();
                TIDParser::push_tmp_node($$);
							  #ifdef DEBUG_ENABLED
								Debugger::register_malloc($$);
  							#endif
							  #ifdef DEBUG_ENABLED
								Debugger::register_free($2);
  							#endif
                delete $2;
              }
              else
                throw CORBA::INTERNAL(
                  "Unexpected semantic value in grammar");
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"UnionPos ::= TK_OPENPAR UnionVal TK_CLOSEPAR CompExt\"", 0);
              #endif
            }
            ;

UnionVal    : /* empty */
            {
              $$ = NULL;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"UnionVal ::= <lambda>\"", 0);
              #endif
            }
            | TK_LONG
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"UnionVal ::= TK_LONG\"", 0);
              #endif
            }
            | TK_MINUS TK_LONG
            {
              dynamic_cast<LongValueNode*>($2)->invert_sign();
              $$ = $2;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"UnionVal ::= TK_MINUS TK_LONG\"", 0);
              #endif
            }
            | TK_ADD TK_LONG
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"UnionVal ::= TK_ADD TK_LONG\"", 0);
              #endif
            }
            | TK_STRING
            {
              $$ = $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"UnionVal ::= TK_STRING\"", 0);
              #endif
            }
            ;

LiteralArray: TK_STRING TK_COMMA LiteralArray
            {
            	$$ = $3;
            	dynamic_cast<StringArrayValueNode*>($$)->add_member(
                dynamic_cast<StringValueNode*>($1)->get_value().data());
              /* String stored at $1 is not needed anymore. */
						  #ifdef DEBUG_ENABLED
							Debugger::register_free($1);
  						#endif
              delete $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"LiteralArray ::= TK_STRING TK_COMMA LiteralArray\"", 0);
              #endif
            }
            | TK_STRING 
            {
              $$ = new StringArrayValueNode(
                dynamic_cast<StringValueNode*>($1)->get_value().data());
              TIDParser::pop_tmp_node();
              TIDParser::push_tmp_node($$);
						  #ifdef DEBUG_ENABLED
							Debugger::register_malloc($$);
  						#endif
              /* String stored at $1 is not needed anymore. */
						  #ifdef DEBUG_ENABLED
							Debugger::register_free($1);
  						#endif
              delete $1;
              #ifdef DEBUG_ENABLED
              Debugger::send_message(90,
                "Reducing rule \"LiteralArray ::= TK_STRING\"", 0);
              #endif
            }
            ;

%%

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
