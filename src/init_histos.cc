///////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::add_histograms(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_pt"]                  = new TH1F(prefix+"_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_leadpt"]              = new TH1F(prefix+"_leadpt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_dxy"]                 = new TH1F(prefix+"_dxy", ";#Delta_{xy} [cm];Events", 80, 0, 10);
    (*hists)[prefix+"_mll"]                 = new TH1F(prefix+"_mll", ";#it{m}_{ll} [GeV];Events", 80, 0, 200);
    (*hists)[prefix+"_vtxfitgen"]           = new TH1F(prefix+"_vtxfitgen", ";|Vtx_{fit} - Vtx_{gen}| [cm];Events", 80, 0, 10);
    (*hists)[prefix+"_chi2"]                = new TH1F(prefix+"_chi2", ";#Chi^{2};Events", 80, 0, 2);
    (*hists)[prefix+"_vtxfitPV"]            = new TH1F(prefix+"_vtxfitPV", ";#Delta_{xy}(Vtx_{fit}, PV) [cm];Events", 80, 0, 10);
    (*hists)[prefix+"_vtxfit_ntracks"]      = new TH1F(prefix+"_vtxfit_ntracks", ";# of tracks used in Vtxfit;Events", 15, 0, 15);
    (*hists)[prefix+"_vtxfit_valid"]        = new TH1F(prefix+"_vtxfit_valid", ";is Vertex Valid?;Events", 2, 0, 2);
    (*hists)[prefix+"_vtxfit_maxdxy_valid"] = new TH1F(prefix+"_vtxfit_maxdxy_valid", ";dxy_{max} (Valid Vtx);Events", 40, 0, 1.1);
    return;
}
