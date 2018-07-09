#!/bin/bash

#First argument must be the txt file containing: SAMPLENAME CROSS-SECTION MaxEntry(to avoid crashes)
headdir="/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_9_4_0/src/2l2q_analysis"
cd $headdir

#compile code
if g++ ${headdir}"/src/full_analyzer_ee.cc" ${headdir}"/src/full_analyzer.cc" ${headdir}"/test/mainroot.cc" `root-config --cflags --glibs`; then
    echo -e "\n//////////////////////////"
    echo -e "//COMPILATION SUCCESSFUL//"
    echo -e "//////////////////////////\n"

    #exec_analyzer will process input and run a.out
    sh ${headdir}/test/scripts/exec_analyzer.sh $1
    rm a.out

else
    echo -e "\n//////////////////////"
    echo -e "//COMPILATION FAILED//"
    echo -e "//////////////////////\n"
fi

