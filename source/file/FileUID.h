/*
 *  File name: FileUID.h
 *  File type: Header file.
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


#ifndef _TIDNOTIF_FILEUID_H_
#define _TIDNOTIF_FILEUID_H_

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <TIDThr/Thread.h>


using namespace std;



namespace TIDNotif {
namespace file {

class FileUID {

private:
  int uid;

  fstream accessor;

  TIDThr::RecursiveMutex _recursive_mutex;

public:
  FileUID (string path);
  ~FileUID();

  void destroy(void); 

  string getUID(void);

protected:

  void writeUID(void);


};

}//namespace file
}//namespace TIDNotif
#endif
