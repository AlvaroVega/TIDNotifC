// -*- c++ -*-
#ifdef _TAO
#include "orbsvcs/orbsvcs/CosEventChannelAdminS.h"
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#include "orbsvcs/Naming/Naming_Server.h"
#elif defined _TIDORB
#include "CosEventChannelAdmin.h"
#include "CosNotifyChannelAdmin.h"
#include "CosNaming.h"
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

char ChannelIOR[2048];

void readChannelIOR(){
  
  FILE *f=fopen("channel.ior","r");
  
  if(f==0){
     fprintf(stderr,"Unable to open channel.ior\n");
     exit(0);
  }
  fscanf (f, "%s\n", ChannelIOR);
  fclose(f);
}



int main(int argc, char* argv[]) {

  char aux1[1000];
  
  try {
    
    //
    // Inicializacion del ORB 
    //

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
    // Crea un POA para el supplier: PERSISTENT LifespanPolicy, USER_ID policy
    // 

    PortableServer::LifespanPolicy_var lifespan =
      root_poa->create_lifespan_policy(PortableServer::PERSISTENT);
    
    PortableServer::IdAssignmentPolicy_var idAssignment =
      root_poa->create_id_assignment_policy(PortableServer::USER_ID);
    
    CORBA::PolicyList policies(2);  
    policies.length(2);
    policies[0] = PortableServer::IdAssignmentPolicy::_duplicate(idAssignment);
    policies[1] = PortableServer::LifespanPolicy::_duplicate(lifespan);
    
    PortableServer::POA_var supplier_poa =
      root_poa->create_POA("supplierPOA", manager.in(), policies);

    PortableServer::POAManager_var supplier_poa_manager = 
      supplier_poa->the_POAManager();

    idAssignment->destroy();
    lifespan->destroy();

    // Activa el POAManager
    manager->activate();


    //
    // Crea y activa el servant del supplier
    // 

    PortableServer::ObjectId_var oid = 
      PortableServer::string_to_ObjectId("MySupplier");

    MySupplierImpl servant_supplier;

    try{
      supplier_poa->activate_object_with_id(oid.in(), &servant_supplier);
    }
    catch(...){
      cerr << "[supplier] ERROR: activating servant_supplier " << endl;
    }
    CORBA::Object_var supplier_obj = supplier_poa->id_to_reference(oid.in());


    CosEventComm::PushSupplier_var supplier =
      CosEventComm::PushSupplier::_narrow(supplier_obj);

    //
    // Obtiene la referencia al canal
    // 
    // readChannelIOR();
    // obj = orb->string_to_object(ChannelIOR);
    CosNaming::NamingContext_var naming_context_notif = NULL;
    CosNaming::Name name_notif(2);
    name_notif.length (2);
    name_notif[0].id = CORBA::string_dup ("MyNotif");
    name_notif[0].kind = CORBA::string_dup ("");
    name_notif[1].id = CORBA::string_dup ("channel");
    name_notif[1].kind = CORBA::string_dup ("");
    obj = naming_context->resolve(name_notif);


    CosNotifyChannelAdmin::EventChannel_var channel;
    channel = CosNotifyChannelAdmin::EventChannel::_narrow(obj);
    if (CORBA::is_nil(channel)) { 
      cerr << "[supplier] ERROR: canal nulo " << endl;
      return -1; 
    }

    // 
    // Obtenemos el manager de emisores por defecto
    // 
    CosNotifyChannelAdmin::SupplierAdmin_var supplierAdmin;
    CosNotifyChannelAdmin::AdminID adminid;
    
    try{
      supplierAdmin = channel->default_supplier_admin();   
    }
    catch(CORBA::Exception &ce){
      fprintf(stderr,"(%s)%i CORBA::Exception - %s\n",
              __FILE__,__LINE__,ce._name());
    }
    catch(...){
      fprintf(stderr,"(%s)%i - Unexpected exception!",
              __FILE__,__LINE__);
    }
    
    // 
    // Obtenemos el proxy para publicar
    // 
    CosNotifyChannelAdmin::ProxyPushConsumer_var pushConsumer;
    CosNotifyChannelAdmin::ProxyID proxy_id;
    CosNotifyChannelAdmin::ClientType ctype = CosNotifyChannelAdmin::ANY_EVENT;
    
    try{
      CosNotifyChannelAdmin::ProxyConsumer_var obj =
        supplierAdmin->obtain_notification_push_consumer(ctype, proxy_id);
      
      pushConsumer = CosNotifyChannelAdmin::ProxyPushConsumer::_narrow(obj);
      
      // Conecta proxy
      pushConsumer->connect_any_push_supplier(supplier);
    }
    catch(CosEventChannelAdmin::AlreadyConnected &ac){
      fprintf(stderr,"(%s)%i CosEventChannelAdmin::AlreadyConnected\n",
              __FILE__,__LINE__);
    }
    catch(CORBA::SystemException& se){
      fprintf(stderr,"(%s)%i CORBA::SystemException\n",
              __FILE__,__LINE__);
    }
    catch(CosNotifyChannelAdmin::AdminLimitExceeded err){
      fprintf(stderr,"(%s)%i CosNotifyChannelAdmin::AdminLimitExceeded\n",
              __FILE__,__LINE__);
    }
    catch(CORBA::Exception &ce){
      fprintf(stderr,"(%s)%i CORBA::Exception - %s\n",
              __FILE__,__LINE__,ce._name());
    }
    catch(...){
      fprintf(stderr,"Unexpected exception!\n");
    }


//     // 
//     // Guarda la referencia en el Servicio de Nombres
//     // 

//     CosNaming::NamingContext_var naming_context_notif = NULL;
//     CosNaming::Name name_notif(1);
//     name_notif.length (1);
//     name_notif[0].id = CORBA::string_dup ("MyNotif");
//     name_notif[0].kind = CORBA::string_dup ("");

//     obj = naming_context->resolve(name_notif);
//     naming_context_notif = CosNaming::NamingContext::_narrow(obj);


//     CosNaming::Name name_supplier(1);
//     name_supplier.length (1);
//     name_supplier[0].id = CORBA::string_dup ("supplier");
//     name_supplier[0].kind = CORBA::string_dup ("");
//     naming_context_notif->bind(name_supplier, supplier_obj);

    
    
    // 
    // Crea y envia los eventos
    // 

    cerr << "[supplier] Crea el evento" << flush << endl;
    CORBA::Any event;
    event <<= "Event hello"; 

    while (1){
       
      char c = getchar();
      
      try{
        // Invocamos al metodo que envia el evento
        pushConsumer->push(event); 
      }
      catch(...){
        cerr << "[supplier] ERROR: push event " << endl;
      }
      
    }
    
    orb->run();

    cerr << "[supplier] Desconectando... " << flush << endl;
//     pushConsumer->disconnect_push_supplier();
//     pushConsumer->destroy();    

    cerr << "[supplier] Terminando" << flush << endl;
    orb->shutdown(true);
    orb->destroy();

  } catch(CORBA::Exception& exc) {
    cerr << "[server] Excepcion: " << exc << endl;
    return 1;
  }

}
