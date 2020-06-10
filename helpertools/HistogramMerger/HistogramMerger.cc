#include "HistogramMerger.h"

// About input sample list, these are the same lists used for plotting:
// First line is plotting instructions, irrelevant for histogram merging
// All lines after that are input filenames with histograms inside, except the line with legend name 'combined', this will be the name of the file where merged histograms will end up.
// the file 'identifiers.txt' in this directory is meant to contain identifiers to be compared against the histogram name. Only matches are merged and put in the destination file

bool equals(double a, double b){ return (fabs(a - b) < 1e-50); }

HistogramMerger::HistogramMerger(TString filename)
{
    TH1::AddDirectory(kFALSE);//https://root.cern.ch/input-and-output
    const char* delim = " ";

    std::string line;
    std::ifstream sampleList(filename);

    if(sampleList.is_open()){
        while(std::getline(sampleList, line)){
            
            std::vector<std::string> line_split;
            size_t start, end = 0;
            while((start = line.find_first_not_of(delim, end)) != std::string::npos){
                end = line.find(delim, start);
                line_split.push_back(line.substr(start, end - start));
            }

            if(line_split[0].find(".root") == std::string::npos) continue; 

            if(line_split[1].find("combined") != std::string::npos) outputfilename = line_split[0];
            else inputfilenames.push_back(line_split[0]);
        }
    }

    identifiers = init_identifiers("identifiers.txt", ",");
}


void HistogramMerger::inverse_variance_weighted_merging()
{
    std::vector<TFile*> files;
    for(unsigned i = 0; i < inputfilenames.size(); i++){
        std::cout << "opening " << inputfilenames[i] << std::endl;
        files.push_back(TFile::Open(inputfilenames[i]));
    }

    std::vector<TH1F*> result_hists;

    TIter next(files.front()->GetListOfKeys());
    TKey* key;
    while((key = (TKey*)next())){
            
        TClass *cl = gROOT->GetClass(key->GetClassName());
        // -- TH1 --
        if (cl->InheritsFrom("TH1") and ! cl->InheritsFrom("TH2")){ // second requirement is because TH2 also inherits from TH1
            // Get a reference histogram for the name, then get all histograms in  a vector, and calculate the resulting merged histogram
            TH1F*   sample_hist_ref = (TH1F*)key->ReadObj();
            TString histname   = sample_hist_ref->GetName();

            if(!check_identifiers(histname)) continue;
            std::cout << histname << std::endl;

            // get histogram from all inputs
            std::vector<TH1F*> hists;
            for(const auto& file : files){
                TH1F* h = (TH1F*)file->Get(histname);
                if(h and h->GetMaximum() > 0)
                    hists.push_back(h);
            }
            if(hists.size() == 0) continue;

            result_hists.push_back(do_inverse_variance_weighted_merging(hists));
        }
    }

    for(TFile* file : files){
        file->Close();
    }


    std::cout << "output to: " << outputfilename << std::endl;
    TFile *output = new TFile(outputfilename, "recreate");

    for(const TH1F* h : result_hists){
        h->Write(h->GetName(), TObject::kOverwrite);
    }

    std::cout << "close file" << std::endl;
    output->Close();
}


TH1F* HistogramMerger::do_inverse_variance_weighted_merging(std::vector<TH1F*> hists)
{
    //https://en.wikipedia.org/wiki/Inverse-variance_weighting
    TH1F* result = (TH1F*)hists.front()->Clone();

    for(int i = 1; i <= result->GetNbinsX(); i++){

        //std::cout << "bin " << i << std::endl;
        double mean = 0, normalization = 0;
        for(const TH1F* h : hists){
            double variance = h->GetBinError(i) * h->GetBinError(i);
            double X = h->GetBinContent(i);
            //std::cout << "content and error: " << X << " +- " << variance << std::endl;
            if(equals(variance, 0) or equals(X, 0)) continue;
            mean += X / variance;
            normalization += 1. / variance;
        }

        if(equals(normalization, 0)){
            result->SetBinContent(i, mean);
            result->SetBinError(i, 0.);
        }else {
            // set result to inverse variance weighted mean
            result->SetBinContent(i, mean / normalization);
            result->SetBinError(i, sqrt(1. / normalization));
        }
        //std::cout << "mean and error: " << result->GetBinContent(i) << " +- " << result->GetBinError(i) << std::endl;

    }

    return result;
}


std::vector<std::vector<TString>> HistogramMerger::init_identifiers(TString identifier_filename, const char* delim)
{
    std::string line;
    std::ifstream identifier_file (identifier_filename);
    std::vector<std::vector<TString>> identifiers; // 2D vector, vector of vectors where inner vectors are to be used in AND mode (outer in OR mode)
    if(identifier_file.is_open()){
        while(std::getline(identifier_file, line)){
            std::vector<TString> AND_identifiers;
            size_t start, end = 0;
            while((start = line.find_first_not_of(delim, end)) != std::string::npos){
                end = line.find(delim, start);
                AND_identifiers.push_back(line.substr(start, end - start));
            }
            identifiers.push_back(AND_identifiers);
        }
        identifier_file.close();
    }
    return identifiers;
}


bool HistogramMerger::check_identifiers(TString histname)
{
    // Inner vector of strings are parts of the histname that have to match altogether, e.g. _OS_e AND _mll have to be in the name (put as _OS_e,_mll in identifier.txt)
    // Outer vector is in OR mode for the tags (different lines in identifier.txt)
    bool check = true;
    for(auto& stringvector : identifiers){
        check = true;
        for(TString id : stringvector){
            if(histname.Index(id) != -1) continue;
            check = false;
            break;
        }
        if(check) break;
    }
    return check;
}


HistogramMerger::~HistogramMerger()
{
}
