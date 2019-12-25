//////////////////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, code for determining lepton ID and pt ordering of leptons//
//////////////////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::get_electronID()
{
    for(unsigned i = 0; i < _nL; ++i){
	    fullElectronID[i] = _lFlavor[i] == 0 &&
			                fabs(_lEta[i]) < 2.5 &&
			                _lPt[i] > 7 &&
			                fabs(_dxy[i]) < 0.05 &&
			                fabs(_dz[i])  < 0.1 &&
			                _3dIPSig[i]   < 8 &&
			                _miniIso[i]    < 0.4 &&
			                _leptonMvaTTH[i] > 0.8 && //move to MVA of TTH as soon as others caught up
			                _lElectronPassConvVeto[i] &&
			                _lElectronMissingHits[i] < 1;
    }
}

//void full_analyzer::get_electronID(bool* ID)
//{
//    for(unsigned i = 0; i < _nL; ++i){
//	    bool fullID =   _lFlavor[i] == 0 &&
//			            fabs(_lEta[i]) < 2.5 &&
//			            _lPt[i] > 7 &&
//			            fabs(_dxy[i]) < 0.05 &&
//			            fabs(_dz[i])  < 0.1 &&
//			            _3dIPSig[i]   < 4 &&
//			            _relIso[i]    < 0.1 &&
//			            _lPOGTight[i] && //move to MVA of TTH as soon as others caught up
//			            _lElectronPassConvVeto[i] &&
//			            _lElectronMissingHits[i] < 1;
//	    if(fullID) *(ID + i) = true;
//	    else *(ID + i) = false;
//    }
//}

void full_analyzer::get_loose_electronID()
{
    for(unsigned i = 0; i < _nL; ++i){
	    looseElectronID[i] = _lFlavor[i] == 0 &&
                             fabs(_lEta[i]) < 2.5 &&
                             _lPt[i] > 7 &&
                             //fabs(_dxy[i]) < 0.05 &&
                             //fabs(_dz[i])  < 0.1 &&
                             //_3dIPSig[i]   < 4 &&
                             //_relIso[i]    < 0.1 &&
                             _lPOGLoose[i] &&
                             _lElectronPassConvVeto[i];
                             //_lElectronMissingHits[i] < 1;
    }
}

void full_analyzer::get_displ_electronID()  //basically medium POG cut-based ID without displacement interfering requirements
{
    for(unsigned i = 0; i < _nL; i++){
        displElectronID[i] = _lFlavor[i] == 0 &&
                             fabs(_lEta[i]) < 2.5 &&
                             _lPt[i] > 7 &&
                             //fabs(_dxy[i]) > 0.01 && for now, require this as a separate condition
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
    }
}

void full_analyzer::get_muonID()
{
    for(unsigned i = 0; i < _nL; ++i){
	    fullMuonID[i] = _lFlavor[i] == 1 &&
			            fabs(_lEta[i]) < 2.4 &&
			            _lPt[i] > 5 &&
			            fabs(_dxy[i]) < 0.05 &&
			            fabs(_dz[i])  < 0.1 &&
			            _3dIPSig[i]   < 8 &&
			            _miniIso[i]    < 0.4 &&
                        _leptonMvaTTH[i] > 0.8; //move to MVA of TTH as soon as others caught up
			            // innertrack, PFmuon and global or tracker muon conditions are executed at ntuplizer level and not stored
    }
}

//void full_analyzer::get_muonID(bool* ID)
//{
//    for(unsigned i = 0; i < _nL; ++i){
//	    bool fullID = 	_lFlavor[i] == 1 &&
//			            fabs(_lEta[i]) < 2.4 &&
//			            _lPt[i] > 5 &&
//			            fabs(_dxy[i]) < 0.05 &&
//			            fabs(_dz[i])  < 0.1 &&
//			            _3dIPSig[i]   < 4 &&
//			            _relIso[i]    < 0.1 &&
//                        _lPOGTight[i]; //move to MVA of TTH as soon as others caught up
//			            // innertrack, PFmuon and global or tracker muon conditions are executed at ntuplizer level and not stored
//	    if(fullID) *(ID + i) = true;
//	    else *(ID + i) = false;
//    }
//}

void full_analyzer::get_loose_muonID()
{
    for(unsigned i = 0; i < _nL; ++i){
	    looseMuonID[i] = _lFlavor[i] == 1 &&
                         fabs(_lEta[i]) < 2.4 &&
                         _lPt[i] > 5 &&
                         //fabs(_dxy[i]) < 0.05 &&
                         //fabs(_dz[i])  < 0.1 &&
                         //_3dIPSig[i]   < 4 &&
                         //_relIso[i]    < 0.1 &&
                         _lPOGLoose[i];
                         // innertrack, PFmuon and global or tracker muon conditions are executed at ntuplizer level and not stored
    }
}

void full_analyzer::get_displ_muonID()
{
    for(unsigned i = 0; i < _nL; ++i){
        bool goodglobalmuon =   _lGlobalMuon[i] &&
                                _lGlobalTrackNormalizedChi2[i] < 3 &&
                                _lCQChi2Position[i] < 12 &&
                                _lCQTrackKink[i] < 20;
	    displMuonID[i] = _lFlavor[i] == 1 &&
			             fabs(_lEta[i]) < 2.4 &&
			             _lPt[i] > 5 &&
			             //fabs(_dxy[i]) > 0.01 && for now, require this as a separate condition
                         _lPOGLoose[i] &&
                         (   (goodglobalmuon &&
                              _lMuonSegComp[i] > 0.303
                             )
                             ||
                             _lMuonSegComp[i] > 0.451
                         );
    }
}




void full_analyzer::get_clean_ele(bool* cleaned, bool* muonID)
{
    // The array cleaned will contain value true when the electron is not within dR < 0.05 around a muon
    for(unsigned i_el = 0; i_el < _nL; ++i_el){
	    *(cleaned + i_el) = true;
	    if(_lFlavor[i_el] != 0) continue;
	    LorentzVector electron(_lPt[i_el], _lEta[i_el], _lPhi[i_el], _lE[i_el]);

	    for(unsigned i_mu = 0; i_mu < _nL; ++i_mu){
	        if(_lFlavor[i_mu] == 1 && *(muonID + i_mu)){
                LorentzVector muon(_lPt[i_mu], _lEta[i_mu], _lPhi[i_mu], _lE[i_mu]);
                if(deltaR(electron, muon) < 0.05) *(cleaned + i_el) = false;
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
    for(unsigned i = 0; i < _nL; ++i){
	    if((int)i == index_good_leading) continue;
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
    for(unsigned i = 0; i < _nL; ++i){
	    if((int)i == index_good_leading) continue;
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
    if(sampleflavor.Index("Run") != -1) return -1;
    double dR = 0.3;
    int i_gen = -1;
    if(i_lep != -1) {
        LorentzVector reco_vec(_lPt[i_lep], _lEta[i_lep], _lPhi[i_lep], _lE[i_lep]);
        for(unsigned i = 0; i< _gen_nL; i++){
            LorentzVector gen_vec(_gen_lPt[i], _gen_lEta[i], _gen_lPhi[i], _gen_lE[i]);
            if(_lFlavor[i_lep] == _gen_lFlavor[i] && deltaR(gen_vec, reco_vec) < dR){
                dR = deltaR(gen_vec, reco_vec);
                i_gen = i;
            }
        }
    }
    return i_gen;
}

int full_analyzer::find_gen_l1()
{
    if(sampleflavor.Index("Run") != -1) return -1;
    int fromW = 0;
    int i_found = -1;
    for(unsigned i = 0; i < _gen_nL; i++){
    	if(abs(_gen_lMomPdg[i]) == 24){ 
            fromW++; 
            i_found = i; 
        } // does not always find the lepton, sometimes its not found, very sometimes two are found
    }
    if(fromW != 1) i_found = -1; 
    return i_found;
}

int full_analyzer::find_gen_l2()
{
    if(sampleflavor.Index("Run") != -1) return -1;
    int fromN = 0;
    int i_found = -1;
    for(unsigned i = 0; i < _gen_nL; i++){
        if(fabs(_gen_lMomPdg[i]) == 9900012){ 
            fromN++; 
            i_found = i; 
        } //works perfectly to find l2
    }
    if(fromN != 1) i_found = -1;
    return i_found;
}

bool full_analyzer::leptonIsGenLepton(int i_lep, int i_gen_lep)
{
    if(i_gen_lep == -1 or i_lep == -1) return false;
    double dR = get_dR(_lEta[i_lep], _lPhi[i_lep], _gen_lEta[i_gen_lep], _gen_lPhi[i_gen_lep]);
    double deta = fabs(_lEta[i_lep] - _gen_lEta[i_gen_lep]);
    if(dR < 0.03 or (dR < 0.1 and deta < 0.03)) return true;
    else return false;
}

double full_analyzer::get_IVF_SVgenreco(int i_gen_l, int i_lepton){
    if(i_gen_l == -1 or i_lepton == -1) return -1; 
    return sqrt((_gen_vertex_x[i_gen_l] - _IVF_x[i_lepton])*(_gen_vertex_x[i_gen_l] - _IVF_x[i_lepton]) + (_gen_vertex_y[i_gen_l] - _IVF_y[i_lepton])*(_gen_vertex_y[i_gen_l] - _IVF_y[i_lepton]) + (_gen_vertex_z[i_gen_l] - _IVF_z[i_lepton])*(_gen_vertex_z[i_gen_l] - _IVF_z[i_lepton])); 
}

double full_analyzer::get_IVF_SVgenreco_2D(int i_gen_l, int i_lepton){
    if(i_gen_l == -1 or i_lepton == -1) return -1; 
    return sqrt((_gen_vertex_x[i_gen_l] - _IVF_x[i_lepton])*(_gen_vertex_x[i_gen_l] - _IVF_x[i_lepton]) + (_gen_vertex_y[i_gen_l] - _IVF_y[i_lepton])*(_gen_vertex_y[i_gen_l] - _IVF_y[i_lepton])); 
}

double full_analyzer::get_IVF_PVSVdist(int i_lepton){
    if(i_lepton == -1) return -1; 
    return sqrt((_PV_x - _IVF_x[i_lepton])*(_PV_x - _IVF_x[i_lepton]) + (_PV_y - _IVF_y[i_lepton])*(_PV_y - _IVF_y[i_lepton]) + (_PV_z - _IVF_z[i_lepton])*(_PV_z - _IVF_z[i_lepton])); 
}

double full_analyzer::get_IVF_PVSVdist_2D(int i_lepton){
    if(i_lepton == -1) return -1; 
    return sqrt((_PV_x - _IVF_x[i_lepton])*(_PV_x - _IVF_x[i_lepton]) + (_PV_y - _IVF_y[i_lepton])*(_PV_y - _IVF_y[i_lepton])); 
}

double full_analyzer::get_KVF_SVgenreco(int i_gen_l, int i_lepton){
    if(i_gen_l == -1 or i_lepton == -1) return -1; 
    return sqrt((_gen_vertex_x[i_gen_l] - _lKVF_x[i_lepton])*(_gen_vertex_x[i_gen_l] - _lKVF_x[i_lepton]) + (_gen_vertex_y[i_gen_l] - _lKVF_y[i_lepton])*(_gen_vertex_y[i_gen_l] - _lKVF_y[i_lepton]) + (_gen_vertex_z[i_gen_l] - _lKVF_z[i_lepton])*(_gen_vertex_z[i_gen_l] - _lKVF_z[i_lepton])); 
}

double full_analyzer::get_KVF_SVgenreco_2D(int i_gen_l, int i_lepton){
    if(i_gen_l == -1 or i_lepton == -1) return -1; 
    return sqrt((_gen_vertex_x[i_gen_l] - _lKVF_x[i_lepton])*(_gen_vertex_x[i_gen_l] - _lKVF_x[i_lepton]) + (_gen_vertex_y[i_gen_l] - _lKVF_y[i_lepton])*(_gen_vertex_y[i_gen_l] - _lKVF_y[i_lepton])); 
}

double full_analyzer::get_KVF_PVSVdist(int i_lepton){
    if(i_lepton == -1) return -1; 
    return sqrt((_PV_x - _lKVF_x[i_lepton])*(_PV_x - _lKVF_x[i_lepton]) + (_PV_y - _lKVF_y[i_lepton])*(_PV_y - _lKVF_y[i_lepton]) + (_PV_z - _lKVF_z[i_lepton])*(_PV_z - _lKVF_z[i_lepton])); 
}

double full_analyzer::get_KVF_PVSVdist_2D(int i_lepton){
    if(i_lepton == -1) return -1; 
    return sqrt((_PV_x - _lKVF_x[i_lepton])*(_PV_x - _lKVF_x[i_lepton]) + (_PV_y - _lKVF_y[i_lepton])*(_PV_y - _lKVF_y[i_lepton])); 
}

double full_analyzer::get_PVSVdist_gen(int i_gen_l){
    if(i_gen_l == -1) return -1; 
    return sqrt((_gen_Nvertex_x - _gen_vertex_x[i_gen_l])*(_gen_Nvertex_x - _gen_vertex_x[i_gen_l]) + (_gen_Nvertex_y - _gen_vertex_y[i_gen_l])*(_gen_Nvertex_y - _gen_vertex_y[i_gen_l]) + (_gen_Nvertex_z - _gen_vertex_z[i_gen_l])*(_gen_Nvertex_z - _gen_vertex_z[i_gen_l]));
}

double full_analyzer::get_PVSVdist_gen_2D(int i_gen_l){
    if(i_gen_l == -1) return -1; 
    return sqrt((_gen_Nvertex_x - _gen_vertex_x[i_gen_l])*(_gen_Nvertex_x - _gen_vertex_x[i_gen_l]) + (_gen_Nvertex_y - _gen_vertex_y[i_gen_l])*(_gen_Nvertex_y - _gen_vertex_y[i_gen_l]));
}
