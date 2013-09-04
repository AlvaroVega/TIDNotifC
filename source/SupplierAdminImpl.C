/*
 *  File name: SupplierAdminImpl.C
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

#include "SupplierAdminImpl.h"

TIDNotif::SupplierAdminImpl::SupplierAdminImpl(
                              TIDorb::core::TIDORB* orb, 
                              PortableServer::POA_ptr poa):
  m_orb(orb), m_supplier_admin_poa(poa)
{
  // Select configuration for suppliers's POA
  m_supplier_POA_config = 
    TIDNotif::util::TIDNotifConfig::getInt(TIDNotif::util::TIDNotifConfig::SUPPLIER_POA_KEY);

  // Create a SupplierAdminPOA
  PortableServer::POAManager_var poa_manager = 
    m_supplier_admin_poa->the_POAManager();
  
  TIDorb::util::StringBuffer name_poa;
  name_poa << "ProxyPushConsumerPOA";

  try{

    CORBA::PolicyList policy_list;
    policy_list.length(5);
    policy_list[0] = m_supplier_admin_poa->create_id_assignment_policy(PortableServer::USER_ID);
    policy_list[1] = m_supplier_admin_poa->create_lifespan_policy (PortableServer::PERSISTENT);
    policy_list[2] = m_supplier_admin_poa->create_request_processing_policy(
                                                                        PortableServer::USE_DEFAULT_SERVANT);
    policy_list[3] = m_supplier_admin_poa->create_servant_retention_policy(PortableServer::RETAIN);
    policy_list[4] = m_supplier_admin_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
    m_proxy_consumer_poa = 
      m_supplier_admin_poa->create_POA(name_poa.str().data(),
                                       poa_manager, policy_list);

     if (m_orb->trace != NULL){
       TIDorb::util::StringBuffer msg;
       msg << name_poa.str().data() << " created"; 
       m_orb->print_trace(TIDorb::util::TR_DEEP_DEBUG, msg.str().data());
     }

  } catch(const PortableServer::POA::AdapterAlreadyExists& ex){

    TIDorb::util::StringBuffer msg;
    try{
       m_proxy_consumer_poa = 
        m_supplier_admin_poa->find_POA(name_poa.str().data(), false);

      msg << name_poa.str().data() << " already exists!"; 
      if (m_orb->trace != NULL)
        m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data(), ex);
    } catch (PortableServer::POA::AdapterNonExistent&){
      throw CORBA::INTERNAL(msg.str().data());
    }
  } 

  CORBA::Object_var obj_cur = orb->resolve_initial_references("POACurrent");
  m_current = PortableServer::Current::_narrow(obj_cur);

  if (m_supplier_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
    ProxyPushConsumerImpl* proxy_servant = 
      new ProxyPushConsumerImpl(m_orb, m_proxy_consumer_poa);
    
    m_proxy_consumer_poa->set_servant(proxy_servant);
  }

}

TIDNotif::SupplierAdminImpl::~SupplierAdminImpl()
{
  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "Deleting SupplierAdminImpl with id ";
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }

  //m_supplier_admin_poa->destroy(true,true); ???
}


TIDNotif::SupplierAdminData* TIDNotif::SupplierAdminImpl::getData()
{
  try {
    PortableServer::ObjectId_var oid = m_current->get_object_id();
    TIDorb::core::poa::OID oid_key(oid);

    SupplierAdminDataTable::iterator it = m_supplier_admins.find(oid_key);
    if (it != m_supplier_admins.end()){
      return (*it).second;
    }
    else
      throw CORBA::OBJECT_NOT_EXIST();  

  } catch (const CORBA::Exception& ex) {
    
    throw CORBA::INV_OBJREF();
  }
}

  
void TIDNotif::SupplierAdminImpl::register_admin(
                                           TIDNotif::SupplierAdminData* data)
{
  TIDorb::util::StringBuffer id_str;
  id_str << "SupplierAdmin_" << data->_channel_id << "_" << data->_id;

  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(id_str.str().data());

  TIDorb::core::poa::OID oid_key(oid);

  m_supplier_admins[oid_key] = data;
}


void TIDNotif::SupplierAdminImpl::unregister_admin(
                                           TIDNotif::SupplierAdminData* data)
{
  TIDorb::util::StringBuffer id_str;
  id_str << "SupplierAdmin_" << data->_channel_id << "_" << data->_id;

  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(id_str.str().data());

  TIDorb::core::poa::OID oid_key(oid);

  // Destroy POA and POAManager if POA config is LOCAL
  if (m_supplier_POA_config == TIDNotif::util::TIDNotifConfig::LOCAL_POA) {
    TIDorb::util::StringBuffer supplier_admin_poa_name;
    supplier_admin_poa_name << "SupplierAdminPOA" << data->_id;
    try {
      PortableServer::POAManager_var supplier_admin_poa_manager = 
        m_supplier_admin_poa->the_POAManager();
      supplier_admin_poa_manager->deactivate(true, false);
      m_supplier_admin_poa->destroy(true, false);
    } catch (const PortableServer::POA::AdapterNonExistent& ex){
      if (m_orb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "Trying to destroy " << id_str.str().data();
        m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data(), ex);
      }
    } catch (const CORBA::SystemException& ex){
      if (m_orb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "Trying to destroy " << id_str.str().data();
        m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data(), ex);
      }
    }
  }

  SupplierAdminDataTable::iterator it = m_supplier_admins.find(oid_key);
  if (it != m_supplier_admins.end()){
    m_supplier_admins.erase(it);
    delete data;
  }

}


// NotificationInternals::InternalSupplierAdmin

void TIDNotif::SupplierAdminImpl::push_event(const CORBA::Any& data){

  TIDThr::Synchronized synchro(m_recursive_mutex);

  SupplierAdminData* admin_data = getData();

  if (CORBA::is_nil(admin_data->_channel)){
    if (m_orb->trace != NULL)
      m_orb->print_trace(TIDorb::util::TR_DEEP_DEBUG, 
                         "SupplierAdminImpl::push_event _channel is NULL");
  }
  else{

    // Filter event

    try {
      if (!admin_data->filterAdminDelegate->match(data)) {
        if (m_orb->trace != NULL)
          m_orb->print_trace(TIDorb::util::TR_DEBUG, "DISCARD_EVENT");
        return;
      }
    } catch (const CosNotifyFilter::UnsupportedFilterableData& ufd ){
      if (m_orb->trace != NULL)
        m_orb->print_trace(TIDorb::util::TR_ERROR, "UnsupportedFilterableData", 
                           ufd);
      return;
    }

    admin_data->_channel->dispatch_event(data); // oneway request  
		
  }



}

CosNotifyChannelAdmin::AdminID 
TIDNotif::SupplierAdminImpl::getAdminId(){
  SupplierAdminData* admin_data = getData();
  return admin_data->_id;
}

void TIDNotif::SupplierAdminImpl::removeProxyPushConsumer(
                                                  CosNotifyChannelAdmin::ProxyID id)
{
  SupplierAdminData* admin_data = getData();

  if (admin_data->_destroying)
    return;

  
  {
    TIDThr::Synchronized synchro(m_recursive_mutex);

    admin_data->proxyPushConsumers.erase(id);

    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Removed and deactivated ProxyPushConsumerImpl with Id " << id; 
      m_orb->print_trace(TIDorb::util::TR_DEEP_DEBUG, msg.str().data());
    }

    if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_PROXY_PUSH_CONSUMER,
                                               this);
    }
  }
}

void TIDNotif::SupplierAdminImpl::removeProxyPullConsumer(
                                    CosNotifyChannelAdmin::ProxyID id)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

void TIDNotif::SupplierAdminImpl::destroyFromChannel(){

  SupplierAdminData* admin_data = getData();

  if (admin_data->_destroying)
    return;

  admin_data->_destroying = true;
  

  {
    TIDThr::Synchronized synchro(m_recursive_mutex);

    proxyPushConsumerMap::iterator it  = admin_data->proxyPushConsumers.begin();
    proxyPushConsumerMap::iterator end = admin_data-> proxyPushConsumers.end();

    while (it != end){
      InternalProxyPushConsumer_ptr proxy = (*it).second;

      if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "SupplierAdminImpl::destroy proxy with id " << (*it).first; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
      }
      
      proxy->destroyFromAdmin();
      it++;
    }
    
    admin_data->proxyPushConsumers.clear();

    if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->delete_data(this);
    }  //TODO_MORFEO: delete_data or update_data
  }

  this->unregister_admin(admin_data);
}


void TIDNotif::SupplierAdminImpl::loadData(){
}


// CosNotifyChannelAdmin::SupplierAdmin

CosNotifyChannelAdmin::AdminID TIDNotif::SupplierAdminImpl::MyID()
{
  SupplierAdminData* admin_data = getData();
  return admin_data->_id;
}

CosNotifyChannelAdmin::EventChannel_ptr 
TIDNotif::SupplierAdminImpl::MyChannel()
{
  SupplierAdminData* admin_data = getData();
  return CosNotifyChannelAdmin::EventChannel::_duplicate(admin_data->_channel);
}

CosNotifyChannelAdmin::InterFilterGroupOperator 
TIDNotif::SupplierAdminImpl::MyOperator()
{
  SupplierAdminData* admin_data = getData();
  return admin_data->m_operator;
}

CosNotifyFilter::MappingFilter_ptr 
TIDNotif::SupplierAdminImpl::priority_filter()
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

void TIDNotif::SupplierAdminImpl::priority_filter(
                         CosNotifyFilter::MappingFilter_ptr value)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

CosNotifyFilter::MappingFilter_ptr 
TIDNotif::SupplierAdminImpl::lifetime_filter()
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

void TIDNotif::SupplierAdminImpl::lifetime_filter(
                                CosNotifyFilter::MappingFilter_ptr value)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

CosNotifyChannelAdmin::ProxyIDSeq* 
TIDNotif::SupplierAdminImpl::pull_consumers()
{
  //   ProxyIDSeq* seq = new ProxyIDSeq;
  //   seq->length(0);
  
  //   return seq;
  
  throw CORBA::NO_IMPLEMENT("No implemented");
}

CosNotifyChannelAdmin::ProxyIDSeq* 
TIDNotif::SupplierAdminImpl::push_consumers()
{
  SupplierAdminData* admin_data = getData();

  proxyPushConsumerMap::iterator it  = admin_data->proxyPushConsumers.begin();
  proxyPushConsumerMap::iterator end = admin_data->proxyPushConsumers.end();

  ProxyIDSeq* seq = new ProxyIDSeq;
  seq->length(admin_data->proxyPushConsumers.size());

  int i = 0;
  while (it != end){
    (*seq)[i]=(*it).first;
    it++;
    i++;
  }
  return seq;
}
		
CosNotifyChannelAdmin::ProxyConsumer_ptr 
TIDNotif::SupplierAdminImpl::get_proxy_consumer(
                                      CosNotifyChannelAdmin::ProxyID proxy_id)
  throw (CosNotifyChannelAdmin::ProxyNotFound)
{
  SupplierAdminData* admin_data = getData();

  proxyPushConsumerMap::iterator it = 
    admin_data->proxyPushConsumers.find(proxy_id);
  if (it != admin_data->proxyPushConsumers.end()){
    return CosNotifyChannelAdmin::ProxyConsumer::_narrow((*it).second);
  }
  else
    throw CosNotifyChannelAdmin::ProxyNotFound();
}
		
CosNotifyChannelAdmin::ProxyConsumer_ptr 
TIDNotif::SupplierAdminImpl::obtain_notification_pull_consumer(
                                     CosNotifyChannelAdmin::ClientType ctype, 
                                     CosNotifyChannelAdmin::ProxyID& proxy_id)
  throw (CosNotifyChannelAdmin::AdminLimitExceeded)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}
	
CosNotifyChannelAdmin::ProxyConsumer_ptr 
TIDNotif::SupplierAdminImpl::obtain_notification_push_consumer(
                                     CosNotifyChannelAdmin::ClientType ctype, 
                                     CosNotifyChannelAdmin::ProxyID& proxy_id)
  throw (CosNotifyChannelAdmin::AdminLimitExceeded)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  SupplierAdminData* admin_data = getData();

  //ProxyPushConsumerImpl* proxy_impl;
  ProxyPushConsumerData* proxy_data;

  // Assing a unique id to proxy
  proxy_id = admin_data->counterProxyPushConsumer++;

  // Get channel POA in order with configuration
  // TODO: refactor this block int ThePOAFactory
  PortableServer::POA_var proxy_consumer_poa;
  if (m_supplier_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Using Global POA for ProxyPushConsumer " << proxy_id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    proxy_consumer_poa = m_proxy_consumer_poa;
  } else { // Local
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Creating Local POA for ProxyPushConsumer " << proxy_id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    TIDorb::util::StringBuffer proxy_consumer_poa_name;
    proxy_consumer_poa_name << "ProxyPushConsumer" << proxy_id;
    CORBA::PolicyList policy_list;
    policy_list.length(5);
    policy_list[0] = m_proxy_consumer_poa->create_id_assignment_policy(PortableServer::USER_ID);
    policy_list[1] = m_proxy_consumer_poa->create_lifespan_policy (PortableServer::PERSISTENT);
    policy_list[2] = m_proxy_consumer_poa->create_request_processing_policy(
                                                                            PortableServer::USE_DEFAULT_SERVANT);
    policy_list[3] = m_proxy_consumer_poa->create_servant_retention_policy(PortableServer::RETAIN);
    policy_list[4] = m_proxy_consumer_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);

    PortableServer::POAManager_var proxy_consumer_poa_mgr = 
      m_proxy_consumer_poa->the_POAManager();
    
    proxy_consumer_poa = 
      m_proxy_consumer_poa->create_POA(proxy_consumer_poa_name.str().data(), 
                                       proxy_consumer_poa_mgr, policy_list);
          
    TIDNotif::ProxyPushConsumerImpl* proxy_consumer_servant;
    proxy_consumer_servant = new TIDNotif::ProxyPushConsumerImpl(m_orb, 
                                                                 proxy_consumer_poa); 
          
    proxy_consumer_poa->set_servant(proxy_consumer_servant);
          
    //proxy_consumer_poa_mgr->activate();
  }


  // Create a new proxy
  switch (ctype){
  case CosNotifyChannelAdmin::ANY_EVENT:
  case CosNotifyChannelAdmin::STRUCTURED_EVENT:
    {
      
    proxy_data = new ProxyPushConsumerData(m_orb, m_proxy_consumer_poa, 
                                           proxy_id, admin_data->_id, 
                                           admin_data->_channel_id);

    TIDNotif::ProxyPushConsumerImpl* proxy_consumer_impl = 
      dynamic_cast < TIDNotif::ProxyPushConsumerImpl* > (proxy_consumer_poa->get_servant());

    proxy_consumer_impl->register_proxy(proxy_data);
    break;
    }
  default:
    if (m_orb->trace != NULL)
      m_orb->print_trace(TIDorb::util::TR_USER, 
                        "obtain_notification_push_consumer not implement ClientType");
    throw CORBA::NO_IMPLEMENT("No implemented");
  }


  // Activate proxy
  TIDorb::util::StringBuffer str_id;
  str_id << "ProxyConsumer_" << proxy_data->_channel_id << "_";
  str_id << proxy_data->_admin_id << "_" << proxy_id;
  
  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(str_id.str().data());
  
  CORBA::Object_var object = 
    proxy_consumer_poa->create_reference_with_id(oid, 
                                      _InternalProxyPushConsumerHelper::id());
  InternalProxyPushConsumer_ptr proxy_ptr = 
    InternalProxyPushConsumer::_narrow(object);

  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "New ProxyPushConsumer created with id " << proxy_id; 
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }

  // Insert into proxys table
  admin_data->proxyPushConsumers[proxy_id] = proxy_ptr;

  if (PersistenceManager::isActive()) {
    PersistenceManager::getDB()->update_data(
                                    PersistenceDB::ATTR_PROXY_PUSH_CONSUMER,
                                    this);
  }
  return CosNotifyChannelAdmin::ProxyConsumer::_narrow(proxy_ptr);

}

void TIDNotif::SupplierAdminImpl::destroy()
{
  SupplierAdminData* admin_data = getData();

  admin_data->_channel->removeSupplierAdmin(admin_data->_id);
  
  this->destroyFromChannel();
}

// CosEventChannelAdmin::SupplierAdmin

CosEventChannelAdmin::ProxyPushConsumer_ptr 
TIDNotif::SupplierAdminImpl::obtain_push_consumer(){

  TIDThr::Synchronized synchro(m_recursive_mutex);

  SupplierAdminData* admin_data = getData();

  // Assing a unique id to proxy
  CosNotifyChannelAdmin::ProxyID proxy_id = 
    admin_data->counterProxyPushConsumer++;

  // Get channel POA in order with configuration
  // TODO: refactor this block int ThePOAFactory
  PortableServer::POA_var proxy_consumer_poa;
  if (m_supplier_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Using Global POA for ProxyPushConsumer " << proxy_id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    proxy_consumer_poa = m_proxy_consumer_poa;
  } else { // Local
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Creating Local POA for ProxyPushConsumer " << proxy_id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    TIDorb::util::StringBuffer proxy_consumer_poa_name;
    proxy_consumer_poa_name << "ProxyPushConsumer" << proxy_id;
    CORBA::PolicyList policy_list;
    policy_list.length(5);
    policy_list[0] = m_proxy_consumer_poa->create_id_assignment_policy(PortableServer::USER_ID);
    policy_list[1] = m_proxy_consumer_poa->create_lifespan_policy (PortableServer::PERSISTENT);
    policy_list[2] = m_proxy_consumer_poa->create_request_processing_policy(
                                                    PortableServer::USE_DEFAULT_SERVANT);
    policy_list[3] = m_proxy_consumer_poa->create_servant_retention_policy(PortableServer::RETAIN);
    policy_list[4] = m_proxy_consumer_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
    PortableServer::POAManager_var proxy_consumer_poa_mgr = 
      m_proxy_consumer_poa->the_POAManager();

    proxy_consumer_poa = 
      m_proxy_consumer_poa->create_POA(proxy_consumer_poa_name.str().data(), 
                                       proxy_consumer_poa_mgr, policy_list);
          

          
    TIDNotif::ProxyPushConsumerImpl* proxy_consumer_servant;
    proxy_consumer_servant = new TIDNotif::ProxyPushConsumerImpl(m_orb, 
                                                                 proxy_consumer_poa); 
          
    proxy_consumer_poa->set_servant(proxy_consumer_servant);
          
    //proxy_consumer_poa_mgr->activate();
  }

  // Create a new proxy
  ProxyPushConsumerData* proxy_data = 
    new ProxyPushConsumerData(m_orb, m_proxy_consumer_poa, 
                              proxy_id, admin_data->_id, admin_data->_channel_id);

  TIDNotif::ProxyPushConsumerImpl* proxy_consumer_impl = 
    dynamic_cast < TIDNotif::ProxyPushConsumerImpl* > (proxy_consumer_poa->get_servant());
  
  proxy_consumer_impl->register_proxy(proxy_data);


  // Activate proxy
  TIDorb::util::StringBuffer str_id;
  str_id << "ProxyConsumer_" << proxy_data->_channel_id << "_"; 
  str_id << proxy_data->_admin_id << "_" << proxy_id;
  
  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(str_id.str().data());
  
  CORBA::Object_var object = 
    proxy_consumer_poa->create_reference_with_id(oid, 
                                     _InternalProxyPushConsumerHelper::id());
  InternalProxyPushConsumer_ptr proxy_ptr = 
    InternalProxyPushConsumer::_narrow(object);

  // Insert into proxys table
  admin_data->proxyPushConsumers[proxy_id] = 
    InternalProxyPushConsumer::_duplicate(proxy_ptr);

  if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(
                                     PersistenceDB::ATTR_PROXY_PUSH_CONSUMER,
                                     this);
  }
  
  return CosEventChannelAdmin::ProxyPushConsumer::_narrow(proxy_ptr);
}


CosEventChannelAdmin::ProxyPullConsumer* 
TIDNotif::SupplierAdminImpl::obtain_pull_consumer()
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}



// CosNotifyFilter::FilterAdmin operations

CosNotifyFilter::FilterID 
TIDNotif::SupplierAdminImpl::add_filter(CosNotifyFilter::Filter_ptr filter)
{
  SupplierAdminData* admin_data = getData();
  return admin_data->filterAdminDelegate->add_filter(filter);
}

void TIDNotif::SupplierAdminImpl::remove_filter(CosNotifyFilter::FilterID filter)
  throw (CosNotifyFilter::FilterNotFound)
{
  SupplierAdminData* admin_data = getData();
  admin_data->filterAdminDelegate->remove_filter(filter);
}

CosNotifyFilter::Filter* 
TIDNotif::SupplierAdminImpl::get_filter(CosNotifyFilter::FilterID filter)
  throw (CosNotifyFilter::FilterNotFound) 
{
  SupplierAdminData* admin_data = getData();
  return admin_data->filterAdminDelegate->get_filter(filter);
}

CosNotifyFilter::FilterIDSeq* 
TIDNotif::SupplierAdminImpl::get_all_filters() 
{
  SupplierAdminData* admin_data = getData();
  return admin_data->filterAdminDelegate->get_all_filters();
}


void TIDNotif::SupplierAdminImpl::remove_all_filters()
{
  SupplierAdminData* admin_data = getData();
  admin_data->filterAdminDelegate->remove_all_filters();
}


// CosNotification::QoSAdmin operations

CosNotification::QoSProperties* 
TIDNotif::SupplierAdminImpl::get_qos()
{
  SupplierAdminData* admin_data = getData();
  return admin_data->qosAdminDelegate->get_qos();
}

void TIDNotif::SupplierAdminImpl::set_qos(
                              const CosNotification::QoSProperties& qos)
  throw (CosNotification::UnsupportedQoS)
{
  SupplierAdminData* admin_data = getData();

  try{
    admin_data->qosAdminDelegate->set_qos(qos);
  }
  catch(const CosNotification::UnsupportedQoS& ex){
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "SupplierAdminImpl::set_qos: QoSProperties not supported";
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data(), ex);
    }
    throw;
  }

  CORBA::PolicyList* policies = 
    admin_data->qosAdminDelegate->getPolicies();
  

  try{
    CORBA::Object_var orbQosObj =
      m_orb->resolve_initial_references("ORBPolicyManager");
    CORBA::PolicyManager_var orbQos =
      CORBA::PolicyManager::_narrow(orbQosObj);
    orbQos->set_policy_overrides(*policies, CORBA::SET_OVERRIDE);
  }
  catch(...){
    if (m_orb->trace != NULL){
      m_orb->print_trace(TIDorb::util::TR_ERROR, "Error: _set_policy_overrides");
    }
    delete policies;
    throw CosNotification::UnsupportedQoS();
  }



  // TIDNotifJ:
  //   data.reference = 
  //     InternalConsumerAdminHelper.narrow 
  //     (
  //      data.reference._set_policy_override(policies,
  //                                          SetOverrideType.SET_OVERRIDE
  //                                          )
  //      );
  // ¿ may be equivalent ?
  //  context = delegate->getPolicyContext();
  //  context->setPolicies(*policies, CORBA::SET_OVERRIDE);

}

void TIDNotif::SupplierAdminImpl::validate_qos(
                      const CosNotification::QoSProperties& required_qos, 
                      CosNotification::NamedPropertyRangeSeq*& available_qos)
  throw (CosNotification::UnsupportedQoS)
{
  SupplierAdminData* admin_data = getData();
  admin_data->qosAdminDelegate->validate_qos(required_qos, available_qos);
}


// CosNotifyComm::NotifyPublish operations

void TIDNotif::SupplierAdminImpl::offer_change(
                                const CosNotification::EventTypeSeq& added, 
                                const CosNotification::EventTypeSeq& removed)
  throw (CosNotifyComm::InvalidEventType)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

void TIDNotif::SupplierAdminImpl::readObject(istream & is)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  SupplierAdminData* data = 
    new SupplierAdminData(m_orb, m_supplier_admin_poa, 0, 0, AND_OP);
  
  // Read AdminID
  is >> data->_id;
  // Read reference to channel 
  try {
    string str_ref;
    is >> str_ref;
    CORBA::Object_var object = m_orb->string_to_object(str_ref.c_str());
    data->_channel = 
      NotificationInternals::InternalDistributionChannel::_narrow(object);
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering reference to channel of SupplierAdmin " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Read actual counterProxyPushConsumer for channels
  is >> data->counterProxyPushConsumer;
  // Read all about consumerAdminTable: IDs and IORs
  try {
    int proxyPushConsumers_size;
    is >> proxyPushConsumers_size;
    ProxyPushConsumerData* proxy_data;
    PortableServer::ObjectId_var oid;
    for (int i = 0; i < proxyPushConsumers_size; i++){
      ProxyID proxy_id;
      string str_ref;
      is >> proxy_id;

      // Get channel POA in order with configuration
      // TODO: refactor this block int ThePOAFactory
      PortableServer::POA_var proxy_consumer_poa;
      if (m_supplier_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
        if (m_orb->trace != NULL){
          TIDorb::util::StringBuffer msg;
          msg << "Using Global POA for ProxyPushConsumer " << proxy_id; 
          m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
        }
        proxy_consumer_poa = m_proxy_consumer_poa;
      } else { // Local
        if (m_orb->trace != NULL){
          TIDorb::util::StringBuffer msg;
          msg << "Creating Local POA for ProxyPushConsumer " << proxy_id; 
          m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
        }
        TIDorb::util::StringBuffer proxy_consumer_poa_name;
        proxy_consumer_poa_name << "ProxyPushConsumer" << proxy_id;
        CORBA::PolicyList policy_list;
        policy_list.length(5);
        policy_list[0] = m_proxy_consumer_poa->create_id_assignment_policy(PortableServer::USER_ID);
        policy_list[1] = m_proxy_consumer_poa->create_lifespan_policy (PortableServer::PERSISTENT);
        policy_list[2] = m_proxy_consumer_poa->create_request_processing_policy(
                                                            PortableServer::USE_DEFAULT_SERVANT);
        policy_list[3] = m_proxy_consumer_poa->create_servant_retention_policy(PortableServer::RETAIN);
        policy_list[4] = m_proxy_consumer_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
        proxy_consumer_poa = 
          m_proxy_consumer_poa->create_POA(proxy_consumer_poa_name.str().data(), NULL, policy_list);
          
        PortableServer::POAManager_var proxy_consumer_poa_mgr = 
          m_proxy_consumer_poa->the_POAManager();
          
        TIDNotif::ProxyPushConsumerImpl* proxy_consumer_servant;
        proxy_consumer_servant = new TIDNotif::ProxyPushConsumerImpl(m_orb, 
                                                                     proxy_consumer_poa); 
          
        proxy_consumer_poa->set_servant(proxy_consumer_servant);
          
        proxy_consumer_poa_mgr->activate();
      }


      proxy_data = 
        new TIDNotif::ProxyPushConsumerData(m_orb, m_proxy_consumer_poa, 
                                            proxy_id, data->_id, 0); // TODO

      TIDNotif::ProxyPushConsumerImpl* proxy_consumer_impl = 
        dynamic_cast < TIDNotif::ProxyPushConsumerImpl* > (proxy_consumer_poa->get_servant());
      
      proxy_consumer_impl->register_proxy(proxy_data);

      is >> str_ref;

      TIDorb::util::StringBuffer str_id;
      str_id << "ProxyConsumer_" << proxy_data->_channel_id << "_";
      str_id << proxy_data->_admin_id << "_" << proxy_id;
      oid = PortableServer::string_to_ObjectId(str_id.str().data());

      if (PersistenceManager::getDB()->data_saved(proxy_consumer_impl))
       PersistenceManager::getDB()->load_ppushc(proxy_consumer_impl);
      
      CORBA::Object_var object = 
        proxy_consumer_poa->create_reference_with_id(oid, 
                                      _InternalProxyPushConsumerHelper::id());
      NotificationInternals::InternalProxyPushConsumer_ptr ref =
        NotificationInternals::InternalProxyPushConsumer::_narrow(object);
      data->proxyPushConsumers[proxy_id] = ref;
    }
  } catch (...) { 
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering consumerAdminTable of SupplierAdmin " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }


  // Read _destroying flag
  is >> data->_destroying;

  //Read Filters
  try {
    TIDorb::util::StringBuffer buf;
    string filter_id;
    int f_id;
    int filter_n;
    is >> filter_n;
    for (int i = 0; i < filter_n ; i++) {
      is >> f_id;
      buf << f_id;
      filter_id = buf.str();
      PersistenceManager::getDB()->load_filter(filter_id, 
                                               data->filterAdminDelegate);
    }
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering Filters of SupplierAdmin " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }
  
  // Read QoS properties
  try {
    data->qosAdminDelegate = new TIDNotif::qos::ProxyQoSAdmin(m_orb);
    data->qosAdminDelegate->readObject(is);  
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering QoSAdminDelegate of SupplierAdmin " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  this->register_admin(data);
}

void TIDNotif::SupplierAdminImpl::writeObject(ostream & os)
{

  TIDThr::Synchronized synchro(m_recursive_mutex);
  
  SupplierAdminData* data = getData();

  // Write AdminID
  os << data->_id << endl;

  CORBA::String_var str_ref; 
  
  // Write reference to channel 
  try {
    str_ref = m_orb->object_to_string(data->_channel);
    os << str_ref << endl;
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving reference to channel of SupplierAdmin " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }
  
  // Write actual counterProxyPushConsumer for channels
  os << data->counterProxyPushConsumer << endl;

  // Write all about consumerAdminTable: IDs and IORs
  try {
    os << data->proxyPushConsumers.size() << endl;
    proxyPushConsumerMap::iterator it   = data->proxyPushConsumers.begin();
    proxyPushConsumerMap::iterator end  = data->proxyPushConsumers.end();
    while (it != end){
      str_ref = m_orb->object_to_string((*it).second);
      os << (*it).first << endl;
      os << str_ref << endl;
      it++;
    }
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving consumerAdminTable of SupplierAdmin " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Write _destroying flag
  os << data->_destroying << endl;

  //Write Filters
  try {
    CosNotifyFilter::FilterIDSeq_var filterIDSeq = 
      data->filterAdminDelegate->get_all_filters();
    int size = filterIDSeq->length();
    os << size << endl;
    for (int i=0; i<size;i++) {
      os << (*filterIDSeq)[i] << endl;
    }
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving Filters of SupplierAdmin " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Write QoS properties
  try {
    data->qosAdminDelegate->writeObject(os);
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving QoSAdminDelegate of SupplierAdmin " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }
}
