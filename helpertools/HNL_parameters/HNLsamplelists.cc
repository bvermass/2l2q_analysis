#include "HNL_parameters.h"

bool goodsample(HNL_parameters HNL_param)
{
    if(HNL_param.recommended.find("*") == std::string::npos)    return false;
    if(HNL_param.events < 50000)                                return false;
    if(HNL_param.type.find("dirac") != std::string::npos)       return false;//don't bother with Dirac files for now


    // The following ctau bounds for HNL sample merging was decided to make displaced samples that span the entire range. It is based on the existing set of HNL hadronic MC samples and are simple cuts that work for this specific set of MC samples
    // If this merger would be applied to new samples with other average ctau values, it would be best to verify these samples and adapt the cuts if necessary
    if(HNL_param.ctau > 500.)                                   return false;
    if(HNL_param.ctau < 6. and HNL_param.mass <= 8)             return false;
    if(HNL_param.ctau < 4. and HNL_param.mass == 10)            return false;
    if(HNL_param.ctau < 0.1 and HNL_param.mass > 10)            return false;

    return true;
}

#ifndef __CINT__
int main(int argc, char * argv[]){
    if(argc != 2){
        std::cout << "incorrect number of arguments." << std::endl;
        std::cout << "Command should be: ./test sampleList" << std::endl;
    }

    const char* delim = " ";

    std::string line;
    std::ifstream sampleList(argv[1]);
    std::map<std::string, bool> RewValListExists;
    std::map<std::string, std::string> combinedSampleNames;
    
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

            if(!goodsample(HNL_param)) continue;
            
            std::ostringstream mass_stream;
            mass_stream << HNL_param.mass;
            std::ostringstream ctau_stream;
            ctau_stream << 0.1*round(10*HNL_param.ctau);

            std::string RewValList = "../../test/sampleLists/RewVal/comb_M-" + mass_stream.str() + "_" + HNL_param.flavor + "_" + HNL_param.year + "_" + HNL_param.type + ".txt";
            std::string outputfilename = (std::string)make_outputfilename(HNLfilename, "/user/bvermass/public/2l2q_analysis/histograms/", "hists_full_analyzer", 1, 0, true);

            if(!RewValListExists[RewValList]){
                RewValListExists[RewValList] = true;
                filePutContents(RewValList, "RewVal_comb_M-" + mass_stream.str()+ "_" + HNL_param.flavor + "_" + HNL_param.year + "_" + HNL_param.type + " 2\n", false);
                combinedSampleNames[RewValList] = outputfilename.substr(0, outputfilename.find("V-")+2) + "combined" + outputfilename.substr(outputfilename.find("_" + HNL_param.flavor + "_")) + " combined\n"; 
            }

            filePutContents(RewValList, outputfilename + " c#tau-" + ctau_stream.str() + "\n", true);
        }

        // comment these 3 lines out if you want to make sampleLists for reweighting validation plots without the combined HNL sample
        for(const auto& combinedSampleName : combinedSampleNames){
            filePutContents(combinedSampleName.first, combinedSampleName.second, true);
        }
    }
}
#endif
