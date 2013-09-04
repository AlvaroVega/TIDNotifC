#
#  File name: Makefile.am
#  File type: makefile file.
#

#
# Copyright (C) 2006 Telefonica I+D S.A.
#
# This source file is a property of Telefonica I+D. You can not
# use it for any purpose unless you have an explicit authorization
# by owner.
#

SUBDIRS = .

AM_CPPFLAGS = 				\
	-I$(top_srcdir)/source/			\
	-I$(top_srcdir)/source/idl/		\
	-I$(top_srcdir)/source/util/		\
	-I$(top_srcdir)/source/util/parser/	\
	@TIDORBC_LIBS@

noinst_LTLIBRARIES = libfile.la

libfile_la_SOURCES = 		\
	FILEPersistenceDB.h	\
	FILEPersistenceDB.C	\
	FileUID.h		\
	FileUID.C		\
	IOException.h		\
	IOException.C


