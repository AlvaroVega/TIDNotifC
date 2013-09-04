/*
 *  File name: LongPropertyValue.h
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

#ifndef _TIDNOTIF_UTIL_LONG_PROPERTY_VALUE_H
#define _TIDNOTIF_UTIL_LONG_PROPERTY_VALUE_H

#include <string>

#include "PropertyValue.h"

#ifndef HAVE_STD_NAMESPACE
using namespace std;
#endif

namespace util
{

  /*!
   * \brief Long property value class.
   */
  class LongPropertyValue : public PropertyValue
  {

    public:

      /*! \brief Bounds error exception. */
      typedef struct BoundsError
      {
        BoundsError(long min_value, long max_value, long value)
          : min(min_value), max(max_value), invalid_value(value) {}
        long min;
        long max;
        long invalid_value;
      } BoundsError;

      /*! \brief Value constructor. */
      LongPropertyValue(long value, bool read_only = false);

      /*! \brief Value and bounds constructor. */
      LongPropertyValue(long value, 
                        long min,
                        long max,
                        bool read_only = false);

      /*! \brief Convert this value to a string. */
      virtual string to_string() const;

      /*! \brief Convert a string to this value. */
      virtual void from_string(const string & str) 
        throw (InvalidStringFormat);

      /*! \brief Copy this value in heap. */
      virtual PropertyValue * copy() const;

      /*! \brief Get value. */
      long get_value() const;

      /*! \brief Set value. */
      void set_value(long value)
        throw (ReadOnlyProperty, BoundsError);

    private:

      /*! \brief Bounds set flag. */
      bool m_has_bounds;

      /*! \brief Lower bound. */
      long m_min_value;

      /*! \brief Upper bound. */
      long m_max_value;

      /*! \brief Value. */
      long m_value;

  }; /* End of LongPropertyValue class. */

}; /* End of namespace util. */

#endif
