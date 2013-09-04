/*
 *  File name: TIDParser.C
 *  File type: Body file.
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
 *   - 03/30/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Static member TIDParser::gbl_lexpr_ptr must not be released.
 *   - 03/30/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Useless extern symbol 'new_constraint()' eliminated.
 *   - 03/31/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Exceptions must be throw without new operator.
 *   - 04/07/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * TIDParser::parse(...) will set gbl_lexpr_ptr to NULL 
 *         before parsing begins.
 *       * Static member name 'gbl_lexpr_ptr' changed to 'tmp_constraint'.
 *       * New static member 'tmp_nodes' to store temporally created nodes
 *         to be released in case of syntax errors.
 *       * New function members 'new_tmp_node(EvaluableNode*)',
 *         'clear_tmp_nodes()' and 'free_tmp_nodes()' to manage 'tmp_nodes'.
 *   - 04/10/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * In 'TIDParser::free_tmp_node_stack()', each node delete must
 *         be reported to debugger.
 */

#include "TIDParser.h"
#include "parser.h"
#include "Debugger.h"


extern void yy_scan_string(const char *);
extern int yyparse();

namespace TIDNotif {
namespace util
{
  namespace parser
  {

    ParsingErrorException::ParsingErrorException(const string & msg)
    {
      add_error(msg);
    }

    void
    ParsingErrorException::add_error(const string & msg)
    {
      m_errors.push_back(msg);
    }

    string
    ParsingErrorException::print_to_string() const
    {
      string buff;
      list<string>::const_iterator it;

      for (it = m_errors.begin(); it != m_errors.end(); it++)
      {
        buff.append(*it);
        buff.append("\n");
      }
      return buff;
    }

    const ParsingErrorException &
    ParsingErrorException::operator >> (iostream & stream) const
    {
      stream << print_to_string();
      return *this;
    }

    const int TIDParser::ERROR      = 1;
    const int TIDParser::USER       = 2;
    const int TIDParser::DEBUG      = 3;
    const int TIDParser::DEEP_DEBUG = 4;
    // Id de la gramatica utilizada
    const char * TIDParser::_CONSTRAINT_GRAMMAR = "EXTENDED_TCL";
    // int max value = 2147483647
    const int TIDParser::_MAX_CONSTRAINT_ID = 999999;
    const char * TIDParser::Title = "ConstraintGrammar Parser Version 1.0";
    int TIDParser::_constraintId = 0;
    char * TIDParser::default_constraint = "TRUE";
    TIDConstraint * TIDParser::tmp_constraint = NULL;
    TIDParser::NodePtrStack TIDParser::tmp_node_stack;

    //extern YY_BUFFER_STATE yy_scan_string(yyconst char *yy_str);

    TIDConstraint *
    TIDParser::parse(string new_constraint)
    { //TODO_MORFEO: synchronized
      //TP_PARSE[1] = new_constraint; //TODO_MORFEO: Trace
      //print(DEBUG, TP_PARSE); //TODO_MORFEO: Trace
      TIDParser::tmp_constraint = NULL; /* Reset constraint store. */
      yy_scan_string(new_constraint.c_str());
      if (yyparse())
        throw ParsingErrorException("parsing error");
      return TIDParser::tmp_constraint;
    }

    void TIDParser::push_tmp_node(EvaluableNode * node)
    {
      TIDParser::tmp_node_stack.push(node);
    }

    void TIDParser::pop_tmp_node()
    {
      TIDParser::tmp_node_stack.pop();
    }

    void TIDParser::clear_tmp_node_stack()
    {
      while (!TIDParser::tmp_node_stack.empty())
        TIDParser::pop_tmp_node();
    }

    void TIDParser::free_tmp_node_stack()
    {
      EvaluableNode * node;

      while (!TIDParser::tmp_node_stack.empty())
      {
        node = TIDParser::tmp_node_stack.top();
        Debugger::register_free(node);
        delete node;
        TIDParser::tmp_node_stack.pop();
      }
    }

    int TIDParser::newConstraintId()
    {
      return (++_constraintId % _MAX_CONSTRAINT_ID);
    }

  }; //namespace parser
}; //namespace util
}; //namespace TIDNotif
