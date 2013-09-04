#include "ConsumerEvtImpl.h"

ConsumerEvtImpl::ConsumerEvtImpl(){

}

// ------------------------------------------------------------------

void ConsumerEvtImpl::push(const CORBA::Any &dat)
   throw (CORBA::SystemException,
          CosEventComm::Disconnected){

  fprintf(stderr,"Evento!\n");
}

// ------------------------------------------------------------------

void ConsumerEvtImpl::offer_change(const CosNotification::EventTypeSeq &added,
                                   const CosNotification::EventTypeSeq &removed)
  throw (CORBA::SystemException,
         CosNotifyComm::InvalidEventType){

  fprintf(stderr,"offer_change!\n");
}
// ------------------------------------------------------------------

void ConsumerEvtImpl::disconnect_push_consumer()
  throw (CORBA::SystemException){

  fprintf(stderr,"disconnect_push_consumer!\n");
}
