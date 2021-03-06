#include <iostream>
#include <string>
#include "../interface/full_analyzer.h"

using namespace std;

void mainroot(TString sample, double cross_section, int max_entries, int partition, int partitionjobnumber)
{
    if (sample.Index(".root") == -1) sample+= "/dilep.root";//in case only the directory is given and not the actual root file. This should fix in almost all cases
    
    TFile *input = new TFile(sample, "open");
    TTree *tree  = (TTree*) input->Get("blackJackAndHookers/blackJackAndHookersTree");
    

    bool makeHistograms = true;
    bool makeHNLtagger = true;
    bool makeBkgEstimator = true;

    TString local_dir = "/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_14/src/2l2q_analysis/";

    full_analyzer b(tree, local_dir, makeHistograms, makeHNLtagger, makeBkgEstimator);
    b.run_over_file(sample, cross_section, max_entries, partition, partitionjobnumber);
}


# ifndef __CINT__
int main(int argc, char * argv[])
{
    if(argc == 0) return 1;
    double cross_section = atof(argv[2]);
    int max_entries = atof(argv[3]);
    int partition = atof(argv[4]);
    int partitionjobnumber = atof(argv[5]);
    mainroot(argv[1], cross_section, max_entries, partition, partitionjobnumber);
    return 0;
}
# endif
