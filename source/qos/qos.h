// -*- c++ -*-
/*
 *  File name: qos.h
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

#ifndef __TIDNOTIF_QOS_H__
#define __TIDNOTIF_QOS_H__

#include "TIDorb/config.h"
#include "TIDorb/core.h"
#include "TIDorb/util.h"
#include "TIDThr.h"


#include "CORBA.h"
#include "PortableServer.h"

namespace TIDNotif{
namespace qos{

// Some forward declarations
class QoSProperty;
class QoSAdmin;
class EventReliabilityProperty;
class ConnectionReliabilityProperty;
class StartTimeSupportedProperty;
class StopTimeSupportedProperty;
class PriorityProperty;
class StartTimeProperty;
class StopTimeProperty;
class TimeoutProperty;
class QueueOrderProperty;
class ChannelQoSAdmin;
class EventQoSAdmin;
class ProxyQoSAdmin;

}
}

#include "QoSProperty.h"

#include "ConnectionReliabilityProperty.h"
#include "EventReliabilityProperty.h"
#include "QueueOrderProperty.h"
#include "StartTimeProperty.h"         
#include "StartTimeSupportedProperty.h"
#include "StopTimeProperty.h"
#include "StopTimeSupportedProperty.h"
#include "TimeoutProperty.h"
#include "PriorityProperty.h"

#include "QoSAdmin.h"
#include "ChannelQoSAdmin.h"
#include "EventQoSAdmin.h"
#include "ProxyQoSAdmin.h"


#endif

