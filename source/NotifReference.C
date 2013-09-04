/*
 *  File name: NotifReference.C
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

#include "NotifReference.h"


CosNotifyChannelAdmin::EventChannel_ptr 
TIDNotif::NotifReference::notifChannelReference(PortableServer::POA_ptr the_poa,
                                                const char* name)
{
  PortableServer::ObjectId_var oid = PortableServer::string_to_ObjectId(name);
  CORBA::Object_ptr channel = 
    the_poa->create_reference_with_id(oid.in(),
                             CosNotifyChannelAdmin::_EventChannelHelper::id());
  return CosNotifyChannelAdmin::EventChannel::_narrow(channel);
}

NotificationInternals::InternalDistributionChannel_ptr 
TIDNotif::NotifReference::internalChannelReference(
                                         PortableServer::POA_ptr the_poa,
                                         const char* name,
                                         CORBA::PolicyList* policies)
{
  PortableServer::ObjectId_var oid = PortableServer::string_to_ObjectId(name);
  CORBA::Object_ptr channel = 
    the_poa->create_reference_with_id(oid.in(), 
             NotificationInternals::_InternalDistributionChannelHelper::id());
      
  if(policies != NULL) {
    channel = channel->_set_policy_overrides(*policies,
                                             CORBA::SET_OVERRIDE);
  }
  return 
    NotificationInternals::InternalDistributionChannel::_narrow(channel);
}


///
//
// SupplierAdmin
//

CosNotifyChannelAdmin::SupplierAdmin_ptr 
TIDNotif::NotifReference::supplierAdminReference(PortableServer::POA_ptr the_poa,
                                                 const char* name)
{ 
  PortableServer::ObjectId_var oid = PortableServer::string_to_ObjectId(name);
  CORBA::Object_ptr admin = 
    the_poa->create_reference_with_id(oid.in(), 
                           CosNotifyChannelAdmin::_SupplierAdminHelper::id());
  return CosNotifyChannelAdmin::SupplierAdmin::_narrow(admin);
}


NotificationInternals::InternalSupplierAdmin_ptr 
TIDNotif::NotifReference::internalSupplierAdminReference(PortableServer::POA_ptr the_poa,
                                                         const char * name,
                                                         CORBA::PolicyList* policies)
{
  PortableServer::ObjectId_var oid =  PortableServer::string_to_ObjectId(name);
  CORBA::Object_ptr admin = 
    the_poa->create_reference_with_id(
                      oid.in(), 
                      NotificationInternals::_InternalSupplierAdminHelper::id());
      
  if(policies != NULL) {
    admin = admin->_set_policy_overrides(*policies,CORBA::SET_OVERRIDE);
  }
  return NotificationInternals::InternalSupplierAdmin::_narrow(admin);
}


CosNotifyChannelAdmin::ProxyPushConsumer_ptr
TIDNotif::NotifReference::proxyPushConsumerReference(PortableServer::POA_ptr poa,
                                                     const char* name)
{ 
  PortableServer::ObjectId_var oid =  PortableServer::string_to_ObjectId(name);
  CORBA::Object_ptr proxy = 
    poa->create_reference_with_id( 
                        oid.in(),
                        CosNotifyChannelAdmin::_ProxyPushConsumerHelper::id());

  return  CosNotifyChannelAdmin::ProxyPushConsumer::_narrow(proxy);
}


NotificationInternals::InternalProxyPushConsumer_ptr
TIDNotif::NotifReference::iProxyPushConsumerReference(PortableServer::POA_ptr poa, 
                                                      const char* name,
                                                      CORBA::PolicyList* policies)
{
  PortableServer::ObjectId_var oid = PortableServer::string_to_ObjectId(name);
  CORBA::Object_ptr proxy =
        poa->create_reference_with_id( 
                  oid.in(),
                  NotificationInternals::_InternalProxyPushConsumerHelper::id());

  if(policies != NULL) {
    proxy = proxy->_set_policy_overrides(*policies,CORBA::SET_OVERRIDE);
  }
  return NotificationInternals::InternalProxyPushConsumer::_narrow(proxy);
}


CosNotifyChannelAdmin::ConsumerAdmin_ptr 
TIDNotif::NotifReference::consumerAdminReference(PortableServer::POA_ptr the_poa,
                                                 const char* name)
{
  PortableServer::ObjectId_var oid =  PortableServer::string_to_ObjectId(name);
  CORBA::Object_ptr admin = 
    the_poa->create_reference_with_id(
                            oid.in(), 
                            CosNotifyChannelAdmin::_ConsumerAdminHelper::id());
  
  return CosNotifyChannelAdmin::ConsumerAdmin::_narrow(admin);
}


NotificationInternals::InternalConsumerAdmin_ptr 
TIDNotif::NotifReference::internalConsumerAdminReference(PortableServer::POA_ptr the_poa,
                                                         const char * name,
                                                         CORBA::PolicyList* policies)
{
  PortableServer::ObjectId_var oid =  PortableServer::string_to_ObjectId(name);
  CORBA::Object_ptr admin = the_poa->create_reference_with_id(
                     oid.in(), 
                     NotificationInternals::_InternalConsumerAdminHelper::id());
     
  if(policies != NULL) {
    admin = admin->_set_policy_overrides(*policies,CORBA::SET_OVERRIDE);
  }
  
  return NotificationInternals::InternalConsumerAdmin::_narrow(admin);
}


CosNotifyChannelAdmin::ProxyPushSupplier_ptr
TIDNotif::NotifReference::proxyPushSupplierReference(PortableServer::POA_ptr poa,
                                                     const char* name )
{ 
  PortableServer::ObjectId_var oid =  PortableServer::string_to_ObjectId(name);
  CORBA::Object_ptr proxy =  
    poa->create_reference_with_id( 
      	                  oid.in(),
                          CosNotifyChannelAdmin::_ProxyPushSupplierHelper::id());
  
  return CosNotifyChannelAdmin::ProxyPushSupplier::_narrow(proxy);
}
                                  

NotificationInternals::InternalProxyPushSupplier_ptr
TIDNotif::NotifReference::iProxyPushSupplierReference(PortableServer::POA_ptr poa, 
                                                      const char* name,
                                                      CORBA::PolicyList* policies)
{
  return NULL;
}
                                   

CosNotifyFilter::Filter_ptr 
TIDNotif::NotifReference::discriminatorReference(PortableServer::POA_ptr poa, 
                                                 const char * name)
{
                                                 
  PortableServer::ObjectId_var oid = PortableServer::string_to_ObjectId(name);
  CORBA::Object_var discriminator = 
    poa->create_reference_with_id(oid.in(), 
                                  CosNotifyFilter::_FilterHelper::id());
  return CosNotifyFilter::Filter::_narrow(discriminator);
}
                                  

CosNotifyFilter::MappingFilter_ptr 
TIDNotif::NotifReference::mappingDiscriminatorReference(PortableServer::POA_ptr poa, 
                                                        const char * name )
{
  PortableServer::ObjectId_var oid = PortableServer::string_to_ObjectId(name);
  CORBA::Object_ptr mapping_discriminator = 
    poa->create_reference_with_id(oid.in(), 
                                  CosNotifyFilter::_MappingFilterHelper::id());

  return CosNotifyFilter::MappingFilter::_narrow(mapping_discriminator);
}


