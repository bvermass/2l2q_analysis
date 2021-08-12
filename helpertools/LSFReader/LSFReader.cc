#include "LSFReader.h"

LSFReader::LSFReader(){
    file_LSF = new TFile();
    histo_LSF = new TH2F();
    histo_sys = new TH2F();
}

LSFReader::LSFReader(const TString filename_LSF, const TString histoname_LSF, const TString histoname_sys, const TString pt_eta_conf){
    file_LSF = new TFile(filename_LSF, "open");
    if(histoname_LSF != "") histo_LSF = (TH2F*) file_LSF->Get(histoname_LSF);
    else histo_LSF = new TH2F();
    if(histoname_sys != "") histo_sys = (TH2F*) file_LSF->Get(histoname_sys);
    else histo_sys = new TH2F();
    if(pt_eta_conf != "eta_pt" and pt_eta_conf != "pt_abseta" and pt_eta_conf != "abseta_pt" and pt_eta_conf != "lxy_pt") std::cout << "Lepton Scale Factor: pt_eta_configuration not recognized: " << pt_eta_conf << std::endl;
    pt_eta_config = pt_eta_conf;

    if(pt_eta_config == "eta_pt" or pt_eta_config == "abseta_pt" or pt_eta_config == "lxy_pt"){
        pt_max_LSF = histo_LSF->GetYaxis()->GetXmax();
        pt_min_LSF = histo_LSF->GetYaxis()->GetXmin();
        pt_max_sys = histo_sys->GetYaxis()->GetXmax();
        pt_min_sys = histo_sys->GetYaxis()->GetXmin();
        eta_max_LSF = histo_LSF->GetXaxis()->GetXmax();
        eta_min_LSF = histo_LSF->GetXaxis()->GetXmin();
        eta_max_sys = histo_sys->GetXaxis()->GetXmax();
        eta_min_sys = histo_sys->GetXaxis()->GetXmin();
    }
    else if(pt_eta_config == "pt_abseta"){
        pt_max_LSF = histo_LSF->GetXaxis()->GetXmax();
        pt_min_LSF = histo_LSF->GetXaxis()->GetXmin();
        pt_max_sys = histo_sys->GetXaxis()->GetXmax();
        pt_min_sys = histo_sys->GetXaxis()->GetXmin();
        eta_max_LSF = histo_LSF->GetYaxis()->GetXmax();
        eta_min_LSF = histo_LSF->GetYaxis()->GetXmin();
        eta_max_sys = histo_sys->GetYaxis()->GetXmax();
        eta_min_sys = histo_sys->GetYaxis()->GetXmin();
    }
}

LSFReader::~LSFReader(){
    delete histo_LSF;
    delete histo_sys;
    delete file_LSF;
}

double LSFReader::get_LSF(double pt, double eta){
    pt = std::max(pt_min_LSF + 0.01, std::min(pt, pt_max_LSF - 0.01));
    if(pt_eta_config.Contains("abseta")) eta = std::max(eta_min_LSF + 0.01, std::min(fabs(eta), eta_max_LSF - 0.01));
    else eta = std::max(eta_min_LSF + 0.01, std::min(eta, eta_max_LSF - 0.01));

    if(pt_eta_config == "eta_pt") return histo_LSF->GetBinContent(histo_LSF->FindBin(eta, pt));
    else if(pt_eta_config == "pt_abseta") return histo_LSF->GetBinContent(histo_LSF->FindBin(pt, eta));
    else if(pt_eta_config == "abseta_pt") return histo_LSF->GetBinContent(histo_LSF->FindBin(eta, pt));
    else if(pt_eta_config == "lxy_pt")    return histo_LSF->GetBinContent(histo_LSF->FindBin(eta, pt));
    std::cout << "pt eta config not recognized, returning 0." << std::endl;
    return 0.;
}

double LSFReader::get_LSF_BinError(double pt, double eta){
    pt = std::max(pt_min_LSF + 0.01, std::min(pt, pt_max_LSF - 0.01));
    if(pt_eta_config.Contains("abseta")) eta = std::max(eta_min_LSF + 0.01, std::min(fabs(eta), eta_max_LSF - 0.01));
    else eta = std::max(eta_min_LSF + 0.01, std::min(eta, eta_max_LSF - 0.01));

    if(pt_eta_config == "eta_pt") return histo_LSF->GetBinError(histo_LSF->FindBin(eta, pt));
    else if(pt_eta_config == "pt_abseta") return histo_LSF->GetBinError(histo_LSF->FindBin(pt, eta));
    else if(pt_eta_config == "abseta_pt") return histo_LSF->GetBinError(histo_LSF->FindBin(eta, pt));
    else if(pt_eta_config == "lxy_pt")    return histo_LSF->GetBinError(histo_LSF->FindBin(eta, pt));
    std::cout << "pt eta config not recognized, returning 0." << std::endl;
    return 0.;
}

double LSFReader::get_sys_as_BinContent(double pt, double eta){
    pt = std::max(pt_min_sys + 0.01, std::min(pt, pt_max_sys - 0.01));
    if(pt_eta_config.Contains("abseta")) eta = std::max(eta_min_sys + 0.01, std::min(fabs(eta), eta_max_sys - 0.01));
    else eta = std::max(eta_min_sys + 0.01, std::min(eta, eta_max_sys - 0.01));

    if(pt_eta_config == "eta_pt") return histo_sys->GetBinContent(histo_sys->FindBin(eta, pt));
    else if(pt_eta_config == "pt_abseta") return histo_sys->GetBinContent(histo_sys->FindBin(pt, eta));
    else if(pt_eta_config == "abseta_pt") return histo_sys->GetBinContent(histo_sys->FindBin(eta, pt));
    else if(pt_eta_config == "lxy_pt")    return histo_sys->GetBinContent(histo_sys->FindBin(eta, pt));
    std::cout << "pt eta config not recognized, returning 0." << std::endl;
    return 0.;
}

double LSFReader::get_sys_as_BinError(double pt, double eta){
    pt = std::max(pt_min_sys + 0.01, std::min(pt, pt_max_sys - 0.01));
    if(pt_eta_config.Contains("abseta")) eta = std::max(eta_min_sys + 0.01, std::min(fabs(eta), eta_max_sys - 0.01));
    else eta = std::max(eta_min_sys + 0.01, std::min(eta, eta_max_sys - 0.01));

    if(pt_eta_config == "eta_pt") return histo_sys->GetBinError(histo_sys->FindBin(eta, pt));
    else if(pt_eta_config == "pt_abseta") return histo_sys->GetBinError(histo_sys->FindBin(pt, eta));
    else if(pt_eta_config == "abseta_pt") return histo_sys->GetBinError(histo_sys->FindBin(eta, pt));
    else if(pt_eta_config == "lxy_pt")    return histo_sys->GetBinError(histo_sys->FindBin(eta, pt));
    std::cout << "pt eta config not recognized, returning 0." << std::endl;
    return 0.;
}
