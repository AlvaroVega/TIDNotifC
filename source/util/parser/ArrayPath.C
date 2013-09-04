/*
 *  File name: ArrayPath.C
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
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 *   - 23/10/2008, by Alvaro Vega Garcia <avega at tid dot es>:
 *       * Removed unnecessary _var templates in declarations
 */

#include "ArrayPath.h"
#include "Debugger.h"

namespace TIDNotif {
namespace util {
namespace parser {

/* Default constructor. */
ArrayPath::ArrayPath(SequencePath * next_step,
                     CORBA::ULong array_pos)
:
SequencePath(next_step),
m_array_pos(array_pos)
{}

/* Set array position. */
void
ArrayPath::set_array_pos(CORBA::ULong array_pos)
{
  m_array_pos = array_pos;
}

/* Get array position. */
CORBA::ULong
ArrayPath::get_array_pos() const
{
  return m_array_pos;
}

/* Extract associated value from a Dynamic Any. */
void
ArrayPath::extract_from_dynany(const DynamicAny::DynAny_ptr& from,
                               DynamicAny::DynAny_ptr& value) const
  throw (BadTypeException)
{
  CORBA::TCKind tk;
  DynamicAny::DynArray_ptr any_array;
  DynamicAny::AnySeq * elements;

  tk = from->type()->kind();
  if (tk != CORBA::tk_array)
    throw BadTypeException();

  any_array = DynamicAny::DynArray::_narrow(from);
  if (any_array == DynamicAny::DynArray::_nil())
    throw BadTypeException();

  elements = any_array->get_elements();
  if (get_array_pos() < elements->length())
    value = NULL; //(*elements)[get_array_pos()];
  else
    throw BadTypeException();
}

/* Copy this node. */
EvaluableNode *
ArrayPath::copy() const
{
  ArrayPath * node;

  node = new ArrayPath(
    dynamic_cast<SequencePath*>(m_next_step->copy()), m_array_pos);
  #ifdef DEBUG_ENABLED
  util::parser::Debugger::register_malloc(node);
  #endif
  return node;
}

} /* End of namespace parser.  */
} /* End of namespace util. */
} /* End of namespace TIDNotif. */

