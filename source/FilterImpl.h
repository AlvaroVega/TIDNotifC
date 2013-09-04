// -*- c++ -*-
/*
 *  File name: FilterImpl.h
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

#ifndef _TIDNOTIF_FILTERIMPL_H_
#define _TIDNOTIF_FILTERIMPL_H_ 

#include "CORBA.h"
#include "POA_CosNotifyFilter.h"
#include "CosNotifyFilter.h"
#include "PortableServer.h"
#include "FilterData.h"
#include "TIDorb/core.h"
#include <map>


namespace TIDNotif{

class FilterImpl : public virtual POA_CosNotifyFilter::Filter
{
 
  friend class FilterFactoryImpl;


  //
  // Fields
  //

protected:
  //TODO_MORFEO: FilterData or FilterData*
  typedef map<string, FilterData*> Hashtable_FilterData;  
  
  // List of Discriminators (Pack)
  Hashtable_FilterData _discriminators_table;


public:

  //
  // Constructors
  //
  FilterImpl(CORBA::ORB_ptr orb);

  FilterImpl(CORBA::ORB_ptr orb, char*);

  ~FilterImpl();



  void register_data(FilterData* data); //TODO_MORFEO: renamed from register like register_data

  void unregister_data(FilterData* data); //TODO_MORFEO: renamed from unregisterlike unregister_data

  FilterData* getData(const char* id );


  CosNotifyFilter::ConstraintInfo&  
  add_constraint(const CosNotifyFilter::ConstraintExp& new_constraint);

  CosNotifyFilter::ConstraintID 
  replace_constraint(CosNotifyFilter::ConstraintInfo& new_constraint );

  void remove_constraint( int id ); //TODO_MORFEO: this method is not necessary because 
  //modify_constrait can be used both to remove constraint and modify constraint



  char* constraint_grammar();


  CosNotifyFilter::ConstraintInfoSeq* 
  add_constraints(const CosNotifyFilter::ConstraintExpSeq& constraint_list)
    throw (CosNotifyFilter::InvalidConstraint);

  void modify_constraints(const CosNotifyFilter::ConstraintIDSeq& del_list, 
                          const CosNotifyFilter::ConstraintInfoSeq& modify_list) 
    throw (CosNotifyFilter::InvalidConstraint, CosNotifyFilter::ConstraintNotFound);


  CosNotifyFilter::ConstraintInfoSeq* 
  get_constraints(const CosNotifyFilter::ConstraintIDSeq& id_list)
    throw (CosNotifyFilter::ConstraintNotFound);


  CosNotifyFilter::ConstraintInfoSeq* get_all_constraints();

  void remove_all_constraints();


  void destroy();


  CORBA::Boolean match(const CORBA::Any& filterable_data)
    throw (CosNotifyFilter::UnsupportedFilterableData);


  CORBA::Boolean 
  match_structured(const CosNotification::StructuredEvent& filterable_data)
    throw (CosNotifyFilter::UnsupportedFilterableData);


  CORBA::Boolean 
  match_typed(const CosNotification::PropertySeq& filterable_data)
    throw (CosNotifyFilter::UnsupportedFilterableData);


  CosNotifyFilter::CallbackID 
  attach_callback(CosNotifyComm::NotifySubscribe_ptr callback);


  void detach_callback(CosNotifyFilter::CallbackID callback)
    throw (CosNotifyFilter::CallbackNotFound);

  CosNotifyFilter::CallbackIDSeq* get_callbacks();


private:	

  static const int ADD_ONE = 0;
  static const int SUB_ONE = 1;
  static const int RESET   = 2;


  CORBA::String_var _grammar;

  CORBA::ORB_var _orb;

  TIDorb::core::TIDORB* _tidorb;

  // Default Servant Current POA
  PortableServer::Current_ptr _current;

  TIDThr::RecursiveMutex _recursive_mutex;	


  //
  // default Servant
  //

  void setCurrent();  

  FilterData* getData();


  void updateCounter(int op, FilterData* data); 

};
}; //namespace TIDNotif
#endif
