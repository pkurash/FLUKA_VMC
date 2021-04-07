#ifndef FLTCLCM_H
#define FLTCLCM_H

#include "cfortran.h"
#include "Rtypes.h"

extern "C" {
//*$ create ltclcm.add
//*copy ltclcm
//*
//*=== ltclcm ===========================================================*
//*
//*----------------------------------------------------------------------*
//*                                                                      *
//*     lattice cell common:                                             *
//*                                                                      *
//*     created on 09 december 1993  by    alfredo ferrari & paola sala  *
//*                                                   infn - milan       *
//*                                                                      *
//*     last change on 10-dec-93     by    alfredo ferrari               *
//*                                                                      *
//*                                                                      *
//*----------------------------------------------------------------------*
//*

typedef struct {
   Long64_t    mlattc;
   Long64_t    newlat;
   Long64_t    mlatld;
   Long64_t    mlatm1;
   Long64_t    mltsen;
   Long64_t    mltsm1;
} ltclcmCommon;
#define LTCLCM COMMON_BLOCK(LTCLCM,ltclcm)
COMMON_BLOCK_DEF(ltclcmCommon,LTCLCM);
}

#endif
