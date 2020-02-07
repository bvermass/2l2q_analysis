//////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include <iostream>

#include "../interface/full_analyzer.h"

void full_analyzer::fill_BkgEstimator_tree(BkgEstimator& bkgestimator, double event_weight)
{
    bkgestimator._weight       = event_weight;
    bkgestimator._gen_Nmass    = _gen_Nmass;
    bkgestimator._gen_NV       = _gen_NV;
    bkgestimator._gen_Nctau     = _gen_Nctau;
    bkgestimator._JetIsFromHNL = get_JetIsFromHNL(i_jetl2);
    bkgestimator._nTightJet    = nTightJet;
    bkgestimator._JetPt        = _jetPt[i_jetl2];
    bkgestimator._JetEta       = _jetEta[i_jetl2];
    bkgestimator._JetPhi       = _jetPhi[i_jetl2];
    bkgestimator._nTightLep             = nTightEle + nTightMu;
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
    bkgestimator._lFlavor               = _lFlavor[i_subleading];
    bkgestimator._lCharge               = _lCharge[i_subleading];

    bkgestimator._l1Pt            = _lPt[i_leading];
    bkgestimator._l1Eta           = _lEta[i_leading];
    bkgestimator._l1Phi           = _lPhi[i_leading];
    bkgestimator._l1Flavor        = _lFlavor[i_leading];
    bkgestimator._l1Charge        = _lCharge[i_leading];
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

    bkgestimator._nMV2            = 0;
    for(auto& MassMap : JetTagVal){
        for(auto& V2Map : MassMap.second){
            if(bkgestimator._nMV2 >= 100){
                std::cout << "error: more than 100 MV2 points, increase size of nMV2_max in BkgEstimator arrays" << std::endl;
                break;
            }
            bkgestimator._evaluating_mass[bkgestimator._nMV2]       = MassMap.first;
            bkgestimator._evaluating_V2[bkgestimator._nMV2]         = V2Map.first;
            bkgestimator._JetTagVal[bkgestimator._nMV2]             = V2Map.second;
            bkgestimator._reweighting_weight[bkgestimator._nMV2]    = reweighting_weights[V2Map.first];
            bkgestimator._nMV2++;
        }
    }

    bkgestimator.fill_tree();
}
