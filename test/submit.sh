#!/bin/bash

#First argument must be the txt file containing the samples that have to be run
headdir=$(pwd)
cd $headdir

#compile code
g++ ${headdir}"/plugin/full_analyzer.cc" ${headdir}"/test/mainroot.cc" `root-config --cflags --glibs`
echo "everything compiled"

#execute code for every file necessary
while IFS='' read -r line || [[ -n "$line" ]]; do
    #root -l -b -q ${headdir}"plugin/full_analyzer.cc+" ${headdir}"test/mainroot.cc(\"$line\")" #maybe add an option to compile using this line, meaning Aclic
    echo "submit.sh file: "$line
    ./a.out $line
done < "$1"
#${headdir}"tools/LeptonID.cc"  
