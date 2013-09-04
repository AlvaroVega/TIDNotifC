/*
 *  File name: UnionDefaultSwitchPath
 *  File type: Body file.
 *  Date : 14th February 2006
 *  Author: Toms Aguado Gmez taguado@gsyc.escet.urjc.es>
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
 *       * Remove unnecessary _var templates in declarations
 */

#include <CORBA.h>

#include "UnionDefaultSwitchPath.h"
#include "Debugger.h"


namespace TIDNotif{
namespace util{
namespace parser{

/* Default constructor. */
UnionDefaultSwitchPath::UnionDefaultSwitchPath(SequencePath * next_step)
:
SequencePath(next_step)
{}

void 
UnionDefaultSwitchPath::extract_from_dynany(const DynamicAny::DynAny_ptr& from,
                                            DynamicAny::DynAny_ptr & value) const
  throw (BadTypeException)
{
  CORBA::TCKind tk;
  DynamicAny::DynUnion_ptr any_union;


  tk = from->type()->kind();
  if (tk != CORBA::tk_union)
    throw BadTypeException();

  any_union = DynamicAny::DynUnion::_narrow(from);
  if (any_union == DynamicAny::DynUnion::_nil())
    throw BadTypeException();

  any_union->set_to_default_member();
  
  value =(any_union->member());
}

/* Copy this node. */
EvaluableNode *
UnionDefaultSwitchPath::copy() const
{
  UnionDefaultSwitchPath * node;

  node = new UnionDefaultSwitchPath(
    dynamic_cast<SequencePath*>(m_next_step->copy()));
  #ifdef DEBUG_ENABLED
  util::parser::Debugger::register_malloc(node);
  #endif
  return node;
}

} /* End of namespace util. */
} /* End of namespace parser.  */
} /* End of namespace TIDNotif. */
