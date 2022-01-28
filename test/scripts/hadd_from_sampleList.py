import os,sys,glob
sampleList = sys.argv[1]
outputfile = sys.argv[2]

files = [line.strip() for line in open(sampleList)]
files = [line.split()[0] for line in files if line and not line.startswith('#')] # Clean empty and comment lines

commandline = 'hadd -f {}'.format(outputfile)
for f in files:
    commandline += ' {}'.format(f)

os.system(commandline)
