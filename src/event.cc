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
        //if(IsPromptMuonID(i))       promptMuonID.push_back(i);
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
    i_leading = select_leading_lepton(promptElectronID, promptMuonID);
    i_subleading = select_subleading_lepton_highestpt(displacedElectronID, displacedMuonID);
    //i_subleading = select_subleading_lepton_withSV(displacedElectronID, displacedMuonID);
    i_subleading_highestpt = select_subleading_lepton_highestpt(displacedElectronID, displacedMuonID);

	i_leading_jet                   = find_leading_jet(jetID);
	i_subleading_jet	            = find_subleading_jet(jetID, i_leading_jet);
    i_thirdleading_jet              = find_thirdleading_jet(jetID, i_leading_jet, i_subleading_jet);

    set_leptons(JetPt_Version);

    signal_regions();

}

double full_analyzer::Get_Event_weight()
{
    if(!isData){
        double tmp_weight = _weight;
        if(isSignal) tmp_weight *= 1.089;//HNL LO xsec uncertainty
        tmp_weight *= puweightreader->get_PUWeight_Central(_nTrueInt);
        if(i_leading != -1 and _lFlavor[i_leading] == 0){//electron scale factors
            tmp_weight *= lsfreader_e_trig->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
            tmp_weight *= lsfreader_e_ID->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
        }else if(i_leading != -1 and _lFlavor[i_leading] == 1){//muon scale factors
            tmp_weight *= lsfreader_m_trig->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            tmp_weight *= lsfreader_m_ID->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            tmp_weight *= lsfreader_m_ISO->get_LSF(_lPt[i_leading], _lEta[i_leading]);
        }
        if(i_subleading != -1 and _lFlavor[i_subleading] == 0){//displaced electron scale factors
            tmp_weight *= get_displEleSF(_lPt[i_subleading], _dxy[i_subleading]);
        }else if(i_subleading != -1 and _lFlavor[i_subleading] == 1){//displaced muon scale factors
            tmp_weight *= sqrt(lsfreader_displ_m_SV->get_LSF(_lPt[i_subleading]*2, IVF_PVSVdist_2D));
        }
        tmp_weight *= highest_trackpt_weight;//displaced tracks scale factor (in src/signal_regions.cc)
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
    nDisplMu = 0;

    for(unsigned i = 0; i < _nLight; i++){
        bool CleanElectron = IsCleanElectron(i, promptMuonID);

        if(IsMvaPromptElectronID(i) and CleanElectron) promptElectronID.push_back(i);
    }
    nTightEle = promptElectronID.size();
    nDisplEle = 0;
    
    std::vector<unsigned> jetID, jetID_uncl;
    for(unsigned i = 0; i < _nJets; i++){
        if(IsTightJetID(i,JetPt_Version) and IsCleanJet(i, promptMuonID) and IsCleanJet(i, promptElectronID)) jetID.push_back(i);
        if(IsTightJetID(i, JetPt_Version)) jetID_uncl.push_back(i);
    }
    nTightJet       = jetID.size();
    nTightJet_uncl  = jetID_uncl.size();
    
    //Find leptons and jets with leading pt
    i_leading = select_leading_lepton(promptElectronID, promptMuonID);
    i_subleading = select_subleading_lepton_highestpt(promptElectronID, promptMuonID);

    i_leading_jet                   = find_leading_jet(jetID);
	i_subleading_jet	            = find_subleading_jet(jetID, i_leading_jet);
    i_thirdleading_jet              = find_thirdleading_jet(jetID, i_leading_jet, i_subleading_jet);

    set_leptons(JetPt_Version);
    signal_regions();
}

double full_analyzer::Get_Event_weight_2prompt()
{
    if(!isData){
        double tmp_weight = _weight;
        tmp_weight *= puweightreader->get_PUWeight_Central(_nTrueInt);
        if(i_leading != -1 and _lFlavor[i_leading] == 0){//electron scale factors
            tmp_weight *= lsfreader_e_trig->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
            tmp_weight *= lsfreader_e_ID->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
        }else if(i_leading != -1 and _lFlavor[i_leading] == 1){//muon scale factors
            tmp_weight *= lsfreader_m_trig->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            tmp_weight *= lsfreader_m_ID->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            tmp_weight *= lsfreader_m_ISO->get_LSF(_lPt[i_leading], _lEta[i_leading]);
        }
        if(i_subleading != -1 and _lFlavor[i_subleading] == 0){//second electron scale factors
            tmp_weight *= lsfreader_e_ID->get_LSF(_lPt[i_subleading], _lEtaSC[i_subleading]);
        }else if(i_subleading != -1 and _lFlavor[i_subleading] == 1){//second muon scale factors
            tmp_weight *= lsfreader_m_ID->get_LSF(_lPt[i_subleading], _lEta[i_subleading]);
            tmp_weight *= lsfreader_m_ISO->get_LSF(_lPt[i_subleading], _lEta[i_subleading]);
        }
        return tmp_weight;
    }else {
        return 1.;
    }
}

void full_analyzer::fill_SR_counters_cutflow(std::map<TString, double>& sr)
{
    sr["1_noSel"]++;
    if(_trigmu){
        sr["2_Triggermuon"]++;
        if(i_leading != -1 && leadptcut(i_leading)){
            sr["3_l1muon"]++;
            if(!_genOverlap){
                sr["4_genOverlap"]++;
                if(i_subleading != -1){
                    sr["5_l2muon"]++;
                    if(_lIVF_match[i_subleading]){
                        sr["6_SV"]++;
                        if(i_jetl2 != -1){
                            sr["7_jetl2"]++;
                            if(nTightJet <= 1){
                                sr["8_nTightJet"]++;
                                if(nTightEle + nTightMu == 1){
                                    sr["9_nTightLep"]++;
                                    if(mll > 10){
                                        sr["10_mll"]++;
                                        if(dphill > 0.4){
                                            sr["11_dphill"]++;
                                            if(IVF_PVSVdist_2D < 50){
                                                sr["12_PVSVdist"]++;
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

void full_analyzer::Print_Event_weight()
{
    if(!isData){
        std::cout << " PU" << puweightreader->get_PUWeight_Central(_nTrueInt);
        if(i_leading != -1 and _lFlavor[i_leading] == 0){//electron scale factors
            std::cout << " etrig" << lsfreader_e_trig->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
            std::cout << " eID" << lsfreader_e_ID->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
        }else if(i_leading != -1 and _lFlavor[i_leading] == 1){//muon scale factors
            std::cout << " mtrig" << lsfreader_m_trig->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            std::cout << " mID" << lsfreader_m_ID->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            std::cout << " mISO" << lsfreader_m_ISO->get_LSF(_lPt[i_leading], _lEta[i_leading]);
        }
        if(i_subleading != -1 and _lFlavor[i_subleading] == 0){//displaced electron scale factors
            std::cout << " e2SF" << get_displEleSF(_lElectronMissingHits[i_subleading]);
        }else if(i_subleading != -1 and _lFlavor[i_subleading] == 1){//displaced muon scale factors
            std::cout << " m2ID" << lsfreader_displ_m_ID->get_LSF(_lPt[i_subleading], _lEta[i_subleading]);
            std::cout << " m2SV" << sqrt(lsfreader_displ_m_SV->get_LSF(_lPt[i_subleading]*2, IVF_PVSVdist_2D));
        }
        std::cout << " SV" << highest_trackpt_weight;
    }
}

void full_analyzer::Print_Event_weight_2prompt()
{
    if(!isData){
        std::cout << "_weight: " << _weight;
        std::cout << " PU: " << puweightreader->get_PUWeight_Central(_nTrueInt);
        if(i_leading != -1 and _lFlavor[i_leading] == 0){//electron scale factors
            std::cout << " etrig: " << lsfreader_e_trig->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
            std::cout << " eID: " << lsfreader_e_ID->get_LSF(_lPt[i_leading], _lEtaSC[i_leading]);
        }else if(i_leading != -1 and _lFlavor[i_leading] == 1){//muon scale factors
            std::cout << " mtrig: " << lsfreader_m_trig->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            std::cout << " mID: " << lsfreader_m_ID->get_LSF(_lPt[i_leading], _lEta[i_leading]);
            std::cout << " mISO: " << lsfreader_m_ISO->get_LSF(_lPt[i_leading], _lEta[i_leading]);
        }
        if(i_subleading != -1 and _lFlavor[i_subleading] == 0){//second electron scale factors
            std::cout << " e2ID: " << lsfreader_e_ID->get_LSF(_lPt[i_subleading], _lEtaSC[i_subleading]);
        }else if(i_subleading != -1 and _lFlavor[i_subleading] == 1){//second muon scale factors
            std::cout << " m2ID: " << lsfreader_m_ID->get_LSF(_lPt[i_subleading], _lEta[i_subleading]);
            std::cout << " m2ISO: " << lsfreader_m_ISO->get_LSF(_lPt[i_subleading], _lEta[i_subleading]);
        }
        std::cout << std::endl;
    }
}

