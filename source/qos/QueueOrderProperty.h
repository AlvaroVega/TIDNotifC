// -*- c++ -*-
/*
*  File name: QueueOrderProperty.h
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

#include "qos.h"

#ifndef _TIDNOTIF_QOS_QUEUEPROPERTY_H_
#define _TIDNOTIF_QOS_QUEUEPROPERTY_H_

#include "CosNotification.h"


namespace TIDNotif{
namespace qos{
  
class QueueOrderProperty : public QoSProperty{

protected:
  QueueOrderProperty(const CosNotification::Property& property,
                     Messaging::QueueOrderPolicy_ptr policy, 
                     CORBA::Short value);

public:
  QueueOrderProperty();

  static QueueOrderProperty* fromProperty(
                                QoSAdmin& admin, 
                                const CosNotification::Property& property,
                                CosNotification::PropertyError*& error);
private:

  Messaging::QueueOrderPolicy_var policy;

  CORBA::Short value;

  TIDThr::RecursiveMutex _recursive_mutex;  

public:

  void readObject( std::istream & in);

  void writeObject(ostream & out);
  
public:

  CORBA::Short getValue();

  Messaging::QueueOrderPolicy_ptr getPolicy(CORBA::ORB_ptr orb);
  
};

}
}
#endif
