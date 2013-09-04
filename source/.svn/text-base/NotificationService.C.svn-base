/*
 *  File name: NotificationService.C
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

#include "NotificationService.h"
#include "TIDorb/util.h"
#include "TIDNotifConfig.h"
#include "ThePOAFactory.h"
#include "PersistenceManager.h"
#include "AlreadyInitialized.h"
#include "NotInitialized.h"



TIDNotif::NotificationService* 
TIDNotif::NotificationService::notification_service = NULL;
    
 
  
TIDNotif::NotificationService::NotificationService(int argc, char** argv){

  // Start TIDNotifConfig

  port_given     = false;
  ssl_port_given = false;
  ssl_config     = false;

  util::TIDNotifConfig* notifConfig = 
    util::TIDNotifConfig::init((const char **)(&argv[1]), argc-1);
  
  port     = util::TIDNotifConfig::get(util::TIDNotifConfig::ADMIN_PORT_KEY);
  ssl_port = util::TIDNotifConfig::get(util::TIDNotifConfig::ADMIN_SSL_PORT_KEY);

  if (strcmp(port.c_str(), "0") != 0)
    port_given = true;

  if (strcmp(ssl_port.c_str(), "0") != 0)
    ssl_port_given = true;


  // Check if ORB port options were provided
  if ( (!port_given) || (!ssl_port_given) ) {

    for (int i = 0; i < argc; i++) {
      if (strcmp(argv[i], "-ORB_iiop_orb_port") == 0)  {
        if (! port_given == 0) {
          port_given = true;
          port = argv[i+1];
          util::TIDNotifConfig::set(util::TIDNotifConfig::ADMIN_PORT_KEY, port.c_str());
        }
       }
      
      if (strcmp(argv[i], "-ORB_ssl_port") == 0) {
        if (! ssl_port_given == 0) {
          ssl_port_given = true; 
          ssl_port = argv[i+1];
          util::TIDNotifConfig::set(util::TIDNotifConfig::ADMIN_SSL_PORT_KEY, ssl_port.c_str());
        }
      }
    }
  }


  // Add iiop/ssliop port ORB to options: latest arguments prevail always
  int offset = (port_given ? 2 : 0) + (ssl_port_given ? 2 : 0);
  int _argc = argc + offset; 
  char * _argv[_argc];
  int i = 0;
  while (i < _argc - offset) {

    // Check if SSL configuration is present
    if (strcmp(argv[i], "-ORB_ssl_private_key") == 0) {
      for (int j = 0; j < argc; j++) {
        if (strcmp(argv[j], "-ORB_ssl_certificate") == 0) {
          ssl_config = true;
          break;
        }
      }
    }

    _argv[i] = argv[i];
    i++;
  }
  if (port_given) {
    _argv[i++] = "-ORB_iiop_orb_port";
    _argv[i++] = CORBA::string_dup(port.c_str());
  }

  if (ssl_port_given) {
    _argv[i++] = "-ORB_ssl_port";
    _argv[i++] = CORBA::string_dup(ssl_port.c_str());
  }

  // ORB init
  try {
    CORBA::ORB_ptr orb = CORBA::ORB_init (_argc, _argv);
    
    _orb = dynamic_cast<TIDorb::core::TIDORB*>(CORBA::ORB::_duplicate(orb));
    
    root_poa = TIDNotif::ThePOAFactory::rootPOA(_orb);
  } catch (const CORBA::INITIALIZE & ex) {
    cerr << "ERROR: cannot initialize Notification Service at port ";
    if (ssl_config) 
      cerr << ssl_port;
    else
      cerr << port;
    cerr << " due to: " << ex << endl;
  } catch (const CORBA::Exception& ex) {
    cerr << "ERROR: Naming Server Exception: " << ex << endl << flush;
    exit (1);
  }

  

  // PersistenceManager init
  persDB = util::TIDNotifConfig::get(util::TIDNotifConfig::PERS_DB_KEY);
  persID = port;
  //  TIDNotif::PersistenceManager::init(persDB.c_str(), persID.c_str(), _orb);
  
  factory_ref = NULL;
  factory_servant = NULL;
  poa_manager = NULL;
  tidnotif_poa = NULL;
}
  

TIDNotif::NotificationService::~NotificationService()
{
  if (_orb->trace != NULL){
    _orb->print_trace(TIDorb::util::TR_DEEP_DEBUG, 
                      "~NotificationService()...");
  }
  this->shutdown_service();
  //TODO_MORFEO: check that it calls to destructor of TIDThr::Thread
}

  
ServiceManager::ServiceState TIDNotif::NotificationService::get_state(){

  //to verify that the EventChannelFactory is really up 
  try
    {
      factory_ref->get_all_channels();
    }
  catch (CORBA::TRANSIENT & e)
    {
      return ServiceManager::stopped;
    }
  catch (CORBA::COMM_FAILURE & e)
    {
      return ServiceManager::stopped;
    }
  catch (CosEventComm::Disconnected & e)
    {
      return ServiceManager::stopped;
    }
  catch (CORBA::OBJECT_NOT_EXIST & e)
    {
      return ServiceManager::stopped;
    }
  return ServiceManager::started;
}

  
CORBA::ORB_ptr TIDNotif::NotificationService::get_orb(){
  return _orb;
}
    

const char* TIDNotif::NotificationService::restore_service(){

//   if (notification_service != NULL) {
//     if (_orb->trace != NULL){
//       TIDorb::util::StringBuffer msg;
//       msg << "NotiificationService::restore_service AlreadyInitialized";
//       _orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
//     }
//     throw AlreadyInitialized("Notification Service has been initialized");
//   }
  
  //util::TIDNotifConfig::restore();
  
  if (TIDNotif::PersistenceManager::isActive()){
    
    tidnotif_poa = TIDNotif::ThePOAFactory::newPOA("TIDNotifPOA",
                                                   root_poa,
                                                   true,
                                                   TIDNotif::ThePOAFactory::_ADMIN_POA);

    try{
      // Start POAManager
      poa_manager = tidnotif_poa->the_POAManager();
      poa_manager->activate();
    } catch(...){
      if (_orb->trace != NULL)
        _orb->print_trace(TIDorb::util::TR_ERROR, 
                          "NotificationService::restore_service: Unknowed exception");
      return NULL;
    }
    
    // Create EventChannelFactory servant 
    factory_servant = new TIDNotif::EventChannelFactoryImpl(_orb, 
                                                            tidnotif_poa);
    PortableServer::ObjectId_var id;
    string string_id = 
      TIDNotif::PersistenceManager::getDB()->recover_channel_factory();
    
    id = PortableServer::string_to_ObjectId(string_id.c_str());
    tidnotif_poa->activate_object_with_id(id, factory_servant);

    TIDNotif::PersistenceManager::getDB()->load_c_f(factory_servant);
    
    if (_orb->trace != NULL)
      _orb->print_trace(TIDorb::util::TR_USER, 
                        "NotificationService::restore_service: EventChannelFactory recovered");
    
    CORBA::Object_ptr object = tidnotif_poa->id_to_reference(id);
    factory_ref = CosNotifyChannelAdmin::EventChannelFactory::_narrow(object);

    //
    // Register initial reference to NotificationService in ORB services table
    //
    TIDorb::core::ORBServices& services = 
      const_cast<TIDorb::core::ORBServices&>(_orb->services());
    services.set_service("NotificationService", object); // consumes object
    

    CORBA::String_var str = _orb->object_to_string(factory_ref);
    return CORBA::string_dup(str.in());


  } else { // TIDNotif::PersistenceManager::isActive()

    TIDorb::util::StringBuffer msg;
    msg << "NotificationService::restore_service:";
    msg << "the last service was started without persistence";
    if (_orb->trace != NULL){
      _orb->print_trace(TIDorb::util::TR_USER, msg.str().data());
    }
    throw ServiceManager::PersistenceException(msg.str().data());

  } // else

}
  

const char* TIDNotif::NotificationService::create_service(){
    

  if (_orb->trace != NULL){
    _orb->print_trace(TIDorb::util::TR_USER, 
                      "Creating Notification Service ...");
  }

  char string_id[100];
  CORBA::String_var str;

  try {
    tidnotif_poa = TIDNotif::ThePOAFactory::newPOA(
                                         "TIDNotifPOA",
                                         root_poa,
                                         true,
                                         TIDNotif::ThePOAFactory::_ADMIN_POA);
    // Start Persistence Manager
    poa_manager = tidnotif_poa->the_POAManager();
    poa_manager->activate();
    
    // Create EventChannelFactory servant 
    factory_servant = new TIDNotif::EventChannelFactoryImpl(_orb,
                                                            tidnotif_poa);
    
    PortableServer::ObjectId_var id;
    
    sprintf(string_id, "TIDNotif_%lu", TIDThr::Thread::getCurrentThreadId());
    id = PortableServer::string_to_ObjectId(string_id);
    tidnotif_poa->activate_object_with_id(id, factory_servant);
    
    
    CORBA::Object_ptr object = tidnotif_poa->id_to_reference(id);
    
    factory_ref = CosNotifyChannelAdmin::EventChannelFactory::_narrow(object);
    
    //
    // Register initial reference to NotificationService in ORB services table
    //
    TIDorb::core::ORBServices& services = 
      const_cast<TIDorb::core::ORBServices&>(_orb->services());
    services.set_service("NotificationService", object);
    
    str = _orb->object_to_string(factory_ref);

    //
    // Get system assigned ports if none ports where provided at initialization
    //
    if (!port_given) {
      TIDorb::portable::Stub* stub_obj = 
        dynamic_cast<TIDorb::portable::Stub*> ((CORBA::Object*)factory_ref);
      TIDorb::core::ObjectDelegateImpl* obj_delegate = 
        dynamic_cast<TIDorb::core::ObjectDelegateImpl*> (stub_obj->_get_delegate());
      TIDorb::core::iop::IOR* ior = obj_delegate->getReference();
      TIDorb::util::StringBuffer port_str;
      port_str << ior->profile_IIOP()->getListenPoint()._port;
      port = port_str.str();
      util::TIDNotifConfig::set(util::TIDNotifConfig::ADMIN_PORT_KEY, port.c_str());
      persID = port;
      util::TIDNotifConfig::store();
    }
    
    if ( (!ssl_port_given) && (ssl_config) ){
      TIDorb::portable::Stub* stub_obj = 
        dynamic_cast<TIDorb::portable::Stub*> ((CORBA::Object*)factory_ref);
      TIDorb::core::ObjectDelegateImpl* obj_delegate = 
        dynamic_cast<TIDorb::core::ObjectDelegateImpl*> (stub_obj->_get_delegate());
      TIDorb::core::iop::IOR* ior = obj_delegate->getReference();
      SSLIOP::SSL* _ssl = ior->get_SSL();
      TIDorb::util::StringBuffer ssl_port_str;
      ssl_port_str << _ssl->port;
      ssl_port = ssl_port_str.str();
      util::TIDNotifConfig::set(util::TIDNotifConfig::ADMIN_SSL_PORT_KEY, ssl_port.c_str());
    }
  } catch (const CORBA::Exception& ex) {
    if (_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "Error: CORBA Exception: " << ex;
      _orb->print_trace(TIDorb::util::TR_ERROR,  msg.str().data());

    }
  } catch (...) {
    if (_orb->trace != NULL) {
      _orb->print_trace(TIDorb::util::TR_ERROR, "Error: Unknown exception ");
    }
  }

  //
  // Print where notif server is listening
  //
  TIDorb::util::StringBuffer msg;
  msg << "Serving at port " << port << "... " << endl;
  if (ssl_config) {
    msg.seekp(0, ios::beg);
    msg << "Serving at SSL port " << ssl_port << "... " << endl;
  }
  if (_orb->trace != NULL)
    _orb->print_trace(TIDorb::util::TR_USER,  msg.str().data());
  cerr << msg.str().data();
  
  //
  // Start and init Persistence
  //

  TIDNotif::PersistenceManager::init(persDB.c_str(), persID.c_str(), _orb);

  if (TIDNotif::PersistenceManager::isActive()){
    TIDNotif::PersistenceManager::getDB()->save_channel_factory(string_id);
    if (_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "NotificationService:create_service ";
      msg << "new EventChannelFactory created with persistence";
      _orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
  }
  else {
    if (_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "NotificationService:create_service ";
      msg << "new EventChannelFactory created without persistence";
      _orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
  }



  return CORBA::string_dup(str.in());
}
		

void TIDNotif::NotificationService::destroy_service(){

  if (_orb->trace != NULL){
    _orb->print_trace(TIDorb::util::TR_USER, 
                      "Destroying Notification Service ...");
  }
  
  CosNotifyChannelAdmin::ChannelIDSeq* channels =
    factory_ref->get_all_channels();
  
  
  for (CORBA::ULong i = 0;  i < channels->length(); i++){
    CosNotifyChannelAdmin::EventChannel_var channel = 
      factory_ref->get_event_channel((*channels)[i]);
    
    channel->destroy();
  }
  
  delete channels;


  // tidnotif_poa->destroy(true,false);
  // poa_manager->deactivate(true,false);
  
  if (_orb->trace != NULL)
    _orb->print_trace(TIDorb::util::TR_USER, 
                      "Notification Service has been halted");

  _orb->shutdown(false);
  //_orb->destroy(); // Exception: BAD_INV_ORDER
  
  delete notification_service;
  notification_service = NULL;

}


void TIDNotif::NotificationService::shutdown_service(){

  tidnotif_poa->destroy(true,false);
  poa_manager->deactivate(true,false);
  
  if (_orb->trace != NULL)
    _orb->print_trace(TIDorb::util::TR_USER, 
                      "Notification Service has been shutdowned");
}


void TIDNotif::NotificationService::run(){

  if (_orb->trace != NULL){
    _orb->print_trace(TIDorb::util::TR_USER, 
                      "NotificationService::run");
  }

  _orb->run();
}

		
TIDNotif::NotificationService& 
TIDNotif::NotificationService::init(int argc, char** argv)
{
  if (notification_service != NULL) {
//     if (_orb->trace != NULL){
//       TIDorb::util::StringBuffer msg;
//       msg << "NotiificationService::init AlreadyInitialized";
//       _orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
//     }
    throw AlreadyInitialized("Notification Service has been initialized");
  }
  
  notification_service = new NotificationService(argc, argv);
  return *notification_service;
  
}

		
TIDNotif::NotificationService& 
TIDNotif::NotificationService::get_notification()
{
  if (notification_service == NULL){
    if (_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "NotiificationService::get_notification hasn't been initialized";
      _orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
    throw NotInitialized("Notification Service hasn't been initialized");
  }
  else
    return *notification_service;
}
  
		

