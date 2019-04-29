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
#include <TMultiGraph.h>

#include "../interface/plotterfunctions.h"
#include "../interface/multihistplotterfunctions.h"

using namespace std;

std::map<TString, TH1*>::iterator it3;
std::map<TString, TGraphAsymmErrors*>::iterator it3_graph;

# ifndef __CINT__
int main(int argc, char * argv[])
{
    if(argc%2 != 1) std::cout << "did you forget a title in the sampleList file?" << std::endl;

    TString pathname                = "/user/bvermass/public/2l2q_analysis/plots/multihists/" + (TString)argv[1] + "/";

    string flavor(argv[2]); // used to only plot electron plots for e signal and mu plots for mu signal
    
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
    for(int i = 3; i < (argc + 3)/2; i++){
        TString name = (TString)argv[i];
        TString fullname = to_string(i) + "_" + name(name.Index("full_analyzer/") + 14, name.Index(".root") - name.Index("full_analyzer") - 14);
        files[fullname] = TFile::Open(argv[i]);
        cout << fullname << endl;
    }

    // loop over histograms
    std::map<TString, TH1*> hists;
    std::map<TString, TGraphAsymmErrors*> graphs;
    TString nameforkey = (TString)argv[3];
    TString fullnameforkey = "3_" + nameforkey(nameforkey.Index("full_analyzer/") + 14, nameforkey.Index(".root") - nameforkey.Index("full_analyzer") - 14);
    TIter next(files[fullnameforkey]->GetListOfKeys());
    TKey * key;

    while ((key = (TKey*)next())) {
        
        // get correct reference histogram
        TClass *cl = gROOT->GetClass(key->GetClassName());

        if (cl->InheritsFrom("TH1")){
            TH1F *h_ref = (TH1F*)key->ReadObj(); //h_ref is the reference histogram that knows the name etc. of the histogramt
            if(h_ref->GetMaximum() == 0) continue;
        
            //cout << h_ref->GetName() << endl;
            TString histname = h_ref->GetName();

            if(flavor == "mu" && (histname.Index("_e_") != -1 || histname.Index("_Ele_") != -1)) continue; //skip plots of wrong flavor for signal, as these are empty anyway 
            if(flavor == "e"  && (histname.Index("_mu_") != -1 || histname.Index("_Mu_") != -1))  continue;

            TString pathname_lin = make_pathname(histname, pathname, "lin");
            TString pathname_log = make_pathname(histname, pathname, "log");
            gSystem->Exec("mkdir -p " + pathname_lin);
            gSystem->Exec("mkdir -p " + pathname_log);

            // get background and signal histograms
            hists.clear();
            if(histname.Index("eff_num") != -1) graphs.clear();
            for(int i = 3; i < (argc + 3)/2; i++){
                TString name = (TString)argv[i];
                TString fullname = to_string(i) + "_" + name(name.Index("full_analyzer/") + 14, name.Index(".root") - name.Index("full_analyzer") - 14) ;
                hists[fullname] = (TH1F*) files[fullname]->Get(histname);
                if(histname.Index("eff_num") != -1) graphs[fullname] = new TGraphAsymmErrors((TH1F*) files[fullname]->Get(histname), (TH1F*) files[fullname]->Get(histname(0, histname.Index("eff_num")+4) + "den"));
            }
            
            mapmarkerstyle(hists);

            THStack *stack = new THStack("stack", histname);
            int i = (argc + 3) / 2;//to iterate over legends    CHANGE THIS TO LET A FUNCTION DECIDE ON THE LEGEND NAME BASED ON THE FILENAME
            double scale_factor = 100;
            lgendrup.Clear();

            for( it3 = hists.begin(); it3 != hists.end(); it3++){
                TH1* h = it3->second;
                //cout << "histname: " << it3->first << " legend: " << argv[i] << endl;
                if(histname.Index("eff") == -1 and histname.Index("_cutflow") == -1) h->Scale(scale_factor / h->Integral());
	            stack->Add(h);
                lgendrup.AddEntry(h, argv[i]);
                i++;
            }
 
            // x lin or log
            int xlog = (histname.Index("xlog") == -1)? 0 : 1;
            // Events or Eff. in yaxis title
            TString yaxistitle = h_ref->GetYaxis()->GetTitle(); 


            draw_stack(pathname_lin + histname + ".pdf", c, stack, &lgendrup, h_ref->GetXaxis()->GetTitle(), yaxistitle, 0, xlog, -1, -1, -1, -1, "nostack");
            draw_stack(pathname_log + histname + ".pdf", c, stack, &lgendrup, h_ref->GetXaxis()->GetTitle(), yaxistitle, 1, xlog, -1, -1, -1, -1, "nostack");

            // Calculate and draw efficiencies as TGraphAsymmErrors
            if(histname.Index("eff_num") != -1){
                TMultiGraph* multigraph = new TMultiGraph();
                for( it3_graph = graphs.begin(); it3_graph != graphs.end(); it3_graph++){
                    it3_graph->second->SetLineWidth(2);
                    multigraph->Add(it3_graph->second);
                }
                yaxistitle = "Eff.";
                draw_multigraph(pathname_lin + histname(0,histname.Index("eff_num")+3) + ".pdf", c, multigraph, &lgendrup, h_ref->GetXaxis()->GetTitle(), yaxistitle, 0, xlog, -1, -1, -1, -1, "AP pmc plc");
                draw_multigraph(pathname_log + histname(0,histname.Index("eff_num")+3) + ".pdf", c, multigraph, &lgendrup, h_ref->GetXaxis()->GetTitle(), yaxistitle, 1, xlog, -1, -1, -1, -1, "AP pmc plc");
            }
        }
    }
    cout << "plots finished" << endl;
    return 0;
}
# endif
