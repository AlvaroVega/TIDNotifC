// -*- c++ -*-
/*
 *  File name: EventChannelImpl.h
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

#include "TIDNotif.h"

#ifndef _TIDNOTIFICATION_EVENT_CHANNELImpl_H_
#define _TIDNOTIFICATION_EVENT_CHANNELImpl_H_

/**
 * Implementation of DistributionEventChannel.
 * @version 1.0
 */

#include "POA_NotificationInternals.h"

#include <map>

#ifdef TIDORB_HAVE_NAMESPACE_STD
using namespace std;
#endif

#ifdef __SUNPRO_LIBRARY_IOSTREAM
using std::map;
using std::string;
#endif

using namespace NotificationInternals;

namespace TIDNotif{

class EventChannelImpl : 
    public virtual POA_NotificationInternals::InternalDistributionChannel
{

private:
  TIDorb::core::TIDORB* m_orb;

  //PortableServer::POA_var m_factory_poa;
  PortableServer::POA_var m_channel_poa;
  PortableServer::POA_var m_consumer_admin_poa;
  PortableServer::POA_var m_supplier_admin_poa;

  PortableServer::Current_var m_current;

  typedef map<TIDorb::core::poa::OID, 
              EventChannelData*> EventChannelDataTable;
  EventChannelDataTable _channels;
  
  TIDThr::RecursiveMutex m_recursive_mutex;

  CosNotification::QoSProperties* qosProperties;

  bool m_persistent;

  int m_consumer_POA_config;
  int m_supplier_POA_config;
  int m_channel_POA_config;

public:
  
  EventChannelImpl(TIDorb::core::TIDORB* orb, PortableServer::POA_ptr poa,
                   EventChannelFactoryImpl* factory,
                   const CosNotification::QoSProperties& initial_qos,
                   const CosNotification::AdminProperties& initial_admin);
  
  ~EventChannelImpl();

private:

  TIDNotif::EventChannelData* getData();
  
public:

  void register_channel(TIDNotif::EventChannelData* data);

  void unregister_channel(TIDNotif::EventChannelData* data);


  // NotificationInternals::InternalDistributionChannel 

  void dispatch_event(const CORBA::Any& data);

  void removeSupplierAdmin(CosNotifyChannelAdmin::AdminID id);

  void removeConsumerAdmin(CosNotifyChannelAdmin::AdminID id);

  void loadData(); // may be unnecesary


  //  CosNotifyFilter::FilterFactory
  
  CosNotifyFilter::Filter* create_filter(const char* constraint_grammar)
    throw (CosNotifyFilter::InvalidGrammar);

  CosNotifyFilter::MappingFilter* 
  create_mapping_filter(const char* constraint_grammar, 
                        const CORBA::Any& default_value)
    throw (CosNotifyFilter::InvalidGrammar);
  

  // CosNotifyChannelAdmin::EventChannel 
  // readonly atributes

  CosNotifyChannelAdmin::EventChannelFactory_ptr MyFactory();

  CosNotifyChannelAdmin::ConsumerAdmin_ptr default_consumer_admin();

  CosNotifyChannelAdmin::SupplierAdmin_ptr default_supplier_admin();

  CosNotifyFilter::FilterFactory_ptr default_filter_factory();

  CosNotifyChannelAdmin::ConsumerAdmin_ptr 
  new_for_consumers(CosNotifyChannelAdmin::InterFilterGroupOperator op, 
                    CosNotifyChannelAdmin::AdminID& id);
		
  CosNotifyChannelAdmin::SupplierAdmin_ptr 
  new_for_suppliers(CosNotifyChannelAdmin::InterFilterGroupOperator op, 
                    CosNotifyChannelAdmin::AdminID& id);
		
  CosNotifyChannelAdmin::ConsumerAdmin_ptr 
  get_consumeradmin(CosNotifyChannelAdmin::AdminID id)
    throw (CosNotifyChannelAdmin::AdminNotFound);
  
  CosNotifyChannelAdmin::SupplierAdmin_ptr 
  get_supplieradmin(CosNotifyChannelAdmin::AdminID id)
    throw (CosNotifyChannelAdmin::AdminNotFound);
		
  CosNotifyChannelAdmin::AdminIDSeq* get_all_consumeradmins();
		
  CosNotifyChannelAdmin::AdminIDSeq* get_all_supplieradmins();


  // CosEvent::EventChannel operations

  CosNotifyChannelAdmin::ConsumerAdmin_ptr for_consumers();

  CosNotifyChannelAdmin::SupplierAdmin_ptr for_suppliers();

  CosNotifyChannelAdmin::ChannelID get_channelID();

  void destroy();


  // CosNotification::AdminPropertiesAdmin operations

  CosNotification::AdminProperties* get_admin();

  void set_admin(const CosNotification::AdminProperties& admin)
    throw (CosNotification::UnsupportedAdmin);


  // CosNotification::QoSAdmin operations

  CosNotification::QoSProperties* get_qos();

  void set_qos(const CosNotification::QoSProperties& qos)
    throw (CosNotification::UnsupportedQoS);

  void validate_qos(const CosNotification::QoSProperties& required_qos, 
                    CosNotification::NamedPropertyRangeSeq*& available_qos)
    throw (CosNotification::UnsupportedQoS);


  // Persistence Management

  void readObject(istream & is);

  void writeObject(ostream & os);

};

} //TIDNotif


#endif
