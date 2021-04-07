#include "cfortran.h"
#include "Rtypes.h"

#include "Fdimpar.h"


extern "C" {
  
/*
*                                                                      *
*=== trackr ===========================================================*
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*     Copyright (C) 1990-2008           by   Alfredo Ferrari           *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*     TRACKs Recording       by  Alfredo Ferrari, INFN - Milan         *
*                                                                      *
*     last change      18 July 2008     by   Alfredo Ferrari           *
*                                                                      *
*            included in :                                             *
*                          bdnopt                                      *
*                          crnkvp                                      *
*                          dedx                                        *
*                          delthr                                      *
*                          doeimb                                      *
*                          dohimb                                      *
*                          doiosp                                      *
*                          donimb                                      *
*                          estprf                                      *
*                          electr                                      *
*                          em2fls                                      *
*                          emdedx                                      *
*                          emfgeo                                      *
*                          emfsco                                      *
*                          emnwnp                                      *
*                          eventv                                      *
*                          evxtes                                      *
*                          fkbirk                                      *
*                          flnwst                                      *
*                          kasemf                                      *
*                          kaskad                                      *
*                          kashea                                      *
*                          kasneu                                      *
*                          kasoph                                      *
*                          kasray                                      *
*                          geoden                                      *
*                          geofar                                      *
*                          geomag                                      *
*                          geomtr                                      *
*                          geonor                                      *
*                          lbxrfl                                      *
*                          mageas                                      *
*                          magnew                                      *
*                          photfl                                      *
*                          photon                                      *
*                          propph                                      *
*                          prtstp                                      *
*                          scntlp                                      *
*                          stprnc                                      *
*                          usrsco                                      *
*                          usrsrn                                      *
*                          zeroin                                      *
*                                                                      *
*          Ntrack = number of track segments                           *
*          Mtrack = number of energy deposition events along the track *
*   0 < i < Ntrack                                                     *
*          Xtrack = end x-point of the ith track segment               *
*          Ytrack = end y-point of the ith track segment               *
*          Ztrack = end z-point of the ith track segment               *
*   1 < i < Ntrack                                                     *
*          Ttrack = length of the ith track segment                    *
*   1 < j < Mtrack                                                     *
*          Dtrack = energy deposition of the jth deposition event      *
*          Dptrck = momentum loss of the jth deposition event          *
*                                                                      *
*          Jtrack = identity number of the particle: for recoils or    *
*                   kerma deposition it can be outside the allowed     *
*                   particle id range, assuming values like:           *
*                     208: "heavy" recoil                              *
*                     211: EM below threshold                          *
*                     308: low energy neutron kerma                    *
*                   in those cases the id of the particle originating  *
*                   the interaction is saved inside J0trck (which othe-*
*                   rwise is zero)                                     *
*          J0trck = see above                                          *
*          Ifltrk = flag used for internal debugging (trying to solve  *
*                   possible residual issues with Mgdraw driven        *
*                   quenching)                                         *
*          Etrack = total energy of the particle                       *
*          Ptrack = momentum of the particle (not always defined, if   *
*                 < 0 must be obtained from Etrack)                    *
*      Cx,y,ztrck = direction cosines of the current particle          *
*      Cx,y,ztrpl = polarization cosines of the current particle       *
*          Wtrack = weight of the particle                             *
*          Wscrng = scoring weight: it can differ from Wtrack if some  *
*                   biasing techniques are used (for example inelastic *
*                   interaction length biasing)                        *
*          Ctrack = total curved path                                  *
*          Cmtrck = cumulative curved path since particle birth        *
*          Zfftrk = <Z_eff> of the particle                            *
*          Zfrttk = actual Z_eff of the particle                       *
*          Atrack = age of the particle                                *
*          Akshrt = Kshrt amplitude for K0/K0bar                       *
*          Aklong = Klong amplitude for K0/K0bar                       *
*          Wninou = neutron algebraic balance of interactions (both    *
*                   for "high" energy particles and "low" energy       *
*                   neutrons)                                          *
*          Spausr = user defined spare variables for the current       *
*                   particle                                           *
*          Sttrck = macroscopic total cross section for low energy     *
*                   neutron collisions                                 *
*          Satrck = macroscopic absorption cross section for low energy*
*                   neutron collisions (it can be negative for Pnab>1) *
*          Tkniel = fraction of energy deposition going into NIEL      *
*          Tkedpa = fraction of energy deposition going into DPAs      *
*          Ktrack = if > 0 neutron group of the particle (neutron)     *
*                                                                      *
*          Ntrack > 0, Mtrack > 0 : energy loss distributed along the  *
*                                   track                              *
*          Ntrack > 0, Mtrack = 0 : no energy loss along the track     *
*          Ntrack = 0, Mtrack = 0 : local energy deposition (the       *
*                                   value and the point are not re-    *
*                                   corded in Trackr)                  *
*          Mmtrck = flag recording the material index for low energy   *
*                   neutron collisions                                 *
*          Lt1trk = initial lattice cell of the current track          *
*                  (or lattice cell for a point energy deposition)     *
*          Lt2trk = final   lattice cell of the current track          *
*          Ihspnt = current geometry history pointer (not set if -1)   *
*          Ltrack = flag recording the generation number               *
*          Llouse = user defined flag for the current particle         *
*          Ispusr = user defined spare flags for the current particle  *
*          Lfsssc = logical flag for inelastic interactions ending with*
*                   fission (used also for low energy neutrons)        *
*          Lpkill = logical (user) flag for sudden particle death      *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
      PARAMETER ( MXTRCK = 2500 )
      LOGICAL LFSSSC, LPKILL
      COMMON / TRACKR /  XTRACK ( 0:MXTRCK ), YTRACK ( 0:MXTRCK ),
     &                   ZTRACK ( 0:MXTRCK ), TTRACK   ( MXTRCK ),
     &                   DTRACK   ( MXTRCK ), DPTRCK ( 3,MXTRCK ),
     &                   ETRACK, PTRACK, CXTRCK, CYTRCK, CZTRCK, WTRACK,
     &                   CXTRPL, CYTRPL, CZTRPL, ZFFTRK, ZFRTTK, ATRACK,
     &                   CTRACK, CMTRCK, AKSHRT, AKLONG, WSCRNG, WNINOU,
     &                   SPAUSR(MKBMX1), STTRCK, SATRCK, TKNIEL, TKEDPA,
     &                   NTRACK, MTRACK, IFLTRK, JTRACK, J0TRCK, KTRACK,
     &                   MMTRCK, LT1TRK, LT2TRK, IHSPNT, LTRACK, LLOUSE,
     &                   ISPUSR(MKBMX2), LFSSSC, LPKILL
      EQUIVALENCE ( SPAUSE, SPAUSR (1) )
      EQUIVALENCE ( ISPUSE, ISPUSR (1) )
      SAVE / TRACKR /
*/
    
const Int_t mxtrck = 5000;

typedef struct {
    Double_t xtrack[mxtrck+1];
    Double_t ytrack[mxtrck+1];
    Double_t ztrack[mxtrck+1];
    Double_t ttrack[mxtrck];
    Double_t dtrack[mxtrck];
    Double_t dptrck[mxtrck][3];
    Double_t etrack;
    Double_t ptrack;
    Double_t cxtrck;
    Double_t cytrck;
    Double_t cztrck;
    Double_t wtrack;
    Double_t cxtrpl;
    Double_t cytrpl;
    Double_t cztrpl;
    Double_t zfftrk;
    Double_t zfrttk;
    Double_t atrack;
    Double_t ctrack;
    Double_t cmtrck;
    Double_t akshrt;
    Double_t aklong;
    Double_t wscrng;
    Double_t wninou;
    Double_t spausr[mkbmx1];
    Double_t sttrck;
    Double_t satrck;
    Double_t tkniel;
    Double_t tkrnie;
    Double_t tkedpa;
    Double_t wcinou;
    Double_t aftrck;
    Double_t eptrck;
    Int_t    ntrack;
    Int_t    mtrack;
    Int_t    ifltrk;
    Int_t    jtrack;
    Int_t    j0trck;
    Int_t    ktrack;
    Int_t    iftrck;
    Int_t    lftrck;
    Int_t    iptrck;
    Int_t    mmtrck;
    Long64_t lt1trk;
    Long64_t lt2trk;
    Long64_t ihspnt;
    Int_t    ltrack;
    Int_t    llouse;
    Int_t    iprodc;
    Int_t    iaztrk;
    Int_t    ispusr[mkbmx2];
    Int_t    lfsssc;
    Int_t    lpkill;
} trackrCommon;
#define TRACKR COMMON_BLOCK(TRACKR,trackr)
COMMON_BLOCK_DEF(trackrCommon,TRACKR);
//static union { Double_t spause; Double_t spausr[0];};
//static union { Int_t    ispuse; Int_t    ispusr[0];};
}
