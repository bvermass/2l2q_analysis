import os,sys

current_directory = os.path.dirname( os.path.abspath( __file__ ) )

if len(sys.argv) != 2:
    print('Wrong number of arguments, input should be: python submit_HistogramMerger.py [sampleListdir]')
    sys.exit()

os.system('make -f makeHistogramMerger')
sampleListdir = os.path.abspath(sys.argv[1])
print 'working on {}'.format(sampleListdir)

for f in os.listdir(sampleListdir):
    if 'comb' in f:
        os.system('./test {}'.format(sampleListdir + '/' + f))

