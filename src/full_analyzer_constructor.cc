//basic constructor and initializer functions
#include "../interface/full_analyzer.h"

void full_analyzer::SetSampleTypes(TString filename)
{
    _is2016 = (!_is2017 and !_is2018);

    isSignal     = filename.Contains("HeavyNeutrino_lljj_");
    isData       = filename.Contains("Run201");
    isBackground = (!isSignal and !isData);
    isUL         = filename.Contains("_UL");

    std::cout << "This is " << (isUL? "UL " : "") << (isData? "Data" : (isSignal? "MC Signal" : "MC bkg")) << " from " << (_is2017? "2017" : (_is2018? "2018" : "2016")) << std::endl;
}


LSFReader full_analyzer::get_LSFReader(TString local_dir, TString flavor, TString type_SF)
{
    TString filename_LSF = local_dir + "data/LeptonScaleFactors/";
    TString histname_LSF;
    TString pt_eta_conf;
    double pt_max;
    if(flavor == "e"){
        if(_is2017 and isUL){
            filename_LSF += "UL17_ElectronTight.root";
            histname_LSF =  "EGamma_SF2D";
            pt_eta_conf  =  "eta_pt";
            pt_max       = 500;
        }
        else if(_is2018 and isUL){
            filename_LSF += "UL18_ElectronTight.root";
            histname_LSF =  "EGamma_SF2D";
            pt_eta_conf  =  "eta_pt";
            pt_max       = 500;
        }
        else if(_is2018 and !isUL){
            filename_LSF += "2018_ElectronTight.root";
            histname_LSF =  "EGamma_SF2D";
            pt_eta_conf  =  "eta_pt";
            pt_max       = 500;
        }
    }else if(flavor == "mu"){
        if(_is2017 and isUL){
            if(type_SF == "ID"){
                filename_LSF += "RunBCDEF_UL_SF_ID.root";
                histname_LSF =  "NUM_TightID_DEN_genTracks_pt_abseta";
                pt_eta_conf  =  "pt_abseta";
                pt_max       =  120;
            }else if(type_SF == "ISO"){
                filename_LSF += "RunBCDEF_UL_SF_ISO.root";
                histname_LSF =  "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta";
                pt_eta_conf  =  "pt_abseta";
                pt_max       =  120;
            }
        }
        else if(_is2018 and isUL){
            if(type_SF == "ID"){
                filename_LSF += "RunABCD_UL18_SF_ID.root";
                histname_LSF =  "NUM_TightID_DEN_TrackerMuons_abseta_pt";
                pt_eta_conf  =  "abseta_pt";
                pt_max       =  120;
            }else if(type_SF == "ISO"){
                filename_LSF += "RunABCD_UL18_SF_ISO.root";
                histname_LSF =  "NUM_TightRelIso_DEN_TightIDandIPCut_abseta_pt";
                pt_eta_conf  =  "abseta_pt";
                pt_max       =  120;
            }
        }
        else if(_is2018 and !isUL){
            filename_LSF += "RunABCD_SF_ID.root";
            histname_LSF =  "NUM_TightID_DEN_TrackerMuons_pt_abseta";
            pt_eta_conf  =  "pt_abseta";
            pt_max       =  120;
        }
    }

    LSFReader lsfreader(filename_LSF, histname_LSF, pt_eta_conf, pt_max);
    return lsfreader;
}

PUWeightReader full_analyzer::get_PUWeightReader(TFile* input, TString local_dir){
    if(!isData){
        TH1F* nTrueInteractions = (TH1F*) input->Get("blackJackAndHookersGlobal/nTrueInteractions");
        if(!nTrueInteractions) nTrueInteractions = (TH1F*) input->Get("blackJackAndHookers/nTrueInteractions");
        PUWeightReader puweightreader(local_dir, _is2017, _is2018, nTrueInteractions);
        return puweightreader;
    }else{
        PUWeightReader puweightreader;
        return puweightreader;
    }
}

full_analyzer::full_analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.

   TH1::AddDirectory(kFALSE);//https://root.cern.ch/input-and-output

   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/displaced/HeavyNeutrino_lljj_M-5_V-0.00707106781187_e_massiveAndCKM_LO/dilep.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/displaced/HeavyNeutrino_lljj_M-5_V-0.00707106781187_e_massiveAndCKM_LO/dilep.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/displaced/HeavyNeutrino_lljj_M-5_V-0.00707106781187_e_massiveAndCKM_LO/dilep.root:/blackJackAndHookers");
      dir->GetObject("blackJackAndHookersTree",tree);

   }
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
   fChain->SetBranchAddress("_is2017", &_is2017, &b__is2017);
   fChain->SetBranchAddress("_is2018", &_is2018, &b__is2018);
   fChain->SetBranchAddress("_BS_x", &_BS_x, &b__BS_x);
   fChain->SetBranchAddress("_BS_y", &_BS_y, &b__BS_y);
   fChain->SetBranchAddress("_BS_z", &_BS_z, &b__BS_z);
   fChain->SetBranchAddress("_PV_x", &_PV_x, &b__PV_x);
   fChain->SetBranchAddress("_PV_y", &_PV_y, &b__PV_y);
   fChain->SetBranchAddress("_PV_z", &_PV_z, &b__PV_z);
   if(tree->FindBranch("_weight")){ // check if we're dealing with data or MC, can't use isData yet because it's not yet initialized
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
   }
   fChain->SetBranchAddress("_HLT_Ele27_WPTight_Gsf", &_HLT_Ele27_WPTight_Gsf, &b__HLT_Ele27_WPTight_Gsf);
   fChain->SetBranchAddress("_HLT_Ele27_WPTight_Gsf_prescale", &_HLT_Ele27_WPTight_Gsf_prescale, &b__HLT_Ele27_WPTight_Gsf_prescale);
   fChain->SetBranchAddress("_HLT_Ele32_WPTight_Gsf", &_HLT_Ele32_WPTight_Gsf, &b__HLT_Ele32_WPTight_Gsf);
   fChain->SetBranchAddress("_HLT_Ele32_WPTight_Gsf_prescale", &_HLT_Ele32_WPTight_Gsf_prescale, &b__HLT_Ele32_WPTight_Gsf_prescale);
   fChain->SetBranchAddress("_HLT_IsoMu24", &_HLT_IsoMu24, &b__HLT_IsoMu24);
   fChain->SetBranchAddress("_HLT_IsoMu24_prescale", &_HLT_IsoMu24_prescale, &b__HLT_IsoMu24_prescale);
   fChain->SetBranchAddress("_HLT_IsoTkMu24", &_HLT_IsoTkMu24, &b__HLT_IsoTkMu24);
   fChain->SetBranchAddress("_HLT_IsoTkMu24_prescale", &_HLT_IsoTkMu24_prescale, &b__HLT_IsoTkMu24_prescale);
   fChain->SetBranchAddress("_passTrigger_m", &_passTrigger_m, &b__passTrigger_m);
   fChain->SetBranchAddress("_passTrigger_mm", &_passTrigger_mm, &b__passTrigger_mm);
   fChain->SetBranchAddress("_passTrigger_e", &_passTrigger_e, &b__passTrigger_e);
   fChain->SetBranchAddress("_passTrigger_ee", &_passTrigger_ee, &b__passTrigger_ee);
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
   fChain->SetBranchAddress("_passMETFilters", &_passMETFilters, &b__passMETFilters);
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
   fChain->SetBranchAddress("_lElectronSummer16MvaGP", _lElectronSummer16MvaGP, &b__lElectronSummer16MvaGP);
   fChain->SetBranchAddress("_lElectronSummer16MvaHZZ", _lElectronSummer16MvaHZZ, &b__lElectronSummer16MvaHZZ);
   fChain->SetBranchAddress("_lElectronMvaFall17v1NoIso", _lElectronMvaFall17v1NoIso, &b__lElectronMvaFall17v1NoIso);
   fChain->SetBranchAddress("_lElectronMvaFall17Iso", _lElectronMvaFall17Iso, &b__lElectronMvaFall17Iso);
   fChain->SetBranchAddress("_lElectronMvaFall17NoIso", _lElectronMvaFall17NoIso, &b__lElectronMvaFall17NoIso);
   fChain->SetBranchAddress("_lElectronPassEmu", _lElectronPassEmu, &b__lElectronPassEmu);
   fChain->SetBranchAddress("_lElectronPassConvVeto", _lElectronPassConvVeto, &b__lElectronPassConvVeto);
   fChain->SetBranchAddress("_lElectronChargeConst", _lElectronChargeConst, &b__lElectronChargeConst);
   fChain->SetBranchAddress("_lElectronMissingHits", _lElectronMissingHits, &b__lElectronMissingHits);
   fChain->SetBranchAddress("_lElectronIsEB", _lElectronIsEB, &b__lElectronIsEB);
   fChain->SetBranchAddress("_lElectronIsEE", _lElectronIsEE, &b__lElectronIsEE);
   fChain->SetBranchAddress("_lElectronSuperClusterOverP", _lElectronSuperClusterOverP, &b__lElectronSuperClusterOverP);
   fChain->SetBranchAddress("_lElectronEcalEnergy", _lElectronEcalEnergy, &b__lElectronEcalEnergy);
   fChain->SetBranchAddress("_lElectronSigmaIetaIeta", _lElectronSigmaIetaIeta, &b__lElectronSigmaIetaIeta);
   fChain->SetBranchAddress("_lElectronDEtaInSeed", _lElectronDEtaInSeed, &b__lElectronDEtaInSeed);
   fChain->SetBranchAddress("_lElectronDeltaPhiSuperClusterTrack", _lElectronDeltaPhiSuperClusterTrack, &b__lElectronDeltaPhiSuperClusterTrack);
   fChain->SetBranchAddress("_lElectronDeltaEtaSuperClusterTrack", _lElectronDeltaEtaSuperClusterTrack, &b__lElectronDeltaEtaSuperClusterTrack);
   fChain->SetBranchAddress("_lElectronHOverE", _lElectronHOverE, &b__lElectronHOverE);
   fChain->SetBranchAddress("_lElectronEInvMinusPInv", _lElectronEInvMinusPInv, &b__lElectronEInvMinusPInv);
   fChain->SetBranchAddress("_lElectronNumberInnerHitsMissing", _lElectronNumberInnerHitsMissing, &b__lElectronNumberInnerHitsMissing);
   fChain->SetBranchAddress("_leptonMvatZq", _leptonMvatZq, &b__leptonMvatZq);
   fChain->SetBranchAddress("_leptonMvaTTH", _leptonMvaTTH, &b__leptonMvaTTH);
   fChain->SetBranchAddress("_leptonMvaTOP", _leptonMvaTOP, &b__leptonMvaTOP);
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
   fChain->SetBranchAddress("_closestJetDeepCsv", _closestJetDeepCsv, &b__closestJetDeepCsv);
   fChain->SetBranchAddress("_closestJetDeepFlavor_b", _closestJetDeepFlavor_b, &b__closestJetDeepFlavor_b);
   fChain->SetBranchAddress("_closestJetDeepFlavor_bb", _closestJetDeepFlavor_bb, &b__closestJetDeepFlavor_bb);
   fChain->SetBranchAddress("_closestJetDeepFlavor_lepb", _closestJetDeepFlavor_lepb, &b__closestJetDeepFlavor_lepb);
   fChain->SetBranchAddress("_closestJetDeepFlavor", _closestJetDeepFlavor, &b__closestJetDeepFlavor);
   fChain->SetBranchAddress("_selectedTrackMult", _selectedTrackMult, &b__selectedTrackMult);
   fChain->SetBranchAddress("_lGlobalMuon", _lGlobalMuon, &b__lGlobalMuon);
   fChain->SetBranchAddress("_lTrackerMuon", _lTrackerMuon, &b__lTrackerMuon);
   fChain->SetBranchAddress("_lInnerTrackValidFraction", _lInnerTrackValidFraction, &b__lInnerTrackValidFraction);
   fChain->SetBranchAddress("_lGlobalTrackNormalizedChi2", _lGlobalTrackNormalizedChi2, &b__lGlobalTrackNormalizedChi2);
   fChain->SetBranchAddress("_lCQChi2Position", _lCQChi2Position, &b__lCQChi2Position);
   fChain->SetBranchAddress("_lCQTrackKink", _lCQTrackKink, &b__lCQTrackKink);
   fChain->SetBranchAddress("_lNumberOfMatchedStation", _lNumberOfMatchedStation, &b__lNumberOfMatchedStation);
   fChain->SetBranchAddress("_lNumberOfValidPixelHits", _lNumberOfValidPixelHits, &b__lNumberOfValidPixelHits);
   fChain->SetBranchAddress("_lNumberOfValidTrackerHits", _lNumberOfValidTrackerHits, &b__lNumberOfValidTrackerHits);
   fChain->SetBranchAddress("_muNumberInnerHits", _muNumberInnerHits, &b__muNumberInnerHits);
   fChain->SetBranchAddress("_lTrackerLayersWithMeasurement", _lTrackerLayersWithMeasurement, &b__lTrackerLayersWithMeasurement);
   fChain->SetBranchAddress("_lMuonSegComp", _lMuonSegComp, &b__lMuonSegComp);
   fChain->SetBranchAddress("_lMuonTrackPt", _lMuonTrackPt, &b__lMuonTrackPt);
   fChain->SetBranchAddress("_lMuonTrackPtErr", _lMuonTrackPtErr, &b__lMuonTrackPtErr);
   fChain->SetBranchAddress("_lMuonTimenDof", _lMuonTimenDof, &b__lMuonTimenDof);
   fChain->SetBranchAddress("_lMuonTime", _lMuonTime, &b__lMuonTime);
   fChain->SetBranchAddress("_lMuonTimeErr", _lMuonTimeErr, &b__lMuonTimeErr);
   fChain->SetBranchAddress("_lMuonRPCTimenDof", _lMuonRPCTimenDof, &b__lMuonRPCTimenDof);
   fChain->SetBranchAddress("_lMuonRPCTime", _lMuonRPCTime, &b__lMuonRPCTime);
   fChain->SetBranchAddress("_lMuonRPCTimeErr", _lMuonRPCTimeErr, &b__lMuonRPCTimeErr);
   if(tree->FindBranch("_weight")){ // check if we're dealing with data or MC, can't use isData yet because it's not yet initialized
        fChain->SetBranchAddress("_lIsPrompt", _lIsPrompt, &b__lIsPrompt);
        fChain->SetBranchAddress("_lMatchPdgId", _lMatchPdgId, &b__lMatchPdgId);
        fChain->SetBranchAddress("_lMatchCharge", _lMatchCharge, &b__lMatchCharge);
        fChain->SetBranchAddress("_tauGenStatus", _tauGenStatus, &b__tauGenStatus);
        fChain->SetBranchAddress("_lMomPdgId", _lMomPdgId, &b__lMomPdgId);
        fChain->SetBranchAddress("_lProvenance", _lProvenance, &b__lProvenance);
        fChain->SetBranchAddress("_lProvenanceCompressed", _lProvenanceCompressed, &b__lProvenanceCompressed);
        fChain->SetBranchAddress("_lProvenanceConversion", _lProvenanceConversion, &b__lProvenanceConversion);
   }
   //fChain->SetBranchAddress("_nPh", &_nPh, &b__nPh);
   //fChain->SetBranchAddress("_phPt", _phPt, &b__phPt);
   //fChain->SetBranchAddress("_phEta", _phEta, &b__phEta);
   //fChain->SetBranchAddress("_phEtaSC", _phEtaSC, &b__phEtaSC);
   //fChain->SetBranchAddress("_phPhi", _phPhi, &b__phPhi);
   //fChain->SetBranchAddress("_phE", _phE, &b__phE);
   //fChain->SetBranchAddress("_phCutBasedLoose", _phCutBasedLoose, &b__phCutBasedLoose);
   //fChain->SetBranchAddress("_phCutBasedMedium", _phCutBasedMedium, &b__phCutBasedMedium);
   //fChain->SetBranchAddress("_phCutBasedTight", _phCutBasedTight, &b__phCutBasedTight);
   //fChain->SetBranchAddress("_phMva", _phMva, &b__phMva);
   //fChain->SetBranchAddress("_phRandomConeChargedIsolation", _phRandomConeChargedIsolation, &b__phRandomConeChargedIsolation);
   //fChain->SetBranchAddress("_phChargedIsolation", _phChargedIsolation, &b__phChargedIsolation);
   //fChain->SetBranchAddress("_phNeutralHadronIsolation", _phNeutralHadronIsolation, &b__phNeutralHadronIsolation);
   //fChain->SetBranchAddress("_phPhotonIsolation", _phPhotonIsolation, &b__phPhotonIsolation);
   //fChain->SetBranchAddress("_phSigmaIetaIeta", _phSigmaIetaIeta, &b__phSigmaIetaIeta);
   //fChain->SetBranchAddress("_phHadronicOverEm", _phHadronicOverEm, &b__phHadronicOverEm);
   //fChain->SetBranchAddress("_phPassElectronVeto", _phPassElectronVeto, &b__phPassElectronVeto);
   //fChain->SetBranchAddress("_phHasPixelSeed", _phHasPixelSeed, &b__phHasPixelSeed);
   //fChain->SetBranchAddress("_phIsPrompt", _phIsPrompt, &b__phIsPrompt);
   //fChain->SetBranchAddress("_phMatchPdgId", _phMatchPdgId, &b__phMatchPdgId);
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
   fChain->SetBranchAddress("_jetDeepCsv", &_jetDeepCsv, &b__jetDeepCsv);
   fChain->SetBranchAddress("_jetDeepFlavor_b", &_jetDeepFlavor_b, &b__jetDeepFlavor_b);
   fChain->SetBranchAddress("_jetDeepFlavor_bb", &_jetDeepFlavor_bb, &b__jetDeepFlavor_bb);
   fChain->SetBranchAddress("_jetDeepFlavor_lepb", &_jetDeepFlavor_lepb, &b__jetDeepFlavor_lepb);
   fChain->SetBranchAddress("_jetDeepFlavor", &_jetDeepFlavor, &b__jetDeepFlavor);
   fChain->SetBranchAddress("_jetDeepFlavor_c", &_jetDeepFlavor_c, &b__jetDeepFlavor_c);
   fChain->SetBranchAddress("_jetDeepFlavor_uds", &_jetDeepFlavor_uds, &b__jetDeepFlavor_uds);
   fChain->SetBranchAddress("_jetDeepFlavor_g", &_jetDeepFlavor_g, &b__jetDeepFlavor_g);
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
   fChain->SetBranchAddress("_nJetConstituents", _nJetConstituents, &b__nJetConstituents);
   fChain->SetBranchAddress("_JetConstituentPt", _JetConstituentPt, &b__JetConstituentPt);
   fChain->SetBranchAddress("_JetConstituentEta", _JetConstituentEta, &b__JetConstituentEta);
   fChain->SetBranchAddress("_JetConstituentPhi", _JetConstituentPhi, &b__JetConstituentPhi);
   fChain->SetBranchAddress("_JetConstituentMass", _JetConstituentMass, &b__JetConstituentMass);
   fChain->SetBranchAddress("_JetConstituentPdgId", _JetConstituentPdgId, &b__JetConstituentPdgId);
   fChain->SetBranchAddress("_JetConstituentCharge", _JetConstituentCharge, &b__JetConstituentCharge);
   fChain->SetBranchAddress("_JetConstituentdxy", _JetConstituentdxy, &b__JetConstituentdxy);
   fChain->SetBranchAddress("_JetConstituentdz", _JetConstituentdz, &b__JetConstituentdz);
   fChain->SetBranchAddress("_JetConstituentdxyErr", _JetConstituentdxyErr, &b__JetConstituentdxyErr);
   fChain->SetBranchAddress("_JetConstituentdzErr", _JetConstituentdzErr, &b__JetConstituentdzErr);
   fChain->SetBranchAddress("_JetConstituentNumberOfHits", _JetConstituentNumberOfHits, &b__JetConstituentNumberOfHits);
   fChain->SetBranchAddress("_JetConstituentNumberOfPixelHits", _JetConstituentNumberOfPixelHits, &b__JetConstituentNumberOfPixelHits);
   fChain->SetBranchAddress("_JetConstituentHasTrack", _JetConstituentHasTrack, &b__JetConstituentHasTrack);
   fChain->SetBranchAddress("_nJetsPuppi", &_nJetsPuppi, &b__nJetsPuppi);
   fChain->SetBranchAddress("_jetPuppiPt", _jetPuppiPt, &b__jetPuppiPt);
   fChain->SetBranchAddress("_jetPuppiEta", _jetPuppiEta, &b__jetPuppiEta);
   fChain->SetBranchAddress("_jetPuppiPhi", _jetPuppiPhi, &b__jetPuppiPhi);
   fChain->SetBranchAddress("_jetPuppiPt_JECUp", _jetPuppiPt_JECUp, &b__jetPuppiPt_JECUp);
   fChain->SetBranchAddress("_jetPuppiPt_JECDown", _jetPuppiPt_JECDown, &b__jetPuppiPt_JECDown);
   fChain->SetBranchAddress("_met", &_met, &b__met);
   fChain->SetBranchAddress("_metType1", &_metType1, &b__metType1);
   fChain->SetBranchAddress("_metRaw", &_metRaw, &b__metRaw);
   fChain->SetBranchAddress("_metJECDown", &_metJECDown, &b__metJECDown);
   fChain->SetBranchAddress("_metJECUp", &_metJECUp, &b__metJECUp);
   fChain->SetBranchAddress("_metUnclDown", &_metUnclDown, &b__metUnclDown);
   fChain->SetBranchAddress("_metUnclUp", &_metUnclUp, &b__metUnclUp);
   fChain->SetBranchAddress("_metResDown", &_metResDown, &b__metResDown);
   fChain->SetBranchAddress("_metResUp", &_metResUp, &b__metResUp);
   fChain->SetBranchAddress("_metPhi", &_metPhi, &b__metPhi);
   fChain->SetBranchAddress("_metType1Phi", &_metType1Phi, &b__metType1Phi);
   fChain->SetBranchAddress("_metRawPhi", &_metRawPhi, &b__metRawPhi);
   fChain->SetBranchAddress("_metPhiJECDown", &_metPhiJECDown, &b__metPhiJECDown);
   fChain->SetBranchAddress("_metPhiJECUp", &_metPhiJECUp, &b__metPhiJECUp);
   fChain->SetBranchAddress("_metPhiUnclDown", &_metPhiUnclDown, &b__metPhiUnclDown);
   fChain->SetBranchAddress("_metPhiUnclUp", &_metPhiUnclUp, &b__metPhiUnclUp);
   fChain->SetBranchAddress("_metPhiResDown", &_metPhiResDown, &b__metPhiResDown);
   fChain->SetBranchAddress("_metPhiResUp", &_metPhiResUp, &b__metPhiResUp);
   fChain->SetBranchAddress("_metSignificance", &_metSignificance, &b__metSignificance);
   fChain->SetBranchAddress("_metPuppi", &_metPuppi, &b__metPuppi);
   fChain->SetBranchAddress("_metPuppiRaw", &_metPuppiRaw, &b__metPuppiRaw);
   fChain->SetBranchAddress("_metPuppiJECDown", &_metPuppiJECDown, &b__metPuppiJECDown);
   fChain->SetBranchAddress("_metPuppiJECUp", &_metPuppiJECUp, &b__metPuppiJECUp);
   fChain->SetBranchAddress("_metPuppiUnclDown", &_metPuppiUnclDown, &b__metPuppiUnclDown);
   fChain->SetBranchAddress("_metPuppiUnclUp", &_metPuppiUnclUp, &b__metPuppiUnclUp);
   fChain->SetBranchAddress("_metPuppiResDown", &_metPuppiResDown, &b__metPuppiResDown);
   fChain->SetBranchAddress("_metPuppiResUp", &_metPuppiResUp, &b__metPuppiResUp);
   fChain->SetBranchAddress("_metPuppiPhi", &_metPuppiPhi, &b__metPuppiPhi);
   fChain->SetBranchAddress("_metPuppiRawPhi", &_metPuppiRawPhi, &b__metPuppiRawPhi);
   fChain->SetBranchAddress("_metPuppiPhiJECDown", &_metPuppiPhiJECDown, &b__metPuppiPhiJECDown);
   fChain->SetBranchAddress("_metPuppiPhiJECUp", &_metPuppiPhiJECUp, &b__metPuppiPhiJECUp);
   fChain->SetBranchAddress("_metPuppiPhiUnclDown", &_metPuppiPhiUnclDown, &b__metPuppiPhiUnclDown);
   fChain->SetBranchAddress("_metPuppiPhiUnclUp", &_metPuppiPhiUnclUp, &b__metPuppiPhiUnclUp);
   fChain->SetBranchAddress("_metPuppiPhiResDown", &_metPuppiPhiResDown, &b__metPuppiPhiResDown);
   fChain->SetBranchAddress("_metPuppiPhiResUp", &_metPuppiPhiResUp, &b__metPuppiPhiResUp);
}

void full_analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
