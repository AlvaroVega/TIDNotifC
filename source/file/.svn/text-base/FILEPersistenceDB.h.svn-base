/*
 *  File name: FILEPersistenceDB.h
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

#ifndef _TIDNOTIF_FILEPERSISTENCEDB_H_
#define _TIDNOTIF_FILEPERSISTENCEDB_H_

#include "PersistenceDB.h"
#include "EventChannelImpl.h"
#include "SupplierAdminImpl.h"
#include "ConsumerAdminImpl.h"
#include "ProxyPushConsumerImpl.h"
#include "ProxyPushSupplierImpl.h"
#include "FilterData.h"
#include "MappingFilterData.h"
#include "CommonData.h"
#include "FileUID.h"

namespace TIDNotif {
namespace file {

class FILEPersistenceDB : public virtual TIDNotif::PersistenceDB
{
private:
  // Directorios
  static const char * DIR_CHANNEL_FACTORY;
  static const char * DIR_CHANNEL;
  static const char * DIR_SUPPLIER_ADMIN;
  static const char * DIR_PROXY_PUXX_CONSUMER;
  static const char * DIR_CONSUMER_ADMIN;
  static const char * DIR_PROXY_PUXX_SUPPLIER;
  static const char * DIR_DISCRIMINATOR;
  static const char * DIR_INDEXLOCATOR;
  static const char * DIR_TRANSFORMING_OPERATOR;
  static const char * DIR_MAPPING_DISCRIMINATOR;
      
  // Fichero UID
  static const char * FILE_UID_DATA;
  static const char * FILE_CHANNEL_FACTORY;

  // Miembros
  string _pers_id;
  string _base_path;
  FileUID* _uid_factory;


  static const char* SAVE[5];
  static const char* UPDATE[5];
  static const char* DELETE[5];
  static const char* LOAD[3];
  static const char* PERSISTENCE_ERROR;


  //
  // - Añadir un elemento
  // - Actualizar un elemento
  // - Eliminar un elemento
  // - Eliminar todos los elementos
  // - Obtener una lista de elementos
  //


public:

  FILEPersistenceDB( string id );

  virtual ~FILEPersistenceDB(){}

  //
  // Channel Methods
  //
  //
  void delete_data(TIDNotif::EventChannelImpl* data);
  bool data_saved(ChannelID id);
  void update_data(int what, TIDNotif::EventChannelImpl* data);
  TIDNotif::EventChannelImpl* load_c(TIDNotif::EventChannelImpl* data);


  //ArrayList load_channels();


  //
  // SupplierAdmin Methods
  //
  //
  void delete_data(TIDNotif::SupplierAdminImpl* data);
  bool data_saved(TIDNotif::SupplierAdminImpl* data);
  void update_data(int what, TIDNotif::SupplierAdminImpl* data);
  TIDNotif::SupplierAdminImpl* load_sa(TIDNotif::SupplierAdminImpl* data);


  //
  // ConsumerAdmin Methods
  //
  //
  void delete_data(TIDNotif::ConsumerAdminImpl* data);
  bool data_saved(TIDNotif::ConsumerAdminImpl* data);
  void update_data(int what, TIDNotif::ConsumerAdminImpl* data);
  TIDNotif::ConsumerAdminImpl* load_ca(TIDNotif::ConsumerAdminImpl* data);



  //
  // ProxyPushConsumer Methods
  //
  //
  void delete_data(TIDNotif::ProxyPushConsumerImpl* data);
  bool data_saved(TIDNotif::ProxyPushConsumerImpl* data);
  void update_data(int what, TIDNotif::ProxyPushConsumerImpl* data);
  TIDNotif::ProxyPushConsumerImpl* load_ppushc(TIDNotif::ProxyPushConsumerImpl* data);


//   //
//   // ProxyPullConsumer Methods
//   //
//   //
//   void delete_data(TIDNotif::ProxyPullConsumerData* data);
//   bool data_saved(TIDNotif::ProxyPullConsumerData* data);
//   void update_data(int what, TIDNotif::ProxyPullConsumerData* data);
//   TIDNotif::ProxyPullConsumerData* load_ppullc(TIDNotif::ProxyPullConsumerData* data);

  //
  // ProxyPushSupplier Methods
  //
  //
  void delete_data(TIDNotif::ProxyPushSupplierImpl* data);
  bool data_saved(TIDNotif::ProxyPushSupplierImpl* data);
  void update_data(int what, TIDNotif::ProxyPushSupplierImpl* data);
  TIDNotif::ProxyPushSupplierImpl* load_ppushs(TIDNotif::ProxyPushSupplierImpl* data);

//   //
//   // ProxyPullSupplier Methods
//   //
//   //
//   void delete_data(TIDNotif::ProxyPullSupplierData* data);
//   bool data_saved(TIDNotif::ProxyPullSupplierData* data);
//   void update_data(int what, TIDNotif::ProxyPullSupplierData* data);
//   TIDNotif::ProxyPullSupplierData* load_ppulls(TIDNotif::ProxyPullSupplierData* data);


  //
  // Discriminator Methods
  //
  //
  void delete_data(TIDNotif::FilterData* data);
  void save_data(TIDNotif::FilterData* data);
  void update_data(int what, TIDNotif::FilterData* data);
  TIDNotif::FilterData* load_d(string name);
  void load_filter(string name, TIDNotif::FilterAdminImpl*);


//   //
//   // IndexLocator Methods
//   //
//   //
//   void delete(IndexLocatorData* data);
//   void save(IndexLocatorData* data);
//   void update(int what, IndexLocatorData* data);
//   IndexLocatorData* load_l(string name);


  //
  // MappingDiscriminator Methods
  //
  //
  void delete_data(TIDNotif::MappingFilterData* data);
  void save_data(TIDNotif::MappingFilterData* data);
  void update_data(int what, TIDNotif::MappingFilterData* data);
  TIDNotif::MappingFilterData* load_md(string name);

  //
  // Internal Methods
  //
  //
      

  //
  // UID generator
  //
  string getUID();

  //
  // ChannelFactory Methods
  //
  //
  void update_data(int what, EventChannelFactoryImpl* data);
  void delete_data();
  void load_c_f(EventChannelFactoryImpl* data);

  void save_channel_factory(string id);
  string recover_channel_factory();
  bool channel_factory_saved();

private:
  string getPath();

  void mkDirs(string dir);

  string makeFilename(string name, TIDNotif::PersistenceDB::OBJ  type);

  bool check_path(string pathname);

  TIDNotif::CommonData* _load(string name);

  void _save(string name, CommonData* data);

};

}//namespace file
}//namespace TIDNotif
#endif
