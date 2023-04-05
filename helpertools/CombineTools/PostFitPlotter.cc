#include "PostFitPlotter.h"

# ifndef __CINT__
int main()
{
    //TString HNLpoint = "M-5_V2-6e-06_mu_run2_majorana";
    TString workingdir = "/user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/postfit/";
    std::vector<TString> HNLpoints = {
        "_mm_M-3_V2-4e-06_run2_majorana",
        "_mm_M-5_V2-4e-06_run2_majorana",
        "_mm_M-6_V2-2e-06_run2_majorana",
        //"_mm_M-10_V2-2e-06_run2_majorana",
        "_mm_M-12_V2-2e-06_run2_majorana",
        "_OS_mm_M-3_V2-4e-06_run2_dirac",
        "_OS_mm_M-5_V2-4e-06_run2_dirac",
        "_OS_mm_M-6_V2-2e-06_run2_dirac",
        //"_OS_mm_M-10_V2-2e-06_run2_dirac",
        "_OS_mm_M-12_V2-2e-06_run2_dirac",
        "_ee_M-3_V2-4e-06_run2_majorana",
        "_ee_M-5_V2-4e-06_run2_majorana",
        "_ee_M-6_V2-2e-06_run2_majorana",
        //"_ee_M-10_V2-2e-06_run2_majorana",
        "_ee_M-12_V2-2e-06_run2_majorana",
        "_OS_ee_M-3_V2-4e-06_run2_dirac",
        "_OS_ee_M-5_V2-4e-06_run2_dirac",
        "_OS_ee_M-6_V2-2e-06_run2_dirac",
        //"_OS_ee_M-10_V2-2e-06_run2_dirac",
        "_OS_ee_M-12_V2-2e-06_run2_dirac",
        "_2l_M-3_V2-4e-06_run2_majorana",
        "_2l_M-5_V2-4e-06_run2_majorana",
        "_2l_M-6_V2-2e-06_run2_majorana",
        //"_2l_M-10_V2-2e-06_run2_majorana",
        "_2l_M-12_V2-2e-06_run2_majorana",
        "_OS_2l_M-3_V2-4e-06_run2_dirac",
        "_OS_2l_M-5_V2-4e-06_run2_dirac",
        //"_OS_2l_M-6_V2-2e-06_run2_dirac",
        //"_OS_2l_M-10_V2-2e-06_run2_dirac",
        "_OS_2l_M-12_V2-2e-06_run2_dirac",
    };
        
    std::vector<double> signal_strengths, srLoErr, srHiErr;
    for(const auto& HNLpoint : HNLpoints){
        FitDiagnosticsOutput fit(workingdir + "fitDiagnostics" + HNLpoint + ".root");
        if(fit.fit_status != 0) continue;
        signal_strengths.push_back(fit.r);
        srLoErr.push_back(fit.rLoErr);
        srHiErr.push_back(fit.rHiErr);

        std::cout << "data max: " << fit.data_prefit_2016->GetMaximum() << " " << fit.data_prefit_1718->GetMaximum() << std::endl;
        std::cout << "bkg prefit max: " << fit.ABCD_prefit_2016->GetMaximum() << " " << fit.ABCD_prefit_1718->GetMaximum() << std::endl;
        std::cout << "bkg postfit max: " << fit.ABCD_postfit_2016->GetMaximum() << " " << fit.ABCD_postfit_1718->GetMaximum() << std::endl;
        std::cout << "sig prefit max: " << fit.sig_prefit_2016->GetMaximum() << " " << fit.sig_prefit_1718->GetMaximum() << std::endl;
        std::cout << "sig postfit max: " << fit.sig_postfit_2016->GetMaximum() << " " << fit.sig_postfit_1718->GetMaximum() << std::endl;

        TString flavor = "";
        if(HNLpoint.Contains("_OS")) flavor += "_OS";
        if(HNLpoint.Contains("_mm")) flavor += "_mm/";
        else if(HNLpoint.Contains("_ee")) flavor += "_ee/";
        else if(HNLpoint.Contains("_2l")) flavor += "_2l/";

        PlotComparison(workingdir + flavor, "prefit_2016" + HNLpoint + "_Shape_SR_NTight", fit.data_prefit_2016, fit.ABCD_prefit_2016, fit.sig_prefit_2016, fit.M_str, fit.V2_str);
        PlotComparison(workingdir + flavor, "postfit_2016" + HNLpoint + "_Shape_SR_NTight", fit.data_prefit_2016, fit.ABCD_postfit_2016, fit.sig_postfit_2016, fit.M_str, fit.V2_str);
        PlotComparison(workingdir + flavor, "prefit_1718" + HNLpoint + "_Shape_SR_NTight", fit.data_prefit_1718, fit.ABCD_prefit_1718, fit.sig_prefit_1718, fit.M_str, fit.V2_str);
        PlotComparison(workingdir + flavor, "postfit_1718" + HNLpoint + "_Shape_SR_NTight", fit.data_prefit_1718, fit.ABCD_postfit_1718, fit.sig_postfit_1718, fit.M_str, fit.V2_str);
    }

    for(unsigned i = 0; i < signal_strengths.size(); i++){
        std::cout << HNLpoints[i] << ": " << signal_strengths[i] << " - " << srLoErr[i] << " + " << srHiErr[i] << std::endl;
    }
}
#endif

void PlotComparison(TString pathname, TString histname, TGraphAsymmErrors* data, TH1F* ABCD, TH1F* sig, TString M, TString V2)
{
    bool wideplots = histname.Contains("_2l_");
    gSystem->Exec("mkdir -p " + pathname);
    // set general plot style
    setTDRStyle(wideplots);
    gROOT->ForceStyle();
    gStyle->SetErrorX(0);

    std::vector<int> rgb_Pred = {174,71,76};
    int color_Pred = TColor::GetColor(rgb_Pred[0], rgb_Pred[1], rgb_Pred[2]);
    TString xaxistitle = "#Delta (PV-SV)_{2D} [cm]";
    TString yaxistitle = "Events";
    
    
    TCanvas* c = new TCanvas("c","",wideplots? 1200 : 700,700);
    c->cd();
    TPad* pad_histo  = new TPad("pad_histo", "", 0., 0.33, 1., 1.);
    pad_histo->SetTopMargin(0.07);
    pad_histo->SetBottomMargin(0.);
    pad_histo->Draw();
    pad_histo->cd();
    
    
    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad_histo, histname.Contains("2016"), histname.Contains("1718"), histname.Contains("1718"), false);
    Shape_SR_plottext* shapeSR_text = new Shape_SR_plottext(pad_histo);
    
    // Make the pad that will contain the ratio data/MC
    c->cd(); // first return to canvas so that second pad will be drawn in here and not in pad_histo
    TPad* pad_ratio = new TPad("pad_ratio", "", 0., 0., 1., 0.33);
    RatioPlot ratioplotter(pad_ratio, wideplots);

    ABCD->SetFillStyle(1001);
    ABCD->SetFillColor(color_Pred);
    ABCD->SetFillStyle(color_Pred);
    ABCD->SetLineColor(color_Pred);
    ABCD->SetLineWidth(1);

    THStack* hists_bkg = new THStack("stack_bkg", ";"  + xaxistitle + ";" + yaxistitle);
    hists_bkg->Add(ABCD);
    TH1F* bkgForError = (TH1F*) hists_bkg->GetStack()->Last()->Clone();
    //TH1F* bkgForError = (TH1F*) ABCD->Clone();
    bkgForError->SetFillStyle(3244);
    bkgForError->SetFillColor(kGray+2);
    bkgForError->SetLineColor(kGray+2);
    bkgForError->SetMarkerStyle(0);
    std::cout << "content and error: " << bkgForError->GetBinContent(1) << " " << bkgForError->GetBinError(1) << std::endl;


    data->SetMarkerStyle(20);
    data->SetMarkerSize(1.2);

    sig->SetLineColor(4);
    sig->SetMarkerColor(4);
    sig->SetLineWidth(3);
                    
    ratioplotter.ClearSystUncs();
    ratioplotter.SetCentralRatio(data, ABCD, xaxistitle, "Obs./pred.");
    ratioplotter.AddStatVariation(ABCD, "Stat. unc.");
    //ratioplotter.SetConstantFit();
    ratioplotter.Add_ABCD_SystVariation(histname, "Syst. unc.", ABCD);
    //if((histname.Contains("TightmlSV_BtoAwithCD_Shape") and !histname.Contains("CR")) or histname.Contains("CR2NoJetVetomlSV_") or histname.Contains("mlSV_CR2Jets_")) ratioplotter.Add_ABCD_SystVariation(histname, "Syst. unc.", (TH1F*)hists_bkg->GetStack()->Last());
 
    TLegend legend = get_legend(wideplots? 0.1 : 0.2, 0.83, wideplots? 0.5 : 0.8, 0.91, 3);
    legend.Clear();
    legend.AddEntry(data, "Data", "pl");
    legend.AddEntry(ABCD, "Pred.", "f");
    legend.AddEntry(sig, "HNL "+M+"GeV V^{2}="+V2.ReplaceAll("-06", "^{-6}"), "l");
    
    // Draw everything
    pad_histo->cd();
    pad_histo->Clear();
    pad_histo->SetLogy(0);

    hists_bkg->Draw("hist");
    bkgForError->Draw("E2 same");
    hists_bkg->SetMaximum(1.35*std::max(ABCD->GetMaximum(), data->GetHistogram()->GetMaximum()));
    hists_bkg->SetMinimum(0.);
    //if(hists_signal->GetNhists() != 0) hists_signal->Draw("hist nostack same");
    //if(hists_signal->GetNhists() != 0) hists_signal->Draw("E nostack same");
    //data->Draw("E0 X0 P same");
    data->Draw("P Z same");
    sig->Draw("hist same");
    legend.Draw("same");
    CMSandLumi->add_flavor(histname);
    CMSandLumi->Draw();
    shapeSR_text->Draw(histname);
    
    pad_histo->Modified();

    // Draw ratio data/MC if data is present
    ratioplotter.dothething();
    //ratioplotter.draw_ABCD_CRline(histname, data_hist->GetXaxis()->GetXmin(), data_hist->GetXaxis()->GetXmax());

    c->Print(pathname + histname + ".png");
}


FitDiagnosticsOutput::FitDiagnosticsOutput(TString filename)
{
    combine_filename = filename;
    if(filename.Contains("_V2-")){
        M_str = (TString)filename(filename.Index("_M-") + 3, filename.Index("_V2-") - filename.Index("_M-") -3);
        M  = M_str.Atof();
        V2_str = (TString)filename(filename.Index("_V2-") + 4, filename.Index("_run2") - filename.Index("_V2-") - 4);
        V2 = V2_str.Atof();

    }else if(filename.Contains("_V-")){
        M_str  = (TString)filename(filename.Index("M-") + 2, filename.Index("_V-") - filename.Index("M-") -2);
        M  = M_str.Atof();
        double V = ((TString)filename(filename.Index("_V-") + 3, filename.Index("_mu") - filename.Index("_V-") - 3)).Atof();
        V2 = V*V;
        V2_str = (TString)filename(filename.Index("_V-") + 3, filename.Index("_mu") - filename.Index("_V-") - 3);
    }
    combine_file = new TFile(filename, "open");
    data_prefit_2016 = (TGraphAsymmErrors*)  combine_file->Get("shapes_prefit/Name1_chA/data");
    data_prefit_1718 = (TGraphAsymmErrors*)  combine_file->Get("shapes_prefit/Name2_chA/data");
    sig_prefit_2016 = (TH1F*)                combine_file->Get("shapes_prefit/Name1_chA/HNL_M-"+M_str);
    sig_prefit_1718 = (TH1F*)                combine_file->Get("shapes_prefit/Name2_chA/HNL_M-"+M_str);
    ABCD_prefit_2016 = (TH1F*)               combine_file->Get("shapes_prefit/Name1_chA/total_background");
    ABCD_prefit_1718 = (TH1F*)               combine_file->Get("shapes_prefit/Name2_chA/total_background");
    ABCD_postfit_2016 = (TH1F*)              combine_file->Get("shapes_fit_s/Name1_chA/total_background");
    ABCD_postfit_1718 = (TH1F*)              combine_file->Get("shapes_fit_s/Name2_chA/total_background");
    sig_postfit_2016 = (TH1F*)               combine_file->Get("shapes_fit_s/Name1_chA/HNL_M-"+M_str);
    sig_postfit_1718 = (TH1F*)               combine_file->Get("shapes_fit_s/Name2_chA/HNL_M-"+M_str);

    tree_fit_sb = (TTree*)combine_file->Get("tree_fit_sb");
    tree_fit_sb->SetBranchAddress("fit_status", &fit_status, &b_fit_status);
    tree_fit_sb->SetBranchAddress("r", &r, &b_r);
    tree_fit_sb->SetBranchAddress("rLoErr", &rLoErr, &b_rLoErr);
    tree_fit_sb->SetBranchAddress("rHiErr", &rHiErr, &b_rHiErr);
    tree_fit_sb->GetEntry(0);

    std::cout << "fit status: " << fit_status << " r: " << r << std::endl;
    if(fit_status != 0){
        std::cout << "**********" << std::endl;
        std::cout << "FIT FAILED" << std::endl;
        std::cout << "**********" << std::endl;
    }
}


FitDiagnosticsOutput::~FitDiagnosticsOutput()
{
    combine_file->Close();
    delete combine_file;
}

