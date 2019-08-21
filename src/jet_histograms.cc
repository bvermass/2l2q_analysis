//////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include <iostream>

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::add_jet_histograms(map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_jet1_pt"]                     = new TH1F(prefix+"_jet1_pt", ";jet_{1} #it{p}_{T};Events", 20, 0, 100); 
    
    (*hists)[prefix+"_jetl2_index"]                 = new TH1F(prefix+"_jetl2_index", ";closestJet(l_{2}) Index;Events", 15, -1, 14);
    (*hists)[prefix+"_jetl2_pt"]                    = new TH1F(prefix+"_jetl2_pt", ";closestJet(l_{2}) #it{p}_{T} [GeV];Events", 30, 0, 140);
    (*hists)[prefix+"_jetl2_eta"]                   = new TH1F(prefix+"_jetl2_eta", ";closestJet(l_{2}) #eta;Events", 20, -3, 3);
    (*hists)[prefix+"_jetl2_phi"]                   = new TH1F(prefix+"_jetl2_phi", ";closestJet(l_{2}) #phi;Events", 20, -3.14, 3.14);
    (*hists)[prefix+"_jetl2_l2dR"]                  = new TH1F(prefix+"_jetl2_l2dR", ";closestJet(l_{2}) #Delta R;Events", 30, 0, 1);
    //(*hists)[prefix+"_jetl2_l2dphi"]                = new TH1F(prefix+"_jetl2_l2dphi", ";closestJet(l_{2}) #Delta #phi;Events", 30, 0, 3.14);
    (*hists)[prefix+"_jetl2_IsTightLepVeto"]        = new TH1F(prefix+"_jetl2_IsTightLepVeto", ";closestJet(l_{2}) TightLepVeto ID;Events", 2, 0, 2);
    (*hists)[prefix+"_jetl2_CsvV2"]                 = new TH1F(prefix+"_jetl2_CsvV2", ";closestJet(l_{2}) CsvV2;Events", 30, -0.1, 1.1);
    (*hists)[prefix+"_jetl2_DeepCsv_udsg"]          = new TH1F(prefix+"_jetl2_DeepCsv_udsg", ";closestJet(l_{2}) DeepCsv udsg;Events", 30, -0.1, 1.1);
    (*hists)[prefix+"_jetl2_DeepCsv_b"]             = new TH1F(prefix+"_jetl2_DeepCsv_b", ";closestJet(l_{2}) DeepCsv b;Events", 30, -0.1, 1.1);
    (*hists)[prefix+"_jetl2_DeepCsv_c"]             = new TH1F(prefix+"_jetl2_DeepCsv_c", ";closestJet(l_{2}) DeepCsv c;Events", 30, -0.1, 1.1);
    (*hists)[prefix+"_jetl2_DeepCsv_bb"]            = new TH1F(prefix+"_jetl2_DeepCsv_bb", ";closestJet(l_{2}) DeepCsv bb;Events", 30, -0.1, 1.1);
    (*hists)[prefix+"_jetl2_HadronFlavor"]          = new TH1F(prefix+"_jetl2_HadronFlavor", ";closestJet(l_{2}) HadronFlavor;Events", 6, 0, 6);
    (*hists)[prefix+"_jetl2_NeutralHadronFraction"] = new TH1F(prefix+"_jetl2_NeutralHadronFraction", ";closestJet(l_{2}) Neutral Hadron Fraction;Events", 30, 0, 1);
    (*hists)[prefix+"_jetl2_NeutralEmFraction"]     = new TH1F(prefix+"_jetl2_NeutralEmFraction", ";closestJet(l_{2}) Neutral Em Fraction;Events", 30, 0, 1);
    (*hists)[prefix+"_jetl2_ChargedHadronFraction"] = new TH1F(prefix+"_jetl2_ChargedHadronFraction", ";closestJet(l_{2}) Charged Hadron Fraction;Events", 30, 0, 1);
    (*hists)[prefix+"_jetl2_ChargedEmFraction"]     = new TH1F(prefix+"_jetl2_ChargedEmFraction", ";closestJet(l_{2}) Charged Em Fraction;Events", 30, 0, 1);
    (*hists)[prefix+"_jetl2_HFHadronFraction"]      = new TH1F(prefix+"_jetl2_HFHadronFraction", ";closestJet(l_{2}) HF Hadron Fraction;Events", 30, 0, 1);
    (*hists)[prefix+"_jetl2_HFEmFraction"]          = new TH1F(prefix+"_jetl2_HFEmFraction", ";closestJet(l_{2}) HF Em Fraction;Events", 30, 0, 1);
}

void full_analyzer::fill_jet_histograms(map<TString, TH1*>* hists, TString prefix, int i_subleading){
    if(i_leading_jet != -1) (*hists)[prefix+"_jet1_pt"]->Fill(_jetPt[i_leading_jet], event_weight);

    (*hists)[prefix+"_jetl2_index"]->Fill(i_closel2_jet, event_weight);
    if(i_closel2_jet != -1){ 
        (*hists)[prefix+"_jetl2_pt"]->Fill(_jetPt[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_eta"]->Fill(_jetEta[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_phi"]->Fill(_jetPhi[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_l2dR"]->Fill(get_dR_lepton_jet(i_subleading, i_closel2_jet), event_weight);
        (*hists)[prefix+"_jetl2_IsTightLepVeto"]->Fill(_jetIsTightLepVeto[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_CsvV2"]->Fill(_jetCsvV2[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_DeepCsv_udsg"]->Fill(_jetDeepCsv_udsg[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_DeepCsv_b"]->Fill(_jetDeepCsv_b[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_DeepCsv_c"]->Fill(_jetDeepCsv_c[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_DeepCsv_bb"]->Fill(_jetDeepCsv_bb[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_HadronFlavor"]->Fill(_jetHadronFlavor[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_NeutralHadronFraction"]->Fill(_jetNeutralHadronFraction[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_NeutralEmFraction"]->Fill(_jetNeutralEmFraction[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_ChargedHadronFraction"]->Fill(_jetChargedHadronFraction[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_ChargedEmFraction"]->Fill(_jetChargedEmFraction[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_HFHadronFraction"]->Fill(_jetHFHadronFraction[i_closel2_jet], event_weight);
        (*hists)[prefix+"_jetl2_HFEmFraction"]->Fill(_jetHFEmFraction[i_closel2_jet], event_weight);
    }
}

// fill function is part of full_analyzer class to access the tree variables
void full_analyzer::fill_HNLtagger_tree(HNLtagger& hnltagger, int i_lep, int i_jet)
{
    if(i_jet == -1) return;
    hnltagger._gen_Nmass    = _gen_Nmass;
    hnltagger._gen_NV       = _gen_NV;
    hnltagger._JetIsFromHNL = get_JetIsFromHNL(i_jet);
    hnltagger._JetPt        = _jetPt[i_jet];
    hnltagger._JetEta       = _jetEta[i_jet];
    hnltagger._lPt                   = _lPt[i_lep];
    hnltagger._lEta                  = _lEta[i_lep];
    hnltagger._lPhi                  = _lPhi[i_lep];
    hnltagger._ldxy                  = _dxy[i_lep];
    hnltagger._ldz                   = _dz[i_lep];
    hnltagger._l3dIPSig              = _3dIPSig[i_lep];
    hnltagger._lrelIso               = _relIso[i_lep];
    hnltagger._lptRel                = _ptRel[i_lep];
    hnltagger._lptRatio              = _ptRatio[i_lep];
    //hnltagger._lNumberOfHits         = (_lFlavor[i_lep] == 1)? _muNumberInnerHits[i_lep] : _lElectronMissingHits[i_lep];
    hnltagger._lNumberOfPixelHits    = (_lFlavor[i_lep] == 1)? _lNumberOfValidPixelHits[i_lep] : 0;

    hnltagger._SV_PVSVdist     = get_IVF_PVSVdist(i_lep);
    hnltagger._SV_PVSVdist_2D  = get_IVF_PVSVdist_2D(i_lep);
    hnltagger._SV_ntracks      = _IVF_ntracks[i_lep];
    hnltagger._SV_normchi2     = fabs(_IVF_chi2[i_lep]/_IVF_df[i_lep]);
    LorentzVector tracksum;
    for(unsigned i_track = 0; i_track < _IVF_ntracks[i_lep]; i_track++){
        LorentzVector tmptrack(_IVF_trackpt[i_lep][i_track], _IVF_tracketa[i_lep][i_track], _IVF_trackphi[i_lep][i_track], _IVF_trackE[i_lep][i_track]);
        tracksum += tmptrack;
    }
    hnltagger._SV_mass               = tracksum.mass();
    hnltagger._SV_pt                 = tracksum.pt();
    hnltagger._SV_eta                = tracksum.eta();
    hnltagger._SV_phi                = tracksum.phi();

    hnltagger._nJetConstituents                    = _nJetConstituents[i_jet];//Constituents[i_jet];
    for(unsigned i = 0; i < _nJetConstituents[i_jet]; i++){
        hnltagger._JetConstituentPt[i]                 = _JetConstituentPt[i_jet][i];
        hnltagger._JetConstituentEta[i]                = _JetConstituentEta[i_jet][i];
        hnltagger._JetConstituentPhi[i]                = _JetConstituentPhi[i_jet][i];
        hnltagger._JetConstituentPdgId[i]              = get_reducedPdgId(_JetConstituentPdgId[i_jet][i]);
        hnltagger._JetConstituentCharge[i]             = _JetConstituentCharge[i_jet][i];
        hnltagger._JetConstituentdxy[i]                = _JetConstituentdxy[i_jet][i];
        hnltagger._JetConstituentdz[i]                 = _JetConstituentdz[i_jet][i];
        hnltagger._JetConstituentdxyErr[i]             = (std::isinf(_JetConstituentdxyErr[i_jet][i]))? -1 : _JetConstituentdxyErr[i_jet][i];  //Rarely, dxy(z)Err were infinite, keras didn't like this
        hnltagger._JetConstituentdzErr[i]              = (std::isinf(_JetConstituentdzErr[i_jet][i]))? -1 : _JetConstituentdzErr[i_jet][i];
        hnltagger._JetConstituentNumberOfHits[i]      = _JetConstituentNumberOfHits[i_jet][i];
        hnltagger._JetConstituentNumberOfPixelHits[i] = _JetConstituentNumberOfPixelHits[i_jet][i];
        hnltagger._JetConstituentHasTrack[i]          = _JetConstituentHasTrack[i_jet][i];
        hnltagger._JetConstituentInSV[i]              = (_JetConstituentCharge[i_jet][i] == 0)? -1 : is_track_in_sv(i_lep, i_jet, i);
    }
    for(unsigned i = _nJetConstituents[i_jet]; i < 50; i++){
        hnltagger._JetConstituentPt[i]                 = 0;
        hnltagger._JetConstituentEta[i]                = 0;
        hnltagger._JetConstituentPhi[i]                = 0;
        hnltagger._JetConstituentPdgId[i]              = 0;
        hnltagger._JetConstituentCharge[i]             = 0;
        hnltagger._JetConstituentdxy[i]                = 0;
        hnltagger._JetConstituentdz[i]                 = 0;
        hnltagger._JetConstituentdxyErr[i]             = 0;
        hnltagger._JetConstituentdzErr[i]              = 0;
        hnltagger._JetConstituentNumberOfHits[i]      = 0;
        hnltagger._JetConstituentNumberOfPixelHits[i] = 0;
        hnltagger._JetConstituentHasTrack[i]          = 0;
        hnltagger._JetConstituentInSV[i]              = 0;
    }
    hnltagger.HNLtagger_tree->Fill();
}

int full_analyzer::is_track_in_sv(int i_lep, int i_jet, int i_const)
{
    for(unsigned i_track = 0; i_track < _IVF_ntracks[i_lep]; i_track++){
        if(fabs(_IVF_trackpt[i_lep][i_track] - _JetConstituentPt[i_jet][i_const]) < 0.01 and fabs(_IVF_tracketa[i_lep][i_track] - _JetConstituentEta[i_jet][i_const]) < 0.01) return 1;
    }
    return 0;
}

void full_analyzer::fill_HNLBDTtagger_tree(HNLBDTtagger& hnlbdttagger, int i_lep, int i_jet, double weight)
{
    if(i_jet == -1 or i_lep == -1 or !_lIVF_match[i_lep]) return;
    hnlbdttagger._gen_Nmass             = _gen_Nmass;
    hnlbdttagger._gen_NV                = _gen_NV;
    hnlbdttagger._JetIsFromHNL          = get_JetIsFromHNL(i_jet);
    hnlbdttagger._weight                = weight;
    hnlbdttagger._lPt                   = _lPt[i_lep];
    hnlbdttagger._lEta                  = _lEta[i_lep];
    hnlbdttagger._lPhi                  = _lPhi[i_lep];
    hnlbdttagger._ldxy                  = _dxy[i_lep];
    hnlbdttagger._ldz                   = _dz[i_lep];
    hnlbdttagger._l3dIPSig              = _3dIPSig[i_lep];
    hnlbdttagger._lrelIso               = _relIso[i_lep];
    hnlbdttagger._lptRel                = _ptRel[i_lep];
    hnlbdttagger._lptRatio              = _ptRatio[i_lep];
    //hnlbdttagger._lNumberOfHits         = (_lFlavor[i_lep] == 1)? _muNumberInnerHits[i_lep] : _lElectronMissingHits[i_lep];
    hnlbdttagger._lNumberOfPixelHits    = (_lFlavor[i_lep] == 1)? _lNumberOfValidPixelHits[i_lep] : 0;

    hnlbdttagger._JetPt                 = _jetPt[i_jet];
    hnlbdttagger._JetEta                = _jetEta[i_jet];
    hnlbdttagger._JetPhi                = _jetPhi[i_jet];
    hnlbdttagger._nJetConstituents      = _nJetConstituents[i_jet];//Constituents[i_jet];

    double jetdxysum = 0, jetdxysigsum = 0, jetdzsum = 0, jetdzsigsum = 0, jetchargesum = 0;
    LorentzVector jetmassVec;
    for(unsigned i = 0; i < _nJetConstituents[i_jet]; i++){
        LorentzVector constituentVec(_JetConstituentPt[i_jet][i], _JetConstituentEta[i_jet][i], _JetConstituentPhi[i_jet][i], sqrt( _JetConstituentMass[i_jet][i]*_JetConstituentMass[i_jet][i] + _JetConstituentPt[i_jet][i]*_JetConstituentPt[i_jet][i]));
        jetmassVec += constituentVec;
        if(_JetConstituentCharge[i] == 0) continue;
        jetdxysum    += fabs(_JetConstituentdxy[i_jet][i]);
        jetdxysigsum += fabs(_JetConstituentdxy[i_jet][i]/_JetConstituentdxyErr[i_jet][i]);
        jetdzsum     += fabs(_JetConstituentdz[i_jet][i]);
        jetdzsigsum  += fabs(_JetConstituentdz[i_jet][i]/_JetConstituentdzErr[i_jet][i]);
        jetchargesum += _JetConstituentCharge[i_jet][i];
    }
    hnlbdttagger._JetMass               = jetmassVec.mass();
    hnlbdttagger._JetdxySum             = jetdxysum;
    hnlbdttagger._JetdxySigSum          = jetdxysigsum;
    hnlbdttagger._JetdzSum              = jetdzsum;
    hnlbdttagger._JetdzSigSum           = jetdzsigsum;
    hnlbdttagger._JetChargeSum          = jetchargesum;

    hnlbdttagger._SV_ntracks            = _IVF_ntracks[i_lep];
    hnlbdttagger._SV_PVSVdist_2D        = get_IVF_PVSVdist_2D(i_lep);
    hnlbdttagger._SV_PVSVdist           = get_IVF_PVSVdist(i_lep);
    hnlbdttagger._SV_normchi2           = fabs(_IVF_chi2[i_lep]/_IVF_df[i_lep]);
    LorentzVector tracksum;
    for(unsigned i_track = 0; i_track < _IVF_ntracks[i_lep]; i_track++){
        LorentzVector tmptrack(_IVF_trackpt[i_lep][i_track], _IVF_tracketa[i_lep][i_track], _IVF_trackphi[i_lep][i_track], _IVF_trackE[i_lep][i_track]);
        tracksum += tmptrack;
    }
    hnlbdttagger._SV_mass               = tracksum.mass();
    hnlbdttagger._SV_pt                 = tracksum.pt();
    hnlbdttagger._SV_eta                = tracksum.eta();
    hnlbdttagger._SV_phi                = tracksum.phi();

    hnlbdttagger.HNLBDTtagger_tree->Fill();
}
