#------------------------------------------------
# The Virtual Monte Carlo packages
# Copyright (C) 2015 Ivana Hrivnacova
# All rights reserved.
#
# For the licensing terms see geant4_vmc/LICENSE.
# Contact: root-vmc@cern.ch
#-------------------------------------------------

# - Try to find FLUKA instalation
# This module sets up FLUKA information
# It defines:
# FLUKA_FOUND           If FLUKA is found
# FLUKA_LIBRARY         the FLUKA library
# FLUKA_DPMJET_LIBRARY  the DPMJET library in Fluka installation
# FLUKA_RQMD_LIBRARY    the RQMD library in Fluka installation 

message(STATUS "Looking for FLUKA ...")

#option(FLUKAWITHDPMJET "Link with dpmjet3" OFF)

# Alternative paths which can be defined by user
set(FLUKA_DIR "" CACHE PATH "Directory where FLUKA is installed")
set(FLUKA_LIB_DIR "" CACHE PATH "Alternative directory for FLUKA libraries")

find_library(FLUKA_LIBRARY NAMES fluka
	           HINTS ${FLUKA_DIR}/lib ${FLUKA_LIB_DIR}
             HINTS $ENV{FLUPRO})
message(STATUS FLUKA_LIBRARY ${FLUKA_LIBRARY})

if(FLUKA_LIBRARY)
  add_library(fluka STATIC IMPORTED)
  set_target_properties(fluka PROPERTIES IMPORTED_LOCATION ${FLUKA_LIBRARY})
  # Promote the imported target to global visibility (so we can alias it)
  set_target_properties(fluka PROPERTIES IMPORTED_GLOBAL TRUE)
  add_library(FLUKA::fluka ALIAS fluka)
endif()

if (FLUKA_LIBRARY)
  set (FLUKA_FOUND TRUE)
endif()

if (FLUKAWITHDPMJET)
# dpmjet
find_library(FLUKA_DPMJET_LIBRARY NAMES dpmjet
           HINTS ${FLUKA_DIR}/lib ${FLUKA_LIB_DIR}
           HINTS $ENV{FLUPRO})
message(STATUS FLUKA_DPMJET_LIBRARY ${FLUKA_DPMJET_LIBRARY})

if(FLUKA_DPMJET_LIBRARY)
  add_library(dpmjet STATIC IMPORTED)
  set_target_properties(dpmjet PROPERTIES IMPORTED_LOCATION ${FLUKA_DPMJET_LIBRARY})
  # Promote the imported target to global visibility (so we can alias it)
  set_target_properties(dpmjet PROPERTIES IMPORTED_GLOBAL TRUE)
  add_library(FLUKA::dpmjet ALIAS dpmjet)
endif()

# rqmd (needed only with dpmjet?)
find_library(FLUKA_RQMD_LIBRARY NAMES rqmd
           HINTS ${FLUKA_DIR}/lib ${FLUKA_LIB_DIR}
           HINTS $ENV{FLUPRO})
message(STATUS FLUKA_RQMD_LIBRARY ${FLUKA_RQMD_LIBRARY})

if(FLUKA_RQMD_LIBRARY)
  add_library(rqmd STATIC IMPORTED)
  set_target_properties(rqmd PROPERTIES IMPORTED_LOCATION ${FLUKA_RQMD_LIBRARY})
  # Promote the imported target to global visibility (so we can alias it)
  set_target_properties(rqmd PROPERTIES IMPORTED_GLOBAL TRUE)
  add_library(FLUKA::rqmd ALIAS rqmd)
endif()

if (FLUKA_LIBRARY AND FLUKA_DPMJET_LIBRARY AND FLUKA_RQMD_LIBRARY)
  set (FLUKA_FOUND TRUE)
endif()

endif(FLUKAWITHDPMJET)

if (FLUKA_FOUND)
  if (NOT FLUKA_FIND_QUIETLY)
      message(STATUS "Found FLUKA libraries ${FLUKA_LIBRARY}")
  endif (NOT FLUKA_FIND_QUIETLY)
else(FLUKA_FOUND)
  if (FLUKA_FIND_REQUIRED)
    message(FATAL_ERROR "FLUKA required, but not found")
  endif (FLUKA_FIND_REQUIRED)
endif(FLUKA_FOUND)

# Make variables changeble to the advanced user
mark_as_advanced(FLUKA_LIBRARY)
mark_as_advanced(FLUKA_DPMJET_LIBRARY)
mark_as_advanced(FLUKA_RQMD_LIBRARY)
