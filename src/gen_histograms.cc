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
    (*hists)["gen_nTrueInteractions"]               = new TH1F("gen_nTrueInteractions", ";N(true interactions);Events", 50, 0, 100);
    (*hists2D)["gen_nTrueInt_vs_nPV"]               = new TH2F("gen_nTrueInt_vs_nPV", ";N(true interactions); nPV", 50, 0, 100, 50, 0, 100);


    //log scale
    double xmin = 0.8;
    double xmax = 300;
    int nbins   = 25;
    double xbins[nbins+1];
    make_logscale(&xbins[0], nbins, xmin, xmax);
}

void full_analyzer::fill_HNL_MC_check(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D)
{
    if(sampleflavor.Index("Run") != -1) return;
    // stuff related to gen Packed Candidates
    // jets containing any particles from HNL
    (*hists)["gen_nTrueInteractions"]->Fill(_nTrueInt, event_weight);
    (*hists2D)["gen_nTrueInt_vs_nPV"]->Fill(_nTrueInt, _nVertex, event_weight);

    if(i_gen_l1 != -1 && i_gen_l2 != -1){
        (*hists2D)["MC_check_gen_l1_l2_charge"]->Fill(_gen_lCharge[i_gen_l1], _gen_lCharge[i_gen_l2], event_weight);
        (*hists)["gen_l1_pt"]->Fill(_gen_lPt[i_gen_l1], event_weight);
        (*hists)["gen_l2_pt"]->Fill(_gen_lPt[i_gen_l2], event_weight);
        (*hists)["gen_l1_flavor"]->Fill(_gen_lFlavor[i_gen_l1], event_weight);
        (*hists)["gen_l2_flavor"]->Fill(_gen_lFlavor[i_gen_l2], event_weight);
    }
}


void full_analyzer::add_gen_histograms(std::map<TString, TH1*>* hists, TString prefix)
{
    if(sampleflavor.Index("Run") != -1) return;
    (*hists)[prefix+"_nTrueInteractions"]               = new TH1F(prefix+"_nTrueInteractions", ";N(true interactions);Events", 50, 0, 100);

    (*hists)[prefix+"_l1_pt_eff_num"]                   = new TH1F(prefix+"_l1_pt_eff_num", ";#it{p}_{T} [GeV];Events", 15, 0, 40);
    (*hists)[prefix+"_l1_pt_eff_den"]                   = new TH1F(prefix+"_l1_pt_eff_den", ";#it{p}_{T} [GeV];Events", 15, 0, 40);
    (*hists)[prefix+"_l2_pt_eff_num"]                   = new TH1F(prefix+"_l2_pt_eff_num", ";#it{p}_{T} [GeV];Events", 15, 0, 40);
    (*hists)[prefix+"_l2_pt_eff_den"]                   = new TH1F(prefix+"_l2_pt_eff_den", ";#it{p}_{T} [GeV];Events", 15, 0, 40);
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
