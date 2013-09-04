/*
 *  File name: test_utils.h
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

#ifndef _TEST_UTILS_H
#define _TEST_UTILS_H

#include <CORBA.h>
#include <DynamicAny.h>

#include "CosNotification.h"

namespace TestUtils {

typedef struct
{
  const char * name;
  CORBA::TypeCode_ptr type;
  CORBA::Any value;
} StructMember;

typedef struct
{
  const char * name;
  CORBA::Any label;
  CORBA::TypeCode_ptr type;
  CORBA::Any value;
} UnionMember;

StructMember
create_boolean_struct_member(const char * name, bool value);

CORBA::Any
create_boolean_label(bool value);

UnionMember
create_boolean_union_member(const char * name, bool value, CORBA::Any label);

UnionMember
create_long_union_member(const char * name, long value, CORBA::Any label);

UnionMember
create_double_union_member(const char * name, double value, CORBA::Any label);

DynamicAny::DynAny_ptr
create_dynstruct(const char * id,
                 const char * name,
                 StructMember members[],
                 unsigned long member_count);

DynamicAny::DynAny_ptr
create_dynstruct(StructMember members[],
                 unsigned long member_count);

DynamicAny::DynAny_ptr
create_dynunion(const char * id,
                const char * name,
                CORBA::TypeCode_ptr discriminator,
                UnionMember members[],
                unsigned long member_count);

DynamicAny::DynAny_ptr
create_dynunion(CORBA::TypeCode_ptr discriminator,
                UnionMember members[],
                unsigned long member_count);

DynamicAny::DynAny_ptr
create_dynbool(bool value);

DynamicAny::DynAny_ptr
create_dynlong(long value);

DynamicAny::DynAny_ptr
create_dyndouble(double value);

DynamicAny::DynAny_ptr
create_dynstring(const char * value);

typedef enum
{
  BOOLEAN_TC,
  LONG_TC,
  DOUBLE_TC,
  STRING_TC
} BasicTypeCode;

CORBA::TypeCode_ptr
get_basic_tc(BasicTypeCode tc);

::CosNotification::StructuredEvent *
create_structured_event(const string & domain_name,
                        const string & type_name,
                        const string & event_name,
                        const CORBA::Any & body);

DynamicAny::DynAny_ptr
structured_event_to_dynany(const CosNotification::StructuredEvent & event);

}

#endif
