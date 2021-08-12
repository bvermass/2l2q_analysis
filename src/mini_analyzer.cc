//Include header for this class
#include "../interface/mini_analyzer.h"

mini_analyzer::mini_analyzer(TString filename) :
    event(filename),
    isData(filename.Contains("Run201") or filename.Contains("SingleLepton")),
    isSignal(filename.Contains("HeavyNeutrino_lljj_"))
{
    TH1::AddDirectory(kFALSE);//https://root.cern.ch/input-and-output
    event.BkgEstimator_tree->GetEntry(0);
    init_MV2_parametrization();
    init_CP();
    init_variations();
    add_histograms();
    //add_histograms_gridscan();
    std::cout << "number of histograms: " << hists.size() << std::endl;
    std::cout << "number of MV2tags: " << MV2tags.size() << std::endl;
}

mini_analyzer::~mini_analyzer()
{}

double get_MediumPFNcut(int mass, unsigned flavor, bool is2016, bool is2017)
{
    if(flavor == 0){//electron
        if(is2016){
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }else if(is2017){
            if(mass <= 5)   return 0.9;//0.98 had almost 0 predicted events
            else            return 0.9;//0.97 had almost 0 predicted events
        }else {
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }
    }else {//muon
        if(is2016){
            if(mass <= 5)   return 0.96;
            else            return 0.96;
        }else if(is2017){
            if(mass <= 5)   return 0.96;
            else            return 0.96;
        }else {
            if(mass <= 5)   return 0.96;
            else            return 0.96;
        }
    }
}

double get_looserPFNcut(int mass, unsigned flavor, bool is2016, bool is2017)
{
    if(flavor == 0){//electron
        if(is2016){
            if(mass <= 5)   return 0.96;
            else            return 0.97;
        }else if(is2017){
            if(mass <= 5)   return 0.95;//0.98 had almost 0 predicted events
            else            return 0.94;//0.97 had almost 0 predicted events
        }else {
            if(mass <= 5)   return 0.96;
            else            return 0.95;
        }
    }else {//muon
        if(is2016){
            if(mass <= 5)   return 0.996;
            else            return 0.996;
        }else if(is2017){
            if(mass <= 5)   return 0.994;
            else            return 0.996;
        }else {
            if(mass <= 5)   return 0.995;
            else            return 0.996;
        }
    }
}

double get_NewPFNcut(int mass, unsigned l1flavor, unsigned l2flavor, double SVmass, double Lxy, bool isOS, bool is2016, bool is2017)
{
    //special cuts for bins that otherwise have 0 prediction
    if(isOS){
        if(is2016){
            if(mass <= 5){
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 2 and Lxy >= 10)                       return 0.957;//OS me LowMass 2016
            }else{
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.990;//OS em HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 1 and Lxy < 5)            return 0.987;//OS ee HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.933;//OS ee HighMass 2016
                if(l1flavor == 1 and l2flavor == 0 and SVmass <  6 and Lxy >= 5)                        return 0.982;//OS me HighMass 2016
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.952;//OS me HighMass 2016
            }
        }else{
            if(mass <= 5){
                if(l1flavor == 1 and l2flavor == 1 and SVmass <  2 and Lxy <  4)                        return 0.995;//OS mm LowMass 1718
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 2 and Lxy >= 10)                       return 0.979;//OS me LowMass 1718
            }else{
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.986;//OS em HighMass 1718
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.917;//OS me HighMass 1718
            }
        }
    }else{
        if(is2016){
            if(mass <= 5){
                //all bins fine
            }else{
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 1 and Lxy < 5)            return 0.987;//SS em HighMass 2016
                //!!!if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.053;//SS em HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 1 and Lxy < 5)            return 0.988;//SS ee HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.913;//SS ee HighMass 2016
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.968;//OS me HighMass 2016
            }
        }else{
            if(mass <= 5){
                if(l1flavor == 1 and l2flavor == 1 and SVmass <  2 and Lxy <  4)                        return 0.994;//SS mm LowMass 1718
                if(l1flavor == 0 and l2flavor == 1 and SVmass <  2 and Lxy <  4)                        return 0.990;//SS me LowMass 1718
            }else{
                if(l1flavor == 1 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.991;//SS mm HighMass 1718
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.510;//SS me HighMass 1718
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.956;//SS me HighMass 1718
            }
        }
    }

    // Normal overall PFN cuts
    if(l1flavor == 0 and l2flavor == 0){//ee
        if(is2016){
            if(mass <= 5)   return 0.98;
            else            return 0.99;
        }else if(is2017){
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }else {
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }
    }else if(l1flavor == 1 and l2flavor == 0){//me
        if(is2016){
            if(mass <= 5)   return 0.98;
            else            return 0.99;
        }else if(is2017){
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }else {
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }
    }else if(l1flavor == 1 and l2flavor == 1){//mm
        if(is2016){
            if(mass <= 5)   return 0.9994;
            else            return 0.998;
        }else if(is2017){
            if(mass <= 5)   return 0.996;
            else            return 0.998;
        }else {
            if(mass <= 5)   return 0.996;
            else            return 0.998;
        }
    }else if(l1flavor == 0 and l2flavor == 1){//em
        if(is2016){
            if(mass <= 5)   return 0.999;
            else            return 0.998;
        }else if(is2017){
            if(mass <= 5)   return 0.996;
            else            return 0.996;
        }else {
            if(mass <= 5)   return 0.996;
            else            return 0.996;
        }
    }else{
        std::cout << "Error: Reaching end of get_NewPFNcut without specifying a cut" << std::endl;
        return 0.;
    }
}

double get_PFNcut(int mass, unsigned flavor, bool is2016, bool is2017)
{
    if(flavor == 0){//electron
        if(is2016){
            if(mass <= 5)   return 0.98;
            else            return 0.99;
        }else if(is2017){
            if(mass <= 5)   return 0.97;//0.98 had almost 0 predicted events
            else            return 0.96;//0.97 had almost 0 predicted events
        }else {
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }
    }else {//muon
        if(is2016){
            if(mass <= 5)   return 0.999;
            else            return 0.998;
        }else if(is2017){
            if(mass <= 5)   return 0.996;
            else            return 0.998;
        }else {
            if(mass <= 5)   return 0.997;
            else            return 0.998;
        }
    }
}

double get_LoosePFNcut(int mass, unsigned flavor, bool is2016, bool is2017)
{
    if(flavor == 0){//electron
        if(is2016){
            if(mass <= 5)   return 0.8;
            else            return 0.8;
        }else if(is2017){
            if(mass <= 5)   return 0.8;
            else            return 0.8;
        }else {
            if(mass <= 5)   return 0.8;
            else            return 0.8;
        }
    }else {//muon
        if(is2016){
            if(mass <= 5)   return 0.85;
            else            return 0.85;
        }else if(is2017){
            if(mass <= 5)   return 0.8;
            else            return 0.8;
        }else {
            if(mass <= 5)   return 0.8;
            else            return 0.8;
        }
    }
}

double get_LoosePFNcut2(int mass, unsigned flavor, bool is2016, bool is2017)
{
    if(flavor == 0){//electron
        if(is2016){
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }else if(is2017){
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }else {
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }
    }else {//muon
        if(is2016){
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }else if(is2017){
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }else {
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }
    }
}

unsigned mini_analyzer::get_PFNevaluation_index(int mass, unsigned flavor)
{
    int mass_ev;
    double V2_ev;
    if(flavor == 0){//electron
        if(mass <= 5){
           mass_ev = 5;
           V2_ev = 6e-6;
        }else {
            mass_ev = 10;
            V2_ev = 9e-7;
        }
    }else if(flavor == 1){//muon
        if(mass <= 5){
           mass_ev = 5;
           V2_ev = 9e-7;
        }else {
            mass_ev = 10;
            V2_ev = 3e-7;
        }
    }else {
        mass_ev = 0;
        V2_ev = 0.;
    }

    return MV2tags[get_MV2name(mass_ev, V2_ev)];
}


void mini_analyzer::init_MV2_parametrization()
{
    for(unsigned i_mv2 = 0; i_mv2 < event._nMV2; i_mv2++){
        MV2tags[get_MV2name(event._evaluating_mass[i_mv2], event._evaluating_V2[i_mv2])] = i_mv2;
    }
}

void mini_analyzer::init_CP()
{
    CPtags["_CP-0p96"] = 0.96;
    CPtags["_CP-0p97"] = 0.97;
    CPtags["_CP-0p98"] = 0.98;
    CPtags["_CP-0p99"] = 0.99;
    CPtags["_CP-0p992"] = 0.992;
    CPtags["_CP-0p994"] = 0.994;
    CPtags["_CP-0p996"] = 0.996;
    CPtags["_CP-0p998"] = 0.998;
}


void mini_analyzer::analyze(int max_entries, int partition, int partitionjobnumber)
{
    // Determine range of events to loop over
    Long64_t nentries = event.BkgEstimator_tree->GetEntries();
    if(max_entries == -1 or max_entries > nentries) max_entries = nentries;
    Long64_t j_begin = floor(1.0 * max_entries * partitionjobnumber / partition);
    Long64_t j_end   = floor(1.0 * max_entries * (partitionjobnumber + 1) / partition);
    unsigned notice = ceil(0.01 * (j_end - j_begin) / 20) * 100;
    unsigned loop_counter = 0;

    unsigned cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0, cnt8 = 0;
    //main loop
    std::cout << "Running over " << j_begin << " - " << j_end-1 << " out of " << max_entries << " events from " << event.BkgEstimator_filename << std::endl;
    for(unsigned jentry = j_begin; jentry < j_end; ++jentry){
	    event.BkgEstimator_tree->GetEntry(jentry);

        if(loop_counter == notice){
            std::cout << jentry - j_begin << " of " << j_end - j_begin << std::endl;
            loop_counter = 0;
        }


        set_signal_regions();
        //set_signal_regions_gridscan();
        fill_histograms();

        if( event._SV_l1mass > 10){
            cnt1++;
            if(event._nTightLep == 1){
                cnt2++;
                if(event._nTightJet <= 1){
                    cnt3++;
                    if(event._SV_l1mass > 50){
                        cnt4++;
                        if(event._SV_l1mass < 85){
                            cnt5++;
                            int i_MV2      = get_PFNevaluation_index(10, 1);
                            double PFNcut  = get_NewPFNcut(10, event._l1Flavor, event._lFlavor, event._SV_mass, event._SV_PVSVdist_2D, event._l1Charge != event._lCharge, event._is2016, event._is2017);
                            if(event._JetTagVal[i_MV2] > PFNcut){
                                cnt6++;
                                if(event._SV_mass > 2){
                                    cnt7++;
                                    if(event._SV_PVSVdist_2D < 4){
                                        cnt8++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        ++loop_counter;
    }
    std::cout << "selection counter values: " << std::endl;
    std::cout << "counter 1: " << cnt1 << std::endl;
    std::cout << "counter 2: " << cnt2 << std::endl;
    std::cout << "counter 3: " << cnt3 << std::endl;
    std::cout << "counter 4: " << cnt4 << std::endl;
    std::cout << "counter 5: " << cnt5 << std::endl;
    std::cout << "counter 6: " << cnt6 << std::endl;
    std::cout << "counter 7: " << cnt7 << std::endl;
    std::cout << "counter 8: " << cnt8 << std::endl;
    sum_quad_histograms();

    //Get the JEC variations for signal MC
    //std::map<TString, TH1*> hists_JEC;
    //if(isSignal){
    //    hists_JEC = get_hists_JECvariations(event.BkgEstimator_filename);
    //    set_correct_sysUp_sysDown(&hists_JEC, {"JEC_", "JER_"});
    //}

    TString outputfilename = get_mini_analyzer_outputfilename(event.BkgEstimator_filename);
    std::cout << "output to: " << outputfilename << std::endl;
    TFile *output = new TFile(outputfilename, "recreate");
    
    std::cout << "calculating and applying ABCD method" << std::endl;
    ABCD_ratios();
    std::cout << "setting quadA quasi-zero bins to zero" << std::endl;
    set_quadA_zero_event_bins();
    add_ABCDstat_variation("cutTightmlSV_BtoAwithCD_Shape_SR");
    //add_NonClosureSys_variation("cutTightmlSV_BtoAwithCD_Shape_SR");

    std::cout << "Add under- and overflow to last bins, then write them" << std::endl;
    for(auto const& it : hists){
        TH1* h = it.second;
        fix_overflow_and_negative_bins(h);
        //divide_stat_errors(h);
	    h->Write(h->GetName(), TObject::kOverwrite);
    }
    for(auto const& it : hists2D){
        TH2* h = it.second;
        h->Write(h->GetName(), TObject::kOverwrite);
    }
    for(auto const& it : hists_sys){
        TH1* h = it.second;
        fix_overflow_and_negative_bins(h);
        h->Write(h->GetName(), TObject::kOverwrite);
    }
    //for(auto const& it : hists_JEC){
    //    TH1* h = it.second;
    //    fix_overflow_and_negative_bins(h);
    //    h->Write(h->GetName(), TObject::kOverwrite);
    //}
    
    TH1F* hadd_counter = new TH1F("hadd_counter", "nr. of files hadded together;;", 1, 0, 1);
    hadd_counter->Fill(0);
    hadd_counter->Write();

    std::cout << "close file" << std::endl;
    output->Close();
}


void mini_analyzer::ABCD_ratios()
{
    if(!isData) calculate_ratio("_quadA_", "_quadB_", "_AoverB_");
    if(!isData) calculate_ratio("_quadA_", "_quadC_", "_AoverC_");
    calculate_ratio("_quadC_", "_quadD_", "_CoverD_");
    calculate_ratio("_quadB_", "_quadD_", "_BoverD_");
    calculate_eff();

    //apply_ratio("_CoverD_", "_quadD_", "_DtoCwithCD_");
    apply_ratio("_CoverD_", "_quadB_", "_BtoAwithCD_", "_CoverD_");
    //apply_ratio("_BoverD_", "_quadC_", "_CtoAwithBD_");
}


void mini_analyzer::calculate_ratio(TString numerator_tag, TString denominator_tag, TString ratio_tag)
{
    for(auto const& it : hists){
        TH1* h = it.second;
        TString hname = h->GetName();

        if(hname.Contains(numerator_tag) and !hname.Contains("_sys")){
            TString hname_den(hname), hname_ratio(hname);

            hname_den.ReplaceAll(numerator_tag, denominator_tag);
            hname_ratio.ReplaceAll(numerator_tag, ratio_tag);

            if(hists[hname]->GetMaximum() > 0 and hists[hname_den]->GetMaximum() > 0){
                hists[hname_ratio]->Divide(hists[hname], hists[hname_den]);
            }
        }
    }
}


void mini_analyzer::apply_ratio(TString ratio_tag, TString histo_tag, TString target_tag, TString ratio_tag_for_error)
{
    for(auto const& it : hists){
        TH1* h = it.second;
        TString hname = h->GetName();

        if(hname.Contains(histo_tag) and !hname.Contains("_sys")){
            TString hname_ratio(hname), hname_target(hname), hname_ratio_for_error(hname);
            hname_ratio.ReplaceAll(histo_tag, ratio_tag);
            hname_target.ReplaceAll(histo_tag, target_tag);
            hname_ratio_for_error.ReplaceAll(histo_tag, ratio_tag_for_error);

            if(hists[hname]->GetMaximum() > 0 and hists[hname_ratio]->GetMaximum() > 0){
                hists[hname_target] = (TH1F*)hists[hname]->Clone(hname_target);
                //hists[hname_target]->Scale(hists[hname_ratio]->GetBinContent(1));//use this in case of using a full ratio for ABCD prediction
                hists[hname_target]->Multiply(hists[hname_ratio]);
                set_error_for_zero_event_bins(hname_target, hname_ratio_for_error);//sets bin error for 0 event bins to (central value of C/D ratio in that bin, this assumes ratio =/= 0!)
            }
        }
    }
}


void mini_analyzer::calculate_eff()
{
    for(auto const& it : hists){
        TString hname = it.first;

        if(hname.Contains("_quadA_") and !hname.Contains("_sys")){
            TString hname_eff = hname;
            hname_eff.ReplaceAll("_quadA_", "_Aeff_");
            hists[hname_eff] = (TH1F*)hists[hname]->Clone(hname_eff);
            TH1F* den = (TH1F*)hists[hname]->Clone(hname_eff + "_den");
            den->Add(hists[hname_eff.ReplaceAll("_Aeff_", "_quadB_")]);
            den->Add(hists[hname_eff.ReplaceAll("_quadB_", "_quadC_")]);
            den->Add(hists[hname_eff.ReplaceAll("_quadC_", "_quadD_")]);
            hists[hname_eff]->Divide(den);
        }
    }
}

void mini_analyzer::add_NonClosureSys_variation(TString selection_tag)
{
    for(auto const& it : hists){
        TH1* h = it.second;
        TString hname = it.first;
        if(!hname.Contains(selection_tag)) continue;

        TString hname_CR1 = hname;
        hname_CR1.ReplaceAll("TightmlSV", "CR1mlSV");
        TString hname_CR1_quadA = hname_CR1;
        hname_CR1_quadA.ReplaceAll("BtoAwithCD", "quadA");
        // ABCD statistical variation
        hists_sys[hname + "_NonClosureUp"] = (TH1F*)h->Clone(hname + "_NonClosureUp");
        hists_sys[hname + "_NonClosureDown"] = (TH1F*)h->Clone(hname + "_NonClosureDown");
        for(int i = 1; i <= h->GetNbinsX(); i++){
            if(hists[hname_CR1_quadA]->GetBinContent(i) == 0 or hists[hname_CR1]->GetBinContent(i) == 0){
                hists_sys[hname + "_NonClosureUp"]->SetBinContent(i, h->GetBinContent(i)*2);
                hists_sys[hname + "_NonClosureDown"]->SetBinContent(i, h->GetBinContent(i)*0.5);
            }else{
                hists_sys[hname + "_NonClosureUp"]->SetBinContent(i, h->GetBinContent(i)*(1 + hists[hname_CR1_quadA]->GetBinContent(i)/hists[hname_CR1]->GetBinContent(i)));
                hists_sys[hname + "_NonClosureDown"]->SetBinContent(i, h->GetBinContent(i)*(1 - hists[hname_CR1_quadA]->GetBinContent(i)/hists[hname_CR1]->GetBinContent(i)));
            }
        }
    }
}

void mini_analyzer::add_ABCDstat_variation(TString selection_tag)
{
    for(auto const& it : hists){
        TH1* h = it.second;
        TString hname = it.first;
        if(!hname.Contains(selection_tag)) continue;

        TString hname_CR1 = hname;
        hname_CR1.ReplaceAll("TightmlSV", "CR1mlSV");
        // ABCD statistical variation
        hists_sys[hname + "_ABCDstatUp"] = (TH1F*)h->Clone(hname + "_ABCDstatUp");
        hists_sys[hname + "_ABCDstatDown"] = (TH1F*)h->Clone(hname + "_ABCDstatDown");
        for(int i = 1; i <= h->GetNbinsX(); i++){
            if(hists[hname_CR1]->GetBinContent(i) == 0){
                hists_sys[hname + "_ABCDstatUp"]->SetBinContent(i, h->GetBinContent(i)*2);
                hists_sys[hname + "_ABCDstatDown"]->SetBinContent(i, h->GetBinContent(i)*0);
            }else{
                hists_sys[hname + "_ABCDstatUp"]->SetBinContent(i, h->GetBinContent(i)*(1 + hists[hname_CR1]->GetBinErrorUp(i)/hists[hname_CR1]->GetBinContent(i)));
                hists_sys[hname + "_ABCDstatDown"]->SetBinContent(i, h->GetBinContent(i)*(1 - hists[hname_CR1]->GetBinErrorLow(i)/hists[hname_CR1]->GetBinContent(i)));
                //hists_sys[hname + "_ABCDstatUp"]->SetBinContent(i, h->GetBinContent(i)*(1 + hists[hname_CR1]->GetBinErrorUp(i)/hists[hname_CR1]->GetBinContent(i)/5.));
                //hists_sys[hname + "_ABCDstatDown"]->SetBinContent(i, h->GetBinContent(i)*(1 - hists[hname_CR1]->GetBinErrorLow(i)/hists[hname_CR1]->GetBinContent(i)/5.));
            }
        }
    }
}


// used for finding optimal PFN cutting point in ABCD method. Grid scan of possible cutting points is done
void mini_analyzer::set_signal_regions_gridscan()
{
    ABCDtags.clear();
    
    baseline_cutmlSV = event._SV_l1mass > 10 &&
                       event._nTightLep == 1 &&
                       event._nTightJet <= 1;

    for(auto const& CP : CPtags){
        TString CPtag = CP.first;
        double PFNcut = CP.second;
        for(auto const& MV2 : MV2tags){
            TString MV2tag = MV2.first;
            int i_MV2      = get_PFNevaluation_index(event._evaluating_mass[MV2.second], event._lFlavor);
            
            if(baseline_cutmlSV){
                if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                    if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + CPtag + "_cutTightmlSV_quadA");
                    else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + CPtag + "_cutTightmlSV_quadC");
                }else {
                    if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + CPtag + "_cutTightmlSV_quadB");
                    else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + CPtag + "_cutTightmlSV_quadD");
                }
            }
        }
    }
    
    // Determine sr_flavor
    sr_flavor = "";
    if(event._l1Charge == event._lCharge) sr_flavor += "_SS";
    else sr_flavor += "_OS";

    if(event._l1Flavor == 0) sr_flavor += "_e";
    else if(event._l1Flavor == 1) sr_flavor += "_m";

    if(event._lFlavor == 0) sr_flavor += "e";
    else if(event._lFlavor == 1) sr_flavor += "m";

}

void mini_analyzer::set_signal_regions()
{
    ABCDtags.clear();

    //Training selection is already applied before filling BkgEstimator tree
    baseline_cutphill = event._mll < 80 &&
                        event._mll > 10 &&
                        event._dphill > 0.4 &&
                        event._nTightLep == 1 &&
                        event._nTightJet <= 1;

    baseline_cutmll = event._dphill > 2.3 &&
                      event._mll > 10 &&
                      event._nTightLep == 1 &&
                      event._nTightJet <= 1;

    baseline_cutphiORmll = event._mll > 10 &&
                           event._nTightLep == 1 &&
                           event._nTightJet <= 1;

    baseline_cutmlSV = event._SV_l1mass > 10 &&
                       event._nTightLep == 1 &&
                       event._nTightJet <= 1;

    baseline_cutmlSV_nojetveto = event._SV_l1mass > 10 &&
                                 event._nTightLep == 1;

    baseline_cutCR3phill = event._SV_l1mass > 10 &&
                           (event._SV_l1mass < 50 || event._SV_l1mass > 85) &&
                           event._dphill > 0.4 &&
                           event._nTightLep == 1 &&
                           event._nTightJet <= 1;

    baseline_cutmlSV_CR2Jets = event._SV_l1mass > 10 &&
                             event._nTightLep == 1 &&
                             event._nTightJet > 1;

    for(auto const& MV2 : MV2tags){
        TString MV2tag = MV2.first;
        int i_MV2      = get_PFNevaluation_index(event._evaluating_mass[MV2.second], event._lFlavor);
        //int i_MV2      = get_PFNevaluation_index(ceil(event._SV_mass), event._lFlavor);
        //double PFNcut  = get_PFNcut(event._evaluating_mass[MV2.second], event._lFlavor, event._is2016, event._is2017);
        double PFNcut  = get_NewPFNcut(event._evaluating_mass[MV2.second], event._l1Flavor, event._lFlavor, event._SV_mass, event._SV_PVSVdist_2D, event._l1Charge != event._lCharge, event._is2016, event._is2017);
        double LoosePFNcut = get_LoosePFNcut(event._evaluating_mass[MV2.second], event._lFlavor, event._is2016, event._is2017);
        double LoosePFNcut2 = get_LoosePFNcut2(event._evaluating_mass[MV2.second], event._lFlavor, event._is2016, event._is2017);
        double MediumPFNcut  = get_MediumPFNcut(event._evaluating_mass[MV2.second], event._lFlavor, event._is2016, event._is2017);
        // Determine quadrant (in PFN output and dphi)
        //// dphill
        //if(baseline_cutphill){
        //    if(event._dphill > 2.3){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutphill_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutphill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutphill_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutphill_quadD");
        //    }
        //}
        //// control region 1: dphill only up to PFN LoosePFNcut
        //if(baseline_cutphill and event._JetTagVal[i_MV2] < LoosePFNcut){
        //    if(event._dphill > 2.3){
        //        if(event._JetTagVal[i_MV2] > 0.6) ABCDtags.push_back(MV2tag + "_cutCR1phill_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutCR1phill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > 0.6) ABCDtags.push_back(MV2tag + "_cutCR1phill_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutCR1phill_quadD");
        //    }
        //}
        //// control region 2: dphill only up to dphi of 2.3
        //if(baseline_cutphill and event._dphill < 2.3){
        //    if(event._dphill > 1.9){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR2phill_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutCR2phill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR2phill_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutCR2phill_quadD");
        //    }
        //}
        //// control region 3: dphill normal method within mlSV inverted region
        //if(baseline_cutCR3phill){
        //    if(event._dphill > 2.3){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR3phill_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutCR3phill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR3phill_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutCR3phill_quadD");
        //    }
        //}
        //// mll
        //if(baseline_cutmll){
        //    if(event._mll < 80){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutmll_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutmll_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutmll_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutmll_quadD");
        //    }
        //}
        //// dphill or mll
        //if(baseline_cutphiORmll){
        //    if(event._dphill > 2.3 and event._mll < 80){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutphiORmll_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutphiORmll_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutphiORmll_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutphiORmll_quadD");
        //    }
        //}
        // mlSV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutmlSV_quadA");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutmlSV_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutmlSV_quadB");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutmlSV_quadD");
            }
        }
        // control region 1: mlSV with PFN below LoosePFNcut
        if(baseline_cutmlSV and event._JetTagVal[i_MV2] < LoosePFNcut){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > 0.6) ABCDtags.push_back(MV2tag + "_cutCR1mlSV_quadA");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutCR1mlSV_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > 0.6) ABCDtags.push_back(MV2tag + "_cutCR1mlSV_quadB");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutCR1mlSV_quadD");
            }
        }
        // control region 1 Tight: mlSV with PFN below LoosePFNcut2
        if(baseline_cutmlSV and event._JetTagVal[i_MV2] < LoosePFNcut2){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > 0.7) ABCDtags.push_back(MV2tag + "_cutTightCR1mlSV_quadA");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR1mlSV_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > 0.7) ABCDtags.push_back(MV2tag + "_cutTightCR1mlSV_quadB");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR1mlSV_quadD");
            }
        }
        // control region 2: mlSV with signal region between 85 - 110 GeV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
                if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR2mlSV_quadA");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutCR2mlSV_quadC");
            }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
                if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR2mlSV_quadB");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutCR2mlSV_quadD");
            }
        }
        //// control region 3: mlSV with signal region between 10 - 50 Gev
        //if(baseline_cutmlSV){
        //    if(event._SV_l1mass < 50){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR3mlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutCR3mlSV_quadC");
        //    }else if(event._SV_l1mass > 85){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR3mlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutCR3mlSV_quadD");
        //    }
        //}



        // Tight predictions: PFN > PFNcut
        //// dphill
        //if(baseline_cutphill){
        //    if(event._dphill > 2.3){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightphill_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightphill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightphill_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightphill_quadD");
        //    }
        //}
        //// control region 2: dphill only up to dphi of 2.3
        //if(baseline_cutphill and event._dphill < 2.3){
        //    if(event._dphill > 1.9){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2phill_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR2phill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2phill_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR2phill_quadD");
        //    }
        //}
        //// control region 2: dphill normal method within mlSV inverted region
        //if(baseline_cutCR3phill){
        //    if(event._dphill > 2.3){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR3phill_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR3phill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR3phill_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR3phill_quadD");
        //    }
        //}
        //// mll
        //if(baseline_cutmll){
        //    if(event._mll < 80){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightmll_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightmll_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightmll_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightmll_quadD");
        //    }
        //}
        //// dphill or mll
        //if(baseline_cutphiORmll){
        //    if(event._dphill > 2.3 and event._mll < 80){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightphiORmll_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightphiORmll_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightphiORmll_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightphiORmll_quadD");
        //    }
        //}
        // mlSV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightmlSV_quadA");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightmlSV_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightmlSV_quadB");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightmlSV_quadD");
            }
        }
        // Medium mlSV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediummlSV_quadA");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutMediummlSV_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediummlSV_quadB");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutMediummlSV_quadD");
            }
        }
        // control region 2: mlSV with signal region between 85 - 110 GeV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_quadA");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_quadC");
            }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_quadB");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_quadD");
            }
        }
        // control region 2: mlSV with signal region between 85 - 110 GeV without jet veto
        if(baseline_cutmlSV_nojetveto){
            if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2NoJetVetomlSV_quadA");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR2NoJetVetomlSV_quadC");
            }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2NoJetVetomlSV_quadB");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR2NoJetVetomlSV_quadD");
            }
        }
        //// control region 3: mlSV with signal region between 10 - 50 Gev
        //if(baseline_cutmlSV){
        //    if(event._SV_l1mass < 50){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR3mlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR3mlSV_quadC");
        //    }else if(event._SV_l1mass > 85){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR3mlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR3mlSV_quadD");
        //    }
        //}
        // control region 2: mlSV with signal region between 85 - 110 GeV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediumCR2mlSV_quadA");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutMediumCR2mlSV_quadC");
            }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediumCR2mlSV_quadB");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutMediumCR2mlSV_quadD");
            }
        }
        //// control region 3: mlSV with signal region between 10 - 50 Gev
        //if(baseline_cutmlSV){
        //    if(event._SV_l1mass < 50){
        //        if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediumCR3mlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutMediumCR3mlSV_quadC");
        //    }else if(event._SV_l1mass > 85){
        //        if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediumCR3mlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutMediumCR3mlSV_quadD");
        //    }
        //}
        // mlSV Inverted Jets CR
        if(baseline_cutmlSV_CR2Jets){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightmlSV_CR2Jets_quadA");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightmlSV_CR2Jets_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightmlSV_CR2Jets_quadB");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightmlSV_CR2Jets_quadD");
            }
        }
        // Medium mlSV Inverted Jets CR
        if(baseline_cutmlSV_CR2Jets){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediummlSV_CR2Jets_quadA");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutMediummlSV_CR2Jets_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediummlSV_CR2Jets_quadB");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutMediummlSV_CR2Jets_quadD");
            }
        }
        // control region 2 in Inverted Jets CR: mlSV with signal region between 85 - 110 GeV
        if(baseline_cutmlSV_CR2Jets){
            if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_CR2Jets_quadA");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_CR2Jets_quadC");
            }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_CR2Jets_quadB");
                else if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_CR2Jets_quadD");
            }
        }

        //extra noSR plots
        if(baseline_cutmlSV){
            if(!isData) ABCDtags.push_back(MV2tag + "_cutbaselinemlSV");
            if(event._JetTagVal[i_MV2] < 0.8) ABCDtags.push_back(MV2tag + "_cutbaselinemlSV_noSR");

            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(!isData) ABCDtags.push_back(MV2tag + "_cutinsidemlSV");
                if(event._JetTagVal[i_MV2] < 0.8) ABCDtags.push_back(MV2tag + "_cutinsidemlSV_noSR");
            }else{
                ABCDtags.push_back(MV2tag + "_cutoutsidemlSV");
            }
        }
        if(baseline_cutmlSV_CR2Jets){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutinsidemlSV_CR2Jets");
            }else{
                if(event._JetTagVal[i_MV2] > 0.2) ABCDtags.push_back(MV2tag + "_cutoutsidemlSV_CR2Jets");
            }
        }
    }


    // Determine sr_flavor
    sr_flavor = "";
    if(event._l1Charge == event._lCharge) sr_flavor += "_SS";
    else sr_flavor += "_OS";

    if(event._l1Flavor == 0) sr_flavor += "_e";
    else if(event._l1Flavor == 1) sr_flavor += "_m";

    if(event._lFlavor == 0) sr_flavor += "e";
    else if(event._lFlavor == 1) sr_flavor += "m";

    if(event.BkgEstimator_filename.Contains("JECDown") or event.BkgEstimator_filename.Contains("JECUp") or event.BkgEstimator_filename.Contains("JERDown") or event.BkgEstimator_filename.Contains("JERUp")){
        for(auto it = ABCDtags.begin(); it != ABCDtags.end(); ){
            if(!(*it).Contains("_cutTightmlSV_quadA")) it = ABCDtags.erase(it);
            else ++it;
        }
    }

}

void mini_analyzer::add_histograms_gridscan()
{
    std::cout << "Initializing histograms" << std::endl;
    for(const TString& lep_region : {"_OS_ee", "_SS_ee", "_OS_mm", "_SS_mm", "_OS_em", "_SS_em", "_OS_me", "_SS_me"}){
        for(const auto& MV2 : MV2tags){
            TString MV2tag = MV2.first;
            for(const auto& CP : CPtags){
                TString CPtag = CP.first;
                for(const TString& cut2region : {"_cutTightmlSV"}){
                    for(const TString& quadrant : {"_quadB", "_quadC", "_quadD"/*, "_quadCD", "_quadBD", "_quadBCD"*/,  "_CoverD"/*, "_BoverD", "_DtoCwithCD"*/, "_BtoAwithCD"/*, "_CtoAwithBD"*/}){
                        //add_standard_histograms(lep_region + MV2tag + cut2region + quadrant);
                        add_pfn_histograms(lep_region + MV2tag + CPtag + cut2region + quadrant);
                    }
                    //add_fraction_histograms(lep_region + MV2tag + CPtag + cut2region);

                    // only make region A histograms if we're not running over data
                    if(!isData or cut2region.Contains("CR")){
                        for(const TString & quadrant : {"_quadA"/*, "_quadAB", "_quadAC"*/, "_AoverB", "_AoverC"/*, "_quadABCD"*/}){
                            //add_standard_histograms(lep_region + MV2tag + cut2region + quadrant);
                            add_pfn_histograms(lep_region + MV2tag + CPtag + cut2region + quadrant);
                        }
                    }
                }
        }
    }
    // Signal region yield histograms
    for(const TString& lep_region : {"_mm", "_ee", "_me", "_em", "_2l"}){
        for(const auto& MV2 : MV2tags){
            TString MV2tag = MV2.first;
            for(const auto& CP : CPtags){
                TString CPtag = CP.first;
                for(const TString& cut2region : {"_cutTightmlSV"}){
                    for(const TString& quadrant : {"_quadB", "_quadC", "_quadD"/*, "_quadCD", "_quadBD", "_quadBCD"*/,  "_CoverD"/*, "_BoverD", "_DtoCwithCD"*/, "_BtoAwithCD"/*, "_CtoAwithBD"*/}){
                        add_Shape_SR_histograms(lep_region + MV2tag + CPtag + cut2region + quadrant);
                    }
                    if(!isData or cut2region.Contains("CR")){
                        for(const TString & quadrant : {"_quadA"/*, "_quadAB", "_quadAC"*/, "_AoverB", "_AoverC"/*, "_quadABCD"*/}){
                            add_Shape_SR_histograms(lep_region + MV2tag + CPtag + cut2region + quadrant);
                        }
                    }
                }
            }
        }
    }
    //for(const auto& hist : hists) hist.second->Sumw2();
}


}

void mini_analyzer::add_histograms()
{
    std::cout << "Initializing histograms" << std::endl;
    for(const TString& lep_region : {"_OS_ee", "_SS_ee", "_OS_mm", "_SS_mm", "_OS_em", "_SS_em", "_OS_me", "_SS_me"}){
        for(const auto& MV2 : MV2tags){
            TString MV2tag = MV2.first;
            if(!(MV2tag.Contains("2e-06") or MV2tag.Contains("4e-06") or MV2tag.Contains("7e-05"))) continue;
            for(const TString& cut2region : {/*"_cutphill", "_cutmll", "_cutphiORmll",*/ "_cutmlSV", "_cutCR1mlSV", "_cutCR2mlSV"/*, "_cutCR3mlSV", "_cutCR1phill", "_cutCR2phill", "_cutCR3phill", "_cutTightphill", "_cutTightmll", "_cutTightphiORmll"*/, "_cutTightmlSV", "_cutMediummlSV", "_cutTightCR1mlSV", "_cutTightCR2mlSV", "_cutTightCR2NoJetVetomlSV", "_cutTightCR2mlSV_CR2Jets"/*, "_cutTightCR3mlSV", "_cutTightCR2phill", "_cutTightCR3phill"*/, "_cutMediumCR2mlSV"/*, "_cutMediumCR3mlSV"*/, "_cutTightmlSV_CR2Jets", "_cutMediummlSV_CR2Jets"}){
                for(const TString& quadrant : {"_quadB", "_quadC", "_quadD", "_quadCD", "_quadBD", "_quadBCD",  "_CoverD", "_BoverD"/*, "_DtoCwithCD"*/, "_BtoAwithCD"/*, "_CtoAwithBD"*/}){
                    add_standard_histograms(lep_region + MV2tag + cut2region + quadrant);
    //                add_pfn_histograms(lep_region + MV2tag + cut2region + quadrant);
                }
    //            //add_fraction_histograms(lep_region + MV2tag + cut2region);

    //            // only make region A histograms if we're not running over data
                if(!isData or cut2region.Contains("CR")){
                    for(const TString & quadrant : {"_quadA", "_quadAB", "_quadAC", "_AoverB", "_AoverC", "_quadABCD"}){
                        add_standard_histograms(lep_region + MV2tag + cut2region + quadrant);
    //                    add_pfn_histograms(lep_region + MV2tag + cut2region + quadrant);
                    }
                }
            }

            std::vector<TString> cutregions;
            if(isData) cutregions = {"_cutbaselinemlSV_noSR", "_cutinsidemlSV_noSR", "_cutoutsidemlSV", "_cutinsidemlSV_CR2Jets", "_cutoutsidemlSV_CR2Jets"};
            else       cutregions = {"_cutbaselinemlSV_noSR", "_cutinsidemlSV_noSR", "_cutoutsidemlSV", "_cutbaselinemlSV", "_cutinsidemlSV", "_cutinsidemlSV_CR2Jets", "_cutoutsidemlSV_CR2Jets"};
            for(const TString& cutregion : cutregions){
                add_standard_histograms(lep_region + MV2tag + cutregion);
                add_pfn_histograms(lep_region + MV2tag + cutregion);
            }
        }
    }
    // Signal region yield histograms
    for(const TString& lep_region : {"_mm", "_ee", "_em", "_me", "_2l"}){
        for(const auto& MV2 : MV2tags){
            TString MV2tag = MV2.first;
            bool TagExtraPlots = MV2tag.Contains("2e-06") or MV2tag.Contains("4e-06") or MV2tag.Contains("7e-05");
            for(const TString& cut2region : {/*"_cutphill", "_cutmll", "_cutphiORmll",*/ "_cutmlSV", "_cutCR1mlSV", "_cutCR2mlSV"/*, "_cutCR3mlSV", "_cutCR1phill", "_cutCR2phill", "_cutCR3phill", "_cutTightphill", "_cutTightmll", "_cutTightphiORmll"*/, "_cutTightmlSV", "_cutMediummlSV", "_cutTightCR1mlSV", "_cutTightCR2mlSV", "_cutTightCR2NoJetVetomlSV", "_cutTightCR2mlSV_CR2Jets"/*, "_cutTightCR3mlSV", "_cutTightCR2phill", "_cutTightCR3phill"*/, "_cutMediumCR2mlSV"/*, "_cutMediumCR3mlSV"*/, "_cutTightmlSV_CR2Jets", "_cutMediummlSV_CR2Jets"}){
                for(const TString& quadrant : {"_quadB", "_quadC", "_quadD", "_quadCD", "_quadBD", "_quadBCD",  "_CoverD", "_BoverD"/*, "_DtoCwithCD"*/, "_BtoAwithCD"/*, "_CtoAwithBD"*/}){
                    add_Shape_SR_histograms(lep_region + MV2tag + cut2region + quadrant);
                    if(TagExtraPlots) add_Shape_SR_extra_histograms(lep_region + MV2tag + cut2region + quadrant);
                }
                if(!isData or cut2region.Contains("CR")){
                    for(const TString & quadrant : {"_quadA", "_quadAB", "_quadAC", "_AoverB", "_AoverC", "_quadABCD"}){
                        add_Shape_SR_histograms(lep_region + MV2tag + cut2region + quadrant);
                        if(TagExtraPlots) add_Shape_SR_extra_histograms(lep_region + MV2tag + cut2region + quadrant);
                    }
                }
            }
            if(!isData){
                for(const auto& var : variations){
                    add_Shape_SR_histograms(lep_region + MV2tag + "_cutTightmlSV_quadA" + var.first);
                }
            }

            std::vector<TString> cutregions;
            if(isData) cutregions = {"_cutbaselinemlSV_noSR", "_cutinsidemlSV_noSR", "_cutoutsidemlSV", "_cutinsidemlSV_CR2Jets", "_cutoutsidemlSV_CR2Jets"};
            else       cutregions = {"_cutbaselinemlSV_noSR", "_cutinsidemlSV_noSR", "_cutoutsidemlSV", "_cutbaselinemlSV", "_cutinsidemlSV", "_cutinsidemlSV_CR2Jets", "_cutoutsidemlSV_CR2Jets"};
            for(const TString& cutregion : cutregions){
                add_Shape_SR_histograms(lep_region + MV2tag + cutregion);
                if(TagExtraPlots) add_Shape_SR_extra_histograms(lep_region + MV2tag + cutregion);
            }
        }
    }
    for(const auto& hist : hists) hist.second->Sumw2();
}


void mini_analyzer::add_fraction_histograms(TString prefix)
{
    hists[prefix+"_QuadFractions"]          = new TH1F(prefix+"_QuadFractions", ";;Fraction", 4, 0, 4);
    hists[prefix+"_QuadFractions_unw"]      = new TH1F(prefix+"_QuadFractions_unw", ";;Unweighted Events", 4, 0, 4);
    hists2D[prefix+"_QuadFractions_2D"]     = new TH2F(prefix+"_QuadFractions_2D", ";;", 4, 0, 4, 4, 0, 4);
    hists2D[prefix+"_QuadFractions2_2D"]    = new TH2F(prefix+"_QuadFractions2_2D", ";;", 2, 0, 2, 4, 0, 4);
}


void mini_analyzer::add_standard_histograms(TString prefix)
{
    //hists[prefix+"_Yield"]              = new TH1F(prefix+"_Yield", ";;Events", 1, 0, 1);
    //hists[prefix+"_SRShape"]            = new TH1F(prefix+"_SRShape", ";;Events", 4, 0, 4);
    //hists[prefix+"_SRShape2"]           = new TH1F(prefix+"_SRShape2", ";;Events", 2, 0, 2);
    //hists[prefix+"_nTightJet"]          = new TH1F(prefix+"_nTightJet", ";N_{Jet};Events", 6, 0, 10);
    //hists[prefix+"_JetPt"]              = new TH1F(prefix+"_JetPt", ";Jet #it{p}_{T} [GeV];Events", 6, 0, 100);
    //hists[prefix+"_JetEta"]             = new TH1F(prefix+"_JetEta", ";Jet #eta;Events", 6, -3, 3);
    //hists[prefix+"_JetPhi"]             = new TH1F(prefix+"_JetPhi", ";Jet #phi;Events", 6, -3.14, 3.14);
    //hists[prefix+"_nTightLep"]          = new TH1F(prefix+"_nTightLep", ";N_{Lep};Events", 6, 0, 10);
    hists[prefix+"_l2_pt"]              = new TH1F(prefix+"_l2_pt", ";l_{2} #it{p}_{T} [GeV];Events", 6, 0, 50);
    //hists[prefix+"_l2_eta"]             = new TH1F(prefix+"_l2_eta", ";l_{2} #eta;Events", 6, -3, 3);
    //hists[prefix+"_l2_phi"]             = new TH1F(prefix+"_l2_phi", ";l_{2} #phi;Events", 6, -3.14, 3.14);
    //hists[prefix+"_l2_dxy"]             = new TH1F(prefix+"_l2_dxy", ";l_{2} dxy [cm];Events", 6, 0, 0.5);
    //hists[prefix+"_l2_dz"]              = new TH1F(prefix+"_l2_dz", ";l_{2} dz [cm];Events", 6, 0, 2);
    //hists[prefix+"_l2_3dIPSig"]         = new TH1F(prefix+"_l2_3dIPSig", ";l_{2} 3dIPSig;Events", 6, 0, 20);
    //hists[prefix+"_l2_reliso"]          = new TH1F(prefix+"_l2_reliso", ";l_{2} Rel Iso;Events", 6, 0, 3.5);
    //hists[prefix+"_l2_ptratio"]         = new TH1F(prefix+"_l2_ptratio", ";l_{2} #it{p}_{T}^{ratio} [GeV];Events", 6, 0, 1);
    //hists[prefix+"_l2_ptrel"]           = new TH1F(prefix+"_l2_ptrel", ";l_{2} #it{p}_{T}^{rel} [GeV];Events", 6, 0, 10);
    //hists[prefix+"_l2_NumberOfHits"]    = new TH1F(prefix+"_l2_NumberOfHits", ";l_{2} Nr. of Hits;Events", 6, 0, 10);
    //hists[prefix+"_l2_NumberOfPixHits"] = new TH1F(prefix+"_l2_NumberOfPixHits", ";l_{2} Nr. of Pixel Hits;Events", 15, 0, 15);
    
    //hists[prefix+"_l1_pt"]              = new TH1F(prefix+"_l1_pt", ";l_{1} #it{p}_{T} [GeV];Events", 6, 0, 150);
    //hists[prefix+"_l1_eta"]             = new TH1F(prefix+"_l1_eta", ";l_{1} #eta;Events", 6, -3, 3);
    //hists[prefix+"_l1_phi"]             = new TH1F(prefix+"_l1_phi", ";l_{1} #phi;Events", 6, -3.14, 3.14);

    hists[prefix+"_mll"]                = new TH1F(prefix+"_mll", ";#it{m}_{ll} [GeV];Events", 6, 0, 200);
    //hists[prefix+"_dRll"]               = new TH1F(prefix+"_dRll", ";#it{#Delta R}_{ll};Events", 6, 0, 6);
    //hists[prefix+"_dphill"]             = new TH1F(prefix+"_dphill", ";#it{#Delta #phi}_{ll};Events", 6, 0, 3.14);
    //hists[prefix+"_dRljet"]             = new TH1F(prefix+"_dRljet", ";#it{#Delta R}_{l,jet};Events", 6, 0, 1.5);

    //double PVSVdxybins[3] = {0, 10, 60};
    hists[prefix+"_PV-SVdxy"]       = new TH1F(prefix+"_PV-SVdxy", ";L_{xy} [cm];Events", 40, 0, 40);
    //hists[prefix+"_PV-SVdxy_zoom2"]  = new TH1F(prefix+"_PV-SVdxy_zoom2", ";L_{xy} [cm];Events", 2, PVSVdxybins);
    //hists[prefix+"_PV-SVdxyz"]      = new TH1F(prefix+"_PV-SVdxyz", ";L_{xyz} [cm];Events", 6, 0, 100);
    //hists[prefix+"_PV-SVdxyz_zoom"] = new TH1F(prefix+"_PV-SVdxyz_zoom", ";L_{xyz} [cm];Events", 6, 0, 20);
    //hists[prefix+"_ntracks"]        = new TH1F(prefix+"_ntracks", ";# of tracks used in SVfit;Events", 15, 0, 15);
    //double SVmassbins[3] = {0, 4, 20};
    //hists[prefix+"_SVmass2"]         = new TH1F(prefix+"_SVmass2", ";SV Mass [GeV];Events", 2, SVmassbins);
    hists[prefix+"_SVl1mass"]         = new TH1F(prefix+"_SVl1mass", ";l_{1}+SV Mass [GeV];Events", 15, 0, 140);
    //hists[prefix+"_SVpt"]             = new TH1F(prefix+"_SVpt", ";SV #it{p}_{T} [GeV];Events", 6, 0, 100);
    //hists[prefix+"_SVeta"]            = new TH1F(prefix+"_SVeta", ";SV #eta;Events", 6, -3, 3);
    //hists[prefix+"_SVphi"]            = new TH1F(prefix+"_SVphi", ";SV #phi;Events", 6, -3.14, 3.14);
    //hists[prefix+"_SVnormchi2"]       = new TH1F(prefix+"_SVnormchi2", ";Normalized #Chi^{2};Events", 6, 0, 10);

    //hists2D[prefix+"_mllvsSVmass"] = new TH2F(prefix+"_mllvsSVmass", ";M_{ll} [GeV];M_{SV} [GeV]", 150, 0, 150, 150, 0, 20);
    //hists2D[prefix+"_mllvsPVSVdxy"] = new TH2F(prefix+"_mllvsPVSVdxy", "M_{ll} [GeV];L_{xy} [cm]", 150, 0, 150, 150, 0, 60);
    //hists2D[prefix+"_dphillvsSVmass"] = new TH2F(prefix+"_dphillvsSVmass", "#Delta #phi_{ll};M_{SV} [GeV]", 150, 0, 3.14, 150, 0, 20);
    //hists2D[prefix+"_dphillvsPVSVdxy"] = new TH2F(prefix+"_dphillvsPVSVdxy", "#Delta #phi_{ll};L_{xy} [cm]", 150, 0, 3.14, 150, 0, 60);
    //hists2D[prefix+"_lprovenance"] = new TH2F(prefix+"_lprovenance", "", 19, 0, 19, 19, 0, 19);
    //hists2D[prefix+"_lprovenanceCompressed"] = new TH2F(prefix+"_lprovenanceCompressed", "", 5, 0, 5, 5, 0, 5);
}


void mini_analyzer::add_pfn_histograms(TString prefix)
{
    //hists2D[prefix+"_PFNvsdphill"]      = new TH2F(prefix+"_PFNvsdphill", ";PFN output; #Delta #phi_{ll}", 40, 0, 1, 40, 0, 3.14);
    //hists2D[prefix+"_PFNvsmll"]         = new TH2F(prefix+"_PFNvsmll", ";PFN output; M_{ll} [GeV]", 40, 0, 1, 40, 0, 150);
    hists2D[prefix+"_PFNvsmlSV"]        = new TH2F(prefix+"_PFNvsmlSV", ";PFN output; M_{l,SV} [GeV]", 40, 0, 1, 40, 0, 150);
    hists[prefix+"_JetTagVal"]          = new TH1F(prefix+"_JetTagVal", ";Jet Tag Value;Events", 20, 0, 1);
    hists[prefix+"_JetTagVal_zoom"]     = new TH1F(prefix+"_JetTagVal_zoom", ";Jet Tag Value;Events", 10, 0.9, 1);
    hists[prefix+"_PV-SVdxy_zoom"]  = new TH1F(prefix+"_PV-SVdxy_zoom", ";L_{xy} [cm];Events", 10, 0, 50);
    hists[prefix+"_SVmass"]         = new TH1F(prefix+"_SVmass", ";SV Mass [GeV];Events", 10, 0, 20);
}


void mini_analyzer::add_Shape_SR_histograms(TString prefix)
{
    if(prefix.Contains("_mm") or prefix.Contains("_ee") or prefix.Contains("_em") or prefix.Contains("_me")){
        TString Shape_SRname    = prefix+"_Shape_SR";
        int nbins = 12;
        if(prefix.Contains("_SS") and prefix.Contains("_M-10_")) nbins = 11;
        hists[Shape_SRname]     = new TH1F(Shape_SRname, ";#Delta (PV-SV)_{2D} [cm];Events", nbins, 0, nbins);

        std::vector<TString> binnames;
        if(prefix.Contains("_M-5_")){
            binnames = {"0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10"};
        }else if(prefix.Contains("_SS") and prefix.Contains("_M-10_")){
            binnames = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", ">1"};
        }else if(prefix.Contains("_M-10_")){
            binnames = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
        }
        for(unsigned i = 1; i <= binnames.size(); ++i){
            hists[Shape_SRname]->GetXaxis()->SetBinLabel(i, binnames[i-1]);
        }
        hists[Shape_SRname]->SetCanExtend(false);
    }
    else if(prefix.Contains("_2l")){
        hists[prefix+"_Shape_SR"]       = new TH1F(prefix+"_Shape_SR", ";#Delta (PV-SV)_{2D} [cm];Events", 46, 0, 46);
        hists["_OS"+prefix+"_Shape_SR"]       = new TH1F("_OS"+prefix+"_Shape_SR", ";#Delta (PV-SV)_{2D} [cm];Events", 24, 0, 24);
        int nbins = 24;
        if(prefix.Contains("_M-10_")) nbins = 22;
        hists["_SS"+prefix+"_Shape_SR"]       = new TH1F("_SS"+prefix+"_Shape_SR", ";#Delta (PV-SV)_{2D} [cm];Events", nbins, 0, nbins);
        std::vector<TString> binnames_OS, binnames_SS;
        if(prefix.Contains("_M-5_")){
            binnames_OS = {"0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10"};
            binnames_SS = {"0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10"};
        }else if(prefix.Contains("_M-10_")){
            binnames_OS = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
            binnames_SS = {"0-1", "1-5", ">5", "0-1", ">1", "0-1", "1-5", ">5", "0-1", ">1", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
        }
        for(unsigned i = 1; i <= binnames_OS.size(); ++i){
            hists["_OS"+prefix+"_Shape_SR"]->GetXaxis()->SetBinLabel(i, binnames_OS[i-1]);
        }
        for(unsigned i = 1; i <= binnames_SS.size(); ++i){
            hists["_SS"+prefix+"_Shape_SR"]->GetXaxis()->SetBinLabel(i, binnames_SS[i-1]);
        }
        hists["_OS"+prefix+"_Shape_SR"]->SetCanExtend(false);
        hists["_SS"+prefix+"_Shape_SR"]->SetCanExtend(false);
    }
}

void mini_analyzer::add_Shape_SR_extra_histograms(TString prefix)
{
    if(prefix.Contains("_mm") or prefix.Contains("_ee") or prefix.Contains("_em") or prefix.Contains("_me")){
        TString Shape_SRname    = prefix+"_Shape_SR_unw";
        TString Shape_alphaname = prefix+"_Shape_alpha";
        TString Shape_alphaname_unw = prefix+"_Shape_alpha_unw";
        int nbins = 12;
        if(prefix.Contains("_SS") and prefix.Contains("_M-10_")) nbins = 11;
        hists[Shape_SRname]     = new TH1F(Shape_SRname, ";#Delta (PV-SV)_{2D} [cm];Events", nbins, 0, nbins);
        hists[Shape_alphaname]  = new TH1F(Shape_alphaname, ";#Delta (PV-SV)_{2D} [cm];Events", 6, 0, 6);
        hists[Shape_alphaname_unw]  = new TH1F(Shape_alphaname_unw, ";#Delta (PV-SV)_{2D} [cm];Events", 6, 0, 6);

        std::vector<TString> binnames;
        if(prefix.Contains("_M-5_")){
            binnames = {"0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10"};
        }else if(prefix.Contains("_SS") and prefix.Contains("_M-10_")){
            binnames = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", ">1"};
        }else if(prefix.Contains("_M-10_")){
            binnames = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
        }
        for(unsigned i = 1; i <= binnames.size(); ++i){
            hists[Shape_SRname]->GetXaxis()->SetBinLabel(i, binnames[i-1]);
            if(i < 7) hists[Shape_alphaname]->GetXaxis()->SetBinLabel(i, binnames[i-1]);
            if(i < 7) hists[Shape_alphaname_unw]->GetXaxis()->SetBinLabel(i, binnames[i-1]);
        }
        hists[Shape_SRname]->SetCanExtend(false);
        hists[Shape_alphaname]->SetCanExtend(false);
        hists[Shape_alphaname_unw]->SetCanExtend(false);
    }
    else if(prefix.Contains("_2l")){
        hists[prefix+"_Shape_alpha"]       = new TH1F(prefix+"_Shape_alpha", ";#Delta (PV-SV)_{2D} [cm];Events", 24, 0, 24);
        hists[prefix+"_Shape_alpha_unw"]       = new TH1F(prefix+"_Shape_alpha_unw", ";#Delta (PV-SV)_{2D} [cm];Events", 24, 0, 24);
        hists2D["_OS"+prefix+"_Shape_PFN"]    = new TH2F("_OS"+prefix+"_Shape_PFN", ";#Delta (PV-SV)_{2D} [cm];PFN output", 24, 0, 24, 10000, 0, 1);
        hists2D["_SS"+prefix+"_Shape_PFN"]    = new TH2F("_SS"+prefix+"_Shape_PFN", ";#Delta (PV-SV)_{2D} [cm];PFN output", 24, 0, 24, 10000, 0, 1);
        hists["_OS"+prefix+"_Shape_SR_unw"]       = new TH1F("_OS"+prefix+"_Shape_SR_unw", ";#Delta (PV-SV)_{2D} [cm];Events", 24, 0, 24);
        hists["_SS"+prefix+"_Shape_SR_unw"]       = new TH1F("_SS"+prefix+"_Shape_SR_unw", ";#Delta (PV-SV)_{2D} [cm];Events", 24, 0, 24);
        std::vector<TString> binnames_OS, binnames_SS;
        if(prefix.Contains("_M-5_")){
            binnames_OS = {"0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10"};
            binnames_SS = {"0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10"};
        }else if(prefix.Contains("_M-10_")){
            binnames_OS = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
            binnames_SS = {"0-1", "1-5", ">5", "0-1", ">1", "0-1", "1-5", ">5", "0-1", ">1", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
        }
        for(unsigned i = 1; i <= binnames_OS.size(); ++i){
            hists[prefix+"_Shape_alpha"]->GetXaxis()->SetBinLabel(i, binnames_OS[i-1]);
            hists[prefix+"_Shape_alpha_unw"]->GetXaxis()->SetBinLabel(i, binnames_OS[i-1]);
            hists["_OS"+prefix+"_Shape_SR_unw"]->GetXaxis()->SetBinLabel(i, binnames_OS[i-1]);
        }
        for(unsigned i = 1; i <= binnames_SS.size(); ++i){
            hists["_SS"+prefix+"_Shape_SR_unw"]->GetXaxis()->SetBinLabel(i, binnames_SS[i-1]);
        }
        hists[prefix+"_Shape_alpha"]->SetCanExtend(false);
        hists[prefix+"_Shape_alpha_unw"]->SetCanExtend(false);
        hists["_OS"+prefix+"_Shape_SR_unw"]->SetCanExtend(false);
        hists["_SS"+prefix+"_Shape_SR_unw"]->SetCanExtend(false);
    }
}


void mini_analyzer::fill_histograms()
{
    for(const auto& ABCDtag : ABCDtags){
        if(isData and ABCDtag.Contains("_quadA") and not ABCDtag.Contains("CR")) continue;// don't fill region A histograms for data

        TString mv2tag = ABCDtag(0,ABCDtag.Index("_cut"));
        //TString mv2tag = ABCDtag(0,ABCDtag.Index("_CP"));//gridscan
        unsigned i_JetTagVal = MV2tags[mv2tag];

        if(mv2tag.Contains("2e-06") or mv2tag.Contains("4e-06") or mv2tag.Contains("7e-05")){
            fill_standard_histograms(sr_flavor + ABCDtag, event._weight * event._reweighting_weight[i_JetTagVal]);
            if(ABCDtag.Contains("cutbaselinemlSV") or ABCDtag.Contains("cutinsidemlSV") or ABCDtag.Contains("cutoutsidemlSV")){
                fill_pfn_histograms(     sr_flavor + ABCDtag, event._weight * event._reweighting_weight[i_JetTagVal], i_JetTagVal);
            }
            fill_Shape_SR_extra_histograms(sr_flavor,  ABCDtag, event._weight * event._reweighting_weight[i_JetTagVal], i_JetTagVal);
        }
        //fill_fraction_histograms(sr_flavor + ABCDtag, event._weight * event._reweighting_weight[i_JetTagVal]);
        fill_Shape_SR_histograms(sr_flavor,  ABCDtag, event._weight * event._reweighting_weight[i_JetTagVal]);
        //if(ABCDtag.Contains("_quadB_")){
        //    fill_Shape_SR_histograms(sr_flavor, ABCDtag + "_unw", 1.);
        //}

        // Add variations for systematic uncertainty plots
        double nominal_weight = event._weight * event._reweighting_weight[i_JetTagVal];
        set_variations(nominal_weight);
        if(ABCDtag.Contains("TightmlSV_quadA")){
            for(const auto& it : variations){
                fill_Shape_SR_histograms(sr_flavor, ABCDtag + it.first, it.second);
            }
        }
    }
}

void mini_analyzer::init_variations()
{
    variations["_Trigger_sysUp"]    = 1.;
    variations["_Trigger_sysDown"]  = 1.;
    variations["_PileUp_sysUp"]     = 1.;
    variations["_PileUp_sysDown"]   = 1.;
    variations["_l1ID_sysUp"]       = 1.;
    variations["_l1ID_sysDown"]     = 1.;
    variations["_l2ID_sysUp"]       = 1.;
    variations["_l2ID_sysDown"]     = 1.;
    variations["_Track_sysUp"]    = 1.;
    variations["_Track_sysDown"]  = 1.;
}

void mini_analyzer::set_variations(double nominal_weight)
{
    variations["_l1ID_sysUp"]       = nominal_weight * ( 1 + sqrt(event._l1_IDSF_unc_sym / event._l1_IDSF * event._l1_IDSF_unc_sym / event._l1_IDSF + event._l1_ISOSF_unc_sym / event._l1_ISOSF * event._l1_ISOSF_unc_sym / event._l1_ISOSF));
    variations["_l1ID_sysDown"]     = nominal_weight * ( 1 - sqrt(event._l1_IDSF_unc_sym / event._l1_IDSF * event._l1_IDSF_unc_sym / event._l1_IDSF + event._l1_ISOSF_unc_sym / event._l1_ISOSF * event._l1_ISOSF_unc_sym / event._l1_ISOSF));
    variations["_l2ID_sysUp"]       = nominal_weight * ( 1 + event._l1_IDSF_unc_sym / event._l1_IDSF);
    variations["_l2ID_sysDown"]     = nominal_weight * ( 1 - event._l1_IDSF_unc_sym / event._l1_IDSF);
    variations["_Track_sysUp"]      = nominal_weight * ( 1 + event._TrackSF_unc_sym / event._TrackSF);
    variations["_Track_sysDown"]    = nominal_weight * ( 1 - event._TrackSF_unc_sym / event._TrackSF);
    variations["_Trigger_sysUp"]    = nominal_weight * ( 1 + event._TriggerSF_unc_sym / event._TriggerSF);
    variations["_Trigger_sysDown"]  = nominal_weight * ( 1 - event._TriggerSF_unc_sym / event._TriggerSF);
    variations["_PileUp_sysUp"]     = nominal_weight * ( 1 + event._PileUpSF_unc_up / event._PileUpSF);
    variations["_PileUp_sysDown"]   = nominal_weight * ( 1 - event._PileUpSF_unc_down / event._PileUpSF);
}

void mini_analyzer::fill_fraction_histograms(TString prefix, double event_weight)
{
    double binnr;
    if(prefix.Contains("_quadA")) binnr = 0.;
    else if(prefix.Contains("_quadB")) binnr = 1.;
    else if(prefix.Contains("_quadC")) binnr = 2.;
    else binnr =3.;
    prefix = prefix(0, prefix.Index("_quad"));

    double SRShapebin = get_SRShapebin(event._SV_PVSVdist_2D, event._SV_mass);
    double SRShape2bin = get_SRShape2bin(event._SV_PVSVdist_2D, prefix);

    hists[prefix+"_QuadFractions"]->Fill(binnr, event_weight);
    hists[prefix+"_QuadFractions_unw"]->Fill(binnr);
    hists2D[prefix+"_QuadFractions_2D"]->Fill(SRShapebin, binnr, event_weight);
    hists2D[prefix+"_QuadFractions2_2D"]->Fill(SRShape2bin, binnr, event_weight);
}


void mini_analyzer::fill_standard_histograms(TString prefix, double event_weight)
{
    //hists[prefix+"_Yield"]->Fill(0., event_weight);
    //hists[prefix+"_SRShape"]->Fill(get_SRShapebin(event._SV_PVSVdist_2D, event._SV_mass), event_weight);
    //hists[prefix+"_SRShape2"]->Fill(get_SRShape2bin(event._SV_PVSVdist_2D, prefix), event_weight);
    //hists[prefix+"_nTightJet"]->Fill(event._nTightJet,event_weight);         
    //hists[prefix+"_JetPt"]->Fill(event._JetPt,event_weight);             
    //hists[prefix+"_JetEta"]->Fill(event._JetEta,event_weight);            
    //hists[prefix+"_JetPhi"]->Fill(event._JetPhi,event_weight);
    //hists[prefix+"_nTightLep"]->Fill(event._nTightLep,event_weight);         
    hists[prefix+"_l2_pt"]->Fill(event._lPt,event_weight);             
    //hists[prefix+"_l2_eta"]->Fill(event._lEta,event_weight);            
    //hists[prefix+"_l2_phi"]->Fill(event._lPhi,event_weight);
    //hists[prefix+"_l2_dxy"]->Fill(event._ldxy,event_weight);
    //hists[prefix+"_l2_dz"]->Fill(event._ldz,event_weight);
    //hists[prefix+"_l2_3dIPSig"]->Fill(event._l3dIPSig,event_weight);        
    //hists[prefix+"_l2_reliso"]->Fill(event._lrelIso,event_weight);         
    //hists[prefix+"_l2_ptratio"]->Fill(event._lptRatio,event_weight);
    //hists[prefix+"_l2_ptrel"]->Fill(event._lptRel,event_weight);
    //hists[prefix+"_l2_NumberOfHits"]->Fill(event._lNumberOfHits,event_weight);
    //hists[prefix+"_l2_NumberOfPixHits"]->Fill(event._lNumberOfPixelHits,event_weight);
    
    //hists[prefix+"_l1_pt"]->Fill(event._l1Pt,event_weight);             
    //hists[prefix+"_l1_eta"]->Fill(event._l1Eta,event_weight);            
    //hists[prefix+"_l1_phi"]->Fill(event._l1Phi,event_weight);
                                       
    hists[prefix+"_mll"]->Fill(event._mll,event_weight);               
    //hists[prefix+"_dRll"]->Fill(event._dRll,event_weight);              
    //hists[prefix+"_dphill"]->Fill(event._dphill,event_weight);
    //hists[prefix+"_dRljet"]->Fill(event._dRljet,event_weight);            
                                       
    hists[prefix + "_PV-SVdxy"]->Fill(event._SV_PVSVdist_2D,event_weight);
    //hists[prefix+"_PV-SVdxy_zoom2"]->Fill(event._SV_PVSVdist_2D,event_weight);
    //hists[prefix+"_PV-SVdxyz"]->Fill(event._SV_PVSVdist,event_weight);
    //hists[prefix+"_PV-SVdxyz_zoom"]->Fill(event._SV_PVSVdist,event_weight);
    //hists[prefix+"_ntracks"]->Fill(event._SV_ntracks,event_weight);
    //hists[prefix+"_SVmass2"]->Fill(event._SV_mass,event_weight);
    hists[prefix+"_SVl1mass"]->Fill(event._SV_l1mass,event_weight);
    //hists[prefix+"_SVpt"]->Fill(event._SV_pt,event_weight);
    //hists[prefix+"_SVeta"]->Fill(event._SV_eta,event_weight);
    //hists[prefix+"_SVphi"]->Fill(event._SV_phi,event_weight);
    //hists[prefix+"_SVnormchi2"]->Fill(event._SV_normchi2,event_weight);

    //hists2D[prefix+"_mllvsSVmass"]->Fill(event._mll, event._SV_mass, event_weight);
    //hists2D[prefix+"_mllvsPVSVdxy"]->Fill(event._mll, event._SV_PVSVdist_2D, event_weight);
    //hists2D[prefix+"_dphillvsSVmass"]->Fill(event._dphill, event._SV_mass, event_weight);
    //hists2D[prefix+"_dphillvsPVSVdxy"]->Fill(event._dphill, event._SV_PVSVdist_2D, event_weight);
    //hists2D[prefix+"_lprovenance"]->Fill(event._l1Provenance, event._lProvenance, event_weight);
    //hists2D[prefix+"_lprovenanceCompressed"]->Fill(event._l1ProvenanceCompressed, event._lProvenanceCompressed, event_weight);
}


void mini_analyzer::fill_pfn_histograms(TString prefix, double event_weight, unsigned i)
{
    //hists2D[prefix+"_PFNvsdphill"]->Fill(event._JetTagVal[i], event._dphill, event_weight);
    //hists2D[prefix+"_PFNvsmll"]->Fill(event._JetTagVal[i], event._mll, event_weight);
    hists2D[prefix+"_PFNvsmlSV"]->Fill(event._JetTagVal[i], event._SV_l1mass, event_weight);
    hists[prefix+"_JetTagVal"]->Fill(event._JetTagVal[i], event_weight);
    hists[prefix+"_JetTagVal_zoom"]->Fill(event._JetTagVal[i], event_weight);
    hists[prefix+"_PV-SVdxy_zoom"]->Fill(event._SV_PVSVdist_2D,event_weight);
    hists[prefix+"_SVmass"]->Fill(event._SV_mass,event_weight);
}

void mini_analyzer::fill_Shape_SR_histograms(TString sr_flavor, TString ABCDtag, double event_weight)
{
    double SRShapebin = get_SRShape3bin(event._SV_PVSVdist_2D, event._SV_mass, ABCDtag, sr_flavor);//gives 0,1,2,3,4,5 based on L_xy and SVmass
    double SRShapebin_OSSS = SRShapebin;
    if(sr_flavor.Contains("_SS")) SRShapebin += 6.;

    TString fl;
    if(sr_flavor.Contains("_mm")) fl = "_mm";
    if(sr_flavor.Contains("_ee")) fl = "_ee";
    if(sr_flavor.Contains("_me")) fl = "_me";
    if(sr_flavor.Contains("_em")) fl = "_em";


    hists[fl + ABCDtag + "_Shape_SR"]->Fill(SRShapebin, event_weight);


    double _2lbin = 0., _2lbin_OSSS = 0.;
    if(sr_flavor.Contains("_SS") and ABCDtag.Contains("M-10")){
        if(sr_flavor.Contains("_em")){      _2lbin += 11.; _2lbin_OSSS += 5.;}
        else if(sr_flavor.Contains("_ee")){ _2lbin += 22.; _2lbin_OSSS += 10.;}
        else if(sr_flavor.Contains("_me")){ _2lbin += 34.; _2lbin_OSSS += 16.;}
    }else{
        if(sr_flavor.Contains("_em")){      _2lbin += 12.; _2lbin_OSSS += 6.;}
        else if(sr_flavor.Contains("_ee")){ _2lbin += 24.; _2lbin_OSSS += 12.;}
        else if(sr_flavor.Contains("_me")){ _2lbin += 36.; _2lbin_OSSS += 18.;}
    }
    hists["_2l" + ABCDtag + "_Shape_SR"]->Fill(SRShapebin + _2lbin, event_weight);
    hists[sr_flavor(0,3) + "_2l" + ABCDtag + "_Shape_SR"]->Fill(SRShapebin_OSSS + _2lbin_OSSS, event_weight);

}

void mini_analyzer::fill_Shape_SR_extra_histograms(TString sr_flavor, TString ABCDtag, double event_weight, unsigned i)
{
    double SRShapebin = get_SRShape3bin(event._SV_PVSVdist_2D, event._SV_mass, ABCDtag, sr_flavor);//gives 0,1,2,3,4,5 based on L_xy and SVmass
    double SRShapebin_OSSS = SRShapebin;
    if(sr_flavor.Contains("_SS")) SRShapebin += 6.;

    TString fl;
    if(sr_flavor.Contains("_mm")) fl = "_mm";
    if(sr_flavor.Contains("_ee")) fl = "_ee";
    if(sr_flavor.Contains("_me")) fl = "_me";
    if(sr_flavor.Contains("_em")) fl = "_em";


    hists[fl + ABCDtag + "_Shape_alpha"]->Fill(SRShapebin_OSSS, event_weight);
    hists[fl + ABCDtag + "_Shape_SR_unw"]->Fill(SRShapebin);
    hists[fl + ABCDtag + "_Shape_alpha_unw"]->Fill(SRShapebin_OSSS);


    double _2lbin = 0., _2lbin_OSSS = 0.;
    if(sr_flavor.Contains("_SS") and ABCDtag.Contains("M-10")){
        if(sr_flavor.Contains("_em")){      _2lbin += 11.; _2lbin_OSSS += 5.;}
        else if(sr_flavor.Contains("_ee")){ _2lbin += 22.; _2lbin_OSSS += 10.;}
        else if(sr_flavor.Contains("_me")){ _2lbin += 34.; _2lbin_OSSS += 16.;}
    }else{
        if(sr_flavor.Contains("_em")){      _2lbin += 12.; _2lbin_OSSS += 6.;}
        else if(sr_flavor.Contains("_ee")){ _2lbin += 24.; _2lbin_OSSS += 12.;}
        else if(sr_flavor.Contains("_me")){ _2lbin += 36.; _2lbin_OSSS += 18.;}
    }
    hists["_2l" + ABCDtag + "_Shape_alpha"]->Fill(SRShapebin_OSSS + _2lbin_OSSS, event_weight);
    hists["_2l" + ABCDtag + "_Shape_alpha_unw"]->Fill(SRShapebin_OSSS + _2lbin_OSSS);
    hists2D[sr_flavor(0,3) + "_2l" + ABCDtag + "_Shape_PFN"]->Fill(SRShapebin_OSSS + _2lbin_OSSS, event._JetTagVal[i], event_weight);
    hists[sr_flavor(0,3) + "_2l" + ABCDtag + "_Shape_SR_unw"]->Fill(SRShapebin_OSSS + _2lbin_OSSS);

}


void mini_analyzer::sum_quad_histograms()
{
    if(!isData){
        sum_histograms_based_on_tags("_quadA_", "_quadB_", "_quadAB_");
        sum_histograms_based_on_tags("_quadA_", "_quadC_", "_quadAC_");
    }
    sum_histograms_based_on_tags("_quadB_", "_quadD_", "_quadBD_");
    sum_histograms_based_on_tags("_quadC_", "_quadD_", "_quadCD_");
    sum_histograms_based_on_tags("_quadB_", "_quadCD_", "_quadBCD_");

    if(!isData) sum_histograms_based_on_tags("_quadAB_", "_quadCD_", "_quadABCD_");
}


void mini_analyzer::sum_histograms_based_on_tags(TString base_tag, TString second_tag, TString target_tag)
{
    for(const auto& hist : hists){
        TString histname = hist.first;
        if(histname.Contains("sys")) continue;
        TH1* h           = hist.second;
        if(histname.Contains(base_tag)){
            TString histname_second = histname;
            TString histname_combined  = histname;
            histname_second.ReplaceAll(base_tag, second_tag);
            histname_combined.ReplaceAll(base_tag, target_tag);

            if(hists[histname_combined] and hists[histname_second]){
                hists[histname_combined]->Add(h, hists[histname_second]);
            }
        }
    }

    for(const auto& hist : hists2D){
        TString histname = hist.first;
        if(histname.Contains("sys")) continue;
        TH2* h           = hist.second;
        if(histname.Contains(base_tag)){
            TString histname_second = histname;
            TString histname_combined  = histname;
            histname_second.ReplaceAll(base_tag, second_tag);
            histname_combined.ReplaceAll(base_tag, target_tag);

            if(hists2D[histname_combined] and hists2D[histname_second]){
                hists2D[histname_combined]->Add(h, hists2D[histname_second]);
            }
        }
    }
}

double mini_analyzer::get_SRShapebin(double PVSVdist_2D, double SV_mass)
{
    if(PVSVdist_2D < 10 and SV_mass <= 4) return 0.;
    else if(PVSVdist_2D > 10 and SV_mass <= 4) return 1.;
    else if(PVSVdist_2D < 10 and SV_mass > 4) return 2.;
    return 3.;
}

double mini_analyzer::get_SRShape2bin(double PVSVdist_2D, TString tagForMass)
{
    //Low Mass
    if(tagForMass.Contains("M-2") or tagForMass.Contains("M-3") or tagForMass.Contains("M-4") or tagForMass.Contains("M-5")){
        if(PVSVdist_2D < 5)  return 0.;
        if(PVSVdist_2D < 10) return 1.;
        else return 2.;
    //High Mass
    }else if(tagForMass.Contains("M-6") or tagForMass.Contains("M-8") or tagForMass.Contains("M-10") or tagForMass.Contains("M-12") or tagForMass.Contains("M-14")){
        if(PVSVdist_2D < 3) return 0.;
        if(PVSVdist_2D < 6) return 1.;
        else return 2.;
    }else {
        std::cout << "Error in get_SRShape2bin: There is no mass tag in the ABCDtag present, using Low Mass definitions of signal region bins" << std::endl;
        if(PVSVdist_2D < 5)  return 0.;
        if(PVSVdist_2D < 10) return 1.;
        else return 2.;
    }
}

double mini_analyzer::get_SRShape3bin(double PVSVdist_2D, double SV_mass, TString tagForMass, TString sr_flavor)
{
    //Low Mass
    if(tagForMass.Contains("M-1_") or tagForMass.Contains("M-2_") or tagForMass.Contains("M-3") or tagForMass.Contains("M-4") or tagForMass.Contains("M-5")){
        if(SV_mass < 2.){
            if(PVSVdist_2D < 4)  return 0.;
            if(PVSVdist_2D < 10) return 1.;
            else return 2.;
        }else {
            if(PVSVdist_2D < 4) return 3.;
            if(PVSVdist_2D < 10) return 4.;
            else return 5.;
        }
    //High Mass
    }else if(tagForMass.Contains("M-6") or tagForMass.Contains("M-7") or tagForMass.Contains("M-8") or tagForMass.Contains("M-9") or tagForMass.Contains("M-10") or tagForMass.Contains("M-11") or tagForMass.Contains("M-12") or tagForMass.Contains("M-13") or tagForMass.Contains("M-14") or tagForMass.Contains("M-15")){
        if(SV_mass < 6.){
            if(PVSVdist_2D < 1) return 0.;
            if(PVSVdist_2D < 5) return 1.;
            else return 2.;
        }else {
            if(PVSVdist_2D < 1) return 3.;
            if(sr_flavor == "_SS_em" or sr_flavor == "_SS_mm") return 4.; //For HighMass SS em and SS mm both in 2016 as in 1718 for bins with SVmass > 6GeV, we have no prediction in bin > 5cm, therefore we merge it with bin 1-5cm
            else if(PVSVdist_2D < 5) return 4.;
            else return 5.;
        }
    }else {
        std::cout << "Error in get_SRShape2bin: There is no mass tag in the ABCDtag present, using Low Mass definitions of signal region bins" << std::endl;
        if(SV_mass < 2.){
            if(PVSVdist_2D < 4)  return 0.;
            if(PVSVdist_2D < 10) return 1.;
            else return 2.;
        }else {
            if(PVSVdist_2D < 4) return 3.;
            if(PVSVdist_2D < 10) return 4.;
            else return 5.;
        }
    }
}

double mini_analyzer::get_SRShape4bin(double PVSVdist_2D, double SV_mass)
{
    if(SV_mass < 5.){
        if(PVSVdist_2D < 4.) return 0.;
        else if(PVSVdist_2D < 10.) return 1.;
        else return 2.;
    }else {
        if(PVSVdist_2D < 1.) return 3.;
        else if(PVSVdist_2D < 5.) return 4.;
        else return 5.;
    }
}

void mini_analyzer::set_error_for_zero_event_bins(TString hname_target, TString hname_ratio)
{
    for(int i = 1; i <= hists[hname_target]->GetNbinsX(); i++){
        if(hists[hname_target]->GetBinContent(i) < 1e-4){
            if(hname_ratio != "") hists[hname_target]->SetBinError(i, hists[hname_ratio]->GetBinContent(i));
            else hists[hname_target]->SetBinError(i, 1.);
        }
    }
}

void mini_analyzer::set_quadA_zero_event_bins()
{
    for(auto const& it : hists){
        TString hname = it.first;
        TH1* h = it.second;
        if(hname.Contains("_quadA_")){
            for(int i = 1; i <= h->GetNbinsX(); i++){
                if(h->GetBinContent(i) < 1e-4){
                    h->SetBinContent(i, 0);
                    h->SetBinError(i, 0);
                }
            }
            //set_error_for_zero_event_bins(hname, "");
        }
    }
}
