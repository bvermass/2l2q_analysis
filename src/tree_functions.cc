//////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include <iostream>

#include "../interface/full_analyzer.h"

void full_analyzer::fill_BkgEstimator_tree(BkgEstimator& bkgestimator, double event_weight, double total_weight)
{
    bkgestimator._is2016       = _is2016;
    bkgestimator._is2017       = _is2017;
    bkgestimator._is2018       = _is2018;
    bkgestimator._gen_Nmass    = HNL_param->mass;
    bkgestimator._gen_NV2      = HNL_param->V2;
    bkgestimator._gen_Nctau    = HNL_param->ctau;
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
    bkgestimator._lProvenance           = _lProvenance[i_subleading];
    bkgestimator._lProvenanceCompressed = _lProvenanceCompressed[i_subleading];

    bkgestimator._l1Pt            = _lPt[i_leading];
    bkgestimator._l1Eta           = _lEta[i_leading];
    bkgestimator._l1Phi           = _lPhi[i_leading];
    bkgestimator._l1Flavor        = _lFlavor[i_leading];
    bkgestimator._l1Charge        = _lCharge[i_leading];
    bkgestimator._l1Provenance           = _lProvenance[i_leading];
    bkgestimator._l1ProvenanceCompressed = _lProvenanceCompressed[i_leading];
    bkgestimator._mll             = mll;
    bkgestimator._mlljet          = 0;//maybe add it?
    bkgestimator._dRll            = dRll;
    bkgestimator._dphill          = dphill;
    bkgestimator._dRljet          = dRljet;

    bkgestimator._SV_PVSVdist     = IVF_PVSVdist;
    bkgestimator._SV_PVSVdist_2D  = IVF_PVSVdist_2D;
    bkgestimator._SV_genreco      = IVF_SVgenreco;
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
            if(bkgestimator._nMV2 >= 150){
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

    bkgestimator._weight            = event_weight;
    bkgestimator._RawWeight         = _weight*total_weight;
    bkgestimator._PileUpSF          = puweightreader->get_PUWeight_Central(_nTrueInt);
    bkgestimator._PileUpSF_unc_up   = puweightreader->get_PUWeight_Up(_nTrueInt) - puweightreader->get_PUWeight_Central(_nTrueInt);
    bkgestimator._PileUpSF_unc_down = puweightreader->get_PUWeight_Central(_nTrueInt) - puweightreader->get_PUWeight_Down(_nTrueInt);
    bkgestimator._TrackSF           = highest_trackpt_weight;
    bkgestimator._TrackSF_unc_sym   = std::abs(1. - highest_trackpt_weight)/2;
    if(_lFlavor[i_leading] == 0){//electron scale factors
        bkgestimator._l1_IDSF           = lsfreader_e_ID->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
        bkgestimator._l1_IDSF_unc_sym   = lsfreader_e_ID->get_LSF_BinError(_lPt[i_leading], _lEtaSC[i_leading]);
        bkgestimator._l1_ISOSF          = 1.;
        bkgestimator._l1_ISOSF_unc_sym  = 0.;
        bkgestimator._TriggerSF         = lsfreader_e_trig->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
        bkgestimator._TriggerSF_unc_sym = lsfreader_e_trig->get_LSF_BinError(_lPt[i_leading], _lEtaSC[i_leading]);
    }else if(_lFlavor[i_leading] == 1){//muon scale factors
        bkgestimator._l1_IDSF           = lsfreader_m_ID->get_LSF(_lPt[i_leading], _lEta[i_leading]);
        double l1_IDSF_unc_stat         = lsfreader_m_ID->get_LSF_BinError(_lPt[i_leading], _lEta[i_leading]);
        double l1_IDSF_unc_syst         = lsfreader_m_IDsys->get_sys_as_BinError(_lPt[i_leading], _lEta[i_leading]);
        bkgestimator._l1_IDSF_unc_sym   = sqrt(l1_IDSF_unc_stat*l1_IDSF_unc_stat + l1_IDSF_unc_syst*l1_IDSF_unc_syst);//add stat and syst error in uncorrelated way
        bkgestimator._l1_ISOSF          = lsfreader_m_ISO->get_LSF(_lPt[i_leading], _lEta[i_leading]);
        double l1_ISOSF_unc_stat        = lsfreader_m_ISO->get_LSF_BinError(_lPt[i_leading], _lEta[i_leading]);
        double l1_ISOSF_unc_syst        = lsfreader_m_ISO->get_sys_as_BinContent(_lPt[i_leading], _lEta[i_leading]);
        bkgestimator._l1_ISOSF_unc_sym  = sqrt(l1_ISOSF_unc_stat*l1_ISOSF_unc_stat + l1_ISOSF_unc_syst*l1_ISOSF_unc_syst);
        bkgestimator._TriggerSF         = lsfreader_m_trig->get_LSF(_lPt[i_leading], _lEta[i_leading]);
        bkgestimator._TriggerSF_unc_sym = lsfreader_m_trig->get_LSF_BinError(_lPt[i_leading], _lEta[i_leading]);
    }
    //l2
    if(_lFlavor[i_subleading] == 0){//electron
        bkgestimator._l2_IDSF           = get_displEleSF(_lPt[i_subleading], _dxy[i_subleading]);
        bkgestimator._l2_IDSF_unc_sym   = get_displEleSF_unc(_lPt[i_subleading], _dxy[i_subleading]);
    }else if(_lFlavor[i_subleading] == 1){//muon
        //bkgestimator._l2_IDSF           = lsfreader_displ_m_ID->get_LSF(_lPt[i_subleading], _lEta[i_subleading])*sqrt(lsfreader_displ_m_SV->get_LSF(_lPt[i_subleading]*2, IVF_PVSVdist_2D));
        bkgestimator._l2_IDSF           = 1.;
        double l2_IDSF_unc_syst         = get_displMuonSF_unc(IVF_PVSVdist_2D, _lPt[i_subleading]);
        double l2_SVSF_unc_syst         = std::abs(1. - sqrt(lsfreader_displ_m_SV->get_LSF(_lPt[i_subleading]*2, IVF_PVSVdist_2D))) / 2;
        bkgestimator._l2_IDSF_unc_sym   = sqrt(l2_IDSF_unc_syst*l2_IDSF_unc_syst + l2_SVSF_unc_syst*l2_SVSF_unc_syst);
    }


    bkgestimator.fill_tree();
}
