/* JPBOL */

# include "ProxyPushConsumerMsg.h"


namespace TIDNotif {

	static const char* GLOBAL_SUPPLIER_DISCRIMINATOR_POA_ID = "GlobalSupplierDiscriminator";

	static const char* LOCAL_SUPPLIER_DISCRIMINATOR_POA_ID = "LocalSupplierDiscriminator@";

	static const char* SUPPLIER_DISCRIMINATOR_POA_ID = "SupplierDiscriminator@";

	static const char* GLOBAL_TRANSFORMING_OPERATOR_POA_ID = "GlobalTransformingOperator";

	static const char* LOCAL_TRANSFORMING_OPERATOR_POA_ID = "LocalTransformingOperator@";

	static const char* TRANSFORMING_OPERATOR_POA_ID = "TransformingOperator@";


	static const char* GET_OPERATIONAL_STATE = "-> ProxyPushConsumerImpl.operational_state()";

	static const char* GET_ADMINISTRATIVE_STATE = "-> ProxyPushConsumerImpl.administrative_state()";

	static const char* SET_ADMINISTRATIVE_STATE = "-> ProxyPushConsumerImpl.administrative_state(value)";

	static const char* GET_FORWARDING_DISCRIMINATOR = "-> ProxyPushConsumerImpl.forwarding_discriminator()";

	static const char* SET_FORWARDING_DISCRIMINATOR = "-> ProxyPushConsumerImpl.forwarding_discriminator(value)";

	static const char* GET_PUSH_SUPPLIER = "-> ProxyPushConsumerImpl.getPushSupplier()";

	static const char* CONNECT_PUSH_SUPPLIER = "-> ProxyPushConsumerImpl.connect_push_supplier(supplier)";

	static const char* DISCONNECT_PUSH_CONSUMER[] = {"-> ProxyPushConsumerImpl.disconnect_push_consumer(): ","null"," [","null","]"};

	static const char* GET_TRANSFORMING_OPERATOR = "-> ProxyPushConsumerImpl.operator()";

	static const char* SET_TRANSFORMING_OPERATOR = "-> ProxyPushConsumerImpl.operator(value)";

	static const char* GET_EXCEPTION_HANDLER = "-> ProxyPushConsumerImpl.transformator_error_handler()";

	static const char* SET_EXCEPTION_HANDLER = "-> ProxyPushConsumerImpl.transformator_error_handler(handler)";

	static const char* DESTROY_FROM_ADMIN[] = { " +>ProxyPushConsumerImpl.destroyFromAdmin(): ", "null", " [", "null", "]" };

	static const char* DESTROY_DISCRIMINATOR[] = {" +>ProxyPushConsumerImpl.destroyDiscriminator(): ", "null", " [", "null", "]"};

	static const char* DEACTIVATE_DISCRIMINATOR = " +>ProxyPushConsumerImpl.deactivate_discriminator()";

	static const char* REGISTER[] = { " # ProxyPushConsumerImpl.register() -> ", "null" };

	static const char* UNREGISTER[] = { " # ProxyPushConsumerImpl.unregister() -> ", "null" };


	static const char* DISCONNECT_PUSH_SUPPLIER_ERROR = " # ProxyPushConsumerImpl.disconnect_push_supplier(): *** EXCEPTION ***";

	static const char* NO_PROCESSED_EVENTS[] = { "  ProxyPushConsumerImpl.destroyFromAdmin(): NO PROCESSED EVENTS: ","null" };

	static const char* IPUSH_COMM_FAILURE = " # ProxyPushConsumerImpl.ipush(event): org.omg.CORBA.COMM_FAILURE";

	static const char* IPUSH_EXCEPTION = " # ProxyPushConsumerImpl.ipush(event): EXCEPTION";

	static const char* DISCARD_EVENT = "  ProxyPushConsumerImpl.ipush(): DISCARD EVENT";

	static const char* TIME_INFO[] = { ">>>Supplier Request Time = ", "null", " [", "null", "-", "null", "]" };

	static const char* TIME_INFO_2[] = { ">>>Internal Process A Time = ", "null", " [", "null", "-", "null", "]" };

	static const char* TIME_INFO_3[] = 
		{ "\n****************************************************\n",
		"** Num. Processed Events = ", "null", " events.\n",
		"** Average Processing Ratio  = ", "null", " events/seconds.\n",
		"** Average Processing Time  = ", "null", " milliseconds.\n",
		"** Max. Processing Time  = ", "null", " milliseconds.\n",
		"** Total Processing Time = ", "null", " milliseconds.\n",
		"****************************************************" };

	static const char* TIME_INFO_4[] = { ">>>Transformation Time = ", "null" };


	static const char* B_O__NOT_ALLOWED = "  Not allowed in distribution mode.";

	static const char* O_N_EXIST = "  ExceptionHandler: null value.";

	static const char* LOCKED = "  ProxyPushConsumer locked!";

	static const char* NOT_ALLOWED = "  NOT ALLOWED IN NOTIFICATION MODE";

	static const char* NOT_CONNECTED = "  No CONNECTED or DESTROYING!";

	static const char* FLOOD_EVENTS = "  FLOOD Event Reached. sleep().";


	static const char* NARROW_ERROR = " # ProxyPushConsumerImpl: narrow(push_supplier_object)";

}; //namespace TIDNotif
