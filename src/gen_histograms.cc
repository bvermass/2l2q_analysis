///////////////////////////////////////////////////////
//part of class full_analyzer, everything gen-related//
///////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::init_HNL_MC_check(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D)
{
    if(sampleflavor.Index("Run") != -1) return;
    (*hists2D)["MC_check_gen_l1_l2_charge"]         = new TH2F("MC_check_gen_l1_l2_charge", ";l_{1} Charge; l_{2} Charge", 2, -2, 2, 2, -2, 2);
    (*hists)["gen_l1_pt"]                           = new TH1F("gen_l1_pt", ";l_{1}^{gen} #it{p}_{T} [GeV]; Events", 40, 0, 80);
    (*hists)["gen_l2_pt"]                           = new TH1F("gen_l2_pt", ";l_{2}^{gen} #it{p}_{T} [GeV]; Events", 40, 0, 80);
    (*hists)["gen_l1_flavor"]                       = new TH1F("gen_l1_flavor", ";l_{1}^{gen} flavor; Events", 32, -16, 16);
    (*hists)["gen_l2_flavor"]                       = new TH1F("gen_l2_flavor", ";l_{2}^{gen} flavor; Events", 32, -16, 16);
    (*hists)["gen_N_pt"]                            = new TH1F("gen_N_pt", ";HNL #it{p}_{T} [GeV]; Events", 40, 0, 80);
    (*hists)["gen_M_l1_N"]                          = new TH1F("gen_M_l1_N", ";M_{Nl1} [GeV]; Events", 40, 0, 150);
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

    //log scale
    double xmin = 0.8;
    double xmax = 300;
    int nbins   = 25;
    double xbins[nbins+1];
    make_logscale(&xbins[0], nbins, xmin, xmax);
    (*hists)["gen_PV-SVdist_xlog"]   = new TH1F("gen_PV-SVdist_xlog", ";#Delta_{xyz} (PV_{gen}, SV_{gen}) [cm]; Events", nbins, xbins);
}

void full_analyzer::fill_HNL_MC_check(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D)
{
    if(sampleflavor.Index("Run") != -1) return;
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

    (*hists)["gen_nTrueInteractions"]->Fill(_nTrueInt, event_weight);

    if(i_gen_l1 != -1 && i_gen_l2 != -1){
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
        (*hists)["gen_PV-SVdist_xlog"]->Fill(get_PVSVdist_gen(i_gen_l2), event_weight);

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
    if(sampleflavor.Index("Run") != -1) return;
    (*hists)[prefix+"_nTrueInteractions"]               = new TH1F(prefix+"_nTrueInteractions", ";N(true interactions);Events", 50, 0, 100);
    (*hists)[prefix+"_KVForIVF_categories"]             = new TH1F(prefix+"_KVForIVF_categories", ";;Events", 4, 0, 4);
    (*hists)[prefix+"_ngentr"]                          = new TH1F(prefix+"_ngentr", ";N_{tracks}^{gen} from HNL;Events", 15, 0, 15);
    (*hists)[prefix+"_ctau"]                            = new TH1F(prefix+"_ctau", ";c#tau_{HNL} [cm];Events", 40, 0, 100);
    (*hists)[prefix+"_ctaug"]                           = new TH1F(prefix+"_ctaug", ";#gamma c#tau_{HNL} [cm];Events", 40, 0, 100);

    (*hists)[prefix+"_KVF_SVgen-reco"]                  = new TH1F(prefix+"_KVF_SVgen-reco", ";|SV_{fit} - SV_{gen}| [cm] (KVF);Events", 30, 0, 10);
    (*hists)[prefix+"_KVF_SVgen-reco_zoom"]             = new TH1F(prefix+"_KVF_SVgen-reco_zoom", ";|SV_{fit} - SV_{gen}| [cm] (KVF);Events", 15, 0, 1);
    (*hists)[prefix+"_KVF_SVgen-reco_aftercut_zoom"]    = new TH1F(prefix+"_KVF_SVgen-reco_aftercut_zoom", ";|SV_{fit} - SV_{gen}| [cm] (KVF);Events", 15, 0, 1);
    (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco"]       = new TH2F(prefix+"_KVF_PV-SVdxyz_genvsreco", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);#Delta_{xyz}(PV, SV_{fit}) [cm] (gen)", 100, 0, 60, 100, 0, 60);
    (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco_zoom"]      = new TH2F(prefix+"_KVF_PV-SVdxyz_genvsreco_zoom", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);#Delta_{xyz}(PV, SV_{fit}) [cm] (gen)", 100, 0, 10, 100, 0, 10);

    (*hists)[prefix+"_IVF_ctau"]                        = new TH1F(prefix+"_IVF_ctau", ";c#tau [cm] (IVF);Events", 40, 0, 100);
    (*hists)[prefix+"_IVF_SVgen-reco"]                  = new TH1F(prefix+"_IVF_SVgen-reco", ";|SV_{fit} - SV_{gen}| [cm] (IVF);Events", 30, 0, 10);
    (*hists)[prefix+"_IVF_SVgen-reco_zoom"]             = new TH1F(prefix+"_IVF_SVgen-reco_zoom", ";|SV_{fit} - SV_{gen}| [cm] (IVF);Events", 15, 0, 1);
    (*hists)[prefix+"_IVF_SVgen-reco_aftercut_zoom"]    = new TH1F(prefix+"_IVF_SVgen-reco_aftercut_zoom", ";|SV_{fit} - SV_{gen}| [cm] (IVF);Events", 10, 0, 0.3);
    (*hists2D)[prefix+"_IVF_PV-SVdxyz_genvsreco"]       = new TH2F(prefix+"_IVF_PV-SVdxyz_genvsreco", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);#Delta_{xyz}(PV, SV_{gen}) [cm] (gen)", 100, 0, 60, 100, 0, 60);
    (*hists2D)[prefix+"_IVF_PV-SVdxyz_genvsreco_zoom"]  = new TH2F(prefix+"_IVF_PV-SVdxyz_genvsreco_zoom", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);#Delta_{xyz}(PV, SV_{gen}) [cm] (gen)", 100, 0, 5, 100, 0, 5);
    (*hists2D)[prefix+"_IVF_ctauHN_PV-SVdxyz"]          = new TH2F(prefix+"_IVF_ctauHN_PV-SVdxyz", ";c#tau (HNL) [cm]; #Delta_{xyz} (PV, SV_{fit}) [cm]", 20, 0, 30, 20, 0, 30);
    (*hists2D)[prefix+"_IVF_ctauHN_genPV-SVdxyz"]       = new TH2F(prefix+"_IVF_ctauHN_gen_PV-SVdxyz", ";c#tau (HNL) [cm]; #Delta_{xyz} (PV, SV)^{gen} [cm]", 20, 0, 30, 20, 0, 30);
    (*hists2D)[prefix+"_IVF_ctaugHN_PV-SVdxyz"]         = new TH2F(prefix+"_IVF_ctaugHN_PV-SVdxyz", ";#gamma c#tau (HNL) [cm]; #Delta_{xyz} (PV, SV_{fit}) [cm]", 20, 0, 30, 20, 0, 30);
    (*hists2D)[prefix+"_IVF_ctaugHN_genPV-SVdxyz"]      = new TH2F(prefix+"_IVF_ctaugHN_gen_PV-SVdxyz", ";#gamma c#tau (HNL) [cm]; #Delta_{xyz} (PV, SV)^{gen} [cm]", 20, 0, 30, 20, 0, 30);

    (*hists)[prefix+"_l1_pt_eff_num"]                   = new TH1F(prefix+"_l1_pt_eff_num", ";#it{p}_{T} [GeV];Events", 15, 0, 40);
    (*hists)[prefix+"_l1_pt_eff_den"]                   = new TH1F(prefix+"_l1_pt_eff_den", ";#it{p}_{T} [GeV];Events", 15, 0, 40);
    (*hists)[prefix+"_l1_ctau_eff_num"]                 = new TH1F(prefix+"_l1_ctau_eff_num", ";c#tau [cm];Events", 15, 0, 40);
    (*hists)[prefix+"_l1_ctau_eff_den"]                 = new TH1F(prefix+"_l1_ctau_eff_den", ";c#tau [cm];Events", 15, 0, 40);
    (*hists)[prefix+"_l2_pt_eff_num"]                   = new TH1F(prefix+"_l2_pt_eff_num", ";#it{p}_{T} [GeV];Events", 15, 0, 40);
    (*hists)[prefix+"_l2_pt_eff_den"]                   = new TH1F(prefix+"_l2_pt_eff_den", ";#it{p}_{T} [GeV];Events", 15, 0, 40);
    (*hists)[prefix+"_l2_ctau_eff_num"]                 = new TH1F(prefix+"_l2_ctau_eff_num", ";c#tau [cm];Events", 15, 0, 40);
    (*hists)[prefix+"_l2_ctau_eff_den"]                 = new TH1F(prefix+"_l2_ctau_eff_den", ";c#tau [cm];Events", 15, 0, 40);
    (*hists)[prefix+"_l2_SVgen-reco_eff_num"]           = new TH1F(prefix+"_l2_SVgen-reco_eff_num", ";|SV_{fit} - SV_{gen}| [cm];Events", 15, -1.5, 10);
    (*hists)[prefix+"_l2_SVgen-reco_eff_den"]           = new TH1F(prefix+"_l2_SVgen-reco_eff_den", ";|SV_{fit} - SV_{gen}| [cm];Events", 15, -1.5, 10);
}

void full_analyzer::add_KVF_eff_histograms(std::map<TString, TH1*>* hists, TString prefix)
{
    if(sampleflavor.Index("Run") != -1) return;
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_eff_num"]        = new TH1F(prefix+"_KVF_gen_PV-SVdxy_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 60);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_eff_den"]        = new TH1F(prefix+"_KVF_gen_PV-SVdxy_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 60);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom_eff_num"]   = new TH1F(prefix+"_KVF_gen_PV-SVdxy_zoom_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom_eff_den"]   = new TH1F(prefix+"_KVF_gen_PV-SVdxy_zoom_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_num"]   = new TH1F(prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_den"]   = new TH1F(prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_ctau_eff_num"]                = new TH1F(prefix+"_KVF_ctau_eff_num", ";c #tau [cm] (KVF);Events", 20, 0, 100);
    (*hists)[prefix+"_KVF_ctau_eff_den"]                = new TH1F(prefix+"_KVF_ctau_eff_den", ";c #tau [cm] (KVF);Events", 20, 0, 100);
    (*hists)[prefix+"_KVF_ctau_zoom_eff_num"]           = new TH1F(prefix+"_KVF_ctau_zoom_eff_num", ";c #tau [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_ctau_zoom_eff_den"]           = new TH1F(prefix+"_KVF_ctau_zoom_eff_den", ";c #tau [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_ctau_zoom2_eff_num"]          = new TH1F(prefix+"_KVF_ctau_zoom2_eff_num", ";c #tau [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_ctau_zoom2_eff_den"]          = new TH1F(prefix+"_KVF_ctau_zoom2_eff_den", ";c #tau [cm] (KVF);Events", 20, 0, 1);

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

void full_analyzer::add_IVF_eff_histograms(std::map<TString, TH1*>* hists, TString prefix)
{
    if(sampleflavor.Index("Run") != -1) return;
    (*hists)[prefix+"_IVF_cutflow"]                     = new TH1F(prefix+"_IVF_cutflow", ";;Events", 3, 0, 3);
    (*hists)[prefix+"_IVF_PV-SVdxy_eff_num"]            = new TH1F(prefix+"_IVF_PV-SVdxy_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_PV-SVdxy_eff_den"]            = new TH1F(prefix+"_IVF_PV-SVdxy_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom_eff_num"]       = new TH1F(prefix+"_IVF_PV-SVdxy_zoom_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom_eff_den"]       = new TH1F(prefix+"_IVF_PV-SVdxy_zoom_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom2_eff_num"]      = new TH1F(prefix+"_IVF_PV-SVdxy_zoom2_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 1);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom2_eff_den"]      = new TH1F(prefix+"_IVF_PV-SVdxy_zoom2_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 1);
    (*hists)[prefix+"_IVF_PV-SVdxyz_eff_num"]           = new TH1F(prefix+"_IVF_PV-SVdxyz_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 100);
    (*hists)[prefix+"_IVF_PV-SVdxyz_eff_den"]           = new TH1F(prefix+"_IVF_PV-SVdxyz_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 100);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom_eff_num"]      = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom_eff_den"]      = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom2_eff_num"]      = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom2_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 1);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom2_eff_den"]      = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom2_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 1);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_eff_num"]        = new TH1F(prefix+"_IVF_gen_PV-SVdxy_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_eff_den"]        = new TH1F(prefix+"_IVF_gen_PV-SVdxy_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom_eff_num"]   = new TH1F(prefix+"_IVF_gen_PV-SVdxy_zoom_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom_eff_den"]   = new TH1F(prefix+"_IVF_gen_PV-SVdxy_zoom_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_num"]  = new TH1F(prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 1);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_den"]  = new TH1F(prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 1);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz_eff_num"]       = new TH1F(prefix+"_IVF_gen_PV-SVdxyz_eff_num", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz_eff_den"]       = new TH1F(prefix+"_IVF_gen_PV-SVdxyz_eff_den", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz_zoom_eff_num"]  = new TH1F(prefix+"_IVF_gen_PV-SVdxyz_zoom_eff_num", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 20);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz_zoom_eff_den"]  = new TH1F(prefix+"_IVF_gen_PV-SVdxyz_zoom_eff_den", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 20);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz_zoom2_eff_num"] = new TH1F(prefix+"_IVF_gen_PV-SVdxyz_zoom2_eff_num", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 1);
    (*hists)[prefix+"_IVF_gen_PV-SVdxyz_zoom2_eff_den"] = new TH1F(prefix+"_IVF_gen_PV-SVdxyz_zoom2_eff_den", ";#Delta_{xyz}(PV, SV_{gen}) [cm] (IVF);Events", 10, 0, 1);
    (*hists)[prefix+"_IVF_ctau_eff_num"]                = new TH1F(prefix+"_IVF_ctau_eff_num", ";c #tau [cm] (IVF);Events", 10, 0, 100);
    (*hists)[prefix+"_IVF_ctau_eff_den"]                = new TH1F(prefix+"_IVF_ctau_eff_den", ";c #tau [cm] (IVF);Events", 10, 0, 100);
    (*hists)[prefix+"_IVF_ctau_zoom_eff_num"]           = new TH1F(prefix+"_IVF_ctau_zoom_eff_num", ";c #tau [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_ctau_zoom_eff_den"]           = new TH1F(prefix+"_IVF_ctau_zoom_eff_den", ";c #tau [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_ctau_zoom2_eff_num"]          = new TH1F(prefix+"_IVF_ctau_zoom2_eff_num", ";c #tau [cm] (IVF);Events", 10, 0, 1);
    (*hists)[prefix+"_IVF_ctau_zoom2_eff_den"]          = new TH1F(prefix+"_IVF_ctau_zoom2_eff_den", ";c #tau [cm] (IVF);Events", 10, 0, 1);
    (*hists)[prefix+"_IVF_ctaug_eff_num"]                = new TH1F(prefix+"_IVF_ctaug_eff_num", ";#gamma c #tau [cm] (IVF);Events", 10, 0, 100);
    (*hists)[prefix+"_IVF_ctaug_eff_den"]                = new TH1F(prefix+"_IVF_ctaug_eff_den", ";#gamma c #tau [cm] (IVF);Events", 10, 0, 100);
    (*hists)[prefix+"_IVF_ctaug_zoom_eff_num"]           = new TH1F(prefix+"_IVF_ctaug_zoom_eff_num", ";#gamma c #tau [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_ctaug_zoom_eff_den"]           = new TH1F(prefix+"_IVF_ctaug_zoom_eff_den", ";#gamma c #tau [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_ctaug_zoom2_eff_num"]          = new TH1F(prefix+"_IVF_ctaug_zoom2_eff_num", ";#gamma c #tau [cm] (IVF);Events", 10, 0, 1);
    (*hists)[prefix+"_IVF_ctaug_zoom2_eff_den"]          = new TH1F(prefix+"_IVF_ctaug_zoom2_eff_den", ";#gamma c #tau [cm] (IVF);Events", 10, 0, 1);
    (*hists)[prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_num"] = new TH1F(prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_den"] = new TH1F(prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_num"]= new TH1F(prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_den"]= new TH1F(prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxy_nomatch"]             = new TH1F(prefix+"_IVF_PV-SVdxy_nomatch", ";#Delta_{xyz}(PV, SV_{fit}) [cm];Events", 10, 0, 10);
}

void full_analyzer::fill_gen_HNLtagger_tree(HNLtagger& hnltagger_gen, int i_jet)
{
    if(sampleflavor != "e" and sampleflavor != "mu") return;
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
        hnltagger_gen._JetConstituentdxy[i]                = _gen_NPackedDtrs_matchdxy[i];
        hnltagger_gen._JetConstituentdz[i]                 = _gen_NPackedDtrs_matchdz[i];
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


void full_analyzer::add_chargeflip_histograms(std::map<TString, TH2*>* hists2D, TString prefix){
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
}

void full_analyzer::fill_chargeflip_histograms(std::map<TString, TH2*>* hists2D, TString prefix, int i_leading, int i_subleading){
    if(_lFlavor[i_leading] == 0){
        (*hists2D)[prefix+"_gen_l1_chargeflip"]->Fill(_gen_lCharge[i_gen_leading_e], _lCharge[i_leading], event_weight);
        (*hists2D)[prefix+"_gen_l1_flipvschargeconst"]->Fill(_gen_lCharge[i_gen_leading_e]*_lCharge[i_leading], _lElectronChargeConst[i_leading], event_weight);
    }
    if(_lFlavor[i_subleading] == 0){
        (*hists2D)[prefix+"_gen_l2_chargeflip"]->Fill(_gen_lCharge[i_gen_subleading_displ_e], _lCharge[i_subleading], event_weight);
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_0p1cm"]->Fill(_gen_lCharge[i_gen_subleading_displ_e]*_lCharge[i_subleading], fabs(_dxy[i_subleading]), event_weight);
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_1cm"]->Fill(_gen_lCharge[i_gen_subleading_displ_e]*_lCharge[i_subleading], fabs(_dxy[i_subleading]), event_weight);
        (*hists2D)[prefix+"_gen_l2_flipvsdxy_10cm"]->Fill(_gen_lCharge[i_gen_subleading_displ_e]*_lCharge[i_subleading], fabs(_dxy[i_subleading]), event_weight);
        (*hists2D)[prefix+"_gen_l2_flipvschargeconst"]->Fill(_gen_lCharge[i_gen_subleading_displ_e]*_lCharge[i_subleading], _lElectronChargeConst[i_subleading], event_weight);
        if(_lCharge[i_subleading] == _gen_lCharge[i_gen_subleading_displ_e]){
            (*hists2D)[prefix+"_gen_l2_noflip_chargeconstvsdxy_0p1cm"]->Fill(_lElectronChargeConst[i_subleading], fabs(_dxy[i_subleading]), event_weight);
            (*hists2D)[prefix+"_gen_l2_noflip_chargeconstvsdxy_1cm"]->Fill(_lElectronChargeConst[i_subleading], fabs(_dxy[i_subleading]), event_weight);
            (*hists2D)[prefix+"_gen_l2_noflip_chargeconstvsdxy_10cm"]->Fill(_lElectronChargeConst[i_subleading], fabs(_dxy[i_subleading]), event_weight);
        }else {
            (*hists2D)[prefix+"_gen_l2_flip_chargeconstvsdxy_0p1cm"]->Fill(_lElectronChargeConst[i_subleading], fabs(_dxy[i_subleading]), event_weight);
            (*hists2D)[prefix+"_gen_l2_flip_chargeconstvsdxy_1cm"]->Fill(_lElectronChargeConst[i_subleading], fabs(_dxy[i_subleading]), event_weight);
            (*hists2D)[prefix+"_gen_l2_flip_chargeconstvsdxy_10cm"]->Fill(_lElectronChargeConst[i_subleading], fabs(_dxy[i_subleading]), event_weight);
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
