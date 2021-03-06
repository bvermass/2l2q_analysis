#include "PUWeightReader.h"

#include <iostream>
#include <string>

# ifndef __CINT__
int main()
{
    PUWeightReader puweightreader;
    std::string filename_data = "/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_14/src/2l2q_analysis/data/PUWeights/PU_2016_36000_XSecCentral.root";
    //std::string filename_MC   = "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/dilep_METResolution.root";
    std::string filename_MC   = "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/dilep_final.root";
    int nbins = 100;
    double xmin = 0;
    double xmax = 100;
    puweightreader.make_PUWeights(filename_data, filename_MC, nbins, xmin, xmax);
}
# endif
