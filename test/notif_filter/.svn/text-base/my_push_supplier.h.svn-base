#include "POA_CosNotifyComm.h"
#include "CosNotifyChannelAdmin.h"
#include "CORBA.h"
class my_push_supplier: public virtual POA_CosNotifyComm::StructuredPushSupplier
{
  private:

   CosNotifyChannelAdmin::StructuredProxyPushConsumer_ptr _consumer;

  public:

    my_push_supplier (CosNotifyChannelAdmin::StructuredProxyPushConsumer_ptr consumer);
    void new_event (CosNotification::StructuredEvent & event);

    void disconnect_structured_push_supplier();
    void subscription_change(const CosNotification::EventTypeSeq&, 
                             const CosNotification::EventTypeSeq&);
};

