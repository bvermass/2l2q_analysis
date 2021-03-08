import os, sys
import time

current_directory = os.path.dirname( os.path.dirname( os.path.abspath( __file__ ) ) )

if len(sys.argv) != 3:
    print('Wrong number of arguments, input should be: python test/submit_mini_analyzer.py [sampleList] [filesperJob]')
    sys.exit()

#os.system('make -f test/make_mini_analyzer')

sampleList      = sys.argv[1]
filesperJob     = int(sys.argv[2]) #currently unused

inputconditions  = [line.strip() for line in open(sampleList)]
inputconditions  = [inputcondition.split() for inputcondition in inputconditions if inputcondition and not inputcondition.startswith('#')] # Clean empty and comment lines

joblist = open('test/condor/MiniAnalyzerJobList.txt', 'w')
for inputcondition in inputconditions:
    inputfilename = inputcondition[0]
    max_entries   = inputcondition[1]
    partition     = inputcondition[2] #currently unused

    joblist.write('{} {}\n'.format(inputfilename, max_entries))

joblist.close()

os.system('condor_submit test/condor/MiniAnalyzer.submit')
