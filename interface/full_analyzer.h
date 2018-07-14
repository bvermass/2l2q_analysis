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

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TSystem.h>

// Header file for the classes stored in the TTree if any.

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
   Double_t        _met;
   Double_t        _metJECDown;
   Double_t        _metJECUp;
   Double_t        _metUnclDown;
   Double_t        _metUnclUp;
   Double_t        _metPhi;
   Double_t        _metPhiJECDown;
   Double_t        _metPhiJECUp;
   Double_t        _metPhiUnclDown;
   Double_t        _metPhiUnclUp;
   Double_t        _metSignificance;
   Float_t         _nTrueInt;
   Double_t        _weight;
   Double_t        _lheHTIncoming;
   Double_t        _ctauHN;
   UChar_t         _nLheWeights;
   Double_t        _lheWeight[110];   //[_nLheWeights]
   UChar_t         _ttgEventType;
   UChar_t         _zgEventType;
   Double_t        _gen_met;
   Double_t        _gen_metPhi;
   UChar_t         _gen_nPh;
   Double_t        _gen_phPt[20];   //[_gen_nPh]
   Double_t        _gen_phEta[20];   //[_gen_nPh]
   Double_t        _gen_phPhi[20];   //[_gen_nPh]
   Double_t        _gen_phE[20];   //[_gen_nPh]
   Int_t           _gen_phMomPdg[20];   //[_gen_nPh]
   Bool_t          _gen_phIsPrompt[20];   //[_gen_nPh]
   Double_t        _gen_phMinDeltaR[20];   //[_gen_nPh]
   Bool_t          _gen_phPassParentage[20];   //[_gen_nPh]
   UChar_t         _gen_nL;
   Double_t        _gen_lPt[20];   //[_gen_nL]
   Double_t        _gen_lEta[20];   //[_gen_nL]
   Double_t        _gen_lPhi[20];   //[_gen_nL]
   Double_t        _gen_lE[20];   //[_gen_nL]
   UInt_t          _gen_lFlavor[20];   //[_gen_nL]
   Int_t           _gen_lCharge[20];   //[_gen_nL]
   Int_t           _gen_lMomPdg[20];   //[_gen_nL]
   Double_t        _gen_vertex_x[20];
   Double_t        _gen_vertex_y[20];
   Double_t        _gen_vertex_z[20];
   Bool_t          _gen_lIsPrompt[20];   //[_gen_nL]
   Double_t        _gen_lMinDeltaR[20];   //[_gen_nL]
   Bool_t          _gen_lPassParentage[20];   //[_gen_nL]
   Double_t        _gen_HT;
   UChar_t         _gen_nW;
   UInt_t          _gen_WMomPdg[1];   //[_gen_nW]
   UChar_t         _gen_nWfromN;
   UChar_t         _gen_nN;
   Double_t        _gen_NPt;
   Double_t        _gen_NEta;
   Double_t        _gen_NPhi;
   Double_t        _gen_NE;
   Double_t        _gen_Nvertex_x;
   Double_t        _gen_Nvertex_y;
   Double_t        _gen_Nvertex_z;
   UChar_t         _gen_nNdaughters;
   UInt_t          _gen_Ndaughters_pdg[30];   //[_gen_nNdaughters]
   UChar_t         _gen_nstatus23;
   UChar_t         _gen_nstatus23_fromN;
   UChar_t         _gen_nstatus23_fromW;
   Int_t           _gen_status23_pdg[5];   //[_gen_nstatus23]
   UInt_t          _gen_status23_fromN_pdg[3];   //[_gen_nstatus23_fromN]
   UInt_t          _gen_status23_fromW_pdg[1];   //[_gen_nstatus23_fromW]
   UChar_t         _gen_nq23;
   Double_t        _gen_qPt[2];   //[_gen_nq23]
   Double_t        _gen_qEta[2];   //[_gen_nq23]
   Double_t        _gen_qPhi[2];   //[_gen_nq23]
   Double_t        _gen_qE[2];   //[_gen_nq23]
   UChar_t         _gen_nq1dtr;
   Int_t           _gen_q1dtr_status[20];   //[_gen_nq1dtr]
   Int_t           _gen_q1dtr_pdgid[20];   //[_gen_nq1dtr]
   Double_t        _gen_q1dtr_Pt[20];   //[_gen_nq1dtr]
   Double_t        _gen_q1dtr_Eta[20];   //[_gen_nq1dtr]
   Double_t        _gen_q1dtr_Phi[20];   //[_gen_nq1dtr]
   Double_t        _gen_q1dtr_E[20];   //[_gen_nq1dtr]
   UChar_t         _gen_nq2dtr;
   Int_t           _gen_q2dtr_status[20];   //[_gen_nq2dtr]
   Int_t           _gen_q2dtr_pdgid[20];   //[_gen_nq2dtr]
   Double_t        _gen_q2dtr_Pt[20];   //[_gen_nq2dtr]
   Double_t        _gen_q2dtr_Eta[20];   //[_gen_nq2dtr]
   Double_t        _gen_q2dtr_Phi[20];   //[_gen_nq2dtr]
   Double_t        _gen_q2dtr_E[20];   //[_gen_nq2dtr]
   Bool_t          _HLT_Ele27_WPTight_Gsf;
   Int_t           _HLT_Ele27_WPTight_Gsf_prescale;
   Bool_t          _HLT_IsoMu24;
   Int_t           _HLT_IsoMu24_prescale;
   Bool_t          _HLT_IsoTkMu24;
   Int_t           _HLT_IsoTkMu24_prescale;
   Bool_t          _HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;
   Int_t           _HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_prescale;
   Bool_t          _HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Int_t           _HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
   Bool_t          _HLT_Mu8_DiEle12_CaloIdL_TrackIdL;
   Int_t           _HLT_Mu8_DiEle12_CaloIdL_TrackIdL_prescale;
   Bool_t          _HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
   Int_t           _HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
   Bool_t          _HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
   Int_t           _HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_prescale;
   Bool_t          _HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ;
   Int_t           _HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
   Bool_t          _HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL;
   Int_t           _HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_prescale;
   Bool_t          _HLT_DiMu9_Ele9_CaloIdL_TrackIdL;
   Int_t           _HLT_DiMu9_Ele9_CaloIdL_TrackIdL_prescale;
   Bool_t          _HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
   Int_t           _HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_prescale;
   Bool_t          _HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
   Int_t           _HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;
   Bool_t          _HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
   Int_t           _HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;
   Bool_t          _HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
   Int_t           _HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_prescale;
   Bool_t          _HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
   Int_t           _HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;
   Bool_t          _HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
   Int_t           _HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;
   Bool_t          _HLT_TripleMu_12_10_5;
   Int_t           _HLT_TripleMu_12_10_5_prescale;
   Bool_t          _passMETFilters;
   Bool_t          _Flag_HBHENoiseFilter;
   Bool_t          _Flag_HBHENoiseIsoFilter;
   Bool_t          _Flag_EcalDeadCellTriggerPrimitiveFilter;
   Bool_t          _Flag_goodVertices;
   Bool_t          _Flag_globalTightHalo2016Filter;
   Bool_t          _flag_badPFMuonFilter;
   Bool_t          _flag_badChCandFilter;
   Bool_t          _HLT_Ele105_CaloIdVT_GsfTrkIdT;
   Int_t           _HLT_Ele105_CaloIdVT_GsfTrkIdT_prescale;
   Bool_t          _HLT_Ele115_CaloIdVT_GsfTrkIdT;
   Int_t           _HLT_Ele115_CaloIdVT_GsfTrkIdT_prescale;
   Bool_t          _HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Int_t           _HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
   Bool_t          _HLT_DoubleEle33_CaloIdL_GsfTrkIdVL;
   Int_t           _HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_prescale;
   Bool_t          _HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL;
   Int_t           _HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_prescale;
   Bool_t          _HLT_Mu50;
   Int_t           _HLT_Mu50_prescale;
   Bool_t          _HLT_TkMu50;
   Int_t           _HLT_TkMu50_prescale;
   Bool_t          _HLT_Mu45_eta2p1;
   Int_t           _HLT_Mu45_eta2p1_prescale;
   Bool_t          _HLT_Mu30_TkMu11;
   Int_t           _HLT_Mu30_TkMu11_prescale;
   UChar_t         _nL;
   UChar_t         _nMu;
   UChar_t         _nEle;
   UChar_t         _nLight;
   UChar_t         _nTau;
   Double_t        _lPt[10];   //[_nL]
   Double_t        _lEta[10];   //[_nL]
   Double_t        _lEtaSC[10];   //[_nLight]
   Double_t        _lPhi[10];   //[_nL]
   Double_t        _lE[10];   //[_nL]
   UInt_t          _lFlavor[10];   //[_nL]
   Int_t           _lCharge[10];   //[_nL]
   Double_t        _dxy[10];   //[_nL]
   Double_t        _dz[10];   //[_nL]
   Double_t        _3dIP[10];   //[_nL]
   Double_t        _3dIPSig[10];   //[_nL]
   Float_t         _lElectronMva[10];   //[_nLight]
   Float_t         _lElectronMvaHZZ[10];   //[_nLight]
   Bool_t          _lElectronPassEmu[10];   //[_nLight]
   Bool_t          _lElectronPassConvVeto[10];   //[_nLight]
   Bool_t          _lElectronChargeConst[10];   //[_nLight]
   UInt_t          _lElectronMissingHits[10];   //[_nLight]
   Double_t        _leptonMvaSUSY[10];   //[_nLight]
   Double_t        _leptonMvaTTH[10];   //[_nLight]
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
   Bool_t          _lPOGLooseWOIso[10];   //[_nLight]
   Bool_t          _lPOGMediumWOIso[10];   //[_nLight]
   Bool_t          _lPOGTightWOIso[10];   //[_nLight]
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
   Double_t        _relIso0p4Mu[2];   //[_nMu]
   Double_t        _miniIso[10];   //[_nLight]
   Double_t        _miniIsoCharged[10];   //[_nLight]
   Double_t        _ptRel[10];   //[_nLight]
   Double_t        _ptRatio[10];   //[_nLight]
   Double_t        _closestJetCsvV2[10];   //[_nLight]
   Double_t        _closestJetDeepCsv_b[10];   //[_nLight]
   Double_t        _closestJetDeepCsv_bb[10];   //[_nLight]
   UInt_t          _selectedTrackMult[10];   //[_nLight]
   UInt_t          _TrackMult_pt0[10];   //[_nLight]
   UInt_t          _TrackMult_pt1[6];   //[_nLight]
   UInt_t          _TrackMult_pt2[6];   //[_nLight]
   UInt_t          _TrackMult_pt3[6];   //[_nLight]
   UInt_t          _TrackMult_pt4[6];   //[_nLight]
   UInt_t          _TrackMult_pt5[10];   //[_nLight]
   UInt_t          _TrackMult_noIP_pt0[6];   //[_nLight]
   UInt_t          _TrackMult_noIP_pt1[6];   //[_nLight]
   UInt_t          _TrackMult_noIP_pt2[6];   //[_nLight]
   UInt_t          _TrackMult_noIP_pt3[6];   //[_nLight]
   UInt_t          _TrackMult_noIP_pt4[6];   //[_nLight]
   UInt_t          _TrackMult_noIP_pt5[6];   //[_nLight]
   UInt_t	       _Nutau_TrackMult_pt1[10];
   UInt_t	       _Nutau_TrackMult_pt5[10];
   Bool_t          _lVtx_valid[10];
   Double_t	       _lVtxpos_x[10];
   Double_t	       _lVtxpos_y[10];
   Double_t	       _lVtxpos_z[10];
   Double_t	       _lVtxpos_cxx[10];
   Double_t	       _lVtxpos_cyy[10];
   Double_t	       _lVtxpos_czz[10];
   Double_t	       _lVtxpos_cyx[10];
   Double_t	       _lVtxpos_czy[10];
   Double_t	       _lVtxpos_czx[10];
   Double_t	       _lVtxpos_df[10];
   Double_t	       _lVtxpos_chi2[10];
   UInt_t	       _lVtxpos_ntracks[10];
   Double_t	       _lVtxpos_PVdxy[10];
   Double_t	       _lVtxpos_BSdxy[10];
   Double_t	       _lVtxpos_PVdz[10];
   Double_t	       _lVtxpos_BSdz[10];
   Double_t        _lVtxpos_maxdxy_valid[10];
   Double_t        _lVtxpos_maxdz_valid[10];
   Double_t        _lVtxpos_maxdxy_Notvalid[10];
   Double_t        _lVtxpos_maxdz_Notvalid[10];
   Double_t        _lMuonSegComp[10];   //[_nMu]
   Double_t        _lMuonTrackPt[10];   //[_nMu]
   Double_t        _lMuonTrackPtErr[10];   //[_nMu]
   Bool_t          _lIsPrompt[10];   //[_nL]
   Int_t           _lMatchPdgId[10];   //[_nL]
   UChar_t         _nPh;
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
   Double_t        _phSigmaIetaIphi[10];   //[_nPh]
   Double_t        _phHadronicOverEm[10];   //[_nPh]
   Bool_t          _phPassElectronVeto[10];   //[_nPh]
   Bool_t          _phHasPixelSeed[10];   //[_nPh]
   Bool_t          _phIsPrompt[10];   //[_nPh]
   Int_t           _phMatchMCPhotonAN15165[10];   //[_nPh]
   Int_t           _phMatchMCLeptonAN15165[10];   //[_nPh]
   Int_t           _phMatchPdgId[10];   //[_nPh]
   UChar_t         _nJets;
   Double_t        _jetPt[20];   //[_nJets]
   Double_t        _jetPt_JECUp[20];   //[_nJets]
   Double_t        _jetPt_JECDown[20];   //[_nJets]
   Double_t        _jetPt_JERUp[20];   //[_nJets]
   Double_t        _jetPt_JERDown[20];   //[_nJets]
   Double_t        _jetEta[20];   //[_nJets]
   Double_t        _jetPhi[20];   //[_nJets]
   Double_t        _jetE[20];   //[_nJets]
   Double_t        _jetCsvV2[20];   //[_nJets]
   Double_t        _jetDeepCsv_udsg[20];   //[_nJets]
   Double_t        _jetDeepCsv_b[20];   //[_nJets]
   Double_t        _jetDeepCsv_c[20];   //[_nJets]
   Double_t        _jetDeepCsv_bb[20];   //[_nJets]
   UInt_t          _jetHadronFlavor[20];   //[_nJets]
   Bool_t          _jetIsLoose[20];   //[_nJets]
   Bool_t          _jetIsTight[20];   //[_nJets]
   Bool_t          _jetIsTightLepVeto[20];   //[_nJets]
   /*Int_t           _nDaughters;
   Int_t           _jet_tag_for_daughters[300];   //[_nDaughters]
   Int_t           _jet_daughter_pdgid[300];   //[_nDaughters]
   Double_t        _jet_daughter_pt[300];   //[_nDaughters]
   Double_t        _jet_daughter_eta[300];   //[_nDaughters]
   Double_t        _jet_daughter_phi[300];   //[_nDaughters]
   Double_t        _jet_daughter_energy[300];   //[_nDaughters]
*/
   // List of branches
   TBranch        *b__runNb;   //!
   TBranch        *b__lumiBlock;   //!
   TBranch        *b__eventNb;   //!
   TBranch        *b__nVertex;   //!
   TBranch        *b__met;   //!
   TBranch        *b__metJECDown;   //!
   TBranch        *b__metJECUp;   //!
   TBranch        *b__metUnclDown;   //!
   TBranch        *b__metUnclUp;   //!
   TBranch        *b__metPhi;   //!
   TBranch        *b__metPhiJECDown;   //!
   TBranch        *b__metPhiJECUp;   //!
   TBranch        *b__metPhiUnclDown;   //!
   TBranch        *b__metPhiUnclUp;   //!
   TBranch        *b__metSignificance;   //!
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
   TBranch        *b__gen_nW;   //!
   TBranch        *b__gen_WMomPdg;   //!
   TBranch        *b__gen_nWfromN;   //!
   TBranch        *b__gen_nN;   //!
   TBranch        *b__gen_NPt;
   TBranch        *b__gen_NEta;
   TBranch        *b__gen_NPhi;
   TBranch        *b__gen_NE;
   TBranch        *b__gen_Nvertex_x;
   TBranch        *b__gen_Nvertex_y;
   TBranch        *b__gen_Nvertex_z;
   TBranch        *b__gen_nNdaughters;   //!
   TBranch        *b__gen_Ndaughters_pdg;   //!
   TBranch        *b__gen_nstatus23;   //!
   TBranch        *b__gen_nstatus23_fromN;   //!
   TBranch        *b__gen_nstatus23_fromW;   //!
   TBranch        *b__gen_status23_pdg;   //!
   TBranch        *b__gen_status23_fromN_pdg;   //!
   TBranch        *b__gen_status23_fromW_pdg;   //!
   TBranch        *b__gen_nq23;   //!
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
   TBranch        *b__HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;   //!
   TBranch        *b__HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_prescale;   //!
   TBranch        *b__HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   TBranch        *b__HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;   //!
   TBranch        *b__HLT_Mu8_DiEle12_CaloIdL_TrackIdL;   //!
   TBranch        *b__HLT_Mu8_DiEle12_CaloIdL_TrackIdL_prescale;   //!
   TBranch        *b__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   TBranch        *b__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_prescale;   //!
   TBranch        *b__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;   //!
   TBranch        *b__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_prescale;   //!
   TBranch        *b__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   TBranch        *b__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_prescale;   //!
   TBranch        *b__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL;   //!
   TBranch        *b__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_prescale;   //!
   TBranch        *b__HLT_DiMu9_Ele9_CaloIdL_TrackIdL;   //!
   TBranch        *b__HLT_DiMu9_Ele9_CaloIdL_TrackIdL_prescale;   //!
   TBranch        *b__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;   //!
   TBranch        *b__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_prescale;   //!
   TBranch        *b__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;   //!
   TBranch        *b__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;   //!
   TBranch        *b__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;   //!
   TBranch        *b__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;   //!
   TBranch        *b__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;   //!
   TBranch        *b__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_prescale;   //!
   TBranch        *b__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;   //!
   TBranch        *b__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;   //!
   TBranch        *b__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL;   //!
   TBranch        *b__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;   //!
   TBranch        *b__HLT_TripleMu_12_10_5;   //!
   TBranch        *b__HLT_TripleMu_12_10_5_prescale;   //!
   TBranch        *b__passMETFilters;   //!
   TBranch        *b__Flag_HBHENoiseFilter;   //!
   TBranch        *b__Flag_HBHENoiseIsoFilter;   //!
   TBranch        *b__Flag_EcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b__Flag_goodVertices;   //!
   TBranch        *b__Flag_globalTightHalo2016Filter;   //!
   TBranch        *b__flag_badPFMuonFilter;   //!
   TBranch        *b__flag_badChCandFilter;   //!
   TBranch        *b__HLT_Ele105_CaloIdVT_GsfTrkIdT;   //!
   TBranch        *b__HLT_Ele105_CaloIdVT_GsfTrkIdT_prescale;   //!
   TBranch        *b__HLT_Ele115_CaloIdVT_GsfTrkIdT;   //!
   TBranch        *b__HLT_Ele115_CaloIdVT_GsfTrkIdT_prescale;   //!
   TBranch        *b__HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   TBranch        *b__HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;   //!
   TBranch        *b__HLT_DoubleEle33_CaloIdL_GsfTrkIdVL;   //!
   TBranch        *b__HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_prescale;   //!
   TBranch        *b__HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL;   //!
   TBranch        *b__HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_prescale;   //!
   TBranch        *b__HLT_Mu50;   //!
   TBranch        *b__HLT_Mu50_prescale;   //!
   TBranch        *b__HLT_TkMu50;   //!
   TBranch        *b__HLT_TkMu50_prescale;   //!
   TBranch        *b__HLT_Mu45_eta2p1;   //!
   TBranch        *b__HLT_Mu45_eta2p1_prescale;   //!
   TBranch        *b__HLT_Mu30_TkMu11;   //!
   TBranch        *b__HLT_Mu30_TkMu11_prescale;   //!
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
   TBranch        *b__leptonMvaSUSY;   //!
   TBranch        *b__leptonMvaTTH;   //!
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
   TBranch        *b__relIso0p4Mu;   //!
   TBranch        *b__miniIso;   //!
   TBranch        *b__miniIsoCharged;   //!
   TBranch        *b__ptRel;   //!
   TBranch        *b__ptRatio;   //!
   TBranch        *b__closestJetCsvV2;   //!
   TBranch        *b__closestJetDeepCsv_b;   //!
   TBranch        *b__closestJetDeepCsv_bb;   //!
   TBranch        *b__selectedTrackMult;   //!
   TBranch        *b__TrackMult_pt0;   //!
   TBranch        *b__TrackMult_pt1;   //!
   TBranch        *b__TrackMult_pt2;   //!
   TBranch        *b__TrackMult_pt3;   //!
   TBranch        *b__TrackMult_pt4;   //!
   TBranch        *b__TrackMult_pt5;   //!
   TBranch        *b__TrackMult_noIP_pt0;   //!
   TBranch        *b__TrackMult_noIP_pt1;   //!
   TBranch        *b__TrackMult_noIP_pt2;   //!
   TBranch        *b__TrackMult_noIP_pt3;   //!
   TBranch        *b__TrackMult_noIP_pt4;   //!
   TBranch        *b__TrackMult_noIP_pt5;   //!
   TBranch	      *b__Nutau_TrackMult_pt1;
   TBranch	      *b__Nutau_TrackMult_pt5;
   TBranch        *b__lVtx_valid;
   TBranch	      *b__lVtxpos_x;
   TBranch	      *b__lVtxpos_y;
   TBranch	      *b__lVtxpos_z;
   TBranch	      *b__lVtxpos_cxx;
   TBranch	      *b__lVtxpos_cyy;
   TBranch	      *b__lVtxpos_czz;
   TBranch	      *b__lVtxpos_cyx;
   TBranch	      *b__lVtxpos_czy;
   TBranch	      *b__lVtxpos_czx;
   TBranch	      *b__lVtxpos_df;
   TBranch	      *b__lVtxpos_chi2;
   TBranch	      *b__lVtxpos_PVdxy;
   TBranch	      *b__lVtxpos_BSdxy;
   TBranch	      *b__lVtxpos_PVdz;
   TBranch	      *b__lVtxpos_BSdz;
   TBranch        *b__lVtxpos_maxdxy_valid;
   TBranch        *b__lVtxpos_maxdz_valid;
   TBranch        *b__lVtxpos_maxdxy_Notvalid;
   TBranch        *b__lVtxpos_maxdz_Notvalid;
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
   TBranch        *b__jetPt_JERUp;   //!
   TBranch        *b__jetPt_JERDown;   //!
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
/*   TBranch        *b__nDaughters;   //!
   TBranch        *b__jet_tag_for_daughters;   //!
   TBranch        *b__jet_daughter_pdgid;   //!
   TBranch        *b__jet_daughter_pt;   //!
   TBranch        *b__jet_daughter_eta;   //!
   TBranch        *b__jet_daughter_phi;   //!
   TBranch        *b__jet_daughter_energy;   //!
*/   
   Double_t event_weight;
   
   int i_leading_e;
   int i_subleading_e;
   int i_leading_mu;
   int i_subleading_mu;
   int i_subleading_noniso_e;
   int i_subleading_noniso_mu;
   int i_subleading_displ_e;
   int i_subleading_displ_mu;
   
   int i_leading_jet_for_full;
   int i_subleading_jet_for_full;
   int i_leading_jet_for_noniso;
   int i_subleading_jet_for_noniso;
   int i_leading_jet_for_displ;
   int i_subleading_jet_for_displ;


   full_analyzer(TTree *tree=0);
   virtual ~full_analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     run_over_file(TString, double, int);
   virtual void     get_electronID(bool*);
   virtual void     get_noniso_electronID(bool*);
   virtual void     get_displ_electronID(bool*);
   virtual void     get_muonID(bool*);
   virtual void     get_noniso_muonID(bool*);
   virtual void     get_displ_muonID(bool*);
   virtual void     get_jetID(bool*);
   virtual void     get_clean_jets(bool*, bool*, bool*);
   virtual void     get_clean_ele(bool*, bool*);
   virtual int      find_leading_e(bool*, bool*);
   virtual int      find_leading_mu(bool*);
   virtual int      find_leading_jet(bool*, bool*);
   virtual int      find_subleading_e(bool*, bool*, int);
   virtual int      find_subleading_mu(bool*, int);
   virtual int      find_subleading_jet(bool*, bool*, int);
   virtual void     print_table();
   virtual void     add_histograms(std::map<TString, TH1*>*, TString);
   virtual void     fill_histograms(std::map<TString, TH1*>*, TString);
   virtual void     fill_histograms_e(std::map<TString, TH1*>*, TString);
   virtual void     fill_histograms_mu(std::map<TString, TH1*>*, TString);
   virtual void     HLT_efficiency_init(std::map<TString, TH1*>*);
   virtual void     HLT_efficiency_fill(std::map<TString, TH1*>*, bool, bool);
   
};

#endif
