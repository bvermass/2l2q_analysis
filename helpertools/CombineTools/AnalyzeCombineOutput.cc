#include "AnalyzeCombineOutput.h"

bool verbose = false;
bool addExternalLimits = true;
bool addLegacyLimits = false;
bool addUpperLimits = false;
# ifndef __CINT__
int main(int argc, char * argv[])
{
    if(argc < 3){
        std::cout << "Command should be ./test [combine_rootfile_sampleList] [flavor_mass_otherId] [extra_subdir=""]" << std::endl;
        return 1;
    }
    //Argument 1: text file containing all necessary combine rootfiles to analyze
    //Code: the textfile is supposed to have combine rootfiles for 1 mass and a range of couplings.
    //      plot will be made of signal strength as a function of coupling
    TString txtfilename = (TString)argv[1];
    TString specific_dir = (TString)argv[2];
    TString extra_subdir = "";
    if(argc > 3) extra_subdir = ((TString)argv[3]) + "/";

    TString basedir = "";
    if(txtfilename.Contains("datacards")) basedir = txtfilename(0, txtfilename.Index("datacards"));
    else if(txtfilename.Contains("combine_output")) basedir = txtfilename(0, txtfilename.Index("combine_output"));

    TString plotbasedir = basedir + "plots/" + extra_subdir;
    gSystem->Exec("mkdir -p " + plotbasedir);

    std::cout << std::endl << "--------------------" << std::endl;
    std::cout << "Base directory: " << basedir << std::endl;
    std::cout << "Base plot directory: " << plotbasedir << std::endl;
    std::cout << "flavor and mass: " << specific_dir << std::endl;
    
    //From txtfile, read the combine output root files to be used for the plot
    std::cout << "--------------------" << std::endl << "reading from textfile:" << std::endl;
    std::string line;
    std::ifstream txtfile (txtfilename);
    std::vector<CombineOutput*> combine_outputs;
    std::map<double, std::map<double, double>> scalefactors;//<M, <V2, scalefactor>>
    if(txtfile.is_open()){
        while(std::getline(txtfile, line)){
            std::cout << line << std::endl;
            CombineOutput* combine_output = new CombineOutput((TString)line);
            if(combine_output->combine_tree){
                combine_outputs.push_back(combine_output);
            }
            scalefactors[combine_output->M][combine_output->V2] = GetCorrespondingScalefactor((TString)line);
        }
    }


    if(verbose) std::cout << "--------------------" << std::endl << "reading signal strengths" << std::endl;
    std::map<double, std::map<double, std::map<float, double>>> signal_strengths; //<M, <V2, <quantile, limit>>
    for(unsigned i = 0; i < combine_outputs.size(); i++){
        if(verbose) std::cout << "processing " << combine_outputs[i]->combine_filename << std::endl;
        std::map<float, double> sigstr = combine_outputs[i]->GetSignalStrengths();
        if(verbose) std::cout << "M, V2, scale factor: " << combine_outputs[i]->M << " " << combine_outputs[i]->V2 << " " << scalefactors[combine_outputs[i]->M][combine_outputs[i]->V2] << std::endl;
        for(auto& sr : sigstr){
            sr.second = sr.second * scalefactors[combine_outputs[i]->M][combine_outputs[i]->V2];
        }
        if(sigstr.size() == 6){
            signal_strengths[combine_outputs[i]->M][combine_outputs[i]->V2] = sigstr;
        }
    }
    if(verbose) PrintAllSignalStrengths(signal_strengths);


    std::cout << "--------------------" << std::endl << "Plotting Signal Strengths vs. coupling for single mass" << std::endl;
    for(auto& sr_M : signal_strengths){
        PlotSignalStrengths(sr_M.second, plotbasedir + "SignalStrength_" + specific_dir + "M-" + std::to_string((int)sr_M.first) + ".png", "|V|^{2}", "Signal Strength");
    }

    std::cout << "--------------------" << std::endl << "Getting exclusion limits and plotting final exclusion plot" << std::endl;//ONLY LOWER LIMIT, NO UPPER LIMIT YET
    std::map<double, std::map<float, double>> lower_exclusion_limits;//<mass, <quantile, V2(where limit is 1, approached from below)>>
    for(auto& sr_M : signal_strengths){
        if(CheckGoesBelow1(sr_M.second, 0.025))     lower_exclusion_limits[sr_M.first][0.025] = GetLowerExclusionLimit(sr_M.second, 0.025);
        else if(CheckGoesBelow1(sr_M.second, 0.50)) lower_exclusion_limits[sr_M.first][0.025] = GetLowerExclusionLimit(sr_M.second, 0.50);
        if(CheckGoesBelow1(sr_M.second, 0.16))      lower_exclusion_limits[sr_M.first][0.16] = GetLowerExclusionLimit(sr_M.second, 0.16);
        else if(CheckGoesBelow1(sr_M.second, 0.50)) lower_exclusion_limits[sr_M.first][0.16] = GetLowerExclusionLimit(sr_M.second, 0.50);
        if(CheckGoesBelow1(sr_M.second, 0.50))      lower_exclusion_limits[sr_M.first][0.50] = GetLowerExclusionLimit(sr_M.second, 0.50);
        if(CheckGoesBelow1(sr_M.second, 0.84))      lower_exclusion_limits[sr_M.first][0.84] = GetLowerExclusionLimit(sr_M.second, 0.84);
        else if(CheckGoesBelow1(sr_M.second, 0.50)) lower_exclusion_limits[sr_M.first][0.84] = GetLowerExclusionLimit(sr_M.second, 0.50);
        if(CheckGoesBelow1(sr_M.second, 0.975))     lower_exclusion_limits[sr_M.first][0.975] = GetLowerExclusionLimit(sr_M.second, 0.975);
        else if(CheckGoesBelow1(sr_M.second, 0.50)) lower_exclusion_limits[sr_M.first][0.975] = GetLowerExclusionLimit(sr_M.second, 0.50);
        if(CheckGoesBelow1(sr_M.second, -1))        lower_exclusion_limits[sr_M.first][-1]    = GetLowerExclusionLimit(sr_M.second, -1);
        else if(CheckGoesBelow1(sr_M.second, 0.50)) lower_exclusion_limits[sr_M.first][-1]    = GetLowerExclusionLimit(sr_M.second, 0.50);
    }
    std::map<double, std::map<float, double>> upper_exclusion_limits;//<mass, <quantile, V2(where limit is 1, approached from below)>>
    for(auto& sr_M : signal_strengths){
        if(CheckGoesBackAbove1(sr_M.second, 0.025))     upper_exclusion_limits[sr_M.first][0.025] = GetUpperExclusionLimit(sr_M.second, 0.025);
        else if(CheckGoesBackAbove1(sr_M.second, 0.50)) upper_exclusion_limits[sr_M.first][0.025] = GetUpperExclusionLimit(sr_M.second, 0.50);
        if(CheckGoesBackAbove1(sr_M.second, 0.16))      upper_exclusion_limits[sr_M.first][0.16] = GetUpperExclusionLimit(sr_M.second, 0.16);
        else if(CheckGoesBackAbove1(sr_M.second, 0.50)) upper_exclusion_limits[sr_M.first][0.16] = GetUpperExclusionLimit(sr_M.second, 0.50);
        if(CheckGoesBackAbove1(sr_M.second, 0.50))      upper_exclusion_limits[sr_M.first][0.50] = GetUpperExclusionLimit(sr_M.second, 0.50);
        if(CheckGoesBackAbove1(sr_M.second, 0.84))      upper_exclusion_limits[sr_M.first][0.84] = GetUpperExclusionLimit(sr_M.second, 0.84);
        else if(CheckGoesBackAbove1(sr_M.second, 0.50)) upper_exclusion_limits[sr_M.first][0.84] = GetUpperExclusionLimit(sr_M.second, 0.50);
        if(CheckGoesBackAbove1(sr_M.second, 0.975))     upper_exclusion_limits[sr_M.first][0.975] = GetUpperExclusionLimit(sr_M.second, 0.975);
        else if(CheckGoesBackAbove1(sr_M.second, 0.50)) upper_exclusion_limits[sr_M.first][0.975] = GetUpperExclusionLimit(sr_M.second, 0.50);
        if(CheckGoesBackAbove1(sr_M.second, -1))        upper_exclusion_limits[sr_M.first][-1]    = GetUpperExclusionLimit(sr_M.second, -1);
        else if(CheckGoesBackAbove1(sr_M.second, 0.50)) upper_exclusion_limits[sr_M.first][-1]    = GetUpperExclusionLimit(sr_M.second, 0.50);
    }

    if(verbose){
        for(const double& q : {0.025, 0.16, 0.5, 0.84, 0.975, -1.}){
            std::cout << "Lower Exclusion Line " << q << ": ";
            PrintExclusionLine(lower_exclusion_limits, q);
        }
        for(const double& q : {0.025, 0.16, 0.5, 0.84, 0.975, -1.}){
            std::cout << "Upper Exclusion Line " << q << ": ";
            PrintExclusionLine(upper_exclusion_limits, q);
        }
    }

    PlotExclusionLimit(lower_exclusion_limits, upper_exclusion_limits, plotbasedir + "ExclusionLimit_" + specific_dir + ".png", "M_{HNL} [GeV]", "|V|^{2}");
    WriteExclusionLimit(lower_exclusion_limits, upper_exclusion_limits, plotbasedir + "Limits_" + specific_dir + ".txt");
    //WriteExclusionLimit_with_Bands(lower_exclusion_limits, upper_exclusion_limits, plotbasedir + "Limits_Legacy_AN_v8_" + specific_dir + ".txt");
}
#endif


bool CheckGoesBelow1(std::map<double, std::map<float, double>> signal_strengths, float quantile){
    for(auto& sr_V2 : signal_strengths){
        if(sr_V2.second[quantile] < 1) return true;
    }
    return false;
}

bool CheckGoesBackAbove1(std::map<double, std::map<float, double>> signal_strengths, float quantile){
    bool passed_lowerlimit = false;
    for(auto& sr_V2 : signal_strengths){
        if(sr_V2.second[quantile] < 1) passed_lowerlimit = true;
        if(passed_lowerlimit and sr_V2.second[quantile] > 1) return true;
    }
    return false;
}


double GetUpperExclusionLimit(std::map<double, std::map<float, double>> signal_strengths, float quantile)
{
    double x1, x2, y1, y2;//x1, x2 = V2 and y1, y2 = signal strength
    bool passed_lowerlimit = false, passed_upperlimit = false;
    for(auto& sr_V2 : signal_strengths){
        if(verbose) std::cout << "V2, signal strength: " << sr_V2.first << " " << sr_V2.second[quantile] << std::endl;
        if(sr_V2.second[quantile] < 1){
            passed_lowerlimit = true;
        }

        if(passed_lowerlimit){
            if(sr_V2.second[quantile] > 1){
                x2 = sr_V2.first;
                y2 = sr_V2.second[quantile];
                passed_upperlimit = true;
                break;
            }else {
                x1 = sr_V2.first;
                y1 = sr_V2.second[quantile];
            }
        }
    }

    if(passed_upperlimit) return (x2 - x1 + y2*x1 - y1*x2) / (y2 - y1);//linear interpolation between (x1,y1) and (x2,y2) and returning x3 for point (x3,1) (signal strength equal to 1sSection(directory)
    else return 0.09;
}

double GetLowerExclusionLimit(std::map<double, std::map<float, double>> signal_strengths, float quantile)
{
    double x1, x2, y1, y2;//x1, x2 = V2 and y1, y2 = signal strength
    for(auto& sr_V2 : signal_strengths){
        if(verbose) std::cout << "V2, signal strength: " << sr_V2.first << " " << sr_V2.second[quantile] << std::endl;
        if(sr_V2.second[quantile] < 1){
            x2 = sr_V2.first;
            y2 = sr_V2.second[quantile];
            break;
        }else {
            x1 = sr_V2.first;
            y1 = sr_V2.second[quantile];
        }
    }

    return (x2 - x1 + y2*x1 - y1*x2) / (y2 - y1);//linear interpolation between (x1,y1) and (x2,y2) and returning x3 for point (x3,1) (signal strength equal to 1)
}

void PlotExclusionLimit(std::map<double, std::map<float, double>> lower_exclusion_limit, std::map<double, std::map<float, double>> upper_exclusion_limit, TString plotfilename, TString Xaxistitle, TString Yaxistitle)
{
    // set general plot style
    setTDRStyle();
    gROOT->ForceStyle();
    bool is2016 = plotfilename.Contains("2016"), is2017 = plotfilename.Contains("2017"), is2018 = plotfilename.Contains("2018"), isRun2 = plotfilename.Contains("Run2") or plotfilename.Contains("run2");

    if(plotfilename.Contains("_mm_")) Yaxistitle.ReplaceAll("V","V_{#mu N}");
    else if(plotfilename.Contains("_ee_")) Yaxistitle.ReplaceAll("V","V_{eN}");
    else if(plotfilename.Contains("_2l_")) Yaxistitle.ReplaceAll("V","V_{lN}");

    TCanvas* c = new TCanvas("c","",1000,1000);
    c->cd();

    // Make the pad that will contain the plot
    TPad* pad  = new TPad("pad", "", 0., 0., 1., 1.);
    pad->Draw();
    pad->cd();
    pad->SetLogx(0);
    pad->SetLogy(1);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad, is2016, is2017, is2018, isRun2);

    std::vector<double> V2_lower, V2_lower_err, sr_lower_2s_up, sr_lower_2s_down, sr_lower_1s_up, sr_lower_1s_down, sr_lower_central, sr_lower_observed;
    for(auto& sr_V2 : lower_exclusion_limit){
        if(sr_V2.second[0.50] < 1e-10) continue;
        V2_lower.push_back(sr_V2.first);
        sr_lower_2s_up.push_back(sr_V2.second[0.975] - sr_V2.second[0.50]); //For 1 and 2 sigma variations, get value RELATIVE to central value to be able to use it as an error in TGraphAsymmErrors
        sr_lower_1s_up.push_back(sr_V2.second[0.84] - sr_V2.second[0.50]);
        sr_lower_2s_down.push_back(sr_V2.second[0.50] - sr_V2.second[0.025]);
        sr_lower_1s_down.push_back(sr_V2.second[0.50] - sr_V2.second[0.16]);
        sr_lower_central.push_back(sr_V2.second[0.50]);
        sr_lower_observed.push_back(sr_V2.second[-1]);
        V2_lower_err.push_back(0.);
    }

    std::vector<double> V2_upper, V2_upper_err, sr_upper_2s_up, sr_upper_2s_down, sr_upper_1s_up, sr_upper_1s_down, sr_upper_central, sr_upper_observed;
    for(auto& sr_V2 : upper_exclusion_limit){
        if(sr_V2.second[0.50] < 1e-10) continue;
        V2_upper.push_back(sr_V2.first);
        sr_upper_2s_up.push_back(sr_V2.second[0.975] - sr_V2.second[0.50]); //For 1 and 2 sigma variations, get value RELATIVE to central value to be able to use it as an error in TGraphAsymmErrors
        sr_upper_1s_up.push_back(sr_V2.second[0.84] - sr_V2.second[0.50]);
        sr_upper_2s_down.push_back(sr_V2.second[0.50] - sr_V2.second[0.025]);
        sr_upper_1s_down.push_back(sr_V2.second[0.50] - sr_V2.second[0.16]);
        sr_upper_central.push_back(sr_V2.second[0.50]);
        sr_upper_observed.push_back(sr_V2.second[-1]);
        V2_upper_err.push_back(0.);
    }

    TGraphAsymmErrors* sr_lower_2s_graph = new TGraphAsymmErrors(V2_lower.size(), &V2_lower[0], &sr_lower_central[0], &V2_lower_err[0], &V2_lower_err[0], &sr_lower_2s_down[0], &sr_lower_2s_up[0]);
    sr_lower_2s_graph->SetFillColor(kOrange);
    sr_lower_2s_graph->SetFillStyle(1001);
    sr_lower_2s_graph->GetXaxis()->SetTitle(Xaxistitle);
    sr_lower_2s_graph->GetYaxis()->SetTitle(Yaxistitle);
    sr_lower_2s_graph->GetYaxis()->SetTitleOffset(1.4);
    sr_lower_2s_graph->GetYaxis()->SetLabelSize(0.042);
    sr_lower_2s_graph->GetXaxis()->SetLabelSize(0.042);
    //sr_lower_2s_graph->GetXaxis()->SetMoreLogLabels();
    //sr_lower_2s_graph->GetYaxis()->SetMoreLogLabels();

    TGraphAsymmErrors* sr_lower_1s_graph = new TGraphAsymmErrors(V2_lower.size(), &V2_lower[0], &sr_lower_central[0], &V2_lower_err[0], &V2_lower_err[0], &sr_lower_1s_down[0], &sr_lower_1s_up[0]);
    sr_lower_1s_graph->SetFillColor(kGreen+1);
    sr_lower_1s_graph->SetFillStyle(1001);

    TGraphAsymmErrors* sr_lower_central_graph = new TGraphAsymmErrors(V2_lower.size(), &V2_lower[0], &sr_lower_central[0], &V2_lower_err[0], &V2_lower_err[0], &V2_lower_err[0], &V2_lower_err[0]);
    TGraphAsymmErrors* sr_lower_observed_graph = new TGraphAsymmErrors(V2_lower.size(), &V2_lower[0], &sr_lower_observed[0], &V2_lower_err[0], &V2_lower_err[0], &V2_lower_err[0], &V2_lower_err[0]);

    TGraphAsymmErrors* sr_upper_2s_graph = new TGraphAsymmErrors(V2_upper.size(), &V2_upper[0], &sr_upper_central[0], &V2_upper_err[0], &V2_upper_err[0], &sr_upper_2s_down[0], &sr_upper_2s_up[0]);
    sr_upper_2s_graph->SetFillColor(kOrange);
    sr_upper_2s_graph->SetFillStyle(1001);

    TGraphAsymmErrors* sr_upper_1s_graph = new TGraphAsymmErrors(V2_upper.size(), &V2_upper[0], &sr_upper_central[0], &V2_upper_err[0], &V2_upper_err[0], &sr_upper_1s_down[0], &sr_upper_1s_up[0]);
    sr_upper_1s_graph->SetFillColor(kGreen+1);
    sr_upper_1s_graph->SetFillStyle(1001);

    TGraphAsymmErrors* sr_upper_central_graph = new TGraphAsymmErrors(V2_upper.size(), &V2_upper[0], &sr_upper_central[0], &V2_upper_err[0], &V2_upper_err[0], &V2_upper_err[0], &V2_upper_err[0]);
    TGraphAsymmErrors* sr_upper_observed_graph = new TGraphAsymmErrors(V2_upper.size(), &V2_upper[0], &sr_upper_observed[0], &V2_upper_err[0], &V2_upper_err[0], &V2_upper_err[0], &V2_upper_err[0]);

    //Close the limit at the high mass end
    //for central value, just draw a line between last two points
    std::vector<double> highmassend_xpoints({V2_lower.back(), V2_upper.back()}), highmassend_ypoints({sr_lower_central.back(), sr_upper_central.back()}), hmend_err({0,0});
    TGraphAsymmErrors* highmassend = new TGraphAsymmErrors(highmassend_xpoints.size(), &highmassend_xpoints[0], &highmassend_ypoints[0], &hmend_err[0], &hmend_err[0], &hmend_err[0], &hmend_err[0]);

    sr_lower_2s_graph->Draw("A3");
    sr_lower_2s_graph->GetXaxis()->SetRangeUser(1,15);
    sr_lower_2s_graph->GetYaxis()->SetRangeUser(2e-8, 0.3);

    sr_lower_1s_graph->Draw("3 same");
    sr_lower_central_graph->Draw("L same");
    sr_lower_observed_graph->Draw("L same");
    sr_lower_observed_graph->SetLineColor(kRed);
    sr_lower_observed_graph->SetLineWidth(2);
    sr_lower_central_graph->SetLineWidth(2);

    if(addUpperLimits){
        sr_upper_2s_graph->Draw("3 same");
        sr_upper_1s_graph->Draw("3 same");
        sr_upper_central_graph->Draw("L same");
        sr_upper_observed_graph->Draw("L same");
        sr_upper_observed_graph->SetLineColor(kRed);
        sr_upper_observed_graph->SetLineWidth(2);
        sr_upper_central_graph->SetLineWidth(2);
    }

    //highmassend->Draw("L same");

    CMSandLumi->Draw();
    double ymin = 0.78, xmin = 0.17;
    if(plotfilename.Contains("_mm_")) ymin = 0.76;
    if(plotfilename.Contains("_2l_")) xmin = 0.6;
    TLegend legend(xmin, ymin, 0.93, 0.95);
    if(plotfilename.Contains("_mm_") or plotfilename.Contains("_ee_")) legend.SetNColumns(2);
    legend.SetTextSize(0.025);
    legend.SetFillStyle(0);
    
    //Add external limits from other/older analyses
    if(addExternalLimits){
        //TGraphAsymmErrors* delphi_prompt                    = get_external_limit("delphi_prompt", kBlue, 10, 3);
        TGraphAsymmErrors* delphi_displaced                 = get_external_limit("delphi_displaced", kBlue+2, 9, 3);
        //TGraphAsymmErrors* atlas_prompt_muon                = get_external_limit("atlas_prompt_muon", kGreen+3, 7, 3);
        //TGraphAsymmErrors* atlas_prompt_electron            = get_external_limit("atlas_prompt_electron", kGreen+3, 8, 3);
        //TGraphAsymmErrors* atlas_displaced_muon_LNV         = get_external_limit("atlas_displaced_muon_LNV", kCyan+1, 6, 3);
        //TGraphAsymmErrors* atlas_displaced_muon_LNC         = get_external_limit("atlas_displaced_muon_LNC", kCyan+3, 5, 3);
        TGraphAsymmErrors* cms_trilepton_prompt_muon        = get_external_limit("cms_trilepton_prompt_muon", kGreen+3, 4, 3);
        TGraphAsymmErrors* cms_trilepton_prompt_electron    = get_external_limit("cms_trilepton_prompt_electron", kGreen+3, 3, 3);
        TGraphAsymmErrors* cms_trilepton_displaced_electron = get_external_limit("cms_trilepton_displaced_electron", kCyan+2, 10, 3);
        TGraphAsymmErrors* cms_trilepton_displaced_muon     = get_external_limit("cms_trilepton_displaced_muon", kCyan+2, 10, 3);

        if(plotfilename.Contains("_mm_")){
            //delphi_prompt->Draw("L same");
            delphi_displaced->Draw("L same");
            //atlas_prompt_muon->Draw("L same");
            //atlas_displaced_muon_LNV->Draw("L same");
            //atlas_displaced_muon_LNC->Draw("L same");
            cms_trilepton_prompt_muon->Draw("L same");
            if(isRun2) cms_trilepton_displaced_muon->Draw("L same");
        }else if(plotfilename.Contains("_ee_")){
            //delphi_prompt->Draw("L same");
            delphi_displaced->Draw("L same");
            //atlas_prompt_electron->Draw("L same");
            cms_trilepton_prompt_electron->Draw("L same");
            if(isRun2) cms_trilepton_displaced_electron->Draw("L same");
        }

        //if(plotfilename.Contains("_mm_") or plotfilename.Contains("_ee_")) legend.AddEntry(delphi_prompt, "DELPHI prompt", "l");
        legend.AddEntry(sr_lower_central_graph, "Expected", "l");
        if(plotfilename.Contains("_mm_") or plotfilename.Contains("_ee_")) legend.AddEntry(delphi_displaced, "DELPHI displaced", "l");
        legend.AddEntry(sr_lower_1s_graph, "Expected #pm 1#sigma", "f");
        //if(plotfilename.Contains("_mm_"))      legend.AddEntry(atlas_prompt_muon, "ATLAS 3l prompt (2016)", "l");
        //else if(plotfilename.Contains("_ee_")) legend.AddEntry(atlas_prompt_electron, "ATLAS 3l prompt (2016)", "l");


        if(plotfilename.Contains("_mm_")){
            //legend.AddEntry(atlas_displaced_muon_LNV, "ATLAS displaced LNV (2016)", "l");
            legend.AddEntry(cms_trilepton_prompt_muon, "CMS 3l prompt (2016)", "l");
            legend.AddEntry(sr_lower_2s_graph, "Expected #pm 2#sigma", "f");
            //legend.AddEntry(atlas_displaced_muon_LNC, "ATLAS displaced LNC (2016)", "l");
            if(isRun2) legend.AddEntry(cms_trilepton_displaced_muon, "CMS 3l displaced (Run2)", "l");
        }else if(plotfilename.Contains("_ee_")){
            legend.AddEntry(cms_trilepton_prompt_electron, "CMS 3l prompt (2016)", "l");
            legend.AddEntry(sr_lower_2s_graph, "Expected #pm 2#sigma", "f");
            if(isRun2) legend.AddEntry(cms_trilepton_displaced_electron, "CMS 3l displaced (Run2)", "l");
        }
        legend.AddEntry(sr_lower_observed_graph, "Observed", "l");
    }
    if(addLegacyLimits){
        TString legacy_limit_file = "/user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/plots/Limits_Legacy_AN_v8_" + plotfilename(plotfilename.Index("ExclusionLimit_")+15, plotfilename.Index(".png") - plotfilename.Index("ExclusionLimit_")-15) + ".txt";

        TGraphAsymmErrors* legacy_lower_V2_central = get_legacy_limit(legacy_limit_file, 0.50, true, kBlue, 5, 3);
        //TGraphAsymmErrors* legacy_lower_V2_up_1s = get_legacy_limit(legacy_limit_file, 0.84, true, kBlue, 5, 3);
        //TGraphAsymmErrors* legacy_lower_V2_up_2s = get_legacy_limit(legacy_limit_file, 0.975, true, kBlue, 5, 3);
        //TGraphAsymmErrors* legacy_lower_V2_down_1s = get_legacy_limit(legacy_limit_file, 0.16, true, kBlue, 5, 3);
        //TGraphAsymmErrors* legacy_lower_V2_down_2s = get_legacy_limit(legacy_limit_file, 0.025, true, kBlue, 5, 3);
        TGraphAsymmErrors* legacy_upper_V2_central = get_legacy_limit(legacy_limit_file, 0.50, false, kBlue, 5, 3);

        legacy_lower_V2_central->Draw("L same");
        //legacy_lower_V2_up_1s->Draw("L same");
        //legacy_lower_V2_up_2s->Draw("L same");
        //legacy_lower_V2_down_1s->Draw("L same");
        //legacy_lower_V2_down_2s->Draw("L same");
        legacy_upper_V2_central->Draw("L same");

        legend.AddEntry(legacy_lower_V2_central, "Old Limit", "l");
        legend.AddEntry(sr_lower_central_graph, "Expected", "l");
        legend.AddEntry(sr_lower_1s_graph, "Expected #pm 1#sigma", "f");
        legend.AddEntry(sr_lower_2s_graph, "Expected #pm 2#sigma", "f");

        plotfilename.ReplaceAll(".png","_vsLegacy.png");
        plotfilename.ReplaceAll(".pdf","_vsLegacy.pdf");
    }




    legend.Draw("same");


    pad->Modified();
    c->Print(plotfilename);
    delete c;
    return;
}


void PlotExclusionLimit_withPolyLine(std::map<double, std::map<float, double>> lower_exclusion_limit, std::map<double, std::map<float, double>> upper_exclusion_limit, TString plotfilename, TString Xaxistitle, TString Yaxistitle)
{
    // set general plot style
    setTDRStyle();
    gROOT->ForceStyle();
    bool is2016 = plotfilename.Contains("2016"), is2017 = plotfilename.Contains("2017"), is2018 = plotfilename.Contains("2018"), isRun2 = plotfilename.Contains("Run2") or plotfilename.Contains("run2");

    TCanvas* c = new TCanvas("c","",1000,1000);
    c->cd();

    // Make the pad that will contain the plot
    TPad* pad  = new TPad("pad", "", 0., 0., 1., 1.);
    pad->Draw();
    pad->cd();
    pad->SetLogx(1);
    pad->SetLogy(1);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad, is2016, is2017, is2018, isRun2);

    std::vector<double> V2_lower, V2_lower_err, sr_lower_2s_up, sr_lower_2s_down, sr_lower_1s_up, sr_lower_1s_down, sr_lower_central;
    for(auto& sr_V2 : lower_exclusion_limit){
        //if(sr_V2.second[0.50] > 5) continue;
        V2_lower.push_back(sr_V2.first);
        sr_lower_2s_up.push_back(sr_V2.second[0.975] - sr_V2.second[0.50]); //For 1 and 2 sigma variations, get value RELATIVE to central value to be able to use it as an error in TGraphAsymmErrors
        sr_lower_1s_up.push_back(sr_V2.second[0.84] - sr_V2.second[0.50]);
        sr_lower_2s_down.push_back(sr_V2.second[0.50] - sr_V2.second[0.025]);
        sr_lower_1s_down.push_back(sr_V2.second[0.50] - sr_V2.second[0.16]);
        sr_lower_central.push_back(sr_V2.second[0.50]);
        V2_lower_err.push_back(0.);
    }

    std::vector<double> V2_upper, V2_upper_err, sr_upper_2s_up, sr_upper_2s_down, sr_upper_1s_up, sr_upper_1s_down, sr_upper_central;
    for(auto& sr_V2 : upper_exclusion_limit){
        //if(sr_V2.second[0.50] > 5) continue;
        V2_upper.push_back(sr_V2.first);
        sr_upper_2s_up.push_back(sr_V2.second[0.975] - sr_V2.second[0.50]); //For 1 and 2 sigma variations, get value RELATIVE to central value to be able to use it as an error in TGraphAsymmErrors
        sr_upper_1s_up.push_back(sr_V2.second[0.84] - sr_V2.second[0.50]);
        sr_upper_2s_down.push_back(sr_V2.second[0.50] - sr_V2.second[0.025]);
        sr_upper_1s_down.push_back(sr_V2.second[0.50] - sr_V2.second[0.16]);
        sr_upper_central.push_back(sr_V2.second[0.50]);
        V2_upper_err.push_back(0.);
    }

    std::vector<double> V2_2s_contour, V2_1s_contour, M_2s_contour, M_1s_contour;
    for(auto V2it = sr_lower_2s_up.begin(); V2it != sr_lower_2s_up.end(); ++V2it) V2_2s_contour.push_back(*V2it);
    for(auto V2it = sr_upper_2s_down.rbegin(); V2it != sr_upper_2s_down.rend(); ++V2it) V2_2s_contour.push_back(*V2it);
    for(auto V2it = sr_upper_2s_up.begin(); V2it != sr_upper_2s_up.end(); ++V2it) V2_2s_contour.push_back(*V2it);
    for(auto V2it = sr_lower_2s_down.rbegin(); V2it != sr_lower_2s_down.rend(); ++V2it) V2_2s_contour.push_back(*V2it);
    // unfinished!

    TGraphAsymmErrors* sr_lower_2s_graph = new TGraphAsymmErrors(V2_lower.size(), &V2_lower[0], &sr_lower_central[0], &V2_lower_err[0], &V2_lower_err[0], &sr_lower_2s_down[0], &sr_lower_2s_up[0]);
    sr_lower_2s_graph->SetFillColor(kOrange);
    sr_lower_2s_graph->SetFillStyle(1001);
    sr_lower_2s_graph->GetXaxis()->SetTitle(Xaxistitle);
    sr_lower_2s_graph->GetYaxis()->SetTitle(Yaxistitle);
    //sr_lower_2s_graph->GetXaxis()->SetMoreLogLabels();
    //sr_lower_2s_graph->GetYaxis()->SetMoreLogLabels();

    TGraphAsymmErrors* sr_lower_1s_graph = new TGraphAsymmErrors(V2_lower.size(), &V2_lower[0], &sr_lower_central[0], &V2_lower_err[0], &V2_lower_err[0], &sr_lower_1s_down[0], &sr_lower_1s_up[0]);
    sr_lower_1s_graph->SetFillColor(kGreen+1);
    sr_lower_1s_graph->SetFillStyle(1001);

    TGraphAsymmErrors* sr_lower_central_graph = new TGraphAsymmErrors(V2_lower.size(), &V2_lower[0], &sr_lower_central[0], &V2_lower_err[0], &V2_lower_err[0], &V2_lower_err[0], &V2_lower_err[0]);

    TGraphAsymmErrors* sr_upper_2s_graph = new TGraphAsymmErrors(V2_upper.size(), &V2_upper[0], &sr_upper_central[0], &V2_upper_err[0], &V2_upper_err[0], &sr_upper_2s_down[0], &sr_upper_2s_up[0]);
    sr_upper_2s_graph->SetFillColor(kOrange);
    sr_upper_2s_graph->SetFillStyle(1001);

    TGraphAsymmErrors* sr_upper_1s_graph = new TGraphAsymmErrors(V2_upper.size(), &V2_upper[0], &sr_upper_central[0], &V2_upper_err[0], &V2_upper_err[0], &sr_upper_1s_down[0], &sr_upper_1s_up[0]);
    sr_upper_1s_graph->SetFillColor(kGreen+1);
    sr_upper_1s_graph->SetFillStyle(1001);

    TGraphAsymmErrors* sr_upper_central_graph = new TGraphAsymmErrors(V2_upper.size(), &V2_upper[0], &sr_upper_central[0], &V2_upper_err[0], &V2_upper_err[0], &V2_upper_err[0], &V2_upper_err[0]);



    sr_lower_2s_graph->Draw("A3");
    sr_lower_2s_graph->GetXaxis()->SetRangeUser(0,15);
    sr_lower_2s_graph->GetYaxis()->SetRangeUser(2e-8, 0.3);

    sr_lower_1s_graph->Draw("3 same");
    sr_lower_central_graph->Draw("L same");

    sr_upper_2s_graph->Draw("3 same");
    sr_upper_1s_graph->Draw("3 same");
    sr_upper_central_graph->Draw("L same");

    CMSandLumi->Draw();

    pad->Modified();
    c->Print(plotfilename);
    delete c;
    return;
    Double_t x[4] = {4.,7.,6.,5.};
    Double_t y[4] = {4e-6,3e-6,4e-5,3e-5};
    TPolyLine *pline = new TPolyLine(4,x,y);
    pline->SetFillColor(38);
    pline->SetLineColor(2);
    pline->SetLineWidth(4);
    pline->Draw("f same");
}


void PlotSignalStrengths(std::map<double, std::map<float, double>> signal_strengths, TString plotfilename, TString Xaxistitle, TString Yaxistitle)
{
    // set general plot style
    setTDRStyle();
    gROOT->ForceStyle();
    bool is2016 = plotfilename.Contains("2016"), is2017 = plotfilename.Contains("2017"), is2018 = plotfilename.Contains("2018"), isRun2 = plotfilename.Contains("Run2") or plotfilename.Contains("run2");

    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    // Make the pad that will contain the plot
    TPad* pad  = new TPad("pad", "", 0., 0., 1., 1.);
    pad->Draw();
    pad->cd();
    pad->SetLogx(1);
    pad->SetLogy(1);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad, is2016, is2017, is2018, isRun2);

    std::vector<double> V2, V2_err, sr_2s_up, sr_2s_down, sr_1s_up, sr_1s_down, sr_central, sr_observed;
    for(auto& sr_V2 : signal_strengths){
        //if(sr_V2.second[0.50] > 5) continue;
        V2.push_back(sr_V2.first);
        sr_2s_up.push_back(sr_V2.second[0.975] - sr_V2.second[0.50]); //For 1 and 2 sigma variations, get value RELATIVE to central value to be able to use it as an error in TGraphAsymmErrors
        sr_1s_up.push_back(sr_V2.second[0.84] - sr_V2.second[0.50]);
        sr_2s_down.push_back(sr_V2.second[0.50] - sr_V2.second[0.025]);
        sr_1s_down.push_back(sr_V2.second[0.50] - sr_V2.second[0.16]);
        sr_central.push_back(sr_V2.second[0.50]);
        sr_observed.push_back(sr_V2.second[-1]);
        V2_err.push_back(0.);
    }

    TGraphAsymmErrors* sr_2s_graph = new TGraphAsymmErrors(V2.size(), &V2[0], &sr_central[0], &V2_err[0], &V2_err[0], &sr_2s_down[0], &sr_2s_up[0]);
    sr_2s_graph->SetFillColor(kOrange);
    sr_2s_graph->SetFillStyle(1001);
    sr_2s_graph->GetXaxis()->SetTitle(Xaxistitle);
    sr_2s_graph->GetYaxis()->SetTitle(Yaxistitle);
    //sr_2s_graph->GetXaxis()->SetMoreLogLabels();
    //sr_2s_graph->GetYaxis()->SetMoreLogLabels();

    TGraphAsymmErrors* sr_1s_graph = new TGraphAsymmErrors(V2.size(), &V2[0], &sr_central[0], &V2_err[0], &V2_err[0], &sr_1s_down[0], &sr_1s_up[0]);
    sr_1s_graph->SetFillColor(kGreen+1);
    sr_1s_graph->SetFillStyle(1001);

    TGraphAsymmErrors* sr_central_graph = new TGraphAsymmErrors(V2.size(), &V2[0], &sr_central[0], &V2_err[0], &V2_err[0], &V2_err[0], &V2_err[0]);
    TGraphAsymmErrors* sr_observed_graph = new TGraphAsymmErrors(V2.size(), &V2[0], &sr_observed[0], &V2_err[0], &V2_err[0], &V2_err[0], &V2_err[0]);

    sr_2s_graph->Draw("A3");
    if(plotfilename.Contains("ExclusionLimit")){
        sr_2s_graph->GetXaxis()->SetRangeUser(0,15);
        sr_2s_graph->GetYaxis()->SetRangeUser(2e-8, 1e-1);
    }
    sr_1s_graph->Draw("3 same");
    sr_central_graph->Draw("L P same");
    sr_observed_graph->Draw("L P same");
    sr_observed_graph->SetLineColor(kRed);
    sr_observed_graph->SetMarkerColor(kRed);
    CMSandLumi->Draw();
    draw_line_at_1(sr_2s_graph->GetXaxis()->GetXmin(), sr_2s_graph->GetXaxis()->GetXmax());

    pad->Modified();
    c->Print(plotfilename);
    delete c;
    return;
}

double GetCorrespondingScalefactor(TString combine_filename)
{
    TString scalefactor_filename = combine_filename;
    scalefactor_filename.ReplaceAll("datacards", "ScaleFactor");
    scalefactor_filename.ReplaceAll("higgsCombine", "");
    scalefactor_filename.ReplaceAll(".AsymptoticLimits.mH120", "");
    scalefactor_filename.ReplaceAll("_run2_", "_1718_");

    TFile *scalefactor_file = new TFile(scalefactor_filename, "open");
    TH1F* scalefactor_hist = (TH1F*)scalefactor_file->Get("scalefactor");

    if(!scalefactor_hist) std::cout << "Error: no scale factor hist retrieved from " << scalefactor_filename << std::endl;
    return scalefactor_hist->GetBinContent(1);
}


CombineOutput::CombineOutput(TString filename)
{
    combine_filename = filename;
    M  = ((TString)filename(filename.Index("_M-") + 3, filename.Index("_V2-") - filename.Index("_M-") -3)).Atof();
    V2 = ((TString)filename(filename.Index("_V2-") + 4, filename.Index("_cut") - filename.Index("_V2-") - 4)).Atof();
    combine_file = new TFile(filename, "open");
    combine_tree = (TTree*) combine_file->Get("limit");
    Init(combine_tree);
}


// returns the signal strengths for each quantile in the order (0.025, 0.16, 0.50, 0.84, 0.975)
std::map<float, double> CombineOutput::GetSignalStrengths()
{
    unsigned nentries = combine_tree->GetEntries();
    std::map<float, double> signal_strengths;
    for(unsigned jentry = 0; jentry < nentries; jentry++){
        combine_tree->GetEntry(jentry);
        //if(quantileExpected > 0) signal_strengths[quantileExpected] = limit;
        signal_strengths[quantileExpected] = limit;
        if(verbose) std::cout << "quantile and limit: " << quantileExpected << " " << limit << std::endl;
    }
    return signal_strengths;
}


void CombineOutput::Init(TTree* tree)
{
    if(!tree){
        std::cout << "Tree could not be initialized" << std::endl;
        return;
    }

    tree->SetMakeClass(1);
    tree->SetBranchAddress("limit", &limit, &b_limit);
    tree->SetBranchAddress("limitErr", &limitErr, &b_limitErr);
    tree->SetBranchAddress("syst", &syst, &b_syst);
    tree->SetBranchAddress("iToy", &iToy, &b_iToy);
    tree->SetBranchAddress("iSeed", &iSeed, &b_iSeed);
    tree->SetBranchAddress("quantileExpected", &quantileExpected, &b_quantileExpected);
}


CombineOutput::~CombineOutput()
{
    delete combine_tree;
    combine_file->Close();
    delete combine_file;
}

void PrintExclusionLine(std::map<double, std::map<float, double>> exclusion_line, double quantile)
{
    std::cout << "M - V2: ";
    for(auto& line_M : exclusion_line){
        std::cout << line_M.first << " - " << line_M.second[quantile] << " | ";
    }std::cout << std::endl;
}

void PrintAllSignalStrengths(std::map<double, std::map<double, std::map<float, double>>> signal_strengths)
{
    std::cout << "--------------------" << std::endl;
    for(auto& sr_M : signal_strengths){
        std::cout << "M: " << sr_M.first << std::endl;
        for(auto& sr_V2 : sr_M.second){
            std::cout << "V2: " << sr_V2.first << std::endl;
            for(std::map<float, double>::iterator sr = sr_V2.second.begin(); sr != sr_V2.second.end(); sr++){
                std::cout << "quantile, limit: " << sr->first << " " << sr->second << std::endl;
            }
        }
    }
}

void WriteExclusionLimit(std::map<double, std::map<float, double>> lower_exclusion_limit, std::map<double, std::map<float, double>> upper_exclusion_limit, TString filename)
{
    std::cout << "Writing Limits to " << filename << std::endl;
    std::ofstream outfile;
    outfile.open(filename);
    outfile << "Lower Limits:\n";
    for(auto& sr_V2 : lower_exclusion_limit){
        outfile << "M = " << sr_V2.first << " GeV : " << sr_V2.second[0.50] << "\n";
    }
    outfile << "Upper Limits:\n";
    for(auto& sr_V2 : upper_exclusion_limit){
        outfile << "M = " << sr_V2.first << " GeV : " << sr_V2.second[0.50] << "\n";
    }
}

void WriteExclusionLimit_with_Bands(std::map<double, std::map<float, double>> lower_exclusion_limit, std::map<double, std::map<float, double>> upper_exclusion_limit, TString filename)
{
    std::cout << "Writing Limits to " << filename << std::endl;
    std::ofstream outfile;
    outfile.open(filename);
    outfile << "M - Lower_V2_central - Lower_V2_2sup - Lower_V2_1sup - Lower_V2_1sdown - Lower_V2_2sdown - Upper_V2_central - Upper_V2_2sup - Upper_V2_1sup - Upper_V2_1sdown - Upper_V2_2sdown\n";
    for(auto& sr_V2 : lower_exclusion_limit){
        outfile << sr_V2.first << " " << sr_V2.second[0.50] << " " << sr_V2.second[0.975] << " " << sr_V2.second[0.84] << " " << sr_V2.second[0.16] << " " << sr_V2.second[0.025] << " ";
        outfile << upper_exclusion_limit[sr_V2.first][0.50] << " " << upper_exclusion_limit[sr_V2.first][0.975] << " " << upper_exclusion_limit[sr_V2.first][0.84] << " " << upper_exclusion_limit[sr_V2.first][0.16] << " " << upper_exclusion_limit[sr_V2.first][0.025] << "\n";
    }
}
