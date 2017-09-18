#ifndef FDIMPAR_H
#define FDIMPAR_H

#include "cfortran.h"
#include "Rtypes.h"
extern "C" {
//*----------------------------------------------------------------------*
//*                                                                      *
//*      DIMPAR: included in any routine                                 *
//*                                                                      *
//*          Mxxrgn = maximum number of regions                          *
//*          Mxxmdf = maximum number of media in Fluka                   *
//*          Mxxmde = maximum number of media in Emf                     *
//*          Mfstck = stack dimension in Fluka                           *
//*          Mestck = stack dimension in Emf                             *
//*          Mostck = stack dimension for optical photons                *
//*          Mxprsn = secondary stack dimension for resonance generator  *
//*          Mxpdpm = secondary stack dimension for DPM generators       *
//*          Mxpscs = secondary stack dimension overall                  *
//*          Mxoutu = maximum number of output units                     *
//*          Nallwp = number of allowed particles                        *
//*          Nelemx = number of maximum allowed elements of a compound   *
//*                   or mixture                                         *
//*          Mpdpdx = number of particle types for which EM dE/dx pro-   *
//*                   cesses (ion,pair,bremss) have to be computed       *
//*          Mxhttr = maximum number of (hit) target nucleons for a      *
//*          Mxglwn = maximum neutron group number                       *
//*                   given collision generation                         *
//*          Icomax = maximum number of materials for compounds/mixtures *
//*                  (equal to the sum of the number of materials for    *
//*                   every compound/mixture)                            *
//*          Ichmax = maximum number of harmonic oscillator levels for   *
//*                   compounds/mixtures (equal to the sum of the number *
//*                   of harmonic oscillator levels for every compound   *
//*                   /mixture)                                          *
//*          Nstbis = number of stable isotopes recorded in common iso-  *
//*                   top                                                *
//*          Nqstis = number of "quasi" stable isotopes which are not    *
//*                   in the standard isotopic composition of a given    *
//*                   element, but for which special data (like GDR data)*
//*                   are anyway available                               *
//*          Ntstis = total number of stable ans "quasi" stable isotopes *
//*          Mxpabl = number of resonances inside Hadrin common blocks   *
//*          Idmaxp = number of particles/resonances defined in common   *
//*                   part                                               *
//*          Idmxdc = number of particles/resonances decay channels      *
//*                   defined in common decayc                           *
//*          Ihypmx = maximum number of hyperons in a hypernucleus       *
//*          Mkbmx1 = dimension for KWB real spare array in Fluka Stack  *
//*          Mkbmx2 = dimension for KWB int. spare array in Fluka Stack  *
//*          Mxirrd = maximum number of irradiation sub-intervals        *
//*          Mxtrdc = maximum number of decay (cooling) times            *
//*          Nktl   = overall dimension parameter for EMF bremsstrahlung *
//*          Nblnmx = blank common dimension in real*8 units!            *
//*                                                                      *
//*----------------------------------------------------------------------*   

    const Int_t mxxrgn = 20000;
    const Int_t mxxmdf = 710;
    const Int_t mxxmde = 702;
    const Int_t mfstck = 40000;
    const Int_t mestck = 100;
    const Int_t mostck = 2000;
    const Int_t mxprsn = 100;
    const Int_t mxpdpm = 800;
    const Int_t mxpscs = 60000;
    const Int_t mxglwn = 300;
    const Int_t mxoutu = 50;
    const Int_t mxknwc = 45;
    const Int_t mxeshl = 32;
    const Int_t nallwp = 64;
    const Int_t nelemx = 90;
    const Int_t mpdpdx = 33;
    const Int_t mxhttr = 260;
    const Int_t mxseax = 30;
    const Int_t mxhtnc = mxseax + 1;
    const Int_t icomax = 4000;
    const Int_t ichmax = icomax+mxxmdf;
    const Int_t nstbis = 304;
    const Int_t nqstis = 46;
    const Int_t ntstis = nstbis + nqstis;
    const Int_t mxpabl = 120;
    const Int_t idmaxp = 450;
    const Int_t idmxdc = 2000;
    const Int_t mxmcin = 410;
    const Int_t ihypmx = 4;
    const Int_t mkbmx1 = 11;
    const Int_t mkbmx2 = 11;
    const Int_t mxirrd = 2500;
    const Int_t mxtrdc = 1500;
    const Int_t nktl   = 17;
    const Int_t nblnmx = 60000000;
}  

#endif
