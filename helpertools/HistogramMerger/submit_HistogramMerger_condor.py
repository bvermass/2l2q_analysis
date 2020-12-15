import os, sys
import time

current_directory = os.path.dirname( os.path.abspath( __file__ ) )

if len(sys.argv) != 2:
    print('Wrong number of arguments, input should be: python submit_HistogramMerger.py [sampleListdir]')
    sys.exit()


os.system('make -f makeHistogramMerger')
sampleListdir = os.path.abspath(sys.argv[1])
print 'working on {}'.format(sampleListdir)
joblist = open('condorJobList.txt', 'w')

for f in os.listdir(sampleListdir):
    if 'comb' in f:
        joblist.write('{}\n'.format(sampleListdir + '/' + f))

joblist.close()

os.system('condor_submit condor.submit')


#sampleList = sys.argv[1]
#scriptname = 'HistMerger.sh'
#script = init_script(scriptname)
#script.write('./test {}'.format(sampleList))
#submit_script(script, scriptname)
