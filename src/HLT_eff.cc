/////////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to HLT efficiency calculation//
/////////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::init_HLT_efficiency(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_Trigger_e_ee_pt_eff_den"]            = new TH1F(prefix+"_Trigger_e_ee_pt_eff_den", ";#it{p}_{T}^{leading} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_e_ee_pt_eff_num"]            = new TH1F(prefix+"_Trigger_e_ee_pt_eff_num", ";#it{p}_{T}^{leading} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_ee_pt_eff_den"]              = new TH1F(prefix+"_Trigger_ee_pt_eff_den", ";#it{p}_{T}^{leading} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_ee_pt_eff_num"]              = new TH1F(prefix+"_Trigger_ee_pt_eff_num", ";#it{p}_{T}^{leading} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_m_mm_pt_eff_den"]            = new TH1F(prefix+"_Trigger_m_mm_pt_eff_den", ";#it{p}_{T}^{leading} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_m_mm_pt_eff_num"]            = new TH1F(prefix+"_Trigger_m_mm_pt_eff_num", ";#it{p}_{T}^{leading} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_mm_pt_eff_den"]              = new TH1F(prefix+"_Trigger_mm_pt_eff_den", ";#it{p}_{T}^{leading} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_mm_pt_eff_num"]              = new TH1F(prefix+"_Trigger_mm_pt_eff_num", ";#it{p}_{T}^{leading} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_e_ee_pt2_eff_den"]            = new TH1F(prefix+"_Trigger_e_ee_pt2_eff_den", ";#it{p}_{T}^{trailing} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_e_ee_pt2_eff_num"]            = new TH1F(prefix+"_Trigger_e_ee_pt2_eff_num", ";#it{p}_{T}^{trailing} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_ee_pt2_eff_den"]              = new TH1F(prefix+"_Trigger_ee_pt2_eff_den", ";#it{p}_{T}^{trailing} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_ee_pt2_eff_num"]              = new TH1F(prefix+"_Trigger_ee_pt2_eff_num", ";#it{p}_{T}^{trailing} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_m_mm_pt2_eff_den"]            = new TH1F(prefix+"_Trigger_m_mm_pt2_eff_den", ";#it{p}_{T}^{trailing} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_m_mm_pt2_eff_num"]            = new TH1F(prefix+"_Trigger_m_mm_pt2_eff_num", ";#it{p}_{T}^{trailing} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_mm_pt2_eff_den"]              = new TH1F(prefix+"_Trigger_mm_pt2_eff_den", ";#it{p}_{T}^{trailing} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_Trigger_mm_pt2_eff_num"]              = new TH1F(prefix+"_Trigger_mm_pt2_eff_num", ";#it{p}_{T}^{trailing} [GeV];Events", 100, 0, 200);
}

void full_analyzer::init_HLT_allevents_efficiency(std::map<TString, TH1*>* hists, TString prefix){
    if(isData) return;
    (*hists)[prefix+"_HLT_e_allevents_eff_den"]                        = new TH1F(prefix+"_HLT_e_allevents_eff_den", ";#it{p}_{T} [GeV];Events", 60, 0, 150);
    (*hists)[prefix+"_HLT_e_allevents_eff_num"]                        = new TH1F(prefix+"_HLT_e_allevents_eff_num", ";#it{p}_{T} [GeV];Events", 60, 0, 150);
    (*hists)[prefix+"_HLT_mu_allevents_eff_den"]                       = new TH1F(prefix+"_HLT_mu_allevents_eff_den", ";#it{p}_{T} [GeV];Events", 60, 0, 150);
    (*hists)[prefix+"_HLT_mu_allevents_eff_num"]                       = new TH1F(prefix+"_HLT_mu_allevents_eff_num", ";#it{p}_{T} [GeV];Events", 60, 0, 150);
    (*hists)[prefix+"_HLT_allevents_eff_den"]                          = new TH1F(prefix+"_HLT_allevents_eff_den", ";ee eff. and #mu#mu eff.;Events", 2, 0, 2);
    (*hists)[prefix+"_HLT_allevents_eff_num"]                          = new TH1F(prefix+"_HLT_allevents_eff_num", ";ee eff. and #mu#mu eff.;Events", 2, 0, 2);
}

void full_analyzer::fill_HLT_efficiency(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_Trigger_e_ee_pt_eff_den"]->Fill(_lPt[i_leading]);
    (*hists)[prefix+"_Trigger_ee_pt_eff_den"]->Fill(_lPt[i_leading]);
    (*hists)[prefix+"_Trigger_m_mm_pt_eff_den"]->Fill(_lPt[i_leading]);
    (*hists)[prefix+"_Trigger_mm_pt_eff_den"]->Fill(_lPt[i_leading]);
    (*hists)[prefix+"_Trigger_e_ee_pt2_eff_den"]->Fill(_lPt[i_leading]);
    (*hists)[prefix+"_Trigger_ee_pt2_eff_den"]->Fill(_lPt[i_leading]);
    (*hists)[prefix+"_Trigger_m_mm_pt2_eff_den"]->Fill(_lPt[i_leading]);
    (*hists)[prefix+"_Trigger_mm_pt2_eff_den"]->Fill(_lPt[i_leading]);

    if(_passTrigger_ee){
        (*hists)[prefix+"_Trigger_ee_pt_eff_num"]->Fill(_lPt[i_leading]);
        (*hists)[prefix+"_Trigger_ee_pt2_eff_num"]->Fill(_lPt[i_subleading]);
    }
    if(_passTrigger_ee or _passTrigger_e){
        (*hists)[prefix+"_Trigger_e_ee_pt_eff_num"]->Fill(_lPt[i_leading]);
        (*hists)[prefix+"_Trigger_e_ee_pt2_eff_num"]->Fill(_lPt[i_subleading]);
    }

    if(_passTrigger_mm){
        (*hists)[prefix+"_Trigger_mm_pt_eff_num"]->Fill(_lPt[i_leading]);
        (*hists)[prefix+"_Trigger_mm_pt2_eff_num"]->Fill(_lPt[i_subleading]);
    }
    if(_passTrigger_mm or _passTrigger_m){
        (*hists)[prefix+"_Trigger_m_mm_pt_eff_num"]->Fill(_lPt[i_leading]);
        (*hists)[prefix+"_Trigger_m_mm_pt2_eff_num"]->Fill(_lPt[i_subleading]);
    }
}

void full_analyzer::fill_HLT_allevents_efficiency(std::map<TString, TH1*>* hists, TString prefix){
    if(isData) return;
    if(_gen_nL == 0) return;

    (*hists)[prefix+"_HLT_e_allevents_eff_den"]->Fill(_gen_lPt[0]);
    (*hists)[prefix+"_HLT_allevents_eff_den"]->Fill(0.);
    if(_HLT_Ele27_WPTight_Gsf){
        (*hists)[prefix+"_HLT_e_allevents_eff_num"]->Fill(_gen_lPt[0]);
        (*hists)[prefix+"_HLT_allevents_eff_num"]->Fill(0.);
    }

    (*hists)[prefix+"_HLT_mu_allevents_eff_den"]->Fill(_gen_lPt[0]);
    (*hists)[prefix+"_HLT_allevents_eff_den"]->Fill(1.);
    if(_HLT_IsoMu24 or _HLT_IsoTkMu24){
        (*hists)[prefix+"_HLT_mu_allevents_eff_num"]->Fill(_gen_lPt[0]);
        (*hists)[prefix+"_HLT_allevents_eff_num"]->Fill(1.);
    }
}
