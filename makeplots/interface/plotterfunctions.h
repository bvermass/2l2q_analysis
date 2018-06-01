# ifndef plotterfunctions_h
# define plotterfunctions_h
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


void markerstyle(TH1F *hist, TString color);
void style_legend_and_normalization(std::map<TString, TH1*>& hists, TLegend& legend, TString legend_entries[], TString colors[], double normalization_const[]);
void draw_n_hists(TString name, TCanvas *c, std::map<TString, TH1*> hists, TString historE1, TLegend *lgend, TString Xaxis, TString Yaxis, double xmin, double xmax, int lin0log1, TString flavor, TString mass, TString coupling);

# endif
