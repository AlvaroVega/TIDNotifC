/*
*  File name: StopTimeSupportedProperty.h
*  File type: Header file.
*  Date : 6th March 2006
*  Author: Tomás Aguado Gómez <taguado@gsyc.escet.urjc.es>
*/

/*
* Copyright (C) 2006 Telefónica I+D S.A.
*
* This source file is a property of Telefónica I+D. You can not
* use it for any purpose unless you have an explicit authorization
* by owner.
*/
#include "StopTimeSupportedProperty.h"

TIDNotif::qos::StopTimeSupportedProperty::StopTimeSupportedProperty()
{
  value = 0;
}

TIDNotif::qos::StopTimeSupportedProperty::StopTimeSupportedProperty(
                                    const CosNotification::Property& property,
                                    CORBA::Boolean val)
  : TIDNotif::qos::QoSProperty(property), value(val)
{
}

void TIDNotif::qos::StopTimeSupportedProperty::writeObject(ostream & out)
{
  out << value << endl;
}

void TIDNotif::qos::StopTimeSupportedProperty::readObject(istream & in)
{
  in >> value;
  
  property.name = CORBA::string_dup(CosNotification::StopTimeSupported);
  property.value <<= CORBA::Any::from_boolean(value);
}

CORBA::Boolean TIDNotif::qos::StopTimeSupportedProperty::getValue()
{
  return value;
}

TIDNotif::qos::StopTimeSupportedProperty* 
TIDNotif::qos::StopTimeSupportedProperty::fromProperty(
                                    QoSAdmin& admin,
                                    const CosNotification::Property& property,
                                    CosNotification::PropertyError*& error)
{
  CORBA::Boolean value;
  property.value >>= value;
  
  return new StopTimeSupportedProperty(property, value);
}
