/*
 *  File name: IOManager.h
 *  File type: Header file.
 *  Date : April 26th 2006
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
 */

#ifndef _TIDNOTIF_UTIL_IO_MANAGER_H
#define _TIDNOTIF_UTIL_IO_MANAGER_H

#include <string>

#ifndef HAVE_STD_NAMESPACE
using namespace std;
#endif

namespace util {

/*!
 * \brief IO manager class.
 *
 * This pure-static class acts as an IO manager, offering many
 * static function members to access and manipulate OS files
 * and directories.
 *
 */
class IOManager
{

  public:

    /*!
     * \brief IO error exception.
     *
     * This exception encapsulates a generic IO subsystem error.
     *
     */
    typedef struct IOError
    {
      IOError(const string & msg) : error_msg(msg) {}
      string error_msg;
    } IOError;

    /*!
     * \brief Check if a file or directory exists.
     *
     * Check for the existence of a file or directory.
     *
     * \param filename File or directory name to be checked.
     * \return True if file ort directory exists. False if file
     * doesn't exists or path prefix is not a directory.
     * \throw IOError In case of any IO error but file not found or path
     * prefix is not a directory.
     */
    static bool file_exists(const string & filename)
      throw (IOError);

    /*!
     * \brief Check if a filename is a directory.
     *
     * Check if a filename is a directory.
     *
     * \param filename File name to be checked.
     * \return True if filename is a directory. False elsewhere.
     * \throw IOError In case of any IO error.
     */
    static bool is_directory(const string & filename)
      throw (IOError);

    /*!
     * \brief Create a new directory.
     *
     * Creates a new directory. If directory already exists (as directory,
     * not as a file), nothing is done.
     *
     * \param dirname Directory name to be created.
     * \param perms Unix permissions for new directory.
     * \throw IOError In case of IO error, but dir name already exists as
     * a directory.
     */
    static void create_directory(const string & dirname, int perms)
      throw (IOError);

    /*!
     * \brief Create a new directory recursively.
     *
     * Creates a new directory, even if prefix path doesn't exists,
     * creating all directories included in such path.
     *
     * \param path Directory name to be created.
     * \param perms Unix permissions for new directory.
     * \throw IOError In case of IO error.
     */
    static void create_directory_recursively(const string & path, int perms)
      throw (IOError);

  private:

    /*!
     * \brief Remove all duplicated slash symbols from a path.
     *
     * Remove all duplicated slash symbols from a path.
     *
     * \param path Path from which slash symbols must be eliminated.
     * \return Slash symbols-cleaned path.
     */
    static string remove_duplicated_slash_symbols(const string & path);

};

}; /* End of util namespace. */

#endif
