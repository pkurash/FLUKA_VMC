#------------------------------------------------
# The Virtual Monte Carlo packages
# Copyright (C) 2014 Ivana Hrivnacova
# All rights reserved.
#
# For the licensing terms see geant4_vmc/LICENSE.
# Contact: root-vmc@cern.ch
#-------------------------------------------------

# Configuration file for CMake build for FlukaVMC with VMC package.
# Inspired by Geant4, Geant4 VMC and VGM projects.
#
# I. Hrivnacova, 13/06/2014

#---  Enforce an out-of-source builds before anything else ---------------------
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(STATUS "FlukaVMC requires an out-of-source build.")
    message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
    message(STATUS "CMakeCache.txt")
    message(STATUS "CMakeFiles")
    message(STATUS "Once these files are removed, create a separate directory")
    message(STATUS "and run CMake from there")
    message(FATAL_ERROR "in-source build detected")
endif()

#--- Define CMake requirements -------------------------------------------------
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

#--- Prepend our own CMake Modules to the search path --------------------------
set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH})

#--- Project definitions -------------------------------------------------------
project(FlukaVMC)
set(${PROJECT_NAME}_VERSION_MAJOR "2011")
set(${PROJECT_NAME}_VERSION_MINOR "3")
set(${PROJECT_NAME}_VERSION_PATCH "0")
set(${PROJECT_NAME}_VERSION
    ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})

#--- Default project build mode ------------------------------------------------
#PH Ok
include(VMCBuildMode)

#--- Options -------------------------------------------------------------------
option(FlukaVMC_INSTALL_DATA "Install data directory" ON)
option(FLUKAWITHDPMJET "Link with dpmjet3" OFF)
option(BUILD_SHARED_LIBS "Build the dynamic libraries" ON)

#--- Enable Fortran ------------------------------------------------------------
enable_language(Fortran)

#--- Find required packages ----------------------------------------------------
#PH Ok
include(FlukaVMCRequiredPackages)

#--- Utility to defined installation lib directory -----------------------------
#PH Ok
include(VMCInstallLibDir)

#--- Project library -----------------------------------------------------------
#PH Ok
include(FlukaVMCBuildLibrary)

#--- Build project configuration -----------------------------------------------
include(FlukaVMCBuildProject)

#--- CPack ----------------- --------------------------------------------------
include(FlukaVMCCPack)
