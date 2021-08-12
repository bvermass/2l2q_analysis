///////////////////////////////////////////////////////
//part of class full_analyzer, everything gen-related//
///////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::init_HNL_MC_check(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D)
{
    if(isData) return;
    (*hists2D)["MC_check_gen_l1_l2_charge"]         = new TH2F("MC_check_gen_l1_l2_charge", ";l_{1} Charge; l_{2} Charge", 2, -2, 2, 2, -2, 2);
    (*hists)["gen_ctauHN"]                          = new TH1F("gen_ctauHN", ";c#tau [mm];Events", 40, 0, 100);
    (*hists)["gen_l1_pt"]                           = new TH1F("gen_l1_pt", ";l_{1}^{gen} #it{p}_{T} [GeV]; Events", 40, 0, 80);
    (*hists)["gen_l2_pt"]                           = new TH1F("gen_l2_pt", ";l_{2}^{gen} #it{p}_{T} [GeV]; Events", 40, 0, 80);
    (*hists)["gen_l1_flavor"]                       = new TH1F("gen_l1_flavor", ";l_{1}^{gen} flavor; Events", 32, -16, 16);
    (*hists)["gen_l2_flavor"]                       = new TH1F("gen_l2_flavor", ";l_{2}^{gen} flavor; Events", 32, -16, 16);
    (*hists)["gen_N_pt"]                            = new TH1F("gen_N_pt", ";HNL #it{p}_{T} [GeV]; Events", 40, 0, 80);
    (*hists)["gen_M_l1_N"]                          = new TH1F("gen_M_l1_N", ";M_{Nl1} [GeV]; Events", 40, 60, 110);
    (*hists)["gen_l2_tracks_dR"]                    = new TH1F("gen_l2_tracks_dR", ";#Delta R (l_{2}, tracks); Events", 40, 0, 1.5);
    (*hists)["gen_PV_Nvertex_dxyz"]                 = new TH1F("gen_PV_Nvertex_dxyz", ";#Delta_{3D} (PV^{reco} - Nvtx^{gen}) [cm]; Events", 40, 0, 0.05);
    (*hists)["gen_NPackedDtrs"]                     = new TH1F("gen_NPackedDtrs", ";N. of HNL Ch. Daughters^{gen}; Events", 30, 0, 30);
    (*hists)["gen_NPackedDtrs_ch"]                  = new TH1F("gen_NPackedDtrs_ch", ";HNL tracks^{gen}; Events", 12, 0, 12);
    (*hists)["gen_NPackedDtrs_ch_pt"]               = new TH1F("gen_NPackedDtrs_ch_pt", ";HNL Ch. Daughters^{gen} #it{p}_{T} [GeV] ; Events", 50, 0, 10);
    (*hists)["gen_NPackedDtrs_njets"]               = new TH1F("gen_NPackedDtrs_njets", ";N. jets from HNL (ch. PF);Events", 6, 0, 6); 
    (*hists)["gen_NPackedDtrs_ch_njets"]            = new TH1F("gen_NPackedDtrs_ch_njets", ";N. jets from HNL;Events (all PF)", 6, 0, 6); 
    (*hists)["gen_l1fromtau_pt"]                    = new TH1F("gen_l1fromtau_pt", ";l_{1}^{gen} from #tau_{1} #it{p}_{T} [GeV]; Events", 40, 0, 80);
    (*hists)["gen_l2fromtau_pt"]                    = new TH1F("gen_l2fromtau_pt", ";l_{2}^{gen} from #tau_{2} #it{p}_{T} [GeV]; Events", 40, 0, 80);
    (*hists)["gen_l1fromtau_ptfrac"]                = new TH1F("gen_l1fromtau_ptfrac", ";l_{1}^{gen} from #tau_{1} #it{p}_{T}^{l}/#it{p}_{T}^{#tau}; Events", 40, 0, 1);
    (*hists)["gen_l2fromtau_ptfrac"]                = new TH1F("gen_l2fromtau_ptfrac", ";l_{2}^{gen} from #tau_{2} #it{p}_{T}^{l}/#it{p}_{T}^{#tau}; Events", 40, 0, 1);
    (*hists)["gen_nTrueInteractions"]               = new TH1F("gen_nTrueInteractions", ";N(true interactions);Events", 50, 0, 100);
    (*hists2D)["gen_ntracks_genvsreco"]             = new TH2F("gen_ntracks_genvsreco", ";HNL tracks^{gen};SV tracks", 10, 0, 10, 10, 0, 10);
    (*hists2D)["gen_PV-SVdxyz_ctauHN"]              = new TH2F("gen_PV-SVdxyz_ctauHN", ";c#tau (HNL) [cm]; #Delta_{xyz} (PV, SV)^{gen} [cm]", 10, 0, 60, 10, 0, 60);
    (*hists2D)["gen_l2pt_ctauHN"]                   = new TH2F("gen_l2pt_ctauHN", ";c#tau (HNL) [cm]; #it{p}_{T} [GeV]", 10, 0, 60, 10, 0, 80);

    (*hists)["l1reco_pt_eff_num"]                   = new TH1F("l1reco_pt_eff_num", ";#it{p}_{T} [GeV];Events", 40, 0, 80);
    (*hists)["l1reco_pt_eff_den"]                   = new TH1F("l1reco_pt_eff_den", ";#it{p}_{T} [GeV];Events", 40, 0, 80);
    (*hists)["l1reco_eta_eff_num"]                  = new TH1F("l1reco_eta_eff_num", ";eta;Events", 40, -3, 3);
    (*hists)["l1reco_eta_eff_den"]                  = new TH1F("l1reco_eta_eff_den", ";eta;Events", 40, -3, 3);
    (*hists)["l1id_pt_eff_num"]                   = new TH1F("l1id_pt_eff_num", ";#it{p}_{T} [GeV];Events", 40, 0, 80);
    (*hists)["l1id_pt_eff_den"]                   = new TH1F("l1id_pt_eff_den", ";#it{p}_{T} [GeV];Events", 40, 0, 80);
    (*hists)["l1id_eta_eff_num"]                  = new TH1F("l1id_eta_eff_num", ";eta;Events", 40, -3, 3);
    (*hists)["l1id_eta_eff_den"]                  = new TH1F("l1id_eta_eff_den", ";eta;Events", 40, -3, 3);
    (*hists)["l1full_pt_eff_num"]                   = new TH1F("l1full_pt_eff_num", ";#it{p}_{T} [GeV];Events", 40, 0, 80);
    (*hists)["l1full_pt_eff_den"]                   = new TH1F("l1full_pt_eff_den", ";#it{p}_{T} [GeV];Events", 40, 0, 80);
    (*hists)["l1full_eta_eff_num"]                  = new TH1F("l1full_eta_eff_num", ";eta;Events", 40, -3, 3);
    (*hists)["l1full_eta_eff_den"]                  = new TH1F("l1full_eta_eff_den", ";eta;Events", 40, -3, 3);
    //(*hists)["l1reco_dxy_eff_num"]                  = new TH1F("l1reco_dxy_eff_num", ";dxy;Events", 40, 0, 0.1);
    //(*hists)["l1reco_dxy_eff_den"]                  = new TH1F("l1reco_dxy_eff_den", ";dxy;Events", 40, 0, 0.1);
    //(*hists)["l1reco_dz_eff_num"]                   = new TH1F("l1reco_dz_eff_num", ";dz;Events", 40, 0, 0.1);
    //(*hists)["l1reco_dz_eff_den"]                   = new TH1F("l1reco_dz_eff_den", ";dz;Events", 40, 0, 0.1);
    (*hists)["l1reco_ctau_eff_num"]                 = new TH1F("l1reco_ctau_eff_num", ";c#tau [mm];Events", 40, 0, 60);
    (*hists)["l1reco_ctau_eff_den"]                 = new TH1F("l1reco_ctau_eff_den", ";c#tau [mm];Events", 40, 0, 60);
    (*hists)["l2reco_pt_eff_num"]                   = new TH1F("l2reco_pt_eff_num", ";#it{p}_{T} [GeV];Events", 20, 0, 60);
    (*hists)["l2reco_pt_eff_den"]                   = new TH1F("l2reco_pt_eff_den", ";#it{p}_{T} [GeV];Events", 20, 0, 60);
    (*hists)["l2reco_eta_eff_num"]                  = new TH1F("l2reco_eta_eff_num", ";eta;Events", 20, -3, 3);
    (*hists)["l2reco_eta_eff_den"]                  = new TH1F("l2reco_eta_eff_den", ";eta;Events", 20, -3, 3);
    //(*hists)["l2reco_dxy_eff_num"]                  = new TH1F("l2reco_dxy_eff_num", ";dxy;Events", 20, 0, 0.1);
    //(*hists)["l2reco_dxy_eff_den"]                  = new TH1F("l2reco_dxy_eff_den", ";dxy;Events", 20, 0, 0.1);
    //(*hists)["l2reco_dz_eff_num"]                   = new TH1F("l2reco_dz_eff_num", ";dz;Events", 20, 0, 0.1);
    //(*hists)["l2reco_dz_eff_den"]                   = new TH1F("l2reco_dz_eff_den", ";dz;Events", 20, 0, 0.1);
    (*hists)["l2reco_ctau_eff_num"]                 = new TH1F("l2reco_ctau_eff_num", ";c#tau [mm];Events", 20, 0, 100);
    (*hists)["l2reco_ctau_eff_den"]                 = new TH1F("l2reco_ctau_eff_den", ";c#tau [mm];Events", 20, 0, 100);
    (*hists)["l2reco_Lxy_eff_num"]                 = new TH1F("l2reco_Lxy_eff_num", ";L_{xy}^{gen}[cm];Events", 20, 0, 40);
    (*hists)["l2reco_Lxy_eff_den"]                 = new TH1F("l2reco_Lxy_eff_den", ";L_{xy}^{gen}[cm];Events", 20, 0, 40);
    (*hists)["l2reco_Lxyz_eff_num"]                 = new TH1F("l2reco_Lxyz_eff_num", ";L_{xyz}^{gen}[cm];Events", 20, 0, 60);
    (*hists)["l2reco_Lxyz_eff_den"]                 = new TH1F("l2reco_Lxyz_eff_den", ";L_{xyz}^{gen}[cm];Events", 20, 0, 60);
    (*hists)["PVNvtxdist"]                          = new TH1F("PVNvtxdist", ";PVNvtxdist;Events", 30, 0, 1);
    //(*hists)["l2reco_SVgen-reco_eff_num"]           = new TH1F("l2reco_SVgen-reco_eff_num", ";|SV_{fit} - SV_{gen}| [cm];Events", 20, -1.5, 10);
    //(*hists)["l2reco_SVgen-reco_eff_den"]           = new TH1F("l2reco_SVgen-reco_eff_den", ";|SV_{fit} - SV_{gen}| [cm];Events", 20, -1.5, 10);

    (*hists)["l2id_pt_eff_num"]                   = new TH1F("l2id_pt_eff_num", ";#it{p}_{T} [GeV];Events", 20, 0, 60);
    (*hists)["l2id_pt_eff_den"]                   = new TH1F("l2id_pt_eff_den", ";#it{p}_{T} [GeV];Events", 20, 0, 60);
    (*hists)["l2id_eta_eff_num"]                  = new TH1F("l2id_eta_eff_num", ";eta;Events", 20, -3, 3);
    (*hists)["l2id_eta_eff_den"]                  = new TH1F("l2id_eta_eff_den", ";eta;Events", 20, -3, 3);
    (*hists)["l2id_ctau_eff_num"]                 = new TH1F("l2id_ctau_eff_num", ";c#tau [mm];Events", 20, 0, 100);
    (*hists)["l2id_ctau_eff_den"]                 = new TH1F("l2id_ctau_eff_den", ";c#tau [mm];Events", 20, 0, 100);
    (*hists)["l2id_Lxy_eff_num"]                 = new TH1F("l2id_Lxy_eff_num", ";L_{xy}^{gen}[cm];Events", 20, 0, 40);
    (*hists)["l2id_Lxy_eff_den"]                 = new TH1F("l2id_Lxy_eff_den", ";L_{xy}^{gen}[cm];Events", 20, 0, 40);
    (*hists)["l2id_Lxyz_eff_num"]                 = new TH1F("l2id_Lxyz_eff_num", ";L_{xyz}^{gen}[cm];Events", 20, 0, 60);
    (*hists)["l2id_Lxyz_eff_den"]                 = new TH1F("l2id_Lxyz_eff_den", ";L_{xyz}^{gen}[cm];Events", 20, 0, 60);

    (*hists)["l2full_pt_eff_num"]                   = new TH1F("l2full_pt_eff_num", ";#it{p}_{T} [GeV];Events", 10, 0, 50);
    (*hists)["l2full_pt_eff_den"]                   = new TH1F("l2full_pt_eff_den", ";#it{p}_{T} [GeV];Events", 10, 0, 50);
    (*hists)["l2full_eta_eff_num"]                  = new TH1F("l2full_eta_eff_num", ";eta;Events", 10, -3, 3);
    (*hists)["l2full_eta_eff_den"]                  = new TH1F("l2full_eta_eff_den", ";eta;Events", 10, -3, 3);
    (*hists)["l2full_Lxy_eff_num"]                 = new TH1F("l2full_Lxy_eff_num", ";L_{xy}^{gen}[cm];Events", 10, 0, 40);
    (*hists)["l2full_Lxy_eff_den"]                 = new TH1F("l2full_Lxy_eff_den", ";L_{xy}^{gen}[cm];Events", 10, 0, 40);
    (*hists)["l2full_Lxyz_eff_num"]                 = new TH1F("l2full_Lxyz_eff_num", ";L_{xyz}^{gen}[cm];Events", 10, 0, 60);
    (*hists)["l2full_Lxyz_eff_den"]                 = new TH1F("l2full_Lxyz_eff_den", ";L_{xyz}^{gen}[cm];Events", 10, 0, 60);

    (*hists)["l2high_l1_pt"]                        = new TH1F("l2high_l1_pt", ";#it{p}_{T} [GeV];Events", 20, 0, 60);
    (*hists)["l2high_N_pt"]                         = new TH1F("l2high_N_pt", ";#it{p}_{T} [GeV];Events", 20, 0, 60);
    (*hists)["l2high_Lxy"]                          = new TH1F("l2high_Lxy", ";L_{xy}^{gen}[cm];Events", 20, 0, 60);
    //log scale
    double xmin = 0.8;
    double xmax = 300;
    int nbins   = 25;
    std::vector<double> xbins = make_logscale(nbins, xmin, xmax);
    (*hists)["gen_PV-SVdist_xlog"]   = new TH1F("gen_PV-SVdist_xlog", ";#Delta_{xyz} (PV_{gen}, SV_{gen}) [cm]; Events", nbins, &xbins[0]);
}

void full_analyzer::fill_HNL_MC_check(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, double event_weight)
{
    if(isData) return;
    // stuff related to gen Packed Candidates
    int ch_count = 0;
    for(unsigned i = 0; i < _gen_nNPackedDtrs; i++){
        if(_gen_NPackedDtrsCharge[i] != 0){ 
            (*hists)["gen_NPackedDtrs_ch_pt"]->Fill(_gen_NPackedDtrsPt[i], event_weight);
            ch_count++;
        }
    }
    (*hists)["gen_NPackedDtrs"]->Fill(_gen_nNPackedDtrs, event_weight);
    (*hists)["gen_NPackedDtrs_ch"]->Fill(ch_count, event_weight);
    
    // jets containing any particles from HNL
    int njets_ch = 0, njets = 0;
    for(unsigned i_jet = 0; i_jet < _nJets; i_jet++){
        for(unsigned i = 0; i < _gen_nNPackedDtrs; i++){
            if(get_dR(_jetEta[i_jet], _jetPhi[i_jet], _gen_NPackedDtrsEta[i], _gen_NPackedDtrsPhi[i]) < 0.4){ 
                njets++;
                if(_gen_NPackedDtrsCharge[i] != 0) njets_ch++;
                break;
            }
        }
    } 
    (*hists)["gen_NPackedDtrs_njets"]->Fill(njets, event_weight);
    (*hists)["gen_NPackedDtrs_ch_njets"]->Fill(njets, event_weight);

    (*hists)["gen_ctauHN"]->Fill(_ctauHN, event_weight*reweighting_weights[1e-5]);
    (*hists)["gen_nTrueInteractions"]->Fill(_nTrueInt, event_weight);

    if(i_gen_l1 != -1 && i_gen_l2 != -1){
        (*hists2D)["gen_PV-SVdxyz_ctauHN"]->Fill(_ctauHN, gen_PVSVdist, event_weight);
        (*hists2D)["gen_l2pt_ctauHN"]->Fill(_ctauHN, _gen_lPt[i_gen_l2], event_weight);
        (*hists2D)["MC_check_gen_l1_l2_charge"]->Fill(_gen_lCharge[i_gen_l1], _gen_lCharge[i_gen_l2], event_weight);
        (*hists)["gen_l1_pt"]->Fill(_gen_lPt[i_gen_l1], event_weight);
        (*hists)["gen_l2_pt"]->Fill(_gen_lPt[i_gen_l2], event_weight);
        (*hists)["gen_l1_flavor"]->Fill(_gen_lFlavor[i_gen_l1], event_weight);
        (*hists)["gen_l2_flavor"]->Fill(_gen_lFlavor[i_gen_l2], event_weight);
        (*hists)["gen_N_pt"]->Fill(_gen_NPt, event_weight);
        LorentzVector lepton1_vec(_gen_lPt[i_gen_l1], _gen_lEta[i_gen_l1], _gen_lPhi[i_gen_l1], _gen_lE[i_gen_l1]);
        LorentzVector HNL_vec(_gen_NPt, _gen_NEta, _gen_NPhi, _gen_NE);
        (*hists)["gen_M_l1_N"]->Fill((lepton1_vec + HNL_vec).mass(), event_weight);
        (*hists)["gen_PV_Nvertex_dxyz"]->Fill(sqrt((_PV_x - _gen_Nvertex_x)*(_PV_x - _gen_Nvertex_x) + (_PV_y - _gen_Nvertex_y)*(_PV_y - _gen_Nvertex_y) + (_PV_z - _gen_Nvertex_z)*(_PV_z - _gen_Nvertex_z)), event_weight);
        (*hists)["gen_PV-SVdist_xlog"]->Fill(get_xyz_distance(_PV_x, _PV_y, _PV_z, _gen_vertex_x[i_gen_l2], _gen_vertex_y[i_gen_l2], _gen_vertex_z[i_gen_l2]), event_weight);

        if(_l1l2SV){
            (*hists2D)["gen_ntracks_genvsreco"]->Fill(ch_count, _IVF_ntracks[i_subleading], event_weight);
        }

        LorentzVector l2_vector(_gen_lPt[i_gen_l2], _gen_lEta[i_gen_l2], _gen_lPhi[i_gen_l2], _gen_lE[i_gen_l2]);
        for(unsigned i = 0; i < _gen_nNPackedDtrs; i++){
            LorentzVector track_vector(_gen_NPackedDtrsPt[i], _gen_NPackedDtrsEta[i], _gen_NPackedDtrsPhi[i], _gen_NPackedDtrsE[i]);
            (*hists)["gen_l2_tracks_dR"]->Fill(deltaR(l2_vector, track_vector), event_weight);
        }

        // lepton from tau histograms
        if(fabs(_gen_lFlavor[i_gen_l1]) == 2){
            int i_gen_l1fromtau = get_lfromtau(i_gen_l1);
            if(i_gen_l1fromtau != -1){
                (*hists)["gen_l1fromtau_pt"]->Fill(_gen_lPt[i_gen_l1fromtau]);
                (*hists)["gen_l1fromtau_ptfrac"]->Fill(_gen_lPt[i_gen_l1fromtau]/_gen_lPt[i_gen_l1]);
            }
        }
        if(fabs(_gen_lFlavor[i_gen_l2]) == 2){
            int i_gen_l2fromtau = get_lfromtau(i_gen_l2);
            if(i_gen_l2fromtau != -1){
                (*hists)["gen_l2fromtau_pt"]->Fill(_gen_lPt[i_gen_l2fromtau]);
                (*hists)["gen_l2fromtau_ptfrac"]->Fill(_gen_lPt[i_gen_l2fromtau]/_gen_lPt[i_gen_l2]);
            }
        }
    }
}


void full_analyzer::add_gen_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix)
{
    if(isData) return;
    (*hists)[prefix+"_nTrueInteractions"]               = new TH1F(prefix+"_nTrueInteractions", ";N(true interactions);Events", 50, 0, 100);
    //(*hists)[prefix+"_KVForIVF_categories"]             = new TH1F(prefix+"_KVForIVF_categories", ";;Events", 4, 0, 4);
    (*hists)[prefix+"_ngentr"]                          = new TH1F(prefix+"_ngentr", ";N_{tracks}^{gen} from HNL;Events", 15, 0, 15);
    (*hists)[prefix+"_ctau"]                            = new TH1F(prefix+"_ctau", ";ct_{HNL} [mm];Events", 40, 0, 100);
    //(*hists)[prefix+"_ctaug"]                           = new TH1F(prefix+"_ctaug", ";#gamma c#tau_{HNL} [mm];Events", 40, 0, 100);

    if(extensive_plots){
        (*hists)[prefix+"_KVF_SVgen-reco"]                  = new TH1F(prefix+"_KVF_SVgen-reco", ";|SV_{fit} - SV_{gen}| [cm] (KVF);Events", 30, 0, 10);
        (*hists)[prefix+"_KVF_SVgen-reco_zoom"]             = new TH1F(prefix+"_KVF_SVgen-reco_zoom", ";|SV_{fit} - SV_{gen}| [cm] (KVF);Events", 15, 0, 1);
        (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco"]       = new TH2F(prefix+"_KVF_PV-SVdxyz_genvsreco", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);#Delta_{xyz}(PV, SV_{fit}) [cm] (gen)", 100, 0, 60, 100, 0, 60);
        (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco_zoom"]      = new TH2F(prefix+"_KVF_PV-SVdxyz_genvsreco_zoom", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);#Delta_{xyz}(PV, SV_{fit}) [cm] (gen)", 100, 0, 10, 100, 0, 10);

        (*hists)[prefix+"_IVF_ctau"]                        = new TH1F(prefix+"_IVF_ctau", ";ct [cm] (IVF);Events", 40, 0, 100);
        (*hists)[prefix+"_IVF_SVgen-reco"]                  = new TH1F(prefix+"_IVF_SVgen-reco", ";|SV_{fit} - SV_{gen}| [cm] (IVF);Events", 30, 0, 10);
        (*hists)[prefix+"_IVF_SVgen-reco_zoom"]             = new TH1F(prefix+"_IVF_SVgen-reco_zoom", ";|SV_{fit} - SV_{gen}| [cm] (IVF);Events", 15, 0, 1);
        (*hists2D)[prefix+"_IVF_PV-SVdxyz_genvsreco"]       = new TH2F(prefix+"_IVF_PV-SVdxyz_genvsreco", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);#Delta_{xyz}(PV, SV_{gen}) [cm] (gen)", 100, 0, 60, 100, 0, 60);
        (*hists2D)[prefix+"_IVF_PV-SVdxyz_genvsreco_zoom"]  = new TH2F(prefix+"_IVF_PV-SVdxyz_genvsreco_zoom", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);#Delta_{xyz}(PV, SV_{gen}) [cm] (gen)", 100, 0, 5, 100, 0, 5);
        (*hists2D)[prefix+"_IVF_ctauHN_PV-SVdxyz"]          = new TH2F(prefix+"_IVF_ctauHN_PV-SVdxyz", ";ct (HNL) [cm]; #Delta_{xyz} (PV, SV_{fit}) [cm]", 10, 0, 60, 10, 0, 60);
        (*hists2D)[prefix+"_IVF_ctauHN_genPV-SVdxyz"]       = new TH2F(prefix+"_IVF_ctauHN_gen_PV-SVdxyz", ";ct (HNL) [cm]; #Delta_{xyz} (PV, SV)^{gen} [cm]", 10, 0, 60, 10, 0, 60);
        (*hists2D)[prefix+"_IVF_ctaugHN_PV-SVdxyz"]         = new TH2F(prefix+"_IVF_ctaugHN_PV-SVdxyz", ";#gamma ct (HNL) [cm]; #Delta_{xyz} (PV, SV_{fit}) [cm]", 10, 0, 60, 10, 0, 60);
        (*hists2D)[prefix+"_IVF_ctaugHN_genPV-SVdxyz"]      = new TH2F(prefix+"_IVF_ctaugHN_gen_PV-SVdxyz", ";#gamma ct (HNL) [cm]; #Delta_{xyz} (PV, SV)^{gen} [cm]", 10, 0, 60, 10, 0, 60);
    }

    (*hists)[prefix+"_l1_pt_eff_num"]                   = new TH1F(prefix+"_l1_pt_eff_num", ";#it{p}_{T} [GeV];Events", 15, 0, 40);
    (*hists)[prefix+"_l1_pt_eff_den"]                   = new TH1F(prefix+"_l1_pt_eff_den", ";#it{p}_{T} [GeV];Events", 15, 0, 40);
    (*hists)[prefix+"_l1_ctau_eff_num"]                 = new TH1F(prefix+"_l1_ctau_eff_num", ";ct [cm];Events", 15, 0, 40);
    (*hists)[prefix+"_l1_ctau_eff_den"]                 = new TH1F(prefix+"_l1_ctau_eff_den", ";ct [cm];Events", 15, 0, 40);
    (*hists)[prefix+"_l2_pt_eff_num"]                   = new TH1F(prefix+"_l2_pt_eff_num", ";#it{p}_{T} [GeV];Events", 15, 0, 40);
    (*hists)[prefix+"_l2_pt_eff_den"]                   = new TH1F(prefix+"_l2_pt_eff_den", ";#it{p}_{T} [GeV];Events", 15, 0, 40);
    (*hists)[prefix+"_l2_ctau_eff_num"]                 = new TH1F(prefix+"_l2_ctau_eff_num", ";ct [cm];Events", 15, 0, 40);
    (*hists)[prefix+"_l2_ctau_eff_den"]                 = new TH1F(prefix+"_l2_ctau_eff_den", ";ct [cm];Events", 15, 0, 40);
    (*hists)[prefix+"_l2_SVgen-reco_eff_num"]           = new TH1F(prefix+"_l2_SVgen-reco_eff_num", ";|SV_{fit} - SV_{gen}| [cm];Events", 15, -1.5, 10);
    (*hists)[prefix+"_l2_SVgen-reco_eff_den"]           = new TH1F(prefix+"_l2_SVgen-reco_eff_den", ";|SV_{fit} - SV_{gen}| [cm];Events", 15, -1.5, 10);
}

void full_analyzer::add_KVF_eff_histograms(std::map<TString, TH1*>* hists, TString prefix)
{
    if(isData) return;
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_eff_num"]        = new TH1F(prefix+"_KVF_gen_PV-SVdxy_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 60);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_eff_den"]        = new TH1F(prefix+"_KVF_gen_PV-SVdxy_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 60);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom_eff_num"]   = new TH1F(prefix+"_KVF_gen_PV-SVdxy_zoom_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom_eff_den"]   = new TH1F(prefix+"_KVF_gen_PV-SVdxy_zoom_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_num"]   = new TH1F(prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_den"]   = new TH1F(prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_ctau_eff_num"]                = new TH1F(prefix+"_KVF_ctau_eff_num", ";c t [cm] (KVF);Events", 20, 0, 100);
    (*hists)[prefix+"_KVF_ctau_eff_den"]                = new TH1F(prefix+"_KVF_ctau_eff_den", ";c t [cm] (KVF);Events", 20, 0, 100);
    (*hists)[prefix+"_KVF_ctau_zoom_eff_num"]           = new TH1F(prefix+"_KVF_ctau_zoom_eff_num", ";c t [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_ctau_zoom_eff_den"]           = new TH1F(prefix+"_KVF_ctau_zoom_eff_den", ";c t [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_ctau_zoom2_eff_num"]          = new TH1F(prefix+"_KVF_ctau_zoom2_eff_num", ";c t [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_ctau_zoom2_eff_den"]          = new TH1F(prefix+"_KVF_ctau_zoom2_eff_den", ";c t [cm] (KVF);Events", 20, 0, 1);

    (*hists)[prefix+"_KVF_PV-SVdxy_eff_num"]            = new TH1F(prefix+"_KVF_PV-SVdxy_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 60);
    (*hists)[prefix+"_KVF_PV-SVdxy_eff_den"]            = new TH1F(prefix+"_KVF_PV-SVdxy_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 60);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom_eff_num"]       = new TH1F(prefix+"_KVF_PV-SVdxy_zoom_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom_eff_den"]       = new TH1F(prefix+"_KVF_PV-SVdxy_zoom_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom2_eff_num"]      = new TH1F(prefix+"_KVF_PV-SVdxy_zoom2_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom2_eff_den"]      = new TH1F(prefix+"_KVF_PV-SVdxy_zoom2_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_PV-SVdxyz_eff_num"]           = new TH1F(prefix+"_KVF_PV-SVdxyz_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 100);
    (*hists)[prefix+"_KVF_PV-SVdxyz_eff_den"]           = new TH1F(prefix+"_KVF_PV-SVdxyz_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 100);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom_eff_num"]      = new TH1F(prefix+"_KVF_PV-SVdxyz_zoom_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom_eff_den"]      = new TH1F(prefix+"_KVF_PV-SVdxyz_zoom_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom2_eff_num"]     = new TH1F(prefix+"_KVF_PV-SVdxyz_zoom2_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom2_eff_den"]     = new TH1F(prefix+"_KVF_PV-SVdxyz_zoom2_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_PV-SVdxy_onlySVgen-reco_eff_num"]= new TH1F(prefix+"_KVF_PV-SVdxy_onlySVgen-reco_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxy_onlySVgen-reco_eff_den"]= new TH1F(prefix+"_KVF_PV-SVdxy_onlySVgen-reco_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxyz_onlySVgen-reco_eff_num"]= new TH1F(prefix+"_KVF_PV-SVdxyz_onlySVgen-reco_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxyz_onlySVgen-reco_eff_den"]= new TH1F(prefix+"_KVF_PV-SVdxyz_onlySVgen-reco_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
}

void full_analyzer::add_HNLrecotracks_KVF_eff_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix)
{
    if(!isSignal) return;
    (*hists)[prefix+"_HNLrecotracks_KVF_PV-SVdxyz_eff_num"] = new TH1F(prefix+"_HNLrecotracks_KVF_PV-SVdxyz_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 10, 0, 60);
    (*hists)[prefix+"_HNLrecotracks_KVF_PV-SVdxyz_eff_den"] = new TH1F(prefix+"_HNLrecotracks_KVF_PV-SVdxyz_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 10, 0, 60);
    (*hists)[prefix+"_HNLrecotracks_KVF_ctau_eff_num"] = new TH1F(prefix+"_HNLrecotracks_KVF_ctau_eff_num", ";ct [cm] (KVF);Events", 10, 0, 60);
    (*hists)[prefix+"_HNLrecotracks_KVF_ctau_eff_den"] = new TH1F(prefix+"_HNLrecotracks_KVF_ctau_eff_den", ";ct [cm] (KVF);Events", 10, 0, 60);
    (*hists)[prefix+"_HNLrecotracks_KVF_PV-SVdxyz_onlylIVFmatch_eff_num"] = new TH1F(prefix+"_HNLrecotracks_KVF_PV-SVdxyz_onlylIVFmatch_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 10, 0, 60);
    (*hists)[prefix+"_HNLrecotracks_KVF_PV-SVdxyz_onlylIVFmatch_eff_den"] = new TH1F(prefix+"_HNLrecotracks_KVF_PV-SVdxyz_onlylIVFmatch_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 10, 0, 60);
    (*hists)[prefix+"_HNLrecotracks_KVF_ctau_onlylIVFmatch_eff_num"] = new TH1F(prefix+"_HNLrecotracks_KVF_ctau_onlylIVFmatch_eff_num", ";ct [cm] (KVF);Events", 10, 0, 60);
    (*hists)[prefix+"_HNLrecotracks_KVF_ctau_onlylIVFmatch_eff_den"] = new TH1F(prefix+"_HNLrecotracks_KVF_ctau_onlylIVFmatch_eff_den", ";ct [cm] (KVF);Events", 10, 0, 60);
    (*hists)[prefix+"_HNLrecotracks_noKVF_l2_pt"]                           = new TH1F(prefix+"_HNLrecotracks_noKVF_l2_pt", ";l_{2} #it{p}_{T} [GeV];Events", 30, 0, 50);
    (*hists)[prefix+"_HNLrecotracks_noKVF_l2_eta"]                          = new TH1F(prefix+"_HNLrecotracks_noKVF_l2_eta", ";l_{2} #eta;Events", 30, -3, 3);
    (*hists)[prefix+"_HNLrecotracks_noKVF_l2_dxy"]                          = new TH1F(prefix+"_HNLrecotracks_noKVF_l2_dxy", ";l_{2} dxy [cm];Events", 30, 0, 0.5);
    (*hists)[prefix+"_HNLrecotracks_noKVF_l2_dz"]                           = new TH1F(prefix+"_HNLrecotracks_noKVF_l2_dz", ";l_{2} dz [cm];Events", 30, 0, 2);
    (*hists)[prefix+"_HNLrecotracks_noKVF_l2_reliso"]                       = new TH1F(prefix+"_HNLrecotracks_noKVF_l2_reliso", ";l_{2} Rel Iso;Events", 30, 0, 3.5);
    (*hists)[prefix+"_HNLrecotracks_noKVF_ntracks"]                         = new TH1F(prefix+"_HNLrecotracks_noKVF_ntracks", ";HNL reco tracks;Events", 7,0,7);
    (*hists)[prefix+"_HNLrecotracks_noKVF_2trPCA"]                         = new TH1F(prefix+"_HNLrecotracks_noKVF_2trPCA", ";PCA distance[cm];Events", 20,0,20);

    (*hists)[prefix+"_HNLrecotracks_yesKVF_2trPCA"]                         = new TH1F(prefix+"_HNLrecotracks_yesKVF_2trPCA", ";PCA distance[cm];Events", 20,0,20);
}


void full_analyzer::add_IVF_eff_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix)
{
    if(isData) return;
    (*hists)[prefix+"_IVF_cutflow"]                     = new TH1F(prefix+"_IVF_cutflow", ";;Events", 3, 0, 3);
    //(*hists)[prefix+"_IVF_PV-SVdxy_eff_num"]            = new TH1F(prefix+"_IVF_PV-SVdxy_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 60);
    //(*hists)[prefix+"_IVF_PV-SVdxy_eff_den"]            = new TH1F(prefix+"_IVF_PV-SVdxy_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 60);
    //(*hists)[prefix+"_IVF_PV-SVdxy_zoom_eff_num"]       = new TH1F(prefix+"_IVF_PV-SVdxy_zoom_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 20);
    //(*hists)[prefix+"_IVF_PV-SVdxy_zoom_eff_den"]       = new TH1F(prefix+"_IVF_PV-SVdxy_zoom_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 20);
    //(*hists)[prefix+"_IVF_PV-SVdxy_zoom2_eff_num"]      = new TH1F(prefix+"_IVF_PV-SVdxy_zoom2_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 2);
    //(*hists)[prefix+"_IVF_PV-SVdxy_zoom2_eff_den"]      = new TH1F(prefix+"_IVF_PV-SVdxy_zoom2_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 2);
    //(*hists)[prefix+"_IVF_PV-SVdxyz_eff_num"]           = new TH1F(prefix+"_IVF_PV-SVdxyz_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 100);
    //(*hists)[prefix+"_IVF_PV-SVdxyz_eff_den"]           = new TH1F(prefix+"_IVF_PV-SVdxyz_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 100);
    //(*hists)[prefix+"_IVF_PV-SVdxyz_zoom_eff_num"]      = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 20);
    //(*hists)[prefix+"_IVF_PV-SVdxyz_zoom_eff_den"]      = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 20);
    //(*hists)[prefix+"_IVF_PV-SVdxyz_zoom2_eff_num"]      = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom2_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 2);
    //(*hists)[prefix+"_IVF_PV-SVdxyz_zoom2_eff_den"]      = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom2_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 2);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_eff_num"]        = new TH1F(prefix+"_IVF_gen_PV-SVdxy_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 40);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_eff_den"]        = new TH1F(prefix+"_IVF_gen_PV-SVdxy_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 40);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_onlylIVFmatch_eff_num"]        = new TH1F(prefix+"_IVF_gen_PV-SVdxy_onlylIVFmatch_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_onlylIVFmatch_eff_den"]        = new TH1F(prefix+"_IVF_gen_PV-SVdxy_onlylIVFmatch_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr_eff_num"]     = new TH1F(prefix+"_IVF_gen_PV-SVdxy_tr_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr_eff_den"]     = new TH1F(prefix+"_IVF_gen_PV-SVdxy_tr_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr_onlylIVFmatch_eff_num"]     = new TH1F(prefix+"_IVF_gen_PV-SVdxy_tr_onlylIVFmatch_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr_onlylIVFmatch_eff_den"]     = new TH1F(prefix+"_IVF_gen_PV-SVdxy_tr_onlylIVFmatch_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr2_eff_num"]     = new TH1F(prefix+"_IVF_gen_PV-SVdxy_tr2_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr2_eff_den"]     = new TH1F(prefix+"_IVF_gen_PV-SVdxy_tr2_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr2_onlylIVFmatch_eff_num"]     = new TH1F(prefix+"_IVF_gen_PV-SVdxy_tr2_onlylIVFmatch_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr2_onlylIVFmatch_eff_den"]     = new TH1F(prefix+"_IVF_gen_PV-SVdxy_tr2_onlylIVFmatch_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr3_eff_num"]     = new TH1F(prefix+"_IVF_gen_PV-SVdxy_tr3_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr3_eff_den"]     = new TH1F(prefix+"_IVF_gen_PV-SVdxy_tr3_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr3_onlylIVFmatch_eff_num"]     = new TH1F(prefix+"_IVF_gen_PV-SVdxy_tr3_onlylIVFmatch_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_tr3_onlylIVFmatch_eff_den"]     = new TH1F(prefix+"_IVF_gen_PV-SVdxy_tr3_onlylIVFmatch_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom_eff_num"]   = new TH1F(prefix+"_IVF_gen_PV-SVdxy_zoom_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 20);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom_eff_den"]   = new TH1F(prefix+"_IVF_gen_PV-SVdxy_zoom_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 20);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz_eff_num"]       = new TH1F(prefix+"_IVF_gen_PV-SVdxyz_eff_num", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz_eff_den"]       = new TH1F(prefix+"_IVF_gen_PV-SVdxyz_eff_den", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz_zoom_eff_num"]  = new TH1F(prefix+"_IVF_gen_PV-SVdxyz_zoom_eff_num", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 20);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz_zoom_eff_den"]  = new TH1F(prefix+"_IVF_gen_PV-SVdxyz_zoom_eff_den", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 20);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy2_eff_num"]       = new TH1F(prefix+"_IVF_gen_PV-SVdxy2_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy2_eff_den"]       = new TH1F(prefix+"_IVF_gen_PV-SVdxy2_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy2_zoom_eff_num"]  = new TH1F(prefix+"_IVF_gen_PV-SVdxy2_zoom_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 20);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy2_zoom_eff_den"]  = new TH1F(prefix+"_IVF_gen_PV-SVdxy2_zoom_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 20);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz2_eff_num"]      = new TH1F(prefix+"_IVF_gen_PV-SVdxyz2_eff_num", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz2_eff_den"]      = new TH1F(prefix+"_IVF_gen_PV-SVdxyz2_eff_den", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz2_zoom_eff_num"] = new TH1F(prefix+"_IVF_gen_PV-SVdxyz2_zoom_eff_num", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 20);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz2_zoom_eff_den"] = new TH1F(prefix+"_IVF_gen_PV-SVdxyz2_zoom_eff_den", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 20);
    (*hists2D)[prefix+"_IVF_gen_PV-SVdxyz_ctauHN_eff_num"]       = new TH2F(prefix+"_IVF_gen_PV-SVdxyz_ctauHN_eff_num", ";ct (HNL) [cm]; #Delta_{xyz} (PV, SV)^{gen} [cm]", 10, 0, 60, 10, 0, 60);
    (*hists2D)[prefix+"_IVF_gen_PV-SVdxyz_ctauHN_eff_den"]       = new TH2F(prefix+"_IVF_gen_PV-SVdxyz_ctauHN_eff_den", ";ct (HNL) [cm]; #Delta_{xyz} (PV, SV)^{gen} [cm]", 10, 0, 60, 10, 0, 60);
    double xmax = 60., xmin = 0.1;
    unsigned nbins = 15;
    std::vector<double> xbins = make_logscale(nbins, xmin, xmax);
    (*hists2D)[prefix+"_IVF_gen_PV-SVdxy_residual_xlog"]     = new TH2F(prefix+"_IVF_gen_PV-SVdxy_residual_xlog", ";L_{xy}^{gen}[cm];#Delta (L_{xy}^{gen} - L_{xy}) [cm]", nbins, &xbins[0], 100, -5, 5);
    (*hists2D)[prefix+"_IVF_gen_PV-SVdxyz_residual_xlog"]    = new TH2F(prefix+"_IVF_gen_PV-SVdxyz_residual_xlog", ";L_{xyz}^{gen}[cm];#Delta (L_{xyz}^{gen} - L_{xyz}) [cm]", nbins, &xbins[0], 100, -5, 5);
    (*hists2D)[prefix+"_IVF_gen_SVmass_residual"]       = new TH2F(prefix+"_IVF_gen_SVmass_residual", ";M_{SV}^{gen} [GeV];#Delta (M_{SV}^{gen} - M_{SV}) [GeV]", 12, 0, 12, 100, -5, 5);
    (*hists2D)[prefix+"_IVF_gen_SVmasstontracks_residual"]       = new TH2F(prefix+"_IVF_gen_SVmasstontracks_residual", ";M_{SV}^{gen} [GeV];#Delta (N_{tracks}^{gen} - N_{tracks})", 12, 0, 12, 11, -5.5, 5.5);
    (*hists2D)[prefix+"_IVF_gen_ntracks_residual"]       = new TH2F(prefix+"_IVF_gen_ntracks_residual", ";N_{tracks}^{gen} in SV;#Delta (N_{tracks}^{gen} - N_{tracks})", 6, 0.5, 6.5, 11, -5.5, 5.5);
    (*hists2D)[prefix+"_IVF_gen_ntracksrecovsinSV_residual"]       = new TH2F(prefix+"_IVF_gen_ntracksrecovsinSV_residual", ";N_{tracks}^{reco} from HNL;#Delta (N_{tracks}^{reco} - N_{tracks}^{SV})", 6, 0.5, 6.5, 11, -5.5, 5.5);
    if(extensive_plots){
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_num"]  = new TH1F(prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 2);
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_den"]  = new TH1F(prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 2);
        (*hists)[prefix+"_IVF_gen_PV-SVdxyz_zoom2_eff_num"] = new TH1F(prefix+"_IVF_gen_PV-SVdxyz_zoom2_eff_num", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 2);
        (*hists)[prefix+"_IVF_gen_PV-SVdxyz_zoom2_eff_den"] = new TH1F(prefix+"_IVF_gen_PV-SVdxyz_zoom2_eff_den", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 2);
        (*hists)[prefix+"_IVF_ctau_eff_num"]                = new TH1F(prefix+"_IVF_ctau_eff_num", ";ct [cm] (IVF);Events", 10, 0, 100);
        (*hists)[prefix+"_IVF_ctau_eff_den"]                = new TH1F(prefix+"_IVF_ctau_eff_den", ";ct [cm] (IVF);Events", 10, 0, 100);
        (*hists)[prefix+"_IVF_ctau_zoom_eff_num"]           = new TH1F(prefix+"_IVF_ctau_zoom_eff_num", ";ct [cm] (IVF);Events", 10, 0, 10);
        (*hists)[prefix+"_IVF_ctau_zoom_eff_den"]           = new TH1F(prefix+"_IVF_ctau_zoom_eff_den", ";ct [cm] (IVF);Events", 10, 0, 10);
        (*hists)[prefix+"_IVF_ctau_zoom2_eff_num"]          = new TH1F(prefix+"_IVF_ctau_zoom2_eff_num", ";ct [cm] (IVF);Events", 10, 0, 1);
        (*hists)[prefix+"_IVF_ctau_zoom2_eff_den"]          = new TH1F(prefix+"_IVF_ctau_zoom2_eff_den", ";ct [cm] (IVF);Events", 10, 0, 1);
        (*hists)[prefix+"_IVF_ctaug_eff_num"]                = new TH1F(prefix+"_IVF_ctaug_eff_num", ";#gamma ct [cm] (IVF);Events", 10, 0, 100);
        (*hists)[prefix+"_IVF_ctaug_eff_den"]                = new TH1F(prefix+"_IVF_ctaug_eff_den", ";#gamma ct [cm] (IVF);Events", 10, 0, 100);
        (*hists)[prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_num"] = new TH1F(prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 20);
        (*hists)[prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_den"] = new TH1F(prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 20);
        (*hists)[prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_num"]= new TH1F(prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 20);
        (*hists)[prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_den"]= new TH1F(prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 20);
        (*hists)[prefix+"_IVF_PV-SVdxy_nomatch"]             = new TH1F(prefix+"_IVF_PV-SVdxy_nomatch", ";#Delta_{xyz}(PV, SV_{fit}) [cm];Events", 10, 0, 10);
    }
}

void full_analyzer::fill_gen_HNLtagger_tree(HNLtagger& hnltagger_gen, int i_jet)
{
    if(!isSignal) return;
    if(i_jet == -1) return;
    hnltagger_gen._JetIsFromHNL = get_JetIsFromHNL(i_jet);
    hnltagger_gen._JetPt        = _jetPt[i_jet];
    hnltagger_gen._JetEta       = _jetEta[i_jet];
    hnltagger_gen._nJetConstituents                    = _gen_nNPackedDtrs;
    for(unsigned i = 0; i < _gen_nNPackedDtrs; i++){
        hnltagger_gen._JetConstituentPt[i]                 = _gen_NPackedDtrsPt[i];
        hnltagger_gen._JetConstituentEta[i]                = _gen_NPackedDtrsEta[i];
        hnltagger_gen._JetConstituentPhi[i]                = _gen_NPackedDtrsPhi[i];
        hnltagger_gen._JetConstituentPdgId[i]              = _gen_NPackedDtrsPdgId[i];
        hnltagger_gen._JetConstituentCharge[i]             = _gen_NPackedDtrsCharge[i];
        hnltagger_gen._JetConstituentdxyErr[i]             = 0;
        hnltagger_gen._JetConstituentdzErr[i]              = 0;
        hnltagger_gen._JetConstituentNumberOfHits[i]      = 0;
        hnltagger_gen._JetConstituentNumberOfPixelHits[i] = 0;
        hnltagger_gen._JetConstituentHasTrack[i]          = 0;
    }
    for(unsigned i = _gen_nNPackedDtrs; i < 50; i++){
        hnltagger_gen._JetConstituentPt[i]                 = 0;
        hnltagger_gen._JetConstituentEta[i]                = 0;
        hnltagger_gen._JetConstituentPhi[i]                = 0;
        hnltagger_gen._JetConstituentPdgId[i]              = 0;
        hnltagger_gen._JetConstituentCharge[i]             = 0;
        hnltagger_gen._JetConstituentdxy[i]                = 0;
        hnltagger_gen._JetConstituentdz[i]                 = 0;
        hnltagger_gen._JetConstituentdxyErr[i]             = 0;
        hnltagger_gen._JetConstituentdzErr[i]              = 0;
        hnltagger_gen._JetConstituentNumberOfHits[i]      = 0;
        hnltagger_gen._JetConstituentNumberOfPixelHits[i] = 0;
        hnltagger_gen._JetConstituentHasTrack[i]          = 0;
    }
    hnltagger_gen.HNLtagger_tree->Fill();
}


void full_analyzer::add_chargeflip_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix){
    if(extensive_plots){
        (*hists2D)[prefix+"_gen_l1_chargeflip"]                 = new TH2F(prefix+"_gen_l1_chargeflip", ";Gen Charge;Charge", 2, -2, 2, 2, -2, 2);
        (*hists2D)[prefix+"_gen_l2_chargeflip"]                 = new TH2F(prefix+"_gen_l2_chargeflip", ";Gen Charge;Charge", 2, -2, 2, 2, -2, 2);
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_0p1cm"]            = new TH2F(prefix+"_gen_l2_flipvsdxy_0p1cm", ";;|dxy| [cm]", 2, -2, 2, 10, 0, 0.1);
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_1cm"]              = new TH2F(prefix+"_gen_l2_flipvsdxy_1cm", ";;|dxy| [cm]", 2, -2, 2, 10, 0, 1);
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_10cm"]             = new TH2F(prefix+"_gen_l2_flipvsdxy_10cm", ";;|dxy| [cm]", 2, -2, 2, 10, 0, 10);
        (*hists2D)[prefix+"_gen_l1_flipvschargeconst"]          = new TH2F(prefix+"_gen_l1_flipvschargeconst", ";;e. Charge Consist.", 2, -2, 2, 2, 0, 2);
        (*hists2D)[prefix+"_gen_l2_flipvschargeconst"]          = new TH2F(prefix+"_gen_l2_flipvschargeconst", ";;e. Charge Consist.", 2, -2, 2, 2, 0, 2);
        (*hists2D)[prefix+"_gen_l2_flip_chargeconstvsdxy_0p1cm"] = new TH2F(prefix+"_gen_l2_flip_chargeconstvsdxy_0p1cm", ";e. Charge Consist.;|dxy| [cm]", 2, 0, 2, 10, 0, 0.1);
        (*hists2D)[prefix+"_gen_l2_flip_chargeconstvsdxy_1cm"]   = new TH2F(prefix+"_gen_l2_flip_chargeconstvsdxy_1cm", ";e. Charge Consist.;|dxy| [cm]", 2, 0, 2, 10, 0, 1);
        (*hists2D)[prefix+"_gen_l2_flip_chargeconstvsdxy_10cm"]  = new TH2F(prefix+"_gen_l2_flip_chargeconstvsdxy_10cm", ";e. Charge Consist.;|dxy| [cm]", 2, 0, 2, 10, 0, 10);
        (*hists2D)[prefix+"_gen_l2_noflip_chargeconstvsdxy_0p1cm"] = new TH2F(prefix+"_gen_l2_noflip_chargeconstvsdxy_0p1cm", ";e. Charge Consist.;|dxy| [cm]", 2, 0, 2, 10, 0, 0.1);
        (*hists2D)[prefix+"_gen_l2_noflip_chargeconstvsdxy_1cm"]   = new TH2F(prefix+"_gen_l2_noflip_chargeconstvsdxy_1cm", ";e. Charge Consist.;|dxy| [cm]", 2, 0, 2, 10, 0, 1);
        (*hists2D)[prefix+"_gen_l2_noflip_chargeconstvsdxy_10cm"]  = new TH2F(prefix+"_gen_l2_noflip_chargeconstvsdxy_10cm", ";e. Charge Consist.;|dxy| [cm]", 2, 0, 2, 10, 0, 10);
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_0p1cm"]->GetXaxis()->SetBinLabel(1, "Ch. flip");
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_0p1cm"]->GetXaxis()->SetBinLabel(2, "no Ch. flip");
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_1cm"]->GetXaxis()->SetBinLabel(1, "Ch. flip");
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_1cm"]->GetXaxis()->SetBinLabel(2, "no Ch. flip");
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_10cm"]->GetXaxis()->SetBinLabel(1, "Ch. flip");
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_10cm"]->GetXaxis()->SetBinLabel(2, "no Ch. flip");
        (*hists2D)[prefix+"_gen_l1_flipvschargeconst"]->GetXaxis()->SetBinLabel(1, "Ch. flip");
        (*hists2D)[prefix+"_gen_l1_flipvschargeconst"]->GetXaxis()->SetBinLabel(2, "no Ch. flip");
        (*hists2D)[prefix+"_gen_l2_flipvschargeconst"]->GetXaxis()->SetBinLabel(1, "Ch. flip");
        (*hists2D)[prefix+"_gen_l2_flipvschargeconst"]->GetXaxis()->SetBinLabel(2, "no Ch. flip");
        (*hists)[prefix+"_gen_l1_fromZ_pt_eff_den"]                            = new TH1F(prefix+"_gen_l1_fromZ_pt_eff_den", ";#it{p}_{T} [GeV]; Events", 20, 0, 100);
        (*hists)[prefix+"_gen_l1_fromZ_pt_eff_num"]                            = new TH1F(prefix+"_gen_l1_fromZ_pt_eff_num", ";#it{p}_{T} [GeV]; Events", 20, 0, 100);
        (*hists)[prefix+"_gen_l2_fromZ_pt_eff_den"]                            = new TH1F(prefix+"_gen_l2_fromZ_pt_eff_den", ";#it{p}_{T} [GeV]; Events", 20, 0, 100);
        (*hists)[prefix+"_gen_l2_fromZ_pt_eff_num"]                            = new TH1F(prefix+"_gen_l2_fromZ_pt_eff_num", ";#it{p}_{T} [GeV]; Events", 20, 0, 100);
        (*hists)[prefix+"_gen_l1_fromZ_dxy_eff_den"]                           = new TH1F(prefix+"_gen_l1_fromZ_dxy_eff_den", ";|dxy| [cm]; Events", 20, 0, 1);
        (*hists)[prefix+"_gen_l1_fromZ_dxy_eff_num"]                           = new TH1F(prefix+"_gen_l1_fromZ_dxy_eff_num", ";|dxy| [cm]; Events", 20, 0, 1);
        (*hists)[prefix+"_gen_l2_fromZ_dxy_eff_den"]                           = new TH1F(prefix+"_gen_l2_fromZ_dxy_eff_den", ";|dxy| [cm]; Events", 20, 0, 1);
        (*hists)[prefix+"_gen_l2_fromZ_dxy_eff_num"]                           = new TH1F(prefix+"_gen_l2_fromZ_dxy_eff_num", ";|dxy| [cm]; Events", 20, 0, 1);
        (*hists)[prefix+"_gen_l1_fake_chargeflipvsPt_eff_den"]                 = new TH1F(prefix+"_gen_l1_fake_chargeflipvsPt_eff_den", ";#it{p}_{T} [GeV];Charge flip Rate", 20, 0, 100);
        (*hists)[prefix+"_gen_l1_fake_chargeflipvsPt_eff_num"]                 = new TH1F(prefix+"_gen_l1_fake_chargeflipvsPt_eff_num", ";#it{p}_{T} [GeV];Charge flip Rate", 20, 0, 100);
        (*hists)[prefix+"_gen_l2_fake_chargeflipvsPt_eff_den"]                 = new TH1F(prefix+"_gen_l2_fake_chargeflipvsPt_eff_den", ";#it{p}_{T} [GeV];Charge flip Rate", 20, 0, 100);
        (*hists)[prefix+"_gen_l2_fake_chargeflipvsPt_eff_num"]                 = new TH1F(prefix+"_gen_l2_fake_chargeflipvsPt_eff_num", ";#it{p}_{T} [GeV];Charge flip Rate", 20, 0, 100);
        (*hists)[prefix+"_gen_l1_fake_chargeflipvsdxy_eff_den"]                 = new TH1F(prefix+"_gen_l1_fake_chargeflipvsdxy_eff_den", ";|dxy| [cm];Charge flip Rate", 20, 0, 1);
        (*hists)[prefix+"_gen_l1_fake_chargeflipvsdxy_eff_num"]                 = new TH1F(prefix+"_gen_l1_fake_chargeflipvsdxy_eff_num", ";|dxy| [cm];Charge flip Rate", 20, 0, 1);
        (*hists)[prefix+"_gen_l2_fake_chargeflipvsdxy_eff_den"]                 = new TH1F(prefix+"_gen_l2_fake_chargeflipvsdxy_eff_den", ";|dxy| [cm];Charge flip Rate", 20, 0, 1);
        (*hists)[prefix+"_gen_l2_fake_chargeflipvsdxy_eff_num"]                 = new TH1F(prefix+"_gen_l2_fake_chargeflipvsdxy_eff_num", ";|dxy| [cm];Charge flip Rate", 20, 0, 1);
        (*hists)[prefix+"_gen_l1_fromZ_chargeflipvsPt_eff_den"]                 = new TH1F(prefix+"_gen_l1_fromZ_chargeflipvsPt_eff_den", ";#it{p}_{T} [GeV];Charge flip Rate", 20, 0, 100);
        (*hists)[prefix+"_gen_l1_fromZ_chargeflipvsPt_eff_num"]                 = new TH1F(prefix+"_gen_l1_fromZ_chargeflipvsPt_eff_num", ";#it{p}_{T} [GeV];Charge flip Rate", 20, 0, 100);
        (*hists)[prefix+"_gen_l2_fromZ_chargeflipvsPt_eff_den"]                 = new TH1F(prefix+"_gen_l2_fromZ_chargeflipvsPt_eff_den", ";#it{p}_{T} [GeV];Charge flip Rate", 20, 0, 100);
        (*hists)[prefix+"_gen_l2_fromZ_chargeflipvsPt_eff_num"]                 = new TH1F(prefix+"_gen_l2_fromZ_chargeflipvsPt_eff_num", ";#it{p}_{T} [GeV];Charge flip Rate", 20, 0, 100);
        (*hists)[prefix+"_gen_l1_fromZ_chargeflipvsdxy_eff_den"]                 = new TH1F(prefix+"_gen_l1_fromZ_chargeflipvsdxy_eff_den", ";|dxy| [cm];Charge flip Rate", 20, 0, 1);
        (*hists)[prefix+"_gen_l1_fromZ_chargeflipvsdxy_eff_num"]                 = new TH1F(prefix+"_gen_l1_fromZ_chargeflipvsdxy_eff_num", ";|dxy| [cm];Charge flip Rate", 20, 0, 1);
        (*hists)[prefix+"_gen_l2_fromZ_chargeflipvsdxy_eff_den"]                 = new TH1F(prefix+"_gen_l2_fromZ_chargeflipvsdxy_eff_den", ";|dxy| [cm];Charge flip Rate", 20, 0, 1);
        (*hists)[prefix+"_gen_l2_fromZ_chargeflipvsdxy_eff_num"]                 = new TH1F(prefix+"_gen_l2_fromZ_chargeflipvsdxy_eff_num", ";|dxy| [cm];Charge flip Rate", 20, 0, 1);
    }
}

void full_analyzer::fill_chargeflip_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, double event_weight){
    if(extensive_plots){
        (*hists2D)[prefix+"_gen_l1_chargeflip"]->Fill(_gen_lCharge[i_gen_l1], _lCharge[i_leading], event_weight);
        (*hists2D)[prefix+"_gen_l2_chargeflip"]->Fill(_gen_lCharge[i_gen_l2], _lCharge[i_subleading], event_weight);
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_0p1cm"]->Fill(_gen_lCharge[i_gen_l2]*_lCharge[i_subleading], fabs(_dxy[i_subleading]), event_weight);
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_1cm"]->Fill(_gen_lCharge[i_gen_l2]*_lCharge[i_subleading], fabs(_dxy[i_subleading]), event_weight);
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_10cm"]->Fill(_gen_lCharge[i_gen_l2]*_lCharge[i_subleading], fabs(_dxy[i_subleading]), event_weight);
        if(_lFlavor[i_leading] == 0){
            (*hists2D)[prefix+"_gen_l1_flipvschargeconst"]->Fill(_gen_lCharge[i_gen_l1]*_lCharge[i_leading], _lElectronChargeConst[i_leading], event_weight);
        }
        if(_lFlavor[i_subleading] == 0){
            (*hists2D)[prefix+"_gen_l2_flipvschargeconst"]->Fill(_gen_lCharge[i_gen_l2]*_lCharge[i_subleading], _lElectronChargeConst[i_subleading], event_weight);
            if(_lCharge[i_subleading] == _gen_lCharge[i_gen_l2]){
                (*hists2D)[prefix+"_gen_l2_noflip_chargeconstvsdxy_0p1cm"]->Fill(_lElectronChargeConst[i_subleading], fabs(_dxy[i_subleading]), event_weight);
                (*hists2D)[prefix+"_gen_l2_noflip_chargeconstvsdxy_1cm"]->Fill(_lElectronChargeConst[i_subleading], fabs(_dxy[i_subleading]), event_weight);
                (*hists2D)[prefix+"_gen_l2_noflip_chargeconstvsdxy_10cm"]->Fill(_lElectronChargeConst[i_subleading], fabs(_dxy[i_subleading]), event_weight);
            }else {
                (*hists2D)[prefix+"_gen_l2_flip_chargeconstvsdxy_0p1cm"]->Fill(_lElectronChargeConst[i_subleading], fabs(_dxy[i_subleading]), event_weight);
                (*hists2D)[prefix+"_gen_l2_flip_chargeconstvsdxy_1cm"]->Fill(_lElectronChargeConst[i_subleading], fabs(_dxy[i_subleading]), event_weight);
                (*hists2D)[prefix+"_gen_l2_flip_chargeconstvsdxy_10cm"]->Fill(_lElectronChargeConst[i_subleading], fabs(_dxy[i_subleading]), event_weight);
            }
        }


        // Charge flip rate vs pt and vs dxy (computed as efficiency histograms)
        TString l1_source;
        (*hists)[prefix+"_gen_l1_fromZ_pt_eff_den"]->Fill(_lPt[i_leading]);
        (*hists)[prefix+"_gen_l1_fromZ_dxy_eff_den"]->Fill(fabs(_dxy[i_leading]));
        if(fabs(_gen_lMomPdg[i_gen_l1] == 23)){
            l1_source = "fromZ";
            (*hists)[prefix+"_gen_l1_fromZ_pt_eff_num"]->Fill(_lPt[i_leading]);
            (*hists)[prefix+"_gen_l1_fromZ_dxy_eff_num"]->Fill(fabs(_dxy[i_leading]));
        } else l1_source = "fake";

        (*hists)[prefix+"_gen_l1_"+l1_source+"_chargeflipvsPt_eff_den"]->Fill(_lPt[i_leading]);
        (*hists)[prefix+"_gen_l1_"+l1_source+"_chargeflipvsdxy_eff_den"]->Fill(fabs(_dxy[i_leading]));
        if(_lCharge[i_leading] != _gen_lCharge[i_gen_l1]){
            (*hists)[prefix+"_gen_l1_"+l1_source+"_chargeflipvsPt_eff_num"]->Fill(_lPt[i_leading]);
            (*hists)[prefix+"_gen_l1_"+l1_source+"_chargeflipvsdxy_eff_num"]->Fill(fabs(_dxy[i_leading]));
        }

        TString l2_source;
        (*hists)[prefix+"_gen_l2_fromZ_pt_eff_den"]->Fill(_lPt[i_subleading]);
        (*hists)[prefix+"_gen_l2_fromZ_dxy_eff_den"]->Fill(fabs(_dxy[i_subleading]));
        if(fabs(_gen_lMomPdg[i_gen_l2] == 23)){
            l2_source = "fromZ";
            (*hists)[prefix+"_gen_l2_fromZ_pt_eff_num"]->Fill(_lPt[i_subleading]);
            (*hists)[prefix+"_gen_l2_fromZ_pt_eff_num"]->Fill(_lPt[i_subleading]);
        } else l2_source = "fake";

        (*hists)[prefix+"_gen_l2_"+l2_source+"_chargeflipvsPt_eff_den"]->Fill(_lPt[i_subleading]);
        (*hists)[prefix+"_gen_l2_"+l2_source+"_chargeflipvsdxy_eff_den"]->Fill(fabs(_dxy[i_subleading]));
        if(_lCharge[i_subleading] != _gen_lCharge[i_gen_l2]){
            (*hists)[prefix+"_gen_l2_"+l2_source+"_chargeflipvsPt_eff_num"]->Fill(_lPt[i_subleading]);
            (*hists)[prefix+"_gen_l2_"+l2_source+"_chargeflipvsdxy_eff_num"]->Fill(fabs(_dxy[i_subleading]));
        }
    }
}

int full_analyzer::get_lfromtau(int i_gen_l){
    if(fabs(_gen_lFlavor[i_gen_l]) != 2){ std::cout << "you did not give a tau to get_lfromtau" << std::endl; return -1;}
    for(unsigned i = 0; i < _gen_nL; i++){
        if(fabs(_gen_lMomPdg[i]) == 15 and (fabs(_gen_lFlavor[i]) == 0 or fabs(_gen_lFlavor[i]) == 1)){
            if(fabs(_gen_lEta[i] - _gen_lEta[i_gen_l]) < 1){ 
                return (int)i;
            }
        }
    }
    return -1;
}
