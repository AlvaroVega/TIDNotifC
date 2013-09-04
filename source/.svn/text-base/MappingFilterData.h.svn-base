// -*- c++ -*-
/*
 *  File name: MappingFilterData.h
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

#ifndef _TIDNOTIF_MAPPINGFILTERDATA_H_
#define _TIDNOTIF_MAPPINGFILTERDATA_H_ 

#include <istream>
#include <ostream>

#include "CommonData.h"
#include "PortableServer.h"
#include "CORBA.h"
#include "TIDConstraint.h"
#include "CosNotifyFilter.h"

namespace TIDNotif {
  
  
  
class MappingFilterData : public CommonData 
{
     
private:
  static const char * ERROR_1;

public:
  static const char * EXTRACT_LONG;

  CORBA::Any default_value;
  CORBA::TypeCode& value_type;
  CosNotifyFilter::MappingFilter_ptr reference; //TODO_MORFEO: transient
      
  typedef map<CosNotifyFilter::ConstraintID,
              CosNotifyFilter::MappingConstraintInfo> 
  MappingConstraintInfoTable; 
										
  MappingConstraintInfoTable assignedMappingConstraintInfoTable;

  typedef map<CosNotifyFilter::ConstraintID,
              util::parser::TIDConstraint*> FilterTable;
  FilterTable filterTable;  //TODO_MORFEO: transient 

			
  util::parser::TIDConstraint* matches; 
  //TODO_MORFEO: Which is its use? (it's not included within persistence)


  //
  // Constructor
  //
  MappingFilterData(const char* id, const CORBA::Any& default_value); //TODO_MORFEO id => OID->toString()



  void readObject(std::istream & ); 
  void writeObject(std::ostream &);

};
	
	 
};//namespace TIDNotif
#endif
