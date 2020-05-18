#include "sensitivity_estimator.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    // set general plot style
    setTDRStyle();
    gROOT->ForceStyle();

    // Argument 1: specific directory for plots (related to x in dilep_x.root or specific set of plots)
    // Argement 2 - (n+1)/2: name of root input files -> separate them between HNL and background based on filename
    // Argument (n+3)/2 - n: legends associated to samples
    int i_rootfiles = 2;
    int i_legends   = argc/2 + 1;

    std::vector<TFile*>  files_signal;
    std::vector<TFile*>  files_bkg;
    std::vector<TFile*>  files_data;
    for(int i = i_rootfiles; i < i_legends; i++){
        TString filename = (TString)argv[i];
        if(filename.Index("_HeavyNeutrino_lljj_") != -1) files_signal.push_back(TFile::Open(filename));
        else if(filename.Index("_Run201") != -1) files_data.push_back(TFile::Open(filename));
        else files_bkg.push_back(TFile::Open(filename));
    }
    std::vector<TString> legends_signal;
    std::vector<TString> legends_bkg;
    std::vector<TString> legends_data;
    for(int i = i_legends; i < argc; i++){
        TString legendname = (TString)argv[i];
        if(legendname.Index("HNL") != -1) legends_signal.push_back(adjust_legend(legendname));
        else if(legendname.Index("201") != -1 or legendname.Index("Data") != -1 or legendname.Index("data") != -1) legends_data.push_back(adjust_legend(legendname));
        else legends_bkg.push_back(adjust_legend(legendname));
    }

    // determine whether the samplelist wants plotting with data, signal or without
    bool withsignal = (files_signal.size() > 0);
    bool withdata = false;
    if(files_data.size() == 1){
        std::cout << "Making plots with data" << std::endl;
        withdata = true;
    } else if(files_data.size() > 1){ 
        std::cout << "Error: giving more than one data file!" << std::endl; 
        return 1; 
    } else {
        std::cout << "Making plots without data" << std::endl;
    }


    // Name of directory where plots will end up
    TString specific_dir = (TString)argv[1];
    std::cout << specific_dir << std::endl;
    TString general_pathname = make_general_pathname("plots/stacks/", specific_dir + "/");

    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    // Make the pad that will contain the plot
    double ymin = 0.33 * withdata;
    TPad* pad_histo  = new TPad("pad_histo", "", 0., ymin, 1., 1.);
    if(withdata){ 
        pad_histo->SetTopMargin(0.07);
        pad_histo->SetBottomMargin(0.);
    }
    pad_histo->Draw();
    pad_histo->cd();

    TLegend legend = get_legend(0.2, 0.80, 0.95, 0.91, 3);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    TString CMStext   = "#bf{CMS} #scale[0.8]{#it{Preliminary}}";
    TString lumitext  = "35.9 fb^{-1} (13 TeV)";
    float leftmargin  = pad_histo->GetLeftMargin();
    float topmargin   = pad_histo->GetTopMargin();
    float rightmargin = pad_histo->GetRightMargin();
    TLatex CMSlatex  = get_latex(0.8*topmargin, 11, 42);
    TLatex lumilatex = get_latex(0.6*topmargin, 31, 42);

    // Make the pad that will contain the ratio data/MC
    c->cd(); // first return to canvas so that second pad will be drawn in here and not in pad_histo
    TPad* pad_ratio = new TPad("pad_ratio", "", 0., 0., 1.,std::max(0.05, ymin));
    if(withdata){
        pad_ratio->SetBottomMargin(0.3);
        pad_ratio->Draw();
        pad_ratio->cd();
    }


    // loop for signal region selection optimization
    TIter next(files_bkg.back()->GetListOfKeys()); //last file in the list is the largest bkg
    TKey* key;

    double SigSum[3][2][4][10];
    double BkgSum[3][2][4][10];
    double SoverB[3][4][10];
    double SoverBplusS[3][4][10];
    TString SoverBname[3][4][10];
    TString SoverBplusSname[3][4][10];
    for(int i_mass = 0; i_mass < 3; i_mass++){
        for(int i = 0; i < 4; i++){
            for(int i2 = 0; i2 < 10; i2++){
                SigSum[i_mass][0][i][i2] = 0.;
                BkgSum[i_mass][0][i][i2] = 0.;
                SigSum[i_mass][1][i][i2] = 0.;
                BkgSum[i_mass][1][i][i2] = 0.;
                SoverB[i_mass][i][i2] = 0.;
                SoverBplusS[i_mass][i][i2] = 0.;
                SoverBname[i_mass][i][i2] = "";
                SoverBplusSname[i_mass][i][i2] = "";
            }
        }
    }
    TString sigreg[4] = {"_OS_mu", "_SS_mu", "_OS_e", "_SS_e"};

    while(key = (TKey*)next()){
        TClass *cl = gROOT->GetClass(key->GetClassName());
        if (cl->InheritsFrom("TH1") and ! cl->InheritsFrom("TH2")){ // second requirement is because TH2 also inherits from TH1
            // Get a reference histogram for the name, then get all histograms in  a vector
            TH1F*   sample_hist_ref = (TH1F*)key->ReadObj();
            TString histname   = sample_hist_ref->GetName();


            if(histname.Index("Bool") == -1) continue;


            std::vector<TH1F*> data_hists;
            std::vector<TH1F*> bkg_hists;
            std::vector<TH1F*> signal_hists;

            for(int i = 0; i < files_data.size(); i++){
                data_hists.push_back((TH1F*)files_data[i]->Get(histname));
            }
            for(int i = 0; i < files_bkg.size(); i++){
                bkg_hists.push_back((TH1F*)files_bkg[i]->Get(histname));
            }
            for(int i = 0; i < files_signal.size(); i++){
                signal_hists.push_back((TH1F*)files_signal[i]->Get(histname));
            }

            double bkg_sum = 0.;
            double sig_sum[3] = {0., 0., 0.};

            std::cout << "------- " << histname << " -------" << std::endl;
            for(int i = 0; i < bkg_hists.size(); i++){
                std::cout << legends_bkg[i] << ":  " << bkg_hists[i]->GetBinContent(1) << " +- " << bkg_hists[i]->GetBinError(1) << std::endl;
                bkg_sum += bkg_hists[i]->GetBinContent(1);
            }
            for(int i = 0; i < signal_hists.size(); i++){
                std::cout << legends_signal[i] << ":  " << signal_hists[i]->GetBinContent(1) << " +- " << signal_hists[i]->GetBinError(1) << std::endl;
                sig_sum[i] = signal_hists[i]->GetBinContent(1);
            }
            for(int i = 0; i < data_hists.size(); i++){
                std::cout << legends_data[i] << ":  " << data_hists[i]->GetBinContent(1) << " +- " << data_hists[i]->GetBinError(1) << std::endl;
            }
            double SoverBtmp[3] = {sig_sum[0]/sqrt(bkg_sum), sig_sum[1]/sqrt(bkg_sum), sig_sum[2]/sqrt(bkg_sum)};
            double SoverBplusStmp[3] = {sig_sum[0]/sqrt(bkg_sum + sig_sum[0]), sig_sum[1]/sqrt(bkg_sum + sig_sum[1]), sig_sum[2]/sqrt(bkg_sum + sig_sum[2])};

            int sigreg_i;
            if(histname.Index("_OS_mu") != -1) sigreg_i = 0;
            if(histname.Index("_SS_mu") != -1) sigreg_i = 1;
            if(histname.Index("_OS_e") != -1) sigreg_i = 2;
            if(histname.Index("_SS_e") != -1) sigreg_i = 3;
            for(int i_mass = 0; i_mass < 3; i_mass++){
                for(int i = 0; i < 10; i++){
                    if(SoverBtmp[i_mass] > SoverB[i_mass][sigreg_i][i]){
                        SigSum[i_mass][0][sigreg_i][i] = sig_sum[i_mass];
                        BkgSum[i_mass][0][sigreg_i][i] = bkg_sum;
                        SoverB[i_mass][sigreg_i][i] = SoverBtmp[i_mass];
                        SoverBname[i_mass][sigreg_i][i] = histname;
                        break;
                    }
                }
                for(int i = 0; i < 10; i++){
                    if(SoverBplusStmp[i_mass] > SoverBplusS[i_mass][sigreg_i][i]){
                        SigSum[i_mass][1][sigreg_i][i] = sig_sum[i_mass];
                        BkgSum[i_mass][1][sigreg_i][i] = bkg_sum;
                        SoverBplusS[i_mass][sigreg_i][i] = SoverBplusStmp[i_mass];
                        SoverBplusSname[i_mass][sigreg_i][i] = histname;
                        break;
                    }
                }
            }
        }
    }
    std::cout << "------- best discriminators -------" << std::endl;
    for(int sigreg_i = 0; sigreg_i < 4; sigreg_i++){
        std::cout << sigreg[sigreg_i] << std::endl;
        for(int i_mass = 0; i_mass < 3; i_mass++){
            std::cout << (i_mass == 0? "3 GeV" : (i_mass == 1? "5 GeV" : "8 GeV")) << std::endl;
            std::cout << "S over sqrt(B)" << std::endl;
            for(int i = 0; i < 10; i++){
                std::cout << SoverB[i_mass][sigreg_i][i] << " for " << SoverBname[i_mass][sigreg_i][i] << " (" << SigSum[i_mass][0][sigreg_i][i] << " Sig, " << BkgSum[i_mass][0][sigreg_i][i] << " Bkg)" << std::endl;
            }
            std::cout << "S over sqrt(B+S)" << std::endl;
            for(int i = 0; i < 10; i++){
                std::cout << SoverBplusS[i_mass][sigreg_i][i] << " for " << SoverBplusSname[i_mass][sigreg_i][i] << " (" << SigSum[i_mass][1][sigreg_i][i] << " Sig, " << BkgSum[i_mass][1][sigreg_i][i] << " Bkg)" << std::endl;
            }
        }
    }
}
# endif
