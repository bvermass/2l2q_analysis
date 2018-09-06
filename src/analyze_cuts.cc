#include <TROOT.h>
#include <TFile.h>
#include <TF1.h>
#include <TH2.h>
#include <TH1.h>
#include <THistPainter.h>
#include <TGraphAsymmErrors.h>
#include <TLatex.h>
#include <TTree.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <iostream>
#include <string>
#include <cmath>
#include <TRandom3.h>
#include <TKey.h>
#include <TSystem.h>
#include <THStack.h>

#include "../interface/analyze_cuts.h"

using namespace std;

# ifndef __CINT__
int main(int argc, char * argv[])
{
    TString pathname = "/user/bvermass/public/2l2q_analysis/log/";
    //This file contains everything regarding the optimization of cuts
    //Essential information is number of events left after a cut.
    //This can be put in several different histograms or in one histogram altogether
    //several histograms is more overseeable, while one histogram with bins is simpler to implement but less clear
    //manipulations: sums of histograms, divisions, ... lets start with one histogram and see how that works

    //for now: sum all background, 
    std::map<TString, TFile*> files;
    for(int i = 1; i < (argc + 1)/2; i++){
        files[argv[i]] = TFile::Open(argv[i]);
        cout << argv[i] << endl;
    }
    
    TFile * HNL3GeV_e_file = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-3_V-0.00836660026534_e_onshell_pre2017_leptonFirst_NLO_displaced.root");
    TFile * HNL3GeV_mu_file = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-3_V-0.00836660026534_mu_onshell_pre2017_leptonFirst_NLO_displaced.root");
    TFile * HNL7GeV_e_file = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-7_V-0.00244948974278_e_onshell_pre2017_leptonFirst_NLO_displaced.root");
    TFile * HNL7GeV_mu_file = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-7_V-0.00244948974278_mu_onshell_pre2017_leptonFirst_NLO_displaced.root");
    TFile * HNL10GeV_e_file = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-10_V-0.00244948974278_e_onshell_pre2017_leptonFirst_NLO_displaced.root");
    TFile * HNL10GeV_mu_file = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-10_V-0.00244948974278_mu_onshell_pre2017_leptonFirst_NLO_displaced.root");

    std::map<TString, TH1*> hists;

    //sum all background together for SS-OS, e-mu
    hists["bkg_displ_SS_mu_cuts"] = (TH1F*) files[argv[1]]->Get("displ_SS_mu_cuts");
    hists["bkg_displ_OS_mu_cuts"] = (TH1F*) files[argv[1]]->Get("displ_OS_mu_cuts");
    hists["bkg_displ_SS_e_cuts"] = (TH1F*) files[argv[1]]->Get("displ_SS_e_cuts");
    hists["bkg_displ_OS_e_cuts"] = (TH1F*) files[argv[1]]->Get("displ_OS_e_cuts");
    for(int i = 2; i < (argc + 1)/2; i++){
        hists["bkg_displ_SS_mu_cuts"]->Add((TH1F*)files[argv[i]]->Get("displ_SS_mu_cuts"));
        hists["bkg_displ_OS_mu_cuts"]->Add((TH1F*)files[argv[i]]->Get("displ_OS_mu_cuts"));
        hists["bkg_displ_SS_e_cuts"]->Add((TH1F*)files[argv[i]]->Get("displ_SS_e_cuts"));
        hists["bkg_displ_OS_e_cuts"]->Add((TH1F*)files[argv[i]]->Get("displ_OS_e_cuts"));
    }

    //get signal histograms
    hists["3GeV_displ_SS_mu_cuts"] = (TH1F*) HNL3GeV_mu_file->Get("displ_SS_mu_cuts");
    hists["3GeV_displ_OS_mu_cuts"] = (TH1F*) HNL3GeV_mu_file->Get("displ_OS_mu_cuts");
    hists["3GeV_displ_SS_e_cuts"] = (TH1F*) HNL3GeV_e_file->Get("displ_SS_e_cuts");
    hists["3GeV_displ_OS_e_cuts"] = (TH1F*) HNL3GeV_e_file->Get("displ_OS_e_cuts");
    hists["7GeV_displ_SS_mu_cuts"] = (TH1F*) HNL7GeV_mu_file->Get("displ_SS_mu_cuts");
    hists["7GeV_displ_OS_mu_cuts"] = (TH1F*) HNL7GeV_mu_file->Get("displ_OS_mu_cuts");
    hists["7GeV_displ_SS_e_cuts"] = (TH1F*) HNL7GeV_e_file->Get("displ_SS_e_cuts");
    hists["7GeV_displ_OS_e_cuts"] = (TH1F*) HNL7GeV_e_file->Get("displ_OS_e_cuts");
    hists["10GeV_displ_SS_mu_cuts"] = (TH1F*) HNL10GeV_mu_file->Get("displ_SS_mu_cuts");
    hists["10GeV_displ_OS_mu_cuts"] = (TH1F*) HNL10GeV_mu_file->Get("displ_OS_mu_cuts");
    hists["10GeV_displ_SS_e_cuts"] = (TH1F*) HNL10GeV_e_file->Get("displ_SS_e_cuts");
    hists["10GeV_displ_OS_e_cuts"] = (TH1F*) HNL10GeV_e_file->Get("displ_OS_e_cuts");

    //now get the efficiencies, dividing bins 8 and 9 by bin 7
    double _bkg_displ_SS_mu_oldID_eff = hists["bkg_displ_SS_mu_cuts"]->GetBinContent(4) / hists["bkg_displ_SS_mu_cuts"]->GetBinContent(3);
    double _bkg_displ_OS_mu_oldID_eff = hists["bkg_displ_OS_mu_cuts"]->GetBinContent(4) / hists["bkg_displ_OS_mu_cuts"]->GetBinContent(3);
    double _bkg_displ_SS_e_oldID_eff = hists["bkg_displ_SS_e_cuts"]->GetBinContent(4) / hists["bkg_displ_SS_e_cuts"]->GetBinContent(3);
    double _bkg_displ_OS_e_oldID_eff = hists["bkg_displ_OS_e_cuts"]->GetBinContent(4) / hists["bkg_displ_OS_e_cuts"]->GetBinContent(3);
    double _3GeV_displ_SS_mu_oldID_eff = hists["3GeV_displ_SS_mu_cuts"]->GetBinContent(4) / hists["3GeV_displ_SS_mu_cuts"]->GetBinContent(3);
    double _3GeV_displ_OS_mu_oldID_eff = hists["3GeV_displ_OS_mu_cuts"]->GetBinContent(4) / hists["3GeV_displ_OS_mu_cuts"]->GetBinContent(3);
    double _3GeV_displ_SS_e_oldID_eff = hists["3GeV_displ_SS_e_cuts"]->GetBinContent(4) / hists["3GeV_displ_SS_e_cuts"]->GetBinContent(3);
    double _3GeV_displ_OS_e_oldID_eff = hists["3GeV_displ_OS_e_cuts"]->GetBinContent(4) / hists["3GeV_displ_OS_e_cuts"]->GetBinContent(3);
    double _7GeV_displ_SS_mu_oldID_eff = hists["7GeV_displ_SS_mu_cuts"]->GetBinContent(4) / hists["7GeV_displ_SS_mu_cuts"]->GetBinContent(3);
    double _7GeV_displ_OS_mu_oldID_eff = hists["7GeV_displ_OS_mu_cuts"]->GetBinContent(4) / hists["7GeV_displ_OS_mu_cuts"]->GetBinContent(3);
    double _7GeV_displ_SS_e_oldID_eff = hists["7GeV_displ_SS_e_cuts"]->GetBinContent(4) / hists["7GeV_displ_SS_e_cuts"]->GetBinContent(3);
    double _7GeV_displ_OS_e_oldID_eff = hists["7GeV_displ_OS_e_cuts"]->GetBinContent(4) / hists["7GeV_displ_OS_e_cuts"]->GetBinContent(3);
    double _10GeV_displ_SS_mu_oldID_eff = hists["10GeV_displ_SS_mu_cuts"]->GetBinContent(4) / hists["10GeV_displ_SS_mu_cuts"]->GetBinContent(3);
    double _10GeV_displ_OS_mu_oldID_eff = hists["10GeV_displ_OS_mu_cuts"]->GetBinContent(4) / hists["10GeV_displ_OS_mu_cuts"]->GetBinContent(3);
    double _10GeV_displ_SS_e_oldID_eff = hists["10GeV_displ_SS_e_cuts"]->GetBinContent(4) / hists["10GeV_displ_SS_e_cuts"]->GetBinContent(3);
    double _10GeV_displ_OS_e_oldID_eff = hists["10GeV_displ_OS_e_cuts"]->GetBinContent(4) / hists["10GeV_displ_OS_e_cuts"]->GetBinContent(3);

    double _bkg_displ_SS_mu_newID_eff = hists["bkg_displ_SS_mu_cuts"]->GetBinContent(5) / hists["bkg_displ_SS_mu_cuts"]->GetBinContent(3);
    double _bkg_displ_OS_mu_newID_eff = hists["bkg_displ_OS_mu_cuts"]->GetBinContent(5) / hists["bkg_displ_OS_mu_cuts"]->GetBinContent(3);
    double _bkg_displ_SS_e_newID_eff = hists["bkg_displ_SS_e_cuts"]->GetBinContent(5) / hists["bkg_displ_SS_e_cuts"]->GetBinContent(3);
    double _bkg_displ_OS_e_newID_eff = hists["bkg_displ_OS_e_cuts"]->GetBinContent(5) / hists["bkg_displ_OS_e_cuts"]->GetBinContent(3);
    double _3GeV_displ_SS_mu_newID_eff = hists["3GeV_displ_SS_mu_cuts"]->GetBinContent(5) / hists["3GeV_displ_SS_mu_cuts"]->GetBinContent(3);
    double _3GeV_displ_OS_mu_newID_eff = hists["3GeV_displ_OS_mu_cuts"]->GetBinContent(5) / hists["3GeV_displ_OS_mu_cuts"]->GetBinContent(3);
    double _3GeV_displ_SS_e_newID_eff = hists["3GeV_displ_SS_e_cuts"]->GetBinContent(5) / hists["3GeV_displ_SS_e_cuts"]->GetBinContent(3);
    double _3GeV_displ_OS_e_newID_eff = hists["3GeV_displ_OS_e_cuts"]->GetBinContent(5) / hists["3GeV_displ_OS_e_cuts"]->GetBinContent(3);
    double _7GeV_displ_SS_mu_newID_eff = hists["7GeV_displ_SS_mu_cuts"]->GetBinContent(5) / hists["7GeV_displ_SS_mu_cuts"]->GetBinContent(3);
    double _7GeV_displ_OS_mu_newID_eff = hists["7GeV_displ_OS_mu_cuts"]->GetBinContent(5) / hists["7GeV_displ_OS_mu_cuts"]->GetBinContent(3);
    double _7GeV_displ_SS_e_newID_eff = hists["7GeV_displ_SS_e_cuts"]->GetBinContent(5) / hists["7GeV_displ_SS_e_cuts"]->GetBinContent(3);
    double _7GeV_displ_OS_e_newID_eff = hists["7GeV_displ_OS_e_cuts"]->GetBinContent(5) / hists["7GeV_displ_OS_e_cuts"]->GetBinContent(3);
    double _10GeV_displ_SS_mu_newID_eff = hists["10GeV_displ_SS_mu_cuts"]->GetBinContent(5) / hists["10GeV_displ_SS_mu_cuts"]->GetBinContent(3);
    double _10GeV_displ_OS_mu_newID_eff = hists["10GeV_displ_OS_mu_cuts"]->GetBinContent(5) / hists["10GeV_displ_OS_mu_cuts"]->GetBinContent(3);
    double _10GeV_displ_SS_e_newID_eff = hists["10GeV_displ_SS_e_cuts"]->GetBinContent(5) / hists["10GeV_displ_SS_e_cuts"]->GetBinContent(3);
    double _10GeV_displ_OS_e_newID_eff = hists["10GeV_displ_OS_e_cuts"]->GetBinContent(5) / hists["10GeV_displ_OS_e_cuts"]->GetBinContent(3);

    
    cout << endl << endl << "SS mu" << endl;
    cout << "oldID bkg, 3, 7, 10 : " << _bkg_displ_SS_mu_oldID_eff << " " << _3GeV_displ_SS_mu_oldID_eff << " " << _7GeV_displ_SS_mu_oldID_eff << " " << _10GeV_displ_SS_mu_oldID_eff << endl;
    cout << "newID bkg, 3, 7, 10 : " << _bkg_displ_SS_mu_newID_eff << " " << _3GeV_displ_SS_mu_newID_eff << " " << _7GeV_displ_SS_mu_newID_eff << " " << _10GeV_displ_SS_mu_newID_eff << endl;
    cout << endl << endl << "OS mu" << endl;
    cout << "oldID bkg, 3, 7, 10 : " << _bkg_displ_OS_mu_oldID_eff << " " << _3GeV_displ_OS_mu_oldID_eff << " " << _7GeV_displ_OS_mu_oldID_eff << " " << _10GeV_displ_OS_mu_oldID_eff << endl;
    cout << "newID bkg, 3, 7, 10 : " << _bkg_displ_OS_mu_newID_eff << " " << _3GeV_displ_OS_mu_newID_eff << " " << _7GeV_displ_OS_mu_newID_eff << " " << _10GeV_displ_OS_mu_newID_eff << endl;
    cout << endl << endl << "SS e" << endl;
    cout << "oldID bkg, 3, 7, 10 : " << _bkg_displ_SS_e_oldID_eff << " " << _3GeV_displ_SS_e_oldID_eff << " " << _7GeV_displ_SS_e_oldID_eff << " " << _10GeV_displ_SS_e_oldID_eff << endl;
    cout << "newID bkg, 3, 7, 10 : " << _bkg_displ_SS_e_newID_eff << " " << _3GeV_displ_SS_e_newID_eff << " " << _7GeV_displ_SS_e_newID_eff << " " << _10GeV_displ_SS_e_newID_eff << endl;
    cout << endl << endl << "OS e" << endl;
    cout << "oldID bkg, 3, 7, 10 : " << _bkg_displ_OS_e_oldID_eff << " " << _3GeV_displ_OS_e_oldID_eff << " " << _7GeV_displ_OS_e_oldID_eff << " " << _10GeV_displ_OS_e_oldID_eff << endl;
    cout << "newID bkg, 3, 7, 10 : " << _bkg_displ_OS_e_newID_eff << " " << _3GeV_displ_OS_e_newID_eff << " " << _7GeV_displ_OS_e_newID_eff << " " << _10GeV_displ_OS_e_newID_eff << endl;

    return 0;
}
# endif
