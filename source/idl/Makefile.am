#
#  File name: idl/Makefile.am
#  File type: makefile file.
#

#
# Copyright (C) 2006 Telefonica I+D S.A.
#
# This source file is a property of Telefonica I+D. You can not
# use it for any purpose unless you have an explicit authorization
# by owner.
#

AM_CPPFLAGS = 				\
	-I$(top_srcdir)/source/	\
	@TIDORBC_LIBS@

CLEANFILES = *.C *.h

lib_LTLIBRARIES = libTIDNotifCIdl.la

libTIDNotifCIdl_la_LDFLAGS = \
        -release $(VERSION)

idl_sources = \
	CosNotification.idl \
	CosEventComm.idl \
	CosNotifyComm.idl \
	CosNotifyFilter.idl \
	CosEventChannelAdmin.idl \
	CosNotifyChannelAdmin.idl \
	CosTypedEventComm.idl \
	CosTypedEventChannelAdmin.idl \
	CosTypedNotifyComm.idl \
	CosTypedNotifyChannelAdmin.idl

idl_internal_sources = \
	NotificationInternals.idl \
	ServiceManager.idl

cpp_headers = \
	CosNotification.h \
	CosEventComm.h \
	CosNotifyComm.h \
	CosNotifyFilter.h \
	CosEventChannelAdmin.h \
	CosNotifyChannelAdmin.h \
	CosTypedEventComm.h \
	CosTypedEventChannelAdmin.h \
	CosTypedNotifyComm.h \
	CosTypedNotifyChannelAdmin.h

cpp_internal_headers = \
	NotificationInternals.h \
	ServiceManager.h

cpp_sources = \
	CosNotification.C \
	CosEventComm.C \
	CosNotifyComm.C \
	CosNotifyFilter.C \
	CosEventChannelAdmin.C \
	CosNotifyChannelAdmin.C \
	CosTypedEventComm.C \
	CosTypedEventChannelAdmin.C \
	CosTypedNotifyComm.C \
	CosTypedNotifyChannelAdmin.C

cpp_internal_sources = \
	NotificationInternals.C \
	ServiceManager.C

poa_cpp_headers = \
	POA_CosNotification.h \
	POA_CosEventComm.h \
	POA_CosNotifyComm.h \
	POA_CosNotifyFilter.h \
	POA_CosEventChannelAdmin.h \
	POA_CosNotifyChannelAdmin.h \
	POA_CosTypedEventComm.h \
	POA_CosTypedEventChannelAdmin.h \
	POA_CosTypedNotifyComm.h \
	POA_CosTypedNotifyChannelAdmin.h

poa_cpp_internal_headers = \
	POA_NotificationInternals.h \
	POA_ServiceManager.h

poa_cpp_sources = \
	POA_CosNotification.C \
	POA_CosEventComm.C \
	POA_CosNotifyComm.C \
	POA_CosNotifyFilter.C \
	POA_CosEventChannelAdmin.C \
	POA_CosNotifyChannelAdmin.C \
	POA_CosTypedEventComm.C \
	POA_CosTypedEventChannelAdmin.C \
	POA_CosTypedNotifyComm.C \
	POA_CosTypedNotifyChannelAdmin.C 

poa_cpp_internal_sources = \
	POA_NotificationInternals.C \
	POA_ServiceManager.C

nodist_libTIDNotifCIdl_la_SOURCES = \
	$(cpp_sources)  \
	$(poa_cpp_sources) \
	$(cpp_internal_sources)  \
	$(poa_cpp_internal_sources) \
	$(cpp_internal_headers) \
	$(poa_cpp_internal_headers)

$(cpp_sources): %.C: %.idl
	${IDLC} -D_PRE_3_0_COMPILER_ $<

$(cpp_internal_sources): %.C: %.idl
	${IDLC} -D_PRE_3_0_COMPILER_ $<

instdir=$(includedir)/TIDNotifC

nodist_inst_HEADERS = \
	$(cpp_headers) \
	$(poa_cpp_headers)

inst_HEADERS = $(idl_sources)
