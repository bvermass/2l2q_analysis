/////////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to HLT efficiency calculation//
/////////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::init_HLT_efficiency(std::map<TString, TH1*>* hists){
    (*hists)["HLT_1_iso_e_pt"]               = new TH1F("HLT_1_iso_e_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)["HLT_Ele27_WPTight_Gsf_pt"]   = new TH1F("HLT_Ele27_WPTight_Gsf_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)["HLT_Ele27_WPTight_Gsf_pt_eff"]   = new TH1F("HLT_Ele27_WPTight_Gsf_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    (*hists)["HLT_1_iso_e_barrel_pt"]               = new TH1F("HLT_1_iso_e_barrel_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)["HLT_Ele27_WPTight_Gsf_barrel_pt"]   = new TH1F("HLT_Ele27_WPTight_Gsf_barrel_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)["HLT_Ele27_WPTight_Gsf_barrel_pt_eff"]   = new TH1F("HLT_Ele27_WPTight_Gsf_barrel_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    (*hists)["HLT_1_iso_e_endcap_pt"]               = new TH1F("HLT_1_iso_e_endcap_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)["HLT_Ele27_WPTight_Gsf_endcap_pt"]   = new TH1F("HLT_Ele27_WPTight_Gsf_endcap_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)["HLT_Ele27_WPTight_Gsf_endcap_pt_eff"]   = new TH1F("HLT_Ele27_WPTight_Gsf_endcap_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    (*hists)["HLT_1_iso_mu_pt"]               = new TH1F("HLT_1_iso_mu_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)["HLT_IsoMu24_IsoTkMu24_pt"]   = new TH1F("HLT_IsoMu24_IsoTkMu24_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)["HLT_IsoMu24_IsoTkMu24_pt_eff"]   = new TH1F("HLT_IsoMu24_IsoTkMu24_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    (*hists)["HLT_1_iso_mu_barrel_pt"]               = new TH1F("HLT_1_iso_mu_barrel_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)["HLT_IsoMu24_IsoTkMu24_barrel_pt"]   = new TH1F("HLT_IsoMu24_IsoTkMu24_barrel_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)["HLT_IsoMu24_IsoTkMu24_barrel_pt_eff"]   = new TH1F("HLT_IsoMu24_IsoTkMu24_barrel_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    (*hists)["HLT_1_iso_mu_endcap_pt"]               = new TH1F("HLT_1_iso_mu_endcap_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)["HLT_IsoMu24_IsoTkMu24_endcap_pt"]   = new TH1F("HLT_IsoMu24_IsoTkMu24_endcap_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)["HLT_IsoMu24_IsoTkMu24_endcap_pt_eff"]   = new TH1F("HLT_IsoMu24_IsoTkMu24_endcap_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
}

void full_analyzer::fill_HLT_efficiency(std::map<TString, TH1*>* hists, bool _1e, bool _1mu){
        if(_1e){
            (*hists)["HLT_1_iso_e_pt"]->Fill(_lPt[i_leading_e], event_weight);
            if(fabs(_lEta[i_leading_e]) < 1.2) (*hists)["HLT_1_iso_e_barrel_pt"]->Fill(_lPt[i_leading_e], event_weight);
            else (*hists)["HLT_1_iso_e_endcap_pt"]->Fill(_lPt[i_leading_e], event_weight);
            
            if(_HLT_Ele27_WPTight_Gsf){ 
                (*hists)["HLT_Ele27_WPTight_Gsf_pt"]->Fill(_lPt[i_leading_e], event_weight);
                if(fabs(_lEta[i_leading_e]) < 1.2) (*hists)["HLT_Ele27_WPTight_Gsf_barrel_pt"]->Fill(_lPt[i_leading_e], event_weight);
                else (*hists)["HLT_Ele27_WPTight_Gsf_endcap_pt"]->Fill(_lPt[i_leading_e], event_weight);
                
                (*hists)["HLT_Ele27_WPTight_Gsf_pt_eff"]->Fill(_lPt[i_leading_e], event_weight);
                if(fabs(_lEta[i_leading_e]) < 1.2) (*hists)["HLT_Ele27_WPTight_Gsf_barrel_pt_eff"]->Fill(_lPt[i_leading_e], event_weight);
                else (*hists)["HLT_Ele27_WPTight_Gsf_endcap_pt_eff"]->Fill(_lPt[i_leading_e], event_weight);
            }

        }
        if(_1mu){
            (*hists)["HLT_1_iso_mu_pt"]->Fill(_lPt[i_leading_mu], event_weight);
            if(fabs(_lEta[i_leading_mu]) < 1.2) (*hists)["HLT_1_iso_mu_barrel_pt"]->Fill(_lPt[i_leading_mu], event_weight);
            else (*hists)["HLT_1_iso_mu_endcap_pt"]->Fill(_lPt[i_leading_mu], event_weight);
            
            if(_HLT_IsoMu24 or _HLT_IsoTkMu24){ 
                (*hists)["HLT_IsoMu24_IsoTkMu24_pt"]->Fill(_lPt[i_leading_mu], event_weight);
                if(fabs(_lEta[i_leading_mu]) < 1.2) (*hists)["HLT_IsoMu24_IsoTkMu24_barrel_pt"]->Fill(_lPt[i_leading_mu], event_weight);
                else (*hists)["HLT_IsoMu24_IsoTkMu24_endcap_pt"]->Fill(_lPt[i_leading_mu], event_weight);
                
                (*hists)["HLT_IsoMu24_IsoTkMu24_pt_eff"]->Fill(_lPt[i_leading_mu], event_weight);
                if(fabs(_lEta[i_leading_mu]) < 1.2) (*hists)["HLT_IsoMu24_IsoTkMu24_barrel_pt_eff"]->Fill(_lPt[i_leading_mu], event_weight);
                else (*hists)["HLT_IsoMu24_IsoTkMu24_endcap_pt_eff"]->Fill(_lPt[i_leading_mu], event_weight);
            }
        }
}
