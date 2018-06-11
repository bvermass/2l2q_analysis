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
        
        if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then
            echo "white line or comment found!"
        else
            #split sample name and cross section that are currenlty on single line
            counter=0
            for val in $line; do
                if [ $counter -eq 0 ]; then
                    inputfile=$val
                    counter=1
                else
                    cross_section=$val
                    counter=0
                fi
            done

            #root -l -b -q ${headdir}"src/full_analyzer.cc+" ${headdir}"test/mainroot.cc(\"$line\")" #maybe add an option to compile using this line, meaning Aclic
            echo "run_analyzer.sh file: "$inputfile
            ./a.out $inputfile $cross_section
            echo 
        fi
    done < "$1"
else
    echo -e "COMPILATION FAILED\n"
fi

