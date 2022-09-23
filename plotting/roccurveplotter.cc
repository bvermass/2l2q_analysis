#include "roccurveplotter.h"

std::vector<TString> get_V2s(double mass)
{
    if(mass >= 5) return {"5e-07", "9e-07", "4e-06", "8e-06", "3e-05"};
    else if(mass == 4) return {"9e-07", "4e-06", "8e-06", "3e-05"};
    else if(mass == 3) return {"4e-06", "8e-06", "3e-05", "7e-05"};
    else if(mass == 2) return {"8e-06", "3e-05", "7e-05", "9e-05"};
    else{
        std::cout << "Warning: if you want plot vs V2 for mass " << mass << " then include it in the code" << std::endl;
        return {};
    }
}



bool plot_extra_hists_with_different_names(TCanvas* c, TMultiGraph* multigraph, TLegend* legend, std::vector<TFile*> files_signal, std::vector<TFile*> files_bkg, std::vector<TString> legends, std::vector<TString> histnames, std::vector<int> colors)
{
    // To plot multiple roc curves in 1 plot, if the histograms have different names
    c->Clear();
    multigraph->Clear();

    for(int i_hist = 0; i_hist < histnames.size(); i_hist++){
        for(int i = 0; i < files_signal.size(); i++){
            TH1F* hist_signal = (TH1F*) files_signal[i]->Get(histnames[i_hist]);
            TH1F* hist_bkg    = (TH1F*) files_bkg[i]->Get(histnames[i_hist]);
            if(!hist_signal or !hist_bkg) return false;

            std::vector< double > eff_signal = computeEfficiencyForROC(hist_signal);
            std::vector< double > eff_bkg    = computeEfficiencyForROC(hist_bkg);
            TGraph* roc = get_roc(eff_signal, eff_bkg);
            roc->SetLineColor(colors[i_hist]);
            multigraph->Add(roc);
            double auc = computeAUC(roc);
            TString auc_str = std::to_string(auc).substr(0, std::to_string(auc).find(".") + 3);
            legend->AddEntry(roc, legends[i_hist] + ": " + auc_str, "l");
        }
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
    // Argument 2: legend of first roc curve
    // Argement 2: name of signal input file  
    // Argument 3: name of bkg input file
    // Argument 4, 5, 6 onwards, do same again
    
    std::vector<TFile*> files_signal;
    std::vector<TFile*> files_bkg;
    std::vector<TString> legends;
    bool is2016 = false, is2017 = false, is2018 = false, isRun2 = true;
    for(int i = 2; i < argc; i++){
        std::cout << argv[i] << std::endl;
        TString argument = (TString)argv[i];
        if(i%3 == 2) legends.push_back(argument);
        else if(i%3 == 0) files_signal.push_back(TFile::Open(argument));
        else if(i%3 == 1) files_bkg.push_back(TFile::Open(argument));

        if(argument.Contains("MiniAOD2016") or argument.Contains("Run2016")) is2016 = true;
        else if(argument.Contains("MiniAOD2017") or argument.Contains("Run2017")) is2017 = true;
        else if(argument.Contains("MiniAOD2018") or argument.Contains("Run2018")) is2018 = true;
        else if(argument.Contains("MiniAODRun2") or argument.Contains("Run2.")) isRun2 = true;
        else if(argument.Contains("MiniAOD1617") or argument.Contains("Run1617")){ is2016 = true; is2017 = true; }
        else if(argument.Contains("MiniAOD1618") or argument.Contains("Run1618")){ is2016 = true; is2018 = true; }
        else if(argument.Contains("MiniAOD1718") or argument.Contains("Run1718")){ is2017 = true; is2018 = true; }
    }

    //this color scheme comes from the coolors.co app: https://coolors.co/4281ae-0a5a50-4b4237-d4b483-c1666b
    //maybe this combo is better: https://coolors.co/4281ae-561643-4b4237-d4b483-c1666b?
    //std::vector<std::vector<int>> rgb = {{66, 129, 174}, {212, 180, 131}, {193, 102, 107}, {10, 90, 80}, {75, 66, 65}, {86, 22, 67}, {247, 135, 100}};
    std::vector<std::vector<int>> rgb = {{46, 114, 204}, {239, 32, 29}, {29, 182, 0}, {86, 14, 118}, {232, 164, 0}, {86, 22, 67}, {247, 135, 100}, {47, 41, 35}};
    std::vector<int> colors;
    for(int i = 0; i < rgb.size(); i++){
        colors.push_back(TColor::GetColor(rgb[i][0], rgb[i][1], rgb[i][2]));
    }

    // Name of directory where plots will end up
    TString specific_dir = (TString)argv[1];
    std::cout << specific_dir << std::endl;
    TString general_pathname = make_general_pathname("plots_new/roccurves/", specific_dir + "/");
    //gSystem->Exec("rm " + general_pathname + "Signal_Bkg_Yields.txt");

    // Read identifiers from plotting/identifiers.txt and only make plots matching these tags
    std::vector<std::vector<TString>> identifiers = get_identifiers("plotting/identifiers.txt", ",");

    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    // Make the pad that will contain the plot
    TPad* pad  = new TPad("pad", "", 0., 0., 1., 1.);
    pad->Draw();
    pad->cd();

    TLegend legend = get_legend(0.57, 0.15, 1, 0.075 + 0.075*legends.size(), 1);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad, is2016, is2017, is2018, isRun2);
    float leftmargin  = pad->GetLeftMargin();
    float topmargin   = pad->GetTopMargin();
    float rightmargin = pad->GetRightMargin();

    std::vector< std::map< TString, double > > auc; // Vector for different files, map <V2, auc>
    for(int i = 0; i < files_signal.size(); i++) auc.push_back(std::map<TString, double>());

    TIter next(files_signal.front()->GetListOfKeys()); //Take signal to get relevant roc curves of that mass
    TKey* key;
    while(key = (TKey*)next()){
        legend.Clear();
        std::string cl(key->GetClassName());

        // -- TH1 --
        if(cl.find("TH1") != std::string::npos){
            
            // Get a reference histogram for the name, then get all histograms in  a vector
            TH1F*   sample_hist_ref = (TH1F*)key->ReadObj();
            TString histname   = sample_hist_ref->GetName();
            if(histname.Index("_ROC") == -1 or histname.Index("_M-") == -1 or histname.Index("_V2-") == -1 or histname.Index("_Training") != -1 or histname.Index("_after") != -1) continue;
            if(!check_identifiers(histname, identifiers)) continue;
            std::cout << histname << std::endl;
            
            // get plot specific pathnames
            TString pathname_lin    = make_plotspecific_pathname(histname, general_pathname, "lin/");
            TString pathname_log    = make_plotspecific_pathname(histname, general_pathname, "log/");

            // for parametrized PFN, put evaluated mass and V2 in legend
            //if(histname.Contains("_M-") and histname.Contains("_V2-")) legend.SetHeader(((TString)histname(histname.Index("_M-") + 1, histname.Index("e-0") - histname.Index("_M-") + 3)).ReplaceAll("_", " ") + " [AUC] - [Bkg eff] - [cut]");
            if(histname.Contains("_M-") and histname.Contains("_V2-")) legend.SetHeader(histname.Contains("M-5")? "Low Mass PFN: AUC" : "High Mass PFN: AUC");

            TMultiGraph* multigraph = new TMultiGraph();
            multigraph->SetTitle((TString)";Bkg Eff.;Signal Eff.");
            bool valid_graph = false;
            for(int i = 0; i < files_signal.size(); i++){
                //auc.push_back(get_roc_and_auc(multigraph, histname, files_signal[i], files_bkg[i]);
                TH1F* hist_signal = (TH1F*) files_signal[i]->Get(histname);
                TH1F* hist_bkg    = (TH1F*) files_bkg[i]->Get(histname);
                if(!hist_signal or !hist_bkg or hist_signal->GetMaximum() <= 0 or hist_bkg->GetMaximum() <= 0) continue;
                
                std::vector< double > eff_signal = computeEfficiencyForROC(hist_signal);
                std::vector< double > eff_bkg    = computeEfficiencyForROC(hist_bkg);

                std::tuple<double,double, double> cp;
                // calculate cutting point to get 75% signal efficiency for PFN or BDT
                if(histname.Index("PFN") != -1 or histname.Index("BDT") != -1) computeCuttingPoint(eff_signal, eff_bkg, hist_signal, hist_bkg, 0.70, general_pathname, histname);
                if(histname.Index("PFN") != -1 or histname.Index("BDT") != -1) computeCuttingPoint(eff_signal, eff_bkg, hist_signal, hist_bkg, 0.75, general_pathname, histname);
                if(histname.Index("PFN") != -1 or histname.Index("BDT") != -1) computeCuttingPoint(eff_signal, eff_bkg, hist_signal, hist_bkg, 0.80, general_pathname, histname);
                if(histname.Index("PFN") != -1 or histname.Index("BDT") != -1) computeCuttingPoint(eff_signal, eff_bkg, hist_signal, hist_bkg, 0.85, general_pathname, histname);
                if(histname.Index("PFN") != -1 or histname.Index("BDT") != -1) cp = computeCuttingPoint(eff_signal, eff_bkg, hist_signal, hist_bkg, 0.90, general_pathname, histname);
                if(histname.Index("PFN") != -1 or histname.Index("BDT") != -1) computeCuttingPoint(eff_signal, eff_bkg, hist_signal, hist_bkg, 0.95, general_pathname, histname);


                TGraph* roc = get_roc(eff_signal, eff_bkg);
                roc->SetLineColor(colors[i]);
                multigraph->Add(roc);
                valid_graph = true;
                auc[i][histname] = computeAUC(roc);
                TString auc_str = std::to_string(auc[i][histname]).substr(0, std::to_string(auc[i][histname]).find(".") + 3);
                TString sig_eff_str = std::to_string(0.01 * round(100*std::get<0>(cp))).substr(0,4);
                TString bkg_eff_str = std::to_string(0.0001 * round(10000*std::get<1>(cp))).substr(0,6);
                TString cut_eff_str = std::to_string(0.001 * round(1000*std::get<2>(cp))).substr(0,5);
                legend.AddEntry(roc, legends[i] + ": " + auc_str/* + " - " + bkg_eff_str + " - " + cut_eff_str*/, "l");
            }


            pad->Clear();
            pad->SetLogx(0);
            pad->SetLogy(0);
            if(valid_graph){
                multigraph->Draw("AL");


                multigraph->GetXaxis()->SetLimits(-0.02, 0.2);
                multigraph->SetMinimum(0.7);
                multigraph->SetMaximum(1.02);

                legend.Draw("same");
                CMSandLumi->add_flavor(histname);
                CMSandLumi->Draw();

                pad->Modified();
                c->Print(pathname_lin + histname + ".png");
            }

            // Plot ROC for several V2 (only for plots with 1 sig-bkg combo):
            if(histname.Index("_V2-3e-05") != -1 and files_signal.size() == 1 and histname.Index("_M-") != -1){
                legend.Clear();

                TString mass = histname(histname.Index("_M-") + 3, histname.Index("_V2-") - histname.Index("_M-") - 3);
                std::vector<TString> newV2s = get_V2s(mass.Atof());

                std::vector<TString> histnamesV2;
                std::vector<TString> legendsV2;
                for(const TString& newV2 : newV2s){
                    TString tmpname = histname;
                    histnamesV2.push_back(tmpname.ReplaceAll("3e-05", newV2));
                    legendsV2.push_back("M-" + mass + "V2-" + newV2);
                }

                if(plot_extra_hists_with_different_names(c, multigraph, &legend, files_signal, files_bkg, legendsV2, histnamesV2, colors)){
                    CMSandLumi->add_flavor(histname);
                    CMSandLumi->Draw();

                    histname.ReplaceAll("_V2-3e-05", "_vsV2");
                    pathname_lin.ReplaceAll("_V2-3e-05", "_vsV2");
                    gSystem->Exec("mkdir -p " + pathname_lin);

                    pad->Modified();
                    c->Print(pathname_lin + histname + ".png");

                    multigraph->GetXaxis()->SetRangeUser(0., 0.1);
                    multigraph->GetYaxis()->SetRangeUser(0.7, 1.);

                    pad->Modified();
                    c->Print(pathname_lin + histname + "_zoom.png");

                    //pad->SetLogx(1);
                    //pad->Modified();
                    //pad->Print(pathname_log + histname + "_zoom.png");
                }
            }
            // Plot PFN vs BDT
            //if(histname.Index("PFN") != -1){ 
            //    if(plot_PFNvsBDT(c, multigraph, &legend, histname, files_signal, files_bkg, legends)){
            //        CMSandLumi->add_flavor(histname);
            //        CMSandLumi->Draw();

            //        histname.ReplaceAll("PFN", "PFNvsBDT");
            //        pad->Modified();
            //        c->Print(pathname_lin + histname + ".png");

            //        multigraph->GetXaxis()->SetRangeUser(0., 0.1);
            //        multigraph->GetYaxis()->SetRangeUser(0.7, 1.);

            //        pad->Modified();
            //        c->Print(pathname_lin + histname + "_zoom.png");

            //        pad->SetLogx(1);
            //        pad->Modified();
            //        c->Print(pathname_log + histname + "_zoom.png");
            //    }
            //}
        }
    }


    // Use stored auc values to make plots vs V2
    //TMultiGraph* multigraph = new TMultiGraph();
    //multigraph->SetTitle((TString)";|V|^{2};auc");
    pad->SetLogx(1);
    for(int i = 0; i < auc.size(); i++){

        for(auto& auc_withname : auc[i]){
            TString histname = auc_withname.first;
            if(histname.Contains("V2-3e-05")){
                legend.Clear();

                TString mass = histname(histname.Index("_M-") + 3, histname.Index("_V2-") - histname.Index("_M-") - 3);

                std::vector<double> auc_for_graph;
                std::vector<double> V2s = get_evaluating_V2s(mass.Atof());
                for(double V2 : V2s){
                    TString MV2name = get_MV2name(mass.Atof(), V2);
                    TString histname_new = histname(0, histname.Index("_M-")) + MV2name + "_PFN_ROC";
                    auc_for_graph.push_back(auc[i][histname_new]);
                }

                TGraph* auc_graph = new TGraph(V2s.size(), &V2s[0], &auc_for_graph[0]);
                auc_graph->SetTitle((TString)";|V|^{2};auc");
                auc_graph->SetLineColor(colors[0]);
                auc_graph->SetMarkerColor(colors[0]);
                legend.AddEntry(auc_graph, "M-"+mass);
                TString pathname_lin    = make_plotspecific_pathname(histname, general_pathname, "lin/");
                histname.ReplaceAll("V2-3e-05", "vsV2_AUC");
                pathname_lin.ReplaceAll("_V2-3e-05", "_vsV2");
                gSystem->Exec("mkdir -p " + pathname_lin);

                auc_graph->Draw("AP");
                auc_graph->SetMaximum(100);
                legend.Draw("same");
                CMSandLumi->add_flavor(histname);
                CMSandLumi->Draw();

                pad->Modified();
                c->Print(pathname_lin + histname + ".png");
            }
        }
    }
}
#endif
