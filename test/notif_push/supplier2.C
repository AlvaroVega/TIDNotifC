#ifdef _TAO
#include "EventS.h"
#include "orbsvcs/orbsvcs/CosEventChannelAdminS.h"
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#elif defined _TIDORB
#include "CosEventChannelAdmin.h"
#include "CosNotifyChannelAdmin.h"
#include "Event.h"
#include "TimeBase.h"
#include "TIDorb/core.h"
#endif

#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#include <iostream>
#include <sys/time.h>
#include <time.h>

using namespace std;


CosNotifyChannelAdmin::StructuredProxyPushConsumer_var _consumer = NULL;
CosNotifyChannelAdmin::SupplierAdmin_var _supplier_admin = NULL;

void TerminarEjecucion (int){
  cerr << "CTRL-C recibido: Terminado ejecucion..." << endl;
  _consumer->disconnect_structured_push_consumer(); 
  _supplier_admin->destroy();    
  exit(0);
}


int main(int argc, char* argv[]) {

  char aux1[1000];
  time_t seconds;

  signal(SIGINT, TerminarEjecucion);

  time(&seconds);
  srand((unsigned int) seconds);

  try {

    // Inicializacion del ORB 
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, "");

    // Recoge la referencia al canal
    cin >> aux1;   
    CORBA::Object_var obj = orb->string_to_object(aux1);

    // Obtiene el canal
    CosNotifyChannelAdmin::EventChannel_var channel;
    channel = CosNotifyChannelAdmin::EventChannel::_narrow(obj);
    if (CORBA::is_nil(channel)) { 
      cerr << "[supplier2] ERROR: canal nulo " << endl;
      return -1; 
    } 

    // Obtiene el SupplierAdmin
    CosNotifyChannelAdmin::AdminID id;
    _supplier_admin = 
      channel->new_for_suppliers(CosNotifyChannelAdmin::AND_OP, id);
    cerr << "[supplier2] SupplierAdminId = " << id << endl;


    CosNotifyChannelAdmin::ProxyID proxy_id;
    CosNotifyChannelAdmin::ProxyConsumer_var proxy_consumer = 
      _supplier_admin->obtain_notification_push_consumer(
                                          CosNotifyChannelAdmin::STRUCTURED_EVENT,
                                          proxy_id);
    cerr << "[supplier2] ProxyId = " << proxy_id << endl;


    // Obtiene el StructuredProxyPushConsumer
    _consumer = 
      CosNotifyChannelAdmin::StructuredProxyPushConsumer::_narrow(proxy_consumer);

    try{
      CosNotifyComm::StructuredPushSupplier_var supplier = 
        CosNotifyComm::StructuredPushSupplier::_nil();
      _consumer->connect_structured_push_supplier(supplier);
      if (_consumer == NULL)  cerr << "[supplier2] consumer NULO 5" << endl;

    } catch (CORBA::Exception& exc) {
      cerr << "[supplier2] Exception in _consumer->connect_push_supplier(...)";
      cerr << exc << endl;
    } catch (...) {
      cerr << "[supplier2] Unknowed exception ";
      cerr << "in _consumer->connect_push_supplier(...)";
    }



#ifdef _TAO
    sleep(1);
#elif defined _TIDORB
    TIDThr::Thread::sleep(1000); // 1 ''
#endif

    cerr << "[supplier2] Crea un structured event" << flush << endl;

    try{
        
      CosNotification::StructuredEvent* event = NULL;
      int rnd = 0;
        
      for(int i=0; i < 200; i++) {

        rnd = rand();

        TimeBase::UtcT current_utc = TIDorb::core::util::Time::currentUtcT();
        TimeBase::UtcT future_utc  = TIDorb::core::util::Time::currentUtcT();
        TimeBase::UtcT pass_utc    = TIDorb::core::util::Time::currentUtcT();
        future_utc.time += (5 * 10000000); // now + 5 ''
        pass_utc.time   -= (5 * 10000000); // now - 5 ''



        // Rellenamos la informacion del evento   
        event = new CosNotification::StructuredEvent();
        event->header.fixed_header.event_name = 
          (rnd % 2) ? CORBA::string_dup("event_name") : CORBA::string_dup("other");
        event->header.fixed_header.event_type.domain_name = 
          (rnd % 2) ? CORBA::string_dup("domain_name") : CORBA::string_dup("other");
        event->header.fixed_header.event_type.type_name  = 
          (rnd % 2) ? CORBA::string_dup("type_name") : CORBA::string_dup("other");

        event->header.variable_header.length(5); 
        event->header.variable_header[0].name = CORBA::string_dup("EventReliability");
        event->header.variable_header[0].value <<= (CORBA::Short) 0;
        event->header.variable_header[1].name = CORBA::string_dup("Priority");
        event->header.variable_header[1].value <<= (CORBA::Short) 0;
        event->header.variable_header[2].name = CORBA::string_dup("StartTime");
        event->header.variable_header[2].value <<= current_utc;
        event->header.variable_header[3].name = CORBA::string_dup("StopTime");
        event->header.variable_header[3].value <<= pass_utc;
        event->header.variable_header[4].name = CORBA::string_dup("Timeout");
        event->header.variable_header[4].value <<= (TimeBase::TimeT) 0;

        event->filterable_data.length(2);
        event->filterable_data[0].name = CORBA::string_dup("int");
        event->filterable_data[0].value <<= ( rnd * 1000 ) ;
        event->filterable_data[1].name = CORBA::string_dup("string");
        event->filterable_data[1].value <<= ( (rnd % 2) ? 
                                              (const char*)"greater" : 
                                              (const char*)"smaller" );
        event->remainder_of_body <<= (const char*) "remainder_of_body";
        CORBA::Long my_long;
        event->filterable_data[0].value >>= my_long;


        cout << "Enviando mensage " << my_long;
        cout << ": " << event->header.fixed_header.event_type.domain_name << ", ";
        cout << event->header.fixed_header.event_type.type_name << endl; 
          
          
        // Envia el evento
        _consumer->push_structured_event(*event);


        delete event;
        event = NULL;
      } // for
      
      cerr << "[supplier2] Desconectando... " << flush << endl;
      _consumer->disconnect_structured_push_consumer();      

    } catch(...){
      cerr << "[supplier2] Excepcion " << endl;
    }
    _supplier_admin->destroy();    

    cerr << "[supplier2] Terminando" << flush << endl;
    orb->shutdown(true);
    orb->destroy();


  } catch(CORBA::Exception& exc) {
    cerr << "[supplier2] Excepcion: " << exc << endl;
    return 1;
  }

}
