//////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include <iostream>

#include "../interface/full_analyzer.h"

using namespace std;


double full_analyzer::calc_betagamma(int particle_mass, double particle_energy)
{
    double particle_betagamma = sqrt(particle_energy*particle_energy - particle_mass*particle_mass)/particle_mass;
    return particle_betagamma;
}

void full_analyzer::add_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix){
    (*hists)[prefix+"_nTrueInteractions"]               = new TH1F(prefix+"_nTrueInteractions", ";N(true interactions);Events", 50, 0, 100);
    (*hists)[prefix+"_nTrueInteractions_sigreg"]        = new TH1F(prefix+"_nTrueInteractions_sigreg", ";N(true interactions);Events", 50, 0, 100);
    (*hists)[prefix+"_KVForIVF_categories"]             = new TH1F(prefix+"_KVForIVF_categories", ";;Events", 4, 0, 4);
    (*hists)[prefix+"_l2_jets_categories"]              = new TH1F(prefix+"_l2_jets_categories", ";;Events", 8, 0, 8);
    (*hists)[prefix+"_jets_categories"]                 = new TH1F(prefix+"_jets_categories", ";;Events", 4, 0, 4);
    //(*hists)[prefix+"_PVSVdxyz_categories"]             = new TH1F(prefix+"_PVSVdxyz_categories", ";;Events", 8, 0, 8);
    //(*hists)[prefix+"_PVSVdxy_categories"]              = new TH1F(prefix+"_PVSVdxy_categories", ";;Events", 8, 0, 8);
    (*hists)[prefix+"_dxy_categories"]                  = new TH1F(prefix+"_dxy_categories", ";;Events", 3, 0, 3);
    (*hists)[prefix+"_MVAvsPOGMedium_categories"]       = new TH1F(prefix+"_MVAvsPOGMedium_categories", ";;Events", 4, 0, 4);
    (*hists)[prefix+"_IVF_categories"]                  = new TH1F(prefix+"_IVF_categories", ";;Events", 3, 0, 3);
    (*hists)[prefix+"_cutflow"]                         = new TH1F(prefix+"_cutflow", ";;Events", 8, 0, 8);

    (*hists)[prefix+"_nEle"]                            = new TH1F(prefix+"_nEle", ";N_{electron};Events", 10, 0, 10);
    (*hists)[prefix+"_nMu"]                             = new TH1F(prefix+"_nMu", ";N_{muon};Events", 10, 0, 10);
    (*hists)[prefix+"_nLight"]                          = new TH1F(prefix+"_nLight", ";N_{lepton};Events", 10, 0, 10);
    (*hists)[prefix+"_nJets_uncl"]                      = new TH1F(prefix+"_nJets_uncl", ";N_{jets(uncl.)};Events", 10, 0, 10);
    (*hists)[prefix+"_nJets_cl"]                        = new TH1F(prefix+"_nJets_cl", ";N_{jets(cl.)};Events", 10, 0, 10);
    (*hists)[prefix+"_IVF_nvtx"]                        = new TH1F(prefix+"_IVF_nvtx", ";N_{vtx} (IVF);Events", 50, 0, 50);
    (*hists)[prefix+"_l1_pt"]                           = new TH1F(prefix+"_l1_pt", ";l_{1} #it{p}_{T} [GeV];Events", 30, 0, 100);
    (*hists)[prefix+"_l2_pt"]                           = new TH1F(prefix+"_l2_pt", ";l_{2} #it{p}_{T} [GeV];Events", 30, 0, 50);
    (*hists)[prefix+"_l1_eta"]                          = new TH1F(prefix+"_l1_eta", ";l_{1} #eta;Events", 30, -3, 3);
    (*hists)[prefix+"_l2_eta"]                          = new TH1F(prefix+"_l2_eta", ";l_{2} #eta;Events", 30, -3, 3);
    (*hists)[prefix+"_l1_phi"]                          = new TH1F(prefix+"_l1_phi", ";l_{1} #phi;Events", 30, 0, 3.14);
    (*hists)[prefix+"_l2_phi"]                          = new TH1F(prefix+"_l2_phi", ";l_{2} #phi;Events", 30, 0, 3.14);
    (*hists)[prefix+"_l1_dxy"]                          = new TH1F(prefix+"_l1_dxy", ";l_{1} dxy [cm];Events", 30, 0, 0.02);
    (*hists)[prefix+"_l2_dxy_zoom"]                     = new TH1F(prefix+"_l2_dxy_zoom", ";l_{2} dxy [cm];Events", 30, 0, 0.05);
    (*hists)[prefix+"_l2_dxy"]                          = new TH1F(prefix+"_l2_dxy", ";l_{2} dxy [cm];Events", 30, 0, 0.5);
    (*hists)[prefix+"_l1_dz"]                           = new TH1F(prefix+"_l1_dz", ";l_{1} dz [cm];Events", 30, 0, 0.05);
    (*hists)[prefix+"_l2_dz"]                           = new TH1F(prefix+"_l2_dz", ";l_{2} dz [cm];Events", 30, 0, 2);
    (*hists)[prefix+"_l1_reliso"]                       = new TH1F(prefix+"_l1_reliso", ";l_{1} Rel Iso;Events", 30, 0, 0.05);
    (*hists)[prefix+"_l2_reliso"]                       = new TH1F(prefix+"_l2_reliso", ";l_{2} Rel Iso;Events", 30, 0, 3.5);
    (*hists)[prefix+"_l2_reliso_zoom"]                  = new TH1F(prefix+"_l2_reliso_zoom", ";l_{2} Rel Iso;Events", 30, 0, 0.5);
    (*hists)[prefix+"_l1_ptrel"]                        = new TH1F(prefix+"_l1_ptrel", ";l_{1} #it{p}_{T}^{rel} [GeV];Events", 30, 0, 40);
    (*hists)[prefix+"_l2_ptrel"]                        = new TH1F(prefix+"_l2_ptrel", ";l_{2} #it{p}_{T}^{rel} [GeV];Events", 30, 0, 10);
    (*hists)[prefix+"_l1_ptratio"]                      = new TH1F(prefix+"_l1_ptratio", ";l_{1} #it{p}_{T}^{ratio} [GeV];Events", 30, 0.75, 1);
    (*hists)[prefix+"_l2_ptratio"]                      = new TH1F(prefix+"_l2_ptratio", ";l_{2} #it{p}_{T}^{ratio} [GeV];Events", 30, 0, 1);
    (*hists)[prefix+"_l1_selectedTrackMult"]            = new TH1F(prefix+"_l1_selectedTrackMult", ";l_{1} selectedTrackMult;Events", 6, 0, 6);
    (*hists)[prefix+"_l2_selectedTrackMult"]            = new TH1F(prefix+"_l2_selectedTrackMult", ";l_{2} selectedTrackMult;Events", 15, 0, 15);
    (*hists)[prefix+"_l1_3dIP"]                         = new TH1F(prefix+"_l1_3dIP", ";l_{1} 3dIP;Events", 30, 0, 0.02);
    (*hists)[prefix+"_l2_3dIP"]                         = new TH1F(prefix+"_l2_3dIP", ";l_{2} 3dIP;Events", 30, 0, 0.5);
    (*hists)[prefix+"_l1_3dIPSig"]                      = new TH1F(prefix+"_l1_3dIPSig", ";l_{1} 3dIPSig;Events", 30, 0, 4);
    (*hists)[prefix+"_l2_3dIPSig"]                      = new TH1F(prefix+"_l2_3dIPSig", ";l_{2} 3dIPSig;Events", 30, 0, 40);
    (*hists)[prefix+"_met"]                             = new TH1F(prefix+"_met", ";MET [GeV];Events", 30, 0, 150);
    (*hists)[prefix+"_mll"]                             = new TH1F(prefix+"_mll", ";#it{m}_{ll} [GeV];Events", 30, 0, 200);
    (*hists)[prefix+"_dphill"]                          = new TH1F(prefix+"_dphill", ";#it{#Delta #phi}_{ll};Events", 30, 0, 3.14);
    (*hists)[prefix+"_dRll"]                            = new TH1F(prefix+"_dRll", ";#it{#Delta R}_{ll};Events", 30, 0, 6);
    (*hists)[prefix+"_dRl2jet1_cl"]                     = new TH1F(prefix+"_dRl2jet1_cl", ";#it{#Delta R}(l_{2},jet_{1}^{cl});Events", 30, 0, 6);
    (*hists)[prefix+"_dRl2jet2_cl"]                     = new TH1F(prefix+"_dRl2jet2_cl", ";#it{#Delta R}(l_{2},jet_{2}^{cl});Events", 30, 0, 6);
    (*hists)[prefix+"_dRjet1jet2_cl"]                   = new TH1F(prefix+"_dRjet1jet2_cl", ";#it{#Delta R}(jet_{1}^{cl},jet_{2}^{cl});Events", 30, 0, 6);
    (*hists2D)[prefix+"_dRl2jet1_2_cl"]                 = new TH2F(prefix+"_dRl2jet1_2_cl", ";#it{#Delta R}(l_{2}, jet_{1}^{cl});#it{#Delta R}(l_{2}, jet_{2}^{cl})", 30, 0, 6, 30, 0, 6);
    (*hists)[prefix+"_dRl2jet1_uncl"]                   = new TH1F(prefix+"_dRl2jet1_uncl", ";#it{#Delta R}(l_{2},jet_{1}^{uncl});Events", 30, 0, 6);
    (*hists)[prefix+"_dRl2jet2_uncl"]                   = new TH1F(prefix+"_dRl2jet2_uncl", ";#it{#Delta R}(l_{2},jet_{2}^{uncl});Events", 30, 0, 6);
    (*hists)[prefix+"_dRjet1jet2_uncl"]                 = new TH1F(prefix+"_dRjet1jet2_uncl", ";#it{#Delta R}(jet_{1}^{uncl},jet_{2}^{uncl});Events", 30, 0, 6);
    (*hists2D)[prefix+"_dRl2jet1_2_uncl"]               = new TH2F(prefix+"_dRl2jet1_2_uncl", ";#it{#Delta R}(l_{2}, jet_{1}^{uncl});#it{#Delta R}(l_{2}, jet_{2}^{uncl})", 30, 0, 6, 30, 0, 6);

    (*hists)[prefix+"_ngentr"]                          = new TH1F(prefix+"_ngentr", ";N_{tracks}^{gen} from HNL;Events", 15, 0, 15);
    (*hists)[prefix+"_ctau"]                            = new TH1F(prefix+"_ctau", ";c#tau_{HNL} [cm];Events", 40, 0, 100);
    (*hists)[prefix+"_ctaug"]                           = new TH1F(prefix+"_ctaug", ";#gamma c#tau_{HNL} [cm];Events", 40, 0, 100);

    (*hists)[prefix+"_KVF_SVgen-reco"]                  = new TH1F(prefix+"_KVF_SVgen-reco", ";|SV_{fit} - SV_{gen}| [cm] (KVF);Events", 30, 0, 10);
    (*hists)[prefix+"_KVF_SVgen-reco_zoom"]             = new TH1F(prefix+"_KVF_SVgen-reco_zoom", ";|SV_{fit} - SV_{gen}| [cm] (KVF);Events", 15, 0, 1);
    (*hists)[prefix+"_KVF_SVgen-reco_aftercut_zoom"]    = new TH1F(prefix+"_KVF_SVgen-reco_aftercut_zoom", ";|SV_{fit} - SV_{gen}| [cm] (KVF);Events", 15, 0, 1);
    (*hists)[prefix+"_KVF_chi2"]                        = new TH1F(prefix+"_KVF_chi2", ";#Chi^{2} (KVF);Events", 100, 0, 200);
    (*hists)[prefix+"_KVF_normchi2"]                    = new TH1F(prefix+"_KVF_normchi2", ";Normalized #Chi^{2} (KVF);Events", 100, 0, 200);
    (*hists)[prefix+"_KVF_normchi2_zoom"]               = new TH1F(prefix+"_KVF_normchi2_zoom", ";Normalized #Chi^{2} (KVF);Events", 20, 0, 30);
    (*hists)[prefix+"_KVF_ntracks"]                     = new TH1F(prefix+"_KVF_ntracks", ";# of tracks used in Vtxfit (KVF);Events", 15, 0, 15);
    (*hists)[prefix+"_KVF_valid"]                       = new TH1F(prefix+"_KVF_valid", ";is Vertex Valid? (KVF);Events", 2, 0, 2);
    (*hists)[prefix+"_KVF_PV-SVdxy"]                    = new TH1F(prefix+"_KVF_PV-SVdxy", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 60);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom"]               = new TH1F(prefix+"_KVF_PV-SVdxy_zoom", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom2"]              = new TH1F(prefix+"_KVF_PV-SVdxy_zoom2", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_PV-SVdxyz"]                   = new TH1F(prefix+"_KVF_PV-SVdxyz", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 100);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom"]              = new TH1F(prefix+"_KVF_PV-SVdxyz_zoom", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom2"]             = new TH1F(prefix+"_KVF_PV-SVdxyz_zoom2", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_dRcut"]                       = new TH1F(prefix+"_KVF_dRcut", ";dR cone size (KVF);Events", 11, 0, 1.1);
    
    (*hists)[prefix+"_KVF_PV-SVdxy_eff_num"]            = new TH1F(prefix+"_KVF_PV-SVdxy_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 60);
    (*hists)[prefix+"_KVF_PV-SVdxy_eff_den"]            = new TH1F(prefix+"_KVF_PV-SVdxy_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 60);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom_eff_num"]       = new TH1F(prefix+"_KVF_PV-SVdxy_zoom_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom_eff_den"]       = new TH1F(prefix+"_KVF_PV-SVdxy_zoom_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom2_eff_num"]      = new TH1F(prefix+"_KVF_PV-SVdxy_zoom2_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom2_eff_den"]      = new TH1F(prefix+"_KVF_PV-SVdxy_zoom2_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_PV-SVdxyz_eff_num"]           = new TH1F(prefix+"_KVF_PV-SVdxyz_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 100);
    (*hists)[prefix+"_KVF_PV-SVdxyz_eff_den"]           = new TH1F(prefix+"_KVF_PV-SVdxyz_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 100);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom_eff_num"]      = new TH1F(prefix+"_KVF_PV-SVdxyz_zoom_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom_eff_den"]      = new TH1F(prefix+"_KVF_PV-SVdxyz_zoom_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom2_eff_num"]     = new TH1F(prefix+"_KVF_PV-SVdxyz_zoom2_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom2_eff_den"]     = new TH1F(prefix+"_KVF_PV-SVdxyz_zoom2_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_eff_num"]        = new TH1F(prefix+"_KVF_gen_PV-SVdxy_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 60);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_eff_den"]        = new TH1F(prefix+"_KVF_gen_PV-SVdxy_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 60);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom_eff_num"]   = new TH1F(prefix+"_KVF_gen_PV-SVdxy_zoom_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom_eff_den"]   = new TH1F(prefix+"_KVF_gen_PV-SVdxy_zoom_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_num"]   = new TH1F(prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_den"]   = new TH1F(prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_ctau_eff_num"]                = new TH1F(prefix+"_KVF_ctau_eff_num", ";c #tau [cm] (KVF);Events", 20, 0, 100);
    (*hists)[prefix+"_KVF_ctau_eff_den"]                = new TH1F(prefix+"_KVF_ctau_eff_den", ";c #tau [cm] (KVF);Events", 20, 0, 100);
    (*hists)[prefix+"_KVF_ctau_zoom_eff_num"]           = new TH1F(prefix+"_KVF_ctau_zoom_eff_num", ";c #tau [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_ctau_zoom_eff_den"]           = new TH1F(prefix+"_KVF_ctau_zoom_eff_den", ";c #tau [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_ctau_zoom2_eff_num"]          = new TH1F(prefix+"_KVF_ctau_zoom2_eff_num", ";c #tau [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_ctau_zoom2_eff_den"]          = new TH1F(prefix+"_KVF_ctau_zoom2_eff_den", ";c #tau [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_PV-SVdxy_onlySVgen-reco_eff_num"]= new TH1F(prefix+"_KVF_PV-SVdxy_onlySVgen-reco_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxy_onlySVgen-reco_eff_den"]= new TH1F(prefix+"_KVF_PV-SVdxy_onlySVgen-reco_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxyz_onlySVgen-reco_eff_num"]= new TH1F(prefix+"_KVF_PV-SVdxyz_onlySVgen-reco_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxyz_onlySVgen-reco_eff_den"]= new TH1F(prefix+"_KVF_PV-SVdxyz_onlySVgen-reco_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco"]       = new TH2F(prefix+"_KVF_PV-SVdxyz_genvsreco", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);#Delta_{xyz}(PV, SV_{fit}) [cm] (gen)", 100, 0, 60, 100, 0, 60);
    (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco2"]      = new TH2F(prefix+"_KVF_PV-SVdxyz_genvsreco2", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);#Delta_{xyz}(PV, SV_{fit}) [cm] (gen)", 100, 0, 10, 100, 0, 10);

    (*hists)[prefix+"_l1_IVF_match"]                    = new TH1F(prefix+"_l1_IVF_match", ";l1 IVF match (IVF);Events", 22, -2, 20);
    (*hists)[prefix+"_l2_IVF_match"]                    = new TH1F(prefix+"_L2_IVF_match", ";l2 IVF match (IVF);Events", 22, -2, 20);
    (*hists)[prefix+"_IVF_SVgen-reco"]                  = new TH1F(prefix+"_IVF_SVgen-reco", ";|SV_{fit} - SV_{gen}| [cm] (IVF);Events", 30, 0, 10);
    (*hists)[prefix+"_IVF_SVgen-reco_zoom"]             = new TH1F(prefix+"_IVF_SVgen-reco_zoom", ";|SV_{fit} - SV_{gen}| [cm] (IVF);Events", 15, 0, 1);
    (*hists)[prefix+"_IVF_SVgen-reco_aftercut_zoom"]    = new TH1F(prefix+"_IVF_SVgen-reco_aftercut_zoom", ";|SV_{fit} - SV_{gen}| [cm] (IVF);Events", 10, 0, 0.3);
    (*hists)[prefix+"_IVF_chi2"]                        = new TH1F(prefix+"_IVF_chi2", ";#Chi^{2} (IVF);Events", 30, 0, 10);
    (*hists)[prefix+"_IVF_normchi2"]                    = new TH1F(prefix+"_IVF_normchi2", ";Normalized #Chi^{2} (IVF);Events", 30, 0, 10);
    (*hists)[prefix+"_IVF_normchi2_zoom"]               = new TH1F(prefix+"_IVF_normchi2_zoom", ";Normalized #Chi^{2} (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_PV-SVdxy"]                    = new TH1F(prefix+"_IVF_PV-SVdxy", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 60);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom"]               = new TH1F(prefix+"_IVF_PV-SVdxy_zoom", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom2"]              = new TH1F(prefix+"_IVF_PV-SVdxy_zoom2", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_PV-SVdxyz"]                   = new TH1F(prefix+"_IVF_PV-SVdxyz", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 100);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom"]              = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom2"]             = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom2", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_ntracks"]                     = new TH1F(prefix+"_IVF_ntracks", ";# of tracks used in SVfit (IVF);Events", 15, 0, 15);
    (*hists)[prefix+"_IVF_df"]                          = new TH1F(prefix+"_IVF_df", ";# of degrees of freedom (IVF);Events", 15, 0, 5);
    (*hists)[prefix+"_IVF_cxy"]                         = new TH1F(prefix+"_IVF_cxy", ";cxy (IVF);Events", 15, 0, 2);
    (*hists)[prefix+"_IVF_cz"]                          = new TH1F(prefix+"_IVF_cz", ";cz (IVF);Events", 15, 0, 4);
    (*hists)[prefix+"_IVF_cxyz"]                        = new TH1F(prefix+"_IVF_cxyz", ";cxyz (IVF);Events", 15, 0, 5);
    (*hists)[prefix+"_IVF_trackpt"]                     = new TH1F(prefix+"_IVF_trackpt", ";track #it{p}_{T} (IVF);Events", 15, 0, 30);
    (*hists)[prefix+"_IVF_tracketa"]                    = new TH1F(prefix+"_IVF_tracketa", ";track #eta (IVF);Events", 15, -3, 3);
    (*hists)[prefix+"_IVF_trackphi"]                    = new TH1F(prefix+"_IVF_trackphi", ";track #phi (IVF);Events", 15, -3.14, 3.14);
    (*hists)[prefix+"_IVF_trackE"]                      = new TH1F(prefix+"_IVF_trackE", ";track Energy (IVF);Events", 15, 0, 40);
    (*hists)[prefix+"_IVF_trackcharge"]                 = new TH1F(prefix+"_IVF_trackcharge", ";track charge (IVF);Events", 15, -2, 2);
    (*hists)[prefix+"_IVF_mass"]                        = new TH1F(prefix+"_IVF_mass", ";SV Mass [GeV] (IVF);Events", 30, 0, 10);
    (*hists)[prefix+"_IVF_ptsum"]                       = new TH1F(prefix+"_IVF_ptsum", ";SV #it{p}_{T}^{sum} [GeV] (IVF);Events", 30, 0, 80);
    (*hists)[prefix+"_IVF_l1_mass"]                     = new TH1F(prefix+"_IVF_l1_mass", ";l_{1} + SV Mass [GeV] (IVF);Events", 40, 0, 150);
    (*hists)[prefix+"_IVF_PVSV_tracks_collimation_dphi"]= new TH1F(prefix+"_IVF_PVSV_tracks_collimation_dphi", ";#Delta#phi: HNL flight - IVF track sum;Events", 30, 0, 0.04);
    (*hists)[prefix+"_IVF_PVSV_tracks_collimation_deta"]= new TH1F(prefix+"_IVF_PVSV_tracks_collimation_deta", ";#Delta#eta: HNL flight - IVF track sum;Events", 30, 0, 0.3);
    (*hists)[prefix+"_IVF_PVSV_tracks_collimation_dR"]  = new TH1F(prefix+"_IVF_PVSV_tracks_collimation_dR", ";#DeltaR: HNL flight - IVF track sum;Events", 30, 0, 0.3);
    (*hists)[prefix+"_IVF_PVSV_tracks_collimation_dot"] = new TH1F(prefix+"_IVF_PVSV_tracks_collimation_dot", ";cos #theta: HNL flight - IVF track sum;Events", 30, 0.9, 1);
    (*hists)[prefix+"_IVF_PVSV_tracks_collimation_perp"]= new TH1F(prefix+"_IVF_PVSV_tracks_collimation_perp", ";sin #theta: HNL flight - IVF track sum;Events", 30, 0, 0.15);
    (*hists2D)[prefix+"_IVF_PV-SVdxyz_genvsreco"]       = new TH2F(prefix+"_IVF_PV-SVdxyz_genvsreco", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);#Delta_{xyz}(PV, SV_{gen}) [cm] (gen)", 100, 0, 60, 100, 0, 60);
    (*hists2D)[prefix+"_IVF_PV-SVdxyz_genvsreco2"]      = new TH2F(prefix+"_IVF_PV-SVdxyz_genvsreco2", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);#Delta_{xyz}(PV, SV_{gen}) [cm] (gen)", 100, 0, 5, 100, 0, 5);
    (*hists2D)[prefix+"_IVF_ctauHN_PV-SVdxyz"]          = new TH2F(prefix+"_IVF_ctauHN_PV-SVdxyz", ";c#tau (HNL) [cm]; #Delta_{xyz} (PV, SV_{fit}) [cm]", 20, 0, 30, 20, 0, 30);
    (*hists2D)[prefix+"_IVF_ctauHN_genPV-SVdxyz"]       = new TH2F(prefix+"_IVF_ctauHN_gen_PV-SVdxyz", ";c#tau (HNL) [cm]; #Delta_{xyz} (PV, SV)^{gen} [cm]", 20, 0, 30, 20, 0, 30);
    (*hists2D)[prefix+"_IVF_ctaugHN_PV-SVdxyz"]         = new TH2F(prefix+"_IVF_ctaugHN_PV-SVdxyz", ";#gamma c#tau (HNL) [cm]; #Delta_{xyz} (PV, SV_{fit}) [cm]", 20, 0, 30, 20, 0, 30);
    (*hists2D)[prefix+"_IVF_ctaugHN_genPV-SVdxyz"]      = new TH2F(prefix+"_IVF_ctaugHN_gen_PV-SVdxyz", ";#gamma c#tau (HNL) [cm]; #Delta_{xyz} (PV, SV)^{gen} [cm]", 20, 0, 30, 20, 0, 30);

    (*hists)[prefix+"_IVF_ctau"]                        = new TH1F(prefix+"_IVF_ctau", ";c#tau [cm] (IVF);Events", 40, 0, 100);
    (*hists)[prefix+"_IVF_PV-SVdxy_eff_num"]            = new TH1F(prefix+"_IVF_PV-SVdxy_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 60);
    (*hists)[prefix+"_IVF_PV-SVdxy_eff_den"]            = new TH1F(prefix+"_IVF_PV-SVdxy_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 60);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom_eff_num"]       = new TH1F(prefix+"_IVF_PV-SVdxy_zoom_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom_eff_den"]       = new TH1F(prefix+"_IVF_PV-SVdxy_zoom_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom2_eff_num"]      = new TH1F(prefix+"_IVF_PV-SVdxy_zoom2_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom2_eff_den"]      = new TH1F(prefix+"_IVF_PV-SVdxy_zoom2_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_PV-SVdxyz_eff_num"]           = new TH1F(prefix+"_IVF_PV-SVdxyz_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 100);
    (*hists)[prefix+"_IVF_PV-SVdxyz_eff_den"]           = new TH1F(prefix+"_IVF_PV-SVdxyz_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 100);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom_eff_num"]      = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom_eff_den"]      = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom2_eff_num"]      = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom2_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom2_eff_den"]      = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom2_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_eff_num"]        = new TH1F(prefix+"_IVF_gen_PV-SVdxy_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 20, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_eff_den"]        = new TH1F(prefix+"_IVF_gen_PV-SVdxy_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 20, 0, 60);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom_eff_num"]   = new TH1F(prefix+"_IVF_gen_PV-SVdxy_zoom_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom_eff_den"]   = new TH1F(prefix+"_IVF_gen_PV-SVdxy_zoom_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_num"]   = new TH1F(prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_num", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_den"]   = new TH1F(prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_den", ";#Delta_{xy}(PV, SV_{gen}) [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_ctau_eff_num"]                = new TH1F(prefix+"_IVF_ctau_eff_num", ";c #tau [cm] (IVF);Events", 20, 0, 100);
    (*hists)[prefix+"_IVF_ctau_eff_den"]                = new TH1F(prefix+"_IVF_ctau_eff_den", ";c #tau [cm] (IVF);Events", 20, 0, 100);
    (*hists)[prefix+"_IVF_ctau_zoom_eff_num"]           = new TH1F(prefix+"_IVF_ctau_zoom_eff_num", ";c #tau [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_ctau_zoom_eff_den"]           = new TH1F(prefix+"_IVF_ctau_zoom_eff_den", ";c #tau [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_ctau_zoom2_eff_num"]          = new TH1F(prefix+"_IVF_ctau_zoom2_eff_num", ";c #tau [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_ctau_zoom2_eff_den"]          = new TH1F(prefix+"_IVF_ctau_zoom2_eff_den", ";c #tau [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_ctaug_eff_num"]                = new TH1F(prefix+"_IVF_ctaug_eff_num", ";#gamma c #tau [cm] (IVF);Events", 20, 0, 100);
    (*hists)[prefix+"_IVF_ctaug_eff_den"]                = new TH1F(prefix+"_IVF_ctaug_eff_den", ";#gamma c #tau [cm] (IVF);Events", 20, 0, 100);
    (*hists)[prefix+"_IVF_ctaug_zoom_eff_num"]           = new TH1F(prefix+"_IVF_ctaug_zoom_eff_num", ";#gamma c #tau [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_ctaug_zoom_eff_den"]           = new TH1F(prefix+"_IVF_ctaug_zoom_eff_den", ";#gamma c #tau [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_ctaug_zoom2_eff_num"]          = new TH1F(prefix+"_IVF_ctaug_zoom2_eff_num", ";#gamma c #tau [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_ctaug_zoom2_eff_den"]          = new TH1F(prefix+"_IVF_ctaug_zoom2_eff_den", ";#gamma c #tau [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_num"] = new TH1F(prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_den"] = new TH1F(prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_num"]= new TH1F(prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_den"]= new TH1F(prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxy_nomatch"]             = new TH1F(prefix+"_IVF_PV-SVdxy_nomatch", ";#Delta_{xyz}(PV, SV_{fit}) [cm];Events", 20, 0, 10);

    (*hists)[prefix+"_corrl2_pt_eff_num"]               = new TH1F(prefix+"_corrl2_pt_eff_num", ";#it{p}_{T} [GeV];Events", 40, 0, 40);
    (*hists)[prefix+"_corrl2_pt_eff_den"]               = new TH1F(prefix+"_corrl2_pt_eff_den", ";#it{p}_{T} [GeV];Events", 40, 0, 40);
    (*hists)[prefix+"_corrl2_ctau_eff_num"]             = new TH1F(prefix+"_corrl2_ctau_eff_num", ";c#tau [cm];Events", 40, 0, 40);
    (*hists)[prefix+"_corrl2_ctau_eff_den"]             = new TH1F(prefix+"_corrl2_ctau_eff_den", ";c#tau [cm];Events", 40, 0, 40);
    (*hists)[prefix+"_corrl2_SVgen-reco_eff_num"]          = new TH1F(prefix+"_corrl2_SVgen-reco_eff_num", ";|SV_{fit} - SV_{gen}| [cm];Events", 60, -1.5, 10);
    (*hists)[prefix+"_corrl2_SVgen-reco_eff_den"]          = new TH1F(prefix+"_corrl2_SVgen-reco_eff_den", ";|SV_{fit} - SV_{gen}| [cm];Events", 60, -1.5, 10);

    add_jet_histograms(hists, prefix);
    
    return;
}


void full_analyzer::fill_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, int i_leading, int i_subleading){
    int nEle    = 0;
    int nMu     = 0;
    for(unsigned i = 0; i < _nL; i++){
        if(displElectronID[i] and ele_clean_full_displ[i]) nEle++;
        if(looseMuonID[i]) nMu++;
    }

    int nJets_uncl = 0;
    int nJets_cl = 0;
    TLorentzVector jets_uncl[4];
    TLorentzVector jets_cl[4];
    for(unsigned i = 0; i < _nJets; i++){
        if(fullJetID[i]){ 
            jets_uncl[nJets_uncl].SetPtEtaPhiE(_jetPt[i], _jetEta[i], _jetPhi[i], _jetE[i]);
            nJets_uncl++;
        }
        if(fullJetID[i] and jet_clean_full_displ[i]){
            jets_cl[nJets_cl].SetPtEtaPhiE(_jetPt[i], _jetEta[i], _jetPhi[i], _jetE[i]);
            nJets_cl++;
        }
    }

    (*hists)[prefix+"_nEle"]->Fill(nEle, event_weight);
    (*hists)[prefix+"_nMu"]->Fill(nMu, event_weight);
    (*hists)[prefix+"_nLight"]->Fill(nEle + nMu, event_weight);
    (*hists)[prefix+"_nJets_uncl"]->Fill(nJets_uncl, event_weight);
    (*hists)[prefix+"_nJets_cl"]->Fill(nJets_cl, event_weight);
    (*hists)[prefix+"_IVF_nvtx"]->Fill(_IVF_nvertex, event_weight);

    (*hists)[prefix+"_l1_pt"]->Fill(_lPt[i_leading], event_weight);
    (*hists)[prefix+"_l2_pt"]->Fill(_lPt[i_subleading], event_weight);
    (*hists)[prefix+"_l1_eta"]->Fill(_lEta[i_leading], event_weight);
    (*hists)[prefix+"_l2_eta"]->Fill(_lEta[i_subleading], event_weight);
    (*hists)[prefix+"_l1_phi"]->Fill(_lPhi[i_leading], event_weight);
    (*hists)[prefix+"_l2_phi"]->Fill(_lPhi[i_subleading], event_weight);
    (*hists)[prefix+"_l1_dxy"]->Fill(fabs(_dxy[i_leading]), event_weight);
    (*hists)[prefix+"_l2_dxy"]->Fill(fabs(_dxy[i_subleading]), event_weight);
    (*hists)[prefix+"_l2_dxy_zoom"]->Fill(fabs(_dxy[i_subleading]), event_weight);
    (*hists)[prefix+"_l1_dz"]->Fill(fabs(_dz[i_leading]), event_weight);
    (*hists)[prefix+"_l2_dz"]->Fill(fabs(_dz[i_subleading]), event_weight);
    (*hists)[prefix+"_l1_reliso"]->Fill(_relIso[i_leading], event_weight);
    (*hists)[prefix+"_l2_reliso"]->Fill(_relIso[i_subleading], event_weight);
    (*hists)[prefix+"_l1_ptrel"]->Fill(_ptRel[i_leading], event_weight);
    (*hists)[prefix+"_l2_ptrel"]->Fill(_ptRel[i_subleading], event_weight);
    (*hists)[prefix+"_l1_ptratio"]->Fill(_ptRatio[i_leading], event_weight);
    (*hists)[prefix+"_l2_ptratio"]->Fill(_ptRatio[i_subleading], event_weight);
    (*hists)[prefix+"_l1_selectedTrackMult"]->Fill(_selectedTrackMult[i_leading], event_weight);
    (*hists)[prefix+"_l2_selectedTrackMult"]->Fill(_selectedTrackMult[i_subleading], event_weight);
    (*hists)[prefix+"_l1_3dIP"]->Fill(_3dIP[i_leading], event_weight);
    (*hists)[prefix+"_l2_3dIP"]->Fill(_3dIP[i_subleading], event_weight);
    (*hists)[prefix+"_l1_3dIPSig"]->Fill(_3dIPSig[i_leading], event_weight);
    (*hists)[prefix+"_l2_3dIPSig"]->Fill(_3dIPSig[i_subleading], event_weight);

    (*hists)[prefix+"_met"]->Fill(_met, event_weight);

    (*hists)[prefix+"_mll"]->Fill(g_mll, event_weight);
    (*hists)[prefix+"_dphill"]->Fill(g_dphill, event_weight);
    (*hists)[prefix+"_dRll"]->Fill(g_dRll, event_weight);
    if(nJets_uncl > 0) (*hists)[prefix+"_dRl2jet1_uncl"]->Fill(get_dR_lepton_jet(i_subleading, jets_uncl[0]),event_weight);
    if(nJets_uncl > 1) (*hists)[prefix+"_dRl2jet2_uncl"]->Fill(get_dR_lepton_jet(i_subleading, jets_uncl[1]),event_weight);
    if(nJets_uncl > 1) (*hists)[prefix+"_dRjet1jet2_uncl"]->Fill(jets_uncl[0].DeltaR(jets_uncl[1]),event_weight);
    if(nJets_uncl > 1) (*hists2D)[prefix+"_dRl2jet1_2_uncl"]->Fill(get_dR_lepton_jet(i_subleading, jets_uncl[0]), get_dR_lepton_jet(i_subleading, jets_uncl[1]), event_weight);
    if(nJets_cl > 0) (*hists)[prefix+"_dRl2jet1_cl"]->Fill(get_dR_lepton_jet(i_subleading, jets_cl[0]),event_weight);
    if(nJets_cl > 1) (*hists)[prefix+"_dRl2jet2_cl"]->Fill(get_dR_lepton_jet(i_subleading, jets_cl[1]),event_weight);
    if(nJets_cl > 1) (*hists)[prefix+"_dRjet1jet2_cl"]->Fill(jets_cl[0].DeltaR(jets_cl[1]),event_weight);
    if(nJets_cl > 1) (*hists2D)[prefix+"_dRl2jet1_2_cl"]->Fill(get_dR_lepton_jet(i_subleading, jets_cl[0]), get_dR_lepton_jet(i_subleading, jets_cl[1]), event_weight);

    (*hists)[prefix+"_ngentr"]->Fill(_gen_nNPackedDtrs, event_weight);
    (*hists)[prefix+"_ctau"]->Fill(_ctauHN, event_weight);
    (*hists)[prefix+"_ctaug"]->Fill(_ctauHN*calc_betagamma(_gen_Nmass, _gen_NE), event_weight);
    
    (*hists)[prefix+"_KVF_valid"]->Fill(_lKVF_valid[i_subleading], event_weight);
    (*hists)[prefix+"_l1_IVF_match"]->Fill(_lIVF_match[i_leading], event_weight);
    (*hists)[prefix+"_l2_IVF_match"]->Fill(_lIVF_match[i_subleading], event_weight);

    fill_jet_histograms(hists, prefix, i_subleading);
}

void full_analyzer::fill_cutflow_e(std::map<TString, TH1*>* hists, TString prefix){
    int SSorOS = (prefix.Index("OS") == -1)? 2 : 0;

    /*
     * Number of true interactions
     */
    (*hists)[prefix+"_nTrueInteractions"]->Fill(_nTrueInt, event_weight);
    if(_1e1disple1jet and fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS) (*hists)[prefix+"_nTrueInteractions_sigreg"]->Fill(_nTrueInt, event_weight);
 
    /*
     * Cutflow
     */
    if(_1e1disple and fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS){ 
                                        (*hists)[prefix+"_cutflow"]->Fill(0., event_weight);
        if(_1e1displevtx)               (*hists)[prefix+"_cutflow"]->Fill(1., event_weight);
        if(_1e1displedispl)             (*hists)[prefix+"_cutflow"]->Fill(2., event_weight);
        if(_1e1disple0adde)             (*hists)[prefix+"_cutflow"]->Fill(3., event_weight);
        if(_1e1displemll)               (*hists)[prefix+"_cutflow"]->Fill(4., event_weight);
        if(_1e1displedphi)              (*hists)[prefix+"_cutflow"]->Fill(5., event_weight);
        if(_1e1displeReliso)            (*hists)[prefix+"_cutflow"]->Fill(6., event_weight);
        if(_1e1disple1jet)              (*hists)[prefix+"_cutflow"]->Fill(7., event_weight);
    }

    /*
     * MVA ID versus cutbased medium prompt ID
     */
    if(_1e and _1pogmediume)    (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(0., event_weight);
    if(_1e and !_1pogmediume)   (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(1., event_weight);
    if(!_1e and _1pogmediume)   (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(2., event_weight);
    if(!_1e and !_1pogmediume)  (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(3., event_weight);

    /*
     * KVF vs IVF for events
     */
    if(_1e1disple and fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS and i_gen_subleading_displ_e != -1) {
        double KVF_SVgenreco = get_KVF_SVgenreco(i_gen_subleading_displ_e, i_subleading_displ_e);

        if(_lIVF_match[i_subleading_displ_e] != -1 and get_IVF_SVgenreco(i_gen_subleading_displ_e, _lIVF_match[i_subleading_displ_e]) < 0.2){
            if(_lKVF_valid[i_subleading_displ_e] and get_KVF_SVgenreco(i_gen_subleading_displ_e, i_subleading_displ_e) < 0.2) (*hists)[prefix+"_KVForIVF_categories"]->Fill(0., event_weight);
            else (*hists)[prefix+"_KVForIVF_categories"]->Fill(1., event_weight);
        }else {
            if(_lKVF_valid[i_subleading_displ_e] and get_KVF_SVgenreco(i_gen_subleading_displ_e, i_subleading_displ_e) < 0.2) (*hists)[prefix+"_KVForIVF_categories"]->Fill(2., event_weight);
            else (*hists)[prefix+"_KVForIVF_categories"]->Fill(3., event_weight);
        }
    }

    /*
     * l2 identification and jets(cleaned)
     */
    if(_1e){
        if(_1e1disple and fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS){
            if(i_leading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(4., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(5., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(6., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(7., event_weight);
            if(i_leading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(0., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(1., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(2., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_jets_categories"]->Fill(3., event_weight);
        }else {
            if(i_leading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(0., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(1., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(2., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(3., event_weight);
        }
    }

    /*
     * dxy > 0.01cm and 0.05cm
     */
    if(_1e1displevtx and fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS){
        (*hists)[prefix+"_dxy_categories"]->Fill(0., event_weight);
        if(fabs(_dxy[i_subleading_displ_e]) > 0.01) (*hists)[prefix+"_dxy_categories"]->Fill(1., event_weight);
        if(fabs(_dxy[i_subleading_displ_e]) > 0.05) (*hists)[prefix+"_dxy_categories"]->Fill(2., event_weight);
    }

}


void full_analyzer::fill_cutflow_mu(std::map<TString, TH1*>* hists, TString prefix){
    int SSorOS = (prefix.Index("OS") == -1)? 2 : 0;

    /*
     * Number of true interactions
     */
    (*hists)[prefix+"_nTrueInteractions"]->Fill(_nTrueInt, event_weight);
    if(_1mu1displmu1jet and fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS) (*hists)[prefix+"_nTrueInteractions_sigreg"]->Fill(_nTrueInt, event_weight);
    
    /*
     * Cutflow
     */
    if(_1mu1displmu and fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS){ 
                                          (*hists)[prefix+"_cutflow"]->Fill(0., event_weight);
        if(_1mu1displmuvtx)               (*hists)[prefix+"_cutflow"]->Fill(1., event_weight);
        if(_1mu1displmudispl)             (*hists)[prefix+"_cutflow"]->Fill(2., event_weight);
        if(_1mu1displmu0addmu)            (*hists)[prefix+"_cutflow"]->Fill(3., event_weight);
        if(_1mu1displmumll)               (*hists)[prefix+"_cutflow"]->Fill(4., event_weight);
        if(_1mu1displmudphi)              (*hists)[prefix+"_cutflow"]->Fill(5., event_weight);
        if(_1mu1displmuReliso)            (*hists)[prefix+"_cutflow"]->Fill(6., event_weight);
        if(_1mu1displmu1jet)              (*hists)[prefix+"_cutflow"]->Fill(7., event_weight);
    }

    /*
     * MVA ID versus cutbased medium prompt ID
     */
    if(_1mu and _1pogmediummu)    (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(0., event_weight);
    if(_1mu and !_1pogmediummu)   (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(1., event_weight);
    if(!_1mu and _1pogmediummu)   (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(2., event_weight);
    if(!_1mu and !_1pogmediummu)  (*hists)[prefix+"_MVAvsPOGMedium_categories"]->Fill(3., event_weight);

    /*
     * KVF vs IVF for events
     */
    if(_1mu1displmu and fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS and i_gen_subleading_displ_mu != -1) {
        double KVF_SVgenreco = get_KVF_SVgenreco(i_gen_subleading_displ_mu, i_subleading_displ_mu);

        if(_lIVF_match[i_subleading_displ_mu] != -1 and get_IVF_SVgenreco(i_gen_subleading_displ_mu, _lIVF_match[i_subleading_displ_mu]) < 0.2){
            if(_lKVF_valid[i_subleading_displ_mu] and get_KVF_SVgenreco(i_gen_subleading_displ_mu, i_subleading_displ_mu) < 0.2) (*hists)[prefix+"_KVForIVF_categories"]->Fill(0., event_weight);
            else (*hists)[prefix+"_KVForIVF_categories"]->Fill(1., event_weight);
        }else {
            if(_lKVF_valid[i_subleading_displ_mu] and get_KVF_SVgenreco(i_gen_subleading_displ_mu, i_subleading_displ_mu) < 0.2) (*hists)[prefix+"_KVForIVF_categories"]->Fill(2., event_weight);
            else (*hists)[prefix+"_KVForIVF_categories"]->Fill(3., event_weight);
        }
    }

    /*
     * l2 identification and jets(cleaned)
     */
    if(_1mu){
        if(_1mu1displmu and fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS){
            if(i_leading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(4., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(5., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(6., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(7., event_weight);
            if(i_leading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(0., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(1., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_jets_categories"]->Fill(2., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_jets_categories"]->Fill(3., event_weight);
        }else {
            if(i_leading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(0., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(1., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet == -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(2., event_weight);
            else if(i_leading_jet != -1 and i_subleading_jet != -1 and i_thirdleading_jet != -1) (*hists)[prefix+"_l2_jets_categories"]->Fill(3., event_weight);
        }
    }

    /*
     * dxy > 0.01cm and 0.05cm
     */
    if(_1mu1displmuvtx and fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS){
        (*hists)[prefix+"_dxy_categories"]->Fill(0., event_weight);
        if(fabs(_dxy[i_subleading_displ_mu]) > 0.01) (*hists)[prefix+"_dxy_categories"]->Fill(1., event_weight);
        if(fabs(_dxy[i_subleading_displ_mu]) > 0.05) (*hists)[prefix+"_dxy_categories"]->Fill(2., event_weight);
    }
}


void full_analyzer::fill_KVF_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, int i_leading, int i_subleading, int i_gen_subleading){
    if(!_lKVF_valid[i_subleading]) return;
    
    double KVF_PVSVdist     = get_KVF_PVSVdist(i_subleading);
    double KVF_PVSVdist_2D  = get_KVF_PVSVdist_2D(i_subleading);

    //plots for valid KVF vertices
    
    (*hists)[prefix+"_KVF_chi2"]->Fill(_lKVF_chi2[i_subleading], event_weight);
    (*hists)[prefix+"_KVF_normchi2"]->Fill(_lKVF_chi2[i_subleading] / _lKVF_df[i_subleading], event_weight);
    (*hists)[prefix+"_KVF_normchi2_zoom"]->Fill(_lKVF_chi2[i_subleading] / _lKVF_df[i_subleading], event_weight);
    (*hists)[prefix+"_KVF_ntracks"]->Fill(_lKVF_ntracks[i_subleading], event_weight);
    
    (*hists)[prefix+"_KVF_PV-SVdxy"]->Fill(KVF_PVSVdist_2D, event_weight);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom"]->Fill(KVF_PVSVdist_2D, event_weight);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom2"]->Fill(KVF_PVSVdist_2D, event_weight);
    (*hists)[prefix+"_KVF_PV-SVdxyz"]->Fill(KVF_PVSVdist, event_weight);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom"]->Fill(KVF_PVSVdist, event_weight);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom2"]->Fill(KVF_PVSVdist, event_weight);
    (*hists)[prefix+"_KVF_dRcut"]->Fill(_lKVF_dRcut[i_subleading], event_weight);

    if(i_gen_subleading != -1){
        double KVF_SVgenreco    = get_KVF_SVgenreco(i_gen_subleading, i_subleading);
        double gen_PVSVdist     = get_PVSVdist_gen(i_gen_subleading);
        double gen_PVSVdist_2D  = get_PVSVdist_gen_2D(i_gen_subleading);
        (*hists)[prefix+"_KVF_SVgen-reco"]->Fill(KVF_SVgenreco);
        (*hists)[prefix+"_KVF_SVgen-reco_zoom"]->Fill(KVF_SVgenreco);
        (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco"]->Fill(KVF_PVSVdist, gen_PVSVdist, event_weight);
        (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco2"]->Fill(KVF_PVSVdist, gen_PVSVdist, event_weight);
    }
}


void full_analyzer::fill_IVF_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, int i_leading, int i_subleading, int i_gen_subleading){
    if(_lIVF_match[i_subleading] == -1 or _lIVF_match[i_subleading] >= (int)_IVF_nvertex) return;

    Int_t i_vtx = _lIVF_match[i_subleading];
    
    double IVF_PVSVdist_2D = get_IVF_PVSVdist_2D(i_vtx);
    double IVF_PVSVdist    = get_IVF_PVSVdist(i_vtx);

    (*hists)[prefix+"_IVF_ctau"]->Fill(_ctauHN, event_weight);
    (*hists)[prefix+"_IVF_chi2"]->Fill(_IVF_chi2[i_vtx], event_weight);
    (*hists)[prefix+"_IVF_normchi2"]->Fill(_IVF_chi2[i_vtx]/_IVF_df[i_vtx], event_weight);
    (*hists)[prefix+"_IVF_normchi2_zoom"]->Fill(_IVF_chi2[i_vtx]/_IVF_df[i_vtx], event_weight);
    (*hists)[prefix+"_IVF_PV-SVdxy"]->Fill(IVF_PVSVdist_2D, event_weight);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom"]->Fill(IVF_PVSVdist_2D, event_weight);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom2"]->Fill(IVF_PVSVdist_2D, event_weight);
    (*hists)[prefix+"_IVF_PV-SVdxyz"]->Fill(IVF_PVSVdist, event_weight);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom"]->Fill(IVF_PVSVdist, event_weight);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom2"]->Fill(IVF_PVSVdist, event_weight);
    (*hists2D)[prefix+"_IVF_ctauHN_PV-SVdxyz"]->Fill(_ctauHN, IVF_PVSVdist, event_weight);
    (*hists2D)[prefix+"_IVF_ctaugHN_PV-SVdxyz"]->Fill(_ctauHN*calc_betagamma(_gen_Nmass, _gen_NE), IVF_PVSVdist, event_weight);
    (*hists)[prefix+"_IVF_ntracks"]->Fill(_IVF_ntracks[i_vtx], event_weight);
    (*hists)[prefix+"_IVF_df"]->Fill(_IVF_df[i_vtx], event_weight);
    (*hists)[prefix+"_IVF_cxy"]->Fill(sqrt(_IVF_cx[i_vtx]*_IVF_cx[i_vtx] + _IVF_cy[i_vtx]*_IVF_cy[i_vtx]), event_weight);
    (*hists)[prefix+"_IVF_cz"]->Fill(_IVF_cz[i_vtx], event_weight);
    (*hists)[prefix+"_IVF_cxyz"]->Fill(sqrt(_IVF_cx[i_vtx]*_IVF_cx[i_vtx] + _IVF_cy[i_vtx]*_IVF_cy[i_vtx] + _IVF_cz[i_vtx]*_IVF_cz[i_vtx]), event_weight);
    
    TLorentzVector PVSV_vector(_IVF_x[i_vtx] - _PV_x, _IVF_y[i_vtx] - _PV_y, _IVF_z[i_vtx] - _PV_z, 0);

    if(_IVF_ntracks[i_vtx] > 1){
        TLorentzVector l1vector;
        l1vector.SetPtEtaPhiE(_lPt[i_leading], _lEta[i_leading], _lPhi[i_leading], _lE[i_leading]);
        TLorentzVector tracksum;
        TLorentzVector tmptrack;
        for(Int_t i_track = 0; i_track < _IVF_ntracks[i_vtx]; i_track++){
            (*hists)[prefix+"_IVF_trackpt"]->Fill(_IVF_trackpt[i_vtx][i_track], event_weight);
            (*hists)[prefix+"_IVF_tracketa"]->Fill(_IVF_tracketa[i_vtx][i_track], event_weight);
            (*hists)[prefix+"_IVF_trackphi"]->Fill(_IVF_trackphi[i_vtx][i_track], event_weight);
            (*hists)[prefix+"_IVF_trackE"]->Fill(_IVF_trackE[i_vtx][i_track], event_weight);
            (*hists)[prefix+"_IVF_trackcharge"]->Fill(_IVF_trackcharge[i_vtx][i_track], event_weight);
            tmptrack.SetPtEtaPhiE(_IVF_trackpt[i_vtx][i_track], _IVF_tracketa[i_vtx][i_track], _IVF_trackphi[i_vtx][i_track], _IVF_trackE[i_vtx][i_track]);
            tracksum += tmptrack;
        }
        (*hists)[prefix+"_IVF_mass"]->Fill(tracksum.M(), event_weight);
        (*hists)[prefix+"_IVF_ptsum"]->Fill(tracksum.Pt(), event_weight);
        (*hists)[prefix+"_IVF_l1_mass"]->Fill((tracksum+l1vector).M(), event_weight);
        (*hists)[prefix+"_IVF_PVSV_tracks_collimation_dphi"]->Fill(tracksum.DeltaPhi(PVSV_vector), event_weight);
        (*hists)[prefix+"_IVF_PVSV_tracks_collimation_deta"]->Fill(fabs(tracksum.Eta() - PVSV_vector.Eta()), event_weight);
        (*hists)[prefix+"_IVF_PVSV_tracks_collimation_dR"]->Fill(tracksum.DeltaR(PVSV_vector), event_weight);
        (*hists)[prefix+"_IVF_PVSV_tracks_collimation_dot"]->Fill(-tracksum*PVSV_vector/tracksum.Vect().Mag()/PVSV_vector.Vect().Mag(), event_weight);
        (*hists)[prefix+"_IVF_PVSV_tracks_collimation_perp"]->Fill(fabs(tracksum.Perp(PVSV_vector.Vect())/tracksum.Vect().Mag()), event_weight);
    }
    //if(tracksum.M() == 0){
    //    cout << "IVF_ntracks: " << (int)_IVF_ntracks[i_vtx] << endl;
    //    cout << "tracksum pt, eta, phi, e: " <<  tracksum.Pt() << " " << tracksum.Eta() << " " << tracksum.Phi() << " " << tracksum.E() << endl;
    //    if(_IVF_ntracks[i_vtx] == 0){
    //        cout << "i_vtx: " << i_vtx << endl;
    //        cout << "_IVF_nvertex: " << (int)_IVF_nvertex << endl;
    //        cout << "_lIVF_match: " << _lIVF_match[i_subleading] << endl;
    //    }
    
    
    if(i_gen_subleading != -1){
        double IVF_SVgenreco   = get_IVF_SVgenreco(i_gen_subleading, i_vtx);
        double gen_PVSVdist    = get_PVSVdist_gen(i_gen_subleading);
        (*hists)[prefix+"_IVF_SVgen-reco"]->Fill(IVF_SVgenreco, event_weight);
        (*hists)[prefix+"_IVF_SVgen-reco_zoom"]->Fill(IVF_SVgenreco, event_weight);
        (*hists2D)[prefix+"_IVF_PV-SVdxyz_genvsreco"]->Fill(IVF_PVSVdist, gen_PVSVdist, event_weight);
        (*hists2D)[prefix+"_IVF_PV-SVdxyz_genvsreco2"]->Fill(IVF_PVSVdist, gen_PVSVdist, event_weight);
        (*hists2D)[prefix+"_IVF_ctauHN_genPV-SVdxyz"]->Fill(_ctauHN, gen_PVSVdist, event_weight);
        (*hists2D)[prefix+"_IVF_ctaugHN_genPV-SVdxyz"]->Fill(_ctauHN*calc_betagamma(_gen_Nmass, _gen_NE), gen_PVSVdist, event_weight);
    }
}


void full_analyzer::fill_corrl2_eff(std::map<TString, TH1*>* hists, TString prefix, int i_subleading, int i_gen_subleading){
    bool vtxOk = true;
    if(_lIVF_match[i_subleading] == -1 or _lIVF_match[i_subleading] >= (int)_IVF_nvertex) vtxOk = false;
    bool genOk = true;
    if(i_gen_subleading == -1) genOk = false;


    (*hists)[prefix+"_corrl2_pt_eff_den"]->Fill(_lPt[i_subleading]);
    (*hists)[prefix+"_corrl2_ctau_eff_den"]->Fill(_ctauHN);
    if(vtxOk and genOk) (*hists)[prefix+"_corrl2_SVgen-reco_eff_den"]->Fill(get_IVF_SVgenreco(i_gen_subleading, _lIVF_match[i_subleading]));
    if(subleading_is_l2){
        (*hists)[prefix+"_corrl2_pt_eff_num"]->Fill(_lPt[i_subleading]);
        (*hists)[prefix+"_corrl2_ctau_eff_num"]->Fill(_ctauHN);
        if(vtxOk and genOk) (*hists)[prefix+"_corrl2_SVgen-reco_eff_num"]->Fill(get_IVF_SVgenreco(i_gen_subleading, _lIVF_match[i_subleading]));
    }
}


void full_analyzer::fill_IVF_eff(std::map<TString, TH1*>* hists, TString prefix, int i_leading, int i_subleading, int i_gen_subleading){
    //To get rid of absurdly high _lIVF_match values that cause a segmentation violation (in TTJets_SingleleptfromT_...)
    if( _lIVF_match[i_subleading] >= 3000 or i_gen_subleading == -1){ /*cout << "too high value for _lIVF_match! _lIVF_match and _IVF_nvertex: " <<  _lIVF_match[i_subleading] << " " << (int)_IVF_nvertex << endl;*/ return;}

    Int_t i_vtx = _lIVF_match[i_subleading];
    
    double IVF_SVgenreco        = get_IVF_SVgenreco(i_gen_subleading, i_vtx);
    double IVF_PVSVdist_gen_2D  = get_PVSVdist_gen_2D(i_gen_subleading);
    double IVF_PVSVdist         = get_IVF_PVSVdist(i_vtx);
    double IVF_PVSVdist_2D      = get_IVF_PVSVdist_2D(i_vtx);

    (*hists)[prefix+"_IVF_categories"]->Fill(0., event_weight);
    (*hists)[prefix+"_IVF_PV-SVdxy_eff_den"]->Fill(IVF_PVSVdist_2D);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom_eff_den"]->Fill(IVF_PVSVdist_2D);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom2_eff_den"]->Fill(IVF_PVSVdist_2D);
    (*hists)[prefix+"_IVF_PV-SVdxyz_eff_den"]->Fill(IVF_PVSVdist);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom_eff_den"]->Fill(IVF_PVSVdist);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_eff_den"]->Fill(IVF_PVSVdist_gen_2D);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom_eff_den"]->Fill(IVF_PVSVdist_gen_2D);
    (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_den"]->Fill(IVF_PVSVdist_gen_2D);
    (*hists)[prefix+"_IVF_ctau_eff_den"]->Fill(_ctauHN);
    (*hists)[prefix+"_IVF_ctau_zoom_eff_den"]->Fill(_ctauHN);
    (*hists)[prefix+"_IVF_ctau_zoom2_eff_den"]->Fill(_ctauHN);
    (*hists)[prefix+"_IVF_ctaug_eff_den"]->Fill(_ctauHN*calc_betagamma(_gen_Nmass, _gen_NE));
    (*hists)[prefix+"_IVF_ctaug_zoom_eff_den"]->Fill(_ctauHN*calc_betagamma(_gen_Nmass, _gen_NE));
    (*hists)[prefix+"_IVF_ctaug_zoom2_eff_den"]->Fill(_ctauHN*calc_betagamma(_gen_Nmass, _gen_NE));
    
    if(_lIVF_match[i_subleading] != -1 or ((int)_IVF_nvertex == 0 and _lIVF_match[i_subleading] > -1)){
        (*hists)[prefix+"_IVF_categories"]->Fill(1., event_weight);
        (*hists)[prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_den"]->Fill(IVF_PVSVdist_2D);
        (*hists)[prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_den"]->Fill(IVF_PVSVdist);
    }else {
        (*hists)[prefix+"_IVF_PV-SVdxy_nomatch"]->Fill(IVF_PVSVdist, event_weight);
    }
    
    if((_lIVF_match[i_subleading] != -1 or ((int)_IVF_nvertex == 0 and _lIVF_match[i_subleading] > -1)) && IVF_SVgenreco < 0.2 && IVF_PVSVdist > 0.05){
        (*hists)[prefix+"_IVF_categories"]->Fill(2., event_weight);
        (*hists)[prefix+"_IVF_SVgen-reco_aftercut_zoom"]->Fill(IVF_SVgenreco, event_weight);
        (*hists)[prefix+"_IVF_PV-SVdxy_eff_num"]->Fill(IVF_PVSVdist_2D);
        (*hists)[prefix+"_IVF_PV-SVdxy_zoom_eff_num"]->Fill(IVF_PVSVdist_2D);
        (*hists)[prefix+"_IVF_PV-SVdxy_zoom2_eff_num"]->Fill(IVF_PVSVdist_2D);
        (*hists)[prefix+"_IVF_PV-SVdxyz_eff_num"]->Fill(IVF_PVSVdist);
        (*hists)[prefix+"_IVF_PV-SVdxyz_zoom_eff_num"]->Fill(IVF_PVSVdist);
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_eff_num"]->Fill(IVF_PVSVdist_gen_2D);
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom_eff_num"]->Fill(IVF_PVSVdist_gen_2D);
        (*hists)[prefix+"_IVF_gen_PV-SVdxy_zoom2_eff_num"]->Fill(IVF_PVSVdist_gen_2D);
        (*hists)[prefix+"_IVF_ctau_eff_num"]->Fill(_ctauHN);
        (*hists)[prefix+"_IVF_ctau_zoom_eff_num"]->Fill(_ctauHN);
        (*hists)[prefix+"_IVF_ctau_zoom2_eff_num"]->Fill(_ctauHN);
        (*hists)[prefix+"_IVF_ctaug_eff_num"]->Fill(_ctauHN*calc_betagamma(_gen_Nmass, _gen_NE));
        (*hists)[prefix+"_IVF_ctaug_zoom_eff_num"]->Fill(_ctauHN*calc_betagamma(_gen_Nmass, _gen_NE));
        (*hists)[prefix+"_IVF_ctaug_zoom2_eff_num"]->Fill(_ctauHN*calc_betagamma(_gen_Nmass, _gen_NE));
        (*hists)[prefix+"_IVF_PV-SVdxy_onlySVgen-reco_eff_num"]->Fill(IVF_PVSVdist_2D);
        (*hists)[prefix+"_IVF_PV-SVdxyz_onlySVgen-reco_eff_num"]->Fill(IVF_PVSVdist);
    } 
}

void full_analyzer::fill_KVF_eff(std::map<TString, TH1*>* hists, TString prefix, int i_leading, int i_subleading, int i_gen_subleading){   
    if(i_gen_subleading == -1) return;

    double KVF_SVgenreco    = get_KVF_SVgenreco(i_gen_subleading, i_subleading);
    double gen_PVSVdist     = get_PVSVdist_gen(i_gen_subleading);
    double gen_PVSVdist_2D  = get_PVSVdist_gen_2D(i_gen_subleading);
    double KVF_PVSVdist     = get_KVF_PVSVdist(i_subleading);
    double KVF_PVSVdist_2D  = get_KVF_PVSVdist_2D(i_subleading);


    (*hists)[prefix+"_KVF_PV-SVdxy_eff_den"]->Fill(KVF_PVSVdist_2D);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom_eff_den"]->Fill(KVF_PVSVdist_2D);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom2_eff_den"]->Fill(KVF_PVSVdist_2D);
    (*hists)[prefix+"_KVF_PV-SVdxyz_eff_den"]->Fill(KVF_PVSVdist);
    (*hists)[prefix+"_KVF_PV-SVdxyz_zoom_eff_den"]->Fill(KVF_PVSVdist);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_eff_den"]->Fill(gen_PVSVdist_2D);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom_eff_den"]->Fill(gen_PVSVdist_2D);
    (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_den"]->Fill(gen_PVSVdist_2D);
    (*hists)[prefix+"_KVF_ctau_eff_den"]->Fill(_ctauHN);
    (*hists)[prefix+"_KVF_ctau_zoom_eff_den"]->Fill(_ctauHN);
    (*hists)[prefix+"_KVF_ctau_zoom2_eff_den"]->Fill(_ctauHN);
    
    if(_lKVF_valid[i_subleading]){
        (*hists)[prefix+"_KVF_PV-SVdxyz_onlySVgen-reco_eff_den"]->Fill(KVF_PVSVdist); 
    }
    
    if(_lKVF_valid[i_subleading] && KVF_SVgenreco < 0.2 && KVF_PVSVdist > 0.05){
        (*hists)[prefix+"_KVF_SVgen-reco_aftercut_zoom"]->Fill(KVF_SVgenreco, event_weight);
        (*hists)[prefix+"_KVF_PV-SVdxy_eff_num"]->Fill(KVF_PVSVdist_2D);
        (*hists)[prefix+"_KVF_PV-SVdxy_zoom_eff_num"]->Fill(KVF_PVSVdist_2D);
        (*hists)[prefix+"_KVF_PV-SVdxy_zoom2_eff_num"]->Fill(KVF_PVSVdist_2D);
        (*hists)[prefix+"_KVF_PV-SVdxyz_eff_num"]->Fill(KVF_PVSVdist);
        (*hists)[prefix+"_KVF_PV-SVdxyz_zoom_eff_num"]->Fill(KVF_PVSVdist);
        (*hists)[prefix+"_KVF_gen_PV-SVdxy_eff_num"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom_eff_num"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_KVF_gen_PV-SVdxy_zoom2_eff_num"]->Fill(gen_PVSVdist_2D);
        (*hists)[prefix+"_KVF_ctau_eff_num"]->Fill(_ctauHN);
        (*hists)[prefix+"_KVF_ctau_zoom_eff_num"]->Fill(_ctauHN);
        (*hists)[prefix+"_KVF_ctau_zoom2_eff_num"]->Fill(_ctauHN);
        (*hists)[prefix+"_KVF_PV-SVdxyz_onlySVgen-reco_eff_num"]->Fill(KVF_PVSVdist);
    } 
}


void full_analyzer::give_alphanumeric_labels(std::map<TString, TH1*>* hists, TString prefix)
{
    TString SSorOS = (prefix.Index("SS") == -1)? "OS" : "SS";
    TString l = (prefix.Index("_e") == -1)? "mu" : "e";

    int nx_MVAvsPOGMedium = 4;
    const char *MVAvsPOGMedium_labels[nx_MVAvsPOGMedium] = {"MVA, POGMedium", "MVA, no POGMedium", "no MVA, POGMedium", "no MVA, no POGMedium"};
    for(int i = 0; i < nx_MVAvsPOGMedium; i++){ 
        (*hists)[prefix+"_MVAvsPOGMedium_categories"]->GetXaxis()->SetBinLabel(i+1,MVAvsPOGMedium_labels[i]);
    }
    int nx_KVForIVF = 4;
    const char *KVForIVF_labels[nx_KVForIVF] = {"IVF, KVF", "IVF, no KVF", "no IVF, KVF", "no IVF, no KVF"};
    for(int i = 0; i < nx_KVForIVF; i++){ 
        (*hists)[prefix+"_KVForIVF_categories"]->GetXaxis()->SetBinLabel(i+1,KVForIVF_labels[i]);
    }
    int nx_l2_jets = 8;
    const char *l2_jets_labels[nx_l2_jets] = {"no l2, 0 jet", "no l2, 1 jet", "no l2, 2 jet", "no l2, 3+ jet", "l2, 0 jet", "l2, 1 jet", "l2, 2 jet", "l2, 3+ jet"};
    for(int i = 0; i < nx_l2_jets; i++){ 
        (*hists)[prefix+"_l2_jets_categories"]->GetXaxis()->SetBinLabel(i+1,l2_jets_labels[i]);
    }
    int nx_jets = 4;
    const char *jets_labels[nx_jets] = {"0 jets", "1 jet", "2 jets", "3+ jets"};
    for(int i = 0; i < nx_jets; i++){ 
        (*hists)[prefix+"_jets_categories"]->GetXaxis()->SetBinLabel(i+1,jets_labels[i]);
    }
    int nx_cutflow = 8;
    const char *cutflow_labels[nx_cutflow] = {"good l2", "Vertex", "dxy(l2) > 0.01cm", "lepton veto", "M_{ll}", "#Delta #phi", "I_{rel}", "#leq 1jet"};
    for(int i = 0; i < nx_cutflow; i++){
        (*hists)[prefix+"_cutflow"]->GetXaxis()->SetBinLabel(i+1, cutflow_labels[i]);
    }
    int nx_dxy = 3;
    const char *dxy_labels[nx_dxy] = {"No dxy cut", "dxy(l2) > 0.01cm", "dxy(l2) > 0.05cm"};
    for(int i = 0; i < nx_dxy; i++){
        (*hists)[prefix+"_dxy_categories"]->GetXaxis()->SetBinLabel(i+1, dxy_labels[i]);
    }
    int nx_IVF = 3;
    const char *IVF_labels[nx_IVF] = {"No Vtx", "Vtx", "|SV-SVgen| < 0.02cm"};
    for(int i = 0; i < nx_IVF; i++){
        (*hists)[prefix+"_IVF_categories"]->GetXaxis()->SetBinLabel(i+1, IVF_labels[i]);
    }
}

