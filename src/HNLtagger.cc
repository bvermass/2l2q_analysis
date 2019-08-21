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
    HNLtagger_tree->Branch("_gen_Nmass",                        &_gen_Nmass,                        "_gen_Nmass/I");
    HNLtagger_tree->Branch("_gen_NV",                           &_gen_NV,                           "_gen_NV/D");
    HNLtagger_tree->Branch("_JetIsFromHNL",                     &_JetIsFromHNL,                     "_JetIsFromHNL/O");
    HNLtagger_tree->Branch("_JetPt",                            &_JetPt,                            "_JetPt/D");
    HNLtagger_tree->Branch("_JetEta",                           &_JetEta,                           "_JetEta/D");
    HNLtagger_tree->Branch("_lPt",                              &_lPt,                              "_lPt/D");
    HNLtagger_tree->Branch("_lEta",                             &_lEta,                             "_lEta/D");
    HNLtagger_tree->Branch("_lPhi",                             &_lPhi,                             "_lPhi/D");
    HNLtagger_tree->Branch("_ldxy",                             &_ldxy,                             "_ldxy/D");
    HNLtagger_tree->Branch("_ldz",                              &_ldz,                              "_ldz/D");
    HNLtagger_tree->Branch("_l3dIPSig",                         &_l3dIPSig,                         "_l3dIPSig/D");
    HNLtagger_tree->Branch("_lrelIso",                          &_lrelIso,                          "_lrelIso/D");
    HNLtagger_tree->Branch("_lptRel",                           &_lptRel,                           "_lptRel/D");
    HNLtagger_tree->Branch("_lptRatio",                         &_lptRatio,                         "_lptRatio/D");
    HNLtagger_tree->Branch("_lNumberOfPixelHits",               &_lNumberOfPixelHits,               "_lNumberOfPixelHits/i");

    HNLtagger_tree->Branch("_SV_PVSVdist",                      &_SV_PVSVdist,                      "_SV_PVSVdist/D");
    HNLtagger_tree->Branch("_SV_PVSVdist_2D",                   &_SV_PVSVdist_2D,                   "_SV_PVSVdist_2D/D");
    HNLtagger_tree->Branch("_SV_ntracks",                       &_SV_ntracks,                       "_SV_ntracks/i");
    HNLtagger_tree->Branch("_SV_mass",                          &_SV_mass,                          "_SV_mass/D");
    HNLtagger_tree->Branch("_SV_pt",                            &_SV_pt,                            "_SV_pt/D");
    HNLtagger_tree->Branch("_SV_eta",                           &_SV_eta,                           "_SV_eta/D");
    HNLtagger_tree->Branch("_SV_phi",                           &_SV_phi,                           "_SV_phi/D");
    HNLtagger_tree->Branch("_SV_normchi2",                      &_SV_normchi2,                      "_SV_normchi2/D");

    HNLtagger_tree->Branch("_nJetConstituents",                 &_nJetConstituents,                 "_nJetConstituents/i");
    HNLtagger_tree->Branch("_JetConstituentPt",                 &_JetConstituentPt,                 "_JetConstituentPt[50]/D");
    HNLtagger_tree->Branch("_JetConstituentEta",                &_JetConstituentEta,                "_JetConstituentEta[50]/D");
    HNLtagger_tree->Branch("_JetConstituentPhi",                &_JetConstituentPhi,                "_JetConstituentPhi[50]/D");
    HNLtagger_tree->Branch("_JetConstituentPdgId",              &_JetConstituentPdgId,              "_JetConstituentPdgId[50]/D");
    HNLtagger_tree->Branch("_JetConstituentCharge",             &_JetConstituentCharge,             "_JetConstituentCharge[50]/I");
    HNLtagger_tree->Branch("_JetConstituentdxy",                &_JetConstituentdxy,                "_JetConstituentdxy[50]/D");
    HNLtagger_tree->Branch("_JetConstituentdxyErr",             &_JetConstituentdxyErr,             "_JetConstituentdxyErr[50]/D");
    HNLtagger_tree->Branch("_JetConstituentdz",                 &_JetConstituentdz,                 "_JetConstituentdz[50]/D");
    HNLtagger_tree->Branch("_JetConstituentdzErr",              &_JetConstituentdzErr,              "_JetConstituentdzErr[50]/D");
    HNLtagger_tree->Branch("_JetConstituentNumberOfHits",       &_JetConstituentNumberOfHits,       "_JetConstituentNumberOfHits[50]/I");
    HNLtagger_tree->Branch("_JetConstituentNumberOfPixelHits",  &_JetConstituentNumberOfPixelHits,  "_JetConstituentNumberOfPixelHits[50]/I");
    HNLtagger_tree->Branch("_JetConstituentHasTrack",           &_JetConstituentHasTrack,           "_JetConstituentHasTrack[50]/O");
    HNLtagger_tree->Branch("_JetConstituentInSV",               &_JetConstituentInSV,               "_JetConstituentInSV[50]/I");
}


double HNLtagger::predict(PFNReader& pfn)
{
    std::vector< double > highlevelInput( { _JetPt, _JetEta, _SV_PVSVdist, _SV_PVSVdist_2D, (double) _SV_ntracks, _SV_mass, _SV_pt, _SV_eta, _SV_phi, _SV_normchi2 } );
    std::vector< std::vector< double > > pfnInput;

    for( unsigned p = 0; p < _nJetConstituents; ++p){
        pfnInput.push_back( { _JetConstituentPt[p], _JetConstituentEta[p], _JetConstituentPhi[p], _JetConstituentdxy[p], _JetConstituentdz[p], _JetConstituentdxyErr[p], _JetConstituentdzErr[p], (double) _JetConstituentNumberOfHits[p], (double) _JetConstituentNumberOfPixelHits[p], (double)_JetConstituentCharge[p], (double) _JetConstituentPdgId[p], (double)_JetConstituentInSV[p] } );
    }

    for( unsigned i = _nJetConstituents; i < 50; ++i){
        pfnInput.push_back( {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } );
    }

    return pfn.predict( highlevelInput, pfnInput );
}


void HNLtagger::write_HNLtagger_tree()
{
    //HNLtagger_tree->Print();
    HNLtagger_file->Write();
    HNLtagger_file->Close();
}

void HNLtagger::delete_HNLtagger_tree()
{
    HNLtagger_file->Close();
    gSystem->Exec("rm " + HNLtagger_filename);
    
}

HNLBDTtagger::HNLBDTtagger(TString filename, TString type_and_flavor, int partition, int partitionjobnumber)
{
    HNLBDTtagger_filename = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/trees/HNLBDTtagger/", type_and_flavor, partition, partitionjobnumber);
    HNLBDTtagger_file = new TFile(HNLBDTtagger_filename, "recreate");
    HNLBDTtagger_tree = new TTree("HNLtagger_tree", "Jetl2 constituent information for HNL BDT tagger");
    HNLBDTtagger_tree->Branch("_gen_Nmass",            &_gen_Nmass,                        "_gen_Nmass/I");
    HNLBDTtagger_tree->Branch("_gen_NV",               &_gen_NV,                           "_gen_NV/D");
    HNLBDTtagger_tree->Branch("_JetIsFromHNL",         &_JetIsFromHNL,                     "_JetIsFromHNL/O");
    HNLBDTtagger_tree->Branch("_weight",               &_weight,                           "_weight/D");
    HNLBDTtagger_tree->Branch("_lPt",                  &_lPt,                              "_lPt/D");
    HNLBDTtagger_tree->Branch("_lEta",                 &_lEta,                             "_lEta/D");
    HNLBDTtagger_tree->Branch("_lPhi",                 &_lPhi,                             "_lPhi/D");
    HNLBDTtagger_tree->Branch("_ldxy",                 &_ldxy,                             "_ldxy/D");
    HNLBDTtagger_tree->Branch("_ldz",                  &_ldz,                              "_ldz/D");
    HNLBDTtagger_tree->Branch("_l3dIPSig",             &_l3dIPSig,                         "_l3dIPSig/D");
    HNLBDTtagger_tree->Branch("_lrelIso",              &_lrelIso,                          "_lrelIso/D");
    HNLBDTtagger_tree->Branch("_lptRel",               &_lptRel,                           "_lptRel/D");
    HNLBDTtagger_tree->Branch("_lptRatio",             &_lptRatio,                         "_lptRatio/D");
    HNLBDTtagger_tree->Branch("_lNumberOfPixelHits",   &_lNumberOfPixelHits,               "_lNumberOfPixelHits/i");

    HNLBDTtagger_tree->Branch("_JetPt",                &_JetPt,                            "_JetPt/D");
    HNLBDTtagger_tree->Branch("_JetEta",               &_JetEta,                           "_JetEta/D");
    HNLBDTtagger_tree->Branch("_JetPhi",               &_JetPhi,                           "_JetPhi/D");
    HNLBDTtagger_tree->Branch("_JetMass",              &_JetMass,                          "_JetMass/D");
    HNLBDTtagger_tree->Branch("_nJetConstituents",     &_nJetConstituents,                 "_nJetConstituents/i");
    HNLBDTtagger_tree->Branch("_JetdxySum",            &_JetdxySum,                        "_JetdxySum/D");
    HNLBDTtagger_tree->Branch("_JetdxySigSum",         &_JetdxySigSum,                     "_JetdxySigSum/D");
    HNLBDTtagger_tree->Branch("_JetdzSum",             &_JetdzSum,                         "_JetdzSum/D");
    HNLBDTtagger_tree->Branch("_JetdzSigSum",          &_JetdzSigSum,                      "_JetdzSigSum/D");
    HNLBDTtagger_tree->Branch("_JetChargeSum",         &_JetChargeSum,                     "_JetChargeSum/I");

    HNLBDTtagger_tree->Branch("_SV_ntracks",           &_SV_ntracks,                       "_SV_ntracks/i");
    HNLBDTtagger_tree->Branch("_SV_PVSVdist_2D",       &_SV_PVSVdist_2D,                   "_SV_PVSVdist_2D/D");
    HNLBDTtagger_tree->Branch("_SV_PVSVdist",          &_SV_PVSVdist,                      "_SV_PVSVdist/D");
    HNLBDTtagger_tree->Branch("_SV_normchi2",          &_SV_normchi2,                      "_SV_normchi2/D");
    HNLBDTtagger_tree->Branch("_SV_mass",              &_SV_mass,                          "_SV_mass/D");
    HNLBDTtagger_tree->Branch("_SV_pt",                &_SV_pt,                            "_SV_pt/D");
    HNLBDTtagger_tree->Branch("_SV_eta",               &_SV_eta,                           "_SV_eta/D");
    HNLBDTtagger_tree->Branch("_SV_phi",               &_SV_phi,                           "_SV_phi/D");
}

double HNLBDTtagger::predict(PFNReader& bdt)
{
    std::vector< double > highlevelInput( { _lPt, _lEta, _lPhi, _ldxy, _ldz, _l3dIPSig, _lrelIso, _lptRel, _lptRatio, (double)_lNumberOfPixelHits,
                                            _JetPt, _JetEta, _JetPhi, _JetMass, (double)_nJetConstituents, _JetdxySum, _JetdxySigSum, _JetdzSum, _JetdzSigSum, (double)_JetChargeSum,
                                            (double)_SV_ntracks, _SV_PVSVdist_2D, _SV_PVSVdist, _SV_normchi2, _SV_mass, _SV_pt, _SV_eta, _SV_phi } );

    return bdt.predict( highlevelInput );
}

void HNLBDTtagger::write_HNLBDTtagger_tree()
{
    //HNLBDTtagger_tree->Print();
    HNLBDTtagger_file->Write();
    HNLBDTtagger_file->Close();
}

void HNLBDTtagger::delete_HNLBDTtagger_tree()
{
    HNLBDTtagger_file->Close();
    gSystem->Exec("rm " + HNLBDTtagger_filename);
    
}
