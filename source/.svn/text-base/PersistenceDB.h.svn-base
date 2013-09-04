// -*- c++ -*-
/*
 *  File name: PersistenceDB.h
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

#ifndef _TIDNOTIF_PERSISTENCEDB_H_
#define _TIDNOTIF_PERSISTENCEDB_H_ 

#include <stdlib.h>
#include "FilterData.h"
#include "MappingFilterData.h"
#include "ConsumerAdminImpl.h"
#include "EventChannelImpl.h"
#include "ProxyPushConsumerImpl.h"
#include "ProxyPushSupplierImpl.h"
#include "SupplierAdminImpl.h"
#include "EventChannelFactoryImpl.h"
#include "CosNotifyFilter.h"
#include "qos/qos.h"


namespace TIDNotif {
	
class PersistenceDB 
{
  
public:
  
  //
  // Common
  static const int STATE;
  
  //
  // Input
    enum OBJ {
      OBJ_CHANNEL_FACTORY       =0,
      OBJ_CHANNEL	        =1,
      OBJ_SUPPLIER_ADMIN	=2,
      OBJ_PROXY_PUSH_CONSUMER	=3,
      OBJ_PROXY_PULL_CONSUMER	=4,
      OBJ_CONSUMER_ADMIN	=5,
      OBJ_PROXY_PUSH_SUPPLIER	=6,
      OBJ_PROXY_PULL_SUPPLIER	=7,
      OBJ_DISCRIMINATOR		=8,
      OBJ_INDEXLOCATOR		=9,
      OBJ_TRANSFORMING_OPERATOR	=10,
      OBJ_MAPPING_DISCRIMINATOR	=11
    };

    enum ATTR {
      ATTR_ADMINISTRATIVE_STATE=0,
      ATTR_DISCRIMINATOR=1,
      ATTR_INDEXLOCATOR=2,
      ATTR_MAPPING_DISCRIMINATOR=3,
      ATTR_D_ERROR_HANDLER=4,
      ATTR_ORDER=5,
      ATTR_ORDER_GAP=6,
      ATTR_TRANSFORMING_OPERATOR=7,
      ATTR_T_ERROR_HANDLER=8,
      ATTR_SUPPLIER_ADMIN=9,
      ATTR_SUPPLIER_ADMIN_PARENT=10,
      ATTR_SUPPLIER_ADMIN_CHILD=11,
      ATTR_PROXY_PUSH_CONSUMER=12,
      ATTR_PROXY_PULL_CONSUMER=13,
      ATTR_CONSUMER_ADMIN=14,
      ATTR_CONSUMER_ADMIN_PARENT=15,
      ATTR_PROXY_PUSH_SUPPLIER=16,
      ATTR_PROXY_PULL_SUPPLIER=17,
      ATTR_EXTENDED_CRITERIA=18,
      ATTR_PUSH_SUPPLIER=19,
      ATTR_PULL_SUPPLIER=20,
      ATTR_PUSH_CONSUMER=21,
      ATTR_PULL_CONSUMER=22,
      ATTR_SUPPLIER_ADMIN_TABLES=23,
      ATTR_PUSH_CONSUMER_TABLE=24,
      ATTR_PULL_CONSUMER_TABLE=25,
      ATTR_CONSUMER_ADMIN_TABLES=26,
      ATTR_PUSH_SUPPLIER_TABLE=27,
      ATTR_PULL_SUPPLIER_TABLE=28,
      ATTR_CONSTRAINTS=29,
      ATTR_TRANSFORMING_RULES=30,
      ATTR_DEFAULT_PRIORITY=31,
      ATTR_DEFAULT_LIFETIME=32,
      ATTR_LEVEL=33,
      ATTR_CHANNEL_FACTORY=34
    };

  // type
  enum MODE_EVENT {
    PUSH=0,
    PULL=1
  };
 

  //
  // Operations
  //
  virtual bool data_saved(ChannelID id)=0;
  virtual void update_data(int what, EventChannelImpl* data)=0;
  virtual void delete_data(EventChannelImpl* data)=0;
  virtual EventChannelImpl* load_c(EventChannelImpl* data)=0;
  //virtual java.util.ArrayList load_channels();

  virtual bool data_saved(SupplierAdminImpl* data)=0;
  virtual void update_data(int what, SupplierAdminImpl* data)=0;
  virtual void delete_data(SupplierAdminImpl* data)=0;
  virtual SupplierAdminImpl* load_sa(SupplierAdminImpl* data)=0;

  virtual bool data_saved(ConsumerAdminImpl* data)=0;
  virtual void update_data(int what, ConsumerAdminImpl* data)=0;
  virtual void delete_data(ConsumerAdminImpl* data)=0;
  virtual ConsumerAdminImpl* load_ca(ConsumerAdminImpl* data)=0;

  virtual bool data_saved(ProxyPushConsumerImpl* data)=0;
  virtual void update_data(int what, ProxyPushConsumerImpl* data)=0;
  virtual void delete_data(ProxyPushConsumerImpl* data)=0;
  virtual ProxyPushConsumerImpl* load_ppushc(ProxyPushConsumerImpl* dat)=0;

  virtual bool data_saved(ProxyPushSupplierImpl* data)=0;
  virtual void update_data(int what, ProxyPushSupplierImpl* data)=0;
  virtual void delete_data(ProxyPushSupplierImpl* data)=0;
  virtual ProxyPushSupplierImpl* load_ppushs(ProxyPushSupplierImpl* data)=0;

//   virtual bool data_saved(ProxyPullConsumerData* data)=0;
//   virtual void update_data(int what, ProxyPullConsumerData* data)=0;
//   virtual void delete_data(ProxyPullConsumerData* data)=0;
//   virtual ProxyPullConsumerData* load_ppullc(ProxyPullConsumerData* data)=0;

//   virtual bool data_saved(ProxyPullSupplierData* data)=0;
//   virtual void update_data(int what, ProxyPullSupplierData* data)=0;
//   virtual void delete_data(ProxyPullSupplierData* data)=0;
//   virtual ProxyPullSupplierData* load_ppulls(ProxyPullSupplierData* data)=0;

  virtual void save_data(FilterData* data)=0;
  virtual void update_data(int what, FilterData* data)=0;	 
  virtual void delete_data(FilterData* data)=0;         
  virtual FilterData* load_d(string name)=0;

  virtual void load_filter(string name,FilterAdminImpl *)=0;

  /*void save(IndexLocatorData data);
    void update(int what, IndexLocatorData data);
    void delete(IndexLocatorData data);
    IndexLocatorData load_l(String name) throws java.lang.Exception;
  */
  virtual void save_data(MappingFilterData* data)=0;
  virtual void update_data(int what, MappingFilterData* data)=0;
  virtual void delete_data(MappingFilterData* data)=0;
  virtual MappingFilterData* load_md(string name)=0;

  /*
    void save(TransformingOperatorData data);
    void update(int what, TransformingOperatorData data);
    void delete(TransformingOperatorData data);
    TransformingOperatorData load_to(String name) throws java.lang.Exception;*/

  virtual void update_data(int what, EventChannelFactoryImpl* data)=0;
  virtual void delete_data()=0;
  virtual void load_c_f(EventChannelFactoryImpl* data)=0;
  virtual void save_channel_factory(string id)=0;
  virtual string recover_channel_factory()=0;
  virtual bool channel_factory_saved()=0;
 
  virtual string getUID() = 0;

  virtual ~PersistenceDB() {}
};
	
	 
};//namespace TIDNotif
#endif
