/*
 *  File name: StructFieldPosPath.h
 *  File type: Header file.
 *  Date : 15th February 2006
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
 *   - 04/19/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Added 'copy()' as new virtual method for EvaluableNode children.
 *   - 23/10/2008, by Alvaro Vega Garcia <avega at tid dot es>:
 *       * Removed unnecessary _var templates in declarations
 */

#ifndef _TIDUTIL_STRUCT_FIELDPOS_PATH_H
#define _TIDUTIL_STRUCT_FIELDPOS_PATH_H

#include <DynamicAny.h>
#include <CORBA.h>

#include "SequencePath.h"
#include "TypeValuePair.h"

namespace TIDNotif {
namespace util {
namespace parser {

/*!
 *
 * \brief Struct field position sequence path class.
 *
 * This class represents a sequence path's step for a
 * struct field position.
 */
class StructFieldPosPath : public SequencePath
{

  public:

    /*!
     * \brief Default constructor.
     * \param next_step Next step in sequence path.
     * \param field_pos Field position to be found.
     */
    StructFieldPosPath(SequencePath * next_step, CORBA::ULong field_pos);

    /*!
     * \brief Set field position.
     * \param field_pos New field position.
     */
    void set_field_pos(CORBA::ULong field_pos);

    /*!
     * \brief Get field position.
     * \return Field position.
     */
    CORBA::ULong get_field_pos() const;

    /*!
     * \brief Extract associated value from a Dynamic Any.
     *
     * Extract a value for this sequence step from a dynamic any.
     *
     * \param from Source dynamic any to be value-extracted.
     * \param value Value extracted from source.
     */
    virtual void extract_from_dynany(const DynamicAny::DynAny_ptr& from,
                                     DynamicAny::DynAny_ptr& value) const
      throw (BadTypeException);

    /*!
     * \brief Copy this node.
     */
    virtual EvaluableNode * copy() const;

  private:

    /*!
     * \brief Field position.
     */
    CORBA::ULong m_field_pos;

};

} /* End of namespace parser.  */
} /* End of namespace util. */
} /* End of namespace TIDNotif.  */

#endif
