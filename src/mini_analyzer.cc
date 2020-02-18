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
    std::cout << "Running over " << j_begin << " - " << j_end-1 << " out of " << max_entries << " events." << std::endl;
    for(unsigned jentry = j_begin; jentry < j_end; ++jentry){
	    event.BkgEstimator_tree->GetEntry(jentry);
	    bool printevent = ((jentry -j_begin)%notice == 0);
	    if(printevent){
            std::cout << jentry - j_begin << " of " << j_end - j_begin << std::endl;
	    }

        set_signal_regions();
        fill_histograms();
    }
    
    TString outputfilename = event.BkgEstimator_filename;
    outputfilename.ReplaceAll("trees/BkgEstimator/final/full_analyzer/BkgEstimator_", "histograms/mini_analyzer/hists_mini_analyzer_");
    std::cout << "output to: " << outputfilename << std::endl;
    TFile *output = new TFile(outputfilename, "recreate");
    
    std::cout << "calculating and applying ABCD method" << std::endl;
    ABCD_ratios();

    std::cout << "Scale histograms to total_weight and add under- and overflow to last bins, then write them" << std::endl;
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
    calculate_ratio("_quadA_", "_quadB_", "_AoverB_");
    calculate_ratio("_quadC_", "_quadD_", "_CoverD_");

    apply_ratio("_CoverD_", "_quadD_", "_DtoCwithCD_");
    apply_ratio("_CoverD_", "_quadB_", "_BtoAwithCD_");
}


void mini_analyzer::calculate_ratio(TString numerator_tag, TString denominator_tag, TString ratio_tag)
{
    for(auto const& it : hists){
        TH1* h = it.second;
        TString hname = h->GetName();
        if(hname.Index(numerator_tag) != -1){
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
        if(hname.Index(histo_tag) != -1){
            TString hname_ratio(hname), hname_target(hname);
            hname_ratio.ReplaceAll(histo_tag, ratio_tag);
            hname_target.ReplaceAll(histo_tag, target_tag);
            if(hists[hname]->GetMaximum() > 0 and hists[hname_ratio]->GetMaximum() > 0){
                hists[hname_target]->Multiply(hists[hname], hists[hname_ratio]);
            }
        }
    }
}


void mini_analyzer::set_signal_regions()
{
    // Determine quadrant (in PFN output and dphi)
    isA = false;
    isB = false;
    isC = false;
    isD = false;
    if(event._dphill > 2.3){
        if(event._JetTagVal[0] > 0.9) isA = true;
        else isB = true;
    }else {
        if(event._JetTagVal[0] > 0.9) isC = true;
        else isD = true;
    }

    // Determine sr_flavor
    sr_flavor = "";
    if(event._l1Charge == event._lCharge) sr_flavor += "_SS";
    else sr_flavor += "_OS";

    if(event._l1Flavor == 0) sr_flavor += "_e";
    else if(event._l1Flavor == 1) sr_flavor += "_m";

    if(event._lFlavor == 0) sr_flavor += "e";
    else if(event._lFlavor == 1) sr_flavor += "m";

    if(isA) quad = "_quadA";
    else if(isB) quad = "_quadB";
    else if(isC) quad = "_quadC";
    else if(isD) quad = "_quadD";
}


void mini_analyzer::add_histograms()
{
    std::cout << "Initializing histograms" << std::endl;
    for(const TString& lep_region : {"_OS_ee", "_SS_ee", "_OS_mm", "_SS_mm", "_OS_em", "_SS_em", "_OS_me", "_SS_me"}){
        for(const TString& quadrant : {"_quadA", "_quadB", "_quadC", "_quadD", "_quadAB", "_quadCD", "_AoverB", "_CoverD", "_DtoCwithCD", "_BtoAwithCD"}){
            add_standard_histograms(lep_region + quadrant);
            //move to parametrized pfn evaluation:
            add_pfn_histograms(lep_region + quadrant);
        }
    }
}


void mini_analyzer::add_standard_histograms(TString prefix)
{
    hists[prefix+"_nTightJet"]          = new TH1F(prefix+"_nTightJet", ";N_{Jet};Events", 10, 0, 10);
    hists[prefix+"_JetPt"]              = new TH1F(prefix+"_JetPt", ";Jet #it{p}_{T} [GeV];Events", 10, 0, 100);
    hists[prefix+"_JetEta"]             = new TH1F(prefix+"_JetEta", ";Jet #eta;Events", 10, -3, 3);
    hists[prefix+"_JetPhi"]             = new TH1F(prefix+"_JetPhi", ";Jet #phi;Events", 10, -3.14, 3.14);
    hists[prefix+"_nTightLep"]          = new TH1F(prefix+"_nTightLep", ";N_{Lep};Events", 10, 0, 10);
    hists[prefix+"_l2_pt"]              = new TH1F(prefix+"_l2_pt", ";l_{2} #it{p}_{T} [GeV];Events", 10, 0, 50);
    hists[prefix+"_l2_eta"]             = new TH1F(prefix+"_l2_eta", ";l_{2} #eta;Events", 10, -3, 3);
    hists[prefix+"_l2_phi"]             = new TH1F(prefix+"_l2_phi", ";l_{2} #phi;Events", 10, -3.14, 3.14);
    hists[prefix+"_l2_dxy"]             = new TH1F(prefix+"_l2_dxy", ";l_{2} dxy [cm];Events", 10, 0, 0.5);
    hists[prefix+"_l2_dz"]              = new TH1F(prefix+"_l2_dz", ";l_{2} dz [cm];Events", 10, 0, 2);
    hists[prefix+"_l2_3dIPSig"]         = new TH1F(prefix+"_l2_3dIPSig", ";l_{2} 3dIPSig;Events", 10, 0, 20);
    hists[prefix+"_l2_reliso"]          = new TH1F(prefix+"_l2_reliso", ";l_{2} Rel Iso;Events", 10, 0, 3.5);
    hists[prefix+"_l2_ptratio"]         = new TH1F(prefix+"_l2_ptratio", ";l_{2} #it{p}_{T}^{ratio} [GeV];Events", 10, 0, 1);
    hists[prefix+"_l2_ptrel"]           = new TH1F(prefix+"_l2_ptrel", ";l_{2} #it{p}_{T}^{rel} [GeV];Events", 10, 0, 10);
    hists[prefix+"_l2_NumberOfHits"]    = new TH1F(prefix+"_l2_NumberOfHits", ";l_{2} Nr. of Hits;Events", 10, 0, 10);
    hists[prefix+"_l2_NumberOfPixHits"] = new TH1F(prefix+"_l2_NumberOfPixHits", ";l_{2} Nr. of Pixel Hits;Events", 15, 0, 15);
    
    hists[prefix+"_l1_pt"]              = new TH1F(prefix+"_l1_pt", ";l_{1} #it{p}_{T} [GeV];Events", 10, 0, 150);
    hists[prefix+"_l1_eta"]             = new TH1F(prefix+"_l1_eta", ";l_{1} #eta;Events", 10, -3, 3);
    hists[prefix+"_l1_phi"]             = new TH1F(prefix+"_l1_phi", ";l_{1} #phi;Events", 10, -3.14, 3.14);

    hists[prefix+"_mll"]                = new TH1F(prefix+"_mll", ";#it{m}_{ll} [GeV];Events", 10, 0, 200);
    hists[prefix+"_dRll"]               = new TH1F(prefix+"_dRll", ";#it{#Delta R}_{ll};Events", 10, 0, 6);
    hists[prefix+"_dphill"]             = new TH1F(prefix+"_dphill", ";#it{#Delta #phi}_{ll};Events", 10, 0, 3.14);
    hists[prefix+"_dRljet"]             = new TH1F(prefix+"_dRljet", ";#it{#Delta R}_{ll};Events", 10, 0, 1.5);

    hists[prefix+"_IVF_PV-SVdxy"]       = new TH1F(prefix+"_IVF_PV-SVdxy", ";#Delta_{xy}(PV, SV_{fit}) [cm];Events", 10, 0, 60);
    hists[prefix+"_IVF_PV-SVdxy_zoom"]  = new TH1F(prefix+"_IVF_PV-SVdxy_zoom", ";#Delta_{xy}(PV, SV_{fit}) [cm];Events", 10, 0, 20);
    hists[prefix+"_IVF_PV-SVdxyz"]      = new TH1F(prefix+"_IVF_PV-SVdxyz", ";#Delta_{xyz}(PV, SV_{fit}) [cm];Events", 10, 0, 100);
    hists[prefix+"_IVF_PV-SVdxyz_zoom"] = new TH1F(prefix+"_IVF_PV-SVdxyz_zoom", ";#Delta_{xyz}(PV, SV_{fit}) [cm];Events", 10, 0, 20);
    hists[prefix+"_IVF_ntracks"]        = new TH1F(prefix+"_IVF_ntracks", ";# of tracks used in SVfit;Events", 15, 0, 15);
    hists[prefix+"_IVF_mass"]           = new TH1F(prefix+"_IVF_mass", ";SV Mass [GeV];Events", 10, 0, 20);
    hists[prefix+"_IVF_l1mass"]         = new TH1F(prefix+"_IVF_l1mass", ";SV Mass [GeV];Events", 10, 0, 150);
    hists[prefix+"_IVF_pt"]             = new TH1F(prefix+"_IVF_pt", ";SV #it{p}_{T} [GeV];Events", 10, 0, 100);
    hists[prefix+"_IVF_eta"]            = new TH1F(prefix+"_IVF_eta", ";SV #eta;Events", 10, -3, 3);
    hists[prefix+"_IVF_phi"]            = new TH1F(prefix+"_IVF_phi", ";SV #phi;Events", 10, -3.14, 3.14);
    hists[prefix+"_IVF_normchi2"]       = new TH1F(prefix+"_IVF_normchi2", ";Normalized #Chi^{2};Events", 10, 0, 10);

}

void mini_analyzer::add_pfn_histograms(TString prefix)
{
    hists[prefix+"_JetTagVal"]          = new TH1F(prefix+"_JetTagVal", ";Jet Tag Value;Events", 10, 0, 1);
}

void mini_analyzer::fill_histograms()
{
    fill_standard_histograms(sr_flavor + quad, event._weight);
    fill_pfn_histograms(sr_flavor + quad, event._weight * event._reweighting_weight[0], 0);

    if(isA or isB){
        fill_standard_histograms(sr_flavor + "_quadAB", event._weight);
        fill_pfn_histograms(sr_flavor + "_quadAB", event._weight * event._reweighting_weight[0], 0);
    }else if(isC or isD){
        fill_standard_histograms(sr_flavor + "_quadCD", event._weight);
        fill_pfn_histograms(sr_flavor + "_quadCD", event._weight * event._reweighting_weight[0], 0);
    }

}


void mini_analyzer::fill_standard_histograms(TString prefix, double event_weight)
{
    hists[prefix+"_nTightJet"]->Fill(event._nTightJet,event_weight);         
    hists[prefix+"_JetPt"]->Fill(event._JetPt,event_weight);             
    hists[prefix+"_JetEta"]->Fill(event._JetEta,event_weight);            
    hists[prefix+"_JetPhi"]->Fill(event._JetPhi,event_weight);            
    hists[prefix+"_nTightLep"]->Fill(event._nTightLep,event_weight);         
    hists[prefix+"_l2_pt"]->Fill(event._lPt,event_weight);             
    hists[prefix+"_l2_eta"]->Fill(event._lEta,event_weight);            
    hists[prefix+"_l2_phi"]->Fill(event._lPhi,event_weight);            
    hists[prefix+"_l2_dxy"]->Fill(event._ldxy,event_weight);            
    hists[prefix+"_l2_dz"]->Fill(event._ldz,event_weight);             
    hists[prefix+"_l2_3dIPSig"]->Fill(event._l3dIPSig,event_weight);        
    hists[prefix+"_l2_reliso"]->Fill(event._lrelIso,event_weight);         
    hists[prefix+"_l2_ptratio"]->Fill(event._lptRatio,event_weight);        
    hists[prefix+"_l2_ptrel"]->Fill(event._lptRel,event_weight);          
    hists[prefix+"_l2_NumberOfHits"]->Fill(event._lNumberOfHits,event_weight);   
    hists[prefix+"_l2_NumberOfPixHits"]->Fill(event._lNumberOfPixelHits,event_weight);
    
    hists[prefix+"_l1_pt"]->Fill(event._l1Pt,event_weight);             
    hists[prefix+"_l1_eta"]->Fill(event._l1Eta,event_weight);            
    hists[prefix+"_l1_phi"]->Fill(event._l1Phi,event_weight);            
                                       
    hists[prefix+"_mll"]->Fill(event._mll,event_weight);               
    hists[prefix+"_dRll"]->Fill(event._dRll,event_weight);              
    hists[prefix+"_dphill"]->Fill(event._dphill,event_weight);            
    hists[prefix+"_dRljet"]->Fill(event._dRljet,event_weight);            
                                       
    hists[prefix+"_IVF_PV-SVdxy"]->Fill(event._SV_PVSVdist_2D,event_weight);      
    hists[prefix+"_IVF_PV-SVdxy_zoom"]->Fill(event._SV_PVSVdist_2D,event_weight); 
    hists[prefix+"_IVF_PV-SVdxyz"]->Fill(event._SV_PVSVdist,event_weight);     
    hists[prefix+"_IVF_PV-SVdxyz_zoom"]->Fill(event._SV_PVSVdist,event_weight);
    hists[prefix+"_IVF_ntracks"]->Fill(event._SV_ntracks,event_weight);       
    hists[prefix+"_IVF_mass"]->Fill(event._SV_mass,event_weight);          
    hists[prefix+"_IVF_l1mass"]->Fill(event._SV_l1mass,event_weight);        
    hists[prefix+"_IVF_pt"]->Fill(event._SV_pt,event_weight);            
    hists[prefix+"_IVF_eta"]->Fill(event._SV_eta,event_weight);           
    hists[prefix+"_IVF_phi"]->Fill(event._SV_phi,event_weight);           
    hists[prefix+"_IVF_normchi2"]->Fill(event._SV_normchi2,event_weight);      
}


void mini_analyzer::fill_pfn_histograms(TString prefix, double event_weight, unsigned i)
{
    hists[prefix+"_JetTagVal"]->Fill(event._JetTagVal[i], event_weight);
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
