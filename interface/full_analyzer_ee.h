#ifndef full_analyzer__ee_h
#define full_analyzer__ee_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "full_analyzer.h"

// Header file for the classes stored in the TTree if any.

class full_analyzer_ee {
public :
    double a;
    full_analyzer_ee(double b);
    virtual double test();
    full_analyzer b;

};



#endif

