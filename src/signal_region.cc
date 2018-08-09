///////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to Signal region definition//
///////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::signal_regions(){

    
    // NEW signal region method, sequential so that I can make histograms between each step if I want
    // others should be adapted to this method, do this NEXT WEEK WITH TIER2 DOWN
    _1e			                = i_leading_e != -1 && leadptcut("e");
    
    _1e1disple                  = _1e && i_subleading_displ_e != -1;

    _1e1disple0adde             = _1e1disple && i_subleading_e == -1 && i_subleading_noniso_e == -1;

    _1e1disple0jet              = _1e1disple0adde && i_leading_jet_for_displ == -1;

    _1e1disple0jet_aftermll     = _1e1disple0jet && mllcut(i_leading_e, i_subleading_displ_e);

    _1e1disple0jet_afterdphi    = _1e1disple0jet_aftermll && dphicut(i_leading_e, i_subleading_displ_e);    
    
    _1mu                        = i_leading_mu != -1 && leadptcut("mu");
    
    _1mu1displmu                = _1mu && i_subleading_displ_mu != -1;

    _1mu1displmu0addmu          = _1mu1displmu && i_subleading_mu == -1 && i_subleading_noniso_mu == -1;

    _1mu1displmu0jet            = _1mu1displmu0addmu && i_leading_jet_for_displ == -1;

    _1mu1displmu0jet_aftermll   = _1mu1displmu0jet && mllcut(i_leading_mu, i_subleading_displ_mu);
    
    _1mu1displmu0jet_afterdphi  = _1mu1displmu0jet_aftermll && dphicut(i_leading_mu, i_subleading_displ_mu);    
    
    // OLD signal region definitions, first require correct number of leptons and jets, new version first does also pt requirements;
    bool leadptveto_e = false;
    if(i_leading_e != -1 and _lPt[i_leading_e] > 30) leadptveto_e = true;
    
    bool leadptveto_mu = false;
	if(i_leading_mu != -1 and _lPt[i_leading_mu] > 25) leadptveto_mu = true;

	_2e0jet 			= leadptveto_e && i_leading_e != -1 && i_subleading_e != -1 && i_leading_jet_for_full == -1 && i_subleading_jet_for_full == -1;
	_2e1jet 			= leadptveto_e && i_leading_e != -1 && i_subleading_e != -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full == -1;
	_2e2jet 			= leadptveto_e && i_leading_e != -1 && i_subleading_e != -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full != -1;
	_1e1nonisoe0jet	    = leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e != -1 && i_leading_jet_for_noniso == -1 && i_subleading_jet_for_noniso == -1;
	_1e1nonisoe1jet	    = leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e != -1 && i_leading_jet_for_noniso != -1 && i_subleading_jet_for_noniso == -1;
	_1e1nonisoe2jet	    = leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e != -1 && i_leading_jet_for_noniso != -1 && i_subleading_jet_for_noniso != -1;
	//_1e1disple0jet		= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e != -1 && i_leading_jet_for_displ == -1 && i_subleading_jet_for_displ == -1;
	_1e1disple1jet		= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ == -1;
	_1e1disple2jet		= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ != -1;
	_1e0jet			= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e == -1 && i_leading_jet_for_full == -1 && i_subleading_jet_for_full == -1;
	_1e1jet			= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e == -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full == -1;
	_1e2jet			= leadptveto_e && i_leading_e != -1 && i_subleading_e == -1 && i_subleading_noniso_e == -1 && i_subleading_displ_e == -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full != -1;
    

    _2mu0jet 			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu != -1 && i_leading_jet_for_full == -1 && i_subleading_jet_for_full == -1;
	_2mu1jet 			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu != -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full == -1;
	_2mu2jet 			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu != -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full != -1;
	_1mu1nonisomu0jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu != -1 && i_leading_jet_for_noniso == -1 && i_subleading_jet_for_noniso == -1;
	_1mu1nonisomu1jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu != -1 && i_leading_jet_for_noniso != -1 && i_subleading_jet_for_noniso == -1;
	_1mu1nonisomu2jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu != -1 && i_leading_jet_for_noniso != -1 && i_subleading_jet_for_noniso != -1;
	//_1mu1displmu0jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu != -1 && i_leading_jet_for_displ == -1 && i_subleading_jet_for_displ == -1;
	_1mu1displmu1jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ == -1;
	_1mu1displmu2jet	= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu != -1 && i_leading_jet_for_displ != -1 && i_subleading_jet_for_displ != -1;
	_1mu0jet			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu == -1 && i_leading_jet_for_full == -1 && i_subleading_jet_for_full == -1;
	_1mu1jet			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu == -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full == -1;
	_1mu2jet			= leadptveto_mu && i_leading_mu != -1 && i_subleading_mu == -1 && i_subleading_noniso_mu == -1 && i_subleading_displ_mu == -1 && i_leading_jet_for_full != -1 && i_subleading_jet_for_full != -1;
    
}

bool full_analyzer::leadptcut(TString flavor){
    if(flavor == "e"       && i_leading_e  != -1 && _lPt[i_leading_e]  > 30) return true;
    else if(flavor == "mu" && i_leading_mu != -1 && _lPt[i_leading_mu] > 25) return true;
    else return false;
}

bool full_analyzer::mllcut(int i_lead, int i_sublead){
    TLorentzVector leadinglepton;
    leadinglepton.SetPtEtaPhiE(_lPt[i_lead], _lEta[i_lead], _lPhi[i_lead], _lE[i_lead]);
    TLorentzVector subleadinglepton;
    subleadinglepton.SetPtEtaPhiE(_lPt[i_sublead], _lEta[i_sublead], _lPhi[i_sublead], _lE[i_sublead]);
    double mll = (leadinglepton + subleadinglepton).M();
    return (mll < 80 || mll > 100);
}

bool full_analyzer::dphicut(int i_lead, int i_sublead){
    TLorentzVector leadinglepton;
    leadinglepton.SetPtEtaPhiE(_lPt[i_lead], _lEta[i_lead], _lPhi[i_lead], _lE[i_lead]);
    TLorentzVector subleadinglepton;
    subleadinglepton.SetPtEtaPhiE(_lPt[i_sublead], _lEta[i_sublead], _lPhi[i_sublead], _lE[i_sublead]);
    double dphi = fabs(leadinglepton.DeltaPhi(subleadinglepton));
    return dphi > 2.4;
}
