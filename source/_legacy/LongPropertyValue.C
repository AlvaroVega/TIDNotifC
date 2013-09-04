/*
 *  File name: LongPropertyValue.C
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

#include "LongPropertyValue.h"

/* Value constructor. */
util::LongPropertyValue::LongPropertyValue(long value, bool read_only)
:
PropertyValue(read_only),
m_has_bounds(false),
m_value(value)
{}

/* Value and bounds constructor. */
util::LongPropertyValue::LongPropertyValue(long value,
                                           long min,
                                           long max,
                                           bool read_only)
:
PropertyValue(read_only),
m_has_bounds(true),
m_min_value(min),
m_max_value(max),
m_value(value)

{}

/* Convert this value to a string. */
string
util::LongPropertyValue::to_string() const
{
  char buff[255];

  sprintf(buff, "%li", m_value);
  return buff;
}

/* Convert a string to this value. */
void
util::LongPropertyValue::from_string(const string & str) 
throw (InvalidStringFormat)
{
  errno = 0;
  m_value = strtol(str.c_str(), NULL, 10);
  if (errno)
    throw InvalidStringFormat();
}

/* Copy this value in heap. */
util::PropertyValue *
util::LongPropertyValue::copy() const
{
  return new LongPropertyValue(*this);
}

/* Get value. */
long
util::LongPropertyValue::get_value() const
{
  return m_value;
}

/* Set value. */
void
util::LongPropertyValue::set_value(long value)
throw (ReadOnlyProperty, BoundsError)
{
  try_writing();
  if (m_has_bounds && 
      (m_value < m_min_value || m_value > m_max_value))
      throw BoundsError(m_min_value, m_max_value, value);
  m_value = value;
}
