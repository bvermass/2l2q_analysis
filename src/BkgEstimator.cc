//////////////////////////////////////////////////////////////////////////////
//Produces BkgEstimator tree for any kind of background estimation technique//
//////////////////////////////////////////////////////////////////////////////

//Include header for the class
#include "../interface/BkgEstimator.h"

BkgEstimator::BkgEstimator()
{
}

BkgEstimator::BkgEstimator(TString filename, TString fileoption, double hCounterValue)
{
    BkgEstimator_filename = filename;
    if(fileoption == "read"){//open existing file to read its contents
        open_file_and_tree(filename);
        set_branch_adresses();
    }else {//open new file or recreate file to write events
        BkgEstimator_file = new TFile(BkgEstimator_filename, fileoption);
        hCounter          = new TH1D("hCounter", "Events counter", 1, 0, 1);
        hCounter->SetBinContent(1, hCounterValue);
        BkgEstimator_tree = new TTree("BkgEstimator_tree", "Class containing main variables for Background estimation");
        BkgEstimator_tree->Branch("_runNb",                            &_runNb,                            "_runNb/l");
        BkgEstimator_tree->Branch("_lumiBlock",                        &_lumiBlock,                        "_lumiBlock/l");
        BkgEstimator_tree->Branch("_eventNb",                          &_eventNb,                          "_eventNb/l");
        BkgEstimator_tree->Branch("_weight",                           &_weight,                           "_weight/D");
        BkgEstimator_tree->Branch("_RawWeight",                        &_RawWeight,                        "_RawWeight/D");
        BkgEstimator_tree->Branch("_l1_IDSF",                          &_l1_IDSF,                          "_l1_IDSF/D");
        BkgEstimator_tree->Branch("_l1_IDSF_unc_sym",                  &_l1_IDSF_unc_sym,                  "_l1_IDSF_unc_sym/D");
        BkgEstimator_tree->Branch("_l2_IDSF",                          &_l2_IDSF,                          "_l2_IDSF/D");
        BkgEstimator_tree->Branch("_l2_IDSF_unc_sym",                  &_l2_IDSF_unc_sym,                  "_l2_IDSF_unc_sym/D");
        BkgEstimator_tree->Branch("_TrackSF",                          &_TrackSF,                          "_TrackSF/D");
        BkgEstimator_tree->Branch("_TrackSF_unc_sym",                  &_TrackSF_unc_sym,                  "_TrackSF_unc_sym/D");
        BkgEstimator_tree->Branch("_l1_ISOSF",                         &_l1_ISOSF,                         "_l1_ISOSF/D");
        BkgEstimator_tree->Branch("_l1_ISOSF_unc_sym",                 &_l1_ISOSF_unc_sym,                 "_l1_ISOSF_unc_sym/D");
        BkgEstimator_tree->Branch("_TriggerSF",                        &_TriggerSF,                        "_TriggerSF/D");
        BkgEstimator_tree->Branch("_TriggerSF_unc_sym",                &_TriggerSF_unc_sym,                "_TriggerSF_unc_sym/D");
        BkgEstimator_tree->Branch("_PileUpSF",                         &_PileUpSF,                         "_PileUpSF/D");
        BkgEstimator_tree->Branch("_PileUpSF_unc_up",                  &_PileUpSF_unc_up,                  "_PileUpSF_unc_up/D");
        BkgEstimator_tree->Branch("_PileUpSF_unc_down",                &_PileUpSF_unc_down,                "_PileUpSF_unc_down/D");
        BkgEstimator_tree->Branch("_is2016",                           &_is2016,                           "_is2016/O");
        BkgEstimator_tree->Branch("_is2017",                           &_is2017,                           "_is2017/O");
        BkgEstimator_tree->Branch("_is2018",                           &_is2018,                           "_is2018/O");
        BkgEstimator_tree->Branch("_gen_Nmass",                        &_gen_Nmass,                        "_gen_Nmass/I");
        BkgEstimator_tree->Branch("_gen_NV2",                          &_gen_NV2,                          "_gen_NV2/D");
        BkgEstimator_tree->Branch("_gen_Nctau",                        &_gen_Nctau,                        "_gen_Nctau/D");
        BkgEstimator_tree->Branch("_JetIsFromHNL",                     &_JetIsFromHNL,                     "_JetIsFromHNL/O");
        BkgEstimator_tree->Branch("_nTightJet",                        &_nTightJet,                        "_nTightJet/i");
        BkgEstimator_tree->Branch("_nMediumBJet",                        &_nMediumBJet,                        "_nMediumBJet/i");
        BkgEstimator_tree->Branch("_nLooseBJet",                        &_nLooseBJet,                        "_nLooseBJet/i");
        BkgEstimator_tree->Branch("_JetPt",                            &_JetPt,                            "_JetPt/D");
        BkgEstimator_tree->Branch("_JetEta",                           &_JetEta,                           "_JetEta/D");
        BkgEstimator_tree->Branch("_JetPhi",                           &_JetPhi,                           "_JetPhi/D");
        BkgEstimator_tree->Branch("_nTightLep",                        &_nTightLep,                        "_nTightLep/i");
        BkgEstimator_tree->Branch("_lPt",                              &_lPt,                              "_lPt/D");
        BkgEstimator_tree->Branch("_lEta",                             &_lEta,                             "_lEta/D");
        BkgEstimator_tree->Branch("_lPhi",                             &_lPhi,                             "_lPhi/D");
        BkgEstimator_tree->Branch("_ldxy",                             &_ldxy,                             "_ldxy/D");
        BkgEstimator_tree->Branch("_ldz",                              &_ldz,                              "_ldz/D");
        BkgEstimator_tree->Branch("_l3dIPSig",                         &_l3dIPSig,                         "_l3dIPSig/D");
        BkgEstimator_tree->Branch("_lrelIso",                          &_lrelIso,                          "_lrelIso/D");
        BkgEstimator_tree->Branch("_lptRel",                           &_lptRel,                           "_lptRel/D");
        BkgEstimator_tree->Branch("_lptRatio",                         &_lptRatio,                         "_lptRatio/D");
        BkgEstimator_tree->Branch("_lNumberOfHits",                    &_lNumberOfHits,                    "_lNumberOfHits/i");
        BkgEstimator_tree->Branch("_lNumberOfPixelHits",               &_lNumberOfPixelHits,               "_lNumberOfPixelHits/i");
        BkgEstimator_tree->Branch("_lFlavor",                          &_lFlavor,                          "_lFlavor/i");
        BkgEstimator_tree->Branch("_lCharge",                          &_lCharge,                          "_lCharge/I");
        BkgEstimator_tree->Branch("_lProvenance",                      &_lProvenance,                      "_lProvenance/i");
        BkgEstimator_tree->Branch("_lProvenanceCompressed",            &_lProvenanceCompressed,            "_lProvenanceCompressed/i");
        BkgEstimator_tree->Branch("_lElectronPassConvVeto",            &_lElectronPassConvVeto,            "_lElectronPassConvVeto/O");
        BkgEstimator_tree->Branch("_lElectronMissingHits",             &_lElectronMissingHits,             "_lElectronMissingHits/i");
        BkgEstimator_tree->Branch("_lElectronSuperClusterOverP",       &_lElectronSuperClusterOverP,       "_lElectronSuperClusterOverP/D");
        BkgEstimator_tree->Branch("_lElectronEcalEnergy",              &_lElectronEcalEnergy,              "_lElectronEcalEnergy/D");
        BkgEstimator_tree->Branch("_lElectronSigmaIetaIeta",           &_lElectronSigmaIetaIeta,           "_lElectronSigmaIetaIeta/D");
        BkgEstimator_tree->Branch("_lElectronDEtaInSeed",              &_lElectronDEtaInSeed,              "_lElectronDEtaInSeed/D");
        BkgEstimator_tree->Branch("_lElectronDeltaPhiSuperClusterTrack", &_lElectronDeltaPhiSuperClusterTrack, "_lElectronDeltaPhiSuperClusterTrack/D");
        BkgEstimator_tree->Branch("_lElectronDeltaEtaSuperClusterTrack", &_lElectronDeltaEtaSuperClusterTrack, "_lElectronDeltaEtaSuperClusterTrack/D");
        BkgEstimator_tree->Branch("_lElectronHOverE",                  &_lElectronHOverE,                  "_lElectronHOverE/D");
        BkgEstimator_tree->Branch("_lElectronEInvMinusPInv",           &_lElectronEInvMinusPInv,           "_lElectronEInvMinusPInv/D");
        BkgEstimator_tree->Branch("_lElectronNumberInnerHitsMissing",  &_lElectronNumberInnerHitsMissing,  "_lElectronNumberInnerHitsMissing/D");
        BkgEstimator_tree->Branch("_lGlobalMuon",                      &_lGlobalMuon,                      "_lGlobalMuon/O");
        BkgEstimator_tree->Branch("_lTrackerMuon",                     &_lTrackerMuon,                     "_lTrackerMuon/O");
        BkgEstimator_tree->Branch("_lInnerTrackValidFraction",         &_lInnerTrackValidFraction,         "_lInnerTrackValidFraction/D");
        BkgEstimator_tree->Branch("_lGlobalTrackNormalizedChi2",       &_lGlobalTrackNormalizedChi2,       "_lGlobalTrackNormalizedChi2/D");
        BkgEstimator_tree->Branch("_lCQChi2Position",                  &_lCQChi2Position,                  "_lCQChi2Position/D");
        BkgEstimator_tree->Branch("_lCQTrackKink",                     &_lCQTrackKink,                     "_lCQTrackKink/D");
        BkgEstimator_tree->Branch("_lMuonSegComp",                     &_lMuonSegComp,                     "_lMuonSegComp/D");
        BkgEstimator_tree->Branch("_lMuonTime",                        &_lMuonTime,                        "_lMuonTime/D");
        BkgEstimator_tree->Branch("_lMuonRPCTime",                     &_lMuonRPCTime,                     "_lMuonRPCTime/D");
        BkgEstimator_tree->Branch("_lMuonTrackPtErr",                  &_lMuonTrackPtErr,                  "_lMuonTrackPtErr/D");

        BkgEstimator_tree->Branch("_l1Pt",                             &_l1Pt,                             "_l1Pt/D");
        BkgEstimator_tree->Branch("_l1Eta",                            &_l1Eta,                            "_l1Eta/D");
        BkgEstimator_tree->Branch("_l1Phi",                            &_l1Phi,                            "_l1Phi/D");
        BkgEstimator_tree->Branch("_l1dxy",                            &_l1dxy,                            "_l1dxy/D");
        BkgEstimator_tree->Branch("_l1dz",                             &_l1dz,                             "_l1dz/D");
        BkgEstimator_tree->Branch("_l13dIPSig",                        &_l13dIPSig,                        "_l13dIPSig/D");
        BkgEstimator_tree->Branch("_l1relIso",                         &_l1relIso,                         "_l1relIso/D");
        BkgEstimator_tree->Branch("_l1ptRel",                          &_l1ptRel,                          "_l1ptRel/D");
        BkgEstimator_tree->Branch("_l1ptRatio",                        &_l1ptRatio,                        "_l1ptRatio/D");
        BkgEstimator_tree->Branch("_l1Flavor",                         &_l1Flavor,                         "_l1Flavor/i");
        BkgEstimator_tree->Branch("_l1Charge",                         &_l1Charge,                         "_l1Charge/I");
        BkgEstimator_tree->Branch("_l1Provenance",                     &_l1Provenance,                     "_l1Provenance/i");
        BkgEstimator_tree->Branch("_l1ProvenanceCompressed",           &_l1ProvenanceCompressed,           "_l1ProvenanceCompressed/i");
        BkgEstimator_tree->Branch("_l1ElectronPassConvVeto",           &_l1ElectronPassConvVeto,           "_l1ElectronPassConvVeto/O");
        BkgEstimator_tree->Branch("_l1ElectronMissingHits",            &_l1ElectronMissingHits,            "_l1ElectronMissingHits/i");
        BkgEstimator_tree->Branch("_l1ElectronSuperClusterOverP",      &_l1ElectronSuperClusterOverP,      "_l1ElectronSuperClusterOverP/D");
        BkgEstimator_tree->Branch("_l1ElectronEcalEnergy",             &_l1ElectronEcalEnergy,             "_l1ElectronEcalEnergy/D");
        BkgEstimator_tree->Branch("_l1ElectronSigmaIetaIeta",          &_l1ElectronSigmaIetaIeta,          "_l1ElectronSigmaIetaIeta/D");
        BkgEstimator_tree->Branch("_l1ElectronDEtaInSeed",             &_l1ElectronDEtaInSeed,             "_l1ElectronDEtaInSeed/D");
        BkgEstimator_tree->Branch("_l1ElectronDeltaPhiSuperClusterTrack", &_l1ElectronDeltaPhiSuperClusterTrack, "_l1ElectronDeltaPhiSuperClusterTrack/D");
        BkgEstimator_tree->Branch("_l1ElectronDeltaEtaSuperClusterTrack", &_l1ElectronDeltaEtaSuperClusterTrack, "_l1ElectronDeltaEtaSuperClusterTrack/D");
        BkgEstimator_tree->Branch("_l1ElectronHOverE",                 &_l1ElectronHOverE,                 "_l1ElectronHOverE/D");
        BkgEstimator_tree->Branch("_l1ElectronEInvMinusPInv",          &_l1ElectronEInvMinusPInv,          "_l1ElectronEInvMinusPInv/D");
        BkgEstimator_tree->Branch("_l1ElectronNumberInnerHitsMissing", &_l1ElectronNumberInnerHitsMissing, "_l1ElectronNumberInnerHitsMissing/D");
        BkgEstimator_tree->Branch("_l1GlobalMuon",                     &_l1GlobalMuon,                     "_l1GlobalMuon/O");
        BkgEstimator_tree->Branch("_l1TrackerMuon",                    &_l1TrackerMuon,                    "_l1TrackerMuon/O");
        BkgEstimator_tree->Branch("_l1InnerTrackValidFraction",        &_l1InnerTrackValidFraction,        "_l1InnerTrackValidFraction/D");
        BkgEstimator_tree->Branch("_l1GlobalTrackNormalizedChi2",      &_l1GlobalTrackNormalizedChi2,      "_l1GlobalTrackNormalizedChi2/D");
        BkgEstimator_tree->Branch("_l1CQChi2Position",                 &_l1CQChi2Position,                 "_l1CQChi2Position/D");
        BkgEstimator_tree->Branch("_l1CQTrackKink",                    &_l1CQTrackKink,                    "_l1CQTrackKink/D");
        BkgEstimator_tree->Branch("_l1MuonSegComp",                    &_l1MuonSegComp,                    "_l1MuonSegComp/D");
        BkgEstimator_tree->Branch("_l1MuonTime",                       &_l1MuonTime,                       "_l1MuonTime/D");
        BkgEstimator_tree->Branch("_l1MuonRPCTime",                    &_l1MuonRPCTime,                    "_l1MuonRPCTime/D");
        BkgEstimator_tree->Branch("_l1MuonTrackPtErr",                 &_l1MuonTrackPtErr,                 "_l1MuonTrackPtErr/D");
        BkgEstimator_tree->Branch("_mll",                              &_mll,                              "_mll/D");
        BkgEstimator_tree->Branch("_mlljet",                           &_mlljet,                           "_mlljet/D");
        BkgEstimator_tree->Branch("_dRll",                             &_dRll,                             "_dRll/D");
        BkgEstimator_tree->Branch("_dphill",                           &_dphill,                           "_dphill/D");
        BkgEstimator_tree->Branch("_dRljet",                           &_dRljet,                           "_dRljet/D");

        BkgEstimator_tree->Branch("_SV_PVSVdist",                      &_SV_PVSVdist,                      "_SV_PVSVdist/D");
        BkgEstimator_tree->Branch("_SV_PVSVdist_2D",                   &_SV_PVSVdist_2D,                   "_SV_PVSVdist_2D/D");
        BkgEstimator_tree->Branch("_SV_genreco",                       &_SV_genreco,                       "_SV_genreco/D");
        BkgEstimator_tree->Branch("_SV_mass",                          &_SV_mass,                          "_SV_mass/D");
        BkgEstimator_tree->Branch("_SV_l1mass",                        &_SV_l1mass,                        "_SV_l1mass/D");
        BkgEstimator_tree->Branch("_SV_pt",                            &_SV_pt,                            "_SV_pt/D");
        BkgEstimator_tree->Branch("_SV_eta",                           &_SV_eta,                           "_SV_eta/D");
        BkgEstimator_tree->Branch("_SV_phi",                           &_SV_phi,                           "_SV_phi/D");
        BkgEstimator_tree->Branch("_SV_normchi2",                      &_SV_normchi2,                      "_SV_normchi2/D");
        BkgEstimator_tree->Branch("_SV_ntracks",                       &_SV_ntracks,                       "_SV_ntracks/i");
        BkgEstimator_tree->Branch("_SV_trackpt",                       &_SV_trackpt,                       "_SV_trackpt[_SV_ntracks]/D");
        BkgEstimator_tree->Branch("_SV_tracketa",                      &_SV_tracketa,                      "_SV_tracketa[_SV_ntracks]/D");
        BkgEstimator_tree->Branch("_SV_trackphi",                      &_SV_trackphi,                      "_SV_trackphi[_SV_ntracks]/D");
        BkgEstimator_tree->Branch("_SV_trackE",                        &_SV_trackE,                        "_SV_trackE[_SV_ntracks]/D");
        BkgEstimator_tree->Branch("_SV_trackcharge",                   &_SV_trackcharge,                   "_SV_trackcharge[_SV_ntracks]/I");

        BkgEstimator_tree->Branch("_nMV2",                             &_nMV2,                             "_nMV2/i");
        BkgEstimator_tree->Branch("_evaluating_mass",                  &_evaluating_mass,                  "_evaluating_mass[_nMV2]/I");
        BkgEstimator_tree->Branch("_evaluating_V2",                    &_evaluating_V2,                    "_evaluating_V2[_nMV2]/D");
        BkgEstimator_tree->Branch("_JetTagVal",                        &_JetTagVal,                        "_JetTagVal[_nMV2]/D");
        BkgEstimator_tree->Branch("_reweighting_weight",               &_reweighting_weight,               "_reweighting_weight[_nMV2]/D");
    }
}


void BkgEstimator::open_file_and_tree(TString filename)
{
    BkgEstimator_file = new TFile(filename, "open");
    BkgEstimator_tree = (TTree*) BkgEstimator_file->Get("BkgEstimator_tree");
    hCounter          = (TH1D*) BkgEstimator_file->Get("hCounter");
}


void BkgEstimator::set_branch_adresses()
{
    BkgEstimator_tree->SetBranchAddress("_runNb", &_runNb, &b__runNb);
    BkgEstimator_tree->SetBranchAddress("_lumiBlock", &_lumiBlock, &b__lumiBlock);
    BkgEstimator_tree->SetBranchAddress("_eventNb", &_eventNb, &b__eventNb);
    BkgEstimator_tree->SetBranchAddress("_weight", &_weight, &b__weight);
    BkgEstimator_tree->SetBranchAddress("_RawWeight", &_RawWeight, &b__RawWeight);
    BkgEstimator_tree->SetBranchAddress("_l1_IDSF", &_l1_IDSF, &b__l1_IDSF);
    BkgEstimator_tree->SetBranchAddress("_l1_IDSF_unc_sym", &_l1_IDSF_unc_sym, &b__l1_IDSF_unc_sym);
    BkgEstimator_tree->SetBranchAddress("_l2_IDSF", &_l2_IDSF, &b__l2_IDSF);
    BkgEstimator_tree->SetBranchAddress("_l2_IDSF_unc_sym", &_l2_IDSF_unc_sym, &b__l2_IDSF_unc_sym);
    BkgEstimator_tree->SetBranchAddress("_TrackSF", &_TrackSF, &b__TrackSF);
    BkgEstimator_tree->SetBranchAddress("_TrackSF_unc_sym", &_TrackSF_unc_sym, &b__TrackSF_unc_sym);
    BkgEstimator_tree->SetBranchAddress("_l1_ISOSF", &_l1_ISOSF, &b__l1_ISOSF);
    BkgEstimator_tree->SetBranchAddress("_l1_ISOSF_unc_sym", &_l1_ISOSF_unc_sym, &b__l1_ISOSF_unc_sym);
    BkgEstimator_tree->SetBranchAddress("_TriggerSF", &_TriggerSF, &b__TriggerSF);
    BkgEstimator_tree->SetBranchAddress("_TriggerSF_unc_sym", &_TriggerSF_unc_sym, &b__TriggerSF_unc_sym);
    BkgEstimator_tree->SetBranchAddress("_PileUpSF", &_PileUpSF, &b__PileUpSF);
    BkgEstimator_tree->SetBranchAddress("_PileUpSF_unc_up", &_PileUpSF_unc_up, &b__PileUpSF_unc_up);
    BkgEstimator_tree->SetBranchAddress("_PileUpSF_unc_down", &_PileUpSF_unc_down, &b__PileUpSF_unc_down);
    BkgEstimator_tree->SetBranchAddress("_is2016", &_is2016, &b__is2016);
    BkgEstimator_tree->SetBranchAddress("_is2017", &_is2017, &b__is2017);
    BkgEstimator_tree->SetBranchAddress("_is2018", &_is2018, &b__is2018);
    BkgEstimator_tree->SetBranchAddress("_gen_Nmass", &_gen_Nmass, &b__gen_Nmass);
    BkgEstimator_tree->SetBranchAddress("_gen_NV2", &_gen_NV2, &b__gen_NV2);
    BkgEstimator_tree->SetBranchAddress("_gen_Nctau", &_gen_Nctau, &b__gen_Nctau);
    BkgEstimator_tree->SetBranchAddress("_JetIsFromHNL", &_JetIsFromHNL, &b__JetIsFromHNL);
    BkgEstimator_tree->SetBranchAddress("_nTightJet", &_nTightJet, &b__nTightJet);
    BkgEstimator_tree->SetBranchAddress("_nMediumBJet", &_nMediumBJet, &b__nMediumBJet);
    BkgEstimator_tree->SetBranchAddress("_nLooseBJet", &_nLooseBJet, &b__nLooseBJet);
    BkgEstimator_tree->SetBranchAddress("_JetPt", &_JetPt, &b__JetPt);
    BkgEstimator_tree->SetBranchAddress("_JetEta", &_JetEta, &b__JetEta);
    BkgEstimator_tree->SetBranchAddress("_JetPhi", &_JetPhi, &b__JetPhi);
    BkgEstimator_tree->SetBranchAddress("_nTightLep", &_nTightLep, &b__nTightLep);
    BkgEstimator_tree->SetBranchAddress("_lPt", &_lPt, &b__lPt);
    BkgEstimator_tree->SetBranchAddress("_lEta", &_lEta, &b__lEta);
    BkgEstimator_tree->SetBranchAddress("_lPhi", &_lPhi, &b__lPhi);
    BkgEstimator_tree->SetBranchAddress("_ldxy", &_ldxy, &b__ldxy);
    BkgEstimator_tree->SetBranchAddress("_ldz", &_ldz, &b__ldz);
    BkgEstimator_tree->SetBranchAddress("_l3dIPSig", &_l3dIPSig, &b__l3dIPSig);
    BkgEstimator_tree->SetBranchAddress("_lrelIso", &_lrelIso, &b__lrelIso);
    BkgEstimator_tree->SetBranchAddress("_lptRel", &_lptRel, &b__lptRel);
    BkgEstimator_tree->SetBranchAddress("_lptRatio", &_lptRatio, &b__lptRatio);
    BkgEstimator_tree->SetBranchAddress("_lNumberOfHits", &_lNumberOfHits, &b__lNumberOfHits);
    BkgEstimator_tree->SetBranchAddress("_lNumberOfPixelHits", &_lNumberOfPixelHits, &b__lNumberOfPixelHits);
    BkgEstimator_tree->SetBranchAddress("_lFlavor", &_lFlavor, &b__lFlavor);
    BkgEstimator_tree->SetBranchAddress("_lCharge", &_lCharge, &b__lCharge);
    BkgEstimator_tree->SetBranchAddress("_lProvenance", &_lProvenance, &b__lProvenance);
    BkgEstimator_tree->SetBranchAddress("_lProvenanceCompressed", &_lProvenanceCompressed, &b__lProvenanceCompressed);
    BkgEstimator_tree->SetBranchAddress("_lElectronPassConvVeto", &_lElectronPassConvVeto, &b__lElectronPassConvVeto);
    BkgEstimator_tree->SetBranchAddress("_lElectronMissingHits", &_lElectronMissingHits, &b__lElectronMissingHits);
    BkgEstimator_tree->SetBranchAddress("_lElectronSuperClusterOverP", &_lElectronSuperClusterOverP, &b__lElectronSuperClusterOverP);
    BkgEstimator_tree->SetBranchAddress("_lElectronEcalEnergy", &_lElectronEcalEnergy, &b__lElectronEcalEnergy);
    BkgEstimator_tree->SetBranchAddress("_lElectronSigmaIetaIeta", &_lElectronSigmaIetaIeta, &b__lElectronSigmaIetaIeta);
    BkgEstimator_tree->SetBranchAddress("_lElectronDEtaInSeed", &_lElectronDEtaInSeed, &b__lElectronDEtaInSeed);
    BkgEstimator_tree->SetBranchAddress("_lElectronDeltaPhiSuperClusterTrack", &_lElectronDeltaPhiSuperClusterTrack, &b__lElectronDeltaPhiSuperClusterTrack);
    BkgEstimator_tree->SetBranchAddress("_lElectronDeltaEtaSuperClusterTrack", &_lElectronDeltaEtaSuperClusterTrack, &b__lElectronDeltaEtaSuperClusterTrack);
    BkgEstimator_tree->SetBranchAddress("_lElectronHOverE", &_lElectronHOverE, &b__lElectronHOverE);
    BkgEstimator_tree->SetBranchAddress("_lElectronEInvMinusPInv", &_lElectronEInvMinusPInv, &b__lElectronEInvMinusPInv);
    BkgEstimator_tree->SetBranchAddress("_lElectronNumberInnerHitsMissing", &_lElectronNumberInnerHitsMissing, &b__lElectronNumberInnerHitsMissing);
    BkgEstimator_tree->SetBranchAddress("_lGlobalMuon", &_lGlobalMuon, &b__lGlobalMuon);
    BkgEstimator_tree->SetBranchAddress("_lTrackerMuon", &_lTrackerMuon, &b__lTrackerMuon);
    BkgEstimator_tree->SetBranchAddress("_lInnerTrackValidFraction", &_lInnerTrackValidFraction, &b__lInnerTrackValidFraction);
    BkgEstimator_tree->SetBranchAddress("_lGlobalTrackNormalizedChi2", &_lGlobalTrackNormalizedChi2, &b__lGlobalTrackNormalizedChi2);
    BkgEstimator_tree->SetBranchAddress("_lCQChi2Position", &_lCQChi2Position, &b__lCQChi2Position);
    BkgEstimator_tree->SetBranchAddress("_lCQTrackKink", &_lCQTrackKink, &b__lCQTrackKink);
    BkgEstimator_tree->SetBranchAddress("_lMuonSegComp", &_lMuonSegComp, &b__lMuonSegComp);
    BkgEstimator_tree->SetBranchAddress("_lMuonTime", &_lMuonTime, &b__lMuonTime);
    BkgEstimator_tree->SetBranchAddress("_lMuonRPCTime", &_lMuonRPCTime, &b__lMuonRPCTime);
    BkgEstimator_tree->SetBranchAddress("_lMuonTrackPtErr", &_lMuonTrackPtErr, &b__lMuonTrackPtErr);

    BkgEstimator_tree->SetBranchAddress("_l1Pt", &_l1Pt, &b__l1Pt);
    BkgEstimator_tree->SetBranchAddress("_l1Eta", &_l1Eta, &b__l1Eta);
    BkgEstimator_tree->SetBranchAddress("_l1Phi", &_l1Phi, &b__l1Phi);
    BkgEstimator_tree->SetBranchAddress("_l1dxy", &_l1dxy, &b__l1dxy);
    BkgEstimator_tree->SetBranchAddress("_l1dz", &_l1dz, &b__l1dz);
    BkgEstimator_tree->SetBranchAddress("_l13dIPSig", &_l13dIPSig, &b__l13dIPSig);
    BkgEstimator_tree->SetBranchAddress("_l1relIso", &_l1relIso, &b__l1relIso);
    BkgEstimator_tree->SetBranchAddress("_l1ptRel", &_l1ptRel, &b__l1ptRel);
    BkgEstimator_tree->SetBranchAddress("_l1ptRatio", &_l1ptRatio, &b__l1ptRatio);
    BkgEstimator_tree->SetBranchAddress("_l1Flavor", &_l1Flavor, &b__l1Flavor);
    BkgEstimator_tree->SetBranchAddress("_l1Charge", &_l1Charge, &b__l1Charge);
    BkgEstimator_tree->SetBranchAddress("_l1Provenance", &_l1Provenance, &b__l1Provenance);
    BkgEstimator_tree->SetBranchAddress("_l1ProvenanceCompressed", &_l1ProvenanceCompressed, &b__l1ProvenanceCompressed);
    BkgEstimator_tree->SetBranchAddress("_l1ElectronPassConvVeto", &_l1ElectronPassConvVeto, &b__l1ElectronPassConvVeto);
    BkgEstimator_tree->SetBranchAddress("_l1ElectronMissingHits", &_l1ElectronMissingHits, &b__l1ElectronMissingHits);
    BkgEstimator_tree->SetBranchAddress("_l1ElectronSuperClusterOverP", &_l1ElectronSuperClusterOverP, &b__l1ElectronSuperClusterOverP);
    BkgEstimator_tree->SetBranchAddress("_l1ElectronEcalEnergy", &_l1ElectronEcalEnergy, &b__l1ElectronEcalEnergy);
    BkgEstimator_tree->SetBranchAddress("_l1ElectronSigmaIetaIeta", &_l1ElectronSigmaIetaIeta, &b__l1ElectronSigmaIetaIeta);
    BkgEstimator_tree->SetBranchAddress("_l1ElectronDEtaInSeed", &_l1ElectronDEtaInSeed, &b__l1ElectronDEtaInSeed);
    BkgEstimator_tree->SetBranchAddress("_l1ElectronDeltaPhiSuperClusterTrack", &_l1ElectronDeltaPhiSuperClusterTrack, &b__l1ElectronDeltaPhiSuperClusterTrack);
    BkgEstimator_tree->SetBranchAddress("_l1ElectronDeltaEtaSuperClusterTrack", &_l1ElectronDeltaEtaSuperClusterTrack, &b__l1ElectronDeltaEtaSuperClusterTrack);
    BkgEstimator_tree->SetBranchAddress("_l1ElectronHOverE", &_l1ElectronHOverE, &b__l1ElectronHOverE);
    BkgEstimator_tree->SetBranchAddress("_l1ElectronEInvMinusPInv", &_l1ElectronEInvMinusPInv, &b__l1ElectronEInvMinusPInv);
    BkgEstimator_tree->SetBranchAddress("_l1ElectronNumberInnerHitsMissing", &_l1ElectronNumberInnerHitsMissing, &b__l1ElectronNumberInnerHitsMissing);
    BkgEstimator_tree->SetBranchAddress("_l1GlobalMuon", &_l1GlobalMuon, &b__l1GlobalMuon);
    BkgEstimator_tree->SetBranchAddress("_l1TrackerMuon", &_l1TrackerMuon, &b__l1TrackerMuon);
    BkgEstimator_tree->SetBranchAddress("_l1InnerTrackValidFraction", &_l1InnerTrackValidFraction, &b__l1InnerTrackValidFraction);
    BkgEstimator_tree->SetBranchAddress("_l1GlobalTrackNormalizedChi2", &_l1GlobalTrackNormalizedChi2, &b__l1GlobalTrackNormalizedChi2);
    BkgEstimator_tree->SetBranchAddress("_l1CQChi2Position", &_l1CQChi2Position, &b__l1CQChi2Position);
    BkgEstimator_tree->SetBranchAddress("_l1CQTrackKink", &_l1CQTrackKink, &b__l1CQTrackKink);
    BkgEstimator_tree->SetBranchAddress("_l1MuonSegComp", &_l1MuonSegComp, &b__l1MuonSegComp);
    BkgEstimator_tree->SetBranchAddress("_l1MuonTime", &_l1MuonTime, &b__l1MuonTime);
    BkgEstimator_tree->SetBranchAddress("_l1MuonRPCTime", &_l1MuonRPCTime, &b__l1MuonRPCTime);
    BkgEstimator_tree->SetBranchAddress("_l1MuonTrackPtErr", &_l1MuonTrackPtErr, &b__l1MuonTrackPtErr);
    BkgEstimator_tree->SetBranchAddress("_mll", &_mll, &b__mll);
    BkgEstimator_tree->SetBranchAddress("_mlljet", &_mlljet, &b__mlljet);
    BkgEstimator_tree->SetBranchAddress("_dRll", &_dRll, &b__dRll);
    BkgEstimator_tree->SetBranchAddress("_dphill", &_dphill, &b__dphill);
    BkgEstimator_tree->SetBranchAddress("_dRljet", &_dRljet, &b__dRljet);
    BkgEstimator_tree->SetBranchAddress("_SV_PVSVdist", &_SV_PVSVdist, &b__SV_PVSVdist);
    BkgEstimator_tree->SetBranchAddress("_SV_PVSVdist_2D", &_SV_PVSVdist_2D, &b__SV_PVSVdist_2D);
    BkgEstimator_tree->SetBranchAddress("_SV_genreco", &_SV_genreco, &b__SV_genreco);
    BkgEstimator_tree->SetBranchAddress("_SV_mass", &_SV_mass, &b__SV_mass);
    BkgEstimator_tree->SetBranchAddress("_SV_l1mass", &_SV_l1mass, &b__SV_l1mass);
    BkgEstimator_tree->SetBranchAddress("_SV_pt", &_SV_pt, &b__SV_pt);
    BkgEstimator_tree->SetBranchAddress("_SV_eta", &_SV_eta, &b__SV_eta);
    BkgEstimator_tree->SetBranchAddress("_SV_phi", &_SV_phi, &b__SV_phi);
    BkgEstimator_tree->SetBranchAddress("_SV_normchi2", &_SV_normchi2, &b__SV_normchi2);
    BkgEstimator_tree->SetBranchAddress("_SV_ntracks", &_SV_ntracks, &b__SV_ntracks);
    BkgEstimator_tree->SetBranchAddress("_SV_trackpt", _SV_trackpt, &b__SV_trackpt);
    BkgEstimator_tree->SetBranchAddress("_SV_tracketa", _SV_tracketa, &b__SV_tracketa);
    BkgEstimator_tree->SetBranchAddress("_SV_trackphi", _SV_trackphi, &b__SV_trackphi);
    BkgEstimator_tree->SetBranchAddress("_SV_trackE", _SV_trackE, &b__SV_trackE);
    BkgEstimator_tree->SetBranchAddress("_SV_trackcharge", _SV_trackcharge, &b__SV_trackcharge);

    BkgEstimator_tree->SetBranchAddress("_nMV2", &_nMV2, &b__nMV2);
    BkgEstimator_tree->SetBranchAddress("_evaluating_mass", _evaluating_mass, &b__evaluating_mass);
    BkgEstimator_tree->SetBranchAddress("_evaluating_V2", _evaluating_V2, &b__evaluating_V2);
    BkgEstimator_tree->SetBranchAddress("_JetTagVal", _JetTagVal, &b__JetTagVal);
    BkgEstimator_tree->SetBranchAddress("_reweighting_weight", _reweighting_weight, &b__reweighting_weight);
}


void BkgEstimator::analyze(int max_entries, int partition, int partitionjobnumber)
{
    // Determine range of events to loop over
    Long64_t nentries = BkgEstimator_tree->GetEntries();
    if(max_entries == -1 or max_entries > nentries) max_entries = nentries;
    Long64_t j_begin = floor(1.0 * max_entries * partitionjobnumber / partition);
    Long64_t j_end   = floor(1.0 * max_entries * (partitionjobnumber + 1) / partition);
    unsigned notice = ceil(0.01 * (j_end - j_begin) / 20) * 100;
    unsigned loop_counter = 0;

    std::vector<ULong64_t> eventnumber_vec;
    //main loop
    for(unsigned jentry = j_begin; jentry < j_end; ++jentry){
	    BkgEstimator_tree->GetEntry(jentry);
	    if(loop_counter == notice){
            std::cout << jentry - j_begin << " of " << j_end - j_begin << std::endl;
            loop_counter = 0;
	    }

        if(_lFlavor == 1 and _l1Flavor == 1 and _lCharge != _l1Charge and _SV_PVSVdist_2D > 10 and _SV_mass < 2){
            eventnumber_vec.push_back(_eventNb);
        }
        ++loop_counter;
    }

    std::sort(eventnumber_vec.begin(), eventnumber_vec.end());
    for(auto nb : eventnumber_vec){
        std::ostringstream eventnumberstream;
        eventnumberstream << nb << "\n";
        filePutContents("EventNumbers_OSmmL10M02.txt", eventnumberstream.str(), true);
    }
}


void BkgEstimator::fill_tree()
{
    BkgEstimator_tree->Fill();
}

void BkgEstimator::write_tree()
{
    //BkgEstimator_tree->Print();
    std::cout << "writing BkgEstimator tree to " << BkgEstimator_filename << std::endl;
    BkgEstimator_file->cd();
    hCounter->Write(hCounter->GetName(), TObject::kOverwrite);
    BkgEstimator_file->Write();
    BkgEstimator_file->Close();
}

void BkgEstimator::delete_tree()
{
    BkgEstimator_file->Close();
    gSystem->Exec("rm " + BkgEstimator_filename);
}

void BkgEstimator::copy_event(BkgEstimator* original)
{
    _runNb = original->_runNb;
    _lumiBlock = original->_lumiBlock;
    _eventNb = original->_eventNb;
    _is2016 = original->_is2016;
    _is2017 = original->_is2017;
    _is2018 = original->_is2018;
    _weight = original->_weight;
    _RawWeight = original->_RawWeight;
    _l1_IDSF = original->_l1_IDSF;
    _l1_IDSF_unc_sym = original->_l1_IDSF_unc_sym;
    _l2_IDSF = original->_l2_IDSF;
    _l2_IDSF_unc_sym = original->_l2_IDSF_unc_sym;
    _TrackSF = original->_TrackSF;
    _TrackSF_unc_sym = original->_TrackSF_unc_sym;
    _l1_ISOSF = original->_l1_ISOSF;
    _l1_ISOSF_unc_sym = original->_l1_ISOSF_unc_sym;
    _TriggerSF = original->_TriggerSF;
    _TriggerSF_unc_sym = original->_TriggerSF_unc_sym;
    _PileUpSF = original->_PileUpSF;
    _PileUpSF_unc_up = original->_PileUpSF_unc_up;
    _PileUpSF_unc_down = original->_PileUpSF_unc_down;
    _gen_Nmass = original->_gen_Nmass;
    _gen_NV2 = original->_gen_NV2;
    _gen_Nctau = original->_gen_Nctau;
    _JetIsFromHNL = original->_JetIsFromHNL;
    _nTightJet = original->_nTightJet;
    _nMediumBJet = original->_nMediumBJet;
    _nLooseBJet = original->_nLooseBJet;
    _JetPt = original->_JetPt;
    _JetEta = original->_JetEta;
    _JetPhi = original->_JetPhi;
    _nTightLep = original->_nTightLep;
    _lPt = original->_lPt;
    _lEta = original->_lEta;
    _lPhi = original->_lPhi;
    _ldxy = original->_ldxy;
    _ldz = original->_ldz;
    _l3dIPSig = original->_l3dIPSig;
    _lrelIso = original->_lrelIso;
    _lptRatio = original->_lptRatio;
    _lptRel = original->_lptRel;
    _lNumberOfHits = original->_lNumberOfHits;
    _lNumberOfPixelHits = original->_lNumberOfPixelHits;
    _lFlavor = original->_lFlavor;
    _lCharge = original->_lCharge;
    _lProvenance = original->_lProvenance;
    _lProvenanceCompressed = original->_lProvenanceCompressed;
    _lElectronPassConvVeto = original->_lElectronPassConvVeto;
    _lElectronMissingHits = original->_lElectronMissingHits;
    _lElectronSuperClusterOverP = original->_lElectronSuperClusterOverP;
    _lElectronEcalEnergy = original->_lElectronEcalEnergy;
    _lElectronSigmaIetaIeta = original->_lElectronSigmaIetaIeta;
    _lElectronDEtaInSeed = original->_lElectronDEtaInSeed;
    _lElectronDeltaPhiSuperClusterTrack = original->_lElectronDeltaPhiSuperClusterTrack;
    _lElectronDeltaEtaSuperClusterTrack = original->_lElectronDeltaEtaSuperClusterTrack;
    _lElectronHOverE = original->_lElectronHOverE;
    _lElectronEInvMinusPInv = original->_lElectronEInvMinusPInv;
    _lElectronNumberInnerHitsMissing = original->_lElectronNumberInnerHitsMissing;
    _lGlobalMuon = original->_lGlobalMuon;
    _lTrackerMuon = original->_lTrackerMuon;
    _lInnerTrackValidFraction = original->_lInnerTrackValidFraction;
    _lGlobalTrackNormalizedChi2 = original->_lGlobalTrackNormalizedChi2;
    _lCQChi2Position = original->_lCQChi2Position;
    _lCQTrackKink = original->_lCQTrackKink;
    _lMuonSegComp = original->_lMuonSegComp;
    _lMuonTime = original->_lMuonTime;
    _lMuonRPCTime = original->_lMuonRPCTime;
    _lMuonTrackPtErr = original->_lMuonTrackPtErr;

    _l1Pt = original->_l1Pt;
    _l1Eta = original->_l1Eta;
    _l1Phi = original->_l1Phi;
    _l1dxy = original->_l1dxy;
    _l1dz = original->_l1dz;
    _l13dIPSig = original->_l13dIPSig;
    _l1relIso = original->_l1relIso;
    _l1ptRatio = original->_l1ptRatio;
    _l1ptRel = original->_l1ptRel;
    _l1Flavor = original->_l1Flavor;
    _l1Charge = original->_l1Charge;
    _l1Provenance = original->_l1Provenance;
    _l1ProvenanceCompressed = original->_l1ProvenanceCompressed;
    _l1ElectronPassConvVeto = original->_l1ElectronPassConvVeto;
    _l1ElectronMissingHits = original->_l1ElectronMissingHits;
    _l1ElectronSuperClusterOverP = original->_l1ElectronSuperClusterOverP;
    _l1ElectronEcalEnergy = original->_l1ElectronEcalEnergy;
    _l1ElectronSigmaIetaIeta = original->_l1ElectronSigmaIetaIeta;
    _l1ElectronDEtaInSeed = original->_l1ElectronDEtaInSeed;
    _l1ElectronDeltaPhiSuperClusterTrack = original->_l1ElectronDeltaPhiSuperClusterTrack;
    _l1ElectronDeltaEtaSuperClusterTrack = original->_l1ElectronDeltaEtaSuperClusterTrack;
    _l1ElectronHOverE = original->_l1ElectronHOverE;
    _l1ElectronEInvMinusPInv = original->_l1ElectronEInvMinusPInv;
    _l1ElectronNumberInnerHitsMissing = original->_l1ElectronNumberInnerHitsMissing;
    _l1GlobalMuon = original->_l1GlobalMuon;
    _l1TrackerMuon = original->_l1TrackerMuon;
    _l1InnerTrackValidFraction = original->_l1InnerTrackValidFraction;
    _l1GlobalTrackNormalizedChi2 = original->_l1GlobalTrackNormalizedChi2;
    _l1CQChi2Position = original->_l1CQChi2Position;
    _l1CQTrackKink = original->_l1CQTrackKink;
    _l1MuonSegComp = original->_l1MuonSegComp;
    _l1MuonTime = original->_l1MuonTime;
    _l1MuonRPCTime = original->_l1MuonRPCTime;
    _l1MuonTrackPtErr = original->_l1MuonTrackPtErr;
    _mll = original->_mll;
    _mlljet = original->_mlljet;
    _dRll = original->_dRll;
    _dphill = original->_dphill;
    _dRljet = original->_dRljet;
    _SV_PVSVdist = original->_SV_PVSVdist;
    _SV_PVSVdist_2D = original->_SV_PVSVdist_2D;
    _SV_genreco = original->_SV_genreco;
    _SV_mass = original->_SV_mass;
    _SV_l1mass = original->_SV_l1mass;
    _SV_pt = original->_SV_pt;
    _SV_eta = original->_SV_eta;
    _SV_phi = original->_SV_phi;
    _SV_normchi2 = original->_SV_normchi2;
    _SV_ntracks = original->_SV_ntracks;
    for(unsigned i = 0; i < _SV_ntracks; i++){
        _SV_trackpt[i] = original->_SV_trackpt[i];
        _SV_tracketa[i] = original->_SV_tracketa[i];
        _SV_trackphi[i] = original->_SV_trackphi[i];
        _SV_trackE[i] = original->_SV_trackE[i];
        _SV_trackcharge[i] = original->_SV_trackcharge[i];
    }
    _nMV2 = original->_nMV2;
    for(unsigned i = 0; i < _nMV2; i++){
        _evaluating_mass[i] = original->_evaluating_mass[i];
        _evaluating_V2[i] = original->_evaluating_V2[i];
        _JetTagVal[i] = original->_JetTagVal[i];
        _reweighting_weight[i] = original->_reweighting_weight[i];
    }
}
