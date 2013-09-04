
/*
 *  File name: UnionStringSwitchPath
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
 *   - 04/12/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *      * Code cleaning.
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 *   - 23/10/2008, by Alvaro Vega Garcia <avega at tid dot es>:
 *       * Removed unnecessary _var templates in declarations
 */

#include <CORBA.h>

#include "UnionStringSwitchPath.h"

#include "Debugger.h"


namespace TIDNotif{
namespace util{
namespace parser{

/* Default constructor. */
UnionStringSwitchPath::UnionStringSwitchPath(SequencePath * next_step,
                                         const string switch_val)
:
SequencePath(next_step),
switch_value(switch_val)
{}

void
UnionStringSwitchPath::set_switch_value(const string switch_val)
{
  switch_value = switch_val;
}

const string
UnionStringSwitchPath::get_switch_value() const
{
  return switch_value;
}


void 
UnionStringSwitchPath::extract_from_dynany(
  const DynamicAny::DynAny_ptr& from,
  DynamicAny::DynAny_ptr & value) const
  throw (BadTypeException)
{
  DynamicAny::DynUnion_var any_union;
  DynamicAny::DynAny_ptr old_discriminator;
  DynamicAny::DynAny_ptr new_discriminator;
  DynamicAny::DynEnum_ptr enum_discriminator;
  CORBA::Any any_value;
  
  #ifdef DEBUG_ENABLED
  Debugger::send_message(70, 
    "Extracting union member", this);
  #endif

  /* If it is we must create a DynUnion */  
  any_union = DynamicAny::DynUnion::_narrow(from);
  if (any_union == DynamicAny::DynUnion::_nil())
  {
    #ifdef DEBUG_ENABLED
    Debugger::send_message(70, 
      "Warning: event is not a DynUnion", this);
    #endif
    throw BadTypeException();
  }

  /* We get the discriminator of the union */  
  old_discriminator = any_union->get_discriminator();
  new_discriminator = NULL;

  /* In case of a DynEnum discriminator. */  
  enum_discriminator = DynamicAny::DynEnum::_narrow(old_discriminator);
  if (enum_discriminator)
  {
    #ifdef DEBUG_ENABLED
    Debugger::send_message(70, 
      "Discriminator is an enumerated type", this);
    #endif
    enum_discriminator = DynamicAny::DynEnum::_duplicate(enum_discriminator);
    try
    {
      enum_discriminator->set_as_string(switch_value.c_str());
    }
    catch (...)
    {
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Warning: cannot set enumerated discriminator value", this);
      #endif
      throw BadTypeException();
    }
    new_discriminator = enum_discriminator;
  }

  else if (old_discriminator->type()->kind() == CORBA::tk_boolean)
  {
    #ifdef DEBUG_ENABLED
    Debugger::send_message(70, 
      "Discriminator is a boolean type", this);
    #endif
    if (switch_value == "TRUE" || switch_value == "true")
    {
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Generating 'true' value for new discriminator", this);
      #endif
      new_discriminator = DynamicAny::DynAny::_duplicate(old_discriminator);
      new_discriminator->insert_boolean(true);
      /*
      any_value.delegate().insert_boolean(true);
      new_discriminator = dynAnyFactory->create_dyn_any(any_value);
      */
    }
    else if (switch_value == "false" || switch_value == "FALSE")
    {
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Generating 'false' value for new discriminator", this);
      #endif
      new_discriminator = DynamicAny::DynAny::_duplicate(old_discriminator);
      new_discriminator->insert_boolean(false);
      /*
      any_value.delegate().insert_boolean(false);
      new_discriminator = dynAnyFactory->create_dyn_any(any_value);
      */
    }
    else
    {
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Constraint switch label has not a boolean value", this);
      #endif
      throw BadTypeException();
    }
  }

  /* 
   * If no new discriminator was set up, it means that this cannot
   * be determinated. 
   */
  if (!new_discriminator)
  {
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Warning: discriminator type cannot be determinated", this);
      #endif
      throw BadTypeException();
  }

  /* Set in union the new calculated discriminator. */
  try
  {
    any_union->set_discriminator(old_discriminator);
  }
  catch (...)
  {
    #ifdef DEBUG_ENABLED
    Debugger::send_message(70, 
      "Warning: cannot set discriminator value", this);
    #endif
    throw BadTypeException();
  }

  /* Extract now the union member value. */
  value = any_union->member();

  /* Set again the old discriminator value. */
  any_union->set_discriminator(old_discriminator);

  /* Release memory. */
  if (old_discriminator) CORBA::release(old_discriminator);
  if (new_discriminator) CORBA::release(new_discriminator);
}

/* Copy this node. */
EvaluableNode *
UnionStringSwitchPath::copy() const
{
  UnionStringSwitchPath * node;

  node = new UnionStringSwitchPath(
    dynamic_cast<SequencePath*>(m_next_step->copy()), switch_value);
  #ifdef DEBUG_ENABLED
  util::parser::Debugger::register_malloc(node);
  #endif
  return node;
}

} /* End of namespace util. */
} /* End of namespace parser.  */
} /* End of namespace TIDNotif.  */
