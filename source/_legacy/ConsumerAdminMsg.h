/* JPBOL */

# ifndef _TIDNOTIF_CONSUMERADMINMSG_H_
# define _TIDNOTIF_CONSUMERADMINMSG_H_

namespace TIDNotif {

	class ConsumerAdminMsg {
	
		public:
			// ID's
			static const char* PROXYPUSHSUPPLIER_ID;
		
			static const char* PROXYPULLSUPPLIER_ID;
		
			static const char* GLOBAL_CONSUMER_POA_ID;
		
			static const char* LOCAL_CONSUMER_POA_ID;
		
			static const char* CONSUMER_POA_ID;
		
			static const char* GLOBAL_PROXYPUSHSUPPLIER_POA_ID;
		
			static const char* LOCAL_PROXYPUSHSUPPLIER_POA_ID;
		
			static const char* PROXYPUSHSUPPLIER_POA_ID;
		
			static const char* GLOBAL_PROXYPULLSUPPLIER_POA_ID;
		
			static const char* LOCAL_PROXYPULLSUPPLIER_POA_ID;
		
			static const char* PROXYPULLSUPPLIER_POA_ID;
		
			static const char* GLOBAL_CONSUMER_DISCRIMINATOR_POA_ID;
		
			static const char* LOCAL_CONSUMER_DISCRIMINATOR_POA_ID;
		
			static const char* CONSUMER_DISCRIMINATOR_POA_ID;
		
			static const char* GLOBAL_CONSUMER_INDEXLOCATOR_POA_ID;
		
			static const char* LOCAL_CONSUMER_INDEXLOCATOR_POA_ID;
		
			static const char* CONSUMER_INDEXLOCATOR_POA_ID;
		
			static const char* GLOBAL_MAPPING_DISCRIMINATOR_POA_ID;
		
			static const char* LOCAL_MAPPING_DISCRIMINATOR_POA_ID;
		
			static const char* MAPPING_DISCRIMINATOR_POA_ID;
		
			static const char* GET_OPERATIONAL_STATE;
		
			static const char* GET_ADMINISTRATIVE_STATE;
		
			static const char* SET_ADMINISTRATIVE_STATE;
		
			static const char* GET_ASSOCIATED_CRITERIA;
		
			static const char* GET_EXTENDED_CRITERIA;
		
			static const char* SET_EXTENDED_CRITERIA;
		
			static const char* GET_PRIORITY_DISCRIMINATOR;
		
			static const char* SET_PRIORITY_DISCRIMINATOR;
		
			static const char* GET_LIFETIME_DISCRIMINATOR;
		
			static const char* SET_LIFETIME_DISCRIMINATOR;
		
			static const char* GET_FORWARDING_DISCRIMINATOR;
		
			static const char* SET_FORWARDING_DISCRIMINATOR;
		
			static const char* GET_INDEX_LOCATOR;
		
			static const char* SET_INDEX_LOCATOR;
		
			static const char* GET_EXCEPTION_HANDLER;
		
			static const char* SET_EXCEPTION_HANDLER;
		
		
		
			static const char** NEW_FOR_CONSUMERS;
		
			static const char** NEW_POSITIONED_FOR_CONSUMERS;
		
			static const char* FIND_FOR_CONSUMERS;
		
			static const char** OBTAIN_POSITIONED_FOR_CONSUMERS;
		
			static const char** MOVE_POSITIONED_COSUMER_ADMIN;
		
			static const char* CONSUMER_ADMINS;
		
			static const char* CONSUMER_ADMIN_IDS;
		
			static const char** DESTROY;
		
			static const char** DESTROY_CONSUMER_ADMIN;
		
			static const char** REMOVE_CONSUMER_ADMIN;
		
			static const char** REMOVE_PROXYPUSHSUPPLIER;
		
			static const char** REMOVE_PROXYPULLSUPPLIER;
		
			static const char** DESTROY_FROM_CHANNEL;
		
			static const char** DESTROY_FROM_ADMIN;
		
			static const char** BASIC_DESTROY;
		
			static const char** TRY_CONSUMERADMIN;
		
			static const char** TRY_PROXYPUSHSUPPLIER;
		
			static const char** TRY_PROXYPULLSUPPLIER;
		
		
		
			static const char** OBTAIN_PUSH_SUPPLIER;
		
			static const char** OBTAIN_POSITIONED_PUSH_SUPPLIER;
		
			static const char** OBTAIN_NAMED_PUSH_SUPPLIER;
		
			static const char** OBTAIN_NAMED_POSITIONED_PUSH_SUPPLIER;
		
			static const char** FIND_PUSH_SUPPLIER;
		
			static const char** MOVE_POSITIONED_PUSH_SUPPLIER;
		
			static const char* PUSH_SUPPLIERS;
		
			static const char* PUSH_SUPPLIER_IDS;
		
		
		
			static const char** OBTAIN_PULL_SUPPLIER;
		
			static const char** OBTAIN_NAMED_PULL_SUPPLIER;
		
			static const char* FIND_PULL_SUPPLIER;
		
			static const char** OBTAIN_POSITIONED_PULL_SUPPLIER;
		
			static const char* PULL_SUPPLIERS;
		
			static const char* PULL_SUPPLIER_IDS;
		
			static const char* CREATE_ANY_VALUE;
		
		
			static const char** NEW_PROXYPUSHSUPPLIER;
		
			static const char** NEW_PROXYPULLSUPPLIER;
		
			static const char* DESTROY_CONSUMER_POA;
		
			static const char** REGISTER;
		
			static const char** UNREGISTER;
		
		
			static const char* N_P__LOCKED;
		
			static const char* B_O__NOT_ALLOWED;
		
			static const char* B_P__EXIST_ID;
		
			static const char* NOT_ALLOWED;
		
			static const char* O_N_EXIST;
		
			static const char* LOCKED;
		
			static const char* DISCARD_EVENT;
		
			static const char* PARENT_NULL;
		
			static const char* LOST_EVENT;
		
			static const char* SENT_TO_HANDLER;
		
			static const char* HANDLER_ERROR;
		
			static const char* NOT_DELIVERED;
		
		
		
			static const char* MSG_ERROR_0;
		
			static const char* MSG_ERROR_1;
		
			static const char* MSG_ERROR_2;
		
			static const char* MSG_ERROR_3;
		
			static const char* MSG_ERROR_4;
		
			static const char* MSG_ERROR_0B;
		
			static const char* MSG_ERROR_1B;
		
			static const char* MSG_ERROR_2B;
		
			static const char* MSG_ERROR_3B;
		
			static const char* MSG_ERROR_4B;
		
			static const char* MSG_ERROR_5B;
		
			static const char* MSG_ERROR_6B;
		
		
		
			static const char* MSG_ERROR_00D;
		
			static const char** MSG_ERROR_10D;
		
			static const char** MSG_ERROR_20D;
		
			static const char** MSG_ERROR_11D;
		
			static const char** MSG_ERROR_21D;
		
			static const char** MSG_ERROR_12D;
		
			static const char** MSG_ERROR_22D;
		
			static const char** MSG_ERROR_13D;
		
			static const char** MSG_ERROR_23D;
		
			static const char** MSG_ERROR_14D;
		
			static const char** MSG_ERROR_24D;
		
		
		
			static const char* INDX_ERROR_0;
		
			static const char* INDX_ERROR_1;
		
			static const char* INDX_ERROR_2;
		
		
			static const char* MSG_ERROR_01;
		
			static const char* MSG_ERROR_02;
		
			static const char* MSG_ERROR_03;
		
			static const char* MSG_ERROR_04;
		
			static const char* MSG_ERROR_1C;
		
			static const char* MSG_ERROR_2C;
		
			static const char* PPSHS_NOT_FOUND;
		
			static const char* PPLLS_NOT_FOUND;
		
			static const char* CA_NOT_FOUND;
		
		
			static const char* DISPATCH_CME;
		
			static const char* DELIVER_CME;
	};

}; //namespace TIDNotif

# endif
