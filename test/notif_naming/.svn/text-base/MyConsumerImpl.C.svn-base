// -*- c++ -*-
#include "MyConsumerImpl.h"

#include <sys/time.h>
#include <time.h>

using namespace std;



MyConsumerImpl::MyConsumerImpl() {
  //  cerr << "[MyConsumerImpl] MyConsumerImpl()" << endl;

}


MyConsumerImpl::~MyConsumerImpl() {

}


void MyConsumerImpl::push(const CORBA::Any& data) 
  throw (CORBA::SystemException, CosEventComm::Disconnected)
{
  // Metodo que ejecuta el ProxyPushSupplier para enviar eventos al Consumer
  cerr << "[MyConsumerImpl] push recibido!" << endl;
  return;
}


void MyConsumerImpl::disconnect_push_consumer() 
  throw (CORBA::SystemException) 
{
  cerr << "[MyConsumerImpl] disconnect_push_consumer recibido!" << endl;
}


void MyConsumerImpl::offer_change(const CosNotification::EventTypeSeq&, 
                                  const CosNotification::EventTypeSeq&) 
  throw (CORBA::SystemException, CosNotifyComm::InvalidEventType)
{
  cerr << "[MyConsumerImpl] subscription_change recibido!" << endl;
}
