#include <CORBA.h>
#include <PortableServer/POA.h>
#include "CosEventChannelAdmin.h"
#include "CosNotifyChannelAdmin.h"
#include "CosNotifyFilter.h"
#include "CosNotification.h"
#include "FilterAdminImpl.h"
#include "FilterFactoryImpl.h"
#include "MappingFilterImpl.h"
#include "FilterImpl.h"
#include "TIDParser.h"
#include "TIDNotifConfig.h"
#include "TIDConfig.h"
#include "ThePOAFactory.h"
#include "PersistenceManager.h"
#include "my_push_supplier.h"
#include "my_push_consumer.h"
#include "Event.h"

int main(int argc,char *argv [])
{
  CORBA::ORB_ptr orb_ptr;
  try
  {
    /************************************************************************/
    /*            INICIALIZAMOS LA PARTE DEL ORB                            */
    /************************************************************************/
    int alt_argc = 0;
    char ** alt_argv;
    const char * orb_id="Test_TIDNotification";
    orb_ptr=CORBA::ORB_init(argc, argv, orb_id);
    if (!orb_ptr)
    {
      cerr<<"El ORB es null"<<endl;
      return -1;
    }

    CORBA::Object_ptr delegado_POA;
    PortableServer::POA_ptr rootPOA;
    try
    {
      delegado_POA = orb_ptr->resolve_initial_references("RootPOA");
    }
    catch ( CORBA::ORB::InvalidName ex )
    {
      ex._name();
      return -1;

    }
    rootPOA = PortableServer::_POAHelper::narrow( delegado_POA,true );
    PortableServer::POAManager_var poa_manager = rootPOA->the_POAManager();
    CORBA::PolicyList_var policies = NULL;
    policies = new CORBA::PolicyList(2);
    policies->length(2);
      // Valores cambiados
    (*policies)[0] = rootPOA->create_lifespan_policy
      ( PortableServer::PERSISTENT );
    (*policies)[1] = rootPOA->create_id_assignment_policy
      ( PortableServer::USER_ID );

    PortableServer::POA_var supplierPOA = rootPOA->create_POA("supplierPOA", poa_manager, *policies );
    printf("Creado el supplierPOA\n");
    /***********************************************************************/
    /*   OBTENEMOS LA FACTORIA DEL CANAL DE EVENTOS Y CREAMOS EL CANAL     */
    /**********************************************************************/

    CORBA::Object_ptr delegado_event_channel_factory;
    delegado_event_channel_factory=orb_ptr->string_to_object(argv[1]);
    CosNotifyChannelAdmin::EventChannelFactory_var factory;
    factory = CosNotifyChannelAdmin::EventChannelFactory::_narrow(delegado_event_channel_factory);
    if (CORBA::is_nil(factory)) { 
      cerr << "[server] ERROR: factoria nula " << endl;
      return -1; 
    } 
  
     CosNotifyChannelAdmin::EventChannel_var channel;
    //CosNotifyChannelAdmin::EventChannel_var channelv[10];


    


    try { 
      channel = factory->get_event_channel(0);
      printf("Obtengo el canal\n");
    } catch (CosNotifyChannelAdmin::ChannelNotFound &ex) { 
      cerr << "[recover_server_supplier] CosNotifyChannelAdmin::ChannelNotFound " << ex._name(); 
      return -1; 
    }
  
   /**************************************************************************/
   /*              OBTENEMOS EL SUPPLIERADMIN POR DEFECTO                    */
   /**************************************************************************/
    //TODO_MORFEO: add new filters
    CosNotifyChannelAdmin::SupplierAdmin_var supplierAdmin = NULL;
    printf("Intento obtener el supplieradmin\n");
    supplierAdmin = channel->get_supplieradmin(0);
    printf("Obtengo el supplierAdmin\n");
    
   /**************************************************************************/
   /*         OBTENEMOS EL PROXYCONSUMER APARTIR DEL SUPPLIERADMIN           */
   /**************************************************************************/
    //TODO_MORFEO: add new filters
    CosNotifyChannelAdmin::ProxyConsumer_ptr proxyConsumer;
    CosNotifyChannelAdmin::ProxyID proxyConsumerID ;
    proxyConsumer = 
      supplierAdmin->get_proxy_consumer(1);
                                                      

      printf("obtengo el ProxyConsumer\n");

  // proxyConsumer->add_filter(filter_II);


   /**************************************************************************/
   /*         OBTENEMOS EL PROXYCONSUMER APARTIR DEL proxyConsumer           */
   /**************************************************************************/
    CosNotifyChannelAdmin::ProxyPushConsumer_ptr proxyPushConsumer;
    
    proxyPushConsumer = CosNotifyChannelAdmin::ProxyPushConsumer::_narrow(proxyConsumer);


    /**************************************************************************/
    /*            INSTANCIAMOS LOS PROXYS Y LOS ACTIVAMOS EN EL POA           */
    /**************************************************************************/
   
    my_push_supplier * my_supplier = new my_push_supplier(proxyPushConsumer);
    char string_id[100];
    sprintf(string_id, "My_Supplier_%lu", TIDThr::Thread::getCurrentThreadId());
    PortableServer::ObjectId_var supplier_objectID = PortableServer::string_to_ObjectId(string_id);
    supplierPOA->activate_object_with_id(supplier_objectID,my_supplier);
    poa_manager->activate();

    Events::Test_Event_ptr event_I = new Events::Test_Event(5,1,2);
    Events::Test_Event_ptr event_II = new Events::Test_Event(5,8,2);

    
    CORBA::Any any_I;
    Events::_Test_EventHelper::insert(any_I,event_I);
    CORBA::Any any_II;
    Events::_Test_EventHelper::insert(any_II,event_II);

    while (true)
    {
      try
      {
        my_supplier->new_event(any_I);
        my_supplier->new_event(any_II);
      }
      catch (CORBA::TRANSIENT & e)
      {
        cerr<< "[server supplier] Channel fail "<< e._name() << endl;
      }
      
      catch (CORBA::COMM_FAILURE & e)
      {
        cerr<< "[server supplier] Channel fail "<< e._name() << endl;
      }
      TIDThr::Thread::sleep(1000);
    }


    
  }
  catch (CORBA::Exception & e)
  {
    cerr<<"[Test_Filter] unknown error"<< typeid(e).name() << e._name();
   return -1;
   
  }

}

