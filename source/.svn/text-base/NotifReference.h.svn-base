// -*- c++ -*-
/*
 *  File name: NotifReference.h
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

#ifndef _TIDNOTIF_NOTIFREFERENCE_H_
#define _TIDNOTIF_NOTIFREFERENCE_H_ 


#include "CosNotifyChannelAdmin.h"
#include "NotificationInternals.h"

#include <PortableServer.h>

namespace TIDNotif {
	
class NotifReference 
{

public:
  static CosNotifyChannelAdmin::EventChannel_ptr 
  notifChannelReference(PortableServer::POA_ptr the_poa,
                        const char * name);
  
  static NotificationInternals::InternalDistributionChannel_ptr 
  internalChannelReference(PortableServer::POA_ptr the_poa,
                           const char* name,
                           CORBA::PolicyList* policies);
  
  static CosNotifyChannelAdmin::SupplierAdmin_ptr 
  supplierAdminReference(PortableServer::POA_ptr the_poa,
                         const char * name); 
  
  static NotificationInternals::InternalSupplierAdmin_ptr 
  internalSupplierAdminReference(PortableServer::POA_ptr the_poa,
                                 const char * name,
                                 CORBA::PolicyList* policies);

  static CosNotifyChannelAdmin::ProxyPushConsumer_ptr      
  proxyPushConsumerReference(PortableServer::POA_ptr poa, 
                             const char * name); 

  /* TODO: static NotificationChannelAdmin::ProxyPushConsumer_ptr
     ProxyPushConsumerReference(PortableServer::POA_ptr poa,
                                   char* name ); */
  
  /* TODO: static org.omg.DistributionChannelAdmin.ProxyPushConsumer
     ProxyPushConsumerReference(org.omg.PortableServer.POA poa, String name); */

  static NotificationInternals::InternalProxyPushConsumer_ptr
  iProxyPushConsumerReference(PortableServer::POA_ptr poa, 
                              const char* name,
                              CORBA::PolicyList* policies);

  /* TODO: In this stage we do not have to implement  the model pull
     static CosEventChannelAdmin::ProxyPullConsumer
     proxyPullConsumerReference( PortableServer::POA poa, char* name );
     
     static NotificationChannelAdmin::ProxyPullConsumer
     nProxyPullConsumerReference(PortableServer::POA poa, char* name );
     
     static NotificationInternals::InternalProxyPullConsumer
     ProxyPullConsumerReference(PortableServer::POA poa, 
     char* name,  Policy[] policies); */
  
  
  static CosNotifyChannelAdmin::ConsumerAdmin_ptr 
  consumerAdminReference(PortableServer::POA_ptr the_poa,
                         const char* name);

  /*TODO: static  org.omg.DistributionChannelAdmin.ConsumerAdmin 
    ConsumerAdminReference( org.omg.PortableServer.POA the_poa,
    String name ); */

  static NotificationInternals::InternalConsumerAdmin_ptr 
  internalConsumerAdminReference(PortableServer::POA_ptr the_poa,
                                 const char * name,
                                 CORBA::PolicyList* policies); 

  static CosNotifyChannelAdmin::ProxyPushSupplier_ptr
  proxyPushSupplierReference(PortableServer::POA_ptr poa, const char* name);
                                  
  /* TODO: static NotificationChannelAdmin::ProxyPushSupplier_ptr
     ProxyPushSupplierReference(PortableServer::POA_ptr poa, char* name); */
                                  
  /* TODO: static org.omg.DistributionChannelAdmin.ProxyPushSupplier
     ProxyPushSupplierReference(org.omg.PortableServer.POA poa, String name); */

  static NotificationInternals::InternalProxyPushSupplier_ptr
  iProxyPushSupplierReference(PortableServer::POA_ptr poa, 
                              const char* name,
                              CORBA::PolicyList* policies);

  /* TODO: In this stage we do not have to implement  the model pull
  static CosEventChannelAdmin::ProxyPullSupplier
      proxyPullSupplierReference( PortableServer::POA poa, char* name );

  static NotificationChannelAdmin::ProxyPullSupplier
       nProxyPullSupplierReference(PortableServer::POA poa, char* name);

  static NotificationInternals::InternalProxyPullSupplier
       iProxyPullSupplierReference(PortableServer::POA poa, 
                                   char* name,
                                   Policy[] policies); */


  static CosNotifyFilter::Filter_ptr 
  discriminatorReference(PortableServer::POA_ptr poa, const char* name);


  static CosNotifyFilter::MappingFilter_ptr 
  mappingDiscriminatorReference(PortableServer::POA_ptr poa, const char* name);


                              
};                              

}; // namespace TIDNotif
#endif
