/*
 *  File name: TIDConstraint.h
 *  File type: Header file.
 *  Date : January 2006
 *  Author: David Alonso <dalonso@gsyc.escet.urjc.es>
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
 *   - 02/14/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Code cleaning.
 *       * DynamicAnyFactory reference is traslated to class SimpleNode.
 *         All its childrens can use this reference to obtain DynAny
 *         objects. In addiction, error is reported by
 *         DynAnyFactoryLocationErrorException instead of a int error code.
 *   - 03/30/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * 'root' object must not be const.
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 */

#ifndef _TIDUTIL_TIDCONSTRAINT_H_
#define _TIDUTIL_TIDCONSTRAINT_H_

#include <DynamicAny.h>

#include "EvaluableNode.h"

namespace TIDNotif {
namespace util {
namespace parser {

/*!
 * \brief Constraint class.
 */
class TIDConstraint : public EvaluableNode
{

  public:

    /*!
     * \brief Default constructor.
     */
    TIDConstraint();

    /*!
     * \brief Root constructor.
     * \param root_node Root node.
     */
    TIDConstraint(EvaluableNode * root_node);

    /*!
     * \brief Destructor.
     */
    ~TIDConstraint();

    /*!
     * \brief Evaluate an object in a filter expression.
     * \param dynany Object to be evaluated.
     * \return Evaluation result.
     */
    TypeValuePair evaluate(DynamicAny::DynAny_ptr dynany) const;

    /*!
     * \brief Check if an event passes this filter.
     * \param event Event.
     * \return Filter result.
     */
    TypeValuePair check_event(const CORBA::Any& event );

    /*!
     * \brief Add a root to this constraint.
     * \param r Root simple node.
     */
    void addRoot (EvaluableNode * r);

    /*!
     * \brief Copy this node.
     */
    virtual EvaluableNode * copy() const;

  private:

    /*!
     * \brief Root simple node.
     */
    EvaluableNode * root;

};


}; /* End of namespace parser. */
}; /* End of namespace util. */
}; /* End of namespace TIDNotif. */

#endif
