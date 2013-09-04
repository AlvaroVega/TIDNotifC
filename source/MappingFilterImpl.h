// -*- c++ -*-
/*
 *  File name: MappingFilterImpl.h
 *  File type: Header file.
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

#ifndef _TIDNOTIF_MAPPINGFILTERIMPL_H_
#define _TIDNOTIF_MAPPINGFILTERIMPL_H_ 

#include "PortableServer.h"
#include "POA_CosNotifyFilter.h"
#include "MappingFilterData.h"

namespace TIDNotif {


class MappingFilterImpl : public virtual POA_CosNotifyFilter::MappingFilter
{

  friend class FilterFactoryImpl;
  
public:
  static const char* GET_GRAMMAR;
  
  static const char* GET_VALUE_TYPE;
		   
  static const char* GET_DEFAULT_VALUE;
		   
  static const char* SET_DEFAULT_VALUE;
		   
  static const char* ADD_MAPPING_RULE;
		   
  static const char* GET_MAPPING_RULE[3];
		   
  static const char* DELETE_MAPPING_RULE[3];
		   
  static const char* DELETE_ALL_MAPPING_RULES;
		  
  static const char* REPLACE_MAPPING_RULE[5];
		   
  static const char* MATCHES[3];
		  
  static const char* MATCH;
		  
  static const char* GET_MAPPINGS_RULES;
		  
  static const char* REGISTER[2];
		  
  static const char* UNREGISTER[2];

  static const char* EXTRACT_LONG;
		  
  static const char* TOO_MAPPING_RULES;
		  
  static const char* NEW_CONSTRAINT[4];
		  
  static const char* ARBOL;
  static const char* FOUND_MAPPING_RULE[3];
		  
  static const char* NOT_FOUND_MAPPING_RULE;
  static const char* FOUND_ARBOL;
  static const char* NOT_FOUND_ARBOL;
  static const char* FOUND_REPLACED_MAPPING_RULE[3];
		
  static const char* NOT_FOUND_REPLACED_MAPPING_RULE;
		
  static const char* TO_DO_1;

private:

  CORBA::ORB_ptr _orb;
  
  char * _grammar;
  
  // Default Servant Current POA
  PortableServer::Current_ptr _current;
  
  TIDThr::RecursiveMutex _recursive_mutex;
  
protected:  
  
  typedef map<string,MappingFilterData*> Hashtable_MappingFilterData;  
  //TODO_MORFEO: MappingFilterData or MappingFilterData*
  
  // List of MappingDiscriminators (Pack)
  Hashtable_MappingFilterData _mapping_discriminators_table;
	

public:
  //
  // Constructors
  //
  MappingFilterImpl(CORBA::ORB_ptr orb);

  MappingFilterImpl(CORBA::ORB_ptr orb,char * grammar);


private:
	
  //
  // Temas del default Servant
  //
  //
  void setCurrent(); //TODO_MORFEO: Synchronized-> take a look to TIDThread{
		
  MappingFilterData* getData();


public: 
  void register_data(MappingFilterData* data); //TODO_MORFEO: renamed from register like register_data

  void unregister_data(MappingFilterData* data); //TODO_MORFEO: renamed from unregister like unregister_data

  /*void default_value(const CORBA::Any& value); //TODO_MORFEO: ???*/
		
	
  CosNotifyFilter::MappingConstraintInfo& 
  add_mapping_constraint(const CosNotifyFilter::MappingConstraintPair& new_constraint);
			 
  CosNotifyFilter::MappingConstraintInfo* 
  get_mapping_constraint(const CosNotifyFilter::ConstraintID& id);

  void delete_mapping_constraint(const CosNotifyFilter::ConstraintID& id);

  CosNotifyFilter::MappingConstraintInfo* 
  replace_mapping_constraint( CosNotifyFilter::MappingConstraintInfo& info );

			
  void matches(char * data_filed_expression);

		
  char* constraint_grammar();


  CORBA::TypeCode_ptr value_type();


  CORBA::Any* default_value();

			
  CosNotifyFilter::MappingConstraintInfoSeq* 
  add_mapping_constraints(const CosNotifyFilter::MappingConstraintPairSeq& pair_list)
    throw (CosNotifyFilter::InvalidConstraint, CosNotifyFilter::InvalidValue);

			
  void modify_mapping_constraints(const CosNotifyFilter::ConstraintIDSeq& del_list, 
                                  const CosNotifyFilter::MappingConstraintInfoSeq& modify_list)
    throw (CosNotifyFilter::InvalidConstraint, CosNotifyFilter::InvalidValue,
           CosNotifyFilter::ConstraintNotFound);

			
  CosNotifyFilter::MappingConstraintInfoSeq* 
  get_mapping_constraints(const CosNotifyFilter::ConstraintIDSeq& id_list)
    throw (CosNotifyFilter::ConstraintNotFound);

			
  CosNotifyFilter::MappingConstraintInfoSeq* get_all_mapping_constraints();

			
  void remove_all_mapping_constraints();

			
  void destroy();

			
  CORBA::Boolean match(const CORBA::Any& filterable_data, CORBA::Any*& result_to_set)
    throw (CosNotifyFilter::UnsupportedFilterableData);

			
  CORBA::Boolean match_structured(const CosNotification::StructuredEvent& filterable_data, 
                                  CORBA::Any*& result_to_set)
    throw (CosNotifyFilter::UnsupportedFilterableData);

			
  CORBA::Boolean match_typed(const CosNotification::PropertySeq& filterable_data, 
                             CORBA::Any*& result_to_set)
    throw (CosNotifyFilter::UnsupportedFilterableData);

};
	
	 
};//namespace TIDNotif
#endif

