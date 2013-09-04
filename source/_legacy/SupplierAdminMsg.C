/* JPBOL */

# include "SupplierAdminMsg.h"

namespace TIDNotif {

	static const char* PROXYPUSHCONSUMER_ID = "ProxyPushConsumer@";

	static const char* PROXYPULLCONSUMER_ID = "ProxyPullConsumer@";


	static const char* SUPPLIER_POA_ID = "TIDSupplierPOA@";

	static const char* GLOBAL_PROXYPUSHCONSUMER_POA_ID = "GlobalProxyPushConsumerPOA";

	static const char* LOCAL_PROXYPUSHCONSUMER_POA_ID = "LocalProxyPushConsumerPOA@";

	static const char* PROXYPUSHCONSUMER_POA_ID = "ProxyPushConsumerPOA@";

	static const char* GLOBAL_PROXYPULLCONSUMER_POA_ID = "GlobalProxyPullConsumerPOA";

	static const char* LOCAL_PROXYPULLCONSUMER_POA_ID = "LocalProxyPullConsumerPOA@";

	static const char* PROXYPULLCONSUMER_POA_ID = "ProxyPullConsumerPOA@";

	static const char* GLOBAL_SUPPLIER_DISCRIMINATOR_POA_ID = "GlobalSupplierDiscriminator";

	static const char* LOCAL_SUPPLIER_DISCRIMINATOR_POA_ID = "LocalSupplierDiscriminator@";

	static const char* SUPPLIER_DISCRIMINATOR_POA_ID = "SupplierDiscriminator@";

	static const char* GLOBAL_TRANSFORMING_OPERATOR_POA_ID = "GlobalTransformingOperator";

	static const char* LOCAL_TRANSFORMING_OPERATOR_POA_ID = "LocalTransformingOperator@";

	static const char* TRANSFORMING_OPERATOR_POA_ID = "TransformingOperator@";


	static const char* GET_OPERATIONAL_STATE = "-> SupplierAdminImpl.operational_state()";

	static const char* GET_ADMINISTRATIVE_STATE = "-> SupplierAdminImpl.administrative_state()";

	static const char* SET_ADMINISTRATIVE_STATE = "-> SupplierAdminImpl.administrative_state(value)";

	static const char* GET_ASSOCIATED_CRITERIA = "-> SupplierAdminImpl.associated_criteria()";

	static const char* GET_EXTENDED_CRITERIA = "-> SupplierAdminImpl.extended_criteria()";

	static const char* SET_EXTENDED_CRITERIA = "-> SupplierAdminImpl.extended_criteria(value)";

	static const char* GET_FORWARDING_DISCRIMINATOR = "-> SupplierAdminImpl.forwarding_discriminator()";

	static const char* SET_FORWARDING_DISCRIMINATOR = "-> SupplierAdminImpl.forwarding_discriminator(value)";

	static const char* GET_TRANSFORMING_OPERATOR = "-> SupplierAdminImpl.operator()";

	static const char* SET_TRANSFORMING_OPERATOR = "-> SupplierAdminImpl.operator(value)";


	static const char* OBTAIN_PULL_CONSUMER[] = { "-> SupplierAdminImpl.obtain_pull_consumer(): ", "null" };

	static const char* OBTAIN_PUSH_CONSUMER[] = { "-> SupplierAdminImpl.obtain_push_consumer(): ", "null" };

	static const char* OBTAIN_NAMED_PULL_CONSUMER[] = { "-> SupplierAdminImpl.obtain_named_pull_consumer(): ", "null" };

	static const char* OBTAIN_NAMED_PUSH_CONSUMER[] = {  "-> SupplierAdminImpl.obtain_named_push_consumer(): ", "null" };

	static const char* FIND_PUSH_CONSUMER = "-> SupplierAdminImpl.find_push_consumer(name)";

	static const char* FIND_PULL_CONSUMER = "-> SupplierAdminImpl.find_pull_consumer(name)";

	static const char* NEW_FOR_SUPPLIERS[] = { "-> SupplierAdminImpl.new_for_suppliers() ", "null" };

	static const char* SET_SUPPLIERADMIN_PARENT = " +>SupplierAdminImpl.setSupplierAdminParent(value)";

	static const char* SET_SUPPLIERADMIN_CHILD = " +>SupplierAdminImpl.setSupplierAdminChild(value)";

	static const char* FIND_FOR_SUPPLIERS = "SupplierAdminImpl: find_for_suppliers()";

	static const char* SUPPLIER_ADMINS = "-> SupplierAdminImpl.supplier_admins()";

	static const char* SUPPLIER_ADMIN_IDS = "-> SupplierAdminImpl.supplier_admin_ids()";

	static const char* PULL_CONSUMERS = "-> SupplierAdminImpl.pull_consumers()";

	static const char* PUSH_CONSUMERS = "-> SupplierAdminImpl.push_consumers()";

	static const char* PULL_CONSUMER_IDS = "-> SupplierAdminImpl.pull_consumer_ids()";

	static const char* PUSH_CONSUMER_IDS = "-> SupplierAdminImpl.push_consumer_ids()";

	static const char* GET_EXCEPTION_HANDLER = "-> SupplierAdminImpl.transformator_error_handler()";

	static const char* SET_EXCEPTION_HANDLER = "-> SupplierAdminImpl.transformator_error_handler(handler)";

	static const char* REMOVE[] = { "-> SupplierAdminImpl.remove(): ", "null", " [", "null", "]" };

	static const char* DESTROY[] = { "-> SupplierAdminImpl.destroy(): ", "null", " [", "null", "]" };

	static const char* DESTROY_FROM_CHANNEL[] = { " +>SupplierAdminImpl.destroyFromChannel(): ", "null", " [", "null", "]" };

	static const char* DESTROY_FROM_ADMIN[] = { " +>SupplierAdminImpl.destroyFromAdmin(): ", "null", " [", "null", "]" };

	static const char* BASIC_DESTROY[] = { " +>SupplierAdminImpl.basicDestroy(): ", "null", " [", "null", "]" };

	static const char* DESTROY_SUPPLIER_ADMIN[] = { " +>SupplierAdminImpl.destroySupplierAdmin(): ", "null", " [", "null", "]" };

	static const char* REMOVE_PROXYPUSHCONSUMER[] = { " +>SupplierAdminImpl.removeProxyPushConsumer(", "null", "): [", "null","]" };

	static const char* REMOVE_PROXYPULLCONSUMER[] = { " +>SupplierAdminImpl.removeProxyPullConsumer(", "null", "): [", "null","]" };

	static const char* DESTROY_SUPPLIER_POA = " +>SupplierAdminImpl.destroySupplierPOA()";

	static const char* DEACTIVATE_DISCRIMINATOR = " +>SupplierAdminImpl.deactivate_discriminator_servant()";


	static const char* REGISTER[] = { " # SupplierAdminImpl.register() -> ", "null" };

	static const char* UNREGISTER[] = { " # SupplierAdminImpl.unregister() -> ", "null" };


	static const char* TRY_SUPPLIERADMIN[] = { "  Order: ", "null", " - ConsumerAdmin: ", "null" };

	static const char* DESTROY_FROM_ADMIN_ERROR = "  destroyFromAdmin EXCEPTION.";

	static const char* DISCARD_EVENT = "  push_event(): DISCARD EVENT";

	static const char* DISPATCH_EVENT_LEVEL_ERROR = "SupplierAdminImpl: dispatch_event() Invalid Level";

	static const char* PUSH_EVENT_LEVEL_ERROR = "SupplierAdminImpl: push_event() Invalid Level";

	static const char* INVALID_MODE = "  INVALID_MODE";


	static const char* NOT_ALLOWED = "  NOT ALLOWED IN NOTIFICATION MODE";

	static const char* B_O__NOT_ALLOWED = "Not allowed in distribution mode.";

	static const char* O_N_EXIST = "ExceptionHandler: null value.";

	static const char* B_P__EXIST_ID = "Criteria Id Already Exist!";

	static const char* LOCKED = "SupplierAdmin locked!";

	static const char* MSG_ERROR = "SupplierAdmin.extended_criteria(new_criteria): Invalid Criteria";

}; //namespace TIDNotif
