#ifndef roccurveplotter_h
#define roccurveplotter_h

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
#include "tdrStyle.h"
#include "helper_plotter_functions.h"
#include "../interface/helper_histo_functions.h"

std::vector<TString> get_V2s(double mass);
TGraph* get_roc(std::vector< double > eff_signal, std::vector< double > eff_bkg);
bool plot_extra_hists_with_different_names(TCanvas* c, TMultiGraph* multigraph, TLegend* legend, std::vector<TFile*> files_signal, std::vector<TFile*> files_bkg, std::vector<TString> legends, std::vector<TString> histnames, std::vector<int> colors);
# ifndef __CINT__ 
int main(int argc, char * argv[]);
#endif

#endif
