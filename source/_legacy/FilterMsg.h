#ifndef _TIDNOTIF_FILTERMSG_H_
#define _TIDNOTIF_FILTERDMSG_H_ 

namespace TIDNotif {
	
class FilterMsg {

 public:

  static const char * GET_GRAMMAR;
  static const char * ADD_CONSTRAINT;
  static const char * ADD_CONSTRAINTS;
  
  static const char * GET_CONSTRAINT[3];
  static const char * REMOVE_CONSTRAINT[3];
  static const char * REMOVE_ALL_CONSTRAINTS;
  static const char * REPLACE_CONSTRAINT[5];
  static const char * EVAL_VALUE;
  static const char * GET_CONSTRAINTS;
  static const char * REGISTER[2];
  static const char * UNREGISTER[2];

  static const char * NEW_CONSTRAINT[4];
  static const char * FOUND_CONSTRAINT[3];
  static const char * FOUND_REPLACED_CONSTRAINT[3];
  static const char * ARBOL;
  static const char * NOT_FOUND_CONSTRAINT;
  static const char * FOUND_ARBOL;
  static const char * NOT_FOUND_ARBOL;
  static const char * NOT_FOUND_REPLACED_CONSTRAINT;
  static const char * TO_MANY_CONSTRAINTS;

 
  };
	
	 
};//namespace TIDNotif
#endif
