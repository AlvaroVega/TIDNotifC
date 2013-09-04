/*
 *  File name: StringIDSeq.h
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
 */

#ifndef _TIDUTIL_STRINGIDSEQ_H_
#define _TIDUTIL_STRINGIDSEQ_H_

#include <CORBA.h>
#include <string>

#ifndef HAVE_NAMESPACE_STD
using namespace std;
#endif

namespace util
{


  class StringIDSeq
  {
  public:

    StringIDSeq() : m_buffer(NULL),
                    m_release(true),
                    m_length(0),
                    m_max_length(0) {}

    StringIDSeq(CORBA::ULong max) : m_buffer(NULL),
                                    m_release(true),
                                    m_length(0),
                                    m_max_length(max) {}

    StringIDSeq(CORBA::ULong max,
                CORBA::ULong length,
                string* data,
                CORBA::Boolean release = false) : m_buffer(data),
                                                  m_release(release),
                                                  m_length(length),
                                                  m_max_length(max) {}

    StringIDSeq(const StringIDSeq& other);

    ~StringIDSeq();

    StringIDSeq& operator=(const StringIDSeq&);

    CORBA::ULong maximum() const {return m_max_length;}

    void length(CORBA::ULong v);

    CORBA::ULong length() const {return m_length;}

    string operator[](CORBA::ULong index);

    const string operator[](CORBA::ULong index) const;

    CORBA::Boolean release() const {return m_release;}

    string* get_buffer(CORBA::Boolean orphan = false);

    const string* get_buffer() const;

    void replace(CORBA::ULong max, CORBA::ULong length, 
                 string* data, 
                 CORBA::Boolean release = false);

    static string* allocbuf(CORBA::ULong size);

    static void freebuf(string* buf);

  private:

    void allocbuf();
    void freebuf();
    string* m_buffer;
    CORBA::Boolean m_release;
    CORBA::ULong m_length;
    CORBA::ULong m_max_length;


  };



}
; /* End of namespace util. */

#endif
