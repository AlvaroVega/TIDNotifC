/* JPBOL */

# include "ConsumerAdminMsg.h"

namespace TIDNotif {
	// ID's
	static const char* PROXYPUSHSUPPLIER_ID = "ProxyPushSupplier@";
	
	static const char* PROXYPULLSUPPLIER_ID = "ProxyPullSupplier@";
	
	static const char* GLOBAL_CONSUMER_POA_ID = "TIDGlobalConsumerPOA";
	
	static const char* LOCAL_CONSUMER_POA_ID = "TIDLocalConsumerPOA@";
	
	static const char* CONSUMER_POA_ID = "TIDConsumerPOA@";
	
	static const char* GLOBAL_PROXYPUSHSUPPLIER_POA_ID = "GlobalProxyPushSupplierPOA";
	
	static const char* LOCAL_PROXYPUSHSUPPLIER_POA_ID = "LocalProxyPushSupplierPOA@";
	
	static const char* PROXYPUSHSUPPLIER_POA_ID = "ProxyPushSupplierPOA@";

	static const char* GLOBAL_PROXYPULLSUPPLIER_POA_ID = "GlobalProxyPullSupplierPOA";

	static const char* LOCAL_PROXYPULLSUPPLIER_POA_ID = "LocalProxyPullSupplierPOA@";

	static const char* PROXYPULLSUPPLIER_POA_ID = "ProxyPullSupplierPOA@";

	static const char* GLOBAL_CONSUMER_DISCRIMINATOR_POA_ID = "GlobalConsumerDiscriminator";

	static const char* LOCAL_CONSUMER_DISCRIMINATOR_POA_ID = "LocalConsumerDiscriminator@";

	static const char* CONSUMER_DISCRIMINATOR_POA_ID = "ConsumerDiscriminator@";

	static const char* GLOBAL_CONSUMER_INDEXLOCATOR_POA_ID = "GlobalConsumerIndexLocator";

	static const char* LOCAL_CONSUMER_INDEXLOCATOR_POA_ID = "LocalConsumerIndexLocator@";

	static const char* CONSUMER_INDEXLOCATOR_POA_ID = "ConsumerIndexLocator@";

	static const char* GLOBAL_MAPPING_DISCRIMINATOR_POA_ID = "GlobalMappingDiscriminator";

	static const char* LOCAL_MAPPING_DISCRIMINATOR_POA_ID = "GlobalMappingDiscriminator@";

	static const char* MAPPING_DISCRIMINATOR_POA_ID = "MappingDiscriminator@";

	static const char* GET_OPERATIONAL_STATE = "-> ConsumerAdminImpl.operational_state()";

	static const char* GET_ADMINISTRATIVE_STATE = "-> ConsumerAdminImpl.administrative_state()";

	static const char* SET_ADMINISTRATIVE_STATE = "-> ConsumerAdminImpl.administrative_state(value)";

	static const char* GET_ASSOCIATED_CRITERIA = "-> ConsumerAdminImpl.associated_criteria()";

	static const char* GET_EXTENDED_CRITERIA = "-> ConsumerAdminImpl.extended_criteria()";

	static const char* SET_EXTENDED_CRITERIA = "-> ConsumerAdminImpl.extended_criteria(new_criteria)";

	static const char* GET_PRIORITY_DISCRIMINATOR = "-> ConsumerAdminImpl.priority_discriminator()";

	static const char* SET_PRIORITY_DISCRIMINATOR = "-> ConsumerAdminImpl.priority_discriminator(value)";

	static const char* GET_LIFETIME_DISCRIMINATOR = "-> ConsumerAdminImpl.lifetime_discriminator()";

	static const char* SET_LIFETIME_DISCRIMINATOR = "-> ConsumerAdminImpl.lifetime_discriminator(value)";

	static const char* GET_FORWARDING_DISCRIMINATOR = "-> ConsumerAdminImpl.forwarding_discriminator()";

	static const char* SET_FORWARDING_DISCRIMINATOR = "-> ConsumerAdminImpl.forwarding_discriminator(value)";

	static const char* GET_INDEX_LOCATOR = "-> ConsumerAdminImpl.get_index_locator()";

	static const char* SET_INDEX_LOCATOR = "-> ConsumerAdminImpl.set_index_locator()";

	static const char* GET_EXCEPTION_HANDLER = "-> ConsumerAdminImpl.distribution_error_handler()";

	static const char* SET_EXCEPTION_HANDLER = "-> ConsumerAdminImpl.distribution_error_handler(handler)";



	static const char* NEW_FOR_CONSUMERS[] = { "-> ConsumerAdminImpl.new_for_consumers() ", "null" };

	static const char* NEW_POSITIONED_FOR_CONSUMERS[] = { "-> ConsumerAdminImpl.new_positioned_for_consumers() ", "null", " (", "null",")" };

	static const char* FIND_FOR_CONSUMERS = "-> ConsumerAdminImpl.find_for_consumers()";

	static const char* OBTAIN_POSITIONED_FOR_CONSUMERS[] = { "-> ConsumerAdminImpl.obtain_positioned_for_consumers() ", "null" };

	static const char* MOVE_POSITIONED_COSUMER_ADMIN[] = { " +>ConsumerAdminImpl.move_positioned_consumer_admin(): ", "null"," [","null","] * ","null"," -> ","null"," (","null",")" };

	static const char* CONSUMER_ADMINS = "-> ConsumerAdminImpl.consumer_admins()";

	static const char* CONSUMER_ADMIN_IDS = "-> ConsumerAdminImpl.consumer_admin_ids()";

	static const char* DESTROY[] = { "-> ConsumerAdminImpl.destroy(): ", "null", " [", "null", "]" };

	static const char* DESTROY_CONSUMER_ADMIN[] = { " +>ConsumerAdminImpl.destroyConsumerAdmin(): ", "null", " [", "null", "]" };

	static const char* REMOVE_CONSUMER_ADMIN[] = { " +>ConsumerAdminImpl.removeConsumerAdmin(): ", "null" };

	static const char* REMOVE_PROXYPUSHSUPPLIER[] = { " +>ConsumerAdminImpl.removeProxyPushSupplier(): ","null"," [","null","]" };

	static const char* REMOVE_PROXYPULLSUPPLIER[] = { " +>ConsumerAdminImpl.removeProxyPullSupplier(): ","null"," [","null","]" };

	static const char* DESTROY_FROM_CHANNEL[] = { " +>ConsumerAdminImpl.destroyFromChannel(): ", "null", " [", "null", "]" };

	static const char* DESTROY_FROM_ADMIN[] = { " +>ConsumerAdminImpl.destroyFromAdmin(): ", "null", " [", "null", "]" };

	static const char* BASIC_DESTROY[] = { " +>ConsumerAdminImpl.basicDestroy(): ", "null", " [", "null", "]" };

	static const char* TRY_CONSUMERADMIN[] = { "    ConsumerAdminId: ", "null", "  (", "null", ")" };

	static const char* TRY_PROXYPUSHSUPPLIER[] = { "    ProxyPushSupplierId: [", "null", "] order=", "null", " where=", "null" };

	static const char* TRY_PROXYPULLSUPPLIER[] = { "    ProxyPullSupplierId: ", "null", "  (", "null", ")" };



	static const char* OBTAIN_PUSH_SUPPLIER[] = { "-> ConsumerAdminImpl.obtain_push_supplier() ", "null" };

	static const char* OBTAIN_POSITIONED_PUSH_SUPPLIER[] = { "-> ConsumerAdminImpl.obtain_positioned_push_supplier() ", "null" };

	static const char* OBTAIN_NAMED_PUSH_SUPPLIER[] = { "-> ConsumerAdminImpl.obtain_named_push_supplier(", "null", ") for ", "null" };

	static const char* OBTAIN_NAMED_POSITIONED_PUSH_SUPPLIER[] = { "-> ConsumerAdminImpl.obtain_named_positioned_push_supplier() ", "null" };

	static const char* FIND_PUSH_SUPPLIER[] = { "-> ConsumerAdminImpl.find_push_supplier(", "null", ") in ", "null" };

	static const char* MOVE_POSITIONED_PUSH_SUPPLIER[] = { " +>ConsumerAdminImpl.move_positioned_push_supplier(): ", "null"," [","null","] * ","null"," -> ","null"," (","null",")" };

	static const char* PUSH_SUPPLIERS = "-> ConsumerAdminImpl.push_suppliers()";

	static const char* PUSH_SUPPLIER_IDS = "-> ConsumerAdminImpl.push_supplier_ids()";



	static const char* OBTAIN_PULL_SUPPLIER[] = { "-> ConsumerAdminImpl.obtain_pull_supplier() ", "null" };

	static const char* OBTAIN_NAMED_PULL_SUPPLIER[] = { "-> ConsumerAdminImpl.obtain_named_pull_supplier()", "null" };

	static const char* FIND_PULL_SUPPLIER = "-> ConsumerAdminImpl.find_pull_supplier()";

	static const char* OBTAIN_POSITIONED_PULL_SUPPLIER[] = { "-> ConsumerAdminImpl.obtain_positioned_pull_supplier() ", "null" };

	static const char* PULL_SUPPLIERS = "-> ConsumerAdminImpl.pull_suppliers()";

	static const char* PULL_SUPPLIER_IDS = "-> ConsumerAdminImpl.pull_supplier_ids()";

	static const char* CREATE_ANY_VALUE = " # ConsumerAdminImpl.createAnyValue(value): Exception.";


	static const char* NEW_PROXYPUSHSUPPLIER[] = { "* NEW ProxyPushSupplierImpl: ", "null" };

	static const char* NEW_PROXYPULLSUPPLIER[] = { "* NEW ProxyPullSupplierImpl: ", "null" };

	static const char* DESTROY_CONSUMER_POA = " +>ConsumerAdminImpl.destroyConsumerPOA()";

	static const char* REGISTER[] = { " # ConsumerAdminImpl.register() -> ", "null" };

	static const char* UNREGISTER[] = { " # ConsumerAdminImpl.unregister() -> ", "null" };


	static const char* N_P__LOCKED = "  Administrative state: Locked.";

	static const char* B_O__NOT_ALLOWED = "  Not allowed in distribution mode.";

	static const char* B_P__EXIST_ID = "  Criteria Id Already Exist!";

	static const char* NOT_ALLOWED = "  NOT ALLOWED IN NOTIFICATION MODE";

	static const char* O_N_EXIST = "  ExceptionHandler: null value.";

	static const char* LOCKED = "  ConsumerAdmin locked!";

	static const char* DISCARD_EVENT = "  push_event(): DISCARD EVENT";

	static const char* PARENT_NULL = "  ##### PARENT == NULL #####";

	static const char* LOST_EVENT = "  ConsumerAdminImpl.dispatch_event(): lost EVENT.";

	static const char* SENT_TO_HANDLER = "  ConsumerAdminImpl.dispatch_event(): Event sent to handler";

	static const char* HANDLER_ERROR = "  ConsumerAdminImpl.dispatch_event(): exception_handler ERROR";

	static const char* NOT_DELIVERED = "NOT DELIVERED";



	static const char* MSG_ERROR_0 = "  ConsumerAdmin.dispatch_event: pushSupplier LOCKED";

	static const char* MSG_ERROR_1 = "  ConsumerAdmin.dispatch_event: pushSupplier NOT MATCH";

	static const char* MSG_ERROR_2 = "  ConsumerAdmin.dispatch_event: pushSupplier COMM ERROR";

	static const char* MSG_ERROR_3 = "  ConsumerAdmin.dispatch_event: pushSupplier LOST EVENT";

	static const char* MSG_ERROR_4 = "  ConsumerAdmin.deliver_event: pushSupplier ERROR";

	static const char* MSG_ERROR_0B = "  ConsumerAdmin.dispatch_event: consumerAdmin LOCKED";

	static const char* MSG_ERROR_1B = "  ConsumerAdmin.dispatch_event: consumerAdmin NOT MATCH";

	static const char* MSG_ERROR_2B = "  ConsumerAdmin.dispatch_event: consumerAdmin NOT DELIVERED";

	static const char* MSG_ERROR_3B = "  ConsumerAdmin.dispatch_event: consumerAdmin LOST EVENT";

	static const char* MSG_ERROR_4B = "  ConsumerAdmin.deliver_event: consumerAdmin ERROR";

	static const char* MSG_ERROR_5B = "  ConsumerAdmin.deliver_event: ProxyPushSupplier NOT FOUND";

	static const char* MSG_ERROR_6B = "  ConsumerAdmin.deliver_event: consumerAdmin NOT FOUND";



	static const char* MSG_ERROR_00D = "  ConsumerAdmin.deliver_event: default_string_index is NULL";

	static const char* MSG_ERROR_10D[] = { "  ConsumerAdmin.deliver_event: ProxyPushSupplier NOT FOUND (1st round) key=","null" };

	static const char* MSG_ERROR_20D[] = { "  ConsumerAdmin.deliver_event: ProxyPushSupplier NOT FOUND (2st round) key=","null"};

	static const char* MSG_ERROR_11D[] = { "  ConsumerAdmin.deliver_event: pushSupplier LOCKED (1st round) key=", "null" };

	static const char* MSG_ERROR_21D[] = { "  ConsumerAdmin.deliver_event: pushSupplier LOCKED (2st round) key=", "null" };

	static const char* MSG_ERROR_12D[] = { "  ConsumerAdmin.deliver_event: pushSupplier NOT MATCH (1st round) key=", "null" };

	static const char* MSG_ERROR_22D[] = { "  ConsumerAdmin.deliver_event: pushSupplier NOT MATCH (2st round) key=", "null" };

	static const char* MSG_ERROR_13D[] = { "  ConsumerAdmin.deliver_event: pushSupplier COMM ERROR (1st round) key=", "null" };

	static const char* MSG_ERROR_23D[] = { "  ConsumerAdmin.deliver_event: pushSupplier COMM ERROR (2st round) key=", "null" };

	static const char* MSG_ERROR_14D[] = { "  ConsumerAdmin.deliver_event: pushSupplier ERROR (1st round) key=", "null" };

	static const char* MSG_ERROR_24D[] = { "  ConsumerAdmin.deliver_event: pushSupplier ERROR (2st round) key=", "null" };



	static const char* INDX_ERROR_0 = "  ConsumerAdmin.index_locator.get_xxx_index(): ERROR InvalidExpression";

	static const char* INDX_ERROR_1 = "  ConsumerAdmin.index_locator.get_xxx_index(): ERROR FieldNotFound";

	static const char* INDX_ERROR_2 = "  ConsumerAdmin.index_locator.get_xxx_index(): ERROR TypeDoesNotMatch";


	static const char* MSG_ERROR_01 = "  ConsumerAdmin.order(): Already Defined Order";

	static const char* MSG_ERROR_02 = "  ConsumerAdmin.order(): Data Error";

	static const char* MSG_ERROR_03 = "  ConsumerAdmin.order(): Order Not Found";

	static const char* MSG_ERROR_04 = "  ConsumerAdmin.extended_criteria(new_criteria): Invalid Criteria";

	static const char* MSG_ERROR_1C = "  ConsumerAdmin.distrib_event: NOT MATCH";

	static const char* MSG_ERROR_2C = "  ConsumerAdmin.distrib_event: lost EVENT";

	static const char* PPSHS_NOT_FOUND = "  removeProxyPushSupplier(): ProxyPushSupplier ### NOT FOUND ###";

	static const char* PPLLS_NOT_FOUND = "  removeProxyPushSupplier(): ProxyPullSupplier ### NOT FOUND ###";

	static const char* CA_NOT_FOUND = "  removeConsumerAdmin(): ConsumerAdmin ### NOT FOUND ###";


	static const char* DISPATCH_CME = "ConsumerAdminImpl.dispatch_event(): CONCURRENT MODIFICATION EXCEPTION";

	static const char* DELIVER_CME = "ConsumerAdminImpl.deliver_event(): CONCURRENT MODIFICATION EXCEPTION";

}; //namespace TIDNotif
