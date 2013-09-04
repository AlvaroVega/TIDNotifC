/*
 *  File name: EventChannelData.C
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

#include "EventChannelData.h"


TIDNotif::EventChannelData::EventChannelData(TIDorb::core::TIDORB* orb, 
                                             PortableServer::POA_ptr poa,
                                             CosNotifyChannelAdmin::ChannelID id,
                                             EventChannelFactoryImpl* factory)
  : m_orb(orb), m_channel_poa(poa), m_id(id)
{


  // Obtain the back reference to channel factory
  if (factory != NULL) {
    CORBA::Object_var obj = 
      m_channel_poa->the_parent()->servant_to_reference(factory);
    m_MyFactory = CosNotifyChannelAdmin::EventChannelFactory::_narrow(obj);
  }
  else
    m_MyFactory = NULL;

  m_default_consumer_admin = NULL;
  m_default_supplier_admin = NULL;

  counterConsumerAdminID = 1;
  counterSupplierAdminID = 1;

  m_destroying = false;
   
  filterFactoryDelegate = new FilterFactoryImpl(m_orb);
  qosAdminDelegate      = new TIDNotif::qos::ChannelQoSAdmin(m_orb);

}


TIDNotif::EventChannelData::~EventChannelData()
{
  if (m_orb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "Deleting EventChannel with id " << m_id; 
    m_orb->print_trace(TIDorb::util::TR_DEBUG, msg.str().data());
  }

//   if (!_destroying)
//     this->destroy();

  if (filterFactoryDelegate) 
    delete filterFactoryDelegate;
  if (qosAdminDelegate) 
    delete qosAdminDelegate; 
}


// Persistence Management

void TIDNotif::EventChannelData::readObject(istream & is)
{


}


void TIDNotif::EventChannelData::writeObject(ostream & os)
{

  
}
