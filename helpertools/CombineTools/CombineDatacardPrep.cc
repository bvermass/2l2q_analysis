#include "CombineDatacardPrep.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    //Requirements for datacard to be made:
    // - Signal Yield > 0.1
    // - only histograms with correct flavor in their name, 'SS', '_M-', '_V2-', '_SR', '_IVF_mass'
    //
    //Argument 1: specific directory for Combine datacards
    //Argument 2 - (n+1)/2: name of root input files (first one has to be signal)
    //Argument (n+3)/2 - n: sig or bkg names
    int i_rootfiles = 2;
    int i_legends = argc/2 + 1;

    std::vector<TFile*>  files_signal;
    std::vector<TFile*>  files_bkg;
    std::vector<TFile*>  files_data;
    TString flavor, mass_str;
    std::cout << "-----Files-----" << std::endl;
    for(int i = i_rootfiles; i < i_legends; i++){
        TString filename = (TString)argv[i];
        if(filename.Index("_HeavyNeutrino_lljj_") != -1){
            std::cout << "sig: " << filename << std::endl;
            flavor = (filename.Contains("_mu_")? "_mm_" : filename.Contains("_e_")? "_ee_" : filename.Contains("_2l_")? "_2l_" : "noFlavor" );
            mass_str = filename(filename.Index("_M-"), filename.Index("_V-") + 1 - filename.Index("_M-"));
            std::cout << "mass of signal: " << mass_str << std::endl;
            files_signal.push_back(TFile::Open(filename));
        }
        else if(i == (argc + 1)/2){
            std::cout << "obs: " << filename << std::endl;
            files_data.push_back(TFile::Open(filename));
        }
        else {
            std::cout << "bkg: " << filename << std::endl;
            files_bkg.push_back(TFile::Open(filename));
        }
        //else if(filename.Index("_Run201") != -1) files_data.push_back(TFile::Open(filename));
    }
    std::vector<std::string> legends_signal;
    std::vector<std::string> legends_bkg;
    std::vector<std::string> legends_data;
    std::cout << "-----Names-----" << std::endl;
    for(int i = i_legends; i < argc; i++){
        std::string legendname = (std::string)argv[i];
        if(legendname.find("HNL") != std::string::npos){ std::cout << "sig: " << legendname << std::endl; legends_signal.push_back(legendname); }
        else if(i == argc - 1){ std::cout << "obs: " << legendname << std::endl; legends_data.push_back(legendname); }
        //else if(legendname.Index("201") != -1 or legendname.Index("Data") != -1 or legendname.Index("data") != -1) legends_data.push_back(adjust_legend(legendname));
        else{ std::cout << "bkg: " << legendname << std::endl; legends_bkg.push_back(legendname); }
    }

    // Name of directory where plots will end up
    TString specific_dir = (TString)argv[1];
    std::cout << "specific directory: " << specific_dir << std::endl;
    std::string general_pathname = (std::string)make_general_pathname("combine_unparametrized_LowAndHighMass/datacards/", specific_dir + "/");
    std::string shapeSR_pathname = (std::string)make_general_pathname("combine_unparametrized_LowAndHighMass/Shapefiles/", specific_dir + "/");
    std::string quadB_pathname   = (std::string)make_general_pathname("combine_unparametrized_LowAndHighMass/quadB_events/", specific_dir + "/");
    gSystem->Exec("mkdir -p " + (TString)general_pathname);
    gSystem->Exec("mkdir -p " + (TString)shapeSR_pathname);
    gSystem->Exec("mkdir -p " + (TString)quadB_pathname);

    // get year information for year-dependent systematics
    std::string year;
    if(specific_dir.Contains("2016")) year = "16";
    else if(specific_dir.Contains("2017")) year = "17";
    else if(specific_dir.Contains("2018")) year = "18";

    TString mass_bkg;
    if(mass_str.Contains("_M-1_") or mass_str.Contains("_M-2_") or mass_str.Contains("_M-3_") or mass_str.Contains("_M-4_") or mass_str.Contains("_M-5_")){
        mass_bkg = "_M-5_";
    }else {
        mass_bkg = "_M-10_";
    }

    TIter next(files_signal[0]->GetListOfKeys());
    TKey* key;
    while((key = (TKey*)next())){

        TClass *cl = gROOT->GetClass(key->GetClassName());

        // -- TH1 --
        if (cl->InheritsFrom("TH1") and ! cl->InheritsFrom("TH2")){ // second requirement is because TH2 also inherits from TH1
            TH1F* sample_hist_ref = (TH1F*)key->ReadObj();
            TString histname = sample_hist_ref->GetName();


            if(histname.Contains(flavor) and histname.Contains(mass_bkg) and histname.Contains("Shape_SR") and histname.Contains("cutTightmlSV_quadA_") and !histname.Contains("ABCDstat") and !histname.Contains("_sys") and !histname.Contains("_unw")){
                std::cout << std::endl << histname << std::endl;
                //if(histname.Index("_afterPFN") != -1 and histname.Index("_PV-SVdxy") != -1){

                // get signal histograms
                TH1F* hist_signal = (TH1F*) files_signal[0]->Get(histname);
                double sigYield = hist_signal->Integral();

                // get data histogram
                TString histname_data = histname;
                histname_data.ReplaceAll("quadA", "BtoAwithCD");
                //histname_data.ReplaceAll(mass_str, mass_bkg);
                histname_data.ReplaceAll((TString)histname_data(histname_data.Index("_V2-"), histname_data.Index("_cut") - histname_data.Index("_V2-")), "_V2-9e-07");
                std::cout << "data histname: " << histname_data << std::endl;
                TH1F* hist_data = (TH1F*) files_data[0]->Get(histname_data);
                double obsYield = hist_data->Integral();

                // get background histograms
                std::vector<TH1F*> hists_bkg;
                std::vector<double> bkgYield;
                for(unsigned i = 0; i < files_bkg.size(); i++){
                    hists_bkg.push_back((TH1F*)files_bkg[i]->Get(histname_data));
                    bkgYield.push_back(hists_bkg[i]->Integral());
                }
                //!!!!! temporary fix !!!!! remove !!!!!
                //bkgYield[0] = std::max(bkgYield[0], 0.1);
                //!!!!!!!!!!!!!!!!!

                //Systematic Uncertainty stuff
                std::vector<std::vector<double>> systUnc;
                std::vector<std::string> systNames;
                std::vector<std::string> systDist;

                systNames.push_back("ABCDstat");
                systDist.push_back("shapeN");
                systUnc.push_back({0,1});

                systNames.push_back((std::string)"lumi_"+year);
                systDist.push_back("lnN");
                if(year == "16" or year == "18") systUnc.push_back({1.025,0});
                else if(year == "17") systUnc.push_back({1.023,0});

                systNames.push_back("xsecNorm");
                systDist.push_back("lnN");
                systUnc.push_back({1.0386, 0});

                systNames.push_back("Trigger_sys");
                systDist.push_back("shapeN");
                systUnc.push_back({1,0});
                systNames.push_back("PileUp_sys");
                systDist.push_back("shapeN");
                systUnc.push_back({1,0});
                systNames.push_back("l1ID_sys");
                systDist.push_back("shapeN");
                systUnc.push_back({1,0});
                systNames.push_back("l2ID_sys");
                systDist.push_back("shapeN");
                systUnc.push_back({1,0});
                systNames.push_back("Track_sys");
                systDist.push_back("shapeN");
                systUnc.push_back({1,0});
                systNames.push_back("JEC_sys");
                systDist.push_back("shapeN");
                systUnc.push_back({1,0});
                systNames.push_back("JER_sys");
                systDist.push_back("shapeN");
                systUnc.push_back({1,0});

                std::vector<TH1F*> hists_signal_sys;
                std::vector<std::vector<TH1F*>> hists_bkg_sys;
                std::vector<std::string> histnames_signal_sys;
                std::vector<std::vector<std::string>> histnames_bkg_sys;
                std::vector<TH1F*> tmp_bkg_sys;
                std::vector<std::string> tmpnames_bkg_sys;
                for(unsigned i = 0; i < systNames.size(); i++){
                    if(systDist[i] != "shapeN") continue;
                    if(systUnc[i][0] != 0){//signal systs
                        TString histname_up = histname;
                        TString histname_down = histname;
                        histname_up.ReplaceAll("Shape_SR", systNames[i] + "Up_Shape_SR");
                        histname_down.ReplaceAll("Shape_SR", systNames[i] + "Down_Shape_SR");
                        if(systNames[i].find("PileUp") != std::string::npos){
                            systNames[i].replace(systNames[i].find("PileUp_"), systNames[i].find("sys"), "PileUp_"+year);
                        }
                        std::cout << "systnames: " << systNames[i] << std::endl;
                        std::cout << "histname: " << histname_up << std::endl;
                        hists_signal_sys.push_back((TH1F*)files_signal[0]->Get(histname_up));
                        std::cout << "address: " << hists_signal_sys.back() << std::endl;
                        histnames_signal_sys.push_back(legends_signal[0] + "_" + systNames[i] + "Up");
                        hists_signal_sys.push_back((TH1F*)files_signal[0]->Get(histname_down));
                        histnames_signal_sys.push_back(legends_signal[0] + "_" + systNames[i] + "Down");
                    }
                    if(systUnc[i][1] != 0){//data-driven prediction systs
                        tmp_bkg_sys.clear();
                        tmpnames_bkg_sys.clear();
                        TString histname_up = histname_data;
                        TString histname_down = histname_data;
                        histname_up.ReplaceAll("Shape_SR", "Shape_SR_" + systNames[i] + "Up");
                        histname_down.ReplaceAll("Shape_SR", "Shape_SR_" + systNames[i] + "Down");
                        //if(systNames[i].find("ABCDstat") != std::string::npos){
                        //    histname_up.ReplaceAll("TightmlSV", "CR1mlSV");
                        //    histname_down.ReplaceAll("TightmlSV", "CR1mlSV");
                        //}
                        std::cout << "systnames: " << systNames[i] << std::endl;
                        std::cout << "histname: " << histname_up << std::endl;
                        tmp_bkg_sys.push_back((TH1F*)files_bkg[0]->Get(histname_up));
                        std::cout << "address: " << tmp_bkg_sys.back() << std::endl;
                        tmpnames_bkg_sys.push_back(legends_bkg[0] + "_" + systNames[i] + "Up");
                        tmp_bkg_sys.push_back((TH1F*)files_bkg[0]->Get(histname_down));
                        tmpnames_bkg_sys.push_back(legends_bkg[0] + "_" + systNames[i] + "Down");
                        hists_bkg_sys.push_back(tmp_bkg_sys);
                        histnames_bkg_sys.push_back(tmpnames_bkg_sys);
                    }
                }

                unsigned nSyst = systNames.size();

                TString outputfilename = histname;
                outputfilename.ReplaceAll(mass_bkg, mass_str);

                //Shape analysis stuff
                bool shapeCard = true;
                std::string shapeFileName = shapeSR_pathname + (std::string)outputfilename + ".root";
                makeShapeSRFile(shapeFileName, hist_signal, hist_data, hists_bkg, legends_signal[0], legends_data[0], legends_bkg, hists_signal_sys, hists_bkg_sys, histnames_signal_sys, histnames_bkg_sys);


                //quadB yield stuff, for limit setting with gamma pdfs
                TString histname_quadB = histname;
                histname_quadB.ReplaceAll("_quadA", "_quadB");
                TH1F* hist_signal_quadB = (TH1F*) files_signal[0]->Get(histname_quadB);
                TString histname_data_quadB = histname_quadB;
                histname_data_quadB.ReplaceAll((TString)histname_data(histname_data.Index("_V2-"), histname_data.Index("_cut") - histname_data.Index("_V2-")), "_V2-9e-07");
                TH1F* hist_data_quadB = (TH1F*) files_data[0]->Get(histname_data_quadB);
                std::vector<TH1F*> hists_bkg_quadB;
                for(unsigned i = 0; i < files_bkg.size(); i++){
                    hists_bkg_quadB.push_back((TH1F*)files_bkg[i]->Get(histname_data_quadB));
                }
                std::string quadBFileName = quadB_pathname + (std::string)outputfilename + ".root";
                makequadFile(quadBFileName, hist_signal_quadB, hist_data_quadB, hists_bkg_quadB, legends_signal[0], legends_data[0], legends_bkg);

                bool autoMCStats = true;

                if(sigYield > 0.1){
                    printDataCard(general_pathname + (std::string)outputfilename + ".txt", obsYield, sigYield, legends_signal[0], &bkgYield[0], files_bkg.size(), &legends_bkg[0], systUnc, nSyst, &systNames[0], &systDist[0], shapeCard, shapeFileName, autoMCStats);
                }else {
                    std::cout << "too low signal yield: " << sigYield << std::endl;
                }
            }
        }
    }
}
#endif


void makequadFile(TString quad_filename, TH1F* hist_signal, TH1F* hist_data, std::vector<TH1F*> hists_bkg, const std::string& sigName, const std::string& dataName, const std::vector<std::string>& bkgNames)
{
    std::cout << "quad histograms in " << quad_filename << std::endl;
    TFile *quad_file = new TFile(quad_filename, "recreate");

    hist_signal->Write(sigName.c_str());
    hist_data->Write("data_obs");
    for(unsigned i = 0; i < hists_bkg.size(); i++){
        hists_bkg[i]->Write(bkgNames[i].c_str());
    }

    quad_file->Close();
}

void makeShapeSRFile(TString shapeSR_filename, TH1F* hist_signal, TH1F* hist_data, std::vector<TH1F*> hists_bkg, const std::string& sigName, const std::string& dataName, const std::vector<std::string>& bkgNames, std::vector<TH1F*> hist_signal_sys, std::vector<std::vector<TH1F*>> hists_bkg_sys, const std::vector<std::string>& sigName_sys, const std::vector<std::vector<std::string>>& bkgNames_sys)
{
    std::cout << "Shape histograms in " << shapeSR_filename << std::endl;
    TFile *shapeSR_file = new TFile(shapeSR_filename, "recreate");

    hist_signal->Write(sigName.c_str());
    hist_data->Write("data_obs");
    for(unsigned i = 0; i < hists_bkg.size(); i++){
        hists_bkg[i]->Write(bkgNames[i].c_str());
        if(hists_bkg_sys.size() > 0){
            for(unsigned j = 0; j < hists_bkg_sys[i].size(); j++){
                hists_bkg_sys[i][j]->Write(bkgNames_sys[i][j].c_str());
            }
        }
    }
    for(unsigned i = 0; i < hist_signal_sys.size(); i++){
        hist_signal_sys[i]->Write(sigName_sys[i].c_str());
    }

    shapeSR_file->Close();
}


//Function to print dataCard to be analysed by CMS combination tool
void printDataCard(const std::string& cardName, const double obsYield, const double sigYield, const std::string& sigName, const double* bkgYield, const unsigned nBkg, const std::string* bkgNames, const std::vector<std::vector<double> >& systUnc, const unsigned nSyst, const std::string* systNames, const std::string* systDist, const bool shapeCard, const std::string& shapeFileName, const bool autoMCStats ){
    std::cout << "Datacard in " << cardName << std::endl;

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
        card << "shapes * * " << shapeFileName + " $PROCESS $PROCESS_$SYSTEMATIC\n";
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
        card << "* autoMCStats 10\n";
    }
    
    card.close();       
}
