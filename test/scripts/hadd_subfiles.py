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
    while os.system('qsub {} -l walltime=01:00:00'.format(scriptname)) != 0:
        print 'qsub error caught, resubmitting'
        time.sleep(2)
    print ''

def merge_files( outputname, inputnames ):
    commandline = 'hadd -f {}'.format(outputname)
    for inputname in inputnames:
        commandline += ' {}'.format(inputname)
    commandline += '\n'
    return commandline

def add_subjob_hadd( path, script ):
    files = [path + s for s in os.listdir(path) if '.root' in s]
    if len(files) == 0:
        return 0
    else:
        output_file = files[0][:files[0].index('_job')] + '.root'
        script.write(merge_files(output_file, files ))
        script.write('mv {} {}/../../\n'.format(output_file, path))
        script.write('rm {}*.root\n'.format(path))
        return 1


def merge_similar_samples( base_path ):
    basenames = []
    if 'histograms' in base_path:
        basenames.append(base_path + 'hists_full_analyzer_')
    elif 'HNLtagger_electron' in base_path:
        basenames.append(base_path + 'HNLtagger_electron_')
    elif 'HNLtagger_muon' in base_path:
        basenames.append(base_path + 'HNLtagger_muon_')
    elif 'BkgEstimator' in base_path:
        basenames.append(base_path + 'BkgEstimator_')

    all_good = True
    for basename in basenames:
        #MiniAOD2017
        Top_UL17_list  = [basename + 'TTToHadronic_TuneCP5_13TeV-powheg-pythia8_MiniAOD2017.root',
                          basename + 'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_MiniAOD2017.root',
                          basename + 'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_MiniAOD2017.root',
                          basename + 'ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-mcatnlo-pythia8_MiniAOD2017.root']
        if os.system(merge_files(basename + 'Top_UL17_MiniAOD2017.root', Top_UL17_list)) != 0:
            print 'Top UL17 failed'
            all_good = False

        Diboson_UL17_list  = [basename + 'WW_TuneCP5_13TeV-pythia8_MiniAOD2017.root',
                              basename + 'WZ_TuneCP5_13TeV-pythia8_MiniAOD2017.root',
                              basename + 'ZZ_TuneCP5_13TeV-pythia8_MiniAOD2017.root']
        if os.system(merge_files(basename + 'Diboson_UL17_MiniAOD2017.root', Diboson_UL17_list)) != 0:
            print 'Diboson UL17 failed'
            all_good = False

        UL17_list = [basename + 'DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_MiniAOD2017.root',
                     basename + 'Top_UL17_MiniAOD2017.root',
                     basename + 'Diboson_UL17_MiniAOD2017.root']
        if os.system(merge_files(basename + 'Background_UL17_MiniAOD2017.root', UL17_list)) != 0:
            print 'Background UL17 failed'
            all_good = False
        
        DoubleEG_UL17_list = [basename + 'DoubleEG_Run2017B.root',
                                basename + 'DoubleEG_Run2017C.root',
                                basename + 'DoubleEG_Run2017D.root',
                                basename + 'DoubleEG_Run2017E.root',
                                basename + 'DoubleEG_Run2017F.root']
        if os.system(merge_files(basename + 'DoubleEG_Run2017.root', DoubleEG_UL17_list)) != 0:
            print 'DoubleEG UL17 failed'
            all_good = False


        
        DoubleMuon_UL17_list = [basename + 'DoubleMuon_Run2017B.root',
                                basename + 'DoubleMuon_Run2017C.root',
                                basename + 'DoubleMuon_Run2017D.root',
                                basename + 'DoubleMuon_Run2017E.root',
                                basename + 'DoubleMuon_Run2017F.root']
        if os.system(merge_files(basename + 'DoubleMuon_Run2017.root', DoubleMuon_UL17_list)) != 0:
            print 'DoubleMuon UL17 failed'
            all_good = False

        #MiniAOD2018
        Top_UL18_list  = [basename + 'TTToHadronic_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                          basename + 'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                          basename + 'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                          basename + 'ST_t-channel_antitop_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                          basename + 'ST_t-channel_top_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                          basename + 'ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                          basename + 'ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                          basename + 'ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8_MiniAOD2018.root']
        if os.system(merge_files(basename + 'Top_UL18_MiniAOD2018.root', Top_UL18_list)) != 0:
            print 'Top UL18 failed'
            all_good = False

        Diboson_UL18_list  = [basename + 'WW_TuneCP5_13TeV-pythia8_MiniAOD2018.root',
                              basename + 'WZ_TuneCP5_13TeV-pythia8_MiniAOD2018.root',
                              basename + 'ZZ_TuneCP5_13TeV-pythia8_MiniAOD2018.root']
        if os.system(merge_files(basename + 'Diboson_UL18_MiniAOD2018.root', Diboson_UL18_list)) != 0:
            print 'Diboson UL18 failed'
            all_good = False

        UL18_list = [basename + 'DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_MiniAOD2018.root',
                     basename + 'Top_UL18_MiniAOD2018.root',
                     basename + 'Diboson_UL18_MiniAOD2018.root']
        if os.system(merge_files(basename + 'Background_UL18_MiniAOD2018.root', UL18_list)) != 0:
            print 'Background UL18 failed'
            all_good = False
        
        EGamma_UL18_list = [basename + 'EGamma_Run2018A.root',
                            basename + 'EGamma_Run2018B.root',
                            basename + 'EGamma_Run2018C.root',
                            basename + 'EGamma_Run2018D.root']
        if os.system(merge_files(basename + 'EGamma_Run2018.root', EGamma_UL18_list)) != 0:
            print 'EGamma UL18 failed'
            all_good = False


        
        DoubleMuon_UL18_list = [basename + 'DoubleMuon_Run2018A.root',
                                basename + 'DoubleMuon_Run2018B.root',
                                basename + 'DoubleMuon_Run2018C.root',
                                basename + 'DoubleMuon_Run2018D.root']
        if os.system(merge_files(basename + 'DoubleMuon_Run2018.root', DoubleMuon_UL18_list)) != 0:
            print 'DoubleMuon UL18 failed'
            all_good = False


    return all_good






#customizable parameters
tag_V5 = 'METResolution_JEC_UL17_V5'
tag_V2 = 'METResolution_JEC_UL18_V2'
tag_V4 = 'METResolution_JEC_UL18_V4'
#tag = 'METResolution_JEC_UL17_V1_ComplexL1'
n_hadds = 10


base_paths = []
base_paths.append('/user/bvermass/public/MET_scale_resolution/histograms/' + tag_V2 + '/full_analyzer/')
base_paths.append('/user/bvermass/public/MET_scale_resolution/histograms/' + tag_V4 + '/full_analyzer/')
base_paths.append('/user/bvermass/public/MET_scale_resolution/histograms/' + tag_V5 + '/full_analyzer/')
#base_paths.append('/user/bvermass/public/2l2q_analysis/trees/HNLtagger_electron/' + tag + '/full_analyzer/')
#base_paths.append('/user/bvermass/public/2l2q_analysis/trees/HNLtagger_muon/' + tag + '/full_analyzer/')
#base_paths.append('/user/bvermass/public/2l2q_analysis/trees/BkgEstimator/' + tag + '/full_analyzer/')

hadd_counter = 0

script_counter = 0
for base_path in base_paths:
    for subfiledir in os.listdir(base_path  + 'subfiles/'):
        print subfiledir
        input_subfile_path = base_path + 'subfiles/' + subfiledir + "/"
        if ((not os.path.isdir(input_subfile_path)) or len(os.listdir(input_subfile_path)) == 0):
            continue
    
        if hadd_counter == 0:
            scriptname = 'haddscript_{}.sh'.format( script_counter )
            print 'making next {}'.format( scriptname )
            script = init_script( scriptname )
            script_counter += 1
    
        hadd_counter += add_subjob_hadd(input_subfile_path, script)
        if hadd_counter == n_hadds:
            submit_script( script, scriptname )
            hadd_counter = 0
    
#submit last job if we end on a number of subfiles smaller than n_hadds
if hadd_counter != 0:
    submit_script( script, scriptname )
    hadd_counter = 0

os.system( './test/scripts/wait_until_jobs_are_finished.sh' )


for base_path in base_paths:
    if merge_similar_samples(base_path):
        print 'successfully merged: {}'.format(base_path)
    else:
        print 'failed merging: {}'.format(base_path)
