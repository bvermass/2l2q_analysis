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
        TH1D*  hCounter;

        ULong64_t   _runNb;
        ULong64_t   _lumiBlock;
        ULong64_t   _eventNb;
        bool     _is2016;
        bool     _is2017;
        bool     _is2018;
        double   _weight;
        double   _RawWeight;
        double   _l1_IDSF;
        double   _l1_IDSF_unc_sym;
        double   _l2_IDSF;
        double   _l2_IDSF_unc_sym;
        double   _TrackSF;
        double   _TrackSF_unc_sym;
        double   _l1_ISOSF;
        double   _l1_ISOSF_unc_sym;
        double   _TriggerSF;
        double   _TriggerSF_unc_sym;
        double   _PileUpSF;
        double   _PileUpSF_unc_up;
        double   _PileUpSF_unc_down;
        int      _gen_Nmass;
        double   _gen_NV2;
        double   _gen_Nctau;
        bool     _JetIsFromHNL;
        unsigned _nTightJet;
        unsigned _nMediumBJet;
        unsigned _nLooseBJet;
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
        unsigned _lProvenance;
        unsigned _lProvenanceCompressed;
        bool     _lElectronPassConvVeto;
        unsigned _lElectronMissingHits;
        double   _lElectronSuperClusterOverP;
        double   _lElectronEcalEnergy;
        double   _lElectronSigmaIetaIeta;
        double   _lElectronDEtaInSeed;
        double   _lElectronDeltaPhiSuperClusterTrack;
        double   _lElectronDeltaEtaSuperClusterTrack;
        double   _lElectronHOverE;
        double   _lElectronEInvMinusPInv;
        double   _lElectronNumberInnerHitsMissing;
        bool     _lGlobalMuon;
        bool     _lTrackerMuon;
        double   _lInnerTrackValidFraction;
        double   _lGlobalTrackNormalizedChi2;
        double   _lCQChi2Position;
        double   _lCQTrackKink;
        double   _lMuonSegComp;
        double   _lMuonTime;
        double   _lMuonRPCTime;
        double   _lMuonTrackPtErr;

        double   _l1Pt;
        double   _l1Eta;
        double   _l1Phi;
        double   _l1dxy;
        double   _l1dz;
        double   _l13dIPSig;
        double   _l1relIso;
        double   _l1ptRatio;
        double   _l1ptRel;
        unsigned _l1Flavor;
        int      _l1Charge;
        unsigned _l1Provenance;
        unsigned _l1ProvenanceCompressed;
        bool     _l1ElectronPassConvVeto;
        unsigned _l1ElectronMissingHits;
        double   _l1ElectronSuperClusterOverP;
        double   _l1ElectronEcalEnergy;
        double   _l1ElectronSigmaIetaIeta;
        double   _l1ElectronDEtaInSeed;
        double   _l1ElectronDeltaPhiSuperClusterTrack;
        double   _l1ElectronDeltaEtaSuperClusterTrack;
        double   _l1ElectronHOverE;
        double   _l1ElectronEInvMinusPInv;
        double   _l1ElectronNumberInnerHitsMissing;
        bool     _l1GlobalMuon;
        bool     _l1TrackerMuon;
        double   _l1InnerTrackValidFraction;
        double   _l1GlobalTrackNormalizedChi2;
        double   _l1CQChi2Position;
        double   _l1CQTrackKink;
        double   _l1MuonSegComp;
        double   _l1MuonTime;
        double   _l1MuonRPCTime;
        double   _l1MuonTrackPtErr;
        double   _mll;
        double   _mlljet;
        double   _dRll;
        double   _dphill;
        double   _dRljet;

        double   _SV_PVSVdist;
        double   _SV_PVSVdist_2D;
        double   _SV_genreco;
        double   _SV_mass;
        double   _SV_l1mass;
        double   _SV_pt;
        double   _SV_eta;
        double   _SV_phi;
        double   _SV_normchi2;
        unsigned _SV_ntracks;
        static const unsigned _SV_ntracks_max = 10;
        double   _SV_trackpt[_SV_ntracks_max];
        double   _SV_tracketa[_SV_ntracks_max];
        double   _SV_trackphi[_SV_ntracks_max];
        double   _SV_trackE[_SV_ntracks_max];
        int      _SV_trackcharge[_SV_ntracks_max];


        unsigned _nMV2 = 0;
        static const unsigned nMV2_max = 150;
        int      _evaluating_mass[nMV2_max];
        double   _evaluating_V2[nMV2_max];
        double   _JetTagVal[nMV2_max];
        double   _reweighting_weight[nMV2_max];

        //Branches for reading variables from an existing tree (produced with this class)
        TBranch     *b__runNb;
        TBranch     *b__lumiBlock;
        TBranch     *b__eventNb;
        TBranch     *b__is2016;
        TBranch     *b__is2017;
        TBranch     *b__is2018;
        TBranch     *b__weight;
        TBranch     *b__RawWeight;
        TBranch     *b__l1_IDSF;
        TBranch     *b__l1_IDSF_unc_sym;
        TBranch     *b__l2_IDSF;
        TBranch     *b__l2_IDSF_unc_sym;
        TBranch     *b__TrackSF;
        TBranch     *b__TrackSF_unc_sym;
        TBranch     *b__l1_ISOSF;
        TBranch     *b__l1_ISOSF_unc_sym;
        TBranch     *b__TriggerSF;
        TBranch     *b__TriggerSF_unc_sym;
        TBranch     *b__PileUpSF;
        TBranch     *b__PileUpSF_unc_up;
        TBranch     *b__PileUpSF_unc_down;
        TBranch     *b__gen_Nmass;
        TBranch     *b__gen_NV2;
        TBranch     *b__gen_Nctau;
        TBranch     *b__JetIsFromHNL;
        TBranch     *b__nTightJet;
        TBranch     *b__nMediumBJet;
        TBranch     *b__nLooseBJet;
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
        TBranch     *b__lProvenance;
        TBranch     *b__lProvenanceCompressed;
        TBranch     *b__lElectronPassConvVeto;
        TBranch     *b__lElectronMissingHits;
        TBranch     *b__lElectronSuperClusterOverP;
        TBranch     *b__lElectronEcalEnergy;
        TBranch     *b__lElectronSigmaIetaIeta;
        TBranch     *b__lElectronDEtaInSeed;
        TBranch     *b__lElectronDeltaPhiSuperClusterTrack;
        TBranch     *b__lElectronDeltaEtaSuperClusterTrack;
        TBranch     *b__lElectronHOverE;
        TBranch     *b__lElectronEInvMinusPInv;
        TBranch     *b__lElectronNumberInnerHitsMissing;
        TBranch     *b__lGlobalMuon;
        TBranch     *b__lTrackerMuon;
        TBranch     *b__lInnerTrackValidFraction;
        TBranch     *b__lGlobalTrackNormalizedChi2;
        TBranch     *b__lCQChi2Position;
        TBranch     *b__lCQTrackKink;
        TBranch     *b__lMuonSegComp;
        TBranch     *b__lMuonTime;
        TBranch     *b__lMuonRPCTime;
        TBranch     *b__lMuonTrackPtErr;

        TBranch     *b__l1Pt;
        TBranch     *b__l1Eta;
        TBranch     *b__l1Phi;
        TBranch     *b__l1dxy;
        TBranch     *b__l1dz;
        TBranch     *b__l13dIPSig;
        TBranch     *b__l1relIso;
        TBranch     *b__l1ptRatio;
        TBranch     *b__l1ptRel;
        TBranch     *b__l1Flavor;
        TBranch     *b__l1Charge;
        TBranch     *b__l1Provenance;
        TBranch     *b__l1ProvenanceCompressed;
        TBranch     *b__l1ElectronPassConvVeto;
        TBranch     *b__l1ElectronMissingHits;
        TBranch     *b__l1ElectronSuperClusterOverP;
        TBranch     *b__l1ElectronEcalEnergy;
        TBranch     *b__l1ElectronSigmaIetaIeta;
        TBranch     *b__l1ElectronDEtaInSeed;
        TBranch     *b__l1ElectronDeltaPhiSuperClusterTrack;
        TBranch     *b__l1ElectronDeltaEtaSuperClusterTrack;
        TBranch     *b__l1ElectronHOverE;
        TBranch     *b__l1ElectronEInvMinusPInv;
        TBranch     *b__l1ElectronNumberInnerHitsMissing;
        TBranch     *b__l1GlobalMuon;
        TBranch     *b__l1TrackerMuon;
        TBranch     *b__l1InnerTrackValidFraction;
        TBranch     *b__l1GlobalTrackNormalizedChi2;
        TBranch     *b__l1CQChi2Position;
        TBranch     *b__l1CQTrackKink;
        TBranch     *b__l1MuonSegComp;
        TBranch     *b__l1MuonTime;
        TBranch     *b__l1MuonRPCTime;
        TBranch     *b__l1MuonTrackPtErr;
        TBranch     *b__mll;
        TBranch     *b__mlljet;
        TBranch     *b__dRll;
        TBranch     *b__dphill;
        TBranch     *b__dRljet;

        TBranch     *b__SV_PVSVdist;
        TBranch     *b__SV_PVSVdist_2D;
        TBranch     *b__SV_genreco;
        TBranch     *b__SV_mass;
        TBranch     *b__SV_l1mass;
        TBranch     *b__SV_pt;
        TBranch     *b__SV_eta;
        TBranch     *b__SV_phi;
        TBranch     *b__SV_normchi2;
        TBranch     *b__SV_ntracks;
        TBranch     *b__SV_trackpt;
        TBranch     *b__SV_tracketa;
        TBranch     *b__SV_trackphi;
        TBranch     *b__SV_trackE;
        TBranch     *b__SV_trackcharge;

        TBranch     *b__nMV2;
        TBranch     *b__evaluating_mass;
        TBranch     *b__evaluating_V2;
        TBranch     *b__JetTagVal;
        TBranch     *b__reweighting_weight;

        //Functions
        BkgEstimator();//empty constructor
        BkgEstimator(TString filename, TString fileoption = "recreate", double hCounterValue = 1.);//Constructor meant to create file and write events or to read an existing file
        void open_file_and_tree(TString filename);
        void set_branch_adresses();
        void analyze(int max_entries, int partition, int partitionjobnumber);
        void fill_tree();
        void write_tree();
        void delete_tree();
        void copy_event(BkgEstimator* original);

};
#endif
