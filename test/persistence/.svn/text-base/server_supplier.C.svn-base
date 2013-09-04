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


    CosNotification::QoSProperties initial_qos;
    CosNotification::AdminProperties initial_admin;
    CosNotifyChannelAdmin::ChannelID id;
    //CosNotifyChannelAdmin::ChannelID idv[10];



//     // Politicas Soportadas:

//     initial_qos.length(9);
//     initial_qos[0].name = CORBA::string_dup("OrderPolicy");
//     initial_qos[0].value <<= CosNotification::FifoOrder; // Any Fifo Priority Deadline

//     initial_qos[1].name = CORBA::string_dup("EventReliability");
//     initial_qos[1].value <<= CosNotification::BestEffort; // Persistent

//     initial_qos[2].name = CORBA::string_dup("ConnectionReliability");
//     initial_qos[2].value <<= CosNotification::Persistent; // Persistent
    
//     initial_qos[3].name = CORBA::string_dup("Priority");
//     initial_qos[3].value <<= CosNotification::HighestPriority; // Highest, Default

//     initial_qos[4].name = CORBA::string_dup("StartTime");
//     initial_qos[4].value <<= *(new TimeBase::UtcT(
//                                   TIDorb::core::util::Time::currentTimeMillis(),
//                                   0,0,0));

//     initial_qos[5].name = CORBA::string_dup("StopTime");
//     initial_qos[5].value <<= *(new TimeBase::UtcT(
//                                   TIDorb::core::util::Time::currentTimeMillis(),
//                                   0,0,0));

//     initial_qos[6].name = CORBA::string_dup("Timeout");
//     initial_qos[6].value <<= (TimeBase::TimeT)TIDorb::core::util::Time::currentTimeMillis();

//     initial_qos[7].name = CORBA::string_dup("StartTimeSupported");
//     initial_qos[7].value <<= (CORBA::Boolean) 0;

//     initial_qos[8].name = CORBA::string_dup("StopTimeSupported");
//     initial_qos[8].value <<= (CORBA::Boolean) 1;

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


    try { 
      // Crear el canal
      channel = factory->create_channel(initial_qos, initial_admin, id);

//       for(int i=0; i < 10; i++){
//         channelv[i] = factory->create_channel(initial_qos, initial_admin, idv[i]);
//       }
    } catch (CosNotification::UnsupportedQoS &ex) { 
      cerr << "[server_supplier] CosNotification::UnsupportedQoS: " << ex._name(); 
      return -1; 
    } catch (CosNotification::UnsupportedAdmin &ex) { 
      cerr << "[server_supplier] CosNotification::UnsupportedAdmin: " << ex._name(); 
      return -1; 
    } catch (CORBA::SystemException &ex) { 
      cerr << "[server_supplier] SystemExcepcion: " << ex._name(); 
      return -1; 
    } 
  
   /**************************************************************************/
   /*              OBTENEMOS EL SUPPLIERADMIN POR DEFECTO                    */
   /**************************************************************************/
    //TODO_MORFEO: add new filters
    CosNotifyChannelAdmin::SupplierAdmin_ptr supplierAdmin;
    supplierAdmin = channel->default_supplier_admin();
    printf("Obtengo el default supplier admin\n");
     /**********************************************************************/
    /*          CREAMOS UNA FACTORIA DE FILTROS                           */
    /**********************************************************************/
    CosNotifyFilter::FilterFactory_ptr filterFactory = channel->default_filter_factory();
    CosNotifyFilter::Filter* filter_II = filterFactory->create_filter("EXTENDED_TCL");
    /****************************************************************/
    /*                  CREAMOS MAS RESTRICCIONES                   */
    /****************************************************************/
    CosNotification::_EventType eventType_III[1];

    eventType_III[0].domain_name = "GSyC";
    eventType_III[0].type_name = "Test";
    

    char * constraint_III = "$.campo_tres == 2";

    CosNotification::EventTypeSeq eventTypeSeq_III(1,1,eventType_III,false);
    

    CosNotifyFilter::ConstraintExp constraintExp_III(eventTypeSeq_III,
                                                     constraint_III);

    CosNotifyFilter::ConstraintExpSeq constraintExpSeq_II(1);
    constraintExpSeq_II.length(1);
    
    constraintExpSeq_II[0]=constraintExp_III;
    CosNotifyFilter::ConstraintInfoSeq* constraintInfoSeq_II;
    constraintInfoSeq_II = filter_II->add_constraints(constraintExpSeq_II);

   /**************************************************************************/
   /*         OBTENEMOS EL PROXYCONSUMER APARTIR DEL SUPPLIERADMIN           */
   /**************************************************************************/
    //TODO_MORFEO: add new filters
    CosNotifyChannelAdmin::ProxyConsumer_ptr proxyConsumer;
    CosNotifyChannelAdmin::ProxyID proxyConsumerID ;
    proxyConsumer = 
      supplierAdmin->obtain_notification_push_consumer(CosNotifyChannelAdmin::ANY_EVENT,
                                                      proxyConsumerID);
                                                      

      printf("obtengo el ProxyConsumer\n");

      proxyConsumer->add_filter(filter_II);


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


    CORBA::Object_ptr obj_supplier = supplierPOA->id_to_reference(supplier_objectID);

    CosNotifyComm::PushSupplier_ptr my_pushSupplier = CosNotifyComm::PushSupplier::_narrow(obj_supplier);

    
    /***********************************************************************/
    /*                CONECTAMOS EL PUSHSUPPLIER Y EL PUSHCONSUMER         */
    /***********************************************************************/
   
    proxyPushConsumer->connect_any_push_supplier(my_pushSupplier);
    
    Events::Test_Event_ptr event_I = new Events::Test_Event(5,1,2);
    Events::Test_Event_ptr event_II = new Events::Test_Event(5,8,0);

    
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
      catch (CORBA::OBJECT_NOT_EXIST & e)
      {
        cerr<< "[server supplier] Channel fail "<< e._name() << endl;
      }		
      catch (CosEventComm::Disconnected & e)
      {
        cerr<< "[server supplier] Channel fail "<< e._name() << endl;
      }
      TIDThr::Thread::sleep(1000);
    }

    orb_ptr->run();

    
  }
  catch (CORBA::Exception & e)
  {
    cerr<<"[server supplier] unknown error"<< typeid(e).name() << e._name();
   return -1;
   
  }

}

