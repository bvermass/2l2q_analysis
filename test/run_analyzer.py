import os, sys
import time

current_directory = os.path.dirname( os.path.dirname( os.path.abspath( __file__ ) ) )

if len(sys.argv) != 2:
    print('Wrong number of arguments, input should be: python test/submit_full_analyzer.py [sampleList]')
    sys.exit()

#os.system('make -f test/make_full_analyzer')

sampleList      = sys.argv[1]

inputconditions  = [line.strip() for line in open(sampleList)]
inputconditions  = [inputcondition.split() for inputcondition in inputconditions if inputcondition and not inputcondition.startswith('#')] # Clean empty and comment lines

for inputcondition in inputconditions:
    inputfilename = inputcondition[0]
    cross_section = inputcondition[1]
    max_entries   = inputcondition[2]
    partition     = inputcondition[3]

    for partitionjobnumber in range(int(partition)):
        os.system('./execFullAnalyzer {} {} {} {} {}'.format(inputfilename, cross_section, max_entries, partition, partitionjobnumber))
