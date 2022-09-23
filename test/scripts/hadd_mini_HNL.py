import os, sys
import time

current_directory = os.path.dirname( os.path.abspath( __file__ ) )

def init_script( scriptname ):
    script = open(scriptname, 'w')
    script.write('#!/bin/bash\n')
    script.write('cd ' + current_directory + '\n')
    return script

def add_script_to_joblist( joblist, script, scriptname ):
    print 'submitting {}\n'.format( scriptname )
    script.close()
    joblist.write(scriptname + '\n')

def submit_jobs():
    print 'Submitting full joblist\n'
    os.system('condor_submit test/condor/Hadd.submit')

def merge_files( outputname, inputnames ):
    commandline = 'hadd -f {}'.format(outputname)
    for inputname in inputnames:
        commandline += ' {}'.format(inputname)
    commandline += '\n'
    return commandline

def add_subjob_hadd( path, script ):
    files = [path + s for s in os.listdir(path) if '.root' in s]
    if len(files) == 0:
        return 0
    else:
        output_file = files[0][:files[0].index('_job')] + '.root'
        script.write(merge_files(output_file, files ))
        script.write('mv {} {}/../../\n'.format(output_file, path))
        script.write('rm {}*.root\n'.format(path))
        return 1


def add_Signal_Run2( path, n_hadds, joblist, script_counter):
    hadd_counter = 0
    for filename in os.listdir(path):
        if ('HeavyNeutrino_lljj' in filename or 'SingleLepton' in filename) and 'MiniAOD2016' in filename:
        #if 'SingleLepton' in filename and 'MiniAOD2016' in filename:
            filename = os.path.join(path, filename)
            filename_1718 = filename.replace('MiniAOD2016', 'MiniAOD1718')
            filename_combined = filename.replace('MiniAOD2016', 'MiniAODRun2_SeparatePrediction')

            if hadd_counter == 0:
                scriptname = 'haddscript_signal_1718_{}.sh'.format( script_counter )
                print 'making next {}'.format( scriptname )
                script = init_script( scriptname )
                script_counter += 1

            hadd_counter += 1
            script.write('hadd -f {} {} {}\n'.format(filename_combined, filename, filename_1718))
            #print('hadd -f {} {} {}\n'.format(filename_combined, filename, filename_1718))

            if hadd_counter == n_hadds:
                add_script_to_joblist( joblist, script, scriptname )
                hadd_counter = 0


    #submit last job if we end on a number of subfiles smaller than n_hadds
    if hadd_counter != 0:
        add_script_to_joblist( joblist, script, scriptname )
        hadd_counter = 0

    return script_counter



#customizable parameters
n_hadds = 4


base_paths = []
base_paths.append('/user/bvermass/public/2l2q_analysis/histograms_highlPt/mini_analyzer/')
base_paths.append('/user/bvermass/public/2l2q_analysis/histograms_highlPt/mini_analyzer/JECUp/')
base_paths.append('/user/bvermass/public/2l2q_analysis/histograms_highlPt/mini_analyzer/JECDown/')
base_paths.append('/user/bvermass/public/2l2q_analysis/histograms_highlPt/mini_analyzer/JERUp/')
base_paths.append('/user/bvermass/public/2l2q_analysis/histograms_highlPt/mini_analyzer/JERDown/')

hadd_counter = 0

joblist = open('test/condor/HaddJobList.txt', 'w')
signal_Run2_counter = 0
for base_path in base_paths:
    signal_Run2_counter = add_Signal_Run2( base_path, n_hadds, joblist, signal_Run2_counter)

joblist.close()
os.system('chmod +x haddscript_*')
submit_jobs()
os.system( './test/scripts/wait_until_jobs_are_finished.sh' )
