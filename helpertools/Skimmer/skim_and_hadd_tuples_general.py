import os, sys

if len(sys.argv) != 3:
    print('wrong number of arguments, input should be: python skim_and_hadd_tuples.py [production_version] [dilep_tag]')
    sys.exit()

os.system('voms-proxy-init --voms cms')
os.system('make -f makeSkimmer')

pnfs_base_path = "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/"
pnfs_sample_path = pnfs_base_path
pnfs_crab_path = pnfs_base_path
production_version = sys.argv[1]
dilep_tag = sys.argv[2]
for sampledir in os.listdir(pnfs_base_path):
    pnfs_sample_path = pnfs_base_path + sampledir + "/"
    for crabdir in os.listdir(pnfs_sample_path):
        if production_version in crabdir:
            pnfs_crab_path = pnfs_sample_path + crabdir + "/"
            print 'production: {}'.format(pnfs_crab_path)
            for root, dirs, files in os.walk(pnfs_crab_path):
                for f in files:
                    if 'dilep' in f and '.root' in f:
                        print('{}'.format(os.path.abspath(os.path.join(root, f))))
                        os.system('./test {} ~/public/heavyNeutrino/skim/{}'.format(os.path.abspath(os.path.join(root, f)), f))
    if os.system('hadd ~/public/heavyNeutrino/skim/dilep_* ~/public/heavyNeutrino/dilep_skim.root') == 0:
        os.system('rm ~/public/heavyNeutrino/skim/dilep_*')
    if os.system('gfal-copy -p -f -t 5000 file:///user/bvermass/public/heavyNeutrino/dilep_skim.root srm://maite.iihe.ac.be:8443{}/{}.root'.format(pnfs_sample_path, dilep_tag)) == 0:
        os.system('rm ~/public/heavyNeutrino/dilep_skim.root')
