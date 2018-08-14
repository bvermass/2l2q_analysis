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
#include "../interface/multihistplotterfunctions.h"

using namespace std;

std::map<TString, TH1*>::iterator it3;

# ifndef __CINT__
int main(int argc, char * argv[])
{
    TString pathname                = "/afs/cern.ch/work/b/bvermass/public/2l2q_analysis/plots/multihists/";

    // define canvas and legend(s)
    TCanvas *c = new TCanvas("c","",700,700);
    gStyle->SetPalette(55);
    gStyle->SetOptStat(0);
    gPad->SetTicks(1,1);

    TLegend lgendrup(.6,.7,.85,.85);
    lgendrup.SetBorderSize(0);
    lgendrup.SetFillStyle(0);

    // put all files in a map that can be looped over
    std::map<TString, TFile*> files;
    for(int i = 1; i < (argc + 1)/2; i++){
        files[argv[i]] = TFile::Open(argv[i]);
        cout << argv[i] << endl;
    }

    // loop over histograms
    std::map<TString, TH1*> hists;
    TIter next(files[argv[1]]->GetListOfKeys());
    TKey * key;

    while ((key = (TKey*)next())) {
        hists.clear();
        
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
        
        gSystem->Exec("mkdir -p " + pathname + HLT + SSorOS + eormu + "lin/");
        gSystem->Exec("mkdir -p " + pathname + HLT + SSorOS + eormu + "log/");


        // find flavor e or mu
        TString flavor;
        TString checkflavor = h_ref->GetName();                 //CHANGE THIS SECTION, MAKE h_ref->GetName() a separate variable and improve else option of flavor!
        if(checkflavor.Index("_e_") != -1) flavor = "e";
        else if(checkflavor.Index("_mu_") != -1) flavor = "#mu";
        else flavor = "e";

        // get background and signal histograms
        for(int i = 1; i < (argc +1)/2; i++){
            TString name = (TString)argv[i];
            name = i + "_" + name(name.Index("full_analyzer/") + 14, name.Index(".root") - name.Index("full_analyzer") - 14) ;
            hists[name] = (TH1F*) files[argv[i]]->Get(h_ref->GetName());
        }
        mapmarkerstyle(hists);

        THStack *stack = new THStack("stack", h_ref->GetName());
        int i = (argc + 1) / 2;//to iterate over legends    CHANGE THIS TO LET A FUNCTION DECIDE ON THE LEGEND NAME BASED ON THE FILENAME
        double scale_factor = 1000;

        lgendrup.Clear();
        TRandom* var = new TRandom3();
        for( it3 = hists.begin(); it3 != hists.end(); it3++){
            TH1* h = it3->second;
            double variation = (var->Rndm(i) / 5) + 0.9;
            h->Scale(scale_factor / h->GetMaximum() * variation);
	        stack->Add(h);
            lgendrup.AddEntry(h, argv[i]);
            i++;
        }
 
        draw_stack(pathname + HLT + SSorOS + eormu + "lin/" + h_ref->GetName() + ".pdf", c, stack, &lgendrup, h_ref->GetXaxis()->GetTitle(), h_ref->GetYaxis()->GetTitle(), 0, -1, -1, -1, -1, "nostack");
        draw_stack(pathname + HLT + SSorOS + eormu + "log/" + h_ref->GetName() + ".pdf", c, stack, &lgendrup, h_ref->GetXaxis()->GetTitle(), h_ref->GetYaxis()->GetTitle(), 1, -1, -1, 10, -1, "nostack");
    
    }
    return 0;
}
# endif
