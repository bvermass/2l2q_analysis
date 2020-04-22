//implementation of LeptonMvaHelper class
#include "LeptonMvaHelper.h"
#include <cmath>

// TODO: clean-up of this class, maybe get rid of older trainings

//Default constructor
//This will set up both MVA readers and book the correct variables
LeptonMvaHelper::LeptonMvaHelper(const std::string taggerName, const TString yearTrain):
    tagger( taggerName ), year( yearTrain )
{
    for(unsigned i = 0; i < 2; ++i){

        //Set up Mva reader 
        reader[i] = std::make_shared<TMVA::Reader>( "!Color:!Silent");
    }

    //TOP lepton MVA
    if( tagger == "TOP" ) {
        for(unsigned i = 0; i < 2; ++i){
	    reader[i]->AddVariable( "dxylog", &LepGood_dxy);
	    reader[i]->AddVariable( "miniIsoCharged", &LepGood_miniRelIsoCharged );
	    reader[i]->AddVariable( "miniIsoNeutral", &LepGood_miniRelIsoNeutral );
	    reader[i]->AddVariable( "pTRel", &LepGood_jetPtRelv2 );
	    reader[i]->AddVariable( "sip3d", &LepGood_sip3d );
	}
        reader[0]->AddVariable("segmentCompatibility", &LepGood_segmentCompatibility);
        reader[1]->AddVariable("mvaIdFall17v2noIso", &LepGood_mvaIdFall17v2noIso);
        for(unsigned i = 0; i < 2; ++i){
	    reader[i]->AddVariable( "ptRatio", &LepGood_jetPtRatio );
	    reader[i]->AddVariable( "bTagDeepJetClosestJet", &LepGood_jetBTag );
            reader[i]->AddVariable( "pt", &LepGood_pt );
	    reader[i]->AddVariable( "trackMultClosestJet", &LepGood_jetNDauChargedMVASel );
            reader[i]->AddVariable( "etaAbs", &LepGood_eta );
	    reader[i]->AddVariable( "dzlog", &LepGood_dz);
            reader[i]->AddVariable( "relIso", &LepGood_relIso0p3); 
	}       
        reader[0]->BookMVA("BDTG method", "/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_14/src/2l2q_analysis/data/TopLeptonMvaWeights/TMVA_BDTG_TOP_muon_" + year + (TString)".weights.xml");
        reader[1]->BookMVA("BDTG method", "/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_14/src/2l2q_analysis/data/TopLeptonMvaWeights/TMVA_BDTG_TOP_elec_" + year + (TString)".weights.xml");
    }
}


void LeptonMvaHelper::bookCommonVars(double pt, double eta, double selectedTrackMult, double miniIsoCharged, double miniIsoNeutral, double ptRel, double ptRatio,
        double closestJetDeepCsv, double closestJetDeepFlavor, double sip3d, double dxy, double dz, double relIso0p3 )
{
    LepGood_pt = pt;
    if( tagger == "TTH" ){
        LepGood_eta = eta;
    } else {
        LepGood_eta = fabs(eta);
    }
    LepGood_jetNDauChargedMVASel = selectedTrackMult;
    LepGood_miniRelIsoCharged = miniIsoCharged;
    LepGood_miniRelIsoNeutral = miniIsoNeutral;
    LepGood_jetPtRelv2 = ptRel;
    LepGood_jetPtRatio = std::min(ptRatio, 1.5);
    if( tagger != "TZQ" ){
        LepGood_jetBTag = std::max( ( std::isnan( closestJetDeepFlavor ) ? 0. : closestJetDeepFlavor ), 0. );
    } else {
        LepGood_jetBTag = std::max( ( std::isnan( closestJetDeepCsv ) ? 0. : closestJetDeepCsv ), 0. );
    }
    LepGood_sip3d = sip3d;
    LepGood_dxy = log(fabs(dxy));
    LepGood_dz = log(fabs(dz));
    LepGood_relIso0p3 = relIso0p3;
}

double LeptonMvaHelper::leptonMvaMuon(double pt, double eta, double selectedTrackMult, double miniIsoCharged, double miniIsoNeutral, double ptRel, double ptRatio, 
    double closestJetDeepCsv, double closestJetDeepFlavor, double sip3d, double dxy, double dz, double relIso0p3, double relIso0p3DB, double segComp)
{
    bookCommonVars(pt, eta, selectedTrackMult, miniIsoCharged, miniIsoNeutral, ptRel, ptRatio, closestJetDeepCsv, closestJetDeepFlavor, sip3d, dxy, dz, relIso0p3);
    if( tagger == "TOP" ) LepGood_relIso0p3 = relIso0p3DB;
    LepGood_segmentCompatibility = segComp;  
    return reader[0]->EvaluateMVA("BDTG method");
}

double LeptonMvaHelper::leptonMvaElectron(double pt, double eta, double selectedTrackMult, double miniIsoCharged, double miniIsoNeutral, double ptRel, double ptRatio, 
    double closestJetDeepCsv, double closestJetDeepFlavor, double sip3d, double dxy, double dz, double relIso0p3, double eleMvaSummer16, double eleMvaFall17v1, double eleMvaFall17v2)
{
    bookCommonVars(pt, eta, selectedTrackMult, miniIsoCharged, miniIsoNeutral, ptRel, ptRatio, closestJetDeepCsv, closestJetDeepFlavor, sip3d, dxy, dz, relIso0p3);
    LepGood_mvaIdSummer16GP = eleMvaSummer16;
    LepGood_mvaIdFall17v1noIso = eleMvaFall17v1;
    LepGood_mvaIdFall17v2noIso = eleMvaFall17v2;
    return reader[1]->EvaluateMVA("BDTG method");
}
