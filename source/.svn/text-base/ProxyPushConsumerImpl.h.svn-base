// -*- c++ -*-
/*
 *  File name: ProxyPushConsumerImpl.h
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

#ifndef _INTERNAL_PROXY_PUSH_CONSUMERImpl_H_
#define _INTERNAL_PROXY_PUSH_CONSUMERImpl_H_

/**
 * Implementation of InternalProxyPushConsumer
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

class ProxyPushConsumerImpl : 
    public virtual POA_NotificationInternals::InternalProxyPushConsumer
{

private:

  TIDorb::core::TIDORB* m_orb;

  PortableServer::POA_var m_proxy_consumer_poa;

  TIDThr::RecursiveMutex m_recursive_mutex;

  PortableServer::Current_var m_current;

  typedef map<TIDorb::core::poa::OID, 
              ProxyPushConsumerData*> ProxyPushConsumerDataTable;
  ProxyPushConsumerDataTable m_proxy_push_consumers;

  int m_supplier_POA_config;

public:

  ProxyPushConsumerImpl(TIDorb::core::TIDORB* orb, 
                        PortableServer::POA_ptr poa);

  ~ProxyPushConsumerImpl();

private:

  TIDNotif::ProxyPushConsumerData* getData();
  
public:

  void register_proxy(TIDNotif::ProxyPushConsumerData* data);

  void unregister_proxy(TIDNotif::ProxyPushConsumerData* data);


  // NotificationInternals::InternalProxyPushConsumer operations

  void ipush(const CORBA::Any& data); // may be obsolete
  
  void destroyFromAdmin();
		
  void loadData();


  // CosEventComm::PushConsummer operations

  void push(const CORBA::Any& data) throw (CosEventComm::Disconnected);

  void disconnect_push_consumer();


  // CosEventChannelAdmin::ProxyPushConsumer operations

  void connect_push_supplier(CosEventComm::PushSupplier_ptr push_supplier)
    throw (CosEventChannelAdmin::AlreadyConnected);


  // CosNotifyChannelAdmin::ProxyPushConsumer operations

  void connect_any_push_supplier(CosEventComm::PushSupplier_ptr push_supplier)
    throw (CosEventChannelAdmin::AlreadyConnected);
  

  // CosNotifyFilter::FilterAdmin

  CosNotifyFilter::FilterID add_filter(CosNotifyFilter::Filter_ptr filter);
		
  void remove_filter(CosNotifyFilter::FilterID filter)
    throw (CosNotifyFilter::FilterNotFound);  
		
  CosNotifyFilter::Filter_ptr get_filter(CosNotifyFilter::FilterID filter)
    throw (CosNotifyFilter::FilterNotFound);
		
  CosNotifyFilter::FilterIDSeq* get_all_filters();
		
  void remove_all_filters();


  // CosNotifyChannelAdmin::StructuredProxyPushConsumer operations

  void connect_structured_push_supplier(
                     CosNotifyComm::StructuredPushSupplier_ptr push_supplier)
    throw(CosEventChannelAdmin::AlreadyConnected);


  // CosNotifyChannelAdmin::ProxyConsumer operations
  
  CosNotifyChannelAdmin::ProxyType MyType();

  CosNotifyChannelAdmin::SupplierAdmin_ptr MyAdmin();
		
  CosNotification::EventTypeSeq* 
  obtain_subscription_types(CosNotifyChannelAdmin::ObtainInfoMode mode);
		
  void validate_event_qos(const CosNotification::QoSProperties& required_qos, 
                          CosNotification::NamedPropertyRangeSeq*& available_qos)
    throw (CosNotification::UnsupportedQoS);


  // CosNotifyComm::NotifyPublish operations

  void offer_change(const CosNotification::EventTypeSeq& added, 
                    const CosNotification::EventTypeSeq& removed)
    throw (CosNotifyComm::InvalidEventType);


  // CosNotification::QoSAdmin operations

  CosNotification::QoSProperties* get_qos();

  void set_qos(const CosNotification::QoSProperties& qos)
    throw (CosNotification::UnsupportedQoS);

  void validate_qos(const CosNotification::QoSProperties& required_qos, 
                    CosNotification::NamedPropertyRangeSeq*& available_qos)
    throw (CosNotification::UnsupportedQoS);


  // CosNotifyComm::StructuredPushConsumer operations

  void push_structured_event(const CosNotification::StructuredEvent& notification)
    throw (CosNotification::UnsupportedQoS, CosEventComm::Disconnected);

  void disconnect_structured_push_consumer();

  CosNotifyChannelAdmin::ProxyID getProxyID ();
  
  // Persistence Management

  void readObject(istream & is);
  void writeObject(ostream & os);

};

} //TIDNotif

#endif
