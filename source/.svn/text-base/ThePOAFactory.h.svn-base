// -*- c++ -*-
/*
 *  File name: ThePOAFactory.h
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

#ifndef _TIDNOTIF_THEPOAFACTORY_H_
#define _TIDNOTIF_THEPOAFACTORY_H_
#include <stdlib.h> 

#include <PortableServer.h>
#include <TIDorb/core/poa/POAManagerImpl.h>
#include "TIDThr.h"


namespace TIDNotif { 

class ThePOAFactory {
    
public:
  
  static const char* CREATE_GLOBAL_POA[2];
  static const char* CREATE_LOCAL_POA[2];
  static const char* CREATE_EXCLUSIVE_POA[2];
  static const char* CONFIG_GLOBAL_POA[6];
  static const char* CONFIG_LOCAL_POA[6];
  static const char* CONFIG_EXCLUSIVE_POA[6];

  static const char* ACTIVATE_GLOBAL_POA; 
  static const char* ACTIVATE_LOCAL_POA; 
  static const char* ACTIVATE_EXCLUSIVE_POA; 
   
  static const char* DESTROY[2]; 
  static const char* ERROR_POA[2];
  static const char* EXCEPTION_POA;
  static const char* POA_EXIST;

  static const char* NEW_POA[2]; 
  static const char* POA_INFO_1[3]; 
  static const char* POA_INFO_2[2]; 
  static const char* POA_INFO_3[2]; 
  static const char* POA_INFO_4[6];



  //
  // LEVELS
  //
  //static const int GLOBAL    = 0;
  //static const int LOCAL     = 1;
  //static const int EXCLUSIVE = 2;
    


  //
  // POA TYPES
  //
   
  enum POA_TypeI {CHANNEL_POA			=0,
                  SUPPLIER_ADMIN_POA		=1,
                  CONSUMER_ADMIN_POA		=2,
                  PROXY_PUSH_SUPPLIER_POA	=3,
                  PROXY_PULL_SUPPLIER_POA	=4,
                  PROXY_PUSH_CONSUMER_POA	=5,
                  PROXY_PULL_CONSUMER_POA	=6,
                  SUPPLIER_DISCRIMINATOR_POA	=7,
                  CONSUMER_DISCRIMINATOR_POA	=8,
                  CONSUMER_INDEXLOCATOR_POA	=9,
                  MAPPING_DISCRIMINATOR_POA	=10,
                  TRANSFORMING_OPERATOR_POA	=11,
                  GLOBAL_FILTER_POA		=12,
                  GLOBAL_MAPPING_FILTER_POA	=13};
  

  enum POA_Type {_SERVER_POA	=0,
                 _AGENT_POA	=1,
                 _ADMIN_POA	=2,
                 _PROXY_POA	=3,
                 _CLIENT_POA	=4,
                 _COMMON_POA	=5};

  static const bool CREATE_MANAGER;
  static const bool NO_CREATE_MANAGER;

  //static TIDThr::RecursiveMutex _recursive_mutex; 
  

private:

  static CORBA::ORB_ptr _orb;
  static PortableServer::POA_ptr _root_poa;
  static PortableServer::POA_ptr _agentPOA;
   
  typedef map<string,PortableServer::POA_ptr> HastablePOA;
  static HastablePOA _globalPOATable;
  static HastablePOA _localPOATable;
  static HastablePOA _exclusivePOATable;
    
public:

  static PortableServer::POA_ptr 
  rootPOA(CORBA::ORB_ptr orb);  
  
  static PortableServer::POA_ptr 
  newPOA(string poaName, 
         PortableServer::POA_var poaFather,
         bool newManager, 
         ThePOAFactory::POA_Type poaType);   
    
  static PortableServer::POA_ptr 
  newPOA(string poaName,
         PortableServer::POA_var poaFather,
         PortableServer::POAManager* poaManager,
         ThePOAFactory::POA_Type poaType); 
  
  static void destroy(PortableServer::POA_ptr poa, 
                      ThePOAFactory::POA_Type poaType); 

  static PortableServer::POA_ptr 
  getGlobalPOA(string name );
  
  static PortableServer::POA_ptr 
  createGlobalPOA(string name, int type, 
                  PortableServer::POAManager_ptr manager); 
    
  static PortableServer::POA_ptr 
  getLocalPOA(string name );
    
  static PortableServer::POA_ptr 
  createLocalPOA(string name, int type, 
                 PortableServer::POAManager_ptr manager); 

  static PortableServer::POA_ptr 
  getExclusivePOA(string name );
    
  static PortableServer::POA_ptr
  createExclusivePOA(string name, int type, 
                     PortableServer::POAManager_ptr manager); 

  static void destroyGlobalPOA(); 
    
  static void destroyLocalPOA(string name, bool destroy_pm);
    
  static void destroyExclusivePOA(string name);
    
  static void debugPoaInfo(string id, 
                           PortableServer::POA_ptr the_poa,
                           PortableServer::POA_ptr the_father_poa);
 
private:

  static PortableServer::POA_ptr 
  create_POA(string poaName,
             PortableServer::POA_ptr poaFather,
             PortableServer::POAManager_ptr poaManager);

  static void checkPOA(string poa_name,
                       PortableServer::POA_ptr poa_father);
    
  static void setMaxThreads(int value, 
                            TIDorb::core::poa::POAManagerImpl* poa_mgr);

  static void setMinThreads(int value, 
                            TIDorb::core::poa::POAManagerImpl* poa_mgr);
    
  static void setMaxQueuedRequests(int value, 
                                   TIDorb::core::poa::POAManagerImpl* poa_mgr);
  

public:
    
  static void debugPOAs();
    
  static string getIdName(string id);
  
};

}; //namespace TIDNotif
#endif

