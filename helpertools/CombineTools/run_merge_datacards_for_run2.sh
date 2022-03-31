#!/bin/bash

cd /user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit && eval `scram runtime -sh`
cd /user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_14/src/2l2q_analysis
python helpertools/CombineTools/merge_datacards_for_run2.py
eval `scram runtime -sh`
