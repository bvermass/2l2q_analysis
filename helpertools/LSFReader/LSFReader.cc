#include "LSFReader.h"

LSFReader::LSFReader(){
    file_LSF = new TFile();
    histo_LSF = new TH2F();
}

LSFReader::LSFReader(const TString filename_LSF, const TString histoname_LSF, const TString flavor){
    file_LSF = new TFile(filename_LSF, "open");
    histo_LSF = (TH2F*) file_LSF->Get(histoname_LSF);
    lepton_flavor = flavor;
}

LSFReader::~LSFReader(){
    delete histo_LSF;
    delete file_LSF;
}

double LSFReader::get_LSF(const double pt, const double eta){
    // if pt of lepton is out of bounds, use last bin instead (std::min)
    if(lepton_flavor == "e") return histo_LSF->GetBinContent(histo_LSF->FindBin(fabs(eta), std::min(pt, 119.99)));
    else if(lepton_flavor == "mu") return histo_LSF->GetBinContent(histo_LSF->FindBin(fabs(eta), std::min(pt, 119.99)));
    std::cout << "Error in LSFReader: unable to get a scale factor" << std::endl;
    std::cout << "lepton flavor: " << lepton_flavor << std::endl;
    std::cout << "file and histo addresses: " << file_LSF << " " << histo_LSF << std::endl;
    return 0;
}
