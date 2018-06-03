# ifndef testplotterfunctions_h
# define testplotterfunctions_h
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


void testplotterfunctions();
void test_plot();
void plot_every_variable_in_root_file(TString filename);

# ifndef __CINT__ 
int main(int argc, char * argv[]);
#endif

#endif
