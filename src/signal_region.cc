///////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to Signal region definition//
///////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::signal_regions(){

    
    // NEW signal region method, sequential so that I can make histograms between each step if I want
    // others should be adapted to this method, do this NEXT WEEK WITH TIER2 DOWN
    
    /////////////////////////////
    // Main signal region : ee //
    /////////////////////////////
    _trige                      = _HLT_Ele27_WPTight_Gsf;
    
    _1e			                = _trige && 
                                  i_leading_e != -1 && 
                                  leadptcut(i_leading_e);

    _1e1disple                  = _1e && 
                                  i_subleading_displ_e != -1;

    _1e1displevtx               = _1e1disple &&
                                  _lIVF_match[i_subleading_displ_e] != -1;

    _1e1displedispl             = _1e1displevtx &&
                                  fabs(_dxy[i_subleading_displ_e]) > 0.01;

    _1e1disple0adde             = _1e1displedispl &&
                                  no_additional_leptons();
    
    _1e1disple0jet              = _1e1disple0adde && 
                                  i_leading_jet == -1;
    
    _1e1disple0jet_aftermll     = _1e1disple0jet && 
                                  mllcut(i_leading_e, i_subleading_displ_e);
    
    _1e1disple0jet_afterdR      = _1e1disple0jet_aftermll && 
                                  dRcut(i_leading_e, i_subleading_displ_e);    
    
    _1e1disple0jet_afterdphi    = _1e1disple0jet_aftermll && 
                                  dphicut(i_leading_e, i_subleading_displ_e, 2.4);    
    
    

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
                                  _lIVF_match[i_subleading_displ_mu] != -1;
    
    _1mu1displmudispl           = _1mu1displmuvtx &&
                                  fabs(_dxy[i_subleading_displ_mu]) > 0.01;

    _1mu1displmu0addmu          = _1mu1displmudispl && 
                                  no_additional_leptons();
    
    _1mu1displmu0jet            = _1mu1displmu0addmu && 
                                  i_leading_jet == -1;
    
    _1mu1displmu0jet_aftermll   = _1mu1displmu0jet && 
                                  mllcut(i_leading_mu, i_subleading_displ_mu);
    
    _1mu1displmu0jet_afterdR    = _1mu1displmu0jet_aftermll && 
                                  dRcut(i_leading_mu, i_subleading_displ_mu);    
    
    _1mu1displmu0jet_afterdphi  = _1mu1displmu0jet_aftermll && 
                                  dphicut(i_leading_mu, i_subleading_displ_mu, 2.4);    
    
    
    ////////////////////////
    // POGMedium prompt ID//
    ////////////////////////

    _1pogmediume                = _trige &&
                                  i_leading_pogmedium_e != -1 &&
                                  leadptcut(i_leading_pogmedium_e);

    _1pogmediummu               = _trigmu &&
                                  i_leading_pogmedium_mu != -1 &&
                                  leadptcut(i_leading_pogmedium_mu);


    // OLD signal region definitions, first require correct number of leptons and jets, new version first does also pt requirements;
    bool leadptveto_e = false;
    if(i_leading_e != -1 and _lPt[i_leading_e] > 30) leadptveto_e = true;
    
    bool leadptveto_mu = false;
	if(i_leading_mu != -1 and _lPt[i_leading_mu] > 25) leadptveto_mu = true;

	_2e0jet 			= leadptveto_e && i_leading_e != -1 && i_subleading_e != -1 && i_leading_jet == -1 && i_subleading_jet == -1;
	_2e1jet 			= leadptveto_e && i_leading_e != -1 && i_subleading_e != -1 && i_leading_jet != -1 && i_subleading_jet == -1;
	_2e2jet 			= leadptveto_e && i_leading_e != -1 && i_subleading_e != -1 && i_leading_jet != -1 && i_subleading_jet != -1;
	//_1e1disple0jet		= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e != -1 && i_leading_jet_for_displ == -1 && i_subleading_jet_for_displ == -1;
	//_1e1disple1jet		= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ == -1;
	//_1e1disple2jet		= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ != -1;
	//_1e0jet			= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e == -1 && i_leading_jet == -1 && i_subleading_jet == -1;
	//_1e1jet			= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e == -1 && i_leading_jet != -1 && i_subleading_jet == -1;
	//_1e2jet			= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e == -1 && i_leading_jet != -1 && i_subleading_jet != -1;
    

    _2mu0jet 			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu != -1 && i_leading_jet == -1 && i_subleading_jet == -1;
	_2mu1jet 			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu != -1 && i_leading_jet != -1 && i_subleading_jet == -1;
	_2mu2jet 			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu != -1 && i_leading_jet != -1 && i_subleading_jet != -1;
	//_1mu1displmu0jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu != -1 && i_leading_jet_for_displ == -1 && i_subleading_jet_for_displ == -1;
	//_1mu1displmu1jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ == -1;
	//_1mu1displmu2jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ != -1;
	//_1mu0jet			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu == -1 && i_leading_jet == -1 && i_subleading_jet == -1;
	//_1mu1jet			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu == -1 && i_leading_jet != -1 && i_subleading_jet == -1;
	//_1mu2jet			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu == -1 && i_leading_jet != -1 && i_subleading_jet != -1;
    
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
        if(displElectronID[i] and ele_clean_loose[i] or displMuonID[i]) loose_leptons++;
    }
    return (loose_leptons == 2);
}


bool full_analyzer::mllcut(int i_lead, int i_sublead){
    TLorentzVector leadinglepton;
    leadinglepton.SetPtEtaPhiE(_lPt[i_lead], _lEta[i_lead], _lPhi[i_lead], _lE[i_lead]);
    TLorentzVector subleadinglepton;
    subleadinglepton.SetPtEtaPhiE(_lPt[i_sublead], _lEta[i_sublead], _lPhi[i_sublead], _lE[i_sublead]);
    double mll = (leadinglepton + subleadinglepton).M();
    return mll < 80;
}

bool full_analyzer::dRcut(int i_lead, int i_sublead){
    TLorentzVector leadinglepton;
    leadinglepton.SetPtEtaPhiE(_lPt[i_lead], _lEta[i_lead], _lPhi[i_lead], _lE[i_lead]);
    TLorentzVector subleadinglepton;
    subleadinglepton.SetPtEtaPhiE(_lPt[i_sublead], _lEta[i_sublead], _lPhi[i_sublead], _lE[i_sublead]);
    double dR = fabs(leadinglepton.DeltaR(subleadinglepton));
    return (dR > 2.4 && dR < 3.5);
}

bool full_analyzer::dphicut(int i_lead, int i_sublead, double dphicut){
    TLorentzVector leadinglepton;
    leadinglepton.SetPtEtaPhiE(_lPt[i_lead], _lEta[i_lead], _lPhi[i_lead], _lE[i_lead]);
    TLorentzVector subleadinglepton;
    subleadinglepton.SetPtEtaPhiE(_lPt[i_sublead], _lEta[i_sublead], _lPhi[i_sublead], _lE[i_sublead]);
    double dphi = fabs(leadinglepton.DeltaPhi(subleadinglepton));
    return (dphi > dphicut);
}

void full_analyzer::init_sigreg_fraction(std::map<TString, TH1*>* hists){
    (*hists)["_e_sigreg_fraction"]			= new TH1F("_e_sigreg_fraction",";signal regions;Events", 13, 0, 13);
    (*hists)["_mu_sigreg_fraction"]		    = new TH1F("_mu_sigreg_fraction",";signal regions;Events", 13, 0, 13);
    (*hists)["1_e_overtotal"]		        = new TH1F("1_e_overtotal",";bin1 = total, bin2 = 1e;Events",2,0,2);
    (*hists)["1_mu_overtotal"]			    = new TH1F("1_mu_overtotal",";bin1 = total, bin2 = 1mu;Events",2,0,2);
    // signal regions that are included:
    // 0 = 2iso l, 0jet
    // 1 = 2iso l, 1jet
    // 2 = 2iso l, 2jet
    // 3 = 1iso l, 1non-iso l, 0jet
    // 4 = 1iso l, 1non-iso l, 1jet
    // 5 = 1iso l, 1non-iso l, 2jet
    // 6 = 1iso l, 1displ l, 0jet
    // 7 = 1iso l, 1displ l, 1jet
    // 8 = 1iso l, 1displ l, 2jet
    // 9 = 1iso l, 0jet
    // 10= 1iso l, 1jet
    // 11= 1iso l, 2jet
    // 12= other
}

void full_analyzer::fill_sigreg_fraction(std::map<TString, TH1*>* hists){
	(*hists)["1_e_overtotal"]->Fill(0., event_weight);
	if(_1e){
	    (*hists)["1_e_overtotal"]->Fill(1., event_weight);
	    if(_2e0jet) (*hists)["_e_sigreg_fraction"]->Fill(0., event_weight);
	    else if(_2e1jet) (*hists)["_e_sigreg_fraction"]->Fill(1., event_weight);
	    else if(_2e2jet) (*hists)["_e_sigreg_fraction"]->Fill(2., event_weight);
	    //else if(_1e1disple0jet)  (*hists)["_e_sigreg_fraction"]->Fill(6., event_weight);
	    //else if(_1e1disple1jet)  (*hists)["_e_sigreg_fraction"]->Fill(7., event_weight);
	    //else if(_1e1disple2jet)  (*hists)["_e_sigreg_fraction"]->Fill(8., event_weight);
	    //else if(_1e0jet) (*hists)["_e_sigreg_fraction"]->Fill(9., event_weight);
	    //else if(_1e1jet) (*hists)["_e_sigreg_fraction"]->Fill(10., event_weight);
	    //else if(_1e2jet) (*hists)["_e_sigreg_fraction"]->Fill(11., event_weight);
	    else (*hists)["_e_sigreg_fraction"]->Fill(12., event_weight);
	}
	(*hists)["1_mu_overtotal"]->Fill(0., event_weight);
	if(_1mu){
	    (*hists)["1_mu_overtotal"]->Fill(1., event_weight);
	    if(_2mu0jet) (*hists)["_mu_sigreg_fraction"]->Fill(0., event_weight);
	    else if(_2mu1jet) (*hists)["_mu_sigreg_fraction"]->Fill(1., event_weight);
	    else if(_2mu2jet) (*hists)["_mu_sigreg_fraction"]->Fill(2., event_weight);
	    //else if(_1mu1displmu0jet)  (*hists)["_mu_sigreg_fraction"]->Fill(6., event_weight);
	    //else if(_1mu1displmu1jet)  (*hists)["_mu_sigreg_fraction"]->Fill(7., event_weight);
	    //else if(_1mu1displmu2jet)  (*hists)["_mu_sigreg_fraction"]->Fill(8., event_weight);
	    //else if(_1mu0jet) (*hists)["_mu_sigreg_fraction"]->Fill(9., event_weight);
	    //else if(_1mu1jet) (*hists)["_mu_sigreg_fraction"]->Fill(10., event_weight);
	    //else if(_1mu2jet) (*hists)["_mu_sigreg_fraction"]->Fill(11., event_weight);
	    else (*hists)["_mu_sigreg_fraction"]->Fill(12., event_weight);
	}
}
