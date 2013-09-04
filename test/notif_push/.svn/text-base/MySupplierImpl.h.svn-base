#ifndef MYSUPPLIER_IMPL_H
#define MYSUPPLIER_IMPL_H


#ifdef _TAO
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#include "EventS.h"
#elif defined _TIDORB
#include "CosNotifyChannelAdmin.h"
#include "CosEventChannelAdmin.h"
#include "POA_Event.h"
#endif

#include <iostream>

using namespace std;



class MySupplierImpl : public virtual POA_Event::Server
{
  // Clase de la parte sumunistradora de eventos
private:

  CORBA::ORB_var _the_orb;
  CosNotifyChannelAdmin::EventChannel_var _the_channel;
  CosNotifyChannelAdmin::ProxyPushConsumer_var _consumer;
  CosNotifyChannelAdmin::SupplierAdmin_var _supplier_admin;
  Event::Server_var supplier_ref;
public:

  MySupplierImpl(const CORBA::ORB_ptr orb,
                 const CosNotifyChannelAdmin::EventChannel_ptr channel);
  
  ~MySupplierImpl();

  void enviar(const CORBA::Any& alarm_info) 
    throw (CORBA::SystemException);

  void disconnect_push_supplier() 
    throw (CORBA::SystemException);

  void destroy() 
    throw (CORBA::SystemException);

  void disconnect();
  
  void subscription_change(const CosNotification::EventTypeSeq&, 
                           const CosNotification::EventTypeSeq&)
    throw (CORBA::SystemException, CosNotifyComm::InvalidEventType);
  
  void set_reference(Event::Server_ptr ref);

};

#endif
