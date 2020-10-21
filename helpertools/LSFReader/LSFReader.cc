#include "LSFReader.h"

LSFReader::LSFReader(){
    file_LSF = new TFile();
    histo_LSF = new TH2F();
}

LSFReader::LSFReader(const TString filename_LSF, const TString histoname_LSF, const TString pt_eta_conf, const double pt_mx){
    file_LSF = new TFile(filename_LSF, "open");
    histo_LSF = (TH2F*) file_LSF->Get(histoname_LSF);
    if(pt_eta_conf != "eta_pt" and pt_eta_conf != "pt_abseta" and pt_eta_conf != "abseta_pt") std::cout << "Lepton Scale Factor: pt_eta_configuration not recognized" << std::endl;
    pt_eta_config = pt_eta_conf;
    pt_max = pt_mx;
}

LSFReader::~LSFReader(){
    delete histo_LSF;
    delete file_LSF;
}

double LSFReader::get_LSF(const double pt, const double eta){
    if(pt_eta_config == "eta_pt") return histo_LSF->GetBinContent(histo_LSF->FindBin(eta, std::min(pt, pt_max - 0.01)));
    else if(pt_eta_config == "pt_abseta") return histo_LSF->GetBinContent(histo_LSF->FindBin(std::min(pt, pt_max - 0.01), fabs(eta)));
    else if(pt_eta_config == "abseta_pt") return histo_LSF->GetBinContent(histo_LSF->FindBin(fabs(eta), std::min(pt, pt_max - 0.01)));
    std::cout << "pt eta config not recognized, returning 0." << std::endl;
    return 0.;
}

void LSFReader::print_LSF(TString filename){
    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    histo_LSF->Draw("COLZ");

    c->Print(filename);
}
