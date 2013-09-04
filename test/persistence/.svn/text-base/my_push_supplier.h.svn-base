#include "POA_CosNotifyComm.h"
#include "CosNotifyChannelAdmin.h"
#include "CORBA.h"
class my_push_supplier: public virtual POA_CosNotifyComm::PushSupplier
{
  private:

   CosNotifyChannelAdmin::ProxyPushConsumer_ptr _consumer;

  public:

    my_push_supplier (CosNotifyChannelAdmin::ProxyPushConsumer_ptr consumer);
    void new_event (CORBA::Any & event);

    void disconnect_push_supplier();
   void subscription_change(const CosNotification::EventTypeSeq&, 
                             const CosNotification::EventTypeSeq&);
};

