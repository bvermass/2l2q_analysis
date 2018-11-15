////////////////////////////////////////////////////////////
//part of class full_analyze, code for finding good vertex//
////////////////////////////////////////////////////////////

#include "../interface/full_analyzer.h"

using namespace std;

//obsolete at the moment (the matching is done at gen level!
int full_analyzer::find_vtx_matching_to_lepton(int i_lepton){
    //find track in vtx matching to lepton
    //for now, by matching lepton pt eta phi to track pt eta phi, but change this at ntuplizer level to use track information and store linked vertex in a variable
    double mindR = 5;
    int i_match = -1;
    if(i_lepton == -1) return -1;
    //cout << endl << endl << "LEPTON pt, eta, phi: " << _lPt[i_lepton] << " " << _lEta[i_lepton] << " " << _lPhi[i_lepton] << endl;
    for(int i_vtx = 0; i_vtx < _IVF_nvertex; i_vtx++){
        for(int i_track = 0; i_track < _IVF_ntracks[i_vtx]; i_track++){
            if(fabs(_lPt[i_lepton] - _IVF_trackpt[i_vtx][i_track]) < 5 and fabs(_lEta[i_lepton] - _IVF_tracketa[i_vtx][i_track]) < 0.1 and fabs(_lPhi[i_lepton] - _IVF_trackphi[i_vtx][i_track]) < 0.1){
                if(fabs(_lEta[i_lepton] - _IVF_tracketa[i_vtx][i_track]) + fabs(_lPhi[i_lepton] - _IVF_trackphi[i_vtx][i_track]) < mindR){
                    mindR = fabs(_lEta[i_lepton] - _IVF_tracketa[i_vtx][i_track]) + fabs(_lPhi[i_lepton] - _IVF_trackphi[i_vtx][i_track]);
                    i_match = i_vtx;
                    //cout << "TRACK pt, eta, phi: " << _IVF_trackpt[i_vtx][i_track] << " " << _IVF_tracketa[i_vtx][i_track] << " " << _IVF_trackphi[i_vtx][i_track] << endl;
                }
            }
        }
    } 
    return i_match;
}
