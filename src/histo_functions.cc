//////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include <iostream>

#include "../interface/full_analyzer.h"

using namespace std;


void full_analyzer::add_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix){
    add_general_histograms(hists, prefix);
    //add_jet_histograms(hists, prefix);
    //add_gen_histograms(hists, prefix);
    //add_KVF_eff_histograms(hists, prefix);
    //add_IVF_eff_histograms(hists, prefix);
    //add_chargeflip_histograms(hists, hists2D, prefix);
    add_MET_histograms(hists, hists2D, prefix);
    init_HLT_efficiency(hists, prefix);
}


void full_analyzer::add_general_histograms(std::map<TString, TH1*>* hists, TString prefix){
    // Plotting histograms
    //(*hists)[prefix+"_l2_jets_categories"]              = new TH1F(prefix+"_l2_jets_categories", ";;Events", 8, 0, 8);
    //(*hists)[prefix+"_jets_categories"]                 = new TH1F(prefix+"_jets_categories", ";;Events", 4, 0, 4);
    //(*hists)[prefix+"_PVSVdxyz_categories"]             = new TH1F(prefix+"_PVSVdxyz_categories", ";;Events", 8, 0, 8);
    //(*hists)[prefix+"_PVSVdxy_categories"]              = new TH1F(prefix+"_PVSVdxy_categories", ";;Events", 8, 0, 8);
    //(*hists)[prefix+"_MVAvsPOGMedium_categories"]       = new TH1F(prefix+"_MVAvsPOGMedium_categories", ";;Events", 4, 0, 4);
    (*hists)[prefix+"_cutflow"]                         = new TH1F(prefix+"_cutflow", ";;Events", 8, 0, 8);
    (*hists)[prefix+"_dxy_cutflow"]                     = new TH1F(prefix+"_dxy_cutflow", ";;Events", 3, 0, 3);
    //(*hists)[prefix+"_deltaphivsR_categories"]          = new TH1F(prefix+"_deltaphivsR_categories", ";;Events", 4, 0, 4);

    (*hists)[prefix+"_nTightEle"]                       = new TH1F(prefix+"_nTightEle", ";N_{prompt electron};Events", 10, 0, 10);
    (*hists)[prefix+"_nTightMu"]                        = new TH1F(prefix+"_nTightMu", ";N_{prompt muon};Events", 10, 0, 10);
    (*hists)[prefix+"_nTight"]                          = new TH1F(prefix+"_nTight", ";N_{prompt e,mu};Events", 10, 0, 10);
    (*hists)[prefix+"_nJets_uncl"]                      = new TH1F(prefix+"_nJets_uncl", ";N_{jets(uncl.)};Events", 10, 0, 10);
    (*hists)[prefix+"_nJets_cl"]                        = new TH1F(prefix+"_nJets_cl", ";N_{jets(cl.)};Events", 10, 0, 10);
    (*hists)[prefix+"_l1_pt"]                           = new TH1F(prefix+"_l1_pt", ";l_{1} #it{p}_{T} [GeV];Events", 30, 0, 100);
    (*hists)[prefix+"_l2_pt"]                           = new TH1F(prefix+"_l2_pt", ";l_{2} #it{p}_{T} [GeV];Events", 30, 0, 100);
    (*hists)[prefix+"_l1_eta"]                          = new TH1F(prefix+"_l1_eta", ";l_{1} #eta;Events", 30, -3, 3);
    (*hists)[prefix+"_l2_eta"]                          = new TH1F(prefix+"_l2_eta", ";l_{2} #eta;Events", 30, -3, 3);
    (*hists)[prefix+"_l1_dxy"]                          = new TH1F(prefix+"_l1_dxy", ";l_{1} dxy [cm];Events", 30, 0, 0.02);
    (*hists)[prefix+"_l2_dxy"]                          = new TH1F(prefix+"_l2_dxy", ";l_{2} dxy [cm];Events", 30, 0, 0.5);
    (*hists)[prefix+"_l1_dz"]                           = new TH1F(prefix+"_l1_dz", ";l_{1} dz [cm];Events", 30, 0, 0.1);
    (*hists)[prefix+"_l2_dz"]                           = new TH1F(prefix+"_l2_dz", ";l_{2} dz [cm];Events", 30, 0, 0.1);
    (*hists)[prefix+"_l1_reliso"]                       = new TH1F(prefix+"_l1_reliso", ";l_{1} Rel Iso;Events", 30, 0, 0.1);
    (*hists)[prefix+"_l2_reliso"]                       = new TH1F(prefix+"_l2_reliso", ";l_{2} Rel Iso;Events", 30, 0, 0.1);
    (*hists)[prefix+"_l2_reliso_zoom"]                  = new TH1F(prefix+"_l2_reliso_zoom", ";l_{2} Rel Iso;Events", 30, 0, 0.05);
    (*hists)[prefix+"_l1_ptrel"]                        = new TH1F(prefix+"_l1_ptrel", ";l_{1} #it{p}_{T}^{rel} [GeV];Events", 30, 0, 40);
    (*hists)[prefix+"_l2_ptrel"]                        = new TH1F(prefix+"_l2_ptrel", ";l_{2} #it{p}_{T}^{rel} [GeV];Events", 30, 0, 40);
    (*hists)[prefix+"_l1_ptratio"]                      = new TH1F(prefix+"_l1_ptratio", ";l_{1} #it{p}_{T}^{ratio} [GeV];Events", 30, 0, 1);
    (*hists)[prefix+"_l2_ptratio"]                      = new TH1F(prefix+"_l2_ptratio", ";l_{2} #it{p}_{T}^{ratio} [GeV];Events", 30, 0, 1);
    (*hists)[prefix+"_l1_selectedTrackMult"]            = new TH1F(prefix+"_l1_selectedTrackMult", ";l_{1} selectedTrackMult;Events", 15, 0, 15);
    (*hists)[prefix+"_l2_selectedTrackMult"]            = new TH1F(prefix+"_l2_selectedTrackMult", ";l_{2} selectedTrackMult;Events", 15, 0, 15);
    (*hists)[prefix+"_l1_3dIP"]                         = new TH1F(prefix+"_l1_3dIP", ";l_{1} 3dIP;Events", 30, 0, 0.05);
    (*hists)[prefix+"_l2_3dIP"]                         = new TH1F(prefix+"_l2_3dIP", ";l_{2} 3dIP;Events", 30, 0, 0.05);
    (*hists)[prefix+"_l1_3dIPSig"]                      = new TH1F(prefix+"_l1_3dIPSig", ";l_{1} 3dIPSig;Events", 30, 0, 4);
    (*hists)[prefix+"_l2_3dIPSig"]                      = new TH1F(prefix+"_l2_3dIPSig", ";l_{2} 3dIPSig;Events", 30, 0, 4);
    (*hists)[prefix+"_mll"]                             = new TH1F(prefix+"_mll", ";#it{m}_{ll} [GeV];Events", 30, 70, 110);
    (*hists)[prefix+"_Zpeak"]                           = new TH1F(prefix+"_Zpeak", ";On-Z;Events", 1, 0, 1);
    (*hists)[prefix+"_dphill"]                          = new TH1F(prefix+"_dphill", ";#it{#Delta #phi}_{ll};Events", 30, 0, 3.14);
    (*hists)[prefix+"_dRll"]                            = new TH1F(prefix+"_dRll", ";#it{#Delta R}_{ll};Events", 30, 0, 6);
    (*hists)[prefix+"_nTrueInteractions"]               = new TH1F(prefix+"_nTrueInteractions", ";N_{PV}^{gen};Events", 100, 0, 100);
    
    if(extensive_plots){
        (*hists)[prefix+"_l1_phi"]                          = new TH1F(prefix+"_l1_phi", ";l_{1} #phi;Events", 30, 0, 3.14);
        (*hists)[prefix+"_l2_phi"]                          = new TH1F(prefix+"_l2_phi", ";l_{2} #phi;Events", 30, 0, 3.14);
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
    if(_l1l2_Full_noTrigger){
        fill_HLT_efficiency(hists, sr_flavor);
    }

    if(_l1l2_Full){
        fill_relevant_histograms(hists, sr_flavor, ev_weight);
        fill_MET_histograms(hists, hists2D, sr_flavor, ev_weight);
    }
}


void full_analyzer::fill_relevant_histograms(std::map<TString, TH1*>* hists, TString prefix, double event_weight){
    fill_general_histograms(hists, prefix, event_weight);
    //fill_IVF_histograms(hists, hists2D, prefix, event_weight);
    //fill_jet_histograms(hists, prefix, event_weight);
}


void full_analyzer::fill_general_histograms(std::map<TString, TH1*>* hists, TString prefix, double event_weight){

    (*hists)[prefix+"_nTightEle"]->Fill(nTightEle, event_weight);
    (*hists)[prefix+"_nTightMu"]->Fill(nTightMu, event_weight);
    (*hists)[prefix+"_nTight"]->Fill(nTightEle + nTightMu, event_weight);
    (*hists)[prefix+"_nJets_uncl"]->Fill(nTightJet_uncl, event_weight);
    (*hists)[prefix+"_nJets_cl"]->Fill(nTightJet, event_weight);
    

    (*hists)[prefix+"_l1_pt"]->Fill(_lPt[i_leading], event_weight);
    (*hists)[prefix+"_l2_pt"]->Fill(_lPt[i_subleading], event_weight);
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

    (*hists)[prefix+"_mll"]->Fill(mll, event_weight);
    if(mll > 80 and mll < 100) (*hists)[prefix+"_Zpeak"]->Fill(1, event_weight);
    (*hists)[prefix+"_dphill"]->Fill(dphill, event_weight);
    (*hists)[prefix+"_dRll"]->Fill(dRll, event_weight);
    if(extensive_plots){
        (*hists)[prefix+"_l1_phi"]->Fill(_lPhi[i_leading], event_weight);
        (*hists)[prefix+"_l2_phi"]->Fill(_lPhi[i_subleading], event_weight);
        (*hists)[prefix+"_l2_dxy_zoom"]->Fill(fabs(_dxy[i_subleading]), event_weight);
        (*hists)[prefix+"_l1_3dIP"]->Fill(_3dIP[i_leading], event_weight);
        (*hists)[prefix+"_l2_3dIP"]->Fill(_3dIP[i_subleading], event_weight);
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
        (*hists)[prefix+"_nTrueInteractions"]->Fill(_nTrueInt, event_weight);
    }
}

void full_analyzer::fill_cutflow(std::map<TString, TH1*>* hists, TString prefix, double event_weight){
    if(i_subleading == -1) return;
    /*
     * Cutflow
     */
    if(_l1l2)                   (*hists)[prefix+"_cutflow"]->Fill(0., event_weight);
    if(_l1l2_Full)                 (*hists)[prefix+"_cutflow"]->Fill(1., event_weight);

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
     * dxy > 0.01cm and 0.02cm
     */
    if(i_subleading != -1){
        (*hists)[prefix+"_dxy_cutflow"]->Fill(0., event_weight);
        if(fabs(_dxy[i_subleading]) > 0.01) (*hists)[prefix+"_dxy_cutflow"]->Fill(1., event_weight);
        if(fabs(_dxy[i_subleading]) > 0.02) (*hists)[prefix+"_dxy_cutflow"]->Fill(2., event_weight);
    }
}


void full_analyzer::fill_lepton_eff(std::map<TString, TH1*>* hists, TString prefix){
    if(isData) return;
    (*hists)[prefix+"_l2_pt_eff_den"]->Fill(_lPt[i_subleading]);
    if(subleadingIsl2){
        (*hists)[prefix+"_l2_pt_eff_num"]->Fill(_lPt[i_subleading]);
    }
    (*hists)[prefix+"_l1_pt_eff_den"]->Fill(_lPt[i_leading]);
    if(leadingIsl1){
        (*hists)[prefix+"_l1_pt_eff_num"]->Fill(_lPt[i_leading]);
    }
}


void full_analyzer::give_alphanumeric_labels(std::map<TString, TH1*>* hists, TString prefix)
{
    TString SSorOS = (prefix.Index("SS") == -1)? "OS" : "SS";
    TString l = (prefix.Index("_e") == -1)? "mu" : "e";

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
    int nx_cutflow = 8;
    const char *cutflow_labels[nx_cutflow] = {"trig", "l1", "l1+l2", "SV", "jetl2", "FullNoPFN", "CR dphi", "CR mll"};
    for(int i = 0; i < nx_cutflow; i++){
        (*hists)[prefix+"_cutflow"]->GetXaxis()->SetBinLabel(i+1, cutflow_labels[i]);
    }
    int nx_dxy = 3;
    const char *dxy_labels[nx_dxy] = {"No dxy cut", "dxy(l2) > 0.01cm", "dxy(l2) > 0.02cm"};
    for(int i = 0; i < nx_dxy; i++){
        (*hists)[prefix+"_dxy_cutflow"]->GetXaxis()->SetBinLabel(i+1, dxy_labels[i]);
    }
}

