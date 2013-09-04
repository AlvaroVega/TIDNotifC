// -*- c++ -*-
/*
 *  File name: ProxyPushSupplierImpl.h
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

#ifndef _INTERNAL_PROXY_PUSH_SUPPLIERImpl_H_
#define _INTERNAL_PROXY_PUSH_SUPPLIERImpl_H_

/**
 * Implementation of InternalProxyPushSupplier
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

class ProxyPushSupplierImpl : 
    public virtual POA_NotificationInternals::InternalProxyPushSupplier {

private:

  TIDorb::core::TIDORB* m_orb;

  PortableServer::POA_var m_proxy_supplier_poa;

  TIDThr::RecursiveMutex m_recursive_mutex;

  PortableServer::Current_var m_current;

  typedef map<TIDorb::core::poa::OID, 
              ProxyPushSupplierData*> ProxyPushSupplierDataTable;
  ProxyPushSupplierDataTable m_proxy_push_suppliers;

  int m_consumer_POA_config;

public:

  ProxyPushSupplierImpl(TIDorb::core::TIDORB* orb, 
                        PortableServer::POA_ptr _poa);

  ~ProxyPushSupplierImpl();

private:

  TIDNotif::ProxyPushSupplierData* getData();
  
public:

  void register_proxy(TIDNotif::ProxyPushSupplierData* data);

  void unregister_proxy(TIDNotif::ProxyPushSupplierData* data);


  // NotificationInternals::InternalProxySupplierConsumer operations

  void push_event(const CORBA::Any& data);
		
  void destroyFromAdmin();
		
  void loadData();


  // CosNotifyComm::StructuredPushSupplier operations

  void disconnect_structured_push_supplier();


  // CosNotifyComm::NotifySubscribe

  void subscription_change(const CosNotification::EventTypeSeq& added, 
                           const CosNotification::EventTypeSeq& removed);


  // CosNotifyFilter::FilterAdmin		

  CosNotifyFilter::FilterID add_filter(CosNotifyFilter::Filter_ptr filter);
		
  void remove_filter(CosNotifyFilter::FilterID filter)
    throw (CosNotifyFilter::FilterNotFound); 
		
  CosNotifyFilter::Filter_ptr get_filter(CosNotifyFilter::FilterID filter)
    throw (CosNotifyFilter::FilterNotFound);
		
  CosNotifyFilter::FilterIDSeq* get_all_filters();

  void remove_all_filters();


  // CosEventComm::PushSupplier	

  void disconnect_push_supplier();


  // CosEventChannelAdmin::ProxyPushSupplier		

  void connect_push_consumer(CosEventComm::PushConsumer_ptr push_consumer)
    throw (CosEventChannelAdmin::AlreadyConnected, 
           CosEventChannelAdmin::TypeError);


  // CosNotifyChannelAdmin::ProxyPushSupplier		

  void connect_any_push_consumer(CosEventComm::PushConsumer_ptr push_consumer)
    throw (CosEventChannelAdmin::AlreadyConnected, 
           CosEventChannelAdmin::TypeError);


  // CosNotifyChannelAdmin::StructuredProxyPullConsumer
  // CosNotifyChannelAdmin::ProxyPushSupplier

  void suspend_connection()
    throw (CosNotifyChannelAdmin::ConnectionAlreadyInactive, 
           CosNotifyChannelAdmin::NotConnected);

  void resume_connection()
    throw (CosNotifyChannelAdmin::ConnectionAlreadyActive, 
           CosNotifyChannelAdmin::NotConnected);
  

  // CosNotification::QoSAdmin operations
		
  CosNotification::QoSProperties* get_qos();

  void set_qos(const CosNotification::QoSProperties& qos)
    throw (CosNotification::UnsupportedQoS);

  void validate_qos(const CosNotification::QoSProperties& required_qos, 
                    CosNotification::NamedPropertyRangeSeq*& available_qos)
    throw (CosNotification::UnsupportedQoS);


  // CosNotifyChannelAdmin::ProxySupplier operations

  CosNotifyChannelAdmin::ProxyType MyType();

  CosNotifyChannelAdmin::ConsumerAdmin_ptr MyAdmin();

  CosNotifyFilter::MappingFilter_ptr priority_filter();
  void priority_filter(CosNotifyFilter::MappingFilter_ptr value);

  CosNotifyFilter::MappingFilter_ptr lifetime_filter();
  void lifetime_filter(CosNotifyFilter::MappingFilter_ptr value);
		
  CosNotification::EventTypeSeq* 
  obtain_offered_types(CosNotifyChannelAdmin::ObtainInfoMode mode);
		
  void validate_event_qos(const CosNotification::QoSProperties& required_qos, 
                          CosNotification::NamedPropertyRangeSeq*& available_qos)
    throw (CosNotification::UnsupportedQoS);
  

  // CosNotifyChannelAdmin::StructuredProxyPushSupplier operations
		
  void connect_structured_push_consumer(
                         CosNotifyComm::StructuredPushConsumer_ptr push_consumer)
    throw (CosEventChannelAdmin::AlreadyConnected);


  CosNotifyChannelAdmin::ProxyID getProxyID();
  // Persistence Management

  void readObject(istream & is);
  void writeObject(ostream & os);

};

} //TIDNotif

#endif
