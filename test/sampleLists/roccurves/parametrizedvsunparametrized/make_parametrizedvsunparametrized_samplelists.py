import os,sys

mass = ['1','2','3','4','5','6','8','10','12','14']
year = ['2016','2017','2018']
flavor = ['e','mu']
roc_paramvsunparam = open('../../../../paramvsunparam_roc.sh', 'w')

for m in mass:
    for y in year:
        for f in flavor:
            listname = f + '_M-' + m + '_' + y + '_parametrizedvsunparametrized.txt'
            samplelist = open(listname, 'w')
            samplelist.write('ROC_' + f + 'vsBkg_M-' + m + '_' + y + '_v8_parametrizedvsunparametrized\n')
            samplelist.write('par\n')
            samplelist.write('/user/bvermass/public/2l2q_analysis/histograms_POGTightID/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-' + m + '_V-combined_' + f + '_massiveAndCKM_LO_MiniAOD' + y + '.root\n')
            samplelist.write('/user/bvermass/public/2l2q_analysis/histograms_POGTightID/final/full_analyzer/hists_full_analyzer_Background_MiniAOD' + y + '.root\n')
            samplelist.write('unp\n')
            samplelist.write('/user/bvermass/public/2l2q_analysis/histograms_POGTightID_unparametrized/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-' + m + '_V-combined_' + f + '_massiveAndCKM_LO_MiniAOD' + y + '.root\n')
            samplelist.write('/user/bvermass/public/2l2q_analysis/histograms_POGTightID_unparametrized/final/full_analyzer/hists_full_analyzer_Background_MiniAOD' + y + '.root\n')
            samplelist.write('split\n')
            samplelist.write('/user/bvermass/public/2l2q_analysis/histograms_POGTightID_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_HeavyNeutrino_lljj_M-' + m + '_V-combined_' + f + '_massiveAndCKM_LO_MiniAOD' + y + '.root\n')
            samplelist.write('/user/bvermass/public/2l2q_analysis/histograms_POGTightID_unparametrized_LowAndHighMass/final/full_analyzer/hists_full_analyzer_Background_MiniAOD' + y + '.root\n')
            samplelist.close()
            
            roc_paramvsunparam.write('./test/submit_plots.sh test/sampleLists/roccurves/parametrizedvsunparametrized/' + listname + ' 4 roc_' + f + '_' + m + '_' + y + '.out\n')
roc_paramvsunparam.close()
