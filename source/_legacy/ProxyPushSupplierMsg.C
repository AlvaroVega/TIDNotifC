/* JPBOL */

# include "ProxyPushSupplierMsg.h"

namespace TIDNotif {

	static const char* GLOBAL_SUPPLIER_DISCRIMINATOR_POA_ID = "GlobalSupplierDiscriminator";

	static const char* LOCAL_SUPPLIER_DISCRIMINATOR_POA_ID = "LocalSupplierDiscriminator@";

	static const char* SUPPLIER_DISCRIMINATOR_POA_ID = "SupplierDiscriminator@";


	static const char* GET_OPERATIONAL_STATE = "-> ProxyPushSupplierImpl.operational_state()";

	static const char* GET_ADMINISTRATIVE_STATE = "-> ProxyPushSupplierImpl.administrative_state()";

	static const char* SET_ADMINISTRATIVE_STATE = "-> ProxyPushSupplierImpl.administrative_state(value)";

	static const char* GET_FORWARDING_DISCRIMINATOR = "-> ProxyPushSupplierImpl.forwarding_discriminator()";

	static const char* SET_FORWARDING_DISCRIMINATOR = "-> ProxyPushSupplierImpl.forwarding_discriminator(value)";

	static const char* GET_PUSH_CONSUMER = "-> ProxyPushConsumerImpl.getPushConsumer()";

	static const char* CONNECT_PUSH_CONSUMER[] = { "-> ProxyPushSupplierImpl.connect_push_consumer(", "null", ")"};

	static const char* DISCONNECT_PUSH_SUPPLIER[] = {"-> ProxyPushSupplierImpl.disconnect_push_supplier(): ","null"," [","null","]"};

	static const char* DESTROY_FROM_ADMIN[] = { " +>ProxyPushSupplierImpl.destroyFromAdmin(): ", "null", " [", "null", "]" };

	static const char* DISCONNECT_PUSH_CONSUMER_ERROR = " # ProxyPushSupplierImpl.disconnect_push_consumer(): *** EXCEPTION ***";

	static const char* REGISTER[] = { " # ProxyPushSupplierImpl.register() -> ", "null" };

	static const char* UNREGISTER[] = { " # ProxyPushSupplierImpl.unregister() -> ", "null" };


	static const char* DEACTIVATE_DISCRIMINATOR[] = { "  * deactivate_discriminator: ", "null" };


	static const char* MSG_ERROR_1 = "ProxyPushSupplierImpl.order: AlreadyDefinedOrder";

	static const char* MSG_ERROR_2 = "ProxyPushSupplierImpl.order: DataError";

	static const char* MSG_ERROR_3 = "ProxyPushSupplierImpl.order: OrderNotFound";


	static const char* LOCKED[] = { "   ProxyPushSupplier [", "null", "] LOCKED! (", "null", ")" };

	static const char* NOT_CONNECTED3[] = { "  ProxyPushSupplierImpl.push_event(): DISCARD EVENT, no CONNECTED! [", "null", "] (", "null", ")" };

	static const char* DESTROYING[] = { "  ProxyPushSupplierImpl.push_event(): DISCARD EVENT, DESTROYING! [", "null", "] (", "null", ")" };

	static const char* DISCARD_EVENT[] = {"  ProxyPushSupplierImpl.push_event(): DISCARD EVENT, FALSE CONSTRAINT [", "null", "] (", "null", ")" };

	static const char* EVAL_TIME_INFO[] = { " ### Eval_Value Time = ", "null", " [", "null", "] (", "null", ")" };


	static const char* TIME_INFO[] = { ">>> PushConsumer Time = ", "null", " [", "null", "] (", "null", ")" };

	static const char* TIME_INFO_3[] =
		{ "\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n",
		"++ Num. Scheduled Events = ", "null", " events.\n",
		"++ Average Scheduling Ratio  = ", "null", " events/seconds.\n",
		"++ Average Scheduling Time  = ", "null", " milliseconds.\n",
		"++ Max. Scheduling Time  = ", "null", " milliseconds.\n",
		"++ Total Scheduling Time = ", "null", " milliseconds.\n",
		"++++++++++++++++++++++++++++++++++++++++++++++++++++" };

	static const char* PUSH_EXCEPTION_1[] = { "  ProxyPushSupplierImpl.push_event(): *** EXCEPTION: COMM_FAILURE [", "null", "] (", "null", ") ***" };

	static const char* PUSH_EXCEPTION_2[] = { "  ProxyPushSupplierImpl.push_event(): *** EXCEPTION: DISCONNECTED [", "null", "] (", "null", ") ***" };

	static const char* AUTO_RESET[] = { "  ProxyPushSupplierImpl.push_event(): *** MAX COMM FAILURES RESET [", "null", "] (", "null", ") ***" };

	static const char* AUTO_LOCK[] = { "  ProxyPushSupplierImpl.push_event(): *** MAX COMM FAILURES LOCK [", "null", "] (", "null", ") ***" };

	static const char* AUTO_DISCONNECT[] = { "  ProxyPushSupplierImpl.push_event(): *** MAX COMM FAILURES DISCONNECT [", "null", "] (", "null", ") ***" };

	static const char* NO_RESPONSE_EXCEPTION[] = { "  ProxyPushSupplierImpl.push_event(): *** EXCEPTION: NO_RESPONSE [", "null", "] (", "null", ") ***" };

	static const char* AUTO_RESET2[] = { "  ProxyPushSupplierImpl.push_event(): *** MAX NO RESPONSE RESET [", "null", "] (", "null", ") ***" };

	static const char* AUTO_LOCK2[] = { "  ProxyPushSupplierImpl.push_event(): *** MAX NO RESPONSE LOCK [", "null", "] (", "null", ") ***" };

	static const char* AUTO_DISCONNECT2[] = { "  ProxyPushSupplierImpl.push_event(): *** MAX NO RESPONSE DISCONNECT [", "null", "] (", "null", ") ***" };

	static const char* AUTO_DISCONNECT3[] = { "  ProxyPushSupplierImpl.push_event(): *** MAX DISCONNECTED TIME DISCONNECT [", "null", "] (", "null", ") ***" };

	static const char* NOT_CONNECTED5 = "  ProxyPushSupplierImpl.distrib_event(): No CONNECTED!";

	static const char* EVENT_NOT_MATCH = "  ProxyPushSupplierImpl.distrib_event(): EVENT NOT MATCH";

	static const char* DISTRIB_PUSH_EXCEPTION = "  ProxyPushSupplierImpl.idstrib_event(): Connetion EXCEPTION.";


	static const char* NARROW_ERROR = " # ProxyPushSupplierImpl: narrow(push_consumer_object)";

	static const char* PUSH_EVENT[] = { " +>ProxyPushSupplierImpl.push_event() [", "null", "] (", "null", ")" };

}; //namespace TIDNotif
