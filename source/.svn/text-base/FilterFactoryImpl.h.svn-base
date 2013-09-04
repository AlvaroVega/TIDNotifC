// -*- c++ -*-
/*
 *  File name: FilterFactoryImpl.h
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

#ifndef _TIDNOTIF_FILTERFACTORYIMPL_H_
#define _TIDNOTIF_FILTERFACTORYIMPL_H_ 


#include "POA_CosNotifyFilter.h"
#include "PortableServer.h"

#include "TIDorb/core.h"

#include <istream>
#include <ostream>

namespace TIDNotif { 

class FilterFactoryImpl : public virtual POA_CosNotifyFilter::FilterFactory
{
public:
	
  static const char * GLOBAL_FILTER_POA_ID;
  static const char * GLOBAL_MAPPING_FILTER_POA_ID;
  static const char * CREATE_FILTER[3];
  static const char * CREATE_MAPPING_FILTER[3];	
	
  FilterFactoryImpl(CORBA::ORB_ptr orb);
  ~FilterFactoryImpl();
			
  //methods -> inherited
  CosNotifyFilter::Filter_ptr create_filter(const char* constraint_grammar)
    throw (CosNotifyFilter::InvalidGrammar);
			
  CosNotifyFilter::MappingFilter_ptr 
  create_mapping_filter(const char* constraint_grammar, 
                        const CORBA::Any& default_value)
    throw (CosNotifyFilter::InvalidGrammar);
			
  //methods
  CosNotifyFilter::Filter_ptr get_filter( int filterId );
	
		
	
private:

  CORBA::ORB_var _orb;
  TIDorb::core::TIDORB* _tidorb;
  int uid;


  PortableServer::POA_ptr globalFilterPOA();
  PortableServer::POA_ptr globalMappingDiscriminatorPOA();
		
  void writeObject(ostream & out);		
  void readObject(istream & input); 
};
}; //namespace TIDNotif
#endif
