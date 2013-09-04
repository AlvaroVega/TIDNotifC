/*
 *  File name: EventChannelFactoryImpl.C
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

#include "EventChannelFactoryImpl.h"



TIDNotif::EventChannelFactoryImpl::EventChannelFactoryImpl(
                                                 TIDorb::core::TIDORB* orb, 
                                                 PortableServer::POA_ptr poa)
  throw (PortableServer::POA::InvalidPolicy, CORBA::SystemException)
  : m_orb(orb), m_tidnotif_poa(poa)
{
  // Select configuration for Channel's POA
  m_channel_POA_config = 
    TIDNotif::util::TIDNotifConfig::getInt(TIDNotif::util::TIDNotifConfig::CHANNEL_POA_KEY);
  
  PortableServer::POAManager_var poa_manager = m_tidnotif_poa->the_POAManager();

  try{

    CORBA::PolicyList policy_list;
    policy_list.length(5);
    policy_list[0] = m_tidnotif_poa->create_id_assignment_policy(PortableServer::USER_ID);
    policy_list[1] = m_tidnotif_poa->create_lifespan_policy (PortableServer::PERSISTENT);
    policy_list[2] = m_tidnotif_poa->create_request_processing_policy(
                                                      PortableServer::USE_DEFAULT_SERVANT);
    policy_list[3] = m_tidnotif_poa->create_servant_retention_policy(PortableServer::RETAIN);
    policy_list[4] = m_tidnotif_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
    m_channel_poa = 
      m_tidnotif_poa->create_POA("EventChannelPOA", poa_manager, policy_list);


    if (m_orb->trace != NULL)
      m_orb->print_trace(TIDorb::util::TR_DEEP_DEBUG, "EventChannelPOA created");

  } catch(PortableServer::POA::AdapterAlreadyExists& ex){

    try{
      m_channel_poa = 
        m_tidnotif_poa->find_POA("EventChannelPOA", false);
      if (m_orb->trace != NULL)
        m_orb->print_trace(TIDorb::util::TR_DEEP_DEBUG, "EventChannelPOA found"); 
    } catch (const PortableServer::POA::AdapterNonExistent& ex){
      TIDorb::util::StringBuffer msg;
      msg << "EventChannelPOA could not be created and found";
      if (m_orb->trace != NULL)
        m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data(), ex);
      throw CORBA::INTERNAL(msg.str().data());
    }
  } 

  m_counterID = 0;

  // Set default servant only if POA is global
  if (m_channel_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
    
    TIDNotif::EventChannelImpl* channel_servant;
    channel_servant = new TIDNotif::EventChannelImpl(m_orb, m_channel_poa,
                                                     this, NULL, NULL);
    m_channel_poa->set_servant(channel_servant);

  }
}


TIDNotif::EventChannelFactoryImpl::~EventChannelFactoryImpl()
  throw (TIDThr::SystemException)
{
  if (m_orb->trace != NULL)
    m_orb->print_trace(TIDorb::util::TR_DEBUG, "Destroying EventChannelFactory");

  if (m_channel_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
    EventChannelImpl* channel_servant = 
      dynamic_cast<EventChannelImpl*>(m_channel_poa->get_servant());
   
    delete channel_servant;

  } else {
    // Destroy channels implies recover and destroy all servants from POA childs
    ChannelsTable::iterator begin = channels.begin();
    ChannelsTable::iterator end   = channels.end();
    for (ChannelsTable::iterator iter = begin; iter != end; iter++) {
      ChannelID id = iter->first;
      TIDorb::util::StringBuffer poa_name;
      poa_name << "EventChannelPOA" << id;

      PortableServer::POA_var channel_poa = 
        m_channel_poa->find_POA(poa_name.str().data(), false);
      EventChannelImpl* channel_servant = 
        dynamic_cast<EventChannelImpl*>(channel_poa->get_servant());
      
      delete channel_servant;
    }
  }
  
  channels.clear();
  
 /* if (PersistenceManager::isActive()) {
    PersistenceManager::getDB()->delete_data();
  }*/
}


CosNotifyChannelAdmin::EventChannel_ptr 
TIDNotif::EventChannelFactoryImpl::create_channel(
                 const CosNotification::QoSProperties& initial_qos, 
                 const CosNotification::AdminProperties& initial_admin, 
                 CosNotifyChannelAdmin::ChannelID& id)
  throw (CosNotification::UnsupportedQoS, CosNotification::UnsupportedAdmin)
{

  TIDThr::Synchronized synchro(m_recursive_mutex);


  // Compose an unique id for this target object
  id = m_counterID++;

  // Get channel POA in order with configuration
  // TODO: refactor this block int ThePOAFactory
  PortableServer::POA_var channel_poa;
  if (m_channel_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Using Global POA for channel " << id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    channel_poa = m_channel_poa;
  } else { // Local
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Creating Local POA for channel " << id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
    TIDorb::util::StringBuffer channel_poa_name;
    channel_poa_name << "EventChannelPOA" << id;
    CORBA::PolicyList policy_list;
    policy_list.length(5);
    policy_list[0] = m_channel_poa->create_id_assignment_policy(PortableServer::USER_ID);
    policy_list[1] = m_channel_poa->create_lifespan_policy (PortableServer::PERSISTENT);
    policy_list[2] = m_channel_poa->create_request_processing_policy(
                                                      PortableServer::USE_DEFAULT_SERVANT);
    policy_list[3] = m_channel_poa->create_servant_retention_policy(PortableServer::RETAIN);
    policy_list[4] = m_channel_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
    channel_poa = 
      m_channel_poa->create_POA(channel_poa_name.str().data(), NULL, policy_list);

    PortableServer::POAManager_var channel_poa_mgr = 
      channel_poa->the_POAManager();

    TIDNotif::EventChannelImpl* channel_servant;
    channel_servant = new TIDNotif::EventChannelImpl(m_orb, channel_poa,
                                                     this, NULL, NULL);
    channel_poa->set_servant(channel_servant);

    channel_poa_mgr->activate();
  }

  TIDNotif::EventChannelData* channel_data = NULL;

  try {

    channel_data = new TIDNotif::EventChannelData(m_orb, m_channel_poa, id, 
                                                  this);

    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "New EventChannel created with id " << id; 
      m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
    }
  } catch(...){
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "Error creating EventChannel with id " << id; 
      m_orb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
  }

  TIDNotif::EventChannelImpl* channel_impl = 
    dynamic_cast < TIDNotif::EventChannelImpl* > (channel_poa->get_servant());
  channel_impl->register_channel(channel_data);

  TIDorb::util::StringBuffer str_id;
  str_id << "Channel_" << id;

  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(str_id.str().data());

  CORBA::Object_var object = 
      channel_poa->create_reference_with_id(oid, 
                                     _InternalDistributionChannelHelper::id());

  CosNotifyChannelAdmin::EventChannel_ptr channel_ref = 
    CosNotifyChannelAdmin::EventChannel::_narrow(object);


  // Check if QoSProperties are supported
  try{
    channel_ref->set_qos(initial_qos);
  } catch(CosNotification::UnsupportedQoS& ex){
    if (m_orb->trace != NULL)
      m_orb->print_trace(TIDorb::util::TR_ERROR, 
                         "EventChannelFactoryImpl: initial_qos not supported!", ex);
    throw;
  }

  // Check if AdminProperties are supported
  try{
    channel_ref->set_admin(initial_admin);
  } catch(CosNotification::UnsupportedAdmin& ex){
    if (m_orb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "EventChannelFactoryImpl: AdminProperties are not supported by the moment!";
      m_orb->print_trace(TIDorb::util::TR_USER, msg.str().data(), ex);
    }
    // throw;
  }


  // Add event channel reference to channels table
  channels[id] = EventChannel::_duplicate(channel_ref);

  if (PersistenceManager::isActive()) {
    PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_CHANNEL_FACTORY,
                                             this);
  }

  return channel_ref;
		
}

		
CosNotifyChannelAdmin::ChannelIDSeq* 
TIDNotif::EventChannelFactoryImpl::get_all_channels()
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  ChannelsTable::iterator it   = channels.begin();
  ChannelsTable::iterator end  = channels.end();

  ChannelIDSeq* seq = new ChannelIDSeq;
  seq->length(channels.size());
  int i = 0;
  while (it != end){
    (*seq)[i]=(*it).first;
    it++;
    i++;
  }
  return seq;
}

		
CosNotifyChannelAdmin::EventChannel_ptr 
TIDNotif::EventChannelFactoryImpl::get_event_channel(
                                          CosNotifyChannelAdmin::ChannelID id)
  throw (CosNotifyChannelAdmin::ChannelNotFound)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  ChannelsTable::iterator it = channels.find(id);

  if (it != channels.end()){
    return EventChannel::_duplicate((*it).second);
  }
  else
    throw CosNotifyChannelAdmin::ChannelNotFound();
}



// Persistence Management

void TIDNotif::EventChannelFactoryImpl::readObject(istream & is)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  // Read current m_counterID for channels
  is >> m_counterID;


  // Read all data about ChannelsTable: IDs and IORs
  try {

    CosNotification::QoSProperties initial_qos;
    initial_qos.length(0); // will be read after create an EventChannel
    CosNotification::AdminProperties initial_admin;
    initial_admin.length(0);
    PortableServer::ObjectId_var oid;


    CORBA::Long channels_size;
    is >> channels_size;

    TIDNotif::EventChannelData* channel_data = NULL;



    for (int i = 0; i < channels_size; i++){
      
        ChannelID id;
        string str_ref;
        is >> id;
        is >> str_ref;

        if (PersistenceManager::getDB()->data_saved(id)){

          // Get channel POA in order with configuration
          // TODO: refactor this block int ThePOAFactory
          PortableServer::POA_var channel_poa;
          if (m_channel_POA_config == TIDNotif::util::TIDNotifConfig::GLOBAL_POA) {
            if (m_orb->trace != NULL){
              TIDorb::util::StringBuffer msg;
              msg << "Using Global POA for channel " << id; 
              m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
            }
            channel_poa = m_channel_poa;
          } else { // Local
            if (m_orb->trace != NULL){
              TIDorb::util::StringBuffer msg;
              msg << "Creating Local POA for channel " << id; 
              m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
            }
            TIDorb::util::StringBuffer channel_poa_name;
            channel_poa_name << "EventChannelPOA" << id;
            CORBA::PolicyList policy_list;
            policy_list.length(5);
            policy_list[0] = m_channel_poa->create_id_assignment_policy(PortableServer::USER_ID);
            policy_list[1] = m_channel_poa->create_lifespan_policy (PortableServer::PERSISTENT);
            policy_list[2] = m_channel_poa->create_request_processing_policy(
                                                             PortableServer::USE_DEFAULT_SERVANT);
            policy_list[3] = m_channel_poa->create_servant_retention_policy(PortableServer::RETAIN);
            policy_list[4] = m_channel_poa->create_id_uniqueness_policy (PortableServer::MULTIPLE_ID);
            channel_poa = 
              m_channel_poa->create_POA(channel_poa_name.str().data(), NULL, policy_list);
            
            PortableServer::POAManager_var channel_poa_mgr = 
              channel_poa->the_POAManager();
            
            TIDNotif::EventChannelImpl* channel_servant;
            channel_servant = new TIDNotif::EventChannelImpl(m_orb, channel_poa,
                                                             this, NULL, NULL);
            channel_poa->set_servant(channel_servant);
            
            channel_poa_mgr->activate();
          }


          channel_data = new TIDNotif::EventChannelData(m_orb, m_channel_poa, 
                                                        id, this);

          TIDorb::util::StringBuffer str_id;
          str_id << "Channel_" << id;
          oid = PortableServer::string_to_ObjectId(str_id.str().data());

          TIDNotif::EventChannelImpl* channel_impl = 
            dynamic_cast < TIDNotif::EventChannelImpl* > (channel_poa->get_servant());
          channel_impl->register_channel(channel_data);

          PersistenceManager::getDB()->load_c(channel_impl);
          
          CORBA::Object_var object =
            channel_poa->create_reference_with_id(oid, 
                                        _InternalDistributionChannelHelper::id());
          EventChannel_ptr ref = EventChannel::_narrow(object);
          channels[id] = ref;
        }
    }// for
    
  } catch (...) {
    
    if (m_orb->trace != NULL)
      m_orb->print_trace(TIDorb::util::TR_ERROR, 
                         "ERROR recovering EventChannelFactory");
  }

}

void TIDNotif::EventChannelFactoryImpl::writeObject(ostream & os)
{
  TIDThr::Synchronized synchro(m_recursive_mutex);

  // Write actual m_counterID for channels
  os << m_counterID << endl;

  // Write all about ChannelsTable: IDs and IORs
  try {
    os << (CORBA::Long) channels.size() << endl;
    ChannelsTable::iterator it   = channels.begin();
    ChannelsTable::iterator end  = channels.end();
    while (it != end){
      CORBA::String_var str_ref = m_orb->object_to_string((*it).second);
      os << (*it).first << endl;
      os << str_ref << endl;
      it++;
    }

  } catch (...) {

    if (m_orb->trace != NULL)
      m_orb->print_trace(TIDorb::util::TR_ERROR, 
                         "ERROR saving EventChannelFactory");
  }
  
}
