#ifdef _TAO
#include "tao/corba.h"
#include "orbsvcs/CosEventChannelAdminS.h"
#include "orbsvcs/CosNotifyChannelAdminS.h"
#include "TimeBaseS.h"
#elif defined _TIDORB
#include "POA_CosEventChannelAdmin.h"
#include "POA_CosNotifyChannelAdmin.h"
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

CORBA::ORB_var orb = NULL;
CosNotifyChannelAdmin::EventChannel_var channel = NULL;
CosNotifyChannelAdmin::EventChannelFactory_var factory = NULL;

void TerminarEjecucion (int){
  cerr << "CTRL-C recibido: Terminado ejecucion..." << endl;
  try{
    channel->destroy();
    orb->shutdown(true);
    orb->destroy();
  } catch(CORBA::Exception& exc) {
    cerr << "[server] Excepcion: " << exc << endl;
  }
  exit(0);
}


int main(int argc, char* argv[]) {
  cerr << "Comenzando ejecucion ..." << endl;
  char aux1[1000];

  signal(SIGINT, TerminarEjecucion);

  try {

    // Inicializacion del ORB 
    orb = CORBA::ORB_init(argc, argv, "");
    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");

    PortableServer::POA_var root_poa = PortableServer::POA::_narrow(obj);
    PortableServer::POAManager_var manager = root_poa->the_POAManager();

    try{
      cerr << "Obtaining Initial References to NotificationService .." << endl;
      // Way 1: read IOR from file
      // cin >> aux1;   
      // obj = orb->string_to_object(aux1);
      // Way 2: rir
#ifndef _TAO
//       obj = orb->resolve_initial_references("NotificationService");
#else
//       obj = orb->resolve_initial_references("NotificationService");
      //obj = orb->resolve_initial_references("EventChannelFactory");
#endif
      // Way 3: corbaloc
      const char *corbaloc = "corbaloc:iiop:1.2@127.0.0.1:15001/NotificationService";
      obj = orb->string_to_object(corbaloc);
    } catch (const CORBA::Exception& ex) {
      cerr << "[server] Excepcion: " << ex << endl;
      return 1;
    }

    // CosNotifyChannelAdmin::EventChannelFactory_var factory;
    factory = CosNotifyChannelAdmin::EventChannelFactory::_narrow(obj);
    if (CORBA::is_nil(factory)) { 
      cerr << "[server] ERROR: factoria nula " << endl;
      return -1; 
    } 

    CosNotification::QoSProperties initial_qos;
    CosNotification::AdminProperties initial_admin;
    CosNotifyChannelAdmin::ChannelID id;

    initial_qos.length(0);
    initial_admin.length(3);
    initial_admin[0].name = CORBA::string_dup("MaxQueueLength");
    initial_admin[0].value <<= (CORBA::Long) 1000;
    initial_admin[1].name = CORBA::string_dup("MaxConsumers");
    initial_admin[1].value <<= (CORBA::Long) 0;
    initial_admin[2].name = CORBA::string_dup("MaxSuppliers");
    initial_admin[2].value <<= (CORBA::Long) 0;


    try { 
      // Crear el canal
      channel = factory->create_channel(initial_qos, initial_admin, id);
      
    } catch (CosNotification::UnsupportedQoS &ex) { 
      cerr << "[server] CosNotification::UnsupportedQoS: " << ex._name(); 
      return -1; 
    } catch (CosNotification::UnsupportedAdmin &ex) { 
      cerr << "[server] CosNotification::UnsupportedAdmin: " << ex._name(); 
      return -1; 
    } catch (CORBA::SystemException &ex) { 
      cerr << "[server] SystemExcepcion: " << ex._name(); 
      return -1; 
    } 


    // Vuelca en salida estandar la referencia como cadena de caracteres
    CORBA::String_var str = orb->object_to_string(channel);
    cout << str << endl << flush;

    // Activa el POAManager
    manager->activate();

    // Acepta peticiones
    cerr << "[server] Preparado en el canal " << id  << endl;

    orb->run();

#ifdef _TAO
    sleep(25);         // 25 ''
#elif defined _TIDORB
    TIDThr::Thread::sleep(25000); // 25 ''
#endif


    // Obtener todos los IDs de los canales creados
    CosNotifyChannelAdmin::ChannelIDSeq* channels =
      factory->get_all_channels();
    for (CORBA::ULong i = 0;  i < channels->length(); i++)
      cerr << "[server] ChannelID: " << (*channels)[i] << endl;

    // Obtener todos los IDs de los ConsummerAdmins creados
    CosNotifyChannelAdmin::AdminIDSeq* admins =
      channel->get_all_consumeradmins();
    for (CORBA::ULong i = 0;  i < admins->length(); i++)
      cerr << "[server] ConsumerAdminID: " << (*admins)[i] << endl;

    // Obtener todos los IDs de los SupplierAdmins creados
    CosNotifyChannelAdmin::AdminIDSeq* admins2 =
      channel->get_all_supplieradmins();
    for (CORBA::ULong i = 0;  i < admins2->length(); i++)
      cerr << "[server] SupplierAdminID: " << (*admins2)[i] << endl;

    
#ifdef _TAO
    sleep(5);         // 5 ''
#elif defined _TIDORB
    TIDThr::Thread::sleep(5000); // 5 ''
#endif
    
    // Destruir el canal
    channel->destroy();

    orb->shutdown(true);
    orb->destroy();
    
  } catch(CORBA::Exception& exc) {
    cerr << "[server] Excepcion: " << exc << endl;
    return 1;
  }

  return 0;
}
