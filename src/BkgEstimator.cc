//////////////////////////////////////////////////////////////////////////////
//Produces BkgEstimator tree for any kind of background estimation technique//
//////////////////////////////////////////////////////////////////////////////

//Include header for the class
#include "../interface/BkgEstimator.h"

BkgEstimator::BkgEstimator(TString filename, TString type_and_flavor, int partition, int partitionjobnumber)
{
    BkgEstimator_filename = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/trees/BkgEstimator/", type_and_flavor, partition, partitionjobnumber);
    BkgEstimator_file = new TFile(BkgEstimator_filename, "recreate");
    BkgEstimator_tree = new TTree("BkgEstimator_tree", "Jetl2 constituent information for HNL tagger");
    BkgEstimator_tree->Branch("_gen_Nmass",                        &_gen_Nmass,                        "_gen_Nmass/I");
    BkgEstimator_tree->Branch("_gen_NV",                           &_gen_NV,                           "_gen_NV/D");
    BkgEstimator_tree->Branch("_gen_Nctau",                        &_gen_Nctau,                        "_gen_Nctau/D");
    BkgEstimator_tree->Branch("_JetIsFromHNL",                     &_JetIsFromHNL,                     "_JetIsFromHNL/O");
    BkgEstimator_tree->Branch("_JetPt",                            &_JetPt,                            "_JetPt/D");
    BkgEstimator_tree->Branch("_JetEta",                           &_JetEta,                           "_JetEta/D");
    BkgEstimator_tree->Branch("_JetPhi",                           &_JetPhi,                           "_JetPhi/D");
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

    BkgEstimator_tree->Branch("_l1Pt",                             &_l1Pt,                             "_l1Pt/D");
    BkgEstimator_tree->Branch("_l1Eta",                            &_l1Eta,                            "_l1Eta/D");
    BkgEstimator_tree->Branch("_l1Phi",                            &_l1Phi,                            "_l1Phi/D");
    BkgEstimator_tree->Branch("_mll",                              &_mll,                              "_mll/D");
    BkgEstimator_tree->Branch("_mlljet",                           &_mlljet,                           "_mlljet/D");
    BkgEstimator_tree->Branch("_dRll",                             &_dRll,                             "_dRll/D");
    BkgEstimator_tree->Branch("_dphill",                           &_dphill,                           "_dphill/D");
    BkgEstimator_tree->Branch("_dRljet",                           &_dRljet,                           "_dRljet/D");

    BkgEstimator_tree->Branch("_SV_PVSVdist",                      &_SV_PVSVdist,                      "_SV_PVSVdist/D");
    BkgEstimator_tree->Branch("_SV_PVSVdist_2D",                   &_SV_PVSVdist_2D,                   "_SV_PVSVdist_2D/D");
    BkgEstimator_tree->Branch("_SV_ntracks",                       &_SV_ntracks,                       "_SV_ntracks/i");
    BkgEstimator_tree->Branch("_SV_mass",                          &_SV_mass,                          "_SV_mass/D");
    BkgEstimator_tree->Branch("_SV_l1mass",                        &_SV_l1mass,                        "_SV_l1mass/D");
    BkgEstimator_tree->Branch("_SV_pt",                            &_SV_pt,                            "_SV_pt/D");
    BkgEstimator_tree->Branch("_SV_eta",                           &_SV_eta,                           "_SV_eta/D");
    BkgEstimator_tree->Branch("_SV_phi",                           &_SV_phi,                           "_SV_phi/D");
    BkgEstimator_tree->Branch("_SV_normchi2",                      &_SV_normchi2,                      "_SV_normchi2/D");
}


void BkgEstimator::fill_tree()
{
    BkgEstimator_tree->Fill();
}

void BkgEstimator::write_tree()
{
    //BkgEstimator_tree->Print();
    BkgEstimator_file->Write();
    BkgEstimator_file->Close();
}

void BkgEstimator::delete_tree()
{
    BkgEstimator_file->Close();
    gSystem->Exec("rm " + BkgEstimator_filename);
}
