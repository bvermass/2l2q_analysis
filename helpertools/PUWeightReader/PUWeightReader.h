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

        void calc_PUWeights(TH1F* PUWeights, TString dataPU_filename, const TH1F* nTrueInteractions_normalized);
        double get_PUWeight_Central(const int nTrueInteractions);
        double get_PUWeight_Up(const int nTrueInteractions);
        double get_PUWeight_Down(const int nTrueInteractions);

    private:

        TH1F *PUWeights_Central;
        TH1F *PUWeights_Up;
        TH1F *PUWeights_Down;
};
#endif
