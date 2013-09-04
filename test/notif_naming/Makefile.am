AM_CPPFLAGS = \
	-I$(top_srcdir)/source/ \
	-I$(top_srcdir)/source/idl \
	-I$(top_srcdir)/source/file \
	-I$(top_srcdir)/source/util \
	-I$(top_srcdir)/source/util/parser \
	@TIDORBC_LIBS@ -D_TIDORB

np_idl_dependencies = 

CLEANFILES = $(np_idl_dependencies)

testdir = $(pkgdatadir)/test/notif_naming/
check_PROGRAMS = server consumer supplier 

nodist_server_SOURCES = $(np_idl_dependencies)
server_SOURCES    = server.C

nodist_supplier_SOURCES = $(np_idl_dependencies)
supplier_SOURCES  = supplier.C MySupplierImpl.h MySupplierImpl.C

nodist_consumer_SOURCES = $(np_idl_dependencies)
consumer_SOURCES = consumer.C MyConsumerImpl.h MyConsumerImpl.C 

std_ldadd = \
	$(top_srcdir)/source/libTIDNotifC.la \
	$(top_srcdir)/source/idl/libTIDNotifCIdl.la \
	@TIDORBC_LDFLAGS@ \
	@TIDORBC_LIBS@

server_LDADD = $(std_ldadd)

supplier_LDADD = $(std_ldadd)

consumer_LDADD = $(std_ldadd)

#TESTS = server supplier supplier2 supplier3 consumer1 consumer2
