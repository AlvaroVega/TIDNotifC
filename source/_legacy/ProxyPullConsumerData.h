
#ifndef _TIDNOTIF_PROXYPULLCONSUMERDATA_H_
#define _TIDNOTIF_PROXYPULLCONSUMERDATA_H_ 
#include "CommonData.h"
#include <istream>
#include <ostream>
#ifdef TIDORB_HAVE_NAMESPACE_STD
using namespace std;
#endif
namespace TIDNotif
{

	class ProxyPullConsumerData : public CommonData //TODO_MORFEO: java.io.Serializable
	{
    public:
  		ProxyPullConsumerData();

      void writeObject (ostream& );
	    void readObject (istream& );
	};
		 
};//namespace TIDNotif
#endif
