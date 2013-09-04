#
#  File name: util/Makefile.am
#  File type: makefile file.
#

#
# Copyright (C) 2006 Telefonica I+D S.A.
#
# This source file is a property of Telefonica I+D. You can not
# use it for any purpose unless you have an explicit authorization
# by owner.
#

SUBDIRS = parser .

AM_CPPFLAGS = 				\
	-I$(top_srcdir)/source/		\
	-I$(top_srcdir)/source/idl	\
	@TIDORBC_LIBS@

noinst_LTLIBRARIES = libutil.la

libutil_la_SOURCES = \
	TIDNotifConfig.h \
	TIDNotifConfig.C \
	TIDConfig.h \
	TIDConfig.C \
	TIDPropValue.h \
	TIDPropValue.C \
	TIDNotifUtil.h \
	TIDNotifUtil.C \
	SynSortedMap.h 

