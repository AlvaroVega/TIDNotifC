#ifdef _TAO
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#include "orbsvcs/orbsvcs/CosNotifyCommS.h"
#elif defined _TIDORB
// #include "CosEventChannelAdmin.h"
// #include "CosNotifyChannelAdmin.h"
#include <CosNotifyChannelAdmin.h>
#include <POA_CosNotifyComm.h>
#endif

#include <errno.h>
#include "ConsumerEvtImpl.h"



// ----------------------------------------

char NotifyFactoryIOR[2048];
char ChannelIOR[2048];

// ----------------------------------------

void readNotifyFactoryIOR(){
  
  FILE *f=fopen("notify_factory.ior","r"); 
  if(f==0){
     fprintf(stderr,"Unable to open notify_factory.ior\n");
     exit(0);
  }
  fscanf (f, "%s\n", NotifyFactoryIOR);
  fclose(f);
}
// ----------------------------------------

void readChannelIOR(){
  
  FILE *f=fopen("channel.ior","r");
  
  if(f==0){
     fprintf(stderr,"Unable to open channel.ior\n");
     exit(0);
  }
  fscanf (f, "%s\n", ChannelIOR);
  fclose(f);
}

// -----------------------------------------

int main(int argc, char *argv[]){
  
   memset(NotifyFactoryIOR,'\0',2048);
   memset(ChannelIOR,'\0',2048);

   int argc_orb=9;

   char **argv_orb;
   argv_orb=(char**)malloc(sizeof(char*)* argc_orb);
   argv_orb[0]=strdup("Consumer");
   argv_orb[1]=strdup("-ORB_trace_level");
   argv_orb[2]=strdup("5");
   argv_orb[3]=strdup("-ORB_trace_file");
   argv_orb[4]=strdup("consumer.log");
   argv_orb[5]=strdup("-ORB_ssl_private_key");
   argv_orb[6]=strdup("publisher_key.pem");    
   argv_orb[7]=strdup("-ORB_ssl_certificate");
   argv_orb[8]=strdup("publisher_cert.pem");    
//    argv_orb[5]=strdup("-ORB_ssl_port");
//    argv_orb[6]=strdup("7777");
//    argv_orb[5]=strdup("-ORB_iiop_orb_port");
//    argv_orb[6]=strdup("15001");
      
   CORBA::ORB_var orb;
   ConsumerEvtImpl consumerEvtImpl;

   try{
       orb = CORBA::ORB_init (argc_orb,argv_orb, "ORB1");
       
      // Root POA ORB1
      CORBA::Object_var poa_object = orb->resolve_initial_references("RootPOA");
      PortableServer::POA_var root_poa=PortableServer::POA::_narrow (poa_object.in());

      PortableServer::POAManager_var poa_manager =root_poa->the_POAManager();

      // PERSISTENT LifespanPolicy
      PortableServer::LifespanPolicy_var lifespan=
           root_poa->create_lifespan_policy(PortableServer::PERSISTENT);
      
      // USER_ID policy
      PortableServer::IdAssignmentPolicy_var idAssignment=
           root_poa->create_id_assignment_policy(PortableServer::USER_ID);

      CORBA::PolicyList policies(2);
      
      policies.length(2);
      policies[0]=PortableServer::IdAssignmentPolicy::_duplicate(idAssignment);
      policies[1]=PortableServer::LifespanPolicy::_duplicate(lifespan);
      
      PortableServer::POA_var child_poa=root_poa->create_POA("childPOA",
                                                              poa_manager.in(),
                                                              policies);
 
      PortableServer::POAManager_var child_poa_manager =child_poa->the_POAManager();

      idAssignment->destroy();
      lifespan->destroy();

      PortableServer::ObjectId_var oid=PortableServer::string_to_ObjectId("calculadoraEvt");

      try{
          child_poa->activate_object_with_id(oid.in(),&consumerEvtImpl);
      }
      catch(...){
        fprintf(stderr,"Rita");
      }
      CORBA::Object_var evtMgrObj=child_poa->id_to_reference(oid.in());
 
      poa_manager->activate();
      child_poa_manager->activate();

      readNotifyFactoryIOR(); //TIDOrb
          
      CosNotifyChannelAdmin::ProxyPushSupplier_var proxySupplier;
       
      CORBA::Object_var objFact = orb->string_to_object(NotifyFactoryIOR); //TIdOrb
      if (CORBA::is_nil(objFact)){
          fprintf(stderr,"Factory object is NIL!\n");
          exit(0);
      }
      fprintf(stderr,"%s\n",orb->object_to_string(objFact));
      CosNotifyChannelAdmin::EventChannelFactory_var factory=
                               CosNotifyChannelAdmin::EventChannelFactory::_narrow(objFact.in());

      if (CORBA::is_nil(factory)){
          fprintf(stderr,"NotificationFactory is NIL!\n");
          exit(0);
      }                
      // ---------------
      // Canal eventos
      // ---------------
      readChannelIOR();
          
      CosNotifyChannelAdmin::EventChannel_var channel=
                 CosNotifyChannelAdmin::EventChannel::_narrow(orb->string_to_object(ChannelIOR));
           
      // ------------------------------------------------
      // Obtenemos el manager de consumidores por defecto
      // ------------------------------------------------
      CosNotifyChannelAdmin::ConsumerAdmin_var ca=channel->default_consumer_admin();
          
      CosNotifyChannelAdmin::ProxyID proxy_id;
      CosNotifyChannelAdmin::ClientType ctype=CosNotifyChannelAdmin::ANY_EVENT;
                 
          try{
              // Obtenemos el proxy para recibir
              CosNotifyChannelAdmin::ProxySupplier_var obj=
                    ca->obtain_notification_push_supplier(ctype,proxy_id);
                   
              fprintf(stderr,"Proxy ID:%lu\n",proxy_id);
                   
              // Narrow a any push supplier
              proxySupplier=CosNotifyChannelAdmin::ProxyPushSupplier::_narrow(obj);
              // Conecta
              try{
                   CosEventComm::PushConsumer_var evtMgr=
                     CosEventComm::PushConsumer::_narrow(evtMgrObj);
                  
                  if (CORBA::is_nil(evtMgr)){
                      fprintf(stderr,"evtMgr is NILL\n");
                  }
                  else{
                       fprintf(stderr,"connect consumer...\n");
                       proxySupplier->connect_any_push_consumer(evtMgr); //untyped
                  }             
              }
              catch(CosEventChannelAdmin::AlreadyConnected &ac){
                     fprintf(stderr,"CosEventChannelAdmin::AlreadyConnected\n");
              }
              catch(CORBA::SystemException& se){
                     fprintf(stderr,"CORBA::SystemException\n");
              }
          }
          catch(CosNotifyChannelAdmin::AdminLimitExceeded err){
               fprintf(stderr,"CosNotifyChannelAdmin::AdminLimitExceeded\n");
          }    
      }
  catch(CORBA::Exception &ce){
        fprintf(stderr,"%s(%i) - %s\n",__FILE__,__LINE__,ce._name());
  }
  catch(...){
        fprintf(stderr,"Unexpected exception!\n");
  }
  // Main loop
  orb->run();
 
  fprintf(stderr,"....Finished!\n");
  exit(0);
}
