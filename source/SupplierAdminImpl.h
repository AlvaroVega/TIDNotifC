// -*- c++ -*-
/*
 *  File name: SupplierAdminImpl.h
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

#ifndef _SUPPLIER_ADMINImpl_H_
#define _SUPPLIER_ADMINImpl_H_

/**
 * Implementation of InternalSupplierAdmin.
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


class SupplierAdminImpl : 
    public virtual POA_NotificationInternals::InternalSupplierAdmin{

private:
  TIDorb::core::TIDORB* m_orb;

  PortableServer::POA_var m_supplier_admin_poa;

  PortableServer::POA_var m_proxy_consumer_poa;

  TIDThr::RecursiveMutex m_recursive_mutex;

  PortableServer::Current_var m_current;

  typedef map<TIDorb::core::poa::OID, 
              SupplierAdminData*> SupplierAdminDataTable;
  SupplierAdminDataTable m_supplier_admins;

  int m_supplier_POA_config;

public:
  
  SupplierAdminImpl(TIDorb::core::TIDORB* orb, PortableServer::POA_ptr poa);

  ~SupplierAdminImpl();

private:

  TIDNotif::SupplierAdminData* getData();
  
public:

  void register_admin(TIDNotif::SupplierAdminData* data);

  void unregister_admin(TIDNotif::SupplierAdminData* data);


  // NotificationInternals::InternalSupplierAdmin

  void push_event(const CORBA::Any& data);

  CosNotifyChannelAdmin::AdminID getAdminId();

  void removeProxyPushConsumer(CosNotifyChannelAdmin::ProxyID id);

  void removeProxyPullConsumer(CosNotifyChannelAdmin::ProxyID id);

  void destroyFromChannel();

  void loadData();


  // CosNotifyChannelAdmin::SupplierAdmin

  CosNotifyChannelAdmin::AdminID MyID();

  CosNotifyChannelAdmin::EventChannel_ptr MyChannel();

  CosNotifyChannelAdmin::InterFilterGroupOperator MyOperator();

  CosNotifyFilter::MappingFilter_ptr priority_filter();
  void priority_filter(CosNotifyFilter::MappingFilter_ptr value);

  CosNotifyFilter::MappingFilter_ptr lifetime_filter();
  void lifetime_filter(CosNotifyFilter::MappingFilter_ptr value);

  CosNotifyChannelAdmin::ProxyIDSeq* pull_consumers();

  CosNotifyChannelAdmin::ProxyIDSeq* push_consumers();
		
  CosNotifyChannelAdmin::ProxyConsumer_ptr 
  get_proxy_consumer(CosNotifyChannelAdmin::ProxyID proxy_id)
    throw (CosNotifyChannelAdmin::ProxyNotFound);
  
  CosNotifyChannelAdmin::ProxyConsumer_ptr 
  obtain_notification_pull_consumer(CosNotifyChannelAdmin::ClientType ctype, 
                                    CosNotifyChannelAdmin::ProxyID& proxy_id)
    throw (CosNotifyChannelAdmin::AdminLimitExceeded);
	
  CosNotifyChannelAdmin::ProxyConsumer_ptr 
  obtain_notification_push_consumer(CosNotifyChannelAdmin::ClientType ctype, 
                                    CosNotifyChannelAdmin::ProxyID& proxy_id)
    throw (CosNotifyChannelAdmin::AdminLimitExceeded);

  void destroy();


  // CosEventChannelAdmin::SupplierAdmin

  CosEventChannelAdmin::ProxyPushConsumer_ptr obtain_push_consumer();

  CosEventChannelAdmin::ProxyPullConsumer_ptr obtain_pull_consumer();


  // CosNotifyFilter::FilterAdmin operations

  CosNotifyFilter::FilterID add_filter(CosNotifyFilter::Filter_ptr new_filter);
		
  void remove_filter(CosNotifyFilter::FilterID filter)
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


  // CosNotifyComm::NotifyPublish operations

  void offer_change(const CosNotification::EventTypeSeq& added, 
                    const CosNotification::EventTypeSeq& removed)
    throw (CosNotifyComm::InvalidEventType);


  // Persistence Management

  void readObject(istream & is);
  void writeObject(ostream & os);

};

} //TIDNotif

#endif
