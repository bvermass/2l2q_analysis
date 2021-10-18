import os, sys
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
    while os.system('qsub {} -l walltime=06:00:00'.format(scriptname)) != 0:
        print 'qsub error caught, resubmitting'
        time.sleep(2)


if len(sys.argv) != 3:
    print('Wrong number of arguments, input should be: python test/submit_mini_analyzer.py [sampleList] [filesperJob]')
    sys.exit()


#os.system('make -f test/make_mini_analyzer')

sampleList      = sys.argv[1]
filesperJob     = int(sys.argv[2])
file_counter     = 0
script_counter  = 0

inputconditions  = [line.strip() for line in open(sampleList)]
inputconditions  = [inputcondition.split() for inputcondition in inputconditions if inputcondition and not inputcondition.startswith('#')] # Clean empty and comment lines

for inputcondition in inputconditions:
    inputfilename = inputcondition[0]
    max_entries   = inputcondition[1]
    partition     = inputcondition[2]

    if file_counter == 0:
        scriptname = 'mini_{}.sh'.format(script_counter)
        script = init_script(scriptname)
        script_counter += 1

    script.write('./execMiniAnalyzer {} {} 1 0\n'.format(inputfilename, max_entries))
    file_counter += 1

    if file_counter == filesperJob:
        submit_script(script, scriptname)
        file_counter = 0

if file_counter != 0:
    submit_script(script, scriptname)
    file_counter = 0
