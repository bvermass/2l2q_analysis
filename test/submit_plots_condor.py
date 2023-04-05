import os, sys
import time

current_directory = os.path.dirname( os.path.dirname( os.path.abspath( __file__ ) ) )
print current_directory

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

if len(sys.argv) != 3:
    print('Wrong number of arguments, input should be: python test/submit_plots_condor.py [sampleList] [plotstyle]')
    sys.exit()

#os.system('make -f test/make_mini_analyzer')

sampleList      = sys.argv[1]
plotstyle       = sys.argv[2]
print('plotstyle: {}'.format(plotstyle))

inputconditions  = [line.strip() for line in open(sampleList)]
inputconditions  = [inputcondition.split() for inputcondition in inputconditions if inputcondition and not inputcondition.startswith('#')] # Clean empty and comment lines

directory_name = inputconditions[0][0]
if plotstyle == '3':
    partition = inputconditions[0][1]

plotfilenames = inputconditions[1:][0]
legendnames = inputconditions[1:][1]

if plotstyle == '3':
    print('making stackplots')
    joblist = open('test/condor/StackPlotterJobList.txt', 'w')
    submitfilename = 'test/condor/StackPlotter.submit'

scriptname = 'combinedatacardscript.sh'
script = init_script(scriptname)

script.write('{} '.format(directory_name))
if plotstyle == '3':
    script.write('{} '.format(partition))

for plotfilename in plotfilenames:
    script.write('{} '.format(plotfilename))
for legendname in legendnames:
    script.write('{} '.format(legendname))

add_script_to_joblist(joblist, script, scriptname)

joblist.close()
submit_jobs(submitfilename)
