// -*- c++ -*-
/*
 *  File name: TIDNotifConfig.h
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

#ifndef _TIDUTIL_TIDNOTIFCONFIG_H_
#define _TIDUTIL_TIDNOTIFCONFIG_H_

#include "TIDConfig.h"


namespace TIDNotif {
namespace util {


class TIDNotifConfig {

public:

  static TIDConfig* config;
  
  //
  // TIDNotif config table size
  // 
  //static const int SIZE_CONFIG_TABLE = 52;
  static const int SIZE_CONFIG_TABLE = 34;


  //
  // POA IDs
  //
  static const int GLOBAL_POA    = 0;
  static const int LOCAL_POA     = 1;
  static const int EXCLUSIVE_POA = 2;
  
  
//   //
//   // Data base config params
//   //
//   static const char * DB_URL_KEY;
//   static const char * DB_USER_KEY;
//   static const char * DB_PASSWORD_KEY;
//   static const char * DB_POOLMAXCONNS_KEY;
//   static const char * DB_CACHESIZE_KEY;


  //
  // Persistence config data
  //
  static const char * PERS_DB_KEY;
//   static const char * RECOVERY_BOOT_KEY;


  static const char * MAX_DISCONNECTED_TIME;
  static const char * MAX_COMM_FAILURES;
  static const char * ON_COMM_FAILURE;
  static const char * MAX_NO_RESPONSE;
  static const char * ON_NO_RESPONSE;

  //static const char * ORB_BUG_KEY;
  static const char * SPEEDUP_POA_KEY;
  //static const char * CORBA_CALLS_KEY;

//   //
//   // Trace Logs options
//   //
//   static const char * TRACE_LEVEL_KEY;
//   static const char * TRACE_DATE_KEY;
//   static const char * TRACE_APPNAME_KEY;
//   static const char * TRACE_TO_FILE_KEY;
//   static const char * TRACE_FILENAME_KEY;
//   static const char * TRACE_FILESIZE_KEY;
//   static const char * TRACE_NUMFILES_KEY;

  
  //
  // ORB port
  // 
  static const char * ADMIN_PORT_KEY;
  static const char * ADMIN_SSL_PORT_KEY;


  //
  // IOR key
  //
  static const char * URL_MODE_KEY;
  static const char * IOR_TO_FILE_KEY;
  static const char * IOR_PATH_KEY;
  static const char * IOR_FILENAME_KEY;


  //
  // Paths
  //
  static const char * DATA_PATH_KEY;
  static const char * DATA_ROOT_KEY;
  static const char * OBJECTS_PATH_KEY;
  static const char * PROPS_FILENAME_KEY;


  //
  // POAs
  //
  static const char * CHANNEL_POA_KEY;
  static const char * SUPPLIER_POA_KEY;
  static const char * CONSUMER_POA_KEY;


//   //
//   //
//   //
//   static const char * CONTENTION_KEY;
//   static const char * CONTENT_TIME_KEY;
//   static const char * FLOOD_EVENTS_KEY;
//   static const char * FLOOD_TIME_KEY;


  //
  // Error
  //
  static const char * RETURN_ON_ERROR_KEY;
  static const char * TIME_DEBUG_KEY;


//   //
//   // Reqeuest queue and POA PoolThreads options
//   //
//   static const char * ROOTPOA_QUEUE_KEY;
//   static const char * ROOTPOA_MAXTHR_KEY;
//   static const char * ROOTPOA_MINTHR_KEY;



  static const char * SUPPLIER_QUEUE_KEY;
  static const char * SUPPLIER_MAXTHR_KEY;
  static const char * SUPPLIER_MINTHR_KEY;

  static const char * CONSUMER_QUEUE_KEY;
  static const char * CONSUMER_MAXTHR_KEY;
  static const char * CONSUMER_MINTHR_KEY;

  static const char * CHANNEL_QUEUE_KEY;
  static const char * CHANNEL_MAXTHR_KEY;
  static const char * CHANNEL_MINTHR_KEY;

  static const char * FILTER_QUEUE_KEY;
  static const char * FILTER_MAXTHR_KEY;
  static const char * FILTER_MINTHR_KEY;


//   //
//   // Date and time format
//   //
//   static const char * DATE_FORMAT_KEY;
//   static const char * TIME_FORMAT_KEY;



  //
  // Root
  //
//   static const char * ORB_KEY_PREFIX;
  static const char * NOTIF_KEY_PREFIX;


  //
  // TIDNotif config table
  // 
  static const char * configTable[][SIZE_CONFIG_TABLE];

private:

  TIDNotifConfig(const TIDConfig::Property& new_values);

  TIDNotifConfig(const char ** values, int rows);

public:

  static TIDNotifConfig* init(const TIDConfig::Property& props);

  static TIDNotifConfig* init(const char** props, int nargs);

  static void updateConfig(const char** args, int nargs);

  static void updateConfig(const TIDConfig::Property& props);

  static const char* get(const char* key);

  static int getInt(const char* key);

  static bool getBool(const char* key);

  static void set(const char* key, const char* value);

  static void restore();

  static void store();

};//class

}; // namespace util
}; // namespace TIDNotif

#endif
