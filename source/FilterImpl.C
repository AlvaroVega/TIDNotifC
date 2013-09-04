/*
 *  File name: FilterImpl.C
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

#include "FilterImpl.h"
#include "TIDParser.h"
#include "TIDConstraint.h"
#include "TIDNotifConfig.h"
#include "PersistenceManager.h"

namespace TIDNotif{


//
// Constructors
//
  
FilterImpl::FilterImpl(CORBA::ORB_ptr orb)
  :_orb(CORBA::ORB::_duplicate(orb)), _current(NULL)
{
  // set the default _grammar
  _grammar = CORBA::string_dup(TIDNotif::util::parser::TIDParser::_CONSTRAINT_GRAMMAR);

  _tidorb = dynamic_cast < TIDorb::core::TIDORB* > ((CORBA::ORB*)orb);

}
  
FilterImpl::FilterImpl(CORBA::ORB_ptr orb, char* grammar)
  :_orb(orb), _current(NULL)
{
  if (strcmp(util::parser::TIDParser::_CONSTRAINT_GRAMMAR, grammar)) {
    throw CORBA::NO_IMPLEMENT();
  }

  _grammar = CORBA::string_dup(grammar);

  _tidorb = dynamic_cast < TIDorb::core::TIDORB* > ((CORBA::ORB*)orb);
}
  
FilterImpl::~FilterImpl()
{

}  
  
void FilterImpl::register_data(FilterData* data)
{
  if (_tidorb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "FilterImpl::register_data " << data->id;
    _tidorb->print_trace(TIDorb::util::TR_USER, msg.str().data());
  }
  _discriminators_table[data->id] = data;
}
  
void FilterImpl::unregister_data(FilterData* data)
{
  if (_tidorb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "FilterImpl::unregister_data " << data->id;
    _tidorb->print_trace(TIDorb::util::TR_USER, msg.str().data());
  }
  _discriminators_table.erase(data->id);
}
  
FilterData* FilterImpl::getData(const char* id )
{
  return (FilterData*)_discriminators_table[id];
}
  
  
CosNotifyFilter::ConstraintInfo&  
FilterImpl::add_constraint(const CosNotifyFilter::ConstraintExp& new_constraint)
{

  FilterData* discriminator = getData();

  if (_tidorb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "FilterImpl::add_constraint: {" << new_constraint.constraint_expr;
    msg << "} ";
    _tidorb->print_trace(TIDorb::util::TR_USER, msg.str().data());
  }

  util::parser::TIDConstraint* new_filter = NULL;

  try {
    TIDorb::util::StringBuffer filter;
    /* 
    //TODO_MORFEO: Aborted in parse
       if ( new_constraint.event_types.length() > 0 ) {
       filter.append( "(" );
       for ( int i=0; i < new_constraint.event_types.length(); i++ ){
       filter.append( " ( $type_name == '" )
       .append( new_constraint.event_types[i].type_name )
       .append( "' )" )
       .append( " and" )
       .append( " ( $domain_name == '" )
       .append(new_constraint.event_types[i].domain_name )
       .append( "' )" );
       if ( i < new_constraint.event_types.length() - 1 ) {
       filter.append( " or" );
       }
       }
       filter.append( " ) and " );
       }
    */
    filter << new_constraint.constraint_expr;
    new_filter = util::parser::TIDParser::parse(filter.str().data());
  } catch (const util::parser::ParsingErrorException& ex) { 
    if (_tidorb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "FilterImpl::add_constraint exception: " << ex.print_to_string().c_str();
      _tidorb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
    throw CosNotifyFilter::InvalidConstraint(new_constraint);
  }
    
  int new_key;
  int security_limit = 0;
  do {
    new_key = util::parser::TIDParser::newConstraintId();
    security_limit++;
    if (security_limit > util::parser::TIDParser::_MAX_CONSTRAINT_ID) {
      if (_tidorb->trace != NULL){
        _tidorb->print_trace(TIDorb::util::TR_ERROR, "To many constraints");
      }
      throw CORBA::NO_RESOURCES();
    }
  } while (discriminator->constraintTable.count(new_key));
    
  try {
    CosNotifyFilter::ConstraintInfo constraint_info(new_constraint, 
                                                    (CosNotifyFilter::ConstraintID) new_key);
    discriminator->constraintTable[new_key]=constraint_info;
    discriminator->filterTable[new_key]=new_filter;
    updateCounter(ADD_ONE, discriminator);
  } catch (const CORBA::Exception& ex) {
    // Por si lo que ha fallado es la segunda insercion
    discriminator->filterTable.erase(new_key);
    if (_tidorb->trace != NULL){
      _tidorb->print_trace(TIDorb::util::TR_ERROR, "FilterImpl::add_constraint", ex);
    }
    CosNotifyFilter::ConstraintInfo c_info = 
      (CosNotifyFilter::ConstraintInfo) (discriminator->constraintTable[new_key]);
    discriminator->constraintTable.erase(new_key);
    throw CosNotifyFilter::InvalidConstraint(c_info.constraint_expression);
  }
  
  if (_tidorb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "FilterImpl::add_constraint: {" << new_constraint.constraint_expr;
    msg << "} - Id = " << new_key;
    _tidorb->print_trace(TIDorb::util::TR_USER, msg.str().data());
  }
   
  //TIDNotifTrace.print(TIDNotifTrace.DEEP_DEBUG, ARBOL); //TODO_MORFEO: Trace
  //new_filter->dump("   "); //TODO_MORFEO: free
  if (PersistenceManager::isActive()) {  
    PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_CONSTRAINTS, 
                                             discriminator);
  }
  return discriminator->constraintTable[new_key];
}
  
  
  
  
CosNotifyFilter::ConstraintID 
FilterImpl::replace_constraint( CosNotifyFilter::ConstraintInfo& new_constraint )
{
  FilterData* discriminator = getData();
  int key = (int) new_constraint.constraint_id;

  if (_tidorb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "FilterImpl::replace_constraint: Id = " << key;
    msg << " {" << new_constraint.constraint_expression.constraint_expr << "}";
    _tidorb->print_trace(TIDorb::util::TR_USER, msg.str().data());
  }
  if (discriminator->constraintTable.find(key)==discriminator->constraintTable.end()) {
    throw CosNotifyFilter::ConstraintNotFound( key );
  }
    
  util::parser::TIDConstraint* new_filter = NULL;
  try {
    new_filter = 
      util::parser::TIDParser::parse(new_constraint.constraint_expression.constraint_expr.in());
  } catch (const util::parser::ParsingErrorException& ex) {
    if (_tidorb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "FilterImpl::replace_constraint exception: " << ex.print_to_string().c_str();
      _tidorb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
    throw CosNotifyFilter::InvalidConstraint( new_constraint.constraint_expression );
  }
    
  // Reemplazamos la Constraint
  const CosNotifyFilter::ConstraintInfo & replacedConstraint = 
    ( CosNotifyFilter::ConstraintInfo ) discriminator->constraintTable[key];
  discriminator->constraintTable[key]= new_constraint;
  
  /*if ( replacedConstraint != NULL ) {
    FOUND_REPLACED_CONSTRAINT[1] = replacedConstraint.constraint_expression.constraint_expr;
    TIDNotifTrace.print(TIDNotifTrace.DEBUG, FOUND_REPLACED_CONSTRAINT);
    } else {
    TIDNotifTrace.print(TIDNotifTrace.DEBUG, NOT_FOUND_REPLACED_CONSTRAINT);
    }*/ //TODO_MORFEO: Trace
    
  // Reemplazamos el arbol
  util::parser::EvaluableNode* replacedFilter;
  replacedFilter = (util::parser::EvaluableNode*) discriminator->filterTable[key];
  discriminator->filterTable[key]=new_filter;
    
  /*if ( replacedFilter != NULL ) {
    TIDNotifTrace.print(TIDNotifTrace.DEBUG, FOUND_ARBOL);
    } else {
    TIDNotifTrace.print(TIDNotifTrace.DEBUG, NOT_FOUND_ARBOL);
    }*/ //TODO_MORFEO: Trace
    
  if (PersistenceManager::isActive()) {
    PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_CONSTRAINTS,
                                             discriminator);
  }
  return replacedConstraint.constraint_id;
}
  
void FilterImpl::remove_constraint( int id )
{
  //TODO_MORFEO: this method is not necessary because 
  //modify_constrait can be used both to remove constraint and modify constraint
  FilterData* discriminator = getData();

  if (_tidorb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "FilterImpl::remove_constraint: Id = " << id; 
    _tidorb->print_trace(TIDorb::util::TR_USER, msg.str().data());
  }

  FilterData::ConstraintTable::iterator iter = 
    discriminator->constraintTable.find(id);

  if (iter == discriminator->constraintTable.end()) {
    throw CosNotifyFilter::ConstraintNotFound(id);
  }
  updateCounter(SUB_ONE, discriminator);
  
  // Eliminamos la Constraint
  
    
  /*  if ( discriminator->constraintTable.find(id)!=discriminator->constraintTable.end()) {
        const CosNotifyFilter::ConstraintInfo & removedConstraint = discriminator->constraintTable[id] ; 
        FOUND_CONSTRAINT[1] = removedConstraint.constraint_expr;
        TIDNotifTrace.print(TIDNotifTrace.DEBUG, FOUND_CONSTRAINT);
        } else {
        TIDNotifTrace.print(TIDNotifTrace.DEBUG, NOT_FOUND_CONSTRAINT);
        }*/ //TOD_MORFEO: Trace
    
  discriminator->constraintTable.erase(id);
  
  
  
  // Eliminamos el arbol
  discriminator->filterTable.erase(id); //TODO_MORFEO: free memory
  
  /*    util::parser::EvaluableNode* removedFilter;   //TODO_MORFEO: Trace
    removedFilter = (util::parser::EvaluableNode*) 
                
    if ( removedFilter != null ) {
                TIDNotifTrace.print(TIDNotifTrace.DEBUG, FOUND_ARBOL);
    } else {
                TIDNotifTrace.print(TIDNotifTrace.DEBUG, NOT_FOUND_ARBOL);
    }
  */
    if (PersistenceManager::isActive()) {
      PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_CONSTRAINTS,
                                               discriminator);
    }
  }
      
       
char* FilterImpl::constraint_grammar()
{
  if (_tidorb->trace != NULL){
    TIDorb::util::StringBuffer msg;
    msg << "FilterImpl::constraint_grammar: " << _grammar;
    _tidorb->print_trace(TIDorb::util::TR_USER, msg.str().data());
  }
  return CORBA::string_dup(_grammar);
}

    
CosNotifyFilter::ConstraintInfoSeq* 
FilterImpl::add_constraints(const CosNotifyFilter::ConstraintExpSeq& constraint_list)
  throw (CosNotifyFilter::InvalidConstraint)
{
  int length = constraint_list.length();

  if ( length > 0) {   
    CORBA::ULong i;
    const CosNotifyFilter::InvalidConstraint * error = NULL;

    CosNotifyFilter::ConstraintInfoSeq * info_list = 
      new CosNotifyFilter::ConstraintInfoSeq(length);
    info_list->length(length);


    for (i = 0; (error == NULL) && (i < length); i++) {
      try {
        (*info_list)[i] = add_constraint(constraint_list[i]);
      } catch (const CosNotifyFilter::InvalidConstraint& ic) {
        error = new CosNotifyFilter::InvalidConstraint(ic);
      } catch (const exception& thw) {
        error = new CosNotifyFilter::InvalidConstraint(constraint_list[i]);
      }
    }

    if (error != NULL) {
      for (CORBA::Long j = i - 1; j >= 0; j--) {

        try {
          remove_constraint((*info_list)[j].constraint_id); 
        } catch (const CosNotifyFilter::ConstraintNotFound& cnf) {
        } catch (const exception& thw) {
        }
          
      }
      delete info_list;
      throw CosNotifyFilter::InvalidConstraint( 
                   (const CosNotifyFilter::InvalidConstraint&)(*error) );
    }
    return info_list;
  } else {
    throw CosNotifyFilter::InvalidConstraint();
  }
}

    
void FilterImpl::modify_constraints(const CosNotifyFilter::ConstraintIDSeq& del_list, 
                                    const CosNotifyFilter::ConstraintInfoSeq& modify_list)
  throw (CosNotifyFilter::InvalidConstraint, CosNotifyFilter::ConstraintNotFound)
{
  bool not_found = false;
  bool invalidConstraint = false;
  CosNotifyFilter::ConstraintID id_error;
  const CosNotifyFilter::ConstraintExp * constraint_expression_error;

  FilterData* data;
  data = getData();

  int* del_list_keys;
  int* modify_list_keys;


  /**
   * Check preconditions: every constraint referenced must exist
   */
  FilterData::ConstraintTable::iterator iteratorTable;
  FilterData::ConstraintTable::iterator end = data->constraintTable.end();

  CORBA::ULong del_list_length = del_list.length();

  if (del_list_length > 0) {
    del_list_keys = new int[del_list_length];

    for (CORBA::ULong i = 0; (!not_found) && (i < del_list_length); i++) {
      del_list_keys[i] = del_list[i];
      iteratorTable = data->constraintTable.find(del_list_keys[i]);
      if (iteratorTable == end) { 
        id_error = del_list[i];
        not_found = true;
      }
    }//for

  } else {
    del_list_keys = NULL;
  }


  CORBA::ULong modify_list_length = modify_list.length();

  if (modify_list_length > 0) {
    modify_list_keys = new int[modify_list_length];
        
    for (CORBA::ULong i = 0; (!not_found) && (i < modify_list_length); i++) {
      modify_list_keys[i] = (int) modify_list[i].constraint_id;
      iteratorTable = data->constraintTable.find(modify_list_keys[i]);
      if (iteratorTable == end) { 
        id_error = modify_list_keys[i];
        not_found = true;
      }
    }//for
  } else {
    modify_list_keys = NULL;
  }

  /**
   * Perform changes...
   */
  if (!not_found) {
    /**
     * Constraint removal. Store a backup array in case of error
     */
    util::parser::TIDConstraint * removedFilters[del_list_length];

    CosNotifyFilter::ConstraintInfoSeq* removedConstraints;
    removedConstraints = new CosNotifyFilter::ConstraintInfoSeq(del_list_length);
    removedConstraints->length(del_list_length);

    for (CORBA::ULong i = 0; i < del_list_length; i++) {
      updateCounter(SUB_ONE, data);
      (*removedConstraints)[i] = 
        (CosNotifyFilter::ConstraintInfo) data->constraintTable[del_list_keys[i]];
      data->constraintTable.erase(del_list_keys[i]);

      if (_tidorb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "FilterImpl::modify_constraints: Constraint {";
        msg << (*removedConstraints)[i].constraint_expression.constraint_expr << "}";
        _tidorb->print_trace(TIDorb::util::TR_USER, msg.str().data());
      }

      removedFilters[i] = data->filterTable[del_list_keys[i]];
      data->filterTable.erase(del_list_keys[i]);

      if (removedFilters[i] != NULL) {
        if (_tidorb->trace != NULL)
          _tidorb->print_trace(TIDorb::util::TR_USER, 
                               "FilterImpl::modify_constraints at: related tree removed");
      } else {
        if (_tidorb->trace != NULL)
          _tidorb->print_trace(TIDorb::util::TR_USER, 
                               "FilterImpl::modify_constraints at: related tree not found");
      }
    }

    /**
     * Constraint replace. Note, if some constraint to be modified was removed
     * in the previous step, it will be inserted as the spec doesn't
     * tells anything about it
     */
    util::parser::TIDConstraint * replacedFilters[modify_list_length];

  
    CosNotifyFilter::ConstraintInfoSeq* replacedConstraints;
    replacedConstraints = new CosNotifyFilter::ConstraintInfoSeq(modify_list_length);
    replacedConstraints->length(0);


    for (CORBA::ULong i = 0; !invalidConstraint && !not_found && i < modify_list_length; i++) {

      if (_tidorb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "FilterImpl::modify_constraints: replace Constraint Id = " << i;
        msg << "{";
        msg << modify_list[i].constraint_expression.constraint_expr << "}";
        _tidorb->print_trace(TIDorb::util::TR_USER, msg.str().data());
      }

      util::parser::TIDConstraint* new_filter = NULL;
      try { 
        new_filter = util::parser::TIDParser::parse(
                                modify_list[i].constraint_expression.constraint_expr.in());
      } catch (const util::parser::ParsingErrorException& ex) {
        if (_tidorb->trace != NULL){
          TIDorb::util::StringBuffer msg;
          msg << "FilterImpl::modify_constraints: ERROR parsing Constraint Id = " << i;
          msg << "{";
          msg << modify_list[i].constraint_expression.constraint_expr << "}";
          _tidorb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
        }
        invalidConstraint = true;
        constraint_expression_error = &modify_list[i].constraint_expression;
      }

      if (!invalidConstraint) {
        // Reemplazamos la Constraint
        iteratorTable = data->constraintTable.find(modify_list_keys[i]);
            
            
        if (iteratorTable!= data->constraintTable.end()) {
          replacedConstraints->length(replacedConstraints->length()+1);
          (*replacedConstraints)[i] = 
            (CosNotifyFilter::ConstraintInfo) data->constraintTable[modify_list_keys[i]];
          data->constraintTable[modify_list_keys[i]] = modify_list[i];
            
          if (_tidorb->trace != NULL){
            TIDorb::util::StringBuffer msg;
            msg << "FilterImpl::modify_constraints: replace old constraint Id = " << i;
            msg << "{";
            msg << (*replacedConstraints)[i].constraint_expression.constraint_expr.in() << "}";
            _tidorb->print_trace(TIDorb::util::TR_USER, msg.str().data());
          }

        } else {
          //TODO_MORFEO:the constraint was removed before so we throw Not_Found
          not_found = true;
          id_error = modify_list_keys[i];

          if (_tidorb->trace != NULL){
            TIDorb::util::StringBuffer msg;
            msg << "FilterImpl::modify_constraints: not found old constraint";
            _tidorb->print_trace(TIDorb::util::TR_USER, msg.str().data());
          }

          /**
           * update constraints counter value as it was decremented upon
           * constraint removal
           */
          //updateCounter(ADD_ONE, data);
        }

        // Reemplazamos el arbol
        replacedFilters[i] = data->filterTable[modify_list_keys[i]];
        data->filterTable[modify_list_keys[i]] = new_filter;

        if (replacedFilters[i] != NULL) {
          if (_tidorb->trace != NULL)
            _tidorb->print_trace(TIDorb::util::TR_USER, 
                                 "FilterImpl::modify_constraints at replacing: related tree removed");
        } else {
          if (_tidorb->trace != NULL)
            _tidorb->print_trace(TIDorb::util::TR_USER, 
                                 "FilterImpl::modify_constraints at replacing: related tree not found");
        }

      }//if invalidConstraint == null

    }//for

    //TODO_MORFEO: free_memory

    if (invalidConstraint || not_found) {
      /**
       * Restore previus.constraint_expression.constraint_expr changes...
       */
      for (int i = replacedConstraints->length()-1; i>= 0 ;i--) {
        data->constraintTable[modify_list_keys[i]] = (*replacedConstraints)[i];
        data->filterTable[modify_list_keys[i]] = replacedFilters[i];
      }// for

      for (int i = removedConstraints->length()-1; i>=0; i--) {
        iteratorTable = data->constraintTable.find(del_list_keys[i]);
        if (iteratorTable == data->constraintTable.end()){
          data->constraintTable[del_list_keys[i]] = (*removedConstraints)[i];
          updateCounter(ADD_ONE, data);
        }
        data->filterTable[del_list_keys[i]] = removedFilters[i];
      }// for

      if (not_found)
        throw CosNotifyFilter::ConstraintNotFound(id_error);
      else
        throw CosNotifyFilter::InvalidConstraint(*constraint_expression_error); 

    } else {
      delete removedConstraints;
      delete replacedConstraints;
      for (CORBA::ULong i = 0; i < del_list_length; i++) {
        delete removedFilters[i];
      }
      for (CORBA::ULong i = 0; i < modify_list_length; i++)  {
        delete replacedFilters[i];
      }
      if (PersistenceManager::isActive()) {
        PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_CONSTRAINTS, data);
      }
    }
  } else {
    throw CosNotifyFilter::ConstraintNotFound(id_error);
  }
      
}

    
CosNotifyFilter::ConstraintInfoSeq* 
FilterImpl::get_constraints(const CosNotifyFilter::ConstraintIDSeq& id_list)
  throw (CosNotifyFilter::ConstraintNotFound)
{   
  FilterData* data;
  data = getData();

  CORBA::ULong id_list_length = id_list.length();

  CosNotifyFilter::ConstraintInfoSeq* _constraints;
  _constraints = new CosNotifyFilter::ConstraintInfoSeq(id_list_length);
  _constraints->length(id_list_length);

  FilterData::ConstraintTable::iterator iter;
  FilterData::ConstraintTable::iterator end = data->constraintTable.end();

  for ( CORBA::ULong i=0; i < id_list_length; i++ ) {
        
    iter = data->constraintTable.find((int) id_list[ i ]);
    if (iter != end)
      {
        (*_constraints)[ i ] = (CosNotifyFilter::ConstraintInfo )
          (data->constraintTable[ (int) id_list[ i ] ]);
      }
    else
      {
        throw CosNotifyFilter::ConstraintNotFound( id_list[ i ] );
      }
  }
  return _constraints;
}

    
CosNotifyFilter::ConstraintInfoSeq* FilterImpl::get_all_constraints()
{
  FilterData* discriminator = getData();

  if (_tidorb->trace != NULL){
    _tidorb->print_trace(TIDorb::util::TR_USER, "FilterImpl::get_all_constraints ");
  }

  CosNotifyFilter::ConstraintInfoSeq* _constraints; 
  _constraints = new CosNotifyFilter::ConstraintInfoSeq();
  _constraints->length(discriminator->constraintTable.size());

  int i = 0;
  FilterData::ConstraintTable::iterator iter;
  FilterData::ConstraintTable::iterator begin = 
    discriminator->constraintTable.begin();
  FilterData::ConstraintTable::iterator end = 
    discriminator->constraintTable.end();

  for(iter = begin; iter != end; iter++){
    
    (*_constraints)[i++] = (CosNotifyFilter::ConstraintInfo)
      discriminator->constraintTable[(*iter).first];
  }
  return _constraints;
}

    
void FilterImpl::remove_all_constraints()
{
  FilterData* data = getData();

  if (_tidorb->trace != NULL){
    _tidorb->print_trace(TIDorb::util::TR_USER, "FilterImpl::remove_all_constraints ");
  }

  updateCounter(SUB_ONE, data);
    
  data->constraintTable.clear();
  data->filterTable.clear(); //TODO_MORFEO: to free memory

  updateCounter(RESET, data);

  if (PersistenceManager::isActive()) {
    PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_CONSTRAINTS,data);
  }
}

void FilterImpl::destroy(){
  string id = getData()->id;
  //TODO_MORFEO: free memory

  if (PersistenceManager::isActive()) {
    PersistenceManager::getDB()->delete_data(getData());
  }
  
  _discriminators_table.erase(id);
    
}

    
CORBA::Boolean FilterImpl::match(const CORBA::Any& filterable_data)
  throw (CosNotifyFilter::UnsupportedFilterableData)
{
  FilterData* discriminator = getData();

  FilterData::FilterTable::iterator it;
  FilterData::FilterTable::iterator begin = 
    discriminator->filterTable.begin();
  FilterData::FilterTable::iterator end = 
    discriminator->filterTable.end(); 
  
  CORBA::Boolean ret = true;
 
  for(it = begin; (it != end) && ret; it++) {

    util::parser::TypeValuePair result = 
      discriminator->filterTable[(*it).first]->check_event(filterable_data);
    
    try {
      ret = result.get_value_as_boolean();
    }
    catch (const util::parser::TypeValuePair::TypeCheckError & e) {    
      throw CosNotifyFilter::UnsupportedFilterableData();
    }

  }
  return ret;
}

    
CORBA::Boolean 
FilterImpl::match_structured(const CosNotification::StructuredEvent& filterable_data)
 throw (CosNotifyFilter::UnsupportedFilterableData)
{
     
  CORBA::Any any; 
  CosNotification::_StructuredEventHelper::insert(any, filterable_data );
  return match(any);

}

    
CORBA::Boolean FilterImpl::match_typed(const CosNotification::PropertySeq& filterable_data)
  throw (CosNotifyFilter::UnsupportedFilterableData)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

    
CosNotifyFilter::CallbackID 
FilterImpl::attach_callback(CosNotifyComm::NotifySubscribe_ptr callback)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

    
void FilterImpl::detach_callback(CosNotifyFilter::CallbackID callback)
  throw (CosNotifyFilter::CallbackNotFound)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

    
CosNotifyFilter::CallbackIDSeq* FilterImpl::get_callbacks()
{
  return NULL; 
  //throw CORBA::NO_IMPLEMENT("No implemented");
}
      
  

//
// Temas del default Servant
//
//
void FilterImpl::setCurrent()
{
  TIDThr::Synchronized sync(_recursive_mutex);

  if (_current == NULL) {
     
    try {

      CORBA::Object_var obj = _orb->resolve_initial_references("POACurrent");

      _current = PortableServer::_CurrentHelper::narrow(obj, true);

    } catch (const CORBA::Exception & ex) {
      if (_tidorb->trace != NULL){
        TIDorb::util::StringBuffer msg;
        msg << "FilterImpl::setCurrent Exception: ";
        _tidorb->print_trace(TIDorb::util::TR_ERROR, msg.str().data(), ex);
      }
      throw CORBA::INTERNAL();
    }
  } 
      
  //TODO_MORFEO: error: passing `const TIDorb::portable::ORB' as 
  //`this' argument of `virtual CORBA::Object* 
  //CORBA::ORB::resolve_initial_references(const char*)' discards qualifiers
  //so the solution is doing copy of orb.
}



FilterData* FilterImpl::getData()
{
  if (_current == NULL)
    setCurrent();

  try {
    TIDorb::util::StringBuffer bufferId;  
    PortableServer::ObjectId* objectId = _current->get_object_id();
    for (CORBA::ULong i = 0; i < objectId->length(); i++) { //TODO_MORFEO: Test
      bufferId << (*objectId)[i];
    }
    delete objectId;
    FilterData* data = (FilterData*) _discriminators_table[bufferId.str().data()];
    if (data != NULL) {
      return data;
    } else {
      throw CORBA::OBJECT_NOT_EXIST();
    }
  } catch (const CORBA::Exception ex) {
    if (_tidorb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "FilterImpl::getData Exception: ";
      _tidorb->print_trace(TIDorb::util::TR_ERROR, msg.str().data(), ex);
    }
    throw CORBA::INV_OBJREF();
  }
}
  
  
void FilterImpl::updateCounter(int op, FilterData* data)
{ 
  TIDThr::Synchronized sync(_recursive_mutex);

  switch ( op ){
  case ADD_ONE:
    data->filter_counter++;
    break;
  case SUB_ONE:
    data->filter_counter--;
    break;
  case RESET:
    data->filter_counter = 0;
    break;
  default:
    if (_tidorb->trace != NULL){
      TIDorb::util::StringBuffer msg;
      msg << "FilterImpl::updateCounter op " << op << " unexpected";
      _tidorb->print_trace(TIDorb::util::TR_ERROR, msg.str().data());
    }
    break;
  }
}

  
  

} //namespace TIDNotif

