/*
 *  File name: RuntimeVariableTable.C
 *  File type: Body file.
 *  Date : April 19th 2006
 *  Author: Alvaro Polo Valdenebro <apoloval@gsyc.escet.urjc.es>
 */

/*
// (C) Copyright 2009 Telefonica Investigacion y Desarrollo
 *
//     S.A.Unipersonal (Telefonica I+D)
//
 * by its owner.
 */

/*
 * Revision historial:
 */

#include "RuntimeVariableTable.h"
#include "StructFieldNamePath.h"
#include "VoidPath.h"

namespace TIDNotif {
namespace util {
namespace parser {

/* Singleton instance. */
RuntimeVariableTable *
RuntimeVariableTable::m_singleton = new RuntimeVariableTable();

/* Default constructor. */
RuntimeVariableTable::RuntimeVariableTable()
{
  create_default_variables(m_values);
}

/* Get evaluable value */
EvaluableNode *
RuntimeVariableTable::get_evaluable_value(const IdentifierValueNode & var_name)
throw (RuntimeVariableTable::VariableNotFoundException)
{
  VariableValues::const_iterator it;
  it = m_singleton->m_values.find(var_name.get_name());
  if (it == m_singleton->m_values.end())
    throw VariableNotFoundException(var_name.get_name());
  return m_singleton->m_values[var_name.get_name()]->copy();
}

/* Initialize a map of variable values with default stuff. */
void
RuntimeVariableTable::create_default_variables(VariableValues & var_values)
{
  /* Domain name variable. */
  VoidPath * dn_end = new VoidPath();
  StructFieldNamePath * dn = 
    new StructFieldNamePath(dn_end, "domain_name");
  StructFieldNamePath * dn_event_type = 
    new StructFieldNamePath(dn, "event_type");
  StructFieldNamePath * dn_fixed_header = 
    new StructFieldNamePath(dn_event_type, "fixed_header");
  StructFieldNamePath * dn_header =
    new StructFieldNamePath(dn_fixed_header, "header");
  var_values["domain_name"] = dn_header;

  /* Type name variable. */
  VoidPath * tn_end = new VoidPath();
  StructFieldNamePath * tn = 
    new StructFieldNamePath(tn_end, "type_name");
  StructFieldNamePath * tn_event_type = 
    new StructFieldNamePath(tn, "event_type");
  StructFieldNamePath * tn_fixed_header = 
    new StructFieldNamePath(tn_event_type, "fixed_header");
  StructFieldNamePath * tn_header =
    new StructFieldNamePath(tn_fixed_header, "header");
  var_values["type_name"] = tn_header;

  /* Event name variable. */
  VoidPath * en_end = new VoidPath();
  StructFieldNamePath * en = 
    new StructFieldNamePath(en_end, "event_name");
  StructFieldNamePath * en_event_type = 
    new StructFieldNamePath(en, "event_type");
  StructFieldNamePath * en_fixed_header = 
    new StructFieldNamePath(en_event_type, "fixed_header");
  StructFieldNamePath * en_header =
    new StructFieldNamePath(en_fixed_header, "header");
  var_values["event_name"] = en_header;
}

}; /* End of namespace parser. */
}; /* End of namespace util. */
}; /* End of namespace TIDNotif. */
