/*
 *  File name: IOManager.C
 *  File type: Body file.
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

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#include "IOManager.h"

#ifndef HAVE_STD_NAMESPACE
using namespace std;
#endif

/* Check if a file exists.  */
bool
util::IOManager::file_exists(const string & filename)
throw (IOError)
{
  struct stat state;
  errno = 0;
  if (stat(filename.c_str(), &state))
  {
    if (errno == ENOENT || errno == ENOTDIR)
      return false;
    throw IOError(strerror(errno));
  }
  return true;
}

/*  Check if a filename is a directory. */
bool
util::IOManager::is_directory(const string & filename)
throw (IOError)
{
  struct stat state;
  errno = 0;
  if (stat(filename.c_str(), &state) < 0)
  {
    throw IOError(strerror(errno));
  }
  return S_ISDIR(state.st_mode);
}

/* Create a new directory. */
void
util::IOManager::create_directory(const string & dirname, int perms)
throw (IOError)
{
  string error_cause;
  errno = 0;
  if (mkdir(dirname.c_str(), perms) < 0)
  {
    switch (errno)
    {
      case EEXIST:
        if (!is_directory(dirname))
          error_cause = "file exists and is not a directory";
        else
          return; /* No error if directory already exists. */
        break;
      case ENOENT:
        error_cause = "some prefix path doesn't exists";
        break;
      case ENOTDIR:
        error_cause = "some prefix path is not a directory";
        break;
      default:
        error_cause = strerror(errno);
        break;
    }
    throw IOError(dirname + ": " + error_cause);
  }
}

/* Create a new directory recursively. */
void
util::IOManager::create_directory_recursively(const string & path, int perms)
throw (IOError)
{
  string prefix, suffix;
  string::size_type loc;

  prefix.clear();
  suffix = remove_duplicated_slash_symbols(path);
  for (;;)
  {
    loc = suffix.find("/", 1);
    if (loc == string::npos)
      break;
    prefix += suffix.substr(0, loc + 1);
    suffix.erase(0, loc + 1);
    create_directory(prefix, perms);
  }
  create_directory(path, perms);
}

/* Remove all duplicated slash symbols from a path. */
string
util::IOManager::remove_duplicated_slash_symbols(const string & path)
{
  string result = path;
  string::size_type loc;

  for (;;)
  {
    loc = result.find("//", 0);
    if (loc == string::npos)
      break;
    result.replace(loc, 2, "/", 0, 1);
  }
  return result;
}
