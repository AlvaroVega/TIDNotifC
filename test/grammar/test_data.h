/*
 *  File name: test_data.h
 *  File type: Test header file.
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

#ifndef __GRAMAR_TEST_DATA_H
#define __GRAMAR_TEST_DATA_H

#include <DynamicAny.h>

#include "test_utils.h"

#define CHECK_COUNT 8

TestUtils::StructMember multivalue_struct_members[] =
{
  TestUtils::create_boolean_struct_member("true_bool_value", true),
  TestUtils::create_boolean_struct_member("false_bool_value", false),
};

DynamicAny::DynAny_ptr multivalue_struct =
TestUtils::create_dynstruct(multivalue_struct_members, 
                            sizeof(multivalue_struct_members)/
                              sizeof(TestUtils::StructMember));


TestUtils::UnionMember bool_union_members[] =
{
  TestUtils::create_long_union_member(
    "long_value", 7, TestUtils::create_boolean_label(true)),
  TestUtils::create_double_union_member(
    "double_value", 7.0, TestUtils::create_boolean_label(false)),
};



DynamicAny::DynAny_ptr bool_union =
TestUtils::create_dynunion(TestUtils::get_basic_tc(TestUtils::BOOLEAN_TC),
                           bool_union_members, 
                           sizeof(bool_union_members)/
                             sizeof(TestUtils::UnionMember));

DynamicAny::DynAny_ptr true_dynany =
  TestUtils::create_dynbool(true);

CORBA::Any * true_any = true_dynany->to_any();

CosNotification::StructuredEvent *
structured_true = TestUtils::create_structured_event(
  "GSyC", "test", "true", *true_any);

DynamicAny::DynAny_ptr dynany_structured_true =
  TestUtils::structured_event_to_dynany(*structured_true);

typedef enum ResultType
{
  SUCCESS_RESULT,
  FAIL_RESULT,
  ERROR_RESULT
};

typedef struct
{
  DynamicAny::DynAny_ptr event;
  char event_img[64];
  ResultType result;
} BatteryCheck;

typedef struct
{
  const char constraint[255];
  bool valid_constraint;
  int valid_checks;
  BatteryCheck checks[CHECK_COUNT];
} BatteryItem;

BatteryItem battery[] =
{
  /* Simple boolean values. */
  {
    "TRUE",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "FALSE",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },

  /* Simple boolean expressions. */
  {
    "TRUE and TRUE",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}},
  },
  {
    "TRUE and FALSE",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}},
  },
  {
    "FALSE and TRUE",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}},
  },
  {
    "FALSE and FALSE",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}},
  },
  {
    "TRUE or TRUE",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}},
  },
  {
    "TRUE or FALSE",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}},
  },
  {
    "FALSE or TRUE",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}},
  },
  {
    "FALSE or FALSE",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}},
  },

  /* More complex boolean expressions. */
  {
    "TRUE and TRUE and TRUE",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}},
  },
  {
    "TRUE and TRUE and FALSE",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}},
  },
  {
    "FALSE and FALSE and FALSE",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}},
  },
  {
    "FALSE or TRUE and TRUE",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}},
  },
  {
    "FALSE or TRUE and FALSE",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}},
  },
  {
    "FALSE and TRUE or TRUE and FALSE",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}},
  },
  {
    "(FALSE or TRUE) and TRUE",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}},
  },
  {
    "(TRUE or FALSE) and (TRUE or FALSE)",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },

  /* Simple relational expressions. */
  {
    "7 == 7",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "7 == 10",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },
  {
    "7 != 10",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "7 != 7",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },
  {
    "7 == 7.0",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "7.0 == 10",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },
  {
    "7.0 != 10.0",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "7.0 != 7",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },
  {
    "7 < 10",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "7 > 10",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },
  {
    "7 < 10.0",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "7.0 > 10",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },
  {
    "7 <= 7",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "7 >= 7",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "7.0 <= 10.0",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "7 < TRUE",
    true,
    1,
    {{NULL, "null", ERROR_RESULT}}
  },
  {
    "7.0 == FALSE",
    true,
    1,
    {{NULL, "null", ERROR_RESULT}}
  },

  /* More complex relational expressions. */
  {
    "7 < 10 and 10 > 7",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "10.0 == 10 and 7 == 7.0",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "7 != 7.0 or 4 > 5.0",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },
  {
    "900 < 90 and TRUE",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },

  /* Extreme values. */
  {
    "65535 == 65535.0",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "65536.0 == 65536",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "70000 < 69999.9",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },
  {
    "2147483647 == 2147483647.0",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "2147483648.0 == 2147483648",
    false,
    0,
    {}
  },
  {
    "-2147483646 == -2147483646.0",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "-2147483647.0 == -2147483647",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "-2147483648.0 == -2147483648",
    false,
    0,
    {}
  },
  {
    "2147483648.0 == 2147483690",
    false,
    0,
    {}
  },

  /* Simple arithmetic expressions. */
  {
    "4 + 3 <= 7",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "4 + 3.0 < 7",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },
  {
    "4.0 * 3 == 12.0",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "4.0 * 3 == 12",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "7.0 / 0 == 7",
    true,
    1,
    {{NULL, "null", ERROR_RESULT}}
  },
  {
    "15.0 + 30.0 / 2 > 0",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },

  /* String-related expressions. */
  {
    "'david' == 'david'",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "'david' == 'mary'",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },
  {
    "'david' == 'David'",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },
  {
    "'david' != 'david'",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },
  {
    "'david' < 'mary'",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "'mary' > 'david'",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "'david' ~ 'david john lisa'",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "'mary' ~ 'david john lisa'",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },

  /* TID defined 'in' for string expressions. */
  {
    "'david' in ('david', 'john', 'lisa')",
    true,
    1,
    {{NULL, "null", SUCCESS_RESULT}}
  },
  {
    "'mary' in ('david', 'john', 'lisa')",
    true,
    1,
    {{NULL, "null", FAIL_RESULT}}
  },

  /* Simple event access expressions. */
  {
    "$",
    true,
    5,
    {
      {TestUtils::create_dynbool(true), "true dynany", SUCCESS_RESULT},
      {TestUtils::create_dynbool(false), "false dynany", FAIL_RESULT},
      {TestUtils::create_dynlong(7), "7 dynany", ERROR_RESULT},
      {TestUtils::create_dyndouble(7.0), "7.0 dynany", ERROR_RESULT},
      {TestUtils::create_dynstring("7.0"), "'7.0' (string) dynany", ERROR_RESULT},
    }
  },
  {
    "$ and TRUE",
    true,
    5,
    {
      {TestUtils::create_dynbool(true), "true dynany", SUCCESS_RESULT},
      {TestUtils::create_dynbool(false), "false dynany", FAIL_RESULT},
      {TestUtils::create_dynlong(7), "7 dynany", ERROR_RESULT},
      {TestUtils::create_dyndouble(7.0), "7.0 dynany", ERROR_RESULT},
      {TestUtils::create_dynstring("7.0"), "'7.0' (string) dynany", ERROR_RESULT},
    }
  },
  {
    "$ and FALSE",
    true,
    5,
    {
      {TestUtils::create_dynbool(true), "true dynany", FAIL_RESULT},
      {TestUtils::create_dynbool(false), "false dynany", FAIL_RESULT},
      {TestUtils::create_dynlong(7), "7 dynany", ERROR_RESULT},
      {TestUtils::create_dyndouble(7.0), "7.0 dynany", ERROR_RESULT},
      {TestUtils::create_dynstring("7.0"), "'7.0' (string) dynany", ERROR_RESULT},
    }
  },
  {
    "$ + 15 < 20.0",
    true,
    5,
    {
      {TestUtils::create_dynbool(true), "true dynany", ERROR_RESULT},
      {TestUtils::create_dynbool(false), "false dynany", ERROR_RESULT},
      {TestUtils::create_dynlong(7), "7 dynany", FAIL_RESULT},
      {TestUtils::create_dyndouble(4.0), "4.0 dynany", SUCCESS_RESULT},
      {TestUtils::create_dynstring("7.0"), "'7.0' (string) dynany", ERROR_RESULT},
    }
  },
  {
    "$ ~ 'thomas david michael john'",
    true,
    8,
    {
      {TestUtils::create_dynbool(true), "true dynany", ERROR_RESULT},
      {TestUtils::create_dynbool(false), "false dynany", ERROR_RESULT},
      {TestUtils::create_dynlong(7), "7 dynany", ERROR_RESULT},
      {TestUtils::create_dyndouble(7.0), "7.0 dynany", ERROR_RESULT},
      {TestUtils::create_dynstring("david"), "'david' (string) dynany", SUCCESS_RESULT},
      {TestUtils::create_dynstring("hugh"), "'david' (string) dynany", FAIL_RESULT},
      {TestUtils::create_dynstring("john"), "'david' (string) dynany", SUCCESS_RESULT},
      {TestUtils::create_dynstring("sarah"), "'david' (string) dynany", FAIL_RESULT},
    }
  },
  {
    "$ in ('thomas', 'david', 'michael', 'john')",
    true,
    8,
    {
      {TestUtils::create_dynbool(true), "true dynany", ERROR_RESULT},
      {TestUtils::create_dynbool(false), "false dynany", ERROR_RESULT},
      {TestUtils::create_dynlong(7), "7 dynany", ERROR_RESULT},
      {TestUtils::create_dyndouble(7.0), "7.0 dynany", ERROR_RESULT},
      {TestUtils::create_dynstring("david"), "'david' (string) dynany", SUCCESS_RESULT},
      {TestUtils::create_dynstring("hugh"), "'david' (string) dynany", FAIL_RESULT},
      {TestUtils::create_dynstring("john"), "'david' (string) dynany", SUCCESS_RESULT},
      {TestUtils::create_dynstring("sarah"), "'david' (string) dynany", FAIL_RESULT},
    }
  },
  {
    "$.true_bool_value",
    true,
    1,
    {
      {multivalue_struct, "multiple value members dynany", SUCCESS_RESULT},
    }
  },
  {
    "$.false_bool_value",
    true,
    1,
    {
      {multivalue_struct, "multiple value members dynany", FAIL_RESULT},
    }
  },
  {
    "$.unexisting_field",
    true,
    1,
    {
      {multivalue_struct, "multiple value members dynany", ERROR_RESULT},
    }
  },
  {
    "$.double_value",
    true,
    1,
    {
      {multivalue_struct, "multiple value members dynany", ERROR_RESULT},
    }
  },
  {
    "$.('true') == 7",
    true,
    1,
    {
      {bool_union, "bool union dynany", SUCCESS_RESULT},
    }
  },

  /* Structured events and runtime variables filter. */
  {
    "$domain_name == 'GSyC'",
    true,
    1,
    {
      {dynany_structured_true, "structured true boolean", SUCCESS_RESULT},
    }
  },
  {
    "$domain_name == 'Microsoft'",
    true,
    1,
    {
      {dynany_structured_true, "structured true boolean", FAIL_RESULT},
    }
  },
  {
    "$undefined_variable == 'No value'",
    false,
    0,
    {}
  },
};

#define battery_length  sizeof(battery)/sizeof(BatteryItem)

#endif
