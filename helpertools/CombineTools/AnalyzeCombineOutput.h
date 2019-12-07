/////////////////////////////////////////////////////////
// CombinePrep prepares datacards for the Combine Tool //
/////////////////////////////////////////////////////////


#ifndef AnalyzeCombineOutput_h
#define AnalyzeCombineOutput_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>

#include <iostream>
#include <fstream>
#include <cmath>

#include <string>
#include <utility>
#include <TSystem.h>

# ifndef __CINT__ 
int main(int argc, char * argv[]);
#endif

class CombineOutput
{
    public:
        TString combine_filename;
        TFile* combine_file;
        TTree* combine_tree;

        CombineOutput(TString filename);
        ~CombineOutput();
        void Loop();
        void Init(TTree* tree);

        // tree variables and branches
        double limit;
        double limitErr;
        int syst; //syst not included(0), or included(1) 
        int iToy;
        int iSeed;
        float quantileExpected;

        TBranch *b_limit;
        TBranch *b_limitErr;
        TBranch *b_syst;
        TBranch *b_iToy;
        TBranch *b_iSeed;
        TBranch *b_quantileExpected;
};
#endif
