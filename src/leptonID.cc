//////////////////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, code for determining lepton ID and pt ordering of leptons//
//////////////////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::get_electronID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	    bool fullID =   _lFlavor[i] == 0 &&
			            fabs(_lEta[i]) < 2.5 &&
			            _lPt[i] > 7 &&
			            fabs(_dxy[i]) < 0.05 &&
			            fabs(_dz[i])  < 0.1 &&
			            _3dIPSig[i]   < 4 &&
			            _relIso[i]    < 0.1 &&
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
			            _relIso[i]    > 0.1 &&
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
                        _lPOGLoose[i] &&
			            _lElectronPassConvVeto[i];
	    if(fullID) *(ID + i) = true;
	    else *(ID + i) = false;
    }
}

void full_analyzer::get_new_displ_electronID(bool* ID)  //basically medium POG cut-based ID without displacement interfering requirements
{
    for(unsigned i = 0; i < _nL; i++){
        bool fullID =   _lFlavor[i] == 0 &&
                        fabs(_lEta[i]) < 2.5 &&
                        _lPt[i] > 7 &&
                        //fabs(_dxy[i]) > 0.05 &&
                        _lElectronPassConvVeto[i] &&
                        (   (_lEleIsEB[i] &&
                             _lElefull5x5SigmaIetaIeta[i] <= 0.11 &&
                             _lEleDEtaInSeed[i] <= 0.00477 &&
                             _lEleDeltaPhiSuperClusterTrackAtVtx[i] <= 0.222 &&
                             _lElehadronicOverEm[i] <= 0.298 &&
                             _lEleInvMinusPInv[i] <= 0.241) 
                            || 
                            (_lEleIsEE[i] &&
                             _lElefull5x5SigmaIetaIeta[i] <= 0.0314 &&
                             _lEleDEtaInSeed[i] <= 0.00868 &&
                             _lEleDeltaPhiSuperClusterTrackAtVtx[i] <= 0.213 &&
                             _lElehadronicOverEm[i] <= 0.101 &&
                             _lEleInvMinusPInv[i] <= 0.14
                            )
                        );
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
			            _relIso[i]    < 0.1 &&
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
			            _relIso[i]    > 0.1 &&
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
                        _lPOGLoose[i] &&
                        fabs(_lEta[i]) < 2.4 &&
			            _lPt[i] > 5;
			            //fabs(_dxy[i]) > 0.05;
	    if(fullID) *(ID + i) = true;
	    else *(ID + i) = false;
    }
}

void full_analyzer::get_new_displ_muonID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
        bool goodglobalmuon =   _lGlobalMuon[i] &&
                                _lGlobalTrackNormalizedChi2[i] < 3 &&
                                _lCQChi2Position[i] < 12 &&
                                _lCQTrackKink[i] < 20;
	    bool fullID = 	_lFlavor[i] == 1 &&
			            fabs(_lEta[i]) < 2.4 &&
			            _lPt[i] > 5 &&
			            //fabs(_dxy[i]) > 0.05 &&
                        _lPOGLoose[i] &&
                        (   (goodglobalmuon &&
                             _lMuonSegComp[i] > 0.303
                            )
                            ||
                            _lMuonSegComp[i] > 0.451
                        );
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
	    if(!*(electronID + i))      continue;
	    if(!*(ele_clean + i))       continue;
	    if(_lPt[i] < 7)             continue;
        if(_lPt[i] > _lPt[index_good_leading]) continue;
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
	    if(!*(muonID + i))          continue;
	    if(_lPt[i] < 5)             continue;
        if(_lPt[i] > _lPt[index_good_leading]) continue;
	    if(index_good_subleading == -1) index_good_subleading = i;
	    if(_lPt[i] > _lPt[index_good_subleading]) index_good_subleading = i;
    }
    return index_good_subleading;
}


int full_analyzer::find_gen_lep(int i_lep)
{
    TLorentzVector reco_vec;
    TLorentzVector gen_vec;
    double dR = 0.2;
    int i_gen = -1;
    if(i_lep != -1) {
        reco_vec.SetPtEtaPhiE(_lPt[i_lep], _lEta[i_lep], _lPhi[i_lep], _lE[i_lep]);
        for(int i = 0; i< _gen_nL; i++){
            gen_vec.SetPtEtaPhiE(_gen_lPt[i], _gen_lEta[i], _gen_lPhi[i], _gen_lE[i]);
            if(_lFlavor[i_lep] == _gen_lFlavor[i] && gen_vec.DeltaR(reco_vec) < dR){
                dR = gen_vec.DeltaR(reco_vec);
                i_gen = i;
            }
        }
    }
    return i_gen;
}

void full_analyzer::find_gen_l1_and_l2()
{
    int fromW = 0;
    int fromN = 0;
    for(int i = 0; i < _gen_nL; i++){
    	if(abs(_gen_lMomPdg[i]) == 24){ fromW++; i_gen_l1 = i; } // does not always find the lepton, sometimes its not found, very sometimes two are found
        if(fabs(_gen_lMomPdg[i]) == 9900012){ fromN++; i_gen_l2 = i; } //works perfectly
    }
    //if(fromW != 1) cout << "fromW: " << fromW << endl;
    //if(fromN != 1) cout << "fromN: " << fromN << endl;
    if(fromW != 1) i_gen_l1 = -1; 
    if(fromN != 1) i_gen_l2 = -1;
}

void full_analyzer::match_gen_and_reco(int i_subleading)
{
    //TLorentzVector gen_l1_vec;
    //TLorentzVector leading_vec;
    //gen_l1_vec.SetPtEtaPhiE(_gen_lPt[i_gen_l1], _gen_lEta[i_gen_l1], _gen_lPhi[i_gen_l1], _gen_lE[i_gen_l1]);
    //leading_vec.SetPtEtaPhiE(_lPt[i_leading], _lEta[i_leading], _lPhi[i_leading], _lE[i_leading]);
    //
    //leading_is_l1 = gen_l1_vec.DeltaR(leading_vec) < 0.2;
    
    TLorentzVector gen_l2_vec;
    TLorentzVector subleading_vec;
    if(i_gen_l2 != -1) gen_l2_vec.SetPtEtaPhiE(_gen_lPt[i_gen_l2], _gen_lEta[i_gen_l2], _gen_lPhi[i_gen_l2], _gen_lE[i_gen_l2]);
    else subleading_is_l2 = false;
    subleading_vec.SetPtEtaPhiE(_lPt[i_subleading], _lEta[i_subleading], _lPhi[i_subleading], _lE[i_subleading]);

    subleading_is_l2 = (gen_l2_vec.DeltaR(subleading_vec) < 0.2);
     
    //if(!subleading_is_l2) cout << "deta: " << fabs(_gen_lEta[i_gen_l2] - _lEta[i_subleading]) << " dphi: " << min(fabs(_gen_lPhi[i_gen_l2] - _lPhi[i_subleading]), 6.28 - fabs(_gen_lPhi[i_gen_l2] - _lPhi[i_subleading])) << " dpt: " << fabs(_gen_lPt[i_gen_l2] - _lPt[i_subleading]) << endl;
}

double full_analyzer::find_dRl2jet(TLorentzVector lepton){
    double dR = 6;
    for( unsigned i = 0; i < _nJets; i++){
        if(!(jet_clean_full_displ[i] && fullJetID[i])) continue;
        //cout << "   " << i << endl << endl << endl;
        TLorentzVector jet;
        jet.SetPtEtaPhiE(_jetPt[i], _jetEta[i], _jetPhi[i], _jetE[i]);
        if(lepton.DeltaR(jet) < dR) dR = lepton.DeltaR(jet);
    }
    return dR;
}

double full_analyzer::get_IVF_gendist(int i_gen_l, int i_vtx){
    return sqrt((_gen_vertex_x[i_gen_l] - _IVF_x[i_vtx])*(_gen_vertex_x[i_gen_l] - _IVF_x[i_vtx]) + (_gen_vertex_y[i_gen_l] - _IVF_y[i_vtx])*(_gen_vertex_y[i_gen_l] - _IVF_y[i_vtx]) + (_gen_vertex_z[i_gen_l] - _IVF_z[i_vtx])*(_gen_vertex_z[i_gen_l] - _IVF_z[i_vtx])); 
}

double full_analyzer::get_IVF_gendist_2D(int i_gen_l, int i_vtx){
    return sqrt((_gen_vertex_x[i_gen_l] - _IVF_x[i_vtx])*(_gen_vertex_x[i_gen_l] - _IVF_x[i_vtx]) + (_gen_vertex_y[i_gen_l] - _IVF_y[i_vtx])*(_gen_vertex_y[i_gen_l] - _IVF_y[i_vtx])); 
}

double full_analyzer::get_IVF_PVSVdist(int i_vtx){
    return sqrt((_PV_x - _IVF_x[i_vtx])*(_PV_x - _IVF_x[i_vtx]) + (_PV_y - _IVF_y[i_vtx])*(_PV_y - _IVF_y[i_vtx]) + (_PV_z - _IVF_z[i_vtx])*(_PV_z - _IVF_z[i_vtx])); 
}

double full_analyzer::get_IVF_PVSVdist_2D(int i_vtx){
    return sqrt((_PV_x - _IVF_x[i_vtx])*(_PV_x - _IVF_x[i_vtx]) + (_PV_y - _IVF_y[i_vtx])*(_PV_y - _IVF_y[i_vtx])); 
}

double full_analyzer::get_KVF_gendist(int i_gen_l, int i_lepton){
    return sqrt((_gen_vertex_x[i_gen_l] - _lKVF_x[i_lepton])*(_gen_vertex_x[i_gen_l] - _lKVF_x[i_lepton]) + (_gen_vertex_y[i_gen_l] - _lKVF_y[i_lepton])*(_gen_vertex_y[i_gen_l] - _lKVF_y[i_lepton]) + (_gen_vertex_z[i_gen_l] - _lKVF_z[i_lepton])*(_gen_vertex_z[i_gen_l] - _lKVF_z[i_lepton])); 
}

double full_analyzer::get_KVF_gendist_2D(int i_gen_l, int i_lepton){
    return sqrt((_gen_vertex_x[i_gen_l] - _lKVF_x[i_lepton])*(_gen_vertex_x[i_gen_l] - _lKVF_x[i_lepton]) + (_gen_vertex_y[i_gen_l] - _lKVF_y[i_lepton])*(_gen_vertex_y[i_gen_l] - _lKVF_y[i_lepton])); 
}

double full_analyzer::get_KVF_PVSVdist(int i_lepton){
    return sqrt((_PV_x - _lKVF_x[i_lepton])*(_PV_x - _lKVF_x[i_lepton]) + (_PV_y - _lKVF_y[i_lepton])*(_PV_y - _lKVF_y[i_lepton]) + (_PV_z - _lKVF_z[i_lepton])*(_PV_z - _lKVF_z[i_lepton])); 
}

double full_analyzer::get_KVF_PVSVdist_2D(int i_lepton){
    return sqrt((_PV_x - _lKVF_x[i_lepton])*(_PV_x - _lKVF_x[i_lepton]) + (_PV_y - _lKVF_y[i_lepton])*(_PV_y - _lKVF_y[i_lepton])); 
}

double full_analyzer::get_PVSVdist_gen(int i_gen_l){
    return sqrt((_gen_Nvertex_x - _gen_vertex_x[i_gen_l])*(_gen_Nvertex_x - _gen_vertex_x[i_gen_l]) + (_gen_Nvertex_y - _gen_vertex_y[i_gen_l])*(_gen_Nvertex_y - _gen_vertex_y[i_gen_l]) + (_gen_Nvertex_z - _gen_vertex_z[i_gen_l])*(_gen_Nvertex_z - _gen_vertex_z[i_gen_l]));
}

double full_analyzer::get_PVSVdist_gen_2D(int i_gen_l){
    return sqrt((_gen_Nvertex_x - _gen_vertex_x[i_gen_l])*(_gen_Nvertex_x - _gen_vertex_x[i_gen_l]) + (_gen_Nvertex_y - _gen_vertex_y[i_gen_l])*(_gen_Nvertex_y - _gen_vertex_y[i_gen_l]));
}
