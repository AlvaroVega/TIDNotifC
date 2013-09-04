/*
 *  File name: NotifConfig
 *  File type: Header file.
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


#ifndef _TIDUTIL_NOTIFCONFIG_H_
#define _TIDUTIL_NOTIFCONFIG_H_

#include <string>

#include "PropertiesMap.h"
#include "TIDPropValue.h"

#ifndef HAVE_STD_NAMESPACE
using namespace std;
#endif

namespace util
{

  /*!
   * \brief Notification configuration storage class.
   *
   * This singleton class is in charge of notification service
   * storage. Inheriting from PropertiesMap, it store properties
   * and its values, offering a new interface to load or store
   * configuration from disk.
   */
  class NotifConfig : public PropertiesMap
  {

  public:

    /*! \brief General configuration error exception. */
    typedef struct GeneralConfigError
    {
      GeneralConfigError(const string & msg) : cause(msg) {}
      string cause;
    } GeneralConfigError;

    static const int GLOBAL_POA    = 0;
    static const int LOCAL_POA     = 1;
    static const int EXCLUSIVE_POA = 2;

    static const int SIZE_CONFIG_TABLE = 52;

    static const char * DB_URL_KEY;
    static const char * DB_USER_KEY;
    static const char * DB_PASSWORD_KEY;
    static const char * DB_POOLMAXCONNS_KEY;
    static const char * DB_CACHESIZE_KEY;

    static const char * PERS_DB_KEY;
    static const char * RECOVERY_BOOT_KEY;

    static const char * MAX_DISCONNECTED_TIME;
    static const char * MAX_COMM_FAILURES;
    static const char * ON_COMM_FAILURE;
    static const char * MAX_NO_RESPONSE;
    static const char * ON_NO_RESPONSE;

    //static const char * ORB_BUG_KEY;
    static const char * SPEEDUP_POA_KEY;
    static const char * CORBA_CALLS_KEY;

    static const char * TRACE_LEVEL_KEY;
    static const char * TRACE_DATE_KEY;
    static const char * TRACE_APPNAME_KEY;
    static const char * TRACE_TO_FILE_KEY;
    static const char * TRACE_FILENAME_KEY;

    static const char * TRACE_FILESIZE_KEY;
    static const char * TRACE_NUMFILES_KEY;

    static const char * ADMIN_PORT_KEY;

    static const char * URL_MODE_KEY;
    static const char * IOR_TO_FILE_KEY;
    static const char * IOR_PATH_KEY;
    static const char * IOR_FILENAME_KEY;

    static const char * DATA_PATH_KEY;
    static const char * DATA_ROOT_KEY;
    static const char * OBJECTS_PATH_KEY;
    static const char * PROPS_FILENAME_KEY;

    static const char * CHANNEL_POA_KEY;
    static const char * SUPPLIER_POA_KEY;
    static const char * CONSUMER_POA_KEY;

    static const char * CONTENTION_KEY;
    static const char * CONTENT_TIME_KEY;
    static const char * FLOOD_EVENTS_KEY;
    static const char * FLOOD_TIME_KEY;

    static const char * RETURN_ON_ERROR_KEY;

    static const char * TIME_DEBUG_KEY;

    static const char * ROOTPOA_QUEUE_KEY;
    static const char * ROOTPOA_MAXTHR_KEY;
    static const char * ROOTPOA_MINTHR_KEY;

    static const char * SUPPLIER_QUEUE_KEY;
    static const char * SUPPLIER_MAXTHR_KEY;
    static const char * SUPPLIER_MINTHR_KEY;

    static const char * CONSUMER_QUEUE_KEY;
    static const char * CONSUMER_MAXTHR_KEY;
    static const char * CONSUMER_MINTHR_KEY;

    static const char * CHANNEL_QUEUE_KEY;
    static const char * CHANNEL_MAXTHR_KEY;
    static const char * CHANNEL_MINTHR_KEY;

    static const char * DATE_FORMAT_KEY;
    static const char * TIME_FORMAT_KEY;

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

    // Root
    static const char * ORB_KEY_PREFIX;
    static const char * NOTIF_KEY_PREFIX;

    ~NotifConfig();

    /*! \brief Get singleton instance. */
    static NotifConfig & get_instance();

     /*!
     * \brief Stores the active configuration in a file.
     * \throw ConfigFileStoreError The configuration could
     * not be stored in a file.
     */
    void store() const throw(GeneralConfigError);

     /*!
     * \brief Loads the configuration from a file.
     * \throw ConfigFileLoadError The configuration could not be loaded.
     */
    void load() throw(GeneralConfigError);


      /*!
     * \brief Returns the prefix of the configuration.
     * \return string prefix.
     */
    string get_prefix();

      /*!
     * \brief Sets the prefix of the configuration.
     * \param string The value we want the prefix to be.
     */
    void set_prefix(const string & prefix);

   private:

    string m_key_prefix;

    /*! \brief Singleton instance. */
    static NotifConfig* m_singleton;

    /*! \brief Default private constructor. */
    NotifConfig();

    /*! \brief Calculate storage filename using notification keys. */
    string get_storage_filename() const throw (GeneralConfigError);

  };

}; /* Namespace Util */

#endif
