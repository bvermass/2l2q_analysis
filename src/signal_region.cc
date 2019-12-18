///////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to Signal region definition//
///////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::signal_regions(){

    // NEW signal region method, sequential so that I can make histograms between each step if I want
    
    /////////////////////////////
    // Main signal region : ee //
    /////////////////////////////
    _trige                      = _HLT_Ele27_WPTight_Gsf;
    
    _1e                         = _trige &&
                                  i_leading_e != -1 && 
                                  leadptcut(i_leading_e);

    _1e1disple                  = _1e &&
                                  i_subleading_displ_e != -1;

    _1e1displevtx               = _1e1disple &&
                                  _lIVF_match[i_subleading_displ_e];

    _1e1displedispl             = _1e1displevtx &&
                                  fabs(_dxy[i_subleading_displ_e]) > 0.02;

    //_1e1disple0adde             = _1e1displedispl &&
    //                              no_additional_leptons();
    
    _1e1displejetl2             = _1e1displedispl &&
                                  i_closel2_jet != -1;
    
    _1e1displemll               = _1e1displejetl2 &&
                                  mllcut(i_leading_e, i_subleading_displ_e, 80);
    
    _1e1displedR                = _1e1displemll &&
                                  dRcut(i_leading_e, i_subleading_displ_e, 1, 5.5); 
    
    _1e1displedphi              = _1e1displemll &&
                                  dphicut(i_leading_e, i_subleading_displ_e, 2.3);

    _1e1displeReliso            = _1e1displedphi &&
                                  relisocut(i_subleading_displ_e, 1.5);
    
    _1e1disple1jet              = _1e1displeReliso &&
                                  i_subleading_jet == -1;

    _1e1displedphi_novtx        = _1e1disple &&
                                  fabs(_dxy[i_subleading_displ_e]) > 0.02 &&
                                  //no_additional_leptons() &&
                                  mllcut(i_leading_e, i_subleading_displ_e, 80) &&
                                  dphicut(i_leading_e, i_subleading_displ_e, 2.3);
    
    _1e1displedispl_Reliso      = _1e1displedispl &&
                                  relisocut(i_subleading_displ_e, 1.5);

    _CR_1e1displedphi           = _1e1displemll &&
                                  get_dphill(i_leading_e, i_subleading_displ_e) < 2.3;

    _CR_1e1displemll            = _1e1displejetl2 &&
                                  get_mll(i_leading_e, i_subleading_displ_e) > 80;
    

    ///////////////////////////////
    // Main signal region : mumu //
    ///////////////////////////////
    _trigmu                     = _HLT_IsoMu24 || _HLT_IsoTkMu24;
    
    _1mu                        = _trigmu &&
                                  i_leading_mu != -1 && 
                                  leadptcut(i_leading_mu);
    
    _1mu1displmu                = _1mu &&
                                  i_subleading_displ_mu != -1;
    
    _1mu1displmuvtx             = _1mu1displmu &&
                                  _lIVF_match[i_subleading_displ_mu];
    
    _1mu1displmudispl           = _1mu1displmuvtx &&
                                  fabs(_dxy[i_subleading_displ_mu]) > 0.02;

    //_1mu1displmu0addmu          = _1mu1displmudispl &&
    //                              no_additional_leptons();
    
    _1mu1displmujetl2           = _1mu1displmudispl &&
                                  i_closel2_jet != -1;

    _1mu1displmumll             = _1mu1displmujetl2 &&
                                  mllcut(i_leading_mu, i_subleading_displ_mu, 80);
    
    _1mu1displmudR              = _1mu1displmumll &&
                                  dRcut(i_leading_mu, i_subleading_displ_mu, 1, 5.5);    
    
    _1mu1displmudphi            = _1mu1displmumll &&
                                  dphicut(i_leading_mu, i_subleading_displ_mu, 2.3);
    
    _1mu1displmuReliso          = _1mu1displmudphi &&
                                  relisocut(i_subleading_displ_mu, 1.5);
    
    _1mu1displmu1jet            = _1mu1displmuReliso &&
                                  i_subleading_jet == -1;

    _1mu1displmudphi_novtx      = _1mu1displmu &&
                                  fabs(_dxy[i_subleading_displ_mu]) > 0.02 &&
                                  //no_additional_leptons() &&
                                  mllcut(i_leading_mu, i_subleading_displ_mu, 80) &&
                                  dphicut(i_leading_mu, i_subleading_displ_mu, 2.3);    
    
    _1mu1displmudispl_Reliso    = _1mu1displmudispl &&
                                  relisocut(i_subleading_displ_mu, 1.5);
    
    _CR_1mu1displmudphi         = _1mu1displmumll &&
                                  get_dphill(i_leading_mu, i_subleading_displ_mu) < 2.3;

    _CR_1mu1displmumll            = _1mu1displmujetl2 &&
                                  get_mll(i_leading_mu, i_subleading_displ_mu) > 80;
}


void full_analyzer::additional_signal_regions(){
    for(auto& MassMap : JetTagVal){
        for(auto& V2Map : MassMap.second){
            _1mu1displmu_PFN[MassMap.first][V2Map.first]            = _1mu1displmu1jet &&
                                                                      (V2Map.second > 0.98);

            _1mu1displmu_TrainingPFN[MassMap.first][V2Map.first]    = _1mu1displmudispl_Reliso &&
                                                                      (V2Map.second > 0.98);

            _1e1disple_PFN[MassMap.first][V2Map.first]              = _1e1disple1jet &&
                                                                      (V2Map.second > 0.98);

            _1e1disple_TrainingPFN[MassMap.first][V2Map.first]      = _1e1displedispl_Reliso &&
                                                                      (V2Map.second > 0.98);
        }
    }

    //_1mu1displmu_BDT            = _1mu1displmu1jet &&
    //                              (JetTagVal_BDT > 0.20);

    //_1mu1displmu_TrainingBDT    = _1mu1displmudispl_Reliso &&
    //                              (JetTagVal_BDT > 0.20);

    //_1e1disple_BDT              = _1e1disple1jet &&
    //                              (JetTagVal_BDT > 0.20);

    //_1e1disple_TrainingBDT      = _1e1displedispl_Reliso &&
    //                              (JetTagVal_BDT > 0.20);
}

 
bool full_analyzer::leadptcut(int i_lep){
    if(i_lep == -1){ cout << "giving value -1 as i_lep to full_analyzer::leadptcut" << endl; return false;}

    double ptcutval;
    if(_lFlavor[i_lep]      == 0) ptcutval = 30; //electron
    else if(_lFlavor[i_lep] == 1) ptcutval = 25; //muon
    
    if(_lPt[i_lep] >= ptcutval) return true;
    else return false;
}

bool full_analyzer::no_additional_leptons(){
    int loose_leptons = 0;
    for(unsigned i = 0; i < _nL; i++){
        if((displElectronID[i] and ele_clean_full_displ[i]) or (fullElectronID[i] and ele_clean_full_displ[i]) or looseMuonID[i] or fullMuonID[i]){ 
            loose_leptons++;
        }
    }
    return (loose_leptons == 2);
}


bool full_analyzer::mllcut(int i_lead, int i_sublead, double uppercut){
    return get_mll(i_lead, i_sublead) < uppercut;
}

double full_analyzer::get_mll(int i_lead, int i_sublead){
    LorentzVector leadingvec(_lPt[i_lead], _lEta[i_lead], _lPhi[i_lead], _lE[i_lead]);
    LorentzVector subleadingvec(_lPt[i_sublead], _lEta[i_sublead], _lPhi[i_sublead], _lE[i_sublead]);
    return (leadingvec + subleadingvec).mass();
}


bool full_analyzer::dRcut(int i_lead, int i_sublead, double lowercut, double uppercut){
    double dRll = get_dRll(i_lead, i_sublead);
    return (dRll > lowercut and dRll < uppercut);
}


double full_analyzer::get_dRll(int i_lead, int i_sublead){
    LorentzVector leadingvec(_lPt[i_lead], _lEta[i_lead], _lPhi[i_lead], _lE[i_lead]);
    LorentzVector subleadingvec(_lPt[i_sublead], _lEta[i_sublead], _lPhi[i_sublead], _lE[i_sublead]);
    return deltaR(leadingvec, subleadingvec);
}


bool full_analyzer::dphicut(int i_lead, int i_sublead, double lowercut){
    return (get_dphill(i_lead, i_sublead) > lowercut);
}

double full_analyzer::get_dphill(int i_lead, int i_sublead){
    LorentzVector leadingvec(_lPt[i_lead], _lEta[i_lead], _lPhi[i_lead], _lE[i_lead]);
    LorentzVector subleadingvec(_lPt[i_sublead], _lEta[i_sublead], _lPhi[i_sublead], _lE[i_sublead]);
    return deltaPhi(leadingvec, subleadingvec);
}

bool full_analyzer::relisocut(int i_sublead, double uppercut){
    return (_relIso[i_sublead] < uppercut);
}


