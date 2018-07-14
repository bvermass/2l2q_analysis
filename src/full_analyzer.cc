//#define full_analyzer_start_cxx

//Include C++ libraries
#include <iostream>

//Include header for this class
#include "../interface/full_analyzer.h"

//#define full_analyzer_done_cxx // otherwise the functions in full_analyzer.h can be loaded multiple times
//#include "/user/bvermass/heavyNeutrino/DileptonPrompt/CMSSW_9_4_0/src/2l2q_analysis/tools/LeptonID.h"

//Include ROOT header files
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TSystem.h>

using namespace std;
//Contents:
//  run_over_file		: This is the main function to loop over events of a certain file, give the exact filename of the signal/background/data to the function
//  clean_jets			: cleans collection of jets by vetoing jets with dR < 0.4 with electrons or muons
//  clean_ele			: cleans collection of electrons by vetoing electrons with dR < 0.4 with muons
//  find_2_highest_pt_particles : finds 2 highest pt particles, if there is only one or zero, then i_jet1 or i_jet2 are put to -1
//  loop 			: currently not used

void full_analyzer::run_over_file(TString filename, double cross_section, int max_entries)
{
// Short description of program flow:
//     - initialize file
//     - initialize histograms
//     - start loop over events
//     - construct booleans for object selection? should be done at ntuplizer level, but all used variables should be included too
//     - functions for every signal region event selection

    //LeptonID b;
    //b.test_function();

    TString flavor = "bkg";
    if(filename.Index("_e_") != -1) flavor = "e";
    else if(filename.Index("_mu_") != -1) flavor = "mu";

    TString promptordisplaced = "";
    if(filename.Index("prompt") != -1) promptordisplaced = "prompt";
    else if(filename.Index("displaced") != -1) promptordisplaced = "displaced";

    //TFile *input = new TFile("/user/bvermass/public/heavyNeutrino/" + filename + "/dilep.root", "open");
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
    /*hists["2isol_0jet_pt"]              = new TH1F("2isol_0jet_pt", ";#it{p}_{T} [GeV]; Events", 40, 0, 100);
    hists["2isol_1jet_pt"]              = new TH1F("2isol_1jet_pt", ";#it{p}_{T} [GeV]; Events", 40, 0, 100);
    hists["2isol_2jet_pt"]              = new TH1F("2isol_2jet_pt", ";#it{p}_{T} [GeV]; Events", 40, 0, 100);
    hists["1iso1displ_0jet_pt"]              = new TH1F("1iso1displ_0jet_pt", ";#it{p}_{T} [GeV]; Events", 40, 0, 100);
    hists["1iso1displ_1jet_pt"]              = new TH1F("1iso1displ_1jet_pt", ";#it{p}_{T} [GeV]; Events", 40, 0, 100);
    hists["1iso1displ_2jet_pt"]              = new TH1F("1iso1displ_2jet_pt", ";#it{p}_{T} [GeV]; Events", 40, 0, 100);
*/
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


    // DELETE THIS AFTER NEXT ITERATION
    /*hists["1_iso_ele_pt"]               = new TH1F("1_iso_ele_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["HLT_Ele27_WPTight_Gsf_pt"]   = new TH1F("HLT_Ele27_WPTight_Gsf_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["HLT_Ele27_WPTight_Gsf_pt_eff"]   = new TH1F("HLT_Ele27_WPTight_Gsf_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    hists["1_iso_ele_barrel_pt"]               = new TH1F("1_iso_ele_barrel_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["HLT_Ele27_WPTight_Gsf_barrel_pt"]   = new TH1F("HLT_Ele27_WPTight_Gsf_barrel_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["HLT_Ele27_WPTight_Gsf_barrel_pt_eff"]   = new TH1F("HLT_Ele27_WPTight_Gsf_barrel_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    hists["1_iso_ele_endcap_pt"]               = new TH1F("1_iso_ele_endcap_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["HLT_Ele27_WPTight_Gsf_endcap_pt"]   = new TH1F("HLT_Ele27_WPTight_Gsf_endcap_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["HLT_Ele27_WPTight_Gsf_endcap_pt_eff"]   = new TH1F("HLT_Ele27_WPTight_Gsf_endcap_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    hists["1_iso_mu_pt"]               = new TH1F("1_iso_mu_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["HLT_IsoMu24_IsoTkMu24_pt"]   = new TH1F("HLT_IsoMu24_IsoTkMu24_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["HLT_IsoMu24_IsoTkMu24_pt_eff"]   = new TH1F("HLT_IsoMu24_IsoTkMu24_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    hists["1_iso_mu_barrel_pt"]               = new TH1F("1_iso_mu_barrel_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["HLT_IsoMu24_IsoTkMu24_barrel_pt"]   = new TH1F("HLT_IsoMu24_IsoTkMu24_barrel_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["HLT_IsoMu24_IsoTkMu24_barrel_pt_eff"]   = new TH1F("HLT_IsoMu24_IsoTkMu24_barrel_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
    hists["1_iso_mu_endcap_pt"]               = new TH1F("1_iso_mu_endcap_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["HLT_IsoMu24_IsoTkMu24_endcap_pt"]   = new TH1F("HLT_IsoMu24_IsoTkMu24_endcap_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["HLT_IsoMu24_IsoTkMu24_endcap_pt_eff"]   = new TH1F("HLT_IsoMu24_IsoTkMu24_endcap_pt_eff", ";#it{p}_{T} [GeV];Efficiency", 80, 0, 200);
*/
    HLT_efficiency_init(&hists);

    // DELETE THIS AFTER NEXT ITERATION 
    /*hists["displ_SS_e_leadpt"]              = new TH1F("displ_SS_e_leadpt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["displ_SS_e_pt"]                  = new TH1F("displ_SS_e_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["displ_SS_e_dxy"]                 = new TH1F("displ_SS_e_dxy", ";#Delta_{xy} [cm];Events", 80, 0, 10);
    hists["displ_SS_e_mll"]                 = new TH1F("displ_SS_e_mll", ";#it{m}_{ll} [GeV];Events", 80, 0, 200);
    hists["displ_SS_e_vtxfitgen"]           = new TH1F("displ_SS_e_vtxfitgen", ";|Vtx_{fit} - Vtx_{gen}| [cm];Events", 80, 0, 10);
    hists["displ_SS_e_chi2"]                = new TH1F("displ_SS_e_chi2", ";#Chi^{2};Events", 80, 0, 2);
    hists["displ_SS_e_vtxfitPV"]            = new TH1F("displ_SS_e_vtxfitPV", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 80, 0, 10);
    hists["displ_SS_e_vtxfit_ntracks"]      = new TH1F("displ_SS_e_vtxfit_ntracks", ";# of tracks used in Vtxfit;Events", 15, 0, 15);
    hists["displ_SS_e_vtxfit_valid"]        = new TH1F("displ_SS_e_vtxfit_valid", ";is Vertex Valid?;Events", 2, 0, 2);
    hists["displ_SS_e_vtxfit_maxdxy_valid"] = new TH1F("displ_SS_e_vtxfit_maxdxy_valid", ";dxy_{max} (Valid Vtx);Events", 40, 0, 1.1);
    hists["displ_SS_mu_leadpt"]             = new TH1F("displ_SS_mu_leadpt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["displ_SS_mu_pt"]                 = new TH1F("displ_SS_mu_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["displ_SS_mu_dxy"]                = new TH1F("displ_SS_mu_dxy", ";#Delta_{xy} [cm];Events", 80, 0, 10);
    hists["displ_SS_mu_mll"]                = new TH1F("displ_SS_mu_mll", ";#it{m}_{ll} [GeV];Events", 80, 0, 200);
    hists["displ_SS_mu_vtxfitgen"]          = new TH1F("displ_SS_mu_vtxfitgen", ";|Vtx_{fit} - Vtx_{gen}| [cm];Events", 80, 0, 10);
    hists["displ_SS_mu_chi2"]               = new TH1F("displ_SS_mu_chi2", ";#Chi^{2};Events", 80, 0, 2);
    hists["displ_SS_mu_vtxfitPV"]           = new TH1F("displ_SS_mu_vtxfitPV", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 80, 0, 10);
    hists["displ_SS_mu_vtxfit_ntracks"]      = new TH1F("displ_SS_mu_vtxfit_ntracks", ";# of tracks used in Vtxfit;Events", 15, 0, 15);
    hists["displ_SS_mu_vtxfit_valid"]        = new TH1F("displ_SS_mu_vtxfit_valid", ";is Vertex Valid?;Events", 2, 0, 2);
    hists["displ_SS_mu_vtxfit_maxdxy_valid"] = new TH1F("displ_SS_mu_vtxfit_maxdxy_valid", ";dxy_{max} (Valid Vtx);Events", 40, 0, 1.1);
    hists["displ_OS_e_leadpt"]              = new TH1F("displ_OS_e_leadpt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    //hists["displ_OS_e_pt"]                  = new TH1F("displ_OS_e_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["displ_OS_e_dxy"]                 = new TH1F("displ_OS_e_dxy", ";#Delta_{xy} [cm];Events", 80, 0, 10);
    hists["displ_OS_e_mll"]                 = new TH1F("displ_OS_e_mll", ";#it{m}_{ll} [GeV];Events", 80, 0, 200);
    hists["displ_OS_e_vtxfitgen"]           = new TH1F("displ_OS_e_vtxfitgen", ";|Vtx_{fit} - Vtx_{gen}| [cm];Events", 80, 0, 10);
    hists["displ_OS_e_chi2"]                = new TH1F("displ_OS_e_chi2", ";#Chi^{2};Events", 80, 0, 2);
    hists["displ_OS_e_vtxfitPV"]            = new TH1F("displ_OS_e_vtxfitPV", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 80, 0, 10);
    hists["displ_OS_e_vtxfit_ntracks"]      = new TH1F("displ_OS_e_vtxfit_ntracks", ";# of tracks used in Vtxfit;Events", 15, 0, 15);
    hists["displ_OS_e_vtxfit_valid"]        = new TH1F("displ_OS_e_vtxfit_valid", ";is Vertex Valid?;Events", 2, 0, 2);
    hists["displ_OS_e_vtxfit_maxdxy_valid"] = new TH1F("displ_OS_e_vtxfit_maxdxy_valid", ";dxy_{max} (Valid Vtx);Events", 40, 0, 1.1);
    hists["displ_OS_mu_leadpt"]             = new TH1F("displ_OS_mu_leadpt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["displ_OS_mu_pt"]                 = new TH1F("displ_OS_mu_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    hists["displ_OS_mu_dxy"]                = new TH1F("displ_OS_mu_dxy", ";#Delta_{xy} [cm];Events", 80, 0, 10);
    hists["displ_OS_mu_mll"]                = new TH1F("displ_OS_mu_mll", ";#it{m}_{ll} [GeV];Events", 80, 0, 200);
    hists["displ_OS_mu_vtxfitgen"]          = new TH1F("displ_OS_mu_vtxfitgen", ";|Vtx_{fit} - Vtx_{gen}| [cm];Events", 80, 0, 10);
    hists["displ_OS_mu_chi2"]               = new TH1F("displ_OS_mu_chi2", ";#Chi^{2};Events", 80, 0, 2);
    hists["displ_OS_mu_vtxfitPV"]           = new TH1F("displ_OS_mu_vtxfitPV", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 80, 0, 10);
    hists["displ_OS_mu_vtxfit_ntracks"]      = new TH1F("displ_OS_mu_vtxfit_ntracks", ";# of tracks used in Vtxfit;Events", 15, 0, 15);
    hists["displ_OS_mu_vtxfit_valid"]        = new TH1F("displ_OS_mu_vtxfit_valid", ";is Vertex Valid?;Events", 2, 0, 2);
    hists["displ_OS_mu_vtxfit_maxdxy_valid"] = new TH1F("displ_OS_mu_vtxfit_maxdxy_valid", ";dxy_{max} (Valid Vtx);Events", 40, 0, 1.1);
*/
    add_histograms(&hists, "displ_OS_e");
    add_histograms(&hists, "displ_SS_e");
    add_histograms(&hists, "displ_OS_mu");
    add_histograms(&hists, "displ_SS_mu");
    cout << hists["displ_OS_e_pt"]->GetName() << endl;

    for(auto&& sh : hists){
	auto&& h = sh.second;
	h->Sumw2();
    }
   
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


    Long64_t nentries = tree->GetEntries();
    cout << "full_analyzer.cc file: " << filename << endl;
    cout << "Number of events: " << nentries << endl;
    if(max_entries == -1 || max_entries > nentries) max_entries = nentries;
    total_weight = 1.0 * nentries / max_entries * total_weight; //Correct weight for the amount of events that is actually ran
    cout << "full_analyzer 2" << endl;
    
    for(unsigned jentry = 0; jentry < max_entries; ++jentry){
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
        bool _1e			    = i_leading_e != -1;
        bool leadptveto_e = false;
        //if(i_leading_e != -1 && jentry%100 == 0) cout << "leading pt: " << _lPt[i_leading_e] << endl;
        if(i_leading_e != -1 and _lPt[i_leading_e] > 30) leadptveto_e = true;
        //if(i_leading_e != -1 && jentry%100 == 0) cout << "leadptveto_e: " << leadptveto_e << endl;
	    bool _2e0jet 			= leadptveto_e && i_leading_e != -1 && i_subleading_e != -1 && i_leading_jet_for_full == -1 && i_subleading_jet_for_full == -1;
	    bool _2e1jet 			= leadptveto_e && i_leading_e != -1 && i_subleading_e != -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full == -1;
	    bool _2e2jet 			= leadptveto_e && i_leading_e != -1 && i_subleading_e != -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full != -1;
	    bool _1e1nonisoe0jet	= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e != -1 && i_leading_jet_for_noniso == -1 && i_subleading_jet_for_noniso == -1;
	    bool _1e1nonisoe1jet	= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e != -1 && i_leading_jet_for_noniso != -1 && i_subleading_jet_for_noniso == -1;
	    bool _1e1nonisoe2jet	= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e != -1 && i_leading_jet_for_noniso != -1 && i_subleading_jet_for_noniso != -1;
	    bool _1e1disple0jet		= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e != -1 && i_leading_jet_for_displ == -1 && i_subleading_jet_for_displ == -1;
	    bool _1e1disple1jet		= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ == -1;
	    bool _1e1disple2jet		= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ != -1;
	    bool _1e0jet			= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e == -1 && i_leading_jet_for_full == -1 && i_subleading_jet_for_full == -1;
	    bool _1e1jet			= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e == -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full == -1;
	    bool _1e2jet			= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e == -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full != -1;
        

	    bool _1mu			    = i_leading_mu != -1;
        bool leadptveto_mu = false;
	    if(i_leading_mu != -1 and _lPt[i_leading_mu] > 25) leadptveto_mu = true;
        bool _2mu0jet 			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu != -1 && i_leading_jet_for_full == -1 && i_subleading_jet_for_full == -1;
	    bool _2mu1jet 			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu != -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full == -1;
	    bool _2mu2jet 			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu != -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full != -1;
	    bool _1mu1nonisomu0jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu != -1 && i_leading_jet_for_noniso == -1 && i_subleading_jet_for_noniso == -1;
	    bool _1mu1nonisomu1jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu != -1 && i_leading_jet_for_noniso != -1 && i_subleading_jet_for_noniso == -1;
	    bool _1mu1nonisomu2jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu != -1 && i_leading_jet_for_noniso != -1 && i_subleading_jet_for_noniso != -1;
	    bool _1mu1displmu0jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu != -1 && i_leading_jet_for_displ == -1 && i_subleading_jet_for_displ == -1;
	    bool _1mu1displmu1jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ == -1;
	    bool _1mu1displmu2jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ != -1;
	    bool _1mu0jet			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu == -1 && i_leading_jet_for_full == -1 && i_subleading_jet_for_full == -1;
	    bool _1mu1jet			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu == -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full == -1;
	    bool _1mu2jet			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu == -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full != -1;
        

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
        /*if(_1e){
            hists["1_iso_ele_pt"]->Fill(_lPt[i_leading_e], event_weight);
            if(fabs(_lEta[i_leading_e]) < 1.2) hists["1_iso_ele_barrel_pt"]->Fill(_lPt[i_leading_e], event_weight);
            else hists["1_iso_ele_endcap_pt"]->Fill(_lPt[i_leading_e], event_weight);
            
            if(_HLT_Ele27_WPTight_Gsf){ 
                hists["HLT_Ele27_WPTight_Gsf_pt"]->Fill(_lPt[i_leading_e], event_weight);
                if(fabs(_lEta[i_leading_e]) < 1.2) hists["HLT_Ele27_WPTight_Gsf_barrel_pt"]->Fill(_lPt[i_leading_e], event_weight);
                else hists["HLT_Ele27_WPTight_Gsf_endcap_pt"]->Fill(_lPt[i_leading_e], event_weight);
                
                hists["HLT_Ele27_WPTight_Gsf_pt_eff"]->Fill(_lPt[i_leading_e], event_weight);
                if(fabs(_lEta[i_leading_e]) < 1.2) hists["HLT_Ele27_WPTight_Gsf_barrel_pt_eff"]->Fill(_lPt[i_leading_e], event_weight);
                else hists["HLT_Ele27_WPTight_Gsf_endcap_pt_eff"]->Fill(_lPt[i_leading_e], event_weight);
            }

        }
        if(_1mu){
            hists["1_iso_mu_pt"]->Fill(_lPt[i_leading_mu], event_weight);
            if(fabs(_lEta[i_leading_mu]) < 1.2) hists["1_iso_mu_barrel_pt"]->Fill(_lPt[i_leading_mu], event_weight);
            else hists["1_iso_mu_endcap_pt"]->Fill(_lPt[i_leading_mu], event_weight);
            
            if(_HLT_IsoMu24 or _HLT_IsoTkMu24){ 
                hists["HLT_IsoMu24_IsoTkMu24_pt"]->Fill(_lPt[i_leading_mu], event_weight);
                if(fabs(_lEta[i_leading_mu]) < 1.2) hists["HLT_IsoMu24_IsoTkMu24_barrel_pt"]->Fill(_lPt[i_leading_mu], event_weight);
                else hists["HLT_IsoMu24_IsoTkMu24_endcap_pt"]->Fill(_lPt[i_leading_mu], event_weight);
                
                hists["HLT_IsoMu24_IsoTkMu24_pt_eff"]->Fill(_lPt[i_leading_mu], event_weight);
                if(fabs(_lEta[i_leading_mu]) < 1.2) hists["HLT_IsoMu24_IsoTkMu24_barrel_pt_eff"]->Fill(_lPt[i_leading_mu], event_weight);
                else hists["HLT_IsoMu24_IsoTkMu24_endcap_pt_eff"]->Fill(_lPt[i_leading_mu], event_weight);
            }
        }*/

        //TLorentzVector lepton1;
        //TLorentzVector lepton2;
        if(_1e1disple0jet){
            if(_lCharge[i_leading_e] == _lCharge[i_subleading_displ_e]){
                fill_histograms(&hists, "displ_SS_e");
/*                hists["displ_SS_e_leadpt"]->Fill(_lPt[i_leading_e], event_weight);
                hists["displ_SS_e_pt"]->Fill(_lPt[i_subleading_displ_e], event_weight);
                hists["displ_SS_e_dxy"]->Fill(_dxy[i_subleading_displ_e], event_weight);
                lepton1.SetPtEtaPhiE(_lPt[i_leading_e], _lEta[i_leading_e], _lPhi[i_leading_e], _lE[i_leading_e]);
                lepton2.SetPtEtaPhiE(_lPt[i_subleading_displ_e], _lEta[i_subleading_displ_e], _lPhi[i_subleading_displ_e], _lE[i_subleading_displ_e]);
                hists["displ_SS_e_mll"]->Fill((lepton1 + lepton2).M(), event_weight);
                hists["displ_SS_e_vtxfit_valid"]->Fill(_lVtx_valid[i_subleading_displ_e], event_weight);
                if(_lVtx_valid[i_subleading_displ_e]){
                    hists["displ_SS_e_vtxfitgen"]->Fill(sqrt((_gen_vertex_x[i_subleading_displ_e] - _lVtxpos_x[i_subleading_displ_e])*(_gen_vertex_x[i_subleading_displ_e] - _lVtxpos_x[i_subleading_displ_e]) + (_gen_vertex_y[i_subleading_displ_e] - _lVtxpos_y[i_subleading_displ_e])*(_gen_vertex_y[i_subleading_displ_e] - _lVtxpos_y[i_subleading_displ_e]) + (_gen_vertex_z[i_subleading_displ_e] - _lVtxpos_z[i_subleading_displ_e])*(_gen_vertex_z[i_subleading_displ_e] - _lVtxpos_z[i_subleading_displ_e])), event_weight);
                    hists["displ_SS_e_chi2"]->Fill(_lVtxpos_chi2[i_subleading_e], event_weight);
                    hists["displ_SS_e_vtxfitPV"]->Fill(_lVtxpos_PVdxy[i_subleading_displ_e], event_weight);
                    hists["displ_SS_e_vtxfit_ntracks"]->Fill(_lVtxpos_ntracks[i_subleading_displ_e], event_weight);
                    hists["displ_SS_e_vtxfit_maxdxy_valid"]->Fill(_lVtxpos_maxdxy_valid[i_subleading_displ_e], event_weight);
                }
            */}else{
                fill_histograms(&hists, "displ_OS_e");
                /*hists["displ_OS_e_leadpt"]->Fill(_lPt[i_leading_e], event_weight);
                hists["displ_OS_e_pt"]->Fill(_lPt[i_subleading_displ_e], event_weight);
                hists["displ_OS_e_dxy"]->Fill(_dxy[i_subleading_displ_e], event_weight);
                lepton1.SetPtEtaPhiE(_lPt[i_leading_e], _lEta[i_leading_e], _lPhi[i_leading_e], _lE[i_leading_e]);
                lepton2.SetPtEtaPhiE(_lPt[i_subleading_displ_e], _lEta[i_subleading_displ_e], _lPhi[i_subleading_displ_e], _lE[i_subleading_displ_e]);
                hists["displ_OS_e_mll"]->Fill((lepton1 + lepton2).M(), event_weight);
                hists["displ_OS_e_vtxfit_valid"]->Fill(_lVtx_valid[i_subleading_displ_e], event_weight);
                if(_lVtx_valid[i_subleading_displ_e]){
                    hists["displ_OS_e_vtxfitgen"]->Fill(sqrt((_gen_vertex_x[i_subleading_displ_e] - _lVtxpos_x[i_subleading_displ_e])*(_gen_vertex_x[i_subleading_displ_e] - _lVtxpos_x[i_subleading_displ_e]) + (_gen_vertex_y[i_subleading_displ_e] - _lVtxpos_y[i_subleading_displ_e])*(_gen_vertex_y[i_subleading_displ_e] - _lVtxpos_y[i_subleading_displ_e]) + (_gen_vertex_z[i_subleading_displ_e] - _lVtxpos_z[i_subleading_displ_e])*(_gen_vertex_z[i_subleading_displ_e] - _lVtxpos_z[i_subleading_displ_e])), event_weight);
                    hists["displ_OS_e_chi2"]->Fill(_lVtxpos_chi2[i_subleading_e], event_weight);
                    hists["displ_OS_e_vtxfitPV"]->Fill(_lVtxpos_PVdxy[i_subleading_displ_e], event_weight);
                    hists["displ_OS_e_vtxfit_ntracks"]->Fill(_lVtxpos_ntracks[i_subleading_displ_e], event_weight);
                    hists["displ_OS_e_vtxfit_maxdxy_valid"]->Fill(_lVtxpos_maxdxy_valid[i_subleading_displ_e], event_weight);
                }
            */}
        }
        if(_1mu1displmu0jet){
            if(_lCharge[i_leading_mu] == _lCharge[i_subleading_displ_mu]){
                fill_histograms(&hists, "displ_SS_mu");
                /*hists["displ_SS_mu_leadpt"]->Fill(_lPt[i_leading_mu], event_weight);
                hists["displ_SS_mu_pt"]->Fill(_lPt[i_subleading_displ_mu], event_weight);
                hists["displ_SS_mu_dxy"]->Fill(_dxy[i_subleading_displ_mu], event_weight);
                lepton1.SetPtEtaPhiE(_lPt[i_leading_mu], _lEta[i_leading_mu], _lPhi[i_leading_mu], _lE[i_leading_mu]);
                lepton2.SetPtEtaPhiE(_lPt[i_subleading_displ_mu], _lEta[i_subleading_displ_mu], _lPhi[i_subleading_displ_mu], _lE[i_subleading_displ_mu]);
                hists["displ_SS_mu_mll"]->Fill((lepton1 + lepton2).M(), event_weight);
                hists["displ_SS_mu_vtxfit_valid"]->Fill(_lVtx_valid[i_subleading_displ_mu], event_weight);
                if(_lVtx_valid[i_subleading_displ_mu]){
                    hists["displ_SS_mu_vtxfitgen"]->Fill(sqrt((_gen_vertex_x[i_subleading_displ_mu] - _lVtxpos_x[i_subleading_displ_mu])*(_gen_vertex_x[i_subleading_displ_mu] - _lVtxpos_x[i_subleading_displ_mu]) + (_gen_vertex_y[i_subleading_displ_mu] - _lVtxpos_y[i_subleading_displ_mu])*(_gen_vertex_y[i_subleading_displ_mu] - _lVtxpos_y[i_subleading_displ_mu]) + (_gen_vertex_z[i_subleading_displ_mu] - _lVtxpos_z[i_subleading_displ_mu])*(_gen_vertex_z[i_subleading_displ_mu] - _lVtxpos_z[i_subleading_displ_mu])), event_weight);
                    hists["displ_SS_mu_chi2"]->Fill(_lVtxpos_chi2[i_subleading_mu], event_weight);
                    hists["displ_SS_mu_vtxfitPV"]->Fill(_lVtxpos_PVdxy[i_subleading_displ_mu], event_weight);
                    hists["displ_SS_mu_vtxfit_ntracks"]->Fill(_lVtxpos_ntracks[i_subleading_displ_mu], event_weight);
                    hists["displ_SS_mu_vtxfit_maxdxy_valid"]->Fill(_lVtxpos_maxdxy_valid[i_subleading_displ_e], event_weight);
                }
            */}else{
                fill_histograms(&hists, "displ_OS_mu");
                /*hists["displ_OS_mu_leadpt"]->Fill(_lPt[i_leading_mu], event_weight);
                hists["displ_OS_mu_dxy"]->Fill(_dxy[i_subleading_displ_mu], event_weight);
                lepton1.SetPtEtaPhiE(_lPt[i_leading_mu], _lEta[i_leading_mu], _lPhi[i_leading_mu], _lE[i_leading_mu]);
                lepton2.SetPtEtaPhiE(_lPt[i_subleading_displ_mu], _lEta[i_subleading_displ_mu], _lPhi[i_subleading_displ_mu], _lE[i_subleading_displ_mu]);
                hists["displ_OS_mu_mll"]->Fill((lepton1 + lepton2).M(), event_weight);
                hists["displ_OS_mu_vtxfit_valid"]->Fill(_lVtx_valid[i_subleading_displ_mu], event_weight);
                if(_lVtx_valid[i_subleading_displ_mu]){
                    hists["displ_OS_mu_vtxfitgen"]->Fill(sqrt((_gen_vertex_x[i_subleading_displ_mu] - _lVtxpos_x[i_subleading_displ_mu])*(_gen_vertex_x[i_subleading_displ_mu] - _lVtxpos_x[i_subleading_displ_mu]) + (_gen_vertex_y[i_subleading_displ_mu] - _lVtxpos_y[i_subleading_displ_mu])*(_gen_vertex_y[i_subleading_displ_mu] - _lVtxpos_y[i_subleading_displ_mu]) + (_gen_vertex_z[i_subleading_displ_mu] - _lVtxpos_z[i_subleading_displ_mu])*(_gen_vertex_z[i_subleading_displ_mu] - _lVtxpos_z[i_subleading_displ_mu])), event_weight);
                    hists["displ_OS_mu_chi2"]->Fill(_lVtxpos_chi2[i_subleading_mu], event_weight);
                    hists["displ_OS_mu_vtxfitPV"]->Fill(_lVtxpos_PVdxy[i_subleading_displ_mu], event_weight);
                    hists["displ_OS_mu_vtxfit_ntracks"]->Fill(_lVtxpos_ntracks[i_subleading_displ_mu], event_weight);
                    hists["displ_OS_mu_vtxfit_maxdxy_valid"]->Fill(_lVtxpos_maxdxy_valid[i_subleading_displ_e], event_weight);
                }
            */}
        }
        /*if(filename.Index("_e_") != -1){
            hists["2isol_0jet_leadlpt"]->Fill(_lPt[i_leading_e], event_weight);
            hists["2isol_1jet_leadlpt"]->Fill(_lPt[i_leading_e], event_weight);
            hists["2isol_2jet_leadlpt"]->Fill(_lPt[i_leading_e], event_weight);
            hists["1iso1displ_0jet_leadlpt"]->Fill(_lPt[i_leading_e], event_weight);
            hists["1iso1displ_1jet_leadlpt"]->Fill(_lPt[i_leading_e], event_weight);
            hists["1iso1displ_2jet_leadlpt"]->Fill(_lPt[i_leading_e], event_weight);
        }
        else if(filename.Index("_mu_") != -1){
            hists["2isol_0jet_leadlpt"]->Fill(_lPt[i_leading_mu], event_weight);
            hists["2isol_1jet_leadlpt"]->Fill(_lPt[i_leading_mu], event_weight);
            hists["2isol_2jet_leadlpt"]->Fill(_lPt[i_leading_mu], event_weight);
            hists["1iso1displ_0jet_leadlpt"]->Fill(_lPt[i_leading_mu], event_weight);
            hists["1iso1displ_1jet_leadlpt"]->Fill(_lPt[i_leading_mu], event_weight);
            hists["1iso1displ_2jet_leadlpt"]->Fill(_lPt[i_leading_mu], event_weight);
        }
        else{


        }*/

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

    //for(auto&& sh : hists){
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
    gSystem->Exec("mkdir -p " + outputfilename);
    if(filename.Index("HeavyNeutrino") != -1) outputfilename += "hists_full_analyzer_" + filename(filename.Index("HeavyNeutrino_"), filename.Index("dilep.root") - 1 - filename.Index("HeavyNeutrino_")) + "_" + promptordisplaced  + ".root";
    else outputfilename += "hists_full_analyzer_Background_" + filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep.root") - filename.Index("heavyNeutrino") - 15) + ".root";
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
    hists["HLT_Ele27_WPTight_Gsf_pt_eff"]->Divide(hists["1_iso_ele_pt"]);
    hists["HLT_Ele27_WPTight_Gsf_barrel_pt_eff"]->Divide(hists["1_iso_ele_barrel_pt"]);
    hists["HLT_Ele27_WPTight_Gsf_endcap_pt_eff"]->Divide(hists["1_iso_ele_endcap_pt"]);
    hists["HLT_IsoMu24_IsoTkMu24_pt_eff"]->Divide(hists["1_iso_mu_pt"]);
    hists["HLT_IsoMu24_IsoTkMu24_barrel_pt_eff"]->Divide(hists["1_iso_mu_barrel_pt"]);
    hists["HLT_IsoMu24_IsoTkMu24_endcap_pt_eff"]->Divide(hists["1_iso_mu_endcap_pt"]);

    for(auto&& sh : hists){
        auto&& h = sh.second;
	    h->Write();
    }
    output->Close();
}

// DELETE AFTER NEXT ITERATION
/*void full_analyzer::get_electronID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	bool fullID = 	
            _lFlavor[i] == 0 &&
			fabs(_lEta[i]) < 2.5 &&
			_lPt[i] > 7 &&
			fabs(_dxy[i]) < 0.05 &&
			fabs(_dz[i])  < 0.1 &&
			_3dIPSig[i]   < 4 &&
			_relIso[i]    < 0.2 &&
			_lPOGMedium[i] &&
			_lElectronPassConvVeto[i] &&
			_lElectronMissingHits[i] < 1;
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}

void full_analyzer::get_noniso_electronID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	bool fullID = 	_lFlavor[i] == 0 &&
			fabs(_lEta[i]) < 2.5 &&
			_lPt[i] > 7 &&
			fabs(_dxy[i]) < 0.05 &&
			fabs(_dz[i])  < 0.1 &&
			_3dIPSig[i]   < 4 &&
			_relIso[i]    > 0.2 &&
			//_lPOGMedium[i] && //->clashes with reliso > 0.2
			_lElectronPassConvVeto[i] &&
			_lElectronMissingHits[i] < 1;
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}

void full_analyzer::get_displ_electronID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	bool fullID = 	_lFlavor[i] == 0 &&
			fabs(_lEta[i]) < 2.5 &&
			_lPt[i] > 7 &&
			fabs(_dxy[i])  > 0.05 &&
			//no dz cut
			//no SIP3D cut
			//also invert reliso?
			//no pogmedium?
			_lElectronPassConvVeto[i];//figure out how this one works exactly to be sure it can still be applied!
			//no missing hits cut?
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}


void full_analyzer::get_muonID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	bool fullID = 	_lFlavor[i] == 1 &&
			fabs(_lEta[i]) < 2.4 &&
			_lPt[i] > 5 &&
			fabs(_dxy[i]) < 0.05 &&
			fabs(_dz[i])  < 0.1 &&
			_3dIPSig[i]   < 4 &&
			_relIso[i]    < 0.2 &&
			_lPOGMedium[i];
			// innertrack, PFmuon and global or tracker muon conditions are executed at ntuplizer level and not stored
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}

void full_analyzer::get_noniso_muonID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	bool fullID = 	_lFlavor[i] == 1 &&
			fabs(_lEta[i]) < 2.4 &&
			_lPt[i] > 5 &&
			fabs(_dxy[i]) < 0.05 &&
			fabs(_dz[i])  < 0.1 &&
			_3dIPSig[i]   < 4 &&
			_relIso[i]    > 0.2 &&
			_lPOGMedium[i];
			// innertrack, PFmuon and global or tracker muon conditions are executed at ntuplizer level and not stored
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}

void full_analyzer::get_displ_muonID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	bool fullID = 	_lFlavor[i] == 1 &&
			fabs(_lEta[i]) < 2.4 &&
			_lPt[i] > 5 &&
			fabs(_dxy[i]) > 0.05;
			//no dz cut
			//no SIP3D cut
			//also invert reliso?
			//no POGMedium? no because it requires dxy of the track to be small 
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}



void full_analyzer::get_jetID(bool* ID)
{
    for(unsigned i = 0; i < _nJets; ++i){
	bool fullID = 	fabs(_jetEta[i]) < 2.4 &&
			_jetPt[i] > 20 &&
			_jetIsTight[i];
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}




void full_analyzer::get_clean_jets(bool* cleaned, bool* electronID, bool* muonID)
{
    // jets are cleaned from leptons if dR < 0.4 
    TLorentzVector lepton;
    TLorentzVector jet;

    for(unsigned i = 0; i < _nJets; ++i){
	*(cleaned + i) = true;
	jet.SetPtEtaPhiE(_jetPt[i], _jetEta[i], _jetPhi[i], _jetE[i]);

	for(unsigned j = 0; j < _nL; ++j){
	    lepton.SetPtEtaPhiE(_lPt[j], _lEta[j], _lPhi[j], _lE[j]);
	    if((_lFlavor[j] == 0 && *(electronID + j)) || (_lFlavor[j] == 1 && *(muonID + j))){
		if(lepton.DeltaR(jet) < 0.4) *(cleaned + i) = false;
	    }
	}
    }
}




void full_analyzer::get_clean_ele(bool* cleaned, bool* muonID)
{
    // This function returns false in the boolean cleaned for electrons within a cone of 0.4 around muons
    TLorentzVector muon;
    TLorentzVector electron;

    for(unsigned i_el = 0; i_el < _nL; ++i_el){
	    *(cleaned + i_el) = true;
	    if(_lFlavor[i_el] != 0) continue;
	    electron.SetPtEtaPhiE(_lPt[i_el], _lEta[i_el], _lPhi[i_el], _lE[i_el]);

	    for(unsigned i_mu = 0; i_mu < _nL; ++i_mu){
	        if(_lFlavor[i_mu] == 1 && *(muonID + i_mu)){
	    	muon.SetPtEtaPhiE(_lPt[i_mu], _lEta[i_mu], _lPhi[i_mu], _lE[i_mu]);
	    	if(muon.DeltaR(electron) < 0.4) *(cleaned + i_el) = false;
	        }
	    }
    }
}




int full_analyzer::find_leading_e(bool* electronID, bool* ele_clean)
{
    int index_good_leading = -1;
    for(unsigned i = 0; i < _nL; ++i){
	    if(_lFlavor[i] != 0)   continue;
	    if(!*(electronID + i)) continue;
	    if(!*(ele_clean + i))  continue;
	    //if(_lPt[i] < 30)       continue;
	    if(index_good_leading == -1) index_good_leading = i;
	    if(_lPt[i] > _lPt[index_good_leading]) index_good_leading = i;
    }
    return index_good_leading;
}

int full_analyzer::find_leading_mu(bool* muonID)
{
    int index_good_leading = -1;
    for(unsigned i = 0; i < _nL; ++i){
	    if(_lFlavor[i] != 1) continue;
	    if(!*(muonID + i))   continue;
	    //if(_lPt[i] < 25)     continue;
	    if(index_good_leading == -1) index_good_leading = i;
	    if(_lPt[i] > _lPt[index_good_leading]) index_good_leading = i;
    }
    return index_good_leading;
}

int full_analyzer::find_leading_jet(bool* jetID, bool* jet_clean)
{
    int index_good_leading = -1;
    for(unsigned i = 0; i < _nJets; ++i){
	    if(!*(jetID + i))      continue;
	    if(!*(jet_clean + i))  continue;
	    if(index_good_leading == -1) index_good_leading = i;
	    if(_lPt[i] > _lPt[index_good_leading]) index_good_leading = i;
    }
    return index_good_leading;
}

int full_analyzer::find_subleading_e(bool* electronID, bool* ele_clean, int index_good_leading)
{
    int index_good_subleading = -1;
    if(index_good_leading == -1) return index_good_subleading;
    for(int i = 0; i < _nL; ++i){
	    if(i == index_good_leading) continue;
	    if(_lFlavor[i] != 0)   	    continue;
	    //if(_lCharge[i] != _lCharge[index_good_leading]) continue;
	    if(!*(electronID + i))      continue;
	    if(!*(ele_clean + i))       continue;
	    if(_lPt[i] < 7)             continue;
	    if(index_good_subleading == -1) index_good_subleading = i;
	    if(_lPt[i] > _lPt[index_good_subleading]) index_good_subleading = i;
    }
    return index_good_subleading;
}

int full_analyzer::find_subleading_mu(bool* muonID, int index_good_leading)
{
    int index_good_subleading = -1;
    if(index_good_leading == -1) return index_good_subleading;
    for(int i = 0; i < _nL; ++i){
	    if(i == index_good_leading) continue;
	    if(_lFlavor[i] != 1)   	    continue;
	    //if(_lCharge[i] != _lCharge[index_good_leading]) continue;
	    if(!*(muonID + i))          continue;
	    if(_lPt[i] < 5)             continue;
	    if(index_good_subleading == -1) index_good_subleading = i;
	    if(_lPt[i] > _lPt[index_good_subleading]) index_good_subleading = i;
    }
    return index_good_subleading;
}

int full_analyzer::find_subleading_jet(bool* jetID, bool* jet_clean, int index_good_leading)
{
    int index_good_subleading = -1;
    if(index_good_leading == -1) return index_good_subleading;
    for(int i = 0; i < _nJets; ++i){
	    if(i == index_good_leading) continue;
	    if(!*(jetID + i))           continue;
	    if(!*(jet_clean + i))       continue;
	    if(index_good_subleading == -1) index_good_subleading = i;
	    if(_lPt[i] > _lPt[index_good_subleading]) index_good_subleading = i;
    }
    return index_good_subleading;
}*/


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
