
AM_CPPFLAGS = \
	-I$(top_srcdir)/source/ \
	-I$(top_srcdir)/source/idl \
	@TIDORBC_LIBS@ -D_TIDORB

ep_idl_dependencies = Event.C POA_Event.C 

CLEANFILES = $(ep_idl_dependencies)

POA_Event.h: POA_Event.C
POA_Event.C: Event.C
Event.h: Event.C

Event.C: Event.idl
	${IDLC} -D_PRE_3_0_COMPILER_ -I$(top_srcdir)/source/idl/ Event.idl

testdir = $(pkgdatadir)/test/event_push/
check_PROGRAMS = server consumer1 consumer2 supplier

nodist_server_SOURCES = $(ep_idl_dependencies)
server_SOURCES    = server.C

nodist_supplier_SOURCES = $(ep_idl_dependencies)
supplier_SOURCES  = supplier.C  MySupplierImpl.h MySupplierImpl.C

nodist_consumer1_SOURCES = $(ep_idl_dependencies)
consumer1_SOURCES = consumer1.C MyConsumerImpl.h MyConsumerImpl.C

nodist_consumer2_SOURCES = $(ep_idl_dependencies)
consumer2_SOURCES = consumer2.C MyConsumerImpl.h MyConsumerImpl.C

noinst_HEADERS = Event.idl

std_ldadd = \
	$(top_srcdir)/source/libTIDNotifC.la \
	$(top_srcdir)/source/idl/libTIDNotifCIdl.la \
	@TIDORBC_LDFLAGS@ \
	@TIDORBC_LIBS@

server_LDADD = $(std_ldadd)

supplier_LDADD = $(std_ldadd)

consumer1_LDADD = $(std_ldadd)

consumer2_LDADD = $(std_ldadd)

#TESTS = server supplier consumer1 consumer2
