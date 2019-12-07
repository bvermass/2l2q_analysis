////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, all helper functions to creating histograms//
////////////////////////////////////////////////////////////////////////////

#include "../interface/helper_histo_functions.h"

//move histo bin naming etc. to here!

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
        else if(filename.Index("Run20") != -1){
            TString tmpname = filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep") - filename.Index("heavyNeutrino") - 15); 
            tmpname.ReplaceAll("/", "_");
            outputfilename += tmpname + "/";
        }
        else outputfilename += "Background_" + filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep") - filename.Index("heavyNeutrino") - 15) + "/";
    }
    
    gSystem->Exec("mkdir -p " + outputfilename);

    if(filename.Index("HeavyNeutrino_lljj") != -1) outputfilename += base_filename + "_" + filename(filename.Index("HeavyNeutrino_"), filename.Index("dilep") - 1 - filename.Index("HeavyNeutrino_"));
    else if(filename.Index("Run20") != -1){ 
        TString tmpname2 = filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep") - filename.Index("heavyNeutrino") - 15); 
        tmpname2.ReplaceAll("/", "_");
        outputfilename += base_filename + "_" + tmpname2;
    }
    else outputfilename += base_filename + "_Background_" + filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep") - filename.Index("heavyNeutrino") - 15);
    
    if(partition != 1) outputfilename += "_job_" + std::to_string(static_cast<long long>(partitionjobnumber)) + ".root";
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

double get_signedLog(double var)
{
    return (var >= 0)? log(var + 1) : - log(fabs(var - 1));
}

//Reweighting stuff
double get_mean_ctau(TString sampleflavor, int _gen_Nmass, double _gen_NV)
{
    if(sampleflavor == "mu"){
        if(_gen_Nmass == 5){
            if(_gen_NV == 0.00547722557505){
                return 4.92;
            }else if(_gen_NV == 0.00316227766017){
                return 14.77;
            }else if(_gen_NV == 0.00282842712475){
                return 18.46;
            }
        }
    }
    std::cout << "Did not find a matching HNL sample for " << sampleflavor << " M-" << _gen_Nmass << " V-" << _gen_NV << std::endl;
    return -1;
}

double get_reweighting_weight(double V2_old, double V2_new, double ctau_old, double ct)
{
    return get_xsec_reweighting_weight(V2_old, V2_new)*get_ctprofile_reweighting_weight(V2_old, V2_new, ctau_old, ct);
}

double get_xsec_reweighting_weight(double V2_old, double V2_new)
{
    return V2_new/V2_old;
}

double get_ctprofile_reweighting_weight(double V2_old, double V2_new, double ctau_old, double ct)
{
    double ctau_new = ctau_old * V2_old / V2_new;
    return (ctau_old/ctau_new)*exp((1./ctau_old - 1./ctau_new)*ct);
}
