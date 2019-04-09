////////////////////////////////
// Header for class HNLtagger //
////////////////////////////////

#ifndef HNLtagger_h
#define HNLtagger_h

#include <TROOT.h>
#include <TFile.h>
#include <iostream>
#include <TTree.h>

// other headers to communicate with
#include "../interface/helper_histo_functions.h"

class HNLtagger
{
    public:
        TFile* HNLtagger_file;
        TTree* HNLtagger_tree;

        static const unsigned maxJetSize = 50;
        bool     _JetIsFromHNL;
        unsigned _nJetConstituents;
        double   _JetConstituentPt[maxJetSize];
        double   _JetConstituentEta[maxJetSize];
        double   _JetConstituentPhi[maxJetSize];
        double   _JetConstituentMass[maxJetSize];
        int      _JetConstituentPdgId[maxJetSize];
        int      _JetConstituentCharge[maxJetSize];
        double   _JetConstituentdxySig[maxJetSize];
        double   _JetConstituentdzSig[maxJetSize];
        int      _JetConstituentsNumberOfHits[maxJetSize];    //signed integer so particles without tracks can have negative default values
        int      _JetConstituentsNumberOfPixelHits[maxJetSize];
        bool     _JetConstituentsHasTrack[maxJetSize];

        HNLtagger(TString filename, int partition, int partitionjobnumber);
        void write_HNLtagger_tree();
};

#endif
