#include <iostream>
#include <string>
#include "../plugin/full_analyzer.h"

using namespace std;

void mainroot(TString samples)
{
    cout << "mainroot.cc file: " << samples << endl;
    
    full_analyzer b;

    TString flavor;
    if(samples.Index("_e_") != -1)          flavor = "e"; //change the full_analyzer function to do this validation itself
    else if(samples.Index("_mu_") != -1)    flavor = "mu";
    else return;
    b.run_over_file(samples, flavor);

}


# ifndef __CINT__
int main(int argc, char * argv[])
{
    mainroot(argv[1]);
    return 0;
}
# endif
