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

if len(sys.argv) != 1:
    print('Wrong number of arguments, input should be: python test/scripts/submit_plots.sh')
    sys.exit()

script_bkg_mu = init_script('plots_bkg_mu.sh')
script_bkg_mu.write('./test/run_plots_new.sh test/sampleLists/plots_bkg_mu.txt plots_bkg_mu.out 3')
submit_script(script_bkg_mu, 'plots_bkg_mu.sh')

#script_bkg_e = init_script('plots_bkg_e.sh')
#script_bkg_e.write('./test/run_plots_new.sh test/sampleLists/plots_bkg_e.txt plots_bkg_e.out 3')
#submit_script(script_bkg_e, 'plots_bkg_e.sh')
