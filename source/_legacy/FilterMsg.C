#include "FilterMsg.h"
#include <stdlib.h>

namespace TIDNotif {

  const char * FilterMsg::GET_GRAMMAR =
  "-> DiscriminatorImpl.grammar()";
  
  const char * FilterMsg::ADD_CONSTRAINT =
  "-> DiscriminatorImpl.add_constraint( constraint_exp )";

  const char * FilterMsg::ADD_CONSTRAINTS =
  "-> DiscriminatorImpl.add_constraints( constraint_list )";
  
  const char * FilterMsg::GET_CONSTRAINT[3] =  
    { "-> DiscriminatorImpl.get_constraint(", NULL, ")" };

  const char * FilterMsg::REMOVE_CONSTRAINT[3] = 
    { "-> DiscriminatorImpl.remove_constraint(", NULL, ")" };

  const char * FilterMsg::REMOVE_ALL_CONSTRAINTS = 
  "-> DiscriminatorImpl.remove_constraint()";

  const char * FilterMsg::REPLACE_CONSTRAINT[5] = 
    { "-> DiscriminatorImpl.replace_constraint(Id: ", NULL, ", <", NULL, ">" };

  const char * FilterMsg::EVAL_VALUE = 
  "-> DiscriminatorImpl.eval_value(any)";

  const char * FilterMsg::GET_CONSTRAINTS = 
  "-> DiscriminatorImpl.get_constraints()";

  const char * FilterMsg::REGISTER[2] =   
    { " # DiscriminatorImpl.register() -> ", NULL };

  const char * FilterMsg::UNREGISTER[2] = 
    { " # DiscriminatorImpl.unregister() -> ", NULL };

  const char * FilterMsg::NEW_CONSTRAINT[4] = 
    { "* Constraint: {", NULL, "} - Id = ", NULL };

  const char * FilterMsg::FOUND_CONSTRAINT[3] = 
    { "  Constraint: {", NULL, "}" };

  const char * FilterMsg::FOUND_REPLACED_CONSTRAINT[3] = 
    { "  Antigua constraint: {", NULL, "}" };

  const char * FilterMsg::ARBOL = 
  " * Arbol asociado: ";

  const char * FilterMsg::NOT_FOUND_CONSTRAINT = 
  "  Constraint: null";

  const char * FilterMsg::FOUND_ARBOL = 
  "  Arbol asociado: removed!";

  const char * FilterMsg::NOT_FOUND_ARBOL = 
  "  Arbol asociado: NOT FOUND";

  const char * FilterMsg::NOT_FOUND_REPLACED_CONSTRAINT = 
  "  Antigua constraint: null";

  const char * FilterMsg::TO_MANY_CONSTRAINTS = 
  "  ERROR: Numero maximo de constraints alcanzado.";

	 
};//namespace TIDNotif

