////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to PFN and BDT stuff//
////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

void full_analyzer::add_pfn_histograms(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_JetTagVal"]       = new TH1F(prefix+"_JetTagVal", ";Jet Tag Value; Events", 40, 0, 1);
    (*hists)[prefix+"_PFN_ROC"]         = new TH1F(prefix+"_PFN_ROC", ";Jet Tag Value; Events", 1000, 0, 1);
    (*hists)[prefix+"_PFN_JetIsFromHNL_ROC"] = new TH1F(prefix+"_PFN_JetIsFromHNL_ROC", ";Jet Tag Value (Jet from HNL); Events", 1000, 0, 1);
    (*hists)[prefix+"_JetTagValzm"]       = new TH1F(prefix+"_JetTagValzm", ";Jet Tag Value; Events", 40, 0.9, 1);
}


void full_analyzer::fill_pfn_histograms(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_JetTagVal"]->Fill(JetTagVal, event_weight);
    (*hists)[prefix+"_PFN_ROC"]->Fill(JetTagVal, event_weight);
    if(get_JetIsFromHNL(i_closel2_jet)) (*hists)[prefix+"_PFN_JetIsFromHNL_ROC"]->Fill(JetTagVal, event_weight);
    (*hists)[prefix+"_JetTagValzm"]->Fill(JetTagVal, event_weight);
}
