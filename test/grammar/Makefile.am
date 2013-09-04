
AM_CPPFLAGS = \
	-I$(top_srcdir)/source/idl -I$(top_srcdir)/source/util/parser/ \
	@TIDORBC_LIBS@

testdir = $(pkgdatadir)/test/grammar/
check_PROGRAMS = test_grammar test_complex_grammar

test_grammar_SOURCES = test_grammar.C test_data.h test_utils.h test_utils.C

test_grammar_LDADD = \
	$(top_srcdir)/source/idl/libTIDNotifCIdl.la \
	$(top_srcdir)/source/util/parser/libparser.la \
	@TIDORBC_LDFLAGS@ \
	@TIDORBC_LIBS@

test_complex_grammar_SOURCES = test_complex_grammar.C 

test_complex_grammar_LDADD = \
	$(top_srcdir)/source/idl/libTIDNotifCIdl.la \
	$(top_srcdir)/source/util/parser/libparser.la \
	@TIDORBC_LDFLAGS@ \
	@TIDORBC_LIBS@


TESTS = test_grammar
