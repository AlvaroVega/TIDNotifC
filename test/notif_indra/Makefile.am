AM_CPPFLAGS = \
	-I$(top_srcdir)/source/ \
	-I$(top_srcdir)/source/idl \
	-I$(top_srcdir)/source/file \
	-I$(top_srcdir)/source/util \
	-I$(top_srcdir)/source/util/parser \
	@TIDORBC_LIBS@ -D_TIDORB

testdir = $(pkgdatadir)/test/notif_indra/
check_PROGRAMS = Consumer Publisher FirstPublisher

nodist_Publisher_SOURCES = 
Publisher_SOURCES    = Publisher.cc

nodist_FirstPublisher_SOURCES = 
FirstPublisher_SOURCES    = FirstPublisher.cc

nodist_Consumer_SOURCES = 
Consumer_SOURCES  = Consumer.cc ConsumerEvtImpl.h ConsumerEvtImpl.cc

std_ldadd = \
	$(top_srcdir)/source/libTIDNotifC.la \
	$(top_srcdir)/source/idl/libTIDNotifCIdl.la \
	@TIDORBC_LDFLAGS@ \
	@TIDORBC_LIBS@

Consumer_LDADD = $(std_ldadd)

Publisher_LDADD = $(std_ldadd)

FirstPublisher_LDADD = $(std_ldadd)


#TESTS = FirstPublisher Publisher Consumer
