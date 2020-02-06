///////////////////////////////////
// Header for class BkgEstimator //
///////////////////////////////////

#ifndef BkgEstimator_h
#define BkgEstimator_h

#include <iostream>
#include <vector>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

// other headers to communicate with
#include "../interface/helper_histo_functions.h"
#include "../helpertools/PFNEvaluation/PFNReader.h"

class BkgEstimator
{
    public:
        TString BkgEstimator_filename;
        TFile* BkgEstimator_file;
        TTree* BkgEstimator_tree;

        int      _gen_Nmass;
        double   _gen_NV;
        double   _gen_Nctau;
        bool     _JetIsFromHNL;
        double   _JetPt;
        double   _JetEta;
        double   _JetPhi;
        double   _lPt;
        double   _lEta;
        double   _lPhi;
        double   _ldxy;
        double   _ldz;
        double   _l3dIPSig;
        double   _lrelIso;
        double   _lptRatio;
        double   _lptRel;
        unsigned _lNumberOfHits;
        unsigned _lNumberOfPixelHits;
        
        double   _l1Pt;
        double   _l1Eta;
        double   _l1Phi;
        double   _mll;
        double   _mlljet;
        double   _dRll;
        double   _dphill;
        double   _dRljet;

        double   _SV_PVSVdist;
        double   _SV_PVSVdist_2D;
        unsigned _SV_ntracks;
        double   _SV_mass;
        double   _SV_l1mass;
        double   _SV_pt;
        double   _SV_eta;
        double   _SV_phi;
        double   _SV_normchi2;

        BkgEstimator(TString filename, TString type_and_flavor, int partition, int partitionjobnumber);
        void fill_tree();
        void write_tree();
        void delete_tree();
};
#endif
