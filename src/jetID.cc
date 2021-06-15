////////////////////////////////////////////////////
//part of class full_analyzer, jet ID and cleaning//
////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

bool full_analyzer::IsTightJetID(const unsigned i)
{
    if(fabs(_jetEta[i]) > 2.4)  return false;
    if(_jetPt[i] < 30)          return false;
    if(!_jetIsTightLepVeto[i])  return false;

    return true;
}

bool full_analyzer::IsCleanJet(const unsigned i, const std::vector<unsigned>& leptoncollection)
{
	LorentzVector jet(_jetPt[i], _jetEta[i], _jetPhi[i], _jetE[i]);

    for(const auto& i_lepton : leptoncollection){
        LorentzVector lepton(_lPt[i_lepton], _lEta[i_lepton], _lPhi[i_lepton], _lE[i_lepton]);

        if(deltaR(jet, lepton) < 0.4) return false;
    }

    return true;
}

int full_analyzer::find_leading_jet(const std::vector<unsigned>& jetcollection)
{
    int index_leading = -1;

    for(const auto& index_jet : jetcollection){
        if(index_leading == -1) index_leading = (int)index_jet;
        else if(_lPt[index_jet] > _lPt[index_leading]) index_leading = (int)index_jet;
    }

    return index_leading;
}

int full_analyzer::find_subleading_jet(const std::vector<unsigned>& jetcollection, const int index_leading)
{
    if(index_leading == -1) return -1;
    int index_subleading = -1;

    for(const auto& index_jet : jetcollection){
        if((int)index_jet == index_leading) continue;

        if(index_subleading == -1) index_subleading = (int)index_jet;
        else if(_lPt[index_jet] > _lPt[index_subleading]) index_subleading = (int)index_jet;
    }

    return index_subleading;
}

int full_analyzer::find_thirdleading_jet(const std::vector<unsigned>& jetcollection, const int index_leading, const int index_subleading)
{
    if(index_leading == -1 or index_subleading == -1) return -1;
    int index_thirdleading = -1;

    for(const auto& index_jet : jetcollection){
        if((int)index_jet == index_leading or (int)index_jet == index_subleading) continue;

        if(index_thirdleading == -1) index_thirdleading = (int)index_jet;
        else if(_lPt[index_jet] > _lPt[index_thirdleading]) index_thirdleading = (int)index_jet;
    }

    return index_thirdleading;
}

int full_analyzer::find_jet_closest_to_lepton(int i_lep)
{
    int index_jet = -1;
    if(i_lep == -1) return index_jet;

    double dR;
    double mindR = 0.7;

    for(unsigned i_jet = 0; i_jet < _nJets; i_jet++){
        if(IsTightJetID(i_jet)){
            dR = get_dR_lepton_jet(i_lep, i_jet);
            if(dR < mindR){ index_jet = (int)i_jet; mindR = dR;}
        }
    }

    return index_jet;
}


double full_analyzer::get_dR_lepton_jet(int i_lep, int i_jet){
    LorentzVector vec_lep(_lPt[i_lep], _lEta[i_lep], _lPhi[i_lep], _lE[i_lep]);
    LorentzVector vec_jet(_jetPt[i_jet], _jetEta[i_jet], _jetPhi[i_jet], _jetE[i_jet]);
    return deltaR(vec_lep, vec_jet);
}

