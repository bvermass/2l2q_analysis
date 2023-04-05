//Part of mini_analyzer framework dealing with JEC and JER variations
#include "../interface/mini_analyzer.h"

std::map<TString, TH1*> mini_analyzer::get_hists_JECvariations(TString base_filename)
{
    std::vector<TString> JECvars = {"JECDown", "JECUp", "JERDown", "JERUp"};
    std::map<TString, TH1*> hists_JEC;

    for(const auto& JECvar : JECvars){
        TString JECvarsys = JECvar;
        JECvarsys.ReplaceAll("Down", "_sysDown").ReplaceAll("Up", "_sysUp");
        std::cout << "Running " << JECvar << " variation" << std::endl;
        add_histograms_JEC(&hists_JEC, JECvarsys);
        run_JECvariation(&hists_JEC, JECvar, JECvarsys, base_filename);
    }
    return hists_JEC;
}

void mini_analyzer::add_histograms_JEC(std::map<TString, TH1*>* hists_JEC, TString JECvar)
{
    for(const TString& lep_region : {"_mm", "_ee", "_me", "_em", "_2l"}){
        for(const auto& MV2 : MV2tags){
            TString MV2tag = MV2.first;
            for(const TString& cut2region : {"_cutTightmlSV"}){
                add_Shape_SR_histograms_JEC(hists_JEC, lep_region + MV2tag + cut2region + "_quadA_" + JECvar);
            }
        }
    }
}

void mini_analyzer::add_Shape_SR_histograms_JEC(std::map<TString, TH1*>* hists_JEC, TString prefix)
{
    if(prefix.Contains("_mm") or prefix.Contains("_ee") or prefix.Contains("_em") or prefix.Contains("_me")){
        for(const TString& weighted : {""}){
            TString Shape_SRname    = prefix+"_Shape_SR"+weighted;
            TString Shape_alphaname = prefix+"_Shape_alpha"+weighted;
            (*hists_JEC)[Shape_SRname]     = new TH1F(Shape_SRname, ";#Delta (PV-SV)_{2D} [cm];Events", 12, 0, 12);
            (*hists_JEC)[Shape_alphaname]  = new TH1F(Shape_alphaname, ";#Delta (PV-SV)_{2D} [cm];Events", 6, 0, 6);

            std::vector<TString> binnames;
            if(prefix.Contains("_M-1_") or prefix.Contains("_M-2_") or prefix.Contains("_M-3_") or prefix.Contains("_M-4_") or prefix.Contains("_M-5_")){
                binnames = {"0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10"};
            }else if(prefix.Contains("_M-6_") or prefix.Contains("_M-8_") or prefix.Contains("_M-10_") or prefix.Contains("_M-12_") or prefix.Contains("_M-14_")){
                binnames = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
            }
            for(unsigned i = 1; i <= binnames.size(); ++i){
                (*hists_JEC)[Shape_SRname]->GetXaxis()->SetBinLabel(i, binnames[i-1]);
                if(i < 7) (*hists_JEC)[Shape_alphaname]->GetXaxis()->SetBinLabel(i, binnames[i-1]);
            }
            (*hists_JEC)[Shape_SRname]->SetCanExtend(false);
            (*hists_JEC)[Shape_alphaname]->SetCanExtend(false);
        }
    }
    else if(prefix.Contains("_2l")){
        (*hists_JEC)[prefix+"_Shape_SR"]       = new TH1F(prefix+"_Shape_SR", ";#Delta (PV-SV)_{2D} [cm];Events", 48, 0, 48);
    }
}

void mini_analyzer::run_JECvariation(std::map<TString, TH1*>* hists_JEC, TString JECvar, TString JECvarsys, TString base_filename)
{
    //get the name, change
    //JECDown/BkgEstimator_JECDown_
    base_filename.ReplaceAll("BkgEstimator_", JECvar+"/BkgEstimator_"+JECvar+"_");
    BkgEstimator eventJEC(base_filename);
    Long64_t nentriesJEC = event.BkgEstimator_tree->GetEntries();
    for(unsigned jentryJEC = 0; jentryJEC < nentriesJEC; jentryJEC++){
        eventJEC.BkgEstimator_tree->GetEntry(jentryJEC);

        std::vector<TString> JECtags = set_signal_regions_JEC(eventJEC, JECvarsys);
        TString sr_flavor_JEC = get_sr_flavor(eventJEC);

        fill_histograms_JEC(eventJEC, hists_JEC, JECtags, sr_flavor_JEC);
    }
}

std::vector<TString> mini_analyzer::set_signal_regions_JEC(BkgEstimator& eventJEC, TString JECvarsys)
{
    std::vector<TString> JECtags;
    bool baseline_cutmlSV_JEC = eventJEC._SV_l1mass > 10 &&
                                eventJEC._nTightLep == 1 &&
                                eventJEC._nTightJet <= 1;

    for(auto const& MV2 : MV2tags){
        TString MV2tag = MV2.first;
        int i_MV2      = get_PFNevaluation_index(eventJEC._evaluating_mass[MV2.second], eventJEC._lFlavor);
        double PFNcut  = get_NTightPFNcut(eventJEC._evaluating_mass[MV2.second], eventJEC._l1Flavor, eventJEC._lFlavor, eventJEC._l1Charge, eventJEC._lCharge, eventJEC._SV_mass, eventJEC._SV_PVSVdist_2D, eventJEC._l1Charge != eventJEC._lCharge, eventJEC._is2016, eventJEC._is2017);

        if(baseline_cutmlSV_JEC){
            if(eventJEC._SV_l1mass > 50 and eventJEC._SV_l1mass < 85){
                if(eventJEC._JetTagVal[i_MV2] > PFNcut) JECtags.push_back(MV2tag + "_cutTightmlSV_quadA_" + JECvarsys);
            }
        }
    }
    return JECtags;
}

TString mini_analyzer::get_sr_flavor(BkgEstimator& eventJEC)
{
    // Determine sr_flavor
    TString srflavor = "";
    if(eventJEC._l1Charge == eventJEC._lCharge) srflavor += "_SS";
    else srflavor += "_OS";

    if(eventJEC._l1Flavor == 0) srflavor += "_e";
    else if(eventJEC._l1Flavor == 1) srflavor += "_m";

    if(eventJEC._lFlavor == 0) srflavor += "e";
    else if(eventJEC._lFlavor == 1) srflavor += "m";
    return srflavor;
}

void mini_analyzer::fill_histograms_JEC(BkgEstimator& eventJEC, std::map<TString, TH1*>* hists_JEC, std::vector<TString> JECtags, TString sr_flavor_JEC)
{
    for(const auto& JECtag : JECtags){
        TString mv2tag = JECtag(0,JECtag.Index("_cut"));
        unsigned i_JetTagVal_JEC = MV2tags[mv2tag];
        fill_Shape_SR_histograms_JEC(eventJEC, hists_JEC, sr_flavor_JEC, JECtag, event._weight * event._reweighting_weight[i_JetTagVal_JEC]);
    }
}

void mini_analyzer::fill_Shape_SR_histograms_JEC(BkgEstimator& eventJEC, std::map<TString, TH1*>* hists_JEC, TString sr_flavor_JEC, TString JECtag, double event_weight)
{
    double SRShape2bin = get_SRShape3bin(eventJEC._SV_PVSVdist_2D, eventJEC._SV_mass, JECtag, sr_flavor);//gives 0,1,2,3,4,5 based on L_xy and SVmass
    double SRShape2bin_OSSS = SRShape2bin;
    if(sr_flavor_JEC.Contains("_SS")) SRShape2bin += 6.;

    TString fl;
    if(sr_flavor_JEC.Contains("_mm")) fl = "_mm";
    if(sr_flavor_JEC.Contains("_ee")) fl = "_ee";
    if(sr_flavor_JEC.Contains("_me")) fl = "_me";
    if(sr_flavor_JEC.Contains("_em")) fl = "_em";

        
    (*hists_JEC)[fl + JECtag + "_Shape_SR"]->Fill(SRShape2bin, event_weight);
    (*hists_JEC)[fl + JECtag + "_Shape_alpha"]->Fill(SRShape2bin_OSSS, event_weight);
    //(*hists_JEC)[fl + JECtag + "_Shape_SR_unw"]->Fill(SRShape2bin);
    //(*hists_JEC)[fl + JECtag + "_Shape_alpha_unw"]->Fill(SRShape2bin_OSSS);


    double _2lbin = 0.;
    if(sr_flavor_JEC.Contains("_em"))      _2lbin += 12.;
    else if(sr_flavor_JEC.Contains("_ee")) _2lbin += 24.;
    else if(sr_flavor_JEC.Contains("_me")) _2lbin += 36.;
    (*hists_JEC)["_2l" + JECtag + "_Shape_SR"]->Fill(SRShape2bin + _2lbin, event_weight);
}

void mini_analyzer::set_correct_sysUp_sysDown(std::map<TString, TH1*>* hists_JEC, std::vector<TString> syslabels)
{
    //for each sysDown Shape_SR histogram in hists_JEC, get corresponding sysUp and nominal(from hists).
    //go over each bin, make sure Down is the lowest value, Up is highest value, if both are lower than nominal then Up should be nominal value, if both are higher than nominal then Down should be nominal value
    for(const auto& h : (*hists_JEC)){
        TString name_sysDown = h.first;
        if(!name_sysDown.Contains("_sysDown")) continue;
        TString name_sysUp = name_sysDown;
        name_sysUp.ReplaceAll("_sysDown", "_sysUp");
        TString name_nominal = name_sysDown;
        name_nominal.ReplaceAll("_sysDown", "");
        for(const auto& syslabel : syslabels) name_nominal.ReplaceAll(syslabel, "");
        for(int i = 1; i <= h.second->GetNbinsX(); i++){
            double bc_sysDown = h.second->GetBinContent(i);
            double bc_sysUp = (*hists_JEC)[name_sysUp]->GetBinContent(i);
            double bc_nominal = hists[name_nominal]->GetBinContent(i);
            double bc_sysUp_max = std::max(std::max(bc_sysUp, bc_sysDown), bc_nominal);
            double bc_sysDown_min = std::min(std::min(bc_sysUp, bc_sysDown), bc_nominal);
            h.second->SetBinContent(i, bc_sysDown_min);
            (*hists_JEC)[name_sysUp]->SetBinContent(i, bc_sysUp_max);
        }
    }
}
