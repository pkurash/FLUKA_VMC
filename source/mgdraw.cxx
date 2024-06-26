#include <Riostream.h>
#include "TVirtualMCApplication.h"
#include "TVirtualMCStack.h"
#include "TFluka.h"
#include "TFlukaCodes.h"

// Fluka includes
#include "Fdimpar.h"  //(DIMPAR) 
#include "Fdblprc.h"  //(DBLPRC) 
#include "Ftrackr.h"  //(TRACKR) 
#include "Fopphst.h"  //(OPPHST) 
#include "Fflkstk.h"  //(FLKSTK) 
#include "Femftrn.h"  //(FEMFTRN)
#include "Fltclcm.h"  //(LTCLCM) 
#include "Fpaprop.h"  //(PAPROP) 
#include "Falldlt.h"  //(ALLDLT) 
#include "Fdpdxcm.h"  //(DPDXCM) 
#include "Fflkmat.h"  //(FLKMAT) 

#include "TGeoManager.h"

#ifndef WIN32
# define mgdraw mgdraw_
#else
# define mgdraw MGDRAW
#endif

extern "C" {
void mgdraw(Int_t& icode, Int_t& mreg)
{
    TFluka* fluka =  (TFluka*) gMC;
    if (mreg == fluka->GetDummyRegion()) return;
//
//  Make sure that stack has currrent track Id
//
    Int_t trackId = -1;
    TVirtualMCStack* cppstack = fluka->GetStack();
    
    if (TRACKR.jtrack == -1) {
        trackId = OPPHST.louopp[OPPHST.lstopp];
        if (trackId == 0) {
            trackId = FLKSTK.ispark[FLKSTK.npflka][mkbmx2-1];
        }
    } else {
        trackId = TRACKR.ispusr[mkbmx2-1];
    }
    
    Int_t verbosityLevel = fluka->GetVerbosityLevel();
    if (TRACKR.jtrack < -6) {
       // from -7 to -12 = "heavy" fragment
       // assing parent id
       // id < -6 was skipped in stuprf =>   if (kpart < -6) return;
       if (verbosityLevel >= 3) {
          std::cout << "mgdraw: (heavy fragment) jtrack < -6 =" << TRACKR.jtrack
               << " assign parent pdg=" << fluka->PDGFromId(TRACKR.ispusr[mkbmx2 - 3]) << std::endl;
       }
//       TRACKR.jtrack = TRACKR.ispusr[mkbmx2 - 3];
    }
    
    cppstack->SetCurrentTrack(trackId);
//
//    
    Int_t mlttc = TRACKR.lt1trk; // LTCLCM.mlatm1;
    fluka->SetMreg(mreg, mlttc);
    if ((icode == 4) && (TRACKR.ptrack == 0.)) {
      fluka->SetIcode(kKASHEAstopping);
    } else {
      fluka->SetIcode((FlukaProcessCode_t) icode);
    }
    fluka->SetCaller(kMGDRAW);

    Int_t nodeId;
    Int_t volId   = fluka->CurrentVolID(nodeId);
    Int_t crtlttc = gGeoManager->GetCurrentNodeId()+1;

    // check region lattice consistency (debug Ernesto)
    // *****************************************************
    if(verbosityLevel>=3 && mreg != volId  && !gGeoManager->IsOutside() ) {
       std::cout << "  mgdraw:   track=" << trackId << " pdg=" << fluka->PDGFromId(TRACKR.jtrack)
            << " icode=" << icode << " gNstep=" << fluka->GetNstep() << std::endl
            << "               fluka   mreg=" << mreg << " mlttc=" << mlttc << std::endl
            << "               TGeo   volId=" << volId << " crtlttc=" << crtlttc << std::endl
            << "     common TRACKR   lt1trk=" << TRACKR.lt1trk << " lt2trk=" << TRACKR.lt2trk << std::endl
            << "     common LTCLCM   newlat=" << LTCLCM.newlat << " mlatld=" <<  LTCLCM.mlatld << std::endl
            << "                     mlatm1=" << LTCLCM.mlatm1 << " mltsen=" <<  LTCLCM.mltsen << std::endl
            << "                     mltsm1=" << LTCLCM.mltsm1 << " mlattc=" << LTCLCM.mlattc << std::endl;
        if( mlttc == crtlttc ) std::cout << "   *************************************************************" << std::endl;
    }
    // *****************************************************

    
    Int_t med   = FLKMAT.medflk[0][mreg - 1];  // Medium
    Int_t msd   = DPDXCM.msdpdx[med  - 1];     // Iionisation model

    if (!TRACKR.ispusr[mkbmx2 - 2]) {
	if (verbosityLevel >= 3) {
	    std::cout << std::endl << "mgdraw: energy deposition for:" << trackId
		 << " icode=" << icode
		 << " pdg=" << fluka->PDGFromId(TRACKR.jtrack)
		 << " flukaid="<< TRACKR.jtrack
		 << " mreg=" << mreg
		 << " np  =" << ALLDLT.nalldl
		 << std::endl;
	         
	}
	  if ( FLKSTK.ispark[FLKSTK.npflka][mkbmx2 - 6] == 0) {
	    // first step of new particle
	    fluka->SetTrackIsNew(kTRUE);
	    fluka->SetCaller(kMGNewTrack);
	    if (fluka->UserStepping()) (TVirtualMCApplication::Instance())->Stepping();
	    FLKSTK.ispark[FLKSTK.npflka][mkbmx2 - 6]++;
	  }
	if (msd > 0) {
//
// Primary ionsiations
	    Int_t nprim = ALLDLT.nalldl;
	    if (nprim >= mxalld) {
		nprim = mxalld;
		Warning("mgdraw", "nprim > mxalld, nprim: %6d  pdg: %6d mreg %6d p %13.3f step %13.3f\n", 
			ALLDLT.nalldl, 
			fluka->PDGFromId(TRACKR.jtrack), 
			mreg, 
			TRACKR.ptrack, 
			TRACKR.ctrack);
	    }
	    fluka->PrimaryIonisationStepping(nprim);
	} else {
	    // Single step
	  fluka->SetCaller(kMGDRAW);
	  fluka->SetTrackIsNew(kFALSE);
	  if (fluka->UserStepping()) (TVirtualMCApplication::Instance())->Stepping();
	  FLKSTK.ispark[FLKSTK.npflka][mkbmx2 - 6]++;
	}
	
    } else {
        //
        // Tracking is being resumed after secondary tracking
        //
        if (verbosityLevel >= 3) {
            std::cout << std::endl << "mgdraw: resuming Stepping(): " << trackId << std::endl;
        }

        fluka->SetTrackIsNew(kTRUE);
        fluka->SetCaller(kMGResumedTrack);
        if (fluka->UserStepping()) (TVirtualMCApplication::Instance())->Stepping();
	FLKSTK.ispark[FLKSTK.npflka][mkbmx2 - 6]++;
        // Reset flag and stored values
        TRACKR.ispusr[mkbmx2 - 2] = 0;
        for (Int_t i = 0; i < 9; i++) TRACKR.spausr[i] = -1.;


        if (verbosityLevel >= 3) {
            std::cout << std::endl << " !!! I am in mgdraw - first Stepping() after resume: " << icode << std::endl;
            std::cout << " Track= " << trackId << " region = " << mreg << std::endl;
        }

        fluka->SetTrackIsNew(kFALSE);
        fluka->SetCaller(kMGDRAW);
	if (msd == 0) {
	    if (fluka->UserStepping()) (TVirtualMCApplication::Instance())->Stepping();
	} else {
	    Int_t nprim = ALLDLT.nalldl;
// Protection against nprim > mxalld
	    if (nprim >= mxalld) {
		nprim = mxalld;
		Warning("mgdraw", "nprim > mxalld, nprim: %6d  pdg: %6d mreg %6d p %13.3f step %13.3f\n", 
			ALLDLT.nalldl, 
			fluka->PDGFromId(TRACKR.jtrack), 
			mreg, 
			TRACKR.ptrack, 
			TRACKR.ctrack);
	    }
	    fluka->PrimaryIonisationStepping(nprim);
	} // primary ionisation switched on
    } // tracking resumed
    if (fluka->GetStoppingCondition()) {
      TRACKR.lpkill = kTRUE;
      EMFTRN.idisc = -1;
      fluka->ResetStoppingCondition();
    }
} // end of mgdraw
} // end of extern "C"

