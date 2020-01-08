#!/bin/bash

./test/scripts/run_combine_datacards_all.sh
cd ~/heavyNeutrino/Dileptonprompt/CMSSW_8_1_0/src/CombineScripts/
eval `scram runtime -sh`
./setup.sh
./moveScriptToDirAndRunCombine.sh
cd ~/heavyNeutrino/Dileptonprompt/CMSSW_10_2_14/src/2l2q_analysis/helpertools/CombineTools
cmsenv
./runCombineOutputPrep.sh
./runAnalyzeCombineOutput.sh
