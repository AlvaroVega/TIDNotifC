/*
 *  File name: ConsumerAdminData.C
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

#include "ConsumerAdminData.h"


TIDNotif::ConsumerAdminData::ConsumerAdminData(
                             TIDorb::core::TIDORB* orb, 
                             PortableServer::POA_ptr poa,
                             CosNotifyChannelAdmin::AdminID id,
                             CosNotifyChannelAdmin::ChannelID channel_id,
                             CosNotifyChannelAdmin::InterFilterGroupOperator op):
  m_orb(orb), m_consumer_admin_poa(poa), _id(id), _channel_id(channel_id), m_operator(op)
{
  counterProxyPushSupplier = 0;
  // Obtain the back reference to channel
  TIDorb::util::StringBuffer id_str;
  id_str << "Channel_" << channel_id;
  PortableServer::ObjectId_var oid = 
    PortableServer::string_to_ObjectId(id_str.str().data()); 
  CORBA::Object_var obj = m_consumer_admin_poa->the_parent()->create_reference_with_id(oid, 
                                                    _InternalDistributionChannelHelper::id());  
  _channel = InternalDistributionChannel::_narrow(obj);
  _destroying = false;
  
  priority_discriminator = NULL;
  lifetime_discriminator = NULL;

  filterAdminDelegate = new FilterAdminImpl();
  qosAdminDelegate    = new TIDNotif::qos::ProxyQoSAdmin(m_orb);
}


TIDNotif::ConsumerAdminData::~ConsumerAdminData()
{
  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "Deleting ConsumerAdminData with id " << _id; 
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }

  if (qosAdminDelegate) 
    delete qosAdminDelegate;
  if (filterAdminDelegate) 
    delete filterAdminDelegate;
  if (priority_discriminator) 
    CORBA::release(priority_discriminator);
  if (lifetime_discriminator) 
    CORBA::release(lifetime_discriminator);

}





void TIDNotif::ConsumerAdminData::readObject(istream & is)
{

}

void TIDNotif::ConsumerAdminData::writeObject(ostream & os)
{

}
