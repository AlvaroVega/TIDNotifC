#
#  File name: util/parser/Makefile.am
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
	-I$(top_srcdir)/source/Util 	\
	@TIDORBC_LIBS@

AM_YFLAGS = -d

CLEANFILES = \
	parser.h \
	parser.cc \
	scanner.cc 

noinst_LTLIBRARIES = libparser.la

libparser_la_SOURCES = StringValueNode.h StringArrayValueNode.h LongValueNode.h \
		InmediateValueNode.h IdentifierValueNode.h EvaluableNode.h DoubleValueNode.h \
		BooleanValueNode.h parser.yy scanner.ll SimpleNode.h SimpleNode.C TypeValuePair.h \
		TypeValuePair.C EnumValue.h EnumValue.C TIDParser.h TIDParser.C \
		TIDConstraint.h TIDConstraint.C UnaryExprNode.h UnaryExprNode.C \
		BinaryExprNode.h BinaryExprNode.C SequencePath.h SequencePath.C StructFieldNamePath.h \
		StructFieldNamePath.C StructFieldPosPath.h StructFieldPosPath.C ArrayPath.h ArrayPath.C \
		VoidPath.h VoidPath.C UnionDefaultSwitchPath.h UnionDefaultSwitchPath.C \
		UnionIntSwitchPath.h UnionIntSwitchPath.C UnionStringSwitchPath.h UnionStringSwitchPath.C \
		Debugger.h Debugger.C RuntimeVariableTable.C RuntimeVariableTable.h


