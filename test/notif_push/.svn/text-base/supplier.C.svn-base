#ifdef _TAO
#include "EventS.h"
#include "orbsvcs/orbsvcs/CosEventChannelAdminS.h"
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#elif defined _TIDORB
#include "CosEventChannelAdmin.h"
#include "CosNotifyChannelAdmin.h"
#include "Event.h"
#endif

#include "MySupplierImpl.h" 

#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#include <iostream>
#include <sys/time.h>
#include <time.h>

using namespace std;

Event::Server_var ref;

void TerminarEjecucion (int){
  cerr << "CTRL-C recibido: Terminado ejecucion..." << endl;
  //ref->disconnect_push_supplier();
  ref->destroy();    
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

    // Creamos un objeto de clase MySupplierImpl
    MySupplierImpl *servant = new MySupplierImpl(orb, channel);

    // Instanciamos el objeto y lo activamos
    ref = servant->_this();
    if (CORBA::is_nil(ref)) { 
      cerr << "[supplier] ERROR: ref  nula " << endl;
      return -1; 
    } 


#ifdef _TAO
    sleep(1);
#elif defined _TIDORB
    TIDThr::Thread::sleep(1000); // 1 '
#endif

    // Activa el POAManager
    manager->activate();

    servant->set_reference(ref);


    cerr << "[supplier] Crea el evento" << flush << endl;

    struct timeval t_inicio;
    struct timezone tz;
    Event::TIEMPO t_inicioidl;   
    CORBA::Any alarm;
    int num = 2000;
    char* cadena = new char [num];
    buildString(num, cadena);
   
    for(int i=0; i < 1000000; i++) {


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

      try{
        // Invocamos al metodo que envia el evento
        ref->enviar(alarm); 
      }
      catch(...){
      }
    }
    
    orb->run();
// #ifdef _TAO
//     sleep(100);
// #elif defined _TIDORB
//     TIDThr::Thread::sleep(10000); // 10 ''
// #endif

    cerr << "[supplier] Desconectando... " << flush << endl;
    ref->disconnect_push_supplier();
    ref->destroy();    

    cerr << "[supplier] Terminando" << flush << endl;
    orb->shutdown(true);
    orb->destroy();

    delete servant;

  } catch(CORBA::Exception& exc) {
    cerr << "[server] Excepcion: " << exc << endl;
    return 1;
  }

}
