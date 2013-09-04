/* JPBOL */


# ifndef _TIDNOTIF_NOTIFICATIONCHANNELDATA_H_
# define _TIDNOTIF_NOTIFICATIONCHANNELDATA_H_

# include <PortableServer/POA.h>
# include <CORBA.h>

# include "FilterFactoryImpl.h"
# include "FilterAdminImpl.h"
# include "CommonData.h"
# include "ConsumerAdminData.h"
# include "SupplierAdminData.h"

namespace TIDNotif
{

	class NotificationChannelData : public CommonData //TODO_MORFEO: java.io.Serializable
	{

		public:
		// Creation Timestamp
		string creation_date;
		string creation_time;
		
		// Default priority anf lifetime.
		int default_priority;
		int default_event_lifetime;
		
		// Modo de operacion
		//OperationMode operation_mode; //transient //TODO_MORFEO: OperationMode
		
		// Estado
		//OperationalState operational_state; //transient  //TODO_MORFEO: OperationalState
		//AdministrativeState administrative_state; //transient //TODO_MORFEO: AdministrativeState
		
		string default_consumer_id; 
		string default_supplier_id;
		
		FilterFactoryImpl* filterFactoryDelegate;
		FilterAdminImpl* filterAdminDelegate;
//		ChannelQoSAdmin* qosAdminDelegate; //TODO_MORFEO: QoS
		
		bool destroying;
		
		
		//Hashtable consumerAdminTable;  transient
		map<int,ConsumerAdminData*> consumerAdminTable;

		// Hashtable supplierAdminTable;  transient
		map<int,SupplierAdminData*> supplierAdminTable;
			
		// Hashtable newConsumerAdminTable;  transient
//		map<int,ConsumerAdminData*> newConsumerAdminTable; //TODO: no la utiliza

		// Hashtable newSupplierAdminTable;  transient
//		map<int,SupplierAdminData*> newSupplierAdminTable; //TODO: no la utiliza

		TIDThr::RecursiveMutex _consumerAdminTableMutex;
		TIDThr::RecursiveMutex _supplierAdminTableMutex;

		//transient public InternalDistributionChannel reference;
		
		
		// NotificationChannelData Constructor
		NotificationChannelData (char* id,
						PortableServer::POA_var poa,
						//OperationMode operation_mode, //TODO_MORFEO: Distribution Notification
						int priority,
						int event_lifetime,
						CORBA::ORB_var orb);


		private:
			static const char* null;

			void writeObject(std::ostream& os);

			void readObject(std::istream& is);

  	};

}; //namespace TIDNotif

#endif
