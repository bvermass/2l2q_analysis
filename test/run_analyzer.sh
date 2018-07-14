#!/bin/bash

#First argument must be the txt file containing: SAMPLENAME CROSS-SECTION MaxEntry(to avoid crashes)
headdir="/home/basile/Documents/PhD/code/2l2q_analysis"
#headdir="/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_9_4_0/src/2l2q_analysis"
cd $headdir

#compile code
if g++ -o a_interactive.out ${headdir}"/src/jetID.cc" ${headdir}"/src/leptonID.cc" ${headdir}"/src/histo_functions.cc" ${headdir}"/src/full_analyzer_constructor.cc" ${headdir}"/src/full_analyzer_ee.cc" ${headdir}"/src/full_analyzer.cc" ${headdir}"/src/print_table.cc" ${headdir}"/test/mainroot.cc" `root-config --cflags --glibs`; then
    echo -e "\n//////////////////////////"
    echo -e "//COMPILATION SUCCESSFUL//"
    echo -e "//////////////////////////\n"

    #exec_analyzer will process input and run a.out
    bash ${headdir}/test/scripts/exec_analyzer.sh $1 a_interactive.out
    rm a_interactive.out

else
    echo -e "\n//////////////////////"
    echo -e "//COMPILATION FAILED//"
    echo -e "//////////////////////\n"
fi

