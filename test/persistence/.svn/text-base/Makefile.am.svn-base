AM_CPPFLAGS = \
	-I$(top_srcdir)/source/ \
	-I$(top_srcdir)/source/idl \
	-I$(top_srcdir)/source/file \
	-I$(top_srcdir)/source/util \
	-I$(top_srcdir)/source/util/parser \
	@TIDORBC_LIBS@

testdir = $(pkgdatadir)/test/persistence/
check_PROGRAMS = server_supplier server_consumer recover_server_supplier

np_idl_dependencies = Event.C

CLEANFILES = $(np_idl_dependencies)

noinst_HEADERS = Event.idl

Event.C: Event.idl
	${IDLC} -D_PRE_3_0_COMPILER_ -I$(top_srcdir)/source/idl/ Event.idl

nodist_server_supplier_SOURCES = $(np_idl_dependencies)
server_supplier_SOURCES = \
	server_supplier.C \
	my_push_supplier.C \
	my_push_supplier.h

nodist_server_consumer_SOURCES = $(np_idl_dependencies)
server_consumer_SOURCES = server_consumer.C \
        my_push_consumer.C \
        my_push_consumer.h

nodist_recover_server_supplier_SOURCES = $(np_idl_dependencies)
recover_server_supplier_SOURCES = \
	recover_server_supplier.C \
	my_push_supplier.C \
	my_push_supplier.h

server_supplier_LDADD = \
	$(top_srcdir)/source/libTIDNotifC.la \
	$(top_srcdir)/source/util/libutil.la \
	$(top_srcdir)/source/util/parser/libparser.la	\
	$(top_srcdir)/source/file/libfile.la \
	$(top_srcdir)/source/idl/libTIDNotifCIdl.la \
	@TIDORBC_LDFLAGS@ @TIDORBC_LIBS@

server_consumer_LDADD = \
	$(top_srcdir)/source/libTIDNotifC.la \
	$(top_srcdir)/source/util/libutil.la \
	$(top_srcdir)/source/util/parser/libparser.la	\
	$(top_srcdir)/source/file/libfile.la \
	$(top_srcdir)/source/idl/libTIDNotifCIdl.la \
	@TIDORBC_LDFLAGS@ @TIDORBC_LIBS@

recover_server_supplier_LDADD = \
	$(top_srcdir)/source/libTIDNotifC.la \
	$(top_srcdir)/source/util/libutil.la \
	$(top_srcdir)/source/util/parser/libparser.la	\
	$(top_srcdir)/source/file/libfile.la \
	$(top_srcdir)/source/idl/libTIDNotifCIdl.la \
	@TIDORBC_LDFLAGS@ @TIDORBC_LIBS@
