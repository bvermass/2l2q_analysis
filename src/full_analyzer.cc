
//Include C++ libraries
#include <iostream>
#include <fstream>

//Include header for this class
#include "../interface/full_analyzer.h"


//Include ROOT header files
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TSystem.h>

using namespace std;

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


    sampleflavor = "bkg";
    if(filename.Index("_e_") != -1) sampleflavor = "e";
    else if(filename.Index("_mu_") != -1) sampleflavor = "mu";

    TString promptordisplaced = "";
    if(filename.Index("prompt") != -1) promptordisplaced = "prompt";
    else if(filename.Index("displaced") != -1) promptordisplaced = "displaced";

    TFile *input = new TFile(filename, "open");
    TTree *tree  = (TTree*) input->Get("blackJackAndHookers/blackJackAndHookersTree");
    double total_weight = (cross_section * 35900) / ((TH1F*) input->Get("blackJackAndHookers/hCounter"))->GetBinContent(1);
    
    _gen_Nmass = ((TString)filename(filename.Index("_M-") + 3, filename.Index("_V-") - filename.Index("_M-") - 3)).Atof();

    //TH1F* hweight = (TH1F*) input->Get("blackJackAndHookers/hCounter");
    //hweight->Scale(hweight->GetBinContent(1) / (cross_section * 35900)); //this is the inverted weight!!! since hadd needs to be able to sum up the weights!
    
    //Find out what is different about events in Moham_noBasile.csv
    // ifstream maskinputstream;
    // maskinputstream.open("../Moham_noBasile.csv");
    // string maskline;
    // int eventnumber[57];
    // double leppt[57];
    // int i_stream = 0;
    // if(maskinputstream.is_open()) {
    //     while(!maskinputstream.eof()) {
    //         getline(maskinputstream, maskline);
    //         if(maskline == "") continue;
    //         eventnumber[i_stream] = stoi(maskline.substr(0, maskline.find(" ")));
    //         leppt[i_stream]       = stod(maskline.substr(maskline.find(" ")));
    //         cout << "nb and pt: " << eventnumber[i_stream] << ", " << leppt[i_stream] << endl;
    //         i_stream++;
    //     }
    // }
    // maskinputstream.close();
    

    Init(tree);


    //This map contains all 1D histograms
    std::map<TString, TH1*> hists;
    std::map<TString, TH2*> hists2D;

    init_sigreg_fraction(&hists);//found in src/signal_region.cc, shows fractions of events in possible signal regions with leptons and jets
    init_HLT_efficiency(&hists, "Beforeptcut");//found in src/HLT_eff.cc, does everything HLT efficiency related
    init_HLT_efficiency(&hists, "Afterptcut");//found in src/HLT_eff.cc, does everything HLT efficiency related
    init_HNL_MC_check(&hists, &hists2D);

    add_histograms(&hists, &hists2D, "_OS_e");//found in src/histo_functions.cc, basically main interesting variables for now, if this gets big, should branch to different files with clearer names
    add_histograms(&hists, &hists2D, "_SS_e");
    add_histograms(&hists, &hists2D, "_OS_mu");
    add_histograms(&hists, &hists2D, "_SS_mu");
    add_histograms(&hists, &hists2D, "_OS_e_beforevtx");
    add_histograms(&hists, &hists2D, "_SS_e_beforevtx");
    add_histograms(&hists, &hists2D, "_OS_mu_beforevtx");
    add_histograms(&hists, &hists2D, "_SS_mu_beforevtx");
    add_histograms(&hists, &hists2D, "_OS_e_beforedispl");
    add_histograms(&hists, &hists2D, "_SS_e_beforedispl");
    add_histograms(&hists, &hists2D, "_OS_mu_beforedispl");
    add_histograms(&hists, &hists2D, "_SS_mu_beforedispl");
    add_histograms(&hists, &hists2D, "_OS_e_before0jet");
    add_histograms(&hists, &hists2D, "_SS_e_before0jet");
    add_histograms(&hists, &hists2D, "_OS_mu_before0jet");
    add_histograms(&hists, &hists2D, "_SS_mu_before0jet");
    add_histograms(&hists, &hists2D, "_OS_e_beforemll");
    add_histograms(&hists, &hists2D, "_SS_e_beforemll");
    add_histograms(&hists, &hists2D, "_OS_mu_beforemll");
    add_histograms(&hists, &hists2D, "_SS_mu_beforemll");
    add_histograms(&hists, &hists2D, "_OS_e_beforedphi");
    add_histograms(&hists, &hists2D, "_SS_e_beforedphi");
    add_histograms(&hists, &hists2D, "_OS_mu_beforedphi");
    add_histograms(&hists, &hists2D, "_SS_mu_beforedphi");
    add_histograms(&hists, &hists2D, "_OS_e_invIVFgendist");
    add_histograms(&hists, &hists2D, "_SS_e_invIVFgendist");
    add_histograms(&hists, &hists2D, "_OS_mu_invIVFgendist");
    add_histograms(&hists, &hists2D, "_SS_mu_invIVFgendist");

    //assures statistical errors are dealt with correctly
    for( it = hists.begin(); it != hists.end(); it++){
        TH1* h = it->second;
        h->Sumw2();
    }
    for( it2D = hists2D.begin(); it2D != hists2D.end(); it2D++){
        TH2* h = it2D->second;
        h->Sumw2();
    }
   
    //these were meant to test cut flow selection, maybe should make these into histograms eventually
    int SSe = 0;
    int OSe = 0;
    int SSmu = 0;
    int OSmu = 0;
    int SSe_weight = 0;
    int OSe_weight = 0;
    int SSmu_weight = 0;
    int OSmu_weight = 0;

    int count = 0;

    // Determine range of events to loop over
    Long64_t nentries = tree->GetEntries();
    //cout << "full_analyzer.cc file: " << filename << endl;
    //cout << "Number of events: " << nentries << endl;
    if(max_entries == -1 || max_entries > nentries) max_entries = nentries;
    total_weight = 1.0 * nentries / max_entries * total_weight; //Correct weight for the amount of events that is actually ran
    //hweight->Scale(hweight->GetBinContent(1) * nentries / max_entries);
    
    Long64_t j_begin = floor(1.0 * max_entries * partitionjobnumber / partition);
    Long64_t j_end   = floor(1.0 * max_entries * (partitionjobnumber + 1) / partition);
    std::cout << "j_begin j_end max_entries: " << j_begin << " " << j_end << " " << max_entries << std::endl;

    //main loop begins here
    for(unsigned jentry = j_begin; jentry < j_end; ++jentry){
	    LoadTree(jentry);
	    tree->GetEntry(jentry);
        unsigned notice = ceil(0.01 * (j_end - j_begin) / 20) * 100;
	    bool printevent = ((jentry -j_begin)%notice == 0);
	    if(printevent){
	        cout << jentry - j_begin << " of " << j_end - j_begin << endl;
	    }

        //bool matchmask = false;
        ////use Moham_noBasile.csv mask
        //for(int i = 0; i < 57; i++){
        //    //if(_eventNb == eventnumber[i]){
        //        //cout << "eventNb match, pt:";
        //        for(unsigned j = 0; j < _nL; j++){
        //            if(fabs(_lPt[j] - leppt[i]) <  0.0001){
        //                matchmask == true;
        //                count++;
        //                //cout << " " << _lPt[j] << " - " << leppt[i] << " eventnb: " << _eventNb << " " << eventnumber[i] << endl;
        //            }
        //        }
        //    //}
        //}
        //if(!matchmask) continue;
            //cout << "what";
            //cout << "nL, nJets, IsoTkMu24, IsoMu24: " << _nL << " " << _nJets << " " << _HLT_IsoTkMu24 << " " << _HLT_IsoMu24 << endl;
            //for(unsigned i = 0; i < _nL; i++){
            //    cout << "l pt, eta, phi, reliso, IVF_match: " << _lPt[i] << " " << _lEta[i] << " " << _lPhi[i] << " " << _relIso0p4MuDeltaBeta[i] << " " << _lIVF_match[i] << endl;
            //}

        //Calculate Event weight
        //if(filename.Index("HeavyNeutrino") == -1) event_weight = _weight; //WHEN WEIGHTS ARE CORRECT CHANGE THIS SO CORRECT WEIGHTS ARE ALSO USED FOR HEAVYNEUTRINO SAMPLES
        event_weight = _weight;

        fix_validity_of_lIVF_match();
	    
        //Get ID
	    get_electronID(&fullElectronID[0]);
        get_loose_electronID(&looseElectronID[0]);
	    get_displ_electronID(&olddisplElectronID[0]);
        get_new_displ_electronID(&displElectronID[0]);
	    get_muonID(&fullMuonID[0]);
        get_loose_muonID(&looseMuonID[0]);
	    get_displ_muonID(&olddisplMuonID[0]);
	    get_new_displ_muonID(&displMuonID[0]);
	    get_jetID(&fullJetID[0]);


        //Get Cleaning for jets
	    get_clean_jets(&jet_clean_full[0],   &fullElectronID[0], &fullMuonID[0]);
	    get_clean_jets(&jet_clean_displ[0],  &displElectronID[0], &displMuonID[0]);
        get_clean_jets(&old_jet_clean_displ[0], &olddisplElectronID[0], &olddisplMuonID[0]);
        get_clean_jets(&jet_clean_loose[0],  &looseElectronID[0], &looseMuonID[0]);
	    for(unsigned i = 0; i < 20; ++i){
	        jet_clean_full_displ[i] = jet_clean_full[i] && jet_clean_displ[i];
	        old_jet_clean_full_displ[i] = jet_clean_full[i] && old_jet_clean_displ[i];
	    }
	    
        //Get cleaning for electrons
	    get_clean_ele(&ele_clean_full[0],   &fullMuonID[0]);
	    get_clean_ele(&ele_clean_displ[0],  &displMuonID[0]);
	    get_clean_ele(&old_ele_clean_displ[0],  &olddisplMuonID[0]);
	    get_clean_ele(&old_ele_clean_loose[0],  &olddisplMuonID[0]);
        get_clean_ele(&ele_clean_loose[0], &looseMuonID[0]);
	    for(unsigned i = 0; i < 10; ++i){
	        ele_clean_full_displ[i] = ele_clean_full[i] && ele_clean_displ[i];
	        old_ele_clean_full_displ[i] = ele_clean_full[i] && old_ele_clean_displ[i];
	    }

        //Find leptons and jets with leading pt
	    i_leading_e     		    = find_leading_e(&fullElectronID[0], &ele_clean_loose[0]);
	    i_subleading_e  		    = find_subleading_e(&fullElectronID[0], &ele_clean_loose[0], i_leading_e);
	    i_leading_mu    		    = find_leading_mu(&fullMuonID[0]);
	    i_subleading_mu 		    = find_subleading_mu(&fullMuonID[0], i_leading_mu);
	    i_subleading_displ_e  	    = find_subleading_e(&displElectronID[0], &ele_clean_loose[0], i_leading_e);
	    i_old_subleading_displ_e  	= find_subleading_e(&olddisplElectronID[0], &old_ele_clean_loose[0], i_leading_e);
	    i_subleading_displ_mu 	    = find_subleading_mu(&displMuonID[0], i_leading_mu);
	    i_old_subleading_displ_mu 	= find_subleading_mu(&olddisplMuonID[0], i_leading_mu);
	    
	    i_leading_jet	    = find_leading_jet(&fullJetID[0], &jet_clean_loose[0]);
	    i_subleading_jet	= find_subleading_jet(&fullJetID[0], &jet_clean_loose[0], i_leading_jet);
        i_thirdleading_jet  = find_thirdleading_jet(&fullJetID[0], &jet_clean_loose[0], i_leading_jet, i_subleading_jet);


        //make sure we are either in e or mu signal region. Based on leading lepton with highest pt.
        if(i_leading_e != -1 and i_leading_mu != -1){
            if(_lPt[i_leading_e] > _lPt[i_leading_mu]) i_leading_mu = -1;
            else i_leading_e = -1;
        }

        //get signal region booleans
        signal_regions();
        
        // Find gen level leptons matching to the leading and subleading lepton (geometrically when its background or data, pgdID when its signal
        i_gen_leading_e             = find_gen_lep(i_leading_e);                //finds closest dR match
        i_gen_subleading_displ_e    = find_gen_lep(i_subleading_displ_e);
        i_gen_leading_mu            = find_gen_lep(i_leading_mu);
        i_gen_subleading_displ_mu   = find_gen_lep(i_subleading_displ_mu);
        
        
        find_gen_l1_and_l2();                                                   //finds HNL process l1 and l2 gen leptons
        if(_1e1disple) match_gen_and_reco(i_subleading_displ_e);                //sets booleans true if leading and subleading match l1 and l2
        if(_1mu1displmu) match_gen_and_reco(i_subleading_displ_mu);
        
        // Fill histograms
        
        fill_sigreg_fraction(&hists);
        fill_HNL_MC_check(&hists, &hists2D);
        fill_HLT_efficiency(&hists, "Beforeptcut", (i_leading_e != -1), (i_leading_mu != -1));
        fill_HLT_efficiency(&hists, "Afterptcut", (i_leading_e != -1 && leadptcut("e")), (i_leading_mu != -1 && leadptcut("mu")));

        fill_cutflow_e(&hists, "_SS_e");
        fill_cutflow_e(&hists, "_OS_e");
        fill_cutflow_mu(&hists, "_SS_mu");
        fill_cutflow_mu(&hists, "_OS_mu");


        TString signs_and_flavor = "";
        if(_1e1disple) signs_and_flavor = (_lCharge[i_leading_e] == _lCharge[i_subleading_displ_e])? "_SS_e" : "_OS_e";
        else if(_1mu1displmu) signs_and_flavor = (_lCharge[i_leading_mu] == _lCharge[i_subleading_displ_mu])? "_SS_mu" : "_OS_mu"; 
        

        if(_1e1disple){
            fill_corrl2_eff(&hists, signs_and_flavor, i_subleading_displ_e, i_gen_subleading_displ_e);
            fill_KVF_eff(&hists, signs_and_flavor, i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
            fill_IVF_eff(&hists, signs_and_flavor, i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
            fill_histograms(&hists, signs_and_flavor + "_beforevtx", i_leading_e, i_subleading_displ_e);
        }
        if(_1mu1displmu){
            fill_corrl2_eff(&hists, signs_and_flavor, i_subleading_displ_mu, i_gen_subleading_displ_mu);
            fill_KVF_eff(&hists, signs_and_flavor, i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
            fill_IVF_eff(&hists, signs_and_flavor, i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
            fill_histograms(&hists, signs_and_flavor + "_beforevtx", i_leading_mu, i_subleading_displ_mu);
        }

        if(_1e1displevtx){
            fill_histograms(&hists, signs_and_flavor + "_beforedispl", i_leading_e, i_subleading_displ_e);
            fill_IVF_histograms(&hists, &hists2D, signs_and_flavor, i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
        }
        if(_1mu1displmuvtx){
            fill_histograms(&hists, signs_and_flavor + "_beforedispl", i_leading_mu, i_subleading_displ_mu);
            fill_IVF_histograms(&hists, &hists2D, signs_and_flavor, i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
        }
        
        if(_1e1displedispl){
            fill_histograms(&hists, signs_and_flavor + "_before0jet", i_leading_e, i_subleading_displ_e);
        }
        if(_1mu1displmudispl){
            fill_histograms(&hists, signs_and_flavor + "_before0jet", i_leading_mu, i_subleading_displ_mu);
        }

        if(_1e1disple0jet){
            fill_histograms(&hists, signs_and_flavor + "_beforemll", i_leading_e, i_subleading_displ_e);
        }
        if(_1mu1displmu0jet){
            fill_histograms(&hists, signs_and_flavor + "_beforemll", i_leading_mu, i_subleading_displ_mu);
        }
        
        if(_1e1disple0jet_aftermll){
            fill_histograms(&hists, signs_and_flavor + "_beforedphi", i_leading_e, i_subleading_displ_e);
        }
        if(_1mu1displmu0jet_aftermll){
            fill_histograms(&hists, signs_and_flavor + "_beforedphi", i_leading_mu, i_subleading_displ_mu);
        }

        if(_1e1disple0jet_afterdphi){
            fill_histograms(&hists, signs_and_flavor, i_leading_e, i_subleading_displ_e);
            fill_KVF_histograms(&hists, &hists2D, signs_and_flavor, i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
            fill_IVF_histograms(&hists, &hists2D, signs_and_flavor, i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
            if(i_gen_subleading_displ_e != -1 and _lIVF_match[i_subleading_displ_e] != -1 and get_IVF_gendist(i_gen_subleading_displ_e, _lIVF_match[i_subleading_displ_e]) > 0.2) fill_IVF_histograms(&hists, &hists2D, signs_and_flavor + "_invIVFgendist", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);

            if(signs_and_flavor == "_SS_e"){ SSe++; SSe_weight += event_weight;}
            else if(signs_and_flavor == "_OS_e"){ OSe++; OSe_weight += event_weight;}
        }
        if(_1mu1displmu0jet_afterdphi){
            fill_histograms(&hists, signs_and_flavor, i_leading_mu, i_subleading_displ_mu);
            fill_KVF_histograms(&hists, &hists2D, signs_and_flavor, i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
            fill_IVF_histograms(&hists, &hists2D, signs_and_flavor, i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
            if(i_gen_subleading_displ_mu != -1 and _lIVF_match[i_subleading_displ_mu] != -1 and get_IVF_gendist(i_gen_subleading_displ_mu, _lIVF_match[i_subleading_displ_mu]) > 0.2) fill_IVF_histograms(&hists, &hists2D, signs_and_flavor + "_invIVFgendist", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);

            if(signs_and_flavor == "_SS_mu"){ SSmu++; SSmu_weight += event_weight;}
            else if(signs_and_flavor == "_OS_mu"){ OSmu++; OSmu_weight += event_weight;}
        }
    }
/*
 * Small summary to write to terminal in order to quickly check state of results
 */
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "Channel    #events     #events(with ind. weight)    #events(with tot. weight)" << endl;
    cout << "SS ee:       " << SSe <<  "        " << SSe_weight <<  "       " << 1.0*SSe_weight*total_weight << endl;
    cout << "SS mumu:     " << SSmu << "        " << SSmu_weight << "       " << 1.0*SSmu_weight*total_weight << endl;
    cout << "OS ee:       " << OSe <<  "        " << OSe_weight <<  "       " << 1.0*OSe_weight*total_weight << endl;
    cout << "OS mumu:     " << OSmu << "        " << OSmu_weight << "       " << 1.0*OSmu_weight*total_weight << endl;
    cout << "count:       " << count << endl;


/*
 * Write everything to output
 * output name is based on input sample name
 */
    TString outputfilename = "/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/";
    
    if(partition != 1) {
        outputfilename += "subfiles/";
        if(filename.Index("HeavyNeutrino") != -1) outputfilename += filename(filename.Index("HeavyNeutrino_"), filename.Index("dilep.root") - 1 - filename.Index("HeavyNeutrino_")) + "_" + promptordisplaced + "/";
        else outputfilename += "Background_" + filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep.root") - filename.Index("heavyNeutrino") - 15) + "/";
    }
    
    gSystem->Exec("mkdir -p " + outputfilename);

    if(filename.Index("HeavyNeutrino") != -1) outputfilename += "hists_full_analyzer_" + filename(filename.Index("HeavyNeutrino_"), filename.Index("dilep.root") - 1 - filename.Index("HeavyNeutrino_")) + "_" + promptordisplaced;
    else outputfilename += "hists_full_analyzer_Background_" + filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep.root") - filename.Index("heavyNeutrino") - 15);
    
    if(partition != 1) outputfilename += "_job_" + to_string(static_cast<long long>(partitionjobnumber)) + ".root";
    else outputfilename += ".root";

    
    cout << "output to: " << outputfilename << endl;
    TFile *output = new TFile(outputfilename, "recreate");

    for( it = hists.begin(); it != hists.end(); it++){
        TH1* h = it->second;
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
    for( it2D = hists2D.begin(); it2D != hists2D.end(); it2D++){
        TH2* h = it2D->second;
        if(((TString)h->GetName()).Index("_eff_") == -1) h->Scale(total_weight);
    }

    give_alphanumeric_labels(&hists, "_SS_e");
    give_alphanumeric_labels(&hists, "_OS_e");
    give_alphanumeric_labels(&hists, "_SS_mu");
    give_alphanumeric_labels(&hists, "_OS_mu");


    for( it = hists.begin(); it != hists.end(); it++){
        TH1* h = it->second;
	    h->Write();
    }

    for( it2D = hists2D.begin(); it2D != hists2D.end(); it2D++){
        TH2* h = it2D->second;
        h->Write();
    }

    TH1F* hadd_counter = new TH1F("hadd_counter", "nr. of files hadded together;;", 1, 0, 1);
    hadd_counter->Fill(0);
    hadd_counter->Write();

    //hweight->Write();
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
