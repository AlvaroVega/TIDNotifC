/* JPBOL */

# include "ProxyPullConsumerMsg.h"

namespace TIDNotif {

	static const char* GLOBAL_SUPPLIER_DISCRIMINATOR_POA_ID = "GlobalSupplierDiscriminator";

	static const char* LOCAL_SUPPLIER_DISCRIMINATOR_POA_ID = "LocalSupplierDiscriminator@";

	static const char* SUPPLIER_DISCRIMINATOR_POA_ID = "SupplierDiscriminator@";


	static const char* GET_OPERATIONAL_STATE = "-> ProxyPullConsumerImpl.operational_state()";

	static const char* GET_ADMINISTRATIVE_STATE = "-> ProxyPullConsumerImpl.administrative_state()";

	static const char* SET_ADMINISTRATIVE_STATE = "-> ProxyPullConsumerImpl.administrative_state(value)";

	static const char* GET_FORWARDING_DISCRIMINATOR = "-> ProxyPullConsumerImpl.forwarding_discriminator()";

	static const char* SET_FORWARDING_DISCRIMINATOR = "-> ProxyPullConsumerImpl.forwarding_discriminator(value)";

	static const char* GET_PULL_SUPPLIER = "-> ProxyPullConsumerImpl.getPullSupplier()";

	static const char* CONNECT_PULL_SUPPLIER = "-> ProxyPullConsumerImpl.connect_push_supplier(supplier)";

	static const char* DISCONNECT_PULL_CONSUMER[] = {"-> ProxyPullConsumerImpl.disconnect_push_consumer(): ","null"," [","null","]"};

	static const char* DESTROY_FROM_ADMIN[] = { " +>ProxyPullConsumerImpl.destroyFromAdmin(): ", "null", " [", "null", "]" };

	static const char* DEACTIVATE_DISCRIMINATOR = " +>ProxyPullConsumerImpl.deactivate_discriminator()";

	static const char* DISCONNECT_PULL_CONSUMER_ERROR = " # ProxyPullConsumerImpl.destroyFromAdmin(): DISCONNECT_PULL_CONSUMER ERROR";

	static const char* REGISTER[] = { " # ProxyPullConsumerImpl.register() -> ", "null" };

	static const char* UNREGISTER[] = { " # ProxyPullConsumerImpl.unregister() -> ", "null" };


	static const char* TIME_INFO_2[] = { " InternalProxyPullConsumer: Processing Time = ", "null", " [", "null", " - ", "null", "]" };

	static const char* TIME_INFO_3[] =
		{ "\n****************************************************\n",
		"** Num. Processed Events = ", "null", " events.\n",
		"** Average Processing Ratio  = ", "null", " events/seconds.\n",
		"** Average Processing Time  = ", "null", " milliseconds.\n",
		"** Max. Processing Time  = ", "null", " milliseconds.\n",
		"** Total Processing Time = ", "null", " milliseconds.\n",
		"****************************************************" };


	static const char* LOCKED = "  ProxyPullConsumer locked!";

	static const char* NO_PROCESSED_EVENTS[] = { "  ProxyPullConsumerImpl.destroyFromAdmin(): NO PROCESSED EVENTS: ","null" };

	static const char* DISCARD_EVENT = "  ProxyPullConsumerImpl.ipush(): DISCARD EVENT";


	static const char* NARROW_ERROR = " # ProxyPullConsumerImpl: narrow(pull_supplier_object)";

}; //namespace TIDNotif
