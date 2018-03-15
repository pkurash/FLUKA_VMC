#include <Riostream.h>

#include "TFluka.h"
#include "TFlukaCodes.h"
#include "TFlukaMCGeometry.h"
#include "Fdimpar.h"  //(DIMPAR) fluka include
#include "Ftrackr.h"  //(TRACKR) fluka common
#include "Fltclcm.h"  //(LTCLCM) fluka common
#include "Fopphst.h"  //(OPPHST) fluka common

#ifndef WIN32
# define bxdraw bxdraw_
#else
# define bxdraw BXDRAW
#endif


#include "TGeoManager.h"


extern "C" {
void bxdraw(Int_t& icode, Int_t& mreg, Int_t& newreg,
            Double_t& xsco, Double_t& ysco, Double_t& zsco)
{
    TFluka* fluka = (TFluka*) gMC;
    Int_t oldlttc = TRACKR.lt1trk; //LTCLCM.mlatm1;
    Int_t newlttc = LTCLCM.newlat;
    fluka->SetIcode((FlukaProcessCode_t)icode);
//    fluka->SetNewreg(newreg,newlttc);
    fluka->SetXsco(xsco);
    fluka->SetYsco(ysco);
    fluka->SetZsco(zsco);
    Int_t verbosityLevel = fluka->GetVerbosityLevel();
    Bool_t debug = (verbosityLevel>=3)?kTRUE:kFALSE;
    // nothing to do if particle is crossing a dummy region
    if (mreg   == fluka->GetDummyRegion() ||
        newreg == fluka->GetDummyRegion() ||
        oldlttc == TFlukaMCGeometry::kLttcVirtual ||
        newlttc == TFlukaMCGeometry::kLttcVirtual
        ) return;

//
// Double step for boundary crossing
//
    fluka->SetTrackIsNew(kFALSE); // has to be called BEFORE Stepping()
    if (mreg != fluka->GetDummyRegion() && newreg != fluka->GetDummyRegion()) {
	if (debug) printf("bxdraw (ex) \n");
	fluka->SetTrackIsExiting();
	fluka->SetCaller(kBXExiting);
	fluka->SetMreg(mreg,oldlttc);
	
	// check region lattice consistency (debug Ernesto)
	// *****************************************************
	Int_t nodeId;
	Int_t volId = fluka->CurrentVolID(nodeId);
	Int_t crtlttc = gGeoManager->GetCurrentNodeId()+1;
	if(debug && mreg != volId  && !gGeoManager->IsOutside()) {
	    std::cout << "  bxdraw:   track=" << TRACKR.ispusr[mkbmx2-1]<< " pdg=" << fluka->PDGFromId(TRACKR.jtrack)
		 << " icode=" << icode << " gNstep=" << fluka->GetNstep() << std::endl
		 << "               fluka   mreg=" << mreg << " oldlttc=" << oldlttc << " newreg=" << newreg << " newlttc=" << newlttc << std::endl
		 << "               TGeo   volId=" << volId << " crtlttc=" << crtlttc << std::endl
		 << "     common TRACKR   lt1trk=" << TRACKR.lt1trk << " lt2trk=" << TRACKR.lt2trk << std::endl
		 << "     common LTCLCM   newlat=" << LTCLCM.newlat << " mlatld=" <<  LTCLCM.mlatld << std::endl
		 << "                     mlatm1=" << LTCLCM.mlatm1 << " mltsen=" <<  LTCLCM.mltsen << std::endl
		 << "                     mltsm1=" << LTCLCM.mltsm1 << " mlattc=" << LTCLCM.mlattc << std::endl;
	    if( oldlttc == crtlttc ) std::cout << "   **************************** Exit *********************************" << std::endl;
	}
	// *****************************************************
	
	
	
	TVirtualMCStack* cppstack = fluka->GetStack();
	
	if (TRACKR.jtrack == -1) {
	    cppstack->SetCurrentTrack(OPPHST.louopp[OPPHST.lstopp]);
	} else {
	    cppstack->SetCurrentTrack( TRACKR.ispusr[mkbmx2-1] );
	}
	
	(TVirtualMCApplication::Instance())->Stepping();
    }
    if (newreg != fluka->GetDummyRegion()) {
	if (debug) printf("bxdraw (en) \n");
	fluka->SetCaller(kBXEntering);
	fluka->SetTrackIsEntering();
	if (fluka->GetDummyBoundary() == 1) fluka->SetDummyBoundary(2);
	fluka->SetMreg(newreg,newlttc);
	
	// check region lattice consistency (debug Ernesto)
	// *****************************************************
	Int_t nodeId;
	Int_t volId = fluka->CurrentVolID(nodeId);
	Int_t crtlttc = gGeoManager->GetCurrentNodeId()+1;
	if(debug && newreg != volId  && !gGeoManager->IsOutside()) {
	    std::cout << "  bxdraw:   track=" << TRACKR.ispusr[mkbmx2-1] << " pdg=" << fluka->PDGFromId(TRACKR.jtrack)
		 << " icode=" << icode << " gNstep=" << fluka->GetNstep() << std::endl
		 << "               fluka   mreg=" << mreg << " oldlttc=" << oldlttc << " newreg=" << newreg << " newlttc=" << newlttc << std::endl
		 << "               TGeo   volId=" << volId << " crtlttc=" << crtlttc << std::endl
		 << "     common TRACKR   lt1trk=" << TRACKR.lt1trk << " lt2trk=" << TRACKR.lt2trk << std::endl
		 << "     common LTCLCM   newlat=" << LTCLCM.newlat << " mlatld=" <<  LTCLCM.mlatld << std::endl
		 << "                     mlatm1=" << LTCLCM.mlatm1 << " mltsen=" <<  LTCLCM.mltsen << std::endl
		 << "                     mltsm1=" << LTCLCM.mltsm1 << " mlattc=" << LTCLCM.mlattc << std::endl;
	    if( newlttc == crtlttc ) std::cout << "   ******************************** Enter *****************************" << std::endl;
	}
	// *****************************************************
	
	TVirtualMCStack* cppstack = fluka->GetStack();
	if (TRACKR.jtrack == -1) {
	    cppstack->SetCurrentTrack(OPPHST.louopp[OPPHST.lstopp]);
	} else {
	    cppstack->SetCurrentTrack( TRACKR.ispusr[mkbmx2-1] );
	}
	
	(TVirtualMCApplication::Instance())->Stepping();
    }

} // end of bxdraw
} // end of extern "C"

