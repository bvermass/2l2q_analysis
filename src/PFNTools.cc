////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to PFN and BDT stuff//
////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

std::map<int, std::map<double, double>> full_analyzer::GetJetTagVals(HNLtagger& hnltagger, PFNReader& pfn, int pfn_version){
    std::map<int, std::map<double, double>> values;

    for(auto& MassMap : evaluating_ctaus){
        for(auto& V2Map : MassMap.second){
            values[MassMap.first][V2Map.first] = hnltagger.predict(pfn, pfn_version, MassMap.first, V2Map.second);
        }
    }
    return values;
}

void full_analyzer::add_pfn_histograms(std::map<TString, TH1*>* hists, TString prefix){
    for(auto& MassMap : evaluating_ctaus){
        for(auto& V2Map : MassMap.second){
            std::cout << "adding: " << MV2name[MassMap.first][V2Map.first] << std::endl;
            (*hists)[prefix+"_JetTagVal"+MV2name[MassMap.first][V2Map.first]]             = new TH1F(prefix+"_JetTagVal"+MV2name[MassMap.first][V2Map.first], ";Jet Tag Value; Events", 40, 0, 1);
            (*hists)[prefix+"_PFN_ROC"+MV2name[MassMap.first][V2Map.first]]               = new TH1F(prefix+"_PFN_ROC"+MV2name[MassMap.first][V2Map.first], ";Jet Tag Value; Events", 1000, 0, 1);
            (*hists)[prefix+"_PFN_JetIsFromHNL_ROC"+MV2name[MassMap.first][V2Map.first]]  = new TH1F(prefix+"_PFN_JetIsFromHNL_ROC"+MV2name[MassMap.first][V2Map.first], ";Jet Tag Value (Jet from HNL); Events", 1000, 0, 1);
            (*hists)[prefix+"_JetTagValzm"+MV2name[MassMap.first][V2Map.first]]           = new TH1F(prefix+"_JetTagValzm"+MV2name[MassMap.first][V2Map.first], ";Jet Tag Value; Events", 40, 0.9, 1);
            (*hists)[prefix+"_JetTagValzm_10b"+MV2name[MassMap.first][V2Map.first]]       = new TH1F(prefix+"_JetTagValzm_10b"+MV2name[MassMap.first][V2Map.first], ";Jet Tag Value; Events", 10, 0.9, 1);
            (*hists)[prefix+"_SR_JetTagVal"+MV2name[MassMap.first][V2Map.first]]          = new TH1F(prefix+"_SR_JetTagVal"+MV2name[MassMap.first][V2Map.first], ";Jet Tag Value; Events", 40, 0, 1);
            (*hists)[prefix+"_SR_JetTagValzm"+MV2name[MassMap.first][V2Map.first]]        = new TH1F(prefix+"_SR_JetTagValzm"+MV2name[MassMap.first][V2Map.first], ";Jet Tag Value; Events", 40, 0.96, 1);
            (*hists)[prefix+"_SR_ctau"+MV2name[MassMap.first][V2Map.first]]               = new TH1F(prefix+"_SR_ctau"+MV2name[MassMap.first][V2Map.first], ";c#{tau} [mm]; Events", 40, 0, 100);
            (*hists)[prefix+"_SR_PV-SVdxy"+MV2name[MassMap.first][V2Map.first]]           = new TH1F(prefix+"_SR_PV-SVdxy"+MV2name[MassMap.first][V2Map.first], ";PV-SVdxy [cm]; Events", 40, 0, 60);
            (*hists)[prefix+"_SR_PV-SVdxy_zoom"+MV2name[MassMap.first][V2Map.first]]      = new TH1F(prefix+"_SR_PV-SVdxy_zoom"+MV2name[MassMap.first][V2Map.first], ";PV-SVdxy [cm]; Events", 40, 0, 20);
            (*hists)[prefix+"_SR_SVmass"+MV2name[MassMap.first][V2Map.first]]             = new TH1F(prefix+"_SR_SVmass"+MV2name[MassMap.first][V2Map.first], ";SV mass [GeV]; Events", 40, 0, 15);
            (*hists)[prefix+"_SR"+MV2name[MassMap.first][V2Map.first]]                    = new TH1F(prefix+"_SR"+MV2name[MassMap.first][V2Map.first], ";Jet Tag Value; Events", 1, 0, 1);
        }
    }

    //(*hists)[prefix+"_JetTagVal_BDT"]   = new TH1F(prefix+"_JetTagVal_BDT", ";Jet Tag Value (BDT); Events", 40, -0.1, 2);
    //(*hists)[prefix+"_BDT_ROC"]         = new TH1F(prefix+"_BDT_ROC", ";Jet Tag Value (BDT); Events", 1000, -0.1, 2);
    //(*hists)[prefix+"_BDT_JetIsFromHNL_ROC"] = new TH1F(prefix+"_BDT_JetIsFromHNL_ROC", ";Jet Tag Value (Jet from HNL) (BDT); Events", 1000, -0.1, 2);
}


void full_analyzer::fill_pfn_histograms(std::map<TString, TH1*>* hists, TString prefix, double i_subleading){
    for(auto& MassMap : JetTagVal){
        for(auto& V2Map : MassMap.second){
            //std::cout << "tag value: " << MV2name[MassMap.first][V2Map.first] << std::endl;
            if(V2Map.second != -1){
                (*hists)[prefix+"_JetTagVal"+MV2name[MassMap.first][V2Map.first]]->Fill(V2Map.second, event_weight);
                (*hists)[prefix+"_JetTagValzm"+MV2name[MassMap.first][V2Map.first]]->Fill(V2Map.second, event_weight);
                (*hists)[prefix+"_JetTagValzm_10b"+MV2name[MassMap.first][V2Map.first]]->Fill(V2Map.second, event_weight);
                (*hists)[prefix+"_PFN_ROC"+MV2name[MassMap.first][V2Map.first]]->Fill(V2Map.second, event_weight);
                if(sampleflavor == "bkg" or sampleflavor.Index("Run20") != -1 or get_JetIsFromHNL(i_closel2_jet)) (*hists)[prefix+"_PFN_JetIsFromHNL_ROC"+MV2name[MassMap.first][V2Map.first]]->Fill(V2Map.second, event_weight);

                // Signal region stuff, not reweighted
                if(V2Map.second > 0.96){
                    (*hists)[prefix+"_SR_JetTagVal"+MV2name[MassMap.first][V2Map.first]]->Fill(V2Map.second, event_weight);
                    (*hists)[prefix+"_SR_JetTagValzm"+MV2name[MassMap.first][V2Map.first]]->Fill(V2Map.second, event_weight);
                    if(sampleflavor.Index("Run201") == -1) (*hists)[prefix+"_SR_ctau"+MV2name[MassMap.first][V2Map.first]]->Fill(_ctauHN, event_weight);
                    double PVSVdist_2D = get_IVF_PVSVdist_2D(i_subleading);
                    (*hists)[prefix+"_SR_PV-SVdxy"+MV2name[MassMap.first][V2Map.first]]->Fill(PVSVdist_2D, event_weight);
                    (*hists)[prefix+"_SR_PV-SVdxy_zoom"+MV2name[MassMap.first][V2Map.first]]->Fill(PVSVdist_2D, event_weight);
                    (*hists)[prefix+"_SR_SVmass"+MV2name[MassMap.first][V2Map.first]]->Fill(stored_SVmass, event_weight);
                    (*hists)[prefix+"_SR"+MV2name[MassMap.first][V2Map.first]]->Fill(0.5, event_weight);
                }
            }
        }
    }
    //if(JetTagVal_BDT != -1){
    //    (*hists)[prefix+"_JetTagVal_BDT"]->Fill(JetTagVal_BDT, event_weight);
    //    (*hists)[prefix+"_BDT_ROC"]->Fill(JetTagVal_BDT, event_weight);
    //    if(sampleflavor == "bkg" or sampleflavor.Index("Run20") != -1 or get_JetIsFromHNL(i_closel2_jet)) (*hists)[prefix+"_BDT_JetIsFromHNL_ROC"]->Fill(JetTagVal_BDT, event_weight);
    //}
}
