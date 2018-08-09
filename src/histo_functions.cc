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
    (*hists)[prefix+"_chi2"]                = new TH1F(prefix+"_chi2", ";#Chi^{2};Events", 80, 0, 2);
    (*hists)[prefix+"_vtxfitPV"]            = new TH1F(prefix+"_vtxfitPV", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 80, 0, 10);
    (*hists)[prefix+"_vtxfit_ntracks"]      = new TH1F(prefix+"_vtxfit_ntracks", ";# of tracks used in Vtxfit;Events", 15, 0, 15);
    (*hists)[prefix+"_vtxfit_valid"]        = new TH1F(prefix+"_vtxfit_valid", ";is Vertex Valid?;Events", 2, 0, 2);
    (*hists)[prefix+"_vtxfit_maxdxy_valid"] = new TH1F(prefix+"_vtxfit_maxdxy_valid", ";dxy_{max} (Valid Vtx);Events", 40, 0, 1.1);
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
    if(_lVtx_valid[i_subleading_displ_e]){
        (*hists)[prefix+"_vtxfitgen"]->Fill(sqrt((_gen_vertex_x[i_subleading_displ_e] - _lVtxpos_x[i_subleading_displ_e])*(_gen_vertex_x[i_subleading_displ_e] - _lVtxpos_x[i_subleading_displ_e]) + (_gen_vertex_y[i_subleading_displ_e] - _lVtxpos_y[i_subleading_displ_e])*(_gen_vertex_y[i_subleading_displ_e] - _lVtxpos_y[i_subleading_displ_e]) + (_gen_vertex_z[i_subleading_displ_e] - _lVtxpos_z[i_subleading_displ_e])*(_gen_vertex_z[i_subleading_displ_e] - _lVtxpos_z[i_subleading_displ_e])), event_weight);
        (*hists)[prefix+"_chi2"]->Fill(_lVtxpos_chi2[i_subleading_e], event_weight);
        (*hists)[prefix+"_vtxfitPV"]->Fill(_lVtxpos_PVdxy[i_subleading_displ_e], event_weight);
        (*hists)[prefix+"_vtxfit_ntracks"]->Fill(_lVtxpos_ntracks[i_subleading_displ_e], event_weight);
        (*hists)[prefix+"_vtxfit_maxdxy_valid"]->Fill(_lVtxpos_maxdxy_valid[i_subleading_displ_e], event_weight);
    }
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
    if(_lVtx_valid[i_subleading_displ_mu]){
        (*hists)[prefix+"_vtxfitgen"]->Fill(sqrt((_gen_vertex_x[i_subleading_displ_mu] - _lVtxpos_x[i_subleading_displ_mu])*(_gen_vertex_x[i_subleading_displ_mu] - _lVtxpos_x[i_subleading_displ_mu]) + (_gen_vertex_y[i_subleading_displ_mu] - _lVtxpos_y[i_subleading_displ_mu])*(_gen_vertex_y[i_subleading_displ_mu] - _lVtxpos_y[i_subleading_displ_mu]) + (_gen_vertex_z[i_subleading_displ_mu] - _lVtxpos_z[i_subleading_displ_mu])*(_gen_vertex_z[i_subleading_displ_mu] - _lVtxpos_z[i_subleading_displ_mu])), event_weight);
        (*hists)[prefix+"_chi2"]->Fill(_lVtxpos_chi2[i_subleading_mu], event_weight);
        (*hists)[prefix+"_vtxfitPV"]->Fill(_lVtxpos_PVdxy[i_subleading_displ_mu], event_weight);
        (*hists)[prefix+"_vtxfit_ntracks"]->Fill(_lVtxpos_ntracks[i_subleading_displ_mu], event_weight);
        (*hists)[prefix+"_vtxfit_maxdxy_valid"]->Fill(_lVtxpos_maxdxy_valid[i_subleading_displ_mu], event_weight);
    }
    return;
}
