#ifndef PUWeightReader_H
#define PUWeightReader_H

//include c++ library classes 
#include <iostream>

//include ROOT library classes
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>

class PUWeightReader{
    public:
        PUWeightReader();
        PUWeightReader(TString local_dir, bool is2017, bool is2018, const TH1F* nTrueInteractions);
        ~PUWeightReader();

        double get_PUWeight_Central(const int nPV);
        double get_PUWeight_Up(const int nPV);
        double get_PUWeight_Down(const int nPV);

    private:
        TH1F *PUWeights_Central, *PUWeights_Up, *PUWeights_Down;
};
#endif
