////////////////////////////////////////////////////////////////////////////
//Produces HNL tagger tree for neural network, part of class full_analyzer//
////////////////////////////////////////////////////////////////////////////

//Include header for the class
#include "../interface/HNLtagger.h"

HNLtagger::HNLtagger(TString filename, TString type_and_flavor, int partition, int partitionjobnumber)
{
    HNLtagger_filename = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/trees/HNLtagger/", type_and_flavor, partition, partitionjobnumber);
    HNLtagger_file = new TFile(HNLtagger_filename, "recreate");
    HNLtagger_tree = new TTree("HNLtagger_tree", "Jetl2 constituent information for HNL tagger");
    HNLtagger_tree->Branch("_JetIsFromHNL",                     &_JetIsFromHNL,                     "_JetIsFromHNL/O");
    HNLtagger_tree->Branch("_JetPt",                            &_JetPt,                            "_JetPt/D");
    HNLtagger_tree->Branch("_JetEta",                           &_JetEta,                           "_JetPt/D");
    HNLtagger_tree->Branch("_nJetConstituents",                 &_nJetConstituents,                 "_nJetConstituents/i");
    HNLtagger_tree->Branch("_JetConstituentPt",                 &_JetConstituentPt,                 "_JetConstituentPt[50]/D");
    HNLtagger_tree->Branch("_JetConstituentEta",                &_JetConstituentEta,                "_JetConstituentEta[50]/D");
    HNLtagger_tree->Branch("_JetConstituentPhi",                &_JetConstituentPhi,                "_JetConstituentPhi[50]/D");
    HNLtagger_tree->Branch("_JetConstituentMass",               &_JetConstituentMass,               "_JetConstituentMass[50]/D");
    HNLtagger_tree->Branch("_JetConstituentPdgId",              &_JetConstituentPdgId,              "_JetConstituentPdgId[50]/I");
    HNLtagger_tree->Branch("_JetConstituentCharge",             &_JetConstituentCharge,             "_JetConstituentCharge[50]/I");
    HNLtagger_tree->Branch("_JetConstituentdxySig",             &_JetConstituentdxySig,             "_JetConstituentdxySig[50]/D");
    HNLtagger_tree->Branch("_JetConstituentdzSig",              &_JetConstituentdzSig,              "_JetConstituentdzSig[50]/D");
    HNLtagger_tree->Branch("_JetConstituentsNumberOfHits",      &_JetConstituentsNumberOfHits,      "_JetConstituentsNumberOfHits[50]/I");
    HNLtagger_tree->Branch("_JetConstituentsNumberOfPixelHits", &_JetConstituentsNumberOfPixelHits, "_JetConstituentsNumberOfPixelHits[50]/I");
    HNLtagger_tree->Branch("_JetConstituentsHasTrack",          &_JetConstituentsHasTrack,          "_JetConstituentsHasTrack[50]/O");
}

void HNLtagger::write_HNLtagger_tree()
{
    HNLtagger_tree->Print();
    HNLtagger_file->Write();
    HNLtagger_file->Close();
}

void HNLtagger::delete_HNLtagger_tree()
{
    HNLtagger_file->Close();
    gSystem->Exec("rm " + HNLtagger_filename);
    
}
