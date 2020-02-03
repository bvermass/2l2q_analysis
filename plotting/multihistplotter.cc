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

    //this color scheme comes from the coolors.co app: https://coolors.co/4281ae-0a5a50-4b4237-d4b483-c1666b
    //maybe this combo is better: https://coolors.co/4281ae-561643-4b4237-d4b483-c1666b?
    std::vector<std::vector<int>> rgb = {{66, 129, 174}, {212, 180, 131}, {193, 102, 107}, {10, 90, 80}, {75, 66, 65}};
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

    TLegend legend = get_legend(0.18, 0.84, 0.95, 0.93, 3);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad);
    float leftmargin  = pad->GetLeftMargin();
    float topmargin   = pad->GetTopMargin();
    float rightmargin = pad->GetRightMargin();

    TLatex chi2latex = get_latex(0.8*topmargin, 31, 42);
    TLatex FWHMlatex = get_latex(0.8*topmargin, 31, 42);

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

            hists->Draw("hist nostack");
            hists->GetXaxis()->SetTitle(sample_hist_ref->GetXaxis()->GetTitle());
            hists->GetYaxis()->SetTitle(sample_hist_ref->GetYaxis()->GetTitle());
            hists->SetMaximum(1.25*hists->GetMaximum("nostack"));
            legend.Draw("same");
            CMSandLumi->Draw();
            
            pad->Modified();
            c->Print(pathname_lin + histname + ".pdf");

            // Draw log version
            pad->Clear();
            pad->SetLogy(1);

            hists->Draw("hist nostack");
            hists->GetXaxis()->SetTitle(sample_hist_ref->GetXaxis()->GetTitle());
            hists->GetYaxis()->SetTitle(sample_hist_ref->GetYaxis()->GetTitle());
            hists->SetMaximum(10*hists->GetMaximum("nostack"));
            legend.Draw("same");
            CMSandLumi->Draw();
            
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
                c->Print(pathname_lin + histname(0, histname.Index("eff_num") + 3) + ".pdf");
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

            //Make Scale and Resolution plots based on AbsScale histogram
            if(histname.Index("AbsScale") != -1){
                pad->Clear();
                pad->SetLogy(0);
                legend.Clear();

                TString pathname_lin    = make_plotspecific_pathname(histname, general_pathname, "lin/");
                gSystem->Exec("mkdir -p " + pathname_lin + "resolution/");


                //1) make profile of the histogram to get <u_para> vs qT
                std::vector<TH2*> hists;
                std::vector<TProfile*> profiles;
                for(int i = 0; i < files.size(); i++){
                    // profile is <u_para> vs qT
                    hists.push_back((TH2*)files[i]->Get(histname));
                    profiles.push_back(hists[i]->ProfileX(histname + "_" + legends[i] + "_profile"));
                    legend.AddEntry(profiles[i], legends[i], "pl");
                }
                draw_profiles(c, pad, profiles, pathname_lin + histname + "_profile.pdf", &legend, xaxistitle, "<" + yaxistitle + ">", CMSandLumi);


                // Draw -<upara>/<qT> as a function of qT (<upara> has been calculated by the profileX, <qT> is simply the bin center)
                if(histname.Index("_vsqT") != -1){
                    pad->Clear();
                    pad->SetLogy(0);
                    legend.Clear();

                    // calculate <qT> vs qT, then calculate -<upara>/<qT> in the profiles
                    std::vector<TH1*> hists_meanqT;
                    for(int i = 0; i < files.size(); i++){
                        TString meanqT_histname = histname;
                        meanqT_histname.ReplaceAll("AbsScale_vsqT", "meanqT_vsqT_num").ReplaceAll("_metRaw", "").ReplaceAll("_uperp", "");
                        hists_meanqT.push_back((TH1*)files[i]->Get(meanqT_histname));
                        hists_meanqT[i]->Divide(hists_meanqT[i], (TH1*)files[i]->Get(meanqT_histname.ReplaceAll("vsqT_num", "vsqT_den")), 1, 1, "b");
                        legend.AddEntry(hists_meanqT[i], legends[i], "pl");
                        for(int i_bin = 1; i_bin <= hists_meanqT[i]->GetNbinsX(); i_bin++) hists_meanqT[i]->SetBinError(i_bin, 0.);
                        profiles[i]->Divide(hists_meanqT[i]);
                    }

                    hists_meanqT[0]->Draw("pmc plc");
                    for(int i = 1; i < hists_meanqT.size(); i++) hists_meanqT[i]->Draw("same pmc plc");
                    legend.Draw("same");
                    CMSandLumi->Draw();

                    pad->Modified();
                    c->Print(pathname_lin + histname + "_meanqT.pdf");
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
                        multigraph->Add(graph);
                        legend.AddEntry(graph, legends[i], "pl");
                    }

                    multigraph->Draw("AP pmc plc");
                    multigraph->SetMaximum(1.1*multigraph->GetHistogram()->GetMaximum());
                    legend.Draw("same");
                    CMSandLumi->Draw();

                    pad->Modified();
                    c->Print(pathname_lin + histname + "_response.pdf");
                    pad->Clear();
                    pad->SetLogy(0);
                    legend.Clear();
                }

                // Draw Resolution of upara and uperp using fit to a voigtian function
                TMultiGraph* multigraph = new TMultiGraph();
                multigraph->SetTitle((TString)";" + xaxistitle + ";#sigma(" + yaxistitle + ")");
                for(int i = 0; i < hists.size(); i++){
                    int nbins = hists[i]->GetNbinsX();
                    double x[nbins], FWHM[nbins], ex[nbins], eFWHM[nbins];

                    for(int i_bin = 1; i_bin <= nbins; i_bin++){
                        pad->Clear();
                        pad->SetLogy(0);
                        legend.Clear();

                        TH1D* projection = hists[i]->ProjectionY(histname + "_" + legends[i] + "_projection_" + std::to_string(i_bin), i_bin, i_bin, "e");
                        legend.AddEntry(projection, legends[i]);
                        TF1* voigt = new TF1("voigt", "[0]*TMath::Voigt(x - [1], [2], [3], 4) + [4]*x + [5]", projection->GetXaxis()->GetXmin(), projection->GetXaxis()->GetXmax());
                        voigt->SetLineColor(kGreen+3);
                        voigt->SetLineWidth(2);

                        if(projection->GetMaximum() > 0){
                            // perform fit
                            voigt->SetParameters(projection->Integral(), projection->GetMean(), projection->GetRMS(), 1, 0, 0);
                            projection->Fit(voigt, "0");
                            x[i_bin] = hists[i]->GetXaxis()->GetBinCenter(i_bin);
                            ex[i_bin] = hists[i]->GetXaxis()->GetBinWidth(i_bin)/2;
                            FWHM[i_bin] = get_FWHM(voigt);
                            eFWHM[i_bin] = 0;

                            projection->Draw();
                            legend.Draw("same");
                            voigt->Draw("C same");
                            CMSandLumi->Draw();
                            chi2latex.DrawLatex(1 - rightmargin*1.8, 1 - 2.2*topmargin, (TString)"#chi^{2}_{norm}: " + std::to_string((int)round(voigt->GetChisquare()/voigt->GetNDF())));
                            FWHMlatex.DrawLatex(1 - rightmargin*1.8, 1 - 3.3*topmargin, (TString)"FWHM: " + std::to_string((int)FWHM[i_bin]));

                            pad->Modified();
                            c->Print(pathname_lin + "resolution/" + histname + "_resolution_" + legends[i] + "_range" + std::to_string((int)hists[i]->GetXaxis()->GetBinLowEdge(i_bin)) + "to" + std::to_string((int)hists[i]->GetXaxis()->GetBinUpEdge(i_bin)) + ".pdf");
                        } else {
                            x[i_bin] = 0;
                            ex[i_bin] = 0;
                            FWHM[i_bin] = 0;
                            eFWHM[i_bin] = 0;
                        }
                    }

                    // Draw FWHM graph as a function of x
                    TGraphErrors* graph = new TGraphErrors(nbins, x, FWHM, ex, eFWHM);
                    multigraph->Add(graph);
                    legend.AddEntry(graph, legends[i], "pl");
                }

                multigraph->Draw("AP pmc plc");
                multigraph->SetMaximum(1.15*multigraph->GetHistogram()->GetMaximum());
                legend.Draw("same");
                CMSandLumi->Draw();

                pad->Modified();
                c->Print(pathname_lin + histname + "_resolution.pdf");
            }
        }
    }
}
# endif
