/*
 *  File name: test_utils.C
 *  File type: Test body file.
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

#include "test_utils.h"

/* ORB reference. */
CORBA::ORB_var __test_utils_orb = NULL;

/* Dynamic any factory reference. */
DynamicAny::DynAnyFactory_ptr __test_utils_dyn_any_factory = NULL;

/* Locate DynAnyFactory reference. */
void
__test_utils_locate_dyn_any_factory()
{
  char ** args;
  int i;
  const char * __test_utils_orb_id;
  CORBA::Object_ptr obj;

  if (__test_utils_dyn_any_factory == NULL)
  {
    try
    {
      i = 0;
      __test_utils_orb_id="TIDConstraint";
      __test_utils_orb = CORBA::ORB_init(i,args,__test_utils_orb_id);
    }
    catch (CORBA::Exception& e)
    {}

    try
    {
      obj =  __test_utils_orb->resolve_initial_references("DynAnyFactory");
      __test_utils_dyn_any_factory = 
        DynamicAny::_DynAnyFactoryHelper::narrow(obj,true);
    }
    catch (CORBA::Exception& e)
    {}
  }
}

TestUtils::StructMember
TestUtils::create_boolean_struct_member(const char * name, bool value)
{
  CORBA::Any any;
  StructMember member;

  any.delegate().insert_boolean(value);
  member.name = name;
  member.type = get_basic_tc(TestUtils::BOOLEAN_TC);
  member.value.delegate() = any.delegate();
  return member;
}

CORBA::Any
TestUtils::create_boolean_label(bool value)
{
  CORBA::Any any;

  any.delegate().insert_boolean(value);
  return any;
}

TestUtils::UnionMember
TestUtils::create_boolean_union_member(const char * name, 
                                       bool value,
                                       CORBA::Any label)
{
  CORBA::Any any;
  UnionMember member;

  any.delegate().insert_boolean(value);
  member.name = name;
  member.type = get_basic_tc(TestUtils::BOOLEAN_TC);
  member.value.delegate() = any.delegate();
  member.label = label;
  return member;
}

TestUtils::UnionMember
TestUtils::create_long_union_member(const char * name, 
                                    long value, 
                                    CORBA::Any label)
{
  CORBA::Any any;
  UnionMember member;

  any.delegate().insert_long(value);
  member.name = name;
  member.type = get_basic_tc(TestUtils::LONG_TC);
  member.value.delegate() = any.delegate();
  member.label = label;
  return member;
}

TestUtils::UnionMember
TestUtils::create_double_union_member(const char * name,
                                      double value,
                                      CORBA::Any label)
{
  CORBA::Any any;
  UnionMember member;

  any.delegate().insert_double(value);
  member.name = name;
  member.type = get_basic_tc(TestUtils::DOUBLE_TC);
  member.value.delegate() = any.delegate();
  member.label = label;
  return member;
}

DynamicAny::DynAny_ptr
TestUtils::create_dynstruct(const char * id,
                            const char * name,
                            StructMember members[],
                            unsigned long member_count)
{
  CORBA::StructMemberSeq * member_seq;
  CORBA::StructMember * smv;
  CORBA::StructDef * sd;
  CORBA::Any a;
  DynamicAny::NameValuePairSeq * member_values;
  DynamicAny::DynStruct_ptr result;
  int i;

  if (!__test_utils_dyn_any_factory)
    __test_utils_locate_dyn_any_factory();

  member_seq = new CORBA::StructMemberSeq();
  member_seq->length(member_count);
  for (i = 0; i < member_count; i++)
  {
    (*member_seq)[i].name = 
      (::CORBA::Identifier) CORBA::string_dup(members[i].name);
    (*member_seq)[i].type = members[i].type;
    (*member_seq)[i].type_def = CORBA::IDLType::_nil();
  }

  result = DynamicAny::DynStruct::_narrow(
    __test_utils_dyn_any_factory->create_dyn_any_from_type_code(
      TIDorb::portable::TypeCodeFactory::create_struct_tc(
        (const ::CORBA::RepositoryId) id,
        (const ::CORBA::Identifier) name, 
        member_seq)));

  member_values = result->get_members();
  for (i = 0; i < member_values->length(); i++)
    (*member_values)[i].value = members[i].value;
  result->set_members(*member_values);
  delete member_values;
  return result;
}

DynamicAny::DynAny_ptr
TestUtils::create_dynstruct(StructMember members[],
                            unsigned long member_count)
{
  char * id;
  char * name;

  id = "IDL:UnknowStructName:1.0";
  name = "UnknowStructName";
  return create_dynstruct(id, name, members, member_count);
}

DynamicAny::DynAny_ptr
TestUtils::create_dynunion(const char * id,
                           const char * name,
                           CORBA::TypeCode_ptr discriminator,
                           UnionMember members[],
                           unsigned long member_count)
{
  CORBA::UnionMemberSeq * member_seq;
  DynamicAny::NameValuePairSeq * member_values;
  DynamicAny::DynUnion_ptr result;
  int i;

  if (!__test_utils_dyn_any_factory)
    __test_utils_locate_dyn_any_factory();

  member_seq = new CORBA::UnionMemberSeq();
  member_seq->length(member_count);
  for (i = 0; i < member_count; i++)
  {
    (*member_seq)[i].name = 
      (::CORBA::Identifier) CORBA::string_dup(members[i].name);
    (*member_seq)[i].label = members[i].label;
    (*member_seq)[i].type = members[i].type;
    (*member_seq)[i].type_def = CORBA::IDLType::_nil();
  }

  result = DynamicAny::DynUnion::_narrow(
    __test_utils_dyn_any_factory->create_dyn_any_from_type_code(
      TIDorb::portable::TypeCodeFactory::create_union_tc(
        (const ::CORBA::RepositoryId) id,
        (const ::CORBA::Identifier) name, 
        discriminator,
        member_seq)));
  return result;
}

DynamicAny::DynAny_ptr
TestUtils::create_dynunion(CORBA::TypeCode_ptr discriminator,
                           UnionMember members[],
                           unsigned long member_count)
{
  char * id;
  char * name;

  id = "IDL:UnknowUnionName:1.0";
  name = "UnknowUnionName";
  return create_dynunion(id, name, discriminator, members, member_count);
}

DynamicAny::DynAny_ptr
TestUtils::create_dynbool(bool value)
{
  CORBA::Any bool_any;

  if (!__test_utils_dyn_any_factory)
    __test_utils_locate_dyn_any_factory();

  bool_any.delegate().insert_boolean(value);
  return __test_utils_dyn_any_factory->create_dyn_any(bool_any);
}

DynamicAny::DynAny_ptr
TestUtils::create_dynlong(long value)
{
  CORBA::Any long_any;

  if (!__test_utils_dyn_any_factory)
    __test_utils_locate_dyn_any_factory();

  long_any.delegate().insert_long(value);
  return __test_utils_dyn_any_factory->create_dyn_any(long_any);
}

DynamicAny::DynAny_ptr
TestUtils::create_dyndouble(double value)
{
  CORBA::Any double_any;

  if (!__test_utils_dyn_any_factory)
    __test_utils_locate_dyn_any_factory();

  double_any.delegate().insert_double(value);
  return __test_utils_dyn_any_factory->create_dyn_any(double_any);
}

DynamicAny::DynAny_ptr
TestUtils::create_dynstring(const char * value)
{
 CORBA::Any str_any;

  if (!__test_utils_dyn_any_factory)
    __test_utils_locate_dyn_any_factory();

  str_any.delegate().insert_string(value);
  return __test_utils_dyn_any_factory->create_dyn_any(str_any);
}

CORBA::TypeCode_ptr
TestUtils::get_basic_tc(BasicTypeCode tc)
{
  switch (tc)
  {
    case BOOLEAN_TC:
      return TIDorb::portable::TypeCodeFactory::get_basic_TypeCode(
        ::CORBA::tk_boolean);
    case LONG_TC:
      return TIDorb::portable::TypeCodeFactory::get_basic_TypeCode(
        ::CORBA::tk_long);
    case DOUBLE_TC:
      return TIDorb::portable::TypeCodeFactory::get_basic_TypeCode(
        ::CORBA::tk_double);
    case STRING_TC:
      return TIDorb::portable::TypeCodeFactory::get_basic_TypeCode(
        ::CORBA::tk_string);
    default:
      return NULL;
  }
}

CosNotification::StructuredEvent *
TestUtils::create_structured_event(const string & domain_name,
                                   const string & type_name,
                                   const string & event_name,
                                   const CORBA::Any & body)
{
  CosNotification::_EventType event_type(
    domain_name.c_str(), type_name.c_str());
  CosNotification::FixedEventHeader fixed_header(
    event_type, event_name.c_str());
  CosNotification::OptionalHeaderFields variable_header(0);
  CosNotification::EventHeader header(fixed_header, variable_header);
  CosNotification::FilterableEventBody filterable_data(0);

  return new CosNotification::StructuredEvent(
    header, filterable_data, body);
}

DynamicAny::DynAny_ptr
TestUtils::structured_event_to_dynany(
  const CosNotification::StructuredEvent & event)
{
  CORBA::Any any;

  any <<= event;
  return __test_utils_dyn_any_factory->create_dyn_any(any);
}
