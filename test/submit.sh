#!/bin/bash

#First argument must be the txt file containing the samples that have to be run
headdir="/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_9_4_0/src/2l2q_analysis/"

while IFS='' read -r line || [[ -n "$line" ]]; do
    root -l -b -q ${headdir}"tools/LeptonID.cc"  ${headdir}"plugin/full_analyzer.cc" ${headdir}"test/mainroot.cc(\"$line\")"
done < "$1"
