/*
 *  File name: FileUID.C
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

#include "FileUID.h"
#include <CORBA.h>
#include "TIDorb/util.h"

namespace TIDNotif {
namespace file {


FileUID::FileUID (string path)
{
  bool exists = true;
  accessor.open(path.c_str(),ios::in|ios::out|ios::binary);
  
  if(!accessor.good())
    {
      accessor.open(path.c_str(),ios::out|ios::binary);
      exists = false;
    }
  
  if(!exists)
    {
      uid = 0;
      writeUID();
    }
  else
    {
      TIDThr::Synchronized sync(_recursive_mutex);
      //accessor.seekp(0); //TODO_MORFEO: i must read the last uid of file
      
      accessor.read((char *)&uid,sizeof(int));
    }
}
  
void FileUID::destroy()
{
  TIDThr::Synchronized sync(_recursive_mutex);
  accessor.close();
}

string FileUID::getUID()
{
  TIDThr::Synchronized sync(_recursive_mutex);
  uid++;
  writeUID();
  TIDorb::util::StringBuffer buffer;
  buffer << uid;
  string s_uid = buffer.str().data();
  return s_uid;
}

void FileUID::writeUID()
{
  TIDThr::Synchronized sync(_recursive_mutex);
  //TODO_MORFEO: it doesn't write in disk (uid.data), why?
  accessor<<uid<<endl;
  accessor.flush();
}

FileUID::~FileUID()
{
  destroy();
}

}//namespace file
}//namespace TIDNotif


