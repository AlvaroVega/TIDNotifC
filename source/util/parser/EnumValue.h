/*
 *  File name: EnumValue.h
 *  File type: Head file.
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

#ifndef _TIDUTIL_ENUMVALUE_H_
#define _TIDUTIL_ENUMVALUE_H_ 

namespace TIDNotif{
namespace util{
namespace parser {
  
class EnumValue {

private:
  int num_value;
  char * string_value;
  char ** string_values;

public:

  EnumValue();

  EnumValue(char * , char ** );

  EnumValue(int , char ** );

  EnumValue(EnumValue * );

  EnumValue(int , char * , char ** );

  int numValue();

  char * stringValue();

  int stringValues(char * );
};

}; //namespace parser
}; //namespace util
}; //namespace TIDNotif

#endif
