import os,sys

import time

current_directory = os.path.dirname( os.path.dirname( os.path.abspath( __file__ ) ) )

def init_script( scriptname ):
    script = open(scriptname, 'w')
    script.write('#!/bin/bash\n')
    script.write('cd ' + current_directory + '\n')
    return script


def submit_script( script, scriptname ):
    print 'submitting {}'.format( scriptname )
    script.close()
    while os.system('qsub {} -l walltime=02:00:00'.format(scriptname)) != 0:
        print 'qsub error caught, resubmitting'
        time.sleep(2)

def add_script_to_joblist( joblist, script, scriptname ):
    print 'submitting {}\n'.format( scriptname )
    script.close()
    joblist.write(scriptname + '\n')

def submit_jobs():
    print 'Submitting full joblist\n'
    os.system('condor_submit test/condor/Combine.submit')

def run_combine_fromOwn_datacards(filesperJob):
    print('running combine with my own datacards')
    #datacardDir = '/user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/datacards/'
    datacardDir = '/user/bvermass/public_html/2l2q_analysis/combine_observed/datacards/'
    #datacardDir = '/user/bvermass/sandbox/combinetest/'

    joblist = open('test/condor/CombineJobList.txt', 'w')

    file_counter    = 0
    script_counter  = 0
    for root, dirs, files in os.walk(datacardDir):
        for f in files:
            if '_M-' in f and '_V2-' in f and '.txt' in f:
                f_abspath = os.path.abspath(os.path.join(root, f))
                print f_abspath
    
                combine_outputDir = root
                combine_outputDir.replace('datacards', 'combine_output')
                os.system('mkdir -p {}'.format(combine_outputDir))
                
    
                if file_counter < 0.1:
                    scriptname = 'combine_{}.sh'.format(script_counter)
                    script = init_script(scriptname)
                    script.write('cd /user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit\n')
                    script.write('eval `scram runtime -sh`\n')
                    script_counter += 1
    
    
                script.write('cd {}\n'.format(combine_outputDir))
                #script.write('combine --rMin 0.00001 --cminPreFit 2 -d {} -n {}\n'.format(f_abspath, f.split('.txt')[0]))
                script.write('combine -d {} -n {}\n'.format(f_abspath, f.split('.txt')[0]))
                #script.write('mv higgs*'
    
                file_counter += 1
    
                if abs(file_counter - filesperJob) < 0.1:
                    add_script_to_joblist(joblist, script, scriptname)
                    file_counter = 0
    
    if file_counter != 0:
        add_script_to_joblist(joblist, script, scriptname)
        file_counter = 0

    joblist.close()
    os.system('chmod +x combine_*')
    submit_jobs()

def run_combine_fromKirills_datacards(filesperJob):
    print('running combine with Kirills datacards')
    datacardDir = '/user/kskovpen/analysis/HNL/CMSSW_10_2_13/src/Limits/input/2L_cards/'
    file_counter    = 0
    script_counter  = 0
    
    for root, dirs, files in os.walk(datacardDir):
        for f in files:
            if '_M-' in f and '_V2-' in f and '.txt' in f:
                f_abspath = os.path.abspath(os.path.join(root, f))
                print f_abspath
    
                HNLpar_dirname = f.split("_cut")[0]
                combine_outputDir = '/user/bvermass/public_html/2l2q_analysis/combine_unparametrized_LowAndHighMass/combine_output_run2/' + HNLpar_dirname
                os.system('mkdir -p {}'.format(combine_outputDir))
                
    
                if file_counter < 0.1:
                    scriptname = 'combine_{}.sh'.format(script_counter)
                    script = init_script(scriptname)
                    script.write('cd /user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_8_1_0/src/HiggsAnalysis/CombinedLimit\n')
                    script.write('eval `scram runtime -sh`\n')
                    script_counter += 1
    
    
                script.write('cd {}\n'.format(combine_outputDir))
                script.write('combine -d {} -n {}\n'.format(f_abspath, f.split('.txt')[0]))
    
                file_counter += 1
    
                if abs(file_counter - filesperJob) < 0.1:
                    submit_script(script, scriptname)
                    file_counter = 0
    
    if file_counter != 0:
        submit_script(script, scriptname)
        file_counter = 0


if len(sys.argv) != 3:
    print 'command should be: python runCombine.py [filesperJob] [runOwnOrKirill]'
    sys.exit()

filesperJob = int(sys.argv[1])
runOwnOrKirill = int(sys.argv[2])

if runOwnOrKirill == 0:
    run_combine_fromOwn_datacards(filesperJob)
elif runOwnOrKirill == 1:
    run_combine_fromKirills_datacards(filesperJob)

