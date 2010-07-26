// $Id$

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007, 2008 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

/*! 

/// \file Doxymain.h
/// \brief The main page for the VMC examples + Fluka code documenation

\mainpage The VMC examples with Fluka


\section exa_s1 Introduction

  To demonstrate use of VirtualMC, four Geant4 novice
  examples (N01, N02, N03, N06) has been rewritten
  as VMC applications: \ref E01, \ref E02, \ref E03, \ref E06.
  
  For the complete description of the examples see:
  http://root.cern.ch/drupal/content/examples

  Here we give only instructions how to run the exammples with Fluka.

  See more detail description in the README files
  withing each example subdirectory:
  - \ref README_E01
  - \ref README_E02
  - \ref README_E03
  - \ref README_E06

\section exa_s3 Macros

  In all examples there are provides macros:
  <pre>  
  run_fl.C     - for running example with Fluka
  flConfig.C   - configuration macro for Fluka
  </pre>  

\section exa_s5 To run an example:
  <pre>  
  With Fluka:
  root[0] .x run_fl.C  
  </pre>  
  
\section exa_s6 Test macros:

  To test all possible configurations, there is provided a test
  macro for each examples
  <pre>  
  test_En.C(const TString& configMacro, Bool_t oldGeometry)
  </pre>  
  with parameters:
     - configMacro: configuration macro loaded in initialization 
     - oldGeometry: if true - geometry is defined via VMC, otherwise via TGeo
     
  The tests with all configurations can be run within
  the test suite:
  <pre>  
  test_suite.sh
  </pre>  
  which saves all test outputs in the files which names correspond
  to run configuration:
  <pre>
  test_fl_tgeo.out  - Fluka, geometry defined via TGeo
  test_fl_vmc.out   - Fluka, geometry defined via VMC
  </pre>
  The files are saved in log/E0n directory.
  The reference output files, which are updated with each release,
  can be found at log_ref directory.  
   
  All run_*.C macros can be run via run suite script:
  <pre>  
  run_suite.sh
  </pre>  
  which saves all output in run_*.out files.
  
*/
