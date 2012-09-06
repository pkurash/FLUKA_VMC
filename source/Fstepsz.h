#include "Fdimpar.h"
extern "C" {
/*
*$ CREATE STEPSZ.ADD
*COPY STEPSZ
*
*=== stepsz ===========================================================*
*
*----------------------------------------------------------------------*
*                                                                      *
*     Copyright (C) 1990-2010      by    Alfredo Ferrari & Paola Sala  *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*   Common stepsz for setting the minimum and maximum step sizes on a  *
*                 a region by region basis: very useful for vacuum re- *
*                 gions with magnetic filed and for saving time ( and  *
*                 accuracy ) with the new plc and lca algorithm in     *
*                 Emf and Fluka                                        *
*                                                                      *
*          W A R N I N G !!!!! At the moment implemented only for      *
*          electron and positron transport in Emf and for charged      *
*          particles transport in Fluka with the new multiple scat-    *
*          tering module!!!!!!                                         *
*                                                                      *
*                  created by A. Ferrari & P. Sala on 14-jan-1990      *
*                                                                      *
*          Last change   on  25-may-2010     by    Alfredo Ferrari     *
*                                                                      *
*          included in:                                                *
*                        fiprou                                        *
*                        flukam (main)                                 *
*                        kashea                                        *
*                        kaskad                                        *
*                        electr                                        *
*                        mageas                                        *
*                        magnew                                        *
*                        zeroin                                        *
*                                                                      *
*                        Ismbgn  = starting address (real*8, 0 index)  *
*                                  for minimum step size (cm)          *
*                        Isxbgn  = starting address (real*8, 0 index)  *
*                                  for maximum step size (cm)          *
*                                                                      *
*----------------------------------------------------------------------*
*
*  Statement functions:
      COMMON / STEPSZ / ISMBGN, ISXBGN
*/
typedef struct {
  Int_t ismbgn;
  Int_t isxbgn;
} stepszCommon;
#define STEPSZ COMMON_BLOCK(STEPSZ,stepsz)
COMMON_BLOCK_DEF(stepszCommon,STEPSZ);
 
}

