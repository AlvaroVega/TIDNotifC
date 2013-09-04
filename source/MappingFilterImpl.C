/*
 *  File name: MappingFilterImpl.C
 *  File type: Body file.
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

#include "MappingFilterImpl.h"
#include "TIDParser.h"
#include "TIDorb/core/poa/OID.h"
#include "PersistenceManager.h"


namespace TIDNotif {


  const char* MappingFilterImpl::GET_GRAMMAR =
  "-> MappingDiscriminatorImpl.grammar()";

  const char* MappingFilterImpl::GET_VALUE_TYPE =
  "-> MappingDiscriminatorImpl.value_type()";

  const char* MappingFilterImpl::GET_DEFAULT_VALUE =
  "-> MappingDiscriminatorImpl.default_value()";

  const char* MappingFilterImpl::SET_DEFAULT_VALUE =
  "-> MappingDiscriminatorImpl.default_value(any)";

  const char* MappingFilterImpl::ADD_MAPPING_RULE =
  "-> MappingDiscriminatorImpl.add_mapping_constraint(new_rule, any)";

  const char* MappingFilterImpl::GET_MAPPING_RULE[3] =
    { "-> MappingDiscriminatorImpl.get_mapping_constraint(", NULL, ")" };

  const char* MappingFilterImpl::DELETE_MAPPING_RULE[3] =
    { "-> MappingDiscriminatorImpl.delete_mapping_constraint(", NULL, ")" };

  const char* MappingFilterImpl::DELETE_ALL_MAPPING_RULES =
  "-> MappingDiscriminatorImpl.delete_mapping_constraint()";

  const char* MappingFilterImpl::REPLACE_MAPPING_RULE[5] =
    { "-> MappingDiscriminatorImpl.replace_mapping_constraint(Id: ", 
      NULL, ", <", NULL, ">"};

  const char* MappingFilterImpl::MATCHES[3] =
    { "-> MappingDiscriminatorImpl.matches(", NULL, ")" };

  const char* MappingFilterImpl::MATCH =
  "-> MappingDiscriminatorImpl.match(any, anyholder)";

  const char* MappingFilterImpl::GET_MAPPINGS_RULES =
  "-> MappingDiscriminatorImpl.get_mapping_rules()";

  const char* MappingFilterImpl::REGISTER[2] =
    { " # MappingDiscriminatorImpl.register() -> ", NULL };

  const char* MappingFilterImpl::UNREGISTER[2] =
    { " # MappingDiscriminatorImpl.unregister() -> ", NULL };

  const char* MappingFilterImpl::EXTRACT_LONG =
  "   ERROR: _default_value.type()";

  const char* MappingFilterImpl::TOO_MAPPING_RULES =
  "   ERROR: Numero maximo de mapping rules (constraints) alcanzado.";

  const char* MappingFilterImpl::NEW_CONSTRAINT[4] =
    { " * Constraint: {", NULL, "} - Id = ", NULL };

  const char* MappingFilterImpl::ARBOL = 
  " * Arbol asociado: ";

  const char* MappingFilterImpl::FOUND_MAPPING_RULE[3] =
    { "  Constraint: {", NULL, "}" };

  const char* MappingFilterImpl::NOT_FOUND_MAPPING_RULE = 
  "  Constraint: null";

  const char* MappingFilterImpl::FOUND_ARBOL = 
  "  Arbol asociado: removed!";

  const char* MappingFilterImpl::NOT_FOUND_ARBOL = 
  "  Arbol asociado: NOT FOUND";

  const char* MappingFilterImpl::FOUND_REPLACED_MAPPING_RULE[3] =
    { "  Antigua constraint: {", NULL, "}" };

  const char* MappingFilterImpl::NOT_FOUND_REPLACED_MAPPING_RULE =
  "  Antigua constraint: null";

  const char* MappingFilterImpl::TO_DO_1 =
  " > Creamos un Any con el valor: TODO...";



//
// Constructors
//
MappingFilterImpl::MappingFilterImpl(CORBA::ORB_ptr orb)
  :_orb(orb), _current(NULL)
{
  _grammar = (char *) util::parser::TIDParser::_CONSTRAINT_GRAMMAR;
}

MappingFilterImpl::MappingFilterImpl(CORBA::ORB_ptr orb, char * grammar)
  :_orb(orb), _current(NULL)
{
  if (strcmp(util::parser::TIDParser::_CONSTRAINT_GRAMMAR, grammar)) {
    throw CORBA::NO_IMPLEMENT();
  }	
  _grammar = grammar;
}

//
// Temas del default Servant
//
//
void MappingFilterImpl::setCurrent()
{ 
  TIDThr::Synchronized sync(_recursive_mutex);

  if (_current == NULL) {
    
    try {
      _current =
        PortableServer::_CurrentHelper::narrow(_orb->resolve_initial_references("POACurrent"),false);
    } catch (CORBA::Exception & ex) {
      //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace.
      throw CORBA::INTERNAL();
    }
  } 
}

MappingFilterData* MappingFilterImpl::getData()
{
  if (_current == NULL)
    setCurrent();
  try {
    TIDorb::core::poa::OID* oid = new TIDorb::core::poa::OID::OID(*(_current->get_object_id()));
    MappingFilterData* data = (MappingFilterData*) _mapping_discriminators_table[oid->toString()];
    if (data != NULL) {
      return data;
    } else {
      throw CORBA::OBJECT_NOT_EXIST();
    }
  } catch (CORBA::Exception ex) {
    //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
    throw CORBA::INV_OBJREF();
  }
}
 
void MappingFilterImpl::register_data(MappingFilterData* data)
{ 
  //TODO_MORFEO: renamed from register like register_data

  REGISTER[1] = data->id_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, REGISTER); //TODO_MORFEO: Trace
  _mapping_discriminators_table[data->id]=data;
}

void MappingFilterImpl::unregister_data(MappingFilterData* data)
{ 
  //TODO_MORFEO: renamed from unregister like unregister_data
  UNREGISTER[1] = data->id_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UNREGISTER); //TODO_MORFEO: Trace
  _mapping_discriminators_table.erase(data->id);
}




//   void MappingFilterImpl::default_value(const CORBA::Any& value){ //TODO_MORFEO: ???
//   MappingFilterData* mapping_discriminator_data = getData();
//   //TIDNotifTrace.print(TIDNotifTrace.USER, SET_DEFAULT_VALUE); //TODO_MORFEO: Trace
			
//   mapping_discriminator_data->default_value = value; 
//   if (PersistenceManager::isActive()) {
//   //PersistenceManager.getDB().save(PersistenceDB.SAVE, _id, 
//                                     mapping_discriminator_data.default_value);
//   }
//   }



	
CosNotifyFilter::MappingConstraintInfo& 
MappingFilterImpl::add_mapping_constraint(
                                const CosNotifyFilter::MappingConstraintPair& new_constraint)
{
  MappingFilterData* data = getData();
  //TIDNotifTrace.print(TIDNotifTrace.USER, ADD_MAPPING_RULE); //TODO_MORFEO: Trace
  if (!(data->value_type.equal(new_constraint.result_to_set.type()))) {
    throw CosNotifyFilter::InvalidValue();
  }
  util::parser::TIDConstraint* new_filter = NULL;
  try { 
    new_filter = 
      util::parser::TIDParser::parse( new_constraint.constraint_expression.constraint_expr.in() );
  } catch (util::parser::ParsingErrorException& ex) { 
    //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
    throw CosNotifyFilter::InvalidConstraint(new_constraint.constraint_expression);
  }
  //TODO: reimplement this... use a stack of unused keys instead...
  int new_key;
  int security_limit = 0;
  do {
    new_key = util::parser::TIDParser::newConstraintId();
    security_limit++;
    if (security_limit > util::parser::TIDParser::_MAX_CONSTRAINT_ID) {
      //TIDNotifTrace.print(TIDNotifTrace.ERROR, TOO_MAPPING_RULES); 
      //TODO_MORFEO: Trace
      //throw new CosNotifyFilter::InvalidConstraint(TOO_MAPPING_RULES, 
      //                                             new_constraint.constraint_expression);
      throw CORBA::NO_RESOURCES();
    }
  } while (data->assignedMappingConstraintInfoTable.count(new_key) );

  CosNotifyFilter::MappingConstraintInfo* info;
  try {
    info = new CosNotifyFilter::MappingConstraintInfo(new_constraint.constraint_expression,
                                                      new_key,
                                                      new_constraint.result_to_set);
    data->assignedMappingConstraintInfoTable[new_key]=*info;
		
    data->filterTable[new_key]= new_filter;
  } catch (CORBA::Exception& ex) { //TODO_MORFEO:
    // Por si lo que ha fallado es la seguinda insercion
    data->assignedMappingConstraintInfoTable.erase(new_key);
    data->filterTable.erase(new_key);
    //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
    throw CosNotifyFilter::InvalidConstraint();
  }
  NEW_CONSTRAINT[1] = new_constraint.constraint_expression.constraint_expr;
  TIDorb::util::StringBuffer buffer;  
  buffer<< new_key;
  string key = buffer.str().data();
  NEW_CONSTRAINT[3] = key.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, NEW_CONSTRAINT); //TODO_MORFEO: Trace
  //TIDNotifTrace.print(TIDNotifTrace.DEEP_DEBUG, ARBOL);    //TODO_MORFEO: Trace
  //new_filter->dump("   "); //TODO_MORFEO: free
  if (PersistenceManager::isActive()) {
    //PersistenceManager::getDB()->save( PersistenceDB::SAVE, _id, 
    //new_key, new_constraint, value );
  }
  return *info;
}

CosNotifyFilter::MappingConstraintInfo* 
MappingFilterImpl::get_mapping_constraint(const CosNotifyFilter::ConstraintID& id)
{
  MappingFilterData* data = getData();
  MappingFilterData::MappingConstraintInfoTable::iterator iter;
  iter=data->assignedMappingConstraintInfoTable.find(id);
  if ( iter == data->assignedMappingConstraintInfoTable.end()  ) {
    throw CosNotifyFilter::ConstraintNotFound( id );
  }
		
  TIDorb::util::StringBuffer buffer;  
  buffer<< id;
  string key = buffer.str().data();

  GET_MAPPING_RULE[1] = key.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, GET_MAPPING_RULE); //TODO_MORFEO: Trace

  CosNotifyFilter::MappingConstraintInfo* info;
  info = new CosNotifyFilter::MappingConstraintInfo( (CosNotifyFilter::MappingConstraintInfo ) data->assignedMappingConstraintInfoTable[id]);
		
  return info;	
}

void MappingFilterImpl::delete_mapping_constraint(const CosNotifyFilter::ConstraintID& id)
{
  MappingFilterData* data = getData();
  TIDorb::util::StringBuffer buffer;  
  buffer<< id;
  string key = buffer.str().data();
  DELETE_MAPPING_RULE[1] = key.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, DELETE_MAPPING_RULE); //TODO_MORFEO: Trace

  if (data->assignedMappingConstraintInfoTable.count(id)==false){
    throw CosNotifyFilter::ConstraintNotFound( id );
  }

  //CosNotifyFilter::MappingConstraintInfo* info; 
  data->assignedMappingConstraintInfoTable.erase(id);

  //if (info != null) { //TODO_MORFEO: Trace
  //	FOUND_MAPPING_RULE[1] = info.constraint_expression.constraint_expr;
  //	TIDNotifTrace.print(TIDNotifTrace.DEBUG, FOUND_MAPPING_RULE);
  //} else {
  //	TIDNotifTrace.print(TIDNotifTrace.DEBUG, NOT_FOUND_MAPPING_RULE);
  //}

  // Eliminamos el arbol
  util::parser::EvaluableNode* filter = (util::parser::EvaluableNode*) data->filterTable[id];
  data->filterTable.erase(id);
  if (filter != NULL) {
    //TIDNotifTrace.print(TIDNotifTrace.DEBUG, FOUND_ARBOL); //TODO_MORFEO: Trace
    delete filter;
  }// else { //TODO_MORFEO: Trace
  //	TIDNotifTrace.print(TIDNotifTrace.DEBUG, NOT_FOUND_ARBOL);
  //}

  if (PersistenceManager::isActive()) {
    //PersistenceManager.getDB().removeMappingRules( id, mapping_discriminator_data.id);
  }
}


CosNotifyFilter::MappingConstraintInfo* 
MappingFilterImpl::replace_mapping_constraint(CosNotifyFilter::MappingConstraintInfo& info)
{
  MappingFilterData* data = getData();
  int key = info.constraint_id ;
  TIDorb::util::StringBuffer buffer;  
  buffer<< key;
  string key_string = buffer.str().data();
  REPLACE_MAPPING_RULE[1] = key_string.c_str();
  REPLACE_MAPPING_RULE[3] = info.constraint_expression.constraint_expr;
  //TIDNotifTrace.print(TIDNotifTrace.USER, REPLACE_MAPPING_RULE); //TODO_MORFEO: Trace


  if (!data->value_type.equal(info.value.type())) {
    throw CosNotifyFilter::InvalidValue(info.constraint_expression,info.value);
  }

  if (data->assignedMappingConstraintInfoTable.count(key) == false) {
    throw CosNotifyFilter::ConstraintNotFound( info.constraint_id );
  }

  util::parser::TIDConstraint* new_filter = NULL;
  //try { //TODO_MORFEO: ParseException
  new_filter = util::parser::TIDParser::parse( info.constraint_expression.constraint_expr.in()	 );
  //} catch (es.tid.util.parser.ParseException ex) {
  //	TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex);
  //	throw new InvalidConstraint( ex.getMessage(), info.constraint_expression );
  //} catch (java.lang.Exception ex) {
  //	TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex);
  //	throw new InvalidConstraint( ex.getMessage(), info.constraint_expression );
  //}

  // Reemplazamos la MappingRule
  CosNotifyFilter::MappingConstraintInfo* previous_info;
  previous_info = new CosNotifyFilter::MappingConstraintInfo( data->assignedMappingConstraintInfoTable[key]);
  data->assignedMappingConstraintInfoTable[key]=info;
  //if (previous_info != null) { //TODO_MORFEO: Trace
  //	FOUND_REPLACED_MAPPING_RULE[1] = previous_info.constraint_expression.constraint_expr;
  //	TIDNotifTrace.print(TIDNotifTrace.DEBUG,FOUND_REPLACED_MAPPING_RULE);
  //} else {
  //	TIDNotifTrace.print(TIDNotifTrace.DEBUG,NOT_FOUND_REPLACED_MAPPING_RULE);
  //}

  // Reemplazamos el arbol
  //util::parser::EvaluableNode* old_filter; //TODO_MORFEO: Trace
  data->filterTable[key]=new_filter;
  //if (old_filter != null) { //TODO_MORFEO: Trace
  //	TIDNotifTrace.print(TIDNotifTrace.DEBUG, FOUND_ARBOL);
  //} else {
  //	TIDNotifTrace.print(TIDNotifTrace.DEBUG, NOT_FOUND_ARBOL);
  //}

  if (PersistenceManager::isActive()) {
    //PersistenceManager.getDB().save( PersistenceDB.UPDATE, _id, 
    //id, new_constraint, new_value );
  }
  return previous_info;
}
			
void MappingFilterImpl::matches(char * data_filed_expression)
{
  //MappingFilterData* mapping_discriminator_data = getData();
  MATCHES[1] = data_filed_expression;
  //TIDNotifTrace.print(TIDNotifTrace.USER, MATCHES); //TODO_MORFEO: Trace

  util::parser::EvaluableNode* match_filter = NULL;
  try {
    match_filter = util::parser::TIDParser::parse(data_filed_expression);
  } catch (util::parser::ParsingErrorException& ex) { 
    //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
    throw CosNotifyFilter::InvalidConstraint();
  }
}
		
char* MappingFilterImpl::constraint_grammar()
{
  //TIDNotifTrace.print(TIDNotifTrace.USER, GET_GRAMMAR); //TODO_MORFEO: Trace
  return _grammar;
}


CORBA::TypeCode_ptr MappingFilterImpl::value_type()
{
  MappingFilterData* mapping_discriminator_data = getData();
  //TIDNotifTrace.print(TIDNotifTrace.USER, GET_VALUE_TYPE); //TODO_MORFEO: Trace
  return (CORBA::TypeCode_ptr) &(mapping_discriminator_data->value_type);
}

CORBA::Any* MappingFilterImpl::default_value()
{
  MappingFilterData* mapping_discriminator_data = getData();
  //TIDNotifTrace.print(TIDNotifTrace.USER, GET_DEFAULT_VALUE); //TODO_MORFEO: Trace
  return (CORBA::Any*) &(mapping_discriminator_data->default_value);
}
			
CosNotifyFilter::MappingConstraintInfoSeq* 
MappingFilterImpl::add_mapping_constraints(
                             const CosNotifyFilter::MappingConstraintPairSeq& pair_list)
  throw (CosNotifyFilter::InvalidConstraint, CosNotifyFilter::InvalidValue)
{
  //if ( pair_list != NULL) { //TODO_MORFEO: it cannot be null
  CORBA::ULong i;
  CosNotifyFilter::InvalidConstraint* error;
  CosNotifyFilter::MappingConstraintInfoSeq* info_list;
  error = NULL;
  info_list = new CosNotifyFilter::MappingConstraintInfoSeq(pair_list.length());
  for (i = 0; error == NULL && i < pair_list.length(); i++) {
    try {
      (*info_list)[i] = this->add_mapping_constraint(pair_list[i]);
    } catch (CosNotifyFilter::InvalidConstraint& ic) {
      error = &ic;
    }
  }

  if (error != NULL) {
    for (int j = i; j >= 0; j++) {
      //if (info_list[j] != NULL) { //TODO_MORFEO : it cannot be null
      try {
        this->delete_mapping_constraint((*info_list)[j].constraint_id);
      } catch (CORBA::Exception& ex) {
      }
      //}
    }
    throw error;
  }
  return info_list;
  //} else {
  //	throw new BAD_PARAM();
  //}
}
		
void 
MappingFilterImpl::modify_mapping_constraints(
                                 const CosNotifyFilter::ConstraintIDSeq& del_list, 
                                 const CosNotifyFilter::MappingConstraintInfoSeq& modify_list)
 throw (CosNotifyFilter::InvalidConstraint, CosNotifyFilter::InvalidValue,
           CosNotifyFilter::ConstraintNotFound)
{

  CosNotifyFilter::ConstraintNotFound* notFound = NULL;
  CosNotifyFilter::InvalidConstraint* invalidConstraint = NULL;

  MappingFilterData* data;
  int* del_list_keys;
  int* modify_list_keys;
  data = getData();

  /**
   * Check preconditions: every constraint referenced must exist
   */
  MappingFilterData::MappingConstraintInfoTable::iterator iteratorTable;
  if (del_list.length() > 0) {
    del_list_keys = new int[del_list.length()];

    for (CORBA::ULong i = 0; notFound == NULL && i < del_list.length(); i++) {
      del_list_keys[i] = del_list[i];
      iteratorTable = data->assignedMappingConstraintInfoTable.find(del_list_keys[i]);
      if (iteratorTable == data->assignedMappingConstraintInfoTable.end()) { 
        notFound = new CosNotifyFilter::ConstraintNotFound(del_list[i]);
      }
    }//for
  } else {
    del_list_keys = NULL;
  }


  if (modify_list.length() > 0) {
    modify_list_keys = new int[modify_list.length()];
			
    for (CORBA::ULong i = 0; notFound == NULL && i < modify_list.length(); i++) {
      modify_list_keys[i] =(int) modify_list[i].constraint_id;
      iteratorTable = data->assignedMappingConstraintInfoTable.find(modify_list_keys[i]);
      if (iteratorTable == data->assignedMappingConstraintInfoTable.end()) { 
        notFound = new CosNotifyFilter::ConstraintNotFound(
                                                           modify_list[i].constraint_id);
      }
    }//for
  } else {
    modify_list_keys = NULL;
  }


  /**
   * Perform changes...
   */
  if (notFound == NULL) {
    /**
     * Constraint removal. Store a backup array in case of error
     */
    util::parser::TIDConstraint * removedFilters[del_list.length()];
    CosNotifyFilter::MappingConstraintInfoSeq* removedConstraints;
    removedConstraints = new CosNotifyFilter::MappingConstraintInfoSeq(del_list.length());
    for (CORBA::ULong i = 0; i < del_list.length(); i++) {
      (*removedConstraints)[i] = (CosNotifyFilter::MappingConstraintInfo) data->assignedMappingConstraintInfoTable[del_list_keys[i]];
      data->assignedMappingConstraintInfoTable.erase(del_list_keys[i]);
      //if (removedConstraints[i] != null) { //TODO_MORFEO: it's not necessary to verify it again
      FOUND_MAPPING_RULE[1] = (*removedConstraints)[i].constraint_expression.constraint_expr;
			
      //TIDNotifTrace.print(TIDNotifTrace.DEBUG, FOUND_MAPPING_RULE); //TODO_MORFEO: Trace
      //} else {
      //	TIDNotifTrace.print(TIDNotifTrace.DEBUG,
      //		NOT_FOUND_MAPPING_RULE);
      //}
      removedFilters[i] = data->filterTable[del_list_keys[i]];
      data->filterTable.erase(del_list_keys[i]);
      /*if (removedFilters[i] != null) { //TODO_MORFEO: Trace;
        TIDNotifTrace.print(TIDNotifTrace.DEBUG, FOUND_ARBOL);
        } else {
        TIDNotifTrace.print(TIDNotifTrace.DEBUG, NOT_FOUND_ARBOL);
        }*/
    }

    /**
     * Constraint replace. Note, if some constraint to be modified was removed
     * in the previous step, it will be inserted as the spec doesn't
     * tells anything about it
     */
    util::parser::TIDConstraint * replacedFilters[modify_list.length()];

	
    CosNotifyFilter::MappingConstraintInfoSeq* replacedConstraints;
    replacedConstraints = new CosNotifyFilter::MappingConstraintInfoSeq(modify_list.length());
	
    for (CORBA::ULong i = 0; invalidConstraint == NULL && i < modify_list.length(); i++) {

      /*REPLACE_MAPPING_RULE[1] = modify_list_keys[i].toString();
        REPLACE_MAPPING_RULE[3] = modify_list[i].constraint_expression.constraint_expr;*/
      //TIDNotifTrace.print(TIDNotifTrace.USER, REPLACE_MAPPING_RULE); //TODO_MORFEO: Trace

      util::parser::TIDConstraint* new_filter = NULL;
      //try { //TODO_MORFEO: ParseException
      new_filter = util::parser::TIDParser::parse(modify_list[i].constraint_expression.constraint_expr.in());
      //} catch (es.tid.util.parser.ParseException ex) {
      //	TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex);
      //	invalidConstraint = new InvalidConstraint(ex.getMessage(),
      //		modify_list[i].constraint_expression);
      //} catch (java.lang.Exception ex) {
      //	TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex);
      //	invalidConstraint = new InvalidConstraint(ex.getMessage(),
      //		modify_list[i].constraint_expression);
      //}

      if (invalidConstraint == NULL) {
        // Reemplazamos la Constraint
        (*replacedConstraints)[i] = data->assignedMappingConstraintInfoTable[modify_list_keys[i]];
        iteratorTable = data->assignedMappingConstraintInfoTable.find(modify_list_keys[i]);
        data->assignedMappingConstraintInfoTable[modify_list_keys[i]]= modify_list[i];
						
        if (iteratorTable!= data->assignedMappingConstraintInfoTable.end()) {
						
          FOUND_REPLACED_MAPPING_RULE[1] = (*replacedConstraints)[i].constraint_expression.constraint_expr.in();
          //TIDNotifTrace.print(TIDNotifTrace.DEBUG,FOUND_REPLACED_MAPPING_RULE); //TODO_MORFEO: Trace

        } else {
          //TIDNotifTrace.print(TIDNotifTrace.DEBUG,NOT_FOUND_REPLACED_MAPPING_RULE); //TODO_MORFEO: Trace

        }

        // Reemplazamos el arbol
        replacedFilters[i] = data->filterTable[modify_list_keys[i]];
        data->filterTable[modify_list_keys[i]]=new_filter;
        /*if (replacedFilters[i] != null) { //TODO_MORFEO: Trace
          TIDNotifTrace.print(TIDNotifTrace.DEBUG, FOUND_ARBOL);
          } else {
          TIDNotifTrace.print(TIDNotifTrace.DEBUG,
          NOT_FOUND_ARBOL);
          }*/
      }//if invalidConstraint == null
    }//for

    if (invalidConstraint != NULL) {
      /**
       * Restore previus.constraint_expression.constraint_expr changes...
       */
      for (CORBA::ULong i = replacedConstraints->length(); i >= 0; --i) {
						
        data->assignedMappingConstraintInfoTable[modify_list_keys[i]]=(*replacedConstraints)[i];
        data->filterTable[modify_list_keys[i]]=replacedFilters[i];
						
      }// for
      for (CORBA::ULong i = removedConstraints->length(); i >= 0; --i) {
													
        data->assignedMappingConstraintInfoTable[del_list_keys[i]]=(*removedConstraints)[i];
        data->filterTable[del_list_keys[i]]=removedFilters[i];
						
      }// for
      //TODO_MORFEO: In Notification Service Specification specifies 
      //that in this situation must be throwed the InvalidConstraint Exception 
    } else {
      delete removedConstraints;
      delete replacedConstraints;
      for (CORBA::ULong i = 0; i<del_list.length(); i++)
        {
          delete removedFilters[i];
        }
      for (CORBA::ULong i = 0; i<modify_list.length(); i++)
        {
          delete replacedFilters[i];
        }
      if (PersistenceManager::isActive()) {
        PersistenceManager::getDB()->update_data(
                                                 PersistenceDB::ATTR_CONSTRAINTS, data);
      }
    }
				
			
  } else {
    throw notFound;
  }
}

			
CosNotifyFilter::MappingConstraintInfoSeq* 
MappingFilterImpl::get_mapping_constraints(const CosNotifyFilter::ConstraintIDSeq& id_list)
  throw (CosNotifyFilter::ConstraintNotFound)
{
  MappingFilterData* data;
  CosNotifyFilter::ConstraintNotFound* notFound;
  CosNotifyFilter::MappingConstraintInfoSeq* constraints;
  data = getData();
  notFound = NULL;
  constraints = new CosNotifyFilter::MappingConstraintInfoSeq(id_list.length());
  MappingFilterData::MappingConstraintInfoTable::iterator iter;

  for (CORBA::ULong i=0; notFound == NULL && i < id_list.length(); i++ ){
    iter = data->assignedMappingConstraintInfoTable.find(id_list[i]);
    if ( iter == data->assignedMappingConstraintInfoTable.end() ){
      notFound = new CosNotifyFilter::ConstraintNotFound( id_list[ i ] );
    }
    else {
      (*constraints)[i] = 
        (CosNotifyFilter::MappingConstraintInfo)data->assignedMappingConstraintInfoTable[id_list[i]];
    }
  }

  if (notFound == NULL) {
    return constraints;
  } else {
    throw notFound;
  }
}

		
CosNotifyFilter::MappingConstraintInfoSeq* 
MappingFilterImpl::get_all_mapping_constraints()
{
  MappingFilterData* data = getData();
  //TIDNotifTrace.print(TIDNotifTrace.USER, GET_MAPPINGS_RULES); //TODO_MORFEO: Trace
  CosNotifyFilter::MappingConstraintInfoSeq* _constraints; 
  _constraints = 
    new CosNotifyFilter::MappingConstraintInfoSeq(data->assignedMappingConstraintInfoTable.size());
  int i = 0;
  MappingFilterData::MappingConstraintInfoTable::iterator iter;
  iter=data->assignedMappingConstraintInfoTable.begin();
  for (;iter!=data->assignedMappingConstraintInfoTable.end(); iter++) {
    (*_constraints)[i++] = 
      (CosNotifyFilter::MappingConstraintInfo) data->assignedMappingConstraintInfoTable[iter->first];
  }
  return _constraints;
}

			
void MappingFilterImpl::remove_all_mapping_constraints()
{
  MappingFilterData* data = getData();
		
  //TIDNotifTrace.print(TIDNotifTrace.USER, DELETE_ALL_MAPPING_RULES); //TODO_MORFEO: Trace

  data->assignedMappingConstraintInfoTable.clear();
  data->filterTable.clear();
		
  if (PersistenceManager::isActive()) {
  }

}

	
void MappingFilterImpl::destroy()
{
  // TODO Auto-generated method stub
}

			
CORBA::Boolean 
MappingFilterImpl::match(const CORBA::Any& filterable_data, 
                         CORBA::Any*& result_to_set)
  throw (CosNotifyFilter::UnsupportedFilterableData)
{
  MappingFilterData* data = getData();
  //TIDNotifTrace.print(TIDNotifTrace.DEBUG, MATCH); //TODO_MORFEO: Trace
  CORBA::Boolean ret = false;
  MappingFilterData::FilterTable::iterator e;
  MappingFilterData::MappingConstraintInfoTable::iterator f;

  if (data->filterTable.size() > 0) {

    for (e = data->filterTable.begin();e!=data->filterTable.end();e++){
      util::parser::TIDConstraint* tree = data->filterTable[e->first];

      util::parser::TypeValuePair result = 
        tree->check_event(filterable_data); 

      if (result.get_type() == util::parser::TypeValuePair::BOOLEAN_TYPE) {

        if (result.get_value_as_boolean()) {
          int key =(int) e->first;
          f = data->assignedMappingConstraintInfoTable.find(key); 
          
          if (f != data->assignedMappingConstraintInfoTable.end()) {
            CosNotifyFilter::MappingConstraintInfo& info = 
              (CosNotifyFilter::MappingConstraintInfo&) 
              data->assignedMappingConstraintInfoTable[key];
            result_to_set = new CORBA::Any(info.value);
            ret = true;
          }
        }
      }
    }
  } // if

  if (data->matches != NULL) {
    util::parser::TypeValuePair result = 
      data->matches->check_event(filterable_data);
    if (result.get_type() == util::parser::TypeValuePair::LONG_TYPE) {
      //TIDNotifTrace.print(TIDNotifTrace.USER, TO_DO_1); //TODO_MORFEO: Trace
      //TODO
    }
  }

  return ret;
}

			
CORBA::Boolean 
MappingFilterImpl::match_structured(const CosNotification::StructuredEvent& filterable_data, 
                                    CORBA::Any*& result_to_set)
  throw (CosNotifyFilter::UnsupportedFilterableData)
{
  // TODO Auto-generated method stub
  return false;
}

			
CORBA::Boolean 
MappingFilterImpl::match_typed(const CosNotification::PropertySeq& filterable_data, 
                               CORBA::Any*& result_to_set)
  throw (CosNotifyFilter::UnsupportedFilterableData)
{
  // TODO Auto-generated method stub
  return false;
}
	  		

	
 
};//namespace TIDNotif
