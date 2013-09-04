/*
 *  File name: PriorityProperty.C
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

#include "PriorityProperty.h"

TIDNotif::qos::PriorityProperty::PriorityProperty()
{
  policy = NULL;
  value = 0;
}

TIDNotif::qos::PriorityProperty::PriorityProperty(
                                  const CosNotification::Property& property, 
                                  Messaging::RequestPriorityPolicy_ptr pol,
                                  CORBA::Short val)
  : QoSProperty(property), policy(pol), value(val)
{

}


TIDNotif::qos::PriorityProperty* 
TIDNotif::qos::PriorityProperty::fromProperty(
                                  QoSAdmin& admin,
                                  const CosNotification::Property& property, 
                                  CosNotification::PropertyError*& error)
{
 CORBA::ORB_ptr orb = admin.getORB();
 TIDorb::core::TIDORB* _orb = dynamic_cast < TIDorb::core::TIDORB* > (orb);

 try {
   CORBA::Short priority;
   property.value >>= priority;
   
   Messaging::PriorityRange_var range = 
     new Messaging::PriorityRange;
            
   range->max <<= priority;
   range->min <<= priority;
   
   CORBA::Any_var priority_value = _orb->create_any();
   
   priority_value <<= *range;
   
   CORBA::Policy_var pol = 
     orb->create_policy(Messaging::REQUEST_PRIORITY_POLICY_TYPE,
                        priority_value);

   Messaging::RequestPriorityPolicy_ptr policy = 
      Messaging::RequestPriorityPolicy::_narrow(pol);
   
   return new PriorityProperty(property, policy, priority);
   
   
 }
 catch (...) {                
   error = QoSAdmin::createPropertyError(property);
   error->code = CosNotification::BAD_VALUE;   
   CosNotification::PropertyRange_var range = admin.getPriorityRange();           	
   error->available_range.low_val  = range->low_val;
   error->available_range.high_val = range->high_val;
   return NULL; 
 } 
 

}


CORBA::Short TIDNotif::qos::PriorityProperty::getValue()
{
  return value;
}

Messaging::RequestPriorityPolicy_ptr 
TIDNotif::qos::PriorityProperty::getPolicy(CORBA::ORB_ptr orb)
{
  TIDThr::Synchronized synchro(_recursive_mutex);

  TIDorb::core::TIDORB* _orb = dynamic_cast < TIDorb::core::TIDORB* > (orb);

  if (policy == NULL) {

    CosNotification::PropertyRange_var range = 
      CosNotification::PropertyRange();

    range->high_val <<= value;
    range->low_val  <<= value;
            
    CORBA::Any_var priority_value = _orb->create_any();
            
    priority_value <<= *range;
            
    try {

      CORBA::Policy_ptr pol = 
        orb->create_policy(Messaging::REQUEST_PRIORITY_POLICY_TYPE,
                           priority_value);

      policy = Messaging::RequestPriorityPolicy::_narrow(pol);

    }
    catch (const CORBA::PolicyError& e) {
      throw CORBA::INTERNAL();
    }
            
  }
  return policy;

}

void TIDNotif::qos::PriorityProperty::readObject(istream& in)
{
  // Read value
  in >> value;

  property.name = CORBA::string_dup(CosNotification::Priority);
  property.value <<= value;
}

void TIDNotif::qos::PriorityProperty::writeObject(ostream& out)
{
  out << value << endl; 
}
