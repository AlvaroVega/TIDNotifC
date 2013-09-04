// -*- c++ -*-
/*
 *  File name: SupplierAdminData.h
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

#ifndef _SUPPLIER_ADMIN_DATA_H_
#define _SUPPLIER_ADMIN_DATA_H_

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
  
typedef map<CosNotifyChannelAdmin::ProxyID, 
            InternalProxyPushConsumer_var> proxyPushConsumerMap;

class SupplierAdminData :
    public TIDNotif::CommonData {

private:
  TIDorb::core::TIDORB* m_orb;

  PortableServer::POA_var m_supplier_admin_poa;

public:

  CosNotifyChannelAdmin::AdminID _id;

  InternalDistributionChannel_ptr _channel;

  CosNotifyChannelAdmin::ChannelID _channel_id;

  proxyPushConsumerMap proxyPushConsumers;
  
  CosNotifyChannelAdmin::AdminID counterProxyPushConsumer;

  TIDThr::RecursiveMutex _recursive_mutex;

  bool _destroying;

  FilterAdminImpl* filterAdminDelegate;

  TIDNotif::qos::ProxyQoSAdmin* qosAdminDelegate;

  CosNotifyChannelAdmin::InterFilterGroupOperator m_operator;

public:
  
  SupplierAdminData(TIDorb::core::TIDORB* orb, 
                    PortableServer::POA_ptr poa,
                    CosNotifyChannelAdmin::AdminID id, 
                    CosNotifyChannelAdmin::ChannelID channel_id,
                    CosNotifyChannelAdmin::InterFilterGroupOperator op);

  ~SupplierAdminData();


  // Persistence Management

  void readObject(istream & is);
  void writeObject(ostream & os);

};

} //TIDNotif

#endif
