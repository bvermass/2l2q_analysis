import os,sys,glob

current_directory = os.path.dirname( os.path.abspath( __file__ ) )

if len(sys.argv) != 2:
    print('Wrong number of arguments, input should be: python merge_run2.py [basedir]')
    print('This script merges combined HNL files of the same mass for all 3 years')
    sys.exit()

basedir = os.path.abspath(sys.argv[1])
print basedir
for f_2016 in glob.glob(basedir + '/*'):
    if '2016' in f_2016:# and 'lljj' in f_2016:
        #f_2017 = f_2016.replace('MiniAOD2016', 'MiniAOD2017').replace('Run2016','Run2017') 
        #f_2018 = f_2016.replace('MiniAOD2016', 'MiniAOD2018').replace('Run2016','Run2018')
        f_1718 = f_2016.replace('MiniAOD2016', 'MiniAOD1718').replace('Run2016','Run1718')
        f_run2 = f_2016.replace('MiniAOD2016', 'MiniAODRun2_SeparatePrediction').replace('Run2016','Run2_SeparatePrediction')
        #f_run2 = f_2016.replace('MiniAOD2016', 'MiniAODRun2')#.replace('Run2016','Run2_SeparatePrediction')

        #if os.path.isfile(f_2017) and os.path.isfile(f_2018):
        #    os.system('hadd -f {} {} {} {}'.format(f_run2, f_2016, f_2017, f_2018))
        if os.path.isfile(f_1718):
            os.system('hadd -f {} {} {}'.format(f_run2, f_2016, f_1718))
