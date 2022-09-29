import os,sys

import time

current_directory = os.path.dirname( os.path.dirname( os.path.abspath( __file__ ) ) )

def init_script( scriptname ):
    script = open(scriptname, 'w')
    script.write('#!/bin/bash\n')
    script.write('cd ' + current_directory + '\n')
    return script


def add_script_to_joblist( script, scriptname, joblist ):
    script.close()
    joblist.write('{}\n'.format(scriptname))


if not (len(sys.argv) == 2 or len(sys.argv) == 3):
    print 'command should be: python runCombine.py [filesperJob] [diracormaj]'
    sys.exit()

datacardDir = '/user/bvermass/public_html/2l2q_analysis/combine_observed_NTight/datacards/'
filesperJob = int(sys.argv[1])
if len(sys.argv) == 3:
    diracormaj = sys.argv[2]
else:
    diracormaj = 'majorana'


file_counter    = 0
script_counter  = 0

joblist = open('test/condor/CombineJobList.txt', 'w')

for root, dirs, files in os.walk(datacardDir):
    for f in files:
        f_abspath = os.path.abspath(os.path.join(root, f))
        if '_M-' in f and '_V2-' in f and '.txt' in f and diracormaj in f_abspath:
            print f_abspath

            combine_outputDir = root
            combine_outputDir.replace('datacards', 'combine_output')
            os.system('mkdir -p {}'.format(combine_outputDir))
            

            if file_counter < 0.1:
                scriptname = 'combine_{}.sh'.format(script_counter)
                script = init_script(scriptname)
                script.write('cd /user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_8_1_0/src/HiggsAnalysis/CombinedLimit\n')
                script.write('eval `scram runtime -sh`\n')
                script_counter += 1


            script.write('cd {}\n'.format(combine_outputDir))
            script.write('combine -d {} -n {}\n'.format(f_abspath, f.split('.txt')[0]))
            #script.write('mv higgs*'

            file_counter += 1

            if abs(file_counter - filesperJob) < 0.1:
                add_script_to_joblist(script, scriptname, joblist)
                file_counter = 0

if file_counter != 0:
    add_script_to_joblist(script, scriptname, joblist)
    file_counter = 0

joblist.close()
os.system('chmod +x combine_*')
os.system('condor_submit test/condor/Combine.submit')
