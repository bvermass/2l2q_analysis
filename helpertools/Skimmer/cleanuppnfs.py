import os,sys

def go_over_crab_dirs( production_version, pnfs_base_path, exec_string):
    for sampledir in os.listdir(pnfs_base_path):
        pnfs_sample_path = pnfs_base_path + sampledir + "/"
        for crabdir in os.listdir(pnfs_sample_path):
            if production_version in crabdir:
                pnfs_crab_path = pnfs_sample_path + crabdir + "/"
                print 'production: {}'.format(pnfs_crab_path)
                if exec_string != "" and "{}" in exec_string:
                    os.system(exec_string.format(pnfs_crab_path))


if len(sys.argv) != 2:
    print('wrong number of arguments, input should be: python cleanuppnfs.py [production_version]')
    sys.exit()

pnfs_base_path = "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/"
pnfs_sample_path = pnfs_base_path
pnfs_crab_path = pnfs_base_path

production_version = sys.argv[1]

go_over_crab_dirs( production_version, pnfs_base_path, "" )
var = input("Please enter 'yes' if you want to remove these. ")
if var == "yes":
    go_over_crab_dirs( production_version, pnfs_base_path, "gfal-rm -r srm://maite.iihe.ac.be:8443{}")
