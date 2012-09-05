#include "cfortran.h"
#include "Rtypes.h"

#include "Fdimpar.h"

extern "C" {
//*$ create souevt.add
//*copy souevt 
/* 
  *
*----------------------------------------------------------------------*
*                                                                      *
*     Copyright (C) 1996-2010      by    Alfredo Ferrari & Paola Sala  *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*     SOUrce EVenT:                                                    *
*                                                                      *
*     Created on 14 November 1996  by    Alfredo Ferrari & Paola Sala  *
*                                                   Infn - Milan       *
*                                                                      *
*     Last change on  17-Oct-10    by    Alfredo Ferrari               *
*                                                                      *
*          X,Y,Zsoevt(i) = position      of the i_th source particle   *
*          TX,Y,Zsoev(i) = direction     of the i_th source particle   *
*              Wtsoev(i) = weight        of the i_th source particle   *
*              Pmsoev(i) = momentum      of the i_th source particle   *
*              Tksoev(i) = kin. energy   of the i_th source particle   *
*              Agsoev(i) = age           of the i_th source particle   *
*              Aksoev(i) = Kaon ampl.    of the i_th source particle   *
*              Rdsoev(i) = Rad. delay    of the i_th source particle   *
*              Dcsoev(i) = De-ch. length of the i_th source particle   *
*            Ussoev(j,i) = user var.     of the i_th source particle   *
*              Ijsoev(i) = identity      of the i_th source particle   *
*              Igsoev(i) = group n.      of the i_th source particle   *
*              Nrsoev(i) = region        of the i_th source particle   *
*              Nlsoev(i) = lattice       of the i_th source particle   *
*              Lrsoev(i) = Rad.dec. flag of the i_th source particle   *
*              Lcsoev(i) = Channel. flag of the i_th source particle   *
*              Losoev(i) = user flag     of the i_th source particle   *
*            Iusoev(j,i) = user flags    of the i_th source particle   *
*                Npsoev  = number of the source particles              *
*                                                                      *
*----------------------------------------------------------------------*
*
      PARAMETER ( MXSOEV = 100 )
      LOGICAL LRSOEV, LCSOEV
      COMMON / SOUEVT / XSOEVT (MXSOEV), YSOEVT (MXSOEV),
     &                  ZSOEVT (MXSOEV), TXSOEV (MXSOEV),
     &                  TYSOEV (MXSOEV), TZSOEV (MXSOEV),
     &                  TXPSOV (MXSOEV), TYPSOV (MXSOEV),
     &                  TZPSOV (MXSOEV), WTSOEV (MXSOEV),
     &                  PMSOEV (MXSOEV), TKSOEV (MXSOEV),
     &                  AGSOEV (MXSOEV), AKSOEV (MXSOEV),
     &                  RDSOEV (MXSOEV), DCSOEV (MXSOEV),
     &                  USSOEV (MKBMX1,MXSOEV),
     &                  IJSOEV (MXSOEV), IGSOEV (MXSOEV),
     &                  NRSOEV (MXSOEV), NLSOEV (MXSOEV),
     &                  LRSOEV (MXSOEV), LCSOEV (MXSOEV),
     &                  LOSOEV (MXSOEV),
     &                  IUSOEV (MKBMX2,MXSOEV), NPSOEV
      SAVE / SOUEVT /
*/ 
const Int_t mxsoev = 100;

typedef struct {
   Double_t xsoevt[mxsoev];
   Double_t ysoevt[mxsoev];
   Double_t zsoevt[mxsoev];
   Double_t txsoev[mxsoev];
   Double_t tysoev[mxsoev];
   Double_t tzsoev[mxsoev];
   Double_t txpsov[mxsoev];
   Double_t typsov[mxsoev];
   Double_t tzpsov[mxsoev];
   Double_t wtsoev[mxsoev];
   Double_t pmsoev[mxsoev];
   Double_t tksoev[mxsoev];
   Double_t agsoev[mxsoev];
   Double_t aksoev[mxsoev];
   Double_t ussoev[mkbmx1][mxsoev];
   Int_t    ijsoev[mxsoev];
   Int_t    igsoev[mxsoev];
   Int_t    nrsoev[mxsoev];
   Int_t    nlsoev[mxsoev];
   Int_t    lrsoev[mxsoev];   
   Int_t    lcsoev[mxsoev];   
   Int_t    losoev[mxsoev];
   Int_t    iusoevo[mkbmx2][mxsoev];
   Int_t    npsoev;

} souevtCommon;
#define SOUEVT COMMON_BLOCK(SOUEVT,souevt)
COMMON_BLOCK_DEF(souevtCommon,SOUEVT);
}
