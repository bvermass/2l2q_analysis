#include "PUWeightReader.h"


PUWeightReader::PUWeightReader(){
    PUWeights_Central = new TH1F();
    PUWeights_Up = new TH1F();
    PUWeights_Down = new TH1F();
}

PUWeightReader::PUWeightReader(TString local_dir, bool is2017, bool is2018, const TH1F* nTrueInteractions)
{
    TString dataPU_base = local_dir + "data/PUWeights/PU_";
    if(is2017) dataPU_base += "2017_41500";
    else if(is2018) dataPU_base += "2018_60000";
    else dataPU_base += "2016_36000";
    
    TFile dataPU_Central_file(dataPU_base + "_XSecCentral.root", "open");
    TFile dataPU_Up_file(dataPU_base + "_XSecUp.root", "open");
    TFile dataPU_Down_file(dataPU_base + "_XSecDown.root", "open");

    TH1F* dataPU_Central = (TH1F*)dataPU_Central_file.Get("pileup");
    TH1F* dataPU_Up = (TH1F*)dataPU_Up_file.Get("pileup");
    TH1F* dataPU_Down = (TH1F*)dataPU_Down_file.Get("pileup");

    dataPU_Central->Scale(1./dataPU_Central->Integral());
    dataPU_Up->Scale(1./dataPU_Up->Integral());
    dataPU_Down->Scale(1./dataPU_Down->Integral());


    TH1F* nTrueInt = (TH1F*)nTrueInteractions->Clone("nTrueInt");
    nTrueInt->Scale(1./nTrueInt->Integral());

    PUWeights_Central = new TH1F("PUWeights_Central", "PUWeights_Central;nTrueInteractions;Weight", 100, 0, 100);
    PUWeights_Up      = new TH1F("PUWeights_Up", "PUWeights_Up;nTrueInteractions;Weight", 100, 0, 100);
    PUWeights_Down    = new TH1F("PUWeights_Down", "PUWeights_Down;nTrueInteractions;Weight", 100, 0, 100);

    PUWeights_Central->Divide(dataPU_Central, nTrueInt);
    PUWeights_Up->Divide(dataPU_Up, nTrueInt);
    PUWeights_Down->Divide(dataPU_Down, nTrueInt);
}

PUWeightReader::~PUWeightReader(){
}

double PUWeightReader::get_PUWeight_Central(const int nTrueInteractions){
    return PUWeights_Central->GetBinContent(PUWeights_Central->FindBin(nTrueInteractions));
}

double PUWeightReader::get_PUWeight_Up(const int nTrueInteractions){
    return PUWeights_Up->GetBinContent(PUWeights_Up->FindBin(nTrueInteractions));
}

double PUWeightReader::get_PUWeight_Down(const int nTrueInteractions){
    return PUWeights_Down->GetBinContent(PUWeights_Down->FindBin(nTrueInteractions));
}
