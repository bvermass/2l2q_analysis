/////////////////////////////////////////////////////////
// CombinePrep prepares datacards for the Combine Tool //
/////////////////////////////////////////////////////////


#ifndef CombineDatacardPrep_h
#define CombineDatacardPrep_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <THStack.h>
#include <TMultiGraph.h>

#include <iostream>
#include <fstream>
#include <cmath>

#include <string>
#include <utility>
#include <TSystem.h>

#include "../../plotting/helper_plotter_functions.h"
#include "../../plotting/tdrStyle.h"

# ifndef __CINT__ 
int main(int argc, char * argv[]);
void makequadFile(TString quad_filename, TH1F* hist_signal, TH1F* hist_data, std::vector<TH1F*> hists_bkg, const std::string& sigName, const std::string& dataName, const std::vector<std::string>& bkgNames);
void makeShapeSRFile(TString shapeSR_filename, TH1F* hist_signal, TH1F* hist_data, std::vector<TH1F*> hists_bkg, const std::string& sigName, const std::string& dataName, const std::vector<std::string>& bkgNames, std::vector<TH1F*> hist_signal_sys, std::vector<std::vector<TH1F*>> hists_bkg_sys, const std::vector<std::string>& sigName_sys, const std::vector<std::vector<std::string>>& bkgNames_sys);
void makescalefactorFile(TString filename, double scalefactor);
void printDataCard(const std::string& cardName, const double obsYield, const double sigYield, const std::string& sigName, const double* bkgYield, const unsigned nBkg, const std::string* bkgNames, const std::vector<std::vector<double> >& systUnc = std::vector< std::vector< double > >(), const unsigned nSyst = 0, const std::string* systNames = nullptr, const std::string* systDist = nullptr, const bool shapeCard = false, const std::string& shapeFileName = "", const bool autoMCStats = false);

void printABCDDataCard(const std::string& cardName, const double obsYieldA, const double obsYieldB, const double obsYieldC, const double obsYieldD, const double sigYieldA, const double sigYieldB, const double sigYieldC, const double sigYieldD, const std::string& sigName, const double* bkgYieldA, const double* bkgYieldB, const double* bkgYieldC, const double* bkgYieldD, const unsigned nBkg, const std::string* bkgNames, const std::vector<std::vector<double> >& systUnc, const unsigned nSyst, const std::string* systNames, const std::string* systDist, const bool shapeCard, const std::string& shapeFileNameA, const std::string& shapeFileNameB, const std::string& shapeFileNameC, const std::string& shapeFileNameD, const bool autoMCStats );

std::vector<bool> get_correlation_mask(TString sysname, TString histname, int nbins);
std::vector<bool> get_correlation_mask_dirac(TString sysname, TString histname, int nbins);
double get_ABCD_error(int i_bin, TString histname);
double get_ABCD_error_dirac();
void set_UpAndDown_correctly(TH1F* nominal, TH1F* up, TH1F* down);
void plotSysEffects(TCanvas* c, TPad* pad, TString shapeSR_filename, TH1F* hist_signal, std::vector<TH1F*> hist_signal_sys, const std::vector<std::string>& sigName_sys);
void checkfornans(std::vector<std::string>& sigName_sys, std::vector<std::vector<std::string>>& bkgNames_sys, std::vector<TH1F*> hist_signal_sys, std::vector<std::vector<TH1F*>> hists_bkg_sys);
void set_low_content_bins_to_zero(TH1F* hist, std::vector<TH1F*>& hists_sys, double cutoff);
void scale_signal_to_observed(double scalefactor, TH1F* hist_quadA, TH1F* hist_quadB, TH1F* hist_quadC, TH1F* hist_quadD, std::vector<TH1F*>& hists_sys);
double get_trilepton_scalefactor(TH1F* hist_quadA, TH1F* hist_quadB, TH1F* hist_quadC, TH1F* hist_quadD, TH1F* hist_obs_quadA, TH1F* hist_obs_quadB, TH1F* hist_obs_quadC, TH1F* hist_obs_quadD);
double calc_scalefactor(TH1F* hist_quadA, TH1F* hist_quadB, TH1F* hist_quadC, TH1F* hist_quadD, TH1F* hist_obs_quadA, TH1F* hist_obs_quadB, TH1F* hist_obs_quadC, TH1F* hist_obs_quadD);
double get_1718_scalefactor(TString sf_filename);
void plot_signal_contamination(TCanvas* c, TPad* pad, TString plotname, TH1F* hist_signal_quadA, TH1F* hist_signal_quadC);
#endif

//class CombinePrep {
//    public :
//        CombinePrep();
//        ~CombinePrep();
//        void printDataCard(const std::string& cardName, const double obsYield, const double sigYield, const std::string& sigName, const double* bkgYield, const unsigned nBkg, const std::string* bkgNames, const std::vector<std::vector<double> >& systUnc = std::vector< std::vector< double > >(), const unsigned nSyst = 0, const std::string* systNames = nullptr, const std::string* systDist = nullptr, const bool shapeCard = false, const std::string& shapeFileName = "", const bool autoMCStats = false);
//};
#endif
