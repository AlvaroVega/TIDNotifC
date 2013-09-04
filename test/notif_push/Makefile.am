AM_CPPFLAGS = \
	-I$(top_srcdir)/source/ \
	-I$(top_srcdir)/source/idl \
	-I$(top_srcdir)/source/file \
	-I$(top_srcdir)/source/util \
	-I$(top_srcdir)/source/util/parser \
	@TIDORBC_LIBS@ -D_TIDORB

np_idl_dependencies = Event.C POA_Event.C

CLEANFILES = $(np_idl_dependencies)

POA_Event.C: Event.C

Event.C: Event.idl
	${IDLC} -D_PRE_3_0_COMPILER_ -I$(top_srcdir)/source/idl/ Event.idl

testdir = $(pkgdatadir)/test/notif_push/
check_PROGRAMS = server consumer1 consumer2 supplier supplier2 supplier3

nodist_server_SOURCES = $(np_idl_dependencies)
server_SOURCES    = server.C

nodist_supplier_SOURCES = $(np_idl_dependencies)
supplier_SOURCES  = supplier.C  MySupplierImpl.h MySupplierImpl.C

nodist_supplier2_SOURCES = $(np_idl_dependencies)
supplier2_SOURCES  = supplier2.C  

nodist_supplier3_SOURCES = $(np_idl_dependencies)
supplier3_SOURCES  = supplier3.C  

nodist_consumer1_SOURCES = $(np_idl_dependencies)
consumer1_SOURCES = consumer1.C MyConsumerImpl.h MyConsumerImpl.C

nodist_consumer2_SOURCES = $(np_idl_dependencies)
consumer2_SOURCES = consumer2.C MyConsumerImpl2.h MyConsumerImpl2.C

noinst_HEADERS = Event.idl

std_ldadd = \
	$(top_srcdir)/source/libTIDNotifC.la \
	$(top_srcdir)/source/idl/libTIDNotifCIdl.la \
	@TIDORBC_LDFLAGS@ \
	@TIDORBC_LIBS@

server_LDADD = $(std_ldadd)

supplier_LDADD = $(std_ldadd)

supplier2_LDADD = $(std_ldadd)

supplier3_LDADD = $(std_ldadd)

consumer1_LDADD = $(std_ldadd)

consumer2_LDADD = $(std_ldadd)

#TESTS = server supplier supplier2 supplier3 consumer1 consumer2
