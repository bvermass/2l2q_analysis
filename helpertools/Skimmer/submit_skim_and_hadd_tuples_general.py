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

def merge_skimmed_files( pnfs_sample_path, pnfs_crab_paths ):
    if os.system('hadd -f ~/public/heavyNeutrino/dilep_skim.root ~/public/heavyNeutrino/skim/dilep_*') == 0:
        print 'successfully hadded dilep files into dilep_skim.root'
        os.system('rm ~/public/heavyNeutrino/skim/dilep_*')
        for pnfs_crab_path in pnfs_crab_paths:
            os.system('echo {} >> hadded_samples.txt'.format(pnfs_crab_path))
    else:
        print 'hadd dilep files into dilep_skim failed, exiting...'
        sys.exit()

def copy_dilepskim_to_pnfs( pnfs_sample_path, RunEra, dilep_tag, pnfs_crab_paths ):
    if os.system('gfal-copy -p -f -t 5000 file:///user/bvermass/public/heavyNeutrino/dilep_skim.root srm://maite.iihe.ac.be:8443{}/{}{}.root'.format(pnfs_sample_path, RunEra, dilep_tag)) == 0:
        print 'successfully copied dilep_skim to pnfs to {}{}'.format(RunEra, dilep_tag)
        os.system('rm ~/public/heavyNeutrino/dilep_skim.root')
        for pnfs_crab_path in pnfs_crab_paths:
            os.system('echo {} >> finished_samples.txt'.format(pnfs_crab_path))
    else:
        print 'copy dilep_skim to pnfs failed, exiting...'
        sys.exit()

if len(sys.argv) != 4:
    print('Wrong number of arguments, input should be: python submit_skim_and_hadd_tuples.py [production_version] [dilep_tag] [number_of_hadds_per_job]')
    sys.exit()

#os.system('voms-proxy-init --voms cms')
os.system('make -f makeSkimmer')
print 'cleaned finished_samples.txt?'

pnfs_base_path = "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/"
pnfs_sample_path = pnfs_base_path
pnfs_crab_path = pnfs_base_path

production_version = sys.argv[1]
dilep_tag = sys.argv[2]
n_hadds = int(sys.argv[3])
print 'production_version: {}, dilep_tag: {}, n_hadds: {}'.format(production_version, dilep_tag, n_hadds)

for sampledir in os.listdir(pnfs_base_path):
    print sampledir
    hasproduction = False
    pnfs_sample_path = pnfs_base_path + sampledir + "/" #The final dilep_tag.root file will end up here

    script_counter = 0
    hadd_counter = 0
    pnfs_crab_paths = [] #this one will keep track of all crab paths that were hadded and finished

    for crabdir in os.listdir(pnfs_sample_path):
        print '    {}'.format( crabdir )
        pnfs_crab_path = pnfs_sample_path + crabdir + "/"
        if production_version in crabdir and not pnfs_crab_path in open('finished_samples.txt').read():
            hasproduction = True

            startindex = crabdir.find('Run201')
            if startindex != -1:
                RunEra = crabdir[startindex:startindex+8] + '/'
            else:
                RunEra = ''

            pnfs_crab_paths.append( pnfs_crab_path )

            for root, dirs, files in os.walk(pnfs_crab_path):
                for f in files:
                    if 'dilep' in f and '.root' in f:
                        if hadd_counter == 0:
                            scriptname = 'script_{}.sh'.format( script_counter )
                            print 'making next {}'.format( scriptname )
                            script = init_script( scriptname )
                            script_counter += 1
                        print('{}'.format(os.path.abspath(os.path.join(root, f))))
                        script.write('./test {} ~/public/heavyNeutrino/skim/{}\n'.format(os.path.abspath(os.path.join(root, f)), f))
                        hadd_counter += 1
                        if hadd_counter == n_hadds:
                            submit_script( script, scriptname )
                            hadd_counter = 0


    if hasproduction:
        #send last job to the cluster if it wasn't filled up to n_hadds
        if hadd_counter != 0:
            submit_script( script, scriptname )
            hadd_counter = 0
        
        os.system( './../../test/scripts/wait_until_jobs_are_finished.sh' )
        merge_skimmed_files( pnfs_sample_path, pnfs_crab_paths )
        copy_dilepskim_to_pnfs( pnfs_sample_path, RunEra, dilep_tag, pnfs_crab_paths )
