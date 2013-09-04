#
#  File name: qos/Makefile.am
#  File type: makefile file.
#

#
# Copyright (C) 2006 Telefonica I+D S.A.
#
# This source file is a property of Telefonica I+D. You can not
# use it for any purpose unless you have an explicit authorization
# by owner.
#

AM_CPPFLAGS = 				\
	-I$(top_srcdir)/source/		\
	-I$(top_srcdir)/source/idl/	\
	@TIDORBC_LIBS@

noinst_LTLIBRARIES = libqos.la

libqos_la_SOURCES =				\
	qos.h					\
	QoSProperty.h    			\
	QoSProperty.C    			\
	QoSAdmin.h 				\
	QoSAdmin.C 				\
	ProxyQoSAdmin.h				\
	ProxyQoSAdmin.C				\
	ChannelQoSAdmin.h 			\
	ChannelQoSAdmin.C 			\
	EventQoSAdmin.h			 	\
	EventQoSAdmin.C			 	\
	EventReliabilityProperty.h 		\
	EventReliabilityProperty.C 		\
	ConnectionReliabilityProperty.h 	\
	ConnectionReliabilityProperty.C 	\
	QueueOrderProperty.h 			\
	QueueOrderProperty.C 			\
	StartTimeProperty.h 			\
	StartTimeProperty.C 			\
	StartTimeSupportedProperty.h 		\
	StartTimeSupportedProperty.C 		\
	StopTimeProperty.h			\
	StopTimeProperty.C			\
	StopTimeSupportedProperty.h 		\
	StopTimeSupportedProperty.C 		\
	TimeoutProperty.h			\
	TimeoutProperty.C			\
	PriorityProperty.h			\
	PriorityProperty.C

