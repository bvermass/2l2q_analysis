#!/bin/bash

# this script will recompile combine and CMSSW, normally, this is unnecessary to rerun

#move into combine directory
cd ~/heavyNeutrino/Dileptonprompt/CMSSW_8_1_0/src/HiggsAnalysis/CombinedLimit/

export SCRAM_ARCH=slc6_amd64_gcc530
eval `scram runtime -sh`
scramv1 b clean; scramv1 b
