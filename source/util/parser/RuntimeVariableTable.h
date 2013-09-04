/*
 *  File name: RuntimeVariableTable.h
 *  File type: Header file.
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

#ifndef _TIDUTIL_PARSER_RUNTIME_VARIABLE_TABLE_H_
#define _TIDUTIL_PARSER_RUNTIME_VARIABLE_TABLE_H_

#include <string>
#include <map>

#include "EvaluableNode.h"
#include "IdentifierValueNode.h"

#ifdef HAVE_STD_NAMESPACE
using namespace std;
#endif

namespace TIDNotif {
namespace util {
namespace parser {
  
class RuntimeVariableTable
{

  public:

    class VariableNotFoundException
    {
      public:

        /* Variable name constructor. */
        VariableNotFoundException(const string & name)
        : m_var_name(name) {}

        /* Return not-found variable name. */
        const string & get_variable_name() const
        {
          return m_var_name;
        }

      private:

        /* Variable name. */
        string m_var_name;

    };

    /* Default constructor. */
    RuntimeVariableTable();

    /* Get evaluable value */
    static EvaluableNode * get_evaluable_value(
      const IdentifierValueNode & var_name) throw (VariableNotFoundException);

  private:

    /* Singleton instance. */
    static RuntimeVariableTable * m_singleton;

    /* Type definition for a map of evaluable nodes. */
    typedef map<string, EvaluableNode*> VariableValues;

    /* Evaliuable nodes for each declared runtime variable. */
    VariableValues m_values;

    /* Initialize a map of variable values with default stuff. */
    static void create_default_variables(VariableValues & var_values);

};

}; /* End of namespace parser. */
}; /* End of namespace util. */
}; /* End of namespace TIDNotif. */

#endif
