#ifndef FFLKSTK_H
#define FFLKSTK_H 1

#include "cfortran.h"
#include "Rtypes.h"

#include "Fdimpar.h"

extern "C" {
//*$ create flkstk.add
//*copy flkstk
/*
*
*----------------------------------------------------------------------*
*                                                                      *
*     Partial (some variables come from FLUKA87)                       *
*     Copyright (C) 1996-2010      by    Alfredo Ferrari & Paola Sala  *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*     FLUKA90-200x particle stack:                                     *
*                                                                      *
*     Changes: last change on 17-Oct-2010   by    Alfredo Ferrari      *
*                                                                      *
*     /Flkstk/ stack for the primaries                                 *
*        Wtflk  = particle statistical weight                          *
*        Pmoflk = particle (laboratory) momentum (GeV/c)               *
*        Tkeflk = particle (laboratory) kinetic energy (GeV)           *
*        Xflk   = particle position  x-coordinate                      *
*        Yflk   = particle position  y-coordinate                      *
*        Zflk   = particle position  z-coordinate                      *
*        Txflk  = particle direction x-coordinate                      *
*        Tyflk  = particle direction y-coordinate                      *
*        Tzflk  = particle direction z-coordinate                      *
*        Txpol  = x direction cosine of the particle polarization      *
*        Typol  = y direction cosine of the particle polarization      *
*        Tzpol  = z direction cosine of the particle polarization      *
*        Txnor  = x direction cosine of a (possible) surface normal    *
*        Tynor  = y direction cosine of a (possible) surface normal    *
*        Tznor  = z direction cosine of a (possible) surface normal    *
*        Dfnear = distance to the nearest boundary                     *
*        Agestk = age of the particle (seconds)                        *
*        Aknshr = Kshort component of K0/K0bar                         *
*        Frcphn = cross section for force photonuclear interaction (if *
*                 < 0), distance to a forced photonuclear interaction  *
*                (if > 0)                                              *
*        Lfrphn = flag for forced photonuclear interaction             *
*        Raddly = delay (s) in production wrt the nominal primary "0"  *
*                 time for particle produced in radioactive decays     *
*                (i.e. those coming from decays of daughter isotopes), *
*                 when in analogue mode, flag for position in the      *
*                 activr array when in non-analogue mode               *
*        Cmpath = cumulative path travelled by the particle since it   *
*                 was produced (cm)                                    *
*        Dchflk = de-channeling length                                 *
*        Sparek = spare real variables available for K.W.Burn          *
*        Ispark = spare integer variables available for K.W.Burn       *
*        Iloflk = particle identity (Paprop numbering)                 *
*        Igroup = energy group for low energy neutrons                 *
*        Loflk  = particle generation                                  *
*        Louse  = user flag                                            *
*        Nrgflk = particle region number                               *
*        Nlattc = particle lattice cell number                         *
*        Nhspnt = pointer to the history object (Geant4 geometry)      *
*        Nevent = number of the event which created the particle       *
*        Numpar = particle number                                      *
*        Lraddc = flag for particles generated in radioactive decays   *
*        Lchflk = flag for channeled particle                          *
*        Nparma = largest particle number ever reached                 *
*        Nstmax = highest value of the stack pointer ever reached      *
*                 in the run                                           *
*        Npflka = Fluka stack pointer                                  *
*        Nstaol = stack pointer of the last processed particle         *
*        Igroun = energy group number of the last processed particle   *
*                 if it is a low energy neutron                        *
*                                                                      *
*----------------------------------------------------------------------*
*
      LOGICAL LRADDC, LFRPHN, LCHFLK
      COMMON / FLKSTK /
     &          XFLK   (0:MFSTCK), YFLK   (0:MFSTCK), ZFLK   (0:MFSTCK),
     &          TXFLK  (0:MFSTCK), TYFLK  (0:MFSTCK), TZFLK  (0:MFSTCK),
     &          TXPOL  (0:MFSTCK), TYPOL  (0:MFSTCK), TZPOL  (0:MFSTCK),
     &          TXNOR  (0:MFSTCK), TYNOR  (0:MFSTCK), TZNOR  (0:MFSTCK),
     &          WTFLK  (0:MFSTCK), PMOFLK (0:MFSTCK), TKEFLK (0:MFSTCK),
     &          DFNEAR (0:MFSTCK), AGESTK (0:MFSTCK), AKNSHR (0:MFSTCK),
     &          RADDLY (0:MFSTCK), CMPATH (0:MFSTCK), FRCPHN (0:MFSTCK),
     &          DCHFLK (0:MFSTCK),
     &          SPAREK (MKBMX1,0:MFSTCK),      ISPARK (MKBMX2,0:MFSTCK),
     &          ILOFLK (0:MFSTCK), IGROUP (0:MFSTCK), LOFLK  (0:MFSTCK),
     &          LOUSE  (0:MFSTCK), NRGFLK (0:MFSTCK), NLATTC (0:MFSTCK),
     &          NHSPNT (0:MFSTCK), NEVENT (0:MFSTCK), NUMPAR (0:MFSTCK),
     &          LRADDC (0:MFSTCK), LFRPHN (0:MFSTCK), LCHFLK (0:MFSTCK),
     &          NPARMA, NSTMAX, NPFLKA, NSTAOL, IGROUN
      SAVE / FLKSTK /
*/

typedef struct {
   Double_t xflk[mfstck+1];           //(0:MFSTCK)
   Double_t yflk[mfstck+1];           //(0:MFSTCK)
   Double_t zflk[mfstck+1];           //(0:MFSTCK)
   Double_t txflk[mfstck+1];          //(0:MFSTCK)
   Double_t tyflk[mfstck+1];          //(0:MFSTCK)
   Double_t tzflk[mfstck+1];          //(0:MFSTCK)
   Double_t txpol[mfstck+1];          //(0:MFSTCK)
   Double_t typol[mfstck+1];          //(0:MFSTCK)
   Double_t tzpol[mfstck+1];          //(0:MFSTCK)
   Double_t txnor[mfstck+1];          //(0:MFSTCK)
   Double_t tynor[mfstck+1];          //(0:MFSTCK)
   Double_t tznor[mfstck+1];          //(0:MFSTCK)
   Double_t wtflk[mfstck+1];          //(0:MFSTCK)
   Double_t pmoflk[mfstck+1];         //(0:MFSTCK)
   Double_t tkeflk[mfstck+1];         //(0:MFSTCK)
   Double_t dfnear[mfstck+1];         //(0:MFSTCK)
   Double_t agestk[mfstck+1];         //(0:MFSTCK)
   Double_t aknshr[mfstck+1];         //(0:MFSTCK)
   Double_t raddly[mfstck+1];         //(0:MFSTCK)
   Double_t cmpath[mfstck+1];         //(0:MFSTCK)
   Double_t frcphn[mfstck+1];         //(0:MFSTCK)
   Double_t dchflk[mfstck+1];         //(0:MFSTCK)
   Double_t anfstk[mfstck+1];         //(0:MFSTCK)
   Double_t ekpstk[mfstck+1];         //(0:MFSTCK)
   Double_t sparek[mfstck+1][mkbmx1]; //(MKBMX1,0:MFSTCK)
   Int_t    ispark[mfstck+1][mkbmx2]; //(MKBMX2,0:MFSTCK)
   Int_t    infstk[mfstck+1];         //(MFSTCK)
   Int_t    lnfstk[mfstck+1];         //(MFSTCK)
   Int_t    iloflk[mfstck+1];         //(0:MFSTCK)
   Int_t    igroup[mfstck+1];         //(0:MFSTCK)
   Int_t    iprstk[mfstck+1];         //(0:MFSTCK)
   Int_t    loflk[mfstck+1];          //(0:MFSTCK)
   Int_t    louse[mfstck+1];          //(0:MFSTCK)
   Int_t    nrgflk[mfstck+1];         //(0:MFSTCK)
   Int_t    nlattc[mfstck+1];         //(0:MFSTCK)
   Int_t    nhspnt[mfstck+1];         //(0:MFSTCK)
   Int_t    nevent[mfstck+1];         //(0:MFSTCK)
   Int_t    numpar[mfstck+1];         //(0:MFSTCK)
   Int_t    irdazm[mfstck+1];         //(0:MFSTCK)
   Int_t    lraddc[mfstck+1];         //(0:MFSTCK)
   Int_t    lfrphn[mfstck+1];         //(0:MFSTCK)
   Int_t    lchflk[mfstck+1];         //(0:MFSTCK)
   Int_t    nparma;
   Int_t    nstmax;
   Int_t    npflka;
   Int_t    nstaol;
   Int_t    igroun;
} flkstkCommon;
#define FLKSTK COMMON_BLOCK(FLKSTK,flkstk)
COMMON_BLOCK_DEF(flkstkCommon,FLKSTK);
}

#endif
