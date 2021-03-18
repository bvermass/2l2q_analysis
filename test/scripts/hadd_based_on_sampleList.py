import os,sys
if(len(sys.argv) != 3):
    print('wrong number of arguments: python hadd_based_on_sampleList.py [sampleList] [outputfile]')
    sys.exit()

sampleList = sys.argv[1]
outputfile = sys.argv[2]

files = [line.strip() for line in open(sampleList)]
files = [line.split()[0] for line in files if line and not line.startswith('#')] # Clean empty and comment lines

commandline = 'hadd -f {}'.format(outputfile)
for f in files: 
    commandline += ' {}'.format(f)

os.system(commandline)
#commandline_M1 = 'hadd -f M-1.root'
#commandline_M2 = 'hadd -f M-2.root'
#commandline_M3 = 'hadd -f M-3.root'
#commandline_M4 = 'hadd -f M-4.root'
#commandline_M5 = 'hadd -f M-5.root'
#commandline_M6 = 'hadd -f M-6.root'
#commandline_M8 = 'hadd -f M-8.root'
#commandline_M10 = 'hadd -f M-10.root'
#for f in files:
#    if 'M-1_' in f:
#        commandline_M1 += ' {}'.format(f)
#    if 'M-2' in f:
#        commandline_M2 += ' {}'.format(f)
#    if 'M-3' in f:
#        commandline_M3 += ' {}'.format(f)
#    if 'M-4' in f:
#        commandline_M4 += ' {}'.format(f)
#    if 'M-5' in f:
#        commandline_M5 += ' {}'.format(f)
#    if 'M-6' in f:
#        commandline_M6 += ' {}'.format(f)
#    if 'M-8' in f:
#        commandline_M8 += ' {}'.format(f)
#    if 'M-10' in f:
#        commandline_M10 += ' {}'.format(f)
#
#os.system(commandline_M1)
#os.system(commandline_M2)
#os.system(commandline_M3)
#os.system(commandline_M4)
#os.system(commandline_M5)
#os.system(commandline_M6)
#os.system(commandline_M8)
#os.system(commandline_M10)
