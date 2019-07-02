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
        TString HNLtagger_filename;
        TFile* HNLtagger_file;
        TTree* HNLtagger_tree;

        static const unsigned maxJetSize = 50;
        bool     _JetIsFromHNL;
        double   _JetPt;
        double   _JetEta;
        unsigned _nJetConstituents;
        double   _JetConstituentPt[maxJetSize];
        double   _JetConstituentEta[maxJetSize];
        double   _JetConstituentPhi[maxJetSize];
        int      _JetConstituentPdgId[maxJetSize];
        int      _JetConstituentCharge[maxJetSize];
        double   _JetConstituentdxy[maxJetSize];
        double   _JetConstituentdxyErr[maxJetSize];
        double   _JetConstituentdz[maxJetSize];
        double   _JetConstituentdzErr[maxJetSize];
        int      _JetConstituentNumberOfHits[maxJetSize];    //signed integer so particles without tracks can have negative default values
        int      _JetConstituentNumberOfPixelHits[maxJetSize];
        bool     _JetConstituentHasTrack[maxJetSize];

        HNLtagger(TString filename, TString flavor, int partition, int partitionjobnumber);
        void write_HNLtagger_tree();
        void delete_HNLtagger_tree();
};

class HNLBDTtagger
{
    public:
        TString HNLBDTtagger_filename;
        TFile* HNLBDTtagger_file;
        TTree* HNLBDTtagger_tree;

        bool     _JetIsFromHNL;
        double   _weight;
        double   _lPt;
        double   _lEta;
        double   _lPhi;
        double   _ldxy;
        double   _ldz;
        double   _l3dIPSig;
        double   _lrelIso;
        double   _lptRatio;
        double   _lptRel;
        unsigned _lNumberOfPixelHits;

        double   _JetPt;
        double   _JetEta;
        double   _JetPhi;
        double   _JetMass;
        unsigned _nJetConstituents;
        double   _JetdxySum;
        double   _JetdxySigSum;
        double   _JetdzSum;
        double   _JetdzSigSum;
        int      _JetChargeSum;

        unsigned _SV_ntracks;
        double   _SV_PVSVdist_2D;
        double   _SV_PVSVdist;
        double   _SV_normchi2;
        double   _SV_mass;
        double   _SV_pt;
        double   _SV_eta;
        double   _SV_phi;

        HNLBDTtagger(TString filename, TString flavor, int partition, int partitionjobnumber);
        void write_HNLBDTtagger_tree();
        void delete_HNLBDTtagger_tree();
};

#endif
