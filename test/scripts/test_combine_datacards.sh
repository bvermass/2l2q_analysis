#!/bin/bash

cd ../../helpertools/CombineTools
make -f makeCombineDataCardPrep
cd ../../
./test/run_plots.sh test/sampleLists/Combine/M-1_mu_1718_dirac.txt 6 M-1_mu_1718.out
./test/run_plots.sh test/sampleLists/Combine/M-1_2l_1718_dirac.txt 6 M-1_2l_1718.out
./test/run_plots.sh test/sampleLists/Combine/M-1_e_1718_dirac.txt 6 M-1_e_1718.out
