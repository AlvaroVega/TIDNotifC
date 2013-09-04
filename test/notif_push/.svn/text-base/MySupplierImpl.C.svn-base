#include "MySupplierImpl.h"


MySupplierImpl::MySupplierImpl(const CORBA::ORB_ptr orb,
                               const CosNotifyChannelAdmin::EventChannel_ptr channel)
{
  // Constructor de la clase que implementa la parte servidora

  _the_orb     = CORBA::ORB::_duplicate(orb);
  _the_channel = CosNotifyChannelAdmin::EventChannel::_duplicate(channel);
  _consumer    = CosNotifyChannelAdmin::ProxyPushConsumer::_nil();
  _supplier_admin = CosNotifyChannelAdmin::SupplierAdmin::_nil();
};


MySupplierImpl::~MySupplierImpl()
{
  // Destructor de la parte servidora implementada
};


void MySupplierImpl::enviar(const CORBA::Any& _alarm_info) 
  throw (CORBA::SystemException)
{
  //  cerr << "[MySupplierImpl] MySupplierImpl::enviar" << endl;

  try{

    if (CORBA::is_nil((CosNotifyChannelAdmin::ProxyPushConsumer_ptr)_consumer)) {
      cerr << "[MySupplierImpl] Preparando para enviar... " << endl;

      CosNotifyChannelAdmin::AdminID id;
      _supplier_admin = 
        _the_channel->new_for_suppliers(CosNotifyChannelAdmin::AND_OP,id);
      cerr << "[MySupplierImpl] SupplierAdminId = " << id << endl;

//       CosEventChannelAdmin::ProxyPushConsumer_var event_consumer;
//       event_consumer = _supplier_admin->obtain_push_consumer();
      CosNotifyChannelAdmin::ProxyID proxy_id;
      CosNotifyChannelAdmin::ProxyConsumer_var proxy_consumer;
      proxy_consumer = _supplier_admin->obtain_notification_push_consumer(
                                                     CosNotifyChannelAdmin::ANY_EVENT, 
                                                     proxy_id);
      cerr << "[MySupplierImpl] ProxyId = " << proxy_id << endl;

      _consumer = CosNotifyChannelAdmin::ProxyPushConsumer::_narrow(proxy_consumer);

      try{

        //CosNotifyComm::PushSupplier_ptr supplier = CosNotifyComm::PushSupplier::_nil();
        //_consumer->connect_any_push_supplier(supplier);
        _consumer->connect_any_push_supplier(supplier_ref);
        if (_consumer == NULL) cerr << "[MySupplierImpl] consumer NULO 5" << endl;

      } catch (CORBA::Exception& exc) {
        cerr << "[MySupplierImpl] Exception in _consumer->connect_push_supplier(...)";
        cerr << exc << endl;
      } catch (...) {
        cerr << "[MySupplierImpl] Unknowed exception ";
        cerr << "in _consumer->connect_push_supplier(...)";
      }

    }
    // else{
      // Invoca al metodo push del ProxyPushConsumer para enviar el evento por el canal
      if (_consumer == NULL)
        cerr << "[MySupplierImpl] consumer NULO 2" << endl;
      else{
        cerr << "[MySupplierImpl] eviando " << endl;
        _consumer->push(_alarm_info);
      }

      //}
    

  } catch (CosEventComm::Disconnected& exc) {

    cerr << "[MySupplierImpl] Disconnected in  _consumer->push(_alarm_info) " <<  endl;
    
//     if (!CORBA::is_nil((CosEventChannelAdmin::ProxyPushConsumer_ptr)_consumer)) {

//       try{
        
//         _consumer->disconnect_push_consumer();
        
//       } catch (CORBA::Exception& exc) {
//         cerr << "[MySupplierImpl] Exception in _consumer->disconnect_push_consumer()";
//         cerr << exc << endl;
//       } catch (...) {
//         cerr << "[MySupplierImpl] Unknowed exception ";
//         cerr << "in _consumer->disconnect_push_consumer()";
//       }
      
//     }
    
    _consumer = CosNotifyChannelAdmin::ProxyPushConsumer::_nil();
    
  } catch (CORBA::Exception& exc) {

    cerr << "[MySupplierImpl] Unknowed exception in  _consumer->push(_alarm_info)";
    cerr << exc << endl;
    
    if (!CORBA::is_nil((CosNotifyChannelAdmin::ProxyPushConsumer_ptr)_consumer)) {
      
      try{
        cerr << "[MySupplierImpl] Disconnecting ... ";
        _consumer->disconnect_push_consumer();
        
      } catch (CORBA::Exception& exc) {
        cerr << "[MySupplierImpl] Exception in _consumer->disconnect_push_consumer()";
        cerr << exc << endl;
      } catch (...) {
        cerr << "[MySupplierImpl] Unknowed exception ";
        cerr << "in _consumer->disconnect_push_consumer()";
      }
      
    }
    
    _consumer = CosNotifyChannelAdmin::ProxyPushConsumer::_nil();
    
  }


};

void MySupplierImpl::disconnect_push_supplier() 
  throw (CORBA::SystemException)
{
  // Metodo que permite la desconexion del ProxyPushConsumer

  cerr << "[MySupplierImpl] disconnect_push_supplier recibido:" << endl;

  if (!CORBA::is_nil((CosNotifyChannelAdmin::ProxyPushConsumer_ptr)_consumer)) {

    try {

      _consumer->disconnect_push_consumer();

    } catch (CORBA::Exception& exc) {
      cerr << "[MySupplierImpl] Exception in _consumer->disconnect_push_consumer() :" ;
      cerr << exc << endl;
    } catch (...) {
      cerr << "[MySupplierImpl] Exception in _consumer->disconnect_push_consumer()";
      cerr << "no determinada " << endl;
    }

  }

  _consumer = CosNotifyChannelAdmin::ProxyPushConsumer::_nil();

};


void MySupplierImpl::destroy() throw (CORBA::SystemException)
{


  CosNotifyChannelAdmin::ProxyIDSeq_var proxys =
    _supplier_admin->push_consumers();
  
//   for (int i = 0;  i < proxys->length(); i++)
//     cerr << "[supplier1] ProxyID: " << (*proxys)[i] << endl;

  _supplier_admin->destroy();
}

void MySupplierImpl::disconnect() 
{
}

void MySupplierImpl::subscription_change(const CosNotification::EventTypeSeq&, 
                                         const CosNotification::EventTypeSeq&) 
  throw (CORBA::SystemException, CosNotifyComm::InvalidEventType)
{
}


void MySupplierImpl::set_reference(Event::Server_ptr ref)
{
  supplier_ref = Event::Server::_duplicate(ref);
}
