// -*- c++ -*-
/*
 *  File name: PersistenceManager.h
 *  File type: Header file.
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

#ifndef _TIDNOTIF_PERSISTENCEMANAGER_H_
#define _TIDNOTIF_PERSISTENCEMANAGER_H_ 

#include <stdlib.h>

#include "CORBA.h"
#include "IOP.h"
#include "PersistenceDB.h"


namespace TIDNotif {
	
class PersistenceManager 
{

 public:

  static const char * NONE_TYPE;
  static const char * ORACLE_TYPE;
  static const char * FILE_TYPE;
  
  static CORBA::ORB_ptr _orb;
  static IOP::Codec_ptr _codec;
  
 private:

  static bool initialized;
  static PersistenceDB* _persistence_db;
  
  
 public:
  
  static void init(const char * db, const char * id, CORBA::ORB_ptr orb);
  
  
  static PersistenceDB* getDB();
  
  
  static bool isActive();
  
  
  
};
	
	 
};//namespace TIDNotif
#endif
