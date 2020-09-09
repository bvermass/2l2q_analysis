#include "Skimmer.h"

void Skimmer::get_TightelectronID(bool* ID)
{
    for(unsigned i = 0; i < i_nL; ++i){
	    *(ID + i)   =   i_lFlavor[i] == 0 &&
			            fabs(i_lEta[i]) < 2.5 &&
			            i_lPt[i] > 10 &&
			            fabs(i_dxy[i]) < 0.05 &&
			            fabs(i_dz[i])  < 0.1 &&
			            i_3dIPSig[i]   < 8 &&
			            //i_relIso[i]    < 0.1 &&
                        (i_leptonMvatZq[i] > 0.7 or i_leptonMvaTTH[i] > 0.7 or i_leptonMvaTOP[i] > -0.5 or i_lPOGMedium[i]) &&
			            //i_lPOGMedium[i] && old ID, move to MVAtZqTTV16
			            i_lElectronPassConvVeto[i] &&
			            i_lElectronMissingHits[i] < 1;
    }
}


void Skimmer::get_DisplelectronID(bool* ID)  //basically medium POG cut-based ID without displacement interfering requirements
{
    for(unsigned i = 0; i < i_nL; i++){
        *(ID + i)   =   i_lFlavor[i] == 0 &&
                        fabs(i_lEta[i]) < 2.5 &&
                        i_lPt[i] > 7 &&
                        //fabs(i_dxy[i]) > 0.01 && for now, require this as a separate condition
                        i_lElectronPassConvVeto[i] &&
                        (   (i_lElectronIsEB[i] &&
                             i_lElectronSigmaIetaIeta[i] <= 0.11 &&
                             i_lElectronDEtaInSeed[i] <= 0.00477 &&
                             i_lElectronDeltaPhiSuperClusterTrack[i] <= 0.222 &&
                             i_lElectronHOverE[i] <= 0.298 &&
                             i_lElectronEInvMinusPInv[i] <= 0.241)
                            || 
                            (i_lElectronIsEE[i] &&
                             i_lElectronSigmaIetaIeta[i] <= 0.0314 &&
                             i_lElectronDEtaInSeed[i] <= 0.00868 &&
                             i_lElectronDeltaPhiSuperClusterTrack[i] <= 0.213 &&
                             i_lElectronHOverE[i] <= 0.101 &&
                             i_lElectronEInvMinusPInv[i] <= 0.14
                            )
                        );
    }
}


void Skimmer::get_TightmuonID(bool* ID)
{
    for(unsigned i = 0; i < i_nL; ++i){
	    *(ID + i)    = 	i_lFlavor[i] == 1 &&
			            fabs(i_lEta[i]) < 2.4 &&
			            i_lPt[i] > 10 &&
			            fabs(i_dxy[i]) < 0.05 &&
			            fabs(i_dz[i])  < 0.1 &&
			            i_3dIPSig[i]   < 4 &&
			            //i_relIso[i]    < 0.1 &&
                        (i_leptonMvatZq[i] > 0.7 or i_leptonMvaTTH[i] > 0.7 or i_leptonMvaTOP[i] > -0.5 or i_lPOGMedium[i]);
                        //i_lPOGMedium[i]; old ID, move to MVAtZqTTV16
			            // innertrack, PFmuon and global or tracker muon conditions are executed at ntuplizer level and not stored
    }
}


void Skimmer::get_DisplmuonID(bool* ID)
{
    for(unsigned i = 0; i < i_nL; ++i){
        bool goodglobalmuon =   i_lGlobalMuon[i] &&
                                i_lGlobalTrackNormalizedChi2[i] < 3 &&
                                i_lCQChi2Position[i] < 12 &&
                                i_lCQTrackKink[i] < 20;
	    bool fullID = 	i_lFlavor[i] == 1 &&
			            fabs(i_lEta[i]) < 2.4 &&
			            i_lPt[i] > 5 &&
			            //fabs(_dxy[i]) > 0.01 && for now, require this as a separate condition
                        i_lPOGLoose[i] &&
                        (   (goodglobalmuon &&
                             i_lMuonSegComp[i] > 0.303
                            )
                            ||
                            i_lMuonSegComp[i] > 0.451
                        );
        if(fullID) *(ID + i) = true;
	    else *(ID + i) = false;
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


bool Skimmer::ElectronTriggerSkim()
{
    if(i_is2017) return ElectronTriggerSkim2017();
    else if(i_is2018) return ElectronTriggerSkim2018();
    else return ElectronTriggerSkim2016();
}
bool Skimmer::ElectronTriggerSkim2016(){return i_HLT_Ele27_WPTight_Gsf;}
bool Skimmer::ElectronTriggerSkim2017(){return i_HLT_Ele32_WPTight_Gsf;}
bool Skimmer::ElectronTriggerSkim2018(){return i_HLT_Ele32_WPTight_Gsf;}


bool Skimmer::MuonTriggerSkim()
{
    if(i_is2017) return MuonTriggerSkim2017();
    else if(i_is2018) return MuonTriggerSkim2018();
    else return MuonTriggerSkim2016();
}
bool Skimmer::MuonTriggerSkim2016(){return (i_HLT_IsoMu24 or i_HLT_IsoTkMu24);}
bool Skimmer::MuonTriggerSkim2017(){return (i_HLT_IsoMu24 or i_HLT_IsoMu27 or i_HLT_IsoMu24_eta2p1);}
bool Skimmer::MuonTriggerSkim2018(){return (i_HLT_IsoMu24);}


bool Skimmer::singleleptonSkim(){
    get_TightelectronID(&TightelectronID[0]);
    get_TightmuonID(&TightmuonID[0]);

    get_clean_ele(&ele_cleaned_tight[0], &TightmuonID[0]);
    for(unsigned i = 0; i < i_nL; i++){
        ele_cleaned_both[i] = ele_cleaned_tight[i];
    }

    int Tightleptons = 0;
    for(unsigned i = 0; i < i_nL; i++){
        if(TightmuonID[i] or (TightelectronID[i] and ele_cleaned_both[i])) Tightleptons++;
    }
    return (Tightleptons >= 1);
}

bool Skimmer::dileptonSkim(){
    get_TightelectronID(&TightelectronID[0]);
    get_DisplelectronID(&DisplelectronID[0]);
    get_TightmuonID(&TightmuonID[0]);
    get_DisplmuonID(&DisplmuonID[0]);

    get_clean_ele(&ele_cleaned_tight[0], &TightmuonID[0]);
    get_clean_ele(&ele_cleaned_displ[0], &DisplmuonID[0]);
    for(unsigned i = 0; i < i_nL; i++){
        ele_cleaned_both[i] = ele_cleaned_tight[i] and ele_cleaned_displ[i];
    }

    int Tightleptons = 0;
    int Displleptons = 0;
    for(unsigned i = 0; i < i_nL; i++){
        if((TightmuonID[i] or (TightelectronID[i] and ele_cleaned_both[i])) and i_lPt[i] > 20) Tightleptons++;
        if((DisplmuonID[i] or (DisplelectronID[i] and ele_cleaned_both[i])) and i_lIVF_match[i]) Displleptons++;
    }
    return (Tightleptons >= 1 and Displleptons >= 1);
}


bool Skimmer::Check_SkimCondition(TString Condition)
{
    if(Condition == "2l2qSkim") return ((ElectronTriggerSkim() or MuonTriggerSkim()) and dileptonSkim());
    if(Condition == "Trigger") return singleleptonSkim();
    else return true;
}
