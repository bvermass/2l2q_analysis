////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, all helper functions to creating histograms//
////////////////////////////////////////////////////////////////////////////

#include "../interface/helper_histo_functions.h"

//move histo bin naming etc. to here!

std::vector<double> make_logscale(unsigned nbins, double xmin, double xmax)
{
    if(xmin <= 0 or xmax <= 0) std::cout << "making log axis with 0 or negative value as boundary will not work!" << std::endl;
    double logxmin = TMath::Log10(xmin);
    double logxmax = TMath::Log10(xmax);
    double binwidth = (logxmax - logxmin)/nbins;
    std::vector<double> xbins;
    for(unsigned i = 0; i <= nbins; ++i){
        xbins.push_back(TMath::Power(10, logxmin + i*binwidth));
    }
    return xbins;
}

TString make_outputfilename(TString filename, TString base_directory, TString base_filename, int partition, int partitionjobnumber, bool full_analyzer)
{
    TString outputfilename = base_directory;
    if(full_analyzer){
        if(filename.Contains("dilep_")) outputfilename += filename(filename.Index("dilep_") + 6, filename.Index(".root") - 6 - filename.Index("dilep_")) + "/full_analyzer/";
        else outputfilename += "full_analyzer/";
    }

    if(base_filename.Contains("JECDown")) outputfilename += "JECDown/";
    if(base_filename.Contains("JECUp")) outputfilename += "JECUp/";
    if(base_filename.Contains("JERDown")) outputfilename += "JERDown/";
    if(base_filename.Contains("JERUp")) outputfilename += "JERUp/";
    
    if(partition != 1) {
        TString tmpname = filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep") - filename.Index("heavyNeutrino") - 15); 
        tmpname.ReplaceAll("/", "_");
        outputfilename += "subfiles/" + tmpname + "/";
    }
    
    gSystem->Exec("mkdir -p " + outputfilename);

    TString tmpname2 = filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep") - filename.Index("heavyNeutrino") - 15); 
    tmpname2.ReplaceAll("/", "_");
    outputfilename += base_filename + "_" + tmpname2;

    if(partition != 1) outputfilename += "_job_" + std::to_string(static_cast<long long>(partitionjobnumber));
    
    outputfilename += ".root";

    return outputfilename;
}

TString get_mini_analyzer_outputfilename(TString input)
{
    TString outputfilename = input;
    outputfilename.ReplaceAll("trees", "histograms");
    outputfilename.ReplaceAll("BkgEstimator/final/full_analyzer/BkgEstimator_", "mini_analyzer/hists_mini_analyzer_");
    gSystem->Exec("mkdir -p " + outputfilename(0,outputfilename.Index("hists_mini_analyzer")));
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
    sr["noSel"] = 0;
    sr["Triggermuon"] = 0;
    sr["l1muon"] = 0;
    sr["genOverlap"] = 0;
    sr["isSingleMuon"] = 0;
    sr["l2muon"] = 0;
    sr["SV"] = 0;
    sr["jetl2"] = 0;
    sr["nTightJet"] = 0;
    sr["nTightLep"] = 0;
    sr["mll"] = 0;
    sr["dphill"] = 0;
    sr["PVSVdist"] = 0;
    return sr;
}

void fill_SR_counters_badleptons(std::map<TString, double> SR_counters, TString sr_flavor, int i_leading, int i_subleading, double gen_PVSVdist_2D, double ev_weight)
{
    if(sr_flavor == ""){
        if(i_leading == -1){
            SR_counters["no_l1"]++;
            SR_counters["no_l1_weighted"] += ev_weight;
        }else if(i_subleading == -1){
            if(gen_PVSVdist_2D > 30){
                SR_counters["no_l2_far"]++;
                SR_counters["no_l2_far_weighted"] += ev_weight;
            }else if(gen_PVSVdist_2D < 0.1) {
                SR_counters["no_l2_cl"]++;
                SR_counters["no_l2_cl_weighted"]++;
            }else {
                SR_counters["no_l2_ot"]++;
                SR_counters["no_l2_ot_weighted"]++;
            }
        }else {
            SR_counters["unid."]++;
        }
    }
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

double get_evaluating_ctau(double mass, double V2_new, TString flavor)
{
    //get ctau corresponding to V2_new by using a certain value of V2_old and ctau_old for each mass,
    //hardcoded because I need the correct ctau for several masses, not just the mass from the sample we are running over
    if(flavor.Contains("2l")){
        if(mass == 1) return 16.36 * 2e-2 / V2_new;
        if(mass == 2) return 48.31 * 2e-4 / V2_new;
        if(mass == 3) return 16.26 * 7e-5 / V2_new;
        if(mass == 4) return 12.12 * 2e-5 / V2_new;
        if(mass == 5) return 9.19  * 8e-6 / V2_new;
        if(mass == 6) return 6.85  * 4.1e-6 / V2_new;
        if(mass == 8) return 2.73  * 2.3e-6 / V2_new;
        if(mass == 10) return 3.135 * 6.3e-7 / V2_new;
        if(mass == 12) return 1.938 * 4e-7 / V2_new;
        if(mass == 14) return 0.3502 * 1e-6 / V2_new;
        if(mass == 15) return 0.0410 * 6e-6 / V2_new;
    }else {
        if(mass == 1) return 70.7357 * 9e-3 / V2_new;
        if(mass == 2) return 97. * 2e-4 / V2_new;
        if(mass == 3) return 32.43 * 7e-5 / V2_new;
        if(mass == 4) return 24.23 * 2e-5 / V2_new;
        if(mass == 5) return 18.4 * 8e-6 / V2_new;
        if(mass == 6) return 13.7 * 4.1e-6 / V2_new;
        if(mass == 8) return 5.46 * 2.3e-6 / V2_new;
        if(mass == 10) return 6.27 * 6.3e-7 / V2_new;
        if(mass == 12) return 3.8774 * 4e-7 / V2_new;
        if(mass == 14) return 0.7039 * 1e-6 / V2_new;
        if(mass == 15) return 0.082 * 6e-6 / V2_new;
    }
    std::cout << "Warning: reached end of get_evaluating_ctau without returning a correct ctau value, returning 0" << std::endl;
    return 0;
}

double get_truncated_ctau(bool is2016, double mass, double ctau_true)
{
    // hardcoded minimum and maximum values on which the PFN is trained. Extrapolation of PFN outside of trained V2 region does not work, therefore truncate ctau for evaluation at max or min trained value instead of true value.
    if(is2016){
        if(mass == 1) return (ctau_true > 97.)? 97. : (ctau_true < 31.)? 31. : ctau_true;
        if(mass == 2) return (ctau_true > 97.)? 97. : (ctau_true < 31.)? 31. : ctau_true;
        if(mass == 3) return (ctau_true > 32.43)? 32.43 : (ctau_true < 7.6)? 7.6 : ctau_true;
        if(mass == 4) return (ctau_true > 24.)? 24. : (ctau_true < 6.9)? 6.9 : ctau_true;
        if(mass == 5) return (ctau_true > 18.4)? 18.4 : (ctau_true < 4.9)? 4.9 : ctau_true;
        if(mass == 6) return (ctau_true > 109)? 109 : (ctau_true < 12.)? 12. : ctau_true;
        if(mass == 8) return (ctau_true > 108.8)? 108.8 : (ctau_true < 1.6)? 1.6 : ctau_true;
        if(mass == 10) return (ctau_true > 6.9)? 6.9 : (ctau_true < 0.66)? 0.66 : ctau_true;
        if(mass == 12) return (ctau_true > 0.08)? 0.08 : (ctau_true < 0.06)? 0.06 : ctau_true;
        if(mass == 14) return (ctau_true > 0.08)? 0.08 : (ctau_true < 0.06)? 0.06 : ctau_true;
        if(mass == 15) return (ctau_true > 0.08)? 0.08 : (ctau_true < 0.06)? 0.06 : ctau_true;
    }else {
        if(mass == 1) return (ctau_true > 74.2)? 74.2 : (ctau_true < 14.8)? 14.8 : ctau_true;
        if(mass == 2) return (ctau_true > 205.0)? 205.0 : (ctau_true < 31.5)? 31.5 : ctau_true;
        if(mass == 3) return (ctau_true > 231.7)? 231.7 : (ctau_true < 23.1)? 23.1 : ctau_true;
        if(mass == 4) return (ctau_true > 288.5)? 288.5 : (ctau_true < 9.3)? 9.3 : ctau_true;
        if(mass == 5) return (ctau_true > 348.4)? 348.4 : (ctau_true < 6.9)? 6.9 : ctau_true;
        if(mass == 6) return (ctau_true > 411.5)? 411.5 : (ctau_true < 12.5)? 12.5 : ctau_true;
        if(mass == 8) return (ctau_true > 144.8)? 144.8 : (ctau_true < 1.89)? 1.89 : ctau_true;
        if(mass == 10) return (ctau_true > 182.1)? 182.1 : (ctau_true < 6.2)? 6.2 : ctau_true;
        if(mass == 12) return (ctau_true > 3.88)? 3.88 : (ctau_true < 1.55)? 1.55 : ctau_true;
        if(mass == 14) return (ctau_true > 2.34)? 2.34 : (ctau_true < 0.70)? 0.70 : ctau_true;
        if(mass == 15) return (ctau_true > 216.)? 216. : (ctau_true < 217.)? 217. : ctau_true;
    }
    std::cout << "Warning: reached end of get_truncated_ctau without returning a correct ctau value, returning ctau_true" << std::endl;
    return ctau_true;
}

std::vector<double> get_evaluating_V2s_all()
{
    return {4e-8, 6e-8, 8e-8, 1e-7, 3e-7, 5e-7, 7e-7, 9e-7, 2e-6, 4e-6, 6e-6, 8e-6, 1e-5, 3e-5, 5e-5, 7e-5, 9e-5, 1e-4, 3e-4, 5e-4, 7e-4, 9e-4, 1e-3, 3e-3, 5e-3, 7e-3, 9e-3, 1e-2, 3e-2, 5e-2, 7e-2, 9e-2};
}


std::vector<double> get_evaluating_V2s(double mass)
{
    if(mass == 1) return {9e-5, 1e-4, 3e-4, 5e-4, 7e-4, 9e-4, 1e-3};
    if(mass == 2) return {6e-6, 8e-6, 1e-5, 3e-5, 5e-5, 7e-5, 9e-5, 1e-4, 3e-4, 5e-4};
    if(mass > 2 and mass < 10) return {8e-8, 1e-7, 3e-7, 5e-7, 7e-7, 9e-7, 2e-6, 4e-6, 6e-6, 8e-6, 1e-5, 3e-5};
    if(mass == 10) return {4e-8, 6e-8, 8e-8, 1e-7, 3e-7, 5e-7, 7e-7, 9e-7, 2e-6, 4e-6, 6e-6, 8e-6, 1e-5, 3e-5};
    if(mass == 12) return {5e-7, 7e-7, 9e-7, 2e-6, 4e-6, 6e-6, 8e-6, 1e-5, 3e-5};
    if(mass == 14) return {5e-7, 7e-7, 9e-7, 2e-6, 4e-6, 6e-6, 8e-6, 1e-5, 3e-5};
    if(mass == 15) return {5e-7, 7e-7, 9e-7, 2e-6, 4e-6, 6e-6, 8e-6, 1e-5, 3e-5};
    std::cout << "Warning: reached end of get_evaluating_V2s without a correct ctau value, returning {}" << std::endl;
    return {};
}

std::vector<double> get_evaluating_V2s_short(double mass)
{
    if(mass == 2) return {1e-5, 3e-5, 5e-5, 7e-5};
    if(mass == 3) return {8e-6, 1e-5, 3e-5, 5e-5};
    if(mass == 4) return {4e-6, 6e-6, 8e-6, 3e-5};
    if(mass == 5 or mass == 6 or mass == 8 or mass == 10) return {3e-7, 5e-7, 7e-7, 9e-7, 4e-6, 3e-5};
    if(mass == 12 or mass == 14 or mass == 15) return {5e-7, 7e-7, 9e-7, 2e-6, 4e-6, 3e-5};
    std::cout << "Warning: reached end of get_evaluating_V2s_short without a correct ctau value, returning {}" << std::endl;
    return {};
}

std::vector<double> get_evaluating_V2s_minimal()
{
    return {1e-4, 7e-5, 2e-6, 9e-7};
}


TString get_MV2name(int mass, double V2)
{
    std::ostringstream V2stream;
    V2stream << std::setprecision(0) << std::scientific << V2;
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


void fix_overflow_and_negative_bins(TH1* h)
{
    int nb = h->GetNbinsX();
    double b0  = h->GetBinContent( 0  );
    double e0  = h->GetBinError  ( 0  );
    double b1  = h->GetBinContent( 1  );
    double e1  = h->GetBinError  ( 1  );
    double bn  = h->GetBinContent(nb  );
    double en  = h->GetBinError  (nb  );
    double bn1 = h->GetBinContent(nb+1);
    double en1 = h->GetBinError  (nb+1);

    h->SetBinContent(0   , 0.);
    h->SetBinError  (0   , 0.);
    h->SetBinContent(1   , b0+b1);
    h->SetBinError  (1   , std::sqrt(e0*e0 + e1*e1  ));
    h->SetBinContent(nb  , bn+bn1);
    h->SetBinError  (nb  , std::sqrt(en*en + en1*en1));
    h->SetBinContent(nb+1, 0.);
    h->SetBinError  (nb+1, 0.);

    //if bin content is below zero, set it to 0 (dealing with negative weights)
    for(int i = 0; i < nb+1; i++){
        if(h->GetBinContent(i) < 0.) h->SetBinContent(i, 0.);
    }
}
