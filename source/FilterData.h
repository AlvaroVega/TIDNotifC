// -*- c++ -*-
/*
 *  File name: FilterData.h
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

#ifndef _TIDNOTIF_FILTERDATA_H_
#define _TIDNOTIF_FILTERDATA_H_ 

#include <istream>
#include <ostream>
#include <map>
#include "PortableServer.h"
#include "CosNotifyFilter.h"
#include "CommonData.h"
#include "TIDConstraint.h"

namespace TIDNotif{

class FilterData : public CommonData //TODO_MORFEO: java.io.Serializable
{
    
private: 
  static const char * ERROR_1;
  
public:

  typedef map<int,CosNotifyFilter::ConstraintInfo> ConstraintTable;
  ConstraintTable constraintTable;
    
  typedef map<CosNotifyFilter::ConstraintID,
              util::parser::TIDConstraint*> FilterTable;
  FilterTable filterTable;  //TODO_MORFEO: transient 
    
  int filter_counter; //TODO_MORFEO: transient 
    
  CosNotifyFilter::Filter_var reference; //TODO_MORFEO: transient
   			
  //
  // Constructors
  //
  FilterData(const char*, PortableServer::POA_ptr);
  ~FilterData();  
  
  void readObject(std::istream & );
  void writeObject(std::ostream &);
    
private:
  
  inline void free_filter_table();

};
  
  
};//namespace TIDNotif

#endif
