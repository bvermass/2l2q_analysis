////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, piece of code I made that takes the amount of events that fall in every signal region and formats it into a table that can be read by latex///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::print_table()
{
    TString pwd = "/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_8_0_30/src/samesign_Analysis/histograms/hists_full_analyzer_";
    TFile *input1eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-1_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input1muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-1_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input2eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-2_V-0.1054524236_e_onshell_pre2017_NLO.root", "open");
    TFile *input2muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-2_V-0.1054524236_mu_onshell_pre2017_NLO.root", "open");
    TFile *input3eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-3_V-0.03823254899_e_onshell_pre2017_NLO.root", "open");
    TFile *input3muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-3_V-0.03823254899_mu_onshell_pre2017_NLO.root", "open");
    TFile *input5eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-5_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input5muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-5_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input10eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-10_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input10muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-10_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input20eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-20_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input20muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-20_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input30eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-30_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input30muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-30_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input40eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-40_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input40muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-40_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input50eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-50_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input50muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-50_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input60eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-60_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input60muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-60_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input80eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-80_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input80muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-80_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input100eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-100_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input100muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-100_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input120eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-120_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input120muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-120_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input200eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-200_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input400eprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-400_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input400muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-400_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input800muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-800_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input1000muprompt = new TFile(pwd + "prompt/HeavyNeutrino_lljj_M-1000_V-0.01_mu_onshell_pre2017_NLO.root", "open");
    TFile *input1edisplaced = new TFile(pwd + "displaced/HeavyNeutrino_lljj_M-1_V-0.59587618054_e_onshell_pre2017_NLO.root", "open");
    TFile *input1mudisplaced = new TFile(pwd + "displaced/HeavyNeutrino_lljj_M-1_V-0.59587618054_mu_onshell_pre2017_NLO.root", "open");
    TFile *input2edisplaced = new TFile(pwd + "displaced/HeavyNeutrino_lljj_M-2_V-0.1054524236_e_onshell_pre2017_NLO.root", "open");
    TFile *input2mudisplaced = new TFile(pwd + "displaced/HeavyNeutrino_lljj_M-2_V-0.1054524236_mu_onshell_pre2017_NLO.root", "open");
    TFile *input3edisplaced = new TFile(pwd + "displaced/HeavyNeutrino_lljj_M-3_V-0.03823254899_e_onshell_pre2017_NLO.root", "open");
    TFile *input3mudisplaced = new TFile(pwd + "displaced/HeavyNeutrino_lljj_M-3_V-0.03823254899_mu_onshell_pre2017_NLO.root", "open");
    TFile *input5edisplaced = new TFile(pwd + "displaced/HeavyNeutrino_lljj_M-5_V-0.01_e_onshell_pre2017_NLO.root", "open");
    TFile *input5mudisplaced = new TFile(pwd + "displaced/HeavyNeutrino_lljj_M-5_V-0.01_mu_onshell_pre2017_NLO.root", "open");

    std::map<TString, TH1*> hists;
    hists["1eprompt"] = (TH1F*) input1eprompt->Get("ee_sigreg_fraction");
    hists["1muprompt"] = (TH1F*) input1muprompt->Get("mumu_sigreg_fraction");
    hists["2eprompt"] = (TH1F*) input2eprompt->Get("ee_sigreg_fraction");
    hists["2muprompt"] = (TH1F*) input2muprompt->Get("mumu_sigreg_fraction");
    hists["3eprompt"] = (TH1F*) input3eprompt->Get("ee_sigreg_fraction");
    hists["3muprompt"] = (TH1F*) input3muprompt->Get("mumu_sigreg_fraction");
    hists["5eprompt"] = (TH1F*) input5eprompt->Get("ee_sigreg_fraction");
    hists["5muprompt"] = (TH1F*) input5muprompt->Get("mumu_sigreg_fraction");
    hists["10eprompt"] = (TH1F*) input10eprompt->Get("ee_sigreg_fraction");
    hists["10muprompt"] = (TH1F*) input10muprompt->Get("mumu_sigreg_fraction");
    hists["20eprompt"] = (TH1F*) input20eprompt->Get("ee_sigreg_fraction");
    hists["20muprompt"] = (TH1F*) input20muprompt->Get("mumu_sigreg_fraction");
    hists["30eprompt"] = (TH1F*) input30eprompt->Get("ee_sigreg_fraction");
    hists["30muprompt"] = (TH1F*) input30muprompt->Get("mumu_sigreg_fraction");
    hists["40eprompt"] = (TH1F*) input40eprompt->Get("ee_sigreg_fraction");
    hists["40muprompt"] = (TH1F*) input40muprompt->Get("mumu_sigreg_fraction");
    hists["50eprompt"] = (TH1F*) input50eprompt->Get("ee_sigreg_fraction");
    hists["50muprompt"] = (TH1F*) input50muprompt->Get("mumu_sigreg_fraction");
    hists["60eprompt"] = (TH1F*) input60eprompt->Get("ee_sigreg_fraction");
    hists["60muprompt"] = (TH1F*) input60muprompt->Get("mumu_sigreg_fraction");
    hists["80eprompt"] = (TH1F*) input80eprompt->Get("ee_sigreg_fraction");
    hists["80muprompt"] = (TH1F*) input80muprompt->Get("mumu_sigreg_fraction");
    hists["100eprompt"] = (TH1F*) input100eprompt->Get("ee_sigreg_fraction");
    hists["100muprompt"] = (TH1F*) input100muprompt->Get("mumu_sigreg_fraction");
    hists["120eprompt"] = (TH1F*) input120eprompt->Get("ee_sigreg_fraction");
    hists["120muprompt"] = (TH1F*) input120muprompt->Get("mumu_sigreg_fraction");
    hists["200eprompt"] = (TH1F*) input200eprompt->Get("ee_sigreg_fraction");
    hists["400eprompt"] = (TH1F*) input400eprompt->Get("ee_sigreg_fraction");
    hists["400muprompt"] = (TH1F*) input400muprompt->Get("mumu_sigreg_fraction");
    hists["800muprompt"] = (TH1F*) input800muprompt->Get("mumu_sigreg_fraction");
    hists["1000muprompt"] = (TH1F*) input1000muprompt->Get("mumu_sigreg_fraction");
    hists["1edisplaced"] = (TH1F*) input1edisplaced->Get("ee_sigreg_fraction");
    hists["1mudisplaced"] = (TH1F*) input1mudisplaced->Get("mumu_sigreg_fraction");
    hists["2edisplaced"] = (TH1F*) input2edisplaced->Get("ee_sigreg_fraction");
    hists["2mudisplaced"] = (TH1F*) input2mudisplaced->Get("mumu_sigreg_fraction");
    hists["3edisplaced"] = (TH1F*) input3edisplaced->Get("ee_sigreg_fraction");
    hists["3mudisplaced"] = (TH1F*) input3mudisplaced->Get("mumu_sigreg_fraction");
    hists["5edisplaced"] = (TH1F*) input5edisplaced->Get("ee_sigreg_fraction");
    hists["5mudisplaced"] = (TH1F*) input5mudisplaced->Get("mumu_sigreg_fraction");

    cout << "This text can be copied to Latex in its entirety." << endl;
    cout << "First two mumu tables are printed, then two ee tables for different HNL masses." << endl;
    
    cout << "\\begin{frame} " << endl;
    cout << "\\frametitle{$\\mu \\mu$qq channel}" << endl;
    cout << "\\begin{center}" << endl;
    cout << "\\scalebox{0.85}{" << endl;
    cout << "\\begin{tabular}{|c|c|c|c|c|c|c|c|c|}" << endl;
    cout << "\\multicolumn{3}{|c|}{$M_N$ [GeV]} & 2(d) & 3(d) & 5(d) & 10(p) & 20(p) & 30(p) \\\\" << endl;
    cout << "\\hline" << endl;
    cout << "& 1iso $\\mu$ & 0jet & " << round(hists["2mudisplaced"]->GetBinContent(1)) << " & " << round(hists["3mudisplaced"]->GetBinContent(1)) << " & " << round(hists["5mudisplaced"]->GetBinContent(1)) << " & " << round(hists["10muprompt"]->GetBinContent(1)) << " & " << round(hists["20muprompt"]->GetBinContent(1)) << " & " << round(hists["30muprompt"]->GetBinContent(1)) << " \\\\ " << endl;
    cout << "& 1iso $\\mu$ & 1jet & " << round(hists["2mudisplaced"]->GetBinContent(2)) << " & " << round(hists["3mudisplaced"]->GetBinContent(2)) << " & " << round(hists["5mudisplaced"]->GetBinContent(2)) << " & " << round(hists["10muprompt"]->GetBinContent(2)) << " & " << round(hists["20muprompt"]->GetBinContent(2)) << " & " << round(hists["30muprompt"]->GetBinContent(2)) << " \\\\ " << endl;
    cout << "& 1iso $\\mu$ & $\\geq$2jet & " << round(hists["2mudisplaced"]->GetBinContent(3)) << " & " << round(hists["3mudisplaced"]->GetBinContent(3)) << " & " << round(hists["5mudisplaced"]->GetBinContent(3)) << " & " << round(hists["10muprompt"]->GetBinContent(3)) << " & " << round(hists["20muprompt"]->GetBinContent(3)) << " & " << round(hists["30muprompt"]->GetBinContent(3)) << " \\\\ " << endl;
    cout << "& 1non-iso $\\mu$ & 0jet & " << round(hists["2mudisplaced"]->GetBinContent(4)) << " & " << round(hists["3mudisplaced"]->GetBinContent(4)) << " & " << round(hists["5mudisplaced"]->GetBinContent(4)) << " & " << round(hists["10muprompt"]->GetBinContent(4)) << " & " << round(hists["20muprompt"]->GetBinContent(4)) << " & " << round(hists["30muprompt"]->GetBinContent(4)) << " \\\\ " << endl;
    cout << "1iso $\\mu$ & 1non-iso $\\mu$ & 1jet & " << round(hists["2mudisplaced"]->GetBinContent(5)) << " & " << round(hists["3mudisplaced"]->GetBinContent(5)) << " & " << round(hists["5mudisplaced"]->GetBinContent(5)) << " & " << round(hists["10muprompt"]->GetBinContent(5)) << " & " << round(hists["20muprompt"]->GetBinContent(5)) << " & " << round(hists["30muprompt"]->GetBinContent(5)) << " \\\\ " << endl;
    cout << "& 1non-iso $\\mu$ & $\\geq$2jet & " << round(hists["2mudisplaced"]->GetBinContent(6)) << " & " << round(hists["3mudisplaced"]->GetBinContent(6)) << " & " << round(hists["5mudisplaced"]->GetBinContent(6)) << " & " << round(hists["10muprompt"]->GetBinContent(6)) << " & " << round(hists["20muprompt"]->GetBinContent(6)) << " & " << round(hists["30muprompt"]->GetBinContent(6)) << " \\\\ " << endl;
    cout << "& 1displ $\\mu$ & 0jet & " << round(hists["2mudisplaced"]->GetBinContent(7)) << " & " << round(hists["3mudisplaced"]->GetBinContent(7)) << " & " << round(hists["5mudisplaced"]->GetBinContent(7)) << " & " << round(hists["10muprompt"]->GetBinContent(7)) << " & " << round(hists["20muprompt"]->GetBinContent(7)) << " & " << round(hists["30muprompt"]->GetBinContent(7)) << " \\\\ " << endl;
    cout << "& 1displ $\\mu$ & 1jet & " << round(hists["2mudisplaced"]->GetBinContent(8)) << " & " << round(hists["3mudisplaced"]->GetBinContent(8)) << " & " << round(hists["5mudisplaced"]->GetBinContent(8)) << " & " << round(hists["10muprompt"]->GetBinContent(8)) << " & " << round(hists["20muprompt"]->GetBinContent(8)) << " & " << round(hists["30muprompt"]->GetBinContent(8)) << " \\\\ " << endl;
    cout << "& 1displ $\\mu$ & $\\geq$2jet & " << round(hists["2mudisplaced"]->GetBinContent(9)) << " & " << round(hists["3mudisplaced"]->GetBinContent(9)) << " & " << round(hists["5mudisplaced"]->GetBinContent(9)) << " & " << round(hists["10muprompt"]->GetBinContent(9)) << " & " << round(hists["20muprompt"]->GetBinContent(9)) << " & " << round(hists["30muprompt"]->GetBinContent(9)) << " \\\\ " << endl;
    cout << "& 0 $\\mu$ & 0jet &" << round(hists["2mudisplaced"]->GetBinContent(10)) << " & " << round(hists["3mudisplaced"]->GetBinContent(10)) << " & " << round(hists["5mudisplaced"]->GetBinContent(10)) << " & " << round(hists["10muprompt"]->GetBinContent(10)) << " & " << round(hists["20muprompt"]->GetBinContent(10)) << " & " << round(hists["30muprompt"]->GetBinContent(10)) << " \\\\ " << endl;
    cout << "& 0 $\\mu$ & 1jet &" << round(hists["2mudisplaced"]->GetBinContent(11)) << " & " << round(hists["3mudisplaced"]->GetBinContent(11)) << " & " << round(hists["5mudisplaced"]->GetBinContent(11)) << " & " << round(hists["10muprompt"]->GetBinContent(11)) << " & " << round(hists["20muprompt"]->GetBinContent(11)) << " & " << round(hists["30muprompt"]->GetBinContent(11)) << " \\\\ " << endl;
    cout << "& 0 $\\mu$ & $\\geq$2jet &" << round(hists["2mudisplaced"]->GetBinContent(12)) << " & " << round(hists["3mudisplaced"]->GetBinContent(12)) << " & " << round(hists["5mudisplaced"]->GetBinContent(12)) << " & " << round(hists["10muprompt"]->GetBinContent(12)) << " & " << round(hists["20muprompt"]->GetBinContent(12)) << " & " << round(hists["30muprompt"]->GetBinContent(12)) << " \\\\ " << endl;
    cout << "\\hline" << endl;
    cout << "\\end{tabular}" << endl;
    cout << "}" << endl;
    cout << "\\end{center}" << endl;
    cout << "\\end{frame}" << endl << endl;

    cout << "\\begin{frame} " << endl;
    cout << "\\frametitle{$\\mu \\mu$qq channel}" << endl;
    cout << "\\begin{center}" << endl;
    cout << "\\scalebox{0.85}{" << endl;
    cout << "\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|}" << endl;
    cout << "\\multicolumn{3}{|c|}{$M_N$ [GeV]} & 40 & 50 & 60 & 80 & 100 & 120 & 400 \\\\" << endl;
    cout << "\\hline" << endl;
    cout << "& 1iso $\\mu$ & 0jet & " << round(hists["40muprompt"]->GetBinContent(1)) << " & " << round(hists["50muprompt"]->GetBinContent(1)) << " & " << round(hists["60muprompt"]->GetBinContent(1)) << " & " << round(hists["80muprompt"]->GetBinContent(1)) << " & " << round(hists["100muprompt"]->GetBinContent(1)) << " & " << round(hists["120muprompt"]->GetBinContent(1)) << " & " << round(hists["400muprompt"]->GetBinContent(1)) << " \\\\ " << endl;
    cout << "& 1iso $\\mu$ & 1jet & " << round(hists["40muprompt"]->GetBinContent(2)) << " & " << round(hists["50muprompt"]->GetBinContent(2)) << " & " << round(hists["60muprompt"]->GetBinContent(2)) << " & " << round(hists["80muprompt"]->GetBinContent(2)) << " & " << round(hists["100muprompt"]->GetBinContent(2)) << " & " << round(hists["120muprompt"]->GetBinContent(2)) << " & " << round(hists["400muprompt"]->GetBinContent(2)) << " \\\\ " << endl;
    cout << "& 1iso $\\mu$ & $\\geq$2jet & " << round(hists["40muprompt"]->GetBinContent(3)) << " & " << round(hists["50muprompt"]->GetBinContent(3)) << " & " << round(hists["60muprompt"]->GetBinContent(3)) << " & " << round(hists["80muprompt"]->GetBinContent(3)) << " & " << round(hists["100muprompt"]->GetBinContent(3)) << " & " << round(hists["120muprompt"]->GetBinContent(3)) << " & " << round(hists["400muprompt"]->GetBinContent(3)) << " \\\\ " << endl;
    cout << "& 1non-iso $\\mu$ & 0jet & " << round(hists["40muprompt"]->GetBinContent(4)) << " & " << round(hists["50muprompt"]->GetBinContent(4)) << " & " << round(hists["60muprompt"]->GetBinContent(4)) << " & " << round(hists["80muprompt"]->GetBinContent(4)) << " & " << round(hists["100muprompt"]->GetBinContent(4)) << " & " << round(hists["120muprompt"]->GetBinContent(4)) << " & " << round(hists["400muprompt"]->GetBinContent(4)) << " \\\\ " << endl;
    cout << "1iso $\\mu$ & 1non-iso $\\mu$ & 1jet & " << round(hists["40muprompt"]->GetBinContent(5)) << " & " << round(hists["50muprompt"]->GetBinContent(5)) << " & " << round(hists["60muprompt"]->GetBinContent(5)) << " & " << round(hists["80muprompt"]->GetBinContent(5)) << " & " << round(hists["100muprompt"]->GetBinContent(5)) << " & " << round(hists["120muprompt"]->GetBinContent(5)) << " & " << round(hists["400muprompt"]->GetBinContent(5)) << " \\\\ " << endl;
    cout << "& 1non-iso $\\mu$ & $\\geq$2jet & " << round(hists["40muprompt"]->GetBinContent(6)) << " & " << round(hists["50muprompt"]->GetBinContent(6)) << " & " << round(hists["60muprompt"]->GetBinContent(6)) << " & " << round(hists["80muprompt"]->GetBinContent(6)) << " & " << round(hists["100muprompt"]->GetBinContent(6)) << " & " << round(hists["120muprompt"]->GetBinContent(6)) << " & " << round(hists["400muprompt"]->GetBinContent(6)) << " \\\\ " << endl;
    cout << "& 1displ $\\mu$ & 0jet & " << round(hists["40muprompt"]->GetBinContent(7)) << " & " << round(hists["50muprompt"]->GetBinContent(7)) << " & " << round(hists["60muprompt"]->GetBinContent(7)) << " & " << round(hists["80muprompt"]->GetBinContent(7)) << " & " << round(hists["100muprompt"]->GetBinContent(7)) << " & " << round(hists["120muprompt"]->GetBinContent(7)) << " & " << round(hists["400muprompt"]->GetBinContent(7)) << " \\\\ " << endl;
    cout << "& 1displ $\\mu$ & 1jet & " << round(hists["40muprompt"]->GetBinContent(8)) << " & " << round(hists["50muprompt"]->GetBinContent(8)) << " & " << round(hists["60muprompt"]->GetBinContent(8)) << " & " << round(hists["80muprompt"]->GetBinContent(8)) << " & " << round(hists["100muprompt"]->GetBinContent(8)) << " & " << round(hists["120muprompt"]->GetBinContent(8)) << " & " << round(hists["400muprompt"]->GetBinContent(8)) << " \\\\ " << endl;
    cout << "& 1displ $\\mu$ & $\\geq$2jet & " << round(hists["40muprompt"]->GetBinContent(9)) << " & " << round(hists["50muprompt"]->GetBinContent(9)) << " & " << round(hists["60muprompt"]->GetBinContent(9)) << " & " << round(hists["80muprompt"]->GetBinContent(9)) << " & " << round(hists["100muprompt"]->GetBinContent(9)) << " & " << round(hists["120muprompt"]->GetBinContent(9)) << " & " << round(hists["400muprompt"]->GetBinContent(9)) << " \\\\ " << endl;
    cout << "& 0 $\\mu$ & 0jet & " << round(hists["40muprompt"]->GetBinContent(10)) << " & " << round(hists["50muprompt"]->GetBinContent(10)) << " & " << round(hists["60muprompt"]->GetBinContent(10)) << " & " << round(hists["80muprompt"]->GetBinContent(10)) << " & " << round(hists["100muprompt"]->GetBinContent(10)) << " & " << round(hists["120muprompt"]->GetBinContent(10)) << " & " << round(hists["400muprompt"]->GetBinContent(10)) << " \\\\ " << endl;
    cout << "& 0 $\\mu$ & 1jet & " << round(hists["40muprompt"]->GetBinContent(11)) << " & " << round(hists["50muprompt"]->GetBinContent(11)) << " & " << round(hists["60muprompt"]->GetBinContent(11)) << " & " << round(hists["80muprompt"]->GetBinContent(11)) << " & " << round(hists["100muprompt"]->GetBinContent(11)) << " & " << round(hists["120muprompt"]->GetBinContent(11)) << " & " << round(hists["400muprompt"]->GetBinContent(11)) << " \\\\ " << endl;
    cout << "& 0 $\\mu$ & $\\geq$2jet & " << round(hists["40muprompt"]->GetBinContent(12)) << " & " << round(hists["50muprompt"]->GetBinContent(12)) << " & " << round(hists["60muprompt"]->GetBinContent(12)) << " & " << round(hists["80muprompt"]->GetBinContent(12)) << " & " << round(hists["100muprompt"]->GetBinContent(12)) << " & " << round(hists["120muprompt"]->GetBinContent(12)) << " & " << round(hists["400muprompt"]->GetBinContent(12)) << " \\\\ " << endl;
    cout << "\\hline" << endl;
    cout << "\\end{tabular}" << endl;
    cout << "}" << endl;
    cout << "\\end{center}" << endl;
    cout << "\\end{frame}" << endl << endl;

    cout << "\\begin{frame} " << endl;
    cout << "\\frametitle{eeqq channel}" << endl;
    cout << "\\begin{center}" << endl;
    cout << "\\scalebox{0.85}{" << endl;
    cout << "\\begin{tabular}{|c|c|c|c|c|c|c|c|c|}" << endl;
    cout << "\\multicolumn{3}{|c|}{$M_N$ [GeV]} & 2(d) & 3(d) & 5(d) & 10(p) & 20(p) & 30(p) \\\\" << endl;
    cout << "\\hline" << endl;
    cout << "& 1iso e & 0jet & " << round(hists["2edisplaced"]->GetBinContent(1)) << " & " << round(hists["3edisplaced"]->GetBinContent(1)) << " & " << round(hists["5edisplaced"]->GetBinContent(1)) << " & " << round(hists["10eprompt"]->GetBinContent(1)) << " & " << round(hists["20eprompt"]->GetBinContent(1)) << " & " << round(hists["30eprompt"]->GetBinContent(1)) << " \\\\ " << endl;
    cout << "& 1iso e & 1jet & " << round(hists["2edisplaced"]->GetBinContent(2)) << " & " << round(hists["3edisplaced"]->GetBinContent(2)) << " & " << round(hists["5edisplaced"]->GetBinContent(2)) << " & " << round(hists["10eprompt"]->GetBinContent(2)) << " & " << round(hists["20eprompt"]->GetBinContent(2)) << " & " << round(hists["30eprompt"]->GetBinContent(2)) << " \\\\ " << endl;
    cout << "& 1iso e & $\\geq$2jet & " << round(hists["2edisplaced"]->GetBinContent(3)) << " & " << round(hists["3edisplaced"]->GetBinContent(3)) << " & " << round(hists["5edisplaced"]->GetBinContent(3)) << " & " << round(hists["10eprompt"]->GetBinContent(3)) << " & " << round(hists["20eprompt"]->GetBinContent(3)) << " & " << round(hists["30eprompt"]->GetBinContent(3)) << " \\\\ " << endl;
    cout << "& 1non-iso e & 0jet & " << round(hists["2edisplaced"]->GetBinContent(4)) << " & " << round(hists["3edisplaced"]->GetBinContent(4)) << " & " << round(hists["5edisplaced"]->GetBinContent(4)) << " & " << round(hists["10eprompt"]->GetBinContent(4)) << " & " << round(hists["20eprompt"]->GetBinContent(4)) << " & " << round(hists["30eprompt"]->GetBinContent(4)) << " \\\\ " << endl;
    cout << "1iso e & 1non-iso e & 1jet & " << round(hists["2edisplaced"]->GetBinContent(5)) << " & " << round(hists["3edisplaced"]->GetBinContent(5)) << " & " << round(hists["5edisplaced"]->GetBinContent(5)) << " & " << round(hists["10eprompt"]->GetBinContent(5)) << " & " << round(hists["20eprompt"]->GetBinContent(5)) << " & " << round(hists["30eprompt"]->GetBinContent(5)) << " \\\\ " << endl;
    cout << "& 1non-iso e & $\\geq$2jet & " << round(hists["2edisplaced"]->GetBinContent(6)) << " & " << round(hists["3edisplaced"]->GetBinContent(6)) << " & " << round(hists["5edisplaced"]->GetBinContent(6)) << " & " << round(hists["10eprompt"]->GetBinContent(6)) << " & " << round(hists["20eprompt"]->GetBinContent(6)) << " & " << round(hists["30eprompt"]->GetBinContent(6)) << " \\\\ " << endl;
    cout << "& 1displ e & 0jet & " << round(hists["2edisplaced"]->GetBinContent(7)) << " & " << round(hists["3edisplaced"]->GetBinContent(7)) << " & " << round(hists["5edisplaced"]->GetBinContent(7)) << " & " << round(hists["10eprompt"]->GetBinContent(7)) << " & " << round(hists["20eprompt"]->GetBinContent(7)) << " & " << round(hists["30eprompt"]->GetBinContent(7)) << " \\\\ " << endl;
    cout << "& 1displ e & 1jet & " << round(hists["2edisplaced"]->GetBinContent(8)) << " & " << round(hists["3edisplaced"]->GetBinContent(8)) << " & " << round(hists["5edisplaced"]->GetBinContent(8)) << " & " << round(hists["10eprompt"]->GetBinContent(8)) << " & " << round(hists["20eprompt"]->GetBinContent(8)) << " & " << round(hists["30eprompt"]->GetBinContent(8)) << " \\\\ " << endl;
    cout << "& 1displ e & $\\geq$2jet & " << round(hists["2edisplaced"]->GetBinContent(9)) << " & " << round(hists["3edisplaced"]->GetBinContent(9)) << " & " << round(hists["5edisplaced"]->GetBinContent(9)) << " & " << round(hists["10eprompt"]->GetBinContent(9)) << " & " << round(hists["20eprompt"]->GetBinContent(9)) << " & " << round(hists["30eprompt"]->GetBinContent(9)) << " \\\\ " << endl;
    cout << "& 0 e & 0jet &" << round(hists["2edisplaced"]->GetBinContent(10)) << " & " << round(hists["3edisplaced"]->GetBinContent(10)) << " & " << round(hists["5edisplaced"]->GetBinContent(10)) << " & " << round(hists["10eprompt"]->GetBinContent(10)) << " & " << round(hists["20eprompt"]->GetBinContent(10)) << " & " << round(hists["30eprompt"]->GetBinContent(10)) << " \\\\ " << endl;
    cout << "& 0 e & 1jet &" << round(hists["2edisplaced"]->GetBinContent(11)) << " & " << round(hists["3edisplaced"]->GetBinContent(11)) << " & " << round(hists["5edisplaced"]->GetBinContent(11)) << " & " << round(hists["10eprompt"]->GetBinContent(11)) << " & " << round(hists["20eprompt"]->GetBinContent(11)) << " & " << round(hists["30eprompt"]->GetBinContent(11)) << " \\\\ " << endl;
    cout << "& 0 e & $\\geq$2jet &" << round(hists["2edisplaced"]->GetBinContent(12)) << " & " << round(hists["3edisplaced"]->GetBinContent(12)) << " & " << round(hists["5edisplaced"]->GetBinContent(12)) << " & " << round(hists["10eprompt"]->GetBinContent(12)) << " & " << round(hists["20eprompt"]->GetBinContent(12)) << " & " << round(hists["30eprompt"]->GetBinContent(12)) << " \\\\ " << endl;
    cout << "\\hline" << endl;
    cout << "\\end{tabular}" << endl;
    cout << "}" << endl;
    cout << "\\end{center}" << endl;
    cout << "\\end{frame}" << endl << endl;

    cout << "\\begin{frame} " << endl;
    cout << "\\frametitle{eeqq channel}" << endl;
    cout << "\\begin{center}" << endl;
    cout << "\\scalebox{0.85}{" << endl;
    cout << "\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|}" << endl;
    cout << "\\multicolumn{3}{|c|}{$M_N$ [GeV]} & 40 & 50 & 60 & 80 & 100 & 120 & 200 \\\\" << endl;
    cout << "\\hline" << endl;
    cout << "& 1iso e & 0jet & " << round(hists["40eprompt"]->GetBinContent(1)) << " & " << round(hists["50eprompt"]->GetBinContent(1)) << " & " << round(hists["60eprompt"]->GetBinContent(1)) << " & " << round(hists["80eprompt"]->GetBinContent(1)) << " & " << round(hists["100eprompt"]->GetBinContent(1)) << " & " << round(hists["120eprompt"]->GetBinContent(1)) << " & " << round(hists["200eprompt"]->GetBinContent(1)) << " \\\\ " << endl;
    cout << "& 1iso e & 1jet & " << round(hists["40eprompt"]->GetBinContent(2)) << " & " << round(hists["50eprompt"]->GetBinContent(2)) << " & " << round(hists["60eprompt"]->GetBinContent(2)) << " & " << round(hists["80eprompt"]->GetBinContent(2)) << " & " << round(hists["100eprompt"]->GetBinContent(2)) << " & " << round(hists["120eprompt"]->GetBinContent(2)) << " & " << round(hists["200eprompt"]->GetBinContent(2)) << " \\\\ " << endl;
    cout << "& 1iso e & $\\geq$2jet & " << round(hists["40eprompt"]->GetBinContent(3)) << " & " << round(hists["50eprompt"]->GetBinContent(3)) << " & " << round(hists["60eprompt"]->GetBinContent(3)) << " & " << round(hists["80eprompt"]->GetBinContent(3)) << " & " << round(hists["100eprompt"]->GetBinContent(3)) << " & " << round(hists["120eprompt"]->GetBinContent(3)) << " & " << round(hists["200eprompt"]->GetBinContent(3)) << " \\\\ " << endl;
    cout << "& 1non-iso e & 0jet & " << round(hists["40eprompt"]->GetBinContent(4)) << " & " << round(hists["50eprompt"]->GetBinContent(4)) << " & " << round(hists["60eprompt"]->GetBinContent(4)) << " & " << round(hists["80eprompt"]->GetBinContent(4)) << " & " << round(hists["100eprompt"]->GetBinContent(4)) << " & " << round(hists["120eprompt"]->GetBinContent(4)) << " & " << round(hists["200eprompt"]->GetBinContent(4)) << " \\\\ " << endl;
    cout << "1iso e & 1non-iso e & 1jet & " << round(hists["40eprompt"]->GetBinContent(5)) << " & " << round(hists["50eprompt"]->GetBinContent(5)) << " & " << round(hists["60eprompt"]->GetBinContent(5)) << " & " << round(hists["80eprompt"]->GetBinContent(5)) << " & " << round(hists["100eprompt"]->GetBinContent(5)) << " & " << round(hists["120eprompt"]->GetBinContent(5)) << " & " << round(hists["200eprompt"]->GetBinContent(5)) << " \\\\ " << endl;
    cout << "& 1non-iso e & $\\geq$2jet & " << round(hists["40eprompt"]->GetBinContent(6)) << " & " << round(hists["50eprompt"]->GetBinContent(6)) << " & " << round(hists["60eprompt"]->GetBinContent(6)) << " & " << round(hists["80eprompt"]->GetBinContent(6)) << " & " << round(hists["100eprompt"]->GetBinContent(6)) << " & " << round(hists["120eprompt"]->GetBinContent(6)) << " & " << round(hists["200eprompt"]->GetBinContent(6)) << " \\\\ " << endl;
    cout << "& 1displ e & 0jet & " << round(hists["40eprompt"]->GetBinContent(7)) << " & " << round(hists["50eprompt"]->GetBinContent(7)) << " & " << round(hists["60eprompt"]->GetBinContent(7)) << " & " << round(hists["80eprompt"]->GetBinContent(7)) << " & " << round(hists["100eprompt"]->GetBinContent(7)) << " & " << round(hists["120eprompt"]->GetBinContent(7)) << " & " << round(hists["200eprompt"]->GetBinContent(7)) << " \\\\ " << endl;
    cout << "& 1displ e & 1jet & " << round(hists["40eprompt"]->GetBinContent(8)) << " & " << round(hists["50eprompt"]->GetBinContent(8)) << " & " << round(hists["60eprompt"]->GetBinContent(8)) << " & " << round(hists["80eprompt"]->GetBinContent(8)) << " & " << round(hists["100eprompt"]->GetBinContent(8)) << " & " << round(hists["120eprompt"]->GetBinContent(8)) << " & " << round(hists["200eprompt"]->GetBinContent(8)) << " \\\\ " << endl;
    cout << "& 1displ e & $\\geq$2jet & " << round(hists["40eprompt"]->GetBinContent(9)) << " & " << round(hists["50eprompt"]->GetBinContent(9)) << " & " << round(hists["60eprompt"]->GetBinContent(9)) << " & " << round(hists["80eprompt"]->GetBinContent(9)) << " & " << round(hists["100eprompt"]->GetBinContent(9)) << " & " << round(hists["120eprompt"]->GetBinContent(9)) << " & " << round(hists["200eprompt"]->GetBinContent(9)) << " \\\\ " << endl;
    cout << "& 0 e & 0jet & " << round(hists["40eprompt"]->GetBinContent(10)) << " & " << round(hists["50eprompt"]->GetBinContent(10)) << " & " << round(hists["60eprompt"]->GetBinContent(10)) << " & " << round(hists["80eprompt"]->GetBinContent(10)) << " & " << round(hists["100eprompt"]->GetBinContent(10)) << " & " << round(hists["120eprompt"]->GetBinContent(10)) << " & " << round(hists["200eprompt"]->GetBinContent(10)) << " \\\\ " << endl;
    cout << "& 0 e & 1jet & " << round(hists["40eprompt"]->GetBinContent(11)) << " & " << round(hists["50eprompt"]->GetBinContent(11)) << " & " << round(hists["60eprompt"]->GetBinContent(11)) << " & " << round(hists["80eprompt"]->GetBinContent(11)) << " & " << round(hists["100eprompt"]->GetBinContent(11)) << " & " << round(hists["120eprompt"]->GetBinContent(11)) << " & " << round(hists["200eprompt"]->GetBinContent(11)) << " \\\\ " << endl;
    cout << "& 0 e & $\\geq$2jet & " << round(hists["40eprompt"]->GetBinContent(12)) << " & " << round(hists["50eprompt"]->GetBinContent(12)) << " & " << round(hists["60eprompt"]->GetBinContent(12)) << " & " << round(hists["80eprompt"]->GetBinContent(12)) << " & " << round(hists["100eprompt"]->GetBinContent(12)) << " & " << round(hists["120eprompt"]->GetBinContent(12)) << " & " << round(hists["200eprompt"]->GetBinContent(12)) << " \\\\ " << endl;
    cout << "\\hline" << endl;
    cout << "\\end{tabular}" << endl;
    cout << "}" << endl;
    cout << "\\end{center}" << endl;
    cout << "\\end{frame}" << endl << endl;
    
    
}
