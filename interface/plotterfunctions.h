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
#include <TGraphAsymmErrors.h>
#include <TMultiGraph.h>


TString make_pathname(TString, TString, TString);
void mapmarkerstyle(std::map<TString, TH1*>);
void mapmarkerstyle(std::map<TString, TGraphAsymmErrors*>);
void markerstyle(TH1F *hist, TString color);
void style_and_normalization(std::map<TString, TH1*>& hists, TString colors[], double normalization_const[]);
void style_legend_and_normalization(std::map<TString, TH1*>& hists, TLegend& legend, TString legend_entries[], TString colors[], double normalization_const[]);
void draw_text_latex(double xmin, double ymin, int textsize, int textalign, TString text);
TString get_2D_draw_options(TH2F* h);
void draw_2D_hist(TString name, TCanvas *c, TH2F* h, TString drawoptions, TLegend *lgend, TString Xaxis, TString Yaxis, TString flavor, TString mass, TString coupling);
void divide_by_binwidth(TH1F* h);
TString get_yaxistitle(TString histname, TString current_title);
void draw_1_hist(TString name, TCanvas *c, TH1F* h, TString historE1, TLegend *lgend, TString Xaxis, TString Yaxis, double xmin, double xmax, int lin0log1, TString flavor, TString mass, TString coupling);
void draw_TGraphAsymmErrors(TString name, TCanvas *c, TGraphAsymmErrors* h, TString drawoptions, TLegend *lgend, TString Xaxis, TString Yaxis, double xmin, double xmax, int lin0log1, TString flavor, TString mass, TString coupling);
void draw_n_hists(TString name, TCanvas *c, std::map<TString, TH1*> hists, TString historE1, TLegend *lgend, TString Xaxis, TString Yaxis, double xmin, double xmax, int lin0log1, double ymin, double ymax, TString flavor, TString mass, TString coupling);
void stack_draw_generalstuff(TCanvas *c, THStack* stack, TString Xaxis, TString Yaxis, int ylin0log1, int xlin0log1, double xmin, double xmax, double ymin, double ymax, TString nostackoption);
void draw_stack(TString, TCanvas *c, THStack *, TLegend *, TString, TString, int, int, double, double, double, double, TString);
void draw_stack_with_signal(TString, TCanvas *c, THStack *, std::map<TString, TH1*>, TString, TLegend *, TString, TString, int, int, double, double, double, double, TString);
void draw_multigraph(TString, TCanvas *c, TMultiGraph *, TLegend *, TString, TString, int, int, double, double, double, double, TString);

# endif
