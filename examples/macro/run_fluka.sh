#!/bin/sh

# $Id$

#------------------------------------------------
# The Virtual Monte Carlo examples
# Copyright (C) 2007, 2008 Ivana Hrivnacova
# All rights reserved.
#
# For the licensing terms see geant4_vmc/LICENSE.
# Contact: vmc@pcroot.cern.ch
#-------------------------------------------------

#
# Macro for preparing working directory for Fluka
# Adapted macro AliRoot/TFluka/scripts/runflukageo.sh 
# by Andreas Morsch

echo "Preparing Fluka working directory ..." 

CURDIR=`pwd`
WORKDIR=$CURDIR/"fluka_out"

# Remove the previous temporary directory
rm -rf $WORKDIR

# Make a new temporary directory and move to it
mkdir $WORKDIR
cd $WORKDIR

# Link here some special Fluka files needed
#ln -s $FLUPRO/neuxsc_72.bin neuxsc.bin 
ln -s $FLUPRO/neuxsc-ind_260.bin neuxsc.bin
ln -s $FLUPRO/random.dat random.dat

# Copy the random seed
cp $FLUPRO/random.dat old.seed

# Give some meaningfull name to the output
ln -s fluka.out fort.11

#Link FlukaConfig.C as Config.C
ln -fs ../run_fl.C run_fl.C
ln -fs ../flConfig.C flConfig.C
cp $FLUVMC/input/coreFlukaVmc.inp coreFlukaVmc.inp

echo "Preparing Fluka working directory ... finished" 
