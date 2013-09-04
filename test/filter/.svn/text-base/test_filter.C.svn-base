/*
 *  Description: Test about filters. The program configures a channel and will 
 *               be obtained a default consumer and default supplier.
 *               Within default consumer will be added two filters for testing the
 *               FiltersAdmin implement and Filter implement
 */
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
#include "Event.h"
#include "my_push_supplier.h"
#include "my_push_consumer.h"



void show_contraint_info (CosNotifyFilter::ConstraintInfoSeq * c_infoSeq)
{
  for (int j = 0; j<c_infoSeq->length();j++)
  {
    printf("_______________________________________________________\n");
    printf("ConstraintID: ");
    printf("%d\n",(*c_infoSeq)[j].constraint_id);
    printf("---------------Tipos de Eventos------------------\n");
    CosNotifyFilter::ConstraintExp constraintExp_aux = 
                    (*c_infoSeq)[j].constraint_expression;
    for (int k = 0;
        k<constraintExp_aux.event_types.length(); 
        k++)
    {
      printf("Dominio: ");
      printf("%s\n",constraintExp_aux.event_types[k].domain_name.in());
      printf("Tipo: ");
      printf("%s\n",constraintExp_aux.event_types[k].type_name.in());
      printf("-------------------------------------------------\n");
    }
    printf("Restriccion: ");
    printf("%s\n",constraintExp_aux.constraint_expr.in());
    printf("_______________________________________________________\n");
  }
}

CosNotifyFilter::FilterIDSeq* 
show_filters_consumer (CosNotifyChannelAdmin::ConsumerAdmin_ptr consumerAdmin)
{
    /****************************************************************/
    /*    OBTENEMOS TODOS LOS FILTROS INSERTADOS HASTA EL MOMENTO   */
    /****************************************************************/
    CosNotifyFilter::FilterIDSeq* filterIDSeq = consumerAdmin->get_all_filters();
    try
    {
      for (int i = 0; i<filterIDSeq->length();i++)
      {
        printf("\n");
  
        /***************************************************************/
        /*           RECUPERAMOS UNO DE LOS FILTROS CREADOS            */
        /***************************************************************/
        CosNotifyFilter::Filter_ptr filter_duplicado;
        filter_duplicado = consumerAdmin->get_filter((*filterIDSeq)[i]);
        /***************************************************************/
        /*   RECUPERAMOS LAS RESTRICCIONES QUE CONTIENE DICHO FILTRO   */
        /***************************************************************/
        CosNotifyFilter::ConstraintInfoSeq * constraintInfoSeq_duplicado;
        constraintInfoSeq_duplicado = filter_duplicado->get_all_constraints();
        printf("***************Restricciones del filtro %d*****************\n",(*filterIDSeq)[i]);
        show_contraint_info(constraintInfoSeq_duplicado);
        printf("**********************************************************\n");
      }
    }
    catch (CosNotifyFilter::FilterNotFound & e)
    {
      cerr << "[FilterAdmin] the get_all_filters fails" << e._name();
      throw CosNotifyFilter::FilterNotFound();
    }
    return filterIDSeq;
}



int main(int argc,char *argv [])
{

  char aux1[1000];
 
  CORBA::ORB_ptr orb_ptr;
  try
  {
    /************************************************************************/
    /*            INICIALIZAMOS LA PARTE DEL ORB                            */
    /************************************************************************/
    int alt_argc = 0;
    char ** alt_argv;
    const char * orb_id="Test_TIDNotification";
    //orb_ptr=CORBA::ORB_init(alt_argc, alt_argv, orb_id);
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
    rootPOA = PortableServer::POA::_narrow(delegado_POA);


    /***********************************************************************/
    /*                CREAMOS DIFERENTES EVENTOS ANY                       */
    /***********************************************************************/
    long value1 = 5;
    long value2 = 1;
    long value3 = 2;
   
    CORBA::StructMemberSeq members(3);
    members.length(3);
    members[0].name = CORBA::string_dup("campo_uno");
    members[0].type = CORBA::TypeCode::_duplicate(CORBA::_tc_long);
    members[1].name = CORBA::string_dup("campo_dos");
    members[1].type = CORBA::TypeCode::_duplicate(CORBA::_tc_long);
    members[2].name = CORBA::string_dup("campo_tres");
    members[2].type = CORBA::TypeCode::_duplicate(CORBA::_tc_long);
    CORBA::TypeCode_ptr event_struct_tc;
    event_struct_tc = orb_ptr->create_struct_tc("IDL::StructEvent:1.0",
                                              "Struct_Event", 
                                              members);
     
    DynamicAny::DynAnyFactory_var dafact;
    
    dafact =  DynamicAny::DynAnyFactory::_narrow(orb_ptr->resolve_initial_references("DynAnyFactory"));
    

    DynamicAny::DynAny_ptr dyn_any;
    dyn_any = dafact->create_dyn_any_from_type_code(event_struct_tc);
    
    DynamicAny::DynStruct_ptr dyn_struct;

    dyn_struct = DynamicAny::DynStruct::_narrow(dyn_any);
    
    
    CORBA::release(dyn_any);
    dyn_struct->seek(0);
    dyn_struct->insert_long(value1);
    
    dyn_struct->next();
    dyn_struct->insert_long(value2);
    dyn_struct->next();
    dyn_struct->insert_long(value3);
    
    CORBA::Any_var event_struct = dyn_struct->to_any();
    dyn_struct->destroy();
    CORBA::release(dyn_struct);


    Events::Test_Event_ptr event_I = new Events::Test_Event(5,1,11);
    Events::Test_Event_ptr event_II = new Events::Test_Event(5,8,2);
    Events::Test_Event_ptr event_III = new Events::Test_Event(5,8,11);
    Events::Test_Event_ptr event_IV = new Events::Test_Event(5,10,2);
    Events::Test_Event_ptr event_V = new Events::Test_Event(5,10,11);
    Events::Test_Event_ptr event_VI = new Events::Test_Event(7,1,2);
    Events::Test_Event_ptr event_VII = new Events::Test_Event(7,1,11);
    Events::Test_Event_ptr event_VIII = new Events::Test_Event(7,8,2);
    Events::Test_Event_ptr event_IX = new Events::Test_Event(7,8,11);
    Events::Test_Event_ptr event_X = new Events::Test_Event(7,10,2);
    Events::Test_Event_ptr event_XI = new Events::Test_Event(7,10,11);
    Events::Test_Event_ptr event_XII = new Events::Test_Event(6,1,2);
    Events::Test_Event_ptr event_XIII = new Events::Test_Event(6,1,11);
    Events::Test_Event_ptr event_XIV = new Events::Test_Event(6,8,2);
    Events::Test_Event_ptr event_XV = new Events::Test_Event(6,8,11);
    Events::Test_Event_ptr event_XVI = new Events::Test_Event(6,10,2);
    Events::Test_Event_ptr event_XVII = new Events::Test_Event(6,10,11);
    Events::Test_Event_ptr event_XVIII = new Events::Test_Event(0,1,2);
    Events::Test_Event_ptr event_XIX = new Events::Test_Event(0,1,11);
    Events::Test_Event_ptr event_XX = new Events::Test_Event(0,8,2);
    Events::Test_Event_ptr event_XXI = new Events::Test_Event(0,8,11);
    Events::Test_Event_ptr event_XXII = new Events::Test_Event(0,10,2);
    Events::Test_Event_ptr event_XXIII = new Events::Test_Event(0,10,11);
    Events::Test_Event_ptr event_XXIV = new Events::Test_Event(3,3,3);
    

    // TODO: Use standard << operator 

    CORBA::Any any_I;
    any_I <<= event_I;

    CORBA::Any any_II;
    any_II <<= event_II;

    CORBA::Any any_III;
    any_III <<= event_III;

    CORBA::Any any_IV;
    any_IV <<= event_IV;

    CORBA::Any any_V;
    any_V <<= event_V;

    CORBA::Any any_VI;
    any_VI <<= event_VI;

    CORBA::Any any_VII;
    any_VII <<= event_VII;

    CORBA::Any any_VIII;
    any_VIII <<= event_VIII;

    CORBA::Any any_IX;
    any_IX <<= event_IX;

    CORBA::Any any_X;
    any_X <<= event_X;

    CORBA::Any any_XI;
    any_XI <<= event_XI;

    CORBA::Any any_XII;
    any_XII <<= event_XII;

    CORBA::Any any_XIII;
    any_XIII <<= event_XIII;

    CORBA::Any any_XIV;
    any_XIV <<= event_XIV;

    CORBA::Any any_XV;
    any_XV <<= event_XV;

    CORBA::Any any_XVI;
    any_XVI <<= event_XVI;

    CORBA::Any any_XVII;
    any_XVII <<= event_XVII;

    CORBA::Any any_XVIII;
    any_XVIII <<= event_XVIII;

    CORBA::Any any_XIX;
    any_XIX <<= event_XIX;

    CORBA::Any any_XX;
    any_XX <<= event_XX;

    CORBA::Any any_XXI;
    any_XXI <<= event_XXI;

    CORBA::Any any_XXII;
    any_XXII <<= event_XXII;

    CORBA::Any any_XXIII;
    any_XXIII <<= event_XXIII;

    CORBA::Any any_XXIV;
    any_XXIV <<= event_XXIV;

    /***********************************************************************/
    /*   OBTENEMOS LA FACTORIA DEL CANAL DE EVENTOS Y CREAMOS EL CANAL     */
    /**********************************************************************/

    CORBA::Object_ptr delegado_event_channel_factory;
    //delegado_event_channel_factory=orb_ptr->string_to_object(argv[1]);
    cin >> aux1;   
    delegado_event_channel_factory = orb_ptr->string_to_object(aux1);
    CosNotifyChannelAdmin::EventChannelFactory_var factory;
    factory = CosNotifyChannelAdmin::EventChannelFactory::_narrow(delegado_event_channel_factory);
    if (CORBA::is_nil(factory)) { 
      cerr << "[test_filter] ERROR: factoria nula " << endl;
      return -1; 
    } 
  
     CosNotifyChannelAdmin::EventChannel_var channel;


    CosNotification::QoSProperties initial_qos;
    CosNotification::AdminProperties initial_admin;
    CosNotifyChannelAdmin::ChannelID id;


//     // Politicas QoS

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

    try { 
      // Crear el canal
      channel = factory->create_channel(initial_qos, initial_admin, id);

    } catch (CosNotification::UnsupportedQoS &ex) { 
      cerr << "[test_filter] CosNotification::UnsupportedQoS: " << ex._name(); 
      return -1; 
    } catch (CosNotification::UnsupportedAdmin &ex) { 
      cerr << "[test_filter] CosNotification::UnsupportedAdmin: " << ex._name(); 
      return -1; 
    } catch (CORBA::SystemException &ex) { 
      cerr << "[test_filter] SystemExcepcion: " << ex._name(); 
      return -1; 
    } 
    /**************************************************************************/
    /*              OBTENEMOS EL CONSUMERADMIN POR DEFECTO                    */
    /**************************************************************************/
    CosNotifyChannelAdmin::ConsumerAdmin_ptr consumerAdmin;
    consumerAdmin = channel->default_consumer_admin();
    /**************************************************************************/
    /*              OBTENEMOS EL SUPPLIERADMIN POR DEFECTO                    */
    /**************************************************************************/
    //TODO_MORFEO: add new filters
    CosNotifyChannelAdmin::SupplierAdmin_ptr supplierAdmin;
    supplierAdmin = channel->default_supplier_admin();
    /**************************************************************************/
    /*         OBTENEMOS EL PROXYSUPPLIER APARTIR DEL CONSUMERADMIN           */
    /**************************************************************************/
    //TODO_MORFEO: add new filters
    CosNotifyChannelAdmin::ProxySupplier_ptr proxySupplier;
    CosNotifyChannelAdmin::ProxyID proxySupplierID;
    proxySupplier = 
      consumerAdmin->obtain_notification_push_supplier(CosNotifyChannelAdmin::ANY_EVENT,
                                                      proxySupplierID);
    /**************************************************************************/
    /*         OBTENEMOS EL PROXYCONSUMER APARTIR DEL SUPPLIERADMIN           */
    /**************************************************************************/
    //TODO_MORFEO: add new filters
    CosNotifyChannelAdmin::ProxyConsumer_ptr proxyConsumer;
    CosNotifyChannelAdmin::ProxyID proxyConsumerID;
    proxyConsumer = 
      supplierAdmin->obtain_notification_push_consumer(CosNotifyChannelAdmin::ANY_EVENT,
                                                      proxyConsumerID);
                                                      

    /**************************************************************************/
    /*       OBTENEMOS EL PROXYPUSHSUPPLIER APARTIR DEL CONSUMERADMIN         */
    /**************************************************************************/
    CosEventChannelAdmin::ProxyPushSupplier_ptr proxyPushSupplier;
    
    proxyPushSupplier = 
      consumerAdmin->obtain_push_supplier();
    /**************************************************************************/
    /*         OBTENEMOS EL PROXYCONSUMER APARTIR DEL SUPPLIERADMIN           */
    /**************************************************************************/
    CosEventChannelAdmin::ProxyPushConsumer_ptr proxyPushConsumer;
  
    proxyPushConsumer = 
      supplierAdmin->obtain_push_consumer();

    /**************************************************************************/
    /*            INSTANCIAMOS LOS PROXYS Y LOS ACTIVAMOS EN EL POA           */
    /**************************************************************************/
    my_push_consumer * my_consumer = new my_push_consumer(orb_ptr,proxyPushSupplier);
    my_push_supplier * my_supplier = new my_push_supplier(proxyPushConsumer);

    PortableServer::ObjectId_ptr consumer_objectID = rootPOA->activate_object(my_consumer);
    PortableServer::ObjectId_ptr supplier_objectID = rootPOA->activate_object(my_supplier);
    CosEventComm::PushSupplier_ptr my_pushSupplier = my_supplier->_this();
    CosEventComm::PushConsumer_ptr my_pushConsumer = my_consumer->_this();

    /***********************************************************************/
    /*                      ACTIVAMOS EL POAMANAGER                        */
    /***********************************************************************/
    rootPOA->the_POAManager()->activate();
    /***********************************************************************/
    /*                CONECTAMOS EL PUSHSUPPLIER Y EL PUSHCONSUMER         */
    /***********************************************************************/
    proxyPushConsumer->connect_push_supplier(my_pushSupplier);
    proxyPushSupplier->connect_push_consumer(my_pushConsumer);


    /*****************************************************************************/
    /*OBTENEMOS DEL CANAL LA FACTORIA DE FILTROS POR DEFECTO Y CREAMOS LOS FILTRO*/
    /*****************************************************************************/
    CosNotifyFilter::FilterFactory_ptr filterFactory = channel->default_filter_factory();
    CosNotifyFilter::Filter* filter_I = filterFactory->create_filter("EXTENDED_TCL");
    CosNotifyFilter::Filter* filter_II = filterFactory->create_filter("EXTENDED_TCL");
    /****************************************************************/
    /*                  CREAMOS LAS RESTRICCIONES                   */
    /****************************************************************/
    CosNotification::_EventType eventType_I[2];

    eventType_I[0].domain_name = "URJC";
    eventType_I[0].type_name = "Entregas";
    eventType_I[1].domain_name = "TID";
    eventType_I[1].type_name = "Proyectos";

    CosNotification::_EventType eventType_II[1];
    eventType_II[0].domain_name = "Morfeo";
    eventType_II[0].type_name = "Difusiones";

    char * constraint_I = "$.campo_uno == 5";
    char * constraint_II = "$.campo_dos == 1";

    CosNotification::EventTypeSeq eventTypeSeq_I(2,2,eventType_I,false);
    CosNotification::EventTypeSeq eventTypeSeq_II(1,1,eventType_II,false);

    CosNotifyFilter::ConstraintExp constraintExp_I(eventTypeSeq_I,constraint_I);
    CosNotifyFilter::ConstraintExp constraintExp_II(eventTypeSeq_II,constraint_II);

    CosNotifyFilter::ConstraintExpSeq constraintExpSeq_I(2);
    constraintExpSeq_I.length(2);
    
    constraintExpSeq_I[0]=constraintExp_I;
    constraintExpSeq_I[1]=constraintExp_II;

    /****************************************************************/
    /*             INSERTAMOS LAS RESTRICCIONES AL FILTRO           */
    /****************************************************************/
    CosNotifyFilter::ConstraintInfoSeq* constraintInfoSeq_I;
    constraintInfoSeq_I = filter_I->add_constraints(constraintExpSeq_I); /// 5CORBA11OBJ_ADAPTEREOBJ_ADAPTER

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

    /****************************************************************/
    /*             INSERTAMOS LAS RESTRICCIONES AL FILTRO           */
    /****************************************************************/
    CosNotifyFilter::ConstraintInfoSeq* constraintInfoSeq_II;
    constraintInfoSeq_II = filter_II->add_constraints(constraintExpSeq_II);

   /****************************************************************/
   /*       INSERTAMOS LOS FILTROS DENTRO DEL CONSUMERADMIN        */
   /****************************************************************/
    CosNotifyFilter::FilterID filterID_I = consumerAdmin->add_filter(filter_I);
    CosNotifyFilter::FilterID filterID_II = consumerAdmin->add_filter(filter_II);
    /******************************************************************/
    /*    MOSTRAMOS LOS FILTROS INSERTADOS DENTRO DEL CONSUMERADMIN   */
    /******************************************************************/
    CosNotifyFilter::FilterIDSeq* _filterIDSeq;
    _filterIDSeq = show_filters_consumer(consumerAdmin);
    /*********************************************************************/
    /*MANDAMOS LOS EVENTOS Y COMPROBAMOS QUE EVENTOS HAN PASADO EL FILTRO*/
    /*********************************************************************/
    my_consumer->new_events(1);
    my_consumer->add_event(event_struct);

    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
    my_supplier->new_event(any_XXII);
    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);

    my_supplier->new_event(event_struct);

    while (!my_consumer->finished()){
        TIDThr::Thread::sleep(1000);
    }
    if (!my_consumer->ok()) {
      cerr<<"[test_filter] 1. There are events that must not arrive"<<endl;
      return -1;
    }



    /************************************************************************/
    /*                ELIMINAMOS UNO DE LOS FILTROS                         */
    /************************************************************************/
    consumerAdmin->remove_filter((*_filterIDSeq)[0]);
    
    
    /*********************************************************************/
    /*MANDAMOS LOS EVENTOS Y COMPROBAMOS QUE EVENTOS HAN PASADO EL FILTRO*/
    /*********************************************************************/
    my_consumer->new_events(12);
    my_consumer->add_event(event_struct);
    my_consumer->add_event(any_II);
    my_consumer->add_event(any_IV);
    my_consumer->add_event(any_VI);
    my_consumer->add_event(any_VIII);
    my_consumer->add_event(any_X);
    my_consumer->add_event(any_XII);
    my_consumer->add_event(any_XIV);
    my_consumer->add_event(any_XVI);
    my_consumer->add_event(any_XVIII);
    my_consumer->add_event(any_XX);
    my_consumer->add_event(any_XXII);
    
    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
    my_supplier->new_event(any_XXII);
    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);

    my_supplier->new_event(event_struct);

    while (!my_consumer->finished()) {
      TIDThr::Thread::sleep(1000);
    }
    if (!my_consumer->ok()) {
      cerr<<"[Filter] There are events that must not arrive"<<endl;
      return -1;
    }


    /************************************************************************/
    /*       INTETAMOS VOLVER A BORRAR EL FILTRO ELIMINADO ANTERIORMENTE    */
    /************************************************************************/
    bool ok = false;
    try {
      consumerAdmin->remove_filter((*_filterIDSeq)[0]);
    } catch (CosNotifyFilter::FilterNotFound & e) {
      ok = true;
    }
    if (!ok) {
      cerr<<"[test_filter] 2. The erasure method fails"<<endl;
      return -1;
    }

    /*********************************************************************/
    /*MANDAMOS LOS EVENTOS Y COMPROBAMOS QUE EVENTOS HAN PASADO EL FILTRO*/
    /*********************************************************************/
    my_consumer->new_events(12);
    my_consumer->add_event(event_struct);
    my_consumer->add_event(any_II);
    my_consumer->add_event(any_IV);
    my_consumer->add_event(any_VI);
    my_consumer->add_event(any_VIII);
    my_consumer->add_event(any_X);
    my_consumer->add_event(any_XII);
    my_consumer->add_event(any_XIV);
    my_consumer->add_event(any_XVI);
    my_consumer->add_event(any_XVIII);
    my_consumer->add_event(any_XX);
    my_consumer->add_event(any_XXII);

    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
    my_supplier->new_event(any_XXII);
    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);

    my_supplier->new_event(event_struct);

    while (!my_consumer->finished()) {
      TIDThr::Thread::sleep(1000);
    }

    if (!my_consumer->ok()) {
      cerr<<"[test_filter] 3. There are events that must not arrive"<<endl;
      return -1;
    }

    /************************************************************************/
    /*      INTENTAMOS OBTENER EL FILTRO ELIMINADO ANTERIORMENTE            */
    /************************************************************************/
    ok = false;
    try {
      CosNotifyFilter::Filter_ptr filter_not_found_I = 
        consumerAdmin->get_filter((*_filterIDSeq)[0]);
    }
    catch (CosNotifyFilter::FilterNotFound & e) {
      ok = true;
    }

    if (!ok) {
      cerr<<"[test_filter] The get_fiter method fails"<<endl;
      return -1;
    } 
   

    /************************************************************************/
    /*         VOLVEMOS A INSERTAR EL FILTRO ELIMINADO                      */
    /************************************************************************/
    CosNotifyFilter::FilterID filterID_reinsertado_I = consumerAdmin->add_filter(filter_I);
   
    /*********************************************************************/
    /*MANDAMOS LOS EVENTOS Y COMPROBAMOS QUE EVENTOS HAN PASADO EL FILTRO*/
    /*********************************************************************/
    my_consumer->new_events(1);
    my_consumer->add_event(event_struct);

    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
    my_supplier->new_event(any_XXII);
    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);

    my_supplier->new_event(event_struct);

    while (!my_consumer->finished()) {
      TIDThr::Thread::sleep(1000);
    }
    if (!my_consumer->ok()) {
      cerr<<"[test_filter] 4. There are events that must not arrive"<<endl;
      return -1;
    }

    /************************************************************************/
    /*              ELIMINAMOS EL OTRO DE LOS FILTROS                       */
    /************************************************************************/
    consumerAdmin->remove_filter((*_filterIDSeq)[1]);

    my_consumer->new_events(2);
    my_consumer->add_event(event_struct);
    my_consumer->add_event(any_I);
   
    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
    my_supplier->new_event(any_XXII);
    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);

    my_supplier->new_event(event_struct);

    while (!my_consumer->finished()) {
      TIDThr::Thread::sleep(1000);
    }
    if (!my_consumer->ok()) {
      cerr<<"[test_filter] 5. There are events that must not arrive"<<endl;
      return -1;
    }

    /************************************************************************/
    /*         VOLVEMOS A INSERTAR EL FILTRO ELIMINADO                      */
    /************************************************************************/
    CosNotifyFilter::FilterID filterID_reinsertado_II;
    filterID_reinsertado_II = consumerAdmin->add_filter(filter_II);
   
    /*********************************************************************/
    /*MANDAMOS LOS EVENTOS Y COMPROBAMOS QUE EVENTOS HAN PASADO EL FILTRO*/
    /*********************************************************************/
    my_consumer->new_events(1);
    my_consumer->add_event(event_struct);

    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
    my_supplier->new_event(any_XXII);
    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);

    my_supplier->new_event(event_struct);

    while (!my_consumer->finished())
      {
        TIDThr::Thread::sleep(1000);
      }
    if (!my_consumer->ok())
      {
        cerr<<"[tst_filter] 6. There are events that must not arrive"<<endl;
        return -1;
      }
    /**********************************************************************/
    /*OPERACIONES DE MODIFICACION Y ELIMINACION DIRECTAMENTE SOBRE FILTROS*/
    /**********************************************************************/

    CosNotifyFilter::Filter_var test_filter;
    test_filter = consumerAdmin->get_filter((*_filterIDSeq)[0]);

    CosNotifyFilter::ConstraintInfoSeq * c_info_seq_empty;
    c_info_seq_empty = new CosNotifyFilter::ConstraintInfoSeq();
    c_info_seq_empty->length(0);
    CosNotifyFilter::ConstraintIDSeq * c_id_seq_empty;
    c_id_seq_empty = new CosNotifyFilter::ConstraintIDSeq();
    c_id_seq_empty->length(0);

    CosNotifyFilter::ConstraintIDSeq * c_id_not_found = new CosNotifyFilter::ConstraintIDSeq();
    c_id_not_found->length(1);
    (*c_id_not_found)[0]=3;
    /***/
    try
      {
    
        CosNotifyFilter::ConstraintInfoSeq * c_info_not_found;
        c_info_not_found = test_filter->get_constraints(*c_id_not_found);
        show_contraint_info(c_info_not_found);
        cerr<<"[test_filter] The get_constraints method fails"<<endl;
        return -1; //Debería haber dado ConstraintNotFound
      }
    catch(CosNotifyFilter::ConstraintNotFound & e)
      {
        //OK
      }
    /***/
    try
      {
        test_filter->modify_constraints(*c_id_not_found,*c_info_seq_empty);
        cerr<<"[test_filter] The modify_constraints method fails"<<endl;
        return -1; //Debería haber dado ConstraintNotFound
      }
    catch(CosNotifyFilter::ConstraintNotFound & e)
      {
        //OK
      }
    /*********************************************************************/
    /*MANDAMOS LOS EVENTOS Y COMPROBAMOS QUE EVENTOS HAN PASADO EL FILTRO*/
    /*********************************************************************/
    my_consumer->new_events(1);
    my_consumer->add_event(event_struct);

    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
    my_supplier->new_event(any_XXII);
    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);

    my_supplier->new_event(event_struct);

    while (!my_consumer->finished())
      {
        TIDThr::Thread::sleep(1000);
      }
    if (!my_consumer->ok())
      {
        cerr<<"[test_filter] 7. There are events that must not arrive"<<endl;
        return -1;
      }
    /***/
    try
      {
        CosNotification::_EventType not_found_eventType_III[1];

        not_found_eventType_III[0].domain_name = "GSyC";
        not_found_eventType_III[0].type_name = "Test";
    

        char * not_found_constraint_III = "$.campo_tres == 11";

        CosNotification::EventTypeSeq not_found_eventTypeSeq_III(1,
                                                                 1,
                                                                 not_found_eventType_III,
                                                                 false);
    

        CosNotifyFilter::ConstraintExp not_found_constraintExp_III(not_found_eventTypeSeq_III,
                                                                   not_found_constraint_III);

        CosNotifyFilter::ConstraintInfo not_found_c_info_II (not_found_constraintExp_III,
                                                             3);

        CosNotifyFilter::ConstraintInfoSeq * not_found_constraintInfoSeq;
        not_found_constraintInfoSeq = new CosNotifyFilter::ConstraintInfoSeq(2);
        not_found_constraintInfoSeq->length(2);
        (*not_found_constraintInfoSeq)[0]=not_found_c_info_II;
        test_filter->modify_constraints(*c_id_seq_empty,*not_found_constraintInfoSeq);
        cerr<<"[test_filter] The modify_constraints method fails"<<endl;
        return -1; //Debería haber dado ConstraintNotFound
      }
    catch(CosNotifyFilter::ConstraintNotFound & e)
      {
        //OK
      }
    /*********************************************************************/
    /*MANDAMOS LOS EVENTOS Y COMPROBAMOS QUE EVENTOS HAN PASADO EL FILTRO*/
    /*********************************************************************/
    my_consumer->new_events(1);
    my_consumer->add_event(event_struct);

    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
    my_supplier->new_event(any_XXII);
    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);

    my_supplier->new_event(event_struct);

    while (!my_consumer->finished())
      {
        TIDThr::Thread::sleep(1000);
      }
    if (!my_consumer->ok())
      {
        cerr<<"[test_filter] 8. There are events that must not arrive"<<endl;
        return -1;
      }
    /***/
    try
      {
        CosNotification::_EventType invalid_constraint_eventType_I[2];

        invalid_constraint_eventType_I[0].domain_name = "URJC";
        invalid_constraint_eventType_I[0].type_name = "Entregas";
        invalid_constraint_eventType_I[1].domain_name = "TID";
        invalid_constraint_eventType_I[1].type_name = "Proyectos";

        CosNotification::_EventType invalid_constraint_eventType_II[1];
        invalid_constraint_eventType_II[0].domain_name = "Morfeo";
        invalid_constraint_eventType_II[0].type_name = "Difusiones";

        char * invalid_constraint_I = "$.campo_uno == 7";
        char * invalid_constraint_II =  
          "('David','Alvaro','Tomas') in ('Alex', 'Alvaro', 'JuanPe')";

        CosNotification::EventTypeSeq 
          invalid_constraint_eventTypeSeq_I(2,
                                            2,
                                            invalid_constraint_eventType_I,
                                            false);

        CosNotification::EventTypeSeq 
          invalid_constraint_eventTypeSeq_II(1,
                                             1,
                                             invalid_constraint_eventType_II,
                                             false);

        CosNotifyFilter::ConstraintExp
          invalid_constraintExp_I(invalid_constraint_eventTypeSeq_I,
                                  invalid_constraint_I);

        CosNotifyFilter::ConstraintExp
          invalid_constraintExp_II(invalid_constraint_eventTypeSeq_II,
                                   invalid_constraint_II);


        CosNotifyFilter::ConstraintInfo 
          invalid_constraint_c_info_I (invalid_constraintExp_I,
                                       (CosNotifyFilter::ConstraintID)1);

        CosNotifyFilter::ConstraintInfo 
          invalid_constraint_c_info_II (invalid_constraintExp_II,
                                        (CosNotifyFilter::ConstraintID)2);

        CosNotifyFilter::ConstraintInfoSeq * invalid_constraintInfoSeq;
        invalid_constraintInfoSeq = new CosNotifyFilter::ConstraintInfoSeq(2);
        invalid_constraintInfoSeq->length(2);
        (*invalid_constraintInfoSeq)[0]=invalid_constraint_c_info_I;
        (*invalid_constraintInfoSeq)[1]=invalid_constraint_c_info_II;
        test_filter->modify_constraints(*c_id_seq_empty,
                                        *invalid_constraintInfoSeq);
        cerr<<"[test_filter] The modify_constraints method fails"<<endl;
        return -1; //InvalidConstraint must be sent
      }
    catch(CosNotifyFilter::InvalidConstraint & e)
      {
        //OK
      }
    /***/
    /*********************************************************************/
    /*MANDAMOS LOS EVENTOS Y COMPROBAMOS QUE EVENTOS HAN PASADO EL FILTRO*/
    /*********************************************************************/
    my_consumer->new_events(1);
    my_consumer->add_event(event_struct);

    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
    my_supplier->new_event(any_XXII);
    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);

    my_supplier->new_event(event_struct);

    while (!my_consumer->finished())
      {
        TIDThr::Thread::sleep(1000);
      }
    if (!my_consumer->ok())
      {
        cerr<<"[test_filter] 9. There are events that must not arrive"<<endl;
        return -1;
      }
    /***/
    try
      {
        CosNotifyFilter::ConstraintIDSeq *del_last_id;
        del_last_id = new CosNotifyFilter::ConstraintIDSeq(1);
        del_last_id->length(1);
        (*del_last_id)[0]=2;
        CosNotification::_EventType invalid_constraint_eventType_I[2];

        invalid_constraint_eventType_I[0].domain_name = "URJC";
        invalid_constraint_eventType_I[0].type_name = "Entregas";
        invalid_constraint_eventType_I[1].domain_name = "TID";
        invalid_constraint_eventType_I[1].type_name = "Proyectos";

        CosNotification::_EventType invalid_constraint_eventType_II[1];
        invalid_constraint_eventType_II[0].domain_name = "Morfeo";
        invalid_constraint_eventType_II[0].type_name = "Difusiones";

        char * invalid_constraint_I = "$.campo_uno == 6";
        char * invalid_constraint_II = "$.campo_uno == 8";

        CosNotification::EventTypeSeq 
          invalid_constraint_eventTypeSeq_I(2,
                                            2,
                                            invalid_constraint_eventType_I,
                                            false);

        CosNotification::EventTypeSeq 
          invalid_constraint_eventTypeSeq_II(1,
                                             1,
                                             invalid_constraint_eventType_II,
                                             false);

        CosNotifyFilter::ConstraintExp
          invalid_constraintExp_I(invalid_constraint_eventTypeSeq_I,
                                  invalid_constraint_I);

        CosNotifyFilter::ConstraintExp
          invalid_constraintExp_II(invalid_constraint_eventTypeSeq_II,
                                   invalid_constraint_II);


        CosNotifyFilter::ConstraintInfo 
          invalid_constraint_c_info_I (invalid_constraintExp_I,
                                       (CosNotifyFilter::ConstraintID)1);

        CosNotifyFilter::ConstraintInfo 
          invalid_constraint_c_info_II (invalid_constraintExp_II,
                                        (CosNotifyFilter::ConstraintID)2);

        CosNotifyFilter::ConstraintInfoSeq * invalid_constraintInfoSeq;
        invalid_constraintInfoSeq = new CosNotifyFilter::ConstraintInfoSeq(2);
        invalid_constraintInfoSeq->length(2);
        (*invalid_constraintInfoSeq)[0]=invalid_constraint_c_info_I;
        (*invalid_constraintInfoSeq)[1]=invalid_constraint_c_info_II;
        test_filter->modify_constraints(*del_last_id,
                                        *invalid_constraintInfoSeq);
        cerr<<"[test_filter] The modify_constraints method fails"<<endl;
        return -1; //Debería haber dado ConstraintNotFound
      }
    catch(CosNotifyFilter::ConstraintNotFound & e)
      {
        //OK
      }
    /***/
    /*********************************************************************/
    /*MANDAMOS LOS EVENTOS Y COMPROBAMOS QUE EVENTOS HAN PASADO EL FILTRO*/
    /*********************************************************************/
    my_consumer->new_events(1);
    my_consumer->add_event(event_struct);

    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
    my_supplier->new_event(any_XXII);
    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);

    my_supplier->new_event(event_struct);

    while (!my_consumer->finished())
      {
        TIDThr::Thread::sleep(1000);
      }
    if (!my_consumer->ok())
      {
        cerr<<"[test_filter] 10. There are events that must not arrive"<<endl;
        return -1;
      }

    CosNotifyFilter::ConstraintInfoSeq * c_info_seq = test_filter->get_all_constraints();
    CosNotifyFilter::ConstraintIDSeq * c_id_seq = new CosNotifyFilter::ConstraintIDSeq();
    c_id_seq->length(c_info_seq->length());
    for (int i = 0; i<c_info_seq->length();i++)
      {
        (*c_id_seq)[i]=(*c_info_seq)[i].constraint_id;
      }
    c_info_seq =test_filter->get_constraints(*c_id_seq);

  

    CosNotification::_EventType modified_eventType_I[2];

    modified_eventType_I[0].domain_name = "URJC_RELOADED";
    modified_eventType_I[0].type_name = "Entregas";
    modified_eventType_I[1].domain_name = "TID_RELOADED";
    modified_eventType_I[1].type_name = "Proyectos";

    CosNotification::_EventType modified_eventType_II[1];
    modified_eventType_II[0].domain_name = "Morfeo_RELOADED";
    modified_eventType_II[0].type_name = "Difusiones";

    char * modified_constraint_I = "$.campo_uno == 0";
    char * modified_constraint_II = "$.campo_dos == 10";

    CosNotification::EventTypeSeq modified_eventTypeSeq_I(2,
                                                          2,
                                                          modified_eventType_I,
                                                          false);
    CosNotification::EventTypeSeq modified_eventTypeSeq_II(1,
                                                           1,
                                                           modified_eventType_II,
                                                           false);

    CosNotifyFilter::ConstraintExp modified_constraintExp_I(modified_eventTypeSeq_I,
                                                            modified_constraint_I);

    CosNotifyFilter::ConstraintExp modified_constraintExp_II(modified_eventTypeSeq_II,
                                                             modified_constraint_II);



    CosNotifyFilter::ConstraintInfo modified_c_info_I (modified_constraintExp_I,
                                                       (*c_info_seq)[0].constraint_id);
    CosNotifyFilter::ConstraintInfo modified_c_info_II (modified_constraintExp_II,
                                                        (*c_info_seq)[1].constraint_id);

    CosNotifyFilter::ConstraintInfoSeq * modified_constraintInfoSeq;
    modified_constraintInfoSeq = new CosNotifyFilter::ConstraintInfoSeq(2);
    modified_constraintInfoSeq->length(2);
    (*modified_constraintInfoSeq)[0]=modified_c_info_I;
    (*modified_constraintInfoSeq)[1]=modified_c_info_II;
    
 

    test_filter->modify_constraints(*c_id_seq_empty,*modified_constraintInfoSeq);

    /*********************************************************************/
    /*MANDAMOS LOS EVENTOS Y COMPROBAMOS QUE EVENTOS HAN PASADO EL FILTRO*/
    /*********************************************************************/
    my_consumer->new_events(1);
    my_consumer->add_event(any_XXII);

    my_supplier->new_event(event_struct);
    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
  
    my_supplier->new_event(any_XXII);

    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);


    while (!my_consumer->finished())
      {
        TIDThr::Thread::sleep(1000);
      }
    if (!my_consumer->ok())
      {
        cerr<<"[test_filter] 11. There are events that must not arrive"<<endl;
        return -1;
      }

    CosNotifyFilter::ConstraintIDSeq * c_id_seq_one = new CosNotifyFilter::ConstraintIDSeq();
    c_id_seq_one->length(1);
    (*c_id_seq_one)[0]=(*c_info_seq)[0].constraint_id;

    test_filter->modify_constraints(*c_id_seq_one,*c_info_seq_empty);
    /*********************************************************************/
    /*MANDAMOS LOS EVENTOS Y COMPROBAMOS QUE EVENTOS HAN PASADO EL FILTRO*/
    /*********************************************************************/
    my_consumer->new_events(4);
    my_consumer->add_event(any_IV);
    my_consumer->add_event(any_X);
    my_consumer->add_event(any_XVI);
    my_consumer->add_event(any_XXII);

    my_supplier->new_event(event_struct);
    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
    my_supplier->new_event(any_XXII);
    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);


    while (!my_consumer->finished())
      {
        TIDThr::Thread::sleep(1000);
      }
    if (!my_consumer->ok())
      {
        cerr<<"[test_filter] 12. There are events that must not arrive"<<endl;
        return -1;
      }

  
    test_filter->remove_all_constraints();
    /*********************************************************************/
    /*MANDAMOS LOS EVENTOS Y COMPROBAMOS QUE EVENTOS HAN PASADO EL FILTRO*/
    /*********************************************************************/
    my_consumer->new_events(12);
    my_consumer->add_event(event_struct);
    my_consumer->add_event(any_II);
    my_consumer->add_event(any_IV);
    my_consumer->add_event(any_VI);
    my_consumer->add_event(any_VIII);
    my_consumer->add_event(any_X);
    my_consumer->add_event(any_XII);
    my_consumer->add_event(any_XIV);
    my_consumer->add_event(any_XVI);
    my_consumer->add_event(any_XVIII);
    my_consumer->add_event(any_XX);
    my_consumer->add_event(any_XXII);

    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
    my_supplier->new_event(any_XXII);
    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);

    my_supplier->new_event(event_struct);

    while (!my_consumer->finished())
      {
        TIDThr::Thread::sleep(1000);
      }
    if (!my_consumer->ok())
      {
        cerr<<"[test_filter] 13. There are events that must not arrive"<<endl;
        return -1;
      }



    /******************************************************************/
    /*               BORRAMOS TODOS LOS FILTROS                       */
    /******************************************************************/
    consumerAdmin->remove_all_filters();
    /*********************************************************************/
    /*MANDAMOS LOS EVENTOS Y COMPROBAMOS QUE EVENTOS HAN PASADO EL FILTRO*/
    /*********************************************************************/
    my_consumer->new_events(25);
    my_consumer->add_event(event_struct);
    my_consumer->add_event(any_I);
    my_consumer->add_event(any_II);
    my_consumer->add_event(any_III);
    my_consumer->add_event(any_IV);
    my_consumer->add_event(any_V);
    my_consumer->add_event(any_VI);
    my_consumer->add_event(any_VII);
    my_consumer->add_event(any_VIII);
    my_consumer->add_event(any_IX);
    my_consumer->add_event(any_X);
    my_consumer->add_event(any_XI);
    my_consumer->add_event(any_XII);
    my_consumer->add_event(any_XIII);
    my_consumer->add_event(any_XIV);
    my_consumer->add_event(any_XV);
    my_consumer->add_event(any_XVI);
    my_consumer->add_event(any_XVII);
    my_consumer->add_event(any_XVIII);
    my_consumer->add_event(any_XIX);
    my_consumer->add_event(any_XX);
    my_consumer->add_event(any_XXI);
    my_consumer->add_event(any_XXII);
    my_consumer->add_event(any_XXIII);
    my_consumer->add_event(any_XXIV);

    my_supplier->new_event(any_I);
    my_supplier->new_event(any_II);
    my_supplier->new_event(any_III);
    my_supplier->new_event(any_IV);
    my_supplier->new_event(any_V);
    my_supplier->new_event(any_VI);
    my_supplier->new_event(any_VII);
    my_supplier->new_event(any_VIII);
    my_supplier->new_event(any_IX);
    my_supplier->new_event(any_X);
    my_supplier->new_event(any_XI);
    my_supplier->new_event(any_XII);
    my_supplier->new_event(any_XIII);
    my_supplier->new_event(any_XIV);
    my_supplier->new_event(any_XV);
    my_supplier->new_event(any_XVI);
    my_supplier->new_event(any_XVII);
    my_supplier->new_event(any_XVIII);
    my_supplier->new_event(any_XIX);
    my_supplier->new_event(any_XX);
    my_supplier->new_event(any_XXI);
    my_supplier->new_event(any_XXII);
    my_supplier->new_event(any_XXIII);
    my_supplier->new_event(any_XXIV);

    my_supplier->new_event(event_struct);

    while (!my_consumer->finished())
      {
        TIDThr::Thread::sleep(1000);
      }
    if (!my_consumer->ok())
      {
        cerr<<"[test_filter] 14. There are events that must not arrive"<<endl;
        return -1;
      }


   
    printf("OK\n");

    //orb_ptr->run();
    return 0;
    
  }
  catch (CORBA::Exception & e)
    {
      cerr<<"[test_filter] unknown error"<< typeid(e).name() << e._name();
      return -1;
   
    }

}
