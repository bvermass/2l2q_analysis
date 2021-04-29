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

