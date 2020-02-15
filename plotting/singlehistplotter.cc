#include "singlehistplotter.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    // set general plot style
    setTDRStyle();
    gROOT->ForceStyle();

    // Argument 1: name of root input file
    // Argument 2: legend associated to sample
    TString inputfilename = (TString)argv[1];
    TFile*  sample_file   = TFile::Open(inputfilename);
    TString sample_legend = adjust_legend((TString)argv[2]);

    //this color scheme comes from the coolors.co app: https://coolors.co/4281ae-0a5a50-4b4237-d4b483-c1666b
    //maybe this combo is better: https://coolors.co/4281ae-561643-4b4237-d4b483-c1666b?
    std::vector<std::vector<int>> rgb = {{66, 129, 174}, {212, 180, 131}, {193, 102, 107}, {10, 90, 80}, {75, 66, 65}};
    std::vector<int> colors;
    for(int i = 0; i < rgb.size(); i++){
        colors.push_back(TColor::GetColor(rgb[i][0], rgb[i][1], rgb[i][2]));
    }

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

    TLegend legend = get_legend(0.2, 0.88, 0.95, 0.93, 4);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad);

    TIter next(sample_file->GetListOfKeys());
    TKey* key;
    while(key = (TKey*)next()){

        TClass *cl = gROOT->GetClass(key->GetClassName());
        legend.Clear();

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

            legend.AddEntry(sample_hist, sample_legend);

            pad->Clear();
            pad->SetLogy(0);
    
            sample_hist->SetMarkerColor(colors[0]);
            sample_hist->SetLineColor(colors[0]);
            sample_hist->Draw("E0 P");
            legend.Draw("same");
            CMSandLumi->Draw();

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
                CMSandLumi->Draw();

                pad->Modified();
                c->Print(pathname_lin + histname(0, histname.Index("eff_num") + 3) + ".png");
            }

            // Mini analyzer specific plots
            if(inputfilename.Contains("hists_mini_analyzer")){
                plot_normalized_hists(sample_file, general_pathname, sample_hist, histname, c, pad, legend, colors, CMSandLumi, {"_quadAB_", "_quadCD_"}, {"AR+SR", "MR"}, "_quadAB-CD_");
                plot_normalized_hists(sample_file, general_pathname, sample_hist, histname, c, pad, legend, colors, CMSandLumi, {"_DtoCwithCD_", "_quadC_"}, {"MC", "ABCD pred."}, "_quadCwithDtoC_");
                plot_normalized_hists(sample_file, general_pathname, sample_hist, histname, c, pad, legend, colors, CMSandLumi, {"_BtoAwithCD_", "_quadA_"}, {"MC", "ABCD pred."}, "_quadAwithDtoC_");
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
            CMSandLumi->Draw();

            pad->Modified();
            c->Print(pathname_lin + histname + ".png");
        }
    }
}
# endif

void plot_normalized_hists(TFile* sample_file, TString general_pathname, TH1F* sample_hist, TString histname, TCanvas* c, TPad* pad, TLegend legend, std::vector<int> colors, CMSandLuminosity* CMSandLumi, std::vector<TString> tags, std::vector<TString> legend_tags, TString plot_tag)
{
    if(histname.Contains(tags[0])){
        legend.Clear();

        THStack* hists = new THStack("stack", "");

        hists->Add(sample_hist);
        sample_hist->Scale(1./sample_hist->Integral());
        legend.AddEntry(sample_hist, legend_tags[0], "l");

        for(int i = 1; i < tags.size(); i++){
            TString histname_extra = histname;
            histname_extra.ReplaceAll(tags[0], tags[i]);
            TH1* hist_extra = (TH1*)sample_file->Get(histname_extra);
            hist_extra->SetMarkerColor(colors[i]);
            hist_extra->SetLineColor(colors[i]);
            hists->Add(hist_extra);
            legend.AddEntry(hist_extra, legend_tags[i], "l");
            hist_extra->Scale(1./hist_extra->Integral());
        }

        TString plotname = histname;
        plotname.ReplaceAll(tags[0], plot_tag);
        TString pathname_lin    = make_plotspecific_pathname(plotname, general_pathname, "lin/");
        TString pathname_log    = make_plotspecific_pathname(plotname, general_pathname, "log/");

        pad->Clear();
        pad->SetLogy(0);

        hists->Draw("E P hist nostack");
        hists->GetXaxis()->SetTitle(sample_hist->GetXaxis()->GetTitle());
        hists->GetYaxis()->SetTitle(sample_hist->GetYaxis()->GetTitle());
        hists->SetMaximum(1.25*hists->GetMaximum("nostack"));
        hists->SetMinimum(0);
        legend.Draw("same");
        CMSandLumi->Draw();

        pad->Modified();
        c->Print(pathname_lin + plotname + ".png");

        // Draw log version
        pad->Clear();
        pad->SetLogy(1);

        hists->Draw("E P hist nostack");
        hists->GetXaxis()->SetTitle(sample_hist->GetXaxis()->GetTitle());
        hists->GetYaxis()->SetTitle(sample_hist->GetYaxis()->GetTitle());
        hists->SetMaximum(10*hists->GetMaximum("nostack"));
        hists->SetMinimum(std::max(1e-6, 0.5*hists->GetMinimum("nostack")));
        legend.Draw("same");
        CMSandLumi->Draw();

        pad->Modified();
        c->Print(pathname_log + plotname + ".png");
    }
}
