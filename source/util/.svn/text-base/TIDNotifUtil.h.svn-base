// -*- c++ -*-
/*
 *  File name: TIDNotifUtil.h
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
 *   - 17/12/2007, by Alvaro Vega <avega@tid.es>:
 *       * Code cleaning.
 */


#ifndef _TIDNOTIFUTIL_H_
#define _TIDNOTIFUTIL_H_

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
#include "TIDNotifConfig.h"

#ifndef HAVE_STD_NAMESPACE
using namespace std;
#endif

namespace TIDNotif {
namespace util {

class TIDNotifUtil {
  
public:
  
  static string tidConfigFilename(bool);
  
private:
  
  static bool check_filepath(string, bool );
  
  static void exportReference( string );
  
  static bool check_path(string, bool);

  static string IOR_EXT;
  
  static string properties_file;
}; // Class

}; // namespace util
}; // namespace TIDNotif


#endif
