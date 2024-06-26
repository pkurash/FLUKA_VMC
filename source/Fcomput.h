#ifndef FCOMPUT_H
#define FCOMPUT_H 

#include "cfortran.h"
#include "Rtypes.h"
extern "C" {
//*$ CREATE COMPUT.ADD
//*COPY COMPUT
/*
*=== comput ===========================================================*
*
*----------------------------------------------------------------------*
*                                                                      *
*     Copyright (C) 1994-2005      by         Alberto Fasso            *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*     include file: comput copy           created 23/08/94 by A.Fasso  *
*                                                                      *
*     Last change  on  09-nov-98   by   Alfredo Ferrari, CERN          *
*     included in the following subroutines or functions:              *
*                                                                      *
*                               bdtrns                                 *
*                               cmsppr                                 *
*                               dtimst                                 *
*                               echinp                                 *
*                               elsgrd                                 *
*                               epilog                                 *
*                               feeder                                 *
*                               flukam                                 *
*                               fluoin                                 *
*                               geogeo                                 *
*                               mgdraw                                 *
*                               ncdtrd                                 *
*                               nuscti                                 *
*                               pisgrd                                 *
*                               plotgm                                 *
*                               rsncli                                 *
*                               source                                 *
*                               usrbdx                                 *
*                               usrbin                                 *
*                               usrtrk                                 *
*                               usryld                                 *
*                               which                                  *
*                               xnbnls                                 *
*                               xnloan                                 *
*                               xsread                                 *
*                                                                      *
*     description of the common block(s) and variable(s)               *
*                                                                      *
*                                                                      *
*     /comput/ contains information about the computer used            *
*              and about the input file                                *
*         komput       = system (1=OpenVms,  2=ibm-vm,   3=ibm-mvs,    *
*                                4=cray,     5=unix-aix, 6=unix-hp,    *
*                                7=unix-sun, 8=DEC-unix, 9=Linux...)   *
*         Cpuspe       = computer speed with respect to IBM 370/168-3  *
*                        or to VAX 780/11 or to IBM RISC/6000 7012/370 *
*         Cpujob       = cpu limit (s) for the current job             *
*         Kinpnm       = last non blank character of Inpnam            *
*         Kpwdir       = last non blank character of Pwddir            *
*         Kfldir       = last non blank character of Hfldir            *
*         Khmdir       = last non blank character of Homdir            *
*         Mxftnu       = maximum fortran unit number allowed           *
*         Comptr       = model                                         *
*         Inpfil       = input file name (old VM way)                  *
*         Inpnam       = input file name (new Linux way)               *
*         Pwddir       = current work directory                        *
*         Hfldir       = home FLUKA directory                          *
*         Homdir       = user  home directory                          *
*         Hostnm       = host  name                                    *
*         Usrflk       = user  name                                    *
*         Grpflk       = group name                                    *
*                                                                      *
*----------------------------------------------------------------------*
*
*      CHARACTER COMPTR*50 , INPFIL*200, PWDDIR*200, HFLDIR*200,
*     &          HOMDIR*200, HOSTNM*200, USRFLK*200, GRPFLK*200,
*     &          INPNAM*200, CHINPF*256, HFPATH*200
*      COMMON / COMPUT / CPUSPE, CPUJOB, KOMPUT, KINPNM, KPWDIR, KFLDIR,
*     &                  KHMDIR, MXFTNU
*      COMMON / CHCMPT / COMPTR, INPFIL, PWDDIR, HFLDIR, HOMDIR, HOSTNM,
*     &                  USRFLK, GRPFLK, INPNAM, CHINPF, HFPATH
*      SAVE / COMPUT /
*      SAVE / CHCMPT /
*/
    typedef struct {
      Char_t comptr[50];
      Char_t inpfil[200];
      Char_t pwddir[200];
      Char_t hfldir[200];
      Char_t homdir[200];
      Char_t hostnm[200];
      Char_t usrflk[200];
      Char_t grpflk[200];
      Char_t inpnam[200];
      Char_t chinpf[256];
      Char_t hfpath[256];
    } chcmptCommon;
#define CHCMPT  COMMON_BLOCK(CHCMPT,chcmpt)
    COMMON_BLOCK_DEF(chcmptCommon,CHCMPT);
}

#endif
