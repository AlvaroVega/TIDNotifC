#ifndef _TIDNOTIF_THEPOAFACTORYMSG_H_
#define _TIDNOTIF_THEPOAFACTORYMSG_H_ 

namespace TIDNotif { 

class ThePOAFactoryMsg 
{
public:
  static const char* CREATE_GLOBAL_POA[2];
    
  static const char* CREATE_LOCAL_POA[2];
   
  static const char* CREATE_EXCLUSIVE_POA[2];
   
  static const char* CONFIG_GLOBAL_POA[6];
   
  static const char* CONFIG_LOCAL_POA[6];
   
  static const char* CONFIG_EXCLUSIVE_POA[6];
   
  static const char* ACTIVATE_GLOBAL_POA; 
   
  static const char* ACTIVATE_LOCAL_POA; 
   
  static const char* ACTIVATE_EXCLUSIVE_POA; 
   
  static const char* DESTROY[2]; 
   
  static const char* ERROR_POA[2];
  
  static const char* EXCEPTION_POA;
  
  static const char* POA_EXIST;

  // NUEVO
  static const char* NEW_POA[2]; 
  
  static const char* POA_INFO_1[3]; 
  
  static const char* POA_INFO_2[2]; 
  
  static const char* POA_INFO_3[2]; 
  
  static const char* POA_INFO_4[6];
  
		
	
};
}; //namespace TIDNotif
#endif
