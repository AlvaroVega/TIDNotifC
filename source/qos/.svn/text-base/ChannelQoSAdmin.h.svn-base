// -*- c++ -*-
/*
 *  File name: ChannelQoSAdmin.h
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

#include "qos.h"

#ifndef _TIDNOTIF_QOS_CHANNELQOSADMIN_H_
#define _TIDNOTIF_QOS_CHANNELQOSADMIN_H_

#include "CosNotification.h"

namespace TIDNotif{
namespace qos{
  

class ChannelQoSAdmin : public virtual TIDNotif::qos::QoSAdmin{
  
public:

  static CosNotification::NamedPropertyRangeSeq* st_available_properties;
  
  /**
   * @param orb
   */
  ChannelQoSAdmin(CORBA::ORB_ptr orb);

    
protected:
    
  /** 
   * Overrided method. Property not supported 
   * for this kind of Notification elements
   * @see es.tid.corba.TIDNotif.qos.QoSAdmin#validate(es.tid.corba.TIDNotif.qos.StartTimeProperty)
   */
  CosNotification::PropertyError_ptr 
  validate(StartTimeProperty& property);
    
  CosNotification::PropertyError_ptr 
  validate(StopTimeProperty& property);
    

  /**
   * Validates if this property is supported. By default, all property values
   * are valid. 
   * @param property 
   * @return error if not supported
   */    
  CosNotification::PropertyError_ptr 
  validate(EventReliabilityProperty& property);
  
  /* (non-Javadoc)
   * @see es.tid.corba.TIDNotif.qos.QoSAdmin#getAvailableQoS()
   */
  CosNotification::NamedPropertyRangeSeq* 
  getAvailableQoS();

  /**
   * Create the EventReliability property. Only BestEfford is available in the
   * current version of TIDNotif.
   * @return
   */
  CosNotification::PropertyRange_ptr 
  getEventReliabilityRange();

};

}
}
#endif
