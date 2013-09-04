/*
 *  File name: ProxyQoSAdmin.C
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

#include "ProxyQoSAdmin.h"


CORBA::Long serialVersionUID = (CORBA::Long) 66666L;

CosNotification::NamedPropertyRangeSeq* 
TIDNotif::qos::ProxyQoSAdmin::st_available_properties = NULL;

TIDNotif::qos::ProxyQoSAdmin::ProxyQoSAdmin(CORBA::ORB_ptr orb)
  : TIDNotif::qos::QoSAdmin(orb)
{
}

CosNotification::PropertyError_ptr 
TIDNotif::qos::ProxyQoSAdmin::validate(EventReliabilityProperty& property)
{
  if(property.getValue() == CosNotification::Persistent) {
    return createUnsupportedProperty(property.getProperty()); 
  }
  
  return NULL;
}

CosNotification::PropertyError_ptr 
TIDNotif::qos::ProxyQoSAdmin::validate(StartTimeProperty& property)
{
  return createBadProperty(property.getProperty());
}

CosNotification::PropertyError_ptr 
TIDNotif::qos::ProxyQoSAdmin::validate(StopTimeProperty& property)
{
  return createBadProperty(property.getProperty());
}

CosNotification::PropertyError_ptr 
TIDNotif::qos::ProxyQoSAdmin::validate(QueueOrderProperty& property)
{
  return createBadProperty(property.getProperty());
}

CosNotification::NamedPropertyRangeSeq* 
TIDNotif::qos::ProxyQoSAdmin::getAvailableQoS()
{

  TIDThr::Synchronized synchro(TIDNotif::qos::QoSAdmin::_recursive_mutex);

  if(st_available_properties == NULL) {                
    
    CosNotification::NamedPropertyRangeSeq* tmp = 
      new CosNotification::NamedPropertyRangeSeq;
    
    tmp->length(5);

    (*tmp)[0] = *(new CosNotification::NamedPropertyRange(CosNotification::ConnectionReliability,
                                                          *getConnectionReliabilityRange()));
    (*tmp)[1] = *(new CosNotification::NamedPropertyRange(CosNotification::Priority, 
                                                          *getPriorityRange()));
    (*tmp)[2] = *(new CosNotification::NamedPropertyRange(CosNotification::Timeout, 
                                                          *getTimeoutRange()));
    (*tmp)[3] = *(new CosNotification::NamedPropertyRange(CosNotification::StartTimeSupported, 
                                                          *getBooleanRange()));
    (*tmp)[4] = *(new CosNotification::NamedPropertyRange(CosNotification::StopTimeSupported, 
                                                          *getBooleanRange()));
    st_available_properties = tmp; 

  }

  return st_available_properties;

}
