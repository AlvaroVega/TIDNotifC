/*
*  File name: EventReliabilityProperty.h
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

#ifndef _TIDNOTIF_QOS_EVENTRELIABILITY_H_
#define _TIDNOTIF_QOS_EVENTRELIABILITY_H_

#include "CosNotification.h"

#include <istream>
#include <ostream>

namespace TIDNotif{
namespace qos{

class EventReliabilityProperty: public QoSProperty{

private:

  CORBA::Short value;


protected: 

  EventReliabilityProperty(const CosNotification::Property& property,
                           CORBA::Short val);
public:  

  void readObject(istream & in);
  void writeObject(ostream & out);

  static EventReliabilityProperty* fromProperty(QoSAdmin& admin,
                                                const CosNotification::Property& property, 
                                                CosNotification::PropertyError*& error);

public:
  EventReliabilityProperty();

  CORBA::Short getValue();

};

}
}
#endif
