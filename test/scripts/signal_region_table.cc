#ifndef PFN_efficiency_cc
#define PFN_efficiency_cc

// c++ libraries
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>

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
#include <THStack.h>
#include <TGraphAsymmErrors.h>
#include <TMultiGraph.h>
#include <TLatex.h>


TString filename_low_2016 = "/user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/Shapefiles/M-3_2l_2016_majorana/_2l_M-3_V2-2e-06_cutTightmlSV_quadA_Shape_SR.root";
TString filename_low_1718 = "/user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/Shapefiles/M-3_2l_1718_majorana/_2l_M-3_V2-2e-06_cutTightmlSV_quadA_Shape_SR.root";
TString filename_high_2016 = "/user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/Shapefiles/M-8_2l_2016_majorana/_2l_M-8_V2-2e-06_cutTightmlSV_quadA_Shape_SR.root";
TString filename_high_1718 = "/user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/Shapefiles/M-8_2l_1718_majorana/_2l_M-8_V2-2e-06_cutTightmlSV_quadA_Shape_SR.root";


# ifndef __CINT__ 
int main(int argc, char * argv[])
{
    //open necessary files: 2016, 1718
    TFile* file_low_2016 = TFile::Open(filename_low_2016);
    TFile* file_low_1718 = TFile::Open(filename_low_1718);
    TFile* file_high_2016 = TFile::Open(filename_high_2016);
    TFile* file_high_1718 = TFile::Open(filename_high_1718);

    //get necessary histograms: ABCD, ABCD_ABCDsysUp, ABCD_ABCDsysDown
    TH1F* ABCD_low_2016 = (TH1F*)file_low_2016->Get("ABCD");
    TH1F* ABCDUp_low_2016 = (TH1F*)file_low_2016->Get("ABCD_ABCDsysUp");
    TH1F* ABCDDown_low_2016 = (TH1F*)file_low_2016->Get("ABCD_ABCDsysDown");
    TH1F* ABCD_low_1718 = (TH1F*)file_low_1718->Get("ABCD");
    TH1F* ABCDUp_low_1718 = (TH1F*)file_low_1718->Get("ABCD_ABCDsysUp");
    TH1F* ABCDDown_low_1718 = (TH1F*)file_low_1718->Get("ABCD_ABCDsysDown");
    
    TH1F* ABCD_high_2016 = (TH1F*)file_high_2016->Get("ABCD");
    TH1F* ABCDUp_high_2016 = (TH1F*)file_high_2016->Get("ABCD_ABCDsysUp");
    TH1F* ABCDDown_high_2016 = (TH1F*)file_high_2016->Get("ABCD_ABCDsysDown");
    TH1F* ABCD_high_1718 = (TH1F*)file_high_1718->Get("ABCD");
    TH1F* ABCDUp_high_1718 = (TH1F*)file_high_1718->Get("ABCD_ABCDsysUp");
    TH1F* ABCDDown_high_1718 = (TH1F*)file_high_1718->Get("ABCD_ABCDsysDown");
    
    std::cout << "bins: " << ABCD_low_2016->GetNbinsX() << std::endl;
    std::ostringstream str_low_2016[6], str_low_1718[6], str_high_2016[6], str_high_1718[6];
    int k = 0;
    for(int i = 1; i < 7; i++){
        str_low_2016[i-1] << std::setprecision(2);
        str_low_1718[i-1] << std::setprecision(2);
        str_high_2016[i-1] << std::setprecision(2);
        str_high_1718[i-1] << std::setprecision(2);
        for(int j = 0; j < 8; j++){
            str_low_2016[i-1] << " & $" << ABCD_low_2016->GetBinContent(i+j*6) << "\\pm " << ABCD_low_2016->GetBinError(i+j*6) << "\\pm " << ABCD_low_2016->GetBinContent(i+j*6) - ABCDDown_low_2016->GetBinContent(i+j*6) << "$";
            str_low_1718[i-1] << " & $" << ABCD_low_1718->GetBinContent(i+j*6) << "\\pm " << ABCD_low_1718->GetBinError(i+j*6) << "\\pm " << ABCD_low_1718->GetBinContent(i+j*6) - ABCDDown_low_1718->GetBinContent(i+j*6) << "$";
            if(i+j*6 == 11 or i+j*6 == 23){
                str_high_2016[i-1] << " & \\multirow{2}{*}{$" << ABCD_high_2016->GetBinContent(i+j*6-k) << "\\pm " << ABCD_high_2016->GetBinError(i+j*6-k) << "\\pm " << ABCD_high_2016->GetBinContent(i+j*6-k) - ABCDDown_high_2016->GetBinContent(i+j*6-k) << "$}";
                str_high_1718[i-1] << " & \\multirow{2}{*}{$" << ABCD_high_1718->GetBinContent(i+j*6-k) << "\\pm " << ABCD_high_1718->GetBinError(i+j*6-k) << "\\pm " << ABCD_high_1718->GetBinContent(i+j*6-k) - ABCDDown_high_1718->GetBinContent(i+j*6-k) << "$}";
                k++;
            }else if(i+j*6 == 12 or i+j*6 == 24){
                str_high_2016[i-1] << " &";
                str_high_1718[i-1] << " &";
            }else{
                str_high_2016[i-1] << " & $" << ABCD_high_2016->GetBinContent(i+j*6-k) << "\\pm " << ABCD_high_2016->GetBinError(i+j*6-k) << "\\pm " << ABCD_high_2016->GetBinContent(i+j*6-k) - ABCDDown_high_2016->GetBinContent(i+j*6-k) << "$";
                str_high_1718[i-1] << " & $" << ABCD_high_1718->GetBinContent(i+j*6-k) << "\\pm " << ABCD_high_1718->GetBinError(i+j*6-k) << "\\pm " << ABCD_high_1718->GetBinContent(i+j*6-k) - ABCDDown_high_1718->GetBinContent(i+j*6-k) << "$";
            }
        }
        //teststr << " & $" << ABCD_2016->GetBinContent(1) << "\\pm " << ABCD_2016->GetBinError(1) << "\\pm " << ABCD_2016->GetBinContent(1) - ABCDDown_2016->GetBinContent(1) << "$";
        //teststr << " & $" << ABCD_2016->GetBinContent(1+6) << "\\pm " << ABCD_2016->GetBinError(1+6) << "\\pm " << ABCD_2016->GetBinContent(1+6) - ABCDDown_2016->GetBinContent(1+6) << "$";
        //teststr << " & $" << ABCD_2016->GetBinContent(1+12) << "\\pm " << ABCD_2016->GetBinError(1+12) << "\\pm " << ABCD_2016->GetBinContent(1+12) - ABCDDown_2016->GetBinContent(1+12) << "$";
        //teststr << " & $" << ABCD_2016->GetBinContent(1+18) << "\\pm " << ABCD_2016->GetBinError(1+18) << "\\pm " << ABCD_2016->GetBinContent(1+18) - ABCDDown_2016->GetBinContent(1+18) << "$";
        //teststr << " & $" << ABCD_2016->GetBinContent(1+24) << "\\pm " << ABCD_2016->GetBinError(1+24) << "\\pm " << ABCD_2016->GetBinContent(1+24) - ABCDDown_2016->GetBinContent(1+24) << "$";
        //teststr << " & $" << ABCD_2016->GetBinContent(1+30) << "\\pm " << ABCD_2016->GetBinError(1+30) << "\\pm " << ABCD_2016->GetBinContent(1+30) - ABCDDown_2016->GetBinContent(1+30) << "$";
        //teststr << " & $" << ABCD_2016->GetBinContent(1+36) << "\\pm " << ABCD_2016->GetBinError(1+36) << "\\pm " << ABCD_2016->GetBinContent(1+36) - ABCDDown_2016->GetBinContent(1+36) << "$";
        //teststr << " & $" << ABCD_2016->GetBinContent(1+42) << "\\pm " << ABCD_2016->GetBinError(1+42) << "\\pm " << ABCD_2016->GetBinContent(1+42) - ABCDDown_2016->GetBinContent(1+42) << "$";
    }
    //std::cout << "adresses: " << ABCD_low_2016->GetNbinsX() << " " << ABCDUp_2016->GetNbinsX() << " " << ABCDDown_2016->GetNbinsX() << " " << ABCD_1718->GetNbinsX() << " " << ABCDUp_1718->GetNbinsX() << " " << ABCDDown_1718->GetNbinsX() << std::endl;
    //write table in loop
    std::cout << "\\begin{table}\n";
    std::cout << "    \\centering\n";
    std::cout << "    \\caption{The predicted event yield in each bin of the signal region, with its statistical and systematic uncertainty.}\n";
    std::cout << "    \\label{tab:SRyield}\n";
    std::cout << "    \\resizebox{1.0\\textwidth}{!}{";
    std::cout << "    \\begin{tabular}{|l|l|l|l|cccccccc|}\n";
    std::cout << "        \\hline\n";
    std::cout << "        PFN & Year & SV mass & \\Deltwod (PV-SV) & OS $\\PGm\\PGm$ & SS \\PGm\\PGm & OS \\Pe\\PGm & SS \\Pe\\PGm & OS \\Pe\\Pe & SS \\Pe\\Pe & OS \\Pgm\\Pe & SS \\PGm\\Pe\\\\\n";
    std::cout << "        \\hline\n";
    std::cout << "        \\hline\n";
    std::cout << "        \\multirow{12}{*}{low mass} & \\multirow{6}{*}{2016} & \\multirow{3}{*}{$<2$ GeV} & 0-4cm" + str_low_2016[0].str() + "\\\\\n";
    std::cout << "        & & & 4-10cm" + str_low_2016[1].str() + "\\\\\n";
    std::cout << "        & & & $>10$cm" + str_low_2016[2].str() + "\\\\\\cline{3-12}\n";
    std::cout << "        & & \\multirow{3}{*}{$>2$ GeV} & 0-4cm" + str_low_2016[3].str() + "\\\\\n";
    std::cout << "        & & & 4-10cm" + str_low_2016[4].str() + "\\\\\n";
    std::cout << "        & & & $>10$cm" + str_low_2016[5].str() + "\\\\\\cline{2-12}\n";
    std::cout << "        & \\multirow{6}{*}{2017+2018} & \\multirow{3}{*}{$<2$ GeV} & 0-4cm" + str_low_1718[0].str() + "\\\\\n";
    std::cout << "        & & & 4-10cm" + str_low_1718[1].str() + "\\\\\n";
    std::cout << "        & & & $>10$cm" + str_low_1718[2].str() + "\\\\\\cline{3-12}\n";
    std::cout << "        & & \\multirow{3}{*}{$>2$ GeV} & 0-4cm" + str_low_1718[3].str() + "\\\\\n";
    std::cout << "        & & & 4-10cm" + str_low_1718[4].str() + "\\\\\n";
    std::cout << "        & & & $>10$cm" + str_low_1718[5].str() + "\\\\\n";
    std::cout << "        \\hline\n";
    std::cout << "        \\multirow{12}{*}{high mass} & \\multirow{6}{*}{2016} & \\multirow{3}{*}{$<6$ GeV} & 0-1cm" + str_high_2016[0].str() + "\\\\\n";
    std::cout << "        & & & 1-5cm" + str_high_2016[1].str() + "\\\\\n";
    std::cout << "        & & & $>5$cm" + str_high_2016[2].str() + "\\\\\\cline{3-12}\n";
    std::cout << "        & & \\multirow{3}{*}{$>6$ GeV} & 0-1cm" + str_high_2016[3].str() + "\\\\\n";
    std::cout << "        & & & 1-5cm" + str_high_2016[4].str() + "\\\\\n";
    std::cout << "        & & & $>5$cm" + str_high_2016[5].str() + "\\\\\\cline{2-12}\n";
    std::cout << "        & \\multirow{6}{*}{2017+2018} & \\multirow{3}{*}{$<6$ GeV} & 0-1cm" + str_high_1718[0].str() + "\\\\\n";
    std::cout << "        & & & 1-5cm" + str_high_1718[1].str() + "\\\\\n";
    std::cout << "        & & & $>5$cm" + str_high_1718[2].str() + "\\\\\\cline{3-12}\n";
    std::cout << "        & & \\multirow{3}{*}{$>6$ GeV} & 0-1cm" + str_high_1718[3].str() + "\\\\\n";
    std::cout << "        & & & 1-5cm" + str_high_1718[4].str() + "\\\\\n";
    std::cout << "        & & & $>5$cm" + str_high_1718[5].str() + "\\\\\n";
    std::cout << "        \\hline\n";
    std::cout << "    \\end{tabular}}\n";
    std::cout << "\\end{table}\n";
}
#endif
#endif
