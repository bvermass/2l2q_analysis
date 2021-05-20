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

# Add HeavyNeutrino 'Dirac' and their charge conjugate 'Dirac_cc' files together. in the original 'Dirac' production, 'Dirac_cc' was missing. 
# Dirac and Dirac_cc HNL samples don't have the same cross_section (due to different cross section of W+ and W- production) so they should be hadded after full_analyzer is run
def add_Dirac_cc( path, n_hadds):
    hadd_counter = 0
    script_counter = 0
    for filename in os.listdir(path):
        if 'HeavyNeutrino_lljj' in filename and 'Dirac_cc' in filename:
            filename = os.path.join(path, filename)
            filename_dirac = filename.replace('Dirac_cc', 'Dirac')
            filename_combined = filename.replace('Dirac_cc', 'Dirac_combined')

            if hadd_counter == 0:
                scriptname = 'haddscript_dirac_cc_{}.sh'.format( script_counter )
                print 'making next {}'.format( scriptname )
                script = init_script( scriptname )
                script_counter += 1

            hadd_counter += 1
            script.write('hadd -f {} {} {}\n'.format(filename_combined, filename, filename_dirac))
            script.write('rm {} {}\n'.format(filename, filename_dirac))

            if hadd_counter == n_hadds:
                submit_script( script, scriptname )
                hadd_counter = 0


    #submit last job if we end on a number of subfiles smaller than n_hadds
    if hadd_counter != 0:
        submit_script( script, scriptname )
        hadd_counter = 0








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

    # all_good is a boolean that will keep track if any hadd operation fails
    all_good = True

    for basename in basenames:


        #MiniAOD2016
        VG_2016_list = [basename + 'WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_MiniAOD2016.root',
                       basename + 'ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_MiniAOD2016.root']
        if os.system(merge_files(basename + 'VG_MiniAOD2016.root', VG_2016_list)) != 0:
            print 'VG 2016 failed'
            all_good = False

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
                        basename + 'ZZTo2L2Nu_13TeV_powheg_pythia8_ext1_MiniAOD2016.root',
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

        QCD_MuEnriched_2016_list = [basename + 'QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root']
        if os.system(merge_files(basename + 'QCD_MuEnriched_MiniAOD2016.root', QCD_MuEnriched_2016_list)) != 0:
            all_good = False

        QCD_EMEnriched_2016_list = [basename + 'QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                                    basename + 'QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root']
        if os.system(merge_files(basename + 'QCD_EMEnriched_MiniAOD2016.root', QCD_EMEnriched_2016_list)) != 0:
            all_good = False

        QCD_bcToE_2016_list = [basename + 'QCD_Pt_15to20_bcToE_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                               basename + 'QCD_Pt_20to30_bcToE_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                               basename + 'QCD_Pt_30to80_bcToE_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                               basename + 'QCD_Pt_80to170_bcToE_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                               basename + 'QCD_Pt_170to250_bcToE_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root',
                               basename + 'QCD_Pt_250toInf_bcToE_TuneCUETP8M1_13TeV_pythia8_MiniAOD2016.root']
        if os.system(merge_files(basename + 'QCD_bcToE_MiniAOD2016.root', QCD_bcToE_2016_list)) != 0:
            all_good = False

        Bkg_2016_list = [basename + 'DYJets_MiniAOD2016.root',
                    basename + 'VG_MiniAOD2016.root',
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

        Lepton_Run2016_list = [basename + 'SingleElectron_Run2016.root',
                        basename + 'SingleMuon_Run2016.root']
        if os.system(merge_files(basename + 'SingleLepton_Run2016.root', Lepton_Run2016_list)) != 0:
            all_good = False

        #MiniAOD2017
        VG_2017_list = [basename + 'ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2017.root',
                       basename + 'WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2017.root']
        if os.system(merge_files(basename + 'VG_MiniAOD2017.root', VG_2017_list)) != 0:
            print 'VG 2017 failed'
            all_good = False

        WJets_012J_2017_list = [basename + 'WJetsToLNu_0J_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2017.root',
                       basename + 'WJetsToLNu_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2017.root',
                       basename + 'WJetsToLNu_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2017.root']
        if os.system(merge_files(basename + 'WJets_012J_MiniAOD2017.root', WJets_012J_2017_list)) != 0:
            print 'WJets 012J 2017 failed'
            all_good = False

        DYJets_2017_list = [basename + 'DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8_MiniAOD2017.root',
                       basename + 'DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2017.root']
                       #basename + 'DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_MiniAOD2017.root']
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

        QCD_MuEnriched_2017_list = [basename + 'QCD_Pt-15to20_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2017.root']
        if os.system(merge_files(basename + 'QCD_MuEnriched_MiniAOD2017.root', QCD_MuEnriched_2017_list)) != 0:
            all_good = False

        QCD_EMEnriched_2017_list = [basename + 'QCD_Pt-15to20_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-20to30_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-30to50_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-50to80_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-80to120_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-120to170_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    #basename + 'QCD_Pt-170to300_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                                    basename + 'QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2017.root']
        if os.system(merge_files(basename + 'QCD_EMEnriched_MiniAOD2017.root', QCD_EMEnriched_2017_list)) != 0:
            all_good = False

        QCD_bcToE_2017_list = [#basename + 'QCD_Pt_15to20_bcToE_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                               basename + 'QCD_Pt_20to30_bcToE_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                               basename + 'QCD_Pt_30to80_bcToE_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                               basename + 'QCD_Pt_80to170_bcToE_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                               basename + 'QCD_Pt_170to250_bcToE_TuneCP5_13TeV_pythia8_MiniAOD2017.root',
                               basename + 'QCD_Pt_250toInf_bcToE_TuneCP5_13TeV_pythia8_MiniAOD2017.root']
        if os.system(merge_files(basename + 'QCD_bcToE_MiniAOD2017.root', QCD_bcToE_2017_list)) != 0:
            all_good = False


        Bkg_2017_list = [basename + 'DYJets_MiniAOD2017.root',
                    basename + 'VG_MiniAOD2017.root',
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

        Lepton_Run2017_list = [basename + 'SingleElectron_Run2017.root',
                        basename + 'SingleMuon_Run2017.root']
        if os.system(merge_files(basename + 'SingleLepton_Run2017.root', Lepton_Run2017_list)) != 0:
            all_good = False


        #MiniAOD2018
        VG_2018_list = [basename + 'ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2018.root',
                       basename + 'WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2018.root']
        if os.system(merge_files(basename + 'VG_MiniAOD2018.root', VG_2018_list)) != 0:
            print 'VG 2018 failed'
            all_good = False

        WJets_012J_2018_list = [basename + 'WJetsToLNu_0J_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2018.root',
                       basename + 'WJetsToLNu_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2018.root',
                       basename + 'WJetsToLNu_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2018.root']
        if os.system(merge_files(basename + 'WJets_012J_MiniAOD2018.root', WJets_012J_2018_list)) != 0:
            print 'WJets 012J 2018 failed'
            all_good = False

        DYJets_2018_list = [basename + 'DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8_MiniAOD2018.root',
                       #basename + 'DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_MiniAOD2018.root']
                       basename + 'DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_MiniAOD2018.root']
        if os.system(merge_files(basename + 'DYJets_MiniAOD2018.root', DYJets_2018_list)) != 0:
            print 'DY 2018 failed'
            all_good = False

        TTJets_2018_list = [basename + 'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                       #basename + 'TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_MiniAOD2018.root',
                       basename + 'TTToHadronic_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                       basename + 'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root']
        if os.system(merge_files(basename + 'TTJets_MiniAOD2018.root', TTJets_2018_list)) != 0:
            print 'TTJets 2018 failed'
            all_good = False

        ST_2018_list = [basename + 'ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-madgraph-pythia8_MiniAOD2018.root',
                   basename + 'ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8_MiniAOD2018.root',
                   basename + 'ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8_MiniAOD2018.root',
                   #basename + 'ST_t-channel_top_5f_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                   #basename + 'ST_t-channel_antitop_5f_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                   basename + 'ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                   basename + 'ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root']
        if os.system(merge_files(basename + 'ST_MiniAOD2018.root', ST_2018_list)) != 0:
            all_good = False

        Top_2018_list = [basename + 'TTJets_MiniAOD2018.root',
                         basename + 'ST_MiniAOD2018.root']
        if os.system(merge_files(basename + 'Top_MiniAOD2018.root', Top_2018_list)) != 0:
            all_good = False

        Diboson_2018_list = [basename + 'WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                        basename + 'WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                        basename + 'WWTo2L2Nu_DoubleScattering_13TeV-pythia8_MiniAOD2018.root',
                        basename + 'WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_MiniAOD2018.root',
                        basename + 'WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_MiniAOD2018.root',
                        basename + 'WZTo3LNu_TuneCP5_13TeV-powheg-pythia8_MiniAOD2018.root',
                        basename + 'ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8_MiniAOD2018.root',
                        basename + 'ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_MiniAOD2018.root',
                        basename + 'ZZTo2Q2Nu_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8_MiniAOD2018.root',
                        basename + 'ZZTo4L_TuneCP5_13TeV_powheg_pythia8_MiniAOD2018.root']
        if os.system(merge_files(basename + 'Diboson_MiniAOD2018.root', Diboson_2018_list)) != 0:
            all_good = False

        QCD_MuEnriched_2018_list = [basename + 'QCD_Pt-15to20_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8_MiniAOD2018.root']
        if os.system(merge_files(basename + 'QCD_MuEnriched_MiniAOD2018.root', QCD_MuEnriched_2018_list)) != 0:
            all_good = False

        QCD_EMEnriched_2018_list = [basename + 'QCD_Pt-15to20_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-20to30_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-30to50_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-50to80_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-80to120_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-120to170_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-170to300_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                                    basename + 'QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8_MiniAOD2018.root']
        if os.system(merge_files(basename + 'QCD_EMEnriched_MiniAOD2018.root', QCD_EMEnriched_2018_list)) != 0:
            all_good = False

        QCD_bcToE_2018_list = [basename + 'QCD_Pt_15to20_bcToE_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                               basename + 'QCD_Pt_20to30_bcToE_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                               basename + 'QCD_Pt_30to80_bcToE_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                               basename + 'QCD_Pt_80to170_bcToE_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                               basename + 'QCD_Pt_170to250_bcToE_TuneCP5_13TeV_pythia8_MiniAOD2018.root',
                               basename + 'QCD_Pt_250toInf_bcToE_TuneCP5_13TeV_pythia8_MiniAOD2018.root']
        if os.system(merge_files(basename + 'QCD_bcToE_MiniAOD2018.root', QCD_bcToE_2018_list)) != 0:
            all_good = False


        Bkg_2018_list = [basename + 'DYJets_MiniAOD2018.root',
                    basename + 'VG_MiniAOD2018.root',
                    basename + 'Diboson_MiniAOD2018.root',
                    basename + 'TTJets_MiniAOD2018.root',
                    basename + 'ST_MiniAOD2018.root',
                    basename + 'WJets_012J_MiniAOD2018.root']
        if os.system(merge_files(basename + 'Background_MiniAOD2018.root', Bkg_2018_list)) != 0:
            all_good = False


        #Run2018
        Muon_Run2018_list = [basename + 'SingleMuon_Run2018A.root',
                        basename + 'SingleMuon_Run2018B.root',
                        basename + 'SingleMuon_Run2018C.root',
                        basename + 'SingleMuon_Run2018D.root']
        if os.system(merge_files(basename + 'SingleMuon_Run2018.root', Muon_Run2018_list)) != 0:
            all_good = False

        Electron_Run2018_list = [basename + 'EGamma_Run2018A.root',
                        basename + 'EGamma_Run2018B.root',
                        basename + 'EGamma_Run2018C.root',
                        basename + 'EGamma_Run2018D.root']
        if os.system(merge_files(basename + 'EGamma_Run2018.root', Electron_Run2018_list)) != 0:
            all_good = False

        Lepton_Run2018_list = [basename + 'EGamma_Run2018.root',
                        basename + 'SingleMuon_Run2018.root']
        if os.system(merge_files(basename + 'SingleLepton_Run2018.root', Lepton_Run2018_list)) != 0:
            all_good = False

        Lepton_Run2_list = [basename + 'SingleLepton_Run2016.root',
                        basename + 'SingleLepton_Run2017.root',
                        basename + 'SingleLepton_Run2018.root']
        if os.system(merge_files(basename + 'SingleLepton_Run2.root', Lepton_Run2_list)) != 0:
            all_good = False
        Top_Run2_list = [basename + 'Top_MiniAOD2016.root',
                        basename + 'Top_MiniAOD2017.root',
                        basename + 'Top_MiniAOD2018.root']
        if os.system(merge_files(basename + 'Top_MiniAODRun2.root', Top_Run2_list)) != 0:
            all_good = False
        Background_Run2_list = [basename + 'Background_MiniAOD2016.root',
                        basename + 'Background_MiniAOD2017.root',
                        basename + 'Background_MiniAOD2018.root']
        if os.system(merge_files(basename + 'Background_MiniAODRun2.root', Background_Run2_list)) != 0:
            all_good = False

        #2017+2018
        Lepton_Run1718_list = [basename + 'SingleLepton_Run2017.root',
                        basename + 'SingleLepton_Run2018.root']
        if os.system(merge_files(basename + 'SingleLepton_Run1718.root', Lepton_Run1718_list)) != 0:
            all_good = False
        Electron_Run1718_list = [basename + 'SingleElectron_Run2017.root',
                        basename + 'EGamma_Run2018.root']
        if os.system(merge_files(basename + 'SingleElectron_Run1718.root', Electron_Run1718_list)) != 0:
            all_good = False
        Muon_Run1718_list = [basename + 'SingleMuon_Run2017.root',
                        basename + 'SingleMuon_Run2018.root']
        if os.system(merge_files(basename + 'SingleMuon_Run1718.root', Muon_Run1718_list)) != 0:
            all_good = False
        Top_Run1718_list = [basename + 'Top_MiniAOD2017.root',
                        basename + 'Top_MiniAOD2018.root']
        if os.system(merge_files(basename + 'Top_MiniAOD1718.root', Top_Run1718_list)) != 0:
            all_good = False
        DYJets_Run1718_list = [basename + 'DYJets_MiniAOD2017.root',
                        basename + 'DYJets_MiniAOD2018.root']
        if os.system(merge_files(basename + 'DYJets_MiniAOD1718.root', DYJets_Run1718_list)) != 0:
            all_good = False
        VG_Run1718_list = [basename + 'VG_MiniAOD2017.root',
                        basename + 'VG_MiniAOD2018.root']
        if os.system(merge_files(basename + 'VG_MiniAOD1718.root', VG_Run1718_list)) != 0:
            all_good = False
        WJets_012J_Run1718_list = [basename + 'WJets_012J_MiniAOD2017.root',
                        basename + 'WJets_012J_MiniAOD2018.root']
        if os.system(merge_files(basename + 'WJets_012J_MiniAOD1718.root', WJets_012J_Run1718_list)) != 0:
            all_good = False
        Diboson_Run1718_list = [basename + 'Diboson_MiniAOD2017.root',
                        basename + 'Diboson_MiniAOD2018.root']
        if os.system(merge_files(basename + 'Diboson_MiniAOD1718.root', Diboson_Run1718_list)) != 0:
            all_good = False
        QCD_MuEnriched_Run1718_list = [basename + 'QCD_MuEnriched_MiniAOD2017.root',
                        basename + 'QCD_MuEnriched_MiniAOD2018.root']
        if os.system(merge_files(basename + 'QCD_MuEnriched_MiniAOD1718.root', QCD_MuEnriched_Run1718_list)) != 0:
            all_good = False
        QCD_EMEnriched_Run1718_list = [basename + 'QCD_EMEnriched_MiniAOD2017.root',
                        basename + 'QCD_EMEnriched_MiniAOD2018.root']
        if os.system(merge_files(basename + 'QCD_EMEnriched_MiniAOD1718.root', QCD_EMEnriched_Run1718_list)) != 0:
            all_good = False
        QCD_bcToE_Run1718_list = [basename + 'QCD_bcToE_MiniAOD2017.root',
                        basename + 'QCD_bcToE_MiniAOD2018.root']
        if os.system(merge_files(basename + 'QCD_bcToE_MiniAOD1718.root', QCD_bcToE_Run1718_list)) != 0:
            all_good = False

    return all_good






#customizable parameters
tag = 'final'
n_hadds = 8


base_paths = []
base_paths.append('/user/bvermass/public/2l2q_analysis/histograms_unparametrized_LowAndHighMass/' + tag + '/full_analyzer/')
#base_paths.append('/user/bvermass/public/2l2q_analysis/trees_unparametrized_LowAndHighMass/HNLtagger_electron/' + tag + '/full_analyzer/')
#base_paths.append('/user/bvermass/public/2l2q_analysis/trees_unparametrized_LowAndHighMass/HNLtagger_muon/' + tag + '/full_analyzer/')
base_paths.append('/user/bvermass/public/2l2q_analysis/trees_unparametrized_LowAndHighMass/BkgEstimator/' + tag + '/full_analyzer/')

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

for base_path in base_paths:
    add_Dirac_cc( base_path, n_hadds)

os.system( './test/scripts/wait_until_jobs_are_finished.sh' )


for base_path in base_paths:
    if merge_similar_samples(base_path):
        print 'successfully merged: {}'.format(base_path)
    else:
        print 'failed merging: {}'.format(base_path)
