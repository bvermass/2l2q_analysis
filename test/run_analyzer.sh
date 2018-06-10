#!/bin/bash

#First argument must be the txt file containing the samples that have to be run
headdir="/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_9_4_0/src/2l2q_analysis"
cd $headdir
echo 

#compile code
if g++ ${headdir}"/src/full_analyzer_ee.cc" ${headdir}"/src/full_analyzer.cc" ${headdir}"/test/mainroot.cc" `root-config --cflags --glibs`; then
    echo -e "COMPILATION SUCCESSFUL\n"
    #execute code for every file necessary
    while IFS='' read -r line || [[ -n "$line" ]]; do
        for val in $line; do
            cols+=("$val")
        done
        inputfile="${cols[0]}"; 
        cross_section="${cols[1]}";
        #root -l -b -q ${headdir}"src/full_analyzer.cc+" ${headdir}"test/mainroot.cc(\"$line\")" #maybe add an option to compile using this line, meaning Aclic
        echo "run.sh file: "$line
        ./a.out $inputfile $cross_section
        echo 
    done < "$1"
else
    echo -e "COMPILATION FAILED\n"
fi

