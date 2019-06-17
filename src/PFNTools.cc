/////////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to HLT efficiency calculation//
/////////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

//Gives the corresponding HNL jet tag value for i_jet with the tagger loaded in pfn
double full_analyzer::get_PFNprediction(PFNReader pfn, int i_jet){
    if(i_jet == -1) return 0;
    std::vector< double > highlevelInput( { _jetPt[i_jet], _jetEta[i_jet] } );
    std::vector< std::vector< double > > pfnInput;

    for( unsigned i_const = 0; i_const < _nJetConstituents[i_jet]; ++i_const){
        pfnInput.push_back( { _JetConstituentPt[i_jet][i_const], _JetConstituentEta[i_jet][i_const], _JetConstituentPhi[i_jet][i_const], _JetConstituentdxy[i_jet][i_const], _JetConstituentdz[i_jet][i_const], _JetConstituentdxyErr[i_jet][i_const], _JetConstituentdzErr[i_jet][i_const], (double) _JetConstituentNumberOfHits[i_jet][i_const], (double) _JetConstituentNumberOfPixelHits[i_jet][i_const], (double)_JetConstituentCharge[i_jet][i_const], (double) _JetConstituentPdgId[i_jet][i_const] } );
    }

    for( unsigned i = _nJetConstituents[i_jet]; i < 50; ++i){
        pfnInput.push_back( {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } );
    }

    return pfn.predict( pfnInput, highlevelInput );
}

void full_analyzer::add_pfn_histograms(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_JetTagVal"]       = new TH1F(prefix+"_JetTagVal", ";Jet Tag Value; Events", 40, 0, 1);
    (*hists)[prefix+"_JetTagValzm"]       = new TH1F(prefix+"_JetTagValzm", ";Jet Tag Value; Events", 40, 0.9, 1);
}

void full_analyzer::fill_pfn_histograms(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_JetTagVal"]->Fill(JetTagVal, event_weight);
    (*hists)[prefix+"_JetTagValzm"]->Fill(JetTagVal, event_weight);
}
