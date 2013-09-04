
AM_CPPFLAGS = \
	-I$(top_srcdir)/source/ \
	-I$(top_srcdir)/source/idl \
	-I$(top_srcdir)/source/file \
	-I$(top_srcdir)/source/util \
	-I$(top_srcdir)/source/util/parser \
	@TIDORBC_LIBS@

np_idl_dependencies = Event.C

CLEANFILES = $(np_idl_dependencies)

testdir = $(pkgdatadir)/test/filter/

check_PROGRAMS = test_filter 

noinst_HEADERS = Event.idl

Event.C: Event.idl
	${IDLC} -D_PRE_3_0_COMPILER_ -I$(top_srcdir)/test/filter/ Event.idl

#nodist_test_filter_SOURCES = Event.C Event.h
nodist_test_filter_SOURCES = $(np_idl_dependencies)

test_filter_SOURCES = \
	test_filter.C \
	my_push_supplier.C \
	my_push_consumer.C \
	my_push_supplier.h \
	my_push_consumer.h

test_filter_LDADD = \
	$(top_srcdir)/source/libTIDNotifC.la \
	$(top_srcdir)/source/util/libutil.la \
	$(top_srcdir)/source/util/parser/libparser.la	\
	$(top_srcdir)/source/file/libfile.la \
	$(top_srcdir)/source/idl/libTIDNotifCIdl.la \
	@TIDORBC_LDFLAGS@ @TIDORBC_LIBS@

#TESTS = test_filter

