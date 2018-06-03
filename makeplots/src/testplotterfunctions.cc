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
#include <TKey.h>
#include <TSystem.h>

#include "../interface/plotterfunctions.h"
#include "../interface/testplotterfunctions.h"

using namespace std;

void testplotterfunctions()
{
    //test_plot();
    plot_every_variable_in_root_file("/user/bvermass/public/2l2q_analysis/histograms/hists_full_analyzer_HeavyNeutrino_lljj_M-4_V-0.004472135955_e_pre2017_leptonFirst_NLO_displaced.root");
    plot_every_variable_in_root_file("/user/bvermass/public/2l2q_analysis/histograms/hists_full_analyzer_Background_WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
}
 
void test_plot()
{
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

void plot_every_variable_in_root_file(TString filename)
{
    //Make directory to store plots for this file
    TString pathname = "~/public/2l2q_analysis/plots/";
    if(filename.Index("HeavyNeutrino") != -1)   pathname += filename(filename.Index("hists_") + 6, filename.Index("HeavyNeutrino") - 7 - filename.Index("hists_")) + "/" + filename(filename.Index("HeavyNeutrino"), filename.Index(".root") - filename.Index("HeavyNeutrino"));
    else if(filename.Index("Background") != -1) pathname += filename(filename.Index("hists_") + 6, filename.Index("Background") -7 - filename.Index("hists_")) + "/" + filename(filename.Index("Background") + 11, filename.Index(".root") - filename.Index("Background") -11);
    gSystem->Exec("mkdir -p " + pathname);

    //For HNL, make mass, coupling and flavor titles
    TString flavor = "";
    TString mass = "";
    TString coupling = "";
    if(filename.Index("HeavyNeutrino") != -1){
        if(filename.Index("_e_") != -1) flavor = "e";
        else if(filename.Index("_mu_") != -1) flavor = "mu";
        else if(filename.Index("_2l_") != -1) flavor = "2l";
        mass = filename(filename.Index("_M-") + 3, filename.Index("_V-") - filename.Index("_M-") - 3);
        coupling = filename(filename.Index("_V-") + 3, filename.Index("_" + flavor + "_") - filename.Index("_V-") - 3);
        if(flavor == "2l") flavor = "l";
    }

    TCanvas *c = new TCanvas("c","",700,700);
    gStyle->SetOptStat(0);
    gPad->SetTicks(1,1);

    TLegend lgendrup(.6,.6,.85,.85);
    lgendrup.SetBorderSize(0);
    lgendrup.SetFillStyle(0);
    
    //GetListOfKeys gives list of keys of all histograms in a file
    TFile *file = TFile::Open(filename);
    TIter next(file->GetListOfKeys());
    TKey * key;
    while ((key = (TKey*)next())) {
        TClass *cl = gROOT->GetClass(key->GetClassName());
        if (!cl->InheritsFrom("TH1")) continue;
        TH1F *h = (TH1F*)key->ReadObj();
        markerstyle(h,"blue");
        cout << h->GetName() << endl;
        if(((TString)h->GetName()).Index("eff") == -1) draw_1_hist(pathname + "/" + h->GetName() + ".pdf", c, h, "hist", &lgendrup, "", "", 0, 0, 0, flavor, mass, coupling); 
        else draw_1_hist(pathname + "/" + h->GetName() + ".pdf", c, h, "E1", &lgendrup, "", "", 0, 0, 0, flavor, mass, coupling);
        //within public/2l2q_analysis/plots/ every different sample gets its own directory 
        //A higher/lower directory based on what cuts I apply? Higher makes more sense
        //Make a directory all! (to easily copy to my pc)
    } 
}

# ifndef __CINT__
int main(int argc, char * argv[])
{
    //std::cout << "main" << std::endl;
    testplotterfunctions();
    return 0;
}
# endif
