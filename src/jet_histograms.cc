//////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include <iostream>

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::add_jet_histograms(map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_jet1_pt"]                     = new TH1F(prefix+"_jet1_pt", ";jet_1 #it{p}_{T};Events", 60, 0, 140); 
    (*hists)[prefix+"_jetl2_index"]                 = new TH1F(prefix+"_jetl2_index", ";closestJet(l_{2}) Index;Events", 15, -1, 14);
    (*hists)[prefix+"_jetl2_pt"]                    = new TH1F(prefix+"_jetl2_pt", ";closestJet(l_{2});Events", 60, 0, 140);
}

void full_analyzer::fill_jet_histograms(map<TString, TH1*>* hists, TString prefix){
    if(i_leading_jet != -1) (*hists)[prefix+"_jet1_pt"]->Fill(_jetPt[i_leading_jet], event_weight);
    (*hists)[prefix+"_jetl2_index"]->Fill(i_closel2_jet, event_weight);
    if(i_closel2_jet != -1) (*hists)[prefix+"_jetl2_pt"]->Fill(_jetPt[i_closel2_jet], event_weight);
}
