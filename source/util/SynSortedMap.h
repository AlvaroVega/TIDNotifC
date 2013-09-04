// -*- c++ -*-
/*
 *  File name: SynSortedMap.h
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

#ifndef _TIDUTIL_SYNSORTEDMAP_H_
#define _TIDUTIL_SYNSORTEDMAP_H_

#include <map>

#include "TIDThr.h"

#ifdef __SUNPRO_LIBRARY_IOSTREAM
using std::map;
#endif

#ifdef TIDORB_HAVE_NAMESPACE_STD
using namespace std;
#endif

namespace TIDNotif {
namespace util
{

  template< class T>
  class Ascendant
  {
  public:

    bool operator()(const T s,const  T t) const
    {
      return s<t;
    }
  };


  template< class S, class T, class R >
  class SynSortedMap
  {

  public:

    typedef map <S,T,Ascendant<S> > SortedMap;
    typedef typename SortedMap::iterator iterator_map;

    typedef map <S,S> FreeKeyMap;
    FreeKeyMap freeKeyMap;

    void put(S key,T element)
    {
      TIDThr::Synchronized sync(recursive_mutex);
      syn_sorted_map[key]=element;
      freeKeyMap.erase(key);
    }

    T get(S key)
    {
      TIDThr::Synchronized sync(recursive_mutex);
      typename SynSortedMap::SortedMap::iterator iter = syn_sorted_map.find(key);
      if (iter != syn_sorted_map.end())
          return syn_sorted_map[key];    
      else
          return NULL;
    }

    bool isEmpty()
    {
      TIDThr::Synchronized sync(recursive_mutex);
      return syn_sorted_map.empty();
    }

    void clear()
    {
      TIDThr::Synchronized sync(recursive_mutex);
      syn_sorted_map.clear();
      freeKeyMap.clear();
    }

    S lastKey()
    {
      TIDThr::Synchronized sync(recursive_mutex);
      S l_key;
      typename SynSortedMap::SortedMap::iterator iter = syn_sorted_map.end();
      l_key =(S) (iter->first);
      return l_key;
    }
  
    bool freeKey ()
    {
      return freeKeyMap.size();
    }

    S get_freeKey()
    {
      typename SynSortedMap::FreeKeyMap::iterator iter;
      iter = freeKeyMap.begin();
      return iter->first;
    }

    bool remove(S id)
    {
      TIDThr::Synchronized sync(recursive_mutex);
      typename SynSortedMap::SortedMap::iterator iter = syn_sorted_map.end();
      iter = syn_sorted_map.find(id);
      if (iter!=syn_sorted_map.end())
      {
        freeKeyMap[id]=id;
        syn_sorted_map.erase(id);
        return true;
      }
      else
      {
        return false;
      }
    }

    long size()
    {
      TIDThr::Synchronized sync(recursive_mutex);
      return syn_sorted_map.size();
    }

    R* keySet()
    {
      TIDThr::Synchronized sync(recursive_mutex);
      R* IDSeq;
      typename SynSortedMap::SortedMap::iterator iter;
      int i = 0;
      IDSeq = new R(syn_sorted_map.size());
      IDSeq->length(syn_sorted_map.size());
      for (iter=syn_sorted_map.begin() ; iter != syn_sorted_map.end(); iter++)
      {
        (*IDSeq)[ i++ ] = iter->first ;
      }//for
      return IDSeq;
    }

    iterator_map begin()
    {
      TIDThr::Synchronized sync(recursive_mutex);
      return syn_sorted_map.begin();
    }

    iterator_map end()
    {
      TIDThr::Synchronized sync(recursive_mutex);
      return syn_sorted_map.end();
    }

  private:

    SortedMap syn_sorted_map;

    TIDThr::RecursiveMutex recursive_mutex;

  };



}; /* End of namespace util. */
}; /* End of namespace TIDNotif. */

#endif
