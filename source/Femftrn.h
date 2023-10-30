#ifndef FEMFTRN_H
#define FEMFTRN_H 1

#include "cfortran.h"
#include "Rtypes.h"
extern "C" {
  /*
*
*=== Emftrn ===========================================================*
*
*----------------------------------------------------------------------*
*                                                                      *
*     Copyright (C) 2003-2019:  CERN & INFN                            *
*     All Rights Reserved.                                             *
*                                                                      *
*     EMF TRaNsport related variables:                                 *
*                                                                      *
*        Lemagn = flag for magnetic field (set by Emfgeo)              *
*                                                                      *
*        Lrflbx = flag for reflection at boundary (set by Electr)      *
*                                                                      *
*        Xemfld = x-coordinate of the end point in the electro/magnetic*
*                 field                                                *
*        Yemfld = y-coordinate of the end point in the electro/magnetic*
*                 field                                                *
*        Zemfld = z-coordinate of the end point in the electro/magnetic*
*                 field                                                *
*                                                                      *
*        Uemfld = u-cosine of the end point in the electro/magnetic    *
*                 field                                                *
*        Vemfld = v-cosine of the end point in the electro/magnetic    *
*                 field                                                *
*        Wemfld = w-cosine of the end point in the electro/magnetic    *
*                 field                                                *
*                                                                      *
*        Dedxem = current de/dx for electrons/positrons                *
*        Demelf = energy loss/gain in EM fields                        *
*        Rndrfl = boundary reflection random number                    *
*                                                                      *
*        Irold  = old region                                           *
*                                                                      *
*        Irnew  = new region                                           *
*                                                                      *
*        Idisc  = geometry discard flag                                *
*                                                                      *
*        Intrck = flag for tracking initialization: it must be set to  *
*                 zero every time the trajectory direction has changed *
*                 from the previous call to Emfgeo                     *
*                                                                      *
*----------------------------------------------------------------------*
*
      LOGICAL LEMAGN, LRFLBX
      COMMON / EMFTRN / XEMFLD, YEMFLD, ZEMFLD, UEMFLD, VEMFLD, WEMFLD,
     &                  DEDXEM, DEMELF, EDEP  , RNDRFL, LEMAGN, LRFLBX,
     &                  IROLD , IRNEW , IDISC , INTRCK
      SAVE / EMFTRN /
    */
typedef struct {
  Double_t xemfld;
  Double_t yemfld;
  Double_t zemfld;
  Double_t uemfld;
  Double_t vemfld;
  Double_t wemfld;
  Double_t dedxem;
  Double_t demelf;
  Double_t edep;
  Double_t rndrfl;
  Int_t lemagn;
  Int_t lrflbx;
  Int_t irold;
  Int_t irnew;
  Int_t idisc;
  Int_t intrck;
} emftrnCommon;

#define EMFTRN COMMON_BLOCK(EMFTRN,emftrn)
COMMON_BLOCK_DEF(emftrnCommon,EMFTRN);
}
#endif
