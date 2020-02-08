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

class BkgEstimator
{
    public:
        TString BkgEstimator_filename;
        TFile* BkgEstimator_file;
        TTree* BkgEstimator_tree;

        double   _weight;
        int      _gen_Nmass;
        double   _gen_NV;
        double   _gen_Nctau;
        bool     _JetIsFromHNL;
        unsigned _nTightJet;
        double   _JetPt;
        double   _JetEta;
        double   _JetPhi;
        unsigned _nTightLep;
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
        unsigned _lFlavor;
        int      _lCharge;

        double   _l1Pt;
        double   _l1Eta;
        double   _l1Phi;
        unsigned _l1Flavor;
        int      _l1Charge;
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

        unsigned _nMV2;
        static const unsigned nMV2_max = 100;
        int      _evaluating_mass[nMV2_max];
        double   _evaluating_V2[nMV2_max];
        double   _JetTagVal[nMV2_max];
        double   _reweighting_weight[nMV2_max];

        //Branches for reading variables from an existing tree (produced with this class)
        TBranch     *b__weight;
        TBranch     *b__gen_Nmass;
        TBranch     *b__gen_NV;
        TBranch     *b__gen_Nctau;
        TBranch     *b__JetIsFromHNL;
        TBranch     *b__nTightJet;
        TBranch     *b__JetPt;
        TBranch     *b__JetEta;
        TBranch     *b__JetPhi;
        TBranch     *b__nTightLep;
        TBranch     *b__lPt;
        TBranch     *b__lEta;
        TBranch     *b__lPhi;
        TBranch     *b__ldxy;
        TBranch     *b__ldz;
        TBranch     *b__l3dIPSig;
        TBranch     *b__lrelIso;
        TBranch     *b__lptRatio;
        TBranch     *b__lptRel;
        TBranch     *b__lNumberOfHits;
        TBranch     *b__lNumberOfPixelHits;
        TBranch     *b__lFlavor;
        TBranch     *b__lCharge;

        TBranch     *b__l1Pt;
        TBranch     *b__l1Eta;
        TBranch     *b__l1Phi;
        TBranch     *b__l1Flavor;
        TBranch     *b__l1Charge;
        TBranch     *b__mll;
        TBranch     *b__mlljet;
        TBranch     *b__dRll;
        TBranch     *b__dphill;
        TBranch     *b__dRljet;

        TBranch     *b__SV_PVSVdist;
        TBranch     *b__SV_PVSVdist_2D;
        TBranch     *b__SV_ntracks;
        TBranch     *b__SV_mass;
        TBranch     *b__SV_l1mass;
        TBranch     *b__SV_pt;
        TBranch     *b__SV_eta;
        TBranch     *b__SV_phi;
        TBranch     *b__SV_normchi2;

        TBranch     *b__nMV2;
        TBranch     *b__evaluating_mass;
        TBranch     *b__evaluating_V2;
        TBranch     *b__JetTagVal;
        TBranch     *b__reweighting_weight;

        //Functions
        BkgEstimator(TString filename, TString type_and_flavor, int partition, int partitionjobnumber);//Constructor meant to create file and write events
        BkgEstimator(TString filename);//Constructor meant to read existing file and access events
        void open_file_and_tree(TString filename);
        void set_branch_adresses();
        void analyze(int max_entries, int partition, int partitionjobnumber);
        void fill_tree();
        void write_tree();
        void delete_tree();

};
#endif
