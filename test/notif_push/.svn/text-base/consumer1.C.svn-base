#ifdef _TAO
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#include "orbsvcs/orbsvcs/CosNotifyCommS.h"
#include "EventC.h"
#elif defined _TIDORB
#include "CosEventChannelAdmin.h"
#include "CosNotifyChannelAdmin.h"
#include "Event.h"
#endif

#include "MyConsumerImpl.h"

#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#include <iostream>

using namespace std;


CosNotifyChannelAdmin::ProxyPushSupplier_var supplier = NULL;
CosNotifyChannelAdmin::ConsumerAdmin_var consumeradmin = NULL;

void TerminarEjecucion (int){
  cerr << "CTRL-C recibido: Terminado ejecucion..." << endl;
  cerr << "[consumer1] disconnect .... " << endl;
  supplier->disconnect_push_supplier();
  consumeradmin->destroy();
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
      cerr << "[consumer1] ERROR: canal nulo " << endl;
      return -1; 
    } 


    // cerr << "[consumer1] ChannelId " << channel->get_channelID() << endl;

    // Crea un objeto de la clase MyConsumerImpl
    MyConsumerImpl* servant = new MyConsumerImpl();

    // Instanciamos el objeto y lo activamos
#ifdef _TAO
    CosNotifyComm::PushConsumer_ptr ref = servant->_this();
#else
    CosEventComm::PushConsumer_ptr ref = servant->_this();
#endif

    if (CORBA::is_nil(ref)) { 
      cerr << "[consumer1] ERROR: ref  nula " << endl;
      return -1; 
    } 
    CosNotifyChannelAdmin::AdminID id;
    CosNotifyChannelAdmin::ProxyID proxy_id;

    // Obtenemos la referencia de un ConsumerAdmin nuevo 
    consumeradmin = 
      channel->new_for_consumers(CosNotifyChannelAdmin::AND_OP, id);
    cerr << "[consumer1] ConsumerAdminId: " << id << endl;

    try{

      // Obtenemos la referencia a un ProxyPushSupplier
      CosNotifyChannelAdmin::ProxySupplier_var proxy_supplier;
      proxy_supplier = consumeradmin->obtain_notification_push_supplier(
                                             CosNotifyChannelAdmin::ANY_EVENT,
                                             proxy_id);
      supplier = 
        CosNotifyChannelAdmin::ProxyPushSupplier::_narrow(proxy_supplier);

      //   CosEventChannelAdmin::ProxyPushSupplier_var event_supplier;
      //   event_supplier = consumeradmin->obtain_push_supplier();
      //   supplier = CosNotifyChannelAdmin::ProxyPushSupplier::_narrow(event_supplier);


    }
    catch(const CORBA::Exception &ex){
      cerr << "[consumer1] Exception: " << ex << endl;
      return -1;
    }



    // TODO: Creamos la referencia a un filtro para el ConsumerAdmin 

    CosNotifyFilter::FilterFactory_var filterFactory = channel->default_filter_factory();
    cerr << "[consumer1] FilterFactory creado" << endl;
    CosNotifyFilter::Filter_ptr filter = filterFactory->create_filter("EXTENDED_TCL");

#ifdef _TIDORB
    // CREAMOS LAS RESTRICCIONES 
    CosNotification::_EventType eventType_I[2]; // ¿donde esta en TAO ??? -> No soportado

    eventType_I[0].domain_name = "URJC";
    eventType_I[0].type_name = "Entregas";
    eventType_I[1].domain_name = "TID";
    eventType_I[1].type_name = "Proyectos";
  
    CosNotification::_EventType eventType_II[1];
    eventType_II[0].domain_name = "Morfeo";
    eventType_II[0].type_name = "Difusiones";
  
    char * constraint_I = "$.campo_uno == 5";
    char * constraint_II = "$.campo_dos == 1";
  
    CosNotification::EventTypeSeq eventTypeSeq_I(2, 2, eventType_I, false);
    CosNotification::EventTypeSeq eventTypeSeq_II(1, 1, eventType_II, false);
  
    CosNotifyFilter::ConstraintExp constraintExp_I(eventTypeSeq_I, constraint_I);
    CosNotifyFilter::ConstraintExp constraintExp_II(eventTypeSeq_II, constraint_II);
  
    CosNotifyFilter::ConstraintExpSeq constraintExpSeq(2);
    constraintExpSeq.length(2);
  
    constraintExpSeq[0]=constraintExp_I;
    constraintExpSeq[1]=constraintExp_II;

#elif defined _TAO
    CosNotifyFilter::ConstraintExpSeq constraintExpSeq(1);
    constraintExpSeq.length(1);
    constraintExpSeq[0].event_types.length(0);
    constraintExpSeq[0].constraint_expr = CORBA::string_dup ("Morfeo");
#endif

    // INSERTAMOS LAS RESTRICCIONES AL FILTRO
    CosNotifyFilter::ConstraintInfoSeq* constraintInfoSeq;
    constraintInfoSeq = filter->add_constraints(constraintExpSeq);

    // INSERTAMOS EL FILTRO DENTRO DEL CONSUMERADMIN 
    cerr << "[consumer1] filter añadido" << endl;
    CosNotifyFilter::FilterID filterID = consumeradmin->add_filter(filter);

    // BORRAMOS EL FILTRO  DEL CONSUMERADMIN
    //consumeradmin->remove_filter(filterID);

//     //   ConstraintAdmin::Discriminator_ptr filtro = supplier2->forwarding_discriminator();
//     //   ConstraintAdmin::ConstraintId id_filtro = 
//     //     filtro->add_constraint("($.id>2 and $.id<=3) or ($.id > 4 and $.id <= 5)"); 



    // Conectamos el ProxyPushSupplier al cliente (consumer)
    try{
      cerr << "[consumer1] connect_any_push_consumer(ref)" << endl;
      supplier->connect_any_push_consumer(ref);
      cerr << "[consumer1] connect_any_push_consumer(ref) terminado" << endl;
    }
    catch(const CORBA::Exception &ex){
      cerr << "[consumer1] Exception: " << ex << endl;
      return -1;
    }



    cerr << "[consumer1] Esperando" << endl;

    // Activa el POAManager
    manager->activate(); 

    // Acepta peticiones
    cerr << "[consumer1] Esperando eventos.... " << endl;


    orb->run();  
#ifdef _TAO
    sleep(25);         // 25 ''
#elif defined _TIDORB
    TIDThr::Thread::sleep(20000); // 20 ''
#endif

    cerr << "[consumer1] disconnect .... " << endl;
    supplier->disconnect_push_supplier();
    consumeradmin->destroy();

    cerr << "[consumer1] Terminando " << endl;
    orb->shutdown(true);
    orb->destroy();



  } catch(CORBA::Exception& exc) {
    cerr << "[consumer1] Excepcion: " << exc << endl;
    return 1;
  }

}
