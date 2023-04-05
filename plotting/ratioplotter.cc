#include "ratioplotter.h"

RatioPlot::RatioPlot(TPad* pad, bool widepl):
    Pad(pad),
    Central_Ratio(new TH1F("Central_Ratio", "", 1, 0, 1)),
    systunc_legend(get_legend((widepl)? 0.10 : 0.18, 0.32, 0.75, 0.42, 3)),
    fit_exists(false),
    fittext(get_latex(0.08, 11, 42)),
    wideplots(widepl)
{
    Pad->SetTopMargin(0.04);
    Pad->SetBottomMargin(0.3);
    Pad->Draw();
    Pad->cd();
    
    Central_Ratio->GetXaxis()->SetLabelSize(0.11);
    Central_Ratio->GetYaxis()->SetLabelSize(0.09);
    Central_Ratio->GetXaxis()->SetTitleSize(0.09);
    Central_Ratio->GetYaxis()->SetTitleSize(0.09);
    Central_Ratio->GetYaxis()->SetTitleOffset(0.3);
    Central_Ratio->SetMinimum(0);
    Central_Ratio->SetMaximum(2);
    
    std::vector<std::vector<int>> rgb = {{63,136,197}, {68,187,164}, {186,16,25}};
    for(unsigned i = 0; i < rgb.size(); i++){
        colors.push_back(TColor::GetColor(rgb[i][0], rgb[i][1], rgb[i][2]));
    }

    systunc_legend.SetTextSize(0.08);
}

RatioPlot::~RatioPlot(){
    delete Central_Ratio;
}

void RatioPlot::SetLogx(int xlog)
{
    Pad->SetLogx(xlog);
}

void RatioPlot::SetBinNames(std::vector<TString> BinNames)
{
    Central_Ratio->SetLabelSize(0.14);
    for(unsigned i = 0; i < BinNames.size(); ++i){
        Central_Ratio->GetXaxis()->SetBinLabel(i+1, BinNames[i]);
    }
}

void RatioPlot::SetCentralRatio(TH1F* num, TH1F* den, TString xaxistitle, TString yaxistitle)
{
    Central_Ratio->Reset();
    Central_Ratio->SetBins(num->GetNbinsX(), num->GetXaxis()->GetXmin(), num->GetXaxis()->GetXmax());
    Central_Ratio->Divide(num, den);

    Central_Ratio->GetXaxis()->SetTitle(xaxistitle);
    Central_Ratio->GetYaxis()->SetTitle(yaxistitle);
    Central_Ratio->SetMinimum(0);
    Central_Ratio->SetMaximum(2);
    for(int i = 1; i <= num->GetNbinsX(); i++){
        Central_Ratio->SetBinError(i, num->GetBinError(i)/den->GetBinContent(i));
        if(num->GetXaxis()->IsAlphanumeric()) Central_Ratio->GetXaxis()->SetBinLabel(i, num->GetXaxis()->GetBinLabel(i));
        else Central_Ratio->GetXaxis()->SetAlphanumeric(false);
    }
}

void RatioPlot::SetCentralRatio(TGraphAsymmErrors* num, TH1F* den, TString xaxistitle, TString yaxistitle)
{
    Central_Ratio->Reset();
    Central_Ratio->SetBins(den->GetNbinsX(), den->GetXaxis()->GetXmin(), den->GetXaxis()->GetXmax());
    for(int i = 1; i <= den->GetNbinsX(); i++){
        double x,y;
        num->GetPoint(i-1, x, y);
        Central_Ratio->SetBinContent(i, (y)/den->GetBinContent(i));
        Central_Ratio->SetBinError(i, num->GetErrorY(i)/den->GetBinContent(i));
        if(den->GetXaxis()->IsAlphanumeric()) Central_Ratio->GetXaxis()->SetBinLabel(i, den->GetXaxis()->GetBinLabel(i));
        else Central_Ratio->GetXaxis()->SetAlphanumeric(false);
    }

    Central_Ratio->GetXaxis()->SetTitle(xaxistitle);
    Central_Ratio->GetYaxis()->SetTitle(yaxistitle);
    Central_Ratio->SetMinimum(0);
    Central_Ratio->SetMaximum(2);
}

void RatioPlot::SetConstantFit()
{
    fit_exists = true;
    fit = new TF1("fit", "[0]", Central_Ratio->GetXaxis()->GetXmin(), Central_Ratio->GetXaxis()->GetXmin());
    fit->SetParameters(0, 1.);
    Central_Ratio->Fit(fit, "0");
}

std::vector<double> RatioPlot::GetVariations(TString variation_name, std::vector<TFile*> files_bkg, TH1F* MC_central)
{
    THStack* MC_varied = new THStack("MC_varied", ";;Events");
    for(unsigned i = 0; i < files_bkg.size(); i++){
        TH1F* varied_hist = (TH1F*) files_bkg[i]->Get(variation_name);
        if(varied_hist){
            MC_varied->Add(varied_hist);
            varied_exists = true;
        }
    }

    std::vector<double> variations;
    if(varied_exists and MC_varied->GetNhists() > 0){
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
    for(unsigned i_syst = 0; i_syst < systunc_names.size(); i_syst++){
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
            systunc_graphs.back()->SetName(histname + systunc_names[i_syst]);
            systunc_graphs.back()->SetFillColor(colors[systunc_graphs.size()-1]);
            systunc_graphs.back()->SetLineColor(colors[systunc_graphs.size()-1]);
            systunc_graphs.back()->SetMarkerColor(colors[systunc_graphs.size()-1]);
        }
    }

    for(const auto& l : legends){
        systunc_legends.push_back(l);
    }
}

void RatioPlot::ClearSystUncs()
{
    systunc_graphs.clear();
    systunc_legends.clear();
    systunc_legend.Clear();
    varied_exists = false;
}

void RatioPlot::AddStatVariation(TH1* hist, TString statname)
{
    varied_exists = true;
    std::vector<double> x_central, x_low, x_high, y_central, y_low, y_high;
    for(int i = 1; i <= hist->GetNbinsX(); i++){
        x_central.push_back((double)hist->GetXaxis()->GetBinCenter(i));
        x_low.push_back((double)x_central[i-1] - hist->GetXaxis()->GetBinLowEdge(i));
        x_high.push_back((double)hist->GetXaxis()->GetBinUpEdge(i) - x_central[i-1]);
        y_central.push_back(1.);
        y_low.push_back((double)hist->GetBinError(i) / hist->GetBinContent(i));
        y_high.push_back((double)hist->GetBinError(i) / hist->GetBinContent(i));
    }

    systunc_graphs.push_back(new TGraphAsymmErrors(x_central.size(), &x_central[0], &y_central[0], &x_low[0], &x_high[0], &y_low[0], &y_high[0]));
    systunc_graphs.back()->SetName(hist->GetName() + statname);
    systunc_graphs.back()->SetFillColor(colors[systunc_graphs.size()-1]);
    systunc_graphs.back()->SetLineColor(colors[systunc_graphs.size()-1]);
    systunc_graphs.back()->SetMarkerColor(colors[systunc_graphs.size()-1]);
    
    systunc_legends.push_back(statname);
}

void RatioPlot::Add_ABCD_SystVariation(TString histname, TString legendname, TH1F* MC_central)
{

    std::vector<double> x_central, x_low, x_high, y_central, y_low, y_high;
    for(int i = 1; i <= MC_central->GetNbinsX(); i++){
        x_central.push_back((double)MC_central->GetXaxis()->GetBinCenter(i));
        x_low.push_back((double)x_central[i-1] - MC_central->GetXaxis()->GetBinLowEdge(i));
        x_high.push_back((double)MC_central->GetXaxis()->GetBinUpEdge(i) - x_central[i-1]);
        y_central.push_back(1.);
        if(histname.Contains("_SS")){
            y_low.push_back(0.2);
            y_high.push_back(0.2);
        }else if(histname.Contains("_OS") and get_mass_category(histname) == "high"){
            y_low.push_back(0.3);
            y_high.push_back(0.3);
        }else if(histname.Contains("_OS") and get_mass_category(histname) == "low"){
            if(i <= MC_central->GetNbinsX()/2){
                y_low.push_back(0.2);
                y_high.push_back(0.2);
            }else{
                y_low.push_back(0.3);
                y_high.push_back(0.3);
            }
        }else if(histname.Contains("_mm") and get_mass_category(histname) == "high"){
            y_low.push_back(0.3);
            y_high.push_back(0.3);
        }else if(histname.Contains("_mm") and get_mass_category(histname) == "low"){
            y_low.push_back(0.2);
            y_high.push_back(0.2);
        }
    }

    systunc_graphs.push_back(new TGraphAsymmErrors(x_central.size(), &x_central[0], &y_central[0], &x_low[0], &x_high[0], &y_low[0], &y_high[0]));
    systunc_graphs.back()->SetName(MC_central->GetName() + legendname);
    systunc_graphs.back()->SetFillColor(colors[systunc_graphs.size()-1]);
    systunc_graphs.back()->SetLineColor(colors[systunc_graphs.size()-1]);
    systunc_graphs.back()->SetMarkerColor(colors[systunc_graphs.size()-1]);

    systunc_legends.push_back(legendname);
}

void RatioPlot::Add_DYSF_SystVariation(TString histname, TString legendname, TH1F* MC_central)
{
    std::vector<double> kappa_unc = get_DY_KappaFactor_unc(histname);
    //TString kappa_filename = get_DY_KappaFactor_filename(histname);
    //std::ifstream kappa_file(kappa_filename);
    //std::vector<double> kappa, kappa_unc, DY_fraction;

    //if(kappa_file.is_open()){
    //    std::string line;

    //    while(std::getline(kappa_file, line)){
    //        std::istringstream iss(line);
    //        std::string bin_number_str, kappa_str, kappa_unc_str, DY_fraction_str;
    //        iss >> bin_number_str >> kappa_str >> kappa_unc_str >> DY_fraction_str;

    //        //std::cout << "bin number: " << bin_number_str << " kappa_str: " << kappa_str << " kappa_unc_str: " << kappa_unc_str << std::endl;

    //        kappa.push_back(std::stod(kappa_str));
    //        kappa_unc.push_back(std::stod(kappa_unc_str));
    //        DY_fraction.push_back(std::stod(DY_fraction_str));
    //    }

    //    //std::cout << "kappa 4 and unc: " << kappa[4] << " " << kappa_unc[4] << std::endl;
    //}else{
    //    std::cout << "Error: kappa Factor file " << kappa_filename << " is not correctly open" << std::endl;
    //    return;
    //}


    std::vector<double> x_central, x_low, x_high, y_central, y_low, y_high;
    for(unsigned i = 1; i <= MC_central->GetNbinsX(); i++){
        x_central.push_back((double)MC_central->GetXaxis()->GetBinCenter(i));
        x_low.push_back((double)x_central[i-1] - MC_central->GetXaxis()->GetBinLowEdge(i));
        x_high.push_back((double)MC_central->GetXaxis()->GetBinUpEdge(i) - x_central[i-1]);
        y_central.push_back(1.);

        // beyond OS mumu bins, no SF at all
        if(i > kappa_unc.size()){
            y_low.push_back(0.);
            y_high.push_back(0.);
        }else{//for OS mumu, apply kappa_unc, not scaled by DY_fraction
            y_low.push_back(kappa_unc[i-1]);
            y_high.push_back(kappa_unc[i-1]);
        }
    }

    systunc_graphs.push_back(new TGraphAsymmErrors(x_central.size(), &x_central[0], &y_central[0], &x_low[0], &x_high[0], &y_low[0], &y_high[0]));
    systunc_graphs.back()->SetName(MC_central->GetName() + legendname);
    systunc_graphs.back()->SetFillColor(colors[systunc_graphs.size()-1]);
    systunc_graphs.back()->SetLineColor(colors[systunc_graphs.size()-1]);
    systunc_graphs.back()->SetMarkerColor(colors[systunc_graphs.size()-1]);

    systunc_legends.push_back(legendname);
}


void RatioPlot::Add_CR2_SystVariation(TFile* DataRun2File, TString histname, TString legendname, TH1F* MC_central)
{
    TString histname_CR2_pred = histname;
    histname_CR2_pred.ReplaceAll("TightmlSV", "TightCR2NoJetVetomlSV");
    //TString histname_CR2_obs = histname;
    //histname_CR2_obs.ReplaceAll("TightmlSV", "TightCR2NoJetVetomlSV");
    //histname_CR2_obs.ReplaceAll("BtoAwithCD", "quadA");

    TH1F* hist_CR2_pred = (TH1F*)DataRun2File->Get(histname_CR2_pred);
    //TH1F* hist_CR2_obs = (TH1F*)DataRun2File->Get(histname_CR2_obs);
    std::vector<double> x_central, x_low, x_high, y_central, y_low, y_high;
    for(int i = 1; i <= hist_CR2_pred->GetNbinsX(); i++){
        x_central.push_back((double)hist_CR2_pred->GetXaxis()->GetBinCenter(i));
        x_low.push_back((double)x_central[i-1] - hist_CR2_pred->GetXaxis()->GetBinLowEdge(i));
        x_high.push_back((double)hist_CR2_pred->GetXaxis()->GetBinUpEdge(i) - x_central[i-1]);
        y_central.push_back(1.);
        //if(hist_CR2_pred->GetBinContent(i) == 0 or hist_CR2_pred->GetBinErrorUp(i) == 0 or hist_CR2_obs->GetBinContent(i) == 0 or hist_CR2_obs->GetBinErrorUp(i) == 0){
        if(hist_CR2_pred->GetBinContent(i) == 0 or hist_CR2_pred->GetBinErrorUp(i) == 0){
            y_low.push_back(0.);
            y_high.push_back(2.);
        }else{
            y_low.push_back((double)hist_CR2_pred->GetBinError(i) / hist_CR2_pred->GetBinContent(i));
            y_high.push_back((double)hist_CR2_pred->GetBinError(i) / hist_CR2_pred->GetBinContent(i));
            //y_low.push_back((double)sqrt(pow(hist_CR2_pred->GetBinError(i) / hist_CR2_pred->GetBinContent(i),2) + pow(hist_CR2_obs->GetBinError(i) / hist_CR2_obs->GetBinContent(i),2)));
            //y_high.push_back((double)sqrt(pow(hist_CR2_pred->GetBinError(i) / hist_CR2_pred->GetBinContent(i),2) + pow(hist_CR2_obs->GetBinError(i) / hist_CR2_obs->GetBinContent(i),2)));
        }
    }

    systunc_graphs.push_back(new TGraphAsymmErrors(x_central.size(), &x_central[0], &y_central[0], &x_low[0], &x_high[0], &y_low[0], &y_high[0]));
    systunc_graphs.back()->SetName(hist_CR2_pred->GetName() + legendname);
    systunc_graphs.back()->SetFillColor(colors[systunc_graphs.size()-1]);
    systunc_graphs.back()->SetLineColor(colors[systunc_graphs.size()-1]);
    systunc_graphs.back()->SetMarkerColor(colors[systunc_graphs.size()-1]);

    systunc_legends.push_back(legendname);
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
                //yl += systunc_graphs[j]->GetErrorYlow(bin);
                //yh += systunc_graphs[j]->GetErrorYhigh(bin);
                yl = sqrt(yl*yl + systunc_graphs[j]->GetErrorYlow(bin)*systunc_graphs[j]->GetErrorYlow(bin));
                yh = sqrt(yh*yh + systunc_graphs[j]->GetErrorYhigh(bin)*systunc_graphs[j]->GetErrorYhigh(bin));
            }
            grtodraw.back()->SetPointError(bin, xl, xh, yl, yh);
        }
        grtodraw.back()->Draw("same Z2");
        systunc_legend.AddEntry(grtodraw.back(), systunc_legends[i]);
    }
    if(systunc_graphs.size() != 0) systunc_legend.Draw("same");
}

void RatioPlot::Add_Full_Error(TH1F* h)
{
    for(int bin = 1; bin < h->GetNbinsX(); bin++){
        double fullerrorl = 0, fullerrorh = 0;
        for(unsigned i = 0; i < systunc_graphs.size(); i++){
            fullerrorl = sqrt(fullerrorl*fullerrorl + systunc_graphs[i]->GetErrorYlow(bin)*systunc_graphs[i]->GetErrorYlow(bin));
            fullerrorh = sqrt(fullerrorh*fullerrorh + systunc_graphs[i]->GetErrorYhigh(bin)*systunc_graphs[i]->GetErrorYhigh(bin));
        }
        //std::cout << "old and new error: " << bin << ": " << h->GetBinError(bin) << " " << 0.5 * (fullerrorl + fullerrorh) * h->GetBinContent(bin) << std::endl;
        //std::cout << "from errl, errh, bincontent: " << fullerrorl << " " << fullerrorh << " " << h->GetBinContent(bin) << std::endl;
        h->SetBinError(bin, 0.5 * (fullerrorl + fullerrorh) * h->GetBinContent(bin));//TH1F doesnt have asymmetric error options
    }
}

void RatioPlot::draw_ABCD_CRline(TString histname, double xmin, double xmax)
{
    TLine line;
    line.SetLineStyle(2);
    line.SetLineColor(kRed);
    line.SetLineWidth(2);
    if(histname.Contains("_SS")){
        line.DrawLine(xmin, 0.8, xmax, 0.8);
        line.DrawLine(xmin, 1.2, xmax, 1.2);
    }else if(histname.Contains("_OS") and histname.Contains("_M-10")){
        line.DrawLine(xmin, 0.7, xmax, 0.7);
        line.DrawLine(xmin, 1.3, xmax, 1.3);
    }else if(histname.Contains("_OS") and histname.Contains("_M-5")){
        line.DrawLine(xmin, 0.8, xmax/2, 0.8);
        line.DrawLine(xmin, 1.2, xmax/2, 1.2);
        line.DrawLine(xmax/2, 0.7, xmax, 0.7);
        line.DrawLine(xmax/2, 1.3, xmax, 1.3);
    }
}

void RatioPlot::dothething()
{
    Pad->cd();
    Pad->Clear();

    Central_Ratio->Draw("E0 X0 P");
    if(varied_exists) draw_systuncs();
    draw_line_at_1(Central_Ratio->GetXaxis()->GetXmin(), Central_Ratio->GetXaxis()->GetXmax());
    Central_Ratio->Draw("E0 X0 P same");
    if(fit_exists){
        Central_Ratio->SetStats(0);
        std::ostringstream fitt;
        fitt << std::setprecision(3) << "Avg. ratio: " << fit->GetParameter(0) << "#pm " << fit->GetParError(0);
        if(wideplots) fittext.DrawLatex(0.1, 0.85,(TString) fitt.str());
        else fittext.DrawLatex(0.18, 0.85,(TString) fitt.str());
    }
    
    Pad->Modified();
}

void RatioPlot::Write_Central_Ratio(const std::string& name)
{
    std::cout << "Writing ratio to " << name << std::endl;
    std::string contents = "";
    for(int i = 1; i < Central_Ratio->GetNbinsX(); i++){
        contents += std::to_string(i) + " " + std::to_string(Central_Ratio->GetBinContent(i)) + " " + std::to_string(Central_Ratio->GetBinError(i)) + "\n";
    }
    filePutContents(name, contents, false);
}
