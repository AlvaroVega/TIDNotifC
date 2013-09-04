// -*- c++ -*-
/*
 *  File name: CommonData.h
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

#ifndef _TIDNOTIF_COMMONDATA_H_
#define _TIDNOTIF_COMMONDATA_H_ 

#include "PortableServer.h"
#include <iostream>

namespace TIDNotif {
  
class CommonData {  //TODO_MORFEO: Serializable, Comparable
    
protected:
  static const char* READ_DATA[4]; 
  static const char* WRITE_DATA[2];
  static const char* DATA_READED[2];
  static const char* READ_OBJECT;
  static const char* WRITE_OBJECT;
    

public: 
  char* id;
  
  char* id_str();          // Identificador del Objeto
  PortableServer::POA_var poa; // TODO_MORFEO: transient public POA poa;  // Reference to its POA
  
    
  CommonData();
  CommonData(const char* id_data);
  CommonData(const char* id_data, PortableServer::POA_ptr);
  ~CommonData();
  
  int compareTo(void * o); //TODO_MORFEO: Inherited method of class Comparable 
  
  /* istream& operator>> (istream& input);*/
  /* virtual void writeObject (ostream& );
     virtual void readObject (istream& );*/
  
    
};
  /*ostream& operator<< (ostream& output, const CommonData& data);*/
  
};//namespace TIDNotif

#endif
