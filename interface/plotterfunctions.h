# ifndef plotterfunctions_h
# define plotterfunctions_h
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


void mapmarkerstyle(std::map<TString, TH1*>);
void markerstyle(TH1F *hist, TString color);
void style_and_normalization(std::map<TString, TH1*>& hists, TString colors[], double normalization_const[]);
void style_legend_and_normalization(std::map<TString, TH1*>& hists, TLegend& legend, TString legend_entries[], TString colors[], double normalization_const[]);
void draw_1_hist(TString name, TCanvas *c, TH1F* h, TString historE1, TLegend *lgend, TString Xaxis, TString Yaxis, double xmin, double xmax, int lin0log1, TString flavor, TString mass, TString coupling);
void draw_n_hists(TString name, TCanvas *c, std::map<TString, TH1*> hists, TString historE1, TLegend *lgend, TString Xaxis, TString Yaxis, double xmin, double xmax, int lin0log1, TString flavor, TString mass, TString coupling);
void draw_stack(TString, TCanvas *c, THStack *, TLegend *, TString, TString, int, double, double, double, double);

# endif
