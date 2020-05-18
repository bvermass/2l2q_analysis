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

    i_jetl2             = find_jet_closest_to_lepton(i_subleading); //finds jet within 0.7 of subleading lepton to be used as 'displaced jet'
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
    }
}


TString full_analyzer::get_signal_region_flavor(){
    TString signal_region_flavor = "";
    
    if(i_leading == -1 or i_subleading == -1) return signal_region_flavor;

    //if(_lCharge[i_leading] == _lCharge[i_subleading]) signal_region_flavor += "_SS";
    //else signal_region_flavor += "_OS";

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
    _trige                        = _passTrigger_ee or _passTrigger_e;
    _trigmu                       = _passTrigger_mm or _passTrigger_m;
    
    _l1                           = i_leading != -1 && 
                                    ((_trige && _lFlavor[i_leading] == 0) || (_trigmu && _lFlavor[i_leading] == 1)) &&
                                    leadptcut(i_leading);

    _l1l2                         = _l1 &&
                                    i_subleading != -1 &&
                                    _lFlavor[i_leading] == _lFlavor[i_subleading] &&
                                    _lCharge[i_leading] != _lCharge[i_subleading] &&
                                    subleadptcut(i_subleading);

    _l1l2_Full                    = _l1l2 &&
                                    mll > 80 &&
                                    mll < 100 &&
                                    (nLooseMu + nLooseEle) == 2 &&
                                    _passMETFilters;

    _l1l2_Full_noTrigger          = i_leading != -1 &&
                                    leadptcut(i_leading) &&
                                    i_subleading != -1 &&
                                    subleadptcut(i_subleading) &&
                                    _lFlavor[i_leading] == _lFlavor[i_subleading] &&
                                    _lCharge[i_leading] != _lCharge[i_subleading] &&
                                    mll > 80 &&
                                    mll < 100 &&
                                    (nLooseMu + nLooseEle) == 2 &&
                                    _passMETFilters;
}


bool full_analyzer::leadptcut(int i_lep){
    if(i_lep == -1){ cout << "giving value -1 as i_lep to full_analyzer::leadptcut" << endl; return false;}

    double ptcutval;
    if(_lFlavor[i_lep]      == 0) ptcutval = 25; //electron
    else if(_lFlavor[i_lep] == 1) ptcutval = 20; //muon

    if(_lPt[i_lep] >= ptcutval) return true;
    else return false;
}
 

bool full_analyzer::subleadptcut(int i_lep){
    if(i_lep == -1){ cout << "giving value -1 as i_lep to full_analyzer::subleadptcut" << endl; return false;}

    double ptcutval;
    if(_lFlavor[i_lep]      == 0) ptcutval = 20; //electron
    else if(_lFlavor[i_lep] == 1) ptcutval = 20; //muon

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
