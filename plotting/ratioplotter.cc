#include "ratioplotter.h"

RatioPlot::RatioPlot(TPad* pad):
    Pad(pad),
    Central_Ratio(new TH1F("Central_Ratio", "", 1, 0, 1)),
    systunc_legend(get_legend(0.2, 0.3, 0.45, 0.4, 3))
{
    Pad->SetTopMargin(0.04);
    Pad->SetBottomMargin(0.3);
    Pad->Draw();
    Pad->cd();
    
    Central_Ratio->GetXaxis()->SetLabelSize(0.09);
    Central_Ratio->GetYaxis()->SetLabelSize(0.09);
    Central_Ratio->GetXaxis()->SetTitleSize(0.09);
    Central_Ratio->GetYaxis()->SetTitleSize(0.09);
    Central_Ratio->GetYaxis()->SetTitleOffset(0.7);
    Central_Ratio->SetMinimum(0);
    Central_Ratio->SetMaximum(2);
    
    std::vector<std::vector<int>> rgb = {{186,16,25}, {63,136,197}, {68,187,164}};
    for(int i = 0; i < rgb.size(); i++){
        colors.push_back(TColor::GetColor(rgb[i][0], rgb[i][1], rgb[i][2]));
    }
}

RatioPlot::~RatioPlot(){}

void RatioPlot::SetLogx(int xlog)
{
    Pad->SetLogx(xlog);
}

void RatioPlot::SetCentralRatio(TH1F* num, TH1F* den, TString xaxistitle, TString yaxistitle)
{
    Central_Ratio->SetBins(num->GetNbinsX(), num->GetXaxis()->GetXmin(), num->GetXaxis()->GetXmax());
    Central_Ratio->Divide(num, den);

    Central_Ratio->GetXaxis()->SetTitle(xaxistitle);
    Central_Ratio->GetYaxis()->SetTitle(yaxistitle);
    Central_Ratio->SetMinimum(0);
    Central_Ratio->SetMaximum(2);
}


std::vector<double> RatioPlot::GetVariations(TString variation_name, std::vector<TFile*> files_bkg, TH1F* MC_central)
{
    THStack* MC_varied = new THStack("MC_varied", ";;Events");
    varied_exists = false;
    for(int i = 0; i < files_bkg.size(); i++){
        TH1F* varied_hist = (TH1F*) files_bkg[i]->Get(variation_name);
        if(varied_hist){
            MC_varied->Add(varied_hist);
            varied_exists = true;
        }
    }

    std::vector<double> variations;
    if(varied_exists){
        for(int i = 1; i <= MC_central->GetNbinsX(); i++){
            TH1F* fullstack = (TH1F*)MC_varied->GetStack()->Last();
            variations.push_back((fullstack->GetBinContent(i) - MC_central->GetBinContent(i)) / MC_central->GetBinContent(i));
        }
    }else {
        for(int i = 1; i <= MC_central->GetNbinsX(); i++){
            variations.push_back(0.);
        }
    }
    
    // temp fix to not plot syst uncs for metXYPhi
    if(variation_name.Contains("metXYPhi")) varied_exists = false;
    return variations;
}


void RatioPlot::SetSystUncs_up_and_down(TString histname, std::vector<TFile*> files_bkg, std::vector<TString> systunc_names, std::vector<TString> legends, TH1F* MC_central)
{
    systunc_graphs.clear();
    for(int i_syst = 0; i_syst < systunc_names.size(); i_syst++){
        TString systunc_name_down = histname + systunc_names[i_syst] + "Down";
        TString systunc_name_up   = histname + systunc_names[i_syst] + "Up";

        std::vector<double> y_down = GetVariations(systunc_name_down, files_bkg, MC_central);
        std::vector<double> y_up   = GetVariations(systunc_name_up, files_bkg, MC_central);

        if(y_down.size() != 0 or y_up.size() != 0){
            std::vector<double> x_central, x_low, x_high, y_central, y_low, y_high;
            for(int i = 1; i <= Central_Ratio->GetNbinsX(); i++){
                x_central.push_back((double)Central_Ratio->GetXaxis()->GetBinCenter(i));
                x_low.push_back((double)x_central[i-1] - Central_Ratio->GetXaxis()->GetBinLowEdge(i));
                x_high.push_back((double)Central_Ratio->GetXaxis()->GetBinUpEdge(i) - x_central[i-1]);
                y_central.push_back(1.);
                if(y_down[i-1] < 0 and y_up[i-1] < 0){
                    y_low.push_back(fabs(std::min(y_down[i-1], y_up[i-1])));
                    y_high.push_back(0);
                }else if(y_down[i-1] < 0 and y_up[i-1] >= 0){
                    y_low.push_back(fabs(y_down[i-1]));
                    y_high.push_back(y_up[i-1]);
                }else if(y_down[i-1] >= 0 and y_up[i-1] < 0){
                    y_low.push_back(fabs(y_up[i-1]));
                    y_high.push_back(y_down[i-1]);
                }else {
                    y_low.push_back(0);
                    y_high.push_back(std::max(y_down[i-1], y_up[i-1]));
                }
            }

            systunc_graphs.push_back(new TGraphAsymmErrors(x_central.size(), &x_central[0], &y_central[0], &x_low[0], &x_high[0], &y_low[0], &y_high[0]));
            systunc_graphs[i_syst]->SetName(histname + systunc_names[i_syst]);
            systunc_graphs[i_syst]->SetFillColor(colors[i_syst]);
            systunc_graphs[i_syst]->SetLineColor(colors[i_syst]);
            systunc_graphs[i_syst]->SetMarkerColor(colors[i_syst]);
        }
    }

    systunc_legends = legends;
}


void RatioPlot::draw_systuncs()
{
    systunc_legend.Clear();
    std::vector<TGraphAsymmErrors*> grtodraw;
    for(int i = systunc_graphs.size()-1; i >= 0; i--){
        grtodraw.push_back((TGraphAsymmErrors*)systunc_graphs[i]->Clone((TString)systunc_graphs[i]->GetName() + "_sum"));
        for(int bin = 0; bin < systunc_graphs[i]->GetN(); bin++){
            double xl = systunc_graphs[i]->GetErrorXlow(bin);
            double xh = systunc_graphs[i]->GetErrorXhigh(bin);
            double yl = 0, yh = 0;
            for(int j = 0; j <= i; j++){
                yl += systunc_graphs[j]->GetErrorYlow(bin);
                yh += systunc_graphs[j]->GetErrorYhigh(bin);
            }
            grtodraw.back()->SetPointError(bin, xl, xh, yl, yh);
        }
        grtodraw.back()->Draw("same Z2");
        systunc_legend.AddEntry(grtodraw.back(), systunc_legends[i]);
    }
    if(systunc_graphs.size() != 0) systunc_legend.Draw("same");
}


void RatioPlot::dothething()
{
    Pad->cd();
    Pad->Clear();

    Central_Ratio->Draw("E0 X0 P");
    if(varied_exists) draw_systuncs();
    draw_line_at_1(Central_Ratio->GetXaxis()->GetXmin(), Central_Ratio->GetXaxis()->GetXmax());
    Central_Ratio->Draw("E0 X0 P same");
    
    Pad->Modified();
}
