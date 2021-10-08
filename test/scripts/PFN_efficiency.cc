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
TString filename_Run2_Bkg = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_Background_MiniAODRun2.root";

TString filename_2016_Data = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_SingleLepton_Run2016.root";
TString filename_2017_Data = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_SingleLepton_Run2017.root";
TString filename_2018_Data = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_SingleLepton_Run2018.root";
TString filename_Run2_Data = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_SingleLepton_Run2.root";


void print_Kshort_efficiency(TString year)
{
    TString dir = "/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/Kshort/full_analyzer/";
    TString filename_data_Kshort, filename_mc_Kshort;
    if(year == "Run2"){
        filename_data_Kshort = dir + "hists_full_analyzer_DoubleMuon_Run2.root";
        filename_mc_Kshort = dir + "hists_full_analyzer_DYJetsToLL_M-50_MiniAODRun2.root";
    }else if(year == "2016"){
        filename_data_Kshort = dir + "hists_full_analyzer_DoubleMuon_Run2016.root";
        filename_mc_Kshort = dir + "hists_full_analyzer_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_MiniAOD2016.root";
    }else if(year == "2017"){
        filename_data_Kshort = dir + "hists_full_analyzer_DoubleMuon_Run2017.root";
        filename_mc_Kshort = dir + "hists_full_analyzer_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2017.root";
    }else if(year == "2018"){
        filename_data_Kshort = dir + "hists_full_analyzer_DoubleMuon_Run2018.root";
        filename_mc_Kshort = dir + "hists_full_analyzer_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2018.root";
    }else if(year == "2016HIP"){
        filename_data_Kshort = dir + "hists_full_analyzer_DoubleMuon_Run2016HIP.root";
        filename_mc_Kshort = dir + "hists_full_analyzer_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_MiniAOD2016.root";
    }else if(year == "2016noHIP"){
        filename_data_Kshort = dir + "hists_full_analyzer_DoubleMuon_Run2016noHIP.root";
        filename_mc_Kshort = dir + "hists_full_analyzer_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_MiniAOD2016.root";
    }


    TFile* file_data_Kshort = TFile::Open(filename_data_Kshort);
    TFile* file_mc_Kshort = TFile::Open(filename_mc_Kshort);

    TH1F* hist_data_Kshort_mu_LowMass = (TH1F*)file_data_Kshort->Get("_mm_Kshort_2GeV_PFNmu_LowMass");
    TH1F* hist_data_Kshort_mu_HighMass = (TH1F*)file_data_Kshort->Get("_mm_Kshort_2GeV_PFNmu_HighMass");
    TH1F* hist_data_Kshort_e_LowMass = (TH1F*)file_data_Kshort->Get("_mm_Kshort_2GeV_PFNe_LowMass");
    TH1F* hist_data_Kshort_e_HighMass = (TH1F*)file_data_Kshort->Get("_mm_Kshort_2GeV_PFNe_HighMass");
    TH1F* hist_mc_Kshort_mu_LowMass = (TH1F*)file_mc_Kshort->Get("_mm_Kshort_2GeV_PFNmu_LowMass");
    TH1F* hist_mc_Kshort_mu_HighMass = (TH1F*)file_mc_Kshort->Get("_mm_Kshort_2GeV_PFNmu_HighMass");
    TH1F* hist_mc_Kshort_e_LowMass = (TH1F*)file_mc_Kshort->Get("_mm_Kshort_2GeV_PFNe_LowMass");
    TH1F* hist_mc_Kshort_e_HighMass = (TH1F*)file_mc_Kshort->Get("_mm_Kshort_2GeV_PFNe_HighMass");

    //scale the MC histograms to the data histograms
    hist_mc_Kshort_mu_LowMass->Scale(hist_data_Kshort_mu_LowMass->Integral()/hist_mc_Kshort_mu_LowMass->Integral());
    hist_mc_Kshort_mu_HighMass->Scale(hist_data_Kshort_mu_HighMass->Integral()/hist_mc_Kshort_mu_HighMass->Integral());
    hist_mc_Kshort_e_LowMass->Scale(hist_data_Kshort_e_LowMass->Integral()/hist_mc_Kshort_e_LowMass->Integral());
    hist_mc_Kshort_e_HighMass->Scale(hist_data_Kshort_e_HighMass->Integral()/hist_mc_Kshort_e_HighMass->Integral());

    std::vector<double> eff_data_Kshort_mu_LowMass = computeEfficiencyForROC(hist_data_Kshort_mu_LowMass);
    std::vector<double> eff_data_Kshort_mu_HighMass = computeEfficiencyForROC(hist_data_Kshort_mu_HighMass);
    std::vector<double> eff_data_Kshort_e_LowMass = computeEfficiencyForROC(hist_data_Kshort_e_LowMass);
    std::vector<double> eff_data_Kshort_e_HighMass = computeEfficiencyForROC(hist_data_Kshort_e_HighMass);
    std::vector<double> eff_mc_Kshort_mu_LowMass = computeEfficiencyForROC(hist_mc_Kshort_mu_LowMass);
    std::vector<double> eff_mc_Kshort_mu_HighMass = computeEfficiencyForROC(hist_mc_Kshort_mu_HighMass);
    std::vector<double> eff_mc_Kshort_e_LowMass = computeEfficiencyForROC(hist_mc_Kshort_e_LowMass);
    std::vector<double> eff_mc_Kshort_e_HighMass = computeEfficiencyForROC(hist_mc_Kshort_e_HighMass);

    double eff_0p9_data_Kshort_mu_LowMass = eff_data_Kshort_mu_LowMass[hist_data_Kshort_mu_LowMass->FindBin(0.9)-1];
    double eff_0p9_data_Kshort_mu_HighMass = eff_data_Kshort_mu_HighMass[hist_data_Kshort_mu_HighMass->FindBin(0.9)-1];
    double eff_0p9_data_Kshort_e_LowMass = eff_data_Kshort_e_LowMass[hist_data_Kshort_e_LowMass->FindBin(0.9)-1];
    double eff_0p9_data_Kshort_e_HighMass = eff_data_Kshort_e_HighMass[hist_data_Kshort_e_HighMass->FindBin(0.9)-1];
    double eff_0p9_mc_Kshort_mu_LowMass = eff_mc_Kshort_mu_LowMass[hist_mc_Kshort_mu_LowMass->FindBin(0.9)-1];
    double eff_0p9_mc_Kshort_mu_HighMass = eff_mc_Kshort_mu_HighMass[hist_mc_Kshort_mu_HighMass->FindBin(0.9)-1];
    double eff_0p9_mc_Kshort_e_LowMass = eff_mc_Kshort_e_LowMass[hist_mc_Kshort_e_LowMass->FindBin(0.9)-1];
    double eff_0p9_mc_Kshort_e_HighMass = eff_mc_Kshort_e_HighMass[hist_mc_Kshort_e_HighMass->FindBin(0.9)-1];

    //error calculation
    double yield_0p9_data_Kshort_mu_LowMass = hist_data_Kshort_mu_LowMass->GetBinContent(37) + hist_data_Kshort_mu_LowMass->GetBinContent(38) + hist_data_Kshort_mu_LowMass->GetBinContent(39) + hist_data_Kshort_mu_LowMass->GetBinContent(40);
    double yield_0p9_data_Kshort_mu_HighMass = hist_data_Kshort_mu_HighMass->GetBinContent(37) + hist_data_Kshort_mu_HighMass->GetBinContent(38) + hist_data_Kshort_mu_HighMass->GetBinContent(39) + hist_data_Kshort_mu_HighMass->GetBinContent(40);
    double yield_0p9_data_Kshort_e_LowMass = hist_data_Kshort_e_LowMass->GetBinContent(37) + hist_data_Kshort_e_LowMass->GetBinContent(38) + hist_data_Kshort_e_LowMass->GetBinContent(39) + hist_data_Kshort_e_LowMass->GetBinContent(40);
    double yield_0p9_data_Kshort_e_HighMass = hist_data_Kshort_e_HighMass->GetBinContent(37) + hist_data_Kshort_e_HighMass->GetBinContent(38) + hist_data_Kshort_e_HighMass->GetBinContent(39) + hist_data_Kshort_e_HighMass->GetBinContent(40);
    double yield_0p9_mc_Kshort_mu_LowMass = hist_mc_Kshort_mu_LowMass->GetBinContent(37) + hist_mc_Kshort_mu_LowMass->GetBinContent(38) + hist_mc_Kshort_mu_LowMass->GetBinContent(39) + hist_mc_Kshort_mu_LowMass->GetBinContent(40);
    double yield_0p9_mc_Kshort_mu_HighMass = hist_mc_Kshort_mu_HighMass->GetBinContent(37) + hist_mc_Kshort_mu_HighMass->GetBinContent(38) + hist_mc_Kshort_mu_HighMass->GetBinContent(39) + hist_mc_Kshort_mu_HighMass->GetBinContent(40);
    double yield_0p9_mc_Kshort_e_LowMass = hist_mc_Kshort_e_LowMass->GetBinContent(37) + hist_mc_Kshort_e_LowMass->GetBinContent(38) + hist_mc_Kshort_e_LowMass->GetBinContent(39) + hist_mc_Kshort_e_LowMass->GetBinContent(40);
    double yield_0p9_mc_Kshort_e_HighMass = hist_mc_Kshort_e_HighMass->GetBinContent(37) + hist_mc_Kshort_e_HighMass->GetBinContent(38) + hist_mc_Kshort_e_HighMass->GetBinContent(39) + hist_mc_Kshort_e_HighMass->GetBinContent(40);

    double yieldErr_0p9_data_Kshort_mu_LowMass = sqrt(pow(hist_data_Kshort_mu_LowMass->GetBinError(37),2) + pow(hist_data_Kshort_mu_LowMass->GetBinError(38),2) + pow(hist_data_Kshort_mu_LowMass->GetBinError(39),2) + pow(hist_data_Kshort_mu_LowMass->GetBinError(40),2));
    double yieldErr_0p9_data_Kshort_mu_HighMass = sqrt(pow(hist_data_Kshort_mu_HighMass->GetBinError(37),2) + pow(hist_data_Kshort_mu_HighMass->GetBinError(38),2) + pow(hist_data_Kshort_mu_HighMass->GetBinError(39),2) + pow(hist_data_Kshort_mu_HighMass->GetBinError(40),2));
    double yieldErr_0p9_data_Kshort_e_LowMass = sqrt(pow(hist_data_Kshort_e_LowMass->GetBinError(37),2) + pow(hist_data_Kshort_e_LowMass->GetBinError(38),2) + pow(hist_data_Kshort_e_LowMass->GetBinError(39),2) + pow(hist_data_Kshort_e_LowMass->GetBinError(40),2));
    double yieldErr_0p9_data_Kshort_e_HighMass = sqrt(pow(hist_data_Kshort_e_HighMass->GetBinError(37),2) + pow(hist_data_Kshort_e_HighMass->GetBinError(38),2) + pow(hist_data_Kshort_e_HighMass->GetBinError(39),2) + pow(hist_data_Kshort_e_HighMass->GetBinError(40),2));
    double yieldErr_0p9_mc_Kshort_mu_LowMass = sqrt(pow(hist_mc_Kshort_mu_LowMass->GetBinError(37),2) + pow(hist_mc_Kshort_mu_LowMass->GetBinError(38),2) + pow(hist_mc_Kshort_mu_LowMass->GetBinError(39),2) + pow(hist_mc_Kshort_mu_LowMass->GetBinError(40),2));
    double yieldErr_0p9_mc_Kshort_mu_HighMass = sqrt(pow(hist_mc_Kshort_mu_HighMass->GetBinError(37),2) + pow(hist_mc_Kshort_mu_HighMass->GetBinError(38),2) + pow(hist_mc_Kshort_mu_HighMass->GetBinError(39),2) + pow(hist_mc_Kshort_mu_HighMass->GetBinError(40),2));
    double yieldErr_0p9_mc_Kshort_e_LowMass = sqrt(pow(hist_mc_Kshort_e_LowMass->GetBinError(37),2) + pow(hist_mc_Kshort_e_LowMass->GetBinError(38),2) + pow(hist_mc_Kshort_e_LowMass->GetBinError(39),2) + pow(hist_mc_Kshort_e_LowMass->GetBinError(40),2));
    double yieldErr_0p9_mc_Kshort_e_HighMass = sqrt(pow(hist_mc_Kshort_e_HighMass->GetBinError(37),2) + pow(hist_mc_Kshort_e_HighMass->GetBinError(38),2) + pow(hist_mc_Kshort_e_HighMass->GetBinError(39),2) + pow(hist_mc_Kshort_e_HighMass->GetBinError(40),2));

    double ratioErr_0p9_data_Kshort_mu_LowMass = ratio_error(yield_0p9_data_Kshort_mu_LowMass, yield_0p9_mc_Kshort_mu_LowMass, yieldErr_0p9_data_Kshort_mu_LowMass, yieldErr_0p9_mc_Kshort_mu_LowMass);
    double ratioErr_0p9_data_Kshort_mu_HighMass = ratio_error(yield_0p9_data_Kshort_mu_HighMass, yield_0p9_mc_Kshort_mu_HighMass, yieldErr_0p9_data_Kshort_mu_HighMass, yieldErr_0p9_mc_Kshort_mu_HighMass);
    double ratioErr_0p9_data_Kshort_e_LowMass = ratio_error(yield_0p9_data_Kshort_e_LowMass, yield_0p9_mc_Kshort_e_LowMass, yieldErr_0p9_data_Kshort_e_LowMass, yieldErr_0p9_mc_Kshort_e_LowMass);
    double ratioErr_0p9_data_Kshort_e_HighMass = ratio_error(yield_0p9_data_Kshort_e_HighMass, yield_0p9_mc_Kshort_e_HighMass, yieldErr_0p9_data_Kshort_e_HighMass, yieldErr_0p9_mc_Kshort_e_HighMass);

    std::ostringstream str_mu_LowMass_2, str_mu_HighMass_2, str_e_LowMass_2, str_e_HighMass_2;
    str_mu_LowMass_2 << std::setprecision(3) << "$\\mu$ Low Mass PFN & " << 100.*eff_0p9_data_Kshort_mu_LowMass << " & " << 100.*eff_0p9_mc_Kshort_mu_LowMass << " & " << 100.*std::abs(eff_0p9_data_Kshort_mu_LowMass - eff_0p9_mc_Kshort_mu_LowMass)/eff_0p9_data_Kshort_mu_LowMass << " & " << yield_0p9_data_Kshort_mu_LowMass/yield_0p9_mc_Kshort_mu_LowMass << " $\\pm$ " << ratioErr_0p9_data_Kshort_mu_LowMass << "\\\\";
    str_mu_HighMass_2 << std::setprecision(3) << "$\\mu$ High Mass PFN & " << 100.*eff_0p9_data_Kshort_mu_HighMass << " & " << 100.*eff_0p9_mc_Kshort_mu_HighMass << " & " << 100.*std::abs(eff_0p9_data_Kshort_mu_HighMass - eff_0p9_mc_Kshort_mu_HighMass)/eff_0p9_data_Kshort_mu_HighMass << " & " << yield_0p9_data_Kshort_mu_HighMass/yield_0p9_mc_Kshort_mu_HighMass << " $\\pm$ " << ratioErr_0p9_data_Kshort_mu_HighMass << "\\\\";
    str_e_LowMass_2 << std::setprecision(3) << "$e$ Low Mass PFN & " << 100.*eff_0p9_data_Kshort_e_LowMass << " & " << 100.*eff_0p9_mc_Kshort_e_LowMass << " & " << 100.*std::abs(eff_0p9_data_Kshort_e_LowMass - eff_0p9_mc_Kshort_e_LowMass)/eff_0p9_data_Kshort_e_LowMass << " & " << yield_0p9_data_Kshort_e_LowMass/yield_0p9_mc_Kshort_e_LowMass << " $\\pm$ " << ratioErr_0p9_data_Kshort_e_LowMass << "\\\\";
    str_e_HighMass_2 << std::setprecision(3) << "$e$ High Mass PFN & " << 100.*eff_0p9_data_Kshort_e_HighMass << " & " << 100.*eff_0p9_mc_Kshort_e_HighMass << " & " << 100.*std::abs(eff_0p9_data_Kshort_e_HighMass - eff_0p9_mc_Kshort_e_HighMass)/eff_0p9_data_Kshort_e_HighMass << " & " << yield_0p9_data_Kshort_e_HighMass/yield_0p9_mc_Kshort_e_HighMass << " $\\pm$ " << ratioErr_0p9_data_Kshort_e_HighMass << "\\\\";

    //str_mu_LowMass_2 << std::setprecision(4) << "$\\mu$ Low Mass PFN & " << 100.*eff_0p9_data_Kshort_mu_LowMass << " & " << 100.*eff_0p9_mc_Kshort_mu_LowMass << " & " << 100.*(std::abs(eff_0p9_data_Kshort_mu_LowMass - eff_0p9_mc_Kshort_mu_LowMass)) << " & " << 100.*std::abs(eff_0p9_data_Kshort_mu_LowMass - eff_0p9_mc_Kshort_mu_LowMass)/eff_0p9_data_Kshort_mu_LowMass << "\\\\";
    //str_mu_HighMass_2 << std::setprecision(4) << "$\\mu$ High Mass PFN & " << 100.*eff_0p9_data_Kshort_mu_HighMass << " & " << 100.*eff_0p9_mc_Kshort_mu_HighMass << " & " << 100.*(std::abs(eff_0p9_data_Kshort_mu_HighMass - eff_0p9_mc_Kshort_mu_HighMass)) << " & " << 100.*std::abs(eff_0p9_data_Kshort_mu_HighMass - eff_0p9_mc_Kshort_mu_HighMass)/eff_0p9_data_Kshort_mu_HighMass << "\\\\";
    //str_e_LowMass_2 << std::setprecision(4) << "$e$ Low Mass PFN & " << 100.*eff_0p9_data_Kshort_e_LowMass << " & " << 100.*eff_0p9_mc_Kshort_e_LowMass << " & " << 100.*(std::abs(eff_0p9_data_Kshort_e_LowMass - eff_0p9_mc_Kshort_e_LowMass)) << " & " << 100.*std::abs(eff_0p9_data_Kshort_e_LowMass - eff_0p9_mc_Kshort_e_LowMass)/eff_0p9_data_Kshort_e_LowMass << "\\\\";
    //str_e_HighMass_2 << std::setprecision(4) << "$e$ High Mass PFN & " << 100.*eff_0p9_data_Kshort_e_HighMass << " & " << 100.*eff_0p9_mc_Kshort_e_HighMass << " & " << 100.*(std::abs(eff_0p9_data_Kshort_e_HighMass - eff_0p9_mc_Kshort_e_HighMass)) << " & " << 100.*std::abs(eff_0p9_data_Kshort_e_HighMass - eff_0p9_mc_Kshort_e_HighMass)/eff_0p9_data_Kshort_e_HighMass << "\\\\";

    std::cout << "year: " << year << std::endl;
    std::cout << "data eff & mc eff (cut at 0.9)" << std::endl;
    std::cout << str_mu_LowMass_2.str() << std::endl;
    std::cout << str_mu_HighMass_2.str() << std::endl;
    std::cout << str_e_LowMass_2.str() << std::endl;
    std::cout << str_e_HighMass_2.str() << std::endl;

    double eff_0p98_data_Kshort_mu_LowMass = eff_data_Kshort_mu_LowMass[hist_data_Kshort_mu_LowMass->FindBin(0.98)-1];
    double eff_0p98_data_Kshort_mu_HighMass = eff_data_Kshort_mu_HighMass[hist_data_Kshort_mu_HighMass->FindBin(0.98)-1];
    double eff_0p98_data_Kshort_e_LowMass = eff_data_Kshort_e_LowMass[hist_data_Kshort_e_LowMass->FindBin(0.98)-1];
    double eff_0p98_data_Kshort_e_HighMass = eff_data_Kshort_e_HighMass[hist_data_Kshort_e_HighMass->FindBin(0.98)-1];
    double eff_0p98_mc_Kshort_mu_LowMass = eff_mc_Kshort_mu_LowMass[hist_mc_Kshort_mu_LowMass->FindBin(0.98)-1];
    double eff_0p98_mc_Kshort_mu_HighMass = eff_mc_Kshort_mu_HighMass[hist_mc_Kshort_mu_HighMass->FindBin(0.98)-1];
    double eff_0p98_mc_Kshort_e_LowMass = eff_mc_Kshort_e_LowMass[hist_mc_Kshort_e_LowMass->FindBin(0.98)-1];
    double eff_0p98_mc_Kshort_e_HighMass = eff_mc_Kshort_e_HighMass[hist_mc_Kshort_e_HighMass->FindBin(0.98)-1];

    double ratioErr_0p98_data_Kshort_mu_LowMass = ratio_error(hist_data_Kshort_mu_LowMass->GetBinContent(40), hist_mc_Kshort_mu_LowMass->GetBinContent(40), hist_data_Kshort_mu_LowMass->GetBinError(40), hist_mc_Kshort_mu_LowMass->GetBinError(40));
    double ratioErr_0p98_data_Kshort_mu_HighMass = ratio_error(hist_data_Kshort_mu_HighMass->GetBinContent(40), hist_mc_Kshort_mu_HighMass->GetBinContent(40), hist_data_Kshort_mu_HighMass->GetBinError(40), hist_mc_Kshort_mu_HighMass->GetBinError(40));
    double ratioErr_0p98_data_Kshort_e_LowMass = ratio_error(hist_data_Kshort_e_LowMass->GetBinContent(40), hist_mc_Kshort_e_LowMass->GetBinContent(40), hist_data_Kshort_e_LowMass->GetBinError(40), hist_mc_Kshort_e_LowMass->GetBinError(40));
    double ratioErr_0p98_data_Kshort_e_HighMass = ratio_error(hist_data_Kshort_e_HighMass->GetBinContent(40), hist_mc_Kshort_e_HighMass->GetBinContent(40), hist_data_Kshort_e_HighMass->GetBinError(40), hist_mc_Kshort_e_HighMass->GetBinError(40));
    
    str_mu_LowMass_2.str(""); str_mu_HighMass_2.str(""); str_e_LowMass_2.str(""); str_e_HighMass_2.str("");
    str_mu_LowMass_2.clear(); str_mu_HighMass_2.clear(); str_e_LowMass_2.clear(); str_e_HighMass_2.clear();
    str_mu_LowMass_2 << std::setprecision(3) << "$\\mu$ Low Mass PFN & " << 100.*eff_0p98_data_Kshort_mu_LowMass << " & " << 100.*eff_0p98_mc_Kshort_mu_LowMass << " & " << 100.*std::abs(eff_0p98_data_Kshort_mu_LowMass - eff_0p98_mc_Kshort_mu_LowMass)/eff_0p98_data_Kshort_mu_LowMass << " & " << hist_data_Kshort_mu_LowMass->GetBinContent(40)/hist_mc_Kshort_mu_LowMass->GetBinContent(40) << " $\\pm$ " << ratioErr_0p98_data_Kshort_mu_LowMass << "\\\\";
    str_mu_HighMass_2 << std::setprecision(3) << "$\\mu$ High Mass PFN & " << 100.*eff_0p98_data_Kshort_mu_HighMass << " & " << 100.*eff_0p98_mc_Kshort_mu_HighMass << " & " << 100.*std::abs(eff_0p98_data_Kshort_mu_HighMass - eff_0p98_mc_Kshort_mu_HighMass)/eff_0p98_data_Kshort_mu_HighMass << " & " << hist_data_Kshort_mu_HighMass->GetBinContent(40)/hist_mc_Kshort_mu_HighMass->GetBinContent(40) << " $\\pm$ " << ratioErr_0p98_data_Kshort_mu_HighMass << "\\\\";
    str_e_LowMass_2 << std::setprecision(3) << "$e$ Low Mass PFN & " << 100.*eff_0p98_data_Kshort_e_LowMass << " & " << 100.*eff_0p98_mc_Kshort_e_LowMass << " & " << 100.*std::abs(eff_0p98_data_Kshort_e_LowMass - eff_0p98_mc_Kshort_e_LowMass)/eff_0p98_data_Kshort_e_LowMass << " & " << hist_data_Kshort_e_LowMass->GetBinContent(40)/hist_mc_Kshort_e_LowMass->GetBinContent(40) << " $\\pm$ " << ratioErr_0p98_data_Kshort_e_LowMass << "\\\\";
    str_e_HighMass_2 << std::setprecision(3) << "$e$ High Mass PFN & " << 100.*eff_0p98_data_Kshort_e_HighMass << " & " << 100.*eff_0p98_mc_Kshort_e_HighMass << " & " << 100.*std::abs(eff_0p98_data_Kshort_e_HighMass - eff_0p98_mc_Kshort_e_HighMass)/eff_0p98_data_Kshort_e_HighMass << " & " << hist_data_Kshort_e_HighMass->GetBinContent(40)/hist_mc_Kshort_e_HighMass->GetBinContent(40) << " $\\pm$ " << ratioErr_0p98_data_Kshort_e_HighMass << "\\\\";

    //str_mu_LowMass_2 << std::setprecision(4) << "$\\mu$ Low Mass PFN & " << 100.*eff_0p98_data_Kshort_mu_LowMass << " & " << 100.*eff_0p98_mc_Kshort_mu_LowMass << " & " << 100.*(std::abs(eff_0p98_data_Kshort_mu_LowMass - eff_0p98_mc_Kshort_mu_LowMass)) << " & " << 100.*std::abs(eff_0p98_data_Kshort_mu_LowMass - eff_0p98_mc_Kshort_mu_LowMass)/eff_0p98_data_Kshort_mu_LowMass << "\\\\";
    //str_mu_HighMass_2 << std::setprecision(4) << "$\\mu$ High Mass PFN & " << 100.*eff_0p98_data_Kshort_mu_HighMass << " & " << 100.*eff_0p98_mc_Kshort_mu_HighMass << " & " << 100.*(std::abs(eff_0p98_data_Kshort_mu_HighMass - eff_0p98_mc_Kshort_mu_HighMass)) << " & " << 100.*std::abs(eff_0p98_data_Kshort_mu_HighMass - eff_0p98_mc_Kshort_mu_HighMass)/eff_0p98_data_Kshort_mu_HighMass << "\\\\";
    //str_e_LowMass_2 << std::setprecision(4) << "$e$ Low Mass PFN & " << 100.*eff_0p98_data_Kshort_e_LowMass << " & " << 100.*eff_0p98_mc_Kshort_e_LowMass << " & " << 100.*(std::abs(eff_0p98_data_Kshort_e_LowMass - eff_0p98_mc_Kshort_e_LowMass)) << " & " << 100.*std::abs(eff_0p98_data_Kshort_e_LowMass - eff_0p98_mc_Kshort_e_LowMass)/eff_0p98_data_Kshort_e_LowMass << "\\\\";
    //str_e_HighMass_2 << std::setprecision(4) << "$e$ High Mass PFN & " << 100.*eff_0p98_data_Kshort_e_HighMass << " & " << 100.*eff_0p98_mc_Kshort_e_HighMass << " & " << 100.*(std::abs(eff_0p98_data_Kshort_e_HighMass - eff_0p98_mc_Kshort_e_HighMass)) << " & " << 100.*std::abs(eff_0p98_data_Kshort_e_HighMass - eff_0p98_mc_Kshort_e_HighMass)/eff_0p98_data_Kshort_e_HighMass << "\\\\";

    std::cout << "data eff & mc eff (cut at 0.98)" << std::endl;
    std::cout << str_mu_LowMass_2.str() << std::endl;
    std::cout << str_mu_HighMass_2.str() << std::endl;
    std::cout << str_e_LowMass_2.str() << std::endl;
    std::cout << str_e_HighMass_2.str() << std::endl;
}


# ifndef __CINT__ 
int main(int argc, char * argv[])
{
    print_Kshort_efficiency("Run2");
    print_Kshort_efficiency("2016");
    print_Kshort_efficiency("2017");
    print_Kshort_efficiency("2018");
    print_Kshort_efficiency("2016HIP");
    print_Kshort_efficiency("2016noHIP");
    return 0;

    std::map<TString, double> PFNcuts;
    PFNcuts["ee_2016_2GeV"] = get_PFNcut(5, 0, true, false);
    PFNcuts["ee_2016_5GeV"] = get_PFNcut(5, 0, true, false);
    PFNcuts["ee_2016_8GeV"] = get_PFNcut(10, 0, true, false);
    PFNcuts["ee_2016_12GeV"] = get_PFNcut(10, 0, true, false);
    PFNcuts["mm_2016_2GeV"] = get_PFNcut(5, 1, true, false);
    PFNcuts["mm_2016_5GeV"] = get_PFNcut(5, 1, true, false);
    PFNcuts["mm_2016_8GeV"] = get_PFNcut(10, 1, true, false);
    PFNcuts["mm_2016_12GeV"] = get_PFNcut(10, 1, true, false);
    PFNcuts["ee_2017_2GeV"] = get_PFNcut(5, 0, false, true);
    PFNcuts["ee_2017_5GeV"] = get_PFNcut(5, 0, false, true);
    PFNcuts["ee_2017_8GeV"] = get_PFNcut(10, 0, false, true);
    PFNcuts["ee_2017_12GeV"] = get_PFNcut(10, 0, false, true);
    PFNcuts["mm_2017_2GeV"] = get_PFNcut(5, 1, false, true);
    PFNcuts["mm_2017_5GeV"] = get_PFNcut(5, 1, false, true);
    PFNcuts["mm_2017_8GeV"] = get_PFNcut(10, 1, false, true);
    PFNcuts["mm_2017_12GeV"] = get_PFNcut(10, 1, false, true);
    PFNcuts["ee_2018_2GeV"] = get_PFNcut(5, 0, false, false);
    PFNcuts["ee_2018_5GeV"] = get_PFNcut(5, 0, false, false);
    PFNcuts["ee_2018_8GeV"] = get_PFNcut(10, 0, false, false);
    PFNcuts["ee_2018_12GeV"] = get_PFNcut(10, 0, false, false);
    PFNcuts["mm_2018_2GeV"] = get_PFNcut(5, 1, false, false);
    PFNcuts["mm_2018_5GeV"] = get_PFNcut(5, 1, false, false);
    PFNcuts["mm_2018_8GeV"] = get_PFNcut(10, 1, false, false);
    PFNcuts["mm_2018_12GeV"] = get_PFNcut(10, 1, false, false);

    PFNcuts["em_2016_2GeV"] = get_PFNcut(5, 1, true, false);
    PFNcuts["em_2016_5GeV"] = get_PFNcut(5, 1, true, false);
    PFNcuts["em_2016_8GeV"] = get_PFNcut(10, 1, true, false);
    PFNcuts["em_2016_12GeV"] = get_PFNcut(10, 1, true, false);
    PFNcuts["me_2016_2GeV"] = get_PFNcut(5, 0, true, false);
    PFNcuts["me_2016_5GeV"] = get_PFNcut(5, 0, true, false);
    PFNcuts["me_2016_8GeV"] = get_PFNcut(10, 0, true, false);
    PFNcuts["me_2016_12GeV"] = get_PFNcut(10, 0, true, false);
    PFNcuts["em_2017_2GeV"] = get_PFNcut(5, 1, false, true);
    PFNcuts["em_2017_5GeV"] = get_PFNcut(5, 1, false, true);
    PFNcuts["em_2017_8GeV"] = get_PFNcut(10, 1, false, true);
    PFNcuts["em_2017_12GeV"] = get_PFNcut(10, 1, false, true);
    PFNcuts["me_2017_2GeV"] = get_PFNcut(5, 0, false, true);
    PFNcuts["me_2017_5GeV"] = get_PFNcut(5, 0, false, true);
    PFNcuts["me_2017_8GeV"] = get_PFNcut(10, 0, false, true);
    PFNcuts["me_2017_12GeV"] = get_PFNcut(10, 0, false, true);
    PFNcuts["em_2018_2GeV"] = get_PFNcut(5, 1, false, false);
    PFNcuts["em_2018_5GeV"] = get_PFNcut(5, 1, false, false);
    PFNcuts["em_2018_8GeV"] = get_PFNcut(10, 1, false, false);
    PFNcuts["em_2018_12GeV"] = get_PFNcut(10, 1, false, false);
    PFNcuts["me_2018_2GeV"] = get_PFNcut(5, 0, false, false);
    PFNcuts["me_2018_5GeV"] = get_PFNcut(5, 0, false, false);
    PFNcuts["me_2018_8GeV"] = get_PFNcut(10, 0, false, false);
    PFNcuts["me_2018_12GeV"] = get_PFNcut(10, 0, false, false);

    PFNcuts["ee_2016_5Bkg"] = get_PFNcut(5, 0, true, false);
    PFNcuts["ee_2016_10Bkg"] = get_PFNcut(10, 0, true, false);
    PFNcuts["mm_2016_5Bkg"] = get_PFNcut(5, 1, true, false);
    PFNcuts["mm_2016_10Bkg"] = get_PFNcut(10, 1, true, false);
    PFNcuts["ee_2017_5Bkg"] = get_PFNcut(5, 0, false, true);
    PFNcuts["ee_2017_10Bkg"] = get_PFNcut(10, 0, false, true);
    PFNcuts["mm_2017_5Bkg"] = get_PFNcut(5, 1, false, true);
    PFNcuts["mm_2017_10Bkg"] = get_PFNcut(10, 1, false, true);
    PFNcuts["ee_2018_5Bkg"] = get_PFNcut(5, 0, false, false);
    PFNcuts["ee_2018_10Bkg"] = get_PFNcut(10, 0, false, false);
    PFNcuts["mm_2018_5Bkg"] = get_PFNcut(5, 1, false, false);
    PFNcuts["mm_2018_10Bkg"] = get_PFNcut(10, 1, false, false);
    PFNcuts["em_2016_5Bkg"] = get_PFNcut(5, 1, true, false);
    PFNcuts["em_2016_10Bkg"] = get_PFNcut(10, 1, true, false);
    PFNcuts["me_2016_5Bkg"] = get_PFNcut(5, 0, true, false);
    PFNcuts["me_2016_10Bkg"] = get_PFNcut(10, 0, true, false);
    PFNcuts["em_2017_5Bkg"] = get_PFNcut(5, 1, false, true);
    PFNcuts["em_2017_10Bkg"] = get_PFNcut(10, 1, false, true);
    PFNcuts["me_2017_5Bkg"] = get_PFNcut(5, 0, false, true);
    PFNcuts["me_2017_10Bkg"] = get_PFNcut(10, 0, false, true);
    PFNcuts["em_2018_5Bkg"] = get_PFNcut(5, 1, false, false);
    PFNcuts["em_2018_10Bkg"] = get_PFNcut(10, 1, false, false);
    PFNcuts["me_2018_5Bkg"] = get_PFNcut(5, 0, false, false);
    PFNcuts["me_2018_10Bkg"] = get_PFNcut(10, 0, false, false);

    std::map<TString, double> PFNcuts_0p9;
    PFNcuts_0p9["e_2016_2GeV"] =  0.9; 
    PFNcuts_0p9["e_2016_5GeV"] =  0.9;
    PFNcuts_0p9["e_2016_8GeV"] =  0.9;
    PFNcuts_0p9["e_2016_12GeV"] = 0.9;
    PFNcuts_0p9["m_2016_2GeV"] =  0.96;
    PFNcuts_0p9["m_2016_5GeV"] =  0.96;
    PFNcuts_0p9["m_2016_8GeV"] =  0.96;
    PFNcuts_0p9["m_2016_12GeV"] = 0.96;
    PFNcuts_0p9["e_2017_2GeV"] =  0.9;
    PFNcuts_0p9["e_2017_5GeV"] =  0.9;
    PFNcuts_0p9["e_2017_8GeV"] =  0.9;
    PFNcuts_0p9["e_2017_12GeV"] = 0.9;
    PFNcuts_0p9["m_2017_2GeV"] =  0.96;
    PFNcuts_0p9["m_2017_5GeV"] =  0.96;
    PFNcuts_0p9["m_2017_8GeV"] =  0.96;
    PFNcuts_0p9["m_2017_12GeV"] = 0.96;
    PFNcuts_0p9["e_2018_2GeV"] =  0.9;
    PFNcuts_0p9["e_2018_5GeV"] =  0.9;
    PFNcuts_0p9["e_2018_8GeV"] =  0.9;
    PFNcuts_0p9["e_2018_12GeV"] = 0.9;
    PFNcuts_0p9["m_2018_2GeV"] =  0.96;
    PFNcuts_0p9["m_2018_5GeV"] =  0.96;
    PFNcuts_0p9["m_2018_8GeV"] =  0.96;
    PFNcuts_0p9["m_2018_12GeV"] = 0.96;

    PFNcuts_0p9["e_2016_5Bkg"] =  0.9;
    PFNcuts_0p9["e_2016_10Bkg"] = 0.9;
    PFNcuts_0p9["m_2016_5Bkg"] =  0.96;
    PFNcuts_0p9["m_2016_10Bkg"] = 0.96;
    PFNcuts_0p9["e_2017_5Bkg"] =  0.9;
    PFNcuts_0p9["e_2017_10Bkg"] = 0.9;
    PFNcuts_0p9["m_2017_5Bkg"] =  0.96;
    PFNcuts_0p9["m_2017_10Bkg"] = 0.96;
    PFNcuts_0p9["e_2018_5Bkg"] =  0.9;
    PFNcuts_0p9["e_2018_10Bkg"] = 0.9;
    PFNcuts_0p9["m_2018_5Bkg"] =  0.96;
    PFNcuts_0p9["m_2018_10Bkg"] = 0.96; 

    PFNcuts_0p9["e_2016_5Data"] =  0.9;
    PFNcuts_0p9["e_2016_10Data"] = 0.9;
    PFNcuts_0p9["m_2016_5Data"] =  0.96;
    PFNcuts_0p9["m_2016_10Data"] = 0.96;
    PFNcuts_0p9["e_2017_5Data"] =  0.9;
    PFNcuts_0p9["e_2017_10Data"] = 0.9;
    PFNcuts_0p9["m_2017_5Data"] =  0.96;
    PFNcuts_0p9["m_2017_10Data"] = 0.96;
    PFNcuts_0p9["e_2018_5Data"] =  0.9;
    PFNcuts_0p9["e_2018_10Data"] = 0.9;
    PFNcuts_0p9["m_2018_5Data"] =  0.96;
    PFNcuts_0p9["m_2018_10Data"] = 0.96; 


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
    
    files["e_2016_5Data"] = TFile::Open(filename_2016_Data);
    files["e_2017_5Data"] = TFile::Open(filename_2017_Data);
    files["e_2018_5Data"] = TFile::Open(filename_2018_Data);
    files["m_2016_5Data"] = files["e_2016_5Data"];
    files["m_2017_5Data"] = files["e_2017_5Data"];
    files["m_2018_5Data"] = files["e_2018_5Data"];
    files["e_2016_10Data"] = files["e_2016_5Data"];
    files["e_2017_10Data"] = files["e_2017_5Data"];
    files["e_2018_10Data"] = files["e_2018_5Data"];
    files["m_2016_10Data"] = files["e_2016_5Data"];
    files["m_2017_10Data"] = files["e_2017_5Data"];
    files["m_2018_10Data"] = files["e_2018_5Data"];

    std::map<TString, TH1F*> hists;
    //hists["e_2016_2GeV"] = (TH1F*)files["e_2016_2GeV"]->Get("_ee"+get_MV2name(5,get_favorite_V2(2,"e"))+"_PFN_ROC");
    //hists["e_2016_5GeV"] = (TH1F*)files["e_2016_5GeV"]->Get("_ee"+get_MV2name(5,get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["e_2016_8GeV"] = (TH1F*)files["e_2016_8GeV"]->Get("_ee"+get_MV2name(10,get_favorite_V2(8,"e"))+"_PFN_ROC");
    //hists["e_2016_12GeV"] = (TH1F*)files["e_2016_12GeV"]->Get("_ee"+get_MV2name(10,get_favorite_V2(12,"e"))+"_PFN_ROC");
    //hists["m_2016_2GeV"] = (TH1F*)files["m_2016_2GeV"]->Get("_mm"+get_MV2name(5,get_favorite_V2(2,"mu"))+"_PFN_ROC");
    //hists["m_2016_5GeV"] = (TH1F*)files["m_2016_5GeV"]->Get("_mm"+get_MV2name(5,get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["m_2016_8GeV"] = (TH1F*)files["m_2016_8GeV"]->Get("_mm"+get_MV2name(10,get_favorite_V2(8,"mu"))+"_PFN_ROC");
    //hists["m_2016_12GeV"] = (TH1F*)files["m_2016_12GeV"]->Get("_mm"+get_MV2name(10,get_favorite_V2(12,"mu"))+"_PFN_ROC");
    //hists["e_2017_2GeV"] = (TH1F*)files["e_2017_2GeV"]->Get("_ee"+get_MV2name(5,get_favorite_V2(2,"e"))+"_PFN_ROC");
    //hists["e_2017_5GeV"] = (TH1F*)files["e_2017_5GeV"]->Get("_ee"+get_MV2name(5,get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["e_2017_8GeV"] = (TH1F*)files["e_2017_8GeV"]->Get("_ee"+get_MV2name(10,get_favorite_V2(8,"e"))+"_PFN_ROC");
    //hists["e_2017_12GeV"] = (TH1F*)files["e_2017_12GeV"]->Get("_ee"+get_MV2name(10,get_favorite_V2(12,"e"))+"_PFN_ROC");
    //hists["m_2017_2GeV"] = (TH1F*)files["m_2017_2GeV"]->Get("_mm"+get_MV2name(5,get_favorite_V2(2,"mu"))+"_PFN_ROC");
    //hists["m_2017_5GeV"] = (TH1F*)files["m_2017_5GeV"]->Get("_mm"+get_MV2name(5,get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["m_2017_8GeV"] = (TH1F*)files["m_2017_8GeV"]->Get("_mm"+get_MV2name(10,get_favorite_V2(8,"mu"))+"_PFN_ROC");
    //hists["m_2017_12GeV"] = (TH1F*)files["m_2017_12GeV"]->Get("_mm"+get_MV2name(10,get_favorite_V2(12,"mu"))+"_PFN_ROC");
    //hists["e_2018_2GeV"] = (TH1F*)files["e_2018_2GeV"]->Get("_ee"+get_MV2name(5,get_favorite_V2(2,"e"))+"_PFN_ROC");
    //hists["e_2018_5GeV"] = (TH1F*)files["e_2018_5GeV"]->Get("_ee"+get_MV2name(5,get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["e_2018_8GeV"] = (TH1F*)files["e_2018_8GeV"]->Get("_ee"+get_MV2name(10,get_favorite_V2(8,"e"))+"_PFN_ROC");
    //hists["e_2018_12GeV"] = (TH1F*)files["e_2018_12GeV"]->Get("_ee"+get_MV2name(10,get_favorite_V2(12,"e"))+"_PFN_ROC");
    //hists["m_2018_2GeV"] = (TH1F*)files["m_2018_2GeV"]->Get("_mm"+get_MV2name(5,get_favorite_V2(2,"mu"))+"_PFN_ROC");
    //hists["m_2018_5GeV"] = (TH1F*)files["m_2018_5GeV"]->Get("_mm"+get_MV2name(5,get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["m_2018_8GeV"] = (TH1F*)files["m_2018_8GeV"]->Get("_mm"+get_MV2name(10,get_favorite_V2(8,"mu"))+"_PFN_ROC");
    //hists["m_2018_12GeV"] = (TH1F*)files["m_2018_12GeV"]->Get("_mm"+get_MV2name(10,get_favorite_V2(12,"mu"))+"_PFN_ROC");

    //hists["e_2016_5Bkg"] = (TH1F*)files["e_2016_5Bkg"]->Get("_ee"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["e_2017_5Bkg"] = (TH1F*)files["e_2017_5Bkg"]->Get("_ee"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["e_2018_5Bkg"] = (TH1F*)files["e_2018_5Bkg"]->Get("_ee"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["m_2016_5Bkg"] = (TH1F*)files["m_2016_5Bkg"]->Get("_mm"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["m_2017_5Bkg"] = (TH1F*)files["m_2017_5Bkg"]->Get("_mm"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["m_2018_5Bkg"] = (TH1F*)files["m_2018_5Bkg"]->Get("_mm"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["e_2016_10Bkg"] = (TH1F*)files["e_2016_10Bkg"]->Get("_ee"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    //hists["e_2017_10Bkg"] = (TH1F*)files["e_2017_10Bkg"]->Get("_ee"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    //hists["e_2018_10Bkg"] = (TH1F*)files["e_2018_10Bkg"]->Get("_ee"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    //hists["m_2016_10Bkg"] = (TH1F*)files["m_2016_10Bkg"]->Get("_mm"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");
    //hists["m_2017_10Bkg"] = (TH1F*)files["m_2017_10Bkg"]->Get("_mm"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");
    //hists["m_2018_10Bkg"] = (TH1F*)files["m_2018_10Bkg"]->Get("_mm"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");

    //hists["e_2016_5Data"] = (TH1F*)files["e_2016_5Data"]->Get("_ee"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["e_2017_5Data"] = (TH1F*)files["e_2017_5Data"]->Get("_ee"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["e_2018_5Data"] = (TH1F*)files["e_2018_5Data"]->Get("_ee"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["m_2016_5Data"] = (TH1F*)files["m_2016_5Data"]->Get("_mm"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["m_2017_5Data"] = (TH1F*)files["m_2017_5Data"]->Get("_mm"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["m_2018_5Data"] = (TH1F*)files["m_2018_5Data"]->Get("_mm"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["e_2016_10Data"] = (TH1F*)files["e_2016_10Data"]->Get("_ee"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    //hists["e_2017_10Data"] = (TH1F*)files["e_2017_10Data"]->Get("_ee"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    //hists["e_2018_10Data"] = (TH1F*)files["e_2018_10Data"]->Get("_ee"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    //hists["m_2016_10Data"] = (TH1F*)files["m_2016_10Data"]->Get("_mm"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");
    //hists["m_2017_10Data"] = (TH1F*)files["m_2017_10Data"]->Get("_mm"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");
    //hists["m_2018_10Data"] = (TH1F*)files["m_2018_10Data"]->Get("_mm"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");

    ////for(const TString& mass : {"2","5","8","12"}){
    ////    for(std::string flavor : {"e", "mu"}){
    ////        for(const TString& year : {"2016", "2017", "2018"}){
    ////            double V2 = get_favorite_V2(std::atoi(mass), flavor);
    ////            TString MV2name = get_MV2name((mass == "2" or mass == "5")? 5 : 10, V2);
    ////            TString fl = flavor.substr(0,1);
    ////            std::cout << fl+"_"+year+"_"+mass+"GeV" << ": " << "_"+fl+fl+MV2name+"_PFN_ROC" << std::endl;
    ////            hists[fl+"_"+year+"_"+mass+ "GeV"] = (TH1F*)files[fl+"_"+year+"_"+mass+"GeV"]->Get("_"+fl+fl+MV2name+"_PFN_ROC");
    ////        }
    ////    }
    ////}
    ////for(const TString& mass : {"5","10"}){
    ////    for(std::string flavor : {"e", "mu"}){
    ////        for(const TString& year : {"2016", "2017", "2018"}){
    ////            double V2 = get_favorite_V2(std::atoi(mass), flavor);
    ////            TString MV2name = get_MV2name((mass == "5")? 5 : 10, V2);
    ////            TString fl = flavor.substr(0,1);
    ////            std::cout << fl+"_"+year+"_"+mass+"Bkg" << ": " << "_"+fl+fl+MV2name+"_PFN_ROC" << std::endl;
    ////            hists[fl+"_"+year+"_"+mass+ "Bkg"] = (TH1F*)files[fl+"_"+year+"_"+mass+"Bkg"]->Get("_"+fl+fl+MV2name+"_PFN_ROC");
    ////        }
    ////    }
    ////}


    std::map<TString, std::vector<double>> effs;
    //std::cout << "1";
    //effs["e_2016_2GeV"] = computeEfficiencyForROC(hists["e_2016_2GeV"]);
    //effs["e_2016_5GeV"] = computeEfficiencyForROC(hists["e_2016_5GeV"]);
    //effs["e_2016_8GeV"] = computeEfficiencyForROC(hists["e_2016_8GeV"]);
    //effs["e_2016_12GeV"] = computeEfficiencyForROC(hists["e_2016_12GeV"]);
    //effs["m_2016_2GeV"] = computeEfficiencyForROC(hists["m_2016_2GeV"]);
    //effs["m_2016_5GeV"] = computeEfficiencyForROC(hists["m_2016_5GeV"]);
    //std::cout << "2";
    //effs["m_2016_8GeV"] = computeEfficiencyForROC(hists["m_2016_8GeV"]);
    //effs["m_2016_12GeV"] = computeEfficiencyForROC(hists["m_2016_12GeV"]);
    //effs["e_2017_2GeV"] = computeEfficiencyForROC(hists["e_2017_2GeV"]);
    //effs["e_2017_5GeV"] = computeEfficiencyForROC(hists["e_2017_5GeV"]);
    //effs["e_2017_8GeV"] = computeEfficiencyForROC(hists["e_2017_8GeV"]);
    //effs["e_2017_12GeV"] = computeEfficiencyForROC(hists["e_2017_12GeV"]);
    //std::cout << "3";
    //effs["m_2017_2GeV"] = computeEfficiencyForROC(hists["m_2017_2GeV"]);
    //effs["m_2017_5GeV"] = computeEfficiencyForROC(hists["m_2017_5GeV"]);
    //effs["m_2017_8GeV"] = computeEfficiencyForROC(hists["m_2017_8GeV"]);
    //effs["m_2017_12GeV"] = computeEfficiencyForROC(hists["m_2017_12GeV"]);
    //effs["e_2018_2GeV"] = computeEfficiencyForROC(hists["e_2018_2GeV"]);
    //effs["e_2018_5GeV"] = computeEfficiencyForROC(hists["e_2018_5GeV"]);
    //effs["e_2018_8GeV"] = computeEfficiencyForROC(hists["e_2018_8GeV"]);
    //effs["e_2018_12GeV"] = computeEfficiencyForROC(hists["e_2018_12GeV"]);
    //std::cout << "4";
    //effs["m_2018_2GeV"] = computeEfficiencyForROC(hists["m_2018_2GeV"]);
    //effs["m_2018_5GeV"] = computeEfficiencyForROC(hists["m_2018_5GeV"]);
    //effs["m_2018_8GeV"] = computeEfficiencyForROC(hists["m_2018_8GeV"]);
    //effs["m_2018_12GeV"] = computeEfficiencyForROC(hists["m_2018_12GeV"]);

    //std::cout << "5";
    //effs["e_2016_5Bkg"] = computeEfficiencyForROC(hists["e_2016_5Bkg"]);
    //effs["e_2017_5Bkg"] = computeEfficiencyForROC(hists["e_2017_5Bkg"]);
    //effs["e_2018_5Bkg"] = computeEfficiencyForROC(hists["e_2018_5Bkg"]);
    //effs["m_2016_5Bkg"] = computeEfficiencyForROC(hists["m_2016_5Bkg"]);
    //std::cout << "6";
    //effs["m_2017_5Bkg"] = computeEfficiencyForROC(hists["m_2017_5Bkg"]);
    //effs["m_2018_5Bkg"] = computeEfficiencyForROC(hists["m_2018_5Bkg"]);
    //std::cout << "7";
    //effs["e_2016_10Bkg"] = computeEfficiencyForROC(hists["e_2016_10Bkg"]);
    //effs["e_2017_10Bkg"] = computeEfficiencyForROC(hists["e_2017_10Bkg"]);
    //effs["e_2018_10Bkg"] = computeEfficiencyForROC(hists["e_2018_10Bkg"]);
    //effs["m_2016_10Bkg"] = computeEfficiencyForROC(hists["m_2016_10Bkg"]);
    //effs["m_2017_10Bkg"] = computeEfficiencyForROC(hists["m_2017_10Bkg"]);
    //effs["m_2018_10Bkg"] = computeEfficiencyForROC(hists["m_2018_10Bkg"]);
    //
    //std::cout << "8";
    //effs["e_2016_5Data"] = computeEfficiencyForROC(hists["e_2016_5Data"]);
    //effs["e_2017_5Data"] = computeEfficiencyForROC(hists["e_2017_5Data"]);
    //effs["e_2018_5Data"] = computeEfficiencyForROC(hists["e_2018_5Data"]);
    //effs["m_2016_5Data"] = computeEfficiencyForROC(hists["m_2016_5Data"]);
    //std::cout << "9";
    //effs["m_2017_5Data"] = computeEfficiencyForROC(hists["m_2017_5Data"]);
    //effs["m_2018_5Data"] = computeEfficiencyForROC(hists["m_2018_5Data"]);
    //std::cout << "10";
    //effs["e_2016_10Data"] = computeEfficiencyForROC(hists["e_2016_10Data"]);
    //effs["e_2017_10Data"] = computeEfficiencyForROC(hists["e_2017_10Data"]);
    //effs["e_2018_10Data"] = computeEfficiencyForROC(hists["e_2018_10Data"]);
    //effs["m_2016_10Data"] = computeEfficiencyForROC(hists["m_2016_10Data"]);
    //std::cout << "11";
    //effs["m_2017_10Data"] = computeEfficiencyForROC(hists["m_2017_10Data"]);
    //effs["m_2018_10Data"] = computeEfficiencyForROC(hists["m_2018_10Data"]);

    //std::cout << "12";
    std::map<TString, double> PFNcut_effs;
    //PFNcut_effs["e_2016_2GeV"] = effs["e_2016_2GeV"][hists["e_2016_2GeV"]->FindBin(PFNcuts["e_2016_2GeV"])-1];
    //PFNcut_effs["e_2016_5GeV"] = effs["e_2016_5GeV"][hists["e_2016_5GeV"]->FindBin(PFNcuts["e_2016_5GeV"])-1];
    //PFNcut_effs["e_2016_8GeV"] = effs["e_2016_8GeV"][hists["e_2016_8GeV"]->FindBin(PFNcuts["e_2016_8GeV"])-1];
    //PFNcut_effs["e_2016_12GeV"] = effs["e_2016_12GeV"][hists["e_2016_12GeV"]->FindBin(PFNcuts["e_2016_12GeV"])-1];
    //PFNcut_effs["m_2016_2GeV"] = effs["m_2016_2GeV"][hists["m_2016_2GeV"]->FindBin(PFNcuts["m_2016_2GeV"])-1];
    //PFNcut_effs["m_2016_5GeV"] = effs["m_2016_5GeV"][hists["m_2016_5GeV"]->FindBin(PFNcuts["m_2016_5GeV"])-1];
    //PFNcut_effs["m_2016_8GeV"] = effs["m_2016_8GeV"][hists["m_2016_8GeV"]->FindBin(PFNcuts["m_2016_8GeV"])-1];
    //PFNcut_effs["m_2016_12GeV"] = effs["m_2016_12GeV"][hists["m_2016_12GeV"]->FindBin(PFNcuts["m_2016_12GeV"])-1];
    //PFNcut_effs["e_2017_2GeV"] = effs["e_2017_2GeV"][hists["e_2017_2GeV"]->FindBin(PFNcuts["e_2017_2GeV"])-1];
    //PFNcut_effs["e_2017_5GeV"] = effs["e_2017_5GeV"][hists["e_2017_5GeV"]->FindBin(PFNcuts["e_2017_5GeV"])-1];
    //PFNcut_effs["e_2017_8GeV"] = effs["e_2017_8GeV"][hists["e_2017_8GeV"]->FindBin(PFNcuts["e_2017_8GeV"])-1];
    //PFNcut_effs["e_2017_12GeV"] = effs["e_2017_12GeV"][hists["e_2017_12GeV"]->FindBin(PFNcuts["e_2017_12GeV"])-1];
    //PFNcut_effs["m_2017_2GeV"] = effs["m_2017_2GeV"][hists["m_2017_2GeV"]->FindBin(PFNcuts["m_2017_2GeV"])-1];
    //PFNcut_effs["m_2017_5GeV"] = effs["m_2017_5GeV"][hists["m_2017_5GeV"]->FindBin(PFNcuts["m_2017_5GeV"])-1];
    //PFNcut_effs["m_2017_8GeV"] = effs["m_2017_8GeV"][hists["m_2017_8GeV"]->FindBin(PFNcuts["m_2017_8GeV"])-1];
    //PFNcut_effs["m_2017_12GeV"] = effs["m_2017_12GeV"][hists["m_2017_12GeV"]->FindBin(PFNcuts["m_2017_12GeV"])-1];
    //PFNcut_effs["e_2018_2GeV"] = effs["e_2018_2GeV"][hists["e_2018_2GeV"]->FindBin(PFNcuts["e_2018_2GeV"])-1];
    //PFNcut_effs["e_2018_5GeV"] = effs["e_2018_5GeV"][hists["e_2018_5GeV"]->FindBin(PFNcuts["e_2018_5GeV"])-1];
    //PFNcut_effs["e_2018_8GeV"] = effs["e_2018_8GeV"][hists["e_2018_8GeV"]->FindBin(PFNcuts["e_2018_8GeV"])-1];
    //PFNcut_effs["e_2018_12GeV"] = effs["e_2018_12GeV"][hists["e_2018_12GeV"]->FindBin(PFNcuts["e_2018_12GeV"])-1];
    //PFNcut_effs["m_2018_2GeV"] = effs["m_2018_2GeV"][hists["m_2018_2GeV"]->FindBin(PFNcuts["m_2018_2GeV"])-1];
    //PFNcut_effs["m_2018_5GeV"] = effs["m_2018_5GeV"][hists["m_2018_5GeV"]->FindBin(PFNcuts["m_2018_5GeV"])-1];
    //PFNcut_effs["m_2018_8GeV"] = effs["m_2018_8GeV"][hists["m_2018_8GeV"]->FindBin(PFNcuts["m_2018_8GeV"])-1];
    //PFNcut_effs["m_2018_12GeV"] = effs["m_2018_12GeV"][hists["m_2018_12GeV"]->FindBin(PFNcuts["m_2018_12GeV"])-1];

    //PFNcut_effs["e_2016_5Bkg"] = effs["e_2016_5Bkg"][hists["e_2016_5Bkg"]->FindBin(PFNcuts["e_2016_5Bkg"])-1];
    //PFNcut_effs["e_2017_5Bkg"] = effs["e_2017_5Bkg"][hists["e_2017_5Bkg"]->FindBin(PFNcuts["e_2017_5Bkg"])-1];
    //PFNcut_effs["e_2018_5Bkg"] = effs["e_2018_5Bkg"][hists["e_2018_5Bkg"]->FindBin(PFNcuts["e_2018_5Bkg"])-1];
    //PFNcut_effs["m_2016_5Bkg"] = effs["m_2016_5Bkg"][hists["m_2016_5Bkg"]->FindBin(PFNcuts["m_2016_5Bkg"])-1];
    //PFNcut_effs["m_2017_5Bkg"] = effs["m_2017_5Bkg"][hists["m_2017_5Bkg"]->FindBin(PFNcuts["m_2017_5Bkg"])-1];
    //PFNcut_effs["m_2018_5Bkg"] = effs["m_2018_5Bkg"][hists["m_2018_5Bkg"]->FindBin(PFNcuts["m_2018_5Bkg"])-1];
    //PFNcut_effs["e_2016_10Bkg"] = effs["e_2016_10Bkg"][hists["e_2016_10Bkg"]->FindBin(PFNcuts["e_2016_10Bkg"])-1];
    //PFNcut_effs["e_2017_10Bkg"] = effs["e_2017_10Bkg"][hists["e_2017_10Bkg"]->FindBin(PFNcuts["e_2017_10Bkg"])-1];
    //PFNcut_effs["e_2018_10Bkg"] = effs["e_2018_10Bkg"][hists["e_2018_10Bkg"]->FindBin(PFNcuts["e_2018_10Bkg"])-1];
    //PFNcut_effs["m_2016_10Bkg"] = effs["m_2016_10Bkg"][hists["m_2016_10Bkg"]->FindBin(PFNcuts["m_2016_10Bkg"])-1];
    //PFNcut_effs["m_2017_10Bkg"] = effs["m_2017_10Bkg"][hists["m_2017_10Bkg"]->FindBin(PFNcuts["m_2017_10Bkg"])-1];
    //PFNcut_effs["m_2018_10Bkg"] = effs["m_2018_10Bkg"][hists["m_2018_10Bkg"]->FindBin(PFNcuts["m_2018_10Bkg"])-1];
    //
    //PFNcut_effs["e_2016_5Data"] = effs["e_2016_5Data"][hists["e_2016_5Data"]->FindBin(PFNcuts["e_2016_5Data"])-1];
    //PFNcut_effs["e_2017_5Data"] = effs["e_2017_5Data"][hists["e_2017_5Data"]->FindBin(PFNcuts["e_2017_5Data"])-1];
    //PFNcut_effs["e_2018_5Data"] = effs["e_2018_5Data"][hists["e_2018_5Data"]->FindBin(PFNcuts["e_2018_5Data"])-1];
    //PFNcut_effs["m_2016_5Data"] = effs["m_2016_5Data"][hists["m_2016_5Data"]->FindBin(PFNcuts["m_2016_5Data"])-1];
    //PFNcut_effs["m_2017_5Data"] = effs["m_2017_5Data"][hists["m_2017_5Data"]->FindBin(PFNcuts["m_2017_5Data"])-1];
    //PFNcut_effs["m_2018_5Data"] = effs["m_2018_5Data"][hists["m_2018_5Data"]->FindBin(PFNcuts["m_2018_5Data"])-1];
    //PFNcut_effs["e_2016_10Data"] = effs["e_2016_10Data"][hists["e_2016_10Data"]->FindBin(PFNcuts["e_2016_10Data"])-1];
    //PFNcut_effs["e_2017_10Data"] = effs["e_2017_10Data"][hists["e_2017_10Data"]->FindBin(PFNcuts["e_2017_10Data"])-1];
    //PFNcut_effs["e_2018_10Data"] = effs["e_2018_10Data"][hists["e_2018_10Data"]->FindBin(PFNcuts["e_2018_10Data"])-1];
    //PFNcut_effs["m_2016_10Data"] = effs["m_2016_10Data"][hists["m_2016_10Data"]->FindBin(PFNcuts["m_2016_10Data"])-1];
    //PFNcut_effs["m_2017_10Data"] = effs["m_2017_10Data"][hists["m_2017_10Data"]->FindBin(PFNcuts["m_2017_10Data"])-1];
    //PFNcut_effs["m_2018_10Data"] = effs["m_2018_10Data"][hists["m_2018_10Data"]->FindBin(PFNcuts["m_2018_10Data"])-1];


    //std::ostringstream e_2016_5_stream, e_2016_10_stream, e_2017_5_stream, e_2017_10_stream, e_2018_5_stream, e_2018_10_stream, m_2016_5_stream, m_2016_10_stream, m_2017_5_stream, m_2017_10_stream, m_2018_5_stream, m_2018_10_stream;
    //e_2016_5_stream << std::setprecision(2) << 100.*PFNcut_effs["e_2016_2GeV"] << "\\% & " << 100.*PFNcut_effs["e_2016_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs["e_2016_5Bkg"] << "\\%";
    //e_2016_10_stream << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs["e_2016_8GeV"] << "\\% & " << 100.*PFNcut_effs["e_2016_12GeV"] << "\\% & " << 100.*PFNcut_effs["e_2016_10Bkg"] << "\\%";
    //m_2016_5_stream << std::setprecision(2) << 100.*PFNcut_effs["m_2016_2GeV"] << "\\% & " << 100.*PFNcut_effs["m_2016_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs["m_2016_5Bkg"] << "\\%";
    //m_2016_10_stream << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs["m_2016_8GeV"] << "\\% & " << 100.*PFNcut_effs["m_2016_12GeV"] << "\\% & " << 100.*PFNcut_effs["m_2016_10Bkg"] << "\\%";
    //e_2017_5_stream << std::setprecision(2) << 100.*PFNcut_effs["e_2017_2GeV"] << "\\% & " << 100.*PFNcut_effs["e_2017_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs["e_2017_5Bkg"] << "\\%";
    //e_2017_10_stream << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs["e_2017_8GeV"] << "\\% & " << 100.*PFNcut_effs["e_2017_12GeV"] << "\\% & " << 100.*PFNcut_effs["e_2017_10Bkg"] << "\\%";
    //m_2017_5_stream << std::setprecision(2) << 100.*PFNcut_effs["m_2017_2GeV"] << "\\% & " << 100.*PFNcut_effs["m_2017_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs["m_2017_5Bkg"] << "\\%";
    //m_2017_10_stream << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs["m_2017_8GeV"] << "\\% & " << 100.*PFNcut_effs["m_2017_12GeV"] << "\\% & " << 100.*PFNcut_effs["m_2017_10Bkg"] << "\\%";
    //e_2018_5_stream << std::setprecision(2) << 100.*PFNcut_effs["e_2018_2GeV"] << "\\% & " << 100.*PFNcut_effs["e_2018_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs["e_2018_5Bkg"] << "\\%";
    //e_2018_10_stream << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs["e_2018_8GeV"] << "\\% & " << 100.*PFNcut_effs["e_2018_12GeV"] << "\\% & " << 100.*PFNcut_effs["e_2018_10Bkg"] << "\\%";
    //m_2018_5_stream << std::setprecision(2) << 100.*PFNcut_effs["m_2018_2GeV"] << "\\% & " << 100.*PFNcut_effs["m_2018_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs["m_2018_5Bkg"] << "\\%";
    //m_2018_10_stream << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs["m_2018_8GeV"] << "\\% & " << 100.*PFNcut_effs["m_2018_12GeV"] << "\\% & " << 100.*PFNcut_effs["m_2018_10Bkg"] << "\\%";

    //std::cout << "\\begin{table}" << std::endl;
    //std::cout << "    \\centering" << std::endl;
    //std::cout << "    \\caption{PFN cuts for defining the normal and inverted region.}" << std::endl;
    //std::cout << "    \\label{tab:PFNcuts}" << std::endl;
    //std::cout << "    \\begin{tabular}{|l|l|l|l|l|l|l|l|l|}" << std::endl;
    //std::cout << "        \\hline" << std::endl;
    //std::cout << "        \\ltwo flavor & year & \\mhnl & Cut & Eff.(2GeV) & Eff.(5GeV) & Eff.(8GeV) & Eff.(12GeV) & Eff.(Bkg)\\\\" << std::endl;
    //std::cout << "        \\hline" << std::endl;
    //std::cout << "        \\hline" << std::endl;
    //std::cout << "        \\multirow{6}{*}{\\Pe} & \\multirow{2}{*}{2016} & low mass & 0.98 & " + e_2016_5_stream.str() + "\\\\" << std::endl;
    //std::cout << "        & & high mass & 0.99 & " + e_2016_10_stream.str() + "\\\\\\cline{2-4}" << std::endl;
    //std::cout << "        & \\multirow{2}{*}{2017} & low mass & 0.97 & " + e_2017_5_stream.str() + "\\\\" << std::endl;
    //std::cout << "        & & high mass & 0.96 & " + e_2017_10_stream.str() + "\\\\\\cline{2-4}" << std::endl;
    //std::cout << "        & \\multirow{2}{*}{2018} & low mass & 0.98 & " + e_2018_5_stream.str() + "\\\\" << std::endl;
    //std::cout << "        & & high mass & 0.97 & " + e_2018_10_stream.str() + "\\\\" << std::endl;
    //std::cout << "        \\hline" << std::endl;
    //std::cout << "        \\multirow{6}{*}{\\PGm} & \\multirow{2}{*}{2016} & low mass & 0.999 & " + m_2016_5_stream.str() + "\\\\" << std::endl;
    //std::cout << "        & & high mass & 0.998 & " + m_2016_10_stream.str() + "\\\\\\cline{2-4}" << std::endl;
    //std::cout << "        & \\multirow{2}{*}{2017} & low mass & 0.996 & " + m_2017_5_stream.str() + "\\\\" << std::endl;
    //std::cout << "        & & high mass & 0.998 & " + m_2017_10_stream.str() + "\\\\\\cline{2-4}" << std::endl;
    //std::cout << "        & \\multirow{2}{*}{2018} & low mass & 0.997 & " + m_2018_5_stream.str() + "\\\\" << std::endl;
    //std::cout << "        & & high mass & 0.998 & " + m_2018_10_stream.str() + "\\\\" << std::endl;
    //std::cout << "        \\hline" << std::endl;
    //std::cout << "    \\end{tabular}" << std::endl;
    //std::cout << "\\end{table}" << std::endl;

    //
    //
    //PFNcut_effs["e_2016_5Bkg"] = effs["e_2016_5Bkg"][hists["e_2016_5Bkg"]->FindBin(PFNcuts["e_2016_5Bkg"])-1];
    //PFNcut_effs["e_2017_5Bkg"] = effs["e_2017_5Bkg"][hists["e_2017_5Bkg"]->FindBin(PFNcuts["e_2017_5Bkg"])-1];
    //PFNcut_effs["e_2018_5Bkg"] = effs["e_2018_5Bkg"][hists["e_2018_5Bkg"]->FindBin(PFNcuts["e_2018_5Bkg"])-1];
    //PFNcut_effs["m_2016_5Bkg"] = effs["m_2016_5Bkg"][hists["m_2016_5Bkg"]->FindBin(PFNcuts["m_2016_5Bkg"])-1];
    //PFNcut_effs["m_2017_5Bkg"] = effs["m_2017_5Bkg"][hists["m_2017_5Bkg"]->FindBin(PFNcuts["m_2017_5Bkg"])-1];
    //PFNcut_effs["m_2018_5Bkg"] = effs["m_2018_5Bkg"][hists["m_2018_5Bkg"]->FindBin(PFNcuts["m_2018_5Bkg"])-1];
    //PFNcut_effs["e_2016_10Bkg"] = effs["e_2016_10Bkg"][hists["e_2016_10Bkg"]->FindBin(PFNcuts["e_2016_10Bkg"])-1];
    //PFNcut_effs["e_2017_10Bkg"] = effs["e_2017_10Bkg"][hists["e_2017_10Bkg"]->FindBin(PFNcuts["e_2017_10Bkg"])-1];
    //PFNcut_effs["e_2018_10Bkg"] = effs["e_2018_10Bkg"][hists["e_2018_10Bkg"]->FindBin(PFNcuts["e_2018_10Bkg"])-1];
    //PFNcut_effs["m_2016_10Bkg"] = effs["m_2016_10Bkg"][hists["m_2016_10Bkg"]->FindBin(PFNcuts["m_2016_10Bkg"])-1];
    //PFNcut_effs["m_2017_10Bkg"] = effs["m_2017_10Bkg"][hists["m_2017_10Bkg"]->FindBin(PFNcuts["m_2017_10Bkg"])-1];
    //PFNcut_effs["m_2018_10Bkg"] = effs["m_2018_10Bkg"][hists["m_2018_10Bkg"]->FindBin(PFNcuts["m_2018_10Bkg"])-1];
    //
    //PFNcut_effs["e_2016_5Data"] = effs["e_2016_5Data"][hists["e_2016_5Data"]->FindBin(PFNcuts["e_2016_5Data"])-1];
    //PFNcut_effs["e_2017_5Data"] = effs["e_2017_5Data"][hists["e_2017_5Data"]->FindBin(PFNcuts["e_2017_5Data"])-1];
    //PFNcut_effs["e_2018_5Data"] = effs["e_2018_5Data"][hists["e_2018_5Data"]->FindBin(PFNcuts["e_2018_5Data"])-1];
    //PFNcut_effs["m_2016_5Data"] = effs["m_2016_5Data"][hists["m_2016_5Data"]->FindBin(PFNcuts["m_2016_5Data"])-1];
    //PFNcut_effs["m_2017_5Data"] = effs["m_2017_5Data"][hists["m_2017_5Data"]->FindBin(PFNcuts["m_2017_5Data"])-1];
    //PFNcut_effs["m_2018_5Data"] = effs["m_2018_5Data"][hists["m_2018_5Data"]->FindBin(PFNcuts["m_2018_5Data"])-1];
    //PFNcut_effs["e_2016_10Data"] = effs["e_2016_10Data"][hists["e_2016_10Data"]->FindBin(PFNcuts["e_2016_10Data"])-1];
    //PFNcut_effs["e_2017_10Data"] = effs["e_2017_10Data"][hists["e_2017_10Data"]->FindBin(PFNcuts["e_2017_10Data"])-1];
    //PFNcut_effs["e_2018_10Data"] = effs["e_2018_10Data"][hists["e_2018_10Data"]->FindBin(PFNcuts["e_2018_10Data"])-1];
    //PFNcut_effs["m_2016_10Data"] = effs["m_2016_10Data"][hists["m_2016_10Data"]->FindBin(PFNcuts["m_2016_10Data"])-1];
    //PFNcut_effs["m_2017_10Data"] = effs["m_2017_10Data"][hists["m_2017_10Data"]->FindBin(PFNcuts["m_2017_10Data"])-1];
    //PFNcut_effs["m_2018_10Data"] = effs["m_2018_10Data"][hists["m_2018_10Data"]->FindBin(PFNcuts["m_2018_10Data"])-1];
    //

    //// Make the ROC curves
    //setTDRStyle();
    //gROOT->ForceStyle();

    //TCanvas* c = new TCanvas("c","",700,700);
    //c->cd();

    //// Make the pad that will contain the plot
    //TPad* pad  = new TPad("pad", "", 0., 0., 1., 1.);
    //pad->Draw();
    //pad->cd();

    ////TLegend legend = get_legend(0.18, 0.61, 0.65, 0.93, 1);
    //TLegend legend = get_legend(0.57, 0.15, 1, 0.075*6, 1);


    //std::vector<std::vector<int>> rgb = {{46, 114, 204}, {239, 32, 29}, {29, 182, 0}, {86, 14, 118}, {232, 164, 0}, {86, 22, 67}, {247, 135, 100}, {47, 41, 35}};
    //std::vector<int> colors;
    //for(unsigned i = 0; i < rgb.size(); i++){
    //    colors.push_back(TColor::GetColor(rgb[i][0], rgb[i][1], rgb[i][2]));
    //}


    //for(const TString& year : {"2016", "2017", "2018"}){
    //    for(const TString& fl : {"e", "m"}){
    //        // Get margins and make the CMS and lumi basic latex to print on top of the figure
    //        CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad, year == "2016", year == "2017", year == "2018", false);
    //        CMSandLumi->add_flavor("_"+fl+fl);
    //        legend.Clear();
    //        legend.SetHeader("HNL Mass: AUC");

    //        TMultiGraph* multigraph = new TMultiGraph();
    //        multigraph->SetTitle((TString)";Bkg Eff.;Signal Eff.");
    //        TGraph* roc_2GeV = get_roc(effs[fl+"_"+year+"_2GeV"], effs[fl+"_"+year+"_5Bkg"]);
    //        roc_2GeV->SetLineColor(colors[0]);
    //        multigraph->Add(roc_2GeV);
    //        std::ostringstream auc_2GeV;
    //        auc_2GeV << std::setprecision(4) << computeAUC(roc_2GeV);
    //        TString leg_2GeV = "M-2GeV: " + auc_2GeV.str();
    //        legend.AddEntry(roc_2GeV, leg_2GeV, "l");
    //        
    //        TGraph* roc_5GeV = get_roc(effs[fl+"_"+year+"_5GeV"], effs[fl+"_"+year+"_5Bkg"]);
    //        roc_5GeV->SetLineColor(colors[1]);
    //        multigraph->Add(roc_5GeV);
    //        std::ostringstream auc_5GeV;
    //        auc_5GeV << std::setprecision(4) << computeAUC(roc_5GeV);
    //        TString leg_5GeV = "M-5GeV: " + auc_5GeV.str();
    //        legend.AddEntry(roc_5GeV, leg_5GeV, "l");
    //        
    //        TGraph* roc_8GeV = get_roc(effs[fl+"_"+year+"_8GeV"], effs[fl+"_"+year+"_10Bkg"]);
    //        roc_8GeV->SetLineColor(colors[2]);
    //        multigraph->Add(roc_8GeV);
    //        std::ostringstream auc_8GeV;
    //        auc_8GeV << std::setprecision(4) << computeAUC(roc_8GeV);
    //        TString leg_8GeV = "M-8GeV: " + auc_8GeV.str();
    //        legend.AddEntry(roc_8GeV, leg_8GeV, "l");
    //        
    //        TGraph* roc_12GeV = get_roc(effs[fl+"_"+year+"_12GeV"], effs[fl+"_"+year+"_10Bkg"]);
    //        roc_12GeV->SetLineColor(colors[3]);
    //        multigraph->Add(roc_12GeV);
    //        std::ostringstream auc_12GeV;
    //        auc_12GeV << std::setprecision(4) << computeAUC(roc_12GeV);
    //        TString leg_12GeV = "M-12GeV: " + auc_12GeV.str();
    //        legend.AddEntry(roc_12GeV, leg_12GeV, "l");

    //        double sig_eff[4], bkg_eff[4];
    //        sig_eff[0] = PFNcut_effs[fl+"_"+year+"_2GeV"];
    //        sig_eff[1] = PFNcut_effs[fl+"_"+year+"_5GeV"];
    //        sig_eff[2] = PFNcut_effs[fl+"_"+year+"_8GeV"];
    //        sig_eff[3] = PFNcut_effs[fl+"_"+year+"_12GeV"];
    //        bkg_eff[0] = PFNcut_effs[fl+"_"+year+"_5Bkg"];
    //        bkg_eff[1] = PFNcut_effs[fl+"_"+year+"_5Bkg"];
    //        bkg_eff[2] = PFNcut_effs[fl+"_"+year+"_10Bkg"];
    //        bkg_eff[3] = PFNcut_effs[fl+"_"+year+"_10Bkg"];
    //        TGraph* workingpoints = new TGraph(4, bkg_eff, sig_eff);
    //        workingpoints->SetMarkerStyle(29);
    //        workingpoints->SetMarkerSize(3);
    //        legend.AddEntry(workingpoints, "Working Points", "p");
    //        
    //        pad->SetLogx(1);
    //        multigraph->Draw("AL");
    //        workingpoints->Draw("P same");


    //        multigraph->GetXaxis()->SetLimits(5e-5, 0.2);
    //        multigraph->SetMinimum(0.4);
    //        multigraph->SetMaximum(1.02);

    //        legend.Draw("same");
    //        CMSandLumi->Draw();

    //        pad->Modified();
    //        c->Print("/user/bvermass/public_html/2l2q_analysis/plots/roccurves/ROC_"+fl+"_"+year+".png");
    //    }
    //}
    //std::map<TString, double> PFNcut_effs_0p9;
    //PFNcut_effs_0p9["e_2016_2GeV"] = effs["e_2016_2GeV"][hists["e_2016_2GeV"]->FindBin(PFNcuts_0p9["e_2016_2GeV"])-1]    - effs["e_2016_2GeV"][hists["e_2016_2GeV"]->FindBin(PFNcuts["e_2016_2GeV"])-1];
    //PFNcut_effs_0p9["e_2016_5GeV"] = effs["e_2016_5GeV"][hists["e_2016_5GeV"]->FindBin(PFNcuts_0p9["e_2016_5GeV"])-1]    - effs["e_2016_5GeV"][hists["e_2016_5GeV"]->FindBin(PFNcuts["e_2016_5GeV"])-1];
    //PFNcut_effs_0p9["e_2016_8GeV"] = effs["e_2016_8GeV"][hists["e_2016_8GeV"]->FindBin(PFNcuts_0p9["e_2016_8GeV"])-1]    - effs["e_2016_8GeV"][hists["e_2016_8GeV"]->FindBin(PFNcuts["e_2016_8GeV"])-1];
    //PFNcut_effs_0p9["e_2016_12GeV"] = effs["e_2016_12GeV"][hists["e_2016_12GeV"]->FindBin(PFNcuts_0p9["e_2016_12GeV"])-1]-  effs["e_2016_12GeV"][hists["e_2016_12GeV"]->FindBin(PFNcuts["e_2016_12GeV"])-1];
    //PFNcut_effs_0p9["m_2016_2GeV"] = effs["m_2016_2GeV"][hists["m_2016_2GeV"]->FindBin(PFNcuts_0p9["m_2016_2GeV"])-1]    - effs["m_2016_2GeV"][hists["m_2016_2GeV"]->FindBin(PFNcuts["m_2016_2GeV"])-1];
    //PFNcut_effs_0p9["m_2016_5GeV"] = effs["m_2016_5GeV"][hists["m_2016_5GeV"]->FindBin(PFNcuts_0p9["m_2016_5GeV"])-1]    - effs["m_2016_5GeV"][hists["m_2016_5GeV"]->FindBin(PFNcuts["m_2016_5GeV"])-1];
    //PFNcut_effs_0p9["m_2016_8GeV"] = effs["m_2016_8GeV"][hists["m_2016_8GeV"]->FindBin(PFNcuts_0p9["m_2016_8GeV"])-1]    - effs["m_2016_8GeV"][hists["m_2016_8GeV"]->FindBin(PFNcuts["m_2016_8GeV"])-1];
    //PFNcut_effs_0p9["m_2016_12GeV"] = effs["m_2016_12GeV"][hists["m_2016_12GeV"]->FindBin(PFNcuts_0p9["m_2016_12GeV"])-1]-  effs["m_2016_12GeV"][hists["m_2016_12GeV"]->FindBin(PFNcuts["m_2016_12GeV"])-1];
    //PFNcut_effs_0p9["e_2017_2GeV"] = effs["e_2017_2GeV"][hists["e_2017_2GeV"]->FindBin(PFNcuts_0p9["e_2017_2GeV"])-1]    - effs["e_2017_2GeV"][hists["e_2017_2GeV"]->FindBin(PFNcuts["e_2017_2GeV"])-1];
    //PFNcut_effs_0p9["e_2017_5GeV"] = effs["e_2017_5GeV"][hists["e_2017_5GeV"]->FindBin(PFNcuts_0p9["e_2017_5GeV"])-1]    - effs["e_2017_5GeV"][hists["e_2017_5GeV"]->FindBin(PFNcuts["e_2017_5GeV"])-1];
    //PFNcut_effs_0p9["e_2017_8GeV"] = effs["e_2017_8GeV"][hists["e_2017_8GeV"]->FindBin(PFNcuts_0p9["e_2017_8GeV"])-1]    - effs["e_2017_8GeV"][hists["e_2017_8GeV"]->FindBin(PFNcuts["e_2017_8GeV"])-1];
    //PFNcut_effs_0p9["e_2017_12GeV"] = effs["e_2017_12GeV"][hists["e_2017_12GeV"]->FindBin(PFNcuts_0p9["e_2017_12GeV"])-1]-  effs["e_2017_12GeV"][hists["e_2017_12GeV"]->FindBin(PFNcuts["e_2017_12GeV"])-1];
    //PFNcut_effs_0p9["m_2017_2GeV"] = effs["m_2017_2GeV"][hists["m_2017_2GeV"]->FindBin(PFNcuts_0p9["m_2017_2GeV"])-1]    - effs["m_2017_2GeV"][hists["m_2017_2GeV"]->FindBin(PFNcuts["m_2017_2GeV"])-1];
    //PFNcut_effs_0p9["m_2017_5GeV"] = effs["m_2017_5GeV"][hists["m_2017_5GeV"]->FindBin(PFNcuts_0p9["m_2017_5GeV"])-1]    - effs["m_2017_5GeV"][hists["m_2017_5GeV"]->FindBin(PFNcuts["m_2017_5GeV"])-1];
    //PFNcut_effs_0p9["m_2017_8GeV"] = effs["m_2017_8GeV"][hists["m_2017_8GeV"]->FindBin(PFNcuts_0p9["m_2017_8GeV"])-1]    - effs["m_2017_8GeV"][hists["m_2017_8GeV"]->FindBin(PFNcuts["m_2017_8GeV"])-1];
    //PFNcut_effs_0p9["m_2017_12GeV"] = effs["m_2017_12GeV"][hists["m_2017_12GeV"]->FindBin(PFNcuts_0p9["m_2017_12GeV"])-1]-  effs["m_2017_12GeV"][hists["m_2017_12GeV"]->FindBin(PFNcuts["m_2017_12GeV"])-1];
    //PFNcut_effs_0p9["e_2018_2GeV"] = effs["e_2018_2GeV"][hists["e_2018_2GeV"]->FindBin(PFNcuts_0p9["e_2018_2GeV"])-1]    - effs["e_2018_2GeV"][hists["e_2018_2GeV"]->FindBin(PFNcuts["e_2018_2GeV"])-1];
    //PFNcut_effs_0p9["e_2018_5GeV"] = effs["e_2018_5GeV"][hists["e_2018_5GeV"]->FindBin(PFNcuts_0p9["e_2018_5GeV"])-1]    - effs["e_2018_5GeV"][hists["e_2018_5GeV"]->FindBin(PFNcuts["e_2018_5GeV"])-1];
    //PFNcut_effs_0p9["e_2018_8GeV"] = effs["e_2018_8GeV"][hists["e_2018_8GeV"]->FindBin(PFNcuts_0p9["e_2018_8GeV"])-1]    - effs["e_2018_8GeV"][hists["e_2018_8GeV"]->FindBin(PFNcuts["e_2018_8GeV"])-1];
    //PFNcut_effs_0p9["e_2018_12GeV"] = effs["e_2018_12GeV"][hists["e_2018_12GeV"]->FindBin(PFNcuts_0p9["e_2018_12GeV"])-1]-  effs["e_2018_12GeV"][hists["e_2018_12GeV"]->FindBin(PFNcuts["e_2018_12GeV"])-1];
    //PFNcut_effs_0p9["m_2018_2GeV"] = effs["m_2018_2GeV"][hists["m_2018_2GeV"]->FindBin(PFNcuts_0p9["m_2018_2GeV"])-1]    - effs["m_2018_2GeV"][hists["m_2018_2GeV"]->FindBin(PFNcuts["m_2018_2GeV"])-1];
    //PFNcut_effs_0p9["m_2018_5GeV"] = effs["m_2018_5GeV"][hists["m_2018_5GeV"]->FindBin(PFNcuts_0p9["m_2018_5GeV"])-1]    - effs["m_2018_5GeV"][hists["m_2018_5GeV"]->FindBin(PFNcuts["m_2018_5GeV"])-1];
    //PFNcut_effs_0p9["m_2018_8GeV"] = effs["m_2018_8GeV"][hists["m_2018_8GeV"]->FindBin(PFNcuts_0p9["m_2018_8GeV"])-1]    - effs["m_2018_8GeV"][hists["m_2018_8GeV"]->FindBin(PFNcuts["m_2018_8GeV"])-1];
    //PFNcut_effs_0p9["m_2018_12GeV"] = effs["m_2018_12GeV"][hists["m_2018_12GeV"]->FindBin(PFNcuts_0p9["m_2018_12GeV"])-1]-  effs["m_2018_12GeV"][hists["m_2018_12GeV"]->FindBin(PFNcuts["m_2018_12GeV"])-1];

    //PFNcut_effs_0p9["e_2016_5Bkg"] = effs["e_2016_5Bkg"][hists["e_2016_5Bkg"]->FindBin(PFNcuts_0p9["e_2016_5Bkg"])-1]    - effs["e_2016_5Bkg"][hists["e_2016_5Bkg"]->FindBin(PFNcuts["e_2016_5Bkg"])-1];
    //PFNcut_effs_0p9["e_2017_5Bkg"] = effs["e_2017_5Bkg"][hists["e_2017_5Bkg"]->FindBin(PFNcuts_0p9["e_2017_5Bkg"])-1]    - effs["e_2017_5Bkg"][hists["e_2017_5Bkg"]->FindBin(PFNcuts["e_2017_5Bkg"])-1];
    //PFNcut_effs_0p9["e_2018_5Bkg"] = effs["e_2018_5Bkg"][hists["e_2018_5Bkg"]->FindBin(PFNcuts_0p9["e_2018_5Bkg"])-1]    - effs["e_2018_5Bkg"][hists["e_2018_5Bkg"]->FindBin(PFNcuts["e_2018_5Bkg"])-1];
    //PFNcut_effs_0p9["m_2016_5Bkg"] = effs["m_2016_5Bkg"][hists["m_2016_5Bkg"]->FindBin(PFNcuts_0p9["m_2016_5Bkg"])-1]    - effs["m_2016_5Bkg"][hists["m_2016_5Bkg"]->FindBin(PFNcuts["m_2016_5Bkg"])-1];
    //PFNcut_effs_0p9["m_2017_5Bkg"] = effs["m_2017_5Bkg"][hists["m_2017_5Bkg"]->FindBin(PFNcuts_0p9["m_2017_5Bkg"])-1]    - effs["m_2017_5Bkg"][hists["m_2017_5Bkg"]->FindBin(PFNcuts["m_2017_5Bkg"])-1];
    //PFNcut_effs_0p9["m_2018_5Bkg"] = effs["m_2018_5Bkg"][hists["m_2018_5Bkg"]->FindBin(PFNcuts_0p9["m_2018_5Bkg"])-1]    - effs["m_2018_5Bkg"][hists["m_2018_5Bkg"]->FindBin(PFNcuts["m_2018_5Bkg"])-1];
    //PFNcut_effs_0p9["e_2016_10Bkg"] = effs["e_2016_10Bkg"][hists["e_2016_10Bkg"]->FindBin(PFNcuts_0p9["e_2016_10Bkg"])-1]-  effs["e_2016_10Bkg"][hists["e_2016_10Bkg"]->FindBin(PFNcuts["e_2016_10Bkg"])-1];
    //PFNcut_effs_0p9["e_2017_10Bkg"] = effs["e_2017_10Bkg"][hists["e_2017_10Bkg"]->FindBin(PFNcuts_0p9["e_2017_10Bkg"])-1]-  effs["e_2017_10Bkg"][hists["e_2017_10Bkg"]->FindBin(PFNcuts["e_2017_10Bkg"])-1];
    //PFNcut_effs_0p9["e_2018_10Bkg"] = effs["e_2018_10Bkg"][hists["e_2018_10Bkg"]->FindBin(PFNcuts_0p9["e_2018_10Bkg"])-1]-  effs["e_2018_10Bkg"][hists["e_2018_10Bkg"]->FindBin(PFNcuts["e_2018_10Bkg"])-1];
    //PFNcut_effs_0p9["m_2016_10Bkg"] = effs["m_2016_10Bkg"][hists["m_2016_10Bkg"]->FindBin(PFNcuts_0p9["m_2016_10Bkg"])-1]-  effs["m_2016_10Bkg"][hists["m_2016_10Bkg"]->FindBin(PFNcuts["m_2016_10Bkg"])-1];
    //PFNcut_effs_0p9["m_2017_10Bkg"] = effs["m_2017_10Bkg"][hists["m_2017_10Bkg"]->FindBin(PFNcuts_0p9["m_2017_10Bkg"])-1]-  effs["m_2017_10Bkg"][hists["m_2017_10Bkg"]->FindBin(PFNcuts["m_2017_10Bkg"])-1];
    //PFNcut_effs_0p9["m_2018_10Bkg"] = effs["m_2018_10Bkg"][hists["m_2018_10Bkg"]->FindBin(PFNcuts_0p9["m_2018_10Bkg"])-1]-  effs["m_2018_10Bkg"][hists["m_2018_10Bkg"]->FindBin(PFNcuts["m_2018_10Bkg"])-1];
    //
    //std::ostringstream e_2016_5_stream_0p9, e_2016_10_stream_0p9, e_2017_5_stream_0p9, e_2017_10_stream_0p9, e_2018_5_stream_0p9, e_2018_10_stream_0p9, m_2016_5_stream_0p9, m_2016_10_stream_0p9, m_2017_5_stream_0p9, m_2017_10_stream_0p9, m_2018_5_stream_0p9, m_2018_10_stream_0p9;
    //e_2016_5_stream_0p9 << std::setprecision(2) << 100.*PFNcut_effs_0p9["e_2016_2GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2016_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs_0p9["e_2016_5Bkg"] << "\\%";
    //e_2016_10_stream_0p9 << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs_0p9["e_2016_8GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2016_12GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2016_10Bkg"] << "\\%";
    //m_2016_5_stream_0p9 << std::setprecision(2) << 100.*PFNcut_effs_0p9["m_2016_2GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2016_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs_0p9["m_2016_5Bkg"] << "\\%";
    //m_2016_10_stream_0p9 << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs_0p9["m_2016_8GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2016_12GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2016_10Bkg"] << "\\%";
    //e_2017_5_stream_0p9 << std::setprecision(2) << 100.*PFNcut_effs_0p9["e_2017_2GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2017_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs_0p9["e_2017_5Bkg"] << "\\%";
    //e_2017_10_stream_0p9 << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs_0p9["e_2017_8GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2017_12GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2017_10Bkg"] << "\\%";
    //m_2017_5_stream_0p9 << std::setprecision(2) << 100.*PFNcut_effs_0p9["m_2017_2GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2017_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs_0p9["m_2017_5Bkg"] << "\\%";
    //m_2017_10_stream_0p9 << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs_0p9["m_2017_8GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2017_12GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2017_10Bkg"] << "\\%";
    //e_2018_5_stream_0p9 << std::setprecision(2) << 100.*PFNcut_effs_0p9["e_2018_2GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2018_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs_0p9["e_2018_5Bkg"] << "\\%";
    //e_2018_10_stream_0p9 << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs_0p9["e_2018_8GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2018_12GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["e_2018_10Bkg"] << "\\%";
    //m_2018_5_stream_0p9 << std::setprecision(2) << 100.*PFNcut_effs_0p9["m_2018_2GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2018_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs_0p9["m_2018_5Bkg"] << "\\%";
    //m_2018_10_stream_0p9 << std::setprecision(2) << " - & - & " << 100.*PFNcut_effs_0p9["m_2018_8GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2018_12GeV"] << "\\% & " << 100.*PFNcut_effs_0p9["m_2018_10Bkg"] << "\\%";

    //std::cout << "\\begin{table}" << std::endl;
    //std::cout << "    \\centering" << std::endl;
    //std::cout << "    \\caption{PFN cuts for defining the normal and inverted region.}" << std::endl;
    //std::cout << "    \\label{tab:PFNcuts}" << std::endl;
    //std::cout << "    \\begin{tabular}{|l|l|l|l|l|l|l|l|l|}" << std::endl;
    //std::cout << "        \\hline" << std::endl;
    //std::cout << "        \\ltwo flavor & year & \\mhnl & Cut & Eff.(2GeV) & Eff.(5GeV) & Eff.(8GeV) & Eff.(12GeV) & Eff.(Bkg)\\\\" << std::endl;
    //std::cout << "        \\hline" << std::endl;
    //std::cout << "        \\hline" << std::endl;
    //std::cout << "        \\multirow{6}{*}{\\Pe} & \\multirow{2}{*}{2016} & low mass & 0.98 & " + e_2016_5_stream_0p9.str() + "\\\\" << std::endl;
    //std::cout << "        & & high mass & 0.99 & " + e_2016_10_stream_0p9.str() + "\\\\\\cline{2-4}" << std::endl;
    //std::cout << "        & \\multirow{2}{*}{2017} & low mass & 0.97 & " + e_2017_5_stream_0p9.str() + "\\\\" << std::endl;
    //std::cout << "        & & high mass & 0.96 & " + e_2017_10_stream_0p9.str() + "\\\\\\cline{2-4}" << std::endl;
    //std::cout << "        & \\multirow{2}{*}{2018} & low mass & 0.98 & " + e_2018_5_stream_0p9.str() + "\\\\" << std::endl;
    //std::cout << "        & & high mass & 0.97 & " + e_2018_10_stream_0p9.str() + "\\\\" << std::endl;
    //std::cout << "        \\hline" << std::endl;
    //std::cout << "        \\multirow{6}{*}{\\PGm} & \\multirow{2}{*}{2016} & low mass & 0.999 & " + m_2016_5_stream_0p9.str() + "\\\\" << std::endl;
    //std::cout << "        & & high mass & 0.998 & " + m_2016_10_stream_0p9.str() + "\\\\\\cline{2-4}" << std::endl;
    //std::cout << "        & \\multirow{2}{*}{2017} & low mass & 0.996 & " + m_2017_5_stream_0p9.str() + "\\\\" << std::endl;
    //std::cout << "        & & high mass & 0.998 & " + m_2017_10_stream_0p9.str() + "\\\\\\cline{2-4}" << std::endl;
    //std::cout << "        & \\multirow{2}{*}{2018} & low mass & 0.997 & " + m_2018_5_stream_0p9.str() + "\\\\" << std::endl;
    //std::cout << "        & & high mass & 0.998 & " + m_2018_10_stream_0p9.str() + "\\\\" << std::endl;
    //std::cout << "        \\hline" << std::endl;
    //std::cout << "    \\end{tabular}" << std::endl;
    //std::cout << "\\end{table}" << std::endl;
    
    
    
    //
    // 2BJet efficiency comparison between data and MC
    //
    
    hists["e_2016_5Bkg_2BJets"] = (TH1F*)files["e_2016_5Bkg"]->Get("_ee_2BJets_M-5_V2-2e-06_PFN_ROC");
    hists["e_2017_5Bkg_2BJets"] = (TH1F*)files["e_2017_5Bkg"]->Get("_ee_2BJets_M-5_V2-2e-06_PFN_ROC");
    hists["e_2018_5Bkg_2BJets"] = (TH1F*)files["e_2018_5Bkg"]->Get("_ee_2BJets_M-5_V2-2e-06_PFN_ROC");
    hists["m_2016_5Bkg_2BJets"] = (TH1F*)files["m_2016_5Bkg"]->Get("_mm_2BJets_M-5_V2-2e-06_PFN_ROC");
    hists["m_2017_5Bkg_2BJets"] = (TH1F*)files["m_2017_5Bkg"]->Get("_mm_2BJets_M-5_V2-2e-06_PFN_ROC");
    hists["m_2018_5Bkg_2BJets"] = (TH1F*)files["m_2018_5Bkg"]->Get("_mm_2BJets_M-5_V2-2e-06_PFN_ROC");
    hists["e_2016_10Bkg_2BJets"] = (TH1F*)files["e_2016_10Bkg"]->Get("_ee_2BJets_M-10_V2-2e-06_PFN_ROC");
    hists["e_2017_10Bkg_2BJets"] = (TH1F*)files["e_2017_10Bkg"]->Get("_ee_2BJets_M-10_V2-2e-06_PFN_ROC");
    hists["e_2018_10Bkg_2BJets"] = (TH1F*)files["e_2018_10Bkg"]->Get("_ee_2BJets_M-10_V2-2e-06_PFN_ROC");
    hists["m_2016_10Bkg_2BJets"] = (TH1F*)files["m_2016_10Bkg"]->Get("_mm_2BJets_M-10_V2-2e-06_PFN_ROC");
    hists["m_2017_10Bkg_2BJets"] = (TH1F*)files["m_2017_10Bkg"]->Get("_mm_2BJets_M-10_V2-2e-06_PFN_ROC");
    hists["m_2018_10Bkg_2BJets"] = (TH1F*)files["m_2018_10Bkg"]->Get("_mm_2BJets_M-10_V2-2e-06_PFN_ROC");

    hists["e_2016_5Data_2BJets"] = (TH1F*)files["e_2016_5Data"]->Get("_ee_2BJets_M-5_V2-2e-06_PFN_ROC");
    hists["e_2017_5Data_2BJets"] = (TH1F*)files["e_2017_5Data"]->Get("_ee_2BJets_M-5_V2-2e-06_PFN_ROC");
    hists["e_2018_5Data_2BJets"] = (TH1F*)files["e_2018_5Data"]->Get("_ee_2BJets_M-5_V2-2e-06_PFN_ROC");
    hists["m_2016_5Data_2BJets"] = (TH1F*)files["m_2016_5Data"]->Get("_mm_2BJets_M-5_V2-2e-06_PFN_ROC");
    hists["m_2017_5Data_2BJets"] = (TH1F*)files["m_2017_5Data"]->Get("_mm_2BJets_M-5_V2-2e-06_PFN_ROC");
    hists["m_2018_5Data_2BJets"] = (TH1F*)files["m_2018_5Data"]->Get("_mm_2BJets_M-5_V2-2e-06_PFN_ROC");
    hists["e_2016_10Data_2BJets"] = (TH1F*)files["e_2016_10Data"]->Get("_ee_2BJets_M-10_V2-2e-06_PFN_ROC");
    hists["e_2017_10Data_2BJets"] = (TH1F*)files["e_2017_10Data"]->Get("_ee_2BJets_M-10_V2-2e-06_PFN_ROC");
    hists["e_2018_10Data_2BJets"] = (TH1F*)files["e_2018_10Data"]->Get("_ee_2BJets_M-10_V2-2e-06_PFN_ROC");
    hists["m_2016_10Data_2BJets"] = (TH1F*)files["m_2016_10Data"]->Get("_mm_2BJets_M-10_V2-2e-06_PFN_ROC");
    hists["m_2017_10Data_2BJets"] = (TH1F*)files["m_2017_10Data"]->Get("_mm_2BJets_M-10_V2-2e-06_PFN_ROC");
    hists["m_2018_10Data_2BJets"] = (TH1F*)files["m_2018_10Data"]->Get("_mm_2BJets_M-10_V2-2e-06_PFN_ROC");

    //hists["e_2016_5Bkg_2BJets"] = (TH1F*)files["e_2016_5Bkg"]->Get("_ee_2BJets"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["e_2017_5Bkg_2BJets"] = (TH1F*)files["e_2017_5Bkg"]->Get("_ee_2BJets"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["e_2018_5Bkg_2BJets"] = (TH1F*)files["e_2018_5Bkg"]->Get("_ee_2BJets"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["m_2016_5Bkg_2BJets"] = (TH1F*)files["m_2016_5Bkg"]->Get("_mm_2BJets"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["m_2017_5Bkg_2BJets"] = (TH1F*)files["m_2017_5Bkg"]->Get("_mm_2BJets"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["m_2018_5Bkg_2BJets"] = (TH1F*)files["m_2018_5Bkg"]->Get("_mm_2BJets"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["e_2016_10Bkg_2BJets"] = (TH1F*)files["e_2016_10Bkg"]->Get("_ee_2BJets"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    //hists["e_2017_10Bkg_2BJets"] = (TH1F*)files["e_2017_10Bkg"]->Get("_ee_2BJets"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    //hists["e_2018_10Bkg_2BJets"] = (TH1F*)files["e_2018_10Bkg"]->Get("_ee_2BJets"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    //hists["m_2016_10Bkg_2BJets"] = (TH1F*)files["m_2016_10Bkg"]->Get("_mm_2BJets"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");
    //hists["m_2017_10Bkg_2BJets"] = (TH1F*)files["m_2017_10Bkg"]->Get("_mm_2BJets"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");
    //hists["m_2018_10Bkg_2BJets"] = (TH1F*)files["m_2018_10Bkg"]->Get("_mm_2BJets"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");

    //hists["e_2016_5Data_2BJets"] = (TH1F*)files["e_2016_5Data"]->Get("_ee_2BJets"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["e_2017_5Data_2BJets"] = (TH1F*)files["e_2017_5Data"]->Get("_ee_2BJets"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["e_2018_5Data_2BJets"] = (TH1F*)files["e_2018_5Data"]->Get("_ee_2BJets"+get_MV2name(5, get_favorite_V2(5,"e"))+"_PFN_ROC");
    //hists["m_2016_5Data_2BJets"] = (TH1F*)files["m_2016_5Data"]->Get("_mm_2BJets"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["m_2017_5Data_2BJets"] = (TH1F*)files["m_2017_5Data"]->Get("_mm_2BJets"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["m_2018_5Data_2BJets"] = (TH1F*)files["m_2018_5Data"]->Get("_mm_2BJets"+get_MV2name(5, get_favorite_V2(5,"mu"))+"_PFN_ROC");
    //hists["e_2016_10Data_2BJets"] = (TH1F*)files["e_2016_10Data"]->Get("_ee_2BJets"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    //hists["e_2017_10Data_2BJets"] = (TH1F*)files["e_2017_10Data"]->Get("_ee_2BJets"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    //hists["e_2018_10Data_2BJets"] = (TH1F*)files["e_2018_10Data"]->Get("_ee_2BJets"+get_MV2name(10, get_favorite_V2(10,"e"))+"_PFN_ROC");
    //hists["m_2016_10Data_2BJets"] = (TH1F*)files["m_2016_10Data"]->Get("_mm_2BJets"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");
    //hists["m_2017_10Data_2BJets"] = (TH1F*)files["m_2017_10Data"]->Get("_mm_2BJets"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");
    //hists["m_2018_10Data_2BJets"] = (TH1F*)files["m_2018_10Data"]->Get("_mm_2BJets"+get_MV2name(10, get_favorite_V2(10,"mu"))+"_PFN_ROC");
    
    effs["e_2016_5Bkg_2BJets"] = computeEfficiencyForROC(hists["e_2016_5Bkg_2BJets"]);
    effs["e_2017_5Bkg_2BJets"] = computeEfficiencyForROC(hists["e_2017_5Bkg_2BJets"]);
    effs["e_2018_5Bkg_2BJets"] = computeEfficiencyForROC(hists["e_2018_5Bkg_2BJets"]);
    effs["m_2016_5Bkg_2BJets"] = computeEfficiencyForROC(hists["m_2016_5Bkg_2BJets"]);
    effs["m_2017_5Bkg_2BJets"] = computeEfficiencyForROC(hists["m_2017_5Bkg_2BJets"]);
    effs["m_2018_5Bkg_2BJets"] = computeEfficiencyForROC(hists["m_2018_5Bkg_2BJets"]);
    effs["e_2016_10Bkg_2BJets"] = computeEfficiencyForROC(hists["e_2016_10Bkg_2BJets"]);
    effs["e_2017_10Bkg_2BJets"] = computeEfficiencyForROC(hists["e_2017_10Bkg_2BJets"]);
    effs["e_2018_10Bkg_2BJets"] = computeEfficiencyForROC(hists["e_2018_10Bkg_2BJets"]);
    effs["m_2016_10Bkg_2BJets"] = computeEfficiencyForROC(hists["m_2016_10Bkg_2BJets"]);
    effs["m_2017_10Bkg_2BJets"] = computeEfficiencyForROC(hists["m_2017_10Bkg_2BJets"]);
    effs["m_2018_10Bkg_2BJets"] = computeEfficiencyForROC(hists["m_2018_10Bkg_2BJets"]);
    
    effs["e_2016_5Data_2BJets"] = computeEfficiencyForROC(hists["e_2016_5Data_2BJets"]);
    effs["e_2017_5Data_2BJets"] = computeEfficiencyForROC(hists["e_2017_5Data_2BJets"]);
    effs["e_2018_5Data_2BJets"] = computeEfficiencyForROC(hists["e_2018_5Data_2BJets"]);
    effs["m_2016_5Data_2BJets"] = computeEfficiencyForROC(hists["m_2016_5Data_2BJets"]);
    effs["m_2017_5Data_2BJets"] = computeEfficiencyForROC(hists["m_2017_5Data_2BJets"]);
    effs["m_2018_5Data_2BJets"] = computeEfficiencyForROC(hists["m_2018_5Data_2BJets"]);
    effs["e_2016_10Data_2BJets"] = computeEfficiencyForROC(hists["e_2016_10Data_2BJets"]);
    effs["e_2017_10Data_2BJets"] = computeEfficiencyForROC(hists["e_2017_10Data_2BJets"]);
    effs["e_2018_10Data_2BJets"] = computeEfficiencyForROC(hists["e_2018_10Data_2BJets"]);
    effs["m_2016_10Data_2BJets"] = computeEfficiencyForROC(hists["m_2016_10Data_2BJets"]);
    effs["m_2017_10Data_2BJets"] = computeEfficiencyForROC(hists["m_2017_10Data_2BJets"]);
    effs["m_2018_10Data_2BJets"] = computeEfficiencyForROC(hists["m_2018_10Data_2BJets"]);
    
    
    PFNcut_effs["e_2016_5Bkg_2BJets"] = effs["e_2016_5Bkg_2BJets"][hists["e_2016_5Bkg_2BJets"]->FindBin(PFNcuts_0p9["e_2016_5Bkg"])-1];
    PFNcut_effs["e_2017_5Bkg_2BJets"] = effs["e_2017_5Bkg_2BJets"][hists["e_2017_5Bkg_2BJets"]->FindBin(PFNcuts_0p9["e_2017_5Bkg"])-1];
    PFNcut_effs["e_2018_5Bkg_2BJets"] = effs["e_2018_5Bkg_2BJets"][hists["e_2018_5Bkg_2BJets"]->FindBin(PFNcuts_0p9["e_2018_5Bkg"])-1];
    PFNcut_effs["m_2016_5Bkg_2BJets"] = effs["m_2016_5Bkg_2BJets"][hists["m_2016_5Bkg_2BJets"]->FindBin(PFNcuts_0p9["m_2016_5Bkg"])-1];
    PFNcut_effs["m_2017_5Bkg_2BJets"] = effs["m_2017_5Bkg_2BJets"][hists["m_2017_5Bkg_2BJets"]->FindBin(PFNcuts_0p9["m_2017_5Bkg"])-1];
    PFNcut_effs["m_2018_5Bkg_2BJets"] = effs["m_2018_5Bkg_2BJets"][hists["m_2018_5Bkg_2BJets"]->FindBin(PFNcuts_0p9["m_2018_5Bkg"])-1];
    PFNcut_effs["e_2016_10Bkg_2BJets"] = effs["e_2016_10Bkg_2BJets"][hists["e_2016_10Bkg_2BJets"]->FindBin(PFNcuts_0p9["e_2016_10Bkg"])-1];
    PFNcut_effs["e_2017_10Bkg_2BJets"] = effs["e_2017_10Bkg_2BJets"][hists["e_2017_10Bkg_2BJets"]->FindBin(PFNcuts_0p9["e_2017_10Bkg"])-1];
    PFNcut_effs["e_2018_10Bkg_2BJets"] = effs["e_2018_10Bkg_2BJets"][hists["e_2018_10Bkg_2BJets"]->FindBin(PFNcuts_0p9["e_2018_10Bkg"])-1];
    PFNcut_effs["m_2016_10Bkg_2BJets"] = effs["m_2016_10Bkg_2BJets"][hists["m_2016_10Bkg_2BJets"]->FindBin(PFNcuts_0p9["m_2016_10Bkg"])-1];
    PFNcut_effs["m_2017_10Bkg_2BJets"] = effs["m_2017_10Bkg_2BJets"][hists["m_2017_10Bkg_2BJets"]->FindBin(PFNcuts_0p9["m_2017_10Bkg"])-1];
    PFNcut_effs["m_2018_10Bkg_2BJets"] = effs["m_2018_10Bkg_2BJets"][hists["m_2018_10Bkg_2BJets"]->FindBin(PFNcuts_0p9["m_2018_10Bkg"])-1];
    
    PFNcut_effs["e_2016_5Data_2BJets"] = effs["e_2016_5Data_2BJets"][hists["e_2016_5Data_2BJets"]->FindBin(PFNcuts_0p9["e_2016_5Data"])-1];
    PFNcut_effs["e_2017_5Data_2BJets"] = effs["e_2017_5Data_2BJets"][hists["e_2017_5Data_2BJets"]->FindBin(PFNcuts_0p9["e_2017_5Data"])-1];
    PFNcut_effs["e_2018_5Data_2BJets"] = effs["e_2018_5Data_2BJets"][hists["e_2018_5Data_2BJets"]->FindBin(PFNcuts_0p9["e_2018_5Data"])-1];
    PFNcut_effs["m_2016_5Data_2BJets"] = effs["m_2016_5Data_2BJets"][hists["m_2016_5Data_2BJets"]->FindBin(PFNcuts_0p9["m_2016_5Data"])-1];
    PFNcut_effs["m_2017_5Data_2BJets"] = effs["m_2017_5Data_2BJets"][hists["m_2017_5Data_2BJets"]->FindBin(PFNcuts_0p9["m_2017_5Data"])-1];
    PFNcut_effs["m_2018_5Data_2BJets"] = effs["m_2018_5Data_2BJets"][hists["m_2018_5Data_2BJets"]->FindBin(PFNcuts_0p9["m_2018_5Data"])-1];
    PFNcut_effs["e_2016_10Data_2BJets"] = effs["e_2016_10Data_2BJets"][hists["e_2016_10Data_2BJets"]->FindBin(PFNcuts_0p9["e_2016_10Data"])-1];
    PFNcut_effs["e_2017_10Data_2BJets"] = effs["e_2017_10Data_2BJets"][hists["e_2017_10Data_2BJets"]->FindBin(PFNcuts_0p9["e_2017_10Data"])-1];
    PFNcut_effs["e_2018_10Data_2BJets"] = effs["e_2018_10Data_2BJets"][hists["e_2018_10Data_2BJets"]->FindBin(PFNcuts_0p9["e_2018_10Data"])-1];
    PFNcut_effs["m_2016_10Data_2BJets"] = effs["m_2016_10Data_2BJets"][hists["m_2016_10Data_2BJets"]->FindBin(PFNcuts_0p9["m_2016_10Data"])-1];
    PFNcut_effs["m_2017_10Data_2BJets"] = effs["m_2017_10Data_2BJets"][hists["m_2017_10Data_2BJets"]->FindBin(PFNcuts_0p9["m_2017_10Data"])-1];
    PFNcut_effs["m_2018_10Data_2BJets"] = effs["m_2018_10Data_2BJets"][hists["m_2018_10Data_2BJets"]->FindBin(PFNcuts_0p9["m_2018_10Data"])-1];
    
    std::ostringstream e_2016_5_stream_datavsMC, e_2016_10_stream_datavsMC, e_2017_5_stream_datavsMC, e_2017_10_stream_datavsMC, e_2018_5_stream_datavsMC, e_2018_10_stream_datavsMC, m_2016_5_stream_datavsMC, m_2016_10_stream_datavsMC, m_2017_5_stream_datavsMC, m_2017_10_stream_datavsMC, m_2018_5_stream_datavsMC, m_2018_10_stream_datavsMC;
    //e_2016_5_stream << std::setprecision(2) << 100.*PFNcut_effs["e_2016_2GeV"] << "\\% & " << 100.*PFNcut_effs["e_2016_5GeV"] << "\\% & - & - & " << 100.*PFNcut_effs["e_2016_5Bkg"] << "\\%";
    e_2016_5_stream_datavsMC << std::setprecision(2) << PFNcut_effs["e_2016_5Bkg_2BJets"] << " & " << PFNcut_effs["e_2016_5Data_2BJets"] << std::endl;
    std::cout << e_2016_5_stream_datavsMC.str() << std::endl;
    std::cout << "full effs: " << PFNcut_effs["e_2016_5Bkg_2BJets"] << " & " << PFNcut_effs["e_2016_5Data_2BJets"] << std::endl;
    

    //TCanvas c("c2","",700,700);
    //hists["e_2016_5Data_2BJets"]->Draw();
    //c.Print("lakefj.pdf");

    std::cout << "e_2016_5Data_2BJet and e_2016_5Bkg_2BJet effs: " << std::endl;
    for(unsigned i = 0; i < effs["e_2016_5Data_2BJets"].size(); i++){
        //std::cout << effs["e_2016_5Data_2BJets"][i] << " - " << effs["e_2016_5Bkg_2BJets"][i] << std::endl;
    }


}
#endif

#endif
