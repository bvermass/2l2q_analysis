//Include header for this class
#include "../interface/mini_analyzer.h"

mini_analyzer::mini_analyzer(TString filename) :
    event(filename)
{
    TH1::AddDirectory(kFALSE);//https://root.cern.ch/input-and-output
    add_histograms();
}

mini_analyzer::~mini_analyzer()
{}


void mini_analyzer::analyze(int max_entries, int partition, int partitionjobnumber)
{
    // Determine range of events to loop over
    Long64_t nentries = event.BkgEstimator_tree->GetEntries();
    if(max_entries == -1 or max_entries > nentries) max_entries = nentries;
    Long64_t j_begin = floor(1.0 * max_entries * partitionjobnumber / partition);
    Long64_t j_end   = floor(1.0 * max_entries * (partitionjobnumber + 1) / partition);
    unsigned notice = ceil(0.01 * (j_end - j_begin) / 20) * 100;

    //main loop
    std::cout << "Running over " << j_begin << " - " << j_end-1 << " out of " << max_entries << " events from " << event.BkgEstimator_filename << std::endl;
    for(unsigned jentry = j_begin; jentry < j_end; ++jentry){
	    event.BkgEstimator_tree->GetEntry(jentry);

        if((jentry - j_begin)%notice == 0) std::cout << jentry - j_begin << " of " << j_end - j_begin << std::endl;

        set_signal_regions();
        fill_histograms();
    }
    sum_quad_histograms();

    TString outputfilename = event.BkgEstimator_filename;
    outputfilename.ReplaceAll("trees/BkgEstimator/final/full_analyzer/BkgEstimator_", "histograms/mini_analyzer/hists_mini_analyzer_");
    std::cout << "output to: " << outputfilename << std::endl;
    TFile *output = new TFile(outputfilename, "recreate");
    
    std::cout << "calculating and applying ABCD method" << std::endl;
    ABCD_ratios();

    std::cout << "Add under- and overflow to last bins, then write them" << std::endl;
    for(auto const& it : hists){
        TH1* h = it.second;
        fix_overflow_and_negative_bins(h);
	    h->Write(h->GetName(), TObject::kOverwrite);
    }
    
    TH1F* hadd_counter = new TH1F("hadd_counter", "nr. of files hadded together;;", 1, 0, 1);
    hadd_counter->Fill(0);
    hadd_counter->Write();

    std::cout << "close file" << std::endl;
    output->Close();
}


void mini_analyzer::ABCD_ratios()
{
    calculate_ratio("_quadA_Yield", "_quadB_Yield", "_AoverB_Yield");
    calculate_ratio("_quadC_Yield", "_quadD_Yield", "_CoverD_Yield");

    apply_ratio("_CoverD_Yield", "_quadD_", "_DtoCwithCD_");
    apply_ratio("_CoverD_Yield", "_quadB_", "_BtoAwithCD_");
}


void mini_analyzer::calculate_ratio(TString numerator_tag, TString denominator_tag, TString ratio_tag)
{
    for(auto const& it : hists){
        TH1* h = it.second;
        TString hname = h->GetName();

        if(hname.Contains(numerator_tag)){
            TString hname_den(hname), hname_ratio(hname);

            hname_den.ReplaceAll(numerator_tag, denominator_tag);
            hname_ratio.ReplaceAll(numerator_tag, ratio_tag);

            if(hists[hname]->GetMaximum() > 0 and hists[hname_den]->GetMaximum() > 0){
                hists[hname_ratio]->Divide(hists[hname], hists[hname_den]);
            }
        }
    }
}


void mini_analyzer::apply_ratio(TString ratio_tag, TString histo_tag, TString target_tag)
{
    for(auto const& it : hists){
        TH1* h = it.second;
        TString hname = h->GetName();

        if(hname.Contains(histo_tag)){
            TString hname_ratio(hname(0, hname.Index(histo_tag)) + ratio_tag), hname_target(hname);
            hname_target.ReplaceAll(histo_tag, target_tag);

            if(hists[hname]->GetMaximum() > 0 and hists[hname_ratio]->GetMaximum() > 0){
                hists[hname_target] = (TH1F*)hists[hname]->Clone(hname_target);
                hists[hname_target]->Scale(hists[hname_ratio]->GetBinContent(1));
            }
        }
    }
}


void mini_analyzer::set_signal_regions()
{
    ABCDtags.clear();

    //Training selection is already applied before filling BkgEstimator tree
    baseline_cutphill = event._mll < 80 &&
                        event._mll > 10 &&
                        event._nTightJet <= 1;

    baseline_cutmll = event._dphill > 2.3 &&
                      event._nTightJet <= 1;

    baseline_cutphiORmll = event._mll > 10 &&
                           event._nTightJet <= 1;


    // Determine quadrant (in PFN output and dphi)
    // dphill
    if(baseline_cutphill){
        if(event._dphill > 2.3){
            if(event._JetTagVal[0] > 0.9) ABCDtags.push_back("_cutphill_quadA");
            else if(event._JetTagVal[0] > 0.2) ABCDtags.push_back("_cutphill_quadC");
        }else {
            if(event._JetTagVal[0] > 0.9) ABCDtags.push_back("_cutphill_quadB");
            else if(event._JetTagVal[0] > 0.2) ABCDtags.push_back("_cutphill_quadD");
        }
    }
    // mll
    if(baseline_cutmll){
        if(event._mll < 80){
            if(event._JetTagVal[0] > 0.9) ABCDtags.push_back("_cutmll_quadA");
            else if(event._JetTagVal[0] > 0.2) ABCDtags.push_back("_cutmll_quadC");
        }else {
            if(event._JetTagVal[0] > 0.9) ABCDtags.push_back("_cutmll_quadB");
            else if(event._JetTagVal[0] > 0.2) ABCDtags.push_back("_cutmll_quadD");
        }
    }
    // dphill or mll
    if(baseline_cutphiORmll){
        if(event._dphill > 2.3 and event._mll < 80){
            if(event._JetTagVal[0] > 0.9) ABCDtags.push_back("_cutphiORmll_quadA");
            else if(event._JetTagVal[0] > 0.2) ABCDtags.push_back("_cutphiORmll_quadC");
        }else {
            if(event._JetTagVal[0] > 0.9) ABCDtags.push_back("_cutphiORmll_quadB");
            else if(event._JetTagVal[0] > 0.2) ABCDtags.push_back("_cutphiORmll_quadD");
        }
    }


    // Determine sr_flavor
    sr_flavor = "";
    if(event._l1Charge == event._lCharge) sr_flavor += "_SS";
    else sr_flavor += "_OS";

    if(event._l1Flavor == 0) sr_flavor += "_e";
    else if(event._l1Flavor == 1) sr_flavor += "_m";

    if(event._lFlavor == 0) sr_flavor += "e";
    else if(event._lFlavor == 1) sr_flavor += "m";

}


void mini_analyzer::add_histograms()
{
    std::cout << "Initializing histograms" << std::endl;
    for(const TString& lep_region : {"_OS_ee", "_SS_ee", "_OS_mm", "_SS_mm", "_OS_em", "_SS_em", "_OS_me", "_SS_me"}){
        for(const TString& cut2region : {"_cutphill", "_cutmll", "_cutphiORmll"}){
            for(const TString& quadrant : {"_quadA", "_quadB", "_quadC", "_quadD", "_quadAB", "_quadCD", "_quadAC", "_quadBD", "_AoverB", "_CoverD", "_DtoCwithCD", "_BtoAwithCD"}){
                add_standard_histograms(lep_region + cut2region + quadrant);
                //move to parametrized pfn evaluation:
                add_pfn_histograms(lep_region + cut2region + quadrant);
            }
            add_fraction_histograms(lep_region + cut2region);
        }
    }
}


void mini_analyzer::add_fraction_histograms(TString prefix)
{
    hists[prefix+"_QuadFractions"]          = new TH1F(prefix+"_QuadFractions", ";;Fraction", 4, 0, 4);
    hists[prefix+"_QuadFractions_unw"]      = new TH1F(prefix+"_QuadFractions_unw", ";;Unweighted Events", 4, 0, 4);
    const char *quadfractions_labels[4] = {"A", "B", "C", "D"};
    for(int i = 0; i < 4; i++){
        hists[prefix+"_QuadFractions"]->GetXaxis()->SetBinLabel(i+1, quadfractions_labels[i]);
        hists[prefix+"_QuadFractions_unw"]->GetXaxis()->SetBinLabel(i+1, quadfractions_labels[i]);
    }
}


void mini_analyzer::add_standard_histograms(TString prefix)
{
    hists[prefix+"_Yield"]              = new TH1F(prefix+"_Yield", ";;Events", 1, 0, 1);
    hists[prefix+"_nTightJet"]          = new TH1F(prefix+"_nTightJet", ";N_{Jet};Events", 10, 0, 10);
    hists[prefix+"_JetPt"]              = new TH1F(prefix+"_JetPt", ";Jet #it{p}_{T} [GeV];Events", 10, 0, 100);
    hists[prefix+"_JetEta"]             = new TH1F(prefix+"_JetEta", ";Jet #eta;Events", 10, -3, 3);
    //hists[prefix+"_JetPhi"]             = new TH1F(prefix+"_JetPhi", ";Jet #phi;Events", 10, -3.14, 3.14);
    hists[prefix+"_nTightLep"]          = new TH1F(prefix+"_nTightLep", ";N_{Lep};Events", 10, 0, 10);
    hists[prefix+"_l2_pt"]              = new TH1F(prefix+"_l2_pt", ";l_{2} #it{p}_{T} [GeV];Events", 10, 0, 50);
    hists[prefix+"_l2_eta"]             = new TH1F(prefix+"_l2_eta", ";l_{2} #eta;Events", 10, -3, 3);
    //hists[prefix+"_l2_phi"]             = new TH1F(prefix+"_l2_phi", ";l_{2} #phi;Events", 10, -3.14, 3.14);
    hists[prefix+"_l2_dxy"]             = new TH1F(prefix+"_l2_dxy", ";l_{2} dxy [cm];Events", 10, 0, 0.5);
    hists[prefix+"_l2_dz"]              = new TH1F(prefix+"_l2_dz", ";l_{2} dz [cm];Events", 10, 0, 2);
    hists[prefix+"_l2_3dIPSig"]         = new TH1F(prefix+"_l2_3dIPSig", ";l_{2} 3dIPSig;Events", 10, 0, 20);
    hists[prefix+"_l2_reliso"]          = new TH1F(prefix+"_l2_reliso", ";l_{2} Rel Iso;Events", 10, 0, 3.5);
    //hists[prefix+"_l2_ptratio"]         = new TH1F(prefix+"_l2_ptratio", ";l_{2} #it{p}_{T}^{ratio} [GeV];Events", 10, 0, 1);
    //hists[prefix+"_l2_ptrel"]           = new TH1F(prefix+"_l2_ptrel", ";l_{2} #it{p}_{T}^{rel} [GeV];Events", 10, 0, 10);
    //hists[prefix+"_l2_NumberOfHits"]    = new TH1F(prefix+"_l2_NumberOfHits", ";l_{2} Nr. of Hits;Events", 10, 0, 10);
    hists[prefix+"_l2_NumberOfPixHits"] = new TH1F(prefix+"_l2_NumberOfPixHits", ";l_{2} Nr. of Pixel Hits;Events", 15, 0, 15);
    
    hists[prefix+"_l1_pt"]              = new TH1F(prefix+"_l1_pt", ";l_{1} #it{p}_{T} [GeV];Events", 10, 0, 150);
    hists[prefix+"_l1_eta"]             = new TH1F(prefix+"_l1_eta", ";l_{1} #eta;Events", 10, -3, 3);
    //hists[prefix+"_l1_phi"]             = new TH1F(prefix+"_l1_phi", ";l_{1} #phi;Events", 10, -3.14, 3.14);

    hists[prefix+"_mll"]                = new TH1F(prefix+"_mll", ";#it{m}_{ll} [GeV];Events", 10, 0, 200);
    hists[prefix+"_dRll"]               = new TH1F(prefix+"_dRll", ";#it{#Delta R}_{ll};Events", 10, 0, 6);
    hists[prefix+"_dphill"]             = new TH1F(prefix+"_dphill", ";#it{#Delta #phi}_{ll};Events", 10, 0, 3.14);
    hists[prefix+"_dRljet"]             = new TH1F(prefix+"_dRljet", ";#it{#Delta R}_{l,jet};Events", 10, 0, 1.5);

    hists[prefix+"_IVF_PV-SVdxy"]       = new TH1F(prefix+"_IVF_PV-SVdxy", ";L_{xy} [cm];Events", 10, 0, 60);
    hists[prefix+"_IVF_PV-SVdxy_zoom"]  = new TH1F(prefix+"_IVF_PV-SVdxy_zoom", ";L_{xy} [cm];Events", 10, 0, 20);
    //hists[prefix+"_IVF_PV-SVdxyz"]      = new TH1F(prefix+"_IVF_PV-SVdxyz", ";L_{xyz} [cm];Events", 10, 0, 100);
    //hists[prefix+"_IVF_PV-SVdxyz_zoom"] = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom", ";L_{xyz} [cm];Events", 10, 0, 20);
    hists[prefix+"_IVF_ntracks"]        = new TH1F(prefix+"_IVF_ntracks", ";# of tracks used in SVfit;Events", 15, 0, 15);
    hists[prefix+"_IVF_mass"]           = new TH1F(prefix+"_IVF_mass", ";SV Mass [GeV];Events", 10, 0, 20);
    hists[prefix+"_IVF_l1mass"]         = new TH1F(prefix+"_IVF_l1mass", ";SV Mass [GeV];Events", 10, 0, 150);
    hists[prefix+"_IVF_pt"]             = new TH1F(prefix+"_IVF_pt", ";SV #it{p}_{T} [GeV];Events", 10, 0, 100);
    hists[prefix+"_IVF_eta"]            = new TH1F(prefix+"_IVF_eta", ";SV #eta;Events", 10, -3, 3);
    //hists[prefix+"_IVF_phi"]            = new TH1F(prefix+"_IVF_phi", ";SV #phi;Events", 10, -3.14, 3.14);
    hists[prefix+"_IVF_normchi2"]       = new TH1F(prefix+"_IVF_normchi2", ";Normalized #Chi^{2};Events", 10, 0, 10);

}


void mini_analyzer::add_pfn_histograms(TString prefix)
{
    hists[prefix+"_JetTagVal"]          = new TH1F(prefix+"_JetTagVal", ";Jet Tag Value;Events", 10, 0, 1);
}


void mini_analyzer::fill_histograms()
{
    for(const auto& ABCDtag : ABCDtags){
        fill_standard_histograms(sr_flavor + ABCDtag, event._weight);
        fill_pfn_histograms(sr_flavor + ABCDtag, event._weight * event._reweighting_weight[0], 0);
        fill_fraction_histograms(sr_flavor + ABCDtag, event._weight);
    }
}


void mini_analyzer::fill_fraction_histograms(TString prefix, double event_weight)
{
    int binnr;
    if(prefix.Contains("_quadA")) binnr = 0;
    else if(prefix.Contains("_quadB")) binnr = 1;
    else if(prefix.Contains("_quadC")) binnr = 2;
    else binnr =3;
    prefix = prefix(0, prefix.Index("_quad"));
    hists[prefix+"_QuadFractions"]->Fill(binnr, event_weight);
    hists[prefix+"_QuadFractions_unw"]->Fill(binnr);
}


void mini_analyzer::fill_standard_histograms(TString prefix, double event_weight)
{
    hists[prefix+"_Yield"]->Fill(0., event_weight);
    hists[prefix+"_nTightJet"]->Fill(event._nTightJet,event_weight);         
    hists[prefix+"_JetPt"]->Fill(event._JetPt,event_weight);             
    hists[prefix+"_JetEta"]->Fill(event._JetEta,event_weight);            
    //hists[prefix+"_JetPhi"]->Fill(event._JetPhi,event_weight);
    hists[prefix+"_nTightLep"]->Fill(event._nTightLep,event_weight);         
    hists[prefix+"_l2_pt"]->Fill(event._lPt,event_weight);             
    hists[prefix+"_l2_eta"]->Fill(event._lEta,event_weight);            
    //hists[prefix+"_l2_phi"]->Fill(event._lPhi,event_weight);
    hists[prefix+"_l2_dxy"]->Fill(event._ldxy,event_weight);            
    hists[prefix+"_l2_dz"]->Fill(event._ldz,event_weight);             
    hists[prefix+"_l2_3dIPSig"]->Fill(event._l3dIPSig,event_weight);        
    hists[prefix+"_l2_reliso"]->Fill(event._lrelIso,event_weight);         
    //hists[prefix+"_l2_ptratio"]->Fill(event._lptRatio,event_weight);
    //hists[prefix+"_l2_ptrel"]->Fill(event._lptRel,event_weight);
    //hists[prefix+"_l2_NumberOfHits"]->Fill(event._lNumberOfHits,event_weight);
    hists[prefix+"_l2_NumberOfPixHits"]->Fill(event._lNumberOfPixelHits,event_weight);
    
    hists[prefix+"_l1_pt"]->Fill(event._l1Pt,event_weight);             
    hists[prefix+"_l1_eta"]->Fill(event._l1Eta,event_weight);            
    //hists[prefix+"_l1_phi"]->Fill(event._l1Phi,event_weight);
                                       
    hists[prefix+"_mll"]->Fill(event._mll,event_weight);               
    hists[prefix+"_dRll"]->Fill(event._dRll,event_weight);              
    hists[prefix+"_dphill"]->Fill(event._dphill,event_weight);            
    hists[prefix+"_dRljet"]->Fill(event._dRljet,event_weight);            
                                       
    hists[prefix+"_IVF_PV-SVdxy"]->Fill(event._SV_PVSVdist_2D,event_weight);      
    hists[prefix+"_IVF_PV-SVdxy_zoom"]->Fill(event._SV_PVSVdist_2D,event_weight); 
    //hists[prefix+"_IVF_PV-SVdxyz"]->Fill(event._SV_PVSVdist,event_weight);
    //hists[prefix+"_IVF_PV-SVdxyz_zoom"]->Fill(event._SV_PVSVdist,event_weight);
    hists[prefix+"_IVF_ntracks"]->Fill(event._SV_ntracks,event_weight);       
    hists[prefix+"_IVF_mass"]->Fill(event._SV_mass,event_weight);          
    hists[prefix+"_IVF_l1mass"]->Fill(event._SV_l1mass,event_weight);        
    hists[prefix+"_IVF_pt"]->Fill(event._SV_pt,event_weight);            
    hists[prefix+"_IVF_eta"]->Fill(event._SV_eta,event_weight);           
    //hists[prefix+"_IVF_phi"]->Fill(event._SV_phi,event_weight);
    hists[prefix+"_IVF_normchi2"]->Fill(event._SV_normchi2,event_weight);      
}


void mini_analyzer::fill_pfn_histograms(TString prefix, double event_weight, unsigned i)
{
    hists[prefix+"_JetTagVal"]->Fill(event._JetTagVal[i], event_weight);
}


void mini_analyzer::sum_quad_histograms()
{
    std::vector< std::vector< TString > > quadcombos;
    quadcombos.push_back({"_quadA_", "_quadB_", "_quadAB_"});
    quadcombos.push_back({"_quadA_", "_quadC_", "_quadAC_"});
    quadcombos.push_back({"_quadB_", "_quadD_", "_quadBD_"});
    quadcombos.push_back({"_quadC_", "_quadD_", "_quadCD_"});
    for(const auto& hist : hists){
        TString histname = hist.first;
        TH1* h           = hist.second;
        for(const auto& quadcombo : quadcombos){
            if(histname.Contains(quadcombo[0])){
                TString histname_second = histname;
                TString histname_combined  = histname;
                histname_second.ReplaceAll(quadcombo[0], quadcombo[1]);
                histname_combined.ReplaceAll(quadcombo[0], quadcombo[2]);
                hists[histname_combined]->Add(h, hists[histname_second]);
            }
        }
    }
}


# ifndef __CINT__
int main(int argc, char * argv[])
{
    if(argc != 5){
        std::cout << "did not provide correct arguments: ./executable input_filename max_entries partition partitionjobnumber" << std::endl;
        return 1;
    }

    mini_analyzer mini(argv[1]);
    double max_entries      = atof(argv[2]);
    int partition           = atoi(argv[3]);
    int partitionjobnumber  = atoi(argv[4]);
    mini.analyze(max_entries, partition, partitionjobnumber);
}
#endif
