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
    (*hists)[prefix+"_cutflow"]                         = new TH1F(prefix+"_cutflow", ";cutflow;Events", 8, 0, 8);
    (*hists)[prefix+"_cuts"]                            = new TH1F(prefix+"_cuts", ";cuts;Events", 9, 0, 9);

    (*hists)[prefix+"_nEle"]                            = new TH1F(prefix+"_nEle", ";N_{electron};Events", 10, 0, 10);
    (*hists)[prefix+"_nMu"]                             = new TH1F(prefix+"_nMu", ";N_{muon};Events", 10, 0, 10);
    (*hists)[prefix+"_nLight"]                          = new TH1F(prefix+"_nLight", ";N_{lepton};Events", 10, 0, 10);
    (*hists)[prefix+"_nJets_uncl"]                      = new TH1F(prefix+"_nJets_uncl", ";N_{jets(uncl.)};Events", 10, 0, 10);
    (*hists)[prefix+"_nJets_cl"]                        = new TH1F(prefix+"_nJets_cl", ";N_{jets(cl.)};Events", 10, 0, 10);
    (*hists)[prefix+"_pt"]                              = new TH1F(prefix+"_pt", ";#it{p}_{T} [GeV];Events", 60, 0, 100);
    (*hists)[prefix+"_leadpt"]                          = new TH1F(prefix+"_leadpt", ";#it{p}_{T} [GeV];Events", 60, 0, 100);
    (*hists)[prefix+"_leadjetpt"]                       = new TH1F(prefix+"_leadjetpt", ";#it{p}_{T} [GeV];Events", 60, 0, 140);
    (*hists)[prefix+"_met"]                             = new TH1F(prefix+"_met", ";MET [GeV];Events", 60, 0, 200);
    (*hists)[prefix+"_dxy"]                             = new TH1F(prefix+"_dxy", ";#Delta_{xy} [cm];Events", 60, 0, 1.5);
    (*hists)[prefix+"_dz"]                              = new TH1F(prefix+"_dz", ";#Delta_{z} [cm];Events", 60, 0, 15);
    (*hists)[prefix+"_mll"]                             = new TH1F(prefix+"_mll", ";#it{m}_{ll} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_dphill"]                          = new TH1F(prefix+"_dphill", ";#it{#Delta #phi}_{ll};Events", 60, 0, 3.14);
    (*hists)[prefix+"_dRll"]                            = new TH1F(prefix+"_dRll", ";#it{#Delta R}_{ll};Events", 80, 0, 6);
    (*hists)[prefix+"_dRl2jet"]                         = new TH1F(prefix+"_dRl2jet", ";#it{#Delta R}_{l^{2}jet};Events", 80, 0, 6);
    (*hists)[prefix+"_l1reliso"]                        = new TH1F(prefix+"_l1reliso", ";L1 Rel Iso;Events", 60, 0, 0.3);
    (*hists)[prefix+"_l2reliso"]                        = new TH1F(prefix+"_l2reliso", ";L2 Rel Iso;Events", 40, 0, 3.5);
    (*hists)[prefix+"_leadptrel"]                       = new TH1F(prefix+"_leadptrel", ";l_{1} #it{p}_{T}^{rel} [GeV];Events", 40, 0, 40);
    (*hists)[prefix+"_ptrel"]                           = new TH1F(prefix+"_ptrel", ";l_{2} #it{p}_{T}^{rel} [GeV];Events", 40, 0, 40);

    (*hists)[prefix+"_ngentr"]                          = new TH1F(prefix+"_ngentr", ";N_{tracks}^{gen} from HNL;Events", 15, 0, 15);
    (*hists)[prefix+"_ctau"]                            = new TH1F(prefix+"_ctau", ";c#tau_{HNL} [cm];Events", 40, 0, 100);
    (*hists)[prefix+"_ctaug"]                           = new TH1F(prefix+"_ctaug", ";#gamma c#tau_{HNL} [cm];Events", 40, 0, 100);

    (*hists)[prefix+"_KVF_gendist"]                     = new TH1F(prefix+"_KVF_gendist", ";|Vtx_{fit} - Vtx_{gen}| [cm] (KVF);Events", 30, 0, 10);
    (*hists)[prefix+"_KVF_gendist_zoom"]                = new TH1F(prefix+"_KVF_gendist_zoom", ";|Vtx_{fit} - Vtx_{gen}| [cm] (KVF);Events", 15, 0, 1);
    (*hists)[prefix+"_KVF_gendist_aftercut_zoom"]       = new TH1F(prefix+"_KVF_gendist_aftercut_zoom", ";|Vtx_{fit} - Vtx_{gen}| [cm] (KVF);Events", 10, 0, 0.3);
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
    (*hists)[prefix+"_KVF_maxdxy"]                      = new TH1F(prefix+"_KVF_maxdxy", ";Max(dxy^{l2} - dxy^{trk}) (KVF);Events", 30, 0, 1.1);
    (*hists)[prefix+"_KVF_maxdz"]                       = new TH1F(prefix+"_KVF_maxdz", ";Max(dz^{l2} - dz^{trk}) (KVF);Events", 30, 0, 15);
    (*hists)[prefix+"_KVF_mindxy"]                      = new TH1F(prefix+"_KVF_mindxy", ";Min(dxy^{l2} - dxy^{trk}) (KVF);Events", 30, 0, 1.1);
    (*hists)[prefix+"_KVF_mindz"]                       = new TH1F(prefix+"_KVF_mindz", ";Min(dz^{l2} - dz^{trk}) (KVF);Events", 30, 0, 15);
    (*hists)[prefix+"_KVF_dRcut"]                       = new TH1F(prefix+"_KVF_dRcut", ";dR cone size (KVF);Events", 11, 0, 1.1);
    (*hists)[prefix+"_KVF_mass"]                        = new TH1F(prefix+"_KVF_mass", ";vertex mass [GeV] (KVF);Events", 40, 0, 30);
    
    (*hists)[prefix+"_KVF_PV-SVdxy_eff_num"]            = new TH1F(prefix+"_KVF_PV-SVdxy_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 60);
    (*hists)[prefix+"_KVF_PV-SVdxy_eff_den"]            = new TH1F(prefix+"_KVF_PV-SVdxy_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 60);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom_eff_num"]       = new TH1F(prefix+"_KVF_PV-SVdxy_zoom_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom_eff_den"]       = new TH1F(prefix+"_KVF_PV-SVdxy_zoom_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom2_eff_num"]      = new TH1F(prefix+"_KVF_PV-SVdxy_zoom2_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 1);
    (*hists)[prefix+"_KVF_PV-SVdxy_zoom2_eff_den"]      = new TH1F(prefix+"_KVF_PV-SVdxy_zoom2_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 1);
    //(*hists)[prefix+"_KVF_PV-SVdxy_zoom3_eff_num"]      = new TH1F(prefix+"_KVF_PV-SVdxy_zoom3_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 50, 0, 10);
    //(*hists)[prefix+"_KVF_PV-SVdxy_zoom3_eff_den"]      = new TH1F(prefix+"_KVF_PV-SVdxy_zoom3_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 50, 0, 10);
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
    (*hists)[prefix+"_KVF_PV-SVdxy_onlygendist_eff_num"]= new TH1F(prefix+"_KVF_PV-SVdxy_onlygendist_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxy_onlygendist_eff_den"]= new TH1F(prefix+"_KVF_PV-SVdxy_onlygendist_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxyz_onlygendist_eff_num"]= new TH1F(prefix+"_KVF_PV-SVdxyz_onlygendist_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists)[prefix+"_KVF_PV-SVdxyz_onlygendist_eff_den"]= new TH1F(prefix+"_KVF_PV-SVdxyz_onlygendist_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);Events", 20, 0, 10);
    (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco"]       = new TH2F(prefix+"_KVF_PV-SVdxyz_genvsreco", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);#Delta_{xyz}(PV, SV_{fit}) [cm] (gen)", 100, 0, 60, 100, 0, 60);
    (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco2"]      = new TH2F(prefix+"_KVF_PV-SVdxyz_genvsreco2", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (KVF);#Delta_{xyz}(PV, SV_{fit}) [cm] (gen)", 100, 0, 10, 100, 0, 10);

    (*hists)[prefix+"_l1_IVF_match"]                    = new TH1F(prefix+"_l1_IVF_match", ";l1 IVF match (IVF);Events", 22, -2, 20);
    (*hists)[prefix+"_l2_IVF_match"]                    = new TH1F(prefix+"_L2_IVF_match", ";l2 IVF match (IVF);Events", 22, -2, 20);
    (*hists)[prefix+"_IVF_gendist"]                     = new TH1F(prefix+"_IVF_gendist", ";|Vtx_{fit} - Vtx_{gen}| [cm] (IVF);Events", 30, 0, 10);
    (*hists)[prefix+"_IVF_gendist_zoom"]                = new TH1F(prefix+"_IVF_gendist_zoom", ";|Vtx_{fit} - Vtx_{gen}| [cm] (IVF);Events", 30, 0, 1);
    (*hists)[prefix+"_IVF_gendist_aftercut_zoom"]       = new TH1F(prefix+"_IVF_gendist_aftercut_zoom", ";|Vtx_{fit} - Vtx_{gen}| [cm] (IVF);Events", 10, 0, 0.3);
    (*hists)[prefix+"_IVF_chi2"]                        = new TH1F(prefix+"_IVF_chi2", ";#Chi^{2} (IVF);Events", 30, 0, 10);
    (*hists)[prefix+"_IVF_normchi2"]                    = new TH1F(prefix+"_IVF_normchi2", ";Normalized #Chi^{2} (IVF);Events", 30, 0, 10);
    (*hists)[prefix+"_IVF_normchi2_zoom"]               = new TH1F(prefix+"_IVF_normchi2_zoom", ";Normalized #Chi^{2} (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_PV-SVdxy"]                    = new TH1F(prefix+"_IVF_PV-SVdxy", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 60);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom"]               = new TH1F(prefix+"_IVF_PV-SVdxy_zoom", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxy_zoom2"]              = new TH1F(prefix+"_IVF_PV-SVdxy_zoom2", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_PV-SVdxyz"]                   = new TH1F(prefix+"_IVF_PV-SVdxyz", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 100);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom"]              = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxyz_zoom2"]             = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom2", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 1);
    (*hists)[prefix+"_IVF_ntracks"]                     = new TH1F(prefix+"_IVF_ntracks", ";# of tracks used in Vtxfit (IVF);Events", 15, 0, 15);
    (*hists)[prefix+"_IVF_df"]                          = new TH1F(prefix+"_IVF_df", ";# of degrees of freedom (IVF);Events", 15, 0, 5);
    (*hists)[prefix+"_IVF_cxy"]                         = new TH1F(prefix+"_IVF_cxy", ";cxy (IVF);Events", 15, 0, 2);
    (*hists)[prefix+"_IVF_cz"]                          = new TH1F(prefix+"_IVF_cz", ";cz (IVF);Events", 15, 0, 4);
    (*hists)[prefix+"_IVF_cxyz"]                        = new TH1F(prefix+"_IVF_cxyz", ";cxyz (IVF);Events", 15, 0, 5);
    (*hists)[prefix+"_IVF_trackpt"]                     = new TH1F(prefix+"_IVF_trackpt", ";track #it{p}_{T} (IVF);Events", 15, 0, 30);
    (*hists)[prefix+"_IVF_tracketa"]                    = new TH1F(prefix+"_IVF_tracketa", ";track #eta (IVF);Events", 15, -3, 3);
    (*hists)[prefix+"_IVF_trackphi"]                    = new TH1F(prefix+"_IVF_trackphi", ";track #phi (IVF);Events", 15, -3.14, 3.14);
    (*hists)[prefix+"_IVF_trackE"]                      = new TH1F(prefix+"_IVF_trackE", ";track Energy (IVF);Events", 15, 0, 40);
    (*hists)[prefix+"_IVF_trackcharge"]                 = new TH1F(prefix+"_IVF_trackcharge", ";track charge (IVF);Events", 15, -2, 2);
    (*hists)[prefix+"_IVF_mass"]                        = new TH1F(prefix+"_IVF_mass", ";Vtx Mass [GeV] (IVF);Events", 30, 0, 9);
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
    //(*hists)[prefix+"_IVF_PV-SVdxy_zoom3_eff_num"]      = new TH1F(prefix+"_IVF_PV-SVdxy_zoom3_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 50, 0, 10);
    //(*hists)[prefix+"_IVF_PV-SVdxy_zoom3_eff_den"]      = new TH1F(prefix+"_IVF_PV-SVdxy_zoom3_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 50, 0, 10);
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
    (*hists)[prefix+"_IVF_PV-SVdxy_onlygendist_eff_num"] = new TH1F(prefix+"_IVF_PV-SVdxy_onlygendist_eff_num", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxy_onlygendist_eff_den"] = new TH1F(prefix+"_IVF_PV-SVdxy_onlygendist_eff_den", ";#Delta_{xy}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxyz_onlygendist_eff_num"]= new TH1F(prefix+"_IVF_PV-SVdxyz_onlygendist_eff_num", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxyz_onlygendist_eff_den"]= new TH1F(prefix+"_IVF_PV-SVdxyz_onlygendist_eff_den", ";#Delta_{xyz}(PV, SV_{fit}) [cm] (IVF);Events", 20, 0, 10);
    (*hists)[prefix+"_IVF_PV-SVdxy_nomatch"]             = new TH1F(prefix+"_IVF_PV-SVdxy_nomatch", ";#Delta_{xyz}(PV, SV_{fit}) [cm];Events", 20, 0, 10);

    (*hists)[prefix+"_corrl2_pt_eff_num"]               = new TH1F(prefix+"_corrl2_pt_eff_num", ";#it{p}_{T} [GeV];Events", 40, 0, 40);
    (*hists)[prefix+"_corrl2_pt_eff_den"]               = new TH1F(prefix+"_corrl2_pt_eff_den", ";#it{p}_{T} [GeV];Events", 40, 0, 40);
    (*hists)[prefix+"_corrl2_ctau_eff_num"]             = new TH1F(prefix+"_corrl2_ctau_eff_num", ";c#tau [cm];Events", 40, 0, 40);
    (*hists)[prefix+"_corrl2_ctau_eff_den"]             = new TH1F(prefix+"_corrl2_ctau_eff_den", ";c#tau [cm];Events", 40, 0, 40);
    (*hists)[prefix+"_corrl2_gendist_eff_num"]          = new TH1F(prefix+"_corrl2_gendist_eff_num", ";|Vtx_{fit} - Vtx_{gen}| [cm];Events", 60, 0, 10);
    (*hists)[prefix+"_corrl2_gendist_eff_den"]          = new TH1F(prefix+"_corrl2_gendist_eff_den", ";|Vtx_{fit} - Vtx_{gen}| [cm];Events", 60, 0, 10);
   
/*    (*hists)[prefix+"_n_prompte_ID"]   = new TH1F(prefix+"_n_prompte_ID", ";Number of electron with prompt ID;Events", 10, 0, 10);
    (*hists)[prefix+"_n_disple_ID"]   = new TH1F(prefix+"_n_disple_ID", ";Number of electron with displ ID;Events", 10, 0, 10);
    (*hists)[prefix+"_n_cleanede"]   = new TH1F(prefix+"_n_cleanede", ";Number of electron cleaned;Events", 10, 0, 10);
    (*hists)[prefix+"_n_cleaned_prompte_ID"]   = new TH1F(prefix+"_n_cleaned_prompte_ID", ";Number of electron with cleaned prompt ID;Events", 10, 0, 10);
    (*hists)[prefix+"_n_cleaned_disple_ID"]   = new TH1F(prefix+"_n_cleaned_disple_ID", ";Number of electron with cleaned displ ID;Events", 10, 0, 10);
    (*hists)[prefix+"_n_promptmu_ID"]   = new TH1F(prefix+"_n_promptmu_ID", ";Number of muon with prompt ID;Events", 10, 0, 10);
    (*hists)[prefix+"_n_displmu_ID"]   = new TH1F(prefix+"_n_displmu_ID", ";Number of muon with displ ID;Events", 10, 0, 10);
    (*hists)[prefix+"_n_ptcut"]   = new TH1F(prefix+"_n_ptcut", ";Number of muon with prompt ID passing ptcut;Events", 10, 0, 10);
    (*hists)[prefix+"_n_ptcut_trig"]   = new TH1F(prefix+"_n_ptcut_trig", ";Number of muon with prompt ID passing ptcut and trigger;Events", 10, 0, 10);
    (*hists)[prefix+"_n_leadingmu_trig"]   = new TH1F(prefix+"_n_leadingmu_trig", ";Number of muon with prompt ID passing ptcut and trigger;Events", 10, 0, 10);
    (*hists)[prefix+"_n_trige"]   = new TH1F(prefix+"_n_trige", ";Number of events passing e trigger;Events", 10, 0, 10);
    (*hists)[prefix+"_n_trigmu"]   = new TH1F(prefix+"_n_trigmu", ";Number of events passing mu trigger;Events", 10, 0, 10);*/
    return;
}


void full_analyzer::fill_histograms(std::map<TString, TH1*>* hists, TString prefix, int i_leading, int i_subleading){
    int nEle    = 0;
    int nMu     = 0;
    for(unsigned i = 0; i < _nL; i++){
        if(displElectronID[i]) nEle++;
        if(displMuonID[i]) nMu++;
    }

    int nJets_uncl = 0;
    int nJets_cl = 0;
    for(unsigned i = 0; i < _nJets; i++){
        if(fullJetID[i]) nJets_uncl++;
        if(fullJetID[i] and jet_clean_full_displ[i]) nJets_cl++;
    }

    (*hists)[prefix+"_nEle"]->Fill(nEle, event_weight);
    (*hists)[prefix+"_nMu"]->Fill(nMu, event_weight);
    (*hists)[prefix+"_nLight"]->Fill(nEle + nMu, event_weight);
    (*hists)[prefix+"_nJets_uncl"]->Fill(nJets_uncl, event_weight);
    (*hists)[prefix+"_nJets_cl"]->Fill(nJets_cl, event_weight);

    (*hists)[prefix+"_leadpt"]->Fill(_lPt[i_leading], event_weight);
    (*hists)[prefix+"_pt"]->Fill(_lPt[i_subleading], event_weight);
    (*hists)[prefix+"_dxy"]->Fill(fabs(_dxy[i_subleading]), event_weight);
    (*hists)[prefix+"_dz"]->Fill(fabs(_dz[i_subleading]), event_weight);
    (*hists)[prefix+"_l1reliso"]->Fill(_relIso[i_leading], event_weight);
    (*hists)[prefix+"_l2reliso"]->Fill(_relIso[i_subleading], event_weight);
    (*hists)[prefix+"_ptrel"]->Fill(_ptRel[i_subleading], event_weight);
    (*hists)[prefix+"_leadptrel"]->Fill(_ptRel[i_leading], event_weight);

    (*hists)[prefix+"_leadjetpt"]->Fill(_jetPt[i_leading_jet_for_displ], event_weight);
    (*hists)[prefix+"_met"]->Fill(_met, event_weight);

    TLorentzVector lepton1;
    TLorentzVector lepton2;
    lepton1.SetPtEtaPhiE(_lPt[i_leading], _lEta[i_leading], _lPhi[i_leading], _lE[i_leading]);
    lepton2.SetPtEtaPhiE(_lPt[i_subleading], _lEta[i_subleading], _lPhi[i_subleading], _lE[i_subleading]);
    
    (*hists)[prefix+"_mll"]->Fill((lepton1 + lepton2).M(), event_weight);
    (*hists)[prefix+"_dphill"]->Fill(fabs(lepton1.DeltaPhi(lepton2)), event_weight);
    (*hists)[prefix+"_dRll"]->Fill(lepton1.DeltaR(lepton2), event_weight);
    (*hists)[prefix+"_dRl2jet"]->Fill(find_dRl2jet(lepton2),event_weight);

    (*hists)[prefix+"_ngentr"]->Fill(_gen_nNPackedDtrs, event_weight);
    (*hists)[prefix+"_ctau"]->Fill(_ctauHN, event_weight);
    (*hists)[prefix+"_ctaug"]->Fill(_ctauHN*calc_betagamma(_gen_Nmass, _gen_NE), event_weight);
    
    (*hists)[prefix+"_KVF_valid"]->Fill(_lKVF_valid[i_subleading], event_weight);
    (*hists)[prefix+"_l1_IVF_match"]->Fill(_lIVF_match[i_leading], event_weight);
    (*hists)[prefix+"_l2_IVF_match"]->Fill(_lIVF_match[i_subleading], event_weight);

}

void full_analyzer::fill_cutflow_e(std::map<TString, TH1*>* hists, TString prefix){
    int SSorOS = (prefix.Index("OS") == -1)? 2 : 0;//sum of charges is 2 if SS, 0 if OS

    (*hists)[prefix+"_cutflow"]->Fill(0.,event_weight); //cutflow contains the legitimate actual cutflow of the analysis
    if(_trige) (*hists)[prefix+"_cutflow"]->Fill(1.,event_weight);
    if(_1e) (*hists)[prefix+"_cutflow"]->Fill(2.,event_weight); 
    if(_1e1disple && fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS) {
        (*hists)[prefix+"_cutflow"]->Fill(3.,event_weight); 
        if(_1e1disple0adde) (*hists)[prefix+"_cutflow"]->Fill(4.,event_weight); 
        if(_1e1disple0jet) (*hists)[prefix+"_cutflow"]->Fill(5.,event_weight); 
        if(_1e1disple0jet_aftermll) (*hists)[prefix+"_cutflow"]->Fill(6.,event_weight); 
        if(_1e1disple0jet_afterdphi) (*hists)[prefix+"_cutflow"]->Fill(7.,event_weight); 
    }

    (*hists)[prefix+"_cuts"]->Fill(0.,event_weight); //cuts contains all possible cuts and is more meant to analyze different cuts
    if(_trige) (*hists)[prefix+"_cuts"]->Fill(1.,event_weight);
    if(_1e) (*hists)[prefix+"_cuts"]->Fill(2.,event_weight); 
    if(_1e1displolde && fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS) {
        (*hists)[prefix+"_cuts"]->Fill(3.,event_weight); 
        if(_1e1disple0adde) (*hists)[prefix+"_cuts"]->Fill(5.,event_weight); 
        if(_1e1disple0jet) (*hists)[prefix+"_cuts"]->Fill(6.,event_weight); 
        if(_1e1disple0jet_aftermll) (*hists)[prefix+"_cuts"]->Fill(7.,event_weight); 
        if(_1e1disple0jet_afterdphi) (*hists)[prefix+"_cuts"]->Fill(8.,event_weight); 
    }
    
    if(_1e1disple && fabs(_lCharge[i_leading_e] + _lCharge[i_subleading_displ_e]) == SSorOS) {
        (*hists)[prefix+"_cuts"]->Fill(4., event_weight);
    }
}


void full_analyzer::fill_cutflow_mu(std::map<TString, TH1*>* hists, TString prefix){
    int SSorOS = (prefix.Index("OS") == -1)? 2 : 0;//sum of charges is 2 if SS, 0 if OS

    (*hists)[prefix+"_cutflow"]->Fill(0.,event_weight); //cutflow contains the legitimate actual cutflow of the analysis
    if(_trigmu) (*hists)[prefix+"_cutflow"]->Fill(1.,event_weight); 
    if(_1mu) (*hists)[prefix+"_cutflow"]->Fill(2.,event_weight); 
    if(_1mu1displmu && fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS) {
        (*hists)[prefix+"_cutflow"]->Fill(3.,event_weight); 
        if(_1mu1displmu0addmu) (*hists)[prefix+"_cutflow"]->Fill(4.,event_weight); 
        if(_1mu1displmu0jet) (*hists)[prefix+"_cutflow"]->Fill(5.,event_weight); 
        if(_1mu1displmu0jet_aftermll) (*hists)[prefix+"_cutflow"]->Fill(6.,event_weight); 
        if(_1mu1displmu0jet_afterdphi) (*hists)[prefix+"_cutflow"]->Fill(7.,event_weight); 
    }

    (*hists)[prefix+"_cuts"]->Fill(0.,event_weight); //cuts contains all possible cuts and is more meant to analyze different cuts
    if(_trigmu) (*hists)[prefix+"_cuts"]->Fill(1.,event_weight); 
    if(_1mu) (*hists)[prefix+"_cuts"]->Fill(2.,event_weight); 
    if(_1mu1disploldmu && fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS) {
        (*hists)[prefix+"_cuts"]->Fill(3.,event_weight); 
        if(_1mu1displmu0addmu) (*hists)[prefix+"_cuts"]->Fill(5.,event_weight); 
        if(_1mu1displmu0jet) (*hists)[prefix+"_cuts"]->Fill(6.,event_weight); 
        if(_1mu1displmu0jet_aftermll) (*hists)[prefix+"_cuts"]->Fill(7.,event_weight); 
        if(_1mu1displmu0jet_afterdphi) (*hists)[prefix+"_cuts"]->Fill(8.,event_weight); 
    }
    
    if(_1mu1displmu && fabs(_lCharge[i_leading_mu] + _lCharge[i_subleading_displ_mu]) == SSorOS) {
        (*hists)[prefix+"_cuts"]->Fill(4.,event_weight); 
    }
}


void full_analyzer::fill_KVF_histograms(std::map<TString, TH1*>* hists, std::map<TString, TH2*>* hists2D, TString prefix, int i_leading, int i_subleading, int i_gen_subleading){
    if(!_lKVF_valid[i_subleading]) return;
    
    double KVF_gendist      = get_KVF_gendist(i_gen_subleading, i_subleading);
    double gen_PVSVdist     = get_PVSVdist_gen(i_gen_subleading);
    double gen_PVSVdist_2D  = get_PVSVdist_gen_2D(i_gen_subleading);
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

    (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco"]->Fill(KVF_PVSVdist, gen_PVSVdist, event_weight);
    (*hists2D)[prefix+"_KVF_PV-SVdxyz_genvsreco2"]->Fill(KVF_PVSVdist, gen_PVSVdist, event_weight);

    //IF i want the following plots again, I need to rewrite this, but probably not
    //double maxdxy = 0;
    //double maxdz  = 0;
    //double mindxy = 5;
    //double mindz  = 5;
    //for(int i = 0; i < _lKVF_ntracks[i_subleading]; i++){
    //    //if(_lKVF_trackddxy[i_subleading][i] > maxdxy) maxdxy = _lKVF_trackddxy[i_subleading][i];
    //    //if(_lKVF_trackddz[i_subleading][i]  > maxdz)  maxdz  = _lKVF_trackddz[i_subleading][i];
    //    //if(_lKVF_trackddxy[i_subleading][i] < mindxy) mindxy = _lKVF_trackddxy[i_subleading][i];
    //    //if(_lKVF_trackddz[i_subleading][i]  < mindz)  mindz  = _lKVF_trackddz[i_subleading][i];
    //}
    //(*hists)[prefix+"_KVF_maxdxy"]->Fill(maxdxy, event_weight);
    //(*hists)[prefix+"_KVF_maxdz"]->Fill(maxdz, event_weight);
    //(*hists)[prefix+"_KVF_mindxy"]->Fill(mindxy, event_weight);
    //(*hists)[prefix+"_KVF_mindz"]->Fill(mindz, event_weight);
    (*hists)[prefix+"_KVF_dRcut"]->Fill(_lKVF_dRcut[i_subleading], event_weight);

    if(sampleflavor != "bkg"){ //this does not work yet
        int i_track = 0;
        TLorentzVector all;
        all.SetPtEtaPhiE(0,0,0,0);
        for(int i = 0; i_track < _lKVF_ntracks[i_subleading]; i++){
            if(_lKVF_trackdR[i_subleading][i] < _lKVF_dRcut[i_subleading]){
                i_track++;
                TLorentzVector temp;
                temp.SetPtEtaPhiE(_lKVF_trackPt[i_subleading][i], _lKVF_trackEta[i_subleading][i], _lKVF_trackPhi[i_subleading][i], _lKVF_trackE[i_subleading][i]);
                all += temp;
            }
        }
        (*hists)[prefix+"_KVF_mass"]->Fill(all.M(), event_weight);
    }
    
    if(i_gen_subleading != -1){
        (*hists)[prefix+"_KVF_gendist"]->Fill(get_KVF_gendist(i_gen_subleading, i_subleading));
        (*hists)[prefix+"_KVF_gendist_zoom"]->Fill(get_KVF_gendist(i_gen_subleading, i_subleading));
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
    
    
    if(i_gen_subleading != -1){
        double IVF_gendist     = get_IVF_gendist(i_gen_subleading, i_vtx);
        double gen_PVSVdist    = get_PVSVdist_gen(i_gen_subleading);
        (*hists)[prefix+"_IVF_gendist"]->Fill(IVF_gendist, event_weight);
        (*hists)[prefix+"_IVF_gendist_zoom"]->Fill(IVF_gendist, event_weight);
        (*hists2D)[prefix+"_IVF_PV-SVdxyz_genvsreco"]->Fill(IVF_PVSVdist, gen_PVSVdist, event_weight);
        (*hists2D)[prefix+"_IVF_PV-SVdxyz_genvsreco2"]->Fill(IVF_PVSVdist, gen_PVSVdist, event_weight);
        (*hists2D)[prefix+"_IVF_ctauHN_genPV-SVdxyz"]->Fill(_ctauHN, gen_PVSVdist, event_weight);
        (*hists2D)[prefix+"_IVF_ctaugHN_genPV-SVdxyz"]->Fill(_ctauHN*calc_betagamma(_gen_Nmass, _gen_NE), gen_PVSVdist, event_weight);
    }
}


void full_analyzer::fill_corrl2_eff(std::map<TString, TH1*>* hists, TString prefix, int i_subleading, int i_gen_subleading)
{
    if(i_gen_subleading == -1) return;

    double KVF_gendist = get_KVF_gendist(i_gen_subleading, i_subleading);

    (*hists)[prefix+"_corrl2_pt_eff_den"]->Fill(_lPt[i_subleading]);
    (*hists)[prefix+"_corrl2_ctau_eff_den"]->Fill(_ctauHN);
    (*hists)[prefix+"_corrl2_gendist_eff_den"]->Fill(KVF_gendist);
    if(subleading_is_l2){
        (*hists)[prefix+"_corrl2_pt_eff_num"]->Fill(_lPt[i_subleading]);
        (*hists)[prefix+"_corrl2_ctau_eff_num"]->Fill(_ctauHN);
        (*hists)[prefix+"_corrl2_gendist_eff_num"]->Fill(KVF_gendist);
    }
}


void full_analyzer::fill_IVF_eff(std::map<TString, TH1*>* hists, TString prefix, int i_leading, int i_subleading, int i_gen_subleading){
    //To get rid of absurdly high _lIVF_match values that cause a segmentation violation (in TTJets_SingleleptfromT_...)
    if( _lIVF_match[i_subleading] >= 3000 or i_gen_subleading == -1){ /*cout << "too high value for _lIVF_match! _lIVF_match and _IVF_nvertex: " <<  _lIVF_match[i_subleading] << " " << (int)_IVF_nvertex << endl;*/ return;}

    Int_t i_vtx = _lIVF_match[i_subleading];
    
    double IVF_gendist          = get_IVF_gendist(i_gen_subleading, i_vtx);
    double IVF_PVSVdist_gen_2D  = get_PVSVdist_gen_2D(i_gen_subleading);
    double IVF_PVSVdist         = get_IVF_PVSVdist(i_vtx);
    double IVF_PVSVdist_2D      = get_IVF_PVSVdist_2D(i_vtx);

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
        (*hists)[prefix+"_IVF_PV-SVdxy_onlygendist_eff_den"]->Fill(IVF_PVSVdist_2D);
        (*hists)[prefix+"_IVF_PV-SVdxyz_onlygendist_eff_den"]->Fill(IVF_PVSVdist);
    }else {
        (*hists)[prefix+"_IVF_PV-SVdxy_nomatch"]->Fill(IVF_PVSVdist, event_weight);
    }
    
    if((_lIVF_match[i_subleading] != -1 or ((int)_IVF_nvertex == 0 and _lIVF_match[i_subleading] > -1)) && IVF_gendist < 0.2 && IVF_PVSVdist > 0.05){
        (*hists)[prefix+"_IVF_gendist_aftercut_zoom"]->Fill(IVF_gendist, event_weight);
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
        (*hists)[prefix+"_IVF_PV-SVdxy_onlygendist_eff_num"]->Fill(IVF_PVSVdist_2D);
        (*hists)[prefix+"_IVF_PV-SVdxyz_onlygendist_eff_num"]->Fill(IVF_PVSVdist);
    } 
}

void full_analyzer::fill_KVF_eff(std::map<TString, TH1*>* hists, TString prefix, int i_leading, int i_subleading, int i_gen_subleading){   
    if(i_gen_subleading == -1) return;

    double KVF_gendist      = get_KVF_gendist(i_gen_subleading, i_subleading);
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
        (*hists)[prefix+"_KVF_PV-SVdxyz_onlygendist_eff_den"]->Fill(KVF_PVSVdist); 
    }
    
    if(_lKVF_valid[i_subleading] && KVF_gendist < 0.2 && KVF_PVSVdist > 0.05){
        (*hists)[prefix+"_KVF_gendist_aftercut_zoom"]->Fill(KVF_gendist, event_weight);
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
        (*hists)[prefix+"_KVF_PV-SVdxyz_onlygendist_eff_num"]->Fill(KVF_PVSVdist);
    } 
}

// This function tested the efficiencies for the prompt and displaced ID's, since something seemed to be wrong, turns out everything works fine!
/*void full_analyzer::fill_ID_histos(std::map<TString, TH1*>* hists, TString prefix)
{
    int nprompte = 0;
    int ndisple  = 0;
    int ncleanede = 0;
    int ncleanedandprompte = 0;
    int ncleanedanddisple  = 0;
    int npromptmu = 0;
    int ndisplmu  = 0;
    int nptcut = 0;
    int nptcutandtrig = 0;
    int ntrige = 0;
    int ntrigmu = 0;
    for(int i = 0; i < _nL; i++){
        if(fullElectronID[i]) nprompte++;
        if(newdisplElectronID[i]) ndisple++;
        if(ele_clean_full_noniso_displ[i]) ncleanede++;
        if(fullElectronID[i] && ele_clean_full_noniso_displ[i]) ncleanedandprompte++;
        if(newdisplElectronID[i] && ele_clean_full_noniso_displ[i]) ncleanedanddisple++;
        if(fullMuonID[i]) npromptmu++;
        if(newdisplMuonID[i]) ndisplmu++;
        if((fullElectronID[i] && _lPt[i] > 30) || (fullMuonID[i] && _lPt[i] > 25)) nptcut++;
        if((_trige && fullElectronID[i] && _lPt[i] > 30) || (_trigmu && fullMuonID[i] && _lPt[i] > 25)) nptcutandtrig++;
    }
    if(_trigmu) ntrigmu++;
    if(_trige)  ntrige++;
    (*hists)[prefix+"_n_prompte_ID"]->Fill(nprompte, event_weight);
    (*hists)[prefix+"_n_disple_ID"]->Fill(ndisple, event_weight);
    (*hists)[prefix+"_n_cleanede"]->Fill(ncleanede, event_weight);
    (*hists)[prefix+"_n_cleaned_prompte_ID"]->Fill(ncleanedandprompte, event_weight);
    (*hists)[prefix+"_n_cleaned_disple_ID"]->Fill(ncleanedanddisple, event_weight);
    (*hists)[prefix+"_n_promptmu_ID"]->Fill(npromptmu, event_weight);
    (*hists)[prefix+"_n_displmu_ID"]->Fill(ndisplmu, event_weight);
    (*hists)[prefix+"_n_ptcut"]->Fill(nptcut, event_weight);
    (*hists)[prefix+"_n_ptcut_trig"]->Fill(nptcutandtrig, event_weight);
    (*hists)[prefix+"_n_leadingmu_trig"]->Fill(_1mu, event_weight);
    (*hists)[prefix+"_n_trige"]->Fill(ntrige, event_weight);
    (*hists)[prefix+"_n_trigmu"]->Fill(ntrigmu, event_weight);
}*/

void full_analyzer::give_alphanumeric_labels(std::map<TString, TH1*>* hists, TString prefix)
{
    TString SSorOS = (prefix.Index("SS") == -1)? "OS" : "SS";
    TString l = (prefix.Index("_e") == -1)? "mu" : "e";

    int nx = 8;
    const char *cutflow_labels[nx] = {"2 lep. presel.", "HLT single " + l, "1 prompt " + l, "1 displ " + l + " " + SSorOS, "0 add. lepton", "0 tight ID jets", "M_ll < 80", "dphi_ll > 2.4"};
    for(int i = 1; i <= nx; i++) (*hists)[prefix+"_cutflow"]->GetXaxis()->SetBinLabel(i,cutflow_labels[i-1]);
    nx = 9;
    const char *cuts_labels[nx] = {"2 lep. presel.", "HLT single " + l, "1 prompt " + l, "1 displ " + l + " " + SSorOS, "new displ ID " + l + " " + SSorOS, "0 add. lepton", "0 tight ID jets", "M_ll < 80", "dphi_ll > 2.4"};
    for(int i = 1; i <= nx; i++) (*hists)[prefix+"_cuts"]->GetXaxis()->SetBinLabel(i,cuts_labels[i-1]);
}

