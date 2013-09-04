/*
 *  File name: EventChannelImpl.C
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

#include "EventChannelImpl.h"


TIDNotif::EventChannelImpl::EventChannelImpl(TIDorb::core::TIDORB* orb,
                                   PortableServer::POA_ptr poa,
                                   EventChannelFactoryImpl* factory,
                                   const CosNotification::QoSProperties& initial_qos,
                                   const CosNotification::AdminProperties& initial_admin):
  m_orb(orb), m_channel_poa(poa) 
{

  // Select configuration for consumer and supplier's POA
  m_supplier_POA_config = 
    TIDNotif::util::TIDNotifConfig::getInt(TIDNotif::util::TIDNotifConfig::SUPPLIER_POA_KEY);
  m_consumer_POA_config = 
    TIDNotif::util::TIDNotifConfig::getInt(TIDNotif::util::TIDNotifConfig::CONSUMER_POA_KEY);
  m_channel_POA_config = 
    TIDNotif::util::TIDNotifConfig::getInt(TIDNotif::util::TIDNotifConfig::CHANNEL_POA_KEY);
  
  PortableServer::POAManager_var poa_manager = m_channel_poa->the_POAManager();

  try{

    CORBA::PolicyList policy_list;
    policy_list.length(5);
    policy_list[0] = m_channel_poa->create_id_assignment_policy(PortableServer::USER_ID);
    policy_list[1] = m_channel_poa->create_lifespan_policy (PortableServer::PERSISTENT);
    policy_list[2] = m_channel_poa->create_request_processing_policy(
                                                             PortableServer::USE_DEFAULT_SERVANT);
    policy_list[3] = m_channel_poa->create_servant_retention_policy(PortableServer::RETAIN);
    policy_list[4] = m_channel_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID); 

    m_consumer_admin_poa =
      m_channel_poa->create_POA("ConsumerAdminPOA", poa_manager, policy_list);
    m_supplier_admin_poa =
      m_channel_poa->create_POA("SupplierAdminPOA", poa_manager, policy_list);
    
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "ConsumerAdminPOA & SupplierAdminPOA" << " created"; 
      m_orb->print_trace(TIDorb::util::TR_DEEP_DEBUG, msg.str().data());
    }

  } catch(PortableServer::POA::AdapterAlreadyExists& ex){

    TIDorb::util::StringBuffer msg;
    msg << "ConsumerAdminPOA & SupplierAdminPOA" << " already exists!"; 
    if (m_orb->trace != NULL)
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data(), ex);
    throw CORBA::INTERNAL(msg.str().data());

  }

  CORBA::Object_var obj_cur = orb->resolve_initial_references("POACurrent");
  m_current = PortableServer::Current::_narrow(obj_cur);

  qosProperties       = new CosNotification::QoSProperties(initial_qos);

  CORBA::ULong length = qosProperties->length();

  for (CORBA::ULong i=0; i < length; i++) {

    string name = (*qosProperties)[i].name.in();

    if (name == "ConnectionReliability"){
      CORBA::Short persistent;
      ((*qosProperties)[i].value) >>= persistent;
      if ( persistent == CosNotification::Persistent) {
        m_persistent = true;
        return;
      }
    }
  }

  m_persistent = false;

  // Set default servant only if POA is global
  if (m_consumer_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
    ConsumerAdminImpl* consumer_admin_servant = 
      new ConsumerAdminImpl(m_orb, m_consumer_admin_poa);

    m_consumer_admin_poa->set_servant(consumer_admin_servant);
  }

  if (m_supplier_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
    SupplierAdminImpl* supplier_admin_servant = 
      new SupplierAdminImpl(m_orb, m_supplier_admin_poa);
  
    m_supplier_admin_poa->set_servant(supplier_admin_servant);
  }

}


TIDNotif::EventChannelImpl::~EventChannelImpl()
{

  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "Deleting EventChannelImpl";
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }

  if (qosProperties) 
    delete qosProperties;
  
}


TIDNotif::EventChannelData* TIDNotif::EventChannelImpl::getData()
{
  try {
    PortableServer::ObjectId_var oid = m_current->get_object_id();
    TIDorb::core::poa::OID oid_key(oid);

    EventChannelDataTable::iterator it = _channels.find(oid_key);
    if (it != _channels.end()){
      return (*it).second;
    }
    else {
      throw CORBA::OBJECT_NOT_EXIST();  
    }

  } catch (const CORBA::Exception& ex) {
    throw CORBA::INV_OBJREF();
  }
 
}
  

void TIDNotif::EventChannelImpl::register_channel(
                                          TIDNotif::EventChannelData* data)
{
  TIDorb::util::StringBuffer id_str;
  id_str << "Channel_" << data->m_id;

  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(id_str.str().data());

  TIDorb::core::poa::OID oid_key(oid);

  _channels[oid_key] = data;
}


void TIDNotif::EventChannelImpl::unregister_channel(
                                          TIDNotif::EventChannelData* data)
{
  TIDorb::util::StringBuffer id_str;
  id_str << "Channel_" << data->m_id;

  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(id_str.str().data());

  TIDorb::core::poa::OID oid_key(oid);

  // Destroy POA and POAManager if POA config is LOCAL
  if (m_channel_POA_config == TIDNotif::util::TIDNotifConfig::LOCAL_POA) {
    TIDorb::util::StringBuffer channel_poa_name;
    channel_poa_name << "EventChannelPOA" << data->m_id;
    try {
      PortableServer::POAManager_var channel_poa_manager = 
        m_channel_poa->the_POAManager();
      channel_poa_manager->deactivate(true, false);
      m_channel_poa->destroy(true, false);
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

  EventChannelDataTable::iterator it = _channels.find(oid_key);
  if (it != _channels.end()){
    _channels.erase(it);
    delete data;
  }


}






// NotificationInternals::InternalDistributionChannel 

void TIDNotif::EventChannelImpl::dispatch_event(const CORBA::Any& event)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  EventChannelData* data = getData();

  consumerAdminTable::iterator it  = data->m_consumerAdmins.begin();
  consumerAdminTable::iterator end = data->m_consumerAdmins.end();

  // Legacy comment:
  // Estudiar esto mas detenidamente ya que puede que no sea necesario en
  // la gran mayoria de casos  ????


  while (it != end){

    InternalConsumerAdmin_ptr consumer_admin = (*it).second;

    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "EventChannelImpl::dispatch_event to " << (*it).first;
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }

    consumer_admin->dispatch_event(event); // oneway request
    it++;
  }

}

void TIDNotif::EventChannelImpl::removeSupplierAdmin(CosNotifyChannelAdmin::AdminID id)
{
  EventChannelData* data = getData();

  if (data->m_destroying)
    return;


  {
    TIDThr::Synchronized synchro(m_recursive_mutex);
    
    data->m_supplierAdmins.erase(id);

    if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_CONSUMER_ADMIN,
                                               this);
    }
  }

}

void TIDNotif::EventChannelImpl::removeConsumerAdmin(CosNotifyChannelAdmin::AdminID id)
{
  EventChannelData* data = getData();

  if (data->m_destroying)
    return;


  {
    TIDThr::Synchronized synchro(m_recursive_mutex);

    data->m_consumerAdmins.erase(id);

    if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_CONSUMER_ADMIN,
                                               this);
    }
  }

}

void TIDNotif::EventChannelImpl::loadData(){
  //  cerr << "EventChannelImpl::loadData" << endl;
}


//  CosNotifyFilter::FilterFactory
  
CosNotifyFilter::Filter* 
TIDNotif::EventChannelImpl::create_filter(const char* constraint_grammar)
  throw (CosNotifyFilter::InvalidGrammar)
{
  EventChannelData* data = getData();
  return data->filterFactoryDelegate->create_filter(constraint_grammar);
}

CosNotifyFilter::MappingFilter* 
TIDNotif::EventChannelImpl::create_mapping_filter(const char* constraint_grammar, 
                                        const CORBA::Any& default_value)
  throw (CosNotifyFilter::InvalidGrammar)
{
  EventChannelData* data = getData();
  return data->filterFactoryDelegate->create_mapping_filter(constraint_grammar, 
                                                            default_value);
}
  

// CosNotifyChannelAdmin::EventChannel 
// readonly atributes


CosNotifyChannelAdmin::EventChannelFactory_ptr 
TIDNotif::EventChannelImpl::MyFactory()
{
  EventChannelData* data = getData();
  return CosNotifyChannelAdmin::EventChannelFactory::_duplicate(data->m_MyFactory);
}


CosNotifyChannelAdmin::ConsumerAdmin_ptr 
TIDNotif::EventChannelImpl::default_consumer_admin()
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  EventChannelData* data = getData();

  CosNotifyChannelAdmin::AdminID id = 0;

  if (data->m_default_consumer_admin == NULL){

    // Get channel POA in order with configuration
    // TODO: refactor this block int ThePOAFactory
    PortableServer::POA_var consumer_admin_poa;
    if (m_consumer_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
      if (m_orb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "Using Global POA for ConsumerAdmin " << id; 
        m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
      }
      consumer_admin_poa = m_consumer_admin_poa;
    } else { // Local
      if (m_orb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "Creating Local POA for ConsumerAdmin " << id; 
        m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
      }
      TIDorb::util::StringBuffer consumer_admin_poa_name;
      consumer_admin_poa_name << "ConsumerAdminPOA" << id;
      CORBA::PolicyList policy_list;
      policy_list.length(5);
      policy_list[0] = m_consumer_admin_poa->create_id_assignment_policy(PortableServer::USER_ID);
      policy_list[1] = m_consumer_admin_poa->create_lifespan_policy (PortableServer::PERSISTENT);
      policy_list[2] = m_consumer_admin_poa->create_request_processing_policy(
                                                         PortableServer::USE_DEFAULT_SERVANT);
      policy_list[3] = m_consumer_admin_poa->create_servant_retention_policy(PortableServer::RETAIN);
      policy_list[4] = m_consumer_admin_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
      consumer_admin_poa = 
        m_consumer_admin_poa->create_POA(consumer_admin_poa_name.str().data(), NULL, policy_list);
      
      PortableServer::POAManager_var consumer_admin_poa_mgr = 
        consumer_admin_poa->the_POAManager();
      
      TIDNotif::ConsumerAdminImpl* consumer_servant;
      consumer_servant = new TIDNotif::ConsumerAdminImpl(m_orb, consumer_admin_poa); 

      consumer_admin_poa->set_servant(consumer_servant);
      
      consumer_admin_poa_mgr->activate();
    }


    ConsumerAdminData* default_consumer_admin_data = 
      new ConsumerAdminData(m_orb, m_consumer_admin_poa, id, data->m_id, AND_OP);

    TIDNotif::ConsumerAdminImpl* consumer_admin_impl = 
      dynamic_cast < TIDNotif::ConsumerAdminImpl* > (consumer_admin_poa->get_servant());

    consumer_admin_impl->register_admin(default_consumer_admin_data);

    // Activate default_consumer_admin
    TIDorb::util::StringBuffer str_id;
    str_id << "ConsumerAdmin_" << data->m_id  << "_" << id;

    PortableServer::ObjectId_var oid = 
      PortableServer::string_to_ObjectId(str_id.str().data());

    CORBA::Object_var object = 
      consumer_admin_poa->create_reference_with_id(oid, 
                                              _InternalConsumerAdminHelper::id());
    data->m_default_consumer_admin = 
      NotificationInternals::InternalConsumerAdmin::_narrow(object);   
    data->m_consumerAdmins[id] = data->m_default_consumer_admin;

    if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_CONSUMER_ADMIN,
                                               this);
    }
  }
  return CosNotifyChannelAdmin::ConsumerAdmin::_narrow(data->m_default_consumer_admin);
}


CosNotifyChannelAdmin::SupplierAdmin_ptr 
TIDNotif::EventChannelImpl::default_supplier_admin()
{
  TIDThr::Synchronized synchro(m_recursive_mutex);
    
  EventChannelData* data = getData();

  CosNotifyChannelAdmin::AdminID id = 0;

  if (data->m_default_supplier_admin == NULL){

    // Get channel POA in order with configuration
    // TODO: refactor this block int ThePOAFactory
    PortableServer::POA_var supplier_admin_poa;
    if (m_supplier_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
      if (m_orb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "Using Global POA for SupplierAdmin " << id; 
        m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
      }
      supplier_admin_poa = m_supplier_admin_poa;
    } else { // Local
      if (m_orb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "Creating Local POA for SupplierAdmin " << id; 
        m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
      }
      TIDorb::util::StringBuffer supplier_admin_poa_name;
      supplier_admin_poa_name << "SupplierAdminPOA" << id;
      CORBA::PolicyList policy_list;
      policy_list.length(5);
      policy_list[0] = m_supplier_admin_poa->create_id_assignment_policy(PortableServer::USER_ID);
      policy_list[1] = m_supplier_admin_poa->create_lifespan_policy (PortableServer::PERSISTENT);
      policy_list[2] = m_supplier_admin_poa->create_request_processing_policy(
                                                         PortableServer::USE_DEFAULT_SERVANT);
      policy_list[3] = m_supplier_admin_poa->create_servant_retention_policy(PortableServer::RETAIN);
      policy_list[4] = m_supplier_admin_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
      supplier_admin_poa = 
        m_supplier_admin_poa->create_POA(supplier_admin_poa_name.str().data(), NULL, policy_list);
      
      PortableServer::POAManager_var supplier_admin_poa_mgr = 
        supplier_admin_poa->the_POAManager();
      
      TIDNotif::SupplierAdminImpl* supplier_servant;
      supplier_servant = new TIDNotif::SupplierAdminImpl(m_orb, supplier_admin_poa); 

      supplier_admin_poa->set_servant(supplier_servant);
      
      supplier_admin_poa_mgr->activate();
    }

    SupplierAdminData* default_supplier_admin_data = 
      new SupplierAdminData(m_orb, m_supplier_admin_poa, id, data->m_id /*this*/, AND_OP);

    TIDNotif::SupplierAdminImpl* supplier_admin_impl = 
      dynamic_cast < TIDNotif::SupplierAdminImpl* > (supplier_admin_poa->get_servant());

    supplier_admin_impl->register_admin(default_supplier_admin_data);

    // Activate default_supplier_admin
    TIDorb::util::StringBuffer str_id;
    str_id << "SupplierAdmin_" << data->m_id  << "_" << id;
    
    PortableServer::ObjectId_var oid = 
      PortableServer::string_to_ObjectId(str_id.str().data());
    
    CORBA::Object_var object = 
      supplier_admin_poa->create_reference_with_id(oid, 
                                           _InternalSupplierAdminHelper::id());
    data->m_default_supplier_admin = 
      NotificationInternals::InternalSupplierAdmin::_narrow(object);

    data->m_supplierAdmins[id] = data->m_default_supplier_admin;
    
    if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_SUPPLIER_ADMIN,
                                               this);
    }
  }

  return CosNotifyChannelAdmin::SupplierAdmin::_narrow(data->m_default_supplier_admin);
}


CosNotifyFilter::FilterFactory_ptr 
TIDNotif::EventChannelImpl::default_filter_factory()
{
  EventChannelData* data = getData();

  TIDorb::util::StringBuffer id_str;
  id_str << "Channel_" << data->m_id;

  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(id_str.str().data());

  CORBA::Object_var obj = 
    m_channel_poa->create_reference_with_id(oid, 
                                _InternalDistributionChannelHelper::id());
  CosNotifyFilter::FilterFactory_ptr filter_factory_ref = 
    CosNotifyFilter::FilterFactory::_narrow(obj);

  return filter_factory_ref;
}

		
CosNotifyChannelAdmin::ConsumerAdmin_ptr 
TIDNotif::EventChannelImpl::new_for_consumers(
                                    CosNotifyChannelAdmin::InterFilterGroupOperator op, 
                                    CosNotifyChannelAdmin::AdminID& id)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);
  
  EventChannelData* data = getData();

  // Create a new ConsumerAdmin
  id = data->counterConsumerAdminID++;

  // Get channel POA in order with configuration
  // TODO: refactor this block int ThePOAFactory
  PortableServer::POA_var consumer_admin_poa;
  if (m_consumer_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Using Global POA for ConsumerAdmin " << id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    consumer_admin_poa = m_consumer_admin_poa;
  } else { // Local
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Creating Local POA for ConsumerAdmin " << id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    TIDorb::util::StringBuffer consumer_admin_poa_name;
    consumer_admin_poa_name << "ConsumerAdminPOA" << id;
    CORBA::PolicyList policy_list;
    policy_list.length(5);
    policy_list[0] = m_consumer_admin_poa->create_id_assignment_policy(PortableServer::USER_ID);
    policy_list[1] = m_consumer_admin_poa->create_lifespan_policy (PortableServer::PERSISTENT);
    policy_list[2] = m_consumer_admin_poa->create_request_processing_policy(
                                                     PortableServer::USE_DEFAULT_SERVANT);
    policy_list[3] = m_consumer_admin_poa->create_servant_retention_policy(PortableServer::RETAIN);
    policy_list[4] = m_consumer_admin_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
    consumer_admin_poa = 
      m_consumer_admin_poa->create_POA(consumer_admin_poa_name.str().data(), NULL, policy_list);
    
    PortableServer::POAManager_var consumer_admin_poa_mgr = 
      consumer_admin_poa->the_POAManager();
    
    TIDNotif::ConsumerAdminImpl* consumer_servant;
    consumer_servant = new TIDNotif::ConsumerAdminImpl(m_orb, consumer_admin_poa); 
    
    consumer_admin_poa->set_servant(consumer_servant);
      
    consumer_admin_poa_mgr->activate();
  }

  ConsumerAdminData* consumer_admin_data = 
    new ConsumerAdminData(m_orb, m_consumer_admin_poa, id, data->m_id, AND_OP);
  
  TIDNotif::ConsumerAdminImpl* consumer_admin_impl = 
    dynamic_cast < TIDNotif::ConsumerAdminImpl* > (consumer_admin_poa->get_servant());

  consumer_admin_impl->register_admin(consumer_admin_data);

  // Activate the new ConsumerAdmin
  TIDorb::util::StringBuffer str_id;
  str_id << "ConsumerAdmin_" << data->m_id  << "_" << id;
  
  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(str_id.str().data());
  
  CORBA::Object_var object = 
    consumer_admin_poa->create_reference_with_id(oid, 
                                         _InternalConsumerAdminHelper::id());
  NotificationInternals::InternalConsumerAdmin_ptr consumer_admin_ptr = 
    NotificationInternals::InternalConsumerAdmin::_narrow(object);


  // Add into table
  data->m_consumerAdmins[id] = consumer_admin_ptr;

  if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_CONSUMER_ADMIN,
                                               this);
  }

  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "New ConsumerAdmin created with id " << id; 
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }

  // Return the reference
  return CosNotifyChannelAdmin::ConsumerAdmin::_narrow(consumer_admin_ptr);
}

		
CosNotifyChannelAdmin::SupplierAdmin_ptr 
TIDNotif::EventChannelImpl::new_for_suppliers(
                                    CosNotifyChannelAdmin::InterFilterGroupOperator op, 
                                    CosNotifyChannelAdmin::AdminID& id)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  EventChannelData* data = getData();

  // Create a new SupplierAdmin
  id = data->counterSupplierAdminID++;

  // Get channel POA in order with configuration
  // TODO: refactor this block int ThePOAFactory
  PortableServer::POA_var supplier_admin_poa;
  if (m_supplier_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Using Global POA for SupplierAdmin " << id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    supplier_admin_poa = m_supplier_admin_poa;
  } else { // Local
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Creating Local POA for SupplierAdmin " << id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    TIDorb::util::StringBuffer supplier_admin_poa_name;
    supplier_admin_poa_name << "SupplierAdminPOA" << id;
    CORBA::PolicyList policy_list;
    policy_list.length(5);
    policy_list[0] = m_supplier_admin_poa->create_id_assignment_policy(PortableServer::USER_ID);
    policy_list[1] = m_supplier_admin_poa->create_lifespan_policy (PortableServer::PERSISTENT);
    policy_list[2] = m_supplier_admin_poa->create_request_processing_policy(
                                                                            PortableServer::USE_DEFAULT_SERVANT);
    policy_list[3] = m_supplier_admin_poa->create_servant_retention_policy(PortableServer::RETAIN);
    policy_list[4] = m_supplier_admin_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
    supplier_admin_poa = 
      m_supplier_admin_poa->create_POA(supplier_admin_poa_name.str().data(), NULL, policy_list);
    
    PortableServer::POAManager_var supplier_admin_poa_mgr = 
      supplier_admin_poa->the_POAManager();
    
    TIDNotif::SupplierAdminImpl* supplier_servant;
    supplier_servant = new TIDNotif::SupplierAdminImpl(m_orb, supplier_admin_poa); 
    
    supplier_admin_poa->set_servant(supplier_servant);
    
    supplier_admin_poa_mgr->activate();
  }
  
  SupplierAdminData* supplier_admin_data = 
    new SupplierAdminData(m_orb, m_supplier_admin_poa, id, data->m_id, AND_OP);
  
  TIDNotif::SupplierAdminImpl* supplier_admin_impl = 
    dynamic_cast < TIDNotif::SupplierAdminImpl* > (supplier_admin_poa->get_servant());
  
  supplier_admin_impl->register_admin(supplier_admin_data);


  // Activate the new SupplierAdmin
  TIDorb::util::StringBuffer str_id;
  str_id << "SupplierAdmin_" <<  data->m_id  << "_" << id;
  
  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(str_id.str().data());
  
  CORBA::Object_var object = 
    supplier_admin_poa->create_reference_with_id(oid, 
                                          _InternalSupplierAdminHelper::id());
  NotificationInternals::InternalSupplierAdmin_ptr supplier_admin_ptr =
     NotificationInternals::InternalSupplierAdmin::_narrow(object);


  // Add into table
  data->m_supplierAdmins[id] = supplier_admin_ptr;

  if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_SUPPLIER_ADMIN,
                                               this);
  }

  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "New SupplierAdmin created with id " << id; 
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }
  // Return the reference
  return CosNotifyChannelAdmin::SupplierAdmin::_narrow(supplier_admin_ptr);

}

		
CosNotifyChannelAdmin::ConsumerAdmin_ptr 
TIDNotif::EventChannelImpl::get_consumeradmin(CosNotifyChannelAdmin::AdminID id)
  throw (CosNotifyChannelAdmin::AdminNotFound)
{
  EventChannelData* data = getData();

  consumerAdminTable::iterator it = data->m_consumerAdmins.find(id);
  if (it != data->m_consumerAdmins.end()){
    return ConsumerAdmin::_duplicate((*it).second);
  }
  else
    throw CosNotifyChannelAdmin::AdminNotFound();
}

		
CosNotifyChannelAdmin::SupplierAdmin_ptr 
TIDNotif::EventChannelImpl::get_supplieradmin(CosNotifyChannelAdmin::AdminID id)
  throw (CosNotifyChannelAdmin::AdminNotFound)
{
  EventChannelData* data = getData();

  supplierAdminTable::iterator it = data->m_supplierAdmins.find(id);
  if (it != data->m_supplierAdmins.end()){
    return SupplierAdmin::_duplicate((*it).second);
  }
  else
    throw CosNotifyChannelAdmin::AdminNotFound();
}
		

CosNotifyChannelAdmin::AdminIDSeq* 
TIDNotif::EventChannelImpl::get_all_consumeradmins()
{
  EventChannelData* data = getData();

  consumerAdminTable::iterator it = data->m_consumerAdmins.begin();
  consumerAdminTable::iterator end = data->m_consumerAdmins.end();

  AdminIDSeq* seq = new AdminIDSeq;
  seq->length(data->m_consumerAdmins.size());
  int i = 0;
  while (it != end){
    (*seq)[i]=(*it).first;
    it++;
    i++;
  }
  return seq;
}
		

CosNotifyChannelAdmin::AdminIDSeq* 
TIDNotif::EventChannelImpl::get_all_supplieradmins()
{
  EventChannelData* data = getData();

  supplierAdminTable::iterator it = data->m_supplierAdmins.begin();
  supplierAdminTable::iterator end = data->m_supplierAdmins.end();

  AdminIDSeq* seq = new AdminIDSeq;
  seq->length(data->m_supplierAdmins.size());
  int i = 0;
  while (it != end){
    (*seq)[i]=(*it).first;
    it++;
    i++;
  }
  return seq;
}


// CosEvent::EventChanels operations

CosNotifyChannelAdmin::ConsumerAdmin_ptr 
TIDNotif::EventChannelImpl::for_consumers()
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  EventChannelData* data = getData();

  CosNotifyChannelAdmin::AdminID id = 0;

  if (data->m_default_consumer_admin == NULL){

    // Get channel POA in order with configuration
    // TODO: refactor this block int ThePOAFactory
    PortableServer::POA_var consumer_admin_poa;
    if (m_consumer_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
      if (m_orb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "Using Global POA for ConsumerAdmin " << id; 
        m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
      }
      consumer_admin_poa = m_consumer_admin_poa;
    } else { // Local
      if (m_orb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "Creating Local POA for ConsumerAdmin " << id; 
        m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
      }
      TIDorb::util::StringBuffer consumer_admin_poa_name;
      consumer_admin_poa_name << "ConsumerAdminPOA" << id;
      CORBA::PolicyList policy_list;
      policy_list.length(5);
      policy_list[0] = m_consumer_admin_poa->create_id_assignment_policy(PortableServer::USER_ID);
      policy_list[1] = m_consumer_admin_poa->create_lifespan_policy (PortableServer::PERSISTENT);
      policy_list[2] = m_consumer_admin_poa->create_request_processing_policy(
                                                         PortableServer::USE_DEFAULT_SERVANT);
      policy_list[3] = m_consumer_admin_poa->create_servant_retention_policy(PortableServer::RETAIN);
      policy_list[4] = m_consumer_admin_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
      consumer_admin_poa = 
        m_consumer_admin_poa->create_POA(consumer_admin_poa_name.str().data(), NULL, policy_list);
      
      PortableServer::POAManager_var consumer_admin_poa_mgr = 
        consumer_admin_poa->the_POAManager();
      
      TIDNotif::ConsumerAdminImpl* consumer_servant;
      consumer_servant = new TIDNotif::ConsumerAdminImpl(m_orb, consumer_admin_poa); 

      consumer_admin_poa->set_servant(consumer_servant);
      
      consumer_admin_poa_mgr->activate();
    }

    ConsumerAdminData* default_consumer_admin_data = 
      new ConsumerAdminData(m_orb, m_consumer_admin_poa, id, data->m_id, AND_OP);
    
    TIDNotif::ConsumerAdminImpl* consumer_admin_impl = 
      dynamic_cast < TIDNotif::ConsumerAdminImpl* > (consumer_admin_poa->get_servant());

    consumer_admin_impl->register_admin(default_consumer_admin_data);

    // Activate ConsumerAdmin
    TIDorb::util::StringBuffer str_id;
    str_id << "ConsumerAdmin_" << data->m_id << "_" << id;
    
    PortableServer::ObjectId_var oid = 
      PortableServer::string_to_ObjectId(str_id.str().data());
    
    CORBA::Object_var object = 
      consumer_admin_poa->create_reference_with_id(oid, 
                                         _InternalConsumerAdminHelper::id());
    data->m_default_consumer_admin = 
      NotificationInternals::InternalConsumerAdmin::_narrow(object);

    data->m_consumerAdmins[id] = data->m_default_consumer_admin;

    if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_CONSUMER_ADMIN,
                                               this);
    }
  }

  return CosNotifyChannelAdmin::ConsumerAdmin::_duplicate(data->m_default_consumer_admin);
}


CosNotifyChannelAdmin::SupplierAdmin_ptr 
TIDNotif::EventChannelImpl::for_suppliers()
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  EventChannelData* data = getData();

  CosNotifyChannelAdmin::AdminID id = 0;

  if (data->m_default_supplier_admin == NULL){

    // Get channel POA in order with configuration
    // TODO: refactor this block int ThePOAFactory
    PortableServer::POA_var supplier_admin_poa;
    if (m_supplier_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
      if (m_orb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "Using Global POA for SupplierAdmin " << id; 
        m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
      }
      supplier_admin_poa = m_supplier_admin_poa;
    } else { // Local
      if (m_orb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "Creating Local POA for SupplierAdmin " << id; 
        m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
      }
      TIDorb::util::StringBuffer supplier_admin_poa_name;
      supplier_admin_poa_name << "SupplierAdminPOA" << id;
      CORBA::PolicyList policy_list;
      policy_list.length(5);
      policy_list[0] = m_supplier_admin_poa->create_id_assignment_policy(PortableServer::USER_ID);
      policy_list[1] = m_supplier_admin_poa->create_lifespan_policy (PortableServer::PERSISTENT);
      policy_list[2] = m_supplier_admin_poa->create_request_processing_policy(
                                                   PortableServer::USE_DEFAULT_SERVANT);
      policy_list[3] = m_supplier_admin_poa->create_servant_retention_policy(PortableServer::RETAIN);
      policy_list[4] = m_supplier_admin_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
      supplier_admin_poa = 
        m_supplier_admin_poa->create_POA(supplier_admin_poa_name.str().data(), NULL, policy_list);
      
      PortableServer::POAManager_var supplier_admin_poa_mgr = 
        supplier_admin_poa->the_POAManager();
      
      TIDNotif::SupplierAdminImpl* supplier_servant;
      supplier_servant = new TIDNotif::SupplierAdminImpl(m_orb, supplier_admin_poa); 
      
      supplier_admin_poa->set_servant(supplier_servant);
      
      supplier_admin_poa_mgr->activate();
    }

    SupplierAdminData* default_supplier_admin_data = 
      new SupplierAdminData(m_orb, m_supplier_admin_poa, id, data->m_id, AND_OP);
    
    TIDNotif::SupplierAdminImpl* supplier_admin_impl = 
      dynamic_cast < TIDNotif::SupplierAdminImpl* > (supplier_admin_poa->get_servant());
    
    supplier_admin_impl->register_admin(default_supplier_admin_data);

    // Activate SupplierAdmin
    TIDorb::util::StringBuffer str_id;
    str_id << "SupplierAdmin_" << data->m_id << "_" << id;
    
    PortableServer::ObjectId_var oid = 
      PortableServer::string_to_ObjectId(str_id.str().data());
    
    CORBA::Object_var object = 
      supplier_admin_poa->create_reference_with_id(oid, 
                                          _InternalSupplierAdminHelper::id());
    data->m_default_supplier_admin = 
      NotificationInternals::InternalSupplierAdmin::_narrow(object);

    data->m_supplierAdmins[id] = data->m_default_supplier_admin;

    if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_SUPPLIER_ADMIN,
                                               this);
    }

  }

  return CosNotifyChannelAdmin::SupplierAdmin::_duplicate(data->m_default_supplier_admin);
}


CosNotifyChannelAdmin::ChannelID TIDNotif::EventChannelImpl::get_channelID (){
  EventChannelData* data = getData();
  return data->m_id;
}

void TIDNotif::EventChannelImpl::destroy()
{
  EventChannelData* data = getData();

  if (data->m_destroying)
    return;

  data->m_destroying = true;

  {
    TIDThr::Synchronized synchro(m_recursive_mutex);

    {  // Disconnect ConsumerAdmin
      consumerAdminTable::iterator it  = data->m_consumerAdmins.begin();
      consumerAdminTable::iterator end = data->m_consumerAdmins.end();
      
      while (it != end){
        InternalConsumerAdmin_ptr consumer_admin = (*it).second;
        if (m_orb->trace != NULL){
          TIDorb::util::StringBuffer msg;
          msg << "EventChannelImpl::destroy call for destroy ConsumerAdmin with id ";
          msg << (*it).first;
          m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
        }
        consumer_admin->destroyFromChannel();
        it++;
      }
    }
    
    {  // Disconnect SupplierAdmin
      supplierAdminTable::iterator it  = data->m_supplierAdmins.begin();
      supplierAdminTable::iterator end = data->m_supplierAdmins.end();
      
      while (it != end){
        InternalSupplierAdmin_ptr supplier_admin = (*it).second;
        if (m_orb->trace != NULL){
          TIDorb::util::StringBuffer msg;
          msg << "EventChannelImpl::destroyChannel call to destroy SupplierAdmin with id ";
          msg << (*it).first;
          m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
        }
        supplier_admin->destroyFromChannel();
        it++;
      }
      
    }

    if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->delete_data(this);
    }  //TODO_MORFEO: delete_data or update_data
    

  } // TIDThr::Synchronized


  // Unregister channel...
  this->unregister_channel(data);

  // ¿Notificar la destruccion a la factoria de canales de eventos?
  // -> El estandar no lo contempla.

}


// CosNotification::AdminPropertiesAdmin operations

CosNotification::AdminProperties* TIDNotif::EventChannelImpl::get_admin()
{
  CosNotification::AdminProperties* seq = new CosNotification::AdminProperties;
  seq->length(1);
  (*seq)[0].name = CORBA::string_dup("MaxQueueLength");
  (*seq)[0].value <<= (CORBA::Long) m_orb->conf().poa_max_queued_requests;
//   (*seq)[1].name = CORBA::string_dup("MaxConsumers");
//   (*seq)[1].value <<= (CORBA::Long) 0;
//   (*seq)[2].name = CORBA::string_dup("MaxSuppliers");
//   (*seq)[2].value <<= (CORBA::Long) 0;
  return seq;
}

void TIDNotif::EventChannelImpl::set_admin(
                               const CosNotification::AdminProperties& admin)
  throw (CosNotification::UnsupportedAdmin)
{
  throw CosNotification::UnsupportedAdmin();
}



// CosNotification::QoSAdmin operations

CosNotification::QoSProperties* TIDNotif::EventChannelImpl::get_qos()
{
  EventChannelData* data = getData();
  return data->qosAdminDelegate->get_qos();
}


void TIDNotif::EventChannelImpl::set_qos(
                                    const CosNotification::QoSProperties& qos)
  throw (CosNotification::UnsupportedQoS)
{
  EventChannelData* data = getData();
  try{
    data->qosAdminDelegate->set_qos(qos);
  }
  catch(const CosNotification::UnsupportedQoS& ex){
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "EventChannelImpl::set_qos: QoSProperties not supported";
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data(), ex);
    }
    throw;
  }

  CORBA::PolicyList* policies = 
    data->qosAdminDelegate->getPolicies();
  

//   // Obtain reference to channel
//   CORBA::Object_var obj = m_factory_poa->servant_to_reference(this);  
//   NotificationInternals::InternalDistributionChannel_var channel_ref = 
//     NotificationInternals::InternalDistributionChannel::_narrow(obj);


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

  TIDNotif::qos::QueueOrderProperty* order_property = 
    data->qosAdminDelegate->getQueueOrderProperty();
  
  if(order_property != NULL) {
    //TODO: Tuning POA with related QoS properties
    //if (this._channel_poa_policy == 0) { //global POA
      PortableServer::POAManager_ptr manager = m_channel_poa->the_POAManager();
      TIDorb::core::poa::POAManagerImpl* manager_impl = 
        dynamic_cast < TIDorb::core::poa::POAManagerImpl* > (manager);
      manager_impl->set_queue_order(order_property->getPolicy(m_orb)->allowed_orders());
      // }
    // if
  }

}


void TIDNotif::EventChannelImpl::validate_qos(
                        const CosNotification::QoSProperties& required_qos, 
                        CosNotification::NamedPropertyRangeSeq*& available_qos)
  throw (CosNotification::UnsupportedQoS)
{
  EventChannelData* data = getData();
  data->qosAdminDelegate->validate_qos(required_qos, available_qos);
}




// Persistence Management

void TIDNotif::EventChannelImpl::readObject(istream & is)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);
  
  EventChannelData* data = 
    new TIDNotif::EventChannelData(m_orb, m_channel_poa, 0, NULL);

  // Read ChannelID
  is >> data->m_id;

  // Read reference to event channel factory
  try {
    string str_ref;
    is >> str_ref;
    CORBA::Object_var object = m_orb->string_to_object(str_ref.c_str());
    data->m_MyFactory = CosNotifyChannelAdmin::EventChannelFactory::_narrow(object);
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering EventChannelFactory of EventChannel " << data->m_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  PortableServer::ObjectId_var oid;
  // Read actual counterConsumerAdminID for channels
  is >> data->counterConsumerAdminID;

  // Read all about consumerAdminTable: IDs and IORs
  try {
    CORBA::Long m_consumerAdmins_size;
    is >> m_consumerAdmins_size;
    ConsumerAdminData* admin_data;
    for (int i = 0; i < m_consumerAdmins_size; i++){
      ChannelID id;
      string str_ref;
      is >> id;


      // Get channel POA in order with configuration
      // TODO: refactor this block int ThePOAFactory
      PortableServer::POA_var consumer_admin_poa;
      if (m_consumer_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
        if (m_orb->trace != NULL){
          TIDorb::util::StringBuffer msg;
          msg << "Using Global POA for ConsumerAdmin " << id; 
          m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
        }
        consumer_admin_poa = m_consumer_admin_poa;
      } else { // Local
        if (m_orb->trace != NULL){
          TIDorb::util::StringBuffer msg;
          msg << "Creating Local POA for ConsumerAdmin " << id; 
        m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
        }
        TIDorb::util::StringBuffer consumer_admin_poa_name;
        consumer_admin_poa_name << "ConsumerAdminPOA" << id;
        CORBA::PolicyList policy_list;
        policy_list.length(5);
        policy_list[0] = m_consumer_admin_poa->create_id_assignment_policy(PortableServer::USER_ID);
        policy_list[1] = m_consumer_admin_poa->create_lifespan_policy (PortableServer::PERSISTENT);
        policy_list[2] = m_consumer_admin_poa->create_request_processing_policy(
                                                             PortableServer::USE_DEFAULT_SERVANT);
        policy_list[3] = m_consumer_admin_poa->create_servant_retention_policy(PortableServer::RETAIN);
        policy_list[4] = m_consumer_admin_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
        consumer_admin_poa = 
          m_consumer_admin_poa->create_POA(consumer_admin_poa_name.str().data(), NULL, policy_list);
        
        PortableServer::POAManager_var consumer_admin_poa_mgr = 
          consumer_admin_poa->the_POAManager();
      
        TIDNotif::ConsumerAdminImpl* consumer_servant;
        consumer_servant = new TIDNotif::ConsumerAdminImpl(m_orb, consumer_admin_poa); 
        
        consumer_admin_poa->set_servant(consumer_servant);
        
        consumer_admin_poa_mgr->activate();
      }

      admin_data = new ConsumerAdminData(m_orb, m_consumer_admin_poa, id, 
                                         data->m_id, AND_OP);

      TIDNotif::ConsumerAdminImpl* consumer_admin_impl = 
        dynamic_cast < TIDNotif::ConsumerAdminImpl* > (consumer_admin_poa->get_servant());
      
      consumer_admin_impl->register_admin(admin_data);

      is >> str_ref;

      TIDorb::util::StringBuffer str_id;
      str_id << "ConsumerAdmin_" << data->m_id << "_" << id;
      oid = PortableServer::string_to_ObjectId(str_id.str().data());
      
      if (PersistenceManager::getDB()->data_saved(consumer_admin_impl))
        PersistenceManager::getDB()->load_ca(consumer_admin_impl);

      CORBA::Object_var object =
        consumer_admin_poa->create_reference_with_id(oid, 
                                            _InternalConsumerAdminHelper::id());
      NotificationInternals::InternalConsumerAdmin_ptr ref;
      ref = NotificationInternals::InternalConsumerAdmin::_narrow(object);
      data->m_consumerAdmins[id] = ref;

      if (id == 0)
        data->m_default_consumer_admin = ref;
    }
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering ConsumerAdminTable of EventChannel " << data->m_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Read current counterSupplierAdminID for channels
  is >> data->counterSupplierAdminID;

  // Read all about supplierAdminTable: IDs and IORs
  try {
    CORBA::Long m_supplierAdmins_size;
    is >> m_supplierAdmins_size;

    SupplierAdminData* admin_data; 
    for (int i = 0; i < m_supplierAdmins_size; i++){
      ChannelID id;
      string str_ref;
      is >> id;


      // Get channel POA in order with configuration
      // TODO: refactor this block int ThePOAFactory
      PortableServer::POA_var supplier_admin_poa;
      if (m_supplier_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
        if (m_orb->trace != NULL){
          TIDorb::util::StringBuffer msg;
          msg << "Using Global POA for SupplierAdmin " << id; 
          m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
        }
        supplier_admin_poa = m_supplier_admin_poa;
      } else { // Local
        if (m_orb->trace != NULL){
          TIDorb::util::StringBuffer msg;
          msg << "Creating Local POA for SupplierAdmin " << id; 
          m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
        }
        TIDorb::util::StringBuffer supplier_admin_poa_name;
        supplier_admin_poa_name << "SupplierAdminPOA" << id;
        CORBA::PolicyList policy_list;
        policy_list.length(5);
        policy_list[0] = m_supplier_admin_poa->create_id_assignment_policy(PortableServer::USER_ID);
        policy_list[1] = m_supplier_admin_poa->create_lifespan_policy (PortableServer::PERSISTENT);
        policy_list[2] = m_supplier_admin_poa->create_request_processing_policy(
                                                            PortableServer::USE_DEFAULT_SERVANT);
        policy_list[3] = m_supplier_admin_poa->create_servant_retention_policy(PortableServer::RETAIN);
        policy_list[4] = m_supplier_admin_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
        supplier_admin_poa = 
          m_supplier_admin_poa->create_POA(supplier_admin_poa_name.str().data(), NULL, policy_list);
        
        PortableServer::POAManager_var supplier_admin_poa_mgr = 
          supplier_admin_poa->the_POAManager();
        
        TIDNotif::SupplierAdminImpl* supplier_servant;
        supplier_servant = new TIDNotif::SupplierAdminImpl(m_orb, supplier_admin_poa); 
        
        supplier_admin_poa->set_servant(supplier_servant);
        
        supplier_admin_poa_mgr->activate();
      }
      
      admin_data = new SupplierAdminData(m_orb, m_supplier_admin_poa, id, 
                                         data->m_id, AND_OP);
      
      TIDNotif::SupplierAdminImpl* supplier_admin_impl = 
        dynamic_cast < TIDNotif::SupplierAdminImpl* > (supplier_admin_poa->get_servant());

      supplier_admin_impl->register_admin(admin_data);

      is >> str_ref;

      TIDorb::util::StringBuffer str_id;
      str_id << "SupplierAdmin_" << data->m_id << "_" << id;

      oid = PortableServer::string_to_ObjectId(str_id.str().data());
      
      if (PersistenceManager::getDB()->data_saved(supplier_admin_impl))
        PersistenceManager::getDB()->load_sa(supplier_admin_impl);
      
      CORBA::Object_var object =
        supplier_admin_poa->create_reference_with_id(oid, 
                                           _InternalSupplierAdminHelper::id());
      NotificationInternals::InternalSupplierAdmin_ptr ref;
      ref = NotificationInternals::InternalSupplierAdmin::_narrow(object);
      data->m_supplierAdmins[id] = ref;

      if (id == 0)
        data->m_default_supplier_admin = ref;
    }
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering SupplierAdminTable of EventChannel " << data->m_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Read m_destroying flag
  is >> data->m_destroying;

  // Read QoS properties
  try {

    data->qosAdminDelegate = new TIDNotif::qos::ChannelQoSAdmin(m_orb);
    data->qosAdminDelegate->readObject(is);

  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering QoSAdminDelegate of EventChannel " << data->m_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }
  

  this->register_channel(data);

  //  TODO:
  //  ¿ Donde se lee y guarda esta informacion asociada al canal ?
  //  FilterFactoryImpl*

}


void TIDNotif::EventChannelImpl::writeObject(ostream & os)
{

  TIDThr::Synchronized synchro(m_recursive_mutex);
  
  EventChannelData* data = getData();

  // Write id channel
  os << data->m_id << endl;
  
  CORBA::String_var str_ref; 
  
  // Write reference to event channel factory
  try {
    str_ref = m_orb->object_to_string(data->m_MyFactory);
    os << str_ref << endl;
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving EventChannelFactory of EventChannel " << data->m_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }
  
  // Write actual counterConsumerAdminID for channels
  os << data->counterConsumerAdminID << endl;
  
  // Write all about consumerAdminTable: IDs and IORs
  try {
    os << (CORBA::Long)data->m_consumerAdmins.size() << endl;
    consumerAdminTable::iterator it   = data->m_consumerAdmins.begin();
    consumerAdminTable::iterator end  = data->m_consumerAdmins.end();
    while (it != end){
      str_ref = m_orb->object_to_string((*it).second);
      os << (*it).first << endl;
      os << str_ref << endl;
      it++;
    }
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving ConsumerAdminTable of EventChannel " << data->m_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }
  
  
  // Write actual counterSupplierAdminID for channels
  os << data->counterSupplierAdminID << endl;
  
  // Write all about supplierAdminTable: IDs and IORs
  try {
    os << (CORBA::Long)data->m_supplierAdmins.size() << endl;
    supplierAdminTable::iterator it2   = data->m_supplierAdmins.begin();
    supplierAdminTable::iterator end2  = data->m_supplierAdmins.end();
    while (it2 != end2){
      str_ref = m_orb->object_to_string((*it2).second);
      os << (*it2).first << endl;
      os << str_ref << endl;
      it2++;
    } 
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving SupplierAdminTable of EventChannel " << data->m_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }
  
  // Write m_destroying flag
  os << data->m_destroying << endl;
  
  // Write QoS properties
  try {
    data->qosAdminDelegate->writeObject(os);
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving QoSAdminDelegate of EventChannel " << data->m_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }
  
}
