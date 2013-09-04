#include "my_push_supplier.h"

 my_push_supplier::my_push_supplier (CosNotifyChannelAdmin::StructuredProxyPushConsumer_ptr consumer)
  :_consumer(consumer){}
 void my_push_supplier::new_event (CosNotification::StructuredEvent & event){
    _consumer->push_structured_event(event);
}

  void my_push_supplier::disconnect_structured_push_supplier(){
    _consumer->disconnect_structured_push_consumer();
  }
    void my_push_supplier::subscription_change(const CosNotification::EventTypeSeq&, 
                             const CosNotification::EventTypeSeq&){
      printf("No implemented\n");
}
