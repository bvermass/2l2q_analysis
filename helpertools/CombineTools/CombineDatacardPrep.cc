#include "CombineDatacardPrep.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    //Argument 1: specific directory for Combine datacards
    //Argument 2 - (n+1)/2: name of root input files (first one has to be signal)
    //Argument (n+3)/2 - n: sig or bkg names
    int i_rootfiles = 2;
    int i_legends = argc/2 + 1;

    std::vector<TFile*>  files_signal;
    std::vector<TFile*>  files_bkg;
    std::vector<TFile*>  files_data;
    TString flavor;
    std::cout << "-----Files-----" << std::endl;
    for(int i = i_rootfiles; i < i_legends; i++){
        TString filename = (TString)argv[i];
        if(filename.Index("_HeavyNeutrino_lljj_") != -1){ std::cout << "sig: " << filename << std::endl; flavor = (filename.Index("_mu_") != -1? "mu" : "e"); files_signal.push_back(TFile::Open(filename)); }
        else if(filename.Index("_Background_") != -1){ std::cout << "bkg: " << filename << std::endl; files_bkg.push_back(TFile::Open(filename)); }
        else if(i == (argc + 1)/2){ std::cout << "obs: " << filename << std::endl; files_data.push_back(TFile::Open(filename)); }
        //else if(filename.Index("_Run201") != -1) files_data.push_back(TFile::Open(filename));
    }
    std::vector<std::string> legends_signal;
    std::vector<std::string> legends_bkg;
    std::vector<std::string> legends_data;
    std::cout << "-----Names-----" << std::endl;
    for(int i = i_legends; i < argc; i++){
        std::string legendname = (std::string)argv[i];
        if(legendname.find("HNL") != std::string::npos){ std::cout << "sig: " << legendname << std::endl; legends_signal.push_back(legendname); }
        else if(i == argc){ std::cout << "obs: " << legendname << std::endl; legends_data.push_back(legendname); }
        //else if(legendname.Index("201") != -1 or legendname.Index("Data") != -1 or legendname.Index("data") != -1) legends_data.push_back(adjust_legend(legendname));
        else{ std::cout << "bkg: " << legendname << std::endl; legends_bkg.push_back(legendname); }
    }

    // Name of directory where plots will end up
    TString specific_dir = (TString)argv[1];
    std::cout << "specific directory: " << specific_dir << std::endl;
    std::string general_pathname = (std::string)make_general_pathname("datacards/", specific_dir + "/");
    gSystem->Exec("mkdir -p " + (TString)general_pathname);

    TIter next(files_signal[0]->GetListOfKeys());
    TKey* key;
    while(key = (TKey*)next()){

        TClass *cl = gROOT->GetClass(key->GetClassName());

        // -- TH1 --
        if (cl->InheritsFrom("TH1") and ! cl->InheritsFrom("TH2")){ // second requirement is because TH2 also inherits from TH1
            TH1F* sample_hist_ref = (TH1F*)key->ReadObj();
            TString histname = sample_hist_ref->GetName();
            if(histname.Index(flavor) != -1 and histname.Index("_M-") != -1 and histname.Index("_V2-") != -1 and histname.Index("_afterPFN") != -1 and histname.Index("_ctau") == -1){
            //if(histname.Index("_afterPFN") != -1 and histname.Index("_PV-SVdxy") != -1){

                // get signal histograms
                TH1F* hist_signal = (TH1F*) files_signal[0]->Get(histname);
                double sigYield = hist_signal->GetBinContent(1);

                TString histname_bkg(histname(0, histname.Index("_M-")));

                // get data histogram
                TH1F* hist_data = (TH1F*) files_data[0]->Get(histname_bkg);
                double obsYield = hist_data->GetBinContent(1);

                // get background histograms
                std::vector<TH1F*> hists_bkg;
                std::vector<double> bkgYield;
                for(int i = 0; i < files_bkg.size(); i++){
                    hists_bkg.push_back((TH1F*)files_bkg[i]->Get(histname_bkg));
                    bkgYield.push_back(hists_bkg[i]->GetBinContent(1));
                }

                //Systematic Uncertainty stuff
                //std::vector<std::vector<double>> systUnc;
                //unsigned nSyst;
                //std::vector<std::string> systNames;
                //std::vector<std::string> systDist;
                //
                ////Shape analysis stuff
                //bool shapeCard = false;
                //std::string shapeFilename = "";

                //bool autoMCStats = false;

                printDataCard(general_pathname + (std::string)histname + ".txt", obsYield, sigYield, legends_signal[0], &bkgYield[0], files_bkg.size(), &legends_bkg[0]);
            }
        }
    }
}
#endif


//Function to print dataCard to be analysed by CMS combination tool
void printDataCard(const std::string& cardName, const double obsYield, const double sigYield, const std::string& sigName, const double* bkgYield, const unsigned nBkg, const std::string* bkgNames, const std::vector<std::vector<double> >& systUnc, const unsigned nSyst, const std::string* systNames, const std::string* systDist, const bool shapeCard, const std::string& shapeFileName, const bool autoMCStats ){

    //stream for writing card
    std::ofstream card;

    //add .txt to name if no file extension is given
    card.open(cardName + ((cardName.find(".") == std::string::npos) ? ".txt" : "") ); //add .txt to name if no file extension is given

    //define number of channels, background sources and systematics
    card << "imax 1 number of channels \n";
    card << "jmax " << nBkg << " number of backgrounds \n";
    card << "kmax " << nSyst << " number of nuisance parameters (sources of systematical uncertainties) \n";
    card << "---------------------------------------------------------------------------------------- \n";

    //define the channels and the number of observed events
    card << "bin bin1 \n";
    card << "observation " << obsYield << "\n";

    //define all backgrounds and their yields
    card << "---------------------------------------------------------------------------------------- \n";
    if(shapeCard){
        card << "shapes * * " << shapeFileName + ".root  $PROCESS $PROCESS_$SYSTEMATIC\n";
        card << "---------------------------------------------------------------------------------------- \n";
    }
    card << "bin    ";
    for(unsigned proc = 0; proc < nBkg + 1; ++proc){
        card << "   " << "bin1";
    }
    card << "\n";
    card << "process";
    card << "   " << sigName;
    for(unsigned bkg = 0; bkg < nBkg; ++bkg){
        card << "   " << bkgNames[bkg];
    }
    card << "\n";
    card << "process";
    for(unsigned bkg = 0; bkg < nBkg + 1; ++bkg){
        card << "   " << bkg;
    }
    card << "\n";
    card << "rate";
    card << "   " << sigYield;
    for(unsigned bkg = 0; bkg < nBkg; ++bkg){
        if(bkgYield[bkg] <= 0) card << "    " << "0.00";
        else card << "  " << bkgYield[bkg];
    }
    card << "\n";
    card << "---------------------------------------------------------------------------------------- \n";

    //define sources of systematic uncertainty, what distibution they follow and how large their effect is
    if( nSyst != 0 ){
        for(unsigned syst = 0; syst < nSyst; ++syst){
            card << systNames[syst] << "    " << systDist[syst];
            for(unsigned proc = 0; proc < nBkg + 1; ++proc){
                card << "   ";
                if(systUnc[syst][proc] == 0) card << "-";
                else card << systUnc[syst][proc];
            }
            card << "\n";
        }
    }

    //add line to automatically include statistical uncertainties from the MC shape histograms 
    if( autoMCStats ){
        card << "* autoMCStats 0\n";
    }
    
    card.close();       
}
