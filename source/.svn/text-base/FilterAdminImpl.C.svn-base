/*
 *  File name: FilterAdminImpl.C
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

#include "FilterAdminImpl.h"
#include "ThePOAFactory.h"
#include "FilterData.h"
#include "FilterImpl.h"
#include "NotifReference.h"

namespace TIDNotif {

TIDNotif::FilterAdminImpl::FilterAdminImpl()
{
}


FilterAdminImpl::~FilterAdminImpl() 
{
  filters.clear();
}


CosNotifyFilter::FilterID FilterAdminImpl::nextKey()
{
  CosNotifyFilter::FilterID lastKey, nextKey;
  if ( filters.freeKey() ) {
    nextKey = filters.get_freeKey();
  } else {
    lastKey = filters.lastKey();
    nextKey = lastKey+1;
  }
  return nextKey;
}
	
	 		
CosNotifyFilter::FilterID 
FilterAdminImpl::add_filter(CosNotifyFilter::Filter_ptr new_filter)
{
  CosNotifyFilter::FilterID key; 
  key = nextKey();
  // duplicate at insertion
  filters.put( key,  CosNotifyFilter::Filter::_duplicate(new_filter) );  
  return key;
}

		
void FilterAdminImpl::remove_filter(CosNotifyFilter::FilterID filter)
  throw (CosNotifyFilter::FilterNotFound)
{
  bool exist = filters.remove( filter  );
  if (!exist){
    throw CosNotifyFilter::FilterNotFound();
  }
}

		
CosNotifyFilter::Filter_ptr 
FilterAdminImpl::get_filter(CosNotifyFilter::FilterID filter)
  throw (CosNotifyFilter::FilterNotFound)
{
  CosNotifyFilter::Filter_ptr existingFilter = NULL;
  existingFilter = filters.get(filter);
  if ( existingFilter == NULL ){
    throw CosNotifyFilter::FilterNotFound();
  } 
  return CosNotifyFilter::Filter::_duplicate(existingFilter);
}

		
CosNotifyFilter::FilterIDSeq* FilterAdminImpl::get_all_filters()
{
  return filters.keySet();
}

		
void FilterAdminImpl::remove_all_filters()
{
  filters.clear();
}
		
CORBA::Boolean FilterAdminImpl::match(const CORBA::Any& event)
{
  FilterAdminMapT::iterator_map iter;
  FilterAdminMapT::iterator_map begin = filters.begin();
  FilterAdminMapT::iterator_map end = filters.end();
  
  CosNotifyFilter::Filter_ptr filter;
  for (iter = begin; iter != end; iter++) {
    filter = (CosNotifyFilter::Filter_ptr) filters.get(iter->first);
    if(!filter->match(event)) {
      return false;
    }
  }
  return true;
}

void FilterAdminImpl::writeObject (ostream& )
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}

void FilterAdminImpl::readObject (istream& si)
{
  PortableServer::POA_ptr the_poa;
  the_poa = ThePOAFactory::getGlobalPOA("GlobalFilterPOA");
  
  // Fix bug [#438]	Crash recovering persistence data of a Filter
  if (the_poa == NULL) {
    the_poa = 
      ThePOAFactory::createGlobalPOA("GlobalFilterPOA",
                                     ThePOAFactory::GLOBAL_FILTER_POA, 
                                     NULL );
  }
  FilterData* filterData  = new FilterData("0", the_poa );
  
  filterData->readObject(si);
  try {
    (dynamic_cast<FilterImpl*> (the_poa->get_servant()))
      ->register_data( filterData );
  } catch (const CORBA::Exception& e) {
  }

  CosNotifyFilter::Filter_ptr filter;
  filter = NotifReference::discriminatorReference(the_poa,
                                                  filterData->id);
  int _id = atoi(filterData->id);
  
  filters.put(_id, filter );
  
}

}; 
	
