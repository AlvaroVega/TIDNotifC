/*
 *  File name: BooleanValueNode.h
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
 *   - 03/14/20006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Code cleaning.
 *       * Class renamed from TIDBoolean to BooleanValueNode.
 *       * New inheritance from InmediateValueNode.
 *       * Private value renamed to 'm_value'.
 *       * All member functions implemented in header.
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 */

#ifndef _TIDUTIL_BOOLEAN_VALUE_NODE_H_
#define _TIDUTIL_BOOLEAN_VALUE_NODE_H_

#include <DynamicAny.h>

#include "InmediateValueNode.h"
#include "TypeValuePair.h"
#include "Debugger.h"

namespace TIDNotif {
namespace util {
namespace parser {

class BooleanValueNode: public InmediateValueNode
{

  public:

    BooleanValueNode(bool value) : InmediateValueNode(), m_value(value) {}
  
    TypeValuePair evaluate(DynamicAny::DynAny_ptr dynany) const
    {
      return TypeValuePair::create_boolean(m_value);
    }

    virtual EvaluableNode * copy() const
    {
      BooleanValueNode * node;
      node =  new BooleanValueNode(m_value);
      #ifdef DEBUG_ENABLED
      util::parser::Debugger::register_malloc(node);
      #endif
      return node;
    }

  private:
  
    bool m_value;

};

}; /* End of namespace parser. */
}; /* End of namespace util. */
}; /* End of namespace TIDNotif. */

#endif
