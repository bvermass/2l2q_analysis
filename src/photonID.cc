////////////////////////////////////////////////////////////////////////////////////////////
//part of class full_analyzer, code for determining photon ID and photon related functions//
////////////////////////////////////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

std::vector<bool> full_analyzer::get_photonID()
{
    std::vector<bool> photonID;
    for(unsigned i = 0; i < _nPh; ++i){
        photonID.push_back(_phCutbasedTight[i]);
    }
    return photonID;
}
