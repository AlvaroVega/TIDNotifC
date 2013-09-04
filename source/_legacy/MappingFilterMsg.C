#include <stdlib.h>
#include "MappingFilterMsg.h"

namespace TIDNotif {
  
  const char* MappingFilterMsg::GET_GRAMMAR =
  "-> MappingDiscriminatorImpl.grammar()";

  const char* MappingFilterMsg::GET_VALUE_TYPE =
  "-> MappingDiscriminatorImpl.value_type()";

  const char* MappingFilterMsg::GET_DEFAULT_VALUE =
  "-> MappingDiscriminatorImpl.default_value()";

  const char* MappingFilterMsg::SET_DEFAULT_VALUE =
  "-> MappingDiscriminatorImpl.default_value(any)";

  const char* MappingFilterMsg::ADD_MAPPING_RULE =
  "-> MappingDiscriminatorImpl.add_mapping_constraint(new_rule, any)";

  const char* MappingFilterMsg::GET_MAPPING_RULE[3] =
    { "-> MappingDiscriminatorImpl.get_mapping_constraint(", NULL, ")" };

  const char* MappingFilterMsg::DELETE_MAPPING_RULE[3] =
    { "-> MappingDiscriminatorImpl.delete_mapping_constraint(", NULL, ")" };

  const char* MappingFilterMsg::DELETE_ALL_MAPPING_RULES =
  "-> MappingDiscriminatorImpl.delete_mapping_constraint()";

  const char* MappingFilterMsg::REPLACE_MAPPING_RULE[5] =
    { "-> MappingDiscriminatorImpl.replace_mapping_constraint(Id: ", 
      NULL, ", <", NULL, ">"};

  const char* MappingFilterMsg::MATCHES[3] =
    { "-> MappingDiscriminatorImpl.matches(", NULL, ")" };

  const char* MappingFilterMsg::MATCH =
  "-> MappingDiscriminatorImpl.match(any, anyholder)";

  const char* MappingFilterMsg::GET_MAPPINGS_RULES =
  "-> MappingDiscriminatorImpl.get_mapping_rules()";

  const char* MappingFilterMsg::REGISTER[2] =
    { " # MappingDiscriminatorImpl.register() -> ", NULL };

  const char* MappingFilterMsg::UNREGISTER[2] =
    { " # MappingDiscriminatorImpl.unregister() -> ", NULL };

  const char* MappingFilterMsg::EXTRACT_LONG =
  "   ERROR: _default_value.type()";

  const char* MappingFilterMsg::TOO_MAPPING_RULES =
  "   ERROR: Numero maximo de mapping rules (constraints) alcanzado.";

  const char* MappingFilterMsg::NEW_CONSTRAINT[4] =
    { " * Constraint: {", NULL, "} - Id = ", NULL };

  const char* MappingFilterMsg::ARBOL = 
  " * Arbol asociado: ";

  const char* MappingFilterMsg::FOUND_MAPPING_RULE[3] =
    { "  Constraint: {", NULL, "}" };

  const char* MappingFilterMsg::NOT_FOUND_MAPPING_RULE = 
  "  Constraint: null";

  const char* MappingFilterMsg::FOUND_ARBOL = 
  "  Arbol asociado: removed!";

  const char* MappingFilterMsg::NOT_FOUND_ARBOL = 
  "  Arbol asociado: NOT FOUND";

  const char* MappingFilterMsg::FOUND_REPLACED_MAPPING_RULE[3] =
    { "  Antigua constraint: {", NULL, "}" };

  const char* MappingFilterMsg::NOT_FOUND_REPLACED_MAPPING_RULE =
  "  Antigua constraint: null";

  const char* MappingFilterMsg::TO_DO_1 =
  " > Creamos un Any con el valor: TODO...";

	 
};//namespace TIDNotif
