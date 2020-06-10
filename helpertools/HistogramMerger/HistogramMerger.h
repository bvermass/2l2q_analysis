////////////////////////////////////////////////////////////////////////////////////////
// Histogram Merger takes a samplelist containing root files with histograms inside.  //
// First line of the samplelist is the destination root filename.                     //
// The lines after that are existing files that are to be merged.                     //
// Merging can happen in a number of ways. Currently the only implementation is       //
// meant for HNL samples of same mass, different original coupling that are basically //
// the same events kinematically, except for different initial lifetime distribution  //
// We merge histograms bin by bin, using weights for each sample bin equal to the     //
// reciprocal of the variance of that sample bin. Weights are normalized to sum to 1  //
// This method is valid only for reweighted HNL histograms that represent exactly     //
// the same expectation values in each bin.                                           //
////////////////////////////////////////////////////////////////////////////////////////


#ifndef histogram_merger_h
#define histogram_merger_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>

#include <iostream>
#include <fstream>
#include <cmath>

#include <string>
#include <TSystem.h>

class HistogramMerger {
    private :
        TString outputfilename;
        std::vector<TString> inputfilenames;
        std::vector<std::vector<TString>> identifiers;

    public :

        HistogramMerger(TString sampleList);
        ~HistogramMerger();
        void inverse_variance_weighted_merging();
        TH1F* do_inverse_variance_weighted_merging(std::vector<TH1F*> hists);
        std::vector<std::vector<TString>> init_identifiers(TString identifier_filename, const char* delim);
        bool check_identifiers(TString histname);
};
#endif
