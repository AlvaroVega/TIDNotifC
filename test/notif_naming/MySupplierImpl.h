// -*- c++ -*-
#ifndef MYSUPPLIER_IMPL_H
#define MYSUPPLIER_IMPL_H


#ifdef _TAO
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#elif defined _TIDORB
#include "CosNotifyChannelAdmin.h"
#include "CosEventChannelAdmin.h"
#include "POA_CosNotifyComm.h"
#endif

#include <iostream>

using namespace std;



class MySupplierImpl: 
#ifdef _TAO
  public virtual POA_CosNotifyComm::PushSupplier
#else
  public virtual POA_CosEventComm::PushSupplier
#endif
{

public:

  MySupplierImpl();
  
  ~MySupplierImpl();

  void disconnect_push_supplier() 
    throw (CORBA::SystemException);

  void subscription_change(const CosNotification::EventTypeSeq&, 
                           const CosNotification::EventTypeSeq&)
    throw (CORBA::SystemException, CosNotifyComm::InvalidEventType);

};

#endif
