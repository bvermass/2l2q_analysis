#!/bin/bash

#This code does the entire run through from ntuples to histograms to plots.
# - for testrun of 3 samples and single plots from them, type 2 when prompted
# - for full run of all samples with all plots, type 1 when prompted
# - test/local_submit.sh is executed to get histograms with test/sampleLists/histos_all.txt as input samples
# - when all jobs are done, test/scripts/hadd_subfiles.sh is executed to merge histograms that belong together
# - test/script/submit_plots_all.sh is executed, making all plots and putting them in ~/public/2l2q_analysis/plots/
# - plots are copied to ~/public_html to be viewable through web browser at 

read -p "all(1), test(2): " choice

if [[ choice -eq 1 ]]; then
    ./test/local_submit.sh test/sampleLists/histos_all.txt
    ./test/scripts/wait_until_jobs_are_finished.sh
    ./test/scripts/hadd_subfiles.sh
    ./test/scripts/submit_plots_all.sh
    ./test/scripts/wait_until_jobs_are_finished.sh
    #cp -R ~/public/2l2q_analysis/plots/ ~/public_html/     # only uncomment if connection to tier2 is extremely slow, then access through web browser
elif [[ choice -eq 2 ]]; then
    ./test/run_analyzer.sh test/sampleLists/test.txt
    ./test/run_plots.sh test/sampleLists/plots_test.txt a_test_plot.out 1
fi
