#include <iostream>
#include <string>
#include "../plugin/full_analyzer.h"

using namespace std;

void mainroot(TString sample)
{
    cout << "mainroot.cc file: " << sample << endl;
    
    full_analyzer b;

    b.run_over_file(sample);

}


# ifndef __CINT__
int main(int argc, char * argv[])
{
    mainroot(argv[1]);
    return 0;
}
# endif
