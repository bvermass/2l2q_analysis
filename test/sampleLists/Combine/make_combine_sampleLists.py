import os,sys

masses = ['1','2','3','4','5','6','8','10','12','14','15']
flavors = ['mu','e','2l']
years = ['2016', '2017', '2018']

run_all_filename = '../../scripts/run_combine_datacards_all.sh'
run_all_file = open(run_all_filename, 'w')
run_all_file.write('#!/bin/bash\n')

for mass in masses:
    for flavor in flavors:
        if mass == '15' and flavor == '2l':
            continue
        for year in years:
            txtfilename = 'M-' + mass + '_' + flavor + '_' + year + '_majorana.txt'
            txtfile = open(txtfilename, 'w')
            txtfile.write('M-' + mass + '_' + flavor + '_' + year + '_majorana\n')
            txtfile.write('/user/bvermass/public/2l2q_analysis/histograms_POGTightID/mini_analyzer/hists_mini_analyzer_HeavyNeutrino_lljj_M-' + mass + '_V-combined_' + flavor + '_massiveAndCKM_LO_MiniAOD' + year + '.root HNL_M-' + mass + '\n')
            txtfile.write('/user/bvermass/public/2l2q_analysis/histograms_POGTightID/mini_analyzer/hists_mini_analyzer_SingleLepton_Run' + year + '.root ABCD\n')
            txtfile.write('/user/bvermass/public/2l2q_analysis/histograms_POGTightID/mini_analyzer/hists_mini_analyzer_SingleLepton_Run' + year + '.root Obs\n')
            txtfile.close()

            run_all_file.write('./test/submit_plots.sh test/sampleLists/Combine/M-' + mass + '_' + flavor + '_' + year + '_majorana.txt 6 M-' + mass + '_' + flavor + '_' + year + '.out\n')
