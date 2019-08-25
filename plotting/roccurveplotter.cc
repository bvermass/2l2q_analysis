#include "roccurveplotter.h"

#ifndef __CINT__
int main(int argc, char * argv[])
{
    // set general plot style
    setTDRStyle();
    gROOT->ForceStyle();
    
    // Argument 1: specific directory for plots
    // Argument 2: legend of first
    // Argement 2: name of signal input file  
    // Argument 3: name of bkg input file
    // Argument 4, 5, 6 onwards, do same again
    
    std::vector<TFile*> files_signal;
    std::vector<TFile*> files_bkg;
    std::vector<TString> legends;
    for(int i = 2; i < argc; i++){
        std::cout << argv[i] << std::endl;
        TString argument = (TString)argv[i];
        if(i%3 == 2) legends.push_back(argument);
        else if(i%3 == 0) files_signal.push_back(TFile::Open(argument));
        else if(i%3 == 1) files_bkg.push_back(TFile::Open(argument));
    }

    // Name of directory where plots will end up
    TString specific_dir = (TString)argv[1];
    std::cout << specific_dir << std::endl;
    TString general_pathname = make_general_pathname("roccurves/", specific_dir + "/");

    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    TLegend legend = get_legend(0.7, 0.15, 1, 0.35, 1);
    TLegend legend_log = get_legend(0.4, 0.05, 0.2, 0.91, 3);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    TString CMStext   = "#bf{CMS} #scale[0.8]{#it{Preliminary}}";
    TString lumitext  = "21.1 fb^{-1} (13 TeV)";
    float leftmargin  = c->GetLeftMargin();
    float topmargin   = c->GetTopMargin();
    float rightmargin = c->GetRightMargin();
    TLatex CMSlatex  = get_latex(0.8*topmargin, 11, 42);
    TLatex lumilatex = get_latex(0.6*topmargin, 31, 42);

    TIter next(files_bkg.front()->GetListOfKeys()); //doesn't really matter if we take bkg or signal
    TKey* key;
    while(key = (TKey*)next()){
        legend.Clear();
        legend_log.Clear();
        TClass *cl = gROOT->GetClass(key->GetClassName());

        // -- TH1 --
        if (cl->InheritsFrom("TH1") and ! cl->InheritsFrom("TH2")){ // second requirement is because TH2 also inherits from TH1
            
            // Get a reference histogram for the name, then get all histograms in  a vector
            TH1F*   sample_hist_ref = (TH1F*)key->ReadObj();
            TString histname   = sample_hist_ref->GetName();
            if(histname.Index("_ROC") == -1) continue;
            
            // get plot specific pathnames
            TString pathname_lin    = make_plotspecific_pathname(histname, general_pathname, "lin/");
            TString pathname_log    = make_plotspecific_pathname(histname, general_pathname, "log/");

            TMultiGraph* multigraph = new TMultiGraph();
            TMultiGraph* multigraph_log = new TMultiGraph();
            std::vector< double > auc;
            multigraph->SetTitle((TString)";Signal Eff.;Bkg Eff.");
            for(int i = 0; i < files_signal.size(); i++){
                TH1F* hist_signal = (TH1F*) files_signal[i]->Get(histname);
                TH1F* hist_bkg    = (TH1F*) files_bkg[i]->Get(histname);

                
                std::vector< double > eff_signal = computeEfficiencyForROC(hist_signal);
                std::vector< double > eff_bkg    = computeEfficiencyForROC(hist_bkg);

                std::vector< double > eff_signal_log;
                std::vector< double > eff_bkg_log;
                for(int j = 0; j < eff_signal.size(); j++){
                    if(eff_signal[j] > 0.01 and eff_bkg[j] > 0.01){
                        eff_signal_log.push_back(eff_signal[j]);
                        eff_bkg_log.push_back(eff_bkg[j]);
                    }
                }

                TGraph* roc = new TGraph(eff_signal.size(), &(eff_signal[0]), &(eff_bkg[0]));
                roc->SetLineColor(get_color(legends[i]));
                roc->SetLineWidth(2);
                multigraph->Add(roc);
                auc.push_back(computeAUC(roc));
                TString auc_str = std::to_string(auc[i]).substr(0, std::to_string(auc[i]).find(".") + 3);
                legend.AddEntry(roc, legends[i] + ": " + auc_str, "l");

                TGraph* roc_log = new TGraph(eff_signal_log.size(), &(eff_signal_log[0]), &(eff_bkg_log[0]));
                roc_log->SetLineColor(get_color(legends[i]));
                roc_log->SetLineWidth(2);
                multigraph_log->Add(roc_log);
                legend_log.AddEntry(roc_log, legends[i], "l");
            }

            c->Clear();
            c->SetLogx(0);
            c->SetLogy(0);
            multigraph->Draw("AL");
            legend.Draw("same");
            CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);

            c->Modified();
            c->Print(pathname_lin + histname + ".pdf");

            // log version
            //c->Clear();
            //c->SetLogx(1);
            //c->SetLogy(1);
            //multigraph_log->Draw("AL");
            //legend_log.Draw("same");
            //CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);

            //c->Modified();
            //c->Print(pathname_log + histname + ".pdf");
        }
    }
}
#endif
