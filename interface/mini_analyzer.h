/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Mini Analyzer class, meant to operate on files created by BkgEstimator.
// Class performs any kind of operations necessary for background prediction, either data-driven, straight from MC if prompt, or whatever I come up with 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef mini_analyzer_h
#define mini_analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include <string>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TSystem.h>
#include <TGraphAsymmErrors.h>

// helper functions
#include "../interface/helper_histo_functions.h"
#include "../interface/BkgEstimator.h"
#include "../interface/bTagWP.h"
#include "../helpertools/LorentzVector/LorentzVector.h"

double get_PFNcut(int mass, unsigned flavor, bool is2016, bool is2017);
double get_NewPFNcut(int mass, unsigned l1flavor, unsigned l2flavor, double SVmass, double Lxy, bool isOS, bool is2016, bool is2017);
double get_looserPFNcut(int mass, unsigned flavor, bool is2016, bool is2017);
double get_MediumPFNcut(int mass, unsigned flavor, bool is2016, bool is2017);
double get_LoosePFNcut(int mass, unsigned flavor, bool is2016, bool is2017);
double get_LoosePFNcut2(int mass, unsigned flavor, bool is2016, bool is2017);

class mini_analyzer {
    public :
        BkgEstimator event;
        TString sr_flavor;
        bool isData, isSignal;
        std::map<TString, TH1*> hists;
        std::map<TString, TH1*> hists_sys;
        std::map<TString, TH2*> hists2D;

        //For ABCD method based on PFN output and dphi
        std::vector<TString> ABCDtags;
        std::map<TString, unsigned> MV2tags;
        std::map<TString, double> CPtags;
        std::map<TString, double> variations;
        bool isPrompt;
        bool baseline_cutphill;
        bool baseline_cutmll;
        bool baseline_cutphiORmll;
        bool baseline_cutmlSV;
        bool baseline_cutmlSV_CR2Jets;
        bool baseline_cutmlSV_nojetveto;
        bool baseline_cutCR3phill;

        //General functions
        mini_analyzer(TString filename);
        ~mini_analyzer();
        unsigned get_PFNevaluation_index(int mass, unsigned flavor);
        void init_MV2_parametrization();
        void init_CP();

        void analyze(int max_entries, int partition, int partitionjobnumber);

        void ABCD_ratios();
        void calculate_ratio(TString numerator_tag, TString denominator_tag, TString ratio_tag);
        void apply_ratio(TString ratio_tag, TString histo_tag, TString target_tag, TString ratio_tag_for_error);
        void calculate_eff();
        void add_NonClosureSys_variation(TString selection_tag);
        void add_ABCDstat_variation(TString selection_tag);

        void set_signal_regions();
        void set_signal_regions_gridscan();

        void add_histograms();
        void add_histograms_gridscan();
        void add_fraction_histograms(TString prefix);
        void add_standard_histograms(TString prefix);
        void add_pfn_histograms(TString prefix);
        void add_Shape_SR_histograms(TString prefix);
        void add_Shape_SR_extra_histograms(TString prefix);

        void fill_histograms();
        void fill_fraction_histograms(TString prefix, double event_weight);
        void fill_standard_histograms(TString prefix, double event_weight);
        void fill_pfn_histograms(TString prefix, double event_weight, unsigned i);
        void fill_Shape_SR_histograms(TString sr_flavor, TString ABCDtag, double event_weight);
        void fill_Shape_SR_extra_histograms(TString sr_flavor, TString ABCDtag, double event_weight, unsigned i);

        void sum_quad_histograms();
        void sum_histograms_based_on_tags(TString base_tag, TString second_tags, TString target_tag);
        double get_SRShapebin(double PVSVdist_2D, double SV_mass);
        double get_SRShape2bin(double PVSVdist_2D, TString tagForMass);
        double get_SRShape3bin(double PVSVdist_2D, double SV_mass, TString tagForMass, TString sr_flavor);
        double get_SRShape4bin(double PVSVdist_2D, double SV_mass);
        void set_error_for_zero_event_bins(TString hname_target, TString hname_ratio);
        void set_quadA_zero_event_bins();

        void init_variations();
        void set_variations(double nominal_weight);

        //in src/mini_analyzer_JEC.cc
        std::map<TString, TH1*> get_hists_JECvariations(TString base_filename);
        void add_histograms_JEC(std::map<TString, TH1*>* hists_JEC, TString JECvar);
        void add_Shape_SR_histograms_JEC(std::map<TString, TH1*>* hists_JEC, TString prefix);
        void run_JECvariation(std::map<TString, TH1*>* hists_JEC, TString JECvar, TString JECvarsys, TString base_filename);
        std::vector<TString> set_signal_regions_JEC(BkgEstimator& eventJEC, TString JECvarsys);
        TString get_sr_flavor(BkgEstimator& eventJEC);
        void fill_histograms_JEC(BkgEstimator& eventJEC, std::map<TString, TH1*>* hists_JEC, std::vector<TString> JECtags, TString sr_flavor_JEC);
        void fill_Shape_SR_histograms_JEC(BkgEstimator& eventJEC, std::map<TString, TH1*>* hists_JEC, TString sr_flavor, TString JECtag, double event_weight);
        void set_correct_sysUp_sysDown(std::map<TString, TH1*>* hists_JEC, std::vector<TString> syslabels);

};

#endif
