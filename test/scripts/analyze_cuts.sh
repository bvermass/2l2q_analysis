#!/bin/bash

./test/run_plots.sh test/sampleLists/ivfcheck/ivfcheck_analyzecuts_mu_nochange.txt a_analyze_cuts.out 4
./test/run_plots.sh test/sampleLists/ivfcheck/ivfcheck_analyzecuts_mu_cMDAndDistcutAndFrac.txt a_analyze_cuts.out 4
./test/run_plots.sh test/sampleLists/ivfcheck/ivfcheck_analyzecuts_e_nochange.txt a_analyze_cuts.out 4
./test/run_plots.sh test/sampleLists/ivfcheck/ivfcheck_analyzecuts_e_cMDAndDistcutAndFrac.txt a_analyze_cuts.out 4
