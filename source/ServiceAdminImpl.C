/*
 *  File name: ServiceAdminImpl.C
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

#include "ServiceAdminImpl.h"
#include "TIDNotifConfig.h"
#include "ThePOAFactory.h"
#include "PersistenceManager.h"
#include "AlreadyInitialized.h"
#include "TIDNotif.h"

namespace TIDNotif{

ServiceAdminImpl::ServiceAdminImpl(int argc, char** argv)
  : state(ServiceManager::stopped),
    service(NotificationService::init(argc, argv))
{
  activate(service.get_orb());
}
    
ServiceAdminImpl::~ServiceAdminImpl()
{
}


char* ServiceAdminImpl::start_service()
  throw(ServiceManager::AlreadyStarted)
{

  if (state == ServiceManager::stopped){

    try{

      if (TIDNotif::PersistenceManager::isActive()){
        if (PersistenceManager::getDB()->channel_factory_saved())
          ior_ref = service.restore_service();
        else
          ior_ref = service.create_service();
      }
      else
        ior_ref = service.create_service();
    
      state = ServiceManager::started;
      return CORBA::string_dup(ior_ref);
      
    } catch (CORBA::SystemException &ex) {
      cerr << "ERROR ServiceAdminImpl::start_service: CORBA::SystemException:";
      cerr <<  ex._name() << endl;    
      return NULL;
    } catch (CORBA::Exception &ex) {
      cerr << "ERROR ServiceAdminImpl::start_service: CORBA::Exception:";
      cerr << ex._name() << endl;
      return NULL;
    } catch (TIDNotif::AlreadyInitialized &){
      cerr << "ERROR ServiceAdminImpl::start_service: AlreadyInitialized" << endl;
      return NULL;
    } catch (...) {
      cerr << "ERROR ServiceAdminImpl::start_service: Unknowed exception" << endl;
      return NULL;
    }


  } else { // (state == ServiceManager::started)


     try{

       if (service.get_state() == ServiceManager::stopped){
         cerr << "ERROR ServiceAdminImpl::start_service2" << endl;
         ior_ref = service.restore_service();
         state = ServiceManager::started;
         return CORBA::string_dup(ior_ref);   
       } 
       else{
         cerr << "ERROR ServiceAdminImpl::start_service2: Service already started" << endl;
         throw ServiceManager::AlreadyStarted("Service already started");
       }

     } catch(ServiceManager::AlreadyStarted& ex) {
       throw;
     } catch (CORBA::SystemException &ex) {
       cerr << "ERROR ServiceAdminImpl::start_service2: CORBA::SystemException:";
       cerr <<  ex._name() << endl;    
       return NULL;
     } catch (CORBA::Exception &ex) {
       cerr << "ERROR ServiceAdminImpl::start_service2: CORBA::Exception:";
       cerr << ex._name() << endl;
       return NULL;
     }

  } // if else

}

		
void ServiceAdminImpl::shutdown_service()
  throw(ServiceManager::NotStarted)
{

  if (state == ServiceManager::stopped) {
    throw ServiceManager::NotStarted("The service hasn't been started");
  }
  else {

    try{
      service.shutdown_service();
      state = ServiceManager::stopped;
    } catch (CORBA::SystemException &ex) {
      cerr << "ERROR ServiceAdminImpl::shutdown_service: CORBA::SystemException ";
      cerr <<  ex._name() << endl;    
    } catch (CORBA::Exception &ex) {
      cerr << "ERROR ServiceAdminImpl::shutdown_service: CORBA::Exception ";
      cerr << ex._name() << endl;
    } catch (...) {
      cerr << "ERROR ServiceAdminImpl::shutdown_service: Unknowed exception" << endl;
    }
    
  } // else
  
}


char* ServiceAdminImpl::get_factory_ref()
  throw(ServiceManager::NotStarted)
{
  if (state == ServiceManager::stopped)
    throw ServiceManager::NotStarted("The service hasn't been started");
  else
    return CORBA::string_dup(ior_ref);
}

void ServiceAdminImpl::halt_service()
  throw(ServiceManager::NotStarted)
{
  try{

    if (state == ServiceManager::stopped) 
      throw ServiceManager::NotStarted("The service hasn't been started");
    else
      service.destroy_service();

    } catch (CORBA::SystemException &ex) {
      cerr << "ERROR ServiceAdminImpl::halt_service: CORBA::SystemException ";
      cerr << ex._name() << endl;    
    } catch (CORBA::Exception &ex) {
      cerr << "ERROR ServiceAdminImpl::halt_service: CORBA::Exception ";
      cerr << ex._name() << endl;
    } catch (...) {
      cerr << "ERROR ServiceAdminImpl::halt_service: Unknowed exception" << endl;
    }
}


void ServiceAdminImpl::run()
{
  try{
    service.run();
  } catch (CORBA::SystemException &ex) {
    cerr << "ERROR ServiceAdminImpl::run: CORBA::SystemException:";
    cerr <<  ex._name() << endl;    
  } catch (CORBA::Exception &ex) {
    cerr << "ERROR ServiceAdminImpl::run: CORBA::Exception:" << ex._name() << endl;
  } catch (...) {
    cerr << "ERROR ServiceAdminImpl::run: Unknowed exception" << endl;
  }

}
		
		
void ServiceAdminImpl::activate(CORBA::ORB_ptr orb)
{

  try{

    PortableServer::POA_var root_poa = TIDNotif::ThePOAFactory::rootPOA(orb);
    PortableServer::POAManager_var poa_manager = root_poa->the_POAManager();
  
    PortableServer::POA_var serviceAdmin_poa = 
      TIDNotif::ThePOAFactory::newPOA("ServiceAdmin",
                                      root_poa,
                                      poa_manager,
                                      TIDNotif::ThePOAFactory::_ADMIN_POA);
    PortableServer::ObjectId_var id;

    //
    // Registra el servant en RootPOA y crea una referencia al objeto CORBA
    //
    const char* string_id="ServiceManager";
    id = PortableServer::string_to_ObjectId(string_id);

    serviceAdmin_poa->activate_object_with_id(id, this);
    poa_manager->activate();
  
    CORBA::Object_var object = serviceAdmin_poa->id_to_reference(id);
    
    ServiceManager::ServiceAdmin_var serviceAdmin_ref =
      ServiceManager::ServiceAdmin::_narrow(object);
  


    // Vuelca en salida estandar la referencia como cadena de caracteres
    CORBA::String_var str = orb->object_to_string(serviceAdmin_ref);
    cout << str << endl << flush;
    
    cerr << "Service Manager is ready " << endl;
    
  } catch (CORBA::SystemException &ex) {
    cerr << "ERROR ServiceAdminImpl::activate: CORBA::SystemException:";
    cerr <<  ex._name() << endl;    
  } catch (CORBA::Exception &ex) {
    cerr << "ERROR ServiceAdminImpl::activate: CORBA::Exception:" << ex._name() << endl;
  } catch (...) {
    cerr << "ERROR ServiceAdminImpl::activate: Unknowed exception" << endl;
  }

}
  

}; //namespace TIDNotif

