#------------------------------------------------
# The Virtual Monte Carlo packages
# Copyright (C) 2014 Ivana Hrivnacova
# All rights reserved.
#
# For the licensing terms see geant4_vmc/LICENSE.
# Contact: root-vmc@cern.ch
#-------------------------------------------------

# Configuration file for CMake build for Fluka VMC package
# which defines customised installation.
#
# I. Hrivnacova, 13/06/2014

# Copy the custom cmake modules into the build tree
foreach(_mod CMakeMacroParseArguments UseVMC UseMC VMCBuildMode VMCInstallLibDir)
  configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/${_mod}.cmake
    ${PROJECT_BINARY_DIR}/Modules/${_mod}.cmake
    COPYONLY
  )
endforeach()

# Find modules
foreach(_find_mod Garfield Pythia6 VMCPackages MCPackages)
  configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/Find${_find_mod}.cmake
    ${PROJECT_BINARY_DIR}/Modules/Find${_find_mod}.cmake
    COPYONLY
  )
endforeach()

# Set needed variables for the install tree
set(FlukaVMC_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/cmake)

# Install the custom modules for the examples
install(DIRECTORY
  ${PROJECT_BINARY_DIR}/Modules/
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/FlukaVMC-${FlukaVMC_VERSION}/Modules
  COMPONENT Development
)

# Install examples
if(FlukaVMC_INSTALL_DATA)
  install(DIRECTORY
    ${PROJECT_SOURCE_DIR}/examples
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/FlukaVMC-${FlukaVMC_VERSION}
  )
endif()

#
# Install the FlukaVMCConfig, FlukaVMCConfigVersion
#
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/FlukaVMCConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/FlukaVMCConfig.cmake" @ONLY)

configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/FlukaVMCConfigVersion.cmake.in"
  "${PROJECT_BINARY_DIR}/FlukaVMCConfigVersion.cmake" @ONLY)

install(FILES
  "${PROJECT_BINARY_DIR}/FlukaVMCConfig.cmake"
  "${PROJECT_BINARY_DIR}/FlukaVMCConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/FlukaVMC-${FlukaVMC_VERSION})

install(EXPORT FlukaVMCTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/FlukaVMC-${FlukaVMC_VERSION})
