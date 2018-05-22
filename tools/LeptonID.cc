#define LeptonID_cc
#include "LeptonID.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>

using namespace std;

void LeptonID::test_function()
{
    cout << endl << endl << "heuj dit werkt blijkbaar" << endl << endl;
}


/*void LeptonID::get_electronID(bool* ID)
{
    for(unsigned i = 0; i < _nL; ++i){
	bool fullID = 	_lFlavor[i] == 0 &&
			fabs(_lEta[i]) < 2.5 &&
			_lPt[i] > 7 &&
			fabs(_dxy[i]) < 0.05 &&
			fabs(_dz[i])  < 0.1 &&
			_3dIPSig[i]   < 4 &&
			_relIso[i]    < 0.2 &&
			_lPOGMedium[i] &&
			_lElectronPassConvVeto[i] &&
			_lElectronMissingHits[i] < 1;
	if(fullID) *(ID + i) = true;
	else *(ID + i) = false;
    }
}*/


