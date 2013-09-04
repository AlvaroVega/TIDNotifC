/*
 *  File name: StartTimeSupportedProperty.C
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

#include "StartTimeSupportedProperty.h"


TIDNotif::qos::StartTimeSupportedProperty::StartTimeSupportedProperty()
{
  value = 0;
}

TIDNotif::qos::StartTimeSupportedProperty::StartTimeSupportedProperty(
                                     const CosNotification::Property& property,
                                     CORBA::Boolean val)
  : QoSProperty(property), value(val)
{
}

CORBA::Boolean TIDNotif::qos::StartTimeSupportedProperty::getValue()
{
  return value;
}

void TIDNotif::qos::StartTimeSupportedProperty::readObject(istream& in)
{
  in >> value;

  property.name = CORBA::string_dup(CosNotification::StartTimeSupported);
  property.value <<= CORBA::Any::from_boolean(value);
}
  
void TIDNotif::qos::StartTimeSupportedProperty::writeObject(ostream& out)
{
  out << value << endl; 
}


TIDNotif::qos::StartTimeSupportedProperty* 
TIDNotif::qos::StartTimeSupportedProperty::fromProperty(
                                     QoSAdmin& admin,
                                     const CosNotification::Property& property, 
                                     CosNotification::PropertyError*& error)
{
  CORBA::Boolean value;
  property.value >>= value;
  
  return new StartTimeSupportedProperty(property, value);
}
