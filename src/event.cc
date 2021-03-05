///////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to Signal region definition//
///////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

void full_analyzer::Set_Objects_And_Relevant_Variables(const TString JetPt_Version)
{
    //Get muons, electrons and jets that pass ID and cleaning
    std::vector<unsigned> promptMuonID, promptElectronID, displacedMuonID, displacedElectronID, looseMuonID, looseElectronID;
    for(unsigned i = 0; i < _nLight; i++){
        if(IsMediumPromptMuonID(i)) promptMuonID.push_back(i);
        if(IsDisplacedMuonID(i))    displacedMuonID.push_back(i);
        if(IsLooseMuonID(i))        looseMuonID.push_back(i);
    }
    nTightMu = promptMuonID.size();
    nDisplMu = displacedMuonID.size();

    for(unsigned i = 0; i < _nLight; i++){
        bool CleanElectron = IsCleanElectron(i, promptMuonID) and IsCleanElectron(i, displacedMuonID);

        if(IsMvaPromptElectronID(i) and CleanElectron) promptElectronID.push_back(i);
        if(IsDisplacedElectronID(i) and CleanElectron) displacedElectronID.push_back(i);
        if(IsLooseElectronID(i)     and CleanElectron) looseElectronID.push_back(i);
    }
    nTightEle = promptElectronID.size();
    nDisplEle = displacedElectronID.size();

    set_jetPt_JERvariations();
    std::vector<unsigned> jetID, jetID_uncl;
    for(unsigned i = 0; i < _nJets; i++){
        if(IsTightJetID(i,JetPt_Version) and IsCleanJet(i, promptMuonID) and IsCleanJet(i, promptElectronID) and IsCleanJet(i, displacedMuonID) and IsCleanJet(i, displacedElectronID)) jetID.push_back(i);
        if(IsTightJetID(i, JetPt_Version)) jetID_uncl.push_back(i);
    }
    nTightJet       = jetID.size();
    nTightJet_uncl  = jetID_uncl.size();

    //Find leptons and jets with leading pt
	int i_leading_e     		    = find_leading_lepton(promptElectronID);
	int i_leading_mu    		    = find_leading_lepton(promptMuonID);

    i_leading = select_leading_lepton(i_leading_e, i_leading_mu);

	int i_subleading_e  		    = find_subleading_lepton(promptElectronID, i_leading);
	int i_subleading_displ_e  	    = find_subleading_lepton(displacedElectronID, i_leading);
	int i_subleading_mu 		    = find_subleading_lepton(promptMuonID, i_leading);
	int i_subleading_displ_mu 	    = find_subleading_lepton(displacedMuonID, i_leading);

	i_leading_jet                   = find_leading_jet(jetID);
	i_subleading_jet	            = find_subleading_jet(jetID, i_leading_jet);
    i_thirdleading_jet              = find_thirdleading_jet(jetID, i_leading_jet, i_subleading_jet);


    set_leptons(i_subleading_displ_e, i_subleading_displ_mu, JetPt_Version);
    signal_regions();

}

double full_analyzer::Get_Event_weight()
{
    if(!isData){
        double tmp_weight = _weight;
        if(isSignal) tmp_weight *= 1.089;//HNL LO xsec uncertainty
        tmp_weight *= puweightreader->get_PUWeight_Central(_nTrueInt);
        if(_lFlavor[i_leading] == 0){//electron scale factors
            tmp_weight *= lsfreader_e_trig->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
            tmp_weight *= lsfreader_e_ID->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
        }else if(_lFlavor[i_leading] == 1){//muon scale factors
            tmp_weight *= lsfreader_m_trig->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            tmp_weight *= lsfreader_m_ID->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            tmp_weight *= lsfreader_m_ISO->get_LSF(_lPt[i_leading], _lEta[i_leading]);
        }
        if(_lFlavor[i_subleading] == 0){//displaced electron scale factors
            tmp_weight *= get_displEleSF(_lElectronMissingHits[i_subleading]);
        }else if(_lFlavor[i_subleading] == 1){//displaced muon scale factors
            tmp_weight *= lsfreader_displ_m_ID->get_LSF(_lPt[i_subleading], _lEta[i_subleading]);
            tmp_weight *= sqrt(lsfreader_displ_m_SV->get_LSF(_lPt[i_subleading]*2, IVF_PVSVdist_2D));
        }
        tmp_weight *= highest_trackpt_weight;//displaced tracks scale factor (in src/signal_regions.cc)
        if(tmp_weight == 0 and _Training){
            std::cout << "Weight 0: ";
            std::cout << " PU" << puweightreader->get_PUWeight_Central(_nTrueInt);
            std::cout << " etrig" << lsfreader_e_trig->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
            std::cout << " eID" << lsfreader_e_ID->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
            std::cout << " mtrig" << lsfreader_m_trig->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            std::cout << " mID" << lsfreader_m_ID->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            std::cout << " mISO" << lsfreader_m_ISO->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            std::cout << " e2SF" << get_displEleSF(_lElectronMissingHits[i_subleading]);
            std::cout << " m2ID" << lsfreader_displ_m_ID->get_LSF(_lPt[i_subleading], _lEta[i_subleading]);
            std::cout << " m2SV" << sqrt(lsfreader_displ_m_SV->get_LSF(_lPt[i_subleading]*2, IVF_PVSVdist_2D));
            std::cout << " SV" << highest_trackpt_weight;
        }
        return tmp_weight;
    }else {
        return 1.;
    }
}

void full_analyzer::Set_Objects_And_Relevant_Variables_2prompt(const TString JetPt_Version)
{
    //Get muons, electrons and jets that pass ID and cleaning
    std::vector<unsigned> promptMuonID, promptElectronID;
    for(unsigned i = 0; i < _nLight; i++){
        if(IsMediumPromptMuonID(i)) promptMuonID.push_back(i);
    }
    nTightMu = promptMuonID.size();

    for(unsigned i = 0; i < _nLight; i++){
        bool CleanElectron = IsCleanElectron(i, promptMuonID);

        if(IsMvaPromptElectronID(i) and CleanElectron) promptElectronID.push_back(i);
    }
    nTightEle = promptElectronID.size();
    
    std::vector<unsigned> jetID, jetID_uncl;
    for(unsigned i = 0; i < _nJets; i++){
        if(IsTightJetID(i,JetPt_Version) and IsCleanJet(i, promptMuonID) and IsCleanJet(i, promptElectronID)) jetID.push_back(i);
        if(IsTightJetID(i, JetPt_Version)) jetID_uncl.push_back(i);
    }
    nTightJet       = jetID.size();
    nTightJet_uncl  = jetID_uncl.size();
    
    //Find leptons and jets with leading pt
	int i_leading_e     		    = find_leading_lepton(promptElectronID);
	int i_leading_mu    		    = find_leading_lepton(promptMuonID);

    i_leading = select_leading_lepton(i_leading_e, i_leading_mu);

	int i_subleading_e  		    = find_subleading_lepton(promptElectronID, i_leading);
	int i_subleading_mu 		    = find_subleading_lepton(promptMuonID, i_leading);
	
    i_leading_jet                   = find_leading_jet(jetID);
	i_subleading_jet	            = find_subleading_jet(jetID, i_leading_jet);
    i_thirdleading_jet              = find_thirdleading_jet(jetID, i_leading_jet, i_subleading_jet);

    set_leptons(i_subleading_e, i_subleading_mu, JetPt_Version);
    signal_regions();
}

double full_analyzer::Get_Event_weight_2prompt()
{
    if(!isData){
        double tmp_weight = _weight;
        //std::cout << "_weight: " << _weight;
        tmp_weight *= puweightreader->get_PUWeight_Central(_nTrueInt);
        //std::cout << " PU: " << puweightreader->get_PUWeight_Central(_nTrueInt);
        if(_lFlavor[i_leading] == 0){//electron scale factors
            tmp_weight *= lsfreader_e_trig->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
            tmp_weight *= lsfreader_e_ID->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
            //std::cout << " etrig: " << lsfreader_e_trig->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
            //std::cout << " eID: " << lsfreader_e_ID->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
        }else if(_lFlavor[i_leading] == 1){//muon scale factors
            tmp_weight *= lsfreader_m_trig->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            tmp_weight *= lsfreader_m_ID->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            tmp_weight *= lsfreader_m_ISO->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            //std::cout << " mtrig: " << lsfreader_m_trig->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            //std::cout << " mID: " << lsfreader_m_ID->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            //std::cout << " mISO: " << lsfreader_m_ISO->get_LSF(_lPt[i_leading], _lEta[i_leading]);
        }
        if(_lFlavor[i_subleading] == 0){//second electron scale factors
            tmp_weight *= lsfreader_e_ID->get_LSF(_lPt[i_subleading], _lEtaSC[i_subleading]);
            //std::cout << " e2ID: " << lsfreader_e_ID->get_LSF(_lPt[i_subleading], _lEtaSC[i_subleading]);
        }else if(_lFlavor[i_subleading] == 1){//second muon scale factors
            tmp_weight *= lsfreader_m_ID->get_LSF(_lPt[i_subleading], _lEta[i_subleading]);
            tmp_weight *= lsfreader_m_ISO->get_LSF(_lPt[i_subleading], _lEta[i_subleading]);
            //std::cout << " m2ID: " << lsfreader_m_ID->get_LSF(_lPt[i_subleading], _lEta[i_subleading]);
            //std::cout << " m2ISO: " << lsfreader_m_ISO->get_LSF(_lPt[i_subleading], _lEta[i_subleading]);
        }
        //std::cout << std::endl;
        return tmp_weight;
    }else {
        return 1.;
    }
}

void full_analyzer::fill_SR_counters_cutflow(std::map<TString, double>& sr)
{
    sr["noSel"]++;
    if(_trigmu){
        sr["Triggermuon"]++;
        if(i_leading != -1 && leadptcut(i_leading)){
            sr["l1muon"]++;
            if(!_genOverlap){
                sr["genOverlap"]++;
                if(isSingleMuon and _lFlavor[i_leading] == 1){
                    sr["isSingleMuon"]++;
                    if(i_subleading != -1){
                        sr["l2muon"]++;
                        if(_lIVF_match[i_subleading] != -1){
                            sr["SV"]++;
                            if(i_jetl2 != -1){
                                sr["jetl2"]++;
                                if(nTightJet <= 1){
                                    sr["nTightJet"]++;
                                    if(nTightEle + nTightMu == 1){
                                        sr["nTightLep"]++;
                                        if(mll > 10){
                                            sr["mll"]++;
                                            if(dphill > 0.4){
                                                sr["dphill"]++;
                                                if(IVF_PVSVdist_2D < 50){
                                                    sr["PVSVdist"]++;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
