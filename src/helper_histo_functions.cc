
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
