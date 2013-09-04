// -*- c++ -*-
/*
 *  File name: TIDConfig.h
 *  File type: Header file.
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

#ifndef _TIDUTIL_TIDCONFIG_H_
#define _TIDUTIL_TIDCONFIG_H_

#include <stdio.h>
#include <string>
#include <map>

#include "TIDPropValue.h"

#ifdef HAVE_NAMESPACE_STD
using namespace std;
#endif


namespace TIDNotif {
namespace util {

class TIDConfig {
  
public:
  typedef std::map <std::string, std::string>     Property;
  typedef std::map <std::string, TIDPropValue*>   Hash;
  

  // Property Types
  static const char * NUMTYPE;
  static const char * BOOLTYPE;
  static const char * STRTYPE;

  // Property Attributes
  static const int RO_ATTR       =  0;
  static const int RW_ATTR       =  1;
  static const char * READ_ONLY;
  static const char * READ_WRITE;
  
  // Integer Value Limits
  static const int NO_LIMIT  =  -1;
  static const char * NO_MIN;
  static const char * NO_MAX;

  // Boolean Values
  static const char * TRUE_VALUE;
  static const char * FALSE_VALUE;

  static const int NAME_INDEX  = 0;
  static const int TYPE_INDEX  = 1;
  static const int ATTR_INDEX  = 2;
  static const int VALUE_INDEX = 3;
  static const int MIN_INDEX   = 4;
  static const int MAX_INDEX   = 5;


private:

  bool         _debug;
  std::string  key_prefix;
  int          long_config_table;
  Property*    tid_config;
  Hash         check_table;

public:

  TIDConfig(const std::string&, const Property&);

  TIDConfig(const std::string&, const char ** values, int rows);

  ~TIDConfig();

  void setPrefix(const std::string& new_prefix );

  std::string getPrefix();

  const char* get(const std::string& key );// throw (CORBA::UNKNOWN);

  void set(const char* key,const char* value );

  void updateConfig(const Property & );

  void updateConfig(const char** ,int );

  void setDebug(bool value);

  void store();

  void load();


private:

  Property* createDefaults();

  Property * create_property(const char ** new_values, int rows);

  Hash createCheckTable();

  Property * copyConfig(const Property& new_values );

  bool startsWith (const std::string&, const std::string&);

  bool checkValue(const std::string& key,const std::string& value );

};
  
}; // namespace util
}; // namespace TIDNotif

#endif

