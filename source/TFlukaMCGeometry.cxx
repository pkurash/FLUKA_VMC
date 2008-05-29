/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

// $Id$

// Class TFlukaMCGeometry
// --------------------
// Implementation of the TVirtualMCGeometry interface
// for defining and using TGeo geometry with FLUKA.
// This allows the FLUKA MonteCarlo to run with the TGeo 
// geometrical modeller
// Author: Andrei Gheata 10/07/2003

#include "Riostream.h"
#include "TList.h"
#include "TCallf77.h"
#include "TFluka.h"
#include "TSystem.h"
#include "TFlukaMCGeometry.h"
#include "TFlukaConfigOption.h"
#include "TGeoManager.h" 
#include "TGeoVolume.h" 
#include "TObjString.h"
#include "Fsourcm.h"
#include "Ftrackr.h"
#include "Fstepsz.h"       //(STEPSZ) fluka common

#ifndef WIN32 
# define idnrwr idnrwr_
# define g1wr   g1wr_
# define g1rtwr g1rtwr_
# define conhwr conhwr_
# define inihwr inihwr_
# define jomiwr jomiwr_
# define lkdbwr lkdbwr_
# define lkfxwr lkfxwr_
# define lkmgwr lkmgwr_
# define lkwr lkwr_
# define magfld magfld_
# define nrmlwr nrmlwr_
# define rgrpwr rgrpwr_
# define isvhwr isvhwr_

#else

# define idnrwr IDNRWR
# define g1wr   G1WR
# define g1rtwr G1RTWR
# define conhwr CONHWR
# define inihwr INIHWR
# define jomiwr JOMIWR
# define lkdbwr LKDBWR
# define lkfxwr LKFXWR
# define lkmgwr LKMGWR
# define lkwr   LKWR
# define magfld MAGFLD
# define nrmlwr NRMLWR
# define rgrpwr RGRPWR
# define isvhwr ISVHWR

#endif

//____________________________________________________________________________ 
extern "C" 
{
   //
   // Prototypes for FLUKA navigation methods
   //
   Int_t type_of_call idnrwr(const Int_t & /*nreg*/, const Int_t & /*mlat*/);
   void  type_of_call   g1wr(Double_t & /*pSx*/, Double_t & /*pSy*/, Double_t & /*pSz*/, 
                             Double_t * /*pV*/,  Int_t & /*oldReg*/ , const Int_t & /*oldLttc*/, Double_t & /*propStep*/,
                             Int_t & /*nascFlag*/, Double_t & /*retStep*/, Int_t & /*newReg*/,
                                  Double_t & /*saf*/, Int_t & /*newLttc*/, Int_t & /*LttcFlag*/,
                             Double_t *s /*Lt*/, Int_t * /*jrLt*/);
   
   void  type_of_call g1rtwr();
   void  type_of_call conhwr(Int_t & /*intHist*/, Int_t & /*incrCount*/);
   void  type_of_call inihwr(Int_t & /*intHist*/);
   void  type_of_call jomiwr(const Int_t & /*nge*/, const Int_t & /*lin*/, const Int_t & /*lou*/,
                             Int_t & /*flukaReg*/);
   void  type_of_call lkdbwr(Double_t & /*pSx*/, Double_t & /*pSy*/, Double_t & /*pSz*/,
                             Double_t * /*pV*/, const Int_t & /*oldReg*/, const Int_t & /*oldLttc*/,
                             Int_t & /*flagErr*/, Int_t & /*newReg*/, Int_t & /*newLttc*/);
   void  type_of_call lkfxwr(Double_t & /*pSx*/, Double_t & /*pSy*/, Double_t & /*pSz*/,
                             Double_t * /*pV*/, const Int_t & /*oldReg*/, const Int_t & /*oldLttc*/,
                             Int_t & /*flagErr*/, Int_t & /*newReg*/, Int_t & /*newLttc*/);
   void  type_of_call lkmgwr(Double_t & /*pSx*/, Double_t & /*pSy*/, Double_t & /*pSz*/,
                             Double_t * /*pV*/, const Int_t & /*oldReg*/, const Int_t & /*oldLttc*/,
                                       Int_t & /*flagErr*/, Int_t & /*newReg*/, Int_t & /*newLttc*/);
   void  type_of_call   lkwr(Double_t & /*pSx*/, Double_t & /*pSy*/, Double_t & /*pSz*/,
                             Double_t * /*pV*/, const Int_t & /*oldReg*/, const Int_t & /*oldLttc*/,
                                  Int_t & /*flagErr*/, Int_t & /*newReg*/, Int_t & /*newLttc*/);
//   void  type_of_call magfld(const Double_t & /*pX*/, const Double_t & /*pY*/, const Double_t & /*pZ*/,
//                             Double_t & /*cosBx*/, Double_t & /*cosBy*/, Double_t & /*cosBz*/, 
//                             Double_t & /*Bmag*/, Int_t & /*reg*/, Int_t & /*idiscflag*/);        
   void  type_of_call nrmlwr(Double_t & /*pSx*/, Double_t & /*pSy*/, Double_t & /*pSz*/,
                             Double_t & /*pVx*/, Double_t & /*pVy*/, Double_t & /*pVz*/,
                                  Double_t * /*norml*/, const Int_t & /*oldReg*/,
                                  const Int_t & /*newReg*/, Int_t & /*flagErr*/);
   void  type_of_call rgrpwr(const Int_t & /*flukaReg*/, const Int_t & /*ptrLttc*/, Int_t & /*g4Reg*/,
                             Int_t * /*indMother*/, Int_t * /*repMother*/, Int_t & /*depthFluka*/);
   Int_t type_of_call isvhwr(const Int_t & /*fCheck*/, const Int_t & /*intHist*/);
}
   
// TFluka global pointer
TFluka *gFluka = 0;
TFlukaMCGeometry *gMCGeom = 0;
Int_t gNstep = 0;

ClassImp(TFlukaMCGeometry)

TFlukaMCGeometry* TFlukaMCGeometry::fgInstance= NULL;

//_____________________________________________________________________________
TFlukaMCGeometry::TFlukaMCGeometry(const char *name, const char *title) 
   :TNamed(name, title), 
   fDebug(kFALSE),
   fLastMaterial(0),
   fDummyRegion(0),
   fCurrentRegion(0),
   fCurrentLattice(0),
   fNextRegion(0),
   fNextLattice(0),
   fRegionList(0),
   fIndmat(0),
   fMatList(new TObjArray(256)),
   fMatNames(new TObjArray(256))
{
  //
  // Standard constructor
  //
  gFluka = (TFluka*)gMC;
  gMCGeom = this;
  gNstep = 0;
}

//_____________________________________________________________________________
TFlukaMCGeometry::TFlukaMCGeometry()
  :TNamed(),
   fDebug(kFALSE),
   fLastMaterial(0),
   fDummyRegion(0),
   fCurrentRegion(0),
   fCurrentLattice(0),
   fNextRegion(0),
   fNextLattice(0),
   fRegionList(0),
   fIndmat(0),
   fMatList(0),
   fMatNames(0)

{
  //
  // Default constructor
  //
  gFluka = (TFluka*)gMC;
  gMCGeom = this;
  gNstep = 0;
}

//_____________________________________________________________________________
TFlukaMCGeometry::~TFlukaMCGeometry() 
{
  //
  // Destructor
  //
  fgInstance=0;
  if (fRegionList) delete [] fRegionList;
  if (fMatList) delete fMatList;
  if (fMatNames) {fMatNames->Delete(); delete fMatNames;}
  if (gGeoManager) delete gGeoManager;
}

//
// private methods
//

//_____________________________________________________________________________
Double_t* TFlukaMCGeometry::CreateDoubleArray(Float_t* array, Int_t size) const
{
// Converts Float_t* array to Double_t*,
// !! The new array has to be deleted by user.
// ---

  Double_t* doubleArray;
  if (size>0) {
    doubleArray = new Double_t[size]; 
    for (Int_t i=0; i<size; i++) doubleArray[i] = array[i];
  }
  else {
    //doubleArray = 0; 
    doubleArray = new Double_t[1]; 
  }  
  return doubleArray;
}
//
// public methods


//_____________________________________________________________________________
Int_t TFlukaMCGeometry::GetMedium() const
{
// Get current medium number
   Int_t imed = 0;
   TGeoNode *node = gGeoManager->GetCurrentNode();
   if (!node) imed = gGeoManager->GetTopNode()->GetVolume()->GetMedium()->GetId();
   else       imed = node->GetVolume()->GetMedium()->GetId();
   if (fDebug) printf("GetMedium=%i\n", imed);
   return imed;
}

//_____________________________________________________________________________
Int_t TFlukaMCGeometry::GetFlukaMaterial(Int_t imed) const
{
// Returns FLUKA material index for medium IMED
     TGeoMedium *med = (TGeoMedium*)gGeoManager->GetListOfMedia()->At(imed-1);
   if (!med) {
      Error("GetFlukaMaterial", "MEDIUM %i nor found", imed);
      return -1;
   }
   TGeoMaterial* mat = med->GetMaterial();
   if (!mat->IsUsed()) return -1;
   Int_t imatfl = med->GetMaterial()->GetIndex();
   return imatfl;   
}

//_____________________________________________________________________________
Int_t *TFlukaMCGeometry::GetRegionList(Int_t imed, Int_t &nreg)
{
// Get an ordered list of regions matching a given medium number
   nreg = 0;
   if (!fRegionList) fRegionList = new Int_t[NofVolumes()+1];
   TIter next(gGeoManager->GetListOfUVolumes());
   TGeoVolume *vol;
   Int_t imedium, ireg;
   while ((vol = (TGeoVolume*)next())) {
       TGeoMedium* med;
       if ((med = vol->GetMedium()) == 0) continue;
       imedium = med->GetId();
       if (imedium == imed) {
           ireg = vol->GetNumber();
           fRegionList[nreg++] = ireg;
       }
   }
   return fRegionList;
}

//_____________________________________________________________________________
Int_t *TFlukaMCGeometry::GetMaterialList(Int_t imat, Int_t &nreg)
{
// Get an ordered list of regions matching a given medium number
   nreg = 0;
   if (!fRegionList) fRegionList = new Int_t[NofVolumes()+1];
   TIter next(gGeoManager->GetListOfUVolumes());
   TGeoVolume *vol;
   Int_t imaterial, ireg;
   while ((vol = (TGeoVolume*)next())) {
       TGeoMedium* med;
       if ((med = vol->GetMedium()) == 0) continue;
       imaterial = med->GetMaterial()->GetIndex();
       if (imaterial == imat) {
           ireg = vol->GetNumber();
           fRegionList[nreg++] = ireg;
       }
   }
   return fRegionList;
}
 
//_____________________________________________________________________________
Int_t TFlukaMCGeometry::NofVolumes() const 
{
  //
  // Return total number of volumes in the geometry
  //

  return gGeoManager->GetListOfUVolumes()->GetEntriesFast()-1;
}
  
//_____________________________________________________________________________
TGeoMaterial * TFlukaMCGeometry::GetMakeWrongMaterial(Double_t z)
{
// Try to replace a wrongly-defined material
   static Double_t kz[23] = {7.3, 17.8184, 7.2167, 10.856, 8.875, 8.9, 7.177,
      25.72, 6.2363, 7.1315, 47.7056, 10.6467, 7.8598, 2.10853, 10.6001, 9.1193, 
      15.3383, 4.55,   9.6502, 6.4561, 21.7963, 29.8246, 15.4021};

   Int_t ind;
   Double_t dz;
   for (ind=0; ind<23; ind++) {
      dz = TMath::Abs(z-kz[ind]);
      if (dz<1E-4) break;
   }
   if (ind>22) {
      printf("Cannot patch material with Z=%g\n", z);
      return 0;
   }
   TGeoMixture *mix = 0;
   TGeoElement *element;
   TGeoElementTable *table = gGeoManager->GetElementTable();
   switch (ind) {
      case 0: // AIR
         mix = new TGeoMixture("TPC_AIR", 4, 0.001205);
         element = table->GetElement(6); // C
         mix->DefineElement(0, element, 0.000124);
         element = table->GetElement(7); // N
         mix->DefineElement(1, element, 0.755267);
         element = table->GetElement(8); // O
         mix->DefineElement(2, element, 0.231781);
         element = table->GetElement(18); // AR
         mix->DefineElement(3, element, 0.012827);
         break;
      case 1: //SDD SI CHIP
         mix = new TGeoMixture("ITS_SDD_SI", 6, 2.4485);
         element = table->GetElement(1);
         mix->DefineElement(0, element, 0.004367771);
         element = table->GetElement(6);
         mix->DefineElement(1, element, 0.039730642);
         element = table->GetElement(7);
         mix->DefineElement(2, element, 0.001396798);
         element = table->GetElement(8);
         mix->DefineElement(3, element, 0.01169634);
         element = table->GetElement(14);
         mix->DefineElement(4, element, 0.844665);
         element = table->GetElement(47);
         mix->DefineElement(5, element, 0.09814344903);
         break;
      case 2:  // WATER
         mix = new TGeoMixture("ITS_WATER", 2, 1.0);
         element = table->GetElement(1);
         mix->DefineElement(0, element, 0.111898344);
         element = table->GetElement(8);
         mix->DefineElement(1, element, 0.888101656);
         break;
      case 3: // CERAMICS
         mix = new TGeoMixture("ITS_CERAMICS", 5, 3.6);
         element = table->GetElement(8);
         mix->DefineElement(0, element, 0.59956);
         element = table->GetElement(13);
         mix->DefineElement(1, element, 0.3776);
         element = table->GetElement(14);
         mix->DefineElement(2, element, 0.00933);
         element = table->GetElement(24);
         mix->DefineElement(3, element, 0.002);
         element = table->GetElement(25);
         mix->DefineElement(4, element, 0.0115);
         break;
      case 4: // EPOXY
         mix = new TGeoMixture("MUON_G10FR4", 4, 1.8);
         element = table->GetElement(1);
         mix->DefineElement(0, element, 0.19);
         element = table->GetElement(6);
         mix->DefineElement(1, element, 0.18);
         element = table->GetElement(8);
         mix->DefineElement(2, element, 0.35);
         element = table->GetElement(14);
         mix->DefineElement(3, element, 0.28);
         break;
      case 5: // EPOXY
         mix = new TGeoMixture("G10FR4", 4, 1.8);
         element = table->GetElement(1);
         mix->DefineElement(0, element, 0.19);
         element = table->GetElement(6);
         mix->DefineElement(1, element, 0.18);
         element = table->GetElement(8);
         mix->DefineElement(2, element, 0.35);
         element = table->GetElement(14);
         mix->DefineElement(3, element, 0.28);
         break;
      case 6: // KAPTON
         mix = new TGeoMixture("ITS_KAPTON", 4, 1.3);
         element = table->GetElement(1);
         mix->DefineElement(0, element, 0.026363415);
         element = table->GetElement(6);
         mix->DefineElement(1, element, 0.6911272);
         element = table->GetElement(7);
         mix->DefineElement(2, element, 0.073271325);
         element = table->GetElement(8);
         mix->DefineElement(3, element, 0.209238060);
         break;
      case 7: // INOX
         mix = new TGeoMixture("ITS_INOX", 9, 7.9);
         element = table->GetElement(6);
         mix->DefineElement(0, element, 0.0003);
         element = table->GetElement(14);
         mix->DefineElement(1, element, 0.01);          
         element = table->GetElement(15);
         mix->DefineElement(2, element, 0.00045);
         element = table->GetElement(16);
         mix->DefineElement(3, element, 0.0003);
         element = table->GetElement(24);
         mix->DefineElement(4, element, 0.17);
         element = table->GetElement(25);
         mix->DefineElement(5, element, 0.02);
         element = table->GetElement(26);
         mix->DefineElement(6, element, 0.654);
         element = table->GetElement(28);
         mix->DefineElement(7, element, 0.12);
         element = table->GetElement(42);
         mix->DefineElement(8, element, 0.025);
         break;
      case 8: // ROHACELL
         mix = new TGeoMixture("ROHACELL", 4, 0.05);
         element = table->GetElement(1);
         mix->DefineElement(0, element, 0.07836617);
         element = table->GetElement(6);
         mix->DefineElement(1, element, 0.64648941);
         element = table->GetElement(7);
         mix->DefineElement(2, element, 0.08376983);
         element = table->GetElement(8);
         mix->DefineElement(3, element, 0.19137459);
         break;
      case 9: // SDD-C-AL
         mix = new TGeoMixture("ITS_SDD-C-AL", 5, 1.9837);
         element = table->GetElement(1);
         mix->DefineElement(0, element, 0.022632);
         element = table->GetElement(6);
         mix->DefineElement(1, element, 0.8176579);
         element = table->GetElement(7);
         mix->DefineElement(2, element, 0.0093488);
         element = table->GetElement(8);
         mix->DefineElement(3, element, 0.0503618);
         element = table->GetElement(13);
         mix->DefineElement(4, element, 0.1);
         break;
      case 10: // X7R-CAP
         mix = new TGeoMixture("ITS_X7R-CAP", 7, 6.72);
         element = table->GetElement(8);
         mix->DefineElement(0, element, 0.085975822);
         element = table->GetElement(22);
         mix->DefineElement(1, element, 0.084755042);
         element = table->GetElement(28);
         mix->DefineElement(2, element, 0.038244751);
         element = table->GetElement(29);
         mix->DefineElement(3, element, 0.009471271);
         element = table->GetElement(50);
         mix->DefineElement(4, element, 0.321736471);
         element = table->GetElement(56);
         mix->DefineElement(5, element, 0.251639432);
         element = table->GetElement(82);
         mix->DefineElement(6, element, 0.2081768);
         break;
      case 11: // SDD ruby sph. Al2O3
         mix = new TGeoMixture("ITS_AL2O3", 2, 3.97);
         element = table->GetElement(8);
         mix->DefineElement(0, element, 0.5293);
         element = table->GetElement(13);
         mix->DefineElement(1, element, 0.4707);
         break;
      case 12: // SDD HV microcable
         mix = new TGeoMixture("ITS_HV-CABLE", 5, 1.6087);
         element = table->GetElement(1);
         mix->DefineElement(0, element, 0.01983871336);
         element = table->GetElement(6);
         mix->DefineElement(1, element, 0.520088819984);
         element = table->GetElement(7);
         mix->DefineElement(2, element, 0.0551367996);
         element = table->GetElement(8);
         mix->DefineElement(3, element, 0.157399667056);
         element = table->GetElement(13);
         mix->DefineElement(4, element, 0.247536);
         break;
      case 13: //SDD LV+signal cable
         mix = new TGeoMixture("ITS_LV-CABLE", 5, 2.1035);
         element = table->GetElement(1);
         mix->DefineElement(0, element, 0.0082859922);
         element = table->GetElement(6);
         mix->DefineElement(1, element, 0.21722436468);
         element = table->GetElement(7);
         mix->DefineElement(2, element, 0.023028867);
         element = table->GetElement(8);
         mix->DefineElement(3, element, 0.06574077612);
         element = table->GetElement(13);
         mix->DefineElement(4, element, 0.68572);
         break;
      case 14: //SDD hybrid microcab
         mix = new TGeoMixture("ITS_HYB-CAB", 5, 2.0502);
         element = table->GetElement(1);
         mix->DefineElement(0, element, 0.00926228815);
         element = table->GetElement(6);
         mix->DefineElement(1, element, 0.24281879711);
         element = table->GetElement(7);
         mix->DefineElement(2, element, 0.02574224025);
         element = table->GetElement(8);
         mix->DefineElement(3, element, 0.07348667449);
         element = table->GetElement(13);
         mix->DefineElement(4, element, 0.64869);
         break;
      case 15: //SDD anode microcab
         mix = new TGeoMixture("ITS_ANOD-CAB", 5, 1.7854);
         element = table->GetElement(1);
         mix->DefineElement(0, element, 0.0128595919215);
         element = table->GetElement(6);
         mix->DefineElement(1, element, 0.392653705471);
         element = table->GetElement(7);
         mix->DefineElement(2, element, 0.041626868025);
         element = table->GetElement(8);
         mix->DefineElement(3, element, 0.118832707289);
         element = table->GetElement(13);
         mix->DefineElement(4, element, 0.431909);
         break;
      case 16: // inox/alum
         mix = new TGeoMixture("ITS_INOX-AL", 5, 3.0705);
         element = table->GetElement(13);
         mix->DefineElement(0, element, 0.816164);
         element = table->GetElement(14);
         mix->DefineElement(1, element, 0.000919182);
         element = table->GetElement(24);
         mix->DefineElement(2, element, 0.0330906);
         element = table->GetElement(26);
         mix->DefineElement(3, element, 0.131443);
         element = table->GetElement(28);
         mix->DefineElement(4, element, 0.0183836);
      case 17: // MYLAR
         mix = new TGeoMixture("TPC_MYLAR", 3, 1.39);
         element = table->GetElement(1);
         mix->DefineElement(0, element, 0.0416667);
         element = table->GetElement(6);
         mix->DefineElement(1, element, 0.625);
         element = table->GetElement(8);
         mix->DefineElement(2, element, 0.333333);
         break;
      case 18: // SPDBUS(AL+KPT+EPOX)   - unknown composition
         mix = new TGeoMixture("ITS_SPDBUS", 1, 1.906);
         element = table->GetElement(9);
         mix->DefineElement(0, element, 1.);
         z = element->Z();
         break;
      case 19: // SDD/SSD rings   - unknown composition
         mix = new TGeoMixture("ITS_SDDRINGS", 1, 1.8097);
         element = table->GetElement(6);
         mix->DefineElement(0, element, 1.);
         z = element->Z();
         break;
      case 20: // SPD end ladder   - unknown composition
         mix = new TGeoMixture("ITS_SPDEL", 1, 3.6374);
         element = table->GetElement(22);
         mix->DefineElement(0, element, 1.);
         z = element->Z();
         break;
      case 21: // SDD end ladder   - unknown composition
         mix = new TGeoMixture("ITS_SDDEL", 1, 0.3824);
         element = table->GetElement(30);
         mix->DefineElement(0, element, 1.);
         z = element->Z();
         break;
      case 22: // SSD end ladder   - unknown composition
         mix = new TGeoMixture("ITS_SSDEL", 1, 0.68);
         element = table->GetElement(16);
         mix->DefineElement(0, element, 1.);
         z = element->Z();
         break;
   }
   mix->SetZ(z);      
   printf("Patched with mixture %s\n", mix->GetName());
   return mix;
}   

//_____________________________________________________________________________
void TFlukaMCGeometry::CreateFlukaMatFile(const char *fname)
{
  // ==== from FLUGG ====
  // NAMES OF ELEMENTS AND COMPOUNDS: the names must be written in upper case,
  // according to the fluka standard. In addition,. they must be equal to the
  // names of the fluka materials - see fluka manual - in order that the 
  // program load the right cross sections, and equal to the names included in
  // the .pemf. Otherwise the user must define the LOW-MAT CARDS, and make his
  // own .pemf, in order to get the right cross sections loaded in memory.
  // Materials defined by FLUKA
   TString sname;
   gGeoManager->Export("geometry.root");
   if (fname) sname = fname;
   else       sname = "flukaMat.inp";
   ofstream out;
   out.open(sname.Data(), ios::out);
   if (!out.good()) {
      Fatal("CreateFlukaMatFile", "could not open file %s for writing", sname.Data());
      return;
   }
   PrintHeader(out, "MATERIALS AND COMPOUNDS");
   PrintHeader(out, "MATERIALS");   
   Int_t i,j,idmat;
   Int_t counttothree, nelem;
   Double_t a,z,rho, w;
   TGeoElementTable *table = gGeoManager->GetElementTable();
   TGeoElement *element;
   element = table->GetElement(13);
   element->SetTitle("ALUMINUM"); // this is how FLUKA likes it ...
   element = table->GetElement(15);
   element->SetTitle("PHOSPHO");  // same story ...
   Int_t nelements = table->GetNelements();
   TList *matlist = gGeoManager->GetListOfMaterials();
   TIter next(matlist);
   Int_t nmater = matlist->GetSize();
   Int_t nfmater =  0;
   Int_t newind  = 26;  // here non predefined materials start
   
   TGeoMaterial *mat;
   TGeoMixture *mix = 0;
   TString matname;
   TObjString *objstr;
   // Create all needed elements
   for (Int_t iel = 1; iel < nelements; iel++) {
      element = table->GetElement(iel);
      // skip elements which are not defined
      if (!element->IsUsed() && !element->IsDefined()) continue;
      matname = element->GetTitle();
      ToFlukaString(matname);
      rho = 0.999;

      mat = new TGeoMaterial(matname, element->A(), element->Z(), rho);
      // Check if the element has been predefined by FLUKA
      Int_t pmid = GetPredefinedMaterialId(Int_t(element->Z()));
      if (pmid > 0) {
	  mat->SetIndex(pmid);
      } else {
	  mat->SetIndex(newind++);
      }
      
      mat->SetUsed(kTRUE);
      fMatList->Add(mat);
      objstr = new TObjString(matname.Data());
      fMatNames->Add(objstr);
      nfmater++;
   }
   
   fIndmat = nfmater;
   // Adjust material names and add them to FLUKA list
   for (i=0; i<nmater; i++) {
      mat = (TGeoMaterial*)matlist->At(i);
      if (!mat->IsUsed()) continue;
      z = mat->GetZ();
      a = mat->GetA();
      rho = mat->GetDensity();
      if (mat->GetZ()<0.001) {
         mat->SetIndex(2); // vacuum, built-in inside FLUKA
         continue;
      } 
      matname = mat->GetName();
      FlukaMatName(matname);

      mat->SetIndex(newind++);
      objstr = new TObjString(matname.Data());
      fMatList->Add(mat);
      fMatNames->Add(objstr);
      nfmater++;
   }   

   // Dump all elements with MATERIAL cards         
   for (i=0; i<nfmater; i++) {
      mat = (TGeoMaterial*)fMatList->At(i);
//      mat->SetUsed(kFALSE);
      mix = 0;
      out << setw(10) << "MATERIAL  ";
      out.setf(static_cast<std::ios::fmtflags>(0),std::ios::floatfield);
      objstr = (TObjString*)fMatNames->At(i);
      matname = objstr->GetString();
      z = mat->GetZ();
      a = mat->GetA();
      rho = mat->GetDensity();
      if (mat->IsMixture()) {
         out << setw(10) << " ";
         out << setw(10) << " ";
         mix = (TGeoMixture*)mat;
      } else {   
         out << setw(10) << setiosflags(ios::fixed) << setprecision(1) << z;
         out << setw(10) << setprecision(3) << a;
      }
      out.setf(static_cast<std::ios::fmtflags>(0),std::ios::floatfield);
      out << setw(10) << setiosflags(ios::scientific) << setprecision(3) << rho;
      out.setf(static_cast<std::ios::fmtflags>(0),std::ios::floatfield);
      out << setw(10) << setiosflags(ios::fixed) << setprecision(1) << Double_t(mat->GetIndex());   
      out << setw(10) << " ";
      out << setw(10) << " ";
      out << setw(8) << matname.Data() << endl;
      if (!mix) {
         // add LOW-MAT card for NEON to associate with ARGON neutron xsec
         if (z==10) {
            out << setw(10) << "LOW-MAT   ";
            out.setf(static_cast<std::ios::fmtflags>(0),std::ios::floatfield);
            out << setw(10) << setiosflags(ios::fixed) << setprecision(1) << Double_t(mat->GetIndex());
            out << setw(10) << setiosflags(ios::fixed) << setprecision(1) << 18.;
            out << setw(10) << setiosflags(ios::fixed) << setprecision(1) << -2.;
            out << setw(10) << setiosflags(ios::fixed) << setprecision(1) << 293.;
            out << setw(10) << " ";
            out << setw(10) << " ";
//            out << setw(8) << matname.Data() << endl;
            out << setw(8) << " " << endl;
         } 
         else { 
            element = table->GetElement((int)z);
            TString elename = element->GetTitle();
            ToFlukaString(elename);
            if( matname.CompareTo( elename ) != 0 ) {
               out << setw(10) << "LOW-MAT   ";
               out.setf(static_cast<std::ios::fmtflags>(0),std::ios::floatfield);
               out << setw(10) << setiosflags(ios::fixed) << setprecision(1) << Double_t(mat->GetIndex());
               out << setw(10) << setiosflags(ios::fixed) << setprecision(1) << z;
               out << setw(10) << setiosflags(ios::fixed) << setprecision(1) << " ";
               out << setw(10) << setiosflags(ios::fixed) << setprecision(1) << " ";
               out << setw(10) << " ";
               out << setw(10) << " ";
               // missing material at Low Energy Cross Section Table
               if( (int)z==10 || (int)z==21 || (int)z==34 || (int)z==37 || (int)z==39 || (int)z==44 ||
                   (int)z==45 || (int)z==46 || (int)z==52 || (int)z==57 || (int)z==59 || (int)z==60 ||
                   (int)z==61 || (int)z==65 || (int)z==66 || (int)z==67 || (int)z==68 || (int)z==69 ||
                   (int)z==70 || (int)z==71 || (int)z==72 || (int)z==76 || (int)z==77 || (int)z==78 ||
                   (int)z==81 || (int)z==84 || (int)z==85 || (int)z==86 || (int)z==87 || (int)z==88 ||
                   (int)z==89 || (int)z==91 )
                  out << setw(8) << "UNKNOWN " << endl;
               else
                  out << setw(8) << elename.Data() << endl;
   //               out << setw(8) << " " << endl;
            }
         }
         continue;
      }   
      counttothree = 0;
      out << setw(10) << "COMPOUND  ";
      nelem = mix->GetNelements();
      objstr = (TObjString*)fMatNames->At(i);
      matname = objstr->GetString();
      for (j=0; j<nelem; j++) {
         w = (mix->GetWmixt())[j];
         if (w<0.00001) w=0.00001;
         z = (mix->GetZmixt())[j];       
         a = (mix->GetAmixt())[j];
         idmat = GetElementIndex(Int_t(z));
         if (!idmat) Error("CreateFlukaMatFile", "element with Z=%f not found", z);
         out.setf(static_cast<std::ios::fmtflags>(0),std::ios::floatfield);
         out << setw(10) << setiosflags(ios::fixed) << setprecision(6) << -w;   
         out.setf(static_cast<std::ios::fmtflags>(0),std::ios::floatfield);
         out << setw(10) << setiosflags(ios::fixed) << setprecision(1) << Double_t(idmat);
         counttothree++;
         if (counttothree == 3) {
            out << matname.Data();
            out << endl;
            if ( (j+1) != nelem) out << setw(10) << "COMPOUND  ";
            counttothree = 0;
         } 
      }               
      if (nelem%3) {
         for (j=0; j<(3-(nelem%3)); j++)
            out << setw(10) << " " << setw(10) << " ";
         out << matname.Data();
         out << endl;
      } 
   }     
   Int_t nvols = gGeoManager->GetListOfUVolumes()->GetEntriesFast()-1;
   TGeoVolume *vol;
   // Now print the material assignments
   Double_t flagfield = 0.;
   printf("#############################################################\n");
   if (gFluka->IsFieldEnabled()) {
      flagfield = 1.;
      printf("Magnetic field enabled\n");
   } else printf("Magnetic field disabled\n");   
   printf("#############################################################\n");
   
   PrintHeader(out, "TGEO MATERIAL ASSIGNMENTS");   
   for (i=1; i<=nvols; i++) {
      TGeoMedium* med;
      vol = gGeoManager->GetVolume(i);
      if ((med = vol->GetMedium()) == 0) continue;
      mat = med->GetMaterial();
      idmat = mat->GetIndex();
      for (Int_t jmat = 0; jmat < nfmater; jmat++) {
         mat = (TGeoMaterial*)fMatList->At(jmat);
         if (mat->GetIndex() == idmat) mat->SetUsed(kTRUE);
      }   

      Float_t hasfield  = (vol->GetMedium()->GetParam(1) > 0) ? flagfield : 0.;
      out << "* Assigning material:   " << vol->GetMedium()->GetMaterial()->GetName() << "   to Volume: " << vol->GetName();
      out << endl;

      out << setw(10) << "ASSIGNMAT ";
      out.setf(static_cast<std::ios::fmtflags>(0),std::ios::floatfield);
      out << setw(10) << setiosflags(ios::fixed) << Double_t(idmat);
      out << setw(10) << setiosflags(ios::fixed) << Double_t(i);
      out << setw(10) << "0.0";
      out << setw(10) << "0.0";
      out << setw(10) << setiosflags(ios::fixed) <<  hasfield;
      out << setw(10) << "0.0";
      out << endl;
   }
   // dummy region
   idmat = 2; // vacuum
   fDummyRegion = nvols+1;
   out << "* Dummy region:   " << endl;
   out << setw(10) << "ASSIGNMAT ";
   out.setf(static_cast<std::ios::fmtflags>(0),std::ios::floatfield);
   out << setw(10) << setiosflags(ios::fixed) << idmat;
   out << setw(10) << setiosflags(ios::fixed) << fDummyRegion;
   out << setw(10) << "0.0";
   out << setw(10) << "0.0";
   out << setw(10) << "0.0";
   out << setw(10) << "0.0" << endl;
   out.close();
//   fLastMaterial = nfmater+2;
   fLastMaterial = newind;
}

//_____________________________________________________________________________
void TFlukaMCGeometry::PrintHeader(ofstream &out, const char *text) const
{
// Print a FLUKA header.
  out << "*\n" << "*\n" << "*\n";
  out << "*********************  " << text << " *********************\n"
     << "*\n";
  out << "*...+....1....+....2....+....3....+....4....+....5....+....6....+....7..."
     << endl;
  out << "*" << endl;
}

//_____________________________________________________________________________
Int_t TFlukaMCGeometry::RegionId() const
{
// Returns current region id <-> TGeo node id
   if (gGeoManager->IsOutside()) return 0;
   return gGeoManager->GetCurrentNode()->GetUniqueID();
}

//_____________________________________________________________________________
Int_t TFlukaMCGeometry::GetElementIndex(Int_t z) const
{
// Get index of a material having a given Z element.
   TIter next(fMatList);
   TGeoMaterial *mat;
   Int_t index = 0;
   while ((mat=(TGeoMaterial*)next())) {
      if (mat->IsMixture()) continue;
      if (mat->GetElement()->Z() == z) return mat->GetIndex();
   }
   return index;   
}

//_____________________________________________________________________________
void TFlukaMCGeometry::SetMreg(Int_t mreg, Int_t lttc)
{
// Update if needed next history;
//   if (gFluka->GetDummyBoundary()==2) {
//      gGeoManager->CdNode(fNextLattice-1);
//      return;
//   }   
   if (lttc == TFlukaMCGeometry::kLttcOutside) {
      fCurrentRegion = NofVolumes()+2;
      fCurrentLattice = lttc;
      gGeoManager->CdTop();
      gGeoManager->SetOutside(kTRUE);
   }
   if (lttc == TFlukaMCGeometry::kLttcVirtual) return;
   if (lttc <=0) {
      Error("TFlukaMCGeometry::SetMreg","Invalide lattice %i",lttc);
      return;
   }      
   fCurrentRegion = mreg;
   fCurrentLattice = lttc;
   
   Int_t crtlttc = gGeoManager->GetCurrentNodeId()+1;
   if (crtlttc == lttc) return;
   gGeoManager->CdNode(lttc-1);
   while (gGeoManager->GetCurrentVolume()->IsAssembly()) gGeoManager->CdUp();
}

//_____________________________________________________________________________
void TFlukaMCGeometry::SetCurrentRegion(Int_t mreg, Int_t latt)
{
// Set index/history for next entered region
   fCurrentRegion = mreg;
   fCurrentLattice = latt;
}   

//_____________________________________________________________________________
void TFlukaMCGeometry::SetNextRegion(Int_t mreg, Int_t latt)
{
// Set index/history for next entered region
   fNextRegion = mreg;
   fNextLattice = latt;
}   

//_____________________________________________________________________________
void TFlukaMCGeometry::ToFlukaString(TString &str) const
{
// ToFlukaString converts an string to something usefull in FLUKA:
// * Capital letters
// * Only 8 letters
// * Replace ' ' by '_'
   if (str.Length()<8) {
      str += "        ";
   }   
   str.Remove(8);
   Int_t ilast;
   for (ilast=7; ilast>0; ilast--) if (str(ilast)!=' ') break;
   str.ToUpper();
   for (Int_t pos=0; pos<ilast; pos++)
      if (str(pos)==' ') str.Replace(pos,1,"_",1);
   return;
}   

//_____________________________________________________________________________
void TFlukaMCGeometry::FlukaMatName(TString &str) const
{
// Strip the detector name
    TObjArray * tokens = str.Tokenize("_");
    Int_t ntok = tokens->GetEntries();
    if (ntok > 1) {
        TString head = ((TObjString*) tokens->At(0))->GetString();
        Int_t nhead = head.Length();
        str = str.Remove(0, nhead + 1);
    }
    tokens->Clear();
    delete tokens;
// Convert a name to upper case 8 chars.
   ToFlukaString(str);
   Int_t ilast;
   for (ilast=7; ilast>0; ilast--) if (str(ilast)!=' ') break;
   if (ilast>5) ilast = 5;
   char number[3];
   TIter next(fMatNames);
   TObjString *objstr;
   TString matname;
   Int_t index = 0;
   while ((objstr=(TObjString*)next())) {
      matname = objstr->GetString();
      if (matname == str) {
         index++;
         if (index<10) {
            number[0] = '0';
            sprintf(&number[1], "%d", index);
         } else if (index<100) {
            sprintf(number, "%d", index);            
         } else {
            Error("FlukaMatName", "Too many materials %s", str.Data());
            return;
         }
         str.Replace(ilast+1, 2, number);
         str.Remove(8);
      }   
   }   
}   

//______________________________________________________________________________
void TFlukaMCGeometry::Vname(const char *name, char *vname) const
{
  //
  //  convert name to upper case. Make vname at least 4 chars
  //
  Int_t l = strlen(name);
  Int_t i;
  l = l < 4 ? l : 4;
  for (i=0;i<l;i++) vname[i] = toupper(name[i]);
  for (i=l;i<4;i++) vname[i] = ' ';
  vname[4] = 0;      
}


//______________________________________________________________________________
Int_t TFlukaMCGeometry::GetNstep()
{
   // return gNstep for debug propose
   return gNstep;
}


Int_t TFlukaMCGeometry::GetPredefinedMaterialId(Int_t z) const
{
// Get predifined material id from Z if present in list
    const Int_t kMax = 25;
    
    static Int_t idFluka[kMax] = 	
	{-1, -1,  1,  2,  4,  6,  7,  8,  12,  13, 
	 26, 29, 47, 14, 79, 80, 82, 73,  11,  18, 
	 20, 50, 74, 22, 28};
    
    Int_t id = -1;

    for (Int_t i = 0; i < kMax; i++)
    {
	if (z == idFluka[i]) {
	    id = i + 1;
	    break;
	}

  }
  
    return id;
}

// FLUKA GEOMETRY WRAPPERS - to replace FLUGG wrappers
//
//_____________________________________________________________________________
Int_t idnrwr(const Int_t & /*nreg*/, const Int_t & /*mlat*/)
{
//   from FLUGG:
// Wrapper for setting DNEAR option on fluka side. Must return 0 
// if user doesn't want Fluka to use DNEAR to compute the 
// step (the same effect is obtained with the GLOBAL (WHAT(3)=-1)
// card in fluka input), returns 1 if user wants Fluka always to 
// use DNEAR (in this case, be sure that GEANT4 DNEAR is unique, 
// coming from all directions!!!)
   if (gMCGeom->IsDebugging()) printf("========== Dummy IDNRWR\n");
   return 0;
}

//_____________________________________________________________________________
void g1wr(Double_t &pSx, Double_t &pSy, Double_t &pSz, 
          Double_t *pV,  Int_t &oldReg , const Int_t &oldLttc, Double_t &propStep,
          Int_t &/*nascFlag*/, Double_t &retStep, Int_t &newReg,
          Double_t &saf, Int_t &newLttc, Int_t &lttcFlag,
          Double_t *sLt, Int_t *jrLt)

{
   // Initialize FLUKa point and direction;
   static Int_t ierr = 0;
   gNstep++;
//      gMCGeom->SetDebugMode(kTRUE);
   
   NORLAT.xn[0] = pSx;
   NORLAT.xn[1] = pSy;
   NORLAT.xn[2] = pSz;

   Int_t olttc = oldLttc;
   if (oldLttc<=0) {
      gGeoManager->FindNode(pSx,pSy,pSz);
      olttc = gGeoManager->GetCurrentNodeId()+1;
      oldReg = gGeoManager->GetCurrentVolume()->GetNumber();
   }

   if (gMCGeom->IsDebugging()) {
      cout << "g1wr gNstep=" << gNstep << " oldReg="<< oldReg <<" olttc="<< olttc
           << " track=" << TRACKR.ispusr[mkbmx2-1] << endl;
      cout << " point: (" << pSx << ", " << pSy << ", " << pSz << ")  dir: ("
           << pV[0] << ", " << pV[1] << ", " << pV[2] << ")" << endl;
   }        
           

   Int_t ccreg=0,cclat=0;
   gMCGeom->GetCurrentRegion(ccreg,cclat);
   Bool_t crossed = (ccreg==oldReg && cclat==olttc)?kFALSE:kTRUE;

   gMCGeom->SetCurrentRegion(oldReg, olttc);
   // Initialize default return values
   lttcFlag = 0;
   jrLt[lttcFlag] = olttc;
   sLt[lttcFlag] = propStep;
   jrLt[lttcFlag+1] = -1;
   sLt[lttcFlag+1] = 0.;
   newReg = oldReg;
   newLttc = olttc;
   Bool_t crossedDummy = (oldReg == gFluka->GetDummyRegion())?kTRUE:kFALSE;
   Int_t curLttc, curReg;
   if (crossedDummy) {
   // FLUKA crossed the dummy boundary - update new region/history
      retStep = TGeoShape::Tolerance();
      saf = 0.;
      gMCGeom->GetNextRegion(newReg, newLttc);
      gMCGeom->SetMreg(newReg, newLttc);
      sLt[lttcFlag] = TGeoShape::Tolerance(); // null step in current region
      lttcFlag++;
      jrLt[lttcFlag] = newLttc;
      sLt[lttcFlag] = TGeoShape::Tolerance(); // null step in next region
      jrLt[lttcFlag+1] = -1;
      sLt[lttcFlag+1] = 0.; // null step in next region;
      if (gMCGeom->IsDebugging()) printf("=> crossed dummy!! newReg=%i newLttc=%i\n", newReg, newLttc);
      return;
   }

   // Reset outside flag
   gGeoManager->SetOutside(kFALSE);

   curLttc = gGeoManager->GetCurrentNodeId()+1;
   curReg = gGeoManager->GetCurrentVolume()->GetNumber();
   if (olttc != curLttc) {
      // FLUKA crossed the boundary : we trust that the given point is really there,
      // so we just update TGeo state
      gGeoManager->CdNode(olttc-1);
      curLttc = gGeoManager->GetCurrentNodeId()+1;
      curReg  = gGeoManager->GetCurrentVolume()->GetNumber();
   }
   // Now the current TGeo state reflects the FLUKA state 

   gGeoManager->SetCurrentPoint(pSx, pSy, pSz);
   gGeoManager->SetCurrentDirection(pV);
   Double_t pt[3], local[3], ldir[3];
   Int_t pid = TRACKR.jtrack;
   pt[0] = pSx;
   pt[1] = pSy;
   pt[2] = pSz;
   gGeoManager->MasterToLocal(pt,local);
   gGeoManager->MasterToLocalVect(pV,ldir);
/*
   Bool_t valid = gGeoManager->GetCurrentVolume()->Contains(local);
   if (!valid) {
      printf("location not valid in %s pid=%i\n", gGeoManager->GetPath(),pid);
      printf("local:(%f, %f, %f)  ldir:(%f, %f, %f)\n", local[0],local[1],local[2],ldir[0],ldir[1],ldir[2]);
//      gGeoManager->FindNode();
//      printf("   -> actual location: %s\n", gGeoManager->GetPath());
   }   
*/
   Double_t pstep = propStep;
   Double_t snext = propStep;
   const Double_t epsil = 0.9999999 * TGeoShape::Tolerance();
   // This should never happen !!!
   if (pstep<TGeoShape::Tolerance()) {
      printf("Proposed step is 0 !!!\n");
      pstep = 2.*TGeoShape::Tolerance();
   }   
   if (crossed) {
      gGeoManager->FindNextBoundaryAndStep(pstep);
      snext = gGeoManager->GetStep();
      saf = 0.;
      if (snext <= TGeoShape::Tolerance()) {
//         printf("FLUKA crossed boundary but snext=%g\n", snext);
         ierr++;
         snext = epsil;
      } else {
         snext += TGeoShape::Tolerance();
         ierr = 0;
      }     
   } else {
      gGeoManager->FindNextBoundaryAndStep(pstep, kTRUE);
      snext = gGeoManager->GetStep();
      saf = gGeoManager->GetSafeDistance();
      if (snext <= TGeoShape::Tolerance()) {
//         printf("FLUKA put particle on bondary without crossing\n");
         ierr++;
         snext = epsil;
         saf = 0.;
      } else {
         snext += TGeoShape::Tolerance();
         ierr = 0;
      }      
      if (saf<0) saf=0.;
      saf -= saf*3.0e-09;
   }
//   if (ierr>1) {
//      printf("%d snext=%g\n", ierr, snext);
//   }   
   if (ierr == 10) {
//      printf("Too many null steps - sending error code -33...\n");
      newReg = -33;   // Error code
      ierr = 0;
      return;
   }   
   
   PAREM.dist = snext;
   NORLAT.distn = snext;
   NORLAT.xn[0] += snext*pV[0];
   NORLAT.xn[1] += snext*pV[1];
   NORLAT.xn[2] += snext*pV[2];
   if (!gGeoManager->IsOnBoundary()) {
   // Next boundary further than proposed step, which is approved
      if (saf>propStep) saf = propStep;
      retStep = propStep;
      sLt[lttcFlag] = propStep;
      return;
   }
   if (saf>snext) saf = snext; // Safety should be less than the proposed step if a boundary will be crossed
   gGeoManager->SetCurrentPoint(pSx,pSy,pSz);
   newLttc = (gGeoManager->IsOutside())?(TFlukaMCGeometry::kLttcOutside):gGeoManager->GetCurrentNodeId()+1;
   newReg = (gGeoManager->IsOutside())?(gMCGeom->NofVolumes()+2):gGeoManager->GetCurrentVolume()->GetNumber();
   if (gMCGeom->IsDebugging()) printf("=> newReg=%i newLttc=%i\n", newReg, newLttc);

   // We really crossed the boundary, but is it the same region ?
   gMCGeom->SetNextRegion(newReg, newLttc);

   if ( ((newReg==oldReg && newLttc!=olttc) || (oldReg!=newReg && olttc==newLttc) ) && pid!=-1) {
      // Virtual boundary between replicants
      newReg  = gFluka->GetDummyRegion();
      newLttc = TFlukaMCGeometry::kLttcVirtual;
      if (gMCGeom->IsDebugging()) printf("=> virtual boundary!! newReg=%i newLttc=%i\n", newReg, newLttc);
   }

   retStep = snext;
   sLt[lttcFlag] = snext;
   lttcFlag++;
   jrLt[lttcFlag] = newLttc;
   sLt[lttcFlag] = snext;
   jrLt[lttcFlag+1] = -1;

   sLt[lttcFlag+1] = 0.;
   gGeoManager->SetOutside(kFALSE);
   gGeoManager->CdNode(olttc-1);
   if (gMCGeom->IsDebugging()) {
      printf("=> snext=%g safe=%g\n", snext, saf);
      for (Int_t i=0; i<lttcFlag+1; i++) printf("   jrLt[%i]=%i  sLt[%i]=%g\n", i,jrLt[i],i,sLt[i]);
   }
}

//_____________________________________________________________________________
void g1rtwr()
{

   if (gMCGeom->IsDebugging()) printf("========== Dummy G1RTWR\n");
} 

//_____________________________________________________________________________
void conhwr(Int_t & intHist, Int_t & incrCount)
{
   if (gMCGeom->IsDebugging()) printf("========== Dummy CONHWR intHist=%d incrCount=%d currentNodeId=%d\n",
                                       intHist, incrCount, gGeoManager->GetCurrentNodeId()+1 );
//   if( incrCount != -1 ) {
//      if (intHist==0) gGeoManager->CdTop();
//      else gGeoManager->CdNode(intHist-1);
//   }
//   intHist = gGeoManager->GetCurrentNodeId()+1;
}

//_____________________________________________________________________________
void inihwr(Int_t &intHist)
{
   if (gMCGeom->IsDebugging())
      printf("========== Inside INIHWR -> reinitializing history: %i \n", intHist);
   if (gGeoManager->IsOutside()) gGeoManager->CdTop();
   if (intHist<0) {
//      printf("=== wrong history number\n");
      return;
   }
   if (intHist==0) gGeoManager->CdTop();
   else gGeoManager->CdNode(intHist-1);
   if (gMCGeom->IsDebugging()) {
      printf(" --- current path: %s\n", gGeoManager->GetPath());
      printf("<= INIHWR\n");
   }
}

//_____________________________________________________________________________
void  jomiwr(const Int_t & /*nge*/, const Int_t & /*lin*/, const Int_t & /*lou*/,
             Int_t &flukaReg)
{
// Geometry initialization wrapper called by FLUKAM. Provides to FLUKA the
// number of regions (volumes in TGeo)
   // build application geometry
   if (gMCGeom->IsDebugging()) printf("========== Inside JOMIWR\n");
   flukaReg = gGeoManager->GetListOfUVolumes()->GetEntriesFast()+1;
   if (gMCGeom->IsDebugging()) printf("<= JOMIWR: last region=%i\n", flukaReg);
}   

//_____________________________________________________________________________
void lkdbwr(Double_t &pSx, Double_t &pSy, Double_t &pSz,
            Double_t *pV, const Int_t &oldReg, const Int_t &oldLttc,
            Int_t &flagErr, Int_t &newReg, Int_t &newLttc)             
{
   if (gMCGeom->IsDebugging()) {
      printf("========== Inside LKDBWR (%f, %f, %f)\n",pSx, pSy, pSz);
      printf("   in: pV=(%f, %f, %f)\n", pV[0], pV[1], pV[2]);
      printf("   in: oldReg=%i oldLttc=%i\n", oldReg, oldLttc);
   }   
   lkwr(pSx,pSy,pSz,pV,oldReg,oldLttc,flagErr,newReg,newLttc);
}

//_____________________________________________________________________________
void lkfxwr(Double_t &pSx, Double_t &pSy, Double_t &pSz,
            Double_t *pV, const Int_t &oldReg, const Int_t &oldLttc,
            Int_t &flagErr, Int_t &newReg, Int_t &newLttc)
{
   if (gMCGeom->IsDebugging()) {
      printf("========== Inside LKFXWR (%f, %f, %f)\n",pSx, pSy, pSz);
      printf("   in: pV=(%f, %f, %f)\n", pV[0], pV[1], pV[2]);
      printf("   in: oldReg=%i oldLttc=%i\n", oldReg, oldLttc);
   }   
   lkwr(pSx,pSy,pSz,pV,oldReg,oldLttc,flagErr,newReg,newLttc);
}

//_____________________________________________________________________________
void lkmgwr(Double_t &pSx, Double_t &pSy, Double_t &pSz,
            Double_t *pV, const Int_t &oldReg, const Int_t &oldLttc,
            Int_t &flagErr, Int_t &newReg, Int_t &newLttc)
{
   if (gMCGeom->IsDebugging()) {
      printf("========== Inside LKMGWR (%f, %f, %f)\n",pSx, pSy, pSz);
      printf("   in: pV=(%f, %f, %f)\n", pV[0], pV[1], pV[2]);
      printf("   in: oldReg=%i oldLttc=%i\n", oldReg, oldLttc);
   }   
   lkwr(pSx,pSy,pSz,pV,oldReg,oldLttc,flagErr,newReg,newLttc);
}

//_____________________________________________________________________________
void lkwr(Double_t &pSx, Double_t &pSy, Double_t &pSz,
          Double_t *pV, const Int_t &oldReg, const Int_t &oldLttc,
          Int_t &flagErr, Int_t &newReg, Int_t &newLttc)
{
   if (gMCGeom->IsDebugging()) {
      printf("========== Inside LKWR (%f, %f, %f)\n",pSx, pSy, pSz);
      printf("   in: pV=(%f, %f, %f)\n", pV[0], pV[1], pV[2]);
      printf("   in: oldReg=%i oldLttc=%i\n", oldReg, oldLttc);
   }   
   flagErr = 0;
   Double_t epsil = 1000.*TGeoShape::Tolerance();
   TGeoNode *node = gGeoManager->FindNode(pSx+epsil*pV[0], pSy+epsil*pV[1], pSz+epsil*pV[2]);
   if (gGeoManager->IsOutside()) {
      newReg = gMCGeom->NofVolumes()+2;
      newLttc = TFlukaMCGeometry::kLttcOutside;
      gGeoManager->SetOutside(kFALSE);
      if (oldLttc>0 && oldLttc<newLttc) gGeoManager->CdNode(oldLttc-1);
      return;
   } 
   gGeoManager->SetOutside(kFALSE);
   newReg = node->GetVolume()->GetNumber();
   newLttc = gGeoManager->GetCurrentNodeId()+1;
   if (oldLttc==TFlukaMCGeometry::kLttcOutside || oldLttc==0) return;

   Int_t dummy = gFluka->GetDummyRegion();
   if (oldReg==dummy) {
      Int_t newreg1, newlttc1;
      gMCGeom->GetNextRegion(newreg1, newlttc1);
      if (newreg1==newReg && newlttc1==newLttc) {
         newReg = dummy;
         newLttc = TFlukaMCGeometry::kLttcVirtual;
         flagErr = newReg;
         if (gMCGeom->IsDebugging()) printf("  virtual boundary (oldReg==dummy) !! newReg=%i newLttc=%i\n", newReg, newLttc);
      }
      return;
   }

   if (oldReg==newReg && oldLttc!=newLttc) {
      newReg  = dummy;
      newLttc = TFlukaMCGeometry::kLttcVirtual;
      if (gMCGeom->IsDebugging()) printf("  virtual boundary!! newReg=%i newLttc=%i\n", newReg, newLttc);
   }

   if( oldReg!=newReg && oldLttc==newLttc ) {
      // this should not happen!! ??? Ernesto
//       cout << "  lkwr      oldReg!=newReg ("<< oldReg <<"!="<< newReg
//            << ") && oldLttc==newLttc ("<< newLttc <<") !!!!!!!!!!!!!!!!!" << endl;
      newReg  = dummy;
      newLttc = TFlukaMCGeometry::kLttcVirtual;
      flagErr = newReg;
   }

   if (gMCGeom->IsDebugging()) {
      printf("  LKWR: newReg=%i newLttc=%i\n", newReg, newLttc);
   }   
}

//_____________________________________________________________________________
void nrmlwr(Double_t &pSx, Double_t &pSy, Double_t &pSz,
            Double_t &pVx, Double_t &pVy, Double_t &pVz,
            Double_t *norml, const Int_t &oldReg,
            const Int_t &newReg, Int_t &flagErr)
{
   if (gMCGeom->IsDebugging()) {
      printf("========== Inside NRMLWR (%g, %g, %g, %g, %g, %g)\n", pSx,pSy,pSz,pVx,pVy,pVz);
      printf("                         (%g, %g, %g)\n", NORLAT.xn[0], NORLAT.xn[1], NORLAT.xn[2]);
      printf("   oldReg=%i, newReg=%i\n", oldReg,newReg);
   }   
   gGeoManager->SetCurrentPoint(NORLAT.xn[0], NORLAT.xn[1], NORLAT.xn[2]);
   gGeoManager->SetCurrentDirection(pVx, pVy, pVz);
   Double_t *dnorm = gGeoManager->FindNormalFast();
   flagErr = 0;
   if (!dnorm) {
      printf("   ERROR: Cannot compute fast normal\n");
      flagErr = 1;
      norml[0] = -pVx;   
      norml[1] = -pVy;   
      norml[2] = -pVz; 
   } else {
      norml[0] = -dnorm[0];
      norml[1] = -dnorm[1];
      norml[2] = -dnorm[2];
   }  

   if (gMCGeom->IsDebugging()) {
      printf("   normal to boundary: (%g, %g, %g)\n", norml[0], norml[1], norml[2]);  
      printf("<= NRMLWR\n");
   }

}

//_____________________________________________________________________________
void rgrpwr(const Int_t & /*flukaReg*/, const Int_t & /*ptrLttc*/, Int_t & /*g4Reg*/,
            Int_t * /*indMother*/, Int_t * /*repMother*/, Int_t & /*depthFluka*/)
{
   if (gMCGeom->IsDebugging()) printf("=> Dummy RGRPWR\n");
}

//_____________________________________________________________________________
Int_t isvhwr(const Int_t &check, const Int_t & intHist)
{
//   from FLUGG:
// Wrapper for saving current navigation history (fCheck=default) 
// and returning its pointer. If fCheck=-1 copy of history pointed 
// by intHist is made in NavHistWithCount object, and its pointer 
// is returned. fCheck=1 and fCheck=2 cases are only in debugging 
// version: an array is created by means of FGeometryInit functions
// (but could be a static int * ptrArray = new int[10000] with 
// file scope as well) that stores a flag for deleted/undeleted 
// histories and at the end of event is checked to verify that 
// all saved history objects have been deleted.

// For TGeo, just return the current node ID. No copy need to be made.

   if (gMCGeom->IsDebugging()) printf("=> Inside ISVHWR check=%d intHist=%d\n", check, intHist);
   if (check<0) return intHist;
   Int_t histInt = gGeoManager->GetCurrentNodeId()+1;
   if (gMCGeom->IsDebugging()) printf("<= ISVHWR: history is: %i in: %s\n", histInt, gGeoManager->GetPath());
   return histInt;
}



   
