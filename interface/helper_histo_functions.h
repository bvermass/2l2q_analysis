////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, all helper functions to creating histograms//
////////////////////////////////////////////////////////////////////////////

#ifndef helper_histo_functions_h
#define helper_histo_functions_h

#include <TROOT.h>
#include <TMath.h>
#include <TSystem.h>
#include <TString.h>

void        make_logscale(double* xbins, int nbins, double xmin, double xmax);
TString     make_outputfilename(TString filename, TString base_directory, TString base_filename, int partition, int partitionjobnumber);
double      calc_betagamma(int particle_mass, double particle_energy);

#endif
