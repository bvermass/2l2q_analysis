# ifndef ratioplotter_h
# define ratioplotter_h

// c++ libraries
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

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
#include <TProfile.h>
#include <TLine.h>
#include <TLatex.h>
#include <TF1.h>
#include <THStack.h>
#include <TColor.h>

#include "helper_plotter_functions.h"

class RatioPlot{
    public:
        RatioPlot(TPad* pad);
        ~RatioPlot();
        
        void SetLogx(int xlog);
        void SetBinNames(std::vector<TString> BinNames);
        void SetCentralRatio(TH1F* num, TH1F* den, TString xaxistitle, TString yaxistitle);
        std::vector<double> GetVariations(TString variation_name, std::vector<TFile*> files_bkg, TH1F* MC_central);
        void SetSystUncs_up_and_down(TString histname, std::vector<TFile*> files_bkg, std::vector<TString> systunc_names, std::vector<TString> legends, TH1F* MC_central);
        void draw_systuncs();
        void ClearSystUncs();
        void AddStatVariation(TH1* hist, TString statname);
        void dothething();
    private:
        TPad* Pad;
        TH1F* Central_Ratio;
        bool varied_exists;
        std::vector<TGraphAsymmErrors*> systunc_graphs;
        std::vector<TString> systunc_legends;
        TLegend systunc_legend;

        std::vector<int> colors;
};


#endif
