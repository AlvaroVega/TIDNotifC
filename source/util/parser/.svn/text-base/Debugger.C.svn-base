/*
 *  File name: Debugger.C
 *  File type: Body file.
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
 *       * Bad end of line printing corrected.
 *       * Bad spacing at printing corrected.
 *   - 03/06/2006 by Alvaro Polo <apoloval@gsyc.escet.urjc.es>
 *       * Crash reporting functions added.
 *       * Crash report forces the debugger activation.
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

#include <stdio.h>
#include <typeinfo>

#include "Debugger.h"

namespace TIDNotif {
namespace util {
namespace parser {

/* Singleton initialization. */
Debugger * Debugger::m_singleton = NULL;

/* Activate debugger to start working with standard error output. */
void
Debugger::activate_debug(unsigned int level)
{
  if (! m_singleton)
    m_singleton = new Debugger(level);
}

/* Activate debugger to start working with file output. */
void
Debugger::activate_debug(const char * filename, unsigned int level)
{
  if (! m_singleton)
    m_singleton = new Debugger(filename, level);
}

/* Deactivate debugger to start working with standard error output. */
void
Debugger::deactivate_debug()
{
  if (m_singleton) delete m_singleton;
}

void
Debugger::send_message(unsigned int level,
                       const char * msg,
                       const SimpleNode * object_address)
{
  if (!m_singleton)
    return;
  if (level <= m_singleton->m_level)
  {
    if (object_address)
    {
      m_singleton->print_msg("Message from instance of ", false);
      try
      {
        m_singleton->print_msg(typeid(*object_address).name(), false);
      }
      catch (...)
      {
        m_singleton->print_msg("unknown", false);
      }
      m_singleton->print_msg(" at address ", false);
      m_singleton->print_hex_number((CORBA::ULongLong)object_address, false);
      m_singleton->print_msg(": ", false);
    }
    m_singleton->print_msg(msg, true);
  }
}

/* Send a crash report. */
void
Debugger::report_crash(char * msg,
                       const SimpleNode * object_address)
{
  activate_debug(1000);

  m_singleton->print_msg("", true);
  m_singleton->print_msg("*-*-*-*-*-*-*-*-*-*-*-*-*", true);
  m_singleton->print_msg("* APPLICATION CRASH !!! *", true);
  m_singleton->print_msg("*-*-*-*-*-*-*-*-*-*-*-*-*", true);
  m_singleton->print_msg("", true);

  if (object_address)
  {
    m_singleton->print_msg("Object instance of ", false);
    try
    {
      m_singleton->print_msg(typeid(*object_address).name(), false);
    }
    catch (...)
    {
      m_singleton->print_msg("unknown", false);
    }
    m_singleton->print_msg(" at address ", false);
    m_singleton->print_hex_number((CORBA::ULongLong)object_address, false);
    m_singleton->print_msg(" reports next hard error: ", true);
    m_singleton->print_msg("", true);
  }
  m_singleton->print_msg(msg, true);
  m_singleton->print_msg("", true);
}

/* Register a memory allocation. */
void
Debugger::register_malloc(const SimpleNode * address)
{
  if (m_singleton)
    m_singleton->m_registered_memory[address] = true;  
}

/* Register a memory freed. */
void
Debugger::register_free(const SimpleNode * address)
{
  if (m_singleton)
    m_singleton->m_registered_memory[address] = false;  
}

/* Report registered memory. */
void
Debugger::report_registered_memory()
{
  RegisteredMemoryMap::const_iterator it;
  
  if (m_singleton)
  {
    m_singleton->print_msg("", true);
    m_singleton->print_msg("*-*-*-*-*-*-*-*-*-*-*-*-*-*", true);
    m_singleton->print_msg("* ALLOCATED MEMORY REPORT *", true);
    m_singleton->print_msg("*-*-*-*-*-*-*-*-*-*-*-*-*-*", true);
    m_singleton->print_msg("", true);
    for (it = m_singleton->m_registered_memory.begin();
         it != m_singleton->m_registered_memory.end();
         it++)
    {
      if (it->second)
      {
        m_singleton->print_msg("Memory allocated at ", false);
        m_singleton->print_hex_number((CORBA::ULongLong)it->first, false);
        m_singleton->print_msg(" of type ", false);
        m_singleton->print_msg(typeid(*(it->first)).name(), false);
        m_singleton->print_msg(".", true);
      }
    }
  }
}

/* Default constructor. */
Debugger::Debugger(unsigned int level)
:
m_output(NULL),
m_level(level)
{}

/* Filename constructor. */
Debugger::Debugger(const char * filename, unsigned int level)
:
m_output(new fstream(filename, ios::app)),
m_level(level)
{}

/* Destructor. */
Debugger::~Debugger()
{
  if (m_output)
    delete m_output;
}

void
Debugger::print_msg(const char * msg, bool new_line) const
{
  if (m_output)
  {
    *m_output << msg;
    if (new_line)
      *m_output << endl;
  }
  else
  {
    cerr << msg;
    if (new_line)
      cerr << endl;
  }
}

void 
Debugger::print_hex_number(CORBA::ULongLong number, bool new_line) const
{
  char buff[255];

  sprintf(buff, "%x", number);

  if (m_output)
  {
    *m_output << "0x" << buff;
    if (new_line)
      *m_output << endl;
  }
  else
  {
    cerr << "0x" << buff;
    if (new_line)
      cerr << endl;
  }
}

} /* End of namespace parser.  */
} /* End of namespace util. */
} /* End of namespace TIDNotif. */
