/*
*=== caslim ===========================================================*
*
*----------------------------------------------------------------------*
*                                                                      *
*     New version of Caslim for Fluka89-20xy                           *
*                                                                      *
*     Created on 20 september 1989  by   Alfredo Ferrari & Paola Sala  *
*                                                   Infn - Milan       *
*                                                                      *
*                                                                      *
*                                                                      *
*     /caslim/ is needed to decide when to stop the run                *
*        Trnlim = if cpu-time-left<tlim the run will be ended          *
*        Tpmean = is the average time needed for the following         *
*                 of one beam particle                                 *
*        Tprmax = is the maximum time needed for the following         *
*                 of one beam particle                                 *
*        Trntot = the cumulative time needed to follow the beam        *
*                 particles                                            *
*        Ncases = maximum number of beam particles to be followed      *
*                 modulo 1,000,000,000)                                *
*        Mcases = maximum number of beam particles to be followed      *
*                 in excess of 1,000,000,000, divided by 1,000,000,000 *
*        Ncase  = current number of beam particles followed (modulo    *
*                 1,000,000,000)                                       *
*        Mcase  = current number of beam particles followed in excess  *
*                 of 1,000,000,000, divided by 1,000,000,000           *
*        Nsouit = number of source iterations                          *
*        Ncoinc = flag used by the detect option to know if the ncase  *
*                 particle has or has not to be considered in coinci-  *
*                 dence with the previous one (if they have the same   *
*                 ncoinc/mcoinc they belong to the same event)         *
*        Mcoinc = flag as ncoinc, accounting for Ncase > 1,000,000,000 *
*        Lpseed = if .true. seeds will be printed for any history      *
*        Levtdt = if .true. a few data will be printed at each history *
*        Lcrrfl = if .true. rfluka.stop must be created and the run    *
*                 stopped                                              *
*                                                                      *
*----------------------------------------------------------------------*
*
      LOGICAL LPSEED, LEVTDT, LCRRFL
      COMMON / CASLIM / TRNLIM, TPMEAN, TPRMAX, TRNTOT, MCASES, NCASES,
     &                  NCASE , MCASE , NSOUIT, NCOINC, MCOINC, LPSEED,
     &                  LEVTDT, LCRRFL
      SAVE / CASLIM /
*/
typedef struct {
  Double_t trnlim;
  Double_t tpmean;
  Double_t tprmax;
  Double_t trntot;
  Int_t    mcases;
  Int_t    ncases;
  Int_t    ncase;
  Int_t    mcase;
  Int_t    nsouit;
  Int_t    ncoinc;
  Int_t    mcoinc;
  Int_t    lpseed;
  Int_t    levtdt;
  Int_t    lcrrfl;
    } caslimCommon;
#define CASLIM COMMON_BLOCK(CASLIM, caslim)
    COMMON_BLOCK_DEF(caslimCommon,CASLIM);


