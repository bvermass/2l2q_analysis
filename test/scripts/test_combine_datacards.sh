#!/bin/bash

cd ../../helpertools/CombineTools
make -f makeCombineDataCardPrep
cd ../../
./test/run_plots.sh test/sampleLists/Combine/M-1_mu_2016_majorana.txt 6 M-1_mu_2016.out
