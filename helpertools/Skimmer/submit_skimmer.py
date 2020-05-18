import os, sys
import time

current_directory = os.path.dirname( os.path.abspath( __file__ ) )

def init_script( scriptname ):
    script = open(scriptname, 'w')
    script.write('#!/bin/bash\n')
    script.write('cd ' + current_directory + '\n')
    script.write('eval `scram runtime -sh`\n')
    return script


def submit_script( script, scriptname ):
    print 'submitting {}'.format( scriptname )
    script.close()
    while os.system('qsub {} -l walltime=01:00:00'.format(scriptname)) != 0:
        print 'qsub error caught, resubmitting'
        time.sleep(2)


def merge_skimmed_files( input_crab_paths ):
    if os.system('hadd -f ~/public/heavyNeutrino/dilep_skim.root ~/public/heavyNeutrino/skim/*.root') == 0:
        print 'successfully hadded dilep files into dilep_skim.root'
        os.system('rm ~/public/heavyNeutrino/skim/*.root')
        for input_crab_path in input_crab_paths:
            os.system('echo {} >> hadded_samples.txt'.format(input_crab_path))
    else:
        print 'hadd dilep files into dilep_skim failed, exiting...'
        sys.exit()


def copy_dilepskim_to_pnfs( output_path, dilep_tag, input_crab_paths ):
    if os.path.exists('{}{}.root'.format(output_path, dilep_tag)):
        os.system('gfal-copy -p -f -t 5000 srm://maite.iihe.ac.be:8443{}{}.root srm://maite.iihe.ac.be:8443{}{}_old.root'.format(output_path, dilep_tag, output_path, dilep_tag))

    if os.system('gfal-copy -p -f -t 5000 file:///user/bvermass/public/heavyNeutrino/dilep_skim.root srm://maite.iihe.ac.be:8443{}{}.root'.format(output_path, dilep_tag)) == 0:
        print 'successfully copied dilep_skim to pnfs to {}{}'.format(output_path, dilep_tag)
        os.system('rm ~/public/heavyNeutrino/dilep_skim.root')
        for input_crab_path in input_crab_paths:
            os.system('echo {} >> finished_samples.txt'.format(input_crab_path))
    else:
        print 'copy dilep_skim to pnfs failed, exiting...'
        sys.exit()


def get_run_eras_data( input_sample_path, production_version ):
    run_eras = []
    for crabdir in os.listdir(input_sample_path):
        full_crab_path = input_sample_path + crabdir + "/"
        if production_version in full_crab_path and 'Run201' in full_crab_path and not full_crab_path in open('finished_samples.txt').read():
            
            index = crabdir.find('Run201')
            print index
            era = crabdir[index:index+8]
            if not era in run_eras:
                run_eras.append(era)

    if len(run_eras) == 0:
        run_eras.append('')
            
    return run_eras


def get_run_era( crabdir ):
    startindex_data = crabdir.find('Run201')
    if startindex_data != -1:
        return crabdir[startindex_data:startindex_data+8] + '/'
    elif crabdir.find('MiniAOD2016') != -1 or crabdir.find('Summer16MiniAOD') != -1 or crabdir.find('dilepton_HNL_2016') != -1:
        return 'MiniAOD2016/'
    elif crabdir.find('MiniAOD2017') != -1 or crabdir.find('Fall17MiniAOD') != -1 or crabdir.find('dilepton_HNL_2017') != -1:
        return 'MiniAOD2017/'
    elif crabdir.find('MiniAOD2018') != -1 or crabdir.find('Autumn18MiniAOD') != -1 or crabdir.find('dilepton_HNL_2018') != -1:
        return 'MiniAOD2018/'
    else:
        return ''


def get_crab_paths( input_sample_path, production_version, run_era_for_data):
    input_crab_paths = []
    for crabdir in os.listdir(input_sample_path):
        full_crab_path = input_sample_path + crabdir + "/"
        if production_version in full_crab_path and run_era_for_data in full_crab_path and not full_crab_path in open('finished_samples.txt').read():
            input_crab_paths.append(full_crab_path)
            
    return input_crab_paths
        

if len(sys.argv) != 4:
    print('Wrong number of arguments, input should be: python submit_skim_and_hadd_tuples.py [production_version] [dilep_tag] [number_of_hadds_per_job]')
    sys.exit()

#os.system('voms-proxy-init --voms cms')
os.system('make -f makeSkimmer')
print 'cleaned finished_samples.txt?'
os.system('touch finished_samples.txt')
os.system('touch hadded_samples.txt')

output_base_path = "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/"
input_base_path = output_base_path
output_sample_path = output_base_path
input_crab_path = output_base_path

production_version = sys.argv[1]
dilep_tag = sys.argv[2]
n_hadds = int(sys.argv[3])
print 'production_version: {}, dilep_tag: {}, n_hadds: {}'.format(production_version, dilep_tag, n_hadds)

for sampledir in os.listdir(input_base_path):
    print sampledir
    hasproduction = False
    output_sample_path = output_base_path + sampledir + "/" #The final dilep_tag.root file will end up here
    input_sample_path = input_base_path + sampledir + "/"
    if not os.path.isdir(input_sample_path):
        continue

    script_counter = 0
    hadd_counter = 0

    run_eras = get_run_eras_data(input_sample_path, production_version)

    for run_era in run_eras:
        input_crab_paths = get_crab_paths(input_sample_path, production_version, run_era)
        if len(input_crab_paths) == 0 :
            continue
        output_path = output_sample_path + get_run_era(input_crab_paths[0])

        for i in range(len(input_crab_paths)):
            print '    hadding {}: {}'.format(str(i), input_crab_paths[i])
            for root, dirs, files in os.walk(input_crab_paths[i]):
                for f in files:
                    if '.root' in f:
                        if hadd_counter == 0:
                            scriptname = 'script_{}.sh'.format( script_counter )
                            print 'making next {}'.format( scriptname )
                            script = init_script( scriptname )
                            script_counter += 1
                        print('{} to {}'.format(os.path.abspath(os.path.join(root, f)), f.split('.')[0] + '_' + str(i) + '.root'))
                        script.write('./test {} /user/bvermass/public/heavyNeutrino/skim/{}\n'.format(os.path.abspath(os.path.join(root, f)), f.split('.')[0] + '_' + str(i) + '.root'))
                        hadd_counter += 1
                        if hadd_counter == n_hadds:
                            submit_script( script, scriptname )
                            hadd_counter = 0


        #send last job to the cluster if it wasn't filled up to n_hadds
        if hadd_counter != 0:
            submit_script( script, scriptname )
            hadd_counter = 0

        os.system( './../../test/scripts/wait_until_jobs_are_finished.sh' )
        merge_skimmed_files( input_crab_paths )
        copy_dilepskim_to_pnfs( output_path, dilep_tag, input_crab_paths )

print 'successfully finished'
