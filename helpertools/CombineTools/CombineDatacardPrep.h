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
void printDataCard(const std::string& cardName, const double obsYield, const double sigYield, const std::string& sigName, const double* bkgYield, const unsigned nBkg, const std::string* bkgNames, const std::vector<std::vector<double> >& systUnc = std::vector< std::vector< double > >(), const unsigned nSyst = 0, const std::string* systNames = nullptr, const std::string* systDist = nullptr, const bool shapeCard = false, const std::string& shapeFileName = "", const bool autoMCStats = false);
void set_UpAndDown_correctly(TH1F* nominal, TH1F* up, TH1F* down);
void plotSysEffects(TString shapeSR_filename, TH1F* hist_signal, std::vector<TH1F*> hist_signal_sys, const std::vector<std::string>& sigName_sys);
#endif

//class CombinePrep {
//    public :
//        CombinePrep();
//        ~CombinePrep();
//        void printDataCard(const std::string& cardName, const double obsYield, const double sigYield, const std::string& sigName, const double* bkgYield, const unsigned nBkg, const std::string* bkgNames, const std::vector<std::vector<double> >& systUnc = std::vector< std::vector< double > >(), const unsigned nSyst = 0, const std::string* systNames = nullptr, const std::string* systDist = nullptr, const bool shapeCard = false, const std::string& shapeFileName = "", const bool autoMCStats = false);
//};
#endif
