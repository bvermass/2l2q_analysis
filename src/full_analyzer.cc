
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
void full_analyzer::run_over_file(TString filename, double cross_section, int max_entries, int partition, int partitionjobnumber)
{
// Short description of program flow:
//     - initialize file
//     - initialize histograms
//     - start loop over events
//     - construct booleans for object selection? should be done at ntuplizer level, but all used variables should be included too
//     - functions for every signal region event selection


    TString flavor = "bkg";
    if(filename.Index("_e_") != -1) flavor = "e";
    else if(filename.Index("_mu_") != -1) flavor = "mu";

    TString promptordisplaced = "";
    if(filename.Index("prompt") != -1) promptordisplaced = "prompt";
    else if(filename.Index("displaced") != -1) promptordisplaced = "displaced";

    TFile *input = new TFile(filename, "open");
    TTree *tree  = (TTree*) input->Get("blackJackAndHookers/blackJackAndHookersTree");
    double total_weight = cross_section * 35900 / ((TH1F*) input->Get("blackJackAndHookers/hCounter"))->GetBinContent(1);
    cout << "total weight: " << total_weight << endl;
    Init(tree);


    //This map contains all 1D histograms
    std::map<TString, TH1*> hists;
    hists["ee_sigreg_fraction"]			= new TH1F("ee_sigreg_fraction",";signal regions;Events", 13, 0, 13);
    hists["mumu_sigreg_fraction"]		= new TH1F("mumu_sigreg_fraction",";signal regions;Events", 13, 0, 13);
    hists["1eovertotal"]			    = new TH1F("1eovertotal",";bin1 = total, bin2 = 1e;Events",2,0,2);
    hists["1muovertotal"]			    = new TH1F("1muovertotal",";bin1 = total, bin2 = 1mu;Events",2,0,2);
    // signal regions that are included:
    // 0 = 2iso l, 0jet
    // 1 = 2iso l, 1jet
    // 2 = 2iso l, 2jet
    // 3 = 1iso l, 1non-iso l, 0jet
    // 4 = 1iso l, 1non-iso l, 1jet
    // 5 = 1iso l, 1non-iso l, 2jet
    // 6 = 1iso l, 1displ l, 0jet
    // 7 = 1iso l, 1displ l, 1jet
    // 8 = 1iso l, 1displ l, 2jet
    // 9 = 1iso l, 0jet
    // 10= 1iso l, 1jet
    // 11= 1iso l, 2jet
    // 12= other

    HLT_efficiency_init(&hists);//found in src/HLT_eff.cc, does everything HLT efficiency related

    add_histograms(&hists, "displ_OS_e");//found in src/histo_functions.cc, basically main interesting variables for now, if this gets big, should branch to different files with clearer names
    add_histograms(&hists, "displ_SS_e");
    add_histograms(&hists, "displ_OS_mu");
    add_histograms(&hists, "displ_SS_mu");
    add_histograms(&hists, "displ_OS_e_beforemll");
    add_histograms(&hists, "displ_SS_e_beforemll");
    add_histograms(&hists, "displ_OS_mu_beforemll");
    add_histograms(&hists, "displ_SS_mu_beforemll");
    add_histograms(&hists, "displ_OS_e_beforedphi");
    add_histograms(&hists, "displ_SS_e_beforedphi");
    add_histograms(&hists, "displ_OS_mu_beforedphi");
    add_histograms(&hists, "displ_SS_mu_beforedphi");

    //assures statistical errors are dealt with correctly
    for(auto&& sh : hists){
	auto&& h = sh.second;
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

    // Determine range of events to loop over
    Long64_t nentries = tree->GetEntries();
    cout << "full_analyzer.cc file: " << filename << endl;
    cout << "Number of events: " << nentries << endl;
    if(max_entries == -1 || max_entries > nentries) max_entries = nentries;
    total_weight = 1.0 * nentries / max_entries * total_weight; //Correct weight for the amount of events that is actually ran
    
    Long64_t j_begin = floor(1.0 * max_entries * partitionjobnumber / partition);
    Long64_t j_end   = floor(1.0 * max_entries * (partitionjobnumber + 1) / partition);
    std::cout << "j_begin j_end max_entries: " << j_begin << " " << j_end << " " << max_entries << std::endl;

    //main loop begins here
    for(unsigned jentry = j_begin; jentry < j_end; ++jentry){
	    LoadTree(jentry);
	    tree->GetEntry(jentry);
        unsigned notice = round(0.001 * max_entries / 20) * 1000;
	    bool printevent = (jentry%notice == 0);
	    if(printevent){
	        cout << jentry << " of " << max_entries << endl;
	    }

        //Calculate Event weight
        if(filename.Index("HeavyNeutrino") == -1) event_weight = _weight; //WHEN WEIGHTS ARE CORRECT CHANGE THIS SO CORRECT WEIGHTS ARE ALSO USED FOR HEAVYNEUTRINO SAMPLES

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
	    bool fullElectronID[10], nonisoElectronID[10], displElectronID[10], fullMuonID[10], nonisoMuonID[10], displMuonID[10], fullJetID[10];
	    get_electronID(&fullElectronID[0]);
	    get_noniso_electronID(&nonisoElectronID[0]);
	    get_displ_electronID(&displElectronID[0]);
	    get_muonID(&fullMuonID[0]);
	    get_noniso_muonID(&nonisoMuonID[0]);
	    get_displ_muonID(&displMuonID[0]);
	    get_jetID(&fullJetID[0]);

        //Get Cleaning for jets
	    bool jet_clean_full[20], jet_clean_noniso[20], jet_clean_displ[20], jet_clean_full_noniso[20], jet_clean_full_displ[20];
	    get_clean_jets(&jet_clean_full[0],   &fullElectronID[0], &fullMuonID[0]);
	    get_clean_jets(&jet_clean_noniso[0], &nonisoElectronID[0], &nonisoMuonID[0]);
	    get_clean_jets(&jet_clean_displ[0],  &displElectronID[0], &displMuonID[0]);
	    for(unsigned i = 0; i < 20; ++i){
	        jet_clean_full_noniso[i] = jet_clean_full[i] && jet_clean_noniso[i];
	        jet_clean_full_displ[i] = jet_clean_full[i] && jet_clean_displ[i];
	    }
	    
        //Get cleaning for electrons
        bool ele_clean_full[10], ele_clean_noniso[10], ele_clean_displ[10], ele_clean_full_noniso_displ[10];
	    get_clean_ele(&ele_clean_full[0],   &fullMuonID[0]);
	    get_clean_ele(&ele_clean_noniso[0], &nonisoMuonID[0]);
	    get_clean_ele(&ele_clean_displ[0],  &displMuonID[0]);
	    for(unsigned i = 0; i < 10; ++i){
	        ele_clean_full_noniso_displ[i] = ele_clean_full[i] && ele_clean_noniso[i] && ele_clean_displ[i];
	    }

        //Find leptons and jets with leading pt
	    i_leading_e     		    = find_leading_e(&fullElectronID[0], &ele_clean_full_noniso_displ[0]);
	    i_subleading_e  		    = find_subleading_e(&fullElectronID[0], &ele_clean_full_noniso_displ[0], i_leading_e);
	    i_leading_mu    		    = find_leading_mu(&fullMuonID[0]);
	    i_subleading_mu 		    = find_subleading_mu(&fullMuonID[0], i_leading_mu);
	    i_subleading_noniso_e  	    = find_subleading_e(&nonisoElectronID[0], &ele_clean_full_noniso_displ[0], i_leading_e);
	    i_subleading_noniso_mu 	    = find_subleading_mu(&nonisoMuonID[0], i_leading_mu);
	    i_subleading_displ_e  	    = find_subleading_e(&displElectronID[0], &ele_clean_full_noniso_displ[0], i_leading_e);
	    i_subleading_displ_mu 	    = find_subleading_mu(&displMuonID[0], i_leading_mu);
	    
	    i_leading_jet_for_full	    = find_leading_jet(&fullJetID[0], &jet_clean_full[0]);
	    i_subleading_jet_for_full	= find_subleading_jet(&fullJetID[0], &jet_clean_full[0], i_leading_jet_for_full);
	    i_leading_jet_for_noniso	= find_leading_jet(&fullJetID[0], &jet_clean_full_noniso[0]);
	    i_subleading_jet_for_noniso	= find_subleading_jet(&fullJetID[0], &jet_clean_full_noniso[0], i_leading_jet_for_noniso);
	    i_leading_jet_for_displ	    = find_leading_jet(&fullJetID[0], &jet_clean_full_displ[0]);
	    i_subleading_jet_for_displ	= find_subleading_jet(&fullJetID[0], &jet_clean_full_displ[0], i_leading_jet_for_displ);


        
        //Get signal region -> put this into a function maybe
        signal_regions();
       // bool _1e			    = i_leading_e != -1;
       // bool leadptveto_e = false;
       // if(i_leading_e != -1 and _lPt[i_leading_e] > 30) leadptveto_e = true;
	   // bool _2e0jet 			= leadptveto_e && i_leading_e != -1 && i_subleading_e != -1 && i_leading_jet_for_full == -1 && i_subleading_jet_for_full == -1;
	   // bool _2e1jet 			= leadptveto_e && i_leading_e != -1 && i_subleading_e != -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full == -1;
	   // bool _2e2jet 			= leadptveto_e && i_leading_e != -1 && i_subleading_e != -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full != -1;
	   // bool _1e1nonisoe0jet	= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e != -1 && i_leading_jet_for_noniso == -1 && i_subleading_jet_for_noniso == -1;
	   // bool _1e1nonisoe1jet	= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e != -1 && i_leading_jet_for_noniso != -1 && i_subleading_jet_for_noniso == -1;
	   // bool _1e1nonisoe2jet	= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e != -1 && i_leading_jet_for_noniso != -1 && i_subleading_jet_for_noniso != -1;
	   // bool _1e1disple0jet		= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e != -1 && i_leading_jet_for_displ == -1 && i_subleading_jet_for_displ == -1;
	   // bool _1e1disple1jet		= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ == -1;
	   // bool _1e1disple2jet		= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ != -1;
	   // bool _1e0jet			= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e == -1 && i_leading_jet_for_full == -1 && i_subleading_jet_for_full == -1;
	   // bool _1e1jet			= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e == -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full == -1;
	   // bool _1e2jet			= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e == -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full != -1;
       // 

	   // bool _1mu			    = i_leading_mu != -1;
       // bool leadptveto_mu = false;
	   // if(i_leading_mu != -1 and _lPt[i_leading_mu] > 25) leadptveto_mu = true;
       // bool _2mu0jet 			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu != -1 && i_leading_jet_for_full == -1 && i_subleading_jet_for_full == -1;
	   // bool _2mu1jet 			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu != -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full == -1;
	   // bool _2mu2jet 			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu != -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full != -1;
	   // bool _1mu1nonisomu0jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu != -1 && i_leading_jet_for_noniso == -1 && i_subleading_jet_for_noniso == -1;
	   // bool _1mu1nonisomu1jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu != -1 && i_leading_jet_for_noniso != -1 && i_subleading_jet_for_noniso == -1;
	   // bool _1mu1nonisomu2jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu != -1 && i_leading_jet_for_noniso != -1 && i_subleading_jet_for_noniso != -1;
	   // bool _1mu1displmu0jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu != -1 && i_leading_jet_for_displ == -1 && i_subleading_jet_for_displ == -1;
	   // bool _1mu1displmu1jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ == -1;
	   // bool _1mu1displmu2jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ != -1;
	   // bool _1mu0jet			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu == -1 && i_leading_jet_for_full == -1 && i_subleading_jet_for_full == -1;
	   // bool _1mu1jet			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu == -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full == -1;
	   // bool _1mu2jet			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu == -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full != -1;
        

	    hists["1eovertotal"]->Fill(0., event_weight);
	    if(_1e){
	        hists["1eovertotal"]->Fill(1., event_weight);
	        if(_2e0jet) hists["ee_sigreg_fraction"]->Fill(0., event_weight);
	        else if(_2e1jet) hists["ee_sigreg_fraction"]->Fill(1., event_weight);
	        else if(_2e2jet) hists["ee_sigreg_fraction"]->Fill(2., event_weight);
	        else if(_1e1nonisoe0jet) hists["ee_sigreg_fraction"]->Fill(3., event_weight);
	        else if(_1e1nonisoe1jet) hists["ee_sigreg_fraction"]->Fill(4., event_weight);
	        else if(_1e1nonisoe2jet) hists["ee_sigreg_fraction"]->Fill(5., event_weight);
	        else if(_1e1disple0jet)  hists["ee_sigreg_fraction"]->Fill(6., event_weight);
	        else if(_1e1disple1jet)  hists["ee_sigreg_fraction"]->Fill(7., event_weight);
	        else if(_1e1disple2jet)  hists["ee_sigreg_fraction"]->Fill(8., event_weight);
	        else if(_1e0jet) hists["ee_sigreg_fraction"]->Fill(9., event_weight);
	        else if(_1e1jet) hists["ee_sigreg_fraction"]->Fill(10., event_weight);
	        else if(_1e2jet) hists["ee_sigreg_fraction"]->Fill(11., event_weight);
	        else hists["ee_sigreg_fraction"]->Fill(12., event_weight);
	    }
	    hists["1muovertotal"]->Fill(0., event_weight);
	    if(_1mu){
	        hists["1muovertotal"]->Fill(1., event_weight);
	        if(_2mu0jet) hists["mumu_sigreg_fraction"]->Fill(0., event_weight);
	        else if(_2mu1jet) hists["mumu_sigreg_fraction"]->Fill(1., event_weight);
	        else if(_2mu2jet) hists["mumu_sigreg_fraction"]->Fill(2., event_weight);
	        else if(_1mu1nonisomu0jet) hists["mumu_sigreg_fraction"]->Fill(3., event_weight);
	        else if(_1mu1nonisomu1jet) hists["mumu_sigreg_fraction"]->Fill(4., event_weight);
	        else if(_1mu1nonisomu2jet) hists["mumu_sigreg_fraction"]->Fill(5., event_weight);
	        else if(_1mu1displmu0jet)  hists["mumu_sigreg_fraction"]->Fill(6., event_weight);
	        else if(_1mu1displmu1jet)  hists["mumu_sigreg_fraction"]->Fill(7., event_weight);
	        else if(_1mu1displmu2jet)  hists["mumu_sigreg_fraction"]->Fill(8., event_weight);
	        else if(_1mu0jet) hists["mumu_sigreg_fraction"]->Fill(9., event_weight);
	        else if(_1mu1jet) hists["mumu_sigreg_fraction"]->Fill(10., event_weight);
	        else if(_1mu2jet) hists["mumu_sigreg_fraction"]->Fill(11., event_weight);
	        else hists["mumu_sigreg_fraction"]->Fill(12., event_weight);
	    }

        //HLT efficiency stuff, put this in a separate function later
        HLT_efficiency_fill(&hists, _1e, _1mu);


        if(_1e1disple0jet){
            if(_lCharge[i_leading_e] == _lCharge[i_subleading_displ_e]){
                fill_histograms(&hists, "displ_SS_e_beforemll");
            }else{
                fill_histograms(&hists, "displ_OS_e_beforemll");
            }           
        }
        if(_1mu1displmu0jet){
            if(_lCharge[i_leading_mu] == _lCharge[i_subleading_displ_mu]){
                fill_histograms(&hists, "displ_SS_mu_beforemll");
            }else{
                fill_histograms(&hists, "displ_OS_mu_beforemll");
            }
        }
        
        if(_1e1disple0jet_aftermll){
            if(_lCharge[i_leading_e] == _lCharge[i_subleading_displ_e]){
                fill_histograms(&hists, "displ_SS_e_beforedphi");
            }else{
                fill_histograms(&hists, "displ_OS_e_beforedphi");
            }           
        }
        if(_1mu1displmu0jet_aftermll){
            if(_lCharge[i_leading_mu] == _lCharge[i_subleading_displ_mu]){
                fill_histograms(&hists, "displ_SS_mu_beforedphi");
            }else{
                fill_histograms(&hists, "displ_OS_mu_beforedphi");
            }
        }

        if(_1e1disple0jet_afterdphi){
            if(_lCharge[i_leading_e] == _lCharge[i_subleading_displ_e]){
                fill_histograms(&hists, "displ_SS_e");
            }else{
                fill_histograms(&hists, "displ_OS_e");
            }
        }
        if(_1mu1displmu0jet_afterdphi){
            if(_lCharge[i_leading_mu] == _lCharge[i_subleading_displ_mu]){
                fill_histograms(&hists, "displ_SS_mu");
            }else{
                fill_histograms(&hists, "displ_OS_mu");
            }
        }
    }

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

    if(flavor == "e" or flavor == "bkg"){
        cout << "2iso e, 0jet:            " << hists["ee_sigreg_fraction"]->GetBinContent(1) << endl;
        cout << "2iso e, 1jet:            " << hists["ee_sigreg_fraction"]->GetBinContent(2) << endl;
        cout << "2iso e, 2jet:            " << hists["ee_sigreg_fraction"]->GetBinContent(3) << endl;
        cout << "1iso e, 1noniso e, 0jet: " << hists["ee_sigreg_fraction"]->GetBinContent(4) << endl;
        cout << "1iso e, 1noniso e, 1jet: " << hists["ee_sigreg_fraction"]->GetBinContent(5) << endl;
        cout << "1iso e, 1noniso e, 2jet: " << hists["ee_sigreg_fraction"]->GetBinContent(6) << endl;
        cout << "1iso e, 1displ e, 0jet:  " << hists["ee_sigreg_fraction"]->GetBinContent(7) << endl;
        cout << "1iso e, 1displ e, 1jet:  " << hists["ee_sigreg_fraction"]->GetBinContent(8) << endl;
        cout << "1iso e, 1displ e, 2jet:  " << hists["ee_sigreg_fraction"]->GetBinContent(9) << endl << endl;
        cout << "1iso e, 0jet:            " << hists["ee_sigreg_fraction"]->GetBinContent(10) << endl;
        cout << "1iso e, 1jet:            " << hists["ee_sigreg_fraction"]->GetBinContent(11) << endl;
        cout << "1iso e, 2jet:            " << hists["ee_sigreg_fraction"]->GetBinContent(12) << endl;
        cout << "other:                   " << hists["ee_sigreg_fraction"]->GetBinContent(13) << endl;
    }
    if(flavor == "mu" or flavor == "bkg"){
        cout << "2iso mu, 0jet:             " << hists["mumu_sigreg_fraction"]->GetBinContent(1) << endl;
        cout << "2iso mu, 1jet:             " << hists["mumu_sigreg_fraction"]->GetBinContent(2) << endl;
        cout << "2iso mu, 2jet:             " << hists["mumu_sigreg_fraction"]->GetBinContent(3) << endl;
        cout << "1iso mu, 1noniso mu, 0jet: " << hists["mumu_sigreg_fraction"]->GetBinContent(4) << endl;
        cout << "1iso mu, 1noniso mu, 1jet: " << hists["mumu_sigreg_fraction"]->GetBinContent(5) << endl;
        cout << "1iso mu, 1noniso mu, 2jet: " << hists["mumu_sigreg_fraction"]->GetBinContent(6) << endl;
        cout << "1iso mu, 1displ mu, 0jet:  " << hists["mumu_sigreg_fraction"]->GetBinContent(7) << endl;
        cout << "1iso mu, 1displ mu, 1jet:  " << hists["mumu_sigreg_fraction"]->GetBinContent(8) << endl;
        cout << "1iso mu, 1displ mu, 2jet:  " << hists["mumu_sigreg_fraction"]->GetBinContent(9) << endl;
        cout << "1iso mu, 0jet:             " << hists["mumu_sigreg_fraction"]->GetBinContent(10) << endl;
        cout << "1iso mu, 1jet:             " << hists["mumu_sigreg_fraction"]->GetBinContent(11) << endl;
        cout << "1iso mu, 2jet:             " << hists["mumu_sigreg_fraction"]->GetBinContent(12) << endl;
        cout << "other:                     " << hists["mumu_sigreg_fraction"]->GetBinContent(13) << endl;
    }
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


    TString outputfilename = "~/public/2l2q_analysis/histograms/full_analyzer/";
    
    if(partition != 1) {
        outputfilename += "subfiles/";
        if(filename.Index("HeavyNeutrino") != -1) outputfilename += filename(filename.Index("HeavyNeutrino_"), filename.Index("dilep.root") - 1 - filename.Index("HeavyNeutrino_")) + "_" + promptordisplaced + "/";
        else outputfilename += "Background_" + filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep.root") - filename.Index("heavyNeutrino") - 15) + "/";
    }
    gSystem->Exec("mkdir -p " + outputfilename);

    if(filename.Index("HeavyNeutrino") != -1) outputfilename += "hists_full_analyzer_" + filename(filename.Index("HeavyNeutrino_"), filename.Index("dilep.root") - 1 - filename.Index("HeavyNeutrino_")) + "_" + promptordisplaced;
    else outputfilename += "hists_full_analyzer_Background_" + filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep.root") - filename.Index("heavyNeutrino") - 15);
    
    if(partition != 1) outputfilename += "_job_" + to_string(partitionjobnumber) + ".root";
    else outputfilename += ".root";

    cout << "output to: " << outputfilename << endl;
    TFile *output = new TFile(outputfilename, "recreate");
    for(auto&& sh : hists){
	    auto&& h  = sh.second;
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
            if(h->GetBinContent(i) < 0.2) h->SetBinContent(i, 0.);
        }
        h->Scale(total_weight);
    }

    //Determine efficiencies for HLT
    hists["HLT_Ele27_WPTight_Gsf_pt_eff"]->Divide(hists["HLT_1_iso_e_pt"]);
    hists["HLT_Ele27_WPTight_Gsf_barrel_pt_eff"]->Divide(hists["HLT_1_iso_e_barrel_pt"]);
    hists["HLT_Ele27_WPTight_Gsf_endcap_pt_eff"]->Divide(hists["HLT_1_iso_e_endcap_pt"]);
    hists["HLT_IsoMu24_IsoTkMu24_pt_eff"]->Divide(hists["HLT_1_iso_mu_pt"]);
    hists["HLT_IsoMu24_IsoTkMu24_barrel_pt_eff"]->Divide(hists["HLT_1_iso_mu_barrel_pt"]);
    hists["HLT_IsoMu24_IsoTkMu24_endcap_pt_eff"]->Divide(hists["HLT_1_iso_mu_endcap_pt"]);

    for(auto&& sh : hists){
        auto&& h = sh.second;
	    h->Write();
    }
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
