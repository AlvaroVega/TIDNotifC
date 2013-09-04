AM_CPPFLAGS = \
	-I$(top_srcdir)/source/ \
	-I$(top_srcdir)/source/idl \
	-I$(top_srcdir)/source/file \
	-I$(top_srcdir)/source/util \
	-I$(top_srcdir)/source/util/parser \
	@TIDORBC_LIBS@ -D_TIDORB


testdir = $(pkgdatadir)/test/notif_rir/
check_PROGRAMS = server 

nodist_server_SOURCES = $(np_idl_dependencies)
server_SOURCES    = server.C

std_ldadd = \
	$(top_srcdir)/source/libTIDNotifC.la \
	$(top_srcdir)/source/idl/libTIDNotifCIdl.la \
	@TIDORBC_LDFLAGS@ \
	@TIDORBC_LIBS@

server_LDADD = $(std_ldadd)


#TESTS = server supplier supplier2 supplier3 consumer1 consumer2
