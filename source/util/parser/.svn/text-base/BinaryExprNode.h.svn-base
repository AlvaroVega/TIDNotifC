/*
 *  File name: BinaryExprNode.h
 *  File type: Header file.
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
 *       * Inheritance must be no virtual.
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 */

#ifndef _TIDUTIL_BINARY_EXPR_NODE_H_
#define _TIDUTIL_BINARY_EXPR_NODE_H_ 

#include <DynamicAny.h>

#include "TypeValuePair.h"
#include "EvaluableNode.h"

namespace TIDNotif {
namespace util {
namespace parser {

/*! \brief This class represents a binary expression
 *  in constraint grammar. */
class BinaryExprNode: public EvaluableNode
{

  public:

    /*! \brief Arithmetic operations type. */
    typedef enum
    {
      ADD_OP,
      SUB_OP,
      MUL_OP,
      DIV_OP,
      MOD_OP,
      AND_OP,
      OR_OP,
      EQUAL_OP,
      NOT_EQUAL_OP,
      GREATER_THAN_OP,
      GREATER_OR_EQUAL_THAN_OP,
      LESS_THAN_OP,
      LESS_OR_EQUAL_THAN_OP,
      IN_OP,
      TILDE_OP
    } Operator;

    /*!
     * \brief Default constructor.
     * \param s1 Left hand operand.
     * \param s2 Right hand operand.
     */
    BinaryExprNode(EvaluableNode * left_expression,
                       EvaluableNode * right_expression,
                       Operator op);
                       
    /*! \brief Destructor. */
    ~BinaryExprNode();

    /*!
     * \brief Evaluate an object in a filter expression.
     * \param dynany Object to be evaluated.
     * \return Evaluation result.
     */
    TypeValuePair evaluate(DynamicAny::DynAny_ptr dynany) const;

    /*!
     * \brief Copy this node.
     */
    virtual EvaluableNode * copy() const;

private:

    /*! \brief Left hand operand. */
    EvaluableNode * m_left_expr;

    /*! \brief Right hand operand. */
    EvaluableNode * m_right_expr;

    /*! \brief Operator. */
    Operator m_op;

};

} /* End of namespace parser.  */
} /* End of namespace util. */
} /* End of namespace TIDNotif. */


#endif
