/*
 *  File name: NotifConfig.C
 *  File type: Body file.
 *  Date : March 2006
 *  Author: Tom� Aguado G�ez <taguado@gsyc.escet.urjc.es>
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

#include "NotifConfig.h"
#include "CORBA.h"
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include "IOManager.h"
#include "PropertiesMap.h"


namespace util
{

  /* Singleton initialization. */
  NotifConfig * NotifConfig::m_singleton = new NotifConfig();

  // Property Types

  const char * NotifConfig::NUMTYPE = "N";
  const char * NotifConfig::BOOLTYPE = "B";
  const char * NotifConfig::STRTYPE  = "S";

  // Property Attributes
  const char * NotifConfig::READ_ONLY  = "RO";
  const char * NotifConfig::READ_WRITE = "RW";

  // Integer Value Limits

  const char * NotifConfig::NO_MIN = "";
  const char * NotifConfig::NO_MAX = "";

  // Boolean Values
  const char * NotifConfig::TRUE_VALUE = "true";
  const char * NotifConfig::FALSE_VALUE = "false";

  const char* NotifConfig::DB_URL_KEY =
    "TIDNotif.database.url";
  const char*  NotifConfig::DB_USER_KEY =
    "TIDNotif.database.user";
  const char*  NotifConfig::DB_PASSWORD_KEY =
    "TIDNotif.database.password";
  const char*  NotifConfig::DB_POOLMAXCONNS_KEY =
    "TIDNotif.database.poolmaxconns";
  const char*  NotifConfig::DB_CACHESIZE_KEY =
    "TIDNotif.database.CacheSize";                          

  const char*  NotifConfig::PERS_DB_KEY =
    "TIDNotif.persistence.db";
  const char*  NotifConfig::RECOVERY_BOOT_KEY =
    "TIDNotif.persistence.load";

  const char*  NotifConfig::MAX_DISCONNECTED_TIME =
    "TIDNotif.consumer.max_disconnected_time";
  const char*  NotifConfig::MAX_COMM_FAILURES =
    "TIDNotif.consumer.max_comm_failures";
  const char*  NotifConfig::ON_COMM_FAILURE =
    "TIDNotif.consumer.on_comm_failure";
  const char*  NotifConfig::MAX_NO_RESPONSE =
    "TIDNotif.consumer.max_no_response";
  const char*  NotifConfig::ON_NO_RESPONSE =
    "TIDNotif.consumer.on_no_response";
  
   const char*  NotifConfig::SPEEDUP_POA_KEY    =
    "TIDNotif.poa.speedup";
  const char*  NotifConfig::CORBA_CALLS_KEY    =
    "TIDNotif.corba.calls";

  const char*  NotifConfig::TRACE_LEVEL_KEY    =
    "TIDNotif.trace.level";
  const char*  NotifConfig::TRACE_DATE_KEY     =
    "TIDNotif.trace.date";
  const char*  NotifConfig::TRACE_APPNAME_KEY  =
    "TIDNotif.trace.appname";

  const char*  NotifConfig::TRACE_TO_FILE_KEY  =
    "TIDNotif.trace.tofile";
  const char*  NotifConfig::TRACE_FILENAME_KEY =
    "TIDNotif.trace.filename";

  const char*  NotifConfig::TRACE_FILESIZE_KEY =
    "TIDNotif.trace.file_size";
  const char*  NotifConfig::TRACE_NUMFILES_KEY =
    "TIDNotif.trace.num_files";

  const char*  NotifConfig::ADMIN_PORT_KEY     =
    "TIDNotif.orb.port";

  const char*  NotifConfig::URL_MODE_KEY       =
    "TIDNotif.ior.urlmode";
  const char*  NotifConfig::IOR_TO_FILE_KEY    =
    "TIDNotif.ior.tofile";
  const char*  NotifConfig::IOR_PATH_KEY       =
    "TIDNotif.ior.path";
  const char*  NotifConfig::IOR_FILENAME_KEY   =
  "TIDNotif.ior.filename";

  const char*  NotifConfig::DATA_PATH_KEY      =
    "TIDNotif.data.path";
  const char*  NotifConfig::DATA_ROOT_KEY      =
    "TIDNotif.data.root";

  const char*  NotifConfig::OBJECTS_PATH_KEY   =
    "TIDNotif.objects.path";
  const char*  NotifConfig::PROPS_FILENAME_KEY =
    "TIDNotif.property.filename";

  const char*  NotifConfig::CHANNEL_POA_KEY    =
    "TIDNotif.channel.poa";
  const char*  NotifConfig::SUPPLIER_POA_KEY   =
    "TIDNotif.supplier.poa";
  const char*  NotifConfig::CONSUMER_POA_KEY   =
    "TIDNotif.consumer.poa";

  const char*  NotifConfig::CONTENTION_KEY     =
    "TIDNotif.contention.active";
  const char*  NotifConfig::CONTENT_TIME_KEY   =
    "TIDNotif.contention.time";
  const char*  NotifConfig::FLOOD_EVENTS_KEY   =
    "TIDNotif.flood.numevents";
  const char*  NotifConfig::FLOOD_TIME_KEY     =
    "TIDNotif.flood.time";

  const char*  NotifConfig::RETURN_ON_ERROR_KEY=
    "TIDNotif.constraint.return";

  const char*  NotifConfig::TIME_DEBUG_KEY     =
    "TIDNotif.debug.time";

  const char*  NotifConfig::ROOTPOA_QUEUE_KEY =
    "TIDNotif.rootpoa.queuesize";
  const char*  NotifConfig::ROOTPOA_MAXTHR_KEY=
    "TIDNotif.rootpoa.maxthreads";
  const char*  NotifConfig::ROOTPOA_MINTHR_KEY=
    "TIDNotif.rootpoa.minthreads";

  const char*  NotifConfig::SUPPLIER_QUEUE_KEY =
    "TIDNotif.supplier.queuesize";
  const char*  NotifConfig::SUPPLIER_MAXTHR_KEY=
    "TIDNotif.supplier.maxthreads";
  const char*  NotifConfig::SUPPLIER_MINTHR_KEY=
    "TIDNotif.supplier.minthreads";

  const char*  NotifConfig::CONSUMER_QUEUE_KEY =
    "TIDNotif.consumer.queuesize";
  const char*  NotifConfig::CONSUMER_MAXTHR_KEY=
    "TIDNotif.consumer.maxthreads";
  const char*  NotifConfig::CONSUMER_MINTHR_KEY=
    "TIDNotif.consumer.minthreads";

  const char*  NotifConfig::CHANNEL_QUEUE_KEY =
    "TIDNotif.internal.queuesize";
  const char*  NotifConfig::CHANNEL_MAXTHR_KEY=
    "TIDNotif.internal.maxthreads";
  const char*  NotifConfig::CHANNEL_MINTHR_KEY=
    "TIDNotif.internal.minthreads";

    const char*  NotifConfig::DATE_FORMAT_KEY =
    "TIDNotif.format.date";
  const char*  NotifConfig::TIME_FORMAT_KEY =
    "TIDNotif.format.time";

  // Root
  const char*  NotifConfig::ORB_KEY_PREFIX  =
    "es.tid.TIDorbC";
  const char*  NotifConfig::NOTIF_KEY_PREFIX  =
    "TIDNotif";

  NotifConfig::~NotifConfig()
  {
  }

  /* Get singleton instance. */
  NotifConfig::NotifConfig &
  NotifConfig::get_instance()
  {
    if (!m_singleton)
      m_singleton = new NotifConfig();
    return *m_singleton;
  }

  NotifConfig::NotifConfig()
  {
    /* This default constructor will create all default properties. */
    bind_property_value(
      PERS_DB_KEY,
      new StringPropertyValue("file"));

    bind_property_value(
      DB_URL_KEY,
      new StringPropertyValue("jdbc:oracle:thin:@avena:1521:eforce1"));

    bind_property_value(
      DB_USER_KEY,
      new StringPropertyValue("owner1"));

    bind_property_value(
      DB_PASSWORD_KEY,
      new StringPropertyValue("owner1"));

    bind_property_value(
      DB_POOLMAXCONNS_KEY,
      new LongPropertyValue(5, 0, 90));

    bind_property_value(
      DB_CACHESIZE_KEY,
      new LongPropertyValue(1000, 0, 99999));

    bind_property_value(
      MAX_DISCONNECTED_TIME,
      new LongPropertyValue(0, 0, 999999));

    bind_property_value(
      MAX_COMM_FAILURES,
      new LongPropertyValue(-1, -1, 99999));

    // 0=none /  1=lock / 2=destroy
    bind_property_value(
      ON_COMM_FAILURE,
      new LongPropertyValue(0, 0, 2));

    bind_property_value(
      MAX_NO_RESPONSE,
      new LongPropertyValue(-1, -1, 99999));

    // 0=none /  1=lock / 2=destroy
    bind_property_value(
      ON_NO_RESPONSE,
      new LongPropertyValue(0, 0, 2));

    //{ ORB_BUG_KEY, NotifConfig::BOOLTYPE, NotifConfig::READ_ONLY, "false" },
    bind_property_value(
      SPEEDUP_POA_KEY,
      new BoolPropertyValue(true));

    bind_property_value(
      CORBA_CALLS_KEY,
      new BoolPropertyValue(true));

    bind_property_value(
      TRACE_LEVEL_KEY,
      new LongPropertyValue(0, 0, 4));

    bind_property_value(
      TRACE_DATE_KEY,
      new BoolPropertyValue(true));

    bind_property_value(
      TRACE_APPNAME_KEY,
      new StringPropertyValue("null"));

    bind_property_value(
      TRACE_TO_FILE_KEY,
      new BoolPropertyValue(true));

    bind_property_value(
      TRACE_FILENAME_KEY,
      new StringPropertyValue("tidnotif"));

    bind_property_value(
      TRACE_NUMFILES_KEY,
      new LongPropertyValue(1, 1, 99));

    bind_property_value(
      TRACE_FILESIZE_KEY,
      new LongPropertyValue(4096000, 1024, 99999999));

    // Directorio temporal donde almacenar schemas
    bind_property_value(
      DATA_PATH_KEY,
      new StringPropertyValue("."));

    bind_property_value(
      DATA_ROOT_KEY,
      new StringPropertyValue(".notif"));

    bind_property_value(
      OBJECTS_PATH_KEY,
      new StringPropertyValue("db"));

    bind_property_value(
      PROPS_FILENAME_KEY,
      new StringPropertyValue("properties"));

    // No tiene mucha utilidad, solo para comprobar que es iidentico al del ORB
    bind_property_value(
      ADMIN_PORT_KEY,
      new LongPropertyValue(2002, 1025, 99999));

    bind_property_value(
      URL_MODE_KEY,
      new BoolPropertyValue(false));

    bind_property_value(
      IOR_TO_FILE_KEY,
      new BoolPropertyValue(true));

    bind_property_value(
      IOR_PATH_KEY,
      new StringPropertyValue("./"));

    bind_property_value(
      IOR_FILENAME_KEY,
      new StringPropertyValue("agent"));

    // 0=none /  1=common / 2=exclusive
    // 0=global /  1=local
    bind_property_value(
      CHANNEL_POA_KEY, 
      new LongPropertyValue(1, 0, 1));

    // 0=global /  1=local / 2=exclusive
    bind_property_value(
      SUPPLIER_POA_KEY,
      new LongPropertyValue(2, 0, 2));

    bind_property_value(
      CONSUMER_POA_KEY,
      new LongPropertyValue(2, 0, 2));

    // No se permitira que lleguen eventos al canal con un ritmo superior a
    // FLOOD_EVENTS_KEY por FLOOD_TIME_KEY, de ser asi se esperara
    // CONTENT_TIME_KEY milliseconds
    bind_property_value(
      CONTENTION_KEY,
      new BoolPropertyValue(false));

    bind_property_value(
      CONTENT_TIME_KEY,
      new LongPropertyValue(25, 10, 1000));

    bind_property_value(
      FLOOD_EVENTS_KEY,
      new LongPropertyValue(10, 1, 10000));

    bind_property_value(
      FLOOD_TIME_KEY,
      new LongPropertyValue(200, 10, 1000));

    bind_property_value(
      RETURN_ON_ERROR_KEY,
      new BoolPropertyValue(true));

    bind_property_value(
      TIME_DEBUG_KEY,
      new BoolPropertyValue(false));

    bind_property_value(
      ROOTPOA_QUEUE_KEY,
      new LongPropertyValue(250000, 0, 99999));

    bind_property_value(
      ROOTPOA_MAXTHR_KEY,
      new LongPropertyValue(45, -1, 99999));

    bind_property_value(
      ROOTPOA_MINTHR_KEY,
      new LongPropertyValue(5, 0, 99999));

    bind_property_value(
      SUPPLIER_QUEUE_KEY,
      new LongPropertyValue(25000, 0, 99999));

    bind_property_value(
      SUPPLIER_MAXTHR_KEY,
      new LongPropertyValue(20, -1, 99999));

    bind_property_value(
      SUPPLIER_MINTHR_KEY,
      new LongPropertyValue(-1, -1, 99999));

    bind_property_value(
      CONSUMER_QUEUE_KEY,
      new LongPropertyValue(75000, 0, 99999));

    bind_property_value(
      CONSUMER_MAXTHR_KEY,
      new LongPropertyValue(40, -1, 99999));

    bind_property_value(
      CONSUMER_MINTHR_KEY,
      new LongPropertyValue(-1, -1, 99999));

    bind_property_value(
      CHANNEL_QUEUE_KEY,
      new LongPropertyValue(25000, 0, 99999));

    bind_property_value(
      CHANNEL_MAXTHR_KEY,
      new LongPropertyValue(25, -1, 99999));

    bind_property_value(
      CHANNEL_MINTHR_KEY,
      new LongPropertyValue(-1, -1, 99999));

    bind_property_value(
      DATE_FORMAT_KEY,
      new StringPropertyValue("dd-MM-yyyy"));

    bind_property_value(
      TIME_FORMAT_KEY,
      new StringPropertyValue("HH:mm:ss"));

  }

  void
  NotifConfig::store() const
  throw (NotifConfig::GeneralConfigError)
  {
    string filename = get_storage_filename();
    string dirname = filename.substr(0, filename.rfind("/"));

    /* Create (if not exists) configuration directory. */
    try
    {
      IOManager::create_directory_recursively(dirname, 0755);
    }
    catch (IOManager::IOError & e)
    {
      string msg = "cannot create configuracion directory due to a IO error: ";
      msg.append(e.error_msg);
      throw GeneralConfigError(msg);
    }

    fstream file(filename.c_str(),ios::out);

    if (!file)
    {
      string msg = "cannot open config file '";
      msg.append(filename + "' for storing");
      throw GeneralConfigError(msg);
    }

    PropertyValuesMap::const_iterator e;
    for (e = m_properties.begin(); e != m_properties.end(); e++)
    {
      file << e->first << " " << e->second->to_string() << endl;
      if (!file.good())
        throw GeneralConfigError("cannot write configuration file");
    }
    file.close();
    if (!file.good())
      throw GeneralConfigError("cannot close configuration file");
  }

  void
  NotifConfig::load()
  throw (NotifConfig::GeneralConfigError)
  {
    string filename = get_storage_filename();

    fstream file(filename.c_str(), ios::in);

    if (!file.good())
    {
      string msg = "cannot open config file '";
      msg.append(filename + "' for loading");
      throw NotifConfig::GeneralConfigError(msg);
    }

    string line,head,tail;
    int n;
    getline(file, line);
    while (!file.eof())
    {
      if (line == "")
        continue;
      n = line.find(" ");
      head = line.substr(0, n);
      tail = line.substr(n + 1);
      try
      {
        PropertyValue * value = find(head);
        value->from_string(tail);
      }
      catch (PropertyNotFound & e)
      {
        string msg = "cannot load config from disk: key '";
        msg.append(e.property_name + "' not found");
        throw GeneralConfigError(msg);
      }
      catch (PropertyValue::InvalidStringFormat & e)
      {
        string msg = "cannot load config from disk: key '";
        msg.append(head + "' cannot be correctly interpreted");
        throw GeneralConfigError(msg);
      }
      getline(file,line);
    }
    file.close();
  }

  string
  NotifConfig::get_prefix()
  {
    return m_key_prefix;
  };

  void
  NotifConfig::set_prefix(const string & prefix)
  {
    m_key_prefix = prefix;
  };

  /* Calculate storage filename using notification keys. */
  string
  NotifConfig::get_storage_filename() const
  throw (NotifConfig::GeneralConfigError)
  {
    string filename;

    try
    {
      /* Get data path key. */
      filename = get_property_value(DATA_PATH_KEY).to_string() + "/";

      /* Get data root key. */
      filename.append(get_property_value(DATA_ROOT_KEY).to_string() + "/");

      /* Get admin port key. */
      filename.append(get_property_value(ADMIN_PORT_KEY).to_string() + "/");

      /* Get properties filename key. */
      filename.append(get_property_value(PROPS_FILENAME_KEY).to_string());
    }
    catch (PropertyNotFound & e)
    {
      string msg = "cannot resolve storage filename: property '";
      msg.append(e.property_name + "' was not found");
      throw GeneralConfigError(msg);
    }

    return filename;
  }

}; /* Namespace NotifConfig */
