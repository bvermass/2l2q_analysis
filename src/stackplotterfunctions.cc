#include <TROOT.h>
#include <TFile.h>
#include <TF1.h>
#include <TH2.h>
#include <TH1.h>
#include <THistPainter.h>
#include <TGraphAsymmErrors.h>
#include <TLatex.h>
#include <TTree.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <iostream>
#include <string>
#include <cmath>
#include <TRandom3.h>
#include <TKey.h>
#include <TSystem.h>
#include <THStack.h>

#include "../interface/plotterfunctions.h"
#include "../interface/stackplotterfunctions.h"

using namespace std;

std::map<TString, TH1*>::iterator it2;

# ifndef __CINT__
int main(int argc, char * argv[])
{
    TString pathname                = "/user/bvermass/public/2l2q_analysis/plots/stacks/";
    TString pathname_with_signal    = "/user/bvermass/public/2l2q_analysis/plots/stacks_with_signal/";

    // define canvas and legend(s)
    TCanvas *c = new TCanvas("c","",700,700);
    gStyle->SetPalette(55);
    gStyle->SetOptStat(0);
    gPad->SetTicks(1,1);

    TLegend lgendrup(.6,.6,.87,.87);
    lgendrup.SetBorderSize(0);
    lgendrup.SetFillStyle(0);
   

    // put all background files in a map that can be looped over
    std::map<TString, TFile*> files;
    for(int i = 1; i < (argc + 1)/2; i++){
        files[argv[i]] = TFile::Open(argv[i]);
        cout << argv[i] << endl;
    }
    // signal files
    TFile * HNL3GeV_e_file = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-3_V-0.00836660026534_e_onshell_pre2017_leptonFirst_NLO_displaced.root");
    TFile * HNL3GeV_mu_file = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-3_V-0.00836660026534_mu_onshell_pre2017_leptonFirst_NLO_displaced.root");
    TFile * HNL7GeV_e_file = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-7_V-0.00244948974278_e_onshell_pre2017_leptonFirst_NLO_displaced.root");
    TFile * HNL7GeV_mu_file = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-7_V-0.00244948974278_mu_onshell_pre2017_leptonFirst_NLO_displaced.root");
    TFile * HNL10GeV_e_file = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-10_V-0.00244948974278_e_onshell_pre2017_leptonFirst_NLO_displaced.root");
    TFile * HNL10GeV_mu_file = TFile::Open("/user/bvermass/public/2l2q_analysis/histograms/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-10_V-0.00244948974278_mu_onshell_pre2017_leptonFirst_NLO_displaced.root");


    // loop over histograms
    std::map<TString, TH1*> hists;
    std::map<TString, TH1*> signals;
    TIter next(files[argv[1]]->GetListOfKeys());
    TKey * key;

    while ((key = (TKey*)next())) {
        hists.clear();
        signals.clear();
    
        // get correct reference histogram
        TClass *cl = gROOT->GetClass(key->GetClassName());
        if (!cl->InheritsFrom("TH1")) continue;
        TH1F *h_ref = (TH1F*)key->ReadObj(); //h_ref is the reference histogram that knows the name etc. of the histogram
        cout << h_ref->GetName() << endl;
        TString histname = h_ref->GetName();

        // append directories such as SS/OS, e/mu or HLT to pathname
        TString SSorOS = "";
        if((histname.Index("_SS_") != -1)){ 
            SSorOS = "SS/";
        }else if(histname.Index("_OS_") != -1){
            SSorOS = "OS/";
        }
        TString eormu = "";
        if(histname.Index("_e_") != -1 || histname.Index("Ele") != -1){ 
            eormu = "e/";
        }else if(histname.Index("_mu_") != -1 || histname.Index("Mu") != -1){
            eormu = "mu/";
        }
        TString HLT = "";
        if(histname.Index("HLT_") != -1){
            HLT = "HLT/";
        }
        TString partialcuts = "";
        if(histname.Index("before") != -1){
            partialcuts = "partialcuts/";
        }
        
        gSystem->Exec("mkdir -p " + pathname + HLT + SSorOS + eormu + "lin/" + partialcuts);
        gSystem->Exec("mkdir -p " + pathname + HLT + SSorOS + eormu + "log/" + partialcuts);
        gSystem->Exec("mkdir -p " + pathname_with_signal + HLT + SSorOS + eormu + "lin/" + partialcuts);
        gSystem->Exec("mkdir -p " + pathname_with_signal + HLT + SSorOS + eormu + "log/" + partialcuts);


        // find flavor e or mu
        TString flavor;
        TString checkflavor = h_ref->GetName();                 //CHANGE THIS SECTION, MAKE h_ref->GetName() a separate variable and improve else option of flavor!
        if(checkflavor.Index("_e_") != -1) flavor = "e";
        else if(checkflavor.Index("_mu_") != -1) flavor = "mu";
        else flavor = "e";

        // get background and signal histograms
        for(int i = 1; i < (argc +1)/2; i++){
            TString name = (TString)argv[i];
            TString fullname = to_string(i) + "_" + name(name.Index("full_analyzer/") + 14, name.Index(".root") - name.Index("full_analyzer") - 14) ;
            hists[fullname] = (TH1F*) files[argv[i]]->Get(h_ref->GetName());
        }
        if(flavor == "e"){
            signals["1_3GeV"] = (TH1F*) HNL3GeV_e_file->Get(h_ref->GetName());
            signals["2_7GeV"] = (TH1F*) HNL7GeV_e_file->Get(h_ref->GetName());
            signals["3_10GeV"] = (TH1F*) HNL10GeV_e_file->Get(h_ref->GetName());
        }else if(flavor == "mu"){
            signals["1_3GeV"] = (TH1F*) HNL3GeV_mu_file->Get(h_ref->GetName());
            signals["2_7GeV"] = (TH1F*) HNL7GeV_mu_file->Get(h_ref->GetName());
            signals["3_10GeV"] = (TH1F*) HNL10GeV_mu_file->Get(h_ref->GetName());
        }

        // style of signal
        markerstyle((TH1F*)signals["1_3GeV"], "red");
        markerstyle((TH1F*)signals["2_7GeV"], "magenta");
        markerstyle((TH1F*)signals["3_10GeV"], "blue");
        mapmarkerstyle(hists);

        THStack *stack = new THStack("stack", h_ref->GetName());
        int i = (argc + 1) / 2;//to iterate over legends    CHANGE THIS TO LET A FUNCTION DECIDE ON THE LEGEND NAME BASED ON THE FILENAME
        lgendrup.Clear();
        for( it2 = hists.begin(); it2 != hists.end(); it2++){
            TH1* h = it2->second;
	        stack->Add(h);
            lgendrup.AddEntry(h, argv[i]);
            i++;
        }
        
 
        draw_stack(pathname + HLT + SSorOS + eormu + "lin/" + partialcuts + h_ref->GetName() + ".pdf", c, stack, &lgendrup, h_ref->GetXaxis()->GetTitle(), h_ref->GetYaxis()->GetTitle(), 0, -1, -1, -1, -1, "");
        draw_stack(pathname + HLT + SSorOS + eormu + "log/" + partialcuts + h_ref->GetName() + ".pdf", c, stack, &lgendrup, h_ref->GetXaxis()->GetTitle(), h_ref->GetYaxis()->GetTitle(), 1, -1, -1, 10, -1, "");
        
        lgendrup.AddEntry(signals["1_3GeV"], "HNL 3GeV, c#tau~20.90mm");
        lgendrup.AddEntry(signals["2_7GeV"], "HNL 7GeV, c#tau~3.52mm");
        lgendrup.AddEntry(signals["3_10GeV"], "HNL 10GeV, c#tau~0.59mm");
        
        draw_stack_with_signal(pathname_with_signal + HLT + SSorOS + eormu + "lin/" + partialcuts + h_ref->GetName() + ".pdf", c, stack, signals, "hist", &lgendrup, h_ref->GetXaxis()->GetTitle(), h_ref->GetYaxis()->GetTitle(), 0, -1, -1, -1, -1, "");
        draw_stack_with_signal(pathname_with_signal + HLT + SSorOS + eormu + "log/" + partialcuts + h_ref->GetName() + ".pdf", c, stack, signals, "hist", &lgendrup, h_ref->GetXaxis()->GetTitle(), h_ref->GetYaxis()->GetTitle(), 1, -1, -1, 10, -1, "");
        
 
        //if(((TString)h->GetName()).Index("eff") == -1) draw_1_hist(pathname + "/" + h->GetName() + ".pdf", c, h, "hist", &lgendrup, "", "", 0, 0, 0, flavor, mass, coupling); 
        //else draw_1_hist(pathname + "/" + h->GetName() + ".pdf", c, h, "E1", &lgendrup, "", "", 0, 0, 0, flavor, mass, coupling);
        //within public/2l2q_analysis/plots/ every different sample gets its own directory 
        //A higher/lower directory based on what cuts I apply? Higher makes more sense
        //Make a directory all! (to easily copy to my pc)
    } 


    return 0;
}
# endif
