
////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, all helper functions to creating histograms//
////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

//move histo bin naming etc. to here!
using namespace std;

void full_analyzer::make_logscale(double* xbins, int nbins, double xmin, double xmax)
{
    double logxmin = TMath::Log10(xmin);
    double logxmax = TMath::Log10(xmax);
    double binwidth = (logxmax - logxmin)/nbins;
    for(unsigned i = 0; i <= nbins; ++i){
        *(xbins+i) = TMath::Power(10, logxmin + i*binwidth);
    }
}

TString full_analyzer::make_outputfilename(TString filename, TString base_directory, int partition, int partitionjobnumber)
{
    TString outputfilename = base_directory;
    if(filename.Index("dilep_") != -1) outputfilename += filename(filename.Index("dilep_") + 6, filename.Index(".root") - 6 - filename.Index("dilep_")) + "/full_analyzer/";
    else outputfilename += "full_analyzer/";
    
    if(partition != 1) {
        outputfilename += "subfiles/";
        if(filename.Index("HeavyNeutrino") != -1) outputfilename += filename(filename.Index("HeavyNeutrino_"), filename.Index("dilep") - 1 - filename.Index("HeavyNeutrino_")) + "/";
        else outputfilename += "Background_" + filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep") - filename.Index("heavyNeutrino") - 15) + "/";
    }
    
    gSystem->Exec("mkdir -p " + outputfilename);

    if(filename.Index("HeavyNeutrino") != -1) outputfilename += "hists_full_analyzer_" + filename(filename.Index("HeavyNeutrino_"), filename.Index("dilep") - 1 - filename.Index("HeavyNeutrino_"));
    else outputfilename += "hists_full_analyzer_Background_" + filename(filename.Index("heavyNeutrino") + 14, filename.Index("dilep") - filename.Index("heavyNeutrino") - 15);
    
    if(partition != 1) outputfilename += "_job_" + to_string(static_cast<long long>(partitionjobnumber)) + ".root";
    else outputfilename += ".root";

    return outputfilename;
}
