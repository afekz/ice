# **********************************************************************
#
# Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

top_srcdir	= ../..

LIBNAME		= $(call mklibname,TestCommonObjC)

TARGETS		= ../../lib/$(LIBNAME)

OBJS		= TestCommon.o

SRCS		:= $(OBJS:.o=.m)

include $(top_srcdir)/config/Make.rules

ifeq ($(STATICLIBS),yes)
    mklibname	= lib$(1).a
else
    mklibname	= lib$(1).dylib
endif

CPPFLAGS	:= -I../include $(CPPFLAGS)

ifeq ($(STATICLIBS),yes)

../../lib/$(LIBNAME): $(OBJS)
	rm -f $@
	$(call mklib,$@,$(OBJS))

else

../../lib/$(LIBNAME): $(OBJS)
	rm -f $@
	$(call mkshlib,$@,$(LIBNAME),$(OBJS),$(LIBS))

endif
