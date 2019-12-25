////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, all helper functions to creating histograms//
////////////////////////////////////////////////////////////////////////////

#ifndef helper_histo_functions_h
#define helper_histo_functions_h

#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TMath.h>
#include <TSystem.h>
#include <TString.h>

void        make_logscale(double* xbins, unsigned nbins, double xmin, double xmax);
TString     make_outputfilename(TString filename, TString base_directory, TString base_filename, int partition, int partitionjobnumber);
std::map<TString, double> add_SR_counters();
void        print_SR_counters(std::map<TString, double> sr, double total_weight);
double      calc_betagamma(int particle_mass, double particle_energy);
double      get_dR(double eta1, double phi1, double eta2, double phi2);
double      get_reducedPdgId(int pdgId);
double      get_signedLog(double var);
double      get_mean_ctau(TString sampleflavor, int _gen_Nmass, double _gen_NV);
double      get_reweighting_weight(double V2_old, double V2_new, double ctau_old, double ct);
double      get_xsec_reweighting_weight(double V2_old, double V2_new);
double      get_ctprofile_reweighting_weight(double V2_old, double V2_new, double ctau_old, double ct);
double      get_evaluating_ctau(double mass, double V2_new);//for evaluating PFN on bkg (when parametrized in ctau)
std::vector<double> get_evaluating_V2s(double mass);
TString     get_MV2name(int mass, double V2);

#endif
