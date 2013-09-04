#include "MySupplierImpl.h"


MySupplierImpl::MySupplierImpl(const CORBA::ORB_ptr orb,
                               const CosEventChannelAdmin::EventChannel_ptr channel)
{
  // Constructor de la clase que implementa la parte servidora

  _the_orb     = CORBA::ORB::_duplicate(orb);
  _the_channel = CosEventChannelAdmin::EventChannel::_duplicate(channel);
  _consumer    = CosEventChannelAdmin::ProxyPushConsumer::_nil();
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

    if (CORBA::is_nil((CosEventChannelAdmin::ProxyPushConsumer_ptr)_consumer)) {
      cerr << "[MySupplierImpl] eviar 1" << endl;
      CosEventChannelAdmin::SupplierAdmin_var _supplier_admin = 
        _the_channel->for_suppliers();
      cerr << "[MySupplierImpl] eviar 2" << endl;
      _consumer = _supplier_admin->obtain_push_consumer();
      cerr << "[MySupplierImpl] eviar 3" << endl;
      try{
        CosEventComm::PushSupplier_ptr supplier = CosEventComm::PushSupplier::_nil();
        _consumer->connect_push_supplier(supplier);
        if (_consumer == NULL)
          cerr << "[MySupplierImpl] consumer NULO 5" << endl;

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
       
        cerr << "[MySupplierImpl] eviar 4" << endl;
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
    
    _consumer = CosEventChannelAdmin::ProxyPushConsumer::_nil();
    
  } catch (CORBA::Exception& exc) {

    cerr << "[MySupplierImpl] Unknowed exception in  _consumer->push(_alarm_info)";
    cerr << exc << endl;
    
    if (!CORBA::is_nil((CosEventChannelAdmin::ProxyPushConsumer_ptr)_consumer)) {
      
      try{
        
        _consumer->disconnect_push_consumer();
        
      } catch (CORBA::Exception& exc) {
        cerr << "[MySupplierImpl] Exception in _consumer->disconnect_push_consumer()";
        cerr << exc << endl;
      } catch (...) {
        cerr << "[MySupplierImpl] Unknowed exception ";
        cerr << "in _consumer->disconnect_push_consumer()";
      }
      
    }
    
    _consumer = CosEventChannelAdmin::ProxyPushConsumer::_nil();
    
  }


};

void MySupplierImpl::disconnect_push_supplier() 
  throw (CORBA::SystemException)
{
  // Metodo que permite la desconexion del ProxyPushConsumer

  if (!CORBA::is_nil((CosEventChannelAdmin::ProxyPushConsumer_ptr)_consumer)) {

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

  _consumer = CosEventChannelAdmin::ProxyPushConsumer::_nil();

};




