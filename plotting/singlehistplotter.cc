#include "singlehistplotter.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    // set general plot style
    setTDRStyle();
    gROOT->ForceStyle();

    // Argument 1: subdirectory name (currently unused as subdirectory is decided based on sample name)
    // Argument 2: partition job number (which section of the splitting)
    // Argument 3: partition (in how many sections the plotting will be split)
    // Argument 4: name of root input file
    // Argument 5: legend associated to sample
    TString subdirectory_name = (TString)argv[1];
    TString inputfilename = (TString)argv[4];
    bool is2016 = false, is2017 = false, is2018 = false;
    if(inputfilename.Contains("MiniAOD2016") or inputfilename.Contains("Run2016")) is2016 = true;
    else if(inputfilename.Contains("MiniAOD2017") or inputfilename.Contains("Run2017")) is2017 = true;
    else if(inputfilename.Contains("MiniAOD2018") or inputfilename.Contains("Run2018")) is2018 = true;
    bool is_mini_analyzer = inputfilename.Contains("hists_mini_analyzer");
    bool isData           = inputfilename.Contains("Run201");
    TFile*  sample_file   = TFile::Open(inputfilename);
    TString sample_legend = adjust_legend((TString)argv[5]);

    //this color scheme comes from the coolors.co app: https://coolors.co/4281ae-0a5a50-4b4237-d4b483-c1666b
    //maybe this combo is better: https://coolors.co/4281ae-561643-4b4237-d4b483-c1666b?
    std::vector<std::vector<int>> rgb = {{66, 129, 174}, {212, 180, 131}, {193, 102, 107}, {10, 90, 80}, {20, 30, 190}, {75, 66, 65}, {86, 22, 67}, {247, 135, 100}};
    std::vector<int> colors;
    for(int i = 0; i < rgb.size(); i++){
        colors.push_back(TColor::GetColor(rgb[i][0], rgb[i][1], rgb[i][2]));
    }

    // Name of directory where plots will end up
    TString general_pathname = make_general_pathname("plots/singlehists/", inputfilename);
    std::string corfilename = (std::string)(general_pathname + "correlations.txt");
    gSystem->Exec("rm -f " + (TString)corfilename);

    // Read identifiers from plotting/identifiers.txt and only make plots matching these tags
    std::vector<std::vector<TString>> identifiers = get_identifiers("plotting/identifiers.txt", ",");
    std::cout << "identifiers: " << std::endl;
    for(const auto& identifier : identifiers){
        for(const auto& id : identifier){
            std::cout << id << ", ";
        }std::cout << std::endl;
    }

    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    // Make the pad that will contain the plot
    TPad* pad  = new TPad("pad", "", 0., 0., 1., 1.);
    pad->Draw();
    pad->cd();

    TLegend legend = get_legend(0.2, 0.88, 0.95, 0.93, 4);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    CMSandLuminosity* CMSandLumi = new CMSandLuminosity(pad, is2016, is2017, is2018);
    Shape_SR_plottext* shapeSR_text = new Shape_SR_plottext(pad);

    int partitionjobnumber = std::atoi(argv[2]);
    int partition = std::atoi(argv[3]);
    int counter = 0;
    int counter_begin = floor(1.0 * partitionjobnumber / partition * sample_file->GetNkeys());
    int counter_end   = floor(1.0 * (partitionjobnumber + 1) / partition * sample_file->GetNkeys());
    
    TIter next(sample_file->GetListOfKeys());
    TKey* key;
    while(key = (TKey*)next()){
        if(counter >= counter_begin and counter <= counter_end){
            std::string cl(key->GetClassName());

            // -- TH1 --
            if (cl.find("TH1") != std::string::npos){ // second requirement is because TH2 also inherits from TH1
                TH1F*   sample_hist = (TH1F*)key->ReadObj();
                TString histname   = sample_hist->GetName();

                if(!check_identifiers(histname, identifiers) or sample_hist->GetMaximum() == 0){
                    delete sample_hist;
                    continue;
                }
                std::cout << "hist passed: " << histname << std::endl;
                alphanumeric_labels(sample_hist, histname);

                TString pathname_lin    = make_plotspecific_pathname(histname, general_pathname, "lin/");
                TString pathname_log    = make_plotspecific_pathname(histname, general_pathname, "log/");

                // set x range to log if necessary
                int xlog = (histname.Index("xlog") == -1)? 0 : 1;
                pad->SetLogx(xlog);
                if(xlog) divide_by_binwidth(sample_hist);
                sample_hist->GetYaxis()->SetRangeUser(0, 1.25*sample_hist->GetMaximum());

                legend.Clear();
                if(!is_mini_analyzer) legend.AddEntry(sample_hist, sample_legend);
                else {
                    if(histname.Contains("_quadABCD")) legend.AddEntry(sample_hist, "Region A+B+C+D");
                    else if(histname.Contains("_quadBCD")) legend.AddEntry(sample_hist, "Region B+C+D");
                    else if(histname.Contains("_quadAB")) legend.AddEntry(sample_hist, "Region A+B");
                    else if(histname.Contains("_quadAC")) legend.AddEntry(sample_hist, "Region A+C");
                    else if(histname.Contains("_quadCD")) legend.AddEntry(sample_hist, "Region C+D");
                    else if(histname.Contains("_quadBD")) legend.AddEntry(sample_hist, "Region B+D");
                    else if(histname.Contains("_quadA")) legend.AddEntry(sample_hist, "Region A");
                    else if(histname.Contains("_quadB")) legend.AddEntry(sample_hist, "Region B");
                    else if(histname.Contains("_quadC")) legend.AddEntry(sample_hist, "Region C");
                    else if(histname.Contains("_quadD")) legend.AddEntry(sample_hist, "Region D");
                    else if(histname.Contains("_CoverD")) legend.AddEntry(sample_hist, "C/D");
                    else if(histname.Contains("_BoverD")) legend.AddEntry(sample_hist, "B/D");
                    else if(histname.Contains("_AoverB")) legend.AddEntry(sample_hist, "A/B");
                    else if(histname.Contains("_DtoCwithCD")) legend.AddEntry(sample_hist, "C pred.");
                    else if(histname.Contains("_BtoAwithCD")) legend.AddEntry(sample_hist, "A pred.");
                    else if(histname.Contains("_CtoAwithBD")) legend.AddEntry(sample_hist, "A.pred.");
                }

                pad->Clear();
                pad->SetLogy(0);
    
                sample_hist->SetMarkerColor(colors[0]);
                sample_hist->SetLineColor(colors[0]);
                sample_hist->Draw("E0 P");
                legend.Draw("same");
                CMSandLumi->Draw();
                if(histname.Contains("Shape_SR")) shapeSR_text->Draw(histname);

                pad->Modified();
                c->Print(pathname_lin + histname + ".png");

                // Efficiencies are calculated right here as TGraphAsymmErrors
                if(histname.Index("eff_num") != -1){
                    TGraphAsymmErrors* efficiency_graph = new TGraphAsymmErrors((TH1F*)sample_hist, (TH1F*)sample_file->Get(histname(0, histname.Index("eff_num") + 4) + "den"), "cp");
                    efficiency_graph->GetXaxis()->SetTitle(sample_hist->GetXaxis()->GetTitle());
                    efficiency_graph->SetLineWidth(2);
                    efficiency_graph->GetYaxis()->SetTitle("Eff.");
                    efficiency_graph->GetHistogram()->SetMinimum(0.);
                    efficiency_graph->GetHistogram()->SetMaximum((efficiency_graph->GetHistogram()->GetMaximum() > 0.2)? 1.25 : 0.225);

                    pad->Clear();
                    legend.Clear();

                    legend.AddEntry(efficiency_graph, sample_legend);

                    efficiency_graph->Draw("AP");
                    legend.Draw("same");
                    CMSandLumi->Draw();

                    pad->Modified();
                    c->Print(pathname_lin + histname(0, histname.Index("eff_num") + 3) + ".png");
                    delete efficiency_graph;
                }

                // Mini analyzer specific plots
                if(inputfilename.Contains("hists_mini_analyzer")){
                    plot_normalized_hists(sample_file, general_pathname, sample_hist, histname, c, pad, legend, colors, CMSandLumi, shapeSR_text, {"_quadAB_", "_quadCD_"}, {"Region A+B", "Region C+D"}, "_quadAB-CD_", true);
                    plot_normalized_hists(sample_file, general_pathname, sample_hist, histname, c, pad, legend, colors, CMSandLumi, shapeSR_text, {"_quadAC_", "_quadBD_"}, {"Region A+C", "Region B+D"}, "_quadAC-BD_", true);
                    plot_normalized_hists(sample_file, general_pathname, sample_hist, histname, c, pad, legend, colors, CMSandLumi, shapeSR_text, {"_DtoCwithCD_", "_quadC_"}, {"Region C (pred.)", "Region C"}, "_quadCwithDtoC_", false);
                    plot_2_hists_with_ratio(sample_file, general_pathname, sample_hist, histname, colors, is2016, is2017, is2018, {"_BtoAwithCD_", "_quadA_"}, {"pred.", "obs."}, "_quadAwithBtoA_", false);
                    plot_normalized_hists(sample_file, general_pathname, sample_hist, histname, c, pad, legend, colors, CMSandLumi, shapeSR_text, {"_quadA_", "_quadB_"}, {"Region A", "Region B"}, "_quadA-B_", true);
                    plot_normalized_hists(sample_file, general_pathname, sample_hist, histname, c, pad, legend, colors, CMSandLumi, shapeSR_text, {"_quadA_", "_quadC_"}, {"Region A", "Region C"}, "_quadA-C_", true);
                    if(isData) plot_normalized_hists(sample_file, general_pathname, sample_hist, histname, c, pad, legend, colors, CMSandLumi, shapeSR_text, {"_quadC_", "_quadD_"}, {"Region C", "Region D"}, "_quadC-D_", true);
                    plot_normalized_hists(sample_file, general_pathname, sample_hist, histname, c, pad, legend, colors, CMSandLumi, shapeSR_text, {"_AoverB_", "_CoverD_"}, {"A/B", "C/D"}, "_AoverB-CoverD_", false);
                    plot_normalized_hists(sample_file, general_pathname, sample_hist, histname, c, pad, legend, colors, CMSandLumi, shapeSR_text, {"_cutphill_", "_cutmll_", "_cutphiORmll_", "_cutmlSV_"}, {"#Delta #phi", "m_{ll}", "#Delta #phi or m_{ll}", "m_{l,SV}"}, "_cutAll_", false);
                    plot_normalized_hists(sample_file, general_pathname, sample_hist, histname, c, pad, legend, colors, CMSandLumi, shapeSR_text, {"_cutTightphill_", "_cutTightmll_", "_cutTightphiORmll_", "_cutTightmlSV_"}, {"#Delta #phi", "m_{ll}", "#Delta #phi or m_{ll}", "m_{l,SV}"}, "_cutTightAll_", false);

                    if(isData and histname.Contains("Shape_SR") and histname.Contains("BtoAwithCD")) plot_Shape_SR_with_Signal_eff(inputfilename, pathname_lin, sample_hist, histname, c, pad, legend, colors, CMSandLumi, shapeSR_text);
                    //if(isData and histname.Contains("Shape_SR") and histname.Contains("BoverD")) plot_Shape_SR_with_Signal_AoverC(inputfilename, pathname_lin, sample_hist, histname, c, pad, legend, colors, CMSandLumi, shapeSR_text);
                }
                delete sample_hist;
            }else if(cl.find("TH2") != std::string::npos){
                TH2F *sample_hist = (TH2F*)key->ReadObj();
                TString histname = sample_hist->GetName();

                if(!check_identifiers(histname, identifiers) or sample_hist->GetMaximum() == 0){
                    delete sample_hist;
                    continue;
                }
                alphanumeric_labels_2D(sample_hist, histname);

                TString pathname_lin = make_plotspecific_pathname(histname, general_pathname, "lin/");

                pad->Clear();
                pad->SetLogy(0);

                sample_hist->SetMinimum(0);
                sample_hist->Draw(get_2D_draw_options(sample_hist));
                CMSandLumi->Draw();

                pad->Modified();
                c->Print(pathname_lin + histname + ".png");

                if(is_mini_analyzer and (histname.Contains("_PFNvs") or histname.Contains("_mllvs") or histname.Contains("_dphillvs"))){
                    double cor = sample_hist->GetCorrelationFactor();
                    std::ostringstream corstream;
                    corstream << cor;
                    std::string corstring = (std::string)histname + " correlation factor:" + corstream.str();
                    filePutContents(corfilename, corstring, true);
                }
                delete sample_hist;
            }
        }
        ++counter;
    }
}
# endif

void plot_2_hists_with_ratio(TFile* sample_file, TString general_pathname, TH1F* sample_hist, TString histname, std::vector<int> colors, bool is2016, bool is2017, bool is2018, std::vector<TString> tags, std::vector<TString> legend_tags, TString plot_tag, bool normalize_to_1)
{
    if(histname.Contains(tags[0]) and tags.size() == 2){
        TCanvas c2("c2","",700,700);
        c2.cd();

        TPad pad_histo("pad_histo", "", 0., 0.33, 1., 1.);
        pad_histo.SetTopMargin(0.07);
        pad_histo.SetBottomMargin(0.01);
        pad_histo.Draw();
        pad_histo.cd();
        float leftmargin  = pad_histo.GetLeftMargin();
        float topmargin   = pad_histo.GetTopMargin();
        float rightmargin = pad_histo.GetRightMargin();

        CMSandLuminosity CMSandLumi(&pad_histo, is2016, is2017, is2018);
        Shape_SR_plottext shapeSR_text(&pad_histo);
        TLegend legend = get_legend(0.2, 0.84, 0.95, 0.9, 4);

        c2.cd();
        TPad pad_ratio("pad_ratio", "", 0., 0., 1., 0.32);
        RatioPlot ratioplotter(&pad_ratio);

        legend.Clear();

        THStack* hists = new THStack("stack", "");

        hists->Add(sample_hist);
        if(normalize_to_1) sample_hist->Scale(1./sample_hist->Integral());
        sample_hist->SetMarkerColor(colors[0]);
        sample_hist->SetLineColor(colors[0]);
        legend.AddEntry(sample_hist, legend_tags[0], "pl");

        TString histname_extra = histname;
        histname_extra.ReplaceAll(tags[0], tags[1]);
        TH1F* hist_extra = (TH1F*)sample_file->Get(histname_extra);
        if(!hist_extra){
            std::cout << "hist " << histname_extra << " does not exist, skipping " << plot_tag << std::endl;
            return;
        }
        hist_extra->SetMarkerColor(colors[1]);
        hist_extra->SetLineColor(colors[1]);
        hists->Add(hist_extra);
        legend.AddEntry(hist_extra, legend_tags[1], "pl");
        if(normalize_to_1) hist_extra->Scale(1./hist_extra->Integral());

        ratioplotter.SetCentralRatio(hist_extra, sample_hist, sample_hist->GetXaxis()->GetTitle(), "obs/pred");
        if(histname.Contains("Shape_SR")){
            std::vector<TString> shape_sr_binnames = {"0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5", "0-1", "1-5", ">5"};
            ratioplotter.SetBinNames(shape_sr_binnames);
        }

        TString plotname = histname;
        plotname.ReplaceAll(tags[0], plot_tag);
        TString pathname_lin    = make_plotspecific_pathname(plotname, general_pathname, "lin/");
        TString pathname_log    = make_plotspecific_pathname(plotname, general_pathname, "log/");

        pad_histo.Clear();
        pad_histo.SetLogy(0);

        hists->Draw("E P hist nostack");
        hists->GetXaxis()->SetTitle(sample_hist->GetXaxis()->GetTitle());
        hists->GetYaxis()->SetTitle(sample_hist->GetYaxis()->GetTitle());
        hists->SetMaximum(1.25*hists->GetMaximum("nostack"));
        if(plot_tag.Contains("AoverB")) hists->SetMaximum(std::min((1.25*hists->GetMaximum("nostack")), 10.));
        hists->SetMinimum(0);
        legend.Draw("same");
        CMSandLumi.Draw();
        if(histname.Contains("Shape_SR")) shapeSR_text.Draw(histname);

        pad_histo.Modified();
        ratioplotter.dothething();
        c2.Print(pathname_lin + plotname + ".png");

        // Draw log version
        //pad_histo.Clear();
        //pad_histo.SetLogy(1);

        //hists->Draw("E P hist nostack");
        //hists->GetXaxis()->SetTitle(sample_hist->GetXaxis()->GetTitle());
        //hists->GetYaxis()->SetTitle(sample_hist->GetYaxis()->GetTitle());
        //hists->SetMaximum(10*hists->GetMaximum("nostack"));
        //hists->SetMinimum(std::max(1e-6, 0.5*hists->GetMinimum("nostack")));
        //legend.Draw("same");
        //CMSandLumi.Draw();
        //if(histname.Contains("Shape_SR")) shapeSR_text.Draw(histname);

        //pad_histo.Modified();
        //ratioplotter.dothething();
        //c2.Print(pathname_log + plotname + ".png");
        

        //delete hists, hist_extra;
    }
}

void plot_normalized_hists(TFile* sample_file, TString general_pathname, TH1F* sample_hist, TString histname, TCanvas* c, TPad* pad, TLegend legend, std::vector<int> colors, CMSandLuminosity* CMSandLumi, Shape_SR_plottext* shapeSR_text, std::vector<TString> tags, std::vector<TString> legend_tags, TString plot_tag, bool normalize_to_1)
{
    if(histname.Contains(tags[0])){
        legend.Clear();

        THStack* hists = new THStack("stack", "");

        hists->Add(sample_hist);
        if(normalize_to_1) sample_hist->Scale(1./sample_hist->Integral());
        sample_hist->SetMarkerColor(colors[0]);
        sample_hist->SetLineColor(colors[0]);
        legend.AddEntry(sample_hist, legend_tags[0], "pl");

        for(int i = 1; i < tags.size(); i++){
            TString histname_extra = histname;
            histname_extra.ReplaceAll(tags[0], tags[i]);
            TH1* hist_extra = (TH1*)sample_file->Get(histname_extra);
            if(!hist_extra) continue;
            hist_extra->SetMarkerColor(colors[i]);
            hist_extra->SetLineColor(colors[i]);
            hists->Add(hist_extra);
            legend.AddEntry(hist_extra, legend_tags[i], "pl");
            if(normalize_to_1) hist_extra->Scale(1./hist_extra->Integral());
        }

        TString plotname = histname;
        plotname.ReplaceAll(tags[0], plot_tag);
        TString pathname_lin    = make_plotspecific_pathname(plotname, general_pathname, "lin/");
        TString pathname_log    = make_plotspecific_pathname(plotname, general_pathname, "log/");

        pad->Clear();
        pad->SetLogy(0);

        hists->Draw("E P hist nostack");
        hists->GetXaxis()->SetTitle(sample_hist->GetXaxis()->GetTitle());
        hists->GetYaxis()->SetTitle(sample_hist->GetYaxis()->GetTitle());
        hists->SetMaximum(1.25*hists->GetMaximum("nostack"));
        if(plot_tag.Contains("AoverB")) hists->SetMaximum(std::min((1.25*hists->GetMaximum("nostack")), 10.));
        hists->SetMinimum(0);
        legend.Draw("same");
        CMSandLumi->Draw();
        if(histname.Contains("Shape_SR")) shapeSR_text->Draw(histname);

        pad->Modified();
        c->Print(pathname_lin + plotname + ".png");

        // Draw log version
        //pad->Clear();
        //pad->SetLogy(1);

        //hists->Draw("E P hist nostack");
        //hists->GetXaxis()->SetTitle(sample_hist->GetXaxis()->GetTitle());
        //hists->GetYaxis()->SetTitle(sample_hist->GetYaxis()->GetTitle());
        //hists->SetMaximum(10*hists->GetMaximum("nostack"));
        //hists->SetMinimum(std::max(1e-6, 0.5*hists->GetMinimum("nostack")));
        //legend.Draw("same");
        //CMSandLumi->Draw();
        //if(histname.Contains("Shape_SR")) shapeSR_text->Draw(histname);

        //pad->Modified();
        //c->Print(pathname_log + plotname + ".png");
    }
}

void plot_Shape_SR_with_Signal_AoverC(TString filename, TString pathname_lin, TH1F* sample_hist, TString histname, TCanvas* c, TPad* pad, TLegend legend, std::vector<int> colors, CMSandLuminosity* CMSandLumi, Shape_SR_plottext* shapeSR_text)
{
    if(!histname.Contains("M-") or !histname.Contains("V2-")) return;

    pad->Clear();
    pad->SetLogy(0);
    legend.Clear();

    sample_hist->SetMarkerColor(kBlack);
    sample_hist->SetLineColor(kBlack);

    //get mass, flavor, year for correct HNL samples
    TString mass = (TString)histname(histname.Index("_M-"), histname.Index("_V2-") - histname.Index("_M-"));
    TString flavor;
    if(histname.Contains("_mm")) flavor = "_mu";
    if(histname.Contains("_ee")) flavor = "_e";
    if(histname.Contains("_2l") or histname.Contains("_em") or histname.Contains("_me")) flavor = "_2l";

    TString year;
    if(filename.Contains("2016")) year = "_MiniAOD2016";
    if(filename.Contains("2017")) year = "_MiniAOD2017";
    if(filename.Contains("2018")) year = "_MiniAOD2018";

    THStack* hists = new THStack("stack", "");
    hists->Add(sample_hist);
    hists->Draw("E P hist nostack");
    legend.AddEntry(sample_hist, "Data pred.", "pl");

    TH1F *m2_eff, *m3_eff, *m4_eff, *m5_eff, *m6_eff, *m8_eff, *m10_eff, *m12_eff, *m14_eff;
    if(mass == "_M-5" or mass == "_M-2" or mass == "_M-3" or mass == "_M-4"){
        m2_eff = get_HNL_AoverC_ABCD(filename, histname, "_M-2", flavor, year, colors[1]);
        m2_eff->Draw("same P");
        legend.AddEntry(m2_eff, "M-2 A/C", "pl");
        m3_eff = get_HNL_AoverC_ABCD(filename, histname, "_M-3", flavor, year, colors[2]);
        m3_eff->Draw("same P");
        legend.AddEntry(m3_eff, "M-3 A/C", "pl");
        m4_eff = get_HNL_AoverC_ABCD(filename, histname, "_M-4", flavor, year, colors[3]);
        m4_eff->Draw("same P");
        legend.AddEntry(m4_eff, "M-4 A/C", "pl");
        m5_eff = get_HNL_AoverC_ABCD(filename, histname, "_M-5", flavor, year, colors[4]);
        m5_eff->Draw("same P");
        legend.AddEntry(m5_eff, "M-5 A/C", "pl");
    }else {
        m6_eff = get_HNL_AoverC_ABCD(filename, histname, "_M-6", flavor, year, colors[1]);
        m6_eff->Draw("same P");
        legend.AddEntry(m6_eff, "M-6 A/C", "pl");
        m8_eff = get_HNL_AoverC_ABCD(filename, histname, "_M-8", flavor, year, colors[2]);
        m8_eff->Draw("same P");
        legend.AddEntry(m8_eff, "M-8 A/C", "pl");
        m10_eff = get_HNL_AoverC_ABCD(filename, histname, "_M-10", flavor, year, colors[3]);
        m10_eff->Draw("same P");
        legend.AddEntry(m10_eff, "M-10 A/C", "pl");
        m12_eff = get_HNL_AoverC_ABCD(filename, histname, "_M-12", flavor, year, colors[4]);
        m12_eff->Draw("same P");
        legend.AddEntry(m12_eff, "M-12 A/C", "pl");
        m14_eff = get_HNL_AoverC_ABCD(filename, histname, "_M-14", flavor, year, colors[5]);
        m14_eff->Draw("same P");
        legend.AddEntry(m14_eff, "M-14 A/C", "pl");
    }

    legend.Draw("same");
    CMSandLumi->Draw();
    if(histname.Contains("Shape_SR")) shapeSR_text->Draw(histname);

    pad->Modified();
    c->Print(pathname_lin + histname + "_withHNL.png");

    //delete m2_eff, m3_eff, m4_eff, m5_eff, m6_eff, m8_eff, m10_eff, m12_eff, m14_eff;
}

void plot_Shape_SR_with_Signal_eff(TString filename, TString pathname_lin, TH1F* sample_hist, TString histname, TCanvas* c, TPad* pad, TLegend legend, std::vector<int> colors, CMSandLuminosity* CMSandLumi, Shape_SR_plottext* shapeSR_text)
{
    if(!histname.Contains("M-") or !histname.Contains("V2-")) return;

    pad->Clear();
    pad->SetLogy(0);
    legend.Clear();

    sample_hist->SetMarkerColor(kBlack);
    sample_hist->SetLineColor(kBlack);

    //get mass, flavor, year for correct HNL samples
    TString mass = (TString)histname(histname.Index("_M-"), histname.Index("_V2-") - histname.Index("_M-"));
    TString flavor;
    if(histname.Contains("_mm")) flavor = "_mu";
    if(histname.Contains("_ee")) flavor = "_e";
    if(histname.Contains("_2l") or histname.Contains("_em") or histname.Contains("_me")) flavor = "_2l";

    TString year;
    if(filename.Contains("2016")) year = "_MiniAOD2016";
    if(filename.Contains("2017")) year = "_MiniAOD2017";
    if(filename.Contains("2018")) year = "_MiniAOD2018";

    legend.AddEntry(sample_hist, "Data eff", "pl");

    // Make the pad that will contain the plot
    c->cd();
    TPad* pad_eff  = new TPad("pad_eff", "", 0., 0., 1., 1.);
    pad_eff->Draw();
    pad_eff->cd();
    pad_eff->SetFillStyle(4000);
    pad_eff->SetFrameFillStyle(0);
    pad_eff->SetTicky(0);
    pad_eff->SetRightMargin(0.07);

    TH1F* m2_eff, *m3_eff, *m4_eff, *m5_eff, *m6_eff, *m8_eff, *m10_eff, *m12_eff, *m14_eff;
    if(mass == "_M-5" or mass == "_M-2" or mass == "_M-3" or mass == "_M-4"){
        m2_eff = get_HNL_eff_ABCD(filename, histname, "_M-2", flavor, year, colors[1]);
        m2_eff->Draw("E P Y+");
        legend.AddEntry(m2_eff, "M-2 eff", "pl");
        m3_eff = get_HNL_eff_ABCD(filename, histname, "_M-3", flavor, year, colors[2]);
        m3_eff->Draw("same E P Y+");
        legend.AddEntry(m3_eff, "M-3 eff", "pl");
        m4_eff = get_HNL_eff_ABCD(filename, histname, "_M-4", flavor, year, colors[3]);
        m4_eff->Draw("same E P Y+");
        legend.AddEntry(m4_eff, "M-4 eff", "pl");
        m5_eff = get_HNL_eff_ABCD(filename, histname, "_M-5", flavor, year, colors[4]);
        m5_eff->Draw("same E P Y+");
        legend.AddEntry(m5_eff, "M-5 eff", "pl");
    }else {
        m6_eff = get_HNL_eff_ABCD(filename, histname, "_M-6", flavor, year, colors[1]);
        m6_eff->Draw("E P Y+");
        legend.AddEntry(m6_eff, "M-6 eff", "pl");
        m8_eff = get_HNL_eff_ABCD(filename, histname, "_M-8", flavor, year, colors[2]);
        m8_eff->Draw("same E P Y+");
        legend.AddEntry(m8_eff, "M-8 eff", "pl");
        m10_eff = get_HNL_eff_ABCD(filename, histname, "_M-10", flavor, year, colors[3]);
        m10_eff->Draw("same E P Y+");
        legend.AddEntry(m10_eff, "M-10 eff", "pl");
        m12_eff = get_HNL_eff_ABCD(filename, histname, "_M-12", flavor, year, colors[4]);
        m12_eff->Draw("same E P Y+");
        legend.AddEntry(m12_eff, "M-12 eff", "pl");
        m14_eff = get_HNL_eff_ABCD(filename, histname, "_M-14", flavor, year, colors[5]);
        m14_eff->Draw("same E P Y+");
        legend.AddEntry(m14_eff, "M-14 eff", "pl");
    }

    pad->cd();
    pad->SetTicky(0);
    pad->SetRightMargin(0.07);
    THStack* hists = new THStack("stack", "");
    hists->Add(sample_hist);
    //hists->Add(HNL_hist_quadA);
    //hists->Add(HNL_hist_quadB);
    //hists->Add(HNL_hist_quadC);
    //hists->Add(HNL_hist_quadD);


    //legend.AddEntry(HNL_hist_quadA, adjust_legend("HNL" + mass), "pl");
    //legend.AddEntry(HNL_hist_quadB, "quad B", "pl");
    //legend.AddEntry(HNL_hist_quadC, "quad C", "pl");
    //legend.AddEntry(HNL_hist_quadD, "quad D", "pl");

    hists->Draw("E P hist nostack");
    legend.Draw("same");
    CMSandLumi->Draw();
    if(histname.Contains("Shape_SR")) shapeSR_text->Draw(histname);

    pad->Modified();
    c->Print(pathname_lin + histname + "_withHNL.png");
    pad->SetTicky(1);
    pad->SetRightMargin(0.04);
    pad_eff->Clear();
}

TH1F* get_HNL_AoverC_ABCD(TString filename, TString histname, TString mass, TString flavor, TString year, int colors)
{
    TString full_HNL_name = (TString)filename(0, filename.Index("_analyzer_") + 10) + "HeavyNeutrino_lljj" + mass + "_V-combined" + flavor + "_massiveAndCKM_LO" + year + ".root";
    if(!gSystem->AccessPathName(full_HNL_name,kFileExists)){
        std::cout << "HNL file does not exist: " << full_HNL_name << std::endl;
        return nullptr;
    }
    std::unique_ptr<TFile>  HNL_file(new TFile(full_HNL_name, "read"));

    TString histname_quadA = histname;
    histname_quadA.ReplaceAll("BtoAwithCD", "quadA");
    TH1F* HNL_hist_quadA = (TH1F*)HNL_file->Get(histname_quadA);
    //HNL_hist_quadA->SetMarkerColor(colors[0]);
    //HNL_hist_quadA->SetLineColor(colors[0]);

    histname_quadA.ReplaceAll("quadA", "quadC");
    TH1F* HNL_hist_quadC = (TH1F*)HNL_file->Get(histname_quadA);
    //HNL_hist_quadC->SetMarkerColor(colors[3]);
    //HNL_hist_quadC->SetLineColor(colors[3]);

    TH1F* HNL_hist_effA = (TH1F*)HNL_hist_quadA->Clone();
    HNL_hist_effA->Add(HNL_hist_quadC);

    HNL_hist_effA->Divide(HNL_hist_quadA, HNL_hist_effA);
    HNL_hist_effA->SetMarkerColor(colors);
    HNL_hist_effA->SetLineColor(colors);
    HNL_hist_effA->GetYaxis()->SetRangeUser(0, 1.1);

    //HNL_file->Close();
    //delete HNL_file;
    return HNL_hist_effA;
}

TH1F* get_HNL_eff_ABCD(TString filename, TString histname, TString mass, TString flavor, TString year, int colors)
{
    TString full_HNL_name = (TString)filename(0, filename.Index("_analyzer_") + 10) + "HeavyNeutrino_lljj" + mass + "_V-combined" + flavor + "_massiveAndCKM_LO" + year + ".root";
    if(gSystem->AccessPathName(full_HNL_name,kFileExists)){ std::cout << "file " << full_HNL_name << " does not exist, returning nullpointer" << std::endl; return nullptr;}
    std::unique_ptr<TFile>  HNL_file(new TFile(full_HNL_name, "read"));

    TString histname_quadA = histname;
    histname_quadA.ReplaceAll("BtoAwithCD", "quadA");
    TH1F* HNL_hist_quadA = (TH1F*)HNL_file->Get(histname_quadA);
    //HNL_hist_quadA->SetMarkerColor(colors[0]);
    //HNL_hist_quadA->SetLineColor(colors[0]);

    //getting quadB, C and D as well and calculating percent of events in A
    histname_quadA.ReplaceAll("quadA", "quadB");
    TH1F* HNL_hist_quadB = (TH1F*)HNL_file->Get(histname_quadA);
    //HNL_hist_quadB->SetMarkerColor(colors[2]);
    //HNL_hist_quadB->SetLineColor(colors[2]);
    histname_quadA.ReplaceAll("quadB", "quadC");
    TH1F* HNL_hist_quadC = (TH1F*)HNL_file->Get(histname_quadA);
    //HNL_hist_quadC->SetMarkerColor(colors[3]);
    //HNL_hist_quadC->SetLineColor(colors[3]);
    histname_quadA.ReplaceAll("quadC", "quadD");
    TH1F* HNL_hist_quadD = (TH1F*)HNL_file->Get(histname_quadA);
    //HNL_hist_quadD->SetMarkerColor(colors[4]);
    //HNL_hist_quadD->SetLineColor(colors[4]);

    TH1F* HNL_hist_effA = (TH1F*)HNL_hist_quadA->Clone();
    HNL_hist_effA->Add(HNL_hist_quadB);
    HNL_hist_effA->Add(HNL_hist_quadC);
    HNL_hist_effA->Add(HNL_hist_quadD);

    HNL_hist_effA->Divide(HNL_hist_quadA, HNL_hist_effA);
    HNL_hist_effA->SetMarkerColor(colors);
    HNL_hist_effA->SetLineColor(colors);
    HNL_hist_effA->GetYaxis()->SetRangeUser(0, 1.1);

    //HNL_file->Close();
    //delete HNL_file;
    return HNL_hist_effA;
}
