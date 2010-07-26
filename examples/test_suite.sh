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
# Run tests for all VMC examples with Fluka and regenerate output files
#
# By I. Hrivnacova, IPN Orsay

CURDIR=`pwd`
OUTDIR=$CURDIR/log

# Recreate log directory
rm -fr $OUTDIR

for EXAMPLE in E01 E02 E03 E06
do
  OUT=$OUTDIR/$EXAMPLE
  if [ ! -d $OUT ]; then
    mkdir -p $OUT
  fi
  
  cd $CURDIR/$EXAMPLE

  echo "... Example $EXAMPLE"
  
  MACRODIR="$G4VMC/examples/$EXAMPLE"
  
  if [ "$EXAMPLE" != "E03" ]; then 
  
    echo "... Running test with Fluka, geometry via TGeo" 
    root.exe -q "$MACRODIR/test_$EXAMPLE.C(\"flConfig.C\", kFALSE)" >& $OUT/test_fl_tgeo.out   
 
    echo "... Running test with Fluka, geometry via VMC" 
    root.exe -q "$MACRODIR/test_$EXAMPLE.C(\"flConfig.C\", kTRUE)" >& $OUT/test_fl_vmc.out   

  else
    # Run three macro + special configuration available only in E03 example
    echo "... Running test with Fluka, geometry via TGeo" 
    root.exe -q "$MACRODIR/test_E03_1.C(\"flConfig.C\", kFALSE)" >& $OUT/test_fl_tgeo.out   
    root.exe -q "$MACRODIR/test_E03_2.C(\"flConfig.C\", kFALSE)" >& tmpfile
    cat tmpfile >> $OUT/test_fl_tgeo.out

    echo "... Running test with Fluka, geometry via VMC" 
    root.exe -q "$MACRODIR/test_E03_1.C(\"flConfig.C\", kTRUE)" >& $OUT/test_fl_vmc.out   
    root.exe -q "$MACRODIR/test_E03_2.C(\"flConfig.C\", kTRUE)" >& tmpfile   
    cat tmpfile >> $OUT/test_fl_vmc.out
  fi  

  echo " "
done  
  
cd $CURDIR
