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
    bkgestimator._mll             = get_mll(i_leading, i_subleading);
    bkgestimator._mlljet          = 0;//maybe add it?
    bkgestimator._dRll            = get_dRll(i_leading, i_subleading);
    bkgestimator._dphill          = get_dphill(i_leading, i_subleading);
    bkgestimator._dRljet          = get_dR_lepton_jet(i_subleading, i_jetl2);

    bkgestimator._SV_PVSVdist     = get_IVF_PVSVdist(i_subleading);
    bkgestimator._SV_PVSVdist_2D  = get_IVF_PVSVdist_2D(i_subleading);
    bkgestimator._SV_ntracks      = _IVF_ntracks[i_subleading];
    bkgestimator._SV_normchi2     = fabs(_IVF_chi2[i_subleading]/_IVF_df[i_subleading]);
    LorentzVector tracksum;
    LorentzVector l1_vec(_lPt[i_leading], _lEta[i_leading], _lPhi[i_leading], _lE[i_leading]);
    for(unsigned i_track = 0; i_track < _IVF_ntracks[i_subleading]; i_track++){
        LorentzVector tmptrack(_IVF_trackpt[i_subleading][i_track], _IVF_tracketa[i_subleading][i_track], _IVF_trackphi[i_subleading][i_track], _IVF_trackE[i_subleading][i_track]);
        tracksum += tmptrack;
    }
    bkgestimator._SV_mass               = tracksum.mass();
    bkgestimator._SV_l1mass             = (tracksum + l1_vec).mass();
    bkgestimator._SV_pt                 = tracksum.pt();
    bkgestimator._SV_eta                = tracksum.eta();
    bkgestimator._SV_phi                = tracksum.phi();

    bkgestimator.fill_tree();
}
