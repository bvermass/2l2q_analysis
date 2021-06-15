#include "Skimmer.h"

bool Skimmer::IsPromptMuonID(const unsigned i)
{
    if(i_lFlavor[i] != 1)                            return false;
    if(fabs(i_lEta[i]) >= 2.4)                       return false;
    if(i_lPt[i] <= 10)                               return false;
    if(fabs(i_dxy[i]) >= 0.045)                      return false;
    if(fabs(i_dz[i]) >= 0.2)                         return false;
    if(i_relIso0p4MuDeltaBeta[i] >= 0.15)            return false;
    if(!i_lPOGMedium[i])                             return false;

    return true;
}

bool Skimmer::IsPromptElectronID(const unsigned i)
{
    if(i_lFlavor[i] != 0)                            return false;
    if(fabs(i_lEta[i]) >= 2.5)                       return false;
    if(fabs(i_lEta[i]) >= 1.4442 and fabs(i_lEta[i]) <= 1.5660) return false;
    if(i_lPt[i] <= 10)                               return false;
    if(fabs(i_dxy[i]) >= 0.045)                      return false;
    if(fabs(i_dz[i]) >= 0.2)                         return false;
    if(i_relIso[i] >= 0.15)                          return false;
    if(i_lElectronNumberInnerHitsMissing[i] >= 1)    return false;
    if(!i_lElectronPassConvVeto[i])                  return false;
    //if(!(passMvaFall17NoIso_WP90(i) or passMvaFall17Iso_WP90(i))) return false;

    return true;
}

bool Skimmer::passMvaFall17NoIso_WP90(const unsigned i)
{
    double mvaRaw = convertMvaInRawMva(i_lElectronMvaFall17NoIso[i]);
    int category = getEleMvaCategory(i);
    if (category == 0) return (mvaRaw > 2.77072387339 - exp(-i_lPt[i] / 3.81500912145) * 8.16304860178);
    if (category == 1) return (mvaRaw > 1.85602317813 - exp(-i_lPt[i] / 2.18697654938) * 11.8568936824);
    if (category == 2) return (mvaRaw > 1.73489307814 - exp(-i_lPt[i] / 2.0163211971) * 17.013880078);
    if (category == 3) return (mvaRaw > 5.9175992258  - exp(-i_lPt[i] / 13.4807294538) * 9.31966232685);
    if (category == 4) return (mvaRaw > 5.01598837255 - exp(-i_lPt[i] / 13.1280451502) * 8.79418193765);
    if (category == 5) return (mvaRaw > 4.16921343208 - exp(-i_lPt[i] / 13.2017224621) * 9.00720913211);
    std::cout << "did not find an electron Mva category!" << std::endl;
    return false;
}
bool Skimmer::passMvaFall17Iso_WP90(const unsigned i)
{
    double mvaRaw = convertMvaInRawMva(i_lElectronMvaFall17Iso[i]);
    int category = getEleMvaCategory(i);
    if (category == 0) return (mvaRaw > 2.84704783417 - exp(-i_lPt[i] / 3.32529515837) * 9.38050947827);
    if (category == 1) return (mvaRaw > 2.03833922005 - exp(-i_lPt[i] / 1.93288758682) * 15.364588247);
    if (category == 2) return (mvaRaw > 1.82704158461 - exp(-i_lPt[i] / 1.89796754399) * 19.1236071158);
    if (category == 3) return (mvaRaw > 6.12931925263 - exp(-i_lPt[i] / 13.281753835) * 8.71138432196);
    if (category == 4) return (mvaRaw > 5.26289004857 - exp(-i_lPt[i] / 13.2154971491) * 8.0997882835);
    if (category == 5) return (mvaRaw > 4.37338792902 - exp(-i_lPt[i] / 14.0776094696) * 8.48513324496);
    std::cout << "did not find an electron Mva category!" << std::endl;
    return false;
}

int Skimmer::getEleMvaCategory(const unsigned i)
{
    if (i_lPt[i] < 10 && fabs(i_lEtaSC[i]) < 0.800) return 0;
    if (i_lPt[i] < 10 && fabs(i_lEtaSC[i]) >= 0.800 && fabs(i_lEtaSC[i]) < 1.479) return 1;
    if (i_lPt[i] < 10 && fabs(i_lEtaSC[i]) >= 1.479) return 2;
    if (i_lPt[i] >= 10 && fabs(i_lEtaSC[i]) < 0.800) return 3;
    if (i_lPt[i] >= 10 && fabs(i_lEtaSC[i]) >= 0.800 && fabs(i_lEtaSC[i]) < 1.479) return 4;
    if (i_lPt[i] >= 10 && fabs(i_lEtaSC[i]) >= 1.479) return 5;
    return 0;
}

double Skimmer::convertMvaInRawMva(const double mva)
{
    return -0.5 * (std::log((1.-mva)/(1.+mva)));
}


bool Skimmer::IsCleanElectron(const unsigned i, const std::vector<unsigned>& muoncollection)
{
    if(i_lFlavor[i] != 0) return false;
	LorentzVector electron(i_lPt[i], i_lEta[i], i_lPhi[i], i_lE[i]);

    for(const auto& i_muon : muoncollection){
        LorentzVector muon(i_lPt[i_muon], i_lEta[i_muon], i_lPhi[i_muon], i_lE[i_muon]);

        if(deltaR(electron, muon) < 0.05) return false;
    }

    return true;
}


bool Skimmer::ElectronTriggerSkim(){return i_passTrigger_e;}


bool Skimmer::MuonTriggerSkim(){return i_passTrigger_m;}


bool Skimmer::dileptonSkim(){
    //Get muons and electrons that pass ID
    std::vector<unsigned> promptMuonID, promptElectronID;
    for(unsigned i = 0; i < i_nLight; i++){
        if(IsPromptMuonID(i))           promptMuonID.push_back(i);
    }
    unsigned nTightMu = promptMuonID.size();

    for(unsigned i = 0; i < i_nLight; i++){
        bool CleanElectron = IsCleanElectron(i, promptMuonID);

        if(IsPromptElectronID(i)    and CleanElectron) promptElectronID.push_back(i);
    }
    unsigned nTightEle = promptElectronID.size();

	int i_leading_e     		    = find_leading_lepton(promptElectronID);
	int i_leading_mu    		    = find_leading_lepton(promptMuonID);

	int i_subleading_e  		    = find_subleading_lepton(promptElectronID, i_leading_e);
	int i_subleading_mu 		    = find_subleading_lepton(promptMuonID, i_leading_mu);

    if(i_leading_e != -1 and i_subleading_e != -1){
        LorentzVector leadingvec(i_lPt[i_leading_e], i_lEta[i_leading_e], i_lPhi[i_leading_e], i_lE[i_leading_e]);
        LorentzVector subleadingvec(i_lPt[i_subleading_e], i_lEta[i_subleading_e], i_lPhi[i_subleading_e], i_lE[i_subleading_e]);
        double mass = (leadingvec + subleadingvec).mass();
        double dR = deltaR(leadingvec, subleadingvec);
        bool OS = (i_lCharge[i_leading_e] != i_lCharge[i_subleading_e]);
        if(mass > 70 and mass < 100 and dR > 0.3 and i_lPt[i_leading_e] > 29 and OS) return true;
    }
    
    if(i_leading_mu != -1 and i_subleading_mu != -1){
        LorentzVector leadingvec(i_lPt[i_leading_mu], i_lEta[i_leading_mu], i_lPhi[i_leading_mu], i_lE[i_leading_mu]);
        LorentzVector subleadingvec(i_lPt[i_subleading_mu], i_lEta[i_subleading_mu], i_lPhi[i_subleading_mu], i_lE[i_subleading_mu]);
        double mass = (leadingvec + subleadingvec).mass();
        double dR = deltaR(leadingvec, subleadingvec);
        bool OS = (i_lCharge[i_leading_mu] != i_lCharge[i_subleading_mu]);
        if(mass > 70 and mass < 100 and dR > 0.3 and i_lPt[i_leading_mu] > 25 and OS) return true;
    }
    
    return (nTightEle >= 2 or nTightMu >= 2);
}


int Skimmer::find_leading_lepton(const std::vector<unsigned>& leptoncollection)
{
    int index_leading = -1;

    for(const auto& index_lepton : leptoncollection){
        if(index_leading == -1) index_leading = (int)index_lepton;
        else if(i_lPt[index_lepton] > i_lPt[index_leading]) index_leading = (int)index_lepton;
    }

    return index_leading;
}

int Skimmer::find_subleading_lepton(const std::vector<unsigned>& leptoncollection, const int index_leading)
{
    if(index_leading == -1) return -1;
    int index_subleading = -1;

    for(const auto& index_lepton : leptoncollection){
        if((int)index_lepton == index_leading) continue;

        if(index_subleading == -1) index_subleading = (int)index_lepton;
        else if(i_lPt[index_lepton] > i_lPt[index_subleading]) index_subleading = (int)index_lepton;
    }

    return index_subleading;
}


bool Skimmer::Check_SkimCondition(TString Condition)
{
    if(Condition == "dileptonSkim") return ((ElectronTriggerSkim() or MuonTriggerSkim()) and dileptonSkim());
    else return true;
}
