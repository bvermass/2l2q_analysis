////////////////////////////////////////////////////////////////////////////////
// Skimmer reads input root file, checks skimCondition, fill output root file //
////////////////////////////////////////////////////////////////////////////////


#ifndef full_analyzer_h
#define full_analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>

#include <iostream>
#include <fstream>
#include <cmath>

#include <string>
#include <TSystem.h>

#include "../../interface/full_analyzer.h"
#include "../LorentzVector/LorentzVector.h"
#include "LeptonMvaHelper.h"

class Skimmer {
    public :
        TFile* input;
        TTree* inputtree;
        bool isData;
        ULong64_t       i_runNb;
        ULong64_t       i_lumiBlock;
        ULong64_t       i_eventNb;
        UChar_t         i_nVertex;
        Bool_t          i_is2017;
        Bool_t          i_is2018;
        Double_t        i_BS_x;
        Double_t        i_BS_y;
        Double_t        i_BS_z;
        Double_t        i_BS_xErr;
        Double_t        i_BS_yErr;
        Double_t        i_BS_zErr;
        Double_t        i_PV_x;
        Double_t        i_PV_y;
        Double_t        i_PV_z;
        Double_t        i_PV_xErr;
        Double_t        i_PV_yErr;
        Double_t        i_PV_zErr;
        Float_t         i_prefireWeight;
        Float_t         i_prefireWeightUp;
        Float_t         i_prefireWeightDown;
        Float_t         i_nTrueInt;
        Double_t        i_weight;
        Double_t        i_lheHTIncoming;
        Double_t        i_ctauHN;
        unsigned        i_nLheTau;
        unsigned        i_nLheWeights;
        Double_t        i_lheWeight[110];   //[_nLheWeights]
        unsigned        i_nPsWeights;
        Double_t        i_psWeight[110];   //[_nLheWeights]
        unsigned        i_ttgEventType;
        unsigned        i_zgEventType;
        Double_t        i_gen_met;
        Double_t        i_gen_metPhi;
        unsigned        i_gen_nPh;
        unsigned        i_gen_phStatus[20];
        Double_t        i_gen_phPt[20];   //[_gen_nPh]
        Double_t        i_gen_phEta[20];   //[_gen_nPh]
        Double_t        i_gen_phPhi[20];   //[_gen_nPh]
        Double_t        i_gen_phE[20];   //[_gen_nPh]
        Int_t           i_gen_phMomPdg[20];   //[_gen_nPh]
        Bool_t          i_gen_phIsPrompt[20];   //[_gen_nPh]
        Double_t        i_gen_phMinDeltaR[20];   //[_gen_nPh]
        Bool_t          i_gen_phPassParentage[20];   //[_gen_nPh]
        unsigned        i_gen_nL;
        Double_t        i_gen_lPt[20];   //[_gen_nL]
        Double_t        i_gen_lEta[20];   //[_gen_nL]
        Double_t        i_gen_lPhi[20];   //[_gen_nL]
        Double_t        i_gen_lE[20];   //[_gen_nL]
        unsigned        i_gen_lFlavor[20];   //[_gen_nL]
        Int_t           i_gen_lCharge[20];   //[_gen_nL]
        Int_t           i_gen_lMomPdg[20];   //[_gen_nL]
        Double_t        i_gen_vertex_x[20];
        Double_t        i_gen_vertex_y[20];
        Double_t        i_gen_vertex_z[20];
        Bool_t          i_gen_lIsPrompt[20];   //[_gen_nL]
        Bool_t          i_gen_lDecayedHadr[20];
        Double_t        i_gen_lMinDeltaR[20];   //[_gen_nL]
        Bool_t          i_gen_lPassParentage[20];   //[_gen_nL]
        Bool_t          i_hasInternalConversion;   //[_gen_nL]
        unsigned        i_gen_nN;
        Double_t        i_gen_NPt;
        Double_t        i_gen_NEta;
        Double_t        i_gen_NPhi;
        Double_t        i_gen_NE;
        Double_t        i_gen_Nvertex_x;
        Double_t        i_gen_Nvertex_y;
        Double_t        i_gen_Nvertex_z;
        unsigned        i_gen_nNPackedDtrs;
        Double_t        i_gen_NPackedDtrsPt[20];
        Double_t        i_gen_NPackedDtrsEta[20];
        Double_t        i_gen_NPackedDtrsPhi[20];
        Double_t        i_gen_NPackedDtrsE[20];
        Int_t           i_gen_NPackedDtrsPdgId[20];
        Int_t           i_gen_NPackedDtrsCharge[20];
        Double_t        i_gen_NPackedDtrsRecodR[20];
        Double_t        i_gen_NPackedDtrsRecodptoverpt[20];
        Double_t        i_gen_NPackedDtrsRecoPt[20];
        Double_t        i_gen_NPackedDtrsRecoEta[20];
        Double_t        i_gen_NPackedDtrsRecoPhi[20];
        Double_t        i_gen_NPackedDtrsRecoE[20];
        Int_t           i_gen_NPackedDtrsRecoPdgId[20];
        Double_t        i_gen_NPackedDtrsRecodxy[20];
        Double_t        i_gen_NPackedDtrsRecodz[20];
        Bool_t          i_gen_NPackedDtrsHasReco[20];
        unsigned        i_gen_nNPackedDtrsPCA;
        Double_t        i_gen_NPackedDtrsPCADist[20];
        Double_t        i_gen_NPackedDtrsPCAX0[20];
        Double_t        i_gen_NPackedDtrsPCAY0[20];
        Double_t        i_gen_NPackedDtrsPCAZ0[20];
        Double_t        i_gen_NPackedDtrsPCAX1[20];
        Double_t        i_gen_NPackedDtrsPCAY1[20];
        Double_t        i_gen_NPackedDtrsPCAZ1[20];
        Double_t        i_gen_NPackedDtrsPCAX2[20];
        Double_t        i_gen_NPackedDtrsPCAY2[20];
        Double_t        i_gen_NPackedDtrsPCAZ2[20];
        Double_t        i_gen_NPackedDtrsPCAPhi1[20];
        Double_t        i_gen_NPackedDtrsPCAPhi2[20];
        unsigned        i_gen_NPackedDtrsPCAIndex1[20];
        unsigned        i_gen_NPackedDtrsPCAIndex2[20];
        Bool_t          i_gen_NPackedDtrsHasKVFvertex;
        Double_t        i_gen_NPackedDtrs_KVF_x;
        Double_t        i_gen_NPackedDtrs_KVF_y;
        Double_t        i_gen_NPackedDtrs_KVF_z;
        Double_t        i_gen_NPackedDtrs_KVF_cxx;
        Double_t        i_gen_NPackedDtrs_KVF_cyy;
        Double_t        i_gen_NPackedDtrs_KVF_czz;
        Double_t        i_gen_NPackedDtrs_KVF_cyx;
        Double_t        i_gen_NPackedDtrs_KVF_czy;
        Double_t        i_gen_NPackedDtrs_KVF_czx;
        Double_t        i_gen_NPackedDtrs_KVF_df;
        Double_t        i_gen_NPackedDtrs_KVF_chi2;
        unsigned        i_gen_NPackedDtrs_KVF_ntracks;
        unsigned        i_gen_nNdaughters;
        unsigned        i_gen_Ndaughters_pdg[30];   //[_gen_nNdaughters]
        Double_t        i_gen_Ndaughters_Pt[30];
        Double_t        i_gen_Ndaughters_Eta[30];
        Double_t        i_gen_Ndaughters_Phi[30];
        Double_t        i_gen_Ndaughters_E[30];
        Int_t           i_gen_Ndaughters_Charge[30];
        //UChar_t         i_gen_nstatus23;
        //UChar_t         i_gen_nstatus23_fromN;
        //UChar_t         i_gen_nstatus23_fromW;
        //Int_t           i_gen_status23_pdg[5];   //[_gen_nstatus23]
        //unsigned        i_gen_status23_fromN_pdg[3];   //[_gen_nstatus23_fromN]
        //unsigned        i_gen_status23_fromW_pdg[1];   //[_gen_nstatus23_fromW]
        unsigned        i_gen_nq;
        Double_t        i_gen_qPt[2];   //[_gen_nq23]
        Double_t        i_gen_qEta[2];   //[_gen_nq23]
        Double_t        i_gen_qPhi[2];   //[_gen_nq23]
        Double_t        i_gen_qE[2];   //[_gen_nq23]
        Bool_t          i_passMETFilters;
        Bool_t          i_Flag_goodVertices;
        Bool_t          i_Flag_HBHENoiseFilter;
        Bool_t          i_Flag_HBHENoiseIsoFilter;
        Bool_t          i_Flag_EcalDeadCellTriggerPrimitiveFilter;
        Bool_t          i_Flag_BadPFMuonFilter;
        Bool_t          i_Flag_BadChargedCandidateFilter;
        Bool_t          i_Flag_globalSuperTightHalo2016Filter;
        Bool_t          i_HLT_Ele27_WPTight_Gsf;
        Int_t           i_HLT_Ele27_WPTight_Gsf_prescale;
        Bool_t          i_HLT_Ele32_WPTight_Gsf;
        Int_t           i_HLT_Ele32_WPTight_Gsf_prescale;
        Bool_t          i_HLT_IsoMu24;
        Int_t           i_HLT_IsoMu24_prescale;
        Bool_t          i_HLT_IsoTkMu24;
        Int_t           i_HLT_IsoTkMu24_prescale;
        Bool_t          i_HLT_IsoMu27;
        Int_t           i_HLT_IsoMu27_prescale;
        Bool_t          i_HLT_IsoMu24_eta2p1;
        Int_t           i_HLT_IsoMu24_eta2p1_prescale;
        Bool_t          i_HLT_MET200;
        Int_t           i_HLT_MET200_prescale;
        Bool_t          i_HLT_PFMET300;
        Int_t           i_HLT_PFMET300_prescale;
        Bool_t          i_HLT_PFMET170_HBHECleaned;
        Int_t           i_HLT_PFMET170_HBHECleaned_prescale;
        Bool_t          i_HLT_PFMET120_PFMHT120_IDTight;
        Int_t           i_HLT_PFMET120_PFMHT120_IDTight_prescale;
        Bool_t          i_HLT_PFMET140_PFMHT140_IDTight;
        Int_t           i_HLT_PFMET140_PFMHT140_IDTight_prescale;
        Bool_t          i_HLT_CaloMET350_HBHECleaned;
        Int_t           i_HLT_CaloMET350_HBHECleaned_prescale;
        Bool_t          i_HLT_PFMET250_HBHECleaned;
        Int_t           i_HLT_PFMET250_HBHECleaned_prescale;
        Bool_t          i_HLT_PFMET200_HBHE_BeamHaloCleaned;
        Int_t           i_HLT_PFMET200_HBHE_BeamHaloCleaned_prescale;
        Bool_t          i_HLT_PFMETTypeOne140_PFMHT140_IDTight;
        Int_t           i_HLT_PFMETTypeOne140_PFMHT140_IDTight_prescale;
        Bool_t          i_HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned;
        Int_t           i_HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_prescale;
        //Bool_t          i_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;
        //Int_t           i_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_prescale;
        //Bool_t          i_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
        //Int_t           i_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
        //Bool_t          i_HLT_Mu8_DiEle12_CaloIdL_TrackIdL;
        //Int_t           i_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_prescale;
        //Bool_t          i_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
        //Int_t           i_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
        //Bool_t          i_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
        //Int_t           i_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_prescale;
        //Bool_t          i_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ;
        //Int_t           i_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
        //Bool_t          i_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL;
        //Int_t           i_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_prescale;
        //Bool_t          i_HLT_DiMu9_Ele9_CaloIdL_TrackIdL;
        //Int_t           i_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_prescale;
        //Bool_t          i_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
        //Int_t           i_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_prescale;
        //Bool_t          i_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
        //Int_t           i_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;
        //Bool_t          i_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
        //Int_t           i_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;
        //Bool_t          i_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
        //Int_t           i_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_prescale;
        //Bool_t          i_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
        //Int_t           i_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;
        //Bool_t          i_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
        //Int_t           i_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;
        //Bool_t          i_HLT_TripleMu_12_10_5;
        //Int_t           i_HLT_TripleMu_12_10_5_prescale;
        //Bool_t          i_passMETFilters;
        //Bool_t          i_Flag_HBHENoiseFilter;
        //Bool_t          i_Flag_HBHENoiseIsoFilter;
        //Bool_t          i_Flag_EcalDeadCellTriggerPrimitiveFilter;
        //Bool_t          i_Flag_goodVertices;
        //Bool_t          i_Flag_BadPFMuonFilter;
        //Bool_t          i_Flag_BadChargedCandidateFilter;
        //Bool_t          i_Flag_globalTightHalo2016Filter;
        //Bool_t          i_HLT_Ele105_CaloIdVT_GsfTrkIdT;
        //Int_t           i_HLT_Ele105_CaloIdVT_GsfTrkIdT_prescale;
        //Bool_t          i_HLT_Ele115_CaloIdVT_GsfTrkIdT;
        //Int_t           i_HLT_Ele115_CaloIdVT_GsfTrkIdT_prescale;
        //Bool_t          i_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
        //Int_t           i_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
        //Bool_t          i_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL;
        //Int_t           i_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_prescale;
        //Bool_t          i_HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL;
        //Int_t           i_HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_prescale;
        //Bool_t          i_HLT_Mu50;
        //Int_t           i_HLT_Mu50_prescale;
        //Bool_t          i_HLT_TkMu50;
        //Int_t           i_HLT_TkMu50_prescale;
        //Bool_t          i_HLT_Mu45_eta2p1;
        //Int_t           i_HLT_Mu45_eta2p1_prescale;
        //Bool_t          i_HLT_Mu30_TkMu11;
        //Int_t           i_HLT_Mu30_TkMu11_prescale;
        unsigned        i_nL;
        unsigned        i_nMu;
        unsigned        i_nEle;
        unsigned        i_nLight;
        unsigned        i_nTau;
        Double_t        i_lPt[10];   //[_nL]
        Double_t        i_lEta[10];   //[_nL]
        Double_t        i_lEtaSC[10];   //[_nLight]
        Double_t        i_lPhi[10];   //[_nL]
        Double_t        i_lE[10];   //[_nL]
        unsigned        i_lFlavor[10];   //[_nL]
        Int_t           i_lCharge[10];   //[_nL]
        Double_t        i_dxy[10];   //[_nL]
        Double_t        i_dz[10];   //[_nL]
        Double_t        i_3dIP[10];   //[_nL]
        Double_t        i_3dIPSig[10];   //[_nL]
        Double_t        i_lElectronSummer16MvaGP[10];
        Double_t        i_lElectronSummer16MvaHZZ[10];
        Double_t        i_lElectronMvaFall17v1NoIso[10];
        Double_t        i_lElectronMvaFall17Iso[10];
        Double_t        i_lElectronMvaFall17NoIso[10];
        Bool_t          i_lElectronPassEmu[10];   //[_nLight]
        Bool_t          i_lElectronPassConvVeto[10];   //[_nLight]
        Bool_t          i_lElectronChargeConst[10];   //[_nLight]
        unsigned        i_lElectronMissingHits[10];   //[_nLight]
        Bool_t          i_lElectronIsEB[10];                                                                         //electron specific variables for displaced electron ID
        Bool_t          i_lElectronIsEE[10];
        Double_t        i_lElectronSuperClusterOverP[10];
        Double_t        i_lElectronEcalEnergy[10];
        Double_t        i_lElectronSigmaIetaIeta[10];
        Double_t        i_lElectronDEtaInSeed[10];
        Double_t        i_lElectronDeltaPhiSuperClusterTrack[10];
        Double_t        i_lElectronDeltaEtaSuperClusterTrack[10];
        Double_t        i_lElectronHOverE[10];
        Double_t        i_lElectronEInvMinusPInv[10];
        Double_t        i_lElectronNumberInnerHitsMissing[10];
        Double_t        i_leptonMvaTTH[10];
        Double_t        i_leptonMvatZq[10];
        Double_t        i_leptonMvaTOP[10];
        Bool_t          i_lPOGVeto[10];   //[_nL]
        Bool_t          i_lPOGLoose[10];   //[_nL]
        Bool_t          i_lPOGMedium[10];   //[_nL]
        Bool_t          i_lPOGTight[10];   //[_nL]
        Bool_t          i_tauMuonVetoLoose[10];   //[_nL]
        Bool_t          i_tauEleVetoLoose[10];   //[_nL]
        Bool_t          i_decayModeFinding[10];   //[_nL]
        Double_t        i_tauAgainstElectronMVA6Raw[10];
        Double_t        i_tauCombinedIsoDBRaw3Hits[10];
        Double_t        i_tauIsoMVAPWdR03oldDMwLT[10];
        Double_t        i_tauIsoMVADBdR03oldDMwLT[10];
        Double_t        i_tauIsoMVADBdR03newDMwLT[10];
        Double_t        i_tauIsoMVAPWnewDMwLT[10];
        Double_t        i_tauIsoMVAPWoldDMwLT[10];
        Double_t        i_relIso[10];   //[_nLight]
        Double_t        i_relIso0p4[10];   //[_nMu]
        Double_t        i_relIso0p4MuDeltaBeta[10];   //[_nMu]
        Double_t        i_miniIso[10];   //[_nLight]
        Double_t        i_miniIsoCharged[10];   //[_nLight]
        Double_t        i_ptRel[10];   //[_nLight]
        Double_t        i_ptRatio[10];   //[_nLight]
        Double_t        i_closestJetCsvV2[10];   //[_nLight]
        Double_t        i_closestJetDeepCsv_b[10];   //[_nLight]
        Double_t        i_closestJetDeepCsv_bb[10];   //[_nLight]
        Double_t        i_closestJetDeepCsv[10];   //[_nLight]
        Double_t        i_closestJetDeepFlavor_b[10];
        Double_t        i_closestJetDeepFlavor_bb[10];
        Double_t        i_closestJetDeepFlavor_lepb[10];
        Double_t        i_closestJetDeepFlavor[10];
        unsigned        i_selectedTrackMult[10];   //[_nLight]
        //Bool_t          i_lKVF_valid[10];
        //Double_t	    i_lKVF_x[10];
        //Double_t	    i_lKVF_y[10];
        //Double_t	    i_lKVF_z[10];
        //Double_t	    i_lKVF_cxx[10];
        //Double_t	    i_lKVF_cyy[10];
        //Double_t	    i_lKVF_czz[10];
        //Double_t	    i_lKVF_cyx[10];
        //Double_t	    i_lKVF_czy[10];
        //Double_t	    i_lKVF_czx[10];
        //Double_t	    i_lKVF_df[10];
        //Double_t	    i_lKVF_chi2[10];
        //UInt_t	        i_lKVF_ntracks[10];
        //Double_t        i_lKVF_dRcut[10];
        //Double_t        i_lKVF_trackPt[10][15];
        //Double_t        i_lKVF_trackEta[10][15];
        //Double_t        i_lKVF_trackPhi[10][15];
        //Double_t        i_lKVF_trackE[10][15];
        //Double_t        i_lKVF_trackdR[10][15];
        //Double_t        i_lKVF_trackdxy[10][15];
        //Double_t        i_lKVF_trackdz[10][15];
        Double_t        i_IVF_x[10];
        Double_t        i_IVF_y[10];
        Double_t        i_IVF_z[10];
        Double_t        i_IVF_cx[10];
        Double_t        i_IVF_cy[10];
        Double_t        i_IVF_cz[10];
        Double_t        i_IVF_df[10];
        Double_t        i_IVF_chi2[10];
        Double_t        i_IVF_pt[10];
        Double_t        i_IVF_eta[10];
        Double_t        i_IVF_phi[10];
        Double_t        i_IVF_E[10];
        Double_t        i_IVF_mass[10];
        unsigned        i_IVF_ntracks[10];
        Double_t        i_IVF_trackpt[10][15];
        Double_t        i_IVF_tracketa[10][15];
        Double_t        i_IVF_trackphi[10][15];
        Double_t        i_IVF_trackE[10][15];
        Double_t        i_IVF_trackcharge[10][15];
        Bool_t          i_lIVF_match[10];
        Bool_t          i_lGlobalMuon[10];                                                                       //muon speficic variables, also for displaced muon ID
        Bool_t          i_lTrackerMuon[10];
        Double_t        i_lInnerTrackValidFraction[10];
        Double_t        i_lGlobalTrackNormalizedChi2[10];
        Double_t        i_lCQChi2Position[10];
        Double_t        i_lCQTrackKink[10];
        unsigned        i_lNumberOfMatchedStation[10];
        unsigned        i_lNumberOfValidPixelHits[10];
        unsigned        i_lNumberOfValidTrackerHits[10];
        unsigned        i_muNumberInnerHits[10];
        unsigned        i_lTrackerLayersWithMeasurement[10];
        Double_t        i_lMuonSegComp[10];   //[_nMu]
        Double_t        i_lMuonTrackPt[10];   //[_nMu]
        Double_t        i_lMuonTrackPtErr[10];   //[_nMu]
        Int_t           i_lMuonTimenDof[10];
        Double_t        i_lMuonTime[10];
        Double_t        i_lMuonTimeErr[10];
        Int_t           i_lMuonRPCTimenDof[10];
        Double_t        i_lMuonRPCTime[10];
        Double_t        i_lMuonRPCTimeErr[10];
        Bool_t          i_lIsPrompt[10];   //[_nL]
        Int_t           i_lMatchPdgId[10];   //[_nL]
        Int_t           i_lMatchCharge[10];   //[_nL]
        Int_t           i_tauGenStatus[10];   //[_nL]
        Int_t           i_lMomPdgId[10];
        unsigned        i_lProvenance[10];
        unsigned        i_lProvenanceCompressed[10];
        unsigned        i_lProvenanceConversion[10];
        Double_t        i_lPtCorr[10];
        Double_t        i_lPtScaleUp[10];
        Double_t        i_lPtScaleDown[10];
        Double_t        i_lPtResUp[10];
        Double_t        i_lPtResDown[10];//ECorr, EScaleUp can be calculated with ECorr/E = PtCorr/Pt and analogue for the others
        unsigned        i_nPh;
        Double_t        i_phPt[10];   //[_nPh]
        Double_t        i_phEta[10];   //[_nPh]
        Double_t        i_phEtaSC[10];   //[_nPh]
        Double_t        i_phPhi[10];   //[_nPh]
        Double_t        i_phE[10];   //[_nPh]
        Bool_t          i_phCutBasedLoose[10];   //[_nPh]
        Bool_t          i_phCutBasedMedium[10];   //[_nPh]
        Bool_t          i_phCutBasedTight[10];   //[_nPh]
        Double_t        i_phMva[10];   //[_nPh]
        Double_t        i_phRandomConeChargedIsolation[10];   //[_nPh]
        Double_t        i_phChargedIsolation[10];   //[_nPh]
        Double_t        i_phNeutralHadronIsolation[10];   //[_nPh]
        Double_t        i_phPhotonIsolation[10];   //[_nPh]
        Double_t        i_phSigmaIetaIeta[10];   //[_nPh]
        Double_t        i_phHadronicOverEm[10];   //[_nPh]
        Double_t        i_phHadTowOverEm[10];
        Bool_t          i_phPassElectronVeto[10];   //[_nPh]
        Bool_t          i_phHasPixelSeed[10];   //[_nPh]
        Bool_t          i_phIsPrompt[10];   //[_nPh]
        Int_t           i_phMatchPdgId[10];   //[_nPh]
        Double_t        i_phPtCorr[10];
        Double_t        i_phPtScaleUp[10];
        Double_t        i_phPtScaleDown[10];
        Double_t        i_phPtResUp[10];
        Double_t        i_phPtResDown[10];//ECorr,... same as for electrons
        unsigned        i_nJets;
        Double_t        i_jetPt[20];   //[_nJets]
        Double_t        i_jetPt_JECUp[20];   //[_nJets]
        Double_t        i_jetPt_JECDown[20];   //[_nJets]
        Double_t        i_jetPt_Uncorrected[20];   //[_nJets]
        Double_t        i_jetPt_L1[20];   //[_nJets]
        Double_t        i_jetPt_L2[20];   //[_nJets]
        Double_t        i_jetPt_L3[20];   //[_nJets]
        Double_t        i_jetSmearedPt[20];
        Double_t        i_jetSmearedPt_JECDown[20];
        Double_t        i_jetSmearedPt_JECUp[20];
        Double_t        i_jetSmearedPt_JERDown[20];
        Double_t        i_jetSmearedPt_JERUp[20];
        Double_t        i_jetEta[20];   //[_nJets]
        Double_t        i_jetPhi[20];   //[_nJets]
        Double_t        i_jetE[20];   //[_nJets]
        Double_t        i_jetCsvV2[20];   //[_nJets]
        Double_t        i_jetDeepCsv_udsg[20];   //[_nJets]
        Double_t        i_jetDeepCsv_b[20];   //[_nJets]
        Double_t        i_jetDeepCsv_c[20];   //[_nJets]
        Double_t        i_jetDeepCsv_bb[20];   //[_nJets]
        Double_t        i_jetDeepCsv[20];   //[_nJets]
        Double_t        i_jetDeepFlavor_b[20];
        Double_t        i_jetDeepFlavor_bb[20];
        Double_t        i_jetDeepFlavor_lepb[20];
        Double_t        i_jetDeepFlavor[20];
        Double_t        i_jetDeepFlavor_c[20];
        Double_t        i_jetDeepFlavor_uds[20];
        Double_t        i_jetDeepFlavor_g[20];
        unsigned        i_jetHadronFlavor[20];   //[_nJets]
        //Bool_t          i_jetIsLoose[20];   //[_nJets]
        Bool_t          i_jetIsTight[20];   //[_nJets]
        Bool_t          i_jetIsTightLepVeto[20];   //[_nJets]
        Double_t        i_jetNeutralHadronFraction[20];
        Double_t        i_jetChargedHadronFraction[20];
        Double_t        i_jetNeutralEmFraction[20];
        Double_t        i_jetChargedEmFraction[20];
        Double_t        i_jetHFHadronFraction[20];
        Double_t        i_jetHFEmFraction[20];
        unsigned        i_nJetConstituents[20];
        Double_t        i_JetConstituentPt[20][50];
        Double_t        i_JetConstituentEta[20][50];
        Double_t        i_JetConstituentPhi[20][50];
        Double_t        i_JetConstituentMass[20][50];
        Int_t           i_JetConstituentPdgId[20][50];
        Double_t        i_JetConstituentPdgIdReduced[20][50];
        Int_t           i_JetConstituentCharge[20][50];
        Double_t        i_JetConstituentdxy[20][50];
        Double_t        i_JetConstituentdz[20][50];
        Double_t        i_JetConstituentdxyErr[20][50];
        Double_t        i_JetConstituentdzErr[20][50];
        Int_t           i_JetConstituentNumberOfHits[20][50];
        Int_t           i_JetConstituentNumberOfPixelHits[20][50];
        Bool_t          i_JetConstituentHasTrack[20][50];
        Double_t        i_met;
        Double_t        i_metRaw;
        Double_t        i_metJECDown;
        Double_t        i_metJECUp;
        Double_t        i_metUnclDown;
        Double_t        i_metUnclUp;
        Double_t        i_metPhi;
        Double_t        i_metRawPhi;
        Double_t        i_metPhiJECDown;
        Double_t        i_metPhiJECUp;
        Double_t        i_metPhiUnclDown;
        Double_t        i_metPhiUnclUp;
        Double_t        i_metSignificance;                                                              

        TFile* output;
        TTree* outputtree;
        ULong64_t       o_runNb;
        ULong64_t       o_lumiBlock;
        ULong64_t       o_eventNb;
        UChar_t         o_nVertex;
        Bool_t          o_is2017;
        Bool_t          o_is2018;
        Double_t        o_BS_x;
        Double_t        o_BS_y;
        Double_t        o_BS_z;
        Double_t        o_BS_xErr;
        Double_t        o_BS_yErr;
        Double_t        o_BS_zErr;
        Double_t        o_PV_x;
        Double_t        o_PV_y;
        Double_t        o_PV_z;
        Double_t        o_PV_xErr;
        Double_t        o_PV_yErr;
        Double_t        o_PV_zErr;
        Float_t         o_prefireWeight;
        Float_t         o_prefireWeightUp;
        Float_t         o_prefireWeightDown;
        Float_t         o_nTrueInt;
        Double_t        o_weight;
        Double_t        o_lheHTIncoming;
        Double_t        o_ctauHN;
        unsigned        o_nLheTau;
        unsigned        o_nLheWeights;
        Double_t        o_lheWeight[110];   //[_nLheWeights]
        unsigned        o_nPsWeights;
        Double_t        o_psWeight[110];   //[_nLheWeights]
        unsigned        o_ttgEventType;
        unsigned        o_zgEventType;
        Double_t        o_gen_met;
        Double_t        o_gen_metPhi;
        unsigned        o_gen_nPh;
        unsigned        o_gen_phStatus[20];
        Double_t        o_gen_phPt[20];   //[_gen_nPh]
        Double_t        o_gen_phEta[20];   //[_gen_nPh]
        Double_t        o_gen_phPhi[20];   //[_gen_nPh]
        Double_t        o_gen_phE[20];   //[_gen_nPh]
        Int_t           o_gen_phMomPdg[20];   //[_gen_nPh]
        Bool_t          o_gen_phIsPrompt[20];   //[_gen_nPh]
        Double_t        o_gen_phMinDeltaR[20];   //[_gen_nPh]
        Bool_t          o_gen_phPassParentage[20];   //[_gen_nPh]
        unsigned        o_gen_nL;
        Double_t        o_gen_lPt[20];   //[_gen_nL]
        Double_t        o_gen_lEta[20];   //[_gen_nL]
        Double_t        o_gen_lPhi[20];   //[_gen_nL]
        Double_t        o_gen_lE[20];   //[_gen_nL]
        unsigned        o_gen_lFlavor[20];   //[_gen_nL]
        Int_t           o_gen_lCharge[20];   //[_gen_nL]
        Int_t           o_gen_lMomPdg[20];   //[_gen_nL]
        Double_t        o_gen_vertex_x[20];
        Double_t        o_gen_vertex_y[20];
        Double_t        o_gen_vertex_z[20];
        Bool_t          o_gen_lIsPrompt[20];   //[_gen_nL]
        Bool_t          o_gen_lDecayedHadr[20];
        Double_t        o_gen_lMinDeltaR[20];   //[_gen_nL]
        Bool_t          o_gen_lPassParentage[20];   //[_gen_nL]
        Bool_t          o_hasInternalConversion;   //[_gen_nL]
        unsigned        o_gen_nN;
        Double_t        o_gen_NPt;
        Double_t        o_gen_NEta;
        Double_t        o_gen_NPhi;
        Double_t        o_gen_NE;
        Double_t        o_gen_Nvertex_x;
        Double_t        o_gen_Nvertex_y;
        Double_t        o_gen_Nvertex_z;
        unsigned        o_gen_nNPackedDtrs;
        Double_t        o_gen_NPackedDtrsPt[20];
        Double_t        o_gen_NPackedDtrsEta[20];
        Double_t        o_gen_NPackedDtrsPhi[20];
        Double_t        o_gen_NPackedDtrsE[20];
        Int_t           o_gen_NPackedDtrsPdgId[20];
        Int_t           o_gen_NPackedDtrsCharge[20];
        Double_t        o_gen_NPackedDtrsRecodR[20];
        Double_t        o_gen_NPackedDtrsRecodptoverpt[20];
        Double_t        o_gen_NPackedDtrsRecoPt[20];
        Double_t        o_gen_NPackedDtrsRecoEta[20];
        Double_t        o_gen_NPackedDtrsRecoPhi[20];
        Double_t        o_gen_NPackedDtrsRecoE[20];
        Int_t           o_gen_NPackedDtrsRecoPdgId[20];
        Double_t        o_gen_NPackedDtrsRecodxy[20];
        Double_t        o_gen_NPackedDtrsRecodz[20];
        Bool_t          o_gen_NPackedDtrsHasReco[20];
        unsigned        o_gen_nNPackedDtrsPCA;
        Double_t        o_gen_NPackedDtrsPCADist[20];
        Double_t        o_gen_NPackedDtrsPCAX0[20];
        Double_t        o_gen_NPackedDtrsPCAY0[20];
        Double_t        o_gen_NPackedDtrsPCAZ0[20];
        Double_t        o_gen_NPackedDtrsPCAX1[20];
        Double_t        o_gen_NPackedDtrsPCAY1[20];
        Double_t        o_gen_NPackedDtrsPCAZ1[20];
        Double_t        o_gen_NPackedDtrsPCAX2[20];
        Double_t        o_gen_NPackedDtrsPCAY2[20];
        Double_t        o_gen_NPackedDtrsPCAZ2[20];
        Double_t        o_gen_NPackedDtrsPCAPhi1[20];
        Double_t        o_gen_NPackedDtrsPCAPhi2[20];
        unsigned        o_gen_NPackedDtrsPCAIndex1[20];
        unsigned        o_gen_NPackedDtrsPCAIndex2[20];
        Bool_t          o_gen_NPackedDtrsHasKVFvertex;
        Double_t        o_gen_NPackedDtrs_KVF_x;
        Double_t        o_gen_NPackedDtrs_KVF_y;
        Double_t        o_gen_NPackedDtrs_KVF_z;
        Double_t        o_gen_NPackedDtrs_KVF_cxx;
        Double_t        o_gen_NPackedDtrs_KVF_cyy;
        Double_t        o_gen_NPackedDtrs_KVF_czz;
        Double_t        o_gen_NPackedDtrs_KVF_cyx;
        Double_t        o_gen_NPackedDtrs_KVF_czy;
        Double_t        o_gen_NPackedDtrs_KVF_czx;
        Double_t        o_gen_NPackedDtrs_KVF_df;
        Double_t        o_gen_NPackedDtrs_KVF_chi2;
        unsigned        o_gen_NPackedDtrs_KVF_ntracks;
        unsigned        o_gen_nNdaughters;
        unsigned        o_gen_Ndaughters_pdg[30];   //[_gen_nNdaughters]
        Double_t        o_gen_Ndaughters_Pt[30];
        Double_t        o_gen_Ndaughters_Eta[30];
        Double_t        o_gen_Ndaughters_Phi[30];
        Double_t        o_gen_Ndaughters_E[30];
        Int_t           o_gen_Ndaughters_Charge[30];
        //UChar_t         o_gen_nstatus23;
        //UChar_t         o_gen_nstatus23_fromN;
        //UChar_t         o_gen_nstatus23_fromW;
        //Int_t           o_gen_status23_pdg[5];   //[_gen_nstatus23]
        //unsigned        o_gen_status23_fromN_pdg[3];   //[_gen_nstatus23_fromN]
        //unsigned        o_gen_status23_fromW_pdg[1];   //[_gen_nstatus23_fromW]
        unsigned        o_gen_nq;
        Double_t        o_gen_qPt[2];   //[_gen_nq23]
        Double_t        o_gen_qEta[2];   //[_gen_nq23]
        Double_t        o_gen_qPhi[2];   //[_gen_nq23]
        Double_t        o_gen_qE[2];   //[_gen_nq23]
        Bool_t          o_passMETFilters;
        Bool_t          o_Flag_goodVertices;
        Bool_t          o_Flag_HBHENoiseFilter;
        Bool_t          o_Flag_HBHENoiseIsoFilter;
        Bool_t          o_Flag_EcalDeadCellTriggerPrimitiveFilter;
        Bool_t          o_Flag_BadPFMuonFilter;
        Bool_t          o_Flag_BadChargedCandidateFilter;
        Bool_t          o_Flag_globalSuperTightHalo2016Filter;
        Bool_t          o_HLT_Ele27_WPTight_Gsf;
        Int_t           o_HLT_Ele27_WPTight_Gsf_prescale;
        Bool_t          o_HLT_Ele32_WPTight_Gsf;
        Int_t           o_HLT_Ele32_WPTight_Gsf_prescale;
        Bool_t          o_HLT_IsoMu24;
        Int_t           o_HLT_IsoMu24_prescale;
        Bool_t          o_HLT_IsoTkMu24;
        Int_t           o_HLT_IsoTkMu24_prescale;
        Bool_t          o_HLT_IsoMu27;
        Int_t           o_HLT_IsoMu27_prescale;
        Bool_t          o_HLT_IsoMu24_eta2p1;
        Int_t           o_HLT_IsoMu24_eta2p1_prescale;
        Bool_t          o_HLT_MET200;
        Int_t           o_HLT_MET200_prescale;
        Bool_t          o_HLT_PFMET300;
        Int_t           o_HLT_PFMET300_prescale;
        Bool_t          o_HLT_PFMET170_HBHECleaned;
        Int_t           o_HLT_PFMET170_HBHECleaned_prescale;
        Bool_t          o_HLT_PFMET120_PFMHT120_IDTight;
        Int_t           o_HLT_PFMET120_PFMHT120_IDTight_prescale;
        Bool_t          o_HLT_PFMET140_PFMHT140_IDTight;
        Int_t           o_HLT_PFMET140_PFMHT140_IDTight_prescale;
        Bool_t          o_HLT_CaloMET350_HBHECleaned;
        Int_t           o_HLT_CaloMET350_HBHECleaned_prescale;
        Bool_t          o_HLT_PFMET250_HBHECleaned;
        Int_t           o_HLT_PFMET250_HBHECleaned_prescale;
        Bool_t          o_HLT_PFMET200_HBHE_BeamHaloCleaned;
        Int_t           o_HLT_PFMET200_HBHE_BeamHaloCleaned_prescale;
        Bool_t          o_HLT_PFMETTypeOne140_PFMHT140_IDTight;
        Int_t           o_HLT_PFMETTypeOne140_PFMHT140_IDTight_prescale;
        Bool_t          o_HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned;
        Int_t           o_HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_prescale;
        //Bool_t          o_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;
        //Int_t           o_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_prescale;
        //Bool_t          o_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
        //Int_t           o_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
        //Bool_t          o_HLT_Mu8_DiEle12_CaloIdL_TrackIdL;
        //Int_t           o_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_prescale;
        //Bool_t          o_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
        //Int_t           o_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
        //Bool_t          o_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
        //Int_t           o_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_prescale;
        //Bool_t          o_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ;
        //Int_t           o_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
        //Bool_t          o_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL;
        //Int_t           o_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_prescale;
        //Bool_t          o_HLT_DiMu9_Ele9_CaloIdL_TrackIdL;
        //Int_t           o_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_prescale;
        //Bool_t          o_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
        //Int_t           o_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_prescale;
        //Bool_t          o_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
        //Int_t           o_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;
        //Bool_t          o_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
        //Int_t           o_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;
        //Bool_t          o_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
        //Int_t           o_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_prescale;
        //Bool_t          o_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
        //Int_t           o_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;
        //Bool_t          o_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
        //Int_t           o_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;
        //Bool_t          o_HLT_TripleMu_12_10_5;
        //Int_t           o_HLT_TripleMu_12_10_5_prescale;
        //Bool_t          o_passMETFilters;
        //Bool_t          o_Flag_HBHENoiseFilter;
        //Bool_t          o_Flag_HBHENoiseIsoFilter;
        //Bool_t          o_Flag_EcalDeadCellTriggerPrimitiveFilter;
        //Bool_t          o_Flag_goodVertices;
        //Bool_t          o_Flag_BadPFMuonFilter;
        //Bool_t          o_Flag_BadChargedCandidateFilter;
        //Bool_t          o_Flag_globalTightHalo2016Filter;
        //Bool_t          o_HLT_Ele105_CaloIdVT_GsfTrkIdT;
        //Int_t           o_HLT_Ele105_CaloIdVT_GsfTrkIdT_prescale;
        //Bool_t          o_HLT_Ele115_CaloIdVT_GsfTrkIdT;
        //Int_t           o_HLT_Ele115_CaloIdVT_GsfTrkIdT_prescale;
        //Bool_t          o_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
        //Int_t           o_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;
        //Bool_t          o_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL;
        //Int_t           o_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_prescale;
        //Bool_t          o_HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL;
        //Int_t           o_HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_prescale;
        //Bool_t          o_HLT_Mu50;
        //Int_t           o_HLT_Mu50_prescale;
        //Bool_t          o_HLT_TkMu50;
        //Int_t           o_HLT_TkMu50_prescale;
        //Bool_t          o_HLT_Mu45_eta2p1;
        //Int_t           o_HLT_Mu45_eta2p1_prescale;
        //Bool_t          o_HLT_Mu30_TkMu11;
        //Int_t           o_HLT_Mu30_TkMu11_prescale;
        unsigned        o_nL;
        unsigned        o_nMu;
        unsigned        o_nEle;
        unsigned        o_nLight;
        unsigned        o_nTau;
        Double_t        o_lPt[10];   //[_nL]
        Double_t        o_lEta[10];   //[_nL]
        Double_t        o_lEtaSC[10];   //[_nLight]
        Double_t        o_lPhi[10];   //[_nL]
        Double_t        o_lE[10];   //[_nL]
        unsigned        o_lFlavor[10];   //[_nL]
        Int_t           o_lCharge[10];   //[_nL]
        Double_t        o_dxy[10];   //[_nL]
        Double_t        o_dz[10];   //[_nL]
        Double_t        o_3dIP[10];   //[_nL]
        Double_t        o_3dIPSig[10];   //[_nL]
        Double_t        o_lElectronSummer16MvaGP[10];
        Double_t        o_lElectronSummer16MvaHZZ[10];
        Double_t        o_lElectronMvaFall17v1NoIso[10];
        Double_t        o_lElectronMvaFall17Iso[10];
        Double_t        o_lElectronMvaFall17NoIso[10];
        Bool_t          o_lElectronPassEmu[10];   //[_nLight]
        Bool_t          o_lElectronPassConvVeto[10];   //[_nLight]
        Bool_t          o_lElectronChargeConst[10];   //[_nLight]
        unsigned        o_lElectronMissingHits[10];   //[_nLight]
        Bool_t          o_lElectronIsEB[10];                                                                         //electron specific variables for displaced electron ID
        Bool_t          o_lElectronIsEE[10];
        Double_t        o_lElectronSuperClusterOverP[10];
        Double_t        o_lElectronEcalEnergy[10];
        Double_t        o_lElectronSigmaIetaIeta[10];
        Double_t        o_lElectronDEtaInSeed[10];
        Double_t        o_lElectronDeltaPhiSuperClusterTrack[10];
        Double_t        o_lElectronDeltaEtaSuperClusterTrack[10];
        Double_t        o_lElectronHOverE[10];
        Double_t        o_lElectronEInvMinusPInv[10];
        Double_t        o_lElectronNumberInnerHitsMissing[10];
        Double_t        o_leptonMvaTTH[10];
        Double_t        o_leptonMvatZq[10];
        Double_t        o_leptonMvaTOP[10];
        Bool_t          o_lPOGVeto[10];   //[_nL]
        Bool_t          o_lPOGLoose[10];   //[_nL]
        Bool_t          o_lPOGMedium[10];   //[_nL]
        Bool_t          o_lPOGTight[10];   //[_nL]
        Bool_t          o_tauMuonVetoLoose[10];   //[_nL]
        Bool_t          o_tauEleVetoLoose[10];   //[_nL]
        Bool_t          o_decayModeFinding[10];   //[_nL]
        Double_t        o_tauAgainstElectronMVA6Raw[10];
        Double_t        o_tauCombinedIsoDBRaw3Hits[10];
        Double_t        o_tauIsoMVAPWdR03oldDMwLT[10];
        Double_t        o_tauIsoMVADBdR03oldDMwLT[10];
        Double_t        o_tauIsoMVADBdR03newDMwLT[10];
        Double_t        o_tauIsoMVAPWnewDMwLT[10];
        Double_t        o_tauIsoMVAPWoldDMwLT[10];
        Double_t        o_relIso[10];   //[_nLight]
        Double_t        o_relIso0p4[10];   //[_nMu]
        Double_t        o_relIso0p4MuDeltaBeta[10];   //[_nMu]
        Double_t        o_miniIso[10];   //[_nLight]
        Double_t        o_miniIsoCharged[10];   //[_nLight]
        Double_t        o_ptRel[10];   //[_nLight]
        Double_t        o_ptRatio[10];   //[_nLight]
        Double_t        o_closestJetCsvV2[10];   //[_nLight]
        Double_t        o_closestJetDeepCsv_b[10];   //[_nLight]
        Double_t        o_closestJetDeepCsv_bb[10];   //[_nLight]
        Double_t        o_closestJetDeepCsv[10];
        Double_t        o_closestJetDeepFlavor_b[10];
        Double_t        o_closestJetDeepFlavor_bb[10];
        Double_t        o_closestJetDeepFlavor_lepb[10];
        Double_t        o_closestJetDeepFlavor[10];
        unsigned        o_selectedTrackMult[10];   //[_nLight]
        //Bool_t          o_lKVF_valid[10];
        //Double_t	    o_lKVF_x[10];
        //Double_t	    o_lKVF_y[10];
        //Double_t	    o_lKVF_z[10];
        //Double_t	    o_lKVF_cxx[10];
        //Double_t	    o_lKVF_cyy[10];
        //Double_t	    o_lKVF_czz[10];
        //Double_t	    o_lKVF_cyx[10];
        //Double_t	    o_lKVF_czy[10];
        //Double_t	    o_lKVF_czx[10];
        //Double_t	    o_lKVF_df[10];
        //Double_t	    o_lKVF_chi2[10];
        //UInt_t	        o_lKVF_ntracks[10];
        //Double_t        o_lKVF_dRcut[10];
        //Double_t        o_lKVF_trackPt[10][15];
        //Double_t        o_lKVF_trackEta[10][15];
        //Double_t        o_lKVF_trackPhi[10][15];
        //Double_t        o_lKVF_trackE[10][15];
        //Double_t        o_lKVF_trackdR[10][15];
        //Double_t        o_lKVF_trackdxy[10][15];
        //Double_t        o_lKVF_trackdz[10][15];
        Double_t        o_IVF_x[10];
        Double_t        o_IVF_y[10];
        Double_t        o_IVF_z[10];
        Double_t        o_IVF_cx[10];
        Double_t        o_IVF_cy[10];
        Double_t        o_IVF_cz[10];
        Double_t        o_IVF_df[10];
        Double_t        o_IVF_chi2[10];
        Double_t        o_IVF_pt[10];
        Double_t        o_IVF_eta[10];
        Double_t        o_IVF_phi[10];
        Double_t        o_IVF_E[10];
        Double_t        o_IVF_mass[10];
        unsigned        o_IVF_ntracks[10];
        Double_t        o_IVF_trackpt[10][15];
        Double_t        o_IVF_tracketa[10][15];
        Double_t        o_IVF_trackphi[10][15];
        Double_t        o_IVF_trackE[10][15];
        Double_t        o_IVF_trackcharge[10][15];
        Bool_t          o_lIVF_match[10];
        Bool_t          o_lGlobalMuon[10];                                                                       //muon speficic variables, also for displaced muon ID
        Bool_t          o_lTrackerMuon[10];
        Double_t        o_lInnerTrackValidFraction[10];
        Double_t        o_lGlobalTrackNormalizedChi2[10];
        Double_t        o_lCQChi2Position[10];
        Double_t        o_lCQTrackKink[10];
        unsigned        o_lNumberOfMatchedStation[10];
        unsigned        o_lNumberOfValidPixelHits[10];
        unsigned        o_lNumberOfValidTrackerHits[10];
        unsigned        o_muNumberInnerHits[10];
        unsigned        o_lTrackerLayersWithMeasurement[10];
        Double_t        o_lMuonSegComp[10];   //[_nMu]
        Double_t        o_lMuonTrackPt[10];   //[_nMu]
        Double_t        o_lMuonTrackPtErr[10];   //[_nMu]
        Int_t           o_lMuonTimenDof[10];
        Double_t        o_lMuonTime[10];
        Double_t        o_lMuonTimeErr[10];
        Int_t           o_lMuonRPCTimenDof[10];
        Double_t        o_lMuonRPCTime[10];
        Double_t        o_lMuonRPCTimeErr[10];
        Bool_t          o_lIsPrompt[10];   //[_nL]
        Int_t           o_lMatchPdgId[10];   //[_nL]
        Int_t           o_lMatchCharge[10];   //[_nL]
        Int_t           o_tauGenStatus[10];   //[_nL]
        Int_t           o_lMomPdgId[10];
        unsigned        o_lProvenance[10];
        unsigned        o_lProvenanceCompressed[10];
        unsigned        o_lProvenanceConversion[10];
        Double_t        o_lPtCorr[10];
        Double_t        o_lPtScaleUp[10];
        Double_t        o_lPtScaleDown[10];
        Double_t        o_lPtResUp[10];
        Double_t        o_lPtResDown[10];//ECorr, EScaleUp can be calculated with ECorr/E = PtCorr/Pt and analogue for the others
        unsigned        o_nPh;
        Double_t        o_phPt[10];   //[_nPh]
        Double_t        o_phEta[10];   //[_nPh]
        Double_t        o_phEtaSC[10];   //[_nPh]
        Double_t        o_phPhi[10];   //[_nPh]
        Double_t        o_phE[10];   //[_nPh]
        Bool_t          o_phCutBasedLoose[10];   //[_nPh]
        Bool_t          o_phCutBasedMedium[10];   //[_nPh]
        Bool_t          o_phCutBasedTight[10];   //[_nPh]
        Double_t        o_phMva[10];   //[_nPh]
        Double_t        o_phRandomConeChargedIsolation[10];   //[_nPh]
        Double_t        o_phChargedIsolation[10];   //[_nPh]
        Double_t        o_phNeutralHadronIsolation[10];   //[_nPh]
        Double_t        o_phPhotonIsolation[10];   //[_nPh]
        Double_t        o_phSigmaIetaIeta[10];   //[_nPh]
        Double_t        o_phHadronicOverEm[10];   //[_nPh]
        Double_t        o_phHadTowOverEm[10];
        Bool_t          o_phPassElectronVeto[10];   //[_nPh]
        Bool_t          o_phHasPixelSeed[10];   //[_nPh]
        Bool_t          o_phIsPrompt[10];   //[_nPh]
        Int_t           o_phMatchPdgId[10];   //[_nPh]
        Double_t        o_phPtCorr[10];
        Double_t        o_phPtScaleUp[10];
        Double_t        o_phPtScaleDown[10];
        Double_t        o_phPtResUp[10];
        Double_t        o_phPtResDown[10];//ECorr,... same as for electrons
        unsigned        o_nJets;
        Double_t        o_jetPt[20];   //[_nJets]
        Double_t        o_jetPt_JECUp[20];   //[_nJets]
        Double_t        o_jetPt_JECDown[20];   //[_nJets]
        Double_t        o_jetPt_Uncorrected[20];   //[_nJets]
        Double_t        o_jetPt_L1[20];   //[_nJets]
        Double_t        o_jetPt_L2[20];   //[_nJets]
        Double_t        o_jetPt_L3[20];   //[_nJets]
        Double_t        o_jetSmearedPt[20];
        Double_t        o_jetSmearedPt_JECDown[20];
        Double_t        o_jetSmearedPt_JECUp[20];
        Double_t        o_jetSmearedPt_JERDown[20];
        Double_t        o_jetSmearedPt_JERUp[20];
        Double_t        o_jetEta[20];   //[_nJets]
        Double_t        o_jetPhi[20];   //[_nJets]
        Double_t        o_jetE[20];   //[_nJets]
        Double_t        o_jetCsvV2[20];   //[_nJets]
        Double_t        o_jetDeepCsv_udsg[20];   //[_nJets]
        Double_t        o_jetDeepCsv_b[20];   //[_nJets]
        Double_t        o_jetDeepCsv_c[20];   //[_nJets]
        Double_t        o_jetDeepCsv_bb[20];   //[_nJets]
        Double_t        o_jetDeepCsv[20];   //[_nJets]
        Double_t        o_jetDeepFlavor_b[20];
        Double_t        o_jetDeepFlavor_bb[20];
        Double_t        o_jetDeepFlavor_lepb[20];
        Double_t        o_jetDeepFlavor[20];
        Double_t        o_jetDeepFlavor_c[20];
        Double_t        o_jetDeepFlavor_uds[20];
        Double_t        o_jetDeepFlavor_g[20];
        unsigned        o_jetHadronFlavor[20];   //[_nJets]
        //Bool_t          o_jetIsLoose[20];   //[_nJets]
        Bool_t          o_jetIsTight[20];   //[_nJets]
        Bool_t          o_jetIsTightLepVeto[20];   //[_nJets]
        Double_t        o_jetNeutralHadronFraction[20];
        Double_t        o_jetChargedHadronFraction[20];
        Double_t        o_jetNeutralEmFraction[20];
        Double_t        o_jetChargedEmFraction[20];
        Double_t        o_jetHFHadronFraction[20];
        Double_t        o_jetHFEmFraction[20];
        unsigned        o_nJetConstituents[20];
        Double_t        o_JetConstituentPt[20][50];
        Double_t        o_JetConstituentEta[20][50];
        Double_t        o_JetConstituentPhi[20][50];
        Double_t        o_JetConstituentMass[20][50];
        Int_t           o_JetConstituentPdgId[20][50];
        Double_t        o_JetConstituentPdgIdReduced[20][50];
        Int_t           o_JetConstituentCharge[20][50];
        Double_t        o_JetConstituentdxy[20][50];
        Double_t        o_JetConstituentdz[20][50];
        Double_t        o_JetConstituentdxyErr[20][50];
        Double_t        o_JetConstituentdzErr[20][50];
        Int_t           o_JetConstituentNumberOfHits[20][50];
        Int_t           o_JetConstituentNumberOfPixelHits[20][50];
        Bool_t          o_JetConstituentHasTrack[20][50];
        Double_t        o_met;
        Double_t        o_metRaw;
        Double_t        o_metJECDown;
        Double_t        o_metJECUp;
        Double_t        o_metUnclDown;
        Double_t        o_metUnclUp;
        Double_t        o_metPhi;
        Double_t        o_metRawPhi;
        Double_t        o_metPhiJECDown;
        Double_t        o_metPhiJECUp;
        Double_t        o_metPhiUnclDown;
        Double_t        o_metPhiUnclUp;
        Double_t        o_metSignificance;                                              

        TBranch        *bi__runNb;   //!
        TBranch        *bi__lumiBlock;   //!
        TBranch        *bi__eventNb;   //!
        TBranch        *bi__nVertex;   //!
        TBranch        *bi__is2017;   //!
        TBranch        *bi__is2018;   //!
        TBranch        *bi__BS_x;
        TBranch        *bi__BS_y;
        TBranch        *bi__BS_z;
        TBranch        *bi__BS_xErr;
        TBranch        *bi__BS_yErr;
        TBranch        *bi__BS_zErr;
        TBranch        *bi__PV_x;
        TBranch        *bi__PV_y;
        TBranch        *bi__PV_z;
        TBranch        *bi__PV_xErr;
        TBranch        *bi__PV_yErr;
        TBranch        *bi__PV_zErr;
        TBranch        *bi__prefireWeight;
        TBranch        *bi__prefireWeightUp;
        TBranch        *bi__prefireWeightDown;
        TBranch        *bi__nTrueInt;   //!
        TBranch        *bi__weight;   //!
        TBranch        *bi__lheHTIncoming;   //!
        TBranch        *bi__ctauHN;   //!
        TBranch        *bi__nLheTau;
        TBranch        *bi__nLheWeights;   //!
        TBranch        *bi__lheWeight;   //!
        TBranch        *bi__nPsWeights;   //!
        TBranch        *bi__psWeight;   //!
        TBranch        *bi__ttgEventType;   //!
        TBranch        *bi__zgEventType;   //!
        TBranch        *bi__gen_met;   //!
        TBranch        *bi__gen_metPhi;   //!
        TBranch        *bi__gen_nPh;   //!
        TBranch        *bi__gen_phStatus;   //!
        TBranch        *bi__gen_phPt;   //!
        TBranch        *bi__gen_phEta;   //!
        TBranch        *bi__gen_phPhi;   //!
        TBranch        *bi__gen_phE;   //!
        TBranch        *bi__gen_phMomPdg;   //!
        TBranch        *bi__gen_phIsPrompt;   //!
        TBranch        *bi__gen_phMinDeltaR;   //!
        TBranch        *bi__gen_phPassParentage;   //!
        TBranch        *bi__gen_nL;   //!
        TBranch        *bi__gen_lPt;   //!
        TBranch        *bi__gen_lEta;   //!
        TBranch        *bi__gen_lPhi;   //!
        TBranch        *bi__gen_lE;   //!
        TBranch        *bi__gen_lFlavor;   //!
        TBranch        *bi__gen_lCharge;   //!
        TBranch        *bi__gen_lMomPdg;   //!
        TBranch        *bi__gen_vertex_x;  //!
        TBranch        *bi__gen_vertex_y;  //!
        TBranch        *bi__gen_vertex_z;  //!
        TBranch        *bi__gen_lIsPrompt;   //!
        TBranch        *bi__gen_lDecayedHadr;   //!
        TBranch        *bi__gen_lMinDeltaR;   //!
        TBranch        *bi__gen_lPassParentage;   //!
        TBranch        *bi__hasInternalConversion;   //!
        TBranch        *bi__gen_nN;   //!
        TBranch        *bi__gen_NPt;
        TBranch        *bi__gen_NEta;
        TBranch        *bi__gen_NPhi;
        TBranch        *bi__gen_NE;
        TBranch        *bi__gen_Nvertex_x;
        TBranch        *bi__gen_Nvertex_y;
        TBranch        *bi__gen_Nvertex_z;
        TBranch        *bi__gen_nNPackedDtrs;
        TBranch        *bi__gen_NPackedDtrsPt;
        TBranch        *bi__gen_NPackedDtrsEta;
        TBranch        *bi__gen_NPackedDtrsPhi;
        TBranch        *bi__gen_NPackedDtrsE;
        TBranch        *bi__gen_NPackedDtrsPdgId;
        TBranch        *bi__gen_NPackedDtrsCharge;
        TBranch        *bi__gen_NPackedDtrsRecodR;
        TBranch        *bi__gen_NPackedDtrsRecodptoverpt;
        TBranch        *bi__gen_NPackedDtrsRecoPt;
        TBranch        *bi__gen_NPackedDtrsRecoEta;
        TBranch        *bi__gen_NPackedDtrsRecoPhi;
        TBranch        *bi__gen_NPackedDtrsRecoE;
        TBranch        *bi__gen_NPackedDtrsRecoPdgId;
        TBranch        *bi__gen_NPackedDtrsRecodxy;
        TBranch        *bi__gen_NPackedDtrsRecodz;
        TBranch        *bi__gen_NPackedDtrsHasReco;
        TBranch        *bi__gen_nNPackedDtrsPCA;
        TBranch        *bi__gen_NPackedDtrsPCADist;
        TBranch        *bi__gen_NPackedDtrsPCAX0;
        TBranch        *bi__gen_NPackedDtrsPCAY0;
        TBranch        *bi__gen_NPackedDtrsPCAZ0;
        TBranch        *bi__gen_NPackedDtrsPCAX1;
        TBranch        *bi__gen_NPackedDtrsPCAY1;
        TBranch        *bi__gen_NPackedDtrsPCAZ1;
        TBranch        *bi__gen_NPackedDtrsPCAX2;
        TBranch        *bi__gen_NPackedDtrsPCAY2;
        TBranch        *bi__gen_NPackedDtrsPCAZ2;
        TBranch        *bi__gen_NPackedDtrsPCAPhi1;
        TBranch        *bi__gen_NPackedDtrsPCAPhi2;
        TBranch        *bi__gen_NPackedDtrsPCAIndex1;
        TBranch        *bi__gen_NPackedDtrsPCAIndex2;
        TBranch        *bi__gen_NPackedDtrsHasKVFvertex;
        TBranch        *bi__gen_NPackedDtrs_KVF_x;
        TBranch        *bi__gen_NPackedDtrs_KVF_y;
        TBranch        *bi__gen_NPackedDtrs_KVF_z;
        TBranch        *bi__gen_NPackedDtrs_KVF_cxx;
        TBranch        *bi__gen_NPackedDtrs_KVF_cyy;
        TBranch        *bi__gen_NPackedDtrs_KVF_czz;
        TBranch        *bi__gen_NPackedDtrs_KVF_cyx;
        TBranch        *bi__gen_NPackedDtrs_KVF_czy;
        TBranch        *bi__gen_NPackedDtrs_KVF_czx;
        TBranch        *bi__gen_NPackedDtrs_KVF_df;
        TBranch        *bi__gen_NPackedDtrs_KVF_chi2;
        TBranch        *bi__gen_NPackedDtrs_KVF_ntracks;
        TBranch        *bi__gen_nNdaughters;   //!
        TBranch        *bi__gen_Ndaughters_pdg;   //!
        TBranch        *bi__gen_Ndaughters_Pt;   //!
        TBranch        *bi__gen_Ndaughters_Eta;   //!
        TBranch        *bi__gen_Ndaughters_Phi;   //!
        TBranch        *bi__gen_Ndaughters_E;   //!
        TBranch        *bi__gen_Ndaughters_Charge;   //!
        //TBranch        *bi__gen_nstatus23;   //!
        //TBranch        *bi__gen_nstatus23_fromN;   //!
        //TBranch        *bi__gen_nstatus23_fromW;   //!
        //TBranch        *bi__gen_status23_pdg;   //!
        //TBranch        *bi__gen_status23_fromN_pdg;   //!
        //TBranch        *bi__gen_status23_fromW_pdg;   //!
        TBranch        *bi__gen_nq;   //!
        TBranch        *bi__gen_qPt;   //!
        TBranch        *bi__gen_qEta;   //!
        TBranch        *bi__gen_qPhi;   //!
        TBranch        *bi__gen_qE;   //!
        TBranch        *bi__passMETFilters;   //!
        TBranch        *bi__Flag_goodVertices;   //!
        TBranch        *bi__Flag_HBHENoiseFilter;   //!
        TBranch        *bi__Flag_HBHENoiseIsoFilter;   //!
        TBranch        *bi__Flag_EcalDeadCellTriggerPrimitiveFilter;   //!
        TBranch        *bi__Flag_BadPFMuonFilter;   //!
        TBranch        *bi__Flag_BadChargedCandidateFilter;   //!
        TBranch        *bi__Flag_globalSuperTightHalo2016Filter;   //!
        TBranch        *bi__HLT_Ele27_WPTight_Gsf;   //!
        TBranch        *bi__HLT_Ele27_WPTight_Gsf_prescale;   //!
        TBranch        *bi__HLT_Ele32_WPTight_Gsf;   //!
        TBranch        *bi__HLT_Ele32_WPTight_Gsf_prescale;   //!
        TBranch        *bi__HLT_IsoMu24;   //!
        TBranch        *bi__HLT_IsoMu24_prescale;   //!
        TBranch        *bi__HLT_IsoTkMu24;   //!
        TBranch        *bi__HLT_IsoTkMu24_prescale;   //!
        TBranch        *bi__HLT_IsoMu27;
        TBranch        *bi__HLT_IsoMu27_prescale;
        TBranch        *bi__HLT_IsoMu24_eta2p1;
        TBranch        *bi__HLT_IsoMu24_eta2p1_prescale;
        TBranch        *bi__HLT_MET200;
        TBranch        *bi__HLT_MET200_prescale;
        TBranch        *bi__HLT_PFMET300;
        TBranch        *bi__HLT_PFMET300_prescale;
        TBranch        *bi__HLT_PFMET170_HBHECleaned;
        TBranch        *bi__HLT_PFMET170_HBHECleaned_prescale;
        TBranch        *bi__HLT_PFMET120_PFMHT120_IDTight;
        TBranch        *bi__HLT_PFMET120_PFMHT120_IDTight_prescale;
        TBranch        *bi__HLT_PFMET140_PFMHT140_IDTight;
        TBranch        *bi__HLT_PFMET140_PFMHT140_IDTight_prescale;
        TBranch        *bi__HLT_CaloMET350_HBHECleaned;
        TBranch        *bi__HLT_CaloMET350_HBHECleaned_prescale;
        TBranch        *bi__HLT_PFMET250_HBHECleaned;
        TBranch        *bi__HLT_PFMET250_HBHECleaned_prescale;
        TBranch        *bi__HLT_PFMET200_HBHE_BeamHaloCleaned;
        TBranch        *bi__HLT_PFMET200_HBHE_BeamHaloCleaned_prescale;
        TBranch        *bi__HLT_PFMETTypeOne140_PFMHT140_IDTight;
        TBranch        *bi__HLT_PFMETTypeOne140_PFMHT140_IDTight_prescale;
        TBranch        *bi__HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned;
        TBranch        *bi__HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_prescale;
        //TBranch        *bi__HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;   //!
        //TBranch        *bi__HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_prescale;   //!
        //TBranch        *bi__HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;   //!
        //TBranch        *bi__HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;   //!
        //TBranch        *bi__HLT_Mu8_DiEle12_CaloIdL_TrackIdL;   //!
        //TBranch        *bi__HLT_Mu8_DiEle12_CaloIdL_TrackIdL_prescale;   //!
        //TBranch        *bi__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;   //!
        //TBranch        *bi__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_prescale;   //!
        //TBranch        *bi__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;   //!
        //TBranch        *bi__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_prescale;   //!
        //TBranch        *bi__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ;   //!
        //TBranch        *bi__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_prescale;   //!
        //TBranch        *bi__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL;   //!
        //TBranch        *bi__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_prescale;   //!
        //TBranch        *bi__HLT_DiMu9_Ele9_CaloIdL_TrackIdL;   //!
        //TBranch        *bi__HLT_DiMu9_Ele9_CaloIdL_TrackIdL_prescale;   //!
        //TBranch        *bi__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;   //!
        //TBranch        *bi__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_prescale;   //!
        //TBranch        *bi__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;   //!
        //TBranch        *bi__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;   //!
        //TBranch        *bi__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;   //!
        //TBranch        *bi__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale;   //!
        //TBranch        *bi__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;   //!
        //TBranch        *bi__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_prescale;   //!
        //TBranch        *bi__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;   //!
        //TBranch        *bi__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;   //!
        //TBranch        *bi__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL;   //!
        //TBranch        *bi__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale;   //!
        //TBranch        *bi__HLT_TripleMu_12_10_5;   //!
        //TBranch        *bi__HLT_TripleMu_12_10_5_prescale;   //!
        //TBranch        *bi__passMETFilters;   //!
        //TBranch        *bi__Flag_HBHENoiseFilter;   //!
        //TBranch        *bi__Flag_HBHENoiseIsoFilter;   //!
        //TBranch        *bi__Flag_EcalDeadCellTriggerPrimitiveFilter;   //!
        //TBranch        *bi__Flag_goodVertices;   //!
        //TBranch        *bi__Flag_globalTightHalo2016Filter;   //!
        //TBranch        *bi__Flag_BadPFMuonFilter;   //!
        //TBranch        *bi__Flag_BadChargedCandidateFilter;   //!
        //TBranch        *bi__HLT_Ele105_CaloIdVT_GsfTrkIdT;   //!
        //TBranch        *bi__HLT_Ele105_CaloIdVT_GsfTrkIdT_prescale;   //!
        //TBranch        *bi__HLT_Ele115_CaloIdVT_GsfTrkIdT;   //!
        //TBranch        *bi__HLT_Ele115_CaloIdVT_GsfTrkIdT_prescale;   //!
        //TBranch        *bi__HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;   //!
        //TBranch        *bi__HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale;   //!
        //TBranch        *bi__HLT_DoubleEle33_CaloIdL_GsfTrkIdVL;   //!
        //TBranch        *bi__HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_prescale;   //!
        //TBranch        *bi__HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL;   //!
        //TBranch        *bi__HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_prescale;   //!
        //TBranch        *bi__HLT_Mu50;   //!
        //TBranch        *bi__HLT_Mu50_prescale;   //!
        //TBranch        *bi__HLT_TkMu50;   //!
        //TBranch        *bi__HLT_TkMu50_prescale;   //!
        //TBranch        *bi__HLT_Mu45_eta2p1;   //!
        //TBranch        *bi__HLT_Mu45_eta2p1_prescale;   //!
        //TBranch        *bi__HLT_Mu30_TkMu11;   //!
        //TBranch        *bi__HLT_Mu30_TkMu11_prescale;   //!
        TBranch        *bi__nL;   //!
        TBranch        *bi__nMu;   //!
        TBranch        *bi__nEle;   //!
        TBranch        *bi__nLight;   //!
        TBranch        *bi__nTau;   //!
        TBranch        *bi__lPt;   //!
        TBranch        *bi__lEta;   //!
        TBranch        *bi__lEtaSC;   //!
        TBranch        *bi__lPhi;   //!
        TBranch        *bi__lE;   //!
        TBranch        *bi__lFlavor;   //!
        TBranch        *bi__lCharge;   //!
        TBranch        *bi__dxy;   //!
        TBranch        *bi__dz;   //!
        TBranch        *bi__3dIP;   //!
        TBranch        *bi__3dIPSig;   //!
        TBranch        *bi__lElectronSummer16MvaGP;
        TBranch        *bi__lElectronSummer16MvaHZZ;
        TBranch        *bi__lElectronMvaFall17v1NoIso;
        TBranch        *bi__lElectronMvaFall17Iso;
        TBranch        *bi__lElectronMvaFall17NoIso;
        TBranch        *bi__lElectronPassEmu;   //!
        TBranch        *bi__lElectronPassConvVeto;   //!
        TBranch        *bi__lElectronChargeConst;   //!
        TBranch        *bi__lElectronMissingHits;   //!
        TBranch        *bi__lElectronIsEB;                                                                         //electron specific variables for displaced electron ID
        TBranch        *bi__lElectronIsEE;
        TBranch        *bi__lElectronSuperClusterOverP;
        TBranch        *bi__lElectronEcalEnergy;
        TBranch        *bi__lElectronSigmaIetaIeta;
        TBranch        *bi__lElectronDEtaInSeed;
        TBranch        *bi__lElectronDeltaPhiSuperClusterTrack;
        TBranch        *bi__lElectronDeltaEtaSuperClusterTrack;
        TBranch        *bi__lElectronHOverE;
        TBranch        *bi__lElectronEInvMinusPInv;
        TBranch        *bi__lElectronNumberInnerHitsMissing;
        TBranch        *bi__leptonMvaTTH;
        TBranch        *bi__leptonMvatZq;
        TBranch        *bi__leptonMvaTOP;
        TBranch        *bi__lPOGVeto;   //!
        TBranch        *bi__lPOGLoose;   //!
        TBranch        *bi__lPOGMedium;   //!
        TBranch        *bi__lPOGTight;   //!
        TBranch        *bi__tauMuonVetoLoose;   //[_nL]
        TBranch        *bi__tauEleVetoLoose;   //[_nL]
        TBranch        *bi__decayModeFinding;   //[_nL]
        TBranch        *bi__tauAgainstElectronMVA6Raw;
        TBranch        *bi__tauCombinedIsoDBRaw3Hits;
        TBranch        *bi__tauIsoMVAPWdR03oldDMwLT;
        TBranch        *bi__tauIsoMVADBdR03oldDMwLT;
        TBranch        *bi__tauIsoMVADBdR03newDMwLT;
        TBranch        *bi__tauIsoMVAPWnewDMwLT;
        TBranch        *bi__tauIsoMVAPWoldDMwLT;
        TBranch        *bi__relIso;   //!
        TBranch        *bi__relIso0p4;   //!
        TBranch        *bi__relIso0p4MuDeltaBeta;   //!
        TBranch        *bi__miniIso;   //!
        TBranch        *bi__miniIsoCharged;   //!
        TBranch        *bi__ptRel;   //!
        TBranch        *bi__ptRatio;   //!
        TBranch        *bi__closestJetCsvV2;   //!
        TBranch        *bi__closestJetDeepCsv_b;   //!
        TBranch        *bi__closestJetDeepCsv_bb;   //!
        TBranch        *bi__closestJetDeepCsv;   //!
        TBranch        *bi__closestJetDeepFlavor_b;   //!
        TBranch        *bi__closestJetDeepFlavor_bb;   //!
        TBranch        *bi__closestJetDeepFlavor_lepb;   //!
        TBranch        *bi__closestJetDeepFlavor;   //!
        TBranch        *bi__selectedTrackMult;   //!
        //TBranch        *bi__lKVF_valid;
        //TBranch	      *bi__lKVF_x;
        //TBranch	      *bi__lKVF_y;
        //TBranch	      *bi__lKVF_z;
        //TBranch	      *bi__lKVF_cxx;
        //TBranch	      *bi__lKVF_cyy;
        //TBranch	      *bi__lKVF_czz;
        //TBranch	      *bi__lKVF_cyx;
        //TBranch	      *bi__lKVF_czy;
        //TBranch	      *bi__lKVF_czx;
        //TBranch	      *bi__lKVF_df;
        //TBranch	      *bi__lKVF_chi2;
        //TBranch        *bi__lKVF_ntracks;
        //TBranch        *bi__lKVF_dRcut;
        //TBranch        *bi__lKVF_trackPt;
        //TBranch        *bi__lKVF_trackEta;
        //TBranch        *bi__lKVF_trackPhi;
        //TBranch        *bi__lKVF_trackE;
        //TBranch        *bi__lKVF_trackdR;
        //TBranch        *bi__lKVF_trackdxy;
        //TBranch        *bi__lKVF_trackdz;
        TBranch        *bi__IVF_x;
        TBranch        *bi__IVF_y;
        TBranch        *bi__IVF_z;
        TBranch        *bi__IVF_cx;
        TBranch        *bi__IVF_cy;
        TBranch        *bi__IVF_cz;
        TBranch        *bi__IVF_df;
        TBranch        *bi__IVF_chi2;
        TBranch        *bi__IVF_pt;
        TBranch        *bi__IVF_eta;
        TBranch        *bi__IVF_phi;
        TBranch        *bi__IVF_E;
        TBranch        *bi__IVF_mass;
        TBranch        *bi__IVF_ntracks;
        TBranch        *bi__IVF_trackpt;
        TBranch        *bi__IVF_tracketa;
        TBranch        *bi__IVF_trackphi;
        TBranch        *bi__IVF_trackE;
        TBranch        *bi__IVF_trackcharge;
        TBranch        *bi__lIVF_match;
        TBranch        *bi__lGlobalMuon;                                                                       //muon speficic variables, also for displaced muon ID
        TBranch        *bi__lTrackerMuon;
        TBranch        *bi__lInnerTrackValidFraction;
        TBranch        *bi__lGlobalTrackNormalizedChi2;
        TBranch        *bi__lCQChi2Position;
        TBranch        *bi__lCQTrackKink;
        TBranch        *bi__lNumberOfMatchedStation;
        TBranch        *bi__lNumberOfValidPixelHits;
        TBranch        *bi__lNumberOfValidTrackerHits;
        TBranch        *bi__muNumberInnerHits;
        TBranch        *bi__lTrackerLayersWithMeasurement;
        TBranch        *bi__lMuonSegComp;   //!
        TBranch        *bi__lMuonTrackPt;   //!
        TBranch        *bi__lMuonTrackPtErr;   //!
        TBranch        *bi__lMuonTimenDof;
        TBranch        *bi__lMuonTime;
        TBranch        *bi__lMuonTimeErr;
        TBranch        *bi__lMuonRPCTimenDof;
        TBranch        *bi__lMuonRPCTime;
        TBranch        *bi__lMuonRPCTimeErr;
        TBranch        *bi__lIsPrompt;   //!
        TBranch        *bi__lMatchPdgId;   //!
        TBranch        *bi__lMatchCharge;   //[_nL]
        TBranch        *bi__tauGenStatus;   //[_nL]
        TBranch        *bi__lMomPdgId;
        TBranch        *bi__lProvenance;
        TBranch        *bi__lProvenanceCompressed;
        TBranch        *bi__lProvenanceConversion;
        TBranch        *bi__lPtCorr;
        TBranch        *bi__lPtScaleUp;
        TBranch        *bi__lPtScaleDown;
        TBranch        *bi__lPtResUp;
        TBranch        *bi__lPtResDown;
        TBranch        *bi__nPh;   //!
        TBranch        *bi__phPt;   //!
        TBranch        *bi__phEta;   //!
        TBranch        *bi__phEtaSC;   //!
        TBranch        *bi__phPhi;   //!
        TBranch        *bi__phE;   //!
        TBranch        *bi__phCutBasedLoose;   //!
        TBranch        *bi__phCutBasedMedium;   //!
        TBranch        *bi__phCutBasedTight;   //!
        TBranch        *bi__phMva;   //!
        TBranch        *bi__phRandomConeChargedIsolation;   //!
        TBranch        *bi__phChargedIsolation;   //!
        TBranch        *bi__phNeutralHadronIsolation;   //!
        TBranch        *bi__phPhotonIsolation;   //!
        TBranch        *bi__phSigmaIetaIeta;   //!
        TBranch        *bi__phHadronicOverEm;   //!
        TBranch        *bi__phHadTowOverEm;
        TBranch        *bi__phPassElectronVeto;   //!
        TBranch        *bi__phHasPixelSeed;   //!
        TBranch        *bi__phIsPrompt;   //!
        TBranch        *bi__phMatchPdgId;   //!
        TBranch        *bi__phPtCorr;
        TBranch        *bi__phPtScaleUp;
        TBranch        *bi__phPtScaleDown;
        TBranch        *bi__phPtResUp;
        TBranch        *bi__phPtResDown;
        TBranch        *bi__nJets;   //!
        TBranch        *bi__jetPt;   //!
        TBranch        *bi__jetPt_JECUp;   //!
        TBranch        *bi__jetPt_JECDown;   //!
        TBranch        *bi__jetPt_Uncorrected;
        TBranch        *bi__jetPt_L1;
        TBranch        *bi__jetPt_L2;
        TBranch        *bi__jetPt_L3;
        TBranch        *bi__jetSmearedPt;
        TBranch        *bi__jetSmearedPt_JECDown;
        TBranch        *bi__jetSmearedPt_JECUp;
        TBranch        *bi__jetSmearedPt_JERDown;
        TBranch        *bi__jetSmearedPt_JERUp;
        TBranch        *bi__jetEta;   //!
        TBranch        *bi__jetPhi;   //!
        TBranch        *bi__jetE;   //!
        TBranch        *bi__jetCsvV2;   //!
        TBranch        *bi__jetDeepCsv_udsg;   //!
        TBranch        *bi__jetDeepCsv_b;   //!
        TBranch        *bi__jetDeepCsv_c;   //!
        TBranch        *bi__jetDeepCsv_bb;   //!
        TBranch        *bi__jetDeepCsv;   //!
        TBranch        *bi__jetDeepFlavor_b;   //!
        TBranch        *bi__jetDeepFlavor_bb;   //!
        TBranch        *bi__jetDeepFlavor_lepb;   //!
        TBranch        *bi__jetDeepFlavor;   //!
        TBranch        *bi__jetDeepFlavor_c;   //!
        TBranch        *bi__jetDeepFlavor_uds;   //!
        TBranch        *bi__jetDeepFlavor_g;   //!
        TBranch        *bi__jetHadronFlavor;   //!
        //TBranch        *bi__jetIsLoose;   //!
        TBranch        *bi__jetIsTight;   //!
        TBranch        *bi__jetIsTightLepVeto;   //!
        TBranch        *bi__jetNeutralHadronFraction;   //!
        TBranch        *bi__jetChargedHadronFraction;   //!
        TBranch        *bi__jetNeutralEmFraction;   //!
        TBranch        *bi__jetChargedEmFraction;   //!
        TBranch        *bi__jetHFHadronFraction;   //!
        TBranch        *bi__jetHFEmFraction;   //!
        TBranch        *bi__nJetConstituents;
        TBranch        *bi__JetConstituentPt;
        TBranch        *bi__JetConstituentEta;
        TBranch        *bi__JetConstituentPhi;
        TBranch        *bi__JetConstituentMass;
        TBranch        *bi__JetConstituentPdgId;
        TBranch        *bi__JetConstituentPdgIdReduced;
        TBranch        *bi__JetConstituentCharge;
        TBranch        *bi__JetConstituentdxy;
        TBranch        *bi__JetConstituentdz;
        TBranch        *bi__JetConstituentdxyErr;
        TBranch        *bi__JetConstituentdzErr;
        TBranch        *bi__JetConstituentNumberOfHits;
        TBranch        *bi__JetConstituentNumberOfPixelHits;
        TBranch        *bi__JetConstituentHasTrack;
        TBranch        *bi__met;   //!
        TBranch        *bi__metRaw;
        TBranch        *bi__metJECDown;   //!
        TBranch        *bi__metJECUp;   //!
        TBranch        *bi__metUnclDown;   //!
        TBranch        *bi__metUnclUp;   //!
        TBranch        *bi__metPhi;   //!
        TBranch        *bi__metRawPhi;   //!
        TBranch        *bi__metPhiJECDown;   //!
        TBranch        *bi__metPhiJECUp;   //!
        TBranch        *bi__metPhiUnclDown;   //!
        TBranch        *bi__metPhiUnclUp;   //!
        TBranch        *bi__metSignificance;   //!

        LeptonMvaHelper* mvahelper;
        bool hasLeptonMvaTOP;

        Skimmer(TString inputfilename, TString outputfilename);
        ~Skimmer();
        void Init_input_branches(TTree* tree);
        void Add_branches(TTree* tree);
        void Skim(TString skimcondition);

        //Skim conditions related stuff
        void get_TightelectronID(bool* ID);
        void get_DisplelectronID(bool* ID);
        void get_TightmuonID(bool* ID);
        void get_DisplmuonID(bool* ID);
        void get_clean_ele(bool* cleaned, bool* muonID);
        bool ElectronTriggerSkim();
        bool ElectronTriggerSkim2016();
        bool ElectronTriggerSkim2017();
        bool ElectronTriggerSkim2018();
        bool MuonTriggerSkim();
        bool MuonTriggerSkim2016();
        bool MuonTriggerSkim2017();
        bool MuonTriggerSkim2018();
        bool singleleptonSkim();
        bool dileptonSkim();
        bool Check_SkimCondition(TString Condition);

        bool TightmuonID[10], DisplmuonID[10], TightelectronID[10], DisplelectronID[10];
        bool ele_cleaned_tight[10], ele_cleaned_displ[10], ele_cleaned_both[10];
};
#endif
