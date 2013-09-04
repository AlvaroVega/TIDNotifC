/*
 *  File name: EvaluableNode.h
 *  File type: Header file.
 *  Date : 02/17/2006 2006
 *  Author: Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 */

/*
// (C) Copyright 2009 Telefonica Investigacion y Desarrollo
 *
//     S.A.Unipersonal (Telefonica I+D)
//
 * by its owner.
 */

/*
 * Revision historial:
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 */

#ifndef _TIDUTIL_EVALUABLENODE_H_
#define _TIDUTIL_EVALUABLENODE_H_

#include "SimpleNode.h"
#include "TypeValuePair.h"

namespace TIDNotif {
namespace util {
namespace parser {

/*!
 * \brief Evaluable node pure virtual class.
 */
class EvaluableNode: public SimpleNode
{

  public:

    /*!
     * \brief Default constructor.
     */
    EvaluableNode() : SimpleNode() {}

    /*!
     * \brief Evaluate an object in a filter expression.
     * \param dynany Object to be evaluated.
     * \return Evaluation result.
     */
    virtual TypeValuePair evaluate(DynamicAny::DynAny_ptr dynany) const = 0;
    
    /*!
     * \brief Reduce this node if possible.
     * \return If node can be reduced, a new EvaluableNode object is return.
     *         Return null otherwise.
     */
    virtual EvaluableNode * reduce() const { return 0; }

    /*!
     * \brief Copy this node.
     */
    virtual EvaluableNode * copy() const = 0;
};

}; /* End of namespace parser. */
}; /* End of namespace util. */
}; /* End of namespace TIDNotif. */

#endif
