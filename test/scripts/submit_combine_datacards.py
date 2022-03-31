import os, sys
import time

current_directory = os.path.dirname( os.path.dirname( os.path.dirname( os.path.abspath( __file__ ) ) ) )

def init_script( scriptname ):
    script = open(scriptname, 'w')
    script.write('#!/bin/bash\n')
    script.write('cd ' + current_directory + '\n')
    script.write('./helpertools/CombineTools/datacardprep ')
    return script

def add_script_to_joblist( joblist, script, scriptname ):
    print 'adding {} to joblist\n'.format( scriptname )
    script.close()
    joblist.write(scriptname + '\n')

def submit_jobs(submitfilename):
    print 'Submitting full joblist\n'
    os.system('condor_submit {}'.format(submitfilename))

if len(sys.argv) == 1:
    startpoint = 0
else:
    startpoint = int(sys.argv[1])
    #if startpoint = 0, make 1718 datacards + make 2016 datacards + make run2 datacards
    #if startpoint = 1, make 2016 datacards + make run2 datacards (This assumes 1718 datacards have been made already)
    #if startpoint = 2, make run2 datacards (This assumes 1718 and 2016 datacards have been made already)

sampleListdirectory = 'test/sampleLists/Combine/'

if startpoint == 0:
    joblist = open('test/condor/CombineDatacardJobList.txt', 'w')
    submitfilename = 'test/condor/CombineDatacard.submit'
    
    job_counter = 0
    for sampleList in os.listdir(sampleListdirectory):
        if not '1718' in sampleList:
            continue
        
        inputconditions  = [line.strip() for line in open(sampleListdirectory+sampleList)]
        inputconditions  = [inputcondition.split() for inputcondition in inputconditions if inputcondition and not inputcondition.startswith('#')] # Clean empty and comment lines
        
        directory_name = inputconditions[0][0]
        
        plotfilenames = []
        legendnames = []
        for inputcondition in inputconditions[1:]:
            plotfilenames.append(inputcondition[0])
            legendnames.append(inputcondition[1])
        
        scriptname = 'combinedatacardscript_1718_{}.sh'.format(job_counter)
        script = init_script(scriptname)
        
        script.write('{} '.format(directory_name))
        
        for plotfilename in plotfilenames:
            script.write('{} '.format(plotfilename))
        for legendname in legendnames:
            script.write('{} '.format(legendname))
        
        add_script_to_joblist(joblist, script, scriptname)
        job_counter += 1
    
    joblist.close()
    os.system('chmod +x combinedatacardscript_*')
    submit_jobs(submitfilename)
    
    os.system('./test/scripts/wait_until_jobs_are_finished.sh')

if startpoint == 1 or startpoint == 0:
    joblist = open('test/condor/CombineDatacardJobList2016.txt', 'w')
    submitfilename = 'test/condor/CombineDatacard2016.submit'
    job_counter = 0
    for sampleList in os.listdir(sampleListdirectory):
        if not '2016' in sampleList:
            continue
        
        inputconditions  = [line.strip() for line in open(sampleListdirectory+sampleList)]
        inputconditions  = [inputcondition.split() for inputcondition in inputconditions if inputcondition and not inputcondition.startswith('#')] # Clean empty and comment lines
        
        directory_name = inputconditions[0][0]
        
        plotfilenames = []
        legendnames = []
        for inputcondition in inputconditions[1:]:
            plotfilenames.append(inputcondition[0])
            legendnames.append(inputcondition[1])
        
        scriptname = 'combinedatacardscript_2016_{}.sh'.format(job_counter)
        script = init_script(scriptname)
        
        script.write('{} '.format(directory_name))
        
        for plotfilename in plotfilenames:
            script.write('{} '.format(plotfilename))
        for legendname in legendnames:
            script.write('{} '.format(legendname))
        
        add_script_to_joblist(joblist, script, scriptname)
        job_counter += 1
    
    joblist.close()
    os.system('chmod +x combinedatacardscript_*')
    submit_jobs(submitfilename)
    
    os.system('./test/scripts/wait_until_jobs_are_finished.sh')

os.system('./helpertools/CombineTools/init_merge_datacards_for_run2.sh')

#cleanup
os.system('rm combinedatacardscript_*.sh')
