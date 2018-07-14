//////////////////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, code for determining lepton ID and pt ordering of leptons//
//////////////////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"


void full_analyzer::get_electronID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	bool fullID = 	
            _lFlavor[i] == 0 &&
			fabs(_lEta[i]) < 2.5 &&
			_lPt[i] > 7 &&
			fabs(_dxy[i]) < 0.05 &&
			fabs(_dz[i])  < 0.1 &&
			_3dIPSig[i]   < 4 &&
			_relIso[i]    < 0.2 &&
			_lPOGMedium[i] &&
			_lElectronPassConvVeto[i] &&
			_lElectronMissingHits[i] < 1;
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}

void full_analyzer::get_noniso_electronID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	bool fullID = 	_lFlavor[i] == 0 &&
			fabs(_lEta[i]) < 2.5 &&
			_lPt[i] > 7 &&
			fabs(_dxy[i]) < 0.05 &&
			fabs(_dz[i])  < 0.1 &&
			_3dIPSig[i]   < 4 &&
			_relIso[i]    > 0.2 &&
			//_lPOGMedium[i] && //->clashes with reliso > 0.2
			_lElectronPassConvVeto[i] &&
			_lElectronMissingHits[i] < 1;
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}

void full_analyzer::get_displ_electronID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	bool fullID = 	_lFlavor[i] == 0 &&
			fabs(_lEta[i]) < 2.5 &&
			_lPt[i] > 7 &&
			fabs(_dxy[i])  > 0.05 &&
			//no dz cut
			//no SIP3D cut
			//also invert reliso?
			//no pogmedium?
			_lElectronPassConvVeto[i];//figure out how this one works exactly to be sure it can still be applied!
			//no missing hits cut?
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}


void full_analyzer::get_muonID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	bool fullID = 	_lFlavor[i] == 1 &&
			fabs(_lEta[i]) < 2.4 &&
			_lPt[i] > 5 &&
			fabs(_dxy[i]) < 0.05 &&
			fabs(_dz[i])  < 0.1 &&
			_3dIPSig[i]   < 4 &&
			_relIso[i]    < 0.2 &&
			_lPOGMedium[i];
			// innertrack, PFmuon and global or tracker muon conditions are executed at ntuplizer level and not stored
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}

void full_analyzer::get_noniso_muonID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	bool fullID = 	_lFlavor[i] == 1 &&
			fabs(_lEta[i]) < 2.4 &&
			_lPt[i] > 5 &&
			fabs(_dxy[i]) < 0.05 &&
			fabs(_dz[i])  < 0.1 &&
			_3dIPSig[i]   < 4 &&
			_relIso[i]    > 0.2 &&
			_lPOGMedium[i];
			// innertrack, PFmuon and global or tracker muon conditions are executed at ntuplizer level and not stored
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}

void full_analyzer::get_displ_muonID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	bool fullID = 	_lFlavor[i] == 1 &&
			fabs(_lEta[i]) < 2.4 &&
			_lPt[i] > 5 &&
			fabs(_dxy[i]) > 0.05;
			//no dz cut
			//no SIP3D cut
			//also invert reliso?
			//no POGMedium? no because it requires dxy of the track to be small 
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}





void full_analyzer::get_clean_ele(bool* cleaned, bool* muonID)
{
    // This function returns false in the boolean cleaned for electrons within a cone of 0.4 around muons
    TLorentzVector muon;
    TLorentzVector electron;

    for(unsigned i_el = 0; i_el < _nL; ++i_el){
	    *(cleaned + i_el) = true;
	    if(_lFlavor[i_el] != 0) continue;
	    electron.SetPtEtaPhiE(_lPt[i_el], _lEta[i_el], _lPhi[i_el], _lE[i_el]);

	    for(unsigned i_mu = 0; i_mu < _nL; ++i_mu){
	        if(_lFlavor[i_mu] == 1 && *(muonID + i_mu)){
	    	muon.SetPtEtaPhiE(_lPt[i_mu], _lEta[i_mu], _lPhi[i_mu], _lE[i_mu]);
	    	if(muon.DeltaR(electron) < 0.4) *(cleaned + i_el) = false;
	        }
	    }
    }
}




int full_analyzer::find_leading_e(bool* electronID, bool* ele_clean)
{
    int index_good_leading = -1;
    for(unsigned i = 0; i < _nL; ++i){
	    if(_lFlavor[i] != 0)   continue;
	    if(!*(electronID + i)) continue;
	    if(!*(ele_clean + i))  continue;
	    //if(_lPt[i] < 30)       continue;
	    if(index_good_leading == -1) index_good_leading = i;
	    if(_lPt[i] > _lPt[index_good_leading]) index_good_leading = i;
    }
    return index_good_leading;
}

int full_analyzer::find_leading_mu(bool* muonID)
{
    int index_good_leading = -1;
    for(unsigned i = 0; i < _nL; ++i){
	    if(_lFlavor[i] != 1) continue;
	    if(!*(muonID + i))   continue;
	    //if(_lPt[i] < 25)     continue;
	    if(index_good_leading == -1) index_good_leading = i;
	    if(_lPt[i] > _lPt[index_good_leading]) index_good_leading = i;
    }
    return index_good_leading;
}


int full_analyzer::find_subleading_e(bool* electronID, bool* ele_clean, int index_good_leading)
{
    int index_good_subleading = -1;
    if(index_good_leading == -1) return index_good_subleading;
    for(int i = 0; i < _nL; ++i){
	    if(i == index_good_leading) continue;
	    if(_lFlavor[i] != 0)   	    continue;
	    //if(_lCharge[i] != _lCharge[index_good_leading]) continue;
	    if(!*(electronID + i))      continue;
	    if(!*(ele_clean + i))       continue;
	    if(_lPt[i] < 7)             continue;
	    if(index_good_subleading == -1) index_good_subleading = i;
	    if(_lPt[i] > _lPt[index_good_subleading]) index_good_subleading = i;
    }
    return index_good_subleading;
}

int full_analyzer::find_subleading_mu(bool* muonID, int index_good_leading)
{
    int index_good_subleading = -1;
    if(index_good_leading == -1) return index_good_subleading;
    for(int i = 0; i < _nL; ++i){
	    if(i == index_good_leading) continue;
	    if(_lFlavor[i] != 1)   	    continue;
	    //if(_lCharge[i] != _lCharge[index_good_leading]) continue;
	    if(!*(muonID + i))          continue;
	    if(_lPt[i] < 5)             continue;
	    if(index_good_subleading == -1) index_good_subleading = i;
	    if(_lPt[i] > _lPt[index_good_subleading]) index_good_subleading = i;
    }
    return index_good_subleading;
}

