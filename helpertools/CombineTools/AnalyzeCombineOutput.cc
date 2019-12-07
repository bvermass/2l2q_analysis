#include "AnalyzeCombineOutput.h"

# ifndef __CINT__
int main(int argc, char * argv[])
{
    if(argc != 2){
        std::cout << "Command should be ./test [combine_rootfile_dir]" << std::endl;
        return 1;
    }
    //Argument 1: text file containing all necessary combine rootfiles to analyze
    //Code: the textfile is supposed to have combine rootfiles for 1 mass and a range of couplings.
    //      plot will be made of signal strength as a function of coupling
    TString txtfilename = (TString)argv[1];
    
    //From txtfile, read the combine output root files to be used for the plot
    std::string line;
    std::ifstream txtfile (txtfilename);
    std::vector<CombineOutput*> combineOutputs;
    if(txtfile.is_open()){
        while(std::getline(txtfile, line)){
            std::cout << line << std::endl;
            combineOutputs.push_back(new CombineOutput((TString)line));
        }
    }

    for(unsigned i = 0; i < combineOutputs.size(); i++){
        std::cout << std::endl << "processing " << combineOutputs[i]->combine_filename << std::endl;
        combineOutputs[i]->Loop();
    }
}
#endif


CombineOutput::CombineOutput(TString filename)
{
    combine_filename = filename;
    combine_file = new TFile(filename, "open");
    combine_tree = (TTree*) combine_file->Get("limit");
    Init(combine_tree);
}


void CombineOutput::Loop()
{
    unsigned nentries = combine_tree->GetEntries();
    for(unsigned jentry = 0; jentry < nentries; jentry++){
        combine_tree->GetEntry(jentry);
        std::cout << quantileExpected << ": " << limit << std::endl;
    }
}


void CombineOutput::Init(TTree* tree)
{
    if(!tree){
        std::cout << "Tree could not be initialized" << std::endl;
        return;
    }

    tree->SetMakeClass(1);
    tree->SetBranchAddress("limit", &limit, &b_limit);
    tree->SetBranchAddress("limitErr", &limitErr, &b_limitErr);
    tree->SetBranchAddress("syst", &syst, &b_syst);
    tree->SetBranchAddress("iToy", &iToy, &b_iToy);
    tree->SetBranchAddress("iSeed", &iSeed, &b_iSeed);
    tree->SetBranchAddress("quantileExpected", &quantileExpected, &b_quantileExpected);
}


CombineOutput::~CombineOutput()
{
    delete combine_tree;
    combine_file->Close();
    delete combine_file;
}
