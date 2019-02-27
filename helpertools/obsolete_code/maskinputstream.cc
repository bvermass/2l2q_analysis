//line 52 - 69 of src/full_analyzer.cc with Moham_noBasile stuff with inputstream
    //Find out what is different about events in Moham_noBasile.csv
    // ifstream maskinputstream;
    // maskinputstream.open("../Moham_noBasile.csv");
    // string maskline;
    // int eventnumber[57];
    // double leppt[57];
    // int i_stream = 0;
    // if(maskinputstream.is_open()) {
    //     while(!maskinputstream.eof()) {
    //         getline(maskinputstream, maskline);
    //         if(maskline == "") continue;
    //         eventnumber[i_stream] = stoi(maskline.substr(0, maskline.find(" ")));
    //         leppt[i_stream]       = stod(maskline.substr(maskline.find(" ")));
    //         cout << "nb and pt: " << eventnumber[i_stream] << ", " << leppt[i_stream] << endl;
    //         i_stream++;
    //     }
    // }
    // maskinputstream.close();
    
// stuff in loop to check if event matches mask
        //bool matchmask = false;
        ////use Moham_noBasile.csv mask
        //for(int i = 0; i < 57; i++){
        //    //if(_eventNb == eventnumber[i]){
        //        //cout << "eventNb match, pt:";
        //        for(unsigned j = 0; j < _nL; j++){
        //            if(fabs(_lPt[j] - leppt[i]) <  0.0001){
        //                matchmask == true;
        //                count++;
        //                //cout << " " << _lPt[j] << " - " << leppt[i] << " eventnb: " << _eventNb << " " << eventnumber[i] << endl;
        //            }
        //        }
        //    //}
        //}
        //if(!matchmask) continue;
            //cout << "what";
            //cout << "nL, nJets, IsoTkMu24, IsoMu24: " << _nL << " " << _nJets << " " << _HLT_IsoTkMu24 << " " << _HLT_IsoMu24 << endl;
            //for(unsigned i = 0; i < _nL; i++){
            //    cout << "l pt, eta, phi, reliso, IVF_match: " << _lPt[i] << " " << _lEta[i] << " " << _lPhi[i] << " " << _relIso0p4MuDeltaBeta[i] << " " << _lIVF_match[i] << endl;
            //}
