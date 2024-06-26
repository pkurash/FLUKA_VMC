#ifndef FEMFSTK
#define FEMFSTK_H 1

#include "Rtypes.h"
#include "cfortran.h"

#include "Fdimpar.h"
extern "C" {
//*$ create emfstk.add
//*copy emfstk
//*
//*=== emfstk ===========================================================*
//*
//*----------------------------------------------------------------------*
//*                                                                      *
//*     common emfstk (emf stack) for emf                                *
//*                                                                      *
//*     last change on  08-oct-97    by    alfredo ferrari               *
//*                                                                      *
//*----------------------------------------------------------------------*
//*

typedef struct {
   Double_t etemf[mestck]; // total energy in MeV
   Double_t pmemf[mestck];
   Double_t xemf[mestck]; // particle x-coordinate
   Double_t yemf[mestck]; // particle y-coordinate
   Double_t zemf[mestck]; // particle z-coordinate
   Double_t uemf[mestck]; // x direction cosine
   Double_t vemf[mestck]; // y direction cosine
   Double_t wemf[mestck]; // z direction cosine
   Double_t dnear[mestck]; // equivalent to GEANT "safety"
   Double_t upol[mestck]; // polarisation in x direction
   Double_t vpol[mestck]; // polarisation in y direction
   Double_t wpol[mestck]; // polarisation in z direction
   Double_t usnrml[mestck];
   Double_t vsnrml[mestck];
   Double_t wsnrml[mestck];
   Double_t wtemf[mestck]; // weight
   Double_t agemf[mestck]; // age
   Double_t cmpemf[mestck];
   Double_t rdlyem[mestck];
   Double_t ecremf[mestck];
   Double_t anfemf[mestck];
   Double_t ekpemf[mestck];
   Double_t espark[mestck][mkbmx1];
   Long64_t irlatt[mestck]; // lattice cell
   Long64_t nhpemf[mestck];
   Int_t    iremf[mestck];  // region
   Int_t    iespak[mestck][mkbmx2];
   Int_t    ichemf[mestck]; // charge
   Int_t    infemf[mestck];
   Int_t    lnfemf[mestck];
   Int_t    ipremf[mestck];
   Int_t    kchemf[mestck];
   Int_t    lloemf[mestck]; // generation number
   Int_t    louemf[mestck];
   Int_t    lrdemf[mestck];
   Int_t    iazemf[mestck];
   Int_t    npemf;  // number of particles in stack
   Int_t    npstrt; // EMF stack index before the interaction (since
                    // the projectile disappears it is also the starting
                    // index of secondaries)
} emfstkCommon; 
#define EMFSTK COMMON_BLOCK(EMFSTK,emfstk)
COMMON_BLOCK_DEF(emfstkCommon,EMFSTK);
}
#endif
