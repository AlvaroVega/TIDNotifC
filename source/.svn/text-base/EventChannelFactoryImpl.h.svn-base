// -*- c++ -*-
/*
 *  File name: EventChannelFactoryImpl.h
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

#ifndef _TIDNOTIFICATION_EVENT_CHANNEL_FACTORYImpl_H_
#define _TIDNOTIFICATION_EVENT_CHANNEL_FACTORYImpl_H_

/**
 * Implementation of EventChannelFactory.
 * @version 1.0
*/
#include "POA_CosNotifyChannelAdmin.h"

#include <istream>
#include <ostream>
#include <map>

#ifdef TIDORB_HAVE_NAMESPACE_STD
using namespace std;
#endif

#ifdef __SUNPRO_LIBRARY_IOSTREAM
using std::map;
using std::string;
#endif

using namespace CosNotifyChannelAdmin;



namespace TIDNotif{

class EventChannelFactoryImpl : 
    public virtual POA_CosNotifyChannelAdmin::EventChannelFactory,
    public virtual TIDThr::RefCounter{

private:

  TIDorb::core::TIDORB*  m_orb;

  // POAs: channel and Notification Service
  PortableServer::POA_var m_channel_poa;
  PortableServer::POA_var m_tidnotif_poa;
  
  // Counter of unique ids of channels
  ChannelID m_counterID;

  typedef map<ChannelID, EventChannel_var> ChannelsTable;
  ChannelsTable channels;

  TIDThr::RecursiveMutex m_recursive_mutex;

  int m_channel_POA_config;

public:
  
  EventChannelFactoryImpl(TIDorb::core::TIDORB* orb, 
                          PortableServer::POA_ptr poa)
    throw (PortableServer::POA::InvalidPolicy, CORBA::SystemException);

  ~EventChannelFactoryImpl() throw (TIDThr::SystemException);

  EventChannel_ptr 
  create_channel(const CosNotification::QoSProperties& initial_qos, 
                 const CosNotification::AdminProperties& initial_admin, 
                 ChannelID& id)
    throw (CosNotification::UnsupportedQoS, CosNotification::UnsupportedAdmin);
  
  ChannelIDSeq* get_all_channels();
  
  EventChannel_ptr get_event_channel(ChannelID id)
    throw (ChannelNotFound);


  // Persistence Management
  void readObject(istream & is);
  void writeObject(ostream & os);
};

} //TIDNotif

#endif
