/////////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to HLT efficiency calculation//
/////////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::init_HLT_efficiency(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff_den"]            = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff_num"]            = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff"]                = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff_den"]     = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff_num"]     = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff"]         = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff_den"]     = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff_num"]     = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff"]         = new TH1F(prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff_den"]            = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff_num"]            = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff"]                = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff_den"]     = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff_num"]     = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff"]         = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff_den"]     = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff_den", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff_num"]     = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff_num", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff"]         = new TH1F(prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
}

void full_analyzer::fill_HLT_efficiency(std::map<TString, TH1*>* hists, TString prefix, bool _1Ele, bool _1Mu){
        if(_1Ele){
            (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff_den"]->Fill(_lPt[i_leading_e], event_weight);
            if(fabs(_lEta[i_leading_e]) < 1.2) (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff_den"]->Fill(_lPt[i_leading_e], event_weight);
            else (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff_den"]->Fill(_lPt[i_leading_e], event_weight);
            
            if(_HLT_Ele27_WPTight_Gsf){ 
                (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff_num"]->Fill(_lPt[i_leading_e], event_weight);
                if(fabs(_lEta[i_leading_e]) < 1.2) (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff_num"]->Fill(_lPt[i_leading_e], event_weight);
                else (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff_num"]->Fill(_lPt[i_leading_e], event_weight);
                
                (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff"]->Fill(_lPt[i_leading_e], event_weight);
                if(fabs(_lEta[i_leading_e]) < 1.2) (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff"]->Fill(_lPt[i_leading_e], event_weight);
                else (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff"]->Fill(_lPt[i_leading_e], event_weight);
            }

        }
        if(_1Mu){
            (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff_den"]->Fill(_lPt[i_leading_mu], event_weight);
            if(fabs(_lEta[i_leading_mu]) < 1.2) (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff_den"]->Fill(_lPt[i_leading_mu], event_weight);
            else (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff_den"]->Fill(_lPt[i_leading_mu], event_weight);
            
            if(_HLT_IsoMu24 or _HLT_IsoTkMu24){ 
                (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff_num"]->Fill(_lPt[i_leading_mu], event_weight);
                if(fabs(_lEta[i_leading_mu]) < 1.2) (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff_num"]->Fill(_lPt[i_leading_mu], event_weight);
                else (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff_num"]->Fill(_lPt[i_leading_mu], event_weight);
                
                (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff"]->Fill(_lPt[i_leading_mu], event_weight);
                if(fabs(_lEta[i_leading_mu]) < 1.2) (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff"]->Fill(_lPt[i_leading_mu], event_weight);
                else (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff"]->Fill(_lPt[i_leading_mu], event_weight);
            }
        }
}

void full_analyzer::divide_for_eff_HLT(std::map<TString, TH1*>* hists, TString prefix)
{
    (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff"]->Divide((*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_pt_eff_den"]);
    (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff"]->Divide((*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_barrel_pt_eff_den"]);
    (*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff"]->Divide((*hists)[prefix+"_HLT_Ele27_WPTight_Gsf_endcap_pt_eff_den"]);
    (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff"]->Divide((*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_pt_eff_den"]);
    (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff"]->Divide((*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_barrel_pt_eff_den"]);
    (*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff"]->Divide((*hists)[prefix+"_HLT_IsoMu24_IsoTkMu24_endcap_pt_eff_den"]);
}
