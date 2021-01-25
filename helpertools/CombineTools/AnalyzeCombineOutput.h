/////////////////////////////////////////////////////////
// CombinePrep prepares datacards for the Combine Tool //
/////////////////////////////////////////////////////////


#ifndef AnalyzeCombineOutput_h
#define AnalyzeCombineOutput_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TGraphAsymmErrors.h>
#include <TPolyLine.h>

#include <iostream>
#include <fstream>
#include <cmath>

#include <string>
#include <utility>
#include <TSystem.h>

#include "../../plotting/tdrStyle.h"
#include "../../plotting/helper_plotter_functions.h"

# ifndef __CINT__ 
int main(int argc, char * argv[]);
#endif
double GetUpperExclusionLimit(std::map<double, std::map<float, double>> signal_strengths, float quantile);
double GetLowerExclusionLimit(std::map<double, std::map<float, double>> signal_strengths, float quantile);
bool CheckGoesBelow1(std::map<double, std::map<float, double>> signal_strengths, float quantile);
bool CheckGoesBackAbove1(std::map<double, std::map<float, double>> signal_strengths, float quantile);
void PlotExclusionLimit(std::map<double, std::map<float, double>> lower_exclusion_limit, std::map<double, std::map<float, double>> upper_exclusion_limit, TString specific_dir, TString Xaxistitle, TString Yaxistitle);
void PlotExclusionLimit_withPolyLine(std::map<double, std::map<float, double>> lower_exclusion_limit, std::map<double, std::map<float, double>> upper_exclusion_limit, TString specific_dir, TString Xaxistitle, TString Yaxistitle);
void PlotSignalStrengths(std::map<double, std::map<float, double>> signal_strengths, TString specific_dir, TString Xaxistitle, TString Yaxistitle);
void PrintExclusionLine(std::map<double, std::map<float, double>> exclusion_line, double quantile);
void PrintAllSignalStrengths(std::map<double, std::map<double, std::map<float, double>>> signal_strengths);
void WriteExclusionLimit(std::map<double, std::map<float, double>> lower_exclusion_limit, std::map<double, std::map<float, double>> upper_exclusion_limit, TString filename);

class CombineOutput
{
    public:
        TString combine_filename;
        TFile* combine_file;
        TTree* combine_tree;

        double M;
        double V2;

        CombineOutput(TString filename);
        ~CombineOutput();
        std::map<float, double> GetSignalStrengths();
        void Init(TTree* tree);

        // tree variables and branches
        double limit;
        double limitErr;
        int syst; //syst not included(0), or included(1) 
        int iToy;
        int iSeed;
        float quantileExpected;

        TBranch *b_limit;
        TBranch *b_limitErr;
        TBranch *b_syst;
        TBranch *b_iToy;
        TBranch *b_iSeed;
        TBranch *b_quantileExpected;
};

//In ExternalLimits.cc
TGraphAsymmErrors* get_external_limit(TString identifier, Color_t lcolor, Style_t lstyle, Width_t lwidth);
std::vector<std::vector<double>> get_limitpoints(TString identifier);
std::vector<std::vector<double>> get_delphi_prompt();
std::vector<std::vector<double>> get_delphi_displaced();
std::vector<std::vector<double>> get_atlas_prompt_electron();
std::vector<std::vector<double>> get_atlas_prompt_muon();
std::vector<std::vector<double>> get_atlas_displaced_muon_LNV();
std::vector<std::vector<double>> get_atlas_displaced_muon_LNC();
std::vector<std::vector<double>> get_cms_trilepton_prompt_muon();
std::vector<std::vector<double>> get_cms_trilepton_prompt_electron();
std::vector<std::vector<double>> get_cms_trilepton_displaced_muon();
std::vector<std::vector<double>> get_cms_trilepton_displaced_electron();

#endif
