/*
*  File name: QueueOrderProperty.h
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
#include "QueueOrderProperty.h"


TIDNotif::qos::QueueOrderProperty::QueueOrderProperty()
{
  policy = NULL;
  value = 0;
}


TIDNotif::qos::QueueOrderProperty::QueueOrderProperty(
                               const CosNotification::Property& property,
                               Messaging::QueueOrderPolicy_ptr pol, 
                               CORBA::Short val)
  : QoSProperty(property), policy(pol), value(val)
{
}

CORBA::Short TIDNotif::qos::QueueOrderProperty::getValue()
{
  return value;
}


TIDNotif::qos::QueueOrderProperty* 
TIDNotif::qos::QueueOrderProperty::fromProperty(
                                     QoSAdmin& admin, 
                                     const CosNotification::Property& property,
                                     CosNotification::PropertyError*& error)
{
  CORBA::ORB_ptr orb = admin.getORB();
  TIDorb::core::TIDORB* _orb = dynamic_cast < TIDorb::core::TIDORB* > (orb);

  try {
    
    CORBA::Short order;
    property.value >>= order;
    
    
    Messaging::Ordering order_value = 0;
    
    switch(order) {
    case CosNotification::AnyOrder:
      order_value = Messaging::ORDER_ANY;
      break;
    case CosNotification::FifoOrder:
      order_value = Messaging::ORDER_TEMPORAL;
      break;
    case CosNotification::PriorityOrder:
      order_value = Messaging::ORDER_PRIORITY;
      break;
    case CosNotification::DeadlineOrder:
      order_value = Messaging::ORDER_DEADLINE;
      break;
    default:
      error = new CosNotification::PropertyError();
      error->code = CosNotification::BAD_VALUE;
      error->name = property.name;
      CosNotification::PropertyRange_var range = admin.getOrderRange(); 
      error->available_range.low_val  = range->low_val;
      error->available_range.high_val = range->high_val;
      return NULL;
    }
    
    CORBA::Any_var policy_value = _orb->create_any();
    
    (*policy_value) <<= order_value;        
    
    CORBA::Policy_var pol = 
      orb->create_policy(Messaging::QUEUE_ORDER_POLICY_TYPE, 
                         policy_value);
    Messaging::QueueOrderPolicy_ptr policy = 
      Messaging::QueueOrderPolicy::_narrow(pol);

    return new QueueOrderProperty(property, policy, order);
  }
  catch (...){ 
    error = QoSAdmin::createPropertyError(property);
    error->code = CosNotification::BAD_VALUE;        	
    CosNotification::PropertyRange_var range = admin.getOrderRange(); 
    error->available_range.low_val  = range->low_val;
    error->available_range.high_val = range->high_val;
    return NULL;            
  }            
  
  

}



  
void TIDNotif::qos::QueueOrderProperty::writeObject(ostream & out)
{
  out << value << endl;
}

void TIDNotif::qos::QueueOrderProperty::readObject(istream & in)
{
  in >> value;
  property.name = CORBA::string_dup(CosNotification::OrderPolicy);
  property.value <<= value;
}

Messaging::QueueOrderPolicy_ptr 
TIDNotif::qos::QueueOrderProperty::getPolicy(CORBA::ORB_ptr orb)
{
  TIDThr::Synchronized synchro(_recursive_mutex);

  TIDorb::core::TIDORB* _orb = dynamic_cast < TIDorb::core::TIDORB* > (orb);

  if (policy == NULL) {

    try {

      CORBA::Short order_value = 0;

      switch(value) {
      case CosNotification::AnyOrder:
        order_value = Messaging::ORDER_ANY;
        break;
      case CosNotification::FifoOrder:
        order_value = Messaging::ORDER_TEMPORAL;
        break;
      case CosNotification::PriorityOrder:
        order_value = Messaging::ORDER_PRIORITY;
        break;
      case CosNotification::DeadlineOrder:
        order_value = Messaging::ORDER_DEADLINE;
        break;
      default:
        throw CORBA::INTERNAL();
      }
      CORBA::Any_var policy_value = _orb->create_any();
      *policy_value <<= order_value;
      
      CORBA::Policy_ptr pol = 
        orb->create_policy(Messaging::QUEUE_ORDER_POLICY_TYPE, 
                           policy_value);

      policy = Messaging::QueueOrderPolicy::_narrow(pol);

    }
    catch (const CORBA::PolicyError& e) {
      throw CORBA::INTERNAL();
    }
  }
  return Messaging::QueueOrderPolicy::_duplicate(policy);
}

