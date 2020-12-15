//////////////////////////////////////////////////////////////////////////////
//Produces BkgEstimator tree for any kind of background estimation technique//
//////////////////////////////////////////////////////////////////////////////

//Include header for the class
#include "../interface/BkgEstimator.h"

BkgEstimator::BkgEstimator(TString filename, TString type_and_flavor, int partition, int partitionjobnumber)
{
    //BkgEstimator_filename = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/trees/BkgEstimator/", type_and_flavor, partition, partitionjobnumber, true);
    BkgEstimator_filename = make_outputfilename(filename, "/user/bvermass/public/2l2q_analysis/trees_POGTightID/BkgEstimator/", type_and_flavor, partition, partitionjobnumber, true);
    BkgEstimator_file = new TFile(BkgEstimator_filename, "recreate");
    BkgEstimator_tree = new TTree("BkgEstimator_tree", "Class containing main variables for Background estimation");
    BkgEstimator_tree->Branch("_weight",                           &_weight,                           "_weight/D");
    BkgEstimator_tree->Branch("_is2016",                           &_is2016,                           "_is2016/O");
    BkgEstimator_tree->Branch("_is2017",                           &_is2017,                           "_is2017/O");
    BkgEstimator_tree->Branch("_is2018",                           &_is2018,                           "_is2018/O");
    BkgEstimator_tree->Branch("_gen_Nmass",                        &_gen_Nmass,                        "_gen_Nmass/I");
    BkgEstimator_tree->Branch("_gen_NV2",                          &_gen_NV2,                          "_gen_NV2/D");
    BkgEstimator_tree->Branch("_gen_Nctau",                        &_gen_Nctau,                        "_gen_Nctau/D");
    BkgEstimator_tree->Branch("_JetIsFromHNL",                     &_JetIsFromHNL,                     "_JetIsFromHNL/O");
    BkgEstimator_tree->Branch("_nTightJet",                        &_nTightJet,                        "_nTightJet/i");
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

    BkgEstimator_tree->Branch("_l1Pt",                             &_l1Pt,                             "_l1Pt/D");
    BkgEstimator_tree->Branch("_l1Eta",                            &_l1Eta,                            "_l1Eta/D");
    BkgEstimator_tree->Branch("_l1Phi",                            &_l1Phi,                            "_l1Phi/D");
    BkgEstimator_tree->Branch("_l1Flavor",                         &_l1Flavor,                         "_l1Flavor/i");
    BkgEstimator_tree->Branch("_l1Charge",                         &_l1Charge,                         "_l1Charge/I");
    BkgEstimator_tree->Branch("_l1Provenance",                     &_l1Provenance,                     "_l1Provenance/i");
    BkgEstimator_tree->Branch("_l1ProvenanceCompressed",           &_l1ProvenanceCompressed,           "_l1ProvenanceCompressed/i");
    BkgEstimator_tree->Branch("_mll",                              &_mll,                              "_mll/D");
    BkgEstimator_tree->Branch("_mlljet",                           &_mlljet,                           "_mlljet/D");
    BkgEstimator_tree->Branch("_dRll",                             &_dRll,                             "_dRll/D");
    BkgEstimator_tree->Branch("_dphill",                           &_dphill,                           "_dphill/D");
    BkgEstimator_tree->Branch("_dRljet",                           &_dRljet,                           "_dRljet/D");

    BkgEstimator_tree->Branch("_SV_PVSVdist",                      &_SV_PVSVdist,                      "_SV_PVSVdist/D");
    BkgEstimator_tree->Branch("_SV_PVSVdist_2D",                   &_SV_PVSVdist_2D,                   "_SV_PVSVdist_2D/D");
    BkgEstimator_tree->Branch("_SV_genreco",                       &_SV_genreco,                       "_SV_genreco/D");
    BkgEstimator_tree->Branch("_SV_ntracks",                       &_SV_ntracks,                       "_SV_ntracks/i");
    BkgEstimator_tree->Branch("_SV_mass",                          &_SV_mass,                          "_SV_mass/D");
    BkgEstimator_tree->Branch("_SV_l1mass",                        &_SV_l1mass,                        "_SV_l1mass/D");
    BkgEstimator_tree->Branch("_SV_pt",                            &_SV_pt,                            "_SV_pt/D");
    BkgEstimator_tree->Branch("_SV_eta",                           &_SV_eta,                           "_SV_eta/D");
    BkgEstimator_tree->Branch("_SV_phi",                           &_SV_phi,                           "_SV_phi/D");
    BkgEstimator_tree->Branch("_SV_normchi2",                      &_SV_normchi2,                      "_SV_normchi2/D");

    BkgEstimator_tree->Branch("_nMV2",                             &_nMV2,                             "_nMV2/i");
    BkgEstimator_tree->Branch("_evaluating_mass",                  &_evaluating_mass,                  "_evaluating_mass[_nMV2]/I");
    BkgEstimator_tree->Branch("_evaluating_V2",                    &_evaluating_V2,                    "_evaluating_V2[_nMV2]/D");
    BkgEstimator_tree->Branch("_JetTagVal",                        &_JetTagVal,                        "_JetTagVal[_nMV2]/D");
    BkgEstimator_tree->Branch("_reweighting_weight",               &_reweighting_weight,               "_reweighting_weight[_nMV2]/D");
}


// Constructor where BkgEstimator variables are read from an existing file that was produced USING THIS CLASS.
BkgEstimator::BkgEstimator(TString filename)
{
    BkgEstimator_filename = filename;
    open_file_and_tree(filename);
    set_branch_adresses();
}


void BkgEstimator::open_file_and_tree(TString filename)
{
    BkgEstimator_file = new TFile(filename, "open");
    BkgEstimator_tree = (TTree*) BkgEstimator_file->Get("BkgEstimator_tree");
}


void BkgEstimator::set_branch_adresses()
{
    BkgEstimator_tree->SetBranchAddress("_weight", &_weight, &b__weight);
    BkgEstimator_tree->SetBranchAddress("_is2016", &_is2016, &b__is2016);
    BkgEstimator_tree->SetBranchAddress("_is2017", &_is2017, &b__is2017);
    BkgEstimator_tree->SetBranchAddress("_is2018", &_is2018, &b__is2018);
    BkgEstimator_tree->SetBranchAddress("_gen_Nmass", &_gen_Nmass, &b__gen_Nmass);
    BkgEstimator_tree->SetBranchAddress("_gen_NV2", &_gen_NV2, &b__gen_NV2);
    BkgEstimator_tree->SetBranchAddress("_gen_Nctau", &_gen_Nctau, &b__gen_Nctau);
    BkgEstimator_tree->SetBranchAddress("_JetIsFromHNL", &_JetIsFromHNL, &b__JetIsFromHNL);
    BkgEstimator_tree->SetBranchAddress("_nTightJet", &_nTightJet, &b__nTightJet);
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

    BkgEstimator_tree->SetBranchAddress("_l1Pt", &_l1Pt, &b__l1Pt);
    BkgEstimator_tree->SetBranchAddress("_l1Eta", &_l1Eta, &b__l1Eta);
    BkgEstimator_tree->SetBranchAddress("_l1Phi", &_l1Phi, &b__l1Phi);
    BkgEstimator_tree->SetBranchAddress("_l1Flavor", &_l1Flavor, &b__l1Flavor);
    BkgEstimator_tree->SetBranchAddress("_l1Charge", &_l1Charge, &b__l1Charge);
    BkgEstimator_tree->SetBranchAddress("_l1Provenance", &_l1Provenance, &b__l1Provenance);
    BkgEstimator_tree->SetBranchAddress("_l1ProvenanceCompressed", &_l1ProvenanceCompressed, &b__l1ProvenanceCompressed);
    BkgEstimator_tree->SetBranchAddress("_mll", &_mll, &b__mll);
    BkgEstimator_tree->SetBranchAddress("_mlljet", &_mlljet, &b__mlljet);
    BkgEstimator_tree->SetBranchAddress("_dRll", &_dRll, &b__dRll);
    BkgEstimator_tree->SetBranchAddress("_dphill", &_dphill, &b__dphill);
    BkgEstimator_tree->SetBranchAddress("_dRljet", &_dRljet, &b__dRljet);
    BkgEstimator_tree->SetBranchAddress("_SV_PVSVdist", &_SV_PVSVdist, &b__SV_PVSVdist);
    BkgEstimator_tree->SetBranchAddress("_SV_PVSVdist_2D", &_SV_PVSVdist_2D, &b__SV_PVSVdist_2D);
    BkgEstimator_tree->SetBranchAddress("_SV_genreco", &_SV_genreco, &b__SV_genreco);
    BkgEstimator_tree->SetBranchAddress("_SV_ntracks", &_SV_ntracks, &b__SV_ntracks);
    BkgEstimator_tree->SetBranchAddress("_SV_mass", &_SV_mass, &b__SV_mass);
    BkgEstimator_tree->SetBranchAddress("_SV_l1mass", &_SV_l1mass, &b__SV_l1mass);
    BkgEstimator_tree->SetBranchAddress("_SV_pt", &_SV_pt, &b__SV_pt);
    BkgEstimator_tree->SetBranchAddress("_SV_eta", &_SV_eta, &b__SV_eta);
    BkgEstimator_tree->SetBranchAddress("_SV_phi", &_SV_phi, &b__SV_phi);
    BkgEstimator_tree->SetBranchAddress("_SV_normchi2", &_SV_normchi2, &b__SV_normchi2);

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

    //main loop
    for(unsigned jentry = j_begin; jentry < j_end; ++jentry){
	    BkgEstimator_tree->GetEntry(jentry);
	    if(loop_counter == notice){
            std::cout << jentry - j_begin << " of " << j_end - j_begin << std::endl;
            loop_counter = 0;
	    }
        ++loop_counter;
    }
}


void BkgEstimator::fill_tree()
{
    BkgEstimator_tree->Fill();
}

void BkgEstimator::write_tree()
{
    //BkgEstimator_tree->Print();
    std::cout << "writing BkgEstimator tree" << std::endl;
    BkgEstimator_file->Write();
    BkgEstimator_file->Close();
}

void BkgEstimator::delete_tree()
{
    BkgEstimator_file->Close();
    gSystem->Exec("rm " + BkgEstimator_filename);
}
