#include <iostream>
#include <string>
#include "../interface/PFNcutStudy.h"

void print_maxPFN(TH1F* SR, TH2F* PFN, TH1F* SRC, TH1F* SRD){
    std::cout << SR->GetName() << std::endl;
    for(int i = 1; i <= SR->GetNbinsX(); i++){
        if(SR->GetBinContent(i) == 0 or SRC->GetBinContent(i) == 0 or SRD->GetBinContent(i) == 0) std::cout << "!!!!" << std::endl;
        std::cout << "Bin " << i << ": " << SR->GetBinContent(i) << ", " << SRC->GetBinContent(i) << ", " << SRD->GetBinContent(i) << std::endl;
        //if(SR->GetBinContent(i) == 0){
        //    std::cout << " has no events" << std::endl;
        //}
        //if(SRC->GetBinContent(i) == 0){
        //    std::cout << " C has no events" << std::endl;
        //}
        //if(SRD->GetBinContent(i) == 0){
        //    std::cout << " D has no events" << std::endl;
        //}

            
        if(SR->GetBinContent(i) == 0){
            double maxPFN = 0;
            for(int j = 1; j <= PFN->GetNbinsY(); j++){
                if(PFN->GetBinContent(i, j) != 0){
                    maxPFN = std::max(PFN->GetYaxis()->GetBinLowEdge(j), maxPFN);
                }
            }
            std::cout << "Maximum PFN value is " << maxPFN << std::endl;
        }
    }
}

# ifndef __CINT__
int main(int argc, char * argv[])
{
    //PFNcutStudy mini(argv[1]);
    //double max_entries      = atof(argv[2]);
    //int partition           = atoi(argv[3]);
    //int partitionjobnumber  = atoi(argv[4]);
    //mini.analyze(max_entries, partition, partitionjobnumber);

    TFile* file_2016 = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/mini_analyzer/hists_mini_analyzer_SingleLepton_Run2016.root");
    TFile* file_1718 = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/mini_analyzer/hists_mini_analyzer_SingleLepton_Run1718.root");

    TH1F* SR_OS_High_2016 = (TH1F*)file_2016->Get("_OS_2l_M-10_V2-2e-06_cutTightmlSV_quadB_Shape_SR");
    TH1F* SR_OS_Low_2016 = (TH1F*)file_2016->Get("_OS_2l_M-5_V2-4e-06_cutTightmlSV_quadB_Shape_SR");
    TH1F* SR_SS_High_2016 = (TH1F*)file_2016->Get("_SS_2l_M-10_V2-2e-06_cutTightmlSV_quadB_Shape_SR");
    TH1F* SR_SS_Low_2016 = (TH1F*)file_2016->Get("_SS_2l_M-5_V2-4e-06_cutTightmlSV_quadB_Shape_SR");
    
    TH1F* SR_OS_High_1718 = (TH1F*)file_1718->Get("_OS_2l_M-10_V2-2e-06_cutTightmlSV_quadB_Shape_SR");
    TH1F* SR_OS_Low_1718 = (TH1F*)file_1718->Get("_OS_2l_M-5_V2-4e-06_cutTightmlSV_quadB_Shape_SR");
    TH1F* SR_SS_High_1718 = (TH1F*)file_1718->Get("_SS_2l_M-10_V2-2e-06_cutTightmlSV_quadB_Shape_SR");
    TH1F* SR_SS_Low_1718 = (TH1F*)file_1718->Get("_SS_2l_M-5_V2-4e-06_cutTightmlSV_quadB_Shape_SR");

    TH1F* SRC_OS_High_2016 = (TH1F*)file_2016->Get("_OS_2l_M-10_V2-2e-06_cutTightmlSV_quadC_Shape_SR");
    TH1F* SRC_OS_Low_2016 = (TH1F*)file_2016->Get("_OS_2l_M-5_V2-4e-06_cutTightmlSV_quadC_Shape_SR");
    TH1F* SRC_SS_High_2016 = (TH1F*)file_2016->Get("_SS_2l_M-10_V2-2e-06_cutTightmlSV_quadC_Shape_SR");
    TH1F* SRC_SS_Low_2016 = (TH1F*)file_2016->Get("_SS_2l_M-5_V2-4e-06_cutTightmlSV_quadC_Shape_SR");
    
    TH1F* SRC_OS_High_1718 = (TH1F*)file_1718->Get("_OS_2l_M-10_V2-2e-06_cutTightmlSV_quadC_Shape_SR");
    TH1F* SRC_OS_Low_1718 = (TH1F*)file_1718->Get("_OS_2l_M-5_V2-4e-06_cutTightmlSV_quadC_Shape_SR");
    TH1F* SRC_SS_High_1718 = (TH1F*)file_1718->Get("_SS_2l_M-10_V2-2e-06_cutTightmlSV_quadC_Shape_SR");
    TH1F* SRC_SS_Low_1718 = (TH1F*)file_1718->Get("_SS_2l_M-5_V2-4e-06_cutTightmlSV_quadC_Shape_SR");

    TH1F* SRD_OS_High_2016 = (TH1F*)file_2016->Get("_OS_2l_M-10_V2-2e-06_cutTightmlSV_quadD_Shape_SR");
    TH1F* SRD_OS_Low_2016 = (TH1F*)file_2016->Get("_OS_2l_M-5_V2-4e-06_cutTightmlSV_quadD_Shape_SR");
    TH1F* SRD_SS_High_2016 = (TH1F*)file_2016->Get("_SS_2l_M-10_V2-2e-06_cutTightmlSV_quadD_Shape_SR");
    TH1F* SRD_SS_Low_2016 = (TH1F*)file_2016->Get("_SS_2l_M-5_V2-4e-06_cutTightmlSV_quadD_Shape_SR");
    
    TH1F* SRD_OS_High_1718 = (TH1F*)file_1718->Get("_OS_2l_M-10_V2-2e-06_cutTightmlSV_quadD_Shape_SR");
    TH1F* SRD_OS_Low_1718 = (TH1F*)file_1718->Get("_OS_2l_M-5_V2-4e-06_cutTightmlSV_quadD_Shape_SR");
    TH1F* SRD_SS_High_1718 = (TH1F*)file_1718->Get("_SS_2l_M-10_V2-2e-06_cutTightmlSV_quadD_Shape_SR");
    TH1F* SRD_SS_Low_1718 = (TH1F*)file_1718->Get("_SS_2l_M-5_V2-4e-06_cutTightmlSV_quadD_Shape_SR");

    TH2F* PFN_OS_High_2016 = (TH2F*)file_2016->Get("_OS_2l_M-10_V2-2e-06_cutoutsidemlSV_Shape_PFN");
    TH2F* PFN_OS_Low_2016 = (TH2F*)file_2016->Get("_OS_2l_M-5_V2-4e-06_cutoutsidemlSV_Shape_PFN");
    TH2F* PFN_SS_High_2016 = (TH2F*)file_2016->Get("_SS_2l_M-10_V2-2e-06_cutoutsidemlSV_Shape_PFN");
    TH2F* PFN_SS_Low_2016 = (TH2F*)file_2016->Get("_SS_2l_M-5_V2-4e-06_cutoutsidemlSV_Shape_PFN");
    
    TH2F* PFN_OS_High_1718 = (TH2F*)file_1718->Get("_OS_2l_M-10_V2-2e-06_cutoutsidemlSV_Shape_PFN");
    TH2F* PFN_OS_Low_1718 = (TH2F*)file_1718->Get("_OS_2l_M-5_V2-4e-06_cutoutsidemlSV_Shape_PFN");
    TH2F* PFN_SS_High_1718 = (TH2F*)file_1718->Get("_SS_2l_M-10_V2-2e-06_cutoutsidemlSV_Shape_PFN");
    TH2F* PFN_SS_Low_1718 = (TH2F*)file_1718->Get("_SS_2l_M-5_V2-4e-06_cutoutsidemlSV_Shape_PFN");

    std::cout << PFN_OS_High_2016 << " " << PFN_OS_Low_2016 << " " << PFN_SS_High_2016 << " " << PFN_SS_Low_2016 << " " << PFN_OS_High_1718 << " " << PFN_OS_Low_1718 << " " << PFN_SS_High_1718 << " " << PFN_SS_Low_1718 << std::endl;

    print_maxPFN(SR_OS_High_2016, PFN_OS_High_2016, SRC_OS_High_2016, SRD_OS_High_2016);
    print_maxPFN(SR_OS_Low_2016, PFN_OS_Low_2016, SRC_OS_Low_2016, SRD_OS_Low_2016);
    print_maxPFN(SR_SS_High_2016, PFN_SS_High_2016, SRC_SS_High_2016, SRD_SS_High_2016);
    print_maxPFN(SR_SS_Low_2016, PFN_SS_Low_2016, SRC_SS_Low_2016, SRD_SS_Low_2016);
    print_maxPFN(SR_OS_High_1718, PFN_OS_High_1718, SRC_OS_High_1718, SRD_OS_High_1718);
    print_maxPFN(SR_OS_Low_1718, PFN_OS_Low_1718, SRC_OS_Low_1718, SRD_OS_Low_1718);
    print_maxPFN(SR_SS_High_1718, PFN_SS_High_1718, SRC_SS_High_1718, SRD_SS_High_1718);
    print_maxPFN(SR_SS_Low_1718, PFN_SS_Low_1718, SRC_SS_Low_1718, SRD_SS_Low_1718);

    //TH1F* regionC_SS_High_2016 = (TH1F*)file_2016->Get("_SS_2l_M-10_V2-2e-06_cutTightmlSV_quadC_Shape_SR");
    //TH1F* regionD_SS_High_2016 = (TH1F*)file_2016->Get("_SS_2l_M-10_V2-2e-06_cutTightmlSV_quadD_Shape_SR");
    //TH2F* PFNinside_SS_High_2016 = (TH2F*)file_2016->Get("_SS_2l_M-10_V2-2e-06_cutinsidemlSV_noSR_Shape_PFN");


    //std::cout << "study of region B,C,D for _SS_2l_M-10_V2-2e-06_cutTightmlSV_quadB_Shape_SR" << std::endl;
    //std::cout << "Bin i: B, C, D " << std::endl;
    //for(int i = 1; i <= SR_SS_High_2016->GetNbinsX(); i++){
    //    std::cout << "Bin " << i << ": " << SR_SS_High_2016->GetBinContent(i) << ", " << regionC_SS_High_2016->GetBinContent(i) << ", " << regionD_SS_High_2016->GetBinContent(i);
    //    if(SR_SS_High_2016->GetBinContent(i) == 0){
    //        std::cout << "          B has no events" << std::endl;
    //    }
    //    if(regionC_SS_High_2016->GetBinContent(i) == 0){
    //        std::cout << "          C has no events" << std::endl;
    //    }
    //    if(regionD_SS_High_2016->GetBinContent(i) == 0){
    //        std::cout << "          D has no events" << std::endl;
    //    }
    //        
    //    if(SR_SS_High_2016->GetBinContent(i) == 0){
    //        double maxPFN = 0, maxPFNinside = 0;
    //        for(int j = 1; j <= PFN_SS_High_2016->GetNbinsY(); j++){
    //            if(PFN_SS_High_2016->GetBinContent(i, j) != 0){
    //                maxPFN = std::max(PFN_SS_High_2016->GetYaxis()->GetBinLowEdge(j), maxPFN);
    //            }
    //            if(PFNinside_SS_High_2016->GetBinContent(i, j) != 0){
    //                maxPFNinside = std::max(PFNinside_SS_High_2016->GetYaxis()->GetBinLowEdge(j), maxPFNinside);
    //            }
    //        }
    //        std::cout << "Maximum PFN value for outside mlSV is " << maxPFN << std::endl;
    //        std::cout << "Maximum PFN value for inside mlSV is " << maxPFNinside << std::endl;
    //    }
    //    else std::cout << std::endl;
    //}

}
#endif
