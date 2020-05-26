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
#include <fstream>
#include <sstream>
#include <cmath>

#include <string>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TSystem.h>
#include <TGraphAsymmErrors.h>

// Header file for the classes stored in the TTree if any.

// helper functions
#include "../interface/helper_histo_functions.h"
#include "../interface/HNLtagger.h"
#include "../interface/HNL_parameters.h"
#include "../interface/BkgEstimator.h"
#include "../interface/bTagWP.h"
#include "../helpertools/PFNEvaluation/PFNReader.h"
#include "../helpertools/LorentzVector/LorentzVector.h"
#include "../helpertools/PUWeightReader/PUWeightReader.h"
#include "../helpertools/LSFReader/LSFReader.h"

class full_analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   ULong64_t       _runNb;
   ULong64_t       _lumiBlock;
   ULong64_t       _eventNb;
   UChar_t         _nVertex;
   Bool_t          _is2017;
   Bool_t          _is2018;
   Double_t        _BS_x;
   Double_t        _BS_y;
   Double_t        _BS_z;
   Double_t        _PV_x;
   Double_t        _PV_y;
   Double_t        _PV_z;
   Float_t         _nTrueInt;
   Double_t        _weight;
   Double_t        _lheHTIncoming;
   Double_t        _ctauHN;
   unsigned        _nLheWeights;
   Double_t        _lheWeight[110];   //[_nLheWeights]
   unsigned        _ttgEventType;
   unsigned        _zgEventType;
   Double_t        _gen_met;
   Double_t        _gen_metPhi;
   unsigned        _gen_nPh;
   Double_t        _gen_phPt[20];   //[_gen_nPh]
   Double_t        _gen_phEta[20];   //[_gen_nPh]
   Double_t        _gen_phPhi[20];   //[_gen_nPh]
   Double_t        _gen_phE[20];   //[_gen_nPh]
   Int_t           _gen_phMomPdg[20];   //[_gen_nPh]
   Bool_t          _gen_phIsPrompt[20];   //[_gen_nPh]
   Double_t        _gen_phMinDeltaR[20];   //[_gen_nPh]
   Bool_t          _gen_phPassParentage[20];   //[_gen_nPh]
   unsigned        _gen_nL;
   Double_t        _gen_lPt[20];   //[_gen_nL]
   Double_t        _gen_lEta[20];   //[_gen_nL]
   Double_t        _gen_lPhi[20];   //[_gen_nL]
   Double_t        _gen_lE[20];   //[_gen_nL]
   unsigned        _gen_lFlavor[20];   //[_gen_nL]
   Int_t           _gen_lCharge[20];   //[_gen_nL]
   Int_t           _gen_lMomPdg[20];   //[_gen_nL]
   Double_t        _gen_vertex_x[20];
   Double_t        _gen_vertex_y[20];
   Double_t        _gen_vertex_z[20];
   Bool_t          _gen_lIsPrompt[20];   //[_gen_nL]
   Double_t        _gen_lMinDeltaR[20];   //[_gen_nL]
   Bool_t          _gen_lPassParentage[20];   //[_gen_nL]
   Double_t        _gen_HT;
   Bool_t          _HLT_Ele27_WPTight_Gsf;
   Int_t           _HLT_Ele27_WPTight_Gsf_prescale;
   Bool_t          _HLT_Ele32_WPTight_Gsf;
   Int_t           _HLT_Ele32_WPTight_Gsf_prescale;
   Bool_t          _HLT_IsoMu24;
   Int_t           _HLT_IsoMu24_prescale;
   Bool_t          _HLT_IsoTkMu24;
   Int_t           _HLT_IsoTkMu24_prescale;
   Bool_t          _passTrigger_m;
   Bool_t          _passTrigger_e;
   Bool_t          _passTrigger_mm;
   Bool_t          _passTrigger_ee;
   //Bool_t          _HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;
   //Int_t           _HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_prescale;
   //Bool_t          _HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   //Int_t           _HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
   //Bool_t          _HLT_Mu8_DiEle12_CaloIdL_TrackIdL;
   //Int_t           _HLT_Mu8_DiEle12_CaloIdL_TrackIdL_prescale;
   //Bool_t          _HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
   //Int_t           _HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
   //Bool_t          _HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
   //Int_t           _HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_prescale;
   //Bool_t          _HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ;
   //Int_t           _HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
   //Bool_t          _HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL;
   //Int_t           _HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_prescale;
   //Bool_t          _HLT_DiMu9_Ele9_CaloIdL_TrackIdL;
   //Int_t           _HLT_DiMu9_Ele9_CaloIdL_TrackIdL_prescale;
   //Bool_t          _HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
   //Int_t           _HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_prescale;
   //Bool_t          _HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
   //Int_t           _HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;
   //Bool_t          _HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
   //Int_t           _HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;
   //Bool_t          _HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
   //Int_t           _HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_prescale;
   //Bool_t          _HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
   //Int_t           _HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;
   //Bool_t          _HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
   //Int_t           _HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;
   //Bool_t          _HLT_TripleMu_12_10_5;
   //Int_t           _HLT_TripleMu_12_10_5_prescale;
   Bool_t          _passMETFilters;
   //Bool_t          _Flag_HBHENoiseFilter;
   //Bool_t          _Flag_HBHENoiseIsoFilter;
   //Bool_t          _Flag_EcalDeadCellTriggerPrimitiveFilter;
   //Bool_t          _Flag_goodVertices;
   //Bool_t          _Flag_BadPFMuonFilter;
   //Bool_t          _Flag_BadChargedCandidateFilter;
   //Bool_t          _Flag_globalTightHalo2016Filter;
   //Bool_t          _HLT_Ele105_CaloIdVT_GsfTrkIdT;
   //Int_t           _HLT_Ele105_CaloIdVT_GsfTrkIdT_prescale;
   //Bool_t          _HLT_Ele115_CaloIdVT_GsfTrkIdT;
   //Int_t           _HLT_Ele115_CaloIdVT_GsfTrkIdT_prescale;
   //Bool_t          _HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   //Int_t           _HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
   //Bool_t          _HLT_DoubleEle33_CaloIdL_GsfTrkIdVL;
   //Int_t           _HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_prescale;
   //Bool_t          _HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL;
   //Int_t           _HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_prescale;
   //Bool_t          _HLT_Mu50;
   //Int_t           _HLT_Mu50_prescale;
   //Bool_t          _HLT_TkMu50;
   //Int_t           _HLT_TkMu50_prescale;
   //Bool_t          _HLT_Mu45_eta2p1;
   //Int_t           _HLT_Mu45_eta2p1_prescale;
   //Bool_t          _HLT_Mu30_TkMu11;
   //Int_t           _HLT_Mu30_TkMu11_prescale;
   unsigned         _nL;
   unsigned         _nMu;
   unsigned         _nEle;
   unsigned         _nLight;
   unsigned         _nTau;
   Double_t        _lPt[10];   //[_nL]
   Double_t        _lEta[10];   //[_nL]
   Double_t        _lEtaSC[10];   //[_nLight]
   Double_t        _lPhi[10];   //[_nL]
   Double_t        _lE[10];   //[_nL]
   unsigned        _lFlavor[10];   //[_nL]
   Int_t           _lCharge[10];   //[_nL]
   Double_t        _dxy[10];   //[_nL]
   Double_t        _dz[10];   //[_nL]
   Double_t        _3dIP[10];   //[_nL]
   Double_t        _3dIPSig[10];   //[_nL]
   Double_t        _lElectronSummer16MvaGP[10];
   Double_t        _lElectronSummer16MvaHZZ[10];
   Double_t        _lElectronMvaFall17v1NoIso[10];
   Double_t        _lElectronMvaFall17Iso[10];
   Double_t        _lElectronMvaFall17NoIso[10];
   Bool_t          _lElectronPassEmu[10];   //[_nLight]
   Bool_t          _lElectronPassConvVeto[10];   //[_nLight]
   Bool_t          _lElectronChargeConst[10];   //[_nLight]
   unsigned        _lElectronMissingHits[10];   //[_nLight]
   Bool_t          _lElectronIsEB[10];                                                                         //electron specific variables for displaced electron ID
   Bool_t          _lElectronIsEE[10];
   Double_t        _lElectronSuperClusterOverP[10];
   Double_t        _lElectronEcalEnergy[10];
   Double_t        _lElectronSigmaIetaIeta[10];
   Double_t        _lElectronDEtaInSeed[10];
   Double_t        _lElectronDeltaPhiSuperClusterTrack[10];
   Double_t        _lElectronDeltaEtaSuperClusterTrack[10];
   Double_t        _lElectronHOverE[10];
   Double_t        _lElectronEInvMinusPInv[10];
   Double_t        _lElectronNumberInnerHitsMissing[10];
   Double_t        _leptonMvatZq[10];
   Double_t        _leptonMvaTTH[10];
   Double_t        _leptonMvaTOP[10];
   Double_t        _leptonMvaSUSY16[10];   //[_nLight]
   Double_t        _leptonMvaTTH16[10];   //[_nLight]
   Double_t        _leptonMvaSUSY17[10];   //[_nLight]
   Double_t        _leptonMvaTTH17[10];   //[_nLight]
   Double_t        _leptonMvatZqTTV16[10];   //[_nLight]
   Double_t        _leptonMvatZqTTV17[10];   //[_nLight]
   Bool_t          _lHNLoose[10];   //[_nLight]
   Bool_t          _lHNFO[10];   //[_nLight]
   Bool_t          _lHNTight[10];   //[_nLight]
   Bool_t          _lEwkLoose[10];   //[_nL]
   Bool_t          _lEwkFO[10];   //[_nL]
   Bool_t          _lEwkTight[10];   //[_nL]
   Bool_t          _lPOGVeto[10];   //[_nL]
   Bool_t          _lPOGLoose[10];   //[_nL]
   Bool_t          _lPOGMedium[10];   //[_nL]
   Bool_t          _lPOGTight[10];   //[_nL]
   Bool_t          _tauMuonVeto[10];   //[_nL]
   Bool_t          _tauEleVeto[10];   //[_nL]
   Bool_t          _decayModeFindingNew[10];   //[_nL]
   Bool_t          _tauVLooseMvaNew[10];   //[_nL]
   Bool_t          _tauLooseMvaNew[10];   //[_nL]
   Bool_t          _tauMediumMvaNew[10];   //[_nL]
   Bool_t          _tauTightMvaNew[10];   //[_nL]
   Bool_t          _tauVTightMvaNew[10];   //[_nL]
   Bool_t          _tauVTightMvaOld[10];   //[_nL]
   Double_t        _relIso[10];   //[_nLight]
   Double_t        _relIso0p4[10];   //[_nMu]
   Double_t        _relIso0p4MuDeltaBeta[10];   //[_nMu]
   Double_t        _miniIso[10];   //[_nLight]
   Double_t        _miniIsoCharged[10];   //[_nLight]
   Double_t        _ptRel[10];   //[_nLight]
   Double_t        _ptRatio[10];   //[_nLight]
   Double_t        _closestJetCsvV2[10];   //[_nLight]
   Double_t        _closestJetDeepCsv_b[10];   //[_nLight]
   Double_t        _closestJetDeepCsv_bb[10];   //[_nLight]
   Double_t        _closestJetDeepCsv[10];   //[_nLight]
   Double_t        _closestJetDeepFlavor_b[10];
   Double_t        _closestJetDeepFlavor_bb[10];
   Double_t        _closestJetDeepFlavor_lepb[10];
   Double_t        _closestJetDeepFlavor[10];
   unsigned        _selectedTrackMult[10];   //[_nLight]
   Bool_t          _lGlobalMuon[10];                                                                       //muon speficic variables, also for displaced muon ID
   Bool_t          _lTrackerMuon[10];
   Double_t        _lInnerTrackValidFraction[10];
   Double_t        _lGlobalTrackNormalizedChi2[10];
   Double_t        _lCQChi2Position[10];
   Double_t        _lCQTrackKink[10];
   unsigned        _lNumberOfMatchedStation[10];
   unsigned        _lNumberOfValidPixelHits[10];
   unsigned        _lNumberOfValidTrackerHits[10];
   unsigned        _muNumberInnerHits[10];
   unsigned        _lTrackerLayersWithMeasurement[10];
   Double_t        _lMuonSegComp[10];   //[_nMu]
   Double_t        _lMuonTrackPt[10];   //[_nMu]
   Double_t        _lMuonTrackPtErr[10];   //[_nMu]
   Int_t           _lMuonTimenDof[10];
   Double_t        _lMuonTime[10];
   Double_t        _lMuonTimeErr[10];
   Int_t           _lMuonRPCTimenDof[10];
   Double_t        _lMuonRPCTime[10];
   Double_t        _lMuonRPCTimeErr[10];
   Bool_t          _lIsPrompt[10];   //[_nL]
   Int_t           _lMatchPdgId[10];   //[_nL]
   Int_t           _lMatchCharge[10];
   unsigned        _tauGenStatus[10];
   Int_t           _lMomPdgId[10];
   unsigned        _lProvenance[10];
   unsigned        _lProvenanceCompressed[10];
   unsigned        _lProvenanceConversion[10];
   unsigned        _nPh;
   Double_t        _phPt[10];   //[_nPh]
   Double_t        _phEta[10];   //[_nPh]
   Double_t        _phEtaSC[10];   //[_nPh]
   Double_t        _phPhi[10];   //[_nPh]
   Double_t        _phE[10];   //[_nPh]
   Bool_t          _phCutBasedLoose[10];   //[_nPh]
   Bool_t          _phCutBasedMedium[10];   //[_nPh]
   Bool_t          _phCutBasedTight[10];   //[_nPh]
   Double_t        _phMva[10];   //[_nPh]
   Double_t        _phRandomConeChargedIsolation[10];   //[_nPh]
   Double_t        _phChargedIsolation[10];   //[_nPh]
   Double_t        _phNeutralHadronIsolation[10];   //[_nPh]
   Double_t        _phPhotonIsolation[10];   //[_nPh]
   Double_t        _phSigmaIetaIeta[10];   //[_nPh]
   Double_t        _phHadronicOverEm[10];   //[_nPh]
   Bool_t          _phPassElectronVeto[10];   //[_nPh]
   Bool_t          _phHasPixelSeed[10];   //[_nPh]
   Bool_t          _phIsPrompt[10];   //[_nPh]
   Int_t           _phMatchPdgId[10];   //[_nPh]
   unsigned        _nJets;
   Double_t        _jetPt[20];   //[_nJets]
   Double_t        _jetPt_JECUp[20];   //[_nJets]
   Double_t        _jetPt_JECDown[20];   //[_nJets]
   Double_t        _jetPt_Uncorrected[20];   //[_nJets]
   Double_t        _jetPt_L1[20];   //[_nJets]
   Double_t        _jetPt_L2[20];   //[_nJets]
   Double_t        _jetPt_L3[20];   //[_nJets]
   Double_t        _jetEta[20];   //[_nJets]
   Double_t        _jetPhi[20];   //[_nJets]
   Double_t        _jetE[20];   //[_nJets]
   Double_t        _jetCsvV2[20];   //[_nJets]
   Double_t        _jetDeepCsv_udsg[20];   //[_nJets]
   Double_t        _jetDeepCsv_b[20];   //[_nJets]
   Double_t        _jetDeepCsv_c[20];   //[_nJets]
   Double_t        _jetDeepCsv_bb[20];   //[_nJets]
   Double_t        _jetDeepCsv[20];   //[_nJets]
   Double_t        _jetDeepFlavor_b[20];
   Double_t        _jetDeepFlavor_bb[20];
   Double_t        _jetDeepFlavor_lepb[20];
   Double_t        _jetDeepFlavor[20];
   Double_t        _jetDeepFlavor_c[20];
   Double_t        _jetDeepFlavor_uds[20];
   Double_t        _jetDeepFlavor_g[20];
   unsigned        _jetHadronFlavor[20];   //[_nJets]
   Bool_t          _jetIsLoose[20];   //[_nJets]
   Bool_t          _jetIsTight[20];   //[_nJets]
   Bool_t          _jetIsTightLepVeto[20];   //[_nJets]
   Double_t        _jetNeutralHadronFraction[20];
   Double_t        _jetChargedHadronFraction[20];
   Double_t        _jetNeutralEmFraction[20];
   Double_t        _jetChargedEmFraction[20];
   Double_t        _jetHFHadronFraction[20];
   Double_t        _jetHFEmFraction[20];
   unsigned         _nJetConstituents[20];
   Double_t        _JetConstituentPt[20][50];
   Double_t        _JetConstituentEta[20][50];
   Double_t        _JetConstituentPhi[20][50];
   Double_t        _JetConstituentMass[20][50];
   Int_t           _JetConstituentPdgId[20][50];
   Int_t           _JetConstituentCharge[20][50];
   Double_t        _JetConstituentdxy[20][50];
   Double_t        _JetConstituentdz[20][50];
   Double_t        _JetConstituentdxyErr[20][50];
   Double_t        _JetConstituentdzErr[20][50];
   Int_t           _JetConstituentNumberOfHits[20][50];
   Int_t           _JetConstituentNumberOfPixelHits[20][50];
   Bool_t          _JetConstituentHasTrack[20][50];
   unsigned        _nJetsPuppi;
   Double_t        _jetPuppiPt[20];   //[_nJetsPuppi]
   Double_t        _jetPuppiEta[20];   //[_nJetsPuppi]
   Double_t        _jetPuppiPhi[20];   //[_nJetsPuppi]
   Double_t        _jetPuppiPt_JECUp[20];   //[_nJetsPuppi]
   Double_t        _jetPuppiPt_JECDown[20];   //[_nJetsPuppi]
   Double_t        _met;
   Double_t        _metType1;
   Double_t        _metRaw;
   Double_t        _metJECDown;
   Double_t        _metJECUp;
   Double_t        _metUnclDown;
   Double_t        _metUnclUp;
   Double_t        _metResDown;
   Double_t        _metResUp;
   Double_t        _metPhi;
   Double_t        _metType1Phi;
   Double_t        _metRawPhi;
   Double_t        _metPhiJECDown;
   Double_t        _metPhiJECUp;
   Double_t        _metPhiUnclDown;
   Double_t        _metPhiUnclUp;
   Double_t        _metPhiResDown;
   Double_t        _metPhiResUp;
   Double_t        _metSignificance;
   Double_t        _metPuppi;
   Double_t        _metPuppiRaw;
   Double_t        _metPuppiJECDown;
   Double_t        _metPuppiJECUp;
   Double_t        _metPuppiUnclDown;
   Double_t        _metPuppiUnclUp;
   Double_t        _metPuppiResDown;
   Double_t        _metPuppiResUp;
   Double_t        _metPuppiPhi;
   Double_t        _metPuppiRawPhi;
   Double_t        _metPuppiPhiJECDown;
   Double_t        _metPuppiPhiJECUp;
   Double_t        _metPuppiPhiUnclDown;
   Double_t        _metPuppiPhiUnclUp;
   Double_t        _metPuppiPhiResDown;
   Double_t        _metPuppiPhiResUp;

   // List of branches
   TBranch        *b__runNb;   //!
   TBranch        *b__lumiBlock;   //!
   TBranch        *b__eventNb;   //!
   TBranch        *b__nVertex;   //!
   TBranch        *b__is2017;   //!
   TBranch        *b__is2018;   //!
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
   TBranch        *b__HLT_Ele27_WPTight_Gsf;   //!
   TBranch        *b__HLT_Ele27_WPTight_Gsf_prescale;   //!
   TBranch        *b__HLT_Ele32_WPTight_Gsf;   //!
   TBranch        *b__HLT_Ele32_WPTight_Gsf_prescale;   //!
   TBranch        *b__HLT_IsoMu24;   //!
   TBranch        *b__HLT_IsoMu24_prescale;   //!
   TBranch        *b__HLT_IsoTkMu24;   //!
   TBranch        *b__HLT_IsoTkMu24_prescale;   //!
   TBranch        *b__passTrigger_m;
   TBranch        *b__passTrigger_e;
   TBranch        *b__passTrigger_mm;
   TBranch        *b__passTrigger_ee;
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
   TBranch        *b__passMETFilters;   //!
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
   TBranch        *b__lElectronSummer16MvaGP;
   TBranch        *b__lElectronSummer16MvaHZZ;
   TBranch        *b__lElectronMvaFall17v1NoIso;
   TBranch        *b__lElectronMvaFall17Iso;
   TBranch        *b__lElectronMvaFall17NoIso;
   TBranch        *b__lElectronPassEmu;   //!
   TBranch        *b__lElectronPassConvVeto;   //!
   TBranch        *b__lElectronChargeConst;   //!
   TBranch        *b__lElectronMissingHits;   //!
   TBranch        *b__lElectronIsEB;                                                                         //electron specific variables for displaced electron ID
   TBranch        *b__lElectronIsEE;
   TBranch        *b__lElectronSuperClusterOverP;
   TBranch        *b__lElectronEcalEnergy;
   TBranch        *b__lElectronSigmaIetaIeta;
   TBranch        *b__lElectronDEtaInSeed;
   TBranch        *b__lElectronDeltaPhiSuperClusterTrack;
   TBranch        *b__lElectronDeltaEtaSuperClusterTrack;
   TBranch        *b__lElectronHOverE;
   TBranch        *b__lElectronEInvMinusPInv;
   TBranch        *b__lElectronNumberInnerHitsMissing;
   TBranch        *b__leptonMvatZq;
   TBranch        *b__leptonMvaTTH;
   TBranch        *b__leptonMvaTOP;
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
   TBranch        *b__closestJetDeepCsv;   //!
   TBranch        *b__closestJetDeepFlavor_b;   //!
   TBranch        *b__closestJetDeepFlavor_bb;   //!
   TBranch        *b__closestJetDeepFlavor_lepb;   //!
   TBranch        *b__closestJetDeepFlavor;   //!
   TBranch        *b__selectedTrackMult;   //!
   TBranch        *b__lGlobalMuon;                                                                       //muon speficic variables, also for displaced muon ID
   TBranch        *b__lTrackerMuon;
   TBranch        *b__lInnerTrackValidFraction;
   TBranch        *b__lGlobalTrackNormalizedChi2;
   TBranch        *b__lCQChi2Position;
   TBranch        *b__lCQTrackKink;
   TBranch        *b__lNumberOfMatchedStation;
   TBranch        *b__lNumberOfValidPixelHits;
   TBranch        *b__lNumberOfValidTrackerHits;
   TBranch        *b__muNumberInnerHits;
   TBranch        *b__lTrackerLayersWithMeasurement;
   TBranch        *b__lMuonSegComp;   //!
   TBranch        *b__lMuonTrackPt;   //!
   TBranch        *b__lMuonTrackPtErr;   //!
   TBranch        *b__lMuonTimenDof;
   TBranch        *b__lMuonTime;
   TBranch        *b__lMuonTimeErr;
   TBranch        *b__lMuonRPCTimenDof;
   TBranch        *b__lMuonRPCTime;
   TBranch        *b__lMuonRPCTimeErr;
   TBranch        *b__lIsPrompt;   //!
   TBranch        *b__lMatchPdgId;   //!
   TBranch        *b__lMatchCharge;
   TBranch        *b__tauGenStatus;
   TBranch        *b__lMomPdgId;
   TBranch        *b__lProvenance;
   TBranch        *b__lProvenanceCompressed;
   TBranch        *b__lProvenanceConversion;
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
   TBranch        *b__phHadronicOverEm;   //!
   TBranch        *b__phPassElectronVeto;   //!
   TBranch        *b__phHasPixelSeed;   //!
   TBranch        *b__phIsPrompt;   //!
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
   TBranch        *b__jetDeepCsv;   //!
   TBranch        *b__jetDeepFlavor_b;   //!
   TBranch        *b__jetDeepFlavor_bb;   //!
   TBranch        *b__jetDeepFlavor_lepb;   //!
   TBranch        *b__jetDeepFlavor;   //!
   TBranch        *b__jetDeepFlavor_c;   //!
   TBranch        *b__jetDeepFlavor_uds;   //!
   TBranch        *b__jetDeepFlavor_g;   //!
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
   TBranch        *b__nJetConstituents;
   TBranch        *b__JetConstituentPt;
   TBranch        *b__JetConstituentEta;
   TBranch        *b__JetConstituentPhi;
   TBranch        *b__JetConstituentMass;
   TBranch        *b__JetConstituentPdgId;
   TBranch        *b__JetConstituentCharge;
   TBranch        *b__JetConstituentdxy;
   TBranch        *b__JetConstituentdz;
   TBranch        *b__JetConstituentdxyErr;
   TBranch        *b__JetConstituentdzErr;
   TBranch        *b__JetConstituentNumberOfHits;
   TBranch        *b__JetConstituentNumberOfPixelHits;
   TBranch        *b__JetConstituentHasTrack;
   TBranch        *b__nJetsPuppi;
   TBranch        *b__jetPuppiPt;   //
   TBranch        *b__jetPuppiEta;   //
   TBranch        *b__jetPuppiPhi;   //
   TBranch        *b__jetPuppiPt_JECUp;   //
   TBranch        *b__jetPuppiPt_JECDown;   //
   TBranch        *b__met;
   TBranch        *b__metType1;
   TBranch        *b__metRaw;
   TBranch        *b__metJECDown;
   TBranch        *b__metJECUp;
   TBranch        *b__metUnclDown;
   TBranch        *b__metUnclUp;
   TBranch        *b__metResDown;
   TBranch        *b__metResUp;
   TBranch        *b__metPhi;
   TBranch        *b__metType1Phi;
   TBranch        *b__metRawPhi;
   TBranch        *b__metPhiJECDown;
   TBranch        *b__metPhiJECUp;
   TBranch        *b__metPhiUnclDown;
   TBranch        *b__metPhiUnclUp;
   TBranch        *b__metPhiResDown;
   TBranch        *b__metPhiResUp;
   TBranch        *b__metSignificance;
   TBranch        *b__metPuppi;
   TBranch        *b__metPuppiRaw;
   TBranch        *b__metPuppiJECDown;
   TBranch        *b__metPuppiJECUp;
   TBranch        *b__metPuppiUnclDown;
   TBranch        *b__metPuppiUnclUp;
   TBranch        *b__metPuppiResDown;
   TBranch        *b__metPuppiResUp;
   TBranch        *b__metPuppiPhi;
   TBranch        *b__metPuppiRawPhi;
   TBranch        *b__metPuppiPhiJECDown;
   TBranch        *b__metPuppiPhiJECUp;
   TBranch        *b__metPuppiPhiUnclDown;
   TBranch        *b__metPuppiPhiUnclUp;
   TBranch        *b__metPuppiPhiResDown;
   TBranch        *b__metPuppiPhiResUp;
   
   Double_t ev_weight;
   bool isSignal = false, isBackground = false, isData = false, _is2016 = false;
   bool extensive_plots = false;
   std::map<double, double> reweighting_weights;//<V2, weight>
   std::vector<int> evaluating_masses = {2, 3, 4, 5, 6, 8, 10, 15};
   std::map<int, std::vector<double>> evaluating_V2s;//<M, V2's>
   std::map<int, std::map<double, double>> evaluating_ctaus;//<M, <V2, ctau>> -> to use in parametrized training that takes ctau as parameter
   std::map<int, std::map<double, double>> JetTagVal; //<M, <V2, JetTagVal>>
   std::map<int, std::map<double, TString>> MV2name;
   //double JetTagVal_BDT = -1;
   

   // gen variables related to truth of event
   HNL_parameters* HNL_param;
   int i_gen_l1;
   int i_gen_l2;
   bool leadingIsl1;
   bool subleadingIsl2; 

   // signal region lepton indices 
   int i_leading;
   int i_subleading;
   TString sr_flavor, sr_charge, sr_lflavor;
   
   // gen indices corresponding to signal region leptons (geometric)
   int i_gen_leading;
   int i_gen_subleading;
   
   // jet indices
   int i_leading_jet;
   int i_subleading_jet;
   int i_thirdleading_jet;
   int i_jetl2;

   // numbers of leptons
   int nTightEle, nTightMu, nLooseEle, nLooseMu, nTightJet, nTightJet_uncl;

   //Signal region booleans
   bool _trige, _trigmu, _l1, _l1l2, _l1l2_Full, _l1l2_Full_noTrigger;

   // relevant lepton variables
   double mll, dRll, dphill, dRljet;

   // SV stuff
   double SVmass, SVl1mass, SVmassminl2, SVpt, SVeta, SVphi, IVF_PVSVdist_2D, IVF_PVSVdist, IVF_SVgenreco, gen_PVSVdist, gen_PVSVdist_2D;
   
   // functions
   // in src/full_analyzer_constructor.cc
   void      SetSampleTypes(TString filename);
   LSFReader get_LSFReader(TString local_dir, TString flavor);
   PUWeightReader get_PUWeightReader(TString local_dir);
   full_analyzer(TTree *tree=0);
    ~full_analyzer();
    Int_t    GetEntry(Long64_t entry);
    Long64_t LoadTree(Long64_t entry);
    void     Init(TTree *tree);
    void     Loop();
    void     Show(Long64_t entry = -1);

    // in src/full_analyzer.cc, the main code body
    void     run_over_file(TString, double, int, int, int);

   // in src/leptonID.cc
    bool     IsPromptElectronID(const unsigned i);
    double   rawElectronMVA(const double electronMVA);
    unsigned electronMVACategory(unsigned i);
    double   looseMVACut(unsigned i);
    bool     IsDisplacedElectronID(const unsigned i);
    bool     IsLooseElectronID(const unsigned i);
    bool     IsPromptMuonID(const unsigned i);
    bool     IsDisplacedMuonID(const unsigned i);
    bool     IsLooseMuonID(const unsigned i);
    bool     IsCleanElectron(const unsigned i, const std::vector<unsigned>& muoncollection);
    int      find_leading_lepton(const std::vector<unsigned>& leptoncollection);
    int      find_subleading_lepton(const std::vector<unsigned>& leptoncollection, const int index_leading);
    int      find_gen_lep(int i_lep);
    int      find_gen_l1();
    int      find_gen_l2();
    bool     leptonIsGenLepton(int, int);
    double   get_lsource(int);
    double   get_LSF(LSFReader& lsfreader_e, LSFReader& lsfreader_mu, int i);

   // in src/jetID.cc
    bool     IsTightJetID(const unsigned i);
    bool     IsCleanJet(const unsigned i, const std::vector<unsigned>& leptoncollection);
    int      find_leading_jet(const std::vector<unsigned>& jetcollection);
    int      find_subleading_jet(const std::vector<unsigned>& jetcollection, const int index_leading);
    int      find_thirdleading_jet(const std::vector<unsigned>& jetcollection, const int index_leading, const int index_subleading);
    int      find_jet_closest_to_lepton(const int index_lepton);
    double   get_dR_lepton_jet(int, int);

   // in src/signal_regions.cc
    void     set_leptons(int i_subleading_e, int i_subleading_mu);
    void     set_relevant_lepton_variables();
    TString  get_signal_region_flavor();
    int      select_subleading_lepton(int i_subleading_e, int i_subleading_mu);
    int      select_leading_lepton(int i_leading_e, int i_leading_mu);
    void     signal_regions();
    void     additional_signal_regions();
    bool     leadptcut(int);
    bool     subleadptcut(int);
    double   get_mll(int, int);
    double   get_dRll(int, int);
    double   get_dphill(int, int);

    // in src/print_tables.cc
    void     print_table();
   
    // in src/histo_functions.cc
    void     add_histograms(std::map<TString, TH1*>*, std::map<TString, TH2*>*, TString);
    void     add_general_histograms(std::map<TString, TH1*>*, TString);
    void     add_Shape_SR_histograms(std::map<TString, TH1*>* hists, TString prefix);
    void     fill_Shape_SR_histograms(std::map<TString, TH1*>* hists, TString MV2, double event_weight);
    void     fill_histograms(std::map<TString, TH1*>*, std::map<TString, TH2*>*);
    void     fill_relevant_histograms(std::map<TString, TH1*>*, TString, double);
    void     fill_general_histograms(std::map<TString, TH1*>*, TString, double);
    void     fill_cutflow(std::map<TString, TH1*>*, TString, double);
    void     fill_lepton_eff(std::map<TString, TH1*>* hists, TString prefix);
    void     give_alphanumeric_labels(std::map<TString, TH1*>*, TString);
   
    // in src/jet_histograms.cc
    void     add_jet_histograms(std::map<TString, TH1*>*, TString);
    void     fill_jet_histograms(std::map<TString, TH1*>*, TString, double);
    void     fill_jet_constituent_histograms(std::map<TString, TH1*>* hists, TString prefix, double event_weight);
    //void     fill_HNLtagger_tree(HNLtagger& hnltagger);
    int      is_track_in_sv(int i_lep, int i_jet, int i_const);
    //void     fill_HNLBDTtagger_tree(HNLBDTtagger& hnlbdttagger, double _weight);

    // in src/HLT_eff.cc
    void     init_HLT_efficiency(std::map<TString, TH1*>*, TString);
    void     init_HLT_allevents_efficiency(std::map<TString, TH1*>*, TString);
    void     fill_HLT_efficiency(std::map<TString, TH1*>*, TString);
    void     fill_HLT_allevents_efficiency(std::map<TString, TH1*>*, TString);

    // in src/gen_histograms.cc
    void     init_HNL_MC_check(std::map<TString, TH1*>*, std::map<TString, TH2*>*);
    void     fill_HNL_MC_check(std::map<TString, TH1*>*, std::map<TString, TH2*>*, double);
    void     add_gen_histograms(std::map<TString, TH1*>* hists, TString prefix);
    void     add_KVF_eff_histograms(std::map<TString, TH1*>* hists, TString prefix);
    void     add_IVF_eff_histograms(std::map<TString, TH1*>* hists, TString prefix);
    void     add_chargeflip_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix);
    void     fill_chargeflip_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, double event_weight);
    //void     fill_gen_HNLtagger_tree(HNLtagger& hnltagger_gen, int i_jet);
    int      get_lfromtau(int i_gen_l);

    // in src/MET_histograms.cc
    TString  runera;
    bool     usemetv2 = false;
    void     setRunEra(const unsigned long runnb);
    std::pair<double, double> METXYCorr_Met_MetPhi(double uncormet, double uncormet_phi, int npv);
    void     add_MET_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix);
    void     fill_MET_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, double event_weight);
   
    // in src/tree_functions.cc
    //void     fill_BkgEstimator_tree(BkgEstimator& bkgestimator, double event_weight);

   // in src/SelectionOptimization.cc
   // bool     create_sigreg_bool(int i_leading, int i_subleading, bool base_selection, double l2_dxy, double l2_reliso, double dphi, double dR, double upperdR, double mll, double lowermll, bool applyLepVeto, bool applyOneJet, double jettagval);
   // void     add_Bool_hists(std::map<TString, TH1*>* hists, TString prefix);
   // void     create_Bools_and_fill_Bool_hists(std::map<TString, TH1*>* hists, TString prefix, int i_leading, int i_subleading, bool base_selection);
};

#endif
