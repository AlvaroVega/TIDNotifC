/*
 *  File name: ConnectionReliabilityProperty.C
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

#include "ConnectionReliabilityProperty.h"


TIDNotif::qos::ConnectionReliabilityProperty::ConnectionReliabilityProperty()
{
  value = 0;
}


TIDNotif::qos::ConnectionReliabilityProperty::ConnectionReliabilityProperty(
                                     const CosNotification::Property& property, 
                                     CORBA::Short val)
  : TIDNotif::qos::QoSProperty(property), value(val)
{
}


TIDNotif::qos::ConnectionReliabilityProperty* 
TIDNotif::qos::ConnectionReliabilityProperty::fromProperty(
                                     QoSAdmin& admin,
                                     const CosNotification::Property& property,
                                     CosNotification::PropertyError*& error)
{ 

  try {
    CORBA::Short val;
    property.value >>= val;

    //    short value = property.value.extract_short();
    
    if( (val != CosNotification::BestEffort) && 
        (val != CosNotification::Persistent) ) {
      error = QoSAdmin::createPropertyError(property);
      CosNotification::PropertyRange_var range = 
        admin.getConnectionReliabilityRange(); 
      error->available_range.low_val  = range->low_val;
      error->available_range.high_val = range->high_val;
      //      error->available_range
      error->code = CosNotification::BAD_VALUE;
      return NULL;                
    }
    
    // no error
    error = NULL;
    
    return new ConnectionReliabilityProperty(property, val);
    
    
    
  } catch (...) {
    error = QoSAdmin::createPropertyError(property);
    error->code = CosNotification::BAD_VALUE;       
    CosNotification::PropertyRange_var range = 
      admin.getConnectionReliabilityRange(); 
    error->available_range.low_val  = range->low_val;
    error->available_range.high_val = range->high_val;     	
    return NULL;
  }


}

CORBA::Short 
TIDNotif::qos::ConnectionReliabilityProperty::getValue()
{
  return value;
}


void TIDNotif::qos::ConnectionReliabilityProperty::readObject(istream& in)
{
  in >> value;

  property.name = CORBA::string_dup(CosNotification::ConnectionReliability);
  property.value <<= value;
}

void TIDNotif::qos::ConnectionReliabilityProperty::writeObject(ostream& out)
{
  out << value << endl; 
}
