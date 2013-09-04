/*
 *  File name: PropertyValue.h
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

#ifndef _TIDNOTIF_UTIL_PROPERTY_VALUE_H
#define _TIDNOTIF_UTIL_PROPERTY_VALUE_H

#include <string>

#ifndef HAVE_STD_NAMESPACE
using namespace std;
#endif

namespace util
{

  /*!
   * \brief Property value virtual base class.
   */
  class PropertyValue
  {

    public:

      /*! \brief Invalid string format exception. */
      typedef struct {} InvalidStringFormat;

      /*! \brief Read only property exception. */
      typedef struct {} ReadOnlyProperty;

      /*! \brief Constructor. */
      PropertyValue(bool read_only)
        : m_read_only(read_only){}

      /*! \brief Virtual destructor. */
      virtual ~PropertyValue() {}

      /*! \brief Convert this value to a string. */
      virtual string to_string() const = 0;

      /*! \brief Convert a string to this value. */
      virtual void from_string(const string & str) 
        throw (InvalidStringFormat) = 0;

      /*! \brief Copy this value in heap. */
      virtual PropertyValue * copy() const = 0;

      /*! \brief Check if this value is read only. */
      bool is_read_only() const { return m_read_only; }

    protected:

      /*! \brief Throw ReadOnlyProperty is value is read only. */
      void try_writing() throw (ReadOnlyProperty)
        { if (m_read_only) throw ReadOnlyProperty(); }

    private:

      /*! \brief Read only flag. */
      bool m_read_only;

  }; /* End of PropertyValue class. */

}; /* End of namespace util. */

#endif
