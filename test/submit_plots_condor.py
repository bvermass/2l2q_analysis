import os, sys
import time

current_directory = os.path.dirname( os.path.dirname( os.path.abspath( __file__ ) ) )

if len(sys.argv) != 3:
    print('Wrong number of arguments, input should be: python test/submit_plots_condor.py [sampleList] [plotstyle]')
    sys.exit()

#os.system('make -f test/make_mini_analyzer')

sampleList      = sys.argv[1]
plotstyle       = sys.argv[2]

inputconditions  = [line.strip() for line in open(sampleList)]
inputconditions  = [inputcondition.split() for inputcondition in inputconditions if inputcondition and not inputcondition.startswith('#')] # Clean empty and comment lines

directory_name = inputconditions[0][0]
partition = inputconditions[0][1]

joblist = open('test/condor/StackPlotterJobList.txt', 'w')
for inputcondition in inputconditions[1:]:
    inputfilename = inputcondition[0]
    max_entries   = inputcondition[1]
    partition     = inputcondition[2] #currently unused

    joblist.write('{} {}\n'.format(inputfilename, max_entries))

joblist.close()

os.system('condor_submit test/condor/StackPlotter.submit')
