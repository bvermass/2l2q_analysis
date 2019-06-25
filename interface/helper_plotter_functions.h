# ifndef helper_plotter_functions_h
# define helper_plotter_functions_h
#include <TROOT.h>
#include <TFile.h>
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


TCanvas*    get_canvas();
TLegend     get_legend(double xmin, double ymin, double xmax, double ymax);
void        histstyle(TH1* h);
void        graphstyle(TGraph* graph);

# endif
