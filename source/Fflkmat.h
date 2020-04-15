#include "cfortran.h"
#include "Rtypes.h"

#include "Fdimpar.h"

extern "C" {
/*$ CREATE FLKMAT.ADD
*COPY FLKMAT
*
*----------------------------------------------------------------------*
*                                                                      *
*     Partial (some variables come from FLUKA87)                       *
*     Copyright (C) 1996-2010      by        Alfredo Ferrari           *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*     FLuKa MATerial properties and atomic data                        *
*                                                                      *
*     Version for Fluka91/.../2010/...:                                *
*                                                                      *
*     Last change on  13-Sep-10    by  Alfredo Ferrari, INFN-Milan     *
*                                                                      *
*                                                                      *
*     This common contains the basic properties of the materials used  *
*     in the FLUKA run. Other properties are recorded in specialized   *
*     commons (ie for dE/dx etc)                                       *
*                                                                      *
*     Aocmbm(i) = Atomic density of the i_th material in barn^-1 cm^-1 *
*                 (Atoms Over Cm times Barn for Materials)             *
*     Eocmbm(i) = Electron density of the i_th material in barn^-1cm^-1*
*                 (Electrons Over Cm times Barn for Materials)         *
*     Cberho(i) = Conduction band electron density of the i_th material*
*       Amss(i) = Atomic weight (g/mole) of the i_th material          *
*     Amssem(i) = "Effective" i_th material atomic weight for the para-*
*                 metrized EM cascade                                  *
*        Rho(i) = Density of the i_th material                         *
*       Ztar(i) = Atomic number of the i_th material                   *
*     Zsqtar(i) = Squared atomic number of the i_th material           *
*     Ztarem(i) = "Effective" atomic number for the i_th material for  *
*                 the parametrized EM cascade                          *
*     Ainlng(i) = Inelastic scattering length of the i_th material     *
*                 for beam particles at the average beam energy in cm  *
*     Aellng(i) = Elastic scattering length of the i_th material for   *
*                 beam particles at average beam energy in cm          *
*      X0rad(i) = Radiation length of the i_th material in cm          *
*     Dmgene(i) = Damage energy of the i_th material (GeV)             *
*     Ainnth(i) = Inelastic scattering length of the i_th material     *
*                 for neutrons at threshold energy in cm               *
*   Medflk(k,j) = Material number of the k_th region, for prompt (j=1) *
*                 or radioactive decay (j=2) particles                 *
*     Mulflg(i) = Flags for multiple scattering options for the i_th   *
*                 material                                             *
*      Icomp(i) = Starting address in the Matnum array if the i_th     *
*                 material is a compound/mixture, 0 otherwise          *
*     Mssnum(i) = Mass number of the target nucleus for the i_th mater-*
*                 ial, if =< 0 it means that it is in the natural isot-*
*                 opic composition                                     *
*     Msindx(i) = Index for tabulations for the given isotope of the   *
*                 target nucleus (meaningful only for mssnum > 0)      *
*                 that it is in the natural isotopic composition       *
*     Lcmpnd(i) = logical flag for real compounds versus mixtures      *
*     Imetal(i) = flag for metallic materials (1 if metallic, -1       *
*                 otherwise)                                           *
*     Libsnm(i) = flag whether inelastic interaction biasing must be   *
*                 done for this medium                                 *
*     Matnam(i) = Alphabetical name of the i_th material number        *
*        Nmtibs = number of materials to which inelastic biasing       *
*                 applies                                              *
*        Nregs  = total number of regions                              *
*        Nregcg = total number of combinatorial geometry regions       *
*        Nmat   = total number of materials used in the problem        *
*        Matqlt = special extra material (water) for Q(L) calculations *
*        Mrgqlt = special region with the extra material (water) for   *
*                 Q(L) calculations                                    *
*                                                                      *
*                        Mxxmdf = maximum number of materials          *
*                        Mxxrgn = maximum number of regions            *
*                                                                      *
*----------------------------------------------------------------------*
*
      CHARACTER*8 MATNAM
      LOGICAL     LCMPND, LIBSNM
      COMMON / FLKMAT / AOCMBM(MXXMDF), EOCMBM(MXXMDF), CBERHO(MXXMDF),
     &                  AMSS  (MXXMDF), AMSSEM(MXXMDF), RHO   (MXXMDF),
     &                  ZTAR  (MXXMDF), ZTAREM(MXXMDF), ZSQTAR(MXXMDF),
     &                  AINLNG(MXXMDF), AELLNG(MXXMDF), X0RAD (MXXMDF),
     &                  AINNTH(MXXMDF), DMGENE(MXXMDF),
     &                  MEDFLK(MXXRGN,2),               MULFLG(MXXMDF),
     &                  ICOMP (MXXMDF), MSSNUM(MXXMDF), MSINDX(MXXMDF),
     &                  IMETAL(MXXMDF), LCMPND(MXXMDF), LIBSNM(MXXMDF),
     &                  NMTIBS, NREGS , NMAT  , NREGCG, MATQLT, MRGQLT
      COMMON / CHFLKM / MATNAM(MXXMDF)
      SAVE / FLKMAT /
      SAVE / CHFLKM /
*/

    typedef struct {
	Double_t aocmbm[mxxmdf];
	Double_t eocmbm[mxxmdf];
        Double_t cberho[mxxmdf];
	Double_t amss  [mxxmdf];
	Double_t amssem[mxxmdf];
	Double_t rho   [mxxmdf];
	Double_t ztar  [mxxmdf];
	Double_t ztarem[mxxmdf];
	Double_t zsqtar[mxxmdf];
	Double_t ainlng[mxxmdf];
	Double_t aellng[mxxmdf];
	Double_t x0rad [mxxmdf];
	Double_t ainnth[mxxmdf];
        Double_t dmgene[mxxmdf];
        Int_t    medflk[2][mxxrgn];
        Int_t    mulflg[mxxmdf];
        Int_t    icomp[mxxmdf];
	Int_t    mssnum[mxxmdf];
        Int_t    msindx[mxxmdf];
        Int_t    imetal[mxxmdf];
	Int_t    lcmpnd[mxxmdf];
        Int_t    libsnm[mxxmdf];
        Int_t    nmtibs;
	Int_t    nregs;
	Int_t    nmat;
	Int_t    nregcg;
        Int_t    matqlt;
        Int_t    mrgqlt;
        Int_t    mrgext;
    } flkmatCommon;
#define FLKMAT COMMON_BLOCK(FLKMAT,flkmat)
    COMMON_BLOCK_DEF(flkmatCommon, FLKMAT);
}
