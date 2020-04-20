///////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to Signal region definition//
///////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::set_leptons(int i_subleading_e, int i_subleading_mu){
    i_subleading = select_subleading_lepton(i_subleading_e, i_subleading_mu);

    sr_flavor = get_signal_region_flavor();
    sr_charge = sr_flavor(0,3);
    sr_lflavor = sr_flavor(3,3);

    set_relevant_lepton_variables();
}


void full_analyzer::set_relevant_lepton_variables(){

    i_jetl2 = find_jet_closest_to_lepton(&fullJetID[0], i_subleading); //finds jet within 0.7 of subleading lepton to be used as 'displaced jet'
    i_gen_leading       = find_gen_lep(i_leading);                //finds closest dR match
    i_gen_subleading    = find_gen_lep(i_subleading);
    i_gen_l1            = find_gen_l1();                                                   //finds HNL process l1 gen lepton
    i_gen_l2            = find_gen_l2();                                                   //finds HNL process l2 gen lepton
    leadingIsl1         = leptonIsGenLepton(i_leading, i_gen_l1);
    subleadingIsl2      = leptonIsGenLepton(i_subleading, i_gen_l2);


    if(i_leading != -1 and i_subleading != -1){
        mll = get_mll(i_leading, i_subleading);
        dRll = get_dRll(i_leading, i_subleading);
        dphill = get_dphill(i_leading, i_subleading);
        dRljet = get_dR_lepton_jet(i_subleading, i_jetl2);
        if(_lIVF_match[i_subleading]){
            LorentzVector tracksum(0,0,0,0);
            LorentzVector l1_vec(_lPt[i_leading], _lEta[i_leading], _lPhi[i_leading], _lE[i_leading]);
            LorentzVector l2_vec(_lPt[i_subleading], _lEta[i_subleading], _lPhi[i_subleading], _lE[i_subleading]);
            if(_IVF_ntracks[i_subleading] > 1){
                for(unsigned i_track = 0; i_track < _IVF_ntracks[i_subleading]; i_track++){
                    LorentzVector tmptrack(_IVF_trackpt[i_subleading][i_track], _IVF_tracketa[i_subleading][i_track], _IVF_trackphi[i_subleading][i_track], _IVF_trackE[i_subleading][i_track]);
                    tracksum += tmptrack;
                }
            }
            SVmass          = tracksum.mass();
            SVl1mass        = (tracksum + l1_vec).mass();
            SVmassminl2     = (tracksum - l2_vec).mass();
            SVpt            = tracksum.pt();
            SVeta           = tracksum.eta();
            SVphi           = tracksum.phi();
            IVF_PVSVdist_2D = get_IVF_PVSVdist_2D(i_subleading);
            IVF_PVSVdist    = get_IVF_PVSVdist(i_subleading);
            if(!isData){
                IVF_SVgenreco   = get_IVF_SVgenreco(i_gen_subleading, i_subleading);
                gen_PVSVdist_2D = get_PVSVdist_gen_2D(i_gen_subleading);
                gen_PVSVdist    = get_PVSVdist_gen(i_gen_subleading);
            }
        }
    }

    nTightEle = 0;
    nTightMu  = 0;
    nDisplEle = 0;
    nDisplMu  = 0;
    for(unsigned i = 0; i < _nL; i++){
        if(fullElectronID[i] and ele_clean_full_displ[i]) nTightEle++;
        else if(fullMuonID[i]) nTightMu++;
        else if(displElectronID[i] and ele_clean_full_displ[i]) nDisplEle++;
        else if(displMuonID[i]) nDisplMu++;
    }
    nTightJet = 0;
    for(unsigned i = 0; i < _nJets; i++){
        if(fullJetID[i] and jet_clean_full_displ[i]) nTightJet++;
    }
}


TString full_analyzer::get_signal_region_flavor(){
    TString signal_region_flavor = "";
    
    if(i_leading == -1 or i_subleading == -1) return signal_region_flavor;

    if(_lCharge[i_leading] == _lCharge[i_subleading]) signal_region_flavor += "_SS";
    else signal_region_flavor += "_OS";

    if(_lFlavor[i_leading] == 0) signal_region_flavor += "_e";
    else if(_lFlavor[i_leading] == 1) signal_region_flavor += "_m";

    if(_lFlavor[i_subleading] == 0) signal_region_flavor += "e";
    else if(_lFlavor[i_subleading] == 1) signal_region_flavor += "m";

    return signal_region_flavor;
}

int full_analyzer::select_subleading_lepton(int i_subleading_e, int i_subleading_mu){
    if(i_subleading_mu == -1){
        return i_subleading_e;
    }else if(i_subleading_e == -1){
        return i_subleading_mu;
    }else if(i_subleading_e != -1 and i_subleading_mu != -1){
        if(_lPt[i_subleading_e] > _lPt[i_subleading_mu]) return i_subleading_e;
        else return i_subleading_mu;
    }else {
        return -1;
    }
}


int full_analyzer::select_leading_lepton(int i_leading_e, int i_leading_mu){
    if(i_leading_mu == -1){
        return i_leading_e;
    }else if(i_leading_e == -1){
        return i_leading_mu;
    }else if(i_leading_e != -1 and i_leading_mu != -1){
        if(_lPt[i_leading_e] > _lPt[i_leading_mu]) return i_leading_e;
        else return i_leading_mu;
    }else {
        return -1;
    }
}


void full_analyzer::signal_regions(){

    //signal region method: sequential booleans so that I can make histograms between each step if I want
    if(_is2016){
        _trige                  = _HLT_Ele27_WPTight_Gsf;
        _trigmu                 = _HLT_IsoMu24 || _HLT_IsoTkMu24;
    }else if(_is2017 or _is2018){
        _trige                  = _HLT_Ele32_WPTight_Gsf;
        _trigmu                 = _HLT_IsoMu24;
    }
    
     _l1                        = i_leading != -1 &&
                                  ((_trige && _lFlavor[i_leading] == 0) || (_trigmu && _lFlavor[i_leading] == 1)) &&
                                  leadptcut(i_leading);

     _l1l2                      = _l1 &&
                                  i_subleading != -1;
                                  //fabs(_dxy[i_subleading]) > 0.02;

     _l1l2SV                    = _l1l2 &&
                                  _lIVF_match[i_subleading];

     _Training                  = _l1l2SV &&
                                  i_jetl2 != -1;
                                  //_relIso[i_subleading] < 1.5;//to remove?

     _FullNoPFN                 = _Training &&
                                  mll < 80 &&
                                  dphill > 2.3 &&
                                  i_subleading_jet == -1 &&
                                  (nTightEle + nTightMu == 1);

     _FullNoPFN_toofar          = _FullNoPFN &&
                                  IVF_PVSVdist_2D > 40;

     _CR_FullNoPFN_invdphi      = _Training &&
                                  mll < 80 &&
                                  dphill < 2.3 &&
                                  i_subleading_jet == -1 &&
                                  (nTightEle + nTightMu == 1);

     _CR_FullNoPFN_invmll       = _Training &&
                                  mll > 80 &&
                                  dphill > 2.3 &&
                                  i_subleading_jet == -1 &&
                                  (nTightEle + nTightMu == 1);

     //questions: no additional leptons?
     //mll?
     //dR (dphi)?
}


void full_analyzer::additional_signal_regions(){
    for(auto& MassMap : JetTagVal){
        for(auto& V2Map : MassMap.second){
            _TrainingHighPFN[MassMap.first][V2Map.first]            = _Training &&
                                                               (V2Map.second > 0.98);

            _Full[MassMap.first][V2Map.first]                = _FullNoPFN &&
                                                               (V2Map.second > 0.98);

            _CR_Full_invdphi[MassMap.first][V2Map.first]     = _CR_FullNoPFN_invdphi &&
                                                               (V2Map.second > 0.98);

            _CR_Full_invmll[MassMap.first][V2Map.first]      = _CR_FullNoPFN_invmll &&
                                                               (V2Map.second > 0.98);
        }
    }

    //_afterBDT             = _Training &&
    //                        (JetTagVal_BDT > 0.20);

    //_FullBDT              = _FullNoPFN &&
    //                        (JetTagVal_BDT > 0.20);
}

 
bool full_analyzer::leadptcut(int i_lep){
    if(i_lep == -1){ cout << "giving value -1 as i_lep to full_analyzer::leadptcut" << endl; return false;}

    double ptcutval;
    if(_lFlavor[i_lep]      == 0 and _is2016) ptcutval = 30; //electron
    else if(_lFlavor[i_lep] == 0) ptcutval = 34;
    else if(_lFlavor[i_lep] == 1) ptcutval = 25; //muon
    
    if(_lPt[i_lep] >= ptcutval) return true;
    else return false;
}

double full_analyzer::get_mll(int i_lead, int i_sublead){
    LorentzVector leadingvec(_lPt[i_lead], _lEta[i_lead], _lPhi[i_lead], _lE[i_lead]);
    LorentzVector subleadingvec(_lPt[i_sublead], _lEta[i_sublead], _lPhi[i_sublead], _lE[i_sublead]);
    return (leadingvec + subleadingvec).mass();
}


double full_analyzer::get_dRll(int i_lead, int i_sublead){
    LorentzVector leadingvec(_lPt[i_lead], _lEta[i_lead], _lPhi[i_lead], _lE[i_lead]);
    LorentzVector subleadingvec(_lPt[i_sublead], _lEta[i_sublead], _lPhi[i_sublead], _lE[i_sublead]);
    return deltaR(leadingvec, subleadingvec);
}


double full_analyzer::get_dphill(int i_lead, int i_sublead){
    LorentzVector leadingvec(_lPt[i_lead], _lEta[i_lead], _lPhi[i_lead], _lE[i_lead]);
    LorentzVector subleadingvec(_lPt[i_sublead], _lEta[i_sublead], _lPhi[i_sublead], _lE[i_sublead]);
    return deltaPhi(leadingvec, subleadingvec);
}
