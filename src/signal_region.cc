///////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to Signal region definition//
///////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::set_leptons(const TString JetPt_Version){
    sr_flavor = get_signal_region_flavor();
    sr_charge = sr_flavor(0,3);
    sr_lflavor = sr_flavor(3,3);

    set_relevant_lepton_variables(JetPt_Version);
}


void full_analyzer::set_relevant_lepton_variables(const TString JetPt_Version){

    i_jetl2             = find_jet_closest_to_lepton(i_subleading, JetPt_Version); //finds jet within 0.7 of subleading lepton to be used as 'displaced jet'
    i_gen_leading       = find_gen_lep(i_leading);                //finds closest dR match
    i_gen_subleading    = find_gen_lep(i_subleading);
    i_gen_l1            = find_gen_l1();                                                   //finds HNL process l1 gen lepton
    i_gen_l2            = find_gen_l2();                                                   //finds HNL process l2 gen lepton
    leadingIsl1         = leptonIsGenLepton(i_leading, i_gen_l1);
    subleadingIsl2      = leptonIsGenLepton(i_subleading, i_gen_l2);
    l1hasreco           = gen_l_has_reco(i_gen_l1);
    l2hasreco           = gen_l_has_reco(i_gen_l2);


    if(i_leading != -1 and i_subleading != -1){
        mll = get_mll(i_leading, i_subleading);
        dRll = get_dRll(i_leading, i_subleading);
        dphill = get_dphill(i_leading, i_subleading);
        dRljet = get_dR_lepton_jet(i_subleading, i_jetl2);
        if(_lIVF_match[i_subleading]){
            LorentzVector tracksum(0,0,0,0);
            LorentzVector l1_vec(_lPt[i_leading], _lEta[i_leading], _lPhi[i_leading], _lE[i_leading]);
            LorentzVector l2_vec(_lPt[i_subleading], _lEta[i_subleading], _lPhi[i_subleading], _lE[i_subleading]);
            LorentzVector PVSV_vec;
            PVSV_vec.setCartesianCoords(_IVF_x[i_subleading] - _PV_x, _IVF_y[i_subleading] - _PV_y, _IVF_z[i_subleading] - _PV_z, 0);
            i_subleading_track = 0;
            double mindR = 0.6;
            if(_IVF_ntracks[i_subleading] > 1){
                for(unsigned i_track = 0; i_track < _IVF_ntracks[i_subleading]; i_track++){
                    LorentzVector tmptrack(_IVF_trackpt[i_subleading][i_track], _IVF_tracketa[i_subleading][i_track], _IVF_trackphi[i_subleading][i_track], _IVF_trackE[i_subleading][i_track]);
                    tracksum += tmptrack;

                    if(deltaR(tmptrack, l2_vec) < mindR){
                        i_subleading_track = i_track;
                        mindR = deltaR(tmptrack, l2_vec);
                    }
                }
                double highest_trackpt = -1;
                highest_trackpt_weight = 1.;
                for(unsigned i_track = 0; i_track < _IVF_ntracks[i_subleading]; i_track++){
                    if(i_subleading_track == i_track) continue;
                    if(_IVF_trackpt[i_subleading][i_track] > highest_trackpt){
                        highest_trackpt_weight = sqrt(lsfreader_displ_m_SV->get_LSF(_IVF_trackpt[i_subleading][i_track]*2, IVF_PVSVdist_2D));
                        highest_trackpt = _IVF_trackpt[i_subleading][i_track];
                    }
                }
            }
            SVmass          = tracksum.mass();
            SVl1mass        = (tracksum + l1_vec).mass();
            SVmassminl2     = (tracksum - l2_vec).mass();
            SVpt            = tracksum.pt();
            SVeta           = tracksum.eta();
            SVphi           = tracksum.phi();
            IVF_costracks   = cosine3D(tracksum, PVSV_vec);
            IVF_PVSVdist_2D = get_IVF_PVSVdist_2D(i_subleading);
            IVF_PVSVdist    = get_IVF_PVSVdist(i_subleading);
            if(!isData){
                IVF_SVgenreco   = get_IVF_SVgenreco(i_gen_subleading, i_subleading);
                gen_PVSVdist_2D = get_PVSVdist_gen_2D(i_gen_subleading);
                gen_PVSVdist    = get_PVSVdist_gen(i_gen_subleading);
                PVNvtxdist = get_PVNvtxdist();
            }
        }
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

int full_analyzer::select_subleading_lepton_withSV(std::vector<unsigned> displacedElectronID, std::vector<unsigned> displacedMuonID){
    //step 1: keep leptons with an SV
    std::vector<unsigned> l2_withSV;
    for(const auto& i_ele : displacedElectronID){
        if(_lIVF_match[i_ele] and _lPt[i_ele] + 5 < _lPt[i_leading]) l2_withSV.push_back(i_ele);
    }
    for(const auto& i_mu : displacedMuonID){
        if(_lIVF_match[i_mu] and _lPt[i_mu] < _lPt[i_leading]) l2_withSV.push_back(i_mu);
    }
    if(l2_withSV.size() == 0) return -1;

    //step 2: select lepton with highest SV pt (sum of track pts)
    unsigned i_l2_SVpt = l2_withSV.front();
    for(const auto& i_l : l2_withSV){
        if(_IVF_pt[i_l] > _IVF_pt[i_l2_SVpt]){
            i_l2_SVpt = i_l;
        }
    }

    return i_l2_SVpt;
}
int full_analyzer::select_subleading_lepton_highestpt(std::vector<unsigned> displacedElectronID, std::vector<unsigned> displacedMuonID){
	int i_subleading_e  	    = find_subleading_lepton(displacedElectronID, i_leading);
	int i_subleading_mu 	    = find_subleading_lepton(displacedMuonID, i_leading);

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


int full_analyzer::select_leading_lepton(std::vector<unsigned> promptElectronID, std::vector<unsigned> promptMuonID){
	int i_leading_e     		    = find_leading_lepton(promptElectronID);
	int i_leading_mu    		    = find_leading_lepton(promptMuonID);

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

    //genOverlap is true if event has to be removed. Goal is to get external conversions from ZG and WG, but internal conversions from WJets and DY
    _genOverlap                 = (isDY and _zgEventType >= 3) or
                                  (isZG and _hasInternalConversion) or
                                  (isWJets and _zgEventType >= 3) or
                                  (isWG and _hasInternalConversion);

    //signal region method: sequential booleans so that I can make histograms between each step if I want
    if(_is2016){
        _trige                  = _HLT_Ele27_WPTight_Gsf;
        _trigmu                 = _HLT_IsoMu24 || _HLT_IsoTkMu24;
    }else if(_is2018){
        _trige                  = _HLT_Ele32_WPTight_Gsf;
        _trigmu                 = _HLT_IsoMu24;
    }else if(_is2017){
        _trige                  = _HLT_Ele32_WPTight_Gsf;
        _trigmu                 = _HLT_IsoMu24 || _HLT_IsoMu27 || _HLT_IsoMu24_eta2p1;
    }else{
        std::cout << "signal_regions.cc: did not correctly register data taking year!" << std::endl;
        _trige                  = false;
        _trigmu                 = false;
    }
    
     _l1                        = i_leading != -1 &&
                                  ((_trige && _lFlavor[i_leading] == 0) || (_trigmu && _lFlavor[i_leading] == 1)) &&
                                  leadptcut(i_leading) &&
                                  !_genOverlap;

     _l1l2                      = _l1 &&
                                  i_subleading != -1;
                                  //fabs(_dxy[i_subleading]) > 0.02;

     _l1l2SV                    = _l1l2 &&
                                  _lIVF_match[i_subleading];

     _bkgestimator              = _l1l2SV &&
                                  i_jetl2 != -1 &&
                                  (nTightEle + nTightMu == 1) &&
                                  dphill > 0.4 &&
                                  mll > 10 &&
                                  IVF_PVSVdist_2D < 50;

     _Training                  = _l1l2SV &&
                                  i_jetl2 != -1 &&
                                  nTightJet <= 1 &&
                                  (nTightEle + nTightMu == 1) &&
                                  dphill > 0.4 &&
                                  mll > 10 &&
                                  IVF_PVSVdist_2D < 50;
                                  //_relIso[i_subleading] < 1.5;//to remove?

     _Training2Jets             = _l1l2SV &&
                                  i_jetl2 != -1 &&
                                  nTightJet > 1 &&
                                  (nTightEle + nTightMu == 1) &&
                                  dphill > 0.4 &&
                                  mll > 10 &&
                                  IVF_PVSVdist_2D < 50;

     _Training2JetsNoZ          = _l1l2SV &&
                                  i_jetl2 != -1 &&
                                  nTightJet > 1 &&
                                  (nTightEle + nTightMu == 1) &&
                                  dphill > 0.4 &&
                                  (mll > 100 || mll < 80) &&
                                  mll > 10 &&
                                  IVF_PVSVdist_2D < 50;

     _FullNoPFN                 = _Training &&
                                  mll < 80 &&
                                  dphill > 2.3;
                                  //i_subleading_jet == -1 &&
                                  //(nTightEle + nTightMu == 1);

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
