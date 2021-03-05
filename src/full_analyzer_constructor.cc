//basic constructor and initializer functions
#include "../interface/full_analyzer.h"

void full_analyzer::SetSampleTypes(TString filename)
{
    _is2016 = (!_is2017 and !_is2018);

    isSignal     = filename.Contains("HeavyNeutrino_lljj_");
    isData       = filename.Contains("Run201");
    isSingleElectron = isData and (filename.Contains("SingleElectron") or filename.Contains("EGamma"));
    isSingleMuon     = isData and filename.Contains("SingleMuon");
    isMET            = isData and filename.Contains("MET");
    isBackground = (!isSignal and !isData);
    isUL         = filename.Contains("_UL");
    isDY         = filename.Contains("DY");
    isZG         = filename.Contains("ZGTo");
    isWG         = filename.Contains("WGTo");
    isWJets      = filename.Contains("WJetsToLNu");

    std::cout << "This is " << (isUL? "UL " : "") << (isData? (isSingleMuon? "Muon Data" : (isSingleElectron? "Electron Data" : (isMET? "MET Data" : "Unid. Data"))) : (isSignal? "MC Signal" : "MC bkg")) << " from " << (_is2017? "2017" : (_is2018? "2018" : "2016")) << std::endl;
}

PUWeightReader* full_analyzer::get_PUWeightReader(TFile* input){
    if(!isData){
        TH1F* nTrueInteractions = (TH1F*) input->Get("blackJackAndHookersGlobal/nTrueInteractions");
        if(!nTrueInteractions) nTrueInteractions = (TH1F*) input->Get("blackJackAndHookers/nTrueInteractions");
        PUWeightReader* puweightreader = new PUWeightReader(local_dir, _is2017, _is2018, nTrueInteractions);
        return puweightreader;
    }else{
        PUWeightReader *puweightreader = new PUWeightReader();
        return puweightreader;
    }
}

LSFReader* full_analyzer::get_LSFReader(TString flavor, TString type_SF)
{
    TString filename_LSF = local_dir + "data/LeptonScaleFactors/";
    TString histname_LSF = "", histname_sys = "";
    TString pt_eta_config;
    if(flavor == "e" and type_SF == "ID"){
        if(_is2016) filename_LSF += "ID_egammaEffi.txt_EGM2D_16.root";
        if(_is2017) filename_LSF += "ID_egammaEffi.txt_EGM2D_17.root";
        if(_is2018) filename_LSF += "ID_egammaEffi.txt_EGM2D_18.root";
        histname_LSF  = "EGamma_SF2D";
        histname_sys  = "";
        pt_eta_config = "eta_pt";
    }else if(flavor == "mu" and type_SF == "ID"){
        if(_is2016){
            filename_LSF += "EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SYS_ID.root";
            histname_LSF  = "NUM_MediumID_DEN_genTracks_eta_pt";
            histname_sys  = "";
            pt_eta_config = "eta_pt";
        }
        if(_is2017){
            filename_LSF += "RunBCDEF_SF_ID_syst.root";
            histname_LSF  = "NUM_MediumID_DEN_genTracks_pt_abseta";
            histname_sys  = "NUM_MediumID_DEN_genTracks_pt_abseta_syst";
            pt_eta_config = "pt_abseta";
        }
        if(_is2018){
            filename_LSF += "EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root";
            histname_LSF  = "NUM_MediumID_DEN_TrackerMuons_pt_abseta";
            histname_sys  = "NUM_MediumID_DEN_TrackerMuons_pt_abseta_syst";
            pt_eta_config = "pt_abseta";
        }
    }else if(flavor == "mu" and type_SF == "IDsys"){
        if(_is2016){
            filename_LSF += "EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SYS_ID.root";
            histname_LSF  = "";
            histname_sys  = "NUM_MediumID_DEN_genTracks_eta_pt";
            pt_eta_config = "eta_pt";
        }
        if(_is2017){
            filename_LSF += "RunBCDEF_SF_ID_syst.root";
            histname_LSF  = "NUM_MediumID_DEN_genTracks_pt_abseta";
            histname_sys  = "NUM_MediumID_DEN_genTracks_pt_abseta_syst";
            pt_eta_config = "pt_abseta";
        }
        if(_is2018){
            filename_LSF += "EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root";
            histname_LSF  = "NUM_MediumID_DEN_TrackerMuons_pt_abseta";
            histname_sys  = "NUM_MediumID_DEN_TrackerMuons_pt_abseta_syst";
            pt_eta_config = "pt_abseta";
        }
    }else if(flavor == "mu" and type_SF == "ISO"){
        if(_is2016) filename_LSF += "Iso_ip_NUM_displacedIsoIP_DEN_displaced_abseta_pt_16.root";
        if(_is2017) filename_LSF += "Iso_ip_NUM_displacedIsoIP_DEN_displaced_abseta_pt_17.root";
        if(_is2018) filename_LSF += "Iso_ip_NUM_displacedIsoIP_DEN_displaced_abseta_pt_18.root";
        histname_LSF  = "NUM_displacedIsoIP_DEN_displaced_abseta_pt";
        histname_sys  = "NUM_displacedIsoIP_DEN_displaced_abseta_pt_combined_syst";
        pt_eta_config = "abseta_pt";
    }else if(flavor == "e" and type_SF == "Trigger"){
        if(_is2016) filename_LSF += "trigger_egammaEffi.txt_EGM2D_16.root";
        if(_is2017) filename_LSF += "trigger_egammaEffi.txt_EGM2D_17.root";
        if(_is2018) filename_LSF += "trigger_egammaEffi.txt_EGM2D_18.root";
        histname_LSF  = "EGamma_SF2D";
        histname_sys  = "";
        pt_eta_config = "eta_pt";
    }else if(flavor == "mu" and type_SF == "Trigger"){
        if(_is2016){
            filename_LSF += "EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunBtoF.root";
            histname_LSF  = "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio";
            histname_sys  = "";
            pt_eta_config = "abseta_pt";
        }
        if(_is2017){
            filename_LSF += "EfficienciesStudies_2017_trigger_EfficienciesAndSF_RunBtoF_Nov17Nov2017.root";
            histname_LSF  = "IsoMu27_PtEtaBins/abseta_pt_ratio";
            histname_sys  = "";
            pt_eta_config = "abseta_pt";
        }
        if(_is2018){
            filename_LSF += "EfficienciesStudies_2018_trigger_EfficienciesAndSF_2018Data_AfterMuonHLTUpdate.root";
            histname_LSF  = "IsoMu24_PtEtaBins/abseta_pt_ratio";
            histname_sys  = "";
            pt_eta_config = "abseta_pt";
        }
    }
    LSFReader *lsfreader = new LSFReader(filename_LSF, histname_LSF, histname_sys, pt_eta_config);
    return lsfreader;
}

LSFReader* full_analyzer::get_LSFReader_displ(TString flavor, TString type_SF)
{
    TString filename_LSF = local_dir + "data/LeptonScaleFactors/displacedSF/";
    TString histname_LSF = "", histname_sys = "";
    TString pt_eta_config;
    if(flavor == "mu" and type_SF == "SV"){
        if(_is2016) filename_LSF += "SV_SF_16.root";
        if(_is2017) filename_LSF += "SV_SF_17.root";
        if(_is2018) filename_LSF += "SV_SF_18.root";
        histname_LSF  = "SV_SF_lxy_pt";
        histname_sys  = "";
        pt_eta_config = "lxy_pt";
    }else if(flavor == "mu" and type_SF == "IDISO"){
        if(_is2016) filename_LSF += "NUM_displacedIso_DEN_trackerMuons_abseta_pt_16.root";
        if(_is2017) filename_LSF += "NUM_displacedIso_DEN_trackerMuons_abseta_pt_17.root";
        if(_is2018) filename_LSF += "NUM_displacedIso_DEN_trackerMuons_abseta_pt_18.root";
        histname_LSF  = "NUM_displacedIso_DEN_trackerMuons_abseta_pt";
        histname_sys  = "NUM_displacedIso_DEN_trackerMuons_abseta_pt_combined_syst";
        pt_eta_config = "abseta_pt";
    }
    LSFReader *lsfreader = new LSFReader(filename_LSF, histname_LSF, histname_sys, pt_eta_config);
    return lsfreader;
}

PFNReader full_analyzer::get_PFNReader(int flavor)
{
    unsigned highlevel_shape = 25;
    std::pair<unsigned, unsigned> pfn_shape = {50, 13};
    std::string PFN_filename;
    if(flavor == 0){//electron
        if(_is2016) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNe_2016_v8/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
        else if(_is2017 or _is2018) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNe_201718_v8/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
    }else if(flavor == 1){//muon
        if(_is2016) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNmu_2016_v8/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
        else if(_is2017 or _is2018) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNmu_201718_v8/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
    }

    PFNReader pfn(PFN_filename, highlevel_shape, pfn_shape);
    return pfn;
}


PFNReader full_analyzer::get_PFNReader_unparametrized(int flavor)
{
    unsigned highlevel_shape = 23;
    std::pair<unsigned, unsigned> pfn_shape = {50, 13};
    std::string PFN_filename;
    if(flavor == 0){//electron
        if(_is2016) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNe_2016_v8_unparametrized/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
        else if(_is2017 or _is2018) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNe_201718_v8_unparametrized/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
    }else if(flavor == 1){//muon
        if(_is2016) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNmu_2016_v8_unparametrized/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
        else if(_is2017 or _is2018) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNmu_201718_v8_unparametrized/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
    }

    PFNReader pfn(PFN_filename, highlevel_shape, pfn_shape);
    return pfn;
}


PFNReader full_analyzer::get_PFNReader_unparametrized_LowMass(int flavor)
{
    unsigned highlevel_shape = 23;
    std::pair<unsigned, unsigned> pfn_shape = {50, 13};
    std::string PFN_filename;
    if(flavor == 0){//electron
        if(_is2016) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNe_2016_v8_unparametrized_LowMass/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
        else if(_is2017 or _is2018) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNe_201718_v8_unparametrized_LowMass/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
    }else if(flavor == 1){//muon
        if(_is2016) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNmu_2016_v8_unparametrized_LowMass/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
        else if(_is2017 or _is2018) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNmu_201718_v8_unparametrized_LowMass/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
    }

    PFNReader pfn(PFN_filename, highlevel_shape, pfn_shape);
    return pfn;
}


PFNReader full_analyzer::get_PFNReader_unparametrized_HighMass(int flavor)
{
    unsigned highlevel_shape = 23;
    std::pair<unsigned, unsigned> pfn_shape = {50, 13};
    std::string PFN_filename;
    if(flavor == 0){//electron
        if(_is2016) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNe_2016_v8_unparametrized_HighMass/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
        else if(_is2017 or _is2018) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNe_201718_v8_unparametrized_HighMass/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
    }else if(flavor == 1){//muon
        if(_is2016) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNmu_2016_v8_unparametrized_HighMass/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
        else if(_is2017 or _is2018) PFN_filename = "/user/bvermass/public/PFN/JetTagger/PFN_v8/PFNmu_201718_v8_unparametrized_HighMass/dropoutLatent=0p5_dropoutOutput=0p5_hiddenLayersLatent=3_hiddenLayersOutput=3_latentSpace=256_learningRate=1_learningRateDecay=1_nodesLatent=128_nodesOutput=128/jetTagger.h5";
    }

    PFNReader pfn(PFN_filename, highlevel_shape, pfn_shape);
    return pfn;
}


full_analyzer::full_analyzer(TTree *tree, TString local_dr, bool mkHistograms, bool mkHNLtagger, bool mkBkgEstimator) : fChain(0)
    , makeHistograms(mkHistograms)
    , makeHNLtagger(mkHNLtagger)
    , makeBkgEstimator(mkBkgEstimator)
    , local_dir(local_dr)
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
        fChain->SetBranchAddress("_hasInternalConversion", &_hasInternalConversion, &b__hasInternalConversion);
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
        //fChain->SetBranchAddress("_gen_nstatus23", &_gen_nstatus23, &b__gen_nstatus23);
        //fChain->SetBranchAddress("_gen_nstatus23_fromN", &_gen_nstatus23_fromN, &b__gen_nstatus23_fromN);
        //fChain->SetBranchAddress("_gen_nstatus23_fromW", &_gen_nstatus23_fromW, &b__gen_nstatus23_fromW);
        //fChain->SetBranchAddress("_gen_status23_pdg", _gen_status23_pdg, &b__gen_status23_pdg);
        //fChain->SetBranchAddress("_gen_status23_fromN_pdg", _gen_status23_fromN_pdg, &b__gen_status23_fromN_pdg);
        //fChain->SetBranchAddress("_gen_status23_fromW_pdg", _gen_status23_fromW_pdg, &b__gen_status23_fromW_pdg);
        fChain->SetBranchAddress("_gen_nq", &_gen_nq, &b__gen_nq);
        fChain->SetBranchAddress("_gen_qPt", _gen_qPt, &b__gen_qPt);
        fChain->SetBranchAddress("_gen_qEta", _gen_qEta, &b__gen_qEta);
        fChain->SetBranchAddress("_gen_qPhi", _gen_qPhi, &b__gen_qPhi);
        fChain->SetBranchAddress("_gen_qE", _gen_qE, &b__gen_qE);
   }
   fChain->SetBranchAddress("_HLT_Ele27_WPTight_Gsf", &_HLT_Ele27_WPTight_Gsf, &b__HLT_Ele27_WPTight_Gsf);
   fChain->SetBranchAddress("_HLT_Ele27_WPTight_Gsf_prescale", &_HLT_Ele27_WPTight_Gsf_prescale, &b__HLT_Ele27_WPTight_Gsf_prescale);
   fChain->SetBranchAddress("_HLT_Ele32_WPTight_Gsf", &_HLT_Ele32_WPTight_Gsf, &b__HLT_Ele32_WPTight_Gsf);
   fChain->SetBranchAddress("_HLT_Ele32_WPTight_Gsf_prescale", &_HLT_Ele32_WPTight_Gsf_prescale, &b__HLT_Ele32_WPTight_Gsf_prescale);
   fChain->SetBranchAddress("_HLT_IsoMu24", &_HLT_IsoMu24, &b__HLT_IsoMu24);
   fChain->SetBranchAddress("_HLT_IsoMu24_prescale", &_HLT_IsoMu24_prescale, &b__HLT_IsoMu24_prescale);
   fChain->SetBranchAddress("_HLT_IsoTkMu24", &_HLT_IsoTkMu24, &b__HLT_IsoTkMu24);
   fChain->SetBranchAddress("_HLT_IsoTkMu24_prescale", &_HLT_IsoTkMu24_prescale, &b__HLT_IsoTkMu24_prescale);
   fChain->SetBranchAddress("_HLT_IsoMu27", &_HLT_IsoMu27, &b__HLT_IsoMu27);
   fChain->SetBranchAddress("_HLT_IsoMu27_prescale", &_HLT_IsoMu27_prescale, &b__HLT_IsoMu27_prescale);
   fChain->SetBranchAddress("_HLT_IsoMu24_eta2p1", &_HLT_IsoMu24_eta2p1, &b__HLT_IsoMu24_eta2p1);
   fChain->SetBranchAddress("_HLT_IsoMu24_eta2p1_prescale", &_HLT_IsoMu24_eta2p1_prescale, &b__HLT_IsoMu24_eta2p1_prescale);
   fChain->SetBranchAddress("_HLT_MET200", &_HLT_MET200, &b__HLT_MET200);
   fChain->SetBranchAddress("_HLT_MET200_prescale", &_HLT_MET200_prescale, &b__HLT_MET200_prescale);
   fChain->SetBranchAddress("_HLT_PFMET300", &_HLT_PFMET300, &b__HLT_PFMET300);
   fChain->SetBranchAddress("_HLT_PFMET300_prescale", &_HLT_PFMET300_prescale, &b__HLT_PFMET300_prescale);
   fChain->SetBranchAddress("_HLT_PFMET170_HBHECleaned", &_HLT_PFMET170_HBHECleaned, &b__HLT_PFMET170_HBHECleaned);
   fChain->SetBranchAddress("_HLT_PFMET170_HBHECleaned_prescale", &_HLT_PFMET170_HBHECleaned_prescale, &b__HLT_PFMET170_HBHECleaned_prescale);
   fChain->SetBranchAddress("_HLT_PFMET120_PFMHT120_IDTight", &_HLT_PFMET120_PFMHT120_IDTight, &b__HLT_PFMET120_PFMHT120_IDTight);
   fChain->SetBranchAddress("_HLT_PFMET120_PFMHT120_IDTight_prescale", &_HLT_PFMET120_PFMHT120_IDTight_prescale, &b__HLT_PFMET120_PFMHT120_IDTight_prescale);
   fChain->SetBranchAddress("_HLT_PFMET140_PFMHT140_IDTight", &_HLT_PFMET140_PFMHT140_IDTight, &b__HLT_PFMET140_PFMHT140_IDTight);
   fChain->SetBranchAddress("_HLT_PFMET140_PFMHT140_IDTight_prescale", &_HLT_PFMET140_PFMHT140_IDTight_prescale, &b__HLT_PFMET140_PFMHT140_IDTight_prescale);
   fChain->SetBranchAddress("_HLT_CaloMET350_HBHECleaned", &_HLT_CaloMET350_HBHECleaned, &b__HLT_CaloMET350_HBHECleaned);
   fChain->SetBranchAddress("_HLT_CaloMET350_HBHECleaned_prescale", &_HLT_CaloMET350_HBHECleaned_prescale, &b__HLT_CaloMET350_HBHECleaned_prescale);
   fChain->SetBranchAddress("_HLT_PFMET250_HBHECleaned", &_HLT_PFMET250_HBHECleaned, &b__HLT_PFMET250_HBHECleaned);
   fChain->SetBranchAddress("_HLT_PFMET250_HBHECleaned_prescale", &_HLT_PFMET250_HBHECleaned_prescale, &b__HLT_PFMET250_HBHECleaned_prescale);
   fChain->SetBranchAddress("_HLT_PFMET200_HBHE_BeamHaloCleaned", &_HLT_PFMET200_HBHE_BeamHaloCleaned, &b__HLT_PFMET200_HBHE_BeamHaloCleaned);
   fChain->SetBranchAddress("_HLT_PFMET200_HBHE_BeamHaloCleaned_prescale", &_HLT_PFMET200_HBHE_BeamHaloCleaned_prescale, &b__HLT_PFMET200_HBHE_BeamHaloCleaned_prescale);
   fChain->SetBranchAddress("_HLT_PFMETTypeOne140_PFMHT140_IDTight", &_HLT_PFMETTypeOne140_PFMHT140_IDTight, &b__HLT_PFMETTypeOne140_PFMHT140_IDTight);
   fChain->SetBranchAddress("_HLT_PFMETTypeOne140_PFMHT140_IDTight_prescale", &_HLT_PFMETTypeOne140_PFMHT140_IDTight_prescale, &b__HLT_PFMETTypeOne140_PFMHT140_IDTight_prescale);
   fChain->SetBranchAddress("_HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned", &_HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned, &b__HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned);
   fChain->SetBranchAddress("_HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_prescale", &_HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_prescale, &b__HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_prescale);
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
   //fChain->SetBranchAddress("_lKVF_valid", _lKVF_valid, &b__lKVF_valid);
   //fChain->SetBranchAddress("_lKVF_x", _lKVF_x, &b__lKVF_x);
   //fChain->SetBranchAddress("_lKVF_y", _lKVF_y, &b__lKVF_y);
   //fChain->SetBranchAddress("_lKVF_z", _lKVF_z, &b__lKVF_z);
   //fChain->SetBranchAddress("_lKVF_cxx", _lKVF_cxx, &b__lKVF_cxx);
   //fChain->SetBranchAddress("_lKVF_cyy", _lKVF_cyy, &b__lKVF_cyy);
   //fChain->SetBranchAddress("_lKVF_czz", _lKVF_czz, &b__lKVF_czz);
   //fChain->SetBranchAddress("_lKVF_cyx", _lKVF_cyx, &b__lKVF_cyx);
   //fChain->SetBranchAddress("_lKVF_czy", _lKVF_czy, &b__lKVF_czy);
   //fChain->SetBranchAddress("_lKVF_czx", _lKVF_czx, &b__lKVF_czx);
   //fChain->SetBranchAddress("_lKVF_df", _lKVF_df, &b__lKVF_df);
   //fChain->SetBranchAddress("_lKVF_chi2", _lKVF_chi2, &b__lKVF_chi2);
   //fChain->SetBranchAddress("_lKVF_ntracks", _lKVF_ntracks, &b__lKVF_ntracks);
   //fChain->SetBranchAddress("_lKVF_dRcut", _lKVF_dRcut, &b__lKVF_dRcut);
   //fChain->SetBranchAddress("_lKVF_trackPt", _lKVF_trackPt, &b__lKVF_trackPt);
   //fChain->SetBranchAddress("_lKVF_trackEta", _lKVF_trackEta, &b__lKVF_trackEta);
   //fChain->SetBranchAddress("_lKVF_trackPhi", _lKVF_trackPhi, &b__lKVF_trackPhi);
   //fChain->SetBranchAddress("_lKVF_trackE", _lKVF_trackE, &b__lKVF_trackE);
   //fChain->SetBranchAddress("_lKVF_trackdR", _lKVF_trackdR, &b__lKVF_trackdR);
   //fChain->SetBranchAddress("_lKVF_trackdxy", _lKVF_trackdxy, &b__lKVF_trackdxy);
   //fChain->SetBranchAddress("_lKVF_trackdz", _lKVF_trackdz, &b__lKVF_trackdz);
   fChain->SetBranchAddress("_IVF_x", _IVF_x, &b__IVF_x);
   fChain->SetBranchAddress("_IVF_y", _IVF_y, &b__IVF_y);
   fChain->SetBranchAddress("_IVF_z", _IVF_z, &b__IVF_z);
   fChain->SetBranchAddress("_IVF_cx", _IVF_cx, &b__IVF_cx);
   fChain->SetBranchAddress("_IVF_cy", _IVF_cy, &b__IVF_cy);
   fChain->SetBranchAddress("_IVF_cz", _IVF_cz, &b__IVF_cz);
   fChain->SetBranchAddress("_IVF_df", _IVF_df, &b__IVF_df);
   fChain->SetBranchAddress("_IVF_chi2", _IVF_chi2, &b__IVF_chi2);
   fChain->SetBranchAddress("_IVF_pt", _IVF_pt, &b__IVF_pt);
   fChain->SetBranchAddress("_IVF_eta", _IVF_eta, &b__IVF_eta);
   fChain->SetBranchAddress("_IVF_phi", _IVF_phi, &b__IVF_phi);
   fChain->SetBranchAddress("_IVF_E", _IVF_E, &b__IVF_E);
   fChain->SetBranchAddress("_IVF_mass", _IVF_mass, &b__IVF_mass);
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
   fChain->SetBranchAddress("_jetSmearedPt", _jetSmearedPt, &b__jetSmearedPt);
   fChain->SetBranchAddress("_jetSmearedPt_JERDown", _jetSmearedPt_JERDown, &b__jetSmearedPt_JERDown);
   fChain->SetBranchAddress("_jetSmearedPt_JERUp", _jetSmearedPt_JERUp, &b__jetSmearedPt_JERUp);
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
}

void full_analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

LSFReader* full_analyzer::get_LSFReader_old(TString flavor, TString type_SF)
{
    TString filename_LSF = local_dir + "data/LeptonScaleFactors/POG/";
    TString histname_LSF, histname_sys = "";
    TString pt_eta_config;
    if(flavor == "e"){
        if(_is2016){
            filename_LSF += "Electron/2016LegacyReReco_ElectronTight_Fall17V2.root";
            histname_LSF  = "EGamma_SF2D";
            pt_eta_config = "eta_pt";
        }
        if(_is2017){
            filename_LSF += "Electron/2017_ElectronTight.root";
            histname_LSF  = "EGamma_SF2D";
            pt_eta_config = "eta_pt";
        }
        if(_is2018){
            filename_LSF += "Electron/2018_ElectronTight.root";
            histname_LSF  = "EGamma_SF2D";
            pt_eta_config = "eta_pt";
        }
    }else if(flavor == "mu" and type_SF == "ID"){
        if(_is2016){
            filename_LSF += "Muon/2016_RunBCDEFGH_SF_ID.root";
            histname_LSF  = "NUM_TightID_DEN_genTracks_eta_pt";
            pt_eta_config = "eta_pt";
        }
        if(_is2017){
            filename_LSF += "Muon/2017_RunBCDEF_SF_ID.root";
            histname_LSF  = "NUM_TightID_DEN_genTracks_pt_abseta";
            pt_eta_config = "pt_abseta";
        }
        if(_is2018){
            filename_LSF += "Muon/2018_RunABCD_SF_ID.root";
            histname_LSF  = "NUM_TightID_DEN_TrackerMuons_pt_abseta";
            pt_eta_config = "pt_abseta";
        }
    }else if(flavor == "mu" and type_SF == "ISO"){
        if(_is2016){
            filename_LSF += "Muon/2016_RunBCDEFGH_SF_ISO.root";
            histname_LSF  = "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt";
            pt_eta_config = "eta_pt";
        }
        if(_is2017){
            filename_LSF += "Muon/2017_RunBCDEF_SF_ISO.root";
            histname_LSF  = "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta";
            pt_eta_config = "pt_abseta";
        }
        if(_is2018){
            filename_LSF += "Muon/2018_RunABCD_SF_ISO.root";
            histname_LSF  = "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta";
            pt_eta_config = "pt_abseta";
        }
    }
    LSFReader* lsfreader = new LSFReader(filename_LSF, histname_LSF, histname_sys, pt_eta_config);
    return lsfreader;
}

