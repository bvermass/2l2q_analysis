import os, sys
import time

current_directory = os.path.dirname( os.path.abspath( __file__ ) )

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


if len(sys.argv) != 2:
    print('Wrong number of arguments, input should be: python submit_HistogramMerger.py [sampleListdir]')
    sys.exit()


os.system('make -f makeHistogramMerger')
sampleListdir = os.path.abspath(sys.argv[1])
print 'working on {}'.format(sampleListdir)
script_counter = 0
for f in os.listdir(sampleListdir):
    if 'comb' in f:
        scriptname = 'HNLHistmerging_{}.sh'.format(script_counter)
        script = init_script(scriptname)
        script.write('./test {}'.format(sampleListdir + '/' + f))
        submit_script(script, scriptname)
        script_counter += 1




#sampleList = sys.argv[1]
#scriptname = 'HistMerger.sh'
#script = init_script(scriptname)
#script.write('./test {}'.format(sampleList))
#submit_script(script, scriptname)
