
//Include C++ libraries
#include <iostream>

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
    
    //TH1F* hweight = (TH1F*) input->Get("blackJackAndHookers/hCounter");
    //hweight->Scale(hweight->GetBinContent(1) / (cross_section * 35900)); //this is the inverted weight!!! since hadd needs to be able to sum up the weights!
    

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
    add_histograms(&hists, &hists2D, "_OS_e_beforemll");
    add_histograms(&hists, &hists2D, "_SS_e_beforemll");
    add_histograms(&hists, &hists2D, "_OS_mu_beforemll");
    add_histograms(&hists, &hists2D, "_SS_mu_beforemll");
    add_histograms(&hists, &hists2D, "_OS_e_beforedphi");
    add_histograms(&hists, &hists2D, "_SS_e_beforedphi");
    add_histograms(&hists, &hists2D, "_OS_mu_beforedphi");
    add_histograms(&hists, &hists2D, "_SS_mu_beforedphi");
    add_histograms(&hists, &hists2D, "_OS_e_oldID");
    add_histograms(&hists, &hists2D, "_SS_e_oldID");
    add_histograms(&hists, &hists2D, "_OS_mu_oldID");
    add_histograms(&hists, &hists2D, "_SS_mu_oldID");
    add_histograms(&hists, &hists2D, "_OS_e_invgendist");
    add_histograms(&hists, &hists2D, "_SS_e_invgendist");
    add_histograms(&hists, &hists2D, "_OS_mu_invgendist");
    add_histograms(&hists, &hists2D, "_SS_mu_invgendist");
    add_histograms(&hists, &hists2D, "_OS_e_close");
    add_histograms(&hists, &hists2D, "_SS_e_close");
    add_histograms(&hists, &hists2D, "_OS_mu_close");
    add_histograms(&hists, &hists2D, "_SS_mu_close");
    add_histograms(&hists, &hists2D, "_OS_e_far");
    add_histograms(&hists, &hists2D, "_SS_e_far");
    add_histograms(&hists, &hists2D, "_OS_mu_far");
    add_histograms(&hists, &hists2D, "_SS_mu_far");

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
    int ee_else = 0; 
    int n_ele = 0;
    int n_after_eta = 0;
    int n_after_pt = 0;
    int n_after_dxy = 0;
    int n_after_dz = 0;
    int n_after_sip3d = 0;
    int n_after_reliso = 0;
    int n_after_invreliso = 0;
    int n_after_pogmedium = 0;
    int n_after_convveto = 0;
    int n_after_missinghits = 0;
    int n_after_invreliso_pogmedium = 0;
    int n_after_invreliso_convveto = 0;
    int n_after_invreliso_missinghits = 0;
    int SSe = 0;
    int OSe = 0;
    int SSmu = 0;
    int OSmu = 0;
    int SSe_weight = 0;
    int OSe_weight = 0;
    int SSmu_weight = 0;
    int OSmu_weight = 0;

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
        unsigned notice = round(0.001 * (j_end - j_begin) / 20) * 1000;
	    bool printevent = ((jentry -j_begin)%notice == 0);
	    if(printevent){
	        cout << jentry - j_begin << " of " << j_end - j_begin << endl;
	    }

        //Calculate Event weight
        //if(filename.Index("HeavyNeutrino") == -1) event_weight = _weight; //WHEN WEIGHTS ARE CORRECT CHANGE THIS SO CORRECT WEIGHTS ARE ALSO USED FOR HEAVYNEUTRINO SAMPLES
        event_weight = _weight;

	    for(unsigned i = 0; i < _nL; ++i){
        	if(_lFlavor[i] != 0) continue;
	        ++n_ele;
	        if(fabs(_lEta[i]) < 2.5)    ++n_after_eta;
        	if(_lPt[i] > 30)            ++n_after_pt;
        	if(fabs(_dxy[i]) < 0.05)    ++n_after_dxy;
        	if(fabs(_dz[i])  < 0.1)     ++n_after_dz;
        	if(_3dIPSig[i]   < 4)       ++n_after_sip3d;
        	if(_relIso[i]    < 0.2)     ++n_after_reliso;
	        if(_relIso[i]    > 0.2)     ++n_after_invreliso;
        	if(_lPOGMedium[i])          ++n_after_pogmedium;
        	if(_lElectronPassConvVeto[i])       ++n_after_convveto;
        	if(_lElectronMissingHits[i] < 1)    ++n_after_missinghits;
	        if(_relIso[i] > 0.03 && _lPOGMedium[i])             ++n_after_invreliso_pogmedium;
	        if(_relIso[i] > 0.2 && _lElectronPassConvVeto[i])   ++n_after_invreliso_convveto;
	        if(_relIso[i] > 0.2 && _lElectronMissingHits[i])    ++n_after_invreliso_missinghits;
	    }
	    
        //Get ID
	    get_electronID(&fullElectronID[0]);
	    get_noniso_electronID(&nonisoElectronID[0]);
	    get_displ_electronID(&olddisplElectronID[0]);
        get_new_displ_electronID(&displElectronID[0]);
	    get_muonID(&fullMuonID[0]);
	    get_noniso_muonID(&nonisoMuonID[0]);
	    get_displ_muonID(&olddisplMuonID[0]);
	    get_new_displ_muonID(&displMuonID[0]);
	    get_jetID(&fullJetID[0]);

        //fill_ID_histos(&hists, "_SS_mu");
        //fill_ID_histos(&hists, "_OS_mu");
        //fill_ID_histos(&hists, "_SS_e");
        //fill_ID_histos(&hists, "_OS_e");

        //Get Cleaning for jets
	    get_clean_jets(&jet_clean_full[0],   &fullElectronID[0], &fullMuonID[0]);
	    get_clean_jets(&jet_clean_noniso[0], &nonisoElectronID[0], &nonisoMuonID[0]);
	    get_clean_jets(&jet_clean_displ[0],  &displElectronID[0], &displMuonID[0]);
        get_clean_jets(&old_jet_clean_displ[0], &olddisplElectronID[0], &olddisplMuonID[0]);
	    for(unsigned i = 0; i < 20; ++i){
	        jet_clean_full_noniso[i] = jet_clean_full[i] && jet_clean_noniso[i];
	        jet_clean_full_displ[i] = jet_clean_full[i] && jet_clean_displ[i];
	        old_jet_clean_full_displ[i] = jet_clean_full[i] && old_jet_clean_displ[i];
	    }
	    
        //Get cleaning for electrons
	    get_clean_ele(&ele_clean_full[0],   &fullMuonID[0]);
	    get_clean_ele(&ele_clean_noniso[0], &nonisoMuonID[0]);
	    get_clean_ele(&ele_clean_displ[0],  &displMuonID[0]);
	    get_clean_ele(&old_ele_clean_displ[0],  &olddisplMuonID[0]);
	    for(unsigned i = 0; i < 10; ++i){
	        ele_clean_full_noniso_displ[i] = ele_clean_full[i] && ele_clean_noniso[i] && ele_clean_displ[i];
	        old_ele_clean_full_noniso_displ[i] = ele_clean_full[i] && ele_clean_noniso[i] && old_ele_clean_displ[i];
	    }

        //Find leptons and jets with leading pt
	    i_leading_e     		    = find_leading_e(&fullElectronID[0], &ele_clean_full_noniso_displ[0]);
	    i_subleading_e  		    = find_subleading_e(&fullElectronID[0], &ele_clean_full_noniso_displ[0], i_leading_e);
	    i_leading_mu    		    = find_leading_mu(&fullMuonID[0]);
	    i_subleading_mu 		    = find_subleading_mu(&fullMuonID[0], i_leading_mu);
	    i_subleading_noniso_e  	    = find_subleading_e(&nonisoElectronID[0], &ele_clean_full_noniso_displ[0], i_leading_e);
	    i_subleading_noniso_mu 	    = find_subleading_mu(&nonisoMuonID[0], i_leading_mu);
	    i_subleading_displ_e  	    = find_subleading_e(&displElectronID[0], &ele_clean_full_noniso_displ[0], i_leading_e);
	    i_old_subleading_displ_e  	= find_subleading_e(&olddisplElectronID[0], &old_ele_clean_full_noniso_displ[0], i_leading_e);
	    i_subleading_displ_mu 	    = find_subleading_mu(&displMuonID[0], i_leading_mu);
	    i_old_subleading_displ_mu 	= find_subleading_mu(&olddisplMuonID[0], i_leading_mu);
	    
	    i_leading_jet_for_full	    = find_leading_jet(&fullJetID[0], &jet_clean_full[0]);
	    i_subleading_jet_for_full	= find_subleading_jet(&fullJetID[0], &jet_clean_full[0], i_leading_jet_for_full);
	    i_leading_jet_for_noniso	= find_leading_jet(&fullJetID[0], &jet_clean_full_noniso[0]);
	    i_subleading_jet_for_noniso	= find_subleading_jet(&fullJetID[0], &jet_clean_full_noniso[0], i_leading_jet_for_noniso);
	    i_leading_jet_for_displ	    = find_leading_jet(&fullJetID[0], &jet_clean_full_displ[0]);
	    i_old_leading_jet_for_displ	= find_leading_jet(&fullJetID[0], &old_jet_clean_full_displ[0]);
	    i_subleading_jet_for_displ	= find_subleading_jet(&fullJetID[0], &jet_clean_full_displ[0], i_leading_jet_for_displ);
	    i_old_subleading_jet_for_displ	= find_subleading_jet(&fullJetID[0], &old_jet_clean_full_displ[0], i_old_leading_jet_for_displ);


        //get signal region booleans
        signal_regions();
        
        i_vtx_subleading_displ_e    = _lIVF_match[i_subleading_displ_e];
        i_vtx_subleading_displ_mu   = _lIVF_match[i_subleading_displ_mu];
        //i_vtx_subleading_displ_e    = find_vtx_matching_to_lepton(i_subleading_displ_e);
        //i_vtx_subleading_displ_mu   = find_vtx_matching_to_lepton(i_subleading_displ_mu);
        
        i_gen_leading_e             = find_gen_lep(i_leading_e);                //finds closest dR match
        i_gen_subleading_displ_e    = find_gen_lep(i_subleading_displ_e);
        i_gen_leading_mu            = find_gen_lep(i_leading_mu);
        i_gen_subleading_displ_mu   = find_gen_lep(i_subleading_displ_mu);
        
        
        find_gen_l1_and_l2();                                                   //finds HNL process l1 and l2 gen leptons
        if(_1e1disple) match_gen_and_reco(i_subleading_displ_e);                //sets booleans true if leading and subleading match l1 and l2
        if(_1mu1displmu) match_gen_and_reco(i_subleading_displ_mu);
        
        
        fill_sigreg_fraction(&hists);
        fill_HNL_MC_check(&hists, &hists2D);
        fill_HLT_efficiency(&hists, "Beforeptcut", (i_leading_e != -1), (i_leading_mu != -1));
        fill_HLT_efficiency(&hists, "Afterptcut", (i_leading_e != -1 && leadptcut("e")), (i_leading_mu != -1 && leadptcut("mu")));

        fill_cutflow_e(&hists, "_SS_e");
        fill_cutflow_e(&hists, "_OS_e");
        fill_cutflow_mu(&hists, "_SS_mu");
        fill_cutflow_mu(&hists, "_OS_mu");

        if(_1e){
            fill_l2_and_vtx_eff(&hists, &hists2D, "_SS_e", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
            fill_l2_and_vtx_eff(&hists, &hists2D, "_OS_e", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
            fill_l2_and_vtx_eff(&hists, &hists2D, "_SS_e_oldID", i_leading_e, i_old_subleading_displ_e, i_gen_subleading_displ_e);
            fill_l2_and_vtx_eff(&hists, &hists2D, "_OS_e_oldID", i_leading_e, i_old_subleading_displ_e, i_gen_subleading_displ_e);
            fill_IVF_eff(&hists, "_SS_e", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
            fill_IVF_eff(&hists, "_OS_e", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
            fill_IVF_eff(&hists, "_SS_e_oldID", i_leading_e, i_old_subleading_displ_e, i_gen_subleading_displ_e);
            fill_IVF_eff(&hists, "_OS_e_oldID", i_leading_e, i_old_subleading_displ_e, i_gen_subleading_displ_e);
        }
        if(_1mu){
            fill_l2_and_vtx_eff(&hists, &hists2D, "_SS_mu", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
            fill_l2_and_vtx_eff(&hists, &hists2D, "_OS_mu", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
            fill_l2_and_vtx_eff(&hists, &hists2D, "_SS_mu_oldID", i_leading_mu, i_old_subleading_displ_mu, i_gen_subleading_displ_mu);
            fill_l2_and_vtx_eff(&hists, &hists2D, "_OS_mu_oldID", i_leading_mu, i_old_subleading_displ_mu, i_gen_subleading_displ_mu);
            fill_IVF_eff(&hists, "_SS_mu", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
            fill_IVF_eff(&hists, "_OS_mu", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
            fill_IVF_eff(&hists, "_SS_mu_oldID", i_leading_mu, i_old_subleading_displ_mu, i_gen_subleading_displ_mu);
            fill_IVF_eff(&hists, "_OS_mu_oldID", i_leading_mu, i_old_subleading_displ_mu, i_gen_subleading_displ_mu);
        }
        if(_1e1disple){
            if(_lCharge[i_leading_e] == _lCharge[i_subleading_displ_e]){
                fill_corrl2_eff(&hists, "_SS_e");
                fill_jetmet_variables(&hists, "_SS_e");
            }else{
                fill_corrl2_eff(&hists, "_OS_e");
                fill_jetmet_variables(&hists, "_OS_e");
            }           
        }
        if(_1mu1displmu){
            if(_lCharge[i_leading_mu] == _lCharge[i_subleading_displ_mu]){
                fill_corrl2_eff(&hists, "_SS_mu");
                fill_jetmet_variables(&hists, "_SS_mu");
            }else{
                fill_corrl2_eff(&hists, "_OS_mu");
                fill_jetmet_variables(&hists, "_OS_mu");
            }
        }

        if(_1e1disple0jet){
            if(_lCharge[i_leading_e] == _lCharge[i_subleading_displ_e]){
                fill_histograms(&hists, "_SS_e_beforemll", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                if(_lKVF_valid[i_subleading_displ_e]) fill_KVF_histograms(&hists, "_SS_e_beforemll", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                else fill_KVF_inv_histograms(&hists, "_SS_e_beforemll", i_subleading_displ_e);
            }else{
                fill_histograms(&hists, "_OS_e_beforemll", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                if(_lKVF_valid[i_subleading_displ_e]) fill_KVF_histograms(&hists, "_OS_e_beforemll", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                else fill_KVF_inv_histograms(&hists, "_OS_e_beforemll", i_subleading_displ_e);
            }           
        }
        if(_1mu1displmu0jet){
            if(_lCharge[i_leading_mu] == _lCharge[i_subleading_displ_mu]){
                fill_histograms(&hists, "_SS_mu_beforemll", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                if(_lKVF_valid[i_subleading_displ_mu]) fill_KVF_histograms(&hists, "_SS_mu_beforemll", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                else fill_KVF_inv_histograms(&hists, "_SS_mu_beforemll", i_subleading_displ_mu);
            }else{
                fill_histograms(&hists, "_OS_mu_beforemll", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                if(_lKVF_valid[i_subleading_displ_mu]) fill_KVF_histograms(&hists, "_OS_mu_beforemll", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                else fill_KVF_inv_histograms(&hists, "_OS_mu_beforemll", i_subleading_displ_mu);
            }
        }
        
        if(_1e1disple0jet_aftermll){
            if(_lCharge[i_leading_e] == _lCharge[i_subleading_displ_e]){
                fill_histograms(&hists, "_SS_e_beforedphi", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                if(_lKVF_valid[i_subleading_displ_e]) fill_KVF_histograms(&hists, "_SS_e_beforedphi", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                else fill_KVF_inv_histograms(&hists, "_SS_e_beforedphi", i_subleading_displ_e);
            }else{
                fill_histograms(&hists, "_OS_e_beforedphi", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                if(_lKVF_valid[i_subleading_displ_e]) fill_KVF_histograms(&hists, "_OS_e_beforedphi", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                else fill_KVF_inv_histograms(&hists, "_OS_e_beforedphi", i_subleading_displ_e);
            }           
        }
        if(_1mu1displmu0jet_aftermll){
            if(_lCharge[i_leading_mu] == _lCharge[i_subleading_displ_mu]){
                fill_histograms(&hists, "_SS_mu_beforedphi", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                if(_lKVF_valid[i_subleading_displ_mu]) fill_KVF_histograms(&hists, "_SS_mu_beforedphi", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                else fill_KVF_inv_histograms(&hists, "_SS_mu_beforedphi", i_subleading_displ_mu);
            }else{
                fill_histograms(&hists, "_OS_mu_beforedphi", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                if(_lKVF_valid[i_subleading_displ_mu]) fill_KVF_histograms(&hists, "_OS_mu_beforedphi", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                else fill_KVF_inv_histograms(&hists, "_OS_mu_beforedphi", i_subleading_displ_mu);
            }
        }

        if(_1e1disple0jet_afterdphi){
            if(_lCharge[i_leading_e] == _lCharge[i_subleading_displ_e]){
                fill_histograms(&hists, "_SS_e", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                if(_lKVF_valid[i_subleading_displ_e]) fill_KVF_histograms(&hists, "_SS_e", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                else fill_KVF_inv_histograms(&hists, "_SS_e", i_subleading_displ_e);
                if(_lIVF_match[i_subleading_displ_e] != -1) fill_IVF_histograms(&hists, &hists2D, "_SS_e", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                if(_lIVF_match[i_subleading_displ_e] != -1 and i_gen_l2 != -1 and get_IVF_gendist(i_gen_l2, _lIVF_match[i_subleading_displ_e]) > 0.2) fill_IVF_histograms(&hists, &hists2D, "_SS_e_invgendist", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                if(_lIVF_match[i_subleading_displ_e] != -1 and get_IVF_PVSVdist(_lIVF_match[i_subleading_displ_e]) < 10) fill_IVF_histograms(&hists, &hists2D, "_SS_e_close", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                if(_lIVF_match[i_subleading_displ_e] != -1 and get_IVF_PVSVdist(_lIVF_match[i_subleading_displ_e]) > 10) fill_IVF_histograms(&hists, &hists2D, "_SS_e_far", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                SSe++;
                SSe_weight += event_weight;
            }else{
                fill_histograms(&hists, "_OS_e", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                if(_lKVF_valid[i_subleading_displ_e]) fill_KVF_histograms(&hists, "_OS_e", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                else fill_KVF_inv_histograms(&hists, "_OS_e", i_subleading_displ_e);
                if(_lIVF_match[i_subleading_displ_e] != -1) fill_IVF_histograms(&hists, &hists2D, "_OS_e", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                if(_lIVF_match[i_subleading_displ_e] != -1 and i_gen_l2 != -1 and get_IVF_gendist(i_gen_l2, _lIVF_match[i_subleading_displ_e]) > 0.2) fill_IVF_histograms(&hists, &hists2D, "_OS_e_invgendist", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                if(_lIVF_match[i_subleading_displ_e] != -1 and get_IVF_PVSVdist(_lIVF_match[i_subleading_displ_e]) < 10) fill_IVF_histograms(&hists, &hists2D, "_OS_e_close", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                if(_lIVF_match[i_subleading_displ_e] != -1 and get_IVF_PVSVdist(_lIVF_match[i_subleading_displ_e]) > 10) fill_IVF_histograms(&hists, &hists2D, "_OS_e_far", i_leading_e, i_subleading_displ_e, i_gen_subleading_displ_e);
                OSe++;
                OSe_weight += event_weight;
            }
        }
        if(_1mu1displmu0jet_afterdphi){
            if(_lCharge[i_leading_mu] == _lCharge[i_subleading_displ_mu]){
                fill_histograms(&hists, "_SS_mu", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                if(_lKVF_valid[i_subleading_displ_mu]) fill_KVF_histograms(&hists, "_SS_mu", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                else fill_KVF_inv_histograms(&hists, "_SS_mu", i_subleading_displ_mu);
                if(_lIVF_match[i_subleading_displ_mu] != -1) fill_IVF_histograms(&hists, &hists2D, "_SS_mu", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                if(_lIVF_match[i_subleading_displ_mu] != -1 and i_gen_l2 != -1 and get_IVF_gendist(i_gen_l2, _lIVF_match[i_subleading_displ_mu]) > 0.2) fill_IVF_histograms(&hists, &hists2D, "_SS_mu_invgendist", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                if(_lIVF_match[i_subleading_displ_mu] != -1 and get_IVF_PVSVdist(_lIVF_match[i_subleading_displ_mu]) < 10) fill_IVF_histograms(&hists, &hists2D, "_SS_mu_close", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                if(_lIVF_match[i_subleading_displ_mu] != -1 and get_IVF_PVSVdist(_lIVF_match[i_subleading_displ_mu]) > 10) fill_IVF_histograms(&hists, &hists2D, "_SS_mu_far", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                SSmu++;
                SSmu_weight += event_weight;
            }else{
                fill_histograms(&hists, "_OS_mu", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                if(_lKVF_valid[i_subleading_displ_mu]) fill_KVF_histograms(&hists, "_OS_mu", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                else fill_KVF_inv_histograms(&hists, "_OS_mu", i_subleading_displ_mu);
                if(_lIVF_match[i_subleading_displ_mu] != -1) fill_IVF_histograms(&hists, &hists2D, "_OS_mu", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                if(_lIVF_match[i_subleading_displ_mu] != -1 and i_gen_l2 != -1 and get_IVF_gendist(i_gen_l2, _lIVF_match[i_subleading_displ_mu]) > 0.2) fill_IVF_histograms(&hists, &hists2D, "_OS_mu_invgendist", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                if(_lIVF_match[i_subleading_displ_mu] != -1 and get_IVF_PVSVdist(_lIVF_match[i_subleading_displ_mu]) < 10) fill_IVF_histograms(&hists, &hists2D, "_OS_mu_close", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                if(_lIVF_match[i_subleading_displ_mu] != -1 and get_IVF_PVSVdist(_lIVF_match[i_subleading_displ_mu]) > 10) fill_IVF_histograms(&hists, &hists2D, "_OS_mu_far", i_leading_mu, i_subleading_displ_mu, i_gen_subleading_displ_mu);
                OSmu++;
                OSmu_weight += event_weight;
            }
        }
    }

    cout << "-----------------------------------------------------------------------" << endl;
    cout << "Channel    #events     #events(with ind. weight)    #events(with tot. weight)" << endl;
    cout << "SS ee:       " << SSe <<  "        " << SSe_weight <<  "       " << 1.0*SSe_weight*total_weight << endl;
    cout << "SS mumu:     " << SSmu << "        " << SSmu_weight << "       " << 1.0*SSmu_weight*total_weight << endl;
    cout << "OS ee:       " << OSe <<  "        " << OSe_weight <<  "       " << 1.0*OSe_weight*total_weight << endl;
    cout << "OS mumu:     " << OSmu << "        " << OSmu_weight << "       " << 1.0*OSmu_weight*total_weight << endl;
    //cout << "ee else: " << ee_else << endl;
    /*cout << "n total " << n_ele << endl;
    cout << "after eta " << n_after_eta << endl;
    cout << "after pt " << n_after_pt << endl;
    cout << "after dxy " << n_after_dxy << endl;
    cout << "after dz " << n_after_dz << endl;
    cout << "after sip3d " << n_after_sip3d << endl;
    cout << "after reliso " << n_after_reliso << endl;
    cout << "after inverted reliso " << n_after_invreliso << endl;
    cout << "after pogmedium " << n_after_pogmedium << endl;
    cout << "after convveto " << n_after_convveto << endl;
    cout << "after missinghits " << n_after_missinghits << endl;
    cout << "after invreliso and pogmedium " << n_after_invreliso_pogmedium << endl;
    cout << "after invreliso and convveto " << n_after_invreliso_convveto << endl;
    cout << "after invreliso and missinghits " << n_after_invreliso_missinghits << endl;*/

    //for(auto&& sh : hists){  //used to be just for ee_sigreg_fraction and mumu
	//    auto&& h  = sh.second;
	//    h->Scale(100/h->GetEntries());
    //}
    // 
    //if(flavor == "e" or flavor == "bkg"){
    //    cout << "2iso e, 0jet:            " << hists["ee_sigreg_fraction"]->GetBinContent(1) << endl;
    //    cout << "2iso e, 1jet:            " << hists["ee_sigreg_fraction"]->GetBinContent(2) << endl;
    //    cout << "2iso e, 2jet:            " << hists["ee_sigreg_fraction"]->GetBinContent(3) << endl;
    //    cout << "1iso e, 1noniso e, 0jet: " << hists["ee_sigreg_fraction"]->GetBinContent(4) << endl;
    //    cout << "1iso e, 1noniso e, 1jet: " << hists["ee_sigreg_fraction"]->GetBinContent(5) << endl;
    //    cout << "1iso e, 1noniso e, 2jet: " << hists["ee_sigreg_fraction"]->GetBinContent(6) << endl;
    //    cout << "1iso e, 1displ e, 0jet:  " << hists["ee_sigreg_fraction"]->GetBinContent(7) << endl;
    //    cout << "1iso e, 1displ e, 1jet:  " << hists["ee_sigreg_fraction"]->GetBinContent(8) << endl;
    //    cout << "1iso e, 1displ e, 2jet:  " << hists["ee_sigreg_fraction"]->GetBinContent(9) << endl << endl;
    //    cout << "1iso e, 0jet:            " << hists["ee_sigreg_fraction"]->GetBinContent(10) << endl;
    //    cout << "1iso e, 1jet:            " << hists["ee_sigreg_fraction"]->GetBinContent(11) << endl;
    //    cout << "1iso e, 2jet:            " << hists["ee_sigreg_fraction"]->GetBinContent(12) << endl;
    //    cout << "other:                   " << hists["ee_sigreg_fraction"]->GetBinContent(13) << endl;
    //}
    //if(flavor == "mu" or flavor == "bkg"){
    //    cout << "2iso mu, 0jet:             " << hists["mumu_sigreg_fraction"]->GetBinContent(1) << endl;
    //    cout << "2iso mu, 1jet:             " << hists["mumu_sigreg_fraction"]->GetBinContent(2) << endl;
    //    cout << "2iso mu, 2jet:             " << hists["mumu_sigreg_fraction"]->GetBinContent(3) << endl;
    //    cout << "1iso mu, 1noniso mu, 0jet: " << hists["mumu_sigreg_fraction"]->GetBinContent(4) << endl;
    //    cout << "1iso mu, 1noniso mu, 1jet: " << hists["mumu_sigreg_fraction"]->GetBinContent(5) << endl;
    //    cout << "1iso mu, 1noniso mu, 2jet: " << hists["mumu_sigreg_fraction"]->GetBinContent(6) << endl;
    //    cout << "1iso mu, 1displ mu, 0jet:  " << hists["mumu_sigreg_fraction"]->GetBinContent(7) << endl;
    //    cout << "1iso mu, 1displ mu, 1jet:  " << hists["mumu_sigreg_fraction"]->GetBinContent(8) << endl;
    //    cout << "1iso mu, 1displ mu, 2jet:  " << hists["mumu_sigreg_fraction"]->GetBinContent(9) << endl;
    //    cout << "1iso mu, 0jet:             " << hists["mumu_sigreg_fraction"]->GetBinContent(10) << endl;
    //    cout << "1iso mu, 1jet:             " << hists["mumu_sigreg_fraction"]->GetBinContent(11) << endl;
    //    cout << "1iso mu, 2jet:             " << hists["mumu_sigreg_fraction"]->GetBinContent(12) << endl;
    //    cout << "other:                     " << hists["mumu_sigreg_fraction"]->GetBinContent(13) << endl;
    //}
    //cout << endl << "it should be:" << endl;
    //cout << "2iso e, 0jet:            0.136727     " << endl; 
    //cout << "2iso e, 1jet:            0.0321711    " << endl; 
    //cout << "2iso e, 2jet:            0.00402139   " << endl; 
    //cout << "1iso e, 1noniso e, 0jet: 1.25467      " << endl; 
    //cout << "1iso e, 1noniso e, 1jet: 1.18229      " << endl; 
    //cout << "1iso e, 1noniso e, 2jet: 0.305626     " << endl; 
    //cout << "1iso e, 1displ e, 0jet:  15.4904      " << endl; 
    //cout << "1iso e, 1displ e, 1jet:  3.58306      " << endl; 
    //cout << "1iso e, 1displ e, 2jet:  0.63538      " << endl; 
    //
    //cout << "1iso e, 0jet:            17.7906      " << endl; 
    //cout << "1iso e, 1jet:            47.8707      " << endl; 
    //cout << "1iso e, 2jet:            11.7143      " << endl; 


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
        
        //if bin content is below zero, set it to 0
        for(int i = 0; i < nb+1; i++){
            if(h->GetBinContent(i) < 0.) h->SetBinContent(i, 0.);
        }
        h->Scale(total_weight); //this scaling now happens before the plotting stage, since after running, the histograms need to be hadded.
    }
    for( it2D = hists2D.begin(); it2D != hists2D.end(); it2D++){
        TH2* h = it2D->second;
        h->Scale(total_weight);
    }

    //Determine efficiencies for HLT
    divide_for_eff_HLT(&hists, "Beforeptcut");
    divide_for_eff_HLT(&hists, "Afterptcut");
    divide_for_eff(&hists, "_SS_e");
    divide_for_eff(&hists, "_OS_e");
    divide_for_eff(&hists, "_SS_mu");
    divide_for_eff(&hists, "_OS_mu");
    divide_for_eff(&hists, "_OS_e_oldID");
    divide_for_eff(&hists, "_SS_e_oldID");
    divide_for_eff(&hists, "_OS_mu_oldID");
    divide_for_eff(&hists, "_SS_mu_oldID");
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
