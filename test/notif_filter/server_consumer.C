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
#include "CORBA.h"
#include "CosNotifyComm.h"

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

    PortableServer::POA_var consumerPOA = rootPOA->create_POA("consumerPOA", poa_manager, *policies );
    
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
//     initial_qos[2].value <<= CosNotification::BestEffort; // Persistent
    
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
      channel = factory->get_event_channel(0);

//       for(int i=0; i < 10; i++){
//         channelv[i] = factory->create_channel(initial_qos, initial_admin, idv[i]);
//       }
    } catch (CosNotifyChannelAdmin::ChannelNotFound &ex) { 
      cerr << "[server_consumer] CosNotifyChannelAdmin::ChannelNotFound: " << ex._name(); 
      return -1; 
    }
    /**************************************************************************/
    /*              OBTENEMOS EL CONSUMERADMIN POR DEFECTO                    */
    /**************************************************************************/
    CosNotifyChannelAdmin::ConsumerAdmin_ptr consumerAdmin;
    consumerAdmin = channel->default_consumer_admin();
   
    //Metemos los filtros en el consumer admin
    CosNotifyFilter::Filter* filter_II = create_filter(channel,"GSyC","test","$domain_name != 'GSyC'");
    //consumerAdmin->add_filter(filter_II);
    //CosNotifyFilter::Filter* filter_III = create_filter(channel,"GSyC","test","$.remainder_of_boy.campo_uno != 1");
    //consumerAdmin->add_filter(filter_III);
   /**************************************************************************/
   /*         OBTENEMOS EL PROXYSUPPLIER APARTIR DEL CONSUMERADMIN           */
   /**************************************************************************/
    //TODO_MORFEO: add new filters
    CosNotifyChannelAdmin::ProxySupplier_ptr proxySupplier;
    CosNotifyChannelAdmin::ProxyID proxySupplierID = 1;
    proxySupplier = 
      consumerAdmin->obtain_notification_push_supplier(CosNotifyChannelAdmin::ANY_EVENT,
                                                      proxySupplierID);

                                                      

   /**************************************************************************/
   /*       OBTENEMOS EL PROXYPUSHSUPPLIER APARTIR DEL CONSUMERADMIN         */
   /**************************************************************************/
    CosNotifyChannelAdmin::StructuredProxyPushSupplier_ptr proxyPushSupplier;
    
    proxyPushSupplier = CosNotifyChannelAdmin::StructuredProxyPushSupplier::_narrow(proxySupplier);



    /**************************************************************************/
    /*            INSTANCIAMOS LOS PROXYS Y LOS ACTIVAMOS EN EL POA           */
    /**************************************************************************/
    my_push_consumer * my_consumer = new my_push_consumer(orb_ptr,proxyPushSupplier);
    PortableServer::ObjectId_ptr consumer_objectID = PortableServer::string_to_ObjectId("My_Consumer:1.0");
    consumerPOA->activate_object_with_id(*consumer_objectID,my_consumer);
    poa_manager->activate();
    CORBA::Object_ptr obj_consumer = consumerPOA->id_to_reference(*consumer_objectID);
    CosNotifyComm::StructuredPushConsumer_ptr my_pushConsumer = CosNotifyComm::StructuredPushConsumer::_narrow(obj_consumer);


    /***********************************************************************/
    /*                CONECTAMOS EL PUSHSUPPLIER Y EL PUSHCONSUMER         */
    /***********************************************************************/
    proxyPushSupplier->connect_structured_push_consumer(my_pushConsumer);


    orb_ptr->run();
 
    
  }
  catch (CORBA::Exception & e)
  {
    cerr<<"[Test_Filter] unknown error"<< typeid(e).name() << e._name();
   return -1;
   
  }

}

