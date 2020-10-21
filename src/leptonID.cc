//////////////////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, code for determining lepton ID and pt ordering of leptons//
//////////////////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

bool full_analyzer::IsPromptMuonID(const unsigned i)
{
    if(_lFlavor[i] != 1)                            return false;
    if(fabs(_lEta[i]) >= 2.4)                       return false;
    if(_lPt[i] <= 20)                               return false;
    if(fabs(_dxy[i]) >= 0.05)                       return false;
    if(fabs(_dz[i]) >= 0.1)                         return false;
    if(_3dIPSig[i] >= 4)                            return false;
    if(_relIso[i] >= 0.1)                           return false;
    if(!_lPOGTight[i])                              return false;

    return true;
}

bool full_analyzer::IsPromptElectronID(const unsigned i)
{
    if(_lFlavor[i] != 0)                            return false;
    if(fabs(_lEta[i]) >= 2.5)                       return false;
    if(_lPt[i] <= 20)                               return false;
    if(fabs(_dxy[i]) >= 0.05)                       return false;
    if(fabs(_dz[i]) >= 0.1)                         return false;
    if(_3dIPSig[i] >= 4)                            return false;
    if(_relIso[i] >= 0.1)                           return false;
    if(_lElectronNumberInnerHitsMissing[i] >= 2)    return false;
    if(!_lElectronPassConvVeto[i])                  return false;
    if(!_lPOGTight[i])                              return false;

    return true;
}

//bool full_analyzer::IsPromptElectronID(const unsigned i)
//{
//    if(_lFlavor[i] != 0)                    return false;
//    if(fabs(_lEta[i]) > 2.5)                return false;
//    if(_lPt[i] < 7)                         return false;
//    if(fabs(_dxy[i]) > 0.05)                return false;
//    if(fabs(_dz[i])  > 0.1)                 return false;
//    if(_3dIPSig[i]   > 8)                   return false;
//    if(_miniIso[i]    > 0.4)                return false;
//    if(_leptonMvaTTH[i] < 0.8)              return false;
//    if(!_lElectronPassConvVeto[i])          return false;
//    if(_lElectronMissingHits[i] >= 1)       return false;
//    if(_lElectronHOverE[i] > 0.1)           return false;
//    if(_lElectronEInvMinusPInv[i] < -0.04)  return false;
//    if(!((fabs(_lEtaSC[i]) < 1.479 && _lElectronSigmaIetaIeta[i] < 0.011) || (fabs(_lEtaSC[i]) > 1.479 && _lElectronSigmaIetaIeta[i] < 0.030))) return false;
//    if(_is2016 and _closestJetDeepFlavor[i] > bTagWP::mediumDeepFlavor2016()) return false; //closestJetDeepFlavor is sum of closestJetDeepFlavor_b, _bb and _lepb
//    if(_is2017 and _closestJetDeepFlavor[i] > bTagWP::mediumDeepFlavor2017()) return false;
//    if(_is2018 and _closestJetDeepFlavor[i] > bTagWP::mediumDeepFlavor2018()) return false;
//    if(rawElectronMVA( _lElectronMvaFall17NoIso[i] ) < looseMVACut( i )) return false;
//
//    return true;
//}

double full_analyzer::rawElectronMVA( const double electronMVA ){
        return -0.5 * ( std::log( ( 1. - electronMVA ) / ( 1. + electronMVA ) ) );
}


unsigned full_analyzer::electronMVACategory( unsigned i ){
    double etasc = fabs(_lEtaSC[i]);
    if( _lPt[i] < 10 ){
        if( etasc < 0.8 ) return 0;
        else if( etasc < 1.479 ) return 1;
        else return 2;
    } else {
        if( etasc < 0.8 ) return 3;
        else if( etasc < 1.479 ) return 4;
        else return 5;
    }
}


double full_analyzer::looseMVACut( unsigned i ){
	unsigned category = electronMVACategory( i );
	if( category == 0 ) return 0.700642584415;
    else if( category == 1 ) return 0.739335420875;
    else if( category == 2 ) return 1.45390456109;
    else if( category == 3 ) return -0.146270871164;
    else if( category == 4 ) return -0.0315850882679;
    else return -0.0321841194737;
}


bool full_analyzer::IsLooseElectronID(const unsigned i)
{
    if(_lFlavor[i] != 0)            return false;
    if(fabs(_lEta[i]) > 2.5)        return false;
    if(_lPt[i] < 7)                 return false;
    if(!_lPOGLoose[i])              return false;
    if(!_lElectronPassConvVeto[i])  return false;

    return true;
}

bool full_analyzer::IsDisplacedElectronID(const unsigned i)  //basically medium POG cut-based ID without displacement interfering requirements
{
    if(_lFlavor[i] != 0)            return false;
    if(fabs(_lEta[i]) > 2.5)        return false;
    if(_lPt[i] < 7)                 return false;
    if(fabs(_dxy[i]) < 0.02)        return false;
    if(!_lElectronPassConvVeto[i])  return false;
    if(!( (_lElectronIsEB[i] &&
         _lElectronSigmaIetaIeta[i] <= 0.11 &&
         _lElectronDEtaInSeed[i] <= 0.00477 &&
         _lElectronDeltaPhiSuperClusterTrack[i] <= 0.222 &&
         _lElectronHOverE[i] <= 0.298 &&
         _lElectronEInvMinusPInv[i] <= 0.241)
        ||
        (_lElectronIsEE[i] &&
         _lElectronSigmaIetaIeta[i] <= 0.0314 &&
         _lElectronDEtaInSeed[i] <= 0.00868 &&
         _lElectronDeltaPhiSuperClusterTrack[i] <= 0.213 &&
         _lElectronHOverE[i] <= 0.101 &&
         _lElectronEInvMinusPInv[i] <= 0.14)
    )) return false;

    return true;
}

//bool full_analyzer::IsPromptMuonID(const unsigned i)
//{
//    if(_lFlavor[i] != 1)        return false;
//    if(fabs(_lEta[i]) > 2.4)    return false;
//    if(_lPt[i] < 5)             return false;
//    if(fabs(_dxy[i]) > 0.05)    return false;
//    if(fabs(_dz[i])  > 0.1)     return false;
//    if(_3dIPSig[i]   > 8)       return false;
//    if(_miniIso[i]    > 0.4)    return false;
//    if(_leptonMvaTTH[i] < 0.85) return false;
//    if(!_lPOGMedium[i])         return false;
//    if(_is2016 and _closestJetDeepFlavor[i] > bTagWP::mediumDeepFlavor2016()) return false;
//    if(_is2017 and _closestJetDeepFlavor[i] > bTagWP::mediumDeepFlavor2017()) return false;
//    if(_is2018 and _closestJetDeepFlavor[i] > bTagWP::mediumDeepFlavor2018()) return false;
//    // innertrack, PFmuon and global or tracker muon conditions are executed at ntuplizer level and not stored
//
//    return true;
//}


bool full_analyzer::IsLooseMuonID(const unsigned i)
{
    if(_lFlavor[i] != 1) return false;
    if(fabs(_lEta[i]) > 2.4) return false;
    if(_lPt[i] < 5) return false;
    if(!_lPOGLoose[i]) return false;

    return true;
}

bool full_analyzer::IsDisplacedMuonID(const unsigned i)
{
    bool goodglobalmuon =   _lGlobalMuon[i] &&
                            _lGlobalTrackNormalizedChi2[i] < 3 &&
                            _lCQChi2Position[i] < 12 &&
                            _lCQTrackKink[i] < 20;

    if(_lFlavor[i] != 1)                                return false;
    if(fabs(_lEta[i]) > 2.4)                            return false;
    if(_lPt[i] < 5)                                     return false;
    if(fabs(_dxy[i]) < 0.02)                            return false;
    if(!_lPOGLoose[i])                                  return false;
    if(_lMuonSegComp[i] < 0.303)                        return false;
    if(_lMuonSegComp[i] < 0.451 and !goodglobalmuon)    return false;

    return true;
}

bool full_analyzer::IsCleanElectron(const unsigned i, const std::vector<unsigned>& muoncollection)
{
    if(_lFlavor[i] != 0) return false;
	LorentzVector electron(_lPt[i], _lEta[i], _lPhi[i], _lE[i]);

    for(const auto& i_muon : muoncollection){
        LorentzVector muon(_lPt[i_muon], _lEta[i_muon], _lPhi[i_muon], _lE[i_muon]);

        if(deltaR(electron, muon) < 0.05) return false;
    }

    return true;
}

int full_analyzer::find_leading_lepton(const std::vector<unsigned>& leptoncollection)
{
    int index_leading = -1;

    for(const auto& index_lepton : leptoncollection){
        if(index_leading == -1) index_leading = (int)index_lepton;
        else if(_lPt[index_lepton] > _lPt[index_leading]) index_leading = (int)index_lepton;
    }

    return index_leading;
}

int full_analyzer::find_subleading_lepton(const std::vector<unsigned>& leptoncollection, const int index_leading)
{
    if(index_leading == -1) return -1;
    int index_subleading = -1;

    for(const auto& index_lepton : leptoncollection){
        if((int)index_lepton == index_leading) continue;

        if(index_subleading == -1) index_subleading = (int)index_lepton;
        else if(_lPt[index_lepton] > _lPt[index_subleading]) index_subleading = (int)index_lepton;
    }

    return index_subleading;
}

int full_analyzer::find_gen_lep(int i_lep)
{
    if(isData) return -1;
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
    if(isData) return -1;
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
    if(isData) return -1;
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

double full_analyzer::get_lsource(int i_gen_lep)
{
    if(i_gen_lep == -1) return -1;
    double mompdg = abs(_gen_lMomPdg[i_gen_lep])%10000;
    if(mompdg == 23) return 0;//Z
    else if(mompdg == 24) return 1;//W
    else if(mompdg == 6) return 2;//t
    else if((mompdg >= 500 and mompdg < 600) or (mompdg >= 5000 and mompdg < 6000) or mompdg == 5) return 3;//b
    else if((mompdg >= 400 and mompdg < 500) or (mompdg >= 4000 and mompdg < 5000) or mompdg == 4) return 4;//c
    else if((mompdg >= 100 and mompdg < 400) or (mompdg >= 1000 and mompdg < 4000) or mompdg == 1 or mompdg == 2 or mompdg == 3) return 5;//uds
    else if(mompdg == 21) return 6;//gluon
    else if(mompdg == 22) return 7;//photon
    else if(mompdg == 15) return 8;//tau
    else if(mompdg == 13) return 9;//mu
    else if(mompdg == 11) return 10;//e
    else if(mompdg == 12) return 11;//HNL
    else if(mompdg == 0) return -2;//unknown
    else {
        std::cout << "no category for lepton with mother: " << mompdg << std::endl;
        return -2;
    }
}

double full_analyzer::get_LSF(LSFReader& lsfreader_e, LSFReader& lsfreader_mu, LSFReader& lsfreader_mu_iso, int i){
    if(i == -1) return 1.;
    if(_lFlavor[i] == 0) return lsfreader_e.get_LSF(_lPt[i], _lEtaSC[i]);
    else if(_lFlavor[i] == 1) return lsfreader_mu.get_LSF(_lPt[i], _lEta[i])*lsfreader_mu_iso.get_LSF(_lPt[i], _lEta[i]);
    std::cout << "wrong lepton flavor, returning 1 for scale factor. flavor: " << _lFlavor[i] << std::endl;

    return 1.;
}
