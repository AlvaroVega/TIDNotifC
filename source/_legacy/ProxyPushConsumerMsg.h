/* JPBOL */

# ifndef _TIDNOTIF_PROXYPUSHCONSUMERMSG_H_
# define _TIDNOTIF_PROXYPUSHCONSUMERMSG_H_


namespace TIDNotif {

	class ProxyPushConsumerMsg {
	
		public:
			static const char* GLOBAL_SUPPLIER_DISCRIMINATOR_POA_ID;
	
			static const char* LOCAL_SUPPLIER_DISCRIMINATOR_POA_ID;
	
			static const char* SUPPLIER_DISCRIMINATOR_POA_ID;
	
			static const char* GLOBAL_TRANSFORMING_OPERATOR_POA_ID;
	
			static const char* LOCAL_TRANSFORMING_OPERATOR_POA_ID;
	
			static const char* TRANSFORMING_OPERATOR_POA_ID;
	
	
			static const char* GET_OPERATIONAL_STATE;
	
			static const char* GET_ADMINISTRATIVE_STATE;
	
			static const char* SET_ADMINISTRATIVE_STATE;
	
			static const char* GET_FORWARDING_DISCRIMINATOR;
	
			static const char* SET_FORWARDING_DISCRIMINATOR;
	
			static const char* GET_PUSH_SUPPLIER;
	
			static const char* CONNECT_PUSH_SUPPLIER;
	
			static const char** DISCONNECT_PUSH_CONSUMER;
	
			static const char* GET_TRANSFORMING_OPERATOR;
	
			static const char* SET_TRANSFORMING_OPERATOR;
	
			static const char* GET_EXCEPTION_HANDLER;
	
			static const char* SET_EXCEPTION_HANDLER;
	
			static const char** DESTROY_FROM_ADMIN;
	
			static const char** DESTROY_DISCRIMINATOR;
	
			static const char* DEACTIVATE_DISCRIMINATOR;
	
			static const char** REGISTER;
	
			static const char** UNREGISTER;
	
	
			static const char* DISCONNECT_PUSH_SUPPLIER_ERROR;
	
			static const char** NO_PROCESSED_EVENTS;
	
			static const char* IPUSH_COMM_FAILURE;
	
			static const char* IPUSH_EXCEPTION;
	
			static const char* DISCARD_EVENT;
	
			static const char** TIME_INFO;
	
			static const char** TIME_INFO_2;
	
			static const char** TIME_INFO_3;
	
			static const char** TIME_INFO_4;
	
	
			static const char* B_O__NOT_ALLOWED;
	
			static const char* O_N_EXIST;
	
			static const char* LOCKED;
	
			static const char* NOT_ALLOWED;
	
			static const char* NOT_CONNECTED;
	
			static const char* FLOOD_EVENTS;
	
	
			static const char* NARROW_ERROR;
	};

}; //namespace TIDNotif

# endif
