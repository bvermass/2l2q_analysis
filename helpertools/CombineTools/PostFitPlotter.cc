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
        
    for(const auto& HNLpoint : HNLpoints){
        FitDiagnosticsOutput fit(workingdir + "fitDiagnostics" + HNLpoint + ".root");

        std::cout << "data max: " << fit.data_prefit_2016->GetMaximum() << " " << fit.data_prefit_1718->GetMaximum() << std::endl;
        std::cout << "bkg prefit max: " << fit.ABCD_prefit_2016->GetMaximum() << " " << fit.ABCD_prefit_1718->GetMaximum() << std::endl;
        std::cout << "bkg postfit max: " << fit.ABCD_postfit_2016->GetMaximum() << " " << fit.ABCD_postfit_1718->GetMaximum() << std::endl;

        TString flavor = "";
        if(HNLpoint.Contains("_OS")) flavor += "_OS";
        if(HNLpoint.Contains("_mm")) flavor += "_mm/";
        else if(HNLpoint.Contains("_ee")) flavor += "_ee/";
        else if(HNLpoint.Contains("_2l")) flavor += "_2l/";

        PlotComparison(workingdir + flavor, "prefit_2016" + HNLpoint + "_Shape_SR_NTight", fit.data_prefit_2016, fit.ABCD_prefit_2016);
        PlotComparison(workingdir + flavor, "postfit_2016" + HNLpoint + "_Shape_SR_NTight", fit.data_prefit_2016, fit.ABCD_postfit_2016);
        PlotComparison(workingdir + flavor, "prefit_1718" + HNLpoint + "_Shape_SR_NTight", fit.data_prefit_1718, fit.ABCD_prefit_1718);
        PlotComparison(workingdir + flavor, "postfit_1718" + HNLpoint + "_Shape_SR_NTight", fit.data_prefit_1718, fit.ABCD_postfit_1718);
    }

}
#endif

void PlotComparison(TString pathname, TString histname, TGraphAsymmErrors* data, TH1F* ABCD)
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
    //std::cout << "content and error: " << bkgForError->GetBinContent(1) << " " << bkgForError->GetBinError(1) << std::endl;


    data->SetMarkerStyle(20);
    data->SetMarkerSize(1.2);
                    
    ratioplotter.ClearSystUncs();
    ratioplotter.SetCentralRatio(data, ABCD, xaxistitle, "Obs./pred.");
    ratioplotter.AddStatVariation(ABCD, "Stat. unc.");
    ratioplotter.SetConstantFit();
    ratioplotter.Add_ABCD_SystVariation(histname, "Syst. unc.", ABCD);
    //if((histname.Contains("TightmlSV_BtoAwithCD_Shape") and !histname.Contains("CR")) or histname.Contains("CR2NoJetVetomlSV_") or histname.Contains("mlSV_CR2Jets_")) ratioplotter.Add_ABCD_SystVariation(histname, "Syst. unc.", (TH1F*)hists_bkg->GetStack()->Last());
 
    
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
    //legend.Draw("same");
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
        M  = ((TString)filename(filename.Index("_M-") + 3, filename.Index("_V2-") - filename.Index("_M-") -3)).Atof();
        V2 = ((TString)filename(filename.Index("_V2-") + 4, filename.Index("_cut") - filename.Index("_V2-") - 4)).Atof();
    }else if(filename.Contains("_V-")){
        M  = ((TString)filename(filename.Index("M-") + 2, filename.Index("_V-") - filename.Index("M-") -2)).Atof();
        double V = ((TString)filename(filename.Index("_V-") + 3, filename.Index("_mu") - filename.Index("_V-") - 3)).Atof();
        V2 = V*V;
    }
    combine_file = new TFile(filename, "open");
    data_prefit_2016 = (TGraphAsymmErrors*)  combine_file->Get("shapes_prefit/Name1_chA/data");
    data_prefit_1718 = (TGraphAsymmErrors*)  combine_file->Get("shapes_prefit/Name2_chA/data");
    ABCD_prefit_2016 = (TH1F*)               combine_file->Get("shapes_prefit/Name1_chA/total_background");
    ABCD_prefit_1718 = (TH1F*)               combine_file->Get("shapes_prefit/Name2_chA/total_background");
    ABCD_postfit_2016 = (TH1F*)              combine_file->Get("shapes_fit_s/Name1_chA/total_background");
    ABCD_postfit_1718 = (TH1F*)              combine_file->Get("shapes_fit_s/Name2_chA/total_background");
}


FitDiagnosticsOutput::~FitDiagnosticsOutput()
{
    combine_file->Close();
    delete combine_file;
}

