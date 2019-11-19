#include "multihistplotter.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    // set general plot style
    setTDRStyle();
    gROOT->ForceStyle();

    // Argument 1: specific directory for plots (related to x in dilep_x.root or specific set of plots)
    // Argement 2 - (n+1)/2: name of root input files
    // Argument (n+3)/2 - n: legends associated to samples
    int i_rootfiles = 2;
    int i_legends   = argc/2 + 1;

    std::vector<TFile*>  files;
    for(int i = i_rootfiles; i < i_legends; i++){
        files.push_back(TFile::Open((TString)argv[i]));
    }
    std::vector<TString> legends;
    for(int i = i_legends; i < argc; i++){
        legends.push_back(adjust_legend((TString)argv[i]));
    }


    // Name of directory where plots will end up
    TString specific_dir = (TString)argv[1];
    TString general_pathname = make_general_pathname("multihists/", specific_dir + "/");

    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    // Make the pad that will contain the plot
    TPad* pad  = new TPad("pad", "", 0., 0., 1., 1.);
    pad->Draw();
    pad->cd();

    TLegend legend = get_legend(0.18, 0.84, 0.95, 0.93, 3);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    TString CMStext   = "#bf{CMS} #scale[0.8]{#it{Preliminary}}";
    TString lumitext  = "35.9 fb^{-1} (13 TeV)";
    float leftmargin  = pad->GetLeftMargin();
    float topmargin   = pad->GetTopMargin();
    float rightmargin = pad->GetRightMargin();
    TLatex CMSlatex  = get_latex(0.8*topmargin, 11, 42);
    TLatex lumilatex = get_latex(0.6*topmargin, 31, 42);

    TIter next(files.front()->GetListOfKeys());
    TKey* key;
    while(key = (TKey*)next()){
        legend.Clear();

        TClass *cl = gROOT->GetClass(key->GetClassName());

        // -- TH1 --
        if (cl->InheritsFrom("TH1") and ! cl->InheritsFrom("TH2")){ // second requirement is because TH2 also inherits from TH1
            
            // Get a reference histogram for the name, then get all histograms in  a vector
            TH1F*   sample_hist_ref = (TH1F*)key->ReadObj();
            TString histname   = sample_hist_ref->GetName();
            std::cout << histname << std::endl;
            
            if(histname.Index("_Bool_") != -1) continue; // don't plot the Bool histograms
            if(sample_hist_ref->GetMaximum() == 0) continue;
            
            THStack* hists = new THStack("stack", "");
            for(int i = 0; i < files.size(); i++){
                TH1* hist = (TH1*)files[i]->Get(histname);
                if(hist->GetMaximum() > 0){
                    hists->Add(hist);
                    legend.AddEntry(hist, legends[i], "l");
                }
            }

            TString pathname_lin    = make_plotspecific_pathname(histname, general_pathname, "lin/");
            TString pathname_log    = make_plotspecific_pathname(histname, general_pathname, "log/");
            
            // set x range to log if necessary
            int xlog = (histname.Index("xlog") == -1)? 0 : 1;
            pad->SetLogx(xlog);
            if(xlog){
                TIter stack_iterator(hists->GetHists());
                TObject* sample_hist = 0;
                while(sample_hist = stack_iterator()){
                    divide_by_binwidth((TH1F*) sample_hist);
                }
            }


            // Draw lin version
            pad->Clear();
            pad->SetLogy(0);

            hists->Draw("PLC hist nostack");
            hists->GetXaxis()->SetTitle(sample_hist_ref->GetXaxis()->GetTitle());
            hists->GetYaxis()->SetTitle(sample_hist_ref->GetYaxis()->GetTitle());
            hists->SetMaximum(1.25*hists->GetMaximum("nostack"));
            legend.Draw("same");
            CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);
            lumilatex.DrawLatex(1-rightmargin, 1-0.8*topmargin, lumitext);
            
            pad->Modified();
            c->Print(pathname_lin + histname + ".pdf");

            // Draw log version
            pad->Clear();
            pad->SetLogy(1);

            hists->Draw("PLC hist nostack");
            hists->GetXaxis()->SetTitle(sample_hist_ref->GetXaxis()->GetTitle());
            hists->GetYaxis()->SetTitle(sample_hist_ref->GetYaxis()->GetTitle());
            hists->SetMaximum(10*hists->GetMaximum("nostack"));
            legend.Draw("same");
            CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);
            lumilatex.DrawLatex(1-rightmargin, 1-0.8*topmargin, lumitext);
            
            pad->Modified();
            c->Print(pathname_log + histname + ".pdf");




            // Calculate and draw efficiencies as TGraphAsymmErrors in a multigraph
            if(histname.Index("eff_num") != -1){
                pad->Clear();
                pad->SetLogy(0);
                legend.Clear();
                
                TMultiGraph* multigraph = new TMultiGraph();
                multigraph->SetTitle((TString)";" + sample_hist_ref->GetXaxis()->GetTitle() + ";Eff.");
                for(int i = 0; i < files.size(); i++){
                    TGraphAsymmErrors* graph = new TGraphAsymmErrors((TH1F*) files[i]->Get(histname), (TH1F*) files[i]->Get(histname(0, histname.Index("eff_num")+4) + "den"), "cp");
                    multigraph->Add(graph);
                    legend.AddEntry(graph, legends[i], "pl");
                }

                multigraph->Draw("AP pmc plc");
                multigraph->SetMinimum(0.);
                multigraph->SetMaximum((multigraph->GetHistogram()->GetMaximum() > 0.2)? 1.25 : 0.225);

                legend.Draw("same");
                CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);
                lumilatex.DrawLatex(1-rightmargin, 1-0.8*topmargin, lumitext);

                pad->Modified();
                c->Print(pathname_lin + histname(0, histname.Index("eff_num") + 3) + ".pdf");
            }
        }
    }
}
# endif
