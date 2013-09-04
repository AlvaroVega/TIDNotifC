#include "POA_CosEventComm.h"

class my_push_supplier: public virtual POA_CosEventComm::PushSupplier
{
 private:
  
  CosEventComm::PushConsumer_ptr _consumer;
  
public:
  
  my_push_supplier (CosEventComm::PushConsumer_ptr consumer);
  void new_event (CORBA::Any & event);
  
  void disconnect_push_supplier();
  /* 
     void subscription_change(const CosNotification::EventTypeSeq&, 
                             const CosNotification::EventTypeSeq&);
  */
};

