#!/bin/bash

./test/run_plots.sh test/sampleLists/plots_all.txt a_singleplot.out 1
./test/run_plots.sh test/sampleLists/plots_bkg.txt a_stack.out 2 1 0
./test/run_plots.sh test/sampleLists/plots_HNL258e.txt a_multihist_e.out 3
./test/run_plots.sh test/sampleLists/plots_HNL258mu.txt a_multihist_mu.out 3
#tar -cf /user/bvermass/public/2l2q_analysis/plots.tar /user/bvermass/public/2l2q_analysis/plots/
#cp /user/bvermass/public/2l2q_analysis/plots.tar /user/bvermass/public_html/
#tar -xf /user/bvermass/public_html/plots.tar /user/bvermass/public_html/
