/*
*  File name: EventReliabilityProperty.C
*  File type: Body file.
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
#include "EventReliabilityProperty.h"


TIDNotif::qos::EventReliabilityProperty::EventReliabilityProperty()
{
  value = 0;
}


TIDNotif::qos::EventReliabilityProperty::EventReliabilityProperty(
                                  const CosNotification::Property& property, 
                                  CORBA::Short val)
  : TIDNotif::qos::QoSProperty(property), value(val)
{
}


CORBA::Short TIDNotif::qos::EventReliabilityProperty::getValue()
{
  return value;
}

void TIDNotif::qos::EventReliabilityProperty::writeObject(ostream & out)
{
  out << value << endl;
}

void TIDNotif::qos::EventReliabilityProperty::readObject(istream & in)
{
  in >> value;

  property.name = CORBA::string_dup(CosNotification::EventReliability);
  property.value <<= value;
}


TIDNotif::qos::EventReliabilityProperty* 
TIDNotif::qos::EventReliabilityProperty::fromProperty(
                                   TIDNotif::qos::QoSAdmin& admin, 
                                   const CosNotification::Property& property,
                                   CosNotification::PropertyError*& error)
{
  try{
    
    CORBA::Short val;
    property.value >>= val;
            
    if ( (val != CosNotification::BestEffort) && 
         (val != CosNotification::Persistent) ) {
      error = QoSAdmin::createPropertyError(property);
      CosNotification::PropertyRange_var range = 
        admin.getEventReliabilityRange(); 
      error->available_range.low_val  = range->low_val;
      error->available_range.high_val = range->high_val;
      error->code = CosNotification::BAD_VALUE;
      return NULL;                
    }
            
    // no error
    error = NULL;
            
    return new EventReliabilityProperty(property, val);                        
            
  } catch (...) {
    error = QoSAdmin::createPropertyError(property);
    error->code = CosNotification::BAD_VALUE;            	
    CosNotification::PropertyRange_var range = 
      admin.getEventReliabilityRange(); 
    error->available_range.low_val  = range->low_val;
    error->available_range.high_val = range->high_val;
    return NULL;
  }
}
