import os,sys

datacardDir = '/user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/'
print('merging datacards in {}'.format(datacardDir))

for root, dirs, files in os.walk(datacardDir):
    for f in files:
        f_2016 = os.path.abspath(os.path.join(root,f))
        #print f_abspath
        if '_M-' in f and '_V2-' in f and '.txt' in f and '2016' in f_2016:
            #f_2017 = f_2016.replace('2016', '2017')
            #f_2018 = f_2016.replace('2016', '2018')
            f_1718 = f_2016.replace('2016', '1718')
            f_run2 = f_2016.replace('2016', 'run2')
            os.system('mkdir -p {}'.format(os.path.dirname(f_run2)))
            print f_run2
        
            #os.system('python /user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_8_1_0/src/HiggsAnalysis/CombinedLimit/scripts/combineCards.py Name1={} Name2={} Name3={} > {}'.format(f_2016, f_2017, f_2018, f_run2))
            os.system('python /user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_8_1_0/src/HiggsAnalysis/CombinedLimit/scripts/combineCards.py Name1={} Name2={} > {}'.format(f_2016, f_1718, f_run2))
