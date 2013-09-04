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
 *       * Class renamed from TIDString to StringValueNode.
 *       * New inheritance from InmediateValueNode.
 *       * Private value renamed to 'm_value'.
 *       * All member functions implemented in header.
 *   - 03/31/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Inheritance must be no virtual.
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 */

#ifndef _TIDUTIL_STRING_VALUE_NODE_H_
#define _TIDUTIL_STRING_VALUE_NODE_H_

#include <DynamicAny.h>

#include <string>

#include "InmediateValueNode.h"
#include "TypeValuePair.h"

#ifdef HAVE_STD_NAMESPACE
using namespace std;
#endif

namespace TIDNotif {
namespace util {
namespace parser {
  
class StringValueNode: public InmediateValueNode
{

public:

    StringValueNode(const char * value) : InmediateValueNode(), 
                                          m_value(value) {}
    const string & get_value() const { return m_value; }

    TypeValuePair evaluate(DynamicAny::DynAny_ptr dynany) const
    {
      return TypeValuePair::create_string(m_value.data());
    }

    TypeValuePair substring_find(const StringValueNode & substring) const
    {
      return TypeValuePair::create_boolean(
        m_value.find(substring.m_value, 0) != string::npos);
    }

    virtual EvaluableNode * copy() const
    {
      return new StringValueNode(m_value.c_str());
    }

private:
  
    string m_value;

};

}; /* End of namespace parser. */
}; /* End of namespace util. */
}; /* End of namespace TIDNotif. */

#endif
