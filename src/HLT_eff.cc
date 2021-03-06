/////////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to HLT efficiency calculation//
/////////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::init_HLT_efficiency(std::map<TString, TH1*>* hists, TString prefix){
    if(_is2016){
        (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff_den"]            = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff_num"]            = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff_den"]     = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff_num"]     = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff_den"]     = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff_num"]     = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff_den"]            = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff_num"]            = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff_den"]     = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff_num"]     = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff_den"]     = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff_num"]     = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    }else if(_is2017 or _is2018){
        (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_pt_eff_den"]            = new TH1F(prefix+"_HLT_Ele32_WPTight_Gsf_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_pt_eff_num"]            = new TH1F(prefix+"_HLT_Ele32_WPTight_Gsf_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_barrel_pt_eff_den"]     = new TH1F(prefix+"_HLT_Ele32_WPTight_Gsf_barrel_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_barrel_pt_eff_num"]     = new TH1F(prefix+"_HLT_Ele32_WPTight_Gsf_barrel_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_endcap_pt_eff_den"]     = new TH1F(prefix+"_HLT_Ele32_WPTight_Gsf_endcap_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_endcap_pt_eff_num"]     = new TH1F(prefix+"_HLT_Ele32_WPTight_Gsf_endcap_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_IsoMu24_pt_eff_den"]                      = new TH1F(prefix+"_HLT_IsoMu24_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_IsoMu24_pt_eff_num"]                      = new TH1F(prefix+"_HLT_IsoMu24_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_IsoMu24_barrel_pt_eff_den"]               = new TH1F(prefix+"_HLT_IsoMu24_barrel_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_IsoMu24_barrel_pt_eff_num"]               = new TH1F(prefix+"_HLT_IsoMu24_barrel_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_IsoMu24_endcap_pt_eff_den"]               = new TH1F(prefix+"_HLT_IsoMu24_endcap_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
        (*hists)[prefix+"_HLT_IsoMu24_endcap_pt_eff_num"]               = new TH1F(prefix+"_HLT_IsoMu24_endcap_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    }
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

void full_analyzer::fill_HLT_efficiency(std::map<TString, TH1*>* hists, TString prefix, bool _1Ele, bool _1Mu, double event_weight){
    if(!METtriggers()) return;
    if(_is2016){
        if(_1Ele){
            (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);
            if(fabs(_lEta[i_leading]) < 1.2) (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);
            else (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);

            if(_HLT_Ele27_WPTight_Gsf){
                (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
                if(fabs(_lEta[i_leading]) < 1.2) (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
                else (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
            }
        }
        if(_1Mu){
            (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);
            if(fabs(_lEta[i_leading]) < 1.2){
                (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);
            }
            else{
                (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);
            }

            if(_HLT_IsoMu24 or _HLT_IsoTkMu24){
                (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
                if(fabs(_lEta[i_leading]) < 1.2) (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
                else (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
            }
        }
    }else if(_is2017){
        if(_1Ele){
            (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);
            if(fabs(_lEta[i_leading]) < 1.2) (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_barrel_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);
            else (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_endcap_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);

            if(_HLT_Ele32_WPTight_Gsf){
                (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
                if(fabs(_lEta[i_leading]) < 1.2) (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_barrel_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
                else (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_endcap_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
            }
        }
        if(_1Mu){
            (*hists)[prefix+"_HLT_IsoMu24_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);
            if(fabs(_lEta[i_leading]) < 1.2) (*hists)[prefix+"_HLT_IsoMu24_barrel_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);
            else (*hists)[prefix+"_HLT_IsoMu24_endcap_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);

            if(_HLT_IsoMu24 or _HLT_IsoMu27 or _HLT_IsoMu24_eta2p1){
                (*hists)[prefix+"_HLT_IsoMu24_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
                if(fabs(_lEta[i_leading]) < 1.2) (*hists)[prefix+"_HLT_IsoMu24_barrel_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
                else (*hists)[prefix+"_HLT_IsoMu24_endcap_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
            }
        }
    }else if(_is2018){
        if(_1Ele){
            (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);
            if(fabs(_lEta[i_leading]) < 1.2) (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_barrel_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);
            else (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_endcap_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);

            if(_HLT_Ele32_WPTight_Gsf){
                (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
                if(fabs(_lEta[i_leading]) < 1.2) (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_barrel_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
                else (*hists)[prefix+"_HLT_Ele32_WPTight_Gsf_endcap_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
            }
        }
        if(_1Mu){
            (*hists)[prefix+"_HLT_IsoMu24_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);
            if(fabs(_lEta[i_leading]) < 1.2) (*hists)[prefix+"_HLT_IsoMu24_barrel_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);
            else (*hists)[prefix+"_HLT_IsoMu24_endcap_pt_eff_den"]->Fill(_lPt[i_leading], event_weight);

            if(_HLT_IsoMu24){
                (*hists)[prefix+"_HLT_IsoMu24_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
                if(fabs(_lEta[i_leading]) < 1.2) (*hists)[prefix+"_HLT_IsoMu24_barrel_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
                else (*hists)[prefix+"_HLT_IsoMu24_endcap_pt_eff_num"]->Fill(_lPt[i_leading], event_weight);
            }
        }
    }
}

bool full_analyzer::METtriggers(){
    if(_is2016){
        if(_HLT_MET200)                                 return true;
        if(_HLT_PFMET300)                               return true;
        if(_HLT_PFMET170_HBHECleaned)                   return true;
        if(_HLT_PFMET120_PFMHT120_IDTight)              return true;
    }else if(_is2017){
        if(_HLT_PFMET140_PFMHT140_IDTight)              return true;
    }else if(_is2018){
        if(_HLT_PFMET120_PFMHT120_IDTight)              return true;
        if(_HLT_CaloMET350_HBHECleaned)                 return true;
        if(_HLT_PFMET250_HBHECleaned)                   return true;
        if(_HLT_PFMET200_HBHE_BeamHaloCleaned)          return true;
        if(_HLT_PFMETTypeOne140_PFMHT140_IDTight)       return true;
        if(_HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned)   return true;
    }
    return false;
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
