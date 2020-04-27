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
        #MiniAOD2016
        TTJets_2016_list = [basename + 'TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MiniAOD2016.root',
                       basename + 'TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MiniAOD2016.root',
                       basename + 'TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MiniAOD2016.root']
        if os.system(merge_files(basename + 'TTJets_MiniAOD2016.root', TTJets_2016_list)) != 0:
            print 'TTJets 2016 failed'
            all_good = False
        
        DYJets_2016_list = [basename + 'DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MiniAOD2016.root',
                       basename + 'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MiniAOD2016.root']
        #DYJets_2016_list = [basename + 'DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_MiniAOD2016.root',
        #               basename + 'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_MiniAOD2016.root']
        if os.system(merge_files(basename + 'DYJets_MiniAOD2016.root', DYJets_2016_list)) != 0:
            all_good = False

        Diboson_2016_list = [basename + 'WWTo2L2Nu_13TeV-powheg_MiniAOD2016.root',
                        basename + 'WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_MiniAOD2016.root',
                        basename + 'ZZTo4L_13TeV_powheg_pythia8_ext1_MiniAOD2016.root',
                        basename + 'ZZTo2L2Q_13TeV_powheg_pythia8_MiniAOD2016.root',
                        basename + 'ZZTo2L2Nu_13TeV_powheg_pythia8_MiniAOD2016.root',
                        basename + 'WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_MiniAOD2016.root',
                        basename + 'WZToLNu2Q_13TeV_powheg_pythia8_MiniAOD2016.root',
                        basename + 'WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_MiniAOD2016.root']
        if os.system(merge_files(basename + 'Diboson_MiniAOD2016.root', Diboson_2016_list)) != 0:
            all_good = False

        ST_2016_list = [basename + 'ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_MiniAOD2016.root',
                   basename + 'ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_MiniAOD2016.root',
                   basename + 'ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_MiniAOD2016.root',
                   basename + 'ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_MiniAOD2016.root',
                   basename + 'ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_MiniAOD2016.root']
        if os.system(merge_files(basename + 'ST_MiniAOD2016.root', ST_2016_list)) != 0:
            all_good = False
        
        Top_2016_list = [basename + 'TTJets_MiniAOD2016.root',
                         basename + 'ST_MiniAOD2016.root']
        if os.system(merge_files(basename + 'Top_MiniAOD2016.root', Top_2016_list)) != 0:
            all_good = False
        
        Bkg_2016_list = [basename + 'DYJets_MiniAOD2016.root',
                    basename + 'Diboson_MiniAOD2016.root',
                    basename + 'TTJets_MiniAOD2016.root',
                    basename + 'ST_MiniAOD2016.root',
                    basename + 'WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_MiniAOD2016.root']
        if os.system(merge_files(basename + 'Background_MiniAOD2016.root', Bkg_2016_list)) != 0:
            all_good = False


        #Run2016
        Muon_Run2016_list = [basename + 'SingleMuon_Run2016B.root',
                        basename + 'SingleMuon_Run2016C.root',
                        basename + 'SingleMuon_Run2016D.root',
                        basename + 'SingleMuon_Run2016E.root',
                        basename + 'SingleMuon_Run2016F.root',
                        basename + 'SingleMuon_Run2016G.root',
                        basename + 'SingleMuon_Run2016H.root']
        if os.system(merge_files(basename + 'SingleMuon_Run2016.root', Muon_Run2016_list)) != 0:
            all_good = False

        Electron_Run2016_list = [basename + 'SingleElectron_Run2016B.root',
                        basename + 'SingleElectron_Run2016C.root',
                        basename + 'SingleElectron_Run2016D.root',
                        basename + 'SingleElectron_Run2016E.root',
                        basename + 'SingleElectron_Run2016F.root',
                        basename + 'SingleElectron_Run2016G.root',
                        basename + 'SingleElectron_Run2016H.root']
        if os.system(merge_files(basename + 'SingleElectron_Run2016.root', Electron_Run2016_list)) != 0:
            all_good = False

        #MiniAOD2017
        WJets_2017_list = [basename + 'WJetsToLNu_0J_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2017.root',
                       basename + 'WJetsToLNu_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2017.root',
                       basename + 'WJetsToLNu_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2017.root']
        if os.system(merge_files(basename + 'WJets_012J_MiniAOD2017.root', WJets_2017_list)) != 0:
            print 'WJets 012J 2017 failed'
            all_good = False
        
        DYJets_2017_list = [basename + 'DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8_MiniAOD2017.root',
                       #basename + 'DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2017.root']
                       basename + 'DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_MiniAOD2017.root']
        if os.system(merge_files(basename + 'DYJets_MiniAOD2017.root', DYJets_2017_list)) != 0:
            print 'DY 2017 failed'
            all_good = False

        TTJets_2017_list = [basename + 'TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_MiniAOD2017.root',
                       basename + 'TTToHadronic_TuneCP5_13TeV-powheg-pythia8_MiniAOD2017.root',
                       basename + 'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_MiniAOD2017.root']
        if os.system(merge_files(basename + 'TTJets_MiniAOD2017.root', TTJets_2017_list)) != 0:
            print 'TTJets 2017 failed'
            all_good = False
        
        ST_2017_list = [basename + 'ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8_MiniAOD2017.root',
                   basename + 'ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_MiniAOD2017.root',
                   basename + 'ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_MiniAOD2017.root',
                   basename + 'ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_MiniAOD2017.root',
                   basename + 'ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_MiniAOD2017.root']
        if os.system(merge_files(basename + 'ST_MiniAOD2017.root', ST_2017_list)) != 0:
            all_good = False

        Top_2017_list = [basename + 'TTJets_MiniAOD2017.root',
                         basename + 'ST_MiniAOD2017.root']
        if os.system(merge_files(basename + 'Top_MiniAOD2017.root', Top_2017_list)) != 0:
            all_good = False
        
        Diboson_2017_list = [basename + 'WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_MiniAOD2017.root',
                        basename + 'WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_MiniAOD2017.root',
                        basename + 'WW_DoubleScattering_13TeV-pythia8_TuneCP5_MiniAOD2017.root',
                        basename + 'WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_MiniAOD2017.root',
                        basename + 'WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2_MiniAOD2017.root',
                        basename + 'WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_MiniAOD2017.root',
                        basename + 'WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2017.root',
                        basename + 'ZZTo2L2Nu_13TeV_powheg_pythia8_MiniAOD2017.root',
                        basename + 'ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_MiniAOD2017.root',
                        basename + 'ZZTo2Q2Nu_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8_MiniAOD2017.root',
                        basename + 'ZZTo4L_13TeV_powheg_pythia8_MiniAOD2017.root']
        if os.system(merge_files(basename + 'Diboson_MiniAOD2017.root', Diboson_2017_list)) != 0:
            all_good = False

        
        Bkg_2017_list = [basename + 'DYJets_MiniAOD2017.root',
                    basename + 'Diboson_MiniAOD2017.root',
                    basename + 'TTJets_MiniAOD2017.root',
                    basename + 'ST_MiniAOD2017.root',
                    basename + 'WJets_012J_MiniAOD2017.root']
        if os.system(merge_files(basename + 'Background_MiniAOD2017.root', Bkg_2017_list)) != 0:
            all_good = False


        #Run2017
        Muon_Run2017_list = [basename + 'SingleMuon_Run2017B.root',
                        basename + 'SingleMuon_Run2017C.root',
                        basename + 'SingleMuon_Run2017D.root',
                        basename + 'SingleMuon_Run2017E.root',
                        basename + 'SingleMuon_Run2017F.root']
        if os.system(merge_files(basename + 'SingleMuon_Run2017.root', Muon_Run2017_list)) != 0:
            all_good = False

        Electron_Run2017_list = [basename + 'SingleElectron_Run2017B.root',
                        basename + 'SingleElectron_Run2017C.root',
                        basename + 'SingleElectron_Run2017D.root',
                        basename + 'SingleElectron_Run2017E.root',
                        basename + 'SingleElectron_Run2017F.root']
        if os.system(merge_files(basename + 'SingleElectron_Run2017.root', Electron_Run2017_list)) != 0:
            all_good = False

    return all_good






#customizable parameters
tag = 'final'
n_hadds = 10


base_paths = []
base_paths.append('/user/bvermass/public/2l2q_analysis/histograms/' + tag + '/full_analyzer/')
base_paths.append('/user/bvermass/public/2l2q_analysis/trees/HNLtagger_electron/' + tag + '/full_analyzer/')
base_paths.append('/user/bvermass/public/2l2q_analysis/trees/HNLtagger_muon/' + tag + '/full_analyzer/')
base_paths.append('/user/bvermass/public/2l2q_analysis/trees/BkgEstimator/' + tag + '/full_analyzer/')

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
