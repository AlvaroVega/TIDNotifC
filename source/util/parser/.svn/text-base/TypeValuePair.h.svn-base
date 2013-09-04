/*
 *  File name: TypeValuePair.h
 *  File type: Header file.
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
 *       * New method: search_in_dynany.
 *       * Enum value eliminated.
 *       * ExprType traslated to this file and TIDExprValue class remove.
 *   - 03/14/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Design major changes. See documentation for more details.
 *   - 04/10/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Tilde operator implemented and executed from TypeValuePair
 *         instead of BinaryExprNode.
 */

#ifndef _TIDUTIL_TYPEVALUEPAIR_H_
#define _TIDUTIL_TYPEVALUEPAIR_H_

#include <string>

#include <DynamicAny.h>

#ifndef HAVE_STD_NAMESPACE
using namespace std;
#endif

namespace TIDNotif {
namespace util {
namespace parser {

/* Predefinition of InmediateValueNode class. */
class InmediateValueNode;

/*!
 *
 */
class TypeValuePair {

  public:

    /*!
     * \brief Value type.
     */
    enum Type
    {
      BOOLEAN_TYPE,
      LONG_TYPE,
      DOUBLE_TYPE,
      STRING_TYPE,
      ERROR_TYPE
    };

    class TypeCheckError
    {
  
    public:
  
      TypeCheckError(const char * cause) : m_error_cause(cause) {}
      
      const string & get_cause() const { return m_error_cause; }
      
    private:
    
      string m_error_cause;
    };

    /*!
     *  \brief Copy constructor.
     */
    TypeValuePair(const TypeValuePair & pair);

    /*! \brief Assign operator.
     */
    const TypeValuePair & operator = (const TypeValuePair & pair);
    
    /*!
     * \brief Create a new boolean type value.
     * \param value New boolean value.
     */
    static TypeValuePair create_boolean(bool value);

    /*!
     * \brief Create a new boolean type value.
     * \param value New long value.
     */
    static TypeValuePair create_long(long value);

    /*!
     * \brief Create a new boolean type value.
     * \param value New double value.
     */
    static TypeValuePair create_double(double value);

    /*!
     * \brief Create a new boolean type value.
     * \param value New string value.
     */
    static TypeValuePair create_string(const char * value);

    /*!
     * \brief Create a new error type value in heap.
     * \param value Error cause.
     */
    static TypeValuePair create_error(const char * cause);

    /*!
     * \brief Get this value type pair type.
     * \return Value type pair type.
     */
    Type get_type() const;

    /*!
     * \brief Get this value type pair type image.
     * \return Value type pair type image.
     */
    string get_type_image() const;    

    /*!
     * \brief Get value as boolean type.
     * \return Boolean value.
     * \throw TypeCheckError This value type pair is not of boolean type.
     */
    bool get_value_as_boolean() const throw (TypeCheckError);

    /*!
     * \brief Get value as long type.
     * \return Long value.
     * \throw TypeCheckError This value type pair is not of long type.
     */
    long get_value_as_long() const throw (TypeCheckError);

    /*!
     * \brief Get value as double type.
     * \return Double value.
     * \throw TypeCheckError This value type pair is not of double type.
     */
    double get_value_as_double() const throw (TypeCheckError);

    /*!
     * \brief Get value as string type.
     * \return String value.
     * \throw TypeCheckError This value type pair is not of string type.
     */
    const string & get_value_as_string() const throw (TypeCheckError);

    /*!
     * \brief Get value as error type.
     * \return Error cause.
     * \throw TypeCheckError This value type pair is not of error type.
     */
    const string & get_value_as_error() const throw (TypeCheckError);

    /*!
     * \brief Get value image.
     * \return Value image.
     */
    string get_value_image() const;
    
    /*!
     * \brief Seach for this value in a DynAny.
     * \param dynany DynAny in which search will be done.
     * \return Value of search. If a bad type coerce is found,
     * an error is return. Elsewhere return a bool value indicating
     * if this value was found.
     */
    TypeValuePair search_in_dynany(const DynamicAny::DynAny_ptr& dynany) const;


    /*! \brief Add operator. */
    TypeValuePair operator + (const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief Subtract operator. */
    TypeValuePair operator - (const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief Multiply operator. */
    TypeValuePair operator * (const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief Divide operator. */
    TypeValuePair operator / (const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief Module operator. */
    TypeValuePair operator % (const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief Equal operator. */
    TypeValuePair operator == (const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief Not equal operator. */
    TypeValuePair operator != (const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief Greater than operator. */
    TypeValuePair operator > (const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief Greater or equal than operator. */
    TypeValuePair operator >= (const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief Minor than operator. */
    TypeValuePair operator < (const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief Minor or equal than operator. */
    TypeValuePair operator <= (const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief And operator. */
    TypeValuePair operator && (const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief Or operator. */
    TypeValuePair operator || (const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief Not operator. */
    TypeValuePair operator ! () const
      throw (TypeCheckError);
      
    /*! \brief Tilde operator. */
    TypeValuePair operator_tilde(const TypeValuePair & right_operand) const
      throw (TypeCheckError);

    /*! \brief Convert this type value pair to a inmediate value node. */
    InmediateValueNode * converto_to_inmediate_value_node() const
      throw (TypeCheckError);
  private:
  
    /*!
     *  \brief Default constructor.
     *
     *  This constructor doesn't build anything.
     */
    TypeValuePair();
    
    enum BinaryOperators {
      ADD_OP,
      SUB_OP,
      MUL_OP,
      DIV_OP,
      MOD_OP,
      AND_OP,
      OR_OP,
      EQUAL_OP,
      NOT_EQUAL_OP,
      GREATER_THAN_OP,
      GREATER_OR_EQUAL_THAN_OP,
      MINOR_THAN_OP,
      MINOR_OR_EQUAL_THAN_OP,
      TILDE_OP
    };

    /*!
     * \brief Perform a binary operation.
     */
    TypeValuePair operate(BinaryOperators op,
                          const TypeValuePair & right_operand) const
                          throw (TypeCheckError);

    /*!
     * \brief Throw a TypeCheckError exception with a message based on
     * operator and operands.
     */
    void throw_type_check_error(BinaryOperators op,
                                const TypeValuePair & right_operand) const;
    /*!
     * \brief Value type.
     */
    Type m_type;

    /*!
     * \brief Value as boolean.
     */
    bool m_boolean_value;

    /*!
     * \brief Value as long.
     */
    long m_long_value;

    /*!
     * \brief Value as double.
     */
    double m_double_value;

    /*!
     * \brief Value as string.
     */
    string m_string_value;

    /*!
     * \brief Value as error cause.
     */
    string m_error_cause;

};

}; /* End of Parser namespace. */
}; /* End of util namespace. */
}; /* End of TIDNotif namespace. */

#endif
