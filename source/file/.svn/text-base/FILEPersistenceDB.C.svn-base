/*
 *  File name: FILEPersistenceDB.C
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
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include "FILEPersistenceDB.h"
#include "TIDNotifConfig.h"
#include "IOException.h"
#include "TimeBase.h"
#include "ThePOAFactory.h"
#include "CORBA.h"
#include "FilterImpl.h"
#include "PersistenceManager.h"


namespace TIDNotif {

namespace file {

  const char * FILEPersistenceDB::DIR_CHANNEL_FACTORY       = "channel_factory";
  const char * FILEPersistenceDB::DIR_CHANNEL               = "channels";
  const char * FILEPersistenceDB::DIR_SUPPLIER_ADMIN        = "s_admins";
  const char * FILEPersistenceDB::DIR_PROXY_PUXX_CONSUMER   = "p_consumers";
  const char * FILEPersistenceDB::DIR_CONSUMER_ADMIN        = "c_admins";
  const char * FILEPersistenceDB::DIR_PROXY_PUXX_SUPPLIER   = "p_suppliers";
  const char * FILEPersistenceDB::DIR_DISCRIMINATOR         = "discriminators";
  const char * FILEPersistenceDB::DIR_INDEXLOCATOR          = "i_locators";
  const char * FILEPersistenceDB::DIR_TRANSFORMING_OPERATOR = "t_operators";
  const char * FILEPersistenceDB::DIR_MAPPING_DISCRIMINATOR = "m_discriminators";
  
  const char * FILEPersistenceDB::FILE_UID_DATA = "uid.data";
  
  const char * FILEPersistenceDB::FILE_CHANNEL_FACTORY = "c_f.data";
  

  const char* FILEPersistenceDB::SAVE[5] =
    { " +>FILEPersistenceDB.save(", NULL, ") [", NULL, "]" };
  const char* FILEPersistenceDB::UPDATE[5] =
    { " +>FILEPersistenceDB.update(", NULL, ") [", NULL, "]" };
  const char* FILEPersistenceDB::DELETE[5] =
    { " +>FILEPersistenceDB.delete(", NULL, ") [", NULL, "]" };
  const char* FILEPersistenceDB::LOAD[3] =
    { " +>FILEPersistenceDB.load(", NULL, ")" };
  const char* FILEPersistenceDB::PERSISTENCE_ERROR =
  "*** MUTUAL INCOMPATIBILITY BETWEEN PERSISTENT DATA AND SERVICE VERSION ***";

  
FILEPersistenceDB::FILEPersistenceDB( string id )
{
  _pers_id = id; // ???
  _base_path = getPath();
  mkDirs(_base_path);
  _uid_factory = new FileUID(_base_path + "/" + FILE_UID_DATA); 
  //TODO_MORFEO: name-separator character (Unix, Microsoft)
}
  //
  // Channel Methods
  //
  //
void FILEPersistenceDB::delete_data(TIDNotif::EventChannelImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->get_channelID();
  string id_string = id.str().data();
  SAVE[1] = NULL;
  SAVE[3] = id_string.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_CHANNEL);
  remove( path.c_str() );

}

bool FILEPersistenceDB::data_saved(ChannelID id)
{

  TIDorb::util::StringBuffer id_stream;
  id_stream << id;
  string id_string = id_stream.str();


  string the_file = makeFilename(id_string,
                                 TIDNotif::PersistenceDB::OBJ_CHANNEL);

  ifstream is(the_file.c_str(),ios::in|ios::binary);
  if (is.good())
    {
      is.close();
      return true;
    }
  else
    {
      return false;
    }
}



void FILEPersistenceDB::update_data(int what, TIDNotif::EventChannelImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->get_channelID();
  string id_string = id.str().data();
  SAVE[1] = NULL;
  SAVE[3] = id_string.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_CHANNEL);

  ofstream so(path.c_str() , ios::out | ios::binary | ios::trunc );
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  data->writeObject(so);
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.flush();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.close();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
}


TIDNotif::EventChannelImpl* FILEPersistenceDB::load_c(TIDNotif::EventChannelImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->get_channelID();
  string id_string = id.str().data();
  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_CHANNEL);
  ifstream si(path.c_str() , ios::in | ios::binary );
  data->readObject(si);

  return data;
}


//ArrayList load_channels();


//
// SupplierAdmin Methods
//
//
void FILEPersistenceDB::delete_data(TIDNotif::SupplierAdminImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getAdminId();
  string id_string = id.str().data();
  SAVE[1] = NULL;
  SAVE[3] = id_string.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_SUPPLIER_ADMIN);
  remove( path.c_str() );
}

bool FILEPersistenceDB::data_saved(TIDNotif::SupplierAdminImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getAdminId();
  string id_string = id.str().data();
  string the_file = makeFilename(id_string,
                                 TIDNotif::PersistenceDB::OBJ_SUPPLIER_ADMIN);
  ifstream is(the_file.c_str(),ios::in|ios::binary);
  if (is.good())
    {
      is.close();
      return true;
    }
  else
    {
      return false;
    }
      
}

void FILEPersistenceDB::update_data(int what, TIDNotif::SupplierAdminImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getAdminId();
  string id_string = id.str().data();
  SAVE[1] = NULL;
  SAVE[3] = id_string.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_SUPPLIER_ADMIN);

  ofstream so(path.c_str() , ios::out | ios::binary | ios::trunc );
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  data->writeObject(so);
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.flush();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.close();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
}


TIDNotif::SupplierAdminImpl* FILEPersistenceDB::load_sa(TIDNotif::SupplierAdminImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getAdminId();
  string id_string = id.str().data();
  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_SUPPLIER_ADMIN);
  ifstream si(path.c_str() , ios::in | ios::binary );
  data->readObject(si);
  
  return data;
}


//
// ConsumerAdmin Methods
//
//
void FILEPersistenceDB::delete_data(TIDNotif::ConsumerAdminImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getAdminId();
  string id_string = id.str().data();
  SAVE[1] = NULL;
  SAVE[3] = id_string.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_CONSUMER_ADMIN);
  remove( path.c_str() );
}

bool FILEPersistenceDB::data_saved(TIDNotif::ConsumerAdminImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getAdminId();
  string id_string = id.str().data();

  string the_file = makeFilename(id_string,
                                 TIDNotif::PersistenceDB::OBJ_CONSUMER_ADMIN);
  ifstream is(the_file.c_str(),ios::in|ios::binary);
  if (is.good())
    {
      is.close();
      return true;
    }
  else
    {
      return false;
    }
}


void FILEPersistenceDB::update_data(int what, TIDNotif::ConsumerAdminImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getAdminId();
  string id_string = id.str().data();
  SAVE[1] = NULL;
  SAVE[3] = id_string.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_CONSUMER_ADMIN);

  ofstream so(path.c_str() , ios::out | ios::binary | ios::trunc );
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  data->writeObject(so);
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.flush();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.close();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
}


TIDNotif::ConsumerAdminImpl* FILEPersistenceDB::load_ca(TIDNotif::ConsumerAdminImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getAdminId();
  string id_string = id.str().data();
  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_CONSUMER_ADMIN);

  ifstream si(path.c_str() , ios::in | ios::binary );
  data->readObject(si);

  return data;
}



//
// ProxyPushConsumer Methods
//
//
void FILEPersistenceDB::delete_data(TIDNotif::ProxyPushConsumerImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getProxyID();
  string id_string = id.str().data();
  SAVE[1] = NULL;
  SAVE[3] = id_string.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_PROXY_PUSH_CONSUMER);
  remove( path.c_str() );
}

bool FILEPersistenceDB::data_saved(TIDNotif::ProxyPushConsumerImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getProxyID();
  string id_string = id.str().data();

  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string the_file = makeFilename(id_string,
                                 TIDNotif::PersistenceDB::OBJ_PROXY_PUSH_CONSUMER);
  ifstream is(the_file.c_str(),ios::in|ios::binary);
  if (is.good())
    {
      is.close();
      return true;
    }
  else
    {
      return false;
    }
}


void FILEPersistenceDB::update_data(int what, TIDNotif::ProxyPushConsumerImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getProxyID();
  string id_string = id.str().data();
  SAVE[1] = NULL;
  SAVE[3] = id_string.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_PROXY_PUSH_CONSUMER);

  ofstream so(path.c_str() , ios::out | ios::binary | ios::trunc );
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  data->writeObject(so);
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.flush();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.close();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
}


TIDNotif::ProxyPushConsumerImpl* 
FILEPersistenceDB::load_ppushc(TIDNotif::ProxyPushConsumerImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getProxyID();
  string id_string = id.str().data();
  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_PROXY_PUSH_CONSUMER);
  ifstream si(path.c_str() , ios::in | ios::binary );
  data->readObject(si);

  return data;
}


// //
// // ProxyPullConsumer Methods
// //
// //
// void FILEPersistenceDB::delete_data(TIDNotif::ProxyPullConsumerData* data)
// {
//   throw new CORBA::NO_IMPLEMENT("No implemented");
// }

// bool FILEPersistenceDB::data_saved(TIDNotif::ProxyPullConsumerData* data)
// {
//   throw new CORBA::NO_IMPLEMENT("No implemented");
// }


// void FILEPersistenceDB::update_data(int what, TIDNotif::ProxyPullConsumerData* data)
// {
//   throw new CORBA::NO_IMPLEMENT("No implemented");
// }


// TIDNotif::ProxyPullConsumerData* FILEPersistenceDB::load_ppullc(TIDNotif::ProxyPullConsumerData* data)
// {
//   throw new CORBA::NO_IMPLEMENT("No implemented");
// }

//
// ProxyPushSupplier Methods
//
//
void FILEPersistenceDB::delete_data(TIDNotif::ProxyPushSupplierImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getProxyID();
  string id_string = id.str().data();
  SAVE[1] = NULL;
  SAVE[3] = id_string.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_PROXY_PUSH_SUPPLIER);
  remove( path.c_str() );
}


bool FILEPersistenceDB::data_saved(TIDNotif::ProxyPushSupplierImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getProxyID();
  string id_string = id.str().data();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string the_file = makeFilename(id_string,
                                 TIDNotif::PersistenceDB::OBJ_PROXY_PUSH_SUPPLIER);
  ifstream is(the_file.c_str(),ios::in|ios::binary);
  if (is.good())
    {
      is.close();
      return true;
    }
  else
    {
      return false;
    }
}

void FILEPersistenceDB::update_data(int what, TIDNotif::ProxyPushSupplierImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getProxyID();
  string id_string = id.str().data();
  SAVE[1] = NULL;
  SAVE[3] = id_string.c_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_PROXY_PUSH_SUPPLIER);

  ofstream so(path.c_str() , ios::out | ios::binary | ios::trunc );
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  data->writeObject(so);
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.flush();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.close();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
}

TIDNotif::ProxyPushSupplierImpl* 
FILEPersistenceDB::load_ppushs(TIDNotif::ProxyPushSupplierImpl* data)
{
  TIDorb::util::StringBuffer id;
  id << data->getProxyID();
  string id_string = id.str().data();
  string path = makeFilename(id_string,
                             TIDNotif::PersistenceDB::OBJ_PROXY_PUSH_SUPPLIER);

  ifstream si(path.c_str() , ios::in | ios::binary );
  data->readObject(si);

  return data;
}

// //
// // ProxyPullSupplier Methods
// //
// //
// void FILEPersistenceDB::delete_data(TIDNotif::ProxyPullSupplierData* data)
// {
//   throw new CORBA::NO_IMPLEMENT("No implemented");
// }

// bool FILEPersistenceDB::data_saved(TIDNotif::ProxyPullSupplierData* data)
// {
//   throw new CORBA::NO_IMPLEMENT("No implemented");
// }


// void FILEPersistenceDB::update_data(int what, TIDNotif::ProxyPullSupplierData* data)
// {
//   throw new CORBA::NO_IMPLEMENT("No implemented");
// }


// TIDNotif::ProxyPullSupplierData* FILEPersistenceDB::load_ppulls(TIDNotif::ProxyPullSupplierData* data)
// {
//   throw new CORBA::NO_IMPLEMENT("No implemented");
// }



//
// Discriminator Methods
//
//
void FILEPersistenceDB::delete_data(TIDNotif::FilterData* data)
{
  //DELETE[1] = data.name;

  //DELETE[1] = data.name;
  DELETE[3] = data->id_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, DELETE); //TODO_MORFEO: Trace
  if( remove( makeFilename(data->id,TIDNotif::PersistenceDB::OBJ_DISCRIMINATOR).c_str() ) == -1 )
    {
      /*TIDNotifTrace.print(TIDNotifTrace.USER, " *** ERROR delete NotificationChannelData ***");
        TIDNotifTrace.print( TIDNotifTrace.USER, " ### FILE: "+makeFilename(data.id,OBJ_CHANNEL));*/ //TODO_MORFEO: Trace
    }

}

void FILEPersistenceDB::save_data(TIDNotif::FilterData* data)
{
  SAVE[1] = NULL;
  SAVE[3] = data->id_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, SAVE); //TODO_MORFEO: Trace
  string path = makeFilename(data->id,
                             TIDNotif::PersistenceDB::OBJ_DISCRIMINATOR);

  ofstream so(path.c_str() , ios::out | ios::binary | ios::trunc );
  if (!so) //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
    data->writeObject(so);
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.flush();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.close();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace


}

void FILEPersistenceDB::update_data(int what, TIDNotif::FilterData* data)
{

  SAVE[1] = NULL;
  SAVE[3] = data->id_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string path = makeFilename(data->id,
                             TIDNotif::PersistenceDB::OBJ_DISCRIMINATOR);

  ofstream so(path.c_str() , ios::out | ios::binary | ios::trunc );
      
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  data->writeObject(so);
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.flush();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.close();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
}

TIDNotif::FilterData* FILEPersistenceDB::load_d(string name)
{

  LOAD[1] = name.c_str();
  //TIDNotifTrace.print( TIDNotifTrace.USER, LOAD ); //TODO_MORFEO: Trace
  ifstream si(name.c_str(),ios::in|ios::binary);

  string id;
  si>>id;
  CORBA::ORB_var orb = PersistenceManager::_orb;
  PortableServer::POA_ptr the_poa;
  the_poa = ThePOAFactory::getGlobalPOA("GlobalFilterPOA");

  if (the_poa == NULL)
    {
      the_poa = ThePOAFactory::createGlobalPOA("GlobalFilterPOA",
                                               ThePOAFactory::GLOBAL_FILTER_POA, NULL );
      try
        {
          the_poa->get_servant();
        }
      catch (PortableServer::POA::NoServant& ex)
        {  //TODO_MORFEO: POAPackage -> POA
          try
            {
              the_poa->set_servant(new TIDNotif::FilterImpl(orb));
            }
          catch (CORBA::Exception& e)
            {
              //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace.
            }
        }
      catch (PortableServer::POA::WrongPolicy& ex)
        {
          //TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace.
        }
    }
  TIDNotif::FilterData* data = new TIDNotif::FilterData(id.c_str(),the_poa);


  if (!si) throw IOException();
  data->readObject(si);
  if (!si) throw IOException();
  si.close();
  if (!si) throw IOException();
  //TIDNotifTrace.print(TIDNotifTrace.ERROR, PERSISTENCE_ERROR); //TODO_MORFEO: Trace
  return data;
}

void
FILEPersistenceDB::load_filter(string name,
                               TIDNotif::FilterAdminImpl* filterAdmin)
{
  //TODO_MORFEO: if more grammars are implemented then the identification of
  //grammar must be persistent too 
  string path = makeFilename(name,
                             TIDNotif::PersistenceDB::OBJ_DISCRIMINATOR);
  ifstream is(path.c_str(),ios::in|ios::binary);

  filterAdmin->readObject(is);
  is.close();
     
}
//
// IndexLocator Methods
//
//
/*void delete(IndexLocatorData* data);

void save(IndexLocatorData* data);


void update(int what, IndexLocatorData* data);

IndexLocatorData* load_l(string name);*/


//
// MappingDiscriminator Methods
//
//
void FILEPersistenceDB::delete_data(TIDNotif::MappingFilterData* data)
{
  //DELETE[1] = data.name;

  //DELETE[1] = data.name;
  DELETE[3] = data->id_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, DELETE); //TODO_MORFEO: Trace
  if( remove( makeFilename(data->id,TIDNotif::PersistenceDB::OBJ_MAPPING_DISCRIMINATOR).c_str() ) == -1 )
    {
      /*TIDNotifTrace.print(TIDNotifTrace.USER, " *** ERROR delete NotificationChannelData ***");
        TIDNotifTrace.print( TIDNotifTrace.USER, " ### FILE: "+makeFilename(data.id,OBJ_CHANNEL));*/ //TODO_MORFEO: Trace
    }
}

void FILEPersistenceDB::save_data(TIDNotif::MappingFilterData* data)
{
  SAVE[1] = NULL;
  SAVE[3] = data->id_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, SAVE); //TODO_MORFEO: Trace
  string path = makeFilename(data->id,
                             TIDNotif::PersistenceDB::OBJ_MAPPING_DISCRIMINATOR);
  ofstream so(path.c_str() , ios::out | ios::binary );
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  data->writeObject(so); //TODO_MORFEO: 
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.flush();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.close();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
}


void FILEPersistenceDB::update_data(int what, TIDNotif::MappingFilterData* data)
{
  SAVE[1] = NULL;
  SAVE[3] = data->id_str();
  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string file_name(data->id,TIDNotif::PersistenceDB::OBJ_MAPPING_DISCRIMINATOR);
  ofstream so(file_name.c_str() , ios::out | ios::binary | ios::trunc );
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  data->writeObject(so);
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.flush();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.close();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
}


TIDNotif::MappingFilterData* FILEPersistenceDB::load_md(string name)
{
  TimeBase::TimeT lifetime;
  CORBA::Short priority;
  LOAD[1] = name.c_str();
  //TIDNotifTrace.print( TIDNotifTrace.USER, LOAD ); //TODO_MORFEO: Trace



  ifstream is(name.c_str(),ios::in|ios::binary);


  string id;
  if (!is) throw IOException();
  is>>id;
  CORBA::Any default_value;
  int k;
  is>>k;
  switch (k)
    {
    case CORBA::tk_short:
      is>>priority;
      (default_value) <<= (priority);
      break;

    case CORBA::tk_ulonglong:
      is>>lifetime;
      (default_value) <<= (lifetime);

      break;

    default:
      throw CORBA::INTERNAL();
    }

  TIDNotif::MappingFilterData* data=new TIDNotif::MappingFilterData(id.c_str(),default_value);



  if (!is) throw IOException();
  data->readObject(is);
  if (!is) throw IOException();
  is.close();
  if (!is) throw IOException();
  //TIDNotifTrace.print(TIDNotifTrace.ERROR, PERSISTENCE_ERROR); //TODO_MORFEO: Trace
  return data;
}




//
// Internal Methods
//
//


//
// UID generator
//
string FILEPersistenceDB::getUID()
{
  return _uid_factory->getUID();
}


void FILEPersistenceDB::update_data(int what, EventChannelFactoryImpl* data){
  string file_name = makeFilename(FILE_CHANNEL_FACTORY,
                                  TIDNotif::PersistenceDB::OBJ_CHANNEL_FACTORY);
  string id;
  ifstream si(file_name.c_str(),ios::in|ios::binary);

  si>>id;
  si.close();

  ofstream so(file_name.c_str() , ios::out | ios::binary | ios::trunc );
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so<<id <<endl;
  data->writeObject(so);
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.flush();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.close();

}
void FILEPersistenceDB::delete_data(){
  string file_name = makeFilename(FILE_CHANNEL_FACTORY,
                                  TIDNotif::PersistenceDB::OBJ_CHANNEL_FACTORY);
  if( remove( file_name.c_str() ) == -1 )
    {
      /*TIDNotifTrace.print(TIDNotifTrace.USER, " *** ERROR delete NotificationChannelData ***");
        TIDNotifTrace.print( TIDNotifTrace.USER, " ### FILE: "+makeFilename(data.id,OBJ_CHANNEL));*/ //TODO_MORFEO: Trace
    }
}

void FILEPersistenceDB::load_c_f(EventChannelFactoryImpl* data){
  string file_name = makeFilename(FILE_CHANNEL_FACTORY,
                                  TIDNotif::PersistenceDB::OBJ_CHANNEL_FACTORY);
  ifstream si(file_name.c_str() , ios::in | ios::binary );
  if (si.good())
    {
      string id;
      si>>id;
      data->readObject(si);
      si.close();
    }
  else
    throw IOException("Error Path" );

}
void FILEPersistenceDB::save_channel_factory(string id){

  //TIDNotifTrace.print(TIDNotifTrace.USER, UPDATE); //TODO_MORFEO: Trace

  string file_name = makeFilename(FILE_CHANNEL_FACTORY,
                                  TIDNotif::PersistenceDB::OBJ_CHANNEL_FACTORY);

  ofstream so(file_name.c_str() , ios::out | ios::binary | ios::trunc );
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so<<id<<endl;
  so<<0<<endl;
  so<<0<<endl;
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.flush();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace
  so.close();
  //if (!so) TIDNotifTrace.printStackTrace(TIDNotifTrace.ERROR, ex); //TODO_MORFEO: Trace 
}

string FILEPersistenceDB::recover_channel_factory(){
  string file_name = makeFilename(FILE_CHANNEL_FACTORY,
                                  TIDNotif::PersistenceDB::OBJ_CHANNEL_FACTORY);
  ifstream si(file_name.c_str(),ios::in|ios::binary);

  string id;
  si>>id;
  si.close();
  return id;
}

bool FILEPersistenceDB::channel_factory_saved(){
  string the_file = makeFilename(FILE_CHANNEL_FACTORY,
                                 TIDNotif::PersistenceDB::OBJ_CHANNEL_FACTORY);
  ifstream is(the_file.c_str(),ios::in|ios::binary);
  if (is.good())
    {
      is.close();
      return true;
    }
  else
    {
      return false;
    }
}
    
string FILEPersistenceDB::getPath()
{
  string the_file;
  the_file.append(util::TIDNotifConfig::get(util::TIDNotifConfig::DATA_PATH_KEY));

  if (!check_path(the_file)) throw IOException("Error Path" );
  the_file.append("/");
  the_file.append(util::TIDNotifConfig::get(util::TIDNotifConfig::DATA_ROOT_KEY));
  if (!check_path(the_file)) throw IOException("Error Path");
  the_file.append("/");
  the_file.append(util::TIDNotifConfig::get(util::TIDNotifConfig::ADMIN_PORT_KEY));
  if (!check_path(the_file)) throw IOException("Error Path");
//   the_file.append(pers_id);
//   if (!check_path(the_file)) throw IOException("Error Path");
  the_file.append("/");
  the_file.append(util::TIDNotifConfig::get(util::TIDNotifConfig::OBJECTS_PATH_KEY));
  if (!check_path(the_file)) throw IOException("Error Path");

  return the_file;
}

void FILEPersistenceDB::mkDirs(string dir)
{
  string path = dir+"/";
  if (!check_path(path+DIR_CHANNEL_FACTORY)) throw IOException();
  if (!check_path(path+DIR_CHANNEL)) throw IOException();
  if (!check_path(path+DIR_SUPPLIER_ADMIN)) throw IOException();
  if (!check_path(path+DIR_PROXY_PUXX_CONSUMER)) throw IOException();
  if (!check_path(path+DIR_CONSUMER_ADMIN)) throw IOException();
  if (!check_path(path+DIR_PROXY_PUXX_SUPPLIER)) throw IOException();
  if (!check_path(path+DIR_DISCRIMINATOR)) throw IOException();
  if (!check_path(path+DIR_INDEXLOCATOR)) throw IOException();
  if (!check_path(path+DIR_TRANSFORMING_OPERATOR)) throw IOException();
  if (!check_path(path+DIR_MAPPING_DISCRIMINATOR)) throw IOException();
}

string FILEPersistenceDB::makeFilename(string name, TIDNotif::PersistenceDB::OBJ type)
{
  string the_file = _base_path;
  the_file.append("/");
  switch (type)
    {
    case TIDNotif::PersistenceDB::OBJ_CHANNEL_FACTORY:
      return the_file.append(DIR_CHANNEL_FACTORY).append("/").append(name);
    case TIDNotif::PersistenceDB::OBJ_CHANNEL:
      return the_file.append(DIR_CHANNEL).append("/").append(name);

    case TIDNotif::PersistenceDB::OBJ_SUPPLIER_ADMIN:
      return the_file.append(DIR_SUPPLIER_ADMIN).append("/").append(name);

    case TIDNotif::PersistenceDB::OBJ_PROXY_PUSH_CONSUMER:
    case TIDNotif::PersistenceDB::OBJ_PROXY_PULL_CONSUMER:
      return the_file.append(DIR_PROXY_PUXX_CONSUMER).append("/").append(name);

    case TIDNotif::PersistenceDB::OBJ_CONSUMER_ADMIN:
      return the_file.append(DIR_CONSUMER_ADMIN).append("/").append(name);

    case TIDNotif::PersistenceDB::OBJ_PROXY_PUSH_SUPPLIER:
    case TIDNotif::PersistenceDB::OBJ_PROXY_PULL_SUPPLIER:
      return the_file.append(DIR_PROXY_PUXX_SUPPLIER).append("/").append(name);

    case TIDNotif::PersistenceDB::OBJ_DISCRIMINATOR:
      return the_file.append(DIR_DISCRIMINATOR).append("/").append(name);

    case TIDNotif::PersistenceDB::OBJ_INDEXLOCATOR:
      return the_file.append(DIR_INDEXLOCATOR).append("/").append(name);

    case TIDNotif::PersistenceDB::OBJ_TRANSFORMING_OPERATOR:
      return the_file.append(DIR_TRANSFORMING_OPERATOR).append("/").append(name);

    case TIDNotif::PersistenceDB::OBJ_MAPPING_DISCRIMINATOR:
      return the_file.append(DIR_MAPPING_DISCRIMINATOR).append("/").append(name);
    }
  return the_file.append(name);
}

bool FILEPersistenceDB::check_path(string pathname)
{
  // Next lines are used to obtain current working directory
  // To avoid too large path problems, buffer is resized when needed.
  char * current_dir;
  int _size = 1024;
  while (true)
  {
    current_dir = new char[_size];
    if (getcwd(current_dir, _size))
      break;

    // Current directory path is too large, 
    // let's resize the buffer and try again
    delete current_dir;
    _size += 1024;
  }

  if (!chdir(pathname.c_str()))
    {
      chdir(current_dir);
      delete current_dir;
      return true;
    }
  else
    {
      delete current_dir;
      return !mkdir (pathname.c_str(),500);
    }
}

TIDNotif::CommonData* FILEPersistenceDB::_load(string name)
{
  throw CORBA::NO_IMPLEMENT("No implemented");

}

void FILEPersistenceDB::_save(string name, CommonData* data)
{
  throw CORBA::NO_IMPLEMENT("No implemented");
}





}//namespace file
}//namespace TIDNotif
