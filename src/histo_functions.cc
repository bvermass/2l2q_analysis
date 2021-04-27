//////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include <iostream>

#include "../interface/full_analyzer.h"

using namespace std;


void full_analyzer::add_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix){
    add_general_histograms(hists, hists2D, prefix);
    add_jet_histograms(hists, prefix);
    add_gen_histograms(hists, hists2D, prefix);
    //add_KVF_eff_histograms(hists, prefix);
    add_chargeflip_histograms(hists, hists2D, prefix);
}


void full_analyzer::add_general_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix){
    // Plotting histograms
    //(*hists)[prefix+"_l2_jets_categories"]              = new TH1F(prefix+"_l2_jets_categories", ";;Events", 8, 0, 8);
    //(*hists)[prefix+"_jets_categories"]                 = new TH1F(prefix+"_jets_categories", ";;Events", 4, 0, 4);
    //(*hists)[prefix+"_PVSVdxyz_categories"]             = new TH1F(prefix+"_PVSVdxyz_categories", ";;Events", 8, 0, 8);
    //(*hists)[prefix+"_PVSVdxy_categories"]              = new TH1F(prefix+"_PVSVdxy_categories", ";;Events", 8, 0, 8);
    //(*hists)[prefix+"_MVAvsPOGMedium_categories"]       = new TH1F(prefix+"_MVAvsPOGMedium_categories", ";;Events", 4, 0, 4);
    //(*hists)[prefix+"_deltaphivsR_categories"]          = new TH1F(prefix+"_deltaphivsR_categories", ";;Events", 4, 0, 4);

    (*hists)[prefix+"_nTightEle"]                       = new TH1F(prefix+"_nTightEle", ";N_{prompt electron};Events", 10, 0, 10);
    (*hists)[prefix+"_nTightMu"]                        = new TH1F(prefix+"_nTightMu", ";N_{prompt muon};Events", 10, 0, 10);
    (*hists)[prefix+"_nTight"]                          = new TH1F(prefix+"_nTight", ";N_{prompt e,mu};Events", 10, 0, 10);
    (*hists)[prefix+"_nDisplEle"]                       = new TH1F(prefix+"_nDisplEle", ";N_{displ electron};Events", 10, 0, 10);
    (*hists)[prefix+"_nDisplMu"]                        = new TH1F(prefix+"_nDisplMu", ";N_{displ muon};Events", 10, 0, 10);
    (*hists)[prefix+"_nDispl"]                          = new TH1F(prefix+"_nDispl", ";N_{displ e,mu};Events", 10, 0, 10);
    (*hists)[prefix+"_nTightDispl"]                     = new TH1F(prefix+"_nTightDispl", ";N_{e,mu};Events", 10, 0, 10);
    (*hists)[prefix+"_nDispleAndmu"]                     = new TH1F(prefix+"_nDispleAndmu", ";;Events", 3, 0, 3);
    (*hists)[prefix+"_nJets_uncl"]                      = new TH1F(prefix+"_nJets_uncl", ";N_{jets(uncl.)};Events", 10, 0, 10);
    (*hists)[prefix+"_nJets_cl"]                        = new TH1F(prefix+"_nJets_cl", ";N_{jets(cl.)};Events", 10, 0, 10);
    (*hists)[prefix+"_l1_pt"]                           = new TH1F(prefix+"_l1_pt", ";l_{1} #it{p}_{T} [GeV];Events", 30, 0, 100);
    (*hists)[prefix+"_l2_pt"]                           = new TH1F(prefix+"_l2_pt", ";l_{2} #it{p}_{T} [GeV];Events", 30, 0, 50);
    (*hists)[prefix+"_llptdiff"]                        = new TH1F(prefix+"_llptdiff", ";l_{1} #it{p}_{T} - l_{2} #it{p}_{T} [GeV];Events", 30, -50, 100);
    (*hists)[prefix+"_l1_eta"]                          = new TH1F(prefix+"_l1_eta", ";l_{1} #eta;Events", 30, -3, 3);
    (*hists)[prefix+"_l2_eta"]                          = new TH1F(prefix+"_l2_eta", ";l_{2} #eta;Events", 30, -3, 3);
    (*hists)[prefix+"_l1_dxy"]                          = new TH1F(prefix+"_l1_dxy", ";l_{1} dxy [cm];Events", 30, 0, 0.02);
    (*hists)[prefix+"_l2_dxy"]                          = new TH1F(prefix+"_l2_dxy", ";l_{2} dxy [cm];Events", 30, 0, 0.5);
    (*hists)[prefix+"_l1_dz"]                           = new TH1F(prefix+"_l1_dz", ";l_{1} dz [cm];Events", 30, 0, 0.05);
    (*hists)[prefix+"_l2_dz"]                           = new TH1F(prefix+"_l2_dz", ";l_{2} dz [cm];Events", 30, 0, 2);
    (*hists)[prefix+"_l1_reliso"]                       = new TH1F(prefix+"_l1_reliso", ";l_{1} Rel Iso;Events", 30, 0, 0.05);
    (*hists)[prefix+"_l2_reliso"]                       = new TH1F(prefix+"_l2_reliso", ";l_{2} Rel Iso;Events", 30, 0, 3.5);
    (*hists)[prefix+"_l2_reliso_zoom"]                  = new TH1F(prefix+"_l2_reliso_zoom", ";l_{2} Rel Iso;Events", 30, 0, 0.5);
    (*hists)[prefix+"_l1_ptrel"]                        = new TH1F(prefix+"_l1_ptrel", ";l_{1} #it{p}_{T}^{rel} [GeV];Events", 30, 0, 40);
    (*hists)[prefix+"_l2_ptrel"]                        = new TH1F(prefix+"_l2_ptrel", ";l_{2} #it{p}_{T}^{rel} [GeV];Events", 30, 0, 10);
    (*hists)[prefix+"_l1_ptratio"]                      = new TH1F(prefix+"_l1_ptratio", ";l_{1} #it{p}_{T}^{ratio} [GeV];Events", 30, 0.75, 1);
    (*hists)[prefix+"_l2_ptratio"]                      = new TH1F(prefix+"_l2_ptratio", ";l_{2} #it{p}_{T}^{ratio} [GeV];Events", 30, 0, 1);
    (*hists)[prefix+"_l1_selectedTrackMult"]            = new TH1F(prefix+"_l1_selectedTrackMult", ";l_{1} selectedTrackMult;Events", 6, 0, 6);
    (*hists)[prefix+"_l2_selectedTrackMult"]            = new TH1F(prefix+"_l2_selectedTrackMult", ";l_{2} selectedTrackMult;Events", 15, 0, 15);
    (*hists)[prefix+"_l1_3dIPSig"]                      = new TH1F(prefix+"_l1_3dIPSig", ";l_{1} 3dIPSig;Events", 30, 0, 4);
    (*hists)[prefix+"_l2_3dIPSig"]                      = new TH1F(prefix+"_l2_3dIPSig", ";l_{2} 3dIPSig;Events", 30, 0, 40);
    (*hists)[prefix+"_l2_NumberOfHits"]                 = new TH1F(prefix+"_l2_NumberOfHits", ";l_{2} Nr. of Tracker Hits;Events", 20, 0, 20);
    (*hists)[prefix+"_l2_NumberOfPixelHits"]            = new TH1F(prefix+"_l2_NumberOfPixelHits", ";l_{2} Nr. of Pixel Hits;Events", 15, 0, 15);
    (*hists2D)[prefix+"_l2_ptvsctau"]                   = new TH2F(prefix+"_l2_ptvsctau", ";l_{2} #it{p}_{T} [GeV]; c#tau [mm]", 20, 0, 60, 20, 0, 100);
    (*hists2D)[prefix+"_lsources"]                      = new TH2F(prefix+"_lsources", ";l1 source;l2 source", 14, -2, 12, 14, -2, 12);
    (*hists2D)[prefix+"_lprovenance"]                   = new TH2F(prefix+"_lprovenance", ";l1 source;l2 source", 19, 0, 19, 19, 0, 19);
    (*hists2D)[prefix+"_lprovenanceCompressed"]         = new TH2F(prefix+"_lprovenanceCompressed", ";l1 source;l2 source", 5, 0, 5, 5, 0, 5);
    (*hists2D)[prefix+"_l2provCompressedvsConversion"]  = new TH2F(prefix+"_l2provCompressedvsConversion", ";l2 Provenance;l2 Conversion", 5, 0, 5, 4, 0, 4);
    (*hists)[prefix+"_met"]                             = new TH1F(prefix+"_met", ";MET [GeV];Events", 30, 0, 150);
    (*hists)[prefix+"_mll"]                             = new TH1F(prefix+"_mll", ";#it{m}_{ll} [GeV];Events", 30, 0, 200);
    (*hists)[prefix+"_mll_zoomAtLowMll"]                = new TH1F(prefix+"_mll_zoomAtLowMll", ";#it{m}_{ll} [GeV];Events", 100, 0, 30);
    (*hists)[prefix+"_integral"]                        = new TH1F(prefix+"_integral", ";Integral Yield;Events", 1, 0, 1);
    (*hists)[prefix+"_dphill"]                          = new TH1F(prefix+"_dphill", ";#it{#Delta #phi}_{ll};Events", 30, 0, 3.14);
    (*hists)[prefix+"_dRll"]                            = new TH1F(prefix+"_dRll", ";#it{#Delta R}_{ll};Events", 30, 0, 6);
    (*hists)[prefix+"_l1_IVF_match"]                    = new TH1F(prefix+"_l1_IVF_match", ";l1 IVF match (IVF);Events", 2, 0, 2);
    (*hists)[prefix+"_l2_IVF_match"]                    = new TH1F(prefix+"_l2_IVF_match", ";l2 IVF match (IVF);Events", 2, 0, 2);
    
    (*hists)[prefix+"_IVF_normchi2"]                    = new TH1F(prefix+"_IVF_normchi2", ";Normalized #Chi^{2} (IVF);Events", 30, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxy"]                    = new TH1F(prefix+"_IVF_PV-SVdxy", ";L_{xy} [cm];Events", 20, 0, 60);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom"]               = new TH1F(prefix+"_IVF_PV-SVdxy_zoom", ";L_{xy} [cm];Events", 20, 0, 20);
    (*hists)[prefix+"_IVF_PV-SVdxyz"]                   = new TH1F(prefix+"_IVF_PV-SVdxyz", ";L_{xyz} [cm];Events", 20, 0, 100);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom"]              = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom", ";L_{xyz} [cm];Events", 20, 0, 20);
    (*hists)[prefix+"_IVF_ntracks"]                     = new TH1F(prefix+"_IVF_ntracks", ";# of tracks used in SVfit;Events", 15, 0, 15);
    (*hists)[prefix+"_IVF_mass"]                        = new TH1F(prefix+"_IVF_mass", ";SV Mass [GeV];Events", 30, 0, 10);
    (*hists)[prefix+"_IVF_l1mass"]                      = new TH1F(prefix+"_IVF_l1mass", ";l_{1}+SV Mass [GeV];Events", 30, 0, 140);
    (*hists)[prefix+"_IVF_massminl2"]                   = new TH1F(prefix+"_IVF_massminl2", ";SV mass (without l_{2}) [GeV];Events", 20, 0, 20);
    (*hists)[prefix+"_IVF_massminl2_K0"]                = new TH1F(prefix+"_IVF_massminl2_K0", ";SV mass (without l_{2}) [GeV];Events", 20, 0.4, 0.6);
    (*hists)[prefix+"_IVF_costracks"]                   = new TH1F(prefix+"_IVF_costracks", ";cos(PV-SV, SV tracks);Events", 40, 0.9, 1.0);
    (*hists)[prefix+"_gen_PV-SVdxy"]                    = new TH1F(prefix+"_gen_PV-SVdxy", ";L_{xy} [cm];Events", 20, 0, 60);
    (*hists)[prefix+"_gen_PV-SVdxy_zoom"]               = new TH1F(prefix+"_gen_PV-SVdxy_zoom", ";L_{xy} [cm];Events", 20, 0, 20);
    (*hists)[prefix+"_gen_PV-SVdxyz"]                   = new TH1F(prefix+"_gen_PV-SVdxyz", ";L_{xyz} [cm];Events", 20, 0, 100);
    (*hists)[prefix+"_gen_PV-SVdxyz_zoom"]              = new TH1F(prefix+"_gen_PV-SVdxyz_zoom", ";L_{xyz} [cm];Events", 20, 0, 20);
    (*hists)[prefix+"_gen_SVntracks"]                   = new TH1F(prefix+"_gen_SVntracks", ";# of tracks used in SVfit;Events", 15, 0, 15);
    (*hists)[prefix+"_gen_SVmass"]                      = new TH1F(prefix+"_gen_SVmass", ";SV Mass [GeV];Events", 30, 0, 10);

    if(extensive_plots){
        (*hists)[prefix+"_l1_phi"]                          = new TH1F(prefix+"_l1_phi", ";l_{1} #phi;Events", 30, -3.14, 3.14);
        (*hists)[prefix+"_l2_phi"]                          = new TH1F(prefix+"_l2_phi", ";l_{2} #phi;Events", 30, -3.14, 3.14);
        (*hists)[prefix+"_l2_dxy_zoom"]                     = new TH1F(prefix+"_l2_dxy_zoom", ";l_{2} dxy [cm];Events", 30, 0, 0.05);
        (*hists)[prefix+"_l1_3dIP"]                         = new TH1F(prefix+"_l1_3dIP", ";l_{1} 3dIP;Events", 30, 0, 0.02);
        (*hists)[prefix+"_l2_3dIP"]                         = new TH1F(prefix+"_l2_3dIP", ";l_{2} 3dIP;Events", 30, 0, 0.5);

        //(*hists)[prefix+"_dRl2jet1_cl"]                     = new TH1F(prefix+"_dRl2jet1_cl", ";#it{#Delta R}(l_{2},jet_{1}^{cl});Events", 30, 0, 6);
        //(*hists)[prefix+"_dRl2jet2_cl"]                     = new TH1F(prefix+"_dRl2jet2_cl", ";#it{#Delta R}(l_{2},jet_{2}^{cl});Events", 30, 0, 6);
        //(*hists)[prefix+"_dRjet1jet2_cl"]                   = new TH1F(prefix+"_dRjet1jet2_cl", ";#it{#Delta R}(jet_{1}^{cl},jet_{2}^{cl});Events", 30, 0, 6);
        //(*hists2D)[prefix+"_dRl2jet1_2_cl"]                 = new TH2F(prefix+"_dRl2jet1_2_cl", ";#it{#Delta R}(l_{2}, jet_{1}^{cl});#it{#Delta R}(l_{2}, jet_{2}^{cl})", 30, 0, 6, 30, 0, 6);
        //(*hists)[prefix+"_dRl2jet1_uncl"]                   = new TH1F(prefix+"_dRl2jet1_uncl", ";#it{#Delta R}(l_{2},jet_{1}^{uncl});Events", 30, 0, 6);
        //(*hists)[prefix+"_dRl2jet2_uncl"]                   = new TH1F(prefix+"_dRl2jet2_uncl", ";#it{#Delta R}(l_{2},jet_{2}^{uncl});Events", 30, 0, 6);
        //(*hists)[prefix+"_dRjet1jet2_uncl"]                 = new TH1F(prefix+"_dRjet1jet2_uncl", ";#it{#Delta R}(jet_{1}^{uncl},jet_{2}^{uncl});Events", 30, 0, 6);
        //(*hists2D)[prefix+"_dRl2jet1_2_uncl"]               = new TH2F(prefix+"_dRl2jet1_2_uncl", ";#it{#Delta R}(l_{2}, jet_{1}^{uncl});#it{#Delta R}(l_{2}, jet_{2}^{uncl})", 30, 0, 6, 30, 0, 6);

        //(*hists)[prefix+"_KVF_chi2"]                        = new TH1F(prefix+"_KVF_chi2", ";#Chi^{2} (KVF);Events", 100, 0, 200);
        //(*hists)[prefix+"_KVF_normchi2"]                    = new TH1F(prefix+"_KVF_normchi2", ";Normalized #Chi^{2} (KVF);Events", 100, 0, 200);
        //(*hists)[prefix+"_KVF_normchi2_zoom"]               = new TH1F(prefix+"_KVF_normchi2_zoom", ";Normalized #Chi^{2} (KVF);Events", 20, 0, 30);
        //(*hists)[prefix+"_KVF_ntracks"]                     = new TH1F(prefix+"_KVF_ntracks", ";# of tracks used in Vtxfit (KVF);Events", 15, 0, 15);
        //(*hists)[prefix+"_KVF_valid"]                       = new TH1F(prefix+"_KVF_valid", ";is Vertex Valid? (KVF);Events", 2, 0, 2);
        //(*hists)[prefix+"_KVF_PV-SVdxy"]                    = new TH1F(prefix+"_KVF_PV-SVdxy", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 60);
        //(*hists)[prefix+"_KVF_PV-SVdxy_zoom"]               = new TH1F(prefix+"_KVF_PV-SVdxy_zoom", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 20);
        //(*hists)[prefix+"_KVF_PV-SVdxy_zoom2"]              = new TH1F(prefix+"_KVF_PV-SVdxy_zoom2", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 2);
        //(*hists)[prefix+"_KVF_PV-SVdxyz"]                   = new TH1F(prefix+"_KVF_PV-SVdxyz", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 100);
        //(*hists)[prefix+"_KVF_PV-SVdxyz_zoom"]              = new TH1F(prefix+"_KVF_PV-SVdxyz_zoom", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 20);
        //(*hists)[prefix+"_KVF_PV-SVdxyz_zoom2"]             = new TH1F(prefix+"_KVF_PV-SVdxyz_zoom2", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 2);
        //(*hists)[prefix+"_KVF_dRcut"]                       = new TH1F(prefix+"_KVF_dRcut", ";dR cone size (KVF);Events", 11, 0, 1.1);
        

        (*hists)[prefix+"_IVF_chi2"]                        = new TH1F(prefix+"_IVF_chi2", ";#Chi^{2} (IVF);Events", 30, 0, 10);
        (*hists)[prefix+"_IVF_normchi2_zoom"]               = new TH1F(prefix+"_IVF_normchi2_zoom", ";Normalized #Chi^{2} (IVF);Events", 20, 0, 1);
        (*hists)[prefix+"_IVF_df"]                          = new TH1F(prefix+"_IVF_df", ";# of degrees of freedom (IVF);Events", 15, 0, 5);
        (*hists)[prefix+"_IVF_cxy"]                         = new TH1F(prefix+"_IVF_cxy", ";cxy (IVF);Events", 15, 0, 0.4);
        (*hists)[prefix+"_IVF_cz"]                          = new TH1F(prefix+"_IVF_cz", ";cz (IVF);Events", 15, 0, 0.6);
        (*hists)[prefix+"_IVF_cxyz"]                        = new TH1F(prefix+"_IVF_cxyz", ";cxyz (IVF);Events", 15, 0, 1);
        (*hists)[prefix+"_IVF_trackpt"]                     = new TH1F(prefix+"_IVF_trackpt", ";track #it{p}_{T} (IVF);Events", 15, 0, 30);
        (*hists)[prefix+"_IVF_tracketa"]                    = new TH1F(prefix+"_IVF_tracketa", ";track #eta (IVF);Events", 15, -3, 3);
        (*hists)[prefix+"_IVF_trackphi"]                    = new TH1F(prefix+"_IVF_trackphi", ";track #phi (IVF);Events", 15, -3.14, 3.14);
        (*hists)[prefix+"_IVF_trackE"]                      = new TH1F(prefix+"_IVF_trackE", ";track Energy (IVF);Events", 15, 0, 40);
        (*hists)[prefix+"_IVF_trackcharge"]                 = new TH1F(prefix+"_IVF_trackcharge", ";track charge (IVF);Events", 15, -2, 2);
        (*hists)[prefix+"_IVF_pt"]                          = new TH1F(prefix+"_IVF_pt", ";SV #it{p}_{T} [GeV] (IVF);Events", 30, 0, 80);
        (*hists)[prefix+"_IVF_eta"]                         = new TH1F(prefix+"_IVF_eta", ";SV #eta (IVF);Events", 15, -3, 3);
        (*hists)[prefix+"_IVF_phi"]                         = new TH1F(prefix+"_IVF_phi", ";SV #phi (IVF);Events", 15, -3.14, 3.14);
        //(*hists)[prefix+"_IVF_mass_check"]                  = new TH1F(prefix+"_IVF_mass_check", ";SV Mass [GeV] (IVF);Events", 30, 0, 10);
        (*hists)[prefix+"_IVF_ptsum"]                       = new TH1F(prefix+"_IVF_ptsum", ";SV #it{p}_{T}^{sum} [GeV] (IVF);Events", 30, 0, 80);
        (*hists)[prefix+"_IVF_l1_mass"]                     = new TH1F(prefix+"_IVF_l1_mass", ";l_{1} + SV Mass [GeV] (IVF);Events", 40, 0, 150);
        (*hists)[prefix+"_IVF_PV-SVdxy_zoom2"]              = new TH1F(prefix+"_IVF_PV-SVdxy_zoom2", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 2);
        (*hists)[prefix+"_IVF_PV-SVdxyz_zoom2"]             = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom2", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 2);
    }
}


void full_analyzer::add_Shape_SR_histograms(std::map<TString, TH1*>* hists, TString prefix)
{
    (*hists)[prefix+"_Shape_SR"]    = new TH1F(prefix+"_Shape_SR", ";SR bins;Events", 12, 0, 12);
}


void full_analyzer::fill_Shape_SR_histograms(std::map<TString, TH1*>* hists, TString MV2, double event_weight)
{
    unsigned bin = -20;
    if(IVF_PVSVdist_2D > 0 and IVF_PVSVdist_2D < 1) bin = 0;
    else if(IVF_PVSVdist_2D > 1 and IVF_PVSVdist_2D < 5) bin = 1;
    else if(IVF_PVSVdist_2D > 5 and IVF_PVSVdist_2D < 60) bin = 2;

    if(SVmass > 5) bin += 3;

    if(sr_flavor.Index("OS") != -1) bin += 6;

    (*hists)[sr_lflavor + MV2 + "_Shape_SR"]->Fill(bin, event_weight);
}


void full_analyzer::fill_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D){
    fill_HNL_MC_check(hists, hists2D, ev_weight);
    fill_leptonreco_eff(hists);
    if(i_leading != -1) fill_HLT_efficiency(hists, "Beforeptcut", _lFlavor[i_leading] == 0, _lFlavor[i_leading] == 1, 1);
    //fill_HLT_efficiency(hists, "Afterptcut", (i_leading_e != -1 && leadptcut(i_leading_e)), (i_leading_mu != -1 && leadptcut(i_leading_mu)));

    fill_cutflow(hists, sr_flavor, ev_weight);

    if(_l1l2){
        fill_lepton_eff(hists, sr_flavor);
        fill_IVF_eff(hists, hists2D, sr_lflavor, ev_weight);
        fill_HNLrecotracks_KVF_eff(hists, hists2D, sr_lflavor, ev_weight);
    }

    if(_l1l2SV){
        fill_relevant_histograms(hists, hists2D, sr_flavor + "_afterSV", ev_weight);
    }

    if(_Training){
        fill_relevant_histograms(hists, hists2D, sr_flavor + "_Training", ev_weight);
        fill_chargeflip_histograms(hists, hists2D, sr_flavor + "_Training", ev_weight);
        fill_HLT_efficiency(hists, "Afterptcut", _lFlavor[i_leading] == 0, _lFlavor[i_leading] == 1, ev_weight);
    }
    if(_Training2Jets){
        fill_relevant_histograms(hists, hists2D, sr_flavor + "_2Jets", ev_weight);
    }
    if(_Training2JetsNoZ){
        fill_relevant_histograms(hists, hists2D, sr_flavor + "_2JetsNoZ", ev_weight);
    }

    if(_FullNoPFN){
        fill_relevant_histograms(hists, hists2D, sr_flavor, ev_weight);
    }
    //if(_FullNoPFN_toofar){
    //    fill_relevant_histograms(hists, hists2D, sr_flavor + "_TooFar", ev_weight);
    //}


    for(auto& MassMap : evaluating_V2s_plots){
        if(_TrainingHighPFN[MassMap.first][7e-5]){
            fill_relevant_histograms(hists, hists2D, sr_flavor + "_TrainingHighPFN_M-" + std::to_string(MassMap.first), ev_weight);
        }
        for(auto& V2 : MassMap.second){
            if(_FullNoPFN){
                fill_pfn_histograms(hists, sr_flavor + MV2name[MassMap.first][V2], MassMap.first, V2, ev_weight*reweighting_weights[V2]);
                fill_relevant_histograms(hists, hists2D, sr_flavor + "_SR" + MV2name[MassMap.first][V2], ev_weight*reweighting_weights[V2]);
            }
            if(_Training2Jets) fill_pfn_histograms(hists, sr_flavor + "_2Jets" + MV2name[MassMap.first][V2], MassMap.first, V2, ev_weight*reweighting_weights[V2]);
            //if(_Training) fill_pfn_histograms(hists, sr_flavor + "_Training" + MV2name[MassMap.first][V2], MassMap.first, V2, ev_weight*reweighting_weights[V2]);
            //if(_TrainingHighPFN[MassMap.first][V2]) fill_relevant_histograms(hists, hists2D, sr_flavor + "_TrainingHighPFN" + MV2name[MassMap.first][V2], ev_weight*reweighting_weights[V2]);
            if(_FullNoPFN and _Full[MassMap.first][V2]){
                fill_Shape_SR_histograms(hists, MV2name[MassMap.first][V2], ev_weight*reweighting_weights[V2]);
            }
            //if(_CR_Full_invdphi[MassMap.first][V2]) fill_relevant_histograms(hists, hists2D, sr_flavor + "_CRdphi" + MV2name[MassMap.first][V2], ev_weight*reweighting_weights[V2]);
            //if(_CR_Full_invmll[MassMap.first][V2]) fill_relevant_histograms(hists, hists2D, sr_flavor + "_CRmll" + MV2name[MassMap.first][V2], ev_weight*reweighting_weights[V2]);
        }
    }
}


void full_analyzer::fill_relevant_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, double event_weight){
    fill_general_histograms(hists, hists2D, prefix, event_weight);
    fill_IVF_histograms(hists, hists2D, prefix, event_weight);
    fill_jet_histograms(hists, prefix, event_weight);
}


void full_analyzer::fill_general_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, double event_weight){
    
    (*hists)[prefix+"_nTightEle"]->Fill(nTightEle, event_weight);
    (*hists)[prefix+"_nTightMu"]->Fill(nTightMu, event_weight);
    (*hists)[prefix+"_nTight"]->Fill(nTightEle + nTightMu, event_weight);
    (*hists)[prefix+"_nDisplEle"]->Fill(nDisplEle, event_weight);
    (*hists)[prefix+"_nDisplMu"]->Fill(nDisplMu, event_weight);
    (*hists)[prefix+"_nDispl"]->Fill(nDisplEle + nDisplMu, event_weight);
    (*hists)[prefix+"_nTightDispl"]->Fill(nTightEle + nDisplEle + nTightMu + nDisplMu, event_weight);
    (*hists)[prefix+"_nDispleAndmu"]->Fill(((nDisplEle > 0)? 1 : 0) + ((nDisplMu > 0)? 1 : 0), event_weight);
    (*hists)[prefix+"_nJets_uncl"]->Fill(nTightJet_uncl, event_weight);
    (*hists)[prefix+"_nJets_cl"]->Fill(nTightJet, event_weight);

    (*hists)[prefix+"_l1_pt"]->Fill(_lPt[i_leading], event_weight);
    //std::cout << "l2 pt: " << _lPt[i_subleading] << " weight: " << event_weight << std::endl;
    (*hists)[prefix+"_l2_pt"]->Fill(_lPt[i_subleading], event_weight);
    (*hists)[prefix+"_llptdiff"]->Fill(_lPt[i_leading] - _lPt[i_subleading], event_weight);
    (*hists)[prefix+"_l1_eta"]->Fill(_lEta[i_leading], event_weight);
    (*hists)[prefix+"_l2_eta"]->Fill(_lEta[i_subleading], event_weight);
    (*hists)[prefix+"_l1_dxy"]->Fill(fabs(_dxy[i_leading]), event_weight);
    (*hists)[prefix+"_l2_dxy"]->Fill(fabs(_dxy[i_subleading]), event_weight);
    (*hists)[prefix+"_l1_dz"]->Fill(fabs(_dz[i_leading]), event_weight);
    (*hists)[prefix+"_l2_dz"]->Fill(fabs(_dz[i_subleading]), event_weight);
    (*hists)[prefix+"_l1_reliso"]->Fill(_relIso[i_leading], event_weight);
    (*hists)[prefix+"_l2_reliso"]->Fill(_relIso[i_subleading], event_weight);
    (*hists)[prefix+"_l1_ptrel"]->Fill(_ptRel[i_leading], event_weight);
    (*hists)[prefix+"_l2_ptrel"]->Fill(_ptRel[i_subleading], event_weight);
    (*hists)[prefix+"_l1_ptratio"]->Fill(_ptRatio[i_leading], event_weight);
    (*hists)[prefix+"_l2_ptratio"]->Fill(_ptRatio[i_subleading], event_weight);
    (*hists)[prefix+"_l1_selectedTrackMult"]->Fill(_selectedTrackMult[i_leading], event_weight);
    (*hists)[prefix+"_l2_selectedTrackMult"]->Fill(_selectedTrackMult[i_subleading], event_weight);
    (*hists)[prefix+"_l1_3dIPSig"]->Fill(_3dIPSig[i_leading], event_weight);
    (*hists)[prefix+"_l2_3dIPSig"]->Fill(_3dIPSig[i_subleading], event_weight);
    (*hists2D)[prefix+"_l2_ptvsctau"]->Fill(_lPt[i_subleading], _ctauHN, event_weight);
    (*hists2D)[prefix+"_lsources"]->Fill(get_lsource(i_gen_l1), get_lsource(i_gen_l2), event_weight);
    (*hists2D)[prefix+"_lprovenance"]->Fill(_lProvenance[i_leading], _lProvenance[i_subleading], event_weight);
    (*hists2D)[prefix+"_lprovenanceCompressed"]->Fill(_lProvenanceCompressed[i_leading], _lProvenanceCompressed[i_subleading], event_weight);
    (*hists2D)[prefix+"_l2provCompressedvsConversion"]->Fill(_lProvenanceCompressed[i_subleading], std::min((unsigned)3, _lProvenanceConversion[i_subleading]), event_weight);

    (*hists)[prefix+"_met"]->Fill(_met, event_weight);
    //(*hists)[prefix+"_KVF_valid"]->Fill(_lKVF_valid[i_subleading], event_weight);

    //if(mll < 15){
    //    std::cout << "mll lower than 15!" << mll << std::endl;
    //    std::cout << "l1 pt eta phi: " << _lPt[i_leading] << " " << _lEta[i_leading] << " " << _lPhi[i_leading] << std::endl;
    //    std::cout << "l2 pt eta phi: " << _lPt[i_subleading] << " " << _lEta[i_subleading] << " " << _lPhi[i_subleading] << std::endl;
    //}

    (*hists)[prefix+"_mll"]->Fill(mll, event_weight);
    (*hists)[prefix+"_mll_zoomAtLowMll"]->Fill(mll, event_weight);
    (*hists)[prefix+"_integral"]->Fill(1, event_weight);
    (*hists)[prefix+"_dphill"]->Fill(dphill, event_weight);
    (*hists)[prefix+"_dRll"]->Fill(dRll, event_weight);
    if(extensive_plots){
        (*hists)[prefix+"_l1_phi"]->Fill(_lPhi[i_leading], event_weight);
        (*hists)[prefix+"_l2_phi"]->Fill(_lPhi[i_subleading], event_weight);
        (*hists)[prefix+"_l2_dxy_zoom"]->Fill(fabs(_dxy[i_subleading]), event_weight);
        (*hists)[prefix+"_l1_3dIP"]->Fill(_3dIP[i_leading], event_weight);
        (*hists)[prefix+"_l2_3dIP"]->Fill(_3dIP[i_subleading], event_weight);
        (*hists)[prefix+"_l2_NumberOfHits"]->Fill(_lNumberOfValidTrackerHits[i_subleading], event_weight);
        (*hists)[prefix+"_l2_NumberOfPixelHits"]->Fill(_lNumberOfValidPixelHits[i_subleading], event_weight);
        //LorentzVector l2_vec(_lPt[i_subleading], _lEta[i_subleading], _lPhi[i_subleading], _lE[i_subleading]);
        //if(nJets_uncl > 0) (*hists)[prefix+"_dRl2jet1_uncl"]->Fill(deltaR(l2_vec, jets_uncl[0]), event_weight);
        //if(nJets_uncl > 1) (*hists)[prefix+"_dRl2jet2_uncl"]->Fill(deltaR(l2_vec, jets_uncl[1]), event_weight);
        //if(nJets_uncl > 1) (*hists)[prefix+"_dRjet1jet2_uncl"]->Fill(deltaR(jets_uncl[0], jets_uncl[1]), event_weight);
        //if(nJets_uncl > 1) (*hists2D)[prefix+"_dRl2jet1_2_uncl"]->Fill(deltaR(l2_vec, jets_uncl[0]), deltaR(l2_vec, jets_uncl[1]), event_weight);
        //if(nJets_cl > 0) (*hists)[prefix+"_dRl2jet1_cl"]->Fill(deltaR(l2_vec, jets_cl[0]), event_weight);
        //if(nJets_cl > 1) (*hists)[prefix+"_dRl2jet2_cl"]->Fill(deltaR(l2_vec, jets_cl[1]), event_weight);
        //if(nJets_cl > 1) (*hists)[prefix+"_dRjet1jet2_cl"]->Fill(deltaR(jets_cl[0], jets_cl[1]), event_weight);
        //if(nJets_cl > 1) (*hists2D)[prefix+"_dRl2jet1_2_cl"]->Fill(deltaR(l2_vec, jets_cl[0]), deltaR(l2_vec, jets_cl[1]), event_weight);
    }

    if(!isData){
        int charged_count = 0;
        for(unsigned i = 0; i < _gen_nNPackedDtrs; i++){
            if(_gen_NPackedDtrsCharge[i] != 0){
                charged_count++;
            }
        }
    
        (*hists)[prefix+"_nTrueInteractions"]->Fill(_nTrueInt, event_weight);
        (*hists)[prefix+"_ngentr"]->Fill(charged_count, event_weight);
        (*hists)[prefix+"_ctau"]->Fill(_ctauHN, event_weight);
        //(*hists)[prefix+"_ctaug"]->Fill(_ctauHN*calc_betagamma(HNL_param->mass, _gen_NE), event_weight);
    }
}

void full_analyzer::add_cutflow_histograms(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_cutflow"]                 = new TH1F(prefix+"_cutflow", ";;Events", 9, 0, 9);
    (*hists)[prefix+"_cutflow2"]                = new TH1F(prefix+"_cutflow2", ";;Events", 7, 0, 7);
    (*hists)[prefix+"_cutflow_l2Sel"]           = new TH1F(prefix+"_cutflow_l2Sel", ";;Events", 3, 0, 3);
    (*hists)[prefix+"_l2Sel_llptdiff"]          = new TH1F(prefix+"_l2Sel_llptdiff", ";;Events", 30, -50, 100);
}

void full_analyzer::fill_cutflow(std::map<TString, TH1*>* hists, TString prefix, double event_weight){
    /*
     * Cutflow
     */
    if(i_leading != -1 and ((_lFlavor[i_leading] == 0 and _trige) or (_lFlavor[i_leading] == 1 and _trigmu))){
        //(*hists)[prefix+"_cutflow"]->Fill(0., event_weight);
        if(_l1){
            //(*hists)[prefix+"_cutflow"]->Fill(1., event_weight);
            if(_l1l2){
                (*hists)[prefix+"_cutflow"]->Fill(2., event_weight);
                (*hists)[prefix+"_cutflow2"]->Fill(0., event_weight);
                if(_l1l2SV){
                    (*hists)[prefix+"_cutflow"]->Fill(3., event_weight);
                    (*hists)[prefix+"_cutflow2"]->Fill(1., event_weight);
                    if(dphill > 0.4){
                        (*hists)[prefix+"_cutflow"]->Fill(4., event_weight);
                        (*hists)[prefix+"_cutflow2"]->Fill(2., event_weight);
                        if(mll > 10){
                            (*hists)[prefix+"_cutflow"]->Fill(5., event_weight);
                            (*hists)[prefix+"_cutflow2"]->Fill(3., event_weight);
                            if(i_jetl2 != -1){
                                (*hists)[prefix+"_cutflow"]->Fill(6., event_weight);
                                (*hists)[prefix+"_cutflow2"]->Fill(4., event_weight);
                                if(nTightJet <= 1){
                                    (*hists)[prefix+"_cutflow"]->Fill(7., event_weight);
                                    (*hists)[prefix+"_cutflow2"]->Fill(5., event_weight);
                                    if(nTightEle + nTightMu == 1){
                                        (*hists)[prefix+"_cutflow"]->Fill(8., event_weight);
                                        (*hists)[prefix+"_cutflow2"]->Fill(6., event_weight);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /*
     * l2 selection method cutflow
     */
    if(_l1){
        if(i_subleading_highestpt != -1 and _lIVF_match[i_subleading_highestpt]){
            TString prefix_highestpt = get_signal_region_flavor(i_leading, i_subleading_highestpt);
            (*hists)[prefix_highestpt+"_cutflow_l2Sel"]->Fill(0., event_weight);
            (*hists)[prefix_highestpt+"_l2Sel_llptdiff"]->Fill(_lPt[i_leading] - _lPt[i_subleading_highestpt], event_weight);
        }
        if(i_subleading != -1) (*hists)[prefix+"_cutflow_l2Sel"]->Fill(1., event_weight);
        if(i_subleading != -1 and nDisplMu + nDisplEle < 2) (*hists)[prefix+"_cutflow_l2Sel"]->Fill(2., event_weight);
    }


    /*
     * MVA ID versus cutbased medium prompt ID
     */
    //if(_1e and _1pogmediume)    (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(0., event_weight);
    //if(_1e and !_1pogmediume)   (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(1., event_weight);
    //if(!_1e and _1pogmediume)   (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(2., event_weight);
    //if(!_1e and !_1pogmediume)  (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(3., event_weight);

    /*
     * Delta phi(ll) > 2.4 versus 1 < Delta R(ll) < 5.5
     */
    //if(_1e1displedphi and _1e1displedR) (*hists)[prefix+"_deltaphivsR_categories"]->Fill(0., event_weight);
    //if(_1e1displedphi and !_1e1displedR) (*hists)[prefix+"_deltaphivsR_categories"]->Fill(1., event_weight);
    //if(!_1e1displedphi and _1e1displedR) (*hists)[prefix+"_deltaphivsR_categories"]->Fill(2., event_weight);
    //if(!_1e1displedphi and !_1e1displedR) (*hists)[prefix+"_deltaphivsR_categories"]->Fill(3., event_weight);

    /*
     * KVF vs IVF for events
     */
    //if(!isData){
    //    if(_1e1disple and fabs(_lCharge[i_leading] + _lCharge[i_subleading]) == SSorOS and i_gen_l2 != -1) {
    //        if(_lIVF_match[i_subleading] and get_xyz_distance(_gen_vertex_x[i_gen_l2], _gen_vertex_y[i_gen_l2], _gen_vertex_z[i_gen_l2], _IVF_x[i_subleading], _IVF_y[i_subleading], _IVF_z[i_subleading]){
    //            if(_lKVF_valid[i_subleading] and get_xyz_distance(_gen_vertex_x[i_gen_l2], _gen_vertex_y[i_gen_l2], _gen_vertex_z[i_gen_l2], _lKVF_x[i_subleading], _lKVF_y[i_subleading], _lKVF_z[i_subleading]) < 0.2) (*hists)[prefix+"_KVForIVF_categories"]->Fill(0., event_weight);
    //            else (*hists)[prefix+"_KVForIVF_categories"]->Fill(1., event_weight);
    //        }else {
    //            if(_lKVF_valid[i_subleading] and get_xyz_distance(_gen_vertex_x[i_gen_l2], _gen_vertex_y[i_gen_l2], _gen_vertex_z[i_gen_l2], _lKVF_x[i_subleading], _lKVF_y[i_subleading], _lKVF_z[i_subleading]) < 0.2) (*hists)[prefix+"_KVForIVF_categories"]->Fill(2., event_weight);
    //            else (*hists)[prefix+"_KVForIVF_categories"]->Fill(3., event_weight);
    //        }
    //    }
    //}

    /*
     * l2 identification and jets(cleaned)
     */
    //if(_1e){
    //    if(_1e1disple and fabs(_lCharge[i_leading] + _lCharge[i_subleading]) == SSorOS){
    //        if(i_leading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(4., event_weight);
    //        else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(5., event_weight);
    //        else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(6., event_weight);
    //        else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(7., event_weight);
    //        if(i_leading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(0., event_weight);
    //        else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(1., event_weight);
    //        else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(2., event_weight);
    //        else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_jets_categories"]->Fill(3., event_weight);
    //    }else {
    //        if(i_leading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(0., event_weight);
    //        else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(1., event_weight);
    //        else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(2., event_weight);
    //        else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(3., event_weight);
    //    }
    //}

    /*
     * Is l1 or l2 matched to a vertex?
     */
    if(_l1l2){
        (*hists)[prefix+"_l1_IVF_match"]->Fill(_lIVF_match[i_leading], event_weight);
        (*hists)[prefix+"_l2_IVF_match"]->Fill(_lIVF_match[i_subleading], event_weight);
    }
}


void full_analyzer::fill_KVF_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, double event_weight){
    if(!_lKVF_valid[i_subleading]) return;
    
    double KVF_PVSVdist     = get_xyz_distance(_PV_x, _PV_y, _PV_z, _lKVF_x[i_subleading], _lKVF_y[i_subleading], _lKVF_z[i_subleading]);
    double KVF_PVSVdist_2D  = get_xy_distance(_PV_x, _PV_y, _lKVF_x[i_subleading], _lKVF_y[i_subleading]);

    //plots for valid KVF vertices
    
    (*hists)[prefix+"_KVF_chi2"]->Fill(_lKVF_chi2[i_subleading], event_weight);
    (*hists)[prefix+"_KVF_normchi2"]->Fill(_lKVF_chi2[i_subleading] / _lKVF_df[i_subleading], event_weight);
    (*hists)[prefix+"_KVF_normchi2_zoom"]->Fill(_lKVF_chi2[i_subleading] / _lKVF_df[i_subleading], event_weight);
    (*hists)[prefix+"_KVF_ntracks"]->Fill(_lKVF_ntracks[i_subleading], event_weight);
    
    (*hists)[prefix+"_KVF_PV-SVdxy"]->Fill(KVF_PVSVdist_2D, event_weight);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom"]->Fill(KVF_PVSVdist_2D, event_weight);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom2"]->Fill(KVF_PVSVdist_2D, event_weight);
    (*hists)[prefix+"_KVF_PV-SVdxyz"]->Fill(KVF_PVSVdist, event_weight);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom"]->Fill(KVF_PVSVdist, event_weight);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom2"]->Fill(KVF_PVSVdist, event_weight);
    (*hists)[prefix+"_KVF_dRcut"]->Fill(_lKVF_dRcut[i_subleading], event_weight);

    if(!isData){
        if(i_gen_l2 != -1){
            double KVF_SVgenreco    = get_xyz_distance(_gen_vertex_x[i_gen_l2], _gen_vertex_y[i_gen_l2], _gen_vertex_z[i_gen_l2], _lKVF_x[i_subleading], _lKVF_y[i_subleading], _lKVF_z[i_subleading]);
            (*hists)[prefix+"_KVF_SVgen-reco"]->Fill(KVF_SVgenreco);
            (*hists)[prefix+"_KVF_SVgen-reco_zoom"]->Fill(KVF_SVgenreco);
            (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco"]->Fill(KVF_PVSVdist, gen_PVSVdist, event_weight);
            (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco_zoom"]->Fill(KVF_PVSVdist, gen_PVSVdist, event_weight);
        }
    }
}


void full_analyzer::fill_IVF_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, double event_weight){
    if(!_lIVF_match[i_subleading]) return;

    (*hists)[prefix+"_IVF_normchi2"]->Fill(_IVF_chi2[i_subleading]/_IVF_df[i_subleading], event_weight);
    (*hists)[prefix+"_IVF_PV-SVdxy"]->Fill(IVF_PVSVdist_2D, event_weight);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom"]->Fill(IVF_PVSVdist_2D, event_weight);
    (*hists)[prefix+"_IVF_PV-SVdxyz"]->Fill(IVF_PVSVdist, event_weight);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom"]->Fill(IVF_PVSVdist, event_weight);
    (*hists)[prefix+"_IVF_ntracks"]->Fill(_IVF_ntracks[i_subleading], event_weight);
    (*hists)[prefix+"_IVF_mass"]->Fill(SVmass, event_weight);
    (*hists)[prefix+"_IVF_l1mass"]->Fill(SVl1mass, event_weight);
    (*hists)[prefix+"_IVF_massminl2"]->Fill(SVmassminl2, event_weight);
    (*hists)[prefix+"_IVF_massminl2_K0"]->Fill(SVmassminl2, event_weight);
    (*hists)[prefix+"_IVF_costracks"]->Fill(IVF_costracks, event_weight);

    (*hists)[prefix+"_gen_PV-SVdxy"]->Fill(gen_PVSVdist_2D,event_weight);
    (*hists)[prefix+"_gen_PV-SVdxy_zoom"]->Fill(gen_PVSVdist_2D,event_weight);
    (*hists)[prefix+"_gen_PV-SVdxyz"]->Fill(gen_PVSVdist,event_weight);
    (*hists)[prefix+"_gen_PV-SVdxyz_zoom"]->Fill(gen_PVSVdist,event_weight);
    (*hists)[prefix+"_gen_SVntracks"]->Fill(gen_SVntracks,event_weight);
    (*hists)[prefix+"_gen_SVmass"]->Fill(gen_SVmass,event_weight);

    if(extensive_plots){
        (*hists)[prefix+"_IVF_chi2"]->Fill(_IVF_chi2[i_subleading], event_weight);
        (*hists)[prefix+"_IVF_PV-SVdxy_zoom2"]->Fill(IVF_PVSVdist_2D, event_weight);
        (*hists)[prefix+"_IVF_PV-SVdxyz_zoom2"]->Fill(IVF_PVSVdist, event_weight);
        (*hists)[prefix+"_IVF_normchi2_zoom"]->Fill(_IVF_chi2[i_subleading]/_IVF_df[i_subleading], event_weight);
        (*hists)[prefix+"_IVF_df"]->Fill(_IVF_df[i_subleading], event_weight);
        (*hists)[prefix+"_IVF_cxy"]->Fill(sqrt(_IVF_cx[i_subleading]*_IVF_cx[i_subleading] + _IVF_cy[i_subleading]*_IVF_cy[i_subleading]), event_weight);
        (*hists)[prefix+"_IVF_cz"]->Fill(_IVF_cz[i_subleading], event_weight);
        (*hists)[prefix+"_IVF_cxyz"]->Fill(sqrt(_IVF_cx[i_subleading]*_IVF_cx[i_subleading] + _IVF_cy[i_subleading]*_IVF_cy[i_subleading] + _IVF_cz[i_subleading]*_IVF_cz[i_subleading]), event_weight);
    
        if(_IVF_ntracks[i_subleading] > 1){
            TLorentzVector l1vector;
            l1vector.SetPtEtaPhiE(_lPt[i_leading], _lEta[i_leading], _lPhi[i_leading], _lE[i_leading]);
            TLorentzVector tracksum;
            TLorentzVector tmptrack;
            for(unsigned i_track = 0; i_track < _IVF_ntracks[i_subleading]; i_track++){
                (*hists)[prefix+"_IVF_trackpt"]->Fill(_IVF_trackpt[i_subleading][i_track], event_weight);
                (*hists)[prefix+"_IVF_tracketa"]->Fill(_IVF_tracketa[i_subleading][i_track], event_weight);
                (*hists)[prefix+"_IVF_trackphi"]->Fill(_IVF_trackphi[i_subleading][i_track], event_weight);
                (*hists)[prefix+"_IVF_trackE"]->Fill(_IVF_trackE[i_subleading][i_track], event_weight);
                (*hists)[prefix+"_IVF_trackcharge"]->Fill(_IVF_trackcharge[i_subleading][i_track], event_weight);
                tmptrack.SetPtEtaPhiE(_IVF_trackpt[i_subleading][i_track], _IVF_tracketa[i_subleading][i_track], _IVF_trackphi[i_subleading][i_track], _IVF_trackE[i_subleading][i_track]);
                tracksum += tmptrack;
            }
            (*hists)[prefix+"_IVF_pt"]->Fill(SVpt, event_weight);
            (*hists)[prefix+"_IVF_eta"]->Fill(SVeta, event_weight);
            (*hists)[prefix+"_IVF_phi"]->Fill(SVphi, event_weight);
            //(*hists)[prefix+"_IVF_mass_check"]->Fill(_IVF_mass[i_subleading], event_weight);
            (*hists)[prefix+"_IVF_ptsum"]->Fill(tracksum.Pt(), event_weight);
            (*hists)[prefix+"_IVF_l1_mass"]->Fill((tracksum+l1vector).M(), event_weight);

        }
        
        if(!isData){
            (*hists)[prefix+"_IVF_ctau"]->Fill(_ctauHN, event_weight);
            (*hists2D)[prefix+"_IVF_ctauHN_PV-SVdxyz"]->Fill(_ctauHN, IVF_PVSVdist, event_weight);
            (*hists2D)[prefix+"_IVF_ctaugHN_PV-SVdxyz"]->Fill(_ctauHN*calc_betagamma(HNL_param->mass, _gen_NE), IVF_PVSVdist, event_weight);
            if(i_gen_l2 != -1){
                (*hists)[prefix+"_IVF_SVgen-reco"]->Fill(IVF_SVgenreco, event_weight);
                (*hists)[prefix+"_IVF_SVgen-reco_zoom"]->Fill(IVF_SVgenreco, event_weight);
                (*hists2D)[prefix+"_IVF_PV-SVdxyz_genvsreco"]->Fill(IVF_PVSVdist, gen_PVSVdist, event_weight);
                (*hists2D)[prefix+"_IVF_PV-SVdxyz_genvsreco_zoom"]->Fill(IVF_PVSVdist, gen_PVSVdist, event_weight);
                (*hists2D)[prefix+"_IVF_ctauHN_genPV-SVdxyz"]->Fill(_ctauHN, gen_PVSVdist, event_weight);
                (*hists2D)[prefix+"_IVF_ctaugHN_genPV-SVdxyz"]->Fill(_ctauHN*calc_betagamma(HNL_param->mass, _gen_NE), gen_PVSVdist, event_weight);
            }
        }
    }
}

void full_analyzer::fill_leptonreco_eff(std::map<TString, TH1*>* hists){
    if(i_gen_l1 != -1 and ((_gen_lFlavor[i_gen_l1] == 0 and _gen_lPt[i_gen_l1] > 30 and fabs(_gen_lEta[i_gen_l1]) < 2.5) or (_gen_lFlavor[i_gen_l1] == 1 and _gen_lPt[i_gen_l1] > 25 and fabs(_gen_lEta[i_gen_l1]) < 2.4))){
        (*hists)["l1reco_pt_eff_den"]->Fill(_gen_lPt[i_gen_l1]);
        (*hists)["l1reco_eta_eff_den"]->Fill(_gen_lEta[i_gen_l1]);
        //(*hists)["l1reco_dxy_eff_den"]->Fill(_gen_[i_gen_l1]);
        //(*hists)["l1reco_dz_eff_den"]->Fill(_gen_[i_gen_l1]);
        (*hists)["l1reco_ctau_eff_den"]->Fill(_ctauHN);

        if(i_l1_fromgen != -1){
            (*hists)["l1reco_pt_eff_num"]->Fill(_gen_lPt[i_gen_l1]);
            (*hists)["l1reco_eta_eff_num"]->Fill(_gen_lEta[i_gen_l1]);
            //(*hists)["l1reco_dxy_eff_num"]->Fill(_gen_[i_gen_l1]);
            //(*hists)["l1reco_dz_eff_num"]->Fill(_gen_[i_gen_l1]);
            (*hists)["l1reco_ctau_eff_num"]->Fill(_ctauHN);

            (*hists)["l1id_pt_eff_den"]->Fill(_gen_lPt[i_gen_l1]);
            (*hists)["l1id_eta_eff_den"]->Fill(_gen_lEta[i_gen_l1]);

            if(leadingIsl1){
                (*hists)["l1id_pt_eff_num"]->Fill(_gen_lPt[i_gen_l1]);
                (*hists)["l1id_eta_eff_num"]->Fill(_gen_lEta[i_gen_l1]);
            }
        }
    }

    if(i_gen_l2 != -1 and _l1 and ((_gen_lFlavor[i_gen_l2] == 0 and _gen_lPt[i_gen_l2] > 7 and fabs(_gen_lEta[i_gen_l2]) < 2.5) or (_gen_lFlavor[i_gen_l2] == 1 and _gen_lPt[i_gen_l2] > 5 and fabs(_gen_lEta[i_gen_l2]) < 2.4)) and get_xy_distance(_PV_x, _PV_y, _gen_vertex_x[i_gen_l2], _gen_vertex_y[i_gen_l2]) < 50){
        (*hists)["l2reco_pt_eff_den"]->Fill(_gen_lPt[i_gen_l2]);
        (*hists)["l2reco_eta_eff_den"]->Fill(_gen_lEta[i_gen_l2]);
        //(*hists)["l2reco_dxy_eff_den"]->Fill(_gen_[i_gen_l2]);
        //(*hists)["l2reco_dz_eff_den"]->Fill(_gen_[i_gen_l2]);
        (*hists)["l2reco_ctau_eff_den"]->Fill(_ctauHN);
        (*hists)["PVNvtxdist"]->Fill(PVNvtxdist);
        (*hists)["l2reco_Lxyz_eff_den"]->Fill(gen_PVSVdist);
        (*hists)["l2reco_Lxy_eff_den"]->Fill(gen_PVSVdist_2D);
        //(*hists)["l2reco_SVgen-reco_eff_den"]

        if(i_l2_fromgen != -1){
            (*hists)["l2reco_pt_eff_num"]->Fill(_gen_lPt[i_gen_l2]);
            (*hists)["l2reco_eta_eff_num"]->Fill(_gen_lEta[i_gen_l2]);
            //(*hists)["l2reco_dxy_eff_num"]->Fill(_gen_[i_gen_l2]);
            //(*hists)["l2reco_dz_eff_num"]->Fill(_gen_[i_gen_l2]);
            (*hists)["l2reco_ctau_eff_num"]->Fill(_ctauHN);
            (*hists)["l2reco_Lxyz_eff_num"]->Fill(gen_PVSVdist);
            (*hists)["l2reco_Lxy_eff_num"]->Fill(gen_PVSVdist_2D);
            //(*hists)["l2reco_PVSVdist_eff_num"]->Fill(_gen_);

            (*hists)["l2id_pt_eff_den"]->Fill(_gen_lPt[i_gen_l2]);
            (*hists)["l2id_eta_eff_den"]->Fill(_gen_lEta[i_gen_l2]);
            (*hists)["l2id_ctau_eff_den"]->Fill(_ctauHN);
            (*hists)["l2id_Lxyz_eff_den"]->Fill(gen_PVSVdist);
            (*hists)["l2id_Lxy_eff_den"]->Fill(gen_PVSVdist_2D);

            if(subleadinghighestptIsl2){
                (*hists)["l2id_pt_eff_num"]->Fill(_gen_lPt[i_gen_l2]);
                (*hists)["l2id_eta_eff_num"]->Fill(_gen_lEta[i_gen_l2]);
                (*hists)["l2id_ctau_eff_num"]->Fill(_ctauHN);
                (*hists)["l2id_Lxyz_eff_num"]->Fill(gen_PVSVdist);
                (*hists)["l2id_Lxy_eff_num"]->Fill(gen_PVSVdist_2D);
            }
        }
    }
}

void full_analyzer::fill_lepton_eff(std::map<TString, TH1*>* hists, TString prefix){
    if(isData) return;
    (*hists)[prefix+"_l2_pt_eff_den"]->Fill(_lPt[i_subleading]);
    (*hists)[prefix+"_l2_ctau_eff_den"]->Fill(_ctauHN);
    if(_lIVF_match[i_subleading] and i_gen_l2 != -1) (*hists)[prefix+"_l2_SVgen-reco_eff_den"]->Fill(IVF_SVgenreco);
    if(subleadinghighestptIsl2){
        (*hists)[prefix+"_l2_pt_eff_num"]->Fill(_lPt[i_subleading]);
        (*hists)[prefix+"_l2_ctau_eff_num"]->Fill(_ctauHN);
        if(_lIVF_match[i_subleading] and i_gen_l2 != -1) (*hists)[prefix+"_l2_SVgen-reco_eff_num"]->Fill(IVF_SVgenreco);
    }
    (*hists)[prefix+"_l1_pt_eff_den"]->Fill(_lPt[i_leading]);
    (*hists)[prefix+"_l1_ctau_eff_den"]->Fill(_ctauHN);
    if(leadingIsl1){
        (*hists)[prefix+"_l1_pt_eff_num"]->Fill(_lPt[i_leading]);
        (*hists)[prefix+"_l1_ctau_eff_num"]->Fill(_ctauHN);
    }
}

void full_analyzer::fill_HNLrecotracks_KVF_eff(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, double event_weight)
{
    if(!isSignal) return;
    if(i_gen_l2 == -1 or !(leadingIsl1 and subleadinghighestptIsl2)) return;
    if(HNLadditionaltracks < 1) return;
    
    (*hists)[prefix+"_HNLrecotracks_KVF_PV-SVdxyz_eff_den"]->Fill(gen_PVSVdist);
    (*hists)[prefix+"_HNLrecotracks_KVF_ctau_eff_den"]->Fill(_ctauHN);
    (*hists)[prefix+"_HNLrecotracks_KVF_PV-SVdxyz_onlylIVFmatch_eff_den"]->Fill(gen_PVSVdist);
    (*hists)[prefix+"_HNLrecotracks_KVF_ctau_onlylIVFmatch_eff_den"]->Fill(_ctauHN);
    if(_gen_NPackedDtrsHasKVFvertex){
        (*hists)[prefix+"_HNLrecotracks_KVF_PV-SVdxyz_onlylIVFmatch_eff_num"]->Fill(gen_PVSVdist);
        (*hists)[prefix+"_HNLrecotracks_KVF_ctau_onlylIVFmatch_eff_num"]->Fill(_ctauHN);
        if(HNLadditionaltracks == 1 and _gen_nNPackedDtrsPCA == 1){
            (*hists)[prefix+"_HNLrecotracks_yesKVF_2trPCA"]->Fill(_gen_NPackedDtrsPCADist[0], event_weight);
        }
    }else{
        (*hists)[prefix+"_HNLrecotracks_noKVF_l2_pt"]->Fill(_lPt[i_subleading], event_weight);
        (*hists)[prefix+"_HNLrecotracks_noKVF_l2_eta"]->Fill(_lEta[i_subleading], event_weight);
        (*hists)[prefix+"_HNLrecotracks_noKVF_l2_dxy"]->Fill(fabs(_dxy[i_subleading]), event_weight);
        (*hists)[prefix+"_HNLrecotracks_noKVF_l2_dz"]->Fill(fabs(_dz[i_subleading]), event_weight);
        (*hists)[prefix+"_HNLrecotracks_noKVF_l2_reliso"]->Fill(_relIso[i_subleading], event_weight);
        (*hists)[prefix+"_HNLrecotracks_noKVF_ntracks"]->Fill(HNLadditionaltracks + 1, event_weight);
        if(HNLadditionaltracks == 1 and _gen_nNPackedDtrsPCA == 1){
            (*hists)[prefix+"_HNLrecotracks_noKVF_2trPCA"]->Fill(_gen_NPackedDtrsPCADist[0], event_weight);
        }
    }
    if(_gen_NPackedDtrsHasKVFvertex && HNLrecotracks_KVF_SVgenreco / gen_PVSVdist < 0.1){
        (*hists)[prefix+"_HNLrecotracks_KVF_PV-SVdxyz_eff_num"]->Fill(gen_PVSVdist);
        (*hists)[prefix+"_HNLrecotracks_KVF_ctau_eff_num"]->Fill(_ctauHN);
    }
}

void full_analyzer::fill_IVF_eff(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, double event_weight){
    if(isData) return;
    if(i_gen_l2 == -1 or !(leadingIsl1 and subleadinghighestptIsl2)) return;


    if(HNLadditionaltracks >= 1){
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr_eff_den"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr_onlylIVFmatch_eff_den"]->Fill(gen_PVSVdist_2D);
        if(_lIVF_match[i_subleading]){
            (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr_onlylIVFmatch_eff_num"]->Fill(gen_PVSVdist_2D);
        }
        if(_lIVF_match[i_subleading] && IVF_SVgenreco / gen_PVSVdist < 0.1){
            (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr_eff_num"]->Fill(gen_PVSVdist_2D);
        }
    }
    if(HNLadditionaltracks >= 2){
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr2_eff_den"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr2_onlylIVFmatch_eff_den"]->Fill(gen_PVSVdist_2D);
        if(_lIVF_match[i_subleading]){
            (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr2_onlylIVFmatch_eff_num"]->Fill(gen_PVSVdist_2D);
        }
        if(_lIVF_match[i_subleading] && IVF_SVgenreco / gen_PVSVdist < 0.1){
            (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr2_eff_num"]->Fill(gen_PVSVdist_2D);
        }
    }
    if(HNLadditionaltracks >= 3){
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr3_eff_den"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr3_onlylIVFmatch_eff_den"]->Fill(gen_PVSVdist_2D);
        if(_lIVF_match[i_subleading]){
            (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr3_onlylIVFmatch_eff_num"]->Fill(gen_PVSVdist_2D);
        }
        if(_lIVF_match[i_subleading] && IVF_SVgenreco / gen_PVSVdist < 0.1){
            (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr3_eff_num"]->Fill(gen_PVSVdist_2D);
        }
    }

    (*hists)[prefix+"_IVF_cutflow"]->Fill(0., event_weight);
    //(*hists)[prefix+"_IVF_PV-SVdxy_eff_den"]->Fill(IVF_PVSVdist_2D);
    //(*hists)[prefix+"_IVF_PV-SVdxy_zoom_eff_den"]->Fill(IVF_PVSVdist_2D);
    //(*hists)[prefix+"_IVF_PV-SVdxy_zoom2_eff_den"]->Fill(IVF_PVSVdist_2D);
    //(*hists)[prefix+"_IVF_PV-SVdxyz_eff_den"]->Fill(IVF_PVSVdist);
    //(*hists)[prefix+"_IVF_PV-SVdxyz_zoom_eff_den"]->Fill(IVF_PVSVdist);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_eff_den"]->Fill(gen_PVSVdist_2D);
    (*hists)[prefix+"_IVF_ctau_eff_den"]->Fill(_ctauHN);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_onlylIVFmatch_eff_den"]->Fill(gen_PVSVdist_2D);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom_eff_den"]->Fill(gen_PVSVdist_2D);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz_eff_den"]->Fill(gen_PVSVdist);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz_zoom_eff_den"]->Fill(gen_PVSVdist);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy2_eff_den"]->Fill(gen_PVSVdist_2D);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy2_zoom_eff_den"]->Fill(gen_PVSVdist_2D);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz2_eff_den"]->Fill(gen_PVSVdist);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz2_zoom_eff_den"]->Fill(gen_PVSVdist);
    //std::cout << "ctau, PVSV, eventweight: " << _ctauHN << " " << gen_PVSVdist << " " << event_weight << std::endl;
    (*hists2D)[prefix+"_IVF_gen_PV-SVdxyz_ctauHN_eff_den"]->Fill(_ctauHN, gen_PVSVdist, event_weight);
    if(extensive_plots){
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_den"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_IVF_gen_PV-SVdxyz_zoom2_eff_den"]->Fill(gen_PVSVdist);
        (*hists)[prefix+"_IVF_ctau_zoom_eff_den"]->Fill(_ctauHN);
        (*hists)[prefix+"_IVF_ctau_zoom2_eff_den"]->Fill(_ctauHN);
        (*hists)[prefix+"_IVF_ctaug_eff_den"]->Fill(_ctauHN*calc_betagamma(HNL_param->mass, _gen_NE));
    }
    
    if(_lIVF_match[i_subleading]){
        (*hists)[prefix+"_IVF_cutflow"]->Fill(1., event_weight);
        (*hists2D)[prefix+"_IVF_gen_PV-SVdxy_residual_xlog"]->Fill(gen_PVSVdist_2D, gen_PVSVdist_2D - IVF_PVSVdist_2D, event_weight);
        (*hists2D)[prefix+"_IVF_gen_PV-SVdxyz_residual_xlog"]->Fill(gen_PVSVdist, gen_PVSVdist - IVF_PVSVdist, event_weight);
        (*hists2D)[prefix+"_IVF_gen_SVmass_residual"]->Fill(gen_SVmass, gen_SVmass - SVmass, event_weight);
        (*hists2D)[prefix+"_IVF_gen_SVmasstontracks_residual"]->Fill(gen_SVmass, gen_SVntracks - _IVF_ntracks[i_subleading], event_weight);
        (*hists2D)[prefix+"_IVF_gen_ntracks_residual"]->Fill(gen_SVntracks, gen_SVntracks - _IVF_ntracks[i_subleading], event_weight);
        if(extensive_plots){
            (*hists)[prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_den"]->Fill(IVF_PVSVdist_2D);
            (*hists)[prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_den"]->Fill(IVF_PVSVdist);
        }
    }else {
        if(extensive_plots) (*hists)[prefix+"_IVF_PV-SVdxy_nomatch"]->Fill(IVF_PVSVdist, event_weight);
    }
    if(_lIVF_match[i_subleading]){
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_onlylIVFmatch_eff_num"]->Fill(gen_PVSVdist_2D);
    }
    if(_lIVF_match[i_subleading] && IVF_SVgenreco / gen_PVSVdist < 0.1){
        (*hists)[prefix+"_IVF_cutflow"]->Fill(2., event_weight);
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_eff_num"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom_eff_num"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_IVF_gen_PV-SVdxyz_eff_num"]->Fill(gen_PVSVdist);
        (*hists)[prefix+"_IVF_gen_PV-SVdxyz_zoom_eff_num"]->Fill(gen_PVSVdist);
        (*hists)[prefix+"_IVF_ctau_eff_num"]->Fill(_ctauHN);
        (*hists2D)[prefix+"_IVF_gen_PV-SVdxyz_ctauHN_eff_num"]->Fill(_ctauHN, gen_PVSVdist, event_weight);
    }
    
    if(_lIVF_match[i_subleading] && IVF_SVgenreco < 0.2){
        //(*hists)[prefix+"_IVF_PV-SVdxy_eff_num"]->Fill(IVF_PVSVdist_2D);
        //(*hists)[prefix+"_IVF_PV-SVdxy_zoom_eff_num"]->Fill(IVF_PVSVdist_2D);
        //(*hists)[prefix+"_IVF_PV-SVdxy_zoom2_eff_num"]->Fill(IVF_PVSVdist_2D);
        //(*hists)[prefix+"_IVF_PV-SVdxyz_eff_num"]->Fill(IVF_PVSVdist);
        //(*hists)[prefix+"_IVF_PV-SVdxyz_zoom_eff_num"]->Fill(IVF_PVSVdist);
        (*hists)[prefix+"_IVF_gen_PV-SVdxy2_eff_num"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_IVF_gen_PV-SVdxy2_zoom_eff_num"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_IVF_gen_PV-SVdxyz2_eff_num"]->Fill(gen_PVSVdist);
        (*hists)[prefix+"_IVF_gen_PV-SVdxyz2_zoom_eff_num"]->Fill(gen_PVSVdist);
        if(extensive_plots){
            (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_num"]->Fill(gen_PVSVdist_2D);
            (*hists)[prefix+"_IVF_gen_PV-SVdxyz_zoom2_eff_num"]->Fill(gen_PVSVdist);
            (*hists)[prefix+"_IVF_ctau_zoom_eff_num"]->Fill(_ctauHN);
            (*hists)[prefix+"_IVF_ctau_zoom2_eff_num"]->Fill(_ctauHN);
            (*hists)[prefix+"_IVF_ctaug_eff_num"]->Fill(_ctauHN*calc_betagamma(HNL_param->mass, _gen_NE));
            (*hists)[prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_num"]->Fill(IVF_PVSVdist_2D);
            (*hists)[prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_num"]->Fill(IVF_PVSVdist);
        }
    } 
}

void full_analyzer::fill_KVF_eff(std::map<TString, TH1*>* hists, TString prefix, double event_weight){
    if(isData) return;
    if(i_gen_l2 == -1) return;

    double KVF_SVgenreco    = get_xyz_distance(_gen_vertex_x[i_gen_l2], _gen_vertex_y[i_gen_l2], _gen_vertex_z[i_gen_l2], _lKVF_x[i_subleading], _lKVF_y[i_subleading], _lKVF_z[i_subleading]);
    double KVF_PVSVdist     = get_xyz_distance(_PV_x, _PV_y, _PV_z, _lKVF_x[i_subleading], _lKVF_y[i_subleading], _lKVF_z[i_subleading]);
    double KVF_PVSVdist_2D  = get_xy_distance(_PV_x, _PV_y, _lKVF_x[i_subleading], _lKVF_y[i_subleading]);


    (*hists)[prefix+"_KVF_PV-SVdxy_eff_den"]->Fill(KVF_PVSVdist_2D);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom_eff_den"]->Fill(KVF_PVSVdist_2D);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom2_eff_den"]->Fill(KVF_PVSVdist_2D);
    (*hists)[prefix+"_KVF_PV-SVdxyz_eff_den"]->Fill(KVF_PVSVdist);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom_eff_den"]->Fill(KVF_PVSVdist);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_eff_den"]->Fill(gen_PVSVdist_2D);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom_eff_den"]->Fill(gen_PVSVdist_2D);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_den"]->Fill(gen_PVSVdist_2D);
    (*hists)[prefix+"_KVF_ctau_eff_den"]->Fill(_ctauHN);
    (*hists)[prefix+"_KVF_ctau_zoom_eff_den"]->Fill(_ctauHN);
    (*hists)[prefix+"_KVF_ctau_zoom2_eff_den"]->Fill(_ctauHN);
    
    if(_lKVF_valid[i_subleading]){
        (*hists)[prefix+"_KVF_PV-SVdxyz_onlySVgen-reco_eff_den"]->Fill(KVF_PVSVdist); 
    }
    
    if(_lKVF_valid[i_subleading] && KVF_SVgenreco < 0.2 && KVF_PVSVdist > 0.05){
        (*hists)[prefix+"_KVF_PV-SVdxy_eff_num"]->Fill(KVF_PVSVdist_2D);
        (*hists)[prefix+"_KVF_PV-SVdxy_zoom_eff_num"]->Fill(KVF_PVSVdist_2D);
        (*hists)[prefix+"_KVF_PV-SVdxy_zoom2_eff_num"]->Fill(KVF_PVSVdist_2D);
        (*hists)[prefix+"_KVF_PV-SVdxyz_eff_num"]->Fill(KVF_PVSVdist);
        (*hists)[prefix+"_KVF_PV-SVdxyz_zoom_eff_num"]->Fill(KVF_PVSVdist);
        (*hists)[prefix+"_KVF_gen_PV-SVdxy_eff_num"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom_eff_num"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_num"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_KVF_ctau_eff_num"]->Fill(_ctauHN);
        (*hists)[prefix+"_KVF_ctau_zoom_eff_num"]->Fill(_ctauHN);
        (*hists)[prefix+"_KVF_ctau_zoom2_eff_num"]->Fill(_ctauHN);
        (*hists)[prefix+"_KVF_PV-SVdxyz_onlySVgen-reco_eff_num"]->Fill(KVF_PVSVdist);
    } 
}


void full_analyzer::give_alphanumeric_labels(std::map<TString, TH1*>* hists, TString prefix)
{
    TString SSorOS = (prefix.Index("SS") == -1)? "OS" : "SS";
    TString l = (prefix.Index("_e") == -1)? "_mm" : "_ee";

    //int nx_MVAvsPOGMedium = 4;
    //const char *MVAvsPOGMedium_labels[nx_MVAvsPOGMedium] = {"MVA, POGMedium", "MVA, no POGMedium", "no MVA, POGMedium", "no MVA, no POGMedium"};
    //for(int i = 0; i < nx_MVAvsPOGMedium; i++){
    //    (*hists)[prefix+"_MVAvsPOGMedium_categories"]->GetXaxis()->SetBinLabel(i+1,MVAvsPOGMedium_labels[i]);
    //}
    //if(!isData){
    //    int nx_KVForIVF = 4;
    //    const char *KVForIVF_labels[nx_KVForIVF] = {"IVF, KVF", "IVF, no KVF", "no IVF, KVF", "no IVF, no KVF"};
    //    for(int i = 0; i < nx_KVForIVF; i++){ 
    //        (*hists)[prefix+"_KVForIVF_categories"]->GetXaxis()->SetBinLabel(i+1,KVForIVF_labels[i]);
    //    }
    //}
    //int nx_deltaphivsR = 4;
    //const char *deltaphivsR_labels[nx_deltaphivsR] = {"#Delta #phi, #Delta R", "#Delta #phi, !#Delta R", "!#Delta #phi, #Delta R", "!#Delta #phi, !#Delta R"};
    //for(int i = 0; i < nx_deltaphivsR; i++){ 
    //    (*hists)[prefix+"_deltaphivsR_categories"]->GetXaxis()->SetBinLabel(i+1,deltaphivsR_labels[i]);
    //}
    //int nx_l2_jets = 8;
    //const char *l2_jets_labels[nx_l2_jets] = {"no l2, 0 jet", "no l2, 1 jet", "no l2, 2 jet", "no l2, 3+ jet", "l2, 0 jet", "l2, 1 jet", "l2, 2 jet", "l2, 3+ jet"};
    //for(int i = 0; i < nx_l2_jets; i++){ 
    //    (*hists)[prefix+"_l2_jets_categories"]->GetXaxis()->SetBinLabel(i+1,l2_jets_labels[i]);
    //}
    //int nx_jets = 4;
    //const char *jets_labels[nx_jets] = {"0 jets", "1 jet", "2 jets", "3+ jets"};
    //for(int i = 0; i < nx_jets; i++){ 
    //    (*hists)[prefix+"_jets_categories"]->GetXaxis()->SetBinLabel(i+1,jets_labels[i]);
    //}
    int nx_cutflow = 9;
    const char *cutflow_labels[nx_cutflow] = {"trig.", "l1", "l2", "SV", "#{Delta}#{phi}_{ll}>0.4", "M_{ll}>10", "jetl2", "N_{jet}<2", "N_{l}=2"};
    for(int i = 0; i < nx_cutflow; i++){
        (*hists)[prefix+"_cutflow"]->GetXaxis()->SetBinLabel(i+1, cutflow_labels[i]);
    }
    (*hists)[prefix+"_cutflow"]->SetCanExtend(false);
    int nx_cutflow2 = 7;
    const char *cutflow2_labels[nx_cutflow2] = {"l1+l2", "SV", "#{Delta}#{phi}_{ll}>0.4", "M_{ll}>10", "jetl2", "N_{jet}<2", "N_{l}=2"};
    for(int i = 0; i < nx_cutflow2; i++){
        (*hists)[prefix+"_cutflow2"]->GetXaxis()->SetBinLabel(i+1, cutflow2_labels[i]);
    }
    (*hists)[prefix+"_cutflow2"]->SetCanExtend(false);
    //int nx_dxy = 3;
    //if(!isData){
    //    int nx_IVF = 3;
    //    const char *IVF_labels[nx_IVF] = {"Preselection", "Vertex", "|SV-SVgen| < 0.2cm"};
    //    for(int i = 0; i < nx_IVF; i++){
    //        (*hists)[l+"_IVF_cutflow"]->GetXaxis()->SetBinLabel(i+1, IVF_labels[i]);
    //    }
    //}
    int nx_nDispl = 3;
    const char *nDispl_labels[nx_nDispl] = {"No l2", "e OR #mu", "e AND #mu"};
    for(int i = 0; i < nx_nDispl; i++){
        (*hists)[prefix+"_nDispleAndmu"]->GetXaxis()->SetBinLabel(i+1, nDispl_labels[i]);
    }
    (*hists)[prefix+"_nDispleAndmu"]->SetCanExtend(false);
}

