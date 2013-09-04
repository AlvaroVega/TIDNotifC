/*
 *  File name: ProxyPushConsumerImpl.C
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

#include "ProxyPushConsumerImpl.h"


TIDNotif::ProxyPushConsumerImpl::ProxyPushConsumerImpl(
                                   TIDorb::core::TIDORB* orb, 
                                   PortableServer::POA_ptr poa):
  m_orb(orb), m_proxy_consumer_poa(PortableServer::POA::_duplicate(poa)) 
{
  // Select configuration for suppliers's POA
  m_supplier_POA_config = 
    TIDNotif::util::TIDNotifConfig::getInt(TIDNotif::util::TIDNotifConfig::SUPPLIER_POA_KEY);

  CORBA::Object_var obj_cur = orb->resolve_initial_references("POACurrent");
  m_current = PortableServer::Current::_narrow(obj_cur);
}

TIDNotif::ProxyPushConsumerImpl::~ProxyPushConsumerImpl()
{
  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "Deleting ProxyPushConsumerImpl with id ";
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }

}


TIDNotif::ProxyPushConsumerData* TIDNotif::ProxyPushConsumerImpl::getData()
{
  try {
    PortableServer::ObjectId_var oid = m_current->get_object_id();
    TIDorb::core::poa::OID oid_key(oid);

    ProxyPushConsumerDataTable::iterator it = 
      m_proxy_push_consumers.find(oid_key);
    if (it != m_proxy_push_consumers.end()){
      return (*it).second;
    }
    else
      throw CORBA::OBJECT_NOT_EXIST();  

  } catch (const CORBA::Exception& ex) {
    
    throw CORBA::INV_OBJREF();
  }
}


void TIDNotif::ProxyPushConsumerImpl::register_proxy(
                                         TIDNotif::ProxyPushConsumerData* data)
{
  TIDorb::util::StringBuffer id_str;
  id_str << "ProxyConsumer_" << data->_channel_id << "_";
  id_str << data->_admin_id << "_" << data->_id;

  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(id_str.str().data());

  TIDorb::core::poa::OID oid_key(oid);

  m_proxy_push_consumers[oid_key] = data;
}


void TIDNotif::ProxyPushConsumerImpl::unregister_proxy(
                                         TIDNotif::ProxyPushConsumerData* data)
{
  TIDorb::util::StringBuffer id_str;
  id_str << "ProxyConsumer_" << data->_channel_id << "_";
  id_str << data->_admin_id << "_" << data->_id;

  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(id_str.str().data());

  TIDorb::core::poa::OID oid_key(oid);

  // Destroy POA and POAManager if POA config is LOCAL
  if (m_supplier_POA_config == TIDNotif::util::TIDNotifConfig::LOCAL_POA) {
    TIDorb::util::StringBuffer proxy_consumer_poa_name;
    proxy_consumer_poa_name << "ProxyPushConsumerPOA" << data->_id;
    try {
      PortableServer::POAManager_var proxy_consumer_poa_manager = 
        m_proxy_consumer_poa->the_POAManager();
      m_proxy_consumer_poa->destroy(true, false);
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

  ProxyPushConsumerDataTable::iterator it = m_proxy_push_consumers.find(oid_key);
  if (it != m_proxy_push_consumers.end()){
    m_proxy_push_consumers.erase(it);
    delete data;
  }

}


// NotificationInternals::InternalProxyPushConsumer operations

void TIDNotif::ProxyPushConsumerImpl::ipush(const CORBA::Any& data)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

void TIDNotif::ProxyPushConsumerImpl::destroyFromAdmin()
{

  ProxyPushConsumerData* proxy_data = getData();

  if (proxy_data->_destroying)
    return;

  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "ProxyPushConsumerImpl::destroyFromAdmin";
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }

  proxy_data->_destroying = true;

  if (proxy_data->connected){

    if (!CORBA::is_nil(proxy_data->_push_supplier)){
      proxy_data->_push_supplier->disconnect_push_supplier();
    }

    proxy_data->connected = false;
  }
  if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->delete_data(this);
  }  //TODO_MORFEO: delete_data or update_data
  
  this->unregister_proxy(proxy_data);
}

void TIDNotif::ProxyPushConsumerImpl::loadData()
{
}


// CosEventChannelAdmin::ProxyPushConsumer operations

void TIDNotif::ProxyPushConsumerImpl::connect_push_supplier(
                                    CosEventComm::PushSupplier_ptr push_supplier)
  throw (CosEventChannelAdmin::AlreadyConnected)
{

  ProxyPushConsumerData* proxy_data = getData();

  if (proxy_data->connected)
    throw CosEventChannelAdmin::AlreadyConnected();
  
  if (!CORBA::is_nil((CosEventComm::PushSupplier_ptr)push_supplier))
    proxy_data->_push_supplier =
      CosEventComm::PushSupplier::_duplicate (push_supplier);
  else
    proxy_data->_push_supplier = CosEventComm::PushSupplier::_nil();

  // Is a pure event service style push supplier
  proxy_data->notify_style = false;

  proxy_data->_type = CosNotifyChannelAdmin::PUSH_ANY;
  proxy_data->connected = true;

  if (PersistenceManager::isActive()) {
    PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_PUSH_SUPPLIER,
                                             this);
  }
 
}


// CosNotifyChannelAdmin::ProxyPushConsumer operations

void TIDNotif::ProxyPushConsumerImpl::connect_any_push_supplier(
                                         CosEventComm::PushSupplier_ptr push_supplier)
  throw (CosEventChannelAdmin::AlreadyConnected)
{
  ProxyPushConsumerData* proxy_data = getData();

  if (proxy_data->connected)
    throw CosEventChannelAdmin::AlreadyConnected();

  if (!CORBA::is_nil(push_supplier)){
    
    CosNotifyComm::PushSupplier_var supplier = 
      CosNotifyComm::PushSupplier::_narrow(push_supplier);

    if (!CORBA::is_nil(supplier))
      // Is a notification service style push supplier
      proxy_data->notify_style = true;
    else
      // Is a pure event service style push supplier
      proxy_data->notify_style = false;

    proxy_data->_push_supplier = 
      CosEventComm::PushSupplier::_duplicate (push_supplier);
  } 

  proxy_data->_type = CosNotifyChannelAdmin::PUSH_ANY;

  proxy_data->connected = true;

  if (PersistenceManager::isActive()) {
    PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_PUSH_SUPPLIER,
                                             this);
  }
}
  
  
// CosNotifyChannelAdmin::ProxyConsumer operations

ProxyType TIDNotif::ProxyPushConsumerImpl::MyType()
{
  ProxyPushConsumerData* proxy_data = getData();

  if (proxy_data->connected)
    return proxy_data->_type;
  else 
    return CosNotifyChannelAdmin::PUSH_ANY; // or what?
}


SupplierAdmin_ptr TIDNotif::ProxyPushConsumerImpl::MyAdmin()
{
  ProxyPushConsumerData* proxy_data = getData();
  return SupplierAdmin::_narrow(proxy_data->_supplier_admin);
}

		
CosNotification::EventTypeSeq* 
TIDNotif::ProxyPushConsumerImpl::obtain_subscription_types(ObtainInfoMode mode)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

		
void TIDNotif::ProxyPushConsumerImpl::validate_event_qos(
                        const CosNotification::QoSProperties& required_qos, 
                        CosNotification::NamedPropertyRangeSeq*& available_qos)
  throw (CosNotification::UnsupportedQoS)
{
  TIDNotif::qos::EventQoSAdmin* admin = new TIDNotif::qos::EventQoSAdmin(m_orb);
  admin->validate_qos(required_qos, available_qos);
  delete admin;
}


// CosNotifyFilter::FilterAdmin

CosNotifyFilter::FilterID 
TIDNotif::ProxyPushConsumerImpl::add_filter(CosNotifyFilter::Filter_ptr filter)
{
  ProxyPushConsumerData* proxy_data = getData();
  return proxy_data->filterAdminDelegate->add_filter(filter);
}

		
void TIDNotif::ProxyPushConsumerImpl::remove_filter(CosNotifyFilter::FilterID filter)
  throw (CosNotifyFilter::FilterNotFound)
{
  ProxyPushConsumerData* proxy_data = getData();
  proxy_data->filterAdminDelegate->remove_filter(filter);
}

		
CosNotifyFilter::Filter_ptr 
TIDNotif::ProxyPushConsumerImpl::get_filter(CosNotifyFilter::FilterID filter)
  throw (CosNotifyFilter::FilterNotFound)
{
  ProxyPushConsumerData* proxy_data = getData();
  return proxy_data->filterAdminDelegate->get_filter(filter);
}
		
CosNotifyFilter::FilterIDSeq* 
TIDNotif::ProxyPushConsumerImpl::get_all_filters()
{
  ProxyPushConsumerData* proxy_data = getData();
  return proxy_data->filterAdminDelegate->get_all_filters();
}
		
void TIDNotif::ProxyPushConsumerImpl::remove_all_filters()
{
  ProxyPushConsumerData* proxy_data = getData();
  proxy_data->filterAdminDelegate->remove_all_filters();
}


// CosEventComm::PushConsummer operations

void TIDNotif::ProxyPushConsumerImpl::push(const CORBA::Any& data)
  throw (CosEventComm::Disconnected)
{

  TIDThr::Synchronized synchro(m_recursive_mutex);

  ProxyPushConsumerData* proxy_data = getData();

  if (proxy_data->_destroying){
    if (m_orb->trace != NULL)
      m_orb->print_trace(TIDorb::util::TR_ERROR, "ProxyPushConsumerImpl::push Disconnected");
    throw CosEventComm::Disconnected();
  }

  if (proxy_data->connected){ // comprobar _type y notify_style_ ??

    try {
      if (!proxy_data->filterAdminDelegate->match(data)) {
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

    proxy_data->_supplier_admin->push_event(data);

  }
  else{
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "ProxyPushConsumerImpl::push not connected to any SupplierAdmin";
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
    throw CosEventComm::Disconnected();
  }

}

		
void TIDNotif::ProxyPushConsumerImpl::disconnect_push_consumer()
{
  ProxyPushConsumerData* proxy_data = getData();

  if (proxy_data->_destroying)
    return;

  if (proxy_data->connected){
    //this->destroyFromAdmin();
    proxy_data->connected = false;
    proxy_data->_supplier_admin->removeProxyPushConsumer(proxy_data->_id);
    this->destroyFromAdmin();
  }

}


// CosNotifyComm::NotifyPublish operations

void TIDNotif::ProxyPushConsumerImpl::offer_change(
                                         const CosNotification::EventTypeSeq& added, 
                                         const CosNotification::EventTypeSeq& removed)
    throw (CosNotifyComm::InvalidEventType)
{

}

		
// CosNotification::QoSAdmin operations

CosNotification::QoSProperties* 
TIDNotif::ProxyPushConsumerImpl::get_qos()
{
  ProxyPushConsumerData* proxy_data = getData();
  return proxy_data->qosAdminDelegate->get_qos();
}


void TIDNotif::ProxyPushConsumerImpl::set_qos(const CosNotification::QoSProperties& qos)
  throw (CosNotification::UnsupportedQoS)
{
  ProxyPushConsumerData* proxy_data = getData();

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


void TIDNotif::ProxyPushConsumerImpl::validate_qos(
                        const CosNotification::QoSProperties& required_qos, 
                        CosNotification::NamedPropertyRangeSeq*& available_qos)
  throw (CosNotification::UnsupportedQoS)
{
  ProxyPushConsumerData* proxy_data = getData();
  proxy_data->qosAdminDelegate->validate_qos(required_qos, available_qos);
}

// CosNotifyChannelAdmin::StructuredProxyPushConsumer operations

void TIDNotif::ProxyPushConsumerImpl::connect_structured_push_supplier(
                               CosNotifyComm::StructuredPushSupplier_ptr push_supplier)
  throw(CosEventChannelAdmin::AlreadyConnected)
{
  ProxyPushConsumerData* proxy_data = getData();

  if (proxy_data->connected)
    throw CosEventChannelAdmin::AlreadyConnected();

  // Is a notification service style push supplier
  proxy_data->notify_style = true;

  if (!CORBA::is_nil(push_supplier)){

    proxy_data->_push_supplier = CosEventComm::PushSupplier::_narrow (push_supplier);
  }

  proxy_data->_type = CosNotifyChannelAdmin::PUSH_STRUCTURED;

  proxy_data->connected = true;

  if (PersistenceManager::isActive()) {
    PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_PUSH_SUPPLIER,
                                             this);
  }
            
}

// CosNotifyComm::StructuredPushConsumer operations

void TIDNotif::ProxyPushConsumerImpl::push_structured_event(
                               const CosNotification::StructuredEvent& notification)
  throw (CosNotification::UnsupportedQoS, CosEventComm::Disconnected)
{

  TIDThr::Synchronized synchro(m_recursive_mutex);

  ProxyPushConsumerData* proxy_data = getData();

  if ( proxy_data->connected && proxy_data->notify_style && 
       (proxy_data->_type == CosNotifyChannelAdmin::PUSH_STRUCTURED) ){ 


    if (notification.header.variable_header.length() > 0) {
      
      CORBA::PolicyList* policies = new CORBA::PolicyList();
      CORBA::ULong _length = 0;

      TIDNotif::qos::EventQoSAdmin* admin = 
        new TIDNotif::qos::EventQoSAdmin(m_orb);
            
      try {
        admin->set_qos(notification.header.variable_header);
      }
      catch (const CosNotification::UnsupportedQoS& ex) {
        if (m_orb->trace != NULL){
          TIDorb::util::StringBuffer msg;
          msg << "Unsupported Qos in variable_header of Structured Event";
          m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data(), ex);
        }
      }

            
      TIDNotif::qos::StartTimeProperty* start_time = 
        admin->getStartTimeProperty();
            
      if (start_time != NULL) {
        TIDNotif::qos::StartTimeSupportedProperty* start_supported = 
          proxy_data->qosAdminDelegate->getStartTimeSupportedProperty();
                
        if (start_supported != NULL) 
          if (start_supported->getValue()) {
            policies->length(++_length);
            (*policies)[_length - 1] = start_time->getPolicy(m_orb);
          }            
      }

            
      TIDNotif::qos::StopTimeProperty* stop_time = 
        admin->getStopTimeProperty();
            
      if (stop_time != NULL) {
        TIDNotif::qos::StopTimeSupportedProperty* stop_supported = 
          proxy_data->qosAdminDelegate->getStopTimeSupportedProperty();
                
        if (stop_supported != NULL) 
          if (stop_supported->getValue()) {
            policies->length(++_length);
            (*policies)[_length - 1] = stop_time->getPolicy(m_orb);
          }            
      }
      
            
      if (policies->length() > 0) {

        CORBA::PolicyCurrent* thread_policies = NULL;

        try {
          CORBA::Object_var obj;
          obj = m_orb->resolve_initial_references("PolicyCurrent");
          thread_policies = CORBA::PolicyCurrent::_narrow(obj);
        }
        catch (CORBA::ORB::InvalidName& e) {
          throw CORBA::INTERNAL();
        }
                
        try {
          thread_policies->set_policy_overrides(*policies, 
                                                CORBA::ADD_OVERRIDE);
        }
        catch (CORBA::InvalidPolicies& e1) {}
      }

      delete admin;
      delete policies;
    } // if (notification.header.variable_header.length() > 0)


    CORBA::Any data;
    data <<= notification;

    // Event Filter
    try {
      if (!proxy_data->filterAdminDelegate->match(data)) {
        if (m_orb->trace != NULL)
          m_orb->print_trace(TIDorb::util::TR_DEBUG, "DISCARD_EVENT");
        return;
      }
    } catch (const CosNotifyFilter::UnsupportedFilterableData& ufd ){
      if (m_orb->trace != NULL)
        m_orb->print_trace(TIDorb::util::TR_ERROR, 
                           "UnsupportedFilterableData",
                           ufd);
      return;
    }

    proxy_data->_supplier_admin->push_event(data);

  }
  else{

    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "ProxyPushConsumerImpl::push_structured_event not connected to any SupplierAdmin";
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
    throw CosEventComm::Disconnected();
  }


}


void TIDNotif::ProxyPushConsumerImpl::disconnect_structured_push_consumer()
{
  ProxyPushConsumerData* proxy_data = getData();
  
  if (proxy_data->_destroying)
    return;

  if (proxy_data->connected){
    //this->destroyFromAdmin();
    proxy_data->connected = false;
    proxy_data->_supplier_admin->removeProxyPushConsumer(proxy_data->_id);
    this->destroyFromAdmin();
  }

}


CosNotifyChannelAdmin::ProxyID TIDNotif::ProxyPushConsumerImpl::getProxyID ()
{
  ProxyPushConsumerData* proxy_data = getData();
  return proxy_data->_id;
}


// Persistence Management

void TIDNotif::ProxyPushConsumerImpl::readObject(istream & is)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  ProxyPushConsumerData* data = 
    new ProxyPushConsumerData(m_orb, m_proxy_consumer_poa, 0, 0, 0);

  // Read connected flag
  is >> data->connected;
  // Read ProxyID
  is >> data->_id;

  // Read reference to SupplierAdmin
  try {
    string str_ref; 
    is >> str_ref;
    CORBA::Object_var obj = m_orb->string_to_object(str_ref.c_str());
    data->_supplier_admin = InternalSupplierAdmin::_narrow(obj);
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering SupplierAdmin of ProxyPushConsumer " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }
  
  // Read ProxyType
  CORBA::Long type;
  is >> type;
  try {
    switch(type){
    case 0:
      data->_type = CosNotifyChannelAdmin::PUSH_ANY;
      break;
    case 1:
      data->_type = CosNotifyChannelAdmin::PUSH_STRUCTURED;
      break;
    default:
      break;
    } // switch
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering type of ProxyPushConsumer " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }


  // Read PushSupplier reference
  try {
    string str_ref; 
    is >> str_ref;
    // Fix bug #437 Notification Service doesn't restart in some circustances
    if (str_ref.find("IOR") != string::npos ) { 
      CORBA::Object_var obj = m_orb->string_to_object(str_ref.c_str()); 
      data->_push_supplier = CosEventComm::PushSupplier::_unchecked_narrow(obj);
    }
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering PushSupplier of ProxyPushConsumer " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Read Notification service style push supplier
  is >> data->notify_style;

  // Read Filters
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
      buf.clear(); //TODO_MORFEO: clear buffer
      buf.flush();
      PersistenceManager::getDB()->load_filter(filter_id, 
                                               data->filterAdminDelegate);
    }
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR recovering Filters of ProxyPushConsumer " << data->_id;
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
      msg << "ERROR recovering QoSAdminDelegate of ProxyPushConsumer " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  this->register_proxy(data);

}


void TIDNotif::ProxyPushConsumerImpl::writeObject(ostream & os)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  ProxyPushConsumerData* data = getData();
  
  // Write connected flag
  os << data->connected << endl;

  // Write ProxyID
  os << data->_id << endl;

  CORBA::String_var str_ref; 
  
  // Write reference to SupplierAdmin
  try {
    str_ref = m_orb->object_to_string(data->_supplier_admin);
    os << str_ref << endl;
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving SupplierAdmin of ProxyPushConsumer " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }
   
  // Write ProxyType
  try {
    switch(data->_type){
    case CosNotifyChannelAdmin::PUSH_ANY:
      os << (CORBA::Long) 0 << endl;
      break;
    case CosNotifyChannelAdmin::PUSH_STRUCTURED:
      os << (CORBA::Long) 1 << endl;
      break;
    default:
      break;
    } // switch
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving type of ProxyPushConsumer " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Write PushSupplier reference
  try {
    if (data->_push_supplier != NULL) {
      str_ref = m_orb->object_to_string(data->_push_supplier); 
      os << str_ref << endl;  
    }
    else
      os << endl;  
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving PushSupplier reference of ProxyPushConsumer " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Write Notification service style push supplier
  os << data->notify_style << endl;

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
      msg << "ERROR saving Filters of ProxyPushConsumer " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  // Write QoS properties
  try { 
    data->qosAdminDelegate->writeObject(os);
  } catch (...) {
    if (m_orb->trace != NULL) {
      TIDorb::util::StringBuffer msg;
      msg << "ERROR saving QoSAdminDelegate of ProxyPushConsumer " << data->_id;
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

}
