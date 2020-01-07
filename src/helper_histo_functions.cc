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


std::map<TString, double> add_SR_counters()
{
    std::map<TString, double> sr;
    for(const TString &lep_region : {"", "_OS_ee", "_SS_ee", "_OS_mm", "_SS_mm", "_OS_em", "_SS_em", "_OS_me", "_SS_me"}){
        for(const TString &weight : {"", "_weighted"}){
            sr[lep_region + weight] = 0;
        }
    }
    return sr;
}


void print_SR_counters(std::map<TString, double> sr, double total_weight)
{
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Channel\t\t#events\t\t#events(weighted)" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    for(auto& srel : sr){
        if(srel.first.Index("weighted") == -1 and srel.first != "") std::cout << srel.first << "\t\t" << srel.second << "\t\t" << sr[srel.first+"_weighted"]*total_weight << std::endl;
        else if(srel.first == "") std::cout << "=/=l1l2" << "\t\t" << srel.second << "\t\t" << sr["_weighted"]*total_weight << std::endl;
    }
}


void print_evaluating_points(const std::map<int, std::map<double, double>>& evaluating_ctaus)
{
    std::cout << "Evaluating points for PFN:" << std::endl;
    for(auto& MassMap : evaluating_ctaus){
        std::cout << "M-" << MassMap.first << ": ";
        for(auto& V2Map : MassMap.second){
            std::cout << V2Map.first << " - ";
        }std::cout << std::endl;
    }
    std::cout << "-------------------------------------------" << std::endl;
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
        if(_gen_Nmass == 2){
            if(_gen_NV == 0.0141421356237) return 97;//
            else if(_gen_NV == 0.0173205080757) return 64;
            else if(_gen_NV == 0.0217715410571) return 41;
            else if(_gen_NV == 0.022360679775) return 38;
            else if(_gen_NV == 0.0248394846967) return 31;
        }else if(_gen_Nmass == 3){
            if(_gen_NV == 0.00836660026534) return 32.60;//exact
            else if(_gen_NV == 0.01) return 23;
            else if(_gen_NV == 0.0141421356237) return 11;
            else if(_gen_NV == 0.0173205080757) return 7.6;
        }else if(_gen_Nmass == 4){
            if(_gen_NV == 0.004472135955) return 24;
            else if(_gen_NV == 0.00547722557505) return 16;
            else if(_gen_NV == 0.00707106781187) return 9.7;
            else if(_gen_NV == 0.00836660026534) return 6.9;
        }else if(_gen_Nmass == 5){
            if(_gen_NV == 0.00282842712475) return 18.46;//exact
            else if(_gen_NV == 0.00316227766017) return 14.77;//exact
            else if(_gen_NV == 0.004472135955) return 7.4;
            else if(_gen_NV == 0.00547722557505) return 4.92;//exact
        }else if(_gen_Nmass == 6){
            if(_gen_NV == 0.000716240183179) return 109;
            else if(_gen_NV == 0.000827042925125) return 82;
            else if(_gen_NV == 0.00202484567313) return 14;
            else if(_gen_NV == 0.00211896201004) return 12;
        }else if(_gen_Nmass == 8){
            if(_gen_NV == 0.000339116499156) return 109;
            else if(_gen_NV == 0.00151327459504) return 5.5;
            else if(_gen_NV == 0.00257293606605) return 1.9;
            else if(_gen_NV == 0.00282842712475) return 1.56;//exact
        }else if(_gen_Nmass == 10){
            if(_gen_NV == 0.000169410743461) return 138;
            else if(_gen_NV == 0.000756967634711) return 6.9;
            else if(_gen_NV == 0.000793725393319) return 6.28;//exact
            else if(_gen_NV == 0.00244948974278) return 0.66;
        }else if(_gen_Nmass == 15){
            if(_gen_NV == 4.77493455453e-05) return 217;
            else if(_gen_NV == 0.00244948974278) return 0.08;
            else if(_gen_NV == 0.00282842712475) return 0.06;
        }
    }
    if(sampleflavor == "e"){
        if(_gen_Nmass == 2){
            if(_gen_NV == 0.0141421356237) return 97;//
            else if(_gen_NV == 0.0173205080757) return 64;
            else if(_gen_NV == 0.0217715410571) return 41;
            else if(_gen_NV == 0.022360679775) return 38;
            else if(_gen_NV == 0.0248394846967) return 31;
        }else if(_gen_Nmass == 3){
            if(_gen_NV == 0.00836660026534) return 32.43;//exact
            else if(_gen_NV == 0.01) return 23;
            else if(_gen_NV == 0.0141421356237) return 11;
            else if(_gen_NV == 0.0173205080757) return 7.6;
        }else if(_gen_Nmass == 4){
            if(_gen_NV == 0.004472135955) return 24;
            else if(_gen_NV == 0.00547722557505) return 16;
            else if(_gen_NV == 0.00707106781187) return 9.7;
            else if(_gen_NV == 0.00836660026534) return 6.9;
        }else if(_gen_Nmass == 5){
            if(_gen_NV == 0.00282842712475) return 18.37;//exact
            else if(_gen_NV == 0.00316227766017) return 14.69;//exact
            else if(_gen_NV == 0.004472135955) return 7.4;
            else if(_gen_NV == 0.00547722557505) return 4.90;//exact
        }else if(_gen_Nmass == 6){
            if(_gen_NV == 0.000716240183179) return 109;
            else if(_gen_NV == 0.000827042925125) return 82;
            else if(_gen_NV == 0.00202484567313) return 14;
            else if(_gen_NV == 0.00211896201004) return 12;
        }else if(_gen_Nmass == 8){
            if(_gen_NV == 0.000339116499156) return 109;
            else if(_gen_NV == 0.00151327459504) return 5.5;
            else if(_gen_NV == 0.00257293606605) return 1.9;
            else if(_gen_NV == 0.00282842712475) return 1.56;//exact
        }else if(_gen_Nmass == 10){
            if(_gen_NV == 0.000169410743461) return 138;
            else if(_gen_NV == 0.000756967634711) return 6.9;
            else if(_gen_NV == 0.000793725393319) return 6.27;//exact
            else if(_gen_NV == 0.00244948974278) return 0.66;
        }else if(_gen_Nmass == 15){
            if(_gen_NV == 4.77493455453e-05) return 217;
            else if(_gen_NV == 0.00244948974278) return 0.08;
            else if(_gen_NV == 0.00282842712475) return 0.06;
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

double get_evaluating_ctau(double mass, double V2_new)
{
    //get ctau corresponding to V2_new by using a certain value of V2_old and ctau_old for each mass
    if(mass == 2) return 97. * 2e-4 / V2_new;
    if(mass == 3) return 32.43 * 7e-5 / V2_new;
    if(mass == 4) return 24.23 * 2e-5 / V2_new;
    if(mass == 5) return 18.4 * 8e-6 / V2_new;
    if(mass == 6) return 13.7 * 4.1e-6 / V2_new;
    if(mass == 8) return 5.46 * 2.3e-6 / V2_new;
    if(mass == 10) return 6.27 * 6.3e-7 / V2_new;
    if(mass == 15) return 0.08 * 6e-6 / V2_new;
    std::cout << "Warning: reached end of get_evaluating_ctau without returning a correct ctau value, returning 0" << std::endl;
    return 0;
}

double get_truncated_ctau(double mass, double ctau_true)
{
    // hardcoded minimum and maximum values on which the PFN is trained. Extrapolation of PFN outside of trained V2 region does not work, therefore truncate ctau for evaluation at max or min trained value instead of true value.
    if(mass == 2) return (ctau_true > 97.)? 97. : (ctau_true < 31.)? 31. : ctau_true;
    if(mass == 3) return (ctau_true > 32.43)? 32.43 : (ctau_true < 7.6)? 7.6 : ctau_true;
    if(mass == 4) return (ctau_true > 24.)? 24. : (ctau_true < 6.9)? 6.9 : ctau_true;
    if(mass == 5) return (ctau_true > 18.4)? 18.4 : (ctau_true < 4.9)? 4.9 : ctau_true;
    if(mass == 6) return (ctau_true > 109)? 109 : (ctau_true < 12.)? 12. : ctau_true;
    if(mass == 8) return (ctau_true > 5.5)? 5.5 : (ctau_true < 1.6)? 1.6 : ctau_true;
    if(mass == 10) return (ctau_true > 6.9)? 6.9 : (ctau_true < 0.66)? 0.66 : ctau_true;
    if(mass == 15) return (ctau_true > 0.08)? 0.08 : (ctau_true < 0.06)? 0.06 : ctau_true;
    std::cout << "Warning: reached end of get_truncated_ctau without returning a correct ctau value, returning ctau_true" << std::endl;
    return ctau_true;
}

std::vector<double> get_evaluating_V2s(double mass)
{
    if(mass == 2) return {6e-6, 8e-6, 1e-5, 3e-5, 5e-5, 7e-5, 9e-5};
    if(mass == 3) return {4e-6, 6e-6, 8e-6, 1e-5, 3e-5, 5e-5, 7e-5};
    if(mass == 4) return {9e-7, 2e-6, 4e-6, 6e-6, 8e-6, 1e-5, 3e-5};
    if(mass == 5 or mass == 6 or mass == 8 or mass == 10 or mass == 15) return {5e-7, 7e-7, 9e-7, 2e-6, 4e-6, 6e-6, 8e-6, 1e-5, 3e-5};
    std::cout << "Warning: reached end of get_evaluating_V2s without a correct ctau value, returning {}" << std::endl;
    return {};
}

TString get_MV2name(int mass, double V2)
{
    std::ostringstream V2stream;
    V2stream << V2;
    return "_M-" + std::to_string(mass) + "_V2-" + V2stream.str();
}

// Usage example: filePutContents("./yourfile.txt", "content", true);
void filePutContents(const std::string& name, const std::string& content, bool append)
{
    std::ofstream outfile;
    if (append) outfile.open(name, std::ios_base::app);
    else outfile.open(name);
    outfile << content;
}
