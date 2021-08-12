#ifndef PFN_efficiency_cc
#define PFN_efficiency_cc

// c++ libraries
#include <iostream>
#include <cmath>

// root libraries
#include <TROOT.h>
#include <TSystem.h>
#include <TKey.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <THStack.h>
#include <TGraphAsymmErrors.h>
#include <TMultiGraph.h>
#include <TLatex.h>

// other header files
#include "../../plotting/tdrStyle.h"
#include "../../plotting/helper_plotter_functions.h"
#include "../../interface/helper_histo_functions.h"
#include "../../interface/mini_analyzer.h"

TString filename_e_2016_2GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-2_V-combined_e_massiveAndCKM_LO_MiniAOD2016.root";
TString filename_e_2016_5GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-5_V-combined_e_massiveAndCKM_LO_MiniAOD2016.root";
TString filename_e_2016_8GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-8_V-combined_e_massiveAndCKM_LO_MiniAOD2016.root";
TString filename_e_2016_12GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-12_V-combined_e_massiveAndCKM_LO_MiniAOD2016.root";
TString filename_mu_2016_2GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-2_V-combined_mu_massiveAndCKM_LO_MiniAOD2016.root";
TString filename_mu_2016_5GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-5_V-combined_mu_massiveAndCKM_LO_MiniAOD2016.root";
TString filename_mu_2016_8GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-8_V-combined_mu_massiveAndCKM_LO_MiniAOD2016.root";
TString filename_mu_2016_12GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-12_V-combined_mu_massiveAndCKM_LO_MiniAOD2016.root";
TString filename_2l_2016_2GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-2_V-combined_2l_massiveAndCKM_LO_MiniAOD2016.root";
TString filename_2l_2016_5GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-5_V-combined_2l_massiveAndCKM_LO_MiniAOD2016.root";
TString filename_2l_2016_8GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-8_V-combined_2l_massiveAndCKM_LO_MiniAOD2016.root";
TString filename_2l_2016_12GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-12_V-combined_2l_massiveAndCKM_LO_MiniAOD2016.root";

TString filename_e_2017_2GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-2_V-combined_e_massiveAndCKM_LO_MiniAOD2017.root";
TString filename_e_2017_5GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-5_V-combined_e_massiveAndCKM_LO_MiniAOD2017.root";
TString filename_e_2017_8GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-8_V-combined_e_massiveAndCKM_LO_MiniAOD2017.root";
TString filename_e_2017_12GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-12_V-combined_e_massiveAndCKM_LO_MiniAOD2017.root";
TString filename_mu_2017_2GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-2_V-combined_mu_massiveAndCKM_LO_MiniAOD2017.root";
TString filename_mu_2017_5GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-5_V-combined_mu_massiveAndCKM_LO_MiniAOD2017.root";
TString filename_mu_2017_8GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-8_V-combined_mu_massiveAndCKM_LO_MiniAOD2017.root";
TString filename_mu_2017_12GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-12_V-combined_mu_massiveAndCKM_LO_MiniAOD2017.root";
TString filename_2l_2017_2GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-2_V-combined_2l_massiveAndCKM_LO_MiniAOD2017.root";
TString filename_2l_2017_5GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-5_V-combined_2l_massiveAndCKM_LO_MiniAOD2017.root";
TString filename_2l_2017_8GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-8_V-combined_2l_massiveAndCKM_LO_MiniAOD2017.root";
TString filename_2l_2017_12GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-12_V-combined_2l_massiveAndCKM_LO_MiniAOD2017.root";

TString filename_e_2018_2GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-2_V-combined_e_massiveAndCKM_LO_MiniAOD2018.root";
TString filename_e_2018_5GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-5_V-combined_e_massiveAndCKM_LO_MiniAOD2018.root";
TString filename_e_2018_8GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-8_V-combined_e_massiveAndCKM_LO_MiniAOD2018.root";
TString filename_e_2018_12GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-12_V-combined_e_massiveAndCKM_LO_MiniAOD2018.root";
TString filename_mu_2018_2GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-2_V-combined_mu_massiveAndCKM_LO_MiniAOD2018.root";
TString filename_mu_2018_5GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-5_V-combined_mu_massiveAndCKM_LO_MiniAOD2018.root";
TString filename_mu_2018_8GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-8_V-combined_mu_massiveAndCKM_LO_MiniAOD2018.root";
TString filename_mu_2018_12GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-12_V-combined_mu_massiveAndCKM_LO_MiniAOD2018.root";
TString filename_2l_2018_2GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-2_V-combined_2l_massiveAndCKM_LO_MiniAOD2018.root";
TString filename_2l_2018_5GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-5_V-combined_2l_massiveAndCKM_LO_MiniAOD2018.root";
TString filename_2l_2018_8GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-8_V-combined_2l_massiveAndCKM_LO_MiniAOD2018.root";
TString filename_2l_2018_12GeV = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-12_V-combined_2l_massiveAndCKM_LO_MiniAOD2018.root";

TString filename_2016_Bkg = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_Background_MiniAOD2016.root";
TString filename_2017_Bkg = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_Background_MiniAOD2017.root";
TString filename_2018_Bkg = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_Background_MiniAOD2018.root";

# ifndef __CINT__ 
int main(int argc, char * argv[])
{
    std::map<TString, double> PFNcuts;
    PFNcuts["ee_2016_2GeV"] = get_NewPFNcut(5, 0, 0, true, false);
    PFNcuts["ee_2016_5GeV"] = get_NewPFNcut(5, 0, 0, true, false);
    PFNcuts["ee_2016_8GeV"] = get_NewPFNcut(10, 0, 0, true, false);
    PFNcuts["ee_2016_12GeV"] = get_NewPFNcut(10, 0, 0, true, false);
    PFNcuts["mm_2016_2GeV"] = get_NewPFNcut(5, 1, 1, true, false);
    PFNcuts["mm_2016_5GeV"] = get_NewPFNcut(5, 1, 1, true, false);
    PFNcuts["mm_2016_8GeV"] = get_NewPFNcut(10, 1, 1, true, false);
    PFNcuts["mm_2016_12GeV"] = get_NewPFNcut(10, 1, 1, true, false);
    PFNcuts["ee_2017_2GeV"] = get_NewPFNcut(5, 0, 0, false, true);
    PFNcuts["ee_2017_5GeV"] = get_NewPFNcut(5, 0, 0, false, true);
    PFNcuts["ee_2017_8GeV"] = get_NewPFNcut(10, 0, 0, false, true);
    PFNcuts["ee_2017_12GeV"] = get_NewPFNcut(10, 0, 0, false, true);
    PFNcuts["mm_2017_2GeV"] = get_NewPFNcut(5, 1, 1, false, true);
    PFNcuts["mm_2017_5GeV"] = get_NewPFNcut(5, 1, 1, false, true);
    PFNcuts["mm_2017_8GeV"] = get_NewPFNcut(10, 1, 1, false, true);
    PFNcuts["mm_2017_12GeV"] = get_NewPFNcut(10, 1, 1, false, true);
    PFNcuts["ee_2018_2GeV"] = get_NewPFNcut(5, 0, 0, false, false);
    PFNcuts["ee_2018_5GeV"] = get_NewPFNcut(5, 0, 0, false, false);
    PFNcuts["ee_2018_8GeV"] = get_NewPFNcut(10, 0, 0, false, false);
    PFNcuts["ee_2018_12GeV"] = get_NewPFNcut(10, 0, 0, false, false);
    PFNcuts["mm_2018_2GeV"] = get_NewPFNcut(5, 1, 1, false, false);
    PFNcuts["mm_2018_5GeV"] = get_NewPFNcut(5, 1, 1, false, false);
    PFNcuts["mm_2018_8GeV"] = get_NewPFNcut(10, 1, 1, false, false);
    PFNcuts["mm_2018_12GeV"] = get_NewPFNcut(10, 1, 1, false, false);

    PFNcuts["em_2016_2GeV"] = get_NewPFNcut(5, 0, 1, true, false);
    PFNcuts["em_2016_5GeV"] = get_NewPFNcut(5, 0, 1, true, false);
    PFNcuts["em_2016_8GeV"] = get_NewPFNcut(10, 0, 1, true, false);
    PFNcuts["em_2016_12GeV"] = get_NewPFNcut(10, 0, 1, true, false);
    PFNcuts["me_2016_2GeV"] = get_NewPFNcut(5, 1, 0, true, false);
    PFNcuts["me_2016_5GeV"] = get_NewPFNcut(5, 1, 0, true, false);
    PFNcuts["me_2016_8GeV"] = get_NewPFNcut(10, 1, 0, true, false);
    PFNcuts["me_2016_12GeV"] = get_NewPFNcut(10, 1, 0, true, false);
    PFNcuts["em_2017_2GeV"] = get_NewPFNcut(5, 0, 1, false, true);
    PFNcuts["em_2017_5GeV"] = get_NewPFNcut(5, 0, 1, false, true);
    PFNcuts["em_2017_8GeV"] = get_NewPFNcut(10, 0, 1, false, true);
    PFNcuts["em_2017_12GeV"] = get_NewPFNcut(10, 0, 1, false, true);
    PFNcuts["me_2017_2GeV"] = get_NewPFNcut(5, 1, 0, false, true);
    PFNcuts["me_2017_5GeV"] = get_NewPFNcut(5, 1, 0, false, true);
    PFNcuts["me_2017_8GeV"] = get_NewPFNcut(10, 1, 0, false, true);
    PFNcuts["me_2017_12GeV"] = get_NewPFNcut(10, 1, 0, false, true);
    PFNcuts["em_2018_2GeV"] = get_NewPFNcut(5, 0, 1, false, false);
    PFNcuts["em_2018_5GeV"] = get_NewPFNcut(5, 0, 1, false, false);
    PFNcuts["em_2018_8GeV"] = get_NewPFNcut(10, 0, 1, false, false);
    PFNcuts["em_2018_12GeV"] = get_NewPFNcut(10, 0, 1, false, false);
    PFNcuts["me_2018_2GeV"] = get_NewPFNcut(5, 1, 0, false, false);
    PFNcuts["me_2018_5GeV"] = get_NewPFNcut(5, 1, 0, false, false);
    PFNcuts["me_2018_8GeV"] = get_NewPFNcut(10, 1, 0, false, false);
    PFNcuts["me_2018_12GeV"] = get_NewPFNcut(10, 1, 0, false, false);

    PFNcuts["ee_2016_5Bkg"] = get_NewPFNcut(5, 0, 0, true, false);
    PFNcuts["ee_2016_10Bkg"] = get_NewPFNcut(10, 0, 0, true, false);
    PFNcuts["mm_2016_5Bkg"] = get_NewPFNcut(5, 1, 1, true, false);
    PFNcuts["mm_2016_10Bkg"] = get_NewPFNcut(10, 1, 1, true, false);
    PFNcuts["ee_2017_5Bkg"] = get_NewPFNcut(5, 0, 0, false, true);
    PFNcuts["ee_2017_10Bkg"] = get_NewPFNcut(10, 0, 0, false, true);
    PFNcuts["mm_2017_5Bkg"] = get_NewPFNcut(5, 1, 1, false, true);
    PFNcuts["mm_2017_10Bkg"] = get_NewPFNcut(10, 1, 1, false, true);
    PFNcuts["ee_2018_5Bkg"] = get_NewPFNcut(5, 0, 0, false, false);
    PFNcuts["ee_2018_10Bkg"] = get_NewPFNcut(10, 0, 0, false, false);
    PFNcuts["mm_2018_5Bkg"] = get_NewPFNcut(5, 1, 1, false, false);
    PFNcuts["mm_2018_10Bkg"] = get_NewPFNcut(10, 1, 1, false, false);
    PFNcuts["em_2016_5Bkg"] = get_NewPFNcut(5, 0, 1, true, false);
    PFNcuts["em_2016_10Bkg"] = get_NewPFNcut(10, 0, 1, true, false);
    PFNcuts["me_2016_5Bkg"] = get_NewPFNcut(5, 1, 0, true, false);
    PFNcuts["me_2016_10Bkg"] = get_NewPFNcut(10, 1, 0, true, false);
    PFNcuts["em_2017_5Bkg"] = get_NewPFNcut(5, 0, 1, false, true);
    PFNcuts["em_2017_10Bkg"] = get_NewPFNcut(10, 0, 1, false, true);
    PFNcuts["me_2017_5Bkg"] = get_NewPFNcut(5, 1, 0, false, true);
    PFNcuts["me_2017_10Bkg"] = get_NewPFNcut(10, 1, 0, false, true);
    PFNcuts["em_2018_5Bkg"] = get_NewPFNcut(5, 0, 1, false, false);
    PFNcuts["em_2018_10Bkg"] = get_NewPFNcut(10, 0, 1, false, false);
    PFNcuts["me_2018_5Bkg"] = get_NewPFNcut(5, 1, 0, false, false);
    PFNcuts["me_2018_10Bkg"] = get_NewPFNcut(10, 1, 0, false, false);

    std::map<TString, double> PFNcuts_0p9;
    PFNcuts_0p9["e_2016_2GeV"] =  0.9; 
    PFNcuts_0p9["e_2016_5GeV"] =  0.9;
    PFNcuts_0p9["e_2016_8GeV"] =  0.9;
    PFNcuts_0p9["e_2016_12GeV"] = 0.9;
    PFNcuts_0p9["m_2016_2GeV"] =  0.9;
    PFNcuts_0p9["m_2016_5GeV"] =  0.9;
    PFNcuts_0p9["m_2016_8GeV"] =  0.9;
    PFNcuts_0p9["m_2016_12GeV"] = 0.9;
    PFNcuts_0p9["e_2017_2GeV"] =  0.9;
    PFNcuts_0p9["e_2017_5GeV"] =  0.9;
    PFNcuts_0p9["e_2017_8GeV"] =  0.9;
    PFNcuts_0p9["e_2017_12GeV"] = 0.9;
    PFNcuts_0p9["m_2017_2GeV"] =  0.9;
    PFNcuts_0p9["m_2017_5GeV"] =  0.9;
    PFNcuts_0p9["m_2017_8GeV"] =  0.9;
    PFNcuts_0p9["m_2017_12GeV"] = 0.9;
    PFNcuts_0p9["e_2018_2GeV"] =  0.9;
    PFNcuts_0p9["e_2018_5GeV"] =  0.9;
    PFNcuts_0p9["e_2018_8GeV"] =  0.9;
    PFNcuts_0p9["e_2018_12GeV"] = 0.9;
    PFNcuts_0p9["m_2018_2GeV"] =  0.9;
    PFNcuts_0p9["m_2018_5GeV"] =  0.9;
    PFNcuts_0p9["m_2018_8GeV"] =  0.9;
    PFNcuts_0p9["m_2018_12GeV"] = 0.9;

    PFNcuts_0p9["e_2016_5Bkg"] =  0.9;
    PFNcuts_0p9["e_2016_10Bkg"] = 0.9;
    PFNcuts_0p9["m_2016_5Bkg"] =  0.9;
    PFNcuts_0p9["m_2016_10Bkg"] = 0.9;
    PFNcuts_0p9["e_2017_5Bkg"] =  0.9;
    PFNcuts_0p9["e_2017_10Bkg"] = 0.9;
    PFNcuts_0p9["m_2017_5Bkg"] =  0.9;
    PFNcuts_0p9["m_2017_10Bkg"] = 0.9;
    PFNcuts_0p9["e_2018_5Bkg"] =  0.9;
    PFNcuts_0p9["e_2018_10Bkg"] = 0.9;
    PFNcuts_0p9["m_2018_5Bkg"] =  0.9;
    PFNcuts_0p9["m_2018_10Bkg"] = 0.9; 


    std::map<TString, TFile*> files;
    files["e_2016_2GeV"] = TFile::Open(filename_e_2016_2GeV);
    files["e_2016_5GeV"] = TFile::Open(filename_e_2016_5GeV);
    files["e_2016_8GeV"] = TFile::Open(filename_e_2016_8GeV);
    files["e_2016_12GeV"] = TFile::Open(filename_e_2016_12GeV);
    files["m_2016_2GeV"] = TFile::Open(filename_mu_2016_2GeV);
    files["m_2016_5GeV"] = TFile::Open(filename_mu_2016_5GeV);
    files["m_2016_8GeV"] = TFile::Open(filename_mu_2016_8GeV);
    files["m_2016_12GeV"] = TFile::Open(filename_mu_2016_12GeV);
    files["2l_2016_2GeV"] = TFile::Open(filename_2l_2016_2GeV);
    files["2l_2016_5GeV"] = TFile::Open(filename_2l_2016_5GeV);
    files["2l_2016_8GeV"] = TFile::Open(filename_2l_2016_8GeV);
    files["2l_2016_12GeV"] = TFile::Open(filename_2l_2016_12GeV);
    files["e_2017_2GeV"] = TFile::Open(filename_e_2017_2GeV);
    files["e_2017_5GeV"] = TFile::Open(filename_e_2017_5GeV);
    files["e_2017_8GeV"] = TFile::Open(filename_e_2017_8GeV);
    files["e_2017_12GeV"] = TFile::Open(filename_e_2017_12GeV);
    files["m_2017_2GeV"] = TFile::Open(filename_mu_2017_2GeV);
    files["m_2017_5GeV"] = TFile::Open(filename_mu_2017_5GeV);
    files["m_2017_8GeV"] = TFile::Open(filename_mu_2017_8GeV);
    files["m_2017_12GeV"] = TFile::Open(filename_mu_2017_12GeV);
    files["2l_2017_2GeV"] = TFile::Open(filename_2l_2017_2GeV);
    files["2l_2017_5GeV"] = TFile::Open(filename_2l_2017_5GeV);
    files["2l_2017_8GeV"] = TFile::Open(filename_2l_2017_8GeV);
    files["2l_2017_12GeV"] = TFile::Open(filename_2l_2017_12GeV);
    files["e_2018_2GeV"] = TFile::Open(filename_e_2018_2GeV);
    files["e_2018_5GeV"] = TFile::Open(filename_e_2018_5GeV);
    files["e_2018_8GeV"] = TFile::Open(filename_e_2018_8GeV);
    files["e_2018_12GeV"] = TFile::Open(filename_e_2018_12GeV);
    files["m_2018_2GeV"] = TFile::Open(filename_mu_2018_2GeV);
    files["m_2018_5GeV"] = TFile::Open(filename_mu_2018_5GeV);
    files["m_2018_8GeV"] = TFile::Open(filename_mu_2018_8GeV);
    files["m_2018_12GeV"] = TFile::Open(filename_mu_2018_12GeV);
    files["2l_2018_2GeV"] = TFile::Open(filename_2l_2018_2GeV);
    files["2l_2018_5GeV"] = TFile::Open(filename_2l_2018_5GeV);
    files["2l_2018_8GeV"] = TFile::Open(filename_2l_2018_8GeV);
    files["2l_2018_12GeV"] = TFile::Open(filename_2l_2018_12GeV);

    files["e_2016_5Bkg"] = TFile::Open(filename_2016_Bkg);
    files["e_2017_5Bkg"] = TFile::Open(filename_2017_Bkg);
    files["e_2018_5Bkg"] = TFile::Open(filename_2018_Bkg);
    files["m_2016_5Bkg"] = files["e_2016_5Bkg"];
    files["m_2017_5Bkg"] = files["e_2017_5Bkg"];
    files["m_2018_5Bkg"] = files["e_2018_5Bkg"];
    files["2l_2016_5Bkg"] = files["e_2016_5Bkg"];
    files["2l_2017_5Bkg"] = files["e_2017_5Bkg"];
    files["2l_2018_5Bkg"] = files["e_2018_5Bkg"];
    files["e_2016_10Bkg"] = files["e_2016_5Bkg"];
    files["e_2017_10Bkg"] = files["e_2017_5Bkg"];
    files["e_2018_10Bkg"] = files["e_2018_5Bkg"];
    files["m_2016_10Bkg"] = files["e_2016_5Bkg"];
    files["m_2017_10Bkg"] = files["e_2017_5Bkg"];
    files["m_2018_10Bkg"] = files["e_2018_5Bkg"];
    files["2l_2016_10Bkg"] = files["e_2016_5Bkg"];
    files["2l_2017_10Bkg"] = files["e_2017_5Bkg"];
    files["2l_2018_10Bkg"] = files["e_2018_5Bkg"];

    std::map<TString, TH1F*> hists;
    hists["e_2016_2GeV"] = (TH1F*)files["e_2016_2GeV"]->Get("_ee"+get_MV2name(5,get_favorite_V2(2,"e"))+"_PFN_ROC");
    hists["e_2016_5GeV"] = (TH1F*)files["e_2016_5GeV"]->Get("_ee"+get_MV2name(5,get_favorite_V2(5,"e"))+"_PFN_ROC");
    hists["e_2016_8GeV"] = (TH1F*)files["e_2016_8GeV"]->Get("_ee"+get_MV2name(10,get_favorite_V2(8,"e"))+"_PFN_ROC");
    hists["e_2016_12GeV"] = (TH1F*)files["e_2016_12GeV"]->Get("_ee"+get_MV2name(10,get_favorite_V2(12,"e"))+"_PFN_ROC");
    hists["m_2016_2GeV"] = (TH1F*)files["m_2016_2GeV"]->Get("_mm"+get_MV2name(5,get_favorite_V2(2,"mu"))+"_PFN_ROC");
    hists["m_2016_5GeV"] = (TH1F*)files["m_2016_5GeV"]->Get("_mm"+get_MV2name(5,get_favorite_V2(5,"mu"))+"_PFN_ROC");
    hists["m_2016_8GeV"] = (TH1F*)files["m_2016_8GeV"]->Get("_mm"+get_MV2name(10,get_favorite_V2(8,"mu"))+"_PFN_ROC");
    hists["m_2016_12GeV"] = (TH1F*)files["m_2016_12GeV"]->Get("_mm"+get_MV2name(10,get_favorite_V2(12,"mu"))+"_PFN_ROC");
    hists["e_2017_2GeV"] = (TH1F*)files["e_2017_2GeV"]->Get("_ee"+get_MV2name(5,get_favorite_V2(2,"e"))+"_PFN_ROC");
    hists["e_2017_5GeV"] = (TH1F*)files["e_2017_5GeV"]->Get("_ee"+get_MV2name(5,get_favorite_V2(5,"e"))+"_PFN_ROC");
    hists["e_2017_8GeV"] = (TH1F*)files["e_2017_8GeV"]->Get("_ee"+get_MV2name(10,get_favorite_V2(8,"e"))+"_PFN_ROC");
    hists["e_2017_12GeV"] = (TH1F*)files["e_2017_12GeV"]->Get("_ee"+get_MV2name(10,get_favorite_V2(12,"e"))+"_PFN_ROC");
    hists["m_2017_2GeV"] = (TH1F*)files["m_2017_2GeV"]->Get("_mm"+get_MV2name(5,get_favorite_V2(2,"mu"))+"_PFN_ROC");
    hists["m_2017_5GeV"] = (TH1F*)files["m_2017_5GeV"]->Get("_mm"+get_MV2name(5,get_favorite_V2(5,"mu"))+"_PFN_ROC");
    hists["m_2017_8GeV"] = (TH1F*)files["m_2017_8GeV"]->Get("_mm"+get_MV2name(10,get_favorite_V2(8,"mu"))+"_PFN_ROC");
    hists["m_2017_12GeV"] = (TH1F*)files["m_2017_12GeV"]->Get("_mm"+get_MV2name(10,get_favorite_V2(12,"mu"))+"_PFN_ROC");
    hists["e_2018_2GeV"] = (TH1F*)files["e_2018_2GeV"]->Get("_ee"+get_MV2name(5,get_favorite_V2(2,"e"))+"_PFN_ROC");
    hists["e_2018_5GeV"] = (TH1F*)files["e_2018_5GeV"]->Get("_ee"+get_MV2name(5,get_favorite_V2(5,"e"))+"_PFN_ROC");
    hists["e_2018_8GeV"] = (TH1F*)files["e_2018_8GeV"]->Get("_ee"+get_MV2name(10,get_favorite_V2(8,"e"))+"_PFN_ROC");
    hists["e_2018_12GeV"] = (TH1F*)files["e_2018_12GeV"]->Get("_ee"+get_MV2name(10,get_favorite_V2(12,"e"))+"_PFN_ROC");
    hists["m_2018_2GeV"] = (TH1F*)files["m_2018_2GeV"]->Get("_mm"+get_MV2name(5,get_favorite_V2(2,"mu"))+"_PFN_ROC");
    hists["m_2018_5GeV"] = (TH1F*)files["m_2018_5GeV"]->Get("_mm"+get_MV2name(5,get_favorite_V2(5,"mu"))+"_PFN_ROC");
    hists["m_2018_8GeV"] = (TH1F*)files["m_2018_8GeV"]->Get("_mm"+get_MV2name(10,get_favorite_V2(8,"mu"))+"_PFN_ROC");
    hists["m_2018_12GeV"] = (TH1F*)files["m_2018_12GeV"]->Get("_mm"+get_MV2name(10,get_favorite_V2(12,"mu"))+"_PFN_ROC");

    hists["e_2016_5Bkg"] = (TH1F*)files["e_2016_5Bkg"]->Get("_ee"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    hists["e_2017_5Bkg"] = (TH1F*)files["e_2017_5Bkg"]->Get("_ee"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    hists["e_2018_5Bkg"] = (TH1F*)files["e_2018_5Bkg"]->Get("_ee"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    hists["m_2016_5Bkg"] = (TH1F*)files["m_2016_5Bkg"]->Get("_mm"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    hists["m_2017_5Bkg"] = (TH1F*)files["m_2017_5Bkg"]->Get("_mm"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    hists["m_2018_5Bkg"] = (TH1F*)files["m_2018_5Bkg"]->Get("_mm"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    hists["e_2016_10Bkg"] = (TH1F*)files["e_2016_10Bkg"]->Get("_ee"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    hists["e_2017_10Bkg"] = (TH1F*)files["e_2017_10Bkg"]->Get("_ee"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    hists["e_2018_10Bkg"] = (TH1F*)files["e_2018_10Bkg"]->Get("_ee"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    hists["m_2016_10Bkg"] = (TH1F*)files["m_2016_10Bkg"]->Get("_mm"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");
    hists["m_2017_10Bkg"] = (TH1F*)files["m_2017_10Bkg"]->Get("_mm"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");
    hists["m_2018_10Bkg"] = (TH1F*)files["m_2018_10Bkg"]->Get("_mm"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");


    //for(const TString& mass : {"2","5","8","12"}){
    //    for(std::string flavor : {"e", "mu"}){
    //        for(const TString& year : {"2016", "2017", "2018"}){
    //            double V2 = get_favorite_V2(std::atoi(mass), flavor);
    //            TString MV2name = get_MV2name((mass == "2" or mass == "5")? 5 : 10, V2);
    //            TString fl = flavor.substr(0,1);
    //            std::cout << fl+"_"+year+"_"+mass+"GeV" << ": " << "_"+fl+fl+MV2name+"_PFN_ROC" << std::endl;
    //            hists[fl+"_"+year+"_"+mass+ "GeV"] = (TH1F*)files[fl+"_"+year+"_"+mass+"GeV"]->Get("_"+fl+fl+MV2name+"_PFN_ROC");
    //        }
    //    }
    //}
    //for(const TString& mass : {"5","10"}){
    //    for(std::string flavor : {"e", "mu"}){
    //        for(const TString& year : {"2016", "2017", "2018"}){
    //            double V2 = get_favorite_V2(std::atoi(mass), flavor);
    //            TString MV2name = get_MV2name((mass == "5")? 5 : 10, V2);
    //            TString fl = flavor.substr(0,1);
    //            std::cout << fl+"_"+year+"_"+mass+"Bkg" << ": " << "_"+fl+fl+MV2name+"_PFN_ROC" << std::endl;
    //            hists[fl+"_"+year+"_"+mass+ "Bkg"] = (TH1F*)files[fl+"_"+year+"_"+mass+"Bkg"]->Get("_"+fl+fl+MV2name+"_PFN_ROC");
    //        }
    //    }
    //}


    std::map<TString, std::vector<double>> effs;
    effs["e_2016_2GeV"] = computeEfficiencyForROC(hists["e_2016_2GeV"]);
    effs["e_2016_5GeV"] = computeEfficiencyForROC(hists["e_2016_5GeV"]);
    effs["e_2016_8GeV"] = computeEfficiencyForROC(hists["e_2016_8GeV"]);
    effs["e_2016_12GeV"] = computeEfficiencyForROC(hists["e_2016_12GeV"]);
    effs["m_2016_2GeV"] = computeEfficiencyForROC(hists["m_2016_2GeV"]);
    effs["m_2016_5GeV"] = computeEfficiencyForROC(hists["m_2016_5GeV"]);
    effs["m_2016_8GeV"] = computeEfficiencyForROC(hists["m_2016_8GeV"]);
    effs["m_2016_12GeV"] = computeEfficiencyForROC(hists["m_2016_12GeV"]);
    effs["e_2017_2GeV"] = computeEfficiencyForROC(hists["e_2017_2GeV"]);
    effs["e_2017_5GeV"] = computeEfficiencyForROC(hists["e_2017_5GeV"]);
    effs["e_2017_8GeV"] = computeEfficiencyForROC(hists["e_2017_8GeV"]);
    effs["e_2017_12GeV"] = computeEfficiencyForROC(hists["e_2017_12GeV"]);
    effs["m_2017_2GeV"] = computeEfficiencyForROC(hists["m_2017_2GeV"]);
    effs["m_2017_5GeV"] = computeEfficiencyForROC(hists["m_2017_5GeV"]);
    effs["m_2017_8GeV"] = computeEfficiencyForROC(hists["m_2017_8GeV"]);
    effs["m_2017_12GeV"] = computeEfficiencyForROC(hists["m_2017_12GeV"]);
    effs["e_2018_2GeV"] = computeEfficiencyForROC(hists["e_2018_2GeV"]);
    effs["e_2018_5GeV"] = computeEfficiencyForROC(hists["e_2018_5GeV"]);
    effs["e_2018_8GeV"] = computeEfficiencyForROC(hists["e_2018_8GeV"]);
    effs["e_2018_12GeV"] = computeEfficiencyForROC(hists["e_2018_12GeV"]);
    effs["m_2018_2GeV"] = computeEfficiencyForROC(hists["m_2018_2GeV"]);
    effs["m_2018_5GeV"] = computeEfficiencyForROC(hists["m_2018_5GeV"]);
    effs["m_2018_8GeV"] = computeEfficiencyForROC(hists["m_2018_8GeV"]);
    effs["m_2018_12GeV"] = computeEfficiencyForROC(hists["m_2018_12GeV"]);

    effs["e_2016_5Bkg"] = computeEfficiencyForROC(hists["e_2016_5Bkg"]);
    effs["e_2017_5Bkg"] = computeEfficiencyForROC(hists["e_2017_5Bkg"]);
    effs["e_2018_5Bkg"] = computeEfficiencyForROC(hists["e_2018_5Bkg"]);
    effs["m_2016_5Bkg"] = computeEfficiencyForROC(hists["m_2016_5Bkg"]);
    effs["m_2017_5Bkg"] = computeEfficiencyForROC(hists["m_2017_5Bkg"]);
    effs["m_2018_5Bkg"] = computeEfficiencyForROC(hists["m_2018_5Bkg"]);
    effs["e_2016_10Bkg"] = computeEfficiencyForROC(hists["e_2016_10Bkg"]);
    effs["e_2017_10Bkg"] = computeEfficiencyForROC(hists["e_2017_10Bkg"]);
    effs["e_2018_10Bkg"] = computeEfficiencyForROC(hists["e_2018_10Bkg"]);
    effs["m_2016_10Bkg"] = computeEfficiencyForROC(hists["m_2016_10Bkg"]);
    effs["m_2017_10Bkg"] = computeEfficiencyForROC(hists["m_2017_10Bkg"]);
    effs["m_2018_10Bkg"] = computeEfficiencyForROC(hists["m_2018_10Bkg"]);

    std::map<TString, double> PFNcut_effs;
    PFNcut_effs["e_2016_2GeV"] = effs["e_2016_2GeV"][hists["e_2016_2GeV"]->FindBin(PFNcuts["e_2016_2GeV"])-1];
    PFNcut_effs["e_2016_5GeV"] = effs["e_2016_5GeV"][hists["e_2016_5GeV"]->FindBin(PFNcuts["e_2016_5GeV"])-1];
    PFNcut_effs["e_2016_8GeV"] = effs["e_2016_8GeV"][hists["e_2016_8GeV"]->FindBin(PFNcuts["e_2016_8GeV"])-1];
    PFNcut_effs["e_2016_12GeV"] = effs["e_2016_12GeV"][hists["e_2016_12GeV"]->FindBin(PFNcuts["e_2016_12GeV"])-1];
    PFNcut_effs["m_2016_2GeV"] = effs["m_2016_2GeV"][hists["m_2016_2GeV"]->FindBin(PFNcuts["m_2016_2GeV"])-1];
    PFNcut_effs["m_2016_5GeV"] = effs["m_2016_5GeV"][hists["m_2016_5GeV"]->FindBin(PFNcuts["m_2016_5GeV"])-1];
    PFNcut_effs["m_2016_8GeV"] = effs["m_2016_8GeV"][hists["m_2016_8GeV"]->FindBin(PFNcuts["m_2016_8GeV"])-1];
    PFNcut_effs["m_2016_12GeV"] = effs["m_2016_12GeV"][hists["m_2016_12GeV"]->FindBin(PFNcuts["m_2016_12GeV"])-1];
    PFNcut_effs["e_2017_2GeV"] = effs["e_2017_2GeV"][hists["e_2017_2GeV"]->FindBin(PFNcuts["e_2017_2GeV"])-1];
    PFNcut_effs["e_2017_5GeV"] = effs["e_2017_5GeV"][hists["e_2017_5GeV"]->FindBin(PFNcuts["e_2017_5GeV"])-1];
    PFNcut_effs["e_2017_8GeV"] = effs["e_2017_8GeV"][hists["e_2017_8GeV"]->FindBin(PFNcuts["e_2017_8GeV"])-1];
    PFNcut_effs["e_2017_12GeV"] = effs["e_2017_12GeV"][hists["e_2017_12GeV"]->FindBin(PFNcuts["e_2017_12GeV"])-1];
    PFNcut_effs["m_2017_2GeV"] = effs["m_2017_2GeV"][hists["m_2017_2GeV"]->FindBin(PFNcuts["m_2017_2GeV"])-1];
    PFNcut_effs["m_2017_5GeV"] = effs["m_2017_5GeV"][hists["m_2017_5GeV"]->FindBin(PFNcuts["m_2017_5GeV"])-1];
    PFNcut_effs["m_2017_8GeV"] = effs["m_2017_8GeV"][hists["m_2017_8GeV"]->FindBin(PFNcuts["m_2017_8GeV"])-1];
    PFNcut_effs["m_2017_12GeV"] = effs["m_2017_12GeV"][hists["m_2017_12GeV"]->FindBin(PFNcuts["m_2017_12GeV"])-1];
    PFNcut_effs["e_2018_2GeV"] = effs["e_2018_2GeV"][hists["e_2018_2GeV"]->FindBin(PFNcuts["e_2018_2GeV"])-1];
    PFNcut_effs["e_2018_5GeV"] = effs["e_2018_5GeV"][hists["e_2018_5GeV"]->FindBin(PFNcuts["e_2018_5GeV"])-1];
    PFNcut_effs["e_2018_8GeV"] = effs["e_2018_8GeV"][hists["e_2018_8GeV"]->FindBin(PFNcuts["e_2018_8GeV"])-1];
    PFNcut_effs["e_2018_12GeV"] = effs["e_2018_12GeV"][hists["e_2018_12GeV"]->FindBin(PFNcuts["e_2018_12GeV"])-1];
    PFNcut_effs["m_2018_2GeV"] = effs["m_2018_2GeV"][hists["m_2018_2GeV"]->FindBin(PFNcuts["m_2018_2GeV"])-1];
    PFNcut_effs["m_2018_5GeV"] = effs["m_2018_5GeV"][hists["m_2018_5GeV"]->FindBin(PFNcuts["m_2018_5GeV"])-1];
    PFNcut_effs["m_2018_8GeV"] = effs["m_2018_8GeV"][hists["m_2018_8GeV"]->FindBin(PFNcuts["m_2018_8GeV"])-1];
    PFNcut_effs["m_2018_12GeV"] = effs["m_2018_12GeV"][hists["m_2018_12GeV"]->FindBin(PFNcuts["m_2018_12GeV"])-1];

    PFNcut_effs["e_2016_5Bkg"] = effs["e_2016_5Bkg"][hists["e_2016_5Bkg"]->FindBin(PFNcuts["e_2016_5Bkg"])-1];
    PFNcut_effs["e_2017_5Bkg"] = effs["e_2017_5Bkg"][hists["e_2017_5Bkg"]->FindBin(PFNcuts["e_2017_5Bkg"])-1];
    PFNcut_effs["e_2018_5Bkg"] = effs["e_2018_5Bkg"][hists["e_2018_5Bkg"]->FindBin(PFNcuts["e_2018_5Bkg"])-1];
    PFNcut_effs["m_2016_5Bkg"] = effs["m_2016_5Bkg"][hists["m_2016_5Bkg"]->FindBin(PFNcuts["m_2016_5Bkg"])-1];
    PFNcut_effs["m_2017_5Bkg"] = effs["m_2017_5Bkg"][hists["m_2017_5Bkg"]->FindBin(PFNcuts["m_2017_5Bkg"])-1];
    PFNcut_effs["m_2018_5Bkg"] = effs["m_2018_5Bkg"][hists["m_2018_5Bkg"]->FindBin(PFNcuts["m_2018_5Bkg"])-1];
    PFNcut_effs["e_2016_10Bkg"] = effs["e_2016_10Bkg"][hists["e_2016_10Bkg"]->FindBin(PFNcuts["e_2016_10Bkg"])-1];
    PFNcut_effs["e_2017_10Bkg"] = effs["e_2017_10Bkg"][hists["e_2017_10Bkg"]->FindBin(PFNcuts["e_2017_10Bkg"])-1];
    PFNcut_effs["e_2018_10Bkg"] = effs["e_2018_10Bkg"][hists["e_2018_10Bkg"]->FindBin(PFNcuts["e_2018_10Bkg"])-1];
    PFNcut_effs["m_2016_10Bkg"] = effs["m_2016_10Bkg"][hists["m_2016_10Bkg"]->FindBin(PFNcuts["m_2016_10Bkg"])-1];
    PFNcut_effs["m_2017_10Bkg"] = effs["m_2017_10Bkg"][hists["m_2017_10Bkg"]->FindBin(PFNcuts["m_2017_10Bkg"])-1];
    PFNcut_effs["m_2018_10Bkg"] = effs["m_2018_10Bkg"][hists["m_2018_10Bkg"]->FindBin(PFNcuts["m_2018_10Bkg"])-1];


    std::ostringstream e_2016_5_stream, e_2016_10_stream, e_2017_5_stream, e_2017_10_stream, e_2018_5_stream, e_2018_10_stream, m_2016_5_stream, m_2016_10_stream, m_2017_5_stream, m_2017_10_stream, m_2018_5_stream, m_2018_10_stream;
    e_2016_5_stream << std::setprecision(2) << 100.*PFNcut_effs["e_2016_2GeV"] << "\\% & " << 100.*PFNcut_effs["e_2016_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs["e_2016_5Bkg"] << "\\%";
    e_2016_10_stream << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs["e_2016_8GeV"] << "\\% & " << 100.*PFNcut_effs["e_2016_12GeV"] << "\\% & " << 100.*PFNcut_effs["e_2016_10Bkg"] << "\\%";
    m_2016_5_stream << std::setprecision(2) << 100.*PFNcut_effs["m_2016_2GeV"] << "\\% & " << 100.*PFNcut_effs["m_2016_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs["m_2016_5Bkg"] << "\\%";
    m_2016_10_stream << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs["m_2016_8GeV"] << "\\% & " << 100.*PFNcut_effs["m_2016_12GeV"] << "\\% & " << 100.*PFNcut_effs["m_2016_10Bkg"] << "\\%";
    e_2017_5_stream << std::setprecision(2) << 100.*PFNcut_effs["e_2017_2GeV"] << "\\% & " << 100.*PFNcut_effs["e_2017_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs["e_2017_5Bkg"] << "\\%";
    e_2017_10_stream << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs["e_2017_8GeV"] << "\\% & " << 100.*PFNcut_effs["e_2017_12GeV"] << "\\% & " << 100.*PFNcut_effs["e_2017_10Bkg"] << "\\%";
    m_2017_5_stream << std::setprecision(2) << 100.*PFNcut_effs["m_2017_2GeV"] << "\\% & " << 100.*PFNcut_effs["m_2017_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs["m_2017_5Bkg"] << "\\%";
    m_2017_10_stream << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs["m_2017_8GeV"] << "\\% & " << 100.*PFNcut_effs["m_2017_12GeV"] << "\\% & " << 100.*PFNcut_effs["m_2017_10Bkg"] << "\\%";
    e_2018_5_stream << std::setprecision(2) << 100.*PFNcut_effs["e_2018_2GeV"] << "\\% & " << 100.*PFNcut_effs["e_2018_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs["e_2018_5Bkg"] << "\\%";
    e_2018_10_stream << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs["e_2018_8GeV"] << "\\% & " << 100.*PFNcut_effs["e_2018_12GeV"] << "\\% & " << 100.*PFNcut_effs["e_2018_10Bkg"] << "\\%";
    m_2018_5_stream << std::setprecision(2) << 100.*PFNcut_effs["m_2018_2GeV"] << "\\% & " << 100.*PFNcut_effs["m_2018_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs["m_2018_5Bkg"] << "\\%";
    m_2018_10_stream << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs["m_2018_8GeV"] << "\\% & " << 100.*PFNcut_effs["m_2018_12GeV"] << "\\% & " << 100.*PFNcut_effs["m_2018_10Bkg"] << "\\%";

    std::cout << "\\begin{table}" << std::endl;
    std::cout << "    \\centering" << std::endl;
    std::cout << "    \\caption{PFN cuts for defining the normal and inverted region.}" << std::endl;
    std::cout << "    \\label{tab:PFNcuts}" << std::endl;
    std::cout << "    \\begin{tabular}{|l|l|l|l|l|l|l|l|l|}" << std::endl;
    std::cout << "        \\hline" << std::endl;
    std::cout << "        \\ltwo flavor & year & \\mhnl & Cut & Eff.(2GeV) & Eff.(5GeV) & Eff.(8GeV) & Eff.(12GeV) & Eff.(Bkg)\\\\" << std::endl;
    std::cout << "        \\hline" << std::endl;
    std::cout << "        \\hline" << std::endl;
    std::cout << "        \\multirow{6}{*}{\\Pe} & \\multirow{2}{*}{2016} & low mass & 0.98 & " + e_2016_5_stream.str() + "\\\\" << std::endl;
    std::cout << "        & & high mass & 0.99 & " + e_2016_10_stream.str() + "\\\\\\cline{2-4}" << std::endl;
    std::cout << "        & \\multirow{2}{*}{2017} & low mass & 0.97 & " + e_2017_5_stream.str() + "\\\\" << std::endl;
    std::cout << "        & & high mass & 0.96 & " + e_2017_10_stream.str() + "\\\\\\cline{2-4}" << std::endl;
    std::cout << "        & \\multirow{2}{*}{2018} & low mass & 0.98 & " + e_2018_5_stream.str() + "\\\\" << std::endl;
    std::cout << "        & & high mass & 0.97 & " + e_2018_10_stream.str() + "\\\\" << std::endl;
    std::cout << "        \\hline" << std::endl;
    std::cout << "        \\multirow{6}{*}{\\PGm} & \\multirow{2}{*}{2016} & low mass & 0.999 & " + m_2016_5_stream.str() + "\\\\" << std::endl;
    std::cout << "        & & high mass & 0.998 & " + m_2016_10_stream.str() + "\\\\\\cline{2-4}" << std::endl;
    std::cout << "        & \\multirow{2}{*}{2017} & low mass & 0.996 & " + m_2017_5_stream.str() + "\\\\" << std::endl;
    std::cout << "        & & high mass & 0.998 & " + m_2017_10_stream.str() + "\\\\\\cline{2-4}" << std::endl;
    std::cout << "        & \\multirow{2}{*}{2018} & low mass & 0.997 & " + m_2018_5_stream.str() + "\\\\" << std::endl;
    std::cout << "        & & high mass & 0.998 & " + m_2018_10_stream.str() + "\\\\" << std::endl;
    std::cout << "        \\hline" << std::endl;
    std::cout << "    \\end{tabular}" << std::endl;
    std::cout << "\\end{table}" << std::endl;

    

    // Make the ROC curves
    setTDRStyle();
    gROOT->ForceStyle();

    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    // Make the pad that will contain the plot
    TPad* pad  = new TPad("pad", "", 0., 0., 1., 1.);
    pad->Draw();
    pad->cd();

    //TLegend legend = get_legend(0.18, 0.61, 0.65, 0.93, 1);
    TLegend legend = get_legend(0.57, 0.15, 1, 0.075*6, 1);


    std::vector<std::vector<int>> rgb = {{46, 114, 204}, {239, 32, 29}, {29, 182, 0}, {86, 14, 118}, {232, 164, 0}, {86, 22, 67}, {247, 135, 100}, {47, 41, 35}};
    std::vector<int> colors;
    for(unsigned i = 0; i < rgb.size(); i++){
        colors.push_back(TColor::GetColor(rgb[i][0], rgb[i][1], rgb[i][2]));
    }


    for(const TString& year : {"2016", "2017", "2018"}){
        for(const TString& fl : {"e", "m"}){
            // Get margins and make the CMS and lumi basic latex to print on top of the figure
            CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad, year == "2016", year == "2017", year == "2018", false);
            CMSandLumi->add_flavor("_"+fl+fl);
            legend.Clear();
            legend.SetHeader("HNL Mass: AUC");

            TMultiGraph* multigraph = new TMultiGraph();
            multigraph->SetTitle((TString)";Bkg Eff.;Signal Eff.");
            TGraph* roc_2GeV = get_roc(effs[fl+"_"+year+"_2GeV"], effs[fl+"_"+year+"_5Bkg"]);
            roc_2GeV->SetLineColor(colors[0]);
            multigraph->Add(roc_2GeV);
            std::ostringstream auc_2GeV;
            auc_2GeV << std::setprecision(4) << computeAUC(roc_2GeV);
            TString leg_2GeV = "M-2GeV: " + auc_2GeV.str();
            legend.AddEntry(roc_2GeV, leg_2GeV, "l");
            
            TGraph* roc_5GeV = get_roc(effs[fl+"_"+year+"_5GeV"], effs[fl+"_"+year+"_5Bkg"]);
            roc_5GeV->SetLineColor(colors[1]);
            multigraph->Add(roc_5GeV);
            std::ostringstream auc_5GeV;
            auc_5GeV << std::setprecision(4) << computeAUC(roc_5GeV);
            TString leg_5GeV = "M-5GeV: " + auc_5GeV.str();
            legend.AddEntry(roc_5GeV, leg_5GeV, "l");
            
            TGraph* roc_8GeV = get_roc(effs[fl+"_"+year+"_8GeV"], effs[fl+"_"+year+"_10Bkg"]);
            roc_8GeV->SetLineColor(colors[2]);
            multigraph->Add(roc_8GeV);
            std::ostringstream auc_8GeV;
            auc_8GeV << std::setprecision(4) << computeAUC(roc_8GeV);
            TString leg_8GeV = "M-8GeV: " + auc_8GeV.str();
            legend.AddEntry(roc_8GeV, leg_8GeV, "l");
            
            TGraph* roc_12GeV = get_roc(effs[fl+"_"+year+"_12GeV"], effs[fl+"_"+year+"_10Bkg"]);
            roc_12GeV->SetLineColor(colors[3]);
            multigraph->Add(roc_12GeV);
            std::ostringstream auc_12GeV;
            auc_12GeV << std::setprecision(4) << computeAUC(roc_12GeV);
            TString leg_12GeV = "M-12GeV: " + auc_12GeV.str();
            legend.AddEntry(roc_12GeV, leg_12GeV, "l");

            double sig_eff[4], bkg_eff[4];
            sig_eff[0] = PFNcut_effs[fl+"_"+year+"_2GeV"];
            sig_eff[1] = PFNcut_effs[fl+"_"+year+"_5GeV"];
            sig_eff[2] = PFNcut_effs[fl+"_"+year+"_8GeV"];
            sig_eff[3] = PFNcut_effs[fl+"_"+year+"_12GeV"];
            bkg_eff[0] = PFNcut_effs[fl+"_"+year+"_5Bkg"];
            bkg_eff[1] = PFNcut_effs[fl+"_"+year+"_5Bkg"];
            bkg_eff[2] = PFNcut_effs[fl+"_"+year+"_10Bkg"];
            bkg_eff[3] = PFNcut_effs[fl+"_"+year+"_10Bkg"];
            TGraph* workingpoints = new TGraph(4, bkg_eff, sig_eff);
            workingpoints->SetMarkerStyle(29);
            workingpoints->SetMarkerSize(3);
            legend.AddEntry(workingpoints, "Working Points", "p");
            
            pad->SetLogx(1);
            multigraph->Draw("AL");
            workingpoints->Draw("P same");


            multigraph->GetXaxis()->SetLimits(5e-5, 0.2);
            multigraph->SetMinimum(0.4);
            multigraph->SetMaximum(1.02);

            legend.Draw("same");
            CMSandLumi->Draw();

            pad->Modified();
            c->Print("/user/bvermass/public_html/2l2q_analysis/plots/roccurves/ROC_"+fl+"_"+year+".png");
        }
    }
    std::map<TString, double> PFNcut_effs_0p9;
    PFNcut_effs_0p9["e_2016_2GeV"] = effs["e_2016_2GeV"][hists["e_2016_2GeV"]->FindBin(PFNcuts_0p9["e_2016_2GeV"])-1]    - effs["e_2016_2GeV"][hists["e_2016_2GeV"]->FindBin(PFNcuts["e_2016_2GeV"])-1];
    PFNcut_effs_0p9["e_2016_5GeV"] = effs["e_2016_5GeV"][hists["e_2016_5GeV"]->FindBin(PFNcuts_0p9["e_2016_5GeV"])-1]    - effs["e_2016_5GeV"][hists["e_2016_5GeV"]->FindBin(PFNcuts["e_2016_5GeV"])-1];
    PFNcut_effs_0p9["e_2016_8GeV"] = effs["e_2016_8GeV"][hists["e_2016_8GeV"]->FindBin(PFNcuts_0p9["e_2016_8GeV"])-1]    - effs["e_2016_8GeV"][hists["e_2016_8GeV"]->FindBin(PFNcuts["e_2016_8GeV"])-1];
    PFNcut_effs_0p9["e_2016_12GeV"] = effs["e_2016_12GeV"][hists["e_2016_12GeV"]->FindBin(PFNcuts_0p9["e_2016_12GeV"])-1]-  effs["e_2016_12GeV"][hists["e_2016_12GeV"]->FindBin(PFNcuts["e_2016_12GeV"])-1];
    PFNcut_effs_0p9["m_2016_2GeV"] = effs["m_2016_2GeV"][hists["m_2016_2GeV"]->FindBin(PFNcuts_0p9["m_2016_2GeV"])-1]    - effs["m_2016_2GeV"][hists["m_2016_2GeV"]->FindBin(PFNcuts["m_2016_2GeV"])-1];
    PFNcut_effs_0p9["m_2016_5GeV"] = effs["m_2016_5GeV"][hists["m_2016_5GeV"]->FindBin(PFNcuts_0p9["m_2016_5GeV"])-1]    - effs["m_2016_5GeV"][hists["m_2016_5GeV"]->FindBin(PFNcuts["m_2016_5GeV"])-1];
    PFNcut_effs_0p9["m_2016_8GeV"] = effs["m_2016_8GeV"][hists["m_2016_8GeV"]->FindBin(PFNcuts_0p9["m_2016_8GeV"])-1]    - effs["m_2016_8GeV"][hists["m_2016_8GeV"]->FindBin(PFNcuts["m_2016_8GeV"])-1];
    PFNcut_effs_0p9["m_2016_12GeV"] = effs["m_2016_12GeV"][hists["m_2016_12GeV"]->FindBin(PFNcuts_0p9["m_2016_12GeV"])-1]-  effs["m_2016_12GeV"][hists["m_2016_12GeV"]->FindBin(PFNcuts["m_2016_12GeV"])-1];
    PFNcut_effs_0p9["e_2017_2GeV"] = effs["e_2017_2GeV"][hists["e_2017_2GeV"]->FindBin(PFNcuts_0p9["e_2017_2GeV"])-1]    - effs["e_2017_2GeV"][hists["e_2017_2GeV"]->FindBin(PFNcuts["e_2017_2GeV"])-1];
    PFNcut_effs_0p9["e_2017_5GeV"] = effs["e_2017_5GeV"][hists["e_2017_5GeV"]->FindBin(PFNcuts_0p9["e_2017_5GeV"])-1]    - effs["e_2017_5GeV"][hists["e_2017_5GeV"]->FindBin(PFNcuts["e_2017_5GeV"])-1];
    PFNcut_effs_0p9["e_2017_8GeV"] = effs["e_2017_8GeV"][hists["e_2017_8GeV"]->FindBin(PFNcuts_0p9["e_2017_8GeV"])-1]    - effs["e_2017_8GeV"][hists["e_2017_8GeV"]->FindBin(PFNcuts["e_2017_8GeV"])-1];
    PFNcut_effs_0p9["e_2017_12GeV"] = effs["e_2017_12GeV"][hists["e_2017_12GeV"]->FindBin(PFNcuts_0p9["e_2017_12GeV"])-1]-  effs["e_2017_12GeV"][hists["e_2017_12GeV"]->FindBin(PFNcuts["e_2017_12GeV"])-1];
    PFNcut_effs_0p9["m_2017_2GeV"] = effs["m_2017_2GeV"][hists["m_2017_2GeV"]->FindBin(PFNcuts_0p9["m_2017_2GeV"])-1]    - effs["m_2017_2GeV"][hists["m_2017_2GeV"]->FindBin(PFNcuts["m_2017_2GeV"])-1];
    PFNcut_effs_0p9["m_2017_5GeV"] = effs["m_2017_5GeV"][hists["m_2017_5GeV"]->FindBin(PFNcuts_0p9["m_2017_5GeV"])-1]    - effs["m_2017_5GeV"][hists["m_2017_5GeV"]->FindBin(PFNcuts["m_2017_5GeV"])-1];
    PFNcut_effs_0p9["m_2017_8GeV"] = effs["m_2017_8GeV"][hists["m_2017_8GeV"]->FindBin(PFNcuts_0p9["m_2017_8GeV"])-1]    - effs["m_2017_8GeV"][hists["m_2017_8GeV"]->FindBin(PFNcuts["m_2017_8GeV"])-1];
    PFNcut_effs_0p9["m_2017_12GeV"] = effs["m_2017_12GeV"][hists["m_2017_12GeV"]->FindBin(PFNcuts_0p9["m_2017_12GeV"])-1]-  effs["m_2017_12GeV"][hists["m_2017_12GeV"]->FindBin(PFNcuts["m_2017_12GeV"])-1];
    PFNcut_effs_0p9["e_2018_2GeV"] = effs["e_2018_2GeV"][hists["e_2018_2GeV"]->FindBin(PFNcuts_0p9["e_2018_2GeV"])-1]    - effs["e_2018_2GeV"][hists["e_2018_2GeV"]->FindBin(PFNcuts["e_2018_2GeV"])-1];
    PFNcut_effs_0p9["e_2018_5GeV"] = effs["e_2018_5GeV"][hists["e_2018_5GeV"]->FindBin(PFNcuts_0p9["e_2018_5GeV"])-1]    - effs["e_2018_5GeV"][hists["e_2018_5GeV"]->FindBin(PFNcuts["e_2018_5GeV"])-1];
    PFNcut_effs_0p9["e_2018_8GeV"] = effs["e_2018_8GeV"][hists["e_2018_8GeV"]->FindBin(PFNcuts_0p9["e_2018_8GeV"])-1]    - effs["e_2018_8GeV"][hists["e_2018_8GeV"]->FindBin(PFNcuts["e_2018_8GeV"])-1];
    PFNcut_effs_0p9["e_2018_12GeV"] = effs["e_2018_12GeV"][hists["e_2018_12GeV"]->FindBin(PFNcuts_0p9["e_2018_12GeV"])-1]-  effs["e_2018_12GeV"][hists["e_2018_12GeV"]->FindBin(PFNcuts["e_2018_12GeV"])-1];
    PFNcut_effs_0p9["m_2018_2GeV"] = effs["m_2018_2GeV"][hists["m_2018_2GeV"]->FindBin(PFNcuts_0p9["m_2018_2GeV"])-1]    - effs["m_2018_2GeV"][hists["m_2018_2GeV"]->FindBin(PFNcuts["m_2018_2GeV"])-1];
    PFNcut_effs_0p9["m_2018_5GeV"] = effs["m_2018_5GeV"][hists["m_2018_5GeV"]->FindBin(PFNcuts_0p9["m_2018_5GeV"])-1]    - effs["m_2018_5GeV"][hists["m_2018_5GeV"]->FindBin(PFNcuts["m_2018_5GeV"])-1];
    PFNcut_effs_0p9["m_2018_8GeV"] = effs["m_2018_8GeV"][hists["m_2018_8GeV"]->FindBin(PFNcuts_0p9["m_2018_8GeV"])-1]    - effs["m_2018_8GeV"][hists["m_2018_8GeV"]->FindBin(PFNcuts["m_2018_8GeV"])-1];
    PFNcut_effs_0p9["m_2018_12GeV"] = effs["m_2018_12GeV"][hists["m_2018_12GeV"]->FindBin(PFNcuts_0p9["m_2018_12GeV"])-1]-  effs["m_2018_12GeV"][hists["m_2018_12GeV"]->FindBin(PFNcuts["m_2018_12GeV"])-1];

    PFNcut_effs_0p9["e_2016_5Bkg"] = effs["e_2016_5Bkg"][hists["e_2016_5Bkg"]->FindBin(PFNcuts_0p9["e_2016_5Bkg"])-1]    - effs["e_2016_5Bkg"][hists["e_2016_5Bkg"]->FindBin(PFNcuts["e_2016_5Bkg"])-1];
    PFNcut_effs_0p9["e_2017_5Bkg"] = effs["e_2017_5Bkg"][hists["e_2017_5Bkg"]->FindBin(PFNcuts_0p9["e_2017_5Bkg"])-1]    - effs["e_2017_5Bkg"][hists["e_2017_5Bkg"]->FindBin(PFNcuts["e_2017_5Bkg"])-1];
    PFNcut_effs_0p9["e_2018_5Bkg"] = effs["e_2018_5Bkg"][hists["e_2018_5Bkg"]->FindBin(PFNcuts_0p9["e_2018_5Bkg"])-1]    - effs["e_2018_5Bkg"][hists["e_2018_5Bkg"]->FindBin(PFNcuts["e_2018_5Bkg"])-1];
    PFNcut_effs_0p9["m_2016_5Bkg"] = effs["m_2016_5Bkg"][hists["m_2016_5Bkg"]->FindBin(PFNcuts_0p9["m_2016_5Bkg"])-1]    - effs["m_2016_5Bkg"][hists["m_2016_5Bkg"]->FindBin(PFNcuts["m_2016_5Bkg"])-1];
    PFNcut_effs_0p9["m_2017_5Bkg"] = effs["m_2017_5Bkg"][hists["m_2017_5Bkg"]->FindBin(PFNcuts_0p9["m_2017_5Bkg"])-1]    - effs["m_2017_5Bkg"][hists["m_2017_5Bkg"]->FindBin(PFNcuts["m_2017_5Bkg"])-1];
    PFNcut_effs_0p9["m_2018_5Bkg"] = effs["m_2018_5Bkg"][hists["m_2018_5Bkg"]->FindBin(PFNcuts_0p9["m_2018_5Bkg"])-1]    - effs["m_2018_5Bkg"][hists["m_2018_5Bkg"]->FindBin(PFNcuts["m_2018_5Bkg"])-1];
    PFNcut_effs_0p9["e_2016_10Bkg"] = effs["e_2016_10Bkg"][hists["e_2016_10Bkg"]->FindBin(PFNcuts_0p9["e_2016_10Bkg"])-1]-  effs["e_2016_10Bkg"][hists["e_2016_10Bkg"]->FindBin(PFNcuts["e_2016_10Bkg"])-1];
    PFNcut_effs_0p9["e_2017_10Bkg"] = effs["e_2017_10Bkg"][hists["e_2017_10Bkg"]->FindBin(PFNcuts_0p9["e_2017_10Bkg"])-1]-  effs["e_2017_10Bkg"][hists["e_2017_10Bkg"]->FindBin(PFNcuts["e_2017_10Bkg"])-1];
    PFNcut_effs_0p9["e_2018_10Bkg"] = effs["e_2018_10Bkg"][hists["e_2018_10Bkg"]->FindBin(PFNcuts_0p9["e_2018_10Bkg"])-1]-  effs["e_2018_10Bkg"][hists["e_2018_10Bkg"]->FindBin(PFNcuts["e_2018_10Bkg"])-1];
    PFNcut_effs_0p9["m_2016_10Bkg"] = effs["m_2016_10Bkg"][hists["m_2016_10Bkg"]->FindBin(PFNcuts_0p9["m_2016_10Bkg"])-1]-  effs["m_2016_10Bkg"][hists["m_2016_10Bkg"]->FindBin(PFNcuts["m_2016_10Bkg"])-1];
    PFNcut_effs_0p9["m_2017_10Bkg"] = effs["m_2017_10Bkg"][hists["m_2017_10Bkg"]->FindBin(PFNcuts_0p9["m_2017_10Bkg"])-1]-  effs["m_2017_10Bkg"][hists["m_2017_10Bkg"]->FindBin(PFNcuts["m_2017_10Bkg"])-1];
    PFNcut_effs_0p9["m_2018_10Bkg"] = effs["m_2018_10Bkg"][hists["m_2018_10Bkg"]->FindBin(PFNcuts_0p9["m_2018_10Bkg"])-1]-  effs["m_2018_10Bkg"][hists["m_2018_10Bkg"]->FindBin(PFNcuts["m_2018_10Bkg"])-1];
    
    std::ostringstream e_2016_5_stream_0p9, e_2016_10_stream_0p9, e_2017_5_stream_0p9, e_2017_10_stream_0p9, e_2018_5_stream_0p9, e_2018_10_stream_0p9, m_2016_5_stream_0p9, m_2016_10_stream_0p9, m_2017_5_stream_0p9, m_2017_10_stream_0p9, m_2018_5_stream_0p9, m_2018_10_stream_0p9;
    e_2016_5_stream_0p9 << std::setprecision(2) << 100.*PFNcut_effs_0p9["e_2016_2GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2016_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs_0p9["e_2016_5Bkg"] << "\\%";
    e_2016_10_stream_0p9 << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs_0p9["e_2016_8GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2016_12GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2016_10Bkg"] << "\\%";
    m_2016_5_stream_0p9 << std::setprecision(2) << 100.*PFNcut_effs_0p9["m_2016_2GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2016_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs_0p9["m_2016_5Bkg"] << "\\%";
    m_2016_10_stream_0p9 << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs_0p9["m_2016_8GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2016_12GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2016_10Bkg"] << "\\%";
    e_2017_5_stream_0p9 << std::setprecision(2) << 100.*PFNcut_effs_0p9["e_2017_2GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2017_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs_0p9["e_2017_5Bkg"] << "\\%";
    e_2017_10_stream_0p9 << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs_0p9["e_2017_8GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2017_12GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2017_10Bkg"] << "\\%";
    m_2017_5_stream_0p9 << std::setprecision(2) << 100.*PFNcut_effs_0p9["m_2017_2GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2017_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs_0p9["m_2017_5Bkg"] << "\\%";
    m_2017_10_stream_0p9 << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs_0p9["m_2017_8GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2017_12GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2017_10Bkg"] << "\\%";
    e_2018_5_stream_0p9 << std::setprecision(2) << 100.*PFNcut_effs_0p9["e_2018_2GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2018_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs_0p9["e_2018_5Bkg"] << "\\%";
    e_2018_10_stream_0p9 << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs_0p9["e_2018_8GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2018_12GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2018_10Bkg"] << "\\%";
    m_2018_5_stream_0p9 << std::setprecision(2) << 100.*PFNcut_effs_0p9["m_2018_2GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2018_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs_0p9["m_2018_5Bkg"] << "\\%";
    m_2018_10_stream_0p9 << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs_0p9["m_2018_8GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2018_12GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2018_10Bkg"] << "\\%";

    std::cout << "\\begin{table}" << std::endl;
    std::cout << "    \\centering" << std::endl;
    std::cout << "    \\caption{PFN cuts for defining the normal and inverted region.}" << std::endl;
    std::cout << "    \\label{tab:PFNcuts}" << std::endl;
    std::cout << "    \\begin{tabular}{|l|l|l|l|l|l|l|l|l|}" << std::endl;
    std::cout << "        \\hline" << std::endl;
    std::cout << "        \\ltwo flavor & year & \\mhnl & Cut & Eff.(2GeV) & Eff.(5GeV) & Eff.(8GeV) & Eff.(12GeV) & Eff.(Bkg)\\\\" << std::endl;
    std::cout << "        \\hline" << std::endl;
    std::cout << "        \\hline" << std::endl;
    std::cout << "        \\multirow{6}{*}{\\Pe} & \\multirow{2}{*}{2016} & low mass & 0.98 & " + e_2016_5_stream_0p9.str() + "\\\\" << std::endl;
    std::cout << "        & & high mass & 0.99 & " + e_2016_10_stream_0p9.str() + "\\\\\\cline{2-4}" << std::endl;
    std::cout << "        & \\multirow{2}{*}{2017} & low mass & 0.97 & " + e_2017_5_stream_0p9.str() + "\\\\" << std::endl;
    std::cout << "        & & high mass & 0.96 & " + e_2017_10_stream_0p9.str() + "\\\\\\cline{2-4}" << std::endl;
    std::cout << "        & \\multirow{2}{*}{2018} & low mass & 0.98 & " + e_2018_5_stream_0p9.str() + "\\\\" << std::endl;
    std::cout << "        & & high mass & 0.97 & " + e_2018_10_stream_0p9.str() + "\\\\" << std::endl;
    std::cout << "        \\hline" << std::endl;
    std::cout << "        \\multirow{6}{*}{\\PGm} & \\multirow{2}{*}{2016} & low mass & 0.999 & " + m_2016_5_stream_0p9.str() + "\\\\" << std::endl;
    std::cout << "        & & high mass & 0.998 & " + m_2016_10_stream_0p9.str() + "\\\\\\cline{2-4}" << std::endl;
    std::cout << "        & \\multirow{2}{*}{2017} & low mass & 0.996 & " + m_2017_5_stream_0p9.str() + "\\\\" << std::endl;
    std::cout << "        & & high mass & 0.998 & " + m_2017_10_stream_0p9.str() + "\\\\\\cline{2-4}" << std::endl;
    std::cout << "        & \\multirow{2}{*}{2018} & low mass & 0.997 & " + m_2018_5_stream_0p9.str() + "\\\\" << std::endl;
    std::cout << "        & & high mass & 0.998 & " + m_2018_10_stream_0p9.str() + "\\\\" << std::endl;
    std::cout << "        \\hline" << std::endl;
    std::cout << "    \\end{tabular}" << std::endl;
    std::cout << "\\end{table}" << std::endl;
}
#endif

#endif
