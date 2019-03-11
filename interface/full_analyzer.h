//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 13 16:51:52 2017 by ROOT version 6.06/01
// from TTree full_analyzer/full_analyzer
// found on file: /user/bvermass/public/heavyNeutrino/HeavyNeutrino_samesign_M-10_V-0.01_e_NLO/local_HNdilepMCList/dilep.root
//////////////////////////////////////////////////////////

#ifndef full_analyzer_h
#define full_analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <iostream>

#include <string>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TSystem.h>
#include <TGraphAsymmErrors.h>

// Header file for the classes stored in the TTree if any.

class full_analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   unsigned long    _runNb;
   unsigned long    _lumiBlock;
   unsigned long    _eventNb;
   unsigned     _nVertex;
   double       _BS_x;
   double       _BS_y;
   double       _BS_z;
   double       _PV_x;
   double       _PV_y;
   double       _PV_z;
   float        _nTrueInt;
   double       _weight;
   double       _lheHTIncoming;
   double       _ctauHN;
   unsigned     _nLheWeights;
   double       _lheWeight[110];   //[_nLheWeights]
   unsigned     _ttgEventType;
   unsigned     _zgEventType;
   double       _gen_met;
   double       _gen_metPhi;
   unsigned     _gen_nPh;
   double       _gen_phPt[20];   //[_gen_nPh]
   double       _gen_phEta[20];   //[_gen_nPh]
   double       _gen_phPhi[20];   //[_gen_nPh]
   double       _gen_phE[20];   //[_gen_nPh]
   int          _gen_phMomPdg[20];   //[_gen_nPh]
   bool         _gen_phIsPrompt[20];   //[_gen_nPh]
   double       _gen_phMinDeltaR[20];   //[_gen_nPh]
   bool         _gen_phPassParentage[20];   //[_gen_nPh]
   unsigned     _gen_nL;
   double       _gen_lPt[20];   //[_gen_nL]
   double       _gen_lEta[20];   //[_gen_nL]
   double       _gen_lPhi[20];   //[_gen_nL]
   double       _gen_lE[20];   //[_gen_nL]
   unsigned     _gen_lFlavor[20];   //[_gen_nL]
   int          _gen_lCharge[20];   //[_gen_nL]
   int          _gen_lMomPdg[20];   //[_gen_nL]
   double       _gen_vertex_x[20];
   double       _gen_vertex_y[20];
   double       _gen_vertex_z[20];
   bool         _gen_lIsPrompt[20];   //[_gen_nL]
   double       _gen_lMinDeltaR[20];   //[_gen_nL]
   bool         _gen_lPassParentage[20];   //[_gen_nL]
   double       _gen_HT;
   unsigned     _gen_nN;
   double       _gen_NPt;
   double       _gen_NEta;
   double       _gen_NPhi;
   double       _gen_NE;
   double       _gen_Nvertex_x;
   double       _gen_Nvertex_y;
   double       _gen_Nvertex_z;
   unsigned     _gen_nNPackedDtrs;
   double       _gen_NPackedDtrsPt[20];
   double       _gen_NPackedDtrsEta[20];
   double       _gen_NPackedDtrsPhi[20];
   double       _gen_NPackedDtrsE[20];
   int          _gen_NPackedDtrsPdgId[20];
   int          _gen_NPackedDtrsCharge[20];
   int          matches[20];
   double       _gen_NPackedDtrsmineta[20];
   double       _gen_NPackedDtrsminphi[20];
   double       _gen_NPackedDtrsminpt[20];
   double       _gen_NPackedDtrs_matchPt[20];
   double       _gen_NPackedDtrs_matchEta[20];
   double       _gen_NPackedDtrs_matchPhi[20];
   double       _gen_NPackedDtrs_matchE[20];
   double       _gen_NPackedDtrs_matchdxy[20];
   double       _gen_NPackedDtrs_matchdz[20];
   int          _gen_NPackedDtrs_matchcharge[20];
   unsigned     _gen_nNdaughters;
   unsigned     _gen_Ndaughters_pdg[30];   //[_gen_nNdaughters]
   unsigned     _gen_nstatus23;
   unsigned     _gen_nstatus23_fromN;
   unsigned     _gen_nstatus23_fromW;
   int          _gen_status23_pdg[5];   //[_gen_nstatus23]
   unsigned     _gen_status23_fromN_pdg[3];   //[_gen_nstatus23_fromN]
   unsigned     _gen_status23_fromW_pdg[1];   //[_gen_nstatus23_fromW]
   unsigned     _gen_nq;
   double       _gen_qPt[2];   //[_gen_nq23]
   double       _gen_qEta[2];   //[_gen_nq23]
   double       _gen_qPhi[2];   //[_gen_nq23]
   double       _gen_qE[2];   //[_gen_nq23]
   unsigned     _gen_nq1dtr;
   int          _gen_q1dtr_status[20];   //[_gen_nq1dtr]
   int          _gen_q1dtr_pdgid[20];   //[_gen_nq1dtr]
   double       _gen_q1dtr_Pt[20];   //[_gen_nq1dtr]
   double       _gen_q1dtr_Eta[20];   //[_gen_nq1dtr]
   double       _gen_q1dtr_Phi[20];   //[_gen_nq1dtr]
   double       _gen_q1dtr_E[20];   //[_gen_nq1dtr]
   unsigned     _gen_nq2dtr;
   int          _gen_q2dtr_status[20];   //[_gen_nq2dtr]
   int          _gen_q2dtr_pdgid[20];   //[_gen_nq2dtr]
   double       _gen_q2dtr_Pt[20];   //[_gen_nq2dtr]
   double       _gen_q2dtr_Eta[20];   //[_gen_nq2dtr]
   double       _gen_q2dtr_Phi[20];   //[_gen_nq2dtr]
   double       _gen_q2dtr_E[20];   //[_gen_nq2dtr]
   bool         _HLT_Ele27_WPTight_Gsf;
   int          _HLT_Ele27_WPTight_Gsf_prescale;
   bool         _HLT_IsoMu24;
   int          _HLT_IsoMu24_prescale;
   bool         _HLT_IsoTkMu24;
   int          _HLT_IsoTkMu24_prescale;
   //bool         _HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;
   //int          _HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_prescale;
   //bool         _HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   //int          _HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
   //bool         _HLT_Mu8_DiEle12_CaloIdL_TrackIdL;
   //int          _HLT_Mu8_DiEle12_CaloIdL_TrackIdL_prescale;
   //bool         _HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
   //int          _HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
   //bool         _HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
   //int          _HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_prescale;
   //bool         _HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ;
   //int          _HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
   //bool         _HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL;
   //int          _HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_prescale;
   //bool         _HLT_DiMu9_Ele9_CaloIdL_TrackIdL;
   //int          _HLT_DiMu9_Ele9_CaloIdL_TrackIdL_prescale;
   //bool         _HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
   //int          _HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_prescale;
   //bool         _HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
   //int          _HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;
   //bool         _HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
   //int          _HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;
   //bool         _HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
   //int          _HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_prescale;
   //bool         _HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
   //int          _HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;
   //bool         _HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
   //int          _HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;
   //bool         _HLT_TripleMu_12_10_5;
   //int          _HLT_TripleMu_12_10_5_prescale;
   //bool         _passMETFilters;
   //bool         _Flag_HBHENoiseFilter;
   //bool         _Flag_HBHENoiseIsoFilter;
   //bool         _Flag_EcalDeadCellTriggerPrimitiveFilter;
   //bool         _Flag_goodVertices;
   //bool         _Flag_BadPFMuonFilter;
   //bool         _Flag_BadChargedCandidateFilter;
   //bool         _Flag_globalTightHalo2016Filter;
   //bool         _HLT_Ele105_CaloIdVT_GsfTrkIdT;
   //int          _HLT_Ele105_CaloIdVT_GsfTrkIdT_prescale;
   //bool         _HLT_Ele115_CaloIdVT_GsfTrkIdT;
   //int          _HLT_Ele115_CaloIdVT_GsfTrkIdT_prescale;
   //bool         _HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   //int          _HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
   //bool         _HLT_DoubleEle33_CaloIdL_GsfTrkIdVL;
   //int          _HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_prescale;
   //bool         _HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL;
   //int          _HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_prescale;
   //bool         _HLT_Mu50;
   //int          _HLT_Mu50_prescale;
   //bool         _HLT_TkMu50;
   //int          _HLT_TkMu50_prescale;
   //bool         _HLT_Mu45_eta2p1;
   //int          _HLT_Mu45_eta2p1_prescale;
   //bool         _HLT_Mu30_TkMu11;
   //int          _HLT_Mu30_TkMu11_prescale;
   unsigned     _nL;
   unsigned     _nMu;
   unsigned     _nEle;
   unsigned     _nLight;
   unsigned     _nTau;
   double       _lPt[10];   //[_nL]
   double       _lEta[10];   //[_nL]
   double       _lEtaSC[10];   //[_nLight]
   double       _lPhi[10];   //[_nL]
   double       _lE[10];   //[_nL]
   unsigned     _lFlavor[10];   //[_nL]
   int          _lCharge[10];   //[_nL]
   double       _dxy[10];   //[_nL]
   double       _dz[10];   //[_nL]
   double       _3dIP[10];   //[_nL]
   double       _3dIPSig[10];   //[_nL]
   float        _lElectronMva[10];   //[_nLight]
   float        _lElectronMvaHZZ[10];   //[_nLight]
   bool         _lElectronPassEmu[10];   //[_nLight]
   bool         _lElectronPassConvVeto[10];   //[_nLight]
   bool         _lElectronChargeConst[10];   //[_nLight]
   unsigned     _lElectronMissingHits[10];   //[_nLight]
   bool         _lEleIsEB[10];                                                                         //electron specific variables for displaced electron ID
   bool         _lEleIsEE[10];
   double       _lEleSuperClusterOverP[10];
   double       _lEleEcalEnergy[10];
   double       _lElefull5x5SigmaIetaIeta[10];
   double       _lEleDEtaInSeed[10];
   double       _lEleDeltaPhiSuperClusterTrackAtVtx[10];
   double       _lElehadronicOverEm[10];
   double       _lEleInvMinusPInv[10];
   double       _eleNumberInnerHitsMissing[10];
   double       _leptonMvaSUSY16[10];   //[_nLight]
   double       _leptonMvaTTH16[10];   //[_nLight]
   double       _leptonMvaSUSY17[10];   //[_nLight]
   double       _leptonMvaTTH17[10];   //[_nLight]
   double       _leptonMvatZqTTV16[10];   //[_nLight]
   double       _leptonMvatZqTTV17[10];   //[_nLight]
   bool         _lHNLoose[10];   //[_nLight]
   bool         _lHNFO[10];   //[_nLight]
   bool         _lHNTight[10];   //[_nLight]
   bool         _lEwkLoose[10];   //[_nL]
   bool         _lEwkFO[10];   //[_nL]
   bool         _lEwkTight[10];   //[_nL]
   bool         _lPOGVeto[10];   //[_nL]
   bool         _lPOGLoose[10];   //[_nL]
   bool         _lPOGMedium[10];   //[_nL]
   bool         _lPOGTight[10];   //[_nL]
   bool         _lPOGLooseWOIso[10];   //[_nLight]
   bool         _lPOGMediumWOIso[10];   //[_nLight]
   bool         _lPOGTightWOIso[10];   //[_nLight]
   bool         _tauMuonVeto[10];   //[_nL]
   bool         _tauEleVeto[10];   //[_nL]
   bool         _decayModeFindingNew[10];   //[_nL]
   bool         _tauVLooseMvaNew[10];   //[_nL]
   bool         _tauLooseMvaNew[10];   //[_nL]
   bool         _tauMediumMvaNew[10];   //[_nL]
   bool         _tauTightMvaNew[10];   //[_nL]
   bool         _tauVTightMvaNew[10];   //[_nL]
   bool         _tauVTightMvaOld[10];   //[_nL]
   double       _relIso[10];   //[_nLight]
   double       _relIso0p4[10];   //[_nMu]
   double       _relIso0p4MuDeltaBeta[10];   //[_nMu]
   double       _miniIso[10];   //[_nLight]
   double       _miniIsoCharged[10];   //[_nLight]
   double       _ptRel[10];   //[_nLight]
   double       _ptRatio[10];   //[_nLight]
   double       _closestJetCsvV2[10];   //[_nLight]
   double       _closestJetDeepCsv_b[10];   //[_nLight]
   double       _closestJetDeepCsv_bb[10];   //[_nLight]
   unsigned     _selectedTrackMult[10];   //[_nLight]
   bool         _lKVF_valid[10];
   double	    _lKVF_x[10];
   double	    _lKVF_y[10];
   double	    _lKVF_z[10];
   double	    _lKVF_cxx[10];
   double	    _lKVF_cyy[10];
   double	    _lKVF_czz[10];
   double	    _lKVF_cyx[10];
   double	    _lKVF_czy[10];
   double	    _lKVF_czx[10];
   double	    _lKVF_df[10];
   double	    _lKVF_chi2[10];
   unsigned	    _lKVF_ntracks[10];
   double       _lKVF_dRcut[10];
   double       _lKVF_trackPt[10][20];
   double       _lKVF_trackEta[10][20];
   double       _lKVF_trackPhi[10][20];
   double       _lKVF_trackE[10][20];
   double       _lKVF_trackdR[10][20];
   double       _lKVF_trackdxy[10][20];
   double       _lKVF_trackdz[10][20];
   unsigned     _IVF_nvertex;
   double       _IVF_x[50];
   double       _IVF_y[50];
   double       _IVF_z[50];
   double       _IVF_cx[50];
   double       _IVF_cy[50];
   double       _IVF_cz[50];
   double       _IVF_df[50];
   double       _IVF_chi2[50];
   unsigned     _IVF_ntracks[50];
   double       _IVF_trackpt[50][15];
   double       _IVF_tracketa[50][15];
   double       _IVF_trackphi[50][15];
   double       _IVF_trackE[50][15];
   double       _IVF_trackcharge[50][15];
   int          _lIVF_match[10];
   bool         _lGlobalMuon[10];                                                                       //muon speficic variables, also for displaced muon ID
   bool         _lTrackerMuon[10];
   double       _lInnerTrackValidFraction[10];
   double       _lGlobalTrackNormalizedChi2[10];
   double       _lCQChi2Position[10];
   double       _lCQTrackKink[10];
   unsigned     _lNumberOfMatchedStation[10];
   unsigned     _lNumberOfValidPixelHits[10];
   unsigned     _muNumberInnerHits[10];
   unsigned     _lTrackerLayersWithMeasurement[10];
   double       _lMuonSegComp[10];   //[_nMu]
   double       _lMuonTrackPt[10];   //[_nMu]
   double       _lMuonTrackPtErr[10];   //[_nMu]
   bool         _lIsPrompt[10];   //[_nL]
   int          _lMatchPdgId[10];   //[_nL]
   unsigned     _nPh;
   double       _phPt[10];   //[_nPh]
   double       _phEta[10];   //[_nPh]
   double       _phEtaSC[10];   //[_nPh]
   double       _phPhi[10];   //[_nPh]
   double       _phE[10];   //[_nPh]
   bool         _phCutBasedLoose[10];   //[_nPh]
   bool         _phCutBasedMedium[10];   //[_nPh]
   bool         _phCutBasedTight[10];   //[_nPh]
   double       _phMva[10];   //[_nPh]
   double       _phRandomConeChargedIsolation[10];   //[_nPh]
   double       _phChargedIsolation[10];   //[_nPh]
   double       _phNeutralHadronIsolation[10];   //[_nPh]
   double       _phPhotonIsolation[10];   //[_nPh]
   double       _phSigmaIetaIeta[10];   //[_nPh]
   double       _phSigmaIetaIphi[10];   //[_nPh]
   double       _phHadronicOverEm[10];   //[_nPh]
   bool         _phPassElectronVeto[10];   //[_nPh]
   bool         _phHasPixelSeed[10];   //[_nPh]
   bool         _phIsPrompt[10];   //[_nPh]
   int          _phMatchMCPhotonAN15165[10];   //[_nPh]
   int          _phMatchMCLeptonAN15165[10];   //[_nPh]
   int          _phMatchPdgId[10];   //[_nPh]
   unsigned     _nJets;
   double       _jetPt[20];   //[_nJets]
   double       _jetPt_JECUp[20];   //[_nJets]
   double       _jetPt_JECDown[20];   //[_nJets]
   double       _jetPt_Uncorrected[20];   //[_nJets]
   double       _jetPt_L1[20];   //[_nJets]
   double       _jetPt_L2[20];   //[_nJets]
   double       _jetPt_L3[20];   //[_nJets]
   double       _jetEta[20];   //[_nJets]
   double       _jetPhi[20];   //[_nJets]
   double       _jetE[20];   //[_nJets]
   double       _jetCsvV2[20];   //[_nJets]
   double       _jetDeepCsv_udsg[20];   //[_nJets]
   double       _jetDeepCsv_b[20];   //[_nJets]
   double       _jetDeepCsv_c[20];   //[_nJets]
   double       _jetDeepCsv_bb[20];   //[_nJets]
   unsigned     _jetHadronFlavor[20];   //[_nJets]
   bool         _jetIsLoose[20];   //[_nJets]
   bool         _jetIsTight[20];   //[_nJets]
   bool         _jetIsTightLepVeto[20];   //[_nJets]
   double       _jetNeutralHadronFraction[20];
   double       _jetChargedHadronFraction[20];
   double       _jetNeutralEmFraction[20];
   double       _jetChargedEmFraction[20];
   double       _jetHFHadronFraction[20];
   double       _jetHFEmFraction[20];
   double       _met;
   double       _metRaw;
   double       _metJECDown;
   double       _metJECUp;
   double       _metUnclDown;
   double       _metUnclUp;
   double       _metPhi;
   double       _metRawPhi;
   double       _metPhiJECDown;
   double       _metPhiJECUp;
   double       _metPhiUnclDown;
   double       _metPhiUnclUp;
   double       _metSignificance;

   /*int          _nDaughters;
   int          _jet_tag_for_daughters[300];   //[_nDaughters]
   int          _jet_daughter_pdgid[300];   //[_nDaughters]
   double       _jet_daughter_pt[300];   //[_nDaughters]
   double       _jet_daughter_eta[300];   //[_nDaughters]
   double       _jet_daughter_phi[300];   //[_nDaughters]
   double       _jet_daughter_energy[300];   //[_nDaughters]
*/
   // List of branches
   TBranch        *b__runNb;   //!
   TBranch        *b__lumiBlock;   //!
   TBranch        *b__eventNb;   //!
   TBranch        *b__nVertex;   //!
   TBranch        *b__BS_x;
   TBranch        *b__BS_y;
   TBranch        *b__BS_z;
   TBranch        *b__PV_x;
   TBranch        *b__PV_y;
   TBranch        *b__PV_z;
   TBranch        *b__nTrueInt;   //!
   TBranch        *b__weight;   //!
   TBranch        *b__lheHTIncoming;   //!
   TBranch        *b__ctauHN;   //!
   TBranch        *b__nLheWeights;   //!
   TBranch        *b__lheWeight;   //!
   TBranch        *b__ttgEventType;   //!
   TBranch        *b__zgEventType;   //!
   TBranch        *b__gen_met;   //!
   TBranch        *b__gen_metPhi;   //!
   TBranch        *b__gen_nPh;   //!
   TBranch        *b__gen_phPt;   //!
   TBranch        *b__gen_phEta;   //!
   TBranch        *b__gen_phPhi;   //!
   TBranch        *b__gen_phE;   //!
   TBranch        *b__gen_phMomPdg;   //!
   TBranch        *b__gen_phIsPrompt;   //!
   TBranch        *b__gen_phMinDeltaR;   //!
   TBranch        *b__gen_phPassParentage;   //!
   TBranch        *b__gen_nL;   //!
   TBranch        *b__gen_lPt;   //!
   TBranch        *b__gen_lEta;   //!
   TBranch        *b__gen_lPhi;   //!
   TBranch        *b__gen_lE;   //!
   TBranch        *b__gen_lFlavor;   //!
   TBranch        *b__gen_lCharge;   //!
   TBranch        *b__gen_lMomPdg;   //!
   TBranch        *b__gen_vertex_x;  //!
   TBranch        *b__gen_vertex_y;  //!
   TBranch        *b__gen_vertex_z;  //!
   TBranch        *b__gen_lIsPrompt;   //!
   TBranch        *b__gen_lMinDeltaR;   //!
   TBranch        *b__gen_lPassParentage;   //!
   TBranch        *b__gen_HT;   //!
   TBranch        *b__gen_nN;   //!
   TBranch        *b__gen_NPt;
   TBranch        *b__gen_NEta;
   TBranch        *b__gen_NPhi;
   TBranch        *b__gen_NE;
   TBranch        *b__gen_Nvertex_x;
   TBranch        *b__gen_Nvertex_y;
   TBranch        *b__gen_Nvertex_z;
   TBranch        *b__gen_nNPackedDtrs;
   TBranch        *b__gen_NPackedDtrsPt;
   TBranch        *b__gen_NPackedDtrsEta;
   TBranch        *b__gen_NPackedDtrsPhi;
   TBranch        *b__gen_NPackedDtrsE;
   TBranch        *b__gen_NPackedDtrsPdgId;
   TBranch        *b__gen_NPackedDtrsCharge;
   TBranch        *b_matches;
   TBranch        *b__gen_NPackedDtrsmineta;
   TBranch        *b__gen_NPackedDtrsminphi;
   TBranch        *b__gen_NPackedDtrsminpt;
   TBranch        *b__gen_NPackedDtrs_matchPt;
   TBranch        *b__gen_NPackedDtrs_matchEta;
   TBranch        *b__gen_NPackedDtrs_matchPhi;
   TBranch        *b__gen_NPackedDtrs_matchE;
   TBranch        *b__gen_NPackedDtrs_matchdxy;
   TBranch        *b__gen_NPackedDtrs_matchdz;
   TBranch        *b__gen_NPackedDtrs_matchcharge;
   TBranch        *b__gen_nNdaughters;   //!
   TBranch        *b__gen_Ndaughters_pdg;   //!
   TBranch        *b__gen_nstatus23;   //!
   TBranch        *b__gen_nstatus23_fromN;   //!
   TBranch        *b__gen_nstatus23_fromW;   //!
   TBranch        *b__gen_status23_pdg;   //!
   TBranch        *b__gen_status23_fromN_pdg;   //!
   TBranch        *b__gen_status23_fromW_pdg;   //!
   TBranch        *b__gen_nq;   //!
   TBranch        *b__gen_qPt;   //!
   TBranch        *b__gen_qEta;   //!
   TBranch        *b__gen_qPhi;   //!
   TBranch        *b__gen_qE;   //!
   TBranch        *b__gen_nq1dtr;   //!
   TBranch        *b__gen_q1dtr_status;   //!
   TBranch        *b__gen_q1dtr_pdgid;   //!
   TBranch        *b__gen_q1dtr_Pt;   //!
   TBranch        *b__gen_q1dtr_Eta;   //!
   TBranch        *b__gen_q1dtr_Phi;   //!
   TBranch        *b__gen_q1dtr_E;   //!
   TBranch        *b__gen_nq2dtr;   //!
   TBranch        *b__gen_q2dtr_status;   //!
   TBranch        *b__gen_q2dtr_pdgid;   //!
   TBranch        *b__gen_q2dtr_Pt;   //!
   TBranch        *b__gen_q2dtr_Eta;   //!
   TBranch        *b__gen_q2dtr_Phi;   //!
   TBranch        *b__gen_q2dtr_E;   //!
   TBranch        *b__HLT_Ele27_WPTight_Gsf;   //!
   TBranch        *b__HLT_Ele27_WPTight_Gsf_prescale;   //!
   TBranch        *b__HLT_IsoMu24;   //!
   TBranch        *b__HLT_IsoMu24_prescale;   //!
   TBranch        *b__HLT_IsoTkMu24;   //!
   TBranch        *b__HLT_IsoTkMu24_prescale;   //!
   //TBranch        *b__HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;   //!
   //TBranch        *b__HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_prescale;   //!
   //TBranch        *b__HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   //TBranch        *b__HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;   //!
   //TBranch        *b__HLT_Mu8_DiEle12_CaloIdL_TrackIdL;   //!
   //TBranch        *b__HLT_Mu8_DiEle12_CaloIdL_TrackIdL_prescale;   //!
   //TBranch        *b__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   //TBranch        *b__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_prescale;   //!
   //TBranch        *b__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;   //!
   //TBranch        *b__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_prescale;   //!
   //TBranch        *b__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   //TBranch        *b__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_prescale;   //!
   //TBranch        *b__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL;   //!
   //TBranch        *b__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_prescale;   //!
   //TBranch        *b__HLT_DiMu9_Ele9_CaloIdL_TrackIdL;   //!
   //TBranch        *b__HLT_DiMu9_Ele9_CaloIdL_TrackIdL_prescale;   //!
   //TBranch        *b__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;   //!
   //TBranch        *b__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_prescale;   //!
   //TBranch        *b__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;   //!
   //TBranch        *b__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;   //!
   //TBranch        *b__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;   //!
   //TBranch        *b__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;   //!
   //TBranch        *b__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;   //!
   //TBranch        *b__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_prescale;   //!
   //TBranch        *b__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;   //!
   //TBranch        *b__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;   //!
   //TBranch        *b__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL;   //!
   //TBranch        *b__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;   //!
   //TBranch        *b__HLT_TripleMu_12_10_5;   //!
   //TBranch        *b__HLT_TripleMu_12_10_5_prescale;   //!
   //TBranch        *b__passMETFilters;   //!
   //TBranch        *b__Flag_HBHENoiseFilter;   //!
   //TBranch        *b__Flag_HBHENoiseIsoFilter;   //!
   //TBranch        *b__Flag_EcalDeadCellTriggerPrimitiveFilter;   //!
   //TBranch        *b__Flag_goodVertices;   //!
   //TBranch        *b__Flag_globalTightHalo2016Filter;   //!
   //TBranch        *b__Flag_BadPFMuonFilter;   //!
   //TBranch        *b__Flag_BadChargedCandidateFilter;   //!
   //TBranch        *b__HLT_Ele105_CaloIdVT_GsfTrkIdT;   //!
   //TBranch        *b__HLT_Ele105_CaloIdVT_GsfTrkIdT_prescale;   //!
   //TBranch        *b__HLT_Ele115_CaloIdVT_GsfTrkIdT;   //!
   //TBranch        *b__HLT_Ele115_CaloIdVT_GsfTrkIdT_prescale;   //!
   //TBranch        *b__HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   //TBranch        *b__HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;   //!
   //TBranch        *b__HLT_DoubleEle33_CaloIdL_GsfTrkIdVL;   //!
   //TBranch        *b__HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_prescale;   //!
   //TBranch        *b__HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL;   //!
   //TBranch        *b__HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_prescale;   //!
   //TBranch        *b__HLT_Mu50;   //!
   //TBranch        *b__HLT_Mu50_prescale;   //!
   //TBranch        *b__HLT_TkMu50;   //!
   //TBranch        *b__HLT_TkMu50_prescale;   //!
   //TBranch        *b__HLT_Mu45_eta2p1;   //!
   //TBranch        *b__HLT_Mu45_eta2p1_prescale;   //!
   //TBranch        *b__HLT_Mu30_TkMu11;   //!
   //TBranch        *b__HLT_Mu30_TkMu11_prescale;   //!
   TBranch        *b__nL;   //!
   TBranch        *b__nMu;   //!
   TBranch        *b__nEle;   //!
   TBranch        *b__nLight;   //!
   TBranch        *b__nTau;   //!
   TBranch        *b__lPt;   //!
   TBranch        *b__lEta;   //!
   TBranch        *b__lEtaSC;   //!
   TBranch        *b__lPhi;   //!
   TBranch        *b__lE;   //!
   TBranch        *b__lFlavor;   //!
   TBranch        *b__lCharge;   //!
   TBranch        *b__dxy;   //!
   TBranch        *b__dz;   //!
   TBranch        *b__3dIP;   //!
   TBranch        *b__3dIPSig;   //!
   TBranch        *b__lElectronMva;   //!
   TBranch        *b__lElectronMvaHZZ;   //!
   TBranch        *b__lElectronPassEmu;   //!
   TBranch        *b__lElectronPassConvVeto;   //!
   TBranch        *b__lElectronChargeConst;   //!
   TBranch        *b__lElectronMissingHits;   //!
   TBranch        *b__lEleIsEB;                                                                         //electron specific variables for displaced electron ID
   TBranch        *b__lEleIsEE;
   TBranch        *b__lEleSuperClusterOverP;
   TBranch        *b__lEleEcalEnergy;
   TBranch        *b__lElefull5x5SigmaIetaIeta;
   TBranch        *b__lEleDEtaInSeed;
   TBranch        *b__lEleDeltaPhiSuperClusterTrackAtVtx;
   TBranch        *b__lElehadronicOverEm;
   TBranch        *b__lEleInvMinusPInv;
   TBranch        *b__eleNumberInnerHitsMissing;
   TBranch        *b__leptonMvaSUSY16;   //!
   TBranch        *b__leptonMvaTTH16;   //!
   TBranch        *b__leptonMvaSUSY17;   //!
   TBranch        *b__leptonMvaTTH17;   //!
   TBranch        *b__leptonMvatZqTTV16;   //!
   TBranch        *b__leptonMvatZqTTV17;   //!
   TBranch        *b__lHNLoose;   //!
   TBranch        *b__lHNFO;   //!
   TBranch        *b__lHNTight;   //!
   TBranch        *b__lEwkLoose;   //!
   TBranch        *b__lEwkFO;   //!
   TBranch        *b__lEwkTight;   //!
   TBranch        *b__lPOGVeto;   //!
   TBranch        *b__lPOGLoose;   //!
   TBranch        *b__lPOGMedium;   //!
   TBranch        *b__lPOGTight;   //!
   TBranch        *b__lPOGLooseWOIso;   //!
   TBranch        *b__lPOGMediumWOIso;   //!
   TBranch        *b__lPOGTightWOIso;   //!
   TBranch        *b__tauMuonVeto;   //!
   TBranch        *b__tauEleVeto;   //!
   TBranch        *b__decayModeFindingNew;   //!
   TBranch        *b__tauVLooseMvaNew;   //!
   TBranch        *b__tauLooseMvaNew;   //!
   TBranch        *b__tauMediumMvaNew;   //!
   TBranch        *b__tauTightMvaNew;   //!
   TBranch        *b__tauVTightMvaNew;   //!
   TBranch        *b__tauVTightMvaOld;   //!
   TBranch        *b__relIso;   //!
   TBranch        *b__relIso0p4;   //!
   TBranch        *b__relIso0p4MuDeltaBeta;   //!
   TBranch        *b__miniIso;   //!
   TBranch        *b__miniIsoCharged;   //!
   TBranch        *b__ptRel;   //!
   TBranch        *b__ptRatio;   //!
   TBranch        *b__closestJetCsvV2;   //!
   TBranch        *b__closestJetDeepCsv_b;   //!
   TBranch        *b__closestJetDeepCsv_bb;   //!
   TBranch        *b__selectedTrackMult;   //!
   TBranch        *b__lKVF_valid;
   TBranch	      *b__lKVF_x;
   TBranch	      *b__lKVF_y;
   TBranch	      *b__lKVF_z;
   TBranch	      *b__lKVF_cxx;
   TBranch	      *b__lKVF_cyy;
   TBranch	      *b__lKVF_czz;
   TBranch	      *b__lKVF_cyx;
   TBranch	      *b__lKVF_czy;
   TBranch	      *b__lKVF_czx;
   TBranch	      *b__lKVF_df;
   TBranch	      *b__lKVF_chi2;
   TBranch        *b__lKVF_ntracks;
   TBranch        *b__lKVF_dRcut;
   TBranch        *b__lKVF_trackPt;
   TBranch        *b__lKVF_trackEta;
   TBranch        *b__lKVF_trackPhi;
   TBranch        *b__lKVF_trackE;
   TBranch        *b__lKVF_trackdR;
   TBranch        *b__lKVF_trackdxy;
   TBranch        *b__lKVF_trackdz;
   TBranch        *b__IVF_nvertex;
   TBranch        *b__IVF_x;
   TBranch        *b__IVF_y;
   TBranch        *b__IVF_z;
   TBranch        *b__IVF_cx;
   TBranch        *b__IVF_cy;
   TBranch        *b__IVF_cz;
   TBranch        *b__IVF_df;
   TBranch        *b__IVF_chi2;
   TBranch        *b__IVF_ntracks;
   TBranch        *b__IVF_trackpt;
   TBranch        *b__IVF_tracketa;
   TBranch        *b__IVF_trackphi;
   TBranch        *b__IVF_trackE;
   TBranch        *b__IVF_trackcharge;
   TBranch        *b__lIVF_match;
   TBranch        *b__lGlobalMuon;                                                                       //muon speficic variables, also for displaced muon ID
   TBranch        *b__lTrackerMuon;
   TBranch        *b__lInnerTrackValidFraction;
   TBranch        *b__lGlobalTrackNormalizedChi2;
   TBranch        *b__lCQChi2Position;
   TBranch        *b__lCQTrackKink;
   TBranch        *b__lNumberOfMatchedStation;
   TBranch        *b__lNumberOfValidPixelHits;
   TBranch        *b__muNumberInnerHits;
   TBranch        *b__lTrackerLayersWithMeasurement;
   TBranch        *b__lMuonSegComp;   //!
   TBranch        *b__lMuonTrackPt;   //!
   TBranch        *b__lMuonTrackPtErr;   //!
   TBranch        *b__lIsPrompt;   //!
   TBranch        *b__lMatchPdgId;   //!
   TBranch        *b__nPh;   //!
   TBranch        *b__phPt;   //!
   TBranch        *b__phEta;   //!
   TBranch        *b__phEtaSC;   //!
   TBranch        *b__phPhi;   //!
   TBranch        *b__phE;   //!
   TBranch        *b__phCutBasedLoose;   //!
   TBranch        *b__phCutBasedMedium;   //!
   TBranch        *b__phCutBasedTight;   //!
   TBranch        *b__phMva;   //!
   TBranch        *b__phRandomConeChargedIsolation;   //!
   TBranch        *b__phChargedIsolation;   //!
   TBranch        *b__phNeutralHadronIsolation;   //!
   TBranch        *b__phPhotonIsolation;   //!
   TBranch        *b__phSigmaIetaIeta;   //!
   TBranch        *b__phSigmaIetaIphi;   //!
   TBranch        *b__phHadronicOverEm;   //!
   TBranch        *b__phPassElectronVeto;   //!
   TBranch        *b__phHasPixelSeed;   //!
   TBranch        *b__phIsPrompt;   //!
   TBranch        *b__phMatchMCPhotonAN15165;   //!
   TBranch        *b__phMatchMCLeptonAN15165;   //!
   TBranch        *b__phMatchPdgId;   //!
   TBranch        *b__nJets;   //!
   TBranch        *b__jetPt;   //!
   TBranch        *b__jetPt_JECUp;   //!
   TBranch        *b__jetPt_JECDown;   //!
   TBranch        *b__jetPt_Uncorrected;
   TBranch        *b__jetPt_L1;
   TBranch        *b__jetPt_L2;
   TBranch        *b__jetPt_L3;
   TBranch        *b__jetEta;   //!
   TBranch        *b__jetPhi;   //!
   TBranch        *b__jetE;   //!
   TBranch        *b__jetCsvV2;   //!
   TBranch        *b__jetDeepCsv_udsg;   //!
   TBranch        *b__jetDeepCsv_b;   //!
   TBranch        *b__jetDeepCsv_c;   //!
   TBranch        *b__jetDeepCsv_bb;   //!
   TBranch        *b__jetHadronFlavor;   //!
   TBranch        *b__jetIsLoose;   //!
   TBranch        *b__jetIsTight;   //!
   TBranch        *b__jetIsTightLepVeto;   //!
   TBranch        *b__jetNeutralHadronFraction;   //!
   TBranch        *b__jetChargedHadronFraction;   //!
   TBranch        *b__jetNeutralEmFraction;   //!
   TBranch        *b__jetChargedEmFraction;   //!
   TBranch        *b__jetHFHadronFraction;   //!
   TBranch        *b__jetHFEmFraction;   //!
   TBranch        *b__met;   //!
   TBranch        *b__metRaw;
   TBranch        *b__metJECDown;   //!
   TBranch        *b__metJECUp;   //!
   TBranch        *b__metUnclDown;   //!
   TBranch        *b__metUnclUp;   //!
   TBranch        *b__metPhi;   //!
   TBranch        *b__metRawPhi;   //!
   TBranch        *b__metPhiJECDown;   //!
   TBranch        *b__metPhiJECUp;   //!
   TBranch        *b__metPhiUnclDown;   //!
   TBranch        *b__metPhiUnclUp;   //!
   TBranch        *b__metSignificance;   //!
/*   TBranch        *b__nDaughters;   //!
   TBranch        *b__jet_tag_for_daughters;   //!
   TBranch        *b__jet_daughter_pdgid;   //!
   TBranch        *b__jet_daughter_pt;   //!
   TBranch        *b__jet_daughter_eta;   //!
   TBranch        *b__jet_daughter_phi;   //!
   TBranch        *b__jet_daughter_energy;   //!
*/   
   std::map<TString, TH1*>::iterator it;
   std::map<TString, TH2*>::iterator it2D;
   Double_t event_weight;
   TString sampleflavor;
   
   // lepton and jet ID and cleaning bool arrays
   bool jet_clean_loose[20], jet_clean_full[20], jet_clean_displ[20], jet_clean_full_displ[20];
   bool ele_clean_loose[10], ele_clean_full[10], ele_clean_displ[10], ele_clean_full_displ[10];
   bool fullElectronID[10], looseElectronID[10], displElectronID[10], fullMuonID[10], looseMuonID[10], displMuonID[10], fullJetID[10], pogmediumElectronID[10], pogmediumMuonID[10];

   // gen variables related to truth of event
   int i_gen_l1;
   int i_gen_l2;
   int _gen_Nmass;
   //int i_l1; might add these later, through geometric match with i_gen_l1or2, find i_l1or2
   //int i_l2;
   bool leading_is_l1;
   bool subleading_is_l2; 

   // signal region lepton indices 
   int i_leading_e;
   int i_subleading_displ_e;
   int i_leading_mu;
   int i_subleading_displ_mu;
   
   // gen indices corresponding to signal region leptons (geometric)
   int i_gen_leading_e;
   int i_gen_subleading_displ_e;
   int i_gen_leading_mu;
   int i_gen_subleading_displ_mu;
   
   // extra lepton indices
   int i_subleading_e;
   int i_leading_pogmedium_e;
   int i_subleading_mu;
   int i_leading_pogmedium_mu;
   
   // jet indices
   int i_leading_jet;
   int i_subleading_jet;
   int i_thirdleading_jet;
   int i_closel2_jet;

   double g_mll;
   double g_dphill;
   double g_dRll;

   // signal region booleans: ee
   bool _trige;
   bool _1e;
   bool _1e1disple;
   bool _1e1displevtx;
   bool _1e1displedispl;
   bool _1e1disple0adde;
   //bool _1e1disple0jet;
   bool _1e1displemll;
   bool _1e1displedphi;

   // extra booleans: ee
   bool _1e1displedR;
   bool _1pogmediume;

   // old booleans: ee
   bool _1e0jet;
   bool _1e1jet;
   bool _1e2jet;
   bool _2e0jet;
   bool _2e1jet;
   bool _2e2jet;
   bool _1e1disple1jet;
   bool _1e1disple2jet;

   // signal region booleans: mumu
   bool _trigmu;
   bool _1mu;
   bool _1mu1displmu;
   bool _1mu1displmuvtx;
   bool _1mu1displmudispl;
   bool _1mu1displmu0addmu;
   //bool _1mu1displmu0jet;
   bool _1mu1displmumll;
   bool _1mu1displmudphi;

   // extra booleans: mumu
   bool _1mu1displmudR;
   bool _1pogmediummu;
   
   // old booleans: mumu
   bool _1mu0jet;
   bool _1mu1jet;
   bool _1mu2jet;
   bool _2mu0jet;
   bool _2mu1jet;
   bool _2mu2jet;
   bool _1mu1displmu1jet;
   bool _1mu1displmu2jet;

   int count_IVFmatch_larger_than_IVF_nvertex;

   // functions
   // in src/full_analyzer_constructor.cc
   full_analyzer(TTree *tree=0);
   virtual ~full_analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   // in src/full_analyzer.cc, the main code body
   virtual void     run_over_file(TString, double, int, int, int);

   //in src/leptonID.cc and jetID.cc
   virtual void     get_electronID(bool*);
   virtual void     get_pogmedium_electronID(bool*);
   virtual void     get_displ_electronID(bool*);
   virtual void     get_loose_electronID(bool*);
   virtual void     get_muonID(bool*);
   virtual void     get_pogmedium_muonID(bool*);
   virtual void     get_displ_muonID(bool*);
   virtual void     get_loose_muonID(bool*);
   virtual void     get_jetID(bool*);
   virtual void     get_clean_jets(bool*, bool*, bool*);
   virtual void     get_clean_ele(bool*, bool*);
   virtual int      find_leading_e(bool*, bool*);
   virtual int      find_leading_mu(bool*);
   virtual int      find_leading_jet(bool*, bool*);
   virtual int      find_subleading_e(bool*, bool*, int);
   virtual int      find_subleading_mu(bool*, int);
   virtual int      find_subleading_jet(bool*, bool*, int);
   virtual int      find_thirdleading_jet(bool*, bool*, int, int);
   virtual int      find_jet_closest_to_lepton(bool*, int);
   virtual int      find_gen_lep(int i_lep);
   virtual void     find_gen_l1_and_l2();
   virtual void     match_gen_and_reco(int);
   virtual double   get_dR_lepton_jet(TLorentzVector, TLorentzVector);
   virtual double   get_dR_lepton_jet(int, TLorentzVector&);
   virtual double   get_dR_lepton_jet(int, int);
   virtual double   get_IVF_SVgenreco(int, int);
   virtual double   get_IVF_SVgenreco_2D(int, int);
   virtual double   get_IVF_PVSVdist(int);
   virtual double   get_IVF_PVSVdist_2D(int);
   virtual double   get_KVF_SVgenreco(int, int);
   virtual double   get_KVF_SVgenreco_2D(int, int);
   virtual double   get_KVF_PVSVdist(int);
   virtual double   get_KVF_PVSVdist_2D(int);
   virtual double   get_PVSVdist_gen(int);
   virtual double   get_PVSVdist_gen_2D(int);

   // in src/vtxID.cc
   virtual int      find_vtx_matching_to_lepton(int);
   virtual void     fix_validity_of_lIVF_match();

   // in src/signal_regions.cc
   virtual void     signal_regions();
   virtual bool     leadptcut(int);
   virtual bool     no_additional_leptons();
   virtual bool     mllcut(int, int, double);
   virtual double   get_mll(int, int);
   virtual bool     dRcut(int, int, double, double);
   virtual double   get_dRll(int, int);
   virtual bool     dphicut(int, int, double);
   virtual double   get_dphill(int, int);
   virtual void     init_sigreg_fraction(std::map<TString, TH1*>*);
   virtual void     fill_sigreg_fraction(std::map<TString, TH1*>*);
   virtual void     reset_signal_regions();

   // in src/print_tables.cc
   virtual void     print_table();
   
   // in src/histo_functions.cc
   virtual void     add_histograms(std::map<TString, TH1*>*, std::map<TString, TH2*>*, TString);
   virtual void     fill_histograms(std::map<TString, TH1*>*, std::map<TString, TH2*>*, TString, int, int);
   virtual void     fill_cutflow_e(std::map<TString, TH1*>*, TString);
   virtual void     fill_cutflow_mu(std::map<TString, TH1*>*, TString);
   virtual void     fill_KVF_histograms(std::map<TString, TH1*>*, std::map<TString, TH2*>*, TString, int, int, int);
   virtual void     fill_IVF_histograms(std::map<TString, TH1*>*, std::map<TString, TH2*>*, TString, int, int, int);
   virtual void     fill_corrl2_eff(std::map<TString, TH1*>*, TString, int, int);
   virtual void     fill_KVF_eff(std::map<TString, TH1*>*, TString, int, int, int);
   virtual void     fill_IVF_eff(std::map<TString, TH1*>*, TString, int, int, int);
   //virtual void     fill_ID_histos(std::map<TString, TH1*>*, TString);
   virtual void     give_alphanumeric_labels(std::map<TString, TH1*>*, TString);
   
   // in src/jet_histograms.cc
   virtual void     add_jet_histograms(std::map<TString, TH1*>*, TString);
   virtual void     fill_jet_histograms(std::map<TString, TH1*>*, TString, int);

   // in src/HLT_eff.cc
   virtual void     init_HLT_efficiency(std::map<TString, TH1*>*, TString);
   virtual void     init_HLT_allevents_efficiency(std::map<TString, TH1*>*, TString);
   virtual void     fill_HLT_efficiency(std::map<TString, TH1*>*, TString, bool, bool);
   virtual void     fill_HLT_allevents_efficiency(std::map<TString, TH1*>*, TString);

   // in src/HNL_MC_check.cc
   virtual void     init_HNL_MC_check(std::map<TString, TH1*>*, std::map<TString, TH2*>*);
   virtual void     fill_HNL_MC_check(std::map<TString, TH1*>*, std::map<TString, TH2*>*);

   // in src/helper_histo_functions.cc
   virtual void     make_logscale(double*, int, double, double);
   virtual double   calc_betagamma(int, double);
};

#endif
