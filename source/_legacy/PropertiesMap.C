/*
 *  File name: PropertiesMap.C
 *  File type: Body file.
 *  Date : April 27th 2006
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

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "PropertiesMap.h"

/* Default constructor. */
util::PropertiesMap::PropertiesMap()
{}

/* Key value pairs constructor. */
util::PropertiesMap::PropertiesMap(const PropertiesMap & map)
{
  PropertyValuesMap::const_iterator it;

  for (it = map.m_properties.begin(); it != map.m_properties.end(); it++)
    m_properties[it->first] = it->second->copy();
}

/*! Destructor. */
util::PropertiesMap::~PropertiesMap()
{
  PropertyValuesMap::iterator it;

  for (it = m_properties.begin(); it != m_properties.end(); it++)
    delete it->second;
}

/* Add new property values to map. */
void
util::PropertiesMap::add_property_values(const KeyValuePairs & pairs,
                                         bool create_news)
throw (PropertyNotFound)
{
  PropertyValue * value;

  for (int i = 0; i < pairs.pairc; i+=2)
  {
    try
    {
      value = find(pairs.pairv[i]);
      value->from_string(pairs.pairv[i + 1]);
    }
    catch (PropertyNotFound & e)
    {
      if (create_news)
        m_properties[pairs.pairv[i]] = 
          new StringPropertyValue(pairs.pairv[i + 1]);
      else
        throw e;
    }
  }
}

/* Get a property value. */
util::PropertyValue &
util::PropertiesMap::get_property_value(const string & property)
throw (PropertyNotFound)
{
  return *find(property);
}

/* Get a constant property value. */
const util::PropertyValue &
util::PropertiesMap::get_property_value(const string & property) const
throw (PropertyNotFound)
{
  return *find(property);
}

/* Set a property value. */
void
util::PropertiesMap::set_property_value(const string & name,
                                        const PropertyValue & value)
{
  bind_property_value(name, value.copy());
}

/* Bind a property value pointer. */
void
util::PropertiesMap::bind_property_value(const string & name,
                                         PropertyValue * value)
{
  util::PropertyValue * old_value;

  try
  {
    old_value = find(name);
    delete old_value;
  }
  catch (PropertyNotFound & e)
  {}
  m_properties[name] = value;
}


/* Find a property in map. */
const util::PropertyValue *
util::PropertiesMap::find(const string & prop) const
throw (PropertyNotFound)
{
  PropertyValuesMap::const_iterator it;
  it = m_properties.find(prop);
  if (it == m_properties.end())
    throw PropertyNotFound(prop);
  return it->second;
}

/* Find a property in map. */
util::PropertyValue *
util::PropertiesMap::find(const string & prop)
throw (PropertyNotFound)
{
  PropertyValuesMap::iterator it;
  it = m_properties.find(prop);
  if (it == m_properties.end())
    throw PropertyNotFound(prop);
  return it->second;
}
