#
#  File name: Makefile.am
#  File type: makefile file.
#

#
# Copyright (C) 2006 Telefonica I+D S.A.
#
# This source file is a property of Telefonica I+D. You can not
# use it for any purpose unless you have an explicit authorization
# by owner.
#

SUBDIRS = idl util file qos . 

AM_CPPFLAGS = 				\
	-I$(srcdir)/idl/		\
	-I$(srcdir)/util/ 		\
	-I$(srcdir)/util/parser 	\
	-I$(srcdir)/file/ 		\
	-I$(srcdir)/qos/ 		\
	@TIDORBC_LIBS@

lib_LTLIBRARIES = libTIDNotifC.la

libTIDNotifC_la_SOURCES =		\
	TIDNotif.h			\
	ThePOAFactory.h			\
	ThePOAFactory.C			\
	PersistenceManager.h		\
	PersistenceManager.C		\
	PersistenceDB.h			\
	PersistenceDB.C			\
	NotifReference.h		\
	NotifReference.C		\
	MappingFilterImpl.h		\
	MappingFilterImpl.C		\
	MappingFilterData.h		\
	MappingFilterData.C		\
	FilterFactoryImpl.h		\
	FilterFactoryImpl.C		\
	FilterData.h			\
	FilterData.C			\
	FilterAdminImpl.h		\
	FilterAdminImpl.C		\
	CommonData.h			\
	CommonData.C			\
	FilterImpl.h			\
	FilterImpl.C			\
	SupplierAdminImpl.h		\
	SupplierAdminImpl.C		\
	SupplierAdminData.h		\
	SupplierAdminData.C		\
	ProxyPushSupplierImpl.h		\
	ProxyPushSupplierImpl.C		\
	ProxyPushSupplierData.h		\
	ProxyPushSupplierData.C		\
	ProxyPushConsumerImpl.h		\
	ProxyPushConsumerImpl.C		\
	ProxyPushConsumerData.h		\
	ProxyPushConsumerData.C		\
	EventChannelImpl.h		\
	EventChannelImpl.C		\
	EventChannelData.h		\
	EventChannelData.C		\
	EventChannelFactoryImpl.h	\
	EventChannelFactoryImpl.C	\
	ConsumerAdminImpl.h		\
	ConsumerAdminImpl.C  		\
	ConsumerAdminData.h		\
	ConsumerAdminData.C  		\
	ServiceAdminImpl.h 		\
	ServiceAdminImpl.C 		\
	NotificationService.h 		\
	NotificationService.C 		\
	AlreadyInitialized.h 		\
	AlreadyInitialized.C 		\
	NotInitialized.h 		\
	NotInitialized.C 		


libTIDNotifC_la_LIBADD =		\
	util/libutil.la			\
	util/parser/libparser.la	\
	file/libfile.la			\
	qos/libqos.la

libTIDNotifC_la_LDFLAGS = \
        -release $(VERSION)

tidnotifdir = $(bindir)
tidnotif_PROGRAMS = tidnotif

tidnotif_SOURCES = tidnotif.C

tidnotif_LDADD = $(srcdir)/libTIDNotifC.la \
	$(srcdir)/idl/libTIDNotifCIdl.la \
	@TIDORBC_LDFLAGS@ @TIDORBC_LIBS@

notifddir = $(bindir)
notifd_PROGRAMS = notifd

dist_bin_SCRIPTS = start_notif.sh start_notif_ssl.sh

notifd_SOURCES = notifd.C TIDNotif.h

notifd_LDADD = $(srcdir)/libTIDNotifC.la \
	$(srcdir)/idl/libTIDNotifCIdl.la \
	@TIDORBC_LDFLAGS@ @TIDORBC_LIBS@

