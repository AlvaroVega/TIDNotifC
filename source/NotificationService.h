// -*- c++ -*-
/*
 *  File name: NotificationService.h
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

#ifndef _TIDNOTIF_NOTIFICATIONSERVICE_H_
#define _TIDNOTIF_NOTIFICATIONSERVICE_H_ 

#include "CORBA.h"
#include "PortableServer.h"
#include "TIDThr.h"
#include "ServiceManager.h"
#include "CosNotifyChannelAdmin.h"
#include "TIDorb/core.h"
#include "EventChannelFactoryImpl.h"


namespace TIDNotif{

class NotificationService
{
 
private:

  TIDorb::core::TIDORB* _orb;
  CosNotifyChannelAdmin::EventChannelFactory_ptr factory_ref;
  EventChannelFactoryImpl* factory_servant;
  PortableServer::POA_ptr root_poa;
  PortableServer::POAManager_var poa_manager;
  PortableServer::POA_var tidnotif_poa;

  string port;
  string ssl_port;

  bool port_given;
  bool ssl_port_given;
  bool ssl_config;

  string persDB;
  string persID;

  static NotificationService* notification_service;
  
protected: 
  
  NotificationService(int argc, char** argv);
      
  ~NotificationService();

public:

  ServiceManager::ServiceState get_state();
  
  CORBA::ORB_ptr get_orb();
  
  const char* restore_service();
    
  const char* create_service();
  
  void destroy_service();
  
  void shutdown_service();
  
  void run();

  static NotificationService& init(int argc, char** argv);
  
  NotificationService& get_notification();
		
  //static NotificationService& get_service();
  
};

} //namespace TIDNotif
#endif
