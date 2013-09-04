/*
*  File name: QoSProperty.C
*  File File type: Body.
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
#include "QoSProperty.h"

TIDNotif::qos::QoSProperty::QoSProperty()
{
}


TIDNotif::qos::QoSProperty::QoSProperty(const CosNotification::Property& prop)
{
  property.name  = CORBA::string_dup(prop.name);
  property.value = prop.value; // deep copy
}


const char* TIDNotif::qos::QoSProperty::getName()
{
  return CORBA::string_dup(property.name);
}


CosNotification::Property& TIDNotif::qos::QoSProperty::getProperty()
{
  return property;
}


bool TIDNotif::qos::QoSProperty::operator == (const CORBA::Object* obj) const 
{
  const QoSProperty* other = dynamic_cast<const QoSProperty*>(obj);
  if(other)
    return ( (strcmp(property.name, other->property.name) == 0) && 
             (property.value == other->property.value) );
  return false;
}


CORBA::TypeCode_ptr TIDNotif::qos::QoSProperty::_type() const 
{
  return CORBA::TypeCode::_duplicate(CosNotification::_tc_Property);
}



