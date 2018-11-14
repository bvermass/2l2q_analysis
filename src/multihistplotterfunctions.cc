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
    TString pathname                = "/user/bvermass/public/2l2q_analysis/plots/multihists/";

    string str(argv[1]); // used to only plot electron plots for e signal and mu plots for mu signal
    cout << str  << " " << str.find("_mu_") << " " << str.find("_e_") << endl;

    // define canvas and legend(s)
    TCanvas *c = new TCanvas("c","",700,700);
    gStyle->SetPalette(55);
    gStyle->SetOptStat(0);
    gPad->SetTicks(1,1);

    TLegend lgendrup(.5,.7,.85,.85);
    lgendrup.SetBorderSize(0);
    lgendrup.SetFillStyle(0);

    // put all files in a map that can be looped over
    std::map<TString, TFile*> files;
    for(int i = 1; i < (argc + 1)/2; i++){
        TString name = (TString)argv[i];
        TString fullname = to_string(i) + "_" + name(name.Index("full_analyzer/") + 14, name.Index(".root") - name.Index("full_analyzer") - 14);
        files[fullname] = TFile::Open(argv[i]);
        cout << fullname << endl;
    }

    // loop over histograms
    std::map<TString, TH1*> hists;
    TString nameforkey = (TString)argv[1];
    TString fullnameforkey = "1_" + nameforkey(nameforkey.Index("full_analyzer/") + 14, nameforkey.Index(".root") - nameforkey.Index("full_analyzer") - 14);
    TIter next(files[fullnameforkey]->GetListOfKeys());
    TKey * key;

    while ((key = (TKey*)next())) {
        hists.clear();
        
        // get correct reference histogram
        TClass *cl = gROOT->GetClass(key->GetClassName());
        if (!cl->InheritsFrom("TH1")) continue;
        TH1F *h_ref = (TH1F*)key->ReadObj(); //h_ref is the reference histogram that knows the name etc. of the histogramt
        //cout << h_ref->GetName() << endl;
        TString histname = h_ref->GetName();
        if(h_ref->GetMaximum() == 0) continue;

        if(str.find("_mu_") != std::string::npos && (histname.Index("_e_") != -1 || histname.Index("_Ele_") != -1)) continue; //skip plots of opposite signal, these are empty anyway 
        if(str.find("_e_") != std::string::npos && (histname.Index("_mu_") != -1 || histname.Index("_Mu_") != -1))  continue;

        TString pathname_lin = make_pathname(histname, pathname, "lin");
        TString pathname_log = make_pathname(histname, pathname, "log");
        gSystem->Exec("mkdir -p " + pathname_lin);
        gSystem->Exec("mkdir -p " + pathname_log);

        // find flavor e or mu
        TString flavor;
        TString checkflavor = h_ref->GetName();                 //CHANGE THIS SECTION, MAKE h_ref->GetName() a separate variable and improve else option of flavor!
        if(checkflavor.Index("_e_") != -1) flavor = "e";
        else if(checkflavor.Index("_mu_") != -1) flavor = "#mu";
        else flavor = "e";

        // get background and signal histograms
        for(int i = 1; i < (argc +1)/2; i++){
            TString name = (TString)argv[i];
            TString fullname = to_string(i) + "_" + name(name.Index("full_analyzer/") + 14, name.Index(".root") - name.Index("full_analyzer") - 14) ;
            hists[fullname] = (TH1F*) files[fullname]->Get(histname);
        }
        mapmarkerstyle(hists);

        THStack *stack = new THStack("stack", h_ref->GetName());
        int i = (argc + 1) / 2;//to iterate over legends    CHANGE THIS TO LET A FUNCTION DECIDE ON THE LEGEND NAME BASED ON THE FILENAME
        double scale_factor = 100;

        lgendrup.Clear();
        for( it3 = hists.begin(); it3 != hists.end(); it3++){
            TH1* h = it3->second;
            //cout << "histname: " << it3->first << " legend: " << argv[i] << endl;
            if(histname.Index("eff") == -1) h->Scale(scale_factor / h->Integral());
	        stack->Add(h);
            lgendrup.AddEntry(h, argv[i]);
            i++;
        }
 
        draw_stack(pathname_lin + h_ref->GetName() + ".pdf", c, stack, &lgendrup, h_ref->GetXaxis()->GetTitle(), h_ref->GetYaxis()->GetTitle(), 0, -1, -1, -1, -1, "nostack");
        draw_stack(pathname_log + h_ref->GetName() + ".pdf", c, stack, &lgendrup, h_ref->GetXaxis()->GetTitle(), h_ref->GetYaxis()->GetTitle(), 1, -1, -1, 10, -1, "nostack");
    
    }
    cout << "plots finished" << endl;
    return 0;
}
# endif
