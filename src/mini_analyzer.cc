//Include header for this class
#include "../interface/mini_analyzer.h"

bool Dogridscan = false;
bool makeMajToDirac = true;

mini_analyzer::mini_analyzer(TString filename) :
    event(filename, "read"),
    isData(filename.Contains("Run201") or filename.Contains("SingleLepton")),
    isSignal(filename.Contains("HeavyNeutrino_lljj_")),
    isBlind(false),
    storeSRevents(true),
    allCouplings(true)
{
    TH1::AddDirectory(kFALSE);//https://root.cern.ch/input-and-output
    event.BkgEstimator_tree->GetEntry(0);
    init_MV2_parametrization();
    init_CP();
    init_variations();
    if(Dogridscan) add_histograms_gridscan();
    else add_histograms();
    if(storeSRevents){
        TString SRevents_LowMass_filename  = filename;
        SRevents_LowMass_filename.ReplaceAll("final/full_analyzer", "SRevents_LowMass");
        SRevents_LowMass_filename.ReplaceAll("final_official/full_analyzer", "SRevents_LowMass");
        if(Dogridscan) SRevents_LowMass_filename.ReplaceAll("highlPt","highlPt_gridscan");
        //SRevents_LowMass_filename.ReplaceAll("highlPt","highlPt_noDYveto");
        gSystem->Exec("mkdir -p " + SRevents_LowMass_filename(0,SRevents_LowMass_filename.Index("BkgEstimator_")));
        std::cout << "hCounter adress: " << event.hCounter << std::endl;
        SRevents_LowMass = new BkgEstimator(SRevents_LowMass_filename, "recreate", event.hCounter->GetBinContent(1));

        TString SRevents_HighMass_filename = filename;
        SRevents_HighMass_filename.ReplaceAll("final/full_analyzer", "SRevents_HighMass");
        SRevents_HighMass_filename.ReplaceAll("final_official/full_analyzer", "SRevents_HighMass");
        if(Dogridscan) SRevents_HighMass_filename.ReplaceAll("highlPt","highlPt_gridscan");
        //SRevents_HighMass_filename.ReplaceAll("highlPt","highlPt_noDYveto");
        gSystem->Exec("mkdir -p " + SRevents_HighMass_filename(0,SRevents_HighMass_filename.Index("BkgEstimator_")));
        SRevents_HighMass = new BkgEstimator(SRevents_HighMass_filename, "recreate", event.hCounter->GetBinContent(1));
    }
    std::cout << "number of histograms: " << hists.size() << std::endl;
    std::cout << "number of MV2tags: " << MV2tags.size() << std::endl;
}

mini_analyzer::~mini_analyzer()
{}

double get_looserPFNcut(int mass, unsigned flavor, bool is2016, bool is2017)
{
    if(flavor == 0){//electron
        if(is2016){
            if(mass <= 5)   return 0.94;
            else            return 0.94;
        }else if(is2017){
            if(mass <= 5)   return 0.94;//0.98 had almost 0 predicted events
            else            return 0.94;//0.97 had almost 0 predicted events
        }else {
            if(mass <= 5)   return 0.94;
            else            return 0.94;
        }
    }else {//muon
        if(is2016){
            if(mass <= 5)   return 0.975;
            else            return 0.975;
        }else if(is2017){
            if(mass <= 5)   return 0.975;
            else            return 0.975;
        }else {
            if(mass <= 5)   return 0.975;
            else            return 0.975;
        }
    }
}

double get_MediumPFNcut(int mass, unsigned l1flavor, unsigned l2flavor, double SVmass, double Lxy, bool isOS, bool is2016, bool is2017)
{
    //special cuts for bins that otherwise have 0 prediction
    if(isOS){
        if(is2016){
            if(mass <= 5){
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 2 and Lxy >= 10)                       return 0.93;//OS me LowMass 2016
            }else{
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.980;//OS em HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 1 and Lxy < 5)            return 0.967;//OS ee HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.913;//OS ee HighMass 2016
                if(l1flavor == 1 and l2flavor == 0 and SVmass <  6 and Lxy >= 5)                        return 0.962;//OS me HighMass 2016
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.932;//OS me HighMass 2016
            }
        }else{
            if(mass <= 5){
                if(l1flavor == 1 and l2flavor == 1 and SVmass <  2 and Lxy <  4)                        return 0.99;//OS mm LowMass 1718
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 2 and Lxy >= 10)                       return 0.959;//OS me LowMass 1718
            }else{
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.976;//OS em HighMass 1718
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.9;//OS me HighMass 1718
            }
        }
    }else{
        if(is2016){
            if(mass <= 5){
                //all bins fine
            }else{
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 1 and Lxy < 5)            return 0.97;//SS em HighMass 2016
                //!!!if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.053;//SS em HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 1 and Lxy < 5)            return 0.97;//SS ee HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.9;//SS ee HighMass 2016
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.94;//OS me HighMass 2016
            }
        }else{
            if(mass <= 5){
                if(l1flavor == 1 and l2flavor == 1 and SVmass <  2 and Lxy <  4)                        return 0.99;//SS mm LowMass 1718
                if(l1flavor == 0 and l2flavor == 1 and SVmass <  2 and Lxy <  4)                        return 0.980;//SS me LowMass 1718
            }else{
                if(l1flavor == 1 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.98;//SS mm HighMass 1718
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.510;//SS me HighMass 1718
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.936;//SS me HighMass 1718
            }
        }
    }

    //Normal overall PFN cuts
    if(l2flavor == 0){//electron
        if(is2016){
            if(mass <= 5)   return 0.96;
            else            return 0.97;
        }else if(is2017){
            if(mass <= 5)   return 0.95;
            else            return 0.94;
        }else {
            if(mass <= 5)   return 0.96;
            else            return 0.95;
        }
    }else {//muon
        if(is2016){
            if(mass <= 5)   return 0.994;
            else            return 0.994;
        }else if(is2017){
            if(mass <= 5)   return 0.992;
            else            return 0.994;
        }else {
            if(mass <= 5)   return 0.993;
            else            return 0.994;
        }
    }
}

double get_TightPFNcut(int mass, unsigned l1flavor, unsigned l2flavor, double SVmass, double Lxy, bool isOS, bool is2016, bool is2017)
{
    //special cuts for bins that otherwise have 0 prediction
    if(isOS){
        if(is2016){
            if(mass <= 5){
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 2 and Lxy >= 10)                       return 0.957;//OS me LowMass 2016
            }else{
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.990;//OS em HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 1 and Lxy < 5)            return 0.987;//OS ee HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.933;//OS ee HighMass 2016
                if(l1flavor == 1 and l2flavor == 0 and SVmass <  6 and Lxy >= 5)                        return 0.982;//OS me HighMass 2016
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.952;//OS me HighMass 2016
            }
        }else{
            if(mass <= 5){
                if(l1flavor == 1 and l2flavor == 1 and SVmass <  2 and Lxy <  4)                        return 0.995;//OS mm LowMass 1718
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 2 and Lxy >= 10)                       return 0.979;//OS me LowMass 1718
            }else{
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.986;//OS em HighMass 1718
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.917;//OS me HighMass 1718
            }
        }
    }else{
        if(is2016){
            if(mass <= 5){
                //all bins fine
            }else{
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 1 and Lxy < 5)            return 0.987;//SS em HighMass 2016
                //!!!if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.053;//SS em HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 1 and Lxy < 5)            return 0.988;//SS ee HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.913;//SS ee HighMass 2016
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.968;//OS me HighMass 2016
            }
        }else{
            if(mass <= 5){
                if(l1flavor == 1 and l2flavor == 1 and SVmass <  2 and Lxy <  4)                        return 0.994;//SS mm LowMass 1718
                if(l1flavor == 0 and l2flavor == 1 and SVmass <  2 and Lxy <  4)                        return 0.990;//SS me LowMass 1718
            }else{
                if(l1flavor == 1 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.991;//SS mm HighMass 1718
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.510;//SS me HighMass 1718
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.956;//SS me HighMass 1718
            }
        }
    }

    // Normal overall PFN cuts
    if(l1flavor == 0 and l2flavor == 0){//ee
        if(is2016){
            if(mass <= 5)   return 0.98;
            else            return 0.99;
        }else if(is2017){
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }else {
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }
    }else if(l1flavor == 1 and l2flavor == 0){//me
        if(is2016){
            if(mass <= 5)   return 0.98;
            else            return 0.99;
        }else if(is2017){
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }else {
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }
    }else if(l1flavor == 1 and l2flavor == 1){//mm
        if(is2016){
            if(mass <= 5)   return 0.9994;
            else            return 0.998;
        }else if(is2017){
            if(mass <= 5)   return 0.996;
            else            return 0.998;
        }else {
            if(mass <= 5)   return 0.996;
            else            return 0.998;
        }
    }else if(l1flavor == 0 and l2flavor == 1){//em
        if(is2016){
            if(mass <= 5)   return 0.999;
            else            return 0.998;
        }else if(is2017){
            if(mass <= 5)   return 0.996;
            else            return 0.996;
        }else {
            if(mass <= 5)   return 0.996;
            else            return 0.996;
        }
    }else{
        std::cout << "Error: Reaching end of get_TightPFNcut without specifying a cut" << std::endl;
        return 0.;
    }
}


double get_NTightPFNcut(int mass, unsigned l1flavor, unsigned l2flavor, int l1charge, int l2charge, double SVmass, double Lxy, bool isOS, bool is2016, bool is2017)
{
    //special cuts for bins that otherwise have 0 prediction
    if(isOS){
        if(is2016){
            if(mass <= 5){
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 2 and Lxy >= 10)                       return 0.957;//OS me LowMass 2016
            }else{
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.990;//OS em HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 1 and Lxy < 5)            return 0.987;//OS ee HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.933;//OS ee HighMass 2016
                if(l1flavor == 1 and l2flavor == 0 and SVmass <  6 and Lxy >= 5)                        return 0.982;//OS me HighMass 2016
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.952;//OS me HighMass 2016
            }
        }else{
            if(mass <= 5){
                if(l1flavor == 1 and l2flavor == 1 and SVmass <  2 and Lxy <  4)                        return 0.995;//OS mm LowMass 1718
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 2 and Lxy >= 10)                       return 0.979;//OS me LowMass 1718
            }else{
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.986;//OS em HighMass 1718
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.917;//OS me HighMass 1718
            }
        }
    }else{
        if(is2016){
            if(mass <= 5){
                //all bins fine
            }else{
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 1 and Lxy < 5)            return 0.987;//SS em HighMass 2016
                //!!!if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.053;//SS em HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 1 and Lxy < 5)            return 0.988;//SS ee HighMass 2016
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.913;//SS ee HighMass 2016
                if(l1flavor == 1 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.968;//OS me HighMass 2016
            }
        }else{
            if(mass <= 5){
                if(l1flavor == 1 and l2flavor == 1 and SVmass <  2 and Lxy <  4)                        return 0.994;//SS mm LowMass 1718
                if(l1flavor == 0 and l2flavor == 1 and SVmass <  2 and Lxy <  4)                        return 0.990;//SS me LowMass 1718
            }else{
                if(l1flavor == 1 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.991;//SS mm HighMass 1718
                if(l1flavor == 0 and l2flavor == 1 and SVmass >= 6 and Lxy >= 5)                        return 0.510;//SS me HighMass 1718
                if(l1flavor == 0 and l2flavor == 0 and SVmass >= 6 and Lxy >= 5)                        return 0.956;//SS me HighMass 1718
            }
        }
    }

    // Normal overall PFN cuts
    if(l1flavor == 0 and l2flavor == 0){//ee
        if(is2016){
            if(mass <= 5)   return 0.98;
            else            return 0.99;
        }else if(is2017){
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }else {
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }
    }else if(l1flavor == 1 and l2flavor == 0){//me
        if(is2016){
            if(mass <= 5)   return 0.98;
            else            return 0.99;
        }else if(is2017){
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }else {
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }
    }else if(l1flavor == 1 and l2flavor == 1){//mm
        if(l1charge == l2charge){
            if(is2016){
                if(mass <= 5)   return 0.9994;
                else            return 0.998;
            }else if(is2017){
                if(mass <= 5)   return 0.996;
                else            return 0.998;
            }else {
                if(mass <= 5)   return 0.996;
                else            return 0.998;
            }
        }else{
            if(is2016){
                if(mass <= 5)   return 0.975;
                else            return 0.998;
            }else if(is2017){
                if(mass <= 5)   return 0.975;
                else            return 0.998;
            }else {
                if(mass <= 5)   return 0.975;
                else            return 0.998;
            }
        }
    }else if(l1flavor == 0 and l2flavor == 1){//em
        if(is2016){
            if(mass <= 5)   return 0.999;
            else            return 0.998;
        }else if(is2017){
            if(mass <= 5)   return 0.996;
            else            return 0.996;
        }else {
            if(mass <= 5)   return 0.996;
            else            return 0.996;
        }
    }else{
        std::cout << "Error: Reaching end of get_NTightPFNcut without specifying a cut" << std::endl;
        return 0.;
    }
}

double get_PFNcut(int mass, unsigned flavor, bool is2016, bool is2017)
{
    if(flavor == 0){//electron
        if(is2016){
            if(mass <= 5)   return 0.98;
            else            return 0.99;
        }else if(is2017){
            if(mass <= 5)   return 0.97;//0.98 had almost 0 predicted events
            else            return 0.96;//0.97 had almost 0 predicted events
        }else {
            if(mass <= 5)   return 0.98;
            else            return 0.97;
        }
    }else {//muon
        if(is2016){
            if(mass <= 5)   return 0.999;
            else            return 0.998;
        }else if(is2017){
            if(mass <= 5)   return 0.996;
            else            return 0.998;
        }else {
            if(mass <= 5)   return 0.997;
            else            return 0.998;
        }
    }
}

double get_LoosePFNcut(int mass, unsigned flavor, bool is2016, bool is2017)
{
    if(flavor == 0){//electron
        if(is2016){
            if(mass <= 5)   return 0.8;
            else            return 0.8;
        }else if(is2017){
            if(mass <= 5)   return 0.8;
            else            return 0.8;
        }else {
            if(mass <= 5)   return 0.8;
            else            return 0.8;
        }
    }else {//muon
        if(is2016){
            if(mass <= 5)   return 0.85;
            else            return 0.85;
        }else if(is2017){
            if(mass <= 5)   return 0.8;
            else            return 0.8;
        }else {
            if(mass <= 5)   return 0.8;
            else            return 0.8;
        }
    }
}

double get_VLoosePFNcut(int mass, unsigned flavor, bool is2016, bool is2017)
{
    if(flavor == 0){//electron
        if(is2016){
            if(mass <= 5)   return 0.95;
            else            return 0.95;
        }else if(is2017){
            if(mass <= 5)   return 0.95;
            else            return 0.95;
        }else {
            if(mass <= 5)   return 0.95;
            else            return 0.95;
        }
    }else {//muon
        if(is2016){
            if(mass <= 5)   return 0.95;
            else            return 0.95;
        }else if(is2017){
            if(mass <= 5)   return 0.95;
            else            return 0.95;
        }else {
            if(mass <= 5)   return 0.95;
            else            return 0.95;
        }
    }
}

double get_VVLoosePFNcut(int mass, unsigned flavor, bool is2016, bool is2017)
{
    if(flavor == 0){//electron
        if(is2016){
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }else if(is2017){
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }else {
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }
    }else {//muon
        if(is2016){
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }else if(is2017){
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }else {
            if(mass <= 5)   return 0.9;
            else            return 0.9;
        }
    }
}

unsigned mini_analyzer::get_PFNevaluation_index(int mass, unsigned flavor)
{
    int mass_ev;
    double V2_ev;
    if(flavor == 0){//electron
        if(mass <= 5){
           mass_ev = 5;
           V2_ev = 2e-6;
        }else {
            mass_ev = 10;
            V2_ev = 2e-6;
        }
    }else if(flavor == 1){//muon
        if(mass <= 5){
           mass_ev = 5;
           V2_ev = 2e-6;
        }else {
            mass_ev = 10;
            V2_ev = 2e-6;
        }
    }else {
        mass_ev = 0;
        V2_ev = 0.;
    }

    return MV2tags[get_MV2name(mass_ev, V2_ev)];
}


void mini_analyzer::init_MV2_parametrization()
{
    for(unsigned i_mv2 = 0; i_mv2 < event._nMV2; i_mv2++){
        if((allCouplings and isSignal) or equals(event._evaluating_V2[i_mv2], 2e-6, 1e-10) or equals(event._evaluating_V2[i_mv2], 4e-6, 1e-10)){
            MV2tags[get_MV2name(event._evaluating_mass[i_mv2], event._evaluating_V2[i_mv2])] = i_mv2;
        }
    }
}

void mini_analyzer::init_CP()
{
    CPtags["_CP-0p94"] = 0.94;
    CPtags["_CP-0p95"] = 0.95;
    CPtags["_CP-0p96"] = 0.96;
    CPtags["_CP-0p97"] = 0.97;
    CPtags["_CP-0p98"] = 0.98;
    CPtags["_CP-0p99"] = 0.99;
    CPtags["_CP-0p992"] = 0.992;
    CPtags["_CP-0p994"] = 0.994;
    CPtags["_CP-0p996"] = 0.996;
    CPtags["_CP-0p998"] = 0.998;
    CPtags["_CP-0p999"] = 0.999;
}


void mini_analyzer::analyze(int max_entries, int partition, int partitionjobnumber)
{
    // Determine range of events to loop over
    Long64_t nentries = event.BkgEstimator_tree->GetEntries();
    if(max_entries == -1 or max_entries > nentries) max_entries = nentries;
    Long64_t j_begin = floor(1.0 * max_entries * partitionjobnumber / partition);
    Long64_t j_end   = floor(1.0 * max_entries * (partitionjobnumber + 1) / partition);
    unsigned notice = ceil(0.01 * (j_end - j_begin) / 20) * 100;
    unsigned loop_counter = 0;

    unsigned cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0, cnt8 = 0;
    //main loop
    std::cout << "Running over " << j_begin << " - " << j_end-1 << " out of " << max_entries << " events from " << event.BkgEstimator_filename << std::endl;
    for(unsigned jentry = j_begin; jentry < j_end; ++jentry){
	    event.BkgEstimator_tree->GetEntry(jentry);

        if(loop_counter == notice){
            std::cout << jentry - j_begin << " of " << j_end - j_begin << std::endl;
            loop_counter = 0;
        }


        if(Dogridscan) set_signal_regions_gridscan();
        else set_signal_regions();
        fill_histograms();
        fill_SRevents();

        if( event._SV_l1mass > 10){
            cnt1++;
            if(event._nTightLep == 1){
                cnt2++;
                if(event._nTightJet <= 1){
                    cnt3++;
                    if(event._SV_l1mass > 50){
                        cnt4++;
                        if(event._SV_l1mass < 85){
                            cnt5++;
                            int i_MV2      = get_PFNevaluation_index(10, 1);
                            double PFNcut  = get_NTightPFNcut(10, event._l1Flavor, event._lFlavor, event._l1Charge, event._lCharge, event._SV_mass, event._SV_PVSVdist_2D, event._l1Charge != event._lCharge, event._is2016, event._is2017);
                            if(event._JetTagVal[i_MV2] > PFNcut){
                                cnt6++;
                                if(event._SV_mass > 2){
                                    cnt7++;
                                    if(event._SV_PVSVdist_2D < 4){
                                        cnt8++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        ++loop_counter;
    }
    std::cout << "selection counter values: " << std::endl;
    std::cout << "counter 1: " << cnt1 << std::endl;
    std::cout << "counter 2: " << cnt2 << std::endl;
    std::cout << "counter 3: " << cnt3 << std::endl;
    std::cout << "counter 4: " << cnt4 << std::endl;
    std::cout << "counter 5: " << cnt5 << std::endl;
    std::cout << "counter 6: " << cnt6 << std::endl;
    std::cout << "counter 7: " << cnt7 << std::endl;
    std::cout << "counter 8: " << cnt8 << std::endl;
    if(!Dogridscan) sum_quad_histograms();

    //Get the JEC variations for signal MC
    //std::map<TString, TH1*> hists_JEC;
    //if(isSignal){
    //    hists_JEC = get_hists_JECvariations(event.BkgEstimator_filename);
    //    set_correct_sysUp_sysDown(&hists_JEC, {"JEC_", "JER_"});
    //}

    if(storeSRevents){
        SRevents_LowMass->write_tree();
        SRevents_HighMass->write_tree();
    }

    TString outputfilename = get_mini_analyzer_outputfilename(event.BkgEstimator_filename, Dogridscan);
    if(max_entries == 10000) outputfilename.ReplaceAll(".root", "_test.root");
    std::cout << "output to: " << outputfilename << std::endl;
    TFile *output = new TFile(outputfilename, "recreate");
    
    std::cout << "calculating and applying ABCD method" << std::endl;
    ABCD_ratios();
    std::cout << "setting quadA quasi-zero bins to zero" << std::endl;
    set_quadA_zero_event_bins();
    //add_ABCDstat_variation("cutTightmlSV_BtoAwithCD_Shape_SR");
    //add_NonClosureSys_variation("cutTightmlSV_BtoAwithCD_Shape_SR");

    std::cout << "Add under- and overflow to last bins, then write them" << std::endl;
    for(auto const& it : hists){
        TH1* h = it.second;
        fix_overflow_and_negative_bins(h);
        //divide_stat_errors(h);
	    h->Write(h->GetName(), TObject::kOverwrite);
    }
    for(auto const& it : hists2D){
        TH2* h = it.second;
        h->Write(h->GetName(), TObject::kOverwrite);
    }
    for(auto const& it : hists_sys){
        TH1* h = it.second;
        fix_overflow_and_negative_bins(h);
        h->Write(h->GetName(), TObject::kOverwrite);
    }
    //for(auto const& it : hists_JEC){
    //    TH1* h = it.second;
    //    fix_overflow_and_negative_bins(h);
    //    h->Write(h->GetName(), TObject::kOverwrite);
    //}
    
    TH1F* hadd_counter = new TH1F("hadd_counter", "nr. of files hadded together;;", 1, 0, 1);
    hadd_counter->Fill(0);
    hadd_counter->Write();

    std::cout << "close file" << std::endl;
    output->Close();
}


void mini_analyzer::ABCD_ratios()
{
    //if(!(isData and isBlind)) calculate_ratio("_quadA_", "_quadB_", "_AoverB_");
    //if(!(isData and isBlind)) calculate_ratio("_quadA_", "_quadC_", "_AoverC_");
    calculate_ratio("_quadC_", "_quadD_", "_CoverD_");
    //calculate_ratio("_quadB_", "_quadD_", "_BoverD_");
    //calculate_eff();

    //apply_ratio("_CoverD_", "_quadD_", "_DtoCwithCD_");
    apply_ratio("_CoverD_", "_quadB_", "_BtoAwithCD_", "_CoverD_");
    //apply_ratio("_BoverD_", "_quadC_", "_CtoAwithBD_", "_BoverD_");
}


void mini_analyzer::calculate_ratio(TString numerator_tag, TString denominator_tag, TString ratio_tag)
{
    for(auto const& it : hists){
        TH1* h = it.second;
        TString hname = h->GetName();

        if(hname.Contains(numerator_tag) and !hname.Contains("_sys")){
            TString hname_den(hname), hname_ratio(hname);

            hname_den.ReplaceAll(numerator_tag, denominator_tag);
            hname_ratio.ReplaceAll(numerator_tag, ratio_tag);

            if(hists[hname]->GetMaximum() > 0 and hists[hname_den]->GetMaximum() > 0){
                hists[hname_ratio]->Divide(hists[hname], hists[hname_den]);
            }
        }
    }
}


void mini_analyzer::apply_ratio(TString ratio_tag, TString histo_tag, TString target_tag, TString ratio_tag_for_error)
{
    for(auto const& it : hists){
        TH1* h = it.second;
        TString hname = h->GetName();

        if(hname.Contains("Shape_") and hname.Contains(histo_tag) and !hname.Contains("_sys")){
            TString hname_ratio(hname), hname_target(hname), hname_ratio_for_error(hname);
            hname_ratio.ReplaceAll(histo_tag, ratio_tag);
            hname_target.ReplaceAll(histo_tag, target_tag);
            hname_ratio_for_error.ReplaceAll(histo_tag, ratio_tag_for_error);

            if(hists[hname]->GetMaximum() > 0 and hists[hname_ratio]->GetMaximum() > 0){
                hists[hname_target] = (TH1F*)hists[hname]->Clone(hname_target);
                //hists[hname_target]->Scale(hists[hname_ratio]->GetBinContent(1));//use this in case of using a full ratio for ABCD prediction
                hists[hname_target]->Multiply(hists[hname_ratio]);
                set_error_for_zero_event_bins(hname_target, hname_ratio_for_error);//sets bin error for 0 event bins to (central value of C/D ratio in that bin, this assumes ratio =/= 0!)
            }
        }else if(hname.Contains(histo_tag) and !hname.Contains("_sys")){
            TString hname_ratio(hname(0, hname.Last('_')) + "_Yield"), hname_target(hname);
            hname_ratio.ReplaceAll(histo_tag, ratio_tag);
            hname_target.ReplaceAll(histo_tag, target_tag);

            //std::cout << "original, target and ratio: " << std::endl;
            //std::cout << hname << std::endl;
            //std::cout << hname_target << std::endl;
            //std::cout << hname_ratio << std::endl << std::endl;
            if(hists[hname]->GetMaximum() > 0 and hists[hname_ratio]->GetMaximum() > 0){
                hists[hname_target] = (TH1F*)hists[hname]->Clone(hname_target);
                hists[hname_target]->Scale(hists[hname_ratio]->GetBinContent(1));//use this in case of using a full ratio for ABCD prediction
                //hists[hname_target]->Multiply(hists[hname_ratio]);
            }
            
        }
    }
}


void mini_analyzer::calculate_eff()
{
    for(auto const& it : hists){
        TString hname = it.first;

        if(hname.Contains("_quadA_") and !hname.Contains("_sys")){
            TString hname_eff = hname;
            hname_eff.ReplaceAll("_quadA_", "_Aeff_");
            hists[hname_eff] = (TH1F*)hists[hname]->Clone(hname_eff);
            TH1F* den = (TH1F*)hists[hname]->Clone(hname_eff + "_den");
            den->Add(hists[hname_eff.ReplaceAll("_Aeff_", "_quadB_")]);
            den->Add(hists[hname_eff.ReplaceAll("_quadB_", "_quadC_")]);
            den->Add(hists[hname_eff.ReplaceAll("_quadC_", "_quadD_")]);
            hists[hname_eff]->Divide(den);
        }
    }
}

void mini_analyzer::add_NonClosureSys_variation(TString selection_tag)
{
    for(auto const& it : hists){
        TH1* h = it.second;
        TString hname = it.first;
        if(!hname.Contains(selection_tag)) continue;

        TString hname_CR1 = hname;
        hname_CR1.ReplaceAll("TightmlSV", "CR1mlSV");
        TString hname_CR1_quadA = hname_CR1;
        hname_CR1_quadA.ReplaceAll("BtoAwithCD", "quadA");
        // ABCD statistical variation
        hists_sys[hname + "_NonClosureUp"] = (TH1F*)h->Clone(hname + "_NonClosureUp");
        hists_sys[hname + "_NonClosureDown"] = (TH1F*)h->Clone(hname + "_NonClosureDown");
        for(int i = 1; i <= h->GetNbinsX(); i++){
            if(hists[hname_CR1_quadA]->GetBinContent(i) == 0 or hists[hname_CR1]->GetBinContent(i) == 0){
                hists_sys[hname + "_NonClosureUp"]->SetBinContent(i, h->GetBinContent(i)*2);
                hists_sys[hname + "_NonClosureDown"]->SetBinContent(i, h->GetBinContent(i)*0.5);
            }else{
                hists_sys[hname + "_NonClosureUp"]->SetBinContent(i, h->GetBinContent(i)*(1 + hists[hname_CR1_quadA]->GetBinContent(i)/hists[hname_CR1]->GetBinContent(i)));
                hists_sys[hname + "_NonClosureDown"]->SetBinContent(i, h->GetBinContent(i)*(1 - hists[hname_CR1_quadA]->GetBinContent(i)/hists[hname_CR1]->GetBinContent(i)));
            }
        }
    }
}

void mini_analyzer::add_ABCDstat_variation(TString selection_tag)
{
    for(auto const& it : hists){
        TH1* h = it.second;
        TString hname = it.first;
        if(!hname.Contains(selection_tag)) continue;

        TString hname_CR1 = hname;
        hname_CR1.ReplaceAll("TightmlSV", "CR1mlSV");
        // ABCD statistical variation
        hists_sys[hname + "_ABCDstatUp"] = (TH1F*)h->Clone(hname + "_ABCDstatUp");
        hists_sys[hname + "_ABCDstatDown"] = (TH1F*)h->Clone(hname + "_ABCDstatDown");
        for(int i = 1; i <= h->GetNbinsX(); i++){
            if(hists[hname_CR1]->GetBinContent(i) == 0){
                hists_sys[hname + "_ABCDstatUp"]->SetBinContent(i, h->GetBinContent(i)*2);
                hists_sys[hname + "_ABCDstatDown"]->SetBinContent(i, h->GetBinContent(i)*0);
            }else{
                hists_sys[hname + "_ABCDstatUp"]->SetBinContent(i, h->GetBinContent(i)*(1 + hists[hname_CR1]->GetBinErrorUp(i)/hists[hname_CR1]->GetBinContent(i)));
                hists_sys[hname + "_ABCDstatDown"]->SetBinContent(i, h->GetBinContent(i)*(1 - hists[hname_CR1]->GetBinErrorLow(i)/hists[hname_CR1]->GetBinContent(i)));
                //hists_sys[hname + "_ABCDstatUp"]->SetBinContent(i, h->GetBinContent(i)*(1 + hists[hname_CR1]->GetBinErrorUp(i)/hists[hname_CR1]->GetBinContent(i)/5.));
                //hists_sys[hname + "_ABCDstatDown"]->SetBinContent(i, h->GetBinContent(i)*(1 - hists[hname_CR1]->GetBinErrorLow(i)/hists[hname_CR1]->GetBinContent(i)/5.));
            }
        }
    }
}


// used for finding optimal PFN cutting point in ABCD method. Grid scan of possible cutting points is done
void mini_analyzer::set_signal_regions_gridscan()
{
    ABCDtags.clear();
    
    baseline_cutmlSV = event._SV_l1mass > 10 &&
                       (event._lFlavor == 0 || event._l1Flavor == 0 || event._l1Charge == event._lCharge || event._mll < 85 || event._mll > 95) &&
                       event._nTightLep == 1 &&
                       event._nTightJet <= 1;

    double baseline_cutPFN = 0.3;

    for(auto const& CP : CPtags){
        TString CPtag = CP.first;
        double PFNcut = CP.second;
        for(auto const& MV2 : MV2tags){
            TString MV2tag = MV2.first;
            int i_MV2      = get_PFNevaluation_index(event._evaluating_mass[MV2.second], event._lFlavor);

            if(baseline_cutmlSV){
                if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                    if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + CPtag + "_cutTightmlSV_quadA");
                    else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + CPtag + "_cutTightmlSV_quadC");
                }else {
                    if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + CPtag + "_cutTightmlSV_quadB");
                    else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + CPtag + "_cutTightmlSV_quadD");
                }
            }
            // control region 2: mlSV with signal region between 85 - 110 GeV
            if(baseline_cutmlSV){
                if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
                    if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + CPtag + "_cutTightCR2mlSV_quadA");
                    else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + CPtag + "_cutTightCR2mlSV_quadC");
                }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
                    if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + CPtag + "_cutTightCR2mlSV_quadB");
                    else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + CPtag + "_cutTightCR2mlSV_quadD");
                }
            }
        }
    }
    
    // Determine sr_flavor
    sr_flavor = "";
    if(event._l1Charge == event._lCharge) sr_flavor += "_SS";
    else sr_flavor += "_OS";

    if(event._l1Flavor == 0) sr_flavor += "_e";
    else if(event._l1Flavor == 1) sr_flavor += "_m";

    if(event._lFlavor == 0) sr_flavor += "e";
    else if(event._lFlavor == 1) sr_flavor += "m";

    //in case of makeMajToDirac, assume all SS HNL events are actually OS events
    if(makeMajToDirac and isSignal) sr_flavor.ReplaceAll("_SS", "_OS");
}

void mini_analyzer::set_signal_regions()
{
    ABCDtags.clear();

    //Training selection is already applied before filling BkgEstimator tree
    baseline_cutphill = event._mll < 80 &&
                        event._mll > 10 &&
                        event._dphill > 0.4 &&
                        event._nTightLep == 1 &&
                        event._nTightJet <= 1;

    baseline_cutmll = event._dphill > 2.3 &&
                      event._mll > 10 &&
                      event._nTightLep == 1 &&
                      event._nTightJet <= 1;

    baseline_cutphiORmll = event._mll > 10 &&
                           event._nTightLep == 1 &&
                           event._nTightJet <= 1;

    baseline_cutmlSV = event._SV_l1mass > 10 &&
                       (event._lFlavor == 0 || event._l1Flavor == 0 || event._l1Charge == event._lCharge || event._mll < 85 || event._mll > 95) &&
                       event._nTightLep == 1 &&
                       event._nTightJet <= 1;

    baseline_cutmlSV_nojetveto = event._SV_l1mass > 10 &&
                                 (event._lFlavor == 0 || event._l1Flavor == 0 || event._l1Charge == event._lCharge || event._mll < 85 || event._mll > 95) &&
                                 event._nTightLep == 1;

    baseline_cutCR3phill = event._SV_l1mass > 10 &&
                           (event._SV_l1mass < 50 || event._SV_l1mass > 85) &&
                           event._dphill > 0.4 &&
                           event._nTightLep == 1 &&
                           event._nTightJet <= 1;

    baseline_cutmlSV_CR2Jets = event._SV_l1mass > 10 &&
                             (event._lFlavor == 0 || event._l1Flavor == 0 || event._l1Charge == event._lCharge || event._mll < 85 || event._mll > 95) &&
                             event._nTightLep == 1 &&
                             event._nTightJet > 1;

    double baseline_cutPFN = 0.2;
    //double baseline_cutPFN_high = 0.8;

    //if(event._l1Charge != event._lCharge and event._mll > 85 and event._mll < 95) std::cout << "preselection: " << baseline_cutmlSV << " and mll: " << event._mll << std::endl;

    for(auto const& MV2 : MV2tags){
        TString MV2tag = MV2.first;
        int i_MV2      = get_PFNevaluation_index(event._evaluating_mass[MV2.second], event._lFlavor);
        //int i_MV2      = get_PFNevaluation_index(ceil(event._SV_mass), event._lFlavor);
        //double PFNcut  = get_PFNcut(event._evaluating_mass[MV2.second], event._lFlavor, event._is2016, event._is2017);
        double NTightPFNcut = get_NTightPFNcut(event._evaluating_mass[MV2.second], event._l1Flavor, event._lFlavor, event._l1Charge, event._lCharge, event._SV_mass, event._SV_PVSVdist_2D, event._l1Charge != event._lCharge, event._is2016, event._is2017);
        double PFNcut       = get_TightPFNcut(event._evaluating_mass[MV2.second], event._l1Flavor, event._lFlavor, event._SV_mass, event._SV_PVSVdist_2D, event._l1Charge != event._lCharge, event._is2016, event._is2017);
        double MediumPFNcut = get_MediumPFNcut(event._evaluating_mass[MV2.second], event._l1Flavor, event._lFlavor, event._SV_mass, event._SV_PVSVdist_2D, event._l1Charge != event._lCharge, event._is2016, event._is2017);
        double LoosePFNcut  = get_looserPFNcut(event._evaluating_mass[MV2.second], event._lFlavor, event._is2016, event._is2017);
        double VLoosePFNcut  = get_VLoosePFNcut(event._evaluating_mass[MV2.second], event._lFlavor, event._is2016, event._is2017);
        double VVLoosePFNcut  = get_VVLoosePFNcut(event._evaluating_mass[MV2.second], event._lFlavor, event._is2016, event._is2017);
        // Determine quadrant (in PFN output and dphi)
        //// dphill
        //if(baseline_cutphill){
        //    if(event._dphill > 2.3){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutphill_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutphill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutphill_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutphill_quadD");
        //    }
        //}
        //// control region 1: dphill only up to PFN LoosePFNcut
        //if(baseline_cutphill and event._JetTagVal[i_MV2] < LoosePFNcut){
        //    if(event._dphill > 2.3){
        //        if(event._JetTagVal[i_MV2] > 0.6) ABCDtags.push_back(MV2tag + "_cutCR1phill_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutCR1phill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > 0.6) ABCDtags.push_back(MV2tag + "_cutCR1phill_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutCR1phill_quadD");
        //    }
        //}
        //// control region 2: dphill only up to dphi of 2.3
        //if(baseline_cutphill and event._dphill < 2.3){
        //    if(event._dphill > 1.9){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR2phill_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutCR2phill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR2phill_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutCR2phill_quadD");
        //    }
        //}
        //// control region 3: dphill normal method within mlSV inverted region
        //if(baseline_cutCR3phill){
        //    if(event._dphill > 2.3){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR3phill_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutCR3phill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR3phill_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutCR3phill_quadD");
        //    }
        //}
        //// mll
        //if(baseline_cutmll){
        //    if(event._mll < 80){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutmll_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutmll_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutmll_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutmll_quadD");
        //    }
        //}
        //// dphill or mll
        //if(baseline_cutphiORmll){
        //    if(event._dphill > 2.3 and event._mll < 80){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutphiORmll_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutphiORmll_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutphiORmll_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutphiORmll_quadD");
        //    }
        //}
        // mlSV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutmlSV_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutmlSV_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutmlSV_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutmlSV_quadD");
            }
        }
        // control region 1: mlSV with PFN below LoosePFNcut
        if(baseline_cutmlSV and event._JetTagVal[i_MV2] < LoosePFNcut){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > 0.9) ABCDtags.push_back(MV2tag + "_cutCR1mlSV_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutCR1mlSV_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > 0.9) ABCDtags.push_back(MV2tag + "_cutCR1mlSV_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutCR1mlSV_quadD");
            }
        }
        //// control region 1 Old Tight: mlSV with PFN below VLoosePFNcut and mlSV upper limit still at 90
        //if(baseline_cutmlSV and event._JetTagVal[i_MV2] < VLoosePFNcut){
        //    if(event._SV_l1mass > 50 and event._SV_l1mass < 90){
        //        if(event._JetTagVal[i_MV2] > 0.7) ABCDtags.push_back(MV2tag + "_cutOldTightCR1mlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutOldTightCR1mlSV_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > 0.7) ABCDtags.push_back(MV2tag + "_cutOldTightCR1mlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutOldTightCR1mlSV_quadD");
        //    }
        //}
        // control region 1 Tight: mlSV with PFN below VLoosePFNcut
        if(baseline_cutmlSV and event._JetTagVal[i_MV2] < VLoosePFNcut){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > 0.7) ABCDtags.push_back(MV2tag + "_cutTightCR1mlSV_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR1mlSV_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > 0.7) ABCDtags.push_back(MV2tag + "_cutTightCR1mlSV_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR1mlSV_quadD");
            }
        }
        // control region 2: mlSV with signal region between 85 - 110 GeV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
                if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR2mlSV_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutCR2mlSV_quadC");
            }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
                if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR2mlSV_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutCR2mlSV_quadD");
            }
        }
        //// control region 3: mlSV with signal region between 10 - 50 Gev
        //if(baseline_cutmlSV){
        //    if(event._SV_l1mass < 50){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR3mlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutCR3mlSV_quadC");
        //    }else if(event._SV_l1mass > 85){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutCR3mlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutCR3mlSV_quadD");
        //    }
        //}



        // Tight predictions: PFN > PFNcut
        //// dphill
        //if(baseline_cutphill){
        //    if(event._dphill > 2.3){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightphill_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightphill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightphill_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightphill_quadD");
        //    }
        //}
        //// control region 2: dphill only up to dphi of 2.3
        //if(baseline_cutphill and event._dphill < 2.3){
        //    if(event._dphill > 1.9){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2phill_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR2phill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2phill_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR2phill_quadD");
        //    }
        //}
        //// control region 2: dphill normal method within mlSV inverted region
        //if(baseline_cutCR3phill){
        //    if(event._dphill > 2.3){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR3phill_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR3phill_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR3phill_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR3phill_quadD");
        //    }
        //}
        //// mll
        //if(baseline_cutmll){
        //    if(event._mll < 80){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightmll_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightmll_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightmll_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightmll_quadD");
        //    }
        //}
        //// dphill or mll
        //if(baseline_cutphiORmll){
        //    if(event._dphill > 2.3 and event._mll < 80){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightphiORmll_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightphiORmll_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightphiORmll_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightphiORmll_quadD");
        //    }
        //}
        // mlSV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightmlSV_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightmlSV_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightmlSV_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightmlSV_quadD");
            }
        }
        // Very Tight mlSV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > NTightPFNcut) ABCDtags.push_back(MV2tag + "_cutNTightmlSV_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutNTightmlSV_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > NTightPFNcut) ABCDtags.push_back(MV2tag + "_cutNTightmlSV_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutNTightmlSV_quadD");
            }
        }
        // Medium mlSV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediummlSV_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutMediummlSV_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediummlSV_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutMediummlSV_quadD");
            }
        }
        //// VLoose mlSV
        //if(baseline_cutmlSV){
        //    if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
        //        if(event._JetTagVal[i_MV2] > VLoosePFNcut) ABCDtags.push_back(MV2tag + "_cutVLoosemlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutVLoosemlSV_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > VLoosePFNcut) ABCDtags.push_back(MV2tag + "_cutVLoosemlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutVLoosemlSV_quadD");
        //    }
        //}
        //// VVLoose mlSV
        //if(baseline_cutmlSV){
        //    if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
        //        if(event._JetTagVal[i_MV2] > VVLoosePFNcut) ABCDtags.push_back(MV2tag + "_cutVVLoosemlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutVVLoosemlSV_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > VVLoosePFNcut) ABCDtags.push_back(MV2tag + "_cutVVLoosemlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutVVLoosemlSV_quadD");
        //    }
        //}
        //// mlSV with high baseline PFN cut
        //if(baseline_cutmlSV){
        //    if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutHighbmlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN_high) ABCDtags.push_back(MV2tag + "_cutHighbmlSV_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > LoosePFNcut) ABCDtags.push_back(MV2tag + "_cutHighbmlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN_high) ABCDtags.push_back(MV2tag + "_cutHighbmlSV_quadD");
        //    }
        //}
        //// Tight mlSV with high baseline PFN cut
        //if(baseline_cutmlSV){
        //    if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightHighbmlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN_high) ABCDtags.push_back(MV2tag + "_cutTightHighbmlSV_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightHighbmlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN_high) ABCDtags.push_back(MV2tag + "_cutTightHighbmlSV_quadD");
        //    }
        //}
        //// Medium mlSV with high baseline PFN cut
        //if(baseline_cutmlSV){
        //    if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
        //        if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediumHighbmlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN_high) ABCDtags.push_back(MV2tag + "_cutMediumHighbmlSV_quadC");
        //    }else {
        //        if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediumHighbmlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN_high) ABCDtags.push_back(MV2tag + "_cutMediumHighbmlSV_quadD");
        //    }
        //}
        // control region 2: mlSV with signal region between 85 - 110 GeV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
                if(event._JetTagVal[i_MV2] > NTightPFNcut) ABCDtags.push_back(MV2tag + "_cutNTightCR2mlSV_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutNTightCR2mlSV_quadC");
            }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
                if(event._JetTagVal[i_MV2] > NTightPFNcut) ABCDtags.push_back(MV2tag + "_cutNTightCR2mlSV_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutNTightCR2mlSV_quadD");
            }
        }
        // control region 2: mlSV with signal region between 85 - 110 GeV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_quadC");
            }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_quadD");
            }
        }
        // control region 2: mlSV with signal region between 85 - 110 GeV without jet veto
        if(baseline_cutmlSV_nojetveto){
            if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2NoJetVetomlSV_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR2NoJetVetomlSV_quadC");
            }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2NoJetVetomlSV_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR2NoJetVetomlSV_quadD");
            }
        }
        //// control region 3: mlSV with signal region between 10 - 50 Gev
        //if(baseline_cutmlSV){
        //    if(event._SV_l1mass < 50){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR3mlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR3mlSV_quadC");
        //    }else if(event._SV_l1mass > 85){
        //        if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR3mlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR3mlSV_quadD");
        //    }
        //}
        // control region 2: mlSV with signal region between 85 - 110 GeV
        if(baseline_cutmlSV){
            if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediumCR2mlSV_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutMediumCR2mlSV_quadC");
            }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediumCR2mlSV_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutMediumCR2mlSV_quadD");
            }
        }
        //// CR2 VLoose
        //if(baseline_cutmlSV){
        //    if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
        //        if(event._JetTagVal[i_MV2] > VLoosePFNcut) ABCDtags.push_back(MV2tag + "_cutVLooseCR2mlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutVLooseCR2mlSV_quadC");
        //    }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
        //        if(event._JetTagVal[i_MV2] > VLoosePFNcut) ABCDtags.push_back(MV2tag + "_cutVLooseCR2mlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutVLooseCR2mlSV_quadD");
        //    }
        //}
        //// CR2 VVLoose
        //if(baseline_cutmlSV){
        //    if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
        //        if(event._JetTagVal[i_MV2] > VVLoosePFNcut) ABCDtags.push_back(MV2tag + "_cutVVLooseCR2mlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutVVLooseCR2mlSV_quadC");
        //    }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
        //        if(event._JetTagVal[i_MV2] > VVLoosePFNcut) ABCDtags.push_back(MV2tag + "_cutVVLooseCR2mlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutVVLooseCR2mlSV_quadD");
        //    }
        //}
        if(baseline_cutmlSV_nojetveto){
            if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediumCR2NoJetVetomlSV_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutMediumCR2NoJetVetomlSV_quadC");
            }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediumCR2NoJetVetomlSV_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutMediumCR2NoJetVetomlSV_quadD");
            }
        }
        //// control region 3: mlSV with signal region between 10 - 50 Gev
        //if(baseline_cutmlSV){
        //    if(event._SV_l1mass < 50){
        //        if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediumCR3mlSV_quadA");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutMediumCR3mlSV_quadC");
        //    }else if(event._SV_l1mass > 85){
        //        if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediumCR3mlSV_quadB");
        //        else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutMediumCR3mlSV_quadD");
        //    }
        //}
        // mlSV Inverted Jets CR
        if(baseline_cutmlSV_CR2Jets){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightmlSV_CR2Jets_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightmlSV_CR2Jets_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightmlSV_CR2Jets_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightmlSV_CR2Jets_quadD");
            }
        }
        // Medium mlSV Inverted Jets CR
        if(baseline_cutmlSV_CR2Jets){
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediummlSV_CR2Jets_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutMediummlSV_CR2Jets_quadC");
            }else {
                if(event._JetTagVal[i_MV2] > MediumPFNcut) ABCDtags.push_back(MV2tag + "_cutMediummlSV_CR2Jets_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutMediummlSV_CR2Jets_quadD");
            }
        }
        // control region 2 in Inverted Jets CR: mlSV with signal region between 85 - 110 GeV
        if(baseline_cutmlSV_CR2Jets){
            if(event._SV_l1mass > 85 and event._SV_l1mass < 110){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_CR2Jets_quadA");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_CR2Jets_quadC");
            }else if(event._SV_l1mass < 50 or event._SV_l1mass > 110){
                if(event._JetTagVal[i_MV2] > PFNcut) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_CR2Jets_quadB");
                else if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutTightCR2mlSV_CR2Jets_quadD");
            }
        }

        //extra noSR plots
        if(baseline_cutmlSV){
            if(!(isData and isBlind)) ABCDtags.push_back(MV2tag + "_cutbaselinemlSV");
            if(event._JetTagVal[i_MV2] < 0.8) ABCDtags.push_back(MV2tag + "_cutbaselinemlSV_noSR");

            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(!(isData and isBlind) and event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutinsidemlSV");
                if(event._JetTagVal[i_MV2] > baseline_cutPFN and event._JetTagVal[i_MV2] < 0.8) ABCDtags.push_back(MV2tag + "_cutinsidemlSV_noSR");
            }else{
                if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutoutsidemlSV");
            }
        }
        if(baseline_cutmlSV_CR2Jets){
            ABCDtags.push_back(MV2tag + "_cutbaselinemlSV_CR2Jets");
            if(event._SV_l1mass > 50 and event._SV_l1mass < 85){
                if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutinsidemlSV_CR2Jets");
            }else{
                if(event._JetTagVal[i_MV2] > baseline_cutPFN) ABCDtags.push_back(MV2tag + "_cutoutsidemlSV_CR2Jets");
            }
        }
    }


    // Determine sr_flavor
    sr_flavor = "";
    if(event._l1Charge == event._lCharge) sr_flavor += "_SS";
    else sr_flavor += "_OS";

    if(event._l1Flavor == 0) sr_flavor += "_e";
    else if(event._l1Flavor == 1) sr_flavor += "_m";

    if(event._lFlavor == 0) sr_flavor += "e";
    else if(event._lFlavor == 1) sr_flavor += "m";

    //in case of makeMajToDirac, assume all SS HNL events are actually OS events
    if(makeMajToDirac and isSignal) sr_flavor.ReplaceAll("_SS", "_OS");

    // Determine Low and High Mass bin
    double lowmassbinnr = get_SRShape3bin(event._SV_PVSVdist_2D, event._SV_mass, "M-5_", sr_flavor);//gives 0,1,2,3,4,5 based on L_xy and SVmass
    double highmassbinnr = get_SRShape3bin(event._SV_PVSVdist_2D, event._SV_mass, "M-10_", sr_flavor);//gives 0,1,2,3,4,5 based on L_xy and SVmass
    LowMassBin = ""; HighMassBin = "";
    if(equals(lowmassbinnr, 0., 1e-4)) LowMassBin = "_L04M02";
    if(equals(lowmassbinnr, 1., 1e-4)) LowMassBin = "_L41M02";
    if(equals(lowmassbinnr, 2., 1e-4)) LowMassBin = "_L10M02";
    if(equals(lowmassbinnr, 3., 1e-4)) LowMassBin = "_L04M2X";
    if(equals(lowmassbinnr, 4., 1e-4)) LowMassBin = "_L41M2X";
    if(equals(lowmassbinnr, 5., 1e-4)) LowMassBin = "_L10M2X";
    if(equals(highmassbinnr, 0., 1e-4)) HighMassBin = "_L01M06";
    if(equals(highmassbinnr, 1., 1e-4)) HighMassBin = "_L15M06";
    if(equals(highmassbinnr, 2., 1e-4)) HighMassBin = "_L5XM06";
    if(equals(highmassbinnr, 3., 1e-4)) HighMassBin = "_L01M6X";
    if(equals(highmassbinnr, 4., 1e-4)) HighMassBin = "_L15M6X";
    if(equals(highmassbinnr, 5., 1e-4)) HighMassBin = "_L5XM6X";

    if(event.BkgEstimator_filename.Contains("JECDown") or event.BkgEstimator_filename.Contains("JECUp") or event.BkgEstimator_filename.Contains("JERDown") or event.BkgEstimator_filename.Contains("JERUp")){
        for(auto it = ABCDtags.begin(); it != ABCDtags.end(); ){
            if(!((*it).Contains("_cutTightmlSV_quadA") or (*it).Contains("_cutNTightmlSV_quadA"))) it = ABCDtags.erase(it);
            else ++it;
        }
    }

}

void mini_analyzer::add_histograms_gridscan()
{
    std::cout << "Initializing histograms" << std::endl;
    for(const TString& lep_region : {"_OS_ee", "_SS_ee", "_OS_mm", "_SS_mm", "_OS_em", "_SS_em", "_OS_me", "_SS_me"}){
        for(const auto& MV2 : MV2tags){
            TString MV2tag = MV2.first;
            if(!MV2tag.Contains("2e-06")) continue;
            for(const auto& CP : CPtags){
                TString CPtag = CP.first;
                for(const TString& cut2region : {"_cutTightmlSV", "_cutTightCR2mlSV"}){
                    for(const TString& quadrant : {"_quadB", "_quadC", "_quadD"/*, "_quadCD", "_quadBD", "_quadBCD"*/,  "_CoverD"/*, "_BoverD", "_DtoCwithCD"*/, "_BtoAwithCD"/*, "_CtoAwithBD"*/}){
                        //add_standard_histograms(lep_region + MV2tag + cut2region + quadrant);
//                        add_pfn_histograms(lep_region + MV2tag + CPtag + cut2region + quadrant);
                    }
                    //add_fraction_histograms(lep_region + MV2tag + CPtag + cut2region);

                    // only make region A histograms if we're not running over data
                    if(!(isData and isBlind) or cut2region.Contains("CR")){
                        for(const TString & quadrant : {"_quadA"/*, "_quadAB", "_quadAC"*/, "_AoverB", "_AoverC"/*, "_quadABCD"*/}){
                            //add_standard_histograms(lep_region + MV2tag + cut2region + quadrant);
//                            add_pfn_histograms(lep_region + MV2tag + CPtag + cut2region + quadrant);
                        }
                    }
                }
            }
        }
    }
    // Signal region yield histograms
    for(const TString& lep_region : {"_mm", "_ee", "_me", "_em", "_2l"}){
        for(const auto& MV2 : MV2tags){
            TString MV2tag = MV2.first;
            for(const auto& CP : CPtags){
                TString CPtag = CP.first;
                for(const TString& cut2region : {"_cutTightmlSV", "_cutTightCR2mlSV"}){
                    for(const TString& quadrant : {"_quadB", "_quadC", "_quadD"/*, "_quadCD", "_quadBD", "_quadBCD"*/,  "_CoverD"/*, "_BoverD", "_DtoCwithCD"*/, "_BtoAwithCD"/*, "_CtoAwithBD"*/}){
                        add_Shape_SR_histograms(lep_region + MV2tag + CPtag + cut2region + quadrant);
                    }
                    if(!(isData and isBlind) or cut2region.Contains("CR")){
                        for(const TString & quadrant : {"_quadA"/*, "_quadAB", "_quadAC"*/, "_AoverB", "_AoverC"/*, "_quadABCD"*/}){
                            add_Shape_SR_histograms(lep_region + MV2tag + CPtag + cut2region + quadrant);
                        }
                    }
                }
            }
        }
    }
    //for(const auto& hist : hists) hist.second->Sumw2();
}

void mini_analyzer::add_histograms()
{
    std::cout << "Initializing histograms" << std::endl;
    std::vector<TString> lowmassbins({"_L04M02", "_L41M02", "_L10M02", "_L04M2X", "_L41M2X", "_L10M2X"}), highmassbins({"_L01M06", "_L15M06", "_L5XM06", "_L01M6X", "_L15M6X", "_L5XM6X"});
    for(const TString& lep_region : {"_OS_ee", "_SS_ee", "_OS_mm", "_SS_mm", "_OS_em", "_SS_em", "_OS_me", "_SS_me"}){
        for(const auto& MV2 : MV2tags){
            TString MV2tag = MV2.first;
            //if(!(MV2tag.Contains("2e-06") or MV2tag.Contains("4e-06"))) continue;
            if(!MV2tag.Contains("2e-06")) continue;
            for(const TString& cut2region : {/*"_cutphill", "_cutmll", "_cutphiORmll",*/ "_cutmlSV"/*, "_cutOldTightCR1mlSV"*/, "_cutCR1mlSV", "_cutCR2mlSV"/*, "_cutCR3mlSV", "_cutCR1phill", "_cutCR2phill", "_cutCR3phill", "_cutTightphill", "_cutTightmll", "_cutTightphiORmll"*/, "_cutTightmlSV", "_cutMediummlSV"/*, "_cutVLoosemlSV", "_cutVVLoosemlSV"*/, "_cutTightCR1mlSV", "_cutNTightCR2mlSV", "_cutTightCR2mlSV", "_cutTightCR2NoJetVetomlSV", "_cutTightCR2mlSV_CR2Jets"/*, "_cutTightCR3mlSV", "_cutTightCR2phill", "_cutTightCR3phill"*/, "_cutMediumCR2mlSV"/*, "_cutVVLooseCR2mlSV", "_cutVLooseCR2mlSV"*/, "_cutMediumCR2NoJetVetomlSV"/*, "_cutMediumCR3mlSV"*/, "_cutTightmlSV_CR2Jets", "_cutMediummlSV_CR2Jets"/*, "_cutHighbmlSV", "_cutMediumHighbmlSV", "_cutTightHighbmlSV"*/, "_cutNTightmlSV"}){
                for(const TString& quadrant : {"_quadB", "_quadC", "_quadD", "_quadCD", "_quadBD", "_quadBCD",  "_CoverD", "_BoverD"/*, "_DtoCwithCD"*/, "_BtoAwithCD", "_CtoAwithBD"}){
                    add_standard_histograms(lep_region + MV2tag + cut2region + quadrant);
                    if(cut2region.Contains("_cutTightmlSV")){
                        add_pfn_histograms(lep_region + MV2tag + cut2region + quadrant);
                        add_extra_histograms(lep_region + MV2tag + cut2region + quadrant);
                        std::vector<TString> SRbins;
                        if(MV2tag.Contains("M-5")) SRbins = lowmassbins;
                        else                       SRbins = highmassbins;
                        for(const TString& SRbin : SRbins){
                            add_standard_histograms(lep_region + MV2tag + cut2region + quadrant + SRbin);
                            add_extra_histograms(lep_region + MV2tag + cut2region + quadrant + SRbin);
                        }
                    }
                }
    //            //add_fraction_histograms(lep_region + MV2tag + cut2region);

    //            // only make region A histograms if we're not running over data
                if(!(isData and isBlind) or cut2region.Contains("CR")){
                    for(const TString & quadrant : {"_quadA", "_quadAB", "_quadAC", "_AoverB", "_AoverC", "_quadABCD"}){
                        add_standard_histograms(lep_region + MV2tag + cut2region + quadrant);
                        if(cut2region.Contains("_cutTightmlSV")){
                            add_pfn_histograms(lep_region + MV2tag + cut2region + quadrant);
                            add_extra_histograms(lep_region + MV2tag + cut2region + quadrant);
                            std::vector<TString> SRbins;
                            if(MV2tag.Contains("M-5")) SRbins = lowmassbins;
                            else                       SRbins = highmassbins;
                            for(const TString& SRbin : SRbins){
                                add_standard_histograms(lep_region + MV2tag + cut2region + quadrant + SRbin);
                                add_extra_histograms(lep_region + MV2tag + cut2region + quadrant + SRbin);
                            }
                        }
                    }
                }
            }

            std::vector<TString> cutregions;
            if(isData and isBlind) cutregions = {"_cutbaselinemlSV_noSR", "_cutinsidemlSV_noSR", "_cutoutsidemlSV", "_cutbaselinemlSV_CR2Jets", "_cutinsidemlSV_CR2Jets", "_cutoutsidemlSV_CR2Jets"};
            else       cutregions = {"_cutbaselinemlSV_noSR", "_cutinsidemlSV_noSR", "_cutoutsidemlSV", "_cutbaselinemlSV", "_cutinsidemlSV", "_cutbaselinemlSV_CR2Jets", "_cutinsidemlSV_CR2Jets", "_cutoutsidemlSV_CR2Jets"};
            for(const TString& cutregion : cutregions){
                add_standard_histograms(lep_region + MV2tag + cutregion);
                add_extra_histograms(lep_region + MV2tag + cutregion);
                add_pfn_histograms(lep_region + MV2tag + cutregion);
                std::vector<TString> SRbins;
                if(MV2tag.Contains("M-5")) SRbins = lowmassbins;
                else                       SRbins = highmassbins;
                for(const TString& SRbin : SRbins){
                    add_standard_histograms(lep_region + MV2tag + cutregion + SRbin);
                    add_extra_histograms(lep_region + MV2tag + cutregion + SRbin);
                }
            }
        }
    }
    // Signal region yield histograms
    for(const TString& lep_region : {"_mm", "_ee", "_em", "_me", "_2l"}){
        for(const auto& MV2 : MV2tags){
            TString MV2tag = MV2.first;
            bool TagExtraPlots = MV2tag.Contains("2e-06") or MV2tag.Contains("4e-06");
            for(const TString& cut2region : {/*"_cutphill", "_cutmll", "_cutphiORmll",*/ "_cutmlSV"/*, "_cutOldTightCR1mlSV"*/, "_cutCR1mlSV", "_cutCR2mlSV"/*, "_cutCR3mlSV", "_cutCR1phill", "_cutCR2phill", "_cutCR3phill", "_cutTightphill", "_cutTightmll", "_cutTightphiORmll"*/, "_cutTightmlSV", "_cutMediummlSV"/*, "_cutVLoosemlSV", "_cutVVLoosemlSV"*/, "_cutTightCR1mlSV", "_cutNTightCR2mlSV", "_cutTightCR2mlSV", "_cutTightCR2NoJetVetomlSV", "_cutTightCR2mlSV_CR2Jets"/*, "_cutTightCR3mlSV", "_cutTightCR2phill", "_cutTightCR3phill"*/, "_cutMediumCR2mlSV"/*, "_cutVVLooseCR2mlSV", "_cutVLooseCR2mlSV"*/, "_cutMediumCR2NoJetVetomlSV"/*, "_cutMediumCR3mlSV"*/, "_cutTightmlSV_CR2Jets", "_cutMediummlSV_CR2Jets"/*, "_cutHighbmlSV", "_cutMediumHighbmlSV", "_cutTightHighbmlSV"*/, "_cutNTightmlSV"}){

                if(!(MV2tag.Contains("2e-06") or cut2region == "_cutTightmlSV" or cut2region == "_cutNTightmlSV")) continue;

                for(const TString& quadrant : {"_quadB", "_quadC", "_quadD", "_quadCD", "_quadBD", "_quadBCD",  "_CoverD", "_BoverD"/*, "_DtoCwithCD"*/, "_BtoAwithCD", "_CtoAwithBD"}){
                    add_Shape_SR_histograms(lep_region + MV2tag + cut2region + quadrant);
                    if(TagExtraPlots) add_Shape_SR_extra_histograms(lep_region + MV2tag + cut2region + quadrant);
                }
                if(!(isData and isBlind) or cut2region.Contains("CR")){
                    for(const TString & quadrant : {"_quadA", "_quadAB", "_quadAC", "_AoverB", "_AoverC", "_quadABCD"}){
                        add_Shape_SR_histograms(lep_region + MV2tag + cut2region + quadrant);
                        if(TagExtraPlots) add_Shape_SR_extra_histograms(lep_region + MV2tag + cut2region + quadrant);
                    }
                }
            }
            if(!(isData and isBlind)){
                for(const auto& var : variations){
                    add_Shape_SR_histograms(lep_region + MV2tag + "_cutTightmlSV_quadA" + var.first);
                    add_Shape_SR_histograms(lep_region + MV2tag + "_cutNTightmlSV_quadA" + var.first);
                }
            }

            std::vector<TString> cutregions;
            if(isData and isBlind) cutregions = {"_cutbaselinemlSV_noSR", "_cutinsidemlSV_noSR", "_cutoutsidemlSV", "_cutbaselinemlSV_CR2Jets", "_cutinsidemlSV_CR2Jets", "_cutoutsidemlSV_CR2Jets"};
            else       cutregions = {"_cutbaselinemlSV_noSR", "_cutinsidemlSV_noSR", "_cutoutsidemlSV", "_cutbaselinemlSV", "_cutinsidemlSV", "_cutbaselinemlSV_CR2Jets", "_cutinsidemlSV_CR2Jets", "_cutoutsidemlSV_CR2Jets"};
            for(const TString& cutregion : cutregions){
                add_Shape_SR_histograms(lep_region + MV2tag + cutregion);
                if(TagExtraPlots) add_Shape_SR_extra_histograms(lep_region + MV2tag + cutregion);
            }
        }
    }
    for(const auto& hist : hists) hist.second->Sumw2();
}


void mini_analyzer::add_fraction_histograms(TString prefix)
{
    hists[prefix+"_QuadFractions"]          = new TH1F(prefix+"_QuadFractions", ";;Fraction", 4, 0, 4);
    //hists[prefix+"_QuadFractions_unw"]      = new TH1F(prefix+"_QuadFractions_unw", ";;Unweighted Events", 4, 0, 4);
    hists2D[prefix+"_QuadFractions_2D"]     = new TH2F(prefix+"_QuadFractions_2D", ";;", 4, 0, 4, 4, 0, 4);
    hists2D[prefix+"_QuadFractions2_2D"]    = new TH2F(prefix+"_QuadFractions2_2D", ";;", 2, 0, 2, 4, 0, 4);
}


void mini_analyzer::add_standard_histograms(TString prefix)
{
    hists[prefix+"_Yield"]              = new TH1F(prefix+"_Yield", ";;Events", 1, 0, 1);
    hists[prefix+"_mll"]                = new TH1F(prefix+"_mll", ";#it{m}_{ll} [GeV];Events", 30, 0, 130);
    hists[prefix+"_PV-SVdxy"]           = new TH1F(prefix+"_PV-SVdxy", ";L_{xy} [cm];Events", 40, 0, 40);
    hists[prefix+"_SVl1mass"]           = new TH1F(prefix+"_SVl1mass", ";l_{1}+SV Mass [GeV];Events", 15, 0, 140);
}

void mini_analyzer::add_extra_histograms(TString prefix)
{
    //hists[prefix+"_SRShape"]            = new TH1F(prefix+"_SRShape", ";;Events", 4, 0, 4);
    //hists[prefix+"_SRShape2"]           = new TH1F(prefix+"_SRShape2", ";;Events", 2, 0, 2);
    //hists[prefix+"_nTightJet"]          = new TH1F(prefix+"_nTightJet", ";N_{Jet};Events", 10, 0, 10);
    hists[prefix+"_nMediumBJet"]        = new TH1F(prefix+"_nMediumBJet", ";N_{BJet};Events", 10, 0, 10);
    //hists[prefix+"_nLooseBJet"]         = new TH1F(prefix+"_nLooseBJet", ";N_{BJet};Events", 10, 0, 10);
    hists[prefix+"_JetPt"]              = new TH1F(prefix+"_JetPt", ";Jet #it{p}_{T} [GeV];Events", 15, 0, 100);
    hists[prefix+"_JetEta"]             = new TH1F(prefix+"_JetEta", ";Jet #eta;Events", 15, -3, 3);
    hists[prefix+"_JetPhi"]             = new TH1F(prefix+"_JetPhi", ";Jet #phi;Events", 15, -3.14, 3.14);
    //hists[prefix+"_nTightLep"]          = new TH1F(prefix+"_nTightLep", ";N_{Lep};Events", 15, 0, 10);
    hists[prefix+"_l2pt"]              = new TH1F(prefix+"_l2pt", ";l_{2} #it{p}_{T} [GeV];Events", 15, 0, 50);
    hists[prefix+"_l2eta"]             = new TH1F(prefix+"_l2eta", ";l_{2} #eta;Events", 15, -3, 3);
    //hists[prefix+"_l2phi"]             = new TH1F(prefix+"_l2phi", ";l_{2} #phi;Events", 15, -3.14, 3.14);
    hists[prefix+"_l2dxy"]             = new TH1F(prefix+"_l2dxy", ";l_{2} dxy [cm];Events", 15, 0, 0.5);
    hists[prefix+"_l2dxy2"]            = new TH1F(prefix+"_l2dxy2", ";l_{2} dxy [cm];Events", 15, 0, 0.05);
    hists[prefix+"_l2dz"]              = new TH1F(prefix+"_l2dz", ";l_{2} dz [cm];Events", 15, 0, 2);
    hists[prefix+"_l23dIPSig"]         = new TH1F(prefix+"_l23dIPSig", ";l_{2} 3dIPSig;Events", 15, 0, 20);
    hists[prefix+"_l2reliso"]          = new TH1F(prefix+"_l2reliso", ";l_{2} Rel Iso;Events", 15, 0, 3.5);
    hists[prefix+"_l2reliso2"]         = new TH1F(prefix+"_l2reliso2", ";l_{2} Rel Iso;Events", 15, 0, 0.4);
    hists[prefix+"_l2ptratio"]         = new TH1F(prefix+"_l2ptratio", ";l_{2} #it{p}_{T}^{ratio} [GeV];Events", 15, 0, 1);
    hists[prefix+"_l2ptrel"]           = new TH1F(prefix+"_l2ptrel", ";l_{2} #it{p}_{T}^{rel} [GeV];Events", 15, 0, 10);
    hists[prefix+"_l2NumberOfHits"]    = new TH1F(prefix+"_l2NumberOfHits", ";l_{2} Nr. of Hits;Events", 20, 10, 30);
    hists[prefix+"_l2NumberOfPixHits"] = new TH1F(prefix+"_l2NumberOfPixHits", ";l_{2} Nr. of Pixel Hits;Events", 15, 0, 15);
    //hists[prefix+"_l2MuonSegComp"]     = new TH1F(prefix+"_l2MuonSegComp", ";l_{2} Muon Segment Comp.;Events", 15, 0, 1);
    //hists[prefix+"_l2MuonTime"]        = new TH1F(prefix+"_l2MuonTime", ";l_{2} Muon Time;Events", 15, -10, 10);
    //hists[prefix+"_l2MuonRPCTime"]     = new TH1F(prefix+"_l2MuonRPCTime", ";l_{2} Muon RPC Time;Events", 15, -0.2, 0.2);
    hists[prefix+"_l2InnerTrackValidFraction"] = new TH1F(prefix+"_l2InnerTrackValidFraction", ";l_{2} Inner Track Valid Fraction;Events", 15, 0, 1);
    
    hists[prefix+"_l1pt"]              = new TH1F(prefix+"_l1pt", ";l_{1} #it{p}_{T} [GeV];Events", 15, 0, 150);
    hists[prefix+"_l1eta"]             = new TH1F(prefix+"_l1eta", ";l_{1} #eta;Events", 15, -3, 3);
    //hists[prefix+"_l1phi"]             = new TH1F(prefix+"_l1phi", ";l_{1} #phi;Events", 15, -3.14, 3.14);

    hists[prefix+"_dRll"]               = new TH1F(prefix+"_dRll", ";#it{#Delta R}_{ll};Events", 15, 0, 5);
    hists[prefix+"_dphill"]             = new TH1F(prefix+"_dphill", ";#it{#Delta #phi}_{ll};Events", 15, 0, 3.14);
    hists[prefix+"_detall"]             = new TH1F(prefix+"_detall", ";#it{#Delta #eta}_{ll};Events", 15, 0, 5);
    //hists[prefix+"_dTimell"]             = new TH1F(prefix+"_dTimell", ";#it{#Delta Time}_{ll};Events", 15, 0, 5);
    hists[prefix+"_dabsetall"]          = new TH1F(prefix+"_dabsetall", ";#Delta |#eta|_{ll};Events", 15, 0, 5);
    //hists[prefix+"_cosine3Dll"]         = new TH1F(prefix+"_cosine3Dll", ";cosine3D_{ll};Events", 15, -1, 1);
    hists[prefix+"_dRljet"]             = new TH1F(prefix+"_dRljet", ";#it{#Delta R}_{l,jet};Events", 15, 0, 1);
    hists[prefix+"_jetPtOverlPt"]       = new TH1F(prefix+"_jetPtOverlPt", ";jet #it{p}_{T} / l_{2} #it{p}_{T};Events", 20, 0, 10);

    double PVSVdxybins[3] = {0, 10, 60};
    hists[prefix+"_PV-SVdxy"]  = new TH1F(prefix+"_PV-SVdxy", ";L_{xy} [cm];Events", 10, 0, 50);
    hists[prefix+"_PV-SVdxy2"]       = new TH1F(prefix+"_PV-SVdxy2", ";L_{xy} [cm];Events", 40, 0, 40);
    hists[prefix+"_PV-SVdxy3"]  = new TH1F(prefix+"_PV-SVdxy3", ";L_{xy} [cm];Events", 2, PVSVdxybins);
    hists[prefix+"_PV-SVdxyz"]      = new TH1F(prefix+"_PV-SVdxyz", ";L_{xyz} [cm];Events", 15, 0, 100);
    hists[prefix+"_PV-SVdxyz2"] = new TH1F(prefix+"_PV-SVdxyz2", ";L_{xyz} [cm];Events", 15, 0, 20);
    hists[prefix+"_ntracks"]        = new TH1F(prefix+"_ntracks", ";# of tracks used in SVfit;Events", 10, 0, 10);
    hists[prefix+"_SVmass"]         = new TH1F(prefix+"_SVmass", ";SV Mass [GeV];Events", 20, 0, 20);
    double SVmassbins[3] = {0, 4, 20};
    hists[prefix+"_SVmass2"]         = new TH1F(prefix+"_SVmass2", ";SV Mass [GeV];Events", 2, SVmassbins);
    hists[prefix+"_SVmass3"]         = new TH1F(prefix+"_SVmass3", ";SV Mass [GeV];Events", 25, 0, 5);
    //hists[prefix+"_SVl1mass"]         = new TH1F(prefix+"_SVl1mass", ";l_{1}+SV Mass [GeV];Events", 15, 0, 140);
    hists[prefix+"_SVpt"]             = new TH1F(prefix+"_SVpt", ";SV #it{p}_{T} [GeV];Events", 15, 0, 100);
    hists[prefix+"_SVeta"]            = new TH1F(prefix+"_SVeta", ";SV #eta;Events", 15, -3, 3);
    //hists[prefix+"_SVphi"]            = new TH1F(prefix+"_SVphi", ";SV #phi;Events", 15, -3.14, 3.14);
    hists[prefix+"_SVnormchi2"]       = new TH1F(prefix+"_SVnormchi2", ";Normalized #Chi^{2};Events", 15, 0, 10);
    hists[prefix+"_SVchsum"]       = new TH1F(prefix+"_SVchsum", ";SV Charge sum;Events", 8, -4, 4);
    hists[prefix+"_SVchsum2tr"]       = new TH1F(prefix+"_SVchsum2tr", ";SV Charge sum;Events", 8, -4, 4);

    hists2D[prefix+"_mllvsSVmass"] = new TH2F(prefix+"_mllvsSVmass", ";M_{ll} [GeV];M_{SV} [GeV]", 150, 0, 150, 150, 0, 20);
    hists2D[prefix+"_mllvsSVl1mass"] = new TH2F(prefix+"_mllvsSVl1mass", ";M_{ll} [GeV];M_{l_1,SV} [GeV]", 150, 0, 150, 150, 0, 150);
    hists2D[prefix+"_mllvsPVSVdxy"] = new TH2F(prefix+"_mllvsPVSVdxy", ";M_{ll} [GeV];L_{xy} [cm]", 150, 0, 150, 150, 0, 60);
    hists2D[prefix+"_l2dxyvsPVSVdxy"] = new TH2F(prefix+"_l2dxyvsPVSVdxy", ";l_{2} dxy [cm];L_{xy} [cm]", 150, 0, 4, 150, 0, 60);
    //hists2D[prefix+"_dphillvsSVmass"] = new TH2F(prefix+"_dphillvsSVmass", "#Delta #phi_{ll};M_{SV} [GeV]", 150, 0, 3.14, 150, 0, 20);
    //hists2D[prefix+"_dphillvsPVSVdxy"] = new TH2F(prefix+"_dphillvsPVSVdxy", "#Delta #phi_{ll};L_{xy} [cm]", 150, 0, 3.14, 150, 0, 60);
    hists2D[prefix+"_lprovenance"] = new TH2F(prefix+"_lprovenance", "", 19, 0, 19, 19, 0, 19);
    hists2D[prefix+"_lprovenanceCompressed"] = new TH2F(prefix+"_lprovenanceCompressed", "", 5, 0, 5, 5, 0, 5);

}

void mini_analyzer::add_pfn_histograms(TString prefix)
{
    //hists2D[prefix+"_PFNvsdphill"]      = new TH2F(prefix+"_PFNvsdphill", ";PFN output; #Delta #phi_{ll}", 40, 0, 1, 40, 0, 3.14);
    //hists2D[prefix+"_PFNvsmll"]         = new TH2F(prefix+"_PFNvsmll", ";PFN output; M_{ll} [GeV]", 40, 0, 1, 40, 0, 150);
    hists2D[prefix+"_PFNvsmlSV"]        = new TH2F(prefix+"_PFNvsmlSV", ";PFN output; M_{l,SV} [GeV]", 40, 0, 1, 40, 0, 150);
    hists2D[prefix+"_PFNvsmlSVzoom"]        = new TH2F(prefix+"_PFNvsmlSVzoom", ";PFN output; M_{l,SV} [GeV]", 40, 0.9, 1, 40, 0, 150);
    hists[prefix+"_JetTagVal"]          = new TH1F(prefix+"_JetTagVal", ";Jet Tag Value;Events", 20, 0, 1);
    hists[prefix+"_JetTagValzoom"]     = new TH1F(prefix+"_JetTagValzoom", ";Jet Tag Value;Events", 10, 0.9, 1);
}


void mini_analyzer::add_Shape_SR_histograms(TString prefix)
{
    if(prefix.Contains("_mm") or prefix.Contains("_ee") or prefix.Contains("_em") or prefix.Contains("_me")){
        TString Shape_SRname    = prefix+"_Shape_SR";
        int nbins = 12;
        //if(prefix.Contains("_SS") and prefix.Contains("_M-10_")) nbins = 11;
        if((prefix.Contains("_mm") or prefix.Contains("_em")) and prefix.Contains("_M-10_")) nbins = 11;
        hists[Shape_SRname]     = new TH1F(Shape_SRname, ";#Delta (PV-SV)_{2D} [cm];Events", nbins, 0, nbins);
        if(makeMajToDirac or isData) hists["_OS"+Shape_SRname] = new TH1F("_OS"+Shape_SRname, ";#Delta (PV-SV)_{2D} [cm];Events", 6, 0, 6);

        std::vector<TString> binnames;
        if(prefix.Contains("_M-5_")){
            binnames = {"0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10"};
        //}else if(prefix.Contains("_SS") and prefix.Contains("_M-10_")){
        }else if((prefix.Contains("_mm") or prefix.Contains("_em")) and prefix.Contains("_M-10_")){
            binnames = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", ">1"};
        }else if(prefix.Contains("_M-10_")){
            binnames = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
        }
        for(unsigned i = 1; i <= binnames.size(); ++i){
            hists[Shape_SRname]->GetXaxis()->SetBinLabel(i, binnames[i-1]);
            if((makeMajToDirac or isData) and i < 7) hists["_OS"+Shape_SRname]->GetXaxis()->SetBinLabel(i, binnames[i-1]);
        }
        hists[Shape_SRname]->SetCanExtend(false);
        if(makeMajToDirac or isData) hists["_OS"+Shape_SRname]->SetCanExtend(false);
    }
    else if(prefix.Contains("_2l")){
        hists["_OS"+prefix+"_Shape_SR"]       = new TH1F("_OS"+prefix+"_Shape_SR", ";#Delta (PV-SV)_{2D} [cm];Events", 24, 0, 24);
        int nbins = 24;
        if(prefix.Contains("_M-10_")) nbins = 22;
        hists["_SS"+prefix+"_Shape_SR"]       = new TH1F("_SS"+prefix+"_Shape_SR", ";#Delta (PV-SV)_{2D} [cm];Events", nbins, 0, nbins);
        hists[prefix+"_Shape_SR"]       = new TH1F(prefix+"_Shape_SR", ";#Delta (PV-SV)_{2D} [cm];Events", nbins+24, 0, nbins+24);
        std::vector<TString> binnames_OS, binnames_SS;
        if(prefix.Contains("_M-5_")){
            binnames_OS = {"0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10"};
            binnames_SS = {"0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10"};
        }else if(prefix.Contains("_M-10_")){
            binnames_OS = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
            binnames_SS = {"0-1", "1-5", ">5", "0-1", ">1", "0-1", "1-5", ">5", "0-1", ">1", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
        }
        for(unsigned i = 1; i <= binnames_OS.size(); ++i){
            hists["_OS"+prefix+"_Shape_SR"]->GetXaxis()->SetBinLabel(i, binnames_OS[i-1]);
        }
        for(unsigned i = 1; i <= binnames_SS.size(); ++i){
            hists["_SS"+prefix+"_Shape_SR"]->GetXaxis()->SetBinLabel(i, binnames_SS[i-1]);
        }
        hists["_OS"+prefix+"_Shape_SR"]->SetCanExtend(false);
        hists["_SS"+prefix+"_Shape_SR"]->SetCanExtend(false);
    }
}

void mini_analyzer::add_Shape_SR_extra_histograms(TString prefix)
{
    if(prefix.Contains("_mm") or prefix.Contains("_ee") or prefix.Contains("_em") or prefix.Contains("_me")){
        //TString Shape_SRname    = prefix+"_Shape_SR_unw";
        TString Shape_alphaname = prefix+"_Shape_alpha";
        //TString Shape_alphaname_unw = prefix+"_Shape_alpha_unw";
        //int nbins = 12;
        //if(prefix.Contains("_SS") and prefix.Contains("_M-10_")) nbins = 11;
        //hists[Shape_SRname]     = new TH1F(Shape_SRname, ";#Delta (PV-SV)_{2D} [cm];Events", nbins, 0, nbins);
        hists[Shape_alphaname]  = new TH1F(Shape_alphaname, ";#Delta (PV-SV)_{2D} [cm];Events", 6, 0, 6);
        //hists[Shape_alphaname_unw]  = new TH1F(Shape_alphaname_unw, ";#Delta (PV-SV)_{2D} [cm];Events", 6, 0, 6);

        std::vector<TString> binnames;
        if(prefix.Contains("_M-5_")){
            binnames = {"0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10"};
        }else if(prefix.Contains("_SS") and prefix.Contains("_M-10_")){
            binnames = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", ">1"};
        }else if(prefix.Contains("_M-10_")){
            binnames = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
        }
        for(unsigned i = 1; i <= binnames.size(); ++i){
            //hists[Shape_SRname]->GetXaxis()->SetBinLabel(i, binnames[i-1]);
            if(i < 7) hists[Shape_alphaname]->GetXaxis()->SetBinLabel(i, binnames[i-1]);
            //if(i < 7) hists[Shape_alphaname_unw]->GetXaxis()->SetBinLabel(i, binnames[i-1]);
        }
        //hists[Shape_SRname]->SetCanExtend(false);
        hists[Shape_alphaname]->SetCanExtend(false);
        //hists[Shape_alphaname_unw]->SetCanExtend(false);
    }
    else if(prefix.Contains("_2l")){
        hists[prefix+"_Shape_alpha"]       = new TH1F(prefix+"_Shape_alpha", ";#Delta (PV-SV)_{2D} [cm];Events", 24, 0, 24);
        //hists[prefix+"_Shape_alpha_unw"]       = new TH1F(prefix+"_Shape_alpha_unw", ";#Delta (PV-SV)_{2D} [cm];Events", 24, 0, 24);
        hists2D["_OS"+prefix+"_Shape_PFN"]    = new TH2F("_OS"+prefix+"_Shape_PFN", ";#Delta (PV-SV)_{2D} [cm];PFN output", 24, 0, 24, 10000, 0, 1);
        hists2D["_SS"+prefix+"_Shape_PFN"]    = new TH2F("_SS"+prefix+"_Shape_PFN", ";#Delta (PV-SV)_{2D} [cm];PFN output", 24, 0, 24, 10000, 0, 1);
        //hists["_OS"+prefix+"_Shape_SR_unw"]       = new TH1F("_OS"+prefix+"_Shape_SR_unw", ";#Delta (PV-SV)_{2D} [cm];Events", 24, 0, 24);
        //hists["_SS"+prefix+"_Shape_SR_unw"]       = new TH1F("_SS"+prefix+"_Shape_SR_unw", ";#Delta (PV-SV)_{2D} [cm];Events", 24, 0, 24);
        std::vector<TString> binnames_OS, binnames_SS;
        if(prefix.Contains("_M-5_")){
            binnames_OS = {"0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10"};
            binnames_SS = {"0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10", "0-4", "4-10", ">10"};
        }else if(prefix.Contains("_M-10_")){
            binnames_OS = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
            binnames_SS = {"0-1", "1-5", ">5", "0-1", ">1", "0-1", "1-5", ">5", "0-1", ">1", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
        }
        for(unsigned i = 1; i <= binnames_OS.size(); ++i){
            hists[prefix+"_Shape_alpha"]->GetXaxis()->SetBinLabel(i, binnames_OS[i-1]);
            //hists[prefix+"_Shape_alpha_unw"]->GetXaxis()->SetBinLabel(i, binnames_OS[i-1]);
            //hists["_OS"+prefix+"_Shape_SR_unw"]->GetXaxis()->SetBinLabel(i, binnames_OS[i-1]);
        }
        for(unsigned i = 1; i <= binnames_SS.size(); ++i){
            //hists["_SS"+prefix+"_Shape_SR_unw"]->GetXaxis()->SetBinLabel(i, binnames_SS[i-1]);
        }
        hists[prefix+"_Shape_alpha"]->SetCanExtend(false);
        //hists[prefix+"_Shape_alpha_unw"]->SetCanExtend(false);
        //hists["_OS"+prefix+"_Shape_SR_unw"]->SetCanExtend(false);
        //hists["_SS"+prefix+"_Shape_SR_unw"]->SetCanExtend(false);
    }
}


void mini_analyzer::fill_histograms()
{
    for(const auto& ABCDtag : ABCDtags){
        if((isData and isBlind) and ABCDtag.Contains("_quadA") and not ABCDtag.Contains("CR")) continue;// don't fill region A histograms for data

        TString mv2tag = "";
        if(Dogridscan) mv2tag = ABCDtag(0,ABCDtag.Index("_CP"));//gridscan
        else mv2tag = ABCDtag(0,ABCDtag.Index("_cut"));
        unsigned i_JetTagVal = MV2tags[mv2tag];

        double ev_weight = event._weight * event._reweighting_weight[i_JetTagVal];
        //if((mv2tag.Contains("5e-05") or mv2tag.Contains("9e-07")) and ABCDtag.Contains("_cutTightmlSV_quadA")){
        //    std::cout << mv2tag << ": " << ev_weight << " " << event._reweighting_weight[i_JetTagVal] << " " << i_JetTagVal << std::endl;
        //}

        if(!Dogridscan){
            //if(mv2tag.Contains("2e-06") or mv2tag.Contains("4e-06")){
            if(!(mv2tag.Contains("2e-06") or ABCDtag.Contains("_cutTightmlSV_q") or ABCDtag.Contains("_cutNTightmlSV_q") or ABCDtag.Contains("cutbaselinemlSV") or ABCDtag.Contains("cutinsidemlSV") or ABCDtag.Contains("cutoutsidemlSV"))) continue;
            if(mv2tag.Contains("2e-06")){
                fill_standard_histograms(sr_flavor + ABCDtag, ev_weight);
                if(ABCDtag.Contains("cutbaselinemlSV") or ABCDtag.Contains("cutinsidemlSV") or ABCDtag.Contains("cutoutsidemlSV") or ABCDtag.Contains("cutTightmlSV")){
                    fill_pfn_histograms(     sr_flavor + ABCDtag, ev_weight, i_JetTagVal);
                }
                fill_Shape_SR_extra_histograms(sr_flavor,  ABCDtag, ev_weight, i_JetTagVal);
            }
            if(mv2tag.Contains("2e-06") and (ABCDtag.Contains("cutTightmlSV") or ABCDtag.Contains("cutbaselinemlSV") or ABCDtag.Contains("cutinsidemlSV") or ABCDtag.Contains("cutoutsidemlSV"))){
                //if(event._mll > 85 and event._mll < 95) std::cout << "sr_flavor and mll " << sr_flavor + ABCDtag << " " << event._mll << std::endl;
                fill_extra_histograms(sr_flavor + ABCDtag, ev_weight);
                TString SRbin;
                if(ABCDtag.Contains("M-5")) SRbin = LowMassBin;
                else SRbin = HighMassBin;
                fill_standard_histograms(sr_flavor + ABCDtag + SRbin, ev_weight);
                fill_extra_histograms(sr_flavor + ABCDtag + SRbin, ev_weight);
            }
            //fill_fraction_histograms(sr_flavor + ABCDtag, ev_weight);
            fill_Shape_SR_histograms(sr_flavor,  ABCDtag, ev_weight);
            //if(ABCDtag.Contains("_quadB_")){
            //    fill_Shape_SR_histograms(sr_flavor, ABCDtag + "_unw", 1.);
            //}

            // Add variations for systematic uncertainty plots
            double nominal_weight = ev_weight;
            set_variations(nominal_weight);
            if(ABCDtag.Contains("cutTightmlSV_quadA") or ABCDtag.Contains("cutNTightmlSV_quadA")){
                for(const auto& it : variations){
                    fill_Shape_SR_histograms(sr_flavor, ABCDtag + it.first, it.second);
                }
            }
        }else{
            fill_Shape_SR_histograms(sr_flavor,  ABCDtag, ev_weight);
        }
    }
}

void mini_analyzer::fill_SRevents()
{
    for(const auto& ABCDtag : ABCDtags){
        if((isData and isBlind) and ABCDtag.Contains("_quadA") and not ABCDtag.Contains("CR")) continue;

        if(ABCDtag.Contains("M-5_V2-2e-06_cutTightmlSV_quadA")){
            SRevents_LowMass->copy_event(&event);
            SRevents_LowMass->fill_tree();
        }
        if(ABCDtag.Contains("M-10_V2-2e-06_cutTightmlSV_quadA")){
            SRevents_HighMass->copy_event(&event);
            SRevents_HighMass->fill_tree();
        }
    }
}

void mini_analyzer::init_variations()
{
    variations["_Trigger_sysUp"]    = 1.;
    variations["_Trigger_sysDown"]  = 1.;
    variations["_PileUp_sysUp"]     = 1.;
    variations["_PileUp_sysDown"]   = 1.;
    variations["_l1ID_sysUp"]       = 1.;
    variations["_l1ID_sysDown"]     = 1.;
    variations["_l2ID_sysUp"]       = 1.;
    variations["_l2ID_sysDown"]     = 1.;
    variations["_Track_sysUp"]    = 1.;
    variations["_Track_sysDown"]  = 1.;
}

void mini_analyzer::set_variations(double nominal_weight)
{
    variations["_l1ID_sysUp"]       = nominal_weight * ( 1 + sqrt(event._l1_IDSF_unc_sym / event._l1_IDSF * event._l1_IDSF_unc_sym / event._l1_IDSF + event._l1_ISOSF_unc_sym / event._l1_ISOSF * event._l1_ISOSF_unc_sym / event._l1_ISOSF));
    variations["_l1ID_sysDown"]     = nominal_weight * ( 1 - sqrt(event._l1_IDSF_unc_sym / event._l1_IDSF * event._l1_IDSF_unc_sym / event._l1_IDSF + event._l1_ISOSF_unc_sym / event._l1_ISOSF * event._l1_ISOSF_unc_sym / event._l1_ISOSF));
    variations["_l2ID_sysUp"]       = nominal_weight * ( 1 + event._l1_IDSF_unc_sym / event._l1_IDSF);
    variations["_l2ID_sysDown"]     = nominal_weight * ( 1 - event._l1_IDSF_unc_sym / event._l1_IDSF);
    variations["_Track_sysUp"]      = nominal_weight * ( 1 + event._TrackSF_unc_sym / event._TrackSF);
    variations["_Track_sysDown"]    = nominal_weight * ( 1 - event._TrackSF_unc_sym / event._TrackSF);
    variations["_Trigger_sysUp"]    = nominal_weight * ( 1 + event._TriggerSF_unc_sym / event._TriggerSF);
    variations["_Trigger_sysDown"]  = nominal_weight * ( 1 - event._TriggerSF_unc_sym / event._TriggerSF);
    variations["_PileUp_sysUp"]     = nominal_weight * ( 1 + event._PileUpSF_unc_up / event._PileUpSF);
    variations["_PileUp_sysDown"]   = nominal_weight * ( 1 - event._PileUpSF_unc_down / event._PileUpSF);
}

void mini_analyzer::fill_fraction_histograms(TString prefix, double event_weight)
{
    double binnr;
    if(prefix.Contains("_quadA")) binnr = 0.;
    else if(prefix.Contains("_quadB")) binnr = 1.;
    else if(prefix.Contains("_quadC")) binnr = 2.;
    else binnr =3.;
    prefix = prefix(0, prefix.Index("_quad"));

    double SRShapebin = get_SRShapebin(event._SV_PVSVdist_2D, event._SV_mass);
    double SRShape2bin = get_SRShape2bin(event._SV_PVSVdist_2D, prefix);

    hists[prefix+"_QuadFractions"]->Fill(binnr, event_weight);
    //hists[prefix+"_QuadFractions_unw"]->Fill(binnr);
    hists2D[prefix+"_QuadFractions_2D"]->Fill(SRShapebin, binnr, event_weight);
    hists2D[prefix+"_QuadFractions2_2D"]->Fill(SRShape2bin, binnr, event_weight);
}

void mini_analyzer::fill_standard_histograms(TString prefix, double event_weight)
{
    //std::cout << "prefix: " << prefix << std::endl;
    hists[prefix+"_Yield"]->Fill(0., event_weight);
    hists[prefix+"_mll"]->Fill(event._mll,event_weight);
    hists[prefix+"_PV-SVdxy"]->Fill(event._SV_PVSVdist_2D,event_weight);
    hists[prefix+"_SVl1mass"]->Fill(event._SV_l1mass,event_weight);
}

void mini_analyzer::fill_extra_histograms(TString prefix, double event_weight)
{
    //hists[prefix+"_SRShape"]->Fill(get_SRShapebin(event._SV_PVSVdist_2D, event._SV_mass), event_weight);
    //hists[prefix+"_SRShape2"]->Fill(get_SRShape2bin(event._SV_PVSVdist_2D, prefix), event_weight);
    //hists[prefix+"_nTightJet"]->Fill(event._nTightJet,event_weight);
    hists[prefix+"_nMediumBJet"]->Fill(event._nMediumBJet,event_weight);
    //hists[prefix+"_nLooseBJet"]->Fill(event._nLooseBJet,event_weight);
    hists[prefix+"_JetPt"]->Fill(event._JetPt,event_weight);
    hists[prefix+"_JetEta"]->Fill(event._JetEta,event_weight);
    hists[prefix+"_JetPhi"]->Fill(event._JetPhi,event_weight);
    //hists[prefix+"_nTightLep"]->Fill(event._nTightLep,event_weight);
    hists[prefix+"_l2pt"]->Fill(event._lPt,event_weight);
    hists[prefix+"_l2eta"]->Fill(event._lEta,event_weight);
    //hists[prefix+"_l2phi"]->Fill(event._lPhi,event_weight);
    hists[prefix+"_l2dxy"]->Fill(fabs(event._ldxy),event_weight);
    hists[prefix+"_l2dxy2"]->Fill(fabs(event._ldxy),event_weight);
    hists[prefix+"_l2dz"]->Fill(fabs(event._ldz),event_weight);
    hists[prefix+"_l23dIPSig"]->Fill(event._l3dIPSig,event_weight);
    hists[prefix+"_l2reliso"]->Fill(event._lrelIso,event_weight);
    hists[prefix+"_l2reliso2"]->Fill(event._lrelIso,event_weight);
    hists[prefix+"_l2ptratio"]->Fill(event._lptRatio,event_weight);
    hists[prefix+"_l2ptrel"]->Fill(event._lptRel,event_weight);
    hists[prefix+"_l2NumberOfHits"]->Fill(event._lNumberOfHits,event_weight);
    hists[prefix+"_l2NumberOfPixHits"]->Fill(event._lNumberOfPixelHits,event_weight);
    //hists[prefix+"_l2MuonSegComp"]->Fill(event._lMuonSegComp,event_weight);
    //hists[prefix+"_l2MuonTime"]->Fill(event._lMuonTime,event_weight);
    //hists[prefix+"_l2MuonRPCTime"]->Fill(event._lMuonRPCTime,event_weight);
    hists[prefix+"_l2InnerTrackValidFraction"]->Fill(event._lInnerTrackValidFraction,event_weight);
    
    hists[prefix+"_l1pt"]->Fill(event._l1Pt,event_weight);
    hists[prefix+"_l1eta"]->Fill(event._l1Eta,event_weight);
    //hists[prefix+"_l1phi"]->Fill(event._l1Phi,event_weight);
                                       
    hists[prefix+"_dRll"]->Fill(event._dRll,event_weight);
    hists[prefix+"_dphill"]->Fill(event._dphill,event_weight);
    hists[prefix+"_detall"]->Fill(fabs(event._l1Eta - event._lEta),event_weight);
    //hists[prefix+"_dTimell"]->Fill(fabs(event._l1MuonTime - event._lMuonTime),event_weight);
    hists[prefix+"_dabsetall"]->Fill(fabs(fabs(event._l1Eta) - fabs(event._lEta)),event_weight);
    LorentzVector l1_vec(event._l1Pt, event._l1Eta, event._l1Phi, event._l1Pt);
    LorentzVector l2_vec(event._lPt, event._lEta, event._lPhi, event._lPt);
    //hists[prefix+"_cosine3Dll"]->Fill(cosine3D(l1_vec, l2_vec));
    hists[prefix+"_dRljet"]->Fill(event._dRljet,event_weight);
    hists[prefix+"_jetPtOverlPt"]->Fill(event._JetPt / event._lPt,event_weight);

    hists[prefix+"_PV-SVdxy2"]->Fill(event._SV_PVSVdist_2D,event_weight);
    hists[prefix+"_PV-SVdxy3"]->Fill(event._SV_PVSVdist_2D,event_weight);
    hists[prefix+"_PV-SVdxyz"]->Fill(event._SV_PVSVdist,event_weight);
    hists[prefix+"_PV-SVdxyz2"]->Fill(event._SV_PVSVdist,event_weight);
    hists[prefix+"_ntracks"]->Fill(event._SV_ntracks,event_weight);
    hists[prefix+"_SVmass"]->Fill(event._SV_mass,event_weight);
    hists[prefix+"_SVmass2"]->Fill(event._SV_mass,event_weight);
    hists[prefix+"_SVmass3"]->Fill(event._SV_mass,event_weight);
    hists[prefix+"_SVpt"]->Fill(event._SV_pt,event_weight);
    hists[prefix+"_SVeta"]->Fill(event._SV_eta,event_weight);
    //hists[prefix+"_SVphi"]->Fill(event._SV_phi,event_weight);
    hists[prefix+"_SVnormchi2"]->Fill(event._SV_normchi2,event_weight);
    int chsum = 0;
    for(unsigned i_tr = 0; i_tr < event._SV_ntracks; i_tr++){
        chsum += event._SV_trackcharge[i_tr];
    }
    hists[prefix+"_SVchsum"]->Fill(chsum,event_weight);
    if(event._SV_ntracks == 2) hists[prefix+"_SVchsum2tr"]->Fill(chsum,event_weight);

    hists2D[prefix+"_mllvsSVmass"]->Fill(event._mll, event._SV_mass, event_weight);
    hists2D[prefix+"_mllvsSVl1mass"]->Fill(event._mll, event._SV_l1mass, event_weight);
    hists2D[prefix+"_mllvsPVSVdxy"]->Fill(event._mll, event._SV_PVSVdist_2D, event_weight);
    hists2D[prefix+"_l2dxyvsPVSVdxy"]->Fill(fabs(event._ldxy), event._SV_PVSVdist_2D, event_weight);
    //hists2D[prefix+"_dphillvsSVmass"]->Fill(event._dphill, event._SV_mass, event_weight);
    //hists2D[prefix+"_dphillvsPVSVdxy"]->Fill(event._dphill, event._SV_PVSVdist_2D, event_weight);
    hists2D[prefix+"_lprovenance"]->Fill(event._l1Provenance, event._lProvenance, event_weight);
    hists2D[prefix+"_lprovenanceCompressed"]->Fill(event._l1ProvenanceCompressed, event._lProvenanceCompressed, event_weight);
}


void mini_analyzer::fill_pfn_histograms(TString prefix, double event_weight, unsigned i)
{
    //hists2D[prefix+"_PFNvsdphill"]->Fill(event._JetTagVal[i], event._dphill, event_weight);
    //hists2D[prefix+"_PFNvsmll"]->Fill(event._JetTagVal[i], event._mll, event_weight);
    hists2D[prefix+"_PFNvsmlSV"]->Fill(event._JetTagVal[i], event._SV_l1mass, event_weight);
    hists[prefix+"_JetTagVal"]->Fill(event._JetTagVal[i], event_weight);
    hists[prefix+"_JetTagValzoom"]->Fill(event._JetTagVal[i], event_weight);
}

void mini_analyzer::fill_Shape_SR_histograms(TString sr_flavor, TString ABCDtag, double event_weight)
{
    //std::cout << "flavor and tag: " << sr_flavor << " " << ABCDtag << std::endl;
    double SRShapebin = get_SRShape3bin(event._SV_PVSVdist_2D, event._SV_mass, ABCDtag, sr_flavor);//gives 0,1,2,3,4,5 based on L_xy and SVmass
    double SRShapebin_OSSS = SRShapebin;
    if(sr_flavor.Contains("_SS")) SRShapebin += 6.;

    TString fl;
    if(sr_flavor.Contains("_mm")) fl = "_mm";
    if(sr_flavor.Contains("_ee")) fl = "_ee";
    if(sr_flavor.Contains("_me")) fl = "_me";
    if(sr_flavor.Contains("_em")) fl = "_em";


    hists[fl + ABCDtag + "_Shape_SR"]->Fill(SRShapebin, event_weight);
    //std::cout << sr_flavor + ABCDtag + "_Shape_SR" << std::endl;
    if((makeMajToDirac or isData) and sr_flavor.Contains("_OS")) hists[sr_flavor + ABCDtag + "_Shape_SR"]->Fill(SRShapebin_OSSS, event_weight); //for MajToDirac interpretation, assume all OS and SS decays are all OS

    double _2lbin = 0., _2lbin_OSSS = 0.;
    if(sr_flavor.Contains("_SS") and ABCDtag.Contains("M-10")){
        if(sr_flavor.Contains("_em")){      _2lbin += 11.; _2lbin_OSSS += 5.;}
        else if(sr_flavor.Contains("_ee")){ _2lbin += 22.; _2lbin_OSSS += 10.;}
        else if(sr_flavor.Contains("_me")){ _2lbin += 34.; _2lbin_OSSS += 16.;}
    }else{
        if(sr_flavor.Contains("_em")){      _2lbin += 12.; _2lbin_OSSS += 6.;}
        else if(sr_flavor.Contains("_ee")){ _2lbin += 24.; _2lbin_OSSS += 12.;}
        else if(sr_flavor.Contains("_me")){ _2lbin += 36.; _2lbin_OSSS += 18.;}
    }
    hists["_2l" + ABCDtag + "_Shape_SR"]->Fill(SRShapebin + _2lbin, event_weight);
    hists[sr_flavor(0,3) + "_2l" + ABCDtag + "_Shape_SR"]->Fill(SRShapebin_OSSS + _2lbin_OSSS, event_weight);

}

void mini_analyzer::fill_Shape_SR_extra_histograms(TString sr_flavor, TString ABCDtag, double event_weight, unsigned i)
{
    double SRShapebin = get_SRShape3bin(event._SV_PVSVdist_2D, event._SV_mass, ABCDtag, sr_flavor);//gives 0,1,2,3,4,5 based on L_xy and SVmass
    double SRShapebin_OSSS = SRShapebin;
    if(sr_flavor.Contains("_SS")) SRShapebin += 6.;

    TString fl;
    if(sr_flavor.Contains("_mm")) fl = "_mm";
    if(sr_flavor.Contains("_ee")) fl = "_ee";
    if(sr_flavor.Contains("_me")) fl = "_me";
    if(sr_flavor.Contains("_em")) fl = "_em";


    hists[fl + ABCDtag + "_Shape_alpha"]->Fill(SRShapebin_OSSS, event_weight);
    //hists[fl + ABCDtag + "_Shape_SR_unw"]->Fill(SRShapebin);
    //hists[fl + ABCDtag + "_Shape_alpha_unw"]->Fill(SRShapebin_OSSS);


    double _2lbin = 0., _2lbin_OSSS = 0.;
    if(sr_flavor.Contains("_SS") and ABCDtag.Contains("M-10")){
        if(sr_flavor.Contains("_em")){      _2lbin += 11.; _2lbin_OSSS += 5.;}
        else if(sr_flavor.Contains("_ee")){ _2lbin += 22.; _2lbin_OSSS += 10.;}
        else if(sr_flavor.Contains("_me")){ _2lbin += 34.; _2lbin_OSSS += 16.;}
    }else{
        if(sr_flavor.Contains("_em")){      _2lbin += 12.; _2lbin_OSSS += 6.;}
        else if(sr_flavor.Contains("_ee")){ _2lbin += 24.; _2lbin_OSSS += 12.;}
        else if(sr_flavor.Contains("_me")){ _2lbin += 36.; _2lbin_OSSS += 18.;}
    }
    hists["_2l" + ABCDtag + "_Shape_alpha"]->Fill(SRShapebin_OSSS + _2lbin_OSSS, event_weight);
    //hists["_2l" + ABCDtag + "_Shape_alpha_unw"]->Fill(SRShapebin_OSSS + _2lbin_OSSS);
    hists2D[sr_flavor(0,3) + "_2l" + ABCDtag + "_Shape_PFN"]->Fill(SRShapebin_OSSS + _2lbin_OSSS, event._JetTagVal[i], event_weight);
    //hists[sr_flavor(0,3) + "_2l" + ABCDtag + "_Shape_SR_unw"]->Fill(SRShapebin_OSSS + _2lbin_OSSS);

}


void mini_analyzer::sum_quad_histograms()
{
    if(!(isData and isBlind)){
        sum_histograms_based_on_tags("_quadA_", "_quadB_", "_quadAB_");
        sum_histograms_based_on_tags("_quadA_", "_quadC_", "_quadAC_");
    }
    sum_histograms_based_on_tags("_quadB_", "_quadD_", "_quadBD_");
    sum_histograms_based_on_tags("_quadC_", "_quadD_", "_quadCD_");
    sum_histograms_based_on_tags("_quadB_", "_quadCD_", "_quadBCD_");

    if(!(isData and isBlind)) sum_histograms_based_on_tags("_quadAB_", "_quadCD_", "_quadABCD_");
}


void mini_analyzer::sum_histograms_based_on_tags(TString base_tag, TString second_tag, TString target_tag)
{
    for(const auto& hist : hists){
        TString histname = hist.first;
        if(histname.Contains("sys")) continue;
        TH1* h           = hist.second;
        if(histname.Contains(base_tag)){
            TString histname_second = histname;
            TString histname_combined  = histname;
            histname_second.ReplaceAll(base_tag, second_tag);
            histname_combined.ReplaceAll(base_tag, target_tag);

            if(hists[histname_combined] and hists[histname_second]){
                hists[histname_combined]->Add(h, hists[histname_second]);
            }
        }
    }

    for(const auto& hist : hists2D){
        TString histname = hist.first;
        if(histname.Contains("sys")) continue;
        TH2* h           = hist.second;
        if(histname.Contains(base_tag)){
            TString histname_second = histname;
            TString histname_combined  = histname;
            histname_second.ReplaceAll(base_tag, second_tag);
            histname_combined.ReplaceAll(base_tag, target_tag);

            if(hists2D[histname_combined] and hists2D[histname_second]){
                hists2D[histname_combined]->Add(h, hists2D[histname_second]);
            }
        }
    }
}

double mini_analyzer::get_SRShapebin(double PVSVdist_2D, double SV_mass)
{
    if(PVSVdist_2D < 10 and SV_mass <= 4) return 0.;
    else if(PVSVdist_2D > 10 and SV_mass <= 4) return 1.;
    else if(PVSVdist_2D < 10 and SV_mass > 4) return 2.;
    return 3.;
}

double mini_analyzer::get_SRShape2bin(double PVSVdist_2D, TString tagForMass)
{
    //Low Mass
    if(tagForMass.Contains("M-2") or tagForMass.Contains("M-3") or tagForMass.Contains("M-4") or tagForMass.Contains("M-5")){
        if(PVSVdist_2D < 5)  return 0.;
        if(PVSVdist_2D < 10) return 1.;
        else return 2.;
    //High Mass
    }else if(tagForMass.Contains("M-6") or tagForMass.Contains("M-8") or tagForMass.Contains("M-10") or tagForMass.Contains("M-12") or tagForMass.Contains("M-14")){
        if(PVSVdist_2D < 3) return 0.;
        if(PVSVdist_2D < 6) return 1.;
        else return 2.;
    }else {
        std::cout << "Error in get_SRShape2bin: There is no mass tag in the ABCDtag present, using Low Mass definitions of signal region bins" << std::endl;
        if(PVSVdist_2D < 5)  return 0.;
        if(PVSVdist_2D < 10) return 1.;
        else return 2.;
    }
}

double mini_analyzer::get_SRShape3bin(double PVSVdist_2D, double SV_mass, TString tagForMass, TString sr_flavor)
{
    //Low Mass
    if(tagForMass.Contains("M-1_") or tagForMass.Contains("M-2_") or tagForMass.Contains("M-3") or tagForMass.Contains("M-4") or tagForMass.Contains("M-5")){
        if(SV_mass < 2.){
            if(PVSVdist_2D < 4)  return 0.;
            if(PVSVdist_2D < 10) return 1.;
            else return 2.;
        }else {
            if(PVSVdist_2D < 4) return 3.;
            if(PVSVdist_2D < 10) return 4.;
            else return 5.;
        }
    //High Mass
    }else if(tagForMass.Contains("M-6") or tagForMass.Contains("M-7") or tagForMass.Contains("M-8") or tagForMass.Contains("M-9") or tagForMass.Contains("M-10") or tagForMass.Contains("M-11") or tagForMass.Contains("M-12") or tagForMass.Contains("M-13") or tagForMass.Contains("M-14") or tagForMass.Contains("M-15")){
        if(SV_mass < 6.){
            if(PVSVdist_2D < 1) return 0.;
            if(PVSVdist_2D < 5) return 1.;
            else return 2.;
        }else {
            if(PVSVdist_2D < 1) return 3.;
            if(sr_flavor == "_SS_em" or sr_flavor == "_SS_mm") return 4.; //For HighMass SS em and SS mm both in 2016 as in 1718 for bins with SVmass > 6GeV, we have no prediction in bin > 5cm, therefore we merge it with bin 1-5cm
            else if(PVSVdist_2D < 5) return 4.;
            else return 5.;
        }
    }else {
        std::cout << "Error in get_SRShape2bin: There is no mass tag in the ABCDtag present, using Low Mass definitions of signal region bins" << std::endl;
        if(SV_mass < 2.){
            if(PVSVdist_2D < 4)  return 0.;
            if(PVSVdist_2D < 10) return 1.;
            else return 2.;
        }else {
            if(PVSVdist_2D < 4) return 3.;
            if(PVSVdist_2D < 10) return 4.;
            else return 5.;
        }
    }
}

double mini_analyzer::get_SRShape4bin(double PVSVdist_2D, double SV_mass)
{
    if(SV_mass < 5.){
        if(PVSVdist_2D < 4.) return 0.;
        else if(PVSVdist_2D < 10.) return 1.;
        else return 2.;
    }else {
        if(PVSVdist_2D < 1.) return 3.;
        else if(PVSVdist_2D < 5.) return 4.;
        else return 5.;
    }
}

void mini_analyzer::set_error_for_zero_event_bins(TString hname_target, TString hname_ratio)
{
    for(int i = 1; i <= hists[hname_target]->GetNbinsX(); i++){
        if(hists[hname_target]->GetBinContent(i) < 1e-4){
            if(hname_ratio != "") hists[hname_target]->SetBinError(i, hists[hname_ratio]->GetBinContent(i));
            else hists[hname_target]->SetBinError(i, 1.);
        }
    }
}

void mini_analyzer::set_quadA_zero_event_bins()
{
    for(auto const& it : hists){
        TString hname = it.first;
        TH1* h = it.second;
        if(hname.Contains("_quadA_")){
            for(int i = 1; i <= h->GetNbinsX(); i++){
                if(h->GetBinContent(i) < 1e-4){
                    h->SetBinContent(i, 0);
                    h->SetBinError(i, 0);
                }
            }
            //set_error_for_zero_event_bins(hname, "");
        }
    }
}
