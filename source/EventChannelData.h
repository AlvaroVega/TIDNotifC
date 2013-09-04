// -*- c++ -*-
/*
 *  File name: EventChannelData.h
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

#ifndef _TIDNOTIFICATION_EVENT_CHANNEL_DATA_H_
#define _TIDNOTIFICATION_EVENT_CHANNEL_DATA_H_

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

  typedef map<CosNotifyChannelAdmin::AdminID, 
              NotificationInternals::InternalConsumerAdmin_var> consumerAdminTable;

  typedef map<CosNotifyChannelAdmin::AdminID, 
              NotificationInternals::InternalSupplierAdmin_var> supplierAdminTable;

class EventChannelData : 
    public TIDNotif::CommonData
{

private:

  TIDorb::core::TIDORB* m_orb;

  PortableServer::POA_var m_channel_poa;

public:

  CosNotifyChannelAdmin::EventChannelFactory_ptr m_MyFactory; 

  CosNotifyChannelAdmin::ChannelID m_id;

  InternalConsumerAdmin_ptr m_default_consumer_admin;
  InternalSupplierAdmin_ptr m_default_supplier_admin;

  consumerAdminTable m_consumerAdmins;
  supplierAdminTable m_supplierAdmins;

  // Counters of unique ids of admins
  CosNotifyChannelAdmin::AdminID counterConsumerAdminID;
  CosNotifyChannelAdmin::AdminID counterSupplierAdminID;

  bool m_destroying;

  FilterFactoryImpl* filterFactoryDelegate;  
  TIDNotif::qos::ChannelQoSAdmin* qosAdminDelegate;

public:
  
  EventChannelData(TIDorb::core::TIDORB* orb, PortableServer::POA_ptr poa,
                   CosNotifyChannelAdmin::ChannelID id, 
                   EventChannelFactoryImpl* factory);
  
  ~EventChannelData();


  // Persistence Management

  void readObject(istream & is);

  void writeObject(ostream & os);

};

} //TIDNotif


#endif
