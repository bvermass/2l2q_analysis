#include "LSFReader.h"

LSFReader::LSFReader(){
    file_LSF = new TFile();
    histo_LSF = new TH2F();
    histo_sys = new TH2F();
}

LSFReader::LSFReader(const TString filename_LSF, const TString histoname_LSF, const TString histoname_sys, const TString pt_eta_conf, const double pt_mx){
    file_LSF = new TFile(filename_LSF, "open");
    if(histoname_LSF != "") histo_LSF = (TH2F*) file_LSF->Get(histoname_LSF);
    else histo_LSF = new TH2F();
    if(histoname_sys != "") histo_sys = (TH2F*) file_LSF->Get(histoname_sys);
    else histo_sys = new TH2F();
    if(pt_eta_conf != "eta_pt" and pt_eta_conf != "pt_abseta" and pt_eta_conf != "abseta_pt" and pt_eta_conf != "lxy_pt") std::cout << "Lepton Scale Factor: pt_eta_configuration not recognized: " << pt_eta_conf << std::endl;
    pt_eta_config = pt_eta_conf;
    pt_max = pt_mx;
}

LSFReader::~LSFReader(){
    delete histo_LSF;
    delete histo_sys;
    delete file_LSF;
}

double LSFReader::get_LSF(const double pt, const double eta){
    if(pt_eta_config == "eta_pt") return histo_LSF->GetBinContent(histo_LSF->FindBin(eta, std::min(pt, pt_max - 0.01)));
    else if(pt_eta_config == "pt_abseta") return histo_LSF->GetBinContent(histo_LSF->FindBin(std::min(pt, pt_max - 0.01), fabs(eta)));
    else if(pt_eta_config == "abseta_pt") return histo_LSF->GetBinContent(histo_LSF->FindBin(fabs(eta), std::min(pt, pt_max -0.01)));
    else if(pt_eta_config == "lxy_pt")    return histo_LSF->GetBinContent(histo_LSF->FindBin(std::min(eta, 19.9), std::min(pt, 19.9)));
    std::cout << "pt eta config not recognized, returning 0." << std::endl;
    return 0.;
}

double LSFReader::get_LSF_BinError(const double pt, const double eta){
    if(pt_eta_config == "eta_pt") return histo_LSF->GetBinError(histo_LSF->FindBin(eta, std::min(pt, pt_max - 0.01)));
    else if(pt_eta_config == "pt_abseta") return histo_LSF->GetBinError(histo_LSF->FindBin(std::min(pt, pt_max - 0.01), fabs(eta)));
    else if(pt_eta_config == "abseta_pt") return histo_LSF->GetBinError(histo_LSF->FindBin(fabs(eta), std::min(pt, pt_max -0.01)));
    else if(pt_eta_config == "lxy_pt")    return histo_LSF->GetBinError(histo_LSF->FindBin(std::min(eta, 19.9), std::min(pt, 19.9)));
    std::cout << "pt eta config not recognized, returning 0." << std::endl;
    return 0.;
}

double LSFReader::get_sys_as_BinContent(const double pt, const double eta){
    if(pt_eta_config == "eta_pt") return histo_sys->GetBinContent(histo_sys->FindBin(eta, std::min(pt, pt_max - 0.01)));
    else if(pt_eta_config == "pt_abseta") return histo_sys->GetBinContent(histo_sys->FindBin(std::min(pt, pt_max - 0.01), fabs(eta)));
    else if(pt_eta_config == "abseta_pt") return histo_sys->GetBinContent(histo_sys->FindBin(fabs(eta), std::min(pt, pt_max -0.01)));
    else if(pt_eta_config == "lxy_pt")    return histo_sys->GetBinContent(histo_LSF->FindBin(std::min(eta, 19.9), std::min(pt, 19.9)));
    std::cout << "pt eta config not recognized, returning 0." << std::endl;
    return 0.;
}

double LSFReader::get_sys_as_BinError(const double pt, const double eta){
    if(pt_eta_config == "eta_pt") return histo_sys->GetBinError(histo_sys->FindBin(eta, std::min(pt, pt_max - 0.01)));
    else if(pt_eta_config == "pt_abseta") return histo_sys->GetBinError(histo_sys->FindBin(std::min(pt, pt_max - 0.01), fabs(eta)));
    else if(pt_eta_config == "abseta_pt") return histo_sys->GetBinError(histo_sys->FindBin(fabs(eta), std::min(pt, pt_max -0.01)));
    else if(pt_eta_config == "lxy_pt")    return histo_sys->GetBinError(histo_LSF->FindBin(std::min(eta, 19.9), std::min(pt, 19.9)));
    std::cout << "pt eta config not recognized, returning 0." << std::endl;
    return 0.;
}
