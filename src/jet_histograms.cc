//////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include <iostream>

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::add_jet_histograms(map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_jet1_pt"]                     = new TH1F(prefix+"_jet1_pt", ";jet_1 #it{p}_{T};Events", 60, 0, 140); 
    
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
    (*hists)[prefix+"_jetl2_ChargedEmFraction"]     = new TH1F(prefix+"_jetl2_ChargedEmFraction", ";closestJet(l_{2}) Charged Hadron Fraction;Events", 30, 0, 1);
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
void full_analyzer::fill_HNLtagger_tree(HNLtagger& hnltagger, int i_jet)
{
    if(i_jet == -1) return;
    hnltagger._JetIsFromHNL = get_JetIsFromHNL(i_jet);
    hnltagger._JetPt        = _jetPt[i_jet];
    hnltagger._JetEta       = _jetEta[i_jet];
    hnltagger._nJetConstituents                    = _nJetConstituents[i_jet];//Constituents[i_jet];
    for(unsigned i = 0; i < _nJetConstituents[i_jet]; i++){
        hnltagger._JetConstituentPt[i]                 = _JetConstituentPt[i_jet][i];
        hnltagger._JetConstituentEta[i]                = _JetConstituentEta[i_jet][i];
        hnltagger._JetConstituentPhi[i]                = _JetConstituentPhi[i_jet][i];
        hnltagger._JetConstituentMass[i]               = _JetConstituentMass[i_jet][i];
        hnltagger._JetConstituentPdgId[i]              = _JetConstituentPdgId[i_jet][i];
        hnltagger._JetConstituentCharge[i]             = _JetConstituentCharge[i_jet][i];
        hnltagger._JetConstituentdxySig[i]             = _JetConstituentdxySig[i_jet][i];
        hnltagger._JetConstituentdzSig[i]              = _JetConstituentdzSig[i_jet][i];
        hnltagger._JetConstituentsNumberOfHits[i]      = _JetConstituentsNumberOfHits[i_jet][i];
        hnltagger._JetConstituentsNumberOfPixelHits[i] = _JetConstituentsNumberOfPixelHits[i_jet][i];
        hnltagger._JetConstituentsHasTrack[i]          = _JetConstituentsHasTrack[i_jet][i];
    }
    for(unsigned i = _nJetConstituents[i_jet]; i < 50; i++){
        hnltagger._JetConstituentPt[i]                 = 0;
        hnltagger._JetConstituentEta[i]                = 0;
        hnltagger._JetConstituentPhi[i]                = 0;
        hnltagger._JetConstituentMass[i]               = 0;
        hnltagger._JetConstituentPdgId[i]              = 0;
        hnltagger._JetConstituentCharge[i]             = 0;
        hnltagger._JetConstituentdxySig[i]             = 0;
        hnltagger._JetConstituentdzSig[i]              = 0;
        hnltagger._JetConstituentsNumberOfHits[i]      = 0;
        hnltagger._JetConstituentsNumberOfPixelHits[i] = 0;
        hnltagger._JetConstituentsHasTrack[i]          = 0;
    }
    hnltagger.HNLtagger_tree->Fill();
}
