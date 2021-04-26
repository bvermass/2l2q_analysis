////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to PFN and BDT stuff//
////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

std::map<int, std::map<double, double>> full_analyzer::GetJetTagVals(HNLtagger& hnltagger, PFNReader& pfn, int pfn_version){
    std::map<int, std::map<double, double>> values;

    for(auto& MassMap : evaluating_ctaus){
        for(auto& V2Map : MassMap.second){
            values[MassMap.first][V2Map.first] = hnltagger.predict(pfn, pfn_version, MassMap.first, get_truncated_ctau(_is2016, MassMap.first, V2Map.second));
        }
    }
    return values;
}

std::map<int, std::map<double, double>> full_analyzer::GetJetTagVals_LowAndHighMass(HNLtagger& hnltagger, PFNReader& pfn_lowmass, PFNReader& pfn_highmass){
    std::map<int, std::map<double, double>> values;

    double JetTagVal_LowMass = hnltagger.predict_PFN_v8_unparametrized_LowAndHighMass(pfn_lowmass, pfn_highmass, 2.);
    double JetTagVal_HighMass = hnltagger.predict_PFN_v8_unparametrized_LowAndHighMass(pfn_lowmass, pfn_highmass, 10.);
    //if(i_subleading_track == 37) std::cout << "i_subleading_track is still -1! ntracks: " << _IVF_ntracks[i_subleading] << " lFlavor: " << _lFlavor[i_subleading] << " PFN low and high: " << JetTagVal_LowMass << " " << JetTagVal_HighMass <<  std::endl;
    //std::cout << "Low and High Mass PFN value: " << JetTagVal_LowMass << " " << JetTagVal_HighMass << std::endl;
    for(auto& MassMap : evaluating_ctaus){
        for(auto& V2Map : MassMap.second){
            if(MassMap.first < 6.) values[MassMap.first][V2Map.first] = JetTagVal_LowMass;
            else                   values[MassMap.first][V2Map.first] = JetTagVal_HighMass;
        }
    }
    return values;
}

void full_analyzer::add_pfn_histograms(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_JetTagVal"]             = new TH1F(prefix+"_JetTagVal", ";Jet Tag Value; Events", 20, 0, 1);
    (*hists)[prefix+"_JetTagVal_noSR"]        = new TH1F(prefix+"_JetTagVal", ";Jet Tag Value; Events", 20, 0, 1);
    (*hists)[prefix+"_PFN_ROC"]               = new TH1F(prefix+"_PFN_ROC", ";Jet Tag Value; Events", 10000, 0, 1);
    (*hists)[prefix+"_JetTagValzm"]           = new TH1F(prefix+"_JetTagValzm", ";Jet Tag Value; Events", 10, 0.9, 1);
    (*hists)[prefix+"_JetTagValzm2"]          = new TH1F(prefix+"_JetTagValzm2", ";Jet Tag Value; Events", 10, 0.96, 1);
    if(extensive_plots) (*hists)[prefix+"_PFN_JetIsFromHNL_ROC"]  = new TH1F(prefix+"_PFN_JetIsFromHNL_ROC", ";Jet Tag Value (Jet from HNL); Events", 1000, 0, 1);

    //(*hists)[prefix+"_JetTagVal_BDT"]   = new TH1F(prefix+"_JetTagVal_BDT", ";Jet Tag Value (BDT); Events", 40, -0.1, 2);
    //(*hists)[prefix+"_BDT_ROC"]         = new TH1F(prefix+"_BDT_ROC", ";Jet Tag Value (BDT); Events", 1000, -0.1, 2);
    //(*hists)[prefix+"_BDT_JetIsFromHNL_ROC"] = new TH1F(prefix+"_BDT_JetIsFromHNL_ROC", ";Jet Tag Value (Jet from HNL) (BDT); Events", 1000, -0.1, 2);
}

void full_analyzer::Combine_PFN_ROC_flavor_states(std::map<TString, TH1*>* hists){
    for(const auto& it : (*hists)){
        TString name = it.first;
        TH1* h = it.second;
        if(name.Contains("PFN_ROC") and name.Contains("_OS")){
            TString newname = name;
            newname.ReplaceAll("_OS","");
            (*hists)[newname] = (TH1F*)h->Clone(newname);
            name.ReplaceAll("_OS", "_SS");
            (*hists)[newname]->Add((*hists)[name]);
        }
    }
}


void full_analyzer::fill_pfn_histograms(std::map<TString, TH1*>* hists, TString prefix, double mass, double V2, double event_weight){
    (*hists)[prefix+"_JetTagVal"]->Fill(JetTagVal[mass][V2], event_weight);
    if(JetTagVal[mass][V2] < 0.8) (*hists)[prefix+"_JetTagVal_noSR"]->Fill(JetTagVal[mass][V2], event_weight);
    (*hists)[prefix+"_JetTagValzm"]->Fill(JetTagVal[mass][V2], event_weight);
    (*hists)[prefix+"_JetTagValzm2"]->Fill(JetTagVal[mass][V2], event_weight);
    (*hists)[prefix+"_PFN_ROC"]->Fill(JetTagVal[mass][V2], event_weight);
    if(extensive_plots and (isBackground or isData or get_JetIsFromHNL(i_jetl2))) (*hists)[prefix+"_PFN_JetIsFromHNL_ROC"]->Fill(JetTagVal[mass][V2], event_weight);

    //if(JetTagVal_BDT != -1){
    //    (*hists)[prefix+"_JetTagVal_BDT"]->Fill(JetTagVal_BDT, event_weight);
    //    (*hists)[prefix+"_BDT_ROC"]->Fill(JetTagVal_BDT, event_weight);
    //    if(isBackground or isData or get_JetIsFromHNL(i_jetl2)) (*hists)[prefix+"_BDT_JetIsFromHNL_ROC"]->Fill(JetTagVal_BDT, event_weight);
    //}
}
