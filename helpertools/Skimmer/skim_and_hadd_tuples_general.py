import os, sys

if len(sys.argv) != 3:
    print('wrong number of arguments, input should be: python skim_and_hadd_tuples.py [production_version] [dilep_tag]')
    sys.exit()

os.system('make -f makeSkimmer')
print('cleaned finished_samples.txt?')

pnfs_base_path = "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/"
pnfs_sample_path = pnfs_base_path
pnfs_crab_path = pnfs_base_path


production_version = sys.argv[1]
dilep_tag = sys.argv[2]


for sampledir in os.listdir(pnfs_base_path):
    hasproduction = False
    pnfs_sample_path = pnfs_base_path + sampledir + "/"
    if sampledir in open('finished_samples.txt').read():
        print('already finished {}'.format(sampledir))
    else:
        for crabdir in os.listdir(pnfs_sample_path):
            if production_version in crabdir:
                hasproduction = True

                pnfs_crab_path = pnfs_sample_path + crabdir + "/"
                print 
                print 'production: {}'.format(pnfs_crab_path)

                for root, dirs, files in os.walk(pnfs_crab_path):
                    for f in files:
                        if 'dilep' in f and '.root' in f:
                            full_path = os.path.abspath(os.path.join(root, f))
                            if not 'failed' in full_path:
                                print full_path
                                os.system('./test {} ~/public/heavyNeutrino/skim/{}'.format(full_path, f))

        if hasproduction:
            if os.system('hadd -f ~/public/heavyNeutrino/dilep_skim.root ~/public/heavyNeutrino/skim/dilep_*') == 0:
                print 'successfully hadded dilep files into dilep_skim.root'
                os.system('rm ~/public/heavyNeutrino/skim/dilep_*')
                os.system('echo {} >> hadded_samples.txt'.format(pnfs_sample_path))
            if os.system('gfal-copy -p -f -t 5000 file:///user/bvermass/public/heavyNeutrino/dilep_skim.root srm://maite.iihe.ac.be:8443{}{}.root'.format(pnfs_sample_path, dilep_tag)) == 0:
                print 'successfully copied dilep_skim to pnfs to {}'.format(dilep_tag)
                os.system('rm ~/public/heavyNeutrino/dilep_skim.root')
                os.system('echo {} >> finished_samples.txt'.format(pnfs_sample_path))
