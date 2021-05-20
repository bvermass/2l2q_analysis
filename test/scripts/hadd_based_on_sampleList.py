import os,sys,glob
samplelists = glob.glob("/user/bvermass/heavyNeutrino/Dileptonprompt/CMSSW_10_2_14/src/2l2q_analysis/data/HNL_merging_parameters/*majorana.txt")

for sampleList in samplelists:
    files = [line.strip() for line in open(sampleList)]
    files = [line.split()[0] for line in files if line and not line.startswith('#')] # Clean empty and comment lines

    file0 = files[0]
    outputfile = "/user/bvermass/public/heavyNeutrino/" + file0[file0.find("HeavyNeutrino_lljj"):file0.find("V-")+2] + "combined" + file0[file0.find("_", file0.find("V-")+3):file0.find("/dilep")]
    pnfsfile = "/pnfs/iihe/cms/store/user/bvermass/heavyNeutrino/" + file0[file0.find("HeavyNeutrino_lljj"):file0.find("V-")+2] + "combined" + file0[file0.find("_", file0.find("V-")+3):file0.find("/dilep")]
    print(outputfile)
    os.system("mkdir -p {}".format(outputfile))

    commandline = 'hadd -f {}/dilep_final.root'.format(outputfile)
    for f in files:
        commandline += ' {}'.format(f)

    os.system(commandline)
    os.system('gfal-copy -p -f -t 5000 file://{}/dilep_final.root srm://maite.iihe.ac.be:8443{}/dilep_final.root'.format(outputfile, pnfsfile))
    os.system('rm {}/dilep_final.root'.format(outputfile))
