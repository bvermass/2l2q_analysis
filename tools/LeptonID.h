//////////////////////////////////////////////////////////////////////
//Helper Class for Lepton identification and finding leading leptons//
//////////////////////////////////////////////////////////////////////

#ifndef LeptonID_h
#define LeptonID_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>


class LeptonID {
    public :
        LeptonID();
        ~LeptonID();
        virtual void test_function();
};

#endif

#ifdef LeptonID_cc
LeptonID::LeptonID()
{

}


LeptonID::~LeptonID()
{

}
#endif
