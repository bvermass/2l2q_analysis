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
void PlotComparison(TString pathname, TString histname, TGraphAsymmErrors* data, TH1F* ABCD);

class FitDiagnosticsOutput
{
    public:
        TString combine_filename;
        TFile* combine_file;

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
};
#endif
