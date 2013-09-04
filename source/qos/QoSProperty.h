// -*- c++ -*-
/*
*  File name: QoSProperty.h
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

#ifndef _TIDNOTIF_QOS_QOSPROPERTY_H_
#define _TIDNOTIF_QOS_QOSPROPERTY_H_

#include "CosNotification.h"

namespace TIDNotif{
namespace qos{
  

class QoSProperty : public virtual TIDorb::portable::Streamable {
  
  //private:
protected:
  
  CosNotification::Property property;
  
public:
  
  QoSProperty();

  ~QoSProperty() {};
  
  QoSProperty(const CosNotification::Property& prop);
  
  const char* getName();
  
  CosNotification::Property& getProperty();
  
  bool operator == (const CORBA::Object* obj) const;
  
  virtual void _read(TIDorb::portable::InputStream& is) {}
  
  virtual void _write(TIDorb::portable::OutputStream& os) const {}
  
  virtual CORBA::TypeCode_ptr _type() const;
};

}
}
#endif

