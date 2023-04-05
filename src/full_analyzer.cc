//Include header for this class
#include "../interface/full_analyzer.h"


using namespace std;


//  run_over_file		: This is the main function to loop over events of a certain file, it does the main event selection and delegates to other functions
//  'filename' is the file containing the events over which we will run
//  'cross_section' is the cross section of the process, for HNL, this is taken from the HNL data file
//  'max_entries' is the maximal entry over which must be ran, if its 50000, then we will run over the first 50000 events, if its -1, all events will be ran
//  'partition' is the number of jobs that the file will be split in, if 5, then the code knows it is 1 of 5 jobs running over this file
//  'partitionjobnumber' is the number of the particular job in the partition, so if it's 3 and partition is 5, then this code will run over the third fraction of events if they are divided in 5 fractions
void full_analyzer::run_over_file(TString filename, double cross_section, int max_entries, int partition, int partitionjobnumber)
{
// Short description of program flow:
//     - initialize file
//     - initialize histograms
//     - start loop over events
//     - construct booleans for object selection? should be done at ntuplizer level, but all used variables should be included too
//     - functions for every signal region event selection

    bool makeMajToDirac = true; // set true if you want to set event weights so that majorana HNL samples can be interpreted as if they were dirac HNL samples. will add '_Dirac' to filename.
    TString tree_identifier = "_highlPt"; // set this identifier however you like. I use it as identifier name when making small changes to compare to.
    if(makeMajToDirac) tree_identifier += "_Dirac";

    std::vector<TString> filenames;
    filenames.push_back(filename);

    if(filename == "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MiniAOD2016/dilep_final.root"){
        filenames.push_back("/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MiniAOD2016/dilep_final.root");
    }
    if(filename == "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MiniAOD2016/dilep_final.root"){
        filenames.push_back("/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MiniAOD2016/dilep_final.root");
    }
    if(filename == "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD2017/dilep_final.root"){
        filenames.push_back("/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/MiniAOD2017/dilep_final.root");
    }
    if(filename == "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/MiniAOD2018/dilep_final.root"){
        filenames.push_back("/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD2018/dilep_final.root");
    }
    //if(filename == "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_MiniAOD2017v2-v1_dilepton_MC_2017_v8_missingLumis/210416_111422/0000/dilep_120.root"){
    //    filenames.push_back("/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_MiniAOD2017v2-v1_dilepton_MC_2017_v8_TT_missingLumis/210425_131940/0000/dilep_23.root");
    //}


    TChain *chain = new TChain("blackJackAndHookers/blackJackAndHookersTree");
    for(const auto& fn : filenames){
        chain->Add(fn);
    }

    //TFile *input = new TFile(filename, "open");
    //TTree *tree  = (TTree*) input->Get("blackJackAndHookers/blackJackAndHookersTree");
    Init(chain);
    chain->GetEntry(0);

    extensive_plots = true;
    bool makeJECvariations = true;

    SetSampleTypes(filename);
    HNL_param = new HNL_parameters(local_dir + "data/HNL_parameters/availableHeavyNeutrinoSamples.txt", filename);
    HNL_param->Set_Merging_parameters();

    if(isSignal){
        filePutContents("/user/bvermass/public/2l2q_analysis/log/MV2_points_" + (std::string)HNL_param->flavor + "_" + (_is2017? "2017" : (_is2018? "2018" : "2016")) + ".txt", (std::string)get_MV2name(HNL_param->mass, HNL_param->V2) + "\n", true);
        filePutContents("/user/bvermass/public/2l2q_analysis/log/Mctau_points_" + (std::string)HNL_param->flavor + "_" + (_is2017? "2017" : (_is2018? "2018" : "2016")) + ".txt", (std::string)get_MV2name(HNL_param->mass, HNL_param->ctau) + "\n", true);
        if(HNL_param->merged) cross_section = HNL_param->cross_section;
    }

    // Determine V2s and ctaus on which jettagger needs to be evaluated (1 mass for signal, all masses for background or data)
    evaluating_masses = {5,10};
    //evaluating_masses = {};
    //if(isSignal and HNL_param->mass != 5 and HNL_param->mass != 10) evaluating_masses.push_back(HNL_param->mass);

    for(const int& mass : evaluating_masses){
        evaluating_V2s[mass] = get_evaluating_V2s_all();
        evaluating_V2s_plots[mass] = get_evaluating_V2s_minimal();
        for(const double& V2 : evaluating_V2s[mass]){
            evaluating_ctaus[mass][V2] = get_evaluating_ctau(mass, V2, isSignal? HNL_param->flavor : "e");
            MV2name[mass][V2] = get_MV2name(mass, V2);
        }
    }

    // open the separate files to get summed hCounter histogram and summed nTrueInteractions histogram for PUWeightReader
    std::vector<double> weight_normalization;
    std::vector<TFile*> inputs;
    for(const auto& fn : filenames){
        inputs.push_back(new TFile(fn, "open"));
    }
    double hCounterValue = 0., hCounterInitial = 0.;
    if(!isData and !(isSignal and HNL_param->merged)){
        for(unsigned i = 0; i < inputs.size(); i++){
            TH1F* hCounter = (TH1F*) inputs[i]->Get("blackJackAndHookersGlobal/hCounter");
            if(!hCounter) hCounter = (TH1F*) inputs[i]->Get("blackJackAndHookers/hCounter");
            if(filenames.size() > 1) std::cout << "hCounter individual values: " << hCounter->GetBinContent(1) << " ";
            if(i == 0) hCounterInitial = hCounter->GetBinContent(1);
            weight_normalization.push_back( hCounterInitial / hCounter->GetBinContent(1) );
            hCounterValue += hCounterInitial;
        }
    }else {
        hCounterValue = 1.;
        for(unsigned i = 0; i < inputs.size(); i++){
            weight_normalization.push_back(1.);
        }
    }
    //TH1F* hCounter = (TH1F*) input->Get("blackJackAndHookersGlobal/hCounter");
    //if(!hCounter) hCounter = (TH1F*) input->Get("blackJackAndHookers/hCounter");
    //if(!isData and !(isSignal and HNL_param->merged)) hCounterValue = hCounter->GetBinContent(1);
    std::cout << std::endl << "normalization weights: ";
    for(const auto& w_normi : weight_normalization){
        std::cout << w_normi << " ";
    }std::cout << std::endl;

    // Load PU weights
    puweightreader = get_PUWeightReader(inputs);

    for(const auto& input : inputs){
        input->Close();
    }


    //This map contains all 1D histograms
    std::map<TString, TH1*> hists;
    std::map<TString, TH2*> hists2D;

    init_HLT_efficiency(&hists, "Beforeptcut");//found in src/HLT_eff.cc, does everything HLT efficiency related
    init_HLT_efficiency(&hists, "Afterptcut");//found in src/HLT_eff.cc, does everything HLT efficiency related
    //init_HLT_allevents_efficiency(&hists, "");
    init_HNL_MC_check(&hists, &hists2D);

    for(const TString &lep_region : {"_OS_ee", "_SS_ee", "_OS_mm", "_SS_mm", "_OS_em", "_SS_em", "_OS_me", "_SS_me", "_l2e", "_l2m"}){
        add_cutflow_histograms(&hists, lep_region);
        for(const TString &ev_region : {"", "_afterSV", "_Training", /*"_TooFar", */"_2prompt", "_2promptwithMll", "_2Jets", "_2JetsNoZ", "_2prompt2BJets", "_2BJets", "_2BJetsExtraCuts"}){
            add_histograms(&hists, &hists2D, lep_region + ev_region);
            //give_alphanumeric_labels(&hists, lep_region);
        }
        for(auto& MassMap : evaluating_V2s_plots){
            for(auto& V2 : MassMap.second){
                for(const TString& selection : {"", "_2Jets", "_2prompt2BJets", "_2BJets", "_2BJetsExtraCuts"}){
                    add_pfn_histograms(&hists, &hists2D, lep_region + selection + MV2name[MassMap.first][V2]);
                }
            }
        }
        for(auto& MassMap : evaluating_V2s_plots){
            add_histograms(&hists, &hists2D, lep_region + "_TrainingHighPFN_M-" + std::to_string(MassMap.first));
            add_histograms(&hists, &hists2D, lep_region + "_2BJetsHighPFN_M-" + std::to_string(MassMap.first));
            add_histograms(&hists, &hists2D, lep_region + "_2prompt2BJetsHighPFN_M-" + std::to_string(MassMap.first));
            for(auto& V2 : MassMap.second){
                for(const TString &ev_region : {"_SR"}){//, "_TrainingHighPFN", "_CRdphi", "_CRmll"}){
                    add_histograms(&hists, &hists2D, lep_region + ev_region + MV2name[MassMap.first][V2]);
                }
            }
        }
        //add_Bool_hists(&hists, lep_region);
    }
    for(const TString &lep_region : {"_mm", "_ee", "_me", "_em"}){
        add_IVF_eff_histograms(&hists, &hists2D, lep_region);
        add_HNLrecotracks_KVF_eff_histograms(&hists, lep_region);
        for(auto& MassMap : evaluating_V2s_plots){
            for(auto& V2 : MassMap.second){
                add_Shape_SR_histograms(&hists, lep_region + MV2name[MassMap.first][V2]);
            }
        }
        for(auto& MassMap : evaluating_V2s_plots){
            for(auto& V2 : MassMap.second){
                for(const TString& selection : {"", "_2Jets", "_2prompt2BJets", "_2BJets", "_2BJetsExtraCuts"}){
                    add_pfn_histograms(&hists, &hists2D, lep_region + selection + MV2name[MassMap.first][V2]);
                }
            }
        }
    }
 
    //Kshort histograms
    if(isKshortntuple){
        add_Kshort_histograms(&hists, "_mm_Kshort");
        add_Kshort_histograms(&hists, "_mm_Kshort_outsideMSV");
        add_Kshort_histograms(&hists, "_mm_Kshort_2GeV");
        add_Kshort_histograms(&hists, "_mm_Kshort_2GeV_outsideMSV");
    }

    //Conversin
    hists["Conversion_count"] = new TH1F("Conversion_count", ";;Count", 1, 0, 1);

    //assures statistical errors are dealt with correctly
    for(auto const& it : hists){
        TH1* h = it.second;
        h->Sumw2();
    }
    for(auto const& it2D : hists2D){
        TH2* h = it2D.second;
        h->Sumw2();
    }
    std::cout << "Total amount of plots: " << hists.size() << ", 2D: " << hists2D.size() << std::endl;

    // Load Lepton Scale Factors
    lsfreader_e_trig = get_LSFReader("e", "Trigger");
    lsfreader_m_trig = get_LSFReader("mu", "Trigger");
    lsfreader_e_ID   = get_LSFReader("e", "ID");
    lsfreader_m_ID   = get_LSFReader("mu", "ID");
    lsfreader_m_IDsys = get_LSFReader("mu", "IDsys");
    lsfreader_m_ISO  = get_LSFReader("mu", "ISO");

    //lsfreader_displ_m_ID = get_LSFReader_displ("mu", "IDISO");
    lsfreader_displ_m_SV = get_LSFReader_displ("mu", "SV");
    set_json_displ_e_ID();


    HNLtagger hnltagger_e(filename, "HNLtagger_electron", partition, partitionjobnumber);
    HNLtagger hnltagger_mu(filename, "HNLtagger_muon", partition, partitionjobnumber);
    //HNLtagger hnltagger_gen_e(filename, "HNLtagger_gen_electron", partition, partitionjobnumber);
    //HNLtagger hnltagger_gen_mu(filename, "HNLtagger_gen_muon", partition, partitionjobnumber);

    //Kshort HNLtagger files
    HNLtagger hnltagger_Kshort(filename, "HNLtagger_Kshort", partition, partitionjobnumber);

    // Fill a small tree with only relevant variables that might be useful for background estimation. Fill it when it passes an inclusive selection that encompasses both signal region and orthogonal regions from where to predict the background
    TString BkgEstimator_fileoption = "recreate";
    TString BkgEstimator_filename         = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/trees"+tree_identifier+"/BkgEstimator/", "BkgEstimator", partition, partitionjobnumber, true);
    TString BkgEstimator_filename_JECDown = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/trees"+tree_identifier+"/BkgEstimator/", "BkgEstimator_JECDown", partition, partitionjobnumber, true);
    TString BkgEstimator_filename_JECUp   = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/trees"+tree_identifier+"/BkgEstimator/", "BkgEstimator_JECUp", partition, partitionjobnumber, true);
    TString BkgEstimator_filename_JERDown = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/trees"+tree_identifier+"/BkgEstimator/", "BkgEstimator_JERDown", partition, partitionjobnumber, true);
    TString BkgEstimator_filename_JERUp   = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/trees"+tree_identifier+"/BkgEstimator/", "BkgEstimator_JERUp", partition, partitionjobnumber, true);
    BkgEstimator bkgestimator(BkgEstimator_filename, BkgEstimator_fileoption, hCounterValue);
    BkgEstimator bkgestimator_JECDown(BkgEstimator_filename_JECDown, BkgEstimator_fileoption, hCounterValue);
    BkgEstimator bkgestimator_JECUp(BkgEstimator_filename_JECUp, BkgEstimator_fileoption, hCounterValue);
    BkgEstimator bkgestimator_JERDown(BkgEstimator_filename_JERDown, BkgEstimator_fileoption, hCounterValue);
    BkgEstimator bkgestimator_JERUp(BkgEstimator_filename_JERUp, BkgEstimator_fileoption, hCounterValue);


    PFNReader pfn_e_LowMass = get_PFNReader_unparametrized_LowMass(0);
    PFNReader pfn_e_HighMass = get_PFNReader_unparametrized_HighMass(0);
    PFNReader pfn_mu_LowMass = get_PFNReader_unparametrized_LowMass(1);
    PFNReader pfn_mu_HighMass = get_PFNReader_unparametrized_HighMass(1);

    //these were meant to test cut flow selection, maybe should make these into histograms eventually
    std::map<TString, double> SR_counters = add_SR_counters();

    double int_lumi;
    if(_is2016) int_lumi = 36.33;
    if(_is2017) int_lumi = 41.53;
    if(_is2018) int_lumi = 59.74;

    // Determine range of events to loop over
    Long64_t nentries = chain->GetEntries();
    //cout << "full_analyzer.cc file: " << filename << endl;
    //cout << "Number of events: " << nentries << endl;
    if(max_entries == -1 || max_entries > nentries) max_entries = nentries;
    double total_weight = 1;
    if(!isData and !(isSignal and HNL_param->merged)){
        std::cout << "xsec: " << cross_section << " nentries: " << nentries << " max_entries: " << max_entries << " hCounter: " << hCounterValue << std::endl;
        total_weight = (cross_section * int_lumi * 1000. * (double)nentries / (double)max_entries) / hCounterValue; // int lumi is given in inverse picobarn, because cross_section is given in picobarn, nentries/max_entries corrects for amount of events actually ran (if only a fifth, then each weight * 5)
    }else if(isSignal and HNL_param->merged){
        total_weight = int_lumi * 1000. * (double)nentries / (double)max_entries;
    }
    std::cout << "flavor and total weight: " << HNL_param->flavor << " " << total_weight << std::endl;
    print_evaluating_points(evaluating_ctaus);
    //hweight->Scale(hweight->GetBinContent(1) * nentries / max_entries);
    
    Long64_t j_begin = floor(1.0 * max_entries * partitionjobnumber / partition);
    Long64_t j_end   = floor(1.0 * max_entries * (partitionjobnumber + 1) / partition);
    unsigned notice = ceil(0.01 * (j_end - j_begin) / 20) * 100;
    unsigned loop_counter = 0;
    cout << "j_begin j_end max_entries: " << j_begin << " " << j_end << " " << max_entries << endl;
    if(j_end - j_begin > 2000000) cout << "More than 2million events to run over! Increase partition (" << j_end - j_begin << ")" << endl;

    //main loop begins here
    for(unsigned jentry = j_begin; jentry < j_end; ++jentry){
	    chain->GetEntry(jentry);
        bool printevent = (loop_counter == notice);
	    if(printevent){
	        cout << jentry - j_begin << " of " << j_end - j_begin << endl;
            cout << "file: " << chain->GetTreeNumber() << ", base weight: " << _weight << ", norm. weight: " << weight_normalization[chain->GetTreeNumber()] << endl;
            loop_counter = 0;
	    }

        ////TString JetPt_Version = "_jetPt";
        Set_Objects_And_Relevant_Variables("_jetPt");
        ev_weight = Get_Event_weight() * weight_normalization[chain->GetTreeNumber()];
        fill_SR_counters_cutflow(SR_counters);

        // Skip data events that have the wrong leading lepton flavor, making SingleMuon and SingleElectron datasets fully orthogonal
        if((isSingleElectron and _lFlavor[i_leading] == 1) or (isSingleMuon and _lFlavor[i_leading] == 0)) continue;

        //Reweighting weights for HNL V2s, map: <V2, weight>
        for(auto& MassMap : evaluating_V2s){
            for(double V2 : MassMap.second){
                if(isSignal){
                    if(HNL_param->merged) reweighting_weights[V2] = HNL_param->get_reweighting_weight_merged(V2, _ctauHN, makeMajToDirac);
                    else reweighting_weights[V2] = get_reweighting_weight(HNL_param->V2, V2, HNL_param->ctau, _ctauHN, makeMajToDirac);
                }else {
                    reweighting_weights[V2] = 1.;
                }
            }
        }

        if(_bkgestimator or _2prompt2BJets){
            if(_lFlavor[i_subleading] == 0){
                if(makeHNLtagger and _Training) fill_HNLtagger_tree(hnltagger_e);
                JetTagVal = GetJetTagVals_LowAndHighMass(hnltagger_e, pfn_e_LowMass, pfn_e_HighMass);
            }else if(_lFlavor[i_subleading] == 1){
                if(makeHNLtagger and _Training) fill_HNLtagger_tree(hnltagger_mu);
                JetTagVal = GetJetTagVals_LowAndHighMass(hnltagger_mu, pfn_mu_LowMass, pfn_mu_HighMass);
            }
            additional_signal_regions();
            if(makeBkgEstimator) fill_BkgEstimator_tree(bkgestimator, ev_weight*total_weight, total_weight);

            SR_counters[sr_flavor]++;
            SR_counters[sr_flavor+"_weighted"] += ev_weight;
        }else {
            JetTagVal.clear();
            _TrainingHighPFN.clear();
            _2BJetsHighPFN.clear();
            _2prompt2BJetsHighPFN.clear();
            _Full.clear();
            _CR_Full_invdphi.clear();
            _CR_Full_invmll.clear();
        }


        if(makeHistograms) fill_histograms(&hists, &hists2D);
        fill_SR_counters_badleptons(SR_counters, sr_flavor, i_leading, i_subleading, gen_PVSVdist_2D, ev_weight);

        if(isSignal and makeJECvariations){
            Set_Objects_And_Relevant_Variables("_jetPt_JECDown");
            ev_weight = Get_Event_weight();
            if(_bkgestimator){
                if(_lFlavor[i_subleading] == 0) JetTagVal = GetJetTagVals_LowAndHighMass(hnltagger_e, pfn_e_LowMass, pfn_e_HighMass);
                else if(_lFlavor[i_subleading] == 1) JetTagVal = GetJetTagVals_LowAndHighMass(hnltagger_mu, pfn_mu_LowMass, pfn_mu_HighMass);
                fill_BkgEstimator_tree(bkgestimator_JECDown, ev_weight*total_weight, total_weight);
            }else {
                JetTagVal.clear();
            }

            Set_Objects_And_Relevant_Variables("_jetPt_JECUp");
            ev_weight = Get_Event_weight();
            if(_bkgestimator){
                if(_lFlavor[i_subleading] == 0) JetTagVal = GetJetTagVals_LowAndHighMass(hnltagger_e, pfn_e_LowMass, pfn_e_HighMass);
                else if(_lFlavor[i_subleading] == 1) JetTagVal = GetJetTagVals_LowAndHighMass(hnltagger_mu, pfn_mu_LowMass, pfn_mu_HighMass);
                fill_BkgEstimator_tree(bkgestimator_JECUp, ev_weight*total_weight, total_weight);
            }else {
                JetTagVal.clear();
            }

            Set_Objects_And_Relevant_Variables("_jetPt_JERDown");
            ev_weight = Get_Event_weight();
            if(_bkgestimator){
                if(_lFlavor[i_subleading] == 0) JetTagVal = GetJetTagVals_LowAndHighMass(hnltagger_e, pfn_e_LowMass, pfn_e_HighMass);
                else if(_lFlavor[i_subleading] == 1) JetTagVal = GetJetTagVals_LowAndHighMass(hnltagger_mu, pfn_mu_LowMass, pfn_mu_HighMass);
                fill_BkgEstimator_tree(bkgestimator_JERDown, ev_weight*total_weight, total_weight);
            }else {
                JetTagVal.clear();
            }

            Set_Objects_And_Relevant_Variables("_jetPt_JERUp");
            ev_weight = Get_Event_weight();
            if(_bkgestimator){
                if(_lFlavor[i_subleading] == 0) JetTagVal = GetJetTagVals_LowAndHighMass(hnltagger_e, pfn_e_LowMass, pfn_e_HighMass);
                else if(_lFlavor[i_subleading] == 1) JetTagVal = GetJetTagVals_LowAndHighMass(hnltagger_mu, pfn_mu_LowMass, pfn_mu_HighMass);
                fill_BkgEstimator_tree(bkgestimator_JERUp, ev_weight*total_weight, total_weight);
            }else {
                JetTagVal.clear();
            }
        }




        Set_Objects_And_Relevant_Variables_2prompt("_jetPt");
        ev_weight = Get_Event_weight_2prompt();
        if(_l1l2 and (_lFlavor[i_leading] == 0 or _lPt[i_leading] > 30) and ((_lFlavor[i_subleading] == 1 and _lPt[i_subleading] > 20) or (_lFlavor[i_subleading] == 0 and _lPt[i_subleading] > 27))){
            fill_general_histograms(&hists, &hists2D, sr_flavor + "_2prompt", ev_weight);
            if(mll > 15) fill_general_histograms(&hists, &hists2D, sr_flavor + "_2promptwithMll", ev_weight);
            if(_2prompt2BJets){
                fill_relevant_histograms(&hists, &hists2D, sr_flavor + "_2prompt2BJets", ev_weight);
                fill_relevant_histograms(&hists, &hists2D, sr_l2flavor + "_2prompt2BJets", ev_weight);
                for(auto& MassMap : evaluating_V2s_plots){
                    for(auto& V2 : MassMap.second){
                        if(_2prompt2BJets){
                            fill_pfn_histograms(&hists, &hists2D, sr_flavor + "_2prompt2BJets" + MV2name[MassMap.first][V2], MassMap.first, V2, ev_weight*reweighting_weights[V2]);
                            fill_pfn_histograms(&hists, &hists2D, sr_l2flavor + "_2prompt2BJets" + MV2name[MassMap.first][V2], MassMap.first, V2, ev_weight*reweighting_weights[V2]);
                        }
                    }
                }
                for(auto& MassMap : evaluating_V2s_plots){
                    if(_2prompt2BJetsHighPFN[MassMap.first][7e-5]){
                        fill_relevant_histograms(&hists, &hists2D, sr_flavor + "_2prompt2BJetsHighPFN_M-" + std::to_string(MassMap.first), ev_weight);
                        fill_relevant_histograms(&hists, &hists2D, sr_l2flavor + "_2prompt2BJetsHighPFN_M-" + std::to_string(MassMap.first), ev_weight);
                    }
                }
            }
        }
        if(isKshortntuple) Kshort_study(&hists, hnltagger_Kshort, pfn_e_LowMass, pfn_e_HighMass, pfn_mu_LowMass, pfn_mu_HighMass, ev_weight);
        Conversion_study(&hists);

        ++loop_counter;
    }
    //Small summary to write to terminal in order to quickly check state of results
    print_SR_counters(SR_counters, total_weight);
/*
 * Write everything to output:
 * 1. find output name based on input sample name
 * 2. create output TFile
 * 3. normalize histograms and make under- and overflow visible
 * 4. give necessary text bin labels
 * 5. write events to output
 */
    if(!makeHNLtagger){
        hnltagger_e.delete_HNLtagger_tree();
        hnltagger_mu.delete_HNLtagger_tree();
    }else if(HNL_param->flavor == "e"){
        hnltagger_e.write_HNLtagger_tree();
        hnltagger_mu.delete_HNLtagger_tree();
    }else if(HNL_param->flavor == "mu"){
        hnltagger_e.delete_HNLtagger_tree();
        hnltagger_mu.write_HNLtagger_tree();
    }else if(HNL_param->flavor == "2l" or HNL_param->flavor == "3l"){
        hnltagger_e.write_HNLtagger_tree();
        hnltagger_mu.write_HNLtagger_tree();
    }else {
        hnltagger_e.write_HNLtagger_tree();
        hnltagger_mu.write_HNLtagger_tree();
    }
    if(makeBkgEstimator) bkgestimator.write_tree();
    if(isSignal and makeJECvariations){
        bkgestimator_JECDown.write_tree();
        bkgestimator_JECUp.write_tree();
        bkgestimator_JERDown.write_tree();
        bkgestimator_JERUp.write_tree();
    }else if(!isSignal){
        bkgestimator_JECDown.delete_tree();
        bkgestimator_JECUp.delete_tree();
        bkgestimator_JERDown.delete_tree();
        bkgestimator_JERUp.delete_tree();
    }

    if(makeHistograms){
        //TString outputfilename = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass_PFNv9_3dIPSigPixHits/", "hists_full_analyzer", partition, partitionjobnumber, true);
        TString outputfilename;
        outputfilename = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/histograms" + tree_identifier + "/", "hists_full_analyzer", partition, partitionjobnumber, true);
        cout << "output to: " << outputfilename << endl;
        TFile *output = new TFile(outputfilename, "recreate");

        Combine_PFN_ROC_flavor_states(&hists);

        std::cout << "Scale histograms to total_weight and add under- and overflow to last bins, then write them" << std::endl;
        for(auto const& it : hists){
            TH1* h = it.second;
            fix_overflow_and_negative_bins(h);
            if(((TString)h->GetName()).Index("_eff_") == -1) h->Scale(total_weight); //this scaling now happens before the plotting stage, since after running, the histograms need to be hadded.
	        h->Write(h->GetName(), TObject::kOverwrite);
        }
        // Normalize 2D histograms to correct total weight and write them
        for(auto const& it2D : hists2D){
            TH2* h = it2D.second;
            if(((TString)h->GetName()).Index("_eff_") == -1) h->Scale(total_weight);
            h->Write(h->GetName(), TObject::kOverwrite);
        }

        // This is a histogram with 1 bin that is filled with value 1.
        // After hadding files together, this allows to see how many were hadded together.
        // This was used for efficiency histograms that were elevated by number of hadded files. at the moment it is not used anymore (efficiencies are calculated after hadding, in plotting step)
        TH1F* hadd_counter = new TH1F("hadd_counter", "nr. of files hadded together;;", 1, 0, 1);
        hadd_counter->Fill(0);
        hadd_counter->Write();

        //hweight->Write();
        std::cout << "close file" << std::endl;
        output->Close();
    }
}

void full_analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L full_analyzer.cc
//      root> full_analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;
    }
}
