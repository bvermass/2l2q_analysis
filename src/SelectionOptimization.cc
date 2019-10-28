/////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to selection optimization//
/////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

//void full_analyzer::add_ROC_hists(std::map<TString, TH1*>* hists, TString prefix)
//{
//    (*hists)[prefix+"_SelOpt_l1_MVA_ROC"]   = new TH1F(prefix+"_SelOpt_l1_MVA_ROC", ";l1 MVA; Events", 5, 0.5, 1);
//}
//
//
//void full_analyzer::fill_ROC_hists(std::map<TString, TH1*>* hists, TString prefix, int i_leading)
//{
//    if(_leptonMvatZq[i_leading] > 0.6) (*hists)[prefix+"_SelOpt_l1_MVA_ROC"]->Fill(_leptonMvatZq[i_leading], event_weight);
//    else (*hists)[prefix+"_SelOpt_l1_MVA_ROC"]->Fill(0.51, event_weight);
//}

void full_analyzer::add_Bool_hists(std::map<TString, TH1*>* hists, TString prefix)
{
    (*hists)[prefix+"_Bool_1mu1displmu_PFN"] = new TH1F(prefix+"_Bool_1mu1displmu_PFN", ";1mu1displmu_PFN;Events", 1, 0, 1);
}

void full_analyzer::create_Bools_and_fill_Bool_hists(std::map<TString, TH1*>* hists, TString prefix, int i_leading, int i_subleading)
{
    if(_1mu1displmu_PFN) (*hists)[prefix+"_Bool_1mu1displmu_PFN"]->Fill(1, event_weight);
}
