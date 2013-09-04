/*
 *  File name: StructFieldPosPath.C
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
 *   - 04/17/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * In 'extract_from_dynany', member extraction is performed
 *         using DynamicAny class component iterators instead of
 *         DynStruct function member 'get_members'. 
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 *   - 23/10/2008, by Alvaro Vega Garcia <avega at tid dot es>:
 *       * Removed unnecessary _var templates in declarations
 */

#include "StructFieldPosPath.h"

#include "Debugger.h"

namespace TIDNotif {
namespace util {
namespace parser {

/* Default constructor. */
StructFieldPosPath::StructFieldPosPath(SequencePath * next_step,
                                       CORBA::ULong field_pos)
:
SequencePath(next_step),
m_field_pos(field_pos)
{}

/* Set field position. */
void
StructFieldPosPath::set_field_pos(CORBA::ULong field_pos)
{
  m_field_pos = field_pos;
}

/* Get field position. */
CORBA::ULong
StructFieldPosPath::get_field_pos() const
{
  return m_field_pos;
}

/* Extract associated value from a Dynamic Any. */
void
StructFieldPosPath::extract_from_dynany(const DynamicAny::DynAny_ptr& from,
                                        DynamicAny::DynAny_ptr& value) const
  throw (BadTypeException)
{
  CORBA::TCKind tk;
  DynamicAny::DynStruct_ptr any_struct;
  //DynamicAny::NameValuePairSeq * members;
  DynamicAny::NameValuePair field;
  CORBA::ULong i;

  tk = from->type()->kind();
  if (tk != CORBA::tk_struct)
    throw BadTypeException();

  any_struct = DynamicAny::DynStruct::_narrow(from);
  if (any_struct == DynamicAny::DynStruct::_nil())
    throw BadTypeException();

  /*
   * Instead of trying to get struct members using function member
   * 'DynStruct::get_members', it's better to use component handling
   * methods from class DynamicAny. It's due to a possible bug in
   * TIDorbC library in DynStruct::get_members. For this reason,
   * next code chunk is commented and sustituted by below code,
   * using component handling function members.
   */
  /*
  members = any_struct->get_members();
  if (get_field_pos() < members->length())
    field = (*members)[get_field_pos()];
  else
    throw BadTypeException();
  value = dynAnyFactory->create_dyn_any(field.value);
  */

  /* This code use component handling methods from DynamicAny class. */
  if (get_field_pos() >= any_struct->component_count())
  {
    #ifdef DEBUG_ENABLED
    Debugger::send_message(70,
      "Field position is greater than struct member count.", this);
    #endif
    throw BadTypeException();
  }
  any_struct->rewind();
  for (i = 0; i < get_field_pos(); i++)
    any_struct->next();
  #ifdef DEBUG_ENABLED
  Debugger::send_message(70,
    "Field position found. Returning next event slice value.", this);
  #endif
  value = any_struct->current_component();
}

/* Copy this node. */
EvaluableNode *
StructFieldPosPath::copy() const
{
  StructFieldPosPath * node;

  node = new StructFieldPosPath(
    dynamic_cast<SequencePath*>(m_next_step->copy()), m_field_pos);
  #ifdef DEBUG_ENABLED
  util::parser::Debugger::register_malloc(node);
  #endif
  return node;
}

} /* End of namespace parser.  */
} /* End of namespace util. */
} /* End of namespace TIDNotif. */
