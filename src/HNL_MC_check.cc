/////////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to HLT efficiency calculation//
/////////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::init_HNL_MC_check(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D)
{
    (*hists2D)["MC_check_gen_l1_l2_charge"]         = new TH2F("MC_check_gen_l1_l2_charge", ";l_{1} Charge; l_{2} Charge", 2, -2, 2, 2, -2, 2);
    (*hists)["gen_l1_pt"]                           = new TH1F("gen_l1_pt", ";l_{1}^{gen} #it{p}_{T} [GeV]; Events", 40, 0, 80);
    (*hists)["gen_l2_pt"]                           = new TH1F("gen_l2_pt", ";l_{1}^{gen} #it{p}_{T} [GeV]; Events", 40, 0, 80);
    (*hists)["gen_N_pt"]                            = new TH1F("gen_N_pt", ";HNL #it{p}_{T} [GeV]; Events", 40, 0, 80);
    (*hists)["gen_M_l1_N"]                          = new TH1F("gen_M_l1_N", ";M_{Nl1} [GeV]; Events", 40, 0, 80);
}

void full_analyzer::fill_HNL_MC_check(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D)
{
    if(i_gen_l1 != -1 && i_gen_l2 != -1){
        (*hists2D)["MC_check_gen_l1_l2_charge"]->Fill(_gen_lCharge[i_gen_l1], _gen_lCharge[i_gen_l2], event_weight);
        (*hists)["gen_l1_pt"]->Fill(_gen_lPt[i_gen_l1]);
        (*hists)["gen_l2_pt"]->Fill(_gen_lPt[i_gen_l2]);
        (*hists)["gen_N_pt"]->Fill(_gen_NPt);
        TLorentzVector lepton1_vec;
        TLorentzVector HNL_vec;
        lepton1_vec.SetPtEtaPhiE(_gen_lPt[i_gen_l1], _gen_lEta[i_gen_l1], _gen_lPhi[i_gen_l1], _gen_lE[i_gen_l1]);
        HNL_vec.SetPtEtaPhiE(_gen_NPt, _gen_NEta, _gen_NPhi, _gen_NE);
        (*hists)["gen_M_l1_N"]->Fill((lepton1_vec + HNL_vec).M());
    }
}
