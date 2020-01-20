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


TGraph* get_roc(std::vector< double > eff_signal, std::vector< double > eff_bkg)
{
    TGraph* roc = new TGraph(eff_signal.size(), &(eff_bkg[0]), &(eff_signal[0]));
    roc->SetLineWidth(2);
    return roc;
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

    multigraph->Draw("AC");
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
    for(int i = 2; i < argc; i++){
        std::cout << argv[i] << std::endl;
        TString argument = (TString)argv[i];
        if(i%3 == 2) legends.push_back(argument);
        else if(i%3 == 0) files_signal.push_back(TFile::Open(argument));
        else if(i%3 == 1) files_bkg.push_back(TFile::Open(argument));
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

    std::vector< std::map< TString, double > > auc; // Vector for different files, map <V2, auc>
    for(int i = 0; i < files_signal.size(); i++) auc.push_back(std::map<TString, double>());

    TIter next(files_signal.front()->GetListOfKeys()); //Take signal to get relevant roc curves of that mass
    TKey* key;
    while(key = (TKey*)next()){
        legend.Clear();
        TClass *cl = gROOT->GetClass(key->GetClassName());

        // -- TH1 --
        if (cl->InheritsFrom("TH1") and ! cl->InheritsFrom("TH2")){ // second requirement is because TH2 also inherits from TH1
            
            // Get a reference histogram for the name, then get all histograms in  a vector
            TH1F*   sample_hist_ref = (TH1F*)key->ReadObj();
            TString histname   = sample_hist_ref->GetName();
            if(histname.Index("_ROC") == -1 or histname.Index("_M-") == -1 or histname.Index("_V2-") == -1 or histname.Index("_Training") != -1 or histname.Index("_after") != -1) continue;
            std::cout << histname << std::endl;
            
            // get plot specific pathnames
            TString pathname_lin    = make_plotspecific_pathname(histname, general_pathname, "lin/");
            TString pathname_log    = make_plotspecific_pathname(histname, general_pathname, "log/");

            TMultiGraph* multigraph = new TMultiGraph();
            multigraph->SetTitle((TString)";Bkg Eff.;Signal Eff.");
            for(int i = 0; i < files_signal.size(); i++){
                //auc.push_back(get_roc_and_auc(multigraph, histname, files_signal[i], files_bkg[i]);
                TH1F* hist_signal = (TH1F*) files_signal[i]->Get(histname);
                TH1F* hist_bkg    = (TH1F*) files_bkg[i]->Get(histname);
                if(hist_signal->GetMaximum() <= 0 or hist_bkg->GetMaximum() <= 0) continue;

                
                std::vector< double > eff_signal = computeEfficiencyForROC(hist_signal);
                std::vector< double > eff_bkg    = computeEfficiencyForROC(hist_bkg);

                // calculate cutting point to get 75% signal efficiency for PFN or BDT
                if(histname.Index("PFN") != -1 or histname.Index("BDT") != -1) computeCuttingPoint(eff_signal, eff_bkg, hist_signal, hist_bkg, 0.70);
                if(histname.Index("PFN") != -1 or histname.Index("BDT") != -1) computeCuttingPoint(eff_signal, eff_bkg, hist_signal, hist_bkg, 0.75);
                if(histname.Index("PFN") != -1 or histname.Index("BDT") != -1) computeCuttingPoint(eff_signal, eff_bkg, hist_signal, hist_bkg, 0.80);
                if(histname.Index("PFN") != -1 or histname.Index("BDT") != -1) computeCuttingPoint(eff_signal, eff_bkg, hist_signal, hist_bkg, 0.85);
                if(histname.Index("PFN") != -1 or histname.Index("BDT") != -1) computeCuttingPoint(eff_signal, eff_bkg, hist_signal, hist_bkg, 0.90);
                if(histname.Index("PFN") != -1 or histname.Index("BDT") != -1) computeCuttingPoint(eff_signal, eff_bkg, hist_signal, hist_bkg, 0.95);

                TGraph* roc = get_roc(eff_signal, eff_bkg);
                roc->SetLineColor(colors[i]);
                multigraph->Add(roc);
                auc[i][histname] = computeAUC(roc);
                TString auc_str = std::to_string(auc[i][histname]).substr(0, std::to_string(auc[i][histname]).find(".") + 3);
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
                    CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);

                    histname.ReplaceAll("_V2-3e-05", "_vsV2");
                    pathname_lin.ReplaceAll("_V2-3e-05", "_vsV2");
                    gSystem->Exec("mkdir -p " + pathname_lin);

                    c->Modified();
                    c->Print(pathname_lin + histname + ".pdf");

                    multigraph->GetXaxis()->SetRangeUser(0., 0.1);
                    multigraph->GetYaxis()->SetRangeUser(0.7, 1.);

                    c->Modified();
                    c->Print(pathname_lin + histname + "_zoom.pdf");

                    //c->SetLogx(1);
                    //c->Modified();
                    //c->Print(pathname_log + histname + "_zoom.pdf");
                }
            }
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


    // Use stored auc values to make plots vs V2
    //TMultiGraph* multigraph = new TMultiGraph();
    //multigraph->SetTitle((TString)";|V|^{2};auc");
    c->SetLogx(1);
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
                CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);
                lumilatex.DrawLatex(1-rightmargin, 1-0.8*topmargin, lumitext);

                c->Modified();
                c->Print(pathname_lin + histname + ".pdf");
            }
        }
    }
}
#endif
