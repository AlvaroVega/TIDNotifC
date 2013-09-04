#ifndef MYCLIENT_IMPL_H
#define MYCLIENT_IMPL_H

#ifdef _TAO
#include "orbsvcs/orbsvcs/CosEventChannelAdminS.h"
#include "EventS.h"
#elif defined _TIDORB
#include "CosEventChannelAdmin.h"
#include "POA_Event.h"
#include "POA_CosEventComm.h"
#elif defined _MICO
#include <coss/CosEventComm.h>
#include <coss/CosEventChannelAdmin.h>
#include "Event.h"
#endif

#include <iostream>
using namespace std;

class MyConsumerImpl : public virtual POA_CosEventComm::PushConsumer
{
public:

        void push(const CORBA::Any & any) throw (CORBA::SystemException, 
                                                 CosEventComm::Disconnected);

        void disconnect_push_consumer() throw (CORBA::SystemException) {};

	MyConsumerImpl();

	~MyConsumerImpl();
};

#endif
