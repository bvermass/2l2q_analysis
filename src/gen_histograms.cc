///////////////////////////////////////////////////////
//part of class full_analyzer, everything gen-related//
///////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::init_HNL_MC_check(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D)
{
    (*hists2D)["MC_check_gen_l1_l2_charge"]         = new TH2F("MC_check_gen_l1_l2_charge", ";l_{1} Charge; l_{2} Charge", 2, -2, 2, 2, -2, 2);
    (*hists)["gen_l1_pt"]                           = new TH1F("gen_l1_pt", ";l_{1}^{gen} #it{p}_{T} [GeV]; Events", 40, 0, 80);
    (*hists)["gen_l2_pt"]                           = new TH1F("gen_l2_pt", ";l_{1}^{gen} #it{p}_{T} [GeV]; Events", 40, 0, 80);
    (*hists)["gen_l1_flavor"]                       = new TH1F("gen_l1_flavor", ";l_{1}^{gen} flavor; Events", 32, -16, 16);
    (*hists)["gen_l2_flavor"]                       = new TH1F("gen_l2_flavor", ";l_{1}^{gen} flavor; Events", 32, -16, 16);
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

    if(i_gen_l1 != -1 && i_gen_l2 != -1){
        (*hists2D)["MC_check_gen_l1_l2_charge"]->Fill(_gen_lCharge[i_gen_l1], _gen_lCharge[i_gen_l2], event_weight);
        (*hists)["gen_l1_pt"]->Fill(_gen_lPt[i_gen_l1], event_weight);
        (*hists)["gen_l2_pt"]->Fill(_gen_lPt[i_gen_l2], event_weight);
        (*hists)["gen_l1_flavor"]->Fill(_gen_lFlavor[i_gen_l1], event_weight);
        (*hists)["gen_l2_flavor"]->Fill(_gen_lFlavor[i_gen_l2], event_weight);
        (*hists)["gen_N_pt"]->Fill(_gen_NPt, event_weight);
        TLorentzVector lepton1_vec;
        TLorentzVector HNL_vec;
        lepton1_vec.SetPtEtaPhiE(_gen_lPt[i_gen_l1], _gen_lEta[i_gen_l1], _gen_lPhi[i_gen_l1], _gen_lE[i_gen_l1]);
        HNL_vec.SetPtEtaPhiE(_gen_NPt, _gen_NEta, _gen_NPhi, _gen_NE);
        (*hists)["gen_M_l1_N"]->Fill((lepton1_vec + HNL_vec).M(), event_weight);
        (*hists)["gen_PV_Nvertex_dxyz"]->Fill(sqrt((_PV_x - _gen_Nvertex_x)*(_PV_x - _gen_Nvertex_x) + (_PV_y - _gen_Nvertex_y)*(_PV_y - _gen_Nvertex_y) + (_PV_z - _gen_Nvertex_z)*(_PV_z - _gen_Nvertex_z)), event_weight);
        (*hists)["gen_PV-SVdist_xlog"]->Fill(get_PVSVdist_gen(i_gen_l2), event_weight);

        TLorentzVector l2_vector; l2_vector.SetPtEtaPhiE(_gen_lPt[i_gen_l2], _gen_lEta[i_gen_l2], _gen_lPhi[i_gen_l2], _gen_lE[i_gen_l2]);
        TLorentzVector track_vector;
        for(unsigned i = 0; i < _gen_nNPackedDtrs; i++){
            track_vector.SetPtEtaPhiE(_gen_NPackedDtrsPt[i], _gen_NPackedDtrsEta[i], _gen_NPackedDtrsPhi[i], _gen_NPackedDtrsE[i]);                    
            (*hists)["gen_l2_tracks_dR"]->Fill(l2_vector.DeltaR(track_vector), event_weight);
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

void full_analyzer::fill_gen_HNLtagger_tree(HNLtagger& hnltagger_gen, int i_jet)
{
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
