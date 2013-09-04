// -*- c++ -*-
/*
*  File name: StopTimeSupportedProperty.h
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

#ifndef _TIDNOTIF_QOS_STOPTIMESUPPORTEDPROPERTY_H_
#define _TIDNOTIF_QOS_STOPTIMESUPPORTEDPROPERTY_H_


#include "CosNotification.h"

#ifdef TIDORB_HAVE_NAMESPACE_STD
using namespace std;
#endif

namespace TIDNotif{
namespace qos{

class StopTimeSupportedProperty : public QoSProperty{

protected:
  StopTimeSupportedProperty(const CosNotification::Property& property, 
                            CORBA::Boolean value);

public:
  StopTimeSupportedProperty();

  static StopTimeSupportedProperty* 
  fromProperty(QoSAdmin& admin,
               const CosNotification::Property& property,
               CosNotification::PropertyError*& error);
private:
  
  CORBA::Boolean value;


public:
  bool getValue();
  void readObject(istream & in);
  void writeObject(ostream & out);
};

}
}
#endif
