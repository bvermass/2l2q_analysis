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
    (*hists)["gen_M_l1_N"]                          = new TH1F("gen_M_l1_N", ";M_{Nl1} [GeV]; Events", 40, 0, 150);
    (*hists)["gen_PV_Nvertex_dxyz"]                 = new TH1F("gen_PV_Nvertex_dxyz", ";#Delta_{3D} (PV^{reco} - Nvtx^{gen}) [cm]; Events", 40, 0, 0.05);

    //log scale
    double xmin = 0.8;
    double xmax = 300;
    int nbins   = 25;
    double xbins[nbins+1];
    make_logscale(&xbins[0], nbins, xmin, xmax);
    (*hists)["gen_PV-SVdist_xlog"]   = new TH1F("gen_PV-SVdist_xlog", ";#Delta_{xyz} (PV_{gen}, SV_{gen}) [cm]; Events", nbins, xbins);
}

void full_analyzer::fill_HNL_MC_check(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D)
{
    if(i_gen_l1 != -1 && i_gen_l2 != -1){
        (*hists2D)["MC_check_gen_l1_l2_charge"]->Fill(_gen_lCharge[i_gen_l1], _gen_lCharge[i_gen_l2], event_weight);
        (*hists)["gen_l1_pt"]->Fill(_gen_lPt[i_gen_l1], event_weight);
        (*hists)["gen_l2_pt"]->Fill(_gen_lPt[i_gen_l2], event_weight);
        (*hists)["gen_N_pt"]->Fill(_gen_NPt, event_weight);
        TLorentzVector lepton1_vec;
        TLorentzVector HNL_vec;
        lepton1_vec.SetPtEtaPhiE(_gen_lPt[i_gen_l1], _gen_lEta[i_gen_l1], _gen_lPhi[i_gen_l1], _gen_lE[i_gen_l1]);
        HNL_vec.SetPtEtaPhiE(_gen_NPt, _gen_NEta, _gen_NPhi, _gen_NE);
        (*hists)["gen_M_l1_N"]->Fill((lepton1_vec + HNL_vec).M(), event_weight);
        (*hists)["gen_PV_Nvertex_dxyz"]->Fill(sqrt((_PV_x - _gen_Nvertex_x)*(_PV_x - _gen_Nvertex_x) + (_PV_y - _gen_Nvertex_y)*(_PV_y - _gen_Nvertex_y) + (_PV_z - _gen_Nvertex_z)*(_PV_z - _gen_Nvertex_z)), event_weight);
        (*hists)["gen_PV-SVdist_xlog"]->Fill(get_PVSVdist_gen(i_gen_l2), event_weight);
    }
}
