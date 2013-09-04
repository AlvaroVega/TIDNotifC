/*
 *  File name: DoubleValueNode.h
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

#ifndef _TIDUTIL_DOUBLE_VALUE_NODE_H_
#define _TIDUTIL_DOUBLE_VALUE_NODE_H_

#include <DynamicAny.h>

#include "InmediateValueNode.h"
#include "TypeValuePair.h"
#include "Debugger.h"

namespace TIDNotif {
namespace util {
namespace parser {
  
class DoubleValueNode: virtual public InmediateValueNode
{
  
public:
  
  DoubleValueNode(double value) : InmediateValueNode(), m_value(value) {}
  
  TypeValuePair evaluate(DynamicAny::DynAny_ptr dynany) const
  {
    return TypeValuePair::create_double(m_value);
  }
  
  void invert() { m_value = - m_value; }
  
  virtual EvaluableNode * copy() const
  {
    DoubleValueNode * node;
    node = new DoubleValueNode(m_value);
#ifdef DEBUG_ENABLED
    util::parser::Debugger::register_malloc(node);
#endif
    return node;
  }
  
private:
  
  double m_value;
  
};

}; /* End of namespace parser. */
}; /* End of namespace util. */
}; /* End of namespace TIDNotif. */

#endif
