#!/bin/bash

if g++ -Wall -Wno-reorder -Wextra -I/cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/python/2.7.14-omkpbe4/include/python2.7 -L/cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/python/2.7.14-omkpbe4/lib -lpython2.7  -lboost_python -std=c++0x -o a_makePUWeights.out "main_makePUWeights.cc" "PUWeightReader.cc" `root-config --cflags --glibs`; then
    echo -e "\nCOMPILATION SUCCESSFUL\n"
    ./a_makePUWeights.out
    rm a_makePUWeights.out
else
    echo -e "\nCOMPILATION FAILED\n"
fi
