/*
 *  File name: FILEPersistenceDBMsg.C
 *  File type: Body file.
 *  Date : March 2006
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
 *   - 04/04/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Code cleaning.
 */

#include "FILEPersistenceDBMsg.h"
#include <stdlib.h>
namespace TIDNotif
{

  namespace file
  {
    const char* FILEPersistenceDBMsg::SAVE[5] =
      { " +>FILEPersistenceDB.save(", NULL, ") [", NULL, "]" };

    const char* FILEPersistenceDBMsg::UPDATE[5] =
      { " +>FILEPersistenceDB.update(", NULL, ") [", NULL, "]" };

    const char* FILEPersistenceDBMsg::DELETE[5] =
      { " +>FILEPersistenceDB.delete(", NULL, ") [", NULL, "]" };

    const char* FILEPersistenceDBMsg::LOAD[3] =
      { " +>FILEPersistenceDB.load(", NULL, ")" };

    const char* FILEPersistenceDBMsg::PERSISTENCE_ERROR =
"*** MUTUAL INCOMPATIBILITY BETWEEN PERSISTENT DATA AND SERVICE VERSION ***";

  }//namespace file
}//namespace TIDNotif

