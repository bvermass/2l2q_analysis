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
    HNLtagger_tree->Branch("_JetEta",                           &_JetEta,                           "_JetEta/D");
    HNLtagger_tree->Branch("_nJetConstituents",                 &_nJetConstituents,                 "_nJetConstituents/i");
    HNLtagger_tree->Branch("_JetConstituentPt",                 &_JetConstituentPt,                 "_JetConstituentPt[50]/D");
    HNLtagger_tree->Branch("_JetConstituentEta",                &_JetConstituentEta,                "_JetConstituentEta[50]/D");
    HNLtagger_tree->Branch("_JetConstituentPhi",                &_JetConstituentPhi,                "_JetConstituentPhi[50]/D");
    HNLtagger_tree->Branch("_JetConstituentPdgId",              &_JetConstituentPdgId,              "_JetConstituentPdgId[50]/I");
    HNLtagger_tree->Branch("_JetConstituentCharge",             &_JetConstituentCharge,             "_JetConstituentCharge[50]/I");
    HNLtagger_tree->Branch("_JetConstituentdxy",                &_JetConstituentdxy,                "_JetConstituentdxy[50]/D");
    HNLtagger_tree->Branch("_JetConstituentdxyErr",             &_JetConstituentdxyErr,             "_JetConstituentdxyErr[50]/D");
    HNLtagger_tree->Branch("_JetConstituentdz",                 &_JetConstituentdz,                 "_JetConstituentdz[50]/D");
    HNLtagger_tree->Branch("_JetConstituentdzErr",              &_JetConstituentdzErr,              "_JetConstituentdzErr[50]/D");
    HNLtagger_tree->Branch("_JetConstituentNumberOfHits",       &_JetConstituentNumberOfHits,       "_JetConstituentNumberOfHits[50]/I");
    HNLtagger_tree->Branch("_JetConstituentNumberOfPixelHits",  &_JetConstituentNumberOfPixelHits,  "_JetConstituentNumberOfPixelHits[50]/I");
    HNLtagger_tree->Branch("_JetConstituentHasTrack",           &_JetConstituentHasTrack,           "_JetConstituentHasTrack[50]/O");
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
