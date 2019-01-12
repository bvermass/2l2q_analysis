
// This are code fragments that pertained to KVF algorithm when KVF failed (inv vtx)

fill_KVF_inv_histograms(&hists, signs_and_flavor, i_subleading_displ_e); //is this one necessary still?
fill_KVF_inv_histograms(&hists, signs_and_flavor, i_subleading_displ_mu); //is this one necessary still?

    (*hists)[prefix+"_invVtx_ntracks"]                  = new TH1F(prefix+"_invVtx_ntracks", ";# of tracks for an invalid vertex;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_ngentr"]               = new TH1F(prefix+"_invVtx_1tr_ngentr", ";Gen-level # of tracks for invalid vtx with no found tracks;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_ngenl"]                = new TH1F(prefix+"_invVtx_1tr_ngenl", ";Gen-level # of Leptons for invalid vtx with no found tracks;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_ngene"]                = new TH1F(prefix+"_invVtx_1tr_ngene", ";Gen-level # of Electrons for invalid vtx with no found tracks;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_ngenmu"]               = new TH1F(prefix+"_invVtx_1tr_ngenmu", ";Gen-level # of Muons for invalid vtx with no found tracks;Events", 15, 0, 15);
    (*hists)[prefix+"_invVtx_1tr_pt"]                   = new TH1F(prefix+"_invVtx_1tr_pt", ";#it{p}_{T} [GeV];Events", 40, 0, 40);
    (*hists)[prefix+"_invVtx_1tr_deta"]                 = new TH1F(prefix+"_invVtx_1tr_deta", ";#Delta #eta;Events", 40, 0, 4);
    (*hists)[prefix+"_invVtx_1tr_dphi"]                 = new TH1F(prefix+"_invVtx_1tr_dphi", ";#Delta #phi;Events", 40, 0, 3.14);
    (*hists)[prefix+"_invVtx_1tr_dR"]                   = new TH1F(prefix+"_invVtx_1tr_dR", ";#Delta R;Events", 40, 0, 5);
    (*hists)[prefix+"_invVtx_1tr_dxy"]                  = new TH1F(prefix+"_invVtx_1tr_dxy", ";#Delta_{xy}[cm];Events", 30, 0, 4);
    (*hists)[prefix+"_invVtx_1tr_dz"]                   = new TH1F(prefix+"_invVtx_1tr_dz", ";#Delta_{z}[cm];Events", 30, 0, 10);


void full_analyzer::fill_KVF_inv_histograms(std::map<TString, TH1*>* hists, TString prefix, int i_subleading){
    if(_lKVF_valid[i_subleading]) return;
    (*hists)[prefix+"_invVtx_ntracks"]->Fill(_lKVF_ntracks[i_subleading], event_weight);
    if(_lKVF_ntracks[i_subleading] == 1) fill_1tr(hists, prefix, i_subleading);
}


void full_analyzer::fill_1tr(std::map<TString, TH1*>* hists, TString prefix, int i_lep){
    //rewrite this function?
    (*hists)[prefix+"_invVtx_1tr_ngentr"]->Fill(_gen_nNPackedDtrs, event_weight);

    // find out how many leptons are in the packed daughters of HNL
    int i_gen_ne = 0;
    int i_gen_nmu = 0;
    for(int i = 0; i < _gen_nNPackedDtrs; i++){
        if(fabs(_gen_NPackedDtrsPdgId[i]) == 11) i_gen_ne++;
        else if(fabs(_gen_NPackedDtrsPdgId[i] == 13)) i_gen_nmu++;
    }
    (*hists)[prefix+"_invVtx_1tr_ngenl"]->Fill(i_gen_ne + i_gen_nmu, event_weight);
    (*hists)[prefix+"_invVtx_1tr_ngene"]->Fill(i_gen_ne, event_weight);
    (*hists)[prefix+"_invVtx_1tr_ngenmu"]->Fill(i_gen_nmu, event_weight);

    // using gen lepton from HNL, find lepton from HNL in Packed daughters
    double mineta = 5;
    int i_lepHNL = 0;
    for(int i = 0; i < _gen_nNPackedDtrs; i++){
        if((fabs(_gen_NPackedDtrsPdgId[i]) == 11 || fabs(_gen_NPackedDtrsPdgId[i] == 13)) && fabs(_gen_NPackedDtrsEta[i] - _gen_lEta[i_gen_l2]) < mineta){
            mineta = fabs(_gen_NPackedDtrsEta[i] - _gen_lEta[i_gen_l2]);
            i_lepHNL = i;//lepton from HNL in packed daughters found
        }
    }
    // if reco lepton is not the correct one, there is no meaning to the following histograms 
    bool correct_reco_lepton = (fabs(_lEta[i_lep] - _gen_NPackedDtrsEta[i_lepHNL]) < 1 && fabs(_lPhi[i_lep] - _gen_NPackedDtrsPhi[i_lepHNL]) < 1 && fabs(_lPt[i_lep] - _gen_NPackedDtrsPt[i_lepHNL]) < 5);
    
    if(correct_reco_lepton){
        double mindR  = 5;
        double mindxy = 5;
        for(int i = 0; i < _gen_nNPackedDtrs; i++){
            if(i == i_lepHNL) continue;
            (*hists)[prefix+"_invVtx_1tr_deta"]->Fill(fabs(_gen_NPackedDtrsEta[i] - _gen_NPackedDtrsEta[i_lepHNL]));
            (*hists)[prefix+"_invVtx_1tr_pt"]->Fill(_gen_NPackedDtrsPt[i]);
            TLorentzVector lep;
            TLorentzVector track;
            lep.SetPtEtaPhiE(_gen_NPackedDtrsPt[i_lepHNL], _gen_NPackedDtrsEta[i_lepHNL], _gen_NPackedDtrsPhi[i_lepHNL], _gen_NPackedDtrsE[i_lepHNL]);
            track.SetPtEtaPhiE(_gen_NPackedDtrsPt[i], _gen_NPackedDtrsEta[i], _gen_NPackedDtrsPhi[i], _gen_NPackedDtrsE[i]);
            if(fabs(lep.DeltaR(track)) < mindR) mindR = fabs(lep.DeltaR(track));
            (*hists)[prefix+"_invVtx_1tr_dphi"]->Fill(fabs(lep.DeltaPhi(track)));
            if(matches[i] >= 1 && fabs(_gen_NPackedDtrs_matchdxy[i] - _gen_NPackedDtrs_matchdxy[i_lepHNL]) < mindxy) mindxy = fabs(_gen_NPackedDtrs_matchdxy[i] - _gen_NPackedDtrs_matchdxy[i_lepHNL]);
            if(matches[i] >= 1) (*hists)[prefix+"_invVtx_1tr_dz"]->Fill(fabs(_gen_NPackedDtrs_matchdz[i] - _gen_NPackedDtrs_matchdz[i_lepHNL]));
        }
        if(mindR  != 5) (*hists)[prefix+"_invVtx_1tr_dR"]->Fill(mindR);
        if(mindxy != 5) (*hists)[prefix+"_invVtx_1tr_dxy"]->Fill(mindxy);
    }
}


