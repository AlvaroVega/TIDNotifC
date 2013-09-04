#ifndef __CONSUMER_EVT_IMPL_H__
#define __CONSUMER_EVT_IMPL_H__

#ifdef _TAO
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#elif defined _TIDORB
#include "CosNotifyChannelAdmin.h"
#include "CosEventChannelAdmin.h"
#include "POA_CosNotifyComm.h"
/* #include <CosNotifyChannelAdmin.h> */
/* #include <POA_CosNotifyComm.h> */
#endif



class ConsumerEvtImpl : public virtual POA_CosNotifyComm::PushConsumer{
  
  public:
     ConsumerEvtImpl();
  
     void push(const CORBA::Any &dat) 
          throw (CORBA::SystemException,CosEventComm::Disconnected);
     
     void offer_change(const CosNotification::EventTypeSeq &added,
                       const CosNotification::EventTypeSeq &removed)
          throw (CORBA::SystemException,
                 CosNotifyComm::InvalidEventType);
     
     void disconnect_push_consumer()
          throw (CORBA::SystemException);
 
  protected:

  private:
};

#endif // __CONSUMER_EVT_IMPL_H__
