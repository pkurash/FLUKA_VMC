#include <Riostream.h>
#include "TVirtualMCApplication.h"
#include "TFluka.h"
#include "TFlukaCodes.h"
#include "Fdimpar.h"  //(DIMPAR) fluka include
#include "Fdblprc.h"  //(DBLPRC) fluka include
#include "Fiounit.h"  //(IOUNIT) fluka include

#ifndef WIN32
# define usrmed usrmed_
#else
# define usrmed USRMED
#endif


extern "C" {
  void usrmed(Int_t& ij, Double_t& eksco,  Double_t& pla,
	      Double_t& wee, Int_t& mreg, Int_t& newreg,
	      Double_t& xx,  Double_t& yy, Double_t& zz,
	      Double_t& txx,  Double_t& tyy, Double_t& tzz,
	      Double_t& txxpol,  Double_t& tyypol, Double_t& tzzpol)
{
/*
*     Input variables:                                                 *
*             ij = particle id                                         *
*          Eksco = particle kinetic energy (GeV)                       *
*            Pla = particle momentum (GeV/c)                           *
*            Wee = particle weight                                     *
*           Mreg = (original) region number                            *
*         Newreg = (final)    region number                            *
*       Xx,Yy,Zz = particle position                                   *
*    Txx,Tyy,Tzz = particle direction                                  *
* Txx,Tyy,Tzzpol = particle polarization direction                     *
*                                                                      *
*     The user is supposed to change only WEE if MREG = NEWREG and     *
*     WEE, NEWREG, TXX, TYY, TZZ (TXXPOL, TYYPOL, TZZPOL) if           *
*     MREG .NE. NEWREG                                                 *
*   
*/
  
  TFluka *fluka = (TFluka*)gMC;
  // stop particle on user request
  if (fluka->GetStoppingCondition()) {
    wee = -1.;
    fluka->ResetStoppingCondition();
  }
} // end of usrmed
} // end of extern "C"

