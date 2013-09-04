/*
 *  File name: Debugger.h
 *  File type: Header file.
 *  Date : 16th February 2006
 *  Author: Alvaro Polo Valdenebro <apoloval@gsyc.escet.urjc.es>
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
 *   - 03/03/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Argument 'object_address' from member function 'send_message'
 *         now uses 'const void *' type instead of 'void *'.
 *   - 03/06/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Crash reporting functions added.
 *   - 03/28/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Object pointer is now of type 'const SimpleNode*' instead
 *         of 'const void *' to allow type information to be correctly
 *         printed.
 *   - 03/30/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * New method 'deactivate_debug()'.
 *   - 03/31/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * New functionality to debug allocated memory.
 *   - 04/10/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Method argument 'msg' for 'send_message' must be const.
 */

#ifndef _TIDUTIL_DEBUGGER_H
#define _TIDUTIL_DEBUGGER_H

#ifndef HAVE_STD_NAMESPACE
using namespace std;
#endif

#include <fstream>
#include <string>
#include <map>

#include "SimpleNode.h"

namespace TIDNotif {
namespace util {
namespace parser {

/*!
 *
 * \brief Debugger class.
 *
 * This class is used to send debuggind messages.
 */
class Debugger
{

  public:

    /*!
     * \brief Activate debugger to start working with standard error output.
     * \param level Debugging level.
     */
    static void activate_debug(unsigned int level);

    /*!
     * \brief Activate debugger to start working with file output.
     * \param filename File name to be used as output.
     * \param level Debugging level.
     */
    static void activate_debug(const char * filename, unsigned int level);

    /*!
     * \brief Deactivate debugger to start working with standard error output.
     * \param level Debugging level.
     */
    static void deactivate_debug();

    /*!
     * \brief Send a debug message.
     * \param level Debugging level for message to be shown.
     * \param msg Message to be shown.
     * \param object_address Object address.
     */
    static void send_message(unsigned int level,
                             const char * msg,
                             const SimpleNode * object_address = NULL);

    /*!
     * \brief Send a crash report.
     * \param msg Crash message to be shown.
     * \param object_address Object address.
     */
    static void report_crash(char * msg,
                             const SimpleNode * object_address = NULL);
                             
    /*!
     * \brief Register a memory allocation
     * \param address Allocated memory.
     */
    static void register_malloc(const SimpleNode * address);

    /*!
     * \brief Register a memory freed.
     * \param address Freed memory.
     */
    static void register_free(const SimpleNode * address);

    /*!
     * \brief Report registered memory.
     */
    static void report_registered_memory();

  private:

    /*!
     * \brief Default constructor.
     *
     * Uses standard error output to send debugging messages.
     * \param level Debugging level.
     */
    Debugger(unsigned int level);

    /*!
     * \brief File name constructor.
     * \param filename File name to be used as output.
     * \param level Debugging level.
     */
    Debugger(const char * filename, unsigned int level);

    /*!
     * \brief Destructor.
     */
    ~Debugger();

    /*!
     * \brief Send message to corresponding output.
     */
    void print_msg(const char * msg, bool new_line) const;

    /*!
     * \brief Send hexadecimal number to corresponding output.
     */
    void print_hex_number(CORBA::ULongLong number, bool new_line) const;

    /*!
     * \brief Output stream to send debugging messages.
     */
    fstream * m_output;

    /*!
     * \brief Debugging level.
     */
    unsigned int m_level;

    /*!
     * \brief Type definition of map of registered allocated memory.
     */
    typedef map<const SimpleNode*, bool> RegisteredMemoryMap;

    /*!
     * \brief Map of registered allocated memory.
     */
    RegisteredMemoryMap m_registered_memory;
    
    /*!
     * \brief Singleton object.
     */
    static Debugger * m_singleton;

};

} /* End of namespace parser.  */
} /* End of namespace util. */
} /* End of namespace TIDNotif. */

#endif
