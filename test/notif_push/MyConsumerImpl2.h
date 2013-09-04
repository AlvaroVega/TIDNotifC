#ifndef MYCONSUMER2_IMPL_H
#define MYCONSUMER2_IMPL_H

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

class MyConsumerImpl2 : public virtual POA_CosNotifyComm::StructuredPushConsumer
{
public:

  MyConsumerImpl2();
  
  ~MyConsumerImpl2();

  void push_structured_event(const CosNotification::StructuredEvent& notification) 
    throw (CORBA::SystemException, CosEventComm::Disconnected);
  
  void disconnect_structured_push_consumer() throw (CORBA::SystemException);
  
  void offer_change(const CosNotification::EventTypeSeq&, 
               const CosNotification::EventTypeSeq&) 
    throw (CORBA::SystemException, CosNotifyComm::InvalidEventType){};
};

#endif
