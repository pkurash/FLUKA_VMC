#include "cfortran.h"
#include "Rtypes.h"

#include "Fdimpar.h"

extern "C" {
/*$ CREATE DPDXCM.ADD
*COPY DPDXCM
*
*=== dpdxcm ===========================================================*
*
*----------------------------------------------------------------------*
*                                                                      *
*     Copyright (C) 1989-2006         by        Alfredo Ferrari        *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*     Include file: dpdxcm  (DP/DX CoMmon)                             *
*                                                                      *
*     Created  on  10 february 1991   by        Alfredo Ferrari        *
*                                                INFN - Milan          *
*                                                                      *
*     Last change on  21-may-06       by        Alfredo Ferrari        *
*                                                                      *
*     Included in the following routines:                              *
*                                                                      *
*              blockmvax/bdtrns.f                                      *
*              dedxmvax/dedsdv.f                                       *
*              dedxmvax/dedx.f                                         *
*              dedxmvax/dedxfl.f                                       *
*              dedxmvax/deltad.f                                       *
*              dedxmvax/deltar.f                                       *
*              dedxmvax/deltas.f                                       *
*              dedxmvax/delthr.f                                       *
*              dedxmvax/delths.f                                       *
*              dedxmvax/dpdx.f                                         *
*              dedxmvax/dpdxio.f                                       *
*              dedxmvax/enion.f                                        *
*              dedxmvax/enionf.f                                       *
*              dedxmvax/gdedxc.f                                       *
*              dedxmvax/heabre.f                                       *
*              dedxmvax/hosufl.f                                       *
*              dedxmvax/hvbrem.f                                       *
*              dedxmvax/hvpair.f                                       *
*              dedxmvax/t0zffc.f                                       *
*              elsmvax/sigtab.f                                        *
*              emfmvax/ededxf.f                                        *
*              emfmvax/emenio.f                                        *
*              emfmvax/emfin.f                                         *
*              emfmvax/emfret.f                                        *
*              emfmvax/emfsco.f                                        *
*              emfmvax/emfstp.f                                        *
*              emfmvax/pdedxf.f                                        *
*              kaskadmvax/hmsnsc.f                                     *
*              kaskadmvax/kashea.f                                     *
*              kaskadmvax/kaskad.f                                     *
*              kaskadmvax/mulhad.f                                     *
*              kaskadmvax/omegah.f                                     *
*              kaskadmvax/sgttot.f                                     *
*              kaskadmvax/stepop.f                                     *
*              mainmvax/deflts.f                                       *
*              mainmvax/dltcrd.f                                       *
*              mainmvax/matcrd.f                                       *
*              mainmvax/zeroin.f                                       *
*                                                                      *
*
*         Dedxmp (i,m) = restricted (up to Tmxmip(m)) MIP dE/dx        *
*                        (GeV/cm) for particle type i and medium m     *
*         Tmxmip (i,m) = maximum secondary electron energy (GeV) used  *
*                        when computing Dedxmp(i,m),  for medium m     *
*           Avionp (m) = average ionization potential (eV) of medium m *
*           Ccster (m) = Sternheimer cbar   parameter for medium m     *
*           X0ster (m) = Sternheimer x0     parameter for medium m     *
*           Xester (m) = Sternheimer x1     parameter for medium m     *
*           Amster (m) = Sternheimer m      parameter for medium m     *
*           Aaster (m) = Sternheimer a      parameter for medium m     *
*           D0ster (m) = Sternheimer delta0 parameter for medium m     *
*           Aviont (m) = auxiliary ionization potential of medium m    *
*           T0dpdx (m) = delta ray production threshold of medium m    *
*                        (all particle but e+/e-)                      *
*           Tedpdx (m) = delta ray production threshold of medium m    *
*                        (electrons and positrons)                     *
*           Gaspfl (m) = pressure (atm) if a gas                       *
*           Pthrmx     = maximum momentum of the tabulations           *
*           Anpicm (m) = average number of primary ionization per cm   *
*                        for a mip for medium m (at NTP for a gas)     *
*           Ansicm (m) = average number of secondary ionization per cm *
*                        for a mip for medium m (at NTP for a gas)     *
*           Frstip (m) = first ionization potential for medium m (GeV) *
*           Aenioc (m) = average energy spent per ion couple in medium *
*                        m (GeV)                                       *
*           Faltmt (m) = density modifying factor for a possible alt-  *
*                        ernate material for medium m                  *
*            Ijdpdx(i) = index translation from (paprop) i_th particle *
*                        index to dp/dx j_th particle index            *
*            Kwdpdx(m) = index of the material in the pre-defined      *
*                        I, Sternheimer, "known" compounds, arrays     *
*                        for the m_th medium                           *
*          Kdpdxt(j,m) = total dp/dx tabulation pointer for the j_th   *
*                        dp/dx particle in the m_th medium             *
*        Ndpdxt(k,j,m) = nuclear and NIEL dp/dx tabulation pointer for *
*                        the j_th dp/dx particle in the m_th medium,   *
*                        k=1 -> nuclear,                               *
*                        k=2 -> NIEL unrestricted,                     *
*                        k=3 -> NIEL restricted,                       *
*                        k=4 -> DPA  restricted  
*           Maltmt (m) = alternate material for medium m               *
*           Msdpdx (m) = possible "special material" flag for medium m *
*                        0: no special treatment                       *
*                        i>0: primary ionization production with i_th  *
*                             (i=1,2,3,4) model inside ..dedxf.. rout- *
*                             ines with recording of the selected val- *
*                             ues activated                            *
*               Iazmdp = A x 100 + Z x 100000 + m x 10000000 of the ion*
*                        whose dE/dx is tabulated                      *
*           Liopos (m) = (primary) ionization positions requested for  *
*                        medium m                                      *
*           Lsecio (m) = secondary ionizations requested for medium m  *
*               Lncdxx = flag for accounitng for nuclear stopping power*
*               Lzl1bk = flag for accoutning for zL1  (Barkas) correc- *
*                        tion term                                     *
*               Lz2l2b = flag for accounting for z^2L2 (Bloch) correc- *
*                        tion term                                     *
*               Lhmott = flag for accounting for Mott corrections in   *
*                        computing heavy ion stopping power            *
*                                                                      *
*----------------------------------------------------------------------*
*
      PARAMETER ( MNDPDX = 50 )
      PARAMETER ( RMDPDX = 1.15D+00 )
      PARAMETER ( DPDXR1 = 0.15D+00 )
      PARAMETER ( DPDXR2 = 0.70D+00 )
      PARAMETER ( ERDEDX = 0.15D+00 * 0.15D+00 )
      PARAMETER ( MDPDXH =  4 )
*  "MIP" related parameters:
      PARAMETER ( ETAMIP = THRTHR )
      PARAMETER ( BETMIP = 0.9486832980505138D+00 )
      PARAMETER ( GAMMIP = ETAMIP / BETMIP )
      PARAMETER ( TAUMIP = GAMMIP - ONEONE )
      PARAMETER ( GMIPSQ = GAMMIP * GAMMIP )
      PARAMETER ( BMIPSQ = BETMIP * BETMIP )
*  Toln10 = 2 x log (10)
      PARAMETER ( TOLN10 = 4.605170185988091 D+00 )
*
    COMMON / DPDXCM / P0DPDX (MPDPDX,MXXMDF), P1DPDX (MPDPDX,MXXMDF),
     &                  DEDXMP (-2:MPDPDX,MXXMDF),
     &                  TMXMIP (-2:MPDPDX,MXXMDF),
     &                  TMDPDX (MXXMDF), T0DPDX (MXXMDF),
     &                  TEDPDX (MXXMDF), D0DPDX (MXXMDF),
     &                  AVIONP (MXXMDF), RHORFL (MXXMDF),
     &                  GASPFL (MXXMDF), CCSTER (MXXMDF),
     &                  AMSTER (MXXMDF), XOSTER (MXXMDF),
     &                  XESTER (MXXMDF), AASTER (MXXMDF),
     &                  D0STER (MXXMDF), AVIONT (MXXMDF),
     &                  ETDPDX (MXXMDF), ALMASS (MPDPDX), PTHRMX,
     &                  FRSTIP (MXXMDF), ANPICM (MXXMDF),
     &                  AENIOC (MXXMDF), ANSICM (MXXMDF),
     &                  FALTMT (MXXMDF), MALTMT (MXXMDF),
     &                  MSDPDX (MXXMDF), NBDPDX (MXXMDF),
     &                  KDPDXT   (MPDPDX,MXXMDF), KWDPDX (MXXMDF),
     &                  NDPDXT (4,MPDPDX,MXXMDF), IAZMDP,
     &                  LDELTA (MXXMDF), LPDETB (MXXMDF),
     &                  LIOPOS (MXXMDF), LSECIO (MXXMDF),
     &                  IJDPDX (-6:NALLWP), LETFUN, LHVNFF, LNCDDX,
     &                  LZL1BK, LZ2L2B, LHMOTT
*/
    const Int_t     mndpdx = 50;
    const Double_t  rmdpdx = 1.15e0;
    const Double_t  dpdxr1 = 0.15e0;
    const Double_t  dpdxr2 = 0.70e0;
    const Double_t  erdedx = 0.15e0 * 0.15e0;
    const Int_t     mdpdxh = 4;
  // "MIP" related parameters    
    const Double_t  etamip = thrthr;
    const Double_t  betmip = 0.9486832980505138e+00; 
    const Double_t  gammip = etamip / betmip;
    const Double_t  taumip = gammip - oneone;
    const Double_t  gmipsq = gammip * gammip;
    const Double_t  bmipsq = betmip * betmip;
  //  Toln10 = 2 x log (10)
    const Double_t  toln10 = 4.605170185988091e+00;
    typedef struct {
	Double_t p0dpdx [mxxmdf][mpdpdx];
	Double_t p1dpdx [mxxmdf][mpdpdx];
        Double_t dedxmp [mxxmdf][mpdpdx +3];
        Double_t tmxmip [mxxmdf][mpdpdx +3];
	Double_t tmdpdx [mxxmdf];
	Double_t t0dpdx [mxxmdf];
	Double_t tedpdx [mxxmdf];
	Double_t d0dpdx [mxxmdf];
	Double_t avionp [mxxmdf];
	Double_t rhorfl [mxxmdf];
	Double_t gaspfl [mxxmdf];
	Double_t ccster [mxxmdf];
	Double_t amster [mxxmdf];
	Double_t xoster [mxxmdf];
	Double_t xester [mxxmdf];
	Double_t aaster [mxxmdf];
	Double_t d0ster [mxxmdf];
	Double_t aviont [mxxmdf];
	Double_t etdpdx [mxxmdf];
	Double_t almass [mpdpdx];
        Double_t pthrmx;
	Double_t frstip [mxxmdf];
	Double_t anpicm [mxxmdf];
        Double_t aenioc [mxxmdf]; 
        Double_t ansicm [mxxmdf];      
	Double_t faltmt [mxxmdf];
	Int_t    maltmt [mxxmdf];
	Int_t    msdpdx [mxxmdf];
	Int_t    nbdpdx [mxxmdf];
	Int_t    kdpdxt [mxxmdf][mpdpdx];
        Int_t    kwdpdx [mxxmdf];
        Int_t    ndpdxt [mxxmdf][mpdpdx][4];
        Int_t    iazmdp;
	Int_t    ldelta [mxxmdf];
	Int_t    lpdetb [mxxmdf];
        Int_t    liopos [mxxmdf];
        Int_t    lsecio [mxxmdf];
	Int_t    ijdpdx [nallwp + 7];
	Int_t    letfun;
        Int_t    lhvnff;
        Int_t    lncddx; 
        Int_t    lzl1bk;
        Int_t    lz2l2b;
        Int_t    lhmott;
    } dpdxcmCommon;
#define DPDXCM COMMON_BLOCK(DPDXCM,dpdxcm)
COMMON_BLOCK_DEF(dpdxcmCommon, DPDXCM);
}
