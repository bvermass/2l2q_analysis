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

int full_analyzer::find_thirdleading_jet(bool* jetID, bool* jet_clean, int index_good_leading, int index_good_subleading)
{
    int index_good_thirdleading = -1;
    if(index_good_leading == -1 or index_good_subleading == -1) return index_good_thirdleading;
    for(int i = 0; i < _nJets; ++i){
	    if(i == index_good_leading or i == index_good_subleading) continue;
	    if(!*(jetID + i))           continue;
	    if(!*(jet_clean + i))       continue;
	    if(index_good_thirdleading == -1) index_good_thirdleading = i;
	    if(_lPt[i] > _lPt[index_good_thirdleading]) index_good_thirdleading = i;
    }
    return index_good_thirdleading;
}

int full_analyzer::find_jet_closest_to_lepton(bool* jetID, int i_lep)
{
    int index_jet = -1;
    if(i_lep == -1) return index_jet;
    
    double dR    = -1;
    double mindR = 10;
    
    for(int i_jet = 0; i_jet < _nJets; i_jet++){
        if(!*(jetID + i_jet)) continue;
        dR = get_dR_lepton_jet(i_lep, i_jet);
        if(index_jet == -1){ index_jet = i_jet;}
        if(dR < mindR){ index_jet = i_jet; mindR = dR;}
    }

    return index_jet;
}

double full_analyzer::get_dR_lepton_jet(TLorentzVector vec_lep, TLorentzVector vec_jet){
    return fabs(vec_lep.DeltaR(vec_jet));
}

double full_analyzer::get_dR_lepton_jet(int i_lep, int i_jet){
    TLorentzVector vec_lep;
    vec_lep.SetPtEtaPhiE(_lPt[i_lep], _lEta[i_lep], _lPhi[i_lep], _lE[i_lep]);
    TLorentzVector vec_jet;
    vec_jet.SetPtEtaPhiE(_jetPt[i_jet], _jetEta[i_jet], _jetPhi[i_jet], _jetE[i_jet]);
    return fabs(vec_lep.DeltaR(vec_jet));
}

double full_analyzer::get_dR_lepton_jet(int i_lep, TLorentzVector& vec_jet){
    TLorentzVector vec_lep;
    vec_lep.SetPtEtaPhiE(_lPt[i_lep], _lEta[i_lep], _lPhi[i_lep], _lE[i_lep]);
    return fabs(vec_lep.DeltaR(vec_jet));
}

