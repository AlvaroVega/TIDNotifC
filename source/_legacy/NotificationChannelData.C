/* JPBOL */

# include <TIDThr/Synchronized.h>

#include "NotificationChannelData.h"

namespace TIDNotif
{

	static const char* null = "";

	// NotificationChannelData Constructor
	NotificationChannelData::NotificationChannelData (char* id,
											PortableServer::POA_var poa,
											//OperationMode operation_mode, //TODO_MORFEO: Distribution Notification
											int priority,
											int event_lifetime,
											CORBA::ORB_var orb):CommonData(id,poa)
	{

		// Modo de operación
//              this->operation_mode = operation_mode;  //TODO_MORFEO: OperationMode

		// setting the priority and lifetime
		this->default_priority = priority;
		this->default_event_lifetime = event_lifetime;


		//TODO_MORFEO
		int date = time(NULL);
//              java.util.Date date = new java.util.Date(System.currentTimeMillis());
//              creation_date = NotifDateFormat.DATE_FORMAT.format(date);
//              creation_time = NotifDateFormat.TIME_FORMAT.format(date);

		// Init Operational and Administrative States
//              operational_state = OperationalState.enabled;
//              administrative_state = AdministrativeState.unlocked;

		// Id's de los default ConsumerAdmin y SupplierAdmin
		this->default_consumer_id = "";
		this->default_supplier_id = "";

		//TODO_MORFEO: resolver las referencias de los metodos virtuales puros de las clases FilterAdminImpl y FilterFactoryImpl
  		filterAdminDelegate = new FilterAdminImpl();
  		filterFactoryDelegate = new FilterFactoryImpl(orb);

//		this->qosAdminDelegate = new ChannelQoSAdmin(orb);  //TODO_MORFEO: QoS

//              reference = NotifReference::internalChannelReference(poa, id, qosAdminDelegate->getPolicies());  //TODO_MORFEO: QoS

		this->destroying = false;
	}


	/// WRITEOBJECT
	void NotificationChannelData::writeObject (std::ostream& os)  //TODO_MORFEO: throws IOException
	{
		//os.defaultWriteObject();
		os << creation_date << endl;
		os << creation_time << endl;
		os << default_priority << endl;
		os << default_event_lifetime << endl;
		os << default_consumer_id << endl;
		os << default_supplier_id << endl;
		os << destroying << endl;

		//TODO_MORFEO: OperationMode
// 		os.writeInt(operation_mode.value());  //TODO_MORFEO: ObjectOutputStream
// 		os.writeInt(operational_state.value());  //TODO_MORFEO: ObjectOutputStream
// 		os.writeInt(administrative_state.value());  //TODO_MORFEO: ObjectOutputStream
		
		//os.writeObject(consumerAdminTable.ids()); comentado en el codigo de java

		//Escritura de los objetos almacenados en consumerAdminTable
		TIDThr::Synchronized synchronized_consumerTable(_consumerAdminTableMutex);
		{
			os << consumerAdminTable.size();
			map<int,ConsumerAdminData*>::iterator iter_cat;  //Iterador de ConsumerAdminTable
			for (iter_cat = consumerAdminTable.begin(); iter_cat!= consumerAdminTable.end(); iter_cat++) {
				os << iter_cat->first << endl;
				iter_cat->second->writeObject(os);
			}
		}

		//Escritura de los objetos almacenados en supplierAdminTable
		TIDThr::Synchronized synchronized_supplierTable(_supplierAdminTableMutex);
		{
			os << supplierAdminTable.size();
			map<int,SupplierAdminData*>::iterator iter_sat;  //Iterador de SupplierAdminTable
			for (iter_sat = supplierAdminTable.begin(); iter_sat!= supplierAdminTable.end(); iter_sat++) {
				os << iter_sat->first << endl;
				iter_sat->second->writeObject(os);
			}
		}
	}


	///READOBJECT
	void NotificationChannelData::readObject (std::istream& is)
	{
		//is.defaultReadObject();  //TODO_MORFEO: ObjectInputStream
		is >> creation_date;
		is >> creation_time;
		is >> default_priority;
		is >> default_event_lifetime;
		is >> default_consumer_id;
		is >> default_supplier_id;
		is >> destroying;

		
//		this->qosAdminDelegate->setORB(PersistenceManager._orb);  //TODO_MORFEO: QoS
		
		//TODO_MORFEO: OperationMode
// 		operation_mode = OperationMode.from_int(is.readInt());
// 		operational_state = OperationalState.from_int(is.readInt());
// 		administrative_state = AdministrativeState.from_int(is.readInt());

		//Lectura de los objetos ConsumerAdmin
		int size;
		int consumer_id;  ///TODO:Depende de lo que metas dentro del map para identificar al objeto
		ConsumerAdminData* consumer_admin = new ConsumerAdminData();
		is >> size;
		for (int i=0; i<=size ; i++)
		{
			is >> consumer_id;
			consumer_admin->readObject(is);
			consumerAdminTable[consumer_id]=consumer_admin;
		}
		
		//Lectura de los objectos SupplierAdmin
		int supplier_id;   ///TODO:Depende de lo que metas dentro del map para identificar al objeto
		SupplierAdminData* supplier_admin = new SupplierAdminData();
		is >> size;
		for (int i=0; i<=size ; i++)
		{
			is >> supplier_id;
			supplier_admin->readObject(is);
			supplierAdminTable[supplier_id]=supplier_admin;
		}
	}
}; //namespace TIDNotif
