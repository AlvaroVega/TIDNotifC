// -*- c++ -*-
/*
 *  File name: ServiceAdminImpl.h
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

#ifndef _TIDNOTIF_SERVICEADMINIMPL_H_
#define _TIDNOTIF_SERVICEADMINIMPL_H_ 

#include "POA_ServiceManager.h"
#include "NotificationService.h"


namespace TIDNotif{

class ServiceAdminImpl : public virtual POA_ServiceManager::ServiceAdmin
{
 
private:

  ServiceManager::ServiceState state;
  NotificationService& service;
  CORBA::String_var ior_ref;

public: 
  
  ServiceAdminImpl(int argc, char** argv);
  
  ~ServiceAdminImpl();
  
  char* start_service() throw(ServiceManager::AlreadyStarted);
  
  void shutdown_service() throw(ServiceManager::NotStarted);
  
  char* get_factory_ref() throw(ServiceManager::NotStarted);
		
  void halt_service() throw(ServiceManager::NotStarted);

  void run();

private:

  void activate(CORBA::ORB_ptr orb);
		
  
};
}; //namespace TIDNotif
#endif
