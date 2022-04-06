#!/bin/env python

import os, sys
import glob
import ROOT
import multiprocessing

from optparse import OptionParser

def main(argv = None):

    if argv == None:
        argv = sys.argv[1:]

    usage = "usage: %prog [options]\n Incorporate ABCD method in Combine"

    parser = OptionParser(usage)
    parser.add_option("--input", type=str, default='/user/bvermass/public_html/2l2q_analysis/combine_observed', help="Input card directory [default: %default]")
    parser.add_option("--output", type=str, default='cards', help="Output card directory [default: %default]")
    parser.add_option("--ncores", type=int, default=4, help="Number of cores for multiprocessing [default: %default]")
    parser.add_option("--fake", action="store_true", help="Produce fake shapes [default: %default]")

    (options, args) = parser.parse_args(sys.argv[1:])

    return options

def procCard(dname, fname, fout, typ, mass):

    print dname, fname
    dabcd = ['ShapefilesA', 'ShapefilesB', 'ShapefilesC', 'ShapefilesD']
    intSig, intABCD, intData = [], [], []
    fs = typ+'_cutTightmlSV_quadA_Shape_SR.root'
    for dn, d in enumerate(dabcd):
        fr = ROOT.TFile(options.output+'/'+dname+'/'+d+'/'+fs, 'READ')
        hSig = fr.Get('HNL_'+mass); intSig.append(hSig.Integral())
        hABCD = fr.Get('ABCD'); intABCD.append(hABCD.Integral())
        hData = fr.Get('data_obs'); intData.append(hData.Integral())
        fr.Close()
    
    pcardi = ''
    with open(fname, 'r') as f:
        for fl in f.readlines():
            if ('lnN' in fl) or ('shapeN' in fl) or ('auto' in fl):
                if 'auto' not in fl: fl = fl.rstrip('\n') + ' - - - - - -\n'
                pcardi += fl
        f.close()

    with open(fout, 'w') as f:
        gap = '----------------------------------------------------------------------------------------\n'
        pcard = 'imax 4 number of channels\n'
        pcard += 'jmax 1 number of backgrounds\n'
        pcard += 'kmax 10 number of nuisance parameters\n'
        pcard += gap
        pcard += 'bin chA chB chC chD\n'
        pcard += 'observation '+str(intData[0])+' '+str(intData[1])+' '+str(intData[2])+' '+str(intData[3])+'\n'
        pcard += gap
        pcard += 'shapes * chA '+dabcd[0]+'/'+fs+' $PROCESS $PROCESS_$SYSTEMATIC\n'
        pcard += 'shapes * chB '+dabcd[1]+'/'+fs+' $PROCESS $PROCESS_$SYSTEMATIC\n'
        pcard += 'shapes * chC '+dabcd[2]+'/'+fs+' $PROCESS $PROCESS_$SYSTEMATIC\n'
        pcard += 'shapes * chD '+dabcd[3]+'/'+fs+' $PROCESS $PROCESS_$SYSTEMATIC\n'
        pcard += gap
        pcard += 'bin chA chA chB chB chC chC chD chD\n'
        pcard += 'process HNL_'+mass+' ABCD HNL_'+mass+' ABCD HNL_'+mass+' ABCD HNL_'+mass+' ABCD\n'
        pcard += 'process 0 1 0 1 0 1 0 1\n'
        pcard += 'rate '+str(intSig[0])+' '+str(intABCD[0])+' '+str(intSig[1])+' '+str(intABCD[1])+' '+str(intSig[2])+' '+str(intABCD[2])+' '+str(intSig[3])+' '+str(intABCD[3])+'\n'
        pcard += gap
        pcard += 'alpha rateParam chA ABCD (@0*@1/@2) beta,gamma,delta\n'
        pcard += 'beta  rateParam chB ABCD 1.\n'
        pcard += 'gamma rateParam chC ABCD 1.\n'
        pcard += 'delta rateParam chD ABCD 1.\n'
        pcard += gap
        pcard += pcardi
        f.write(pcard)
        f.close()
        
if __name__ == '__main__':
        
    options = main()
    
    cdir = os.getcwd()
    
    pool = multiprocessing.Pool(options.ncores)
    
    os.system('rm -rf '+options.output+'; mkdir '+options.output)

    dlist = [d.split('/')[-2] for d in glob.glob(options.input+'/datacards/*/')]
    print(dlist)
    for d in dlist:
        print('processing {}'.format(d))
        if len(glob.glob(options.input+'/datacards/'+d+'/*.txt')) == 0 or d.find('2016') == -1:
            continue

        os.system('mkdir '+options.output+'/'+d)
        os.system('mkdir '+options.output+'/'+d+'/ShapefilesA')
        os.system('mkdir '+options.output+'/'+d+'/ShapefilesB')
        os.system('mkdir '+options.output+'/'+d+'/ShapefilesC')
        os.system('mkdir '+options.output+'/'+d+'/ShapefilesD')
        os.system('cp '+options.input+'/Shapefiles/'+d+'/*.root '+options.output+'/'+d+'/ShapefilesA/.')
        os.system('cp '+options.input+'/quadB_events/'+d+'/*.root '+options.output+'/'+d+'/ShapefilesB/.')
        os.system('cp '+options.input+'/quadC_events/'+d+'/*.root '+options.output+'/'+d+'/ShapefilesC/.')
        os.system('cp '+options.input+'/quadD_events/'+d+'/*.root '+options.output+'/'+d+'/ShapefilesD/.')
        flist = [f.split('/')[-1] for f in glob.glob(options.input+'/datacards/'+d+'/*.txt')]

        jobs = []
        for f in flist:
            typ = f.split('_cut')[0]
            mass = f.split('_')[2]
            jobs.append( pool.apply_async(procCard, (d, options.input+'/datacards/'+d+'/'+f, options.output+'/'+d+'/'+f, typ, mass)) )
        for job in jobs: result = job.get()
