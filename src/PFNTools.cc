////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to PFN and BDT stuff//
////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

void full_analyzer::add_pfn_histograms(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_JetTagVal"]       = new TH1F(prefix+"_JetTagVal", ";Jet Tag Value; Events", 40, 0, 1);
    (*hists)[prefix+"_JetTagVal_BDT"]   = new TH1F(prefix+"_JetTagVal_BDT", ";Jet Tag Value (BDT); Events", 40, -0.1, 2);
    (*hists)[prefix+"_PFN_ROC"]         = new TH1F(prefix+"_PFN_ROC", ";Jet Tag Value; Events", 1000, 0, 1);
    (*hists)[prefix+"_BDT_ROC"]         = new TH1F(prefix+"_BDT_ROC", ";Jet Tag Value (BDT); Events", 1000, -0.1, 2);
    (*hists)[prefix+"_PFN_JetIsFromHNL_ROC"] = new TH1F(prefix+"_PFN_JetIsFromHNL_ROC", ";Jet Tag Value (Jet from HNL); Events", 1000, 0, 1);
    (*hists)[prefix+"_BDT_JetIsFromHNL_ROC"] = new TH1F(prefix+"_BDT_JetIsFromHNL_ROC", ";Jet Tag Value (Jet from HNL) (BDT); Events", 1000, -0.1, 2);
    (*hists)[prefix+"_JetTagValzm"]       = new TH1F(prefix+"_JetTagValzm", ";Jet Tag Value; Events", 40, 0.9, 1);
}


void full_analyzer::fill_pfn_histograms(std::map<TString, TH1*>* hists, TString prefix){
    if(JetTagVal != -1){
        (*hists)[prefix+"_JetTagVal"]->Fill(JetTagVal, event_weight);
        (*hists)[prefix+"_JetTagValzm"]->Fill(JetTagVal, event_weight);
        (*hists)[prefix+"_PFN_ROC"]->Fill(JetTagVal, event_weight);
        if(sampleflavor == "bkg" or sampleflavor.Index("Run20") != -1 or get_JetIsFromHNL(i_closel2_jet)) (*hists)[prefix+"_PFN_JetIsFromHNL_ROC"]->Fill(JetTagVal, event_weight);
    }
    if(JetTagVal_BDT != -1){
        (*hists)[prefix+"_JetTagVal_BDT"]->Fill(JetTagVal_BDT, event_weight);
        (*hists)[prefix+"_BDT_ROC"]->Fill(JetTagVal_BDT, event_weight);
        if(sampleflavor == "bkg" or sampleflavor.Index("Run20") != -1 or get_JetIsFromHNL(i_closel2_jet)) (*hists)[prefix+"_BDT_JetIsFromHNL_ROC"]->Fill(JetTagVal_BDT, event_weight);
    }
}
