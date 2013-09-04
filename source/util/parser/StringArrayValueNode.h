/*
 *  File name: StringArrayValueNode.C
 *  File type: Body file.
 *  Date : March 2006
 *  Author: Alvaro Polo Valdenebro <apoloval@gsyc.escet.urjc.es>
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
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 */

#ifndef _UTIL_STRING_ARRAY_VALUE_NODE_H_
#define _UTIL_STRING_ARRAY_VALUE_NODE_H_

#include <string>
#include <list>

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

class StringArrayValueNode: public EvaluableNode
{
  
  public:
  
    StringArrayValueNode() : EvaluableNode() {}

    StringArrayValueNode(const char * value) : EvaluableNode()
    {
      add_member(value);
    }

    void add_member(const char * value)
    {
      m_members.push_back(value);
    }

    TypeValuePair evaluate(DynamicAny::DynAny_ptr dynany) const
    {
      return TypeValuePair::create_error(
        "type array of string cannot be evaluated");
    }
    
    bool search_string(const char * str) const
    {
      list<string>::const_iterator it;
      for (it=m_members.begin(); it!= m_members.end(); it++)
        if (*it == str)
          return true;
      return false;
    }

    virtual EvaluableNode * copy() const
    {
      StringArrayValueNode * node;
      list<string>::const_iterator it;

      it = m_members.begin();
      node = new StringArrayValueNode(it->c_str());
      it++;
      while (it != m_members.end())
      {
        node->add_member(it->c_str());
        it++;
      }
      #ifdef DEBUG_ENABLED
      util::parser::Debugger::register_malloc(node);
      #endif
      return node;
    }

  private:
  
    list<string> m_members;  
    
};

}; /* Namespace parser. */
}; /* Namespace util. */
}; /* Namespace TIDNotif. */

#endif
