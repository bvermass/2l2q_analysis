////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, all helper functions to creating histograms//
////////////////////////////////////////////////////////////////////////////

#include "../interface/helper_histo_functions.h"

//move histo bin naming etc. to here!
using namespace std;

void make_logscale(double* xbins, unsigned nbins, double xmin, double xmax)
{
    double logxmin = TMath::Log10(xmin);
    double logxmax = TMath::Log10(xmax);
    double binwidth = (logxmax - logxmin)/nbins;
    for(unsigned i = 0; i <= nbins; ++i){
        *(xbins+i) = TMath::Power(10, logxmin + i*binwidth);
    }
}

TString make_outputfilename(TString filename, TString base_directory, TString base_filename, int partition, int partitionjobnumber)
{
    TString outputfilename = base_directory;
    if(filename.Index("dilep_") != -1) outputfilename += filename(filename.Index("dilep_") + 6, filename.Index(".root") - 6 - filename.Index("dilep_")) + "/full_analyzer/";
    else outputfilename += "full_analyzer/";
    
    if(partition != 1) {
        outputfilename += "subfiles/";
        if(filename.Index("HeavyNeutrino_lljj") != -1) outputfilename += filename(filename.Index("HeavyNeutrino_"), filename.Index("dilep") - filename.Index("HeavyNeutrino_"));
        else if(filename.Index("SingleMuon") != -1) outputfilename += filename(filename.Index("Run20"), 8);
        else outputfilename += "Background_" + filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep") - filename.Index("heavyNeutrino") - 15) + "/";
    }
    
    gSystem->Exec("mkdir -p " + outputfilename);

    if(filename.Index("HeavyNeutrino_lljj") != -1) outputfilename += base_filename + "_" + filename(filename.Index("HeavyNeutrino_"), filename.Index("dilep") - 1 - filename.Index("HeavyNeutrino_"));
    else if(filename.Index("SingleMuon") != -1) outputfilename += base_filename + "_" + filename(filename.Index("Run20"), 8);
    else outputfilename += base_filename + "_Background_" + filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep") - filename.Index("heavyNeutrino") - 15);
    
    if(partition != 1) outputfilename += "_job_" + to_string(static_cast<long long>(partitionjobnumber)) + ".root";
    else outputfilename += ".root";

    return outputfilename;
}

double calc_betagamma(int particle_mass, double particle_energy)
{
    double particle_betagamma = sqrt(particle_energy*particle_energy - particle_mass*particle_mass)/particle_mass;
    return particle_betagamma;
}

double get_dR(double eta1, double phi1, double eta2, double phi2){
    double deta = fabs(eta1 - eta2);
    double dphi = (fabs(phi1 - phi2) < 3.14)? fabs(phi1 - phi2) : 6.28 - fabs(phi1 - phi2);
    return sqrt(deta*deta + dphi*dphi);
}

double get_reducedPdgId(int pdgId)
{
    static const std::map< unsigned, double > pdgIdMap = {
        { 0, 0.},
        { 1, 0.125},
        { 2, 0.25},
        { 11, 0.375},
        { 13, 0.5},
        { 22, 0.625},
        { 130, 0.75},
        { 211, 0.875}
    };
    auto entry = pdgIdMap.find( fabs( pdgId ) );
    if( entry != pdgIdMap.cend() ){
        return entry->second;
    } else {
        return 1;
    }
}
