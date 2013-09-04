#ifdef _TAO
#include "EventS.h"
#include "orbsvcs/orbsvcs/CosEventChannelAdminS.h"
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#elif defined _TIDORB
#include "CosEventChannelAdmin.h"
#include "CosNotifyChannelAdmin.h"
#include "Event.h"
#include "PortableServer.h"
#endif


#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#include <iostream>
#include <sys/time.h>
#include <time.h>

using namespace std;


CosNotifyChannelAdmin::ProxyPushConsumer_var _consumer = NULL;
CosNotifyChannelAdmin::SupplierAdmin_var _supplier_admin = NULL;
    
void TerminarEjecucion (int){
  cerr << "CTRL-C recibido: Terminado ejecucion...";
  try{
    _consumer->disconnect_push_consumer();
  } catch (...){
    cerr << "[supplier3] Excepcion en disconnect_push_consumer";
  }

  try{
    _supplier_admin->destroy();    
  } catch (...){
    cerr << "[supplier3] Excepcion en destroy";
  }

  cerr << " STOP." << endl;
  exit(0);

}

void buildString (int n, char* c) {
  for  (int i=0; i<n; i++)
    c[i]='a';
}

int main(int argc, char* argv[]) {

  char aux1[1000];

  signal(SIGINT, TerminarEjecucion);

  try {

    // Inicializacion del ORB 
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, "");
    
    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
    PortableServer::POA_var root_poa = PortableServer::POA::_narrow(obj);
    PortableServer::POAManager_var manager = root_poa->the_POAManager();


    // Recoge la referencia al canal
    cin >> aux1;   
    obj = orb->string_to_object(aux1);

    CosNotifyChannelAdmin::EventChannel_var channel;
    channel = CosNotifyChannelAdmin::EventChannel::_narrow(obj);
    if (CORBA::is_nil(channel)) { 
      cerr << "[supplier] ERROR: canal nulo " << endl;
      return -1; 
    } 
    
    //cerr << "[supplier] ChannelId " << channel->get_channelID() << endl;

    CosNotifyChannelAdmin::AdminID id;
    _supplier_admin = 
      channel->new_for_suppliers(CosNotifyChannelAdmin::AND_OP,id);
    cerr << "[supplier] SupplierAdminId = " << id << endl;
    
    CosNotifyChannelAdmin::ProxyID proxy_id;
    CosNotifyChannelAdmin::ProxyConsumer_var proxy_consumer;
    proxy_consumer = _supplier_admin->obtain_notification_push_consumer(
                                                 CosNotifyChannelAdmin::ANY_EVENT, 
                                                 proxy_id);
    cerr << "[supplier] ProxyId = " << proxy_id << endl;

    _consumer = 
      CosNotifyChannelAdmin::ProxyPushConsumer::_narrow(proxy_consumer);
    
    try{
      
      CosNotifyComm::PushSupplier_ptr supplier = CosNotifyComm::PushSupplier::_nil();
      _consumer->connect_any_push_supplier(supplier);
      
    } catch (CORBA::Exception& exc) {
      cerr << "[supplier] Exception in _consumer->connect_push_supplier(...)";
      cerr << exc << endl;
    } catch (...) {
      cerr << "[supplier] Unknowed exception ";
      cerr << "in _consumer->connect_push_supplier(...)";
    }



    cerr << "[supplier] Crea el evento" << flush << endl;
    struct timeval t_inicio;
    struct timezone tz;
    Event::TIEMPO t_inicioidl;   
    CORBA::Any alarm;
    int num = 200000;
    char* cadena = new char [num];
    buildString(num, cadena);
   
    for(int i=0; i < 100; i++) {

      // Rellenamos la informacion del evento   
      gettimeofday(&t_inicio,&tz);
      t_inicioidl.tv_sec  = t_inicio.tv_sec;
      t_inicioidl.tv_usec = t_inicio.tv_usec;
      t_inicioidl.id = (CORBA::Long)i;
      t_inicioidl.data <<= cadena;

      cerr << "[supplier] componiendo alarma: ";
      cerr << "    Evento: " << i << " Inicio:  "  << t_inicio.tv_sec << "/" 
           << t_inicio.tv_usec << endl;
      alarm <<= (t_inicioidl); 


      // Enviamos el evento
      try{
        _consumer->push(alarm);
      }
      catch(CosEventComm::Disconnected& ex ){
        cerr << "[supplier] Exception CosEventComm::Disconnected hacer push " << endl;
        orb->shutdown(true);
        orb->destroy();
        exit(1);
      }

    } // for


    cerr << "[supplier] Desconectando... " << flush << endl;
    _consumer->disconnect_push_consumer();
    _supplier_admin->destroy();

    cerr << "[supplier] Terminando" << flush << endl;
    orb->shutdown(true);
    orb->destroy();


  } catch(CORBA::Exception& exc) {
    cerr << "[supplier] Excepcion: " << exc << endl;
    return 1;
  }

}
