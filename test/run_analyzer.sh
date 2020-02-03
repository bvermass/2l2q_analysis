#!/bin/bash

#First argument must be the txt file containing: SAMPLENAME CROSS-SECTION MaxEntry(to avoid crashes)
headdir=$(pwd)

#compile code
if g++ -Wall -Wno-reorder -Wextra -I/cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/python/2.7.14-omkpbe4/include/python2.7 -L/cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/python/2.7.14-omkpbe4/lib -lpython2.7  -lboost_python -std=c++11 -o a_interactive.out ${headdir}"/src/MET_histograms.cc" ${headdir}"/helpertools/LSFReader/LSFReader.cc" ${headdir}"/helpertools/PUWeightReader/PUWeightReader.cc" ${headdir}"/helpertools/LorentzVector/LorentzVector.cc" ${headdir}"/helpertools/PFNEvaluation/PFNReader.cc" ${headdir}"/src/PFNTools.cc" ${headdir}"/src/HNLtagger.cc" ${headdir}"/src/jet_histograms.cc" ${headdir}"/src/helper_histo_functions.cc" ${headdir}"/src/gen_histograms.cc" ${headdir}"/src/signal_region.cc" ${headdir}"/src/HLT_eff.cc" ${headdir}"/src/jetID.cc" ${headdir}"/src/leptonID.cc" ${headdir}"/src/histo_functions.cc" ${headdir}"/src/full_analyzer_constructor.cc" ${headdir}"/src/full_analyzer.cc" ${headdir}"/src/print_table.cc" ${headdir}"/test/mainroot.cc" `root-config --cflags --glibs`; then
    echo -e "\n//////////////////////////"
    echo -e "//COMPILATION SUCCESSFUL//"
    echo -e "//////////////////////////\n"

    # I'll need to read the input file, and for every line, read partition, then make separate job files for each partitionjobnumber. then exec_analyzer.sh can be executed for each job file.
    tmp=${headdir}"/test/sampleLists/tmp/tmp_for_run_analyzer.txt"
    > $tmp

    while IFS='' read -r line || [[ -n "$line" ]]; do
        if [[ ! "$line" =~ [^[:space:]] ]] || [[ "${line:0:1}" = "#" ]]; then
            echo -e ""
        else
            counter=0
            for val in $line; do 
                if [ $counter -eq 0 ]; then
                    inputfile=$val
                    counter=1
                elif [ $counter -eq 1 ]; then
                    cross_section=$val
                    counter=2
                elif [ $counter -eq 2 ]; then
                    max_entries=$val
                    counter=3
                else 
                    partition=$val
                    counter=0
                fi
            done
             
            partitionjobnumber=0
            while [[ ! $partitionjobnumber -eq $partition ]]; do
                echo $line" "$partitionjobnumber > $tmp
                #exec_analyzer will process the input in tmp again and run a_interactive.out
                bash ${headdir}/test/scripts/exec_analyzer.sh $tmp a_interactive.out
                let "partitionjobnumber++"
            done
        fi
    done < "$1"
    rm a_interactive.out
    rm $tmp
else
    echo -e "\n//////////////////////"
    echo -e "//COMPILATION FAILED//"
    echo -e "//////////////////////\n"
fi

