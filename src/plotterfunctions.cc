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
#include <TString.h>
#include <iostream>
#include <string>
#include <cmath>

#include "../interface/plotterfunctions.h"


using namespace std;


std::map<TString, TH1*>::iterator it;


TString make_pathname(TString histname, TString pathname, TString linorlog)
{
        // append directories such as SS/OS, e/mu or HLT to pathname
        TString eormu = "";
        if(histname.Index("_e_") != -1 || histname.Index("Ele") != -1){ 
            eormu = "e/";
        }else if(histname.Index("_mu_") != -1 || histname.Index("Mu") != -1){
            eormu = "mu/";
        }
        TString SSorOS      = (histname.Index("_OS_") == -1)? ((histname.Index("_SS_") == -1)? "" : "SS/") : "OS/";
        TString HLT         = (histname.Index("HLT_") == -1)?       "" : "HLT/";
        TString partialcuts = (histname.Index("before") == -1)?     "" : "partialcuts/";
        TString gen         = (histname.Index("_gen_") == -1)?      "" : "gen/";
        TString vtx         = (histname.Index("_vtx_") == -1)?      "" : "vtx/";
        TString invVtx      = (histname.Index("_invVtx_") == -1)?   "" : "invVtx/";
        TString corrl2      = (histname.Index("_corrl2_") == -1)?   "" : "corrl2/";

        if(linorlog == "lin" || linorlog == "log") linorlog += "/";
        
        return pathname + HLT + eormu + SSorOS + linorlog + partialcuts + gen + vtx + invVtx + corrl2;
}


void mapmarkerstyle(std::map<TString, TH1*> hists)
{
    int i = 0;
    for( it = hists.begin(); it != hists.end(); it++){
        TH1* h = it->second;
        //h->SetMarkerStyle(20);
        h->SetMarkerSize(0);
        h->SetLineWidth(1);
    }
}


void markerstyle(TH1F *hist, TString color)
{
    hist->SetLineWidth(2);
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
    for( it = hists.begin(); it != hists.end(); it++){
        TH1* h = it->second;
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
    for( it = hists.begin(); it != hists.end(); it++){
        TH1* h = it->second;
        markerstyle((TH1F*)h, colors[count]);
        legend.AddEntry(h, legend_entries[count]);
        if(normalization_const[count] == -1) h->Scale(1, "width");
        else h->Scale(normalization_const[count]/h->GetEntries(), "width");
        count++;
    }
}


void draw_text_latex(double xmin, double ymin, int textsize, int textalign, TString text)
{
    TLatex *textltx    = new TLatex(xmin, ymin, text);//0.9,0.905,text);//"35.9 fb^{-1} (13 TeV)"); 
    textltx->SetNDC();
    textltx->SetTextAlign(textalign);
    textltx->SetTextFont(43);
    textltx->SetTextSize(textsize);
    textltx->SetTextColor(kBlack);
    textltx->Draw("same");
}


void draw_2D_hist(TString name, TCanvas *c, TH2F* h, TString drawoptions, TLegend *lgend, TString Xaxis, TString Yaxis, TString flavor, TString mass, TString coupling)
{
    h->GetXaxis()->SetTitleOffset(1.2);
    h->GetYaxis()->SetTitleOffset(1.5);
    if(Xaxis != "") h->GetXaxis()->SetTitle(Xaxis);
    if(Yaxis != "") h->GetYaxis()->SetTitle(Yaxis);

    h->Draw("BOX");//drawoptions);

    lgend->DrawClone("same");
    
    //mass, coupling, flavor in top right corner
    TString masslatex     = (mass == "")? "" : "m_{N}=" + mass + "GeV";
    if((coupling != "" or flavor != "") and mass != "") masslatex += ", ";
    TString couplinglatex = (coupling == "")? "" : "|V|=" + coupling(0,6);
    if(flavor != "" and coupling != "") couplinglatex += ", ";
    TString flavorlatex   = (flavor == "")? "" : (flavor == "e")? "e" : "#mu";
    if(flavor != "") flavorlatex = flavorlatex + flavorlatex + "qq";
    
    draw_text_latex(0.1, 0.91, 25, 11, "#bf{CMS} #it{simulation}");
    draw_text_latex(0.9, 0.91, 22, 31, "#bf{CMS} #it{simulation}");

    c->Print(name);
}


void draw_1_hist(TString name, TCanvas *c, TH1F* h, TString historE1, TLegend *lgend, TString Xaxis, TString Yaxis, double xmin, double xmax, int lin0log1, TString flavor, TString mass, TString coupling)
{
    // set x range lin or log
    c->SetLogx(lin0log1);
 
    // find the y range needed for the plot
    double ymax = 1.25*h->GetMaximum();
  
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

    // "mass, coupling and flavor info if relevant in top right
    TString masslatex     = (mass == "")? "" : "m_{N}=" + mass + "GeV";
    if((coupling != "" or flavor != "") and mass != "") masslatex += ", ";
    TString couplinglatex = (coupling == "")? "" : "|V|=" + coupling(0,6);
    if(flavor != "" and coupling != "") couplinglatex += ", ";
    TString flavorlatex   = (flavor == "")? "" : (flavor == "e")? "e" : "#mu";
    if(flavor != "") flavorlatex = flavorlatex + flavorlatex + "qq";
    
    draw_text_latex(0.13, 0.85, 25, 11, "#bf{CMS} #it{simulation}");
    draw_text_latex(0.87, 0.85, 22, 31, masslatex + couplinglatex + flavorlatex);
    
    //Add option to make several formats, like .root, .png,...
    c->Print(name);
}


void draw_n_hists(TString name, TCanvas *c, std::map<TString, TH1*> hists, TString historE1, TLegend *lgend, TString Xaxis, TString Yaxis, double xmin, double xmax, int ylin0log1, double ymin, double ymax, TString flavor, TString mass, TString coupling)
{
    // set y range lin or log
    c->SetLogy(ylin0log1);
 
    // find the y range needed for the plot
    if(ymax = -1){
        ymax = 0;
        for( it = hists.begin(); it != hists.end(); it++){
            TH1* h = it->second;
            if(1.1*h->GetMaximum() > ymax) ymax = 1.1*h->GetMaximum();
        }
    }
  
    // design and draw the histograms
    bool firstlayout = true; // do only the range and title stuff for the first histogram
    for( it = hists.begin(); it != hists.end(); it++){
        TH1* h2 = it->second;
        if(firstlayout){
            h2->GetXaxis()->SetRangeUser(xmin, xmax);
            h2->GetXaxis()->SetTitle(Xaxis);
            h2->GetXaxis()->SetTitleOffset(1.2);
            h2->GetYaxis()->SetRangeUser(ymin, ymax);
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

    // "mass, coupling and flavor info if relevant in top right
    TString masslatex     = (mass == "")? "" : "m_{N}=" + mass + "GeV";
    if((coupling != "" or flavor != "") and mass != "") masslatex += ", ";
    TString couplinglatex = (coupling == "")? "" : "|V|=" + coupling(0,6);
    if(flavor != "" and coupling != "") couplinglatex += ", ";
    TString flavorlatex   = (flavor == "")? "" : (flavor == "e")? "e" : "#mu";
    if(flavor != "") flavorlatex = flavorlatex + flavorlatex + "qq";
    draw_text_latex(0.13, 0.85, 25, 11, "#bf{CMS} #it{simulation}");
    draw_text_latex(0.9, 0.905, 22, 31, masslatex + couplinglatex + flavorlatex);
    
    //Add option to make several formats, like .root, .png,...
    c->Print(name);
}


void stack_draw_generalstuff(TCanvas *c, THStack* stack, TString Xaxis, TString Yaxis, int ylin0log1, double xmin, double xmax, double ymin, double ymax, TString nostackoption)
{
    c->SetLogy(ylin0log1);
    
    if(nostackoption == "nostack") stack->Draw("PLC hist nostack");
    else stack->Draw("PFC PLC hist");

    stack->SetTitle("");
    stack->GetXaxis()->SetTitle(Xaxis);
    stack->GetYaxis()->SetTitle(Yaxis);
    stack->GetXaxis()->SetTitleOffset(1.2);
    stack->GetYaxis()->SetTitleOffset(1.5);

    if(xmin != -1) stack->GetXaxis()->SetRangeUser(xmin,xmax);
    if(ymin != -1 && stack->GetMaximum() > xmin) stack->SetMinimum(ymin);
    else if(ymin != -1 && ylin0log1 == 0) stack->SetMinimum(0.05 * stack->GetMaximum());
    else if(ymin != -1 && ylin0log1 == 1) stack->SetMinimum(0.0001 * stack->GetMaximum());
    if(ymax != -1) stack->SetMaximum(ymax);
    
    // "CMS simulation" in top left
    draw_text_latex(0.1, 0.905, 25, 11, "#bf{CMS} #it{simulation}");
    draw_text_latex(0.9, 0.905, 22, 31, "35.9 fb^{-1} (13 TeV)");
}


void draw_stack(TString name, TCanvas *c, THStack* stack, TLegend *lgend, TString Xaxis, TString Yaxis, int ylin0log1, double xmin, double xmax, double ymin, double ymax, TString nostackoption)
{
    stack_draw_generalstuff(c, stack, Xaxis, Yaxis, ylin0log1, xmin, xmax, ymin, ymax, nostackoption);
    lgend->DrawClone("same");
    
    //TLatex luminosity   = new TLatex(
    c->Modified();
    c->Print(name);
}


void draw_stack_with_signal(TString name, TCanvas *c, THStack* stack, std::map<TString, TH1*> signals, TString historE1, TLegend *lgend, TString Xaxis, TString Yaxis, int ylin0log1, double xmin, double xmax, double ymin, double ymax, TString nostackoption)
{
    stack_draw_generalstuff(c, stack, Xaxis, Yaxis, ylin0log1, xmin, xmax, ymin, ymax, nostackoption);
    
    // draw signal on top, scaled to integral of background
    double stack_integral = 0;
    TIter next(stack->GetHists());
    TObject* hist = 0;
    while( hist = next()){
        stack_integral += ((TH1*)hist)->Integral();
    }
    for( it = signals.begin(); it != signals.end(); it++){
        TH1* h = it->second;
        double scale_factor = stack_integral / h->Integral();
        h->Scale(scale_factor);
        if(historE1 == "hist") h->Draw("hist same");
        else if(historE1 == "E1") h->Draw("E1 same");
    
        if(ymax == -1 && h->GetMaximum() > stack->GetMaximum()) stack->SetMaximum(1.1 * h->GetMaximum());
    }


    lgend->DrawClone("same");

    c->Modified();
    c->Print(name);
}
