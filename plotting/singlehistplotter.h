# ifndef singlehistplotter_h
# define singlehistplotter_h

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
#include <TGraphAsymmErrors.h>
#include <TLatex.h>
#include <THStack.h>

// other header files
#include "tdrStyle.h"
#include "helper_plotter_functions.h"
#include "ratioplotter.h"
#include "../interface/helper_histo_functions.h"

# ifndef __CINT__ 
int main(int argc, char * argv[]);
#endif
void plot_2_hists_with_ratio(TFile* sample_file, TString general_pathname, TH1F* sample_hist, TString histname, std::vector<int> colors, bool is2016, bool is2017, bool is2018, std::vector<TString> tags, std::vector<TString> legend_tags, TString plot_tag, bool normalize_to_1);
void plot_normalized_hists(TFile* sample_file, TString general_pathname, TH1F* sample_hist, TString histname, TCanvas* c, TPad* pad, TLegend legend, std::vector<int> colors, CMSandLuminosity* CMSandLumi, Shape_SR_plottext* shapeSR_text, std::vector<TString> tags, std::vector<TString> legend_tags, TString plot_tag, bool normalize_to_1);
void plot_Shape_SR_with_Signal_eff(TString filename, TString general_pathname, TH1F* sample_hist, TString histname, TCanvas* c, TPad* pad, TLegend legend, std::vector<int> colors, CMSandLuminosity* CMSandLumi, Shape_SR_plottext* shapeSR_text);

#endif
