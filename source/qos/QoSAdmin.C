/*
 *  File name: QoSAdmin.C
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

#include "QoSAdmin.h"


TIDNotif::qos::QoSAdmin::PropertiesMapT* 
TIDNotif::qos::QoSAdmin::st_global_supported_properties = 
  TIDNotif::qos::QoSAdmin::initGlobalSupportedProperties();


TIDNotif::qos::QoSAdmin::QoSAdmin()
{
  m_orb = NULL;
  m_properties = NULL;
  m_policies = NULL;

  eventReliabilityProperty      = NULL;
  connectionReliabilityProperty = NULL;
  startTimeSupportedProperty    = NULL;
  stopTimeSupportedProperty     = NULL;
  priorityProperty              = NULL;
  startTimeProperty             = NULL;
  stopTimeProperty              = NULL;
  timeoutProperty               = NULL;
  queueOrderProperty            = NULL;

  m_properties_updated = false;
}
  
TIDNotif::qos::QoSAdmin::QoSAdmin(CORBA::ORB_ptr orb)
{
  m_orb = orb;
  m_properties = NULL;
  m_policies = NULL;

  eventReliabilityProperty      = NULL;
  connectionReliabilityProperty = NULL;
  startTimeSupportedProperty    = NULL;
  stopTimeSupportedProperty     = NULL;
  priorityProperty              = NULL;
  startTimeProperty             = NULL;
  stopTimeProperty              = NULL;
  timeoutProperty               = NULL;
  queueOrderProperty            = NULL;

  m_properties_updated = false;
}


TIDNotif::qos::QoSAdmin::~QoSAdmin()
{
  delete eventReliabilityProperty;
  delete connectionReliabilityProperty;
  delete startTimeSupportedProperty;    
  delete stopTimeSupportedProperty;     
  delete priorityProperty;              
  delete startTimeProperty;            
  delete stopTimeProperty;             
  delete timeoutProperty;              
  delete queueOrderProperty;           
}


  
CORBA::ORB_ptr TIDNotif::qos::QoSAdmin::getORB()
{
  return m_orb;
}

void TIDNotif::qos::QoSAdmin::setORB(CORBA::ORB_ptr orb)
{
  m_orb = orb;
}
    
/**
 * @return Returns the connectionReliabilityProperty.
 */
TIDNotif::qos::ConnectionReliabilityProperty* 
TIDNotif::qos::QoSAdmin::getConnectionReliabilityProperty()
{
  return connectionReliabilityProperty;
}

/**
 * @return Returns the eventReliabilityProperty.
 */
TIDNotif::qos::EventReliabilityProperty* 
TIDNotif::qos::QoSAdmin::getEventReliabilityProperty()
{
  return eventReliabilityProperty;
}
    
/**
 * @return Returns the priorityProperty.
 */
TIDNotif::qos::PriorityProperty* 
TIDNotif::qos::QoSAdmin::getPriorityProperty()
{
  return priorityProperty;
}

/**
 * @return Returns the queueOrderProperty.
 */
TIDNotif::qos::QueueOrderProperty* 
TIDNotif::qos::QoSAdmin::getQueueOrderProperty()
{
  return queueOrderProperty;
}

/**
 * @return Returns the startTimeProperty.
 */
TIDNotif::qos::StartTimeProperty* 
TIDNotif::qos::QoSAdmin::getStartTimeProperty()
{
  return startTimeProperty;
}

/**
 * @return Returns the startTimeSupportedProperty.
 */
TIDNotif::qos::StartTimeSupportedProperty* 
TIDNotif::qos::QoSAdmin::getStartTimeSupportedProperty()
{
  return startTimeSupportedProperty;
}

/**
 * @return Returns the stopTimeProperty.
 */
TIDNotif::qos::StopTimeProperty* 
TIDNotif::qos::QoSAdmin::getStopTimeProperty()
{
  return stopTimeProperty;
}

/**
 * @return Returns the stopTimeSupportedProperty.
 */
TIDNotif::qos::StopTimeSupportedProperty* 
TIDNotif::qos::QoSAdmin::getStopTimeSupportedProperty()
{
  return stopTimeSupportedProperty;
}

/**
 * @return Returns the timeoutProperty.
 */
TIDNotif::qos::TimeoutProperty* 
TIDNotif::qos::QoSAdmin::getTimeoutProperty()
{
  return timeoutProperty;
}

/***************************************
 * CosNotification::QoSAdmin operatons *
 ***************************************/
    
    
    
CosNotification::QoSProperties* TIDNotif::qos::QoSAdmin::get_qos()
{
  TIDThr::Synchronized synchro(_recursive_mutex);

  if (m_properties == NULL || (!m_properties_updated) ) {

    if (!m_properties_updated)
      delete m_properties;

    m_properties = new CosNotification::QoSProperties;
    CORBA::ULong _length = 0;
    
    if(eventReliabilityProperty != NULL) {
      m_properties->length(++_length);
      (*m_properties)[_length - 1].name = CORBA::string_dup("EventReliability");
      (*m_properties)[_length - 1].value <<= eventReliabilityProperty->getValue();
    }
    if(connectionReliabilityProperty != NULL) {
      m_properties->length(++_length);
      (*m_properties)[_length - 1].name = CORBA::string_dup("ConnectionReliability");
      (*m_properties)[_length - 1].value <<= connectionReliabilityProperty->getValue();
    }
    if(startTimeSupportedProperty != NULL) {
      m_properties->length(++_length);
      (*m_properties)[_length - 1].name = CORBA::string_dup("StartTimeSupported");
      (*m_properties)[_length - 1].value <<= startTimeSupportedProperty->getValue();
    }
    if(stopTimeSupportedProperty != NULL) {
      m_properties->length(++_length);
      (*m_properties)[_length - 1].name = CORBA::string_dup("StopTimeSupported");
      (*m_properties)[_length - 1].value <<= stopTimeSupportedProperty->getValue();
    }
    if(priorityProperty != NULL) {
      m_properties->length(++_length);
      (*m_properties)[_length - 1].name = CORBA::string_dup("Priority");
      (*m_properties)[_length - 1].value <<= priorityProperty->getValue();
    }
    if(startTimeProperty != NULL) {
      m_properties->length(++_length);
      (*m_properties)[_length - 1].name = CORBA::string_dup("StartTime");
      (*m_properties)[_length - 1].value <<= startTimeProperty->getValue();
    }
    if(stopTimeProperty != NULL) {
      m_properties->length(++_length);
      (*m_properties)[_length - 1].name = CORBA::string_dup("StopTime");
      (*m_properties)[_length - 1].value <<= stopTimeProperty->getValue();
    }
    if(timeoutProperty != NULL) {
      m_properties->length(++_length);
      (*m_properties)[_length - 1].name = CORBA::string_dup("Timeout");
      (*m_properties)[_length - 1].value <<= timeoutProperty->getValue();
    }
    if(queueOrderProperty != NULL) {
      m_properties->length(++_length);
      (*m_properties)[_length - 1].name = CORBA::string_dup("OrderPolicy");
      (*m_properties)[_length - 1].value <<= queueOrderProperty->getValue();
    }
    m_properties_updated = true; 
  }
        
  return m_properties;

}

void TIDNotif::qos::QoSAdmin::set_qos(const CosNotification::QoSProperties& qos)
  throw (CosNotification::UnsupportedQoS)
{
  TIDThr::Synchronized synchro(_recursive_mutex);

  m_properties_updated = false;
//   delete m_properties;
//   m_properties = NULL;
  
  // parse and validate all properties
  CosNotification::QoSProperties* properties = validate(qos);
  
  commit((const CosNotification::QoSProperties&)*properties);

  delete properties;
}
  
CORBA::PolicyList* TIDNotif::qos::QoSAdmin::getPolicies()
{
  
  TIDThr::Synchronized synchro(_recursive_mutex);

  CORBA::ULong _length = 0;

  if (m_policies == NULL)  
    _length = 0;
  else 
    _length = m_policies->length();



  if (_length == 0)  {
    
    m_policies = new CORBA::PolicyList();

    CORBA::Policy_ptr policy = NULL;
    
    if(priorityProperty != NULL) {
      m_policies->length(++_length);
      policy = CORBA::Policy::_narrow(priorityProperty->getPolicy(m_orb));
      (*m_policies)[_length - 1] = policy;
    }
    if(startTimeProperty != NULL) {
      m_policies->length(++_length);
      policy = CORBA::Policy::_narrow(startTimeProperty->getPolicy(m_orb));
      (*m_policies)[_length - 1] = policy;
    }
    if(stopTimeProperty != NULL) {
      m_policies->length(++_length);
      policy = CORBA::Policy::_narrow(stopTimeProperty->getPolicy(m_orb));
      (*m_policies)[_length - 1] = policy;
    }   
    if(timeoutProperty != NULL) {
      m_policies->length(++_length);
      policy = CORBA::Policy::_narrow(timeoutProperty->getPolicy(m_orb));
      (*m_policies)[_length - 1] = policy;
    }
    if(queueOrderProperty != NULL) {
      m_policies->length(++_length);
      policy = CORBA::Policy::_narrow(queueOrderProperty->getPolicy(m_orb));
      (*m_policies)[_length - 1] = policy;
    }
    
  }
  
  return m_policies;

}
  
void TIDNotif::qos::QoSAdmin::validate_qos(
                       const CosNotification::QoSProperties& required_qos,
                       CosNotification::NamedPropertyRangeSeq*& available_qos)
  throw (CosNotification::UnsupportedQoS)
{
  CosNotification::QoSProperties* qos_properties = validate(required_qos);       
  delete qos_properties; 
  available_qos = new CosNotification::NamedPropertyRangeSeq(*getAvailableQoS());
}
     
/*
 * Implementation operations
 */
    
/**
 * Set deffinitively validated properties
 * @param properties vector of QoSProperty 
 */
void TIDNotif::qos::QoSAdmin::commit(
                      const CosNotification::QoSProperties& properties)
{
  int size = properties.length();

  for(int i = 0; i < size; i++) {
    this->setProperty(properties[i]);
  }

}
        

    
/**
 * Sets a validaded property     
 * @param property
 */
    
void TIDNotif::qos::QoSAdmin::setProperty(
                      const CosNotification::Property& property)
{

  QoSPropertyType type = TIDNotif::qos::NOTYPE;
  type = (*st_global_supported_properties)[property.name];
        
  if (type == TIDNotif::qos::NOTYPE) {
    throw CORBA::INTERNAL("Unexpected property");
  }
  CosNotification::PropertyError* error = NULL;

  switch (type) {
  case EVENT_RELIABILITY:  
    delete eventReliabilityProperty;
    eventReliabilityProperty = 
      TIDNotif::qos::EventReliabilityProperty::fromProperty(*this, property, error);
    break;
  case CONNECTION_RELIABILITY:
    delete connectionReliabilityProperty;
    connectionReliabilityProperty = 
      TIDNotif::qos::ConnectionReliabilityProperty::fromProperty(*this, property, error);
    break;
  case START_TIME_SUPPORTED:  
    delete startTimeSupportedProperty;
    startTimeSupportedProperty = 
      TIDNotif::qos::StartTimeSupportedProperty::fromProperty(*this, property, error);
    break;
  case STOP_TIME_SUPPORTED:
    delete stopTimeSupportedProperty;
    stopTimeSupportedProperty = 
      TIDNotif::qos::StopTimeSupportedProperty::fromProperty(*this, property, error);
    break;
  case PRIORITY:
    delete priorityProperty;
    priorityProperty = 
      TIDNotif::qos::PriorityProperty::fromProperty(*this, property, error);
    break;            
  case START_TIME:
    delete startTimeProperty;
    startTimeProperty = 
      TIDNotif::qos::StartTimeProperty::fromProperty(*this, property, error);
    break;                
  case STOP_TIME:
    delete stopTimeProperty;
    stopTimeProperty = 
      TIDNotif::qos::StopTimeProperty::fromProperty(*this, property, error);
    break;
  case TIMEOUT:
    delete timeoutProperty;
    timeoutProperty =
      TIDNotif::qos::TimeoutProperty::fromProperty(*this, property, error); 
    break;
  case ORDER_POLICY:
    delete queueOrderProperty;
    queueOrderProperty = 
      TIDNotif::qos::QueueOrderProperty::fromProperty(*this, property, error); 
    break; 
  default:
    break;
  }       
  
}
    
/**
 * Validates and process the Property to QoSProperty list
 * @param qos the QoS properties
 * @return the Processed QoSProperties
 * @throws UnsupportedQoS if any property is not supported
 */
CosNotification::QoSProperties*
TIDNotif::qos::QoSAdmin::validate(const CosNotification::QoSProperties& qos) 
  throw (CosNotification::UnsupportedQoS)
{
  // Reset values for get_pos & toPolicyList
  
  CosNotification::QoSProperties* qos_properties = 
    new CosNotification::QoSProperties;
  CORBA::ULong length_qos_properties = 0;

  QoSProperty* property = NULL;
  CosNotification::PropertyError* error = NULL;
  CosNotification::PropertyErrorSeq errors;
  CORBA::ULong length_errors = 0;

  for (CORBA::ULong i=0; i < qos.length(); i++) {
           
    error = NULL;
    property = toQoSProperty(qos[i], error);
    
    if (error == NULL) {  
      qos_properties->length(++length_qos_properties);
      (*qos_properties)[length_qos_properties - 1].name = CORBA::string_dup(qos[i].name);
      (*qos_properties)[length_qos_properties - 1].value = qos[i].value;
    } 
    else {
      errors.length(++length_errors);
      errors[length_errors - 1] = *error; 
      delete error;
      error = NULL;
    }

    // What can i do with property?
    delete property;
    property = NULL;

  } // for

        
  if(errors.length() > 0) {
            
    delete qos_properties;
    qos_properties = NULL;
            
    throw CosNotification::UnsupportedQoS(errors);
  }
        
  return qos_properties;    
}
   
/**
 * Validates if this property is supported. By default, all property values
 * are valid. Override these methods if not supported values exist.
 * @param property 
 * @return error if not supported
 */    
CosNotification::PropertyError_ptr 
TIDNotif::qos::QoSAdmin::validate(const EventReliabilityProperty& property)
{
  return NULL;
}


CosNotification::PropertyError_ptr 
TIDNotif::qos::QoSAdmin::validate(const ConnectionReliabilityProperty& property)
{
  return NULL;
}

    
CosNotification::PropertyError_ptr 
TIDNotif::qos::QoSAdmin::validate(const StartTimeSupportedProperty&  property)
{
  return NULL;
}
    

CosNotification::PropertyError_ptr 
TIDNotif::qos::QoSAdmin::validate(const StopTimeSupportedProperty& property)
{
  return NULL;
}

    
CosNotification::PropertyError_ptr 
TIDNotif::qos::QoSAdmin::validate(const PriorityProperty& property)
{
  return NULL;
}
    

CosNotification::PropertyError_ptr 
TIDNotif::qos::QoSAdmin::validate(const StartTimeProperty& property)
{
  return NULL;
}
    

CosNotification::PropertyError_ptr 
TIDNotif::qos::QoSAdmin::validate(const StopTimeProperty& property)
{
  return NULL;
}
    

CosNotification::PropertyError_ptr 
TIDNotif::qos::QoSAdmin::validate(const TimeoutProperty& property)
{
  return NULL;
}
    

CosNotification::PropertyError_ptr 
TIDNotif::qos::QoSAdmin::validate(const QueueOrderProperty& property)
{
  return NULL;
}
     
    
    
/**
 * Maps a CosNotification property to a CORBA Messaging policy.
 * @param property the property
 * @param error out holder that could contain an error creating the policy
 * @return null if it has not any policy to map or there has been an error
 *         creating the policy  
 */
TIDNotif::qos::QoSProperty* 
TIDNotif::qos::QoSAdmin::toQoSProperty(const CosNotification::Property& property, 
                                       CosNotification::PropertyError*& error)
{

  error = NULL;
  QoSPropertyType type = TIDNotif::qos::NOTYPE;
  type = (*st_global_supported_properties)[property.name];
        
  if(type == TIDNotif::qos::NOTYPE) {
    error = createUnsupportedProperty(property);            
    return NULL;
  }
        
  switch (type) {
  case EVENT_RELIABILITY: 
    {
      EventReliabilityProperty* event_rel =  
        eventReliabilityProperty->fromProperty((QoSAdmin&)*this, property, error);
      if(error == NULL) {               
        validate(*event_rel);
        return event_rel;
      } else {
        delete event_rel;
        return NULL;
      }
    }
  case CONNECTION_RELIABILITY:
    {
      ConnectionReliabilityProperty* conn_rel =  
        connectionReliabilityProperty->fromProperty(*this, property, error);
      if(error == NULL) {               
        validate(*conn_rel);
        return conn_rel;
      } else {
        delete conn_rel;
        return NULL;
      }
    }
  case START_TIME_SUPPORTED:  
    {
      StartTimeSupportedProperty* time_sup =  
        startTimeSupportedProperty->fromProperty(*this, property, error);
      if(error == NULL) {               
        validate(*time_sup);
        return time_sup;
      } else {
        delete time_sup;
        return NULL;
      }
    }              
  case STOP_TIME_SUPPORTED:
    {
      StopTimeSupportedProperty* time_sup =  
        stopTimeSupportedProperty->fromProperty(*this, property, error);
      if(error == NULL) {               
        validate(*time_sup);
        return time_sup;
      } else {
        delete time_sup;
        return NULL;
      }
    }  
  case PRIORITY:
    {
      PriorityProperty* priority =  
        priorityProperty->fromProperty(*this, property, error);
      if(error == NULL) {               
        validate(*priority);
        return priority;
      } else {
        delete priority;
        return NULL;
      }
    }
  case START_TIME:
    {
      StartTimeProperty* start_tm =  
        startTimeProperty->fromProperty(*this, property, error);
      if(error == NULL) {               
        validate(*start_tm);
        return start_tm;
      } else {
        delete start_tm;
        return NULL;
      }
    }    
  case STOP_TIME:
    {
      StopTimeProperty* stop_tm =  
        stopTimeProperty->fromProperty(*this, property, error);
      if(error == NULL) {               
        validate(*stop_tm);
        return stop_tm;
      } else {
        delete stop_tm;
        return NULL;
      }
    }             
  case TIMEOUT:
    {
      TimeoutProperty* timeout =  
        timeoutProperty->fromProperty(*this, property, error);
      if(error == NULL) {               
        validate(*timeout);
        return timeout;
      } else {
        delete timeout;
        return NULL;
      }
    }      
  case ORDER_POLICY:
    {
      QueueOrderProperty* order =  
        queueOrderProperty->fromProperty(*this, property, error);
      if(error == NULL) {               
        validate(*order);
        return order;
      } else {
        delete order;
        return NULL;
      }
    }            
  default:
    break;
  }
  //unreachable
  return NULL;


}

/**
 * Create a PropertyRange for Order properties.
 * @return The range with short values (AnyOrder to DeadLineOrder)
 */
CosNotification::PropertyRange_ptr 
TIDNotif::qos::QoSAdmin::getOrderRange()
{
  CosNotification::PropertyRange_ptr order_range = 
    new CosNotification::PropertyRange();

  order_range->low_val  <<= CosNotification::AnyOrder;
  order_range->high_val <<= CosNotification::DeadlineOrder;
  
  return order_range;
}
    
/**
 * Create a PropertyRange for ConnectionReliability properties.
 * @return The range with short values (BestEffort - Persistent)
 */
CosNotification::PropertyRange_ptr 
TIDNotif::qos::QoSAdmin::getConnectionReliabilityRange()
{
  CosNotification::PropertyRange_ptr reliability_range = 
    new CosNotification::PropertyRange();

  reliability_range->low_val  <<= CosNotification::BestEffort;
  reliability_range->high_val <<= CosNotification::Persistent;                 
  
  return reliability_range;   
}
     
/**
 * Create a PropertyRange for Event properties.
 * @return The range with short values (BestEffort - Persistent)
 */
CosNotification::PropertyRange_ptr 
TIDNotif::qos::QoSAdmin::getEventReliabilityRange()
{
  CosNotification::PropertyRange_ptr reliability_range = 
    new CosNotification::PropertyRange();

  reliability_range->low_val  <<= CosNotification::BestEffort;
  reliability_range->high_val <<= CosNotification::Persistent;
  
  return reliability_range;         
}
    
/**
 * Create a PropertyRange for time properties.
 * @return The range with TimeBase::UtcT values
 */
CosNotification::PropertyRange_ptr 
TIDNotif::qos::QoSAdmin::getTimeRange()
{

  CosNotification::PropertyRange_ptr time_range = 
    new CosNotification::PropertyRange();

  TimeBase::UtcT time;
        
  time.time = (CORBA::ULongLong) 0L;
        
  time_range->low_val <<= time;          
                        
  // TimeT is defined in IDL as unsigned long long. In Java
  // equivalent type is long (signed), and this value must be
  // assumed by the user as unsigned
  time.time = (CORBA::Long) 0xffffffffL;
        
  time_range->high_val <<= time;
        
  return time_range;
}
    
/**
 * Create a PropertyRange for the Priority property.
 * @return The range with unsigned short values
 */
CosNotification::PropertyRange_ptr 
TIDNotif::qos::QoSAdmin::getPriorityRange()
{
   CosNotification::PropertyRange_ptr priority_range = 
     new CosNotification::PropertyRange();

   priority_range->high_val <<= CosNotification::HighestPriority;
   priority_range->low_val <<= CosNotification::LowestPriority;
   
   return priority_range;
}
    
/**
 * Create a null PropertyRange for PropertyErrors.
 * @param property
 * @return The range with null Any values
 */
CosNotification::PropertyRange_ptr 
TIDNotif::qos::QoSAdmin::getBooleanRange()
{
  CosNotification::PropertyRange_ptr bool_range = 
    new CosNotification::PropertyRange();
  
  bool_range->high_val <<= true;
  bool_range->low_val <<= false;
  
  return bool_range;
}
    
/**
 * Create a null PropertyRange for PropertyErrors.
 * @param property
 * @return The range with null Any values
 */
CosNotification::PropertyRange_ptr 
TIDNotif::qos::QoSAdmin::getNullRange()
{
  CosNotification::PropertyRange_ptr null_range = 
    new CosNotification::PropertyRange();

  return null_range;
}

    
/**
 * Create a PropertyRange for timeouts. Timeout type is TimeBase::TimeT,
 * and the units are 100 ns.
 * @return
 */
CosNotification::PropertyRange_ptr 
TIDNotif::qos::QoSAdmin::getTimeoutRange()
{
  CosNotification::PropertyRange_ptr timeout_range = 
    new CosNotification::PropertyRange();

  TIDorb::core::TIDORB* _orb = dynamic_cast < TIDorb::core::TIDORB* > (m_orb);

  CORBA::Any_var any1 = _orb->create_any();
  CORBA::Any_var any2 = _orb->create_any();
        
  // TimeT is defined in IDL as unsigned long long. 
            
  *any1 <<= (CORBA::Long) 0xffffffffL;
  timeout_range->high_val = *any1;

  *any2 <<= (CORBA::Long) 0L;
  timeout_range->low_val = *any2;
   
        
  return timeout_range;
}
    
CosNotification::PropertyError_ptr 
TIDNotif::qos::QoSAdmin::createPropertyError(CosNotification::Property property)
{
  CosNotification::PropertyError_ptr error = new CosNotification::PropertyError();
  error->code = CosNotification::BAD_VALUE;
  error->name = property.name;
  CosNotification::PropertyRange_var range = getNullRange(); 
  error->available_range.low_val  = range->low_val; 
  error->available_range.high_val = range->high_val;
  return error; 
}
    
CosNotification::PropertyError_ptr
TIDNotif::qos::QoSAdmin::createBadProperty(CosNotification::Property& property)
{
  CosNotification::PropertyError_ptr error = createPropertyError(property);
  error->code = CosNotification::BAD_PROPERTY;
  return error;
}
    
CosNotification::PropertyError_ptr
TIDNotif::qos::QoSAdmin::createUnsupportedProperty(CosNotification::Property property)
{
  CosNotification::PropertyError_ptr error = createPropertyError(property);
  error->code = CosNotification::UNSUPPORTED_PROPERTY;
  return error;
}

/**
 * @return
 */
TIDNotif::qos::QoSAdmin::PropertiesMapT* 
TIDNotif::qos::QoSAdmin::initGlobalSupportedProperties()
{
  TIDNotif::qos::QoSAdmin::PropertiesMapT* properties_map = 
    new TIDNotif::qos::QoSAdmin::PropertiesMapT;

  (*properties_map)[CosNotification::EventReliability]      = EVENT_RELIABILITY;
  (*properties_map)[CosNotification::ConnectionReliability] = CONNECTION_RELIABILITY;
  (*properties_map)[CosNotification::Priority]              = PRIORITY;
  (*properties_map)[CosNotification::StartTime]             = START_TIME;
  (*properties_map)[CosNotification::StopTime]              = STOP_TIME;
  (*properties_map)[CosNotification::Timeout]               = TIMEOUT;        
  (*properties_map)[CosNotification::OrderPolicy]           = ORDER_POLICY;
  (*properties_map)[CosNotification::StopTime]              = STOP_TIME;
  (*properties_map)[CosNotification::StartTimeSupported]    = START_TIME_SUPPORTED;
  (*properties_map)[CosNotification::StopTimeSupported]     = STOP_TIME_SUPPORTED;

  return properties_map;
}
    


void TIDNotif::qos::QoSAdmin::readObject(istream& in)
{
  TIDThr::Synchronized synchro(_recursive_mutex);


  // Read all properties in the correct order
  CORBA::Long num;

  in >> num;
  if (num == 1){
    eventReliabilityProperty = new EventReliabilityProperty();
    eventReliabilityProperty->readObject(in);
  }
  in >> num;
  if (num == 2){
    connectionReliabilityProperty = new ConnectionReliabilityProperty();
    connectionReliabilityProperty->readObject(in);
  }
  in >> num;
  if (num == 3){
    startTimeSupportedProperty = new StartTimeSupportedProperty();
    startTimeSupportedProperty->readObject(in);
  }
  in >> num;
  if (num == 4){
    stopTimeSupportedProperty = new StopTimeSupportedProperty();
    stopTimeSupportedProperty->readObject(in);
  }
  in >> num;
  if (num == 5){
    priorityProperty = new PriorityProperty();
    priorityProperty->readObject(in);
  }
  in >> num;
  if (num == 6){
    startTimeProperty = new StartTimeProperty();
    startTimeProperty->readObject(in);
  }
  in >> num;
  if (num == 7){
    stopTimeProperty = new StopTimeProperty();
    stopTimeProperty->readObject(in);
  }
  in >> num;
  if (num == 8){
    timeoutProperty = new TimeoutProperty();
    timeoutProperty->readObject(in);
  }
  in >> num;
  if (num == 9){
    queueOrderProperty = new QueueOrderProperty();
    queueOrderProperty->readObject(in);
  }

}

void TIDNotif::qos::QoSAdmin::writeObject(ostream& out)
{
  TIDThr::Synchronized synchro(_recursive_mutex);
  
  // Write all properties in the same order

  if (eventReliabilityProperty != NULL){
    out << "1" << endl;
    eventReliabilityProperty->writeObject(out);
  }
  if (connectionReliabilityProperty != NULL){
    out << "2" << endl;
    connectionReliabilityProperty->writeObject(out);
  }
  if (startTimeSupportedProperty != NULL){
    out << "3" << endl;
    startTimeSupportedProperty->writeObject(out);
  }
  if (stopTimeSupportedProperty != NULL){
    out << "4" << endl;
    stopTimeSupportedProperty->writeObject(out);
  }
  if (priorityProperty != NULL){
    out << "5" << endl;
    priorityProperty->writeObject(out);
  }
  if (startTimeProperty != NULL){
    out << "6" << endl;
    startTimeProperty->writeObject(out);
  }
  if (stopTimeProperty != NULL){
    out << "7" << endl;
    stopTimeProperty->writeObject(out);
  }
  if (timeoutProperty != NULL){
    out << "8" << endl;
    timeoutProperty->writeObject(out);
  }
  if (queueOrderProperty != NULL){
    out << "9" << endl;
    queueOrderProperty->writeObject(out);
  }

}
