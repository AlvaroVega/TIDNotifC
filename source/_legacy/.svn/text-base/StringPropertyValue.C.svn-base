/*
 *  File name: StringPropertyValue.C
 *  File type: Header file.
 *  Date : May 10th 2006
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
 */


#include "StringPropertyValue.h"

/* Value constructor. */
util::StringPropertyValue::StringPropertyValue(const string & value, 
                                               bool read_only)
:
PropertyValue(read_only),
m_value(value)
{}

/* Convert this value to a string. */
string
util::StringPropertyValue::to_string() const
{
  return m_value;
}

/* Convert a string to this value. */
void
util::StringPropertyValue::from_string(const string & str) 
throw (InvalidStringFormat)
{
  m_value = str;
}

/* Copy this value in heap. */
util::PropertyValue *
util::StringPropertyValue::copy() const
{
  return new StringPropertyValue(*this);
}

/* Get value. */
string
util::StringPropertyValue::get_value() const
{
  return m_value;
}

/* Set value. */
void
util::StringPropertyValue::set_value(const string & value)
throw (ReadOnlyProperty)
{
  try_writing();
  m_value = value;
}
