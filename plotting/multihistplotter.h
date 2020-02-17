# ifndef multihistplotter_h
# define multihistplotter_h

// c++ libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

// root libraries
#include <TROOT.h>
#include <TSystem.h>
#include <TMath.h>
#include <TKey.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <THStack.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TMultiGraph.h>
#include <TProfile.h>
#include <TLatex.h>

// other header files
#include "tdrStyle.h"
#include "helper_plotter_functions.h"

# ifndef __CINT__ 
int main(int argc, char * argv[]);
#endif

#endif
