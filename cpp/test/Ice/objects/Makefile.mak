# **********************************************************************
#
# Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

top_srcdir	= ..\..\..

!if "$(WINRT)" != "yes"
NAME_PREFIX	=
EXT		= .exe
OBJDIR		= .
!else
NAME_PREFIX	= Ice_objects_
EXT		= .dll
OBJDIR		= winrt
!endif

CLIENT		= $(NAME_PREFIX)client
SERVER		= $(NAME_PREFIX)server
COLLOCATED	= $(NAME_PREFIX)collocated
TESTLIBNAME	= libTestDerived.lib

TARGETS		= $(CLIENT)$(EXT) $(SERVER)$(EXT) $(COLLOCATED)$(EXT) $(TESTLIBNAME)

SLICE_OBJS	= $(OBJDIR)\Test.obj \
		  $(OBJDIR)\Derived.obj \
		  $(OBJDIR)\DerivedEx.obj

COBJS		= $(OBJDIR)\TestI.obj \
		  $(OBJDIR)\Client.obj \
		  $(OBJDIR)\AllTests.obj

SOBJS		= $(SLICE_OBJS) \
		  $(OBJDIR)\TestI.obj \
		  $(OBJDIR)\TestIntfI.obj \
		  $(OBJDIR)\Server.obj

COLOBJS		= $(SLICE_OBJS) \
		  $(OBJDIR)\TestI.obj \
		  $(OBJDIR)\TestIntfI.obj \
		  $(OBJDIR)\Collocated.obj \
		  $(OBJDIR)\AllTests.obj

OBJS		= $(COBJS) \
		  $(SOBJS) \
		  $(COLOBJS)

!include $(top_srcdir)/config/Make.rules.mak

CPPFLAGS	= -I. -I../../include $(CPPFLAGS) -DWIN32_LEAN_AND_MEAN
LINKWITH	= testcommon$(LIBSUFFIX).lib $(LIBS)
SLICE2CPPFLAGS	= -I. $(SLICE2CPPFLAGS)

!if "$(GENERATE_PDB)" == "yes"
CPDBFLAGS        = /pdb:$(CLIENT).pdb
SPDBFLAGS        = /pdb:$(SERVER).pdb
COPDBFLAGS       = /pdb:$(COLLOCATED).pdb
!endif

$(CLIENT)$(EXT): $(COBJS) $(TESTLIBNAME)
	$(LINK) $(LD_TESTFLAGS) $(CPDBFLAGS) $(COBJS) $(PREOUT)$@ $(PRELIBS)$(LINKWITH) libTestDerived.lib
	@if exist $@.manifest echo ^ ^ ^ Embedding manifest using $(MT) && \
	    $(MT) -nologo -manifest $@.manifest -outputresource:$@;#1 && del /q $@.manifest

$(TESTLIBNAME): $(SLICE_OBJS)
	$(AR) $(ARFLAGS) $(SLICE_OBJS) /out:$(TESTLIBNAME)

$(SERVER)$(EXT): $(SOBJS)
	$(LINK) $(LD_TESTFLAGS) $(SPDBFLAGS) $(SOBJS) $(PREOUT)$@ $(PRELIBS)$(LINKWITH)
	@if exist $@.manifest echo ^ ^ ^ Embedding manifest using $(MT) && \
	    $(MT) -nologo -manifest $@.manifest -outputresource:$@;#1 && del /q $@.manifest

$(COLLOCATED)$(EXT): $(COLOBJS)
	$(LINK) $(LD_TESTFLAGS) $(COPDBFLAGS) $(COLOBJS) $(PREOUT)$@ $(PRELIBS)$(LINKWITH)
	@if exist $@.manifest echo ^ ^ ^ Embedding manifest using $(MT) && \
	    $(MT) -nologo -manifest $@.manifest -outputresource:$@;#1 && del /q $@.manifest

clean::
	del /q Test.cpp Test.h
	del /q Derived.cpp Derived.h
	del /q DerivedEx.cpp DerivedEx.h
