#include "HistogramMerger.h"

#include <iostream>
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"

#ifndef __CINT__
int main(int argc, char * argv[]){
    if(argc != 2){
        std::cout << "incorrect number of arguments." << std::endl;
        std::cout << "Command should be: ./a.out sampleList" << std::endl;
    }

    HistogramMerger merger(argv[1]);
    merger.inverse_variance_weighted_merging();
}
#endif
