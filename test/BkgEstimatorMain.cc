#include "../interface/BkgEstimator.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    std::cout << "opening bkgestimator file" << std::endl;
    BkgEstimator event("/user/bvermass/public/2l2q_analysis/trees_unparametrized_LowAndHighMass/BkgEstimator/SRevents_LowMass/BkgEstimator_SingleLepton_Run2.root", "read");
    std::cout << "analyzing events" << std::endl;
    event.analyze(-1, 1, 0);
    std::cout << "finished" << std::endl;
    return 0;
}
# endif
