//////////////////////////////////////////////////////
//initializes MET related histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

void full_analyzer::add_MET_histograms(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_met"]                     = new TH1F(prefix+"_met", ";Type 1 E_{T}^{miss} [GeV];Events", 50, 0, 300); 
    (*hists)[prefix+"_metSM"]                   = new TH1F(prefix+"_metSM", ";Smeared E_{T}^{miss} [GeV];Events", 50, 0, 300); 
    (*hists)[prefix+"_metRaw"]                  = new TH1F(prefix+"_metRaw", ";Raw E_{T}^{miss} [GeV];Events", 50, 0, 300); 
    (*hists)[prefix+"_metPhi"]                  = new TH1F(prefix+"_metPhi", ";Type 1 E_{T}^{miss} Phi;Events", 50, -3.1415, 3.1415); 
    (*hists)[prefix+"_metSMPhi"]                = new TH1F(prefix+"_metSMPhi", ";Smeared E_{T}^{miss} Phi;Events", 50, -3.1415, 3.1415); 
    (*hists)[prefix+"_metRawPhi"]               = new TH1F(prefix+"_metRawPhi", ";Raw E_{T}^{miss} Phi;Events", 50, -3.1415, 3.1415); 
    
    (*hists)[prefix+"_nPV"]                     = new TH1F(prefix+"_nPV", ";nPV;Events", 100, 0, 100); 
}

void full_analyzer::fill_MET_histograms(std::map<TString, TH1*>* hists, TString prefix, int i_leading, int i_subleading){
    (*hists)[prefix+"_met"]->Fill(_met, event_weight);
    (*hists)[prefix+"_metSM"]->Fill(_met, event_weight); //FIX
    (*hists)[prefix+"_metRaw"]->Fill(_metRaw, event_weight);
    (*hists)[prefix+"_metPhi"]->Fill(_metPhi, event_weight);
    (*hists)[prefix+"_metSMPhi"]->Fill(_metPhi, event_weight);//FIX
    (*hists)[prefix+"_metRawPhi"]->Fill(_metRawPhi, event_weight);
   
    (*hists)[prefix+"_nPV"]->Fill(_nVertex, event_weight);
}
