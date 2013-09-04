/*
 *  File name: LongValueNode.h
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
 *   - 03/31/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Inheritance must be no virtual.
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 */

#ifndef _TIDUTIL_LONG_VALUE_NODE_H_
#define _TIDUTIL_LONG_VALUE_NODE_H_

#include <DynamicAny.h>

#include "InmediateValueNode.h"
#include "TypeValuePair.h"
#include "Debugger.h"

namespace TIDNotif {
namespace util {
namespace parser {

class LongValueNode: public InmediateValueNode
{

  public:

    LongValueNode(long value) : InmediateValueNode(), m_value(value) {}

    TypeValuePair evaluate(DynamicAny::DynAny_ptr dynany) const
    {
      return TypeValuePair::create_long(m_value);
    }

    void invert_sign() { m_value = - m_value; }

    long get_value() const { return m_value; }

    virtual EvaluableNode * copy() const
    {
      LongValueNode * node;

      node = new LongValueNode(m_value);
      #ifdef DEBUG_ENABLED
      util::parser::Debugger::register_malloc(node);
      #endif
      return node;
    }

  private:
  
    long m_value;

};

}; /* End of namespace parser. */
}; /* End of namespace util. */
}; /* End of namespace TIDNotif. */

#endif
