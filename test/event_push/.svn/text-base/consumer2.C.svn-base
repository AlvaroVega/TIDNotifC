#ifdef _TAO
#include "orbsvcs/orbsvcs/CosEventChannelAdminS.h"
#include "orbsvcs/orbsvcs/CosEventCommS.h"
#include "EventC.h"
#elif defined _TIDORB
#include "CosEventChannelAdmin.h"
#include "CosNotifyChannelAdmin.h"
#include "Event.h"
#elif defined _MICO
#include <coss/CosEventComm.h>
#include <coss/CosEventChannelAdmin.h>
#include "Event.h"
#endif

#include "MyConsumerImpl.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]){

  char aux1[1000];

  // Recoge la referencia del canal de notificaciones
  CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, "");
  CORBA::Object_var obj1 = orb->resolve_initial_references("RootPOA");
  PortableServer::POA_var poa = PortableServer::POA::_narrow(obj1);
  PortableServer::POAManager_var manager = poa->the_POAManager();

  // Recoge la referencia al canal
  cin >> aux1;   
  CORBA::Object_var obj = orb->string_to_object(aux1);

  CosEventChannelAdmin::EventChannel_var channel;
  channel =  CosEventChannelAdmin::EventChannel::_narrow(obj);
  if (CORBA::is_nil(channel)) { 
    cerr << "[consumer2] ERROR: canal nulo " << endl;
    return -1; 
  } 


  // Crea un objeto de la clase MyConsumerImpl
  MyConsumerImpl* servant = new MyConsumerImpl();

  // Instanciamos el objeto y lo activamos
  CORBA::Object_var aux = servant->_this();
  CosEventComm::PushConsumer_var ref = CosEventComm::PushConsumer::_narrow(aux);

  // Obtenemos la referencia de un ConsumerAdmin nuevo 
  CosEventChannelAdmin::ConsumerAdmin_var consumeradmin = channel->for_consumers();
  CosEventChannelAdmin::ProxyPushSupplier_var supplier;
  try{
    // Obtenemos la referencia a un ProxyPushSupplier
    supplier = consumeradmin->obtain_push_supplier();
  }
  catch(const CORBA::Exception &ex){
    cerr << "[consumer2] Exception: " << ex << endl;
    return -1;
  }

//   CosEventChannelAdmin::ProxyPushSupplier_var supplier2 = 
//     CosEventChannelAdmin::ProxyPushSupplier::_narrow(supplier);


//   //Creamos la referencia a un filtro para el ConsumerAdmin 
//   ConstraintAdmin::Discriminator_ptr filtro = supplier2->forwarding_discriminator();
//   ConstraintAdmin::ConstraintId id_filtro = 
//     filtro->add_constraint("($.id>2 and $.id<=3) or ($.id > 4 and $.id <= 5)"); 

  // Conectamos el ProxyPushSupplier al cliente (consumer)
  try{
    supplier->connect_push_consumer(ref);
  }
  catch(const CORBA::Exception &ex){
    cerr << "[consumer2] Exception: " << ex << endl;
    return -1;
  }

  cerr << "[consumer2] Esperando" << endl;

  // Activa el POAManager
  manager->activate(); 

  // Acepta peticiones
  orb->run();

}
