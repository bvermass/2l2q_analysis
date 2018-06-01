#include <TROOT.h>
#include <TFile.h>
#include <TF1.h>
#include <TH2.h>
#include <TH1.h>
#include <THistPainter.h>
#include <TGraphAsymmErrors.h>
#include <TLatex.h>
#include <TTree.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <iostream>
#include <cmath>
#include <TRandom3.h>

#include "../interface/plotterfunctions.h"

void testplotterfunctions(){
    
    //std::cout << "testplotterfunctions" << std::endl; MAKE THIS A STANDARD OPTION FOR DEBUGGING
    std::map<TString, TH1*> hists;

    hists["h"] = new TH1F("h","", 100, -1.5, 1.5);
    hists["h2"] = new TH1F("h2","", 20, -1.5, 1.5);
    hists["h"]->Sumw2();
    hists["h2"]->Sumw2();

    TRandom3 random_generator;
    for (Int_t i = 0; i < 100000; i++) hists["h"]->Fill(random_generator.Gaus(0, 1));
    for (Int_t i = 0; i < 50000; i++) hists["h2"]->Fill(random_generator.Gaus(0, 1));
    
    TCanvas *c = new TCanvas("c","",700,700);
    gStyle->SetOptStat(0);
    gPad->SetTicks(1,1);

    TLegend lgendrup(.6,.6,.85,.85);
    lgendrup.SetBorderSize(0);
    lgendrup.SetFillStyle(0);

    TString legends[] = {"test", "test2"};
    TString colors[]  = {"green", "blue"};
    double norms[]   = {1,1};
    style_legend_and_normalization(hists, lgendrup, legends, colors, norms);
    draw_n_hists("/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_9_4_0/src/2l2q_analysis/makeplots/testplot.pdf", c, hists, "hist", &lgendrup, "pt", "events", -1.5, 1.5, 0, "e", "2", "0.22");
}

# ifndef __CINT__
int main(int argc, char * argv[])
{
    //std::cout << "main" << std::endl;
    testplotterfunctions();
    return 0;
}
# endif
