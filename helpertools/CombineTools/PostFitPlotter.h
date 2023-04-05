///////////////////////////////////////////////////////////////////////////////////////
// PostFitPlotter makes plots of the postfit distributions from combine fitdiagnostics //
///////////////////////////////////////////////////////////////////////////////////////


#ifndef PostFitPlotter_h
#define PostFitPlotter_h

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
#include "../../plotting/ratioplotter.h"

# ifndef __CINT__ 
int main();
#endif
void PlotComparison(TString pathname, TString histname, TGraphAsymmErrors* data, TH1F* ABCD, TH1F* sig, TString M, TString V2);

class FitDiagnosticsOutput
{
    public:
        TString combine_filename;
        TFile* combine_file;

        TString M_str;
        TString V2_str;
        double M;
        double V2;

        FitDiagnosticsOutput(TString filename);
        ~FitDiagnosticsOutput();

        // tree variables and branches
        TGraphAsymmErrors* data_prefit_2016;
        TGraphAsymmErrors* data_prefit_1718;
        TH1F* ABCD_prefit_2016;
        TH1F* ABCD_prefit_1718;
        TH1F* ABCD_postfit_2016;
        TH1F* ABCD_postfit_1718;
        TH1F* sig_prefit_2016;
        TH1F* sig_prefit_1718;
        TH1F* sig_postfit_2016;
        TH1F* sig_postfit_1718;

        TTree* tree_fit_sb;
        int fit_status;
        double r;
        double rLoErr;
        double rHiErr;
        TBranch *b_fit_status;
        TBranch *b_r;
        TBranch *b_rLoErr;
        TBranch *b_rHiErr;
};
#endif
