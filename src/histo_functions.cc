//////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include <iostream>

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::add_histograms(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_cutflow"]                         = new TH1F(prefix+"_cutflow", ";cutflow;Events", 8, 0, 8);
    (*hists)[prefix+"_cuts"]                            = new TH1F(prefix+"_cuts", ";cuts;Events", 9, 0, 9);

    (*hists)[prefix+"_pt"]                              = new TH1F(prefix+"_pt", ";#it{p}_{T} [GeV];Events", 60, 0, 100);
    (*hists)[prefix+"_leadpt"]                          = new TH1F(prefix+"_leadpt", ";#it{p}_{T} [GeV];Events", 60, 0, 100);
    (*hists)[prefix+"_leadjetpt"]                       = new TH1F(prefix+"_leadjetpt", ";#it{p}_{T} [GeV];Events", 60, 0, 140);
    (*hists)[prefix+"_met"]                             = new TH1F(prefix+"_met", ";MET [GeV];Events", 60, 0, 200);
    (*hists)[prefix+"_dxy"]                             = new TH1F(prefix+"_dxy", ";#Delta_{xy} [cm];Events", 60, 0, 1.5);
    (*hists)[prefix+"_dz"]                              = new TH1F(prefix+"_dz", ";#Delta_{z} [cm];Events", 60, 0, 15);
    (*hists)[prefix+"_mll"]                             = new TH1F(prefix+"_mll", ";#it{m}_{ll} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_dphill"]                          = new TH1F(prefix+"_dphill", ";#it{#Delta #phi}_{ll};Events", 60, 0, 3.14);
    (*hists)[prefix+"_dRll"]                            = new TH1F(prefix+"_dRll", ";#it{#Delta R}_{ll};Events", 80, 0, 6);
    (*hists)[prefix+"_dRl2jet"]                         = new TH1F(prefix+"_dRl2jet", ";#it{#Delta R}_{l^{2}jet};Events", 80, 0, 6);
    (*hists)[prefix+"_l1reliso"]                        = new TH1F(prefix+"_l1reliso", ";L1 Rel Iso;Events", 60, 0, 0.3);
    (*hists)[prefix+"_l2reliso"]                        = new TH1F(prefix+"_l2reliso", ";L2 Rel Iso;Events", 40, 0, 3.5);

    (*hists)[prefix+"_ngentr"]                          = new TH1F(prefix+"_ngentr", ";N_{tracks}^{gen} from HNL;Events", 15, 0, 15);
    (*hists)[prefix+"_ctauHN"]                          = new TH1F(prefix+"_ctauHN", ";c#tau_{HNL} [mm];Events", 40, 0, 150);

    (*hists)[prefix+"_vtx_gendist"]                     = new TH1F(prefix+"_vtx_gendist", ";|Vtx_{fit} - Vtx_{gen}| [cm];Events", 30, 0, 10);
    (*hists)[prefix+"_vtx_gendist_zoom"]                = new TH1F(prefix+"_vtx_gendist_zoom", ";|Vtx_{fit} - Vtx_{gen}| [cm];Events", 15, 0, 1);
    (*hists)[prefix+"_vtx_gendist_aftercut_zoom"]       = new TH1F(prefix+"_vtx_gendist_aftercut_zoom", ";|Vtx_{fit} - Vtx_{gen}| [cm];Events", 10, 0, 0.3);
    (*hists)[prefix+"_vtx_chi2"]                        = new TH1F(prefix+"_vtx_chi2", ";#Chi^{2};Events", 100, 0, 200);
    (*hists)[prefix+"_vtx_normchi2"]                    = new TH1F(prefix+"_vtx_normchi2", ";Normalized #Chi^{2};Events", 100, 0, 200);
    (*hists)[prefix+"_vtx_normchi2_zoom"]               = new TH1F(prefix+"_vtx_normchi2_zoom", ";Normalized #Chi^{2};Events", 20, 0, 30);
    (*hists)[prefix+"_vtx_PVdist"]                      = new TH1F(prefix+"_vtx_PVdist", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 40, 0, 10);
    (*hists)[prefix+"_vtx_ntracks"]                     = new TH1F(prefix+"_vtx_ntracks", ";# of tracks used in Vtxfit;Events", 15, 0, 15);
    (*hists)[prefix+"_vtx_valid"]                       = new TH1F(prefix+"_vtx_valid", ";is Vertex Valid?;Events", 2, 0, 2);
    (*hists)[prefix+"_vtx_maxdxy"]                      = new TH1F(prefix+"_vtx_maxdxy", ";Max(dxy^{l2} - dxy^{trk}) (Valid Vtx);Events", 30, 0, 1.1);
    (*hists)[prefix+"_vtx_maxdz"]                       = new TH1F(prefix+"_vtx_maxdz", ";Max(dz^{l2} - dz^{trk}) (Valid Vtx);Events", 30, 0, 15);
    (*hists)[prefix+"_vtx_mindxy"]                      = new TH1F(prefix+"_vtx_mindxy", ";Min(dxy^{l2} - dxy^{trk}) (Valid Vtx);Events", 30, 0, 1.1);
    (*hists)[prefix+"_vtx_mindz"]                       = new TH1F(prefix+"_vtx_mindz", ";Min(dz^{l2} - dz^{trk}) (Valid Vtx);Events", 30, 0, 15);
    (*hists)[prefix+"_vtx_dRcut"]                       = new TH1F(prefix+"_vtx_dRcut", ";dR cone size (Valid Vtx);Events", 11, 0, 1.1);
    (*hists)[prefix+"_vtx_mass"]                        = new TH1F(prefix+"_vtx_mass", ";vertex mass [GeV];Events", 40, 0, 10);
    
    (*hists)[prefix+"_vtx_PV-SVdxy_eff"]                = new TH1F(prefix+"_vtx_PV-SVdxy_eff", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 10, 0, 60);
    (*hists)[prefix+"_vtx_PV-SVdxy_eff_num"]            = new TH1F(prefix+"_vtx_PV-SVdxy_eff_num", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 10, 0, 60);
    (*hists)[prefix+"_vtx_PV-SVdxy_eff_den"]            = new TH1F(prefix+"_vtx_PV-SVdxy_eff_den", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 10, 0, 60);
    (*hists)[prefix+"_vtx_PV-SVdxy_zoom_eff"]           = new TH1F(prefix+"_vtx_PV-SVdxy_zoom_eff", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 10, 0, 50);
    (*hists)[prefix+"_vtx_PV-SVdxy_zoom_eff_num"]       = new TH1F(prefix+"_vtx_PV-SVdxy_zoom_eff_num", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 10, 0, 50);
    (*hists)[prefix+"_vtx_PV-SVdxy_zoom_eff_den"]       = new TH1F(prefix+"_vtx_PV-SVdxy_zoom_eff_den", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 10, 0, 50);
    (*hists)[prefix+"_vtx_PV-SVdxy_zoom2_eff"]          = new TH1F(prefix+"_vtx_PV-SVdxy_zoom2_eff", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 10, 0, 18);
    (*hists)[prefix+"_vtx_PV-SVdxy_zoom2_eff_num"]      = new TH1F(prefix+"_vtx_PV-SVdxy_zoom2_eff_num", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 10, 0, 18);
    (*hists)[prefix+"_vtx_PV-SVdxy_zoom2_eff_den"]      = new TH1F(prefix+"_vtx_PV-SVdxy_zoom2_eff_den", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 10, 0, 18);
    (*hists)[prefix+"_vtx_PV-SVdxy_zoom3_eff"]          = new TH1F(prefix+"_vtx_PV-SVdxy_zoom3_eff", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 10, 0, 15);
    (*hists)[prefix+"_vtx_PV-SVdxy_zoom3_eff_num"]      = new TH1F(prefix+"_vtx_PV-SVdxy_zoom3_eff_num", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 10, 0, 15);
    (*hists)[prefix+"_vtx_PV-SVdxy_zoom3_eff_den"]      = new TH1F(prefix+"_vtx_PV-SVdxy_zoom3_eff_den", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 10, 0, 15);
    (*hists)[prefix+"_vtx_PV-SVdxyz_eff"]               = new TH1F(prefix+"_vtx_PV-SVdxyz_eff", ";#Delta_{xyz}(Vtx_{fit}, PV) [cm];Events", 10, 0, 100);
    (*hists)[prefix+"_vtx_PV-SVdxyz_eff_num"]           = new TH1F(prefix+"_vtx_PV-SVdxyz_eff_num", ";#Delta_{xyz}(Vtx_{fit}, PV) [cm];Events", 10, 0, 100);
    (*hists)[prefix+"_vtx_PV-SVdxyz_eff_den"]           = new TH1F(prefix+"_vtx_PV-SVdxyz_eff_den", ";#Delta_{xyz}(Vtx_{fit}, PV) [cm];Events", 10, 0, 100);
    (*hists)[prefix+"_vtx_PV-SVdxyz_zoom_eff"]          = new TH1F(prefix+"_vtx_PV-SVdxyz_zoom_eff", ";#Delta_{xyz}(Vtx_{fit}, PV) [cm];Events", 10, 0, 50);
    (*hists)[prefix+"_vtx_PV-SVdxyz_zoom_eff_num"]      = new TH1F(prefix+"_vtx_PV-SVdxyz_zoom_eff_num", ";#Delta_{xyz}(Vtx_{fit}, PV) [cm];Events", 10, 0, 50);
    (*hists)[prefix+"_vtx_PV-SVdxyz_zoom_eff_den"]      = new TH1F(prefix+"_vtx_PV-SVdxyz_zoom_eff_den", ";#Delta_{xyz}(Vtx_{fit}, PV) [cm];Events", 10, 0, 50);
    (*hists)[prefix+"_vtx_ctau_eff"]                    = new TH1F(prefix+"_vtx_ctau_eff", ";c #tau [mm] ;Events", 5, 0, 60);
    (*hists)[prefix+"_vtx_ctau_eff_num"]                = new TH1F(prefix+"_vtx_ctau_eff_num", ";c #tau [mm];Events", 5, 0, 60);
    (*hists)[prefix+"_vtx_ctau_eff_den"]                = new TH1F(prefix+"_vtx_ctau_eff_den", ";c #tau [mm];Events", 5, 0, 60);
    (*hists)[prefix+"_vtx_ctau_zoom_eff"]               = new TH1F(prefix+"_vtx_ctau_zoom_eff", ";c #tau [mm];Events", 5, 0, 30);
    (*hists)[prefix+"_vtx_ctau_zoom_eff_num"]           = new TH1F(prefix+"_vtx_ctau_zoom_eff_num", ";c #tau [mm];Events", 5, 0, 30);
    (*hists)[prefix+"_vtx_ctau_zoom_eff_den"]           = new TH1F(prefix+"_vtx_ctau_zoom_eff_den", ";c #tau [mm];Events", 5, 0, 30);
    (*hists)[prefix+"_vtx_ctau_zoom2_eff"]              = new TH1F(prefix+"_vtx_ctau_zoom2_eff", ";c #tau [mm];Events", 5, 0, 6);
    (*hists)[prefix+"_vtx_ctau_zoom2_eff_num"]          = new TH1F(prefix+"_vtx_ctau_zoom2_eff_num", ";c #tau [mm];Events", 5, 0, 6);
    (*hists)[prefix+"_vtx_ctau_zoom2_eff_den"]          = new TH1F(prefix+"_vtx_ctau_zoom2_eff_den", ";c #tau [mm];Events", 5, 0, 6);

    (*hists)[prefix+"_invVtx_ntracks"]                  = new TH1F(prefix+"_invVtx_ntracks", ";# of tracks for an invalid vertex;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_ngentr"]               = new TH1F(prefix+"_invVtx_1tr_ngentr", ";Gen-level # of tracks for invalid vtx with no found tracks;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_ngenl"]                = new TH1F(prefix+"_invVtx_1tr_ngenl", ";Gen-level # of Leptons for invalid vtx with no found tracks;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_ngene"]                = new TH1F(prefix+"_invVtx_1tr_ngene", ";Gen-level # of Electrons for invalid vtx with no found tracks;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_ngenmu"]               = new TH1F(prefix+"_invVtx_1tr_ngenmu", ";Gen-level # of Muons for invalid vtx with no found tracks;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_pt"]                   = new TH1F(prefix+"_invVtx_1tr_pt", ";#it{p}_{T} [GeV];Events", 40, 0, 40);
    (*hists)[prefix+"_invVtx_1tr_deta"]                 = new TH1F(prefix+"_invVtx_1tr_deta", ";#Delta #eta;Events", 40, 0, 4);
    (*hists)[prefix+"_invVtx_1tr_dphi"]                 = new TH1F(prefix+"_invVtx_1tr_dphi", ";#Delta #phi;Events", 40, 0, 3.14);
    (*hists)[prefix+"_invVtx_1tr_dR"]                   = new TH1F(prefix+"_invVtx_1tr_dR", ";#Delta R;Events", 40, 0, 5);
    (*hists)[prefix+"_invVtx_1tr_dxy"]                  = new TH1F(prefix+"_invVtx_1tr_dxy", ";#Delta_{xy}[cm];Events", 30, 0, 4);
    (*hists)[prefix+"_invVtx_1tr_dz"]                   = new TH1F(prefix+"_invVtx_1tr_dz", ";#Delta_{z}[cm];Events", 30, 0, 10);

    (*hists)[prefix+"_corrl2_pt_eff"]                   = new TH1F(prefix+"_corrl2_pt_eff", ";#it{p}_{T} [GeV];Eff.", 40, 0, 40);
    (*hists)[prefix+"_corrl2_pt_eff_num"]               = new TH1F(prefix+"_corrl2_pt_eff_num", ";#it{p}_{T} [GeV];Events", 40, 0, 40);
    (*hists)[prefix+"_corrl2_pt_eff_den"]               = new TH1F(prefix+"_corrl2_pt_eff_den", ";#it{p}_{T} [GeV];Events", 40, 0, 40);
    (*hists)[prefix+"_corrl2_ctau_eff"]                 = new TH1F(prefix+"_corrl2_ctau_eff", ";c#tau [mm];Eff.", 40, 0, 40);
    (*hists)[prefix+"_corrl2_ctau_eff_num"]             = new TH1F(prefix+"_corrl2_ctau_eff_num", ";c#tau [mm];Events", 40, 0, 40);
    (*hists)[prefix+"_corrl2_ctau_eff_den"]             = new TH1F(prefix+"_corrl2_ctau_eff_den", ";c#tau [mm];Events", 40, 0, 40);
    (*hists)[prefix+"_corrl2_gendist_eff"]              = new TH1F(prefix+"_corrl2_gendist_eff", ";|Vtx_{fit} - Vtx_{gen}| [cm];Eff.", 60, 0, 10);
    (*hists)[prefix+"_corrl2_gendist_eff_num"]          = new TH1F(prefix+"_corrl2_gendist_eff_num", ";|Vtx_{fit} - Vtx_{gen}| [cm];Events", 60, 0, 10);
    (*hists)[prefix+"_corrl2_gendist_eff_den"]          = new TH1F(prefix+"_corrl2_gendist_eff_den", ";|Vtx_{fit} - Vtx_{gen}| [cm];Events", 60, 0, 10);
   

    (*hists)[prefix+"_l2_and_vtx_ctau_zoom2_eff"]       = new TH1F(prefix+"_l2_and_vtx_ctau_zoom2_eff", ";c #tau [mm];Events", 5, 0, 6);
    (*hists)[prefix+"_l2_and_vtx_ctau_zoom2_eff_num"]   = new TH1F(prefix+"_l2_and_vtx_ctau_zoom2_eff_num", ";c #tau [mm];Events", 5, 0, 6);
    (*hists)[prefix+"_l2_and_vtx_ctau_zoom2_eff_den"]   = new TH1F(prefix+"_l2_and_vtx_ctau_zoom2_eff_den", ";c #tau [mm];Events", 5, 0, 6);
    (*hists)[prefix+"_l2_and_vtx_ctau_zoom_eff"]        = new TH1F(prefix+"_l2_and_vtx_ctau_zoom_eff", ";c #tau [mm];Events", 5, 0, 30);
    (*hists)[prefix+"_l2_and_vtx_ctau_zoom_eff_num"]    = new TH1F(prefix+"_l2_and_vtx_ctau_zoom_eff_num", ";c #tau [mm];Events", 5, 0, 30);
    (*hists)[prefix+"_l2_and_vtx_ctau_zoom_eff_den"]    = new TH1F(prefix+"_l2_and_vtx_ctau_zoom_eff_den", ";c #tau [mm];Events", 5, 0, 30);
    (*hists)[prefix+"_l2_and_vtx_ctau_eff"]             = new TH1F(prefix+"_l2_and_vtx_ctau_eff", ";c #tau [mm];Events", 5, 0, 60);
    (*hists)[prefix+"_l2_and_vtx_ctau_eff_num"]         = new TH1F(prefix+"_l2_and_vtx_ctau_eff_num", ";c #tau [mm];Events", 5, 0, 60);
    (*hists)[prefix+"_l2_and_vtx_ctau_eff_den"]         = new TH1F(prefix+"_l2_and_vtx_ctau_eff_den", ";c #tau [mm];Events", 5, 0, 60);

    
/*    (*hists)[prefix+"_n_prompte_ID"]   = new TH1F(prefix+"_n_prompte_ID", ";Number of electron with prompt ID;Events", 10, 0, 10);
    (*hists)[prefix+"_n_disple_ID"]   = new TH1F(prefix+"_n_disple_ID", ";Number of electron with displ ID;Events", 10, 0, 10);
    (*hists)[prefix+"_n_cleanede"]   = new TH1F(prefix+"_n_cleanede", ";Number of electron cleaned;Events", 10, 0, 10);
    (*hists)[prefix+"_n_cleaned_prompte_ID"]   = new TH1F(prefix+"_n_cleaned_prompte_ID", ";Number of electron with cleaned prompt ID;Events", 10, 0, 10);
    (*hists)[prefix+"_n_cleaned_disple_ID"]   = new TH1F(prefix+"_n_cleaned_disple_ID", ";Number of electron with cleaned displ ID;Events", 10, 0, 10);
    (*hists)[prefix+"_n_promptmu_ID"]   = new TH1F(prefix+"_n_promptmu_ID", ";Number of muon with prompt ID;Events", 10, 0, 10);
    (*hists)[prefix+"_n_displmu_ID"]   = new TH1F(prefix+"_n_displmu_ID", ";Number of muon with displ ID;Events", 10, 0, 10);
    (*hists)[prefix+"_n_ptcut"]   = new TH1F(prefix+"_n_ptcut", ";Number of muon with prompt ID passing ptcut;Events", 10, 0, 10);
    (*hists)[prefix+"_n_ptcut_trig"]   = new TH1F(prefix+"_n_ptcut_trig", ";Number of muon with prompt ID passing ptcut and trigger;Events", 10, 0, 10);
    (*hists)[prefix+"_n_leadingmu_trig"]   = new TH1F(prefix+"_n_leadingmu_trig", ";Number of muon with prompt ID passing ptcut and trigger;Events", 10, 0, 10);
    (*hists)[prefix+"_n_trige"]   = new TH1F(prefix+"_n_trige", ";Number of events passing e trigger;Events", 10, 0, 10);
    (*hists)[prefix+"_n_trigmu"]   = new TH1F(prefix+"_n_trigmu", ";Number of events passing mu trigger;Events", 10, 0, 10);*/
    return;
}

void full_analyzer::fill_histograms(std::map<TString, TH1*>* hists, TString prefix, int i_leading, int i_subleading, int i_gen_subleading){
    (*hists)[prefix+"_leadpt"]->Fill(_lPt[i_leading], event_weight);
    (*hists)[prefix+"_pt"]->Fill(_lPt[i_subleading], event_weight);
    (*hists)[prefix+"_dxy"]->Fill(fabs(_dxy[i_subleading]), event_weight);
    (*hists)[prefix+"_dz"]->Fill(fabs(_dz[i_subleading]), event_weight);
    (*hists)[prefix+"_l1reliso"]->Fill(_relIso[i_leading], event_weight);
    (*hists)[prefix+"_l2reliso"]->Fill(_relIso[i_subleading], event_weight);

    TLorentzVector lepton1;
    TLorentzVector lepton2;
    lepton1.SetPtEtaPhiE(_lPt[i_leading], _lEta[i_leading], _lPhi[i_leading], _lE[i_leading]);
    lepton2.SetPtEtaPhiE(_lPt[i_subleading], _lEta[i_subleading], _lPhi[i_subleading], _lE[i_subleading]);
    
    (*hists)[prefix+"_mll"]->Fill((lepton1 + lepton2).M(), event_weight);
    (*hists)[prefix+"_dphill"]->Fill(fabs(lepton1.DeltaPhi(lepton2)), event_weight);
    (*hists)[prefix+"_dRll"]->Fill(lepton1.DeltaR(lepton2), event_weight);
    (*hists)[prefix+"_dRl2jet"]->Fill(find_dRl2jet(lepton2),event_weight);
    (*hists)[prefix+"_vtx_valid"]->Fill(_lKVF_valid[i_subleading], event_weight);

    (*hists)[prefix+"_ngentr"]->Fill(_gen_nNPackedDtrs, event_weight);
    (*hists)[prefix+"_ctauHN"]->Fill(_ctauHN, event_weight);
    
    // valid vertex
    if(_lKVF_valid[i_subleading]){
        if(sampleflavor != "bkg") (*hists)[prefix+"_vtx_gendist"]->Fill(sqrt((_gen_vertex_x[i_gen_l2] - _lKVF_x[i_subleading])*(_gen_vertex_x[i_gen_l2] - _lKVF_x[i_subleading]) + (_gen_vertex_y[i_gen_l2] - _lKVF_y[i_subleading])*(_gen_vertex_y[i_gen_l2] - _lKVF_y[i_subleading]) + (_gen_vertex_z[i_gen_l2] - _lKVF_z[i_subleading])*(_gen_vertex_z[i_gen_l2] - _lKVF_z[i_subleading])), event_weight);
        else (*hists)[prefix+"_vtx_gendist"]->Fill(sqrt((_gen_vertex_x[i_gen_subleading] - _lKVF_x[i_subleading])*(_gen_vertex_x[i_gen_subleading] - _lKVF_x[i_subleading]) + (_gen_vertex_y[i_gen_subleading] - _lKVF_y[i_subleading])*(_gen_vertex_y[i_gen_subleading] - _lKVF_y[i_subleading]) + (_gen_vertex_z[i_gen_subleading] - _lKVF_z[i_subleading])*(_gen_vertex_z[i_gen_subleading] - _lKVF_z[i_subleading])), event_weight);
        if(sampleflavor != "bkg") (*hists)[prefix+"_vtx_gendist_zoom"]->Fill(sqrt((_gen_vertex_x[i_gen_l2] - _lKVF_x[i_subleading])*(_gen_vertex_x[i_gen_l2] - _lKVF_x[i_subleading]) + (_gen_vertex_y[i_gen_l2] - _lKVF_y[i_subleading])*(_gen_vertex_y[i_gen_l2] - _lKVF_y[i_subleading]) + (_gen_vertex_z[i_gen_l2] - _lKVF_z[i_subleading])*(_gen_vertex_z[i_gen_l2] - _lKVF_z[i_subleading])), event_weight);
        else (*hists)[prefix+"_vtx_gendist_zoom"]->Fill(sqrt((_gen_vertex_x[i_gen_subleading] - _lKVF_x[i_subleading])*(_gen_vertex_x[i_gen_subleading] - _lKVF_x[i_subleading]) + (_gen_vertex_y[i_gen_subleading] - _lKVF_y[i_subleading])*(_gen_vertex_y[i_gen_subleading] - _lKVF_y[i_subleading]) + (_gen_vertex_z[i_gen_subleading] - _lKVF_z[i_subleading])*(_gen_vertex_z[i_gen_subleading] - _lKVF_z[i_subleading])), event_weight);
        (*hists)[prefix+"_vtx_chi2"]->Fill(_lKVF_chi2[i_subleading], event_weight);
        (*hists)[prefix+"_vtx_normchi2"]->Fill(_lKVF_chi2[i_subleading] / _lKVF_df[i_subleading], event_weight);
        (*hists)[prefix+"_vtx_normchi2_zoom"]->Fill(_lKVF_chi2[i_subleading] / _lKVF_df[i_subleading], event_weight);
        //(*hists)[prefix+"_vtx_PVdist"]->Fill(_lKVF_PVdxy[i_subleading], event_weight);
        (*hists)[prefix+"_vtx_ntracks"]->Fill(_lKVF_ntracks[i_subleading], event_weight);
        
        double maxdxy = 0;
        double maxdz  = 0;
        double mindxy = 5;
        double mindz  = 5;
        for(int i = 0; i < _lKVF_ntracks[i_subleading]; i++){
            //if(_lKVF_trackddxy[i_subleading][i] > maxdxy) maxdxy = _lKVF_trackddxy[i_subleading][i];
            //if(_lKVF_trackddz[i_subleading][i]  > maxdz)  maxdz  = _lKVF_trackddz[i_subleading][i];
            //if(_lKVF_trackddxy[i_subleading][i] < mindxy) mindxy = _lKVF_trackddxy[i_subleading][i];
            //if(_lKVF_trackddz[i_subleading][i]  < mindz)  mindz  = _lKVF_trackddz[i_subleading][i];
        }
        //(*hists)[prefix+"_vtx_maxdxy"]->Fill(maxdxy, event_weight);
        //(*hists)[prefix+"_vtx_maxdz"]->Fill(maxdz, event_weight);
        //(*hists)[prefix+"_vtx_mindxy"]->Fill(mindxy, event_weight);
        //(*hists)[prefix+"_vtx_mindz"]->Fill(mindz, event_weight);
        (*hists)[prefix+"_vtx_dRcut"]->Fill(_lKVF_dRcut[i_subleading], event_weight);

        if(sampleflavor != "bkg"){ //this does not work yet
            int i_track = 0;
            TLorentzVector all;
            all.SetPtEtaPhiE(0,0,0,0);
            for(int i = 0; i_track < _lKVF_ntracks[i_subleading]; i++){
                if(_lKVF_trackdR[i_subleading][i] < _lKVF_dRcut[i_subleading]){
                    i_track++;
                    TLorentzVector temp;
                    temp.SetPtEtaPhiE(_lKVF_trackPt[i_subleading][i], _lKVF_trackEta[i_subleading][i], _lKVF_trackPhi[i_subleading][i], _lKVF_trackE[i_subleading][i]);
                    all += temp;
                }
            }
            (*hists)[prefix+"_vtx_mass"]->Fill(all.M(), event_weight);
        }
    

    }else{ //invalid vertex
        (*hists)[prefix+"_invVtx_ntracks"]->Fill(_lKVF_ntracks[i_subleading], event_weight);
        if(_lKVF_ntracks[i_subleading] == 1) fill_1tr(hists, prefix, i_subleading);
    }
}

void full_analyzer::fill_cutflow_e(std::map<TString, TH1*>* hists, TString prefix){
    int SSorOS = (prefix.Index("OS") == -1)? 2 : 0;//sum of charges is 2 if SS, 0 if OS

    (*hists)[prefix+"_cutflow"]->Fill(0.,event_weight); //cutflow contains the legitimate actual cutflow of the analysis
    if(_trige) (*hists)[prefix+"_cutflow"]->Fill(1.,event_weight);
    if(_1e) (*hists)[prefix+"_cutflow"]->Fill(2.,event_weight); 
    if(_1e1disple && fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS) {
        (*hists)[prefix+"_cutflow"]->Fill(3.,event_weight); 
        if(_1e1disple0adde) (*hists)[prefix+"_cutflow"]->Fill(4.,event_weight); 
        if(_1e1disple0jet) (*hists)[prefix+"_cutflow"]->Fill(5.,event_weight); 
        if(_1e1disple0jet_aftermll) (*hists)[prefix+"_cutflow"]->Fill(6.,event_weight); 
        if(_1e1disple0jet_afterdphi) (*hists)[prefix+"_cutflow"]->Fill(7.,event_weight); 
    }

    (*hists)[prefix+"_cuts"]->Fill(0.,event_weight); //cuts contains all possible cuts and is more meant to analyze different cuts
    if(_trige) (*hists)[prefix+"_cuts"]->Fill(1.,event_weight);
    if(_1e) (*hists)[prefix+"_cuts"]->Fill(2.,event_weight); 
    if(_1e1displolde && fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS) {
        (*hists)[prefix+"_cuts"]->Fill(3.,event_weight); 
        if(_1e1disple0adde) (*hists)[prefix+"_cuts"]->Fill(5.,event_weight); 
        if(_1e1disple0jet) (*hists)[prefix+"_cuts"]->Fill(6.,event_weight); 
        if(_1e1disple0jet_aftermll) (*hists)[prefix+"_cuts"]->Fill(7.,event_weight); 
        if(_1e1disple0jet_afterdphi) (*hists)[prefix+"_cuts"]->Fill(8.,event_weight); 
    }
    
    if(_1e1disple && fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS) {
        (*hists)[prefix+"_cuts"]->Fill(4., event_weight);
    }
}


void full_analyzer::fill_cutflow_mu(std::map<TString, TH1*>* hists, TString prefix){
    int SSorOS = (prefix.Index("OS") == -1)? 2 : 0;//sum of charges is 2 if SS, 0 if OS

    (*hists)[prefix+"_cutflow"]->Fill(0.,event_weight); //cutflow contains the legitimate actual cutflow of the analysis
    if(_trigmu) (*hists)[prefix+"_cutflow"]->Fill(1.,event_weight); 
    if(_1mu) (*hists)[prefix+"_cutflow"]->Fill(2.,event_weight); 
    if(_1mu1displmu && fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS) {
        (*hists)[prefix+"_cutflow"]->Fill(3.,event_weight); 
        if(_1mu1displmu0addmu) (*hists)[prefix+"_cutflow"]->Fill(4.,event_weight); 
        if(_1mu1displmu0jet) (*hists)[prefix+"_cutflow"]->Fill(5.,event_weight); 
        if(_1mu1displmu0jet_aftermll) (*hists)[prefix+"_cutflow"]->Fill(6.,event_weight); 
        if(_1mu1displmu0jet_afterdphi) (*hists)[prefix+"_cutflow"]->Fill(7.,event_weight); 
    }

    (*hists)[prefix+"_cuts"]->Fill(0.,event_weight); //cuts contains all possible cuts and is more meant to analyze different cuts
    if(_trigmu) (*hists)[prefix+"_cuts"]->Fill(1.,event_weight); 
    if(_1mu) (*hists)[prefix+"_cuts"]->Fill(2.,event_weight); 
    if(_1mu1disploldmu && fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS) {
        (*hists)[prefix+"_cuts"]->Fill(3.,event_weight); 
        if(_1mu1displmu0addmu) (*hists)[prefix+"_cuts"]->Fill(5.,event_weight); 
        if(_1mu1displmu0jet) (*hists)[prefix+"_cuts"]->Fill(6.,event_weight); 
        if(_1mu1displmu0jet_aftermll) (*hists)[prefix+"_cuts"]->Fill(7.,event_weight); 
        if(_1mu1displmu0jet_afterdphi) (*hists)[prefix+"_cuts"]->Fill(8.,event_weight); 
    }
    
    if(_1mu1displmu && fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS) {
        (*hists)[prefix+"_cuts"]->Fill(4.,event_weight); 
    }
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

    // using gen lepton from HNL, find lepton from HNL in Packed daughters
    double mineta = 5;
    int i_lepHNL = 0;
    for(int i = 0; i < _gen_nNPackedDtrs; i++){
        if((fabs(_gen_NPackedDtrsPdgId[i]) == 11 || fabs(_gen_NPackedDtrsPdgId[i] == 13)) && fabs(_gen_NPackedDtrsEta[i] - _gen_lEta[i_gen_l2]) < mineta){
            mineta = fabs(_gen_NPackedDtrsEta[i] - _gen_lEta[i_gen_l2]);
            i_lepHNL = i;//lepton from HNL in packed daughters found
        }
    }
    // if reco lepton is not the correct one, there is no meaning to the following histograms 
    bool correct_reco_lepton = (fabs(_lEta[i_lep] - _gen_NPackedDtrsEta[i_lepHNL]) < 1 && fabs(_lPhi[i_lep] - _gen_NPackedDtrsPhi[i_lepHNL]) < 1 && fabs(_lPt[i_lep] - _gen_NPackedDtrsPt[i_lepHNL]) < 5);
    
    if(correct_reco_lepton){
        double mindR  = 5;
        double mindxy = 5;
        for(int i = 0; i < _gen_nNPackedDtrs; i++){
            if(i == i_lepHNL) continue;
            (*hists)[prefix+"_invVtx_1tr_deta"]->Fill(fabs(_gen_NPackedDtrsEta[i] - _gen_NPackedDtrsEta[i_lepHNL]));
            (*hists)[prefix+"_invVtx_1tr_pt"]->Fill(_gen_NPackedDtrsPt[i]);
            TLorentzVector lep;
            TLorentzVector track;
            lep.SetPtEtaPhiE(_gen_NPackedDtrsPt[i_lepHNL], _gen_NPackedDtrsEta[i_lepHNL], _gen_NPackedDtrsPhi[i_lepHNL], _gen_NPackedDtrsE[i_lepHNL]);
            track.SetPtEtaPhiE(_gen_NPackedDtrsPt[i], _gen_NPackedDtrsEta[i], _gen_NPackedDtrsPhi[i], _gen_NPackedDtrsE[i]);
            if(fabs(lep.DeltaR(track)) < mindR) mindR = fabs(lep.DeltaR(track));
            (*hists)[prefix+"_invVtx_1tr_dphi"]->Fill(fabs(lep.DeltaPhi(track)));
            if(matches[i] >= 1 && fabs(_gen_NPackedDtrs_matchdxy[i] - _gen_NPackedDtrs_matchdxy[i_lepHNL]) < mindxy) mindxy = fabs(_gen_NPackedDtrs_matchdxy[i] - _gen_NPackedDtrs_matchdxy[i_lepHNL]);
            if(matches[i] >= 1) (*hists)[prefix+"_invVtx_1tr_dz"]->Fill(fabs(_gen_NPackedDtrs_matchdz[i] - _gen_NPackedDtrs_matchdz[i_lepHNL]));
        }
        if(mindR  != 5) (*hists)[prefix+"_invVtx_1tr_dR"]->Fill(mindR);
        if(mindxy != 5) (*hists)[prefix+"_invVtx_1tr_dxy"]->Fill(mindxy);
    }
}

void full_analyzer::fill_jetmet_variables(std::map<TString, TH1*>* hists, TString prefix)
{
    (*hists)[prefix+"_leadjetpt"]->Fill(_lPt[i_leading_jet_for_displ], event_weight);
    (*hists)[prefix+"_met"]->Fill(_met, event_weight);
}

void full_analyzer::fill_corrl2_eff(std::map<TString, TH1*>* hists, TString prefix)
{
    int i_lep = -1;
    if(prefix.Index("_e") != -1) i_lep = i_subleading_displ_e;
    if(prefix.Index("_mu") != -1) i_lep = i_subleading_displ_mu;

    (*hists)[prefix+"_corrl2_pt_eff_den"]->Fill(_lPt[i_lep], event_weight);
    (*hists)[prefix+"_corrl2_ctau_eff_den"]->Fill(_ctauHN, event_weight);
    (*hists)[prefix+"_corrl2_gendist_eff_den"]->Fill(sqrt((_gen_vertex_x[i_lep] - _lKVF_x[i_lep])*(_gen_vertex_x[i_lep] - _lKVF_x[i_lep]) + (_gen_vertex_y[i_lep] - _lKVF_y[i_lep])*(_gen_vertex_y[i_lep] - _lKVF_y[i_lep]) + (_gen_vertex_z[i_lep] - _lKVF_z[i_lep])*(_gen_vertex_z[i_lep] - _lKVF_z[i_lep])), event_weight);
    if(subleading_is_l2){
        (*hists)[prefix+"_corrl2_pt_eff_num"]->Fill(_lPt[i_lep], event_weight);
        (*hists)[prefix+"_corrl2_ctau_eff_num"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_corrl2_pt_eff"]->Fill(_lPt[i_lep], event_weight);
        (*hists)[prefix+"_corrl2_ctau_eff"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_corrl2_gendist_eff_num"]->Fill(sqrt((_gen_vertex_x[i_lep] - _lKVF_x[i_lep])*(_gen_vertex_x[i_lep] - _lKVF_x[i_lep]) + (_gen_vertex_y[i_lep] - _lKVF_y[i_lep])*(_gen_vertex_y[i_lep] - _lKVF_y[i_lep]) + (_gen_vertex_z[i_lep] - _lKVF_z[i_lep])*(_gen_vertex_z[i_lep] - _lKVF_z[i_lep])), event_weight);
        (*hists)[prefix+"_corrl2_gendist_eff"]->Fill(sqrt((_gen_vertex_x[i_lep] - _lKVF_x[i_lep])*(_gen_vertex_x[i_lep] - _lKVF_x[i_lep]) + (_gen_vertex_y[i_lep] - _lKVF_y[i_lep])*(_gen_vertex_y[i_lep] - _lKVF_y[i_lep]) + (_gen_vertex_z[i_lep] - _lKVF_z[i_lep])*(_gen_vertex_z[i_lep] - _lKVF_z[i_lep])), event_weight);
    }
}


void full_analyzer::fill_l2_and_vtx_eff(std::map<TString, TH1*>* hists, TString prefix, int i_leading, int i_subleading, int i_gen_subleading){
    bool _1prompt1displ = false;
    if(prefix.Index("_e") != -1) _1prompt1displ = _1e1disple;
    if(prefix.Index("_mu") != -1) _1prompt1displ = _1mu1displmu;

    (*hists)[prefix+"_l2_and_vtx_ctau_eff_den"]->Fill(_ctauHN, event_weight);
    (*hists)[prefix+"_l2_and_vtx_ctau_zoom_eff_den"]->Fill(_ctauHN, event_weight);
    (*hists)[prefix+"_l2_and_vtx_ctau_zoom2_eff_den"]->Fill(_ctauHN, event_weight);
    
    double vtx_gendist = sqrt((_gen_vertex_x[i_gen_l2] - _lKVF_x[i_subleading])*(_gen_vertex_x[i_gen_l2] - _lKVF_x[i_subleading]) + (_gen_vertex_y[i_gen_l2] - _lKVF_y[i_subleading])*(_gen_vertex_y[i_gen_l2] - _lKVF_y[i_subleading]) + (_gen_vertex_z[i_gen_l2] - _lKVF_z[i_subleading])*(_gen_vertex_z[i_gen_l2] - _lKVF_z[i_subleading]));
    double vtx_PVdist = sqrt((_gen_Nvertex_x - _lKVF_x[i_subleading])*(_gen_Nvertex_x - _lKVF_x[i_subleading]) + (_gen_Nvertex_y - _lKVF_y[i_subleading])*(_gen_Nvertex_y - _lKVF_y[i_subleading]) + (_gen_Nvertex_z - _lKVF_z[i_subleading])*(_gen_Nvertex_z - _lKVF_z[i_subleading]));
    double vtx_PVdistxy = sqrt((_gen_Nvertex_x - _lKVF_x[i_subleading])*(_gen_Nvertex_x - _lKVF_x[i_subleading]) + (_gen_Nvertex_y - _lKVF_y[i_subleading])*(_gen_Nvertex_y - _lKVF_y[i_subleading]));
    
    if(_1prompt1displ){
        //(*hists)[prefix+"_vtx_PV-SVdxy_eff_den"]->Fill(_lKVF_PVdxy[i_subleading], event_weight);
        //(*hists)[prefix+"_vtx_PV-SVdxy_zoom_eff_den"]->Fill(_lKVF_PVdxy[i_subleading], event_weight);
        //(*hists)[prefix+"_vtx_PV-SVdxy_zoom2_eff_den"]->Fill(_lKVF_PVdxy[i_subleading], event_weight);
        //(*hists)[prefix+"_vtx_PV-SVdxy_zoom3_eff_den"]->Fill(_lKVF_PVdxy[i_subleading], event_weight);
        (*hists)[prefix+"_vtx_PV-SVdxyz_eff_den"]->Fill(vtx_PVdist, event_weight);
        (*hists)[prefix+"_vtx_PV-SVdxyz_zoom_eff_den"]->Fill(vtx_PVdist, event_weight);
        (*hists)[prefix+"_vtx_ctau_eff_den"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_vtx_ctau_zoom_eff_den"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_vtx_ctau_zoom2_eff_den"]->Fill(_ctauHN, event_weight);
    }
    if(_1prompt1displ && _lKVF_valid[i_subleading] && vtx_gendist < 0.2 && vtx_PVdist > 0.05){
        if(sampleflavor != "bkg") (*hists)[prefix+"_vtx_gendist_aftercut_zoom"]->Fill(sqrt((_gen_vertex_x[i_gen_l2] - _lKVF_x[i_subleading])*(_gen_vertex_x[i_gen_l2] - _lKVF_x[i_subleading]) + (_gen_vertex_y[i_gen_l2] - _lKVF_y[i_subleading])*(_gen_vertex_y[i_gen_l2] - _lKVF_y[i_subleading]) + (_gen_vertex_z[i_gen_l2] - _lKVF_z[i_subleading])*(_gen_vertex_z[i_gen_l2] - _lKVF_z[i_subleading])), event_weight);
        else (*hists)[prefix+"_vtx_gendist_aftercut_zoom"]->Fill(sqrt((_gen_vertex_x[i_gen_subleading] - _lKVF_x[i_subleading])*(_gen_vertex_x[i_gen_subleading] - _lKVF_x[i_subleading]) + (_gen_vertex_y[i_gen_subleading] - _lKVF_y[i_subleading])*(_gen_vertex_y[i_gen_subleading] - _lKVF_y[i_subleading]) + (_gen_vertex_z[i_gen_subleading] - _lKVF_z[i_subleading])*(_gen_vertex_z[i_gen_subleading] - _lKVF_z[i_subleading])), event_weight);
        //(*hists)[prefix+"_vtx_PV-SVdxy_eff_num"]->Fill(_lKVF_PVdxy[i_subleading], event_weight);
        //(*hists)[prefix+"_vtx_PV-SVdxy_eff"]->Fill(_lKVF_PVdxy[i_subleading], event_weight);
        //(*hists)[prefix+"_vtx_PV-SVdxy_zoom_eff_num"]->Fill(_lKVF_PVdxy[i_subleading], event_weight);
        //(*hists)[prefix+"_vtx_PV-SVdxy_zoom_eff"]->Fill(_lKVF_PVdxy[i_subleading], event_weight);
        //(*hists)[prefix+"_vtx_PV-SVdxy_zoom2_eff_num"]->Fill(_lKVF_PVdxy[i_subleading], event_weight);
        //(*hists)[prefix+"_vtx_PV-SVdxy_zoom2_eff"]->Fill(_lKVF_PVdxy[i_subleading], event_weight);
        //(*hists)[prefix+"_vtx_PV-SVdxy_zoom3_eff_num"]->Fill(_lKVF_PVdxy[i_subleading], event_weight);
        //(*hists)[prefix+"_vtx_PV-SVdxy_zoom3_eff"]->Fill(_lKVF_PVdxy[i_subleading], event_weight);
        (*hists)[prefix+"_vtx_PV-SVdxyz_eff_num"]->Fill(vtx_PVdist, event_weight);
        (*hists)[prefix+"_vtx_PV-SVdxyz_eff"]->Fill(vtx_PVdist, event_weight);
        (*hists)[prefix+"_vtx_PV-SVdxyz_zoom_eff_num"]->Fill(vtx_PVdist, event_weight);
        (*hists)[prefix+"_vtx_PV-SVdxyz_zoom_eff"]->Fill(vtx_PVdist, event_weight);
        (*hists)[prefix+"_l2_and_vtx_ctau_eff_num"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_l2_and_vtx_ctau_zoom_eff_num"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_l2_and_vtx_ctau_zoom2_eff_num"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_l2_and_vtx_ctau_eff"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_l2_and_vtx_ctau_zoom_eff"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_l2_and_vtx_ctau_zoom2_eff"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_vtx_ctau_eff_num"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_vtx_ctau_zoom_eff_num"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_vtx_ctau_zoom2_eff_num"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_vtx_ctau_eff"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_vtx_ctau_zoom_eff"]->Fill(_ctauHN, event_weight);
        (*hists)[prefix+"_vtx_ctau_zoom2_eff"]->Fill(_ctauHN, event_weight);
    } 
}

// This function tested the efficiencies for the prompt and displaced ID's, since something seemed to be wrong, turns out everything works fine!
/*void full_analyzer::fill_ID_histos(std::map<TString, TH1*>* hists, TString prefix)
{
    int nprompte = 0;
    int ndisple  = 0;
    int ncleanede = 0;
    int ncleanedandprompte = 0;
    int ncleanedanddisple  = 0;
    int npromptmu = 0;
    int ndisplmu  = 0;
    int nptcut = 0;
    int nptcutandtrig = 0;
    int ntrige = 0;
    int ntrigmu = 0;
    for(int i = 0; i < _nL; i++){
        if(fullElectronID[i]) nprompte++;
        if(newdisplElectronID[i]) ndisple++;
        if(ele_clean_full_noniso_displ[i]) ncleanede++;
        if(fullElectronID[i] && ele_clean_full_noniso_displ[i]) ncleanedandprompte++;
        if(newdisplElectronID[i] && ele_clean_full_noniso_displ[i]) ncleanedanddisple++;
        if(fullMuonID[i]) npromptmu++;
        if(newdisplMuonID[i]) ndisplmu++;
        if((fullElectronID[i] && _lPt[i] > 30) || (fullMuonID[i] && _lPt[i] > 25)) nptcut++;
        if((_trige && fullElectronID[i] && _lPt[i] > 30) || (_trigmu && fullMuonID[i] && _lPt[i] > 25)) nptcutandtrig++;
    }
    if(_trigmu) ntrigmu++;
    if(_trige)  ntrige++;
    (*hists)[prefix+"_n_prompte_ID"]->Fill(nprompte, event_weight);
    (*hists)[prefix+"_n_disple_ID"]->Fill(ndisple, event_weight);
    (*hists)[prefix+"_n_cleanede"]->Fill(ncleanede, event_weight);
    (*hists)[prefix+"_n_cleaned_prompte_ID"]->Fill(ncleanedandprompte, event_weight);
    (*hists)[prefix+"_n_cleaned_disple_ID"]->Fill(ncleanedanddisple, event_weight);
    (*hists)[prefix+"_n_promptmu_ID"]->Fill(npromptmu, event_weight);
    (*hists)[prefix+"_n_displmu_ID"]->Fill(ndisplmu, event_weight);
    (*hists)[prefix+"_n_ptcut"]->Fill(nptcut, event_weight);
    (*hists)[prefix+"_n_ptcut_trig"]->Fill(nptcutandtrig, event_weight);
    (*hists)[prefix+"_n_leadingmu_trig"]->Fill(_1mu, event_weight);
    (*hists)[prefix+"_n_trige"]->Fill(ntrige, event_weight);
    (*hists)[prefix+"_n_trigmu"]->Fill(ntrigmu, event_weight);
}*/

void full_analyzer::divide_for_eff(std::map<TString, TH1*>* hists, TString prefix)
{
    (*hists)[prefix+"_corrl2_pt_eff"]->Divide((*hists)[prefix+"_corrl2_pt_eff_den"]);
    (*hists)[prefix+"_corrl2_ctau_eff"]->Divide((*hists)[prefix+"_corrl2_ctau_eff_den"]);
    (*hists)[prefix+"_corrl2_gendist_eff"]->Divide((*hists)[prefix+"_corrl2_gendist_eff_den"]);

    (*hists)[prefix+"_l2_and_vtx_ctau_eff"]->Divide((*hists)[prefix+"_l2_and_vtx_ctau_eff_den"]);
    (*hists)[prefix+"_l2_and_vtx_ctau_zoom_eff"]->Divide((*hists)[prefix+"_l2_and_vtx_ctau_zoom_eff_den"]);
    (*hists)[prefix+"_l2_and_vtx_ctau_zoom2_eff"]->Divide((*hists)[prefix+"_l2_and_vtx_ctau_zoom2_eff_den"]);

    (*hists)[prefix+"_vtx_PV-SVdxy_eff"]->Divide((*hists)[prefix+"_vtx_PV-SVdxy_eff_den"]);
    (*hists)[prefix+"_vtx_PV-SVdxy_zoom_eff"]->Divide((*hists)[prefix+"_vtx_PV-SVdxy_zoom_eff_den"]);
    (*hists)[prefix+"_vtx_PV-SVdxy_zoom2_eff"]->Divide((*hists)[prefix+"_vtx_PV-SVdxy_zoom2_eff_den"]);
    (*hists)[prefix+"_vtx_PV-SVdxy_zoom3_eff"]->Divide((*hists)[prefix+"_vtx_PV-SVdxy_zoom3_eff_den"]);
    (*hists)[prefix+"_vtx_PV-SVdxyz_eff"]->Divide((*hists)[prefix+"_vtx_PV-SVdxyz_eff_den"]);
    (*hists)[prefix+"_vtx_PV-SVdxyz_zoom_eff"]->Divide((*hists)[prefix+"_vtx_PV-SVdxyz_zoom_eff_den"]);
    (*hists)[prefix+"_vtx_ctau_eff"]->Divide((*hists)[prefix+"_vtx_ctau_eff_den"]);
    (*hists)[prefix+"_vtx_ctau_zoom_eff"]->Divide((*hists)[prefix+"_vtx_ctau_zoom_eff_den"]);
    (*hists)[prefix+"_vtx_ctau_zoom2_eff"]->Divide((*hists)[prefix+"_vtx_ctau_zoom2_eff_den"]);
}

void full_analyzer::give_alphanumeric_labels(std::map<TString, TH1*>* hists, TString prefix)
{
    TString SSorOS = (prefix.Index("SS") == -1)? "OS" : "SS";
    TString l = (prefix.Index("_e") == -1)? "mu" : "e";

    int nx = 8;
    const char *cutflow_labels[nx] = {"2 lep. presel.", "HLT single " + l, "1 prompt " + l, "1 displ " + l + " " + SSorOS, "0 add. lepton", "0 tight ID jets", "M_ll < 80", "dphi_ll > 2.4"};
    for(int i = 1; i <= nx; i++) (*hists)[prefix+"_cutflow"]->GetXaxis()->SetBinLabel(i,cutflow_labels[i-1]);
    nx = 9;
    const char *cuts_labels[nx] = {"2 lep. presel.", "HLT single " + l, "1 prompt " + l, "1 displ " + l + " " + SSorOS, "new displ ID " + l + " " + SSorOS, "0 add. lepton", "0 tight ID jets", "M_ll < 80", "dphi_ll > 2.4"};
    for(int i = 1; i <= nx; i++) (*hists)[prefix+"_cuts"]->GetXaxis()->SetBinLabel(i,cuts_labels[i-1]);
}

