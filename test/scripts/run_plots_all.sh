#!/bin/bash

./test/run_plots.sh test/sampleLists/plots_all.txt 1
./test/run_plots.sh test/sampleLists/plots_bkg.txt 2
./test/run_plots.sh test/sampleLists/plots_HNL258e.txt 3
./test/run_plots.sh test/sampleLists/plots_HNL258mu.txt 3
tar -cf /user/bvermass/public/2l2q_analysis/plots.tar /user/bvermass/public/2l2q_analysis/plots/
cp /user/bvermass/public/2l2q_analysis/plots.tar /user/bvermass/public_html/
tar -xf /user/bvermass/public_html/plots.tar /user/bvermass/public_html/
