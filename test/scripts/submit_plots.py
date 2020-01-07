import os, sys
import time

base_directory = os.path.dirname( os.path.dirname( os.path.dirname( os.path.abspath( __file__ ) ) ) )

def init_script( scriptname ):
    script = open(scriptname, 'w')
    script.write('#!/bin/bash\n')
    script.write('cd ' + base_directory + '\n')
    return script

def submit_script( script, scriptname ):
    print 'submitting {}'.format( scriptname )
    script.close()
    while os.system('qsub {} -l walltime=20:00:00'.format(scriptname)) != 0:
        print 'qsub error caught, resubmitting'
        time.sleep(2)
    os.system('rm {}'.format(scriptname))

if len(sys.argv) != 3:
    print('Wrong number of arguments, input should be: python test/scripts/submit_plots.sh [sampleList] [plot option]')
    sys.exit()

scriptname = sys.argv[1].replace('.txt', '.sh')
execname = sys.argv[1].replace('.txt', '.out')

script_bkg_mu = init_script(scriptname)
script_bkg_mu.write('./test/run_plots.sh {} {} {}'.format(sys.argv[1], execname, sys.argv[2]))
submit_script(script_bkg_mu, scriptname)
