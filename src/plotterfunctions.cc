#include <TF1.h>
#include <TH2.h>
#include <TH1.h>
#include <THStack.h>
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

#include "../interface/plotterfunctions.h"

using namespace std;

void mapmarkerstyle(std::map<TString, TH1*> hists)
{
    for(auto&& sh : hists){
        auto&& h = sh.second;
        //h->SetMarkerStyle(20);
        h->SetMarkerSize(0);
        h->SetLineWidth(1);
    }
}

void markerstyle(TH1F *hist, TString color)
{
    hist->SetMarkerStyle(20);
    hist->SetMarkerSize(0.7);
    if(color == "blue"){
        hist->SetMarkerColor(kBlue+1);
        hist->SetLineColor(kBlue+1);
    }else if(color == "green"){
        hist->SetMarkerColor(kGreen+2);
        hist->SetLineColor(kGreen+2);
    }else if(color == "red"){
        hist->SetMarkerColor(kRed);
        hist->SetLineColor(kRed);
    }else if(color == "black"){
        hist->SetMarkerColor(kBlack);
        hist->SetLineColor(kBlack);
    }else if(color == "cyan"){
        hist->SetMarkerColor(kCyan);
        hist->SetLineColor(kCyan);
    }else if(color == "magenta"){
        hist->SetMarkerColor(kMagenta+2);
        hist->SetLineColor(kMagenta+2);
    }else if(color == "orange"){
        hist->SetMarkerColor(kOrange+2);
        hist->SetLineColor(kOrange+2);
    }else if(color == "teal"){
        hist->SetMarkerColor(kTeal-6);
        hist->SetLineColor(kTeal-6);
    }else if(color == "pink"){
        hist->SetMarkerColor(kPink);
        hist->SetLineColor(kPink);
    }
}

void style_and_normalization(std::map<TString, TH1*>& hists, TString colors[], double normalization_const[])
{
    unsigned count = 0; //to count along with histograms in the map
    for(auto&& sh : hists){
        auto&& h = sh.second;
        markerstyle((TH1F*)h, colors[count]);
        if(normalization_const[count] == -1) h->Scale(1, "width");
        else h->Scale(normalization_const[count]/h->GetEntries(), "width");
        count++;
    }
}

void style_legend_and_normalization(std::map<TString, TH1*>& hists, TLegend& legend, TString legend_entries[], TString colors[], double normalization_const[])
{
    unsigned count = 0; //to count along with histograms in the map
    legend.Clear();
    for(auto&& sh : hists){
        auto&& h = sh.second;
        markerstyle((TH1F*)h, colors[count]);
        legend.AddEntry(h, legend_entries[count]);
        if(normalization_const[count] == -1) h->Scale(1, "width");
        else h->Scale(normalization_const[count]/h->GetEntries(), "width");
        count++;
    }
}

void draw_1_hist(TString name, TCanvas *c, TH1F* h, TString historE1, TLegend *lgend, TString Xaxis, TString Yaxis, double xmin, double xmax, int lin0log1, TString flavor, TString mass, TString coupling)
{
    //std::cout << "draw_n_hists" << std::endl;
    // set x range lin or log
    c->SetLogx(lin0log1);
 
    // find the y range needed for the plot
    double ymax = 1.1*h->GetMaximum();
  
    // design and draw the histograms
    if(xmax != xmin) h->GetXaxis()->SetRangeUser(xmin, xmax);
    if(Xaxis != "") h->GetXaxis()->SetTitle(Xaxis);
    h->GetXaxis()->SetTitleOffset(1.2);
    h->GetYaxis()->SetRangeUser(0, ymax);
    if(Yaxis != "") h->GetYaxis()->SetTitle(Yaxis);
    h->GetYaxis()->SetTitleOffset(1.5);
    if(historE1 == "hist") h->Draw("hist");
    else if(historE1 == "E1") h->Draw("E1");
  
    lgend->DrawClone("same");

    // "CMS simulation" in top left
    TLatex *cms_title    = new TLatex(xmin,1.01*ymax,"#bf{CMS} #it{simulation}"); 
    cms_title->SetTextAlign(11);
    cms_title->SetTextFont(43);
    cms_title->SetTextSize(25);
    cms_title->SetTextColor(kBlack);
    cms_title->Draw("same");

    // "mass, coupling and flavor info if relevant in top right
    TString masslatex     = (mass == "")? "" : "m_{N}=" + mass + "GeV";
    if((coupling != "" or flavor != "") and mass != "") masslatex += ", ";
    TString couplinglatex = (coupling == "")? "" : "|V|=" + coupling;
    if(flavor != "" and coupling != "") couplinglatex += ", ";
    TString flavorlatex   = (flavor == "")? "" : (flavor == "e")? "e" : "#mu";
    if(flavor != "") flavorlatex = flavorlatex + flavorlatex + "qq";
    double xmax_for_title = (xmax == xmin)? h->GetXaxis()->GetXmax() : xmax;
    TLatex *massflavor_title    = new TLatex(xmax_for_title,1.012*ymax, masslatex + couplinglatex + flavorlatex);
    massflavor_title->SetTextFont(43);
    massflavor_title->SetTextSize(25);
    massflavor_title->SetTextAlign(31);
    massflavor_title->SetTextColor(kBlack);
    massflavor_title->Draw("same");
    
    //Add option to make several formats, like .root, .png,...
    c->Print(name);
}

void draw_n_hists(TString name, TCanvas *c, std::map<TString, TH1*> hists, TString historE1, TLegend *lgend, TString Xaxis, TString Yaxis, double xmin, double xmax, int lin0log1, TString flavor, TString mass, TString coupling)
{
    //std::cout << "draw_n_hists" << std::endl;
    // set x range lin or log
    c->SetLogx(lin0log1);
 
    // find the y range needed for the plot
    double ymax = 0;
    for(auto&& sh : hists){
        auto&& h = sh.second;
        if(1.1*h->GetMaximum() > ymax) ymax = 1.1*h->GetMaximum();
    }
  
    // design and draw the histograms
    bool firstlayout = true; // do only the range and title stuff for the first histogram
    for(auto&& sh : hists){
        auto&& h2 = sh.second;
        if(firstlayout){
            h2->GetXaxis()->SetRangeUser(xmin, xmax);
            h2->GetXaxis()->SetTitle(Xaxis);
            h2->GetXaxis()->SetTitleOffset(1.2);
            h2->GetYaxis()->SetRangeUser(0, ymax);
            h2->GetYaxis()->SetTitle(Yaxis);
            h2->GetYaxis()->SetTitleOffset(1.5);
            if(historE1 == "hist") h2->Draw("hist");
            else if(historE1 == "E1") h2->Draw("E1");
            firstlayout = false;
        }
        else if(historE1 == "hist") h2->Draw("hist same");
        else if(historE1 == "E1")   h2->Draw("E1 same");
    }
  
    lgend->DrawClone("same");

    // "CMS simulation" in top left
    TLatex *cms_title    = new TLatex(xmin,1.01*ymax,"#bf{CMS} #it{simulation}"); 
    cms_title->SetTextAlign(11);
    cms_title->SetTextFont(43);
    cms_title->SetTextSize(25);
    cms_title->SetTextColor(kBlack);
    cms_title->Draw("same");

    // "mass, coupling and flavor info if relevant in top right
    TString masslatex     = (mass == "")? "" : "m_{N}=" + mass + "GeV";
    if((coupling != "" or flavor != "") and mass != "") masslatex += ", ";
    TString couplinglatex = (coupling == "")? "" : "|V|=" + coupling;
    if(flavor != "" and coupling != "") couplinglatex += ", ";
    TString flavorlatex   = (flavor == "")? "" : (flavor == "e")? "e" : "#mu";
    if(flavor != "") flavorlatex = flavorlatex + flavorlatex + "qq";
    TLatex *massflavor_title    = new TLatex(xmax,1.012*ymax, masslatex + couplinglatex + flavorlatex);
    massflavor_title->SetTextFont(43);
    massflavor_title->SetTextSize(25);
    massflavor_title->SetTextAlign(31);
    massflavor_title->SetTextColor(kBlack);
    massflavor_title->Draw("same");
    
    //Add option to make several formats, like .root, .png,...
    c->Print(name);
}

void draw_stack(TString name, TCanvas *c, THStack* stack, TLegend *lgend, TString Xaxis, TString Yaxis, int ylin0log1, double xmin, double xmax, double ymin, double ymax)
{
    c->SetLogy(ylin0log1);
    
    stack->Draw("PFC PLC hist");

    stack->GetXaxis()->SetTitle(Xaxis);
    stack->GetYaxis()->SetTitle(Yaxis);
    stack->GetXaxis()->SetTitleOffset(1.2);
    stack->GetYaxis()->SetTitleOffset(1.5);

    if(xmin != -1) stack->GetXaxis()->SetRangeUser(xmin,xmax);
    if(ymin != -1) stack->SetMinimum(ymin);
    if(ymax != -1) stack->SetMaximum(ymax);

    lgend->DrawClone("same");

    // "CMS simulation" in top left
    //TLatex *cms_title    = new TLatex(xmin,1.01*ymax,"#bf{CMS} #it{simulation}"); 
    //cms_title->SetTextAlign(11);
    //cms_title->SetTextFont(43);
    //cms_title->SetTextSize(25);
    //cms_title->SetTextColor(kBlack);
    //cms_title->Draw("same");

    //TLatex luminosity   = new TLatex(
    c->Modified();
    c->Print(name);
}

void draw_stack_with_signal(TString name, TCanvas *c, THStack* stack, std::map<TString, TH1*> signals, TString historE1, TLegend *lgend, TString Xaxis, TString Yaxis, int ylin0log1, double xmin, double xmax, double ymin, double ymax)
{
    c->SetLogy(ylin0log1);
    
    stack->Draw("PFC PLC hist");

    stack->GetXaxis()->SetTitle(Xaxis);
    stack->GetYaxis()->SetTitle(Yaxis);
    stack->GetXaxis()->SetTitleOffset(1.2);
    stack->GetYaxis()->SetTitleOffset(1.5);

    if(xmin != -1) stack->GetXaxis()->SetRangeUser(xmin,xmax);
    if(ymin != -1) stack->SetMinimum(ymin);
    if(ymax != -1) stack->SetMaximum(ymax);

    // draw signal on top
    // find the y range needed for the plot
    double max_for_scale = 0;
    for(auto&& sh : signals){
        auto&& h = sh.second;
        if(h->GetMaximum() > max_for_scale) max_for_scale = h->GetMaximum();
    }
    //double scale_factor = 0.01 * stack->GetMaximum() / max_for_scale;
    
    for(auto&& sh : signals){
        auto&& h = sh.second;
        double scale_factor = 0.01 * stack->GetMaximum() / h->GetMaximum();
        h->Scale(scale_factor);
        if(historE1 == "hist") h->Draw("hist same");
        else if(historE1 == "E1") h->Draw("E1 same");
    }

    lgend->DrawClone("same");

    // "CMS simulation" in top left
    TLatex *cms_title    = new TLatex(0.1,0.905,"#bf{CMS} #it{simulation}"); 
    cms_title->SetNDC();
    cms_title->SetTextAlign(11);
    cms_title->SetTextFont(43);
    cms_title->SetTextSize(25);
    cms_title->SetTextColor(kBlack);
    cms_title->Draw("same");

    TLatex *lumi    = new TLatex(0.9,0.905,"35.9 fb^{-1} (13 TeV)"); 
    lumi->SetNDC();
    lumi->SetTextAlign(31);
    lumi->SetTextFont(43);
    lumi->SetTextSize(22);
    lumi->SetTextColor(kBlack);
    lumi->Draw("same");
    
    c->Modified();
    c->Print(name);
}
