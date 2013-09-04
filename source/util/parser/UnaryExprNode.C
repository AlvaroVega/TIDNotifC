/*
 *  File name: UnaryExprNode.C
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
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 */

#include "UnaryExprNode.h"
#include "InmediateValueNode.h"

#include <CORBA.h>

#include "Debugger.h"

namespace TIDNotif {
namespace util {
namespace parser{

/* Default constructor. */
UnaryExprNode::UnaryExprNode(EvaluableNode * expression, Operator op)
: 
EvaluableNode(),
m_expression(expression),
m_op(op)
{}

/* Destructor. */
UnaryExprNode::~UnaryExprNode()
{
  #ifdef DEBUG_ENABLED
  Debugger::register_free(m_expression);
  #endif
  delete m_expression;
}

/* Evaluate an object in a filter expression. */
TypeValuePair
UnaryExprNode::evaluate(DynamicAny::DynAny_ptr dynany) const
{
  try
  {
    switch (m_op)
    {
      case NOT_OP:
        return !(m_expression->evaluate(dynany));
      default:
        break;
    }
  }
  catch (TypeValuePair::TypeCheckError & e)
  {
    return TypeValuePair::create_error(e.get_cause().c_str());
  }
  return TypeValuePair::create_error("Operator not found");
}

/* Reduce this node if possible. */
EvaluableNode *
UnaryExprNode::reduce() const
{
  if (dynamic_cast<InmediateValueNode*>(m_expression))
    try
    {
      return evaluate(NULL).converto_to_inmediate_value_node();
    }
    catch (TypeValuePair::TypeCheckError & e)
    {
      return NULL;
    }
  else
    return NULL;
}

/* Copy this node. */
EvaluableNode *
UnaryExprNode::copy() const
{
  UnaryExprNode * node;

  node = new UnaryExprNode(m_expression->copy(), m_op);
  #ifdef DEBUG_ENABLED
  util::parser::Debugger::register_malloc(node);
  #endif
  return node;
}


} /* End of namespace parser.  */
} /* End of namespace util.  */
} /* End of namespace TIDNotif.  */
