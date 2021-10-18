#include "../interface/full_analyzer.h"

double KshortMass = 0.49761;


void full_analyzer::Conversion_study(std::map<TString, TH1*>* hists)
{
    //event selection
    if(i_leading == -1 or i_subleading == -1)   return;
    if(_lFlavor[i_leading] != 1)                return;
    if(_lFlavor[i_leading] != 1)                return;
    if(_lCharge[i_leading] == _lCharge[i_subleading]) return;
    if(_lPt[i_leading] < 30)                    return;
    if(_lPt[i_subleading] < 20)                 return;
    if(std::abs(mll - 91.2) > 10)               return;

    std::vector<unsigned> displacedElectronID;
    for(unsigned i = 0; i < _nLight; i++){
        if(i == (unsigned)i_leading or i == (unsigned)i_subleading) continue;
        if(IsDisplacedElectronID(i) and _lIVF_match[i]) displacedElectronID.push_back(i);
    }
    if(displacedElectronID.size() < 2) return;

    for(const auto& i : displacedElectronID){
        for(const auto& j : displacedElectronID){
            if(i == j) continue;
            if(std::abs(_IVF_x[i] - _IVF_x[j]) < 0.01) (*hists)["Conversion_count"]->Fill(0.5);
        }
    }
}

void full_analyzer::Kshort_study(std::map<TString, TH1*>* hists, HNLtagger& hnltagger_Kshort, PFNReader& pfn_e_LowMass, PFNReader& pfn_e_HighMass, PFNReader& pfn_mu_LowMass, PFNReader& pfn_mu_HighMass, double ev_weight)
{
    //Perform event selection
    if(i_leading == -1 or i_subleading == -1)   return;
    if(_lFlavor[i_leading] != 1)                return;
    if(_lFlavor[i_leading] != 1)                return;
    if(_lCharge[i_leading] == _lCharge[i_subleading]) return;
    if(_lPt[i_leading] < 30)                    return;
    if(_lPt[i_subleading] < 20)                 return;
    if(std::abs(mll - 91.2) > 10)               return;
    (*hists)["_mm_Kshort_nBJets"]->Fill(nLooseBJet, ev_weight);
    if(nLooseBJet >= 1)                         return;

    fill_Kshort_EvSel_histograms(hists, "_mm_Kshort", ev_weight);
 
    //run for every Kshort candidate
    nKshort = 0;
    for(unsigned i_V0 = 0; i_V0 < _nV0s; i_V0++){
        if(_V0Type[i_V0] < 0.5 or _V0Type[i_V0] > 1.5) continue;
        if(std::abs(_V0InvMass[i_V0] - KshortMass) > 0.07) continue;
        int i_jetKshort = find_jet_closest_to_Kshort_pion(0.7, i_V0);
        if(i_jetKshort == -1) continue;//only consider events that have a jet near Kshort

        //Apply tracking scale factors
        if(!isData) ev_weight *= lsfreader_displ_m_SV->get_LSF(_V0Pt[i_V0], get_xy_distance(_PV_x, _PV_y, _V0X[i_V0], _V0Y[i_V0]));

        fill_Kshort_HNLtagger_tree(hnltagger_Kshort, i_V0, i_jetKshort);
        std::map<int, std::map<double, double>> JetTagVal_Kshort_e = GetJetTagVals_LowAndHighMass(hnltagger_Kshort, pfn_e_LowMass, pfn_e_HighMass);
        std::map<int, std::map<double, double>> JetTagVal_Kshort_mu = GetJetTagVals_LowAndHighMass(hnltagger_Kshort, pfn_mu_LowMass, pfn_mu_HighMass);

        //for(const auto& tagss : JetTagVal_Kshort_e){
        //    for(const auto& tags : tagss.second){
        //        std::cout << "Electron M, V2, score: " << tagss.first << " " << tags.first << " " << tags.second << std::endl;
        //    }
        //}
        //for(const auto& tagss : JetTagVal_Kshort_mu){
        //    for(const auto& tags : tagss.second){
        //        std::cout << "Muon M, V2, score: " << tagss.first << " " << tags.first << " " << tags.second << std::endl;
        //    }
        //}

        if(std::abs(_V0InvMass[i_V0] - KshortMass) < 0.015) fill_Kshort_histograms(hists, "_mm_Kshort", ev_weight, i_V0, i_jetKshort, JetTagVal_Kshort_e, JetTagVal_Kshort_mu);
        else fill_Kshort_histograms(hists, "_mm_Kshort_outsideMSV", ev_weight, i_V0, i_jetKshort, JetTagVal_Kshort_e, JetTagVal_Kshort_mu);
        if(_V0PtPos[i_V0] < 2 or _V0PtNeg[i_V0] < 2) continue;
        if(std::abs(_V0InvMass[i_V0] - KshortMass) < 0.015) fill_Kshort_histograms(hists, "_mm_Kshort_2GeV", ev_weight, i_V0, i_jetKshort, JetTagVal_Kshort_e, JetTagVal_Kshort_mu);
        else fill_Kshort_histograms(hists, "_mm_Kshort_2GeV_outsideMSV", ev_weight, i_V0, i_jetKshort, JetTagVal_Kshort_e, JetTagVal_Kshort_mu);
        nKshort++;
    }
}

int full_analyzer::find_jet_closest_to_Kshort_pion(double mindR, unsigned i_V0){
    int i_jetKshort = -1;
    double dRPos, dRNeg;
    for(unsigned i_jet = 0; i_jet < _nJets; i_jet++){
        if(IsTightJetID(i_jet, "_jetPt")){
            LorentzVector vec_pionPos(_V0PtPos[i_V0], _V0EtaPos[i_V0], _V0PhiPos[i_V0], _V0PtPos[i_V0]);
            LorentzVector vec_pionNeg(_V0PtNeg[i_V0], _V0EtaNeg[i_V0], _V0PhiNeg[i_V0], _V0PtNeg[i_V0]);
            LorentzVector vec_jet(_jetPt[i_jet], _jetEta[i_jet], _jetPhi[i_jet], _jetPt[i_jet]);
            dRPos = deltaR(vec_pionPos, vec_jet);
            dRNeg = deltaR(vec_pionNeg, vec_jet);
            if(dRPos < mindR or dRNeg < mindR){ i_jetKshort = (int)i_jet; mindR = std::min(dRPos, dRNeg);}
        }
    }
    return i_jetKshort;
}

void full_analyzer::add_Kshort_histograms(std::map<TString, TH1*>* hists, TString prefix)
{
    (*hists)[prefix+"_l1_pt"]                           = new TH1F(prefix+"_l1_pt", ";l_{1} #it{p}_{T} [GeV];Events", 40, 0, 80);
    (*hists)[prefix+"_l2_pt"]                           = new TH1F(prefix+"_l2_pt", ";l_{2} #it{p}_{T} [GeV];Events", 40, 0, 80);
    (*hists)[prefix+"_mll"] = new TH1F(prefix+"_mll", ";#it{m}_{ll} [GeV];Events", 40, 70, 110);
    (*hists)[prefix+"_nBJets"] = new TH1F(prefix+"_nBJets", ";Nr. B-jets;Events", 5, 0, 5);
    (*hists)[prefix+"_nKs"] = new TH1F(prefix+"_nKs", ";Nr. Kshort;Events", 10, 0, 10);
    (*hists)[prefix+"_PFNmu_LowMass"] = new TH1F(prefix+"_PFNmu_LowMass", ";Muon Low Mass PFN score;Events", 40, 0, 1);
    (*hists)[prefix+"_PFNmu_HighMass"] = new TH1F(prefix+"_PFNmu_HighMass", ";Muon High Mass PFN score;Events", 40, 0, 1);
    (*hists)[prefix+"_PFNe_LowMass"] = new TH1F(prefix+"_PFNe_LowMass", ";Electron Low Mass PFN score;Events", 40, 0, 1);
    (*hists)[prefix+"_PFNe_HighMass"] = new TH1F(prefix+"_PFNe_HighMass", ";Electron High Mass PFN score;Events", 40, 0, 1);

    (*hists)[prefix+"_V0Mass"] = new TH1F(prefix+"_V0Mass", ";SV Mass [GeV];Events", 40, 0.4, 0.6);
    (*hists)[prefix+"_V0normchi2"] = new TH1F(prefix+"_V0normchi2", ";Normalized #chi^{2};Events", 40, 0, 12);
    (*hists)[prefix+"_Lxy"] = new TH1F(prefix+"_Lxy", ";L_{xy} [cm];Events", 40, 0, 50);
    (*hists)[prefix+"_JetPt"] = new TH1F(prefix+"_JetPt", ";Jet Pt [GeV];Events", 40, 0, 80);
    (*hists)[prefix+"_JetEta"] = new TH1F(prefix+"_JetEta", ";Jet #eta;Events", 40, -3, 3);
    (*hists)[prefix+"_JetPhi"] = new TH1F(prefix+"_JetPhi", ";Jet #phi;Events", 40, -3.14, 3.14);
    (*hists)[prefix+"_lPt"] = new TH1F(prefix+"_lPt", ";l_{2} Pt [GeV];Events", 40, 0, 50);
    (*hists)[prefix+"_lEta"] = new TH1F(prefix+"_lEta", ";l_{2} #eta;Events", 40, -3, 3);
    (*hists)[prefix+"_lPhi"] = new TH1F(prefix+"_lPhi", ";l_{2} #phi;Events", 40, -3.14, 3.14);
    (*hists)[prefix+"_ldxy_sgnlog"] = new TH1F(prefix+"_ldxy_sgnlog", ";l_{2} dxy;Events", 40, 0, 1);
    (*hists)[prefix+"_ldz_sgnlog"] = new TH1F(prefix+"_ldz_sgnlog", ";l_{2} dz;Events", 40, 0, 1);
    (*hists)[prefix+"_l3dIPSig"] = new TH1F(prefix+"_l3dIPSig", ";l_{2} 3dIPSig;Events", 40, 0, 10);
    (*hists)[prefix+"_lrelIso"] = new TH1F(prefix+"_lrelIso", ";l_{2} RelIso;Events", 40, 0, 10);
    (*hists)[prefix+"_lptRel"] = new TH1F(prefix+"_lptRel", ";l_{2} PtRel;Events", 40, 0, 10);
    (*hists)[prefix+"_lptRatio"] = new TH1F(prefix+"_lptRatio", ";l_{2} PtRatio;Events", 40, 0, 1);
    (*hists)[prefix+"_lNPixHits"] = new TH1F(prefix+"_lNPixHits", ";l_{2} Nr. of Pixel Hits;Events", 10, 0, 10);
    (*hists)[prefix+"_Lxyz"] = new TH1F(prefix+"_Lxyz", ";L_{xyz} [cm];Events", 40, 0, 60);
    (*hists)[prefix+"_V0Pt"] = new TH1F(prefix+"_V0Pt", ";SV Pt [GeV];Events", 40, 0, 50);
    (*hists)[prefix+"_V0Eta"] = new TH1F(prefix+"_V0Eta", ";SV #eta;Events", 40, -3, 3);
    (*hists)[prefix+"_V0Phi"] = new TH1F(prefix+"_V0Phi", ";SV #phi;Events", 40, -3.14, 3.14);
    (*hists)[prefix+"_nJetConstituents"] = new TH1F(prefix+"_nJetConstituents", ";Nr. of Jet Constituents;Events", 20, 0, 20);
    (*hists)[prefix+"_dRljet"] = new TH1F(prefix+"_dRljet", ";#Delta R (l_{2}, jet);Events", 40, 0, 0.75);
    (*hists)[prefix+"_JetConstituentPt"] = new TH1F(prefix+"_JetConstituentPt", ";Jet Constituent Pt;Events", 40, 0, 50);
    (*hists)[prefix+"_JetConstituentEta"] = new TH1F(prefix+"_JetConstituentEta", ";Jet Constituent #eta;Events", 40, -3, 3);
    (*hists)[prefix+"_JetConstituentPhi"] = new TH1F(prefix+"_JetConstituentPhi", ";Jet Constituent #phi;Events", 40, -3.14, 3.14);
    (*hists)[prefix+"_JetConstituentPdgId"] = new TH1F(prefix+"_JetConstituentPdgId", ";Jet Constituent pdgId;Events", 10, 0, 10);
    (*hists)[prefix+"_JetConstituentCharge"] = new TH1F(prefix+"_JetConstituentCharge", ";Jet Constituent Charge;Events", 3, -1, 2);
    (*hists)[prefix+"_JetConstituentdxy_sgnlog"] = new TH1F(prefix+"_JetConstituentdxy_sgnlog", ";Jet Constituent dxy;Events", 40, -3, 3);
    (*hists)[prefix+"_JetConstituentdxyErr"] = new TH1F(prefix+"_JetConstituentdxyErr", ";Jet Constituent dxyErr;Events", 40, 0, 0.5);
    (*hists)[prefix+"_JetConstituentdz_sgnlog"] = new TH1F(prefix+"_JetConstituentdz_sgnlog", ";Jet Constituent dz;Events", 40, -3, 3);
    (*hists)[prefix+"_JetConstituentdzErr"] = new TH1F(prefix+"_JetConstituentdzErr", ";Jet Constituent dzErr;Events", 40, 0, 0.5);
    (*hists)[prefix+"_JetConstituentNHits"] = new TH1F(prefix+"_JetConstituentNHits", ";Jet Constituent Nr. Hits;Events", 20, 0, 20);
    (*hists)[prefix+"_JetConstituentNPixHits"] = new TH1F(prefix+"_JetConstituentNPixHits", ";Jet Constituent Nr. PixelHits;Events", 10, 0, 10);
}

void full_analyzer::fill_Kshort_EvSel_histograms(std::map<TString, TH1*>* hists, TString prefix, double event_weight)
{
    (*hists)[prefix+"_l1_pt"]->Fill(_lPt[i_leading], event_weight);
    (*hists)[prefix+"_l2_pt"]->Fill(_lPt[i_subleading], event_weight);
    (*hists)[prefix+"_mll"]->Fill(mll, event_weight);
    (*hists)[prefix+"_nKs"]->Fill(nKshort, event_weight);
}

void full_analyzer::fill_Kshort_histograms(std::map<TString, TH1*>* hists, TString prefix, double event_weight, unsigned i_V0, unsigned i_jetKshort, std::map<int, std::map<double, double>> JetTagVal_Kshort_e, std::map<int, std::map<double, double>> JetTagVal_Kshort_mu)
{
    //std::cout << "ok1" << std::endl;
    (*hists)[prefix+"_PFNmu_LowMass"]->Fill(JetTagVal_Kshort_mu[5][2e-6], event_weight);
    (*hists)[prefix+"_PFNmu_HighMass"]->Fill(JetTagVal_Kshort_mu[10][2e-6], event_weight);
    (*hists)[prefix+"_PFNe_LowMass"]->Fill(JetTagVal_Kshort_e[5][2e-6], event_weight);
    (*hists)[prefix+"_PFNe_HighMass"]->Fill(JetTagVal_Kshort_e[10][2e-6], event_weight);

    //std::cout << "ok2" << std::endl;
    //SV related variables
    (*hists)[prefix+"_Lxyz"]->Fill(get_xyz_distance(_PV_x, _PV_y, _PV_z, _V0X[i_V0], _V0Y[i_V0], _V0Z[i_V0]), event_weight);
    (*hists)[prefix+"_Lxy"]->Fill(get_xy_distance(_PV_x, _PV_y, _V0X[i_V0], _V0Y[i_V0]), event_weight);
    (*hists)[prefix+"_V0normchi2"]->Fill(_V0VtxNormChi2[i_V0], event_weight);
    (*hists)[prefix+"_V0Mass"]->Fill(_V0InvMass[i_V0], event_weight);
    (*hists)[prefix+"_V0Pt"]->Fill(_V0Pt[i_V0], event_weight);
    (*hists)[prefix+"_V0Eta"]->Fill(_V0Eta[i_V0], event_weight);
    (*hists)[prefix+"_V0Phi"]->Fill(_V0Phi[i_V0], event_weight);
    //std::cout << "ok3" << std::endl;

    (*hists)[prefix+"_nJetConstituents"]->Fill(_nJetConstituents[i_jetKshort], event_weight);//Constituents[i_jetKshort];
    //std::cout << "ok4" << std::endl;
    for(unsigned i = 0; i < _nJetConstituents[i_jetKshort]; i++){
        (*hists)[prefix+"_JetConstituentPt"]->Fill( _JetConstituentPt[i_jetKshort][i], event_weight);
        (*hists)[prefix+"_JetConstituentEta"]->Fill( _JetConstituentEta[i_jetKshort][i], event_weight);
        (*hists)[prefix+"_JetConstituentPhi"]->Fill( _JetConstituentPhi[i_jetKshort][i], event_weight);
        (*hists)[prefix+"_JetConstituentPdgId"]->Fill( get_reducedPdgId(_JetConstituentPdgId[i_jetKshort][i]), event_weight);
        (*hists)[prefix+"_JetConstituentCharge"]->Fill( _JetConstituentCharge[i_jetKshort][i], event_weight);
        (*hists)[prefix+"_JetConstituentdxy_sgnlog"]->Fill( get_signedLog(_JetConstituentdxy[i_jetKshort][i]), event_weight);
        (*hists)[prefix+"_JetConstituentdz_sgnlog"]->Fill( get_signedLog(_JetConstituentdz[i_jetKshort][i]), event_weight);
        (*hists)[prefix+"_JetConstituentdxyErr"]->Fill( (std::isinf(_JetConstituentdxyErr[i_jetKshort][i]))? -1 : _JetConstituentdxyErr[i_jetKshort][i], event_weight);  //Rarely, dxy(z)Err were infinite, keras didn't like this
        (*hists)[prefix+"_JetConstituentdzErr"]->Fill( (std::isinf(_JetConstituentdzErr[i_jetKshort][i]))? -1 : _JetConstituentdzErr[i_jetKshort][i], event_weight);
        (*hists)[prefix+"_JetConstituentNHits"]->Fill(_JetConstituentNumberOfHits[i_jetKshort][i], event_weight);
        (*hists)[prefix+"_JetConstituentNPixHits"]->Fill(_JetConstituentNumberOfPixelHits[i_jetKshort][i], event_weight);
    }
    //std::cout << "ok5" << std::endl;

    //identify highest pt track, to be used as the lepton proxy
    if(_V0PtPos[i_V0] > _V0PtNeg[i_V0]){
    //std::cout << "ok6.1" << std::endl;
        //lepton related variables, filled with pion proxy
        (*hists)[prefix+"_lPt"]->Fill(_V0PtPos[i_V0], event_weight);
        (*hists)[prefix+"_lEta"]->Fill(_V0EtaPos[i_V0], event_weight);
        (*hists)[prefix+"_lPhi"]->Fill(_V0PhiPos[i_V0], event_weight);
        (*hists)[prefix+"_ldxy_sgnlog"]->Fill(get_signedLog(_V0D0Pos[i_V0]), event_weight);
        (*hists)[prefix+"_ldz_sgnlog"]->Fill(get_signedLog(_V0DzPos[i_V0]), event_weight);
        (*hists)[prefix+"_l3dIPSig"]->Fill(_V0TransIPSigPos[i_V0], event_weight);
        (*hists)[prefix+"_lrelIso"]->Fill(_V0IsoPos[i_V0], event_weight);
        (*hists)[prefix+"_lptRel"]->Fill(_V0PtRelPos[i_V0], event_weight);
        (*hists)[prefix+"_lptRatio"]->Fill(_V0PtRatioPos[i_V0], event_weight);
        (*hists)[prefix+"_lNPixHits"]->Fill(_V0NPixHitsPos[i_V0], event_weight);
    //std::cout << "ok7.1" << std::endl;
    

        LorentzVector vec_pion(_V0PtPos[i_V0], _V0EtaPos[i_V0], _V0PhiPos[i_V0], _V0PtPos[i_V0]);
        LorentzVector vec_jet(_jetPt[i_jetKshort], _jetEta[i_jetKshort], _jetPhi[i_jetKshort], _jetPt[i_jetKshort]);
        (*hists)[prefix+"_dRljet"]->Fill(deltaR(vec_pion, vec_jet), event_weight);
        (*hists)[prefix+"_JetPt"]->Fill(_jetPt[i_jetKshort], event_weight);
        (*hists)[prefix+"_JetEta"]->Fill(_jetEta[i_jetKshort], event_weight);
        (*hists)[prefix+"_JetPhi"]->Fill(_jetPhi[i_jetKshort], event_weight);
        
    //std::cout << "ok8.1" << std::endl;
    }else{
    //std::cout << "ok6.2" << std::endl;
        //lepton related variables, filled with pion proxy
        (*hists)[prefix+"_lPt"]->Fill(_V0PtNeg[i_V0], event_weight);
        (*hists)[prefix+"_lEta"]->Fill(_V0EtaNeg[i_V0], event_weight);
        (*hists)[prefix+"_lPhi"]->Fill(_V0PhiNeg[i_V0], event_weight);
        (*hists)[prefix+"_ldxy_sgnlog"]->Fill(get_signedLog(_V0D0Neg[i_V0]), event_weight);
        (*hists)[prefix+"_ldz_sgnlog"]->Fill(get_signedLog(_V0DzNeg[i_V0]), event_weight);
        (*hists)[prefix+"_l3dIPSig"]->Fill(_V0TransIPSigNeg[i_V0], event_weight);
        (*hists)[prefix+"_lrelIso"]->Fill(_V0IsoNeg[i_V0], event_weight);
        (*hists)[prefix+"_lptRel"]->Fill(_V0PtRelNeg[i_V0], event_weight);
        (*hists)[prefix+"_lptRatio"]->Fill(_V0PtRatioNeg[i_V0], event_weight);
        (*hists)[prefix+"_lNPixHits"]->Fill(_V0NPixHitsNeg[i_V0], event_weight);
    
    //std::cout << "ok7.2" << std::endl;

        LorentzVector vec_pion(_V0PtNeg[i_V0], _V0EtaNeg[i_V0], _V0PhiNeg[i_V0], _V0PtNeg[i_V0]);
        LorentzVector vec_jet(_jetPt[i_jetKshort], _jetEta[i_jetKshort], _jetPhi[i_jetKshort], _jetPt[i_jetKshort]);
        (*hists)[prefix+"_dRljet"]->Fill(deltaR(vec_pion, vec_jet), event_weight);
        (*hists)[prefix+"_JetPt"]->Fill(_jetPt[i_jetKshort], event_weight);
        (*hists)[prefix+"_JetEta"]->Fill(_jetEta[i_jetKshort], event_weight);
        (*hists)[prefix+"_JetPhi"]->Fill(_jetPhi[i_jetKshort], event_weight);
    //std::cout << "ok8.2" << std::endl;
    }

}


void full_analyzer::fill_Kshort_HNLtagger_tree(HNLtagger& hnltagger, unsigned i_V0, unsigned i_jetKshort)
{

    hnltagger.isValid = true;

    //general variables not really applicable to Kshort case
    hnltagger._gen_Nmass    = HNL_param->mass;
    hnltagger._gen_NV2      = HNL_param->V2;
    hnltagger._gen_Nctau    = HNL_param->ctau;
    hnltagger._is2016       = _is2016;
    hnltagger._is2017       = _is2017;
    hnltagger._is2018       = _is2018;
    hnltagger._JetIsFromHNL = get_JetIsFromHNL(i_jetl2);

    //identify highest pt track, to be used as the lepton proxy
    if(_V0PtPos[i_V0] > _V0PtNeg[i_V0]){
        //lepton related variables, filled with pion proxy
        hnltagger._lPt                   = _V0PtPos[i_V0];
        hnltagger._lPt_log               = log(_V0PtPos[i_V0]);
        hnltagger._lEta                  = _V0EtaPos[i_V0];
        hnltagger._lPhi                  = _V0PhiPos[i_V0];
        hnltagger._ldxy                  = _V0D0Pos[i_V0];
        hnltagger._ldxy_log              = log(fabs(_V0D0Pos[i_V0]));
        hnltagger._ldxy_sgnlog           = get_signedLog(_V0D0Pos[i_V0]);
        hnltagger._ldz                   = _V0DzPos[i_V0];
        hnltagger._ldz_log               = log(fabs(_V0DzPos[i_V0]));
        hnltagger._ldz_sgnlog            = get_signedLog(_V0DzPos[i_V0]);
        hnltagger._l3dIPSig              = _V0TransIPSigPos[i_V0];
        hnltagger._l3dIPSig_log          = log(_V0TransIPSigPos[i_V0]);
        hnltagger._lrelIso               = _V0IsoPos[i_V0];
        hnltagger._lptRel                = _V0PtRelPos[i_V0];
        hnltagger._lptRel_log            = log(_V0PtRelPos[i_V0]);
        hnltagger._lptRatio              = _V0PtRatioPos[i_V0];
        hnltagger._lNumberOfHits         = _V0NHitsPos[i_V0];
        hnltagger._lNumberOfPixelHits    = _V0NPixHitsPos[i_V0];
    
        //SV related variables
        hnltagger._SV_PVSVdist     = get_xyz_distance(_PV_x, _PV_y, _PV_z, _V0X[i_V0], _V0Y[i_V0], _V0Z[i_V0]);
        hnltagger._SV_PVSVdist_2D  = get_xy_distance(_PV_x, _PV_y, _V0X[i_V0], _V0Y[i_V0]);
        hnltagger._SV_ntracks      = 2;//always 2 tracks
        hnltagger._SV_normchi2     = _V0VtxNormChi2[i_V0];
        hnltagger._SV_mass         = _V0InvMass[i_V0];
        hnltagger._SV_l1mass       = 0;
        hnltagger._SV_pt           = _V0Pt[i_V0];
        hnltagger._SV_pt_log       = log(_V0Pt[i_V0]);
        hnltagger._SV_eta          = _V0Eta[i_V0];
        hnltagger._SV_phi          = _V0Phi[i_V0];

        //l1 related stuff
        hnltagger._l1Pt            = _lPt[i_leading];
        hnltagger._l1Pt_log        = log(_lPt[i_leading]);
        hnltagger._l1Eta           = _lEta[i_leading];
        hnltagger._mll             = mll;
        hnltagger._mlljet          = 0;//maybe add it?
        hnltagger._dRll            = dRll;


        LorentzVector vec_pion(_V0PtPos[i_V0], _V0EtaPos[i_V0], _V0PhiPos[i_V0], _V0PtPos[i_V0]);
        LorentzVector vec_jet(_jetPt[i_jetKshort], _jetEta[i_jetKshort], _jetPhi[i_jetKshort], _jetPt[i_jetKshort]);
        hnltagger._dRljet       = deltaR(vec_pion, vec_jet);
        hnltagger._JetPt        = _jetPt[i_jetKshort];
        hnltagger._JetPt_log    = log(_jetPt[i_jetKshort]);
        hnltagger._JetEta       = _jetEta[i_jetKshort];
        hnltagger._JetPhi       = _jetPhi[i_jetKshort];
        

        hnltagger._nJetConstituents                    = _nJetConstituents[i_jetKshort];//Constituents[i_jetKshort];
        for(unsigned i = 0; i < _nJetConstituents[i_jetKshort]; i++){
            hnltagger._JetConstituentPt[i]                 = _JetConstituentPt[i_jetKshort][i];
            hnltagger._JetConstituentPt_log[i]             = log(_JetConstituentPt[i_jetKshort][i]);
            hnltagger._JetConstituentEta[i]                = _JetConstituentEta[i_jetKshort][i];
            hnltagger._JetConstituentPhi[i]                = _JetConstituentPhi[i_jetKshort][i];
            hnltagger._JetConstituentPdgId[i]              = get_reducedPdgId(_JetConstituentPdgId[i_jetKshort][i]);
            hnltagger._JetConstituentCharge[i]             = _JetConstituentCharge[i_jetKshort][i];
            hnltagger._JetConstituentdxy[i]                = _JetConstituentdxy[i_jetKshort][i];
            hnltagger._JetConstituentdxy_log[i]            = log(fabs(_JetConstituentdxy[i_jetKshort][i]));
            hnltagger._JetConstituentdxy_sgnlog[i]         = get_signedLog(_JetConstituentdxy[i_jetKshort][i]);
            hnltagger._JetConstituentdz[i]                 = _JetConstituentdz[i_jetKshort][i];
            hnltagger._JetConstituentdz_log[i]             = log(fabs(_JetConstituentdz[i_jetKshort][i]));
            hnltagger._JetConstituentdz_sgnlog[i]          = get_signedLog(_JetConstituentdz[i_jetKshort][i]);
            hnltagger._JetConstituentdxyErr[i]             = (std::isinf(_JetConstituentdxyErr[i_jetKshort][i]))? -1 : _JetConstituentdxyErr[i_jetKshort][i];  //Rarely, dxy(z)Err were infinite, keras didn't like this
            hnltagger._JetConstituentdzErr[i]              = (std::isinf(_JetConstituentdzErr[i_jetKshort][i]))? -1 : _JetConstituentdzErr[i_jetKshort][i];
            hnltagger._JetConstituentNumberOfHits[i]      = _JetConstituentNumberOfHits[i_jetKshort][i];
            hnltagger._JetConstituentNumberOfPixelHits[i] = _JetConstituentNumberOfPixelHits[i_jetKshort][i];
            hnltagger._JetConstituentHasTrack[i]          = _JetConstituentHasTrack[i_jetKshort][i];
            hnltagger._JetConstituentInSV[i]              = (_JetConstituentCharge[i_jetKshort][i] == 0)? -1 : is_track_in_sv(i_subleading, i_jetKshort, i);
            hnltagger._JetConstituentNmass[i]              = HNL_param->mass;
            hnltagger._JetConstituentNV2[i]                = HNL_param->V2;
            hnltagger._JetConstituentNctau[i]              = HNL_param->ctau;
        }
        for(unsigned i = _nJetConstituents[i_jetKshort]; i < 50; i++){
            hnltagger._JetConstituentPt[i]                 = 0;
            hnltagger._JetConstituentPt_log[i]             = 0;
            hnltagger._JetConstituentEta[i]                = 0;
            hnltagger._JetConstituentPhi[i]                = 0;
            hnltagger._JetConstituentPdgId[i]              = 0;
            hnltagger._JetConstituentCharge[i]             = 0;
            hnltagger._JetConstituentdxy[i]                = 0;
            hnltagger._JetConstituentdxy_log[i]            = 0;
            hnltagger._JetConstituentdxy_sgnlog[i]         = 0;
            hnltagger._JetConstituentdz[i]                 = 0;
            hnltagger._JetConstituentdz_log[i]             = 0;
            hnltagger._JetConstituentdz_sgnlog[i]          = 0;
            hnltagger._JetConstituentdxyErr[i]             = 0;
            hnltagger._JetConstituentdzErr[i]              = 0;
            hnltagger._JetConstituentNumberOfHits[i]      = 0;
            hnltagger._JetConstituentNumberOfPixelHits[i] = 0;
            hnltagger._JetConstituentHasTrack[i]          = 0;
            hnltagger._JetConstituentInSV[i]              = 0;
            hnltagger._JetConstituentNmass[i]             = 0;
            hnltagger._JetConstituentNV2[i]               = 0;
            hnltagger._JetConstituentNctau[i]             = 0;
        }
    }else{
        //lepton related variables, filled with pion proxy
        hnltagger._lPt                   = _V0PtNeg[i_V0];
        hnltagger._lPt_log               = log(_V0PtNeg[i_V0]);
        hnltagger._lEta                  = _V0EtaNeg[i_V0];
        hnltagger._lPhi                  = _V0PhiNeg[i_V0];
        hnltagger._ldxy                  = _V0D0Neg[i_V0];
        hnltagger._ldxy_log              = log(fabs(_V0D0Neg[i_V0]));
        hnltagger._ldxy_sgnlog           = get_signedLog(_V0D0Neg[i_V0]);
        hnltagger._ldz                   = _V0DzNeg[i_V0];
        hnltagger._ldz_log               = log(fabs(_V0DzNeg[i_V0]));
        hnltagger._ldz_sgnlog            = get_signedLog(_V0DzNeg[i_V0]);
        hnltagger._l3dIPSig              = _V0TransIPSigNeg[i_V0];
        hnltagger._l3dIPSig_log          = log(_V0TransIPSigNeg[i_V0]);
        hnltagger._lrelIso               = _V0IsoNeg[i_V0];
        hnltagger._lptRel                = _V0PtRelNeg[i_V0];
        hnltagger._lptRel_log            = log(_V0PtRelNeg[i_V0]);
        hnltagger._lptRatio              = _V0PtRatioNeg[i_V0];
        hnltagger._lNumberOfHits         = _V0NHitsNeg[i_V0];
        hnltagger._lNumberOfPixelHits    = _V0NPixHitsNeg[i_V0];
    
        //SV related variables
        hnltagger._SV_PVSVdist     = get_xyz_distance(_PV_x, _PV_y, _PV_z, _V0X[i_V0], _V0Y[i_V0], _V0Z[i_V0]);
        hnltagger._SV_PVSVdist_2D  = get_xy_distance(_PV_x, _PV_y, _V0X[i_V0], _V0Y[i_V0]);
        hnltagger._SV_ntracks      = 2;//always 2 tracks
        hnltagger._SV_normchi2     = _V0VtxNormChi2[i_V0];
        hnltagger._SV_mass         = _V0InvMass[i_V0];
        hnltagger._SV_l1mass       = 0;
        hnltagger._SV_pt           = _V0Pt[i_V0];
        hnltagger._SV_pt_log       = log(_V0Pt[i_V0]);
        hnltagger._SV_eta          = _V0Eta[i_V0];
        hnltagger._SV_phi          = _V0Phi[i_V0];

        //l1 related stuff
        hnltagger._l1Pt            = _lPt[i_leading];
        hnltagger._l1Pt_log        = log(_lPt[i_leading]);
        hnltagger._l1Eta           = _lEta[i_leading];
        hnltagger._mll             = mll;
        hnltagger._mlljet          = 0;//maybe add it?
        hnltagger._dRll            = dRll;


        LorentzVector vec_pion(_V0PtNeg[i_V0], _V0EtaNeg[i_V0], _V0PhiNeg[i_V0], _V0PtNeg[i_V0]);
        LorentzVector vec_jet(_jetPt[i_jetKshort], _jetEta[i_jetKshort], _jetPhi[i_jetKshort], _jetPt[i_jetKshort]);
        hnltagger._dRljet       = deltaR(vec_pion, vec_jet);
        hnltagger._JetPt        = _jetPt[i_jetKshort];
        hnltagger._JetPt_log    = log(_jetPt[i_jetKshort]);
        hnltagger._JetEta       = _jetEta[i_jetKshort];
        hnltagger._JetPhi       = _jetPhi[i_jetKshort];
        

        hnltagger._nJetConstituents                    = _nJetConstituents[i_jetKshort];//Constituents[i_jetKshort];
        for(unsigned i = 0; i < _nJetConstituents[i_jetKshort]; i++){
            hnltagger._JetConstituentPt[i]                 = _JetConstituentPt[i_jetKshort][i];
            hnltagger._JetConstituentPt_log[i]             = log(_JetConstituentPt[i_jetKshort][i]);
            hnltagger._JetConstituentEta[i]                = _JetConstituentEta[i_jetKshort][i];
            hnltagger._JetConstituentPhi[i]                = _JetConstituentPhi[i_jetKshort][i];
            hnltagger._JetConstituentPdgId[i]              = get_reducedPdgId(_JetConstituentPdgId[i_jetKshort][i]);
            hnltagger._JetConstituentCharge[i]             = _JetConstituentCharge[i_jetKshort][i];
            hnltagger._JetConstituentdxy[i]                = _JetConstituentdxy[i_jetKshort][i];
            hnltagger._JetConstituentdxy_log[i]            = log(fabs(_JetConstituentdxy[i_jetKshort][i]));
            hnltagger._JetConstituentdxy_sgnlog[i]         = get_signedLog(_JetConstituentdxy[i_jetKshort][i]);
            hnltagger._JetConstituentdz[i]                 = _JetConstituentdz[i_jetKshort][i];
            hnltagger._JetConstituentdz_log[i]             = log(fabs(_JetConstituentdz[i_jetKshort][i]));
            hnltagger._JetConstituentdz_sgnlog[i]          = get_signedLog(_JetConstituentdz[i_jetKshort][i]);
            hnltagger._JetConstituentdxyErr[i]             = (std::isinf(_JetConstituentdxyErr[i_jetKshort][i]))? -1 : _JetConstituentdxyErr[i_jetKshort][i];  //Rarely, dxy(z)Err were infinite, keras didn't like this
            hnltagger._JetConstituentdzErr[i]              = (std::isinf(_JetConstituentdzErr[i_jetKshort][i]))? -1 : _JetConstituentdzErr[i_jetKshort][i];
            hnltagger._JetConstituentNumberOfHits[i]      = _JetConstituentNumberOfHits[i_jetKshort][i];
            hnltagger._JetConstituentNumberOfPixelHits[i] = _JetConstituentNumberOfPixelHits[i_jetKshort][i];
            hnltagger._JetConstituentHasTrack[i]          = _JetConstituentHasTrack[i_jetKshort][i];
            hnltagger._JetConstituentInSV[i]              = (_JetConstituentCharge[i_jetKshort][i] == 0)? -1 : is_track_in_sv_Kshort(i_V0, i_jetKshort, i);
            hnltagger._JetConstituentNmass[i]              = HNL_param->mass;
            hnltagger._JetConstituentNV2[i]                = HNL_param->V2;
            hnltagger._JetConstituentNctau[i]              = HNL_param->ctau;
        }
        for(unsigned i = _nJetConstituents[i_jetKshort]; i < 50; i++){
            hnltagger._JetConstituentPt[i]                 = 0;
            hnltagger._JetConstituentPt_log[i]             = 0;
            hnltagger._JetConstituentEta[i]                = 0;
            hnltagger._JetConstituentPhi[i]                = 0;
            hnltagger._JetConstituentPdgId[i]              = 0;
            hnltagger._JetConstituentCharge[i]             = 0;
            hnltagger._JetConstituentdxy[i]                = 0;
            hnltagger._JetConstituentdxy_log[i]            = 0;
            hnltagger._JetConstituentdxy_sgnlog[i]         = 0;
            hnltagger._JetConstituentdz[i]                 = 0;
            hnltagger._JetConstituentdz_log[i]             = 0;
            hnltagger._JetConstituentdz_sgnlog[i]          = 0;
            hnltagger._JetConstituentdxyErr[i]             = 0;
            hnltagger._JetConstituentdzErr[i]              = 0;
            hnltagger._JetConstituentNumberOfHits[i]      = 0;
            hnltagger._JetConstituentNumberOfPixelHits[i] = 0;
            hnltagger._JetConstituentHasTrack[i]          = 0;
            hnltagger._JetConstituentInSV[i]              = 0;
            hnltagger._JetConstituentNmass[i]             = 0;
            hnltagger._JetConstituentNV2[i]               = 0;
            hnltagger._JetConstituentNctau[i]             = 0;
        }
    }
    if(hnltagger._JetIsFromHNL or isBackground or isData) hnltagger.HNLtagger_tree->Fill();
}

int full_analyzer::is_track_in_sv_Kshort(unsigned i_V0, int i_jet, int i_const)
{
    if(fabs(_V0PtPos[i_V0] - _JetConstituentPt[i_jet][i_const]) < 0.01 and fabs(_V0EtaPos[i_V0] - _JetConstituentEta[i_jet][i_const]) < 0.01) return 1;
    if(fabs(_V0PtNeg[i_V0] - _JetConstituentPt[i_jet][i_const]) < 0.01 and fabs(_V0EtaNeg[i_V0] - _JetConstituentEta[i_jet][i_const]) < 0.01) return 1;
    return 0;
}
