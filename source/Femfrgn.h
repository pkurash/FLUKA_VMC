#ifndef FEMFRGN_H
#define FEMFRGN_H 1

#include "cfortran.h"
#include "Rtypes.h"
extern "C" {
  //*$ CREATE EMFRGN.ADD
  //*COPY EMFRGN
  //*
  //*----------------------------------------------------------------------*
  //*                                                                      *
  //*     Common Emfrgn for EMF                                            *
  //*                                                                      *
  //*----------------------------------------------------------------------*
  //*
  //    COMMON / EMFRGN / ELETHR (MXXRGN), PHOTHR (MXXRGN),
  //   &                  EMREJE, EMSAMP, EMSNGL,
  //   &                  MEDEMF (MXXRGN), IRAYLR (MXXRGN), NRGEMF,
  //   &                  NOSCAT, NOLLDA
  // OLD EFMRGN:
  //    COMMON / EFMRGN / RHOR   (MXXRGN), ECUT   (MXXRGN), PCUT (MXXRGN),
  //   &                  EMREJE, EMSAMP, EMSNGL, VACDST,
  //   &                  MEDEMF (MXXRGN), IRAYLR (MXXRGN), NRGEMF,
  //   &                  NOSCAT, NOLLDA
  //*D === Obsolete variable names === *
  //*D     DIMENSION MED (MXXRGN)
  //*D     EQUIVALENCE ( MED (1), MEDEMF (1) )
typedef struct {
  Double_t elethr[mxxrgn];
  Double_t phothr[mxxrgn];
  Double_t emreje;
  Double_t emsamp;
  Double_t emsngl;
  Int_t    medemf[mxxrgn];
  Int_t    iraylr[mxxrgn];
  Int_t    nrgemf;
  Int_t    noscat;
  Int_t    nollda;
} emfrgnCommon;

#define EMFRGN COMMON_BLOCK(EMFRGN,emfrgn)
COMMON_BLOCK_DEF(emfrgnCommon,EMFRGN);
}

#endif
