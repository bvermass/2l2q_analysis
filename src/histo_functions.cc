//////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include <iostream>

#include "../interface/full_analyzer.h"

using namespace std;


void full_analyzer::add_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix){
    (*hists)[prefix+"_l2_jets_categories"]              = new TH1F(prefix+"_l2_jets_categories", ";;Events", 8, 0, 8);
    (*hists)[prefix+"_jets_categories"]                 = new TH1F(prefix+"_jets_categories", ";;Events", 4, 0, 4);
    (*hists)[prefix+"_dxy_cutflow"]                     = new TH1F(prefix+"_dxy_cutflow", ";;Events", 3, 0, 3);
    (*hists)[prefix+"_MVAvsPOGMedium_categories"]       = new TH1F(prefix+"_MVAvsPOGMedium_categories", ";;Events", 4, 0, 4);
    (*hists)[prefix+"_cutflow"]                         = new TH1F(prefix+"_cutflow", ";;Events", 8, 0, 8);
    (*hists)[prefix+"_deltaphivsR_categories"]          = new TH1F(prefix+"_deltaphivsR_categories", ";;Events", 4, 0, 4);

    (*hists)[prefix+"_nEle"]                            = new TH1F(prefix+"_nEle", ";N_{electron};Events", 10, 0, 10);
    (*hists)[prefix+"_nMu"]                             = new TH1F(prefix+"_nMu", ";N_{muon};Events", 10, 0, 10);
    (*hists)[prefix+"_nLight"]                          = new TH1F(prefix+"_nLight", ";N_{lepton};Events", 10, 0, 10);
    (*hists)[prefix+"_nJets_uncl"]                      = new TH1F(prefix+"_nJets_uncl", ";N_{jets(uncl.)};Events", 10, 0, 10);
    (*hists)[prefix+"_nJets_cl"]                        = new TH1F(prefix+"_nJets_cl", ";N_{jets(cl.)};Events", 10, 0, 10);
    (*hists)[prefix+"_l1_pt"]                           = new TH1F(prefix+"_l1_pt", ";l_{1} #it{p}_{T} [GeV];Events", 30, 0, 100);
    (*hists)[prefix+"_l2_pt"]                           = new TH1F(prefix+"_l2_pt", ";l_{2} #it{p}_{T} [GeV];Events", 30, 0, 100);
    (*hists)[prefix+"_l1_eta"]                          = new TH1F(prefix+"_l1_eta", ";l_{1} #eta;Events", 30, -3, 3);
    (*hists)[prefix+"_l2_eta"]                          = new TH1F(prefix+"_l2_eta", ";l_{2} #eta;Events", 30, -3, 3);
    (*hists)[prefix+"_l1_phi"]                          = new TH1F(prefix+"_l1_phi", ";l_{1} #phi;Events", 30, 0, 3.14);
    (*hists)[prefix+"_l2_phi"]                          = new TH1F(prefix+"_l2_phi", ";l_{2} #phi;Events", 30, 0, 3.14);
    (*hists)[prefix+"_l1_dxy"]                          = new TH1F(prefix+"_l1_dxy", ";l_{1} dxy [cm];Events", 30, 0, 0.02);
    (*hists)[prefix+"_l2_dxy_zoom"]                     = new TH1F(prefix+"_l2_dxy_zoom", ";l_{2} dxy [cm];Events", 30, 0, 0.05);
    (*hists)[prefix+"_l2_dxy"]                          = new TH1F(prefix+"_l2_dxy", ";l_{2} dxy [cm];Events", 30, 0, 0.02);
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
    (*hists)[prefix+"_mll"]                             = new TH1F(prefix+"_mll", ";#it{m}_{ll} [GeV];Events", 30, 0, 200);
    (*hists)[prefix+"_dphill"]                          = new TH1F(prefix+"_dphill", ";#it{#Delta #phi}_{ll};Events", 30, 0, 3.14);
    (*hists)[prefix+"_dRll"]                            = new TH1F(prefix+"_dRll", ";#it{#Delta R}_{ll};Events", 30, 0, 6);
    (*hists)[prefix+"_dRl2jet1_cl"]                     = new TH1F(prefix+"_dRl2jet1_cl", ";#it{#Delta R}(l_{2},jet_{1}^{cl});Events", 30, 0, 6);
    (*hists)[prefix+"_dRl2jet2_cl"]                     = new TH1F(prefix+"_dRl2jet2_cl", ";#it{#Delta R}(l_{2},jet_{2}^{cl});Events", 30, 0, 6);
    (*hists)[prefix+"_dRjet1jet2_cl"]                   = new TH1F(prefix+"_dRjet1jet2_cl", ";#it{#Delta R}(jet_{1}^{cl},jet_{2}^{cl});Events", 30, 0, 6);
    (*hists2D)[prefix+"_dRl2jet1_2_cl"]                 = new TH2F(prefix+"_dRl2jet1_2_cl", ";#it{#Delta R}(l_{2}, jet_{1}^{cl});#it{#Delta R}(l_{2}, jet_{2}^{cl})", 30, 0, 6, 30, 0, 6);
    (*hists)[prefix+"_dRl2jet1_uncl"]                   = new TH1F(prefix+"_dRl2jet1_uncl", ";#it{#Delta R}(l_{2},jet_{1}^{uncl});Events", 30, 0, 6);
    (*hists)[prefix+"_dRl2jet2_uncl"]                   = new TH1F(prefix+"_dRl2jet2_uncl", ";#it{#Delta R}(l_{2},jet_{2}^{uncl});Events", 30, 0, 6);
    (*hists)[prefix+"_dRjet1jet2_uncl"]                 = new TH1F(prefix+"_dRjet1jet2_uncl", ";#it{#Delta R}(jet_{1}^{uncl},jet_{2}^{uncl});Events", 30, 0, 6);
    (*hists2D)[prefix+"_dRl2jet1_2_uncl"]               = new TH2F(prefix+"_dRl2jet1_2_uncl", ";#it{#Delta R}(l_{2}, jet_{1}^{uncl});#it{#Delta R}(l_{2}, jet_{2}^{uncl})", 30, 0, 6, 30, 0, 6);

    add_gen_histograms(hists, prefix);
    add_MET_histograms(hists, prefix);
}


void full_analyzer::fill_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, int i_leading, int i_subleading){

    fill_MET_histograms(hists, prefix, i_leading, i_subleading);

    int nEle    = 0;
    int nMu     = 0;
    for(unsigned i = 0; i < _nL; i++){
        if(looseElectronID[i] and ele_clean_loose[i]) nEle++;
        if(looseMuonID[i]) nMu++;
    }

    int nJets_uncl = 0;
    int nJets_cl = 0;
    std::vector<LorentzVector> jets_uncl;
    std::vector<LorentzVector> jets_cl;
    for(unsigned i = 0; i < _nJets; i++){
        if(fullJetID[i]){ 
            LorentzVector tmp(_jetPt[i], _jetEta[i], _jetPhi[i], _jetE[i]);
            jets_uncl.push_back(tmp);
            nJets_uncl++;
        }
        if(fullJetID[i] and jet_clean_full[i]){
            LorentzVector tmp(_jetPt[i], _jetEta[i], _jetPhi[i], _jetE[i]);
            jets_cl.push_back(tmp);
            nJets_cl++;
        }
    }

    (*hists)[prefix+"_nEle"]->Fill(nEle, event_weight);
    (*hists)[prefix+"_nMu"]->Fill(nMu, event_weight);
    (*hists)[prefix+"_nLight"]->Fill(nEle + nMu, event_weight);
    (*hists)[prefix+"_nJets_uncl"]->Fill(nJets_uncl, event_weight);
    (*hists)[prefix+"_nJets_cl"]->Fill(nJets_cl, event_weight);

    (*hists)[prefix+"_l1_pt"]->Fill(_lPt[i_leading], event_weight);
    (*hists)[prefix+"_l2_pt"]->Fill(_lPt[i_subleading], event_weight);
    (*hists)[prefix+"_l1_eta"]->Fill(_lEta[i_leading], event_weight);
    (*hists)[prefix+"_l2_eta"]->Fill(_lEta[i_subleading], event_weight);
    (*hists)[prefix+"_l1_phi"]->Fill(_lPhi[i_leading], event_weight);
    (*hists)[prefix+"_l2_phi"]->Fill(_lPhi[i_subleading], event_weight);
    (*hists)[prefix+"_l1_dxy"]->Fill(fabs(_dxy[i_leading]), event_weight);
    (*hists)[prefix+"_l2_dxy"]->Fill(fabs(_dxy[i_subleading]), event_weight);
    (*hists)[prefix+"_l2_dxy_zoom"]->Fill(fabs(_dxy[i_subleading]), event_weight);
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
    (*hists)[prefix+"_l1_3dIP"]->Fill(_3dIP[i_leading], event_weight);
    (*hists)[prefix+"_l2_3dIP"]->Fill(_3dIP[i_subleading], event_weight);
    (*hists)[prefix+"_l1_3dIPSig"]->Fill(_3dIPSig[i_leading], event_weight);
    (*hists)[prefix+"_l2_3dIPSig"]->Fill(_3dIPSig[i_subleading], event_weight);

    (*hists)[prefix+"_mll"]->Fill(get_mll(i_leading, i_subleading), event_weight);
    (*hists)[prefix+"_dphill"]->Fill(get_dphill(i_leading, i_subleading), event_weight);
    (*hists)[prefix+"_dRll"]->Fill(get_dRll(i_leading, i_subleading), event_weight);
    LorentzVector l2_vec(_lPt[i_subleading], _lEta[i_subleading], _lPhi[i_subleading], _lE[i_subleading]);
    if(nJets_uncl > 0) (*hists)[prefix+"_dRl2jet1_uncl"]->Fill(deltaR(l2_vec, jets_uncl[0]), event_weight);
    if(nJets_uncl > 1) (*hists)[prefix+"_dRl2jet2_uncl"]->Fill(deltaR(l2_vec, jets_uncl[1]), event_weight);
    if(nJets_uncl > 1) (*hists)[prefix+"_dRjet1jet2_uncl"]->Fill(deltaR(jets_uncl[0], jets_uncl[1]), event_weight);
    if(nJets_uncl > 1) (*hists2D)[prefix+"_dRl2jet1_2_uncl"]->Fill(deltaR(l2_vec, jets_uncl[0]), deltaR(l2_vec, jets_uncl[1]), event_weight);
    if(nJets_cl > 0) (*hists)[prefix+"_dRl2jet1_cl"]->Fill(deltaR(l2_vec, jets_cl[0]), event_weight);
    if(nJets_cl > 1) (*hists)[prefix+"_dRl2jet2_cl"]->Fill(deltaR(l2_vec, jets_cl[1]), event_weight);
    if(nJets_cl > 1) (*hists)[prefix+"_dRjet1jet2_cl"]->Fill(deltaR(jets_cl[0], jets_cl[1]), event_weight);
    if(nJets_cl > 1) (*hists2D)[prefix+"_dRl2jet1_2_cl"]->Fill(deltaR(l2_vec, jets_cl[0]), deltaR(l2_vec, jets_cl[1]), event_weight);

    if(sampleflavor.Index("Run") == -1){
        (*hists)[prefix+"_nTrueInteractions"]->Fill(_nTrueInt, event_weight);
    }
}

void full_analyzer::fill_cutflow_e(std::map<TString, TH1*>* hists, TString prefix){
    int SSorOS = (prefix.Index("OS") == -1)? 2 : 0;

 
    /*
     * Cutflow
     */
    if(_1e1disple and fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS){ 
                                        (*hists)[prefix+"_cutflow"]->Fill(0., event_weight);
        if(_1e1displevtx)               (*hists)[prefix+"_cutflow"]->Fill(1., event_weight);
        if(_1e1displedispl)             (*hists)[prefix+"_cutflow"]->Fill(2., event_weight);
        if(_1e1disple0adde)             (*hists)[prefix+"_cutflow"]->Fill(3., event_weight);
        if(_1e1displemll)               (*hists)[prefix+"_cutflow"]->Fill(4., event_weight);
        if(_1e1displedphi)              (*hists)[prefix+"_cutflow"]->Fill(5., event_weight);
        if(_1e1displeReliso)            (*hists)[prefix+"_cutflow"]->Fill(6., event_weight);
        if(_1e1disple1jet)              (*hists)[prefix+"_cutflow"]->Fill(7., event_weight);
    }

    /*
     * MVA ID versus cutbased medium prompt ID
     */
    if(_1e and _1pogmediume)    (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(0., event_weight);
    if(_1e and !_1pogmediume)   (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(1., event_weight);
    if(!_1e and _1pogmediume)   (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(2., event_weight);
    if(!_1e and !_1pogmediume)  (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(3., event_weight);

    /*
     * Delta phi(ll) > 2.4 versus 1 < Delta R(ll) < 5.5
     */
    if(_1e1displedphi and _1e1displedR) (*hists)[prefix+"_deltaphivsR_categories"]->Fill(0., event_weight);
    if(_1e1displedphi and !_1e1displedR) (*hists)[prefix+"_deltaphivsR_categories"]->Fill(1., event_weight);
    if(!_1e1displedphi and _1e1displedR) (*hists)[prefix+"_deltaphivsR_categories"]->Fill(2., event_weight);
    if(!_1e1displedphi and !_1e1displedR) (*hists)[prefix+"_deltaphivsR_categories"]->Fill(3., event_weight);

    /*
     * l2 identification and jets(cleaned)
     */
    if(_1e){
        if(_1e1disple and fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS){
            if(i_leading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(4., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(5., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(6., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(7., event_weight);
            if(i_leading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(0., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(1., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(2., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_jets_categories"]->Fill(3., event_weight);
        }else {
            if(i_leading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(0., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(1., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(2., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(3., event_weight);
        }
    }

    /*
     * dxy > 0.01cm and 0.05cm
     */
    if(_1e1displevtx and fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS){
        (*hists)[prefix+"_dxy_cutflow"]->Fill(0., event_weight);
        if(fabs(_dxy[i_subleading_displ_e]) > 0.01) (*hists)[prefix+"_dxy_cutflow"]->Fill(1., event_weight);
        if(fabs(_dxy[i_subleading_displ_e]) > 0.05) (*hists)[prefix+"_dxy_cutflow"]->Fill(2., event_weight);
    }
}


void full_analyzer::fill_cutflow_mu(std::map<TString, TH1*>* hists, TString prefix){
    int SSorOS = (prefix.Index("OS") == -1)? 2 : 0;

    /*
     * Cutflow
     */
    if(_1mu1displmu and fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS){ 
                                          (*hists)[prefix+"_cutflow"]->Fill(0., event_weight);
        if(_1mu1displmuvtx)               (*hists)[prefix+"_cutflow"]->Fill(1., event_weight);
        if(_1mu1displmudispl)             (*hists)[prefix+"_cutflow"]->Fill(2., event_weight);
        if(_1mu1displmu0addmu)            (*hists)[prefix+"_cutflow"]->Fill(3., event_weight);
        if(_1mu1displmumll)               (*hists)[prefix+"_cutflow"]->Fill(4., event_weight);
        if(_1mu1displmudphi)              (*hists)[prefix+"_cutflow"]->Fill(5., event_weight);
        if(_1mu1displmuReliso)            (*hists)[prefix+"_cutflow"]->Fill(6., event_weight);
        if(_1mu1displmu1jet)              (*hists)[prefix+"_cutflow"]->Fill(7., event_weight);
    }

    /*
     * MVA ID versus cutbased medium prompt ID
     */
    if(_1mu and _1pogmediummu)    (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(0., event_weight);
    if(_1mu and !_1pogmediummu)   (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(1., event_weight);
    if(!_1mu and _1pogmediummu)   (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(2., event_weight);
    if(!_1mu and !_1pogmediummu)  (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(3., event_weight);

    /*
     * Delta phi(ll) > 2.4 versus 1 < Delta R(ll) < 5.5
     */
    if(_1mu1displmudphi and _1mu1displmudR) (*hists)[prefix+"_deltaphivsR_categories"]->Fill(0., event_weight);
    if(_1mu1displmudphi and !_1mu1displmudR) (*hists)[prefix+"_deltaphivsR_categories"]->Fill(1., event_weight);
    if(!_1mu1displmudphi and _1mu1displmudR) (*hists)[prefix+"_deltaphivsR_categories"]->Fill(2., event_weight);
    if(!_1mu1displmudphi and !_1mu1displmudR) (*hists)[prefix+"_deltaphivsR_categories"]->Fill(3., event_weight);

    /*
     * l2 identification and jets(cleaned)
     */
    if(_1mu){
        if(_1mu1displmu and fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS){
            if(i_leading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(4., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(5., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(6., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(7., event_weight);
            if(i_leading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(0., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(1., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(2., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_jets_categories"]->Fill(3., event_weight);
        }else {
            if(i_leading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(0., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(1., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(2., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(3., event_weight);
        }
    }

    /*
     * dxy > 0.01cm and 0.05cm
     */
    if(_1mu1displmuvtx and fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS){
        (*hists)[prefix+"_dxy_cutflow"]->Fill(0., event_weight);
        if(fabs(_dxy[i_subleading_displ_mu]) > 0.01) (*hists)[prefix+"_dxy_cutflow"]->Fill(1., event_weight);
        if(fabs(_dxy[i_subleading_displ_mu]) > 0.05) (*hists)[prefix+"_dxy_cutflow"]->Fill(2., event_weight);
    }
}


void full_analyzer::fill_lepton_eff(std::map<TString, TH1*>* hists, TString prefix, int i_leading, int i_subleading){
    if(sampleflavor.Index("Run") != -1) return;
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

    int nx_MVAvsPOGMedium = 4;
    const char *MVAvsPOGMedium_labels[nx_MVAvsPOGMedium] = {"MVA, POGMedium", "MVA, no POGMedium", "no MVA, POGMedium", "no MVA, no POGMedium"};
    for(int i = 0; i < nx_MVAvsPOGMedium; i++){ 
        (*hists)[prefix+"_MVAvsPOGMedium_categories"]->GetXaxis()->SetBinLabel(i+1,MVAvsPOGMedium_labels[i]);
    }
    int nx_deltaphivsR = 4;
    const char *deltaphivsR_labels[nx_deltaphivsR] = {"#Delta #phi, #Delta R", "#Delta #phi, !#Delta R", "!#Delta #phi, #Delta R", "!#Delta #phi, !#Delta R"};
    for(int i = 0; i < nx_deltaphivsR; i++){ 
        (*hists)[prefix+"_deltaphivsR_categories"]->GetXaxis()->SetBinLabel(i+1,deltaphivsR_labels[i]);
    }
    int nx_l2_jets = 8;
    const char *l2_jets_labels[nx_l2_jets] = {"no l2, 0 jet", "no l2, 1 jet", "no l2, 2 jet", "no l2, 3+ jet", "l2, 0 jet", "l2, 1 jet", "l2, 2 jet", "l2, 3+ jet"};
    for(int i = 0; i < nx_l2_jets; i++){ 
        (*hists)[prefix+"_l2_jets_categories"]->GetXaxis()->SetBinLabel(i+1,l2_jets_labels[i]);
    }
    int nx_jets = 4;
    const char *jets_labels[nx_jets] = {"0 jets", "1 jet", "2 jets", "3+ jets"};
    for(int i = 0; i < nx_jets; i++){ 
        (*hists)[prefix+"_jets_categories"]->GetXaxis()->SetBinLabel(i+1,jets_labels[i]);
    }
    int nx_cutflow = 8;
    const char *cutflow_labels[nx_cutflow] = {"good l2", "Vertex", "dxy(l2) > 0.01cm", "lepton veto", "M_{ll}", "#Delta #phi", "I_{rel}", "#leq 1jet"};
    for(int i = 0; i < nx_cutflow; i++){
        (*hists)[prefix+"_cutflow"]->GetXaxis()->SetBinLabel(i+1, cutflow_labels[i]);
    }
    int nx_dxy = 3;
    const char *dxy_labels[nx_dxy] = {"No dxy cut", "dxy(l2) > 0.01cm", "dxy(l2) > 0.05cm"};
    for(int i = 0; i < nx_dxy; i++){
        (*hists)[prefix+"_dxy_cutflow"]->GetXaxis()->SetBinLabel(i+1, dxy_labels[i]);
    }
}

