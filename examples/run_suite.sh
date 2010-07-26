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
# Test all VMC examples with Fluka and regenerate output files
#
# by I. Hrivnacova, IPN Orsay

CURDIR=`pwd`

for EXAMPLE in E01 E02 E03 E06
do
  cd $CURDIR/$EXAMPLE

  # run Fluka
  echo "... Running example $EXAMPLE with Fluka" 
  root.exe -q "run_fl.C"  >& run_fl.out

done
        
cd $CURDIR
