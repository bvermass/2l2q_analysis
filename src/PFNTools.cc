////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to PFN and BDT stuff//
////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

std::map<int, std::map<double, double>> full_analyzer::GetJetTagVals(HNLtagger& hnltagger, PFNReader& pfn, int pfn_version){
    std::map<int, std::map<double, double>> values;

    for(auto& MassMap : evaluating_ctaus){
        for(auto& CouplingMap : MassMap.second){
            values[MassMap.first][CouplingMap.first] = hnltagger.predict(pfn, pfn_version, MassMap.first, CouplingMap.second);
        }
    }
    return values;
}

void full_analyzer::add_pfn_histograms(std::map<TString, TH1*>* hists, TString prefix){
    for(auto& MassMap : evaluating_ctaus){
        for(auto& CouplingMap : MassMap.second){
            std::ostringstream V2stream;
            V2stream << CouplingMap.first;
            TString param = "_M-" + std::to_string(MassMap.first) + "_V2-" + V2stream.str();
            std::cout << "adding: " << param << std::endl;
            (*hists)[prefix+"_JetTagVal"+param]             = new TH1F(prefix+"_JetTagVal"+param, ";Jet Tag Value; Events", 40, 0, 1);
            (*hists)[prefix+"_PFN_ROC"+param]               = new TH1F(prefix+"_PFN_ROC"+param, ";Jet Tag Value; Events", 1000, 0, 1);
            (*hists)[prefix+"_PFN_JetIsFromHNL_ROC"+param]  = new TH1F(prefix+"_PFN_JetIsFromHNL_ROC"+param, ";Jet Tag Value (Jet from HNL); Events", 1000, 0, 1);
            (*hists)[prefix+"_JetTagValzm"+param]           = new TH1F(prefix+"_JetTagValzm"+param, ";Jet Tag Value; Events", 40, 0.9, 1);
            (*hists)[prefix+"_JetTagValzm_10b"+param]       = new TH1F(prefix+"_JetTagValzm_10b"+param, ";Jet Tag Value; Events", 10, 0.9, 1);
        }
    }

    //(*hists)[prefix+"_JetTagVal_BDT"]   = new TH1F(prefix+"_JetTagVal_BDT", ";Jet Tag Value (BDT); Events", 40, -0.1, 2);
    //(*hists)[prefix+"_BDT_ROC"]         = new TH1F(prefix+"_BDT_ROC", ";Jet Tag Value (BDT); Events", 1000, -0.1, 2);
    //(*hists)[prefix+"_BDT_JetIsFromHNL_ROC"] = new TH1F(prefix+"_BDT_JetIsFromHNL_ROC", ";Jet Tag Value (Jet from HNL) (BDT); Events", 1000, -0.1, 2);
}


void full_analyzer::fill_pfn_histograms(std::map<TString, TH1*>* hists, TString prefix){
    for(auto& MassMap : JetTagVal){
        for(auto& CouplingMap : MassMap.second){
            std::ostringstream V2stream;
            V2stream << CouplingMap.first;
            TString param = "_M-" + std::to_string(MassMap.first) + "_V2-" + V2stream.str();
            //std::cout << "tag value: " << param << std::endl;
            if(CouplingMap.second != -1){
                (*hists)[prefix+"_JetTagVal"+param]->Fill(CouplingMap.second, event_weight);
                (*hists)[prefix+"_JetTagValzm"+param]->Fill(CouplingMap.second, event_weight);
                (*hists)[prefix+"_JetTagValzm_10b"+param]->Fill(CouplingMap.second, event_weight);
                (*hists)[prefix+"_PFN_ROC"+param]->Fill(CouplingMap.second, event_weight);
                if(sampleflavor == "bkg" or sampleflavor.Index("Run20") != -1 or get_JetIsFromHNL(i_closel2_jet)) (*hists)[prefix+"_PFN_JetIsFromHNL_ROC"+param]->Fill(CouplingMap.second, event_weight);
            }
        }
    }
    //if(JetTagVal_BDT != -1){
    //    (*hists)[prefix+"_JetTagVal_BDT"]->Fill(JetTagVal_BDT, event_weight);
    //    (*hists)[prefix+"_BDT_ROC"]->Fill(JetTagVal_BDT, event_weight);
    //    if(sampleflavor == "bkg" or sampleflavor.Index("Run20") != -1 or get_JetIsFromHNL(i_closel2_jet)) (*hists)[prefix+"_BDT_JetIsFromHNL_ROC"]->Fill(JetTagVal_BDT, event_weight);
    //}
}
