////////////////////////////////////////////////////////////////////////////
//Produces HNL tagger tree for neural network, part of class full_analyzer//
////////////////////////////////////////////////////////////////////////////

//Include header for the class
#include "../interface/HNLtagger.h"

HNLtagger::HNLtagger(TString filename, int partition, int partitionjobnumber)
{
    TString HNLtagger_filename = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/trees/HNLtagger/", "HNLtagger", partition, partitionjobnumber);
    HNLtagger_file = new TFile(HNLtagger_filename, "recreate");
    HNLtagger_tree = new TTree("HNLtagger_tree", "Jetl2 constituent information for HNL tagger");
    HNLtagger_tree->Branch("_nJetConstituents",                 &_nJetConstituents,                 "_nJetConstituents/i");
    //HNLtagger_tree->Branch("_JetConstituentPt",                 &_JetConstituentPt,                 "_JetConstituentPt[_nJetConstituents]/D");
    //HNLtagger_tree->Branch("_JetConstituentEta",                &_JetConstituentEta,                "_JetConstituentEta[_nJetConstituents]/D");
    //HNLtagger_tree->Branch("_JetConstituentPhi",                &_JetConstituentPhi,                "_JetConstituentPhi[_nJetConstituents]/D");
    //HNLtagger_tree->Branch("_JetConstituentMass",               &_JetConstituentMass,               "_JetConstituentMass[_nJetConstituents]/D");
    //HNLtagger_tree->Branch("_JetConstituentPdgId",              &_JetConstituentPdgId,              "_JetConstituentPdgId[_nJetConstituents]/I");
    //HNLtagger_tree->Branch("_JetConstituentCharge",             &_JetConstituentCharge,             "_JetConstituentCharge[_nJetConstituents]/I");
    //HNLtagger_tree->Branch("_JetConstituentdxySig",             &_JetConstituentdxySig,             "_JetConstituentdxySig[_nJetConstituents]/D");
    //HNLtagger_tree->Branch("_JetConstituentdzSig",              &_JetConstituentdzSig,              "_JetConstituentdzSig[_nJetConstituents]/D");
    //HNLtagger_tree->Branch("_JetConstituentsNumberOfHits",      &_JetConstituentsNumberOfHits,      "_JetConstituentsNumberOfHits[_nJetConstituents]/I");
    //HNLtagger_tree->Branch("_JetConstituentsNumberOfPixelHits", &_JetConstituentsNumberOfPixelHits, "_JetConstituentsNumberOfPixelHits[_nJetConstituents]/I");
    //HNLtagger_tree->Branch("_JetConstituentsHasTrack",          &_JetConstituentsHasTrack,          "_JetConstituentsHasTrack[_nJetConstituents]/O");
}

void HNLtagger::write_HNLtagger_tree()
{
    HNLtagger_tree->Print();
    HNLtagger_file->Write();
    HNLtagger_file->Close();
}
