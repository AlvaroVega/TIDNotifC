/*
 *  File name: BoolPropertyValue.C
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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "BoolPropertyValue.h"

/* Value constructor. */
util::BoolPropertyValue::BoolPropertyValue(bool value, bool read_only)
:
PropertyValue(read_only),
m_value(value)
{}

/* Convert this value to a string. */
string
util::BoolPropertyValue::to_string() const
{
  if (m_value)
    return "true";
  else
    return "false";
}

/* Convert a string to this value. */
void
util::BoolPropertyValue::from_string(const string & str) 
throw (InvalidStringFormat)
{
  if (str == "true" || str == "TRUE")
    m_value = true;
  else if (str == "false"|| str == "FALSE")
    m_value = false;
  else
    throw InvalidStringFormat();
}

/* Copy this value in heap. */
util::PropertyValue *
util::BoolPropertyValue::copy() const
{
  return new BoolPropertyValue(*this);
}

/* Get value. */
bool
util::BoolPropertyValue::get_value() const
{
  return m_value;
}

/* Set value. */
void
util::BoolPropertyValue::set_value(bool value)
throw (ReadOnlyProperty)
{
  try_writing();
  m_value = value;
}