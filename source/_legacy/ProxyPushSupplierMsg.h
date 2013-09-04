/* JPBOL */

# ifndef TIDNOTIF_PROXYPUSHSUPPLIERMSG_H_
# define TIDNOTIF_PROXYPUSHSUPPLIERMSG_H_


namespace TIDNotif {

	class ProxyPushSupplierMsg {
		
		public:
			static const char* GLOBAL_SUPPLIER_DISCRIMINATOR_POA_ID;
	
			static const char* LOCAL_SUPPLIER_DISCRIMINATOR_POA_ID;
	
			static const char* SUPPLIER_DISCRIMINATOR_POA_ID;
	
	
			static const char* GET_OPERATIONAL_STATE;
	
			static const char* GET_ADMINISTRATIVE_STATE;
	
			static const char* SET_ADMINISTRATIVE_STATE;
	
			static const char* GET_FORWARDING_DISCRIMINATOR;
	
			static const char* SET_FORWARDING_DISCRIMINATOR;
	
			static const char* GET_PUSH_CONSUMER;
	
			static const char** CONNECT_PUSH_CONSUMER;
	
			static const char** DISCONNECT_PUSH_SUPPLIER;
	
			static const char** DESTROY_FROM_ADMIN;
	
			static const char* DISCONNECT_PUSH_CONSUMER_ERROR;
	
			static const char** REGISTER;
	
			static const char** UNREGISTER;
	
	
			static const char** DEACTIVATE_DISCRIMINATOR;
	
	
			static const char* MSG_ERROR_1;
	
			static const char* MSG_ERROR_2;
	
			static const char* MSG_ERROR_3;
	
	
			static const char** LOCKED;
	
			static const char** NOT_CONNECTED3;
	
			static const char** DESTROYING;
	
			static const char** DISCARD_EVENT;
	
			static const char** EVAL_TIME_INFO;
	
	
			static const char** TIME_INFO;
	
			static const char** TIME_INFO_3;
	
			static const char** PUSH_EXCEPTION_1;
	
			static const char** PUSH_EXCEPTION_2;
	
			static const char** AUTO_RESET;
	
			static const char** AUTO_LOCK;
	
			static const char** AUTO_DISCONNECT;
	
			static const char** NO_RESPONSE_EXCEPTION;
	
			static const char** AUTO_RESET2;
	
			static const char** AUTO_LOCK2;
	
			static const char** AUTO_DISCONNECT2;
	
			static const char** AUTO_DISCONNECT3;
	
			static const char* NOT_CONNECTED5;
	
			static const char* EVENT_NOT_MATCH;
	
			static const char* DISTRIB_PUSH_EXCEPTION;
	
	
			static const char* NARROW_ERROR;
	
			static const char** PUSH_EVENT;
	};

}; //namespace TIDNotif

# endif
