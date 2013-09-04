#ifndef MYSERVER_IMPL_H
#define MYSERVER_IMPL_H


#ifdef _TAO
#include "orbsvcs/orbsvcs/CosEventChannelAdminS.h"
#include "EventS.h"
#elif defined _TIDORB
#include "CosEventChannelAdmin.h"
#include "POA_Event.h"
#elif defined _MICO
#include <coss/CosEventComm.h>
#include <coss/CosEventChannelAdmin.h>
#include "Event.h"
#endif

#include <iostream>

using namespace std;



class MySupplierImpl : public virtual POA_Event::Server
{
  //Clase de la parte sumunistradora de eventos
private:

  CORBA::ORB_var _the_orb;
  CosEventChannelAdmin::EventChannel_var _the_channel;
  CosEventChannelAdmin::ProxyPushConsumer_var _consumer;

public:

  MySupplierImpl(const CORBA::ORB_ptr orb,
                 const CosEventChannelAdmin::EventChannel_ptr channel);
  
  ~MySupplierImpl();

  void enviar(const CORBA::Any& alarm_info) 
    throw (CORBA::SystemException);

  void disconnect_push_supplier() 
    throw (CORBA::SystemException);

  void disconnect() {};

};

#endif
