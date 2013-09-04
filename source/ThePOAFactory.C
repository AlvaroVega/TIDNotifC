/*
 *  File name: ThePOAFactory.C
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

#include "ThePOAFactory.h"
#include "TIDNotifConfig.h"

namespace TIDNotif { 


  const char* ThePOAFactory::CREATE_GLOBAL_POA[] =
    { "-> ThePOAFactory.globalPOA(): ", NULL };
  
  const char* ThePOAFactory::CREATE_LOCAL_POA[] =
    { "-> ThePOAFactory.localPOA(): ", NULL };
  
  const char* ThePOAFactory::CREATE_EXCLUSIVE_POA[] =
    { "-> ThePOAFactory.exclusivePOA(): ", NULL };
  
  const char* ThePOAFactory::CONFIG_GLOBAL_POA[] =
    { "  config: ", NULL, ", ", NULL, ", ", NULL };
  
  const char* ThePOAFactory::CONFIG_LOCAL_POA[] =
    { "  config: ", NULL, ", ", NULL, ", ", NULL };

  const char* ThePOAFactory::CONFIG_EXCLUSIVE_POA[] =
   { "  config: ", NULL, ", ", NULL, ", ", NULL };
  
  const char* ThePOAFactory::ACTIVATE_GLOBAL_POA = 
   "  ¡activate!";

  const char* ThePOAFactory::ACTIVATE_LOCAL_POA = 
   "  ¡activate!";

  const char* ThePOAFactory::ACTIVATE_EXCLUSIVE_POA = 
   "  ¡activate!";

  const char* ThePOAFactory::DESTROY[] = 
   { "-> POAFactory.destroy: ", NULL };

  const char* ThePOAFactory::ERROR_POA[] =
   { " ERROR POAFactory: Invalid poaType = ", NULL };

  const char* ThePOAFactory::EXCEPTION_POA =
   " POAFactory: create child POA Exception.";

  const char* ThePOAFactory::POA_EXIST =
   " POAFactory: ERROR, child POA already exist.";


  // NUEVO
  const char* ThePOAFactory::NEW_POA[] = 
   { "* NEW POA: ", NULL };

  const char* ThePOAFactory::POA_INFO_1[] = 
   { "  [", NULL, "]" };

  const char* ThePOAFactory::POA_INFO_2[] = 
   { "  POA Manager = ", NULL };

  const char* ThePOAFactory::POA_INFO_3[] = 
   { "  Parent POA = ", NULL };

  const char* ThePOAFactory::POA_INFO_4[] =
   { "  Num. Threads = [", NULL, ",", NULL, "] -  Max. Queue Size = ", NULL };



const bool ThePOAFactory::CREATE_MANAGER  = true;
const bool ThePOAFactory::NO_CREATE_MANAGER  = false;
  
  
  
CORBA::ORB_ptr ThePOAFactory::_orb = NULL;
PortableServer::POA_ptr ThePOAFactory::_root_poa = NULL;
PortableServer::POA_ptr ThePOAFactory::_agentPOA = NULL;
  
ThePOAFactory::HastablePOA ThePOAFactory::_globalPOATable;
ThePOAFactory::HastablePOA ThePOAFactory::_localPOATable;
ThePOAFactory::HastablePOA ThePOAFactory::_exclusivePOATable;
  
//
// PUBLIC METHODS
//
PortableServer::POA_ptr 
ThePOAFactory::rootPOA(CORBA::ORB_ptr orb)
{  
  //  TIDThr::Synchronized synchro(_recursive_mutex);

  if ( _root_poa == NULL) {
    _orb = orb;
    try {
      CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
      _root_poa = PortableServer::POA::_narrow(obj);
    }
    catch ( CORBA::ORB::InvalidName ex ) {
      //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
      throw CORBA::INTERNAL();
    }
  }
  return _root_poa;
}
  

PortableServer::POA_ptr 
ThePOAFactory::newPOA(string poaName, 
                      PortableServer::POA_var poaFather,
                      bool newManager, 
                      ThePOAFactory::POA_Type poaType)
{
  if (newManager) {
    return newPOA(poaName, poaFather, (PortableServer::POAManager*) NULL, 
                  poaType);
  }
  else {
    return newPOA(poaName, poaFather, poaFather->the_POAManager(), 
                  poaType);
  }
}
  


PortableServer::POA_ptr 
ThePOAFactory::newPOA(string poaName,
                      PortableServer::POA_var poaFather,
                      PortableServer::POAManager* poaManager,
                      ThePOAFactory::POA_Type poaType)
{ 
  // TIDThr::Synchronized synchro(_recursive_mutex);
  
  checkPOA( poaName, poaFather);
  
  // define policies for child POA
  CORBA::PolicyList_var policies = NULL;
  
  switch (poaType) {
  case ThePOAFactory::_SERVER_POA: // 0
  case ThePOAFactory::_AGENT_POA:  // 1
  case ThePOAFactory::_ADMIN_POA:  // 2
    
    policies = new CORBA::PolicyList(2);
    policies->length(2);
    // Valores cambiados
    (*policies)[0] = poaFather->create_lifespan_policy
      ( PortableServer::PERSISTENT );
    (*policies)[1] = poaFather->create_id_assignment_policy
      ( PortableServer::USER_ID );
    
    // Valores estandar
    //    policies[2] = poaFather.create_thread_policy
    //       ( org.omg.PortableServer.ThreadPolicyValue.ORB_CTRL_MODEL );
    //    policies[3] = poaFather.create_id_uniqueness_policy
    //       ( org.omg.PortableServer.IdUniquenessPolicyValue.UNIQUE_ID );
    //    policies[4] = poaFather.create_servant_retention_policy
    //       ( org.omg.PortableServer.ServantRetentionPolicyValue.RETAIN );
    //    policies[5] = poaFather.create_request_processing_policy
    //       ( org.omg.PortableServer.RequestProcessingPolicyValue.USE_ACTIVE_OBJECT_MAP_ONLY );
    //    policies[6] = poaFather.create_implicit_activation_policy
    //             (org.omg.PortableServer.ImplicitActivationPolicyValue.IMPLICIT_ACTIVATION);
    break;
    
  case ThePOAFactory::_PROXY_POA:  // 3
    
    policies = new CORBA::PolicyList(5);
    policies->length(5);
    // Valores cambiados
    (*policies)[0] = poaFather->create_lifespan_policy
      ( PortableServer::PERSISTENT );
    (*policies)[1] = poaFather->create_id_assignment_policy
      ( PortableServer::USER_ID );
    (*policies)[2] = poaFather->create_id_uniqueness_policy
      ( PortableServer::MULTIPLE_ID );
    (*policies)[3] = poaFather->create_servant_retention_policy
      ( PortableServer::NON_RETAIN );
    (*policies)[4] = poaFather->create_request_processing_policy
      ( PortableServer::USE_DEFAULT_SERVANT );
    
    // Valores estandar
    //   policies[5] = poaFather.create_thread_policy
    //      ( org.omg.PortableServer.ThreadPolicyValue.ORB_CTRL_MODEL );
    //   policies[6] = poaFather.create_implicit_activation_policy
    //      ( org.omg.PortableServer.ImplicitActivationPolicyValue.IMPLICIT_ACTIVATION);
    break;
    
  case ThePOAFactory::_CLIENT_POA: // 4
    policies = new CORBA::PolicyList(1);
    policies->length(1);
    // Valores cambiados
    (*policies)[0] = poaFather->create_id_assignment_policy
      ( PortableServer::USER_ID );
      
    // Valores estandar
    //        policies[1] = poaFather.create_lifespan_policy
    //          ( org.omg.PortableServer.LifespanPolicyValue.TRANSIENT );
    //        policies[2] = poaFather.create_thread_policy
    //          ( org.omg.PortableServer.ThreadPolicyValue.ORB_CTRL_MODEL );
    //        policies[3] = poaFather.create_id_uniqueness_policy
    //          ( org.omg.PortableServer.IdUniquenessPolicyValue.UNIQUE_ID );
    //        policies[4] = poaFather.create_servant_retention_policy
    //          ( org.omg.PortableServer.ServantRetentionPolicyValue.RETAIN );
    //        policies[5] = poaFather.create_request_processing_policy
    //          ( org.omg.PortableServer.RequestProcessingPolicyValue.USE_ACTIVE_OBJECT_MAP_ONLY );
    //        policies[6] = poaFather.create_implicit_activation_policy
    //          (org.omg.PortableServer.ImplicitActivationPolicyValue.IMPLICIT_ACTIVATION);
    break;
      
  case ThePOAFactory::_COMMON_POA:  // 5
    policies = new CORBA::PolicyList(5);
    policies->length(5);
    // Valores cambiados
    (*policies)[0] = poaFather->create_lifespan_policy
      ( PortableServer::PERSISTENT );
    (*policies)[1] = poaFather->create_id_assignment_policy
      ( PortableServer::USER_ID );
    (*policies)[2] = poaFather->create_id_uniqueness_policy
      ( PortableServer::MULTIPLE_ID );
    (*policies)[3] = poaFather->create_servant_retention_policy
      ( PortableServer::NON_RETAIN );
    (*policies)[4] = poaFather->create_request_processing_policy
      ( PortableServer::USE_DEFAULT_SERVANT );
    break;
      
  default:
    /*ERROR_POA[1] = Integer.toString(poaType);
      TIDNotifTrace.print(TIDNotifTrace.ERROR, ERROR_POA);*/ //TODO_MORFEO:Trace
    return NULL;
  }

  // Create the child POA
  try {
    return  poaFather->create_POA( poaName.c_str(), poaManager, *policies );
  } catch ( CORBA::Exception& ex ) {			
    /*TIDNotifTrace.print(TIDNotifTrace.ERROR, EXCEPTION_POA);
      TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex);*/ //TODO_MORFEO: Trace
  }            
  return NULL;
}
  
  
  
void ThePOAFactory::destroy( PortableServer::POA_ptr poa, 
                             ThePOAFactory::POA_Type poaType )
{ 
  // TIDThr::Synchronized synchro(_recursive_mutex);

  DESTROY[1] = poa->the_name();
  //TIDNotifTrace.print(TIDNotifTrace.USER, DESTROY); //TODO_MORFEO: Trace
  
  //TODO_MORFEO: 
  switch (poaType) 
    {
    case _AGENT_POA:  // 1
      poa->destroy(true, false);
      break;
      
    case _PROXY_POA:  // 3
      //poa.set_servant( null );
      poa->destroy(true, false);
      break;
      
    case _CLIENT_POA: // 4
      break;
      
    case _COMMON_POA:  // 5
      //poa.set_servant( null );
      poa->destroy(true, false);
      break;
      
    default:
      /*ERROR_POA[1] = Integer.toString(poaType);
        TIDNotifTrace.print(TIDNotifTrace.ERROR, ERROR_POA);*/ //TODO_MORFEO: Trace
      return;
    }
}
  
PortableServer::POA_ptr 
ThePOAFactory::getGlobalPOA( string name )
{
  return (PortableServer::POA_ptr)  _globalPOATable[name];
}
  

PortableServer::POA_ptr 
ThePOAFactory::createGlobalPOA(string name, int type, 
                               PortableServer::POAManager_ptr manager)
{
  // TIDThr::Synchronized synchro(_recursive_mutex); 
  		
  PortableServer::POA_ptr the_poa = (PortableServer::POA_ptr) _globalPOATable[name];
  if (the_poa == NULL) {
    CREATE_GLOBAL_POA[1] =  name.c_str();
    //TIDNotifTrace.print(TIDNotifTrace.DEBUG, CREATE_GLOBAL_POA); //TODO_MORFEO: Trace
      
    if ( util::TIDNotifConfig::getBool(util::TIDNotifConfig::SPEEDUP_POA_KEY) )     {
      the_poa = create_POA( name, _root_poa, manager);
    }
    else        {
      the_poa = create_POA( name, _agentPOA, manager);
    }

    if (manager == NULL) {
      int max_threads = 0, min_threads = 0, max_requests = 0;
      switch (type) {
      case CHANNEL_POA:
        max_threads = util::TIDNotifConfig::getInt(util::TIDNotifConfig::CHANNEL_MAXTHR_KEY);
        min_threads = util::TIDNotifConfig::getInt(util::TIDNotifConfig::CHANNEL_MINTHR_KEY);
        max_requests= util::TIDNotifConfig::getInt(util::TIDNotifConfig::CHANNEL_QUEUE_KEY);
        break;
      case SUPPLIER_ADMIN_POA:
      case PROXY_PUSH_SUPPLIER_POA:
      case PROXY_PULL_SUPPLIER_POA:
      case SUPPLIER_DISCRIMINATOR_POA:
      case TRANSFORMING_OPERATOR_POA:
        max_threads = util::TIDNotifConfig::getInt(util::TIDNotifConfig::SUPPLIER_MAXTHR_KEY);
        min_threads = util::TIDNotifConfig::getInt(util::TIDNotifConfig::SUPPLIER_MINTHR_KEY);
        max_requests= util::TIDNotifConfig::getInt(util::TIDNotifConfig::SUPPLIER_QUEUE_KEY);
        break;
      case CONSUMER_ADMIN_POA:
      case PROXY_PUSH_CONSUMER_POA:
      case PROXY_PULL_CONSUMER_POA:
      case CONSUMER_DISCRIMINATOR_POA:
      case CONSUMER_INDEXLOCATOR_POA:
      case MAPPING_DISCRIMINATOR_POA:
        max_threads = util::TIDNotifConfig::getInt(util::TIDNotifConfig::CONSUMER_MAXTHR_KEY);
        min_threads = util::TIDNotifConfig::getInt(util::TIDNotifConfig::CONSUMER_MINTHR_KEY);
        max_requests= util::TIDNotifConfig::getInt(util::TIDNotifConfig::CONSUMER_QUEUE_KEY);
        break;
      case GLOBAL_FILTER_POA:
      case GLOBAL_MAPPING_FILTER_POA:
        max_threads = util::TIDNotifConfig::getInt(util::TIDNotifConfig::FILTER_MAXTHR_KEY);
        min_threads = util::TIDNotifConfig::getInt(util::TIDNotifConfig::FILTER_MINTHR_KEY);
        max_requests= util::TIDNotifConfig::getInt(util::TIDNotifConfig::FILTER_QUEUE_KEY);
        break;
      }

      setMaxThreads(max_threads,
                    (TIDorb::core::poa::POAManagerImpl*)(the_poa->the_POAManager()));
      setMinThreads(min_threads,
                    (TIDorb::core::poa::POAManagerImpl*)(the_poa->the_POAManager()));
      setMaxQueuedRequests(max_requests,
                           (TIDorb::core::poa::POAManagerImpl*)(the_poa->the_POAManager()));
          
      TIDorb::util::StringBuffer max_t;
      max_t<< max_threads;
      string max_min = max_t.str().data();
      CONFIG_GLOBAL_POA[1] = max_min.c_str();
      TIDorb::util::StringBuffer min_t;
      min_t<< min_threads;
      max_min = min_t.str().data();
      CONFIG_GLOBAL_POA[3] = max_min.c_str();
      TIDorb::util::StringBuffer max_r;  
      max_r<< max_requests;
      max_min = max_r.str();
      CONFIG_GLOBAL_POA[5] = max_min.c_str();
      //TIDNotifTrace.print(TIDNotifTrace.DEBUG, CONFIG_GLOBAL_POA); //TODO_MORFEO: Trace
    }
      
    // NOTIFICATION
    if ( util::TIDNotifConfig::getBool(util::TIDNotifConfig::SPEEDUP_POA_KEY) )
      debugPoaInfo(name, the_poa, _root_poa);
    else
      debugPoaInfo(name, the_poa, _agentPOA);
      
    if (manager == NULL) {
      // Activate the POA by its manager way
      try {
        the_poa->the_POAManager()->activate();
      } catch ( PortableServer::POAManager::AdapterInactive& ex) {
        //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
      }
      //TIDNotifTrace::print(TIDNotifTrace.DEBUG, ACTIVATE_GLOBAL_POA); //TODO_MORFEO: Trace
    }
    _globalPOATable[name]= the_poa;
  }
  return the_poa;
}
  

PortableServer::POA_ptr ThePOAFactory::getLocalPOA(string name)
{
  return (PortableServer::POA_ptr) _localPOATable[name];
}
  
PortableServer::POA_ptr ThePOAFactory::createLocalPOA(string name, int type, 
                                                      PortableServer::POAManager_ptr manager)
{ 
  // TIDThr::Synchronized synchro(_recursive_mutex); 
  
  
  PortableServer::POA_ptr the_poa = (PortableServer::POA_ptr) _localPOATable[name];

  if (the_poa == NULL) {
      CREATE_LOCAL_POA[1] =  name.c_str();
      //TIDNotifTrace.print(TIDNotifTrace.DEEP_DEBUG, CREATE_LOCAL_POA); //TODO_MORFEO: Trace
      
      if ( util::TIDNotifConfig::getBool(util::TIDNotifConfig::SPEEDUP_POA_KEY) )
        the_poa = create_POA( name, _root_poa, manager);
      else
        the_poa = create_POA( name, _agentPOA, manager);
      
      if (manager == NULL) {
        
          int max_threads = 0, min_threads = 0, max_requests = 0;
          switch (type)
            {
            case CHANNEL_POA:
              max_threads =
                util::TIDNotifConfig::getInt(util::TIDNotifConfig::CHANNEL_MAXTHR_KEY);
              min_threads =
                util::TIDNotifConfig::getInt(util::TIDNotifConfig::CHANNEL_MINTHR_KEY);
              max_requests =
                util::TIDNotifConfig::getInt(util::TIDNotifConfig::CHANNEL_QUEUE_KEY);
              break;
            case SUPPLIER_ADMIN_POA:
            case PROXY_PUSH_SUPPLIER_POA:
            case PROXY_PULL_SUPPLIER_POA:
            case SUPPLIER_DISCRIMINATOR_POA:
            case TRANSFORMING_OPERATOR_POA:
              max_threads =
                util::TIDNotifConfig::getInt(util::TIDNotifConfig::SUPPLIER_MAXTHR_KEY);
              min_threads =
                util::TIDNotifConfig::getInt(util::TIDNotifConfig::SUPPLIER_MINTHR_KEY);
              max_requests =
                util::TIDNotifConfig::getInt(util::TIDNotifConfig::SUPPLIER_QUEUE_KEY);
              break;
            case CONSUMER_ADMIN_POA:
            case PROXY_PUSH_CONSUMER_POA:
            case PROXY_PULL_CONSUMER_POA:
            case CONSUMER_DISCRIMINATOR_POA:
            case CONSUMER_INDEXLOCATOR_POA:
            case MAPPING_DISCRIMINATOR_POA:
              max_threads =
                util::TIDNotifConfig::getInt(util::TIDNotifConfig::CONSUMER_MAXTHR_KEY);
              min_threads =
                util::TIDNotifConfig::getInt(util::TIDNotifConfig::CONSUMER_MINTHR_KEY);
              max_requests =
                util::TIDNotifConfig::getInt(util::TIDNotifConfig::CONSUMER_QUEUE_KEY);
              break;
            }
          setMaxThreads(max_threads, 
                        (TIDorb::core::poa::POAManagerImpl*)(the_poa->the_POAManager()));
          setMinThreads(min_threads, 
                        (TIDorb::core::poa::POAManagerImpl*)(the_poa->the_POAManager()));
          setMaxQueuedRequests(max_requests, 
                               (TIDorb::core::poa::POAManagerImpl*)(the_poa->the_POAManager()));
		
          TIDorb::util::StringBuffer max_t;  
          max_t<< max_threads;
          string max_min = max_t.str().data();
          CONFIG_LOCAL_POA[1] = max_min.c_str();
          TIDorb::util::StringBuffer min_t;
          min_t<< min_threads;
          max_min = min_t.str().data();
          CONFIG_LOCAL_POA[3] = max_min.c_str();
          TIDorb::util::StringBuffer max_r;  
          max_r<< max_requests;
          max_min = max_r.str();
          CONFIG_LOCAL_POA[5] = max_min.c_str();
          //TIDNotifTrace.print(TIDNotifTrace.DEBUG, CONFIG_LOCAL_POA); //TODO_MORFEO: Trace
        }
      
      // NOTIFICATION
      if ( util::TIDNotifConfig::getBool(util::TIDNotifConfig::SPEEDUP_POA_KEY) )
        debugPoaInfo(name, the_poa, _root_poa);
      else
        debugPoaInfo(name, the_poa, _agentPOA);
      
      if (manager == NULL)
        {
          // Activate the POA by its manager way
          try
            {
              the_poa->the_POAManager()->activate();
            }
          catch (PortableServer::POAManager::AdapterInactive ex)
            {
              //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
            }
          //TIDNotifTrace.print(TIDNotifTrace.DEBUG, ACTIVATE_LOCAL_POA); //TODO_MORFEO: Trace
        }
      _localPOATable[name]=the_poa;
    }
  return the_poa;
}
  

PortableServer::POA_ptr ThePOAFactory::getExclusivePOA( string name ){
  return (PortableServer::POA_ptr)_exclusivePOATable[name];
}
  

PortableServer::POA_ptr 
ThePOAFactory::createExclusivePOA( string name, int type, 
                                   PortableServer::POAManager_ptr manager )
{ 
  // TIDThr::Synchronized synchro(_recursive_mutex); 

  PortableServer::POA_ptr the_poa = (PortableServer::POA_ptr) 
    _exclusivePOATable[name];
  if (the_poa == NULL) {
    CREATE_EXCLUSIVE_POA[1] =  name.c_str();
    //TIDNotifTrace.print(TIDNotifTrace.DEEP_DEBUG, CREATE_EXCLUSIVE_POA); //TODO_MORFEO: Trace
      
    if ( util::TIDNotifConfig::getBool(util::TIDNotifConfig::SPEEDUP_POA_KEY) )
      the_poa = create_POA( name, _root_poa, manager);
    else
      the_poa = create_POA( name, _agentPOA, manager);
      
    if (manager == NULL)  {
      int max_threads = 0, min_threads = 0, max_requests = 0;
      switch (type) {
      case CHANNEL_POA:
        max_threads =
          util::TIDNotifConfig::getInt(util::TIDNotifConfig::CHANNEL_MAXTHR_KEY);
        min_threads =
          util::TIDNotifConfig::getInt(util::TIDNotifConfig::CHANNEL_MINTHR_KEY);
        max_requests =
          util::TIDNotifConfig::getInt(util::TIDNotifConfig::CHANNEL_QUEUE_KEY);
        break;
      case SUPPLIER_ADMIN_POA:
      case PROXY_PUSH_SUPPLIER_POA:
      case PROXY_PULL_SUPPLIER_POA:
      case SUPPLIER_DISCRIMINATOR_POA:
      case TRANSFORMING_OPERATOR_POA:
        max_threads =
          util::TIDNotifConfig::getInt(util::TIDNotifConfig::SUPPLIER_MAXTHR_KEY);
        min_threads =
          util::TIDNotifConfig::getInt(util::TIDNotifConfig::SUPPLIER_MINTHR_KEY);
        max_requests =
          util::TIDNotifConfig::getInt(util::TIDNotifConfig::SUPPLIER_QUEUE_KEY);
        break;
      case CONSUMER_ADMIN_POA:
      case PROXY_PUSH_CONSUMER_POA:
      case PROXY_PULL_CONSUMER_POA:
      case CONSUMER_DISCRIMINATOR_POA:
      case CONSUMER_INDEXLOCATOR_POA:
      case MAPPING_DISCRIMINATOR_POA:
        max_threads =
          util::TIDNotifConfig::getInt(util::TIDNotifConfig::CONSUMER_MAXTHR_KEY);
        min_threads =
          util::TIDNotifConfig::getInt(util::TIDNotifConfig::CONSUMER_MINTHR_KEY);
        max_requests =
          util::TIDNotifConfig::getInt(util::TIDNotifConfig::CONSUMER_QUEUE_KEY);
        break;
      }
      setMaxThreads(max_threads, 
                    (TIDorb::core::poa::POAManagerImpl*)(the_poa->the_POAManager()));
      setMinThreads(min_threads, 
                    (TIDorb::core::poa::POAManagerImpl*)(the_poa->the_POAManager()));
      setMaxQueuedRequests(max_requests, 
                           (TIDorb::core::poa::POAManagerImpl*)(the_poa->the_POAManager()));

      TIDorb::util::StringBuffer max_t;  
      max_t<< max_threads;
      string max_min = max_t.str().data();
      CONFIG_EXCLUSIVE_POA[1] = max_min.c_str();
      TIDorb::util::StringBuffer min_t;
      min_t<< min_threads;
      max_min = min_t.str().data();
      CONFIG_EXCLUSIVE_POA[3] = max_min.c_str();
      TIDorb::util::StringBuffer max_r;  
      max_r<< max_requests;
      max_min = max_r.str().data();
      CONFIG_EXCLUSIVE_POA[5] = max_min.c_str();
      //TIDNotifTrace.print(TIDNotifTrace.DEBUG, CONFIG_EXCLUSIVE_POA); //TODO_MORFEO: Trace
    }
      
    // NOTIFICATION
    if ( util::TIDNotifConfig::getBool(util::TIDNotifConfig::SPEEDUP_POA_KEY) )
      debugPoaInfo(name, the_poa, _root_poa);
    else
      debugPoaInfo(name, the_poa, _agentPOA);
      
    if (manager == NULL) {
      // Activate the POA by its manager way
      try {
        the_poa->the_POAManager()->activate();
      }
      catch ( PortableServer::POAManager::AdapterInactive& ex) {
        //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
      }
      //TIDNotifTrace.print(TIDNotifTrace.DEBUG, ACTIVATE_EXCLUSIVE_POA); //TODO_MORFEO: Trace
    }
    _exclusivePOATable[name]=the_poa;
  }
  return the_poa;
}
  
void ThePOAFactory::destroyGlobalPOA()
{ 
  // TIDThr::Synchronized synchro(_recursive_mutex); 
  throw CORBA::NO_IMPLEMENT("No implemented");
}

void ThePOAFactory::destroyLocalPOA(string name, bool destroy_pm)
{
  // TIDThr::Synchronized synchro(_recursive_mutex); 
  	
  HastablePOA::iterator iter;
  iter = _localPOATable.find(name);
  if (iter == _localPOATable.end()) {
      //TIDNotifTrace.print(TIDNotifTrace.DEBUG, "ThePOAFactory.destroyLocalPOA(): POA NOT FOUND"); //TODO_MORFEO: Trace
      return;
    }
    else {
      try {
	PortableServer::POA_ptr poa = (PortableServer::POA_ptr)_localPOATable[name];
        _localPOATable.erase(name);
        if (destroy_pm) {
          if ( poa->the_POAManager()->get_state() != 
               PortableServer::POAManager::INACTIVE ) {
            //poa->the_POAManager()->deactivate(true, false);
            poa->the_POAManager()->deactivate(false, false);
          }
        }
        //poa.destroy(true, false);
        poa->destroy(false, false);
      } catch ( PortableServer::POAManager::AdapterInactive& ex) {
        //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
      }
    }
  }

void ThePOAFactory::destroyExclusivePOA(string name){

  // TIDThr::Synchronized synchro(_recursive_mutex); 
 	
  HastablePOA::iterator iter;
  iter = _exclusivePOATable.find(name);
  if (iter == _exclusivePOATable.end()) {
    //TIDNotifTrace.print(TIDNotifTrace.DEBUG, "ThePOAFactory.destroyExclusivePOA(): POA NOT FOUND"); //TODO_MORFEO: Trace
  } else {
 
    try{
    
      PortableServer::POA_ptr poa = (PortableServer::POA_ptr) _exclusivePOATable[name];
      _exclusivePOATable.erase(name);
      poa->the_POAManager()->deactivate(true, false);
      poa->destroy(true, false);
 
    } catch ( PortableServer::POAManager::AdapterInactive& ex) {
      //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
    }
  }
}

void ThePOAFactory::debugPoaInfo( string id, 
                                  PortableServer::POA_ptr the_poa,
                                  PortableServer::POA_ptr the_father_poa )
{
    
  // NOTIFICATION
  NEW_POA[1] = id.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, NEW_POA); //TODO_MORFEO: Trace
  
  // NOTIFICATION
  POA_INFO_1[1] = the_poa->the_name();
  //TIDNotifTrace.print(TIDNotifTrace.DEBUG, POA_INFO_1); //TODO_MORFEO: Trace
	
  TIDorb::core::poa::POAManagerImpl* poa_mgr = 
    (TIDorb::core::poa::POAManagerImpl*) (the_poa->the_POAManager());
  		
  // NOTIFICATION
  POA_INFO_2[1] = poa_mgr->toString();
  //TIDNotifTrace.print(TIDNotifTrace.DEBUG, POA_INFO_2); //TODO_MORFEO: Trace
	
  // NOTIFICATION
  POA_INFO_3[1] = the_father_poa->the_name();
  //TIDNotifTrace.print(TIDNotifTrace.DEBUG, POA_INFO_3); //TODO_MORFEO: Trace
	
  // NOTIFICATION
  TIDorb::util::StringBuffer max_t;  
  max_t << poa_mgr->get_max_threads();
  string max_min = max_t.str().data();
  POA_INFO_4[1] = max_min.c_str();
  TIDorb::util::StringBuffer min_t;
  min_t << poa_mgr->get_min_threads();
  max_min = min_t.str().data();
  POA_INFO_4[3] = max_min.c_str();
  TIDorb::util::StringBuffer max_r;  
  max_r << poa_mgr->get_max_queued_requests();
  max_min = max_r.str().data();
  POA_INFO_4[5] = max_min.c_str();
    	
  //TIDNotifTrace.print(TIDNotifTrace.DEBUG, POA_INFO_4);  //TODO_MORFEO: Trace
}
 

//
// PRIVATE METHODS
//
PortableServer::POA_ptr 
ThePOAFactory::create_POA(string poaName,
                          PortableServer::POA_ptr poaFather,
                          PortableServer::POAManager_ptr poaManager)
{
  
  checkPOA( poaName, poaFather);

  CORBA::PolicyList_var policies = new CORBA::PolicyList(5);
  policies->length(5);
        

  // Valores cambiados
  (*policies)[0] = poaFather->create_lifespan_policy( PortableServer::PERSISTENT );

  (*policies)[1] = poaFather->create_id_assignment_policy
    ( PortableServer::USER_ID );

  (*policies)[2] = poaFather->create_id_uniqueness_policy
    ( PortableServer::MULTIPLE_ID );

  (*policies)[3] = poaFather->create_servant_retention_policy
    ( PortableServer::NON_RETAIN );

  (*policies)[4] = poaFather->create_request_processing_policy
    (PortableServer::USE_DEFAULT_SERVANT);

        

  // Create the child POA
  try{
    return poaFather->create_POA(poaName.c_str(), poaManager, *policies);
  }
  //catch ( org.omg.PortableServer.POAPackage.AdapterAlreadyExists ex)
  catch (CORBA::Exception& ex) {			
      //TIDNotifTrace.print(TIDNotifTrace.ERROR, EXCEPTION_POA); //TODO_MORFEO: Trace
      //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  }            
  return  NULL;
}


void ThePOAFactory::checkPOA(string poa_name,
                             PortableServer::POA_ptr poa_father)
{

  int counter = 3;

  while (counter > 0) {

    counter--;
    TIDThr::Thread* th = TIDThr::Thread::currentThread();

    // Si existia antes 
    try {
      PortableServer::POA_ptr old_poa = 
        poa_father->find_POA(poa_name.c_str(), false);
      //TIDNotifTrace.print(TIDNotifTrace.ERROR, POA_EXIST); //TODO_MORFEO: Trace
      if ( old_poa->the_POAManager() != NULL) {
        //TIDNotifTrace.print(TIDNotifTrace.ERROR, 
        //"Old POAManager state = "+ old_poa->the_POAManager()->get_state()->value()); //TODO_MORFEO: Trace
        return;
        
      }
      try {
        TIDThr::Thread::sleep(1000);
      }
      catch ( ... ) {
      }
    }
    catch ( PortableServer::POA::AdapterNonExistent& ex ) {
      counter = 0;
    }
  }
}


void ThePOAFactory::setMaxThreads(int value, 
                                  TIDorb::core::poa::POAManagerImpl* poa_mgr )
{
  if (value > -1) {
    try {
      poa_mgr->set_max_threads(value);
    }
    catch (CORBA::Exception& ex) {
      //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
    }
  }
}
  

void ThePOAFactory::setMinThreads(int value, TIDorb::core::poa::POAManagerImpl* poa_mgr )
{
  if (value > -1) {
    try {
      poa_mgr->set_min_threads(value);
    } catch (CORBA::Exception& ex) {
      //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
    }
  }
}

void ThePOAFactory::setMaxQueuedRequests(int value, 
                                         TIDorb::core::poa::POAManagerImpl* poa_mgr )
{
  if (value > -1) {
    try {
      poa_mgr->set_max_queued_requests(value);
    } catch (CORBA::Exception& ex) {
      //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
    }
  }
}
  
  

  
void ThePOAFactory::debugPOAs()
{
  //TODO_MORFEO: Trace
}

string ThePOAFactory::getIdName(string id )
{
  return id.substr(id.find_last_of("##")+2);
}
  
}; //namespace TIDNotif
