/*
 *  File name: TIDNotifUtil.C
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
 *   - 17/12/2007, by Alvaro Vega <avega@tid.es>:
 *       * Code cleaning.
 */

#include "TIDNotifUtil.h"
#include "CORBA.h"

#include <stdlib.h>

#include <fstream>
#include <iostream>


string TIDNotif::util::TIDNotifUtil::IOR_EXT = ".ior";

string TIDNotif::util::TIDNotifUtil::properties_file = "";



bool TIDNotif::util::TIDNotifUtil::check_path(string pathname, bool mk_dir)
{
  fstream file(pathname.c_str(),ios::in);
  if (file) { 
    file.close(); 
    return true;
  }
  if (mk_dir) {
    return !mkdir(pathname.c_str(),0755);
  }
  return false;
}



bool TIDNotif::util::TIDNotifUtil::check_filepath(string pathname, bool mk_dir)
{
  int index = pathname.find_last_of("/", pathname.length());
  string parent = pathname.erase(index);
  fstream file(parent.c_str(), ios::in);

  if (file) { 
    file.close(); 
    return true;
  }
  if (mk_dir){
    return mkdir(parent.c_str(), 0755);
  }
  return false;
}

string TIDNotif::util::TIDNotifUtil::tidConfigFilename(bool mkdir)
{
  if (properties_file == "") {
    string the_file;
    the_file.append(TIDNotifConfig::get((char*)TIDNotifConfig::DATA_PATH_KEY));
  
    if (!TIDNotifUtil::check_path(the_file, mkdir))
      throw CORBA::UNKNOWN("IO Exception");

    the_file.append("/");
    the_file.append(TIDNotifConfig::get((char*)TIDNotifConfig::DATA_ROOT_KEY));

    if (!TIDNotifUtil::check_path(the_file,mkdir))
      throw CORBA::UNKNOWN("IO exception");

    the_file.append("/");
    the_file.append(TIDNotifConfig::get((char*)TIDNotifConfig::ADMIN_PORT_KEY));

    if (!TIDNotifUtil::check_path(the_file,mkdir))
      throw CORBA::UNKNOWN("IO exception");

    the_file.append("/");
    the_file.append(TIDNotifConfig::get((char*)TIDNotifConfig::PROPS_FILENAME_KEY));
    properties_file = the_file;
  }
  return properties_file;
}


void TIDNotif::util::TIDNotifUtil::exportReference(string reference)
{
  if (TIDNotifConfig::getBool((char*)TIDNotifConfig::IOR_TO_FILE_KEY)) {

    string the_file;
    the_file.append(TIDNotifConfig::get((char*)TIDNotifConfig::DATA_PATH_KEY));

    if (!check_path(the_file, true)) {
      throw CORBA::UNKNOWN("IO exception");
    }

    the_file.append("/");
    the_file.append(TIDNotifConfig::get((char*)TIDNotifConfig::IOR_FILENAME_KEY));
    the_file.append("_");
    the_file.append(TIDNotifConfig::get((char*)TIDNotifConfig::ADMIN_PORT_KEY));
    the_file.append(IOR_EXT);
    
    if (!check_filepath(the_file, true)) {
      throw CORBA::UNKNOWN("IO exception");
    }
    else {
      try {
        fstream file(the_file.c_str(), ios::out);
        file << reference << endl;
      } catch (...) {
        cerr << "\nWarning: Cannot write agent reference to file." << endl;
      }
    }
  }
}

