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

void testplotterfunctions(TString sample)
{
    cout << sample << endl;
    plot_every_variable_in_root_file(sample);
    //plot_every_variable_in_root_file("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-4_V-0.004472135955_e_pre2017_leptonFirst_NLO_displaced.root");
    //plot_every_variable_in_root_file("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_Background_WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
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
    draw_n_hists("/user/bvermass/CMSSW_9_4_0/src/2l2q_analysis/misc/testplot.pdf", c, hists, "hist", &lgendrup, "pt", "events", -1.5, 1.5, 0, 0, -1, "e", "2", "0.22");
}

void plot_every_variable_in_root_file(TString filename)
{
    //Make directory to store plots for this file
    TString pathname = "/user/bvermass/public/2l2q_analysis/plots/";
    if(filename.Index("HeavyNeutrino") != -1)   pathname += filename(filename.Index("hists_") + 6, filename.Index("HeavyNeutrino") - 7 - filename.Index("hists_")) + "/" + filename(filename.Index("HeavyNeutrino"), filename.Index(".root") - filename.Index("HeavyNeutrino")) + "/";
    else if(filename.Index("Background") != -1) pathname += filename(filename.Index("hists_") + 6, filename.Index("Background") -7 - filename.Index("hists_")) + "/" + filename(filename.Index("Background") + 11, filename.Index(".root") - filename.Index("Background") -11) + "/";

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
    gStyle->SetPaintTextFormat("4.0f");//defines number of digits displayed in text (for example for 2D plots with colz text)
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

        if (cl->InheritsFrom("TH1") and ! cl->InheritsFrom("TH2")){ // second requirement is because TH2 also inherits from TH1
            TH1F *h = (TH1F*)key->ReadObj();
            TString histname = h->GetName();
            if(h->GetMaximum() == 0) continue;
            
            // xlin or log
            int xlog = (histname.Index("xlog") == -1)? 0 : 1;
            // Events or Eff. in yaxis title
            TString yaxistitle = h->GetYaxis()->GetTitle();

            TString pathname_lin = make_pathname(histname, pathname, "lin");
            TString pathname_log = make_pathname(histname, pathname, "log");
            gSystem->Exec("mkdir -p " + pathname_lin);
            gSystem->Exec("mkdir -p " + pathname_log);

            
            markerstyle(h,"blue");

            draw_1_hist(pathname_lin + histname + ".pdf", c, h, "E1", &lgendrup, "", yaxistitle, 0, 0, xlog, flavor, mass, coupling); 
            
            // Efficiencies are calculated right here as TGraphAsymmErrors:       
            if(histname.Index("eff_num") != -1){
                TGraphAsymmErrors* efficiency_graph = new TGraphAsymmErrors((TH1F*)h, (TH1F*)file->Get(histname(0, histname.Index("eff_num") + 4) + "den"), "cp");
                efficiency_graph->GetXaxis()->SetTitle(h->GetXaxis()->GetTitle());
                yaxistitle = "Eff.";
                draw_TGraphAsymmErrors(pathname_lin + histname(0, histname.Index("eff_num") + 3) + ".pdf", c, efficiency_graph, "ALP", &lgendrup, "", yaxistitle, 0, 0, xlog, flavor, mass, coupling);
            }

        }else if(cl->InheritsFrom("TH2")){
            TH2F *h = (TH2F*)key->ReadObj();
            TString histname = h->GetName();
            if(h->GetMaximum() == 0) continue;

            TString pathname_lin = make_pathname(histname, pathname, "lin");
            gSystem->Exec("mkdir -p " + pathname_lin);

            //markerstyle2D(h);

            TString drawoptions = get_2D_draw_options(h);
            draw_2D_hist(pathname_lin + histname + ".pdf", c, h, drawoptions, &lgendrup, "", "", flavor, mass, coupling);
        }
        //This part is obsolete already?    
        //}else if(cl->InheritsFrom("TGraphAsymmErrors")){
        //    TGraphAsymmErrors* h = (TGraphAsymmErrors*)key->ReadObj();
        //    TString histname = h->GetName();
        //    
        //    // xlin or log
        //    int xlog = (histname.Index("xlog") == -1)? 0 : 1;
        //    // Events or Eff. in yaxis title
        //    TString yaxistitle = "Eff.";
        //                                         
        //    TString pathname_lin = make_pathname(histname, pathname, "lin");
        //    gSystem->Exec("mkdir -p " + pathname_lin);

        //    draw_TGraphAsymmErrors(pathname_lin + histname + "_asymm2.pdf", c, h, "ALP", &lgendrup, "", yaxistitle, 0, 0, xlog, flavor, mass, coupling);
        //}
    } 
    cout << "plots finished" << endl;
}

# ifndef __CINT__
int main(int argc, char * argv[])
{
    //std::cout << "main" << std::endl;
    testplotterfunctions(argv[1]);
    return 0;
}
# endif
