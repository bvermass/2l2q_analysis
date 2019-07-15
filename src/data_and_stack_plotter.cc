#include "../interface/data_and_stack_plotter.h"
#include "../interface/plotterfunctions.h"
#include "../interface/helper_plotter_functions.h"

// Argument 1 in argv will be the subdirectory specific name
// Argument 2 in argv will be the partition
// Argument 3 in argv will be the partitionjobnumber
// Argument 4 in argv will be the datafile
// Argument 5 in argv will be the data legend
// Argument 6 - ((argc + 6)/2 - 1)  will be the root sample files
// Argument ((argc + 6)/2) - (argc - 1) will be the legends for the sample files
# ifndef __CINT__
int main(int argc, char * argv[])
{
// program flow:
//  - put names of background files and names of legends in 2 separate vectors for much easier access
//  - make general pathname of where plots need to go
//  - define canvas
//  - define legend shape
//  - put background files in a vector (used to be a map, but vector seems to make more sense
//  - get data file
    TString general_pathname = make_general_pathname("stacks_with_data/", ((TString)argv[1]) + "/", "");

    std::vector<TFile*>  bkg_files;
    std::vector<TH1*>    bkg_hists; // will be filled  each loop
    std::vector<TString> bkg_legends;
    for(int i = 6; i < (argc + 6)/2; i++){
        std::cout << "file + legend: " << (TString)argv[i] << " + " << (TString)argv[i + (argc-6)/2] << std::endl;
        bkg_files.push_back(TFile::Open((TString)argv[i]));
        bkg_legends.push_back((TString)argv[i + (argc - 6)/2]);
    }

    TCanvas *c = get_canvas();
    TLegend lgnd = get_legend(.67,.67,.87,.87);

    TFile* data_file = TFile::Open((TString)argv[4]);
    TString data_legend = (TString)argv[5];

    TIter next(data_file->GetListOfKeys());
    TKey* key;

    Int_t partition = std::atoi(argv[2]);
    Int_t partitionjobnumber = std::atoi(argv[3]);
    Int_t counter_begin = floor(1.0 * partitionjobnumber / partition * data_file->GetNkeys());
    Int_t counter_end   = floor(1.0 * (partitionjobnumber + 1) / partition * data_file->GetNkeys());
    Int_t counter       = 0;

    while(key = (TKey*)next()){
        if(counter >= counter_begin and counter , counter_end){
            bkg_hists.clear();
            lgnd.Clear();

            // get correct reference histogram (is also the data one)
            TClass *cl = gROOT->GetClass(key->GetClassName());
            if (!cl->InheritsFrom("TH1") or cl->InheritsFrom("TH2")) continue; //don't plot 2d plots or TGraphAsymmErrors(efficiencies) for now ( don't know why a stack plot of this would be useful
            TH1F* data_hist = (TH1F*)key->ReadObj();
            TString histname = data_hist->GetName();
            std::cout << histname << std::endl;
            if(data_hist->GetMaximum() == 0) continue;
            if(histname.Index("_CR") == -1) continue;
            
            // get histogram name (to get corresponding other histos and for other stuff

            // get stack of bkg histograms
            THStack* stack = new THStack("bkg_stack", histname);
            for(int i = 0; i < bkg_files.size(); i++){
                TH1* h = (TH1*)bkg_files[i]->Get(histname);
                h->SetMarkerSize(0);
                stack->Add(h);
                if(h->GetMaximum() != 0) lgnd.AddEntry(h, bkg_legends[i]);
            }

            // Construct data as a TGraphErrors object
            TGraphErrors* data_graph = new TGraphErrors(data_hist);
            graphstyle(data_graph);
            lgnd.AddEntry(data_graph, data_legend);

            TString pathname_lin    = make_plotspecific_pathname(histname, general_pathname, "lin");
            TString pathname_log    = make_plotspecific_pathname(histname, general_pathname, "log");
            gSystem->Exec("mkdir -p " + pathname_lin);
            gSystem->Exec("mkdir -p " + pathname_log);

            // x log or lin
            int xlog = (histname.Index("xlog") == -1)? 0 : 1;
            // Events or Eff. in yaxis title
            TString yaxistitle = data_hist->GetYaxis()->GetTitle(); 

            draw_stack_with_data(pathname_lin + histname + ".pdf", c, stack, data_graph, "0P", &lgnd, data_hist->GetXaxis()->GetTitle(), yaxistitle, 0, xlog, -1, -1, -1, -1, "");
            draw_stack_with_data(pathname_log + histname + ".pdf", c, stack, data_graph, "0P", &lgnd, data_hist->GetXaxis()->GetTitle(), yaxistitle, 1, xlog, -1, -1, 1, -1, "");
        }
        counter++;
    }
    std::cout << "plots finished" << std::endl;
}
#endif
