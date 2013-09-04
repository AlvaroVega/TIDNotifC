/*
 *  File name: TimeoutProperty.C
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

#include "TimeoutProperty.h"

TIDNotif::qos::TimeoutProperty::TimeoutProperty()
{
  policy = NULL;
  value = 0;
}

TIDNotif::qos::TimeoutProperty::TimeoutProperty(
                               const CosNotification::Property& property, 
                               Messaging::RelativeRoundtripTimeoutPolicy_ptr pol,
                               TimeBase::TimeT val)
  : QoSProperty(property), policy(pol), value(val)
{
}


TIDNotif::qos::TimeoutProperty* 
TIDNotif::qos::TimeoutProperty::fromProperty(
                                  QoSAdmin& admin,
                                  const CosNotification::Property& property, 
                                  CosNotification::PropertyError*& error)
{

  CORBA::ORB_ptr orb = admin.getORB();
        
  try {
            
    CORBA::Policy_var pol = 
      orb->create_policy(Messaging::RELATIVE_RT_TIMEOUT_POLICY_TYPE,
                         property.value);
           
    Messaging::RelativeRoundtripTimeoutPolicy_ptr timeout_policy =
      Messaging::RelativeRoundtripTimeoutPolicy::_narrow(pol);
           
    return new TimeoutProperty(property,
                               timeout_policy, 
                               timeout_policy->relative_expiry());
  }
  catch (...) {                
    error = QoSAdmin::createPropertyError(property);
    error->code = CosNotification::BAD_VALUE;            	
    CosNotification::PropertyRange_var range = admin.getTimeoutRange();
    error->available_range.low_val  = range->low_val;
    error->available_range.high_val = range->high_val;
    return NULL; 
  }


}


TimeBase::TimeT TIDNotif::qos::TimeoutProperty::getValue()
{
  return value;
}

Messaging::RelativeRoundtripTimeoutPolicy_ptr 
TIDNotif::qos::TimeoutProperty::getPolicy(CORBA::ORB_ptr orb)
{
  TIDThr::Synchronized synchro(_recursive_mutex);

  if(policy == NULL) {
            
    try {
      CORBA::Policy_ptr pol = 
        orb->create_policy(Messaging::RELATIVE_RT_TIMEOUT_POLICY_TYPE,
                           property.value);
      policy = Messaging::RelativeRoundtripTimeoutPolicy::_narrow(pol);
    }
    catch (const CORBA::PolicyError& e) {
      throw CORBA::INTERNAL();
    }
  }
  
  return Messaging::RelativeRoundtripTimeoutPolicy::_duplicate(policy);

}

void TIDNotif::qos::TimeoutProperty::readObject(istream& in)
{
  in >> value;

  property.name = CORBA::string_dup(CosNotification::Timeout);
  property.value <<= value;
}

void TIDNotif::qos::TimeoutProperty::writeObject(ostream& out)
{
  out << value << endl;
}
