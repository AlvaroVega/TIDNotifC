#ifndef MYCLIENT_IMPL_H
#define MYCLIENT_IMPL_H

#ifdef _TAO
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#include "EventS.h"
#elif defined _TIDORB
#include "CosNotifyChannelAdmin.h"
#include "CosEventChannelAdmin.h"
#include "POA_Event.h"
#include "POA_CosNotifyComm.h"
#endif

#include <iostream>

using namespace std;

class MyConsumerImpl : 
#ifdef _TAO
  public virtual POA_CosNotifyComm::PushConsumer
#else
  public virtual POA_CosEventComm::PushConsumer
#endif
{
public:

  MyConsumerImpl();
  
  ~MyConsumerImpl();

  void push(const CORBA::Any & any) throw (CORBA::SystemException, 
                                           CosEventComm::Disconnected);
  
  void disconnect_push_consumer() throw (CORBA::SystemException);
  
  void offer_change(const CosNotification::EventTypeSeq&, 
               const CosNotification::EventTypeSeq&)
    throw (CORBA::SystemException, CosNotifyComm::InvalidEventType) {};
};

#endif
