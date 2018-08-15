///////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include <iostream>

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::add_histograms(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_pt"]                  = new TH1F(prefix+"_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_leadpt"]              = new TH1F(prefix+"_leadpt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_dxy"]                 = new TH1F(prefix+"_dxy", ";#Delta_{xy} [cm];Events", 80, 0, 10);
    (*hists)[prefix+"_mll"]                 = new TH1F(prefix+"_mll", ";#it{m}_{ll} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_dphill"]              = new TH1F(prefix+"_dphill", ";#it{#Delta #phi}_{ll};Events", 80, 0, 3.14);
    (*hists)[prefix+"_dRll"]                = new TH1F(prefix+"_dRll", ";#it{#Delta R}_{ll};Events", 80, 0, 6);
    (*hists)[prefix+"_vtxfitgen"]           = new TH1F(prefix+"_vtxfitgen", ";|Vtx_{fit} - Vtx_{gen}| [cm];Events", 80, 0, 10);
    (*hists)[prefix+"_chi2"]                = new TH1F(prefix+"_chi2", ";#Chi^{2};Events", 80, 0, 80);
    (*hists)[prefix+"_normchi2"]            = new TH1F(prefix+"_normchi2", ";Normalized #Chi^{2};Events", 80, 0, 80);
    (*hists)[prefix+"_vtxfitPV"]            = new TH1F(prefix+"_vtxfitPV", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 80, 0, 10);
    (*hists)[prefix+"_vtxfit_ntracks"]      = new TH1F(prefix+"_vtxfit_ntracks", ";# of tracks used in Vtxfit;Events", 15, 0, 15);
    (*hists)[prefix+"_vtxfit_valid"]        = new TH1F(prefix+"_vtxfit_valid", ";is Vertex Valid?;Events", 2, 0, 2);
    (*hists)[prefix+"_ngentr"]              = new TH1F(prefix+"_ngentr", ";Gen-level # of tracks for all events;Events", 15, 0, 15);
    (*hists)[prefix+"_vtxfit_maxdxy"]       = new TH1F(prefix+"_vtxfit_maxdxy", ";dxy_{max} (Valid Vtx);Events", 40, 0, 1.1);
    (*hists)[prefix+"_cutflow"]             = new TH1F(prefix+"_cutflow", ";cutflow;Events", 7, 0, 7);
    (*hists)[prefix+"_l1reliso"]            = new TH1F(prefix+"_l1reliso", ";L1 Rel Iso;Events", 40, 0, 0.3);
    (*hists)[prefix+"_l2reliso"]            = new TH1F(prefix+"_l2reliso", ";L2 Rel Iso;Events", 40, 0, 0.8);
    (*hists)[prefix+"_invVtx_ntracks"]      = new TH1F(prefix+"_invVtx_ntracks", ";# of tracks for invalid vtxfits;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_ngentr"]   = new TH1F(prefix+"_invVtx_1tr_ngentr", ";Gen-level # of tracks for invalid vtx with no found tracks;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_ngenl"]    = new TH1F(prefix+"_invVtx_1tr_ngenl", ";Gen-level # of Leptons for invalid vtx with no found tracks;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_ngene"]    = new TH1F(prefix+"_invVtx_1tr_ngene", ";Gen-level # of Electrons for invalid vtx with no found tracks;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_ngenmu"]   = new TH1F(prefix+"_invVtx_1tr_ngenmu", ";Gen-level # of Muons for invalid vtx with no found tracks;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_deta"]   = new TH1F(prefix+"_invVtx_1tr_deta", ";#Delta #eta;Events", 30, 0, 5);
    (*hists)[prefix+"_invVtx_1tr_dphi"]   = new TH1F(prefix+"_invVtx_1tr_dphi", ";#Delta #phi;Events", 30, 0, 3.14);
    (*hists)[prefix+"_invVtx_1tr_dxy"]   = new TH1F(prefix+"_invVtx_1tr_dxy", ";#Delta_{xy}[cm];Events", 30, 0, 4);
    (*hists)[prefix+"_invVtx_1tr_dz"]   = new TH1F(prefix+"_invVtx_1tr_dz", ";#Delta_{z}[cm];Events", 30, 0, 10);
    return;
}

void full_analyzer::fill_histograms(std::map<TString, TH1*>* hists, TString prefix){
    if(prefix.Index("_e") != -1) fill_histograms_e(hists, prefix);
    else if(prefix.Index("_mu") != -1) fill_histograms_mu(hists, prefix);
    else{ 
        cout << "flavor was not specified in prefix" << endl;
    }
    return;
}

void full_analyzer::fill_histograms_e(std::map<TString, TH1*>* hists, TString prefix){

    (*hists)[prefix+"_leadpt"]->Fill(_lPt[i_leading_e], event_weight);
    (*hists)[prefix+"_pt"]->Fill(_lPt[i_subleading_displ_e], event_weight);
    (*hists)[prefix+"_dxy"]->Fill(_dxy[i_subleading_displ_e], event_weight);
    TLorentzVector lepton1;
    TLorentzVector lepton2;
    lepton1.SetPtEtaPhiE(_lPt[i_leading_e], _lEta[i_leading_e], _lPhi[i_leading_e], _lE[i_leading_e]);
    lepton2.SetPtEtaPhiE(_lPt[i_subleading_displ_e], _lEta[i_subleading_displ_e], _lPhi[i_subleading_displ_e], _lE[i_subleading_displ_e]);
    (*hists)[prefix+"_mll"]->Fill((lepton1 + lepton2).M(), event_weight);
    (*hists)[prefix+"_dphill"]->Fill(fabs(lepton1.DeltaPhi(lepton2)), event_weight);
    (*hists)[prefix+"_dRll"]->Fill(lepton1.DeltaR(lepton2), event_weight);
    (*hists)[prefix+"_vtxfit_valid"]->Fill(_lVtx_valid[i_subleading_displ_e], event_weight);
    (*hists)[prefix+"_ngentr"]->Fill(_gen_nNPackedDtrs, event_weight);
    if(_lVtx_valid[i_subleading_displ_e]){
        (*hists)[prefix+"_vtxfitgen"]->Fill(sqrt((_gen_vertex_x[i_subleading_displ_e] - _lVtxpos_x[i_subleading_displ_e])*(_gen_vertex_x[i_subleading_displ_e] - _lVtxpos_x[i_subleading_displ_e]) + (_gen_vertex_y[i_subleading_displ_e] - _lVtxpos_y[i_subleading_displ_e])*(_gen_vertex_y[i_subleading_displ_e] - _lVtxpos_y[i_subleading_displ_e]) + (_gen_vertex_z[i_subleading_displ_e] - _lVtxpos_z[i_subleading_displ_e])*(_gen_vertex_z[i_subleading_displ_e] - _lVtxpos_z[i_subleading_displ_e])), event_weight);
        (*hists)[prefix+"_chi2"]->Fill(_lVtxpos_chi2[i_subleading_displ_e], event_weight);
        (*hists)[prefix+"_normchi2"]->Fill(_lVtxpos_chi2[i_subleading_displ_e] / _lVtxpos_df[i_subleading_displ_e], event_weight);
        (*hists)[prefix+"_vtxfitPV"]->Fill(_lVtxpos_PVdxy[i_subleading_displ_e], event_weight);
        (*hists)[prefix+"_vtxfit_ntracks"]->Fill(_lVtxpos_ntracks[i_subleading_displ_e], event_weight);
        (*hists)[prefix+"_vtxfit_maxdxy"]->Fill(_lVtxpos_maxdxy[i_subleading_displ_e], event_weight);
    }else{
        (*hists)[prefix+"_invVtx_ntracks"]->Fill(_lVtxpos_ntracks[i_subleading_displ_e], event_weight);
        if(_lVtxpos_ntracks[i_subleading_displ_e] ==1) fill_1tr(hists, prefix, i_subleading_displ_e);
    }
    (*hists)[prefix+"_l1reliso"]->Fill(_relIso[i_leading_e], event_weight);
    (*hists)[prefix+"_l2reliso"]->Fill(_relIso[i_subleading_displ_e], event_weight);
    return;
}


void full_analyzer::fill_histograms_mu(std::map<TString, TH1*>* hists, TString prefix){

    (*hists)[prefix+"_leadpt"]->Fill(_lPt[i_leading_mu], event_weight);
    (*hists)[prefix+"_pt"]->Fill(_lPt[i_subleading_displ_mu], event_weight);
    (*hists)[prefix+"_dxy"]->Fill(_dxy[i_subleading_displ_mu], event_weight);
    TLorentzVector lepton1;
    TLorentzVector lepton2;
    lepton1.SetPtEtaPhiE(_lPt[i_leading_mu], _lEta[i_leading_mu], _lPhi[i_leading_mu], _lE[i_leading_mu]);
    lepton2.SetPtEtaPhiE(_lPt[i_subleading_displ_mu], _lEta[i_subleading_displ_mu], _lPhi[i_subleading_displ_mu], _lE[i_subleading_displ_mu]);
    (*hists)[prefix+"_mll"]->Fill((lepton1 + lepton2).M(), event_weight);
    (*hists)[prefix+"_dphill"]->Fill(fabs(lepton1.DeltaPhi(lepton2)), event_weight);
    (*hists)[prefix+"_dRll"]->Fill(lepton1.DeltaR(lepton2), event_weight);
    (*hists)[prefix+"_vtxfit_valid"]->Fill(_lVtx_valid[i_subleading_displ_mu], event_weight);
    (*hists)[prefix+"_ngentr"]->Fill(_gen_nNPackedDtrs, event_weight);
    if(_lVtx_valid[i_subleading_displ_mu]){
        (*hists)[prefix+"_vtxfitgen"]->Fill(sqrt((_gen_vertex_x[i_subleading_displ_mu] - _lVtxpos_x[i_subleading_displ_mu])*(_gen_vertex_x[i_subleading_displ_mu] - _lVtxpos_x[i_subleading_displ_mu]) + (_gen_vertex_y[i_subleading_displ_mu] - _lVtxpos_y[i_subleading_displ_mu])*(_gen_vertex_y[i_subleading_displ_mu] - _lVtxpos_y[i_subleading_displ_mu]) + (_gen_vertex_z[i_subleading_displ_mu] - _lVtxpos_z[i_subleading_displ_mu])*(_gen_vertex_z[i_subleading_displ_mu] - _lVtxpos_z[i_subleading_displ_mu])), event_weight);
        (*hists)[prefix+"_chi2"]->Fill(_lVtxpos_chi2[i_subleading_displ_mu], event_weight);
        (*hists)[prefix+"_normchi2"]->Fill(_lVtxpos_chi2[i_subleading_displ_mu] / _lVtxpos_df[i_subleading_displ_mu], event_weight);
        (*hists)[prefix+"_vtxfitPV"]->Fill(_lVtxpos_PVdxy[i_subleading_displ_mu], event_weight);
        (*hists)[prefix+"_vtxfit_ntracks"]->Fill(_lVtxpos_ntracks[i_subleading_displ_mu], event_weight);
        (*hists)[prefix+"_vtxfit_maxdxy"]->Fill(_lVtxpos_maxdxy[i_subleading_displ_mu], event_weight);
    }else{
        (*hists)[prefix+"_invVtx_ntracks"]->Fill(_lVtxpos_ntracks[i_subleading_displ_e], event_weight);
        if(_lVtxpos_ntracks[i_subleading_displ_mu] ==1) fill_1tr(hists, prefix, i_subleading_displ_mu);
    }
    (*hists)[prefix+"_l1reliso"]->Fill(_relIso[i_leading_mu], event_weight);
    (*hists)[prefix+"_l2reliso"]->Fill(_relIso[i_subleading_mu], event_weight);
    return;
}


void full_analyzer::fill_cutflow_e(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_cutflow"]->Fill(0.,event_weight); 
    if(_1e) (*hists)[prefix+"_cutflow"]->Fill(1.,event_weight); 
    if(_1e1disple) (*hists)[prefix+"_cutflow"]->Fill(2.,event_weight); 
    if(_1e1disple0adde) (*hists)[prefix+"_cutflow"]->Fill(3.,event_weight); 
    if(_1e1disple0jet) (*hists)[prefix+"_cutflow"]->Fill(4.,event_weight); 
    if(_1e1disple0jet_aftermll) (*hists)[prefix+"_cutflow"]->Fill(5.,event_weight); 
    if(_1e1disple0jet_afterdphi) (*hists)[prefix+"_cutflow"]->Fill(6.,event_weight); 
}


void full_analyzer::fill_cutflow_mu(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_cutflow"]->Fill(0.,event_weight); 
    if(_1mu) (*hists)[prefix+"_cutflow"]->Fill(1.,event_weight); 
    if(_1mu1displmu) (*hists)[prefix+"_cutflow"]->Fill(2.,event_weight); 
    if(_1mu1displmu0addmu) (*hists)[prefix+"_cutflow"]->Fill(3.,event_weight); 
    if(_1mu1displmu0jet) (*hists)[prefix+"_cutflow"]->Fill(4.,event_weight); 
    if(_1mu1displmu0jet_aftermll) (*hists)[prefix+"_cutflow"]->Fill(5.,event_weight); 
    if(_1mu1displmu0jet_afterdphi) (*hists)[prefix+"_cutflow"]->Fill(6.,event_weight); 
}


void full_analyzer::fill_1tr(std::map<TString, TH1*>* hists, TString prefix, int i_lep){
    (*hists)[prefix+"_invVtx_1tr_ngentr"]->Fill(_gen_nNPackedDtrs, event_weight);

    // find out how many leptons are in the packed daughters of HNL
    int i_gen_ne = 0;
    int i_gen_nmu = 0;
    for(int i = 0; i < _gen_nNPackedDtrs; i++){
        if(fabs(_gen_NPackedDtrsPdgId[i]) == 11) i_gen_ne++;
        else if(fabs(_gen_NPackedDtrsPdgId[i] == 13)) i_gen_nmu++;
    }
    (*hists)[prefix+"_invVtx_1tr_ngenl"]->Fill(i_gen_ne + i_gen_nmu, event_weight);
    (*hists)[prefix+"_invVtx_1tr_ngene"]->Fill(i_gen_ne, event_weight);
    (*hists)[prefix+"_invVtx_1tr_ngenmu"]->Fill(i_gen_nmu, event_weight);

    // find gen lepton from HNL
    int i_genlep_HNL = 0;
    for(int i = 0; i < _gen_nL; i++){
        if(fabs(_gen_lMomPdg[i]) == 9900012) i_genlep_HNL = i;
    }
    // using gen lepton from HNL, find lepton from HNL in Packed daughters
    double mineta = 5;
    int i_lepHNL = 0;
    for(int i = 0; i < _gen_nNPackedDtrs; i++){
        if((fabs(_gen_NPackedDtrsPdgId[i]) == 11 || fabs(_gen_NPackedDtrsPdgId[i] == 13)) && fabs(_gen_NPackedDtrsEta[i] - _gen_lEta[i_genlep_HNL]) < mineta){
            mineta = fabs(_gen_NPackedDtrsEta[i] - _gen_lEta[i_genlep_HNL]);
            i_lepHNL = i;//lepton from HNL in packed daughters found
        }
    }
    // if reco lepton is not the correct one, there is no meaning to the following histograms 
    bool correct_reco_lepton = (fabs(_lEta[i_lep] - _gen_NPackedDtrsEta[i_lepHNL]) < 1 && fabs(_lPhi[i_lep] - _gen_NPackedDtrsPhi[i_lepHNL]) < 1 && fabs(_lPt[i_lep] - _gen_NPackedDtrsPt[i_lepHNL]) < 5);
    if(correct_reco_lepton){
        for(int i = 0; i < _gen_nNPackedDtrs; i++){
            if(i == i_lepHNL) continue;
            (*hists)[prefix+"_invVtx_1tr_deta"]->Fill(fabs(_gen_NPackedDtrsEta[i] - _gen_NPackedDtrsEta[i_lepHNL]));
            TLorentzVector lep;
            TLorentzVector track;
            lep.SetPtEtaPhiE(_gen_NPackedDtrsPt[i_lepHNL], _gen_NPackedDtrsEta[i_lepHNL], _gen_NPackedDtrsPhi[i_lepHNL], _gen_NPackedDtrsE[i_lepHNL]);
            track.SetPtEtaPhiE(_gen_NPackedDtrsPt[i], _gen_NPackedDtrsEta[i], _gen_NPackedDtrsPhi[i], _gen_NPackedDtrsE[i]);
            (*hists)[prefix+"_invVtx_1tr_dphi"]->Fill(fabs(lep.DeltaPhi(track)));
            if(matches[i] >= 1) (*hists)[prefix+"_invVtx_1tr_dxy"]->Fill(fabs(_gen_NPackedDtrs_matchdxy[i] - _gen_NPackedDtrs_matchdxy[i_lepHNL]));
            if(matches[i] >= 1) (*hists)[prefix+"_invVtx_1tr_dz"]->Fill(fabs(_gen_NPackedDtrs_matchdz[i] - _gen_NPackedDtrs_matchdz[i_lepHNL]));
        }
    }
}
