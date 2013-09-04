/*
 *  File name: StringIDSeq.C
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
 */

#include "StringIDSeq.h"
namespace util
{

  StringIDSeq::StringIDSeq(const StringIDSeq& other): m_release(true),m_length(other.m_length),m_max_length(other.m_max_length)
  {
    allocbuf();
    for(CORBA::ULong i = 0; i < m_length; i++)
      m_buffer[i] = other.m_buffer[i];
  }

  StringIDSeq::~StringIDSeq()
  {
    freebuf();
  }

  StringIDSeq& StringIDSeq::operator=(const StringIDSeq& other)
  {
    if(this == &other)
      return *this;
    freebuf();
    m_release = true;
    m_length = other.m_length;
    m_max_length = other.m_max_length;
    allocbuf();
    for(CORBA::ULong i = 0; i < m_length; i++)
      m_buffer[i] = other.m_buffer[i];
    return *this;
  }

  void StringIDSeq::length(CORBA::ULong v)
  {
    if(!m_buffer)
    {
      m_release = true;
      m_length = v;
      m_max_length = (v > m_max_length)? v : m_max_length;
      allocbuf();
      return;
    }
    if(v > m_max_length)
    {
      string* aux = new string[v];
      for(CORBA::ULong i = 0; i < m_length; i++)
        aux[i] = m_buffer[i];
      freebuf();
      m_buffer = aux;
      m_release = true;
      m_max_length = v;
    }
    if(v > m_length)
    {
      for(CORBA::ULong i = m_length; i < v; i++)
      {
        string* _default = new string();
        m_buffer[i] = *_default;
        delete _default;
      }
    }
    m_length = v;
  }

  string StringIDSeq::operator[](CORBA::ULong index)
  {
    if (index < m_length)
      return m_buffer[index];
    else
      throw CORBA::BAD_PARAM("Current sequence length exceded");
  }

  const string StringIDSeq::operator[] (CORBA::ULong index) const
  {
    if (index < m_length)
      return m_buffer[index];
    else
      throw CORBA::BAD_PARAM("Current sequence length exceded");
  }

  string* StringIDSeq::get_buffer(CORBA::Boolean orphan)
  {
    if(!m_buffer)
      allocbuf();
    if(orphan)
    {  // caller assumes ownership
      string* aux;
      if(!m_release)
        aux = NULL;
      else
      {
        aux = m_buffer;
      }
      m_release = true;
      m_buffer = NULL;
      m_max_length = 0;
      m_length = 0;
      return aux;
    }
    return m_buffer;
  }

  const string* StringIDSeq::get_buffer() const
  {
    if(!m_buffer)
      (const_cast< StringIDSeq* > (this))->allocbuf();
    return (const string*) m_buffer;
  }

  void StringIDSeq::replace(CORBA::ULong max, CORBA::ULong length, string* data, CORBA::Boolean release )
  {
    freebuf();
    m_buffer = data;
    m_length = length;
    m_max_length = max;
    m_release = release;
  }

  void StringIDSeq::allocbuf()
  {
    if(m_max_length > 0)
    {
      m_buffer =  new string[m_max_length];
      m_release = true;
    }
    else
      m_buffer = NULL;
  }

  string* StringIDSeq::allocbuf(CORBA::ULong size)
  {
    return new string[size];
  }

  void StringIDSeq::freebuf()
  {
    if(m_release && m_buffer)
      delete[] m_buffer;
  }

  void StringIDSeq::freebuf(string* buf)
  {
    delete[] buf;
  }


};
