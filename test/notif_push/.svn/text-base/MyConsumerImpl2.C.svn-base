#include "MyConsumerImpl2.h"

#include <sys/time.h>
#include <time.h>




MyConsumerImpl2::MyConsumerImpl2() {
  //  cerr << "[MyConsumerImpl] MyConsumerImpl()" << endl;

};


MyConsumerImpl2::~MyConsumerImpl2() {

};



void MyConsumerImpl2::push_structured_event(
                         const CosNotification::StructuredEvent& notification)
  throw (CORBA::SystemException, CosEventComm::Disconnected)
{
  cerr << "[MyConsumerImpl2] Recibiendo  mensaje ";
  CORBA::Long mylong = 0;
  notification.filterable_data[0].value >>= mylong;
  cerr << mylong << endl;
  return;
};


void MyConsumerImpl2::disconnect_structured_push_consumer() 
  throw (CORBA::SystemException)
{
  cerr << "[MyConsumerImpl2] disconnect_structured_push_consumer" << endl;

};
