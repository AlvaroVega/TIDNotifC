/*
 *  File name: test_grammar.h
 *  File type: Test main program file.
 *  Date : April 2006
 *  Author: Alvaro Polo Valdenebro <apoloval@gsyc.escet.urjc.es>
 */

/*
// (C) Copyright 2009 Telefonica Investigacion y Desarrollo
 *
//     S.A.Unipersonal (Telefonica I+D)
//
// This file is part of Morfeo CORBA Platform.
//
// Morfeo CORBA Platform is free software: you can redistribute it and/or
// modify it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// Morfeo CORBA Platform is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with Morfeo CORBA Platform. If not, see
//
//   http://www.gnu.org/licenses
//
// Info about members and contributors of the MORFEO project
// is available at
//
//   http://morfeo-project.org
 */

/*
 * Revision historial:
 */

#include <iostream>

#include <CORBA.h>

#include "test_data.h"

#include "TIDParser.h"
#include "TypeValuePair.h"
#include "Debugger.h"

using namespace TIDNotif::util::parser;

#ifndef HAVE_STD_NAMESPACE
using namespace std;
#endif

int
main(int argc,char *argv[]) {
  TIDConstraint * constraint;

  /* Statistics*/
  int constraints               = 0;
  int valid_constraints         = 0;
  int invalid_constraints       = 0;
  int success_constraint_checks = 0;
  int error_constraint_checks   = 0;
  int events                    = 0;
  int passed_events             = 0;
  int nonpassed_events          = 0;
  int success_event_checks      = 0;
  int error_event_checks        = 0;

  /* Uncomment (if commented) next line to enable debugging. */
  Debugger::activate_debug(100);
  /* Uncomment (if commented) next line to disable debugging. */
  // Debugger::activate_debug(0);

  for (int i = 0; i < battery_length; i++)
  {
    constraints++;
    if (battery[i].valid_constraint)
      valid_constraints++;
    else
      invalid_constraints++;
    cout << "Checking constraint '" << battery[i].constraint << "': " << endl;
    constraint = NULL;
    try
    {
      cout << "\tParsing constraint... ";
      constraint = TIDParser::parse(battery[i].constraint);
      if (battery[i].valid_constraint)
        cout << "OK (valid constraint)" << endl;
      else
      {
        cout << "ERROR (invalid constraint produces no errors)" << endl;
        error_constraint_checks++;
        Debugger::register_free(constraint);
        delete constraint;
        continue;
      }
    }
    catch (ParsingErrorException & e)
    {
      if (battery[i].valid_constraint)
      {
        error_constraint_checks++;
        cout << "ERROR (valid constraint produces a parsing error)" << endl;
        continue;
      }
      else
        cout << "OK (invalid constraint)" << endl;
    }
    success_constraint_checks++;
    for (int j = 0; j < battery[i].valid_checks; j++)
    {
      events++;
      cout << "\tEvaluating expression with event '" <<
        battery[i].checks[j].event_img << "'... ";
      TypeValuePair evaluation = constraint->evaluate(battery[i].checks[j].event);
      switch (evaluation.get_type())
      {
        case TypeValuePair::BOOLEAN_TYPE:
          if (evaluation.get_value_as_boolean())
            passed_events++;
          else
            nonpassed_events++;
          if (battery[i].checks[j].result == SUCCESS_RESULT &&
              evaluation.get_value_as_boolean())
          {
            success_event_checks++;
            cout << "OK (event passed)" << endl;
          }
          else if (battery[i].checks[j].result == FAIL_RESULT &&
                   !evaluation.get_value_as_boolean())
          {
            success_event_checks++;
            cout << "OK (event not passed)" << endl;
          }
          else
          {
            error_event_checks++;
            cout << "ERROR: evaluation result is not as expected" << endl;
          }
          break;
        case TypeValuePair::ERROR_TYPE:
        default:
          nonpassed_events++;
          if (battery[i].checks[j].result == ERROR_RESULT)
          {
            success_event_checks++;
            cout << "OK (evaluation error)" << endl;
          }
          else
          {
            error_event_checks++;
            cout << "ERROR: evaluation result is not as expected" << endl;
          }
          break;
      }
    }
    cout << "\tDeallocating constraint memory... ";
    if (constraint)
    {
      Debugger::register_free(constraint);
      delete constraint;
      cout << "OK" << endl;
    }
    else
      cout << "OK, memory was not really allocated." << endl;
  }

  /* Report statistics. */
  cout << endl << endl << constraints << " constraints has been parsed:" << endl <<
    "\t" << valid_constraints << " where valid." << endl <<
    "\t" << invalid_constraints << " where invalid." << endl <<
    "\t" << success_constraint_checks << " where correctly parsed." << endl <<
    "\t" << error_constraint_checks << " where uncorrectly parsed." << endl <<
    events << " events has been evaluated:" << endl <<
    "\t" << passed_events << " has passed." << endl <<
    "\t" << nonpassed_events << " has not passed." << endl <<
    "\t" << success_event_checks << " where correctly filtered." << endl <<
    "\t" << error_event_checks << " where uncorrectly filtered." << endl;

  Debugger::report_registered_memory();
  Debugger::deactivate_debug();
  return 0;
}
