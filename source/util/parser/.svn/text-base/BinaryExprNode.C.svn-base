/*
 *  File name: BinaryExprNode.C
 *  File type: Body file.
 *  Date : March 14th 2006
 *  Author: Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 */

/*
// (C) Copyright 2009 Telefonica Investigacion y Desarrollo
 *
//     S.A.Unipersonal (Telefonica I+D)
//
// This file is part of Morfeo CORBA Platform.
//
// Morfeo CORBA Platform is free software: you can redistribute it and/or
// modify it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// Morfeo CORBA Platform is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with Morfeo CORBA Platform. If not, see
//
//   http://www.gnu.org/licenses
//
// Info about members and contributors of the MORFEO project
// is available at
//
//   http://morfeo-project.org
 */

/*
 * Revision historial:
 *   - 03/31/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added code for allocated memory debugging purposes.
 *   - 04/10/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Tilde operator implemented and executed from TypeValuePair
 *         instead of BinaryExprNode.
 *   - 04/11/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * In member function 'BinaryEprNode::operate(...)', left
 *         and right hand operands are evaluated before any operation
 *         is done. In case of a 'in' operator with '<string> in 
 *         <string array>' form, left hand is evaluated and it's type
 *         is checked to be a string before operate or raise
 *         an error.
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 */

#include <CORBA.h>

#include "BinaryExprNode.h"
#include "SequencePath.h"
#include "StringValueNode.h"
#include "StringArrayValueNode.h"
#include "Debugger.h"

namespace TIDNotif {
namespace util {
namespace parser{

/* Default constructor. */
BinaryExprNode::BinaryExprNode(EvaluableNode * left_expression,
                               EvaluableNode * right_expression,
                               Operator op)
: 
EvaluableNode(),
m_left_expr(left_expression),
m_right_expr(right_expression),
m_op(op)
{}

/* Destructor. */
BinaryExprNode::~BinaryExprNode()
{
  if (m_left_expr)
  {
    #ifdef DEBUG_ENABLED
    Debugger::register_free(m_left_expr);
    #endif
    delete m_left_expr;
  }
  if (m_right_expr)
  {
    #ifdef DEBUG_ENABLED
    Debugger::register_free(m_right_expr);
    #endif
    delete m_right_expr;
  }
}

/* Evaluate an object in a filter expression. */
TypeValuePair
BinaryExprNode::evaluate(DynamicAny::DynAny_ptr dynany) const
{
  const SequencePath * seq_path;
  const StringArrayValueNode * str_array;
//   const StringValueNode * left_str_expr;
//   const StringValueNode * right_str_expr;

  TypeValuePair left_eval = m_left_expr->evaluate(dynany);
  TypeValuePair right_eval = m_right_expr->evaluate(dynany);
  seq_path = dynamic_cast<const SequencePath*>(m_right_expr);
  str_array = dynamic_cast<const StringArrayValueNode*>(m_right_expr);

  try
  {
    switch (m_op)
    {
      case ADD_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator '+'", this);
        #endif
        return left_eval + right_eval;
      case SUB_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator '-'", this);
        #endif
        return left_eval - right_eval;
      case MUL_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator '*'", this);
        #endif
        return left_eval * right_eval;
      case DIV_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator '/'", this);
        #endif
        return left_eval / right_eval;
      case MOD_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator '%'", this);
        #endif
        return left_eval % right_eval;
      case AND_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator AND", this);
        #endif
        return left_eval && right_eval;
      case OR_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator OR", this);
        #endif
        return left_eval || right_eval;
      case EQUAL_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator '=='", this);
        #endif
        return left_eval == right_eval;
      case NOT_EQUAL_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator '!='", this);
        #endif
        return left_eval != right_eval;
      case GREATER_THAN_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator '>'", this);
        #endif
        return left_eval > right_eval;
      case GREATER_OR_EQUAL_THAN_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator '>='", this);
        #endif
        return left_eval >= right_eval;
      case LESS_THAN_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator '<'", this);
        #endif
        return left_eval < right_eval;
      case LESS_OR_EQUAL_THAN_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator '<='", this);
        #endif
        return left_eval <= right_eval;
      case IN_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator 'in'", this);
        #endif
        if (seq_path)
          return seq_path->evaluate_in_operation(left_eval, dynany);
        else if (str_array && 
                 left_eval.get_type() == TypeValuePair::STRING_TYPE)
          return TypeValuePair::create_boolean(str_array->search_string(
            left_eval.get_value_as_string().c_str()));
        else
        {
          #ifdef DEBUG_ENABLED
          Debugger::send_message(80, 
            "non sequence path for 'in' operator", this);
          #endif
          return TypeValuePair::create_error(
            "non sequence path for 'in' operator");
        }
      case TILDE_OP:
        #ifdef DEBUG_ENABLED
        Debugger::send_message(80, "evaluating operator '~'", this);
        #endif
        return left_eval.operator_tilde(right_eval);
    }
  }
  catch (TypeValuePair::TypeCheckError & e)
  {
    Debugger::send_message(80, e.get_cause().data(), this);
    return TypeValuePair::create_error(e.get_cause().c_str());
  }
  return TypeValuePair::create_error("Operator not found. Never reached.");
}

/* Copy this node. */
EvaluableNode *
BinaryExprNode::copy() const
{
  BinaryExprNode * node;

  node = new BinaryExprNode(m_left_expr->copy(),
                            m_right_expr->copy(),
                            m_op);
  #ifdef DEBUG_ENABLED
  util::parser::Debugger::register_malloc(node);
  #endif
  return node;
}

} /* End of namespace parser.  */
} /* End of namespace util. */
} /* End of namespace TIDNotif. */

