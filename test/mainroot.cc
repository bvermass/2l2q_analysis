#include <iostream>
#include <string>
//#include "full_analyzer.h"
using namespace std;

void mainroot(TString samples)
{
    cout << endl << samples << endl << endl;
    
    full_analyzer b;

    TString flavor;
    if(samples.Index("_e_") != -1)          flavor = "e";
    else if(samples.Index("_mu_") != -1)    flavor = "mu";
    
    b.run_over_file(samples, flavor);

}
