#include <iostream>

//Include root header files
#include <TString.h>
#include <TFile.h>
#include <TTree.h>

Long64_t get_nentries_from_file(TString filename, TString treename)
{
    TFile *input = new TFile(filename, "open");
    TTree *tree  = (TTree*) input->Get(treename);
    Long64_t entries = tree->GetEntries();
    input->Close();
    return entries;
}

#ifndef __CINT__
int main(int argc, char * argv[])
{
    TString filepath = "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/";
    TString treename = "blackJackAndHookers/blackJackAndHookersTree";
    TString files[]  = {"DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/dilep_final.root",
                        "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/dilep_final.root",
                        "TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/dilep_final.root",
                        "TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/dilep_final.root",
                        "TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/dilep_final.root",
                        "WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/dilep_final.root",
                        "WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/dilep_final.root",
                        "WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/dilep_final.root",
                        "ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/dilep_final.root"};

    //TString filepath = "/user/bvermass/public/2l2q_analysis/trees/HNLtagger/final/full_analyzer/";
    //TString treename = "HNLtagger_tree";
    //TString files[]  = {"HNLtagger_muon_HeavyNeutrino_lljj_M-5_mu.root",
    //                    "HNLtagger_muon_Background_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root", 
    //                    "HNLtagger_muon_Background_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root",
    //                    "HNLtagger_muon_Background_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",
    //                    "HNLtagger_muon_Background_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",
    //                    "HNLtagger_muon_Background_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",
    //                    "HNLtagger_muon_Background_WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"};
    for(TString filename : files){
        Long64_t entries = get_nentries_from_file(filepath + filename, treename);
        std::cout << entries << " entries in " << filename << ": " << std::endl;
    }
    return 0;
}
#endif
