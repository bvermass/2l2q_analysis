#include "helper_plotter_functions.h"

std::vector<std::vector<TString>> get_identifiers(TString identifier_filename, const char* delim)
{
    std::string line;
    std::ifstream identifier_file (identifier_filename);
    std::vector<std::vector<TString>> identifiers; // 2D vector, vector of vectors where inner vectors are to be used in AND mode (outer in OR mode)
    if(identifier_file.is_open()){
        while(std::getline(identifier_file, line)){
            std::vector<TString> AND_identifiers;
            size_t start, end = 0;
            while((start = line.find_first_not_of(delim, end)) != std::string::npos){
                end = line.find(delim, start);
                AND_identifiers.push_back(line.substr(start, end - start));
            }
            identifiers.push_back(AND_identifiers);
        }
        identifier_file.close();
    }
    return identifiers;
}


bool check_identifiers(TString histname, std::vector<std::vector<TString>> identifiers)
{
    // Inner vector of strings are parts of the histname that have to match altogether, e.g. _OS_e AND _mll have to be in the name (put as _OS_e,_mll in identifier.txt)
    // Outer vector is in OR mode for the tags (different lines in identifier.txt)
    bool check = true;
    for(auto& stringvector : identifiers){
        check = true;
        for(TString id : stringvector){
            if(histname.Index(id) != -1) continue;
            check = false;
            break;
        }
        if(check) break;
    }
    return check;
}


TString make_general_pathname(const TString& plottype, TString specific_dir)
{
    // pathname structure example: plots/multihists/HNL_358e/ and after this plot specific directories can follow
    // or plots/singlehists/final/WJets/ and then plotspecific stuff
    if(plottype == "plots/singlehists/"){
        TString filename = specific_dir; // specific_dir is actually the full filename in 'singlehists' case
        specific_dir = filename(filename.Index("histograms/") + 11, filename.Index("full_analyzer/") - 11 - filename.Index("histograms/"));
        if(filename.Index("HeavyNeutrino") != -1) specific_dir += filename(filename.Index("HeavyNeutrino") + 14, filename.Index(".root") - filename.Index("HeavyNeutrino") - 14) + "/";
        else if(filename.Index("Background") != -1) specific_dir += filename(filename.Index("Background") + 11, filename.Index(".root") - filename.Index("Background") - 11) + "/";
        else if(filename.Index("Run") != -1) specific_dir += filename(filename.Index("Run"), filename.Index(".root") - filename.Index("Run")) + "/";
    }

    return "/user/bvermass/public/2l2q_analysis/" + plottype + specific_dir;
}


TString make_plotspecific_pathname(const TString& histname, const TString& pathname, const TString& linorlog)
{
    // append directories such as SS/OS, e/mu or HLT to pathname
    TString gen             = (histname.Index("gen_") == -1)?           "" : "gen/";
    TString eormu           = (histname.Index("_ee_") == -1 && histname.Index("Ele") == -1 && histname.Index("_e.") == -1)? ((histname.Index("_mm") == -1 && histname.Index("Mu") == -1 && histname.Index("_mu.") == -1)? "" : "mu/") : "e/";
    TString SSorOS          = (histname.Index("_OS_") == -1)? ((histname.Index("_SS_") == -1)? "" : "SS/") : "OS/";
    TString HLT             = (histname.Index("HLT_") == -1)?           "" : "HLT/";
    TString control_region  = (histname.Index("_CR") == -1)?            "" : "CR/";
    TString partialcuts     = (histname.Index("before") == -1 && histname.Index("after") == -1 && histname.Index("_Training") == -1)?         "" : "partialcuts/";
    TString KVF             = (histname.Index("_KVF_") == -1)?          "" : "KVF/";
    TString IVF             = (histname.Index("_IVF_") == -1)?          "" : "IVF/";
    TString jetl2           = (histname.Index("_jetl2_") == -1)?        "" : "jetl2/";
    TString oldID           = (histname.Index("_oldID_") == -1)?        "" : "oldID/";
    TString invVtx          = (histname.Index("_invVtx_") == -1)?       "" : "invVtx/";
    TString eff             = (histname.Index("_eff") == -1)?           "" : "eff/";
    TString invIVFSVgenreco = (histname.Index("_invIVFSVgenreco") == -1)? "" : "invIVFSVgenreco/";
    TString endofselection  = (histname.Index("_endofselection_") == -1)? "" : "endofselection/";
    TString Bool            = (histname.Index("_Bool_") == -1)? "" : "Bool/";

    TString fullname = pathname + linorlog + gen + HLT + eormu + SSorOS + Bool + control_region + partialcuts + KVF + IVF + jetl2 + oldID + invVtx + eff + invIVFSVgenreco + endofselection;
    gSystem->Exec("mkdir -p " + fullname);
    return fullname;
}


TLegend get_legend(double xmin, double ymin, double xmax, double ymax, int Ncolumns)
{
    TLegend legend = TLegend(xmin, ymin, xmax, ymax);
    legend.SetNColumns(Ncolumns);
    legend.SetFillStyle(0);
    
    return legend;
}


TString adjust_legend(TString legend)
{
    TString adjusted_legend = legend.ReplaceAll("_", " ");
    return adjusted_legend;
}


TLatex get_latex(double textsize, int textalign, int textfont)
{
    TLatex textltx;//0.9,0.905,text);//"35.9 fb^{-1} (13 TeV)"); 
    textltx.SetNDC();
    textltx.SetTextAlign(textalign);
    textltx.SetTextFont(textfont);
    textltx.SetTextSize(textsize);
    textltx.SetTextColor(kBlack);
    return textltx;
}


int get_color(TString legend)
{
    if(legend.Index("Bkg")           != -1) return kOrange+4;
    else if(legend.Index("W+Jets")   != -1) return kRed+3;
    else if(legend.Index("DY")       != -1) return kOrange-1;
    else if(legend.Index("t#bar{t}") != -1) return kCyan-3;
    else if(legend.Index("Diboson")  != -1) return kGreen+3;
    else if(legend.Index("Triboson") != -1) return kRed+3;
    else if(legend.Index("Top")      != -1) return kBlue+2;
    else if(legend.Index("M-15")   != -1) return kBlack;
    else if(legend.Index("M-3")    != -1) return kRed-9;
    else if(legend.Index("M-5")    != -1) return kGreen-9;
    else if(legend.Index("M-8")    != -1) return kMagenta-7;
    else if(legend.Index("M-10")   != -1) return kCyan-2;
    else return kBlack;
}


TH1F get_histoRatio(TH1F* data, TH1F* MC, TString xaxistitle)
{
    TH1F histo_ratio("data/MC", ";" + xaxistitle + ";data/MC", data->GetNbinsX(), data->GetXaxis()->GetXmin(), data->GetXaxis()->GetXmax());
    histo_ratio.Divide(data, MC);

    histo_ratio.GetXaxis()->SetLabelSize(0.09);
    histo_ratio.GetYaxis()->SetLabelSize(0.09);
    histo_ratio.GetXaxis()->SetTitleSize(0.09);
    histo_ratio.GetYaxis()->SetTitleSize(0.09);
    histo_ratio.GetYaxis()->SetTitleOffset(0.7);
    histo_ratio.SetMinimum(0);
    histo_ratio.SetMaximum(2);

    return histo_ratio;
}


void draw_line_at_1(double xmin, double xmax)
{
    TLine line;
    line.SetLineStyle(2);
    line.DrawLine(xmin, 1., xmax, 1.);
}


void divide_by_binwidth(TH1F* h)
{
    for(int i = 1; i <= h->GetNbinsX(); i++){
        double bincontent = h->GetBinContent(i);
        double binwidth   = h->GetBinWidth(i);
        h->SetBinContent(i, bincontent/binwidth);
    }
    if(h->GetYaxis()->GetTitle() == "Events") h->GetYaxis()->SetTitle("Events / GeV");
}


std::vector< double > computeEfficiencyForROC(TH1F* hist)
{
    int nbins = hist->GetXaxis()->GetNbins();
    // first check that underflow and overflow are empty
    if(hist->GetBinContent(0) != 0) std::cout << "underflow not empty! " << hist->GetBinContent(0) << std::endl;
    if(hist->GetBinContent(nbins+1) != 0) std::cout << "overflow not empty! " << hist->GetBinContent(nbins+1) << std::endl;
    std::vector< double > effs;
    double passed = 0;
    double total = hist->Integral();
    for(int i = 0; i <= nbins; i++){
        passed += hist->GetBinContent(i);
        effs.push_back(1-passed/total);
    }
    return effs;
}


double computeAUC(TGraph* roc)
{
    double area = 0.;
    double x1, x2, y1, y2;
    for(int i = 0; i < roc->GetN() - 1; i++){
        roc->GetPoint(i, x1, y1);
        roc->GetPoint(i+1, x2, y2);
        area += (x2 - x1)*(y1 + y2)/2;
    }
    return  fabs(round(area*10000)/100);
}

void computeCuttingPoint(std::vector<double> eff_signal, std::vector<double> eff_bkg, TH1F* hist_signal, TH1F* hist_bkg, double required_signal_eff)
{
    double cp = 0, cp_eff_signal = 0, cp_eff_bkg = 0, cp_eff_signal_unc = 0, cp_eff_bkg_unc = 0;
    for(int j = eff_signal.size() -1;  j >= 0; j--){
        if(eff_signal[j] > required_signal_eff){
            cp = hist_signal->GetXaxis()->GetBinLowEdge(j+1);
            cp_eff_signal = eff_signal[j];
            cp_eff_bkg = eff_bkg[j];
            for(int junc = j + 1; junc <= hist_signal->GetNbinsX(); junc++){
                cp_eff_signal_unc += hist_signal->GetBinContent(junc);
                cp_eff_bkg_unc    += hist_bkg->GetBinContent(junc);
            }
            break;
        }
    }
    std::cout << " \\item Sig " << cp_eff_signal << "+-" << sqrt(cp_eff_signal_unc)/hist_signal->Integral() << " (" << cp_eff_signal_unc << " events)\\\\" << std::endl;
    std::cout << "Bkg " << cp_eff_bkg << "+-" << sqrt(cp_eff_bkg_unc)/hist_bkg->Integral() << " (" << cp_eff_bkg_unc << " events)\\\\" << std::endl;
    std::cout << "PFN output > " << cp << std::endl;
}


// 2D histograms
TString get_2D_draw_options(TH2F* h)
{
    int nbinsx = h->GetNbinsX();
    int nbinsy = h->GetNbinsY();
    if(nbinsx > 30 or nbinsy > 30) return "colz";
    else return "colz text";
}
