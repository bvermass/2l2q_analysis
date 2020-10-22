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
    int i_rootfiles = 4;
    int i_legends   = argc/2 + 2;

    std::vector<TFile*>  files;
    bool is2016 = false, is2017 = false, is2018 = false;
    for(int i = i_rootfiles; i < i_legends; i++){
        TString filename = (TString)argv[i];
        files.push_back(TFile::Open(filename));

        if(filename.Contains("MiniAOD2016") or filename.Contains("Run2016")) is2016 = true;
        else if(filename.Contains("MiniAOD2017") or filename.Contains("Run2017")) is2017 = true;
        else if(filename.Contains("MiniAOD2018") or filename.Contains("Run2018")) is2018 = true;
    }
    std::vector<TString> legends;
    for(int i = i_legends; i < argc; i++){
        legends.push_back(adjust_legend((TString)argv[i]));
    }

    int n_columns = 3;
    for(int i = 0; i < legends.size(); i++){
        // adjust number of columns for legend if an entry is too large to fit
        if(legends[i].Length() > 13){
            n_columns = 1;
            std::cout << "setting legend to 1 column due to legend " << legends[i] << std::endl;
        }
        else if(legends[i].Length() > 9){
            n_columns = 2;
            std::cout << "setting legend to 1 column" << std::endl;
        }
    }
    std::cout << "coumns: " << n_columns << std::endl;

    //this color scheme comes from the coolors.co app: https://coolors.co/4281ae-0a5a50-4b4237-d4b483-c1666b
    //maybe this combo is better: https://coolors.co/4281ae-561643-4b4237-d4b483-c1666b?
    std::vector<std::vector<int>> rgb = {{66, 129, 174}, {212, 180, 131}, {193, 102, 107}, {10, 90, 80}, {75, 66, 65}, {86, 22, 67}, {247, 135, 100}};
    std::vector<int> colors;
    for(int i = 0; i < rgb.size(); i++){
        colors.push_back(TColor::GetColor(rgb[i][0], rgb[i][1], rgb[i][2]));
    }

    // Name of directory where plots will end up
    TString specific_dir = (TString)argv[1];
    TString general_pathname = make_general_pathname("plots/multihists/", specific_dir + "/");

    // Read identifiers from plotting/identifiers.txt and only make plots matching these tags
    std::vector<std::vector<TString>> identifiers = get_identifiers("plotting/identifiers.txt", ",");

    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    // Make the pad that will contain the plot
    TPad* pad  = new TPad("pad", "", 0., 0., 1., 1.);
    pad->Draw();
    pad->cd();

    TLegend legend = get_legend(0.18, 0.84, 0.95, 0.93, n_columns);
    TLegend legend_profiles = get_legend(0.18, 0.84, 0.95, 0.93, n_columns);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad, is2016, is2017, is2018);
    float leftmargin  = pad->GetLeftMargin();
    float topmargin   = pad->GetTopMargin();
    float rightmargin = pad->GetRightMargin();

    TLatex chi2latex = get_latex(0.8*topmargin, 31, 42);
    TLatex FWHMlatex = get_latex(0.8*topmargin, 31, 42);

    int partitionjobnumber = std::atoi(argv[2]);
    int partition = std::atoi(argv[3]);
    int counter = 0;
    int counter_begin = floor(1.0 * partitionjobnumber / partition * files.front()->GetNkeys());
    int counter_end   = floor(1.0 * (partitionjobnumber + 1) / partition * files.front()->GetNkeys());

    TIter next(files.front()->GetListOfKeys());
    TKey* key;
    while(key = (TKey*)next()){
        if(counter >= counter_begin and counter <= counter_end){
            legend.Clear();

            TClass *cl = gROOT->GetClass(key->GetClassName());

            // -- TH1 --
            if (cl->InheritsFrom("TH1") and ! cl->InheritsFrom("TH2")){ // second requirement is because TH2 also inherits from TH1

                // Get a reference histogram for the name, then get all histograms in  a vector
                TH1F*   sample_hist_ref = (TH1F*)key->ReadObj();
                TString histname   = sample_hist_ref->GetName();
                //std::cout << histname << std::endl;

                if(histname.Index("_Bool_") != -1) continue; // don't plot the Bool histograms
                if(sample_hist_ref->GetMaximum() == 0) continue;
                if(!check_identifiers(histname, identifiers)) continue;

                THStack* hists = new THStack("stack", "");
                for(int i = 0; i < files.size(); i++){
                    if(files[i]->GetListOfKeys()->Contains(histname)){
                        TH1* hist = (TH1*)files[i]->Get(histname);
                        if(hist->GetMaximum() > 0){
                            hists->Add(hist);
                            hist->SetMarkerColor(colors[i]);
                            hist->SetLineColor(colors[i]);
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

                hists->Draw("E nostack");
                hists->GetXaxis()->SetTitle(sample_hist_ref->GetXaxis()->GetTitle());
                hists->GetYaxis()->SetTitle(sample_hist_ref->GetYaxis()->GetTitle());
                hists->SetMaximum(1.25*hists->GetMaximum("nostack"));
                legend.Draw("same");
                CMSandLumi->Draw();

                pad->Modified();
                c->Print(pathname_lin + histname + ".png");

                // Draw log version
                pad->Clear();
                pad->SetLogy(1);

                hists->Draw("E nostack");
                hists->GetXaxis()->SetTitle(sample_hist_ref->GetXaxis()->GetTitle());
                hists->GetYaxis()->SetTitle(sample_hist_ref->GetYaxis()->GetTitle());
                hists->SetMaximum(20*hists->GetMaximum("nostack"));
                hists->SetMinimum(10);
                legend.Draw("same");
                CMSandLumi->Draw();

                pad->Modified();
                c->Print(pathname_log + histname + ".png");




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
                    CMSandLumi->Draw();

                    pad->Modified();
                    c->Print(pathname_lin + histname(0, histname.Index("eff_num") + 3) + ".png");
                }
            }
            else if(cl->InheritsFrom("TH2")){
                // Get a reference histogram for the name, then get all histograms in  a vector later
                TH1F*   sample_hist_ref = (TH1F*)key->ReadObj();
                TString histname   = sample_hist_ref->GetName();
                TString xaxistitle = sample_hist_ref->GetXaxis()->GetTitle();
                TString yaxistitle = sample_hist_ref->GetYaxis()->GetTitle();
                std::cout << histname << std::endl;

                if(sample_hist_ref->GetMaximum() == 0) continue;
                if(general_pathname.Index("_ee") != -1 and histname.Index("_mm") != -1) continue;
                if(general_pathname.Index("_mm") != -1 and histname.Index("_ee") != -1) continue;

                //Make Scale and Resolution plots based on AbsScale histogram
                if(histname.Index("AbsScale") != -1){
                    pad->Clear();
                    pad->SetLogy(0);
                    legend.Clear();

                    TString pathname_lin    = make_plotspecific_pathname(histname, general_pathname, "lin/");
                    TString pathname_log    = make_plotspecific_pathname(histname, general_pathname, "log/");
                    gSystem->Exec("mkdir -p " + pathname_lin + "resolution/");
                    gSystem->Exec("mkdir -p " + pathname_log + "resolution/");


                    //1) make profile of the histogram to get <u_para> vs qT
                    std::vector<TH2*> hists;
                    std::vector<TProfile*> profiles;
                    for(int i = 0; i < files.size(); i++){
                        // profile is <u_para> vs qT
                        hists.push_back((TH2*)files[i]->Get(histname));
                        hists[i]->SetLineColor(colors[i]);
                        hists[i]->SetMarkerColor(colors[i]);
                        profiles.push_back(hists[i]->ProfileX(histname + "_" + legends[i] + "_profile"));
                        profiles[i]->SetLineColor(colors[i]);
                        profiles[i]->SetMarkerColor(colors[i]);
                        legend.AddEntry(profiles[i], legends[i], "pl");
                    }
                    draw_profiles(c, pad, profiles, pathname_lin + histname + "_profile.png", &legend, xaxistitle, "<" + yaxistitle + ">", CMSandLumi);


                    // Draw -<upara>/<qT> as a function of qT (<upara> has been calculated by the profileX, <qT> is simply the bin center)
                    if(histname.Index("_vsqT") != -1){
                        pad->Clear();
                        pad->SetLogy(0);
                        legend.Clear();

                        // calculate <qT> vs qT, then calculate -<upara>/<qT> in the profiles
                        std::vector<TH1*> hists_meanqT;
                        for(int i = 0; i < files.size(); i++){
                            //find corresponding meanqT histname by adapting absScale histname
                            TString meanqT_histname = histname(0, histname.Index("AbsScale_vsqT")) + "meanqT_vsqT_num";
                            //meanqT_histname.ReplaceAll("AbsScale_vsqT", "meanqT_vsqT_num").ReplaceAll("_met", "").ReplaceAll("Raw", "").ReplaceAll("_uperp", "").ReplaceAll("XY", "").ReplaceAll("PuppiRaw", "").ReplaceAll("Puppi", "");
                            //make a copy of the numerator histogram, then divide it by the denominator histogram
                            hists_meanqT.push_back((TH1*)files[i]->Get(meanqT_histname)->Clone(meanqT_histname + std::to_string(i)));
                            if(hists_meanqT[i] == 0 or hists_meanqT[i]->GetMaximum() == 0) continue;
                            hists_meanqT[i]->Divide(hists_meanqT[i], (TH1*)files[i]->Get(meanqT_histname.ReplaceAll("vsqT_num", "vsqT_den")), 1, 1, "b");
                            hists_meanqT[i]->SetLineColor(colors[i]);
                            hists_meanqT[i]->SetMarkerColor(colors[i]);

                            legend.AddEntry(hists_meanqT[i], legends[i], "pl");
                            for(int i_bin = 1; i_bin <= hists_meanqT[i]->GetNbinsX(); i_bin++) hists_meanqT[i]->SetBinError(i_bin, 0.);
                            profiles[i]->Divide(hists_meanqT[i]);
                        }

                        // Uncomment these lines if you want to see the mean qT histogram for each calculation of response
                        //hists_meanqT[0]->Draw("E0 P");
                        //for(int i = 1; i < hists_meanqT.size(); i++) hists_meanqT[i]->Draw("same E0 P");
                        //legend.Draw("same");
                        //CMSandLumi->Draw();

                        //pad->Modified();
                        //c->Print(pathname_lin + histname + "_meanqT.png");
                        pad->Clear();
                        legend.Clear();

                        TMultiGraph* multigraph = new TMultiGraph();
                        multigraph->SetTitle((TString)";" + xaxistitle + ";-<" + yaxistitle + ">/<q_{T}>");
                        for(int i = 0; i < files.size(); i++){
                            int nbins = hists[i]->GetNbinsX();
                            double x[nbins], y[nbins], ex[nbins], ey[nbins];
                            for(int i_bin = 1; i_bin <= nbins; i_bin++){
                                x[i_bin-1] = hists[i]->GetXaxis()->GetBinCenter(i_bin);
                                y[i_bin-1] = - profiles[i]->GetBinContent(i_bin);
                                ex[i_bin-1] = hists[i]->GetXaxis()->GetBinWidth(i_bin)/2;
                                ey[i_bin-1] = profiles[i]->GetBinError(i_bin);
                            }
                            TGraphErrors* graph = new TGraphErrors(nbins, x, y, ex, ey);
                            graph->SetLineColor(colors[i]);
                            graph->SetMarkerColor(colors[i]);
                            multigraph->Add(graph);
                            legend.AddEntry(graph, legends[i], "pl");
                        }

                        multigraph->Draw("AP");
                        multigraph->SetMaximum(1.1);
                        multigraph->SetMinimum(0.65);
                        draw_line_at_1(multigraph->GetXaxis()->GetXmin(), multigraph->GetXaxis()->GetXmax());
                        //multigraph->SetMaximum(1.1*multigraph->GetHistogram()->GetMaximum());
                        legend.Draw("same");
                        CMSandLumi->Draw();

                        pad->Modified();
                        c->Print(pathname_lin + histname + "_response.png");
                        pad->Clear();
                        pad->SetLogy(0);
                        legend.Clear();
                    }

                    // Draw Resolution of upara and uperp using fit to a voigtian function
                    TMultiGraph* multigraph = new TMultiGraph();
                    multigraph->SetTitle((TString)";" + xaxistitle + ";#sigma(" + yaxistitle + ")");
                    for(int i = 0; i < hists.size(); i++){
                        int nbins = hists[i]->GetNbinsX();
                        double x[nbins], FWHM[nbins], exl[nbins], exh[nbins], eFWHMl[nbins], eFWHMh[nbins];

                        for(int i_bin = 1; i_bin <= nbins; i_bin++){
                            pad->Clear();
                            pad->SetLogy(0);
                            legend_profiles.Clear();

                            TH1D* projection = hists[i]->ProjectionY(histname + "_" + legends[i] + "_projection_" + std::to_string(i_bin), i_bin, i_bin, "e");

                            projection->Rebin(8);
                            //if(histname.Contains("_vsnPV")) projection->Rebin(8);
                            //if(hists[i]->GetXaxis()->GetBinLowEdge(i_bin) == 240) projection->Rebin(2);
                            //else if(hists[i]->GetXaxis()->GetBinLowEdge(i_bin) == 320) projection->Rebin(4);
                            //else if(hists[i]->GetXaxis()->GetBinLowEdge(i_bin) == 400) projection->Rebin(4);

                            legend_profiles.AddEntry(projection, legends[i]);
                            TF1* voigt = new TF1("voigt", "[0]*TMath::Voigt(x - [1], [2], [3], 4) + [4]", projection->GetXaxis()->GetXmin(), projection->GetXaxis()->GetXmax());
                            voigt->SetLineColor(kGreen+3);
                            voigt->SetLineWidth(2);

                            if(projection->GetMaximum() > 0){
                                // perform fit
                                voigt->SetParameters(projection->Integral()*2., projection->GetBinCenter(projection->GetMaximumBin()), projection->GetRMS(), 1, 1);
                                projection->Fit(voigt, "WL 0");
                                x[i_bin] = hists[i]->GetXaxis()->GetBinCenter(i_bin);
                                exl[i_bin] = hists[i]->GetXaxis()->GetBinWidth(i_bin)/2;
                                exh[i_bin] = hists[i]->GetXaxis()->GetBinWidth(i_bin)/2;
                                FWHM[i_bin] = get_FWHM(voigt)/(2*sqrt(2*log(2)));
                                eFWHMl[i_bin] = get_eFWHM(voigt, FWHM[i_bin], voigt->GetParameter(2) - voigt->GetParError(2));
                                eFWHMh[i_bin] = get_eFWHM(voigt, FWHM[i_bin], voigt->GetParameter(2) + voigt->GetParError(2));
                                pad->Clear();
                                pad->SetLogy(0);

                                projection->Draw();
                                legend_profiles.Draw("same");
                                voigt->Draw("C same");
                                CMSandLumi->Draw();
                                std::ostringstream chi2stream;
                                chi2stream << 0.01*round(100*voigt->GetChisquare()/voigt->GetNDF());
                                std::ostringstream FWHMstream;
                                FWHMstream << 0.01*round(100*FWHM[i_bin]);
                                chi2latex.DrawLatex(1 - rightmargin*1.8, 1 - 2.2*topmargin, (TString)"#chi^{2}_{norm}: " + chi2stream.str());
                                FWHMlatex.DrawLatex(1 - rightmargin*1.8, 1 - 3.3*topmargin, (TString)"FWHM: " + FWHMstream.str());

                                pad->Modified();
                                c->Print(pathname_lin + "resolution/" + histname + "_resolution_" + legends[i] + "_range" + std::to_string((int)hists[i]->GetXaxis()->GetBinLowEdge(i_bin)) + "to" + std::to_string((int)hists[i]->GetXaxis()->GetBinUpEdge(i_bin)) + ".png");

                                // Draw log version
                                pad->Clear();
                                pad->SetLogy(1);

                                projection->Draw();
                                legend_profiles.Draw("same");
                                voigt->Draw("C same");
                                CMSandLumi->Draw();
                                chi2latex.DrawLatex(1 - rightmargin*1.8, 1 - 2.2*topmargin, (TString)"#chi^{2}_{norm}: " + chi2stream.str());
                                FWHMlatex.DrawLatex(1 - rightmargin*1.8, 1 - 3.3*topmargin, (TString)"FWHM: " + FWHMstream.str());

                                pad->Modified();
                                c->Print(pathname_log + "resolution/" + histname + "_resolution_" + legends[i] + "_range" + std::to_string((int)hists[i]->GetXaxis()->GetBinLowEdge(i_bin)) + "to" + std::to_string((int)hists[i]->GetXaxis()->GetBinUpEdge(i_bin)) + ".png");
                            } else {
                                x[i_bin] = 0;
                                exl[i_bin] = 0;
                                exh[i_bin] = 0;
                                FWHM[i_bin] = 0;
                                eFWHMl[i_bin] = 0;
                                eFWHMh[i_bin] = 0;
                            }
                        }

                        // Draw FWHM graph as a function of x
                        TGraphAsymmErrors* graph = new TGraphAsymmErrors(nbins, x, FWHM, exl, exh, eFWHMl, eFWHMh);
                        graph->SetLineColor(colors[i]);
                        graph->SetMarkerColor(colors[i]);
                        multigraph->Add(graph);
                        legend.AddEntry(graph, legends[i], "pl");
                    }

                    pad->Clear();
                    pad->SetLogy(0);

                    multigraph->Draw("AP");
                    multigraph->SetMaximum(60);
                    multigraph->SetMinimum(0);
                    legend.Draw("same");
                    CMSandLumi->Draw();

                    pad->Modified();
                    c->Print(pathname_lin + histname + "_resolution.png");
                }
            }
            ++counter;
        }
    }
}
# endif
