/*
 *  File name: CommonData.C
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

#include "CommonData.h"

#include <CORBA.h>



	
const char* TIDNotif::CommonData::READ_DATA[4]   = { "   READ DATA: ",  NULL, ", ", NULL };  
const char* TIDNotif::CommonData::WRITE_DATA[2]  = { "   WRITE DATA: ", NULL };
const char* TIDNotif::CommonData::DATA_READED[2] = { "   DATA READED: ", NULL };
const char* TIDNotif::CommonData::READ_OBJECT    = "   READ_OBJECT()";
const char* TIDNotif::CommonData::WRITE_OBJECT   = "   WRITE_OBJECT()";
  	  
TIDNotif::CommonData::CommonData()
  : id(NULL), poa(NULL)
{

}

TIDNotif::CommonData::CommonData(const char* id_data)
  : poa(NULL)
{
  id = CORBA::string_dup(id_data);
}

TIDNotif::CommonData::CommonData(const char* id_data, 
                                 PortableServer::POA_ptr poa_up)
  : poa(poa_up)
{
  id = CORBA::string_dup(id_data);
}

TIDNotif::CommonData::~CommonData()
{
  CORBA::string_free(id);
}

char* TIDNotif::CommonData::id_str()
{
  return CORBA::string_dup(id);
}


/*istream& CommonData::operator>> (istream& input){
  readObject(input);
  }
  ostream& operator<< (ostream& output, const CommonData& data){
  data.writeObject(output);
  }*/

int TIDNotif::CommonData::compareTo(void * o)
{
  throw CORBA::NO_IMPLEMENT("No Implemented");
}; //TODO_MORFEO: Inherited method of class Comparable 
	 
  


