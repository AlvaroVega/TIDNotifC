/*
 *  File name: ChannelQoSAdmin.C
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

#include "ChannelQoSAdmin.h"

CosNotification::NamedPropertyRangeSeq*
TIDNotif::qos::ChannelQoSAdmin::st_available_properties = NULL;


TIDNotif::qos::ChannelQoSAdmin::ChannelQoSAdmin(CORBA::ORB_ptr orb)
  : TIDNotif::qos::QoSAdmin(orb)
{
}


/** 
 * Overrided method. Property not supported 
 * for this kind of Notification elements
 * @see es.tid.corba.TIDNotif.qos.QoSAdmin#validate(es.tid.corba.TIDNotif.qos.StartTimeProperty)
 */
CosNotification::PropertyError_ptr 
TIDNotif::qos::ChannelQoSAdmin::validate(StartTimeProperty& property)
{
  return createBadProperty(property.getProperty());
}


CosNotification::PropertyError_ptr 
TIDNotif::qos::ChannelQoSAdmin::validate(StopTimeProperty& property)
{
  return createBadProperty(property.getProperty());
}
    

/**
 * Validates if this property is supported. By default, all property values
 * are valid. 
 * @param property 
 * @return error if not supported
 */    
CosNotification::PropertyError_ptr 
TIDNotif::qos::ChannelQoSAdmin::validate(EventReliabilityProperty& property)
{
  if(property.getValue() == CosNotification::Persistent) {
    return createUnsupportedProperty(property.getProperty()); 
  }
  
  return NULL;
}
  
/* (non-Javadoc)
 * @see es.tid.corba.TIDNotif.qos.QoSAdmin#getAvailableQoS()
 */
CosNotification::NamedPropertyRangeSeq* 
TIDNotif::qos::ChannelQoSAdmin::getAvailableQoS()
{
  TIDThr::Synchronized synchro(TIDNotif::qos::QoSAdmin::_recursive_mutex);

  if(st_available_properties == NULL) {                
    
    CosNotification::NamedPropertyRangeSeq* tmp = 
      new CosNotification::NamedPropertyRangeSeq;
    
    tmp->length(6);

    (*tmp)[0] = *(new CosNotification::NamedPropertyRange(CosNotification::EventReliability, 
                                                          *getEventReliabilityRange()));
    (*tmp)[1] = *(new CosNotification::NamedPropertyRange(CosNotification::ConnectionReliability,
                                                          *getConnectionReliabilityRange()));
    (*tmp)[2] = *(new CosNotification::NamedPropertyRange(CosNotification::Priority, 
                                                          *getPriorityRange()));
    (*tmp)[3] = *(new CosNotification::NamedPropertyRange(CosNotification::Timeout, 
                                                          *getTimeoutRange()));
    (*tmp)[4] = *(new CosNotification::NamedPropertyRange(CosNotification::StartTimeSupported, 
                                                          *getBooleanRange()));
    (*tmp)[5] = *(new CosNotification::NamedPropertyRange(CosNotification::StopTimeSupported, 
                                                          *getBooleanRange()));
    st_available_properties = tmp; 

  }

  return st_available_properties;

}

/**
 * Create the EventReliability property. Only BestEfford is available in the
 * current version of TIDNotif.
 * @return
 */
CosNotification::PropertyRange_ptr 
TIDNotif::qos::ChannelQoSAdmin::getEventReliabilityRange()
{
  CosNotification::PropertyRange_ptr event_reliability = 
    QoSAdmin::getEventReliabilityRange();               
        
  event_reliability->high_val <<= CosNotification::BestEffort; 
  
  return event_reliability;
}
