/*
 *  File name: ConsumerAdminImpl.C
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

#include "ConsumerAdminImpl.h"


TIDNotif::ConsumerAdminImpl::ConsumerAdminImpl(
                           TIDorb::core::TIDORB* orb,
                           PortableServer::POA_ptr poa):
  m_orb(orb), m_consumer_admin_poa(poa)
{
  // Select configuration for consumer'ss POA
  m_consumer_POA_config = 
    TIDNotif::util::TIDNotifConfig::getInt(TIDNotif::util::TIDNotifConfig::CONSUMER_POA_KEY);

  // Create a ConsumerAdminPOA
  PortableServer::POAManager_var poa_manager = m_consumer_admin_poa->the_POAManager();
  TIDorb::util::StringBuffer name_poa;
  name_poa << "ProxyPushSupplierPOA";

  try{
    
    CORBA::PolicyList policy_list;
    policy_list.length(5);
    policy_list[0] = m_consumer_admin_poa->create_id_assignment_policy(PortableServer::USER_ID);
    policy_list[1] = m_consumer_admin_poa->create_lifespan_policy (PortableServer::PERSISTENT);
    policy_list[2] = m_consumer_admin_poa->create_request_processing_policy(
                                                             PortableServer::USE_DEFAULT_SERVANT);
    policy_list[3] = m_consumer_admin_poa->create_servant_retention_policy(PortableServer::RETAIN);
    policy_list[4] = m_consumer_admin_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
    m_proxy_supplier_poa = 
      m_consumer_admin_poa->create_POA("ProxyPushSupplierPOA", 
                                       poa_manager, policy_list);
    
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << name_poa.str().data() << " created";
      m_orb->print_trace(TIDorb::util::TR_DEEP_DEBUG, msg.str().data());
    }
  } catch(PortableServer::POA::AdapterAlreadyExists& ex){

    TIDorb::util::StringBuffer msg;
    try{
      m_proxy_supplier_poa =
        m_consumer_admin_poa->find_POA(name_poa.str().data(), false);
      TIDorb::util::StringBuffer msg;
      msg << name_poa.str().data() << " already exists!"; 
      if (m_orb->trace != NULL)
        m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    } catch (PortableServer::POA::AdapterNonExistent&){
      throw CORBA::INTERNAL(msg.str().data());
    }

  } 

  CORBA::Object_var obj_cur = orb->resolve_initial_references("POACurrent");
  m_current = PortableServer::Current::_narrow(obj_cur);

  if (m_consumer_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {    
    ProxyPushSupplierImpl* proxy_servant = 
      new ProxyPushSupplierImpl(m_orb, m_proxy_supplier_poa);

    m_proxy_supplier_poa->set_servant(proxy_servant);
  }

}


TIDNotif::ConsumerAdminImpl::~ConsumerAdminImpl()
{
  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "Deleting ConsumerAdminImpl with id "; 
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }
}


TIDNotif::ConsumerAdminData* TIDNotif::ConsumerAdminImpl::getData()
{
  try {
    PortableServer::ObjectId_var oid = m_current->get_object_id();
    TIDorb::core::poa::OID oid_key(oid);

    ConsumerAdminDataTable::iterator it = m_consumer_admins.find(oid_key);
    if (it != m_consumer_admins.end()){
      return (*it).second;
    }
    else
      throw CORBA::OBJECT_NOT_EXIST();  

  } catch (const CORBA::Exception& ex) {
    
    throw CORBA::INV_OBJREF();
  }
}

  
void TIDNotif::ConsumerAdminImpl::register_admin(
                                           TIDNotif::ConsumerAdminData* data)
{
  TIDorb::util::StringBuffer id_str;
  id_str << "ConsumerAdmin_" << data->_channel_id << "_" << data->_id;

  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(id_str.str().data());

  TIDorb::core::poa::OID oid_key(oid);

  m_consumer_admins[oid_key] = data;
}


void TIDNotif::ConsumerAdminImpl::unregister_admin(
                                           TIDNotif::ConsumerAdminData* data)
{
  TIDorb::util::StringBuffer id_str;
  id_str << "ConsumerAdmin_" << data->_channel_id << "_" << data->_id;

  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(id_str.str().data());

  TIDorb::core::poa::OID oid_key(oid);

  // Destroy POA and POAManager if POA config is LOCAL
  if (m_consumer_POA_config == TIDNotif::util::TIDNotifConfig::LOCAL_POA) {
    TIDorb::util::StringBuffer consumer_admin_poa_name;
    consumer_admin_poa_name << "ConsumerAdminPOA" << data->_id;
    try {
      PortableServer::POAManager_var consumer_admin_poa_manager = 
        m_consumer_admin_poa->the_POAManager();
      consumer_admin_poa_manager->deactivate(true, false);
      m_consumer_admin_poa->destroy(true, false);
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

  ConsumerAdminDataTable::iterator it = m_consumer_admins.find(oid_key);
  if (it != m_consumer_admins.end()){
    m_consumer_admins.erase(it);
    delete data;
  }


}


// NotificationInternals::InternalConsumerAdmin

void TIDNotif::ConsumerAdminImpl::dispatch_event(const CORBA::Any& data)
{

  TIDThr::Synchronized synchro(m_recursive_mutex);

  ConsumerAdminData* admin_data = getData();

  // Filter event 
  try{

    if (! admin_data->filterAdminDelegate->match(data) ) {
      if (m_orb->trace != NULL){
        m_orb->print_trace(TIDorb::util::TR_DEBUG, "DISCARD_EVENT");
      }
      return;
    }

  } catch (const CosNotifyFilter::UnsupportedFilterableData& ufd ){
    if (m_orb->trace != NULL){
      m_orb->print_trace(TIDorb::util::TR_ERROR, "UnsupportedFilterableData", 
                         ufd);
    }
    return;
  }


  // Dispatch event to correct ProxyPushSupplier
  proxyPushSupplierMap::iterator it = admin_data->proxyPushSuppliers.begin();
  proxyPushSupplierMap::iterator end = admin_data->proxyPushSuppliers.end();

  while (it != end){
    InternalProxyPushSupplier_ptr proxy = (*it).second;

    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "ConsumerAdminImpl::dispactch_event to proxy with id " << (*it).first; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }

    const CosNotification::StructuredEvent* structured_event;
    
    if (data >>= structured_event){
      if ( (proxy->MyType() == CosNotifyChannelAdmin::PUSH_STRUCTURED) )
        proxy->push_event(data); // oneway request
    }
    else{
      if ( (proxy->MyType() == CosNotifyChannelAdmin::PUSH_ANY) )
        proxy->push_event(data); // oneway request
    }
    
    it++;
  }

}
 
CosNotifyChannelAdmin::AdminID TIDNotif::ConsumerAdminImpl::getAdminId()
{
  ConsumerAdminData* admin_data = getData();
  return admin_data->_id;
}

void TIDNotif::ConsumerAdminImpl::removeProxyPushSupplier(
                                        CosNotifyChannelAdmin::ProxyID id)
{
  ConsumerAdminData* admin_data = getData();

  if (admin_data->_destroying)
    return;


  {
    TIDThr::Synchronized synchro(m_recursive_mutex);
  
    admin_data->proxyPushSuppliers.erase(id);

    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Removed and deactivated ProxyPushSupplierImpl with Id " << id; 
      m_orb->print_trace(TIDorb::util::TR_DEEP_DEBUG, msg.str().data());
    }

    if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_PROXY_PUSH_SUPPLIER,
                                               this);
    }
  }
}
  
void TIDNotif::ConsumerAdminImpl::removeProxyPullSupplier(
                                        CosNotifyChannelAdmin::ProxyID id)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}
		
void TIDNotif::ConsumerAdminImpl::destroyFromChannel()
{
  ConsumerAdminData* admin_data = getData();

  if (admin_data->_destroying)
    return;

  admin_data->_destroying = true;


  {
    TIDThr::Synchronized synchro(m_recursive_mutex);

    proxyPushSupplierMap::iterator it  = admin_data->proxyPushSuppliers.begin();
    proxyPushSupplierMap::iterator end = admin_data->proxyPushSuppliers.end();
    
    while (it != end){
      InternalProxyPushSupplier_ptr proxy = (*it).second;
      
      if (m_orb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "ConsumerAdminImpl::destroy proxy with id " << (*it).first; 
        m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
      }
      
      proxy->destroyFromAdmin();
      it++;
    }
    
    admin_data->proxyPushSuppliers.clear();

    if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->delete_data(this);
    }  //TODO_MORFEO: delete_data or update_data
  }
  
  this->unregister_admin(admin_data);
}
  
  
void TIDNotif::ConsumerAdminImpl::loadData()
{

}


// CosNotifyChannelAdmin::ConsumerAdmin


CosNotifyChannelAdmin::AdminID TIDNotif::ConsumerAdminImpl::MyID()
{
  ConsumerAdminData* admin_data = getData();
  return admin_data->_id;
}


CosNotifyChannelAdmin::EventChannel_ptr 
TIDNotif::ConsumerAdminImpl::MyChannel()
{
  ConsumerAdminData* admin_data = getData();
  return CosNotifyChannelAdmin::EventChannel::_duplicate(admin_data->_channel);
}


CosNotifyChannelAdmin::InterFilterGroupOperator 
TIDNotif::ConsumerAdminImpl::MyOperator()
{
  ConsumerAdminData* admin_data = getData();
  return admin_data->m_operator;
}


CosNotifyFilter::MappingFilter_ptr 
TIDNotif::ConsumerAdminImpl::priority_filter()
{
  ConsumerAdminData* admin_data = getData();

  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "GET_PRIORITY_DISCRIMINATOR"; 
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }
  
  if (admin_data->priority_discriminator == NULL) {
    
    CORBA::Any_var default_value = m_orb->create_any();
    *default_value <<= CosNotification::DefaultPriority;
    
    try {
      admin_data->priority_discriminator =		    
        admin_data->_channel->create_mapping_filter(
                                  util::parser::TIDParser::_CONSTRAINT_GRAMMAR,
                                  default_value);
    }
    catch (const CosNotifyFilter::InvalidGrammar& e) {
      if (m_orb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "ConsumerAdminImpl::priority_filter InvalidGrammar"; 
        m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data(), e);
      }
    }
  }
  return admin_data->priority_discriminator;	
}


void TIDNotif::ConsumerAdminImpl::priority_filter(
                                     CosNotifyFilter::MappingFilter_ptr value)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}


CosNotifyFilter::MappingFilter_ptr TIDNotif::ConsumerAdminImpl::lifetime_filter()
{
  ConsumerAdminData* admin_data = getData();

  if (admin_data->lifetime_discriminator == NULL) {
    CORBA::Any_var default_value = m_orb->create_any();
    

    // TimeT is in 100 ns. units
    TimeBase::UtcT utc_time = TIDorb::core::util::Time::currentUtcT();
    utc_time.time += (5 * 10000000); // now + 5 ''

    *default_value <<= utc_time.time;
    
    try {

      admin_data->lifetime_discriminator = 
        admin_data->_channel->create_mapping_filter(util::parser::TIDParser::_CONSTRAINT_GRAMMAR,
                                        default_value);
    }
    catch (const CosNotifyFilter::InvalidGrammar& e) {
      if (m_orb->trace != NULL)
        m_orb->print_trace(TIDorb::util::TR_ERROR, 
                           "ConsumerAdminImpl::lifetime_filter InvalidGrammar",
                           e);
    }
  }  

  return admin_data->lifetime_discriminator;

}


void TIDNotif::ConsumerAdminImpl::lifetime_filter(CosNotifyFilter::MappingFilter_ptr value)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}


CosNotifyChannelAdmin::ProxyIDSeq* TIDNotif::ConsumerAdminImpl::pull_suppliers()
{
  //   ProxyIDSeq* seq = new ProxyIDSeq;
  //   seq->length(0);

  //   return seq;

  throw CORBA::NO_IMPLEMENT("No implemented");
}


CosNotifyChannelAdmin::ProxyIDSeq* TIDNotif::ConsumerAdminImpl::push_suppliers()
{
  ConsumerAdminData* admin_data = getData();

  proxyPushSupplierMap::iterator it  = admin_data->proxyPushSuppliers.begin();
  proxyPushSupplierMap::iterator end = admin_data->proxyPushSuppliers.end();

  ProxyIDSeq* seq = new ProxyIDSeq;
  seq->length(admin_data->proxyPushSuppliers.size());

  int i = 0;
  while (it != end){
    (*seq)[i]=(*it).first;
    it++;
    i++;
  }
  return seq;
}

		
CosNotifyChannelAdmin::ProxySupplier_ptr 
TIDNotif::ConsumerAdminImpl::get_proxy_supplier(
                                       CosNotifyChannelAdmin::ProxyID proxy_id)
  throw (CosNotifyChannelAdmin::ProxyNotFound)
{
  ConsumerAdminData* admin_data = getData();

  proxyPushSupplierMap::iterator it = admin_data->proxyPushSuppliers.find(proxy_id);
  if (it !=  admin_data->proxyPushSuppliers.end()){
    return ProxyPushSupplier::_duplicate((*it).second);
  }
  else
    throw CosNotifyChannelAdmin::ProxyNotFound();
}

		
CosNotifyChannelAdmin::ProxySupplier_ptr 
TIDNotif::ConsumerAdminImpl::obtain_notification_pull_supplier(
                                     CosNotifyChannelAdmin::ClientType ctype, 
                                     CosNotifyChannelAdmin::ProxyID& proxy_id)
  throw (CosNotifyChannelAdmin::AdminLimitExceeded)
{

  throw CORBA::NO_IMPLEMENT("No implement");
}

	
CosNotifyChannelAdmin::ProxySupplier_ptr 
TIDNotif::ConsumerAdminImpl::obtain_notification_push_supplier(
                                               CosNotifyChannelAdmin::ClientType ctype, 
                                               CosNotifyChannelAdmin::ProxyID& proxy_id)
  throw (CosNotifyChannelAdmin::AdminLimitExceeded)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  ConsumerAdminData* admin_data = getData();

  ProxyPushSupplierData* proxy_data;

  // Assing a unique id to proxy
  proxy_id = admin_data->counterProxyPushSupplier++;

  // Get channel POA in order with configuration
  // TODO: refactor this block int ThePOAFactory
  PortableServer::POA_var proxy_supplier_poa;
  if (m_consumer_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Using Global POA for ProxyPushSupplier " << proxy_id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    proxy_supplier_poa = m_proxy_supplier_poa;
  } else { // Local
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Creating Local POA for ProxyPushSupplier " << proxy_id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    TIDorb::util::StringBuffer proxy_supplier_poa_name;
    proxy_supplier_poa_name << "ProxyPushSupplier" << proxy_id;
    CORBA::PolicyList policy_list;
    policy_list.length(5);
    policy_list[0] = m_proxy_supplier_poa->create_id_assignment_policy(PortableServer::USER_ID);
    policy_list[1] = m_proxy_supplier_poa->create_lifespan_policy (PortableServer::PERSISTENT);
    policy_list[2] = m_proxy_supplier_poa->create_request_processing_policy(
                                                                            PortableServer::USE_DEFAULT_SERVANT);
    policy_list[3] = m_proxy_supplier_poa->create_servant_retention_policy(PortableServer::RETAIN);
    policy_list[4] = m_proxy_supplier_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);

    PortableServer::POAManager_var proxy_supplier_poa_mgr = 
      m_proxy_supplier_poa->the_POAManager();

    proxy_supplier_poa = 
      m_proxy_supplier_poa->create_POA(proxy_supplier_poa_name.str().data(), 
                                       proxy_supplier_poa_mgr, policy_list);        
          
    TIDNotif::ProxyPushSupplierImpl* proxy_supplier_servant;
    proxy_supplier_servant = new TIDNotif::ProxyPushSupplierImpl(m_orb, 
                                                                 proxy_supplier_poa); 
          
    proxy_supplier_poa->set_servant(proxy_supplier_servant);
          
    //proxy_supplier_poa_mgr->activate();
  }

  // Create a new proxy
  switch (ctype){
  case CosNotifyChannelAdmin::ANY_EVENT:
  case CosNotifyChannelAdmin::STRUCTURED_EVENT:
    {
        
      proxy_data = new ProxyPushSupplierData(m_orb, m_proxy_supplier_poa, 
                                             proxy_id,  admin_data->_id, 
                                             admin_data->_channel_id);

      TIDNotif::ProxyPushSupplierImpl* proxy_supplier_impl = 
        dynamic_cast < TIDNotif::ProxyPushSupplierImpl* > (proxy_supplier_poa->get_servant());

      proxy_supplier_impl->register_proxy(proxy_data);
      break;
    }
  default:
    if (m_orb->trace != NULL)
      m_orb->print_trace(TIDorb::util::TR_USER, 
                        "obtain_notification_push_supplier not implement ClientType");
    throw CORBA::NO_IMPLEMENT("No implemented");
  }

  // Activate proxy
  TIDorb::util::StringBuffer str_id;
  str_id << "ProxySupplier_" << proxy_data->_channel_id << "_";
  str_id << proxy_data->_admin_id << "_" << proxy_id;
  
  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(str_id.str().data());
  
  CORBA::Object_var object = 
    proxy_supplier_poa->create_reference_with_id(oid, 
                                _InternalProxyPushSupplierHelper::id());

  InternalProxyPushSupplier_ptr proxy_ptr = 
    InternalProxyPushSupplier::_narrow(object);

  
  // Insert into proxys table
  admin_data->proxyPushSuppliers[proxy_id] = proxy_ptr;
  
  if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(
                                PersistenceDB::ATTR_PROXY_PUSH_SUPPLIER,
                                this);
  }

  return CosNotifyChannelAdmin::ProxySupplier::_narrow(proxy_ptr);
}


void TIDNotif::ConsumerAdminImpl::destroy()
{
  ConsumerAdminData* admin_data = getData();

  admin_data->_channel->removeConsumerAdmin(admin_data->_id);
  
  this->destroyFromChannel();

}



// CosNotifyComm::NotifySubscribe

void TIDNotif::ConsumerAdminImpl::subscription_change(
                                  const CosNotification::EventTypeSeq& added, 
                                  const CosNotification::EventTypeSeq& removed)
  throw (CosNotifyComm::InvalidEventType)
{

  throw CORBA::NO_IMPLEMENT("No implemented");

}


// CosEventChannelAdmin::ConsumerAdmin

CosEventChannelAdmin::ProxyPushSupplier_ptr 
TIDNotif::ConsumerAdminImpl::obtain_push_supplier(){

  TIDThr::Synchronized synchro(m_recursive_mutex);

  ConsumerAdminData* admin_data = getData();

  // Assing a unique id to proxy
  CosNotifyChannelAdmin::ProxyID proxy_id = admin_data->counterProxyPushSupplier++;

  // Get channel POA in order with configuration
  // TODO: refactor this block int ThePOAFactory
  PortableServer::POA_var proxy_supplier_poa;
  if (m_consumer_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Using Global POA for ProxyPushSupplier " << proxy_id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    proxy_supplier_poa = m_proxy_supplier_poa;
  } else { // Local
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Creating Local POA for ProxyPushSupplier " << proxy_id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    TIDorb::util::StringBuffer proxy_supplier_poa_name;
    proxy_supplier_poa_name << "ProxyPushSupplier" << proxy_id;
    CORBA::PolicyList policy_list;
    policy_list.length(5);
    policy_list[0] = m_proxy_supplier_poa->create_id_assignment_policy(PortableServer::USER_ID);
    policy_list[1] = m_proxy_supplier_poa->create_lifespan_policy (PortableServer::PERSISTENT);
    policy_list[2] = m_proxy_supplier_poa->create_request_processing_policy(
                                                    PortableServer::USE_DEFAULT_SERVANT);
    policy_list[3] = m_proxy_supplier_poa->create_servant_retention_policy(PortableServer::RETAIN);
    policy_list[4] = m_proxy_supplier_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);

    PortableServer::POAManager_var proxy_supplier_poa_mgr = 
      m_proxy_supplier_poa->the_POAManager();

    proxy_supplier_poa = 
      m_proxy_supplier_poa->create_POA(proxy_supplier_poa_name.str().data(), 
                                       proxy_supplier_poa_mgr, policy_list);
          
    TIDNotif::ProxyPushSupplierImpl* proxy_supplier_servant;
    proxy_supplier_servant = new TIDNotif::ProxyPushSupplierImpl(m_orb, 
                                                                 proxy_supplier_poa); 
          
    proxy_supplier_poa->set_servant(proxy_supplier_servant);
          
    //proxy_supplier_poa_mgr->activate();
  }


  // Create a new proxy
  ProxyPushSupplierData* proxy_data = 
    new ProxyPushSupplierData(m_orb, m_proxy_supplier_poa, proxy_id, 
                              admin_data->_id, admin_data->_channel_id);

  TIDNotif::ProxyPushSupplierImpl* proxy_supplier_impl = 
    dynamic_cast < TIDNotif::ProxyPushSupplierImpl* > (proxy_supplier_poa->get_servant());

  proxy_supplier_impl->register_proxy(proxy_data);

  // Activate proxy
  TIDorb::util::StringBuffer str_id;
  str_id << "ProxySupplier_" << proxy_data->_channel_id << "_";
  str_id << proxy_data->_admin_id << "_" << proxy_id;
  
  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(str_id.str().data());
  
  CORBA::Object_var object = 
    proxy_supplier_poa->create_reference_with_id(oid, 
                                      _InternalProxyPushSupplierHelper::id());
  InternalProxyPushSupplier_ptr proxy_ptr = 
    InternalProxyPushSupplier::_narrow(object);

  if (CORBA::is_nil(proxy_ptr)){
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Null reference to InternalProxyPushSupplier obtained "; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    exit(1);
  }

  // Insert into proxys table
  admin_data->proxyPushSuppliers[proxy_id] = proxy_ptr;

  if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(
                                      PersistenceDB::ATTR_PROXY_PUSH_SUPPLIER,
                                      this);
  }

  return CosEventChannelAdmin::ProxyPushSupplier::_narrow(proxy_ptr);
}


CosEventChannelAdmin::ProxyPullSupplier_ptr 
TIDNotif::ConsumerAdminImpl::obtain_pull_supplier()
{
  throw CORBA::NO_IMPLEMENT("No implement");
}


// CosNotifyFilter::FilterAdmin operations

CosNotifyFilter::FilterID 
TIDNotif::ConsumerAdminImpl::add_filter(CosNotifyFilter::Filter_ptr filter)
{
  ConsumerAdminData* admin_data = getData();
  return admin_data->filterAdminDelegate->add_filter(filter);
}


void TIDNotif::ConsumerAdminImpl::remove_filter(CosNotifyFilter::FilterID filter)
  throw (CosNotifyFilter::FilterNotFound)
{
  ConsumerAdminData* admin_data = getData();
  admin_data->filterAdminDelegate->remove_filter(filter);
}


CosNotifyFilter::Filter_ptr 
TIDNotif::ConsumerAdminImpl::get_filter(CosNotifyFilter::FilterID filter)
  throw (CosNotifyFilter::FilterNotFound)
{
  ConsumerAdminData* admin_data = getData();
  return admin_data->filterAdminDelegate->get_filter(filter);
}


CosNotifyFilter::FilterIDSeq* TIDNotif::ConsumerAdminImpl::get_all_filters()
{
  ConsumerAdminData* admin_data = getData();
  return admin_data->filterAdminDelegate->get_all_filters();
}


void TIDNotif::ConsumerAdminImpl::remove_all_filters()
{
  ConsumerAdminData* admin_data = getData();
  admin_data->filterAdminDelegate->remove_all_filters();
}


// CosNotification::QoSAdmin operations

CosNotification::QoSProperties* TIDNotif::ConsumerAdminImpl::get_qos()
{
  ConsumerAdminData* admin_data = getData();
  return admin_data->qosAdminDelegate->get_qos();
}


void TIDNotif::ConsumerAdminImpl::set_qos(const CosNotification::QoSProperties& qos)
  throw (CosNotification::UnsupportedQoS)
{
  ConsumerAdminData* admin_data = getData();

  try{
    admin_data->qosAdminDelegate->set_qos(qos);
  }
  catch(const CosNotification::UnsupportedQoS& ex){
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "ConsumerAdminImpl::set_qos: QoSProperties not supported";
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


void TIDNotif::ConsumerAdminImpl::validate_qos(
                                     const CosNotification::QoSProperties& required_qos, 
                                     CosNotification::NamedPropertyRangeSeq*& available_qos)
  throw (CosNotification::UnsupportedQoS)
{
  ConsumerAdminData* admin_data = getData();
  admin_data->qosAdminDelegate->validate_qos(required_qos, available_qos);
}


void TIDNotif::ConsumerAdminImpl::readObject(istream & is)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  ConsumerAdminData* data = 
    new ConsumerAdminData(m_orb, m_consumer_admin_poa, 0, 0, AND_OP);
  
  // Read AdminID
  is >> data->_id;
  
  // Read reference to channel 
  try {
    string str_ref;
    is >> str_ref;
    CORBA::Object_var object = m_orb->string_to_object(str_ref.c_str());
    data->_channel = NotificationInternals::InternalDistributionChannel::_narrow(object);
  } catch (...) {
   if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering reference to channel of ConsumerAdmin " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Read current counterProxyPushSupplier for channels
  is >> data->counterProxyPushSupplier;

  // Read all data about consumerAdminTable: IDs and IORs
  try {
    int proxyPushSuppliers_size;
    is >> proxyPushSuppliers_size;
    //ProxyPushSupplierImpl* proxy_impl;
    ProxyPushSupplierData* proxy_data;
    PortableServer::ObjectId_var oid;
    for (int i = 0; i < proxyPushSuppliers_size; i++){
      ProxyID proxy_id;
      string str_ref;
      is >> proxy_id;

      // Get channel POA in order with configuration
      // TODO: refactor this block int ThePOAFactory
      PortableServer::POA_var proxy_supplier_poa;
      if (m_consumer_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
        if (m_orb->trace != NULL){
          TIDorb::util::StringBuffer msg;
          msg << "Using Global POA for ProxyPushSupplier " << proxy_id; 
          m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
        }
        proxy_supplier_poa = m_proxy_supplier_poa;
      } else { // Local
        if (m_orb->trace != NULL){
          TIDorb::util::StringBuffer msg;
          msg << "Creating Local POA for ProxyPushSupplier " << proxy_id; 
          m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
        }
        TIDorb::util::StringBuffer proxy_supplier_poa_name;
        proxy_supplier_poa_name << "ProxyPushSupplier" << proxy_id;
        CORBA::PolicyList policy_list;
        policy_list.length(5);
        policy_list[0] = m_proxy_supplier_poa->create_id_assignment_policy(PortableServer::USER_ID);
        policy_list[1] = m_proxy_supplier_poa->create_lifespan_policy (PortableServer::PERSISTENT);
        policy_list[2] = m_proxy_supplier_poa->create_request_processing_policy(
                                                            PortableServer::USE_DEFAULT_SERVANT);
        policy_list[3] = m_proxy_supplier_poa->create_servant_retention_policy(PortableServer::RETAIN);
        policy_list[4] = m_proxy_supplier_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);

        PortableServer::POAManager_var proxy_supplier_poa_mgr = 
          m_proxy_supplier_poa->the_POAManager();

        proxy_supplier_poa = 
          m_proxy_supplier_poa->create_POA(proxy_supplier_poa_name.str().data(), 
                                           proxy_supplier_poa_mgr, policy_list);        
          
        TIDNotif::ProxyPushSupplierImpl* proxy_supplier_servant;
        proxy_supplier_servant = new TIDNotif::ProxyPushSupplierImpl(m_orb, 
                                                                     proxy_supplier_poa); 
          
        proxy_supplier_poa->set_servant(proxy_supplier_servant);
          
        //proxy_supplier_poa_mgr->activate();
      }


      proxy_data = new ProxyPushSupplierData(m_orb, m_proxy_supplier_poa, proxy_id, 
                                             data->_id, 0); // TODO

      TIDNotif::ProxyPushSupplierImpl* proxy_supplier_impl = 
        dynamic_cast < TIDNotif::ProxyPushSupplierImpl* > (proxy_supplier_poa->get_servant());
      
      proxy_supplier_impl->register_proxy(proxy_data);

      is >> str_ref;

      TIDorb::util::StringBuffer str_id;
      str_id << "ProxySupplier_" << proxy_data->_channel_id << "_";
      str_id << proxy_data->_admin_id << "_" << proxy_id;
      oid = PortableServer::string_to_ObjectId(str_id.str().data());

      if (PersistenceManager::getDB()->data_saved(proxy_supplier_impl)) 
        PersistenceManager::getDB()->load_ppushs(proxy_supplier_impl);
      

      CORBA::Object_var object = 
        proxy_supplier_poa->create_reference_with_id(oid, 
                                     _InternalProxyPushSupplierHelper::id());
      NotificationInternals::InternalProxyPushSupplier_ptr ref;
      ref = NotificationInternals::InternalProxyPushSupplier::_narrow(object);
      data->proxyPushSuppliers[proxy_id] = ref;
    }
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering consumerAdminTable of ConsumerAdmin " << data->_id;
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
      msg << "ERROR recovering consumerAdminTable of ConsumerAdmin " << data->_id;
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
      msg << "ERROR recovering consumerAdminTable of ConsumerAdmin " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  this->register_admin(data);
  
}

void TIDNotif::ConsumerAdminImpl::writeObject(ostream & os)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);
  
  ConsumerAdminData* data = getData();

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
      msg << "ERROR saving reference to channel of ConsumerAdmin " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }
  
  // Write actual counterProxyPushSupplier for channels
  os << data->counterProxyPushSupplier << endl;

  // Write all about supplierAdminTable: IDs and IORs
  try {
    os << data->proxyPushSuppliers.size() << endl;
    proxyPushSupplierMap::iterator it   = data->proxyPushSuppliers.begin();
    proxyPushSupplierMap::iterator end  = data->proxyPushSuppliers.end();
    while (it != end){
      str_ref = m_orb->object_to_string((*it).second);
      os << (*it).first << endl;
      os << str_ref << endl;
      it++;
    }
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving supplierAdminTable of ConsumerAdmin " << data->_id;
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
      msg << "ERROR saving Filters of ConsumerAdmin " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }


  // Write QoS properties
  try {
    data->qosAdminDelegate->writeObject(os);
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving QoSAdminDelegate of ConsumerAdmin " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

}
