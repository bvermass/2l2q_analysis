#!/bin/bash

./test/run_plots.sh test/sampleLists/plots_METResolution_mm.txt 3 a_plotsfull_mm.out
./test/run_plots.sh test/sampleLists/plots_METResolutionRun2018A_mm.txt 3 a_plotsA_mm.out
./test/run_plots.sh test/sampleLists/plots_METResolutionRun2018B_mm.txt 3 a_plotsB_mm.out
./test/run_plots.sh test/sampleLists/plots_METResolutionRun2018C_mm.txt 3 a_plotsC_mm.out
./test/run_plots.sh test/sampleLists/plots_METResolutionRun2018D_mm.txt 3 a_plotsD_mm.out
./test/run_plots.sh test/sampleLists/plots_METResolution_ee.txt 3 a_plotsfull_ee.out
./test/run_plots.sh test/sampleLists/plots_METResolutionRun2018A_ee.txt 3 a_plotsA_ee.out
./test/run_plots.sh test/sampleLists/plots_METResolutionRun2018B_ee.txt 3 a_plotsB_ee.out
./test/run_plots.sh test/sampleLists/plots_METResolutionRun2018C_ee.txt 3 a_plotsC_ee.out
./test/run_plots.sh test/sampleLists/plots_METResolutionRun2018D_ee.txt 3 a_plotsD_ee.out
./test/run_plots.sh test/sampleLists/multihists/plots_METResolutionRun2018ABCD_ee.txt 2 a_plotsmultihists_ee.out
./test/run_plots.sh test/sampleLists/multihists/plots_METResolutionRun2018ABCD_mm.txt 2 a_plotsmultihists_mm.out
