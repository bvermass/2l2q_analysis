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
double GetLowerExclusionLimit(std::map<double, std::map<float, double>> signal_strengths, float quantile);
bool CheckGoesBelow1(std::map<double, std::map<float, double>> signal_strengths);
void PlotSignalStrengths(std::map<double, std::map<float, double>> signal_strengths, TString specific_dir, TString Xaxistitle, TString Yaxistitle);

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
#endif
