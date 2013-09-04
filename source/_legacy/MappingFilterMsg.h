#ifndef _TIDNOTIF_MAPPINGFILTERMSG_H_
#define _TIDNOTIF_MAPPINGFILTERMSG_H_ 


namespace TIDNotif {


class MappingFilterMsg {

public:
  static const char* GET_GRAMMAR;
  
  static const char* GET_VALUE_TYPE;
		   
  static const char* GET_DEFAULT_VALUE;
		   
  static const char* SET_DEFAULT_VALUE;
		   
  static const char* ADD_MAPPING_RULE;
		   
  static const char* GET_MAPPING_RULE[3];
		   
  static const char* DELETE_MAPPING_RULE[3];
		   
  static const char* DELETE_ALL_MAPPING_RULES;
		  
  static const char* REPLACE_MAPPING_RULE[5];
		   
  static const char* MATCHES[3];
		  
  static const char* MATCH;
		  
  static const char* GET_MAPPINGS_RULES;
		  
  static const char* REGISTER[2];
		  
  static const char* UNREGISTER[2];

  static const char* EXTRACT_LONG;
		  
  static const char* TOO_MAPPING_RULES;
		  
  static const char* NEW_CONSTRAINT[4];
		  
  static const char* ARBOL;
  static const char* FOUND_MAPPING_RULE[3];
		  
  static const char* NOT_FOUND_MAPPING_RULE;
  static const char* FOUND_ARBOL;
  static const char* NOT_FOUND_ARBOL;
  static const char* FOUND_REPLACED_MAPPING_RULE[3];
		
  static const char* NOT_FOUND_REPLACED_MAPPING_RULE;
		
  static const char* TO_DO_1;
		
};
			
	 
};//namespace TIDNotif
#endif
