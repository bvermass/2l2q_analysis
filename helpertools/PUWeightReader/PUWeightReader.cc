#include "PUWeightReader.h"

PUWeightReader::PUWeightReader(){
    file_weights = new TFile();
    histo_weights = new TH1F();
}

PUWeightReader::PUWeightReader(const TString filename_weights, const TString histoname_weights){
    file_weights = new TFile(filename_weights, "open");
    histo_weights = (TH1F*) file_weights->Get(histoname_weights);
}

PUWeightReader::~PUWeightReader(){
    delete histo_weights;
    delete file_weights;
}

double PUWeightReader::get_PUWeight(const int nPV){
    return histo_weights->GetBinContent(histo_weights->FindBin(nPV));
}

void PUWeightReader::make_PUWeights(const TString filename_data, const TString filename_MC, const int nbins, const double xmin, const double xmax){
    TFile file_data(filename_data, "open"), file_MC(filename_MC, "open");
    TTree* tree_MC   = (TTree*) file_MC.Get("blackJackAndHookers/blackJackAndHookersTree");

    // get nPV for data
    TH1F* nPV_data = (TH1F*) file_data.Get("pileup");
    nPV_data->Scale(1./nPV_data->Integral());

    // Fill nTrue for MC
    Float_t     _nTrueInt_MC;
    Double_t    _weight;
    TBranch     *b__nTrueInt_MC;
    TBranch     *b__weight;
    tree_MC->SetBranchAddress("_nTrueInt", &_nTrueInt_MC, &b__nTrueInt_MC);
    tree_MC->SetBranchAddress("_weight", &_weight, &b__weight);
    
    TH1F* nTrueInt_MC =  new TH1F("nTrueInt_MC", ";n True Interactions;Events", nbins, xmin, xmax);
    nTrueInt_MC->Sumw2();
    
    int NMC = tree_MC->GetEntries();
    int notice = NMC/20;
    for(int jentry = 0; jentry < NMC; jentry++){
        tree_MC->GetEntry(jentry);
        if(jentry%notice == 0) std::cout << jentry << " of " << NMC << std::endl;
        nTrueInt_MC->Fill(_nTrueInt_MC, _weight);
    }
    nTrueInt_MC->Scale(1./nTrueInt_MC->Integral());

    // Calculate weight as data/MC
    TH1F* PUWeights = (TH1F*) nPV_data->Clone("PUWeights");
    if(PUWeights->Divide(nTrueInt_MC)){
        std::cout << "PUWeights succesfully created" << std::endl;
    }

    // Store weights in new file
    TString filename_output = "PUWeights.root";
    std::cout << "output to " << filename_output << std::endl;
    TFile* file_output = new TFile(filename_output, "recreate");
    PUWeights->Write();
    nPV_data->Write();
    nTrueInt_MC->Write();
    file_output->Close();
    //file_data.Close();
    //file_MC.Close();
}
