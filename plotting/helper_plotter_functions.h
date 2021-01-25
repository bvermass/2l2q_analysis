# ifndef helper_plotter_functions_h
# define helper_plotter_functions_h

// c++ libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <chrono>
#include <thread>

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
#include <TLine.h>
#include <TLatex.h>

// other header files
#include "../interface/helper_histo_functions.h"

// class CMSandLuminosity helps to draw the CMS and luminosity text relevant for the plot
class CMSandLuminosity{
    public:
        CMSandLuminosity(TPad* pad, bool is2016, bool is2017, bool is2018, bool isRun2);
        ~CMSandLuminosity();
        void change_CMStext(TString new_text);
        void change_lumitext(TString new_text);
        void Draw();
    private:
        TString CMStext;
        TString lumitext;
        float leftmargin, rightmargin, topmargin;
        TLatex CMSlatex;
        TLatex lumilatex;
};

class Shape_SR_plottext{
    public:
        Shape_SR_plottext(TPad* pad);
        ~Shape_SR_plottext();
        void Draw(TString histname);
        void Draw_2l(TString mass_category);
        void Draw_ee(TString mass_category);
        void Draw_em(TString mass_category);
        void Draw_me(TString mass_category);
        void Draw_mm(TString mass_category);
        void Draw_lines_and_generaltext(TString mass_category);
        void Draw_Shape_alpha_lines_and_generaltext(TString mass_category);
    private:
        TString mm, em, ee, me, OS, SS, masslessthan2, massmorethan2, masslessthan6, massmorethan6;
        float leftmargin, rightmargin, topmargin, bottommargin;
        TLatex latex;
        TLine fullLine, dashedLine;
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
int         get_color(TString legend);
TH1F        get_histoRatio(TH1F* data, TH1F* MC, TString xaxistitle);
void        draw_line_at_1(double xmin, double xmax);
void        divide_by_binwidth(TH1F* h);
std::vector< double > computeEfficiencyForROC(TH1F* hist);
double      computeAUC(TGraph* roc);
std::tuple<double, double, double> computeCuttingPoint(std::vector<double> eff_signal, std::vector<double> eff_bkg, TH1F* hist_signal, TH1F* hist_bkg, double required_signal_eff, TString general_pathname, TString histname);

// 2D histograms
TString     get_2D_draw_options(TH2F* h);
void        alphanumeric_labels_2D(TH2F* hist, TString histname);

// template functions are put entirely in the header
template <typename T>
void alphanumeric_labels(T hist, TString histname)
{
    if(histname.Contains("SRShape2")){
        const char* xlabels_SRShape[2] = {"L_{xy}<10", "L_{xy}>10"};
        for(int i = 0; i < 2; i++) hist->GetXaxis()->SetBinLabel(i+1, xlabels_SRShape[i]);
    }
    else if(histname.Contains("SRShape")){
        const char* xlabels_SRShape[4] = {"#splitline{M_{SV}<4}{L_{xy}<10}", "#splitline{M_{SV}<4}{L_{xy}>10}", "#splitline{M_{SV}>4}{L_{xy}<10}", "#splitline{M_{SV}>4}{L_{xy}>10}"};
        for(int i = 0; i < 4; i++) hist->GetXaxis()->SetBinLabel(i+1, xlabels_SRShape[i]);
    }
    else if(histname.Contains("QuadFractions")){
        const char *quadfractions_labels[4] = {"A", "B", "C", "D"};
        for(int i = 0; i < 4; i++) hist->GetXaxis()->SetBinLabel(i+1, quadfractions_labels[i]);
    }
}


#endif
