#include "my_push_consumer.h"
my_push_consumer::my_push_consumer(CORBA::ORB* orb,
                                   CosNotifyComm::PushSupplier_ptr supplier)
    :_orb(orb),_supplier(supplier),finish(false),_ok(false),events(0){
      anySeq = new DynamicAny::AnySeq(0);
    }

void my_push_consumer::push(const CORBA::Any& data){
   
    
  /*  for(int i = 0; i<anySeq->length();i++)
    {
      if ((*anySeq)[i] == data)
      {
        events--;
        if (events==0)
        {
          finish=true;
          _ok=true;
        }
        return;
      }
    }
    //event that must not arrive
    finish = true;
    _ok=false;*/

   DynamicAny::DynAnyFactory_var _dafact;
   _dafact =  DynamicAny::DynAnyFactory::_narrow(_orb->resolve_initial_references("DynAnyFactory"));
    

    DynamicAny::DynAny_ptr _dyn_any;
    _dyn_any = _dafact->create_dyn_any(data);
    
    
    DynamicAny::DynStruct_ptr _dyn_struct;

    _dyn_struct = DynamicAny::DynStruct::_narrow(_dyn_any);
    
    CORBA::release(_dyn_any);
    CORBA::Long value;
    DynamicAny::NameValuePairSeq* member_seq = _dyn_struct->get_members();
    _dyn_struct->seek(0);
    for (int i = 0; i<member_seq->length();i++)
    {
      printf("Campo: %s\n",(*member_seq)[i].id.in());
      value = _dyn_struct->get_long();
      printf("Valor: %d\n",value);
      _dyn_struct->next();
    }
    
    
    _dyn_struct->destroy();
    CORBA::release(_dyn_struct);
}

    
void my_push_consumer::disconnect_push_consumer(){
    _supplier->disconnect_push_supplier();
    _supplier = NULL;
    
}

/*
     *new burst of events that must happen 
     */
    void my_push_consumer::new_events(int n){
      finish=false;
      _ok=false;
      events=n;
      delete anySeq;
      anySeq = new DynamicAny::AnySeq(n);
      anySeq->length(0);
    }

    /*
     *event that must pass the filter 
     */
    void my_push_consumer::add_event(CORBA::Any & event){
      int length = anySeq->length();
      anySeq->length(length+1);
      (*anySeq)[length]=event;
      
    }

    /*
     *it verifies that all the events (that must happen) have happened 
     */
    bool my_push_consumer::finished ()
    {
        return finish;
    }

    /*
     *it verifies that everything has gone well 
     */
    bool my_push_consumer::ok(){
        return _ok;
    }

    void my_push_consumer::offer_change(const CosNotification::EventTypeSeq&, 
                                      const CosNotification::EventTypeSeq&){
      printf("No implemented\n");
    }
