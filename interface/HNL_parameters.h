/////////////////////////////////////
// Header for class HNL_parameters //
/////////////////////////////////////

#ifndef HNL_parameters_h
#define HNL_parameters_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

// other headers to communicate with
#include "../interface/helper_histo_functions.h"

class HNL_parameters
{
    public:
        TString HNL_parameters_filename;
        TString HNL_sample_filename;

        // parameters from file
        bool isValid;
        std::string recommended, type, year, directory;
        double mass, V2, ctau, ctauRatioToTheory, cross_section, cross_section_unc;
        int events;

        //Functions
        HNL_parameters(TString parameters_filename, TString HNL_sample_filename);//Constructor meant to read existing file and access events
        //void open_file_and_tree(TString filename);
        //void set_branch_adresses();
        //void analyze(int max_entries, int partition, int partitionjobnumber);
        //void fill_tree();
        //void write_tree();
        //void delete_tree();
};
#endif
