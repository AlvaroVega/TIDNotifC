/* JPBOL */

# include "NotificationChannelMsg.h"


namespace TIDNotif {

	// POA's Id
	static const char* GLOBAL_SUPPLIER_POA_ID = "TIDGlobalSupplierPOA";

	static const char* LOCAL_SUPPLIER_POA_ID = "TIDLocalSupplierPOA@";

	static const char* SUPPLIER_POA_ID = "TIDSupplierPOA@";

	static const char* GLOBAL_CONSUMER_POA_ID = "TIDGlobalConsumerPOA";

	static const char* LOCAL_CONSUMER_POA_ID = "TIDLocalConsumerPOA@";

	static const char* CONSUMER_POA_ID = "TIDConsumerPOA@";

	static const char* LOCAL_CHANNEL_POA_ID = "TIDLocalChannelPOA@";

	static const char* LOCAL_PROXYPUSHCONSUMER_POA_ID = "LocalProxyPushConsumerPOA@";

	static const char* LOCAL_PROXYPULLCONSUMER_POA_ID = "LocalProxyPullConsumerPOA@";

	static const char* LOCAL_TRANSFORMING_OPERATOR_POA_ID = "LocalTransformingOperator@";

	static const char* LOCAL_SUPPLIER_DISCRIMINATOR_POA_ID = "LocalSupplierDiscriminator@";

	static const char* LOCAL_PROXYPUSHSUPPLIER_POA_ID = "LocalProxyPushSupplierPOA@";

	static const char* LOCAL_PROXYPULLSUPPLIER_POA_ID = "LocalProxyPullSupplierPOA@";

	static const char* LOCAL_CONSUMER_DISCRIMINATOR_POA_ID = "LocalConsumerDiscriminator@";

	static const char* GET_OPERATIONAL_STATE = "-> NotificationChannelImpl.operational_state()";

	static const char* GET_CREATION_DATE = "-> NotificationChannelImpl.creation_date()";

	static const char* GET_CREATION_TIME = "-> NotificationChannelImpl.creation_time()";

	static const char* GET_ADMINISTRATIVE_STATE = "-> NotificationChannelImpl.administrative_state()";

	static const char* SET_ADMINISTRATIVE_STATE = "-> NotificationChannelImpl.administrative_state(value)";

	static const char* GET_OPERATION_MODE = "-> NotificationChannelImpl.operation_mode()";

	static const char* NEW_FOR_CONSUMERS[] = { "-> NotificationChannelImpl.new_for_consumers(): ", "null" };

	static const char* NEW_FOR_SUPPLIERS[] = { "-> NotificationChannelImpl.new_for_suppliers(): ", "null" };

	static const char* NEW_OPERATED_FOR_CONSUMERS = "-> NotificationChannelImpl.new_operated_for_consumers()";

	static const char* NEW_POSITIONED_FOR_CONSUMERS[] = { " +>NotificationChannelImpl.new_positioned_for_consumers(): ", "null",", consumer_id: ","null"," [order: ","null", ", new_order: ","null", "]" };

	static const char* NEW_TRANSFORMED_FOR_SUPPLIERS[] = { " +>NotificationChannelImpl.new_transformed_for_suppliers(): ", "null" };

	static const char* FIND_FOR_CONSUMERS = "-> NotificationChannelImpl.find_for_consumers()";

	static const char* FIND_FOR_SUPPLIERS = "-> NotificationChannelImpl.find_for_supplier()";

	static const char* NEW_FIND_FOR_CONSUMERS = "-> NotificationChannelImpl.new_find_for_consumers()";

	static const char* NEW_FIND_FOR_SUPPLIERS = "-> NotificationChannelImpl.new_find_for_suppliers()";

	static const char* CONSUMER_ADMINS = "-> NotificationChannelImpl.consumer_admins()";

	static const char* SUPPLIER_ADMINS = "-> NotificationChannelImpl.supplier_admins()";

	static const char* CONSUMER_ADMIN_IDS = "-> NotificationChannelImpl.consumer_admin_ids()";

	static const char* SUPPLIER_ADMIN_IDS = "-> NotificationChannelImpl.supplier_admin_ids()";

	static const char* GET_PRIORYTY = "-> NotificationChannelImpl.default_priority()";

	static const char* SET_PRIORYTY = "-> NotificationChannelImpl.default_priority(value)";

	static const char* GET_LIFETIME = "-> NotificationChannelImpl.default_event_lifetime()";

	static const char* SET_LIFETIME = "-> NotificationChannelImpl.default_event_lifetime(value)";

	static const char* FOR_CONSUMERS[] = { "-> NotificationChannelImpl.for_consumers(): ", "null" };

	static const char* FOR_SUPPLIERS[] = { "-> NotificationChannelImpl.for_suppliers(): ", "null" };

	static const char* DESTROY[] = { "-> NotificationChannelImpl.destroy(): ", "null" };

	static const char* DESTROY_CHANNEL[] = { " +>NotificationChannelImpl.destroyChannel(): ", "null" };

	static const char* DESTROY_LOCAL_CHANNEL_POA = " +>NotificationChannelImpl.destroyLocalChannelPOA()";

	static const char* DESTROY_LOCAL_SUPPLIER_POA = " +>NotificationChannelImpl.destroyLocalSupplierPOA()";

	static const char* DESTROY_LOCAL_CONSUMER_POA = " +>NotificationChannelImpl.destroyLocalConsumerPOA()";

	static const char* NEW_CONSUMER_ADMINS = "-> NotificationChannelImpl.new_consumer_admins()";

	static const char* NEW_SUPPLIER_ADMINS = "-> NotificationChannelImpl.new_supplier_admins()";

	static const char* NEW_CONSUMER_ADMIN_IDS = "-> NotificationChannelImpl.new_consumer_admin_ids()";

	static const char* NEW_SUPPLIER_ADMIN_IDS = "-> NotificationChannelImpl.new_supplier_admin_ids()";

	static const char* REMOVE_SUPPLIER_ADMIN = " +>NotificationChannelImpl.removeSupplierAdmin()";

	static const char* REMOVE_NEW_SUPPLIER_ADMIN = " +>NotificationChannelImpl.removeNewSupplierAdmin()";

	static const char* SWAP_SUPPLIER_ADMIN = " +>NotificationChannelImpl.swapSupplierAdmin()";

	static const char* REMOVE_CONSUMER_ADMIN = " +>NotificationChannelImpl.removeConsumerAdmin()";

	static const char* REMOVE_NEW_CONSUMER_ADMIN = " +>NotificationChannelImpl.removeNewConsumerAdmin()";

	static const char* REGISTER[] = { " # NotificationChannelImpl.register() -> ", "null" };

	static const char* UNREGISTER[] = { " # NotificationChannelImpl.unregister() -> ", "null" };

	static const char* B_P__EXIST_ID = "  Criteria Id Already Exist!";

	static const char* B_O__NOT_ALLOWED = "  Not allowed in distribution mode.";

	static const char* LOCKED = "  NotificationChannelImpl: AdministrativeState.locked()";

	static const char* NOT_FOUND = "  # remove New Admin: NOT FOUND";

}; //namespace TIDNotif
