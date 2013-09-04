/*
 *  File name: TIDParser.h
 *  File type: Header file.
 *  Date : January 2006
 *  Author: David Alonso <dalonso@gsyc.escet.urjc.es>
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
 *   - 04/07/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Static member name 'gbl_lexpr_ptr' changed to 'tmp_constraint'.
 *       * New static member 'tmp_nodes' to store temporally created nodes
 *         to be released in case of syntax errors.
 *       * New function members 'new_tmp_node(EvaluableNode*)',
 *         'clear_tmp_nodes()' and 'free_tmp_nodes()' to manage 'tmp_nodes'.
 *       * Temporally stored nodes cannot be saved in a list. It's better to
 *         store them in a stack to avoid memory deallocation from 'yyerror()'
 *         and from composed node destructors. For this reason, 'tmp_nodes',
 *         type NodePtrList and it's managment function members are substituted
 *         by a NodePtrStack, 'tmp_node_stack' and some utility function members.
 */

#ifndef _TIDUTIL_TIDPARSER_H_
#define _TIDUTIL_TIDPARSER_H_

#ifndef HAVE_STD_NAMESPACE
using namespace std;
#endif

#include <string>
#include <list>
#include <stack>
#include <iostream>

#include "TIDConstraint.h"

namespace TIDNotif{
namespace util{
namespace parser {

/*!
 * \brief Parsing error exception class.
 */
class ParsingErrorException
{

  public:

    /*!
     * \brief Default constructor.
     */
    ParsingErrorException(const string & msg);

    /*!
     * \brief Add a new error.
     */
    void add_error(const string & msg);

    /*!
     * \brief Print error list to a string.
     */
    string print_to_string() const;

    /*!
     * \brief Extraction operator.
     */
    const ParsingErrorException & operator >> (iostream & stream) const;

  private:

    /*!
     * \brief Error list.
     */
    list<string> m_errors;

};

class TIDParser {

	public:
    
    static const int ERROR;
    static const int USER;
    static const int DEBUG;
    static const int DEEP_DEBUG;
  
    // Id de la gramatica utilizada
  	static const char * _CONSTRAINT_GRAMMAR;

    // int max value = 2147483647
    static const int _MAX_CONSTRAINT_ID;
				
    static TIDConstraint * tmp_constraint;

    typedef stack<EvaluableNode*> NodePtrStack;
    static NodePtrStack tmp_node_stack;

    static void push_tmp_node(EvaluableNode * node);
    static void pop_tmp_node();
    static void clear_tmp_node_stack();
    static void free_tmp_node_stack();

    static TIDConstraint * parse (string new_constraint); //TODO_MORFEO: synchronized
    static int newConstraintId();
  
	private:
    
    static const char * Title;

    static int _constraintId;
  
    static char * default_constraint;
  
};


} /* End of namespace parser.  */
} /* End of namespace util. */
} /* End of namespace TIDNotif. */

#endif
