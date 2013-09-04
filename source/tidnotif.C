/*
 *  File name: tidnotif.C
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

#include <CORBA.h>
#include "ServiceManager.h"
#include <iostream>

using namespace std;

int main (int argc, char **argv)
{

  if (argc <= 1) {
    cerr << "TIDNotif agent 1.0.0 for Notification Service (c) Telefonica I+D." << endl;
    cerr << "tidnotif { start | stop | halt | factory [arguments] } < agent.ior" << endl;
    return 1;
  }
  
  
  CORBA::ORB_ptr orb = CORBA::ORB_init(argc, argv);

  CORBA::Object_var object;
  
  string ior;
  cin >> ior;
  
  try{
    object = orb->string_to_object(ior.c_str());
  } catch(CORBA::Exception& ex) {
    cerr << "ERROR tidnotif: CORBA::Exception:" << ex._name() << endl;        
    return 1;
  }
  
  ServiceManager::ServiceAdmin_var service;
  
  service = ServiceManager::ServiceAdmin::_narrow(object);

  try{  
    
    string op = argv[1];
    if (op=="start"){
      service->start_service(); // TODO: mem leak
      cerr << "Notification Service started" << endl;
    }
    else if (op=="stop"){
      service->shutdown_service();
      cerr << "Notification Service stopped" << endl;
    }
    else if (op=="factory"){
      cout << service->get_factory_ref() << endl;
    }
    else if (op=="halt"){
      service->halt_service();
      cerr << "Notification Service halted!" << endl;
    }
    else{
      cerr << "No implemented" << endl;
      return 1;
    }

  } catch (CORBA::SystemException &ex) {
    cerr << "ERROR tidnotif: CORBA::SystemException:" << ex._name() << endl;    
  } catch (CORBA::Exception &ex) {
    cerr << "ERROR tidnotif: CORBA::Exception:" << ex._name() << endl;
  } catch (...) {
    cerr << "ERROR tidnotif: Unknowed exception" << endl;
    return 1;
  }
  
  return 0;
}
