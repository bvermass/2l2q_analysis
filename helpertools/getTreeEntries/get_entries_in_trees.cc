#include <iostream>

//Include root header files
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>

std::map<TString, double> get_nentries_from_file(TString filename, TString treename)
{
    TFile *input = new TFile(filename, "open");
    TTree *tree  = (TTree*) input->Get(treename);
    std::map<TString, double> values;
    values["entries"] = tree->GetEntries();
    TH1F*  h = (TH1F*)input->Get("blackJackAndHookersGlobal/hCounter");
    if(!h) h = (TH1F*)input->Get("blackJackAndHookers/hCounter");
    if(!h) values["hCounter"] = -1.;
    else values["hCounter"] = h->GetBinContent(1);
    input->Close();
    return values;
}

#ifndef __CINT__
int main(int argc, char * argv[])
{
    if(argc != 3){
        std::cout << "command should be: ./a.out [filename] [treename]" << std::endl;
        return 1;
    }
    TString file = (TString) argv[1];
    TString treename = (TString) argv[2];
    std::cout << file << ": ";
    std::map<TString, double> values = get_nentries_from_file(file, treename);
    std::cout << values["entries"] << " entries, from " << values["hCounter"] << ")" << std::endl;
    return 0;
}
#endif
