
//Include C++ libraries
#include <iostream>

//Include header for this class
#include "../interface/full_analyzer_ee.h"

//Include ROOT header files
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TSystem.h>

using namespace std;

full_analyzer_ee::full_analyzer_ee(double b = 0){
    a = b;
}

double full_analyzer_ee::test(){

    TFile *input = new TFile("/user/bvermass/public/heavyNeutrino/displaced/HeavyNeutrino_lljj_M-4_V-0.004472135955_e_pre2017_leptonFirst_NLO/dilep.root", "open");
    TTree *tree  = (TTree*) input->Get("blackJackAndHookers/blackJackAndHookersTree");

    Long64_t nentries = tree->GetEntries();
    cout << "Number of events: " << nentries << endl;
    int maxentries = 300000;
    if(nentries > maxentries) nentries = maxentries;//CHANGE THIS, quick fix to not run too long
    //for(unsigned jentry = 0; jentry < nentries; ++jentry){
	//    b.LoadTree(jentry);
	//    tree->GetEntry(jentry);
    //    cout << _lPt[0] << endl;
    //}
    //cout << "a: " << a << endl << endl;
    return a;
}
