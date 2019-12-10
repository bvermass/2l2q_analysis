#include "roccurveplotter.h"

TGraph* get_roc(std::vector< double > eff_signal, std::vector< double > eff_bkg, TString legend)
{
    TGraph* roc = new TGraph(eff_signal.size(), &(eff_bkg[0]), &(eff_signal[0]));
    roc->SetLineColor(get_color(legend));
    roc->SetLineWidth(2);
    return roc;
}


bool plot_PFNvsBDT(TCanvas* c, TMultiGraph* multigraph, TLegend* legend, TString histname, std::vector<TFile*> files_signal, std::vector<TFile*> files_bkg, std::vector<TString> legends)
{
    // This function adds the corresponding BDT roc curve to the existing multigraph that has the PFN version already
    c->Clear();
    histname.ReplaceAll("PFN", "BDT");

    std::vector< double > auc;
    for(int i = 0; i < files_signal.size(); i++){
        TH1F* hist_signal = (TH1F*) files_signal[i]->Get(histname);
        TH1F* hist_bkg    = (TH1F*) files_bkg[i]->Get(histname);
        if(!hist_signal or !hist_bkg) return false;

        std::vector< double > eff_signal = computeEfficiencyForROC(hist_signal);
        std::vector< double > eff_bkg    = computeEfficiencyForROC(hist_bkg);
        TGraph* roc = get_roc(eff_signal, eff_bkg, "3GeV");
        multigraph->Add(roc);
        auc.push_back(computeAUC(roc));
        TString auc_str = std::to_string(auc[i]).substr(0, std::to_string(auc[i]).find(".") + 3);
        legend->AddEntry(roc, legends[i] + "(BDT): " + auc_str, "l");
    }

    multigraph->Draw("AL");
    legend->Draw("same");

    return true;
}


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
    TString general_pathname = make_general_pathname("plots/roccurves/", specific_dir + "/");

    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    TLegend legend = get_legend(0.6, 0.15, 1, 0.3, 1);

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
        TClass *cl = gROOT->GetClass(key->GetClassName());

        // -- TH1 --
        if (cl->InheritsFrom("TH1") and ! cl->InheritsFrom("TH2")){ // second requirement is because TH2 also inherits from TH1
            
            // Get a reference histogram for the name, then get all histograms in  a vector
            TH1F*   sample_hist_ref = (TH1F*)key->ReadObj();
            TString histname   = sample_hist_ref->GetName();
            if(histname.Index("_ROC") == -1) continue;
            std::cout << histname << std::endl;
            
            // get plot specific pathnames
            TString pathname_lin    = make_plotspecific_pathname(histname, general_pathname, "lin/");
            TString pathname_log    = make_plotspecific_pathname(histname, general_pathname, "log/");

            TMultiGraph* multigraph = new TMultiGraph();
            std::vector< double > auc;
            multigraph->SetTitle((TString)";Bkg Eff.;Signal Eff.");
            for(int i = 0; i < files_signal.size(); i++){
                //auc.push_back(get_roc_and_auc(multigraph, histname, files_signal[i], files_bkg[i]);
                TH1F* hist_signal = (TH1F*) files_signal[i]->Get(histname);
                TH1F* hist_bkg    = (TH1F*) files_bkg[i]->Get(histname);
                if(hist_signal->GetMaximum() <= 0 or hist_bkg->GetMaximum() <= 0) continue;

                
                std::vector< double > eff_signal = computeEfficiencyForROC(hist_signal);
                std::vector< double > eff_bkg    = computeEfficiencyForROC(hist_bkg);

                // calculate cutting point to get 75% signal efficiency for PFN or BDT
                if(histname.Index("PFN") != -1 or histname.Index("BDT") != -1) computeCuttingPoint(eff_signal, eff_bkg, hist_signal, hist_bkg, 0.75);

                TGraph* roc = get_roc(eff_signal, eff_bkg, legends[i]);
                multigraph->Add(roc);
                auc.push_back(computeAUC(roc));
                TString auc_str = std::to_string(auc[i]).substr(0, std::to_string(auc[i]).find(".") + 3);
                legend.AddEntry(roc, legends[i] + ": " + auc_str, "l");
            }

            c->Clear();
            c->SetLogx(0);
            c->SetLogy(0);
            multigraph->Draw("AL");
            legend.Draw("same");
            CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);

            c->Modified();
            c->Print(pathname_lin + histname + ".pdf");

            // Plot PFN vs BDT
            //if(histname.Index("PFN") != -1){ 
            //    if(plot_PFNvsBDT(c, multigraph, &legend, histname, files_signal, files_bkg, legends)){
            //        CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);

            //        histname.ReplaceAll("PFN", "PFNvsBDT");
            //        c->Modified();
            //        c->Print(pathname_lin + histname + ".pdf");

            //        multigraph->GetXaxis()->SetRangeUser(0., 0.1);
            //        multigraph->GetYaxis()->SetRangeUser(0.7, 1.);

            //        c->Modified();
            //        c->Print(pathname_lin + histname + "_zoom.pdf");

            //        c->SetLogx(1);
            //        c->Modified();
            //        c->Print(pathname_log + histname + "_zoom.pdf");
            //    }
            //}
        }
    }
}
#endif
