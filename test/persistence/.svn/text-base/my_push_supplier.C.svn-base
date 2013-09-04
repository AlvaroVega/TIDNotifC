#include "my_push_supplier.h"

 my_push_supplier::my_push_supplier (CosNotifyChannelAdmin::ProxyPushConsumer_ptr consumer)
  :_consumer(consumer){}
 void my_push_supplier::new_event (CORBA::Any & event){
    _consumer->push(event);
}

  void my_push_supplier::disconnect_push_supplier(){
    _consumer->disconnect_push_consumer();
  }
    void my_push_supplier::subscription_change(const CosNotification::EventTypeSeq&, 
                             const CosNotification::EventTypeSeq&){
      printf("No implemented\n");
}
