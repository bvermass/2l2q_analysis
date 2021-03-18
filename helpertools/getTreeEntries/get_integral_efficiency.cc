#include <iostream>

//Include root header files
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>

std::map<TString, double> get_integral_efficiencies(TString filename)
{
    TFile *input = new TFile(filename, "open");
    std::map<TString, double> values;
    std::vector<TString> histnames = {"l2reco_ctau_eff", "l2reco_pt_eff", "l2reco_eta_eff", "l2reco_Lxyz_eff"};
    for(const auto& histname : histnames){
        TH1F* hnum = (TH1F*)input->Get(histname+"_num");
        TH1F* hden = (TH1F*)input->Get(histname+"_den");
        values[histname] = hnum->Integral() / hden->Integral();
    }
    input->Close();
    return values;
}

#ifndef __CINT__
int main(int argc, char * argv[])
{
    if(argc==1) return 0;
    for(int i = 1; i < argc; i++){
        TString file = (TString) argv[i];
        std::cout << file << ": " << std::endl;
        std::map<TString, double> values = get_integral_efficiencies(file);
        for(const auto& value : values){
            std::cout << value.first << " : " << value.second << std::endl;
        }
    } 
    return 0;
}
#endif
