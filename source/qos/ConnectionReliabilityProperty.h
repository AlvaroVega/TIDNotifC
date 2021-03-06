// -*- c++ -*-
/*
 *  File name: ConnectionReliabilityProperty.h
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

#ifndef _TIDNOTIF_QOS_CONNECTIONRELIABILITYPROPERTY_H_
#define _TIDNOTIF_QOS_CONNECTIONRELIABILITYPROPERTY_H_


#include "CosNotification.h"

#ifdef TIDORB_HAVE_NAMESPACE_STD
using namespace std;
#endif

namespace TIDNotif{
namespace qos{

class ConnectionReliabilityProperty: public QoSProperty{

private:
  CORBA::Short value;
    
protected:
  ConnectionReliabilityProperty(const CosNotification::Property& property, 
                                CORBA::Short value);

public:
  ConnectionReliabilityProperty();

  static ConnectionReliabilityProperty* 
  fromProperty(QoSAdmin& admin,
               const CosNotification::Property& property, 
               CosNotification::PropertyError*& error);

  CORBA::Short getValue();

  void readObject(istream& in);

  void writeObject(ostream& out);
  
};

}
}
#endif
