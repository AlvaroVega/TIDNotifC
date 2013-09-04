#include "POA_CosNotifyComm.h"
#include "CORBA.h"
#include "DynamicAny.h"
class my_push_consumer : public virtual POA_CosNotifyComm::StructuredPushConsumer
{
  private:
    CORBA::ORB_ptr _orb;
    CosNotifyComm::StructuredPushSupplier_ptr _supplier;
    DynamicAny::AnySeq * anySeq;
    bool finish;
    bool _ok;
    int events;
  public:
    my_push_consumer(CORBA::ORB* orb,
                     CosNotifyComm::StructuredPushSupplier_ptr supplier);

    void push(const CORBA::Any& data);

    
    void disconnect_structured_push_consumer();

    /*
     *new burst of events that must happen 
     */
    void new_events(int n);

    /*
     *event that must pass the filter 
     */
    void add_event(CORBA::Any & event);

    /*
     *it verifies that all the events (that must have happened) have happened 
     */
    bool finished ();

    /*
     *it verifies that everything has gone well 
     */
    bool ok();

    void push_structured_event(const CosNotification::StructuredEvent&);
 
    void offer_change(const CosNotification::EventTypeSeq&, const CosNotification::EventTypeSeq&);

};
