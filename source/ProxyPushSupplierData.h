// -*- c++ -*-
/*
 *  File name: ProxuPushSupplierData.h
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

#ifndef _INTERNAL_PROXY_PUSH_SUPPLIER_DATA_H_
#define _INTERNAL_PROXY_PUSH_SUPPLIER_DATA_H_

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

class ProxyPushSupplierData : 
    public TIDNotif::CommonData {

private:

  TIDorb::core::TIDORB* m_orb;

  PortableServer::POA_var m_proxy_supplier_poa;

public:

  CORBA::Boolean connected;

  CORBA::Boolean _destroying;

  CosNotifyChannelAdmin::ProxyID _id;

  CosNotifyChannelAdmin::AdminID _admin_id;

  CosNotifyChannelAdmin::ChannelID _channel_id;

  InternalConsumerAdmin_var _consumer_admin;

  CosEventComm::PushConsumer_var _push_consumer;

  CosNotifyComm::StructuredPushConsumer_var _structured_push_consumer;

  CORBA::Boolean notify_style; // Is a notification service style push supplier

  CosNotifyChannelAdmin::ProxyType _type;

  //TIDThr::RecursiveMutex _recursive_mutex;

  FilterAdminImpl* filterAdminDelegate;

  TIDNotif::qos::ProxyQoSAdmin* qosAdminDelegate;

public:

  ProxyPushSupplierData(TIDorb::core::TIDORB* orb, 
                        PortableServer::POA_ptr _poa,
                        CosNotifyChannelAdmin::ProxyID id,
                        CosNotifyChannelAdmin::AdminID admin_id,
                        CosNotifyChannelAdmin::ChannelID channel_id);

  ~ProxyPushSupplierData();

  // Persistence Management

  void readObject(istream & is);
  void writeObject(ostream & os);

};

} //TIDNotif

#endif
