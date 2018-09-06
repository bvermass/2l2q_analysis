////////////////////////////////////////////////////
//part of class full_analyzer, jet ID and cleaning//
////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

void full_analyzer::get_jetID(bool* ID)
{
    for(unsigned i = 0; i < _nJets; ++i){
	    bool fullID = 	fabs(_jetEta[i]) < 2.4 &&
			            _jetPt[i] > 20 &&
			            _jetIsTight[i];
	    if(fullID) *(ID + i) = true;
	    else *(ID + i) = false;
    }
}


void full_analyzer::get_clean_jets(bool* cleaned, bool* electronID, bool* muonID)
{
    // jets are cleaned from leptons if dR < 0.4 
    TLorentzVector lepton;
    TLorentzVector jet;

    for(unsigned i = 0; i < _nJets; ++i){
	    *(cleaned + i) = true;
	    jet.SetPtEtaPhiE(_jetPt[i], _jetEta[i], _jetPhi[i], _jetE[i]);

	    for(unsigned j = 0; j < _nL; ++j){
	        lepton.SetPtEtaPhiE(_lPt[j], _lEta[j], _lPhi[j], _lE[j]);
	        if((_lFlavor[j] == 0 && *(electronID + j)) || (_lFlavor[j] == 1 && *(muonID + j))){
		        if(lepton.DeltaR(jet) < 0.4) *(cleaned + i) = false;
	        }
	    }
    }
}


int full_analyzer::find_leading_jet(bool* jetID, bool* jet_clean)
{
    int index_good_leading = -1;
    for(unsigned i = 0; i < _nJets; ++i){
	    if(!*(jetID + i))      continue;
	    if(!*(jet_clean + i))  continue;
	    if(index_good_leading == -1) index_good_leading = i;
	    if(_lPt[i] > _lPt[index_good_leading]) index_good_leading = i;
    }
    return index_good_leading;
}

int full_analyzer::find_subleading_jet(bool* jetID, bool* jet_clean, int index_good_leading)
{
    int index_good_subleading = -1;
    if(index_good_leading == -1) return index_good_subleading;
    for(int i = 0; i < _nJets; ++i){
	    if(i == index_good_leading) continue;
	    if(!*(jetID + i))           continue;
	    if(!*(jet_clean + i))       continue;
	    if(index_good_subleading == -1) index_good_subleading = i;
	    if(_lPt[i] > _lPt[index_good_subleading]) index_good_subleading = i;
    }
    return index_good_subleading;
}

