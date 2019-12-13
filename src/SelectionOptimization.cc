/////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, everything related to selection optimization//
/////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

//void full_analyzer::add_ROC_hists(std::map<TString, TH1*>* hists, TString prefix)
//{
//    (*hists)[prefix+"_SelOpt_l1_MVA_ROC"]   = new TH1F(prefix+"_SelOpt_l1_MVA_ROC", ";l1 MVA; Events", 5, 0.5, 1);
//}
//
//
//void full_analyzer::fill_ROC_hists(std::map<TString, TH1*>* hists, TString prefix, int i_leading)
//{
//    if(_leptonMvatZq[i_leading] > 0.6) (*hists)[prefix+"_SelOpt_l1_MVA_ROC"]->Fill(_leptonMvatZq[i_leading], event_weight);
//    else (*hists)[prefix+"_SelOpt_l1_MVA_ROC"]->Fill(0.51, event_weight);
//}

bool full_analyzer::create_sigreg_bool(int i_leading, int i_subleading, bool base_selection, double l2_dxy, double l2_reliso, double dphi, double dR, double upperdR, double mll, double lowermll, bool applyLepVeto, bool applyOneJet, double jettagval)
{
    return base_selection &&
        fabs(_dxy[i_subleading]) > l2_dxy &&
        (l2_reliso == -1 or relisocut(i_subleading, l2_reliso)) &&
        (dphi == -1 or dphicut(i_leading, i_subleading, dphi)) &&
        (dR == -1 or dRcut(i_leading, i_subleading, dR, 8)) &&
        (upperdR == -1 or dRcut(i_leading, i_subleading, 0, upperdR)) &&
        mllcut(i_leading, i_subleading, mll) &&
        (lowermll == -1 or get_mll(i_leading, i_subleading) > lowermll) &&
        (!applyLepVeto or no_additional_leptons()) &&
        (!applyOneJet or i_subleading_jet == -1) &&
        _lIVF_match[i_subleading] &&
        (jettagval == -1 or JetTagVal[5][1e-6] > jettagval);
}

void full_analyzer::add_Bool_hists(std::map<TString, TH1*>* hists, TString prefix)
{
    (*hists)[prefix+"_Bool_1mu1displmu1jet"] = new TH1F(prefix+"_Bool_1mu1displmu1jet", ";;Events", 1, 0, 1);
    (*hists)[prefix+"_Bool_1mu1displmu_PFN"] = new TH1F(prefix+"_Bool_1mu1displmu_PFN", ";;Events", 1, 0, 1);

    (*hists)[prefix+"_Bool_1e1disple1jet"] = new TH1F(prefix+"_Bool_1e1disple1jet", ";;Events", 1, 0, 1);
    (*hists)[prefix+"_Bool_1e1disple_PFN"] = new TH1F(prefix+"_Bool_1e1disple_PFN", ";;Events", 1, 0, 1);

    for(const double& l2_dxy : {0.02}){
        for(const double& l2_reliso : {1.5, -1.}){
            for(const double& dphi : {-1., 2.2, 2.4}){
                for(const double& dR : {-1., 1., 2., 2.4}){
                    for(const double& upperdR : {-1., 5.5}){
                        for(const double& mll : {75., 80.}){
                            for(const double& lowermll : {-1., 20.}){
                                for(const bool& applyLepVeto : {false}){
                                    for(const bool& applyOneJet : {true, false}){
                                        for(const double& jettagval : {-1., 0.8, 0.9, 0.95}){
                                            TString name = (TString) prefix + "_Bool" +
                                                "_dxy" + std::to_string(l2_dxy) +
                                                ((l2_reliso != -1)? "_Iso" + std::to_string(l2_reliso) : "") +
                                                ((dphi != -1)? "_dphi" + std::to_string(dphi) : "") +
                                                ((dR != -1)? "_dR" + std::to_string(dR) : "") +
                                                ((upperdR != -1)? "_dR" + std::to_string(upperdR) : "") +
                                                "_mll" + std::to_string(mll) +
                                                ((lowermll != -1)? "_mll" + std::to_string(lowermll) : "") +
                                                ((applyLepVeto)? "_lVeto" : "") +
                                                ((applyOneJet)? "_1jet" : "") +
                                                ((jettagval != -1)? "_pfn" + std::to_string(jettagval) : "");
                                            (*hists)[name] = new TH1F(name, ";;Events", 1, 0, 2);
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

    // give the bin the name of the boolean it represents
    for( it = hists->begin(); it != hists->end(); it++){
        if(it->first.Index("_Bool_") != -1){
            TH1* h = it->second;
            h->GetXaxis()->SetBinLabel(1, h->GetName());
        }
    }
}

void full_analyzer::create_Bools_and_fill_Bool_hists(std::map<TString, TH1*>* hists, TString prefix, int i_leading, int i_subleading, bool base_selection)
{
    if(_1mu1displmu1jet) (*hists)[prefix+"_Bool_1mu1displmu1jet"]->Fill(1, event_weight);
    if(_1mu1displmu_PFN) (*hists)[prefix+"_Bool_1mu1displmu_PFN"]->Fill(1, event_weight);

    if(_1e1disple1jet) (*hists)[prefix+"_Bool_1e1disple1jet"]->Fill(1, event_weight);
    if(_1e1disple_PFN) (*hists)[prefix+"_Bool_1e1disple_PFN"]->Fill(1, event_weight);

    for(const double& l2_dxy : {0.02}){
        for(const double& l2_reliso : {1.5, -1.}){
            for(const double& dphi : {-1., 2.2, 2.4}){
                for(const double& dR : {-1., 2., 2.4}){
                    for(const double& upperdR : {-1., 5.5}){
                        for(const double& mll : {75., 80.}){
                            for(const double& lowermll : {-1., 20.}){
                                for(const bool& applyLepVeto : {false}){
                                    for(const bool& applyOneJet : {true, false}){
                                        for(const double& jettagval : {-1., 0.8, 0.9, 0.95}){
                                            TString name = (TString) prefix + "_Bool" +
                                                "_dxy" + std::to_string(l2_dxy) +
                                                ((l2_reliso != -1)? "_Iso" + std::to_string(l2_reliso) : "") +
                                                ((dphi != -1)? "_dphi" + std::to_string(dphi) : "") +
                                                ((dR != -1)? "_dR" + std::to_string(dR) : "") +
                                                ((upperdR != -1)? "_dR" + std::to_string(upperdR) : "") +
                                                "_mll" + std::to_string(mll) +
                                                ((lowermll != -1)? "_mll" + std::to_string(lowermll) : "") +
                                                ((applyLepVeto)? "_lVeto" : "") +
                                                ((applyOneJet)? "_1jet" : "") +
                                                ((jettagval != -1)? "_pfn" + std::to_string(jettagval) : "");
                                            if(create_sigreg_bool(i_leading, i_subleading, base_selection, l2_dxy, l2_reliso, dphi, dR, upperdR, mll, lowermll, applyLepVeto, applyOneJet, jettagval)) (*hists)[name]->Fill(1, event_weight);
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
