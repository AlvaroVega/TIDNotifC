/*
 *  File name: TypeValuePair.C
 *  File type: Body file.
 *  Date : 16th February 2006
 *  Author: David Alonso <dalonso@gsyc.escet.urjc.es>
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
 *   - 02/17/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Code cleaning.
 *       * Bug fixed: error when releases memory for sval.
 *       * New method: search_in_dynany.
 *   - 03/13/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Error constructor must initialize 'sval' and 'val' pointers.
 *   - 03/14/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Design major changes. See documentation for more details.
 *   - 03/31/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Allocated memory debugging code inserted.
 *   - 04/05/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Minor or equal than operator was erroneously implemented
 *         with greater than operator.
 *   - 04/10/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Tilde operator implemented and executed from TypeValuePair
 *         instead of BinaryExprNode.
 */

#include <CORBA.h>

#include "TypeValuePair.h"

#include "InmediateValueNode.h"

#include "BooleanValueNode.h"
#include "LongValueNode.h"
#include "DoubleValueNode.h"
#include "StringValueNode.h"

#include "Debugger.h"

namespace TIDNotif {
namespace util {
namespace parser {

/* Copy constructor. */
TypeValuePair::TypeValuePair(const TypeValuePair & pair)
:
m_type(pair.m_type)
{
  switch (m_type)
  {
    case BOOLEAN_TYPE:
      m_boolean_value = pair.m_boolean_value;
      break;
    case LONG_TYPE:
      m_long_value = pair.m_long_value;
      break;
    case DOUBLE_TYPE:
      m_double_value = pair.m_double_value;
      break;
    case STRING_TYPE:
      m_string_value = pair.m_string_value;
      break;
    case ERROR_TYPE:
      m_error_cause = pair.m_error_cause;
      break;
  }
}

/* Assign operator. */
const TypeValuePair & 
TypeValuePair::operator = (const TypeValuePair & pair)
{
  *this = TypeValuePair(pair);
  return *this;
}

/* 
 * Default constructor. This constructor does nothing. All building
 * is done in static creation methods. 
 */
TypeValuePair::TypeValuePair()
{}

/* Create a new boolean type value. */
TypeValuePair
TypeValuePair::create_boolean(bool value)
{
  TypeValuePair pair;
  pair.m_type = BOOLEAN_TYPE;
  pair.m_boolean_value = value;
  return pair;
}

/* Create a new boolean type value. */
TypeValuePair
TypeValuePair::create_long(long value)
{
  TypeValuePair pair;
  pair.m_type = LONG_TYPE;
  pair.m_long_value = value;
  return pair;
}

/* Create a new boolean type value. */
TypeValuePair
TypeValuePair::create_double(double value)
{
  TypeValuePair pair;
  pair.m_type = DOUBLE_TYPE;
  pair.m_double_value = value;
  return pair;
}

/* Create a new boolean type value. */
TypeValuePair
TypeValuePair::create_string(const char * value)
{
  TypeValuePair pair;
  pair.m_type = STRING_TYPE;
  pair.m_string_value = value;
  return pair;
}

/* Create a new error type value in heap. */
TypeValuePair
TypeValuePair::create_error(const char * cause)
{
  TypeValuePair pair;
  pair.m_type = ERROR_TYPE;
  pair.m_error_cause = cause;
  return pair;
}

/* Get this value type pair type. */
TypeValuePair::Type
TypeValuePair::get_type() const
{
  return m_type;
}

/* Get this value type pair type image. */
string
TypeValuePair::get_type_image() const
{
  switch (get_type())
  {
    case BOOLEAN_TYPE:
      return "boolean";
    case LONG_TYPE:
      return "long";
    case DOUBLE_TYPE:
      return "double";
    case STRING_TYPE:
      return "string";
    case ERROR_TYPE:
      return "error";
    default:
      return "unknow";
  }
}

/* Get value as boolean type. */
bool
TypeValuePair::get_value_as_boolean() const throw (TypeCheckError)
{
  if (get_type() == BOOLEAN_TYPE)
    return m_boolean_value;
  else
    throw TypeCheckError("this type value pair has no boolean type");
}

/* Get value as long type. */
long
TypeValuePair::get_value_as_long() const throw (TypeCheckError)
{
  if (get_type() == LONG_TYPE)
    return m_long_value;
  else
    throw TypeCheckError("this type value pair has no long type");
}

/* Get value as double type. */
double
TypeValuePair::get_value_as_double() const throw (TypeCheckError)
{
  if (get_type() == DOUBLE_TYPE)
    return m_double_value;
  else
    throw TypeCheckError("this type value pair has no double type");
}

/* Get value as string type. */
const string &
TypeValuePair::get_value_as_string() const throw (TypeCheckError)
{
  if (get_type() == STRING_TYPE)
    return m_string_value;
  else
    throw TypeCheckError("this type value pair has no string type");
}

/* Get value as error type. */
const string &
TypeValuePair::get_value_as_error() const throw (TypeCheckError)
{
  if (get_type() == ERROR_TYPE)
    return m_error_cause;
  else
    throw TypeCheckError("this type value pair has no error type");
}

/* Get value image. */
string
TypeValuePair::get_value_image() const
{
  char buff[255];
  
  switch (get_type())
  {
    case BOOLEAN_TYPE:
      if (get_value_as_boolean())
        sprintf(buff, "true");
      else
        sprintf(buff, "false");
      break;
    case LONG_TYPE:
      sprintf(buff, "%li", get_value_as_long());
      break;
    case DOUBLE_TYPE:
      sprintf(buff, "%f", get_value_as_double());
      break;
    case STRING_TYPE:
      sprintf(buff, "%s", get_value_as_string().c_str());
      break;
    case ERROR_TYPE:
      sprintf(buff, "%s", get_value_as_error().c_str());
      break;
  }
  return buff;
}

TypeValuePair
TypeValuePair::search_in_dynany(const DynamicAny::DynAny_ptr& dynany) const
{
  CORBA::TCKind tk;
  DynamicAny::DynAnySeq * elements = NULL;
  DynamicAny::DynAny_var value = NULL;
  CORBA::ULong i;

  tk = dynany->type()->kind();
  switch (tk)
  {
    case CORBA::tk_sequence: 
      {
      DynamicAny::DynSequence_var seq = NULL;
      seq = DynamicAny::DynSequence::_narrow(dynany);
      if (seq == DynamicAny::DynSequence::_nil())
        return create_error("cannot narrow sequence");
      elements = seq->get_elements_as_dyn_any();
      break;
      }
    case CORBA::tk_array:
      {
      DynamicAny::DynArray_var array = NULL;
      array = DynamicAny::DynArray::_narrow(dynany);
      if (array == DynamicAny::DynArray::_nil())
        return create_error("cannot narrow array");
      elements = array->get_elements_as_dyn_any();
      break;
      }
    default:
      return create_error("non sequence or array object");
      break;
  }
  switch (get_type())
  {
    case BOOLEAN_TYPE:
      value->insert_boolean(get_value_as_boolean());
      break;
    case LONG_TYPE:
      value->insert_long(get_value_as_long());
      break;
    case DOUBLE_TYPE:
      value->insert_double(get_value_as_double());
      break;
    case STRING_TYPE:
      value->insert_string(get_value_as_string().c_str());
      break;
    case ERROR_TYPE:
    default:
      return create_error("this type cannot be found in a sequence");
      break;
  }

  for (i=0; i < elements->length(); i++)
    if ((*elements)[i] == value) {
      delete elements;
      return create_boolean(true);
    }

  delete elements;
  return create_boolean(false);
}

/* Add operator. */
TypeValuePair 
TypeValuePair::operator + (const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(ADD_OP, right_operand);
}

/* Subtract operator. */
TypeValuePair
TypeValuePair::operator - (const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(SUB_OP, right_operand);
}

/* Multiply operator. */
TypeValuePair
TypeValuePair::operator * (const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(MUL_OP, right_operand);
}

/* Divide operator. */
TypeValuePair
TypeValuePair::operator / (const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(DIV_OP, right_operand);
}

/* Module operator. */
TypeValuePair
TypeValuePair::operator % (const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(MOD_OP, right_operand);
}

/* Equal operator. */
TypeValuePair
TypeValuePair::operator == (const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(EQUAL_OP, right_operand);
}

/* Not equal operator. */
TypeValuePair
TypeValuePair::operator != (const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(NOT_EQUAL_OP, right_operand);
}

/* Greater than operator. */
TypeValuePair
TypeValuePair::operator > (const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(GREATER_THAN_OP, right_operand);
}

/* Greater or equal than operator. */
TypeValuePair
TypeValuePair::operator >= (const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(GREATER_OR_EQUAL_THAN_OP, right_operand);
}

/* Minor than operator. */
TypeValuePair
TypeValuePair::operator < (const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(MINOR_THAN_OP, right_operand);
}

/* Minor or equal than operator. */
TypeValuePair
TypeValuePair::operator <= (const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(MINOR_OR_EQUAL_THAN_OP, right_operand);
}

/* And operator. */
TypeValuePair
TypeValuePair::operator && (const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(AND_OP, right_operand);
}

/* Or operator. */
TypeValuePair
TypeValuePair::operator || (const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(OR_OP, right_operand);
}

/* Not operator. */
TypeValuePair
TypeValuePair::operator ! () const
throw (TypeCheckError)
{
  if (get_type() == BOOLEAN_TYPE)
    return create_boolean(!get_value_as_boolean());
  else
    throw TypeCheckError("invalid operand for not operator");
}

/* Tilde operator. */
TypeValuePair
TypeValuePair::operator_tilde(const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  return operate(TypeValuePair::TILDE_OP, right_operand);
}

/* Perform a binary operation. */
TypeValuePair
TypeValuePair::operate(BinaryOperators op,
                       const TypeValuePair & right_operand) const
throw (TypeCheckError)
{
  switch (get_type())
  {
    case BOOLEAN_TYPE:
      switch (right_operand.get_type())
      {
        case BOOLEAN_TYPE:
          switch (op)
          {
            case EQUAL_OP:
              return create_boolean(get_value_as_boolean() ==
                                    right_operand.get_value_as_boolean());
            case NOT_EQUAL_OP:
              return create_boolean(get_value_as_boolean() !=
                                    right_operand.get_value_as_boolean());
            case AND_OP:
              return create_boolean(get_value_as_boolean() &&
                                    right_operand.get_value_as_boolean());
            case OR_OP:
              return create_boolean(get_value_as_boolean() ||
                                    right_operand.get_value_as_boolean());
            default:
              break;
            
          }
        default:
          throw_type_check_error(op, right_operand);
      }
    case LONG_TYPE:
      switch (right_operand.get_type())
      {
        case LONG_TYPE:
          switch (op)
          {
            case ADD_OP:
              return create_long(get_value_as_long() + 
                                 right_operand.get_value_as_long());
            case SUB_OP:
              return create_long(get_value_as_long() - 
                                 right_operand.get_value_as_long());
            case MUL_OP:
              return create_long(get_value_as_long() * 
                                 right_operand.get_value_as_long());
            case DIV_OP:
              if (!right_operand.get_value_as_long())
                throw TypeCheckError("divided by zero");
              else
                return create_long(get_value_as_long() / 
                                   right_operand.get_value_as_long());
            case MOD_OP:
              return create_long(get_value_as_long() %
                                 right_operand.get_value_as_long());
            case EQUAL_OP:
              return create_boolean(get_value_as_long() ==
                                    right_operand.get_value_as_long());
            case NOT_EQUAL_OP:
              return create_boolean(get_value_as_long() !=
                                    right_operand.get_value_as_long());
            case GREATER_THAN_OP:
              return create_boolean(get_value_as_long() >
                                    right_operand.get_value_as_long());
            case GREATER_OR_EQUAL_THAN_OP:
              return create_boolean(get_value_as_long() >=
                                    right_operand.get_value_as_long());
            case MINOR_THAN_OP:
              return create_boolean(get_value_as_long() <
                                    right_operand.get_value_as_long());
            case MINOR_OR_EQUAL_THAN_OP:
              return create_boolean(get_value_as_long() <=
                                    right_operand.get_value_as_long());
            default:
              break;
          }
        case DOUBLE_TYPE:
          switch (op)
          {
            case ADD_OP:
              return create_double(get_value_as_long() + 
                                 right_operand.get_value_as_double());
            case SUB_OP:
              return create_double(get_value_as_long() - 
                                 right_operand.get_value_as_double());
            case MUL_OP:
              return create_double(get_value_as_long() * 
                                 right_operand.get_value_as_double());
            case DIV_OP:
              if (!right_operand.get_value_as_double() == 0.0)
                throw TypeCheckError("divided by zero");
              else
                return create_double(get_value_as_long() / 
                                   right_operand.get_value_as_double());
            case EQUAL_OP:
              return create_boolean(get_value_as_long() ==
                                    right_operand.get_value_as_double());
            case NOT_EQUAL_OP:
              return create_boolean(get_value_as_long() !=
                                    right_operand.get_value_as_double());
            case GREATER_THAN_OP:
              return create_boolean(get_value_as_long() >
                                    right_operand.get_value_as_double());
            case GREATER_OR_EQUAL_THAN_OP:
              return create_boolean(get_value_as_long() >=
                                    right_operand.get_value_as_double());
            case MINOR_THAN_OP:
              return create_boolean(get_value_as_long() <
                                    right_operand.get_value_as_double());
            case MINOR_OR_EQUAL_THAN_OP:
              return create_boolean(get_value_as_long() <=
                                    right_operand.get_value_as_double());
            default:
              break;
          }
        default:
          throw_type_check_error(op, right_operand);
      }
    case DOUBLE_TYPE:
      switch (right_operand.get_type())
      {
        case LONG_TYPE:
          switch (op)
          {
            case ADD_OP:
              return create_double(get_value_as_double() + 
                                   right_operand.get_value_as_long());
            case SUB_OP:
              return create_double(get_value_as_double() - 
                                   right_operand.get_value_as_long());
            case MUL_OP:
              return create_double(get_value_as_double() * 
                                   right_operand.get_value_as_long());
            case DIV_OP:
              if (!right_operand.get_value_as_long())
                throw TypeCheckError("divided by zero");
              else
                return create_double(get_value_as_double() / 
                                     right_operand.get_value_as_long());
            case EQUAL_OP:
              return create_boolean(get_value_as_double() ==
                                    right_operand.get_value_as_long());
            case NOT_EQUAL_OP:
              return create_boolean(get_value_as_double() !=
                                    right_operand.get_value_as_long());
            case GREATER_THAN_OP:
              return create_boolean(get_value_as_double() >
                                    right_operand.get_value_as_long());
            case GREATER_OR_EQUAL_THAN_OP:
              return create_boolean(get_value_as_double() >=
                                    right_operand.get_value_as_long());
            case MINOR_THAN_OP:
              return create_boolean(get_value_as_double() <
                                    right_operand.get_value_as_long());
            case MINOR_OR_EQUAL_THAN_OP:
              return create_boolean(get_value_as_double() <=
                                    right_operand.get_value_as_long());
            default:
              break;
          }
        case DOUBLE_TYPE:
          switch (op)
          {
            case ADD_OP:
              return create_double(get_value_as_double() + 
                                 right_operand.get_value_as_double());
            case SUB_OP:
              return create_double(get_value_as_double() - 
                                 right_operand.get_value_as_double());
            case MUL_OP:
              return create_double(get_value_as_double() * 
                                 right_operand.get_value_as_double());
            case DIV_OP:
              if (!right_operand.get_value_as_double() == 0.0)
                throw TypeCheckError("divided by zero");
              else
                return create_double(get_value_as_double() / 
                                   right_operand.get_value_as_double());
            case EQUAL_OP:
              return create_boolean(get_value_as_double() ==
                                    right_operand.get_value_as_double());
            case NOT_EQUAL_OP:
              return create_boolean(get_value_as_double() !=
                                    right_operand.get_value_as_double());
            case GREATER_THAN_OP:
              return create_boolean(get_value_as_double() >
                                    right_operand.get_value_as_double());
            case GREATER_OR_EQUAL_THAN_OP:
              return create_boolean(get_value_as_double() >=
                                    right_operand.get_value_as_double());
            case MINOR_THAN_OP:
              return create_boolean(get_value_as_double() <
                                    right_operand.get_value_as_double());
            case MINOR_OR_EQUAL_THAN_OP:
              return create_boolean(get_value_as_double() <=
                                    right_operand.get_value_as_double());
            default:
              break;
          }
        default:
          throw_type_check_error(op, right_operand);
      }
    case STRING_TYPE:
      switch (right_operand.get_type())
      {
        case STRING_TYPE:
          switch (op)
          {
            case EQUAL_OP:
              return create_boolean(get_value_as_string() ==
                                    right_operand.get_value_as_string());
            case NOT_EQUAL_OP:
              return create_boolean(get_value_as_string() !=
                                    right_operand.get_value_as_string());
            case GREATER_THAN_OP:
              return create_boolean(get_value_as_string() >
                                    right_operand.get_value_as_string());
            case GREATER_OR_EQUAL_THAN_OP:
              return create_boolean(get_value_as_string() >=
                                    right_operand.get_value_as_string());
            case MINOR_THAN_OP:
              return create_boolean(get_value_as_string() <
                                    right_operand.get_value_as_string());
            case MINOR_OR_EQUAL_THAN_OP:
              return create_boolean(get_value_as_string() <=
                                    right_operand.get_value_as_string());
            case TypeValuePair::TILDE_OP:
              return create_boolean(
                right_operand.get_value_as_string().find(
                  get_value_as_string(), 0) != string::npos);
            default:
              break;
          }
        default:
          throw_type_check_error(op, right_operand);
      }
    default:
      throw_type_check_error(op, right_operand);
  }
  throw TypeCheckError("Operator not found");
}

/* 
 * Throw a TypeCheckError exception with a message based on
 * operator and operands.
 */
void 
TypeValuePair::throw_type_check_error(BinaryOperators op,
                                    const TypeValuePair & right_operand) const
{
  string msg;
 
  if (get_type() == ERROR_TYPE)
  {
    msg.append(get_value_as_error());
    msg.append("\n");
  }
  if (right_operand.get_type() == ERROR_TYPE)
  {
    msg.append(right_operand.get_value_as_error());
    msg.append("\n");
  }
  if (get_type() != ERROR_TYPE && right_operand.get_type() != ERROR_TYPE)
  {
    msg.append("type check error in ");
    msg.append(get_value_image() + " (type ");
    msg.append(get_type_image() + ")");
    switch (op)
    {
      case ADD_OP:
        msg.append(" + ");
        break;
      case SUB_OP:
        msg.append(" - ");
        break;
      case MUL_OP:
        msg.append(" * ");
        break;
      case DIV_OP:
        msg.append(" / ");
        break;
      case MOD_OP:
        msg.append(" % ");
        break;
      case AND_OP:
        msg.append(" AND ");
        break;
      case OR_OP:
        msg.append(" OR ");
        break;
      case EQUAL_OP:
        msg.append(" == ");
        break;
      case NOT_EQUAL_OP:
        msg.append(" != ");
        break;
      case GREATER_THAN_OP:
        msg.append(" > ");
        break;
      case GREATER_OR_EQUAL_THAN_OP:
        msg.append(" >= ");
        break;
      case MINOR_THAN_OP:
        msg.append(" < ");
        break;
      case MINOR_OR_EQUAL_THAN_OP:
        msg.append(" <= ");
        break;
      case TILDE_OP:
        msg.append(" ~ ");
        break;
    }
    msg.append(right_operand.get_value_image() + " (type ");
    msg.append(right_operand.get_type_image() + ")");
  }
  throw TypeCheckError(msg.c_str());
}

/* Convert this type value pair to a inmediate value node. */
InmediateValueNode *
TypeValuePair::converto_to_inmediate_value_node() const
throw (TypeCheckError)
{
  InmediateValueNode * result;
  
  switch (get_type())
  {
    case BOOLEAN_TYPE:
      result = new BooleanValueNode(get_value_as_boolean());
      #ifdef DEBUG_ENABLED
      Debugger::register_malloc(result);
      #endif
      return result;
    case LONG_TYPE:
      result = new LongValueNode(get_value_as_long());
      #ifdef DEBUG_ENABLED
      Debugger::register_malloc(result);
      #endif
      return result;
    case DOUBLE_TYPE:
      result = new DoubleValueNode(get_value_as_double());
      #ifdef DEBUG_ENABLED
      Debugger::register_malloc(result);
      #endif
      return result;
    case STRING_TYPE:
      result = new StringValueNode(get_value_as_string().c_str());
      #ifdef DEBUG_ENABLED
      Debugger::register_malloc(result);
      #endif
      return result;
    case ERROR_TYPE:
    default:
      throw TypeCheckError("cannot convert an error to inmediate value node");
  }
}

}; /* End of Parser namespace. */
}; /* End of util namespace. */
}; /* End of TIDNotif namespace. */
