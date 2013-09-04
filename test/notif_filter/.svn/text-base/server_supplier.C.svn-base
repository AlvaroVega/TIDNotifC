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
#include "test_utils.h"
#include "util/parser/Debugger.h"


  CosNotifyFilter::Filter* create_filter(const CosNotifyChannelAdmin::EventChannel_var channel,
                                        const char* domain_name,const char* type_name,
                                        const char* constraint)
  {
    
    CosNotifyFilter::FilterFactory_ptr filterFactory = channel->default_filter_factory();
    //Le pasamos al create el tipo de gramática que soportamos
    CosNotifyFilter::Filter* filter_II = filterFactory->create_filter("EXTENDED_TCL");

    CosNotification::_EventType eventType_III[1];

    eventType_III[0].domain_name = domain_name;
    eventType_III[0].type_name = type_name;
    


    CosNotification::EventTypeSeq eventTypeSeq_III(1,1,eventType_III,false);
    

    CosNotifyFilter::ConstraintExp constraintExp_III(eventTypeSeq_III,
                                                     constraint);

    CosNotifyFilter::ConstraintExpSeq constraintExpSeq_II(1);
    constraintExpSeq_II.length(1);
    
    constraintExpSeq_II[0]=constraintExp_III;
    CosNotifyFilter::ConstraintInfoSeq* constraintInfoSeq_II;
    constraintInfoSeq_II = filter_II->add_constraints(constraintExpSeq_II);
    return filter_II;
  };

int main(int argc,char *argv [])
{
  CORBA::ORB_ptr orb_ptr;
  try
  {
    TIDNotif::util::parser::Debugger::activate_debug(100);
    /************************************************************************/
    /*            INICIALIZAMOS LA PARTE DEL ORB                            */
    /************************************************************************/
    int alt_argc = 0;
    char ** alt_argv;
    const char * orb_id="Test_TIDNotification"  ;
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
 
    (*policies)[0] = rootPOA->create_lifespan_policy
      ( PortableServer::PERSISTENT );
    (*policies)[1] = rootPOA->create_id_assignment_policy
      ( PortableServer::USER_ID );

    PortableServer::POA_var supplierPOA = rootPOA->create_POA("supplierPOA", poa_manager, *policies );
    /***********************************************************************/
    /*   OBTENEMOS LA FACTORIA DEL CANAL DE EVENTOS Y CREAMOS EL CANAL     */
    /**********************************************************************/



    CORBA::Object_ptr delegado_event_channel_factory;
    
    //Le paso el IOR de Eventchannel Factory
    delegado_event_channel_factory=orb_ptr->string_to_object(argv[1]);
    
    CosNotifyChannelAdmin::EventChannelFactory_var factory;

    factory = CosNotifyChannelAdmin::EventChannelFactory::_narrow(delegado_event_channel_factory);
    if (CORBA::is_nil(factory)) { 
      cerr << "[server] ERROR: factoria nula " << endl;
      return -1; 
    } 
  
     CosNotifyChannelAdmin::EventChannel_var channel;



    CosNotification::QoSProperties initial_qos;
    CosNotification::AdminProperties initial_admin;
    CosNotifyChannelAdmin::ChannelID id;




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




    try { 
      // Crear el canal
      channel = factory->create_channel(initial_qos, initial_admin, id);

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

    CosNotifyChannelAdmin::SupplierAdmin_ptr supplierAdmin;
    AdminID ident;
    supplierAdmin = channel->new_for_suppliers(CosNotifyChannelAdmin::OR_OP,ident);
    printf("Obtengo el default supplier admin\n");

    /**********************************************************************/
    /*          CREAMOS UNA FACTORIA DE FILTROS                           */
    /**********************************************************************/

    //CosNotifyFilter::FilterFactory_ptr filterFactory = channel->default_filter_factory();
    //Le pasamos al create el tipo de gramática que soportamos
    //CosNotifyFilter::Filter* filter_II = filterFactory->create_filter("EXTENDED_TCL");
    
    /****************************************************************/
    /*                  CREAMOS MAS RESTRICCIONES                   */
    /****************************************************************/
/*    
    //Construimos el filtro
    CosNotification::_EventType eventType_III[1];

    eventType_III[0].domain_name = "GSyC";
    eventType_III[0].type_name = "Test";
    

    char * constraint_III = "$domain_name != 'GSyC'";

    CosNotification::EventTypeSeq eventTypeSeq_III(1,1,eventType_III,false);
    

    CosNotifyFilter::ConstraintExp constraintExp_III(eventTypeSeq_III,
                                                     constraint_III);

    CosNotifyFilter::ConstraintExpSeq constraintExpSeq_II(1);
    constraintExpSeq_II.length(1);
    
    constraintExpSeq_II[0]=constraintExp_III;
    CosNotifyFilter::ConstraintInfoSeq* constraintInfoSeq_II;
    constraintInfoSeq_II = filter_II->add_constraints(constraintExpSeq_II);*/
    

   /**************************************************************************/
   /*         OBTENEMOS EL PROXYCONSUMER APARTIR DEL SUPPLIERADMIN           */
   /**************************************************************************/

    CosNotifyChannelAdmin::ProxyConsumer_ptr proxyConsumer;
    CosNotifyChannelAdmin::ProxyID proxyConsumerID ;
    proxyConsumer = supplierAdmin->obtain_notification_push_consumer(CosNotifyChannelAdmin::STRUCTURED_EVENT,
                                                      proxyConsumerID);

    //CosNotifyFilter::Filter* filter_II = create_filter(channel,"GSyC","test","$domain_name == 'GSyC'");
    //supplierAdmin->add_filter(filter_II);
    CosNotifyFilter::Filter* filter_III = create_filter(channel,"GSyC","test","$.remainder_of_boy.campo_uno != 1");
    supplierAdmin->add_filter(filter_III);
    /**************************************************************************/
   /*         OBTENEMOS EL PROXYCONSUMER APARTIR DEL proxyConsumer           */
   /**************************************************************************/
    CosNotifyChannelAdmin::StructuredProxyPushConsumer_ptr proxyPushConsumer;
    proxyPushConsumer = CosNotifyChannelAdmin::StructuredProxyPushConsumer::_narrow(proxyConsumer);



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

    CosNotifyComm::StructuredPushSupplier_ptr my_pushSupplier = CosNotifyComm::StructuredPushSupplier::_narrow(obj_supplier);

    
    /***********************************************************************/
    /*                CONECTAMOS EL PUSHSUPPLIER Y EL PUSHCONSUMER         */
    /***********************************************************************/
   
    proxyPushConsumer->connect_structured_push_supplier(my_pushSupplier);
    
    /***********************************************************************/
    /*                Creamos el Structured Event                          */
    /***********************************************************************/


    //Contruyo los anys que necesitaré para el remainder body
    Events::Test_Event_ptr event_I = new Events::Test_Event(1,0,2);
    Events::Test_Event_ptr event_II = new Events::Test_Event(0,0,2);

    CORBA::Any any_I;
    Events::_Test_EventHelper::insert(any_I,event_I);
    CORBA::Any any_II;
    Events::_Test_EventHelper::insert(any_II,event_II);



    //Empezamos a construir el Struct..


    //CosNotification::StructuredEvent * structEvent = TestUtils::create_structured_event(
    //  "LuisPastor", "Test", "evento1", any_I);

     CosNotification::StructuredEvent * structEvent1 = TestUtils::create_structured_event(
      "GSyC", "Test", "evento2", any_II);

    while (true)
    {
      try
      {
        //my_supplier->new_event(*structEvent);
        my_supplier->new_event(*structEvent1);
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
        cerr<< "[server supplier] Object no exist fail "<< e._name() << endl;
      }

      catch (CosEventComm::Disconnected &e){
        cerr<< "[server supplier] disconnect fail "<< e._name() << endl;
      }
      TIDThr::Thread::sleep(1000);
    }

    orb_ptr->run();

    
  }
  catch (CORBA::Exception & e)
  {
    cerr<<"[Test_Filter] unknown error"<< typeid(e).name() << e._name();
   return -1;
   
  }

}

