// -*- c++ -*-
/*
 *  File name: QoSAdmin.h
 *  File type: Header file.
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

#include "qos.h"

#ifndef _TIDNOTIF_QOS_QOSADMIN_H_
#define _TIDNOTIF_QOS_QOSADMIN_H_

#include "CosNotification.h"
#include <map>


namespace TIDNotif{
namespace qos{

enum QoSPropertyType{NOTYPE = 0,
                     EVENT_RELIABILITY, 
                     CONNECTION_RELIABILITY,
                     PRIORITY,
                     START_TIME,
                     STOP_TIME,
                     TIMEOUT,
                     ORDER_POLICY,
                     START_TIME_SUPPORTED,
                     STOP_TIME_SUPPORTED,
                     MAX_EVENTS_PER_CONSUMER,
                     DISCARD_POLICY,
                     MAXIMUM_BATCH_SIZE,
                     PACING_INTERVAL};

struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};



class QoSAdmin: public virtual CosNotification::QoSAdmin,
                public virtual CORBA::LocalObject
{   

private: 

  CORBA::ORB* m_orb;
  CosNotification::QoSProperties* m_properties;
  CORBA::PolicyList* m_policies;
  CORBA::Boolean m_properties_updated;
    
  /* 
   * Smart accessors
   */
    
  EventReliabilityProperty*       eventReliabilityProperty;
  ConnectionReliabilityProperty*  connectionReliabilityProperty;
  StartTimeSupportedProperty*     startTimeSupportedProperty;
  StopTimeSupportedProperty*      stopTimeSupportedProperty;
  PriorityProperty*               priorityProperty;
  StartTimeProperty*              startTimeProperty;
  StopTimeProperty*               stopTimeProperty;
  TimeoutProperty*                timeoutProperty;
  QueueOrderProperty*             queueOrderProperty;

protected:
  TIDThr::RecursiveMutex _recursive_mutex;  
    
public:

  typedef map <const char*, QoSPropertyType, ltstr> PropertiesMapT;

  static PropertiesMapT* st_global_supported_properties;

  QoSAdmin();
  
  QoSAdmin(CORBA::ORB_ptr orb);
  
  ~QoSAdmin();

  CORBA::ORB_ptr getORB();

  void setORB(CORBA::ORB_ptr orb);
    
  /**
   * @return Returns the connectionReliabilityProperty.
   */
  ConnectionReliabilityProperty* getConnectionReliabilityProperty();

  /**
   * @return Returns the eventReliabilityProperty.
   */
  EventReliabilityProperty* getEventReliabilityProperty();
    
  /**
   * @return Returns the priorityProperty.
   */
  PriorityProperty* getPriorityProperty();

  /**
   * @return Returns the queueOrderProperty.
   */
  QueueOrderProperty* getQueueOrderProperty();

  /**
   * @return Returns the startTimeProperty.
   */
  StartTimeProperty* getStartTimeProperty();

  /**
   * @return Returns the startTimeSupportedProperty.
   */
  StartTimeSupportedProperty* getStartTimeSupportedProperty();

  /**
   * @return Returns the stopTimeProperty.
   */
  StopTimeProperty* getStopTimeProperty();

  /**
   * @return Returns the stopTimeSupportedProperty.
   */
  StopTimeSupportedProperty* getStopTimeSupportedProperty();

  /**
   * @return Returns the timeoutProperty.
   */
  TimeoutProperty* getTimeoutProperty();



  /***************************************
   * CosNotification::QoSAdmin operatons *
   ***************************************/
    
  CosNotification::QoSProperties* get_qos();

  void set_qos(const CosNotification::QoSProperties& qos)
    throw (CosNotification::UnsupportedQoS);
  
  CORBA::PolicyList* getPolicies();
  
  void validate_qos(const CosNotification::QoSProperties& required_qos, 
                    CosNotification::NamedPropertyRangeSeq*& available_qos)
    throw (CosNotification::UnsupportedQoS);
     
  /*****************************
   * Implementation operations *
   *****************************/
    
  /**
   * Set deffinitively validated properties
   * @param properties vector of QoSProperty 
   */
  void commit(const CosNotification::QoSProperties& properties);
        
    
private:

  /**
   * Sets a validaded property     
   * @param property
   */
  void setProperty(const CosNotification::Property& property);
    
  /**
   * Validates and process the Property to QoSProperty list
   * @param qos the QoS properties
   * @return the Processed QoSProperties
   * @throws UnsupportedQoS if any property is not supported
   */
  CosNotification::QoSProperties* validate(const CosNotification::QoSProperties& qos) 
    throw (CosNotification::UnsupportedQoS);
   

protected:

  /**
   * Validates if this property is supported. By default, all property values
   * are valid. Override these methods if not supported values exist.
     
   * @param property 
   * @return error if not supported
   */    
  virtual CosNotification::PropertyError_ptr 
  validate(const EventReliabilityProperty& property);
    
  virtual CosNotification::PropertyError_ptr 
  validate(const ConnectionReliabilityProperty& property);

  virtual CosNotification::PropertyError_ptr 
  validate(const StartTimeSupportedProperty&  property);
    
  virtual CosNotification::PropertyError_ptr 
  validate(const StopTimeSupportedProperty& property);
    
  virtual CosNotification::PropertyError_ptr 
  validate(const PriorityProperty& property);
    
  virtual CosNotification::PropertyError_ptr 
  validate(const StartTimeProperty& property);
    
  virtual CosNotification::PropertyError_ptr 
  validate(const StopTimeProperty& property);
    
  virtual CosNotification::PropertyError_ptr 
  validate(const TimeoutProperty& property);
    
  virtual CosNotification::PropertyError_ptr 
  validate(const QueueOrderProperty& property);
     
  /**
   * Gets the available QoS properties
   * @return
   */
  virtual CosNotification::NamedPropertyRangeSeq* getAvailableQoS() = 0;
   
   
public:    

  /**
   * Maps a CosNotification property to a CORBA Messaging policy.
   * @param property the property
   * @param error out holder that could contain an error creating the policy
   * @return null if it has not any policy to map or there has been an error
   *         creating the policy  
   */
  QoSProperty* toQoSProperty(const CosNotification::Property& property, 
                             CosNotification::PropertyError*& error);

  /**
   * Create a PropertyRange for Order properties.
   * @return The range with short values (AnyOrder to DeadLineOrder)
   */
  CosNotification::PropertyRange_ptr getOrderRange();
    
  /**
   * Create a PropertyRange for ConnectionReliability properties.
   * @return The range with short values (BestEffort - Persistent)
   */
  CosNotification::PropertyRange_ptr getConnectionReliabilityRange();
     
  /**
   * Create a PropertyRange for Event properties.
   * @return The range with short values (BestEffort - Persistent)
   */
  CosNotification::PropertyRange_ptr getEventReliabilityRange();
    
  /**
   * Create a PropertyRange for time properties.
   * @return The range with TimeBase::UtcT values
   */
  CosNotification::PropertyRange_ptr getTimeRange();
    
  /**
   * Create a PropertyRange for the Priority property.
   * @return The range with unsigned short values
   */
  CosNotification::PropertyRange_ptr getPriorityRange();
    
  /**
   * Create a null PropertyRange for PropertyErrors.
   * @param property
   * @return The range with null Any values
   */
  CosNotification::PropertyRange_ptr getBooleanRange();
    
  /**
   * Create a null PropertyRange for PropertyErrors.
   * @param property
   * @return The range with null Any values
   */
  static CosNotification::PropertyRange_ptr getNullRange();
    
  /**
   * Create a PropertyRange for timeouts. Timeout type is TimeBase::TimeT,
   * and the units are 100 ns.
   * @return
   */
  CosNotification::PropertyRange_ptr getTimeoutRange();
    


  static CosNotification::PropertyError_ptr 
  createPropertyError(CosNotification::Property property);
    
  CosNotification::PropertyError_ptr 
  createBadProperty(CosNotification::Property& property);
    
  CosNotification::PropertyError_ptr 
  createUnsupportedProperty(CosNotification::Property property);

  /**
   * @return
   */
  static PropertiesMapT* initGlobalSupportedProperties();
    


public:

  void readObject(istream& in);
  
  void writeObject(ostream& out);
};

}
}    
#endif

  
