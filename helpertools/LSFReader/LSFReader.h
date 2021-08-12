#ifndef LSFReader_H
#define LSFReader_H

//include c++ library classes 
#include <iostream>
#include <algorithm>

//include ROOT library classes
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH2.h>

class LSFReader{
    public:
        LSFReader();
        LSFReader(const TString filename_LSF, const TString histoname_LSF, const TString histoname_sys, const TString pt_eta_conf);
        ~LSFReader();

        double get_LSF(double pt, double eta);
        double get_LSF_BinError(double pt, double eta);
        double get_sys_as_BinContent(double pt, double eta);
        double get_sys_as_BinError(double pt, double eta);

    private:
        TFile* file_LSF;
        TH2F* histo_LSF;
        TH2F* histo_sys;
        TString pt_eta_config;
        double pt_max_LSF, pt_min_LSF, pt_max_sys, pt_min_sys;
        double eta_max_LSF, eta_min_LSF, eta_max_sys, eta_min_sys;
};
#endif
