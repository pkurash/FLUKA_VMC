#------------------------------------------------
# The Virtual Monte Carlo packages
# Copyright (C) 2014 Ivana Hrivnacova
# All rights reserved.
#
# For the licensing terms see geant4_vmc/LICENSE.
# Contact: root-vmc@cern.ch
#-------------------------------------------------

# CMake Configuration file for geant4_vmc
# I. Hrivnacova, 13/06/2014

#---CMake required version -----------------------------------------------------
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

#-------------------------------------------------------------------------------
# Define installed names
#
set(library_name flukavmc)

#-------------------------------------------------------------------------------
# Includes
#
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${VMC_INCLUDE_DIRS})

#-------------------------------------------------------------------------------
# Setup project include directories; compile definitions; link libraries
#
include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/source
  ${CMAKE_CURRENT_BINARY_DIR})

#-------------------------------------------------------------------------------
# Generate Root dictionaries
#
ROOT_GENERATE_DICTIONARY(
  ${library_name}_dict
  TFlukaCerenkov.h
  TFlukaCodes.h
  TFlukaConfigOption.h
  TFluka.h
  TFlukaMCGeometry.h
  TFlukaScoringOption.h
  TFlukaIon.h
  MODULE ${library_name}
  OPTIONS "-I${CMAKE_INSTALL_PREFIX}/include/TFluka"
    -excludePath "${CMAKE_CURRENT_BINARY_DIR}"
    -excludePath "${PROJECT_SOURCE_DIR}"
  LINKDEF source/TFlukaLinkDef.h)

# Files produced by the dictionary generation
SET(root_dict
  ${library_name}_dict.cxx)
SET(root_dict_libs
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${library_name}_rdict.pcm
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${library_name}.rootmap)

#-------------------------------------------------------------------------------
# Always use '@rpath' in install names of libraries.
#
set(CMAKE_MACOSX_RPATH 1)

#-------------------------------------------------------------------------------
# Locate sources for this project
#

# Fortran sources
set(fortran_sources ${PROJECT_SOURCE_DIR}/source/FLUKA_input.f)
if("${COMSCW}" STREQUAL "ACTIVITY")
  list(APPEND fortran_sources ${PROJECT_SOURCE_DIR}/source/comscw_activity.f)
endif()
message(STATUS "fortran_sources ${fortran_sources}")

# C++ sources
set(cxx_sources
  ${PROJECT_SOURCE_DIR}/source/abscff.cxx
  ${PROJECT_SOURCE_DIR}/source/bxdraw.cxx
  ${PROJECT_SOURCE_DIR}/source/dffcff.cxx
  ${PROJECT_SOURCE_DIR}/source/eedraw.cxx
  ${PROJECT_SOURCE_DIR}/source/endraw.cxx
  ${PROJECT_SOURCE_DIR}/source/magfld.cxx
  ${PROJECT_SOURCE_DIR}/source/mgdraw.cxx
  ${PROJECT_SOURCE_DIR}/source/queffc.cxx
  ${PROJECT_SOURCE_DIR}/source/rflctv.cxx
  ${PROJECT_SOURCE_DIR}/source/rfrndx.cxx
  ${PROJECT_SOURCE_DIR}/source/sodraw.cxx
  ${PROJECT_SOURCE_DIR}/source/source.cxx
  ${PROJECT_SOURCE_DIR}/source/stupre.cxx
  ${PROJECT_SOURCE_DIR}/source/stuprf.cxx
  ${PROJECT_SOURCE_DIR}/source/TFlukaCerenkov.cxx
  ${PROJECT_SOURCE_DIR}/source/TFlukaConfigOption.cxx
  ${PROJECT_SOURCE_DIR}/source/TFluka.cxx
  ${PROJECT_SOURCE_DIR}/source/TFlukaIon.cxx
  ${PROJECT_SOURCE_DIR}/source/TFlukaMCGeometry.cxx
  ${PROJECT_SOURCE_DIR}/source/TFlukaScoringOption.cxx
  ${PROJECT_SOURCE_DIR}/source/usdraw.cxx
  )
if("${COMSCW}" STREQUAL "ACTIVITY")
  list(APPEND cxx_sources ${PROJECT_SOURCE_DIR}/source/comscw.cxx)
endif()
message(STATUS "cxx_sources ${cxx_sources}")

#-------------------------------------------------------------------------------
# Locate headers for this project
#
set(headers
  ${PROJECT_SOURCE_DIR}/source/Falldlt.h
  ${PROJECT_SOURCE_DIR}/source/Fbeamcm.h
  ${PROJECT_SOURCE_DIR}/source/Fcomput.h
  ${PROJECT_SOURCE_DIR}/source/Fdblprc.h
  ${PROJECT_SOURCE_DIR}/source/Fdimpar.h
  ${PROJECT_SOURCE_DIR}/source/Fdpdxcm.h
  ${PROJECT_SOURCE_DIR}/source/Fdrawcalls.h
  ${PROJECT_SOURCE_DIR}/source/Femfrgn.h
  ${PROJECT_SOURCE_DIR}/source/Femfstk.h
  ${PROJECT_SOURCE_DIR}/source/Fevtflg.h
  ${PROJECT_SOURCE_DIR}/source/Ffheavy.h
  ${PROJECT_SOURCE_DIR}/source/Fflkmat.h
  ${PROJECT_SOURCE_DIR}/source/Fflkstk.h
  ${PROJECT_SOURCE_DIR}/source/Fgenstk.h
  ${PROJECT_SOURCE_DIR}/source/Fioiocm.h
  ${PROJECT_SOURCE_DIR}/source/Fiounit.h
  ${PROJECT_SOURCE_DIR}/source/Fltclcm.h
  ${PROJECT_SOURCE_DIR}/source/Fopphcm.h
  ${PROJECT_SOURCE_DIR}/source/Fopphst.h
  ${PROJECT_SOURCE_DIR}/source/Fpaprop.h
  ${PROJECT_SOURCE_DIR}/source/Fpart.h
  ${PROJECT_SOURCE_DIR}/source/Fscohlp.h
  ${PROJECT_SOURCE_DIR}/source/Fsouevt.h
  ${PROJECT_SOURCE_DIR}/source/Fsourcm.h
  ${PROJECT_SOURCE_DIR}/source/Fstepsz.h
  ${PROJECT_SOURCE_DIR}/source/Fsumcou.h
  ${PROJECT_SOURCE_DIR}/source/Ftrackr.h
  ${PROJECT_SOURCE_DIR}/source/TCallf77.h
  ${PROJECT_SOURCE_DIR}/source/TFlukaCerenkov.h
  ${PROJECT_SOURCE_DIR}/source/TFlukaCodes.h
  ${PROJECT_SOURCE_DIR}/source/TFlukaConfigOption.h
  ${PROJECT_SOURCE_DIR}/source/TFluka.h
  ${PROJECT_SOURCE_DIR}/source/TFlukaIon.h
  ${PROJECT_SOURCE_DIR}/source/TFlukaLinkDef.h
  ${PROJECT_SOURCE_DIR}/source/TFlukaMCGeometry.h
  ${PROJECT_SOURCE_DIR}/source/TFlukaScoringOption.h
  )

#---Add definitions-------------------------------------------------------------
# using Clang on Mac OSX
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND APPLE)
  set(CMAKE_SHARED_LINKER_FLAGS
      "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup -Wl,-no_compact_unwind")
endif()

#---Add library-----------------------------------------------------------------
add_library(${library_name} ${fortran_sources} ${cxx_sources}
            ${root_dict} ${headers})
target_link_libraries(${library_name} PRIVATE ${FLUKA_DEPS} PUBLIC ${DPMJET_DEPS} ${VMC_DEPS} ${ROOT_DEPS})
target_include_directories(flukavmc INTERFACE $<INSTALL_INTERFACE:include/TFluka>)

#----Installation---------------------------------------------------------------
install(FILES ${headers} DESTINATION include/TFluka)
install(TARGETS ${library_name} EXPORT FlukaVMCTargets DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${root_dict_libs} DESTINATION ${CMAKE_INSTALL_LIBDIR})
