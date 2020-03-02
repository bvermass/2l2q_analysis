#include "singlehistplotter.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    // set general plot style
    setTDRStyle();
    gROOT->ForceStyle();
    int color = TColor::GetColor(66, 129, 174);

    // Argument 1: name of root input file
    // Argument 2: legend associated to sample
    TString inputfilename = (TString)argv[1];
    TFile*  sample_file   = TFile::Open(inputfilename);
    TString sample_legend = adjust_legend((TString)argv[2]);

    // Name of directory where plots will end up
    TString general_pathname = make_general_pathname("plots/singlehists/", inputfilename);

    // Read identifiers from plotting/identifiers.txt and only make plots matching these tags
    std::vector<std::vector<TString>> identifiers = get_identifiers("plotting/identifiers.txt", ",");

    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    // Make the pad that will contain the plot
    TPad* pad  = new TPad("pad", "", 0., 0., 1., 1.);
    pad->Draw();
    pad->cd();

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    TString CMStext   = "#bf{CMS} #scale[0.8]{#it{Preliminary}}";
    TString lumitext  = "21.1 fb^{-1} (13 TeV)";
    float leftmargin  = pad->GetLeftMargin();
    float topmargin   = pad->GetTopMargin();
    float rightmargin = pad->GetRightMargin();
    TLatex CMSlatex  = get_latex(0.8*topmargin, 11, 42);
    TLatex lumilatex = get_latex(0.6*topmargin, 31, 42);

    TIter next(sample_file->GetListOfKeys());
    TKey* key;
    while(key = (TKey*)next()){

        TClass *cl = gROOT->GetClass(key->GetClassName());

        // -- TH1 --
        if (cl->InheritsFrom("TH1") and ! cl->InheritsFrom("TH2")){ // second requirement is because TH2 also inherits from TH1
            TH1F*   sample_hist = (TH1F*)key->ReadObj();
            TString histname   = sample_hist->GetName();

            if(histname.Index("_Bool_") != -1) continue; // don't plot the Bool histograms
            if(sample_hist->GetMaximum() == 0) continue;
            if(!check_identifiers(histname, identifiers)) continue;

            TString pathname_lin    = make_plotspecific_pathname(histname, general_pathname, "lin/");
            TString pathname_log    = make_plotspecific_pathname(histname, general_pathname, "log/");

            // set x range to log if necessary
            int xlog = (histname.Index("xlog") == -1)? 0 : 1;
            pad->SetLogx(xlog);
            if(xlog) divide_by_binwidth(sample_hist);
            sample_hist->GetYaxis()->SetRangeUser(0, 1.25*sample_hist->GetMaximum());

            TLegend legend = get_legend(0.2, 0.88, 0.95, 0.93, 4);
            legend.AddEntry(sample_hist, sample_legend);
    
            sample_hist->SetMarkerColor(color);
            sample_hist->SetLineColor(color);
            sample_hist->Draw("E0 X0 P");
            legend.Draw("same");
            CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);
            lumilatex.DrawLatex(1-rightmargin, 1-0.8*topmargin, lumitext);
            //drawLumi(pad);

            pad->Modified();
            c->Print(pathname_lin + histname + ".png");

            // Efficiencies are calculated right here as TGraphAsymmErrors
            if(histname.Index("eff_num") != -1){
                TGraphAsymmErrors* efficiency_graph = new TGraphAsymmErrors((TH1F*)sample_hist, (TH1F*)sample_file->Get(histname(0, histname.Index("eff_num") + 4) + "den"), "cp");
                efficiency_graph->GetXaxis()->SetTitle(sample_hist->GetXaxis()->GetTitle());
                efficiency_graph->SetLineWidth(2);
                efficiency_graph->GetYaxis()->SetTitle("Eff.");
                efficiency_graph->GetHistogram()->SetMinimum(0.);
                efficiency_graph->GetHistogram()->SetMaximum((efficiency_graph->GetHistogram()->GetMaximum() > 0.2)? 1.25 : 0.225);

                pad->Clear();
                legend.Clear();

                legend.AddEntry(efficiency_graph, sample_legend);

                efficiency_graph->Draw("AP");
                legend.Draw("same");
                CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);
                lumilatex.DrawLatex(1-rightmargin, 1-0.8*topmargin, lumitext);

                pad->Modified();
                c->Print(pathname_lin + histname(0, histname.Index("eff_num") + 3) + ".png");
            }
        }else if(cl->InheritsFrom("TH2")){
            TH2F *sample_hist = (TH2F*)key->ReadObj();
            TString histname = sample_hist->GetName();
            
            if(sample_hist->GetMaximum() == 0) continue;
            if(!check_identifiers(histname, identifiers)) continue;
            alphanumeric_labels(sample_hist);

            TString pathname_lin = make_plotspecific_pathname(histname, general_pathname, "lin/");

            pad->Clear();

            sample_hist->Draw(get_2D_draw_options(sample_hist));
            CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);
            lumilatex.DrawLatex(1-rightmargin, 1-0.8*topmargin, lumitext);

            pad->Modified();
            c->Print(pathname_lin + histname + ".png");
        }
    }
}
# endif
