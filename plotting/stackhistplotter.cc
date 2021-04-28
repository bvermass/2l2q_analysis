#include "stackhistplotter.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    // set general plot style
    setTDRStyle();
    gROOT->ForceStyle();

    // Argument 1: specific directory for plots (related to x in dilep_x.root or specific set of plots)
    // Argument 2: partitionjobnumber
    // Argument 3: partition
    // Argement 4 - (n+3)/2: name of root input files -> separate them between HNL and background based on filename
    // Argument (n+5)/2 - n: legends associated to samples
    int i_rootfiles = 4;
    int i_legends   = argc/2 + 2;

    std::vector<TFile*>  files_signal;
    std::vector<TFile*>  files_bkg;
    std::vector<TFile*>  files_data;
    std::vector<TString> legends_signal;
    std::vector<TString> legends_bkg;
    std::vector<TString> legends_data;
    bool is_mini_analyzer = false;
    bool is2016 = false, is2017 = false, is2018 = false, isRun2 = false;
    int n_columns = 3;
    for(int i = 0; i < argc - i_legends; i++){
        TString filename = (TString)argv[i_rootfiles + i];
        TString legendname = (TString)argv[i_legends + i];
        int adjusted_legend_length = legendname.Length() - 3*legendname.Contains("#tau") - 3*legendname.Contains("^{2}");
        //if(adjusted_legend_length > 13) n_columns = 1;
        if(adjusted_legend_length > 9) n_columns = 2;

        if(legendname.Contains("HNL")){
            files_signal.push_back(TFile::Open(filename));
            legends_signal.push_back(adjust_legend(legendname));
        }else if(legendname.Contains("201") or legendname.Contains("Data") or legendname.Contains("data")/* or legendname.Contains("Top") or legendname.Contains("MC_Bkg")*/){
            files_data.push_back(TFile::Open(filename));
            legends_data.push_back(adjust_legend(legendname));
        }else {
            files_bkg.push_back(TFile::Open(filename));
            legends_bkg.push_back(adjust_legend(legendname));
        }

        if(filename.Contains("hists_mini_analyzer")){
            is_mini_analyzer = true;
        }

        if(filename.Contains("MiniAOD2016") or filename.Contains("Run2016")) is2016 = true;
        else if(filename.Contains("MiniAOD2017") or filename.Contains("Run2017")) is2017 = true;
        else if(filename.Contains("MiniAOD2018") or filename.Contains("Run2018")) is2018 = true;
        else if(filename.Contains("MiniAODRun2") or filename.Contains("Run2.")) isRun2 = true;
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

    std::vector<int> linestyle_signal = {10,9,8};
    std::vector<std::vector<int>> rgb_signal = {{66,129,201}, {60,219,28}, {220,0,115}};
    std::vector<int> colors_signal = {3,4,7};
    //for(int i = 0; i < rgb_signal.size(); i++){
    //    colors_signal.push_back(TColor::GetColor(rgb[i][0], rgb[i][1], rgb[i][2]));
    //}

    std::vector<int> rgb_Pred = {174,71,76};
    int color_Pred = TColor::GetColor(rgb_Pred[0], rgb_Pred[1], rgb_Pred[2]);

    // Name of directory where plots will end up
    TString specific_dir = (TString)argv[1];
    std::cout << specific_dir << std::endl;
    TString general_pathname = make_general_pathname("plots/stacks/", specific_dir + "/");

    // Read identifiers from plotting/identifiers.txt and only make plots matching these tags
    std::vector<std::vector<TString>> identifiers = get_identifiers("plotting/identifiers.txt", ",");

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

    double lgnd_lowerbound = 0.80;
    if(legends_signal.size() + legends_bkg.size() + legends_data.size() > 6) lgnd_lowerbound = 0.76;
    if(legends_signal.size() + legends_bkg.size() + legends_data.size() > 8) lgnd_lowerbound = 0.73;
    TLegend legend = get_legend(0.2, lgnd_lowerbound, 0.95, 0.91, n_columns);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad_histo, is2016, is2017, is2018, isRun2);
    Shape_SR_plottext* shapeSR_text = new Shape_SR_plottext(pad_histo);
    float leftmargin  = pad_histo->GetLeftMargin();
    float topmargin   = pad_histo->GetTopMargin();
    float rightmargin = pad_histo->GetRightMargin();

    // Make the pad that will contain the ratio data/MC
    c->cd(); // first return to canvas so that second pad will be drawn in here and not in pad_histo
    TPad* pad_ratio = new TPad("pad_ratio", "", 0., 0., 1.,std::max(0., ymin));
    RatioPlot ratioplotter(pad_ratio);

    int partitionjobnumber = std::atoi(argv[2]);
    int partition = std::atoi(argv[3]);
    int counter = 0;
    int counter_begin = floor(1.0 * partitionjobnumber / partition * files_bkg.back()->GetNkeys());
    int counter_end   = floor(1.0 * (partitionjobnumber + 1) / partition * files_bkg.back()->GetNkeys());

    TList *keylist;
    if(withdata) keylist = files_data.front()->GetListOfKeys();
    else keylist = files_bkg.back()->GetListOfKeys();

    TIter next(keylist); //last file in the list is the largest bkg
    TKey* key;
    while(key = (TKey*)next()){
        if(counter >= counter_begin and counter <= counter_end){
            pad_histo->cd();
            legend.Clear();

            std::string cl(key->GetClassName());

            // -- TH1 --
            if(cl.find("TH1") != std::string::npos){ // second requirement is because TH2 also inherits from TH1
                
                // Get a reference histogram for the name, then get all histograms in  a vector
                TH1F*   sample_hist_ref = (TH1F*)key->ReadObj();
                TString histname   = sample_hist_ref->GetName();
                TString xaxistitle = sample_hist_ref->GetXaxis()->GetTitle();
                TString yaxistitle = sample_hist_ref->GetYaxis()->GetTitle();
                
                if(histname.Index("_sys") != -1 or histname.Index("_Bool_") != -1 or histname.Index("_fromZ_") != -1) continue; // don't plot the Bool histograms
                if(sample_hist_ref->GetMaximum() == 0 and withdata) continue; // bkg histogram is empty and there is no data file to plot
                if(!check_identifiers(histname, identifiers)) continue;
                std::cout << histname << std::endl;

                // get data histogram and fill legend
                TH1F* data_hist;
                if(withdata){
                    TString histname_BtoA = histname;
                    if(!histname.Contains("_noSR")) histname_BtoA.ReplaceAll("_cutbaselinemlSV", "_cutbaselinemlSV_noSR");
                    //if(histname.Contains("_quadA_")){
                    //    histname_BtoA.ReplaceAll("_quadA_", "_BtoAwithCD_");
                    //}else if(histname.Contains("_AoverC_")){
                    //    histname_BtoA.ReplaceAll("_AoverC_", "_BoverD_");
                    //}
                    data_hist = (TH1F*) files_data[0]->Get(histname_BtoA);
                    if(!is_mini_analyzer and histname.Index("_CR") == -1 and histname.Index("_Training_") == -1 and histname.Index("_2prompt") == -1 and histname.Index("_afterSV") == -1 and histname.Index("_2Jets") == -1 and !histname.Contains("l2Sel") and !histname.Contains("cutflow2")) continue; // Only print Control region plots for data or Training region with high background
                    //if(histname.Contains("JetTagVal") or histname.Contains("PFN_ROC")) continue;
                    if(data_hist == 0 or data_hist->GetMaximum() == 0) continue; // data histogram is empty
                    legend.AddEntry(data_hist, legends_data[0], "pl");
                }
                
                TString histname_bkg = histname;
                histname_bkg.ReplaceAll("_quadA_", "_BtoAwithCD_");
                // get background histograms and fill legend
                THStack* hists_bkg = new THStack("stack_bkg", ";"  + ((withdata)? "" : xaxistitle) + ";" + yaxistitle);
                for(int i = 0; i < files_bkg.size(); i++){
                    TH1* hist = (TH1*)files_bkg[i]->Get(histname_bkg);
                    if(hist->GetMaximum() > 0){
                        int color; 
                        if(legends_bkg[i].Contains("Pred")) color = color_Pred;
                        else color = get_color(legends_bkg[i]);
                        hist->SetFillStyle(1001);
                        hist->SetFillColor(color);
                        hist->SetLineColor(color);
                        hists_bkg->Add(hist);
                        legend.AddEntry(hist, legends_bkg[i], "f");
                    }
                }
                if(hists_bkg->GetMaximum() <= 0) continue;
                
                // get signal histograms and fill legend
                TString histname_signal = histname;
                histname_signal.ReplaceAll("_BtoAwithCD_", "_quadA_");
                THStack* hists_signal = new THStack("stack_signal", "");
                for(int i = 0; i < files_signal.size(); i++){
                    if(files_signal[i]->GetListOfKeys()->Contains(histname_signal)){
                        TH1* hist = (TH1*)files_signal[i]->Get(histname_signal);
                        if(hist->GetMaximum() > 0){
                            //int color = get_color(legends_signal[i]);
                            hist->SetLineColor(colors_signal[i]);
                            hist->SetLineStyle(linestyle_signal[i]);
                            hist->SetLineWidth(3);
                            if(histname.Contains("_cutflow2")) hist->Scale(((TH1F*)hists_bkg->GetStack()->Last())->GetBinContent(1)/hist->GetBinContent(1));
                            else if(histname.Contains("_afterSV") or histname.Contains("_Training")) hist->Scale(((TH1F*)hists_bkg->GetStack()->Last())->Integral()/hist->Integral());
                            //else hist->Scale(10.);
                            hist->SetMarkerColor(colors_signal[i]);
                            hists_signal->Add(hist);
                            TString legend_tmp = legends_signal[i];
                            legend_tmp.ReplaceAll("x",histname(histname.Index("V2-")+3, histname.Index("_cut") - histname.Index("V2-") - 3));
                            legend_tmp.ReplaceAll("-03", "^{-3}");
                            legend_tmp.ReplaceAll("-04", "^{-4}");
                            legend_tmp.ReplaceAll("-05", "^{-5}");
                            legend_tmp.ReplaceAll("-06", "^{-6}");
                            legend_tmp.ReplaceAll("-07", "^{-7}");
                            legend.AddEntry(hist, legend_tmp, "l");
                        }
                    }
                }

                // get summed background as a single histogram to draw error bands
                TH1F* bkgForError = (TH1F*) hists_bkg->GetStack()->Last()->Clone();
                bkgForError->SetFillStyle(3244);
                bkgForError->SetFillColor(kGray+2);
                bkgForError->SetMarkerStyle(0);

                // set ratio of data/MC
                if(withdata){
                    ratioplotter.ClearSystUncs();
                    ratioplotter.SetCentralRatio(data_hist, (TH1F*)hists_bkg->GetStack()->Last(), xaxistitle, "Obs/Pred");
                    ratioplotter.AddStatVariation((TH1F*)hists_bkg->GetStack()->Last(), "stat. unc.");
                    //ratioplotter.SetSystUncs_up_and_down(histname, files_bkg, {"JEC", "Res", "Uncl"}, {"JEC", "JER", "Uncl."}, (TH1F*)hists_bkg->GetStack()->Last());//example from MET Resolution study
                }

                // get plot specific pathnames
                TString pathname_lin    = make_plotspecific_pathname(histname, general_pathname, "lin/");
                TString pathname_log    = make_plotspecific_pathname(histname, general_pathname, "log/");
                
                // set x range to log if necessary
                int xlog = (histname.Index("xlog") == -1)? 0 : 1;
                pad_histo->SetLogx(xlog);
                if(withdata) ratioplotter.SetLogx(xlog);
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
                pad_histo->cd();
                pad_histo->Clear();
                pad_histo->SetLogy(0);

                hists_bkg->Draw("hist");
                bkgForError->Draw("e2 same");
                if(withdata) hists_bkg->SetMaximum(1.35*std::max(hists_bkg->GetMaximum(), std::max(hists_signal->GetMaximum("nostack"), data_hist->GetMaximum())));
                else hists_bkg->SetMaximum(1.35*std::max(hists_bkg->GetMaximum(), hists_signal->GetMaximum("nostack")));
                if(!withdata) alphanumeric_labels(hists_bkg, histname);
                hists_bkg->SetMinimum(0.);
                if(hists_signal->GetNhists() != 0) hists_signal->Draw("hist nostack same");
                if(hists_signal->GetNhists() != 0) hists_signal->Draw("E nostack same");
                if(withdata) data_hist->Draw("E0 X0 P same");
                legend.Draw("same");
                CMSandLumi->Draw();
                if(histname.Contains("Shape")) shapeSR_text->Draw(histname);
                
                pad_histo->Modified();

                // Draw ratio data/MC if data is present
                if(withdata) ratioplotter.dothething();

                c->Print(pathname_lin + histname + ".png");


                // Draw log version
                pad_ratio->cd();
                pad_ratio->Clear();
                pad_histo->cd();
                pad_histo->Clear();
                pad_histo->SetLogy(1);

                hists_bkg->Draw("hist");
                bkgForError->Draw("e2 same");
                if(withdata) hists_bkg->SetMaximum(20*std::max(hists_bkg->GetMaximum(), std::max(hists_signal->GetMaximum("nostack"), data_hist->GetMaximum())));
                else hists_bkg->SetMaximum(20*std::max(hists_bkg->GetMaximum(), hists_signal->GetMaximum("nostack")));
                if(!withdata) alphanumeric_labels(hists_bkg, histname);
                if(withdata and std::max(hists_bkg->GetMaximum(), std::max(hists_signal->GetMaximum("nostack"), data_hist->GetMaximum())) > 1000) hists_bkg->SetMinimum(40.);
                else hists_bkg->SetMinimum(4.);
                if(hists_signal->GetNhists() != 0) hists_signal->Draw("hist nostack same");
                if(hists_signal->GetNhists() != 0) hists_signal->Draw("E nostack same");
                if(withdata) data_hist->Draw("E0 X0 P same");
                legend.Draw("same");
                CMSandLumi->Draw();
                if(histname.Contains("Shape")) shapeSR_text->Draw(histname);
                
                pad_histo->Modified();

                // Draw ratio data/MC if data is present
                if(withdata) ratioplotter.dothething();

                c->Print(pathname_log + histname + ".png");


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
                    CMSandLumi->Draw();

                    pad_histo->Modified();
                    c->Print(pathname_lin + histname(0, histname.Index("eff_num") + 3) + ".png");
                }
            }
        }
        ++counter;
    }
}
# endif
