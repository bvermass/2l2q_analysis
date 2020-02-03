import os,sys
import time

base_directory = os.path.dirname( os.path.dirname( os.path.abspath( __file__ ) ) )

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

scriptname_base = sys.argv[1].replace('.out', '_')

partition = int(sys.argv[3])
line_base = './{} {}'.format(sys.argv[1], sys.argv[2])
for partitionjobnumber in range(partition):
    line = line_base + ' {} {}'.format(partitionjobnumber, partition)
    for i in range(len(sys.argv)):
        if i > 3:
            line = line + ' {}'.format(sys.argv[i])

    line = line + '\n'
    scriptname = scriptname_base + '{}.sh'.format(partitionjobnumber)
    script_part = init_script(scriptname)
    script_part.write(line)
    submit_script(script_part, scriptname)
