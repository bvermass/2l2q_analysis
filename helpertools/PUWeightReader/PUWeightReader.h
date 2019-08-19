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
        PUWeightReader();//dummy initializer if you just want to use make_PUWeights.
        PUWeightReader(const TString filename_weights, const TString histoname_weights);
        ~PUWeightReader();

        double get_PUWeight(const int nPV);
        void make_PUWeights(const TString filename_data, const TString filename_MC, const int nbins, const double xmin, const double xmax);

    private:
        TFile* file_weights;
        TH1F* histo_weights;
};
#endif
