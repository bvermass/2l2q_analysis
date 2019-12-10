#include "AnalyzeCombineOutput.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    if(argc != 3){
        std::cout << "Command should be ./test [combine_rootfile_dir] [flavor_mass_otherId]" << std::endl;
        return 1;
    }
    //Argument 1: text file containing all necessary combine rootfiles to analyze
    //Code: the textfile is supposed to have combine rootfiles for 1 mass and a range of couplings.
    //      plot will be made of signal strength as a function of coupling
    TString txtfilename = (TString)argv[1];
    TString specific_dir = (TString)argv[2];
    std::cout << "flavor and mass: " << specific_dir << std::endl;
    
    //From txtfile, read the combine output root files to be used for the plot
    std::cout << "--------------------" << std::endl << "reading from textfile:" << std::endl;
    std::string line;
    std::ifstream txtfile (txtfilename);
    std::vector<CombineOutput*> combine_outputs;
    if(txtfile.is_open()){
        while(std::getline(txtfile, line)){
            std::cout << line << std::endl;
            combine_outputs.push_back(new CombineOutput((TString)line));
        }
    }
    std::cout << "--------------------" << std::endl << "reading signal strengths" << std::endl;
    std::map<double, std::map<double, std::map<float, double>>> signal_strengths; //<M, <V2, <quantile, limit>>
    for(unsigned i = 0; i < combine_outputs.size(); i++){
        std::cout << "processing " << combine_outputs[i]->combine_filename << std::endl;
        signal_strengths[combine_outputs[i]->M][combine_outputs[i]->V2] = combine_outputs[i]->GetSignalStrengths();
    }
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
    std::cout << "--------------------" << std::endl << "Plotting Signal Strengths vs. coupling for single mass" << std::endl;
    for(auto& sr_M : signal_strengths){
        PlotSignalStrengths(sr_M.second, "SignalStrength_" + specific_dir + "M-" + std::to_string((int)sr_M.first), "|V|^{2}", "Signal Strength");
    }

    std::cout << "--------------------" << std::endl << "Getting exclusion limits and plotting final exclusion plot" << std::endl;//ONLY LOWER LIMIT, NO UPPER LIMIT YET
    std::map<double, std::map<float, double>> exclusion_limits;//<mass, <quantile, V2(where limit is 1, approached from below)>>
    for(auto& sr_M : signal_strengths){
        if(CheckGoesBelow1(sr_M.second)){
            exclusion_limits[sr_M.first][0.025] = GetLowerExclusionLimit(sr_M.second, 0.025);
            exclusion_limits[sr_M.first][0.16] = GetLowerExclusionLimit(sr_M.second, 0.16);
            exclusion_limits[sr_M.first][0.50] = GetLowerExclusionLimit(sr_M.second, 0.50);
            exclusion_limits[sr_M.first][0.84] = GetLowerExclusionLimit(sr_M.second, 0.84);
            exclusion_limits[sr_M.first][0.975] = GetLowerExclusionLimit(sr_M.second, 0.975);
        }
    }

    PlotSignalStrengths(exclusion_limits, "ExclusionLimit_" + specific_dir, "M_{HNL} [GeV]", "|V|^{2}");
}
#endif


bool CheckGoesBelow1(std::map<double, std::map<float, double>> signal_strengths){
    bool ok_2s_up = false, ok_2s_down = false, ok_1s_up = false, ok_1s_down = false, ok_central = false;
    for(auto& sr_V2 : signal_strengths){
        if(sr_V2.second[0.025] < 1) ok_2s_down = true;
        if(sr_V2.second[0.16] < 1) ok_1s_down = true;
        if(sr_V2.second[0.50] < 1) ok_central = true;
        if(sr_V2.second[0.84] < 1) ok_1s_up = true;
        if(sr_V2.second[0.975] < 1) ok_2s_up = true;
    }
    return ok_2s_down and ok_1s_down and ok_central and ok_1s_up and ok_2s_up;
}


double GetLowerExclusionLimit(std::map<double, std::map<float, double>> signal_strengths, float quantile)
{
    double x1, x2, y1, y2;//x1, x2 = V2 and y1, y2 = signal strength
    for(auto& sr_V2 : signal_strengths){
        std::cout << "V2, signal strength: " << sr_V2.first << " " << sr_V2.second[quantile] << std::endl;
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

void PlotSignalStrengths(std::map<double, std::map<float, double>> signal_strengths, TString specific_dir, TString Xaxistitle, TString Yaxistitle)
{
    // set general plot style
    setTDRStyle();
    gROOT->ForceStyle();

    TString pathname = "~/public/2l2q_analysis/combine/plots/";
    gSystem->Exec("mkdir -p " + pathname);

    TCanvas* c = new TCanvas("c","",700,700);
    c->cd();

    // Make the pad that will contain the plot
    TPad* pad  = new TPad("pad", "", 0., 0., 1., 1.);
    pad->Draw();
    pad->cd();
    pad->SetLogx(1);
    pad->SetLogy(1);

    // Get margins and make the CMS and lumi basic latex to print on top of the figure
    TString CMStext   = "#bf{CMS} #scale[0.8]{#it{Preliminary}}";
    TString lumitext  = "35.9 fb^{-1} (13 TeV)";
    float leftmargin  = pad->GetLeftMargin();
    float topmargin   = pad->GetTopMargin();
    float rightmargin = pad->GetRightMargin();
    TLatex CMSlatex  = get_latex(0.8*topmargin, 11, 42);
    TLatex lumilatex = get_latex(0.6*topmargin, 31, 42);

    std::vector<double> V2, V2_err, sr_2s_up, sr_2s_down, sr_1s_up, sr_1s_down, sr_central;
    for(auto& sr_V2 : signal_strengths){
        //if(sr_V2.second[0.50] > 5) continue;
        V2.push_back(sr_V2.first);
        sr_2s_up.push_back(sr_V2.second[0.975] - sr_V2.second[0.50]); //For 1 and 2 sigma variations, get value RELATIVE to central value to be able to use it as an error in TGraphAsymmErrors
        sr_1s_up.push_back(sr_V2.second[0.84] - sr_V2.second[0.50]);
        sr_2s_down.push_back(sr_V2.second[0.50] - sr_V2.second[0.025]);
        sr_1s_down.push_back(sr_V2.second[0.50] - sr_V2.second[0.16]);
        sr_central.push_back(sr_V2.second[0.50]);
        V2_err.push_back(0.);
    }

    TGraphAsymmErrors* sr_2s_graph = new TGraphAsymmErrors(V2.size(), &V2[0], &sr_central[0], &V2_err[0], &V2_err[0], &sr_2s_down[0], &sr_2s_up[0]);
    sr_2s_graph->SetFillColor(kOrange);
    sr_2s_graph->SetFillStyle(1001);
    sr_2s_graph->GetXaxis()->SetTitle(Xaxistitle);
    sr_2s_graph->GetYaxis()->SetTitle(Yaxistitle);

    TGraphAsymmErrors* sr_1s_graph = new TGraphAsymmErrors(V2.size(), &V2[0], &sr_central[0], &V2_err[0], &V2_err[0], &sr_1s_down[0], &sr_1s_up[0]);
    sr_1s_graph->SetFillColor(kGreen+1);
    sr_1s_graph->SetFillStyle(1001);

    TGraphAsymmErrors* sr_central_graph = new TGraphAsymmErrors(V2.size(), &V2[0], &sr_central[0], &V2_err[0], &V2_err[0], &V2_err[0], &V2_err[0]);

    sr_2s_graph->Draw("A3");
    sr_1s_graph->Draw("3 same");
    sr_central_graph->Draw("L same");
    CMSlatex.DrawLatex(leftmargin, 1-0.8*topmargin, CMStext);
    lumilatex.DrawLatex(1-rightmargin, 1-0.8*topmargin, lumitext);

    pad->Modified();
    c->Print(pathname + specific_dir + ".pdf");
    return;
}


CombineOutput::CombineOutput(TString filename)
{
    combine_filename = filename;
    M  = ((TString)filename(filename.Index("_M-") + 3, filename.Index("_V2-") - filename.Index("_M-") -3)).Atof();
    V2 = ((TString)filename(filename.Index("_V2-") + 4, filename.Index(".AsymptoticLimits") - filename.Index("_V2-") - 4)).Atof();
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
        if(quantileExpected > 0) signal_strengths[quantileExpected] = limit;
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
