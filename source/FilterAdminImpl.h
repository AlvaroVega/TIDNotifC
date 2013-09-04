// -*- c++ -*-
/*
 *  File name: FilterAdminImpl.h
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

#ifndef _TIDNOTIF_FILTERADMINIMPL_H_
#define _TIDNOTIF_FILTERADMINIMPL_H_ 

#include <istream>
#include <ostream>
#include <map>
#include "POA_CosNotifyFilter.h"

#include "SynSortedMap.h"

namespace TIDNotif{

class FilterAdminImpl : POA_CosNotifyFilter::FilterAdmin {



private:
  
  typedef TIDNotif::util::SynSortedMap<CosNotifyFilter::FilterID, 
                                       CosNotifyFilter::Filter_var, 
                                       CosNotifyFilter::FilterIDSeq> FilterAdminMapT;
  FilterAdminMapT filters;
  

public: //Operations, Constants & Attributes Declaration
	
  FilterAdminImpl();
		

  ~FilterAdminImpl();
		
  CosNotifyFilter::FilterID add_filter(CosNotifyFilter::Filter_ptr new_filter);

		
  void remove_filter(CosNotifyFilter::FilterID filter)
    throw (CosNotifyFilter::FilterNotFound);

		
  CosNotifyFilter::Filter_ptr get_filter(CosNotifyFilter::FilterID filter)
    throw (CosNotifyFilter::FilterNotFound);
		
  CosNotifyFilter::FilterIDSeq* get_all_filters();

  void remove_all_filters();
		
  CORBA::Boolean match(const CORBA::Any& event);

  void writeObject (ostream& );

  void readObject (istream& );

private:

  CosNotifyFilter::FilterID nextKey();


}; 
	
	 
};// TIDNotif

#endif
