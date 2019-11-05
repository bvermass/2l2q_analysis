//////////////////////////////////////////////////////
//initializes MET related histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

void full_analyzer::add_MET_histograms(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_met"]                     = new TH1F(prefix+"_met", ";Type 1 E_{T}^{miss} [GeV];Events", 50, 0, 300); 
    (*hists)[prefix+"_metSM"]                   = new TH1F(prefix+"_metSM", ";Smeared E_{T}^{miss} [GeV];Events", 50, 0, 300); 
    (*hists)[prefix+"_metRaw"]                  = new TH1F(prefix+"_metRaw", ";Raw E_{T}^{miss} [GeV];Events", 50, 0, 300); 
    (*hists)[prefix+"_metPhi"]                  = new TH1F(prefix+"_metPhi", ";Type 1 E_{T}^{miss} Phi;Events", 50, -3.1415, 3.1415); 
    (*hists)[prefix+"_metSMPhi"]                = new TH1F(prefix+"_metSMPhi", ";Smeared E_{T}^{miss} Phi;Events", 50, -3.1415, 3.1415); 
    (*hists)[prefix+"_metRawPhi"]               = new TH1F(prefix+"_metRawPhi", ";Raw E_{T}^{miss} Phi;Events", 50, -3.1415, 3.1415); 
    
    (*hists)[prefix+"_nPV"]                     = new TH1F(prefix+"_nPV", ";nPV;Events", 100, 0, 100); 

    (*hists)[prefix+"_q_pt"]                    = new TH1F(prefix+"_q_pt", ";q #it{p}_{T} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_uT_pt"]                   = new TH1F(prefix+"_uT_pt", ";u_{T} [GeV];Events", 100, 0, 200);
    (*hists)[prefix+"_upara"]                   = new TH1F(prefix+"_upara", ";u_{#parallel} + q_{T} [GeV];Events", 100, -200, 200);
    (*hists)[prefix+"_uperp"]                   = new TH1F(prefix+"_uperp", ";u_{#perp}  [GeV];Events", 100, -200, 200);
    (*hists)[prefix+"_upara_frommetRaw"]        = new TH1F(prefix+"_upara_frommetRaw", ";u_{#parallel} + q_{T} [GeV] (Raw MET);Events", 100, -200, 200);
    (*hists)[prefix+"_uperp_frommetRaw"]        = new TH1F(prefix+"_uperp_frommetRaw", ";u_{#perp}  [GeV] (Raw MET);Events", 100, -200, 200);

    (*hists)[prefix+"_AbsScale"]                = new TH1F(prefix+"_AbsScale", ";-<u_{#parallel}> / <q_{T}>;Events", 100, -200, 200);
}

void full_analyzer::fill_MET_histograms(std::map<TString, TH1*>* hists, TString prefix, int i_leading, int i_subleading){
    (*hists)[prefix+"_met"]->Fill(_met, event_weight);
    (*hists)[prefix+"_metSM"]->Fill(_met, event_weight); //FIX
    (*hists)[prefix+"_metRaw"]->Fill(_metRaw, event_weight);
    (*hists)[prefix+"_metPhi"]->Fill(_metPhi, event_weight);
    (*hists)[prefix+"_metSMPhi"]->Fill(_metPhi, event_weight);//FIX
    (*hists)[prefix+"_metRawPhi"]->Fill(_metRawPhi, event_weight);

    (*hists)[prefix+"_nPV"]->Fill(_nVertex, event_weight);

    // LorentzVector calculations
    LorentzVector l1_vec(_lPt[i_leading], _lEta[i_leading], _lPhi[i_leading], _lE[i_leading]);
    LorentzVector l2_vec(_lPt[i_subleading], _lEta[i_subleading], _lPhi[i_subleading], _lE[i_subleading]);
    LorentzVector q_vec = l1_vec + l2_vec; // q_vec = Z boson
    LorentzVector met_vec(_met, 0, _metPhi, _met); // met is always transverse (eta = 0)
    LorentzVector metRaw_vec(_metRaw, 0, _metRawPhi, _metRaw);
    LorentzVector uT_vec = -(q_vec + met_vec);  // Hadronic recoil u_T is defined as the sum of all PF particles momenta except for the Z boson. Therefore uT + q + met = 0
    LorentzVector uT_frommetRaw_vec = -(q_vec + metRaw_vec);

    // Calculate, in TRANSVERSE PLANE, the parallel and perpendicular component of uT to Z
    double upara = uT_vec.pt() * cos( uT_vec.phi() - q_vec.phi() );
    double uperp = uT_vec.pt() * sin( uT_vec.phi() - q_vec.phi() );
    double upara_frommetRaw = uT_frommetRaw_vec.pt() * cos( uT_frommetRaw_vec.phi() - q_vec.phi() );
    double uperp_frommetRaw = uT_frommetRaw_vec.pt() * sin( uT_frommetRaw_vec.phi() - q_vec.phi() );

    (*hists)[prefix+"_q_pt"]->Fill(q_vec.pt(), event_weight);
    (*hists)[prefix+"_uT_pt"]->Fill(uT_vec.pt(), event_weight);
    (*hists)[prefix+"_upara"]->Fill(upara, event_weight);
    (*hists)[prefix+"_uperp"]->Fill(uperp, event_weight);
    (*hists)[prefix+"_upara_frommetRaw"]->Fill(upara_frommetRaw, event_weight);
    (*hists)[prefix+"_uperp_frommetRaw"]->Fill(uperp_frommetRaw, event_weight);
    (*hists)[prefix+"_AbsScale"]->Fill(-upara/q_vec.pt(), event_weight);
}
