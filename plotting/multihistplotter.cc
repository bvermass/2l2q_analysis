#include "multihistplotter.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    bool normalize_to_unity = false;
    // set general plot style
    setTDRStyle();
    auto style = gROOT->GetStyle("tdrStyle");
    style->SetMarkerSize(0.01);
    gROOT->ForceStyle();

    // Argument 1: specific directory for plots (related to x in dilep_x.root or specific set of plots)
    // Argement 2 - (n+1)/2: name of root input files
    // Argument (n+3)/2 - n: legends associated to samples
    int i_rootfiles = 4;
    int i_legends   = argc/2 + 2;

    std::vector<TFile*>  files;
    bool is2016 = false, is2017 = false, is2018 = false, isRun2 = false, isData = false;
    unsigned i_Data = 0;
    for(int i = i_rootfiles; i < i_legends; i++){
        TString filename = (TString)argv[i];
        files.push_back(TFile::Open(filename));

        if(filename.Contains("MiniAOD2016") or filename.Contains("Run2016")) is2016 = true;
        else if(filename.Contains("MiniAOD2017") or filename.Contains("Run2017")) is2017 = true;
        else if(filename.Contains("MiniAOD2018") or filename.Contains("Run2018")) is2018 = true;
        else if(filename.Contains("MiniAODRun2") or filename.Contains("Run2.")) isRun2 = true;
        else if(filename.Contains("MiniAOD1617") or filename.Contains("Run1617")){ is2016 = true; is2017 = true; }
        else if(filename.Contains("MiniAOD1618") or filename.Contains("Run1618")){ is2016 = true; is2018 = true; }
        else if(filename.Contains("MiniAOD1718") or filename.Contains("Run1718")){ is2017 = true; is2018 = true; }
        if(filename.Contains("Run201") or filename.Contains("Run2.")){
            isData = true;
            i_Data = files.size() - 1;
        }
    }
    std::vector<TString> legends;
    int n_columns = 3;
    for(int i = i_legends; i < argc; i++){
        TString legendname = adjust_legend((TString)argv[i]);
        legends.push_back(legendname);

        // adjust number of columns for legend if an entry is too large to fit
        int adjusted_legend_length = legendname.Length() - 3*legendname.Contains("#tau");
        if(adjusted_legend_length > 13) n_columns = 1;
        else if(adjusted_legend_length > 9) n_columns = 2;

    }

    //this color scheme comes from the coolors.co app: https://coolors.co/2e72cc-560e76-1db600-e8a400-ef201d
    std::vector<std::vector<int>> rgb = {{46, 114, 204}, {239, 32, 29}, {29, 182, 0}, {86, 14, 118}, {232, 164, 0}, {86, 22, 67}, {247, 135, 100}, {47, 41, 35}};
    //std::vector<std::vector<int>> rgb = {{66, 129, 174}, {212, 180, 131}, {193, 102, 107}, {10, 90, 80}, {20, 30, 190}, {86, 22, 67}, {247, 135, 100}, {47, 41, 35}};
    std::vector<int> colors;
    for(int i = 0; i < rgb.size(); i++){
        colors.push_back(TColor::GetColor(rgb[i][0], rgb[i][1], rgb[i][2]));
    }

    // Name of directory where plots will end up
    TString specific_dir = (TString)argv[1];
    TString general_pathname = make_general_pathname("plots_new/multihists/", specific_dir + "/");

    // Read identifiers from plotting/identifiers.txt and only make plots matching these tags
    std::vector<std::vector<TString>> identifiers = get_identifiers("plotting/identifiers.txt", ",");

    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    // Make the pad that will contain the plot
    TPad* pad  = new TPad("pad", "", 0., 0., 1., 1.);
    pad->Draw();
    pad->cd();

    TLegend legend = get_legend(0.18, 0.84, 0.95, 0.93, n_columns);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad, is2016, is2017, is2018, isRun2);
    Shape_SR_plottext* shapeSR_text = new Shape_SR_plottext(pad);
    float leftmargin  = pad->GetLeftMargin();
    float topmargin   = pad->GetTopMargin();
    float rightmargin = pad->GetRightMargin();


    int partitionjobnumber = std::atoi(argv[2]);
    int partition = std::atoi(argv[3]);
    int counter = 0;
    int counter_begin = floor(1.0 * partitionjobnumber / partition * files.front()->GetNkeys());
    int counter_end   = floor(1.0 * (partitionjobnumber + 1) / partition * files.front()->GetNkeys());

    TIter next(files.front()->GetListOfKeys());
    TKey* key;
    while(key = (TKey*)next()){
        if(counter >= counter_begin and counter <= counter_end){
            TString plotname_addition = "";
            legend.Clear();

            std::string cl(key->GetClassName());

            // -- TH1 --
            if(cl.find("TH1") != std::string::npos){

                // Get a reference histogram for the name, then get all histograms in  a vector
                TH1F*   sample_hist_ref = (TH1F*)key->ReadObj();
                TString histname   = sample_hist_ref->GetName();

                if(histname.Index("_Bool_") != -1) continue; // don't plot the Bool histograms
                if(histname.Contains("_sys")) continue;
                if(sample_hist_ref->GetMaximum() == 0) continue;
                if(!check_identifiers(histname, identifiers)) continue;
                std::cout << histname << std::endl;

                THStack* hists = new THStack("stack", "");
                for(int i = 0; i < files.size(); i++){
                    if(files[i]->GetListOfKeys()->Contains(histname)){
                        TString histname_to_use = histname;
                        if(histname.Contains("_Training_") and legends[i].Contains("Low Mass PFN > 0.9")){
                                histname_to_use.ReplaceAll("_Training_", "_TrainingHighPFN_M-5_");
                                plotname_addition = "_vsLowMassPFN";
                        }else if(histname.Contains("_Training_") and legends[i].Contains("High Mass PFN > 0.9")) histname_to_use.ReplaceAll("_Training_", "_TrainingHighPFN_M-10_");
                        else if(histname.Contains("_Training_") and legends[i].Contains("PFN > 0.9")){
                            if(specific_dir.Contains("LowMass")){
                                histname_to_use.ReplaceAll("_Training_", "_TrainingHighPFN_M-5_");
                                plotname_addition = "_vsLowMassPFN";
                            }else if(specific_dir.Contains("HighMass")){
                                histname_to_use.ReplaceAll("_Training_", "_TrainingHighPFN_M-10_");
                                plotname_addition = "_vsHighMassPFN";
                            }
                        }else if(histname.Contains("cutoutsidemlSV") and legends[i].Contains("mlSV = [50,85]")){
                            histname_to_use.ReplaceAll("cutoutsidemlSV", "cutinsidemlSV");
                            plotname_addition = "_VSinside";
                        }
                        TH1* hist = (TH1*)files[i]->Get(histname_to_use);
                        if(hist and hist->GetMaximum() > 0){
                            hists->Add(hist);
                            if(legends[i].Contains("Pred") or legends[i].Contains("Data")){
                                hist->SetMarkerColor(kBlack);
                                hist->SetLineColor(kBlack);
                            }else{
                                hist->SetMarkerColor(colors[i]);
                                hist->SetLineColor(colors[i]);
                            }
                            if(normalize_to_unity and !histname.Contains("_eff_")) hist->Scale(1./hist->Integral());
                            else if(histname.Contains("_ctau") and !histname.Contains("_eff_")) hist->Scale(1./hist->Integral());
                            legend.AddEntry(hist, legends[i], "l");
                        }
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

                hists->Draw("hist E nostack");
                hists->GetXaxis()->SetTitle(sample_hist_ref->GetXaxis()->GetTitle());
                hists->GetYaxis()->SetTitle(sample_hist_ref->GetYaxis()->GetTitle());
                hists->SetMaximum(1.25*hists->GetMaximum("nostack"));
                legend.Draw("same");
                CMSandLumi->add_flavor(histname);
                CMSandLumi->Draw();
                if(histname.Contains("Shape_SR")) shapeSR_text->Draw(histname);

                pad->Modified();
                c->Print(pathname_lin + histname + plotname_addition + ".png");

                // Draw log version
                pad->Clear();
                pad->SetLogy(1);

                hists->Draw("hist E nostack");
                hists->GetXaxis()->SetTitle(sample_hist_ref->GetXaxis()->GetTitle());
                hists->GetYaxis()->SetTitle(sample_hist_ref->GetYaxis()->GetTitle());
                hists->SetMaximum(10*hists->GetMaximum("nostack"));
                hists->SetMinimum(1e-2);
                legend.Draw("same");
                CMSandLumi->add_flavor(histname);
                CMSandLumi->Draw();
                if(histname.Contains("Shape_SR")) shapeSR_text->Draw(histname);

                pad->Modified();
                c->Print(pathname_log + histname + plotname_addition + ".png");




                // Calculate and draw efficiencies as TGraphAsymmErrors in a multigraph
                if(histname.Index("eff_num") != -1){
                    pad->Clear();
                    pad->SetLogy(0);
                    legend.Clear();

                    TMultiGraph* multigraph = new TMultiGraph();
                    multigraph->SetTitle((TString)";" + sample_hist_ref->GetXaxis()->GetTitle() + ";Eff.");
                    for(int i = 0; i < files.size(); i++){
                        if(files[i]->GetListOfKeys()->Contains(histname) and files[i]->GetListOfKeys()->Contains(histname(0, histname.Index("eff_num")+4) + "den")){
                            TGraphAsymmErrors* graph = new TGraphAsymmErrors((TH1F*) files[i]->Get(histname), (TH1F*) files[i]->Get(histname(0, histname.Index("eff_num")+4) + "den"), "cp");
                            multigraph->Add(graph);
                            graph->SetMarkerColor(colors[i]);
                            graph->SetLineColor(colors[i]);
                            legend.AddEntry(graph, legends[i], "pl");
                        }
                    }

                    multigraph->Draw("AP");
                    multigraph->SetMinimum(0.);
                    multigraph->SetMaximum((multigraph->GetHistogram()->GetMaximum() > 0.2)? 1.25 : 0.225);

                    legend.Draw("same");
                    CMSandLumi->add_flavor(histname);
                    CMSandLumi->Draw();

                    pad->Modified();
                    c->Print(pathname_lin + histname(0, histname.Index("eff_num") + 3) + ".png");
                }



                if(isData and (histname.Contains("_BoverD_") or histname.Contains("_BtoAwithCD_"))){

                    legend.Clear();
                    TString histname_AoverC = histname;
                    TString plotname = histname;
                    histname_AoverC.ReplaceAll("_BoverD_", "_AoverC_");
                    histname_AoverC.ReplaceAll("_BtoAwithCD_", "_quadA_");
                    plotname.ReplaceAll("_BoverD_", "_BDvsAC_");
                    plotname.ReplaceAll("_BtoAwithCD_", "_BtoAwithSig_");

                    THStack* hists_AoverC = new THStack("stack_AoverC", "");
                    for(int i = 0; i < files.size(); i++){
                        TString name_to_use;
                        if(i == i_Data) name_to_use = histname;
                        else name_to_use = histname_AoverC;

                        if(files[i]->GetListOfKeys()->Contains(name_to_use)){
                            TH1* hist = (TH1*)files[i]->Get(name_to_use);
                            if(hist->GetMaximum() > 0){
                                hists_AoverC->Add(hist);
                                if(legends[i].Contains("Pred")){
                                    hist->SetMarkerColor(kBlack);
                                    hist->SetLineColor(kBlack);
                                }else{
                                    hist->SetMarkerColor(colors[i]);
                                    hist->SetLineColor(colors[i]);
                                }
                                TString legend_tmp = legends[i];
                                legend_tmp.ReplaceAll("z",histname(histname.Index("V2-")+3, histname.Index("_cut") - histname.Index("V2-") - 3));
                                legend_tmp.ReplaceAll("-03", "^{-3}");
                                legend_tmp.ReplaceAll("-04", "^{-4}");
                                legend_tmp.ReplaceAll("-05", "^{-5}");
                                legend_tmp.ReplaceAll("-06", "^{-6}");
                                legend_tmp.ReplaceAll("-07", "^{-7}");
                                legend.AddEntry(hist, legend_tmp, "l");
                            }
                        }
                    }

                    // Draw lin version
                    pad->Clear();
                    pad->SetLogy(0);

                    hists_AoverC->Draw("hist E nostack");
                    hists_AoverC->GetXaxis()->SetTitle(sample_hist_ref->GetXaxis()->GetTitle());
                    hists_AoverC->GetYaxis()->SetTitle(sample_hist_ref->GetYaxis()->GetTitle());
                    hists_AoverC->SetMaximum(1.25*hists_AoverC->GetMaximum("nostack"));
                    legend.Draw("same");
                    CMSandLumi->add_flavor(histname);
                    CMSandLumi->Draw();
                    if(histname.Contains("Shape_SR")) shapeSR_text->Draw(histname);

                    pad->Modified();
                    c->Print(pathname_lin + plotname + ".png");

                    // Draw log version
                    pad->Clear();
                    pad->SetLogy(1);

                    hists_AoverC->Draw("hist E nostack");
                    hists_AoverC->GetXaxis()->SetTitle(sample_hist_ref->GetXaxis()->GetTitle());
                    hists_AoverC->GetYaxis()->SetTitle(sample_hist_ref->GetYaxis()->GetTitle());
                    hists_AoverC->SetMaximum(10*hists_AoverC->GetMaximum("nostack"));
                    hists_AoverC->SetMinimum(1e-4);
                    legend.Draw("same");
                    CMSandLumi->add_flavor(histname);
                    CMSandLumi->Draw();
                    if(histname.Contains("Shape_SR")) shapeSR_text->Draw(histname);

                    pad->Modified();
                    c->Print(pathname_log + plotname + ".png");

                    delete hists_AoverC;
                }
                
                //figures of C_sig / C_bkg that determine the sensitivity of region C signal 
                if(isData and histname.Contains("_quadC_")){
                    pad->Clear();
                    pad->SetLogy(0);
                    legend.Clear();

                    //TMultiGraph* multigraph = new TMultiGraph();
                    THStack* multigraph = new THStack("CsigOverCbkg", (TString)";" + sample_hist_ref->GetXaxis()->GetTitle() + ";C_{sig}/C_{bkg}");
                    //multigraph->SetTitle((TString)";" + sample_hist_ref->GetXaxis()->GetTitle() + ";C_{sig}/C_{bkg}");
                    for(int i = 0; i < files.size(); i++){
                        if(i == i_Data) continue;
                        if(files[i]->GetListOfKeys()->Contains(histname)){
                            //TGraphAsymmErrors* graph = new TGraphAsymmErrors((TH1F*) files[i]->Get(histname), (TH1F*) files[i_Data]->Get(histname));
                            TH1F* graph = (TH1F*) files[i]->Get(histname);
                            TH1F* graphden = (TH1F*) files[i_Data]->Get(histname);
                            graph->Divide(graphden);
                            multigraph->Add(graph);
                            graph->SetMarkerColor(colors[i]);
                            graph->SetLineColor(colors[i]);

                            TString legend_tmp = legends[i];
                            legend_tmp.ReplaceAll("z",histname(histname.Index("V2-")+3, histname.Index("_cut") - histname.Index("V2-") - 3));
                            legend_tmp.ReplaceAll("-03", "^{-3}");
                            legend_tmp.ReplaceAll("-04", "^{-4}");
                            legend_tmp.ReplaceAll("-05", "^{-5}");
                            legend_tmp.ReplaceAll("-06", "^{-6}");
                            legend_tmp.ReplaceAll("-07", "^{-7}");
                            legend.AddEntry(graph, legend_tmp, "pl");
                        }
                    }
                    multigraph->Draw("hist E nostack");
                    multigraph->SetMinimum(1e-4);
                    pad->SetLogy(1);
                    multigraph->SetMaximum(10*multigraph->GetMaximum("nostack"));

                    legend.Draw("same");
                    CMSandLumi->add_flavor(histname);
                    CMSandLumi->Draw();

                    pad->Modified();
                    c->Print(pathname_log + histname.ReplaceAll("quadC","CsigOverCbkg") + ".png");
                }

                if(histname.Contains("_quadA_")){
                    pad->Clear();
                    pad->SetLogy(0);
                    legend.Clear();

                    TString histname_BtoAwithCD = histname;
                    histname_BtoAwithCD.ReplaceAll("_quadA_", "_BtoAwithCD_");

                    THStack* stack = new THStack("ADoverBC", (TString)";" + sample_hist_ref->GetXaxis()->GetTitle() + ";A*D/B*C");
                    for(int i = 0; i < files.size(); i++){
                        if(files[i]->GetListOfKeys()->Contains(histname)){
                            TH1F* h_quadA = (TH1F*)files[i]->Get(histname);
                            TH1F* h_BtoAwithCD = (TH1F*)files[i]->Get(histname_BtoAwithCD);

                            h_quadA->Divide(h_BtoAwithCD);
                            stack->Add(h_quadA);
                            h_quadA->SetMarkerColor(colors[i]);
                            h_quadA->SetLineColor(colors[i]);
                            
                            TString legend_tmp = legends[i];
                            legend_tmp.ReplaceAll("z",histname(histname.Index("V2-")+3, histname.Index("_cut") - histname.Index("V2-") - 3));
                            legend_tmp.ReplaceAll("-03", "^{-3}");
                            legend_tmp.ReplaceAll("-04", "^{-4}");
                            legend_tmp.ReplaceAll("-05", "^{-5}");
                            legend_tmp.ReplaceAll("-06", "^{-6}");
                            legend_tmp.ReplaceAll("-07", "^{-7}");
                            legend.AddEntry(h_quadA, legend_tmp, "pl");
                        }
                    }

                    stack->Draw("E nostack");
                    stack->SetMinimum(0.);
                    stack->SetMaximum(std::min(6., 1.25*stack->GetMaximum("nostack")));

                    draw_line_at_1(stack->GetXaxis()->GetXmin(), stack->GetXaxis()->GetXmax());

                    legend.Draw("same");
                    CMSandLumi->add_flavor(histname);
                    CMSandLumi->Draw();
                    if(histname.Contains("Shape_SR")) shapeSR_text->Draw(histname);

                    pad->Modified();
                    c->Print(pathname_lin + histname.ReplaceAll("_quadA_", "_ADoverBC_") + ".png");
                }
            }
            if(cl.find("TH2") != std::string::npos){
                TH2F*   sample_hist_ref = (TH2F*)key->ReadObj();
                TString histname   = sample_hist_ref->GetName();
                if(!(histname.Contains("_OS_mm_Training_IVF_ctauHN_gen_PV-SVdxyz") or histname.Contains("_OS_mm_IVF_gen_PV-SVdxyz_ctauHN_eff") or histname == "gen_PV-SVdxyz_ctauHN" or histname == "gen_l2pt_ctauHN")) continue;
                if(!check_identifiers(histname, identifiers)) continue;
                std::cout << histname << std::endl;

                std::vector<TH2*> hists;
                for(int i = 0; i < files.size(); i++){
                    hists.push_back((TH2*)files[i]->Get(histname));
                }

                for(TString projectionAxis : {"projectionX_", "projectionY_"}){
                    int nbins = 0;
                    if(projectionAxis.Contains("projectionX")) nbins = hists[0]->GetNbinsX();
                    if(projectionAxis.Contains("projectionY")) nbins = hists[0]->GetNbinsY();
                    //print projections of the 2D histogram along each axis
                    for(int i_bin = 1; i_bin <= nbins; i_bin++){
                        legend.Clear();
                        THStack* histstack = new THStack("stack", "");
                        for(int i = 0; i < hists.size(); i++){
                            TH1D* projection;
                            if(projectionAxis.Contains("projectionX")) projection = hists[i]->ProjectionX(histname + "_" + legends[i] + "_" + projectionAxis + std::to_string(i_bin), i_bin, i_bin, "e");
                            if(projectionAxis.Contains("projectionY")) projection = hists[i]->ProjectionY(histname + "_" + legends[i] + "_" + projectionAxis + std::to_string(i_bin), i_bin, i_bin, "e");
                            histstack->Add(projection);
                            projection->Scale(1./projection->Integral());
                            projection->Rebin(2);
                            projection->SetLineColor(colors[i]);
                            projection->SetMarkerColor(colors[i]);
                            legend.AddEntry(projection, legends[i], "pl");
                        }
                        pad->Clear();
                        pad->SetLogy(0);
                        TString pathname_lin = make_plotspecific_pathname(histname + "_projection", general_pathname, "lin/");
                        histstack->Draw("hist E nostack");
                        if(projectionAxis.Contains("projectionX")) histstack->GetXaxis()->SetTitle(sample_hist_ref->GetXaxis()->GetTitle());
                        if(projectionAxis.Contains("projectionY")) histstack->GetXaxis()->SetTitle(sample_hist_ref->GetYaxis()->GetTitle());
                        histstack->GetYaxis()->SetTitle("A.U.");
                        histstack->SetMaximum(1.25*histstack->GetMaximum("nostack"));
                        legend.Draw("same");
                        CMSandLumi->add_flavor(histname);
                        CMSandLumi->Draw();

                        pad->Modified();
                        if(projectionAxis.Contains("projectionX")) c->Print(pathname_lin + histname + "_" + projectionAxis + std::to_string((int)hists[0]->GetXaxis()->GetBinLowEdge(i_bin)) + "to" + std::to_string((int)hists[0]->GetXaxis()->GetBinUpEdge(i_bin)) + ".png");
                        if(projectionAxis.Contains("projectionY")) c->Print(pathname_lin + histname + "_" + projectionAxis + std::to_string((int)hists[0]->GetYaxis()->GetBinLowEdge(i_bin)) + "to" + std::to_string((int)hists[0]->GetYaxis()->GetBinUpEdge(i_bin)) + ".png");

                        //if(histname.Contains("eff_num")){
                        //    pad->Clear();
                        //    legend.Clear();

                        //    TMultiGraph* multigraph = new TMultiGraph();
                        //    if(projectionAxis.Contains("projectionX")) multigraph->SetTitle((TString)";"+sample_hist_ref->GetXaxis()->GetTitle() + ";Efficiency");
                        //    if(projectionAxis.Contains("projectionY")) multigraph->SetTitle((TString)";"+sample_hist_ref->GetYaxis()->GetTitle() + ";Efficiency");
                        //    for(int i = 0; i < files.size(); i++){
                        //        if(files[i]->GetListOfKeys()->Contains(histname) and files[i]->GetListOfKeys()->Contains(histname(0, histname.Index("eff_num")+4) + "den")){
                        //            TGraphAsymmErrors* graph = new TGraphAsymmErrors((TH1F*) files[i]->Get(histname), (TH1F*) files[i]->Get(histname(0, histname.Index("eff_num")+4) + "den"), "cp");
                        //            multigraph->Add(graph);
                        //            graph->SetMarkerColor(colors[i]);
                        //            graph->SetLineColor(colors[i]);
                        //            legend.AddEntry(graph, legends[i], "pl");
                        //        }
                        //    }

                        //    multigraph->Draw("AP");
                        //    multigraph->SetMinimum(0.);
                        //    multigraph->SetMaximum((multigraph->GetHistogram()->GetMaximum() > 0.2)? 1.25 : 0.225);

                        //    legend.Draw("same");
                        //    CMSandLumi->add_flavor(histname);
                        //    CMSandLumi->Draw();

                        //    pad->Modified();
                        //    c->Print(pathname_lin + histname(0, histname.Index("eff_num") + 3) + ".png");

                        //}
                    }
                }
            }
        }
        ++counter;
    }
}
# endif
