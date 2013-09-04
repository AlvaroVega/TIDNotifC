/*
 *  File name: ProxyPushSupplierImpl.C
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

#include "ProxyPushSupplierImpl.h"

TIDNotif::ProxyPushSupplierImpl::ProxyPushSupplierImpl(
                                    TIDorb::core::TIDORB* orb, 
                                    PortableServer::POA_ptr poa)
  : m_orb(orb), m_proxy_supplier_poa(PortableServer::POA::_duplicate(poa))
{
  // Select configuration for consumer'ss POA
  m_consumer_POA_config = 
    TIDNotif::util::TIDNotifConfig::getInt(TIDNotif::util::TIDNotifConfig::CONSUMER_POA_KEY);

  CORBA::Object_var obj_cur = orb->resolve_initial_references("POACurrent");
  m_current = PortableServer::Current::_narrow(obj_cur);
}


TIDNotif::ProxyPushSupplierImpl::~ProxyPushSupplierImpl()
{
  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "Deleting ProxyPushSupplierImpl with id ";
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }
}


TIDNotif::ProxyPushSupplierData* TIDNotif::ProxyPushSupplierImpl::getData()
{
  try {
    PortableServer::ObjectId_var oid = m_current->get_object_id();
    TIDorb::core::poa::OID oid_key(oid);

    ProxyPushSupplierDataTable::iterator it = m_proxy_push_suppliers.find(oid_key);
    if (it != m_proxy_push_suppliers.end()){
      return (*it).second;
    }
    else
      throw CORBA::OBJECT_NOT_EXIST();  

  } catch (const CORBA::Exception& ex) {
    
    throw CORBA::INV_OBJREF();
  }
}


void TIDNotif::ProxyPushSupplierImpl::register_proxy(
                                       TIDNotif::ProxyPushSupplierData* data)
{
  TIDorb::util::StringBuffer id_str;
  id_str << "ProxySupplier_" << data->_channel_id << "_";
  id_str << data->_admin_id << "_" << data->_id;

  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(id_str.str().data());

  TIDorb::core::poa::OID oid_key(oid);

  m_proxy_push_suppliers[oid_key] = data;
}


void TIDNotif::ProxyPushSupplierImpl::unregister_proxy(
                                        TIDNotif::ProxyPushSupplierData* data)
{
  TIDorb::util::StringBuffer id_str;
  id_str << "ProxySupplier_" << data->_channel_id << "_";
  id_str << data->_admin_id << "_" << data->_id;

  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(id_str.str().data());

  TIDorb::core::poa::OID oid_key(oid);

  // Destroy POA and POAManager if POA config is LOCAL
  if (m_consumer_POA_config == TIDNotif::util::TIDNotifConfig::LOCAL_POA) {
    TIDorb::util::StringBuffer proxy_supplier_poa_name;
    proxy_supplier_poa_name << "ProxyPushSupplierPOA" << data->_id;
    try {
      PortableServer::POAManager_var proxy_supplier_poa_manager = 
        m_proxy_supplier_poa->the_POAManager();
      m_proxy_supplier_poa->destroy(true, false);
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

  ProxyPushSupplierDataTable::iterator it = 
    m_proxy_push_suppliers.find(oid_key);
  if (it != m_proxy_push_suppliers.end()){
    m_proxy_push_suppliers.erase(it);
    delete data;
  }

}

// NotificationInternals::InternalProxySupplierConsumer operations

void TIDNotif::ProxyPushSupplierImpl::push_event(const CORBA::Any& data)
{

  TIDThr::Synchronized synchro(m_recursive_mutex);

  ProxyPushSupplierData* proxy_data = getData();

  if (proxy_data->connected){

    // Filter event

    try {
      if (!proxy_data->filterAdminDelegate->match(data)) {
        if (m_orb->trace != NULL)
          m_orb->print_trace(TIDorb::util::TR_DEBUG, "DISCARD_EVENT");
        return;
      }
    } catch (CosNotifyFilter::UnsupportedFilterableData& ufd ){
      if (m_orb->trace != NULL)
        m_orb->print_trace(TIDorb::util::TR_ERROR, 
                           "UnsupportedFilterableData");
      return;
    }



    try{
      
      switch( proxy_data->_type){
      case CosNotifyChannelAdmin::PUSH_ANY:
        
        if ( proxy_data->notify_style){
          proxy_data->_push_consumer->push(data);
        }
        else{
          proxy_data->_push_consumer->push(data);
        }
        break;

      case CosNotifyChannelAdmin::PUSH_STRUCTURED:
            
        const CosNotification::StructuredEvent* structured_event;
        data >>= structured_event;
        // Any more to do before deliver structured_event ??
        proxy_data->_structured_push_consumer->push_structured_event(*structured_event);
        break;

      default:
        throw CORBA::NO_IMPLEMENT();
        break;
      } // switch


    } catch(const CosEventComm::Disconnected& ex){
      if (m_orb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "ProxyPushSupplierImpl::push_event receive a ";
        msg << "Disconnected exception from a PushConsumer";
        m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data(), ex);
      }
    }
  }
  else{
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "ProxyPushSupplierImpl::push_event not connected to any PushConsumer";
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

}
		
void TIDNotif::ProxyPushSupplierImpl::destroyFromAdmin()
{

  ProxyPushSupplierData* proxy_data = getData();

  if (proxy_data->_destroying)
    return;

  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "ProxyPushSupplierImpl::destroyFromAdmin";
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }

  proxy_data->_destroying = true;

  if (proxy_data->connected){
    
    switch(proxy_data->_type){
    case CosNotifyChannelAdmin::PUSH_ANY:
      if (!CORBA::is_nil(proxy_data->_push_consumer)){
        proxy_data->_push_consumer->disconnect_push_consumer();
      }
      break;
    case CosNotifyChannelAdmin::PUSH_STRUCTURED:
      if (!CORBA::is_nil(proxy_data->_structured_push_consumer)){
        proxy_data->_structured_push_consumer->disconnect_structured_push_consumer();
      }
    default:
      break;
    } // switch


    proxy_data->connected = false;
    if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->delete_data(this);
    } //TODO_MORFEO: update or delete
  }

  this->unregister_proxy(proxy_data);
}
		
void TIDNotif::ProxyPushSupplierImpl::loadData()
{

}


// CosNotifyComm::StructuredPushSupplier operations

void TIDNotif::ProxyPushSupplierImpl::disconnect_structured_push_supplier()
{

  ProxyPushSupplierData* proxy_data = getData();

  if (proxy_data->_destroying) 
    return;

  if (proxy_data->connected){
    proxy_data->connected = false;
    proxy_data->_consumer_admin->removeProxyPushSupplier(proxy_data->_id);
    this->destroyFromAdmin();
  }

}


// CosNotifyComm::NotifySubscribe

void TIDNotif::ProxyPushSupplierImpl::subscription_change(
                             const CosNotification::EventTypeSeq& added, 
                             const CosNotification::EventTypeSeq& removed)
{

}


// CosNotifyFilter::FilterAdmin		

CosNotifyFilter::FilterID 
TIDNotif::ProxyPushSupplierImpl::add_filter(
                                    CosNotifyFilter::Filter_ptr filter)
{
  ProxyPushSupplierData* proxy_data = getData();
  return proxy_data->filterAdminDelegate->add_filter(filter);
}
		
void TIDNotif::ProxyPushSupplierImpl::remove_filter(
                                    CosNotifyFilter::FilterID filter)
  throw (CosNotifyFilter::FilterNotFound)
{
  ProxyPushSupplierData* proxy_data = getData();
  return proxy_data->filterAdminDelegate->remove_filter(filter);
} 
		
CosNotifyFilter::Filter_ptr 
TIDNotif::ProxyPushSupplierImpl::get_filter(
                                    CosNotifyFilter::FilterID filter)
  throw (CosNotifyFilter::FilterNotFound)
{
  ProxyPushSupplierData* proxy_data = getData();
  return proxy_data->filterAdminDelegate->get_filter(filter);
}
		
CosNotifyFilter::FilterIDSeq* 
TIDNotif::ProxyPushSupplierImpl::get_all_filters()
{
  ProxyPushSupplierData* proxy_data = getData();
  return proxy_data->filterAdminDelegate->get_all_filters();
}

void TIDNotif::ProxyPushSupplierImpl::remove_all_filters()
{
  ProxyPushSupplierData* proxy_data = getData();
  proxy_data->filterAdminDelegate->remove_all_filters();
}


// CosEventComm::PushSupplier	

void TIDNotif::ProxyPushSupplierImpl::disconnect_push_supplier()
{
  ProxyPushSupplierData* proxy_data = getData();
  
  if (proxy_data->_destroying)
    return;
  
  if (proxy_data->connected){
    proxy_data->connected = false;
    proxy_data->_consumer_admin->removeProxyPushSupplier(proxy_data->_id);
    this->destroyFromAdmin();
  }
  
}


// CosEventChannelAdmin::ProxyPushSupplier		

void TIDNotif::ProxyPushSupplierImpl::connect_push_consumer(
                               CosEventComm::PushConsumer_ptr push_consumer)
  throw (CosEventChannelAdmin::AlreadyConnected, 
         CosEventChannelAdmin::TypeError )
{
  ProxyPushSupplierData* proxy_data = getData();

  if (proxy_data->connected)
    throw CosEventChannelAdmin::AlreadyConnected();
  
  if (!CORBA::is_nil(push_consumer))
    proxy_data->_push_consumer = 
      CosEventComm::PushConsumer::_duplicate (push_consumer);
  else
    throw CORBA::BAD_PARAM("nil object reference passed");

  // Is a pure event service style push supplier
  proxy_data->notify_style = false;

  proxy_data->_type = CosNotifyChannelAdmin::PUSH_ANY;
  proxy_data->connected = true;

  if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(
                                        PersistenceDB::ATTR_PUSH_CONSUMER,
                                        this);
  }
}


// CosNotifyChannelAdmin::ProxyPushSupplier		

void TIDNotif::ProxyPushSupplierImpl::connect_any_push_consumer(
                                 CosEventComm::PushConsumer_ptr push_consumer)
  throw (CosEventChannelAdmin::AlreadyConnected, 
         CosEventChannelAdmin::TypeError)
{

  ProxyPushSupplierData* proxy_data = getData();

  if (proxy_data->connected)
    throw CosEventChannelAdmin::AlreadyConnected();

  if (!CORBA::is_nil(push_consumer)){

    CosNotifyComm::PushConsumer_var consumer = 
      CosNotifyComm::PushConsumer::_unchecked_narrow(push_consumer);

    if (!CORBA::is_nil(consumer)){
      // Is a notification service style push supplier
      proxy_data->notify_style = true;
    }
    else{
      // Is a pure event service style push supplier
      proxy_data->notify_style = false;
    }
    proxy_data->_push_consumer = 
      CosEventComm::PushConsumer::_duplicate (push_consumer);

  }

  proxy_data->_type = CosNotifyChannelAdmin::PUSH_ANY;
  proxy_data->connected = true;
  if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(
                                        PersistenceDB::ATTR_PUSH_CONSUMER,
                                        this);
  }
}


// CosNotifyChannelAdmin::StructuredProxyPullConsumer
// CosNotifyChannelAdmin::ProxyPushSupplier

void TIDNotif::ProxyPushSupplierImpl::suspend_connection()
  throw (CosNotifyChannelAdmin::ConnectionAlreadyInactive, 
         CosNotifyChannelAdmin::NotConnected)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

void TIDNotif::ProxyPushSupplierImpl::resume_connection()
  throw (CosNotifyChannelAdmin::ConnectionAlreadyActive, 
         CosNotifyChannelAdmin::NotConnected)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}
  

// CosNotification::QoSAdmin operations
		
CosNotification::QoSProperties* 
TIDNotif::ProxyPushSupplierImpl::get_qos()
{
  ProxyPushSupplierData* proxy_data = getData();
  return proxy_data->qosAdminDelegate->get_qos();
}

void TIDNotif::ProxyPushSupplierImpl::set_qos(
                               const CosNotification::QoSProperties& qos)
  throw (CosNotification::UnsupportedQoS)
{
  ProxyPushSupplierData* proxy_data = getData();
  try{
    proxy_data->qosAdminDelegate->set_qos(qos);
  }
  catch(const CosNotification::UnsupportedQoS& ex){
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "EventChannelImpl::set_qos: QoSProperties not supported";
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data(), ex);
    }
    throw;
  }

  CORBA::PolicyList* policies = proxy_data->qosAdminDelegate->getPolicies();
		
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

//   data.reference = 
//     InternalProxyPushConsumerHelper.narrow 
//     (
//      data.reference._set_policy_override(policies,
//                                          SetOverrideType.SET_OVERRIDE
//                                          )
//      );
}

void TIDNotif::ProxyPushSupplierImpl::validate_qos(
                       const CosNotification::QoSProperties& required_qos, 
                       CosNotification::NamedPropertyRangeSeq*& available_qos)
  throw (CosNotification::UnsupportedQoS)
{
  ProxyPushSupplierData* proxy_data = getData();
  proxy_data->qosAdminDelegate->validate_qos(required_qos, available_qos);
}


// CosNotifyChannelAdmin::ProxySupplier operations

CosNotifyChannelAdmin::ProxyType TIDNotif::ProxyPushSupplierImpl::MyType()
{
  ProxyPushSupplierData* proxy_data = getData();

  if (proxy_data->connected)
    return proxy_data->_type;
  else 
    return CosNotifyChannelAdmin::PUSH_ANY; // or what?
}

CosNotifyChannelAdmin::ConsumerAdmin_ptr 
TIDNotif::ProxyPushSupplierImpl::MyAdmin()
{
  ProxyPushSupplierData* proxy_data = getData();
  return ConsumerAdmin::_narrow(proxy_data->_consumer_admin);
}

CosNotifyFilter::MappingFilter_ptr 
TIDNotif::ProxyPushSupplierImpl::priority_filter()
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

void TIDNotif::ProxyPushSupplierImpl::priority_filter(
                             CosNotifyFilter::MappingFilter_ptr value)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

CosNotifyFilter::MappingFilter_ptr 
TIDNotif::ProxyPushSupplierImpl::lifetime_filter()
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

void TIDNotif::ProxyPushSupplierImpl::lifetime_filter(
                             CosNotifyFilter::MappingFilter_ptr value)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}
		
CosNotification::EventTypeSeq* 
TIDNotif::ProxyPushSupplierImpl::obtain_offered_types(
                             CosNotifyChannelAdmin::ObtainInfoMode mode)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}
		
void TIDNotif::ProxyPushSupplierImpl::validate_event_qos(
                       const CosNotification::QoSProperties& required_qos, 
                       CosNotification::NamedPropertyRangeSeq*& available_qos)
  throw (CosNotification::UnsupportedQoS)
{
  TIDNotif::qos::EventQoSAdmin* admin = new TIDNotif::qos::EventQoSAdmin(m_orb);
  admin->validate_qos(required_qos, available_qos);
  delete admin;
}
  

// CosNotifyChannelAdmin::StructuredProxyPushSupplier operations
		
void TIDNotif::ProxyPushSupplierImpl::connect_structured_push_consumer(
                       CosNotifyComm::StructuredPushConsumer_ptr push_consumer)
  throw(CosEventChannelAdmin::AlreadyConnected)
{
  ProxyPushSupplierData* proxy_data = getData();

  if (proxy_data->connected)
    throw CosEventChannelAdmin::AlreadyConnected();

  // Is a notification service style push supplier
  proxy_data->notify_style = true;

  if (!CORBA::is_nil(push_consumer)){
    proxy_data->_structured_push_consumer = 
      CosNotifyComm::StructuredPushConsumer::_duplicate(push_consumer);
  }

  proxy_data->_type = CosNotifyChannelAdmin::PUSH_STRUCTURED;

  proxy_data->connected = true;

  if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(
                                     PersistenceDB::ATTR_PUSH_CONSUMER,
                                     this);
  }

}

CosNotifyChannelAdmin::ProxyID  
TIDNotif::ProxyPushSupplierImpl::getProxyID ()
{
  ProxyPushSupplierData* proxy_data = getData();
  return proxy_data->_id;
}

// Persistence Management

void TIDNotif::ProxyPushSupplierImpl::readObject(istream & is)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  ProxyPushSupplierData* data = 
    new ProxyPushSupplierData(m_orb, m_proxy_supplier_poa, 0, 0, 0);

  // Read connected flag
  is >> data->connected;

  // Read ProxyID
  is >> data->_id;
  
  // Read reference to ConsumerAdmin
  try {
    string str_ref; 
    is >> str_ref;

    CORBA::Object_var obj = m_orb->string_to_object(str_ref.c_str());
    data->_consumer_admin = InternalConsumerAdmin::_narrow(obj);
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering reference to ConsumerAdmin of ProxyPushSupplier " << data->_id; ///
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Read ProxyType
  CORBA::Long type;
  is >> type;


  try {
    string str_ref; 
    is >> str_ref;

    CORBA::Object_var obj = m_orb->string_to_object(str_ref.c_str());
    
    switch(type){
    case 0:
      data->_type = CosNotifyChannelAdmin::PUSH_ANY;
      data->_push_consumer = CosEventComm::PushConsumer::_unchecked_narrow(obj);
      break;
    case 1:
      data->_type = CosNotifyChannelAdmin::PUSH_STRUCTURED;
      data->_structured_push_consumer = 
        CosNotifyComm::StructuredPushConsumer::_unchecked_narrow(obj);
      break;
    default:
      break;
    } // switch
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering reference to PushConsumer of ProxyPushSupplier " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Read Notification service style push supplier
  is >> data->notify_style;

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
      msg << "ERROR recovering Filters of ProxyPushSupplier " << data->_id;
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
      msg << "ERROR recovering QoSAdminDeletate of ProxyPushSupplier " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  this->register_proxy(data); 
}


void TIDNotif::ProxyPushSupplierImpl::writeObject(ostream & os)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  ProxyPushSupplierData* data = getData();
  
  // Write connected flag
  os << data->connected << endl;

  // Write ProxyID
  os << data->_id << endl;
  
  CORBA::String_var str_ref; 

  // Write reference to ConsumerAdmin
  try {
    str_ref = m_orb->object_to_string(data->_consumer_admin);
    os << str_ref << endl;
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering ConsumerAdmin of ProxyPushSupplier " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }
   
  // Write ProxyType
  try {
    switch(data->_type){
    case CosNotifyChannelAdmin::PUSH_ANY:
      os << (CORBA::Long)0 << endl;
      str_ref = m_orb->object_to_string(data->_push_consumer);
      break;
    case CosNotifyChannelAdmin::PUSH_STRUCTURED:
      os << (CORBA::Long)1 << endl;
      str_ref = m_orb->object_to_string(data->_structured_push_consumer);
      break;
    default:
      break;
    } // switch
    os << str_ref << endl;  
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering PushConsumer of ProxyPushSupplier " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Write Notification service style push supplier
  os << data->notify_style << endl;

  // Write Filters
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
      msg << "ERROR recovering Filters of ProxyPushSupplier " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Write QoS properties
  try {
    data->qosAdminDelegate->writeObject(os);
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering QoSAdminDelegate of ProxyPushSupplier " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }
}
