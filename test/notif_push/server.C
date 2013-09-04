#ifdef _TAO
#include "tao/corba.h"
#include "orbsvcs/orbsvcs/CosEventChannelAdminS.h"
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
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


    // Recoge la referencia a una factoria del servicio de  notificaciones
    cin >> aux1;   
    obj = orb->string_to_object(aux1);

    // CosNotifyChannelAdmin::EventChannelFactory_var factory;
    factory = CosNotifyChannelAdmin::EventChannelFactory::_narrow(obj);
    if (CORBA::is_nil(factory)) { 
      cerr << "[server] ERROR: factoria nula " << endl;
      return -1; 
    } 

    //CosNotifyChannelAdmin::EventChannel_var channelv[10];


    CosNotification::QoSProperties initial_qos;
    CosNotification::AdminProperties initial_admin;
    CosNotifyChannelAdmin::ChannelID id;
    // CosNotifyChannelAdmin::ChannelID idv[10];

    TimeBase::UtcT current_utc = TIDorb::core::util::Time::currentUtcT();
    TimeBase::UtcT future_utc  = TIDorb::core::util::Time::currentUtcT();
    TimeBase::UtcT pass_utc    = TIDorb::core::util::Time::currentUtcT();
    future_utc.time += (5 * 10000000); // now + 5 ''
    pass_utc.time   -= (5 * 10000000); // now - 5 ''


//     cerr << "Tiempo actual " << current_utc.time << endl;
//     cerr << "Tiempo futuro " << future_utc.time << endl;

//     cerr << "Empezando espera 5'' " << endl;
//     sleep( (future_utc.time - current_utc.time)/10000000);
//     cerr << "Terminando espera" << endl;


    

    // Politicas QoS Soportadas:

    initial_qos.length(9);
    initial_qos[0].name = CORBA::string_dup("OrderPolicy");
    initial_qos[0].value <<= CosNotification::FifoOrder; // Any Fifo Priority Deadline

    initial_qos[1].name = CORBA::string_dup("EventReliability");
    initial_qos[1].value <<= CosNotification::Persistent; // BestEffort, Persistent

    initial_qos[2].name = CORBA::string_dup("ConnectionReliability");
    initial_qos[2].value <<= CosNotification::Persistent; // BestEffort, Persistent
    
    initial_qos[3].name = CORBA::string_dup("Priority");
    initial_qos[3].value <<= CosNotification::HighestPriority; // Highest, Default

    initial_qos[4].name = CORBA::string_dup("StartTime");
    initial_qos[4].value <<= current_utc;

    initial_qos[5].name = CORBA::string_dup("StopTime");
    initial_qos[5].value <<= future_utc;

    initial_qos[6].name = CORBA::string_dup("Timeout");
    initial_qos[6].value <<= pass_utc.time;

    initial_qos[7].name = CORBA::string_dup("StartTimeSupported");
    initial_qos[7].value <<= CORBA::Any::from_boolean(0);

    initial_qos[8].name = CORBA::string_dup("StopTimeSupported");
    initial_qos[8].value <<= CORBA::Any::from_boolean(1);




    //
    // Politicas de QoS no soportadas
    //

    // initial_qos[0].name = CORBA::string_dup("DiscardPolicy");
    // initial_qos[0].value <<= CosNotification::AnyOrder; // Any Fifo Priority Deadline

    // initial_qos[7].name = CORBA::string_dup("MaximumBatchSize");
    // initial_qos[7].value <<= (CORBA::Long) 20;

    // initial_qos[0].name = CORBA::string_dup("PacingInterval");
    // initial_qos[0].value <<= (TimeBase::TimeT)TIDorb::core::util::Time::currentTimeMillis();

    // initial_qos[9].name = CORBA::string_dup("MaxEventsPerConsumer");
    // initial_qos[9].value <<= (CORBA::Long) 20;

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
      
//       // Crea otros 10 canales
//       for(int i=0; i < 10; i++){
//         channelv[i] = factory->create_channel(initial_qos, initial_admin, idv[i]);
//       }

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
