
#ifndef _TIDNOTIF_PROXYPULLSUPPLIERDATA_H_
#define _TIDNOTIF_PROXYPULLSUPPLIERDATA_H_ 
#include "CommonData.h"
namespace TIDNotif
{



	class ProxyPullSupplierData : public CommonData //TODO_MORFEO: java.io.Serializable
	{
    public:
  		 ProxyPullSupplierData();

        void writeObject (ostream& );
        void readObject (istream& );
  	};
	
	 
};//namespace TIDNotif
#endif
