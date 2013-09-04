/*
 *  File name: FilterData.C
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

#include <string>
#include "FilterData.h"
#include "NotifReference.h"
#include "CosNotification.h"
#include "TIDParser.h"

namespace TIDNotif {
  
  //static const char * ERROR_1 = "DiscriminatorData.readObject(istream& s)";
  
FilterData::FilterData (const char* id, PortableServer::POA_ptr poa)
  : CommonData(id,poa), filter_counter(0),
    reference(NotifReference::discriminatorReference(poa,id))
{}
  
FilterData::~FilterData()
{
  constraintTable.clear();
  free_filter_table();
  filterTable.clear();
}

void FilterData::readObject(std::istream & si)
{
  
  constraintTable.clear(); /* No heap memory need to be released. */
  free_filter_table();
  filterTable.clear();
  filter_counter = 0;
  //CosNotifyFilter::ConstraintInfo* constraintInfo;
  CosNotifyFilter::ConstraintExp* constraintExp;
  CosNotification::EventTypeSeq* eventTypeSeq;
  string exp;
  string constraint_exp;
  string domain_name;
  string type_name;
  CosNotifyFilter::ConstraintID c_id;
  si>>id;
  int size,i,j,seq;
  si >> size;
  for (i=0; i<size;i++) {

    si >> seq;
    eventTypeSeq = new CosNotification::EventTypeSeq(seq);
    eventTypeSeq->length(seq);
    filter_counter++;
    for (j=0; j<seq;j++) {
      si >> domain_name;
      si >> type_name;
      (*eventTypeSeq)[j]= CosNotification::_EventType(domain_name.c_str(),
                                                      type_name.c_str());
    }

    //whitespace 
    constraint_exp.clear();
    while (si>>exp)
      constraint_exp.append(exp);
    
    constraintExp = new CosNotifyFilter::ConstraintExp(*eventTypeSeq,
                                                       constraint_exp.c_str());
    si >>  c_id;
    constraintTable[c_id]=CosNotifyFilter::ConstraintInfo(*constraintExp,c_id);
    try {
      filterTable[c_id]=util::parser::TIDParser::parse(constraint_exp);
      filter_counter++;
    }
    catch (util::parser::ParsingErrorException & ex) {
      //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
    }
  }  
}

void FilterData::writeObject (std::ostream & os)
{
  //TODO_MORFEO: write type of grammar in case that we implement other grammar
  //different to "EXTENDED_TCL"
  ConstraintTable::iterator it;
  CosNotifyFilter::ConstraintInfo* constraintInfo;
  CosNotifyFilter::ConstraintExp* constraintExp;
  CosNotification::EventTypeSeq* eventTypeSeq;
  CORBA::ULong i;
  
  os<<id<<endl;
  
  
  os<<constraintTable.size()<<endl;
  
  for (it=constraintTable.begin(); it!=constraintTable.end();it++) {
    constraintInfo=&constraintTable[it->first];
    constraintExp=&constraintInfo->constraint_expression;
    eventTypeSeq=&constraintExp->event_types;
    CORBA::ULong seq;
    seq=eventTypeSeq->length();
    os<<seq<<endl;
    for (i=0;i<seq;i++) {
      os<<(*eventTypeSeq)[i].domain_name.in()<<endl;
      os<<(*eventTypeSeq)[i].type_name.in()<<endl;
    }
    
    os<<constraintExp->constraint_expr<<endl;
    os<<constraintInfo->constraint_id<<endl;
  }
}

void
FilterData::free_filter_table()
{
  FilterTable::iterator it;
  for (it = filterTable.begin(); it != filterTable.end(); it++)
    if (it->second) 
      delete it->second;
}

};// namespace TIDNotif

