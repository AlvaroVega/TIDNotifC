// -*- c++ -*-
/*
 *  File name: AlreadyInitialized.h
 *  File type: Header file.
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

#ifndef _TIDNOTIF_ALREADYINITIALIZED_H_
#define _TIDNOTIF_ALREADYINITIALIZED_H_


#include <iostream>

#include <exception>
#include <string>


using namespace std;


namespace TIDNotif
{

    class AlreadyInitialized : public exception
    {

    public:

      AlreadyInitialized(const char* msg = "", int error = 0);

      ~AlreadyInitialized() throw () {}

      const char* what() const throw() { return m_what.data();}

      virtual const char* getName() const {return "AlreadyInitialized";}
      const char* getReason() const {return m_reason.data();}
      int getErrno() const {return m_errno;}

    protected:

      std::string m_reason;
      int m_errno;
      std::string m_what;
    };


}

ostream& operator << (ostream& os, const TIDNotif::AlreadyInitialized& ex);

#endif
