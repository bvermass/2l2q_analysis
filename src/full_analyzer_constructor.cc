//basic constructor and initializer functions
#include "../interface/full_analyzer.h"

full_analyzer::full_analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/displaced/HeavyNeutrino_lljj_M-5_V-0.00707106781187_e_massiveAndCKM_LO/dilep.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/displaced/HeavyNeutrino_lljj_M-5_V-0.00707106781187_e_massiveAndCKM_LO/dilep.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/displaced/HeavyNeutrino_lljj_M-5_V-0.00707106781187_e_massiveAndCKM_LO/dilep.root:/blackJackAndHookers");
      dir->GetObject("blackJackAndHookersTree",tree);

   }
   Init(tree);
   event_weight             = 1;
   i_leading_e              = -1;
   i_subleading_e           = -1;
   i_subleading_displ_e     = -1;
   i_leading_pogmedium_e    = -1;
   i_leading_mu             = -1;
   i_subleading_mu          = -1;
   i_subleading_displ_mu    = -1;
   i_leading_pogmedium_mu   = -1;
                              
   i_leading_jet        = -1;
   i_subleading_jet     = -1;
   i_thirdleading_jet   = -1;

   count_IVFmatch_larger_than_IVF_nvertex   = 0;

}

full_analyzer::~full_analyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t full_analyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t full_analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void full_analyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);


   fChain->SetBranchAddress("_runNb", &_runNb, &b__runNb);
   fChain->SetBranchAddress("_lumiBlock", &_lumiBlock, &b__lumiBlock);
   fChain->SetBranchAddress("_eventNb", &_eventNb, &b__eventNb);
   fChain->SetBranchAddress("_nVertex", &_nVertex, &b__nVertex);
   fChain->SetBranchAddress("_BS_x", &_BS_x, &b__BS_x);
   fChain->SetBranchAddress("_BS_y", &_BS_y, &b__BS_y);
   fChain->SetBranchAddress("_BS_z", &_BS_z, &b__BS_z);
   fChain->SetBranchAddress("_PV_x", &_PV_x, &b__PV_x);
   fChain->SetBranchAddress("_PV_y", &_PV_y, &b__PV_y);
   fChain->SetBranchAddress("_PV_z", &_PV_z, &b__PV_z);
   fChain->SetBranchAddress("_nTrueInt", &_nTrueInt, &b__nTrueInt);
   fChain->SetBranchAddress("_weight", &_weight, &b__weight);
   fChain->SetBranchAddress("_lheHTIncoming", &_lheHTIncoming, &b__lheHTIncoming);
   fChain->SetBranchAddress("_ctauHN", &_ctauHN, &b__ctauHN);
   fChain->SetBranchAddress("_nLheWeights", &_nLheWeights, &b__nLheWeights);
   fChain->SetBranchAddress("_lheWeight", _lheWeight, &b__lheWeight);
   fChain->SetBranchAddress("_ttgEventType", &_ttgEventType, &b__ttgEventType);
   fChain->SetBranchAddress("_zgEventType", &_zgEventType, &b__zgEventType);
   fChain->SetBranchAddress("_gen_met", &_gen_met, &b__gen_met);
   fChain->SetBranchAddress("_gen_metPhi", &_gen_metPhi, &b__gen_metPhi);
   fChain->SetBranchAddress("_gen_nPh", &_gen_nPh, &b__gen_nPh);
   fChain->SetBranchAddress("_gen_phPt", _gen_phPt, &b__gen_phPt);
   fChain->SetBranchAddress("_gen_phEta", _gen_phEta, &b__gen_phEta);
   fChain->SetBranchAddress("_gen_phPhi", _gen_phPhi, &b__gen_phPhi);
   fChain->SetBranchAddress("_gen_phE", _gen_phE, &b__gen_phE);
   fChain->SetBranchAddress("_gen_phMomPdg", _gen_phMomPdg, &b__gen_phMomPdg);
   fChain->SetBranchAddress("_gen_phIsPrompt", _gen_phIsPrompt, &b__gen_phIsPrompt);
   fChain->SetBranchAddress("_gen_phMinDeltaR", _gen_phMinDeltaR, &b__gen_phMinDeltaR);
   fChain->SetBranchAddress("_gen_phPassParentage", _gen_phPassParentage, &b__gen_phPassParentage);
   fChain->SetBranchAddress("_gen_nL", &_gen_nL, &b__gen_nL);
   fChain->SetBranchAddress("_gen_lPt", _gen_lPt, &b__gen_lPt);
   fChain->SetBranchAddress("_gen_lEta", _gen_lEta, &b__gen_lEta);
   fChain->SetBranchAddress("_gen_lPhi", _gen_lPhi, &b__gen_lPhi);
   fChain->SetBranchAddress("_gen_lE", _gen_lE, &b__gen_lE);
   fChain->SetBranchAddress("_gen_lFlavor", _gen_lFlavor, &b__gen_lFlavor);
   fChain->SetBranchAddress("_gen_lCharge", _gen_lCharge, &b__gen_lCharge);
   fChain->SetBranchAddress("_gen_lMomPdg", _gen_lMomPdg, &b__gen_lMomPdg);
   fChain->SetBranchAddress("_gen_vertex_x", _gen_vertex_x, &b__gen_vertex_x);
   fChain->SetBranchAddress("_gen_vertex_y", _gen_vertex_y, &b__gen_vertex_y);
   fChain->SetBranchAddress("_gen_vertex_z", _gen_vertex_z, &b__gen_vertex_z);
   fChain->SetBranchAddress("_gen_lIsPrompt", _gen_lIsPrompt, &b__gen_lIsPrompt);
   fChain->SetBranchAddress("_gen_lMinDeltaR", _gen_lMinDeltaR, &b__gen_lMinDeltaR);
   fChain->SetBranchAddress("_gen_lPassParentage", _gen_lPassParentage, &b__gen_lPassParentage);
   fChain->SetBranchAddress("_gen_HT", &_gen_HT, &b__gen_HT);
   fChain->SetBranchAddress("_gen_nN", &_gen_nN, &b__gen_nN);
   fChain->SetBranchAddress("_gen_NPt", &_gen_NPt, &b__gen_NPt);
   fChain->SetBranchAddress("_gen_NEta", &_gen_NEta, &b__gen_NEta);
   fChain->SetBranchAddress("_gen_NPhi", &_gen_NPhi, &b__gen_NPhi);
   fChain->SetBranchAddress("_gen_NE", &_gen_NE, &b__gen_NE);
   fChain->SetBranchAddress("_gen_Nvertex_x", &_gen_Nvertex_x, &b__gen_Nvertex_x);
   fChain->SetBranchAddress("_gen_Nvertex_y", &_gen_Nvertex_y, &b__gen_Nvertex_y);
   fChain->SetBranchAddress("_gen_Nvertex_z", &_gen_Nvertex_z, &b__gen_Nvertex_z);
   fChain->SetBranchAddress("_gen_nNPackedDtrs", &_gen_nNPackedDtrs, &b__gen_nNPackedDtrs);
   fChain->SetBranchAddress("_gen_NPackedDtrsPt", &_gen_NPackedDtrsPt, &b__gen_NPackedDtrsPt);
   fChain->SetBranchAddress("_gen_NPackedDtrsEta", &_gen_NPackedDtrsEta, &b__gen_NPackedDtrsEta);
   fChain->SetBranchAddress("_gen_NPackedDtrsPhi", &_gen_NPackedDtrsPhi, &b__gen_NPackedDtrsPhi);
   fChain->SetBranchAddress("_gen_NPackedDtrsE", &_gen_NPackedDtrsE, &b__gen_NPackedDtrsE);
   fChain->SetBranchAddress("_gen_NPackedDtrsPdgId", &_gen_NPackedDtrsPdgId, &b__gen_NPackedDtrsPdgId);
   fChain->SetBranchAddress("_gen_NPackedDtrsCharge", &_gen_NPackedDtrsCharge, &b__gen_NPackedDtrsCharge);
   fChain->SetBranchAddress("matches", &matches, &b_matches);
   fChain->SetBranchAddress("_gen_NPackedDtrsmineta", &_gen_NPackedDtrsmineta, &b__gen_NPackedDtrsmineta);
   fChain->SetBranchAddress("_gen_NPackedDtrsminphi", &_gen_NPackedDtrsminphi, &b__gen_NPackedDtrsminphi);
   fChain->SetBranchAddress("_gen_NPackedDtrsminpt", &_gen_NPackedDtrsminpt, &b__gen_NPackedDtrsminpt);
   fChain->SetBranchAddress("_gen_NPackedDtrs_matchPt", &_gen_NPackedDtrs_matchPt, &b__gen_NPackedDtrs_matchPt);
   fChain->SetBranchAddress("_gen_NPackedDtrs_matchEta", &_gen_NPackedDtrs_matchEta, &b__gen_NPackedDtrs_matchEta);
   fChain->SetBranchAddress("_gen_NPackedDtrs_matchPhi", &_gen_NPackedDtrs_matchPhi, &b__gen_NPackedDtrs_matchPhi);
   fChain->SetBranchAddress("_gen_NPackedDtrs_matchE", &_gen_NPackedDtrs_matchE, &b__gen_NPackedDtrs_matchE);
   fChain->SetBranchAddress("_gen_NPackedDtrs_matchdxy", &_gen_NPackedDtrs_matchdxy, &b__gen_NPackedDtrs_matchdxy);
   fChain->SetBranchAddress("_gen_NPackedDtrs_matchdz", &_gen_NPackedDtrs_matchdz, &b__gen_NPackedDtrs_matchdz);
   fChain->SetBranchAddress("_gen_NPackedDtrs_matchcharge", &_gen_NPackedDtrs_matchcharge, &b__gen_NPackedDtrs_matchcharge);
   fChain->SetBranchAddress("_gen_nNdaughters", &_gen_nNdaughters, &b__gen_nNdaughters);
   fChain->SetBranchAddress("_gen_Ndaughters_pdg", _gen_Ndaughters_pdg, &b__gen_Ndaughters_pdg);
   fChain->SetBranchAddress("_gen_nstatus23", &_gen_nstatus23, &b__gen_nstatus23);
   fChain->SetBranchAddress("_gen_nstatus23_fromN", &_gen_nstatus23_fromN, &b__gen_nstatus23_fromN);
   fChain->SetBranchAddress("_gen_nstatus23_fromW", &_gen_nstatus23_fromW, &b__gen_nstatus23_fromW);
   fChain->SetBranchAddress("_gen_status23_pdg", _gen_status23_pdg, &b__gen_status23_pdg);
   fChain->SetBranchAddress("_gen_status23_fromN_pdg", _gen_status23_fromN_pdg, &b__gen_status23_fromN_pdg);
   fChain->SetBranchAddress("_gen_status23_fromW_pdg", _gen_status23_fromW_pdg, &b__gen_status23_fromW_pdg);
   fChain->SetBranchAddress("_gen_nq", &_gen_nq, &b__gen_nq);
   fChain->SetBranchAddress("_gen_qPt", _gen_qPt, &b__gen_qPt);
   fChain->SetBranchAddress("_gen_qEta", _gen_qEta, &b__gen_qEta);
   fChain->SetBranchAddress("_gen_qPhi", _gen_qPhi, &b__gen_qPhi);
   fChain->SetBranchAddress("_gen_qE", _gen_qE, &b__gen_qE);
   fChain->SetBranchAddress("_gen_nq1dtr", &_gen_nq1dtr, &b__gen_nq1dtr);
   fChain->SetBranchAddress("_gen_q1dtr_status", _gen_q1dtr_status, &b__gen_q1dtr_status);
   fChain->SetBranchAddress("_gen_q1dtr_pdgid", _gen_q1dtr_pdgid, &b__gen_q1dtr_pdgid);
   fChain->SetBranchAddress("_gen_q1dtr_Pt", _gen_q1dtr_Pt, &b__gen_q1dtr_Pt);
   fChain->SetBranchAddress("_gen_q1dtr_Eta", _gen_q1dtr_Eta, &b__gen_q1dtr_Eta);
   fChain->SetBranchAddress("_gen_q1dtr_Phi", _gen_q1dtr_Phi, &b__gen_q1dtr_Phi);
   fChain->SetBranchAddress("_gen_q1dtr_E", _gen_q1dtr_E, &b__gen_q1dtr_E);
   fChain->SetBranchAddress("_gen_nq2dtr", &_gen_nq2dtr, &b__gen_nq2dtr);
   fChain->SetBranchAddress("_gen_q2dtr_status", _gen_q2dtr_status, &b__gen_q2dtr_status);
   fChain->SetBranchAddress("_gen_q2dtr_pdgid", _gen_q2dtr_pdgid, &b__gen_q2dtr_pdgid);
   fChain->SetBranchAddress("_gen_q2dtr_Pt", _gen_q2dtr_Pt, &b__gen_q2dtr_Pt);
   fChain->SetBranchAddress("_gen_q2dtr_Eta", _gen_q2dtr_Eta, &b__gen_q2dtr_Eta);
   fChain->SetBranchAddress("_gen_q2dtr_Phi", _gen_q2dtr_Phi, &b__gen_q2dtr_Phi);
   fChain->SetBranchAddress("_gen_q2dtr_E", _gen_q2dtr_E, &b__gen_q2dtr_E);
   fChain->SetBranchAddress("_HLT_Ele27_WPTight_Gsf", &_HLT_Ele27_WPTight_Gsf, &b__HLT_Ele27_WPTight_Gsf);
   fChain->SetBranchAddress("_HLT_Ele27_WPTight_Gsf_prescale", &_HLT_Ele27_WPTight_Gsf_prescale, &b__HLT_Ele27_WPTight_Gsf_prescale);
   fChain->SetBranchAddress("_HLT_IsoMu24", &_HLT_IsoMu24, &b__HLT_IsoMu24);
   fChain->SetBranchAddress("_HLT_IsoMu24_prescale", &_HLT_IsoMu24_prescale, &b__HLT_IsoMu24_prescale);
   fChain->SetBranchAddress("_HLT_IsoTkMu24", &_HLT_IsoTkMu24, &b__HLT_IsoTkMu24);
   fChain->SetBranchAddress("_HLT_IsoTkMu24_prescale", &_HLT_IsoTkMu24_prescale, &b__HLT_IsoTkMu24_prescale);
   //fChain->SetBranchAddress("_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL", &_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL, &b__HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL);
   //fChain->SetBranchAddress("_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_prescale", &_HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_prescale, &b__HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_prescale);
   //fChain->SetBranchAddress("_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, &b__HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
   //fChain->SetBranchAddress("_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale", &_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale, &b__HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale);
   //fChain->SetBranchAddress("_HLT_Mu8_DiEle12_CaloIdL_TrackIdL", &_HLT_Mu8_DiEle12_CaloIdL_TrackIdL, &b__HLT_Mu8_DiEle12_CaloIdL_TrackIdL);
   //fChain->SetBranchAddress("_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_prescale", &_HLT_Mu8_DiEle12_CaloIdL_TrackIdL_prescale, &b__HLT_Mu8_DiEle12_CaloIdL_TrackIdL_prescale);
   //fChain->SetBranchAddress("_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ, &b__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
   //fChain->SetBranchAddress("_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_prescale", &_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_prescale, &b__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_prescale);
   //fChain->SetBranchAddress("_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL, &b__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
   //fChain->SetBranchAddress("_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_prescale", &_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_prescale, &b__HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_prescale);
   //fChain->SetBranchAddress("_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ", &_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ, &b__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ);
   //fChain->SetBranchAddress("_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_prescale", &_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_prescale, &b__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_prescale);
   //fChain->SetBranchAddress("_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL", &_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL, &b__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL);
   //fChain->SetBranchAddress("_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_prescale", &_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_prescale, &b__HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_prescale);
   //fChain->SetBranchAddress("_HLT_DiMu9_Ele9_CaloIdL_TrackIdL", &_HLT_DiMu9_Ele9_CaloIdL_TrackIdL, &b__HLT_DiMu9_Ele9_CaloIdL_TrackIdL);
   //fChain->SetBranchAddress("_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_prescale", &_HLT_DiMu9_Ele9_CaloIdL_TrackIdL_prescale, &b__HLT_DiMu9_Ele9_CaloIdL_TrackIdL_prescale);
   //fChain->SetBranchAddress("_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ", &_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ, &b__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
   //fChain->SetBranchAddress("_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_prescale", &_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_prescale, &b__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_prescale);
   //fChain->SetBranchAddress("_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ", &_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ, &b__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ);
   //fChain->SetBranchAddress("_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale", &_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale, &b__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale);
   //fChain->SetBranchAddress("_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ", &_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ, &b__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ);
   //fChain->SetBranchAddress("_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale", &_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale, &b__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_prescale);
   //fChain->SetBranchAddress("_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL", &_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL, &b__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL);
   //fChain->SetBranchAddress("_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_prescale", &_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_prescale, &b__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_prescale);
   //fChain->SetBranchAddress("_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL", &_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL, &b__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL);
   //fChain->SetBranchAddress("_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale", &_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale, &b__HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale);
   //fChain->SetBranchAddress("_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL", &_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL, &b__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL);
   //fChain->SetBranchAddress("_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale", &_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale, &b__HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_prescale);
   //fChain->SetBranchAddress("_HLT_TripleMu_12_10_5", &_HLT_TripleMu_12_10_5, &b__HLT_TripleMu_12_10_5);
   //fChain->SetBranchAddress("_HLT_TripleMu_12_10_5_prescale", &_HLT_TripleMu_12_10_5_prescale, &b__HLT_TripleMu_12_10_5_prescale);
   //fChain->SetBranchAddress("_passMETFilters", &_passMETFilters, &b__passMETFilters);
   //fChain->SetBranchAddress("_Flag_HBHENoiseFilter", &_Flag_HBHENoiseFilter, &b__Flag_HBHENoiseFilter);
   //fChain->SetBranchAddress("_Flag_HBHENoiseIsoFilter", &_Flag_HBHENoiseIsoFilter, &b__Flag_HBHENoiseIsoFilter);
   //fChain->SetBranchAddress("_Flag_EcalDeadCellTriggerPrimitiveFilter", &_Flag_EcalDeadCellTriggerPrimitiveFilter, &b__Flag_EcalDeadCellTriggerPrimitiveFilter);
   //fChain->SetBranchAddress("_Flag_goodVertices", &_Flag_goodVertices, &b__Flag_goodVertices);
   //fChain->SetBranchAddress("_Flag_globalTightHalo2016Filter", &_Flag_globalTightHalo2016Filter, &b__Flag_globalTightHalo2016Filter);
   //fChain->SetBranchAddress("_Flag_BadPFMuonFilter", &_Flag_BadPFMuonFilter, &b__Flag_BadPFMuonFilter);
   //fChain->SetBranchAddress("_Flag_BadChargedCandidateFilter", &_Flag_BadChargedCandidateFilter, &b__Flag_BadChargedCandidateFilter);
   //fChain->SetBranchAddress("_HLT_Ele105_CaloIdVT_GsfTrkIdT", &_HLT_Ele105_CaloIdVT_GsfTrkIdT, &b__HLT_Ele105_CaloIdVT_GsfTrkIdT);
   //fChain->SetBranchAddress("_HLT_Ele105_CaloIdVT_GsfTrkIdT_prescale", &_HLT_Ele105_CaloIdVT_GsfTrkIdT_prescale, &b__HLT_Ele105_CaloIdVT_GsfTrkIdT_prescale);
   //fChain->SetBranchAddress("_HLT_Ele115_CaloIdVT_GsfTrkIdT", &_HLT_Ele115_CaloIdVT_GsfTrkIdT, &b__HLT_Ele115_CaloIdVT_GsfTrkIdT);
   //fChain->SetBranchAddress("_HLT_Ele115_CaloIdVT_GsfTrkIdT_prescale", &_HLT_Ele115_CaloIdVT_GsfTrkIdT_prescale, &b__HLT_Ele115_CaloIdVT_GsfTrkIdT_prescale);
   //fChain->SetBranchAddress("_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, &b__HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
   //fChain->SetBranchAddress("_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale", &_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale, &b__HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_prescale);
   //fChain->SetBranchAddress("_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL", &_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL, &b__HLT_DoubleEle33_CaloIdL_GsfTrkIdVL);
   //fChain->SetBranchAddress("_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_prescale", &_HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_prescale, &b__HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_prescale);
   //fChain->SetBranchAddress("_HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL", &_HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL, &b__HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL);
   //fChain->SetBranchAddress("_HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_prescale", &_HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_prescale, &b__HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_prescale);
   //fChain->SetBranchAddress("_HLT_Mu50", &_HLT_Mu50, &b__HLT_Mu50);
   //fChain->SetBranchAddress("_HLT_Mu50_prescale", &_HLT_Mu50_prescale, &b__HLT_Mu50_prescale);
   //fChain->SetBranchAddress("_HLT_TkMu50", &_HLT_TkMu50, &b__HLT_TkMu50);
   //fChain->SetBranchAddress("_HLT_TkMu50_prescale", &_HLT_TkMu50_prescale, &b__HLT_TkMu50_prescale);
   //fChain->SetBranchAddress("_HLT_Mu45_eta2p1", &_HLT_Mu45_eta2p1, &b__HLT_Mu45_eta2p1);
   //fChain->SetBranchAddress("_HLT_Mu45_eta2p1_prescale", &_HLT_Mu45_eta2p1_prescale, &b__HLT_Mu45_eta2p1_prescale);
   //fChain->SetBranchAddress("_HLT_Mu30_TkMu11", &_HLT_Mu30_TkMu11, &b__HLT_Mu30_TkMu11);
   //fChain->SetBranchAddress("_HLT_Mu30_TkMu11_prescale", &_HLT_Mu30_TkMu11_prescale, &b__HLT_Mu30_TkMu11_prescale);
   fChain->SetBranchAddress("_nL", &_nL, &b__nL);
   fChain->SetBranchAddress("_nMu", &_nMu, &b__nMu);
   fChain->SetBranchAddress("_nEle", &_nEle, &b__nEle);
   fChain->SetBranchAddress("_nLight", &_nLight, &b__nLight);
   fChain->SetBranchAddress("_nTau", &_nTau, &b__nTau);
   fChain->SetBranchAddress("_lPt", _lPt, &b__lPt);
   fChain->SetBranchAddress("_lEta", _lEta, &b__lEta);
   fChain->SetBranchAddress("_lEtaSC", _lEtaSC, &b__lEtaSC);
   fChain->SetBranchAddress("_lPhi", _lPhi, &b__lPhi);
   fChain->SetBranchAddress("_lE", _lE, &b__lE);
   fChain->SetBranchAddress("_lFlavor", _lFlavor, &b__lFlavor);
   fChain->SetBranchAddress("_lCharge", _lCharge, &b__lCharge);
   fChain->SetBranchAddress("_dxy", _dxy, &b__dxy);
   fChain->SetBranchAddress("_dz", _dz, &b__dz);
   fChain->SetBranchAddress("_3dIP", _3dIP, &b__3dIP);
   fChain->SetBranchAddress("_3dIPSig", _3dIPSig, &b__3dIPSig);
   fChain->SetBranchAddress("_lElectronMva", _lElectronMva, &b__lElectronMva);
   fChain->SetBranchAddress("_lElectronMvaHZZ", _lElectronMvaHZZ, &b__lElectronMvaHZZ);
   fChain->SetBranchAddress("_lElectronPassEmu", _lElectronPassEmu, &b__lElectronPassEmu);
   fChain->SetBranchAddress("_lElectronPassConvVeto", _lElectronPassConvVeto, &b__lElectronPassConvVeto);
   fChain->SetBranchAddress("_lElectronChargeConst", _lElectronChargeConst, &b__lElectronChargeConst);
   fChain->SetBranchAddress("_lElectronMissingHits", _lElectronMissingHits, &b__lElectronMissingHits);
   fChain->SetBranchAddress("_lEleIsEB", _lEleIsEB, &b__lEleIsEB);
   fChain->SetBranchAddress("_lEleIsEE", _lEleIsEE, &b__lEleIsEE);
   fChain->SetBranchAddress("_lEleSuperClusterOverP", _lEleSuperClusterOverP, &b__lEleSuperClusterOverP);
   fChain->SetBranchAddress("_lEleEcalEnergy", _lEleEcalEnergy, &b__lEleEcalEnergy);
   fChain->SetBranchAddress("_lElefull5x5SigmaIetaIeta", _lElefull5x5SigmaIetaIeta, &b__lElefull5x5SigmaIetaIeta);
   fChain->SetBranchAddress("_lEleDEtaInSeed", _lEleDEtaInSeed, &b__lEleDEtaInSeed);
   fChain->SetBranchAddress("_lEleDeltaPhiSuperClusterTrackAtVtx", _lEleDeltaPhiSuperClusterTrackAtVtx, &b__lEleDeltaPhiSuperClusterTrackAtVtx);
   fChain->SetBranchAddress("_lElehadronicOverEm", _lElehadronicOverEm, &b__lElehadronicOverEm);
   fChain->SetBranchAddress("_lEleInvMinusPInv", _lEleInvMinusPInv, &b__lEleInvMinusPInv);
   fChain->SetBranchAddress("_eleNumberInnerHitsMissing", _eleNumberInnerHitsMissing, &b__eleNumberInnerHitsMissing);
   fChain->SetBranchAddress("_leptonMvaSUSY16", _leptonMvaSUSY16, &b__leptonMvaSUSY16);
   fChain->SetBranchAddress("_leptonMvaTTH16", _leptonMvaTTH16, &b__leptonMvaTTH16);
   fChain->SetBranchAddress("_leptonMvaSUSY17", _leptonMvaSUSY17, &b__leptonMvaSUSY17);
   fChain->SetBranchAddress("_leptonMvaTTH17", _leptonMvaTTH17, &b__leptonMvaTTH17);
   fChain->SetBranchAddress("_leptonMvatZqTTV16", _leptonMvatZqTTV16, &b__leptonMvatZqTTV16);
   fChain->SetBranchAddress("_leptonMvatZqTTV17", _leptonMvatZqTTV17, &b__leptonMvatZqTTV17);
   fChain->SetBranchAddress("_lHNLoose", _lHNLoose, &b__lHNLoose);
   fChain->SetBranchAddress("_lHNFO", _lHNFO, &b__lHNFO);
   fChain->SetBranchAddress("_lHNTight", _lHNTight, &b__lHNTight);
   fChain->SetBranchAddress("_lEwkLoose", _lEwkLoose, &b__lEwkLoose);
   fChain->SetBranchAddress("_lEwkFO", _lEwkFO, &b__lEwkFO);
   fChain->SetBranchAddress("_lEwkTight", _lEwkTight, &b__lEwkTight);
   fChain->SetBranchAddress("_lPOGVeto", _lPOGVeto, &b__lPOGVeto);
   fChain->SetBranchAddress("_lPOGLoose", _lPOGLoose, &b__lPOGLoose);
   fChain->SetBranchAddress("_lPOGMedium", _lPOGMedium, &b__lPOGMedium);
   fChain->SetBranchAddress("_lPOGTight", _lPOGTight, &b__lPOGTight);
   fChain->SetBranchAddress("_lPOGLooseWOIso", _lPOGLooseWOIso, &b__lPOGLooseWOIso);
   fChain->SetBranchAddress("_lPOGMediumWOIso", _lPOGMediumWOIso, &b__lPOGMediumWOIso);
   fChain->SetBranchAddress("_lPOGTightWOIso", _lPOGTightWOIso, &b__lPOGTightWOIso);
   fChain->SetBranchAddress("_tauMuonVeto", _tauMuonVeto, &b__tauMuonVeto);
   fChain->SetBranchAddress("_tauEleVeto", _tauEleVeto, &b__tauEleVeto);
   fChain->SetBranchAddress("_decayModeFindingNew", _decayModeFindingNew, &b__decayModeFindingNew);
   fChain->SetBranchAddress("_tauVLooseMvaNew", _tauVLooseMvaNew, &b__tauVLooseMvaNew);
   fChain->SetBranchAddress("_tauLooseMvaNew", _tauLooseMvaNew, &b__tauLooseMvaNew);
   fChain->SetBranchAddress("_tauMediumMvaNew", _tauMediumMvaNew, &b__tauMediumMvaNew);
   fChain->SetBranchAddress("_tauTightMvaNew", _tauTightMvaNew, &b__tauTightMvaNew);
   fChain->SetBranchAddress("_tauVTightMvaNew", _tauVTightMvaNew, &b__tauVTightMvaNew);
   fChain->SetBranchAddress("_tauVTightMvaOld", _tauVTightMvaOld, &b__tauVTightMvaOld);
   fChain->SetBranchAddress("_relIso", _relIso, &b__relIso);
   fChain->SetBranchAddress("_relIso0p4", _relIso0p4, &b__relIso0p4);
   fChain->SetBranchAddress("_relIso0p4MuDeltaBeta", _relIso0p4MuDeltaBeta, &b__relIso0p4MuDeltaBeta);
   fChain->SetBranchAddress("_miniIso", _miniIso, &b__miniIso);
   fChain->SetBranchAddress("_miniIsoCharged", _miniIsoCharged, &b__miniIsoCharged);
   fChain->SetBranchAddress("_ptRel", _ptRel, &b__ptRel);
   fChain->SetBranchAddress("_ptRatio", _ptRatio, &b__ptRatio);
   fChain->SetBranchAddress("_closestJetCsvV2", _closestJetCsvV2, &b__closestJetCsvV2);
   fChain->SetBranchAddress("_closestJetDeepCsv_b", _closestJetDeepCsv_b, &b__closestJetDeepCsv_b);
   fChain->SetBranchAddress("_closestJetDeepCsv_bb", _closestJetDeepCsv_bb, &b__closestJetDeepCsv_bb);
   fChain->SetBranchAddress("_selectedTrackMult", _selectedTrackMult, &b__selectedTrackMult);
   fChain->SetBranchAddress("_lKVF_valid", _lKVF_valid, &b__lKVF_valid);
   fChain->SetBranchAddress("_lKVF_x", _lKVF_x, &b__lKVF_x);
   fChain->SetBranchAddress("_lKVF_y", _lKVF_y, &b__lKVF_y);
   fChain->SetBranchAddress("_lKVF_z", _lKVF_z, &b__lKVF_z);
   fChain->SetBranchAddress("_lKVF_cxx", _lKVF_cxx, &b__lKVF_cxx);
   fChain->SetBranchAddress("_lKVF_cyy", _lKVF_cyy, &b__lKVF_cyy);
   fChain->SetBranchAddress("_lKVF_czz", _lKVF_czz, &b__lKVF_czz);
   fChain->SetBranchAddress("_lKVF_cyx", _lKVF_cyx, &b__lKVF_cyx);
   fChain->SetBranchAddress("_lKVF_czy", _lKVF_czy, &b__lKVF_czy);
   fChain->SetBranchAddress("_lKVF_czx", _lKVF_czx, &b__lKVF_czx);
   fChain->SetBranchAddress("_lKVF_df", _lKVF_df, &b__lKVF_df);
   fChain->SetBranchAddress("_lKVF_chi2", _lKVF_chi2, &b__lKVF_chi2);
   fChain->SetBranchAddress("_lKVF_ntracks", _lKVF_ntracks, &b__lKVF_ntracks);
   fChain->SetBranchAddress("_lKVF_dRcut", _lKVF_dRcut, &b__lKVF_dRcut);
   fChain->SetBranchAddress("_lKVF_trackPt", _lKVF_trackPt, &b__lKVF_trackPt);
   fChain->SetBranchAddress("_lKVF_trackEta", _lKVF_trackEta, &b__lKVF_trackEta);
   fChain->SetBranchAddress("_lKVF_trackPhi", _lKVF_trackPhi, &b__lKVF_trackPhi);
   fChain->SetBranchAddress("_lKVF_trackE", _lKVF_trackE, &b__lKVF_trackE);
   fChain->SetBranchAddress("_lKVF_trackdR", _lKVF_trackdR, &b__lKVF_trackdR);
   fChain->SetBranchAddress("_lKVF_trackdxy", _lKVF_trackdxy, &b__lKVF_trackdxy);
   fChain->SetBranchAddress("_lKVF_trackdz", _lKVF_trackdz, &b__lKVF_trackdz);
   fChain->SetBranchAddress("_IVF_nvertex", &_IVF_nvertex, &b__IVF_nvertex); //FIX THIS
   fChain->SetBranchAddress("_IVF_x", _IVF_x, &b__IVF_x);
   fChain->SetBranchAddress("_IVF_y", _IVF_y, &b__IVF_y);
   fChain->SetBranchAddress("_IVF_z", _IVF_z, &b__IVF_z);
   fChain->SetBranchAddress("_IVF_cx", _IVF_cx, &b__IVF_cx);
   fChain->SetBranchAddress("_IVF_cy", _IVF_cy, &b__IVF_cy);
   fChain->SetBranchAddress("_IVF_cz", _IVF_cz, &b__IVF_cz);
   fChain->SetBranchAddress("_IVF_df", _IVF_df, &b__IVF_df);
   fChain->SetBranchAddress("_IVF_chi2", _IVF_chi2, &b__IVF_chi2);
   fChain->SetBranchAddress("_IVF_ntracks", _IVF_ntracks, &b__IVF_ntracks);
   fChain->SetBranchAddress("_IVF_trackpt", _IVF_trackpt, &b__IVF_trackpt);
   fChain->SetBranchAddress("_IVF_tracketa", _IVF_tracketa, &b__IVF_tracketa);
   fChain->SetBranchAddress("_IVF_trackphi", _IVF_trackphi, &b__IVF_trackphi);
   fChain->SetBranchAddress("_IVF_trackE", _IVF_trackE, &b__IVF_trackE);
   fChain->SetBranchAddress("_IVF_trackcharge", _IVF_trackcharge, &b__IVF_trackcharge);
   fChain->SetBranchAddress("_lIVF_match", _lIVF_match, &b__lIVF_match);
   fChain->SetBranchAddress("_lGlobalMuon", _lGlobalMuon, &b__lGlobalMuon);
   fChain->SetBranchAddress("_lTrackerMuon", _lTrackerMuon, &b__lTrackerMuon);
   fChain->SetBranchAddress("_lInnerTrackValidFraction", _lInnerTrackValidFraction, &b__lInnerTrackValidFraction);
   fChain->SetBranchAddress("_lGlobalTrackNormalizedChi2", _lGlobalTrackNormalizedChi2, &b__lGlobalTrackNormalizedChi2);
   fChain->SetBranchAddress("_lCQChi2Position", _lCQChi2Position, &b__lCQChi2Position);
   fChain->SetBranchAddress("_lCQTrackKink", _lCQTrackKink, &b__lCQTrackKink);
   fChain->SetBranchAddress("_lNumberOfMatchedStation", _lNumberOfMatchedStation, &b__lNumberOfMatchedStation);
   fChain->SetBranchAddress("_lNumberOfValidPixelHits", _lNumberOfValidPixelHits, &b__lNumberOfValidPixelHits);
   fChain->SetBranchAddress("_muNumberInnerHits", _muNumberInnerHits, &b__muNumberInnerHits);
   fChain->SetBranchAddress("_lTrackerLayersWithMeasurement", _lTrackerLayersWithMeasurement, &b__lTrackerLayersWithMeasurement);
   fChain->SetBranchAddress("_lMuonSegComp", _lMuonSegComp, &b__lMuonSegComp);
   fChain->SetBranchAddress("_lMuonTrackPt", _lMuonTrackPt, &b__lMuonTrackPt);
   fChain->SetBranchAddress("_lMuonTrackPtErr", _lMuonTrackPtErr, &b__lMuonTrackPtErr);
   fChain->SetBranchAddress("_lIsPrompt", _lIsPrompt, &b__lIsPrompt);
   fChain->SetBranchAddress("_lMatchPdgId", _lMatchPdgId, &b__lMatchPdgId);
   fChain->SetBranchAddress("_nPh", &_nPh, &b__nPh);
   fChain->SetBranchAddress("_phPt", _phPt, &b__phPt);
   fChain->SetBranchAddress("_phEta", _phEta, &b__phEta);
   fChain->SetBranchAddress("_phEtaSC", _phEtaSC, &b__phEtaSC);
   fChain->SetBranchAddress("_phPhi", _phPhi, &b__phPhi);
   fChain->SetBranchAddress("_phE", _phE, &b__phE);
   fChain->SetBranchAddress("_phCutBasedLoose", _phCutBasedLoose, &b__phCutBasedLoose);
   fChain->SetBranchAddress("_phCutBasedMedium", _phCutBasedMedium, &b__phCutBasedMedium);
   fChain->SetBranchAddress("_phCutBasedTight", _phCutBasedTight, &b__phCutBasedTight);
   fChain->SetBranchAddress("_phMva", _phMva, &b__phMva);
   fChain->SetBranchAddress("_phRandomConeChargedIsolation", _phRandomConeChargedIsolation, &b__phRandomConeChargedIsolation);
   fChain->SetBranchAddress("_phChargedIsolation", _phChargedIsolation, &b__phChargedIsolation);
   fChain->SetBranchAddress("_phNeutralHadronIsolation", _phNeutralHadronIsolation, &b__phNeutralHadronIsolation);
   fChain->SetBranchAddress("_phPhotonIsolation", _phPhotonIsolation, &b__phPhotonIsolation);
   fChain->SetBranchAddress("_phSigmaIetaIeta", _phSigmaIetaIeta, &b__phSigmaIetaIeta);
   fChain->SetBranchAddress("_phSigmaIetaIphi", _phSigmaIetaIphi, &b__phSigmaIetaIphi);
   fChain->SetBranchAddress("_phHadronicOverEm", _phHadronicOverEm, &b__phHadronicOverEm);
   fChain->SetBranchAddress("_phPassElectronVeto", _phPassElectronVeto, &b__phPassElectronVeto);
   fChain->SetBranchAddress("_phHasPixelSeed", _phHasPixelSeed, &b__phHasPixelSeed);
   fChain->SetBranchAddress("_phIsPrompt", _phIsPrompt, &b__phIsPrompt);
   fChain->SetBranchAddress("_phMatchMCPhotonAN15165", _phMatchMCPhotonAN15165, &b__phMatchMCPhotonAN15165);
   fChain->SetBranchAddress("_phMatchMCLeptonAN15165", _phMatchMCLeptonAN15165, &b__phMatchMCLeptonAN15165);
   fChain->SetBranchAddress("_phMatchPdgId", _phMatchPdgId, &b__phMatchPdgId);
   fChain->SetBranchAddress("_nJets", &_nJets, &b__nJets);
   fChain->SetBranchAddress("_jetPt", _jetPt, &b__jetPt);
   fChain->SetBranchAddress("_jetPt_JECUp", _jetPt_JECUp, &b__jetPt_JECUp);
   fChain->SetBranchAddress("_jetPt_JECDown", _jetPt_JECDown, &b__jetPt_JECDown);
   fChain->SetBranchAddress("_jetPt_Uncorrected", _jetPt_Uncorrected, &b__jetPt_Uncorrected);
   fChain->SetBranchAddress("_jetPt_L1", _jetPt_L1, &b__jetPt_L1);
   fChain->SetBranchAddress("_jetPt_L2", _jetPt_L2, &b__jetPt_L2);
   fChain->SetBranchAddress("_jetPt_L3", _jetPt_L3, &b__jetPt_L3);
   fChain->SetBranchAddress("_jetEta", _jetEta, &b__jetEta);
   fChain->SetBranchAddress("_jetPhi", _jetPhi, &b__jetPhi);
   fChain->SetBranchAddress("_jetE", _jetE, &b__jetE);
   fChain->SetBranchAddress("_jetCsvV2", _jetCsvV2, &b__jetCsvV2);
   fChain->SetBranchAddress("_jetDeepCsv_udsg", _jetDeepCsv_udsg, &b__jetDeepCsv_udsg);
   fChain->SetBranchAddress("_jetDeepCsv_b", _jetDeepCsv_b, &b__jetDeepCsv_b);
   fChain->SetBranchAddress("_jetDeepCsv_c", _jetDeepCsv_c, &b__jetDeepCsv_c);
   fChain->SetBranchAddress("_jetDeepCsv_bb", _jetDeepCsv_bb, &b__jetDeepCsv_bb);
   fChain->SetBranchAddress("_jetHadronFlavor", _jetHadronFlavor, &b__jetHadronFlavor);
   fChain->SetBranchAddress("_jetIsLoose", _jetIsLoose, &b__jetIsLoose);
   fChain->SetBranchAddress("_jetIsTight", _jetIsTight, &b__jetIsTight);
   fChain->SetBranchAddress("_jetIsTightLepVeto", _jetIsTightLepVeto, &b__jetIsTightLepVeto);
   fChain->SetBranchAddress("_jetNeutralHadronFraction", _jetNeutralHadronFraction, &b__jetNeutralHadronFraction);
   fChain->SetBranchAddress("_jetChargedHadronFraction", _jetChargedHadronFraction, &b__jetChargedHadronFraction);
   fChain->SetBranchAddress("_jetNeutralEmFraction", _jetNeutralEmFraction, &b__jetNeutralEmFraction);
   fChain->SetBranchAddress("_jetChargedEmFraction", _jetChargedEmFraction, &b__jetChargedEmFraction);
   fChain->SetBranchAddress("_jetHFHadronFraction", _jetHFHadronFraction, &b__jetHFHadronFraction);
   fChain->SetBranchAddress("_jetHFEmFraction", _jetHFEmFraction, &b__jetHFEmFraction);
   fChain->SetBranchAddress("_met", &_met, &b__met);
   fChain->SetBranchAddress("_metRaw", &_metRaw, &b__metRaw);
   fChain->SetBranchAddress("_metJECDown", &_metJECDown, &b__metJECDown);
   fChain->SetBranchAddress("_metJECUp", &_metJECUp, &b__metJECUp);
   fChain->SetBranchAddress("_metUnclDown", &_metUnclDown, &b__metUnclDown);
   fChain->SetBranchAddress("_metUnclUp", &_metUnclUp, &b__metUnclUp);
   fChain->SetBranchAddress("_metPhi", &_metPhi, &b__metPhi);
   fChain->SetBranchAddress("_metRawPhi", &_metRawPhi, &b__metRawPhi);
   fChain->SetBranchAddress("_metPhiJECDown", &_metPhiJECDown, &b__metPhiJECDown);
   fChain->SetBranchAddress("_metPhiJECUp", &_metPhiJECUp, &b__metPhiJECUp);
   fChain->SetBranchAddress("_metPhiUnclDown", &_metPhiUnclDown, &b__metPhiUnclDown);
   fChain->SetBranchAddress("_metPhiUnclUp", &_metPhiUnclUp, &b__metPhiUnclUp);
   fChain->SetBranchAddress("_metSignificance", &_metSignificance, &b__metSignificance);
/*   fChain->SetBranchAddress("_nDaughters", &_nDaughters, &b__nDaughters);
   fChain->SetBranchAddress("_jet_tag_for_daughters", _jet_tag_for_daughters, &b__jet_tag_for_daughters);
   fChain->SetBranchAddress("_jet_daughter_pdgid", _jet_daughter_pdgid, &b__jet_daughter_pdgid);
   fChain->SetBranchAddress("_jet_daughter_pt", _jet_daughter_pt, &b__jet_daughter_pt);
   fChain->SetBranchAddress("_jet_daughter_eta", _jet_daughter_eta, &b__jet_daughter_eta);
   fChain->SetBranchAddress("_jet_daughter_phi", _jet_daughter_phi, &b__jet_daughter_phi);
   fChain->SetBranchAddress("_jet_daughter_energy", _jet_daughter_energy, &b__jet_daughter_energy);
*/
   Notify();
}

Bool_t full_analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void full_analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t full_analyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
