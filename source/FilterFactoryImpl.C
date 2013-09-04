/*
 *  File name: FilterFactoryImpl.C
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

#include "FilterFactoryImpl.h"
#include "FilterData.h"
#include "FilterImpl.h"
#include "NotifReference.h"
#include "TIDParser.h"
#include "PersistenceManager.h"
#include "MappingFilterData.h"
#include "MappingFilterImpl.h"
#include "ThePOAFactory.h"


#include <stdlib.h>


namespace TIDNotif { 		


const char * FilterFactoryImpl::GLOBAL_FILTER_POA_ID = 
"GlobalFilterPOA";

const char * FilterFactoryImpl::GLOBAL_MAPPING_FILTER_POA_ID = 
"GlobalMappingFilterPOA";

const char * FilterFactoryImpl::CREATE_FILTER[3] = 
  { "-> FilterFactoryImpl.createFilter( ", NULL, " )" };

const char * FilterFactoryImpl::CREATE_MAPPING_FILTER[3] = 
  { "-> FilterFactoryImpl.createMappintFilter( ", NULL, " )" };	


FilterFactoryImpl::FilterFactoryImpl(CORBA::ORB_ptr orb)
  : _orb(CORBA::ORB::_duplicate(orb)), uid(0)
{
  _tidorb = dynamic_cast < TIDorb::core::TIDORB* > ((CORBA::ORB_ptr)_orb);
}


FilterFactoryImpl::~FilterFactoryImpl()
{
}
	
CosNotifyFilter::Filter_ptr 
FilterFactoryImpl::get_filter( int filterId )
{

  FilterData* filterData;
  TIDorb::util::StringBuffer buffer_id;
  buffer_id << filterId;
  
  try {
    filterData = (dynamic_cast <FilterImpl*> 
                  ((globalFilterPOA()->get_servant())))->getData(
                                                          buffer_id.str().data());
				
    return NotifReference::discriminatorReference(filterData->poa,
                                                  buffer_id.str().data());
  } catch (const CORBA::Exception& e){
    if (_tidorb->trace != NULL)
      _tidorb->print_trace(TIDorb::util::TR_ERROR, 
                           "FilterFactoryImpl::get_filter unexpected exception", e);
    throw CORBA::OBJECT_NOT_EXIST();
  }
}
	
	
CosNotifyFilter::Filter_ptr 
FilterFactoryImpl::create_filter(const char* constraint_grammar)
  throw (CosNotifyFilter::InvalidGrammar)
{

  FilterFactoryImpl::CREATE_FILTER[1] = constraint_grammar;
		

  if (_tidorb->trace != NULL)
    _tidorb->print_trace(TIDorb::util::TR_USER, 
                         "FilterFactoryImpl::crete_filter ");
			
  if (strcmp(constraint_grammar, util::parser::TIDParser::_CONSTRAINT_GRAMMAR)) 
  {
    throw CosNotifyFilter::InvalidGrammar();
  }
  PortableServer::POA_ptr poa = globalFilterPOA();
  TIDorb::util::StringBuffer buffer_id;
  try {
    if (PersistenceManager::isActive())
      buffer_id << PersistenceManager::getDB()->getUID();
    else
      buffer_id << "0";
  }
  catch (const CORBA::Exception& e1) {
    if (_tidorb->trace != NULL)
      _tidorb->print_trace(TIDorb::util::TR_ERROR, 
                           "FilterFactoryImpl::crete_filter Persistence Manager failed", e1);
    throw CORBA::INTERNAL("Persistence Manager failed");
  }
  FilterData* filterData = new FilterData(buffer_id.str().data(), poa);

  try {
    (dynamic_cast<FilterImpl*> (poa->get_servant()))->register_data( filterData );
  } catch (CORBA::Exception& e) {}

  if (PersistenceManager::isActive()) {
    (PersistenceManager::getDB())->save_data( filterData );
    (PersistenceManager::getDB())->update_data(PersistenceDB::ATTR_DISCRIMINATOR, 
                                               filterData);
  }
  
  return NotifReference::discriminatorReference(filterData->poa,
                                                filterData->id);
}
  
CosNotifyFilter::MappingFilter_ptr 
FilterFactoryImpl::create_mapping_filter(const char* constraint_grammar, 
                                         const CORBA::Any& default_value)
  throw (CosNotifyFilter::InvalidGrammar)
{
  
  FilterFactoryImpl::CREATE_MAPPING_FILTER[1] = constraint_grammar;

  if (_tidorb->trace != NULL)
      _tidorb->print_trace(TIDorb::util::TR_USER, 
                           "FilterFactoryImpl::crete_mapping_filter");

  PortableServer::POA_ptr poa = globalMappingDiscriminatorPOA();
  TIDorb::util::StringBuffer buffer_id;
  try {
    if (PersistenceManager::isActive())
      buffer_id << PersistenceManager::getDB()->getUID();
    else
      buffer_id << "0";
  }
  catch (const CORBA::Exception& e1) {
    if (_tidorb->trace != NULL)
      _tidorb->print_trace(TIDorb::util::TR_ERROR, 
                           "FilterFactoryImpl::crete_mapping_filter Persistence Manager failed", 
                           e1);
    throw CORBA::INTERNAL("Persistence Manager failed");
  }
  MappingFilterData* filterData = new MappingFilterData(buffer_id.str().data(), 
                                                        default_value);
  
  try {
    (dynamic_cast<MappingFilterImpl*> (poa->get_servant()))->register_data( filterData );
  } 
  catch (const CORBA::Exception& e) {
  }
  
  if (PersistenceManager::isActive()) {
    PersistenceManager::getDB()->save_data( filterData );
    PersistenceManager::getDB()->update_data(PersistenceDB::ATTR_DISCRIMINATOR, 
                                             filterData);
  }
  
  return NotifReference::mappingDiscriminatorReference(filterData->poa,
                                                       filterData->id);
  
}
  
  
  
PortableServer::POA_ptr FilterFactoryImpl::globalFilterPOA(){

  PortableServer::POA_ptr the_poa;
  the_poa = ThePOAFactory::getGlobalPOA(GLOBAL_FILTER_POA_ID);
  
  if (the_poa == NULL) {
    
    the_poa = 
      ThePOAFactory::createGlobalPOA(GLOBAL_FILTER_POA_ID,
                                     ThePOAFactory::GLOBAL_FILTER_POA, NULL );
    try {
      the_poa->get_servant();
    } catch (PortableServer::POA::NoServant& ex) {
      try {
        the_poa->set_servant(new FilterImpl(_orb));
      } catch (const CORBA::Exception& e) {
        if (_tidorb->trace != NULL)
          _tidorb->print_trace(TIDorb::util::TR_ERROR, 
                               "FilterFactoryImpl::globalFilterPOA error NoServant", e);
      }
    } catch (const PortableServer::POA::WrongPolicy& ex) {
      if (_tidorb->trace != NULL)
        _tidorb->print_trace(TIDorb::util::TR_ERROR, 
                             "FilterFactoryImpl::globalFilterPOA error WrongPolicy", ex);
    } catch (...) {
      if (_tidorb->trace != NULL)
        _tidorb->print_trace(TIDorb::util::TR_ERROR, 
                             "FilterFactoryImpl::globalFilterPOA error Unknowed exception");
    }

  }
  return the_poa;
}


PortableServer::POA_ptr 
FilterFactoryImpl::globalMappingDiscriminatorPOA(){

  PortableServer::POA_ptr the_poa; 
  the_poa = ThePOAFactory::getGlobalPOA(GLOBAL_MAPPING_FILTER_POA_ID);
  
  if (the_poa == NULL) {

    the_poa = ThePOAFactory::createGlobalPOA( 
                                 GLOBAL_MAPPING_FILTER_POA_ID,
                                 ThePOAFactory::GLOBAL_MAPPING_FILTER_POA, 
                                 NULL );
    try {
      the_poa->get_servant();
    } catch (const PortableServer::POA::NoServant& ex) {
      try {
        the_poa->set_servant(new MappingFilterImpl(_orb));
      } catch (const CORBA::Exception& e) {
        if (_tidorb->trace != NULL)
          _tidorb->print_trace(TIDorb::util::TR_ERROR, "CORBA::Exception", ex);
      }
    } catch (const PortableServer::POA::WrongPolicy& ex) {
      if (_tidorb->trace != NULL)
        _tidorb->print_trace(TIDorb::util::TR_ERROR, "WrongPolicy", ex);
    }
  }
  return the_poa;
}
  
  
void FilterFactoryImpl::writeObject(ostream & out){  

  FilterImpl* filter = NULL;
  try {
    filter = dynamic_cast<FilterImpl*> (globalFilterPOA()->get_servant());

  } catch (const PortableServer::POA::NoServant& e1) {

  } catch (const PortableServer::POA::WrongPolicy& e2) {

  }
  
  FilterImpl::Hashtable_FilterData::iterator it;
  FilterImpl::Hashtable_FilterData::iterator begin = 
    filter->_discriminators_table.begin();
  FilterImpl::Hashtable_FilterData::iterator end = 
    filter->_discriminators_table.end();
  
  out<<filter->_discriminators_table.size()<<endl;
  
  for(it = begin; it != end; it++ ) {	    	    
    FilterData* filterData = filter->_discriminators_table[((*it).first)];
    filterData->writeObject(out);
  }	
  
  
  MappingFilterImpl* mappingFilter = NULL;
  
  try {
    mappingFilter = 
      dynamic_cast<MappingFilterImpl*>(globalMappingDiscriminatorPOA()->get_servant());
  }
  catch (const PortableServer::POA::NoServant& e1) {
  }
  catch (const PortableServer::POA::WrongPolicy& e2) {
  }
  
  
  MappingFilterImpl::Hashtable_MappingFilterData::iterator iter;
  MappingFilterImpl::Hashtable_MappingFilterData::iterator begin2 =
    mappingFilter->_mapping_discriminators_table.begin();
  MappingFilterImpl::Hashtable_MappingFilterData::iterator end2 =
    mappingFilter->_mapping_discriminators_table.end();

  out << mappingFilter->_mapping_discriminators_table.size();

  for(iter = begin2; iter != end2; iter++) {
    MappingFilterData* mappingFilterData = 
      mappingFilter->_mapping_discriminators_table[((*iter).first)];
    mappingFilterData->writeObject(out);
  }	
  
}



void FilterFactoryImpl::readObject(istream & input){
  
  // Filters
  FilterImpl* filter = NULL;
  try {
    filter = dynamic_cast<FilterImpl*> (globalFilterPOA()->get_servant());
  } catch (PortableServer::POA::NoServant& e) {
  } catch (PortableServer::POA::WrongPolicy e) {
  }
  int size;
  input >> size;  
  
  
  string id;
  FilterData * data = NULL;
  
  for(int i = 0; i < size; i++) {
    input>>id;
    
    try {
      data = PersistenceManager::getDB()->load_d(id);
      filter->register_data(data);                
    }
    catch (CORBA::Exception& e) {
      if (_tidorb->trace != NULL)
        _tidorb->print_trace(TIDorb::util::TR_ERROR, 
                             "FilterFactoryImpl::readObject error reading filters ", e);
    }	        
  }
  
  // MappingFilters
  MappingFilterImpl* mappingFilter = NULL;
  
  try {
    mappingFilter = dynamic_cast<MappingFilterImpl*> 
      (globalMappingDiscriminatorPOA()->get_servant());
  } catch (PortableServer::POA::NoServant& e) {

  } catch (PortableServer::POA::WrongPolicy& e) {

  }
  
  MappingFilterData* mappingData = NULL;
  
  input>>size;
  
  for(int i = 0; i < size; i++) {
    input>>id;
    try {
      mappingData = PersistenceManager::getDB()->load_md(id);
      mappingFilter->register_data(mappingData);                
    } catch (CORBA::Exception& e) {
      if (_tidorb->trace != NULL)
        _tidorb->print_trace(TIDorb::util::TR_ERROR, 
                             "FilterFactoryImpl::readObject error reading mapping_filters", e);
    }	        
  }
}
  
}; // TIDNotif
