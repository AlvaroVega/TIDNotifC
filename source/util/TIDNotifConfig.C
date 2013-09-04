/*
 *  File name: TIDNotifConfig.C
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

#include "TIDNotifConfig.h"
#include "CORBA.h"

namespace TIDNotif {
namespace util {

  TIDConfig* TIDNotifConfig::config = NULL;

//   //
//   //   Data base config params
//   //   
//   const char* TIDNotifConfig::DB_URL_KEY = 
//     "TIDNotif.database.url";
//   const char*  TIDNotifConfig::DB_USER_KEY =
//     "TIDNotif.database.user";
//   const char*  TIDNotifConfig::DB_PASSWORD_KEY =
//     "TIDNotif.database.password";
//   const char*  TIDNotifConfig::DB_POOLMAXCONNS_KEY =
//     "TIDNotif.database.poolmaxconns";
//   const char*  TIDNotifConfig::DB_CACHESIZE_KEY =
//     "TIDNotif.database.CacheSize";


  //
  // Persistence config data
  //
  const char*  TIDNotifConfig::PERS_DB_KEY =
    "TIDNotif.persistence.db";
//   const char*  TIDNotifConfig::RECOVERY_BOOT_KEY =
//     "TIDNotif.persistence.load";


  const char*  TIDNotifConfig::MAX_DISCONNECTED_TIME =
    "TIDNotif.consumer.max_disconnected_time";
  const char*  TIDNotifConfig::MAX_COMM_FAILURES =
    "TIDNotif.consumer.max_comm_failures";
  const char*  TIDNotifConfig::ON_COMM_FAILURE =
    "TIDNotif.consumer.on_comm_failure";
  const char*  TIDNotifConfig::MAX_NO_RESPONSE =
    "TIDNotif.consumer.max_no_response";
  const char*  TIDNotifConfig::ON_NO_RESPONSE =
    "TIDNotif.consumer.on_no_response";



//   const char * ORB_BUG_KEY        = 
//     "TIDNotif.orb.bug";
  const char*  TIDNotifConfig::SPEEDUP_POA_KEY    =
    "TIDNotif.poa.speedup";
//   const char*  TIDNotifConfig::CORBA_CALLS_KEY    =
//     "TIDNotif.corba.calls";



//   //
//   // Trace Logs options
//   //
//   const char*  TIDNotifConfig::TRACE_LEVEL_KEY    =
//     "TIDNotif.trace.level";
//   const char*  TIDNotifConfig::TRACE_DATE_KEY     =
//     "TIDNotif.trace.date";
//   const char*  TIDNotifConfig::TRACE_APPNAME_KEY  =
//     "TIDNotif.trace.appname";
//   const char*  TIDNotifConfig::TRACE_TO_FILE_KEY  =
//     "TIDNotif.trace.tofile";
//   const char*  TIDNotifConfig::TRACE_FILENAME_KEY =
//     "TIDNotif.trace.filename";
//   const char*  TIDNotifConfig::TRACE_FILESIZE_KEY =
//     "TIDNotif.trace.file_size";
//   const char*  TIDNotifConfig::TRACE_NUMFILES_KEY =
//     "TIDNotif.trace.num_files";


  //
  // ORB port
  // 
  const char*  TIDNotifConfig::ADMIN_PORT_KEY     =
    "TIDNotif.orb.port";

  const char*  TIDNotifConfig::ADMIN_SSL_PORT_KEY =
    "TIDNotif.orb.ssl_port";


  //
  // IOR key
  //
  const char*  TIDNotifConfig::URL_MODE_KEY       =
    "TIDNotif.ior.urlmode";
  const char*  TIDNotifConfig::IOR_TO_FILE_KEY    =
    "TIDNotif.ior.tofile";
  const char*  TIDNotifConfig::IOR_PATH_KEY       =
    "TIDNotif.ior.path";
  const char*  TIDNotifConfig::IOR_FILENAME_KEY   =
    "TIDNotif.ior.filename";


  //
  // Paths
  //
  const char*  TIDNotifConfig::DATA_PATH_KEY      =
    "TIDNotif.data.path";
  const char*  TIDNotifConfig::DATA_ROOT_KEY      =
    "TIDNotif.data.root";
  const char*  TIDNotifConfig::OBJECTS_PATH_KEY   =
    "TIDNotif.objects.path";
  const char*  TIDNotifConfig::PROPS_FILENAME_KEY =
    "TIDNotif.property.filename";


  //
  // POAs
  //
  const char*  TIDNotifConfig::CHANNEL_POA_KEY    =
    "TIDNotif.channel.poa";
  const char*  TIDNotifConfig::SUPPLIER_POA_KEY   =
    "TIDNotif.supplier.poa";
  const char*  TIDNotifConfig::CONSUMER_POA_KEY   =
    "TIDNotif.consumer.poa";


//   //
//   //
//   //
//   const char*  TIDNotifConfig::CONTENTION_KEY     =
//     "TIDNotif.contention.active";
//   const char*  TIDNotifConfig::CONTENT_TIME_KEY   =
//     "TIDNotif.contention.time";
//   const char*  TIDNotifConfig::FLOOD_EVENTS_KEY   =
//     "TIDNotif.flood.numevents";
//   const char*  TIDNotifConfig::FLOOD_TIME_KEY     =
//     "TIDNotif.flood.time";


//   //
//   // Error
//   //
  const char*  TIDNotifConfig::RETURN_ON_ERROR_KEY=
    "TIDNotif.constraint.return";
  const char*  TIDNotifConfig::TIME_DEBUG_KEY     =
    "TIDNotif.debug.time";


//   //
//   // Request queue and POA PoolThreads options
//   //
//   const char*  TIDNotifConfig::ROOTPOA_QUEUE_KEY =
//     "TIDNotif.rootpoa.queuesize";
//   const char*  TIDNotifConfig::ROOTPOA_MAXTHR_KEY=
//     "TIDNotif.rootpoa.maxthreads";
//   const char*  TIDNotifConfig::ROOTPOA_MINTHR_KEY=
//     "TIDNotif.rootpoa.minthreads";



  const char*  TIDNotifConfig::SUPPLIER_QUEUE_KEY =
    "TIDNotif.supplier.queuesize";
  const char*  TIDNotifConfig::SUPPLIER_MAXTHR_KEY=
    "TIDNotif.supplier.maxthreads";
  const char*  TIDNotifConfig::SUPPLIER_MINTHR_KEY=
    "TIDNotif.supplier.minthreads";

  const char*  TIDNotifConfig::CONSUMER_QUEUE_KEY =
    "TIDNotif.consumer.queuesize";
  const char*  TIDNotifConfig::CONSUMER_MAXTHR_KEY=
    "TIDNotif.consumer.maxthreads";
  const char*  TIDNotifConfig::CONSUMER_MINTHR_KEY=
    "TIDNotif.consumer.minthreads";

  const char*  TIDNotifConfig::CHANNEL_QUEUE_KEY =
    "TIDNotif.internal.queuesize";
  const char*  TIDNotifConfig::CHANNEL_MAXTHR_KEY=
    "TIDNotif.internal.maxthreads";
  const char*  TIDNotifConfig::CHANNEL_MINTHR_KEY=
    "TIDNotif.internal.minthreads";

  const char*  TIDNotifConfig::FILTER_QUEUE_KEY =
    "TIDNotif.filter.queuesize";
  const char*  TIDNotifConfig::FILTER_MAXTHR_KEY=
    "TIDNotif.filter.maxthreads";
  const char*  TIDNotifConfig::FILTER_MINTHR_KEY=
    "TIDNotif.filter.minthreads";


//   //
//   // Date and time format
//   //
//   const char*  TIDNotifConfig::DATE_FORMAT_KEY =
//     "TIDNotif.format.date";
//   const char*  TIDNotifConfig::TIME_FORMAT_KEY =
//     "TIDNotif.format.time";



  //
  // Root
  //
//   const char*  TIDNotifConfig::ORB_KEY_PREFIX  =
//     "es.tid.TIDorbC";
  const char*  TIDNotifConfig::NOTIF_KEY_PREFIX  =
    "TIDNotif";



  //
  // TIDNotif config table (default values)
  // 
  //const char * TIDNotifConfig::configTable[][52] =
  const char * TIDNotifConfig::configTable[][SIZE_CONFIG_TABLE] =
    {
      
      // none, file, oracle
      { PERS_DB_KEY,
        TIDConfig::STRTYPE,
        TIDConfig::READ_WRITE,
        "none" },


//       { DB_URL_KEY,
//         TIDConfig::STRTYPE, 
//         TIDConfig::READ_WRITE,
//         "jdbc:oracle:thin:@host:1521:db" },

//       { DB_USER_KEY,
//         TIDConfig::STRTYPE,
//         TIDConfig::READ_WRITE,
//         "user" },

//       { DB_PASSWORD_KEY,
//         TIDConfig::STRTYPE,
//         TIDConfig::READ_WRITE,
//         "password" },

//       { DB_POOLMAXCONNS_KEY,
//         TIDConfig::NUMTYPE,
//         TIDConfig::READ_WRITE,
//         "5","0","99" },

//       { DB_CACHESIZE_KEY,
//         TIDConfig::NUMTYPE,
//         TIDConfig::READ_WRITE,
//         "1000","0","99999" },


      { MAX_DISCONNECTED_TIME,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "0","0","999999" },

      { MAX_COMM_FAILURES,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "-1","-1","99999" },

      // 0=none /  1=lock / 2=destroy
      { ON_COMM_FAILURE,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "0", "0", "2" },

      { MAX_NO_RESPONSE,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "-1","-1","99999" },

      // 0=none /  1=lock / 2=destroy
      { ON_NO_RESPONSE,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "0", "0", "2" },

      //{ ORB_BUG_KEY, TIDConfig::BOOLTYPE, TIDConfig::READ_ONLY, "false" },
      { SPEEDUP_POA_KEY,
        TIDConfig::BOOLTYPE,
        TIDConfig::READ_ONLY,
        "true" },

//       { CORBA_CALLS_KEY,
//         TIDConfig::BOOLTYPE,
//         TIDConfig::READ_ONLY,
//         "true" },


//       { TRACE_LEVEL_KEY,
//         TIDConfig::NUMTYPE,
//         TIDConfig::READ_WRITE,
//         "0" , "0", "4" },

//       { TRACE_DATE_KEY,
//         TIDConfig::BOOLTYPE,
//         TIDConfig::READ_WRITE,
//         "true" },

//       { TRACE_APPNAME_KEY,
//         TIDConfig::STRTYPE,
//         TIDConfig::READ_WRITE,
//         "null" },

//       { TRACE_TO_FILE_KEY,
//         TIDConfig::BOOLTYPE,
//         TIDConfig::READ_WRITE,
//         "true" },

//       { TRACE_FILENAME_KEY,
//         TIDConfig::STRTYPE,
//         TIDConfig::READ_WRITE,
//         "tidnotif" },

//       { TRACE_NUMFILES_KEY,
//         TIDConfig::NUMTYPE,
//         TIDConfig::READ_WRITE,
//         "1" ,"1","99" },

//       { TRACE_FILESIZE_KEY,
//         TIDConfig::NUMTYPE,
//         TIDConfig::READ_WRITE,
//         "4096000" , "1024", "99999999" },


      // Directorio temporal donde almacenar schemas
      { DATA_PATH_KEY,
        TIDConfig::STRTYPE,
        TIDConfig::READ_WRITE,
        "." },

      { DATA_ROOT_KEY,
        TIDConfig::STRTYPE,
        TIDConfig::READ_WRITE,
        ".notif" },

      { OBJECTS_PATH_KEY,
        TIDConfig::STRTYPE,
        TIDConfig::READ_WRITE,
        "db" },

      { PROPS_FILENAME_KEY,
        TIDConfig::STRTYPE,
        TIDConfig::READ_ONLY,
        "properties" },

      // No tiene mucha utilidad, solo para comprobar que es iidentico al del ORB
      { ADMIN_PORT_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "0","1025","99999" },

      { ADMIN_SSL_PORT_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "0","1025","99999" },


      { URL_MODE_KEY,
        TIDConfig::BOOLTYPE,
        TIDConfig::READ_WRITE,
        "false" },

      { IOR_TO_FILE_KEY,
        TIDConfig::BOOLTYPE,
        TIDConfig::READ_WRITE,
        "true" },

      { IOR_PATH_KEY,
        TIDConfig::STRTYPE,
        TIDConfig::READ_WRITE,
        "./" },

      { IOR_FILENAME_KEY,
        TIDConfig::STRTYPE,
        TIDConfig::READ_WRITE,
        "agent" },


      // 0=none /  1=common / 2=exclusive
      // 0=global /  1=local
      { CHANNEL_POA_KEY, 
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "1" , "0", "1"},

      // 0=global /  1=local / 2=exclusive
      { SUPPLIER_POA_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "2" , "0", "2"},

      { CONSUMER_POA_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "2" , "0", "2"},

//       // No se permitira que lleguen eventos al canal con un ritmo superior a
//       // FLOOD_EVENTS_KEY por FLOOD_TIME_KEY, de ser asi se esperara
//       // CONTENT_TIME_KEY milliseconds
//       { CONTENTION_KEY,
//         TIDConfig::BOOLTYPE,
//         TIDConfig::READ_WRITE,
//         "false" },

//       { CONTENT_TIME_KEY,
//         TIDConfig::NUMTYPE,
//         TIDConfig::READ_WRITE,
//         "25","10","1000" },

//       { FLOOD_EVENTS_KEY,
//         TIDConfig::NUMTYPE,
//         TIDConfig::READ_WRITE,
//         "10","1","10000"},

//       { FLOOD_TIME_KEY,
//         TIDConfig::NUMTYPE,
//         TIDConfig::READ_WRITE,
//         "200","10","1000"},


      { RETURN_ON_ERROR_KEY,
        TIDConfig::BOOLTYPE,
        TIDConfig::READ_WRITE, 
        "true" },

      { TIME_DEBUG_KEY,
        TIDConfig::BOOLTYPE,
        TIDConfig::READ_WRITE,
        "false" },

//       { ROOTPOA_QUEUE_KEY,
//         TIDConfig::NUMTYPE,
//         TIDConfig::READ_WRITE,
//         "250000","0","99999" },

//       { ROOTPOA_MAXTHR_KEY,
//         TIDConfig::NUMTYPE,
//         TIDConfig::READ_WRITE,
//         "45","-1","99999" },

//       { ROOTPOA_MINTHR_KEY,
//         TIDConfig::NUMTYPE,
//         TIDConfig::READ_WRITE,
//         "5","0","99999" },

      { SUPPLIER_QUEUE_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "25000","0","99999" },

      { SUPPLIER_MAXTHR_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "20","-1","99999" },

      { SUPPLIER_MINTHR_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "-1","-1","99999" },

      { CONSUMER_QUEUE_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "75000","0","99999" },

      { CONSUMER_MAXTHR_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "40","-1","99999"},

      { CONSUMER_MINTHR_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "-1","-1","99999"},

      { CHANNEL_QUEUE_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "25000","0","99999"},

      { CHANNEL_MAXTHR_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "25","-1","99999" },

      { CHANNEL_MINTHR_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "-1","-1","99999" },

      { FILTER_QUEUE_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "25000","0","99999"},

      { FILTER_MAXTHR_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "25","-1","99999" },

      { FILTER_MINTHR_KEY,
        TIDConfig::NUMTYPE,
        TIDConfig::READ_WRITE,
        "-1","-1","99999" },

//       { DATE_FORMAT_KEY,
//         TIDConfig::STRTYPE,
//         TIDConfig::READ_WRITE,
//         "dd-MM-yyyy" },

//       { TIME_FORMAT_KEY,
//         TIDConfig::STRTYPE,
//         TIDConfig::READ_WRITE,
//         "HH:mm:ss" },

    };

}; //namespace util
}; //namespace TIDNotif
  
/*
 * Private constructor
 *
 */
TIDNotif::util::TIDNotifConfig::TIDNotifConfig(const TIDConfig::Property& new_values)
{
  config = new TIDConfig(NOTIF_KEY_PREFIX, new_values);
}

TIDNotif::util::TIDNotifConfig::TIDNotifConfig(const char ** values, int rows)
{
  config = new TIDConfig(NOTIF_KEY_PREFIX, values, rows);
}

TIDNotif::util::TIDNotifConfig* 
TIDNotif::util::TIDNotifConfig::init(const TIDConfig::Property& props)
{
  if (config == NULL) {
    TIDNotifConfig* notifconfig = new TIDNotifConfig(props);
    if (strcmp(config->get(TIDNotifConfig::PERS_DB_KEY),"none") && 
        strcmp(config->get(TIDNotifConfig::ADMIN_PORT_KEY),"0"))
      config->store();
    return notifconfig;
  }
  return NULL;
}

TIDNotif::util::TIDNotifConfig* 
TIDNotif::util::TIDNotifConfig::init(const char** props_string, int nargs)
{
  if (config == NULL) {
    TIDNotifConfig* notifconfig = new TIDNotifConfig(props_string, nargs);
    if (strcmp(config->get(TIDNotifConfig::PERS_DB_KEY),"none") && 
        strcmp(config->get(TIDNotifConfig::ADMIN_PORT_KEY),"0"))
      config->store();
    return notifconfig;
  }
  return NULL;
}

void TIDNotif::util::TIDNotifConfig::updateConfig(const char** args, int nargs)
{
  if (config != NULL) {
    config->updateConfig(args,nargs);
  }
}

void TIDNotif::util::TIDNotifConfig::updateConfig(const TIDConfig::Property& props)
{
  if (config != NULL)
    config->updateConfig(props);
}

const char* TIDNotif::util::TIDNotifConfig::get(const char* key)
{
  if (config == NULL)
    throw CORBA::UNKNOWN("IllegalStateException");
  return config->get(key);
}
  
int TIDNotif::util::TIDNotifConfig::getInt(const char* key)
{
  if (config == NULL) {
    throw CORBA::UNKNOWN("IllegalStateException");
  }
  try {
    return atoi(config->get(key));
  }
  catch (...) {}
  return 0;
}



bool TIDNotif::util::TIDNotifConfig::getBool(const char* key)
{
  if ( config == NULL) {
    throw CORBA::UNKNOWN("IllegalStateException");
  } try {
    return !strcmp("true",config->get(key));
  }
  catch (...) {
  }
  return false;
}


void TIDNotif::util::TIDNotifConfig::set(const char* key, const char* value )
{
  if (config == NULL) {
    throw CORBA::UNKNOWN("IllegalStateException");
  }
  config->set(key, value);
}


void TIDNotif::util::TIDNotifConfig::restore()
{
  if ( config != NULL) {
    config->load();
  }
}


void TIDNotif::util::TIDNotifConfig::store()
{
  if ( config != NULL) {
    if (strcmp(config->get(TIDNotifConfig::PERS_DB_KEY),"none") && 
        strcmp(config->get(TIDNotifConfig::ADMIN_PORT_KEY),"0"))
    config->store();
  }
}

