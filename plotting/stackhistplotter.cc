#include "stackhistplotter.h"

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
        else if(filename.Index("_Background_") != -1) files_bkg.push_back(TFile::Open(filename));
        else if(filename.Index("_Run201") != -1) files_data.push_back(TFile::Open(filename));
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
    TString general_pathname = make_general_pathname("stacks/", specific_dir + "/");

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
    TString lumitext  = "21.1 fb^{-1} (13 TeV)";
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


    TIter next(files_bkg.back()->GetListOfKeys()); //last file in the list is the largest bkg
    TKey* key;
    while(key = (TKey*)next()){
        pad_histo->cd();
        legend.Clear();

        TClass *cl = gROOT->GetClass(key->GetClassName());

        // -- TH1 --
        if (cl->InheritsFrom("TH1") and ! cl->InheritsFrom("TH2")){ // second requirement is because TH2 also inherits from TH1
            
            // Get a reference histogram for the name, then get all histograms in  a vector
            TH1F*   sample_hist_ref = (TH1F*)key->ReadObj();
            TString histname   = sample_hist_ref->GetName();
            TString xaxistitle = sample_hist_ref->GetXaxis()->GetTitle();
            TString yaxistitle = sample_hist_ref->GetYaxis()->GetTitle();
            std::cout << histname << std::endl;
            
            if(sample_hist_ref->GetMaximum() == 0 and withdata) continue; // bkg histogram is empty and there is no data file to plot
            
            // get data histogram and fill legend
            TH1F* data_hist;
            if(withdata){ 
                data_hist = (TH1F*) files_data[0]->Get(histname);
                if(histname.Index("_CR") == -1) continue; // Only print Control region plots for data
                if(data_hist == 0 or data_hist->GetMaximum() == 0) continue; // data histogram is empty
                legend.AddEntry(data_hist, legends_data[0], "pl");
            }
            
            // get background histograms and fill legend
            THStack* hists_bkg = new THStack("stack_bkg", ";"  + ((withdata)? "" : xaxistitle) + ";" + yaxistitle);
            for(int i = 0; i < files_bkg.size(); i++){
                TH1* hist = (TH1*)files_bkg[i]->Get(histname);
                if(hist->GetMaximum() > 0){
                    int color = get_color(legends_bkg[i]);
                    hist->SetFillStyle(1001);
                    hist->SetFillColor(color);
                    hist->SetLineColor(color);
                    hists_bkg->Add(hist);
                    legend.AddEntry(hist, legends_bkg[i], "f");
                }
            }
            
            // get signal histograms and fill legend
            THStack* hists_signal = new THStack("stack_signal", "");
            for(int i = 0; i < files_signal.size(); i++){
                TH1* hist = (TH1*)files_signal[i]->Get(histname);
                if(hist->GetMaximum() > 0){
                    int color = get_color(legends_signal[i]);
                    hist->SetLineColor(color);
                    hists_signal->Add(hist);
                    legend.AddEntry(hist, legends_signal[i], "l");
                }
            }

            // get ratio of data/MC
            TH1F histo_ratio;
            if(withdata) histo_ratio = get_histoRatio(data_hist, (TH1F*) hists_bkg->GetStack()->Last(), xaxistitle);

            // get plot specific pathnames
            TString pathname_lin    = make_plotspecific_pathname(histname, general_pathname, "lin/");
            TString pathname_log    = make_plotspecific_pathname(histname, general_pathname, "log/");
            
            // set x range to log if necessary
            int xlog = (histname.Index("xlog") == -1)? 0 : 1;
            pad_histo->SetLogx(xlog);
            if(withdata) pad_ratio->SetLogx(xlog);
            if(xlog){
                TIter stack_iterator(hists_bkg->GetHists());
                TObject* sample_hist = 0;
                while(sample_hist = stack_iterator()){
                    divide_by_binwidth((TH1F*) sample_hist);
                }
                stack_iterator = hists_signal->GetHists();
                while(sample_hist = stack_iterator()){
                    divide_by_binwidth((TH1F*) sample_hist);
                }
                if(withdata) divide_by_binwidth(data_hist);
            }


            // Draw lin version
            pad_ratio->cd();
            pad_ratio->Clear();
            pad_histo->cd();
            pad_histo->Clear();
            pad_histo->SetLogy(0);

            hists_bkg->Draw("hist");
            if(withdata) hists_bkg->SetMaximum(1.28*std::max(hists_bkg->GetMaximum(), std::max(hists_signal->GetMaximum("nostack"), data_hist->GetMaximum())));
            else hists_bkg->SetMaximum(1.28*std::max(hists_bkg->GetMaximum(), hists_signal->GetMaximum("nostack")));
            hists_bkg->SetMinimum(0.);
            if(hists_signal->GetNhists() != 0) hists_signal->Draw("hist nostack same");
            if(withdata) data_hist->Draw("E0 X0 P same");
            legend.Draw("same");
            CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);
            lumilatex.DrawLatex(1-rightmargin, 1-0.8*topmargin, lumitext);
            
            pad_histo->Modified();

            // Draw ratio version if data is present
            if(withdata){
                pad_ratio->cd();
                pad_ratio->Clear();
            
                histo_ratio.Draw("E0 X0 P");
                draw_line_at_1(histo_ratio.GetXaxis()->GetXmin(), histo_ratio.GetXaxis()->GetXmax());

                pad_ratio->Modified();
            }

            c->Print(pathname_lin + histname + ".pdf");


            // Draw log version
            pad_ratio->cd();
            pad_ratio->Clear();
            pad_histo->cd();
            pad_histo->Clear();
            pad_histo->SetLogy(1);

            hists_bkg->Draw("hist");
            if(withdata) hists_bkg->SetMaximum(20*std::max(hists_bkg->GetMaximum(), std::max(hists_signal->GetMaximum("nostack"), data_hist->GetMaximum())));
            else hists_bkg->SetMaximum(20*std::max(hists_bkg->GetMaximum(), hists_signal->GetMaximum("nostack")));
            hists_bkg->SetMinimum(0.1);
            if(hists_signal->GetNhists() != 0) hists_signal->Draw("hist nostack same");
            if(withdata) data_hist->Draw("E0 X0 P same");
            legend.Draw("same");
            CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);
            lumilatex.DrawLatex(1-rightmargin, 1-0.8*topmargin, lumitext);
            
            pad_histo->Modified();

            // Draw ratio data/MC if data is present
            if(withdata){
                pad_ratio->cd();
                pad_ratio->Clear();

                histo_ratio.Draw("E0 X0 P");
                draw_line_at_1(histo_ratio.GetXaxis()->GetXmin(), histo_ratio.GetXaxis()->GetXmax());

                pad_ratio->Modified();
            }

            c->Print(pathname_log + histname + ".pdf");


            // Calculate and draw efficiencies as TGraphAsymmErrors in a multigraph
            if(histname.Index("eff_num") != -1){
                pad_histo->Clear();
                pad_histo->SetLogy(0);
                legend.Clear();
                
                TMultiGraph* multigraph = new TMultiGraph();
                multigraph->SetTitle((TString)";" + xaxistitle + ";Eff.");
                for(int i = 0; i < files_bkg.size(); i++){
                    TGraphAsymmErrors* graph = new TGraphAsymmErrors((TH1F*) files_bkg[i]->Get(histname), (TH1F*) files_bkg[i]->Get(histname(0, histname.Index("eff_num")+4) + "den"), "cp");
                    graph->SetMarkerColor(get_color(legends_bkg[i]));
                    multigraph->Add(graph);
                    legend.AddEntry(graph, legends_bkg[i], "pl");
                }
                for(int i = 0; i < files_signal.size(); i++){
                    TGraphAsymmErrors* graph = new TGraphAsymmErrors((TH1F*) files_signal[i]->Get(histname), (TH1F*) files_signal[i]->Get(histname(0, histname.Index("eff_num")+4) + "den"), "cp");
                    graph->SetMarkerColor(get_color(legends_signal[i]));
                    multigraph->Add(graph);
                    legend.AddEntry(graph, legends_signal[i], "pl");
                }
                if(withdata){
                    TGraphAsymmErrors* graph = new TGraphAsymmErrors((TH1F*) files_data[0]->Get(histname), (TH1F*) files_data[0]->Get(histname(0, histname.Index("eff_num")+4) + "den"), "cp");
                    graph->SetMarkerColor(get_color(legends_data[0]));
                    multigraph->Add(graph);
                    legend.AddEntry(graph, legends_data[0], "pl");
                }

                multigraph->Draw("AP");
                multigraph->SetMinimum(0.);
                multigraph->SetMaximum(1.25);

                legend.Draw("same");
                CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);
                lumilatex.DrawLatex(1-rightmargin, 1-0.8*topmargin, lumitext);

                pad_histo->Modified();
                c->Print(pathname_lin + histname(0, histname.Index("eff_num") + 3) + ".pdf");
            }
        }
    }
}
# endif
