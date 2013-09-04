#ifdef _TAO
#include "tao/corba.h"
#include "orbsvcs/orbsvcs/CosEventChannelAdminS.h"
#include "orbsvcs/orbsvcs/CosNotifyChannelAdminS.h"
#include "TimeBaseS.h"
#elif defined _TIDORB
#include "POA_CosEventChannelAdmin.h"
#include "POA_CosNotifyChannelAdmin.h"
// #include <CosNotifyChannelAdmin.h> 
// #include <POA_CosNotifyComm.h>
#include "TimeBase.h"
#include "TIDorb/core.h"
#endif



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

void writeChannelIOR(){
  
  FILE *f=fopen("channel.ior","w");
  
  if(f==0){
     fprintf(stderr,"Unable to open channel.ior\n");
     exit(0);
  }
  fprintf (f, "%s\n", ChannelIOR);
  fclose(f);
}

// -----------------------------------------

int main(int argc, char *argv[]){
 
  memset(NotifyFactoryIOR,'\0',2048);
  memset(ChannelIOR,'\0',2048);

  int argc_orb=9;
  char **argv_orb;
  
  argv_orb=(char**)malloc(sizeof(char*)*argc_orb);
  argv_orb[0]=strdup("Publisher");
  argv_orb[1]=strdup("-ORB_trace_level");
  argv_orb[2]=strdup("5");    
  argv_orb[3]=strdup("-ORB_trace_file");
  argv_orb[4]=strdup("supplier.log");
  argv_orb[5]=strdup("-ORB_ssl_private_key");
  argv_orb[6]=strdup("publisher_key.pem");    
  argv_orb[7]=strdup("-ORB_ssl_certificate");
  argv_orb[8]=strdup("publisher_cert.pem");    

//   argv_orb[1]=strdup("-ORB_iiop_orb_port");
//   argv_orb[2]=strdup("3133");


  CORBA::ORB_var orb = CORBA::ORB_init (argc_orb, argv_orb, "ORB1");
  
  CosNotifyChannelAdmin::EventChannel_var channel;
  CosNotifyChannelAdmin::ProxyPushConsumer_ptr pushConsumer;

  readNotifyFactoryIOR(); 

  try{
      CORBA::Object_var objFact = orb->string_to_object(NotifyFactoryIOR);
  
      if (CORBA::is_nil(objFact)){
          fprintf(stderr,"Factory object is NIL!\n");
          exit(0);
      }
      CosNotifyChannelAdmin::EventChannelFactory_var factory=
                           CosNotifyChannelAdmin::EventChannelFactory::_narrow(objFact);

      if (CORBA::is_nil(factory)){
          fprintf(stderr,"NotificationFactory is NIL!\n");
          exit(0);
      }
      CosNotifyChannelAdmin::ChannelID id;
      CosNotification::AdminProperties initAdmin;
      CosNotification::QoSProperties initQoS;

      // ---------------------------------------------------------------
      // EventReliability=BestEffort / ConnectionReliability=Persistent
      // ---------------------------------------------------------------
      initQoS.length(2);
               
      initQoS[0].name=CORBA::string_dup(CosNotification::EventReliability);
      initQoS[0].value<<= static_cast<CORBA::Short>(CosNotification::BestEffort);
      initQoS[1].name=CORBA::string_dup(CosNotification::ConnectionReliability);
      initQoS[1].value<<= static_cast<CORBA::Short>(CosNotification::Persistent);                    
      // ------------------
      // Creamos canal
      // ------------------
      try{
          id=0;
          // OJO, la primera vez, descomenta el create_channel, para
          // que cree el canal 0
          //channel=factory->create_channel(initQoS,initAdmin,id);
          channel=factory->get_event_channel(id);
          fprintf(stderr,"ID channel: %lu\n",id);
          sprintf(ChannelIOR,"%s",orb->object_to_string(channel));
          fprintf(stderr,"%s\n",ChannelIOR);
          writeChannelIOR();
          
          if (CORBA::is_nil(channel)){
              fprintf(stderr,"Channel object is NIL!\n");
              exit(0);
          }
      } 
      catch(CORBA::Exception &ce){
            fprintf(stderr,"(%s)%i CORBA::Exception - %s\n",
                    __FILE__,__LINE__,ce._name());
      }
      catch(...){
            fprintf(stderr,"(%s)%i - Unexpected exception!",
                    __FILE__,__LINE__);
      }
      // ---------------------------------------------              
      // Obtenemos el manager de emisores por defecto
      // ----------------------------------------------
      CosNotifyChannelAdmin::SupplierAdmin_var supMgr;
      CosNotifyChannelAdmin::AdminID adminid;

      try{
          supMgr=channel->default_supplier_admin();   
      }
      catch(CORBA::Exception &ce){
            fprintf(stderr,"(%s)%i CORBA::Exception - %s\n",
                    __FILE__,__LINE__,ce._name());
      }
      catch(...){
            fprintf(stderr,"(%s)%i - Unexpected exception!",
                    __FILE__,__LINE__);
      }
      // ---------------------------------
      // Obtenemos el proxy para publicar
      // ---------------------------------
      CosNotifyChannelAdmin::ProxyID proxy_id;
      CosNotifyChannelAdmin::ClientType ctype=CosNotifyChannelAdmin::ANY_EVENT;                           
      
      try{
          CosNotifyChannelAdmin::ProxyConsumer_var obj=
                           supMgr->obtain_notification_push_consumer(ctype,proxy_id);

          pushConsumer=CosNotifyChannelAdmin::ProxyPushConsumer::_narrow(obj);
                           
          // ---------------
          // Conecta proxy
          // ---------------                   
          pushConsumer->connect_any_push_supplier(CosEventComm::PushSupplier::_nil());                     }
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
       CORBA::Any event;

       event<<="Event hello"; 
                    
       while (1){
       
         char c=getchar();
         fprintf(stderr,"Sending event...\n");
         try{
             pushConsumer->push(event);
         }
         catch(CORBA::Exception &ce){
            fprintf(stderr,"CORBA::Exception - %s\n",ce._name());
         }
         catch(...){
          fprintf(stderr,"Unexpected exception!\n");
         }
         // pc->disconnect_push_consumer(); // Libera recursos del publicador
       }
  }
  catch(CORBA::Exception &ce){
        fprintf(stderr,"%s\n",ce._name());
  }
  catch(...){
        fprintf(stderr,"Unexpected exception!\n");
  }  
  fprintf(stderr,"....Finished!\n");
  exit(0);
}


      



