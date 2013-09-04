// -*- c++ -*-
#ifdef _TAO
#include "tao/corba.h"
#include "orbsvcs/orbsvcs/CosEventChannelAdminS.h"
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#include "TimeBaseS.h"
#include "orbsvcs/Naming/Naming_Server.h"
#elif defined _TIDORB
#include "POA_CosEventChannelAdmin.h"
#include "POA_CosNotifyChannelAdmin.h"
#include "TimeBase.h"
#include "CosNaming.h"
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

char NotifyFactoryIOR[2048];
char ChannelIOR[2048];


void readNotifyFactoryIOR(){
  
  FILE *f=fopen("notify_factory.ior","r");
  
  if(f==0){
     fprintf(stderr,"Unable to open notify_factory.ior\n");
     exit(0);
  }
  fscanf (f, "%s\n", NotifyFactoryIOR);
  fclose(f);
}


// void writeChannelIOR(){
  
//   FILE *f=fopen("channel.ior","w");
  
//   if(f==0){
//      fprintf(stderr,"Unable to open channel.ior\n");
//      exit(0);
//   }
//   fprintf (f, "%s\n", ChannelIOR);
//   fclose(f);
// }



int main(int argc, char* argv[]) {
  cerr << "Comenzando ejecucion ..." << endl;


  try {

    // Inicializacion del ORB 
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, "");
    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");

    PortableServer::POA_var root_poa = PortableServer::POA::_narrow(obj);
    PortableServer::POAManager_var manager = root_poa->the_POAManager();


    //
    // Obtain NamincContext reference ...
    //
    CORBA::Object_var naming_context_object;
    CosNaming::NamingContext_ptr naming_context;
    try {
       naming_context_object = 
         orb->string_to_object("corbaloc:iiop:1.2@127.0.0.1:2809/NameService");
       naming_context =
          CosNaming::NamingContext::_narrow (naming_context_object.in ());
    } catch (...) {
       cerr << "Error: cannot obtain naming service initial reference" << endl;
       throw; 
    }



    //
    // Recoge la referencia a una factoria del servicio de  notificaciones
    //
    readNotifyFactoryIOR();
    obj = orb->string_to_object(NotifyFactoryIOR);

    CosNotifyChannelAdmin::EventChannelFactory_var factory = NULL;
    factory = CosNotifyChannelAdmin::EventChannelFactory::_narrow(obj);
    if (CORBA::is_nil(factory)) { 
      cerr << "[server] ERROR: factoria nula " << endl;
      return -1; 
    } 

    CosNotification::QoSProperties initial_qos;
    CosNotification::AdminProperties initial_admin;
    CosNotifyChannelAdmin::ChannelID id;
    CosNotifyChannelAdmin::EventChannel_var channel = NULL;

    try { 
      // Crear el canal
      channel = factory->create_channel(initial_qos, initial_admin, id);
      cerr << "[server] Preparado en el canal " << id  << endl;
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


//     // Vuelca en salida estandar la referencia como cadena de caracteres
//     sprintf(ChannelIOR,"%s",orb->object_to_string(channel));
//     writeChannelIOR();

    // 
    // Guarda la referencia al canal en el Servicio de Nombres
    // 

    CosNaming::NamingContext_var naming_context_notif = NULL;
    CosNaming::Name name_notif(1);
    name_notif.length (1);
    name_notif[0].id = CORBA::string_dup ("MyNotif");
    name_notif[0].kind = CORBA::string_dup ("");

    naming_context_notif = naming_context->bind_new_context(name_notif);

    CosNaming::Name name_channel(1);
    name_channel.length (1);
    name_channel[0].id = CORBA::string_dup ("channel");
    name_channel[0].kind = CORBA::string_dup ("");
    naming_context_notif->bind(name_channel, channel);


    orb->run();
    orb->destroy();
    
  } catch(CORBA::Exception& exc) {
    cerr << "[server] Excepcion: " << exc << endl;
    return 1;
  }

  return 0;
}
