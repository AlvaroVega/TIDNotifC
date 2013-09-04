/*
 *  File name: PersistenceDB.C
 *  File type: Body file.
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

#include "PersistenceDB.h"

namespace TIDNotif {

  //
  // Common
  static const int STATE                     = 0;

  //
  // Input
  static const int OBJ_CHANNEL               = 0;
  static const int OBJ_SUPPLIER_ADMIN        = 1;
  static const int OBJ_PROXY_PUSH_CONSUMER   = 2;
  static const int OBJ_PROXY_PULL_CONSUMER   = 3;
  static const int OBJ_CONSUMER_ADMIN        = 4;
  static const int OBJ_PROXY_PUSH_SUPPLIER   = 5;
  static const int OBJ_PROXY_PULL_SUPPLIER   = 6;
  static const int OBJ_DISCRIMINATOR         = 7;
  static const int OBJ_INDEXLOCATOR          = 8;
  static const int OBJ_TRANSFORMING_OPERATOR = 9;
  static const int OBJ_MAPPING_DISCRIMINATOR = 10;

  static const int ATTR_ADMINISTRATIVE_STATE  = 0;
  static const int ATTR_DISCRIMINATOR         = 1;
  static const int ATTR_INDEXLOCATOR          = 2;
  static const int ATTR_MAPPING_DISCRIMINATOR = 3;
  static const int ATTR_D_ERROR_HANDLER       = 4;
  static const int ATTR_ORDER                 = 5;
  static const int ATTR_ORDER_GAP             = 6;
  static const int ATTR_TRANSFORMING_OPERATOR = 7;
  static const int ATTR_T_ERROR_HANDLER       = 8;
  static const int ATTR_SUPPLIER_ADMIN        = 9;
  static const int ATTR_SUPPLIER_ADMIN_PARENT = 10;
  static const int ATTR_SUPPLIER_ADMIN_CHILD  = 11;
  static const int ATTR_PROXY_PUSH_CONSUMER   = 12;
  static const int ATTR_PROXY_PULL_CONSUMER   = 13;
  static const int ATTR_CONSUMER_ADMIN        = 14;
  static const int ATTR_CONSUMER_ADMIN_PARENT = 15;
  static const int ATTR_PROXY_PUSH_SUPPLIER   = 16;
  static const int ATTR_PROXY_PULL_SUPPLIER   = 17;
  static const int ATTR_EXTENDED_CRITERIA     = 18;
  static const int ATTR_PUSH_SUPPLIER         = 19;
  static const int ATTR_PULL_SUPPLIER         = 20;
  static const int ATTR_PUSH_CONSUMER         = 21;
  static const int ATTR_PULL_CONSUMER         = 22;

  static const int ATTR_SUPPLIER_ADMIN_TABLES = 23;
  static const int ATTR_PUSH_CONSUMER_TABLE   = 24;
  static const int ATTR_PULL_CONSUMER_TABLE   = 25;
  static const int ATTR_CONSUMER_ADMIN_TABLES = 26;
  static const int ATTR_PUSH_SUPPLIER_TABLE   = 27;
  static const int ATTR_PULL_SUPPLIER_TABLE   = 28;
  static const int ATTR_CONSTRAINTS           = 29;
  static const int ATTR_TRANSFORMING_RULES    = 30;

  static const int ATTR_DEFAULT_PRIORITY      = 31;
  static const int ATTR_DEFAULT_LIFETIME      = 32;
  static const int ATTR_LEVEL                 = 33;

  // type
  static const int PUSH = 0;
  static const int PULL = 1;
};
