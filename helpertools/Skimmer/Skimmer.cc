#include "Skimmer.h"

void Skimmer::Init_input_branches(TTree* tree)
{
    if(!tree){
        std::cout << "Error: Input tree can't be initialized because it doesn't seem to exist" << std::endl;
        return;
    }
    tree->SetMakeClass(1);

    tree->SetBranchAddress("_runNb", &i_runNb, &bi__runNb);
    tree->SetBranchAddress("_lumiBlock", &i_lumiBlock, &bi__lumiBlock);
    tree->SetBranchAddress("_eventNb", &i_eventNb, &bi__eventNb);
    tree->SetBranchAddress("_nVertex", &i_nVertex, &bi__nVertex);
    if(!isData){
         //tree->SetBranchAddress("_prefireWeight", &i_prefireWeight, &bi__prefireWeight);
         //tree->SetBranchAddress("_prefireWeightUp", &i_prefireWeightUp, &bi__prefireWeightUp);
         //tree->SetBranchAddress("_prefireWeightDown", &i_prefireWeightDown, &bi__prefireWeightDown);
         tree->SetBranchAddress("_nTrueInt", &i_nTrueInt, &bi__nTrueInt);
         tree->SetBranchAddress("_weight", &i_weight, &bi__weight);
         tree->SetBranchAddress("_lheHTIncoming", &i_lheHTIncoming, &bi__lheHTIncoming);
         tree->SetBranchAddress("_ctauHN", &i_ctauHN, &bi__ctauHN);
         tree->SetBranchAddress("_nLheTau", &i_nLheTau, &bi__nLheTau);
         tree->SetBranchAddress("_nLheWeights", &i_nLheWeights, &bi__nLheWeights);
         tree->SetBranchAddress("_lheWeight", i_lheWeight, &bi__lheWeight);
         tree->SetBranchAddress("_nPsWeights", &i_nPsWeights, &bi__nPsWeights);
         tree->SetBranchAddress("_psWeight", i_psWeight, &bi__psWeight);
         tree->SetBranchAddress("_ttgEventType", &i_ttgEventType, &bi__ttgEventType);
         tree->SetBranchAddress("_zgEventType", &i_zgEventType, &bi__zgEventType);
         tree->SetBranchAddress("_gen_met", &i_gen_met, &bi__gen_met);
         tree->SetBranchAddress("_gen_metPhi", &i_gen_metPhi, &bi__gen_metPhi);
         tree->SetBranchAddress("_gen_nPh", &i_gen_nPh, &bi__gen_nPh);
         tree->SetBranchAddress("_gen_phStatus", i_gen_phStatus, &bi__gen_phStatus);
         tree->SetBranchAddress("_gen_phPt", i_gen_phPt, &bi__gen_phPt);
         tree->SetBranchAddress("_gen_phEta", i_gen_phEta, &bi__gen_phEta);
         tree->SetBranchAddress("_gen_phPhi", i_gen_phPhi, &bi__gen_phPhi);
         tree->SetBranchAddress("_gen_phE", i_gen_phE, &bi__gen_phE);
         tree->SetBranchAddress("_gen_phMomPdg", i_gen_phMomPdg, &bi__gen_phMomPdg);
         tree->SetBranchAddress("_gen_phIsPrompt", i_gen_phIsPrompt, &bi__gen_phIsPrompt);
         tree->SetBranchAddress("_gen_phMinDeltaR", i_gen_phMinDeltaR, &bi__gen_phMinDeltaR);
         tree->SetBranchAddress("_gen_phPassParentage", i_gen_phPassParentage, &bi__gen_phPassParentage);
         tree->SetBranchAddress("_gen_nL", &i_gen_nL, &bi__gen_nL);
         tree->SetBranchAddress("_gen_lPt", i_gen_lPt, &bi__gen_lPt);
         tree->SetBranchAddress("_gen_lEta", i_gen_lEta, &bi__gen_lEta);
         tree->SetBranchAddress("_gen_lPhi", i_gen_lPhi, &bi__gen_lPhi);
         tree->SetBranchAddress("_gen_lE", i_gen_lE, &bi__gen_lE);
         tree->SetBranchAddress("_gen_lFlavor", i_gen_lFlavor, &bi__gen_lFlavor);
         tree->SetBranchAddress("_gen_lCharge", i_gen_lCharge, &bi__gen_lCharge);
         tree->SetBranchAddress("_gen_lMomPdg", i_gen_lMomPdg, &bi__gen_lMomPdg);
         tree->SetBranchAddress("_gen_lIsPrompt", i_gen_lIsPrompt, &bi__gen_lIsPrompt);
         tree->SetBranchAddress("_gen_lDecayedHadr", i_gen_lDecayedHadr, &bi__gen_lDecayedHadr);
         tree->SetBranchAddress("_gen_lMinDeltaR", i_gen_lMinDeltaR, &bi__gen_lMinDeltaR);
         tree->SetBranchAddress("_gen_lPassParentage", i_gen_lPassParentage, &bi__gen_lPassParentage);
    }
    tree->SetBranchAddress("_passMETFilters", &i_passMETFilters, &bi__passMETFilters);
    tree->SetBranchAddress("_Flag_goodVertices", &i_Flag_goodVertices, &bi__Flag_goodVertices);
    tree->SetBranchAddress("_Flag_HBHENoiseFilter", &i_Flag_HBHENoiseFilter, &bi__Flag_HBHENoiseFilter);
    tree->SetBranchAddress("_Flag_HBHENoiseIsoFilter", &i_Flag_HBHENoiseIsoFilter, &bi__Flag_HBHENoiseIsoFilter);
    tree->SetBranchAddress("_Flag_EcalDeadCellTriggerPrimitiveFilter", &i_Flag_EcalDeadCellTriggerPrimitiveFilter, &bi__Flag_EcalDeadCellTriggerPrimitiveFilter);
    tree->SetBranchAddress("_Flag_BadPFMuonFilter", &i_Flag_BadPFMuonFilter, &bi__Flag_BadPFMuonFilter);
    tree->SetBranchAddress("_Flag_BadChargedCandidateFilter", &i_Flag_BadChargedCandidateFilter, &bi__Flag_BadChargedCandidateFilter);
    tree->SetBranchAddress("_Flag_globalSuperTightHalo2016Filter", &i_Flag_globalSuperTightHalo2016Filter, &bi__Flag_globalSuperTightHalo2016Filter);
    tree->SetBranchAddress("_updated_ecalBadCalibFilter", &i_updated_ecalBadCalibFilter, &bi__updated_ecalBadCalibFilter);
    tree->SetBranchAddress("_passTrigger_FR", &i_passTrigger_FR, &bi__passTrigger_FR);
    tree->SetBranchAddress("_passTrigger_e", &i_passTrigger_e, &bi__passTrigger_e);
    tree->SetBranchAddress("_passTrigger_ee", &i_passTrigger_ee, &bi__passTrigger_ee);
    tree->SetBranchAddress("_passTrigger_eee", &i_passTrigger_eee, &bi__passTrigger_eee);
    tree->SetBranchAddress("_passTrigger_eem", &i_passTrigger_eem, &bi__passTrigger_eem);
    tree->SetBranchAddress("_passTrigger_em", &i_passTrigger_em, &bi__passTrigger_em);
    tree->SetBranchAddress("_passTrigger_emm", &i_passTrigger_emm, &bi__passTrigger_emm);
    tree->SetBranchAddress("_passTrigger_et", &i_passTrigger_et, &bi__passTrigger_et);
    tree->SetBranchAddress("_passTrigger_m", &i_passTrigger_m, &bi__passTrigger_m);
    tree->SetBranchAddress("_passTrigger_mm", &i_passTrigger_mm, &bi__passTrigger_mm);
    tree->SetBranchAddress("_passTrigger_mmm", &i_passTrigger_mmm, &bi__passTrigger_mmm);
    tree->SetBranchAddress("_passTrigger_mt", &i_passTrigger_mt, &bi__passTrigger_mt);
    tree->SetBranchAddress("_passTrigger_ref", &i_passTrigger_ref, &bi__passTrigger_ref);
    tree->SetBranchAddress("_nL", &i_nL, &bi__nL);
    tree->SetBranchAddress("_nMu", &i_nMu, &bi__nMu);
    tree->SetBranchAddress("_nEle", &i_nEle, &bi__nEle);
    tree->SetBranchAddress("_nLight", &i_nLight, &bi__nLight);
    tree->SetBranchAddress("_nTau", &i_nTau, &bi__nTau);
    tree->SetBranchAddress("_lPt", i_lPt, &bi__lPt);
    tree->SetBranchAddress("_lEta", i_lEta, &bi__lEta);
    tree->SetBranchAddress("_lEtaSC", i_lEtaSC, &bi__lEtaSC);
    tree->SetBranchAddress("_lPhi", i_lPhi, &bi__lPhi);
    tree->SetBranchAddress("_lE", i_lE, &bi__lE);
    tree->SetBranchAddress("_lFlavor", i_lFlavor, &bi__lFlavor);
    tree->SetBranchAddress("_lCharge", i_lCharge, &bi__lCharge);
    tree->SetBranchAddress("_dxy", i_dxy, &bi__dxy);
    tree->SetBranchAddress("_dz", i_dz, &bi__dz);
    tree->SetBranchAddress("_3dIP", i_3dIP, &bi__3dIP);
    tree->SetBranchAddress("_3dIPSig", i_3dIPSig, &bi__3dIPSig);
    tree->SetBranchAddress("_lElectronSummer16MvaGP", i_lElectronSummer16MvaGP, &bi__lElectronSummer16MvaGP);
    tree->SetBranchAddress("_lElectronSummer16MvaHZZ", i_lElectronSummer16MvaHZZ, &bi__lElectronSummer16MvaHZZ);
    tree->SetBranchAddress("_lElectronMvaFall17v1NoIso", i_lElectronMvaFall17v1NoIso, &bi__lElectronMvaFall17v1NoIso);
    tree->SetBranchAddress("_lElectronMvaFall17Iso", i_lElectronMvaFall17Iso, &bi__lElectronMvaFall17Iso);
    tree->SetBranchAddress("_lElectronMvaFall17NoIso", i_lElectronMvaFall17NoIso, &bi__lElectronMvaFall17NoIso);
    tree->SetBranchAddress("_lElectronPassEmu", i_lElectronPassEmu, &bi__lElectronPassEmu);
    tree->SetBranchAddress("_lElectronPassConvVeto", i_lElectronPassConvVeto, &bi__lElectronPassConvVeto);
    tree->SetBranchAddress("_lElectronChargeConst", i_lElectronChargeConst, &bi__lElectronChargeConst);
    tree->SetBranchAddress("_lElectronMissingHits", i_lElectronMissingHits, &bi__lElectronMissingHits);
    tree->SetBranchAddress("_leptonMvaSUSY", i_leptonMvaSUSY, &bi__leptonMvaSUSY);
    tree->SetBranchAddress("_leptonMvaTTH", i_leptonMvaTTH, &bi__leptonMvaTTH);
    tree->SetBranchAddress("_leptonMvatZq", i_leptonMvatZq, &bi__leptonMvatZq);
    tree->SetBranchAddress("_lEwkLoose", i_lEwkLoose, &bi__lEwkLoose);
    tree->SetBranchAddress("_lEwkFO", i_lEwkFO, &bi__lEwkFO);
    tree->SetBranchAddress("_lEwkTight", i_lEwkTight, &bi__lEwkTight);
    tree->SetBranchAddress("_lPOGVeto", i_lPOGVeto, &bi__lPOGVeto);
    tree->SetBranchAddress("_lPOGLoose", i_lPOGLoose, &bi__lPOGLoose);
    tree->SetBranchAddress("_lPOGMedium", i_lPOGMedium, &bi__lPOGMedium);
    tree->SetBranchAddress("_lPOGTight", i_lPOGTight, &bi__lPOGTight);
    tree->SetBranchAddress("_tauMuonVetoLoose", i_tauMuonVetoLoose, &bi__tauMuonVetoLoose);
    tree->SetBranchAddress("_tauEleVetoLoose", i_tauEleVetoLoose, &bi__tauEleVetoLoose);
    tree->SetBranchAddress("_decayModeFinding", i_decayModeFinding, &bi__decayModeFinding);
    tree->SetBranchAddress("_tauAgainstElectronMVA6Raw", i_tauAgainstElectronMVA6Raw, &bi__tauAgainstElectronMVA6Raw);
    tree->SetBranchAddress("_tauCombinedIsoDBRaw3Hits", i_tauCombinedIsoDBRaw3Hits, &bi__tauCombinedIsoDBRaw3Hits);
    tree->SetBranchAddress("_tauIsoMVAPWdR03oldDMwLT", i_tauIsoMVAPWdR03oldDMwLT, &bi__tauIsoMVAPWdR03oldDMwLT);
    tree->SetBranchAddress("_tauIsoMVADBdR03oldDMwLT", i_tauIsoMVADBdR03oldDMwLT, &bi__tauIsoMVADBdR03oldDMwLT);
    tree->SetBranchAddress("_tauIsoMVADBdR03newDMwLT", i_tauIsoMVADBdR03newDMwLT, &bi__tauIsoMVADBdR03newDMwLT);
    tree->SetBranchAddress("_tauIsoMVAPWnewDMwLT", i_tauIsoMVAPWnewDMwLT, &bi__tauIsoMVAPWnewDMwLT);
    tree->SetBranchAddress("_tauIsoMVAPWoldDMwLT", i_tauIsoMVAPWoldDMwLT, &bi__tauIsoMVAPWoldDMwLT);
    tree->SetBranchAddress("_relIso", i_relIso, &bi__relIso);
    tree->SetBranchAddress("_relIso0p4", i_relIso0p4, &bi__relIso0p4);
    tree->SetBranchAddress("_relIso0p4MuDeltaBeta", i_relIso0p4MuDeltaBeta, &bi__relIso0p4MuDeltaBeta);
    tree->SetBranchAddress("_miniIso", i_miniIso, &bi__miniIso);
    tree->SetBranchAddress("_miniIsoCharged", i_miniIsoCharged, &bi__miniIsoCharged);
    tree->SetBranchAddress("_ptRel", i_ptRel, &bi__ptRel);
    tree->SetBranchAddress("_ptRatio", i_ptRatio, &bi__ptRatio);
    tree->SetBranchAddress("_closestJetCsvV2", i_closestJetCsvV2, &bi__closestJetCsvV2);
    tree->SetBranchAddress("_closestJetDeepCsv_b", i_closestJetDeepCsv_b, &bi__closestJetDeepCsv_b);
    tree->SetBranchAddress("_closestJetDeepCsv_bb", i_closestJetDeepCsv_bb, &bi__closestJetDeepCsv_bb);
    tree->SetBranchAddress("_closestJetDeepCsv", i_closestJetDeepCsv, &bi__closestJetDeepCsv);
    tree->SetBranchAddress("_selectedTrackMult", i_selectedTrackMult, &bi__selectedTrackMult);
    tree->SetBranchAddress("_lMuonSegComp", i_lMuonSegComp, &bi__lMuonSegComp);
    tree->SetBranchAddress("_lMuonTrackPt", i_lMuonTrackPt, &bi__lMuonTrackPt);
    tree->SetBranchAddress("_lMuonTrackPtErr", i_lMuonTrackPtErr, &bi__lMuonTrackPtErr);
    tree->SetBranchAddress("_lIsPrompt", i_lIsPrompt, &bi__lIsPrompt);
    tree->SetBranchAddress("_lMatchPdgId", i_lMatchPdgId, &bi__lMatchPdgId);
    tree->SetBranchAddress("_lMatchCharge", i_lMatchCharge, &bi__lMatchCharge);
    tree->SetBranchAddress("_tauGenStatus", i_tauGenStatus, &bi__tauGenStatus);
    tree->SetBranchAddress("_lMomPdgId", i_lMomPdgId, &bi__lMomPdgId);
    tree->SetBranchAddress("_lProvenance", i_lProvenance, &bi__lProvenance);
    tree->SetBranchAddress("_lProvenanceCompressed", i_lProvenanceCompressed, &bi__lProvenanceCompressed);
    tree->SetBranchAddress("_lProvenanceConversion", i_lProvenanceConversion, &bi__lProvenanceConversion);
    tree->SetBranchAddress("_lPtCorr", i_lPtCorr, &bi__lPtCorr);
    tree->SetBranchAddress("_lPtScaleUp", i_lPtScaleUp, &bi__lPtScaleUp);
    tree->SetBranchAddress("_lPtScaleDown", i_lPtScaleDown, &bi__lPtScaleDown);
    tree->SetBranchAddress("_lPtResUp", i_lPtResUp, &bi__lPtResUp);
    tree->SetBranchAddress("_lPtResDown", i_lPtResDown, &bi__lPtResDown);
    tree->SetBranchAddress("_nPh", &i_nPh, &bi__nPh);
    tree->SetBranchAddress("_phPt", i_phPt, &bi__phPt);
    tree->SetBranchAddress("_phEta", i_phEta, &bi__phEta);
    tree->SetBranchAddress("_phEtaSC", i_phEtaSC, &bi__phEtaSC);
    tree->SetBranchAddress("_phPhi", i_phPhi, &bi__phPhi);
    tree->SetBranchAddress("_phE", i_phE, &bi__phE);
    tree->SetBranchAddress("_phCutBasedLoose", i_phCutBasedLoose, &bi__phCutBasedLoose);
    tree->SetBranchAddress("_phCutBasedMedium", i_phCutBasedMedium, &bi__phCutBasedMedium);
    tree->SetBranchAddress("_phCutBasedTight", i_phCutBasedTight, &bi__phCutBasedTight);
    tree->SetBranchAddress("_phMva", i_phMva, &bi__phMva);
    tree->SetBranchAddress("_phRandomConeChargedIsolation", i_phRandomConeChargedIsolation, &bi__phRandomConeChargedIsolation);
    tree->SetBranchAddress("_phChargedIsolation", i_phChargedIsolation, &bi__phChargedIsolation);
    tree->SetBranchAddress("_phNeutralHadronIsolation", i_phNeutralHadronIsolation, &bi__phNeutralHadronIsolation);
    tree->SetBranchAddress("_phPhotonIsolation", i_phPhotonIsolation, &bi__phPhotonIsolation);
    tree->SetBranchAddress("_phSigmaIetaIeta", i_phSigmaIetaIeta, &bi__phSigmaIetaIeta);
    tree->SetBranchAddress("_phHadronicOverEm", i_phHadronicOverEm, &bi__phHadronicOverEm);
    tree->SetBranchAddress("_phHadTowOverEm", i_phHadTowOverEm, &bi__phHadTowOverEm);
    tree->SetBranchAddress("_phPassElectronVeto", i_phPassElectronVeto, &bi__phPassElectronVeto);
    tree->SetBranchAddress("_phHasPixelSeed", i_phHasPixelSeed, &bi__phHasPixelSeed);
    tree->SetBranchAddress("_phIsPrompt", i_phIsPrompt, &bi__phIsPrompt);
    tree->SetBranchAddress("_phMatchPdgId", i_phMatchPdgId, &bi__phMatchPdgId);
    tree->SetBranchAddress("_phPtCorr", i_phPtCorr, &bi__phPtCorr);
    tree->SetBranchAddress("_phPtScaleUp", i_phPtScaleUp, &bi__phPtScaleUp);
    tree->SetBranchAddress("_phPtScaleDown", i_phPtScaleDown, &bi__phPtScaleDown);
    tree->SetBranchAddress("_phPtResUp", i_phPtResUp, &bi__phPtResUp);
    tree->SetBranchAddress("_phPtResDown", i_phPtResDown, &bi__phPtResDown);
    tree->SetBranchAddress("_nJets", &i_nJets, &bi__nJets);
    tree->SetBranchAddress("_jetPt", i_jetPt, &bi__jetPt);
    tree->SetBranchAddress("_jetPt_JECUp", i_jetPt_JECUp, &bi__jetPt_JECUp);
    tree->SetBranchAddress("_jetPt_JECDown", i_jetPt_JECDown, &bi__jetPt_JECDown);
    tree->SetBranchAddress("_jetPt_Uncorrected", i_jetPt_Uncorrected, &bi__jetPt_Uncorrected);
    tree->SetBranchAddress("_jetPt_L1", i_jetPt_L1, &bi__jetPt_L1);
    tree->SetBranchAddress("_jetPt_L2", i_jetPt_L2, &bi__jetPt_L2);
    tree->SetBranchAddress("_jetPt_L3", i_jetPt_L3, &bi__jetPt_L3);
    tree->SetBranchAddress("_jetSmearedPt", i_jetSmearedPt, &bi__jetSmearedPt);
    tree->SetBranchAddress("_jetSmearedPt_JECDown", i_jetSmearedPt_JECDown, &bi__jetSmearedPt_JECDown);
    tree->SetBranchAddress("_jetSmearedPt_JECUp", i_jetSmearedPt_JECUp, &bi__jetSmearedPt_JECUp);
    tree->SetBranchAddress("_jetSmearedPt_JERDown", i_jetSmearedPt_JERDown, &bi__jetSmearedPt_JERDown);
    tree->SetBranchAddress("_jetSmearedPt_JERUp", i_jetSmearedPt_JERUp, &bi__jetSmearedPt_JERUp);
    tree->SetBranchAddress("_jetEta", i_jetEta, &bi__jetEta);
    tree->SetBranchAddress("_jetPhi", i_jetPhi, &bi__jetPhi);
    tree->SetBranchAddress("_jetE", i_jetE, &bi__jetE);
    tree->SetBranchAddress("_jetCsvV2", i_jetCsvV2, &bi__jetCsvV2);
    tree->SetBranchAddress("_jetDeepCsv_udsg", i_jetDeepCsv_udsg, &bi__jetDeepCsv_udsg);
    tree->SetBranchAddress("_jetDeepCsv_b", i_jetDeepCsv_b, &bi__jetDeepCsv_b);
    tree->SetBranchAddress("_jetDeepCsv_c", i_jetDeepCsv_c, &bi__jetDeepCsv_c);
    tree->SetBranchAddress("_jetDeepCsv_bb", i_jetDeepCsv_bb, &bi__jetDeepCsv_bb);
    tree->SetBranchAddress("_jetDeepCsv", &i_jetDeepCsv, &bi__jetDeepCsv);
    tree->SetBranchAddress("_jetHadronFlavor", i_jetHadronFlavor, &bi__jetHadronFlavor);
    tree->SetBranchAddress("_jetIsTight", i_jetIsTight, &bi__jetIsTight);
    tree->SetBranchAddress("_jetIsTightLepVeto", i_jetIsTightLepVeto, &bi__jetIsTightLepVeto);
    tree->SetBranchAddress("_jetNeutralHadronFraction", i_jetNeutralHadronFraction, &bi__jetNeutralHadronFraction);
    tree->SetBranchAddress("_jetChargedHadronFraction", i_jetChargedHadronFraction, &bi__jetChargedHadronFraction);
    tree->SetBranchAddress("_jetNeutralEmFraction", i_jetNeutralEmFraction, &bi__jetNeutralEmFraction);
    tree->SetBranchAddress("_jetChargedEmFraction", i_jetChargedEmFraction, &bi__jetChargedEmFraction);
    tree->SetBranchAddress("_jetHFHadronFraction", i_jetHFHadronFraction, &bi__jetHFHadronFraction);
    tree->SetBranchAddress("_jetHFEmFraction", i_jetHFEmFraction, &bi__jetHFEmFraction);
    tree->SetBranchAddress("_met", &i_met, &bi__met);
    tree->SetBranchAddress("_metRaw", &i_metRaw, &bi__metRaw);
    tree->SetBranchAddress("_metJECDown", &i_metJECDown, &bi__metJECDown);
    tree->SetBranchAddress("_metJECUp", &i_metJECUp, &bi__metJECUp);
    tree->SetBranchAddress("_metUnclDown", &i_metUnclDown, &bi__metUnclDown);
    tree->SetBranchAddress("_metUnclUp", &i_metUnclUp, &bi__metUnclUp);
    tree->SetBranchAddress("_metPhi", &i_metPhi, &bi__metPhi);
    tree->SetBranchAddress("_metRawPhi", &i_metRawPhi, &bi__metRawPhi);
    tree->SetBranchAddress("_metPhiJECDown", &i_metPhiJECDown, &bi__metPhiJECDown);
    tree->SetBranchAddress("_metPhiJECUp", &i_metPhiJECUp, &bi__metPhiJECUp);
    tree->SetBranchAddress("_metPhiUnclDown", &i_metPhiUnclDown, &bi__metPhiUnclDown);
    tree->SetBranchAddress("_metPhiUnclUp", &i_metPhiUnclUp, &bi__metPhiUnclUp);
    tree->SetBranchAddress("_metSignificance", &i_metSignificance, &bi__metSignificance);
}


void Skimmer::Add_branches(TTree* tree)
{
    tree->Branch("_runNb",                          &o_runNb,                        "_runNb/l");
    tree->Branch("_lumiBlock",                      &o_lumiBlock,                    "_lumiBlock/l");
    tree->Branch("_eventNb",                        &o_eventNb,                      "_eventNb/l");
    tree->Branch("_nVertex",                        &o_nVertex,                      "_nVertex/b");
    if(!isData){
        //tree->Branch("_prefireWeight",              &o_prefireWeight,                "_prefireWeight/F");
        //tree->Branch("_prefireWeightUp",            &o_prefireWeightUp,              "_prefireWeightUp/F");
        //tree->Branch("_prefireWeightDown",          &o_prefireWeightDown,            "_prefireWeightDown/F");

        tree->Branch("_nTrueInt",                       &o_nTrueInt,                     "_nTrueInt/F");
        tree->Branch("_weight",                         &o_weight,                       "_weight/D");
        tree->Branch("_lheHTIncoming",                  &o_lheHTIncoming,                "_lheHTIncoming/D");
        tree->Branch("_ctauHN",                         &o_ctauHN,                       "_ctauHN/D");
        tree->Branch("_nLheTau",                        &o_nLheTau,                      "_nLheTau/i");
        tree->Branch("_nLheWeights",                    &o_nLheWeights,                  "_nLheWeights/i");
        tree->Branch("_lheWeight",                      &o_lheWeight,                    "_lheWeight[_nLheWeights]/D");
        tree->Branch("_nPsWeights",                     &o_nPsWeights,                   "_nPsWeights/i");
        tree->Branch("_psWeight",                       &o_psWeight,                     "_psWeight[_nPsWeights]/D");

        tree->Branch("_ttgEventType",                   &o_ttgEventType,                 "_ttgEventType/i");
        tree->Branch("_zgEventType",                    &o_zgEventType,                  "_zgEventType/i");
        tree->Branch("_gen_met",                        &o_gen_met,                      "_gen_met/D");
        tree->Branch("_gen_metPhi",                     &o_gen_metPhi,                   "_gen_metPhi/D");
        tree->Branch("_gen_nPh",                        &o_gen_nPh,                      "_gen_nPh/i");
        tree->Branch("_gen_phStatus",                   &o_gen_phStatus,                 "_gen_phStatus[_gen_nPh]/i");
        tree->Branch("_gen_phPt",                       &o_gen_phPt,                     "_gen_phPt[_gen_nPh]/D");
        tree->Branch("_gen_phEta",                      &o_gen_phEta,                    "_gen_phEta[_gen_nPh]/D");
        tree->Branch("_gen_phPhi",                      &o_gen_phPhi,                    "_gen_phPhi[_gen_nPh]/D");
        tree->Branch("_gen_phE",                        &o_gen_phE,                      "_gen_phE[_gen_nPh]/D");
        tree->Branch("_gen_phMomPdg",                   &o_gen_phMomPdg,                 "_gen_phMomPdg[_gen_nPh]/I");
        tree->Branch("_gen_phIsPrompt",                 &o_gen_phIsPrompt,               "_gen_phIsPrompt[_gen_nPh]/O");
        tree->Branch("_gen_phMinDeltaR",                &o_gen_phMinDeltaR,              "_gen_phMinDeltaR[_gen_nPh]/D");
        tree->Branch("_gen_phPassParentage",            &o_gen_phPassParentage,          "_gen_phPassParentage[_gen_nPh]/O");
        tree->Branch("_gen_nL",                         &o_gen_nL,                       "_gen_nL/i");
        tree->Branch("_gen_lPt",                        &o_gen_lPt,                      "_gen_lPt[_gen_nL]/D");
        tree->Branch("_gen_lEta",                       &o_gen_lEta,                     "_gen_lEta[_gen_nL]/D");
        tree->Branch("_gen_lPhi",                       &o_gen_lPhi,                     "_gen_lPhi[_gen_nL]/D");
        tree->Branch("_gen_lE",                         &o_gen_lE,                       "_gen_lE[_gen_nL]/D");
        tree->Branch("_gen_lFlavor",                    &o_gen_lFlavor,                  "_gen_lFlavor[_gen_nL]/i");
        tree->Branch("_gen_lCharge",                    &o_gen_lCharge,                  "_gen_lCharge[_gen_nL]/I");
        tree->Branch("_gen_lMomPdg",                    &o_gen_lMomPdg,                  "_gen_lMomPdg[_gen_nL]/I");
        tree->Branch("_gen_lIsPrompt",                  &o_gen_lIsPrompt,                "_gen_lIsPrompt[_gen_nL]/O");
        tree->Branch("_gen_lDecayedHadr",               &o_gen_lDecayedHadr,             "_gen_lDecayedHadr[_gen_nL]/O");
        tree->Branch("_gen_lMinDeltaR",                 &o_gen_lMinDeltaR,               "_gen_lMinDeltaR[_gen_nL]/D");
        tree->Branch("_gen_lPassParentage",             &o_gen_lPassParentage,           "_gen_lPassParentage[_gen_nL]/O");
    }


    tree->Branch("_passMETFilters", &o_passMETFilters, "_passMETFilters/O");
    tree->Branch("_Flag_goodVertices", &o_Flag_goodVertices, "_Flag_goodVertices/O");
    tree->Branch("_Flag_HBHENoiseFilter", &o_Flag_HBHENoiseFilter, "_Flag_HBHENoiseFilter/O");
    tree->Branch("_Flag_HBHENoiseIsoFilter", &o_Flag_HBHENoiseIsoFilter, "_Flag_HBHENoiseIsoFilter/O");
    tree->Branch("_Flag_EcalDeadCellTriggerPrimitiveFilter", &o_Flag_EcalDeadCellTriggerPrimitiveFilter, "_Flag_EcalDeadCellTriggerPrimitiveFilter/O");
    tree->Branch("_Flag_BadPFMuonFilter", &o_Flag_BadPFMuonFilter, "_Flag_BadPFMuonFilter/O");
    tree->Branch("_Flag_BadChargedCandidateFilter", &o_Flag_BadChargedCandidateFilter, "_Flag_BadChargedCandidateFilter/O");
    tree->Branch("_Flag_globalSuperTightHalo2016Filter", &o_Flag_globalSuperTightHalo2016Filter, "_Flag_globalSuperTightHalo2016Filter/O");
    tree->Branch("_updated_ecalBadCalibFilter", &o_updated_ecalBadCalibFilter, "_updated_ecalBadCalibFilter/O");
    tree->Branch("_passTrigger_FR", &o_passTrigger_FR, "_passTrigger_FR/O");
    tree->Branch("_passTrigger_e", &o_passTrigger_e, "_passTrigger_e/O");
    tree->Branch("_passTrigger_ee", &o_passTrigger_ee, "_passTrigger_ee/O");
    tree->Branch("_passTrigger_eee", &o_passTrigger_eee, "_passTrigger_eee/O");
    tree->Branch("_passTrigger_eem", &o_passTrigger_eem, "_passTrigger_eem/O");
    tree->Branch("_passTrigger_em", &o_passTrigger_em, "_passTrigger_em/O");
    tree->Branch("_passTrigger_emm", &o_passTrigger_emm, "_passTrigger_emm/O");
    tree->Branch("_passTrigger_et", &o_passTrigger_et, "_passTrigger_et/O");
    tree->Branch("_passTrigger_m", &o_passTrigger_m, "_passTrigger_m/O");
    tree->Branch("_passTrigger_mm", &o_passTrigger_mm, "_passTrigger_mm/O");
    tree->Branch("_passTrigger_mmm", &o_passTrigger_mmm, "_passTrigger_mmm/O");
    tree->Branch("_passTrigger_mt", &o_passTrigger_mt, "_passTrigger_mt/O");
    tree->Branch("_passTrigger_ref", &o_passTrigger_ref, "_passTrigger_ref/O");
    tree->Branch("_nL",                                 &o_nL,                                   "_nL/i");
    tree->Branch("_nMu",                                &o_nMu,                                  "_nMu/i");
    tree->Branch("_nEle",                               &o_nEle,                                 "_nEle/i");
    tree->Branch("_nLight",                             &o_nLight,                               "_nLight/i");
    tree->Branch("_nTau",                               &o_nTau,                                 "_nTau/i");
    tree->Branch("_lPt",                                &o_lPt,                                  "_lPt[_nL]/D");
    tree->Branch("_lEta",                               &o_lEta,                                 "_lEta[_nL]/D");
    tree->Branch("_lEtaSC",                             &o_lEtaSC,                               "_lEtaSC[_nLight]/D");
    tree->Branch("_lPhi",                               &o_lPhi,                                 "_lPhi[_nL]/D");
    tree->Branch("_lE",                                 &o_lE,                                   "_lE[_nL]/D");
    tree->Branch("_lFlavor",                            &o_lFlavor,                              "_lFlavor[_nL]/i");
    tree->Branch("_lCharge",                            &o_lCharge,                              "_lCharge[_nL]/I");
    tree->Branch("_dxy",                                &o_dxy,                                  "_dxy[_nL]/D");
    tree->Branch("_dz",                                 &o_dz,                                   "_dz[_nL]/D");
    tree->Branch("_3dIP",                               &o_3dIP,                                 "_3dIP[_nL]/D");
    tree->Branch("_3dIPSig",                            &o_3dIPSig,                              "_3dIPSig[_nL]/D");
    tree->Branch("_lElectronSummer16MvaGP",             &o_lElectronSummer16MvaGP,               "_lElectronSummer16MvaGP[_nLight]/F");
    tree->Branch("_lElectronSummer16MvaHZZ",            &o_lElectronSummer16MvaHZZ,              "_lElectronSummer16MvaHZZ[_nLight]/F");
    tree->Branch("_lElectronMvaFall17v1NoIso",          &o_lElectronMvaFall17v1NoIso,            "_lElectronMvaFall17v1NoIso[_nLight]/F");
    tree->Branch("_lElectronMvaFall17Iso",              &o_lElectronMvaFall17Iso,                "_lElectronMvaFall17Iso[_nLight]/F");
    tree->Branch("_lElectronMvaFall17NoIso",            &o_lElectronMvaFall17NoIso,              "_lElectronMvaFall17NoIso[_nLight]/F");
    tree->Branch("_lElectronPassEmu",                   &o_lElectronPassEmu,                     "_lElectronPassEmu[_nLight]/O");
    tree->Branch("_lElectronPassConvVeto",              &o_lElectronPassConvVeto,                "_lElectronPassConvVeto[_nLight]/O");
    tree->Branch("_lElectronChargeConst",               &o_lElectronChargeConst,                 "_lElectronChargeConst[_nLight]/O");
    tree->Branch("_lElectronMissingHits",               &o_lElectronMissingHits,                 "_lElectronMissingHits[_nLight]/i");
    tree->Branch("_leptonMvaSUSY",                      &o_leptonMvaSUSY,                        "_leptonMvaSUSY[_nLight]/D");
    tree->Branch("_leptonMvaTTH",                       &o_leptonMvaTTH,                         "_leptonMvaTTH[_nLight]/D");
    tree->Branch("_leptonMvatZq",                       &o_leptonMvatZq,                         "_leptonMvatZq[_nLight]/D");
    tree->Branch("_lEwkLoose",                          &o_lEwkLoose,                            "_lEwkLoose[_nL]/O");
    tree->Branch("_lEwkFO",                             &o_lEwkFO,                               "_lEwkFO[_nL]/O");
    tree->Branch("_lEwkTight",                          &o_lEwkTight,                            "_lEwkTight[_nL]/O");
    tree->Branch("_lPOGVeto",                           &o_lPOGVeto,                             "_lPOGVeto[_nL]/O");
    tree->Branch("_lPOGLoose",                          &o_lPOGLoose,                            "_lPOGLoose[_nL]/O");
    tree->Branch("_lPOGMedium",                         &o_lPOGMedium,                           "_lPOGMedium[_nL]/O");
    tree->Branch("_lPOGTight",                          &o_lPOGTight,                            "_lPOGTight[_nL]/O");
    tree->Branch("_tauMuonVetoLoose",                   &o_tauMuonVetoLoose,                     "_tauMuonVetoLoose[_nL]/O");
    tree->Branch("_tauEleVetoLoose",                    &o_tauEleVetoLoose,                      "_tauEleVetoLoose[_nL]/O");
    tree->Branch("_decayModeFinding",                   &o_decayModeFinding,                     "_decayModeFinding[_nL]/O");
    tree->Branch("_tauAgainstElectronMVA6Raw",          &o_tauAgainstElectronMVA6Raw,            "_tauAgainstElectronMVA6Raw[_nL]/D");
    tree->Branch("_tauCombinedIsoDBRaw3Hits",           &o_tauCombinedIsoDBRaw3Hits,             "_tauCombinedIsoDBRaw3Hits[_nL]/D");
    tree->Branch("_tauIsoMVAPWdR03oldDMwLT",            &o_tauIsoMVAPWdR03oldDMwLT,              "_tauIsoMVAPWdR03oldDMwLT[_nL]/D");
    tree->Branch("_tauIsoMVADBdR03oldDMwLT",            &o_tauIsoMVADBdR03oldDMwLT,              "_tauIsoMVADBdR03oldDMwLT[_nL]/D");
    tree->Branch("_tauIsoMVADBdR03newDMwLT",            &o_tauIsoMVADBdR03newDMwLT,              "_tauIsoMVADBdR03newDMwLT[_nL]/D");
    tree->Branch("_tauIsoMVAPWnewDMwLT",                &o_tauIsoMVAPWnewDMwLT,                  "_tauIsoMVAPWnewDMwLT[_nL]/D");
    tree->Branch("_tauIsoMVAPWoldDMwLT",                &o_tauIsoMVAPWoldDMwLT,                  "_tauIsoMVAPWoldDMwLT[_nL]/D");
    tree->Branch("_relIso",                             &o_relIso,                               "_relIso[_nLight]/D");
    tree->Branch("_relIso0p4",                          &o_relIso0p4,                            "_relIso0p4[_nLight]/D");
    tree->Branch("_relIso0p4MuDeltaBeta",               &o_relIso0p4MuDeltaBeta,                 "_relIso0p4MuDeltaBeta[_nMu]/D");
    tree->Branch("_miniIso",                            &o_miniIso,                              "_miniIso[_nLight]/D");
    tree->Branch("_miniIsoCharged",                     &o_miniIsoCharged,                       "_miniIsoCharged[_nLight]/D");
    tree->Branch("_ptRel",                              &o_ptRel,                                "_ptRel[_nLight]/D");
    tree->Branch("_ptRatio",                            &o_ptRatio,                              "_ptRatio[_nLight]/D");
    tree->Branch("_closestJetCsvV2",                    &o_closestJetCsvV2,                      "_closestJetCsvV2[_nLight]/D");
    tree->Branch("_closestJetDeepCsv_b",                &o_closestJetDeepCsv_b,                  "_closestJetDeepCsv_b[_nLight]/D");
    tree->Branch("_closestJetDeepCsv_bb",               &o_closestJetDeepCsv_bb,                 "_closestJetDeepCsv_bb[_nLight]/D");
    tree->Branch("_closestJetDeepCsv",                  &o_closestJetDeepCsv,                    "_closestJetDeepCsv[_nLight]/D");
    tree->Branch("_selectedTrackMult",                  &o_selectedTrackMult,                    "_selectedTrackMult[_nLight]/i");
    tree->Branch("_lMuonSegComp",                       &o_lMuonSegComp,                         "_lMuonSegComp[_nMu]/D");
    tree->Branch("_lMuonTrackPt",                       &o_lMuonTrackPt,                         "_lMuonTrackPt[_nMu]/D");
    tree->Branch("_lMuonTrackPtErr",                    &o_lMuonTrackPtErr,                      "_lMuonTrackPtErr[_nMu]/D");
    if( !isData ){
        tree->Branch("_lIsPrompt",                        &o_lIsPrompt,                            "_lIsPrompt[_nL]/O");
        tree->Branch("_lMatchPdgId",                      &o_lMatchPdgId,                          "_lMatchPdgId[_nL]/I");
        tree->Branch("_lMatchCharge",                     &o_lMatchCharge,                         "_lMatchCharge[_nL]/I");
        tree->Branch("_tauGenStatus",                     &o_tauGenStatus,                         "_tauGenStatus[_nL]/i");
        tree->Branch("_lMomPdgId",                        &o_lMomPdgId,                            "_lMomPdgId[_nL]/I");
        tree->Branch("_lProvenance",                      &o_lProvenance,                          "_lProvenance[_nL]/i");
        tree->Branch("_lProvenanceCompressed",            &o_lProvenanceCompressed,                "_lProvenanceCompressed[_nL]/i");
        tree->Branch("_lProvenanceConversion",            &o_lProvenanceConversion,                "_lProvenanceConversion[_nL]/i");
    }
    tree->Branch("_lPtCorr",                            &o_lPtCorr,                              "_lPtCorr[_nLight]/D");
    tree->Branch("_lPtScaleUp",                         &o_lPtScaleUp,                           "_lPtScaleUp[_nLight]/D");
    tree->Branch("_lPtScaleDown",                       &o_lPtScaleDown,                         "_lPtScaleDown[_nLight]/D");
    tree->Branch("_lPtResUp",                           &o_lPtResUp,                             "_lPtResUp[_nLight]/D");
    tree->Branch("_lPtResDown",                         &o_lPtResDown,                           "_lPtResDown[_nLight]/D");

    tree->Branch("_nJets",                              &o_nJets,                                "_nJets/i");
    tree->Branch("_jetPt",                              &o_jetPt,                                "_jetPt[_nJets]/D");
    tree->Branch("_jetPt_JECDown",                      &o_jetPt_JECDown,                        "_jetPt_JECDown[_nJets]/D");
    tree->Branch("_jetPt_JECUp",                        &o_jetPt_JECUp,                          "_jetPt_JECUp[_nJets]/D");
    tree->Branch("_jetSmearedPt",                       &o_jetSmearedPt,                         "_jetSmearedPt[_nJets]/D");
    tree->Branch("_jetSmearedPt_JECDown",               &o_jetSmearedPt_JECDown,                 "_jetSmearedPt_JECDown[_nJets]/D");
    tree->Branch("_jetSmearedPt_JECUp",                 &o_jetSmearedPt_JECUp,                   "_jetSmearedPt_JECUp[_nJets]/D");
    tree->Branch("_jetSmearedPt_JERDown",               &o_jetSmearedPt_JERDown,                 "_jetSmearedPt_JERDown[_nJets]/D");
    tree->Branch("_jetSmearedPt_JERUp",                 &o_jetSmearedPt_JERUp,                   "_jetSmearedPt_JERUp[_nJets]/D");
    tree->Branch("_jetPt_Uncorrected",                  &o_jetPt_Uncorrected,                    "_jetPt_Uncorrected[_nJets]/D");
    tree->Branch("_jetPt_L1",                           &o_jetPt_L1,                             "_jetPt_L1[_nJets]/D");
    tree->Branch("_jetPt_L2",                           &o_jetPt_L2,                             "_jetPt_L2[_nJets]/D");
    tree->Branch("_jetPt_L3",                           &o_jetPt_L3,                             "_jetPt_L3[_nJets]/D");

    tree->Branch("_jetEta",                             &o_jetEta,                               "_jetEta[_nJets]/D");
    tree->Branch("_jetPhi",                             &o_jetPhi,                               "_jetPhi[_nJets]/D");
    tree->Branch("_jetE",                               &o_jetE,                                 "_jetE[_nJets]/D");
    tree->Branch("_jetCsvV2",                           &o_jetCsvV2,                             "_jetCsvV2[_nJets]/D");
    tree->Branch("_jetDeepCsv_udsg",                    &o_jetDeepCsv_udsg,                      "_jetDeepCsv_udsg[_nJets]/D");
    tree->Branch("_jetDeepCsv_b",                       &o_jetDeepCsv_b,                         "_jetDeepCsv_b[_nJets]/D");
    tree->Branch("_jetDeepCsv_c",                       &o_jetDeepCsv_c,                         "_jetDeepCsv_c[_nJets]/D");
    tree->Branch("_jetDeepCsv_bb",                      &o_jetDeepCsv_bb,                        "_jetDeepCsv_bb[_nJets]/D");
    tree->Branch("_jetDeepCsv",                         &o_jetDeepCsv,                           "_jetDeepCsv[_nJets]/D");
    tree->Branch("_jetHadronFlavor",                    &o_jetHadronFlavor,                      "_jetHadronFlavor[_nJets]/i");
    tree->Branch("_jetIsTight",                         &o_jetIsTight,                           "_jetIsTight[_nJets]/O");
    tree->Branch("_jetIsTightLepVeto",                  &o_jetIsTightLepVeto,                    "_jetIsTightLepVeto[_nJets]/O");

    tree->Branch("_jetNeutralHadronFraction",           &o_jetNeutralHadronFraction,             "_jetNeutralHadronFraction[_nJets]/D");
    tree->Branch("_jetChargedHadronFraction",           &o_jetChargedHadronFraction,             "_jetChargedHadronFraction[_nJets]/D");
    tree->Branch("_jetNeutralEmFraction",               &o_jetNeutralEmFraction,                 "_jetNeutralEmFraction[_nJets]/D");
    tree->Branch("_jetChargedEmFraction",               &o_jetChargedEmFraction,                 "_jetChargedEmFraction[_nJets]/D");
    tree->Branch("_jetHFHadronFraction",                &o_jetHFHadronFraction,                  "_jetHFHadronFraction[_nJets]/D");
    tree->Branch("_jetHFEmFraction",                    &o_jetHFEmFraction,                      "_jetHFEmFraction[_nJets]/D");

    tree->Branch("_met",                                &o_met,                                  "_met/D");
    tree->Branch("_metRaw",                             &o_metRaw,                               "_metRaw/D");
    tree->Branch("_metJECDown",                         &o_metJECDown,                           "_metJECDown/D");
    tree->Branch("_metJECUp",                           &o_metJECUp,                             "_metJECUp/D");
    tree->Branch("_metUnclDown",                        &o_metUnclDown,                          "_metUnclDown/D");
    tree->Branch("_metUnclUp",                          &o_metUnclUp,                            "_metUnclUp/D");

    tree->Branch("_metPhi",                             &o_metPhi,                               "_metPhi/D");
    tree->Branch("_metRawPhi",                          &o_metRawPhi,                            "_metRawPhi/D");
    tree->Branch("_metPhiJECDown",                      &o_metPhiJECDown,                        "_metPhiJECDown/D");
    tree->Branch("_metPhiJECUp",                        &o_metPhiJECUp,                          "_metPhiJECUp/D");
    tree->Branch("_metPhiUnclDown",                     &o_metPhiUnclDown,                       "_metPhiUnclDown/D");
    tree->Branch("_metPhiUnclUp",                       &o_metPhiUnclUp,                         "_metPhiUnclUp/D");
    tree->Branch("_metSignificance",                    &o_metSignificance,                      "_metSignificance/D");
}


Skimmer::Skimmer(TString inputfilename, TString outputfilename)
{
    input = new TFile(inputfilename, "open");
    inputtree = (TTree*)input->Get("blackJackAndHookers/blackJackAndHookersTree");
    Init_input_branches(inputtree);
    isData = (inputfilename.Index("Run20") != -1);
    if(isData) std::cout << "Data!" << std::endl;
    else std::cout << "MC!" << std::endl;

    std::shared_ptr< TH1D > nVertices( (TH1D*) input->Get( "blackJackAndHookers/nVertices" ) );
    std::shared_ptr< TH1D > hCounter;
    std::shared_ptr< TH1D > lheCounter;
    std::shared_ptr< TH1D > psCounter;
    std::shared_ptr< TH1D > tauCounter;
    std::shared_ptr< TH1D > nTrueInteractions;
    if( !isData ){
        hCounter = std::shared_ptr< TH1D >( (TH1D*) input->Get( "blackJackAndHookers/hCounter" ) );
        lheCounter = std::shared_ptr< TH1D >( (TH1D*) input->Get( "blackJackAndHookers/lheCounter" ) );
        psCounter = std::shared_ptr< TH1D >( (TH1D*) input->Get( "blackJackAndHookers/psCounter" ) );
        tauCounter = std::shared_ptr< TH1D >( (TH1D*) input->Get( "blackJackAndHookers/tauCounter" ) );
        nTrueInteractions = std::shared_ptr< TH1D >( (TH1D*) input->Get( "blackJackAndHookers/nTrueInteractions" ) );
    }

    output = new TFile(outputfilename, "recreate");
    output->mkdir("blackJackAndHookers");
    output->cd("blackJackAndHookers");

    nVertices->Write( "nVertices" );
    if( !isData ){
        hCounter->Write( "hCounter" );
        lheCounter->Write( "lheCounter" );
        psCounter->Write( "psCounter" );
        tauCounter->Write( "tauCounter" );
        nTrueInteractions->Write( "nTrueInteractions" );
    }
    outputtree = new TTree("blackJackAndHookersTree", "blackJackAndHookersTree");
    Add_branches(outputtree);
}


void Skimmer::Skim(TString skimcondition)
{
    Long64_t nentries = inputtree->GetEntries();
    for(Long64_t jentry = 0; jentry < nentries; ++jentry){
        inputtree->GetEntry(jentry);

        if(Check_SkimCondition(skimcondition)){
            o_runNb = i_runNb;
            o_lumiBlock = i_lumiBlock;
            o_eventNb = i_eventNb;
            o_nVertex = i_nVertex;
            //o_prefireWeight = i_prefireWeight;
            //o_prefireWeightUp = i_prefireWeightUp;
            //o_prefireWeightDown = i_prefireWeightDown;
            o_nTrueInt = i_nTrueInt;
            o_weight   = i_weight;
            o_lheHTIncoming = i_lheHTIncoming;
            o_ctauHN = i_ctauHN;
            o_nLheTau = i_nLheTau;
            o_nLheWeights = i_nLheWeights;
            for(unsigned i = 0; i < i_nLheWeights; i++) o_lheWeight[i] = i_lheWeight[i];
            o_nPsWeights = i_nPsWeights;
            for(unsigned i = 0; i < i_nPsWeights; i++) o_psWeight[i] = i_psWeight[i];
            o_ttgEventType = i_ttgEventType;
            o_zgEventType  = i_zgEventType;
            o_gen_met      = i_gen_met;
            o_gen_metPhi   = i_gen_metPhi;
            o_gen_nPh      = i_gen_nPh;
            for(unsigned i = 0; i < i_gen_nPh; i++){
                o_gen_phStatus[i] = i_gen_phStatus[i];
                o_gen_phPt[i] = i_gen_phPt[i];   
                o_gen_phEta[i] = i_gen_phEta[i];   
                o_gen_phPhi[i] = i_gen_phPhi[i];   
                o_gen_phE[i] = i_gen_phE[i];   
                o_gen_phMomPdg[i] = i_gen_phMomPdg[i];   
                o_gen_phIsPrompt[i] = i_gen_phIsPrompt[i];   
                o_gen_phMinDeltaR[i] = i_gen_phMinDeltaR[i];   
                o_gen_phPassParentage[i] = i_gen_phPassParentage[i];   
            }
            o_gen_nL = i_gen_nL;
            for(unsigned i = 0; i < i_gen_nL; i++){
                o_gen_lPt[i] = i_gen_lPt[i];   
                o_gen_lEta[i] = i_gen_lEta[i];   
                o_gen_lPhi[i] = i_gen_lPhi[i];   
                o_gen_lE[i] = i_gen_lE[i];   
                o_gen_lFlavor[i] = i_gen_lFlavor[i];   
                o_gen_lCharge[i] = i_gen_lCharge[i];   
                o_gen_lMomPdg[i] = i_gen_lMomPdg[i];   
                o_gen_lIsPrompt[i] = i_gen_lIsPrompt[i];   
                o_gen_lDecayedHadr[i] = i_gen_lDecayedHadr[i];
                o_gen_lMinDeltaR[i] = i_gen_lMinDeltaR[i];   
                o_gen_lPassParentage[i] = i_gen_lPassParentage[i];   
            }
            o_passMETFilters = i_passMETFilters;
            o_Flag_goodVertices = i_Flag_goodVertices;
            o_Flag_HBHENoiseFilter = i_Flag_HBHENoiseFilter;
            o_Flag_HBHENoiseIsoFilter = i_Flag_HBHENoiseIsoFilter;
            o_Flag_EcalDeadCellTriggerPrimitiveFilter = i_Flag_EcalDeadCellTriggerPrimitiveFilter;
            o_Flag_BadPFMuonFilter = i_Flag_BadPFMuonFilter;
            o_Flag_BadChargedCandidateFilter = i_Flag_BadChargedCandidateFilter;
            o_Flag_globalSuperTightHalo2016Filter = i_Flag_globalSuperTightHalo2016Filter;
            o_updated_ecalBadCalibFilter = i_updated_ecalBadCalibFilter;
            o_passTrigger_FR = i_passTrigger_FR;
            o_passTrigger_e = i_passTrigger_e;
            o_passTrigger_ee = i_passTrigger_ee;
            o_passTrigger_eee = i_passTrigger_eee;
            o_passTrigger_eem = i_passTrigger_eem;
            o_passTrigger_em = i_passTrigger_em;
            o_passTrigger_emm = i_passTrigger_emm;
            o_passTrigger_et = i_passTrigger_et;
            o_passTrigger_m = i_passTrigger_m;
            o_passTrigger_mm = i_passTrigger_mm;
            o_passTrigger_mmm = i_passTrigger_mmm;
            o_passTrigger_mt = i_passTrigger_mt;
            o_passTrigger_ref = i_passTrigger_ref;                       
            o_nL = i_nL;
            o_nMu = i_nMu;
            o_nEle = i_nEle;
            o_nLight = i_nLight;
            o_nTau = i_nTau;
            for(unsigned i = 0; i < i_nL; i++){
                o_lPt[i] = i_lPt[i];   
                o_lEta[i] = i_lEta[i];   
                o_lPhi[i] = i_lPhi[i];   
                o_lE[i] = i_lE[i];   
                o_lFlavor[i] = i_lFlavor[i];   
                o_lCharge[i] = i_lCharge[i];   
                o_dxy[i] = i_dxy[i];   
                o_dz[i] = i_dz[i];   
                o_3dIP[i] = i_3dIP[i];   
                o_3dIPSig[i] = i_3dIPSig[i];   
                o_lElectronPassEmu[i] = i_lElectronPassEmu[i];
                o_lElectronPassConvVeto[i] = i_lElectronPassConvVeto[i];
                o_lElectronChargeConst[i] = i_lElectronChargeConst[i];   
                o_lElectronMissingHits[i] = i_lElectronMissingHits[i];
                o_lEwkLoose[i] = i_lEwkLoose[i];   
                o_lEwkFO[i] = i_lEwkFO[i];   
                o_lEwkTight[i] = i_lEwkTight[i];   
                o_lPOGVeto[i] = i_lPOGVeto[i];   
                o_lPOGLoose[i] = i_lPOGLoose[i];   
                o_lPOGMedium[i] = i_lPOGMedium[i];   
                o_lPOGTight[i] = i_lPOGTight[i];   
                o_tauMuonVetoLoose[i] = i_tauMuonVetoLoose[i];
                o_tauEleVetoLoose[i] = i_tauEleVetoLoose[i];
                o_decayModeFinding[i] = i_decayModeFinding[i];
                o_tauAgainstElectronMVA6Raw[i] = i_tauAgainstElectronMVA6Raw[i];
                o_tauCombinedIsoDBRaw3Hits[i] = i_tauCombinedIsoDBRaw3Hits[i];
                o_tauIsoMVAPWdR03oldDMwLT[i] = i_tauIsoMVAPWdR03oldDMwLT[i];
                o_tauIsoMVADBdR03oldDMwLT[i] = i_tauIsoMVADBdR03oldDMwLT[i];
                o_tauIsoMVADBdR03newDMwLT[i] = i_tauIsoMVADBdR03newDMwLT[i];
                o_tauIsoMVAPWnewDMwLT[i] = i_tauIsoMVAPWnewDMwLT[i];
                o_tauIsoMVAPWoldDMwLT[i] = i_tauIsoMVAPWoldDMwLT[i];
                o_lIsPrompt[i] = i_lIsPrompt[i];   
                o_lMatchPdgId[i] = i_lMatchPdgId[i];   
                o_lMatchCharge[i] = i_lMatchCharge[i];   
                o_tauGenStatus[i] = i_tauGenStatus[i];   
                o_lMomPdgId[i] = i_lMomPdgId[i];   
                o_lProvenance[i] = i_lProvenance[i];   
                o_lProvenanceCompressed[i] = i_lProvenanceCompressed[i];   
                o_lProvenanceConversion[i] = i_lProvenanceConversion[i];   
                o_lPtCorr[i] = i_lPtCorr[i];   
                o_lPtScaleUp[i] = i_lPtScaleUp[i];   
                o_lPtScaleDown[i] = i_lPtScaleDown[i];   
                o_lPtResUp[i] = i_lPtResUp[i];   
                o_lPtResDown[i] = i_lPtResDown[i];   
            }
            for(unsigned i = 0; i < i_nLight; i++){
                o_lEtaSC[i] = i_lEtaSC[i];   
                o_lElectronSummer16MvaGP[i] = i_lElectronSummer16MvaGP[i];
                o_lElectronSummer16MvaHZZ[i] = i_lElectronSummer16MvaHZZ[i];
                o_lElectronMvaFall17v1NoIso[i] = i_lElectronMvaFall17v1NoIso[i];
                o_lElectronMvaFall17Iso[i] = i_lElectronMvaFall17Iso[i];
                o_lElectronMvaFall17NoIso[i] = i_lElectronMvaFall17NoIso[i];
                o_lElectronPassEmu[i] = i_lElectronPassEmu[i];   
                o_lElectronPassConvVeto[i] = i_lElectronPassConvVeto[i];   
                o_lElectronChargeConst[i] = i_lElectronChargeConst[i];   
                o_lElectronMissingHits[i] = i_lElectronMissingHits[i];   
                o_leptonMvaSUSY[i] = i_leptonMvaSUSY[i];
                o_leptonMvaTTH[i] = i_leptonMvaTTH[i];
                o_leptonMvatZq[i] = i_leptonMvatZq[i];
                o_relIso[i] = i_relIso[i];   
                o_relIso0p4[i] = i_relIso0p4[i];   
                o_relIso0p4MuDeltaBeta[i] = i_relIso0p4MuDeltaBeta[i];   
                o_miniIso[i] = i_miniIso[i];   
                o_miniIsoCharged[i] = i_miniIsoCharged[i];   
                o_ptRel[i] = i_ptRel[i];   
                o_ptRatio[i] = i_ptRatio[i];   
                o_closestJetCsvV2[i] = i_closestJetCsvV2[i];   
                o_closestJetDeepCsv_b[i] = i_closestJetDeepCsv_b[i];   
                o_closestJetDeepCsv_bb[i] = i_closestJetDeepCsv_bb[i];   
                o_closestJetDeepCsv[i] = i_closestJetDeepCsv[i];   
                o_selectedTrackMult[i] = i_selectedTrackMult[i];   
            }
            for(unsigned i = 0; i < i_nMu; i++){
                o_lMuonSegComp[i] = i_lMuonSegComp[i];   
                o_lMuonTrackPt[i] = i_lMuonTrackPt[i];   
                o_lMuonTrackPtErr[i] = i_lMuonTrackPtErr[i];   
            }
            o_nPh = i_nPh;
            for(unsigned i = 0; i < i_nPh; i++){
                o_phPt[i] = i_phPt[i];   
                o_phEta[i] = i_phEta[i];   
                o_phEtaSC[i] = i_phEtaSC[i];   
                o_phPhi[i] = i_phPhi[i];   
                o_phE[i] = i_phE[i];   
                o_phCutBasedLoose[i] = i_phCutBasedLoose[i];   
                o_phCutBasedMedium[i] = i_phCutBasedMedium[i];   
                o_phCutBasedTight[i] = i_phCutBasedTight[i];   
                o_phMva[i] = i_phMva[i];   
                o_phRandomConeChargedIsolation[i] = i_phRandomConeChargedIsolation[i];   
                o_phChargedIsolation[i] = i_phChargedIsolation[i];   
                o_phNeutralHadronIsolation[i] = i_phNeutralHadronIsolation[i];   
                o_phPhotonIsolation[i] = i_phPhotonIsolation[i];   
                o_phSigmaIetaIeta[i] = i_phSigmaIetaIeta[i];   
                o_phHadronicOverEm[i] = i_phHadronicOverEm[i];   
                o_phHadTowOverEm[i] = i_phHadTowOverEm[i];
                o_phPassElectronVeto[i] = i_phPassElectronVeto[i];   
                o_phHasPixelSeed[i] = i_phHasPixelSeed[i];   
                o_phIsPrompt[i] = i_phIsPrompt[i];   
                o_phMatchPdgId[i] = i_phMatchPdgId[i];   
                o_phPtCorr[i] = i_phPtCorr[i];   
                o_phPtScaleUp[i] = i_phPtScaleUp[i];   
                o_phPtScaleDown[i] = i_phPtScaleDown[i];   
                o_phPtResUp[i] = i_phPtResUp[i];   
                o_phPtResDown[i] = i_phPtResDown[i];   
            }
            o_nJets = i_nJets;
            for(unsigned i = 0; i < i_nJets; i++){
                o_jetPt[i] = i_jetPt[i];   
                o_jetPt_JECUp[i] = i_jetPt_JECUp[i];   
                o_jetPt_JECDown[i] = i_jetPt_JECDown[i];   
                o_jetPt_Uncorrected[i] = i_jetPt_Uncorrected[i];   
                o_jetPt_L1[i] = i_jetPt_L1[i];   
                o_jetPt_L2[i] = i_jetPt_L2[i];   
                o_jetPt_L3[i] = i_jetPt_L3[i];   
                o_jetEta[i] = i_jetEta[i];   
                o_jetPhi[i] = i_jetPhi[i];   
                o_jetE[i] = i_jetE[i];   
                o_jetCsvV2[i] = i_jetCsvV2[i];   
                o_jetDeepCsv_udsg[i] = i_jetDeepCsv_udsg[i];   
                o_jetDeepCsv_b[i] = i_jetDeepCsv_b[i];   
                o_jetDeepCsv_c[i] = i_jetDeepCsv_c[i];   
                o_jetDeepCsv_bb[i] = i_jetDeepCsv_bb[i];   
                o_jetDeepCsv[i] = i_jetDeepCsv[i];   
                o_jetHadronFlavor[i] = i_jetHadronFlavor[i];   
                o_jetIsTight[i] = i_jetIsTight[i];   
                o_jetIsTightLepVeto[i] = i_jetIsTightLepVeto[i];   
                o_jetNeutralHadronFraction[i] = i_jetNeutralHadronFraction[i];
                o_jetChargedHadronFraction[i] = i_jetChargedHadronFraction[i];
                o_jetNeutralEmFraction[i] = i_jetNeutralEmFraction[i];
                o_jetChargedEmFraction[i] = i_jetChargedEmFraction[i];
                o_jetHFHadronFraction[i] = i_jetHFHadronFraction[i];
                o_jetHFEmFraction[i] = i_jetHFEmFraction[i];
            }
            o_met = i_met;
            o_metRaw = i_metRaw;
            o_metJECDown = i_metJECDown;
            o_metJECUp = i_metJECUp;
            o_metUnclDown = i_metUnclDown;
            o_metUnclUp = i_metUnclUp;
            o_metPhi = i_metPhi;
            o_metRawPhi = i_metRawPhi;
            o_metPhiJECDown = i_metPhiJECDown;
            o_metPhiJECUp = i_metPhiJECUp;
            o_metPhiUnclDown = i_metPhiUnclDown;
            o_metPhiUnclUp = i_metPhiUnclUp;
            o_metSignificance = i_metSignificance;
            outputtree->Fill();
        }
    }
}


Skimmer::~Skimmer()
{
    output->Write();
    output->Close();
}
