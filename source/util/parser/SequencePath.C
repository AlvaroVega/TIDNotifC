/*
 *  File name: SequencePath.C
 *  File type: Body file.
 *  Date : 13th February 2006
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
 *   - 02/14/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *      * SimpleNode inheritance was forgotten. Fixed.
 *      * New exception class BadTypeException. It's used in 
 *        'extract_from_dynany' method to indicate a invalid type check.
 *   - 03/07/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *      * Revision historial cleaned.
 *      * Parent class set to 'EvaluableNode' instead of 'SimpleNode'.
 *      * Method 'evaluate' implemented.
 *      * New method: 'extract_sequence_from_dynany'.
 *      * Bug in 'extract_sequence_from_dynany' with base recursive case.
 *      * Debug messages for DynAny extraction in 'evaluate'.
 *   - 03/31/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added code for allocated memory debugging purposes.
 *   - 04/10/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * New debugging code.
 *   - 23/10/2008, by Alvaro Vega Garcia <avega at tid dot es>:
 *       * Removed unnecessary _var templates in declarations
 */

#include "SequencePath.h"

#include "Debugger.h"

namespace TIDNotif{
namespace util{
namespace parser{

/* Default constructor. */
SequencePath::SequencePath(SequencePath * next_step)
:
EvaluableNode(),
m_next_step(next_step)
{}

/* Default destructor. */
SequencePath::~SequencePath()
{
  if (m_next_step)
  {
    #ifdef DEBUG_ENABLED
    Debugger::register_free(m_next_step);
    #endif
    delete m_next_step;
  }
}

/* Evaluate an object in a filter expression. */
TypeValuePair
SequencePath::evaluate(DynamicAny::DynAny_ptr dynany) const
{
  DynamicAny::DynAny_var last;

  #ifdef DEBUG_ENABLED
  Debugger::send_message(70, 
    "Evaluating sequence path...", this);
  #endif
  if (!dynany)
  {
    #ifdef DEBUG_ENABLED
    Debugger::send_message(70, 
      "Warning: event is null", this);
    #endif
  }

  try
  {
    extract_sequence_from_dynany(dynany, last);
  }
  catch (BadTypeException)
  {
    #ifdef DEBUG_ENABLED
    Debugger::send_message(70, 
      "Type check error in event", this);
    #endif
    return TypeValuePair::create_error(__m_type_mismatch_msg);
  }
    
  #ifdef DEBUG_ENABLED
  Debugger::send_message(70, 
    "Final element of sequence obtained.", this);
  #endif

  if (!last)
  {
    #ifdef DEBUG_ENABLED
    Debugger::send_message(70, 
      "Warning: null dynamic any at sequence tail.", this);
    #endif
    return TypeValuePair::create_error(
      "argument type structure mismatch for 'in' operator");
  }
  switch (last->type()->kind())
  {
    case CORBA::tk_boolean:
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Last element is a boolean.", this);
      #endif
      return TypeValuePair::create_boolean(last->get_boolean());
    case CORBA::tk_octet:
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Last element is a octet.", this);
      #endif
      return TypeValuePair::create_long(last->get_octet());
    case CORBA::tk_short:
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Last element is a short.", this);
      #endif
      return TypeValuePair::create_long(last->get_short());
	  case CORBA::tk_ushort:
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Last element is a ushort.", this);
      #endif
      return TypeValuePair::create_long(last->get_ushort());
    case CORBA::tk_long:
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Last element is a long.", this);
      #endif
      return TypeValuePair::create_long(last->get_long());
    case CORBA::tk_ulong:
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Last element is a ulong.", this);
      #endif
      return TypeValuePair::create_long(last->get_ulong());
    case CORBA::tk_longlong:
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Last element is a longlong.", this);
      #endif
      return TypeValuePair::create_long(last->get_longlong());
    case CORBA::tk_ulonglong:
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Last element is a ulonglong.", this);
      #endif
      return TypeValuePair::create_long(last->get_ulonglong());
    case CORBA::tk_float:
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Last element is a float.", this);
      #endif
      return TypeValuePair::create_double(last->get_float());
    case CORBA::tk_double:
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Last element is a double.", this);
      #endif
      return TypeValuePair::create_double(last->get_double());
	  case CORBA::tk_longdouble:
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Last element is a long double.", this);
      #endif
      return TypeValuePair::create_double(last->get_double()); /* long double? */
	  case CORBA::tk_string:
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Last element is a string.", this);
      #endif
      return TypeValuePair::create_string(last->get_string());
    case CORBA::tk_wstring:
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Last element is a wstring.", this);
      #endif
      return TypeValuePair::create_string((char*)last->get_wstring());
    default: 
      #ifdef DEBUG_ENABLED
      Debugger::send_message(70, 
        "Warning: last element has no simple type.", this);
      #endif
      return TypeValuePair::create_error(__m_type_mismatch_msg);
  }
}

TypeValuePair
SequencePath::evaluate_in_operation(const TypeValuePair & simple_value,
                                    const DynamicAny::DynAny_ptr& dyn_any) const
{
  DynamicAny::DynAny_var value;

  try
  {
    extract_sequence_from_dynany(dyn_any, value);
  }
  catch (BadTypeException & exc)
  {
    return TypeValuePair::create_error(__m_type_mismatch_msg);
  }
  return simple_value.search_in_dynany(value);
}

/* Extract associated value from a Dynamic Any for all sequence. */
void 
SequencePath::extract_sequence_from_dynany(
  const DynamicAny::DynAny_ptr& from,
  DynamicAny::DynAny_ptr & value) const
  throw (BadTypeException)
{
  DynamicAny::DynAny_ptr result;

  extract_from_dynany(from, result);
  if (m_next_step)
    m_next_step->extract_sequence_from_dynany(result, value);
  else
    value = result;
}

char *
SequencePath::__m_type_mismatch_msg = 
  "argument type structure mismatch for 'in' operator";


} /* End of namespace parser.  */
} /* End of namespace util. */
} /* End of namespace TIDNotif. */
