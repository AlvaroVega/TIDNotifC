/*
 *  File name: TIDConfig.C
 *  File type: Body file.
 *  Date : March 2006
 *  Author: David Alonso <dalonso@gsyc.escet.urjc.es>
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

/*
 * Revision historial:
 *   - 04/04/2006, by Alvaro Polo <apoloval@gsyc.escet.urjc.es>:
 *       * Code cleaning.
 *   - 17/12/2007, by Alvaro Vega <avega@tid.es>:
 *       * Code cleaning.
 */

#include "TIDConfig.h"
#include "CORBA.h"
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include "TIDNotifConfig.h"
#include "TIDNotifUtil.h"

namespace TIDNotif {
namespace util {

  // Property Types

  const char * TIDConfig::NUMTYPE = "N";
  const char * TIDConfig::BOOLTYPE = "B";
  const char * TIDConfig::STRTYPE  = "S";

  // Property Attributes
  const char * TIDConfig::READ_ONLY  = "RO";
  const char * TIDConfig::READ_WRITE = "RW";

  // Integer Value Limits

  const char * TIDConfig::NO_MIN = "";
  const char * TIDConfig::NO_MAX = "";

  // Boolean Values
  const char * TIDConfig::TRUE_VALUE = "true";
  const char * TIDConfig::FALSE_VALUE = "false";

  //bool _debug = false;

}; //namespace util
}; //namespace TIDNotif



TIDNotif::util::TIDConfig::TIDConfig(const string& prefix, const Property& new_values)
{
  this->key_prefix = prefix;
  this->long_config_table = util::TIDNotifConfig::SIZE_CONFIG_TABLE;
  this->tid_config = createDefaults();
  check_table = createCheckTable();
  //this->tid_config = copyConfig(new_values);
  this->tid_config = createDefaults();
  updateConfig(new_values);

  _debug = false;
}

TIDNotif::util::TIDConfig::TIDConfig(const std::string& prefix, 
                                     const char ** values, int rows)
{
  Property * property;

  property = create_property(values, rows);
  this->key_prefix = prefix;
  this->long_config_table = util::TIDNotifConfig::SIZE_CONFIG_TABLE;
  this->tid_config = createDefaults();
  check_table = createCheckTable();
  //this->tid_config = copyConfig(*property);
  updateConfig(values, rows);
  delete property;

  _debug = false;
}

TIDNotif::util::TIDConfig::~TIDConfig()
{
}

void TIDNotif::util::TIDConfig::setPrefix(const string& new_prefix )
{
  key_prefix = new_prefix;
}

string TIDNotif::util::TIDConfig::getPrefix()
{
  return key_prefix;
}

const char* TIDNotif::util::TIDConfig::get(const string& key)
{
  if(tid_config->empty()) {
    throw CORBA::UNKNOWN("IllegalStateException");
  }
  return (*tid_config)[key].c_str();
}

void TIDNotif::util::TIDConfig::set(const char* key,const char* value)
{
  if(tid_config->empty()) {
      throw CORBA::UNKNOWN("IllegalStateException");
  }
  if (checkValue(key,value))
    (*tid_config)[key] = value;
  else {
    if(_debug)
      cerr << "Value not allowed for the property: "<< key << endl;
  }
}

void TIDNotif::util::TIDConfig::updateConfig(const Property& new_values)
{

  if (new_values.empty()) return;
  Property::const_iterator e;
  for ( e = new_values.begin(); e != new_values.end(); e++) {
    const string & key = e->first;
    if (!startsWith(key,key_prefix) != 0) {
      //USER
      // 	if (_debug)
        //           cerr << "TIDConfig.updateConfig(): ignored key -> " << key << endl;
      continue;
      
    }
    const string & value = e->second;
    if (checkValue(key, value))
      (*tid_config)[key] = value;
    else
      if (_debug)
        cerr << "TIDConfig.updateConfig(): Value not allowed for the property: " <<
          key << endl;
  }
}

void TIDNotif::util::TIDConfig::updateConfig(const char** new_values, int rows)
{
  Property * property;
  property = create_property(new_values, rows);
  updateConfig(*property);
  delete property;
}

TIDNotif::util::TIDConfig::Property *
TIDNotif::util::TIDConfig::create_property(const char ** new_values, int rows)
{
  util::TIDConfig::Property * result;

  result = new util::TIDConfig::Property;
  if (new_values == NULL)
    return result;
  for ( int i = 0; i < rows; i+=2)
    {
      string key = new_values[i];
      if (!startsWith(key,key_prefix))
        {
          //USER
          //         if (_debug)
          //           cerr << "TIDConfig.updateConfig(): ignored key -> " << key << endl;
          continue;
        }
      string value = new_values[i+1];
      (*result)[key] = value;
    }
  return result;
}

void TIDNotif::util::TIDConfig::setDebug(bool value)
{
  _debug=value;
}

void TIDNotif::util::TIDConfig::store()
{
  if(tid_config->empty())
    throw CORBA::UNKNOWN("IllegalStateException");
  fstream file(util::TIDNotifUtil::tidConfigFilename(true).c_str(), ios::out);
  Property::iterator e;
  for(e = tid_config->begin();e!=tid_config->end();e++)
    {
      file<<e->first<<" " <<e->second << endl;
    }
  file.close();
}

void TIDNotif::util::TIDConfig::load()
{
  if (tid_config->empty())
    throw CORBA::UNKNOWN("IllegalStateException");

  fstream file(util::TIDNotifUtil::tidConfigFilename(true).c_str(),ios::in);
  if(!file)
    throw CORBA::UNKNOWN("IO exception");
  string line;
  string head;
  string tail;
  int n;

    
  getline(file,line);
  while (!file.eof())
    {
      n = line.find(" ");
      head = line.substr(0, n);
      tail = line.substr(n+1);
      (*tid_config)[head] = tail;
      getline(file,line);
    }
  file.close();
}

TIDNotif::util::TIDConfig::Property* TIDNotif::util::TIDConfig::createDefaults()
{
  std::string name;
  std::string value;
  util::TIDConfig::Property * defaults = new util::TIDConfig::Property;

  for (int i = 0; i < this->long_config_table; i++)
    {
      name  = util::TIDNotifConfig::configTable[i][TIDConfig::NAME_INDEX];
      value = util::TIDNotifConfig::configTable[i][TIDConfig::VALUE_INDEX];
      (*defaults)[name]=value;
    }
  return defaults;
}


TIDNotif::util::TIDConfig::Hash TIDNotif::util::TIDConfig::createCheckTable()
{
  util::TIDConfig::Hash checktable;
  for (int i = 0; i < this->long_config_table; i++)
    {
      int attr;
      if (!strcmp(READ_WRITE,
                  util::TIDNotifConfig::configTable[i][TIDConfig::ATTR_INDEX]))
        {
          attr=RW_ATTR;
        }
      else if (!strcmp(READ_ONLY,
                       util::TIDNotifConfig::configTable[i][TIDConfig::ATTR_INDEX]))
        {
          attr = RO_ATTR;
        }
      else
        attr = RO_ATTR;

      TIDPropValue* value;

      if (!strcmp(NUMTYPE,
                  util::TIDNotifConfig::configTable[i][TIDConfig::TYPE_INDEX]))
        {

          int min,max;
          try
            {
              min = atoi(util::TIDNotifConfig::configTable[i][MIN_INDEX]);
            }
          catch (...)
            {
              if(_debug)
                cerr << "TIDConfig: parseInt(min) Exception." << endl;
              min = NO_LIMIT;
            }

          try
            {
              max = atoi(util::TIDNotifConfig::configTable[i][MAX_INDEX]);
            }
          catch (...)
            {
              if(_debug)
                cerr << "TIDConfig: parseInt(max) Exception." << endl;
              max = NO_LIMIT;
            }
          value = new TIDPropValue(TIDNotifConfig::configTable[i][TYPE_INDEX],
                                   attr,
                                   min,
                                   max);
        }
      else
        {
          value = new TIDPropValue(TIDNotifConfig::configTable[i][TYPE_INDEX],
                                   attr);
        }
      const char* name = util::TIDNotifConfig::configTable[i][TIDConfig::NAME_INDEX];
      checktable[name] = value;
    }
  return checktable;
}

TIDNotif::util::TIDConfig::Property *
TIDNotif::util::TIDConfig::copyConfig(const Property& new_values)
{
  Property * result;

  result = new Property();

  if (new_values.empty())
    return result;

  Property::const_iterator e; //iterador de map
  std::string n;

  //recorre la tabla new_values
  for ( e = new_values.begin(); e != new_values.end(); e++) {
    std::string key = e->first;
    if (!startsWith(key,key_prefix)) {
      //USER
      //         if (_debug)
      //           cerr << "TIDConfig.updateConfig(): ignored key -> " << key << endl;
      continue;
    }
    std::string value = e->second;
    if (checkValue(key, value))
      (*result)[key] = value;
    else {
      if (_debug)
        cerr <<
          "TIDConfig.updateConfig(): Value not allowed for the property: " <<
          key << endl;
    }
  }
  return result;
}

bool TIDNotif::util::TIDConfig::startsWith(const std::string & str, 
                                           const std::string & prefix)
{
  return str.find(prefix, 0) == 0;
}

bool TIDNotif::util::TIDConfig::checkValue(const string & key, 
                                           const string & value)
{
  if (check_table.empty()) {
    if (_debug)
      cerr << "TIDConfig: CHECK TABLE non exist, return true" << endl;
    return true;
  }

  TIDPropValue* configValue = check_table[key];

  if (configValue == NULL) {
    if (_debug)
      cerr << "TIDConfig: Existing KEY NOT found in Type List" << endl;
    return false;
  }

  if (configValue->attr == RO_ATTR) {
    if (_debug)
      cerr << "TIDConfig: READ ONLY attribute, NOT changed." << endl;
    return false;
  }

  if (strcmp(NUMTYPE,configValue->type)==0) {
    int new_value;
    
      try {
        new_value = atoi(value.c_str());
        if ( (new_value >= configValue->min) && (new_value <= configValue->max) ) {
          return true;
        }
        else {
          if (_debug)
            cerr << "TIDConfig: invalid new_value."<< endl;
          return false;
        }
      }
      catch (...) {
        cerr << "TIDConfig: parseInt(new_value) Exception."<< endl;
        return false;
      }
  }
  
  else if (strcmp(BOOLTYPE,configValue->type)==0) {
    if ( strcmp(TRUE_VALUE,value.c_str())==0) {
      return true;
    }
    else if ( strcmp(FALSE_VALUE,value.c_str())==0 ) {
      return true;
    }
    // DEBUG
    if (_debug)
      cerr << "TIDConfig: Incorrect boolean value"<< endl;
    return true;
  }
  else if (strcmp(STRTYPE,configValue->type)==0) {
    if (strcmp(value.c_str(),"")==0 ) {
      if (_debug)
        cerr << "TIDConfig: Invalid string value"<< endl;
      return false;
    }
    return true;
  }
  return false;
}


