#include <TROOT.h>
#include <TFile.h>
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
#include <string>
#include <cmath>
#include <TRandom3.h>
#include <TKey.h>
#include <TSystem.h>
#include <THStack.h>

#include "../interface/analyze_cuts.h"

using namespace std;

std::vector<TString> get_signs_and_flavor(int argc, char * argv[]){
    bool e = false, mu = false;
    for(int i = 1; i < (argc + 1)/2; i++){
        TString name = (TString)argv[i];
        if(name.Index("_e_") != -1) e = true;
        if(name.Index("_mu_") != -1) mu = true;
    }

    if(!e and !mu){ e = true; mu = true;}               // if neither are true, there are only background samples and you would want both e and mu

    // fill vector based on flavors wanted
    std::vector<TString> signs_and_flavor_vec;
    if(mu){
        signs_and_flavor_vec.push_back("_OS_mu");
        signs_and_flavor_vec.push_back("_SS_mu");
    }
    if(e){
        signs_and_flavor_vec.push_back("_OS_e");
        signs_and_flavor_vec.push_back("_SS_e");
    }

    return signs_and_flavor_vec;
}


# ifndef __CINT__
int main(int argc, char * argv[])
{
    // Open files, get wanted histograms and print latex table in the same loop since I don't need any other functionality
    std::vector<TString> signs_and_flavor_vec = get_signs_and_flavor(argc, argv);
    double accuracy = 0.001;
    for(TString sf_it : signs_and_flavor_vec){
        cout << "----------" << sf_it << "-----------" << endl;
        cout << "\\scalebox{0.85}{" << endl;
        cout << "\\begin{tabular}{|c|c|c|}" << endl;
        cout << "\\hline" << endl;
        cout << "Process (" + sf_it + ") & $l_2$ Vtx & SVgenreco < 0.2cm \\\\" << endl;
        cout << "\\hline" << endl;
        for(int i = 1; i < (argc + 1)/2; i++){
            TString name = (TString)argv[(argc - 1)/2 + i];
            TFile*  file = TFile::Open(argv[i]);
            TH1F* hist = (TH1F*) file->Get(sf_it+"_IVF_categories");
            cout << name << " & " << 100*accuracy*round(hist->GetBinContent(2)/hist->GetBinContent(1)/accuracy) << " & " << 100*accuracy*round(hist->GetBinContent(3)/hist->GetBinContent(1)/accuracy) << " \\\\" << endl;
        }
        cout << "\\hline" << endl;
        cout << "\\end{tabular}" << endl;
        cout << "}" << endl;
    }
}
# endif
