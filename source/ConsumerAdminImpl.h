// -*- c++ -*-
/*
 *  File name: ConsumerAdminImpl.h
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

#ifndef _CONSUMER_ADMINImpl_H_
#define _CONSUMER_ADMINImpl_H_

/**
 * Implementation of InternalConsumerAdmin.
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

class ConsumerAdminImpl: 
    public virtual POA_NotificationInternals::InternalConsumerAdmin{

private:

  TIDorb::core::TIDORB* m_orb;

  PortableServer::POA_var m_consumer_admin_poa;

  PortableServer::POA_var m_proxy_supplier_poa;

  TIDThr::RecursiveMutex m_recursive_mutex;

  PortableServer::Current_var m_current;

  typedef map<TIDorb::core::poa::OID, 
              ConsumerAdminData*> ConsumerAdminDataTable;
  ConsumerAdminDataTable m_consumer_admins;

  int m_consumer_POA_config;

public:
  
  ConsumerAdminImpl(TIDorb::core::TIDORB* orb, PortableServer::POA_ptr _poa);

  ~ConsumerAdminImpl();
  
private:

  TIDNotif::ConsumerAdminData* getData();
  
public:

  void register_admin(TIDNotif::ConsumerAdminData* data);

  void unregister_admin(TIDNotif::ConsumerAdminData* data);


  // NotificationInternals::InternalConsumerAdmin

  void dispatch_event(const CORBA::Any& data);
 
  CosNotifyChannelAdmin::AdminID getAdminId();

  void removeProxyPushSupplier(CosNotifyChannelAdmin::ProxyID id);
  
  void removeProxyPullSupplier(CosNotifyChannelAdmin::ProxyID id);
		
  void destroyFromChannel();
  
  void loadData();


  // CosNotifyChannelAdmin::ConsumerAdmin

  CosNotifyChannelAdmin::AdminID MyID();

  CosNotifyChannelAdmin::EventChannel_ptr MyChannel();

  CosNotifyChannelAdmin::InterFilterGroupOperator MyOperator();

  CosNotifyFilter::MappingFilter_ptr priority_filter();
  void priority_filter(CosNotifyFilter::MappingFilter_ptr value);

  CosNotifyFilter::MappingFilter_ptr lifetime_filter();
  void lifetime_filter(CosNotifyFilter::MappingFilter_ptr value);

  CosNotifyChannelAdmin::ProxyIDSeq* pull_suppliers();

  CosNotifyChannelAdmin::ProxyIDSeq* push_suppliers();
		
  CosNotifyChannelAdmin::ProxySupplier_ptr 
  get_proxy_supplier(CosNotifyChannelAdmin::ProxyID proxy_id)
    throw (CosNotifyChannelAdmin::ProxyNotFound);
		
  CosNotifyChannelAdmin::ProxySupplier_ptr 
  obtain_notification_pull_supplier(CosNotifyChannelAdmin::ClientType ctype, 
                                    CosNotifyChannelAdmin::ProxyID& proxy_id)
    throw (CosNotifyChannelAdmin::AdminLimitExceeded);
	
  CosNotifyChannelAdmin::ProxySupplier_ptr 
  obtain_notification_push_supplier(CosNotifyChannelAdmin::ClientType ctype, 
                                    CosNotifyChannelAdmin::ProxyID& proxy_id)
    throw (CosNotifyChannelAdmin::AdminLimitExceeded);

  void destroy();


  // CosEventChannelAdmin::ConsumerAdmin operations

  CosEventChannelAdmin::ProxyPushSupplier_ptr obtain_push_supplier();

  CosEventChannelAdmin::ProxyPullSupplier_ptr obtain_pull_supplier();


  // CosNotifyFilter::FilterAdmin operations

  CosNotifyFilter::FilterID add_filter(CosNotifyFilter::Filter_ptr filter);

  void remove_filter(CosNotifyFilter::FilterID)
    throw (CosNotifyFilter::FilterNotFound);  

  CosNotifyFilter::Filter_ptr get_filter(CosNotifyFilter::FilterID filter)
    throw (CosNotifyFilter::FilterNotFound);

  CosNotifyFilter::FilterIDSeq* get_all_filters();

  void remove_all_filters();


  // CosNotification::QoSAdmin operations

  CosNotification::QoSProperties* get_qos();

  void set_qos(const CosNotification::QoSProperties& qos)
    throw (CosNotification::UnsupportedQoS);

  void validate_qos(const CosNotification::QoSProperties& required_qos, 
                    CosNotification::NamedPropertyRangeSeq*& available_qos)
    throw (CosNotification::UnsupportedQoS);


  // CosNotifyComm::NotifySubscribe operations

  void subscription_change(const CosNotification::EventTypeSeq& added, 
                           const CosNotification::EventTypeSeq& removed)
    throw (CosNotifyComm::InvalidEventType);


  // Persistence Management

  void readObject(istream & is);
  void writeObject(ostream & os);

};

} //TIDNotif

#endif
