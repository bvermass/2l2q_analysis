//Include header for this class
#include "../interface/full_analyzer.h"


using namespace std;

TString local_dir = "/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_20/src/2l2q_analysis/";

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
    TFile *input = new TFile(filename, "open");
    TTree *tree  = (TTree*) input->Get("blackJackAndHookers/blackJackAndHookersTree");
    Init(tree);
    tree->GetEntry(0);

    extensive_plots = false;

    SetSampleTypes(filename);
    HNL_param = new HNL_parameters(local_dir + "data/HNL_parameters/availableHeavyNeutrinoSamples.txt", filename);
    std::cout << "---HNL param---: " << HNL_param->mass << " " << HNL_param->V2 << " " << HNL_param->ctau << std::endl;
    if(isSignal){
        filePutContents("/user/bvermass/public/2l2q_analysis/log/MV2_points_" + (std::string)sampleflavor + ".txt", (std::string)get_MV2name(HNL_param->mass, HNL_param->V2) + "\n", true);
        cross_section = HNL_param->cross_section;
    }

    // Determine V2s and ctaus on which jettagger needs to be evaluated (1 mass for signal, all masses for background or data)
    evaluating_masses = {2, 3, 4, 5, 6, 8, 10, 15};
    for(const int& mass : evaluating_masses){
        evaluating_V2s[mass] = get_evaluating_V2s_short(mass);
        for(const double& V2 : evaluating_V2s[mass]){
            evaluating_ctaus[mass][V2] = get_evaluating_ctau(mass, V2);
            MV2name[mass][V2] = get_MV2name(mass, V2);
        }
    }


    //TH1F* hweight = (TH1F*) input->Get("blackJackAndHookersGlobal/hCounter");
    //hweight->Scale(hweight->GetBinContent(1) / (cross_section * 35900)); //this is the inverted weight!!! since hadd needs to be able to sum up the weights!
    

    //This map contains all 1D histograms
    std::map<TString, TH1*> hists;
    std::map<TString, TH2*> hists2D;

    //init_HLT_efficiency(&hists, "Beforeptcut");//found in src/HLT_eff.cc, does everything HLT efficiency related
    init_HLT_efficiency(&hists, "Afterptcut");//found in src/HLT_eff.cc, does everything HLT efficiency related
    //init_HLT_allevents_efficiency(&hists, "");
    init_HNL_MC_check(&hists, &hists2D);

    for(const TString &lep_region : {"_OS_ee", "_SS_ee", "_OS_mm", "_SS_mm", "_OS_em", "_SS_em", "_OS_me", "_SS_me"}){
        for(const TString &ev_region : {"", "_Training", "_Training_nRIso", "_TooFar", "_2prompt"}){
            add_histograms(&hists, &hists2D, lep_region + ev_region);
            give_alphanumeric_labels(&hists, lep_region);
        }
        for(auto& MassMap : evaluating_ctaus){
            for(auto& V2Map : MassMap.second){
                for(const TString &ev_region : {"_SR"}){//, "_TrainingHighPFN", "_CRdphi", "_CRmll"}){
                    add_histograms(&hists, &hists2D, lep_region + ev_region + MV2name[MassMap.first][V2Map.first]);
                }
                for(const TString &ev_region : {"", "_Training"}){
                    add_pfn_histograms(&hists, lep_region + ev_region + MV2name[MassMap.first][V2Map.first]);
                }
            }
        }
        //add_Bool_hists(&hists, lep_region);
    }
    for(const TString &lep_region : {"_mm", "_ee", "_me", "_em"}){
        for(auto& MassMap : evaluating_ctaus){
            for(auto& V2Map : MassMap.second){
                add_Shape_SR_histograms(&hists, lep_region + MV2name[MassMap.first][V2Map.first]);
            }
        }
    }

    //assures statistical errors are dealt with correctly
    for(auto const& it : hists){
        TH1* h = it.second;
        h->Sumw2();
    }
    for(auto const& it2D : hists2D){
        TH2* h = it2D.second;
        h->Sumw2();
    }

    // Load PU weights
    PUWeightReader puweightreader = get_PUWeightReader(local_dir);

    // Load Lepton Scale Factors for TTH MVA
    LSFReader lsfreader_e = get_LSFReader(local_dir, "e");
    LSFReader lsfreader_m = get_LSFReader(local_dir, "mu");
   
    HNLtagger hnltagger_e(filename, "HNLtagger_electron", partition, partitionjobnumber);
    HNLtagger hnltagger_mu(filename, "HNLtagger_muon", partition, partitionjobnumber);
    HNLtagger hnltagger_gen_e(filename, "HNLtagger_gen_electron", partition, partitionjobnumber);
    HNLtagger hnltagger_gen_mu(filename, "HNLtagger_gen_muon", partition, partitionjobnumber);

    // Fill a small tree with only relevant variables that might be useful for background estimation. Fill it when it passes an inclusive selection that encompasses both signal region and orthogonal regions from where to predict the background
    BkgEstimator bkgestimator(filename, "BkgEstimator", partition, partitionjobnumber);

    //HNLBDTtagger hnlbdttagger_e(filename, "HNLBDTtagger_electron", partition, partitionjobnumber);
    //HNLBDTtagger hnlbdttagger_mu(filename, "HNLBDTtagger_muon", partition, partitionjobnumber);

    PFNReader pfn_mu("/user/bvermass/public/PFN/JetTagger/PFNmu_v7/jetTagger.h5", 25, {50, 13});
    PFNReader pfn_e("/user/bvermass/public/PFN/JetTagger/PFNe_v7/jetTagger.h5", 25, {50,13});
    PFNReader bdt_mu( "/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_20/src/deepLearning/bestModels_xgboost_HNLtagger_v2/model_rank_1/alpha=0p633294851941_colsampleBytree=0p79485523663_gamma=0p307334894388_learningRate=0p0868032444329_maxDepth=10_minChildWeight=6p66227737302_numberOfTrees=1416_subsample=0p992526187961/alpha=0p633294851941_colsampleBytree=0p79485523663_gamma=0p307334894388_learningRate=0p0868032444329_maxDepth=10_minChildWeight=6p66227737302_numberOfTrees=1416_subsample=0p992526187961.bin", 28 );

    //these were meant to test cut flow selection, maybe should make these into histograms eventually
    std::map<TString, double> SR_counters = add_SR_counters();

    double int_lumi;
    if(_is2016) int_lumi = 35.92;
    if(_is2017) int_lumi = 41.53;
    if(_is2018) int_lumi = 59.74;

    // Determine range of events to loop over
    Long64_t nentries = tree->GetEntries();
    //cout << "full_analyzer.cc file: " << filename << endl;
    //cout << "Number of events: " << nentries << endl;
    TH1F* hCounter = (TH1F*) input->Get("blackJackAndHookersGlobal/hCounter");
    if(!hCounter) hCounter = (TH1F*) input->Get("blackJackAndHookers/hCounter");
    if(max_entries == -1 || max_entries > nentries) max_entries = nentries;
    double total_weight = 1;
    if(!isData){
        std::cout << "xsec: " << cross_section << " nentries: " << nentries << " max_entries: " << max_entries << " hCounter: " << hCounter->GetBinContent(1) << std::endl;
        total_weight = (cross_section * int_lumi * 1000. * (double)nentries / (double)max_entries) / hCounter->GetBinContent(1); // int lumi is given in inverse picobarn, because cross_section is given in picobarn, nentries/max_entries corrects for amount of events actually ran (if only a fifth, then each weight * 5)
    }
    std::cout << "sampleflavor and total weight: " << sampleflavor << " " << total_weight << std::endl;
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
	    tree->GetEntry(jentry);
        bool printevent = (loop_counter == notice);
	    if(printevent){
	        cout << jentry - j_begin << " of " << j_end - j_begin << endl;
            loop_counter = 0;
	    }


        //Get muons, electrons and jets that pass ID and cleaning
        std::vector<unsigned> promptMuonID, promptElectronID, displacedMuonID, displacedElectronID, looseMuonID, looseElectronID;
        for(unsigned i = 0; i < _nLight; i++){
            if(IsPromptMuonID(i))           promptMuonID.push_back(i);
            if(IsDisplacedMuonID(i))        displacedMuonID.push_back(i);
            if(IsLooseMuonID(i))            looseMuonID.push_back(i);
        }
        nTightMu = promptMuonID.size();
        nDisplMu = displacedMuonID.size();

        for(unsigned i = 0; i < _nLight; i++){
            bool CleanElectron = IsCleanElectron(i, promptMuonID) and IsCleanElectron(i, displacedMuonID);

            if(IsPromptElectronID(i)    and CleanElectron) promptElectronID.push_back(i);
            if(IsDisplacedElectronID(i) and CleanElectron) displacedElectronID.push_back(i);
            if(IsLooseElectronID(i)     and CleanElectron) looseElectronID.push_back(i);
        }
        nTightEle = promptElectronID.size();
        nDisplEle = displacedElectronID.size();

        std::vector<unsigned> jetID, jetID_uncl;
        for(unsigned i = 0; i < _nJets; i++){
            if(IsTightJetID(i) and IsCleanJet(i, promptMuonID) and IsCleanJet(i, promptElectronID) and IsCleanJet(i, displacedMuonID) and IsCleanJet(i, displacedElectronID)) jetID.push_back(i);
            if(IsTightJetID(i)) jetID_uncl.push_back(i);
        }
        nTightJet       = jetID.size();
        nTightJet_uncl  = jetID_uncl.size();

        //Find leptons and jets with leading pt
	    int i_leading_e     		    = find_leading_lepton(promptElectronID);
	    int i_leading_mu    		    = find_leading_lepton(promptMuonID);

        i_leading = select_leading_lepton(i_leading_e, i_leading_mu);

	    int i_subleading_e  		    = find_subleading_lepton(promptElectronID, i_leading);
	    int i_subleading_displ_e  	    = find_subleading_lepton(displacedElectronID, i_leading);
	    int i_subleading_mu 		    = find_subleading_lepton(promptMuonID, i_leading);
	    int i_subleading_displ_mu 	    = find_subleading_lepton(displacedMuonID, i_leading);

	    i_leading_jet                   = find_leading_jet(jetID);
	    i_subleading_jet	            = find_subleading_jet(jetID, i_leading_jet);
        i_thirdleading_jet              = find_thirdleading_jet(jetID, i_leading_jet, i_subleading_jet);


        set_leptons(i_subleading_displ_e, i_subleading_displ_mu);
        signal_regions();


        //Calculate Event weight
        if(!isData) ev_weight = _weight * puweightreader.get_PUWeight(_nTrueInt);// * get_LSF(lsfreader_e, lsfreader_m, i_leading);
        else ev_weight = 1.;

        //Reweighting weights for HNL V2s, map: <V2, weight>
        for(auto& MassMap : evaluating_V2s){
            for(double V2 : MassMap.second){
                if(sampleflavor == "e" or sampleflavor == "mu"){
                    reweighting_weights[V2] = get_reweighting_weight(HNL_param->V2, V2, HNL_param->ctau, _ctauHN);
                }else {
                    reweighting_weights[V2] = 1.;
                }
            }
        }

        if(_Training){
            if(_lFlavor[i_subleading] == 0){
                fill_HNLtagger_tree(hnltagger_e);
                //fill_HNLBDTtagger_tree(hnlbdttagger_e, ev_weight*total_weight);
                JetTagVal = GetJetTagVals(hnltagger_e, pfn_e, 7);
            }else if(_lFlavor[i_subleading] == 1){
                fill_HNLtagger_tree(hnltagger_mu);
                //fill_HNLBDTtagger_tree(hnlbdttagger_mu, ev_weight*total_weight);
                JetTagVal = GetJetTagVals(hnltagger_mu, pfn_mu, 7);
            }
            additional_signal_regions();
            fill_BkgEstimator_tree(bkgestimator, ev_weight*total_weight);

            SR_counters[sr_flavor]++;
            SR_counters[sr_flavor+"_weighted"] += ev_weight;
        }else {
            JetTagVal.clear();
        }


        fill_histograms(&hists, &hists2D);


        if(sr_flavor == ""){
            if(i_leading == -1){
                SR_counters["no_l1"]++;
                SR_counters["no_l1_weighted"] += ev_weight;
            }else if(i_subleading == -1){
                if(gen_PVSVdist_2D > 30){
                    SR_counters["no_l2_far"]++;
                    SR_counters["no_l2_far_weighted"] += ev_weight;
                }else if(gen_PVSVdist_2D < 0.1) {
                    SR_counters["no_l2_cl"]++;
                    SR_counters["no_l2_cl_weighted"]++;
                }else {
                    SR_counters["no_l2_ot"]++;
                    SR_counters["no_l2_ot_weighted"]++;
                }
            }else {
                SR_counters["unid."]++;
            }
        }

        // after everything happened, set subleading lepton to tight prompt lepton to measure 2 lepton prompt performance
        set_leptons(i_subleading_e, i_subleading_mu);
        //if(!isData) ev_weight *= get_LSF(lsfreader_e, lsfreader_m, i_subleading);
        signal_regions();
        if(_l1l2 and _lPt[i_subleading] > 20){
            fill_relevant_histograms(&hists, &hists2D, sr_flavor + "_2prompt", ev_weight);
        }

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
    if(sampleflavor == "e"){
        hnltagger_e.write_HNLtagger_tree();
        hnltagger_mu.delete_HNLtagger_tree();
        hnltagger_gen_e.delete_HNLtagger_tree();
        hnltagger_gen_mu.delete_HNLtagger_tree();
        //hnlbdttagger_e.write_HNLBDTtagger_tree();
        //hnlbdttagger_mu.delete_HNLBDTtagger_tree();
    }else if(sampleflavor == "mu"){
        hnltagger_e.delete_HNLtagger_tree();
        hnltagger_mu.write_HNLtagger_tree();
        hnltagger_gen_e.delete_HNLtagger_tree();
        hnltagger_gen_mu.delete_HNLtagger_tree();
        //hnlbdttagger_e.delete_HNLBDTtagger_tree();
        //hnlbdttagger_mu.write_HNLBDTtagger_tree();
    }else {
        hnltagger_e.write_HNLtagger_tree();
        hnltagger_mu.write_HNLtagger_tree();
        hnltagger_gen_e.delete_HNLtagger_tree();
        hnltagger_gen_mu.delete_HNLtagger_tree();
        //hnlbdttagger_e.write_HNLBDTtagger_tree();
        //hnlbdttagger_mu.write_HNLBDTtagger_tree();
    }
    bkgestimator.write_tree();

    TString outputfilename = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/histograms/", "hists_full_analyzer", partition, partitionjobnumber, true);
    cout << "output to: " << outputfilename << endl;
    TFile *output = new TFile(outputfilename, "recreate");

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
