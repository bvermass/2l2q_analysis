#include <iostream>
#include <string>
#include "../interface/full_analyzer.h"
#include "../interface/full_analyzer_ee.h"

using namespace std;

void mainroot(TString sample)
{
    cout << "mainroot.cc file: " << sample << endl;
    
    //how it should be: 
    //if(sample.Index("_e_") != -1){
    //    full_analyzer_ee b;
    //    b.run_over_file(sample);
    //}
    //else if(sample.Index("_mu_") != -1){
    //    full_analyzer_mumu b;
    //    b.run_over_file(sample);
    //}
    //else {
    //    full_analyzer_ee b_ee;
    //    b_ee.run_over_file(sample);
    //    full_analyzer_mumu b_mumu;
    //    b_mumu.run_over_file(sample);
    //}
    //
    //full_analyzer_ee* a = new full_analyzer_ee(5);
    //a->test();
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
