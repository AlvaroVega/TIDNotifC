/*
 *  File name: notifd.C
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

#include "TIDNotif.h"
#include "ServiceAdminImpl.h"
#include "ServiceManager.h"
#include "NotificationService.h"
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>


using namespace std;



TIDNotif::ServiceAdminImpl* serviceAdmin = NULL;


void Stop (int){
  try{
    serviceAdmin->shutdown_service();
  } catch(const ServiceManager::NotStarted& ex) {
    cerr << "TIDNotif is not started!" << endl;
    exit(1);
  }

  exit(0);
}


void
printWelcome()
{
  cerr << "TIDNotif, Telefonica I+D CORBA Notification Service" << endl;
  cerr << "Copyright (c) 1998-2009 Telefonica "\
          "Investigacion y Desarrollo S.A." << endl;
  cerr << "All rights reserved" << endl << endl;
  cerr << "TIDNotif C++ version " << TIDNotif::st_version << endl;
}


int main(int argc, char ** argv){

  printWelcome();

  signal(SIGINT, Stop);

  try {

    // Start TIDThread library
    TIDThr::init();

    serviceAdmin = new TIDNotif::ServiceAdminImpl(argc, argv);
    serviceAdmin->run();
    
    delete serviceAdmin;

  } catch(const CORBA::Exception& exc) {
    cerr << "TIDNotif stop due a CORBA::Exception: " << exc << endl;
    return 1;
  } catch(...) {
    cerr << "TIDNotif stop due an unknown exception: " << endl;
    return 1;
  }

  
  return 0;

}
