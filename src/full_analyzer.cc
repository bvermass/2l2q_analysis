//Include header for this class
#include "../interface/full_analyzer.h"


using namespace std;

TString local_dir = "/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_14/src/2l2q_analysis/";

//  run_over_file		: This is the main function to loop over events of a certain file, it does the main event selection and delegates to other functions
//  'filename' is the file containing the events over which we will run
//  'cross_section' is the cross section of the process
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

    extensive_plots = false;

    SetSampleTypes(filename);

    //TString promptordisplaced = "";
    //if(filename.Index("prompt") != -1) promptordisplaced = "prompt";
    //else if(filename.Index("displaced") != -1) promptordisplaced = "displaced";

    TFile *input = new TFile(filename, "open");
    TTree *tree  = (TTree*) input->Get("blackJackAndHookers/blackJackAndHookersTree");
    
    
    if(sampleflavor == "e" or sampleflavor == "mu"){
        _gen_Nmass = ((TString)filename(filename.Index("_M-") + 3, filename.Index("_V-") - filename.Index("_M-") - 3)).Atof();
        _gen_NV    = ((TString)filename(filename.Index("_V-") + 3, filename.Index("_" + sampleflavor + "_") - filename.Index("_V-") - 3)).Atof();
        _gen_Nctau  = get_mean_ctau(sampleflavor, _gen_Nmass, _gen_NV);
        evaluating_masses = {_gen_Nmass};//controls which masses will be evaluated in the HNLtagger, for signal, only its own mass
        filePutContents("/user/bvermass/public/2l2q_analysis/log/MV2_points_" + (std::string)sampleflavor + ".txt", (std::string)get_MV2name(_gen_Nmass, _gen_NV*_gen_NV) + "\n", true);
    }else {
        _gen_Nmass = 0;
        _gen_NV    = 0;
        _gen_Nctau  = 0;
        evaluating_masses = {2, 3, 4, 5, 6, 8, 10, 15};
    }

    // Determine V2s and ctaus on which jettagger needs to be evaluated (1 mass for signal, all masses for background or data)
    for(const int& mass : evaluating_masses){
        evaluating_V2s[mass] = get_evaluating_V2s_short(mass);
        for(const double& V2 : evaluating_V2s[mass]){
            evaluating_ctaus[mass][V2] = get_evaluating_ctau(mass, V2);
            MV2name[mass][V2] = get_MV2name(mass, V2);
        }
    }


    //TH1F* hweight = (TH1F*) input->Get("blackJackAndHookers/hCounter");
    //hweight->Scale(hweight->GetBinContent(1) / (cross_section * 35900)); //this is the inverted weight!!! since hadd needs to be able to sum up the weights!
    
    Init(tree);

    //This map contains all 1D histograms
    std::map<TString, TH1*> hists;
    std::map<TString, TH2*> hists2D;

    //init_HLT_efficiency(&hists, "Beforeptcut");//found in src/HLT_eff.cc, does everything HLT efficiency related
    //init_HLT_efficiency(&hists, "Afterptcut");//found in src/HLT_eff.cc, does everything HLT efficiency related
    //init_HLT_allevents_efficiency(&hists, "");

    for(const TString &lep_region : {"_mm", "_ee"}){
        for(const TString &ev_region : {""}){
            add_histograms(&hists, &hists2D, lep_region + ev_region);
            give_alphanumeric_labels(&hists, lep_region);
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
    //TString filename_PUWeights = local_dir + "data/PUWeights/PUWeights_2016_XSecCentral.root";
    //TString filename_PUWeights = local_dir + "data/PUWeights/PUWeights_2017_XSecCentral.root";
    TString filename_PUWeights = local_dir + "data/PUWeights/PUWeights_2018_XSecCentral.root";
    TString histname_PUWeights = "PUWeights";
    PUWeightReader puweightreader(filename_PUWeights, histname_PUWeights);

    // Load Lepton Scale Factors (these are for 2018 METResolution task, don't have them yet for HNL analysis)
    TString filename_LSF_e = local_dir + "data/LeptonScaleFactors/2018_ElectronTight.root";
    TString histname_LSF_e = "EGamma_SF2D";
    LSFReader lsfreader_e(filename_LSF_e, histname_LSF_e, "e");
    TString filename_LSF_mu = local_dir + "data/LeptonScaleFactors/RunABCD_SF_ID.root";
    TString histname_LSF_mu = "NUM_TightID_DEN_TrackerMuons_pt_abseta";
    LSFReader lsfreader_mu(filename_LSF_mu, histname_LSF_mu, "mu");
   
    //HNLtagger hnltagger_e(filename, "HNLtagger_electron", partition, partitionjobnumber);
    //HNLtagger hnltagger_mu(filename, "HNLtagger_muon", partition, partitionjobnumber);
    //HNLtagger hnltagger_gen_e(filename, "HNLtagger_gen_electron", partition, partitionjobnumber);
    //HNLtagger hnltagger_gen_mu(filename, "HNLtagger_gen_muon", partition, partitionjobnumber);

    //HNLBDTtagger hnlbdttagger_e(filename, "HNLBDTtagger_electron", partition, partitionjobnumber);
    //HNLBDTtagger hnlbdttagger_mu(filename, "HNLBDTtagger_muon", partition, partitionjobnumber);

    std::map<TString, double> SR_counters = add_SR_counters();

    // Determine range of events to loop over
    Long64_t nentries = tree->GetEntries();
    if(max_entries == -1 || max_entries > nentries) max_entries = nentries;
    double total_weight = 1;
    if(sampleflavor.Index("Run") == -1){ 
        total_weight = (cross_section * 59690 * nentries / max_entries) / ((TH1F*) input->Get("blackJackAndHookers/hCounter"))->GetBinContent(1); // 35900 is in inverse picobarn, because cross_section is given in picobarn, nentries/max_entries corrects for amount of events actually ran (if only a fifth, then each weight * 5)
    }
    std::cout << "sampleflavor and total weight: " << sampleflavor << " " << total_weight << std::endl;
    print_evaluating_points(evaluating_ctaus);
    //hweight->Scale(hweight->GetBinContent(1) * nentries / max_entries);
    
    Long64_t j_begin = floor(1.0 * max_entries * partitionjobnumber / partition);
    Long64_t j_end   = floor(1.0 * max_entries * (partitionjobnumber + 1) / partition);
    unsigned notice = ceil(0.01 * (j_end - j_begin) / 20) * 100;
    cout << "j_begin j_end max_entries: " << j_begin << " " << j_end << " " << max_entries << endl;
    if(j_end - j_begin > 2000000) cout << "More than 2million events to run over! Increase partition (" << j_end - j_begin << ")" << endl;

    //main loop begins here
    for(unsigned jentry = j_begin; jentry < j_end; ++jentry){
	    tree->GetEntry(jentry);
	    bool printevent = ((jentry -j_begin)%notice == 0);
	    if(printevent){
	        cout << jentry - j_begin << " of " << j_end - j_begin << endl;
	    }


        //Calculate Event weight
        if(sampleflavor.Index("Run") == -1) ev_weight = _weight * puweightreader.get_PUWeight(_nTrueInt);
        else ev_weight = 1;

        //Get ID
        get_electronID();
        get_loose_electronID();
        get_muonID();
        get_loose_muonID();
        get_jetID();


        //Get Cleaning for jets
	    get_clean_jets(&jet_clean_full[0],   &fullElectronID[0], &fullMuonID[0]);
	    get_clean_ele(&ele_clean_full[0],   &fullMuonID[0]);
        get_clean_ele(&ele_clean_loose[0], &looseMuonID[0]);

	    int i_leading_e     		    = find_leading_e(&fullElectronID[0], &ele_clean_full[0]);
	    int i_leading_mu    		    = find_leading_mu(&fullMuonID[0]);

        i_leading = select_leading_lepton(i_leading_e, i_leading_mu);

	    int i_subleading_e  		    = find_subleading_e(&fullElectronID[0], &ele_clean_full[0], i_leading);
	    int i_subleading_mu 		    = find_subleading_mu(&fullMuonID[0], i_leading);

	    i_leading_jet                   = find_leading_jet(&fullJetID[0], &jet_clean_full[0]);
	    i_subleading_jet	            = find_subleading_jet(&fullJetID[0], &jet_clean_full[0], i_leading_jet);
        i_thirdleading_jet              = find_thirdleading_jet(&fullJetID[0], &jet_clean_full[0], i_leading_jet, i_subleading_jet);


        set_leptons(i_subleading_e, i_subleading_mu);
        signal_regions();
        
        fill_histograms(&hists, &hists2D);
        SR_counters[sr_flavor]++;
        SR_counters[sr_flavor+"_weighted"] += ev_weight;
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
    //if(sampleflavor == "e"){
    //    hnltagger_e.write_HNLtagger_tree();
    //    hnltagger_mu.delete_HNLtagger_tree();
    //    hnltagger_gen_e.write_HNLtagger_tree();
    //    hnltagger_gen_mu.delete_HNLtagger_tree();
    //    hnlbdttagger_e.write_HNLBDTtagger_tree();
    //    hnlbdttagger_mu.delete_HNLBDTtagger_tree();
    //}else if(sampleflavor == "mu"){
    //    hnltagger_e.delete_HNLtagger_tree();
    //    hnltagger_mu.write_HNLtagger_tree();
    //    hnltagger_gen_e.delete_HNLtagger_tree();
    //    hnltagger_gen_mu.write_HNLtagger_tree();
    //    hnlbdttagger_e.delete_HNLBDTtagger_tree();
    //    hnlbdttagger_mu.write_HNLBDTtagger_tree();
    //}else {
    //    hnltagger_e.write_HNLtagger_tree();
    //    hnltagger_mu.write_HNLtagger_tree();
    //    hnltagger_gen_e.delete_HNLtagger_tree();
    //    hnltagger_gen_mu.delete_HNLtagger_tree();
    //    hnlbdttagger_e.write_HNLBDTtagger_tree();
    //    hnlbdttagger_mu.write_HNLBDTtagger_tree();
    //}

    TString outputfilename = make_outputfilename(filename, "/user/bvermass/public/MET_scale_resolution/histograms/", "hists_full_analyzer", partition, partitionjobnumber);
    cout << "output to: " << outputfilename << endl;
    TFile *output = new TFile(outputfilename, "recreate");

    // Add under- and overflow to first and last bins and normalize histograms to correct total weight.
    for(auto const& it : hists){
        TH1* h = it.second;
        if(((TString)h->GetName()).Index("_meanqT") == -1){
            int nb = h->GetNbinsX();
            double b0  = h->GetBinContent( 0  );
            double e0  = h->GetBinError  ( 0  );
            double b1  = h->GetBinContent( 1  );
            double e1  = h->GetBinError  ( 1  );
            double bn  = h->GetBinContent(nb  );
            double en  = h->GetBinError  (nb  );
            double bn1 = h->GetBinContent(nb+1);
            double en1 = h->GetBinError  (nb+1);

            h->SetBinContent(0   , 0.);
            h->SetBinError  (0   , 0.);
            h->SetBinContent(1   , b0+b1);
            h->SetBinError  (1   , std::sqrt(e0*e0 + e1*e1  ));
            h->SetBinContent(nb  , bn+bn1);
            h->SetBinError  (nb  , std::sqrt(en*en + en1*en1));
            h->SetBinContent(nb+1, 0.);
            h->SetBinError  (nb+1, 0.);

            //if bin content is below zero, set it to 0 (dealing with negative weights)
            for(int i = 0; i < nb+1; i++){
                if(h->GetBinContent(i) < 0.) h->SetBinContent(i, 0.);
            }
            if(((TString)h->GetName()).Index("_eff_") == -1) h->Scale(total_weight); //this scaling now happens before the plotting stage, since after running, the histograms need to be hadded.
        }
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
        if(jentry%1000 == 0) cout << "yeey " << jentry << endl;
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;
    }
}
