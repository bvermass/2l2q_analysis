///////////////////////////////////////////////////////////////////
//Class that reads in HNL_parameters and stores the relevant info//
///////////////////////////////////////////////////////////////////

//Include header for the class
#include "HNL_parameters.h"


// Constructor where HNL_parameters variables are read from an existing file in the format of http://tomc.web.cern.ch/tomc/heavyNeutrino/
HNL_parameters::HNL_parameters(TString parameters_filename, TString sample_filename):
    HNL_parameters_filename(parameters_filename),
    HNL_sample_filename(sample_filename),
    isValid(false)
{
    if(!HNL_sample_filename.Contains("HeavyNeutrino_lljj")) return;

    std::ifstream file(HNL_parameters_filename);
    if(file.is_open()){
        std::cout << "Getting HNL parameters from " << HNL_parameters_filename << std::endl;
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string recommended_str, type_str, mass_str, V2_str, ctau_str, ctauRatioToTheory_str, events_str, cross_section_str, pm_str, cross_section_unc_str, year_str, directory_str;
            iss >> recommended_str >> type_str >> mass_str >> V2_str >> ctau_str >> ctauRatioToTheory_str >> events_str >> cross_section_str >> pm_str >> cross_section_unc_str >> year_str >> directory_str;
                
            // check conditions
            int position = directory_str.find("HeavyNeutrino_lljj_");
            int position_LO = directory_str.find("_LO");
            bool correctyear = ((year_str == "2016v3" and HNL_sample_filename.Contains("MiniAOD2016")) or
                                (year_str == "2017" and HNL_sample_filename.Contains("MiniAOD2017")) or
                                (year_str == "2018" and HNL_sample_filename.Contains("MiniAOD2018")));
            if(recommended_str != "*" or position == -1 or !correctyear) continue;
            
            // find HNL param match
            std::string HeavyNeutrino_lljj_param = directory_str.substr(position, position_LO - position + 3);
            if(HNL_sample_filename.Contains(HeavyNeutrino_lljj_param)){

                // store parameters
                isValid             = true;
                recommended         = recommended_str;
                type                = type_str;
                mass                = std::stod(mass_str);
                V2                  = std::stod(V2_str);
                events              = std::stoi(events_str);
                cross_section       = std::stod(cross_section_str);
                cross_section_unc   = std::stod(cross_section_unc_str);
                year                = year_str;
                directory           = directory_str;
                
                // ctau and ctauRatioToTheory are sometimes - instead of a numerical value. other parameters should always be a numerical value
                if(ctau_str != "-") ctau = std::stod(ctau_str);
                else ctau = 0;
                if(ctauRatioToTheory_str != "-") ctauRatioToTheory   = std::stod(ctauRatioToTheory_str);
                else ctauRatioToTheory = 0;

                if(HNL_sample_filename.Contains("_e_"))         flavor = "e";
                else if(HNL_sample_filename.Contains("_mu_"))   flavor = "mu";
                else if(HNL_sample_filename.Contains("_tau_"))  flavor = "tau";
                else if(HNL_sample_filename.Contains("_2l_"))   flavor = "2l";
                else if(HNL_sample_filename.Contains("_3l_"))   flavor = "3l";
                else flavor = "";

                std::cout << "--HNL parameters-- " << recommended << " " << flavor << " " << type << " M=" << mass << " V2=" << V2 << " ctau=" << ctau << " ctauRatioToTheory=" << ctauRatioToTheory << " events: " << events << " xsec: " << cross_section << " year: " << year <<  std::endl;
                std::cout << "--HNL parameters-- directory: " << directory << std::endl;

                break;
            }
        }
        file.close();
    }else{
        std::cout << HNL_parameters_filename << " is not available!" << std::endl;
    }

    // if no match was found or we are dealing with anything other than HNL, initialize to default arguments
    if(!isValid){
        recommended         = "-";
        type                = "";
        mass                = 0.;
        V2                  = 0.;
        ctau                = 0.;
        ctauRatioToTheory   = 0.;
        events              = 0;
        cross_section       = 0.;
        cross_section_unc   = 0.;
        year                = "";
        directory           = "";
        flavor              = "";

        std::cout << "--HNL parameters-- No parameters initialized" << std::endl;
    }
}

void HNL_parameters::Set_Merging_parameters()
{
    if(!HNL_sample_filename.Contains("V-combined")){
        std::cout << "--HNL parameters-- Dealing with a non-merged sample" << std::endl;
        merged = false;
        return;
    }
    std::cout << "--HNL parameters-- Dealing with a merged sample" << std::endl;
    merged = true;
    std::ostringstream mass_stream;
    mass_stream << mass;
    TString file_path = __FILE__;
    TString HNL_merged_parameters_filename = file_path(0, file_path.Index("/helpertools/")) + "/data/HNL_merging_parameters/parameters_M-" + mass_stream.str() + "_" + flavor + "_" + year + "_" + type + ".txt";
    std::ifstream file(HNL_merged_parameters_filename);
    if(file.is_open()){
        std::cout << "--HNL parameters-- Getting merged info from " << HNL_merged_parameters_filename << std::endl;
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string name, Ntot_i, ctau_i, V2_i, xsec_i;
            iss >> name >> Ntot_i >> ctau_i >> V2_i >> xsec_i;

            Ntot_vec.push_back(std::stoi(Ntot_i));
            ctau_vec.push_back(std::stod(ctau_i));
            V2_vec.push_back(std::stod(V2_i));
            xsec_vec.push_back(std::stod(xsec_i));
        }
        for(unsigned i = 0; i < Ntot_vec.size(); i++){
            std::cout << Ntot_vec[i] << " " << ctau_vec[i] << " " << V2_vec[i] << " " << xsec_vec[i] << std::endl;
        }
        file.close();
    }else {
        std::cout << "--HNL parameters-- Unable to get merged info from " << HNL_merged_parameters_filename << std::endl;
    }
}

double HNL_parameters::get_reweighting_weight_merged(double V2_new, double ct, bool MajToDirac)
{
    //for all initial samples we need: Ntot_i, ctau_i, V2_i, xsec_i
    if(ctau_vec.size() < 1) std::cout << "vectors are empty!" << std::endl;
    double ctau_new = ctau_vec[0] * V2_vec[0] / V2_new * (MajToDirac? 2. : 1.);
    double xsec_new = xsec_vec[0] * V2_new / V2_vec[0];
    double exp_sum = 0.;
    for(unsigned i = 0; i < Ntot_vec.size(); i++){
        exp_sum += Ntot_vec[i] / ctau_vec[i] * exp( -ct / ctau_vec[i] );
    }
    return xsec_new / ctau_new * exp(- ct / ctau_new) / exp_sum;
}
