#ifdef _TAO
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#include "orbsvcs/orbsvcs/CosNotifyCommS.h"
#include "EventC.h"
#elif defined _TIDORB
#include "CosEventChannelAdmin.h"
#include "CosNotifyChannelAdmin.h"
#include "Event.h"
#endif

#include "MyConsumerImpl2.h"

#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#include <iostream>

using namespace std;

CosNotifyChannelAdmin::StructuredProxyPushSupplier_var supplier = NULL;
CosNotifyChannelAdmin::ConsumerAdmin_var consumeradmin = NULL;

void TerminarEjecucion (int){
  cerr << "CTRL-C recibido: Terminado ejecucion..." << endl;
  cerr << "[consumer2] disconnect .... " << endl;
  supplier->disconnect_structured_push_supplier();
  cerr << "[consumer2] destruyendo .... " << endl;
  consumeradmin->destroy();
  cerr << "[consumer2] Terminando " << endl;
#ifdef _TAO
  sleep(20);         // 2 ''
#elif defined _TIDORB
  TIDThr::Thread::sleep(2000); // 2 ''
#endif
  exit(0);
}


int main(int argc, char* argv[]){

  char aux1[1000];

  signal(SIGINT, TerminarEjecucion);


  try{
    // Inicializacion del ORB 
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, "");

    CORBA::Object_var obj1 = orb->resolve_initial_references("RootPOA");
    PortableServer::POA_var poa = PortableServer::POA::_narrow(obj1);
    PortableServer::POAManager_var manager = poa->the_POAManager();

    // Recoge la referencia al canal
    cin >> aux1;   
    CORBA::Object_var obj = orb->string_to_object(aux1);

    CosNotifyChannelAdmin::EventChannel_var channel;
    channel = CosNotifyChannelAdmin::EventChannel::_narrow(obj);
    if (CORBA::is_nil(channel)) { 
      cerr << "[consumer2] ERROR: canal nulo " << endl;
      return -1; 
    } 


    // Crea un objeto de la clase MyConsumerImpl
    MyConsumerImpl2* servant = new MyConsumerImpl2();

    // Instanciamos el objeto y lo activamos
    CosNotifyComm::StructuredPushConsumer_ptr ref = servant->_this();
    if (CORBA::is_nil(ref)) { 
      cerr << "[consumer2] ERROR: ref  nula " << endl;
      return -1; 
    } 
    CosNotifyChannelAdmin::AdminID id;
    CosNotifyChannelAdmin::ProxyID proxy_id;

    // Obtenemos la referencia de un ConsumerAdmin nuevo 
    consumeradmin = 
      channel->new_for_consumers(CosNotifyChannelAdmin::AND_OP, id);
    cerr << "[consumer2] ConsumerAdminId: " << id << endl;
 
    try{

      // Obtenemos la referencia a un ProxyPushSupplier
      CosNotifyChannelAdmin::ProxySupplier_var proxy_supplier;
      proxy_supplier = consumeradmin->obtain_notification_push_supplier(
                                             CosNotifyChannelAdmin::STRUCTURED_EVENT,
                                             proxy_id);
      supplier = 
        CosNotifyChannelAdmin::StructuredProxyPushSupplier::_narrow(proxy_supplier);

    }
    catch(const CORBA::Exception &ex){
      cerr << "[consumer2] Exception: " << ex << endl;
      return -1;
    }

    // Creamos la referencia a un filtro para el ConsumerAdmin 
    //   ConstraintAdmin::Discriminator_ptr filtro = supplier2->forwarding_discriminator();
    //   ConstraintAdmin::ConstraintId id_filtro = 
    //     filtro->add_constraint("($.id>2 and $.id<=3) or ($.id > 4 and $.id <= 5)"); 



    // Conectamos el StructuredProxyPushSupplier al cliente (consumer)
    try{
      supplier->connect_structured_push_consumer(ref);
    }
    catch(const CORBA::Exception &ex){
      cerr << "[consumer2] Exception: " << ex << endl;
      return -1;
    }



    cerr << "[consumer2] Esperando" << endl;

    // Activa el POAManager
    manager->activate(); 

    // Acepta peticiones
    cerr << "[consumer2] Esperando eventos.... " << endl;

    orb->run();
#ifdef _TAO
    sleep(25);         // 25 ''
#elif defined _TIDORB
    TIDThr::Thread::sleep(20000); // 5 ''
#endif

    cerr << "[consumer2] disconnect .... " << endl;
    supplier->disconnect_structured_push_supplier();
    consumeradmin->destroy();

    cerr << "[consumer2] Terminando " << endl;
    orb->shutdown(true);
    orb->destroy();

  } catch(CORBA::Exception& exc) {
    cerr << "[consumer2] Excepcion: " << exc << endl;
    return 1;
  }
}
