import os, sys

if len(sys.argv) != 3:
    print('wrong number of arguments, input should be: python skim_and_hadd_tuples.py [production_version] [dilep_tag]')
    sys.exit()

os.system('voms')
os.system('make -f makeSkimmer')

pnfs_base_path = "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/"
pnfs_path = pnfs_base_path
production_version = sys.argv[1]
dilep_tag = sys.argv[2]
print os.listdir(pnfs_base_path)
for crabdir in os.listdir(pnfs_base_path):
    if production_version in crabdir:
        print 'production {} found'.format(production_version)
        pnfs_path = pnfs_base_path + crabdir
        for root, dirs, files in os.walk(pnfs_path):
            for f in files:
                if 'dilep' in f and '.root' in f:
                    print('{}'.format(os.path.abspath(os.path.join(root, f))))
                    os.system('./test {} ~/public/heavyNeutrino/skim/{}'.format(os.path.abspath(os.path.join(root, f)), f))
os.system('hadd ~/public/heavyNeutrino/skim/dilep_* ~/public/heavyNeutrino/dilep_skim.root')
os.system('gfal-copy -p -f -t 5000 file:///user/bvermass/public/heavyNeutrino/dilep_skim.root srm://maite.iihe.ac.be:8443{}/{}.root'.format(pnfs_base_path, dilep_tag))
