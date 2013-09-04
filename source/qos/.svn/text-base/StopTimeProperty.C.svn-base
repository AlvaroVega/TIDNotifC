/*
 *  File name: StopTimeProperty.C
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

#include "StopTimeProperty.h"

TIDNotif::qos::StopTimeProperty::StopTimeProperty()
{
  policy = NULL;
  value = new TimeBase::UtcT(0,0,0,0);
}

TIDNotif::qos::StopTimeProperty::StopTimeProperty(
                                   const CosNotification::Property& property,
                                   Messaging::RequestEndTimePolicy_ptr pol,
                                   TimeBase::UtcT val)
  : TIDNotif::qos::QoSProperty(property), policy(pol), value(val)
{

}


TIDNotif::qos::StopTimeProperty* 
TIDNotif::qos::StopTimeProperty::fromProperty(
                                   QoSAdmin& admin,
                                   const CosNotification::Property& property, 
                                   CosNotification::PropertyError*& error)
{

  CORBA::ORB_ptr orb = admin.getORB();

  try {
    
    CORBA::Policy_var pol = 
      orb->create_policy(Messaging::REQUEST_END_TIME_POLICY_TYPE,
                         property.value);
           
    Messaging::RequestEndTimePolicy_ptr stop_policy =
      Messaging::RequestEndTimePolicy::_narrow(pol);
    
    return new StopTimeProperty(property,
                                stop_policy, 
                                stop_policy->end_time());
  }
  catch (...) {                
    error = QoSAdmin::createPropertyError(property);
    error->code = CosNotification::BAD_VALUE;     
    CosNotification::PropertyRange_var range = admin.getTimeRange(); 
    error->available_range.low_val  = range->low_val; 
    error->available_range.high_val = range->high_val;         	
    return NULL; 
  }

}


TimeBase::UtcT_ptr TIDNotif::qos::StopTimeProperty::getValue()
{
  return value;
}


Messaging::RequestEndTimePolicy_ptr 
TIDNotif::qos::StopTimeProperty::getPolicy(CORBA::ORB_ptr orb)
{

  TIDThr::Synchronized synchro(_recursive_mutex);

  if (policy == NULL) {
    try {
      CORBA::Policy_ptr pol = 
        orb->create_policy(Messaging::REQUEST_END_TIME_POLICY_TYPE,
                           property.value);
      policy = Messaging::RequestEndTimePolicy::_narrow(pol);
    }
    catch (const CORBA::PolicyError& e) {
      throw CORBA::INTERNAL();
    }        
  }
  return Messaging::RequestEndTimePolicy::_duplicate(policy);
}


void TIDNotif::qos::StopTimeProperty::readObject(istream& in)
{
  in >> value->time;
  in >> value->inacclo;
  in >> value->inacchi;
  in >> value->tdf;

  property.name = CORBA::string_dup(CosNotification::StopTime);
  property.value <<= *value;
}


void TIDNotif::qos::StopTimeProperty::writeObject(ostream& out)
{
  out << value->time    << endl;
  out << value->inacclo << endl;
  out << value->inacchi << endl;
  out << value->tdf     << endl;
}
