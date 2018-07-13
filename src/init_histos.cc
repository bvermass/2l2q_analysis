///////////////////////////////////////////////////////
//initializes histograms, part of class full_analyzer//
///////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

void full_analyzer::add_histogram(std::map<TString, TH1*>* hists, TString prefix){
    (*hists)[prefix+"_pt"]                  = new TH1F(prefix+"_pt", ";#it{p}_{T} [GeV];Events", 80, 0, 200);
    return;
}
