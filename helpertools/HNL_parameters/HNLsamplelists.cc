#include "HNL_parameters.h"

bool good_HNLtagger_sample(HNL_parameters HNL_param)
{
    if(HNL_param.recommended.find("*") == std::string::npos) return false;
    if(HNL_param.flavor.find("2l") != std::string::npos) return false;
    if(HNL_param.flavor.find("3l") != std::string::npos) return false;
    if(HNL_param.year.find("2016") == std::string::npos) return false;
    if(HNL_param.ctau > 200.) return false;
    if(HNL_param.ctau < 0.1) return false;
    return true;
}

bool goodsample(HNL_parameters HNL_param)
{
    if(HNL_param.recommended.find("*") == std::string::npos)    return false;
    if(HNL_param.events < 100000)                                return false;
    if(HNL_param.type.find("dirac") != std::string::npos)       return false;//don't bother with Dirac files for now


    // The following ctau bounds for HNL sample merging was decided to make displaced samples that span the entire range. It is based on the existing set of HNL hadronic MC samples and are simple cuts that work for this specific set of MC samples
    // If this merger would be applied to new samples with other average ctau values, it would be best to verify these samples and adapt the cuts if necessary
    if(HNL_param.ctau > 200.)                                   return false;
    if(HNL_param.ctau < 6. and HNL_param.mass <= 8)             return false;
    if(HNL_param.ctau < 4. and HNL_param.mass == 10)            return false;
    if(HNL_param.ctau < 0.1 and HNL_param.mass > 10)            return false;


    // delete this when reweighting works
    if(HNL_param.flavor == "2l"){
        if(HNL_param.mass == 1 and fabs(HNL_param.ctau - 75) < 10) return true;
        if(HNL_param.mass == 2 and fabs(HNL_param.ctau - 32.2) < 0.1) return true;
        if(HNL_param.mass == 3 and fabs(HNL_param.ctau - 37.9) < 0.1) return true;
        if(HNL_param.mass == 4 and fabs(HNL_param.ctau - 30.3) < 0.1) return true;
        if(HNL_param.mass == 5 and fabs(HNL_param.ctau - 24.5) < 0.1) return true;
        if(HNL_param.mass == 6 and fabs(HNL_param.ctau - 80.2) < 0.1) return true;
        if(HNL_param.mass == 8 and fabs(HNL_param.ctau - 104.1) < 0.1) return true;
        if(HNL_param.mass == 10 and fabs(HNL_param.ctau - 6) < 0.1) return true;
        if(HNL_param.mass == 12 and fabs(HNL_param.ctau - 1.9) < 0.1) return true;
        if(HNL_param.mass == 14 and fabs(HNL_param.ctau - 1.2) < 0.1) return true;
    }else if(HNL_param.flavor == "e"){
        if(HNL_param.mass == 1 and fabs(HNL_param.ctau - 75) < 10) return true;
        if(HNL_param.mass == 2 and fabs(HNL_param.ctau - 41) < 1) return true;
        if(HNL_param.mass == 3 and fabs(HNL_param.ctau - 23) < 0.1) return true;
        if(HNL_param.mass == 4 and fabs(HNL_param.ctau - 57.4) < 0.1) return true;
        if(HNL_param.mass == 5 and fabs(HNL_param.ctau - 92.4) < 0.1) return true;
        if(HNL_param.mass == 6 and fabs(HNL_param.ctau - 109.2) < 0.1) return true;
        if(HNL_param.mass == 8 and fabs(HNL_param.ctau - 62.4) < 0.1) return true;
        if(HNL_param.mass == 10 and fabs(HNL_param.ctau - 6.9) < 0.1) return true;
        if(HNL_param.mass == 12 and fabs(HNL_param.ctau - 3.9) < 0.1) return true;
        if(HNL_param.mass == 14 and fabs(HNL_param.ctau - 2.3) < 0.1) return true;
        if(HNL_param.mass == 15 and fabs(HNL_param.ctau - 216.6) < 0.1) return true;
    }else if(HNL_param.flavor == "mu"){
        if(HNL_param.mass == 1 and fabs(HNL_param.ctau - 75) < 10) return true;
        if(HNL_param.mass == 2 and fabs(HNL_param.ctau - 41) < 1) return true;
        if(HNL_param.mass == 3 and fabs(HNL_param.ctau - 23.1) < 0.1) return true;
        if(HNL_param.mass == 4 and fabs(HNL_param.ctau - 57.5) < 0.1) return true;
        if(HNL_param.mass == 5 and fabs(HNL_param.ctau - 92.9) < 0.1) return true;
        if(HNL_param.mass == 6 and fabs(HNL_param.ctau - 109.7) < 0.1) return true;
        if(HNL_param.mass == 8 and fabs(HNL_param.ctau - 62.6) < 0.1) return true;
        if(HNL_param.mass == 10 and fabs(HNL_param.ctau - 6.9) < 0.1) return true;
        if(HNL_param.mass == 12 and fabs(HNL_param.ctau - 3.9) < 0.1) return true;
        if(HNL_param.mass == 14 and fabs(HNL_param.ctau - 2.3) < 0.1) return true;
        if(HNL_param.mass == 15 and fabs(HNL_param.ctau - 216.6) < 0.1) return true;
    }


    return false;

    //return true;
}

void add_HNLfile_to_BkgEstimator_HNLsampleList(TString HNLfilename)
{
    std::string miniList = "../../test/sampleLists/mini_analyzer/HNL.txt";
    std::string BkgEstimatorName = (std::string)make_outputfilename(HNLfilename, "/user/bvermass/public/2l2q_analysis/trees_POGTightID/BkgEstimator/", "BkgEstimator", 1, 0, true);
    filePutContents(miniList, BkgEstimatorName + " -1 1\n", true);
}

#ifndef __CINT__
int main(int argc, char * argv[]){
    if(argc != 2){
        std::cout << "incorrect number of arguments." << std::endl;
        std::cout << "Command should be: ./test sampleList" << std::endl;
    }

    //booleans to decide which lists I want to make
    bool make_full_analyzer_lists = false;
    bool make_mini_analyzer_lists = false;
    bool make_HNLtagger_list = true;


    const char* delim = " ";

    std::string line;
    std::ifstream sampleList(argv[1]);
    std::map<std::string, bool> RewValListExists, miniListExists;
    std::map<std::string, std::string> combinedSampleNames, mini_combinedSampleNames;
    
    if(sampleList.is_open()){
        while(std::getline(sampleList, line)){
            if(line.size() == 0 or line.find("#") != std::string::npos or line.find_first_not_of(" ") == std::string::npos) continue;
            
            std::vector<std::string> line_split;
            size_t start, end = 0;
            while((start = line.find_first_not_of(delim, end)) != std::string::npos){
                end = line.find(delim, start);
                line_split.push_back(line.substr(start, end - start));
            }

            std::string HNLfilename = line_split[0];
            if(HNLfilename.find("HeavyNeutrino_lljj") == std::string::npos) continue;

            HNL_parameters HNL_param("../../data/HNL_parameters/availableHeavyNeutrinoSamples.txt", HNLfilename);
            std::ostringstream mass_stream;
            mass_stream << HNL_param.mass;
            std::ostringstream ctau_stream;
            ctau_stream << 0.1*round(10*HNL_param.ctau);


            // HNLtagger selection for training
            if(make_HNLtagger_list and good_HNLtagger_sample(HNL_param)){
                std::string HNLtagger_sampleList = "../../test/sampleLists/HNLtagger/HNLtagger_muon_2016.txt";
                filePutContents(HNLtagger_sampleList, HNLfilename + "\n", true);
            }


            if(!goodsample(HNL_param)) continue;

            // full_analyzer output
            if(make_full_analyzer_lists){
                add_HNLfile_to_BkgEstimator_HNLsampleList(HNLfilename);

                std::string RewValList = "../../test/sampleLists/RewVal/comb_M-" + mass_stream.str() + "_" + HNL_param.flavor + "_" + HNL_param.year + "_" + HNL_param.type + ".txt";
                std::string outputfilename = (std::string)make_outputfilename(HNLfilename, "/user/bvermass/public/2l2q_analysis/histograms_POGTightID/", "hists_full_analyzer", 1, 0, true);

                if(!RewValListExists[RewValList]){
                    RewValListExists[RewValList] = true;
                    filePutContents(RewValList, "RewVal_comb_M-" + mass_stream.str()+ "_" + HNL_param.flavor + "_" + HNL_param.year + "_" + HNL_param.type + " 2\n", false);
                    combinedSampleNames[RewValList] = outputfilename.substr(0, outputfilename.find("V-")+2) + "combined" + outputfilename.substr(outputfilename.find("_" + HNL_param.flavor + "_")) + " combined\n"; 
                }

                filePutContents(RewValList, outputfilename + " c#tau-" + ctau_stream.str() + "\n", true);
            }


            // mini_analyzer output
            if(make_mini_analyzer_lists){
                if(HNLfilename.find("trees_POGTightID") != std::string::npos){
                    std::string miniList = "../../test/sampleLists/RewVal/mini_analyzer/comb_M-" + mass_stream.str() + "_" + HNL_param.flavor + "_" + HNL_param.year + "_" + HNL_param.type + ".txt";
                    std::cout << miniList << std::endl;
                    TString HNLfilename_copy = HNLfilename;
                    HNLfilename_copy.ReplaceAll("trees_POGTightID/BkgEstimator/final/full_analyzer/BkgEstimator_", "histograms_POGTightID/mini_analyzer/hists_mini_analyzer_");
                    std::string mini_outputfilename = (std::string) HNLfilename_copy;

                    if(!miniListExists[miniList]){
                        miniListExists[miniList] = true;
                        filePutContents(miniList, "mini_RewVal_comb_M-" + mass_stream.str()+ "_" + HNL_param.flavor + "_" + HNL_param.year + "_" + HNL_param.type + " 2\n", false);
                        mini_combinedSampleNames[miniList] = mini_outputfilename.substr(0, mini_outputfilename.find("V-")+2) + "combined" + mini_outputfilename.substr(mini_outputfilename.find("_" + HNL_param.flavor + "_")) + " combined\n"; 
                    }

                    filePutContents(miniList, mini_outputfilename + " c#tau-" + ctau_stream.str() + "\n", true);
                }
            }
        }

        // comment these 3 lines out if you want to make sampleLists for reweighting validation plots without the combined HNL sample
        if(make_full_analyzer_lists){
            for(const auto& combinedSampleName : combinedSampleNames){
                filePutContents(combinedSampleName.first, combinedSampleName.second, true);
            }
        }
        // mini
        if(make_mini_analyzer_lists){
            for(const auto& combinedSampleName : mini_combinedSampleNames){
                filePutContents(combinedSampleName.first, combinedSampleName.second, true);
            }
        }
    }
}
#endif
