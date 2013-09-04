#ifdef _TAO
#include "tao/corba.h"
#include "orbsvcs/orbsvcs/CosEventChannelAdminS.h"
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#elif defined _TIDORB
#include "POA_CosEventChannelAdmin.h"
#include "POA_CosNotifyChannelAdmin.h"
#elif defined _MICO
#include <coss/CosNaming.h>
#include <coss/CosEventComm.h>
#include <coss/CosEventChannelAdmin.h>
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
CosEventChannelAdmin::EventChannel_var channel = NULL;
CosNotifyChannelAdmin::EventChannelFactory_var factory = NULL;


void TerminarEjecucion (int){
  cerr << "CTRL-C recibido: Terminado ejecucion..." << endl;
  channel->destroy();
  orb->shutdown(true);
  orb->destroy();
  exit(0);
}



int main(int argc, char* argv[]) {

  char aux1[1000];

  signal(SIGINT, TerminarEjecucion);

  try {

    // Inicializacion del ORB 
    orb = CORBA::ORB_init(argc, argv, "");
    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");

    PortableServer::POA_var root_poa = PortableServer::POA::_narrow(obj);
    PortableServer::POAManager_var manager = root_poa->the_POAManager();

#ifdef _MICO
    CORBA::Object_var nsobj =
      orb->resolve_initial_references ("NameService");
    assert (! CORBA::is_nil (nsobj));
    
    CosNaming::NamingContext_var nc = 
      CosNaming::NamingContext::_narrow (nsobj);
    assert (! CORBA::is_nil (nc));
    
    CosNaming::Name name;
    name.length (1);
    name[0].id = CORBA::string_dup ("EventChannelFactory");
    name[0].kind = CORBA::string_dup ("");
    
    CORBA::Object_var obj1;
    
    try {
      obj1 = nc->resolve (name);
    }
    catch (...) {
      cerr << "Cannot find EventChannelFactory !" << endl;
      return -1;
    }
    
    obj = nc->resolve (name);
    SimpleEventChannelAdmin::EventChannelFactory_var ecf;
    CosEventChannelAdmin::EventChannel_var channel;
    ecf = SimpleEventChannelAdmin::EventChannelFactory::_narrow (obj1);
    assert (! CORBA::is_nil (ecf));
    channel = ecf->create_eventchannel ();
    assert (! CORBA::is_nil (channel));

#else
    // Recoge la referencia a una factoria del servicio de  notificaciones
    cin >> aux1;   
    obj = orb->string_to_object(aux1);

    //CosNotifyChannelAdmin::EventChannelFactory_var factory;
    factory = CosNotifyChannelAdmin::EventChannelFactory::_narrow(obj);
    if (CORBA::is_nil(factory)) { 
      cerr << "[server] ERROR: factoria nula " << endl;
      return -1; 
    } 

    //CosEventChannelAdmin::EventChannel_var channel;
    CosNotification::QoSProperties initial_qos;
    CosNotification::AdminProperties initial_admin;
    CosNotifyChannelAdmin::ChannelID id;

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
#endif

    // Vuelca en salida estandar la referencia como cadena de caracteres
    CORBA::String_var str = orb->object_to_string(channel);
    cout << str << endl << flush;

    // Activa el POAManager
    manager->activate();

    // Acepta peticiones
    cerr << "[server] Preparado..." << endl;
    orb->run(); 

#ifdef _TAO
    sleep(250);         // 25 ''
#elif defined _TIDORB
    TIDThr::Thread::sleep(25000); // 25 ''
#endif

    orb->shutdown(true);
    orb->destroy();


  } catch(CORBA::Exception& exc) {
    cerr << "[server] Excepcion: " << exc << endl;
    return 1;
  }

  return 0;
}
