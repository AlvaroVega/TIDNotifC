#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <CORBA.h>
#include <CORBA/StructDef.h>
#include <CORBA/StructMember.h>

#include "EvaluableNode.h"
#include "TypeValuePair.h"
#include "TIDParser.h"
#include "Debugger.h"
#include "parser.h"

#ifdef HAVE_STD_NAMESPACE
using namespace std;
#endif

namespace TIDNotif {
namespace util {
namespace parser {
  extern void new_constraint();
  extern EvaluableNode* tmp_constraint;
}
}
}

extern int  yyparse();
extern void yy_scan_string(const char *);

using namespace TIDNotif::util::parser;

DynamicAny::DynAnyFactory_ptr dynAnyFactory = NULL;
CORBA::ORB_var orb;

/* Locate DynAnyFactory reference. */
void
locateDynAnyFactory()
{
  char ** args;
  int i;
  const char * orb_id;
  CORBA::Object_ptr obj;

  if (dynAnyFactory == NULL)
  {
    try
    {
      i = 0;
      orb_id="TIDConstraint";
      orb = CORBA::ORB_init(i,args,orb_id);
    }
    catch (CORBA::Exception& e)
    {}

    try
    {
      obj =  orb->resolve_initial_references("DynAnyFactory");
      dynAnyFactory = DynamicAny::_DynAnyFactoryHelper::narrow(obj,true);
    }
    catch (CORBA::Exception& e)
    {}
  }
}

char * constraints[] =
{
  "$",
  "$ and TRUE",
  "$ or TRUE",
  "$ and FALSE",
  "$ + 7 < 12",
  "$ + 7 < 12",
  "$ + 7 < 12",
  "$ + 7 < 12 or $ < 10",
  "$ + 7 < 12 or $ < 10 and $ + 12 * 23.3 > 123.456",
  "$.value < 15",
  "$.foo_member < 15"
};

bool expected_result[] =
{
  true,
  true,
  true,
  false,
  true,
  true,
  false,
  true,
  true,
  true,
  false
};

DynamicAny::DynAny_var events[sizeof(constraints)/sizeof(char*)];

DynamicAny::DynAny_ptr
create_struct(const char * id,
              const char * name,
              const char * field_names[],
              const CORBA::TypeCode_var field_types[],
              unsigned long field_count)
{
  CORBA::StructMemberSeq * members;
  CORBA::StructMember * smv;
  CORBA::StructDef * sd;
  CORBA::Any a;
  int i;

  cerr << "Creating dynamic any struct." << endl;
  members = new CORBA::StructMemberSeq();
  members->length(field_count);
  for (i = 0; i < field_count; i++)
  {
    cerr << "Building member #" << i << endl;
    (*members)[i].name = (::CORBA::Identifier) CORBA::string_dup(field_names[i]);
    (*members)[i].type = field_types[i];
    (*members)[i].type_def = CORBA::IDLType::_nil();
    cerr << "Member named " << field_names[i] << " created." << endl;
  }

  return dynAnyFactory->create_dyn_any_from_type_code(
    TIDorb::portable::TypeCodeFactory::create_struct_tc(
      (const ::CORBA::RepositoryId) id,
      (const ::CORBA::Identifier) name, 
      members));
}

main(int argc,char *argv[]) {
  int i;
  CORBA::Any true_any;
  CORBA::Any false_any;
  CORBA::Any one_any;
  CORBA::Any three_any;
  CORBA::Any five_any;

  /* Activate debugging. */
  Debugger::activate_debug(100);
  //Debugger::activate_debug(0);
  locateDynAnyFactory();

  true_any.delegate().insert_boolean(true);
  false_any.delegate().insert_boolean(false);
  one_any.delegate().insert_long(1);
  three_any.delegate().insert_long(3);
  five_any.delegate().insert_long(5);

  events[0] = dynAnyFactory->create_dyn_any(true_any);
  events[1] = dynAnyFactory->create_dyn_any(true_any);
  events[2] = dynAnyFactory->create_dyn_any(true_any);
  events[3] = dynAnyFactory->create_dyn_any(true_any);
  events[4] = dynAnyFactory->create_dyn_any(one_any);
  events[5] = dynAnyFactory->create_dyn_any(three_any);
  events[6] = dynAnyFactory->create_dyn_any(five_any);
  events[7] = dynAnyFactory->create_dyn_any(five_any);
  events[8] = dynAnyFactory->create_dyn_any(five_any);

  const char* struct1_names[] = {"value"};
  CORBA::TypeCode_var struct1_types[] =
  {
    TIDorb::portable::TypeCodeFactory::get_basic_TypeCode(::CORBA::tk_long)
  };
  events[9] = create_struct("IDL:SimpleStruct1:1.0",
                            "SimpleStruct1",
                            struct1_names,
                            struct1_types,
                            1);

  const char* struct2_names[] = {"value1", "value2"};
  CORBA::TypeCode_var struct2_types[] =
  {
    TIDorb::portable::TypeCodeFactory::get_basic_TypeCode(::CORBA::tk_long),
    TIDorb::portable::TypeCodeFactory::get_basic_TypeCode(::CORBA::tk_long)
  };
  events[10] = create_struct("IDL:SimpleStruct2:1.0",
                            "SimpleStruct2",
                            struct2_names,
                            struct2_types,
                            1);

  for (i=0; i<sizeof(constraints)/sizeof(char*); i++)
  {
    if (!events[i].in())
    {
      printf("ERROR: dyn any not created!!!\n");
      return -1;
    }

    printf("Parsing constraint '%s'\n", constraints[i]);
    yy_scan_string(constraints[i]);
    if (yyparse())
    {
      printf("Parsing error: grammar is incorrect\n");
      Debugger::report_registered_memory();
      return -1;
    };
    printf("File is parsed successfully. Trying to check event value\n");
    try {
      TypeValuePair value = TIDParser::tmp_constraint->evaluate(events[i]);
      if (value.get_type() == TypeValuePair::ERROR_TYPE) {
        printf("Error in grammar:\n");
        printf("%s\n", value.get_value_as_error().c_str());
        Debugger::register_free(TIDParser::tmp_constraint);
        delete TIDParser::tmp_constraint;
        Debugger::report_registered_memory();
        return -1;
      }
      else if (value.get_type() == TypeValuePair::BOOLEAN_TYPE) {
        if (value.get_value_as_boolean())
        {
          if (expected_result[i])
            printf("Correct filter passed: OK\n");
          else
          {
            printf("Incorrect filter passed: ERROR\n");
            Debugger::register_free(TIDParser::tmp_constraint);
            delete TIDParser::tmp_constraint;
            Debugger::report_registered_memory();
            return -1;
          }
        }
        else
        {
          if (expected_result[i])
          {
            printf("Correct filter not passed: ERROR\n");
            Debugger::register_free(TIDParser::tmp_constraint);
            delete TIDParser::tmp_constraint;
            Debugger::report_registered_memory();
            return -1;
          }
          else
            printf("Incorrect filter not passed: OK\n");
        }
	
      }
      else {
        printf("it's no bool\n");
      }
    }
    catch(CORBA::NO_IMPLEMENT& e){
      printf("No implement");
    }
    Debugger::register_free(TIDParser::tmp_constraint);
    delete TIDParser::tmp_constraint;
  }

  cout << "Releasing memory... ";
  try
  {
    CORBA::release(dynAnyFactory);
    CORBA::release(orb);
    cout << "OK" << endl;
  }
  catch (...)
  {
    cout << "error" << endl;
    return -1;
  }
  Debugger::report_registered_memory();
  
  return 0;
}
