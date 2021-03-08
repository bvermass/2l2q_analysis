#include <iostream>
#include <fstream>
#include <sstream>

//Include root header files
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>


std::map<TString, double> get_yields(TString filename)
{
    std::vector<TString> flavors = {"_OS_mm", "_SS_mm", "_OS_ee", "_SS_ee", "_OS_me", "_SS_me", "_OS_em", "_SS_em"};
    TFile *input = new TFile(filename, "open");
    std::map<TString, double> values;
    for(TString flavor : flavors){
        TString histname = flavor+"_2Jets_mll";
        TH1F* h = (TH1F*) input->Get(histname);
        values[histname] = h->Integral();
    }
    input->Close();
    return values;
}

#ifndef __CINT__
int main(int argc, char * argv[])
{
    std::vector<TString> flavors = {"_OS_mm", "_SS_mm", "_OS_ee", "_SS_ee", "_OS_me", "_SS_me", "_OS_em", "_SS_em"};
    //if(argc != 3){
    //    std::cout << "command should be: ./a.out [filename] [treename]" << std::endl;
    //    return 1;
    //}
    std::vector<TString> samples,legends;
    std::ifstream file(argv[1]);
    std::string line;
    if(file.is_open()){
        while(std::getline(file, line)){
            std::istringstream iss(line);
            TString samplename, leg;
            iss >> samplename >> leg;
            samples.push_back(samplename);
            legends.push_back(leg);
        }
    }
    file.close();

    //for OS mm training mll, get yields of each sample and print them in latex table format
    std::map<TString, std::map<TString, double>> yields;
    for(unsigned i = 0; i < samples.size(); i++){
        yields[legends[i]] = get_yields(samples[i]);
    }

    for(TString flavor : flavors){
        TString hname = flavor + "_2Jets_mll";
        std::cout << "\\begin{tabular}{|c|c|c|c|}" << std::endl;
        std::cout << "    \\hline" << std::endl;
        std::cout << flavor << " & 2016 & 2017 & 2018\\\\" << std::endl;
        std::cout << "    \\hline" << std::endl;
        std::cout << "Data & " << yields["2016"][hname] << " & " << yields["2017"][hname] << " & " << yields["2018"][hname] << "\\\\" << std::endl;
        std::cout << "W+Jets & " << yields["W+Jets16"][hname] << " & " << yields["W+Jets17"][hname] << " & " << yields["W+Jets18"][hname] << "\\\\" << std::endl;
        std::cout << "DY & " << yields["DY5016"][hname] + yields["DY10-5016"][hname] << " & " << yields["DY17"][hname] << " & " << yields["DY18"][hname] << "\\\\" << std::endl;
        std::cout << "Top & " << yields["Top16"][hname] << " & " << yields["Top17"][hname] << " & " << yields["Top18"][hname] << "\\\\" << std::endl;
        std::cout << "ZG & " << yields["ZG16"][hname] << " & " << yields["ZG17"][hname] << " & " << yields["ZG18"][hname] << "\\\\" << std::endl;
        std::cout << "WG & " << yields["WG16"][hname] << " & " << yields["WG17"][hname] << " & " << yields["WG18"][hname] << "\\\\" << std::endl;
        std::cout << "Diboson & " << yields["Diboson16"][hname] << " & " << yields["Diboson17"][hname] << " & " << yields["Diboson18"][hname] << "\\\\" << std::endl;
        std::cout << "\\end{tabular}" << std::endl;
    }
    return 0;
}
#endif
