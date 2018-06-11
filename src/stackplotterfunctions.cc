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
#include <cmath>
#include <TRandom3.h>
#include <TKey.h>
#include <TSystem.h>
#include <THStack.h>

#include "../interface/plotterfunctions.h"
#include "../interface/testplotterfunctions.h"

using namespace std;


# ifndef __CINT__
int main(int argc, char * argv[])
{
    TString pathname = "~/public/2l2q_analysis/plots/stacks/";

    // define canvas and legend(s)
    TCanvas *c = new TCanvas("c","",700,700);
    gStyle->SetPalette(55);
    gStyle->SetOptStat(0);
    gPad->SetTicks(1,1);

    TLegend lgendrup(.6,.6,.85,.85);
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
    
        TClass *cl = gROOT->GetClass(key->GetClassName());
        if (!cl->InheritsFrom("TH1")) continue;
        TH1F *h_ref = (TH1F*)key->ReadObj(); //h_ref is the reference histogram that knows the name etc. of the histogram
        cout << h_ref->GetName() << endl;
        cout << h_ref->GetXaxis()->GetTitle() << endl;

        for(int i = 1; i < (argc +1)/2; i++){
            TString name = (TString)argv[i];
            name = to_string(i) + "_" + name(name.Index("full_analyzer/") + 14, name.Index(".root") - name.Index("full_analyzer") - 14) ;
            hists[name] = (TH1F*) files[argv[i]]->Get(h_ref->GetName());
        }

        mapmarkerstyle(hists);
        THStack *stack = new THStack("stack","");
        int i = (argc + 1) / 2;//to iterate over legends    CHANGE THIS TO LET A FUNCTION DECIDE ON THE LEGEND NAME BASED ON THE FILENAME
        lgendrup.Clear();
        for(auto&& sh : hists){
	        auto&& h = sh.second;
	        stack->Add(h);
            lgendrup.AddEntry(h, argv[i]);
            i++;
        }
        
        draw_stack(pathname + "lin/" + h_ref->GetName() + ".pdf", c, stack, &lgendrup, h_ref->GetXaxis()->GetTitle(), h_ref->GetYaxis()->GetTitle(), 0, -1, -1, -1, -1);
        draw_stack(pathname + "log/" + h_ref->GetName() + ".pdf", c, stack, &lgendrup, h_ref->GetXaxis()->GetTitle(), h_ref->GetYaxis()->GetTitle(), 1, -1, -1, 10, -1);
        //if(((TString)h->GetName()).Index("eff") == -1) draw_1_hist(pathname + "/" + h->GetName() + ".pdf", c, h, "hist", &lgendrup, "", "", 0, 0, 0, flavor, mass, coupling); 
        //else draw_1_hist(pathname + "/" + h->GetName() + ".pdf", c, h, "E1", &lgendrup, "", "", 0, 0, 0, flavor, mass, coupling);
        //within public/2l2q_analysis/plots/ every different sample gets its own directory 
        //A higher/lower directory based on what cuts I apply? Higher makes more sense
        //Make a directory all! (to easily copy to my pc)
    } 

    return 0;
}
# endif
