/*
 *  File name: StructFieldNamePath.C
 *  File type: Body file.
 *  Date : 14th February 2006
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
 *   - 02/16/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Support for expressions like $._d for accessing default union values.
 *   - 03/30/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * In function member 'extract_from_dyn_any', 'members' array is
 *         deleted after used.
 *   - 03/31/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added code for allocated memory debugging purposes.
 *   - 04/17/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * In 'extract_from_dynany', member extraction is performed
 *         using DynamicAny class component iterators instead of
 *         DynStruct function member 'get_members'. 
 *       * In 'extract_from_dynany', report a debug message when
 *         struct member is not found.
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 *   - 23/10/2008, by Alvaro Vega Garcia <avega at tid dot es>:
 *       * Removed unnecessary _var templates in declarations
 */

#include <CORBA.h>

#include "StructFieldNamePath.h"
#include "Debugger.h"


namespace TIDNotif {
namespace util {
namespace parser {

/* Default constructor. */
StructFieldNamePath::StructFieldNamePath(SequencePath * next_step,
                                         const string & field_name)
:
SequencePath(next_step),
m_field_name(field_name)
{}

/* Set field name. */
void
StructFieldNamePath::set_field_name(const string & field_name)
{
  m_field_name = field_name;
}

/* Get field name. */
const string &
StructFieldNamePath::get_field_name() const
{
  return m_field_name;
}

/* Extract associated value from a Dynamic Any. */
void 
StructFieldNamePath::extract_from_dynany(const DynamicAny::DynAny_ptr& from,
                                         DynamicAny::DynAny_ptr& value) const
                                        throw (BadTypeException)
{
  CORBA::TCKind tk;
  DynamicAny::DynStruct_ptr any_struct;
  DynamicAny::DynUnion_var any_union;
  //  DynamicAny::NameValuePairSeq * members;
  DynamicAny::NameValuePair field;
  CORBA::ULong i;

  tk = from->type()->kind();
#ifdef DEBUG_ENABLED
  Debugger::send_message(70,
    "Type kind extracted from this filter slice", this);
#endif

  if (get_field_name() == "_d")
  {
    if (tk != CORBA::tk_union)
      throw BadTypeException();

    any_union = DynamicAny::DynUnion::_narrow(from);
    if (any_union == DynamicAny::DynUnion::_nil())
      throw BadTypeException();
    any_union->set_to_default_member();
    value = any_union->member();
  }
  else
  {
    if (tk != CORBA::tk_struct)
    {
#ifdef DEBUG_ENABLED
      Debugger::send_message(70,
        "This filter slice is not a struct. Event fails type checking.", this);
#endif
      throw BadTypeException();
    }

#ifdef DEBUG_ENABLED
    Debugger::send_message(70,
      "This filter slice seems to be a struct. Things goes well.", this);
    #endif
    any_struct = DynamicAny::DynStruct::_narrow(from);
#ifdef DEBUG_ENABLED
    Debugger::send_message(70,
      "Event slice narrowed.", this);
    #endif
    if (any_struct == DynamicAny::DynStruct::_nil())
    {
#ifdef DEBUG_ENABLED
      Debugger::send_message(70,
        "Narrowed pointer is null, so it failed. ", this);
#endif
      throw BadTypeException();
    }

    /*
     * Instead of trying to get struct members using function member
     * 'DynStruct::get_members', it's better to use component handling
     * methods from class DynamicAny. It's due to a possible bug in
     * TIDorbC library in DynStruct::get_members. For this reason,
     * next code chunk is commented and sustituted by below code,
     * using component handling function members.
     */
    /*
    try
    {
      members = any_struct->get_members();
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70,
        "Struct members extracted.", this);
      #endif
    }
		catch (...)
    {
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
      	"Cannot get struct members: assuming non valid struct", this);
      #endif
      throw BadTypeException();
    }
    for (i=0; i < members->length(); i++)
    {
      field = (*members)[i];
      if (get_field_name() == (char*)field.id)
      {
        #ifdef DEBUG_ENABLED
        Debugger::send_message(70,
          "Field name found. Returning next event slice value.", this);
        #endif
        value = dynAnyFactory->create_dyn_any(field.value);
        delete members;
        return;
      }
    }
    delete members;
    */

    /* This code use component handling methods from DynamicAny class. */
    any_struct->rewind();
    for (i = 0; i < any_struct->component_count(); i++)
    {
      CORBA::String_var current_member_name = any_struct->current_member_name();
      CORBA::String_var field_name = get_field_name().c_str();
      if (strcmp(current_member_name, field_name) == 0)
      {
        #ifdef DEBUG_ENABLED
        Debugger::send_message(70,
          "Field name found. Returning next event slice value.", this);
        #endif
        value = any_struct->current_component();
        return;
      }
      any_struct->next();
    }

#ifdef DEBUG_ENABLED
    Debugger::send_message(70,
      "Struct field name not found. Raising error. ", this);
#endif
    throw BadTypeException();
  }
}

/* Copy this node. */
EvaluableNode *
StructFieldNamePath::copy() const
{
  StructFieldNamePath * node;

  node = new StructFieldNamePath(
    dynamic_cast<SequencePath*>(m_next_step->copy()), m_field_name);
#ifdef DEBUG_ENABLED
  util::parser::Debugger::register_malloc(node);
#endif
  return node;
}


} /* End of namespace parser.  */
} /* End of namespace util. */
} /* End of namespace TIDNotif.  */




