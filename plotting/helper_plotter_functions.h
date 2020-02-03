# ifndef helper_plotter_functions_h
# define helper_plotter_functions_h

// c++ libraries
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

// root libraries
#include <TROOT.h>
#include <TSystem.h>
#include <TKey.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraphAsymmErrors.h>
#include <TProfile.h>
#include <TLine.h>
#include <TLatex.h>
#include <TF1.h>

// other header files

// class CMSandLuminosity helps to draw the CMS and luminosity text relevant for the plot
class CMSandLuminosity{
    public:
        CMSandLuminosity(TPad* pad);
        ~CMSandLuminosity();
        void Draw();
    private:
        TString CMStext;
        TString lumitext;
        float leftmargin, rightmargin, topmargin;
        TLatex CMSlatex;
        TLatex lumilatex;
};

// Helper functions
std::vector<std::vector<TString>> get_identifiers(const TString identifier_filename, const char* delim);
bool        check_identifiers(TString histname, std::vector<std::vector<TString>> identifiers);
TString     make_general_pathname(const TString& plottype, TString specific_dir);
TString     make_plotspecific_pathname(const TString& histname, const TString& pathname, const TString& linorlog);
TString     get_lflavor(const TString& histname);
TLegend     get_legend(double xmin, double ymin, double xmax, double ymax, int Ncolumns);
TString     adjust_legend(TString legend);
TLatex      get_latex(double textsize, int textalign, int textfont);
TString     get_correct_lumitext(TString RunId, TString lumitext);
int         get_color(TString legend);
TH1F        get_histoRatio(TH1F* data, TH1F* MC, TString xaxistitle);
void        draw_line_at_1(double xmin, double xmax);
void        divide_by_binwidth(TH1F* h);
double      get_scale(TString RunId);
double      get_FWHM(TF1* function);
void        draw_profiles(TCanvas* c, TPad* pad, std::vector<TProfile*> profiles, TString plottitle, TLegend* legend, TString xaxistitle, TString yaxistitle, CMSandLuminosity* CMSandLumi);
std::vector< double > computeEfficiencyForROC(TH1F* hist);
double      computeAUC(TGraph* roc);
void        computeCuttingPoint(std::vector<double> eff_signal, std::vector<double> eff_bkg, TH1F* hist_signal, TH1F* hist_bkg, double required_signal_eff);

// 2D histograms
TString     get_2D_draw_options(TH2F* h);
void        alphanumeric_labels(TH2F* hist);

#endif
