/*
 *  File name: PropertiesMap.h
 *  File type: Header file.
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

#ifndef _TIDNOTIF_UTIL_PROPERTIES_MAP_H
#define _TIDNOTIF_UTIL_PROPERTIES_MAP_H

#include <map>
#include <string>

#include "PropertyValue.h"
#include "BoolPropertyValue.h"
#include "LongPropertyValue.h"
#include "StringPropertyValue.h"

#ifndef HAVE_STD_NAMESPACE
using namespace std;
#endif

namespace util {

/*!
 * \brief Properties map class.
 *
 * This class implements a properties map. It stores a pool of key-value
 * pairs.
 *
 */
class PropertiesMap
{

  public:

    /*!
     * \brief Odd string array error exception.
     *
     * This exception indicates an odd string array size.
     *
     */
    typedef struct OddStringArraySize
    {
      OddStringArraySize(int size) : invalid_size(size) {}
      int invalid_size;
    } OddStringArraySize;

    /*!
     * \brief Type coerce error exception.
     *
     * This exception indicates an invalid type coerce in
     * a property value conversion.
     *
     */
    typedef struct BadTypeCoerce
    {
      BadTypeCoerce(const string & from, const string & to)
        : source_type(from), target_type(to) {}
      string source_type;
      string target_type;
    } BadTypeCoerce;

    /*! \brief Property not found exception. */
    typedef struct PropertyNotFound
    {
      PropertyNotFound(const string & name) : property_name(name) {}
      string property_name;
    } PropertyNotFound;

    /*!
     * \brief Key value pairs structure.
     *
     * This structure encapsulates an array of key value pairs
     * and such pairs count. It's supplied a constructor which
     * may raise a OddStringArraySize exception if members count
     * is odd.
     */
    typedef struct KeyValuePairs
    {
      KeyValuePairs(const char ** str_array, int str_array_count)
        : pairv(str_array), pairc(str_array_count / 2)
          {
            if (str_array_count % 2 == 1)
              throw util::PropertiesMap::OddStringArraySize(
                str_array_count);
          }
      const char ** pairv;
      int pairc;
    } KeyValuePairs;

    /*! \brief Default constructor. */
    PropertiesMap();

    /*!
     * \brief Copy constructor.
     * \param map Map to be copied.
     */
    PropertiesMap(const PropertiesMap & map);

    /*! \brief Destructor. */
    ~PropertiesMap();

    /*!
     * \brief Add new property values to map.
     * \param pairs Property values to be added.
     * \param create_news If property doesn't exists, a new string
     * property is created if 'create_news' is set to true. Elsewhere,
     * a PropertyNotFound will be raised.
     * \throw PropertyNotFound If 'create_news' is set to false and
     * a property name is not found, this exception will be raised.
     */
    void add_property_values(const KeyValuePairs & pairs, 
                             bool create_news = true)
      throw (PropertyNotFound);

    /*!
     * \brief Get a property value.
     * \param property Property name to seek for.
     * \return Property value.
     * \throw PropertyNotFound Property name was not found in map.
     */
    PropertyValue & get_property_value(const string & property)
      throw (PropertyNotFound);

    /*!
     * \brief Get a constant property value.
     * \param property Property name to seek for.
     * \return Constant property value.
     * \throw PropertyNotFound Property name was not found in map.
     */
    const PropertyValue & get_property_value(const string & property) const
      throw (PropertyNotFound);

    /*!
     * \brief Set a property value.
     * \param name Property name to be set.
     * \param value Property value to be set.
     */
    void set_property_value(const string & name,
                            const PropertyValue & value);

  protected:

    typedef map<string, PropertyValue*> PropertyValuesMap;

    PropertyValuesMap m_properties;

    /*!
     * \brief Bind a property value pointer.
     * \param name Property name to be set.
     * \param value Property value pointer to be bound in map.
     */
    void bind_property_value(const string & name,
                            PropertyValue * value);

    /*!
     * \brief Find a property in map.
     * \return Property value pointer (do not release it!!!).
     * \throw PropertyValue Raised if property was not found in map.
     */
    const PropertyValue * find(const string & prop) const
      throw (PropertyNotFound);

    /*!
     * \brief Find a property in map.
     * \return Property value pointer (do not release it!!!).
     * \throw PropertyValue Raised if property was not found in map.
     */
    PropertyValue * find(const string & prop)
      throw (PropertyNotFound);
};

}; /* End of namespace util. */

#endif
