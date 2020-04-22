//Helper class for facilitating the computation of the lepton MVA.
#ifndef Lepton_Mva_Helper
#define Lepton_Mva_Helper

#include "TMVA/Reader.h"
#include <memory>
#include <TString.h>

class LeptonMvaHelper{
    public:
        LeptonMvaHelper(const std::string tagger, const TString year);
        double leptonMvaMuon(double pt, double eta, double selectedTrackMult, double miniIsoCharged, double miniIsoNeutral, double ptRel, double ptRatio, double closestJetDeepCsv, double closestJetDeepFlavor, double sip3d, double dxy, double dz, double relIso0p3, double relIso0p3DB, double segComp);
        double leptonMvaElectron(double pt, double eta, double selectedTrackMult, double miniIsoCharged, double miniIsoNeutral, double ptRel, double ptRatio, double closestJetDeepCsv, double closesJetDeepFlavor, double sip3d, double dxy, double dz, double relIso0p3, double eleMvaSummer16, double eleMvaFall17v1, double eleMvaFall17v2);
    private:
        std::string tagger;
        TString year;
        std::shared_ptr<TMVA::Reader> reader[2]; //First entry is for muons, second one for electrons
        float LepGood_pt,                       //Variables used in MVA computation
        LepGood_eta,
        LepGood_jetNDauChargedMVASel,
        LepGood_miniRelIsoCharged,
        LepGood_miniRelIsoNeutral,
        LepGood_jetPtRelv2,
        LepGood_jetPtRatio,
        LepGood_jetBTag,
        LepGood_sip3d,
        LepGood_dxy,
        LepGood_dz,
        LepGood_segmentCompatibility,
        LepGood_mvaIdSummer16GP,
        LepGood_mvaIdFall17v1noIso,
        LepGood_mvaIdFall17v2noIso,
        LepGood_relIso0p3;
        void bookCommonVars(double pt, double eta, double selectedTrackMult, double miniIsoCharged, double miniIsoNeutral, double ptRel, double ptRatio, double closestJetDeepCsv, double closestJetDeepFlavor, double sip3d, double dxy, double dz, double relIso0p3);
};
#endif
