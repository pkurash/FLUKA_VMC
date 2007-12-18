# $Id: Makefile,v 1.12 2004/07/30 12:30:24 brun Exp $

############################### fluka_vmc Makefile ###########################

PACKAGE   = fluka

ifeq ($(PLATFORM),)
PLATFORM = $(shell root-config --arch)
endif

TOPDIR  = $(shell pwd)/..
BINDIR  = $(TOPDIR)/tmp/tgt_$(PLATFORM)
LIBDIR  = $(TOPDIR)/lib/tgt_$(PLATFORM)

ifeq ($(ROOTSYS),)
ROOT_INCDIR = $(shell root-config --incdir)
ROOT_BINDIR = $(shell root-config --prefix)/bin
ROOT_ETCDIR = $(shell root-config --prefix)/etc/vmc
else
ROOT_INCDIR = $(ROOTSYS)/include
ROOT_BINDIR = $(ROOTSYS)/bin
ROOT_ETCDIR = $(ROOTSYS)/etc/vmc
endif

include $(ROOT_ETCDIR)/Makefile.$(PLATFORM)

############################### Sources #######################################


# Rules
#
include $(ROOT_ETCDIR)/MakeRules

# Dictionary
#
GDICT    := $(BINDIR)/flukaCint.cxx
GDICTH   := $(GDICT:.cxx=.h)
GDICTO   := $(patsubst %.cxx,%.o,$(GDICT))

# Sources
#

FSRC	:= FLUKA_input.f crnkvp.f

ifeq ($(FLUSCW),1MEVN)
FSRCS+=fluscw_1mevn.f
endif

ifeq ($(FLUSCW),DEQ99C)
FSRCS+=fluscw_deq99c.f
endif

ifeq ($(COMSCW),DEFAULT)
SRCS+=comscw.cxx
endif

ifeq ($(COMSCW),ACTIVITY)
FSRCS+=comscw_activity.f
endif

CXXSRC	:= $(wildcard *.cxx) 
SRCS	:= $(FSRC) $(CXXSRC)

# ROOT Dictionary
DHDR    := TFlukaLinkDef.h

# C++ Headers copied to include
#
HDRS    := TFlukaCerenkov.h TFlukaCodes.h TFlukaConfigOption.h TFluka.h TFlukaMCGeometry.h TFlukaScoringOption.h TFlukaLinkDef.h  
HEADERS	:= $(wildcard *.h)

# Objects
#
FOBJ	:= $(patsubst %.f,$(BINDIR)/%.o,$(FSRC))
CXXOBJ	:= $(patsubst %.cxx,$(BINDIR)/%.o,$(CXXSRC))
OBJS	:= $(CXXOBJ) $(FOBJ) $(GDICTO)

# External libs
#
ELIBS   := -L$(FLUPRO) -lflukahp -lg2c

# Make include list
#
INCDIR  := -I$(FLUPRO)/flukapro

# C++ compilation flags
#
CXXFLAGS := $(CXXOPTS) -I. $(INCDIR) -I$(ROOT_INCDIR) 

# FORTRAN compilation flags

#FFLAGS      :=  -fno-second-underscore $(CLIBFOPT) -I. $(INCDIR)
FFLAGS      := $(FOPT) $(CLIBFOPT) -I. $(INCDIR)
ifeq ($(PLATFORM),linux)
   FFLAGS      := $(filter-out -O%,$(FFLAGS))  
endif

DEPINC 		+= -I. -I$(ROOT_INCDIR) $(INCDIR)

############################### Targets #######################################


SLIBRARY	= $(LIBDIR)/lib$(PACKAGE).$(SL)
ALIBRARY	= $(LIBDIR)/lib$(PACKAGE).a

default:	depend $(SLIBRARY)
static: 	$(ALIBRARY) 

$(LIBDIR)/lib$(PACKAGE).$(SL):  $(OBJS)
$(LIBDIR)/lib$(PACKAGE).a:      $(OBJS)

DICT:=	 	$(GDICT)

$(DICT): 	$(HDRS)

depend:		$(SRCS)

TOCLEAN		= $(BINDIR) $(TOPDIR)/include
TOCLEANALL	= $(BINDIR) $(TOPDIR)/include $(LIBDIR)

MAKEDIST	= $(ROOT_ETCDIR)/fl_makedist.sh lib
MAKEDISTSRC	= $(ROOT_ETCDIR)/fl_makedist.sh

include $(ROOT_ETCDIR)/MakeMacros

############################### Dependencies ##################################

-include $(BINDIR)/Make-depend
