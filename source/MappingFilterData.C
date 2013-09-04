/*
 *  File name: MappingFilterData.C
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

#include "MappingFilterData.h"
#include "NotifReference.h"
#include "TimeBase.h"
#include "TIDParser.h"

namespace TIDNotif {

// static const char * ERROR_1 ="MappingDiscriminatorData.readObject(ObjectInputStream s): ERROR";
// static const char * EXTRACT_LONG = "   ERROR: _default_value.type()";
  
	
//
// Constructor
//
MappingFilterData::MappingFilterData(const char* id, const CORBA::Any& default_val)
  : CommonData(id), default_value(default_val),  value_type(*default_value.type()),
    reference(NotifReference::mappingDiscriminatorReference(poa,id)),
    matches(NULL)
{
}



void MappingFilterData::readObject(std::istream & is){ 
  TimeBase::TimeT lifetime;
  CORBA::Short priority;
  
    
  assignedMappingConstraintInfoTable.clear(); //TODO_MORFEO: Free memory
  filterTable.clear(); //TODO_MORFEO: free memory; 
  CORBA::Any any_value;
  CosNotifyFilter::ConstraintExp* constraintExp;
  CosNotification::EventTypeSeq* eventTypeSeq;
  string constraint_exp;
  string domain_name;
  string type_name;
  CosNotifyFilter::ConstraintID id;
  int size,i,j,seq;
  is>>size;
  for (i=0; i<=size;i++)
    {
         
      is>>seq;
      eventTypeSeq = new CosNotification::EventTypeSeq(seq);
      for (j=0; j<=seq;i++)
        {
          is>>domain_name;
          is>>type_name;
          //(*eventTypeSeq)[j]= *(new CosNotification::_EventType(domain_name.c_str(),type_name.c_str())); //TODO_MORFEO
          (*eventTypeSeq)[j]= CosNotification::_EventType(domain_name.c_str(),type_name.c_str());
        }
      is>>constraint_exp;
      constraintExp = new CosNotifyFilter::ConstraintExp(*eventTypeSeq,constraint_exp.c_str());
      is>>id;
      int k;
      is>>k;
      switch (k)
        {
        case CORBA::tk_short:
          is>>priority;
          (any_value) <<= (priority);
          break;
      
        case CORBA::tk_ulonglong:
          is>>lifetime;
          (any_value) <<= (lifetime);
         
          break;
  
        default:
          throw CORBA::INTERNAL();
        }
      assignedMappingConstraintInfoTable[id]=CosNotifyFilter::MappingConstraintInfo(*constraintExp,id,any_value);
      
      try
        {
          filterTable[id]=util::parser::TIDParser::parse(constraint_exp);
        }
      catch (util::parser::ParsingErrorException & ex)
        {
          //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
        }
    }
  
		/*s.defaultReadObject();
    filterTable = new java.util.Hashtable();
    for ( java.util.Iterator e =
                 assignedMappingConstraintInfoTable.entrySet().iterator(); e.hasNext(); )
    {
      java.util.Map.Entry entry = (java.util.Map.Entry)e.next();
      MappingConstraintInfo info = (MappingConstraintInfo)entry.getValue();
      try
      {
        SimpleNode new_filter = TIDParser.parse( info.constraint_expression.constraint_expr );
        filterTable.put((String)entry.getKey(), new_filter);
      }
      catch (es.tid.util.parser.ParseException ex)
      {
        TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex);
      }
      catch (java.lang.Exception ex)
      {
        TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex);
      }
    }*/
}

void MappingFilterData::writeObject(std::ostream & os) {

  TimeBase::TimeT lifetime;
  CORBA::Short priority;
  os<<id;
  os<<value_type.kind()<<endl;
  switch (value_type.kind())
    {
    case CORBA::tk_short:
      if (!(default_value >>= (priority))) throw CORBA::INTERNAL();
      os<<priority<<endl;
      break;
      
    case CORBA::tk_ulonglong:
      if (!(default_value >>= (lifetime))) throw CORBA::INTERNAL();
      os<<lifetime<<endl;
      break;
      
    default:
      throw CORBA::INTERNAL();
    }
  
  MappingConstraintInfoTable::iterator it;
  CosNotifyFilter::MappingConstraintInfo* mappingConstraintInfo;
  CosNotifyFilter::ConstraintExp* constraintExp;
  CosNotification::EventTypeSeq* eventTypeSeq;
  CORBA::ULong i;
  os<<assignedMappingConstraintInfoTable.size()<<endl;
  for (it=assignedMappingConstraintInfoTable.begin(); 
       it!=assignedMappingConstraintInfoTable.end();it++)
    {
      mappingConstraintInfo=&assignedMappingConstraintInfoTable[it->first];
      constraintExp=&mappingConstraintInfo->constraint_expression;
      eventTypeSeq=&constraintExp->event_types;
      CORBA::ULong seq;
      seq=eventTypeSeq->length();
      os<<seq<<endl;
      for (i=0;i<=seq;i++)
        {
          os<<(*eventTypeSeq)[i].domain_name<<endl;
          os<<(*eventTypeSeq)[i].type_name<<endl;
        }
      os<<constraintExp->constraint_expr<<endl;
      mappingConstraintInfo->constraint_id; //  statement has no effect ???????
      CORBA::Any& any_value = mappingConstraintInfo->value;
      os<<any_value.type()->kind();
      switch (any_value.type()->kind())
        {
        case CORBA::tk_short:
          if (!(any_value >>= (priority))) throw CORBA::INTERNAL();
          os<<priority<<endl;
          break;
          
        case CORBA::tk_ulonglong:
          if (!(any_value >>= (lifetime))) throw CORBA::INTERNAL();
          os<<lifetime<<endl;
          break;
          
        default:
          throw CORBA::INTERNAL();
        }
    }
  
}
  	
};//namespace TIDNotif
