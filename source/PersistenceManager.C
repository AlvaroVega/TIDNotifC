/*
 *  File name: PersistenceManager.C
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

#include "PersistenceManager.h"
#include "FILEPersistenceDB.h"

namespace TIDNotif {
	

const char * PersistenceManager::NONE_TYPE   = "none";
const char * PersistenceManager::ORACLE_TYPE = "oracle";
const char * PersistenceManager::FILE_TYPE   = "file";
   			
CORBA::ORB_ptr PersistenceManager::_orb   = NULL;
IOP::Codec_ptr PersistenceManager::_codec = NULL;

	
bool           PersistenceManager::initialized     = false;
PersistenceDB* PersistenceManager::_persistence_db = NULL;



	
void PersistenceManager::init(const char * db, 
                              const char * id, 
                              CORBA::ORB_ptr orb)
{

  TIDorb::core::TIDORB* _orb = 
    dynamic_cast < TIDorb::core::TIDORB* > ( (CORBA::ORB*) orb);

  if (_orb->trace != NULL) {
    TIDorb::util::StringBuffer msg;
    msg << "PersistenceManager.init(): <" << db << "> [" << id << "]" << endl;
    _orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }

  try {

    // Obtiene codec factory
    CORBA::Object_var obj = orb->resolve_initial_references("CodecFactory");
    IOP::CodecFactory_var codec_factory = IOP::CodecFactory::_narrow(obj);

    // Crea codec
    IOP::Encoding encoding;
    encoding.format = IOP::ENCODING_CDR_ENCAPS;
    encoding.major_version = (CORBA::Octet) 1;
    encoding.minor_version = (CORBA::Octet) 2;
    _codec = codec_factory->create_codec(encoding);

  } catch (CORBA::Exception& ex) {
    if (_orb->trace != NULL){
      _orb->print_trace(TIDorb::util::TR_ERROR, "Error create_codec()", ex);
    }
    throw CORBA::INITIALIZE("Error create_codec()");
  }
  
  if (initialized) {
    if (_orb->trace != NULL){
      _orb->print_trace(TIDorb::util::TR_ERROR, "Already Initialized");
    }
    throw CORBA::INITIALIZE("Already Initialized");
  }
  
  if (strcmp(db,NONE_TYPE) == 0) {
    initialized = false;
  }
  else if (strcmp(db,FILE_TYPE) == 0) {
    initialized = true;
    _persistence_db = new TIDNotif::file::FILEPersistenceDB(id);
  }
  else if (strcmp(db,ORACLE_TYPE) == 0) {
    //TODO_MORFEO: DB
    if (_orb->trace != NULL){
      _orb->print_trace(TIDorb::util::TR_ERROR, "NO IMPLEMENTED");
    }
    initialized = false;
    throw CORBA::NO_IMPLEMENT();
  }
  else{
    if (_orb->trace != NULL){
      _orb->print_trace(TIDorb::util::TR_ERROR, "NO IMPLEMENTED");
    }
    throw CORBA::NO_IMPLEMENT();
  }
}
  

PersistenceDB* PersistenceManager::getDB()
{
  return _persistence_db;
}
  
  
bool PersistenceManager::isActive()
{
  return (_persistence_db != NULL);
}
	
	 
};//namespace TIDNotif

