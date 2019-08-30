#include "Skimmer.h"

#include <iostream>
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"

#ifndef __CINT__
int main(int argc, char * argv[]){
    if(argc != 3){
        std::cout << "incorrect number of arguments." << std::endl;
        std::cout << "Command should be: ./a.out inputfilename, outputfilenam" << std::endl;
    }

    Skimmer skimmer(argv[1], argv[2]);
    skimmer.Skim("test");
}
#endif
