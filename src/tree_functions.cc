//////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include <iostream>

#include "../interface/full_analyzer.h"

void full_analyzer::fill_BkgEstimator_tree(BkgEstimator& bkgestimator)
{
    bkgestimator._gen_Nmass    = _gen_Nmass;
    bkgestimator._gen_NV       = _gen_NV;
    bkgestimator._gen_Nctau     = _gen_Nctau;
    bkgestimator._JetIsFromHNL = get_JetIsFromHNL(i_jetl2);
    bkgestimator._JetPt        = _jetPt[i_jetl2];
    bkgestimator._JetEta       = _jetEta[i_jetl2];
    bkgestimator._JetPhi       = _jetPhi[i_jetl2];
    bkgestimator._lPt                   = _lPt[i_subleading];
    bkgestimator._lEta                  = _lEta[i_subleading];
    bkgestimator._lPhi                  = _lPhi[i_subleading];
    bkgestimator._ldxy                  = _dxy[i_subleading];
    bkgestimator._ldz                   = _dz[i_subleading];
    bkgestimator._l3dIPSig              = _3dIPSig[i_subleading];
    bkgestimator._lrelIso               = _relIso[i_subleading];
    bkgestimator._lptRel                = _ptRel[i_subleading];
    bkgestimator._lptRatio              = _ptRatio[i_subleading];
    bkgestimator._lNumberOfHits         = _lNumberOfValidTrackerHits[i_subleading];
    bkgestimator._lNumberOfPixelHits    = _lNumberOfValidPixelHits[i_subleading];

    bkgestimator._l1Pt            = _lPt[i_leading];
    bkgestimator._l1Eta           = _lEta[i_leading];
    bkgestimator._l1Phi           = _lPhi[i_leading];
    bkgestimator._mll             = mll;
    bkgestimator._mlljet          = 0;//maybe add it?
    bkgestimator._dRll            = dRll;
    bkgestimator._dphill          = dphill;
    bkgestimator._dRljet          = dRljet;

    bkgestimator._SV_PVSVdist     = IVF_PVSVdist;
    bkgestimator._SV_PVSVdist_2D  = IVF_PVSVdist_2D;
    bkgestimator._SV_ntracks      = _IVF_ntracks[i_subleading];
    bkgestimator._SV_normchi2     = fabs(_IVF_chi2[i_subleading]/_IVF_df[i_subleading]);
    bkgestimator._SV_mass         = SVmass;
    bkgestimator._SV_l1mass       = SVl1mass;
    bkgestimator._SV_pt           = SVpt;
    bkgestimator._SV_eta          = SVeta;
    bkgestimator._SV_phi          = SVphi;

    bkgestimator.fill_tree();
}
