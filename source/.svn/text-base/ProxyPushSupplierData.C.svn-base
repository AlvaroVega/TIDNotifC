/*
 *  File name: ProxyPushSupplierData.C
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

#include "ProxyPushSupplierData.h"

TIDNotif::ProxyPushSupplierData::ProxyPushSupplierData(
                                  TIDorb::core::TIDORB* orb, 
                                  PortableServer::POA_ptr poa, 
                                  CosNotifyChannelAdmin::ProxyID id,
                                  CosNotifyChannelAdmin::AdminID admin_id,
                                  CosNotifyChannelAdmin::ChannelID channel_id)
  : m_orb(orb), m_proxy_supplier_poa(PortableServer::POA::_duplicate(poa)), 
    _id(id), _admin_id(admin_id), _channel_id(channel_id)
{
  // Obtain the back reference to consumer admin
  TIDorb::util::StringBuffer id_str;
  id_str << "ConsumerAdmin_" << _channel_id << "_" << admin_id;
  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(id_str.str().data()); 
  CORBA::Object_var obj = 
    m_proxy_supplier_poa->the_parent()->create_reference_with_id(oid, 
                                          _InternalConsumerAdminHelper::id());  
  _consumer_admin = InternalConsumerAdmin::_narrow(obj);

  connected    = false;
  notify_style = false;
  _destroying  = false;

  filterAdminDelegate = new TIDNotif::FilterAdminImpl();
  qosAdminDelegate    = new TIDNotif::qos::ProxyQoSAdmin(m_orb);

  _push_consumer = NULL;
  _structured_push_consumer = NULL;

}


TIDNotif::ProxyPushSupplierData::~ProxyPushSupplierData()
{
  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "Deleting ProxyPushSupplierData with id " << _id; 
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }

  if (filterAdminDelegate)
    delete filterAdminDelegate;
  if (qosAdminDelegate)
    delete qosAdminDelegate;
}


void TIDNotif::ProxyPushSupplierData::readObject(istream & is)
{
 
}


void TIDNotif::ProxyPushSupplierData::writeObject(ostream & os)
{

}

