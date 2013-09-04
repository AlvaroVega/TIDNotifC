/*
 *  File name: IdentifierValueNode.h
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

#ifndef _TIDUTIL_IDENTIFIER_VALUE_NODE_H_
#define _TIDUTIL_IDENTIFIER_VALUE_NODE_H_

#include <string>

#include <DynamicAny.h>

#include "EvaluableNode.h"
#include "TypeValuePair.h"
#include "Debugger.h"

#ifdef HAVE_STD_NAMESPACE
using namespace std;
#endif

namespace TIDNotif {
namespace util {
namespace parser {

class IdentifierValueNode: public EvaluableNode
{

  public:

    IdentifierValueNode(const char * name) : EvaluableNode(), m_name(name) {}

    TypeValuePair evaluate(DynamicAny::DynAny_ptr dynany) const
    {
      return TypeValuePair::create_error(
                "access to variables not implemented");
    }

    const string & get_name() const { return m_name; }

    /*!
     * \brief Copy this node.
     */
    virtual EvaluableNode * copy() const
    {
      IdentifierValueNode * node;

      node = new IdentifierValueNode(m_name.c_str());
      #ifdef DEBUG_ENABLED
      util::parser::Debugger::register_malloc(node);
      #endif
      return node;
    }

  private:

    string m_name;

};

}; /* End of namespace parser. */
}; /* End of namespace util. */
}; /* End of namespace TIDNotif. */

#endif
