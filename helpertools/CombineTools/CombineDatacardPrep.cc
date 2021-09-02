#include "CombineDatacardPrep.h"


# ifndef __CINT__
int main(int argc, char * argv[])
{
    setTDRStyle();
    gROOT->ForceStyle();

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
    TFile*  files_signal_JECUp, *files_signal_JECDown, *files_signal_JERUp, *files_signal_JERDown, *files_bkg_ABCDsys;
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

            // Get JEC and JER histogram files
            TString filename_JECDown = filename;
            filename_JECDown.ReplaceAll("hists_mini_analyzer", "JECDown/hists_mini_analyzer_JECDown");
            std::cout << "JECDown: " << filename_JECDown << std::endl;
            files_signal_JECDown = TFile::Open(filename_JECDown);
            TString filename_JECUp = filename;
            filename_JECUp.ReplaceAll("hists_mini_analyzer", "JECUp/hists_mini_analyzer_JECUp");
            std::cout << "JECUp: " << filename_JECUp << std::endl;
            files_signal_JECUp = TFile::Open(filename_JECUp);
            TString filename_JERDown = filename;
            filename_JERDown.ReplaceAll("hists_mini_analyzer", "JERDown/hists_mini_analyzer_JERDown");
            files_signal_JERDown = TFile::Open(filename_JERDown);
            TString filename_JERUp = filename;
            filename_JERUp.ReplaceAll("hists_mini_analyzer", "JERUp/hists_mini_analyzer_JERUp");
            files_signal_JERUp = TFile::Open(filename_JERUp);
        }
        else if(i == (argc + 1)/2){
            std::cout << "obs: " << filename << std::endl;
            files_data.push_back(TFile::Open(filename));
        }
        else {
            std::cout << "bkg: " << filename << std::endl;
            files_bkg.push_back(TFile::Open(filename));
            TString filename_ABCDsys = filename;
            filename_ABCDsys.ReplaceAll("Run2016", "Run2");
            filename_ABCDsys.ReplaceAll("Run1718", "Run2");
            files_bkg_ABCDsys = TFile::Open(filename_ABCDsys);
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
    std::string quadC_pathname   = (std::string)make_general_pathname("combine_unparametrized_LowAndHighMass/quadC_events/", specific_dir + "/");
    std::string quadD_pathname   = (std::string)make_general_pathname("combine_unparametrized_LowAndHighMass/quadD_events/", specific_dir + "/");
    std::string sysEffect_pathname   = (std::string)make_general_pathname("combine_unparametrized_LowAndHighMass/SysEffects/", specific_dir + "/");
    gSystem->Exec("mkdir -p " + (TString)general_pathname);
    gSystem->Exec("mkdir -p " + (TString)shapeSR_pathname);
    gSystem->Exec("mkdir -p " + (TString)quadB_pathname);
    gSystem->Exec("mkdir -p " + (TString)quadC_pathname);
    gSystem->Exec("mkdir -p " + (TString)quadD_pathname);
    gSystem->Exec("mkdir -p " + (TString)sysEffect_pathname);

    // get year information for year-dependent systematics
    std::string year;
    if(specific_dir.Contains("2016")) year = "16";
    else if(specific_dir.Contains("2017")) year = "17";
    else if(specific_dir.Contains("2018")) year = "18";
    else if(specific_dir.Contains("1718")) year = "1718";

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

                systNames.push_back("ABCDsys");
                systDist.push_back("shapeN");
                systUnc.push_back({0,1});

                systNames.push_back("lumi_correlated");
                systDist.push_back("lnN");
                if(year == "16") systUnc.push_back({1.006, 0});
                else if(year == "1718") systUnc.push_back({1.0155, 0});

                systNames.push_back((std::string)"lumi_"+year);
                systDist.push_back("lnN");
                if(year == "16") systUnc.push_back({1.01,0});
                else if(year == "1718") systUnc.push_back({1.0126,0});

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
                systNames.push_back("JEC_"+year+"_sys");
                systDist.push_back("shapeN");
                systUnc.push_back({1,0});
                systNames.push_back("JER_"+year+"_sys");
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

                        if(systNames[i].find("JEC") != std::string::npos){
                            std::cout << "systnames: " << systNames[i] << std::endl;
                            std::cout << "histname: " << histname_up << std::endl;
                            hists_signal_sys.push_back((TH1F*)files_signal_JECUp->Get(histname_up));
                            std::cout << "address: " << hists_signal_sys.back() << std::endl;
                            histnames_signal_sys.push_back(legends_signal[0] + "_" + systNames[i] + "Up");
                            hists_signal_sys.push_back((TH1F*)files_signal_JECDown->Get(histname_down));
                            histnames_signal_sys.push_back(legends_signal[0] + "_" + systNames[i] + "Down");
                            //set_UpAndDown_correctly(hist_signal, hists_signal_sys[hists_signal_sys.size()-2], hists_signal_sys.back());
                        }else if(systNames[i].find("JER") != std::string::npos){
                            std::cout << "systnames: " << systNames[i] << std::endl;
                            std::cout << "histname: " << histname_up << std::endl;
                            hists_signal_sys.push_back((TH1F*)files_signal_JERUp->Get(histname_up));
                            std::cout << "address: " << hists_signal_sys.back() << std::endl;
                            histnames_signal_sys.push_back(legends_signal[0] + "_" + systNames[i] + "Up");
                            hists_signal_sys.push_back((TH1F*)files_signal_JERDown->Get(histname_down));
                            histnames_signal_sys.push_back(legends_signal[0] + "_" + systNames[i] + "Down");
                            //set_UpAndDown_correctly(hist_signal, hists_signal_sys[hists_signal_sys.size()-2], hists_signal_sys.back());
                        }else{
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
                    }
                    if(systUnc[i][1] != 0){//data-driven prediction systs
                        if(systNames[i].find("ABCDsys") != std::string::npos){
                            TString histname_up_pred = histname_data;
                            histname_up_pred.ReplaceAll("cutTightmlSV", "cutTightCR2NoJetVetomlSV");
                            TString histname_up_obs = histname_up_pred;
                            histname_up_obs.ReplaceAll("BtoAwithCD", "quadA");
                            //histname_up.ReplaceAll("Shape_SR", "Shape_SR_" + systNames[i] + "Up"); //used to be the method from CR1
                            //histname_down.ReplaceAll("Shape_SR", "Shape_SR_" + systNames[i] + "Down");//used to be the method from CR1
                            std::cout << "systnames: " << systNames[i] << std::endl;
                            std::cout << "histname: " << histname_up_pred << std::endl;

                            //Get CR2NojetVeto prediction histograms from full run 2 data files
                            TH1F* hist_CR2_pred = (TH1F*)files_bkg_ABCDsys->Get(histname_up_pred);
                            TH1F* hist_CR2_obs = (TH1F*)files_bkg_ABCDsys->Get(histname_up_obs);
                            //Create ABCDsys histograms based on variation of SR histograms with relative stat unc from CR2 histograms
                            TH1F* hist_ABCDsys_up   = (TH1F*)hists_bkg[0]->Clone((legends_bkg[0] + "_" + systNames[i] + "Up").c_str());
                            TH1F* hist_ABCDsys_down = (TH1F*)hists_bkg[0]->Clone((legends_bkg[0] + "_" + systNames[i] + "Down").c_str());
                            for(int i = 1; i <= hist_ABCDsys_up->GetNbinsX(); i++){
                                if(hist_CR2_pred->GetBinContent(i) == 0 or hist_CR2_pred->GetBinErrorUp(i) == 0 or hist_CR2_obs->GetBinContent(i) == 0 or hist_CR2_obs->GetBinErrorUp(i) == 0){
                                    hist_ABCDsys_up->SetBinContent(i, hists_bkg[0]->GetBinContent(i)*2);
                                    hist_ABCDsys_down->SetBinContent(i, 0.);
                                }else{
                                    double ErrorUp = sqrt(pow(hist_CR2_pred->GetBinErrorUp(i)/hist_CR2_pred->GetBinContent(i),2) + pow(hist_CR2_obs->GetBinErrorUp(i)/hist_CR2_obs->GetBinContent(i),2));
                                    double ErrorDown = sqrt(pow(hist_CR2_pred->GetBinErrorLow(i)/hist_CR2_pred->GetBinContent(i),2) + pow(hist_CR2_obs->GetBinErrorLow(i)/hist_CR2_obs->GetBinContent(i),2));
                                    hist_ABCDsys_up->SetBinContent(i, hists_bkg[0]->GetBinContent(i)*(1 + ErrorUp));
                                    hist_ABCDsys_down->SetBinContent(i, hists_bkg[0]->GetBinContent(i)*(1 - ErrorDown));
                                }
                            }

                            tmp_bkg_sys.push_back(hist_ABCDsys_up);
                            tmp_bkg_sys.push_back(hist_ABCDsys_down);
                            std::cout << "address: " << tmp_bkg_sys.back() << std::endl;
                            tmpnames_bkg_sys.push_back(legends_bkg[0] + "_" + systNames[i] + "Up");
                            tmpnames_bkg_sys.push_back(legends_bkg[0] + "_" + systNames[i] + "Down");
                        }
                    }
                }
                hists_bkg_sys.push_back(tmp_bkg_sys);
                histnames_bkg_sys.push_back(tmpnames_bkg_sys);


                unsigned nSyst = systNames.size();

                TString outputfilename = histname;
                outputfilename.ReplaceAll(mass_bkg, mass_str);

                //Shape analysis stuff
                bool shapeCard = true;
                std::string shapeFileName = shapeSR_pathname + (std::string)outputfilename + ".root";
                makeShapeSRFile(shapeFileName, hist_signal, hist_data, hists_bkg, legends_signal[0], legends_data[0], legends_bkg, hists_signal_sys, hists_bkg_sys, histnames_signal_sys, histnames_bkg_sys);
                TString sysEffectFilename = sysEffect_pathname + outputfilename + ".png";
                plotSysEffects(sysEffectFilename, hist_signal, hists_signal_sys, histnames_signal_sys);
                checkfornans(histnames_signal_sys, histnames_bkg_sys, hists_signal_sys, hists_bkg_sys);


                //quadB,C,D yield stuff, for limit setting with gamma pdfs
                TString histname_quadB = histname;
                TString histname_quadC = histname;
                TString histname_quadD = histname;
                histname_quadB.ReplaceAll("_quadA", "_quadB");
                histname_quadC.ReplaceAll("_quadA", "_quadC");
                histname_quadD.ReplaceAll("_quadA", "_quadD");
                TH1F* hist_signal_quadB = (TH1F*) files_signal[0]->Get(histname_quadB);
                TH1F* hist_signal_quadC = (TH1F*) files_signal[0]->Get(histname_quadC);
                TH1F* hist_signal_quadD = (TH1F*) files_signal[0]->Get(histname_quadD);
                double sigYieldB = hist_signal_quadB->Integral();
                double sigYieldC = hist_signal_quadC->Integral();
                double sigYieldD = hist_signal_quadD->Integral();
                TString histname_data_quadB = histname_quadB;
                TString histname_data_quadC = histname_quadC;
                TString histname_data_quadD = histname_quadD;
                histname_data_quadB.ReplaceAll((TString)histname_data(histname_data.Index("_V2-"), histname_data.Index("_cut") - histname_data.Index("_V2-")), "_V2-9e-07");
                histname_data_quadC.ReplaceAll((TString)histname_data(histname_data.Index("_V2-"), histname_data.Index("_cut") - histname_data.Index("_V2-")), "_V2-9e-07");
                histname_data_quadD.ReplaceAll((TString)histname_data(histname_data.Index("_V2-"), histname_data.Index("_cut") - histname_data.Index("_V2-")), "_V2-9e-07");
                TH1F* hist_data_quadB = (TH1F*) files_data[0]->Get(histname_data_quadB);
                TH1F* hist_data_quadC = (TH1F*) files_data[0]->Get(histname_data_quadC);
                TH1F* hist_data_quadD = (TH1F*) files_data[0]->Get(histname_data_quadD);
                double obsYieldB = hist_data_quadB->Integral();
                double obsYieldC = hist_data_quadC->Integral();
                double obsYieldD = hist_data_quadD->Integral();
                std::vector<TH1F*> hists_bkg_quadB;
                std::vector<TH1F*> hists_bkg_quadC;
                std::vector<TH1F*> hists_bkg_quadD;
                std::vector<double> bkgYieldB;
                std::vector<double> bkgYieldC;
                std::vector<double> bkgYieldD;
                for(unsigned i = 0; i < files_bkg.size(); i++){
                    hists_bkg_quadB.push_back((TH1F*)files_bkg[i]->Get(histname_data_quadB));
                    hists_bkg_quadC.push_back((TH1F*)files_bkg[i]->Get(histname_data_quadC));
                    hists_bkg_quadD.push_back((TH1F*)files_bkg[i]->Get(histname_data_quadD));
                    bkgYieldB.push_back(hists_bkg_quadB[i]->Integral());
                    bkgYieldC.push_back(hists_bkg_quadC[i]->Integral());
                    bkgYieldD.push_back(hists_bkg_quadD[i]->Integral());
                }
                std::string quadBFileName = quadB_pathname + (std::string)outputfilename + ".root";
                std::string quadCFileName = quadC_pathname + (std::string)outputfilename + ".root";
                std::string quadDFileName = quadD_pathname + (std::string)outputfilename + ".root";
                makequadFile(quadBFileName, hist_signal_quadB, hist_data_quadB, hists_bkg_quadB, legends_signal[0], legends_data[0], legends_bkg);
                makequadFile(quadCFileName, hist_signal_quadC, hist_data_quadC, hists_bkg_quadC, legends_signal[0], legends_data[0], legends_bkg);
                makequadFile(quadDFileName, hist_signal_quadD, hist_data_quadD, hists_bkg_quadD, legends_signal[0], legends_data[0], legends_bkg);

                bool autoMCStats = true;

                if(sigYield > 0.1){
                    //printDataCard(general_pathname + (std::string)outputfilename + ".txt", obsYield, sigYield, legends_signal[0], &bkgYield[0], files_bkg.size(), &legends_bkg[0], systUnc, nSyst, &systNames[0], &systDist[0], shapeCard, shapeFileName, autoMCStats);
                    printABCDDataCard(general_pathname + (std::string)outputfilename + ".txt", obsYield, obsYieldB, obsYieldC, obsYieldD, sigYield, sigYieldB, sigYieldC, sigYieldD, legends_signal[0], &bkgYield[0], &bkgYieldB[0], &bkgYieldC[0], &bkgYieldD[0], files_bkg.size(), &legends_bkg[0], systUnc, nSyst, &systNames[0], &systDist[0], shapeCard, shapeFileName, quadBFileName, quadCFileName, quadDFileName, autoMCStats);
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
        std::cout << "   add shape for " << bkgNames[i] << std::endl;
        hists_bkg[i]->Write(bkgNames[i].c_str());
        if(hists_bkg_sys.size() > 0){
            for(unsigned j = 0; j < hists_bkg_sys[i].size(); j++){
                std::cout << "   add shape for " << bkgNames_sys[i][j] << std::endl;
                hists_bkg_sys[i][j]->Write(bkgNames_sys[i][j].c_str());
            }
        }
    }
    for(unsigned i = 0; i < hist_signal_sys.size(); i++){
        hist_signal_sys[i]->Write(sigName_sys[i].c_str());
    }

    shapeSR_file->Close();

}

void checkfornans(std::vector<std::string>& sigName_sys, std::vector<std::vector<std::string>>& bkgNames_sys, std::vector<TH1F*> hist_signal_sys, std::vector<std::vector<TH1F*>> hists_bkg_sys)
{
    for(unsigned i = 0; i < hist_signal_sys.size(); i++){
        for(int ibin = 1; ibin <= hist_signal_sys[i]->GetNbinsX(); ibin++){
            if(TMath::IsNaN(hist_signal_sys[i]->GetBinContent(ibin))){
                std::cout << "violation: NaN found in hist " << sigName_sys[i] << " bin nr. " << ibin << std::endl;
            }
        }
    }
    for(unsigned i = 0; i < hists_bkg_sys.size(); i++){
        for(unsigned j = 0; j < hists_bkg_sys[i].size(); j++){
            for(int ibin = 1; ibin <= hists_bkg_sys[i][j]->GetNbinsX(); ibin++){
                if(TMath::IsNaN(hists_bkg_sys[i][j]->GetBinContent(ibin))){
                    std::cout << "violation: NaN found in hist " << bkgNames_sys[i][j] << " bin nr. " << ibin << std::endl;
                }
            }
        }
    }
}

void plotSysEffects(TString plotname, TH1F* hist_signal, std::vector<TH1F*> hist_signal_sys, const std::vector<std::string>& sigName_sys)
{
    bool is2016 = plotname.Contains("2016");
    bool is2017 = plotname.Contains("2017") or plotname.Contains("1718");
    bool is2018 = plotname.Contains("2018") or plotname.Contains("1718");
    bool isRun2 = plotname.Contains("Run2");

    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    // Make the pad that will contain the plot
    TPad* pad  = new TPad("pad", "", 0., 0., 1., 1.);
    pad->Clear();
    pad->Draw();
    pad->cd();

    std::vector<std::vector<int>> rgb = {{46, 114, 204}, {239, 32, 29}, {29, 182, 0}, {86, 14, 118}, {232, 164, 0}, {86, 22, 67}, {247, 135, 100}, {47, 41, 35}};
    std::vector<int> colors;
    for(int i = 0; i < rgb.size(); i++){
        colors.push_back(TColor::GetColor(rgb[i][0], rgb[i][1], rgb[i][2]));
    }

    TLegend legend = TLegend(0.18, 0.84, 0.95, 0.93);
    legend.SetNColumns(2);
    legend.SetFillStyle(0);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad, is2016, is2017, is2018, isRun2);
    Shape_SR_plottext* shapeSR_text = new Shape_SR_plottext(pad);

    std::cout << "calculating relative systematic effects" << std::endl;
    TMultiGraph* hists = new TMultiGraph();
    int icount = 0;
    for(unsigned i = 0; i < hist_signal_sys.size(); i++){
        if(sigName_sys[i].find("JEC") == std::string::npos and sigName_sys[i].find("JER") == std::string::npos) continue;
        //if(sigName_sys[i].find("Trigger") == std::string::npos) continue;
        TH1F* hist_rel = (TH1F*)hist_signal->Clone((TString)sigName_sys[i]);
        TH1F* hist_rel_sys = (TH1F*)hist_signal_sys[i]->Clone((TString)sigName_sys[i] + "sys");
        std::cout << "+ " << sigName_sys[i] << ": " << hist_rel << " " << hist_rel_sys << std::endl;
        TGraphAsymmErrors* graph = new TGraphAsymmErrors(hist_rel_sys, hist_rel, "pois");
        graph->SetLineColor(colors[icount]);
        graph->SetMarkerColor(colors[icount]);
        hists->Add(graph);
        icount++;
        TString legendname = sigName_sys[i];
        legendname.ReplaceAll("HNL_", "");
        legend.AddEntry(graph, legendname, "l");
    }

    hists->Draw("AP");
    //hists->SetMaximum(1.15);
    //hists->SetMinimum(0.9);
    //hists->GetXaxis()->SetRangeUser(0,12);
    legend.Draw("same");
    CMSandLumi->add_flavor(plotname);
    CMSandLumi->Draw();
    shapeSR_text->Draw(plotname);

    pad->Modified();
    c->Print(plotname);
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


//Function to print dataCard to be analysed by CMS combination tool in ABCD format
void printABCDDataCard(const std::string& cardName, const double obsYieldA, const double obsYieldB, const double obsYieldC, const double obsYieldD, const double sigYieldA, const double sigYieldB, const double sigYieldC, const double sigYieldD, const std::string& sigName, const double* bkgYieldA, const double* bkgYieldB, const double* bkgYieldC, const double* bkgYieldD, const unsigned nBkg, const std::string* bkgNames, const std::vector<std::vector<double> >& systUnc, const unsigned nSyst, const std::string* systNames, const std::string* systDist, const bool shapeCard, const std::string& shapeFileNameA, const std::string& shapeFileNameB, const std::string& shapeFileNameC, const std::string& shapeFileNameD, const bool autoMCStats ){
    std::cout << "Datacard in " << cardName << std::endl;

    //stream for writing card
    std::ofstream card;

    //add .txt to name if no file extension is given
    card.open(cardName + ((cardName.find(".") == std::string::npos) ? ".txt" : "") ); //add .txt to name if no file extension is given

    //define number of channels, background sources and systematics
    card << "imax 4 number of channels \n";
    card << "jmax " << nBkg << " number of backgrounds \n";
    card << "kmax " << nSyst << " number of nuisance parameters (sources of systematical uncertainties) \n";
    card << "---------------------------------------------------------------------------------------- \n";

    //define the channels and the number of observed events
    card << "bin chA chB chC chD \n";
    card << "observation " << obsYieldA << " " << obsYieldB << " " << obsYieldC << " " << obsYieldD << "\n";

    //define all backgrounds and their yields
    card << "---------------------------------------------------------------------------------------- \n";
    if(shapeCard){
        card << "shapes * chA " << shapeFileNameA + " $PROCESS $PROCESS_$SYSTEMATIC\n";
        card << "shapes * chB " << shapeFileNameB + " $PROCESS $PROCESS_$SYSTEMATIC\n";
        card << "shapes * chC " << shapeFileNameC + " $PROCESS $PROCESS_$SYSTEMATIC\n";
        card << "shapes * chD " << shapeFileNameD + " $PROCESS $PROCESS_$SYSTEMATIC\n";
        card << "---------------------------------------------------------------------------------------- \n";
    }
    card << "bin    ";
    for(unsigned proc = 0; proc < nBkg + 1; ++proc){
        card << "   " << "chA";
    }
    for(unsigned proc = 0; proc < nBkg + 1; ++proc){
        card << "   " << "chB";
    }
    for(unsigned proc = 0; proc < nBkg + 1; ++proc){
        card << "   " << "chC";
    }
    for(unsigned proc = 0; proc < nBkg + 1; ++proc){
        card << "   " << "chD";
    }
    card << "\n";
    card << "process";
    for(unsigned ABCDcounter = 0; ABCDcounter < 4; ++ABCDcounter){
        card << "   " << sigName;
        for(unsigned bkg = 0; bkg < nBkg; ++bkg){
            card << "   " << bkgNames[bkg];
        }
    }
    card << "\n";
    card << "process";
    for(unsigned ABCDcounter = 0; ABCDcounter < 4; ++ABCDcounter){
        for(unsigned bkg = 0; bkg < nBkg + 1; ++bkg){
            card << "   " << bkg;
        }
    }
    card << "\n";
    card << "rate";
    card << "   " << sigYieldA;
    for(unsigned bkg = 0; bkg < nBkg; ++bkg){
        if(bkgYieldA[bkg] <= 0) card << "    " << "0.00";
        else card << "  " << bkgYieldA[bkg];
    }
    card << "   " << sigYieldB;
    for(unsigned bkg = 0; bkg < nBkg; ++bkg){
        if(bkgYieldB[bkg] <= 0) card << "    " << "0.00";
        else card << "  " << bkgYieldB[bkg];
    }
    card << "   " << sigYieldC;
    for(unsigned bkg = 0; bkg < nBkg; ++bkg){
        if(bkgYieldC[bkg] <= 0) card << "    " << "0.00";
        else card << "  " << bkgYieldC[bkg];
    }
    card << "   " << sigYieldD;
    for(unsigned bkg = 0; bkg < nBkg; ++bkg){
        if(bkgYieldD[bkg] <= 0) card << "    " << "0.00";
        else card << "  " << bkgYieldD[bkg];
    }
    card << "\n";
    card << "---------------------------------------------------------------------------------------- \n";
    card << "alpha rateParam chA ABCD (@0*@1/@2) beta,gamma,delta\n";
    card << "beta  rateParam chB ABCD 1.\n";
    card << "gamma rateParam chC ABCD 1.\n";
    card << "delta rateParam chD ABCD 1.\n";
    card << "---------------------------------------------------------------------------------------- \n";


    //define sources of systematic uncertainty, what distibution they follow and how large their effect is
    if( nSyst != 0 ){
        for(unsigned syst = 0; syst < nSyst; ++syst){
            card << systNames[syst] << " " << systDist[syst];
            for(unsigned proc = 0; proc < nBkg + 1; ++proc){
                card << " ";
                if(systUnc[syst][proc] == 0) card << "-";
                else card << systUnc[syst][proc];
            }
            card << " - - - - - - ";
            card << "\n";
        }
    }

    //add line to automatically include statistical uncertainties from the MC shape histograms 
    if( autoMCStats ){
        card << "* autoMCStats 10\n";
    }

    card.close();
}


void set_UpAndDown_correctly(TH1F* nominal, TH1F* up, TH1F* down)
{
    for(int i = 1; i <= nominal->GetNbinsX(); i++){
        double bc_sysDown = down->GetBinContent(i);
        double bc_sysUp = up->GetBinContent(i);
        double bc_nominal = nominal->GetBinContent(i);
        double bc_sysUp_max = std::max(std::max(bc_sysUp, bc_sysDown), bc_nominal);
        double bc_sysDown_min = std::min(std::min(bc_sysUp, bc_sysDown), bc_nominal);
        down->SetBinContent(i, bc_sysDown_min);
        up->SetBinContent(i, bc_sysUp_max);
    }
}
