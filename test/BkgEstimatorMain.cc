#include "../interface/BkgEstimator.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    std::cout << "opening bkgestimator file" << std::endl;

    TString inputfilename = argv[1];

    //example files
    //TString inputfilename = "/user/bvermass/public/2l2q_analysis/trees_QCDCR/BkgEstimator/final/full_analyzer/BkgEstimator_QCD_MuEnriched_MiniAODRun2.root";
    //TString inputfilename = "/user/bvermass/public/2l2q_analysis/trees_QCDCR/BkgEstimator/final/full_analyzer/BkgEstimator_SingleLepton_Run1718.root";

    BkgEstimator event(inputfilename, "read");
    std::string outputfilename = argv[2];
    std::cout << "analyzing events" << std::endl;
    event.analyze(outputfilename, -1, 1, 0);
    std::cout << "finished" << std::endl;
    return 0;
}
# endif
