#include "Skimmer.h"

void Skimmer::get_TightelectronID(bool* ID)
{
    for(unsigned i = 0; i < i_nL; ++i){
	    *(ID + i)   =   i_lFlavor[i] == 0 &&
			            fabs(i_lEta[i]) < 2.5 &&
			            i_lPt[i] > 20 &&
			            fabs(i_dxy[i]) < 0.05 &&
			            fabs(i_dz[i])  < 0.1 &&
			            i_3dIPSig[i]   < 4 &&
			            i_relIso[i]    < 0.1 &&
			            i_lPOGMedium[i] &&
			            i_lElectronPassConvVeto[i] &&
			            i_lElectronMissingHits[i] < 1;
    }
}


void Skimmer::get_TightmuonID(bool* ID)
{
    for(unsigned i = 0; i < i_nL; ++i){
	    *(ID + i)    = 	i_lFlavor[i] == 1 &&
			            fabs(i_lEta[i]) < 2.4 &&
			            i_lPt[i] > 20 &&
			            fabs(i_dxy[i]) < 0.05 &&
			            fabs(i_dz[i])  < 0.1 &&
			            i_3dIPSig[i]   < 4 &&
			            i_relIso[i]    < 0.1 &&
                        i_lPOGMedium[i];
			            // innertrack, PFmuon and global or tracker muon conditions are executed at ntuplizer level and not stored
    }
}


void Skimmer::get_clean_ele(bool* cleaned, bool* muonID)
{
    // The array cleaned will contain value true when the electron is not within dR < 0.05 around a muon
    for(unsigned i_el = 0; i_el < i_nL; ++i_el){
	    *(cleaned + i_el) = true;
	    if(i_lFlavor[i_el] != 0) continue;
	    LorentzVector electron(i_lPt[i_el], i_lEta[i_el], i_lPhi[i_el], i_lE[i_el]);

	    for(unsigned i_mu = 0; i_mu < i_nL; ++i_mu){
	        if(i_lFlavor[i_mu] == 1 && *(muonID + i_mu)){
                LorentzVector muon(i_lPt[i_mu], i_lEta[i_mu], i_lPhi[i_mu], i_lE[i_mu]);
                if(deltaR(electron, muon) < 0.05) *(cleaned + i_el) = false;
	        }
	    }
    }
}


bool Skimmer::ElectronTriggerSkim(){return (i_passTrigger_ee or i_passTrigger_e);}


bool Skimmer::MuonTriggerSkim(){return (i_passTrigger_mm or i_passTrigger_m);}


bool Skimmer::dileptonSkim(){
    get_TightelectronID(&TightelectronID[0]);
    get_TightmuonID(&TightmuonID[0]);

    get_clean_ele(&ele_cleaned_tight[0], &TightmuonID[0]);

    int Tightleptons = 0;
    for(unsigned i = 0; i < i_nL; i++){
        if(TightmuonID[i] or (TightelectronID[i] and ele_cleaned_tight[i])) Tightleptons++;
    }
    return (Tightleptons >= 2);
}


bool Skimmer::Check_SkimCondition(TString Condition)
{
    if(Condition == "dileptonSkim") return ((ElectronTriggerSkim() or MuonTriggerSkim()) and dileptonSkim());
    else return true;
}
